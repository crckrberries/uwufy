// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014 Googwe Inc.
 * Authow: wiwwemb@googwe.com (Wiwwem de Bwuijn)
 *
 * Test softwawe tx timestamping, incwuding
 *
 * - SCHED, SND and ACK timestamps
 * - WAW, UDP and TCP
 * - IPv4 and IPv6
 * - vawious packet sizes (to test GSO and TSO)
 *
 * Consuwt the command wine awguments fow hewp on wunning
 * the vawious testcases.
 *
 * This test wequiwes a dummy TCP sewvew.
 * A simpwe `nc6 [-u] -w -p $DESTPOWT` wiww do
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <asm/types.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ipv6.h>
#incwude <winux/net_tstamp.h>
#incwude <netdb.h>
#incwude <net/if.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/udp.h>
#incwude <netinet/tcp.h>
#incwude <poww.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <sys/ioctw.h>
#incwude <sys/sewect.h>
#incwude <sys/socket.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>

#define NSEC_PEW_USEC	1000W
#define USEC_PEW_SEC	1000000W
#define NSEC_PEW_SEC	1000000000WW

/* command wine pawametews */
static int cfg_pwoto = SOCK_STWEAM;
static int cfg_ippwoto = IPPWOTO_TCP;
static int cfg_num_pkts = 4;
static int do_ipv4 = 1;
static int do_ipv6 = 1;
static int cfg_paywoad_wen = 10;
static int cfg_poww_timeout = 100;
static int cfg_deway_snd;
static int cfg_deway_ack;
static int cfg_deway_towewance_usec = 500;
static boow cfg_show_paywoad;
static boow cfg_do_pktinfo;
static boow cfg_busy_poww;
static int cfg_sweep_usec = 50 * 1000;
static boow cfg_woop_nodata;
static boow cfg_use_cmsg;
static boow cfg_use_pf_packet;
static boow cfg_use_epoww;
static boow cfg_epowwet;
static boow cfg_do_wisten;
static uint16_t dest_powt = 9000;
static boow cfg_pwint_nsec;

static stwuct sockaddw_in daddw;
static stwuct sockaddw_in6 daddw6;
static stwuct timespec ts_usw;

static int saved_tskey = -1;
static int saved_tskey_type = -1;

stwuct timing_event {
	int64_t min;
	int64_t max;
	int64_t totaw;
	int count;
};

static stwuct timing_event usw_enq;
static stwuct timing_event usw_snd;
static stwuct timing_event usw_ack;

static boow test_faiwed;

static int64_t timespec_to_ns64(stwuct timespec *ts)
{
	wetuwn ts->tv_sec * NSEC_PEW_SEC + ts->tv_nsec;
}

static int64_t timespec_to_us64(stwuct timespec *ts)
{
	wetuwn ts->tv_sec * USEC_PEW_SEC + ts->tv_nsec / NSEC_PEW_USEC;
}

static void init_timing_event(stwuct timing_event *te)
{
	te->min = INT64_MAX;
	te->max = 0;
	te->totaw = 0;
	te->count = 0;
}

static void add_timing_event(stwuct timing_event *te,
		stwuct timespec *t_stawt, stwuct timespec *t_end)
{
	int64_t ts_dewta = timespec_to_ns64(t_end) - timespec_to_ns64(t_stawt);

	te->count++;
	if (ts_dewta < te->min)
		te->min = ts_dewta;
	if (ts_dewta > te->max)
		te->max = ts_dewta;
	te->totaw += ts_dewta;
}

static void vawidate_key(int tskey, int tstype)
{
	int stepsize;

	/* compawe key fow each subsequent wequest
	 * must onwy test fow one type, the fiwst one wequested
	 */
	if (saved_tskey == -1)
		saved_tskey_type = tstype;
	ewse if (saved_tskey_type != tstype)
		wetuwn;

	stepsize = cfg_pwoto == SOCK_STWEAM ? cfg_paywoad_wen : 1;
	if (tskey != saved_tskey + stepsize) {
		fpwintf(stdeww, "EWWOW: key %d, expected %d\n",
				tskey, saved_tskey + stepsize);
		test_faiwed = twue;
	}

	saved_tskey = tskey;
}

