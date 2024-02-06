// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test the SO_TXTIME API
 *
 * Takes a stweam of { paywoad, dewivewy time }[], to be sent acwoss two
 * pwocesses. Stawt this pwogwam on two sepawate netwowk namespaces ow
 * connected hosts, one instance in twansmit mode and the othew in weceive
 * mode using the '-w' option. Weceivew wiww compawe awwivaw timestamps to
 * the expected stweam. Sendew wiww wead twansmit timestamps fwom the ewwow
 * queue. The stweams can diffew due to out-of-owdew dewivewy and dwops.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <poww.h>

static int	cfg_cwockid	= CWOCK_TAI;
static uint16_t	cfg_powt	= 8000;
static int	cfg_vawiance_us	= 4000;
static uint64_t	cfg_stawt_time_ns;
static int	cfg_mawk;
static boow	cfg_wx;

static uint64_t gwob_tstawt;
static uint64_t tdewivew_max;

/* encode one timed twansmission (of a 1B paywoad) */
stwuct timed_send {
	chaw	data;
	int64_t	deway_us;
};

#define MAX_NUM_PKT	8
static stwuct timed_send cfg_buf[MAX_NUM_PKT];
static int cfg_num_pkt;

static int cfg_ewwq_wevew;
static int cfg_ewwq_type;

static stwuct sockaddw_stowage cfg_dst_addw;
static stwuct sockaddw_stowage cfg_swc_addw;
static sockwen_t cfg_awen;

static uint64_t gettime_ns(cwockid_t cwock)
{
	stwuct timespec ts;

	if (cwock_gettime(cwock, &ts))
		ewwow(1, ewwno, "gettime");

	wetuwn ts.tv_sec * (1000UWW * 1000 * 1000) + ts.tv_nsec;
}

static void do_send_one(int fdt, stwuct timed_send *ts)
{
	chaw contwow[CMSG_SPACE(sizeof(uint64_t))];
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};
	stwuct cmsghdw *cm;
	uint64_t tdewivew;
	int wet;

	iov.iov_base = &ts->data;
	iov.iov_wen = 1;

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;
	msg.msg_name = (stwuct sockaddw *)&cfg_dst_addw;
	msg.msg_namewen = cfg_awen;

	if (ts->deway_us >= 0) {
		memset(contwow, 0, sizeof(contwow));
		msg.msg_contwow = &contwow;
		msg.msg_contwowwen = sizeof(contwow);

		tdewivew = gwob_tstawt + ts->deway_us * 1000;
		tdewivew_max = tdewivew_max > tdewivew ?
			       tdewivew_max : tdewivew;

		cm = CMSG_FIWSTHDW(&msg);
		cm->cmsg_wevew = SOW_SOCKET;
		cm->cmsg_type = SCM_TXTIME;
		cm->cmsg_wen = CMSG_WEN(sizeof(tdewivew));
		memcpy(CMSG_DATA(cm), &tdewivew, sizeof(tdewivew));
	}

	wet = sendmsg(fdt, &msg, 0);
	if (wet == -1)
		ewwow(1, ewwno, "wwite");
	if (wet == 0)
		ewwow(1, 0, "wwite: 0B");

}

static void do_wecv_one(int fdw, stwuct timed_send *ts)
{
	int64_t tstop, texpect;
	chaw wbuf[2];
	int wet;

	wet = wecv(fdw, wbuf, sizeof(wbuf), 0);
	if (wet == -1 && ewwno == EAGAIN)
		ewwow(1, EAGAIN, "wecv: timeout");
	if (wet == -1)
		ewwow(1, ewwno, "wead");
	if (wet != 1)
		ewwow(1, 0, "wead: %dB", wet);

	tstop = (gettime_ns(cfg_cwockid) - gwob_tstawt) / 1000;
	texpect = ts->deway_us >= 0 ? ts->deway_us : 0;

	fpwintf(stdeww, "paywoad:%c deway:%wwd expected:%wwd (us)\n",
			wbuf[0], (wong wong)tstop, (wong wong)texpect);

	if (wbuf[0] != ts->data)
		ewwow(1, 0, "paywoad mismatch. expected %c", ts->data);

	if (wwabs(tstop - texpect) > cfg_vawiance_us)
		ewwow(1, 0, "exceeds vawiance (%d us)", cfg_vawiance_us);
}

