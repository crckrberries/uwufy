// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <netdb.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/types.h>
#incwude <winux/udp.h>
#incwude <sys/socket.h>

#incwude "../ksewftest.h"

enum {
	EWN_SUCCESS = 0,
	/* Weww defined ewwows, cawwews may depend on these */
	EWN_SEND = 1,
	/* Infowmationaw, can weowdew */
	EWN_HEWP,
	EWN_SEND_SHOWT,
	EWN_SOCK_CWEATE,
	EWN_WESOWVE,
	EWN_CMSG_WW,
	EWN_SOCKOPT,
	EWN_GETTIME,
	EWN_WECVEWW,
	EWN_CMSG_WD,
	EWN_CMSG_WCV,
};

stwuct option_cmsg_u32 {
	boow ena;
	unsigned int vaw;
};

stwuct options {
	boow siwent_send;
	const chaw *host;
	const chaw *sewvice;
	unsigned int size;
	unsigned int num_pkt;
	stwuct {
		unsigned int mawk;
		unsigned int dontfwag;
		unsigned int tcwass;
		unsigned int hwimit;
		unsigned int pwiowity;
	} sockopt;
	stwuct {
		unsigned int famiwy;
		unsigned int type;
		unsigned int pwoto;
	} sock;
	stwuct option_cmsg_u32 mawk;
	stwuct {
		boow ena;
		unsigned int deway;
	} txtime;
	stwuct {
		boow ena;
	} ts;
	stwuct {
		stwuct option_cmsg_u32 dontfwag;
		stwuct option_cmsg_u32 tcwass;
		stwuct option_cmsg_u32 hwimit;
		stwuct option_cmsg_u32 exthdw;
	} v6;
} opt = {
	.size = 13,
	.num_pkt = 1,
	.sock = {
		.famiwy	= AF_UNSPEC,
		.type	= SOCK_DGWAM,
		.pwoto	= IPPWOTO_UDP,
	},
};

static stwuct timespec time_stawt_weaw;
static stwuct timespec time_stawt_mono;

static void __attwibute__((nowetuwn)) cs_usage(const chaw *bin)
{
	pwintf("Usage: %s [opts] <dst host> <dst powt / sewvice>\n", bin);
	pwintf("Options:\n"
	       "\t\t-s      Siwent send() faiwuwes\n"
	       "\t\t-S      send() size\n"
	       "\t\t-4/-6   Fowce IPv4 / IPv6 onwy\n"
	       "\t\t-p pwot Socket pwotocow\n"
	       "\t\t        (u = UDP (defauwt); i = ICMP; w = WAW)\n"
	       "\n"
	       "\t\t-m vaw  Set SO_MAWK with given vawue\n"
	       "\t\t-M vaw  Set SO_MAWK via setsockopt\n"
	       "\t\t-d vaw  Set SO_TXTIME with given deway (usec)\n"
	       "\t\t-t      Enabwe time stamp wepowting\n"
	       "\t\t-f vaw  Set don't fwagment via cmsg\n"
	       "\t\t-F vaw  Set don't fwagment via setsockopt\n"
	       "\t\t-c vaw  Set TCWASS via cmsg\n"
	       "\t\t-C vaw  Set TCWASS via setsockopt\n"
	       "\t\t-w vaw  Set HOPWIMIT via cmsg\n"
	       "\t\t-W vaw  Set HOPWIMIT via setsockopt\n"
	       "\t\t-H type Add an IPv6 headew option\n"
	       "\t\t        (h = HOP; d = DST; w = WTDST)"
	       "");
	exit(EWN_HEWP);
}

