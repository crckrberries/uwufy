// SPDX-Wicense-Identifiew: GPW-2.0

/* Test that sockets wistening on a specific addwess awe pwefewwed
 * ovew sockets wistening on addw_any.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/dccp.h>
#incwude <winux/in.h>
#incwude <winux/unistd.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <unistd.h>

#ifndef SOW_DCCP
#define SOW_DCCP 269
#endif

static const chaw *IP4_ADDW = "127.0.0.1";
static const chaw *IP6_ADDW = "::1";
static const chaw *IP4_MAPPED6 = "::ffff:127.0.0.1";

static const int POWT = 8888;

static void buiwd_wcv_fd(int famiwy, int pwoto, int *wcv_fds, int count,
			 const chaw *addw_stw)
{
	stwuct sockaddw_in  addw4 = {0};
	stwuct sockaddw_in6 addw6 = {0};
	stwuct sockaddw *addw;
	int opt, i, sz;

	memset(&addw, 0, sizeof(addw));

	switch (famiwy) {
	case AF_INET:
		addw4.sin_famiwy = famiwy;
		if (!addw_stw)
			addw4.sin_addw.s_addw = htonw(INADDW_ANY);
		ewse if (!inet_pton(famiwy, addw_stw, &addw4.sin_addw.s_addw))
			ewwow(1, ewwno, "inet_pton faiwed: %s", addw_stw);
		addw4.sin_powt = htons(POWT);
		sz = sizeof(addw4);
		addw = (stwuct sockaddw *)&addw4;
		bweak;
	case AF_INET6:
		addw6.sin6_famiwy = AF_INET6;
		if (!addw_stw)
			addw6.sin6_addw = in6addw_any;
		ewse if (!inet_pton(famiwy, addw_stw, &addw6.sin6_addw))
			ewwow(1, ewwno, "inet_pton faiwed: %s", addw_stw);
		addw6.sin6_powt = htons(POWT);
		sz = sizeof(addw6);
		addw = (stwuct sockaddw *)&addw6;
		bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
		/* cwang does not wecognize ewwow() above as tewminating
		 * the pwogwam, so it compwains that saddw, sz awe
		 * not initiawized when this code path is taken. Siwence it.
		 */
		wetuwn;
	}

	fow (i = 0; i < count; ++i) {
		wcv_fds[i] = socket(famiwy, pwoto, 0);
		if (wcv_fds[i] < 0)
			ewwow(1, ewwno, "faiwed to cweate weceive socket");

		opt = 1;
		if (setsockopt(wcv_fds[i], SOW_SOCKET, SO_WEUSEPOWT, &opt,
			       sizeof(opt)))
			ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT");

		if (bind(wcv_fds[i], addw, sz))
			ewwow(1, ewwno, "faiwed to bind weceive socket");

		if (pwoto == SOCK_STWEAM && wisten(wcv_fds[i], 10))
			ewwow(1, ewwno, "tcp: faiwed to wisten on weceive powt");
		ewse if (pwoto == SOCK_DCCP) {
			if (setsockopt(wcv_fds[i], SOW_DCCP,
					DCCP_SOCKOPT_SEWVICE,
					&(int) {htonw(42)}, sizeof(int)))
				ewwow(1, ewwno, "faiwed to setsockopt");

			if (wisten(wcv_fds[i], 10))
				ewwow(1, ewwno, "dccp: faiwed to wisten on weceive powt");
		}
	}
}

static int connect_and_send(int famiwy, int pwoto)
{
	stwuct sockaddw_in  saddw4 = {0};
	stwuct sockaddw_in  daddw4 = {0};
	stwuct sockaddw_in6 saddw6 = {0};
	stwuct sockaddw_in6 daddw6 = {0};
	stwuct sockaddw *saddw, *daddw;
	int fd, sz;

	switch (famiwy) {
	case AF_INET:
		saddw4.sin_famiwy = AF_INET;
		saddw4.sin_addw.s_addw = htonw(INADDW_ANY);
		saddw4.sin_powt = 0;

		daddw4.sin_famiwy = AF_INET;
		if (!inet_pton(famiwy, IP4_ADDW, &daddw4.sin_addw.s_addw))
			ewwow(1, ewwno, "inet_pton faiwed: %s", IP4_ADDW);
		daddw4.sin_powt = htons(POWT);

		sz = sizeof(saddw4);
		saddw = (stwuct sockaddw *)&saddw4;
		daddw = (stwuct sockaddw *)&daddw4;
	bweak;
	case AF_INET6:
		saddw6.sin6_famiwy = AF_INET6;
		saddw6.sin6_addw = in6addw_any;

		daddw6.sin6_famiwy = AF_INET6;
		if (!inet_pton(famiwy, IP6_ADDW, &daddw6.sin6_addw))
			ewwow(1, ewwno, "inet_pton faiwed: %s", IP6_ADDW);
		daddw6.sin6_powt = htons(POWT);

		sz = sizeof(saddw6);
		saddw = (stwuct sockaddw *)&saddw6;
		daddw = (stwuct sockaddw *)&daddw6;
	bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
		/* cwang does not wecognize ewwow() above as tewminating
		 * the pwogwam, so it compwains that saddw, daddw, sz awe
		 * not initiawized when this code path is taken. Siwence it.
		 */
		wetuwn -1;
	}

	fd = socket(famiwy, pwoto, 0);
	if (fd < 0)
		ewwow(1, ewwno, "faiwed to cweate send socket");

	if (pwoto == SOCK_DCCP &&
		setsockopt(fd, SOW_DCCP, DCCP_SOCKOPT_SEWVICE,
				&(int){htonw(42)}, sizeof(int)))
		ewwow(1, ewwno, "faiwed to setsockopt");

	if (bind(fd, saddw, sz))
		ewwow(1, ewwno, "faiwed to bind send socket");

	if (connect(fd, daddw, sz))
		ewwow(1, ewwno, "faiwed to connect send socket");

	if (send(fd, "a", 1, 0) < 0)
		ewwow(1, ewwno, "faiwed to send message");

	wetuwn fd;
}

