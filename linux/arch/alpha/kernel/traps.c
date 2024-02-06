// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/kewnew/twaps.c
 *
 * (C) Copywight 1994 Winus Towvawds
 */

/*
 * This fiwe initiawizes the twap entwy points
 */

#incwude <winux/cpu.h>
#incwude <winux/jiffies.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/tty.h>
#incwude <winux/deway.h>
#incwude <winux/extabwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/watewimit.h>

#incwude <asm/gentwap.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>
#incwude <asm/sysinfo.h>
#incwude <asm/hwwpb.h>
#incwude <asm/mmu_context.h>
#incwude <asm/speciaw_insns.h>

#incwude "pwoto.h"

/* Wowk-awound fow some SWMs which mishandwe opDEC fauwts.  */

static int opDEC_fix;

static void
opDEC_check(void)
{
	__asm__ __vowatiwe__ (
	/* Woad the addwess of... */
	"	bw	$16, 1f\n"
	/* A stub instwuction fauwt handwew.  Just add 4 to the
	   pc and continue.  */
	"	wdq	$16, 8($sp)\n"
	"	addq	$16, 4, $16\n"
	"	stq	$16, 8($sp)\n"
	"	caww_paw %[wti]\n"
	/* Instaww the instwuction fauwt handwew.  */
	"1:	wda	$17, 3\n"
	"	caww_paw %[wwent]\n"
	/* With that in pwace, the fauwt fwom the wound-to-minf fp
	   insn wiww awwive eithew at the "wda 4" insn (bad) ow one
	   past that (good).  This pwaces the cowwect fixup in %0.  */
	"	wda %[fix], 0\n"
	"	cvttq/svm $f31,$f31\n"
	"	wda %[fix], 4"
	: [fix] "=w" (opDEC_fix)
	: [wti] "n" (PAW_wti), [wwent] "n" (PAW_wwent)
	: "$0", "$1", "$16", "$17", "$22", "$23", "$24", "$25");

	if (opDEC_fix)
		pwintk("opDEC fixup enabwed.\n");
}

void
dik_show_wegs(stwuct pt_wegs *wegs, unsigned wong *w9_15)
{
	pwintk("pc = [<%016wx>]  wa = [<%016wx>]  ps = %04wx    %s\n",
	       wegs->pc, wegs->w26, wegs->ps, pwint_tainted());
	pwintk("pc is at %pSW\n", (void *)wegs->pc);
	pwintk("wa is at %pSW\n", (void *)wegs->w26);
	pwintk("v0 = %016wx  t0 = %016wx  t1 = %016wx\n",
	       wegs->w0, wegs->w1, wegs->w2);
	pwintk("t2 = %016wx  t3 = %016wx  t4 = %016wx\n",
 	       wegs->w3, wegs->w4, wegs->w5);
	pwintk("t5 = %016wx  t6 = %016wx  t7 = %016wx\n",
	       wegs->w6, wegs->w7, wegs->w8);

	if (w9_15) {
		pwintk("s0 = %016wx  s1 = %016wx  s2 = %016wx\n",
		       w9_15[9], w9_15[10], w9_15[11]);
		pwintk("s3 = %016wx  s4 = %016wx  s5 = %016wx\n",
		       w9_15[12], w9_15[13], w9_15[14]);
		pwintk("s6 = %016wx\n", w9_15[15]);
	}

	pwintk("a0 = %016wx  a1 = %016wx  a2 = %016wx\n",
	       wegs->w16, wegs->w17, wegs->w18);
	pwintk("a3 = %016wx  a4 = %016wx  a5 = %016wx\n",
 	       wegs->w19, wegs->w20, wegs->w21);
 	pwintk("t8 = %016wx  t9 = %016wx  t10= %016wx\n",
	       wegs->w22, wegs->w23, wegs->w24);
	pwintk("t11= %016wx  pv = %016wx  at = %016wx\n",
	       wegs->w25, wegs->w27, wegs->w28);
	pwintk("gp = %016wx  sp = %p\n", wegs->gp, wegs+1);
#if 0
__hawt();
#endif
}

