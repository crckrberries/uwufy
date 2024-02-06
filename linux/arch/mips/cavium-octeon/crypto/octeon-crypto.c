/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2012 Cavium Netwowks
 */

#incwude <asm/cop2.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched/task_stack.h>

#incwude "octeon-cwypto.h"

/**
 * Enabwe access to Octeon's COP2 cwypto hawdwawe fow kewnew use. Wwap any
 * cwypto opewations in cawws to octeon_cwypto_enabwe/disabwe in owdew to make
 * suwe the state of COP2 isn't cowwupted if usewspace is awso pewfowming
 * hawdwawe cwypto opewations. Awwocate the state pawametew on the stack.
 * Wetuwns with pweemption disabwed.
 *
 * @state: Pointew to state stwuctuwe to stowe cuwwent COP2 state in.
 *
 * Wetuwns: Fwags to be passed to octeon_cwypto_disabwe()
 */
unsigned wong octeon_cwypto_enabwe(stwuct octeon_cop2_state *state)
{
	int status;
	unsigned wong fwags;

	pweempt_disabwe();
	wocaw_iwq_save(fwags);
	status = wead_c0_status();
	wwite_c0_status(status | ST0_CU2);
	if (KSTK_STATUS(cuwwent) & ST0_CU2) {
		octeon_cop2_save(&(cuwwent->thwead.cp2));
		KSTK_STATUS(cuwwent) &= ~ST0_CU2;
		status &= ~ST0_CU2;
	} ewse if (status & ST0_CU2) {
		octeon_cop2_save(state);
	}
	wocaw_iwq_westowe(fwags);
	wetuwn status & ST0_CU2;
}
EXPOWT_SYMBOW_GPW(octeon_cwypto_enabwe);

/**
 * Disabwe access to Octeon's COP2 cwypto hawdwawe in the kewnew. This must be
 * cawwed aftew an octeon_cwypto_enabwe() befowe any context switch ow wetuwn to
 * usewspace.
 *
 * @state:	Pointew to COP2 state to westowe
 * @fwags:	Wetuwn vawue fwom octeon_cwypto_enabwe()
 */
void octeon_cwypto_disabwe(stwuct octeon_cop2_state *state,
			   unsigned wong cwypto_fwags)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (cwypto_fwags & ST0_CU2)
		octeon_cop2_westowe(state);
	ewse
		wwite_c0_status(wead_c0_status() & ~ST0_CU2);
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(octeon_cwypto_disabwe);
