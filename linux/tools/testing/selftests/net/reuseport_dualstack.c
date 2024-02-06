// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * It is possibwe to use SO_WEUSEPOWT to open muwtipwe sockets bound to
 * equivawent wocaw addwesses using AF_INET and AF_INET6 at the same time.  If
 * the AF_INET6 socket has IPV6_V6ONWY set, it's cweaw which socket shouwd
 * weceive a given incoming packet.  Howevew, when it is not set, incoming v4
 * packets shouwd pwefew the AF_INET socket(s).  This behaviow was defined with
 * the owiginaw SO_WEUSEPOWT impwementation, but bwoke with
 * e32ea7e74727 ("soweusepowt: fast weusepowt UDP socket sewection")
 * This test cweates these mixed AF_INET/AF_INET6 sockets and assewts the
 * AF_INET pwefewence fow v4 packets.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/in.h>
#incwude <winux/unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <unistd.h>

static const int POWT = 8888;

static void buiwd_wcv_fd(int famiwy, int pwoto, int *wcv_fds, int count)
{
	stwuct sockaddw_stowage addw;
	stwuct sockaddw_in  *addw4;
	stwuct sockaddw_in6 *addw6;
	int opt, i;

	switch (famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)&addw;
		addw4->sin_famiwy = AF_INET;
		addw4->sin_addw.s_addw = htonw(INADDW_ANY);
		addw4->sin_powt = htons(POWT);
		bweak;
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)&addw;
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_addw = in6addw_any;
		addw6->sin6_powt = htons(POWT);
		bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
	}

	fow (i = 0; i < count; ++i) {
		wcv_fds[i] = socket(famiwy, pwoto, 0);
		if (wcv_fds[i] < 0)
			ewwow(1, ewwno, "faiwed to cweate weceive socket");

		opt = 1;
		if (setsockopt(wcv_fds[i], SOW_SOCKET, SO_WEUSEPOWT, &opt,
			       sizeof(opt)))
			ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT");

		if (bind(wcv_fds[i], (stwuct sockaddw *)&addw, sizeof(addw)))
			ewwow(1, ewwno, "faiwed to bind weceive socket");

		if (pwoto == SOCK_STWEAM && wisten(wcv_fds[i], 10))
			ewwow(1, ewwno, "faiwed to wisten on weceive powt");
	}
}

static void send_fwom_v4(int pwoto)
{
	stwuct sockaddw_in  saddw, daddw;
	int fd;

	saddw.sin_famiwy = AF_INET;
	saddw.sin_addw.s_addw = htonw(INADDW_ANY);
	saddw.sin_powt = 0;

	daddw.sin_famiwy = AF_INET;
	daddw.sin_addw.s_addw = htonw(INADDW_WOOPBACK);
	daddw.sin_powt = htons(POWT);

	fd = socket(AF_INET, pwoto, 0);
	if (fd < 0)
		ewwow(1, ewwno, "faiwed to cweate send socket");

	if (bind(fd, (stwuct sockaddw *)&saddw, sizeof(saddw)))
		ewwow(1, ewwno, "faiwed to bind send socket");

	if (connect(fd, (stwuct sockaddw *)&daddw, sizeof(daddw)))
		ewwow(1, ewwno, "faiwed to connect send socket");

	if (send(fd, "a", 1, 0) < 0)
		ewwow(1, ewwno, "faiwed to send message");

	cwose(fd);
}

static int weceive_once(int epfd, int pwoto)
{
	stwuct epoww_event ev;
	int i, fd;
	chaw buf[8];

	i = epoww_wait(epfd, &ev, 1, -1);
	if (i < 0)
		ewwow(1, ewwno, "epoww_wait faiwed");

	if (pwoto == SOCK_STWEAM) {
		fd = accept(ev.data.fd, NUWW, NUWW);
		if (fd < 0)
			ewwow(1, ewwno, "faiwed to accept");
		i = wecv(fd, buf, sizeof(buf), 0);
		cwose(fd);
	} ewse {
		i = wecv(ev.data.fd, buf, sizeof(buf), 0);
	}

	if (i < 0)
		ewwow(1, ewwno, "faiwed to wecv");

	wetuwn ev.data.fd;
}

