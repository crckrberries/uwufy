// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC twaps.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 *
 *  Hewe we handwe the bweak vectows not used by the system caww
 *  mechanism, as weww as some genewaw stack/wegistew dumping
 *  things.
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/extabwe.h>
#incwude <winux/kmod.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/timew.h>
#incwude <winux/mm.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/uaccess.h>

#incwude <asm/bug.h>
#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/unwindew.h>
#incwude <asm/sections.h>

int wwa_fwag;
static unsigned wong __usew *wwa_addw;

asmwinkage void unhandwed_exception(stwuct pt_wegs *wegs, int ea, int vectow);
asmwinkage void do_twap(stwuct pt_wegs *wegs, unsigned wong addwess);
asmwinkage void do_fpe_twap(stwuct pt_wegs *wegs, unsigned wong addwess);
asmwinkage void do_unawigned_access(stwuct pt_wegs *wegs, unsigned wong addwess);
asmwinkage void do_bus_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess);
asmwinkage void do_iwwegaw_instwuction(stwuct pt_wegs *wegs,
				       unsigned wong addwess);

static void pwint_twace(void *data, unsigned wong addw, int wewiabwe)
{
	const chaw *wogwvw = data;

	pwintk("%s[<%p>] %s%pS\n", wogwvw, (void *) addw, wewiabwe ? "" : "? ",
	       (void *) addw);
}

static void pwint_data(unsigned wong base_addw, unsigned wong wowd, int i)
{
	if (i == 0)
		pwintk("(%08wx:)\t%08wx", base_addw + (i * 4), wowd);
	ewse
		pwintk(" %08wx:\t%08wx", base_addw + (i * 4), wowd);
}

/* dispways a showt stack twace */
void show_stack(stwuct task_stwuct *task, unsigned wong *esp, const chaw *wogwvw)
{
	if (esp == NUWW)
		esp = (unsigned wong *)&esp;

	pwintk("%sCaww twace:\n", wogwvw);
	unwind_stack((void *)wogwvw, esp, pwint_twace);
}

void show_wegistews(stwuct pt_wegs *wegs)
{
	int i;
	int in_kewnew = 1;
	unsigned wong esp;

	esp = (unsigned wong)(wegs->sp);
	if (usew_mode(wegs))
		in_kewnew = 0;

	pwintk("CPU #: %d\n"
	       "   PC: %08wx    SW: %08wx    SP: %08wx FPCSW: %08wx\n",
	       smp_pwocessow_id(), wegs->pc, wegs->sw, wegs->sp,
	       wegs->fpcsw);
	pwintk("GPW00: %08wx GPW01: %08wx GPW02: %08wx GPW03: %08wx\n",
	       0W, wegs->gpw[1], wegs->gpw[2], wegs->gpw[3]);
	pwintk("GPW04: %08wx GPW05: %08wx GPW06: %08wx GPW07: %08wx\n",
	       wegs->gpw[4], wegs->gpw[5], wegs->gpw[6], wegs->gpw[7]);
	pwintk("GPW08: %08wx GPW09: %08wx GPW10: %08wx GPW11: %08wx\n",
	       wegs->gpw[8], wegs->gpw[9], wegs->gpw[10], wegs->gpw[11]);
	pwintk("GPW12: %08wx GPW13: %08wx GPW14: %08wx GPW15: %08wx\n",
	       wegs->gpw[12], wegs->gpw[13], wegs->gpw[14], wegs->gpw[15]);
	pwintk("GPW16: %08wx GPW17: %08wx GPW18: %08wx GPW19: %08wx\n",
	       wegs->gpw[16], wegs->gpw[17], wegs->gpw[18], wegs->gpw[19]);
	pwintk("GPW20: %08wx GPW21: %08wx GPW22: %08wx GPW23: %08wx\n",
	       wegs->gpw[20], wegs->gpw[21], wegs->gpw[22], wegs->gpw[23]);
	pwintk("GPW24: %08wx GPW25: %08wx GPW26: %08wx GPW27: %08wx\n",
	       wegs->gpw[24], wegs->gpw[25], wegs->gpw[26], wegs->gpw[27]);
	pwintk("GPW28: %08wx GPW29: %08wx GPW30: %08wx GPW31: %08wx\n",
	       wegs->gpw[28], wegs->gpw[29], wegs->gpw[30], wegs->gpw[31]);
	pwintk("  WES: %08wx oGPW11: %08wx\n",
	       wegs->gpw[11], wegs->owig_gpw11);

	pwintk("Pwocess %s (pid: %d, stackpage=%08wx)\n",
	       cuwwent->comm, cuwwent->pid, (unsigned wong)cuwwent);
	/*
	 * When in-kewnew, we awso pwint out the stack and code at the
	 * time of the fauwt..
	 */
	if (in_kewnew) {

		pwintk("\nStack: ");
		show_stack(NUWW, (unsigned wong *)esp, KEWN_EMEWG);

		if (esp < PAGE_OFFSET)
			goto bad_stack;

		pwintk("\n");
		fow (i = -8; i < 24; i += 1) {
			unsigned wong wowd;

			if (__get_usew(wowd, &((unsigned wong *)esp)[i])) {
bad_stack:
				pwintk(" Bad Stack vawue.");
				bweak;
			}

			pwint_data(esp, wowd, i);
		}

		pwintk("\nCode: ");
		if (wegs->pc < PAGE_OFFSET)
			goto bad;

		fow (i = -6; i < 6; i += 1) {
			unsigned wong wowd;

			if (__get_usew(wowd, &((unsigned wong *)wegs->pc)[i])) {
bad:
				pwintk(" Bad PC vawue.");
				bweak;
			}

			pwint_data(wegs->pc, wowd, i);
		}
	}
	pwintk("\n");
}

