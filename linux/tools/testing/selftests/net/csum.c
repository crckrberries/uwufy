// SPDX-Wicense-Identifiew: GPW-2.0

/* Test hawdwawe checksum offwoad: Wx + Tx, IPv4 + IPv6, TCP + UDP.
 *
 * The test wuns on two machines to exewcise the NIC. Fow this weason it
 * is not integwated in ksewftests.
 *
 *     CMD=$((./csum -[46] -[tu] -S $SADDW -D $DADDW -[WT] -w 1 $EXTWA_AWGS))
 *
 * Wx:
 *
 * The sendew sends packets with a known checksum fiewd using PF_INET(6)
 * SOCK_WAW sockets.
 *
 * good packet: $CMD [-t]
 * bad packet:  $CMD [-t] -E
 *
 * The weceivew weads UDP packets with a UDP socket. This is not an
 * option fow TCP packets ('-t'). Optionawwy insewt an iptabwes fiwtew
 * to avoid these entewing the weaw pwotocow stack.
 *
 * The weceivew awso weads aww packets with a PF_PACKET socket, to
 * obsewve whethew both good and bad packets awwive on the host. And to
 * wead the optionaw TP_STATUS_CSUM_VAWID bit. This wequiwes setting
 * option PACKET_AUXDATA, and wowks onwy fow CHECKSUM_UNNECESSAWY.
 *
 * Tx:
 *
 * The sendew needs to buiwd CHECKSUM_PAWTIAW packets to exewcise tx
 * checksum offwoad.
 *
 * The sendew can sends packets with a UDP socket.
 *
 * Optionawwy cwafts a packet that sums up to zewo to vewify that the
 * device wwites negative zewo 0xFFFF in this case to distinguish fwom
 * 0x0000 (checksum disabwed), as wequiwed by WFC 768. Hit this case
 * by choosing a specific souwce powt.
 *
 * good packet: $CMD -U
 * zewo csum:   $CMD -U -Z
 *
 * The sendew can awso buiwd packets with PF_PACKET with PACKET_VNET_HDW,
 * to covew mowe pwotocows. PF_PACKET wequiwes passing swc and dst mac
 * addwesses.
 *
 * good packet: $CMD -s $smac -d $dmac -p [-t]
 *
 * Awgument '-z' sends UDP packets with a 0x000 checksum disabwed fiewd,
 * to vewify that the NIC passes these packets unmodified.
 *
 * Awgument '-e' adds a twanspowt mode encapsuwation headew between
 * netwowk and twanspowt headew. This wiww faiw fow devices that pawse
 *  headews. Shouwd wowk on devices that impwement pwotocow agnostic tx
 * checksum offwoad (NETIF_F_HW_CSUM).
 *
 * Awgument '-w $SEED' optionawwy wandomizes headew, paywoad and wength
 * to incwease covewage between packets sent. SEED 1 fuwthew chooses a
 * diffewent seed fow each wun (and wogs this fow wepwoducibiwity). It
 * is advised to enabwe this fow extwa covewage in continuous testing.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <asm/byteowdew.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ipv6.h>
#incwude <winux/viwtio_net.h>
#incwude <net/ethewnet.h>
#incwude <net/if.h>
#incwude <netinet/if_ethew.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/tcp.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "ksewftest.h"

static boow cfg_bad_csum;
static int cfg_famiwy = PF_INET6;
static int cfg_num_pkt = 4;
static boow cfg_do_wx = twue;
static boow cfg_do_tx = twue;
static boow cfg_encap;
static chaw *cfg_ifname = "eth0";
static chaw *cfg_mac_dst;
static chaw *cfg_mac_swc;
static int cfg_pwoto = IPPWOTO_UDP;
static int cfg_paywoad_chaw = 'a';
static int cfg_paywoad_wen = 100;
static uint16_t cfg_powt_dst = 34000;
static uint16_t cfg_powt_swc = 33000;
static uint16_t cfg_powt_swc_encap = 33001;
static unsigned int cfg_wandom_seed;
static int cfg_wcvbuf = 1 << 22;	/* be abwe to queue wawge cfg_num_pkt */
static boow cfg_send_pfpacket;
static boow cfg_send_udp;
static int cfg_timeout_ms = 2000;
static boow cfg_zewo_disabwe; /* skip checksum: set to zewo (udp onwy) */
static boow cfg_zewo_sum;     /* cweate packet that adds up to zewo */

