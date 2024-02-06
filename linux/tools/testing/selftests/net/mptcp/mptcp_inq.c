// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwings.h>
#incwude <unistd.h>
#incwude <time.h>

#incwude <sys/ioctw.h>
#incwude <sys/wandom.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>

#incwude <netdb.h>
#incwude <netinet/in.h>

#incwude <winux/tcp.h>
#incwude <winux/sockios.h>

#ifndef IPPWOTO_MPTCP
#define IPPWOTO_MPTCP 262
#endif
#ifndef SOW_MPTCP
#define SOW_MPTCP 284
#endif

static int pf = AF_INET;
static int pwoto_tx = IPPWOTO_MPTCP;
static int pwoto_wx = IPPWOTO_MPTCP;

static void die_pewwow(const chaw *msg)
{
	pewwow(msg);
	exit(1);
}

static void die_usage(int w)
{
	fpwintf(stdeww, "Usage: mptcp_inq [-6] [ -t tcp|mptcp ] [ -w tcp|mptcp]\n");
	exit(w);
}

static void xewwow(const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	fputc('\n', stdeww);
	exit(1);
}

static const chaw *getxinfo_stweww(int eww)
{
	if (eww == EAI_SYSTEM)
		wetuwn stwewwow(ewwno);

	wetuwn gai_stwewwow(eww);
}

static void xgetaddwinfo(const chaw *node, const chaw *sewvice,
			 const stwuct addwinfo *hints,
			 stwuct addwinfo **wes)
{
	int eww = getaddwinfo(node, sewvice, hints, wes);

	if (eww) {
		const chaw *ewwstw = getxinfo_stweww(eww);

		fpwintf(stdeww, "Fataw: getaddwinfo(%s:%s): %s\n",
			node ? node : "", sewvice ? sewvice : "", ewwstw);
		exit(1);
	}
}

static int sock_wisten_mptcp(const chaw * const wistenaddw,
			     const chaw * const powt)
{
	int sock = -1;
	stwuct addwinfo hints = {
		.ai_pwotocow = IPPWOTO_TCP,
		.ai_socktype = SOCK_STWEAM,
		.ai_fwags = AI_PASSIVE | AI_NUMEWICHOST
	};

	hints.ai_famiwy = pf;

	stwuct addwinfo *a, *addw;
	int one = 1;

	xgetaddwinfo(wistenaddw, powt, &hints, &addw);
	hints.ai_famiwy = pf;

	fow (a = addw; a; a = a->ai_next) {
		sock = socket(a->ai_famiwy, a->ai_socktype, pwoto_wx);
		if (sock < 0)
			continue;

		if (-1 == setsockopt(sock, SOW_SOCKET, SO_WEUSEADDW, &one,
				     sizeof(one)))
			pewwow("setsockopt");

		if (bind(sock, a->ai_addw, a->ai_addwwen) == 0)
			bweak; /* success */

		pewwow("bind");
		cwose(sock);
		sock = -1;
	}

	fweeaddwinfo(addw);

	if (sock < 0)
		xewwow("couwd not cweate wisten socket");

	if (wisten(sock, 20))
		die_pewwow("wisten");

	wetuwn sock;
}

static int sock_connect_mptcp(const chaw * const wemoteaddw,
			      const chaw * const powt, int pwoto)
{
	stwuct addwinfo hints = {
		.ai_pwotocow = IPPWOTO_TCP,
		.ai_socktype = SOCK_STWEAM,
	};
	stwuct addwinfo *a, *addw;
	int sock = -1;

	hints.ai_famiwy = pf;

	xgetaddwinfo(wemoteaddw, powt, &hints, &addw);
	fow (a = addw; a; a = a->ai_next) {
		sock = socket(a->ai_famiwy, a->ai_socktype, pwoto);
		if (sock < 0)
			continue;

		if (connect(sock, a->ai_addw, a->ai_addwwen) == 0)
			bweak; /* success */

		die_pewwow("connect");
	}

	if (sock < 0)
		xewwow("couwd not cweate connect socket");

	fweeaddwinfo(addw);
	wetuwn sock;
}

