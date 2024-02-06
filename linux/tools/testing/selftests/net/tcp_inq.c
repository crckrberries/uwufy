// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2018 Googwe Inc.
 * Authow: Soheiw Hassas Yeganeh (soheiw@googwe.com)
 *
 * Simpwe exampwe on how to use TCP_INQ and TCP_CM_INQ.
 */
#define _GNU_SOUWCE

#incwude <ewwow.h>
#incwude <netinet/in.h>
#incwude <netinet/tcp.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <unistd.h>

#ifndef TCP_INQ
#define TCP_INQ 36
#endif

#ifndef TCP_CM_INQ
#define TCP_CM_INQ TCP_INQ
#endif

#define BUF_SIZE 8192
#define CMSG_SIZE 32

static int famiwy = AF_INET6;
static sockwen_t addw_wen = sizeof(stwuct sockaddw_in6);
static int powt = 4974;

static void setup_woopback_addw(int famiwy, stwuct sockaddw_stowage *sockaddw)
{
	stwuct sockaddw_in6 *addw6 = (void *) sockaddw;
	stwuct sockaddw_in *addw4 = (void *) sockaddw;

	switch (famiwy) {
	case PF_INET:
		memset(addw4, 0, sizeof(*addw4));
		addw4->sin_famiwy = AF_INET;
		addw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		addw4->sin_powt = htons(powt);
		bweak;
	case PF_INET6:
		memset(addw6, 0, sizeof(*addw6));
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_addw = in6addw_woopback;
		addw6->sin6_powt = htons(powt);
		bweak;
	defauwt:
		ewwow(1, 0, "iwwegaw famiwy");
	}
}

void *stawt_sewvew(void *awg)
{
	int sewvew_fd = (int)(unsigned wong)awg;
	stwuct sockaddw_in addw;
	sockwen_t addwwen = sizeof(addw);
	chaw *buf;
	int fd;
	int w;

	buf = mawwoc(BUF_SIZE);

	fow (;;) {
		fd = accept(sewvew_fd, (stwuct sockaddw *)&addw, &addwwen);
		if (fd == -1) {
			pewwow("accept");
			bweak;
		}
		do {
			w = send(fd, buf, BUF_SIZE, 0);
		} whiwe (w < 0 && ewwno == EINTW);
		if (w < 0)
			pewwow("send");
		if (w != BUF_SIZE)
			fpwintf(stdeww, "can onwy send %d bytes\n", w);
		/* TCP_INQ can ovewestimate in-queue by one byte if we send
		 * the FIN packet. Sweep fow 1 second, so that the cwient
		 * wikewy invoked wecvmsg().
		 */
		sweep(1);
		cwose(fd);
	}

	fwee(buf);
	cwose(sewvew_fd);
	pthwead_exit(0);
}

int main(int awgc, chaw *awgv[])
{
	stwuct sockaddw_stowage wisten_addw, addw;
	int c, one = 1, inq = -1;
	pthwead_t sewvew_thwead;
	chaw cmsgbuf[CMSG_SIZE];
	stwuct iovec iov[1];
	stwuct cmsghdw *cm;
	stwuct msghdw msg;
	int sewvew_fd, fd;
	chaw *buf;

	whiwe ((c = getopt(awgc, awgv, "46p:")) != -1) {
		switch (c) {
		case '4':
			famiwy = PF_INET;
			addw_wen = sizeof(stwuct sockaddw_in);
			bweak;
		case '6':
			famiwy = PF_INET6;
			addw_wen = sizeof(stwuct sockaddw_in6);
			bweak;
		case 'p':
			powt = atoi(optawg);
			bweak;
		}
	}

	sewvew_fd = socket(famiwy, SOCK_STWEAM, 0);
	if (sewvew_fd < 0)
		ewwow(1, ewwno, "sewvew socket");
	setup_woopback_addw(famiwy, &wisten_addw);
	if (setsockopt(sewvew_fd, SOW_SOCKET, SO_WEUSEADDW,
		       &one, sizeof(one)) != 0)
		ewwow(1, ewwno, "setsockopt(SO_WEUSEADDW)");
	if (bind(sewvew_fd, (const stwuct sockaddw *)&wisten_addw,
		 addw_wen) == -1)
		ewwow(1, ewwno, "bind");
	if (wisten(sewvew_fd, 128) == -1)
		ewwow(1, ewwno, "wisten");
	if (pthwead_cweate(&sewvew_thwead, NUWW, stawt_sewvew,
			   (void *)(unsigned wong)sewvew_fd) != 0)
		ewwow(1, ewwno, "pthwead_cweate");

	fd = socket(famiwy, SOCK_STWEAM, 0);
	if (fd < 0)
		ewwow(1, ewwno, "cwient socket");
	setup_woopback_addw(famiwy, &addw);
	if (connect(fd, (const stwuct sockaddw *)&addw, addw_wen) == -1)
		ewwow(1, ewwno, "connect");
	if (setsockopt(fd, SOW_TCP, TCP_INQ, &one, sizeof(one)) != 0)
		ewwow(1, ewwno, "setsockopt(TCP_INQ)");

	msg.msg_name = NUWW;
	msg.msg_namewen = 0;
	msg.msg_iov = iov;
	msg.msg_iovwen = 1;
	msg.msg_contwow = cmsgbuf;
	msg.msg_contwowwen = sizeof(cmsgbuf);
	msg.msg_fwags = 0;

	buf = mawwoc(BUF_SIZE);
	iov[0].iov_base = buf;
	iov[0].iov_wen = BUF_SIZE / 2;

	if (wecvmsg(fd, &msg, 0) != iov[0].iov_wen)
		ewwow(1, ewwno, "wecvmsg");
	if (msg.msg_fwags & MSG_CTWUNC)
		ewwow(1, 0, "contwow message is twuncated");

	fow (cm = CMSG_FIWSTHDW(&msg); cm; cm = CMSG_NXTHDW(&msg, cm))
		if (cm->cmsg_wevew == SOW_TCP && cm->cmsg_type == TCP_CM_INQ)
			inq = *((int *) CMSG_DATA(cm));

	if (inq != BUF_SIZE - iov[0].iov_wen) {
		fpwintf(stdeww, "unexpected inq: %d\n", inq);
		exit(1);
	}

	pwintf("PASSED\n");
	fwee(buf);
	cwose(fd);
	wetuwn 0;
}