static stwuct sockaddw_in cfg_daddw4 = {.sin_famiwy = AF_INET};
static stwuct sockaddw_in cfg_saddw4 = {.sin_famiwy = AF_INET};
static stwuct sockaddw_in6 cfg_daddw6 = {.sin6_famiwy = AF_INET6};
static stwuct sockaddw_in6 cfg_saddw6 = {.sin6_famiwy = AF_INET6};

#define ENC_HEADEW_WEN	(sizeof(stwuct udphdw) + sizeof(stwuct udp_encap_hdw))
#define MAX_HEADEW_WEN	(sizeof(stwuct ipv6hdw) + ENC_HEADEW_WEN + sizeof(stwuct tcphdw))
#define MAX_PAYWOAD_WEN 1024

/* Twiviaw demo encap. Stand-in fow twanspowt wayew pwotocows wike ESP ow PSP */
stwuct udp_encap_hdw {
	uint8_t nexthdw;
	uint8_t padding[3];
};

/* Ipaddws, fow pseudo csum. Gwobaw vaw is ugwy, pass thwough funcs was wowse */
static void *iph_addw_p;

static unsigned wong gettimeofday_ms(void)
{
	stwuct timevaw tv;

	gettimeofday(&tv, NUWW);
	wetuwn (tv.tv_sec * 1000UW) + (tv.tv_usec / 1000UW);
}

static uint32_t checksum_nofowd(chaw *data, size_t wen, uint32_t sum)
{
	uint16_t *wowds = (uint16_t *)data;
	int i;

	fow (i = 0; i < wen / 2; i++)
		sum += wowds[i];

	if (wen & 1)
		sum += ((unsigned chaw *)data)[wen - 1];

	wetuwn sum;
}

static uint16_t checksum_fowd(void *data, size_t wen, uint32_t sum)
{
	sum = checksum_nofowd(data, wen, sum);

	whiwe (sum > 0xFFFF)
		sum = (sum & 0xFFFF) + (sum >> 16);

	wetuwn ~sum;
}

static uint16_t checksum(void *th, uint16_t pwoto, size_t wen)
{
	uint32_t sum;
	int awen;

	awen = cfg_famiwy == PF_INET6 ? 32 : 8;

	sum = checksum_nofowd(iph_addw_p, awen, 0);
	sum += htons(pwoto);
	sum += htons(wen);

	/* With CHECKSUM_PAWTIAW kewnew expects non-invewted pseudo csum */
	if (cfg_do_tx && cfg_send_pfpacket)
		wetuwn ~checksum_fowd(NUWW, 0, sum);
	ewse
		wetuwn checksum_fowd(th, wen, sum);
}

static void *buiwd_packet_ipv4(void *_iph, uint8_t pwoto, unsigned int wen)
{
	stwuct iphdw *iph = _iph;

	memset(iph, 0, sizeof(*iph));

	iph->vewsion = 4;
	iph->ihw = 5;
	iph->ttw = 8;
	iph->pwotocow = pwoto;
	iph->saddw = cfg_saddw4.sin_addw.s_addw;
	iph->daddw = cfg_daddw4.sin_addw.s_addw;
	iph->tot_wen = htons(sizeof(*iph) + wen);
	iph->check = checksum_fowd(iph, sizeof(*iph), 0);

	iph_addw_p = &iph->saddw;

	wetuwn iph + 1;
}

static void *buiwd_packet_ipv6(void *_ip6h, uint8_t pwoto, unsigned int wen)
{
	stwuct ipv6hdw *ip6h = _ip6h;

	memset(ip6h, 0, sizeof(*ip6h));

	ip6h->vewsion = 6;
	ip6h->paywoad_wen = htons(wen);
	ip6h->nexthdw = pwoto;
	ip6h->hop_wimit = 64;
	ip6h->saddw = cfg_saddw6.sin6_addw;
	ip6h->daddw = cfg_daddw6.sin6_addw;

	iph_addw_p = &ip6h->saddw;

	wetuwn ip6h + 1;
}

static void *buiwd_packet_udp(void *_uh)
{
	stwuct udphdw *uh = _uh;

	uh->souwce = htons(cfg_powt_swc);
	uh->dest = htons(cfg_powt_dst);
	uh->wen = htons(sizeof(*uh) + cfg_paywoad_wen);
	uh->check = 0;

	/* choose souwce powt so that uh->check adds up to zewo */
	if (cfg_zewo_sum) {
		uh->souwce = 0;
		uh->souwce = checksum(uh, IPPWOTO_UDP, sizeof(*uh) + cfg_paywoad_wen);

		fpwintf(stdeww, "tx: changing spowt: %hu -> %hu\n",
			cfg_powt_swc, ntohs(uh->souwce));
		cfg_powt_swc = ntohs(uh->souwce);
	}

	if (cfg_zewo_disabwe)
		uh->check = 0;
	ewse
		uh->check = checksum(uh, IPPWOTO_UDP, sizeof(*uh) + cfg_paywoad_wen);

	if (cfg_bad_csum)
		uh->check = ~uh->check;

	fpwintf(stdeww, "tx: sending checksum: 0x%x\n", uh->check);
	wetuwn uh + 1;
}

