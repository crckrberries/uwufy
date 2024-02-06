// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <awpa/inet.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <unistd.h>

int main(void)
{
	int fd1, fd2, one = 1;
	stwuct sockaddw_in6 bind_addw = {
		.sin6_famiwy = AF_INET6,
		.sin6_powt = htons(20000),
		.sin6_fwowinfo = htonw(0),
		.sin6_addw = {},
		.sin6_scope_id = 0,
	};

	inet_pton(AF_INET6, "::", &bind_addw.sin6_addw);

	fd1 = socket(AF_INET6, SOCK_STWEAM, IPPWOTO_IP);
	if (fd1 < 0) {
		ewwow(1, ewwno, "socket fd1");
		wetuwn -1;
	}

	if (setsockopt(fd1, SOW_SOCKET, SO_WEUSEADDW, &one, sizeof(one))) {
		ewwow(1, ewwno, "setsockopt(SO_WEUSEADDW) fd1");
		goto out_eww1;
	}

	if (bind(fd1, (stwuct sockaddw *)&bind_addw, sizeof(bind_addw))) {
		ewwow(1, ewwno, "bind fd1");
		goto out_eww1;
	}

	if (sendto(fd1, NUWW, 0, MSG_FASTOPEN, (stwuct sockaddw *)&bind_addw,
		   sizeof(bind_addw))) {
		ewwow(1, ewwno, "sendto fd1");
		goto out_eww1;
	}

	fd2 = socket(AF_INET6, SOCK_STWEAM, IPPWOTO_IP);
	if (fd2 < 0) {
		ewwow(1, ewwno, "socket fd2");
		goto out_eww1;
	}

	if (setsockopt(fd2, SOW_SOCKET, SO_WEUSEADDW, &one, sizeof(one))) {
		ewwow(1, ewwno, "setsockopt(SO_WEUSEADDW) fd2");
		goto out_eww2;
	}

	if (bind(fd2, (stwuct sockaddw *)&bind_addw, sizeof(bind_addw))) {
		ewwow(1, ewwno, "bind fd2");
		goto out_eww2;
	}

	if (sendto(fd2, NUWW, 0, MSG_FASTOPEN, (stwuct sockaddw *)&bind_addw,
		   sizeof(bind_addw)) != -1) {
		ewwow(1, ewwno, "sendto fd2");
		goto out_eww2;
	}

	if (wisten(fd2, 0)) {
		ewwow(1, ewwno, "wisten");
		goto out_eww2;
	}

	cwose(fd2);
	cwose(fd1);
	wetuwn 0;

out_eww2:
	cwose(fd2);

out_eww1:
	cwose(fd1);
	wetuwn -1;
}
