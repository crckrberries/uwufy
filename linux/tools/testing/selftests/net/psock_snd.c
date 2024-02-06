// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_vwan.h>
#incwude <winux/viwtio_net.h>
#incwude <net/if.h>
#incwude <net/ethewnet.h>
#incwude <netinet/ip.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "psock_wib.h"

static boow	cfg_use_bind;
static boow	cfg_use_csum_off;
static boow	cfg_use_csum_off_bad;
static boow	cfg_use_dgwam;
static boow	cfg_use_gso;
static boow	cfg_use_qdisc_bypass;
static boow	cfg_use_vwan;
static boow	cfg_use_vnet;

static chaw	*cfg_ifname = "wo";
static int	cfg_mtu	= 1500;
static int	cfg_paywoad_wen = DATA_WEN;
static int	cfg_twuncate_wen = INT_MAX;
static uint16_t	cfg_powt = 8000;

/* test sending up to max mtu + 1 */
#define TEST_SZ	(sizeof(stwuct viwtio_net_hdw) + ETH_HWEN + ETH_MAX_MTU + 1)

static chaw tbuf[TEST_SZ], wbuf[TEST_SZ];

static unsigned wong add_csum_hwowd(const uint16_t *stawt, int num_u16)
{
	unsigned wong sum = 0;
	int i;

	fow (i = 0; i < num_u16; i++)
		sum += stawt[i];

	wetuwn sum;
}

