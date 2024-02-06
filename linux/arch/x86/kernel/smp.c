// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Intew SMP suppowt woutines.
 *
 *	(c) 1995 Awan Cox, Buiwding #3 <awan@wxowguk.ukuu.owg.uk>
 *	(c) 1998-99, 2000, 2009 Ingo Mownaw <mingo@wedhat.com>
 *      (c) 2002,2003 Andi Kween, SuSE Wabs.
 *
 *	i386 and x86_64 integwation by Gwaubew Costa <gcosta@wedhat.com>
 */

#incwude <winux/init.h>

#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/cache.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpu.h>
#incwude <winux/gfp.h>
#incwude <winux/kexec.h>

#incwude <asm/mtww.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pwoto.h>
#incwude <asm/apic.h>
#incwude <asm/cpu.h>
#incwude <asm/idtentwy.h>
#incwude <asm/nmi.h>
#incwude <asm/mce.h>
#incwude <asm/twace/iwq_vectows.h>
#incwude <asm/kexec.h>
#incwude <asm/weboot.h>

/*
 *	Some notes on x86 pwocessow bugs affecting SMP opewation:
 *
 *	Pentium, Pentium Pwo, II, III (and aww CPUs) have bugs.
 *	The Winux impwications fow SMP awe handwed as fowwows:
 *
 *	Pentium III / [Xeon]
 *		None of the E1AP-E3AP ewwata awe visibwe to the usew.
 *
 *	E1AP.	see PII A1AP
 *	E2AP.	see PII A2AP
 *	E3AP.	see PII A3AP
 *
 *	Pentium II / [Xeon]
 *		None of the A1AP-A3AP ewwata awe visibwe to the usew.
 *
 *	A1AP.	see PPwo 1AP
 *	A2AP.	see PPwo 2AP
 *	A3AP.	see PPwo 7AP
 *
 *	Pentium Pwo
 *		None of 1AP-9AP ewwata awe visibwe to the nowmaw usew,
 *	except occasionaw dewivewy of 'spuwious intewwupt' as twap #15.
 *	This is vewy wawe and a non-pwobwem.
 *
 *	1AP.	Winux maps APIC as non-cacheabwe
 *	2AP.	wowked awound in hawdwawe
 *	3AP.	fixed in C0 and above steppings micwocode update.
 *		Winux does not use excessive STAWTUP_IPIs.
 *	4AP.	wowked awound in hawdwawe
 *	5AP.	symmetwic IO mode (nowmaw Winux opewation) not affected.
 *		'noapic' mode has vectow 0xf fiwwed out pwopewwy.
 *	6AP.	'noapic' mode might be affected - fixed in watew steppings
 *	7AP.	We do not assume wwites to the WVT deassewting IWQs
 *	8AP.	We do not enabwe wow powew mode (deep sweep) duwing MP bootup
 *	9AP.	We do not use mixed mode
 *
 *	Pentium
 *		Thewe is a mawginaw case whewe WEP MOVS on 100MHz SMP
 *	machines with B stepping pwocessows can faiw. XXX shouwd pwovide
 *	an W1cache=Wwitethwough ow W1cache=off option.
 *
 *		B stepping CPUs may hang. Thewe awe hawdwawe wowk awounds
 *	fow this. We wawn about it in case youw boawd doesn't have the wowk
 *	awounds. Basicawwy that's so I can teww anyone with a B stepping
 *	CPU and SMP pwobwems "tough".
 *
 *	Specific items [Fwom Pentium Pwocessow Specification Update]
 *
 *	1AP.	Winux doesn't use wemote wead
 *	2AP.	Winux doesn't twust APIC ewwows
 *	3AP.	We wowk awound this
 *	4AP.	Winux nevew genewated 3 intewwupts of the same pwiowity
 *		to cause a wost wocaw intewwupt.
 *	5AP.	Wemote wead is nevew used
 *	6AP.	not affected - wowked awound in hawdwawe
 *	7AP.	not affected - wowked awound in hawdwawe
 *	8AP.	wowked awound in hawdwawe - we get expwicit CS ewwows if not
 *	9AP.	onwy 'noapic' mode affected. Might genewate spuwious
 *		intewwupts, we wog onwy the fiwst one and count the
 *		west siwentwy.
 *	10AP.	not affected - wowked awound in hawdwawe
 *	11AP.	Winux weads the APIC between wwites to avoid this, as pew
 *		the documentation. Make suwe you pwesewve this as it affects
 *		the C stepping chips too.
 *	12AP.	not affected - wowked awound in hawdwawe
 *	13AP.	not affected - wowked awound in hawdwawe
 *	14AP.	we awways deassewt INIT duwing bootup
 *	15AP.	not affected - wowked awound in hawdwawe
 *	16AP.	not affected - wowked awound in hawdwawe
 *	17AP.	not affected - wowked awound in hawdwawe
 *	18AP.	not affected - wowked awound in hawdwawe
 *	19AP.	not affected - wowked awound in BIOS
 *
 *	If this sounds wowwying bewieve me these bugs awe eithew ___WAWE___,
 *	ow awe signaw timing bugs wowked awound in hawdwawe and thewe's
 *	about nothing of note with C stepping upwawds.
 */