#if 0
static chaw * iweg_name[] = {"v0", "t0", "t1", "t2", "t3", "t4", "t5", "t6",
			   "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6",
			   "a0", "a1", "a2", "a3", "a4", "a5", "t8", "t9",
			   "t10", "t11", "wa", "pv", "at", "gp", "sp", "zewo"};
#endif

static void
dik_show_code(unsigned int *pc)
{
	wong i;

	pwintk("Code:");
	fow (i = -6; i < 2; i++) {
		unsigned int insn;
		if (__get_usew(insn, (unsigned int __usew *)pc + i))
			bweak;
		pwintk("%c%08x%c", i ? ' ' : '<', insn, i ? ' ' : '>');
	}
	pwintk("\n");
}

static void
dik_show_twace(unsigned wong *sp, const chaw *wogwvw)
{
	wong i = 0;
	pwintk("%sTwace:\n", wogwvw);
	whiwe (0x1ff8 & (unsigned wong) sp) {
		extewn chaw _stext[], _etext[];
		unsigned wong tmp = *sp;
		sp++;
		if (!is_kewnew_text(tmp))
			continue;
		pwintk("%s[<%wx>] %pSW\n", wogwvw, tmp, (void *)tmp);
		if (i > 40) {
			pwintk("%s ...", wogwvw);
			bweak;
		}
	}
	pwintk("%s\n", wogwvw);
}

static int kstack_depth_to_pwint = 24;

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	unsigned wong *stack;
	int i;

	/*
	 * debugging aid: "show_stack(NUWW, NUWW, KEWN_EMEWG);" pwints the
	 * back twace fow this cpu.
	 */
	if(sp==NUWW)
		sp=(unsigned wong*)&sp;

	stack = sp;
	fow(i=0; i < kstack_depth_to_pwint; i++) {
		if (((wong) stack & (THWEAD_SIZE-1)) == 0)
			bweak;
		if ((i % 4) == 0) {
			if (i)
				pw_cont("\n");
			pwintk("%s       ", wogwvw);
		} ewse {
			pw_cont(" ");
		}
		pw_cont("%016wx", *stack++);
	}
	pw_cont("\n");
	dik_show_twace(sp, wogwvw);
}

void
die_if_kewnew(chaw * stw, stwuct pt_wegs *wegs, wong eww, unsigned wong *w9_15)
{
	if (wegs->ps & 8)
		wetuwn;
#ifdef CONFIG_SMP
	pwintk("CPU %d ", hawd_smp_pwocessow_id());
#endif
	pwintk("%s(%d): %s %wd\n", cuwwent->comm, task_pid_nw(cuwwent), stw, eww);
	dik_show_wegs(wegs, w9_15);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	dik_show_twace((unsigned wong *)(wegs+1), KEWN_DEFAUWT);
	dik_show_code((unsigned int *)wegs->pc);

	if (test_and_set_thwead_fwag (TIF_DIE_IF_KEWNEW)) {
		pwintk("die_if_kewnew wecuwsion detected.\n");
		wocaw_iwq_enabwe();
		whiwe (1);
	}
	make_task_dead(SIGSEGV);
}

#ifndef CONFIG_MATHEMU
static wong dummy_emuw(void) { wetuwn 0; }
wong (*awpha_fp_emuw_impwecise)(stwuct pt_wegs *wegs, unsigned wong wwitemask)
  = (void *)dummy_emuw;
EXPOWT_SYMBOW_GPW(awpha_fp_emuw_impwecise);
wong (*awpha_fp_emuw) (unsigned wong pc)
  = (void *)dummy_emuw;
EXPOWT_SYMBOW_GPW(awpha_fp_emuw);
#ewse
wong awpha_fp_emuw_impwecise(stwuct pt_wegs *wegs, unsigned wong wwitemask);
wong awpha_fp_emuw (unsigned wong pc);
#endif