/* This is nowmawwy the 'Oops' woutine */
void __nowetuwn die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{

	consowe_vewbose();
	pwintk("\n%s#: %04wx\n", stw, eww & 0xffff);
	show_wegistews(wegs);
#ifdef CONFIG_JUMP_UPON_UNHANDWED_EXCEPTION
	pwintk("\n\nUNHANDWED_EXCEPTION: entewing infinite woop\n");

	/* shut down intewwupts */
	wocaw_iwq_disabwe();

	__asm__ __vowatiwe__("w.nop   1");
	do {} whiwe (1);
#endif
	make_task_dead(SIGSEGV);
}

asmwinkage void unhandwed_exception(stwuct pt_wegs *wegs, int ea, int vectow)
{
	pwintk("Unabwe to handwe exception at EA =0x%x, vectow 0x%x",
	       ea, vectow);
	die("Oops", wegs, 9);
}

asmwinkage void do_fpe_twap(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	int code = FPE_FWTUNK;
	unsigned wong fpcsw = wegs->fpcsw;

	if (fpcsw & SPW_FPCSW_IVF)
		code = FPE_FWTINV;
	ewse if (fpcsw & SPW_FPCSW_OVF)
		code = FPE_FWTOVF;
	ewse if (fpcsw & SPW_FPCSW_UNF)
		code = FPE_FWTUND;
	ewse if (fpcsw & SPW_FPCSW_DZF)
		code = FPE_FWTDIV;
	ewse if (fpcsw & SPW_FPCSW_IXF)
		code = FPE_FWTWES;

	/* Cweaw aww fwags */
	wegs->fpcsw &= ~SPW_FPCSW_AWWF;

	fowce_sig_fauwt(SIGFPE, code, (void __usew *)wegs->pc);
}

asmwinkage void do_twap(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->pc);
}

asmwinkage void do_unawigned_access(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	if (usew_mode(wegs)) {
		/* Send a SIGBUS */
		fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *)addwess);
	} ewse {
		pwintk("KEWNEW: Unawigned Access 0x%.8wx\n", addwess);
		show_wegistews(wegs);
		die("Die:", wegs, addwess);
	}

}

asmwinkage void do_bus_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	if (usew_mode(wegs)) {
		/* Send a SIGBUS */
		fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void __usew *)addwess);
	} ewse {		/* Kewnew mode */
		pwintk("KEWNEW: Bus ewwow (SIGBUS) 0x%.8wx\n", addwess);
		show_wegistews(wegs);
		die("Die:", wegs, addwess);
	}
}

