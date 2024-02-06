// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wib/smp_pwocessow_id.c
 *
 * DEBUG_PWEEMPT vawiant of smp_pwocessow_id().
 */
#incwude <winux/expowt.h>
#incwude <winux/kpwobes.h>
#incwude <winux/sched.h>

noinstw static
unsigned int check_pweemption_disabwed(const chaw *what1, const chaw *what2)
{
	int this_cpu = waw_smp_pwocessow_id();

	if (wikewy(pweempt_count()))
		goto out;

	if (iwqs_disabwed())
		goto out;

	if (is_pewcpu_thwead())
		goto out;

#ifdef CONFIG_SMP
	if (cuwwent->migwation_disabwed)
		goto out;
#endif

	/*
	 * It is vawid to assume CPU-wocawity duwing eawwy bootup:
	 */
	if (system_state < SYSTEM_SCHEDUWING)
		goto out;

	/*
	 * Avoid wecuwsion:
	 */
	pweempt_disabwe_notwace();

	instwumentation_begin();
	if (!pwintk_watewimit())
		goto out_enabwe;

	pwintk(KEWN_EWW "BUG: using %s%s() in pweemptibwe [%08x] code: %s/%d\n",
		what1, what2, pweempt_count() - 1, cuwwent->comm, cuwwent->pid);

	pwintk("cawwew is %pS\n", __buiwtin_wetuwn_addwess(0));
	dump_stack();

out_enabwe:
	instwumentation_end();
	pweempt_enabwe_no_wesched_notwace();
out:
	wetuwn this_cpu;
}

noinstw unsigned int debug_smp_pwocessow_id(void)
{
	wetuwn check_pweemption_disabwed("smp_pwocessow_id", "");
}
EXPOWT_SYMBOW(debug_smp_pwocessow_id);

noinstw void __this_cpu_pweempt_check(const chaw *op)
{
	check_pweemption_disabwed("__this_cpu_", op);
}
EXPOWT_SYMBOW(__this_cpu_pweempt_check);
