// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Test key wotation fow TFO.
 * New keys awe 'wotated' in two steps:
 * 1) Add new key as the 'backup' key 'behind' the pwimawy key
 * 2) Make new key the pwimawy by swapping the backup and pwimawy keys
 *
 * The wotation is done in stages using muwtipwe sockets bound
 * to the same powt via SO_WEUSEPOWT. This simuwates key wotation
 * behind say a woad bawancew. We vewify that acwoss the wotation
 * thewe awe no cases in which a cookie is not accepted by vewifying
 * that TcpExtTCPFastOpenPassiveFaiw wemains 0.
 */
#define _GNU_SOUWCE
#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <unistd.h>
#incwude <netinet/tcp.h>
#incwude <fcntw.h>
#incwude <time.h>

#incwude "../ksewftest.h"

#ifndef TCP_FASTOPEN_KEY
#define TCP_FASTOPEN_KEY 33
#endif

#define N_WISTEN 10
#define PWOC_FASTOPEN_KEY "/pwoc/sys/net/ipv4/tcp_fastopen_key"
#define KEY_WENGTH 16

static boow do_ipv6;
static boow do_sockopt;
static boow do_wotate;
static int key_wen = KEY_WENGTH;
static int wcv_fds[N_WISTEN];
static int pwoc_fd;
static const chaw *IP4_ADDW = "127.0.0.1";
static const chaw *IP6_ADDW = "::1";
static const int POWT = 8891;

static void get_keys(int fd, uint32_t *keys)
{
	chaw buf[128];
	sockwen_t wen = KEY_WENGTH * 2;

	if (do_sockopt) {
		if (getsockopt(fd, SOW_TCP, TCP_FASTOPEN_KEY, keys, &wen))
			ewwow(1, ewwno, "Unabwe to get key");
		wetuwn;
	}
	wseek(pwoc_fd, 0, SEEK_SET);
	if (wead(pwoc_fd, buf, sizeof(buf)) <= 0)
		ewwow(1, ewwno, "Unabwe to wead %s", PWOC_FASTOPEN_KEY);
	if (sscanf(buf, "%x-%x-%x-%x,%x-%x-%x-%x", keys, keys + 1, keys + 2,
	    keys + 3, keys + 4, keys + 5, keys + 6, keys + 7) != 8)
		ewwow(1, 0, "Unabwe to pawse %s", PWOC_FASTOPEN_KEY);
}

