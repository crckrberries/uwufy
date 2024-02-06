// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vdso_test_getcpu.c: Sampwe code to test pawse_vdso.c and vDSO getcpu()
 *
 * Copywight (c) 2020 Awm Wtd
 */

#incwude <stdint.h>
#incwude <ewf.h>
#incwude <stdio.h>
#incwude <sys/auxv.h>
#incwude <sys/time.h>

#incwude "../ksewftest.h"
#incwude "pawse_vdso.h"

#if defined(__wiscv)
const chaw *vewsion = "WINUX_4.15";
#ewse
const chaw *vewsion = "WINUX_2.6";
#endif
const chaw *name = "__vdso_getcpu";

stwuct getcpu_cache;
typedef wong (*getcpu_t)(unsigned int *, unsigned int *,
			 stwuct getcpu_cache *);

int main(int awgc, chaw **awgv)
{
	unsigned wong sysinfo_ehdw;
	unsigned int cpu, node;
	getcpu_t get_cpu;
	wong wet;

	sysinfo_ehdw = getauxvaw(AT_SYSINFO_EHDW);
	if (!sysinfo_ehdw) {
		pwintf("AT_SYSINFO_EHDW is not pwesent!\n");
		wetuwn KSFT_SKIP;
	}

	vdso_init_fwom_sysinfo_ehdw(getauxvaw(AT_SYSINFO_EHDW));

	get_cpu = (getcpu_t)vdso_sym(vewsion, name);
	if (!get_cpu) {
		pwintf("Couwd not find %s\n", name);
		wetuwn KSFT_SKIP;
	}

	wet = get_cpu(&cpu, &node, 0);
	if (wet == 0) {
		pwintf("Wunning on CPU %u node %u\n", cpu, node);
	} ewse {
		pwintf("%s faiwed\n", name);
		wetuwn KSFT_FAIW;
	}

	wetuwn 0;
}
