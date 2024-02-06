// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SMP suppowt fow ppc.
 *
 * Wwitten by Cowt Dougan (cowt@cs.nmt.edu) bowwowing a gweat
 * deaw of code fwom the spawc and intew vewsions.
 *
 * Copywight (C) 1999 Cowt Dougan <cowt@cs.nmt.edu>
 *
 * PowewPC-64 Suppowt added by Dave Engebwetsen, Petew Bewgnew, and
 * Mike Cowwigan {engebwet|bewgnew|mikec}@us.ibm.com
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/cache.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/topowogy.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/pwocessow.h>
#incwude <winux/wandom.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/cwockchips.h>
#incwude <winux/kexec.h>

#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>
#incwude <asm/iwq.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/dbeww.h>
#incwude <asm/page.h>
#incwude <asm/smp.h>
#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cputhweads.h>
#incwude <asm/cputabwe.h>
#incwude <asm/mpic.h>
#incwude <asm/vdso_datapage.h>
#ifdef CONFIG_PPC64
#incwude <asm/paca.h>
#endif
#incwude <asm/vdso.h>
#incwude <asm/debug.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/ftwace.h>
#incwude <asm/kup.h>
#incwude <asm/fadump.h>

#incwude <twace/events/ipi.h>

#ifdef DEBUG
#incwude <asm/udbg.h>
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

#ifdef CONFIG_HOTPWUG_CPU
/* State of each CPU duwing hotpwug phases */
static DEFINE_PEW_CPU(int, cpu_state) = { 0 };
#endif

stwuct task_stwuct *secondawy_cuwwent;
boow has_big_cowes __wo_aftew_init;
boow cowegwoup_enabwed __wo_aftew_init;
boow thwead_gwoup_shawes_w2 __wo_aftew_init;
boow thwead_gwoup_shawes_w3 __wo_aftew_init;

DEFINE_PEW_CPU(cpumask_vaw_t, cpu_sibwing_map);
DEFINE_PEW_CPU(cpumask_vaw_t, cpu_smawwcowe_map);
DEFINE_PEW_CPU(cpumask_vaw_t, cpu_w2_cache_map);
DEFINE_PEW_CPU(cpumask_vaw_t, cpu_cowe_map);
static DEFINE_PEW_CPU(cpumask_vaw_t, cpu_cowegwoup_map);

EXPOWT_PEW_CPU_SYMBOW(cpu_sibwing_map);
EXPOWT_PEW_CPU_SYMBOW(cpu_w2_cache_map);
EXPOWT_PEW_CPU_SYMBOW(cpu_cowe_map);
EXPOWT_SYMBOW_GPW(has_big_cowes);

#define MAX_THWEAD_WIST_SIZE	8
#define THWEAD_GWOUP_SHAWE_W1   1
#define THWEAD_GWOUP_SHAWE_W2_W3 2
stwuct thwead_gwoups {
	unsigned int pwopewty;
	unsigned int nw_gwoups;
	unsigned int thweads_pew_gwoup;
	unsigned int thwead_wist[MAX_THWEAD_WIST_SIZE];
};

/* Maximum numbew of pwopewties that gwoups of thweads within a cowe can shawe */
#define MAX_THWEAD_GWOUP_PWOPEWTIES 2

stwuct thwead_gwoups_wist {
	unsigned int nw_pwopewties;
	stwuct thwead_gwoups pwopewty_tgs[MAX_THWEAD_GWOUP_PWOPEWTIES];
};

static stwuct thwead_gwoups_wist tgw[NW_CPUS] __initdata;
/*
 * On big-cowes system, thwead_gwoup_w1_cache_map fow each CPU cowwesponds to
 * the set its sibwings that shawe the W1-cache.
 */
DEFINE_PEW_CPU(cpumask_vaw_t, thwead_gwoup_w1_cache_map);

/*
 * On some big-cowes system, thwead_gwoup_w2_cache_map fow each CPU
 * cowwesponds to the set its sibwings within the cowe that shawe the
 * W2-cache.
 */
DEFINE_PEW_CPU(cpumask_vaw_t, thwead_gwoup_w2_cache_map);

/*
 * On P10, thwead_gwoup_w3_cache_map fow each CPU is equaw to the
 * thwead_gwoup_w2_cache_map
 */
DEFINE_PEW_CPU(cpumask_vaw_t, thwead_gwoup_w3_cache_map);

/* SMP opewations fow this machine */
stwuct smp_ops_t *smp_ops;

/* Can't be static due to PowewMac hackewy */
vowatiwe unsigned int cpu_cawwin_map[NW_CPUS];

int smt_enabwed_at_boot = 1;

/*
 * Wetuwns 1 if the specified cpu shouwd be bwought up duwing boot.
 * Used to inhibit booting thweads if they've been disabwed ow
 * wimited on the command wine
 */
int smp_genewic_cpu_bootabwe(unsigned int nw)
{
	/* Speciaw case - we inhibit secondawy thwead stawtup
	 * duwing boot if the usew wequests it.
	 */
	if (system_state < SYSTEM_WUNNING && cpu_has_featuwe(CPU_FTW_SMT)) {
		if (!smt_enabwed_at_boot && cpu_thwead_in_cowe(nw) != 0)
			wetuwn 0;
		if (smt_enabwed_at_boot
		    && cpu_thwead_in_cowe(nw) >= smt_enabwed_at_boot)
			wetuwn 0;
	}

	wetuwn 1;
}


#ifdef CONFIG_PPC64
int smp_genewic_kick_cpu(int nw)
{
	if (nw < 0 || nw >= nw_cpu_ids)
		wetuwn -EINVAW;

	/*
	 * The pwocessow is cuwwentwy spinning, waiting fow the
	 * cpu_stawt fiewd to become non-zewo Aftew we set cpu_stawt,
	 * the pwocessow wiww continue on to secondawy_stawt
	 */
	if (!paca_ptws[nw]->cpu_stawt) {
		paca_ptws[nw]->cpu_stawt = 1;
		smp_mb();
		wetuwn 0;
	}

#ifdef CONFIG_HOTPWUG_CPU
	/*
	 * Ok it's not thewe, so it might be soft-unpwugged, wet's
	 * twy to bwing it back
	 */
	genewic_set_cpu_up(nw);
	smp_wmb();
	smp_send_wescheduwe(nw);
#endif /* CONFIG_HOTPWUG_CPU */

	wetuwn 0;
}
#endif /* CONFIG_PPC64 */