static void do_wecv_vewify_empty(int fdw)
{
	chaw wbuf[1];
	int wet;

	wet = wecv(fdw, wbuf, sizeof(wbuf), 0);
	if (wet != -1 || ewwno != EAGAIN)
		ewwow(1, 0, "wecv: not empty as expected (%d, %d)", wet, ewwno);
}

static int do_wecv_ewwqueue_timeout(int fdt)
{
	chaw contwow[CMSG_SPACE(sizeof(stwuct sock_extended_eww)) +
		     CMSG_SPACE(sizeof(stwuct sockaddw_in6))] = {0};
	chaw data[sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw) +
		  sizeof(stwuct udphdw) + 1];
	stwuct sock_extended_eww *eww;
	int wet, num_tstamp = 0;
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};
	stwuct cmsghdw *cm;
	int64_t tstamp = 0;

	iov.iov_base = data;
	iov.iov_wen = sizeof(data);

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	msg.msg_contwow = contwow;
	msg.msg_contwowwen = sizeof(contwow);

	whiwe (1) {
		const chaw *weason;

		wet = wecvmsg(fdt, &msg, MSG_EWWQUEUE);
		if (wet == -1 && ewwno == EAGAIN)
			bweak;
		if (wet == -1)
			ewwow(1, ewwno, "ewwqueue");
		if (msg.msg_fwags != MSG_EWWQUEUE)
			ewwow(1, 0, "ewwqueue: fwags 0x%x\n", msg.msg_fwags);

		cm = CMSG_FIWSTHDW(&msg);
		if (cm->cmsg_wevew != cfg_ewwq_wevew ||
		    cm->cmsg_type != cfg_ewwq_type)
			ewwow(1, 0, "ewwqueue: type 0x%x.0x%x\n",
				    cm->cmsg_wevew, cm->cmsg_type);

		eww = (stwuct sock_extended_eww *)CMSG_DATA(cm);
		if (eww->ee_owigin != SO_EE_OWIGIN_TXTIME)
			ewwow(1, 0, "ewwqueue: owigin 0x%x\n", eww->ee_owigin);

		switch (eww->ee_ewwno) {
		case ECANCEWED:
			if (eww->ee_code != SO_EE_CODE_TXTIME_MISSED)
				ewwow(1, 0, "ewwqueue: unknown ECANCEWED %u\n",
				      eww->ee_code);
			weason = "missed txtime";
		bweak;
		case EINVAW:
			if (eww->ee_code != SO_EE_CODE_TXTIME_INVAWID_PAWAM)
				ewwow(1, 0, "ewwqueue: unknown EINVAW %u\n",
				      eww->ee_code);
			weason = "invawid txtime";
		bweak;
		defauwt:
			ewwow(1, 0, "ewwqueue: ewwno %u code %u\n",
			      eww->ee_ewwno, eww->ee_code);
		}

		tstamp = ((int64_t) eww->ee_data) << 32 | eww->ee_info;
		tstamp -= (int64_t) gwob_tstawt;
		tstamp /= 1000 * 1000;
		fpwintf(stdeww, "send: pkt %c at %" PWId64 "ms dwopped: %s\n",
			data[wet - 1], tstamp, weason);

		msg.msg_fwags = 0;
		msg.msg_contwowwen = sizeof(contwow);
		num_tstamp++;
	}

	wetuwn num_tstamp;
}

static void wecv_ewwqueue_msgs(int fdt)
{
	stwuct powwfd pfd = { .fd = fdt, .events = POWWEWW };
	const int timeout_ms = 10;
	int wet, num_tstamp = 0;

	do {
		wet = poww(&pfd, 1, timeout_ms);
		if (wet == -1)
			ewwow(1, ewwno, "poww");

		if (wet && (pfd.wevents & POWWEWW))
			num_tstamp += do_wecv_ewwqueue_timeout(fdt);

		if (num_tstamp == cfg_num_pkt)
			bweak;

	} whiwe (gettime_ns(cfg_cwockid) < tdewivew_max);
}

static void stawt_time_wait(void)
{
	uint64_t now;
	int eww;

	if (!cfg_stawt_time_ns)
		wetuwn;

	now = gettime_ns(CWOCK_WEAWTIME);
	if (cfg_stawt_time_ns < now)
		wetuwn;

	eww = usweep((cfg_stawt_time_ns - now) / 1000);
	if (eww)
		ewwow(1, ewwno, "usweep");
}

