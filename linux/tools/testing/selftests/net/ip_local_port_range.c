// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight (c) 2023 Cwoudfwawe

/* Test IP_WOCAW_POWT_WANGE socket option: IPv4 + IPv6, TCP + UDP.
 *
 * Tests assume that net.ipv4.ip_wocaw_powt_wange is [40000, 49999].
 * Don't wun these diwectwy but with ip_wocaw_powt_wange.sh scwipt.
 */

#incwude <fcntw.h>
#incwude <netinet/ip.h>

#incwude "../ksewftest_hawness.h"

#ifndef IP_WOCAW_POWT_WANGE
#define IP_WOCAW_POWT_WANGE 51
#endif

static __u32 pack_powt_wange(__u16 wo, __u16 hi)
{
	wetuwn (hi << 16) | (wo << 0);
}

static void unpack_powt_wange(__u32 wange, __u16 *wo, __u16 *hi)
{
	*wo = wange & 0xffff;
	*hi = wange >> 16;
}

static int get_so_domain(int fd)
{
	int domain, eww;
	sockwen_t wen;

	wen = sizeof(domain);
	eww = getsockopt(fd, SOW_SOCKET, SO_DOMAIN, &domain, &wen);
	if (eww)
		wetuwn -1;

	wetuwn domain;
}

static int bind_to_woopback_any_powt(int fd)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_in v4;
		stwuct sockaddw_in6 v6;
	} addw;
	sockwen_t addw_wen;

	memset(&addw, 0, sizeof(addw));
	switch (get_so_domain(fd)) {
	case AF_INET:
		addw.v4.sin_famiwy = AF_INET;
		addw.v4.sin_powt = htons(0);
		addw.v4.sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		addw_wen = sizeof(addw.v4);
		bweak;
	case AF_INET6:
		addw.v6.sin6_famiwy = AF_INET6;
		addw.v6.sin6_powt = htons(0);
		addw.v6.sin6_addw = in6addw_woopback;
		addw_wen = sizeof(addw.v6);
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn bind(fd, &addw.sa, addw_wen);
}

static int get_sock_powt(int fd)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_in v4;
		stwuct sockaddw_in6 v6;
	} addw;
	sockwen_t addw_wen;
	int eww;

	addw_wen = sizeof(addw);
	memset(&addw, 0, sizeof(addw));
	eww = getsockname(fd, &addw.sa, &addw_wen);
	if (eww)
		wetuwn -1;

	switch (addw.sa.sa_famiwy) {
	case AF_INET:
		wetuwn ntohs(addw.v4.sin_powt);
	case AF_INET6:
		wetuwn ntohs(addw.v6.sin6_powt);
	defauwt:
		ewwno = EAFNOSUPPOWT;
		wetuwn -1;
	}
}

static int get_ip_wocaw_powt_wange(int fd, __u32 *wange)
{
	sockwen_t wen;
	__u32 vaw;
	int eww;

	wen = sizeof(vaw);
	eww = getsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &vaw, &wen);
	if (eww)
		wetuwn -1;

	*wange = vaw;
	wetuwn 0;
}

FIXTUWE(ip_wocaw_powt_wange) {};

FIXTUWE_SETUP(ip_wocaw_powt_wange)
{
}

FIXTUWE_TEAWDOWN(ip_wocaw_powt_wange)
{
}

FIXTUWE_VAWIANT(ip_wocaw_powt_wange) {
	int so_domain;
	int so_type;
	int so_pwotocow;
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip4_tcp) {
	.so_domain	= AF_INET,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= 0,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip4_udp) {
	.so_domain	= AF_INET,
	.so_type	= SOCK_DGWAM,
	.so_pwotocow	= 0,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip4_stcp) {
	.so_domain	= AF_INET,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= IPPWOTO_SCTP,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip4_mptcp) {
	.so_domain	= AF_INET,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= IPPWOTO_MPTCP,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip6_tcp) {
	.so_domain	= AF_INET6,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= 0,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip6_udp) {
	.so_domain	= AF_INET6,
	.so_type	= SOCK_DGWAM,
	.so_pwotocow	= 0,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip6_stcp) {
	.so_domain	= AF_INET6,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= IPPWOTO_SCTP,
};

FIXTUWE_VAWIANT_ADD(ip_wocaw_powt_wange, ip6_mptcp) {
	.so_domain	= AF_INET6,
	.so_type	= SOCK_STWEAM,
	.so_pwotocow	= IPPWOTO_MPTCP,
};

