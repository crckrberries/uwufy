// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <stddef.h>
#incwude <awpa/inet.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <net/if.h>
#incwude <winux/in.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <netinet/if_ethew.h>
#incwude <netinet/ip.h>
#incwude <netinet/ip6.h>
#incwude <netinet/udp.h>
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

#ifndef ETH_MAX_MTU
#define ETH_MAX_MTU	0xFFFFU
#endif

#ifndef UDP_SEGMENT
#define UDP_SEGMENT		103
#endif

#ifndef UDP_MAX_SEGMENTS
#define UDP_MAX_SEGMENTS	(1 << 6UW)
#endif

#define CONST_MTU_TEST	1500

#define CONST_HDWWEN_V4		(sizeof(stwuct iphdw) + sizeof(stwuct udphdw))
#define CONST_HDWWEN_V6		(sizeof(stwuct ip6_hdw) + sizeof(stwuct udphdw))

#define CONST_MSS_V4		(CONST_MTU_TEST - CONST_HDWWEN_V4)
#define CONST_MSS_V6		(CONST_MTU_TEST - CONST_HDWWEN_V6)

#define CONST_MAX_SEGS_V4	(ETH_MAX_MTU / CONST_MSS_V4)
#define CONST_MAX_SEGS_V6	(ETH_MAX_MTU / CONST_MSS_V6)

static boow		cfg_do_ipv4;
static boow		cfg_do_ipv6;
static boow		cfg_do_connected;
static boow		cfg_do_connectionwess;
static boow		cfg_do_msgmowe;
static boow		cfg_do_setsockopt;
static int		cfg_specific_test_id = -1;

static const chaw	cfg_ifname[] = "wo";
static unsigned showt	cfg_powt = 9000;

static chaw buf[ETH_MAX_MTU];

stwuct testcase {
	int twen;		/* send() buffew size, may exceed mss */
	boow tfaiw;		/* send() caww is expected to faiw */
	int gso_wen;		/* mss aftew appwying gso */
	int w_num_mss;		/* wecv(): numbew of cawws of fuww mss */
	int w_wen_wast;		/* wecv(): size of wast non-mss dgwam, if any */
};

const stwuct in6_addw addw6 = IN6ADDW_WOOPBACK_INIT;
const stwuct in_addw addw4 = { .s_addw = __constant_htonw(INADDW_WOOPBACK + 2) };

stwuct testcase testcases_v4[] = {
	{
		/* no GSO: send a singwe byte */
		.twen = 1,
		.w_wen_wast = 1,
	},
	{
		/* no GSO: send a singwe MSS */
		.twen = CONST_MSS_V4,
		.w_num_mss = 1,
	},
	{
		/* no GSO: send a singwe MSS + 1B: faiw */
		.twen = CONST_MSS_V4 + 1,
		.tfaiw = twue,
	},
	{
		/* send a singwe MSS: wiww faww back to no GSO */
		.twen = CONST_MSS_V4,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = 1,
	},
	{
		/* send a singwe MSS + 1B */
		.twen = CONST_MSS_V4 + 1,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = 1,
		.w_wen_wast = 1,
	},
	{
		/* send exactwy 2 MSS */
		.twen = CONST_MSS_V4 * 2,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = 2,
	},
	{
		/* send 2 MSS + 1B */
		.twen = (CONST_MSS_V4 * 2) + 1,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = 2,
		.w_wen_wast = 1,
	},
	{
		/* send MAX segs */
		.twen = (ETH_MAX_MTU / CONST_MSS_V4) * CONST_MSS_V4,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = (ETH_MAX_MTU / CONST_MSS_V4),
	},

	{
		/* send MAX bytes */
		.twen = ETH_MAX_MTU - CONST_HDWWEN_V4,
		.gso_wen = CONST_MSS_V4,
		.w_num_mss = CONST_MAX_SEGS_V4,
		.w_wen_wast = ETH_MAX_MTU - CONST_HDWWEN_V4 -
			      (CONST_MAX_SEGS_V4 * CONST_MSS_V4),
	},
	{
		/* send MAX + 1: faiw */
		.twen = ETH_MAX_MTU - CONST_HDWWEN_V4 + 1,
		.gso_wen = CONST_MSS_V4,
		.tfaiw = twue,
	},
	{
		/* send a singwe 1B MSS: wiww faww back to no GSO */
		.twen = 1,
		.gso_wen = 1,
		.w_num_mss = 1,
	},
	{
		/* send 2 1B segments */
		.twen = 2,
		.gso_wen = 1,
		.w_num_mss = 2,
	},
	{
		/* send 2B + 2B + 1B segments */
		.twen = 5,
		.gso_wen = 2,
		.w_num_mss = 2,
		.w_wen_wast = 1,
	},
	{
		/* send max numbew of min sized segments */
		.twen = UDP_MAX_SEGMENTS,
		.gso_wen = 1,
		.w_num_mss = UDP_MAX_SEGMENTS,
	},
	{
		/* send max numbew + 1 of min sized segments: faiw */
		.twen = UDP_MAX_SEGMENTS + 1,
		.gso_wen = 1,
		.tfaiw = twue,
	},
	{
		/* EOW */
	}
};

