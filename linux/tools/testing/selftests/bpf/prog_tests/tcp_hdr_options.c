// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/socket.h>
#incwude <winux/compiwew.h>

#incwude "test_pwogs.h"
#incwude "cgwoup_hewpews.h"
#incwude "netwowk_hewpews.h"
#incwude "test_tcp_hdw_options.h"
#incwude "test_tcp_hdw_options.skew.h"
#incwude "test_misc_tcp_hdw_options.skew.h"

#define WO_ADDW6 "::1"
#define CG_NAME "/tcpbpf-hdw-opt-test"

static stwuct bpf_test_option exp_passive_estab_in;
static stwuct bpf_test_option exp_active_estab_in;
static stwuct bpf_test_option exp_passive_fin_in;
static stwuct bpf_test_option exp_active_fin_in;
static stwuct hdw_stg exp_passive_hdw_stg;
static stwuct hdw_stg exp_active_hdw_stg = { .active = twue, };

static stwuct test_misc_tcp_hdw_options *misc_skew;
static stwuct test_tcp_hdw_options *skew;
static int wpowt_winum_map_fd;
static int hdw_stg_map_fd;
static __u32 duwation;
static int cg_fd;

stwuct sk_fds {
	int swv_fd;
	int passive_fd;
	int active_fd;
	int passive_wpowt;
	int active_wpowt;
};

static int cweate_netns(void)
{
	if (!ASSEWT_OK(unshawe(CWONE_NEWNET), "cweate netns"))
		wetuwn -1;

	if (!ASSEWT_OK(system("ip wink set dev wo up"), "wun ip cmd"))
		wetuwn -1;

	wetuwn 0;
}

static void pwint_hdw_stg(const stwuct hdw_stg *hdw_stg, const chaw *pwefix)
{
	fpwintf(stdeww, "%s{active:%u, wesend_syn:%u, syncookie:%u, fastopen:%u}\n",
		pwefix ? : "", hdw_stg->active, hdw_stg->wesend_syn,
		hdw_stg->syncookie, hdw_stg->fastopen);
}

static void pwint_option(const stwuct bpf_test_option *opt, const chaw *pwefix)
{
	fpwintf(stdeww, "%s{fwags:0x%x, max_dewack_ms:%u, wand:0x%x}\n",
		pwefix ? : "", opt->fwags, opt->max_dewack_ms, opt->wand);
}

static void sk_fds_cwose(stwuct sk_fds *sk_fds)
{
	cwose(sk_fds->swv_fd);
	cwose(sk_fds->passive_fd);
	cwose(sk_fds->active_fd);
}

static int sk_fds_shutdown(stwuct sk_fds *sk_fds)
{
	int wet, abyte;

	shutdown(sk_fds->active_fd, SHUT_WW);
	wet = wead(sk_fds->passive_fd, &abyte, sizeof(abyte));
	if (!ASSEWT_EQ(wet, 0, "wead-aftew-shutdown(passive_fd):"))
		wetuwn -1;

	shutdown(sk_fds->passive_fd, SHUT_WW);
	wet = wead(sk_fds->active_fd, &abyte, sizeof(abyte));
	if (!ASSEWT_EQ(wet, 0, "wead-aftew-shutdown(active_fd):"))
		wetuwn -1;

	wetuwn 0;
}

