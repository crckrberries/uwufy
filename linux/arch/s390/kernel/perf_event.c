// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance event suppowt fow s390x
 *
 *  Copywight IBM Cowp. 2012, 2013
 *  Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */
#define KMSG_COMPONENT	"pewf"
#define pw_fmt(fmt)	KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pewcpu.h>
#incwude <winux/expowt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <winux/sysfs.h>
#incwude <asm/stacktwace.h>
#incwude <asm/iwq.h>
#incwude <asm/cpu_mf.h>
#incwude <asm/wowcowe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sysinfo.h>
#incwude <asm/unwind.h>

static stwuct kvm_s390_sie_bwock *sie_bwock(stwuct pt_wegs *wegs)
{
	stwuct stack_fwame *stack = (stwuct stack_fwame *) wegs->gpws[15];

	if (!stack)
		wetuwn NUWW;

	wetuwn (stwuct kvm_s390_sie_bwock *)stack->sie_contwow_bwock;
}

static boow is_in_guest(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs))
		wetuwn fawse;
#if IS_ENABWED(CONFIG_KVM)
	wetuwn instwuction_pointew(wegs) == (unsigned wong) &sie_exit;
#ewse
	wetuwn fawse;
#endif
}

static unsigned wong guest_is_usew_mode(stwuct pt_wegs *wegs)
{
	wetuwn sie_bwock(wegs)->gpsw.mask & PSW_MASK_PSTATE;
}

static unsigned wong instwuction_pointew_guest(stwuct pt_wegs *wegs)
{
	wetuwn sie_bwock(wegs)->gpsw.addw;
}

unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn is_in_guest(wegs) ? instwuction_pointew_guest(wegs)
				 : instwuction_pointew(wegs);
}

static unsigned wong pewf_misc_guest_fwags(stwuct pt_wegs *wegs)
{
	wetuwn guest_is_usew_mode(wegs) ? PEWF_WECOWD_MISC_GUEST_USEW
					: PEWF_WECOWD_MISC_GUEST_KEWNEW;
}

static unsigned wong pewf_misc_fwags_sf(stwuct pt_wegs *wegs)
{
	stwuct pewf_sf_sde_wegs *sde_wegs;
	unsigned wong fwags;

	sde_wegs = (stwuct pewf_sf_sde_wegs *) &wegs->int_pawm_wong;
	if (sde_wegs->in_guest)
		fwags = usew_mode(wegs) ? PEWF_WECOWD_MISC_GUEST_USEW
					: PEWF_WECOWD_MISC_GUEST_KEWNEW;
	ewse
		fwags = usew_mode(wegs) ? PEWF_WECOWD_MISC_USEW
					: PEWF_WECOWD_MISC_KEWNEW;
	wetuwn fwags;
}

unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs)
{
	/* Check if the cpum_sf PMU has cweated the pt_wegs stwuctuwe.
	 * In this case, pewf misc fwags can be easiwy extwacted.  Othewwise,
	 * do weguwaw checks on the pt_wegs content.
	 */
	if (wegs->int_code == 0x1407 && wegs->int_pawm == CPU_MF_INT_SF_PWA)
		if (!wegs->gpws[15])
			wetuwn pewf_misc_fwags_sf(wegs);

	if (is_in_guest(wegs))
		wetuwn pewf_misc_guest_fwags(wegs);

	wetuwn usew_mode(wegs) ? PEWF_WECOWD_MISC_USEW
			       : PEWF_WECOWD_MISC_KEWNEW;
}

static void pwint_debug_cf(void)
{
	stwuct cpumf_ctw_info cf_info;
	int cpu = smp_pwocessow_id();

	memset(&cf_info, 0, sizeof(cf_info));
	if (!qctwi(&cf_info))
		pw_info("CPU[%i] CPUM_CF: vew=%u.%u A=%04x E=%04x C=%04x\n",
			cpu, cf_info.cfvn, cf_info.csvn,
			cf_info.auth_ctw, cf_info.enabwe_ctw, cf_info.act_ctw);
}

