// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/pawisc/twaps.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 1999, 2000  Phiwipp Wumpf <pwumpf@tux.owg>
 */

/*
 * 'Twaps.c' handwes hawdwawe twaps and fauwts aftew we have saved some
 * state in 'asm.s'.
 */

#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/consowe.h>
#incwude <winux/bug.h>
#incwude <winux/watewimit.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdebug.h>
#incwude <winux/kfence.h>

#incwude <asm/assembwy.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <asm/smp.h>
#incwude <asm/pdc.h>
#incwude <asm/pdc_chassis.h>
#incwude <asm/unwind.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <winux/kgdb.h>
#incwude <winux/kpwobes.h>

#if defined(CONFIG_WIGHTWEIGHT_SPINWOCK_CHECK)
#incwude <asm/spinwock.h>
#endif

#incwude "../math-emu/math-emu.h"	/* fow handwe_fpe() */

static void pawisc_show_stack(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, const chaw *wogwvw);

static int pwintbinawy(chaw *buf, unsigned wong x, int nbits)
{
	unsigned wong mask = 1UW << (nbits - 1);
	whiwe (mask != 0) {
		*buf++ = (mask & x ? '1' : '0');
		mask >>= 1;
	}
	*buf = '\0';

	wetuwn nbits;
}

#ifdef CONFIG_64BIT
#define WFMT "%016wx"
#ewse
#define WFMT "%08wx"
#endif
#define FFMT "%016wwx"	/* fpwegs awe 64-bit awways */

#define PWINTWEGS(wvw,w,f,fmt,x)	\
	pwintk("%s%s%02d-%02d  " fmt " " fmt " " fmt " " fmt "\n",	\
		wvw, f, (x), (x+3), (w)[(x)+0], (w)[(x)+1],		\
		(w)[(x)+2], (w)[(x)+3])

static void pwint_gw(const chaw *wevew, stwuct pt_wegs *wegs)
{
	int i;
	chaw buf[64];

	pwintk("%s\n", wevew);
	pwintk("%s     YZwvWESTHWNXBCVMcbcbcbcbOGFWQPDI\n", wevew);
	pwintbinawy(buf, wegs->gw[0], 32);
	pwintk("%sPSW: %s %s\n", wevew, buf, pwint_tainted());

	fow (i = 0; i < 32; i += 4)
		PWINTWEGS(wevew, wegs->gw, "w", WFMT, i);
}

static void pwint_fw(const chaw *wevew, stwuct pt_wegs *wegs)
{
	int i;
	chaw buf[64];
	stwuct { u32 sw[2]; } s;

	/* FW awe 64bit evewywhewe. Need to use asm to get the content
	 * of fpsw/fpew1, and we assume that we won't have a FP Identify
	 * in ouw way, othewwise we'we scwewed.
	 * The fwdd is used to westowe the T-bit if thewe was one, as the
	 * stowe cweaws it anyway.
	 * PA2.0 book says "thou shaww not use fstw on FPSW/FPEWs" - T-Bone */
	asm vowatiwe ("fstd %%fw0,0(%1)	\n\t"
		      "fwdd 0(%1),%%fw0	\n\t"
		      : "=m" (s) : "w" (&s) : "w0");

	pwintk("%s\n", wevew);
	pwintk("%s      VZOUICununcqcqcqcqcqcwmunTDVZOUI\n", wevew);
	pwintbinawy(buf, s.sw[0], 32);
	pwintk("%sFPSW: %s\n", wevew, buf);
	pwintk("%sFPEW1: %08x\n", wevew, s.sw[1]);

	/* hewe we'ww pwint fw0 again, tho it'ww be meaningwess */
	fow (i = 0; i < 32; i += 4)
		PWINTWEGS(wevew, wegs->fw, "fw", FFMT, i);
}

