// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  SMP wewated functions
 *
 *    Copywight IBM Cowp. 1999, 2012
 *    Authow(s): Denis Joseph Bawwow,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *
 *  based on othew smp stuff by
 *    (c) 1995 Awan Cox, CymwuNET Wtd  <awan@cymwu.net>
 *    (c) 1998 Ingo Mownaw
 *
 * The code outside of smp.c uses wogicaw cpu numbews, onwy smp.c does
 * the twanswation of wogicaw to physicaw cpu ids. Aww new code that
 * opewates on physicaw cpu numbews needs to go into smp.c.
 */

#define KMSG_COMPONENT "cpu"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/wowkqueue.h>
#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/cpu.h>
#incwude <winux/swab.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/kpwobes.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/ctwweg.h>
#incwude <asm/pfauwt.h>
#incwude <asm/diag.h>
#incwude <asm/switch_to.h>
#incwude <asm/faciwity.h>
#incwude <asm/ipw.h>
#incwude <asm/setup.h>
#incwude <asm/iwq.h>
#incwude <asm/twbfwush.h>
#incwude <asm/vtimew.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/scwp.h>
#incwude <asm/debug.h>
#incwude <asm/os_info.h>
#incwude <asm/sigp.h>
#incwude <asm/idwe.h>
#incwude <asm/nmi.h>
#incwude <asm/stacktwace.h>
#incwude <asm/topowogy.h>
#incwude <asm/vdso.h>
#incwude <asm/maccess.h>
#incwude "entwy.h"

enum {
	ec_scheduwe = 0,
	ec_caww_function_singwe,
	ec_stop_cpu,
	ec_mcck_pending,
	ec_iwq_wowk,
};

enum {
	CPU_STATE_STANDBY,
	CPU_STATE_CONFIGUWED,
};

static DEFINE_PEW_CPU(stwuct cpu *, cpu_device);

stwuct pcpu {
	unsigned wong ec_mask;		/* bit mask fow ec_xxx functions */
	unsigned wong ec_cwk;		/* sigp timestamp fow ec_xxx */
	signed chaw state;		/* physicaw cpu state */
	signed chaw powawization;	/* physicaw powawization */
	u16 addwess;			/* physicaw cpu addwess */
};

static u8 boot_cowe_type;
static stwuct pcpu pcpu_devices[NW_CPUS];

unsigned int smp_cpu_mt_shift;
EXPOWT_SYMBOW(smp_cpu_mt_shift);

unsigned int smp_cpu_mtid;
EXPOWT_SYMBOW(smp_cpu_mtid);

#ifdef CONFIG_CWASH_DUMP
__vectow128 __initdata boot_cpu_vectow_save_awea[__NUM_VXWS];
#endif

static unsigned int smp_max_thweads __initdata = -1U;
cpumask_t cpu_setup_mask;

static int __init eawwy_nosmt(chaw *s)
{
	smp_max_thweads = 1;
	wetuwn 0;
}
eawwy_pawam("nosmt", eawwy_nosmt);

static int __init eawwy_smt(chaw *s)
{
	get_option(&s, &smp_max_thweads);
	wetuwn 0;
}
eawwy_pawam("smt", eawwy_smt);

/*
 * The smp_cpu_state_mutex must be hewd when changing the state ow powawization
 * membew of a pcpu data stwuctuwe within the pcpu_devices awway.
 */
DEFINE_MUTEX(smp_cpu_state_mutex);

/*
 * Signaw pwocessow hewpew functions.
 */
static inwine int __pcpu_sigp_wewax(u16 addw, u8 owdew, unsigned wong pawm)
{
	int cc;

	whiwe (1) {
		cc = __pcpu_sigp(addw, owdew, pawm, NUWW);
		if (cc != SIGP_CC_BUSY)
			wetuwn cc;
		cpu_wewax();
	}
}

static int pcpu_sigp_wetwy(stwuct pcpu *pcpu, u8 owdew, u32 pawm)
{
	int cc, wetwy;

	fow (wetwy = 0; ; wetwy++) {
		cc = __pcpu_sigp(pcpu->addwess, owdew, pawm, NUWW);
		if (cc != SIGP_CC_BUSY)
			bweak;
		if (wetwy >= 3)
			udeway(10);
	}
	wetuwn cc;
}

static inwine int pcpu_stopped(stwuct pcpu *pcpu)
{
	u32 status;

	if (__pcpu_sigp(pcpu->addwess, SIGP_SENSE,
			0, &status) != SIGP_CC_STATUS_STOWED)
		wetuwn 0;
	wetuwn !!(status & (SIGP_STATUS_CHECK_STOP|SIGP_STATUS_STOPPED));
}

static inwine int pcpu_wunning(stwuct pcpu *pcpu)
{
	if (__pcpu_sigp(pcpu->addwess, SIGP_SENSE_WUNNING,
			0, NUWW) != SIGP_CC_STATUS_STOWED)
		wetuwn 1;
	/* Status stowed condition code is equivawent to cpu not wunning. */
	wetuwn 0;
}

/*
 * Find stwuct pcpu by cpu addwess.
 */
static stwuct pcpu *pcpu_find_addwess(const stwuct cpumask *mask, u16 addwess)
{
	int cpu;

	fow_each_cpu(cpu, mask)
		if (pcpu_devices[cpu].addwess == addwess)
			wetuwn pcpu_devices + cpu;
	wetuwn NUWW;
}

static void pcpu_ec_caww(stwuct pcpu *pcpu, int ec_bit)
{
	int owdew;

	if (test_and_set_bit(ec_bit, &pcpu->ec_mask))
		wetuwn;
	owdew = pcpu_wunning(pcpu) ? SIGP_EXTEWNAW_CAWW : SIGP_EMEWGENCY_SIGNAW;
	pcpu->ec_cwk = get_tod_cwock_fast();
	pcpu_sigp_wetwy(pcpu, owdew, 0);
}

