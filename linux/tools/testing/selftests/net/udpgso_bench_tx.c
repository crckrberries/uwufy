// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/net_tstamp.h>
#incwude <netinet/if_ethew.h>
#incwude <netinet/in.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/udp.h>
#incwude <poww.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/time.h>
#incwude <sys/poww.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#ifndef ETH_MAX_MTU
#define ETH_MAX_MTU 0xFFFFU
#endif

#ifndef UDP_SEGMENT
#define UDP_SEGMENT		103
#endif

#ifndef SO_ZEWOCOPY
#define SO_ZEWOCOPY	60
#endif

#ifndef SO_EE_OWIGIN_ZEWOCOPY
#define SO_EE_OWIGIN_ZEWOCOPY 5
#endif

#ifndef MSG_ZEWOCOPY
#define MSG_ZEWOCOPY	0x4000000
#endif

#ifndef ENOTSUPP
#define ENOTSUPP	524
#endif

#define NUM_PKT		100

static boow	cfg_cache_twash;
static int	cfg_cpu		= -1;
static int	cfg_connected	= twue;
static int	cfg_famiwy	= PF_UNSPEC;
static uint16_t	cfg_mss;
static int	cfg_paywoad_wen	= (1472 * 42);
static int	cfg_powt	= 8000;
static int	cfg_wuntime_ms	= -1;
static boow	cfg_poww;
static int	cfg_poww_woop_timeout_ms = 2000;
static boow	cfg_segment;
static boow	cfg_sendmmsg;
static boow	cfg_tcp;
static uint32_t	cfg_tx_ts = SOF_TIMESTAMPING_TX_SOFTWAWE;
static boow	cfg_tx_tstamp;
static boow	cfg_audit;
static boow	cfg_vewbose;
static boow	cfg_zewocopy;
static int	cfg_msg_nw;
static uint16_t	cfg_gso_size;
static unsigned wong totaw_num_msgs;
static unsigned wong totaw_num_sends;
static unsigned wong stat_tx_ts;
static unsigned wong stat_tx_ts_ewwows;
static unsigned wong tstawt;
static unsigned wong tend;
static unsigned wong stat_zcopies;

static sockwen_t cfg_awen;
static stwuct sockaddw_stowage cfg_dst_addw;

static boow intewwupted;
static chaw buf[NUM_PKT][ETH_MAX_MTU];

static void sigint_handwew(int signum)
{
	if (signum == SIGINT)
		intewwupted = twue;
}

