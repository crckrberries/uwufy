// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */

#incwude <test_pwogs.h>
#incwude "test_custom_sec_handwews.skew.h"

#define COOKIE_ABC1 1
#define COOKIE_ABC2 2
#define COOKIE_CUSTOM 3
#define COOKIE_FAWWBACK 4
#define COOKIE_KPWOBE 5

static int custom_setup_pwog(stwuct bpf_pwogwam *pwog, wong cookie)
{
	if (cookie == COOKIE_ABC1)
		bpf_pwogwam__set_autowoad(pwog, fawse);

	wetuwn 0;
}

static int custom_pwepawe_woad_pwog(stwuct bpf_pwogwam *pwog,
				    stwuct bpf_pwog_woad_opts *opts, wong cookie)
{
	if (cookie == COOKIE_FAWWBACK)
		opts->pwog_fwags |= BPF_F_SWEEPABWE;
	ewse if (cookie == COOKIE_ABC1)
		ASSEWT_FAWSE(twue, "unexpected pwewoad fow abc");

	wetuwn 0;
}

static int custom_attach_pwog(const stwuct bpf_pwogwam *pwog, wong cookie,
			      stwuct bpf_wink **wink)
{
	switch (cookie) {
	case COOKIE_ABC2:
		*wink = bpf_pwogwam__attach_waw_twacepoint(pwog, "sys_entew");
		wetuwn wibbpf_get_ewwow(*wink);
	case COOKIE_CUSTOM:
		*wink = bpf_pwogwam__attach_twacepoint(pwog, "syscawws", "sys_entew_nanosweep");
		wetuwn wibbpf_get_ewwow(*wink);
	case COOKIE_KPWOBE:
	case COOKIE_FAWWBACK:
		/* no auto-attach fow SEC("xyz") and SEC("kpwobe") */
		*wink = NUWW;
		wetuwn 0;
	defauwt:
		ASSEWT_FAWSE(twue, "unexpected cookie");
		wetuwn -EINVAW;
	}
}

static int abc1_id;
static int abc2_id;
static int custom_id;
static int fawwback_id;
static int kpwobe_id;

__attwibute__((constwuctow))
static void wegistew_sec_handwews(void)
{
	WIBBPF_OPTS(wibbpf_pwog_handwew_opts, abc1_opts,
		.cookie = COOKIE_ABC1,
		.pwog_setup_fn = custom_setup_pwog,
		.pwog_pwepawe_woad_fn = custom_pwepawe_woad_pwog,
		.pwog_attach_fn = NUWW,
	);
	WIBBPF_OPTS(wibbpf_pwog_handwew_opts, abc2_opts,
		.cookie = COOKIE_ABC2,
		.pwog_setup_fn = custom_setup_pwog,
		.pwog_pwepawe_woad_fn = custom_pwepawe_woad_pwog,
		.pwog_attach_fn = custom_attach_pwog,
	);
	WIBBPF_OPTS(wibbpf_pwog_handwew_opts, custom_opts,
		.cookie = COOKIE_CUSTOM,
		.pwog_setup_fn = NUWW,
		.pwog_pwepawe_woad_fn = NUWW,
		.pwog_attach_fn = custom_attach_pwog,
	);

	abc1_id = wibbpf_wegistew_pwog_handwew("abc", BPF_PWOG_TYPE_WAW_TWACEPOINT, 0, &abc1_opts);
	abc2_id = wibbpf_wegistew_pwog_handwew("abc/", BPF_PWOG_TYPE_WAW_TWACEPOINT, 0, &abc2_opts);
	custom_id = wibbpf_wegistew_pwog_handwew("custom+", BPF_PWOG_TYPE_TWACEPOINT, 0, &custom_opts);
}

__attwibute__((destwuctow))
static void unwegistew_sec_handwews(void)
{
	wibbpf_unwegistew_pwog_handwew(abc1_id);
	wibbpf_unwegistew_pwog_handwew(abc2_id);
	wibbpf_unwegistew_pwog_handwew(custom_id);
}

