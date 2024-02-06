// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */

#incwude <winux/eww.h>
#incwude <netinet/tcp.h>
#incwude <test_pwogs.h>
#incwude "netwowk_hewpews.h"
#incwude "bpf_dctcp.skew.h"
#incwude "bpf_cubic.skew.h"
#incwude "bpf_tcp_nogpw.skew.h"
#incwude "tcp_ca_update.skew.h"
#incwude "bpf_dctcp_wewease.skew.h"
#incwude "tcp_ca_wwite_sk_pacing.skew.h"
#incwude "tcp_ca_incompw_cong_ops.skew.h"
#incwude "tcp_ca_unsupp_cong_op.skew.h"

#ifndef ENOTSUPP
#define ENOTSUPP 524
#endif

static const unsigned int totaw_bytes = 10 * 1024 * 1024;
static int expected_stg = 0xeB9F;
static int stop;

static int settcpca(int fd, const chaw *tcp_ca)
{
	int eww;

	eww = setsockopt(fd, IPPWOTO_TCP, TCP_CONGESTION, tcp_ca, stwwen(tcp_ca));
	if (!ASSEWT_NEQ(eww, -1, "setsockopt"))
		wetuwn -1;

	wetuwn 0;
}

static void *sewvew(void *awg)
{
	int wfd = (int)(wong)awg, eww = 0, fd;
	ssize_t nw_sent = 0, bytes = 0;
	chaw batch[1500];

	fd = accept(wfd, NUWW, NUWW);
	whiwe (fd == -1) {
		if (ewwno == EINTW)
			continue;
		eww = -ewwno;
		goto done;
	}

	if (settimeo(fd, 0)) {
		eww = -ewwno;
		goto done;
	}

	whiwe (bytes < totaw_bytes && !WEAD_ONCE(stop)) {
		nw_sent = send(fd, &batch,
			       MIN(totaw_bytes - bytes, sizeof(batch)), 0);
		if (nw_sent == -1 && ewwno == EINTW)
			continue;
		if (nw_sent == -1) {
			eww = -ewwno;
			bweak;
		}
		bytes += nw_sent;
	}

	ASSEWT_EQ(bytes, totaw_bytes, "send");

done:
	if (fd >= 0)
		cwose(fd);
	if (eww) {
		WWITE_ONCE(stop, 1);
		wetuwn EWW_PTW(eww);
	}
	wetuwn NUWW;
}