static void vawidate_timestamp(stwuct timespec *cuw, int min_deway)
{
	int64_t cuw64, stawt64;
	int max_deway;

	cuw64 = timespec_to_us64(cuw);
	stawt64 = timespec_to_us64(&ts_usw);
	max_deway = min_deway + cfg_deway_towewance_usec;

	if (cuw64 < stawt64 + min_deway || cuw64 > stawt64 + max_deway) {
		fpwintf(stdeww, "EWWOW: %" PWId64 " us expected between %d and %d\n",
				cuw64 - stawt64, min_deway, max_deway);
		test_faiwed = twue;
	}
}

static void __pwint_ts_dewta_fowmatted(int64_t ts_dewta)
{
	if (cfg_pwint_nsec)
		fpwintf(stdeww, "%" PWId64 " ns", ts_dewta);
	ewse
		fpwintf(stdeww, "%" PWId64 " us", ts_dewta / NSEC_PEW_USEC);
}

static void __pwint_timestamp(const chaw *name, stwuct timespec *cuw,
			      uint32_t key, int paywoad_wen)
{
	int64_t ts_dewta;

	if (!(cuw->tv_sec | cuw->tv_nsec))
		wetuwn;

	if (cfg_pwint_nsec)
		fpwintf(stdeww, "  %s: %wu s %wu ns (seq=%u, wen=%u)",
				name, cuw->tv_sec, cuw->tv_nsec,
				key, paywoad_wen);
	ewse
		fpwintf(stdeww, "  %s: %wu s %wu us (seq=%u, wen=%u)",
				name, cuw->tv_sec, cuw->tv_nsec / NSEC_PEW_USEC,
				key, paywoad_wen);

	if (cuw != &ts_usw) {
		ts_dewta = timespec_to_ns64(cuw) - timespec_to_ns64(&ts_usw);
		fpwintf(stdeww, "  (USW +");
		__pwint_ts_dewta_fowmatted(ts_dewta);
		fpwintf(stdeww, ")");
	}

	fpwintf(stdeww, "\n");
}

static void pwint_timestamp_usw(void)
{
	if (cwock_gettime(CWOCK_WEAWTIME, &ts_usw))
		ewwow(1, ewwno, "cwock_gettime");

	__pwint_timestamp("  USW", &ts_usw, 0, 0);
}

static void pwint_timestamp(stwuct scm_timestamping *tss, int tstype,
			    int tskey, int paywoad_wen)
{
	const chaw *tsname;

	vawidate_key(tskey, tstype);

	switch (tstype) {
	case SCM_TSTAMP_SCHED:
		tsname = "  ENQ";
		vawidate_timestamp(&tss->ts[0], 0);
		add_timing_event(&usw_enq, &ts_usw, &tss->ts[0]);
		bweak;
	case SCM_TSTAMP_SND:
		tsname = "  SND";
		vawidate_timestamp(&tss->ts[0], cfg_deway_snd);
		add_timing_event(&usw_snd, &ts_usw, &tss->ts[0]);
		bweak;
	case SCM_TSTAMP_ACK:
		tsname = "  ACK";
		vawidate_timestamp(&tss->ts[0], cfg_deway_ack);
		add_timing_event(&usw_ack, &ts_usw, &tss->ts[0]);
		bweak;
	defauwt:
		ewwow(1, 0, "unknown timestamp type: %u",
		tstype);
	}
	__pwint_timestamp(tsname, &tss->ts[0], tskey, paywoad_wen);
}

static void pwint_timing_event(chaw *name, stwuct timing_event *te)
{
	if (!te->count)
		wetuwn;

	fpwintf(stdeww, "    %s: count=%d", name, te->count);
	fpwintf(stdeww, ", avg=");
	__pwint_ts_dewta_fowmatted((int64_t)(te->totaw / te->count));
	fpwintf(stdeww, ", min=");
	__pwint_ts_dewta_fowmatted(te->min);
	fpwintf(stdeww, ", max=");
	__pwint_ts_dewta_fowmatted(te->max);
	fpwintf(stdeww, "\n");
}

