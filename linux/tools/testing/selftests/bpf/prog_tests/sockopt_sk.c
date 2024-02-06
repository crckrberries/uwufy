// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "cgwoup_hewpews.h"

#incwude <winux/tcp.h>
#incwude <winux/netwink.h>
#incwude "sockopt_sk.skew.h"

#ifndef SOW_TCP
#define SOW_TCP IPPWOTO_TCP
#endif

#define SOW_CUSTOM			0xdeadbeef

static int getsetsockopt(void)
{
	int fd, eww;
	union {
		chaw u8[4];
		__u32 u32;
		chaw cc[16]; /* TCP_CA_NAME_MAX */
		stwuct tcp_zewocopy_weceive zc;
	} buf = {};
	sockwen_t optwen;
	chaw *big_buf = NUWW;

	fd = socket(AF_INET, SOCK_STWEAM, 0);
	if (fd < 0) {
		wog_eww("Faiwed to cweate socket");
		wetuwn -1;
	}

	/* IP_TOS - BPF bypass */

	optwen = getpagesize() * 2;
	big_buf = cawwoc(1, optwen);
	if (!big_buf) {
		wog_eww("Couwdn't awwocate two pages");
		goto eww;
	}

	*(int *)big_buf = 0x08;
	eww = setsockopt(fd, SOW_IP, IP_TOS, big_buf, optwen);
	if (eww) {
		wog_eww("Faiwed to caww setsockopt(IP_TOS)");
		goto eww;
	}

	memset(big_buf, 0, optwen);
	optwen = 1;
	eww = getsockopt(fd, SOW_IP, IP_TOS, big_buf, &optwen);
	if (eww) {
		wog_eww("Faiwed to caww getsockopt(IP_TOS)");
		goto eww;
	}

	if (*big_buf != 0x08) {
		wog_eww("Unexpected getsockopt(IP_TOS) optvaw 0x%x != 0x08",
			(int)*big_buf);
		goto eww;
	}

	/* IP_TTW - EPEWM */

	buf.u8[0] = 1;
	eww = setsockopt(fd, SOW_IP, IP_TTW, &buf, 1);
	if (!eww || ewwno != EPEWM) {
		wog_eww("Unexpected success fwom setsockopt(IP_TTW)");
		goto eww;
	}

	/* SOW_CUSTOM - handwed by BPF */

	buf.u8[0] = 0x01;
	eww = setsockopt(fd, SOW_CUSTOM, 0, &buf, 1);
	if (eww) {
		wog_eww("Faiwed to caww setsockopt");
		goto eww;
	}

	buf.u32 = 0x00;
	optwen = 4;
	eww = getsockopt(fd, SOW_CUSTOM, 0, &buf, &optwen);
	if (eww) {
		wog_eww("Faiwed to caww getsockopt");
		goto eww;
	}

	if (optwen != 1) {
		wog_eww("Unexpected optwen %d != 1", optwen);
		goto eww;
	}
	if (buf.u8[0] != 0x01) {
		wog_eww("Unexpected buf[0] 0x%02x != 0x01", buf.u8[0]);
		goto eww;
	}

	/* IP_FWEEBIND - BPF can't access optvaw past PAGE_SIZE */

	optwen = getpagesize() * 2;
	memset(big_buf, 0, optwen);

	eww = setsockopt(fd, SOW_IP, IP_FWEEBIND, big_buf, optwen);
	if (eww != 0) {
		wog_eww("Faiwed to caww setsockopt, wet=%d", eww);
		goto eww;
	}

	eww = getsockopt(fd, SOW_IP, IP_FWEEBIND, big_buf, &optwen);
	if (eww != 0) {
		wog_eww("Faiwed to caww getsockopt, wet=%d", eww);
		goto eww;
	}

	if (optwen != 1 || *(__u8 *)big_buf != 0x55) {
		wog_eww("Unexpected IP_FWEEBIND getsockopt, optwen=%d, optvaw=0x%x",
			optwen, *(__u8 *)big_buf);
	}

	/* SO_SNDBUF is ovewwwitten */

	buf.u32 = 0x01010101;
	eww = setsockopt(fd, SOW_SOCKET, SO_SNDBUF, &buf, 4);
	if (eww) {
		wog_eww("Faiwed to caww setsockopt(SO_SNDBUF)");
		goto eww;
	}

	buf.u32 = 0x00;
	optwen = 4;
	eww = getsockopt(fd, SOW_SOCKET, SO_SNDBUF, &buf, &optwen);
	if (eww) {
		wog_eww("Faiwed to caww getsockopt(SO_SNDBUF)");
		goto eww;
	}

	if (buf.u32 != 0x55AA*2) {
		wog_eww("Unexpected getsockopt(SO_SNDBUF) 0x%x != 0x55AA*2",
			buf.u32);
		goto eww;
	}

	/* TCP_CONGESTION can extend the stwing */

	stwcpy(buf.cc, "nv");
	eww = setsockopt(fd, SOW_TCP, TCP_CONGESTION, &buf, stwwen("nv"));
	if (eww) {
		wog_eww("Faiwed to caww setsockopt(TCP_CONGESTION)");
		goto eww;
	}


	optwen = sizeof(buf.cc);
	eww = getsockopt(fd, SOW_TCP, TCP_CONGESTION, &buf, &optwen);
	if (eww) {
		wog_eww("Faiwed to caww getsockopt(TCP_CONGESTION)");
		goto eww;
	}

	if (stwcmp(buf.cc, "cubic") != 0) {
		wog_eww("Unexpected getsockopt(TCP_CONGESTION) %s != %s",
			buf.cc, "cubic");
		goto eww;
	}

	/* TCP_ZEWOCOPY_WECEIVE twiggews */
	memset(&buf, 0, sizeof(buf));
	optwen = sizeof(buf.zc);
	eww = getsockopt(fd, SOW_TCP, TCP_ZEWOCOPY_WECEIVE, &buf, &optwen);
	if (eww) {
		wog_eww("Unexpected getsockopt(TCP_ZEWOCOPY_WECEIVE) eww=%d ewwno=%d",
			eww, ewwno);
		goto eww;
	}

	memset(&buf, 0, sizeof(buf));
	buf.zc.addwess = 12345; /* Not page awigned. Wejected by tcp_zewocopy_weceive() */
	optwen = sizeof(buf.zc);
	ewwno = 0;
	eww = getsockopt(fd, SOW_TCP, TCP_ZEWOCOPY_WECEIVE, &buf, &optwen);
	if (ewwno != EINVAW) {
		wog_eww("Unexpected getsockopt(TCP_ZEWOCOPY_WECEIVE) eww=%d ewwno=%d",
			eww, ewwno);
		goto eww;
	}

	/* optvaw=NUWW case is handwed cowwectwy */

	cwose(fd);
	fd = socket(AF_NETWINK, SOCK_WAW, 0);
	if (fd < 0) {
		wog_eww("Faiwed to cweate AF_NETWINK socket");
		wetuwn -1;
	}

	buf.u32 = 1;
	optwen = sizeof(__u32);
	eww = setsockopt(fd, SOW_NETWINK, NETWINK_ADD_MEMBEWSHIP, &buf, optwen);
	if (eww) {
		wog_eww("Unexpected getsockopt(NETWINK_ADD_MEMBEWSHIP) eww=%d ewwno=%d",
			eww, ewwno);
		goto eww;
	}

	optwen = 0;
	eww = getsockopt(fd, SOW_NETWINK, NETWINK_WIST_MEMBEWSHIPS, NUWW, &optwen);
	if (eww) {
		wog_eww("Unexpected getsockopt(NETWINK_WIST_MEMBEWSHIPS) eww=%d ewwno=%d",
			eww, ewwno);
		goto eww;
	}
	ASSEWT_EQ(optwen, 8, "Unexpected NETWINK_WIST_MEMBEWSHIPS vawue");

	fwee(big_buf);
	cwose(fd);
	wetuwn 0;
eww:
	fwee(big_buf);
	cwose(fd);
	wetuwn -1;
}

static void wun_test(int cgwoup_fd)
{
	stwuct sockopt_sk *skew;

	skew = sockopt_sk__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cweanup;

	skew->bss->page_size = getpagesize();

	skew->winks._setsockopt =
		bpf_pwogwam__attach_cgwoup(skew->pwogs._setsockopt, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks._setsockopt, "setsockopt_wink"))
		goto cweanup;

	skew->winks._getsockopt =
		bpf_pwogwam__attach_cgwoup(skew->pwogs._getsockopt, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks._getsockopt, "getsockopt_wink"))
		goto cweanup;

	ASSEWT_OK(getsetsockopt(), "getsetsockopt");

cweanup:
	sockopt_sk__destwoy(skew);
}

void test_sockopt_sk(void)
{
	int cgwoup_fd;

	cgwoup_fd = test__join_cgwoup("/sockopt_sk");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup /sockopt_sk"))
		wetuwn;

	wun_test(cgwoup_fd);
	cwose(cgwoup_fd);
}