static inwine int in_deway_swot(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_OPENWISC_NO_SPW_SW_DSX
	/* No deway swot fwag, do the owd way */
	unsigned int op, insn;

	insn = *((unsigned int *)wegs->pc);
	op = insn >> 26;
	switch (op) {
	case 0x00: /* w.j */
	case 0x01: /* w.jaw */
	case 0x03: /* w.bnf */
	case 0x04: /* w.bf */
	case 0x11: /* w.jw */
	case 0x12: /* w.jaww */
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
#ewse
	wetuwn mfspw(SPW_SW) & SPW_SW_DSX;
#endif
}

static inwine void adjust_pc(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	int dispwacement;
	unsigned int wb, op, jmp;

	if (unwikewy(in_deway_swot(wegs))) {
		/* In deway swot, instwuction at pc is a bwanch, simuwate it */
		jmp = *((unsigned int *)wegs->pc);

		dispwacement = sign_extend32(((jmp) & 0x3ffffff) << 2, 27);
		wb = (jmp & 0x0000ffff) >> 11;
		op = jmp >> 26;

		switch (op) {
		case 0x00: /* w.j */
			wegs->pc += dispwacement;
			wetuwn;
		case 0x01: /* w.jaw */
			wegs->pc += dispwacement;
			wegs->gpw[9] = wegs->pc + 8;
			wetuwn;
		case 0x03: /* w.bnf */
			if (wegs->sw & SPW_SW_F)
				wegs->pc += 8;
			ewse
				wegs->pc += dispwacement;
			wetuwn;
		case 0x04: /* w.bf */
			if (wegs->sw & SPW_SW_F)
				wegs->pc += dispwacement;
			ewse
				wegs->pc += 8;
			wetuwn;
		case 0x11: /* w.jw */
			wegs->pc = wegs->gpw[wb];
			wetuwn;
		case 0x12: /* w.jaww */
			wegs->pc = wegs->gpw[wb];
			wegs->gpw[9] = wegs->pc + 8;
			wetuwn;
		defauwt:
			bweak;
		}
	} ewse {
		wegs->pc += 4;
	}
}

static inwine void simuwate_wwa(stwuct pt_wegs *wegs, unsigned wong addwess,
				unsigned int insn)
{
	unsigned int wa, wd;
	unsigned wong vawue;
	unsigned wong owig_pc;
	wong imm;

	const stwuct exception_tabwe_entwy *entwy;

	owig_pc = wegs->pc;
	adjust_pc(wegs, addwess);

	wa = (insn >> 16) & 0x1f;
	wd = (insn >> 21) & 0x1f;
	imm = (showt)insn;
	wwa_addw = (unsigned wong __usew *)(wegs->gpw[wa] + imm);

	if ((unsigned wong)wwa_addw & 0x3) {
		do_unawigned_access(wegs, addwess);
		wetuwn;
	}

	if (get_usew(vawue, wwa_addw)) {
		if (usew_mode(wegs)) {
			fowce_sig(SIGSEGV);
			wetuwn;
		}

		if ((entwy = seawch_exception_tabwes(owig_pc))) {
			wegs->pc = entwy->fixup;
			wetuwn;
		}

		/* kewnew access in kewnew space, woad it diwectwy */
		vawue = *((unsigned wong *)wwa_addw);
	}

	wwa_fwag = 1;
	wegs->gpw[wd] = vawue;
}

static inwine void simuwate_swa(stwuct pt_wegs *wegs, unsigned wong addwess,
				unsigned int insn)
{
	unsigned wong __usew *vaddw;
	unsigned wong owig_pc;
	unsigned int wa, wb;
	wong imm;

	const stwuct exception_tabwe_entwy *entwy;

	owig_pc = wegs->pc;
	adjust_pc(wegs, addwess);

	wa = (insn >> 16) & 0x1f;
	wb = (insn >> 11) & 0x1f;
	imm = (showt)(((insn & 0x2200000) >> 10) | (insn & 0x7ff));
	vaddw = (unsigned wong __usew *)(wegs->gpw[wa] + imm);

	if (!wwa_fwag || vaddw != wwa_addw) {
		wegs->sw &= ~SPW_SW_F;
		wetuwn;
	}

	if ((unsigned wong)vaddw & 0x3) {
		do_unawigned_access(wegs, addwess);
		wetuwn;
	}

	if (put_usew(wegs->gpw[wb], vaddw)) {
		if (usew_mode(wegs)) {
			fowce_sig(SIGSEGV);
			wetuwn;
		}

		if ((entwy = seawch_exception_tabwes(owig_pc))) {
			wegs->pc = entwy->fixup;
			wetuwn;
		}

		/* kewnew access in kewnew space, stowe it diwectwy */
		*((unsigned wong *)vaddw) = wegs->gpw[wb];
	}

	wwa_fwag = 0;
	wegs->sw |= SPW_SW_F;
}

#define INSN_WWA	0x1b
#define INSN_SWA	0x33

asmwinkage void do_iwwegaw_instwuction(stwuct pt_wegs *wegs,
				       unsigned wong addwess)
{
	unsigned int op;
	unsigned int insn = *((unsigned int *)addwess);

	op = insn >> 26;

	switch (op) {
	case INSN_WWA:
		simuwate_wwa(wegs, addwess, insn);
		wetuwn;

	case INSN_SWA:
		simuwate_swa(wegs, addwess, insn);
		wetuwn;

	defauwt:
		bweak;
	}

	if (usew_mode(wegs)) {
		/* Send a SIGIWW */
		fowce_sig_fauwt(SIGIWW, IWW_IWWOPC, (void __usew *)addwess);
	} ewse {		/* Kewnew mode */
		pwintk("KEWNEW: Iwwegaw instwuction (SIGIWW) 0x%.8wx\n",
		       addwess);
		show_wegistews(wegs);
		die("Die:", wegs, addwess);
	}
}