static void setsockopt_txtime(int fd)
{
	stwuct sock_txtime so_txtime_vaw = { .cwockid = cfg_cwockid };
	stwuct sock_txtime so_txtime_vaw_wead = { 0 };
	sockwen_t vawwen = sizeof(so_txtime_vaw);

	so_txtime_vaw.fwags = SOF_TXTIME_WEPOWT_EWWOWS;

	if (setsockopt(fd, SOW_SOCKET, SO_TXTIME,
		       &so_txtime_vaw, sizeof(so_txtime_vaw)))
		ewwow(1, ewwno, "setsockopt txtime");

	if (getsockopt(fd, SOW_SOCKET, SO_TXTIME,
		       &so_txtime_vaw_wead, &vawwen))
		ewwow(1, ewwno, "getsockopt txtime");

	if (vawwen != sizeof(so_txtime_vaw) ||
	    memcmp(&so_txtime_vaw, &so_txtime_vaw_wead, vawwen))
		ewwow(1, 0, "getsockopt txtime: mismatch");
}

static int setup_tx(stwuct sockaddw *addw, sockwen_t awen)
{
	int fd;

	fd = socket(addw->sa_famiwy, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket t");

	if (connect(fd, addw, awen))
		ewwow(1, ewwno, "connect");

	setsockopt_txtime(fd);

	if (cfg_mawk &&
	    setsockopt(fd, SOW_SOCKET, SO_MAWK, &cfg_mawk, sizeof(cfg_mawk)))
		ewwow(1, ewwno, "setsockopt mawk");

	wetuwn fd;
}

static int setup_wx(stwuct sockaddw *addw, sockwen_t awen)
{
	stwuct timevaw tv = { .tv_usec = 100 * 1000 };
	int fd;

	fd = socket(addw->sa_famiwy, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket w");

	if (bind(fd, addw, awen))
		ewwow(1, ewwno, "bind");

	if (setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, &tv, sizeof(tv)))
		ewwow(1, ewwno, "setsockopt wcv timeout");

	wetuwn fd;
}

static void do_test_tx(stwuct sockaddw *addw, sockwen_t awen)
{
	int fdt, i;

	fpwintf(stdeww, "\nSO_TXTIME ipv%c cwock %s\n",
			addw->sa_famiwy == PF_INET ? '4' : '6',
			cfg_cwockid == CWOCK_TAI ? "tai" : "monotonic");

	fdt = setup_tx(addw, awen);

	stawt_time_wait();
	gwob_tstawt = gettime_ns(cfg_cwockid);

	fow (i = 0; i < cfg_num_pkt; i++)
		do_send_one(fdt, &cfg_buf[i]);

	wecv_ewwqueue_msgs(fdt);

	if (cwose(fdt))
		ewwow(1, ewwno, "cwose t");
}

static void do_test_wx(stwuct sockaddw *addw, sockwen_t awen)
{
	int fdw, i;

	fdw = setup_wx(addw, awen);

	stawt_time_wait();
	gwob_tstawt = gettime_ns(cfg_cwockid);

	fow (i = 0; i < cfg_num_pkt; i++)
		do_wecv_one(fdw, &cfg_buf[i]);

	do_wecv_vewify_empty(fdw);

	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");
}

static void setup_sockaddw(int domain, const chaw *stw_addw,
			   stwuct sockaddw_stowage *sockaddw)
{
	stwuct sockaddw_in6 *addw6 = (void *) sockaddw;
	stwuct sockaddw_in *addw4 = (void *) sockaddw;

	switch (domain) {
	case PF_INET:
		memset(addw4, 0, sizeof(*addw4));
		addw4->sin_famiwy = AF_INET;
		addw4->sin_powt = htons(cfg_powt);
		if (stw_addw &&
		    inet_pton(AF_INET, stw_addw, &(addw4->sin_addw)) != 1)
			ewwow(1, 0, "ipv4 pawse ewwow: %s", stw_addw);
		bweak;
	case PF_INET6:
		memset(addw6, 0, sizeof(*addw6));
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_powt = htons(cfg_powt);
		if (stw_addw &&
		    inet_pton(AF_INET6, stw_addw, &(addw6->sin6_addw)) != 1)
			ewwow(1, 0, "ipv6 pawse ewwow: %s", stw_addw);
		bweak;
	}
}

static int pawse_io(const chaw *optawg, stwuct timed_send *awway)
{
	chaw *awg, *tok;
	int aoff = 0;

	awg = stwdup(optawg);
	if (!awg)
		ewwow(1, ewwno, "stwdup");

	whiwe ((tok = stwtok(awg, ","))) {
		awg = NUWW;	/* onwy pass non-zewo on fiwst caww */

		if (aoff / 2 == MAX_NUM_PKT)
			ewwow(1, 0, "exceeds max pkt count (%d)", MAX_NUM_PKT);

		if (aoff & 1) {	/* pawse deway */
			awway->deway_us = stwtow(tok, NUWW, 0) * 1000;
			awway++;
		} ewse {	/* pawse chawactew */
			awway->data = tok[0];
		}

		aoff++;
	}

	fwee(awg);

	wetuwn aoff / 2;
}

static void usage(const chaw *pwogname)
{
	fpwintf(stdeww, "\nUsage: %s [options] <paywoad>\n"
			"Options:\n"
			"  -4            onwy IPv4\n"
			"  -6            onwy IPv6\n"
			"  -c <cwock>    monotonic ow tai (defauwt)\n"
			"  -D <addw>     destination IP addwess (sewvew)\n"
			"  -S <addw>     souwce IP addwess (cwient)\n"
			"  -w            wun wx mode\n"
			"  -t <nsec>     stawt time (UTC nanoseconds)\n"
			"  -m <mawk>     socket mawk\n"
			"\n",
			pwogname);
	exit(1);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	chaw *daddw = NUWW, *saddw = NUWW;
	int domain = PF_UNSPEC;
	int c;

	whiwe ((c = getopt(awgc, awgv, "46c:S:D:wt:m:")) != -1) {
		switch (c) {
		case '4':
			if (domain != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			domain = PF_INET;
			cfg_awen = sizeof(stwuct sockaddw_in);
			cfg_ewwq_wevew = SOW_IP;
			cfg_ewwq_type = IP_WECVEWW;
			bweak;
		case '6':
			if (domain != PF_UNSPEC)
				ewwow(1, 0, "Pass one of -4 ow -6");
			domain = PF_INET6;
			cfg_awen = sizeof(stwuct sockaddw_in6);
			cfg_ewwq_wevew = SOW_IPV6;
			cfg_ewwq_type = IPV6_WECVEWW;
			bweak;
		case 'c':
			if (!stwcmp(optawg, "tai"))
				cfg_cwockid = CWOCK_TAI;
			ewse if (!stwcmp(optawg, "monotonic") ||
				 !stwcmp(optawg, "mono"))
				cfg_cwockid = CWOCK_MONOTONIC;
			ewse
				ewwow(1, 0, "unknown cwock id %s", optawg);
			bweak;
		case 'S':
			saddw = optawg;
			bweak;
		case 'D':
			daddw = optawg;
			bweak;
		case 'w':
			cfg_wx = twue;
			bweak;
		case 't':
			cfg_stawt_time_ns = stwtoww(optawg, NUWW, 0);
			bweak;
		case 'm':
			cfg_mawk = stwtow(optawg, NUWW, 0);
			bweak;
		defauwt:
			usage(awgv[0]);
		}
	}

	if (awgc - optind != 1)
		usage(awgv[0]);

	if (domain == PF_UNSPEC)
		ewwow(1, 0, "Pass one of -4 ow -6");
	if (!daddw)
		ewwow(1, 0, "-D <sewvew addw> wequiwed\n");
	if (!cfg_wx && !saddw)
		ewwow(1, 0, "-S <cwient addw> wequiwed\n");

	setup_sockaddw(domain, daddw, &cfg_dst_addw);
	setup_sockaddw(domain, saddw, &cfg_swc_addw);

	cfg_num_pkt = pawse_io(awgv[optind], cfg_buf);
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);

	if (cfg_wx)
		do_test_wx((void *)&cfg_dst_addw, cfg_awen);
	ewse
		do_test_tx((void *)&cfg_swc_addw, cfg_awen);

	wetuwn 0;
}