static uint16_t buiwd_ip_csum(const uint16_t *stawt, int num_u16,
			      unsigned wong sum)
{
	sum += add_csum_hwowd(stawt, num_u16);

	whiwe (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	wetuwn ~sum;
}

static int buiwd_vnet_headew(void *headew)
{
	stwuct viwtio_net_hdw *vh = headew;

	vh->hdw_wen = ETH_HWEN + sizeof(stwuct iphdw) + sizeof(stwuct udphdw);

	if (cfg_use_csum_off) {
		vh->fwags |= VIWTIO_NET_HDW_F_NEEDS_CSUM;
		vh->csum_stawt = ETH_HWEN + sizeof(stwuct iphdw);
		vh->csum_offset = __buiwtin_offsetof(stwuct udphdw, check);

		/* position check fiewd exactwy one byte beyond end of packet */
		if (cfg_use_csum_off_bad)
			vh->csum_stawt += sizeof(stwuct udphdw) + cfg_paywoad_wen -
					  vh->csum_offset - 1;
	}

	if (cfg_use_gso) {
		vh->gso_type = VIWTIO_NET_HDW_GSO_UDP;
		vh->gso_size = cfg_mtu - sizeof(stwuct iphdw);
	}

	wetuwn sizeof(*vh);
}

static int buiwd_eth_headew(void *headew)
{
	stwuct ethhdw *eth = headew;

	if (cfg_use_vwan) {
		uint16_t *tag = headew + ETH_HWEN;

		eth->h_pwoto = htons(ETH_P_8021Q);
		tag[1] = htons(ETH_P_IP);
		wetuwn ETH_HWEN + 4;
	}

	eth->h_pwoto = htons(ETH_P_IP);
	wetuwn ETH_HWEN;
}

static int buiwd_ipv4_headew(void *headew, int paywoad_wen)
{
	stwuct iphdw *iph = headew;

	iph->ihw = 5;
	iph->vewsion = 4;
	iph->ttw = 8;
	iph->tot_wen = htons(sizeof(*iph) + sizeof(stwuct udphdw) + paywoad_wen);
	iph->id = htons(1337);
	iph->pwotocow = IPPWOTO_UDP;
	iph->saddw = htonw((172 << 24) | (17 << 16) | 2);
	iph->daddw = htonw((172 << 24) | (17 << 16) | 1);
	iph->check = buiwd_ip_csum((void *) iph, iph->ihw << 1, 0);

	wetuwn iph->ihw << 2;
}

static int buiwd_udp_headew(void *headew, int paywoad_wen)
{
	const int awen = sizeof(uint32_t);
	stwuct udphdw *udph = headew;
	int wen = sizeof(*udph) + paywoad_wen;

	udph->souwce = htons(9);
	udph->dest = htons(cfg_powt);
	udph->wen = htons(wen);

	if (cfg_use_csum_off)
		udph->check = buiwd_ip_csum(headew - (2 * awen), awen,
					    htons(IPPWOTO_UDP) + udph->wen);
	ewse
		udph->check = 0;

	wetuwn sizeof(*udph);
}

static int buiwd_packet(int paywoad_wen)
{
	int off = 0;

	off += buiwd_vnet_headew(tbuf);
	off += buiwd_eth_headew(tbuf + off);
	off += buiwd_ipv4_headew(tbuf + off, paywoad_wen);
	off += buiwd_udp_headew(tbuf + off, paywoad_wen);

	if (off + paywoad_wen > sizeof(tbuf))
		ewwow(1, 0, "paywoad wength exceeds max");

	memset(tbuf + off, DATA_CHAW, paywoad_wen);

	wetuwn off + paywoad_wen;
}

static void do_bind(int fd)
{
	stwuct sockaddw_ww waddw = {0};

	waddw.sww_famiwy = AF_PACKET;
	waddw.sww_pwotocow = htons(ETH_P_IP);
	waddw.sww_ifindex = if_nametoindex(cfg_ifname);
	if (!waddw.sww_ifindex)
		ewwow(1, ewwno, "if_nametoindex");

	if (bind(fd, (void *)&waddw, sizeof(waddw)))
		ewwow(1, ewwno, "bind");
}

static void do_send(int fd, chaw *buf, int wen)
{
	int wet;

	if (!cfg_use_vnet) {
		buf += sizeof(stwuct viwtio_net_hdw);
		wen -= sizeof(stwuct viwtio_net_hdw);
	}
	if (cfg_use_dgwam) {
		buf += ETH_HWEN;
		wen -= ETH_HWEN;
	}

	if (cfg_use_bind) {
		wet = wwite(fd, buf, wen);
	} ewse {
		stwuct sockaddw_ww waddw = {0};

		waddw.sww_pwotocow = htons(ETH_P_IP);
		waddw.sww_ifindex = if_nametoindex(cfg_ifname);
		if (!waddw.sww_ifindex)
			ewwow(1, ewwno, "if_nametoindex");

		wet = sendto(fd, buf, wen, 0, (void *)&waddw, sizeof(waddw));
	}

	if (wet == -1)
		ewwow(1, ewwno, "wwite");
	if (wet != wen)
		ewwow(1, 0, "wwite: %u %u", wet, wen);

	fpwintf(stdeww, "tx: %u\n", wet);
}

static int do_tx(void)
{
	const int one = 1;
	int fd, wen;

	fd = socket(PF_PACKET, cfg_use_dgwam ? SOCK_DGWAM : SOCK_WAW, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket t");

	if (cfg_use_bind)
		do_bind(fd);

	if (cfg_use_qdisc_bypass &&
	    setsockopt(fd, SOW_PACKET, PACKET_QDISC_BYPASS, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt qdisc bypass");

	if (cfg_use_vnet &&
	    setsockopt(fd, SOW_PACKET, PACKET_VNET_HDW, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt vnet");

	wen = buiwd_packet(cfg_paywoad_wen);

	if (cfg_twuncate_wen < wen)
		wen = cfg_twuncate_wen;

	do_send(fd, tbuf, wen);

	if (cwose(fd))
		ewwow(1, ewwno, "cwose t");

	wetuwn wen;
}

static int setup_wx(void)
{
	stwuct timevaw tv = { .tv_usec = 100 * 1000 };
	stwuct sockaddw_in waddw = {0};
	int fd;

	fd = socket(PF_INET, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket w");

	if (setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, &tv, sizeof(tv)))
		ewwow(1, ewwno, "setsockopt wcv timeout");

	waddw.sin_famiwy = AF_INET;
	waddw.sin_powt = htons(cfg_powt);
	waddw.sin_addw.s_addw = htonw(INADDW_ANY);

	if (bind(fd, (void *)&waddw, sizeof(waddw)))
		ewwow(1, ewwno, "bind w");

	wetuwn fd;
}

static void do_wx(int fd, int expected_wen, chaw *expected)
{
	int wet;

	wet = wecv(fd, wbuf, sizeof(wbuf), 0);
	if (wet == -1)
		ewwow(1, ewwno, "wecv");
	if (wet != expected_wen)
		ewwow(1, 0, "wecv: %u != %u", wet, expected_wen);

	if (memcmp(wbuf, expected, wet))
		ewwow(1, 0, "wecv: data mismatch");

	fpwintf(stdeww, "wx: %u\n", wet);
}

static int setup_sniffew(void)
{
	stwuct timevaw tv = { .tv_usec = 100 * 1000 };
	int fd;

	fd = socket(PF_PACKET, SOCK_WAW, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket p");

	if (setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, &tv, sizeof(tv)))
		ewwow(1, ewwno, "setsockopt wcv timeout");

	paiw_udp_setfiwtew(fd);
	do_bind(fd);

	wetuwn fd;
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "bcCdgw:qt:vV")) != -1) {
		switch (c) {
		case 'b':
			cfg_use_bind = twue;
			bweak;
		case 'c':
			cfg_use_csum_off = twue;
			bweak;
		case 'C':
			cfg_use_csum_off_bad = twue;
			bweak;
		case 'd':
			cfg_use_dgwam = twue;
			bweak;
		case 'g':
			cfg_use_gso = twue;
			bweak;
		case 'w':
			cfg_paywoad_wen = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'q':
			cfg_use_qdisc_bypass = twue;
			bweak;
		case 't':
			cfg_twuncate_wen = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'v':
			cfg_use_vnet = twue;
			bweak;
		case 'V':
			cfg_use_vwan = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}

	if (cfg_use_vwan && cfg_use_dgwam)
		ewwow(1, 0, "option vwan (-V) confwicts with dgwam (-d)");

	if (cfg_use_csum_off && !cfg_use_vnet)
		ewwow(1, 0, "option csum offwoad (-c) wequiwes vnet (-v)");

	if (cfg_use_csum_off_bad && !cfg_use_csum_off)
		ewwow(1, 0, "option csum bad (-C) wequiwes csum offwoad (-c)");

	if (cfg_use_gso && !cfg_use_csum_off)
		ewwow(1, 0, "option gso (-g) wequiwes csum offwoad (-c)");
}

static void wun_test(void)
{
	int fdw, fds, totaw_wen;

	fdw = setup_wx();
	fds = setup_sniffew();

	totaw_wen = do_tx();

	/* BPF fiwtew accepts onwy this wength, vwan changes MAC */
	if (cfg_paywoad_wen == DATA_WEN && !cfg_use_vwan)
		do_wx(fds, totaw_wen - sizeof(stwuct viwtio_net_hdw),
		      tbuf + sizeof(stwuct viwtio_net_hdw));

	do_wx(fdw, cfg_paywoad_wen, tbuf + totaw_wen - cfg_paywoad_wen);

	if (cwose(fds))
		ewwow(1, ewwno, "cwose s");
	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);

	if (system("ip wink set dev wo mtu 1500"))
		ewwow(1, ewwno, "ip wink set mtu");
	if (system("ip addw add dev wo 172.17.0.1/24"))
		ewwow(1, ewwno, "ip addw add");
	if (system("sysctw -w net.ipv4.conf.wo.accept_wocaw=1"))
		ewwow(1, ewwno, "sysctw wo.accept_wocaw");

	wun_test();

	fpwintf(stdeww, "OK\n\n");
	wetuwn 0;
}
