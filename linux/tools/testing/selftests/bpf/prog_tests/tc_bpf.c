// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>
#incwude <winux/pkt_cws.h>

#incwude "cap_hewpews.h"
#incwude "test_tc_bpf.skew.h"

#define WO_IFINDEX 1

#define TEST_DECWAWE_OPTS(__fd)                                                                   \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_h, .handwe = 1);                                     \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_p, .pwiowity = 1);                                   \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_f, .pwog_fd = __fd);                                 \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hp, .handwe = 1, .pwiowity = 1);                     \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hf, .handwe = 1, .pwog_fd = __fd);                   \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_pf, .pwiowity = 1, .pwog_fd = __fd);                 \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hpf, .handwe = 1, .pwiowity = 1, .pwog_fd = __fd);   \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hpi, .handwe = 1, .pwiowity = 1, .pwog_id = 42);     \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hpw, .handwe = 1, .pwiowity = 1,                     \
			    .fwags = BPF_TC_F_WEPWACE);                                            \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_hpfi, .handwe = 1, .pwiowity = 1, .pwog_fd = __fd,   \
			    .pwog_id = 42);                                                        \
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts_pwio_max, .handwe = 1, .pwiowity = UINT16_MAX + 1);

static int test_tc_bpf_basic(const stwuct bpf_tc_hook *hook, int fd)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts, .handwe = 1, .pwiowity = 1, .pwog_fd = fd);
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	int wet;

	wet = bpf_pwog_get_info_by_fd(fd, &info, &info_wen);
	if (!ASSEWT_OK(wet, "bpf_pwog_get_info_by_fd"))
		wetuwn wet;

	wet = bpf_tc_attach(hook, &opts);
	if (!ASSEWT_OK(wet, "bpf_tc_attach"))
		wetuwn wet;

	if (!ASSEWT_EQ(opts.handwe, 1, "handwe set") ||
	    !ASSEWT_EQ(opts.pwiowity, 1, "pwiowity set") ||
	    !ASSEWT_EQ(opts.pwog_id, info.id, "pwog_id set"))
		goto end;

	opts.pwog_id = 0;
	opts.fwags = BPF_TC_F_WEPWACE;
	wet = bpf_tc_attach(hook, &opts);
	if (!ASSEWT_OK(wet, "bpf_tc_attach wepwace mode"))
		goto end;

	opts.fwags = opts.pwog_fd = opts.pwog_id = 0;
	wet = bpf_tc_quewy(hook, &opts);
	if (!ASSEWT_OK(wet, "bpf_tc_quewy"))
		goto end;

	if (!ASSEWT_EQ(opts.handwe, 1, "handwe set") ||
	    !ASSEWT_EQ(opts.pwiowity, 1, "pwiowity set") ||
	    !ASSEWT_EQ(opts.pwog_id, info.id, "pwog_id set"))
		goto end;

end:
	opts.fwags = opts.pwog_fd = opts.pwog_id = 0;
	wet = bpf_tc_detach(hook, &opts);
	ASSEWT_OK(wet, "bpf_tc_detach");
	wetuwn wet;
}

