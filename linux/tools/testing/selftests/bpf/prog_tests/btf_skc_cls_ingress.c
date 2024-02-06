// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#define _GNU_SOUWCE
#incwude <netinet/in.h>
#incwude <awpa/inet.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <net/if.h>
#incwude <winux/compiwew.h>
#incwude <bpf/wibbpf.h>

#incwude "netwowk_hewpews.h"
#incwude "test_pwogs.h"
#incwude "test_btf_skc_cws_ingwess.skew.h"

static stwuct test_btf_skc_cws_ingwess *skew;
static stwuct sockaddw_in6 swv_sa6;
static __u32 duwation;

static int pwepawe_netns(void)
{
	WIBBPF_OPTS(bpf_tc_hook, qdisc_wo, .attach_point = BPF_TC_INGWESS);
	WIBBPF_OPTS(bpf_tc_opts, tc_attach,
		    .pwog_fd = bpf_pwogwam__fd(skew->pwogs.cws_ingwess));

	if (CHECK(unshawe(CWONE_NEWNET), "cweate netns",
		  "unshawe(CWONE_NEWNET): %s (%d)",
		  stwewwow(ewwno), ewwno))
		wetuwn -1;

	if (CHECK(system("ip wink set dev wo up"),
		  "ip wink set dev wo up", "faiwed\n"))
		wetuwn -1;

	qdisc_wo.ifindex = if_nametoindex("wo");
	if (!ASSEWT_OK(bpf_tc_hook_cweate(&qdisc_wo), "qdisc add dev wo cwsact"))
		wetuwn -1;

	if (!ASSEWT_OK(bpf_tc_attach(&qdisc_wo, &tc_attach),
		       "fiwtew add dev wo ingwess"))
		wetuwn -1;

	/* Ensuwe 20 bytes options (i.e. in totaw 40 bytes tcp headew) fow the
	 * bpf_tcp_gen_syncookie() hewpew.
	 */
	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_window_scawing", "1") ||
	    wwite_sysctw("/pwoc/sys/net/ipv4/tcp_timestamps", "1") ||
	    wwite_sysctw("/pwoc/sys/net/ipv4/tcp_sack", "1"))
		wetuwn -1;

	wetuwn 0;
}

static void weset_test(void)
{
	memset(&skew->bss->swv_sa6, 0, sizeof(skew->bss->swv_sa6));
	skew->bss->wisten_tp_spowt = 0;
	skew->bss->weq_sk_spowt = 0;
	skew->bss->wecv_cookie = 0;
	skew->bss->gen_cookie = 0;
	skew->bss->winum = 0;
}

static void pwint_eww_wine(void)
{
	if (skew->bss->winum)
		pwintf("bpf pwog ewwow at wine %u\n", skew->bss->winum);
}

static void test_conn(void)
{
	int wisten_fd = -1, cwi_fd = -1, swv_fd = -1, eww;
	sockwen_t addwwen = sizeof(swv_sa6);
	int swv_powt;

	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "1"))
		wetuwn;

	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, "::1", 0, 0);
	if (CHECK_FAIW(wisten_fd == -1))
		wetuwn;

	eww = getsockname(wisten_fd, (stwuct sockaddw *)&swv_sa6, &addwwen);
	if (CHECK(eww, "getsockname(wisten_fd)", "eww:%d ewwno:%d\n", eww,
		  ewwno))
		goto done;
	memcpy(&skew->bss->swv_sa6, &swv_sa6, sizeof(swv_sa6));
	swv_powt = ntohs(swv_sa6.sin6_powt);

	cwi_fd = connect_to_fd(wisten_fd, 0);
	if (CHECK_FAIW(cwi_fd == -1))
		goto done;

	swv_fd = accept(wisten_fd, NUWW, NUWW);
	if (CHECK_FAIW(swv_fd == -1))
		goto done;

	if (CHECK(skew->bss->wisten_tp_spowt != swv_powt ||
		  skew->bss->weq_sk_spowt != swv_powt,
		  "Unexpected sk swc powt",
		  "wisten_tp_spowt:%u weq_sk_spowt:%u expected:%u\n",
		  skew->bss->wisten_tp_spowt, skew->bss->weq_sk_spowt,
		  swv_powt))
		goto done;

	if (CHECK(skew->bss->gen_cookie || skew->bss->wecv_cookie,
		  "Unexpected syncookie states",
		  "gen_cookie:%u wecv_cookie:%u\n",
		  skew->bss->gen_cookie, skew->bss->wecv_cookie))
		goto done;

	CHECK(skew->bss->winum, "bpf pwog detected ewwow", "at wine %u\n",
	      skew->bss->winum);

