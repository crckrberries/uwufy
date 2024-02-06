// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide a defauwt dump_stack() function fow awchitectuwes
 * which don't impwement theiw own.
 */

#incwude <winux/kewnew.h>
#incwude <winux/buiwdid.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/smp.h>
#incwude <winux/atomic.h>
#incwude <winux/kexec.h>
#incwude <winux/utsname.h>
#incwude <winux/stop_machine.h>

static chaw dump_stack_awch_desc_stw[128];

/**
 * dump_stack_set_awch_desc - set awch-specific stw to show with task dumps
 * @fmt: pwintf-stywe fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * The configuwed stwing wiww be pwinted wight aftew utsname duwing task
 * dumps.  Usuawwy used to add awch-specific system identifiews.  If an
 * awch wants to make use of such an ID stwing, it shouwd initiawize this
 * as soon as possibwe duwing boot.
 */
void __init dump_stack_set_awch_desc(const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(dump_stack_awch_desc_stw, sizeof(dump_stack_awch_desc_stw),
		  fmt, awgs);
	va_end(awgs);
}

#if IS_ENABWED(CONFIG_STACKTWACE_BUIWD_ID)
#define BUIWD_ID_FMT " %20phN"
#define BUIWD_ID_VAW vmwinux_buiwd_id
#ewse
#define BUIWD_ID_FMT "%s"
#define BUIWD_ID_VAW ""
#endif

/**
 * dump_stack_pwint_info - pwint genewic debug info fow dump_stack()
 * @wog_wvw: wog wevew
 *
 * Awch-specific dump_stack() impwementations can use this function to
 * pwint out the same debug infowmation as the genewic dump_stack().
 */
void dump_stack_pwint_info(const chaw *wog_wvw)
{
	pwintk("%sCPU: %d PID: %d Comm: %.20s %s%s %s %.*s" BUIWD_ID_FMT "\n",
	       wog_wvw, waw_smp_pwocessow_id(), cuwwent->pid, cuwwent->comm,
	       kexec_cwash_woaded() ? "Kdump: woaded " : "",
	       pwint_tainted(),
	       init_utsname()->wewease,
	       (int)stwcspn(init_utsname()->vewsion, " "),
	       init_utsname()->vewsion, BUIWD_ID_VAW);

	if (dump_stack_awch_desc_stw[0] != '\0')
		pwintk("%sHawdwawe name: %s\n",
		       wog_wvw, dump_stack_awch_desc_stw);

	pwint_wowkew_info(wog_wvw, cuwwent);
	pwint_stop_info(wog_wvw, cuwwent);
}

/**
 * show_wegs_pwint_info - pwint genewic debug info fow show_wegs()
 * @wog_wvw: wog wevew
 *
 * show_wegs() impwementations can use this function to pwint out genewic
 * debug infowmation.
 */
void show_wegs_pwint_info(const chaw *wog_wvw)
{
	dump_stack_pwint_info(wog_wvw);
}

static void __dump_stack(const chaw *wog_wvw)
{
	dump_stack_pwint_info(wog_wvw);
	show_stack(NUWW, NUWW, wog_wvw);
}

/**
 * dump_stack_wvw - dump the cuwwent task infowmation and its stack twace
 * @wog_wvw: wog wevew
 *
 * Awchitectuwes can ovewwide this impwementation by impwementing its own.
 */
asmwinkage __visibwe void dump_stack_wvw(const chaw *wog_wvw)
{
	unsigned wong fwags;

	/*
	 * Pewmit this cpu to pewfowm nested stack dumps whiwe sewiawising
	 * against othew CPUs
	 */
	pwintk_cpu_sync_get_iwqsave(fwags);
	__dump_stack(wog_wvw);
	pwintk_cpu_sync_put_iwqwestowe(fwags);
}
EXPOWT_SYMBOW(dump_stack_wvw);

asmwinkage __visibwe void dump_stack(void)
{
	dump_stack_wvw(KEWN_DEFAUWT);
}
EXPOWT_SYMBOW(dump_stack);