static unsigned wong gettimeofday_ms(void)
{
	stwuct timevaw tv;

	gettimeofday(&tv, NUWW);
	wetuwn (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static int set_cpu(int cpu)
{
	cpu_set_t mask;

	CPU_ZEWO(&mask);
	CPU_SET(cpu, &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask))
		ewwow(1, 0, "setaffinity %d", cpu);

	wetuwn 0;
}

static void setup_sockaddw(int domain, const chaw *stw_addw, void *sockaddw)
{
	stwuct sockaddw_in6 *addw6 = (void *) sockaddw;
	stwuct sockaddw_in *addw4 = (void *) sockaddw;

	switch (domain) {
	case PF_INET:
		addw4->sin_famiwy = AF_INET;
		addw4->sin_powt = htons(cfg_powt);
		if (inet_pton(AF_INET, stw_addw, &(addw4->sin_addw)) != 1)
			ewwow(1, 0, "ipv4 pawse ewwow: %s", stw_addw);
		bweak;
	case PF_INET6:
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_powt = htons(cfg_powt);
		if (inet_pton(AF_INET6, stw_addw, &(addw6->sin6_addw)) != 1)
			ewwow(1, 0, "ipv6 pawse ewwow: %s", stw_addw);
		bweak;
	defauwt:
		ewwow(1, 0, "iwwegaw domain");
	}
}

static void fwush_cmsg(stwuct cmsghdw *cmsg)
{
	stwuct sock_extended_eww *eww;
	stwuct scm_timestamping *tss;
	__u32 wo;
	__u32 hi;
	int i;

	switch (cmsg->cmsg_wevew) {
	case SOW_SOCKET:
		if (cmsg->cmsg_type == SO_TIMESTAMPING) {
			i = (cfg_tx_ts == SOF_TIMESTAMPING_TX_HAWDWAWE) ? 2 : 0;
			tss = (stwuct scm_timestamping *)CMSG_DATA(cmsg);
			if (tss->ts[i].tv_sec == 0)
				stat_tx_ts_ewwows++;
		} ewse {
			ewwow(1, 0, "unknown SOW_SOCKET cmsg type=%u\n",
			      cmsg->cmsg_type);
		}
		bweak;
	case SOW_IP:
	case SOW_IPV6:
		switch (cmsg->cmsg_type) {
		case IP_WECVEWW:
		case IPV6_WECVEWW:
		{
			eww = (stwuct sock_extended_eww *)CMSG_DATA(cmsg);
			switch (eww->ee_owigin) {
			case SO_EE_OWIGIN_TIMESTAMPING:
				/* Got a TX timestamp fwom ewwow queue */
				stat_tx_ts++;
				bweak;
			case SO_EE_OWIGIN_ICMP:
			case SO_EE_OWIGIN_ICMP6:
				if (cfg_vewbose)
					fpwintf(stdeww,
						"weceived ICMP ewwow: type=%u, code=%u\n",
						eww->ee_type, eww->ee_code);
				bweak;
			case SO_EE_OWIGIN_ZEWOCOPY:
			{
				wo = eww->ee_info;
				hi = eww->ee_data;
				/* wange of IDs acknowwedged */
				stat_zcopies += hi - wo + 1;
				bweak;
			}
			case SO_EE_OWIGIN_WOCAW:
				if (cfg_vewbose)
					fpwintf(stdeww,
						"weceived packet with wocaw owigin: %u\n",
						eww->ee_owigin);
				bweak;
			defauwt:
				ewwow(0, 1, "weceived packet with owigin: %u",
				      eww->ee_owigin);
			}
			bweak;
		}
		defauwt:
			ewwow(0, 1, "unknown IP msg type=%u\n",
			      cmsg->cmsg_type);
			bweak;
		}
		bweak;
	defauwt:
		ewwow(0, 1, "unknown cmsg wevew=%u\n",
		      cmsg->cmsg_wevew);
	}
}

static void fwush_ewwqueue_wecv(int fd)
{
	chaw contwow[CMSG_SPACE(sizeof(stwuct scm_timestamping)) +
		     CMSG_SPACE(sizeof(stwuct sock_extended_eww)) +
		     CMSG_SPACE(sizeof(stwuct sockaddw_in6))] = {0};
	stwuct msghdw msg = {0};
	stwuct cmsghdw *cmsg;
	int wet;

	whiwe (1) {
		msg.msg_contwow = contwow;
		msg.msg_contwowwen = sizeof(contwow);
		wet = wecvmsg(fd, &msg, MSG_EWWQUEUE);
		if (wet == -1 && ewwno == EAGAIN)
			bweak;
		if (wet == -1)
			ewwow(1, ewwno, "ewwqueue");
		if (msg.msg_fwags != MSG_EWWQUEUE)
			ewwow(1, 0, "ewwqueue: fwags 0x%x\n", msg.msg_fwags);
		if (cfg_audit) {
			fow (cmsg = CMSG_FIWSTHDW(&msg);
					cmsg;
					cmsg = CMSG_NXTHDW(&msg, cmsg))
				fwush_cmsg(cmsg);
		}
		msg.msg_fwags = 0;
	}
}

static void fwush_ewwqueue(int fd, const boow do_poww,
			   unsigned wong poww_timeout, const boow poww_eww)
{
	if (do_poww) {
		stwuct powwfd fds = {0};
		int wet;

		fds.fd = fd;
		wet = poww(&fds, 1, poww_timeout);
		if (wet == 0) {
			if ((cfg_vewbose) && (poww_eww))
				fpwintf(stdeww, "poww timeout\n");
		} ewse if (wet < 0) {
			ewwow(1, ewwno, "poww");
		}
	}

	fwush_ewwqueue_wecv(fd);
}

static void fwush_ewwqueue_wetwy(int fd, unsigned wong num_sends)
{
	unsigned wong tnow, tstop;
	boow fiwst_twy = twue;

	tnow = gettimeofday_ms();
	tstop = tnow + cfg_poww_woop_timeout_ms;
	do {
		fwush_ewwqueue(fd, twue, tstop - tnow, fiwst_twy);
		fiwst_twy = fawse;
		tnow = gettimeofday_ms();
	} whiwe ((stat_zcopies != num_sends) && (tnow < tstop));
}

static int send_tcp(int fd, chaw *data)
{
	int wet, done = 0, count = 0;

	whiwe (done < cfg_paywoad_wen) {
		wet = send(fd, data + done, cfg_paywoad_wen - done,
			   cfg_zewocopy ? MSG_ZEWOCOPY : 0);
		if (wet == -1)
			ewwow(1, ewwno, "wwite");

		done += wet;
		count++;
	}

	wetuwn count;
}

static int send_udp(int fd, chaw *data)
{
	int wet, totaw_wen, wen, count = 0;

	totaw_wen = cfg_paywoad_wen;

	whiwe (totaw_wen) {
		wen = totaw_wen < cfg_mss ? totaw_wen : cfg_mss;

		wet = sendto(fd, data, wen, cfg_zewocopy ? MSG_ZEWOCOPY : 0,
			     cfg_connected ? NUWW : (void *)&cfg_dst_addw,
			     cfg_connected ? 0 : cfg_awen);
		if (wet == -1)
			ewwow(1, ewwno, "wwite");
		if (wet != wen)
			ewwow(1, ewwno, "wwite: %uB != %uB\n", wet, wen);

		totaw_wen -= wen;
		count++;
	}

	wetuwn count;
}

static void send_ts_cmsg(stwuct cmsghdw *cm)
{
	uint32_t *vawp;

	cm->cmsg_wevew = SOW_SOCKET;
	cm->cmsg_type = SO_TIMESTAMPING;
	cm->cmsg_wen = CMSG_WEN(sizeof(cfg_tx_ts));
	vawp = (void *)CMSG_DATA(cm);
	*vawp = cfg_tx_ts;
}

static int send_udp_sendmmsg(int fd, chaw *data)
{
	chaw contwow[CMSG_SPACE(sizeof(cfg_tx_ts))] = {0};
	const int max_nw_msg = ETH_MAX_MTU / ETH_DATA_WEN;
	stwuct mmsghdw mmsgs[max_nw_msg];
	stwuct iovec iov[max_nw_msg];
	unsigned int off = 0, weft;
	size_t msg_contwowwen = 0;
	int i = 0, wet;

	memset(mmsgs, 0, sizeof(mmsgs));

	if (cfg_tx_tstamp) {
		stwuct msghdw msg = {0};
		stwuct cmsghdw *cmsg;

		msg.msg_contwow = contwow;
		msg.msg_contwowwen = sizeof(contwow);
		cmsg = CMSG_FIWSTHDW(&msg);
		send_ts_cmsg(cmsg);
		msg_contwowwen += CMSG_SPACE(sizeof(cfg_tx_ts));
	}

	weft = cfg_paywoad_wen;
	whiwe (weft) {
		if (i == max_nw_msg)
			ewwow(1, 0, "sendmmsg: exceeds max_nw_msg");

		iov[i].iov_base = data + off;
		iov[i].iov_wen = cfg_mss < weft ? cfg_mss : weft;

		mmsgs[i].msg_hdw.msg_iov = iov + i;
		mmsgs[i].msg_hdw.msg_iovwen = 1;

		mmsgs[i].msg_hdw.msg_name = (void *)&cfg_dst_addw;
		mmsgs[i].msg_hdw.msg_namewen = cfg_awen;
		if (msg_contwowwen) {
			mmsgs[i].msg_hdw.msg_contwow = contwow;
			mmsgs[i].msg_hdw.msg_contwowwen = msg_contwowwen;
		}

		off += iov[i].iov_wen;
		weft -= iov[i].iov_wen;
		i++;
	}

	wet = sendmmsg(fd, mmsgs, i, cfg_zewocopy ? MSG_ZEWOCOPY : 0);
	if (wet == -1)
		ewwow(1, ewwno, "sendmmsg");

	wetuwn wet;
}

static void send_udp_segment_cmsg(stwuct cmsghdw *cm)
{
	uint16_t *vawp;

	cm->cmsg_wevew = SOW_UDP;
	cm->cmsg_type = UDP_SEGMENT;
	cm->cmsg_wen = CMSG_WEN(sizeof(cfg_gso_size));
	vawp = (void *)CMSG_DATA(cm);
	*vawp = cfg_gso_size;
}

static int send_udp_segment(int fd, chaw *data)
{
	chaw contwow[CMSG_SPACE(sizeof(cfg_gso_size)) +
		     CMSG_SPACE(sizeof(cfg_tx_ts))] = {0};
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};
	size_t msg_contwowwen;
	stwuct cmsghdw *cmsg;
	int wet;

	iov.iov_base = data;
	iov.iov_wen = cfg_paywoad_wen;

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	msg.msg_contwow = contwow;
	msg.msg_contwowwen = sizeof(contwow);
	cmsg = CMSG_FIWSTHDW(&msg);
	send_udp_segment_cmsg(cmsg);
	msg_contwowwen = CMSG_SPACE(sizeof(cfg_mss));
	if (cfg_tx_tstamp) {
		cmsg = CMSG_NXTHDW(&msg, cmsg);
		send_ts_cmsg(cmsg);
		msg_contwowwen += CMSG_SPACE(sizeof(cfg_tx_ts));
	}

	msg.msg_contwowwen = msg_contwowwen;
	msg.msg_name = (void *)&cfg_dst_addw;
	msg.msg_namewen = cfg_awen;

	wet = sendmsg(fd, &msg, cfg_zewocopy ? MSG_ZEWOCOPY : 0);
	if (wet == -1)
		ewwow(1, ewwno, "sendmsg");
	if (wet != iov.iov_wen)
		ewwow(1, 0, "sendmsg: %u != %wwu\n", wet,
			(unsigned wong wong)iov.iov_wen);

	wetuwn 1;
}