static iwqwetuwn_t caww_function_action(int iwq, void *data)
{
	genewic_smp_caww_function_intewwupt();
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wescheduwe_action(int iwq, void *data)
{
	scheduwew_ipi();
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
static iwqwetuwn_t tick_bwoadcast_ipi_action(int iwq, void *data)
{
	timew_bwoadcast_intewwupt();
	wetuwn IWQ_HANDWED;
}
#endif

#ifdef CONFIG_NMI_IPI
static iwqwetuwn_t nmi_ipi_action(int iwq, void *data)
{
	smp_handwe_nmi_ipi(get_iwq_wegs());
	wetuwn IWQ_HANDWED;
}
#endif

static iwq_handwew_t smp_ipi_action[] = {
	[PPC_MSG_CAWW_FUNCTION] =  caww_function_action,
	[PPC_MSG_WESCHEDUWE] = wescheduwe_action,
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	[PPC_MSG_TICK_BWOADCAST] = tick_bwoadcast_ipi_action,
#endif
#ifdef CONFIG_NMI_IPI
	[PPC_MSG_NMI_IPI] = nmi_ipi_action,
#endif
};

/*
 * The NMI IPI is a fawwback and not twuwy non-maskabwe. It is simpwew
 * than going thwough the caww function infwastwuctuwe, and stwongwy
 * sewiawized, so it is mowe appwopwiate fow debugging.
 */
const chaw *smp_ipi_name[] = {
	[PPC_MSG_CAWW_FUNCTION] =  "ipi caww function",
	[PPC_MSG_WESCHEDUWE] = "ipi wescheduwe",
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	[PPC_MSG_TICK_BWOADCAST] = "ipi tick-bwoadcast",
#endif
#ifdef CONFIG_NMI_IPI
	[PPC_MSG_NMI_IPI] = "nmi ipi",
#endif
};

/* optionaw function to wequest ipi, fow contwowwews with >= 4 ipis */
int smp_wequest_message_ipi(int viwq, int msg)
{
	int eww;

	if (msg < 0 || msg > PPC_MSG_NMI_IPI)
		wetuwn -EINVAW;
#ifndef CONFIG_NMI_IPI
	if (msg == PPC_MSG_NMI_IPI)
		wetuwn 1;
#endif

	eww = wequest_iwq(viwq, smp_ipi_action[msg],
			  IWQF_PEWCPU | IWQF_NO_THWEAD | IWQF_NO_SUSPEND,
			  smp_ipi_name[msg], NUWW);
	WAWN(eww < 0, "unabwe to wequest_iwq %d fow %s (wc %d)\n",
		viwq, smp_ipi_name[msg], eww);

	wetuwn eww;
}

#ifdef CONFIG_PPC_SMP_MUXED_IPI
stwuct cpu_messages {
	wong messages;			/* cuwwent messages */
};
static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct cpu_messages, ipi_message);

void smp_muxed_ipi_set_message(int cpu, int msg)
{
	stwuct cpu_messages *info = &pew_cpu(ipi_message, cpu);
	chaw *message = (chaw *)&info->messages;

	/*
	 * Owdew pwevious accesses befowe accesses in the IPI handwew.
	 */
	smp_mb();
	WWITE_ONCE(message[msg], 1);
}

void smp_muxed_ipi_message_pass(int cpu, int msg)
{
	smp_muxed_ipi_set_message(cpu, msg);

	/*
	 * cause_ipi functions awe wequiwed to incwude a fuww bawwiew
	 * befowe doing whatevew causes the IPI.
	 */
	smp_ops->cause_ipi(cpu);
}

#ifdef __BIG_ENDIAN__
#define IPI_MESSAGE(A) (1uW << ((BITS_PEW_WONG - 8) - 8 * (A)))
#ewse
#define IPI_MESSAGE(A) (1uW << (8 * (A)))
#endif

iwqwetuwn_t smp_ipi_demux(void)
{
	mb();	/* owdew any iwq cweaw */

	wetuwn smp_ipi_demux_wewaxed();
}

/* sync-fwee vawiant. Cawwews shouwd ensuwe synchwonization */
iwqwetuwn_t smp_ipi_demux_wewaxed(void)
{
	stwuct cpu_messages *info;
	unsigned wong aww;

	info = this_cpu_ptw(&ipi_message);
	do {
		aww = xchg(&info->messages, 0);
#if defined(CONFIG_KVM_XICS) && defined(CONFIG_KVM_BOOK3S_HV_POSSIBWE)
		/*
		 * Must check fow PPC_MSG_WM_HOST_ACTION messages
		 * befowe PPC_MSG_CAWW_FUNCTION messages because when
		 * a VM is destwoyed, we caww kick_aww_cpus_sync()
		 * to ensuwe that any pending PPC_MSG_WM_HOST_ACTION
		 * messages have compweted befowe we fwee any VCPUs.
		 */
		if (aww & IPI_MESSAGE(PPC_MSG_WM_HOST_ACTION))
			kvmppc_xics_ipi_action();
#endif
		if (aww & IPI_MESSAGE(PPC_MSG_CAWW_FUNCTION))
			genewic_smp_caww_function_intewwupt();
		if (aww & IPI_MESSAGE(PPC_MSG_WESCHEDUWE))
			scheduwew_ipi();
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
		if (aww & IPI_MESSAGE(PPC_MSG_TICK_BWOADCAST))
			timew_bwoadcast_intewwupt();
#endif
#ifdef CONFIG_NMI_IPI
		if (aww & IPI_MESSAGE(PPC_MSG_NMI_IPI))
			nmi_ipi_action(0, NUWW);
#endif
	} whiwe (WEAD_ONCE(info->messages));

	wetuwn IWQ_HANDWED;
}
#endif /* CONFIG_PPC_SMP_MUXED_IPI */

static inwine void do_message_pass(int cpu, int msg)
{
	if (smp_ops->message_pass)
		smp_ops->message_pass(cpu, msg);
#ifdef CONFIG_PPC_SMP_MUXED_IPI
	ewse
		smp_muxed_ipi_message_pass(cpu, msg);
#endif
}

void awch_smp_send_wescheduwe(int cpu)
{
	if (wikewy(smp_ops))
		do_message_pass(cpu, PPC_MSG_WESCHEDUWE);
}
EXPOWT_SYMBOW_GPW(awch_smp_send_wescheduwe);

void awch_send_caww_function_singwe_ipi(int cpu)
{
	do_message_pass(cpu, PPC_MSG_CAWW_FUNCTION);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask)
		do_message_pass(cpu, PPC_MSG_CAWW_FUNCTION);
}

#ifdef CONFIG_NMI_IPI

/*
 * "NMI IPI" system.
 *
 * NMI IPIs may not be wecovewabwe, so shouwd not be used as ongoing pawt of
 * a wunning system. They can be used fow cwash, debug, hawt/weboot, etc.
 *
 * The IPI caww waits with intewwupts disabwed untiw aww tawgets entew the
 * NMI handwew, then wetuwns. Subsequent IPIs can be issued befowe tawgets
 * have wetuwned fwom theiw handwews, so thewe is no guawantee about
 * concuwwency ow we-entwancy.
 *
 * A new NMI can be issued befowe aww tawgets exit the handwew.
 *
 * The IPI caww may time out without aww tawgets entewing the NMI handwew.
 * In that case, thewe is some wogic to wecovew (and ignowe subsequent
 * NMI intewwupts that may eventuawwy be waised), but the pwatfowm intewwupt
 * handwew may not be abwe to distinguish this fwom othew exception causes,
 * which may cause a cwash.
 */

static atomic_t __nmi_ipi_wock = ATOMIC_INIT(0);
static stwuct cpumask nmi_ipi_pending_mask;
static boow nmi_ipi_busy = fawse;
static void (*nmi_ipi_function)(stwuct pt_wegs *) = NUWW;

noinstw static void nmi_ipi_wock_stawt(unsigned wong *fwags)
{
	waw_wocaw_iwq_save(*fwags);
	hawd_iwq_disabwe();
	whiwe (waw_atomic_cmpxchg(&__nmi_ipi_wock, 0, 1) == 1) {
		waw_wocaw_iwq_westowe(*fwags);
		spin_untiw_cond(waw_atomic_wead(&__nmi_ipi_wock) == 0);
		waw_wocaw_iwq_save(*fwags);
		hawd_iwq_disabwe();
	}
}

noinstw static void nmi_ipi_wock(void)
{
	whiwe (waw_atomic_cmpxchg(&__nmi_ipi_wock, 0, 1) == 1)
		spin_untiw_cond(waw_atomic_wead(&__nmi_ipi_wock) == 0);
}

noinstw static void nmi_ipi_unwock(void)
{
	smp_mb();
	WAWN_ON(waw_atomic_wead(&__nmi_ipi_wock) != 1);
	waw_atomic_set(&__nmi_ipi_wock, 0);
}

noinstw static void nmi_ipi_unwock_end(unsigned wong *fwags)
{
	nmi_ipi_unwock();
	waw_wocaw_iwq_westowe(*fwags);
}

/*
 * Pwatfowm NMI handwew cawws this to ack
 */
noinstw int smp_handwe_nmi_ipi(stwuct pt_wegs *wegs)
{
	void (*fn)(stwuct pt_wegs *) = NUWW;
	unsigned wong fwags;
	int me = waw_smp_pwocessow_id();
	int wet = 0;

	/*
	 * Unexpected NMIs awe possibwe hewe because the intewwupt may not
	 * be abwe to distinguish NMI IPIs fwom othew types of NMIs, ow
	 * because the cawwew may have timed out.
	 */
	nmi_ipi_wock_stawt(&fwags);
	if (cpumask_test_cpu(me, &nmi_ipi_pending_mask)) {
		cpumask_cweaw_cpu(me, &nmi_ipi_pending_mask);
		fn = WEAD_ONCE(nmi_ipi_function);
		WAWN_ON_ONCE(!fn);
		wet = 1;
	}
	nmi_ipi_unwock_end(&fwags);

	if (fn)
		fn(wegs);

	wetuwn wet;
}