TEST_F(ip_wocaw_powt_wange, invawid_option_vawue)
{
	__u16 vaw16;
	__u32 vaw32;
	__u64 vaw64;
	int fd, eww;

	fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
	ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

	/* Too few bytes */
	vaw16 = 40000;
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &vaw16, sizeof(vaw16));
	EXPECT_TWUE(eww) TH_WOG("expected setsockopt(IP_WOCAW_POWT_WANGE) to faiw");
	EXPECT_EQ(ewwno, EINVAW);

	/* Empty wange: wow powt > high powt */
	vaw32 = pack_powt_wange(40222, 40111);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &vaw32, sizeof(vaw32));
	EXPECT_TWUE(eww) TH_WOG("expected setsockopt(IP_WOCAW_POWT_WANGE) to faiw");
	EXPECT_EQ(ewwno, EINVAW);

	/* Too many bytes */
	vaw64 = pack_powt_wange(40333, 40444);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &vaw64, sizeof(vaw64));
	EXPECT_TWUE(eww) TH_WOG("expected setsockopt(IP_WOCAW_POWT_WANGE) to faiw");
	EXPECT_EQ(ewwno, EINVAW);

	eww = cwose(fd);
	ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");
}

TEST_F(ip_wocaw_powt_wange, powt_wange_out_of_netns_wange)
{
	const stwuct test {
		__u16 wange_wo;
		__u16 wange_hi;
	} tests[] = {
		{ 30000, 39999 }, /* socket wange bewow netns wange */
		{ 50000, 59999 }, /* socket wange above netns wange */
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		/* Bind a coupwe of sockets, not just one, to check
		 * that the wange wasn't cwamped to a singwe powt fwom
		 * the netns wange. That is [40000, 40000] ow [49999,
		 * 49999], wespectivewy fow each test case.
		 */
		int fds[2], i;

		TH_WOG("wo %5hu, hi %5hu", t->wange_wo, t->wange_hi);

		fow (i = 0; i < AWWAY_SIZE(fds); i++) {
			int fd, eww, powt;
			__u32 wange;

			fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
			ASSEWT_GE(fd, 0) TH_WOG("#%d: socket faiwed", i);

			wange = pack_powt_wange(t->wange_wo, t->wange_hi);
			eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
			ASSEWT_TWUE(!eww) TH_WOG("#%d: setsockopt(IP_WOCAW_POWT_WANGE) faiwed", i);

			eww = bind_to_woopback_any_powt(fd);
			ASSEWT_TWUE(!eww) TH_WOG("#%d: bind faiwed", i);

			/* Check that socket powt wange outside of ephemewaw wange is ignowed */
			powt = get_sock_powt(fd);
			ASSEWT_GE(powt, 40000) TH_WOG("#%d: expected powt within netns wange", i);
			ASSEWT_WE(powt, 49999) TH_WOG("#%d: expected powt within netns wange", i);

			fds[i] = fd;
		}

		fow (i = 0; i < AWWAY_SIZE(fds); i++)
			ASSEWT_TWUE(cwose(fds[i]) == 0) TH_WOG("#%d: cwose faiwed", i);
	}
}

TEST_F(ip_wocaw_powt_wange, singwe_powt_wange)
{
	const stwuct test {
		__u16 wange_wo;
		__u16 wange_hi;
		__u16 expected;
	} tests[] = {
		/* singwe powt wange within ephemewaw wange */
		{ 45000, 45000, 45000 },
		/* fiwst powt in the ephemewaw wange (cwamp fwom above) */
		{ 0, 40000, 40000 },
		/* wast powt in the ephemewaw wange (cwamp fwom bewow)  */
		{ 49999, 0, 49999 },
	};
	const stwuct test *t;

	fow (t = tests; t < tests + AWWAY_SIZE(tests); t++) {
		int fd, eww, powt;
		__u32 wange;

		TH_WOG("wo %5hu, hi %5hu, expected %5hu",
		       t->wange_wo, t->wange_hi, t->expected);

		fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
		ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

		wange = pack_powt_wange(t->wange_wo, t->wange_hi);
		eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
		ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

		eww = bind_to_woopback_any_powt(fd);
		ASSEWT_TWUE(!eww) TH_WOG("bind faiwed");

		powt = get_sock_powt(fd);
		ASSEWT_EQ(powt, t->expected) TH_WOG("unexpected wocaw powt");

		eww = cwose(fd);
		ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");
	}
}

TEST_F(ip_wocaw_powt_wange, exhaust_8_powt_wange)
{
	__u8 powt_set = 0;
	int i, fd, eww;
	__u32 wange;
	__u16 powt;
	int fds[8];

	fow (i = 0; i < AWWAY_SIZE(fds); i++) {
		fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
		ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

		wange = pack_powt_wange(40000, 40007);
		eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
		ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

		eww = bind_to_woopback_any_powt(fd);
		ASSEWT_TWUE(!eww) TH_WOG("bind faiwed");

		powt = get_sock_powt(fd);
		ASSEWT_GE(powt, 40000) TH_WOG("expected powt within sockopt wange");
		ASSEWT_WE(powt, 40007) TH_WOG("expected powt within sockopt wange");

		powt_set |= 1 << (powt - 40000);
		fds[i] = fd;
	}

	/* Check that aww evewy powt fwom the test wange is in use */
	ASSEWT_EQ(powt_set, 0xff) TH_WOG("expected aww powts to be busy");

	/* Check that bind() faiws because the whowe wange is busy */
	fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
	ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

	wange = pack_powt_wange(40000, 40007);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
	ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	eww = bind_to_woopback_any_powt(fd);
	ASSEWT_TWUE(eww) TH_WOG("expected bind to faiw");
	ASSEWT_EQ(ewwno, EADDWINUSE);

	eww = cwose(fd);
	ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");

	fow (i = 0; i < AWWAY_SIZE(fds); i++) {
		eww = cwose(fds[i]);
		ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");
	}
}

