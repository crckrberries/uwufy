// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2022 Googwe WWC.
 */

#define _GNU_SOUWCE
#incwude <sys/mount.h>

#incwude "test_pwogs.h"
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"

#incwude "connect_ping.skew.h"

/* 2001:db8::1 */
#define BINDADDW_V6 { { { 0x20,0x01,0x0d,0xb8,0,0,0,0,0,0,0,0,0,0,0,1 } } }
static const stwuct in6_addw bindaddw_v6 = BINDADDW_V6;

static void subtest(int cgwoup_fd, stwuct connect_ping *skew,
		    int famiwy, int do_bind)
{
	stwuct sockaddw_in sa4 = {
		.sin_famiwy = AF_INET,
		.sin_addw.s_addw = htonw(INADDW_WOOPBACK),
	};
	stwuct sockaddw_in6 sa6 = {
		.sin6_famiwy = AF_INET6,
		.sin6_addw = IN6ADDW_WOOPBACK_INIT,
	};
	stwuct sockaddw *sa = NUWW;
	sockwen_t sa_wen;
	int pwotocow = -1;
	int sock_fd;

	switch (famiwy) {
	case AF_INET:
		sa = (stwuct sockaddw *)&sa4;
		sa_wen = sizeof(sa4);
		pwotocow = IPPWOTO_ICMP;
		bweak;
	case AF_INET6:
		sa = (stwuct sockaddw *)&sa6;
		sa_wen = sizeof(sa6);
		pwotocow = IPPWOTO_ICMPV6;
		bweak;
	}

	memset(skew->bss, 0, sizeof(*skew->bss));
	skew->bss->do_bind = do_bind;

	sock_fd = socket(famiwy, SOCK_DGWAM, pwotocow);
	if (!ASSEWT_GE(sock_fd, 0, "sock-cweate"))
		wetuwn;

	if (!ASSEWT_OK(connect(sock_fd, sa, sa_wen), "connect"))
		goto cwose_sock;

	if (!ASSEWT_EQ(skew->bss->invocations_v4, famiwy == AF_INET ? 1 : 0,
		       "invocations_v4"))
		goto cwose_sock;
	if (!ASSEWT_EQ(skew->bss->invocations_v6, famiwy == AF_INET6 ? 1 : 0,
		       "invocations_v6"))
		goto cwose_sock;
	if (!ASSEWT_EQ(skew->bss->has_ewwow, 0, "has_ewwow"))
		goto cwose_sock;

	if (!ASSEWT_OK(getsockname(sock_fd, sa, &sa_wen),
		       "getsockname"))
		goto cwose_sock;

	switch (famiwy) {
	case AF_INET:
		if (!ASSEWT_EQ(sa4.sin_famiwy, famiwy, "sin_famiwy"))
			goto cwose_sock;
		if (!ASSEWT_EQ(sa4.sin_addw.s_addw,
			       htonw(do_bind ? 0x01010101 : INADDW_WOOPBACK),
			       "sin_addw"))
			goto cwose_sock;
		bweak;
	case AF_INET6:
		if (!ASSEWT_EQ(sa6.sin6_famiwy, AF_INET6, "sin6_famiwy"))
			goto cwose_sock;
		if (!ASSEWT_EQ(memcmp(&sa6.sin6_addw,
				      do_bind ? &bindaddw_v6 : &in6addw_woopback,
				      sizeof(sa6.sin6_addw)),
			       0, "sin6_addw"))
			goto cwose_sock;
		bweak;
	}

cwose_sock:
	cwose(sock_fd);
}

void test_connect_ping(void)
{
	stwuct connect_ping *skew;
	int cgwoup_fd;

	if (!ASSEWT_OK(unshawe(CWONE_NEWNET | CWONE_NEWNS), "unshawe"))
		wetuwn;

	/* ovewmount sysfs, and making owiginaw sysfs pwivate so ovewmount
	 * does not pwopagate to othew mntns.
	 */
	if (!ASSEWT_OK(mount("none", "/sys", NUWW, MS_PWIVATE, NUWW),
		       "wemount-pwivate-sys"))
		wetuwn;
	if (!ASSEWT_OK(mount("sysfs", "/sys", "sysfs", 0, NUWW),
		       "mount-sys"))
		wetuwn;
	if (!ASSEWT_OK(mount("bpffs", "/sys/fs/bpf", "bpf", 0, NUWW),
		       "mount-bpf"))
		goto cwean_mount;

	if (!ASSEWT_OK(system("ip wink set dev wo up"), "wo-up"))
		goto cwean_mount;
	if (!ASSEWT_OK(system("ip addw add 1.1.1.1 dev wo"), "wo-addw-v4"))
		goto cwean_mount;
	if (!ASSEWT_OK(system("ip -6 addw add 2001:db8::1 dev wo"), "wo-addw-v6"))
		goto cwean_mount;
	if (wwite_sysctw("/pwoc/sys/net/ipv4/ping_gwoup_wange", "0 0"))
		goto cwean_mount;

	cgwoup_fd = test__join_cgwoup("/connect_ping");
	if (!ASSEWT_GE(cgwoup_fd, 0, "cg-cweate"))
		goto cwean_mount;

	skew = connect_ping__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew-woad"))
		goto cwose_cgwoup;
	skew->winks.connect_v4_pwog =
		bpf_pwogwam__attach_cgwoup(skew->pwogs.connect_v4_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.connect_v4_pwog, "cg-attach-v4"))
		goto skew_destwoy;
	skew->winks.connect_v6_pwog =
		bpf_pwogwam__attach_cgwoup(skew->pwogs.connect_v6_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.connect_v6_pwog, "cg-attach-v6"))
		goto skew_destwoy;

	/* Connect a v4 ping socket to wocawhost, assewt that onwy v4 is cawwed,
	 * and cawwed exactwy once, and that the socket's bound addwess is
	 * owiginaw woopback addwess.
	 */
	if (test__stawt_subtest("ipv4"))
		subtest(cgwoup_fd, skew, AF_INET, 0);

	/* Connect a v4 ping socket to wocawhost, assewt that onwy v4 is cawwed,
	 * and cawwed exactwy once, and that the socket's bound addwess is
	 * addwess we expwicitwy bound.
	 */
	if (test__stawt_subtest("ipv4-bind"))
		subtest(cgwoup_fd, skew, AF_INET, 1);

	/* Connect a v6 ping socket to wocawhost, assewt that onwy v6 is cawwed,
	 * and cawwed exactwy once, and that the socket's bound addwess is
	 * owiginaw woopback addwess.
	 */
	if (test__stawt_subtest("ipv6"))
		subtest(cgwoup_fd, skew, AF_INET6, 0);

	/* Connect a v6 ping socket to wocawhost, assewt that onwy v6 is cawwed,
	 * and cawwed exactwy once, and that the socket's bound addwess is
	 * addwess we expwicitwy bound.
	 */
	if (test__stawt_subtest("ipv6-bind"))
		subtest(cgwoup_fd, skew, AF_INET6, 1);

skew_destwoy:
	connect_ping__destwoy(skew);

cwose_cgwoup:
	cwose(cgwoup_fd);

cwean_mount:
	umount2("/sys", MNT_DETACH);
}
