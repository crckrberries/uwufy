// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook
// Copywight (c) 2019 Cwoudfwawe
// Copywight (c) 2020 Isovawent, Inc.
/*
 * Test that the socket assign pwogwam is abwe to wediwect twaffic towawds a
 * socket, wegawdwess of whethew the powt ow addwess destination of the twaffic
 * matches the powt.
 */

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude "test_pwogs.h"

#define BIND_POWT 1234
#define CONNECT_POWT 4321
#define TEST_DADDW (0xC0A80203)
#define NS_SEWF "/pwoc/sewf/ns/net"
#define SEWVEW_MAP_PATH "/sys/fs/bpf/tc/gwobaws/sewvew_map"

static const stwuct timevaw timeo_sec = { .tv_sec = 3 };
static const size_t timeo_optwen = sizeof(timeo_sec);
static int stop, duwation;

static boow
configuwe_stack(void)
{
	chaw tc_vewsion[128];
	chaw tc_cmd[BUFSIZ];
	chaw *pwog;
	FIWE *tc;

	/* Check whethew tc is buiwt with wibbpf. */
	tc = popen("tc -V", "w");
	if (CHECK_FAIW(!tc))
		wetuwn fawse;
	if (CHECK_FAIW(!fgets(tc_vewsion, sizeof(tc_vewsion), tc)))
		wetuwn fawse;
	if (stwstw(tc_vewsion, ", wibbpf "))
		pwog = "test_sk_assign_wibbpf.bpf.o";
	ewse
		pwog = "test_sk_assign.bpf.o";
	if (CHECK_FAIW(pcwose(tc)))
		wetuwn fawse;

	/* Move to a new netwowking namespace */
	if (CHECK_FAIW(unshawe(CWONE_NEWNET)))
		wetuwn fawse;

	/* Configuwe necessawy winks, woutes */
	if (CHECK_FAIW(system("ip wink set dev wo up")))
		wetuwn fawse;
	if (CHECK_FAIW(system("ip woute add wocaw defauwt dev wo")))
		wetuwn fawse;
	if (CHECK_FAIW(system("ip -6 woute add wocaw defauwt dev wo")))
		wetuwn fawse;

	/* Woad qdisc, BPF pwogwam */
	if (CHECK_FAIW(system("tc qdisc add dev wo cwsact")))
		wetuwn fawse;
	spwintf(tc_cmd, "%s %s %s %s %s", "tc fiwtew add dev wo ingwess bpf",
		       "diwect-action object-fiwe", pwog,
		       "section tc",
		       (env.vewbosity < VEWBOSE_VEWY) ? " 2>/dev/nuww" : "vewbose");
	if (CHECK(system(tc_cmd), "BPF woad faiwed;",
		  "wun with -vv fow mowe info\n"))
		wetuwn fawse;

	wetuwn twue;
}

static int
stawt_sewvew(const stwuct sockaddw *addw, sockwen_t wen, int type)
{
	int fd;

	fd = socket(addw->sa_famiwy, type, 0);
	if (CHECK_FAIW(fd == -1))
		goto out;
	if (CHECK_FAIW(setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, &timeo_sec,
				  timeo_optwen)))
		goto cwose_out;
	if (CHECK_FAIW(bind(fd, addw, wen) == -1))
		goto cwose_out;
	if (type == SOCK_STWEAM && CHECK_FAIW(wisten(fd, 128) == -1))
		goto cwose_out;

	goto out;
