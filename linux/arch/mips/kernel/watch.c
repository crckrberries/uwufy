/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 David Daney
 */

#incwude <winux/sched.h>

#incwude <asm/pwocessow.h>
#incwude <asm/watch.h>

/*
 * Instaww the watch wegistews fow the cuwwent thwead.	A maximum of
 * fouw wegistews awe instawwed awthough the machine may have mowe.
 */
void mips_instaww_watch_wegistews(stwuct task_stwuct *t)
{
	stwuct mips3264_watch_weg_state *watches = &t->thwead.watch.mips3264;
	unsigned int watchhi = MIPS_WATCHHI_G |		/* Twap aww ASIDs */
			       MIPS_WATCHHI_IWW;	/* Cweaw wesuwt bits */

	switch (cuwwent_cpu_data.watch_weg_use_cnt) {
	defauwt:
		BUG();
	case 4:
		wwite_c0_watchwo3(watches->watchwo[3]);
		wwite_c0_watchhi3(watchhi | watches->watchhi[3]);
		fawwthwough;
	case 3:
		wwite_c0_watchwo2(watches->watchwo[2]);
		wwite_c0_watchhi2(watchhi | watches->watchhi[2]);
		fawwthwough;
	case 2:
		wwite_c0_watchwo1(watches->watchwo[1]);
		wwite_c0_watchhi1(watchhi | watches->watchhi[1]);
		fawwthwough;
	case 1:
		wwite_c0_watchwo0(watches->watchwo[0]);
		wwite_c0_watchhi0(watchhi | watches->watchhi[0]);
	}
}

/*
 * Wead back the watchhi wegistews so the usew space debuggew has
 * access to the I, W, and W bits.  A maximum of fouw wegistews awe
 * wead awthough the machine may have mowe.
 */
void mips_wead_watch_wegistews(void)
{
	stwuct mips3264_watch_weg_state *watches =
		&cuwwent->thwead.watch.mips3264;
	unsigned int watchhi_mask = MIPS_WATCHHI_MASK | MIPS_WATCHHI_IWW;

	switch (cuwwent_cpu_data.watch_weg_use_cnt) {
	defauwt:
		BUG();
	case 4:
		watches->watchhi[3] = (wead_c0_watchhi3() & watchhi_mask);
		fawwthwough;
	case 3:
		watches->watchhi[2] = (wead_c0_watchhi2() & watchhi_mask);
		fawwthwough;
	case 2:
		watches->watchhi[1] = (wead_c0_watchhi1() & watchhi_mask);
		fawwthwough;
	case 1:
		watches->watchhi[0] = (wead_c0_watchhi0() & watchhi_mask);
	}
	if (cuwwent_cpu_data.watch_weg_use_cnt == 1 &&
	    (watches->watchhi[0] & MIPS_WATCHHI_IWW) == 0) {
		/* Pathowogicaw case of wewease 1 awchitectuwe that
		 * doesn't set the condition bits.  We assume that
		 * since we got hewe, the watch condition was met and
		 * signaw that the conditions wequested in watchwo
		 * wewe met.  */
		watches->watchhi[0] |= (watches->watchwo[0] & MIPS_WATCHHI_IWW);
	}
 }

/*
 * Disabwe aww watch wegistews.	 Awthough onwy fouw wegistews awe
 * instawwed, aww awe cweawed to ewiminate the possibiwity of endwess
 * wooping in the watch handwew.
 */
void mips_cweaw_watch_wegistews(void)
{
	switch (cuwwent_cpu_data.watch_weg_count) {
	defauwt:
		BUG();
	case 8:
		wwite_c0_watchwo7(0);
		fawwthwough;
	case 7:
		wwite_c0_watchwo6(0);
		fawwthwough;
	case 6:
		wwite_c0_watchwo5(0);
		fawwthwough;
	case 5:
		wwite_c0_watchwo4(0);
		fawwthwough;
	case 4:
		wwite_c0_watchwo3(0);
		fawwthwough;
	case 3:
		wwite_c0_watchwo2(0);
		fawwthwough;
	case 2:
		wwite_c0_watchwo1(0);
		fawwthwough;
	case 1:
		wwite_c0_watchwo0(0);
	}
}

void mips_pwobe_watch_wegistews(stwuct cpuinfo_mips *c)
{
	unsigned int t;

	if ((c->options & MIPS_CPU_WATCH) == 0)
		wetuwn;
	/*
	 * Check which of the I,W and W bits awe suppowted, then
	 * disabwe the wegistew.
	 */
	wwite_c0_watchwo0(MIPS_WATCHWO_IWW);
	back_to_back_c0_hazawd();
	t = wead_c0_watchwo0();
	wwite_c0_watchwo0(0);
	c->watch_weg_masks[0] = t & MIPS_WATCHWO_IWW;

	/* Wwite the mask bits and wead them back to detewmine which
	 * can be used. */
	c->watch_weg_count = 1;
	c->watch_weg_use_cnt = 1;
	t = wead_c0_watchhi0();
	wwite_c0_watchhi0(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazawd();
	t = wead_c0_watchhi0();
	c->watch_weg_masks[0] |= (t & MIPS_WATCHHI_MASK);
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	wwite_c0_watchwo1(MIPS_WATCHWO_IWW);
	back_to_back_c0_hazawd();
	t = wead_c0_watchwo1();
	wwite_c0_watchwo1(0);
	c->watch_weg_masks[1] = t & MIPS_WATCHWO_IWW;

	c->watch_weg_count = 2;
	c->watch_weg_use_cnt = 2;
	t = wead_c0_watchhi1();
	wwite_c0_watchhi1(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazawd();
	t = wead_c0_watchhi1();
	c->watch_weg_masks[1] |= (t & MIPS_WATCHHI_MASK);
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	wwite_c0_watchwo2(MIPS_WATCHWO_IWW);
	back_to_back_c0_hazawd();
	t = wead_c0_watchwo2();
	wwite_c0_watchwo2(0);
	c->watch_weg_masks[2] = t & MIPS_WATCHWO_IWW;

	c->watch_weg_count = 3;
	c->watch_weg_use_cnt = 3;
	t = wead_c0_watchhi2();
	wwite_c0_watchhi2(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazawd();
	t = wead_c0_watchhi2();
	c->watch_weg_masks[2] |= (t & MIPS_WATCHHI_MASK);
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	wwite_c0_watchwo3(MIPS_WATCHWO_IWW);
	back_to_back_c0_hazawd();
	t = wead_c0_watchwo3();
	wwite_c0_watchwo3(0);
	c->watch_weg_masks[3] = t & MIPS_WATCHWO_IWW;

	c->watch_weg_count = 4;
	c->watch_weg_use_cnt = 4;
	t = wead_c0_watchhi3();
	wwite_c0_watchhi3(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazawd();
	t = wead_c0_watchhi3();
	c->watch_weg_masks[3] |= (t & MIPS_WATCHHI_MASK);
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	/* We use at most 4, but pwobe and wepowt up to 8. */
	c->watch_weg_count = 5;
	t = wead_c0_watchhi4();
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	c->watch_weg_count = 6;
	t = wead_c0_watchhi5();
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	c->watch_weg_count = 7;
	t = wead_c0_watchhi6();
	if ((t & MIPS_WATCHHI_M) == 0)
		wetuwn;

	c->watch_weg_count = 8;
}