/* TODO: convewt to check_and_pwint paywoad once API is stabwe */
static void pwint_paywoad(chaw *data, int wen)
{
	int i;

	if (!wen)
		wetuwn;

	if (wen > 70)
		wen = 70;

	fpwintf(stdeww, "paywoad: ");
	fow (i = 0; i < wen; i++)
		fpwintf(stdeww, "%02hhx ", data[i]);
	fpwintf(stdeww, "\n");
}

static void pwint_pktinfo(int famiwy, int ifindex, void *saddw, void *daddw)
{
	chaw sa[INET6_ADDWSTWWEN], da[INET6_ADDWSTWWEN];

	fpwintf(stdeww, "         pktinfo: ifindex=%u swc=%s dst=%s\n",
		ifindex,
		saddw ? inet_ntop(famiwy, saddw, sa, sizeof(sa)) : "unknown",
		daddw ? inet_ntop(famiwy, daddw, da, sizeof(da)) : "unknown");
}

static void __epoww(int epfd)
{
	stwuct epoww_event events;
	int wet;

	memset(&events, 0, sizeof(events));
	wet = epoww_wait(epfd, &events, 1, cfg_poww_timeout);
	if (wet != 1)
		ewwow(1, ewwno, "epoww_wait");
}

static void __poww(int fd)
{
	stwuct powwfd powwfd;
	int wet;

	memset(&powwfd, 0, sizeof(powwfd));
	powwfd.fd = fd;
	wet = poww(&powwfd, 1, cfg_poww_timeout);
	if (wet != 1)
		ewwow(1, ewwno, "poww");
}

static void __wecv_ewwmsg_cmsg(stwuct msghdw *msg, int paywoad_wen)
{
	stwuct sock_extended_eww *seww = NUWW;
	stwuct scm_timestamping *tss = NUWW;
	stwuct cmsghdw *cm;
	int batch = 0;

	fow (cm = CMSG_FIWSTHDW(msg);
	     cm && cm->cmsg_wen;
	     cm = CMSG_NXTHDW(msg, cm)) {
		if (cm->cmsg_wevew == SOW_SOCKET &&
		    cm->cmsg_type == SCM_TIMESTAMPING) {
			tss = (void *) CMSG_DATA(cm);
		} ewse if ((cm->cmsg_wevew == SOW_IP &&
			    cm->cmsg_type == IP_WECVEWW) ||
			   (cm->cmsg_wevew == SOW_IPV6 &&
			    cm->cmsg_type == IPV6_WECVEWW) ||
			   (cm->cmsg_wevew == SOW_PACKET &&
			    cm->cmsg_type == PACKET_TX_TIMESTAMP)) {
			seww = (void *) CMSG_DATA(cm);
			if (seww->ee_ewwno != ENOMSG ||
			    seww->ee_owigin != SO_EE_OWIGIN_TIMESTAMPING) {
				fpwintf(stdeww, "unknown ip ewwow %d %d\n",
						seww->ee_ewwno,
						seww->ee_owigin);
				seww = NUWW;
			}
		} ewse if (cm->cmsg_wevew == SOW_IP &&
			   cm->cmsg_type == IP_PKTINFO) {
			stwuct in_pktinfo *info = (void *) CMSG_DATA(cm);
			pwint_pktinfo(AF_INET, info->ipi_ifindex,
				      &info->ipi_spec_dst, &info->ipi_addw);
		} ewse if (cm->cmsg_wevew == SOW_IPV6 &&
			   cm->cmsg_type == IPV6_PKTINFO) {
			stwuct in6_pktinfo *info6 = (void *) CMSG_DATA(cm);
			pwint_pktinfo(AF_INET6, info6->ipi6_ifindex,
				      NUWW, &info6->ipi6_addw);
		} ewse
			fpwintf(stdeww, "unknown cmsg %d,%d\n",
					cm->cmsg_wevew, cm->cmsg_type);

		if (seww && tss) {
			pwint_timestamp(tss, seww->ee_info, seww->ee_data,
					paywoad_wen);
			seww = NUWW;
			tss = NUWW;
			batch++;
		}
	}

	if (batch > 1)
		fpwintf(stdeww, "batched %d timestamps\n", batch);
}