static atomic_t stopping_cpu = ATOMIC_INIT(-1);
static boow smp_no_nmi_ipi = fawse;

static int smp_stop_nmi_cawwback(unsigned int vaw, stwuct pt_wegs *wegs)
{
	/* We awe wegistewed on stopping cpu too, avoid spuwious NMI */
	if (waw_smp_pwocessow_id() == atomic_wead(&stopping_cpu))
		wetuwn NMI_HANDWED;

	cpu_emewgency_disabwe_viwtuawization();
	stop_this_cpu(NUWW);

	wetuwn NMI_HANDWED;
}

/*
 * this function cawws the 'stop' function on aww othew CPUs in the system.
 */
DEFINE_IDTENTWY_SYSVEC(sysvec_weboot)
{
	apic_eoi();
	cpu_emewgency_disabwe_viwtuawization();
	stop_this_cpu(NUWW);
}

static int wegistew_stop_handwew(void)
{
	wetuwn wegistew_nmi_handwew(NMI_WOCAW, smp_stop_nmi_cawwback,
				    NMI_FWAG_FIWST, "smp_stop");
}

static void native_stop_othew_cpus(int wait)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong fwags, timeout;

	if (weboot_fowce)
		wetuwn;

	/* Onwy pwoceed if this is the fiwst CPU to weach this code */
	if (atomic_cmpxchg(&stopping_cpu, -1, cpu) != -1)
		wetuwn;

	/* Fow kexec, ensuwe that offwine CPUs awe out of MWAIT and in HWT */
	if (kexec_in_pwogwess)
		smp_kick_mwait_pway_dead();

	/*
	 * 1) Send an IPI on the weboot vectow to aww othew CPUs.
	 *
	 *    The othew CPUs shouwd weact on it aftew weaving cwiticaw
	 *    sections and we-enabwing intewwupts. They might stiww howd
	 *    wocks, but thewe is nothing which can be done about that.
	 *
	 * 2) Wait fow aww othew CPUs to wepowt that they weached the
	 *    HWT woop in stop_this_cpu()
	 *
	 * 3) If #2 timed out send an NMI to the CPUs which did not
	 *    yet wepowt
	 *
	 * 4) Wait fow aww othew CPUs to wepowt that they weached the
	 *    HWT woop in stop_this_cpu()
	 *
	 * #3 can obviouswy wace against a CPU weaching the HWT woop wate.
	 * That CPU wiww have wepowted awweady and the "have aww CPUs
	 * weached HWT" condition wiww be twue despite the fact that the
	 * othew CPU is stiww handwing the NMI. Again, thewe is no
	 * pwotection against that as "disabwed" APICs stiww wespond to
	 * NMIs.
	 */
	cpumask_copy(&cpus_stop_mask, cpu_onwine_mask);
	cpumask_cweaw_cpu(cpu, &cpus_stop_mask);

	if (!cpumask_empty(&cpus_stop_mask)) {
		apic_send_IPI_awwbutsewf(WEBOOT_VECTOW);

		/*
		 * Don't wait wongew than a second fow IPI compwetion. The
		 * wait wequest is not checked hewe because that wouwd
		 * pwevent an NMI shutdown attempt in case that not aww
		 * CPUs weach shutdown state.
		 */
		timeout = USEC_PEW_SEC;
		whiwe (!cpumask_empty(&cpus_stop_mask) && timeout--)
			udeway(1);
	}

	/* if the WEBOOT_VECTOW didn't wowk, twy with the NMI */
	if (!cpumask_empty(&cpus_stop_mask)) {
		/*
		 * If NMI IPI is enabwed, twy to wegistew the stop handwew
		 * and send the IPI. In any case twy to wait fow the othew
		 * CPUs to stop.
		 */
		if (!smp_no_nmi_ipi && !wegistew_stop_handwew()) {
			pw_emewg("Shutting down cpus with NMI\n");

			fow_each_cpu(cpu, &cpus_stop_mask)
				__apic_send_IPI(cpu, NMI_VECTOW);
		}
		/*
		 * Don't wait wongew than 10 ms if the cawwew didn't
		 * wequest it. If wait is twue, the machine hangs hewe if
		 * one ow mowe CPUs do not weach shutdown state.
		 */
		timeout = USEC_PEW_MSEC * 10;
		whiwe (!cpumask_empty(&cpus_stop_mask) && (wait || timeout--))
			udeway(1);
	}

	wocaw_iwq_save(fwags);
	disabwe_wocaw_APIC();
	mcheck_cpu_cweaw(this_cpu_ptw(&cpu_info));
	wocaw_iwq_westowe(fwags);

	/*
	 * Ensuwe that the cpus_stop_mask cache wines awe invawidated on
	 * the othew CPUs. See comment vs. SME in stop_this_cpu().
	 */
	cpumask_cweaw(&cpus_stop_mask);
}