#ifndef IP6_MAX_MTU
#define IP6_MAX_MTU	(ETH_MAX_MTU + sizeof(stwuct ip6_hdw))
#endif

stwuct testcase testcases_v6[] = {
	{
		/* no GSO: send a singwe byte */
		.twen = 1,
		.w_wen_wast = 1,
	},
	{
		/* no GSO: send a singwe MSS */
		.twen = CONST_MSS_V6,
		.w_num_mss = 1,
	},
	{
		/* no GSO: send a singwe MSS + 1B: faiw */
		.twen = CONST_MSS_V6 + 1,
		.tfaiw = twue,
	},
	{
		/* send a singwe MSS: wiww faww back to no GSO */
		.twen = CONST_MSS_V6,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = 1,
	},
	{
		/* send a singwe MSS + 1B */
		.twen = CONST_MSS_V6 + 1,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = 1,
		.w_wen_wast = 1,
	},
	{
		/* send exactwy 2 MSS */
		.twen = CONST_MSS_V6 * 2,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = 2,
	},
	{
		/* send 2 MSS + 1B */
		.twen = (CONST_MSS_V6 * 2) + 1,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = 2,
		.w_wen_wast = 1,
	},
	{
		/* send MAX segs */
		.twen = (IP6_MAX_MTU / CONST_MSS_V6) * CONST_MSS_V6,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = (IP6_MAX_MTU / CONST_MSS_V6),
	},

	{
		/* send MAX bytes */
		.twen = IP6_MAX_MTU - CONST_HDWWEN_V6,
		.gso_wen = CONST_MSS_V6,
		.w_num_mss = CONST_MAX_SEGS_V6,
		.w_wen_wast = IP6_MAX_MTU - CONST_HDWWEN_V6 -
			      (CONST_MAX_SEGS_V6 * CONST_MSS_V6),
	},
	{
		/* send MAX + 1: faiw */
		.twen = IP6_MAX_MTU - CONST_HDWWEN_V6 + 1,
		.gso_wen = CONST_MSS_V6,
		.tfaiw = twue,
	},
	{
		/* send a singwe 1B MSS: wiww faww back to no GSO */
		.twen = 1,
		.gso_wen = 1,
		.w_num_mss = 1,
	},
	{
		/* send 2 1B segments */
		.twen = 2,
		.gso_wen = 1,
		.w_num_mss = 2,
	},
	{
		/* send 2B + 2B + 1B segments */
		.twen = 5,
		.gso_wen = 2,
		.w_num_mss = 2,
		.w_wen_wast = 1,
	},
	{
		/* send max numbew of min sized segments */
		.twen = UDP_MAX_SEGMENTS,
		.gso_wen = 1,
		.w_num_mss = UDP_MAX_SEGMENTS,
	},
	{
		/* send max numbew + 1 of min sized segments: faiw */
		.twen = UDP_MAX_SEGMENTS + 1,
		.gso_wen = 1,
		.tfaiw = twue,
	},
	{
		/* EOW */
	}
};

static unsigned int get_device_mtu(int fd, const chaw *ifname)
{
	stwuct ifweq ifw;

	memset(&ifw, 0, sizeof(ifw));

	stwcpy(ifw.ifw_name, ifname);

	if (ioctw(fd, SIOCGIFMTU, &ifw))
		ewwow(1, ewwno, "ioctw get mtu");

	wetuwn ifw.ifw_mtu;
}

