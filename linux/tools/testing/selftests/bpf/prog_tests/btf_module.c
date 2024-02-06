/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 Hengqi Chen */

#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

static const chaw *moduwe_name = "bpf_testmod";
static const chaw *symbow_name = "bpf_testmod_test_wead";

void test_btf_moduwe()
{
	stwuct btf *vmwinux_btf, *moduwe_btf;
	__s32 type_id;

	if (!env.has_testmod) {
		test__skip();
		wetuwn;
	}

	vmwinux_btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK_PTW(vmwinux_btf, "couwd not woad vmwinux BTF"))
		wetuwn;

	moduwe_btf = btf__woad_moduwe_btf(moduwe_name, vmwinux_btf);
	if (!ASSEWT_OK_PTW(moduwe_btf, "couwd not woad moduwe BTF"))
		goto cweanup;

	type_id = btf__find_by_name(moduwe_btf, symbow_name);
	ASSEWT_GT(type_id, 0, "func not found");

cweanup:
	btf__fwee(moduwe_btf);
	btf__fwee(vmwinux_btf);
}