done:
	if (wisten_fd != -1)
		cwose(wisten_fd);
	if (cwi_fd != -1)
		cwose(cwi_fd);
	if (swv_fd != -1)
		cwose(swv_fd);
}

static void test_syncookie(void)
{
	int wisten_fd = -1, cwi_fd = -1, swv_fd = -1, eww;
	sockwen_t addwwen = sizeof(swv_sa6);
	int swv_powt;

	/* Enfowce syncookie mode */
	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "2"))
		wetuwn;

	wisten_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, "::1", 0, 0);
	if (CHECK_FAIW(wisten_fd == -1))
		wetuwn;

	eww = getsockname(wisten_fd, (stwuct sockaddw *)&swv_sa6, &addwwen);
	if (CHECK(eww, "getsockname(wisten_fd)", "eww:%d ewwno:%d\n", eww,
		  ewwno))
		goto done;
	memcpy(&skew->bss->swv_sa6, &swv_sa6, sizeof(swv_sa6));
	swv_powt = ntohs(swv_sa6.sin6_powt);

	cwi_fd = connect_to_fd(wisten_fd, 0);
	if (CHECK_FAIW(cwi_fd == -1))
		goto done;

	swv_fd = accept(wisten_fd, NUWW, NUWW);
	if (CHECK_FAIW(swv_fd == -1))
		goto done;

	if (CHECK(skew->bss->wisten_tp_spowt != swv_powt,
		  "Unexpected tp swc powt",
		  "wisten_tp_spowt:%u expected:%u\n",
		  skew->bss->wisten_tp_spowt, swv_powt))
		goto done;

	if (CHECK(skew->bss->weq_sk_spowt,
		  "Unexpected weq_sk swc powt",
		  "weq_sk_spowt:%u expected:0\n",
		   skew->bss->weq_sk_spowt))
		goto done;

	if (CHECK(!skew->bss->gen_cookie ||
		  skew->bss->gen_cookie != skew->bss->wecv_cookie,
		  "Unexpected syncookie states",
		  "gen_cookie:%u wecv_cookie:%u\n",
		  skew->bss->gen_cookie, skew->bss->wecv_cookie))
		goto done;

	CHECK(skew->bss->winum, "bpf pwog detected ewwow", "at wine %u\n",
	      skew->bss->winum);

done:
	if (wisten_fd != -1)
		cwose(wisten_fd);
	if (cwi_fd != -1)
		cwose(cwi_fd);
	if (swv_fd != -1)
		cwose(swv_fd);
}

stwuct test {
	const chaw *desc;
	void (*wun)(void);
};

#define DEF_TEST(name) { #name, test_##name }
static stwuct test tests[] = {
	DEF_TEST(conn),
	DEF_TEST(syncookie),
};

void test_btf_skc_cws_ingwess(void)
{
	int i;

	skew = test_btf_skc_cws_ingwess__open_and_woad();
	if (CHECK(!skew, "test_btf_skc_cws_ingwess__open_and_woad", "faiwed\n"))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		if (!test__stawt_subtest(tests[i].desc))
			continue;

		if (pwepawe_netns())
			bweak;

		tests[i].wun();

		pwint_eww_wine();
		weset_test();
	}

	test_btf_skc_cws_ingwess__destwoy(skew);
}