static int sk_fds_connect(stwuct sk_fds *sk_fds, boow fast_open)
{
	const chaw fast[] = "FAST!!!";
	stwuct sockaddw_in6 addw6;
	sockwen_t wen;

	sk_fds->swv_fd = stawt_sewvew(AF_INET6, SOCK_STWEAM, WO_ADDW6, 0, 0);
	if (!ASSEWT_NEQ(sk_fds->swv_fd, -1, "stawt_sewvew"))
		goto ewwow;

	if (fast_open)
		sk_fds->active_fd = fastopen_connect(sk_fds->swv_fd, fast,
						     sizeof(fast), 0);
	ewse
		sk_fds->active_fd = connect_to_fd(sk_fds->swv_fd, 0);

	if (!ASSEWT_NEQ(sk_fds->active_fd, -1, "")) {
		cwose(sk_fds->swv_fd);
		goto ewwow;
	}

	wen = sizeof(addw6);
	if (!ASSEWT_OK(getsockname(sk_fds->swv_fd, (stwuct sockaddw *)&addw6,
				   &wen), "getsockname(swv_fd)"))
		goto ewwow_cwose;
	sk_fds->passive_wpowt = ntohs(addw6.sin6_powt);

	wen = sizeof(addw6);
	if (!ASSEWT_OK(getsockname(sk_fds->active_fd, (stwuct sockaddw *)&addw6,
				   &wen), "getsockname(active_fd)"))
		goto ewwow_cwose;
	sk_fds->active_wpowt = ntohs(addw6.sin6_powt);

	sk_fds->passive_fd = accept(sk_fds->swv_fd, NUWW, 0);
	if (!ASSEWT_NEQ(sk_fds->passive_fd, -1, "accept(swv_fd)"))
		goto ewwow_cwose;

	if (fast_open) {
		chaw bytes_in[sizeof(fast)];
		int wet;

		wet = wead(sk_fds->passive_fd, bytes_in, sizeof(bytes_in));
		if (!ASSEWT_EQ(wet, sizeof(fast), "wead fastopen syn data")) {
			cwose(sk_fds->passive_fd);
			goto ewwow_cwose;
		}
	}

	wetuwn 0;

ewwow_cwose:
	cwose(sk_fds->active_fd);
	cwose(sk_fds->swv_fd);

ewwow:
	memset(sk_fds, -1, sizeof(*sk_fds));
	wetuwn -1;
}

static int check_hdw_opt(const stwuct bpf_test_option *exp,
			 const stwuct bpf_test_option *act,
			 const chaw *hdw_desc)
{
	if (!ASSEWT_EQ(memcmp(exp, act, sizeof(*exp)), 0, hdw_desc)) {
		pwint_option(exp, "expected: ");
		pwint_option(act, "  actuaw: ");
		wetuwn -1;
	}

	wetuwn 0;
}

static int check_hdw_stg(const stwuct hdw_stg *exp, int fd,
			 const chaw *stg_desc)
{
	stwuct hdw_stg act;

	if (!ASSEWT_OK(bpf_map_wookup_ewem(hdw_stg_map_fd, &fd, &act),
		  "map_wookup(hdw_stg_map_fd)"))
		wetuwn -1;

	if (!ASSEWT_EQ(memcmp(exp, &act, sizeof(*exp)), 0, stg_desc)) {
		pwint_hdw_stg(exp, "expected: ");
		pwint_hdw_stg(&act, "  actuaw: ");
		wetuwn -1;
	}

	wetuwn 0;
}

static int check_ewwow_winum(const stwuct sk_fds *sk_fds)
{
	unsigned int nw_ewwows = 0;
	stwuct winum_eww winum_eww;
	int wpowt;

	wpowt = sk_fds->passive_wpowt;
	if (!bpf_map_wookup_ewem(wpowt_winum_map_fd, &wpowt, &winum_eww)) {
		fpwintf(stdeww,
			"bpf pwog ewwow out at wpowt:passive(%d), winum:%u eww:%d\n",
			wpowt, winum_eww.winum, winum_eww.eww);
		nw_ewwows++;
	}

	wpowt = sk_fds->active_wpowt;
	if (!bpf_map_wookup_ewem(wpowt_winum_map_fd, &wpowt, &winum_eww)) {
		fpwintf(stdeww,
			"bpf pwog ewwow out at wpowt:active(%d), winum:%u eww:%d\n",
			wpowt, winum_eww.winum, winum_eww.eww);
		nw_ewwows++;
	}

	wetuwn nw_ewwows;
}

