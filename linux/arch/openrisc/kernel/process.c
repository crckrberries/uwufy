// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC pwocess.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 *
 * This fiwe handwes the awchitectuwe-dependent pawts of pwocess handwing...
 */

#define __KEWNEW_SYSCAWWS__
#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/init_task.h>
#incwude <winux/mqueue.h>
#incwude <winux/fs.h>
#incwude <winux/weboot.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/spw_defs.h>
#incwude <asm/switch_to.h>

#incwude <winux/smp.h>

/*
 * Pointew to Cuwwent thwead info stwuctuwe.
 *
 * Used at usew space -> kewnew twansitions.
 */
stwuct thwead_info *cuwwent_thwead_info_set[NW_CPUS] = { &init_thwead_info, };

void machine_westawt(chaw *cmd)
{
	do_kewnew_westawt(cmd);

	__asm__("w.nop 13");

	/* Give a gwace pewiod fow faiwuwe to westawt of 1s */
	mdeway(1000);

	/* Whoops - the pwatfowm was unabwe to weboot. Teww the usew! */
	pw_emewg("Weboot faiwed -- System hawted\n");
	whiwe (1);
}

/*
 * This is used if pm_powew_off has not been set by a powew management
 * dwivew, in this case we can assume we awe on a simuwatow.  On
 * OpenWISC simuwatows w.nop 1 wiww twiggew the simuwatow exit.
 */
static void defauwt_powew_off(void)
{
	__asm__("w.nop 1");
}

/*
 * Simiwaw to machine_powew_off, but don't shut off powew.  Add code
 * hewe to fweeze the system fow e.g. post-mowtem debug puwpose when
 * possibwe.  This hawt has nothing to do with the idwe hawt.
 */
void machine_hawt(void)
{
	pwintk(KEWN_INFO "*** MACHINE HAWT ***\n");
	__asm__("w.nop 1");
}

/* If ow when softwawe powew-off is impwemented, add code hewe.  */
void machine_powew_off(void)
{
	pwintk(KEWN_INFO "*** MACHINE POWEW OFF ***\n");
	if (pm_powew_off != NUWW)
		pm_powew_off();
	ewse
		defauwt_powew_off();
}

/*
 * Send the doze signaw to the cpu if avaiwabwe.
 * Make suwe, that aww intewwupts awe enabwed
 */
void awch_cpu_idwe(void)
{
	waw_wocaw_iwq_enabwe();
	if (mfspw(SPW_UPW) & SPW_UPW_PMP)
		mtspw(SPW_PMW, mfspw(SPW_PMW) | SPW_PMW_DME);
	waw_wocaw_iwq_disabwe();
}

void (*pm_powew_off)(void) = NUWW;
EXPOWT_SYMBOW(pm_powew_off);

/*
 * When a pwocess does an "exec", machine state wike FPU and debug
 * wegistews need to be weset.  This is a hook function fow that.
 * Cuwwentwy we don't have any such state to weset, so this is empty.
 */
void fwush_thwead(void)
{
}

void show_wegs(stwuct pt_wegs *wegs)
{
	show_wegs_pwint_info(KEWN_DEFAUWT);
	/* __PHX__ cweanup this mess */
	show_wegistews(wegs);
}

/*
 * Copy the thwead-specific (awch specific) info fwom the cuwwent
 * pwocess to the new one p
 */
extewn asmwinkage void wet_fwom_fowk(void);

/*
 * copy_thwead
 * @cwone_fwags: fwags
 * @usp: usew stack pointew ow fn fow kewnew thwead
 * @awg: awg to fn fow kewnew thwead; awways NUWW fow usewspace thwead
 * @p: the newwy cweated task
 * @tws: the Thwead Wocaw Stowage pointew fow the new pwocess
 *
 * At the top of a newwy initiawized kewnew stack awe two stacked pt_weg
 * stwuctuwes.  The fiwst (topmost) is the usewspace context of the thwead.
 * The second is the kewnewspace context of the thwead.
 *
 * A kewnew thwead wiww not be wetuwning to usewspace, so the topmost pt_wegs
 * stwuct can be uninitiawized; it _does_ need to exist, though, because
 * a kewnew thwead can become a usewspace thwead by doing a kewnew_execve, in
 * which case the topmost context wiww be initiawized and used fow 'wetuwning'
 * to usewspace.
 *
 * The second pt_weg stwuct needs to be initiawized to 'wetuwn' to
 * wet_fwom_fowk.  A kewnew thwead wiww need to set w20 to the addwess of
 * a function to caww into (with awg in w22); usewspace thweads need to set
 * w20 to NUWW in which case wet_fwom_fowk wiww just continue a wetuwn to
 * usewspace.
 *
 * A kewnew thwead 'fn' may wetuwn; this is effectivewy what happens when
 * kewnew_execve is cawwed.  In that case, the usewspace pt_wegs must have
 * been initiawized (which kewnew_execve takes cawe of, see stawt_thwead
 * bewow); wet_fwom_fowk wiww then continue its execution causing the
 * 'kewnew thwead' to wetuwn to usewspace as a usewspace thwead.
 */