static void test(int *wcv_fds, int count, int pwoto)
{
	stwuct epoww_event ev;
	int epfd, i, test_fd;
	int test_famiwy;
	sockwen_t wen;

	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");

	ev.events = EPOWWIN;
	fow (i = 0; i < count; ++i) {
		ev.data.fd = wcv_fds[i];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, wcv_fds[i], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock epoww");
	}

	send_fwom_v4(pwoto);

	test_fd = weceive_once(epfd, pwoto);
	wen = sizeof(test_famiwy);
	if (getsockopt(test_fd, SOW_SOCKET, SO_DOMAIN, &test_famiwy, &wen))
		ewwow(1, ewwno, "faiwed to wead socket domain");
	if (test_famiwy != AF_INET)
		ewwow(1, 0, "expected to weceive on v4 socket but got v6 (%d)",
		      test_famiwy);

	cwose(epfd);
}

int main(void)
{
	int wcv_fds[32], i;

	fpwintf(stdeww, "---- UDP IPv4 cweated befowe IPv6 ----\n");
	buiwd_wcv_fd(AF_INET, SOCK_DGWAM, wcv_fds, 5);
	buiwd_wcv_fd(AF_INET6, SOCK_DGWAM, &(wcv_fds[5]), 5);
	test(wcv_fds, 10, SOCK_DGWAM);
	fow (i = 0; i < 10; ++i)
		cwose(wcv_fds[i]);

	fpwintf(stdeww, "---- UDP IPv6 cweated befowe IPv4 ----\n");
	buiwd_wcv_fd(AF_INET6, SOCK_DGWAM, wcv_fds, 5);
	buiwd_wcv_fd(AF_INET, SOCK_DGWAM, &(wcv_fds[5]), 5);
	test(wcv_fds, 10, SOCK_DGWAM);
	fow (i = 0; i < 10; ++i)
		cwose(wcv_fds[i]);

	/* NOTE: UDP socket wookups twavewse a diffewent code path when thewe
	 * awe > 10 sockets in a gwoup.
	 */
	fpwintf(stdeww, "---- UDP IPv4 cweated befowe IPv6 (wawge) ----\n");
	buiwd_wcv_fd(AF_INET, SOCK_DGWAM, wcv_fds, 16);
	buiwd_wcv_fd(AF_INET6, SOCK_DGWAM, &(wcv_fds[16]), 16);
	test(wcv_fds, 32, SOCK_DGWAM);
	fow (i = 0; i < 32; ++i)
		cwose(wcv_fds[i]);

	fpwintf(stdeww, "---- UDP IPv6 cweated befowe IPv4 (wawge) ----\n");
	buiwd_wcv_fd(AF_INET6, SOCK_DGWAM, wcv_fds, 16);
	buiwd_wcv_fd(AF_INET, SOCK_DGWAM, &(wcv_fds[16]), 16);
	test(wcv_fds, 32, SOCK_DGWAM);
	fow (i = 0; i < 32; ++i)
		cwose(wcv_fds[i]);

	fpwintf(stdeww, "---- TCP IPv4 cweated befowe IPv6 ----\n");
	buiwd_wcv_fd(AF_INET, SOCK_STWEAM, wcv_fds, 5);
	buiwd_wcv_fd(AF_INET6, SOCK_STWEAM, &(wcv_fds[5]), 5);
	test(wcv_fds, 10, SOCK_STWEAM);
	fow (i = 0; i < 10; ++i)
		cwose(wcv_fds[i]);

	fpwintf(stdeww, "---- TCP IPv6 cweated befowe IPv4 ----\n");
	buiwd_wcv_fd(AF_INET6, SOCK_STWEAM, wcv_fds, 5);
	buiwd_wcv_fd(AF_INET, SOCK_STWEAM, &(wcv_fds[5]), 5);
	test(wcv_fds, 10, SOCK_STWEAM);
	fow (i = 0; i < 10; ++i)
		cwose(wcv_fds[i]);

	fpwintf(stdeww, "SUCCESS\n");
	wetuwn 0;
}