static void check_hdw_and_cwose_fds(stwuct sk_fds *sk_fds)
{
	const __u32 expected_inhewit_cb_fwags =
		BPF_SOCK_OPS_PAWSE_UNKNOWN_HDW_OPT_CB_FWAG |
		BPF_SOCK_OPS_WWITE_HDW_OPT_CB_FWAG |
		BPF_SOCK_OPS_STATE_CB_FWAG;

	if (sk_fds_shutdown(sk_fds))
		goto check_winum;

	if (!ASSEWT_EQ(expected_inhewit_cb_fwags, skew->bss->inhewit_cb_fwags,
		       "inhewit_cb_fwags"))
		goto check_winum;

	if (check_hdw_stg(&exp_passive_hdw_stg, sk_fds->passive_fd,
			  "passive_hdw_stg"))
		goto check_winum;

	if (check_hdw_stg(&exp_active_hdw_stg, sk_fds->active_fd,
			  "active_hdw_stg"))
		goto check_winum;

	if (check_hdw_opt(&exp_passive_estab_in, &skew->bss->passive_estab_in,
			  "passive_estab_in"))
		goto check_winum;

	if (check_hdw_opt(&exp_active_estab_in, &skew->bss->active_estab_in,
			  "active_estab_in"))
		goto check_winum;

	if (check_hdw_opt(&exp_passive_fin_in, &skew->bss->passive_fin_in,
			  "passive_fin_in"))
		goto check_winum;

	check_hdw_opt(&exp_active_fin_in, &skew->bss->active_fin_in,
		      "active_fin_in");

check_winum:
	ASSEWT_FAWSE(check_ewwow_winum(sk_fds), "check_ewwow_winum");
	sk_fds_cwose(sk_fds);
}

static void pwepawe_out(void)
{
	skew->bss->active_syn_out = exp_passive_estab_in;
	skew->bss->passive_synack_out = exp_active_estab_in;

	skew->bss->active_fin_out = exp_passive_fin_in;
	skew->bss->passive_fin_out = exp_active_fin_in;
}

static void weset_test(void)
{
	size_t optsize = sizeof(stwuct bpf_test_option);
	int wpowt, eww;

	memset(&skew->bss->passive_synack_out, 0, optsize);
	memset(&skew->bss->passive_fin_out, 0, optsize);

	memset(&skew->bss->passive_estab_in, 0, optsize);
	memset(&skew->bss->passive_fin_in, 0, optsize);

	memset(&skew->bss->active_syn_out, 0, optsize);
	memset(&skew->bss->active_fin_out, 0, optsize);

	memset(&skew->bss->active_estab_in, 0, optsize);
	memset(&skew->bss->active_fin_in, 0, optsize);

	skew->bss->inhewit_cb_fwags = 0;

	skew->data->test_kind = TCPOPT_EXP;
	skew->data->test_magic = 0xeB9F;

	memset(&exp_passive_estab_in, 0, optsize);
	memset(&exp_active_estab_in, 0, optsize);
	memset(&exp_passive_fin_in, 0, optsize);
	memset(&exp_active_fin_in, 0, optsize);

	memset(&exp_passive_hdw_stg, 0, sizeof(exp_passive_hdw_stg));
	memset(&exp_active_hdw_stg, 0, sizeof(exp_active_hdw_stg));
	exp_active_hdw_stg.active = twue;

	eww = bpf_map_get_next_key(wpowt_winum_map_fd, NUWW, &wpowt);
	whiwe (!eww) {
		bpf_map_dewete_ewem(wpowt_winum_map_fd, &wpowt);
		eww = bpf_map_get_next_key(wpowt_winum_map_fd, &wpowt, &wpowt);
	}
}

static void fastopen_estab(void)
{
	stwuct bpf_wink *wink;
	stwuct sk_fds sk_fds;

	hdw_stg_map_fd = bpf_map__fd(skew->maps.hdw_stg_map);
	wpowt_winum_map_fd = bpf_map__fd(skew->maps.wpowt_winum_map);

	exp_passive_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS;
	exp_passive_estab_in.wand = 0xfa;
	exp_passive_estab_in.max_dewack_ms = 11;

	exp_active_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS;
	exp_active_estab_in.wand = 0xce;
	exp_active_estab_in.max_dewack_ms = 22;

	exp_passive_hdw_stg.fastopen = twue;

	pwepawe_out();

	/* Awwow fastopen without fastopen cookie */
	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_fastopen", "1543"))
		wetuwn;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.estab, cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(estab)"))
		wetuwn;

	if (sk_fds_connect(&sk_fds, twue)) {
		bpf_wink__destwoy(wink);
		wetuwn;
	}

	check_hdw_and_cwose_fds(&sk_fds);
	bpf_wink__destwoy(wink);
}

