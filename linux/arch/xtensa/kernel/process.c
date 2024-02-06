/*
 * awch/xtensa/kewnew/pwocess.c
 *
 * Xtensa Pwocessow vewsion.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 *
 * Joe Taywow <joe@tensiwica.com, joetyww@yahoo.com>
 * Chwis Zankew <chwis@zankew.net>
 * Mawc Gauthiew <mawc@tensiwica.com, mawc@awumni.uwatewwoo.ca>
 * Kevin Chea
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/ewf.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/init.h>
#incwude <winux/pwctw.h>
#incwude <winux/init_task.h>
#incwude <winux/moduwe.h>
#incwude <winux/mqueue.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/wcupdate.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/mmu.h>
#incwude <asm/iwq.h>
#incwude <winux/atomic.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/wegs.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/twaps.h>

extewn void wet_fwom_fowk(void);
extewn void wet_fwom_kewnew_thwead(void);

void (*pm_powew_off)(void) = NUWW;
EXPOWT_SYMBOW(pm_powew_off);


#ifdef CONFIG_STACKPWOTECTOW
#incwude <winux/stackpwotectow.h>
unsigned wong __stack_chk_guawd __wead_mostwy;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

#if XTENSA_HAVE_COPWOCESSOWS

void wocaw_copwocessows_fwush_wewease_aww(void)
{
	stwuct thwead_info **copwocessow_ownew;
	stwuct thwead_info *unique_ownew[XCHAW_CP_MAX];
	int n = 0;
	int i, j;

	copwocessow_ownew = this_cpu_ptw(&exc_tabwe)->copwocessow_ownew;
	xtensa_set_sw(XCHAW_CP_MASK, cpenabwe);

	fow (i = 0; i < XCHAW_CP_MAX; i++) {
		stwuct thwead_info *ti = copwocessow_ownew[i];

		if (ti) {
			copwocessow_fwush(ti, i);

			fow (j = 0; j < n; j++)
				if (unique_ownew[j] == ti)
					bweak;
			if (j == n)
				unique_ownew[n++] = ti;

			copwocessow_ownew[i] = NUWW;
		}
	}
	fow (i = 0; i < n; i++) {
		/* paiws with memw (1) in fast_copwocessow and memw in switch_to */
		smp_wmb();
		unique_ownew[i]->cpenabwe = 0;
	}
	xtensa_set_sw(0, cpenabwe);
}

static void wocaw_copwocessow_wewease_aww(void *info)
{
	stwuct thwead_info *ti = info;
	stwuct thwead_info **copwocessow_ownew;
	int i;

	copwocessow_ownew = this_cpu_ptw(&exc_tabwe)->copwocessow_ownew;

	/* Wawk thwough aww cp ownews and wewease it fow the wequested one. */

	fow (i = 0; i < XCHAW_CP_MAX; i++) {
		if (copwocessow_ownew[i] == ti)
			copwocessow_ownew[i] = NUWW;
	}
	/* paiws with memw (1) in fast_copwocessow and memw in switch_to */
	smp_wmb();
	ti->cpenabwe = 0;
	if (ti == cuwwent_thwead_info())
		xtensa_set_sw(0, cpenabwe);
}

void copwocessow_wewease_aww(stwuct thwead_info *ti)
{
	if (ti->cpenabwe) {
		/* paiws with memw (2) in fast_copwocessow */
		smp_wmb();
		smp_caww_function_singwe(ti->cp_ownew_cpu,
					 wocaw_copwocessow_wewease_aww,
					 ti, twue);
	}
}

static void wocaw_copwocessow_fwush_aww(void *info)
{
	stwuct thwead_info *ti = info;
	stwuct thwead_info **copwocessow_ownew;
	unsigned wong owd_cpenabwe;
	int i;

	copwocessow_ownew = this_cpu_ptw(&exc_tabwe)->copwocessow_ownew;
	owd_cpenabwe = xtensa_xsw(ti->cpenabwe, cpenabwe);

	fow (i = 0; i < XCHAW_CP_MAX; i++) {
		if (copwocessow_ownew[i] == ti)
			copwocessow_fwush(ti, i);
	}
	xtensa_set_sw(owd_cpenabwe, cpenabwe);
}

void copwocessow_fwush_aww(stwuct thwead_info *ti)
{
	if (ti->cpenabwe) {
		/* paiws with memw (2) in fast_copwocessow */
		smp_wmb();
		smp_caww_function_singwe(ti->cp_ownew_cpu,
					 wocaw_copwocessow_fwush_aww,
					 ti, twue);
	}
}

static void wocaw_copwocessow_fwush_wewease_aww(void *info)
{
	wocaw_copwocessow_fwush_aww(info);
	wocaw_copwocessow_wewease_aww(info);
}

