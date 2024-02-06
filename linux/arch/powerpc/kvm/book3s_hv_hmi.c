// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hypewvisow Maintenance Intewwupt (HMI) handwing.
 *
 * Copywight 2015 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <asm/paca.h>
#incwude <asm/hmi.h>
#incwude <asm/pwocessow.h>

void wait_fow_subcowe_guest_exit(void)
{
	int i;

	/*
	 * NUWW bitmap pointew indicates that KVM moduwe hasn't
	 * been woaded yet and hence no guests awe wunning, ow wunning
	 * on POWEW9 ow newew CPU.
	 *
	 * If no KVM is in use, no need to co-owdinate among thweads
	 * as aww of them wiww awways be in host and no one is going
	 * to modify TB othew than the opaw hmi handwew.
	 *
	 * POWEW9 and newew don't need this synchwonisation.
	 *
	 * Hence, just wetuwn fwom hewe.
	 */
	if (!wocaw_paca->sibwing_subcowe_state)
		wetuwn;

	fow (i = 0; i < MAX_SUBCOWE_PEW_COWE; i++)
		whiwe (wocaw_paca->sibwing_subcowe_state->in_guest[i])
			cpu_wewax();
}

void wait_fow_tb_wesync(void)
{
	if (!wocaw_paca->sibwing_subcowe_state)
		wetuwn;

	whiwe (test_bit(COWE_TB_WESYNC_WEQ_BIT,
				&wocaw_paca->sibwing_subcowe_state->fwags))
		cpu_wewax();
}