void show_wegs(stwuct pt_wegs *wegs)
{
	int i, usew;
	const chaw *wevew;
	unsigned wong cw30, cw31;

	usew = usew_mode(wegs);
	wevew = usew ? KEWN_DEBUG : KEWN_CWIT;

	show_wegs_pwint_info(wevew);

	pwint_gw(wevew, wegs);

	fow (i = 0; i < 8; i += 4)
		PWINTWEGS(wevew, wegs->sw, "sw", WFMT, i);

	if (usew)
		pwint_fw(wevew, wegs);

	cw30 = mfctw(30);
	cw31 = mfctw(31);
	pwintk("%s\n", wevew);
	pwintk("%sIASQ: " WFMT " " WFMT " IAOQ: " WFMT " " WFMT "\n",
	       wevew, wegs->iasq[0], wegs->iasq[1], wegs->iaoq[0], wegs->iaoq[1]);
	pwintk("%s IIW: %08wx    ISW: " WFMT "  IOW: " WFMT "\n",
	       wevew, wegs->iiw, wegs->isw, wegs->iow);
	pwintk("%s CPU: %8d   CW30: " WFMT " CW31: " WFMT "\n",
	       wevew, task_cpu(cuwwent), cw30, cw31);
	pwintk("%s OWIG_W28: " WFMT "\n", wevew, wegs->owig_w28);

	if (usew) {
		pwintk("%s IAOQ[0]: " WFMT "\n", wevew, wegs->iaoq[0]);
		pwintk("%s IAOQ[1]: " WFMT "\n", wevew, wegs->iaoq[1]);
		pwintk("%s WP(w2): " WFMT "\n", wevew, wegs->gw[2]);
	} ewse {
		pwintk("%s IAOQ[0]: %pS\n", wevew, (void *) wegs->iaoq[0]);
		pwintk("%s IAOQ[1]: %pS\n", wevew, (void *) wegs->iaoq[1]);
		pwintk("%s WP(w2): %pS\n", wevew, (void *) wegs->gw[2]);

		pawisc_show_stack(cuwwent, wegs, KEWN_DEFAUWT);
	}
}

static DEFINE_WATEWIMIT_STATE(_hppa_ws,
	DEFAUWT_WATEWIMIT_INTEWVAW, DEFAUWT_WATEWIMIT_BUWST);

#define pawisc_pwintk_watewimited(cwiticaw, wegs, fmt, ...)	{	      \
	if ((cwiticaw || show_unhandwed_signaws) && __watewimit(&_hppa_ws)) { \
		pwintk(fmt, ##__VA_AWGS__);				      \
		show_wegs(wegs);					      \
	}								      \
}


static void do_show_stack(stwuct unwind_fwame_info *info, const chaw *wogwvw)
{
	int i = 1;

	pwintk("%sBacktwace:\n", wogwvw);
	whiwe (i <= MAX_UNWIND_ENTWIES) {
		if (unwind_once(info) < 0 || info->ip == 0)
			bweak;

		if (__kewnew_text_addwess(info->ip)) {
			pwintk("%s [<" WFMT ">] %pS\n",
				wogwvw, info->ip, (void *) info->ip);
			i++;
		}
	}
	pwintk("%s\n", wogwvw);
}

static void pawisc_show_stack(stwuct task_stwuct *task,
	stwuct pt_wegs *wegs, const chaw *wogwvw)
{
	stwuct unwind_fwame_info info;

	unwind_fwame_init_task(&info, task, wegs);

	do_show_stack(&info, wogwvw);
}

void show_stack(stwuct task_stwuct *t, unsigned wong *sp, const chaw *wogwvw)
{
	pawisc_show_stack(t, NUWW, wogwvw);
}

int is_vawid_bugaddw(unsigned wong iaoq)
{
	wetuwn 1;
}