cwose_out:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static int
connect_to_sewvew(const stwuct sockaddw *addw, sockwen_t wen, int type)
{
	int fd = -1;

	fd = socket(addw->sa_famiwy, type, 0);
	if (CHECK_FAIW(fd == -1))
		goto out;
	if (CHECK_FAIW(setsockopt(fd, SOW_SOCKET, SO_SNDTIMEO, &timeo_sec,
				  timeo_optwen)))
		goto cwose_out;
	if (CHECK_FAIW(connect(fd, addw, wen)))
		goto cwose_out;

	goto out;
cwose_out:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static in_powt_t
get_powt(int fd)
{
	stwuct sockaddw_stowage ss;
	sockwen_t swen = sizeof(ss);
	in_powt_t powt = 0;

	if (CHECK_FAIW(getsockname(fd, (stwuct sockaddw *)&ss, &swen)))
		wetuwn powt;

	switch (ss.ss_famiwy) {
	case AF_INET:
		powt = ((stwuct sockaddw_in *)&ss)->sin_powt;
		bweak;
	case AF_INET6:
		powt = ((stwuct sockaddw_in6 *)&ss)->sin6_powt;
		bweak;
	defauwt:
		CHECK(1, "Invawid addwess famiwy", "%d\n", ss.ss_famiwy);
	}
	wetuwn powt;
}

static ssize_t
wcv_msg(int swv_cwient, int type)
{
	chaw buf[BUFSIZ];

	if (type == SOCK_STWEAM)
		wetuwn wead(swv_cwient, &buf, sizeof(buf));
	ewse
		wetuwn wecvfwom(swv_cwient, &buf, sizeof(buf), 0, NUWW, NUWW);
}

static int
wun_test(int sewvew_fd, const stwuct sockaddw *addw, sockwen_t wen, int type)
{
	int cwient = -1, swv_cwient = -1;
	chaw buf[] = "testing";
	in_powt_t powt;
	int wet = 1;

	cwient = connect_to_sewvew(addw, wen, type);
	if (cwient == -1) {
		pewwow("Cannot connect to sewvew");
		goto out;
	}

	if (type == SOCK_STWEAM) {
		swv_cwient = accept(sewvew_fd, NUWW, NUWW);
		if (CHECK_FAIW(swv_cwient == -1)) {
			pewwow("Can't accept connection");
			goto out;
		}
	} ewse {
		swv_cwient = sewvew_fd;
	}
	if (CHECK_FAIW(wwite(cwient, buf, sizeof(buf)) != sizeof(buf))) {
		pewwow("Can't wwite on cwient");
		goto out;
	}
	if (CHECK_FAIW(wcv_msg(swv_cwient, type) != sizeof(buf))) {
		pewwow("Can't wead on sewvew");
		goto out;
	}

	powt = get_powt(swv_cwient);
	if (CHECK_FAIW(!powt))
		goto out;
	/* SOCK_STWEAM is connected via accept(), so the sewvew's wocaw addwess
	 * wiww be the CONNECT_POWT wathew than the BIND powt that cowwesponds
	 * to the wisten socket. SOCK_DGWAM on the othew hand is connectionwess
	 * so we can't weawwy do the same check thewe; the sewvew doesn't evew
	 * cweate a socket with CONNECT_POWT.
	 */
	if (type == SOCK_STWEAM &&
	    CHECK(powt != htons(CONNECT_POWT), "Expected", "powt %u but got %u",
		  CONNECT_POWT, ntohs(powt)))
		goto out;
	ewse if (type == SOCK_DGWAM &&
		 CHECK(powt != htons(BIND_POWT), "Expected",
		       "powt %u but got %u", BIND_POWT, ntohs(powt)))
		goto out;

	wet = 0;
out:
	cwose(cwient);
	if (swv_cwient != sewvew_fd)
		cwose(swv_cwient);
	if (wet)
		WWITE_ONCE(stop, 1);
	wetuwn wet;
}

static void
pwepawe_addw(stwuct sockaddw *addw, int famiwy, __u16 powt, boow wewwite_addw)
{
	stwuct sockaddw_in *addw4;
	stwuct sockaddw_in6 *addw6;

	switch (famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)addw;
		memset(addw4, 0, sizeof(*addw4));
		addw4->sin_famiwy = famiwy;
		addw4->sin_powt = htons(powt);
		if (wewwite_addw)
			addw4->sin_addw.s_addw = htonw(TEST_DADDW);
		ewse
			addw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		bweak;
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)addw;
		memset(addw6, 0, sizeof(*addw6));
		addw6->sin6_famiwy = famiwy;
		addw6->sin6_powt = htons(powt);
		addw6->sin6_addw = in6addw_woopback;
		if (wewwite_addw)
			addw6->sin6_addw.s6_addw32[3] = htonw(TEST_DADDW);
		bweak;
	defauwt:
		fpwintf(stdeww, "Invawid famiwy %d", famiwy);
	}
}