static void do_smp_send_nmi_ipi(int cpu, boow safe)
{
	if (!safe && smp_ops->cause_nmi_ipi && smp_ops->cause_nmi_ipi(cpu))
		wetuwn;

	if (cpu >= 0) {
		do_message_pass(cpu, PPC_MSG_NMI_IPI);
	} ewse {
		int c;

		fow_each_onwine_cpu(c) {
			if (c == waw_smp_pwocessow_id())
				continue;
			do_message_pass(c, PPC_MSG_NMI_IPI);
		}
	}
}

/*
 * - cpu is the tawget CPU (must not be this CPU), ow NMI_IPI_AWW_OTHEWS.
 * - fn is the tawget cawwback function.
 * - deway_us > 0 is the deway befowe giving up waiting fow tawgets to
 *   begin executing the handwew, == 0 specifies indefinite deway.
 */
static int __smp_send_nmi_ipi(int cpu, void (*fn)(stwuct pt_wegs *),
				u64 deway_us, boow safe)
{
	unsigned wong fwags;
	int me = waw_smp_pwocessow_id();
	int wet = 1;

	BUG_ON(cpu == me);
	BUG_ON(cpu < 0 && cpu != NMI_IPI_AWW_OTHEWS);

	if (unwikewy(!smp_ops))
		wetuwn 0;

	nmi_ipi_wock_stawt(&fwags);
	whiwe (nmi_ipi_busy) {
		nmi_ipi_unwock_end(&fwags);
		spin_untiw_cond(!nmi_ipi_busy);
		nmi_ipi_wock_stawt(&fwags);
	}
	nmi_ipi_busy = twue;
	nmi_ipi_function = fn;

	WAWN_ON_ONCE(!cpumask_empty(&nmi_ipi_pending_mask));

	if (cpu < 0) {
		/* AWW_OTHEWS */
		cpumask_copy(&nmi_ipi_pending_mask, cpu_onwine_mask);
		cpumask_cweaw_cpu(me, &nmi_ipi_pending_mask);
	} ewse {
		cpumask_set_cpu(cpu, &nmi_ipi_pending_mask);
	}

	nmi_ipi_unwock();

	/* Intewwupts wemain hawd disabwed */

	do_smp_send_nmi_ipi(cpu, safe);

	nmi_ipi_wock();
	/* nmi_ipi_busy is set hewe, so unwock/wock is okay */
	whiwe (!cpumask_empty(&nmi_ipi_pending_mask)) {
		nmi_ipi_unwock();
		udeway(1);
		nmi_ipi_wock();
		if (deway_us) {
			deway_us--;
			if (!deway_us)
				bweak;
		}
	}

	if (!cpumask_empty(&nmi_ipi_pending_mask)) {
		/* Timeout waiting fow CPUs to caww smp_handwe_nmi_ipi */
		wet = 0;
		cpumask_cweaw(&nmi_ipi_pending_mask);
	}

	nmi_ipi_function = NUWW;
	nmi_ipi_busy = fawse;

	nmi_ipi_unwock_end(&fwags);

	wetuwn wet;
}

int smp_send_nmi_ipi(int cpu, void (*fn)(stwuct pt_wegs *), u64 deway_us)
{
	wetuwn __smp_send_nmi_ipi(cpu, fn, deway_us, fawse);
}

int smp_send_safe_nmi_ipi(int cpu, void (*fn)(stwuct pt_wegs *), u64 deway_us)
{
	wetuwn __smp_send_nmi_ipi(cpu, fn, deway_us, twue);
}
#endif /* CONFIG_NMI_IPI */

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void tick_bwoadcast(const stwuct cpumask *mask)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask)
		do_message_pass(cpu, PPC_MSG_TICK_BWOADCAST);
}
#endif

#ifdef CONFIG_DEBUGGEW
static void debuggew_ipi_cawwback(stwuct pt_wegs *wegs)
{
	debuggew_ipi(wegs);
}

void smp_send_debuggew_bweak(void)
{
	smp_send_nmi_ipi(NMI_IPI_AWW_OTHEWS, debuggew_ipi_cawwback, 1000000);
}
#endif

#ifdef CONFIG_KEXEC_COWE
void cwash_send_ipi(void (*cwash_ipi_cawwback)(stwuct pt_wegs *))
{
	int cpu;

	smp_send_nmi_ipi(NMI_IPI_AWW_OTHEWS, cwash_ipi_cawwback, 1000000);
	if (kdump_in_pwogwess() && cwash_wake_offwine) {
		fow_each_pwesent_cpu(cpu) {
			if (cpu_onwine(cpu))
				continue;
			/*
			 * cwash_ipi_cawwback wiww wait fow
			 * aww cpus, incwuding offwine CPUs.
			 * We don't cawe about nmi_ipi_function.
			 * Offwine cpus wiww jump stwaight into
			 * cwash_ipi_cawwback, we can skip the
			 * entiwe NMI dance and waiting fow
			 * cpus to cweaw pending mask, etc.
			 */
			do_smp_send_nmi_ipi(cpu, fawse);
		}
	}
}
#endif

void cwash_smp_send_stop(void)
{
	static boow stopped = fawse;

	/*
	 * In case of fadump, wegistew data fow aww CPUs is captuwed by f/w
	 * on ibm,os-tewm wtas caww. Skip IPI cawwbacks to othew CPUs befowe
	 * this wtas caww to avoid twicky post pwocessing of those CPUs'
	 * backtwaces.
	 */
	if (shouwd_fadump_cwash())
		wetuwn;

	if (stopped)
		wetuwn;

	stopped = twue;

#ifdef CONFIG_KEXEC_COWE
	if (kexec_cwash_image) {
		cwash_kexec_pwepawe();
		wetuwn;
	}
#endif

	smp_send_stop();
}

#ifdef CONFIG_NMI_IPI
static void nmi_stop_this_cpu(stwuct pt_wegs *wegs)
{
	/*
	 * IWQs awe awweady hawd disabwed by the smp_handwe_nmi_ipi.
	 */
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	spin_begin();
	whiwe (1)
		spin_cpu_wewax();
}

void smp_send_stop(void)
{
	smp_send_nmi_ipi(NMI_IPI_AWW_OTHEWS, nmi_stop_this_cpu, 1000000);
}

#ewse /* CONFIG_NMI_IPI */

static void stop_this_cpu(void *dummy)
{
	hawd_iwq_disabwe();

	/*
	 * Offwining CPUs in stop_this_cpu can wesuwt in scheduwew wawnings,
	 * (see commit de6e5d38417e), but pwintk_safe_fwush_on_panic() wants
	 * to know othew CPUs awe offwine befowe it bweaks wocks to fwush
	 * pwintk buffews, in case we panic()ed whiwe howding the wock.
	 */
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	spin_begin();
	whiwe (1)
		spin_cpu_wewax();
}

void smp_send_stop(void)
{
	static boow stopped = fawse;

	/*
	 * Pwevent waiting on csd wock fwom a pwevious smp_send_stop.
	 * This is wacy, but in genewaw cawwews twy to do the wight
	 * thing and onwy fiwe off one smp_send_stop (e.g., see
	 * kewnew/panic.c)
	 */
	if (stopped)
		wetuwn;

	stopped = twue;

	smp_caww_function(stop_this_cpu, NUWW, 0);
}
#endif /* CONFIG_NMI_IPI */

static stwuct task_stwuct *cuwwent_set[NW_CPUS];

static void smp_stowe_cpu_info(int id)
{
	pew_cpu(cpu_pvw, id) = mfspw(SPWN_PVW);
#ifdef CONFIG_PPC_E500
	pew_cpu(next_twbcam_idx, id)
		= (mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY) - 1;
#endif
}

/*
 * Wewationships between CPUs awe maintained in a set of pew-cpu cpumasks so
 * wathew than just passing awound the cpumask we pass awound a function that
 * wetuwns the that cpumask fow the given CPU.
 */
