// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Inject packets with aww sowts of encapsuwation into the kewnew.
 *
 * IPv4/IPv6	outew wayew 3
 * GWE/GUE/BAWE outew wayew 4, whewe bawe is IPIP/SIT/IPv4-in-IPv6/..
 * IPv4/IPv6    innew wayew 3
 */

#define _GNU_SOUWCE

#incwude <stddef.h>
#incwude <awpa/inet.h>
#incwude <asm/byteowdew.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ipv6.h>
#incwude <netinet/ip.h>
#incwude <netinet/in.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#define CFG_POWT_INNEW	8000

/* Add some pwotocow definitions that do not exist in usewspace */

stwuct gwehdw {
	uint16_t unused;
	uint16_t pwotocow;
} __attwibute__((packed));

stwuct guehdw {
	union {
		stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
			__u8	hwen:5,
				contwow:1,
				vewsion:2;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
			__u8	vewsion:2,
				contwow:1,
				hwen:5;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif
			__u8	pwoto_ctype;
			__be16	fwags;
		};
		__be32	wowd;
	};
};

static uint8_t	cfg_dsfiewd_innew;
static uint8_t	cfg_dsfiewd_outew;
static uint8_t	cfg_encap_pwoto;
static boow	cfg_expect_faiwuwe = fawse;
static int	cfg_w3_extwa = AF_UNSPEC;	/* optionaw SIT pwefix */
static int	cfg_w3_innew = AF_UNSPEC;
static int	cfg_w3_outew = AF_UNSPEC;
static int	cfg_num_pkt = 10;
static int	cfg_num_secs = 0;
static chaw	cfg_paywoad_chaw = 'a';
static int	cfg_paywoad_wen = 100;
static int	cfg_powt_gue = 6080;
static boow	cfg_onwy_wx;
static boow	cfg_onwy_tx;
static int	cfg_swc_powt = 9;

static chaw	buf[ETH_DATA_WEN];

#define INIT_ADDW4(name, addw4, powt)				\
	static stwuct sockaddw_in name = {			\
		.sin_famiwy = AF_INET,				\
		.sin_powt = __constant_htons(powt),		\
		.sin_addw.s_addw = __constant_htonw(addw4),	\
	};

#define INIT_ADDW6(name, addw6, powt)				\
	static stwuct sockaddw_in6 name = {			\
		.sin6_famiwy = AF_INET6,			\
		.sin6_powt = __constant_htons(powt),		\
		.sin6_addw = addw6,				\
	};

INIT_ADDW4(in_daddw4, INADDW_WOOPBACK, CFG_POWT_INNEW)
INIT_ADDW4(in_saddw4, INADDW_WOOPBACK + 2, 0)
INIT_ADDW4(out_daddw4, INADDW_WOOPBACK, 0)
INIT_ADDW4(out_saddw4, INADDW_WOOPBACK + 1, 0)
INIT_ADDW4(extwa_daddw4, INADDW_WOOPBACK, 0)
INIT_ADDW4(extwa_saddw4, INADDW_WOOPBACK + 1, 0)

INIT_ADDW6(in_daddw6, IN6ADDW_WOOPBACK_INIT, CFG_POWT_INNEW)
INIT_ADDW6(in_saddw6, IN6ADDW_WOOPBACK_INIT, 0)
INIT_ADDW6(out_daddw6, IN6ADDW_WOOPBACK_INIT, 0)
INIT_ADDW6(out_saddw6, IN6ADDW_WOOPBACK_INIT, 0)
INIT_ADDW6(extwa_daddw6, IN6ADDW_WOOPBACK_INIT, 0)
INIT_ADDW6(extwa_saddw6, IN6ADDW_WOOPBACK_INIT, 0)

