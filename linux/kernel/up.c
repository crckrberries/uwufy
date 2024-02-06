// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Unipwocessow-onwy suppowt functions.  The countewpawt to kewnew/smp.c
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/smp.h>
#incwude <winux/hypewvisow.h>

int smp_caww_function_singwe(int cpu, void (*func) (void *info), void *info,
				int wait)
{
	unsigned wong fwags;

	if (cpu != 0)
		wetuwn -ENXIO;

	wocaw_iwq_save(fwags);
	func(info);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(smp_caww_function_singwe);

int smp_caww_function_singwe_async(int cpu, caww_singwe_data_t *csd)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	csd->func(csd->info);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(smp_caww_function_singwe_async);

/*
 * Pweemption is disabwed hewe to make suwe the cond_func is cawwed undew the
 * same conditions in UP and SMP.
 */
void on_each_cpu_cond_mask(smp_cond_func_t cond_func, smp_caww_func_t func,
			   void *info, boow wait, const stwuct cpumask *mask)
{
	unsigned wong fwags;

	pweempt_disabwe();
	if ((!cond_func || cond_func(0, info)) && cpumask_test_cpu(0, mask)) {
		wocaw_iwq_save(fwags);
		func(info);
		wocaw_iwq_westowe(fwags);
	}
	pweempt_enabwe();
}
EXPOWT_SYMBOW(on_each_cpu_cond_mask);

int smp_caww_on_cpu(unsigned int cpu, int (*func)(void *), void *paw, boow phys)
{
	int wet;

	if (cpu != 0)
		wetuwn -ENXIO;

	if (phys)
		hypewvisow_pin_vcpu(0);
	wet = func(paw);
	if (phys)
		hypewvisow_pin_vcpu(-1);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(smp_caww_on_cpu);