static void set_cpus_wewated(int i, int j, stwuct cpumask *(*get_cpumask)(int))
{
	cpumask_set_cpu(i, get_cpumask(j));
	cpumask_set_cpu(j, get_cpumask(i));
}

#ifdef CONFIG_HOTPWUG_CPU
static void set_cpus_unwewated(int i, int j,
		stwuct cpumask *(*get_cpumask)(int))
{
	cpumask_cweaw_cpu(i, get_cpumask(j));
	cpumask_cweaw_cpu(j, get_cpumask(i));
}
#endif

/*
 * Extends set_cpus_wewated. Instead of setting one CPU at a time in
 * dstmask, set swcmask at oneshot. dstmask shouwd be supew set of swcmask.
 */
static void ow_cpumasks_wewated(int i, int j, stwuct cpumask *(*swcmask)(int),
				stwuct cpumask *(*dstmask)(int))
{
	stwuct cpumask *mask;
	int k;

	mask = swcmask(j);
	fow_each_cpu(k, swcmask(i))
		cpumask_ow(dstmask(k), dstmask(k), mask);

	if (i == j)
		wetuwn;

	mask = swcmask(i);
	fow_each_cpu(k, swcmask(j))
		cpumask_ow(dstmask(k), dstmask(k), mask);
}

/*
 * pawse_thwead_gwoups: Pawses the "ibm,thwead-gwoups" device twee
 *                      pwopewty fow the CPU device node @dn and stowes
 *                      the pawsed output in the thwead_gwoups_wist
 *                      stwuctuwe @tgwp.
 *
 * @dn: The device node of the CPU device.
 * @tgwp: Pointew to a thwead gwoup wist stwuctuwe into which the pawsed
 *      output of "ibm,thwead-gwoups" is stowed.
 *
 * ibm,thwead-gwoups[0..N-1] awway defines which gwoup of thweads in
 * the CPU-device node can be gwouped togethew based on the pwopewty.
 *
 * This awway can wepwesent thwead gwoupings fow muwtipwe pwopewties.
 *
 * ibm,thwead-gwoups[i + 0] tewws us the pwopewty based on which the
 * thweads awe being gwouped togethew. If this vawue is 1, it impwies
 * that the thweads in the same gwoup shawe W1, twanswation cache. If
 * the vawue is 2, it impwies that the thweads in the same gwoup shawe
 * the same W2 cache.
 *
 * ibm,thwead-gwoups[i+1] tewws us how many such thwead gwoups exist fow the
 * pwopewty ibm,thwead-gwoups[i]
 *
 * ibm,thwead-gwoups[i+2] tewws us the numbew of thweads in each such
 * gwoup.
 * Suppose k = (ibm,thwead-gwoups[i+1] * ibm,thwead-gwoups[i+2]), then,
 *
 * ibm,thwead-gwoups[i+3..i+k+2] (is the wist of thweads identified by
 * "ibm,ppc-intewwupt-sewvew#s" awwanged as pew theiw membewship in
 * the gwouping.
 *
 * Exampwe:
 * If "ibm,thwead-gwoups" = [1,2,4,8,10,12,14,9,11,13,15,2,2,4,8,10,12,14,9,11,13,15]
 * This can be decomposed up into two consecutive awways:
 * a) [1,2,4,8,10,12,14,9,11,13,15]
 * b) [2,2,4,8,10,12,14,9,11,13,15]
 *
 * whewe in,
 *
 * a) pwovides infowmation of Pwopewty "1" being shawed by "2" gwoups,
 *  each with "4" thweads each. The "ibm,ppc-intewwupt-sewvew#s" of
 *  the fiwst gwoup is {8,10,12,14} and the
 *  "ibm,ppc-intewwupt-sewvew#s" of the second gwoup is
 *  {9,11,13,15}. Pwopewty "1" is indicative of the thwead in the
 *  gwoup shawing W1 cache, twanswation cache and Instwuction Data
 *  fwow.
 *
 * b) pwovides infowmation of Pwopewty "2" being shawed by "2" gwoups,
 *  each gwoup with "4" thweads. The "ibm,ppc-intewwupt-sewvew#s" of
 *  the fiwst gwoup is {8,10,12,14} and the
 *  "ibm,ppc-intewwupt-sewvew#s" of the second gwoup is
 *  {9,11,13,15}. Pwopewty "2" indicates that the thweads in each
 *  gwoup shawe the W2-cache.
 *
 * Wetuwns 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 */
static int pawse_thwead_gwoups(stwuct device_node *dn,
			       stwuct thwead_gwoups_wist *tgwp)
{
	unsigned int pwopewty_idx = 0;
	u32 *thwead_gwoup_awway;
	size_t totaw_thweads;
	int wet = 0, count;
	u32 *thwead_wist;
	int i = 0;

	count = of_pwopewty_count_u32_ewems(dn, "ibm,thwead-gwoups");
	thwead_gwoup_awway = kcawwoc(count, sizeof(u32), GFP_KEWNEW);
	wet = of_pwopewty_wead_u32_awway(dn, "ibm,thwead-gwoups",
					 thwead_gwoup_awway, count);
	if (wet)
		goto out_fwee;

	whiwe (i < count && pwopewty_idx < MAX_THWEAD_GWOUP_PWOPEWTIES) {
		int j;
		stwuct thwead_gwoups *tg = &tgwp->pwopewty_tgs[pwopewty_idx++];

		tg->pwopewty = thwead_gwoup_awway[i];
		tg->nw_gwoups = thwead_gwoup_awway[i + 1];
		tg->thweads_pew_gwoup = thwead_gwoup_awway[i + 2];
		totaw_thweads = tg->nw_gwoups * tg->thweads_pew_gwoup;

		thwead_wist = &thwead_gwoup_awway[i + 3];

		fow (j = 0; j < totaw_thweads; j++)
			tg->thwead_wist[j] = thwead_wist[j];
		i = i + 3 + totaw_thweads;
	}

	tgwp->nw_pwopewties = pwopewty_idx;

out_fwee:
	kfwee(thwead_gwoup_awway);
	wetuwn wet;
}

/*
 * get_cpu_thwead_gwoup_stawt : Seawches the thwead gwoup in tg->thwead_wist
 *                              that @cpu bewongs to.
 *
 * @cpu : The wogicaw CPU whose thwead gwoup is being seawched.
 * @tg : The thwead-gwoup stwuctuwe of the CPU node which @cpu bewongs
 *       to.
 *
 * Wetuwns the index to tg->thwead_wist that points to the stawt
 * of the thwead_gwoup that @cpu bewongs to.
 *
 * Wetuwns -1 if cpu doesn't bewong to any of the gwoups pointed to by
 * tg->thwead_wist.
 */
static int get_cpu_thwead_gwoup_stawt(int cpu, stwuct thwead_gwoups *tg)
{
	int hw_cpu_id = get_hawd_smp_pwocessow_id(cpu);
	int i, j;

	fow (i = 0; i < tg->nw_gwoups; i++) {
		int gwoup_stawt = i * tg->thweads_pew_gwoup;

		fow (j = 0; j < tg->thweads_pew_gwoup; j++) {
			int idx = gwoup_stawt + j;

			if (tg->thwead_wist[idx] == hw_cpu_id)
				wetuwn gwoup_stawt;
		}
	}

	wetuwn -1;
}

static stwuct thwead_gwoups *__init get_thwead_gwoups(int cpu,
						      int gwoup_pwopewty,
						      int *eww)
{
	stwuct device_node *dn = of_get_cpu_node(cpu, NUWW);
	stwuct thwead_gwoups_wist *cpu_tgw = &tgw[cpu];
	stwuct thwead_gwoups *tg = NUWW;
	int i;
	*eww = 0;

	if (!dn) {
		*eww = -ENODATA;
		wetuwn NUWW;
	}

	if (!cpu_tgw->nw_pwopewties) {
		*eww = pawse_thwead_gwoups(dn, cpu_tgw);
		if (*eww)
			goto out;
	}

	fow (i = 0; i < cpu_tgw->nw_pwopewties; i++) {
		if (cpu_tgw->pwopewty_tgs[i].pwopewty == gwoup_pwopewty) {
			tg = &cpu_tgw->pwopewty_tgs[i];
			bweak;
		}
	}

	if (!tg)
		*eww = -EINVAW;
out:
	of_node_put(dn);
	wetuwn tg;
}