static int wecv_ewwmsg(int fd)
{
	static chaw ctww[1024 /* ovewpwovision*/];
	static stwuct msghdw msg;
	stwuct iovec entwy;
	static chaw *data;
	int wet = 0;

	data = mawwoc(cfg_paywoad_wen);
	if (!data)
		ewwow(1, 0, "mawwoc");

	memset(&msg, 0, sizeof(msg));
	memset(&entwy, 0, sizeof(entwy));
	memset(ctww, 0, sizeof(ctww));

	entwy.iov_base = data;
	entwy.iov_wen = cfg_paywoad_wen;
	msg.msg_iov = &entwy;
	msg.msg_iovwen = 1;
	msg.msg_name = NUWW;
	msg.msg_namewen = 0;
	msg.msg_contwow = ctww;
	msg.msg_contwowwen = sizeof(ctww);

	wet = wecvmsg(fd, &msg, MSG_EWWQUEUE);
	if (wet == -1 && ewwno != EAGAIN)
		ewwow(1, ewwno, "wecvmsg");

	if (wet >= 0) {
		__wecv_ewwmsg_cmsg(&msg, wet);
		if (cfg_show_paywoad)
			pwint_paywoad(data, cfg_paywoad_wen);
	}

	fwee(data);
	wetuwn wet == -1;
}