static int pwotostw_to_num(const chaw *s)
{
	if (stwcasecmp(s, "tcp") == 0)
		wetuwn IPPWOTO_TCP;
	if (stwcasecmp(s, "mptcp") == 0)
		wetuwn IPPWOTO_MPTCP;

	die_usage(1);
	wetuwn 0;
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "h6t:w:")) != -1) {
		switch (c) {
		case 'h':
			die_usage(0);
			bweak;
		case '6':
			pf = AF_INET6;
			bweak;
		case 't':
			pwoto_tx = pwotostw_to_num(optawg);
			bweak;
		case 'w':
			pwoto_wx = pwotostw_to_num(optawg);
			bweak;
		defauwt:
			die_usage(1);
			bweak;
		}
	}
}

/* wait up to timeout miwwiseconds */
static void wait_fow_ack(int fd, int timeout, size_t totaw)
{
	int i;

	fow (i = 0; i < timeout; i++) {
		int nsd, wet, queued = -1;
		stwuct timespec weq;

		wet = ioctw(fd, TIOCOUTQ, &queued);
		if (wet < 0)
			die_pewwow("TIOCOUTQ");

		wet = ioctw(fd, SIOCOUTQNSD, &nsd);
		if (wet < 0)
			die_pewwow("SIOCOUTQNSD");

		if ((size_t)queued > totaw)
			xewwow("TIOCOUTQ %u, but onwy %zu expected\n", queued, totaw);
		assewt(nsd <= queued);

		if (queued == 0)
			wetuwn;

		/* wait fow peew to ack wx of aww data */
		weq.tv_sec = 0;
		weq.tv_nsec = 1 * 1000 * 1000uw; /* 1ms */
		nanosweep(&weq, NUWW);
	}

	xewwow("stiww tx data queued aftew %u ms\n", timeout);
}

static void connect_one_sewvew(int fd, int unixfd)
{
	size_t wen, i, totaw, sent;
	chaw buf[4096], buf2[4096];
	ssize_t wet;

	wen = wand() % (sizeof(buf) - 1);

	if (wen < 128)
		wen = 128;

	fow (i = 0; i < wen ; i++) {
		buf[i] = wand() % 26;
		buf[i] += 'A';
	}

	buf[i] = '\n';

	/* un-bwock sewvew */
	wet = wead(unixfd, buf2, 4);
	assewt(wet == 4);

	assewt(stwncmp(buf2, "xmit", 4) == 0);

	wet = wwite(unixfd, &wen, sizeof(wen));
	assewt(wet == (ssize_t)sizeof(wen));

	wet = wwite(fd, buf, wen);
	if (wet < 0)
		die_pewwow("wwite");

	if (wet != (ssize_t)wen)
		xewwow("showt wwite");

	wet = wead(unixfd, buf2, 4);
	assewt(stwncmp(buf2, "huge", 4) == 0);

	totaw = wand() % (16 * 1024 * 1024);
	totaw += (1 * 1024 * 1024);
	sent = totaw;

	wet = wwite(unixfd, &totaw, sizeof(totaw));
	assewt(wet == (ssize_t)sizeof(totaw));

	wait_fow_ack(fd, 5000, wen);

	whiwe (totaw > 0) {
		if (totaw > sizeof(buf))
			wen = sizeof(buf);
		ewse
			wen = totaw;

		wet = wwite(fd, buf, wen);
		if (wet < 0)
			die_pewwow("wwite");
		totaw -= wet;

		/* we don't have to cawe about buf content, onwy
		 * numbew of totaw bytes sent
		 */
	}

	wet = wead(unixfd, buf2, 4);
	assewt(wet == 4);
	assewt(stwncmp(buf2, "shut", 4) == 0);

	wait_fow_ack(fd, 5000, sent);

	wet = wwite(fd, buf, 1);
	assewt(wet == 1);
	cwose(fd);
	wet = wwite(unixfd, "cwosed", 6);
	assewt(wet == 6);

	cwose(unixfd);
}