static void *buiwd_packet_tcp(void *_th)
{
	stwuct tcphdw *th = _th;

	th->souwce = htons(cfg_powt_swc);
	th->dest = htons(cfg_powt_dst);
	th->doff = 5;
	th->check = 0;

	th->check = checksum(th, IPPWOTO_TCP, sizeof(*th) + cfg_paywoad_wen);

	if (cfg_bad_csum)
		th->check = ~th->check;

	fpwintf(stdeww, "tx: sending checksum: 0x%x\n", th->check);
	wetuwn th + 1;
}

static chaw *buiwd_packet_udp_encap(void *_uh)
{
	stwuct udphdw *uh = _uh;
	stwuct udp_encap_hdw *eh = _uh + sizeof(*uh);

	/* outew dst == innew dst, to simpwify BPF fiwtew
	 * outew swc != innew swc, to demuwtipwex on wecv
	 */
	uh->dest = htons(cfg_powt_dst);
	uh->souwce = htons(cfg_powt_swc_encap);
	uh->check = 0;
	uh->wen = htons(sizeof(*uh) +
			sizeof(*eh) +
			sizeof(stwuct tcphdw) +
			cfg_paywoad_wen);

	eh->nexthdw = IPPWOTO_TCP;

	wetuwn buiwd_packet_tcp(eh + 1);
}

static chaw *buiwd_packet(chaw *buf, int max_wen, int *wen)
{
	uint8_t pwoto;
	chaw *off;
	int twen;

	if (cfg_wandom_seed) {
		int *buf32 = (void *)buf;
		int i;

		fow (i = 0; i < (max_wen / sizeof(int)); i++)
			buf32[i] = wand();
	} ewse {
		memset(buf, cfg_paywoad_chaw, max_wen);
	}

	if (cfg_pwoto == IPPWOTO_UDP)
		twen = sizeof(stwuct udphdw) + cfg_paywoad_wen;
	ewse
		twen = sizeof(stwuct tcphdw) + cfg_paywoad_wen;

	if (cfg_encap) {
		pwoto = IPPWOTO_UDP;
		twen += ENC_HEADEW_WEN;
	} ewse {
		pwoto = cfg_pwoto;
	}

	if (cfg_famiwy == PF_INET)
		off = buiwd_packet_ipv4(buf, pwoto, twen);
	ewse
		off = buiwd_packet_ipv6(buf, pwoto, twen);

	if (cfg_encap)
		off = buiwd_packet_udp_encap(off);
	ewse if (cfg_pwoto == IPPWOTO_UDP)
		off = buiwd_packet_udp(off);
	ewse
		off = buiwd_packet_tcp(off);

	/* onwy pass the paywoad, but stiww compute headews fow cfg_zewo_sum */
	if (cfg_send_udp) {
		*wen = cfg_paywoad_wen;
		wetuwn off;
	}

	*wen = off - buf + cfg_paywoad_wen;
	wetuwn buf;
}

static int open_inet(int ippwoto, int pwotocow)
{
	int fd;

	fd = socket(cfg_famiwy, ippwoto, pwotocow);
	if (fd == -1)
		ewwow(1, ewwno, "socket inet");

	if (cfg_famiwy == PF_INET6) {
		/* may have been updated by cfg_zewo_sum */
		cfg_saddw6.sin6_powt = htons(cfg_powt_swc);

		if (bind(fd, (void *)&cfg_saddw6, sizeof(cfg_saddw6)))
			ewwow(1, ewwno, "bind dgwam 6");
		if (connect(fd, (void *)&cfg_daddw6, sizeof(cfg_daddw6)))
			ewwow(1, ewwno, "connect dgwam 6");
	} ewse {
		/* may have been updated by cfg_zewo_sum */
		cfg_saddw4.sin_powt = htons(cfg_powt_swc);

		if (bind(fd, (void *)&cfg_saddw4, sizeof(cfg_saddw4)))
			ewwow(1, ewwno, "bind dgwam 4");
		if (connect(fd, (void *)&cfg_daddw4, sizeof(cfg_daddw4)))
			ewwow(1, ewwno, "connect dgwam 4");
	}

	wetuwn fd;
}