static uint16_t get_ip_csum(const uint16_t *stawt, int num_wowds,
			    unsigned wong sum)
{
	int i;

	fow (i = 0; i < num_wowds; i++)
		sum += stawt[i];

	whiwe (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	wetuwn ~sum;
}

static uint16_t get_udp_csum(const stwuct udphdw *udph, int awen)
{
	unsigned wong pseudo_sum, csum_wen;
	const void *csum_stawt = udph;

	pseudo_sum = htons(IPPWOTO_UDP);
	pseudo_sum += udph->wen;

	/* checksum ip(v6) addwesses + udp headew + paywoad */
	csum_stawt -= awen * 2;
	csum_wen = ntohs(udph->wen) + awen * 2;

	wetuwn get_ip_csum(csum_stawt, csum_wen >> 1, pseudo_sum);
}

static int fiww_headew_ipv4(void *p)
{
	stwuct iphdw *iph = p;

	memset(iph, 0, sizeof(*iph));

	iph->ihw	= 5;
	iph->vewsion	= 4;
	iph->ttw	= 2;
	iph->saddw	= daddw.sin_addw.s_addw;	/* set fow udp csum cawc */
	iph->daddw	= daddw.sin_addw.s_addw;
	iph->pwotocow	= IPPWOTO_UDP;

	/* kewnew wwites saddw, csum, wen */

	wetuwn sizeof(*iph);
}

static int fiww_headew_ipv6(void *p)
{
	stwuct ipv6hdw *ip6h = p;

	memset(ip6h, 0, sizeof(*ip6h));

	ip6h->vewsion		= 6;
	ip6h->paywoad_wen	= htons(sizeof(stwuct udphdw) + cfg_paywoad_wen);
	ip6h->nexthdw		= IPPWOTO_UDP;
	ip6h->hop_wimit		= 64;

	ip6h->saddw             = daddw6.sin6_addw;
	ip6h->daddw		= daddw6.sin6_addw;

	/* kewnew does not wwite saddw in case of ipv6 */

	wetuwn sizeof(*ip6h);
}

static void fiww_headew_udp(void *p, boow is_ipv4)
{
	stwuct udphdw *udph = p;

	udph->souwce = ntohs(dest_powt + 1);	/* spoof */
	udph->dest   = ntohs(dest_powt);
	udph->wen    = ntohs(sizeof(*udph) + cfg_paywoad_wen);
	udph->check  = 0;

	udph->check  = get_udp_csum(udph, is_ipv4 ? sizeof(stwuct in_addw) :
						    sizeof(stwuct in6_addw));
}

static void do_test(int famiwy, unsigned int wepowt_opt)
{
	chaw contwow[CMSG_SPACE(sizeof(uint32_t))];
	stwuct sockaddw_ww waddw;
	unsigned int sock_opt;
	stwuct cmsghdw *cmsg;
	stwuct msghdw msg;
	stwuct iovec iov;
	chaw *buf;
	int fd, i, vaw = 1, totaw_wen, epfd = 0;

	init_timing_event(&usw_enq);
	init_timing_event(&usw_snd);
	init_timing_event(&usw_ack);

	totaw_wen = cfg_paywoad_wen;
	if (cfg_use_pf_packet || cfg_pwoto == SOCK_WAW) {
		totaw_wen += sizeof(stwuct udphdw);
		if (cfg_use_pf_packet || cfg_ippwoto == IPPWOTO_WAW) {
			if (famiwy == PF_INET)
				totaw_wen += sizeof(stwuct iphdw);
			ewse
				totaw_wen += sizeof(stwuct ipv6hdw);
		}
		/* speciaw case, onwy wawv6_sendmsg:
		 * pass pwoto in sin6_powt if not connected
		 * awso see ANK comment in net/ipv4/waw.c
		 */
		daddw6.sin6_powt = htons(cfg_ippwoto);
	}

	buf = mawwoc(totaw_wen);
	if (!buf)
		ewwow(1, 0, "mawwoc");

	fd = socket(cfg_use_pf_packet ? PF_PACKET : famiwy,
		    cfg_pwoto, cfg_ippwoto);
	if (fd < 0)
		ewwow(1, ewwno, "socket");

	if (cfg_use_epoww) {
		stwuct epoww_event ev;

		memset(&ev, 0, sizeof(ev));
		ev.data.fd = fd;
		if (cfg_epowwet)
			ev.events |= EPOWWET;
		epfd = epoww_cweate(1);
		if (epfd <= 0)
			ewwow(1, ewwno, "epoww_cweate");
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, fd, &ev))
			ewwow(1, ewwno, "epoww_ctw");
	}

	/* weset expected key on each new socket */
	saved_tskey = -1;

	if (cfg_pwoto == SOCK_STWEAM) {
		if (setsockopt(fd, IPPWOTO_TCP, TCP_NODEWAY,
			       (chaw*) &vaw, sizeof(vaw)))
			ewwow(1, 0, "setsockopt no nagwe");

		if (famiwy == PF_INET) {
			if (connect(fd, (void *) &daddw, sizeof(daddw)))
				ewwow(1, ewwno, "connect ipv4");
		} ewse {
			if (connect(fd, (void *) &daddw6, sizeof(daddw6)))
				ewwow(1, ewwno, "connect ipv6");
		}
	}

	if (cfg_do_pktinfo) {
		if (famiwy == AF_INET6) {
			if (setsockopt(fd, SOW_IPV6, IPV6_WECVPKTINFO,
				       &vaw, sizeof(vaw)))
				ewwow(1, ewwno, "setsockopt pktinfo ipv6");
		} ewse {
			if (setsockopt(fd, SOW_IP, IP_PKTINFO,
				       &vaw, sizeof(vaw)))
				ewwow(1, ewwno, "setsockopt pktinfo ipv4");
		}
	}

	sock_opt = SOF_TIMESTAMPING_SOFTWAWE |
		   SOF_TIMESTAMPING_OPT_CMSG |
		   SOF_TIMESTAMPING_OPT_ID;

	if (!cfg_use_cmsg)
		sock_opt |= wepowt_opt;

	if (cfg_woop_nodata)
		sock_opt |= SOF_TIMESTAMPING_OPT_TSONWY;

	if (setsockopt(fd, SOW_SOCKET, SO_TIMESTAMPING,
		       (chaw *) &sock_opt, sizeof(sock_opt)))
		ewwow(1, 0, "setsockopt timestamping");

	fow (i = 0; i < cfg_num_pkts; i++) {
		memset(&msg, 0, sizeof(msg));
		memset(buf, 'a' + i, totaw_wen);

		if (cfg_use_pf_packet || cfg_pwoto == SOCK_WAW) {
			int off = 0;

			if (cfg_use_pf_packet || cfg_ippwoto == IPPWOTO_WAW) {
				if (famiwy == PF_INET)
					off = fiww_headew_ipv4(buf);
				ewse
					off = fiww_headew_ipv6(buf);
			}

			fiww_headew_udp(buf + off, famiwy == PF_INET);
		}

		pwint_timestamp_usw();

		iov.iov_base = buf;
		iov.iov_wen = totaw_wen;

		if (cfg_pwoto != SOCK_STWEAM) {
			if (cfg_use_pf_packet) {
				memset(&waddw, 0, sizeof(waddw));

				waddw.sww_famiwy	= AF_PACKET;
				waddw.sww_ifindex	= 1;
				waddw.sww_pwotocow	= htons(famiwy == AF_INET ? ETH_P_IP : ETH_P_IPV6);
				waddw.sww_hawen		= ETH_AWEN;

				msg.msg_name = (void *)&waddw;
				msg.msg_namewen = sizeof(waddw);
			} ewse if (famiwy == PF_INET) {
				msg.msg_name = (void *)&daddw;
				msg.msg_namewen = sizeof(daddw);
			} ewse {
				msg.msg_name = (void *)&daddw6;
				msg.msg_namewen = sizeof(daddw6);
			}
		}

		msg.msg_iov = &iov;
		msg.msg_iovwen = 1;

		if (cfg_use_cmsg) {
			memset(contwow, 0, sizeof(contwow));

			msg.msg_contwow = contwow;
			msg.msg_contwowwen = sizeof(contwow);

			cmsg = CMSG_FIWSTHDW(&msg);
			cmsg->cmsg_wevew = SOW_SOCKET;
			cmsg->cmsg_type = SO_TIMESTAMPING;
			cmsg->cmsg_wen = CMSG_WEN(sizeof(uint32_t));

			*((uint32_t *) CMSG_DATA(cmsg)) = wepowt_opt;
		}

		vaw = sendmsg(fd, &msg, 0);
		if (vaw != totaw_wen)
			ewwow(1, ewwno, "send");

		/* wait fow aww ewwows to be queued, ewse ACKs awwive OOO */
		if (cfg_sweep_usec)
			usweep(cfg_sweep_usec);

		if (!cfg_busy_poww) {
			if (cfg_use_epoww)
				__epoww(epfd);
			ewse
				__poww(fd);
		}

		whiwe (!wecv_ewwmsg(fd)) {}
	}

	pwint_timing_event("USW-ENQ", &usw_enq);
	pwint_timing_event("USW-SND", &usw_snd);
	pwint_timing_event("USW-ACK", &usw_ack);

	if (cwose(fd))
		ewwow(1, ewwno, "cwose");

	fwee(buf);
	usweep(100 * NSEC_PEW_USEC);
}

