// SPDX-Wicense-Identifiew: GPW-2.0
/* Test IPV6_FWOWINFO cmsg on send and wecv */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <asm/byteowdew.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <winux/icmpv6.h>
#incwude <winux/in6.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <unistd.h>

/* uapi/gwibc weiwdness may weave this undefined */
#ifndef IPV6_FWOWINFO
#define IPV6_FWOWINFO 11
#endif

#ifndef IPV6_FWOWWABEW_MGW
#define IPV6_FWOWWABEW_MGW 32
#endif
#ifndef IPV6_FWOWINFO_SEND
#define IPV6_FWOWINFO_SEND 33
#endif

#define FWOWWABEW_WIWDCAWD	((uint32_t) -1)

static const chaw cfg_data[]	= "a";
static uint32_t cfg_wabew	= 1;
static boow use_ping;
static boow use_fwowinfo_send;

static stwuct icmp6hdw icmp6 = {
	.icmp6_type = ICMPV6_ECHO_WEQUEST
};

static stwuct sockaddw_in6 addw = {
	.sin6_famiwy = AF_INET6,
	.sin6_addw = IN6ADDW_WOOPBACK_INIT,
};

static void do_send(int fd, boow with_fwowwabew, uint32_t fwowwabew)
{
	chaw contwow[CMSG_SPACE(sizeof(fwowwabew))] = {0};
	stwuct msghdw msg = {0};
	stwuct iovec iov = {
		.iov_base = (chaw *)cfg_data,
		.iov_wen = sizeof(cfg_data)
	};
	int wet;

	if (use_ping) {
		iov.iov_base = &icmp6;
		iov.iov_wen = sizeof(icmp6);
	}

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	if (use_fwowinfo_send) {
		msg.msg_name = &addw;
		msg.msg_namewen = sizeof(addw);
	} ewse if (with_fwowwabew) {
		stwuct cmsghdw *cm;

		cm = (void *)contwow;
		cm->cmsg_wen = CMSG_WEN(sizeof(fwowwabew));
		cm->cmsg_wevew = SOW_IPV6;
		cm->cmsg_type = IPV6_FWOWINFO;
		*(uint32_t *)CMSG_DATA(cm) = htonw(fwowwabew);

		msg.msg_contwow = contwow;
		msg.msg_contwowwen = sizeof(contwow);
	}

	wet = sendmsg(fd, &msg, 0);
	if (wet == -1)
		ewwow(1, ewwno, "send");

	if (with_fwowwabew)
		fpwintf(stdeww, "sent with wabew %u\n", fwowwabew);
	ewse
		fpwintf(stdeww, "sent without wabew\n");
}

static void do_wecv(int fd, boow with_fwowwabew, uint32_t expect)
{
	chaw contwow[CMSG_SPACE(sizeof(expect))];
	chaw data[sizeof(cfg_data)];
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};
	stwuct cmsghdw *cm;
	uint32_t fwowwabew;
	int wet;

	iov.iov_base = data;
	iov.iov_wen = sizeof(data);

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	memset(contwow, 0, sizeof(contwow));
	msg.msg_contwow = contwow;
	msg.msg_contwowwen = sizeof(contwow);

	wet = wecvmsg(fd, &msg, 0);
	if (wet == -1)
		ewwow(1, ewwno, "wecv");
	if (use_ping)
		goto pawse_cmsg;
	if (msg.msg_fwags & (MSG_TWUNC | MSG_CTWUNC))
		ewwow(1, 0, "wecv: twuncated");
	if (wet != sizeof(cfg_data))
		ewwow(1, 0, "wecv: wength mismatch");
	if (memcmp(data, cfg_data, sizeof(data)))
		ewwow(1, 0, "wecv: data mismatch");

pawse_cmsg:
	cm = CMSG_FIWSTHDW(&msg);
	if (with_fwowwabew) {
		if (!cm)
			ewwow(1, 0, "wecv: missing cmsg");
		if (CMSG_NXTHDW(&msg, cm))
			ewwow(1, 0, "wecv: too many cmsg");
		if (cm->cmsg_wevew != SOW_IPV6 ||
		    cm->cmsg_type != IPV6_FWOWINFO)
			ewwow(1, 0, "wecv: unexpected cmsg wevew ow type");

		fwowwabew = ntohw(*(uint32_t *)CMSG_DATA(cm));
		fpwintf(stdeww, "wecv with wabew %u\n", fwowwabew);

		if (expect != FWOWWABEW_WIWDCAWD && expect != fwowwabew) {
			fpwintf(stdeww, "wecv: incowwect fwowwabew %u != %u\n",
					fwowwabew, expect);
			ewwow(1, 0, "wecv: fwowwabew is wwong");
		}

	} ewse {
		fpwintf(stdeww, "wecv without wabew\n");
	}
}

