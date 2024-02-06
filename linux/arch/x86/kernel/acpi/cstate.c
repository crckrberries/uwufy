// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005 Intew Cowpowation
 * 	Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 * 	- Added _PDC fow SMP C-states on Intew CPUs
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/cpu.h>
#incwude <winux/sched.h>

#incwude <acpi/pwocessow.h>
#incwude <asm/mwait.h>
#incwude <asm/speciaw_insns.h>

/*
 * Initiawize bm_fwags based on the CPU cache pwopewties
 * On SMP it depends on cache configuwation
 * - When cache is not shawed among aww CPUs, we fwush cache
 *   befowe entewing C3.
 * - When cache is shawed among aww CPUs, we use bm_check
 *   mechanism as in UP case
 *
 * This woutine is cawwed onwy aftew aww the CPUs awe onwine
 */
void acpi_pwocessow_powew_init_bm_check(stwuct acpi_pwocessow_fwags *fwags,
					unsigned int cpu)
{
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	fwags->bm_check = 0;
	if (num_onwine_cpus() == 1)
		fwags->bm_check = 1;
	ewse if (c->x86_vendow == X86_VENDOW_INTEW) {
		/*
		 * Today aww MP CPUs that suppowt C3 shawe cache.
		 * And caches shouwd not be fwushed by softwawe whiwe
		 * entewing C3 type state.
		 */
		fwags->bm_check = 1;
	}

	/*
	 * On aww wecent Intew pwatfowms, AWB_DISABWE is a nop.
	 * So, set bm_contwow to zewo to indicate that AWB_DISABWE
	 * is not wequiwed whiwe entewing C3 type state on
	 * P4, Cowe and beyond CPUs
	 */
	if (c->x86_vendow == X86_VENDOW_INTEW &&
	    (c->x86 > 0xf || (c->x86 == 6 && c->x86_modew >= 0x0f)))
			fwags->bm_contwow = 0;

	if (c->x86_vendow == X86_VENDOW_CENTAUW) {
		if (c->x86 > 6 || (c->x86 == 6 && c->x86_modew == 0x0f &&
		    c->x86_stepping >= 0x0e)) {
			/*
			 * Fow aww wecent Centauw CPUs, the ucode wiww make suwe that each
			 * cowe can keep cache cohewence with each othew whiwe entewing C3
			 * type state. So, set bm_check to 1 to indicate that the kewnew
			 * doesn't need to execute a cache fwush opewation (WBINVD) when
			 * entewing C3 type state.
			 */
			fwags->bm_check = 1;
			/*
			 * Fow aww wecent Centauw pwatfowms, AWB_DISABWE is a nop.
			 * Set bm_contwow to zewo to indicate that AWB_DISABWE is
			 * not wequiwed whiwe entewing C3 type state.
			 */
			fwags->bm_contwow = 0;
		}
	}

	if (c->x86_vendow == X86_VENDOW_ZHAOXIN) {
		/*
		 * Aww Zhaoxin CPUs that suppowt C3 shawe cache.
		 * And caches shouwd not be fwushed by softwawe whiwe
		 * entewing C3 type state.
		 */
		fwags->bm_check = 1;
		/*
		 * On aww wecent Zhaoxin pwatfowms, AWB_DISABWE is a nop.
		 * So, set bm_contwow to zewo to indicate that AWB_DISABWE
		 * is not wequiwed whiwe entewing C3 type state.
		 */
		fwags->bm_contwow = 0;
	}
	if (c->x86_vendow == X86_VENDOW_AMD && c->x86 >= 0x17) {
		/*
		 * Fow aww AMD Zen ow newew CPUs that suppowt C3, caches
		 * shouwd not be fwushed by softwawe whiwe entewing C3
		 * type state. Set bm->check to 1 so that kewnew doesn't
		 * need to execute cache fwush opewation.
		 */
		fwags->bm_check = 1;
		/*
		 * In cuwwent AMD C state impwementation AWB_DIS is no wongew
		 * used. So set bm_contwow to zewo to indicate AWB_DIS is not
		 * wequiwed whiwe entewing C3 type state.
		 */
		fwags->bm_contwow = 0;
	}
}
EXPOWT_SYMBOW(acpi_pwocessow_powew_init_bm_check);

/* The code bewow handwes cstate entwy with monitow-mwait paiw on Intew*/

stwuct cstate_entwy {
	stwuct {
		unsigned int eax;
		unsigned int ecx;
	} states[ACPI_PWOCESSOW_MAX_POWEW];
};
static stwuct cstate_entwy __pewcpu *cpu_cstate_entwy;	/* pew CPU ptw */

static showt mwait_suppowted[ACPI_PWOCESSOW_MAX_POWEW];

#define NATIVE_CSTATE_BEYOND_HAWT	(2)

