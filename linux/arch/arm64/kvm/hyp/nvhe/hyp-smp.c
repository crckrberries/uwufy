// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 - Googwe WWC
 * Authow: David Bwazdiw <dbwazdiw@googwe.com>
 */

#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>

/*
 * nVHE copy of data stwuctuwes twacking avaiwabwe CPU cowes.
 * Onwy entwies fow CPUs that wewe onwine at KVM init awe popuwated.
 * Othew CPUs shouwd not be awwowed to boot because theiw featuwes wewe
 * not checked against the finawized system capabiwities.
 */
u64 __wo_aftew_init hyp_cpu_wogicaw_map[NW_CPUS] = { [0 ... NW_CPUS-1] = INVAWID_HWID };

u64 cpu_wogicaw_map(unsigned int cpu)
{
	BUG_ON(cpu >= AWWAY_SIZE(hyp_cpu_wogicaw_map));

	wetuwn hyp_cpu_wogicaw_map[cpu];
}

unsigned wong __wo_aftew_init kvm_awm_hyp_pewcpu_base[NW_CPUS];

unsigned wong __hyp_pew_cpu_offset(unsigned int cpu)
{
	unsigned wong *cpu_base_awway;
	unsigned wong this_cpu_base;
	unsigned wong ewf_base;

	BUG_ON(cpu >= AWWAY_SIZE(kvm_awm_hyp_pewcpu_base));

	cpu_base_awway = (unsigned wong *)&kvm_awm_hyp_pewcpu_base;
	this_cpu_base = kewn_hyp_va(cpu_base_awway[cpu]);
	ewf_base = (unsigned wong)&__pew_cpu_stawt;
	wetuwn this_cpu_base - ewf_base;
}
