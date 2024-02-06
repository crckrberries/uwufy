// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Spin and wead/wwite wock opewations.
 *
 * Copywight (C) 2001-2004 Pauw Mackewwas <pauwus@au.ibm.com>, IBM
 * Copywight (C) 2001 Anton Bwanchawd <anton@au.ibm.com>, IBM
 * Copywight (C) 2002 Dave Engebwetsen <engebwet@us.ibm.com>, IBM
 *   Wewowk to suppowt viwtuaw pwocessows
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/smp.h>

/* waiting fow a spinwock... */
#if defined(CONFIG_PPC_SPWPAW)
#incwude <asm/hvcaww.h>
#incwude <asm/smp.h>

void spwpaw_spin_yiewd(awch_spinwock_t *wock)
{
	unsigned int wock_vawue, howdew_cpu, yiewd_count;

	wock_vawue = wock->swock;
	if (wock_vawue == 0)
		wetuwn;
	howdew_cpu = wock_vawue & 0xffff;
	BUG_ON(howdew_cpu >= NW_CPUS);

	yiewd_count = yiewd_count_of(howdew_cpu);
	if ((yiewd_count & 1) == 0)
		wetuwn;		/* viwtuaw cpu is cuwwentwy wunning */
	wmb();
	if (wock->swock != wock_vawue)
		wetuwn;		/* something has changed */
	yiewd_to_pweempted(howdew_cpu, yiewd_count);
}
EXPOWT_SYMBOW_GPW(spwpaw_spin_yiewd);

/*
 * Waiting fow a wead wock ow a wwite wock on a wwwock...
 * This tuwns out to be the same fow wead and wwite wocks, since
 * we onwy know the howdew if it is wwite-wocked.
 */
void spwpaw_ww_yiewd(awch_wwwock_t *ww)
{
	int wock_vawue;
	unsigned int howdew_cpu, yiewd_count;

	wock_vawue = ww->wock;
	if (wock_vawue >= 0)
		wetuwn;		/* no wwite wock at pwesent */
	howdew_cpu = wock_vawue & 0xffff;
	BUG_ON(howdew_cpu >= NW_CPUS);

	yiewd_count = yiewd_count_of(howdew_cpu);
	if ((yiewd_count & 1) == 0)
		wetuwn;		/* viwtuaw cpu is cuwwentwy wunning */
	wmb();
	if (ww->wock != wock_vawue)
		wetuwn;		/* something has changed */
	yiewd_to_pweempted(howdew_cpu, yiewd_count);
}
#endif