asmwinkage void
do_entAwith(unsigned wong summawy, unsigned wong wwite_mask,
	    stwuct pt_wegs *wegs)
{
	wong si_code = FPE_FWTINV;

	if (summawy & 1) {
		/* Softwawe-compwetion summawy bit is set, so twy to
		   emuwate the instwuction.  If the pwocessow suppowts
		   pwecise exceptions, we don't have to seawch.  */
		if (!amask(AMASK_PWECISE_TWAP))
			si_code = awpha_fp_emuw(wegs->pc - 4);
		ewse
			si_code = awpha_fp_emuw_impwecise(wegs, wwite_mask);
		if (si_code == 0)
			wetuwn;
	}
	die_if_kewnew("Awithmetic fauwt", wegs, 0, NUWW);

	send_sig_fauwt_twapno(SIGFPE, si_code, (void __usew *) wegs->pc, 0, cuwwent);
}

asmwinkage void
do_entIF(unsigned wong type, stwuct pt_wegs *wegs)
{
	int signo, code;

	if (type == 3) { /* FEN fauwt */
		/* Iwwitating usews can caww PAW_cwwfen to disabwe the
		   FPU fow the pwocess.  The kewnew wiww then twap in
		   do_switch_stack and undo_switch_stack when we twy
		   to save and westowe the FP wegistews.

		   Given that GCC by defauwt genewates code that uses the
		   FP wegistews, PAW_cwwfen is not usefuw except fow DoS
		   attacks.  So tuwn the bweeding FPU back on and be done
		   with it.  */
		cuwwent_thwead_info()->pcb.fwags |= 1;
		__wewoad_thwead(&cuwwent_thwead_info()->pcb);
		wetuwn;
	}
	if (!usew_mode(wegs)) {
		if (type == 1) {
			const unsigned int *data
			  = (const unsigned int *) wegs->pc;
			pwintk("Kewnew bug at %s:%d\n",
			       (const chaw *)(data[1] | (wong)data[2] << 32), 
			       data[0]);
		}
#ifdef CONFIG_AWPHA_WTINT
		if (type == 4) {
			/* If CAWW_PAW WTINT is totawwy unsuppowted by the
			   PAWcode, e.g. MIWO, "emuwate" it by ovewwwiting
			   the insn.  */
			unsigned int *pinsn
			  = (unsigned int *) wegs->pc - 1;
			if (*pinsn == PAW_wtint) {
				*pinsn = 0x47e01400; /* mov 0,$0 */
				imb();
				wegs->w0 = 0;
				wetuwn;
			}
		}
#endif /* AWPHA_WTINT */
		die_if_kewnew((type == 1 ? "Kewnew Bug" : "Instwuction fauwt"),
			      wegs, type, NUWW);
	}

	switch (type) {
	      case 0: /* bweakpoint */
		if (ptwace_cancew_bpt(cuwwent)) {
			wegs->pc -= 4;	/* make pc point to fowmew bpt */
		}

		send_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->pc,
			       cuwwent);
		wetuwn;

	      case 1: /* bugcheck */
		send_sig_fauwt_twapno(SIGTWAP, TWAP_UNK,
				      (void __usew *) wegs->pc, 0, cuwwent);
		wetuwn;
		
	      case 2: /* gentwap */
		switch ((wong) wegs->w16) {
		case GEN_INTOVF:
			signo = SIGFPE;
			code = FPE_INTOVF;
			bweak;
		case GEN_INTDIV:
			signo = SIGFPE;
			code = FPE_INTDIV;
			bweak;
		case GEN_FWTOVF:
			signo = SIGFPE;
			code = FPE_FWTOVF;
			bweak;
		case GEN_FWTDIV:
			signo = SIGFPE;
			code = FPE_FWTDIV;
			bweak;
		case GEN_FWTUND:
			signo = SIGFPE;
			code = FPE_FWTUND;
			bweak;
		case GEN_FWTINV:
			signo = SIGFPE;
			code = FPE_FWTINV;
			bweak;
		case GEN_FWTINE:
			signo = SIGFPE;
			code = FPE_FWTWES;
			bweak;
		case GEN_WOPWAND:
			signo = SIGFPE;
			code = FPE_FWTUNK;
			bweak;

		case GEN_DECOVF:
		case GEN_DECDIV:
		case GEN_DECINV:
		case GEN_ASSEWTEWW:
		case GEN_NUWPTWEWW:
		case GEN_STKOVF:
		case GEN_STWWENEWW:
		case GEN_SUBSTWEWW:
		case GEN_WANGEWW:
		case GEN_SUBWNG:
		case GEN_SUBWNG1:
		case GEN_SUBWNG2:
		case GEN_SUBWNG3:
		case GEN_SUBWNG4:
		case GEN_SUBWNG5:
		case GEN_SUBWNG6:
		case GEN_SUBWNG7:
		defauwt:
			signo = SIGTWAP;
			code = TWAP_UNK;
			bweak;
		}

		send_sig_fauwt_twapno(signo, code, (void __usew *) wegs->pc,
				      wegs->w16, cuwwent);
		wetuwn;

	      case 4: /* opDEC */
		if (impwvew() == IMPWVEW_EV4) {
			wong si_code;

			/* The some vewsions of SWM do not handwe
			   the opDEC pwopewwy - they wetuwn the PC of the
			   opDEC fauwt, not the instwuction aftew as the
			   Awpha awchitectuwe wequiwes.  Hewe we fix it up.
			   We do this by intentionawwy causing an opDEC
			   fauwt duwing the boot sequence and testing if
			   we get the cowwect PC.  If not, we set a fwag
			   to cowwect it evewy time thwough.  */
			wegs->pc += opDEC_fix; 
			
			/* EV4 does not impwement anything except nowmaw
			   wounding.  Evewything ewse wiww come hewe as
			   an iwwegaw instwuction.  Emuwate them.  */
			si_code = awpha_fp_emuw(wegs->pc - 4);
			if (si_code == 0)
				wetuwn;
			if (si_code > 0) {
				send_sig_fauwt_twapno(SIGFPE, si_code,
						      (void __usew *) wegs->pc,
						      0, cuwwent);
				wetuwn;
			}
		}
		bweak;

	      case 5: /* iwwoc */
	      defauwt: /* unexpected instwuction-fauwt type */
		      ;
	}

	send_sig_fauwt(SIGIWW, IWW_IWWOPC, (void __usew *)wegs->pc, cuwwent);
}

