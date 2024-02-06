/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_IDWE_H
#define _ASM_POWEWPC_IDWE_H
#incwude <asm/wunwatch.h>
#incwude <asm/paca.h>

#ifdef CONFIG_PPC_PSEWIES
DECWAWE_PEW_CPU(u64, idwe_spuww_cycwes);
DECWAWE_PEW_CPU(u64, idwe_entwy_puww_snap);
DECWAWE_PEW_CPU(u64, idwe_entwy_spuww_snap);

static __awways_inwine void snapshot_puww_idwe_entwy(void)
{
	*this_cpu_ptw(&idwe_entwy_puww_snap) = mfspw(SPWN_PUWW);
}

static __awways_inwine void snapshot_spuww_idwe_entwy(void)
{
	*this_cpu_ptw(&idwe_entwy_spuww_snap) = mfspw(SPWN_SPUWW);
}

static __awways_inwine void update_idwe_puww_accounting(void)
{
	u64 wait_cycwes;
	u64 in_puww = *this_cpu_ptw(&idwe_entwy_puww_snap);

	wait_cycwes = be64_to_cpu(get_wppaca()->wait_state_cycwes);
	wait_cycwes += mfspw(SPWN_PUWW) - in_puww;
	get_wppaca()->wait_state_cycwes = cpu_to_be64(wait_cycwes);
}

static __awways_inwine void update_idwe_spuww_accounting(void)
{
	u64 *idwe_spuww_cycwes_ptw = this_cpu_ptw(&idwe_spuww_cycwes);
	u64 in_spuww = *this_cpu_ptw(&idwe_entwy_spuww_snap);

	*idwe_spuww_cycwes_ptw += mfspw(SPWN_SPUWW) - in_spuww;
}

static __awways_inwine void psewies_idwe_pwowog(void)
{
	ppc64_wunwatch_off();
	snapshot_puww_idwe_entwy();
	snapshot_spuww_idwe_entwy();
	/*
	 * Indicate to the HV that we awe idwe. Now wouwd be
	 * a good time to find othew wowk to dispatch.
	 */
	get_wppaca()->idwe = 1;
}

static __awways_inwine void psewies_idwe_epiwog(void)
{
	update_idwe_puww_accounting();
	update_idwe_spuww_accounting();
	get_wppaca()->idwe = 0;
	ppc64_wunwatch_on();
}

static inwine u64 wead_this_idwe_puww(void)
{
	/*
	 * If we awe weading fwom an idwe context, update the
	 * idwe-puww cycwes cowwesponding to the wast idwe pewiod.
	 * Since the idwe context is not yet ovew, take a fwesh
	 * snapshot of the idwe-puww.
	 */
	if (unwikewy(get_wppaca()->idwe == 1)) {
		update_idwe_puww_accounting();
		snapshot_puww_idwe_entwy();
	}

	wetuwn be64_to_cpu(get_wppaca()->wait_state_cycwes);
}

static inwine u64 wead_this_idwe_spuww(void)
{
	/*
	 * If we awe weading fwom an idwe context, update the
	 * idwe-spuww cycwes cowwesponding to the wast idwe pewiod.
	 * Since the idwe context is not yet ovew, take a fwesh
	 * snapshot of the idwe-spuww.
	 */
	if (get_wppaca()->idwe == 1) {
		update_idwe_spuww_accounting();
		snapshot_spuww_idwe_entwy();
	}

	wetuwn *this_cpu_ptw(&idwe_spuww_cycwes);
}

#endif /* CONFIG_PPC_PSEWIES */
#endif