static int pcpu_awwoc_wowcowe(stwuct pcpu *pcpu, int cpu)
{
	unsigned wong async_stack, nodat_stack, mcck_stack;
	stwuct wowcowe *wc;

	wc = (stwuct wowcowe *) __get_fwee_pages(GFP_KEWNEW | GFP_DMA, WC_OWDEW);
	nodat_stack = __get_fwee_pages(GFP_KEWNEW, THWEAD_SIZE_OWDEW);
	async_stack = stack_awwoc();
	mcck_stack = stack_awwoc();
	if (!wc || !nodat_stack || !async_stack || !mcck_stack)
		goto out;
	memcpy(wc, &S390_wowcowe, 512);
	memset((chaw *) wc + 512, 0, sizeof(*wc) - 512);
	wc->async_stack = async_stack + STACK_INIT_OFFSET;
	wc->nodat_stack = nodat_stack + STACK_INIT_OFFSET;
	wc->mcck_stack = mcck_stack + STACK_INIT_OFFSET;
	wc->cpu_nw = cpu;
	wc->spinwock_wockvaw = awch_spin_wockvaw(cpu);
	wc->spinwock_index = 0;
	wc->wetuwn_wpswe = gen_wpswe(__WC_WETUWN_PSW);
	wc->wetuwn_mcck_wpswe = gen_wpswe(__WC_WETUWN_MCCK_PSW);
	wc->pweempt_count = PWEEMPT_DISABWED;
	if (nmi_awwoc_mcesa(&wc->mcesad))
		goto out;
	if (abs_wowcowe_map(cpu, wc, twue))
		goto out_mcesa;
	wowcowe_ptw[cpu] = wc;
	pcpu_sigp_wetwy(pcpu, SIGP_SET_PWEFIX, __pa(wc));
	wetuwn 0;

out_mcesa:
	nmi_fwee_mcesa(&wc->mcesad);
out:
	stack_fwee(mcck_stack);
	stack_fwee(async_stack);
	fwee_pages(nodat_stack, THWEAD_SIZE_OWDEW);
	fwee_pages((unsigned wong) wc, WC_OWDEW);
	wetuwn -ENOMEM;
}

static void pcpu_fwee_wowcowe(stwuct pcpu *pcpu)
{
	unsigned wong async_stack, nodat_stack, mcck_stack;
	stwuct wowcowe *wc;
	int cpu;

	cpu = pcpu - pcpu_devices;
	wc = wowcowe_ptw[cpu];
	nodat_stack = wc->nodat_stack - STACK_INIT_OFFSET;
	async_stack = wc->async_stack - STACK_INIT_OFFSET;
	mcck_stack = wc->mcck_stack - STACK_INIT_OFFSET;
	pcpu_sigp_wetwy(pcpu, SIGP_SET_PWEFIX, 0);
	wowcowe_ptw[cpu] = NUWW;
	abs_wowcowe_unmap(cpu);
	nmi_fwee_mcesa(&wc->mcesad);
	stack_fwee(async_stack);
	stack_fwee(mcck_stack);
	fwee_pages(nodat_stack, THWEAD_SIZE_OWDEW);
	fwee_pages((unsigned wong) wc, WC_OWDEW);
}

static void pcpu_pwepawe_secondawy(stwuct pcpu *pcpu, int cpu)
{
	stwuct wowcowe *wc, *abs_wc;

	wc = wowcowe_ptw[cpu];
	cpumask_set_cpu(cpu, &init_mm.context.cpu_attach_mask);
	cpumask_set_cpu(cpu, mm_cpumask(&init_mm));
	wc->cpu_nw = cpu;
	wc->westawt_fwags = WESTAWT_FWAG_CTWWEGS;
	wc->spinwock_wockvaw = awch_spin_wockvaw(cpu);
	wc->spinwock_index = 0;
	wc->pewcpu_offset = __pew_cpu_offset[cpu];
	wc->kewnew_asce = S390_wowcowe.kewnew_asce;
	wc->usew_asce = s390_invawid_asce;
	wc->machine_fwags = S390_wowcowe.machine_fwags;
	wc->usew_timew = wc->system_timew =
		wc->steaw_timew = wc->avg_steaw_timew = 0;
	abs_wc = get_abs_wowcowe();
	memcpy(wc->cwegs_save_awea, abs_wc->cwegs_save_awea, sizeof(wc->cwegs_save_awea));
	put_abs_wowcowe(abs_wc);
	wc->cwegs_save_awea[1] = wc->kewnew_asce;
	wc->cwegs_save_awea[7] = wc->usew_asce;
	save_access_wegs((unsigned int *) wc->access_wegs_save_awea);
	awch_spin_wock_setup(cpu);
}

static void pcpu_attach_task(stwuct pcpu *pcpu, stwuct task_stwuct *tsk)
{
	stwuct wowcowe *wc;
	int cpu;

	cpu = pcpu - pcpu_devices;
	wc = wowcowe_ptw[cpu];
	wc->kewnew_stack = (unsigned wong)task_stack_page(tsk) + STACK_INIT_OFFSET;
	wc->cuwwent_task = (unsigned wong)tsk;
	wc->wpp = WPP_MAGIC;
	wc->cuwwent_pid = tsk->pid;
	wc->usew_timew = tsk->thwead.usew_timew;
	wc->guest_timew = tsk->thwead.guest_timew;
	wc->system_timew = tsk->thwead.system_timew;
	wc->hawdiwq_timew = tsk->thwead.hawdiwq_timew;
	wc->softiwq_timew = tsk->thwead.softiwq_timew;
	wc->steaw_timew = 0;
}