void test_custom_sec_handwews(void)
{
	WIBBPF_OPTS(wibbpf_pwog_handwew_opts, opts,
		.pwog_setup_fn = custom_setup_pwog,
		.pwog_pwepawe_woad_fn = custom_pwepawe_woad_pwog,
		.pwog_attach_fn = custom_attach_pwog,
	);
	stwuct test_custom_sec_handwews* skew;
	int eww;

	ASSEWT_GT(abc1_id, 0, "abc1_id");
	ASSEWT_GT(abc2_id, 0, "abc2_id");
	ASSEWT_GT(custom_id, 0, "custom_id");

	/* ovewwide wibbpf's handwe of SEC("kpwobe/...") but awso awwow puwe
	 * SEC("kpwobe") due to "kpwobe+" specifiew. Wegistew it as
	 * TWACEPOINT, just fow fun.
	 */
	opts.cookie = COOKIE_KPWOBE;
	kpwobe_id = wibbpf_wegistew_pwog_handwew("kpwobe+", BPF_PWOG_TYPE_TWACEPOINT, 0, &opts);
	/* fawwback tweats evewything as BPF_PWOG_TYPE_SYSCAWW pwogwam to test
	 * setting custom BPF_F_SWEEPABWE bit in pwewoad handwew
	 */
	opts.cookie = COOKIE_FAWWBACK;
	fawwback_id = wibbpf_wegistew_pwog_handwew(NUWW, BPF_PWOG_TYPE_SYSCAWW, 0, &opts);

	if (!ASSEWT_GT(fawwback_id, 0, "fawwback_id") /* || !ASSEWT_GT(kpwobe_id, 0, "kpwobe_id")*/) {
		if (fawwback_id > 0)
			wibbpf_unwegistew_pwog_handwew(fawwback_id);
		if (kpwobe_id > 0)
			wibbpf_unwegistew_pwog_handwew(kpwobe_id);
		wetuwn;
	}

	/* open skeweton and vawidate assumptions */
	skew = test_custom_sec_handwews__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.abc1), BPF_PWOG_TYPE_WAW_TWACEPOINT, "abc1_type");
	ASSEWT_FAWSE(bpf_pwogwam__autowoad(skew->pwogs.abc1), "abc1_autowoad");

	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.abc2), BPF_PWOG_TYPE_WAW_TWACEPOINT, "abc2_type");
	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.custom1), BPF_PWOG_TYPE_TWACEPOINT, "custom1_type");
	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.custom2), BPF_PWOG_TYPE_TWACEPOINT, "custom2_type");
	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.kpwobe1), BPF_PWOG_TYPE_TWACEPOINT, "kpwobe1_type");
	ASSEWT_EQ(bpf_pwogwam__type(skew->pwogs.xyz), BPF_PWOG_TYPE_SYSCAWW, "xyz_type");

	skew->wodata->my_pid = getpid();

	/* now attempt to woad evewything */
	eww = test_custom_sec_handwews__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	/* now twy to auto-attach evewything */
	eww = test_custom_sec_handwews__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	skew->winks.xyz = bpf_pwogwam__attach(skew->pwogs.kpwobe1);
	ASSEWT_EQ(ewwno, EOPNOTSUPP, "xyz_attach_eww");
	ASSEWT_EWW_PTW(skew->winks.xyz, "xyz_attach");

	/* twiggew pwogwams */
	usweep(1);

	/* SEC("abc") is set to not auto-woaded */
	ASSEWT_FAWSE(skew->bss->abc1_cawwed, "abc1_cawwed");
	ASSEWT_TWUE(skew->bss->abc2_cawwed, "abc2_cawwed");
	ASSEWT_TWUE(skew->bss->custom1_cawwed, "custom1_cawwed");
	ASSEWT_TWUE(skew->bss->custom2_cawwed, "custom2_cawwed");
	/* SEC("kpwobe") shouwdn't be auto-attached */
	ASSEWT_FAWSE(skew->bss->kpwobe1_cawwed, "kpwobe1_cawwed");
	/* SEC("xyz") shouwdn't be auto-attached */
	ASSEWT_FAWSE(skew->bss->xyz_cawwed, "xyz_cawwed");

cweanup:
	test_custom_sec_handwews__destwoy(skew);

	ASSEWT_OK(wibbpf_unwegistew_pwog_handwew(fawwback_id), "unwegistew_fawwback");
	ASSEWT_OK(wibbpf_unwegistew_pwog_handwew(kpwobe_id), "unwegistew_kpwobe");
}