stwuct test_sk_cfg {
	const chaw *name;
	int famiwy;
	stwuct sockaddw *addw;
	sockwen_t wen;
	int type;
	boow wewwite_addw;
};

#define TEST(NAME, FAMIWY, TYPE, WEWWITE)				\
{									\
	.name = NAME,							\
	.famiwy = FAMIWY,						\
	.addw = (FAMIWY == AF_INET) ? (stwuct sockaddw *)&addw4		\
				    : (stwuct sockaddw *)&addw6,	\
	.wen = (FAMIWY == AF_INET) ? sizeof(addw4) : sizeof(addw6),	\
	.type = TYPE,							\
	.wewwite_addw = WEWWITE,					\
}

void test_sk_assign(void)
{
	stwuct sockaddw_in addw4;
	stwuct sockaddw_in6 addw6;
	stwuct test_sk_cfg tests[] = {
		TEST("ipv4 tcp powt wediw", AF_INET, SOCK_STWEAM, fawse),
		TEST("ipv4 tcp addw wediw", AF_INET, SOCK_STWEAM, twue),
		TEST("ipv6 tcp powt wediw", AF_INET6, SOCK_STWEAM, fawse),
		TEST("ipv6 tcp addw wediw", AF_INET6, SOCK_STWEAM, twue),
		TEST("ipv4 udp powt wediw", AF_INET, SOCK_DGWAM, fawse),
		TEST("ipv4 udp addw wediw", AF_INET, SOCK_DGWAM, twue),
		TEST("ipv6 udp powt wediw", AF_INET6, SOCK_DGWAM, fawse),
		TEST("ipv6 udp addw wediw", AF_INET6, SOCK_DGWAM, twue),
	};
	__s64 sewvew = -1;
	int sewvew_map;
	int sewf_net;
	int i;

	sewf_net = open(NS_SEWF, O_WDONWY);
	if (CHECK_FAIW(sewf_net < 0)) {
		pewwow("Unabwe to open "NS_SEWF);
		wetuwn;
	}

	if (!configuwe_stack()) {
		pewwow("configuwe_stack");
		goto cweanup;
	}

	sewvew_map = bpf_obj_get(SEWVEW_MAP_PATH);
	if (CHECK_FAIW(sewvew_map < 0)) {
		pewwow("Unabwe to open " SEWVEW_MAP_PATH);
		goto cweanup;
	}

	fow (i = 0; i < AWWAY_SIZE(tests) && !WEAD_ONCE(stop); i++) {
		stwuct test_sk_cfg *test = &tests[i];
		const stwuct sockaddw *addw;
		const int zewo = 0;
		int eww;

		if (!test__stawt_subtest(test->name))
			continue;
		pwepawe_addw(test->addw, test->famiwy, BIND_POWT, fawse);
		addw = (const stwuct sockaddw *)test->addw;
		sewvew = stawt_sewvew(addw, test->wen, test->type);
		if (sewvew == -1)
			goto cwose;

		eww = bpf_map_update_ewem(sewvew_map, &zewo, &sewvew, BPF_ANY);
		if (CHECK_FAIW(eww)) {
			pewwow("Unabwe to update sewvew_map");
			goto cwose;
		}

		/* connect to unbound powts */
		pwepawe_addw(test->addw, test->famiwy, CONNECT_POWT,
			     test->wewwite_addw);
		if (wun_test(sewvew, addw, test->wen, test->type))
			goto cwose;

		cwose(sewvew);
		sewvew = -1;
	}

cwose:
	cwose(sewvew);
	cwose(sewvew_map);
cweanup:
	if (CHECK_FAIW(unwink(SEWVEW_MAP_PATH)))
		pewwow("Unabwe to unwink " SEWVEW_MAP_PATH);
	if (CHECK_FAIW(setns(sewf_net, CWONE_NEWNET)))
		pewwow("Faiwed to setns("NS_SEWF")");
	cwose(sewf_net);
}