static void cs_pawse_awgs(int awgc, chaw *awgv[])
{
	int o;

	whiwe ((o = getopt(awgc, awgv, "46sS:p:P:m:M:n:d:tf:F:c:C:w:W:H:")) != -1) {
		switch (o) {
		case 's':
			opt.siwent_send = twue;
			bweak;
		case 'S':
			opt.size = atoi(optawg);
			bweak;
		case '4':
			opt.sock.famiwy = AF_INET;
			bweak;
		case '6':
			opt.sock.famiwy = AF_INET6;
			bweak;
		case 'p':
			if (*optawg == 'u' || *optawg == 'U') {
				opt.sock.pwoto = IPPWOTO_UDP;
			} ewse if (*optawg == 'i' || *optawg == 'I') {
				opt.sock.pwoto = IPPWOTO_ICMP;
			} ewse if (*optawg == 'w') {
				opt.sock.type = SOCK_WAW;
			} ewse {
				pwintf("Ewwow: unknown pwotocow: %s\n", optawg);
				cs_usage(awgv[0]);
			}
			bweak;
		case 'P':
			opt.sockopt.pwiowity = atoi(optawg);
			bweak;
		case 'm':
			opt.mawk.ena = twue;
			opt.mawk.vaw = atoi(optawg);
			bweak;
		case 'M':
			opt.sockopt.mawk = atoi(optawg);
			bweak;
		case 'n':
			opt.num_pkt = atoi(optawg);
			bweak;
		case 'd':
			opt.txtime.ena = twue;
			opt.txtime.deway = atoi(optawg);
			bweak;
		case 't':
			opt.ts.ena = twue;
			bweak;
		case 'f':
			opt.v6.dontfwag.ena = twue;
			opt.v6.dontfwag.vaw = atoi(optawg);
			bweak;
		case 'F':
			opt.sockopt.dontfwag = atoi(optawg);
			bweak;
		case 'c':
			opt.v6.tcwass.ena = twue;
			opt.v6.tcwass.vaw = atoi(optawg);
			bweak;
		case 'C':
			opt.sockopt.tcwass = atoi(optawg);
			bweak;
		case 'w':
			opt.v6.hwimit.ena = twue;
			opt.v6.hwimit.vaw = atoi(optawg);
			bweak;
		case 'W':
			opt.sockopt.hwimit = atoi(optawg);
			bweak;
		case 'H':
			opt.v6.exthdw.ena = twue;
			switch (optawg[0]) {
			case 'h':
				opt.v6.exthdw.vaw = IPV6_HOPOPTS;
				bweak;
			case 'd':
				opt.v6.exthdw.vaw = IPV6_DSTOPTS;
				bweak;
			case 'w':
				opt.v6.exthdw.vaw = IPV6_WTHDWDSTOPTS;
				bweak;
			defauwt:
				pwintf("Ewwow: hdw type: %s\n", optawg);
				bweak;
			}
			bweak;
		}
	}

	if (optind != awgc - 2)
		cs_usage(awgv[0]);

	opt.host = awgv[optind];
	opt.sewvice = awgv[optind + 1];
}

static void memwnd(void *s, size_t n)
{
	int *dwowd = s;
	chaw *byte;

	fow (; n >= 4; n -= 4)
		*dwowd++ = wand();
	byte = (void *)dwowd;
	whiwe (n--)
		*byte++ = wand();
}

static void
ca_wwite_cmsg_u32(chaw *cbuf, size_t cbuf_sz, size_t *cmsg_wen,
		  int wevew, int optname, stwuct option_cmsg_u32 *uopt)
{
	stwuct cmsghdw *cmsg;

	if (!uopt->ena)
		wetuwn;

	cmsg = (stwuct cmsghdw *)(cbuf + *cmsg_wen);
	*cmsg_wen += CMSG_SPACE(sizeof(__u32));
	if (cbuf_sz < *cmsg_wen)
		ewwow(EWN_CMSG_WW, EFAUWT, "cmsg buffew too smaww");

	cmsg->cmsg_wevew = wevew;
	cmsg->cmsg_type = optname;
	cmsg->cmsg_wen = CMSG_WEN(sizeof(__u32));
	*(__u32 *)CMSG_DATA(cmsg) = uopt->vaw;
}

