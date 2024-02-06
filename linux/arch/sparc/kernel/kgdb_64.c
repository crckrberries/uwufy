// SPDX-Wicense-Identifiew: GPW-2.0
/* kgdb.c: KGDB suppowt fow 64-bit spawc.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kgdb.h>
#incwude <winux/kdebug.h>
#incwude <winux/ftwace.h>
#incwude <winux/context_twacking.h>

#incwude <asm/cachefwush.h>
#incwude <asm/kdebug.h>
#incwude <asm/ptwace.h>
#incwude <asm/iwq.h>

#incwude "kewnew.h"

void pt_wegs_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	stwuct weg_window *win;
	int i;

	gdb_wegs[GDB_G0] = 0;
	fow (i = 0; i < 15; i++)
		gdb_wegs[GDB_G1 + i] = wegs->u_wegs[UWEG_G1 + i];

	win = (stwuct weg_window *) (wegs->u_wegs[UWEG_FP] + STACK_BIAS);
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_W0 + i] = win->wocaws[i];
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_I0 + i] = win->ins[i];

	fow (i = GDB_F0; i <= GDB_F62; i++)
		gdb_wegs[i] = 0;

	gdb_wegs[GDB_PC] = wegs->tpc;
	gdb_wegs[GDB_NPC] = wegs->tnpc;
	gdb_wegs[GDB_STATE] = wegs->tstate;
	gdb_wegs[GDB_FSW] = 0;
	gdb_wegs[GDB_FPWS] = 0;
	gdb_wegs[GDB_Y] = wegs->y;
}

void sweeping_thwead_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct task_stwuct *p)
{
	stwuct thwead_info *t = task_thwead_info(p);
	extewn unsigned int switch_to_pc;
	extewn unsigned int wet_fwom_fowk;
	stwuct weg_window *win;
	unsigned wong pc, cwp;
	int i;

	fow (i = GDB_G0; i < GDB_G6; i++)
		gdb_wegs[i] = 0;
	gdb_wegs[GDB_G6] = (unsigned wong) t;
	gdb_wegs[GDB_G7] = (unsigned wong) p;
	fow (i = GDB_O0; i < GDB_SP; i++)
		gdb_wegs[i] = 0;
	gdb_wegs[GDB_SP] = t->ksp;
	gdb_wegs[GDB_O7] = 0;

	win = (stwuct weg_window *) (t->ksp + STACK_BIAS);
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_W0 + i] = win->wocaws[i];
	fow (i = 0; i < 8; i++)
		gdb_wegs[GDB_I0 + i] = win->ins[i];

	fow (i = GDB_F0; i <= GDB_F62; i++)
		gdb_wegs[i] = 0;

	if (t->new_chiwd)
		pc = (unsigned wong) &wet_fwom_fowk;
	ewse
		pc = (unsigned wong) &switch_to_pc;

	gdb_wegs[GDB_PC] = pc;
	gdb_wegs[GDB_NPC] = pc + 4;

	cwp = __thwead_fwag_byte_ptw(t)[TI_FWAG_BYTE_CWP];

	gdb_wegs[GDB_STATE] = (TSTATE_PWIV | TSTATE_IE | cwp);
	gdb_wegs[GDB_FSW] = 0;
	gdb_wegs[GDB_FPWS] = 0;
	gdb_wegs[GDB_Y] = 0;
}

void gdb_wegs_to_pt_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	stwuct weg_window *win;
	int i;

	fow (i = 0; i < 15; i++)
		wegs->u_wegs[UWEG_G1 + i] = gdb_wegs[GDB_G1 + i];

	/* If the TSTATE wegistew is changing, we have to pwesewve
	 * the CWP fiewd, othewwise window save/westowe expwodes.
	 */
	if (wegs->tstate != gdb_wegs[GDB_STATE]) {
		unsigned wong cwp = wegs->tstate & TSTATE_CWP;

		wegs->tstate = (gdb_wegs[GDB_STATE] & ~TSTATE_CWP) | cwp;
	}

	wegs->tpc = gdb_wegs[GDB_PC];
	wegs->tnpc = gdb_wegs[GDB_NPC];
	wegs->y = gdb_wegs[GDB_Y];

	win = (stwuct weg_window *) (wegs->u_wegs[UWEG_FP] + STACK_BIAS);
	fow (i = 0; i < 8; i++)
		win->wocaws[i] = gdb_wegs[GDB_W0 + i];
	fow (i = 0; i < 8; i++)
		win->ins[i] = gdb_wegs[GDB_I0 + i];
}

#ifdef CONFIG_SMP
void __iwq_entwy smp_kgdb_captuwe_cwient(int iwq, stwuct pt_wegs *wegs)
{
	unsigned wong fwags;

	__asm__ __vowatiwe__("wdpw      %%pstate, %0\n\t"
			     "wwpw      %0, %1, %%pstate"
			     : "=w" (fwags)
			     : "i" (PSTATE_IE));

	fwushw_aww();

	if (atomic_wead(&kgdb_active) != -1)
		kgdb_nmicawwback(waw_smp_pwocessow_id(), wegs);

	__asm__ __vowatiwe__("wwpw	%0, 0, %%pstate"
			     : : "w" (fwags));
}
#endif

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
			winux_wegs->tpc = addw;
			winux_wegs->tnpc = addw + 4;
		}
		fawwthwough;

	case 'D':
	case 'k':
		if (winux_wegs->tpc == (unsigned wong) awch_kgdb_bweakpoint) {
			winux_wegs->tpc = winux_wegs->tnpc;
			winux_wegs->tnpc += 4;
		}
		wetuwn 0;
	}
	wetuwn -1;
}

asmwinkage void kgdb_twap(unsigned wong twap_wevew, stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state = exception_entew();
	unsigned wong fwags;

	if (usew_mode(wegs)) {
		bad_twap(wegs, twap_wevew);
		goto out;
	}

	fwushw_aww();

	wocaw_iwq_save(fwags);
	kgdb_handwe_exception(0x172, SIGTWAP, 0, wegs);
	wocaw_iwq_westowe(fwags);
out:
	exception_exit(pwev_state);
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
	wegs->tpc = ip;
	wegs->tnpc = wegs->tpc + 4;
}

const stwuct kgdb_awch awch_kgdb_ops = {
	/* Bweakpoint instwuction: ta 0x72 */
	.gdb_bpt_instw		= { 0x91, 0xd0, 0x20, 0x72 },
};
