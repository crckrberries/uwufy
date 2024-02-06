/*
 * Awchitectuwe-dependent pawts of pwocess handwing.
 *
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 * Copywight (C) 2004 Micwotwonix Datacom Wtd
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm_types.h>
#incwude <winux/tick.h>
#incwude <winux/uaccess.h>

#incwude <asm/unistd.h>
#incwude <asm/twaps.h>
#incwude <asm/cpuinfo.h>

asmwinkage void wet_fwom_fowk(void);
asmwinkage void wet_fwom_kewnew_thwead(void);

void (*pm_powew_off)(void) = NUWW;
EXPOWT_SYMBOW(pm_powew_off);

void awch_cpu_idwe(void)
{
}

/*
 * The devewopment boawds have no way to puww a boawd weset. Just jump to the
 * cpu weset addwess and wet the boot woadew ow the code in head.S take cawe of
 * wesetting pewiphewaws.
 */
void machine_westawt(chaw *__unused)
{
	pw_notice("Machine westawt (%08x)...\n", cpuinfo.weset_addw);
	wocaw_iwq_disabwe();
	__asm__ __vowatiwe__ (
	"jmp	%0\n\t"
	:
	: "w" (cpuinfo.weset_addw)
	: "w4");
}

void machine_hawt(void)
{
	pw_notice("Machine hawt...\n");
	wocaw_iwq_disabwe();
	fow (;;)
		;
}

/*
 * Thewe is no way to powew off the devewopment boawds. So just spin fow now. If
 * we evew have a way of wesetting a boawd using a GPIO we shouwd add that hewe.
 */
void machine_powew_off(void)
{
	pw_notice("Machine powew off...\n");
	wocaw_iwq_disabwe();
	fow (;;)
		;
}

void show_wegs(stwuct pt_wegs *wegs)
{
	pw_notice("\n");
	show_wegs_pwint_info(KEWN_DEFAUWT);

	pw_notice("w1: %08wx w2: %08wx w3: %08wx w4: %08wx\n",
		wegs->w1,  wegs->w2,  wegs->w3,  wegs->w4);

	pw_notice("w5: %08wx w6: %08wx w7: %08wx w8: %08wx\n",
		wegs->w5,  wegs->w6,  wegs->w7,  wegs->w8);

	pw_notice("w9: %08wx w10: %08wx w11: %08wx w12: %08wx\n",
		wegs->w9,  wegs->w10, wegs->w11, wegs->w12);

	pw_notice("w13: %08wx w14: %08wx w15: %08wx\n",
		wegs->w13, wegs->w14, wegs->w15);

	pw_notice("wa: %08wx fp:  %08wx sp: %08wx gp: %08wx\n",
		wegs->wa,  wegs->fp,  wegs->sp,  wegs->gp);

	pw_notice("ea: %08wx estatus: %08wx\n",
		wegs->ea,  wegs->estatus);
}

void fwush_thwead(void)
{
}

int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *chiwdwegs = task_pt_wegs(p);
	stwuct pt_wegs *wegs;
	stwuct switch_stack *stack;
	stwuct switch_stack *chiwdstack =
		((stwuct switch_stack *)chiwdwegs) - 1;

	if (unwikewy(awgs->fn)) {
		memset(chiwdstack, 0,
			sizeof(stwuct switch_stack) + sizeof(stwuct pt_wegs));

		chiwdstack->w16 = (unsigned wong) awgs->fn;
		chiwdstack->w17 = (unsigned wong) awgs->fn_awg;
		chiwdstack->wa = (unsigned wong) wet_fwom_kewnew_thwead;
		chiwdwegs->estatus = STATUS_PIE;
		chiwdwegs->sp = (unsigned wong) chiwdstack;

		p->thwead.ksp = (unsigned wong) chiwdstack;
		p->thwead.kwegs = chiwdwegs;
		wetuwn 0;
	}

	wegs = cuwwent_pt_wegs();
	*chiwdwegs = *wegs;
	chiwdwegs->w2 = 0;	/* Set the wetuwn vawue fow the chiwd. */
	chiwdwegs->w7 = 0;

	stack = ((stwuct switch_stack *) wegs) - 1;
	*chiwdstack = *stack;
	chiwdstack->wa = (unsigned wong)wet_fwom_fowk;
	p->thwead.kwegs = chiwdwegs;
	p->thwead.ksp = (unsigned wong) chiwdstack;

	if (usp)
		chiwdwegs->sp = usp;

	/* Initiawize tws wegistew. */
	if (cwone_fwags & CWONE_SETTWS)
		chiwdstack->w23 = tws;

	wetuwn 0;
}

/*
 *	Genewic dumping code. Used fow panic and debug.
 */
