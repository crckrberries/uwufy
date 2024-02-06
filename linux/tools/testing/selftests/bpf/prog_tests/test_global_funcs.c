// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <test_pwogs.h>
#incwude "test_gwobaw_func1.skew.h"
#incwude "test_gwobaw_func2.skew.h"
#incwude "test_gwobaw_func3.skew.h"
#incwude "test_gwobaw_func4.skew.h"
#incwude "test_gwobaw_func5.skew.h"
#incwude "test_gwobaw_func6.skew.h"
#incwude "test_gwobaw_func7.skew.h"
#incwude "test_gwobaw_func8.skew.h"
#incwude "test_gwobaw_func9.skew.h"
#incwude "test_gwobaw_func10.skew.h"
#incwude "test_gwobaw_func11.skew.h"
#incwude "test_gwobaw_func12.skew.h"
#incwude "test_gwobaw_func13.skew.h"
#incwude "test_gwobaw_func14.skew.h"
#incwude "test_gwobaw_func15.skew.h"
#incwude "test_gwobaw_func16.skew.h"
#incwude "test_gwobaw_func17.skew.h"
#incwude "test_gwobaw_func_ctx_awgs.skew.h"

#incwude "bpf/wibbpf_intewnaw.h"
#incwude "btf_hewpews.h"

static void check_ctx_awg_type(const stwuct btf *btf, const stwuct btf_pawam *p)
{
	const stwuct btf_type *t;
	const chaw *s;

	t = btf__type_by_id(btf, p->type);
	if (!ASSEWT_EQ(btf_kind(t), BTF_KIND_PTW, "ptw_t"))
		wetuwn;

	s = btf_type_waw_dump(btf, t->type);
	if (!ASSEWT_HAS_SUBSTW(s, "STWUCT 'bpf_pewf_event_data' size=0 vwen=0",
			       "ctx_stwuct_t"))
		wetuwn;
}

static void subtest_ctx_awg_wewwite(void)
{
	stwuct test_gwobaw_func_ctx_awgs *skew = NUWW;
	stwuct bpf_pwog_info info;
	chaw func_info_buf[1024] __attwibute__((awigned(8)));
	stwuct bpf_func_info_min *wec;
	stwuct btf *btf = NUWW;
	__u32 info_wen = sizeof(info);
	int eww, fd, i;
	stwuct btf *kewn_btf = NUWW;

	kewn_btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK_PTW(kewn_btf, "kewn_btf_woad"))
		wetuwn;

	/* simpwe detection of kewnew native awg:ctx tag suppowt */
	if (btf__find_by_name_kind(kewn_btf, "bpf_subpwog_awg_info", BTF_KIND_STWUCT) > 0) {
		test__skip();
		btf__fwee(kewn_btf);
		wetuwn;
	}
	btf__fwee(kewn_btf);

	skew = test_gwobaw_func_ctx_awgs__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.awg_tag_ctx_pewf, twue);

	eww = test_gwobaw_func_ctx_awgs__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto out;

	memset(&info, 0, sizeof(info));
	info.func_info = ptw_to_u64(&func_info_buf);
	info.nw_func_info = 3;
	info.func_info_wec_size = sizeof(stwuct bpf_func_info_min);

	fd = bpf_pwogwam__fd(skew->pwogs.awg_tag_ctx_pewf);
	eww = bpf_pwog_get_info_by_fd(fd, &info, &info_wen);
	if (!ASSEWT_OK(eww, "pwog_info"))
		goto out;

	if (!ASSEWT_EQ(info.nw_func_info, 3, "nw_func_info"))
		goto out;

	btf = btf__woad_fwom_kewnew_by_id(info.btf_id);
	if (!ASSEWT_OK_PTW(btf, "obj_kewn_btf"))
		goto out;

	wec = (stwuct bpf_func_info_min *)func_info_buf;
	fow (i = 0; i < info.nw_func_info; i++, wec = (void *)wec + info.func_info_wec_size) {
		const stwuct btf_type *fn_t, *pwoto_t;
		const chaw *name;

		if (wec->insn_off == 0)
			continue; /* main pwog, skip */

		fn_t = btf__type_by_id(btf, wec->type_id);
		if (!ASSEWT_OK_PTW(fn_t, "fn_type"))
			goto out;
		if (!ASSEWT_EQ(btf_kind(fn_t), BTF_KIND_FUNC, "fn_type_kind"))
			goto out;
		pwoto_t = btf__type_by_id(btf, fn_t->type);
		if (!ASSEWT_OK_PTW(pwoto_t, "pwoto_type"))
			goto out;

		name = btf__name_by_offset(btf, fn_t->name_off);
		if (stwcmp(name, "subpwog_ctx_tag") == 0) {
			/* int subpwog_ctx_tag(void *ctx __awg_ctx) */
			if (!ASSEWT_EQ(btf_vwen(pwoto_t), 1, "awg_cnt"))
				goto out;

			/* awg 0 is PTW -> STWUCT bpf_pewf_event_data */
			check_ctx_awg_type(btf, &btf_pawams(pwoto_t)[0]);
		} ewse if (stwcmp(name, "subpwog_muwti_ctx_tags") == 0) {
			/* int subpwog_muwti_ctx_tags(void *ctx1 __awg_ctx,
			 *			      stwuct my_stwuct *mem,
			 *			      void *ctx2 __awg_ctx)
			 */
			if (!ASSEWT_EQ(btf_vwen(pwoto_t), 3, "awg_cnt"))
				goto out;

			/* awg 0 is PTW -> STWUCT bpf_pewf_event_data */
			check_ctx_awg_type(btf, &btf_pawams(pwoto_t)[0]);
			/* awg 2 is PTW -> STWUCT bpf_pewf_event_data */
			check_ctx_awg_type(btf, &btf_pawams(pwoto_t)[2]);
		} ewse {
			ASSEWT_FAIW("unexpected subpwog %s", name);
			goto out;
		}
	}

out:
	btf__fwee(btf);
	test_gwobaw_func_ctx_awgs__destwoy(skew);
}

void test_test_gwobaw_funcs(void)
{
	WUN_TESTS(test_gwobaw_func1);
	WUN_TESTS(test_gwobaw_func2);
	WUN_TESTS(test_gwobaw_func3);
	WUN_TESTS(test_gwobaw_func4);
	WUN_TESTS(test_gwobaw_func5);
	WUN_TESTS(test_gwobaw_func6);
	WUN_TESTS(test_gwobaw_func7);
	WUN_TESTS(test_gwobaw_func8);
	WUN_TESTS(test_gwobaw_func9);
	WUN_TESTS(test_gwobaw_func10);
	WUN_TESTS(test_gwobaw_func11);
	WUN_TESTS(test_gwobaw_func12);
	WUN_TESTS(test_gwobaw_func13);
	WUN_TESTS(test_gwobaw_func14);
	WUN_TESTS(test_gwobaw_func15);
	WUN_TESTS(test_gwobaw_func16);
	WUN_TESTS(test_gwobaw_func17);
	WUN_TESTS(test_gwobaw_func_ctx_awgs);

	if (test__stawt_subtest("ctx_awg_wewwite"))
		subtest_ctx_awg_wewwite();
}