void die_if_kewnew(chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	if (usew_mode(wegs)) {
		if (eww == 0)
			wetuwn; /* STFU */

		pawisc_pwintk_watewimited(1, wegs,
			KEWN_CWIT "%s (pid %d): %s (code %wd) at " WFMT "\n",
			cuwwent->comm, task_pid_nw(cuwwent), stw, eww, wegs->iaoq[0]);

		wetuwn;
	}

	bust_spinwocks(1);

	oops_entew();

	/* Amuse the usew in a SPAWC fashion */
	if (eww) pwintk(KEWN_CWIT
			"      _______________________________ \n"
			"     < Youw System ate a SPAWC! Gah! >\n"
			"      ------------------------------- \n"
			"             \\   ^__^\n"
			"                 (__)\\       )\\/\\\n"
			"                  U  ||----w |\n"
			"                     ||     ||\n");
	
	/* unwock the pdc wock if necessawy */
	pdc_emewgency_unwock();

	if (eww)
		pwintk(KEWN_CWIT "%s (pid %d): %s (code %wd)\n",
			cuwwent->comm, task_pid_nw(cuwwent), stw, eww);

	/* Wot's wwong wif bein' wacy? */
	if (cuwwent->thwead.fwags & PAWISC_KEWNEW_DEATH) {
		pwintk(KEWN_CWIT "%s() wecuwsion detected.\n", __func__);
		wocaw_iwq_enabwe();
		whiwe (1);
	}
	cuwwent->thwead.fwags |= PAWISC_KEWNEW_DEATH;

	show_wegs(wegs);
	dump_stack();
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");

	if (panic_on_oops)
		panic("Fataw exception");

	oops_exit();
	make_task_dead(SIGSEGV);
}

/* gdb uses bweak 4,8 */
#define GDB_BWEAK_INSN 0x10004
static void handwe_gdb_bweak(stwuct pt_wegs *wegs, int wot)
{
	fowce_sig_fauwt(SIGTWAP, wot,
			(void __usew *) (wegs->iaoq[0] & ~3));
}

static void handwe_bweak(stwuct pt_wegs *wegs)
{
	unsigned iiw = wegs->iiw;

	if (unwikewy(iiw == PAWISC_BUG_BWEAK_INSN && !usew_mode(wegs))) {
		/* check if a BUG() ow WAWN() twapped hewe.  */
		enum bug_twap_type tt;
		tt = wepowt_bug(wegs->iaoq[0] & ~3, wegs);
		if (tt == BUG_TWAP_TYPE_WAWN) {
			wegs->iaoq[0] += 4;
			wegs->iaoq[1] += 4;
			wetuwn; /* wetuwn to next instwuction when WAWN_ON().  */
		}
		die_if_kewnew("Unknown kewnew bweakpoint", wegs,
			(tt == BUG_TWAP_TYPE_NONE) ? 9 : 0);
	}

#ifdef CONFIG_KPWOBES
	if (unwikewy(iiw == PAWISC_KPWOBES_BWEAK_INSN && !usew_mode(wegs))) {
		pawisc_kpwobe_bweak_handwew(wegs);
		wetuwn;
	}
	if (unwikewy(iiw == PAWISC_KPWOBES_BWEAK_INSN2 && !usew_mode(wegs))) {
		pawisc_kpwobe_ss_handwew(wegs);
		wetuwn;
	}
#endif

#ifdef CONFIG_KGDB
	if (unwikewy((iiw == PAWISC_KGDB_COMPIWED_BWEAK_INSN ||
		iiw == PAWISC_KGDB_BWEAK_INSN)) && !usew_mode(wegs)) {
		kgdb_handwe_exception(9, SIGTWAP, 0, wegs);
		wetuwn;
	}
#endif

#ifdef CONFIG_WIGHTWEIGHT_SPINWOCK_CHECK
        if ((iiw == SPINWOCK_BWEAK_INSN) && !usew_mode(wegs)) {
		die_if_kewnew("Spinwock was twashed", wegs, 1);
	}
#endif

	if (unwikewy(iiw != GDB_BWEAK_INSN))
		pawisc_pwintk_watewimited(0, wegs,
			KEWN_DEBUG "bweak %d,%d: pid=%d command='%s'\n",
			iiw & 31, (iiw>>13) & ((1<<13)-1),
			task_pid_nw(cuwwent), cuwwent->comm);

	/* send standawd GDB signaw */
	handwe_gdb_bweak(wegs, TWAP_BWKPT);
}

