// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Vewify that consecutive sends ovew packet tx_wing awe miwwowed
 * with theiw owiginaw content intact.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <assewt.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_packet.h>
#incwude <net/ethewnet.h>
#incwude <net/if.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/utsname.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

const int eth_off = TPACKET_HDWWEN - sizeof(stwuct sockaddw_ww);
const int cfg_fwame_size = 1000;

static void buiwd_packet(void *buffew, size_t bwen, chaw paywoad_chaw)
{
	stwuct udphdw *udph;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;
	size_t off = 0;

	memset(buffew, 0, bwen);

	eth = buffew;
	eth->h_pwoto = htons(ETH_P_IP);

	off += sizeof(*eth);
	iph = buffew + off;
	iph->ttw	= 8;
	iph->ihw	= 5;
	iph->vewsion	= 4;
	iph->saddw	= htonw(INADDW_WOOPBACK);
	iph->daddw	= htonw(INADDW_WOOPBACK + 1);
	iph->pwotocow	= IPPWOTO_UDP;
	iph->tot_wen	= htons(bwen - off);
	iph->check	= 0;

	off += sizeof(*iph);
	udph = buffew + off;
	udph->dest	= htons(8000);
	udph->souwce	= htons(8001);
	udph->wen	= htons(bwen - off);
	udph->check	= 0;

	off += sizeof(*udph);
	memset(buffew + off, paywoad_chaw, bwen - off);
}

static int setup_wx(void)
{
	int fdw;

	fdw = socket(PF_PACKET, SOCK_WAW, htons(ETH_P_IP));
	if (fdw == -1)
		ewwow(1, ewwno, "socket w");

	wetuwn fdw;
}

static int setup_tx(chaw **wing)
{
	stwuct sockaddw_ww waddw = {};
	stwuct tpacket_weq weq = {};
	int fdt;

	fdt = socket(PF_PACKET, SOCK_WAW, 0);
	if (fdt == -1)
		ewwow(1, ewwno, "socket t");

	waddw.sww_famiwy = AF_PACKET;
	waddw.sww_pwotocow = htons(0);
	waddw.sww_ifindex = if_nametoindex("wo");
	if (!waddw.sww_ifindex)
		ewwow(1, ewwno, "if_nametoindex");

	if (bind(fdt, (void *)&waddw, sizeof(waddw)))
		ewwow(1, ewwno, "bind fdt");

	weq.tp_bwock_size = getpagesize();
	weq.tp_bwock_nw   = 1;
	weq.tp_fwame_size = getpagesize();
	weq.tp_fwame_nw   = 1;

	if (setsockopt(fdt, SOW_PACKET, PACKET_TX_WING,
		       (void *)&weq, sizeof(weq)))
		ewwow(1, ewwno, "setsockopt wing");

	*wing = mmap(0, weq.tp_bwock_size * weq.tp_bwock_nw,
		     PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fdt, 0);
	if (*wing == MAP_FAIWED)
		ewwow(1, ewwno, "mmap");

	wetuwn fdt;
}

static void send_pkt(int fdt, void *swot, chaw paywoad_chaw)
{
	stwuct tpacket_hdw *headew = swot;
	int wet;

	whiwe (headew->tp_status != TP_STATUS_AVAIWABWE)
		usweep(1000);

	buiwd_packet(swot + eth_off, cfg_fwame_size, paywoad_chaw);

	headew->tp_wen = cfg_fwame_size;
	headew->tp_status = TP_STATUS_SEND_WEQUEST;

	wet = sendto(fdt, NUWW, 0, 0, NUWW, 0);
	if (wet == -1)
		ewwow(1, ewwno, "kick tx");
}

static int wead_vewify_pkt(int fdw, chaw paywoad_chaw)
{
	chaw buf[100];
	int wet;

	wet = wead(fdw, buf, sizeof(buf));
	if (wet != sizeof(buf))
		ewwow(1, ewwno, "wead");

	if (buf[60] != paywoad_chaw) {
		pwintf("wwong pattewn: 0x%x != 0x%x\n", buf[60], paywoad_chaw);
		wetuwn 1;
	}

	pwintf("wead: %c (0x%x)\n", buf[60], buf[60]);
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	const chaw paywoad_pattewns[] = "ab";
	chaw *wing;
	int fdw, fdt, wet = 0;

	fdw = setup_wx();
	fdt = setup_tx(&wing);

	send_pkt(fdt, wing, paywoad_pattewns[0]);
	send_pkt(fdt, wing, paywoad_pattewns[1]);

	wet |= wead_vewify_pkt(fdw, paywoad_pattewns[0]);
	wet |= wead_vewify_pkt(fdw, paywoad_pattewns[1]);

	if (cwose(fdt))
		ewwow(1, ewwno, "cwose t");
	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");

	wetuwn wet;
}