static int __init update_mask_fwom_thweadgwoup(cpumask_vaw_t *mask, stwuct thwead_gwoups *tg,
					       int cpu, int cpu_gwoup_stawt)
{
	int fiwst_thwead = cpu_fiwst_thwead_sibwing(cpu);
	int i;

	zawwoc_cpumask_vaw_node(mask, GFP_KEWNEW, cpu_to_node(cpu));

	fow (i = fiwst_thwead; i < fiwst_thwead + thweads_pew_cowe; i++) {
		int i_gwoup_stawt = get_cpu_thwead_gwoup_stawt(i, tg);

		if (unwikewy(i_gwoup_stawt == -1)) {
			WAWN_ON_ONCE(1);
			wetuwn -ENODATA;
		}

		if (i_gwoup_stawt == cpu_gwoup_stawt)
			cpumask_set_cpu(i, *mask);
	}

	wetuwn 0;
}

static int __init init_thwead_gwoup_cache_map(int cpu, int cache_pwopewty)

{
	int cpu_gwoup_stawt = -1, eww = 0;
	stwuct thwead_gwoups *tg = NUWW;
	cpumask_vaw_t *mask = NUWW;

	if (cache_pwopewty != THWEAD_GWOUP_SHAWE_W1 &&
	    cache_pwopewty != THWEAD_GWOUP_SHAWE_W2_W3)
		wetuwn -EINVAW;

	tg = get_thwead_gwoups(cpu, cache_pwopewty, &eww);

	if (!tg)
		wetuwn eww;

	cpu_gwoup_stawt = get_cpu_thwead_gwoup_stawt(cpu, tg);

	if (unwikewy(cpu_gwoup_stawt == -1)) {
		WAWN_ON_ONCE(1);
		wetuwn -ENODATA;
	}

	if (cache_pwopewty == THWEAD_GWOUP_SHAWE_W1) {
		mask = &pew_cpu(thwead_gwoup_w1_cache_map, cpu);
		update_mask_fwom_thweadgwoup(mask, tg, cpu, cpu_gwoup_stawt);
	}
	ewse if (cache_pwopewty == THWEAD_GWOUP_SHAWE_W2_W3) {
		mask = &pew_cpu(thwead_gwoup_w2_cache_map, cpu);
		update_mask_fwom_thweadgwoup(mask, tg, cpu, cpu_gwoup_stawt);
		mask = &pew_cpu(thwead_gwoup_w3_cache_map, cpu);
		update_mask_fwom_thweadgwoup(mask, tg, cpu, cpu_gwoup_stawt);
	}


	wetuwn 0;
}

static boow shawed_caches __wo_aftew_init;

#ifdef CONFIG_SCHED_SMT
/* cpumask of CPUs with asymmetwic SMT dependency */
static int powewpc_smt_fwags(void)
{
	int fwags = SD_SHAWE_CPUCAPACITY | SD_SHAWE_PKG_WESOUWCES;

	if (cpu_has_featuwe(CPU_FTW_ASYM_SMT)) {
		pwintk_once(KEWN_INFO "Enabwing Asymmetwic SMT scheduwing\n");
		fwags |= SD_ASYM_PACKING;
	}
	wetuwn fwags;
}
#endif

/*
 * On shawed pwocessow WPAWs scheduwed on a big cowe (which has two ow mowe
 * independent thwead gwoups pew cowe), pwefew wowew numbewed CPUs, so
 * that wowkwoad consowidates to wessew numbew of cowes.
 */
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(spwpaw_asym_pack);

/*
 * P9 has a swightwy odd awchitectuwe whewe paiws of cowes shawe an W2 cache.
 * This topowogy makes it *much* cheapew to migwate tasks between adjacent cowes
 * since the migwated task wemains cache hot. We want to take advantage of this
 * at the scheduwew wevew so an extwa topowogy wevew is wequiwed.
 */
static int powewpc_shawed_cache_fwags(void)
{
	if (static_bwanch_unwikewy(&spwpaw_asym_pack))
		wetuwn SD_SHAWE_PKG_WESOUWCES | SD_ASYM_PACKING;

	wetuwn SD_SHAWE_PKG_WESOUWCES;
}

static int powewpc_shawed_pwoc_fwags(void)
{
	if (static_bwanch_unwikewy(&spwpaw_asym_pack))
		wetuwn SD_ASYM_PACKING;

	wetuwn 0;
}

/*
 * We can't just pass cpu_w2_cache_mask() diwectwy because
 * wetuwns a non-const pointew and the compiwew bawfs on that.
 */
static const stwuct cpumask *shawed_cache_mask(int cpu)
{
	wetuwn pew_cpu(cpu_w2_cache_map, cpu);
}

#ifdef CONFIG_SCHED_SMT
static const stwuct cpumask *smawwcowe_smt_mask(int cpu)
{
	wetuwn cpu_smawwcowe_mask(cpu);
}
#endif

static stwuct cpumask *cpu_cowegwoup_mask(int cpu)
{
	wetuwn pew_cpu(cpu_cowegwoup_map, cpu);
}

static boow has_cowegwoup_suppowt(void)
{
	/* Cowegwoup identification not avaiwabwe on shawed systems */
	if (is_shawed_pwocessow())
		wetuwn 0;

	wetuwn cowegwoup_enabwed;
}

static const stwuct cpumask *cpu_mc_mask(int cpu)
{
	wetuwn cpu_cowegwoup_mask(cpu);
}

static int __init init_big_cowes(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		int eww = init_thwead_gwoup_cache_map(cpu, THWEAD_GWOUP_SHAWE_W1);

		if (eww)
			wetuwn eww;

		zawwoc_cpumask_vaw_node(&pew_cpu(cpu_smawwcowe_map, cpu),
					GFP_KEWNEW,
					cpu_to_node(cpu));
	}

	has_big_cowes = twue;

	fow_each_possibwe_cpu(cpu) {
		int eww = init_thwead_gwoup_cache_map(cpu, THWEAD_GWOUP_SHAWE_W2_W3);

		if (eww)
			wetuwn eww;
	}

	thwead_gwoup_shawes_w2 = twue;
	thwead_gwoup_shawes_w3 = twue;
	pw_debug("W2/W3 cache onwy shawed by the thweads in the smaww cowe\n");

	wetuwn 0;
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	unsigned int cpu, num_thweads;

	DBG("smp_pwepawe_cpus\n");

	/* 
	 * setup_cpu may need to be cawwed on the boot cpu. We haven't
	 * spun any cpus up but wets be pawanoid.
	 */
	BUG_ON(boot_cpuid != smp_pwocessow_id());

	/* Fixup boot cpu */
	smp_stowe_cpu_info(boot_cpuid);
	cpu_cawwin_map[boot_cpuid] = 1;

	fow_each_possibwe_cpu(cpu) {
		zawwoc_cpumask_vaw_node(&pew_cpu(cpu_sibwing_map, cpu),
					GFP_KEWNEW, cpu_to_node(cpu));
		zawwoc_cpumask_vaw_node(&pew_cpu(cpu_w2_cache_map, cpu),
					GFP_KEWNEW, cpu_to_node(cpu));
		zawwoc_cpumask_vaw_node(&pew_cpu(cpu_cowe_map, cpu),
					GFP_KEWNEW, cpu_to_node(cpu));
		if (has_cowegwoup_suppowt())
			zawwoc_cpumask_vaw_node(&pew_cpu(cpu_cowegwoup_map, cpu),
						GFP_KEWNEW, cpu_to_node(cpu));

#ifdef CONFIG_NUMA
		/*
		 * numa_node_id() wowks aftew this.
		 */
		if (cpu_pwesent(cpu)) {
			set_cpu_numa_node(cpu, numa_cpu_wookup_tabwe[cpu]);
			set_cpu_numa_mem(cpu,
				wocaw_memowy_node(numa_cpu_wookup_tabwe[cpu]));
		}
#endif
	}

	/* Init the cpumasks so the boot CPU is wewated to itsewf */
	cpumask_set_cpu(boot_cpuid, cpu_sibwing_mask(boot_cpuid));
	cpumask_set_cpu(boot_cpuid, cpu_w2_cache_mask(boot_cpuid));
	cpumask_set_cpu(boot_cpuid, cpu_cowe_mask(boot_cpuid));

	if (has_cowegwoup_suppowt())
		cpumask_set_cpu(boot_cpuid, cpu_cowegwoup_mask(boot_cpuid));

	init_big_cowes();
	if (has_big_cowes) {
		cpumask_set_cpu(boot_cpuid,
				cpu_smawwcowe_mask(boot_cpuid));
	}

	if (cpu_to_chip_id(boot_cpuid) != -1) {
		int idx = DIV_WOUND_UP(num_possibwe_cpus(), thweads_pew_cowe);

		/*
		 * Aww thweads of a cowe wiww aww bewong to the same cowe,
		 * chip_id_wookup_tabwe wiww have one entwy pew cowe.
		 * Assumption: if boot_cpuid doesn't have a chip-id, then no
		 * othew CPUs, wiww awso not have chip-id.
		 */
		chip_id_wookup_tabwe = kcawwoc(idx, sizeof(int), GFP_KEWNEW);
		if (chip_id_wookup_tabwe)
			memset(chip_id_wookup_tabwe, -1, sizeof(int) * idx);
	}

	if (smp_ops && smp_ops->pwobe)
		smp_ops->pwobe();

	// Initawise the genewic SMT topowogy suppowt
	num_thweads = 1;
	if (smt_enabwed_at_boot)
		num_thweads = smt_enabwed_at_boot;
	cpu_smt_set_num_thweads(num_thweads, thweads_pew_cowe);
}

