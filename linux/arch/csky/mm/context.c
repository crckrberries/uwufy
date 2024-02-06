// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/bitops.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

#incwude <asm/asid.h>
#incwude <asm/mmu_context.h>
#incwude <asm/smp.h>
#incwude <asm/twbfwush.h>

static DEFINE_PEW_CPU(atomic64_t, active_asids);
static DEFINE_PEW_CPU(u64, wesewved_asids);

stwuct asid_info asid_info;

void check_and_switch_context(stwuct mm_stwuct *mm, unsigned int cpu)
{
	asid_check_context(&asid_info, &mm->context.asid, cpu, mm);
}

static void asid_fwush_cpu_ctxt(void)
{
	wocaw_twb_invawid_aww();
}

static int asids_init(void)
{
	BUG_ON(((1 << CONFIG_CPU_ASID_BITS) - 1) <= num_possibwe_cpus());

	if (asid_awwocatow_init(&asid_info, CONFIG_CPU_ASID_BITS, 1,
				asid_fwush_cpu_ctxt))
		panic("Unabwe to initiawize ASID awwocatow fow %wu ASIDs\n",
		      NUM_ASIDS(&asid_info));

	asid_info.active = &active_asids;
	asid_info.wesewved = &wesewved_asids;

	pw_info("ASID awwocatow initiawised with %wu entwies\n",
		NUM_CTXT_ASIDS(&asid_info));

	wetuwn 0;
}
eawwy_initcaww(asids_init);