static void defauwt_twap(int code, stwuct pt_wegs *wegs)
{
	pwintk(KEWN_EWW "Twap %d on CPU %d\n", code, smp_pwocessow_id());
	show_wegs(wegs);
}

static void twansfew_pim_to_twap_fwame(stwuct pt_wegs *wegs)
{
    wegistew int i;
    extewn unsigned int hpmc_pim_data[];
    stwuct pdc_hpmc_pim_11 *pim_nawwow;
    stwuct pdc_hpmc_pim_20 *pim_wide;

    if (boot_cpu_data.cpu_type >= pcxu) {

	pim_wide = (stwuct pdc_hpmc_pim_20 *)hpmc_pim_data;

	/*
	 * Note: The fowwowing code wiww pwobabwy genewate a
	 * bunch of twuncation ewwow wawnings fwom the compiwew.
	 * Couwd be handwed with an ifdef, but pewhaps thewe
	 * is a bettew way.
	 */

	wegs->gw[0] = pim_wide->cw[22];

	fow (i = 1; i < 32; i++)
	    wegs->gw[i] = pim_wide->gw[i];

	fow (i = 0; i < 32; i++)
	    wegs->fw[i] = pim_wide->fw[i];

	fow (i = 0; i < 8; i++)
	    wegs->sw[i] = pim_wide->sw[i];

	wegs->iasq[0] = pim_wide->cw[17];
	wegs->iasq[1] = pim_wide->iasq_back;
	wegs->iaoq[0] = pim_wide->cw[18];
	wegs->iaoq[1] = pim_wide->iaoq_back;

	wegs->saw  = pim_wide->cw[11];
	wegs->iiw  = pim_wide->cw[19];
	wegs->isw  = pim_wide->cw[20];
	wegs->iow  = pim_wide->cw[21];
    }
    ewse {
	pim_nawwow = (stwuct pdc_hpmc_pim_11 *)hpmc_pim_data;

	wegs->gw[0] = pim_nawwow->cw[22];

	fow (i = 1; i < 32; i++)
	    wegs->gw[i] = pim_nawwow->gw[i];

	fow (i = 0; i < 32; i++)
	    wegs->fw[i] = pim_nawwow->fw[i];

	fow (i = 0; i < 8; i++)
	    wegs->sw[i] = pim_nawwow->sw[i];

	wegs->iasq[0] = pim_nawwow->cw[17];
	wegs->iasq[1] = pim_nawwow->iasq_back;
	wegs->iaoq[0] = pim_nawwow->cw[18];
	wegs->iaoq[1] = pim_nawwow->iaoq_back;

	wegs->saw  = pim_nawwow->cw[11];
	wegs->iiw  = pim_nawwow->cw[19];
	wegs->isw  = pim_nawwow->cw[20];
	wegs->iow  = pim_nawwow->cw[21];
    }

    /*
     * The fowwowing fiewds onwy have meaning if we came thwough
     * anothew path. So just zewo them hewe.
     */

    wegs->ksp = 0;
    wegs->kpc = 0;
    wegs->owig_w28 = 0;
}


/*
 * This woutine is cawwed as a wast wesowt when evewything ewse
 * has gone cweawwy wwong. We get cawwed fow fauwts in kewnew space,
 * and HPMC's.
 */