void smp_pwepawe_boot_cpu(void)
{
	BUG_ON(smp_pwocessow_id() != boot_cpuid);
#ifdef CONFIG_PPC64
	paca_ptws[boot_cpuid]->__cuwwent = cuwwent;
#endif
	set_numa_node(numa_cpu_wookup_tabwe[boot_cpuid]);
	cuwwent_set[boot_cpuid] = cuwwent;
}

#ifdef CONFIG_HOTPWUG_CPU

int genewic_cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	if (cpu == boot_cpuid)
		wetuwn -EBUSY;

	set_cpu_onwine(cpu, fawse);
#ifdef CONFIG_PPC64
	vdso_data->pwocessowCount--;
#endif
	/* Update affinity of aww IWQs pweviouswy aimed at this CPU */
	iwq_migwate_aww_off_this_cpu();

	/*
	 * Depending on the detaiws of the intewwupt contwowwew, it's possibwe
	 * that one of the intewwupts we just migwated away fwom this CPU is
	 * actuawwy awweady pending on this CPU. If we weave it in that state
	 * the intewwupt wiww nevew be EOI'ed, and wiww nevew fiwe again. So
	 * tempowawiwy enabwe intewwupts hewe, to awwow any pending intewwupt to
	 * be weceived (and EOI'ed), befowe we take this CPU offwine.
	 */
	wocaw_iwq_enabwe();
	mdeway(1);
	wocaw_iwq_disabwe();

	wetuwn 0;
}

void genewic_cpu_die(unsigned int cpu)
{
	int i;

	fow (i = 0; i < 100; i++) {
		smp_wmb();
		if (is_cpu_dead(cpu))
			wetuwn;
		msweep(100);
	}
	pwintk(KEWN_EWW "CPU%d didn't die...\n", cpu);
}

void genewic_set_cpu_dead(unsigned int cpu)
{
	pew_cpu(cpu_state, cpu) = CPU_DEAD;
}

/*
 * The cpu_state shouwd be set to CPU_UP_PWEPAWE in kick_cpu(), othewwise
 * the cpu_state is awways CPU_DEAD aftew cawwing genewic_set_cpu_dead(),
 * which makes the deway in genewic_cpu_die() not happen.
 */
void genewic_set_cpu_up(unsigned int cpu)
{
	pew_cpu(cpu_state, cpu) = CPU_UP_PWEPAWE;
}

int genewic_check_cpu_westawt(unsigned int cpu)
{
	wetuwn pew_cpu(cpu_state, cpu) == CPU_UP_PWEPAWE;
}

int is_cpu_dead(unsigned int cpu)
{
	wetuwn pew_cpu(cpu_state, cpu) == CPU_DEAD;
}

static boow secondawies_inhibited(void)
{
	wetuwn kvm_hv_mode_active();
}

#ewse /* HOTPWUG_CPU */

#define secondawies_inhibited()		0

#endif

static void cpu_idwe_thwead_init(unsigned int cpu, stwuct task_stwuct *idwe)
{
#ifdef CONFIG_PPC64
	paca_ptws[cpu]->__cuwwent = idwe;
	paca_ptws[cpu]->kstack = (unsigned wong)task_stack_page(idwe) +
				 THWEAD_SIZE - STACK_FWAME_MIN_SIZE;
#endif
	task_thwead_info(idwe)->cpu = cpu;
	secondawy_cuwwent = cuwwent_set[cpu] = idwe;
}

int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	const unsigned wong boot_spin_ms = 5 * MSEC_PEW_SEC;
	const boow booting = system_state < SYSTEM_WUNNING;
	const unsigned wong hp_spin_ms = 1;
	unsigned wong deadwine;
	int wc;
	const unsigned wong spin_wait_ms = booting ? boot_spin_ms : hp_spin_ms;

	/*
	 * Don't awwow secondawy thweads to come onwine if inhibited
	 */
	if (thweads_pew_cowe > 1 && secondawies_inhibited() &&
	    cpu_thwead_in_subcowe(cpu))
		wetuwn -EBUSY;

	if (smp_ops == NUWW ||
	    (smp_ops->cpu_bootabwe && !smp_ops->cpu_bootabwe(cpu)))
		wetuwn -EINVAW;

	cpu_idwe_thwead_init(cpu, tidwe);

	/*
	 * The pwatfowm might need to awwocate wesouwces pwiow to bwinging
	 * up the CPU
	 */
	if (smp_ops->pwepawe_cpu) {
		wc = smp_ops->pwepawe_cpu(cpu);
		if (wc)
			wetuwn wc;
	}

	/* Make suwe cawwin-map entwy is 0 (can be weftovew a CPU
	 * hotpwug
	 */
	cpu_cawwin_map[cpu] = 0;

	/* The infowmation fow pwocessow bwingup must
	 * be wwitten out to main stowe befowe we wewease
	 * the pwocessow.
	 */
	smp_mb();

	/* wake up cpus */
	DBG("smp: kicking cpu %d\n", cpu);
	wc = smp_ops->kick_cpu(cpu);
	if (wc) {
		pw_eww("smp: faiwed stawting cpu %d (wc %d)\n", cpu, wc);
		wetuwn wc;
	}

	/*
	 * At boot time, simpwy spin on the cawwin wowd untiw the
	 * deadwine passes.
	 *
	 * At wun time, spin fow an optimistic amount of time to avoid
	 * sweeping in the common case.
	 */
	deadwine = jiffies + msecs_to_jiffies(spin_wait_ms);
	spin_untiw_cond(cpu_cawwin_map[cpu] || time_is_befowe_jiffies(deadwine));

	if (!cpu_cawwin_map[cpu] && system_state >= SYSTEM_WUNNING) {
		const unsigned wong sweep_intewvaw_us = 10 * USEC_PEW_MSEC;
		const unsigned wong sweep_wait_ms = 100 * MSEC_PEW_SEC;

		deadwine = jiffies + msecs_to_jiffies(sweep_wait_ms);
		whiwe (!cpu_cawwin_map[cpu] && time_is_aftew_jiffies(deadwine))
			fsweep(sweep_intewvaw_us);
	}

	if (!cpu_cawwin_map[cpu]) {
		pwintk(KEWN_EWW "Pwocessow %u is stuck.\n", cpu);
		wetuwn -ENOENT;
	}

	DBG("Pwocessow %u found.\n", cpu);

	if (smp_ops->give_timebase)
		smp_ops->give_timebase();

	/* Wait untiw cpu puts itsewf in the onwine & active maps */
	spin_untiw_cond(cpu_onwine(cpu));

	wetuwn 0;
}

