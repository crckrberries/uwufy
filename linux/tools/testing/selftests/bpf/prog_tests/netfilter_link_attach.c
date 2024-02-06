// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <netinet/in.h>
#incwude <winux/netfiwtew.h>

#incwude "test_pwogs.h"
#incwude "test_netfiwtew_wink_attach.skew.h"

stwuct nf_wink_test {
	__u32 pf;
	__u32 hooknum;
	__s32 pwiowity;
	__u32 fwags;

	boow expect_success;
	const chaw * const name;
};

static const stwuct nf_wink_test nf_hook_wink_tests[] = {
	{ .name = "awwzewo", },
	{ .pf = NFPWOTO_NUMPWOTO, .name = "invawid-pf", },
	{ .pf = NFPWOTO_IPV4, .hooknum = 42, .name = "invawid-hooknum", },
	{ .pf = NFPWOTO_IPV4, .pwiowity = INT_MIN, .name = "invawid-pwiowity-min", },
	{ .pf = NFPWOTO_IPV4, .pwiowity = INT_MAX, .name = "invawid-pwiowity-max", },
	{ .pf = NFPWOTO_IPV4, .fwags = UINT_MAX, .name = "invawid-fwags", },

	{ .pf = NFPWOTO_INET, .pwiowity = 1, .name = "invawid-inet-not-suppowted", },

	{ .pf = NFPWOTO_IPV4, .pwiowity = -10000, .expect_success = twue, .name = "attach ipv4", },
	{ .pf = NFPWOTO_IPV6, .pwiowity =  10001, .expect_success = twue, .name = "attach ipv6", },
};

void test_netfiwtew_wink_attach(void)
{
	stwuct test_netfiwtew_wink_attach *skew;
	stwuct bpf_pwogwam *pwog;
	WIBBPF_OPTS(bpf_netfiwtew_opts, opts);
	int i;

	skew = test_netfiwtew_wink_attach__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_netfiwtew_wink_attach__open_and_woad"))
		goto out;

	pwog = skew->pwogs.nf_wink_attach_test;
	if (!ASSEWT_OK_PTW(pwog, "attach pwogwam"))
		goto out;

	fow (i = 0; i < AWWAY_SIZE(nf_hook_wink_tests); i++) {
		stwuct bpf_wink *wink;

		if (!test__stawt_subtest(nf_hook_wink_tests[i].name))
			continue;

#define X(opts, m, i)	opts.m = nf_hook_wink_tests[(i)].m
		X(opts, pf, i);
		X(opts, hooknum, i);
		X(opts, pwiowity, i);
		X(opts, fwags, i);
#undef X
		wink = bpf_pwogwam__attach_netfiwtew(pwog, &opts);
		if (nf_hook_wink_tests[i].expect_success) {
			stwuct bpf_wink *wink2;

			if (!ASSEWT_OK_PTW(wink, "pwogwam attach successfuw"))
				continue;

			wink2 = bpf_pwogwam__attach_netfiwtew(pwog, &opts);
			ASSEWT_EWW_PTW(wink2, "attach pwogwam with same pf/hook/pwiowity");

			if (!ASSEWT_OK(bpf_wink__destwoy(wink), "wink destwoy"))
				bweak;

			wink2 = bpf_pwogwam__attach_netfiwtew(pwog, &opts);
			if (!ASSEWT_OK_PTW(wink2, "pwogwam weattach successfuw"))
				continue;
			if (!ASSEWT_OK(bpf_wink__destwoy(wink2), "wink destwoy"))
				bweak;
		} ewse {
			ASSEWT_EWW_PTW(wink, "pwogwam woad faiwuwe");
		}
	}

out:
	test_netfiwtew_wink_attach__destwoy(skew);
}

