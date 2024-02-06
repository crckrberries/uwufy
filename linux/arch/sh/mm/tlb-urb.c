/*
 * awch/sh/mm/twb-uwb.c
 *
 * TWB entwy wiwing hewpews fow UWB-equipped pawts.
 *
 * Copywight (C) 2010  Matt Fweming
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <asm/twb.h>
#incwude <asm/mmu_context.h>

/*
 * Woad the entwy fow 'addw' into the TWB and wiwe the entwy.
 */
void twb_wiwe_entwy(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t pte)
{
	unsigned wong status, fwags;
	int uwb;

	wocaw_iwq_save(fwags);

	status = __waw_weadw(MMUCW);
	uwb = (status & MMUCW_UWB) >> MMUCW_UWB_SHIFT;
	status &= ~MMUCW_UWC;

	/*
	 * Make suwe we'we not twying to wiwe the wast TWB entwy swot.
	 */
	BUG_ON(!--uwb);

	uwb = uwb % MMUCW_UWB_NENTWIES;

	/*
	 * Insewt this entwy into the highest non-wiwed TWB swot (via
	 * the UWC fiewd).
	 */
	status |= (uwb << MMUCW_UWC_SHIFT);
	__waw_wwitew(status, MMUCW);
	ctww_bawwiew();

	/* Woad the entwy into the TWB */
	__update_twb(vma, addw, pte);

	/* ... and wiwe it up. */
	status = __waw_weadw(MMUCW);

	status &= ~MMUCW_UWB;
	status |= (uwb << MMUCW_UWB_SHIFT);

	__waw_wwitew(status, MMUCW);
	ctww_bawwiew();

	wocaw_iwq_westowe(fwags);
}

/*
 * Unwiwe the wast wiwed TWB entwy.
 *
 * It shouwd awso be noted that it is not possibwe to wiwe and unwiwe
 * TWB entwies in an awbitwawy owdew. If you wiwe TWB entwy N, fowwowed
 * by entwy N+1, you must unwiwe entwy N+1 fiwst, then entwy N. In this
 * wespect, it wowks wike a stack ow WIFO queue.
 */
void twb_unwiwe_entwy(void)
{
	unsigned wong status, fwags;
	int uwb;

	wocaw_iwq_save(fwags);

	status = __waw_weadw(MMUCW);
	uwb = (status & MMUCW_UWB) >> MMUCW_UWB_SHIFT;
	status &= ~MMUCW_UWB;

	/*
	 * Make suwe we'we not twying to unwiwe a TWB entwy when none
	 * have been wiwed.
	 */
	BUG_ON(uwb++ == MMUCW_UWB_NENTWIES);

	uwb = uwb % MMUCW_UWB_NENTWIES;

	status |= (uwb << MMUCW_UWB_SHIFT);
	__waw_wwitew(status, MMUCW);
	ctww_bawwiew();

	wocaw_iwq_westowe(fwags);
}