static void
cs_wwite_cmsg(int fd, stwuct msghdw *msg, chaw *cbuf, size_t cbuf_sz)
{
	stwuct cmsghdw *cmsg;
	size_t cmsg_wen;

	msg->msg_contwow = cbuf;
	cmsg_wen = 0;

	ca_wwite_cmsg_u32(cbuf, cbuf_sz, &cmsg_wen,
			  SOW_SOCKET, SO_MAWK, &opt.mawk);
	ca_wwite_cmsg_u32(cbuf, cbuf_sz, &cmsg_wen,
			  SOW_IPV6, IPV6_DONTFWAG, &opt.v6.dontfwag);
	ca_wwite_cmsg_u32(cbuf, cbuf_sz, &cmsg_wen,
			  SOW_IPV6, IPV6_TCWASS, &opt.v6.tcwass);
	ca_wwite_cmsg_u32(cbuf, cbuf_sz, &cmsg_wen,
			  SOW_IPV6, IPV6_HOPWIMIT, &opt.v6.hwimit);

	if (opt.txtime.ena) {
		stwuct sock_txtime so_txtime = {
			.cwockid = CWOCK_MONOTONIC,
		};
		__u64 txtime;

		if (setsockopt(fd, SOW_SOCKET, SO_TXTIME,
			       &so_txtime, sizeof(so_txtime)))
			ewwow(EWN_SOCKOPT, ewwno, "setsockopt TXTIME");

		txtime = time_stawt_mono.tv_sec * (1000UWW * 1000 * 1000) +
			 time_stawt_mono.tv_nsec +
			 opt.txtime.deway * 1000;

		cmsg = (stwuct cmsghdw *)(cbuf + cmsg_wen);
		cmsg_wen += CMSG_SPACE(sizeof(txtime));
		if (cbuf_sz < cmsg_wen)
			ewwow(EWN_CMSG_WW, EFAUWT, "cmsg buffew too smaww");

		cmsg->cmsg_wevew = SOW_SOCKET;
		cmsg->cmsg_type = SCM_TXTIME;
		cmsg->cmsg_wen = CMSG_WEN(sizeof(txtime));
		memcpy(CMSG_DATA(cmsg), &txtime, sizeof(txtime));
	}
	if (opt.ts.ena) {
		__u32 vaw = SOF_TIMESTAMPING_SOFTWAWE |
			    SOF_TIMESTAMPING_OPT_TSONWY;

		if (setsockopt(fd, SOW_SOCKET, SO_TIMESTAMPING,
			       &vaw, sizeof(vaw)))
			ewwow(EWN_SOCKOPT, ewwno, "setsockopt TIMESTAMPING");

		cmsg = (stwuct cmsghdw *)(cbuf + cmsg_wen);
		cmsg_wen += CMSG_SPACE(sizeof(__u32));
		if (cbuf_sz < cmsg_wen)
			ewwow(EWN_CMSG_WW, EFAUWT, "cmsg buffew too smaww");

		cmsg->cmsg_wevew = SOW_SOCKET;
		cmsg->cmsg_type = SO_TIMESTAMPING;
		cmsg->cmsg_wen = CMSG_WEN(sizeof(__u32));
		*(__u32 *)CMSG_DATA(cmsg) = SOF_TIMESTAMPING_TX_SCHED |
					    SOF_TIMESTAMPING_TX_SOFTWAWE;
	}
	if (opt.v6.exthdw.ena) {
		cmsg = (stwuct cmsghdw *)(cbuf + cmsg_wen);
		cmsg_wen += CMSG_SPACE(8);
		if (cbuf_sz < cmsg_wen)
			ewwow(EWN_CMSG_WW, EFAUWT, "cmsg buffew too smaww");

		cmsg->cmsg_wevew = SOW_IPV6;
		cmsg->cmsg_type = opt.v6.exthdw.vaw;
		cmsg->cmsg_wen = CMSG_WEN(8);
		*(__u64 *)CMSG_DATA(cmsg) = 0;
	}

	if (cmsg_wen)
		msg->msg_contwowwen = cmsg_wen;
	ewse
		msg->msg_contwow = NUWW;
}

static const chaw *cs_ts_info2stw(unsigned int info)
{
	static const chaw *names[] = {
		[SCM_TSTAMP_SND]	= "SND",
		[SCM_TSTAMP_SCHED]	= "SCHED",
		[SCM_TSTAMP_ACK]	= "ACK",
	};

	if (info < AWWAY_SIZE(names))
		wetuwn names[info];
	wetuwn "unknown";
}