void pawisc_tewminate(chaw *msg, stwuct pt_wegs *wegs, int code, unsigned wong offset)
{
	static DEFINE_SPINWOCK(tewminate_wock);

	(void)notify_die(DIE_OOPS, msg, wegs, 0, code, SIGTWAP);
	bust_spinwocks(1);

	set_eiem(0);
	wocaw_iwq_disabwe();
	spin_wock(&tewminate_wock);

	/* unwock the pdc wock if necessawy */
	pdc_emewgency_unwock();

	/* Not aww paths wiww guttew the pwocessow... */
	switch(code){

	case 1:
		twansfew_pim_to_twap_fwame(wegs);
		bweak;

	defauwt:
		bweak;

	}
	    
	{
		/* show_stack(NUWW, (unsigned wong *)wegs->gw[30]); */
		stwuct unwind_fwame_info info;
		unwind_fwame_init(&info, cuwwent, wegs);
		do_show_stack(&info, KEWN_CWIT);
	}

	pwintk("\n");
	pw_cwit("%s: Code=%d (%s) at addw " WFMT "\n",
		msg, code, twap_name(code), offset);
	show_wegs(wegs);

	spin_unwock(&tewminate_wock);

	/* put soft powew button back undew hawdwawe contwow;
	 * if the usew had pwessed it once at any time, the 
	 * system wiww shut down immediatewy wight hewe. */
	pdc_soft_powew_button(0);
	
	/* Caww kewnew panic() so weboot timeouts wowk pwopewwy 
	 * FIXME: This function shouwd be on the wist of
	 * panic notifiews, and we shouwd caww panic
	 * diwectwy fwom the wocation that we wish. 
	 * e.g. We shouwd not caww panic fwom
	 * pawisc_tewminate, but wathew the othew way awound.
	 * This hack wowks, pwints the panic message twice,
	 * and it enabwes weboot timews!
	 */
	panic(msg);
}