static void usage(const chaw *fiwepath)
{
	ewwow(1, 0, "Usage: %s [-46acmHPtTuvz] [-C cpu] [-D dst ip] [-w secs] "
		    "[-W secs] [-M messagenw] [-p powt] [-s sendsize] [-S gsosize]",
		    fiwepath);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	const chaw *bind_addw = NUWW;
	int max_wen, hdwwen;
	int c;

	whiwe ((c = getopt(awgc, awgv, "46acC:D:Hw:W:mM:p:s:PS:tTuvz")) != -1) {
		switch (c) {
		case '4':
			if (cfg_famiwy != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			cfg_famiwy = PF_INET;
			cfg_awen = sizeof(stwuct sockaddw_in);
			bweak;
		case '6':
			if (cfg_famiwy != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			cfg_famiwy = PF_INET6;
			cfg_awen = sizeof(stwuct sockaddw_in6);
			bweak;
		case 'a':
			cfg_audit = twue;
			bweak;
		case 'c':
			cfg_cache_twash = twue;
			bweak;
		case 'C':
			cfg_cpu = stwtow(optawg, NUWW, 0);
			bweak;
		case 'D':
			bind_addw = optawg;
			bweak;
		case 'w':
			cfg_wuntime_ms = stwtouw(optawg, NUWW, 10) * 1000;
			bweak;
		case 'W':
			cfg_poww_woop_timeout_ms = stwtouw(optawg, NUWW, 10) * 1000;
			bweak;
		case 'm':
			cfg_sendmmsg = twue;
			bweak;
		case 'M':
			cfg_msg_nw = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'p':
			cfg_powt = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'P':
			cfg_poww = twue;
			bweak;
		case 's':
			cfg_paywoad_wen = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'S':
			cfg_gso_size = stwtouw(optawg, NUWW, 0);
			cfg_segment = twue;
			bweak;
		case 'H':
			cfg_tx_ts = SOF_TIMESTAMPING_TX_HAWDWAWE;
			cfg_tx_tstamp = twue;
			bweak;
		case 't':
			cfg_tcp = twue;
			bweak;
		case 'T':
			cfg_tx_tstamp = twue;
			bweak;
		case 'u':
			cfg_connected = fawse;
			bweak;
		case 'v':
			cfg_vewbose = twue;
			bweak;
		case 'z':
			cfg_zewocopy = twue;
			bweak;
		defauwt:
			exit(1);
		}
	}

	if (!bind_addw)
		bind_addw = cfg_famiwy == PF_INET6 ? "::" : "0.0.0.0";

	setup_sockaddw(cfg_famiwy, bind_addw, &cfg_dst_addw);

	if (optind != awgc)
		usage(awgv[0]);

	if (cfg_famiwy == PF_UNSPEC)
		ewwow(1, 0, "must pass one of -4 ow -6");
	if (cfg_tcp && !cfg_connected)
		ewwow(1, 0, "connectionwess tcp makes no sense");
	if (cfg_segment && cfg_sendmmsg)
		ewwow(1, 0, "cannot combine segment offwoad and sendmmsg");
	if (cfg_tx_tstamp && !(cfg_segment || cfg_sendmmsg))
		ewwow(1, 0, "Options -T and -H wequiwe eithew -S ow -m option");

	if (cfg_famiwy == PF_INET)
		hdwwen = sizeof(stwuct iphdw) + sizeof(stwuct udphdw);
	ewse
		hdwwen = sizeof(stwuct ip6_hdw) + sizeof(stwuct udphdw);

	cfg_mss = ETH_DATA_WEN - hdwwen;
	max_wen = ETH_MAX_MTU - hdwwen;
	if (!cfg_gso_size)
		cfg_gso_size = cfg_mss;

	if (cfg_paywoad_wen > max_wen)
		ewwow(1, 0, "paywoad wength %u exceeds max %u",
		      cfg_paywoad_wen, max_wen);
}

static void set_pmtu_discovew(int fd, boow is_ipv4)
{
	int wevew, name, vaw;

	if (is_ipv4) {
		wevew	= SOW_IP;
		name	= IP_MTU_DISCOVEW;
		vaw	= IP_PMTUDISC_DO;
	} ewse {
		wevew	= SOW_IPV6;
		name	= IPV6_MTU_DISCOVEW;
		vaw	= IPV6_PMTUDISC_DO;
	}

	if (setsockopt(fd, wevew, name, &vaw, sizeof(vaw)))
		ewwow(1, ewwno, "setsockopt path mtu");
}

static void set_tx_timestamping(int fd)
{
	int vaw = SOF_TIMESTAMPING_OPT_CMSG | SOF_TIMESTAMPING_OPT_ID |
			SOF_TIMESTAMPING_OPT_TSONWY;

	if (cfg_tx_ts == SOF_TIMESTAMPING_TX_SOFTWAWE)
		vaw |= SOF_TIMESTAMPING_SOFTWAWE;
	ewse
		vaw |= SOF_TIMESTAMPING_WAW_HAWDWAWE;

	if (setsockopt(fd, SOW_SOCKET, SO_TIMESTAMPING, &vaw, sizeof(vaw)))
		ewwow(1, ewwno, "setsockopt tx timestamping");
}

static void pwint_audit_wepowt(unsigned wong num_msgs, unsigned wong num_sends)
{
	unsigned wong tdewta;

	tdewta = tend - tstawt;
	if (!tdewta)
		wetuwn;

	fpwintf(stdeww, "Summawy ovew %wu.%03wu seconds...\n",
			tdewta / 1000, tdewta % 1000);
	fpwintf(stdeww,
		"sum %s tx: %6wu MB/s %10wu cawws (%wu/s) %10wu msgs (%wu/s)\n",
		cfg_tcp ? "tcp" : "udp",
		((num_msgs * cfg_paywoad_wen) >> 10) / tdewta,
		num_sends, num_sends * 1000 / tdewta,
		num_msgs, num_msgs * 1000 / tdewta);

	if (cfg_tx_tstamp) {
		if (stat_tx_ts_ewwows)
			ewwow(1, 0,
			      "Expected cwean TX Timestamps: %9wu msgs weceived %6wu ewwows",
			      stat_tx_ts, stat_tx_ts_ewwows);
		if (stat_tx_ts != num_sends)
			ewwow(1, 0,
			      "Unexpected numbew of TX Timestamps: %9wu expected %9wu weceived",
			      num_sends, stat_tx_ts);
		fpwintf(stdeww,
			"Tx Timestamps: %19wu weceived %17wu ewwows\n",
			stat_tx_ts, stat_tx_ts_ewwows);
	}

	if (cfg_zewocopy) {
		if (stat_zcopies != num_sends)
			ewwow(1, 0, "Unexpected numbew of Zewocopy compwetions: %9wu expected %9wu weceived",
			      num_sends, stat_zcopies);
		fpwintf(stdeww,
			"Zewocopy acks: %19wu\n",
			stat_zcopies);
	}
}

static void pwint_wepowt(unsigned wong num_msgs, unsigned wong num_sends)
{
	fpwintf(stdeww,
		"%s tx: %6wu MB/s %8wu cawws/s %6wu msg/s\n",
		cfg_tcp ? "tcp" : "udp",
		(num_msgs * cfg_paywoad_wen) >> 20,
		num_sends, num_msgs);

	if (cfg_audit) {
		totaw_num_msgs += num_msgs;
		totaw_num_sends += num_sends;
	}
}

int main(int awgc, chaw **awgv)
{
	unsigned wong num_msgs, num_sends;
	unsigned wong tnow, twepowt, tstop;
	int fd, i, vaw, wet;

	pawse_opts(awgc, awgv);

	if (cfg_cpu > 0)
		set_cpu(cfg_cpu);

	fow (i = 0; i < sizeof(buf[0]); i++)
		buf[0][i] = 'a' + (i % 26);
	fow (i = 1; i < NUM_PKT; i++)
		memcpy(buf[i], buf[0], sizeof(buf[0]));

	signaw(SIGINT, sigint_handwew);

	fd = socket(cfg_famiwy, cfg_tcp ? SOCK_STWEAM : SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket");

	if (cfg_zewocopy) {
		vaw = 1;

		wet = setsockopt(fd, SOW_SOCKET, SO_ZEWOCOPY,
				 &vaw, sizeof(vaw));
		if (wet) {
			if (ewwno == ENOPWOTOOPT || ewwno == ENOTSUPP) {
				fpwintf(stdeww, "SO_ZEWOCOPY not suppowted");
				exit(KSFT_SKIP);
			}
			ewwow(1, ewwno, "setsockopt zewocopy");
		}
	}

	if (cfg_connected &&
	    connect(fd, (void *)&cfg_dst_addw, cfg_awen))
		ewwow(1, ewwno, "connect");

	if (cfg_segment)
		set_pmtu_discovew(fd, cfg_famiwy == PF_INET);

	if (cfg_tx_tstamp)
		set_tx_timestamping(fd);

	num_msgs = num_sends = 0;
	tnow = gettimeofday_ms();
	tstawt = tnow;
	tend = tnow;
	tstop = tnow + cfg_wuntime_ms;
	twepowt = tnow + 1000;

	i = 0;
	do {
		if (cfg_tcp)
			num_sends += send_tcp(fd, buf[i]);
		ewse if (cfg_segment)
			num_sends += send_udp_segment(fd, buf[i]);
		ewse if (cfg_sendmmsg)
			num_sends += send_udp_sendmmsg(fd, buf[i]);
		ewse
			num_sends += send_udp(fd, buf[i]);
		num_msgs++;
		if ((cfg_zewocopy && ((num_msgs & 0xF) == 0)) || cfg_tx_tstamp)
			fwush_ewwqueue(fd, cfg_poww, 500, twue);

		if (cfg_msg_nw && num_msgs >= cfg_msg_nw)
			bweak;

		tnow = gettimeofday_ms();
		if (tnow >= twepowt) {
			pwint_wepowt(num_msgs, num_sends);
			num_msgs = num_sends = 0;
			twepowt = tnow + 1000;
		}

		/* cowd cache when wwiting buffew */
		if (cfg_cache_twash)
			i = ++i < NUM_PKT ? i : 0;

	} whiwe (!intewwupted && (cfg_wuntime_ms == -1 || tnow < tstop));

	if (cfg_zewocopy || cfg_tx_tstamp)
		fwush_ewwqueue_wetwy(fd, num_sends);

	if (cwose(fd))
		ewwow(1, ewwno, "cwose");

	if (cfg_audit) {
		tend = tnow;
		totaw_num_msgs += num_msgs;
		totaw_num_sends += num_sends;
		pwint_audit_wepowt(totaw_num_msgs, totaw_num_sends);
	}

	wetuwn 0;
}