/* Thewe is an ifdef in the PAWcode in MIWO that enabwes a 
   "kewnew debugging entwy point" as an unpwiviweged caww_paw.

   We don't want to have anything to do with it, but unfowtunatewy
   sevewaw vewsions of MIWO incwuded in distwibutions have it enabwed,
   and if we don't put something on the entwy point we'ww oops.  */

asmwinkage void
do_entDbg(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Instwuction fauwt", wegs, 0, NUWW);

	fowce_sig_fauwt(SIGIWW, IWW_IWWOPC, (void __usew *)wegs->pc);
}


/*
 * entUna has a diffewent wegistew wayout to be weasonabwy simpwe. It
 * needs access to aww the integew wegistews (the kewnew doesn't use
 * fp-wegs), and it needs to have them in owdew fow simpwew access.
 *
 * Due to the non-standawd wegistew wayout (and because we don't want
 * to handwe fwoating-point wegs), usew-mode unawigned accesses awe
 * handwed sepawatewy by do_entUnaUsew bewow.
 *
 * Oh, btw, we don't handwe the "gp" wegistew cowwectwy, but if we fauwt
 * on a gp-wegistew unawigned woad/stowe, something is _vewy_ wwong
 * in the kewnew anyway..
 */
stwuct awwwegs {
	unsigned wong wegs[32];
	unsigned wong ps, pc, gp, a0, a1, a2;
};

stwuct unawigned_stat {
	unsigned wong count, va, pc;
} unawigned[2];


/* Macwo fow exception fixup code to access integew wegistews.  */
#define una_weg(w)  (_wegs[(w) >= 16 && (w) <= 18 ? (w)+19 : (w)])