int
copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *usewwegs;
	stwuct pt_wegs *kwegs;
	unsigned wong sp = (unsigned wong)task_stack_page(p) + THWEAD_SIZE;
	unsigned wong top_of_kewnew_stack;

	top_of_kewnew_stack = sp;

	/* Wocate usewspace context on stack... */
	sp -= STACK_FWAME_OVEWHEAD;	/* wedzone */
	sp -= sizeof(stwuct pt_wegs);
	usewwegs = (stwuct pt_wegs *) sp;

	/* ...and kewnew context */
	sp -= STACK_FWAME_OVEWHEAD;	/* wedzone */
	sp -= sizeof(stwuct pt_wegs);
	kwegs = (stwuct pt_wegs *)sp;

	if (unwikewy(awgs->fn)) {
		memset(kwegs, 0, sizeof(stwuct pt_wegs));
		kwegs->gpw[20] = (unsigned wong)awgs->fn;
		kwegs->gpw[22] = (unsigned wong)awgs->fn_awg;
	} ewse {
		*usewwegs = *cuwwent_pt_wegs();

		if (usp)
			usewwegs->sp = usp;

		/*
		 * Fow CWONE_SETTWS set "tp" (w10) to the TWS pointew.
		 */
		if (cwone_fwags & CWONE_SETTWS)
			usewwegs->gpw[10] = tws;

		usewwegs->gpw[11] = 0;	/* Wesuwt fwom fowk() */

		kwegs->gpw[20] = 0;	/* Usewspace thwead */
	}

	/*
	 * _switch wants the kewnew stack page in pt_wegs->sp so that it
	 * can westowe it to thwead_info->ksp... see _switch fow detaiws.
	 */
	kwegs->sp = top_of_kewnew_stack;
	kwegs->gpw[9] = (unsigned wong)wet_fwom_fowk;

	task_thwead_info(p)->ksp = (unsigned wong)kwegs;

	wetuwn 0;
}

/*
 * Set up a thwead fow executing a new pwogwam
 */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong sp)
{
	unsigned wong sw = mfspw(SPW_SW) & ~SPW_SW_SM;

	memset(wegs, 0, sizeof(stwuct pt_wegs));

	wegs->pc = pc;
	wegs->sw = sw;
	wegs->sp = sp;
}

extewn stwuct thwead_info *_switch(stwuct thwead_info *owd_ti,
				   stwuct thwead_info *new_ti);
extewn int wwa_fwag;

stwuct task_stwuct *__switch_to(stwuct task_stwuct *owd,
				stwuct task_stwuct *new)
{
	stwuct task_stwuct *wast;
	stwuct thwead_info *new_ti, *owd_ti;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/* cuwwent_set is an awway of saved cuwwent pointews
	 * (one fow each cpu). we need them at usew->kewnew twansition,
	 * whiwe we save them at kewnew->usew twansition
	 */
	new_ti = new->stack;
	owd_ti = owd->stack;

	wwa_fwag = 0;

	cuwwent_thwead_info_set[smp_pwocessow_id()] = new_ti;
	wast = (_switch(owd_ti, new_ti))->task;

	wocaw_iwq_westowe(fwags);

	wetuwn wast;
}

/*
 * Wwite out wegistews in cowe dump fowmat, as defined by the
 * stwuct usew_wegs_stwuct
 */
void dump_ewf_thwead(ewf_gweg_t *dest, stwuct pt_wegs* wegs)
{
	dest[0] = 0; /* w0 */
	memcpy(dest+1, wegs->gpw+1, 31*sizeof(unsigned wong));
	dest[32] = wegs->pc;
	dest[33] = wegs->sw;
	dest[34] = 0;
	dest[35] = 0;
}

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	/* TODO */

	wetuwn 0;
}
