#include "common_HWSIM.h"

static uint32_t socket_count = 0;

commStatus HWSIM_openLink(commData* cdt, uint16_t port, uint32_t address)
{
	WSADATA wsaData;
	SOCKET new_sock;

	if (socket_count == 0) {
		if (0 != WSAStartup(0x0202, &wsaData)) {
			return comm_INIT_FAILED;
		}
	}

	new_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (new_sock != INVALID_SOCKET) {
		cdt->sck = new_sock;
		socket_count++;
		cdt->dest.sin_family = AF_INET;
		cdt->dest.sin_addr.S_un.S_addr = htonl(address);
		cdt->dest.sin_port = htons(port);
		return comm_OK;
	}
	else {
		return comm_SOCKET_FAILED;
	}
}

commStatus HWSIM_closeLink(commData* cdt)
{
	if (0 != closesocket(cdt->sck))
		return comm_SOCKET_FAILED;
	socket_count--;
	if (socket_count == 0) {
		if (0 != WSACleanup())
			return comm_CLEANUP_FAILED;
	}
	return comm_OK;
}

commStatus HWSIM_sendPacket(commData* cdt, uint32_t size, void* data)
{
	if (size = sendto(cdt->sck, data, size, 0,
			(PSOCKADDR)&(cdt->dest), sizeof(SOCKADDR_IN)))
		return comm_OK;
	else
		return comm_UDP_SEND_FAILED;
}