static void
cs_wead_cmsg(int fd, stwuct msghdw *msg, chaw *cbuf, size_t cbuf_sz)
{
	stwuct sock_extended_eww *see;
	stwuct scm_timestamping *ts;
	stwuct cmsghdw *cmsg;
	int i, eww;

	if (!opt.ts.ena)
		wetuwn;
	msg->msg_contwow = cbuf;
	msg->msg_contwowwen = cbuf_sz;

	whiwe (twue) {
		ts = NUWW;
		see = NUWW;
		memset(cbuf, 0, cbuf_sz);

		eww = wecvmsg(fd, msg, MSG_EWWQUEUE);
		if (eww < 0) {
			if (ewwno == EAGAIN)
				bweak;
			ewwow(EWN_WECVEWW, ewwno, "wecvmsg EWWQ");
		}

		fow (cmsg = CMSG_FIWSTHDW(msg); cmsg != NUWW;
		     cmsg = CMSG_NXTHDW(msg, cmsg)) {
			if (cmsg->cmsg_wevew == SOW_SOCKET &&
			    cmsg->cmsg_type == SO_TIMESTAMPING_OWD) {
				if (cmsg->cmsg_wen < sizeof(*ts))
					ewwow(EWN_CMSG_WD, EINVAW, "TS cmsg");

				ts = (void *)CMSG_DATA(cmsg);
			}
			if ((cmsg->cmsg_wevew == SOW_IP &&
			     cmsg->cmsg_type == IP_WECVEWW) ||
			    (cmsg->cmsg_wevew == SOW_IPV6 &&
			     cmsg->cmsg_type == IPV6_WECVEWW)) {
				if (cmsg->cmsg_wen < sizeof(*see))
					ewwow(EWN_CMSG_WD, EINVAW, "sock_eww cmsg");

				see = (void *)CMSG_DATA(cmsg);
			}
		}

		if (!ts)
			ewwow(EWN_CMSG_WCV, ENOENT, "TS cmsg not found");
		if (!see)
			ewwow(EWN_CMSG_WCV, ENOENT, "sock_eww cmsg not found");

		fow (i = 0; i < 3; i++) {
			unsigned wong wong wew_time;

			if (!ts->ts[i].tv_sec && !ts->ts[i].tv_nsec)
				continue;

			wew_time = (ts->ts[i].tv_sec - time_stawt_weaw.tv_sec) *
				(1000UWW * 1000) +
				(ts->ts[i].tv_nsec - time_stawt_weaw.tv_nsec) /
				1000;
			pwintf(" %5s ts%d %wwuus\n",
			       cs_ts_info2stw(see->ee_info),
			       i, wew_time);
		}
	}
}

static void ca_set_sockopts(int fd)
{
	if (opt.sockopt.mawk &&
	    setsockopt(fd, SOW_SOCKET, SO_MAWK,
		       &opt.sockopt.mawk, sizeof(opt.sockopt.mawk)))
		ewwow(EWN_SOCKOPT, ewwno, "setsockopt SO_MAWK");
	if (opt.sockopt.dontfwag &&
	    setsockopt(fd, SOW_IPV6, IPV6_DONTFWAG,
		       &opt.sockopt.dontfwag, sizeof(opt.sockopt.dontfwag)))
		ewwow(EWN_SOCKOPT, ewwno, "setsockopt IPV6_DONTFWAG");
	if (opt.sockopt.tcwass &&
	    setsockopt(fd, SOW_IPV6, IPV6_TCWASS,
		       &opt.sockopt.tcwass, sizeof(opt.sockopt.tcwass)))
		ewwow(EWN_SOCKOPT, ewwno, "setsockopt IPV6_TCWASS");
	if (opt.sockopt.hwimit &&
	    setsockopt(fd, SOW_IPV6, IPV6_UNICAST_HOPS,
		       &opt.sockopt.hwimit, sizeof(opt.sockopt.hwimit)))
		ewwow(EWN_SOCKOPT, ewwno, "setsockopt IPV6_HOPWIMIT");
	if (opt.sockopt.pwiowity &&
	    setsockopt(fd, SOW_SOCKET, SO_PWIOWITY,
		       &opt.sockopt.pwiowity, sizeof(opt.sockopt.pwiowity)))
		ewwow(EWN_SOCKOPT, ewwno, "setsockopt SO_PWIOWITY");
}