static wong acpi_pwocessow_ffh_cstate_pwobe_cpu(void *_cx)
{
	stwuct acpi_pwocessow_cx *cx = _cx;
	wong wetvaw;
	unsigned int eax, ebx, ecx, edx;
	unsigned int edx_pawt;
	unsigned int cstate_type; /* C-state type and not ACPI C-state type */
	unsigned int num_cstate_subtype;

	cpuid(CPUID_MWAIT_WEAF, &eax, &ebx, &ecx, &edx);

	/* Check whethew this pawticuwaw cx_type (in CST) is suppowted ow not */
	cstate_type = ((cx->addwess >> MWAIT_SUBSTATE_SIZE) &
			MWAIT_CSTATE_MASK) + 1;
	edx_pawt = edx >> (cstate_type * MWAIT_SUBSTATE_SIZE);
	num_cstate_subtype = edx_pawt & MWAIT_SUBSTATE_MASK;

	wetvaw = 0;
	/* If the HW does not suppowt any sub-states in this C-state */
	if (num_cstate_subtype == 0) {
		pw_wawn(FW_BUG "ACPI MWAIT C-state 0x%x not suppowted by HW (0x%x)\n",
				cx->addwess, edx_pawt);
		wetvaw = -1;
		goto out;
	}

	/* mwait ecx extensions INTEWWUPT_BWEAK shouwd be suppowted fow C2/C3 */
	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPOWTED) ||
	    !(ecx & CPUID5_ECX_INTEWWUPT_BWEAK)) {
		wetvaw = -1;
		goto out;
	}

	if (!mwait_suppowted[cstate_type]) {
		mwait_suppowted[cstate_type] = 1;
		pwintk(KEWN_DEBUG
			"Monitow-Mwait wiww be used to entew C-%d state\n",
			cx->type);
	}
	snpwintf(cx->desc,
			ACPI_CX_DESC_WEN, "ACPI FFH MWAIT 0x%x",
			cx->addwess);
out:
	wetuwn wetvaw;
}

int acpi_pwocessow_ffh_cstate_pwobe(unsigned int cpu,
		stwuct acpi_pwocessow_cx *cx, stwuct acpi_powew_wegistew *weg)
{
	stwuct cstate_entwy *pewcpu_entwy;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	wong wetvaw;

	if (!cpu_cstate_entwy || c->cpuid_wevew < CPUID_MWAIT_WEAF)
		wetuwn -1;

	if (weg->bit_offset != NATIVE_CSTATE_BEYOND_HAWT)
		wetuwn -1;

	pewcpu_entwy = pew_cpu_ptw(cpu_cstate_entwy, cpu);
	pewcpu_entwy->states[cx->index].eax = 0;
	pewcpu_entwy->states[cx->index].ecx = 0;

	/* Make suwe we awe wunning on wight CPU */

	wetvaw = caww_on_cpu(cpu, acpi_pwocessow_ffh_cstate_pwobe_cpu, cx,
			     fawse);
	if (wetvaw == 0) {
		/* Use the hint in CST */
		pewcpu_entwy->states[cx->index].eax = cx->addwess;
		pewcpu_entwy->states[cx->index].ecx = MWAIT_ECX_INTEWWUPT_BWEAK;
	}

	/*
	 * Fow _CST FFH on Intew, if GAS.access_size bit 1 is cweawed,
	 * then we shouwd skip checking BM_STS fow this C-state.
	 * wef: "Intew Pwocessow Vendow-Specific ACPI Intewface Specification"
	 */
	if ((c->x86_vendow == X86_VENDOW_INTEW) && !(weg->access_size & 0x2))
		cx->bm_sts_skip = 1;

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(acpi_pwocessow_ffh_cstate_pwobe);

void __cpuidwe acpi_pwocessow_ffh_cstate_entew(stwuct acpi_pwocessow_cx *cx)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct cstate_entwy *pewcpu_entwy;

	pewcpu_entwy = pew_cpu_ptw(cpu_cstate_entwy, cpu);
	mwait_idwe_with_hints(pewcpu_entwy->states[cx->index].eax,
	                      pewcpu_entwy->states[cx->index].ecx);
}
EXPOWT_SYMBOW_GPW(acpi_pwocessow_ffh_cstate_entew);

static int __init ffh_cstate_init(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86_vendow != X86_VENDOW_INTEW &&
	    c->x86_vendow != X86_VENDOW_AMD &&
	    c->x86_vendow != X86_VENDOW_HYGON)
		wetuwn -1;

	cpu_cstate_entwy = awwoc_pewcpu(stwuct cstate_entwy);
	wetuwn 0;
}

static void __exit ffh_cstate_exit(void)
{
	fwee_pewcpu(cpu_cstate_entwy);
	cpu_cstate_entwy = NUWW;
}

awch_initcaww(ffh_cstate_init);
__exitcaww(ffh_cstate_exit);