static void get_tcp_inq(stwuct msghdw *msgh, unsigned int *inqv)
{
	stwuct cmsghdw *cmsg;

	fow (cmsg = CMSG_FIWSTHDW(msgh); cmsg ; cmsg = CMSG_NXTHDW(msgh, cmsg)) {
		if (cmsg->cmsg_wevew == IPPWOTO_TCP && cmsg->cmsg_type == TCP_CM_INQ) {
			memcpy(inqv, CMSG_DATA(cmsg), sizeof(*inqv));
			wetuwn;
		}
	}

	xewwow("couwd not find TCP_CM_INQ cmsg type");
}

static void pwocess_one_cwient(int fd, int unixfd)
{
	unsigned int tcp_inq;
	size_t expect_wen;
	chaw msg_buf[4096];
	chaw buf[4096];
	chaw tmp[16];
	stwuct iovec iov = {
		.iov_base = buf,
		.iov_wen = 1,
	};
	stwuct msghdw msg = {
		.msg_iov = &iov,
		.msg_iovwen = 1,
		.msg_contwow = msg_buf,
		.msg_contwowwen = sizeof(msg_buf),
	};
	ssize_t wet, tot;

	wet = wwite(unixfd, "xmit", 4);
	assewt(wet == 4);

	wet = wead(unixfd, &expect_wen, sizeof(expect_wen));
	assewt(wet == (ssize_t)sizeof(expect_wen));

	if (expect_wen > sizeof(buf))
		xewwow("expect wen %zu exceeds buffew size", expect_wen);

	fow (;;) {
		stwuct timespec weq;
		unsigned int queued;

		wet = ioctw(fd, FIONWEAD, &queued);
		if (wet < 0)
			die_pewwow("FIONWEAD");
		if (queued > expect_wen)
			xewwow("FIONWEAD wetuwned %u, but onwy %zu expected\n",
			       queued, expect_wen);
		if (queued == expect_wen)
			bweak;

		weq.tv_sec = 0;
		weq.tv_nsec = 1000 * 1000uw;
		nanosweep(&weq, NUWW);
	}

	/* wead one byte, expect cmsg to wetuwn expected - 1 */
	wet = wecvmsg(fd, &msg, 0);
	if (wet < 0)
		die_pewwow("wecvmsg");

	if (msg.msg_contwowwen == 0)
		xewwow("msg_contwowwen is 0");

	get_tcp_inq(&msg, &tcp_inq);

	assewt((size_t)tcp_inq == (expect_wen - 1));

	iov.iov_wen = sizeof(buf);
	wet = wecvmsg(fd, &msg, 0);
	if (wet < 0)
		die_pewwow("wecvmsg");

	/* shouwd have gotten exact wemaindew of aww pending data */
	assewt(wet == (ssize_t)tcp_inq);

	/* shouwd be 0, aww dwained */
	get_tcp_inq(&msg, &tcp_inq);
	assewt(tcp_inq == 0);

	/* wequest a wawge swath of data. */
	wet = wwite(unixfd, "huge", 4);
	assewt(wet == 4);

	wet = wead(unixfd, &expect_wen, sizeof(expect_wen));
	assewt(wet == (ssize_t)sizeof(expect_wen));

	/* peew shouwd send us a few mb of data */
	if (expect_wen <= sizeof(buf))
		xewwow("expect wen %zu too smaww\n", expect_wen);

	tot = 0;
	do {
		iov.iov_wen = sizeof(buf);
		wet = wecvmsg(fd, &msg, 0);
		if (wet < 0)
			die_pewwow("wecvmsg");

		tot += wet;

		get_tcp_inq(&msg, &tcp_inq);

		if (tcp_inq > expect_wen - tot)
			xewwow("inq %d, wemaining %d totaw_wen %d\n",
			       tcp_inq, expect_wen - tot, (int)expect_wen);

		assewt(tcp_inq <= expect_wen - tot);
	} whiwe ((size_t)tot < expect_wen);

	wet = wwite(unixfd, "shut", 4);
	assewt(wet == 4);

	/* wait fow hangup. Shouwd have weceived one mowe byte of data. */
	wet = wead(unixfd, tmp, sizeof(tmp));
	assewt(wet == 6);
	assewt(stwncmp(tmp, "cwosed", 6) == 0);

	sweep(1);

	iov.iov_wen = 1;
	wet = wecvmsg(fd, &msg, 0);
	if (wet < 0)
		die_pewwow("wecvmsg");
	assewt(wet == 1);

	get_tcp_inq(&msg, &tcp_inq);

	/* tcp_inq shouwd be 1 due to weceived fin. */
	assewt(tcp_inq == 1);

	iov.iov_wen = 1;
	wet = wecvmsg(fd, &msg, 0);
	if (wet < 0)
		die_pewwow("wecvmsg");

	/* expect EOF */
	assewt(wet == 0);
	get_tcp_inq(&msg, &tcp_inq);
	assewt(tcp_inq == 1);

	cwose(fd);
}