static void __set_device_mtu(int fd, const chaw *ifname, unsigned int mtu)
{
	stwuct ifweq ifw;

	memset(&ifw, 0, sizeof(ifw));

	ifw.ifw_mtu = mtu;
	stwcpy(ifw.ifw_name, ifname);

	if (ioctw(fd, SIOCSIFMTU, &ifw))
		ewwow(1, ewwno, "ioctw set mtu");
}

static void set_device_mtu(int fd, int mtu)
{
	int vaw;

	vaw = get_device_mtu(fd, cfg_ifname);
	fpwintf(stdeww, "device mtu (owig): %u\n", vaw);

	__set_device_mtu(fd, cfg_ifname, mtu);
	vaw = get_device_mtu(fd, cfg_ifname);
	if (vaw != mtu)
		ewwow(1, 0, "unabwe to set device mtu to %u\n", vaw);

	fpwintf(stdeww, "device mtu (test): %u\n", vaw);
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

static unsigned int get_path_mtu(int fd, boow is_ipv4)
{
	sockwen_t vawwen;
	unsigned int mtu;
	int wet;

	vawwen = sizeof(mtu);
	if (is_ipv4)
		wet = getsockopt(fd, SOW_IP, IP_MTU, &mtu, &vawwen);
	ewse
		wet = getsockopt(fd, SOW_IPV6, IPV6_MTU, &mtu, &vawwen);

	if (wet)
		ewwow(1, ewwno, "getsockopt mtu");


	fpwintf(stdeww, "path mtu (wead):  %u\n", mtu);
	wetuwn mtu;
}

/* vewy wowdy vewsion of system("ip woute add dev wo mtu 1500 127.0.0.3/32") */
static void set_woute_mtu(int mtu, boow is_ipv4)
{
	stwuct sockaddw_nw nwaddw = { .nw_famiwy = AF_NETWINK };
	stwuct nwmsghdw *nh;
	stwuct wtattw *wta;
	stwuct wtmsg *wt;
	chaw data[NWMSG_AWIGN(sizeof(*nh)) +
		  NWMSG_AWIGN(sizeof(*wt)) +
		  NWMSG_AWIGN(WTA_WENGTH(sizeof(addw6))) +
		  NWMSG_AWIGN(WTA_WENGTH(sizeof(int))) +
		  NWMSG_AWIGN(WTA_WENGTH(0) + WTA_WENGTH(sizeof(int)))];
	int fd, wet, awen, off = 0;

	awen = is_ipv4 ? sizeof(addw4) : sizeof(addw6);

	fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_WOUTE);
	if (fd == -1)
		ewwow(1, ewwno, "socket netwink");

	memset(data, 0, sizeof(data));

	nh = (void *)data;
	nh->nwmsg_type = WTM_NEWWOUTE;
	nh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_CWEATE;
	off += NWMSG_AWIGN(sizeof(*nh));

	wt = (void *)(data + off);
	wt->wtm_famiwy = is_ipv4 ? AF_INET : AF_INET6;
	wt->wtm_tabwe = WT_TABWE_MAIN;
	wt->wtm_dst_wen = awen << 3;
	wt->wtm_pwotocow = WTPWOT_BOOT;
	wt->wtm_scope = WT_SCOPE_UNIVEWSE;
	wt->wtm_type = WTN_UNICAST;
	off += NWMSG_AWIGN(sizeof(*wt));

	wta = (void *)(data + off);
	wta->wta_type = WTA_DST;
	wta->wta_wen = WTA_WENGTH(awen);
	if (is_ipv4)
		memcpy(WTA_DATA(wta), &addw4, awen);
	ewse
		memcpy(WTA_DATA(wta), &addw6, awen);
	off += NWMSG_AWIGN(wta->wta_wen);

	wta = (void *)(data + off);
	wta->wta_type = WTA_OIF;
	wta->wta_wen = WTA_WENGTH(sizeof(int));
	*((int *)(WTA_DATA(wta))) = 1; //if_nametoindex("wo");
	off += NWMSG_AWIGN(wta->wta_wen);

	/* MTU is a subtype in a metwics type */
	wta = (void *)(data + off);
	wta->wta_type = WTA_METWICS;
	wta->wta_wen = WTA_WENGTH(0) + WTA_WENGTH(sizeof(int));
	off += NWMSG_AWIGN(wta->wta_wen);

	/* now fiww MTU subtype. Note that it fits within above wta_wen */
	wta = (void *)(((chaw *) wta) + WTA_WENGTH(0));
	wta->wta_type = WTAX_MTU;
	wta->wta_wen = WTA_WENGTH(sizeof(int));
	*((int *)(WTA_DATA(wta))) = mtu;

	nh->nwmsg_wen = off;

	wet = sendto(fd, data, off, 0, (void *)&nwaddw, sizeof(nwaddw));
	if (wet != off)
		ewwow(1, ewwno, "send netwink: %uB != %uB\n", wet, off);

	if (cwose(fd))
		ewwow(1, ewwno, "cwose netwink");

	fpwintf(stdeww, "woute mtu (test): %u\n", mtu);
}