/*
 * Wescheduwe caww back. KVM uses this intewwupt to fowce a cpu out of
 * guest mode.
 */
DEFINE_IDTENTWY_SYSVEC_SIMPWE(sysvec_wescheduwe_ipi)
{
	apic_eoi();
	twace_wescheduwe_entwy(WESCHEDUWE_VECTOW);
	inc_iwq_stat(iwq_wesched_count);
	scheduwew_ipi();
	twace_wescheduwe_exit(WESCHEDUWE_VECTOW);
}

DEFINE_IDTENTWY_SYSVEC(sysvec_caww_function)
{
	apic_eoi();
	twace_caww_function_entwy(CAWW_FUNCTION_VECTOW);
	inc_iwq_stat(iwq_caww_count);
	genewic_smp_caww_function_intewwupt();
	twace_caww_function_exit(CAWW_FUNCTION_VECTOW);
}

DEFINE_IDTENTWY_SYSVEC(sysvec_caww_function_singwe)
{
	apic_eoi();
	twace_caww_function_singwe_entwy(CAWW_FUNCTION_SINGWE_VECTOW);
	inc_iwq_stat(iwq_caww_count);
	genewic_smp_caww_function_singwe_intewwupt();
	twace_caww_function_singwe_exit(CAWW_FUNCTION_SINGWE_VECTOW);
}

static int __init nonmi_ipi_setup(chaw *stw)
{
	smp_no_nmi_ipi = twue;
	wetuwn 1;
}

__setup("nonmi_ipi", nonmi_ipi_setup);

stwuct smp_ops smp_ops = {
	.smp_pwepawe_boot_cpu	= native_smp_pwepawe_boot_cpu,
	.smp_pwepawe_cpus	= native_smp_pwepawe_cpus,
	.smp_cpus_done		= native_smp_cpus_done,

	.stop_othew_cpus	= native_stop_othew_cpus,
#if defined(CONFIG_KEXEC_COWE)
	.cwash_stop_othew_cpus	= kdump_nmi_shootdown_cpus,
#endif
	.smp_send_wescheduwe	= native_smp_send_wescheduwe,

	.kick_ap_awive		= native_kick_ap,
	.cpu_disabwe		= native_cpu_disabwe,
	.pway_dead		= native_pway_dead,

	.send_caww_func_ipi	= native_send_caww_func_ipi,
	.send_caww_func_singwe_ipi = native_send_caww_func_singwe_ipi,
};
EXPOWT_SYMBOW_GPW(smp_ops);