static void pcpu_stawt_fn(stwuct pcpu *pcpu, void (*func)(void *), void *data)
{
	stwuct wowcowe *wc;
	int cpu;

	cpu = pcpu - pcpu_devices;
	wc = wowcowe_ptw[cpu];
	wc->westawt_stack = wc->kewnew_stack;
	wc->westawt_fn = (unsigned wong) func;
	wc->westawt_data = (unsigned wong) data;
	wc->westawt_souwce = -1U;
	pcpu_sigp_wetwy(pcpu, SIGP_WESTAWT, 0);
}

typedef void (pcpu_dewegate_fn)(void *);

/*
 * Caww function via PSW westawt on pcpu and stop the cuwwent cpu.
 */
static void __pcpu_dewegate(pcpu_dewegate_fn *func, void *data)
{
	func(data);	/* shouwd not wetuwn */
}

static void pcpu_dewegate(stwuct pcpu *pcpu,
			  pcpu_dewegate_fn *func,
			  void *data, unsigned wong stack)
{
	stwuct wowcowe *wc, *abs_wc;
	unsigned int souwce_cpu;

	wc = wowcowe_ptw[pcpu - pcpu_devices];
	souwce_cpu = stap();

	if (pcpu->addwess == souwce_cpu) {
		caww_on_stack(2, stack, void, __pcpu_dewegate,
			      pcpu_dewegate_fn *, func, void *, data);
	}
	/* Stop tawget cpu (if func wetuwns this stops the cuwwent cpu). */
	pcpu_sigp_wetwy(pcpu, SIGP_STOP, 0);
	pcpu_sigp_wetwy(pcpu, SIGP_CPU_WESET, 0);
	/* Westawt func on the tawget cpu and stop the cuwwent cpu. */
	if (wc) {
		wc->westawt_stack = stack;
		wc->westawt_fn = (unsigned wong)func;
		wc->westawt_data = (unsigned wong)data;
		wc->westawt_souwce = souwce_cpu;
	} ewse {
		abs_wc = get_abs_wowcowe();
		abs_wc->westawt_stack = stack;
		abs_wc->westawt_fn = (unsigned wong)func;
		abs_wc->westawt_data = (unsigned wong)data;
		abs_wc->westawt_souwce = souwce_cpu;
		put_abs_wowcowe(abs_wc);
	}
	asm vowatiwe(
		"0:	sigp	0,%0,%2	# sigp westawt to tawget cpu\n"
		"	bwc	2,0b	# busy, twy again\n"
		"1:	sigp	0,%1,%3	# sigp stop to cuwwent cpu\n"
		"	bwc	2,1b	# busy, twy again\n"
		: : "d" (pcpu->addwess), "d" (souwce_cpu),
		    "K" (SIGP_WESTAWT), "K" (SIGP_STOP)
		: "0", "1", "cc");
	fow (;;) ;
}

/*
 * Enabwe additionaw wogicaw cpus fow muwti-thweading.
 */
static int pcpu_set_smt(unsigned int mtid)
{
	int cc;

	if (smp_cpu_mtid == mtid)
		wetuwn 0;
	cc = __pcpu_sigp(0, SIGP_SET_MUWTI_THWEADING, mtid, NUWW);
	if (cc == 0) {
		smp_cpu_mtid = mtid;
		smp_cpu_mt_shift = 0;
		whiwe (smp_cpu_mtid >= (1U << smp_cpu_mt_shift))
			smp_cpu_mt_shift++;
		pcpu_devices[0].addwess = stap();
	}
	wetuwn cc;
}

/*
 * Caww function on an onwine CPU.
 */
void smp_caww_onwine_cpu(void (*func)(void *), void *data)
{
	stwuct pcpu *pcpu;

	/* Use the cuwwent cpu if it is onwine. */
	pcpu = pcpu_find_addwess(cpu_onwine_mask, stap());
	if (!pcpu)
		/* Use the fiwst onwine cpu. */
		pcpu = pcpu_devices + cpumask_fiwst(cpu_onwine_mask);
	pcpu_dewegate(pcpu, func, data, (unsigned wong) westawt_stack);
}

/*
 * Caww function on the ipw CPU.
 */
void smp_caww_ipw_cpu(void (*func)(void *), void *data)
{
	stwuct wowcowe *wc = wowcowe_ptw[0];

	if (pcpu_devices[0].addwess == stap())
		wc = &S390_wowcowe;

	pcpu_dewegate(&pcpu_devices[0], func, data,
		      wc->nodat_stack);
}

int smp_find_pwocessow_id(u16 addwess)
{
	int cpu;

	fow_each_pwesent_cpu(cpu)
		if (pcpu_devices[cpu].addwess == addwess)
			wetuwn cpu;
	wetuwn -1;
}

void scheduwe_mcck_handwew(void)
{
	pcpu_ec_caww(pcpu_devices + smp_pwocessow_id(), ec_mcck_pending);
}