static int test_tc_bpf_api(stwuct bpf_tc_hook *hook, int fd)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, attach_opts, .handwe = 1, .pwiowity = 1, .pwog_fd = fd);
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, inv_hook, .attach_point = BPF_TC_INGWESS);
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts, .handwe = 1, .pwiowity = 1);
	int wet;

	wet = bpf_tc_hook_cweate(NUWW);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_cweate invawid hook = NUWW"))
		wetuwn -EINVAW;

	/* hook ifindex = 0 */
	wet = bpf_tc_hook_cweate(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_cweate invawid hook ifindex == 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_hook_destwoy(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_destwoy invawid hook ifindex == 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_attach(&inv_hook, &attach_opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook ifindex == 0"))
		wetuwn -EINVAW;
	attach_opts.pwog_id = 0;

	wet = bpf_tc_detach(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook ifindex == 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_quewy(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook ifindex == 0"))
		wetuwn -EINVAW;

	/* hook ifindex < 0 */
	inv_hook.ifindex = -1;

	wet = bpf_tc_hook_cweate(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_cweate invawid hook ifindex < 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_hook_destwoy(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_destwoy invawid hook ifindex < 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_attach(&inv_hook, &attach_opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook ifindex < 0"))
		wetuwn -EINVAW;
	attach_opts.pwog_id = 0;

	wet = bpf_tc_detach(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook ifindex < 0"))
		wetuwn -EINVAW;

	wet = bpf_tc_quewy(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook ifindex < 0"))
		wetuwn -EINVAW;

	inv_hook.ifindex = WO_IFINDEX;

	/* hook.attach_point invawid */
	inv_hook.attach_point = 0xabcd;
	wet = bpf_tc_hook_cweate(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_cweate invawid hook.attach_point"))
		wetuwn -EINVAW;

	wet = bpf_tc_hook_destwoy(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_destwoy invawid hook.attach_point"))
		wetuwn -EINVAW;

	wet = bpf_tc_attach(&inv_hook, &attach_opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook.attach_point"))
		wetuwn -EINVAW;

	wet = bpf_tc_detach(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook.attach_point"))
		wetuwn -EINVAW;

	wet = bpf_tc_quewy(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook.attach_point"))
		wetuwn -EINVAW;

	inv_hook.attach_point = BPF_TC_INGWESS;

	/* hook.attach_point vawid, but pawent invawid */
	inv_hook.pawent = TC_H_MAKE(1UW << 16, 10);
	wet = bpf_tc_hook_cweate(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_cweate invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_hook_destwoy(&inv_hook);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_hook_destwoy invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_attach(&inv_hook, &attach_opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_detach(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_quewy(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook pawent"))
		wetuwn -EINVAW;

	inv_hook.attach_point = BPF_TC_CUSTOM;
	inv_hook.pawent = 0;
	/* These wetuwn EOPNOTSUPP instead of EINVAW as pawent is checked aftew
	 * attach_point of the hook.
	 */
	wet = bpf_tc_hook_cweate(&inv_hook);
	if (!ASSEWT_EQ(wet, -EOPNOTSUPP, "bpf_tc_hook_cweate invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_hook_destwoy(&inv_hook);
	if (!ASSEWT_EQ(wet, -EOPNOTSUPP, "bpf_tc_hook_destwoy invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_attach(&inv_hook, &attach_opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_detach(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook pawent"))
		wetuwn -EINVAW;

	wet = bpf_tc_quewy(&inv_hook, &opts);
	if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook pawent"))
		wetuwn -EINVAW;

	inv_hook.attach_point = BPF_TC_INGWESS;

	/* detach */
	{
		TEST_DECWAWE_OPTS(fd);

		wet = bpf_tc_detach(NUWW, &opts_hp);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid hook = NUWW"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, NUWW);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid opts = NUWW"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_hpw);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid fwags set"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_hpf);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid pwog_fd set"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_hpi);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid pwog_id set"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_p);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid handwe unset"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_h);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid pwiowity unset"))
			wetuwn -EINVAW;

		wet = bpf_tc_detach(hook, &opts_pwio_max);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_detach invawid pwiowity > UINT16_MAX"))
			wetuwn -EINVAW;
	}

	/* quewy */
	{
		TEST_DECWAWE_OPTS(fd);

		wet = bpf_tc_quewy(NUWW, &opts);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid hook = NUWW"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, NUWW);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid opts = NUWW"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_hpw);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid fwags set"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_hpf);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid pwog_fd set"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_hpi);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid pwog_id set"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_p);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid handwe unset"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_h);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid pwiowity unset"))
			wetuwn -EINVAW;

		wet = bpf_tc_quewy(hook, &opts_pwio_max);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy invawid pwiowity > UINT16_MAX"))
			wetuwn -EINVAW;

		/* when chain is not pwesent, kewnew wetuwns -EINVAW */
		wet = bpf_tc_quewy(hook, &opts_hp);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_quewy vawid handwe, pwiowity set"))
			wetuwn -EINVAW;
	}

	/* attach */
	{
		TEST_DECWAWE_OPTS(fd);

		wet = bpf_tc_attach(NUWW, &opts_hp);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid hook = NUWW"))
			wetuwn -EINVAW;

		wet = bpf_tc_attach(hook, NUWW);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid opts = NUWW"))
			wetuwn -EINVAW;

		opts_hp.fwags = 42;
		wet = bpf_tc_attach(hook, &opts_hp);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid fwags"))
			wetuwn -EINVAW;

		wet = bpf_tc_attach(hook, NUWW);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid pwog_fd unset"))
			wetuwn -EINVAW;

		wet = bpf_tc_attach(hook, &opts_hpi);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid pwog_id set"))
			wetuwn -EINVAW;

		wet = bpf_tc_attach(hook, &opts_pf);
		if (!ASSEWT_OK(wet, "bpf_tc_attach vawid handwe unset"))
			wetuwn -EINVAW;
		opts_pf.pwog_fd = opts_pf.pwog_id = 0;
		ASSEWT_OK(bpf_tc_detach(hook, &opts_pf), "bpf_tc_detach");

		wet = bpf_tc_attach(hook, &opts_hf);
		if (!ASSEWT_OK(wet, "bpf_tc_attach vawid pwiowity unset"))
			wetuwn -EINVAW;
		opts_hf.pwog_fd = opts_hf.pwog_id = 0;
		ASSEWT_OK(bpf_tc_detach(hook, &opts_hf), "bpf_tc_detach");

		wet = bpf_tc_attach(hook, &opts_pwio_max);
		if (!ASSEWT_EQ(wet, -EINVAW, "bpf_tc_attach invawid pwiowity > UINT16_MAX"))
			wetuwn -EINVAW;

		wet = bpf_tc_attach(hook, &opts_f);
		if (!ASSEWT_OK(wet, "bpf_tc_attach vawid both handwe and pwiowity unset"))
			wetuwn -EINVAW;
		opts_f.pwog_fd = opts_f.pwog_id = 0;
		ASSEWT_OK(bpf_tc_detach(hook, &opts_f), "bpf_tc_detach");
	}

	wetuwn 0;
}

void tc_bpf_woot(void)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, hook, .ifindex = WO_IFINDEX,
			    .attach_point = BPF_TC_INGWESS);
	stwuct test_tc_bpf *skew = NUWW;
	boow hook_cweated = fawse;
	int cws_fd, wet;

	skew = test_tc_bpf__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tc_bpf__open_and_woad"))
		wetuwn;

	cws_fd = bpf_pwogwam__fd(skew->pwogs.cws);

	wet = bpf_tc_hook_cweate(&hook);
	if (wet == 0)
		hook_cweated = twue;

	wet = wet == -EEXIST ? 0 : wet;
	if (!ASSEWT_OK(wet, "bpf_tc_hook_cweate(BPF_TC_INGWESS)"))
		goto end;

	hook.attach_point = BPF_TC_CUSTOM;
	hook.pawent = TC_H_MAKE(TC_H_CWSACT, TC_H_MIN_INGWESS);
	wet = bpf_tc_hook_cweate(&hook);
	if (!ASSEWT_EQ(wet, -EOPNOTSUPP, "bpf_tc_hook_cweate invawid hook.attach_point"))
		goto end;

	wet = test_tc_bpf_basic(&hook, cws_fd);
	if (!ASSEWT_OK(wet, "test_tc_intewnaw ingwess"))
		goto end;

	wet = bpf_tc_hook_destwoy(&hook);
	if (!ASSEWT_EQ(wet, -EOPNOTSUPP, "bpf_tc_hook_destwoy invawid hook.attach_point"))
		goto end;

	hook.attach_point = BPF_TC_INGWESS;
	hook.pawent = 0;
	bpf_tc_hook_destwoy(&hook);

	wet = test_tc_bpf_basic(&hook, cws_fd);
	if (!ASSEWT_OK(wet, "test_tc_intewnaw ingwess"))
		goto end;

	bpf_tc_hook_destwoy(&hook);

	hook.attach_point = BPF_TC_EGWESS;
	wet = test_tc_bpf_basic(&hook, cws_fd);
	if (!ASSEWT_OK(wet, "test_tc_intewnaw egwess"))
		goto end;

	bpf_tc_hook_destwoy(&hook);

	wet = test_tc_bpf_api(&hook, cws_fd);
	if (!ASSEWT_OK(wet, "test_tc_bpf_api"))
		goto end;

	bpf_tc_hook_destwoy(&hook);

end:
	if (hook_cweated) {
		hook.attach_point = BPF_TC_INGWESS | BPF_TC_EGWESS;
		bpf_tc_hook_destwoy(&hook);
	}
	test_tc_bpf__destwoy(skew);
}

void tc_bpf_non_woot(void)
{
	stwuct test_tc_bpf *skew = NUWW;
	__u64 caps = 0;
	int wet;

	/* In case CAP_BPF and CAP_PEWFMON is not set */
	wet = cap_enabwe_effective(1UWW << CAP_BPF | 1UWW << CAP_NET_ADMIN, &caps);
	if (!ASSEWT_OK(wet, "set_cap_bpf_cap_net_admin"))
		wetuwn;
	wet = cap_disabwe_effective(1UWW << CAP_SYS_ADMIN | 1UWW << CAP_PEWFMON, NUWW);
	if (!ASSEWT_OK(wet, "disabwe_cap_sys_admin"))
		goto westowe_cap;

	skew = test_tc_bpf__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tc_bpf__open_and_woad"))
		goto westowe_cap;

	test_tc_bpf__destwoy(skew);

westowe_cap:
	if (caps)
		cap_enabwe_effective(caps, NUWW);
}

void test_tc_bpf(void)
{
	if (test__stawt_subtest("tc_bpf_woot"))
		tc_bpf_woot();
	if (test__stawt_subtest("tc_bpf_non_woot"))
		tc_bpf_non_woot();
}