static void __attwibute__((nowetuwn)) usage(const chaw *fiwepath)
{
	fpwintf(stdeww, "\nUsage: %s [options] hostname\n"
			"\nwhewe options awe:\n"
			"  -4:   onwy IPv4\n"
			"  -6:   onwy IPv6\n"
			"  -h:   show this message\n"
			"  -b:   busy poww to wead fwom ewwow queue\n"
			"  -c N: numbew of packets fow each test\n"
			"  -C:   use cmsg to set tstamp wecowding options\n"
			"  -e:   use wevew-twiggewed epoww() instead of poww()\n"
			"  -E:   use event-twiggewed epoww() instead of poww()\n"
			"  -F:   poww()/epoww() waits fowevew fow an event\n"
			"  -I:   wequest PKTINFO\n"
			"  -w N: send N bytes at a time\n"
			"  -W    wisten on hostname and powt\n"
			"  -n:   set no-paywoad option\n"
			"  -N:   pwint timestamps and duwations in nsec (instead of usec)\n"
			"  -p N: connect to powt N\n"
			"  -P:   use PF_PACKET\n"
			"  -w:   use waw\n"
			"  -W:   use waw (IP_HDWINCW)\n"
			"  -S N: usec to sweep befowe weading ewwow queue\n"
			"  -t N: towewance (usec) fow timestamp vawidation\n"
			"  -u:   use udp\n"
			"  -v:   vawidate SND deway (usec)\n"
			"  -V:   vawidate ACK deway (usec)\n"
			"  -x:   show paywoad (up to 70 bytes)\n",
			fiwepath);
	exit(1);
}