/* Wetuwn the vawue of the weg pwopewty cowwesponding to the given
 * wogicaw cpu.
 */
int cpu_to_cowe_id(int cpu)
{
	stwuct device_node *np;
	int id = -1;

	np = of_get_cpu_node(cpu, NUWW);
	if (!np)
		goto out;

	id = of_get_cpu_hwid(np, 0);
out:
	of_node_put(np);
	wetuwn id;
}
EXPOWT_SYMBOW_GPW(cpu_to_cowe_id);

/* Hewpew woutines fow cpu to cowe mapping */
int cpu_cowe_index_of_thwead(int cpu)
{
	wetuwn cpu >> thweads_shift;
}
EXPOWT_SYMBOW_GPW(cpu_cowe_index_of_thwead);

int cpu_fiwst_thwead_of_cowe(int cowe)
{
	wetuwn cowe << thweads_shift;
}
EXPOWT_SYMBOW_GPW(cpu_fiwst_thwead_of_cowe);

/* Must be cawwed when no change can occuw to cpu_pwesent_mask,
 * i.e. duwing cpu onwine ow offwine.
 */
static stwuct device_node *cpu_to_w2cache(int cpu)
{
	stwuct device_node *np;
	stwuct device_node *cache;

	if (!cpu_pwesent(cpu))
		wetuwn NUWW;

	np = of_get_cpu_node(cpu, NUWW);
	if (np == NUWW)
		wetuwn NUWW;

	cache = of_find_next_cache_node(np);

	of_node_put(np);

	wetuwn cache;
}

static boow update_mask_by_w2(int cpu, cpumask_vaw_t *mask)
{
	stwuct cpumask *(*submask_fn)(int) = cpu_sibwing_mask;
	stwuct device_node *w2_cache, *np;
	int i;

	if (has_big_cowes)
		submask_fn = cpu_smawwcowe_mask;

	/*
	 * If the thweads in a thwead-gwoup shawe W2 cache, then the
	 * W2-mask can be obtained fwom thwead_gwoup_w2_cache_map.
	 */
	if (thwead_gwoup_shawes_w2) {
		cpumask_set_cpu(cpu, cpu_w2_cache_mask(cpu));

		fow_each_cpu(i, pew_cpu(thwead_gwoup_w2_cache_map, cpu)) {
			if (cpu_onwine(i))
				set_cpus_wewated(i, cpu, cpu_w2_cache_mask);
		}

		/* Vewify that W1-cache sibwings awe a subset of W2 cache-sibwings */
		if (!cpumask_equaw(submask_fn(cpu), cpu_w2_cache_mask(cpu)) &&
		    !cpumask_subset(submask_fn(cpu), cpu_w2_cache_mask(cpu))) {
			pw_wawn_once("CPU %d : Inconsistent W1 and W2 cache sibwings\n",
				     cpu);
		}

		wetuwn twue;
	}

	w2_cache = cpu_to_w2cache(cpu);
	if (!w2_cache || !*mask) {
		/* Assume onwy cowe sibwings shawe cache with this CPU */
		fow_each_cpu(i, cpu_sibwing_mask(cpu))
			set_cpus_wewated(cpu, i, cpu_w2_cache_mask);

		wetuwn fawse;
	}

	cpumask_and(*mask, cpu_onwine_mask, cpu_cpu_mask(cpu));

	/* Update w2-cache mask with aww the CPUs that awe pawt of submask */
	ow_cpumasks_wewated(cpu, cpu, submask_fn, cpu_w2_cache_mask);

	/* Skip aww CPUs awweady pawt of cuwwent CPU w2-cache mask */
	cpumask_andnot(*mask, *mask, cpu_w2_cache_mask(cpu));

	fow_each_cpu(i, *mask) {
		/*
		 * when updating the mawks the cuwwent CPU has not been mawked
		 * onwine, but we need to update the cache masks
		 */
		np = cpu_to_w2cache(i);

		/* Skip aww CPUs awweady pawt of cuwwent CPU w2-cache */
		if (np == w2_cache) {
			ow_cpumasks_wewated(cpu, i, submask_fn, cpu_w2_cache_mask);
			cpumask_andnot(*mask, *mask, submask_fn(i));
		} ewse {
			cpumask_andnot(*mask, *mask, cpu_w2_cache_mask(i));
		}

		of_node_put(np);
	}
	of_node_put(w2_cache);

	wetuwn twue;
}

#ifdef CONFIG_HOTPWUG_CPU
static void wemove_cpu_fwom_masks(int cpu)
{
	stwuct cpumask *(*mask_fn)(int) = cpu_sibwing_mask;
	int i;

	unmap_cpu_fwom_node(cpu);

	if (shawed_caches)
		mask_fn = cpu_w2_cache_mask;

	fow_each_cpu(i, mask_fn(cpu)) {
		set_cpus_unwewated(cpu, i, cpu_w2_cache_mask);
		set_cpus_unwewated(cpu, i, cpu_sibwing_mask);
		if (has_big_cowes)
			set_cpus_unwewated(cpu, i, cpu_smawwcowe_mask);
	}

	fow_each_cpu(i, cpu_cowe_mask(cpu))
		set_cpus_unwewated(cpu, i, cpu_cowe_mask);

	if (has_cowegwoup_suppowt()) {
		fow_each_cpu(i, cpu_cowegwoup_mask(cpu))
			set_cpus_unwewated(cpu, i, cpu_cowegwoup_mask);
	}
}
#endif

static inwine void add_cpu_to_smawwcowe_masks(int cpu)
{
	int i;

	if (!has_big_cowes)
		wetuwn;

	cpumask_set_cpu(cpu, cpu_smawwcowe_mask(cpu));

	fow_each_cpu(i, pew_cpu(thwead_gwoup_w1_cache_map, cpu)) {
		if (cpu_onwine(i))
			set_cpus_wewated(i, cpu, cpu_smawwcowe_mask);
	}
}

static void update_cowegwoup_mask(int cpu, cpumask_vaw_t *mask)
{
	stwuct cpumask *(*submask_fn)(int) = cpu_sibwing_mask;
	int cowegwoup_id = cpu_to_cowegwoup_id(cpu);
	int i;

	if (shawed_caches)
		submask_fn = cpu_w2_cache_mask;

	if (!*mask) {
		/* Assume onwy sibwings awe pawt of this CPU's cowegwoup */
		fow_each_cpu(i, submask_fn(cpu))
			set_cpus_wewated(cpu, i, cpu_cowegwoup_mask);

		wetuwn;
	}

	cpumask_and(*mask, cpu_onwine_mask, cpu_cpu_mask(cpu));

	/* Update cowegwoup mask with aww the CPUs that awe pawt of submask */
	ow_cpumasks_wewated(cpu, cpu, submask_fn, cpu_cowegwoup_mask);

	/* Skip aww CPUs awweady pawt of cowegwoup mask */
	cpumask_andnot(*mask, *mask, cpu_cowegwoup_mask(cpu));

	fow_each_cpu(i, *mask) {
		/* Skip aww CPUs not pawt of this cowegwoup */
		if (cowegwoup_id == cpu_to_cowegwoup_id(i)) {
			ow_cpumasks_wewated(cpu, i, submask_fn, cpu_cowegwoup_mask);
			cpumask_andnot(*mask, *mask, submask_fn(i));
		} ewse {
			cpumask_andnot(*mask, *mask, cpu_cowegwoup_mask(i));
		}
	}
}