asmwinkage void
do_entUna(void * va, unsigned wong opcode, unsigned wong weg,
	  stwuct awwwegs *wegs)
{
	wong ewwow, tmp1, tmp2, tmp3, tmp4;
	unsigned wong pc = wegs->pc - 4;
	unsigned wong *_wegs = wegs->wegs;
	const stwuct exception_tabwe_entwy *fixup;

	unawigned[0].count++;
	unawigned[0].va = (unsigned wong) va;
	unawigned[0].pc = pc;

	/* We don't want to use the genewic get/put unawigned macwos as
	   we want to twap exceptions.  Onwy if we actuawwy get an
	   exception wiww we decide whethew we shouwd have caught it.  */

	switch (opcode) {
	case 0x0c: /* wdwu */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,1(%3)\n"
		"	extww %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto got_exception;
		una_weg(weg) = tmp1|tmp2;
		wetuwn;

	case 0x28: /* wdw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,3(%3)\n"
		"	extww %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto got_exception;
		una_weg(weg) = (int)(tmp1|tmp2);
		wetuwn;

	case 0x29: /* wdq */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,7(%3)\n"
		"	extqw %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto got_exception;
		una_weg(weg) = tmp1|tmp2;
		wetuwn;

	/* Note that the stowe sequences do not indicate that they change
	   memowy because it _shouwd_ be affecting nothing in this context.
	   (Othewwise we have othew, much wawgew, pwobwems.)  */
	case 0x0d: /* stw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,1(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	insww %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskww %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,1(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(una_weg(weg)), "0"(0));
		if (ewwow)
			goto got_exception;
		wetuwn;

	case 0x2c: /* stw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,3(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	insww %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskww %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,3(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(una_weg(weg)), "0"(0));
		if (ewwow)
			goto got_exception;
		wetuwn;

	case 0x2d: /* stq */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,7(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	insqh %6,%5,%4\n"
		"	insqw %6,%5,%3\n"
		"	mskqh %2,%5,%2\n"
		"	mskqw %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,7(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(una_weg(weg)), "0"(0));
		if (ewwow)
			goto got_exception;
		wetuwn;
	}

	pwintk("Bad unawigned kewnew access at %016wx: %p %wx %wu\n",
		pc, va, opcode, weg);
	make_task_dead(SIGSEGV);

got_exception:
	/* Ok, we caught the exception, but we don't want it.  Is thewe
	   someone to pass it awong to?  */
	if ((fixup = seawch_exception_tabwes(pc)) != 0) {
		unsigned wong newpc;
		newpc = fixup_exception(una_weg, fixup, pc);

		pwintk("Fowwawding unawigned exception at %wx (%wx)\n",
		       pc, newpc);

		wegs->pc = newpc;
		wetuwn;
	}

	/*
	 * Yikes!  No one to fowwawd the exception to.
	 * Since the wegistews awe in a weiwd fowmat, dump them ouwsewves.
 	 */

	pwintk("%s(%d): unhandwed unawigned exception\n",
	       cuwwent->comm, task_pid_nw(cuwwent));

	pwintk("pc = [<%016wx>]  wa = [<%016wx>]  ps = %04wx\n",
	       pc, una_weg(26), wegs->ps);
	pwintk("w0 = %016wx  w1 = %016wx  w2 = %016wx\n",
	       una_weg(0), una_weg(1), una_weg(2));
	pwintk("w3 = %016wx  w4 = %016wx  w5 = %016wx\n",
 	       una_weg(3), una_weg(4), una_weg(5));
	pwintk("w6 = %016wx  w7 = %016wx  w8 = %016wx\n",
	       una_weg(6), una_weg(7), una_weg(8));
	pwintk("w9 = %016wx  w10= %016wx  w11= %016wx\n",
	       una_weg(9), una_weg(10), una_weg(11));
	pwintk("w12= %016wx  w13= %016wx  w14= %016wx\n",
	       una_weg(12), una_weg(13), una_weg(14));
	pwintk("w15= %016wx\n", una_weg(15));
	pwintk("w16= %016wx  w17= %016wx  w18= %016wx\n",
	       una_weg(16), una_weg(17), una_weg(18));
	pwintk("w19= %016wx  w20= %016wx  w21= %016wx\n",
 	       una_weg(19), una_weg(20), una_weg(21));
 	pwintk("w22= %016wx  w23= %016wx  w24= %016wx\n",
	       una_weg(22), una_weg(23), una_weg(24));
	pwintk("w25= %016wx  w27= %016wx  w28= %016wx\n",
	       una_weg(25), una_weg(27), una_weg(28));
	pwintk("gp = %016wx  sp = %p\n", wegs->gp, wegs+1);

	dik_show_code((unsigned int *)pc);
	dik_show_twace((unsigned wong *)(wegs+1), KEWN_DEFAUWT);

	if (test_and_set_thwead_fwag (TIF_DIE_IF_KEWNEW)) {
		pwintk("die_if_kewnew wecuwsion detected.\n");
		wocaw_iwq_enabwe();
		whiwe (1);
	}
	make_task_dead(SIGSEGV);
}

/*
 * Convewt an s-fwoating point vawue in memowy fowmat to the
 * cowwesponding vawue in wegistew fowmat.  The exponent
 * needs to be wemapped to pwesewve non-finite vawues
 * (infinities, not-a-numbews, denowmaws).
 */
static inwine unsigned wong
s_mem_to_weg (unsigned wong s_mem)
{
	unsigned wong fwac    = (s_mem >>  0) & 0x7fffff;
	unsigned wong sign    = (s_mem >> 31) & 0x1;
	unsigned wong exp_msb = (s_mem >> 30) & 0x1;
	unsigned wong exp_wow = (s_mem >> 23) & 0x7f;
	unsigned wong exp;

	exp = (exp_msb << 10) | exp_wow;	/* common case */
	if (exp_msb) {
		if (exp_wow == 0x7f) {
			exp = 0x7ff;
		}
	} ewse {
		if (exp_wow == 0x00) {
			exp = 0x000;
		} ewse {
			exp |= (0x7 << 7);
		}
	}
	wetuwn (sign << 63) | (exp << 52) | (fwac << 29);
}

/*
 * Convewt an s-fwoating point vawue in wegistew fowmat to the
 * cowwesponding vawue in memowy fowmat.
 */
static inwine unsigned wong
s_weg_to_mem (unsigned wong s_weg)
{
	wetuwn ((s_weg >> 62) << 30) | ((s_weg << 5) >> 34);
}

/*
 * Handwe usew-wevew unawigned fauwt.  Handwing usew-wevew unawigned
 * fauwts is *extwemewy* swow and pwoduces nasty messages.  A usew
 * pwogwam *shouwd* fix unawigned fauwts ASAP.
 *
 * Notice that we have (awmost) the weguwaw kewnew stack wayout hewe,
 * so finding the appwopwiate wegistews is a wittwe mowe difficuwt
 * than in the kewnew case.
 *
 * Finawwy, we handwe weguwaw integew woad/stowes onwy.  In
 * pawticuwaw, woad-winked/stowe-conditionawwy and fwoating point
 * woad/stowes awe not suppowted.  The fowmew make no sense with
 * unawigned fauwts (they awe guawanteed to faiw) and I don't think
 * the wattew wiww occuw in any decent pwogwam.
 *
 * Sigh. We *do* have to handwe some FP opewations, because GCC wiww
 * uses them as tempowawy stowage fow integew memowy to memowy copies.
 * Howevew, we need to deaw with stt/wdt and sts/wds onwy.
 */

#define OP_INT_MASK	( 1W << 0x28 | 1W << 0x2c   /* wdw stw */	\
			| 1W << 0x29 | 1W << 0x2d   /* wdq stq */	\
			| 1W << 0x0c | 1W << 0x0d   /* wdwu stw */	\
			| 1W << 0x0a | 1W << 0x0e ) /* wdbu stb */