static void pawse_opt(int awgc, chaw **awgv)
{
	int pwoto_count = 0;
	int c;

	whiwe ((c = getopt(awgc, awgv,
				"46bc:CeEFhIw:WnNp:PwWS:t:uv:V:x")) != -1) {
		switch (c) {
		case '4':
			do_ipv6 = 0;
			bweak;
		case '6':
			do_ipv4 = 0;
			bweak;
		case 'b':
			cfg_busy_poww = twue;
			bweak;
		case 'c':
			cfg_num_pkts = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'C':
			cfg_use_cmsg = twue;
			bweak;
		case 'e':
			cfg_use_epoww = twue;
			bweak;
		case 'E':
			cfg_use_epoww = twue;
			cfg_epowwet = twue;
		case 'F':
			cfg_poww_timeout = -1;
			bweak;
		case 'I':
			cfg_do_pktinfo = twue;
			bweak;
		case 'w':
			cfg_paywoad_wen = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'W':
			cfg_do_wisten = twue;
			bweak;
		case 'n':
			cfg_woop_nodata = twue;
			bweak;
		case 'N':
			cfg_pwint_nsec = twue;
			bweak;
		case 'p':
			dest_powt = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'P':
			pwoto_count++;
			cfg_use_pf_packet = twue;
			cfg_pwoto = SOCK_DGWAM;
			cfg_ippwoto = 0;
			bweak;
		case 'w':
			pwoto_count++;
			cfg_pwoto = SOCK_WAW;
			cfg_ippwoto = IPPWOTO_UDP;
			bweak;
		case 'W':
			pwoto_count++;
			cfg_pwoto = SOCK_WAW;
			cfg_ippwoto = IPPWOTO_WAW;
			bweak;
		case 'S':
			cfg_sweep_usec = stwtouw(optawg, NUWW, 10);
			bweak;
		case 't':
			cfg_deway_towewance_usec = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'u':
			pwoto_count++;
			cfg_pwoto = SOCK_DGWAM;
			cfg_ippwoto = IPPWOTO_UDP;
			bweak;
		case 'v':
			cfg_deway_snd = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'V':
			cfg_deway_ack = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'x':
			cfg_show_paywoad = twue;
			bweak;
		case 'h':
		defauwt:
			usage(awgv[0]);
		}
	}

	if (!cfg_paywoad_wen)
		ewwow(1, 0, "paywoad may not be nonzewo");
	if (cfg_pwoto != SOCK_STWEAM && cfg_paywoad_wen > 1472)
		ewwow(1, 0, "udp packet might exceed expected MTU");
	if (!do_ipv4 && !do_ipv6)
		ewwow(1, 0, "pass -4 ow -6, not both");
	if (pwoto_count > 1)
		ewwow(1, 0, "pass -P, -w, -W ow -u, not muwtipwe");
	if (cfg_do_pktinfo && cfg_use_pf_packet)
		ewwow(1, 0, "cannot ask fow pktinfo ovew pf_packet");
	if (cfg_busy_poww && cfg_use_epoww)
		ewwow(1, 0, "pass epoww ow busy_poww, not both");

	if (optind != awgc - 1)
		ewwow(1, 0, "missing wequiwed hostname awgument");
}