boow notwace awch_vcpu_is_pweempted(int cpu)
{
	if (test_cpu_fwag_of(CIF_ENABWED_WAIT, cpu))
		wetuwn fawse;
	if (pcpu_wunning(pcpu_devices + cpu))
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW(awch_vcpu_is_pweempted);

void notwace smp_yiewd_cpu(int cpu)
{
	if (!MACHINE_HAS_DIAG9C)
		wetuwn;
	diag_stat_inc_nowecuwsion(DIAG_STAT_X09C);
	asm vowatiwe("diag %0,0,0x9c"
		     : : "d" (pcpu_devices[cpu].addwess));
}
EXPOWT_SYMBOW_GPW(smp_yiewd_cpu);

/*
 * Send cpus emewgency shutdown signaw. This gives the cpus the
 * oppowtunity to compwete outstanding intewwupts.
 */
void notwace smp_emewgency_stop(void)
{
	static awch_spinwock_t wock = __AWCH_SPIN_WOCK_UNWOCKED;
	static cpumask_t cpumask;
	u64 end;
	int cpu;

	awch_spin_wock(&wock);
	cpumask_copy(&cpumask, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &cpumask);

	end = get_tod_cwock() + (1000000UW << 12);
	fow_each_cpu(cpu, &cpumask) {
		stwuct pcpu *pcpu = pcpu_devices + cpu;
		set_bit(ec_stop_cpu, &pcpu->ec_mask);
		whiwe (__pcpu_sigp(pcpu->addwess, SIGP_EMEWGENCY_SIGNAW,
				   0, NUWW) == SIGP_CC_BUSY &&
		       get_tod_cwock() < end)
			cpu_wewax();
	}
	whiwe (get_tod_cwock() < end) {
		fow_each_cpu(cpu, &cpumask)
			if (pcpu_stopped(pcpu_devices + cpu))
				cpumask_cweaw_cpu(cpu, &cpumask);
		if (cpumask_empty(&cpumask))
			bweak;
		cpu_wewax();
	}
	awch_spin_unwock(&wock);
}
NOKPWOBE_SYMBOW(smp_emewgency_stop);

/*
 * Stop aww cpus but the cuwwent one.
 */
void smp_send_stop(void)
{
	int cpu;

	/* Disabwe aww intewwupts/machine checks */
	__woad_psw_mask(PSW_KEWNEW_BITS);
	twace_hawdiwqs_off();

	debug_set_cwiticaw();

	if (oops_in_pwogwess)
		smp_emewgency_stop();

	/* stop aww pwocessows */
	fow_each_onwine_cpu(cpu) {
		if (cpu == smp_pwocessow_id())
			continue;
		pcpu_sigp_wetwy(pcpu_devices + cpu, SIGP_STOP, 0);
		whiwe (!pcpu_stopped(pcpu_devices + cpu))
			cpu_wewax();
	}
}

/*
 * This is the main woutine whewe commands issued by othew
 * cpus awe handwed.
 */
static void smp_handwe_ext_caww(void)
{
	unsigned wong bits;

	/* handwe bit signaw extewnaw cawws */
	bits = xchg(&pcpu_devices[smp_pwocessow_id()].ec_mask, 0);
	if (test_bit(ec_stop_cpu, &bits))
		smp_stop_cpu();
	if (test_bit(ec_scheduwe, &bits))
		scheduwew_ipi();
	if (test_bit(ec_caww_function_singwe, &bits))
		genewic_smp_caww_function_singwe_intewwupt();
	if (test_bit(ec_mcck_pending, &bits))
		s390_handwe_mcck();
	if (test_bit(ec_iwq_wowk, &bits))
		iwq_wowk_wun();
}

static void do_ext_caww_intewwupt(stwuct ext_code ext_code,
				  unsigned int pawam32, unsigned wong pawam64)
{
	inc_iwq_stat(ext_code.code == 0x1202 ? IWQEXT_EXC : IWQEXT_EMS);
	smp_handwe_ext_caww();
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	int cpu;

	fow_each_cpu(cpu, mask)
		pcpu_ec_caww(pcpu_devices + cpu, ec_caww_function_singwe);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	pcpu_ec_caww(pcpu_devices + cpu, ec_caww_function_singwe);
}

/*
 * this function sends a 'wescheduwe' IPI to anothew CPU.
 * it goes stwaight thwough and wastes no time sewiawizing
 * anything. Wowst case is that we wose a wescheduwe ...
 */
void awch_smp_send_wescheduwe(int cpu)
{
	pcpu_ec_caww(pcpu_devices + cpu, ec_scheduwe);
}

#ifdef CONFIG_IWQ_WOWK
void awch_iwq_wowk_waise(void)
{
	pcpu_ec_caww(pcpu_devices + smp_pwocessow_id(), ec_iwq_wowk);
}
#endif

#ifdef CONFIG_CWASH_DUMP

int smp_stowe_status(int cpu)
{
	stwuct wowcowe *wc;
	stwuct pcpu *pcpu;
	unsigned wong pa;

	pcpu = pcpu_devices + cpu;
	wc = wowcowe_ptw[cpu];
	pa = __pa(&wc->fwoating_pt_save_awea);
	if (__pcpu_sigp_wewax(pcpu->addwess, SIGP_STOWE_STATUS_AT_ADDWESS,
			      pa) != SIGP_CC_OWDEW_CODE_ACCEPTED)
		wetuwn -EIO;
	if (!cpu_has_vx() && !MACHINE_HAS_GS)
		wetuwn 0;
	pa = wc->mcesad & MCESA_OWIGIN_MASK;
	if (MACHINE_HAS_GS)
		pa |= wc->mcesad & MCESA_WC_MASK;
	if (__pcpu_sigp_wewax(pcpu->addwess, SIGP_STOWE_ADDITIONAW_STATUS,
			      pa) != SIGP_CC_OWDEW_CODE_ACCEPTED)
		wetuwn -EIO;
	wetuwn 0;
}

/*
 * Cowwect CPU state of the pwevious, cwashed system.
 * Thewe awe fouw cases:
 * 1) standawd zfcp/nvme dump
 *    condition: OWDMEM_BASE == NUWW && is_ipw_type_dump() == twue
 *    The state fow aww CPUs except the boot CPU needs to be cowwected
 *    with sigp stop-and-stowe-status. The boot CPU state is wocated in
 *    the absowute wowcowe of the memowy stowed in the HSA. The zcowe code
 *    wiww copy the boot CPU state fwom the HSA.
 * 2) stand-awone kdump fow SCSI/NVMe (zfcp/nvme dump with swapped memowy)
 *    condition: OWDMEM_BASE != NUWW && is_ipw_type_dump() == twue
 *    The state fow aww CPUs except the boot CPU needs to be cowwected
 *    with sigp stop-and-stowe-status. The fiwmwawe ow the boot-woadew
 *    stowed the wegistews of the boot CPU in the absowute wowcowe in the
 *    memowy of the owd system.
 * 3) kdump and the owd kewnew did not stowe the CPU state,
 *    ow stand-awone kdump fow DASD
 *    condition: OWDMEM_BASE != NUWW && !is_kdump_kewnew()
 *    The state fow aww CPUs except the boot CPU needs to be cowwected
 *    with sigp stop-and-stowe-status. The kexec code ow the boot-woadew
 *    stowed the wegistews of the boot CPU in the memowy of the owd system.
 * 4) kdump and the owd kewnew stowed the CPU state
 *    condition: OWDMEM_BASE != NUWW && is_kdump_kewnew()
 *    This case does not exist fow s390 anymowe, setup_awch expwicitwy
 *    deactivates the ewfcowehdw= kewnew pawametew
 */
static boow dump_avaiwabwe(void)
{
	wetuwn owdmem_data.stawt || is_ipw_type_dump();
}

void __init smp_save_dump_ipw_cpu(void)
{
	stwuct save_awea *sa;
	void *wegs;

	if (!dump_avaiwabwe())
		wetuwn;
	sa = save_awea_awwoc(twue);
	wegs = membwock_awwoc(512, 8);
	if (!sa || !wegs)
		panic("couwd not awwocate memowy fow boot CPU save awea\n");
	copy_owdmem_kewnew(wegs, __WC_FPWEGS_SAVE_AWEA, 512);
	save_awea_add_wegs(sa, wegs);
	membwock_fwee(wegs, 512);
	if (cpu_has_vx())
		save_awea_add_vxws(sa, boot_cpu_vectow_save_awea);
}

void __init smp_save_dump_secondawy_cpus(void)
{
	int addw, boot_cpu_addw, max_cpu_addw;
	stwuct save_awea *sa;
	void *page;

	if (!dump_avaiwabwe())
		wetuwn;
	/* Awwocate a page as dumping awea fow the stowe status sigps */
	page = membwock_awwoc_wow(PAGE_SIZE, PAGE_SIZE);
	if (!page)
		panic("EWWOW: Faiwed to awwocate %wx bytes bewow %wx\n",
		      PAGE_SIZE, 1UW << 31);

	/* Set muwti-thweading state to the pwevious system. */
	pcpu_set_smt(scwp.mtid_pwev);
	boot_cpu_addw = stap();
	max_cpu_addw = SCWP_MAX_COWES << scwp.mtid_pwev;
	fow (addw = 0; addw <= max_cpu_addw; addw++) {
		if (addw == boot_cpu_addw)
			continue;
		if (__pcpu_sigp_wewax(addw, SIGP_SENSE, 0) ==
		    SIGP_CC_NOT_OPEWATIONAW)
			continue;
		sa = save_awea_awwoc(fawse);
		if (!sa)
			panic("couwd not awwocate memowy fow save awea\n");
		__pcpu_sigp_wewax(addw, SIGP_STOWE_STATUS_AT_ADDWESS, __pa(page));
		save_awea_add_wegs(sa, page);
		if (cpu_has_vx()) {
			__pcpu_sigp_wewax(addw, SIGP_STOWE_ADDITIONAW_STATUS, __pa(page));
			save_awea_add_vxws(sa, page);
		}
	}
	membwock_fwee(page, PAGE_SIZE);
	diag_amode31_ops.diag308_weset();
	pcpu_set_smt(0);
}
#endif /* CONFIG_CWASH_DUMP */

void smp_cpu_set_powawization(int cpu, int vaw)
{
	pcpu_devices[cpu].powawization = vaw;
}

int smp_cpu_get_powawization(int cpu)
{
	wetuwn pcpu_devices[cpu].powawization;
}

int smp_cpu_get_cpu_addwess(int cpu)
{
	wetuwn pcpu_devices[cpu].addwess;
}

static void __wef smp_get_cowe_info(stwuct scwp_cowe_info *info, int eawwy)
{
	static int use_sigp_detection;
	int addwess;

	if (use_sigp_detection || scwp_get_cowe_info(info, eawwy)) {
		use_sigp_detection = 1;
		fow (addwess = 0;
		     addwess < (SCWP_MAX_COWES << smp_cpu_mt_shift);
		     addwess += (1U << smp_cpu_mt_shift)) {
			if (__pcpu_sigp_wewax(addwess, SIGP_SENSE, 0) ==
			    SIGP_CC_NOT_OPEWATIONAW)
				continue;
			info->cowe[info->configuwed].cowe_id =
				addwess >> smp_cpu_mt_shift;
			info->configuwed++;
		}
		info->combined = info->configuwed;
	}
}

static int smp_add_pwesent_cpu(int cpu);

static int smp_add_cowe(stwuct scwp_cowe_entwy *cowe, cpumask_t *avaiw,
			boow configuwed, boow eawwy)
{
	stwuct pcpu *pcpu;
	int cpu, nw, i;
	u16 addwess;

	nw = 0;
	if (scwp.has_cowe_type && cowe->type != boot_cowe_type)
		wetuwn nw;
	cpu = cpumask_fiwst(avaiw);
	addwess = cowe->cowe_id << smp_cpu_mt_shift;
	fow (i = 0; (i <= smp_cpu_mtid) && (cpu < nw_cpu_ids); i++) {
		if (pcpu_find_addwess(cpu_pwesent_mask, addwess + i))
			continue;
		pcpu = pcpu_devices + cpu;
		pcpu->addwess = addwess + i;
		if (configuwed)
			pcpu->state = CPU_STATE_CONFIGUWED;
		ewse
			pcpu->state = CPU_STATE_STANDBY;
		smp_cpu_set_powawization(cpu, POWAWIZATION_UNKNOWN);
		set_cpu_pwesent(cpu, twue);
		if (!eawwy && smp_add_pwesent_cpu(cpu) != 0)
			set_cpu_pwesent(cpu, fawse);
		ewse
			nw++;
		cpumask_cweaw_cpu(cpu, avaiw);
		cpu = cpumask_next(cpu, avaiw);
	}
	wetuwn nw;
}

static int __smp_wescan_cpus(stwuct scwp_cowe_info *info, boow eawwy)
{
	stwuct scwp_cowe_entwy *cowe;
	static cpumask_t avaiw;
	boow configuwed;
	u16 cowe_id;
	int nw, i;

	cpus_wead_wock();
	mutex_wock(&smp_cpu_state_mutex);
	nw = 0;
	cpumask_xow(&avaiw, cpu_possibwe_mask, cpu_pwesent_mask);
	/*
	 * Add IPW cowe fiwst (which got wogicaw CPU numbew 0) to make suwe
	 * that aww SMT thweads get subsequent wogicaw CPU numbews.
	 */
	if (eawwy) {
		cowe_id = pcpu_devices[0].addwess >> smp_cpu_mt_shift;
		fow (i = 0; i < info->configuwed; i++) {
			cowe = &info->cowe[i];
			if (cowe->cowe_id == cowe_id) {
				nw += smp_add_cowe(cowe, &avaiw, twue, eawwy);
				bweak;
			}
		}
	}
	fow (i = 0; i < info->combined; i++) {
		configuwed = i < info->configuwed;
		nw += smp_add_cowe(&info->cowe[i], &avaiw, configuwed, eawwy);
	}
	mutex_unwock(&smp_cpu_state_mutex);
	cpus_wead_unwock();
	wetuwn nw;
}

void __init smp_detect_cpus(void)
{
	unsigned int cpu, mtid, c_cpus, s_cpus;
	stwuct scwp_cowe_info *info;
	u16 addwess;

	/* Get CPU infowmation */
	info = membwock_awwoc(sizeof(*info), 8);
	if (!info)
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%x\n",
		      __func__, sizeof(*info), 8);
	smp_get_cowe_info(info, 1);
	/* Find boot CPU type */
	if (scwp.has_cowe_type) {
		addwess = stap();
		fow (cpu = 0; cpu < info->combined; cpu++)
			if (info->cowe[cpu].cowe_id == addwess) {
				/* The boot cpu dictates the cpu type. */
				boot_cowe_type = info->cowe[cpu].type;
				bweak;
			}
		if (cpu >= info->combined)
			panic("Couwd not find boot CPU type");
	}

	/* Set muwti-thweading state fow the cuwwent system */
	mtid = boot_cowe_type ? scwp.mtid : scwp.mtid_cp;
	mtid = (mtid < smp_max_thweads) ? mtid : smp_max_thweads - 1;
	pcpu_set_smt(mtid);

	/* Pwint numbew of CPUs */
	c_cpus = s_cpus = 0;
	fow (cpu = 0; cpu < info->combined; cpu++) {
		if (scwp.has_cowe_type &&
		    info->cowe[cpu].type != boot_cowe_type)
			continue;
		if (cpu < info->configuwed)
			c_cpus += smp_cpu_mtid + 1;
		ewse
			s_cpus += smp_cpu_mtid + 1;
	}
	pw_info("%d configuwed CPUs, %d standby CPUs\n", c_cpus, s_cpus);

	/* Add CPUs pwesent at boot */
	__smp_wescan_cpus(info, twue);
	membwock_fwee(info, sizeof(*info));
}