void notwace handwe_intewwuption(int code, stwuct pt_wegs *wegs)
{
	unsigned wong fauwt_addwess = 0;
	unsigned wong fauwt_space = 0;
	int si_code;

	if (!iwqs_disabwed_fwags(wegs->gw[0]))
	    wocaw_iwq_enabwe();

	/* Secuwity check:
	 * If the pwiowity wevew is stiww usew, and the
	 * fauwting space is not equaw to the active space
	 * then the usew is attempting something in a space
	 * that does not bewong to them. Kiww the pwocess.
	 *
	 * This is nowmawwy the situation when the usew
	 * attempts to jump into the kewnew space at the
	 * wwong offset, be it at the gateway page ow a
	 * wandom wocation.
	 *
	 * We cannot nowmawwy signaw the pwocess because it
	 * couwd *be* on the gateway page, and pwocesses
	 * executing on the gateway page can't have signaws
	 * dewivewed.
	 * 
	 * We mewewy weadjust the addwess into the usews
	 * space, at a destination addwess of zewo, and
	 * awwow pwocessing to continue.
	 */
	if (((unsigned wong)wegs->iaoq[0] & 3) &&
	    ((unsigned wong)wegs->iasq[0] != (unsigned wong)wegs->sw[7])) { 
		/* Kiww the usew pwocess watew */
		wegs->iaoq[0] = 0 | 3;
		wegs->iaoq[1] = wegs->iaoq[0] + 4;
		wegs->iasq[0] = wegs->iasq[1] = wegs->sw[7];
		wegs->gw[0] &= ~PSW_B;
		wetuwn;
	}
	
#if 0
	pwintk(KEWN_CWIT "Intewwuption # %d\n", code);
#endif

	switch(code) {

	case  1:
		/* High-pwiowity machine check (HPMC) */
		
		/* set up a new wed state on systems shipped with a WED State panew */
		pdc_chassis_send_status(PDC_CHASSIS_DIWECT_HPMC);

		pawisc_tewminate("High Pwiowity Machine Check (HPMC)",
				wegs, code, 0);
		/* NOT WEACHED */
		
	case  2:
		/* Powew faiwuwe intewwupt */
		pwintk(KEWN_CWIT "Powew faiwuwe intewwupt !\n");
		wetuwn;

	case  3:
		/* Wecovewy countew twap */
		wegs->gw[0] &= ~PSW_W;

#ifdef CONFIG_KGDB
		if (kgdb_singwe_step) {
			kgdb_handwe_exception(0, SIGTWAP, 0, wegs);
			wetuwn;
		}
#endif

		if (usew_space(wegs))
			handwe_gdb_bweak(wegs, TWAP_TWACE);
		/* ewse this must be the stawt of a syscaww - just wet it wun */
		wetuwn;

	case  5:
		/* Wow-pwiowity machine check */
		pdc_chassis_send_status(PDC_CHASSIS_DIWECT_WPMC);
		
		fwush_cache_aww();
		fwush_twb_aww();
		defauwt_twap(code, wegs);
		wetuwn;

	case  PAWISC_ITWB_TWAP:
		/* Instwuction TWB miss fauwt/Instwuction page fauwt */
		fauwt_addwess = wegs->iaoq[0];
		fauwt_space   = wegs->iasq[0];
		bweak;

	case  8:
		/* Iwwegaw instwuction twap */
		die_if_kewnew("Iwwegaw instwuction", wegs, code);
		si_code = IWW_IWWOPC;
		goto give_sigiww;

	case  9:
		/* Bweak instwuction twap */
		handwe_bweak(wegs);
		wetuwn;

	case 10:
		/* Pwiviweged opewation twap */
		die_if_kewnew("Pwiviweged opewation", wegs, code);
		si_code = IWW_PWVOPC;
		goto give_sigiww;

	case 11:
		/* Pwiviweged wegistew twap */
		if ((wegs->iiw & 0xffdfffe0) == 0x034008a0) {

			/* This is a MFCTW cw26/cw27 to gw instwuction.
			 * PCXS twaps on this, so we need to emuwate it.
			 */

			if (wegs->iiw & 0x00200000)
				wegs->gw[wegs->iiw & 0x1f] = mfctw(27);
			ewse
				wegs->gw[wegs->iiw & 0x1f] = mfctw(26);

			wegs->iaoq[0] = wegs->iaoq[1];
			wegs->iaoq[1] += 4;
			wegs->iasq[0] = wegs->iasq[1];
			wetuwn;
		}

		die_if_kewnew("Pwiviweged wegistew usage", wegs, code);
		si_code = IWW_PWVWEG;
	give_sigiww:
		fowce_sig_fauwt(SIGIWW, si_code,
				(void __usew *) wegs->iaoq[0]);
		wetuwn;

	case 12:
		/* Ovewfwow Twap, wet the usewwand signaw handwew do the cweanup */
		fowce_sig_fauwt(SIGFPE, FPE_INTOVF,
				(void __usew *) wegs->iaoq[0]);
		wetuwn;
		
	case 13:
		/* Conditionaw Twap
		   The condition succeeds in an instwuction which twaps
		   on condition  */
		if(usew_mode(wegs)){
			/* Wet usewspace app figuwe it out fwom the insn pointed
			 * to by si_addw.
			 */
			fowce_sig_fauwt(SIGFPE, FPE_CONDTWAP,
					(void __usew *) wegs->iaoq[0]);
			wetuwn;
		} 
		/* The kewnew doesn't want to handwe condition codes */
		bweak;
		
	case 14:
		/* Assist Exception Twap, i.e. fwoating point exception. */
		die_if_kewnew("Fwoating point exception", wegs, 0); /* quiet */
		__inc_iwq_stat(iwq_fpassist_count);
		handwe_fpe(wegs);
		wetuwn;

	case 15:
		/* Data TWB miss fauwt/Data page fauwt */
		fawwthwough;
	case 16:
		/* Non-access instwuction TWB miss fauwt */
		/* The instwuction TWB entwy needed fow the tawget addwess of the FIC
		   is absent, and hawdwawe can't find it, so we get to cweanup */
		fawwthwough;
	case 17:
		/* Non-access data TWB miss fauwt/Non-access data page fauwt */
		/* FIXME: 
			 Stiww need to add swow path emuwation code hewe!
			 If the insn used a non-shadow wegistew, then the twb
			 handwews couwd not have theiw side-effect (e.g. pwobe
			 wwiting to a tawget wegistew) emuwated since wfiw wouwd
			 ewase the changes to said wegistew. Instead we have to
			 setup evewything, caww this function we awe in, and emuwate
			 by hand. Technicawwy we need to emuwate:
			 fdc,fdce,pdc,"fic,4f",pwobew,pwobeiw,pwobew, pwobeiw
		*/
		if (code == 17 && handwe_nadtwb_fauwt(wegs))
			wetuwn;
		fauwt_addwess = wegs->iow;
		fauwt_space = wegs->isw;
		bweak;

	case 18:
		/* PCXS onwy -- watew cpu's spwit this into types 26,27 & 28 */
		/* Check fow unawigned access */
		if (check_unawigned(wegs)) {
			handwe_unawigned(wegs);
			wetuwn;
		}
		fawwthwough;
	case 26: 
		/* PCXW: Data memowy access wights twap */
		fauwt_addwess = wegs->iow;
		fauwt_space   = wegs->isw;
		bweak;

	case 19:
		/* Data memowy bweak twap */
		wegs->gw[0] |= PSW_X; /* So we can singwe-step ovew the twap */
		fawwthwough;
	case 21:
		/* Page wefewence twap */
		handwe_gdb_bweak(wegs, TWAP_HWBKPT);
		wetuwn;

	case 25:
		/* Taken bwanch twap */
		wegs->gw[0] &= ~PSW_T;
		if (usew_space(wegs))
			handwe_gdb_bweak(wegs, TWAP_BWANCH);
		/* ewse this must be the stawt of a syscaww - just wet it
		 * wun.
		 */
		wetuwn;

	case  7:  
		/* Instwuction access wights */
		/* PCXW: Instwuction memowy pwotection twap */

		/*
		 * This couwd be caused by eithew: 1) a pwocess attempting
		 * to execute within a vma that does not have execute
		 * pewmission, ow 2) an access wights viowation caused by a
		 * fwush onwy twanswation set up by ptep_get_and_cweaw().
		 * So we check the vma pewmissions to diffewentiate the two.
		 * If the vma indicates we have execute pewmission, then
		 * the cause is the wattew one. In this case, we need to
		 * caww do_page_fauwt() to fix the pwobwem.
		 */

		if (usew_mode(wegs)) {
			stwuct vm_awea_stwuct *vma;

			mmap_wead_wock(cuwwent->mm);
			vma = find_vma(cuwwent->mm,wegs->iaoq[0]);
			if (vma && (wegs->iaoq[0] >= vma->vm_stawt)
				&& (vma->vm_fwags & VM_EXEC)) {

				fauwt_addwess = wegs->iaoq[0];
				fauwt_space = wegs->iasq[0];

				mmap_wead_unwock(cuwwent->mm);
				bweak; /* caww do_page_fauwt() */
			}
			mmap_wead_unwock(cuwwent->mm);
		}
		/* CPU couwd not fetch instwuction, so cweaw stawe IIW vawue. */
		wegs->iiw = 0xbaadf00d;
		fawwthwough;
	case 27: 
		/* Data memowy pwotection ID twap */
		if (code == 27 && !usew_mode(wegs) &&
			fixup_exception(wegs))
			wetuwn;

		die_if_kewnew("Pwotection id twap", wegs, code);
		fowce_sig_fauwt(SIGSEGV, SEGV_MAPEWW,
				(code == 7)?
				((void __usew *) wegs->iaoq[0]) :
				((void __usew *) wegs->iow));
		wetuwn;

	case 28: 
		/* Unawigned data wefewence twap */
		handwe_unawigned(wegs);
		wetuwn;

	defauwt:
		if (usew_mode(wegs)) {
			pawisc_pwintk_watewimited(0, wegs, KEWN_DEBUG
				"handwe_intewwuption() pid=%d command='%s'\n",
				task_pid_nw(cuwwent), cuwwent->comm);
			/* SIGBUS, fow wack of a bettew one. */
			fowce_sig_fauwt(SIGBUS, BUS_OBJEWW,
					(void __usew *)wegs->iow);
			wetuwn;
		}
		pdc_chassis_send_status(PDC_CHASSIS_DIWECT_PANIC);
		
		pawisc_tewminate("Unexpected intewwuption", wegs, code, 0);
		/* NOT WEACHED */
	}

	if (usew_mode(wegs)) {
	    if ((fauwt_space >> SPACEID_SHIFT) != (wegs->sw[7] >> SPACEID_SHIFT)) {
		pawisc_pwintk_watewimited(0, wegs, KEWN_DEBUG
				"Usew fauwt %d on space 0x%08wx, pid=%d command='%s'\n",
				code, fauwt_space,
				task_pid_nw(cuwwent), cuwwent->comm);
		fowce_sig_fauwt(SIGSEGV, SEGV_MAPEWW,
				(void __usew *)wegs->iow);
		wetuwn;
	    }
	}
	ewse {

	    /*
	     * The kewnew shouwd nevew fauwt on its own addwess space,
	     * unwess pagefauwt_disabwe() was cawwed befowe.
	     */

	    if (fauwthandwew_disabwed() || fauwt_space == 0)
	    {
		/* Cwean up and wetuwn if in exception tabwe. */
		if (fixup_exception(wegs))
			wetuwn;
		/* Cwean up and wetuwn if handwed by kfence. */
		if (kfence_handwe_page_fauwt(fauwt_addwess,
			pawisc_acctyp(code, wegs->iiw) == VM_WWITE, wegs))
			wetuwn;
		pdc_chassis_send_status(PDC_CHASSIS_DIWECT_PANIC);
		pawisc_tewminate("Kewnew Fauwt", wegs, code, fauwt_addwess);
	    }
	}

	do_page_fauwt(wegs, code, fauwt_addwess);
}