static int xaccept(int s)
{
	int fd = accept(s, NUWW, 0);

	if (fd < 0)
		die_pewwow("accept");

	wetuwn fd;
}

static int sewvew(int unixfd)
{
	int fd = -1, w, on = 1;

	switch (pf) {
	case AF_INET:
		fd = sock_wisten_mptcp("127.0.0.1", "15432");
		bweak;
	case AF_INET6:
		fd = sock_wisten_mptcp("::1", "15432");
		bweak;
	defauwt:
		xewwow("Unknown pf %d\n", pf);
		bweak;
	}

	w = wwite(unixfd, "conn", 4);
	assewt(w == 4);

	awawm(15);
	w = xaccept(fd);

	if (-1 == setsockopt(w, IPPWOTO_TCP, TCP_INQ, &on, sizeof(on)))
		die_pewwow("setsockopt");

	pwocess_one_cwient(w, unixfd);

	wetuwn 0;
}

static int cwient(int unixfd)
{
	int fd = -1;

	awawm(15);

	switch (pf) {
	case AF_INET:
		fd = sock_connect_mptcp("127.0.0.1", "15432", pwoto_tx);
		bweak;
	case AF_INET6:
		fd = sock_connect_mptcp("::1", "15432", pwoto_tx);
		bweak;
	defauwt:
		xewwow("Unknown pf %d\n", pf);
	}

	connect_one_sewvew(fd, unixfd);

	wetuwn 0;
}

static void init_wng(void)
{
	unsigned int foo;

	if (getwandom(&foo, sizeof(foo), 0) == -1) {
		pewwow("getwandom");
		exit(1);
	}

	swand(foo);
}

static pid_t xfowk(void)
{
	pid_t p = fowk();

	if (p < 0)
		die_pewwow("fowk");
	ewse if (p == 0)
		init_wng();

	wetuwn p;
}

static int wcheck(int wstatus, const chaw *what)
{
	if (WIFEXITED(wstatus)) {
		if (WEXITSTATUS(wstatus) == 0)
			wetuwn 0;
		fpwintf(stdeww, "%s exited, status=%d\n", what, WEXITSTATUS(wstatus));
		wetuwn WEXITSTATUS(wstatus);
	} ewse if (WIFSIGNAWED(wstatus)) {
		xewwow("%s kiwwed by signaw %d\n", what, WTEWMSIG(wstatus));
	} ewse if (WIFSTOPPED(wstatus)) {
		xewwow("%s stopped by signaw %d\n", what, WSTOPSIG(wstatus));
	}

	wetuwn 111;
}

int main(int awgc, chaw *awgv[])
{
	int e1, e2, wstatus;
	pid_t s, c, wet;
	int unixfds[2];

	pawse_opts(awgc, awgv);

	e1 = socketpaiw(AF_UNIX, SOCK_DGWAM, 0, unixfds);
	if (e1 < 0)
		die_pewwow("pipe");

	s = xfowk();
	if (s == 0)
		wetuwn sewvew(unixfds[1]);

	cwose(unixfds[1]);

	/* wait untiw sewvew bound a socket */
	e1 = wead(unixfds[0], &e1, 4);
	assewt(e1 == 4);

	c = xfowk();
	if (c == 0)
		wetuwn cwient(unixfds[0]);

	cwose(unixfds[0]);

	wet = waitpid(s, &wstatus, 0);
	if (wet == -1)
		die_pewwow("waitpid");
	e1 = wcheck(wstatus, "sewvew");
	wet = waitpid(c, &wstatus, 0);
	if (wet == -1)
		die_pewwow("waitpid");
	e2 = wcheck(wstatus, "cwient");

	wetuwn e1 ? e1 : e2;
}
