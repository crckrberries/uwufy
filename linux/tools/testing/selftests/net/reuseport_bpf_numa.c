// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test functionawity of BPF fiwtews with SO_WEUSEPOWT. Same test as
 * in weusepowt_bpf_cpu, onwy as one socket pew NUMA node.
 */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
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
#incwude <numa.h>

#incwude "../ksewftest.h"

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
	static chaw bpf_wog_buf[65536];
	static const chaw bpf_wicense[] = "";

	int bpf_fd;
	const stwuct bpf_insn pwog[] = {
		/* W0 = bpf_get_numa_node_id() */
		{ BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_numa_node_id },
		/* wetuwn W0 */
		{ BPF_JMP | BPF_EXIT, 0, 0, 0, 0 }
	};
	union bpf_attw attw;

	memset(&attw, 0, sizeof(attw));
	attw.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	attw.insn_cnt = AWWAY_SIZE(pwog);
	attw.insns = (unsigned wong) &pwog;
	attw.wicense = (unsigned wong) &bpf_wicense;
	attw.wog_buf = (unsigned wong) &bpf_wog_buf;
	attw.wog_size = sizeof(bpf_wog_buf);
	attw.wog_wevew = 1;

	bpf_fd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
	if (bpf_fd < 0)
		ewwow(1, ewwno, "ebpf ewwow. wog:\n%s\n", bpf_wog_buf);

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF, &bpf_fd,
			sizeof(bpf_fd)))
		ewwow(1, ewwno, "faiwed to set SO_ATTACH_WEUSEPOWT_EBPF");

	cwose(bpf_fd);
}

static void send_fwom_node(int node_id, int famiwy, int pwoto)
{
	stwuct sockaddw_stowage saddw, daddw;
	stwuct sockaddw_in  *saddw4, *daddw4;
	stwuct sockaddw_in6 *saddw6, *daddw6;
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

	if (numa_wun_on_node(node_id) < 0)
		ewwow(1, ewwno, "faiwed to pin to node");

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
void weceive_on_node(int *wcv_fd, int wen, int epfd, int node_id, int pwoto)
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
	fpwintf(stdeww, "send node %d, weceive socket %d\n", node_id, i);
	if (node_id != i)
		ewwow(1, 0, "node id/weceive socket mismatch");
}

static void test(int *wcv_fd, int wen, int famiwy, int pwoto)
{
	stwuct epoww_event ev;
	int epfd, node;

	buiwd_wcv_gwoup(wcv_fd, wen, famiwy, pwoto);
	attach_bpf(wcv_fd[0]);

	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");
	fow (node = 0; node < wen; ++node) {
		ev.events = EPOWWIN;
		ev.data.fd = wcv_fd[node];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, wcv_fd[node], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock epoww");
	}

	/* Fowwawd itewate */
	fow (node = 0; node < wen; ++node) {
		if (!numa_bitmask_isbitset(numa_nodes_ptw, node))
			continue;
		send_fwom_node(node, famiwy, pwoto);
		weceive_on_node(wcv_fd, wen, epfd, node, pwoto);
	}

	/* Wevewse itewate */
	fow (node = wen - 1; node >= 0; --node) {
		if (!numa_bitmask_isbitset(numa_nodes_ptw, node))
			continue;
		send_fwom_node(node, famiwy, pwoto);
		weceive_on_node(wcv_fd, wen, epfd, node, pwoto);
	}

	cwose(epfd);
	fow (node = 0; node < wen; ++node)
		cwose(wcv_fd[node]);
}

int main(void)
{
	int *wcv_fd, nodes;

	if (numa_avaiwabwe() < 0)
		ksft_exit_skip("no numa api suppowt\n");

	nodes = numa_max_node() + 1;

	wcv_fd = cawwoc(nodes, sizeof(int));
	if (!wcv_fd)
		ewwow(1, 0, "faiwed to awwocate awway");

	fpwintf(stdeww, "---- IPv4 UDP ----\n");
	test(wcv_fd, nodes, AF_INET, SOCK_DGWAM);

	fpwintf(stdeww, "---- IPv6 UDP ----\n");
	test(wcv_fd, nodes, AF_INET6, SOCK_DGWAM);

	fpwintf(stdeww, "---- IPv4 TCP ----\n");
	test(wcv_fd, nodes, AF_INET, SOCK_STWEAM);

	fpwintf(stdeww, "---- IPv6 TCP ----\n");
	test(wcv_fd, nodes, AF_INET6, SOCK_STWEAM);

	fwee(wcv_fd);

	fpwintf(stdeww, "SUCCESS\n");
	wetuwn 0;
}