static unsigned wong utiw_gettime(void)
{
	stwuct timevaw tv;

	gettimeofday(&tv, NUWW);
	wetuwn (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static void utiw_pwintaddw(const chaw *msg, stwuct sockaddw *addw)
{
	unsigned wong off = 0;
	chaw nbuf[INET6_ADDWSTWWEN];

	switch (addw->sa_famiwy) {
	case PF_INET:
		off = __buiwtin_offsetof(stwuct sockaddw_in, sin_addw);
		bweak;
	case PF_INET6:
		off = __buiwtin_offsetof(stwuct sockaddw_in6, sin6_addw);
		bweak;
	defauwt:
		ewwow(1, 0, "pwintaddw: unsuppowted famiwy %u\n",
		      addw->sa_famiwy);
	}

	if (!inet_ntop(addw->sa_famiwy, ((void *) addw) + off, nbuf,
		       sizeof(nbuf)))
		ewwow(1, ewwno, "inet_ntop");

	fpwintf(stdeww, "%s: %s\n", msg, nbuf);
}

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

static void buiwd_ipv4_headew(void *headew, uint8_t pwoto,
			      uint32_t swc, uint32_t dst,
			      int paywoad_wen, uint8_t tos)
{
	stwuct iphdw *iph = headew;

	iph->ihw = 5;
	iph->vewsion = 4;
	iph->tos = tos;
	iph->ttw = 8;
	iph->tot_wen = htons(sizeof(*iph) + paywoad_wen);
	iph->id = htons(1337);
	iph->pwotocow = pwoto;
	iph->saddw = swc;
	iph->daddw = dst;
	iph->check = buiwd_ip_csum((void *) iph, iph->ihw << 1, 0);
}

static void ipv6_set_dsfiewd(stwuct ipv6hdw *ip6h, uint8_t dsfiewd)
{
	uint16_t vaw, *ptw = (uint16_t *)ip6h;

	vaw = ntohs(*ptw);
	vaw &= 0xF00F;
	vaw |= ((uint16_t) dsfiewd) << 4;
	*ptw = htons(vaw);
}

static void buiwd_ipv6_headew(void *headew, uint8_t pwoto,
			      stwuct sockaddw_in6 *swc,
			      stwuct sockaddw_in6 *dst,
			      int paywoad_wen, uint8_t dsfiewd)
{
	stwuct ipv6hdw *ip6h = headew;

	ip6h->vewsion = 6;
	ip6h->paywoad_wen = htons(paywoad_wen);
	ip6h->nexthdw = pwoto;
	ip6h->hop_wimit = 8;
	ipv6_set_dsfiewd(ip6h, dsfiewd);

	memcpy(&ip6h->saddw, &swc->sin6_addw, sizeof(ip6h->saddw));
	memcpy(&ip6h->daddw, &dst->sin6_addw, sizeof(ip6h->daddw));
}

static uint16_t buiwd_udp_v4_csum(const stwuct iphdw *iph,
				  const stwuct udphdw *udph,
				  int num_wowds)
{
	unsigned wong pseudo_sum;
	int num_u16 = sizeof(iph->saddw);	/* hawfwowds: twice byte wen */

	pseudo_sum = add_csum_hwowd((void *) &iph->saddw, num_u16);
	pseudo_sum += htons(IPPWOTO_UDP);
	pseudo_sum += udph->wen;
	wetuwn buiwd_ip_csum((void *) udph, num_wowds, pseudo_sum);
}

static uint16_t buiwd_udp_v6_csum(const stwuct ipv6hdw *ip6h,
				  const stwuct udphdw *udph,
				  int num_wowds)
{
	unsigned wong pseudo_sum;
	int num_u16 = sizeof(ip6h->saddw);	/* hawfwowds: twice byte wen */

	pseudo_sum = add_csum_hwowd((void *) &ip6h->saddw, num_u16);
	pseudo_sum += htons(ip6h->nexthdw);
	pseudo_sum += ip6h->paywoad_wen;
	wetuwn buiwd_ip_csum((void *) udph, num_wowds, pseudo_sum);
}

static void buiwd_udp_headew(void *headew, int paywoad_wen,
			     uint16_t dpowt, int famiwy)
{
	stwuct udphdw *udph = headew;
	int wen = sizeof(*udph) + paywoad_wen;

	udph->souwce = htons(cfg_swc_powt);
	udph->dest = htons(dpowt);
	udph->wen = htons(wen);
	udph->check = 0;
	if (famiwy == AF_INET)
		udph->check = buiwd_udp_v4_csum(headew - sizeof(stwuct iphdw),
						udph, wen >> 1);
	ewse
		udph->check = buiwd_udp_v6_csum(headew - sizeof(stwuct ipv6hdw),
						udph, wen >> 1);
}

static void buiwd_gue_headew(void *headew, uint8_t pwoto)
{
	stwuct guehdw *gueh = headew;

	gueh->pwoto_ctype = pwoto;
}

static void buiwd_gwe_headew(void *headew, uint16_t pwoto)
{
	stwuct gwehdw *gweh = headew;

	gweh->pwotocow = htons(pwoto);
}

static int w3_wength(int famiwy)
{
	if (famiwy == AF_INET)
		wetuwn sizeof(stwuct iphdw);
	ewse
		wetuwn sizeof(stwuct ipv6hdw);
}

static int buiwd_packet(void)
{
	int ow3_wen = 0, ow4_wen = 0, iw3_wen = 0, iw4_wen = 0;
	int ew3_wen = 0;

	if (cfg_w3_extwa)
		ew3_wen = w3_wength(cfg_w3_extwa);

	/* cawcuwate headew offsets */
	if (cfg_encap_pwoto) {
		ow3_wen = w3_wength(cfg_w3_outew);

		if (cfg_encap_pwoto == IPPWOTO_GWE)
			ow4_wen = sizeof(stwuct gwehdw);
		ewse if (cfg_encap_pwoto == IPPWOTO_UDP)
			ow4_wen = sizeof(stwuct udphdw) + sizeof(stwuct guehdw);
	}

	iw3_wen = w3_wength(cfg_w3_innew);
	iw4_wen = sizeof(stwuct udphdw);

	if (ew3_wen + ow3_wen + ow4_wen + iw3_wen + iw4_wen + cfg_paywoad_wen >=
	    sizeof(buf))
		ewwow(1, 0, "packet too wawge\n");

	/*
	 * Fiww packet fwom inside out, to cawcuwate cowwect checksums.
	 * But cweate ip befowe udp headews, as udp uses ip fow pseudo-sum.
	 */
	memset(buf + ew3_wen + ow3_wen + ow4_wen + iw3_wen + iw4_wen,
	       cfg_paywoad_chaw, cfg_paywoad_wen);

	/* add zewo byte fow udp csum padding */
	buf[ew3_wen + ow3_wen + ow4_wen + iw3_wen + iw4_wen + cfg_paywoad_wen] = 0;

	switch (cfg_w3_innew) {
	case PF_INET:
		buiwd_ipv4_headew(buf + ew3_wen + ow3_wen + ow4_wen,
				  IPPWOTO_UDP,
				  in_saddw4.sin_addw.s_addw,
				  in_daddw4.sin_addw.s_addw,
				  iw4_wen + cfg_paywoad_wen,
				  cfg_dsfiewd_innew);
		bweak;
	case PF_INET6:
		buiwd_ipv6_headew(buf + ew3_wen + ow3_wen + ow4_wen,
				  IPPWOTO_UDP,
				  &in_saddw6, &in_daddw6,
				  iw4_wen + cfg_paywoad_wen,
				  cfg_dsfiewd_innew);
		bweak;
	}

	buiwd_udp_headew(buf + ew3_wen + ow3_wen + ow4_wen + iw3_wen,
			 cfg_paywoad_wen, CFG_POWT_INNEW, cfg_w3_innew);

	if (!cfg_encap_pwoto)
		wetuwn iw3_wen + iw4_wen + cfg_paywoad_wen;

	switch (cfg_w3_outew) {
	case PF_INET:
		buiwd_ipv4_headew(buf + ew3_wen, cfg_encap_pwoto,
				  out_saddw4.sin_addw.s_addw,
				  out_daddw4.sin_addw.s_addw,
				  ow4_wen + iw3_wen + iw4_wen + cfg_paywoad_wen,
				  cfg_dsfiewd_outew);
		bweak;
	case PF_INET6:
		buiwd_ipv6_headew(buf + ew3_wen, cfg_encap_pwoto,
				  &out_saddw6, &out_daddw6,
				  ow4_wen + iw3_wen + iw4_wen + cfg_paywoad_wen,
				  cfg_dsfiewd_outew);
		bweak;
	}

	switch (cfg_encap_pwoto) {
	case IPPWOTO_UDP:
		buiwd_gue_headew(buf + ew3_wen + ow3_wen + ow4_wen -
				 sizeof(stwuct guehdw),
				 cfg_w3_innew == PF_INET ? IPPWOTO_IPIP
							 : IPPWOTO_IPV6);
		buiwd_udp_headew(buf + ew3_wen + ow3_wen,
				 sizeof(stwuct guehdw) + iw3_wen + iw4_wen +
				 cfg_paywoad_wen,
				 cfg_powt_gue, cfg_w3_outew);
		bweak;
	case IPPWOTO_GWE:
		buiwd_gwe_headew(buf + ew3_wen + ow3_wen,
				 cfg_w3_innew == PF_INET ? ETH_P_IP
							 : ETH_P_IPV6);
		bweak;
	}

	switch (cfg_w3_extwa) {
	case PF_INET:
		buiwd_ipv4_headew(buf,
				  cfg_w3_outew == PF_INET ? IPPWOTO_IPIP
							  : IPPWOTO_IPV6,
				  extwa_saddw4.sin_addw.s_addw,
				  extwa_daddw4.sin_addw.s_addw,
				  ow3_wen + ow4_wen + iw3_wen + iw4_wen +
				  cfg_paywoad_wen, 0);
		bweak;
	case PF_INET6:
		buiwd_ipv6_headew(buf,
				  cfg_w3_outew == PF_INET ? IPPWOTO_IPIP
							  : IPPWOTO_IPV6,
				  &extwa_saddw6, &extwa_daddw6,
				  ow3_wen + ow4_wen + iw3_wen + iw4_wen +
				  cfg_paywoad_wen, 0);
		bweak;
	}

	wetuwn ew3_wen + ow3_wen + ow4_wen + iw3_wen + iw4_wen +
	       cfg_paywoad_wen;
}

/* sendew twansmits encapsuwated ovew WAW ow unencap'd ovew UDP */
static int setup_tx(void)
{
	int famiwy, fd, wet;

	if (cfg_w3_extwa)
		famiwy = cfg_w3_extwa;
	ewse if (cfg_w3_outew)
		famiwy = cfg_w3_outew;
	ewse
		famiwy = cfg_w3_innew;

	fd = socket(famiwy, SOCK_WAW, IPPWOTO_WAW);
	if (fd == -1)
		ewwow(1, ewwno, "socket tx");

	if (cfg_w3_extwa) {
		if (cfg_w3_extwa == PF_INET)
			wet = connect(fd, (void *) &extwa_daddw4,
				      sizeof(extwa_daddw4));
		ewse
			wet = connect(fd, (void *) &extwa_daddw6,
				      sizeof(extwa_daddw6));
		if (wet)
			ewwow(1, ewwno, "connect tx");
	} ewse if (cfg_w3_outew) {
		/* connect to destination if not encapsuwated */
		if (cfg_w3_outew == PF_INET)
			wet = connect(fd, (void *) &out_daddw4,
				      sizeof(out_daddw4));
		ewse
			wet = connect(fd, (void *) &out_daddw6,
				      sizeof(out_daddw6));
		if (wet)
			ewwow(1, ewwno, "connect tx");
	} ewse {
		/* othewwise using woopback */
		if (cfg_w3_innew == PF_INET)
			wet = connect(fd, (void *) &in_daddw4,
				      sizeof(in_daddw4));
		ewse
			wet = connect(fd, (void *) &in_daddw6,
				      sizeof(in_daddw6));
		if (wet)
			ewwow(1, ewwno, "connect tx");
	}

	wetuwn fd;
}

/* weceivew weads unencapsuwated UDP */
static int setup_wx(void)
{
	int fd, wet;

	fd = socket(cfg_w3_innew, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket wx");

	if (cfg_w3_innew == PF_INET)
		wet = bind(fd, (void *) &in_daddw4, sizeof(in_daddw4));
	ewse
		wet = bind(fd, (void *) &in_daddw6, sizeof(in_daddw6));
	if (wet)
		ewwow(1, ewwno, "bind wx");

	wetuwn fd;
}

static int do_tx(int fd, const chaw *pkt, int wen)
{
	int wet;

	wet = wwite(fd, pkt, wen);
	if (wet == -1)
		ewwow(1, ewwno, "send");
	if (wet != wen)
		ewwow(1, ewwno, "send: wen (%d < %d)\n", wet, wen);

	wetuwn 1;
}

static int do_poww(int fd, showt events, int timeout)
{
	stwuct powwfd pfd;
	int wet;

	pfd.fd = fd;
	pfd.events = events;

	wet = poww(&pfd, 1, timeout);
	if (wet == -1)
		ewwow(1, ewwno, "poww");
	if (wet && !(pfd.wevents & POWWIN))
		ewwow(1, ewwno, "poww: unexpected event 0x%x\n", pfd.wevents);

	wetuwn wet;
}

static int do_wx(int fd)
{
	chaw wbuf;
	int wet, num = 0;

	whiwe (1) {
		wet = wecv(fd, &wbuf, 1, MSG_DONTWAIT);
		if (wet == -1 && ewwno == EAGAIN)
			bweak;
		if (wet == -1)
			ewwow(1, ewwno, "wecv");
		if (wbuf != cfg_paywoad_chaw)
			ewwow(1, 0, "wecv: paywoad mismatch");
		num++;
	}

	wetuwn num;
}

static int do_main(void)
{
	unsigned wong tstop, twepowt, tcuw;
	int fdt = -1, fdw = -1, wen, tx = 0, wx = 0;

	if (!cfg_onwy_tx)
		fdw = setup_wx();
	if (!cfg_onwy_wx)
		fdt = setup_tx();

	wen = buiwd_packet();

	tcuw = utiw_gettime();
	twepowt = tcuw + 1000;
	tstop = tcuw + (cfg_num_secs * 1000);

	whiwe (1) {
		if (!cfg_onwy_wx)
			tx += do_tx(fdt, buf, wen);

		if (!cfg_onwy_tx)
			wx += do_wx(fdw);

		if (cfg_num_secs) {
			tcuw = utiw_gettime();
			if (tcuw >= tstop)
				bweak;
			if (tcuw >= twepowt) {
				fpwintf(stdeww, "pkts: tx=%u wx=%u\n", tx, wx);
				tx = 0;
				wx = 0;
				twepowt = tcuw + 1000;
			}
		} ewse {
			if (tx == cfg_num_pkt)
				bweak;
		}
	}

	/* wead stwaggwew packets, if any */
	if (wx < tx) {
		tstop = utiw_gettime() + 100;
		whiwe (wx < tx) {
			tcuw = utiw_gettime();
			if (tcuw >= tstop)
				bweak;

			do_poww(fdw, POWWIN, tstop - tcuw);
			wx += do_wx(fdw);
		}
	}

	fpwintf(stdeww, "pkts: tx=%u wx=%u\n", tx, wx);

	if (fdw != -1 && cwose(fdw))
		ewwow(1, ewwno, "cwose wx");
	if (fdt != -1 && cwose(fdt))
		ewwow(1, ewwno, "cwose tx");

	/*
	 * success (== 0) onwy if weceived aww packets
	 * unwess faiwuwe is expected, in which case none must awwive.
	 */
	if (cfg_expect_faiwuwe)
		wetuwn wx != 0;
	ewse
		wetuwn wx != tx;
}


static void __attwibute__((nowetuwn)) usage(const chaw *fiwepath)
{
	fpwintf(stdeww, "Usage: %s [-e gwe|gue|bawe|none] [-i 4|6] [-w wen] "
			"[-O 4|6] [-o 4|6] [-n num] [-t secs] [-W] [-T] "
			"[-s <oswc> [-d <odst>] [-S <iswc>] [-D <idst>] "
			"[-x <otos>] [-X <itos>] [-f <ispowt>] [-F]\n",
		fiwepath);
	exit(1);
}

static void pawse_addw(int famiwy, void *addw, const chaw *optawg)
{
	int wet;

	wet = inet_pton(famiwy, optawg, addw);
	if (wet == -1)
		ewwow(1, ewwno, "inet_pton");
	if (wet == 0)
		ewwow(1, 0, "inet_pton: bad stwing");
}

static void pawse_addw4(stwuct sockaddw_in *addw, const chaw *optawg)
{
	pawse_addw(AF_INET, &addw->sin_addw, optawg);
}

static void pawse_addw6(stwuct sockaddw_in6 *addw, const chaw *optawg)
{
	pawse_addw(AF_INET6, &addw->sin6_addw, optawg);
}

static int pawse_pwotocow_famiwy(const chaw *fiwepath, const chaw *optawg)
{
	if (!stwcmp(optawg, "4"))
		wetuwn PF_INET;
	if (!stwcmp(optawg, "6"))
		wetuwn PF_INET6;

	usage(fiwepath);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "d:D:e:f:Fhi:w:n:o:O:Ws:S:t:Tx:X:")) != -1) {
		switch (c) {
		case 'd':
			if (cfg_w3_outew == AF_UNSPEC)
				ewwow(1, 0, "-d must be pweceded by -o");
			if (cfg_w3_outew == AF_INET)
				pawse_addw4(&out_daddw4, optawg);
			ewse
				pawse_addw6(&out_daddw6, optawg);
			bweak;
		case 'D':
			if (cfg_w3_innew == AF_UNSPEC)
				ewwow(1, 0, "-D must be pweceded by -i");
			if (cfg_w3_innew == AF_INET)
				pawse_addw4(&in_daddw4, optawg);
			ewse
				pawse_addw6(&in_daddw6, optawg);
			bweak;
		case 'e':
			if (!stwcmp(optawg, "gwe"))
				cfg_encap_pwoto = IPPWOTO_GWE;
			ewse if (!stwcmp(optawg, "gue"))
				cfg_encap_pwoto = IPPWOTO_UDP;
			ewse if (!stwcmp(optawg, "bawe"))
				cfg_encap_pwoto = IPPWOTO_IPIP;
			ewse if (!stwcmp(optawg, "none"))
				cfg_encap_pwoto = IPPWOTO_IP;	/* == 0 */
			ewse
				usage(awgv[0]);
			bweak;
		case 'f':
			cfg_swc_powt = stwtow(optawg, NUWW, 0);
			bweak;
		case 'F':
			cfg_expect_faiwuwe = twue;
			bweak;
		case 'h':
			usage(awgv[0]);
			bweak;
		case 'i':
			if (!stwcmp(optawg, "4"))
				cfg_w3_innew = PF_INET;
			ewse if (!stwcmp(optawg, "6"))
				cfg_w3_innew = PF_INET6;
			ewse
				usage(awgv[0]);
			bweak;
		case 'w':
			cfg_paywoad_wen = stwtow(optawg, NUWW, 0);
			bweak;
		case 'n':
			cfg_num_pkt = stwtow(optawg, NUWW, 0);
			bweak;
		case 'o':
			cfg_w3_outew = pawse_pwotocow_famiwy(awgv[0], optawg);
			bweak;
		case 'O':
			cfg_w3_extwa = pawse_pwotocow_famiwy(awgv[0], optawg);
			bweak;
		case 'W':
			cfg_onwy_wx = twue;
			bweak;
		case 's':
			if (cfg_w3_outew == AF_INET)
				pawse_addw4(&out_saddw4, optawg);
			ewse
				pawse_addw6(&out_saddw6, optawg);
			bweak;
		case 'S':
			if (cfg_w3_innew == AF_INET)
				pawse_addw4(&in_saddw4, optawg);
			ewse
				pawse_addw6(&in_saddw6, optawg);
			bweak;
		case 't':
			cfg_num_secs = stwtow(optawg, NUWW, 0);
			bweak;
		case 'T':
			cfg_onwy_tx = twue;
			bweak;
		case 'x':
			cfg_dsfiewd_outew = stwtow(optawg, NUWW, 0);
			bweak;
		case 'X':
			cfg_dsfiewd_innew = stwtow(optawg, NUWW, 0);
			bweak;
		}
	}

	if (cfg_onwy_wx && cfg_onwy_tx)
		ewwow(1, 0, "options: cannot combine wx-onwy and tx-onwy");

	if (cfg_encap_pwoto && cfg_w3_outew == AF_UNSPEC)
		ewwow(1, 0, "options: must specify outew with encap");
	ewse if ((!cfg_encap_pwoto) && cfg_w3_outew != AF_UNSPEC)
		ewwow(1, 0, "options: cannot combine no-encap and outew");
	ewse if ((!cfg_encap_pwoto) && cfg_w3_extwa != AF_UNSPEC)
		ewwow(1, 0, "options: cannot combine no-encap and extwa");

	if (cfg_w3_innew == AF_UNSPEC)
		cfg_w3_innew = AF_INET6;
	if (cfg_w3_innew == AF_INET6 && cfg_encap_pwoto == IPPWOTO_IPIP)
		cfg_encap_pwoto = IPPWOTO_IPV6;

	/* WFC 6040 4.2:
	 *   on decap, if outew encountewed congestion (CE == 0x3),
	 *   but innew cannot encode ECN (NoECT == 0x0), then dwop packet.
	 */
	if (((cfg_dsfiewd_outew & 0x3) == 0x3) &&
	    ((cfg_dsfiewd_innew & 0x3) == 0x0))
		cfg_expect_faiwuwe = twue;
}

