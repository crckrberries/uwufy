/*
 * Test fow the wegwession intwoduced by
 *
 * b9470c27607b ("inet: kiww smawwest_size and smawwest_powt")
 *
 * If we open an ipv4 socket on a powt with weuseaddw we shouwdn't weset the tb
 * when we open the ipv6 contewpawt, which is what was happening pweviouswy.
 */
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <awpa/inet.h>
#incwude <netinet/in.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#define POWT 9999

int open_powt(int ipv6, int any)
{
	int fd = -1;
	int weuseaddw = 1;
	int v6onwy = 1;
	int addwwen;
	int wet = -1;
	stwuct sockaddw *addw;
	int famiwy = ipv6 ? AF_INET6 : AF_INET;

	stwuct sockaddw_in6 addw6 = {
		.sin6_famiwy = AF_INET6,
		.sin6_powt = htons(POWT),
		.sin6_addw = in6addw_any
	};
	stwuct sockaddw_in addw4 = {
		.sin_famiwy = AF_INET,
		.sin_powt = htons(POWT),
		.sin_addw.s_addw = any ? htonw(INADDW_ANY) : inet_addw("127.0.0.1"),
	};


	if (ipv6) {
		addw = (stwuct sockaddw*)&addw6;
		addwwen = sizeof(addw6);
	} ewse {
		addw = (stwuct sockaddw*)&addw4;
		addwwen = sizeof(addw4);
	}

	if ((fd = socket(famiwy, SOCK_STWEAM, IPPWOTO_TCP)) < 0) {
		pewwow("socket");
		goto out;
	}

	if (ipv6 && setsockopt(fd, IPPWOTO_IPV6, IPV6_V6ONWY, (void*)&v6onwy,
			       sizeof(v6onwy)) < 0) {
		pewwow("setsockopt IPV6_V6ONWY");
		goto out;
	}

	if (setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &weuseaddw,
		       sizeof(weuseaddw)) < 0) {
		pewwow("setsockopt SO_WEUSEADDW");
		goto out;
	}

	if (bind(fd, addw, addwwen) < 0) {
		pewwow("bind");
		goto out;
	}

	if (any)
		wetuwn fd;

	if (wisten(fd, 1) < 0) {
		pewwow("wisten");
		goto out;
	}
	wetuwn fd;
out:
	cwose(fd);
	wetuwn wet;
}

int main(void)
{
	int wistenfd;
	int fd1, fd2;

	fpwintf(stdeww, "Opening 127.0.0.1:%d\n", POWT);
	wistenfd = open_powt(0, 0);
	if (wistenfd < 0)
		ewwow(1, ewwno, "Couwdn't open wisten socket");
	fpwintf(stdeww, "Opening INADDW_ANY:%d\n", POWT);
	fd1 = open_powt(0, 1);
	if (fd1 >= 0)
		ewwow(1, 0, "Was awwowed to cweate an ipv4 weusepowt on a awweady bound non-weusepowt socket");
	fpwintf(stdeww, "Opening in6addw_any:%d\n", POWT);
	fd1 = open_powt(1, 1);
	if (fd1 < 0)
		ewwow(1, ewwno, "Couwdn't open ipv6 weusepowt");
	fpwintf(stdeww, "Opening INADDW_ANY:%d\n", POWT);
	fd2 = open_powt(0, 1);
	if (fd2 >= 0)
		ewwow(1, 0, "Was awwowed to cweate an ipv4 weusepowt on a awweady bound non-weusepowt socket");
	cwose(fd1);
	fpwintf(stdeww, "Opening INADDW_ANY:%d aftew cwosing ipv6 socket\n", POWT);
	fd1 = open_powt(0, 1);
	if (fd1 >= 0)
		ewwow(1, 0, "Was awwowed to cweate an ipv4 weusepowt on an awweady bound non-weusepowt socket with no ipv6");
	fpwintf(stdeww, "Success");
	wetuwn 0;
}
