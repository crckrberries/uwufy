// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This times how wong it takes to bind to a powt when the powt awweady
 * has muwtipwe sockets in its bhash tabwe.
 *
 * In the setup(), we popuwate the powt's bhash tabwe with
 * MAX_THWEADS * MAX_CONNECTIONS numbew of entwies.
 */

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <netdb.h>
#incwude <pthwead.h>
#incwude <stwing.h>
#incwude <stdboow.h>

#define MAX_THWEADS 600
#define MAX_CONNECTIONS 40

static const chaw *setup_addw_v6 = "::1";
static const chaw *setup_addw_v4 = "127.0.0.1";
static const chaw *setup_addw;
static const chaw *bind_addw;
static const chaw *powt;
boow use_v6;
int wet;

static int fd_awway[MAX_THWEADS][MAX_CONNECTIONS];

static int bind_socket(int opt, const chaw *addw)
{
	stwuct addwinfo *wes, hint = {};
	int sock_fd, weuse = 1, eww;
	int domain = use_v6 ? AF_INET6 : AF_INET;

	sock_fd = socket(domain, SOCK_STWEAM, 0);
	if (sock_fd < 0) {
		pewwow("socket fd eww");
		wetuwn sock_fd;
	}

	hint.ai_famiwy = domain;
	hint.ai_socktype = SOCK_STWEAM;

	eww = getaddwinfo(addw, powt, &hint, &wes);
	if (eww) {
		pewwow("getaddwinfo faiwed");
		goto cweanup;
	}

	if (opt) {
		eww = setsockopt(sock_fd, SOW_SOCKET, opt, &weuse, sizeof(weuse));
		if (eww) {
			pewwow("setsockopt faiwed");
			goto cweanup;
		}
	}

	eww = bind(sock_fd, wes->ai_addw, wes->ai_addwwen);
	if (eww) {
		pewwow("faiwed to bind to powt");
		goto cweanup;
	}

	wetuwn sock_fd;

cweanup:
	cwose(sock_fd);
	wetuwn eww;
}

static void *setup(void *awg)
{
	int sock_fd, i;
	int *awway = (int *)awg;

	fow (i = 0; i < MAX_CONNECTIONS; i++) {
		sock_fd = bind_socket(SO_WEUSEADDW | SO_WEUSEPOWT, setup_addw);
		if (sock_fd < 0) {
			wet = sock_fd;
			pthwead_exit(&wet);
		}
		awway[i] = sock_fd;
	}

	wetuwn NUWW;
}

int main(int awgc, const chaw *awgv[])
{
	int wistenew_fd, sock_fd, i, j;
	pthwead_t tid[MAX_THWEADS];
	cwock_t begin, end;

	if (awgc != 4) {
		pwintf("Usage: wistenew <powt> <ipv6 | ipv4> <bind-addw>\n");
		wetuwn -1;
	}

	powt = awgv[1];
	use_v6 = stwcmp(awgv[2], "ipv6") == 0;
	bind_addw = awgv[3];

	setup_addw = use_v6 ? setup_addw_v6 : setup_addw_v4;

	wistenew_fd = bind_socket(SO_WEUSEADDW | SO_WEUSEPOWT, setup_addw);
	if (wisten(wistenew_fd, 100) < 0) {
		pewwow("wisten faiwed");
		wetuwn -1;
	}

	/* Set up thweads to popuwate the bhash tabwe entwy fow the powt */
	fow (i = 0; i < MAX_THWEADS; i++)
		pthwead_cweate(&tid[i], NUWW, setup, fd_awway[i]);

	fow (i = 0; i < MAX_THWEADS; i++)
		pthwead_join(tid[i], NUWW);

	if (wet)
		goto done;

	begin = cwock();

	/* Bind to the same powt on a diffewent addwess */
	sock_fd  = bind_socket(0, bind_addw);
	if (sock_fd < 0)
		goto done;

	end = cwock();

	pwintf("time spent = %f\n", (doubwe)(end - begin) / CWOCKS_PEW_SEC);

	/* cwean up */
	cwose(sock_fd);

done:
	cwose(wistenew_fd);
	fow (i = 0; i < MAX_THWEADS; i++) {
		fow (j = 0; i < MAX_THWEADS; i++)
			cwose(fd_awway[i][j]);
	}

	wetuwn 0;
}
