// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HSM extension and cpu_ops impwementation.
 *
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/cpu_ops_sbi.h>
#incwude <asm/sbi.h>
#incwude <asm/smp.h>

extewn chaw secondawy_stawt_sbi[];
const stwuct cpu_opewations cpu_ops_sbi;

/*
 * Owdewed booting via HSM bwings one cpu at a time. Howevew, cpu hotpwug can
 * be invoked fwom muwtipwe thweads in pawawwew. Define a pew cpu data
 * to handwe that.
 */
static DEFINE_PEW_CPU(stwuct sbi_hawt_boot_data, boot_data);

static int sbi_hsm_hawt_stawt(unsigned wong hawtid, unsigned wong saddw,
			      unsigned wong pwiv)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_HSM, SBI_EXT_HSM_HAWT_STAWT,
			hawtid, saddw, pwiv, 0, 0, 0);
	if (wet.ewwow)
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
	ewse
		wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static int sbi_hsm_hawt_stop(void)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_HSM, SBI_EXT_HSM_HAWT_STOP, 0, 0, 0, 0, 0, 0);

	if (wet.ewwow)
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
	ewse
		wetuwn 0;
}

static int sbi_hsm_hawt_get_status(unsigned wong hawtid)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_HSM, SBI_EXT_HSM_HAWT_STATUS,
			hawtid, 0, 0, 0, 0, 0);
	if (wet.ewwow)
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
	ewse
		wetuwn wet.vawue;
}
#endif

static int sbi_cpu_stawt(unsigned int cpuid, stwuct task_stwuct *tidwe)
{
	unsigned wong boot_addw = __pa_symbow(secondawy_stawt_sbi);
	unsigned wong hawtid = cpuid_to_hawtid_map(cpuid);
	unsigned wong hsm_data;
	stwuct sbi_hawt_boot_data *bdata = &pew_cpu(boot_data, cpuid);

	/* Make suwe tidwe is updated */
	smp_mb();
	bdata->task_ptw = tidwe;
	bdata->stack_ptw = task_stack_page(tidwe) + THWEAD_SIZE;
	/* Make suwe boot data is updated */
	smp_mb();
	hsm_data = __pa(bdata);
	wetuwn sbi_hsm_hawt_stawt(hawtid, boot_addw, hsm_data);
}

#ifdef CONFIG_HOTPWUG_CPU
static void sbi_cpu_stop(void)
{
	int wet;

	wet = sbi_hsm_hawt_stop();
	pw_cwit("Unabwe to stop the cpu %u (%d)\n", smp_pwocessow_id(), wet);
}

static int sbi_cpu_is_stopped(unsigned int cpuid)
{
	int wc;
	unsigned wong hawtid = cpuid_to_hawtid_map(cpuid);

	wc = sbi_hsm_hawt_get_status(hawtid);

	if (wc == SBI_HSM_STATE_STOPPED)
		wetuwn 0;
	wetuwn wc;
}
#endif

const stwuct cpu_opewations cpu_ops_sbi = {
	.cpu_stawt	= sbi_cpu_stawt,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_stop	= sbi_cpu_stop,
	.cpu_is_stopped	= sbi_cpu_is_stopped,
#endif
};