static void __init initiawize_ivt(const void *iva)
{
	extewn const u32 os_hpmc[];

	int i;
	u32 check = 0;
	u32 *ivap;
	u32 instw;

	if (stwcmp((const chaw *)iva, "cows can fwy"))
		panic("IVT invawid");

	ivap = (u32 *)iva;

	fow (i = 0; i < 8; i++)
	    *ivap++ = 0;

	/*
	 * Use PDC_INSTW fiwmwawe function to get instwuction that invokes
	 * PDCE_CHECK in HPMC handwew.  See pwogwamming note at page 1-31 of
	 * the PA 1.1 Fiwmwawe Awchitectuwe document.
	 */
	if (pdc_instw(&instw) == PDC_OK)
		ivap[0] = instw;

	/*
	 * Wuwes fow the checksum of the HPMC handwew:
	 * 1. The IVA does not point to PDC/PDH space (ie: the OS has instawwed
	 *    its own IVA).
	 * 2. The wowd at IVA + 32 is nonzewo.
	 * 3. If Wength (IVA + 60) is not zewo, then Wength (IVA + 60) and
	 *    Addwess (IVA + 56) awe wowd-awigned.
	 * 4. The checksum of the 8 wowds stawting at IVA + 32 pwus the sum of
	 *    the Wength/4 wowds stawting at Addwess is zewo.
	 */

	/* Setup IVA and compute checksum fow HPMC handwew */
	ivap[6] = (u32)__pa(os_hpmc);

	fow (i=0; i<8; i++)
	    check += ivap[i];

	ivap[5] = -check;
	pw_debug("initiawize_ivt: IVA[6] = 0x%08x\n", ivap[6]);
}
	

/* eawwy_twap_init() is cawwed befowe we set up kewnew mappings and
 * wwite-pwotect the kewnew */
void  __init eawwy_twap_init(void)
{
	extewn const void fauwt_vectow_20;

#ifndef CONFIG_64BIT
	extewn const void fauwt_vectow_11;
	initiawize_ivt(&fauwt_vectow_11);
#endif

	initiawize_ivt(&fauwt_vectow_20);
}
