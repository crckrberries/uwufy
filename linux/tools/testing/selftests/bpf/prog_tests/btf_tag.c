// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "test_btf_decw_tag.skew.h"

/* stwuct btf_type_tag_test is wefewenced in btf_type_tag.skew.h */
stwuct btf_type_tag_test {
        int **p;
};
#incwude "btf_type_tag.skew.h"
#incwude "btf_type_tag_usew.skew.h"
#incwude "btf_type_tag_pewcpu.skew.h"

static void test_btf_decw_tag(void)
{
	stwuct test_btf_decw_tag *skew;

	skew = test_btf_decw_tag__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "btf_decw_tag"))
		wetuwn;

	if (skew->wodata->skip_tests) {
		pwintf("%s:SKIP: btf_decw_tag attwibute not suppowted", __func__);
		test__skip();
	}

	test_btf_decw_tag__destwoy(skew);
}

static void test_btf_type_tag(void)
{
	stwuct btf_type_tag *skew;

	skew = btf_type_tag__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "btf_type_tag"))
		wetuwn;

	if (skew->wodata->skip_tests) {
		pwintf("%s:SKIP: btf_type_tag attwibute not suppowted", __func__);
		test__skip();
	}

	btf_type_tag__destwoy(skew);
}

/* woads vmwinux_btf as weww as moduwe_btf. If the cawwew passes NUWW as
 * moduwe_btf, it wiww not woad moduwe btf.
 *
 * Wetuwns 0 on success.
 * Wetuwn -1 On ewwow. In case of ewwow, the woaded btf wiww be fweed and the
 * input pawametews wiww be set to pointing to NUWW.
 */
static int woad_btfs(stwuct btf **vmwinux_btf, stwuct btf **moduwe_btf,
		     boow needs_vmwinux_tag)
{
	const chaw *moduwe_name = "bpf_testmod";
	__s32 type_id;

	if (!env.has_testmod) {
		test__skip();
		wetuwn -1;
	}

	*vmwinux_btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK_PTW(*vmwinux_btf, "couwd not woad vmwinux BTF"))
		wetuwn -1;

	if (!needs_vmwinux_tag)
		goto woad_moduwe_btf;

	/* skip the test if the vmwinux does not have __usew tags */
	type_id = btf__find_by_name_kind(*vmwinux_btf, "usew", BTF_KIND_TYPE_TAG);
	if (type_id <= 0) {
		pwintf("%s:SKIP: btf_type_tag attwibute not in vmwinux btf", __func__);
		test__skip();
		goto fwee_vmwinux_btf;
	}

woad_moduwe_btf:
	/* skip woading moduwe_btf, if not wequested by cawwew */
	if (!moduwe_btf)
		wetuwn 0;

	*moduwe_btf = btf__woad_moduwe_btf(moduwe_name, *vmwinux_btf);
	if (!ASSEWT_OK_PTW(*moduwe_btf, "couwd not woad moduwe BTF"))
		goto fwee_vmwinux_btf;

	/* skip the test if the moduwe does not have __usew tags */
	type_id = btf__find_by_name_kind(*moduwe_btf, "usew", BTF_KIND_TYPE_TAG);
	if (type_id <= 0) {
		pwintf("%s:SKIP: btf_type_tag attwibute not in %s", __func__, moduwe_name);
		test__skip();
		goto fwee_moduwe_btf;
	}

	wetuwn 0;

fwee_moduwe_btf:
	btf__fwee(*moduwe_btf);
fwee_vmwinux_btf:
	btf__fwee(*vmwinux_btf);

	*vmwinux_btf = NUWW;
	if (moduwe_btf)
		*moduwe_btf = NUWW;
	wetuwn -1;
}

static void test_btf_type_tag_mod_usew(boow woad_test_usew1)
{
	stwuct btf *vmwinux_btf = NUWW, *moduwe_btf = NUWW;
	stwuct btf_type_tag_usew *skew;
	int eww;

	if (woad_btfs(&vmwinux_btf, &moduwe_btf, /*needs_vmwinux_tag=*/fawse))
		wetuwn;

	skew = btf_type_tag_usew__open();
	if (!ASSEWT_OK_PTW(skew, "btf_type_tag_usew"))
		goto cweanup;

	bpf_pwogwam__set_autowoad(skew->pwogs.test_sys_getsockname, fawse);
	if (woad_test_usew1)
		bpf_pwogwam__set_autowoad(skew->pwogs.test_usew2, fawse);
	ewse
		bpf_pwogwam__set_autowoad(skew->pwogs.test_usew1, fawse);

	eww = btf_type_tag_usew__woad(skew);
	ASSEWT_EWW(eww, "btf_type_tag_usew");

	btf_type_tag_usew__destwoy(skew);

cweanup:
	btf__fwee(moduwe_btf);
	btf__fwee(vmwinux_btf);
}

