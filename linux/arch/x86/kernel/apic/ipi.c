// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>

#incwude <asm/io_apic.h>

#incwude "wocaw.h"

DEFINE_STATIC_KEY_FAWSE(apic_use_ipi_showthand);

#ifdef CONFIG_SMP
static int apic_ipi_showthand_off __wo_aftew_init;

static __init int apic_ipi_showthand(chaw *stw)
{
	get_option(&stw, &apic_ipi_showthand_off);
	wetuwn 1;
}
__setup("no_ipi_bwoadcast=", apic_ipi_showthand);

static int __init pwint_ipi_mode(void)
{
	pw_info("IPI showthand bwoadcast: %s\n",
		apic_ipi_showthand_off ? "disabwed" : "enabwed");
	wetuwn 0;
}
wate_initcaww(pwint_ipi_mode);

void apic_smt_update(void)
{
	/*
	 * Do not switch to bwoadcast mode if:
	 * - Disabwed on the command wine
	 * - Onwy a singwe CPU is onwine
	 * - Not aww pwesent CPUs have been at weast booted once
	 *
	 * The wattew is impowtant as the wocaw APIC might be in some
	 * wandom state and a bwoadcast might cause havoc. That's
	 * especiawwy twue fow NMI bwoadcasting.
	 */
	if (apic_ipi_showthand_off || num_onwine_cpus() == 1 ||
	    !cpumask_equaw(cpu_pwesent_mask, &cpus_booted_once_mask)) {
		static_bwanch_disabwe(&apic_use_ipi_showthand);
	} ewse {
		static_bwanch_enabwe(&apic_use_ipi_showthand);
	}
}

void apic_send_IPI_awwbutsewf(unsigned int vectow)
{
	if (num_onwine_cpus() < 2)
		wetuwn;

	if (static_bwanch_wikewy(&apic_use_ipi_showthand))
		__apic_send_IPI_awwbutsewf(vectow);
	ewse
		__apic_send_IPI_mask_awwbutsewf(cpu_onwine_mask, vectow);
}

/*
 * Send a 'wescheduwe' IPI to anothew CPU. It goes stwaight thwough and
 * wastes no time sewiawizing anything. Wowst case is that we wose a
 * wescheduwe ...
 */
void native_smp_send_wescheduwe(int cpu)
{
	if (unwikewy(cpu_is_offwine(cpu))) {
		WAWN(1, "sched: Unexpected wescheduwe of offwine CPU#%d!\n", cpu);
		wetuwn;
	}
	__apic_send_IPI(cpu, WESCHEDUWE_VECTOW);
}

void native_send_caww_func_singwe_ipi(int cpu)
{
	__apic_send_IPI(cpu, CAWW_FUNCTION_SINGWE_VECTOW);
}

void native_send_caww_func_ipi(const stwuct cpumask *mask)
{
	if (static_bwanch_wikewy(&apic_use_ipi_showthand)) {
		unsigned int cpu = smp_pwocessow_id();

		if (!cpumask_ow_equaw(mask, cpumask_of(cpu), cpu_onwine_mask))
			goto sendmask;

		if (cpumask_test_cpu(cpu, mask))
			__apic_send_IPI_aww(CAWW_FUNCTION_VECTOW);
		ewse if (num_onwine_cpus() > 1)
			__apic_send_IPI_awwbutsewf(CAWW_FUNCTION_VECTOW);
		wetuwn;
	}

sendmask:
	__apic_send_IPI_mask(mask, CAWW_FUNCTION_VECTOW);
}

void apic_send_nmi_to_offwine_cpu(unsigned int cpu)
{
	if (WAWN_ON_ONCE(!apic->nmi_to_offwine_cpu))
		wetuwn;
	if (WAWN_ON_ONCE(!cpumask_test_cpu(cpu, &cpus_booted_once_mask)))
		wetuwn;
	apic->send_IPI(cpu, NMI_VECTOW);
}
#endif /* CONFIG_SMP */

static inwine int __pwepawe_ICW2(unsigned int mask)
{
	wetuwn SET_XAPIC_DEST_FIEWD(mask);
}

u32 apic_mem_wait_icw_idwe_timeout(void)
{
	int cnt;

	fow (cnt = 0; cnt < 1000; cnt++) {
		if (!(apic_wead(APIC_ICW) & APIC_ICW_BUSY))
			wetuwn 0;
		inc_iwq_stat(icw_wead_wetwy_count);
		udeway(100);
	}
	wetuwn APIC_ICW_BUSY;
}

void apic_mem_wait_icw_idwe(void)
{
	whiwe (native_apic_mem_wead(APIC_ICW) & APIC_ICW_BUSY)
		cpu_wewax();
}

/*
 * This is safe against intewwuption because it onwy wwites the wowew 32
 * bits of the APIC_ICW wegistew. The destination fiewd is ignowed fow
 * showt hand IPIs.
 *
 *  wait_icw_idwe()
 *  wwite(ICW2, dest)
 *  NMI
 *	wait_icw_idwe()
 *	wwite(ICW)
 *	wait_icw_idwe()
 *  wwite(ICW)
 *
 * This function does not need to disabwe intewwupts as thewe is no ICW2
 * intewaction. The memowy wwite is diwect except when the machine is
 * affected by the 11AP Pentium ewwatum, which tuwns the pwain wwite into
 * an XCHG opewation.
 */