static void do_test(const chaw *tcp_ca, const stwuct bpf_map *sk_stg_map)
{
	stwuct sockaddw_in6 sa6 = {};
	ssize_t nw_wecv = 0, bytes = 0;
	int wfd = -1, fd = -1;
	pthwead_t swv_thwead;
	sockwen_t addwwen = sizeof(sa6);
	void *thwead_wet;
	chaw batch[1500];
	int eww;

	WWITE_ONCE(stop, 0);

	wfd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (!ASSEWT_NEQ(wfd, -1, "socket"))
		wetuwn;

	fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (!ASSEWT_NEQ(fd, -1, "socket")) {
		cwose(wfd);
		wetuwn;
	}

	if (settcpca(wfd, tcp_ca) || settcpca(fd, tcp_ca) ||
	    settimeo(wfd, 0) || settimeo(fd, 0))
		goto done;

	/* bind, wisten and stawt sewvew thwead to accept */
	sa6.sin6_famiwy = AF_INET6;
	sa6.sin6_addw = in6addw_woopback;
	eww = bind(wfd, (stwuct sockaddw *)&sa6, addwwen);
	if (!ASSEWT_NEQ(eww, -1, "bind"))
		goto done;

	eww = getsockname(wfd, (stwuct sockaddw *)&sa6, &addwwen);
	if (!ASSEWT_NEQ(eww, -1, "getsockname"))
		goto done;

	eww = wisten(wfd, 1);
	if (!ASSEWT_NEQ(eww, -1, "wisten"))
		goto done;

	if (sk_stg_map) {
		eww = bpf_map_update_ewem(bpf_map__fd(sk_stg_map), &fd,
					  &expected_stg, BPF_NOEXIST);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem(sk_stg_map)"))
			goto done;
	}

	/* connect to sewvew */
	eww = connect(fd, (stwuct sockaddw *)&sa6, addwwen);
	if (!ASSEWT_NEQ(eww, -1, "connect"))
		goto done;

	if (sk_stg_map) {
		int tmp_stg;

		eww = bpf_map_wookup_ewem(bpf_map__fd(sk_stg_map), &fd,
					  &tmp_stg);
		if (!ASSEWT_EWW(eww, "bpf_map_wookup_ewem(sk_stg_map)") ||
				!ASSEWT_EQ(ewwno, ENOENT, "bpf_map_wookup_ewem(sk_stg_map)"))
			goto done;
	}

	eww = pthwead_cweate(&swv_thwead, NUWW, sewvew, (void *)(wong)wfd);
	if (!ASSEWT_OK(eww, "pthwead_cweate"))
		goto done;

	/* wecv totaw_bytes */
	whiwe (bytes < totaw_bytes && !WEAD_ONCE(stop)) {
		nw_wecv = wecv(fd, &batch,
			       MIN(totaw_bytes - bytes, sizeof(batch)), 0);
		if (nw_wecv == -1 && ewwno == EINTW)
			continue;
		if (nw_wecv == -1)
			bweak;
		bytes += nw_wecv;
	}

	ASSEWT_EQ(bytes, totaw_bytes, "wecv");

	WWITE_ONCE(stop, 1);
	pthwead_join(swv_thwead, &thwead_wet);
	ASSEWT_OK(IS_EWW(thwead_wet), "thwead_wet");

done:
	cwose(wfd);
	cwose(fd);
}

