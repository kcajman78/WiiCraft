/*
Thanks teknecal for the base code.
*/
#include <errno.h>
#include <fat.h>
#include <math.h>
#include <network.h>
#include <ogc/lwp_watchdog.h>
#include <ogcsys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <unistd.h>
#include <wiiuse/wpad.h>
#include "common.h"

#define NET_BUFFER_SIZE 1024
#define BUFFER_SIZE 1025 // In case server lines not showing up correctly, try to increas this number.
#define IP_ADDRESS "23.99.0.12" // IP address for Webhost
#define SOCKET_PORT 80 

static volatile u8 reset = 0;
static lwp_t reset_thread;

long bytes_count = 0;

static void reset_called() {
	reset = 1;
}

static void *run_reset_thread(void *arg) {
	while (!reset && !(WPAD_ButtonsHeld(0) & WPAD_BUTTON_HOME)) {
		sleep(1);
		WPAD_ScanPads();
	}
	printf("\nShutting down...\n");
	exit(0);
}

u8 initialise_reset_button() {
	s32 result = LWP_CreateThread(&reset_thread, run_reset_thread, NULL, NULL, 0, 80);
	if (result == 0) SYS_SetResetCallback(reset_called);
	return !result;
}

// Write our message to the server
s32 write_http_reply(s32 server, char *msg) {
    u32 msglen = strlen(msg);
    char msgbuf[msglen + 1];
    if (msgbuf == NULL) return -ENOMEM;
    //sprintf(msgbuf, "%s", msg);
    strcpy(msgbuf, msg);
    //printf("Request: %s", msgbuf);
    //return write_exact(server, msgbuf, msglen);
  
    tcp_write (server, msgbuf, msglen);
    //net_write(server, msgbuf, msglen);
    return 1;
}

bool tcp_write (const s32 s, char *buffer, const u32 length) {
    char *p;
    u32 step, left, block, sent;
    s64 time;
    s32 res;
	(void) time; // Has no effect, but silences the "set but not used" warning
  
    step = 0;
    p = buffer;
    left = length;
    sent = 0;
  
    time = gettime ();
    while (left) {
     
        block = left;
        if (block > 2048)
            block = 2048;
      
        res = net_write (s, p, block);
      
        if ((res == 0) || (res == -56)) {
            usleep (20 * 1000);
            continue;
        }
      
        if (res < 0) {
            break;
        }
      
        sent += res;
        left -= res;
        p += res;
      
        if ((sent / NET_BUFFER_SIZE) > step) {
            time = gettime ();
            step++;
        }
    }
  
    return left == 0;
}

// Request a file from the server and store it
bool request_file(s32 server, FILE *f) {
  
    char message[NET_BUFFER_SIZE];
    s32 bytes_read = net_read(server, message, sizeof(message));

    int length_til_data = 0; // Count the length of each \n part until we reach actual data
    int tok_count = 2; // Count the number of \n tokens
    char *temp_tok;
    if (bytes_read == 0) { return -1; }
    temp_tok = strtok (message,"\n");
  
    while (temp_tok != NULL) {
      
        // If HTTP status code is 4xx or 5xx then close connection and try again 3 times
        if (strstr(temp_tok, "HTTP/1.1 4") || strstr(temp_tok, "HTTP/1.1 5")) {
            printf("The server appears to be having an issue. Retry...\n");
			sleep(4000);
            return -1;
        }
      
        if (strlen(temp_tok) == 1) {
            break;
        }
      
        length_til_data += strlen(temp_tok);
        tok_count++;  
        temp_tok = strtok (NULL, "\n");
    }
  
    // New place to store the real data
    char store_data[NET_BUFFER_SIZE];
  
    // We'll store this to the new array
    int q;
    int i = 0;
    for (q = length_til_data + tok_count; q < bytes_read; q++) {
        store_data[i] = message[q];
        i++;
    }
  
    // We now store the real data out of the first 1024 bytes
    if (store_data != NULL) {
        s32 bytes_written = fwrite(store_data, 1, i, f);
        if (bytes_written < i) {
            printf("DEBUG: fwrite error: [%i] %s\n", ferror(f), strerror(ferror(f)));
            sleep(4000);
            return -1;
        }
    }
  
    // Now we can continue storing the rest of the file
    while (bytes_read > 0) {      
        bytes_read = net_read(server, message, sizeof(message));
		
		bytes_count += bytes_read;
		if (bytes_count >= 2000) {
			bytes_count = 0;
			printf(".");
		}
		
        s32 bytes_written = fwrite(message, 1, bytes_read, f);
        if (bytes_written < bytes_read) {
            printf("DEBUG: fwrite error: [%i] %s\n", ferror(f), strerror(ferror(f)));
            sleep(40000);
            return -1;
        }
      
    }
  
    return 1;
}

// Connect to the remote server
s32 server_connect() {
	struct sockaddr_in connect_addr;
	
	s32 server = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (server < 0) die("Error creating socket, exiting");
	
	memset(&connect_addr, 0, sizeof(connect_addr));
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = SOCKET_PORT;
	connect_addr.sin_addr.s_addr= inet_addr(IP_ADDRESS);
	
	if (net_connect(server, (struct sockaddr*)&connect_addr, sizeof(connect_addr)) == -1) {
		net_close(server);
		die("Failed to connect to the remote server.\n");
	}
	
	return server;
}


void die(const char *msg) {
	printf(msg);
	sleep(5);
	fatUnmount("sd:");
	exit(1);
}

void initialise_network() {
    printf("\nWaiting for network to initialise...\n");
	s32 result = -1;
	while (result < 0) {
		while ((result = net_init()) == -EAGAIN) {
		}
		if (result < 0) printf("Unable to initialise network, retrying(net_init)...\n");
	}
	if (result >= 0) {
		u32 ip = 0;
		do {
			ip = net_gethostip();
			if (!ip) printf("Unable to initialise network, retrying(net_gethostip)...\n");
		} while (!ip);
		if (ip) printf("Network initialised.\n");
	}
}

typedef s32 (*transferrer_type)(s32 s, void *mem, s32 len);
inline static s32 transfer_exact(s32 s, char *buf, s32 length, transferrer_type transferrer) {
    s32 bytes_transferred = 0;
    s32 remaining = length;
    while (remaining) {
        if ((bytes_transferred = transferrer(s, buf, remaining > NET_BUFFER_SIZE ? NET_BUFFER_SIZE : remaining)) > 0) {
            remaining -= bytes_transferred;
            buf += bytes_transferred;
        } else if (bytes_transferred < 0) {
            return bytes_transferred;
        } else {
            return -ENODATA;
        }
    }
    return 0;
}

inline s32 write_exact(s32 s, char *buf, s32 length) {
    return transfer_exact(s, buf, length, (transferrer_type)net_write);
}