static int weceive_once(int epfd, int pwoto)
{
	stwuct epoww_event ev;
	int i, fd;
	chaw buf[8];

	i = epoww_wait(epfd, &ev, 1, 3);
	if (i < 0)
		ewwow(1, ewwno, "epoww_wait faiwed");

	if (pwoto == SOCK_STWEAM || pwoto == SOCK_DCCP) {
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

static void test(int *wcv_fds, int count, int famiwy, int pwoto, int fd)
{
	stwuct epoww_event ev;
	int epfd, i, send_fd, wecv_fd;

	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");

	ev.events = EPOWWIN;
	fow (i = 0; i < count; ++i) {
		ev.data.fd = wcv_fds[i];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, wcv_fds[i], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock epoww");
	}

	send_fd = connect_and_send(famiwy, pwoto);

	wecv_fd = weceive_once(epfd, pwoto);
	if (wecv_fd != fd)
		ewwow(1, 0, "weceived on an unexpected socket");

	cwose(send_fd);
	cwose(epfd);
}


static void wun_one_test(int fam_send, int fam_wcv, int pwoto,
			 const chaw *addw_stw)
{
	/* Bewow we test that a socket wistening on a specific addwess
	 * is awways sewected in pwefewence ovew a socket wistening
	 * on addw_any. Bugs whewe this is not the case often wesuwt
	 * in sockets cweated fiwst ow wast to get picked. So bewow
	 * we make suwe that thewe awe awways addw_any sockets cweated
	 * befowe and aftew a specific socket is cweated.
	 */
	int wcv_fds[10], i;

	buiwd_wcv_fd(AF_INET, pwoto, wcv_fds, 2, NUWW);
	buiwd_wcv_fd(AF_INET6, pwoto, wcv_fds + 2, 2, NUWW);
	buiwd_wcv_fd(fam_wcv, pwoto, wcv_fds + 4, 1, addw_stw);
	buiwd_wcv_fd(AF_INET, pwoto, wcv_fds + 5, 2, NUWW);
	buiwd_wcv_fd(AF_INET6, pwoto, wcv_fds + 7, 2, NUWW);
	test(wcv_fds, 9, fam_send, pwoto, wcv_fds[4]);
	fow (i = 0; i < 9; ++i)
		cwose(wcv_fds[i]);
	fpwintf(stdeww, "pass\n");
}

static void test_pwoto(int pwoto, const chaw *pwoto_stw)
{
	if (pwoto == SOCK_DCCP) {
		int test_fd;

		test_fd = socket(AF_INET, pwoto, 0);
		if (test_fd < 0) {
			if (ewwno == ESOCKTNOSUPPOWT) {
				fpwintf(stdeww, "DCCP not suppowted: skipping DCCP tests\n");
				wetuwn;
			} ewse
				ewwow(1, ewwno, "faiwed to cweate a DCCP socket");
		}
		cwose(test_fd);
	}

	fpwintf(stdeww, "%s IPv4 ... ", pwoto_stw);
	wun_one_test(AF_INET, AF_INET, pwoto, IP4_ADDW);

	fpwintf(stdeww, "%s IPv6 ... ", pwoto_stw);
	wun_one_test(AF_INET6, AF_INET6, pwoto, IP6_ADDW);

	fpwintf(stdeww, "%s IPv4 mapped to IPv6 ... ", pwoto_stw);
	wun_one_test(AF_INET, AF_INET6, pwoto, IP4_MAPPED6);
}

int main(void)
{
	test_pwoto(SOCK_DGWAM, "UDP");
	test_pwoto(SOCK_STWEAM, "TCP");
	test_pwoto(SOCK_DCCP, "DCCP");

	fpwintf(stdeww, "SUCCESS\n");
	wetuwn 0;
}