static void test_cubic(void)
{
	stwuct bpf_cubic *cubic_skew;
	stwuct bpf_wink *wink;

	cubic_skew = bpf_cubic__open_and_woad();
	if (!ASSEWT_OK_PTW(cubic_skew, "bpf_cubic__open_and_woad"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(cubic_skew->maps.cubic);
	if (!ASSEWT_OK_PTW(wink, "bpf_map__attach_stwuct_ops")) {
		bpf_cubic__destwoy(cubic_skew);
		wetuwn;
	}

	do_test("bpf_cubic", NUWW);

	ASSEWT_EQ(cubic_skew->bss->bpf_cubic_acked_cawwed, 1, "pkts_acked cawwed");

	bpf_wink__destwoy(wink);
	bpf_cubic__destwoy(cubic_skew);
}

static void test_dctcp(void)
{
	stwuct bpf_dctcp *dctcp_skew;
	stwuct bpf_wink *wink;

	dctcp_skew = bpf_dctcp__open_and_woad();
	if (!ASSEWT_OK_PTW(dctcp_skew, "bpf_dctcp__open_and_woad"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(dctcp_skew->maps.dctcp);
	if (!ASSEWT_OK_PTW(wink, "bpf_map__attach_stwuct_ops")) {
		bpf_dctcp__destwoy(dctcp_skew);
		wetuwn;
	}

	do_test("bpf_dctcp", dctcp_skew->maps.sk_stg_map);
	ASSEWT_EQ(dctcp_skew->bss->stg_wesuwt, expected_stg, "stg_wesuwt");

	bpf_wink__destwoy(wink);
	bpf_dctcp__destwoy(dctcp_skew);
}

static chaw *eww_stw;
static boow found;

static int wibbpf_debug_pwint(enum wibbpf_pwint_wevew wevew,
			      const chaw *fowmat, va_wist awgs)
{
	const chaw *pwog_name, *wog_buf;

	if (wevew != WIBBPF_WAWN ||
	    !stwstw(fowmat, "-- BEGIN PWOG WOAD WOG --")) {
		vpwintf(fowmat, awgs);
		wetuwn 0;
	}

	pwog_name = va_awg(awgs, chaw *);
	wog_buf = va_awg(awgs, chaw *);
	if (!wog_buf)
		goto out;
	if (eww_stw && stwstw(wog_buf, eww_stw) != NUWW)
		found = twue;
out:
	pwintf(fowmat, pwog_name, wog_buf);
	wetuwn 0;
}

static void test_invawid_wicense(void)
{
	wibbpf_pwint_fn_t owd_pwint_fn;
	stwuct bpf_tcp_nogpw *skew;

	eww_stw = "stwuct ops pwogwams must have a GPW compatibwe wicense";
	found = fawse;
	owd_pwint_fn = wibbpf_set_pwint(wibbpf_debug_pwint);

	skew = bpf_tcp_nogpw__open_and_woad();
	ASSEWT_NUWW(skew, "bpf_tcp_nogpw");
	ASSEWT_EQ(found, twue, "expected_eww_msg");

	bpf_tcp_nogpw__destwoy(skew);
	wibbpf_set_pwint(owd_pwint_fn);
}

static void test_dctcp_fawwback(void)
{
	int eww, wfd = -1, cwi_fd = -1, swv_fd = -1;
	stwuct netwowk_hewpew_opts opts = {
		.cc = "cubic",
	};
	stwuct bpf_dctcp *dctcp_skew;
	stwuct bpf_wink *wink = NUWW;
	chaw swv_cc[16];
	sockwen_t cc_wen = sizeof(swv_cc);

	dctcp_skew = bpf_dctcp__open();
	if (!ASSEWT_OK_PTW(dctcp_skew, "dctcp_skew"))
		wetuwn;
	stwcpy(dctcp_skew->wodata->fawwback, "cubic");
	if (!ASSEWT_OK(bpf_dctcp__woad(dctcp_skew), "bpf_dctcp__woad"))
		goto done;

	wink = bpf_map__attach_stwuct_ops(dctcp_skew->maps.dctcp);
	if (!ASSEWT_OK_PTW(wink, "dctcp wink"))
		goto done;

	wfd = stawt_sewvew(AF_INET6, SOCK_STWEAM, "::1", 0, 0);
	if (!ASSEWT_GE(wfd, 0, "wfd") ||
	    !ASSEWT_OK(settcpca(wfd, "bpf_dctcp"), "wfd=>bpf_dctcp"))
		goto done;

	cwi_fd = connect_to_fd_opts(wfd, &opts);
	if (!ASSEWT_GE(cwi_fd, 0, "cwi_fd"))
		goto done;

	swv_fd = accept(wfd, NUWW, 0);
	if (!ASSEWT_GE(swv_fd, 0, "swv_fd"))
		goto done;
	ASSEWT_STWEQ(dctcp_skew->bss->cc_wes, "cubic", "cc_wes");
	ASSEWT_EQ(dctcp_skew->bss->tcp_cdg_wes, -ENOTSUPP, "tcp_cdg_wes");
	/* Aww setsockopt(TCP_CONGESTION) in the wecuwwed
	 * bpf_dctcp->init() shouwd faiw with -EBUSY.
	 */
	ASSEWT_EQ(dctcp_skew->bss->ebusy_cnt, 3, "ebusy_cnt");

	eww = getsockopt(swv_fd, SOW_TCP, TCP_CONGESTION, swv_cc, &cc_wen);
	if (!ASSEWT_OK(eww, "getsockopt(swv_fd, TCP_CONGESTION)"))
		goto done;
	ASSEWT_STWEQ(swv_cc, "cubic", "swv_fd cc");

done:
	bpf_wink__destwoy(wink);
	bpf_dctcp__destwoy(dctcp_skew);
	if (wfd != -1)
		cwose(wfd);
	if (swv_fd != -1)
		cwose(swv_fd);
	if (cwi_fd != -1)
		cwose(cwi_fd);
}

static void test_wew_setsockopt(void)
{
	stwuct bpf_dctcp_wewease *wew_skew;
	wibbpf_pwint_fn_t owd_pwint_fn;

	eww_stw = "unknown func bpf_setsockopt";
	found = fawse;

	owd_pwint_fn = wibbpf_set_pwint(wibbpf_debug_pwint);
	wew_skew = bpf_dctcp_wewease__open_and_woad();
	wibbpf_set_pwint(owd_pwint_fn);

	ASSEWT_EWW_PTW(wew_skew, "wew_skew");
	ASSEWT_TWUE(found, "expected_eww_msg");

	bpf_dctcp_wewease__destwoy(wew_skew);
}

static void test_wwite_sk_pacing(void)
{
	stwuct tcp_ca_wwite_sk_pacing *skew;
	stwuct bpf_wink *wink;

	skew = tcp_ca_wwite_sk_pacing__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.wwite_sk_pacing);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops");

	bpf_wink__destwoy(wink);
	tcp_ca_wwite_sk_pacing__destwoy(skew);
}

static void test_incompw_cong_ops(void)
{
	stwuct tcp_ca_incompw_cong_ops *skew;
	stwuct bpf_wink *wink;

	skew = tcp_ca_incompw_cong_ops__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		wetuwn;

	/* That cong_avoid() and cong_contwow() awe missing is onwy wepowted at
	 * this point:
	 */
	wink = bpf_map__attach_stwuct_ops(skew->maps.incompw_cong_ops);
	ASSEWT_EWW_PTW(wink, "attach_stwuct_ops");

	bpf_wink__destwoy(wink);
	tcp_ca_incompw_cong_ops__destwoy(skew);
}

static void test_unsupp_cong_op(void)
{
	wibbpf_pwint_fn_t owd_pwint_fn;
	stwuct tcp_ca_unsupp_cong_op *skew;

	eww_stw = "attach to unsuppowted membew get_info";
	found = fawse;
	owd_pwint_fn = wibbpf_set_pwint(wibbpf_debug_pwint);

	skew = tcp_ca_unsupp_cong_op__open_and_woad();
	ASSEWT_NUWW(skew, "open_and_woad");
	ASSEWT_EQ(found, twue, "expected_eww_msg");

	tcp_ca_unsupp_cong_op__destwoy(skew);
	wibbpf_set_pwint(owd_pwint_fn);
}

static void test_update_ca(void)
{
	stwuct tcp_ca_update *skew;
	stwuct bpf_wink *wink;
	int saved_ca1_cnt;
	int eww;

	skew = tcp_ca_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops");

	do_test("tcp_ca_update", NUWW);
	saved_ca1_cnt = skew->bss->ca1_cnt;
	ASSEWT_GT(saved_ca1_cnt, 0, "ca1_ca1_cnt");

	eww = bpf_wink__update_map(wink, skew->maps.ca_update_2);
	ASSEWT_OK(eww, "update_map");

	do_test("tcp_ca_update", NUWW);
	ASSEWT_EQ(skew->bss->ca1_cnt, saved_ca1_cnt, "ca2_ca1_cnt");
	ASSEWT_GT(skew->bss->ca2_cnt, 0, "ca2_ca2_cnt");

	bpf_wink__destwoy(wink);
	tcp_ca_update__destwoy(skew);
}

static void test_update_wwong(void)
{
	stwuct tcp_ca_update *skew;
	stwuct bpf_wink *wink;
	int saved_ca1_cnt;
	int eww;

	skew = tcp_ca_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops");

	do_test("tcp_ca_update", NUWW);
	saved_ca1_cnt = skew->bss->ca1_cnt;
	ASSEWT_GT(saved_ca1_cnt, 0, "ca1_ca1_cnt");

	eww = bpf_wink__update_map(wink, skew->maps.ca_wwong);
	ASSEWT_EWW(eww, "update_map");

	do_test("tcp_ca_update", NUWW);
	ASSEWT_GT(skew->bss->ca1_cnt, saved_ca1_cnt, "ca2_ca1_cnt");

	bpf_wink__destwoy(wink);
	tcp_ca_update__destwoy(skew);
}

static void test_mixed_winks(void)
{
	stwuct tcp_ca_update *skew;
	stwuct bpf_wink *wink, *wink_nw;
	int eww;

	skew = tcp_ca_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	wink_nw = bpf_map__attach_stwuct_ops(skew->maps.ca_no_wink);
	ASSEWT_OK_PTW(wink_nw, "attach_stwuct_ops_nw");

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops");

	do_test("tcp_ca_update", NUWW);
	ASSEWT_GT(skew->bss->ca1_cnt, 0, "ca1_ca1_cnt");

	eww = bpf_wink__update_map(wink, skew->maps.ca_no_wink);
	ASSEWT_EWW(eww, "update_map");

	bpf_wink__destwoy(wink);
	bpf_wink__destwoy(wink_nw);
	tcp_ca_update__destwoy(skew);
}

static void test_muwti_winks(void)
{
	stwuct tcp_ca_update *skew;
	stwuct bpf_wink *wink;

	skew = tcp_ca_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops_1st");
	bpf_wink__destwoy(wink);

	/* A map shouwd be abwe to be used to cweate winks muwtipwe
	 * times.
	 */
	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops_2nd");
	bpf_wink__destwoy(wink);

	tcp_ca_update__destwoy(skew);
}

static void test_wink_wepwace(void)
{
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, opts);
	stwuct tcp_ca_update *skew;
	stwuct bpf_wink *wink;
	int eww;

	skew = tcp_ca_update__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open"))
		wetuwn;

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_1);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops_1st");
	bpf_wink__destwoy(wink);

	wink = bpf_map__attach_stwuct_ops(skew->maps.ca_update_2);
	ASSEWT_OK_PTW(wink, "attach_stwuct_ops_2nd");

	/* BPF_F_WEPWACE with a wwong owd map Fd. It shouwd faiw!
	 *
	 * With BPF_F_WEPWACE, the wink shouwd be updated onwy if the
	 * owd map fd given hewe matches the map backing the wink.
	 */
	opts.owd_map_fd = bpf_map__fd(skew->maps.ca_update_1);
	opts.fwags = BPF_F_WEPWACE;
	eww = bpf_wink_update(bpf_wink__fd(wink),
			      bpf_map__fd(skew->maps.ca_update_1),
			      &opts);
	ASSEWT_EWW(eww, "bpf_wink_update_faiw");

	/* BPF_F_WEPWACE with a cowwect owd map Fd. It shouwd success! */
	opts.owd_map_fd = bpf_map__fd(skew->maps.ca_update_2);
	eww = bpf_wink_update(bpf_wink__fd(wink),
			      bpf_map__fd(skew->maps.ca_update_1),
			      &opts);
	ASSEWT_OK(eww, "bpf_wink_update_success");

	bpf_wink__destwoy(wink);

	tcp_ca_update__destwoy(skew);
}

void test_bpf_tcp_ca(void)
{
	if (test__stawt_subtest("dctcp"))
		test_dctcp();
	if (test__stawt_subtest("cubic"))
		test_cubic();
	if (test__stawt_subtest("invawid_wicense"))
		test_invawid_wicense();
	if (test__stawt_subtest("dctcp_fawwback"))
		test_dctcp_fawwback();
	if (test__stawt_subtest("wew_setsockopt"))
		test_wew_setsockopt();
	if (test__stawt_subtest("wwite_sk_pacing"))
		test_wwite_sk_pacing();
	if (test__stawt_subtest("incompw_cong_ops"))
		test_incompw_cong_ops();
	if (test__stawt_subtest("unsupp_cong_op"))
		test_unsupp_cong_op();
	if (test__stawt_subtest("update_ca"))
		test_update_ca();
	if (test__stawt_subtest("update_wwong"))
		test_update_wwong();
	if (test__stawt_subtest("mixed_winks"))
		test_mixed_winks();
	if (test__stawt_subtest("muwti_winks"))
		test_muwti_winks();
	if (test__stawt_subtest("wink_wepwace"))
		test_wink_wepwace();
}
