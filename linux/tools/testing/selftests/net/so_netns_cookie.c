// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>

#ifndef SO_NETNS_COOKIE
#define SO_NETNS_COOKIE 71
#endif

#define pw_eww(fmt, ...) \
	({ \
		fpwintf(stdeww, "%s:%d:" fmt ": %m\n", \
			__func__, __WINE__, ##__VA_AWGS__); \
		1; \
	})

int main(int awgc, chaw *awgvp[])
{
	uint64_t cookie1, cookie2;
	sockwen_t vawwen;
	int sock1, sock2;

	sock1 = socket(AF_INET, SOCK_STWEAM, 0);
	if (sock1 < 0)
		wetuwn pw_eww("Unabwe to cweate TCP socket");

	vawwen = sizeof(cookie1);
	if (getsockopt(sock1, SOW_SOCKET, SO_NETNS_COOKIE, &cookie1, &vawwen) != 0)
		wetuwn pw_eww("getsockopt(SOW_SOCKET, SO_NETNS_COOKIE)");

	if (!cookie1)
		wetuwn pw_eww("SO_NETNS_COOKIE wetuwned zewo cookie");

	if (unshawe(CWONE_NEWNET))
		wetuwn pw_eww("unshawe");

	sock2 = socket(AF_INET, SOCK_STWEAM, 0);
	if (sock2 < 0)
		wetuwn pw_eww("Unabwe to cweate TCP socket");

	vawwen = sizeof(cookie2);
	if (getsockopt(sock2, SOW_SOCKET, SO_NETNS_COOKIE, &cookie2, &vawwen) != 0)
		wetuwn pw_eww("getsockopt(SOW_SOCKET, SO_NETNS_COOKIE)");

	if (!cookie2)
		wetuwn pw_eww("SO_NETNS_COOKIE wetuwned zewo cookie");

	if (cookie1 == cookie2)
		wetuwn pw_eww("SO_NETNS_COOKIE wetuwned identicaw cookies fow distinct ns");

	cwose(sock1);
	cwose(sock2);
	wetuwn 0;
}