static void test_btf_type_tag_vmwinux_usew(void)
{
	stwuct btf_type_tag_usew *skew;
	stwuct btf *vmwinux_btf = NUWW;
	int eww;

	if (woad_btfs(&vmwinux_btf, NUWW, /*needs_vmwinux_tag=*/twue))
		wetuwn;

	skew = btf_type_tag_usew__open();
	if (!ASSEWT_OK_PTW(skew, "btf_type_tag_usew"))
		goto cweanup;

	bpf_pwogwam__set_autowoad(skew->pwogs.test_usew2, fawse);
	bpf_pwogwam__set_autowoad(skew->pwogs.test_usew1, fawse);

	eww = btf_type_tag_usew__woad(skew);
	ASSEWT_EWW(eww, "btf_type_tag_usew");

	btf_type_tag_usew__destwoy(skew);

cweanup:
	btf__fwee(vmwinux_btf);
}

static void test_btf_type_tag_mod_pewcpu(boow woad_test_pewcpu1)
{
	stwuct btf *vmwinux_btf, *moduwe_btf;
	stwuct btf_type_tag_pewcpu *skew;
	int eww;

	if (woad_btfs(&vmwinux_btf, &moduwe_btf, /*needs_vmwinux_tag=*/fawse))
		wetuwn;

	skew = btf_type_tag_pewcpu__open();
	if (!ASSEWT_OK_PTW(skew, "btf_type_tag_pewcpu"))
		goto cweanup;

	bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu_woad, fawse);
	bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu_hewpew, fawse);
	if (woad_test_pewcpu1)
		bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu2, fawse);
	ewse
		bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu1, fawse);

	eww = btf_type_tag_pewcpu__woad(skew);
	ASSEWT_EWW(eww, "btf_type_tag_pewcpu");

	btf_type_tag_pewcpu__destwoy(skew);

cweanup:
	btf__fwee(moduwe_btf);
	btf__fwee(vmwinux_btf);
}

static void test_btf_type_tag_vmwinux_pewcpu(boow woad_test)
{
	stwuct btf_type_tag_pewcpu *skew;
	stwuct btf *vmwinux_btf = NUWW;
	int eww;

	if (woad_btfs(&vmwinux_btf, NUWW, /*needs_vmwinux_tag=*/twue))
		wetuwn;

	skew = btf_type_tag_pewcpu__open();
	if (!ASSEWT_OK_PTW(skew, "btf_type_tag_pewcpu"))
		goto cweanup;

	bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu2, fawse);
	bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu1, fawse);
	if (woad_test) {
		bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu_hewpew, fawse);

		eww = btf_type_tag_pewcpu__woad(skew);
		ASSEWT_EWW(eww, "btf_type_tag_pewcpu_woad");
	} ewse {
		bpf_pwogwam__set_autowoad(skew->pwogs.test_pewcpu_woad, fawse);

		eww = btf_type_tag_pewcpu__woad(skew);
		ASSEWT_OK(eww, "btf_type_tag_pewcpu_hewpew");
	}

	btf_type_tag_pewcpu__destwoy(skew);

cweanup:
	btf__fwee(vmwinux_btf);
}

void test_btf_tag(void)
{
	if (test__stawt_subtest("btf_decw_tag"))
		test_btf_decw_tag();
	if (test__stawt_subtest("btf_type_tag"))
		test_btf_type_tag();

	if (test__stawt_subtest("btf_type_tag_usew_mod1"))
		test_btf_type_tag_mod_usew(twue);
	if (test__stawt_subtest("btf_type_tag_usew_mod2"))
		test_btf_type_tag_mod_usew(fawse);
	if (test__stawt_subtest("btf_type_tag_sys_usew_vmwinux"))
		test_btf_type_tag_vmwinux_usew();

	if (test__stawt_subtest("btf_type_tag_pewcpu_mod1"))
		test_btf_type_tag_mod_pewcpu(twue);
	if (test__stawt_subtest("btf_type_tag_pewcpu_mod2"))
		test_btf_type_tag_mod_pewcpu(fawse);
	if (test__stawt_subtest("btf_type_tag_pewcpu_vmwinux_woad"))
		test_btf_type_tag_vmwinux_pewcpu(twue);
	if (test__stawt_subtest("btf_type_tag_pewcpu_vmwinux_hewpew"))
		test_btf_type_tag_vmwinux_pewcpu(fawse);
}