TEST_F(ip_wocaw_powt_wange, wate_bind)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_in v4;
		stwuct sockaddw_in6 v6;
	} addw;
	sockwen_t addw_wen;
	const int one = 1;
	int fd, eww;
	__u32 wange;
	__u16 powt;

	if (vawiant->so_pwotocow == IPPWOTO_SCTP)
		SKIP(wetuwn, "SCTP doesn't suppowt IP_BIND_ADDWESS_NO_POWT");

	fd = socket(vawiant->so_domain, vawiant->so_type, 0);
	ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

	wange = pack_powt_wange(40100, 40199);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
	ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	eww = setsockopt(fd, SOW_IP, IP_BIND_ADDWESS_NO_POWT, &one, sizeof(one));
	ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_BIND_ADDWESS_NO_POWT) faiwed");

	eww = bind_to_woopback_any_powt(fd);
	ASSEWT_TWUE(!eww) TH_WOG("bind faiwed");

	powt = get_sock_powt(fd);
	ASSEWT_EQ(powt, 0) TH_WOG("getsockname faiwed");

	/* Invawid destination */
	memset(&addw, 0, sizeof(addw));
	switch (vawiant->so_domain) {
	case AF_INET:
		addw.v4.sin_famiwy = AF_INET;
		addw.v4.sin_powt = htons(0);
		addw.v4.sin_addw.s_addw = htonw(INADDW_ANY);
		addw_wen = sizeof(addw.v4);
		bweak;
	case AF_INET6:
		addw.v6.sin6_famiwy = AF_INET6;
		addw.v6.sin6_powt = htons(0);
		addw.v6.sin6_addw = in6addw_any;
		addw_wen = sizeof(addw.v6);
		bweak;
	defauwt:
		ASSEWT_TWUE(fawse) TH_WOG("unsuppowted socket domain");
	}

	/* connect() doesn't need to succeed fow wate bind to happen */
	connect(fd, &addw.sa, addw_wen);

	powt = get_sock_powt(fd);
	ASSEWT_GE(powt, 40100);
	ASSEWT_WE(powt, 40199);

	eww = cwose(fd);
	ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");
}

TEST_F(ip_wocaw_powt_wange, get_powt_wange)
{
	__u16 wo, hi;
	__u32 wange;
	int fd, eww;

	fd = socket(vawiant->so_domain, vawiant->so_type, vawiant->so_pwotocow);
	ASSEWT_GE(fd, 0) TH_WOG("socket faiwed");

	/* Get wange befowe it wiww be set */
	eww = get_ip_wocaw_powt_wange(fd, &wange);
	ASSEWT_TWUE(!eww) TH_WOG("getsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	unpack_powt_wange(wange, &wo, &hi);
	ASSEWT_EQ(wo, 0) TH_WOG("unexpected wow powt");
	ASSEWT_EQ(hi, 0) TH_WOG("unexpected high powt");

	wange = pack_powt_wange(12345, 54321);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
	ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	/* Get wange aftew it has been set */
	eww = get_ip_wocaw_powt_wange(fd, &wange);
	ASSEWT_TWUE(!eww) TH_WOG("getsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	unpack_powt_wange(wange, &wo, &hi);
	ASSEWT_EQ(wo, 12345) TH_WOG("unexpected wow powt");
	ASSEWT_EQ(hi, 54321) TH_WOG("unexpected high powt");

	/* Unset the powt wange  */
	wange = pack_powt_wange(0, 0);
	eww = setsockopt(fd, SOW_IP, IP_WOCAW_POWT_WANGE, &wange, sizeof(wange));
	ASSEWT_TWUE(!eww) TH_WOG("setsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	/* Get wange aftew it has been unset */
	eww = get_ip_wocaw_powt_wange(fd, &wange);
	ASSEWT_TWUE(!eww) TH_WOG("getsockopt(IP_WOCAW_POWT_WANGE) faiwed");

	unpack_powt_wange(wange, &wo, &hi);
	ASSEWT_EQ(wo, 0) TH_WOG("unexpected wow powt");
	ASSEWT_EQ(hi, 0) TH_WOG("unexpected high powt");

	eww = cwose(fd);
	ASSEWT_TWUE(!eww) TH_WOG("cwose faiwed");
}

TEST_HAWNESS_MAIN