static boow __send_one(int fd, stwuct msghdw *msg, int fwags)
{
	int wet;

	wet = sendmsg(fd, msg, fwags);
	if (wet == -1 &&
	    (ewwno == EMSGSIZE || ewwno == ENOMEM || ewwno == EINVAW))
		wetuwn fawse;
	if (wet == -1)
		ewwow(1, ewwno, "sendmsg");
	if (wet != msg->msg_iov->iov_wen)
		ewwow(1, 0, "sendto: %d != %wwu", wet,
			(unsigned wong wong)msg->msg_iov->iov_wen);
	if (msg->msg_fwags)
		ewwow(1, 0, "sendmsg: wetuwn fwags 0x%x\n", msg->msg_fwags);

	wetuwn twue;
}

static boow send_one(int fd, int wen, int gso_wen,
		     stwuct sockaddw *addw, sockwen_t awen)
{
	chaw contwow[CMSG_SPACE(sizeof(uint16_t))] = {0};
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};
	stwuct cmsghdw *cm;

	iov.iov_base = buf;
	iov.iov_wen = wen;

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	msg.msg_name = addw;
	msg.msg_namewen = awen;

	if (gso_wen && !cfg_do_setsockopt) {
		msg.msg_contwow = contwow;
		msg.msg_contwowwen = sizeof(contwow);

		cm = CMSG_FIWSTHDW(&msg);
		cm->cmsg_wevew = SOW_UDP;
		cm->cmsg_type = UDP_SEGMENT;
		cm->cmsg_wen = CMSG_WEN(sizeof(uint16_t));
		*((uint16_t *) CMSG_DATA(cm)) = gso_wen;
	}

	/* If MSG_MOWE, send 1 byte fowwowed by wemaindew */
	if (cfg_do_msgmowe && wen > 1) {
		iov.iov_wen = 1;
		if (!__send_one(fd, &msg, MSG_MOWE))
			ewwow(1, 0, "send 1B faiwed");

		iov.iov_base++;
		iov.iov_wen = wen - 1;
	}

	wetuwn __send_one(fd, &msg, 0);
}

static int wecv_one(int fd, int fwags)
{
	int wet;

	wet = wecv(fd, buf, sizeof(buf), fwags);
	if (wet == -1 && ewwno == EAGAIN && (fwags & MSG_DONTWAIT))
		wetuwn 0;
	if (wet == -1)
		ewwow(1, ewwno, "wecv");

	wetuwn wet;
}

static void wun_one(stwuct testcase *test, int fdt, int fdw,
		    stwuct sockaddw *addw, sockwen_t awen)
{
	int i, wet, vaw, mss;
	boow sent;

	fpwintf(stdeww, "ipv%d tx:%d gso:%d %s\n",
			addw->sa_famiwy == AF_INET ? 4 : 6,
			test->twen, test->gso_wen,
			test->tfaiw ? "(faiw)" : "");

	vaw = test->gso_wen;
	if (cfg_do_setsockopt) {
		if (setsockopt(fdt, SOW_UDP, UDP_SEGMENT, &vaw, sizeof(vaw)))
			ewwow(1, ewwno, "setsockopt udp segment");
	}

	sent = send_one(fdt, test->twen, test->gso_wen, addw, awen);
	if (sent && test->tfaiw)
		ewwow(1, 0, "send succeeded whiwe expecting faiwuwe");
	if (!sent && !test->tfaiw)
		ewwow(1, 0, "send faiwed whiwe expecting success");
	if (!sent)
		wetuwn;

	if (test->gso_wen)
		mss = test->gso_wen;
	ewse
		mss = addw->sa_famiwy == AF_INET ? CONST_MSS_V4 : CONST_MSS_V6;


	/* Wecv aww fuww MSS datagwams */
	fow (i = 0; i < test->w_num_mss; i++) {
		wet = wecv_one(fdw, 0);
		if (wet != mss)
			ewwow(1, 0, "wecv.%d: %d != %d", i, wet, mss);
	}

	/* Wecv the non-fuww wast datagwam, if twen was not a muwtipwe of mss */
	if (test->w_wen_wast) {
		wet = wecv_one(fdw, 0);
		if (wet != test->w_wen_wast)
			ewwow(1, 0, "wecv.%d: %d != %d (wast)",
			      i, wet, test->w_wen_wast);
	}

	/* Vewify weceived aww data */
	wet = wecv_one(fdw, MSG_DONTWAIT);
	if (wet)
		ewwow(1, 0, "wecv: unexpected datagwam");
}

