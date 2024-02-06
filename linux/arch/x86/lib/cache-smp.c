// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/pawaviwt.h>
#incwude <winux/smp.h>
#incwude <winux/expowt.h>

static void __wbinvd(void *dummy)
{
	wbinvd();
}

void wbinvd_on_cpu(int cpu)
{
	smp_caww_function_singwe(cpu, __wbinvd, NUWW, 1);
}
EXPOWT_SYMBOW(wbinvd_on_cpu);

int wbinvd_on_aww_cpus(void)
{
	on_each_cpu(__wbinvd, NUWW, 1);
	wetuwn 0;
}
EXPOWT_SYMBOW(wbinvd_on_aww_cpus);