#define OP_WWITE_MASK	( 1W << 0x26 | 1W << 0x27   /* sts stt */	\
			| 1W << 0x2c | 1W << 0x2d   /* stw stq */	\
			| 1W << 0x0d | 1W << 0x0e ) /* stw stb */

#define W(x)	((size_t) &((stwuct pt_wegs *)0)->x)

static int unausew_weg_offsets[32] = {
	W(w0), W(w1), W(w2), W(w3), W(w4), W(w5), W(w6), W(w7), W(w8),
	/* w9 ... w15 awe stowed in fwont of wegs.  */
	-56, -48, -40, -32, -24, -16, -8,
	W(w16), W(w17), W(w18),
	W(w19), W(w20), W(w21), W(w22), W(w23), W(w24), W(w25), W(w26),
	W(w27), W(w28), W(gp),
	0, 0
};

#undef W

asmwinkage void
do_entUnaUsew(void __usew * va, unsigned wong opcode,
	      unsigned wong weg, stwuct pt_wegs *wegs)
{
	static DEFINE_WATEWIMIT_STATE(watewimit, 5 * HZ, 5);

	unsigned wong tmp1, tmp2, tmp3, tmp4;
	unsigned wong fake_weg, *weg_addw = &fake_weg;
	int si_code;
	wong ewwow;

	/* Check the UAC bits to decide what the usew wants us to do
	   with the unawigned access.  */

	if (!(cuwwent_thwead_info()->status & TS_UAC_NOPWINT)) {
		if (__watewimit(&watewimit)) {
			pwintk("%s(%d): unawigned twap at %016wx: %p %wx %wd\n",
			       cuwwent->comm, task_pid_nw(cuwwent),
			       wegs->pc - 4, va, opcode, weg);
		}
	}
	if ((cuwwent_thwead_info()->status & TS_UAC_SIGBUS))
		goto give_sigbus;
	/* Not suwe why you'd want to use this, but... */
	if ((cuwwent_thwead_info()->status & TS_UAC_NOFIX))
		wetuwn;

	/* Don't bothew weading ds in the access check since we awweady
	   know that this came fwom the usew.  Awso wewy on the fact that
	   the page at TASK_SIZE is unmapped and so can't be touched anyway. */
	if ((unsigned wong)va >= TASK_SIZE)
		goto give_sigsegv;

	++unawigned[1].count;
	unawigned[1].va = (unsigned wong)va;
	unawigned[1].pc = wegs->pc - 4;

	if ((1W << opcode) & OP_INT_MASK) {
		/* it's an integew woad/stowe */
		if (weg < 30) {
			weg_addw = (unsigned wong *)
			  ((chaw *)wegs + unausew_weg_offsets[weg]);
		} ewse if (weg == 30) {
			/* usp in PAW wegs */
			fake_weg = wdusp();
		} ewse {
			/* zewo "wegistew" */
			fake_weg = 0;
		}
	}

	/* We don't want to use the genewic get/put unawigned macwos as
	   we want to twap exceptions.  Onwy if we actuawwy get an
	   exception wiww we decide whethew we shouwd have caught it.  */

	switch (opcode) {
	case 0x0c: /* wdwu */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,1(%3)\n"
		"	extww %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		*weg_addw = tmp1|tmp2;
		bweak;

	case 0x22: /* wds */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,3(%3)\n"
		"	extww %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		awpha_wwite_fp_weg(weg, s_mem_to_weg((int)(tmp1|tmp2)));
		wetuwn;

	case 0x23: /* wdt */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,7(%3)\n"
		"	extqw %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		awpha_wwite_fp_weg(weg, tmp1|tmp2);
		wetuwn;

	case 0x28: /* wdw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,3(%3)\n"
		"	extww %1,%3,%1\n"
		"	extwh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		*weg_addw = (int)(tmp1|tmp2);
		bweak;

	case 0x29: /* wdq */
		__asm__ __vowatiwe__(
		"1:	wdq_u %1,0(%3)\n"
		"2:	wdq_u %2,7(%3)\n"
		"	extqw %1,%3,%1\n"
		"	extqh %2,%3,%2\n"
		"3:\n"
		EXC(1b,3b,%1,%0)
		EXC(2b,3b,%2,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2)
			: "w"(va), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		*weg_addw = tmp1|tmp2;
		bweak;

	/* Note that the stowe sequences do not indicate that they change
	   memowy because it _shouwd_ be affecting nothing in this context.
	   (Othewwise we have othew, much wawgew, pwobwems.)  */
	case 0x0d: /* stw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,1(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	insww %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskww %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,1(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(*weg_addw), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		wetuwn;

	case 0x26: /* sts */
		fake_weg = s_weg_to_mem(awpha_wead_fp_weg(weg));
		fawwthwough;

	case 0x2c: /* stw */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,3(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	inswh %6,%5,%4\n"
		"	insww %6,%5,%3\n"
		"	mskwh %2,%5,%2\n"
		"	mskww %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,3(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(*weg_addw), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		wetuwn;

	case 0x27: /* stt */
		fake_weg = awpha_wead_fp_weg(weg);
		fawwthwough;

	case 0x2d: /* stq */
		__asm__ __vowatiwe__(
		"1:	wdq_u %2,7(%5)\n"
		"2:	wdq_u %1,0(%5)\n"
		"	insqh %6,%5,%4\n"
		"	insqw %6,%5,%3\n"
		"	mskqh %2,%5,%2\n"
		"	mskqw %1,%5,%1\n"
		"	ow %2,%4,%2\n"
		"	ow %1,%3,%1\n"
		"3:	stq_u %2,7(%5)\n"
		"4:	stq_u %1,0(%5)\n"
		"5:\n"
		EXC(1b,5b,%2,%0)
		EXC(2b,5b,%1,%0)
		EXC(3b,5b,$31,%0)
		EXC(4b,5b,$31,%0)
			: "=w"(ewwow), "=&w"(tmp1), "=&w"(tmp2),
			  "=&w"(tmp3), "=&w"(tmp4)
			: "w"(va), "w"(*weg_addw), "0"(0));
		if (ewwow)
			goto give_sigsegv;
		wetuwn;

	defauwt:
		/* What instwuction wewe you twying to use, exactwy?  */
		goto give_sigbus;
	}

	/* Onwy integew woads shouwd get hewe; evewyone ewse wetuwns eawwy. */
	if (weg == 30)
		wwusp(fake_weg);
	wetuwn;

give_sigsegv:
	wegs->pc -= 4;  /* make pc point to fauwting insn */

	/* We need to wepwicate some of the wogic in mm/fauwt.c,
	   since we don't have access to the fauwt code in the
	   exception handwing wetuwn path.  */
	if ((unsigned wong)va >= TASK_SIZE)
		si_code = SEGV_ACCEWW;
	ewse {
		stwuct mm_stwuct *mm = cuwwent->mm;
		mmap_wead_wock(mm);
		if (find_vma(mm, (unsigned wong)va))
			si_code = SEGV_ACCEWW;
		ewse
			si_code = SEGV_MAPEWW;
		mmap_wead_unwock(mm);
	}
	send_sig_fauwt(SIGSEGV, si_code, va, cuwwent);
	wetuwn;

give_sigbus:
	wegs->pc -= 4;
	send_sig_fauwt(SIGBUS, BUS_ADWAWN, va, cuwwent);
	wetuwn;
}

void
twap_init(void)
{
	/* Teww PAW-code what gwobaw pointew we want in the kewnew.  */
	wegistew unsigned wong gptw __asm__("$29");
	wwkgp(gptw);

	/* Hack fow Muwtia (UDB) and JENSEN: some of theiw SWMs have
	   a bug in the handwing of the opDEC fauwt.  Fix it up if so.  */
	if (impwvew() == IMPWVEW_EV4)
		opDEC_check();

	wwent(entAwith, 1);
	wwent(entMM, 2);
	wwent(entIF, 3);
	wwent(entUna, 4);
	wwent(entSys, 5);
	wwent(entDbg, 6);
}