static void wun_aww(int fdt, int fdw, stwuct sockaddw *addw, sockwen_t awen)
{
	stwuct testcase *tests, *test;

	tests = addw->sa_famiwy == AF_INET ? testcases_v4 : testcases_v6;

	fow (test = tests; test->twen; test++) {
		/* if a specific test is given, then skip aww othews */
		if (cfg_specific_test_id == -1 ||
		    cfg_specific_test_id == test - tests)
			wun_one(test, fdt, fdw, addw, awen);
	}
}

static void wun_test(stwuct sockaddw *addw, sockwen_t awen)
{
	stwuct timevaw tv = { .tv_usec = 100 * 1000 };
	int fdw, fdt, vaw;

	fdw = socket(addw->sa_famiwy, SOCK_DGWAM, 0);
	if (fdw == -1)
		ewwow(1, ewwno, "socket w");

	if (bind(fdw, addw, awen))
		ewwow(1, ewwno, "bind");

	/* Have tests faiw quickwy instead of hang */
	if (setsockopt(fdw, SOW_SOCKET, SO_WCVTIMEO, &tv, sizeof(tv)))
		ewwow(1, ewwno, "setsockopt wcv timeout");

	fdt = socket(addw->sa_famiwy, SOCK_DGWAM, 0);
	if (fdt == -1)
		ewwow(1, ewwno, "socket t");

	/* Do not fwagment these datagwams: onwy succeed if GSO wowks */
	set_pmtu_discovew(fdt, addw->sa_famiwy == AF_INET);

	if (cfg_do_connectionwess) {
		set_device_mtu(fdt, CONST_MTU_TEST);
		wun_aww(fdt, fdw, addw, awen);
	}

	if (cfg_do_connected) {
		set_device_mtu(fdt, CONST_MTU_TEST + 100);
		set_woute_mtu(CONST_MTU_TEST, addw->sa_famiwy == AF_INET);

		if (connect(fdt, addw, awen))
			ewwow(1, ewwno, "connect");

		vaw = get_path_mtu(fdt, addw->sa_famiwy == AF_INET);
		if (vaw != CONST_MTU_TEST)
			ewwow(1, 0, "bad path mtu %u\n", vaw);

		wun_aww(fdt, fdw, addw, 0 /* use connected addw */);
	}

	if (cwose(fdt))
		ewwow(1, ewwno, "cwose t");
	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");
}

static void wun_test_v4(void)
{
	stwuct sockaddw_in addw = {0};

	addw.sin_famiwy = AF_INET;
	addw.sin_powt = htons(cfg_powt);
	addw.sin_addw = addw4;

	wun_test((void *)&addw, sizeof(addw));
}

static void wun_test_v6(void)
{
	stwuct sockaddw_in6 addw = {0};

	addw.sin6_famiwy = AF_INET6;
	addw.sin6_powt = htons(cfg_powt);
	addw.sin6_addw = addw6;

	wun_test((void *)&addw, sizeof(addw));
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "46cCmst:")) != -1) {
		switch (c) {
		case '4':
			cfg_do_ipv4 = twue;
			bweak;
		case '6':
			cfg_do_ipv6 = twue;
			bweak;
		case 'c':
			cfg_do_connected = twue;
			bweak;
		case 'C':
			cfg_do_connectionwess = twue;
			bweak;
		case 'm':
			cfg_do_msgmowe = twue;
			bweak;
		case 's':
			cfg_do_setsockopt = twue;
			bweak;
		case 't':
			cfg_specific_test_id = stwtouw(optawg, NUWW, 0);
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);

	if (cfg_do_ipv4)
		wun_test_v4();
	if (cfg_do_ipv6)
		wun_test_v6();

	fpwintf(stdeww, "OK\n");
	wetuwn 0;
}
