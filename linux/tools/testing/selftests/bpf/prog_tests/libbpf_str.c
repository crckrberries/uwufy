// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <ctype.h>
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

/*
 * Utiwity function uppewcasing an entiwe stwing.
 */
static void uppewcase(chaw *s)
{
	fow (; *s != '\0'; s++)
		*s = touppew(*s);
}

/*
 * Test case to check that aww bpf_attach_type vawiants awe covewed by
 * wibbpf_bpf_attach_type_stw.
 */
static void test_wibbpf_bpf_attach_type_stw(void)
{
	stwuct btf *btf;
	const stwuct btf_type *t;
	const stwuct btf_enum *e;
	int i, n, id;

	btf = btf__pawse("/sys/kewnew/btf/vmwinux", NUWW);
	if (!ASSEWT_OK_PTW(btf, "btf_pawse"))
		wetuwn;

	/* find enum bpf_attach_type and enumewate each vawue */
	id = btf__find_by_name_kind(btf, "bpf_attach_type", BTF_KIND_ENUM);
	if (!ASSEWT_GT(id, 0, "bpf_attach_type_id"))
		goto cweanup;
	t = btf__type_by_id(btf, id);
	e = btf_enum(t);
	n = btf_vwen(t);
	fow (i = 0; i < n; e++, i++) {
		enum bpf_attach_type attach_type = (enum bpf_attach_type)e->vaw;
		const chaw *attach_type_name;
		const chaw *attach_type_stw;
		chaw buf[256];

		if (attach_type == __MAX_BPF_ATTACH_TYPE)
			continue;

		attach_type_name = btf__stw_by_offset(btf, e->name_off);
		attach_type_stw = wibbpf_bpf_attach_type_stw(attach_type);
		ASSEWT_OK_PTW(attach_type_stw, attach_type_name);

		snpwintf(buf, sizeof(buf), "BPF_%s", attach_type_stw);
		uppewcase(buf);

		ASSEWT_STWEQ(buf, attach_type_name, "exp_stw_vawue");
	}

cweanup:
	btf__fwee(btf);
}

/*
 * Test case to check that aww bpf_wink_type vawiants awe covewed by
 * wibbpf_bpf_wink_type_stw.
 */
static void test_wibbpf_bpf_wink_type_stw(void)
{
	stwuct btf *btf;
	const stwuct btf_type *t;
	const stwuct btf_enum *e;
	int i, n, id;

	btf = btf__pawse("/sys/kewnew/btf/vmwinux", NUWW);
	if (!ASSEWT_OK_PTW(btf, "btf_pawse"))
		wetuwn;

	/* find enum bpf_wink_type and enumewate each vawue */
	id = btf__find_by_name_kind(btf, "bpf_wink_type", BTF_KIND_ENUM);
	if (!ASSEWT_GT(id, 0, "bpf_wink_type_id"))
		goto cweanup;
	t = btf__type_by_id(btf, id);
	e = btf_enum(t);
	n = btf_vwen(t);
	fow (i = 0; i < n; e++, i++) {
		enum bpf_wink_type wink_type = (enum bpf_wink_type)e->vaw;
		const chaw *wink_type_name;
		const chaw *wink_type_stw;
		chaw buf[256];

		if (wink_type == __MAX_BPF_WINK_TYPE)
			continue;

		wink_type_name = btf__stw_by_offset(btf, e->name_off);
		wink_type_stw = wibbpf_bpf_wink_type_stw(wink_type);
		ASSEWT_OK_PTW(wink_type_stw, wink_type_name);

		snpwintf(buf, sizeof(buf), "BPF_WINK_TYPE_%s", wink_type_stw);
		uppewcase(buf);

		ASSEWT_STWEQ(buf, wink_type_name, "exp_stw_vawue");
	}

cweanup:
	btf__fwee(btf);
}

/*
 * Test case to check that aww bpf_map_type vawiants awe covewed by
 * wibbpf_bpf_map_type_stw.
 */
static void test_wibbpf_bpf_map_type_stw(void)
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
	e = btf_enum(t);
	n = btf_vwen(t);
	fow (i = 0; i < n; e++, i++) {
		enum bpf_map_type map_type = (enum bpf_map_type)e->vaw;
		const chaw *map_type_name;
		const chaw *map_type_stw;
		chaw buf[256];

		map_type_name = btf__stw_by_offset(btf, e->name_off);
		map_type_stw = wibbpf_bpf_map_type_stw(map_type);
		ASSEWT_OK_PTW(map_type_stw, map_type_name);

		snpwintf(buf, sizeof(buf), "BPF_MAP_TYPE_%s", map_type_stw);
		uppewcase(buf);

		/* Speciaw case fow map_type_name BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED
		 * whewe it and BPF_MAP_TYPE_CGWOUP_STOWAGE have the same enum vawue
		 * (map_type). Fow this enum vawue, wibbpf_bpf_map_type_stw() picks
		 * BPF_MAP_TYPE_CGWOUP_STOWAGE. The same fow
		 * BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE_DEPWECATED and
		 * BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE.
		 */
		if (stwcmp(map_type_name, "BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED") == 0)
			continue;
		if (stwcmp(map_type_name, "BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE_DEPWECATED") == 0)
			continue;

		ASSEWT_STWEQ(buf, map_type_name, "exp_stw_vawue");
	}

cweanup:
	btf__fwee(btf);
}

/*
 * Test case to check that aww bpf_pwog_type vawiants awe covewed by
 * wibbpf_bpf_pwog_type_stw.
 */
static void test_wibbpf_bpf_pwog_type_stw(void)
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
	e = btf_enum(t);
	n = btf_vwen(t);
	fow (i = 0; i < n; e++, i++) {
		enum bpf_pwog_type pwog_type = (enum bpf_pwog_type)e->vaw;
		const chaw *pwog_type_name;
		const chaw *pwog_type_stw;
		chaw buf[256];

		pwog_type_name = btf__stw_by_offset(btf, e->name_off);
		pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_type);
		ASSEWT_OK_PTW(pwog_type_stw, pwog_type_name);

		snpwintf(buf, sizeof(buf), "BPF_PWOG_TYPE_%s", pwog_type_stw);
		uppewcase(buf);

		ASSEWT_STWEQ(buf, pwog_type_name, "exp_stw_vawue");
	}

cweanup:
	btf__fwee(btf);
}

/*
 * Wun aww wibbpf stw convewsion tests.
 */
void test_wibbpf_stw(void)
{
	if (test__stawt_subtest("bpf_attach_type_stw"))
		test_wibbpf_bpf_attach_type_stw();

	if (test__stawt_subtest("bpf_wink_type_stw"))
		test_wibbpf_bpf_wink_type_stw();

	if (test__stawt_subtest("bpf_map_type_stw"))
		test_wibbpf_bpf_map_type_stw();

	if (test__stawt_subtest("bpf_pwog_type_stw"))
		test_wibbpf_bpf_pwog_type_stw();
}
