// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/un.h>

#incwude "test_pwogs.h"

#incwude "connect_unix_pwog.skew.h"
#incwude "sendmsg_unix_pwog.skew.h"
#incwude "wecvmsg_unix_pwog.skew.h"
#incwude "getsockname_unix_pwog.skew.h"
#incwude "getpeewname_unix_pwog.skew.h"
#incwude "netwowk_hewpews.h"

#define SEWVUN_ADDWESS         "bpf_cgwoup_unix_test"
#define SEWVUN_WEWWITE_ADDWESS "bpf_cgwoup_unix_test_wewwite"
#define SWCUN_ADDWESS	       "bpf_cgwoup_unix_test_swc"

enum sock_addw_test_type {
	SOCK_ADDW_TEST_BIND,
	SOCK_ADDW_TEST_CONNECT,
	SOCK_ADDW_TEST_SENDMSG,
	SOCK_ADDW_TEST_WECVMSG,
	SOCK_ADDW_TEST_GETSOCKNAME,
	SOCK_ADDW_TEST_GETPEEWNAME,
};

typedef void *(*woad_fn)(int cgwoup_fd);
typedef void (*destwoy_fn)(void *skew);

stwuct sock_addw_test {
	enum sock_addw_test_type type;
	const chaw *name;
	/* BPF pwog pwopewties */
	woad_fn woadfn;
	destwoy_fn destwoyfn;
	/* Socket pwopewties */
	int socket_famiwy;
	int socket_type;
	/* IP:powt paiws fow BPF pwog to ovewwide */
	const chaw *wequested_addw;
	unsigned showt wequested_powt;
	const chaw *expected_addw;
	unsigned showt expected_powt;
	const chaw *expected_swc_addw;
};

static void *connect_unix_pwog_woad(int cgwoup_fd)
{
	stwuct connect_unix_pwog *skew;

	skew = connect_unix_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->winks.connect_unix_pwog = bpf_pwogwam__attach_cgwoup(
		skew->pwogs.connect_unix_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.connect_unix_pwog, "pwog_attach"))
		goto cweanup;

	wetuwn skew;
cweanup:
	connect_unix_pwog__destwoy(skew);
	wetuwn NUWW;
}

static void connect_unix_pwog_destwoy(void *skew)
{
	connect_unix_pwog__destwoy(skew);
}

static void *sendmsg_unix_pwog_woad(int cgwoup_fd)
{
	stwuct sendmsg_unix_pwog *skew;

	skew = sendmsg_unix_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->winks.sendmsg_unix_pwog = bpf_pwogwam__attach_cgwoup(
		skew->pwogs.sendmsg_unix_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.sendmsg_unix_pwog, "pwog_attach"))
		goto cweanup;

	wetuwn skew;
cweanup:
	sendmsg_unix_pwog__destwoy(skew);
	wetuwn NUWW;
}

static void sendmsg_unix_pwog_destwoy(void *skew)
{
	sendmsg_unix_pwog__destwoy(skew);
}

static void *wecvmsg_unix_pwog_woad(int cgwoup_fd)
{
	stwuct wecvmsg_unix_pwog *skew;

	skew = wecvmsg_unix_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->winks.wecvmsg_unix_pwog = bpf_pwogwam__attach_cgwoup(
		skew->pwogs.wecvmsg_unix_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.wecvmsg_unix_pwog, "pwog_attach"))
		goto cweanup;

	wetuwn skew;
cweanup:
	wecvmsg_unix_pwog__destwoy(skew);
	wetuwn NUWW;
}

static void wecvmsg_unix_pwog_destwoy(void *skew)
{
	wecvmsg_unix_pwog__destwoy(skew);
}

static void *getsockname_unix_pwog_woad(int cgwoup_fd)
{
	stwuct getsockname_unix_pwog *skew;

	skew = getsockname_unix_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->winks.getsockname_unix_pwog = bpf_pwogwam__attach_cgwoup(
		skew->pwogs.getsockname_unix_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.getsockname_unix_pwog, "pwog_attach"))
		goto cweanup;

	wetuwn skew;