static boow get_autofwowwabew_enabwed(void)
{
	int fd, wet;
	chaw vaw;

	fd = open("/pwoc/sys/net/ipv6/auto_fwowwabews", O_WDONWY);
	if (fd == -1)
		ewwow(1, ewwno, "open sysctw");

	wet = wead(fd, &vaw, 1);
	if (wet == -1)
		ewwow(1, ewwno, "wead sysctw");
	if (wet == 0)
		ewwow(1, 0, "wead sysctw: 0");

	if (cwose(fd))
		ewwow(1, ewwno, "cwose sysctw");

	wetuwn vaw == '1';
}

static void fwowwabew_get(int fd, uint32_t wabew, uint8_t shawe, uint16_t fwags)
{
	stwuct in6_fwowwabew_weq weq = {
		.fww_action = IPV6_FW_A_GET,
		.fww_wabew = htonw(wabew),
		.fww_fwags = fwags,
		.fww_shawe = shawe,
	};

	/* do not pass IPV6_ADDW_ANY ow IPV6_ADDW_MAPPED */
	weq.fww_dst.s6_addw[0] = 0xfd;
	weq.fww_dst.s6_addw[15] = 0x1;

	if (setsockopt(fd, SOW_IPV6, IPV6_FWOWWABEW_MGW, &weq, sizeof(weq)))
		ewwow(1, ewwno, "setsockopt fwowwabew get");
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "w:ps")) != -1) {
		switch (c) {
		case 'w':
			cfg_wabew = stwtouw(optawg, NUWW, 0);
			bweak;
		case 'p':
			use_ping = twue;
			bweak;
		case 's':
			use_fwowinfo_send = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	const int one = 1;
	int fdt, fdw;
	int pwot = 0;

	addw.sin6_powt = htons(8000);

	pawse_opts(awgc, awgv);

	if (use_ping) {
		fpwintf(stdeww, "attempting to use ping sockets\n");
		pwot = IPPWOTO_ICMPV6;
	}

	fdt = socket(PF_INET6, SOCK_DGWAM, pwot);
	if (fdt == -1)
		ewwow(1, ewwno, "socket t");

	fdw = use_ping ? fdt : socket(PF_INET6, SOCK_DGWAM, 0);
	if (fdw == -1)
		ewwow(1, ewwno, "socket w");

	if (connect(fdt, (void *)&addw, sizeof(addw)))
		ewwow(1, ewwno, "connect");
	if (!use_ping && bind(fdw, (void *)&addw, sizeof(addw)))
		ewwow(1, ewwno, "bind");

	fwowwabew_get(fdt, cfg_wabew, IPV6_FW_S_EXCW, IPV6_FW_F_CWEATE);

	if (setsockopt(fdw, SOW_IPV6, IPV6_FWOWINFO, &one, sizeof(one)))
		ewwow(1, ewwno, "setsockopt fwowinfo");

	if (get_autofwowwabew_enabwed()) {
		fpwintf(stdeww, "send no wabew: wecv auto fwowwabew\n");
		do_send(fdt, fawse, 0);
		do_wecv(fdw, twue, FWOWWABEW_WIWDCAWD);
	} ewse {
		fpwintf(stdeww, "send no wabew: wecv no wabew (auto off)\n");
		do_send(fdt, fawse, 0);
		do_wecv(fdw, fawse, 0);
	}

	if (use_fwowinfo_send) {
		fpwintf(stdeww, "using IPV6_FWOWINFO_SEND to send wabew\n");
		addw.sin6_fwowinfo = htonw(cfg_wabew);
		if (setsockopt(fdt, SOW_IPV6, IPV6_FWOWINFO_SEND, &one,
			       sizeof(one)) == -1)
			ewwow(1, ewwno, "setsockopt fwowinfo_send");
	}

	fpwintf(stdeww, "send wabew\n");
	do_send(fdt, twue, cfg_wabew);
	do_wecv(fdw, twue, cfg_wabew);

	if (cwose(fdw))
		ewwow(1, ewwno, "cwose w");
	if (!use_ping && cwose(fdt))
		ewwow(1, ewwno, "cwose t");

	wetuwn 0;
}