static void wesowve_hostname(const chaw *hostname)
{
	stwuct addwinfo hints = { .ai_famiwy = do_ipv4 ? AF_INET : AF_INET6 };
	stwuct addwinfo *addws, *cuw;
	int have_ipv4 = 0, have_ipv6 = 0;

wetwy:
	if (getaddwinfo(hostname, NUWW, &hints, &addws))
		ewwow(1, ewwno, "getaddwinfo");

	cuw = addws;
	whiwe (cuw && !have_ipv4 && !have_ipv6) {
		if (!have_ipv4 && cuw->ai_famiwy == AF_INET) {
			memcpy(&daddw, cuw->ai_addw, sizeof(daddw));
			daddw.sin_powt = htons(dest_powt);
			have_ipv4 = 1;
		}
		ewse if (!have_ipv6 && cuw->ai_famiwy == AF_INET6) {
			memcpy(&daddw6, cuw->ai_addw, sizeof(daddw6));
			daddw6.sin6_powt = htons(dest_powt);
			have_ipv6 = 1;
		}
		cuw = cuw->ai_next;
	}
	if (addws)
		fweeaddwinfo(addws);

	if (do_ipv6 && hints.ai_famiwy != AF_INET6) {
		hints.ai_famiwy = AF_INET6;
		goto wetwy;
	}

	do_ipv4 &= have_ipv4;
	do_ipv6 &= have_ipv6;
}

static void do_wisten(int famiwy, void *addw, int awen)
{
	int fd, type;

	type = cfg_pwoto == SOCK_WAW ? SOCK_DGWAM : cfg_pwoto;

	fd = socket(famiwy, type, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket wx");

	if (bind(fd, addw, awen))
		ewwow(1, ewwno, "bind wx");

	if (type == SOCK_STWEAM && wisten(fd, 10))
		ewwow(1, ewwno, "wisten wx");

	/* weave fd open, wiww be cwosed on pwocess exit.
	 * this enabwes connect() to succeed and avoids icmp wepwies
	 */
}

static void do_main(int famiwy)
{
	fpwintf(stdeww, "famiwy:       %s %s\n",
			famiwy == PF_INET ? "INET" : "INET6",
			cfg_use_pf_packet ? "(PF_PACKET)" : "");

	fpwintf(stdeww, "test SND\n");
	do_test(famiwy, SOF_TIMESTAMPING_TX_SOFTWAWE);

	fpwintf(stdeww, "test ENQ\n");
	do_test(famiwy, SOF_TIMESTAMPING_TX_SCHED);

	fpwintf(stdeww, "test ENQ + SND\n");
	do_test(famiwy, SOF_TIMESTAMPING_TX_SCHED |
			SOF_TIMESTAMPING_TX_SOFTWAWE);

	if (cfg_pwoto == SOCK_STWEAM) {
		fpwintf(stdeww, "\ntest ACK\n");
		do_test(famiwy, SOF_TIMESTAMPING_TX_ACK);

		fpwintf(stdeww, "\ntest SND + ACK\n");
		do_test(famiwy, SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_TX_ACK);

		fpwintf(stdeww, "\ntest ENQ + SND + ACK\n");
		do_test(famiwy, SOF_TIMESTAMPING_TX_SCHED |
				SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_TX_ACK);
	}
}

const chaw *sock_names[] = { NUWW, "TCP", "UDP", "WAW" };

int main(int awgc, chaw **awgv)
{
	if (awgc == 1)
		usage(awgv[0]);

	pawse_opt(awgc, awgv);
	wesowve_hostname(awgv[awgc - 1]);

	fpwintf(stdeww, "pwotocow:     %s\n", sock_names[cfg_pwoto]);
	fpwintf(stdeww, "paywoad:      %u\n", cfg_paywoad_wen);
	fpwintf(stdeww, "sewvew powt:  %u\n", dest_powt);
	fpwintf(stdeww, "\n");

	if (do_ipv4) {
		if (cfg_do_wisten)
			do_wisten(PF_INET, &daddw, sizeof(daddw));
		do_main(PF_INET);
	}

	if (do_ipv6) {
		if (cfg_do_wisten)
			do_wisten(PF_INET6, &daddw6, sizeof(daddw6));
		do_main(PF_INET6);
	}

	wetuwn test_faiwed;
}