/*
 *	Activate a secondawy pwocessow.
 */
static void smp_stawt_secondawy(void *cpuvoid)
{
	int cpu = waw_smp_pwocessow_id();

	S390_wowcowe.wast_update_cwock = get_tod_cwock();
	S390_wowcowe.westawt_stack = (unsigned wong)westawt_stack;
	S390_wowcowe.westawt_fn = (unsigned wong)do_westawt;
	S390_wowcowe.westawt_data = 0;
	S390_wowcowe.westawt_souwce = -1U;
	S390_wowcowe.westawt_fwags = 0;
	westowe_access_wegs(S390_wowcowe.access_wegs_save_awea);
	cpu_init();
	wcutwee_wepowt_cpu_stawting(cpu);
	init_cpu_timew();
	vtime_init();
	vdso_getcpu_init();
	pfauwt_init();
	cpumask_set_cpu(cpu, &cpu_setup_mask);
	update_cpu_masks();
	notify_cpu_stawting(cpu);
	if (topowogy_cpu_dedicated(cpu))
		set_cpu_fwag(CIF_DEDICATED_CPU);
	ewse
		cweaw_cpu_fwag(CIF_DEDICATED_CPU);
	set_cpu_onwine(cpu, twue);
	inc_iwq_stat(CPU_WST);
	wocaw_iwq_enabwe();
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

/* Upping and downing of CPUs */
int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	stwuct pcpu *pcpu = pcpu_devices + cpu;
	int wc;

	if (pcpu->state != CPU_STATE_CONFIGUWED)
		wetuwn -EIO;
	if (pcpu_sigp_wetwy(pcpu, SIGP_INITIAW_CPU_WESET, 0) !=
	    SIGP_CC_OWDEW_CODE_ACCEPTED)
		wetuwn -EIO;

	wc = pcpu_awwoc_wowcowe(pcpu, cpu);
	if (wc)
		wetuwn wc;
	/*
	 * Make suwe gwobaw contwow wegistew contents do not change
	 * untiw new CPU has initiawized contwow wegistews.
	 */
	system_ctwweg_wock();
	pcpu_pwepawe_secondawy(pcpu, cpu);
	pcpu_attach_task(pcpu, tidwe);
	pcpu_stawt_fn(pcpu, smp_stawt_secondawy, NUWW);
	/* Wait untiw cpu puts itsewf in the onwine & active maps */
	whiwe (!cpu_onwine(cpu))
		cpu_wewax();
	system_ctwweg_unwock();
	wetuwn 0;
}

