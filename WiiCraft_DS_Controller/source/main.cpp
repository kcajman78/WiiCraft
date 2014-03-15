/* Made By filfat */
#include <nds.h>
#include <stdio.h>
#include <dswifi9.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>

#include <sys/socket.h>
#include <netdb.h>
#include <GEMS_WifiDS.h>

bool Connected = false;
bool debug = false;
bool CMDbool = false;
unsigned int PLAYERS = 4;
unsigned int PORT = 8593;
unsigned int clientForServer;
const unsigned int VERSION = 1;
char HELP[] = "/help or /?: Shows this\n"
			  "/version or ver: Shows the version\n"
			  "/server: Start the server mode\n"
			  "/back: Goes back to connect to server\n"
			  "/clear: Clears the screen\n"
			  "/exit: Exit this app";

void OnKeyPressed(int key) {
   if(key > 0)
      iprintf("%c", key);
}

void CMD(void){
	char CMD[256];
	//int NUMBINPUT;
	consoleClear();
	iprintf("Weclome to debug screen\n");
		while(1){
			scanf("%s", CMD);
			if(!strcmp(CMD, "/server")){
				debug = true;
				break;
			}
			else if((!strcmp(CMD, "/version")) || (!strcmp(CMD, "/ver"))){
				iprintf("Version: %d\n", VERSION);
			}
			else if((!strcmp(CMD, "/help")) || (!strcmp(CMD, "/?"))){
				iprintf("%s", HELP);
			}
			else if(!strcmp(CMD, "/back")){
				consoleClear();
				break;
			}
			else if(!strcmp(CMD, "/clear")){
				consoleClear();
			}
			else if(!strcmp(CMD, "/exit")){
				exit(0);
			}
			else{
				iprintf("Unknown Command\n");
			}
		}
}

int main(void)  {

	struct in_addr ip, gateway, mask, dns1, dns2;
	
	// set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_5_2D);
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	consoleDemoInit();
   
	PrintConsole topScreen;
	PrintConsole bottomScreen;
	
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	consoleInit(&topScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	consoleInit(&bottomScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
   
   consoleSelect(&bottomScreen);
   
   Keyboard *kbd = keyboardDemoInit();
   
   kbd->OnKeyPressed = OnKeyPressed;
   
   consoleSelect(&topScreen);
   
   iprintf("Connecting to WiFi...");
	
	if(!Wifi_InitDefault(WFC_CONNECT)){
		iprintf("Failed to connect!");
		exit(1);
	}
		
		iprintf("Connected\n\n");
		
		uint16 keysPressed = ~(REG_KEYINPUT);
			if(keysPressed & KEY_A){
				debug = true;
			}
		
		ip = Wifi_GetIPInfo(&gateway, &mask, &dns1, &dns2);

		while(Connected == false && debug == false) {
			char wiiIP[256];

			iprintf("Your ip: %s\n",inet_ntoa(ip));
			iprintf("Type in your Wii's IP(or /cmd for the console):\n");
			scanf("%s", wiiIP);

			if(!strcmp(wiiIP, "/cmd")){
				CMD();
				continue;
			}	

			iprintf("\nConnecting To %s\nfrom %s...", wiiIP,inet_ntoa(ip));
			
			int server = 0; server = TCP_ClientConnect(wiiIP, 8593);//TCP_ClientConnect(ip address, port)

			if(server == true){
				Connected = true;
				iprintf("Connected\n");
			}

			while(Connected == true){
				
			}
			
			iprintf("Press start to exit or click any other button to try again:\n");

			scanKeys();
			while(!keysDown()){
				scanKeys();
				if(keysPressed & KEY_START)
					exit(0);
			}

			swiWaitForVBlank();
			consoleClear();
	}
	
	int host = 0;
	int client = 0;
	if(debug == true){
		
		consoleClear();
		iprintf("Welcome To Server Screen\n");
		iprintf("Your ip: %s\n",inet_ntoa(ip));
		host = TCP_Server(PORT, PLAYERS);//TCP_Server(port, number of players)
	}
	
	while(debug == true){
		
		client = PLAYERS; client = TCP_GetClient(host);//TCP_GetClient(host socket)
		if(!clientForServer == 4){
			clientForServer++;
			iprintf("Client connected(%d of %d)\n", clientForServer,PLAYERS);
			iprintf("Client id: %d\n", client);
		}
		
	}

   return 0;
}