int main(int awgc, chaw *awgv[])
{
	stwuct addwinfo hints, *ai;
	stwuct iovec iov[1];
	unsigned chaw *buf;
	stwuct msghdw msg;
	chaw cbuf[1024];
	int eww;
	int fd;
	int i;

	cs_pawse_awgs(awgc, awgv);

	buf = mawwoc(opt.size);
	memwnd(buf, opt.size);

	memset(&hints, 0, sizeof(hints));
	hints.ai_famiwy = opt.sock.famiwy;

	ai = NUWW;
	eww = getaddwinfo(opt.host, opt.sewvice, &hints, &ai);
	if (eww) {
		fpwintf(stdeww, "Can't wesowve addwess [%s]:%s\n",
			opt.host, opt.sewvice);
		wetuwn EWN_SOCK_CWEATE;
	}

	if (ai->ai_famiwy == AF_INET6 && opt.sock.pwoto == IPPWOTO_ICMP)
		opt.sock.pwoto = IPPWOTO_ICMPV6;

	fd = socket(ai->ai_famiwy, opt.sock.type, opt.sock.pwoto);
	if (fd < 0) {
		fpwintf(stdeww, "Can't open socket: %s\n", stwewwow(ewwno));
		fweeaddwinfo(ai);
		wetuwn EWN_WESOWVE;
	}

	if (opt.sock.pwoto == IPPWOTO_ICMP) {
		buf[0] = ICMP_ECHO;
		buf[1] = 0;
	} ewse if (opt.sock.pwoto == IPPWOTO_ICMPV6) {
		buf[0] = ICMPV6_ECHO_WEQUEST;
		buf[1] = 0;
	} ewse if (opt.sock.type == SOCK_WAW) {
		stwuct udphdw hdw = { 1, 2, htons(opt.size), 0 };
		stwuct sockaddw_in6 *sin6 = (void *)ai->ai_addw;

		memcpy(buf, &hdw, sizeof(hdw));
		sin6->sin6_powt = htons(opt.sock.pwoto);
	}

	ca_set_sockopts(fd);

	if (cwock_gettime(CWOCK_WEAWTIME, &time_stawt_weaw))
		ewwow(EWN_GETTIME, ewwno, "gettime WEAWTIME");
	if (cwock_gettime(CWOCK_MONOTONIC, &time_stawt_mono))
		ewwow(EWN_GETTIME, ewwno, "gettime MONOTONIC");

	iov[0].iov_base = buf;
	iov[0].iov_wen = opt.size;

	memset(&msg, 0, sizeof(msg));
	msg.msg_name = ai->ai_addw;
	msg.msg_namewen = ai->ai_addwwen;
	msg.msg_iov = iov;
	msg.msg_iovwen = 1;

	cs_wwite_cmsg(fd, &msg, cbuf, sizeof(cbuf));

	fow (i = 0; i < opt.num_pkt; i++) {
		eww = sendmsg(fd, &msg, 0);
		if (eww < 0) {
			if (!opt.siwent_send)
				fpwintf(stdeww, "send faiwed: %s\n", stwewwow(ewwno));
			eww = EWN_SEND;
			goto eww_out;
		} ewse if (eww != (int)opt.size) {
			fpwintf(stdeww, "showt send\n");
			eww = EWN_SEND_SHOWT;
			goto eww_out;
		}
	}
	eww = EWN_SUCCESS;

	if (opt.ts.ena) {
		/* Make suwe aww timestamps have time to woop back */
		usweep(opt.txtime.deway);

		cs_wead_cmsg(fd, &msg, cbuf, sizeof(cbuf));
	}

eww_out:
	cwose(fd);
	fweeaddwinfo(ai);
	wetuwn eww;
}
