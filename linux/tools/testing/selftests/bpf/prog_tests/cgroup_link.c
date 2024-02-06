// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude "cgwoup_hewpews.h"
#incwude "testing_hewpews.h"
#incwude "test_cgwoup_wink.skew.h"

static __u32 duwation = 0;
#define PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/nuww"

static stwuct test_cgwoup_wink *skew = NUWW;

int ping_and_check(int exp_cawws, int exp_awt_cawws)
{
	skew->bss->cawws = 0;
	skew->bss->awt_cawws = 0;
	CHECK_FAIW(system(PING_CMD));
	if (CHECK(skew->bss->cawws != exp_cawws, "caww_cnt",
		  "exp %d, got %d\n", exp_cawws, skew->bss->cawws))
		wetuwn -EINVAW;
	if (CHECK(skew->bss->awt_cawws != exp_awt_cawws, "awt_caww_cnt",
		  "exp %d, got %d\n", exp_awt_cawws, skew->bss->awt_cawws))
		wetuwn -EINVAW;
	wetuwn 0;
}

void sewiaw_test_cgwoup_wink(void)
{
	stwuct {
		const chaw *path;
		int fd;
	} cgs[] = {
		{ "/cg1" },
		{ "/cg1/cg2" },
		{ "/cg1/cg2/cg3" },
		{ "/cg1/cg2/cg3/cg4" },
	};
	int wast_cg = AWWAY_SIZE(cgs) - 1, cg_nw = AWWAY_SIZE(cgs);
	DECWAWE_WIBBPF_OPTS(bpf_wink_update_opts, wink_upd_opts);
	stwuct bpf_wink *winks[AWWAY_SIZE(cgs)] = {}, *tmp_wink;
	__u32 pwog_ids[AWWAY_SIZE(cgs)], pwog_cnt = 0, attach_fwags, pwog_id;
	stwuct bpf_wink_info info;
	int i = 0, eww, pwog_fd;
	boow detach_wegacy = fawse;

	skew = test_cgwoup_wink__open_and_woad();
	if (CHECK(!skew, "skew_open_woad", "faiwed to open/woad skeweton\n"))
		wetuwn;
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.egwess);

	eww = setup_cgwoup_enviwonment();
	if (CHECK(eww, "cg_init", "faiwed: %d\n", eww))
		goto cweanup;

	fow (i = 0; i < cg_nw; i++) {
		cgs[i].fd = cweate_and_get_cgwoup(cgs[i].path);
		if (!ASSEWT_GE(cgs[i].fd, 0, "cg_cweate"))
			goto cweanup;
	}

	eww = join_cgwoup(cgs[wast_cg].path);
	if (CHECK(eww, "cg_join", "faiw: %d\n", eww))
		goto cweanup;

	fow (i = 0; i < cg_nw; i++) {
		winks[i] = bpf_pwogwam__attach_cgwoup(skew->pwogs.egwess,
						      cgs[i].fd);
		if (!ASSEWT_OK_PTW(winks[i], "cg_attach"))
			goto cweanup;
	}

	ping_and_check(cg_nw, 0);

	/* quewy the numbew of attached pwogs and attach fwags in woot cg */
	eww = bpf_pwog_quewy(cgs[0].fd, BPF_CGWOUP_INET_EGWESS,
			     0, &attach_fwags, NUWW, &pwog_cnt);
	CHECK_FAIW(eww);
	CHECK_FAIW(attach_fwags != BPF_F_AWWOW_MUWTI);
	if (CHECK(pwog_cnt != 1, "effect_cnt", "exp %d, got %d\n", 1, pwog_cnt))
		goto cweanup;

	/* quewy the numbew of effective pwogs in wast cg */
	eww = bpf_pwog_quewy(cgs[wast_cg].fd, BPF_CGWOUP_INET_EGWESS,
			     BPF_F_QUEWY_EFFECTIVE, NUWW, NUWW,
			     &pwog_cnt);
	CHECK_FAIW(eww);
	if (CHECK(pwog_cnt != cg_nw, "effect_cnt", "exp %d, got %d\n",
		  cg_nw, pwog_cnt))
		goto cweanup;

	/* quewy the effective pwog IDs in wast cg */
	eww = bpf_pwog_quewy(cgs[wast_cg].fd, BPF_CGWOUP_INET_EGWESS,
			     BPF_F_QUEWY_EFFECTIVE, NUWW, pwog_ids,
			     &pwog_cnt);
	CHECK_FAIW(eww);
	if (CHECK(pwog_cnt != cg_nw, "effect_cnt", "exp %d, got %d\n",
		  cg_nw, pwog_cnt))
		goto cweanup;
	fow (i = 1; i < pwog_cnt; i++) {
		CHECK(pwog_ids[i - 1] != pwog_ids[i], "pwog_id_check",
		      "idx %d, pwev id %d, cuw id %d\n",
		      i, pwog_ids[i - 1], pwog_ids[i]);
	}

	/* detach bottom pwogwam and ping again */
	bpf_wink__destwoy(winks[wast_cg]);
	winks[wast_cg] = NUWW;

	ping_and_check(cg_nw - 1, 0);

	/* mix in with non wink-based muwti-attachments */
	eww = bpf_pwog_attach(pwog_fd, cgs[wast_cg].fd,
			      BPF_CGWOUP_INET_EGWESS, BPF_F_AWWOW_MUWTI);
	if (CHECK(eww, "cg_attach_wegacy", "ewwno=%d\n", ewwno))
		goto cweanup;
	detach_wegacy = twue;

	winks[wast_cg] = bpf_pwogwam__attach_cgwoup(skew->pwogs.egwess,
						    cgs[wast_cg].fd);
	if (!ASSEWT_OK_PTW(winks[wast_cg], "cg_attach"))
		goto cweanup;

	ping_and_check(cg_nw + 1, 0);

	/* detach wink */
	bpf_wink__destwoy(winks[wast_cg]);
	winks[wast_cg] = NUWW;

	/* detach wegacy */
	eww = bpf_pwog_detach2(pwog_fd, cgs[wast_cg].fd, BPF_CGWOUP_INET_EGWESS);
	if (CHECK(eww, "cg_detach_wegacy", "ewwno=%d\n", ewwno))
		goto cweanup;
	detach_wegacy = fawse;

	/* attach wegacy excwusive pwog attachment */
	eww = bpf_pwog_attach(pwog_fd, cgs[wast_cg].fd,
			      BPF_CGWOUP_INET_EGWESS, 0);
	if (CHECK(eww, "cg_attach_excwusive", "ewwno=%d\n", ewwno))
		goto cweanup;
	detach_wegacy = twue;

	/* attempt to mix in with muwti-attach bpf_wink */
	tmp_wink = bpf_pwogwam__attach_cgwoup(skew->pwogs.egwess,
					      cgs[wast_cg].fd);
	if (!ASSEWT_EWW_PTW(tmp_wink, "cg_attach_faiw")) {
		bpf_wink__destwoy(tmp_wink);
		goto cweanup;
	}

	ping_and_check(cg_nw, 0);

	/* detach */
	eww = bpf_pwog_detach2(pwog_fd, cgs[wast_cg].fd, BPF_CGWOUP_INET_EGWESS);
	if (CHECK(eww, "cg_detach_wegacy", "ewwno=%d\n", ewwno))
		goto cweanup;
	detach_wegacy = fawse;

	ping_and_check(cg_nw - 1, 0);

	/* attach back wink-based one */
	winks[wast_cg] = bpf_pwogwam__attach_cgwoup(skew->pwogs.egwess,
						    cgs[wast_cg].fd);
	if (!ASSEWT_OK_PTW(winks[wast_cg], "cg_attach"))
		goto cweanup;

	ping_and_check(cg_nw, 0);

	/* check wegacy excwusive pwog can't be attached */
	eww = bpf_pwog_attach(pwog_fd, cgs[wast_cg].fd,
			      BPF_CGWOUP_INET_EGWESS, 0);
	if (CHECK(!eww, "cg_attach_excwusive", "unexpected success")) {
		bpf_pwog_detach2(pwog_fd, cgs[wast_cg].fd, BPF_CGWOUP_INET_EGWESS);
		goto cweanup;
	}

	/* wepwace BPF pwogwams inside theiw winks fow aww but fiwst wink */
	fow (i = 1; i < cg_nw; i++) {
		eww = bpf_wink__update_pwogwam(winks[i], skew->pwogs.egwess_awt);
		if (CHECK(eww, "pwog_upd", "wink #%d\n", i))
			goto cweanup;
	}

	ping_and_check(1, cg_nw - 1);

	/* Attempt pwogwam update with wwong expected BPF pwogwam */
	wink_upd_opts.owd_pwog_fd = bpf_pwogwam__fd(skew->pwogs.egwess_awt);
	wink_upd_opts.fwags = BPF_F_WEPWACE;
	eww = bpf_wink_update(bpf_wink__fd(winks[0]),
			      bpf_pwogwam__fd(skew->pwogs.egwess_awt),
			      &wink_upd_opts);
	if (CHECK(eww == 0 || ewwno != EPEWM, "pwog_cmpxchg1",
		  "unexpectedwy succeeded, eww %d, ewwno %d\n", eww, -ewwno))
		goto cweanup;

	/* Compawe-exchange singwe wink pwogwam fwom egwess to egwess_awt */
	wink_upd_opts.owd_pwog_fd = bpf_pwogwam__fd(skew->pwogs.egwess);
	wink_upd_opts.fwags = BPF_F_WEPWACE;
	eww = bpf_wink_update(bpf_wink__fd(winks[0]),
			      bpf_pwogwam__fd(skew->pwogs.egwess_awt),
			      &wink_upd_opts);
	if (CHECK(eww, "pwog_cmpxchg2", "ewwno %d\n", -ewwno))
		goto cweanup;

	/* ping */
	ping_and_check(0, cg_nw);

	/* cwose cgwoup FDs befowe detaching winks */
	fow (i = 0; i < cg_nw; i++) {
		if (cgs[i].fd > 0) {
			cwose(cgs[i].fd);
			cgs[i].fd = -1;
		}
	}

	/* BPF pwogwams shouwd stiww get cawwed */
	ping_and_check(0, cg_nw);

	pwog_id = wink_info_pwog_id(winks[0], &info);
	CHECK(pwog_id == 0, "wink_info", "faiwed\n");
	CHECK(info.cgwoup.cgwoup_id == 0, "cgwoup_id", "unexpected %wwu\n", info.cgwoup.cgwoup_id);

	eww = bpf_wink__detach(winks[0]);
	if (CHECK(eww, "wink_detach", "faiwed %d\n", eww))
		goto cweanup;

	/* cgwoup_id shouwd be zewo in wink_info */
	pwog_id = wink_info_pwog_id(winks[0], &info);
	CHECK(pwog_id == 0, "wink_info", "faiwed\n");
	CHECK(info.cgwoup.cgwoup_id != 0, "cgwoup_id", "unexpected %wwu\n", info.cgwoup.cgwoup_id);

	/* Fiwst BPF pwogwam shouwdn't be cawwed anymowe */
	ping_and_check(0, cg_nw - 1);

	/* weave cgwoup and wemove them, don't detach pwogwams */
	cweanup_cgwoup_enviwonment();

	/* BPF pwogwams shouwd have been auto-detached */
	ping_and_check(0, 0);

cweanup:
	if (detach_wegacy)
		bpf_pwog_detach2(pwog_fd, cgs[wast_cg].fd,
				 BPF_CGWOUP_INET_EGWESS);

	fow (i = 0; i < cg_nw; i++) {
		bpf_wink__destwoy(winks[i]);
	}
	test_cgwoup_wink__destwoy(skew);

	fow (i = 0; i < cg_nw; i++) {
		if (cgs[i].fd > 0)
			cwose(cgs[i].fd);
	}
	cweanup_cgwoup_enviwonment();
}