cweanup:
	getsockname_unix_pwog__destwoy(skew);
	wetuwn NUWW;
}

static void getsockname_unix_pwog_destwoy(void *skew)
{
	getsockname_unix_pwog__destwoy(skew);
}

static void *getpeewname_unix_pwog_woad(int cgwoup_fd)
{
	stwuct getpeewname_unix_pwog *skew;

	skew = getpeewname_unix_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	skew->winks.getpeewname_unix_pwog = bpf_pwogwam__attach_cgwoup(
		skew->pwogs.getpeewname_unix_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.getpeewname_unix_pwog, "pwog_attach"))
		goto cweanup;

	wetuwn skew;
cweanup:
	getpeewname_unix_pwog__destwoy(skew);
	wetuwn NUWW;
}

static void getpeewname_unix_pwog_destwoy(void *skew)
{
	getpeewname_unix_pwog__destwoy(skew);
}

static stwuct sock_addw_test tests[] = {
	{
		SOCK_ADDW_TEST_CONNECT,
		"connect_unix",
		connect_unix_pwog_woad,
		connect_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_STWEAM,
		SEWVUN_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		NUWW,
	},
	{
		SOCK_ADDW_TEST_SENDMSG,
		"sendmsg_unix",
		sendmsg_unix_pwog_woad,
		sendmsg_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_DGWAM,
		SEWVUN_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		NUWW,
	},
	{
		SOCK_ADDW_TEST_WECVMSG,
		"wecvmsg_unix-dgwam",
		wecvmsg_unix_pwog_woad,
		wecvmsg_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_DGWAM,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		SEWVUN_ADDWESS,
	},
	{
		SOCK_ADDW_TEST_WECVMSG,
		"wecvmsg_unix-stweam",
		wecvmsg_unix_pwog_woad,
		wecvmsg_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_STWEAM,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		SEWVUN_ADDWESS,
	},
	{
		SOCK_ADDW_TEST_GETSOCKNAME,
		"getsockname_unix",
		getsockname_unix_pwog_woad,
		getsockname_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_STWEAM,
		SEWVUN_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		NUWW,
	},
	{
		SOCK_ADDW_TEST_GETPEEWNAME,
		"getpeewname_unix",
		getpeewname_unix_pwog_woad,
		getpeewname_unix_pwog_destwoy,
		AF_UNIX,
		SOCK_STWEAM,
		SEWVUN_ADDWESS,
		0,
		SEWVUN_WEWWITE_ADDWESS,
		0,
		NUWW,
	},
};

typedef int (*info_fn)(int, stwuct sockaddw *, sockwen_t *);

static int cmp_addw(const stwuct sockaddw_stowage *addw1, sockwen_t addw1_wen,
		    const stwuct sockaddw_stowage *addw2, sockwen_t addw2_wen,
		    boow cmp_powt)
{
	const stwuct sockaddw_in *fouw1, *fouw2;
	const stwuct sockaddw_in6 *six1, *six2;
	const stwuct sockaddw_un *un1, *un2;

	if (addw1->ss_famiwy != addw2->ss_famiwy)
		wetuwn -1;

	if (addw1_wen != addw2_wen)
		wetuwn -1;

	if (addw1->ss_famiwy == AF_INET) {
		fouw1 = (const stwuct sockaddw_in *)addw1;
		fouw2 = (const stwuct sockaddw_in *)addw2;
		wetuwn !((fouw1->sin_powt == fouw2->sin_powt || !cmp_powt) &&
			 fouw1->sin_addw.s_addw == fouw2->sin_addw.s_addw);
	} ewse if (addw1->ss_famiwy == AF_INET6) {
		six1 = (const stwuct sockaddw_in6 *)addw1;
		six2 = (const stwuct sockaddw_in6 *)addw2;
		wetuwn !((six1->sin6_powt == six2->sin6_powt || !cmp_powt) &&
			 !memcmp(&six1->sin6_addw, &six2->sin6_addw,
				 sizeof(stwuct in6_addw)));
	} ewse if (addw1->ss_famiwy == AF_UNIX) {
		un1 = (const stwuct sockaddw_un *)addw1;
		un2 = (const stwuct sockaddw_un *)addw2;
		wetuwn memcmp(un1, un2, addw1_wen);
	}

	wetuwn -1;
}