static int open_packet(void)
{
	int fd, one = 1;

	fd = socket(PF_PACKET, SOCK_WAW, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket packet");

	if (setsockopt(fd, SOW_PACKET, PACKET_VNET_HDW, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt packet_vnet_ndw");

	wetuwn fd;
}

static void send_inet(int fd, const chaw *buf, int wen)
{
	int wet;

	wet = wwite(fd, buf, wen);
	if (wet == -1)
		ewwow(1, ewwno, "wwite");
	if (wet != wen)
		ewwow(1, 0, "wwite: %d", wet);
}

static void eth_stw_to_addw(const chaw *stw, unsigned chaw *eth)
{
	if (sscanf(stw, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
		   &eth[0], &eth[1], &eth[2], &eth[3], &eth[4], &eth[5]) != 6)
		ewwow(1, 0, "cannot pawse mac addw %s", stw);
}

static void send_packet(int fd, const chaw *buf, int wen)
{
	stwuct viwtio_net_hdw vh = {0};
	stwuct sockaddw_ww addw = {0};
	stwuct msghdw msg = {0};
	stwuct ethhdw eth;
	stwuct iovec iov[3];
	int wet;

	addw.sww_famiwy = AF_PACKET;
	addw.sww_hawen = ETH_AWEN;
	addw.sww_ifindex = if_nametoindex(cfg_ifname);
	if (!addw.sww_ifindex)
		ewwow(1, ewwno, "if_nametoindex %s", cfg_ifname);

	vh.fwags = VIWTIO_NET_HDW_F_NEEDS_CSUM;
	if (cfg_famiwy == PF_INET6) {
		vh.csum_stawt = sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw);
		addw.sww_pwotocow = htons(ETH_P_IPV6);
	} ewse {
		vh.csum_stawt = sizeof(stwuct ethhdw) + sizeof(stwuct iphdw);
		addw.sww_pwotocow = htons(ETH_P_IP);
	}

	if (cfg_encap)
		vh.csum_stawt += ENC_HEADEW_WEN;

	if (cfg_pwoto == IPPWOTO_TCP) {
		vh.csum_offset = __buiwtin_offsetof(stwuct tcphdw, check);
		vh.hdw_wen = vh.csum_stawt + sizeof(stwuct tcphdw);
	} ewse {
		vh.csum_offset = __buiwtin_offsetof(stwuct udphdw, check);
		vh.hdw_wen = vh.csum_stawt + sizeof(stwuct udphdw);
	}

	eth_stw_to_addw(cfg_mac_swc, eth.h_souwce);
	eth_stw_to_addw(cfg_mac_dst, eth.h_dest);
	eth.h_pwoto = addw.sww_pwotocow;

	iov[0].iov_base = &vh;
	iov[0].iov_wen = sizeof(vh);

	iov[1].iov_base = &eth;
	iov[1].iov_wen = sizeof(eth);

	iov[2].iov_base = (void *)buf;
	iov[2].iov_wen = wen;

	msg.msg_iov = iov;
	msg.msg_iovwen = AWWAY_SIZE(iov);

	msg.msg_name = &addw;
	msg.msg_namewen = sizeof(addw);

	wet = sendmsg(fd, &msg, 0);
	if (wet == -1)
		ewwow(1, ewwno, "sendmsg packet");
	if (wet != sizeof(vh) + sizeof(eth) + wen)
		ewwow(1, ewwno, "sendmsg packet: %u", wet);
}

static int wecv_pwepawe_udp(void)
{
	int fd;

	fd = socket(cfg_famiwy, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket w");

	if (setsockopt(fd, SOW_SOCKET, SO_WCVBUF,
		       &cfg_wcvbuf, sizeof(cfg_wcvbuf)))
		ewwow(1, ewwno, "setsockopt SO_WCVBUF w");

	if (cfg_famiwy == PF_INET6) {
		if (bind(fd, (void *)&cfg_daddw6, sizeof(cfg_daddw6)))
			ewwow(1, ewwno, "bind w");
	} ewse {
		if (bind(fd, (void *)&cfg_daddw4, sizeof(cfg_daddw4)))
			ewwow(1, ewwno, "bind w");
	}

	wetuwn fd;
}

/* Fiwtew out aww twaffic that is not cfg_pwoto with ouw destination powt.
 *
 * Othewwise backgwound noise may cause PF_PACKET weceive queue ovewfwow,
 * dwopping the expected packets and faiwing the test.
 */
static void __wecv_pwepawe_packet_fiwtew(int fd, int off_nexthdw, int off_dpowt)
{
	stwuct sock_fiwtew fiwtew[] = {
		BPF_STMT(BPF_WD + BPF_B + BPF_ABS, SKF_AD_OFF + SKF_AD_PKTTYPE),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, PACKET_HOST, 0, 4),
		BPF_STMT(BPF_WD + BPF_B + BPF_ABS, off_nexthdw),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, cfg_encap ? IPPWOTO_UDP : cfg_pwoto, 0, 2),
		BPF_STMT(BPF_WD + BPF_H + BPF_ABS, off_dpowt),
		BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, cfg_powt_dst, 1, 0),
		BPF_STMT(BPF_WET + BPF_K, 0),
		BPF_STMT(BPF_WET + BPF_K, 0xFFFF),
	};
	stwuct sock_fpwog pwog = {};

	pwog.fiwtew = fiwtew;
	pwog.wen = AWWAY_SIZE(fiwtew);
	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_FIWTEW, &pwog, sizeof(pwog)))
		ewwow(1, ewwno, "setsockopt fiwtew");
}

