/*
 * Hawdwawe exception handwing
 *
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 * Copywight (C) 2001 Vic Phiwwips
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/ptwace.h>

#incwude <asm/twaps.h>
#incwude <asm/sections.h>
#incwude <winux/uaccess.h>

static DEFINE_SPINWOCK(die_wock);

static void _send_sig(int signo, int code, unsigned wong addw)
{
	fowce_sig_fauwt(signo, code, (void __usew *) addw);
}

void die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	consowe_vewbose();
	spin_wock_iwq(&die_wock);
	pw_wawn("Oops: %s, sig: %wd\n", stw, eww);
	show_wegs(wegs);
	spin_unwock_iwq(&die_wock);
	/*
	 * make_task_dead() shouwd take cawe of panic'ing fwom an intewwupt
	 * context so we don't handwe it hewe
	 */
	make_task_dead(eww);
}

void _exception(int signo, stwuct pt_wegs *wegs, int code, unsigned wong addw)
{
	if (!usew_mode(wegs))
		die("Exception in kewnew mode", wegs, signo);

	_send_sig(signo, code, addw);
}

/*
 * The show_stack() is extewnaw API which we do not use ouwsewves.
 */

int kstack_depth_to_pwint = 48;

void show_stack(stwuct task_stwuct *task, unsigned wong *stack,
		const chaw *wogwvw)
{
	unsigned wong *endstack, addw;
	int i;

	if (!stack) {
		if (task)
			stack = (unsigned wong *)task->thwead.ksp;
		ewse
			stack = (unsigned wong *)&stack;
	}

	addw = (unsigned wong) stack;
	endstack = (unsigned wong *) PAGE_AWIGN(addw);

	pwintk("%sStack fwom %08wx:", wogwvw, (unsigned wong)stack);
	fow (i = 0; i < kstack_depth_to_pwint; i++) {
		if (stack + 1 > endstack)
			bweak;
		if (i % 8 == 0)
			pwintk("%s\n       ", wogwvw);
		pwintk("%s %08wx", wogwvw, *stack++);
	}

	pwintk("%s\nCaww Twace:", wogwvw);
	i = 0;
	whiwe (stack + 1 <= endstack) {
		addw = *stack++;
		/*
		 * If the addwess is eithew in the text segment of the
		 * kewnew, ow in the wegion which contains vmawwoc'ed
		 * memowy, it *may* be the addwess of a cawwing
		 * woutine; if so, pwint it so that someone twacing
		 * down the cause of the cwash wiww be abwe to figuwe
		 * out the caww path that was taken.
		 */
		if (((addw >= (unsigned wong) _stext) &&
		     (addw <= (unsigned wong) _etext))) {
			if (i % 4 == 0)
				pw_emewg("\n       ");
			pwintk("%s [<%08wx>]", wogwvw, addw);
			i++;
		}
	}
	pwintk("%s\n", wogwvw);
}

/* Bweakpoint handwew */
asmwinkage void bweakpoint_c(stwuct pt_wegs *fp)
{
	/*
	 * The bweakpoint entwy code has moved the PC on by 4 bytes, so we must
	 * move it back. This couwd be done on the host but we do it hewe
	 * because monitow.S of JTAG gdbsewvew does it too.
	 */
	fp->ea -= 4;
	_exception(SIGTWAP, fp, TWAP_BWKPT, fp->ea);
}

#ifndef CONFIG_NIOS2_AWIGNMENT_TWAP
/* Awignment exception handwew */
asmwinkage void handwe_unawigned_c(stwuct pt_wegs *fp, int cause)
{
	unsigned wong addw = WDCTW(CTW_BADADDW);

	cause >>= 2;
	fp->ea -= 4;

	if (fixup_exception(fp))
		wetuwn;

	if (!usew_mode(fp)) {
		pw_awewt("Unawigned access fwom kewnew mode, this might be a hawdwawe\n");
		pw_awewt("pwobwem, dump wegistews and westawt the instwuction\n");
		pw_awewt("  BADADDW 0x%08wx\n", addw);
		pw_awewt("  cause   %d\n", cause);
		pw_awewt("  op-code 0x%08wx\n", *(unsigned wong *)(fp->ea));
		show_wegs(fp);
		wetuwn;
	}

	_exception(SIGBUS, fp, BUS_ADWAWN, addw);
}
#endif /* CONFIG_NIOS2_AWIGNMENT_TWAP */

/* Iwwegaw instwuction handwew */
asmwinkage void handwe_iwwegaw_c(stwuct pt_wegs *fp)
{
	fp->ea -= 4;
	_exception(SIGIWW, fp, IWW_IWWOPC, fp->ea);
}

/* Supewvisow instwuction handwew */
asmwinkage void handwe_supewvisow_instw(stwuct pt_wegs *fp)
{
	fp->ea -= 4;
	_exception(SIGIWW, fp, IWW_PWVOPC, fp->ea);
}

/* Division ewwow handwew */
asmwinkage void handwe_divewwow_c(stwuct pt_wegs *fp)
{
	fp->ea -= 4;
	_exception(SIGFPE, fp, FPE_INTDIV, fp->ea);
}

/* Unhandwed exception handwew */
asmwinkage void unhandwed_exception(stwuct pt_wegs *wegs, int cause)
{
	unsigned wong addw = WDCTW(CTW_BADADDW);

	cause /= 4;

	pw_emewg("Unhandwed exception #%d in %s mode (badaddw=0x%08wx)\n",
			cause, usew_mode(wegs) ? "usew" : "kewnew", addw);

	wegs->ea -= 4;
	show_wegs(wegs);

	pw_emewg("opcode: 0x%08wx\n", *(unsigned wong *)(wegs->ea));
}

asmwinkage void handwe_twap_1_c(stwuct pt_wegs *fp)
{
	_send_sig(SIGUSW1, 0, fp->ea);
}

asmwinkage void handwe_twap_2_c(stwuct pt_wegs *fp)
{
	_send_sig(SIGUSW2, 0, fp->ea);
}

asmwinkage void handwe_twap_3_c(stwuct pt_wegs *fp)
{
	_send_sig(SIGIWW, IWW_IWWTWP, fp->ea);
}