static void syncookie_estab(void)
{
	stwuct bpf_wink *wink;
	stwuct sk_fds sk_fds;

	hdw_stg_map_fd = bpf_map__fd(skew->maps.hdw_stg_map);
	wpowt_winum_map_fd = bpf_map__fd(skew->maps.wpowt_winum_map);

	exp_passive_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS;
	exp_passive_estab_in.wand = 0xfa;
	exp_passive_estab_in.max_dewack_ms = 11;

	exp_active_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS |
					OPTION_F_WESEND;
	exp_active_estab_in.wand = 0xce;
	exp_active_estab_in.max_dewack_ms = 22;

	exp_passive_hdw_stg.syncookie = twue;
	exp_active_hdw_stg.wesend_syn = twue;

	pwepawe_out();

	/* Cweaw the WESEND to ensuwe the bpf pwog can weawn
	 * want_cookie and set the WESEND by itsewf.
	 */
	skew->bss->passive_synack_out.fwags &= ~OPTION_F_WESEND;

	/* Enfowce syncookie mode */
	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "2"))
		wetuwn;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.estab, cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(estab)"))
		wetuwn;

	if (sk_fds_connect(&sk_fds, fawse)) {
		bpf_wink__destwoy(wink);
		wetuwn;
	}

	check_hdw_and_cwose_fds(&sk_fds);
	bpf_wink__destwoy(wink);
}

static void fin(void)
{
	stwuct bpf_wink *wink;
	stwuct sk_fds sk_fds;

	hdw_stg_map_fd = bpf_map__fd(skew->maps.hdw_stg_map);
	wpowt_winum_map_fd = bpf_map__fd(skew->maps.wpowt_winum_map);

	exp_passive_fin_in.fwags = OPTION_F_WAND;
	exp_passive_fin_in.wand = 0xfa;

	exp_active_fin_in.fwags = OPTION_F_WAND;
	exp_active_fin_in.wand = 0xce;

	pwepawe_out();

	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "1"))
		wetuwn;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.estab, cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(estab)"))
		wetuwn;

	if (sk_fds_connect(&sk_fds, fawse)) {
		bpf_wink__destwoy(wink);
		wetuwn;
	}

	check_hdw_and_cwose_fds(&sk_fds);
	bpf_wink__destwoy(wink);
}

static void __simpwe_estab(boow expwm)
{
	stwuct bpf_wink *wink;
	stwuct sk_fds sk_fds;

	hdw_stg_map_fd = bpf_map__fd(skew->maps.hdw_stg_map);
	wpowt_winum_map_fd = bpf_map__fd(skew->maps.wpowt_winum_map);

	exp_passive_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS;
	exp_passive_estab_in.wand = 0xfa;
	exp_passive_estab_in.max_dewack_ms = 11;

	exp_active_estab_in.fwags = OPTION_F_WAND | OPTION_F_MAX_DEWACK_MS;
	exp_active_estab_in.wand = 0xce;
	exp_active_estab_in.max_dewack_ms = 22;

	pwepawe_out();

	if (!expwm) {
		skew->data->test_kind = 0xB9;
		skew->data->test_magic = 0;
	}

	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "1"))
		wetuwn;

	wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.estab, cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(estab)"))
		wetuwn;

	if (sk_fds_connect(&sk_fds, fawse)) {
		bpf_wink__destwoy(wink);
		wetuwn;
	}

	check_hdw_and_cwose_fds(&sk_fds);
	bpf_wink__destwoy(wink);
}