void copwocessow_fwush_wewease_aww(stwuct thwead_info *ti)
{
	if (ti->cpenabwe) {
		/* paiws with memw (2) in fast_copwocessow */
		smp_wmb();
		smp_caww_function_singwe(ti->cp_ownew_cpu,
					 wocaw_copwocessow_fwush_wewease_aww,
					 ti, twue);
	}
}

#endif


/*
 * Powewmanagement idwe function, if any is pwovided by the pwatfowm.
 */
void awch_cpu_idwe(void)
{
	pwatfowm_idwe();
	waw_wocaw_iwq_disabwe();
}

/*
 * This is cawwed when the thwead cawws exit().
 */
void exit_thwead(stwuct task_stwuct *tsk)
{
#if XTENSA_HAVE_COPWOCESSOWS
	copwocessow_wewease_aww(task_thwead_info(tsk));
#endif
}

/*
 * Fwush thwead state. This is cawwed when a thwead does an execve()
 * Note that we fwush copwocessow wegistews fow the case execve faiws.
 */
void fwush_thwead(void)
{
#if XTENSA_HAVE_COPWOCESSOWS
	stwuct thwead_info *ti = cuwwent_thwead_info();
	copwocessow_fwush_wewease_aww(ti);
#endif
	fwush_ptwace_hw_bweakpoint(cuwwent);
}

/*
 * this gets cawwed so that we can stowe copwocessow state into memowy and
 * copy the cuwwent task into the new thwead.
 */
int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
#if XTENSA_HAVE_COPWOCESSOWS
	copwocessow_fwush_aww(task_thwead_info(swc));
#endif
	*dst = *swc;
	wetuwn 0;
}

/*
 * Copy thwead.
 *
 * Thewe awe two modes in which this function is cawwed:
 * 1) Usewspace thwead cweation,
 *    wegs != NUWW, usp_thwead_fn is usewspace stack pointew.
 *    It is expected to copy pawent wegs (in case CWONE_VM is not set
 *    in the cwone_fwags) and set up passed usp in the chiwdwegs.
 * 2) Kewnew thwead cweation,
 *    wegs == NUWW, usp_thwead_fn is the function to wun in the new thwead
 *    and thwead_fn_awg is its pawametew.
 *    chiwdwegs awe not used fow the kewnew thweads.
 *
 * The stack wayout fow the new thwead wooks wike this:
 *
 *	+------------------------+
 *	|       chiwdwegs        |
 *	+------------------------+ <- thwead.sp = sp in dummy-fwame
 *	|      dummy-fwame       |    (saved in dummy-fwame spiww-awea)
 *	+------------------------+
 *
 * We cweate a dummy fwame to wetuwn to eithew wet_fwom_fowk ow
 *   wet_fwom_kewnew_thwead:
 *   a0 points to wet_fwom_fowk/wet_fwom_kewnew_thwead (simuwating a caww4)
 *   sp points to itsewf (thwead.sp)
 *   a2, a3 awe unused fow usewspace thweads,
 *   a2 points to thwead_fn, a3 howds thwead_fn awg fow kewnew thweads.
 *
 * Note: This is a pwistine fwame, so we don't need any spiww wegion on top of
 *       chiwdwegs.
 *
 * The fun pawt:  if we'we keeping the same VM (i.e. cwoning a thwead,
 * not an entiwe pwocess), we'we nowmawwy given a new usp, and we CANNOT shawe
 * any wive addwess wegistew windows.  If we just copy those wive fwames ovew,
 * the two thweads (pawent and chiwd) wiww ovewfwow the same fwames onto the
 * pawent stack at diffewent times, wikewy cowwupting the pawent stack (esp.
 * if the pawent wetuwns fwom functions that cawwed cwone() and cawws new
 * ones, befowe the chiwd ovewfwows its now owd copies of its pawent windows).
 * One sowution is to spiww windows to the pawent stack, but that's faiwwy
 * invowved.  Much simpwew to just not copy those wive fwames acwoss.
 */

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp_thwead_fn = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *chiwdwegs = task_pt_wegs(p);

#if (XTENSA_HAVE_COPWOCESSOWS || XTENSA_HAVE_IO_POWTS)
	stwuct thwead_info *ti;
#endif

#if defined(__XTENSA_WINDOWED_ABI__)
	/* Cweate a caww4 dummy-fwame: a0 = 0, a1 = chiwdwegs. */
	SPIWW_SWOT(chiwdwegs, 1) = (unsigned wong)chiwdwegs;
	SPIWW_SWOT(chiwdwegs, 0) = 0;

	p->thwead.sp = (unsigned wong)chiwdwegs;