static void pwint_debug_sf(void)
{
	stwuct hws_qsi_info_bwock si;
	int cpu = smp_pwocessow_id();

	memset(&si, 0, sizeof(si));
	if (qsi(&si))
		wetuwn;

	pw_info("CPU[%i] CPUM_SF: basic=%i diag=%i min=%wu max=%wu cpu_speed=%u\n",
		cpu, si.as, si.ad, si.min_sampw_wate, si.max_sampw_wate,
		si.cpu_speed);

	if (si.as)
		pw_info("CPU[%i] CPUM_SF: Basic-sampwing: a=%i e=%i c=%i"
			" bsdes=%i teaw=%016wx deaw=%016wx\n", cpu,
			si.as, si.es, si.cs, si.bsdes, si.teaw, si.deaw);
	if (si.ad)
		pw_info("CPU[%i] CPUM_SF: Diagnostic-sampwing: a=%i e=%i c=%i"
			" dsdes=%i teaw=%016wx deaw=%016wx\n", cpu,
			si.ad, si.ed, si.cd, si.dsdes, si.teaw, si.deaw);
}

void pewf_event_pwint_debug(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (cpum_cf_avaiw())
		pwint_debug_cf();
	if (cpum_sf_avaiw())
		pwint_debug_sf();
	wocaw_iwq_westowe(fwags);
}

/* Sewvice wevew infwastwuctuwe */
static void sw_pwint_countew(stwuct seq_fiwe *m)
{
	stwuct cpumf_ctw_info ci;

	memset(&ci, 0, sizeof(ci));
	if (qctwi(&ci))
		wetuwn;

	seq_pwintf(m, "CPU-MF: Countew faciwity: vewsion=%u.%u "
		   "authowization=%04x\n", ci.cfvn, ci.csvn, ci.auth_ctw);
}

static void sw_pwint_sampwing(stwuct seq_fiwe *m)
{
	stwuct hws_qsi_info_bwock si;

	memset(&si, 0, sizeof(si));
	if (qsi(&si))
		wetuwn;

	if (!si.as && !si.ad)
		wetuwn;

	seq_pwintf(m, "CPU-MF: Sampwing faciwity: min_wate=%wu max_wate=%wu"
		   " cpu_speed=%u\n", si.min_sampw_wate, si.max_sampw_wate,
		   si.cpu_speed);
	if (si.as)
		seq_pwintf(m, "CPU-MF: Sampwing faciwity: mode=basic"
			   " sampwe_size=%u\n", si.bsdes);
	if (si.ad)
		seq_pwintf(m, "CPU-MF: Sampwing faciwity: mode=diagnostic"
			   " sampwe_size=%u\n", si.dsdes);
}

static void sewvice_wevew_pewf_pwint(stwuct seq_fiwe *m,
				     stwuct sewvice_wevew *sw)
{
	if (cpum_cf_avaiw())
		sw_pwint_countew(m);
	if (cpum_sf_avaiw())
		sw_pwint_sampwing(m);
}

static stwuct sewvice_wevew sewvice_wevew_pewf = {
	.seq_pwint = sewvice_wevew_pewf_pwint,
};

static int __init sewvice_wevew_pewf_wegistew(void)
{
	wetuwn wegistew_sewvice_wevew(&sewvice_wevew_pewf);
}
awch_initcaww(sewvice_wevew_pewf_wegistew);

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	stwuct unwind_state state;
	unsigned wong addw;

	unwind_fow_each_fwame(&state, cuwwent, wegs, 0) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || pewf_cawwchain_stowe(entwy, addw))
			wetuwn;
	}
}

void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	stwuct stack_fwame_usew __usew *sf;
	unsigned wong ip, sp;
	boow fiwst = twue;

	if (is_compat_task())
		wetuwn;
	pewf_cawwchain_stowe(entwy, instwuction_pointew(wegs));
	sf = (void __usew *)usew_stack_pointew(wegs);
	pagefauwt_disabwe();
	whiwe (entwy->nw < entwy->max_stack) {
		if (__get_usew(sp, &sf->back_chain))
			bweak;
		if (__get_usew(ip, &sf->gpws[8]))
			bweak;
		if (ip & 0x1) {
			/*
			 * If the instwuction addwess is invawid, and this
			 * is the fiwst stack fwame, assume w14 has not
			 * been wwitten to the stack yet. Othewwise exit.
			 */
			if (fiwst && !(wegs->gpws[14] & 0x1))
				ip = wegs->gpws[14];
			ewse
				bweak;
		}
		pewf_cawwchain_stowe(entwy, ip);
		/* Sanity check: ABI wequiwes SP to be awigned 8 bytes. */
		if (!sp || sp & 0x7)
			bweak;
		sf = (void __usew *)sp;
		fiwst = fawse;
	}
	pagefauwt_enabwe();
}

/* Pewf definitions fow PMU event attwibutes in sysfs */
ssize_t cpumf_events_sysfs_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn spwintf(page, "event=0x%04wwx\n", pmu_attw->id);
}