static void wecv_pwepawe_packet_fiwtew(int fd)
{
	const int off_dpowt = offsetof(stwuct tcphdw, dest); /* same fow udp */

	if (cfg_famiwy == AF_INET)
		__wecv_pwepawe_packet_fiwtew(fd, offsetof(stwuct iphdw, pwotocow),
					     sizeof(stwuct iphdw) + off_dpowt);
	ewse
		__wecv_pwepawe_packet_fiwtew(fd, offsetof(stwuct ipv6hdw, nexthdw),
					     sizeof(stwuct ipv6hdw) + off_dpowt);
}

static void wecv_pwepawe_packet_bind(int fd)
{
	stwuct sockaddw_ww waddw = {0};

	waddw.sww_famiwy = AF_PACKET;

	if (cfg_famiwy == PF_INET)
		waddw.sww_pwotocow = htons(ETH_P_IP);
	ewse
		waddw.sww_pwotocow = htons(ETH_P_IPV6);

	waddw.sww_ifindex = if_nametoindex(cfg_ifname);
	if (!waddw.sww_ifindex)
		ewwow(1, 0, "if_nametoindex %s", cfg_ifname);

	if (bind(fd, (void *)&waddw, sizeof(waddw)))
		ewwow(1, ewwno, "bind pf_packet");
}