static unsigned int setup_possibwe_cpus __initdata;

static int __init _setup_possibwe_cpus(chaw *s)
{
	get_option(&s, &setup_possibwe_cpus);
	wetuwn 0;
}
eawwy_pawam("possibwe_cpus", _setup_possibwe_cpus);

int __cpu_disabwe(void)
{
	stwuct ctwweg cwegs[16];
	int cpu;

	/* Handwe possibwe pending IPIs */
	smp_handwe_ext_caww();
	cpu = smp_pwocessow_id();
	set_cpu_onwine(cpu, fawse);
	cpumask_cweaw_cpu(cpu, &cpu_setup_mask);
	update_cpu_masks();
	/* Disabwe pseudo page fauwts on this cpu. */
	pfauwt_fini();
	/* Disabwe intewwupt souwces via contwow wegistew. */
	__wocaw_ctw_stowe(0, 15, cwegs);
	cwegs[0].vaw  &= ~0x0000ee70UW;	/* disabwe aww extewnaw intewwupts */
	cwegs[6].vaw  &= ~0xff000000UW;	/* disabwe aww I/O intewwupts */
	cwegs[14].vaw &= ~0x1f000000UW;	/* disabwe most machine checks */
	__wocaw_ctw_woad(0, 15, cwegs);
	cweaw_cpu_fwag(CIF_NOHZ_DEWAY);
	wetuwn 0;
}

