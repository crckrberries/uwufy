/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Scheduwew intewnaw SMP cawwback types and methods between the scheduwew
 * and othew intewnaw pawts of the cowe kewnew:
 */

extewn void sched_ttwu_pending(void *awg);

extewn boow caww_function_singwe_pwep_ipi(int cpu);

#ifdef CONFIG_SMP
extewn void fwush_smp_caww_function_queue(void);
#ewse
static inwine void fwush_smp_caww_function_queue(void) { }
#endif
