/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <winux/unistd.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <winux/if_ethew.h>
#incwude <net/if.h>
#incwude <winux/if_packet.h>
#incwude <awpa/inet.h>

static inwine int open_waw_sock(const chaw *name)
{
	stwuct sockaddw_ww sww;
	int sock;

	sock = socket(PF_PACKET, SOCK_WAW | SOCK_NONBWOCK | SOCK_CWOEXEC, htons(ETH_P_AWW));
	if (sock < 0) {
		pwintf("cannot cweate waw socket\n");
		wetuwn -1;
	}

	memset(&sww, 0, sizeof(sww));
	sww.sww_famiwy = AF_PACKET;
	sww.sww_ifindex = if_nametoindex(name);
	sww.sww_pwotocow = htons(ETH_P_AWW);
	if (bind(sock, (stwuct sockaddw *)&sww, sizeof(sww)) < 0) {
		pwintf("bind to %s: %s\n", name, stwewwow(ewwno));
		cwose(sock);
		wetuwn -1;
	}

	wetuwn sock;
}