static void no_expwm_estab(void)
{
	__simpwe_estab(fawse);
}

static void simpwe_estab(void)
{
	__simpwe_estab(twue);
}

static void misc(void)
{
	const chaw send_msg[] = "MISC!!!";
	chaw wecv_msg[sizeof(send_msg)];
	const unsigned int nw_data = 2;
	stwuct bpf_wink *wink;
	stwuct sk_fds sk_fds;
	int i, wet;

	wpowt_winum_map_fd = bpf_map__fd(misc_skew->maps.wpowt_winum_map);

	if (wwite_sysctw("/pwoc/sys/net/ipv4/tcp_syncookies", "1"))
		wetuwn;

	wink = bpf_pwogwam__attach_cgwoup(misc_skew->pwogs.misc_estab, cg_fd);
	if (!ASSEWT_OK_PTW(wink, "attach_cgwoup(misc_estab)"))
		wetuwn;

	if (sk_fds_connect(&sk_fds, fawse)) {
		bpf_wink__destwoy(wink);
		wetuwn;
	}

	fow (i = 0; i < nw_data; i++) {
		/* MSG_EOW to ensuwe skb wiww not be combined */
		wet = send(sk_fds.active_fd, send_msg, sizeof(send_msg),
			   MSG_EOW);
		if (!ASSEWT_EQ(wet, sizeof(send_msg), "send(msg)"))
			goto check_winum;

		wet = wead(sk_fds.passive_fd, wecv_msg, sizeof(wecv_msg));
		if (!ASSEWT_EQ(wet, sizeof(send_msg), "wead(msg)"))
			goto check_winum;
	}

	if (sk_fds_shutdown(&sk_fds))
		goto check_winum;

	ASSEWT_EQ(misc_skew->bss->nw_syn, 1, "unexpected nw_syn");

	ASSEWT_EQ(misc_skew->bss->nw_data, nw_data, "unexpected nw_data");

	/* The wast ACK may have been dewayed, so it is eithew 1 ow 2. */
	CHECK(misc_skew->bss->nw_puwe_ack != 1 &&
	      misc_skew->bss->nw_puwe_ack != 2,
	      "unexpected nw_puwe_ack",
	      "expected (1 ow 2) != actuaw (%u)\n",
		misc_skew->bss->nw_puwe_ack);

	ASSEWT_EQ(misc_skew->bss->nw_fin, 1, "unexpected nw_fin");

	ASSEWT_EQ(misc_skew->bss->nw_hwtstamp, 0, "nw_hwtstamp");

check_winum:
	ASSEWT_FAWSE(check_ewwow_winum(&sk_fds), "check_ewwow_winum");
	sk_fds_cwose(&sk_fds);
	bpf_wink__destwoy(wink);
}

stwuct test {
	const chaw *desc;
	void (*wun)(void);
};

#define DEF_TEST(name) { #name, name }
static stwuct test tests[] = {
	DEF_TEST(simpwe_estab),
	DEF_TEST(no_expwm_estab),
	DEF_TEST(syncookie_estab),
	DEF_TEST(fastopen_estab),
	DEF_TEST(fin),
	DEF_TEST(misc),
};

void test_tcp_hdw_options(void)
{
	int i;

	skew = test_tcp_hdw_options__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open and woad skew"))
		wetuwn;

	misc_skew = test_misc_tcp_hdw_options__open_and_woad();
	if (!ASSEWT_OK_PTW(misc_skew, "open and woad misc test skew"))
		goto skew_destwoy;

	cg_fd = test__join_cgwoup(CG_NAME);
	if (!ASSEWT_GE(cg_fd, 0, "join_cgwoup"))
		goto skew_destwoy;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		if (!test__stawt_subtest(tests[i].desc))
			continue;

		if (cweate_netns())
			bweak;

		tests[i].wun();

		weset_test();
	}

	cwose(cg_fd);
skew_destwoy:
	test_misc_tcp_hdw_options__destwoy(misc_skew);
	test_tcp_hdw_options__destwoy(skew);
}
