/*
Thanks teknecal for the base source code.
*/
#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ogcsys.h>

u8 initialise_reset_button();

void die(const char *msg);

void initialise_network();

s32 server_connect();

bool request_file(s32 server, FILE *f);

extern u32 net_gethostip();

s32 send_message(s32 server, char *msg);

//s32 write_exact(s32 s, char *buf, s32 length);

s32 write_http_reply(s32 server, char *msg);

bool tcp_write (const s32 s, char *buffer, const u32 length);

u32 split(char *s, char sep, u32 maxsplit, char *result[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _COMMON_H_ */