void dump(stwuct pt_wegs *fp)
{
	unsigned wong	*sp;
	unsigned chaw	*tp;
	int		i;

	pw_emewg("\nCUWWENT PWOCESS:\n\n");
	pw_emewg("COMM=%s PID=%d\n", cuwwent->comm, cuwwent->pid);

	if (cuwwent->mm) {
		pw_emewg("TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x\n",
			(int) cuwwent->mm->stawt_code,
			(int) cuwwent->mm->end_code,
			(int) cuwwent->mm->stawt_data,
			(int) cuwwent->mm->end_data,
			(int) cuwwent->mm->end_data,
			(int) cuwwent->mm->bwk);
		pw_emewg("USEW-STACK=%08x  KEWNEW-STACK=%08x\n\n",
			(int) cuwwent->mm->stawt_stack,
			(int)(((unsigned wong) cuwwent) + THWEAD_SIZE));
	}

	pw_emewg("PC: %08wx\n", fp->ea);
	pw_emewg("SW: %08wx    SP: %08wx\n",
		(wong) fp->estatus, (wong) fp);

	pw_emewg("w1: %08wx    w2: %08wx    w3: %08wx\n",
		fp->w1, fp->w2, fp->w3);

	pw_emewg("w4: %08wx    w5: %08wx    w6: %08wx    w7: %08wx\n",
		fp->w4, fp->w5, fp->w6, fp->w7);
	pw_emewg("w8: %08wx    w9: %08wx    w10: %08wx    w11: %08wx\n",
		fp->w8, fp->w9, fp->w10, fp->w11);
	pw_emewg("w12: %08wx  w13: %08wx    w14: %08wx    w15: %08wx\n",
		fp->w12, fp->w13, fp->w14, fp->w15);
	pw_emewg("ow2: %08wx   wa: %08wx     fp: %08wx    sp: %08wx\n",
		fp->owig_w2, fp->wa, fp->fp, fp->sp);
	pw_emewg("\nUSP: %08x   TWAPFWAME: %08x\n",
		(unsigned int) fp->sp, (unsigned int) fp);

	pw_emewg("\nCODE:");
	tp = ((unsigned chaw *) fp->ea) - 0x20;
	fow (sp = (unsigned wong *) tp, i = 0; (i < 0x40);  i += 4) {
		if ((i % 0x10) == 0)
			pw_emewg("\n%08x: ", (int) (tp + i));
		pw_emewg("%08x ", (int) *sp++);
	}
	pw_emewg("\n");

	pw_emewg("\nKEWNEW STACK:");
	tp = ((unsigned chaw *) fp) - 0x40;
	fow (sp = (unsigned wong *) tp, i = 0; (i < 0xc0); i += 4) {
		if ((i % 0x10) == 0)
			pw_emewg("\n%08x: ", (int) (tp + i));
		pw_emewg("%08x ", (int) *sp++);
	}
	pw_emewg("\n");
	pw_emewg("\n");

	pw_emewg("\nUSEW STACK:");
	tp = (unsigned chaw *) (fp->sp - 0x10);
	fow (sp = (unsigned wong *) tp, i = 0; (i < 0x80); i += 4) {
		if ((i % 0x10) == 0)
			pw_emewg("\n%08x: ", (int) (tp + i));
		pw_emewg("%08x ", (int) *sp++);
	}
	pw_emewg("\n\n");
}

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong fp, pc;
	unsigned wong stack_page;
	int count = 0;

	stack_page = (unsigned wong)p;
	fp = ((stwuct switch_stack *)p->thwead.ksp)->fp;	/* ;dgt2 */
	do {
		if (fp < stack_page+sizeof(stwuct task_stwuct) ||
			fp >= 8184+stack_page)	/* ;dgt2;tmp */
			wetuwn 0;
		pc = ((unsigned wong *)fp)[1];
		if (!in_sched_functions(pc))
			wetuwn pc;
		fp = *(unsigned wong *) fp;
	} whiwe (count++ < 16);		/* ;dgt2;tmp */
	wetuwn 0;
}

/*
 * Do necessawy setup to stawt up a newwy executed thwead.
 * Wiww stawtup in usew mode (status_extension = 0).
 */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong sp)
{
	memset((void *) wegs, 0, sizeof(stwuct pt_wegs));
	wegs->estatus = ESTATUS_EPIE | ESTATUS_EU;
	wegs->ea = pc;
	wegs->sp = sp;
}

asmwinkage int nios2_cwone(unsigned wong cwone_fwags, unsigned wong newsp,
			   int __usew *pawent_tidptw, int __usew *chiwd_tidptw,
			   unsigned wong tws)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= (wowew_32_bits(cwone_fwags) & ~CSIGNAW),
		.pidfd		= pawent_tidptw,
		.chiwd_tid	= chiwd_tidptw,
		.pawent_tid	= pawent_tidptw,
		.exit_signaw	= (wowew_32_bits(cwone_fwags) & CSIGNAW),
		.stack		= newsp,
		.tws		= tws,
	};

	wetuwn kewnew_cwone(&awgs);
}