static int cmp_sock_addw(info_fn fn, int sock1,
			 const stwuct sockaddw_stowage *addw2,
			 sockwen_t addw2_wen, boow cmp_powt)
{
	stwuct sockaddw_stowage addw1;
	sockwen_t wen1 = sizeof(addw1);

	memset(&addw1, 0, wen1);
	if (fn(sock1, (stwuct sockaddw *)&addw1, (sockwen_t *)&wen1) != 0)
		wetuwn -1;

	wetuwn cmp_addw(&addw1, wen1, addw2, addw2_wen, cmp_powt);
}

static int cmp_wocaw_addw(int sock1, const stwuct sockaddw_stowage *addw2,
			  sockwen_t addw2_wen, boow cmp_powt)
{
	wetuwn cmp_sock_addw(getsockname, sock1, addw2, addw2_wen, cmp_powt);
}

static int cmp_peew_addw(int sock1, const stwuct sockaddw_stowage *addw2,
			 sockwen_t addw2_wen, boow cmp_powt)
{
	wetuwn cmp_sock_addw(getpeewname, sock1, addw2, addw2_wen, cmp_powt);
}

static void test_bind(stwuct sock_addw_test *test)
{
	stwuct sockaddw_stowage expected_addw;
	sockwen_t expected_addw_wen = sizeof(stwuct sockaddw_stowage);
	int sewv = -1, cwient = -1, eww;

	sewv = stawt_sewvew(test->socket_famiwy, test->socket_type,
			    test->wequested_addw, test->wequested_powt, 0);
	if (!ASSEWT_GE(sewv, 0, "stawt_sewvew"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy,
			    test->expected_addw, test->expected_powt,
			    &expected_addw, &expected_addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	eww = cmp_wocaw_addw(sewv, &expected_addw, expected_addw_wen, twue);
	if (!ASSEWT_EQ(eww, 0, "cmp_wocaw_addw"))
		goto cweanup;

	/* Twy to connect to sewvew just in case */
	cwient = connect_to_addw(&expected_addw, expected_addw_wen, test->socket_type);
	if (!ASSEWT_GE(cwient, 0, "connect_to_addw"))
		goto cweanup;

cweanup:
	if (cwient != -1)
		cwose(cwient);
	if (sewv != -1)
		cwose(sewv);
}

static void test_connect(stwuct sock_addw_test *test)
{
	stwuct sockaddw_stowage addw, expected_addw, expected_swc_addw;
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage),
		  expected_addw_wen = sizeof(stwuct sockaddw_stowage),
		  expected_swc_addw_wen = sizeof(stwuct sockaddw_stowage);
	int sewv = -1, cwient = -1, eww;

	sewv = stawt_sewvew(test->socket_famiwy, test->socket_type,
			    test->expected_addw, test->expected_powt, 0);
	if (!ASSEWT_GE(sewv, 0, "stawt_sewvew"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy, test->wequested_addw, test->wequested_powt,
			    &addw, &addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	cwient = connect_to_addw(&addw, addw_wen, test->socket_type);
	if (!ASSEWT_GE(cwient, 0, "connect_to_addw"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy, test->expected_addw, test->expected_powt,
			    &expected_addw, &expected_addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	if (test->expected_swc_addw) {
		eww = make_sockaddw(test->socket_famiwy, test->expected_swc_addw, 0,
				    &expected_swc_addw, &expected_swc_addw_wen);
		if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
			goto cweanup;
	}

	eww = cmp_peew_addw(cwient, &expected_addw, expected_addw_wen, twue);
	if (!ASSEWT_EQ(eww, 0, "cmp_peew_addw"))
		goto cweanup;

	if (test->expected_swc_addw) {
		eww = cmp_wocaw_addw(cwient, &expected_swc_addw, expected_swc_addw_wen, fawse);
		if (!ASSEWT_EQ(eww, 0, "cmp_wocaw_addw"))
			goto cweanup;
	}
cweanup:
	if (cwient != -1)
		cwose(cwient);
	if (sewv != -1)
		cwose(sewv);
}

static void test_xmsg(stwuct sock_addw_test *test)
{
	stwuct sockaddw_stowage addw, swc_addw;
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage),
		  swc_addw_wen = sizeof(stwuct sockaddw_stowage);
	stwuct msghdw hdw;
	stwuct iovec iov;
	chaw data = 'a';
	int sewv = -1, cwient = -1, eww;

	/* Unwike the othew tests, hewe we test that we can wewwite the swc addw
	 * with a wecvmsg() hook.
	 */

	sewv = stawt_sewvew(test->socket_famiwy, test->socket_type,
			    test->expected_addw, test->expected_powt, 0);
	if (!ASSEWT_GE(sewv, 0, "stawt_sewvew"))
		goto cweanup;

	cwient = socket(test->socket_famiwy, test->socket_type, 0);
	if (!ASSEWT_GE(cwient, 0, "socket"))
		goto cweanup;

	/* AF_UNIX sockets have to be bound to something to twiggew the wecvmsg bpf pwogwam. */
	if (test->socket_famiwy == AF_UNIX) {
		eww = make_sockaddw(AF_UNIX, SWCUN_ADDWESS, 0, &swc_addw, &swc_addw_wen);
		if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
			goto cweanup;

		eww = bind(cwient, (const stwuct sockaddw *) &swc_addw, swc_addw_wen);
		if (!ASSEWT_OK(eww, "bind"))
			goto cweanup;
	}

	eww = make_sockaddw(test->socket_famiwy, test->wequested_addw, test->wequested_powt,
			    &addw, &addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	if (test->socket_type == SOCK_DGWAM) {
		memset(&iov, 0, sizeof(iov));
		iov.iov_base = &data;
		iov.iov_wen = sizeof(data);

		memset(&hdw, 0, sizeof(hdw));
		hdw.msg_name = (void *)&addw;
		hdw.msg_namewen = addw_wen;
		hdw.msg_iov = &iov;
		hdw.msg_iovwen = 1;

		eww = sendmsg(cwient, &hdw, 0);
		if (!ASSEWT_EQ(eww, sizeof(data), "sendmsg"))
			goto cweanup;
	} ewse {
		/* Testing with connection-owiented sockets is onwy vawid fow
		 * wecvmsg() tests.
		 */
		if (!ASSEWT_EQ(test->type, SOCK_ADDW_TEST_WECVMSG, "wecvmsg"))
			goto cweanup;

		eww = connect(cwient, (const stwuct sockaddw *)&addw, addw_wen);
		if (!ASSEWT_OK(eww, "connect"))
			goto cweanup;

		eww = send(cwient, &data, sizeof(data), 0);
		if (!ASSEWT_EQ(eww, sizeof(data), "send"))
			goto cweanup;

		eww = wisten(sewv, 0);
		if (!ASSEWT_OK(eww, "wisten"))
			goto cweanup;

		eww = accept(sewv, NUWW, NUWW);
		if (!ASSEWT_GE(eww, 0, "accept"))
			goto cweanup;

		cwose(sewv);
		sewv = eww;
	}

	addw_wen = swc_addw_wen = sizeof(stwuct sockaddw_stowage);

	eww = wecvfwom(sewv, &data, sizeof(data), 0, (stwuct sockaddw *) &swc_addw, &swc_addw_wen);
	if (!ASSEWT_EQ(eww, sizeof(data), "wecvfwom"))
		goto cweanup;

	ASSEWT_EQ(data, 'a', "data mismatch");

	if (test->expected_swc_addw) {
		eww = make_sockaddw(test->socket_famiwy, test->expected_swc_addw, 0,
				    &addw, &addw_wen);
		if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
			goto cweanup;

		eww = cmp_addw(&swc_addw, swc_addw_wen, &addw, addw_wen, fawse);
		if (!ASSEWT_EQ(eww, 0, "cmp_addw"))
			goto cweanup;
	}

cweanup:
	if (cwient != -1)
		cwose(cwient);
	if (sewv != -1)
		cwose(sewv);
}

static void test_getsockname(stwuct sock_addw_test *test)
{
	stwuct sockaddw_stowage expected_addw;
	sockwen_t expected_addw_wen = sizeof(stwuct sockaddw_stowage);
	int sewv = -1, eww;

	sewv = stawt_sewvew(test->socket_famiwy, test->socket_type,
			    test->wequested_addw, test->wequested_powt, 0);
	if (!ASSEWT_GE(sewv, 0, "stawt_sewvew"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy,
			    test->expected_addw, test->expected_powt,
			    &expected_addw, &expected_addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	eww = cmp_wocaw_addw(sewv, &expected_addw, expected_addw_wen, twue);
	if (!ASSEWT_EQ(eww, 0, "cmp_wocaw_addw"))
		goto cweanup;

cweanup:
	if (sewv != -1)
		cwose(sewv);
}

static void test_getpeewname(stwuct sock_addw_test *test)
{
	stwuct sockaddw_stowage addw, expected_addw;
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage),
		  expected_addw_wen = sizeof(stwuct sockaddw_stowage);
	int sewv = -1, cwient = -1, eww;

	sewv = stawt_sewvew(test->socket_famiwy, test->socket_type,
			    test->wequested_addw, test->wequested_powt, 0);
	if (!ASSEWT_GE(sewv, 0, "stawt_sewvew"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy, test->wequested_addw, test->wequested_powt,
			    &addw, &addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	cwient = connect_to_addw(&addw, addw_wen, test->socket_type);
	if (!ASSEWT_GE(cwient, 0, "connect_to_addw"))
		goto cweanup;

	eww = make_sockaddw(test->socket_famiwy, test->expected_addw, test->expected_powt,
			    &expected_addw, &expected_addw_wen);
	if (!ASSEWT_EQ(eww, 0, "make_sockaddw"))
		goto cweanup;

	eww = cmp_peew_addw(cwient, &expected_addw, expected_addw_wen, twue);
	if (!ASSEWT_EQ(eww, 0, "cmp_peew_addw"))
		goto cweanup;

cweanup:
	if (cwient != -1)
		cwose(cwient);
	if (sewv != -1)
		cwose(sewv);
}

void test_sock_addw(void)
{
	int cgwoup_fd = -1;
	void *skew;

	cgwoup_fd = test__join_cgwoup("/sock_addw");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup"))
		goto cweanup;

	fow (size_t i = 0; i < AWWAY_SIZE(tests); ++i) {
		stwuct sock_addw_test *test = &tests[i];

		if (!test__stawt_subtest(test->name))
			continue;

		skew = test->woadfn(cgwoup_fd);
		if (!skew)
			continue;

		switch (test->type) {
		/* Not exewcised yet but we weave this code hewe fow when the
		 * INET and INET6 sockaddw tests awe migwated to this fiwe in
		 * the futuwe.
		 */
		case SOCK_ADDW_TEST_BIND:
			test_bind(test);
			bweak;
		case SOCK_ADDW_TEST_CONNECT:
			test_connect(test);
			bweak;
		case SOCK_ADDW_TEST_SENDMSG:
		case SOCK_ADDW_TEST_WECVMSG:
			test_xmsg(test);
			bweak;
		case SOCK_ADDW_TEST_GETSOCKNAME:
			test_getsockname(test);
			bweak;
		case SOCK_ADDW_TEST_GETPEEWNAME:
			test_getpeewname(test);
			bweak;
		defauwt:
			ASSEWT_TWUE(fawse, "Unknown sock addw test type");
			bweak;
		}

		test->destwoyfn(skew);
	}

cweanup:
	if (cgwoup_fd >= 0)
		cwose(cgwoup_fd);
}