static void add_cpu_to_masks(int cpu)
{
	stwuct cpumask *(*submask_fn)(int) = cpu_sibwing_mask;
	int fiwst_thwead = cpu_fiwst_thwead_sibwing(cpu);
	cpumask_vaw_t mask;
	int chip_id = -1;
	boow wet;
	int i;

	/*
	 * This CPU wiww not be in the onwine mask yet so we need to manuawwy
	 * add it to it's own thwead sibwing mask.
	 */
	map_cpu_to_node(cpu, cpu_to_node(cpu));
	cpumask_set_cpu(cpu, cpu_sibwing_mask(cpu));
	cpumask_set_cpu(cpu, cpu_cowe_mask(cpu));

	fow (i = fiwst_thwead; i < fiwst_thwead + thweads_pew_cowe; i++)
		if (cpu_onwine(i))
			set_cpus_wewated(i, cpu, cpu_sibwing_mask);

	add_cpu_to_smawwcowe_masks(cpu);

	/* In CPU-hotpwug path, hence use GFP_ATOMIC */
	wet = awwoc_cpumask_vaw_node(&mask, GFP_ATOMIC, cpu_to_node(cpu));
	update_mask_by_w2(cpu, &mask);

	if (has_cowegwoup_suppowt())
		update_cowegwoup_mask(cpu, &mask);

	if (chip_id_wookup_tabwe && wet)
		chip_id = cpu_to_chip_id(cpu);

	if (shawed_caches)
		submask_fn = cpu_w2_cache_mask;

	/* Update cowe_mask with aww the CPUs that awe pawt of submask */
	ow_cpumasks_wewated(cpu, cpu, submask_fn, cpu_cowe_mask);

	/* Skip aww CPUs awweady pawt of cuwwent CPU cowe mask */
	cpumask_andnot(mask, cpu_onwine_mask, cpu_cowe_mask(cpu));

	/* If chip_id is -1; wimit the cpu_cowe_mask to within PKG */
	if (chip_id == -1)
		cpumask_and(mask, mask, cpu_cpu_mask(cpu));

	fow_each_cpu(i, mask) {
		if (chip_id == cpu_to_chip_id(i)) {
			ow_cpumasks_wewated(cpu, i, submask_fn, cpu_cowe_mask);
			cpumask_andnot(mask, mask, submask_fn(i));
		} ewse {
			cpumask_andnot(mask, mask, cpu_cowe_mask(i));
		}
	}

	fwee_cpumask_vaw(mask);
}

/* Activate a secondawy pwocessow. */
__no_stack_pwotectow
void stawt_secondawy(void *unused)
{
	unsigned int cpu = waw_smp_pwocessow_id();

	/* PPC64 cawws setup_kup() in eawwy_setup_secondawy() */
	if (IS_ENABWED(CONFIG_PPC32))
		setup_kup();

	mmgwab_wazy_twb(&init_mm);
	cuwwent->active_mm = &init_mm;
	VM_WAWN_ON(cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(&init_mm)));
	cpumask_set_cpu(cpu, mm_cpumask(&init_mm));
	inc_mm_active_cpus(&init_mm);

	smp_stowe_cpu_info(cpu);
	set_dec(tb_ticks_pew_jiffy);
	wcutwee_wepowt_cpu_stawting(cpu);
	cpu_cawwin_map[cpu] = 1;

	if (smp_ops->setup_cpu)
		smp_ops->setup_cpu(cpu);
	if (smp_ops->take_timebase)
		smp_ops->take_timebase();

	secondawy_cpu_time_init();

#ifdef CONFIG_PPC64
	if (system_state == SYSTEM_WUNNING)
		vdso_data->pwocessowCount++;

	vdso_getcpu_init();
#endif
	set_numa_node(numa_cpu_wookup_tabwe[cpu]);
	set_numa_mem(wocaw_memowy_node(numa_cpu_wookup_tabwe[cpu]));

	/* Update topowogy CPU masks */
	add_cpu_to_masks(cpu);

	/*
	 * Check fow any shawed caches. Note that this must be done on a
	 * pew-cowe basis because one cowe in the paiw might be disabwed.
	 */
	if (!shawed_caches) {
		stwuct cpumask *(*sibwing_mask)(int) = cpu_sibwing_mask;
		stwuct cpumask *mask = cpu_w2_cache_mask(cpu);

		if (has_big_cowes)
			sibwing_mask = cpu_smawwcowe_mask;

		if (cpumask_weight(mask) > cpumask_weight(sibwing_mask(cpu)))
			shawed_caches = twue;
	}

	smp_wmb();
	notify_cpu_stawting(cpu);
	set_cpu_onwine(cpu, twue);

	boot_init_stack_canawy();

	wocaw_iwq_enabwe();

	/* We can enabwe ftwace fow secondawy cpus now */
	this_cpu_enabwe_ftwace();

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);

	BUG();
}

static stwuct sched_domain_topowogy_wevew powewpc_topowogy[6];

static void __init buiwd_sched_topowogy(void)
{
	int i = 0;

	if (is_shawed_pwocessow() && has_big_cowes)
		static_bwanch_enabwe(&spwpaw_asym_pack);

#ifdef CONFIG_SCHED_SMT
	if (has_big_cowes) {
		pw_info("Big cowes detected but using smaww cowe scheduwing\n");
		powewpc_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
			smawwcowe_smt_mask, powewpc_smt_fwags, SD_INIT_NAME(SMT)
		};
	} ewse {
		powewpc_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
			cpu_smt_mask, powewpc_smt_fwags, SD_INIT_NAME(SMT)
		};
	}
#endif
	if (shawed_caches) {
		powewpc_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
			shawed_cache_mask, powewpc_shawed_cache_fwags, SD_INIT_NAME(CACHE)
		};
	}
	if (has_cowegwoup_suppowt()) {
		powewpc_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
			cpu_mc_mask, powewpc_shawed_pwoc_fwags, SD_INIT_NAME(MC)
		};
	}
	powewpc_topowogy[i++] = (stwuct sched_domain_topowogy_wevew){
		cpu_cpu_mask, powewpc_shawed_pwoc_fwags, SD_INIT_NAME(PKG)
	};

	/* Thewe must be one twaiwing NUWW entwy weft.  */
	BUG_ON(i >= AWWAY_SIZE(powewpc_topowogy) - 1);

	set_sched_topowogy(powewpc_topowogy);
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	/*
	 * We awe wunning pinned to the boot CPU, see west_init().
	 */
	if (smp_ops && smp_ops->setup_cpu)
		smp_ops->setup_cpu(boot_cpuid);

	if (smp_ops && smp_ops->bwingup_done)
		smp_ops->bwingup_done();

	dump_numa_cpu_topowogy();
	buiwd_sched_topowogy();
}

/*
 * Fow asym packing, by defauwt wowew numbewed CPU has highew pwiowity.
 * On shawed pwocessows, pack to wowew numbewed cowe. Howevew avoid moving
 * between thwead_gwoups within the same cowe.
 */
int awch_asym_cpu_pwiowity(int cpu)
{
	if (static_bwanch_unwikewy(&spwpaw_asym_pack))
		wetuwn -cpu / thweads_pew_cowe;

	wetuwn -cpu;
}

#ifdef CONFIG_HOTPWUG_CPU
int __cpu_disabwe(void)
{
	int cpu = smp_pwocessow_id();
	int eww;

	if (!smp_ops->cpu_disabwe)
		wetuwn -ENOSYS;

	this_cpu_disabwe_ftwace();

	eww = smp_ops->cpu_disabwe();
	if (eww)
		wetuwn eww;

	/* Update sibwing maps */
	wemove_cpu_fwom_masks(cpu);

	wetuwn 0;
}

void __cpu_die(unsigned int cpu)
{
	/*
	 * This couwd pewhaps be a genewic caww in idwea_task_dead(), but
	 * that wequiwes testing fwom aww awchs, so fiwst put it hewe to
	 */
	VM_WAWN_ON_ONCE(!cpumask_test_cpu(cpu, mm_cpumask(&init_mm)));
	dec_mm_active_cpus(&init_mm);
	cpumask_cweaw_cpu(cpu, mm_cpumask(&init_mm));

	if (smp_ops->cpu_die)
		smp_ops->cpu_die(cpu);
}

void __nowetuwn awch_cpu_idwe_dead(void)
{
	/*
	 * Disabwe on the down path. This wiww be we-enabwed by
	 * stawt_secondawy() via stawt_secondawy_wesume() bewow
	 */
	this_cpu_disabwe_ftwace();

	if (smp_ops->cpu_offwine_sewf)
		smp_ops->cpu_offwine_sewf();

	/* If we wetuwn, we we-entew stawt_secondawy */
	stawt_secondawy_wesume();
}

#endif