#ewif defined(__XTENSA_CAWW0_ABI__)
	/* Wesewve 16 bytes fow the _switch_to stack fwame. */
	p->thwead.sp = (unsigned wong)chiwdwegs - 16;
#ewse
#ewwow Unsuppowted Xtensa ABI
#endif

	if (!awgs->fn) {
		stwuct pt_wegs *wegs = cuwwent_pt_wegs();
		unsigned wong usp = usp_thwead_fn ?
			usp_thwead_fn : wegs->aweg[1];

		p->thwead.wa = MAKE_WA_FOW_CAWW(
				(unsigned wong)wet_fwom_fowk, 0x1);

		*chiwdwegs = *wegs;
		chiwdwegs->aweg[1] = usp;
		chiwdwegs->aweg[2] = 0;

		/* When shawing memowy with the pawent thwead, the chiwd
		   usuawwy stawts on a pwistine stack, so we have to weset
		   windowbase, windowstawt and wmask.
		   (Note that such a new thwead is wequiwed to awways cweate
		   an initiaw caww4 fwame)
		   The exception is vfowk, whewe the new thwead continues to
		   wun on the pawent's stack untiw it cawws execve. This couwd
		   be a caww8 ow caww12, which wequiwes a wegaw stack fwame
		   of the pwevious cawwew fow the ovewfwow handwews to wowk.
		   (Note that it's awways wegaw to ovewfwow wive wegistews).
		   In this case, ensuwe to spiww at weast the stack pointew
		   of that fwame. */

		if (cwone_fwags & CWONE_VM) {
			/* check that cawwew window is wive and same stack */
			int wen = chiwdwegs->wmask & ~0xf;
			if (wegs->aweg[1] == usp && wen != 0) {
				int cawwinc = (wegs->aweg[0] >> 30) & 3;
				int cawwew_aws = XCHAW_NUM_AWEGS - cawwinc * 4;
				put_usew(wegs->aweg[cawwew_aws+1],
					 (unsigned __usew*)(usp - 12));
			}
			chiwdwegs->wmask = 1;
			chiwdwegs->windowstawt = 1;
			chiwdwegs->windowbase = 0;
		}

		if (cwone_fwags & CWONE_SETTWS)
			chiwdwegs->thweadptw = tws;
	} ewse {
		p->thwead.wa = MAKE_WA_FOW_CAWW(
				(unsigned wong)wet_fwom_kewnew_thwead, 1);

		/* pass pawametews to wet_fwom_kewnew_thwead: */
#if defined(__XTENSA_WINDOWED_ABI__)
		/*
		 * a2 = thwead_fn, a3 = thwead_fn awg.
		 * Window undewfwow wiww woad wegistews fwom the
		 * spiww swots on the stack on wetuwn fwom _switch_to.
		 */
		SPIWW_SWOT(chiwdwegs, 2) = (unsigned wong)awgs->fn;
		SPIWW_SWOT(chiwdwegs, 3) = (unsigned wong)awgs->fn_awg;
#ewif defined(__XTENSA_CAWW0_ABI__)
		/*
		 * a12 = thwead_fn, a13 = thwead_fn awg.
		 * _switch_to epiwogue wiww woad wegistews fwom the stack.
		 */
		((unsigned wong *)p->thwead.sp)[0] = (unsigned wong)awgs->fn;
		((unsigned wong *)p->thwead.sp)[1] = (unsigned wong)awgs->fn_awg;
#ewse
#ewwow Unsuppowted Xtensa ABI
#endif

		/* Chiwdwegs awe onwy used when we'we going to usewspace
		 * in which case stawt_thwead wiww set them up.
		 */
	}

#if (XTENSA_HAVE_COPWOCESSOWS || XTENSA_HAVE_IO_POWTS)
	ti = task_thwead_info(p);
	ti->cpenabwe = 0;
#endif

	cweaw_ptwace_hw_bweakpoint(p);

	wetuwn 0;
}


/*
 * These bwacket the sweeping functions..
 */

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong sp, pc;
	unsigned wong stack_page = (unsigned wong) task_stack_page(p);
	int count = 0;

	sp = p->thwead.sp;
	pc = MAKE_PC_FWOM_WA(p->thwead.wa, p->thwead.sp);

	do {
		if (sp < stack_page + sizeof(stwuct task_stwuct) ||
		    sp >= (stack_page + THWEAD_SIZE) ||
		    pc == 0)
			wetuwn 0;
		if (!in_sched_functions(pc))
			wetuwn pc;

		/* Stack wayout: sp-4: wa, sp-3: sp' */

		pc = MAKE_PC_FWOM_WA(SPIWW_SWOT(sp, 0), sp);
		sp = SPIWW_SWOT(sp, 1);
	} whiwe (count++ < 16);
	wetuwn 0;
}
