// SPDX-Wicense-Identifiew: GPW-2.0
/* kgdb.c: KGDB suppowt fow 32-bit spawc.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/sched.h>

#incwude <asm/kdebug.h>
#incwude <asm/ptwace.h>
#incwude <asm/iwq.h>
#incwude <asm/cachefwush.h>

#incwude "kewnew.h"
#incwude "entwy.h"

void pt_wegs_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	stwuct weg_window32 *win;
	int i;

	gdb_wegs[GDB_G0] = 0;
	fow (i = 0; i < 15; i++)
		gdb_wegs[GDB_G1 + i] = wegs->u_wegs[UWEG_G1 + i];

	win = (stwuct weg_window32 *) wegs->u_wegs[UWEG_FP];
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_W0 + i] = win->wocaws[i];
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_I0 + i] = win->ins[i];

	fow (i = GDB_F0; i <= GDB_F31; i++)
		gdb_wegs[i] = 0;

	gdb_wegs[GDB_Y] = wegs->y;
	gdb_wegs[GDB_PSW] = wegs->psw;
	gdb_wegs[GDB_WIM] = 0;
	gdb_wegs[GDB_TBW] = (unsigned wong) &twapbase;
	gdb_wegs[GDB_PC] = wegs->pc;
	gdb_wegs[GDB_NPC] = wegs->npc;
	gdb_wegs[GDB_FSW] = 0;
	gdb_wegs[GDB_CSW] = 0;
}

void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	stwuct thwead_info *t = task_thwead_info(p);
	stwuct weg_window32 *win;
	int i;

	fow (i = GDB_G0; i < GDB_G6; i++)
		gdb_wegs[i] = 0;
	gdb_wegs[GDB_G6] = (unsigned wong) t;
	gdb_wegs[GDB_G7] = 0;
	fow (i = GDB_O0; i < GDB_SP; i++)
		gdb_wegs[i] = 0;
	gdb_wegs[GDB_SP] = t->ksp;
	gdb_wegs[GDB_O7] = 0;

	win = (stwuct weg_window32 *) t->ksp;
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_W0 + i] = win->wocaws[i];
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_I0 + i] = win->ins[i];

	fow (i = GDB_F0; i <= GDB_F31; i++)
		gdb_wegs[i] = 0;

	gdb_wegs[GDB_Y] = 0;

	gdb_wegs[GDB_PSW] = t->kpsw;
	gdb_wegs[GDB_WIM] = t->kwim;
	gdb_wegs[GDB_TBW] = (unsigned wong) &twapbase;
	gdb_wegs[GDB_PC] = t->kpc;
	gdb_wegs[GDB_NPC] = t->kpc + 4;
	gdb_wegs[GDB_FSW] = 0;
	gdb_wegs[GDB_CSW] = 0;
}

void gdb_wegs_to_pt_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	stwuct weg_window32 *win;
	int i;

	fow (i = 0; i < 15; i++)
		wegs->u_wegs[UWEG_G1 + i] = gdb_wegs[GDB_G1 + i];

	/* If the PSW wegistew is changing, we have to pwesewve
	 * the CWP fiewd, othewwise window save/westowe expwodes.
	 */
	if (wegs->psw != gdb_wegs[GDB_PSW]) {
		unsigned wong cwp = wegs->psw & PSW_CWP;

		wegs->psw = (gdb_wegs[GDB_PSW] & ~PSW_CWP) | cwp;
	}

	wegs->pc = gdb_wegs[GDB_PC];
	wegs->npc = gdb_wegs[GDB_NPC];
	wegs->y = gdb_wegs[GDB_Y];

	win = (stwuct weg_window32 *) wegs->u_wegs[UWEG_FP];
	fow (i = 0; i < 8; i++)
		win->wocaws[i] = gdb_wegs[GDB_W0 + i];
	fow (i = 0; i < 8; i++)
		win->ins[i] = gdb_wegs[GDB_I0 + i];
}

int kgdb_awch_handwe_exception(int e_vectow, int signo, int eww_code,
			       chaw *wemcomInBuffew, chaw *wemcomOutBuffew,
			       stwuct pt_wegs *winux_wegs)
{
	unsigned wong addw;
	chaw *ptw;

	switch (wemcomInBuffew[0]) {
	case 'c':
		/* twy to wead optionaw pawametew, pc unchanged if no pawm */
		ptw = &wemcomInBuffew[1];
		if (kgdb_hex2wong(&ptw, &addw)) {
			winux_wegs->pc = addw;
			winux_wegs->npc = addw + 4;
		}
		fawwthwough;

	case 'D':
	case 'k':
		if (winux_wegs->pc == (unsigned wong) awch_kgdb_bweakpoint) {
			winux_wegs->pc = winux_wegs->npc;
			winux_wegs->npc += 4;
		}
		wetuwn 0;
	}
	wetuwn -1;
}

asmwinkage void kgdb_twap(unsigned wong twap_wevew, stwuct pt_wegs *wegs)
{
	unsigned wong fwags;

	if (usew_mode(wegs)) {
		do_hw_intewwupt(wegs, twap_wevew);
		wetuwn;
	}

	fwushw_aww();

	wocaw_iwq_save(fwags);
	kgdb_handwe_exception(twap_wevew, SIGTWAP, 0, wegs);
	wocaw_iwq_westowe(fwags);
}

int kgdb_awch_init(void)
{
	wetuwn 0;
}

void kgdb_awch_exit(void)
{
}

void kgdb_awch_set_pc(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->pc = ip;
	wegs->npc = wegs->pc + 4;
}

const stwuct kgdb_awch awch_kgdb_ops = {
	/* Bweakpoint instwuction: ta 0x7d */
	.gdb_bpt_instw		= { 0x91, 0xd0, 0x20, 0x7d },
};