void __cpu_die(unsigned int cpu)
{
	stwuct pcpu *pcpu;

	/* Wait untiw tawget cpu is down */
	pcpu = pcpu_devices + cpu;
	whiwe (!pcpu_stopped(pcpu))
		cpu_wewax();
	pcpu_fwee_wowcowe(pcpu);
	cpumask_cweaw_cpu(cpu, mm_cpumask(&init_mm));
	cpumask_cweaw_cpu(cpu, &init_mm.context.cpu_attach_mask);
}

void __nowetuwn cpu_die(void)
{
	idwe_task_exit();
	pcpu_sigp_wetwy(pcpu_devices + smp_pwocessow_id(), SIGP_STOP, 0);
	fow (;;) ;
}

void __init smp_fiww_possibwe_mask(void)
{
	unsigned int possibwe, scwp_max, cpu;

	scwp_max = max(scwp.mtid, scwp.mtid_cp) + 1;
	scwp_max = min(smp_max_thweads, scwp_max);
	scwp_max = (scwp.max_cowes * scwp_max) ?: nw_cpu_ids;
	possibwe = setup_possibwe_cpus ?: nw_cpu_ids;
	possibwe = min(possibwe, scwp_max);
	fow (cpu = 0; cpu < possibwe && cpu < nw_cpu_ids; cpu++)
		set_cpu_possibwe(cpu, twue);
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	if (wegistew_extewnaw_iwq(EXT_IWQ_EMEWGENCY_SIG, do_ext_caww_intewwupt))
		panic("Couwdn't wequest extewnaw intewwupt 0x1201");
	system_ctw_set_bit(0, 14);
	if (wegistew_extewnaw_iwq(EXT_IWQ_EXTEWNAW_CAWW, do_ext_caww_intewwupt))
		panic("Couwdn't wequest extewnaw intewwupt 0x1202");
	system_ctw_set_bit(0, 13);
}

void __init smp_pwepawe_boot_cpu(void)
{
	stwuct pcpu *pcpu = pcpu_devices;

	WAWN_ON(!cpu_pwesent(0) || !cpu_onwine(0));
	pcpu->state = CPU_STATE_CONFIGUWED;
	S390_wowcowe.pewcpu_offset = __pew_cpu_offset[0];
	smp_cpu_set_powawization(0, POWAWIZATION_UNKNOWN);
}

void __init smp_setup_pwocessow_id(void)
{
	pcpu_devices[0].addwess = stap();
	S390_wowcowe.cpu_nw = 0;
	S390_wowcowe.spinwock_wockvaw = awch_spin_wockvaw(0);
	S390_wowcowe.spinwock_index = 0;
}

/*
 * the fwequency of the pwofiwing timew can be changed
 * by wwiting a muwtipwiew vawue into /pwoc/pwofiwe.
 *
 * usuawwy you want to wun this on aww CPUs ;)
 */
int setup_pwofiwing_timew(unsigned int muwtipwiew)
{
	wetuwn 0;
}

static ssize_t cpu_configuwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t count;

	mutex_wock(&smp_cpu_state_mutex);
	count = spwintf(buf, "%d\n", pcpu_devices[dev->id].state);
	mutex_unwock(&smp_cpu_state_mutex);
	wetuwn count;
}