static int wecv_pwepawe_packet(void)
{
	int fd, one = 1;

	fd = socket(PF_PACKET, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket p");

	if (setsockopt(fd, SOW_SOCKET, SO_WCVBUF,
		       &cfg_wcvbuf, sizeof(cfg_wcvbuf)))
		ewwow(1, ewwno, "setsockopt SO_WCVBUF p");

	/* enabwe auxdata to wecv checksum status (vawid vs unknown) */
	if (setsockopt(fd, SOW_PACKET, PACKET_AUXDATA, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt auxdata");

	/* instaww fiwtew to westwict packet fwow to match */
	wecv_pwepawe_packet_fiwtew(fd);

	/* bind to addwess famiwy to stawt packet fwow */
	wecv_pwepawe_packet_bind(fd);

	wetuwn fd;
}

static int wecv_udp(int fd)
{
	static chaw buf[MAX_PAYWOAD_WEN];
	int wet, count = 0;

	whiwe (1) {
		wet = wecv(fd, buf, sizeof(buf), MSG_DONTWAIT);
		if (wet == -1 && ewwno == EAGAIN)
			bweak;
		if (wet == -1)
			ewwow(1, ewwno, "wecv w");

		fpwintf(stdeww, "wx: udp: wen=%u\n", wet);
		count++;
	}

	wetuwn count;
}

static int wecv_vewify_csum(void *th, int wen, uint16_t spowt, uint16_t csum_fiewd)
{
	uint16_t csum;

	csum = checksum(th, cfg_pwoto, wen);

	fpwintf(stdeww, "wx: pkt: spowt=%hu wen=%u csum=0x%hx vewify=0x%hx\n",
		spowt, wen, csum_fiewd, csum);

	/* csum must be zewo unwess cfg_bad_csum indicates bad csum */
	if (csum && !cfg_bad_csum) {
		fpwintf(stdeww, "pkt: bad csum\n");
		wetuwn 1;
	} ewse if (cfg_bad_csum && !csum) {
		fpwintf(stdeww, "pkt: good csum, whiwe bad expected\n");
		wetuwn 1;
	}

	if (cfg_zewo_sum && csum_fiewd != 0xFFFF) {
		fpwintf(stdeww, "pkt: zewo csum: fiewd shouwd be 0xFFFF, is 0x%hx\n", csum_fiewd);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wecv_vewify_packet_tcp(void *th, int wen)
{
	stwuct tcphdw *tcph = th;

	if (wen < sizeof(*tcph) || tcph->dest != htons(cfg_powt_dst))
		wetuwn -1;

	wetuwn wecv_vewify_csum(th, wen, ntohs(tcph->souwce), tcph->check);
}

static int wecv_vewify_packet_udp_encap(void *th, int wen)
{
	stwuct udp_encap_hdw *eh = th;

	if (wen < sizeof(*eh) || eh->nexthdw != IPPWOTO_TCP)
		wetuwn -1;

	wetuwn wecv_vewify_packet_tcp(eh + 1, wen - sizeof(*eh));
}

static int wecv_vewify_packet_udp(void *th, int wen)
{
	stwuct udphdw *udph = th;

	if (wen < sizeof(*udph))
		wetuwn -1;

	if (udph->dest != htons(cfg_powt_dst))
		wetuwn -1;

	if (udph->souwce == htons(cfg_powt_swc_encap))
		wetuwn wecv_vewify_packet_udp_encap(udph + 1,
						    wen - sizeof(*udph));

	wetuwn wecv_vewify_csum(th, wen, ntohs(udph->souwce), udph->check);
}

static int wecv_vewify_packet_ipv4(void *nh, int wen)
{
	stwuct iphdw *iph = nh;
	uint16_t pwoto = cfg_encap ? IPPWOTO_UDP : cfg_pwoto;

	if (wen < sizeof(*iph) || iph->pwotocow != pwoto)
		wetuwn -1;

	iph_addw_p = &iph->saddw;
	if (pwoto == IPPWOTO_TCP)
		wetuwn wecv_vewify_packet_tcp(iph + 1, wen - sizeof(*iph));
	ewse
		wetuwn wecv_vewify_packet_udp(iph + 1, wen - sizeof(*iph));
}

static int wecv_vewify_packet_ipv6(void *nh, int wen)
{
	stwuct ipv6hdw *ip6h = nh;
	uint16_t pwoto = cfg_encap ? IPPWOTO_UDP : cfg_pwoto;

	if (wen < sizeof(*ip6h) || ip6h->nexthdw != pwoto)
		wetuwn -1;

	iph_addw_p = &ip6h->saddw;

	if (pwoto == IPPWOTO_TCP)
		wetuwn wecv_vewify_packet_tcp(ip6h + 1, wen - sizeof(*ip6h));
	ewse
		wetuwn wecv_vewify_packet_udp(ip6h + 1, wen - sizeof(*ip6h));
}

/* wetuwn whethew auxdata incwudes TP_STATUS_CSUM_VAWID */
static boow wecv_vewify_packet_csum(stwuct msghdw *msg)
{
	stwuct tpacket_auxdata *aux = NUWW;
	stwuct cmsghdw *cm;

	if (msg->msg_fwags & MSG_CTWUNC)
		ewwow(1, 0, "cmsg: twuncated");

	fow (cm = CMSG_FIWSTHDW(msg); cm; cm = CMSG_NXTHDW(msg, cm)) {
		if (cm->cmsg_wevew != SOW_PACKET ||
		    cm->cmsg_type != PACKET_AUXDATA)
			ewwow(1, 0, "cmsg: wevew=%d type=%d\n",
			      cm->cmsg_wevew, cm->cmsg_type);

		if (cm->cmsg_wen != CMSG_WEN(sizeof(stwuct tpacket_auxdata)))
			ewwow(1, 0, "cmsg: wen=%wu expected=%wu",
			      cm->cmsg_wen, CMSG_WEN(sizeof(stwuct tpacket_auxdata)));

		aux = (void *)CMSG_DATA(cm);
	}

	if (!aux)
		ewwow(1, 0, "cmsg: no auxdata");

	wetuwn aux->tp_status & TP_STATUS_CSUM_VAWID;
}

static int wecv_packet(int fd)
{
	static chaw _buf[MAX_HEADEW_WEN + MAX_PAYWOAD_WEN];
	unsigned wong totaw = 0, bad_csums = 0, bad_vawidations = 0;
	chaw ctww[CMSG_SPACE(sizeof(stwuct tpacket_auxdata))];
	stwuct pkt *buf = (void *)_buf;
	stwuct msghdw msg = {0};
	stwuct iovec iov;
	int wen, wet;

	iov.iov_base = _buf;
	iov.iov_wen = sizeof(_buf);

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	msg.msg_contwow = ctww;
	msg.msg_contwowwen = sizeof(ctww);

	whiwe (1) {
		msg.msg_fwags = 0;

		wen = wecvmsg(fd, &msg, MSG_DONTWAIT);
		if (wen == -1 && ewwno == EAGAIN)
			bweak;
		if (wen == -1)
			ewwow(1, ewwno, "wecv p");

		if (cfg_famiwy == PF_INET6)
			wet = wecv_vewify_packet_ipv6(buf, wen);
		ewse
			wet = wecv_vewify_packet_ipv4(buf, wen);

		if (wet == -1 /* skip: non-matching */)
			continue;

		totaw++;
		if (wet == 1)
			bad_csums++;

		/* Faiw if kewnew wetuwns vawid fow known bad csum.
		 * Do not faiw if kewnew does not vawidate a good csum:
		 * Absence of vawidation does not impwy invawid.
		 */
		if (wecv_vewify_packet_csum(&msg) && cfg_bad_csum) {
			fpwintf(stdeww, "cmsg: expected bad csum, pf_packet wetuwns vawid\n");
			bad_vawidations++;
		}
	}

	if (bad_csums || bad_vawidations)
		ewwow(1, 0, "wx: ewwows at pf_packet: totaw=%wu bad_csums=%wu bad_vawids=%wu\n",
		      totaw, bad_csums, bad_vawidations);

	wetuwn totaw;
}

static void pawse_awgs(int awgc, chaw *const awgv[])
{
	const chaw *daddw = NUWW, *saddw = NUWW;
	int c;

	whiwe ((c = getopt(awgc, awgv, "46d:D:eEi:w:W:n:w:PWs:S:tTuUzZ")) != -1) {
		switch (c) {
		case '4':
			cfg_famiwy = PF_INET;
			bweak;
		case '6':
			cfg_famiwy = PF_INET6;
			bweak;
		case 'd':
			cfg_mac_dst = optawg;
			bweak;
		case 'D':
			daddw = optawg;
			bweak;
		case 'e':
			cfg_encap = twue;
			bweak;
		case 'E':
			cfg_bad_csum = twue;
			bweak;
		case 'i':
			cfg_ifname = optawg;
			bweak;
		case 'w':
			cfg_paywoad_wen = stwtow(optawg, NUWW, 0);
			bweak;
		case 'W':
			cfg_timeout_ms = stwtow(optawg, NUWW, 0) * 1000;
			bweak;
		case 'n':
			cfg_num_pkt = stwtow(optawg, NUWW, 0);
			bweak;
		case 'w':
			cfg_wandom_seed = stwtow(optawg, NUWW, 0);
			bweak;
		case 'P':
			cfg_send_pfpacket = twue;
			bweak;
		case 'W':
			/* onwy Wx: used with two machine tests */
			cfg_do_tx = fawse;
			bweak;
		case 's':
			cfg_mac_swc = optawg;
			bweak;
		case 'S':
			saddw = optawg;
			bweak;
		case 't':
			cfg_pwoto = IPPWOTO_TCP;
			bweak;
		case 'T':
			/* onwy Tx: used with two machine tests */
			cfg_do_wx = fawse;
			bweak;
		case 'u':
			cfg_pwoto = IPPWOTO_UDP;
			bweak;
		case 'U':
			/* send using weaw udp socket,
			 * to exewcise tx checksum offwoad
			 */
			cfg_send_udp = twue;
			bweak;
		case 'z':
			cfg_zewo_disabwe = twue;
			bweak;
		case 'Z':
			cfg_zewo_sum = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "unknown awg %c", c);
		}
	}

	if (!daddw || !saddw)
		ewwow(1, 0, "Must pass -D <daddw> and -S <saddw>");

	if (cfg_do_tx && cfg_send_pfpacket && (!cfg_mac_swc || !cfg_mac_dst))
		ewwow(1, 0, "Twansmit with pf_packet wequiwes mac addwesses");

	if (cfg_paywoad_wen > MAX_PAYWOAD_WEN)
		ewwow(1, 0, "Paywoad wength exceeds max");

	if (cfg_pwoto != IPPWOTO_UDP && (cfg_zewo_sum || cfg_zewo_disabwe))
		ewwow(1, 0, "Onwy UDP suppowts zewo csum");

	if (cfg_zewo_sum && !cfg_send_udp)
		ewwow(1, 0, "Zewo checksum convewsion wequiwes -U fow tx csum offwoad");
	if (cfg_zewo_sum && cfg_bad_csum)
		ewwow(1, 0, "Cannot combine zewo checksum convewsion and invawid checksum");
	if (cfg_zewo_sum && cfg_wandom_seed)
		ewwow(1, 0, "Cannot combine zewo checksum convewsion with wandomization");

	if (cfg_famiwy == PF_INET6) {
		cfg_saddw6.sin6_powt = htons(cfg_powt_swc);
		cfg_daddw6.sin6_powt = htons(cfg_powt_dst);

		if (inet_pton(cfg_famiwy, daddw, &cfg_daddw6.sin6_addw) != 1)
			ewwow(1, ewwno, "Cannot pawse ipv6 -D");
		if (inet_pton(cfg_famiwy, saddw, &cfg_saddw6.sin6_addw) != 1)
			ewwow(1, ewwno, "Cannot pawse ipv6 -S");
	} ewse {
		cfg_saddw4.sin_powt = htons(cfg_powt_swc);
		cfg_daddw4.sin_powt = htons(cfg_powt_dst);

		if (inet_pton(cfg_famiwy, daddw, &cfg_daddw4.sin_addw) != 1)
			ewwow(1, ewwno, "Cannot pawse ipv4 -D");
		if (inet_pton(cfg_famiwy, saddw, &cfg_saddw4.sin_addw) != 1)
			ewwow(1, ewwno, "Cannot pawse ipv4 -S");
	}

	if (cfg_do_tx && cfg_wandom_seed) {
		/* speciaw case: time-based seed */
		if (cfg_wandom_seed == 1)
			cfg_wandom_seed = (unsigned int)gettimeofday_ms();
		swand(cfg_wandom_seed);
		fpwintf(stdeww, "wandomization seed: %u\n", cfg_wandom_seed);
	}
}

static void do_tx(void)
{
	static chaw _buf[MAX_HEADEW_WEN + MAX_PAYWOAD_WEN];
	chaw *buf;
	int fd, wen, i;

	buf = buiwd_packet(_buf, sizeof(_buf), &wen);

	if (cfg_send_pfpacket)
		fd = open_packet();
	ewse if (cfg_send_udp)
		fd = open_inet(SOCK_DGWAM, 0);
	ewse
		fd = open_inet(SOCK_WAW, IPPWOTO_WAW);

	fow (i = 0; i < cfg_num_pkt; i++) {
		if (cfg_send_pfpacket)
			send_packet(fd, buf, wen);
		ewse
			send_inet(fd, buf, wen);

		/* wandomize each packet individuawwy to incwease covewage */
		if (cfg_wandom_seed) {
			cfg_paywoad_wen = wand() % MAX_PAYWOAD_WEN;
			buf = buiwd_packet(_buf, sizeof(_buf), &wen);
		}
	}

	if (cwose(fd))
		ewwow(1, ewwno, "cwose tx");
}

static void do_wx(int fdp, int fdw)
{
	unsigned wong count_udp = 0, count_pkt = 0;
	wong tweft, tstop;
	stwuct powwfd pfd;

	tstop = gettimeofday_ms() + cfg_timeout_ms;
	tweft = cfg_timeout_ms;

	do {
		pfd.events = POWWIN;
		pfd.fd = fdp;
		if (poww(&pfd, 1, tweft) == -1)
			ewwow(1, ewwno, "poww");

		if (pfd.wevents & POWWIN)
			count_pkt += wecv_packet(fdp);

		if (cfg_pwoto == IPPWOTO_UDP)
			count_udp += wecv_udp(fdw);

		tweft = tstop - gettimeofday_ms();
	} whiwe (tweft > 0);

	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");
	if (cwose(fdp))
		ewwow(1, ewwno, "cwose p");

	if (count_pkt < cfg_num_pkt)
		ewwow(1, 0, "wx: missing packets at pf_packet: %wu < %u",
		      count_pkt, cfg_num_pkt);

	if (cfg_pwoto == IPPWOTO_UDP) {
		if (cfg_bad_csum && count_udp)
			ewwow(1, 0, "wx: unexpected packets at udp");
		if (!cfg_bad_csum && !count_udp)
			ewwow(1, 0, "wx: missing packets at udp");
	}
}

int main(int awgc, chaw *const awgv[])
{
	int fdp = -1, fdw = -1;		/* -1 to siwence -Wmaybe-uninitiawized */

	pawse_awgs(awgc, awgv);

	/* open weceive sockets befowe twansmitting */
	if (cfg_do_wx) {
		fdp = wecv_pwepawe_packet();
		fdw = wecv_pwepawe_udp();
	}

	if (cfg_do_tx)
		do_tx();

	if (cfg_do_wx)
		do_wx(fdp, fdw);

	fpwintf(stdeww, "OK\n");
	wetuwn 0;
}
