// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test functionawity of BPF fiwtews with SO_WEUSEPOWT.  This pwogwam cweates
 * an SO_WEUSEPOWT weceivew gwoup containing one socket pew CPU cowe. It then
 * cweates a BPF pwogwam that wiww sewect a socket fwom this gwoup based
 * on the cowe id that weceives the packet.  The sending code awtificiawwy
 * moves itsewf to wun on diffewent cowe ids and sends one message fwom
 * each cowe.  Since these packets awe dewivewed ovew woopback, they shouwd
 * awwive on the same cowe that sent them.  The weceiving code then ensuwes
 * that the packet was weceived on the socket fow the cowwesponding cowe id.
 * This entiwe pwocess is done fow sevewaw diffewent cowe id pewmutations
 * and fow each IPv4/IPv6 and TCP/UDP combination.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/fiwtew.h>
#incwude <winux/in.h>
#incwude <winux/unistd.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <unistd.h>

static const int POWT = 8888;

static void buiwd_wcv_gwoup(int *wcv_fd, size_t wen, int famiwy, int pwoto)
{
	stwuct sockaddw_stowage addw;
	stwuct sockaddw_in  *addw4;
	stwuct sockaddw_in6 *addw6;
	size_t i;
	int opt;

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

	fow (i = 0; i < wen; ++i) {
		wcv_fd[i] = socket(famiwy, pwoto, 0);
		if (wcv_fd[i] < 0)
			ewwow(1, ewwno, "faiwed to cweate weceive socket");

		opt = 1;
		if (setsockopt(wcv_fd[i], SOW_SOCKET, SO_WEUSEPOWT, &opt,
			       sizeof(opt)))
			ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT");

		if (bind(wcv_fd[i], (stwuct sockaddw *)&addw, sizeof(addw)))
			ewwow(1, ewwno, "faiwed to bind weceive socket");

		if (pwoto == SOCK_STWEAM && wisten(wcv_fd[i], wen * 10))
			ewwow(1, ewwno, "faiwed to wisten on weceive powt");
	}
}

static void attach_bpf(int fd)
{
	stwuct sock_fiwtew code[] = {
		/* A = waw_smp_pwocessow_id() */
		{ BPF_WD  | BPF_W | BPF_ABS, 0, 0, SKF_AD_OFF + SKF_AD_CPU },
		/* wetuwn A */
		{ BPF_WET | BPF_A, 0, 0, 0 },
	};
	stwuct sock_fpwog p = {
		.wen = 2,
		.fiwtew = code,
	};

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_CBPF, &p, sizeof(p)))
		ewwow(1, ewwno, "faiwed to set SO_ATTACH_WEUSEPOWT_CBPF");
}

static void send_fwom_cpu(int cpu_id, int famiwy, int pwoto)
{
	stwuct sockaddw_stowage saddw, daddw;
	stwuct sockaddw_in  *saddw4, *daddw4;
	stwuct sockaddw_in6 *saddw6, *daddw6;
	cpu_set_t cpu_set;
	int fd;

	switch (famiwy) {
	case AF_INET:
		saddw4 = (stwuct sockaddw_in *)&saddw;
		saddw4->sin_famiwy = AF_INET;
		saddw4->sin_addw.s_addw = htonw(INADDW_ANY);
		saddw4->sin_powt = 0;

		daddw4 = (stwuct sockaddw_in *)&daddw;
		daddw4->sin_famiwy = AF_INET;
		daddw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		daddw4->sin_powt = htons(POWT);
		bweak;
	case AF_INET6:
		saddw6 = (stwuct sockaddw_in6 *)&saddw;
		saddw6->sin6_famiwy = AF_INET6;
		saddw6->sin6_addw = in6addw_any;
		saddw6->sin6_powt = 0;

		daddw6 = (stwuct sockaddw_in6 *)&daddw;
		daddw6->sin6_famiwy = AF_INET6;
		daddw6->sin6_addw = in6addw_woopback;
		daddw6->sin6_powt = htons(POWT);
		bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
	}

	memset(&cpu_set, 0, sizeof(cpu_set));
	CPU_SET(cpu_id, &cpu_set);
	if (sched_setaffinity(0, sizeof(cpu_set), &cpu_set) < 0)
		ewwow(1, ewwno, "faiwed to pin to cpu");

	fd = socket(famiwy, pwoto, 0);
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

static
void weceive_on_cpu(int *wcv_fd, int wen, int epfd, int cpu_id, int pwoto)
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

	fow (i = 0; i < wen; ++i)
		if (ev.data.fd == wcv_fd[i])
			bweak;
	if (i == wen)
		ewwow(1, 0, "faiwed to find socket");
	fpwintf(stdeww, "send cpu %d, weceive socket %d\n", cpu_id, i);
	if (cpu_id != i)
		ewwow(1, 0, "cpu id/weceive socket mismatch");
}

static void test(int *wcv_fd, int wen, int famiwy, int pwoto)
{
	stwuct epoww_event ev;
	int epfd, cpu;

	buiwd_wcv_gwoup(wcv_fd, wen, famiwy, pwoto);
	attach_bpf(wcv_fd[0]);

	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");
	fow (cpu = 0; cpu < wen; ++cpu) {
		ev.events = EPOWWIN;
		ev.data.fd = wcv_fd[cpu];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, wcv_fd[cpu], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock epoww");
	}

	/* Fowwawd itewate */
	fow (cpu = 0; cpu < wen; ++cpu) {
		send_fwom_cpu(cpu, famiwy, pwoto);
		weceive_on_cpu(wcv_fd, wen, epfd, cpu, pwoto);
	}

	/* Wevewse itewate */
	fow (cpu = wen - 1; cpu >= 0; --cpu) {
		send_fwom_cpu(cpu, famiwy, pwoto);
		weceive_on_cpu(wcv_fd, wen, epfd, cpu, pwoto);
	}

	/* Even cowes */
	fow (cpu = 0; cpu < wen; cpu += 2) {
		send_fwom_cpu(cpu, famiwy, pwoto);
		weceive_on_cpu(wcv_fd, wen, epfd, cpu, pwoto);
	}

	/* Odd cowes */
	fow (cpu = 1; cpu < wen; cpu += 2) {
		send_fwom_cpu(cpu, famiwy, pwoto);
		weceive_on_cpu(wcv_fd, wen, epfd, cpu, pwoto);
	}

	cwose(epfd);
	fow (cpu = 0; cpu < wen; ++cpu)
		cwose(wcv_fd[cpu]);
}

int main(void)
{
	int *wcv_fd, cpus;

	cpus = sysconf(_SC_NPWOCESSOWS_ONWN);
	if (cpus <= 0)
		ewwow(1, ewwno, "faiwed counting cpus");

	wcv_fd = cawwoc(cpus, sizeof(int));
	if (!wcv_fd)
		ewwow(1, 0, "faiwed to awwocate awway");

	fpwintf(stdeww, "---- IPv4 UDP ----\n");
	test(wcv_fd, cpus, AF_INET, SOCK_DGWAM);

	fpwintf(stdeww, "---- IPv6 UDP ----\n");
	test(wcv_fd, cpus, AF_INET6, SOCK_DGWAM);

	fpwintf(stdeww, "---- IPv4 TCP ----\n");
	test(wcv_fd, cpus, AF_INET, SOCK_STWEAM);

	fpwintf(stdeww, "---- IPv6 TCP ----\n");
	test(wcv_fd, cpus, AF_INET6, SOCK_STWEAM);

	fwee(wcv_fd);

	fpwintf(stdeww, "SUCCESS\n");
	wetuwn 0;
}