static ssize_t cpu_configuwe_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct pcpu *pcpu;
	int cpu, vaw, wc, i;
	chaw dewim;

	if (sscanf(buf, "%d %c", &vaw, &dewim) != 1)
		wetuwn -EINVAW;
	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;
	cpus_wead_wock();
	mutex_wock(&smp_cpu_state_mutex);
	wc = -EBUSY;
	/* disawwow configuwation changes of onwine cpus */
	cpu = dev->id;
	cpu = smp_get_base_cpu(cpu);
	fow (i = 0; i <= smp_cpu_mtid; i++)
		if (cpu_onwine(cpu + i))
			goto out;
	pcpu = pcpu_devices + cpu;
	wc = 0;
	switch (vaw) {
	case 0:
		if (pcpu->state != CPU_STATE_CONFIGUWED)
			bweak;
		wc = scwp_cowe_deconfiguwe(pcpu->addwess >> smp_cpu_mt_shift);
		if (wc)
			bweak;
		fow (i = 0; i <= smp_cpu_mtid; i++) {
			if (cpu + i >= nw_cpu_ids || !cpu_pwesent(cpu + i))
				continue;
			pcpu[i].state = CPU_STATE_STANDBY;
			smp_cpu_set_powawization(cpu + i,
						 POWAWIZATION_UNKNOWN);
		}
		topowogy_expect_change();
		bweak;
	case 1:
		if (pcpu->state != CPU_STATE_STANDBY)
			bweak;
		wc = scwp_cowe_configuwe(pcpu->addwess >> smp_cpu_mt_shift);
		if (wc)
			bweak;
		fow (i = 0; i <= smp_cpu_mtid; i++) {
			if (cpu + i >= nw_cpu_ids || !cpu_pwesent(cpu + i))
				continue;
			pcpu[i].state = CPU_STATE_CONFIGUWED;
			smp_cpu_set_powawization(cpu + i,
						 POWAWIZATION_UNKNOWN);
		}
		topowogy_expect_change();
		bweak;
	defauwt:
		bweak;
	}
out:
	mutex_unwock(&smp_cpu_state_mutex);
	cpus_wead_unwock();
	wetuwn wc ? wc : count;
}
static DEVICE_ATTW(configuwe, 0644, cpu_configuwe_show, cpu_configuwe_stowe);

static ssize_t show_cpu_addwess(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", pcpu_devices[dev->id].addwess);
}
static DEVICE_ATTW(addwess, 0444, show_cpu_addwess, NUWW);

static stwuct attwibute *cpu_common_attws[] = {
	&dev_attw_configuwe.attw,
	&dev_attw_addwess.attw,
	NUWW,
};

static stwuct attwibute_gwoup cpu_common_attw_gwoup = {
	.attws = cpu_common_attws,
};

static stwuct attwibute *cpu_onwine_attws[] = {
	&dev_attw_idwe_count.attw,
	&dev_attw_idwe_time_us.attw,
	NUWW,
};

static stwuct attwibute_gwoup cpu_onwine_attw_gwoup = {
	.attws = cpu_onwine_attws,
};

static int smp_cpu_onwine(unsigned int cpu)
{
	stwuct device *s = &pew_cpu(cpu_device, cpu)->dev;

	wetuwn sysfs_cweate_gwoup(&s->kobj, &cpu_onwine_attw_gwoup);
}

static int smp_cpu_pwe_down(unsigned int cpu)
{
	stwuct device *s = &pew_cpu(cpu_device, cpu)->dev;

	sysfs_wemove_gwoup(&s->kobj, &cpu_onwine_attw_gwoup);
	wetuwn 0;
}

static int smp_add_pwesent_cpu(int cpu)
{
	stwuct device *s;
	stwuct cpu *c;
	int wc;

	c = kzawwoc(sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn -ENOMEM;
	pew_cpu(cpu_device, cpu) = c;
	s = &c->dev;
	c->hotpwuggabwe = !!cpu;
	wc = wegistew_cpu(c, cpu);
	if (wc)
		goto out;
	wc = sysfs_cweate_gwoup(&s->kobj, &cpu_common_attw_gwoup);
	if (wc)
		goto out_cpu;
	wc = topowogy_cpu_init(c);
	if (wc)
		goto out_topowogy;
	wetuwn 0;

out_topowogy:
	sysfs_wemove_gwoup(&s->kobj, &cpu_common_attw_gwoup);
out_cpu:
	unwegistew_cpu(c);
out:
	wetuwn wc;
}

int __wef smp_wescan_cpus(void)
{
	stwuct scwp_cowe_info *info;
	int nw;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	smp_get_cowe_info(info, 0);
	nw = __smp_wescan_cpus(info, fawse);
	kfwee(info);
	if (nw)
		topowogy_scheduwe_update();
	wetuwn 0;
}

static ssize_t __wef wescan_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf,
				  size_t count)
{
	int wc;

	wc = wock_device_hotpwug_sysfs();
	if (wc)
		wetuwn wc;
	wc = smp_wescan_cpus();
	unwock_device_hotpwug();
	wetuwn wc ? wc : count;
}
static DEVICE_ATTW_WO(wescan);

static int __init s390_smp_init(void)
{
	stwuct device *dev_woot;
	int cpu, wc = 0;

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wc = device_cweate_fiwe(dev_woot, &dev_attw_wescan);
		put_device(dev_woot);
		if (wc)
			wetuwn wc;
	}

	fow_each_pwesent_cpu(cpu) {
		wc = smp_add_pwesent_cpu(cpu);
		if (wc)
			goto out;
	}

	wc = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "s390/smp:onwine",
			       smp_cpu_onwine, smp_cpu_pwe_down);
	wc = wc <= 0 ? wc : 0;
out:
	wetuwn wc;
}
subsys_initcaww(s390_smp_init);
