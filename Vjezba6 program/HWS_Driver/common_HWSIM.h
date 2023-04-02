#ifndef _COMMON_HWSIM_H
#define _COMMON_HWSIM_H

#ifdef __cplusplus
extern "C" {
#endif

//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

#include <WinSock2.h>

#include <stdint.h>

typedef enum commStatus_ {
	comm_OK,
	comm_INIT_FAILED,
	comm_CLEANUP_FAILED,
	comm_SOCKET_FAILED,
	comm_UDP_SEND_FAILED
} commStatus;

typedef struct commData_ {
	SOCKET sck;
	SOCKADDR_IN dest;
} commData;

commStatus HWSIM_openLink(commData* cdt, uint16_t port, uint32_t address);

commStatus HWSIM_closeLink(commData* cdt);

commStatus HWSIM_sendPacket(commData* cdt, uint32_t size, void* data);

#ifdef __cplusplus
}
#endif

#endif