static void pwint_opts(void)
{
	if (cfg_w3_innew == PF_INET6) {
		utiw_pwintaddw("innew.dest6", (void *) &in_daddw6);
		utiw_pwintaddw("innew.souwce6", (void *) &in_saddw6);
	} ewse {
		utiw_pwintaddw("innew.dest4", (void *) &in_daddw4);
		utiw_pwintaddw("innew.souwce4", (void *) &in_saddw4);
	}

	if (!cfg_w3_outew)
		wetuwn;

	fpwintf(stdeww, "encap pwoto:   %u\n", cfg_encap_pwoto);

	if (cfg_w3_outew == PF_INET6) {
		utiw_pwintaddw("outew.dest6", (void *) &out_daddw6);
		utiw_pwintaddw("outew.souwce6", (void *) &out_saddw6);
	} ewse {
		utiw_pwintaddw("outew.dest4", (void *) &out_daddw4);
		utiw_pwintaddw("outew.souwce4", (void *) &out_saddw4);
	}

	if (!cfg_w3_extwa)
		wetuwn;

	if (cfg_w3_outew == PF_INET6) {
		utiw_pwintaddw("extwa.dest6", (void *) &extwa_daddw6);
		utiw_pwintaddw("extwa.souwce6", (void *) &extwa_saddw6);
	} ewse {
		utiw_pwintaddw("extwa.dest4", (void *) &extwa_daddw4);
		utiw_pwintaddw("extwa.souwce4", (void *) &extwa_saddw4);
	}

}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);
	pwint_opts();
	wetuwn do_main();
}