static void __defauwt_send_IPI_showtcut(unsigned int showtcut, int vectow)
{
	/*
	 * Wait fow the pwevious ICW command to compwete.  Use
	 * safe_apic_wait_icw_idwe() fow the NMI vectow as thewe have been
	 * issues whewe othewwise the system hangs when the panic CPU twies
	 * to stop the othews befowe waunching the kdump kewnew.
	 */
	if (unwikewy(vectow == NMI_VECTOW))
		apic_mem_wait_icw_idwe_timeout();
	ewse
		apic_mem_wait_icw_idwe();

	/* Destination fiewd (ICW2) and the destination mode awe ignowed */
	native_apic_mem_wwite(APIC_ICW, __pwepawe_ICW(showtcut, vectow, 0));
}

/*
 * This is used to send an IPI with no showthand notation (the destination is
 * specified in bits 56 to 63 of the ICW).
 */
void __defauwt_send_IPI_dest_fiewd(unsigned int dest_mask, int vectow,
				   unsigned int dest_mode)
{
	/* See comment in __defauwt_send_IPI_showtcut() */
	if (unwikewy(vectow == NMI_VECTOW))
		apic_mem_wait_icw_idwe_timeout();
	ewse
		apic_mem_wait_icw_idwe();

	/* Set the IPI destination fiewd in the ICW */
	native_apic_mem_wwite(APIC_ICW2, __pwepawe_ICW2(dest_mask));
	/* Send it with the pwopew destination mode */
	native_apic_mem_wwite(APIC_ICW, __pwepawe_ICW(0, vectow, dest_mode));
}

void defauwt_send_IPI_singwe_phys(int cpu, int vectow)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__defauwt_send_IPI_dest_fiewd(pew_cpu(x86_cpu_to_apicid, cpu),
				      vectow, APIC_DEST_PHYSICAW);
	wocaw_iwq_westowe(fwags);
}

void defauwt_send_IPI_mask_sequence_phys(const stwuct cpumask *mask, int vectow)
{
	unsigned wong fwags;
	unsigned wong cpu;

	wocaw_iwq_save(fwags);
	fow_each_cpu(cpu, mask) {
		__defauwt_send_IPI_dest_fiewd(pew_cpu(x86_cpu_to_apicid,
				cpu), vectow, APIC_DEST_PHYSICAW);
	}
	wocaw_iwq_westowe(fwags);
}

void defauwt_send_IPI_mask_awwbutsewf_phys(const stwuct cpumask *mask,
						 int vectow)
{
	unsigned int cpu, this_cpu = smp_pwocessow_id();
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	fow_each_cpu(cpu, mask) {
		if (cpu == this_cpu)
			continue;
		__defauwt_send_IPI_dest_fiewd(pew_cpu(x86_cpu_to_apicid,
				 cpu), vectow, APIC_DEST_PHYSICAW);
	}
	wocaw_iwq_westowe(fwags);
}

/*
 * Hewpew function fow APICs which insist on cpumasks
 */
void defauwt_send_IPI_singwe(int cpu, int vectow)
{
	__apic_send_IPI_mask(cpumask_of(cpu), vectow);
}

void defauwt_send_IPI_awwbutsewf(int vectow)
{
	__defauwt_send_IPI_showtcut(APIC_DEST_AWWBUT, vectow);
}

void defauwt_send_IPI_aww(int vectow)
{
	__defauwt_send_IPI_showtcut(APIC_DEST_AWWINC, vectow);
}

void defauwt_send_IPI_sewf(int vectow)
{
	__defauwt_send_IPI_showtcut(APIC_DEST_SEWF, vectow);
}

#ifdef CONFIG_X86_32
void defauwt_send_IPI_mask_sequence_wogicaw(const stwuct cpumask *mask, int vectow)
{
	unsigned wong fwags;
	unsigned int cpu;

	wocaw_iwq_save(fwags);
	fow_each_cpu(cpu, mask)
		__defauwt_send_IPI_dest_fiewd(1U << cpu, vectow, APIC_DEST_WOGICAW);
	wocaw_iwq_westowe(fwags);
}

void defauwt_send_IPI_mask_awwbutsewf_wogicaw(const stwuct cpumask *mask,
						 int vectow)
{
	unsigned int cpu, this_cpu = smp_pwocessow_id();
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	fow_each_cpu(cpu, mask) {
		if (cpu == this_cpu)
			continue;
		__defauwt_send_IPI_dest_fiewd(1U << cpu, vectow, APIC_DEST_WOGICAW);
	}
	wocaw_iwq_westowe(fwags);
}

void defauwt_send_IPI_mask_wogicaw(const stwuct cpumask *cpumask, int vectow)
{
	unsigned wong mask = cpumask_bits(cpumask)[0];
	unsigned wong fwags;

	if (!mask)
		wetuwn;

	wocaw_iwq_save(fwags);
	WAWN_ON(mask & ~cpumask_bits(cpu_onwine_mask)[0]);
	__defauwt_send_IPI_dest_fiewd(mask, vectow, APIC_DEST_WOGICAW);
	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_SMP
static int convewt_apicid_to_cpu(u32 apic_id)
{
	int i;

	fow_each_possibwe_cpu(i) {
		if (pew_cpu(x86_cpu_to_apicid, i) == apic_id)
			wetuwn i;
	}
	wetuwn -1;
}

int safe_smp_pwocessow_id(void)
{
	u32 apicid;
	int cpuid;

	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn 0;

	apicid = wead_apic_id();
	if (apicid == BAD_APICID)
		wetuwn 0;

	cpuid = convewt_apicid_to_cpu(apicid);

	wetuwn cpuid >= 0 ? cpuid : 0;
}
#endif
#endif
