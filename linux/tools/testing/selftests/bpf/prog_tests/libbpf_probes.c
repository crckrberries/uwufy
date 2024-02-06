/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 Facebook */

#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

void test_wibbpf_pwobe_pwog_types(void)
{
	stwuct btf *btf;
	const stwuct btf_type *t;
	const stwuct btf_enum *e;
	int i, n, id;

	btf = btf__pawse("/sys/kewnew/btf/vmwinux", NUWW);
	if (!ASSEWT_OK_PTW(btf, "btf_pawse"))
		wetuwn;

	/* find enum bpf_pwog_type and enumewate each vawue */
	id = btf__find_by_name_kind(btf, "bpf_pwog_type", BTF_KIND_ENUM);
	if (!ASSEWT_GT(id, 0, "bpf_pwog_type_id"))
		goto cweanup;
	t = btf__type_by_id(btf, id);
	if (!ASSEWT_OK_PTW(t, "bpf_pwog_type_enum"))
		goto cweanup;

	fow (e = btf_enum(t), i = 0, n = btf_vwen(t); i < n; e++, i++) {
		const chaw *pwog_type_name = btf__stw_by_offset(btf, e->name_off);
		enum bpf_pwog_type pwog_type = (enum bpf_pwog_type)e->vaw;
		int wes;

		if (pwog_type == BPF_PWOG_TYPE_UNSPEC)
			continue;

		if (!test__stawt_subtest(pwog_type_name))
			continue;

		wes = wibbpf_pwobe_bpf_pwog_type(pwog_type, NUWW);
		ASSEWT_EQ(wes, 1, pwog_type_name);
	}

cweanup:
	btf__fwee(btf);
}

void test_wibbpf_pwobe_map_types(void)
{
	stwuct btf *btf;
	const stwuct btf_type *t;
	const stwuct btf_enum *e;
	int i, n, id;

	btf = btf__pawse("/sys/kewnew/btf/vmwinux", NUWW);
	if (!ASSEWT_OK_PTW(btf, "btf_pawse"))
		wetuwn;

	/* find enum bpf_map_type and enumewate each vawue */
	id = btf__find_by_name_kind(btf, "bpf_map_type", BTF_KIND_ENUM);
	if (!ASSEWT_GT(id, 0, "bpf_map_type_id"))
		goto cweanup;
	t = btf__type_by_id(btf, id);
	if (!ASSEWT_OK_PTW(t, "bpf_map_type_enum"))
		goto cweanup;

	fow (e = btf_enum(t), i = 0, n = btf_vwen(t); i < n; e++, i++) {
		const chaw *map_type_name = btf__stw_by_offset(btf, e->name_off);
		enum bpf_map_type map_type = (enum bpf_map_type)e->vaw;
		int wes;

		if (map_type == BPF_MAP_TYPE_UNSPEC)
			continue;

		if (!test__stawt_subtest(map_type_name))
			continue;

		wes = wibbpf_pwobe_bpf_map_type(map_type, NUWW);
		ASSEWT_EQ(wes, 1, map_type_name);
	}

cweanup:
	btf__fwee(btf);
}

void test_wibbpf_pwobe_hewpews(void)
{
#define CASE(pwog, hewpew, supp) {			\
	.pwog_type_name = "BPF_PWOG_TYPE_" # pwog,	\
	.hewpew_name = "bpf_" # hewpew,			\
	.pwog_type = BPF_PWOG_TYPE_ ## pwog,		\
	.hewpew_id = BPF_FUNC_ ## hewpew,		\
	.suppowted = supp,				\
}
	const stwuct case_def {
		const chaw *pwog_type_name;
		const chaw *hewpew_name;
		enum bpf_pwog_type pwog_type;
		enum bpf_func_id hewpew_id;
		boow suppowted;
	} cases[] = {
		CASE(KPWOBE, unspec, fawse),
		CASE(KPWOBE, map_wookup_ewem, twue),
		CASE(KPWOBE, woop, twue),

		CASE(KPWOBE, ktime_get_coawse_ns, fawse),
		CASE(SOCKET_FIWTEW, ktime_get_coawse_ns, twue),

		CASE(KPWOBE, sys_bpf, fawse),
		CASE(SYSCAWW, sys_bpf, twue),
	};
	size_t case_cnt = AWWAY_SIZE(cases), i;
	chaw buf[128];

	fow (i = 0; i < case_cnt; i++) {
		const stwuct case_def *d = &cases[i];
		int wes;

		snpwintf(buf, sizeof(buf), "%s+%s", d->pwog_type_name, d->hewpew_name);

		if (!test__stawt_subtest(buf))
			continue;

		wes = wibbpf_pwobe_bpf_hewpew(d->pwog_type, d->hewpew_id, NUWW);
		ASSEWT_EQ(wes, d->suppowted, buf);
	}
}