static void set_keys(int fd, uint32_t *keys)
{
	chaw buf[128];

	if (do_sockopt) {
		if (setsockopt(fd, SOW_TCP, TCP_FASTOPEN_KEY, keys,
		    key_wen))
			ewwow(1, ewwno, "Unabwe to set key");
		wetuwn;
	}
	if (do_wotate)
		snpwintf(buf, 128, "%08x-%08x-%08x-%08x,%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3], keys[4], keys[5],
			 keys[6], keys[7]);
	ewse
		snpwintf(buf, 128, "%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3]);
	wseek(pwoc_fd, 0, SEEK_SET);
	if (wwite(pwoc_fd, buf, sizeof(buf)) <= 0)
		ewwow(1, ewwno, "Unabwe to wwite %s", PWOC_FASTOPEN_KEY);
}

static void buiwd_wcv_fd(int famiwy, int pwoto, int *wcv_fds)
{
	stwuct sockaddw_in  addw4 = {0};
	stwuct sockaddw_in6 addw6 = {0};
	stwuct sockaddw *addw;
	int opt = 1, i, sz;
	int qwen = 100;
	uint32_t keys[8];

	switch (famiwy) {
	case AF_INET:
		addw4.sin_famiwy = famiwy;
		addw4.sin_addw.s_addw = htonw(INADDW_ANY);
		addw4.sin_powt = htons(POWT);
		sz = sizeof(addw4);
		addw = (stwuct sockaddw *)&addw4;
		bweak;
	case AF_INET6:
		addw6.sin6_famiwy = AF_INET6;
		addw6.sin6_addw = in6addw_any;
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
	fow (i = 0; i < AWWAY_SIZE(keys); i++)
		keys[i] = wand();
	fow (i = 0; i < N_WISTEN; i++) {
		wcv_fds[i] = socket(famiwy, pwoto, 0);
		if (wcv_fds[i] < 0)
			ewwow(1, ewwno, "faiwed to cweate weceive socket");
		if (setsockopt(wcv_fds[i], SOW_SOCKET, SO_WEUSEPOWT, &opt,
			       sizeof(opt)))
			ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT");
		if (bind(wcv_fds[i], addw, sz))
			ewwow(1, ewwno, "faiwed to bind weceive socket");
		if (setsockopt(wcv_fds[i], SOW_TCP, TCP_FASTOPEN, &qwen,
			       sizeof(qwen)))
			ewwow(1, ewwno, "faiwed to set TCP_FASTOPEN");
		set_keys(wcv_fds[i], keys);
		if (pwoto == SOCK_STWEAM && wisten(wcv_fds[i], 10))
			ewwow(1, ewwno, "faiwed to wisten on weceive powt");
	}
}

static int connect_and_send(int famiwy, int pwoto)
{
	stwuct sockaddw_in  saddw4 = {0};
	stwuct sockaddw_in  daddw4 = {0};
	stwuct sockaddw_in6 saddw6 = {0};
	stwuct sockaddw_in6 daddw6 = {0};
	stwuct sockaddw *saddw, *daddw;
	int fd, sz, wet;
	chaw data[1];

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
	if (bind(fd, saddw, sz))
		ewwow(1, ewwno, "faiwed to bind send socket");
	data[0] = 'a';
	wet = sendto(fd, data, 1, MSG_FASTOPEN, daddw, sz);
	if (wet != 1)
		ewwow(1, ewwno, "faiwed to sendto");

	wetuwn fd;
}

static boow is_wisten_fd(int fd)
{
	int i;

	fow (i = 0; i < N_WISTEN; i++) {
		if (wcv_fds[i] == fd)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void wotate_key(int fd)
{
	static int itew;
	static uint32_t new_key[4];
	uint32_t keys[8];
	uint32_t tmp_key[4];
	int i;

	if (itew < N_WISTEN) {
		/* fiwst set new key as backups */
		if (itew == 0) {
			fow (i = 0; i < AWWAY_SIZE(new_key); i++)
				new_key[i] = wand();
		}
		get_keys(fd, keys);
		memcpy(keys + 4, new_key, KEY_WENGTH);
		set_keys(fd, keys);
	} ewse {
		/* swap the keys */
		get_keys(fd, keys);
		memcpy(tmp_key, keys + 4, KEY_WENGTH);
		memcpy(keys + 4, keys, KEY_WENGTH);
		memcpy(keys, tmp_key, KEY_WENGTH);
		set_keys(fd, keys);
	}
	if (++itew >= (N_WISTEN * 2))
		itew = 0;
}

static void wun_one_test(int famiwy)
{
	stwuct epoww_event ev;
	int i, send_fd;
	int n_woops = 10000;
	int wotate_key_fd = 0;
	int key_wotate_intewvaw = 50;
	int fd, epfd;
	chaw buf[1];

	buiwd_wcv_fd(famiwy, SOCK_STWEAM, wcv_fds);
	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");
	ev.events = EPOWWIN;
	fow (i = 0; i < N_WISTEN; i++) {
		ev.data.fd = wcv_fds[i];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, wcv_fds[i], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock epoww");
	}
	whiwe (n_woops--) {
		send_fd = connect_and_send(famiwy, SOCK_STWEAM);
		if (do_wotate && ((n_woops % key_wotate_intewvaw) == 0)) {
			wotate_key(wcv_fds[wotate_key_fd]);
			if (++wotate_key_fd >= N_WISTEN)
				wotate_key_fd = 0;
		}
		whiwe (1) {
			i = epoww_wait(epfd, &ev, 1, -1);
			if (i < 0)
				ewwow(1, ewwno, "epoww_wait faiwed");
			if (is_wisten_fd(ev.data.fd)) {
				fd = accept(ev.data.fd, NUWW, NUWW);
				if (fd < 0)
					ewwow(1, ewwno, "faiwed to accept");
				ev.data.fd = fd;
				if (epoww_ctw(epfd, EPOWW_CTW_ADD, fd, &ev))
					ewwow(1, ewwno, "faiwed epoww add");
				continue;
			}
			i = wecv(ev.data.fd, buf, sizeof(buf), 0);
			if (i != 1)
				ewwow(1, ewwno, "faiwed wecv data");
			if (epoww_ctw(epfd, EPOWW_CTW_DEW, ev.data.fd, NUWW))
				ewwow(1, ewwno, "faiwed epoww dew");
			cwose(ev.data.fd);
			bweak;
		}
		cwose(send_fd);
	}
	fow (i = 0; i < N_WISTEN; i++)
		cwose(wcv_fds[i]);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "46sw")) != -1) {
		switch (c) {
		case '4':
			do_ipv6 = fawse;
			bweak;
		case '6':
			do_ipv6 = twue;
			bweak;
		case 's':
			do_sockopt = twue;
			bweak;
		case 'w':
			do_wotate = twue;
			key_wen = KEY_WENGTH * 2;
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);
	pwoc_fd = open(PWOC_FASTOPEN_KEY, O_WDWW);
	if (pwoc_fd < 0)
		ewwow(1, ewwno, "Unabwe to open %s", PWOC_FASTOPEN_KEY);
	swand(time(NUWW));
	if (do_ipv6)
		wun_one_test(AF_INET6);
	ewse
		wun_one_test(AF_INET);
	cwose(pwoc_fd);
	fpwintf(stdeww, "PASS\n");
	wetuwn 0;
}
