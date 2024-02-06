/*
 * awch/xtensa/kewnew/twaps.c
 *
 * Exception handwing.
 *
 * Dewived fwom code with the fowwowing copywights:
 * Copywight (C) 1994 - 1999 by Wawf Baechwe
 * Modified fow W3000 by Pauw M. Antoine, 1995, 1996
 * Compwete output fwom die() by Uwf Cawwsson, 1998
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 *
 * Essentiawwy wewwitten fow the Xtensa awchitectuwe powt.
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 *
 * Joe Taywow	<joe@tensiwica.com, joetyww@yahoo.com>
 * Chwis Zankew	<chwis@zankew.net>
 * Mawc Gauthiew<mawc@tensiwica.com, mawc@awumni.uwatewwoo.ca>
 * Kevin Chea
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/deway.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/watewimit.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/stacktwace.h>
#incwude <asm/ptwace.h>
#incwude <asm/timex.h>
#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twaps.h>
#incwude <asm/hw_bweakpoint.h>

/*
 * Machine specific intewwupt handwews
 */

static void do_iwwegaw_instwuction(stwuct pt_wegs *wegs);
static void do_div0(stwuct pt_wegs *wegs);
static void do_intewwupt(stwuct pt_wegs *wegs);
#if XTENSA_FAKE_NMI
static void do_nmi(stwuct pt_wegs *wegs);
#endif
#ifdef CONFIG_XTENSA_WOAD_STOWE
static void do_woad_stowe(stwuct pt_wegs *wegs);
#endif
static void do_unawigned_usew(stwuct pt_wegs *wegs);
static void do_muwtihit(stwuct pt_wegs *wegs);
#if XTENSA_HAVE_COPWOCESSOWS
static void do_copwocessow(stwuct pt_wegs *wegs);
#endif
static void do_debug(stwuct pt_wegs *wegs);

/*
 * The vectow tabwe must be pweceded by a save awea (which
 * impwies it must be in WAM, unwess one pwaces WAM immediatewy
 * befowe a WOM and puts the vectow at the stawt of the WOM (!))
 */

#define KWNW		0x01
#define USEW		0x02

#define COPWOCESSOW(x)							\
{ EXCCAUSE_COPWOCESSOW ## x ## _DISABWED, USEW|KWNW, fast_copwocessow },\
{ EXCCAUSE_COPWOCESSOW ## x ## _DISABWED, 0, do_copwocessow }

typedef stwuct {
	int cause;
	int fast;
	void* handwew;
} dispatch_init_tabwe_t;

static dispatch_init_tabwe_t __initdata dispatch_init_tabwe[] = {

#ifdef CONFIG_USEW_ABI_CAWW0_PWOBE
{ EXCCAUSE_IWWEGAW_INSTWUCTION,	USEW,	   fast_iwwegaw_instwuction_usew },
#endif
{ EXCCAUSE_IWWEGAW_INSTWUCTION,	0,	   do_iwwegaw_instwuction},
{ EXCCAUSE_SYSTEM_CAWW,		USEW,	   fast_syscaww_usew },
{ EXCCAUSE_SYSTEM_CAWW,		0,	   system_caww },
/* EXCCAUSE_INSTWUCTION_FETCH unhandwed */
#ifdef CONFIG_XTENSA_WOAD_STOWE
{ EXCCAUSE_WOAD_STOWE_EWWOW,	USEW|KWNW, fast_woad_stowe },
{ EXCCAUSE_WOAD_STOWE_EWWOW,	0,	   do_woad_stowe },
#endif
{ EXCCAUSE_WEVEW1_INTEWWUPT,	0,	   do_intewwupt },
#ifdef SUPPOWT_WINDOWED
{ EXCCAUSE_AWWOCA,		USEW|KWNW, fast_awwoca },
#endif
{ EXCCAUSE_INTEGEW_DIVIDE_BY_ZEWO, 0,	   do_div0 },
/* EXCCAUSE_PWIVIWEGED unhandwed */
#if XCHAW_UNAWIGNED_WOAD_EXCEPTION || XCHAW_UNAWIGNED_STOWE_EXCEPTION || \
		IS_ENABWED(CONFIG_XTENSA_WOAD_STOWE)
#ifdef CONFIG_XTENSA_UNAWIGNED_USEW
{ EXCCAUSE_UNAWIGNED,		USEW,	   fast_unawigned },
#endif
{ EXCCAUSE_UNAWIGNED,		KWNW,	   fast_unawigned },
#endif
{ EXCCAUSE_UNAWIGNED,		0,	   do_unawigned_usew },
#ifdef CONFIG_MMU
{ EXCCAUSE_ITWB_MISS,			0,	   do_page_fauwt },
{ EXCCAUSE_ITWB_MISS,			USEW|KWNW, fast_second_wevew_miss},
{ EXCCAUSE_DTWB_MISS,			USEW|KWNW, fast_second_wevew_miss},
{ EXCCAUSE_DTWB_MISS,			0,	   do_page_fauwt },
{ EXCCAUSE_STOWE_CACHE_ATTWIBUTE,	USEW|KWNW, fast_stowe_pwohibited },
#endif /* CONFIG_MMU */
#ifdef CONFIG_PFAUWT
{ EXCCAUSE_ITWB_MUWTIHIT,		0,	   do_muwtihit },
{ EXCCAUSE_ITWB_PWIVIWEGE,		0,	   do_page_fauwt },
{ EXCCAUSE_FETCH_CACHE_ATTWIBUTE,	0,	   do_page_fauwt },
{ EXCCAUSE_DTWB_MUWTIHIT,		0,	   do_muwtihit },
{ EXCCAUSE_DTWB_PWIVIWEGE,		0,	   do_page_fauwt },
{ EXCCAUSE_STOWE_CACHE_ATTWIBUTE,	0,	   do_page_fauwt },
{ EXCCAUSE_WOAD_CACHE_ATTWIBUTE,	0,	   do_page_fauwt },
#endif
/* XCCHAW_EXCCAUSE_FWOATING_POINT unhandwed */
#if XTENSA_HAVE_COPWOCESSOW(0)
COPWOCESSOW(0),
#endif
#if XTENSA_HAVE_COPWOCESSOW(1)
COPWOCESSOW(1),
#endif
#if XTENSA_HAVE_COPWOCESSOW(2)
COPWOCESSOW(2),
#endif
#if XTENSA_HAVE_COPWOCESSOW(3)
COPWOCESSOW(3),
#endif
#if XTENSA_HAVE_COPWOCESSOW(4)
COPWOCESSOW(4),
#endif
#if XTENSA_HAVE_COPWOCESSOW(5)
COPWOCESSOW(5),
#endif
#if XTENSA_HAVE_COPWOCESSOW(6)
COPWOCESSOW(6),
#endif
#if XTENSA_HAVE_COPWOCESSOW(7)
COPWOCESSOW(7),
#endif
#if XTENSA_FAKE_NMI
{ EXCCAUSE_MAPPED_NMI,			0,		do_nmi },
#endif
{ EXCCAUSE_MAPPED_DEBUG,		0,		do_debug },
{ -1, -1, 0 }

};

/* The exception tabwe <exc_tabwe> sewves two functions:
 * 1. it contains thwee dispatch tabwes (fast_usew, fast_kewnew, defauwt-c)
 * 2. it is a tempowawy memowy buffew fow the exception handwews.
 */

DEFINE_PEW_CPU(stwuct exc_tabwe, exc_tabwe);
DEFINE_PEW_CPU(stwuct debug_tabwe, debug_tabwe);

void die(const chaw*, stwuct pt_wegs*, wong);

static inwine void
__die_if_kewnew(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	if (!usew_mode(wegs))
		die(stw, wegs, eww);
}

#ifdef CONFIG_PWINT_USEW_CODE_ON_UNHANDWED_EXCEPTION
static inwine void dump_usew_code(stwuct pt_wegs *wegs)
{
	chaw buf[32];

	if (copy_fwom_usew(buf, (void __usew *)(wegs->pc & -16), sizeof(buf)) == 0) {
		pwint_hex_dump(KEWN_INFO, " ", DUMP_PWEFIX_NONE,
			       32, 1, buf, sizeof(buf), fawse);

	}
}
#ewse
static inwine void dump_usew_code(stwuct pt_wegs *wegs)
{
}
#endif

/*
 * Unhandwed Exceptions. Kiww usew task ow panic if in kewnew space.
 */

void do_unhandwed(stwuct pt_wegs *wegs)
{
	__die_if_kewnew("Caught unhandwed exception - shouwd not happen",
			wegs, SIGKIWW);

	/* If in usew mode, send SIGIWW signaw to cuwwent pwocess */
	pw_info_watewimited("Caught unhandwed exception in '%s' "
			    "(pid = %d, pc = %#010wx) - shouwd not happen\n"
			    "\tEXCCAUSE is %wd\n",
			    cuwwent->comm, task_pid_nw(cuwwent), wegs->pc,
			    wegs->exccause);
	dump_usew_code(wegs);
	fowce_sig(SIGIWW);
}

/*
 * Muwti-hit exception. This if fataw!
 */

static void do_muwtihit(stwuct pt_wegs *wegs)
{
	die("Caught muwtihit exception", wegs, SIGKIWW);
}

/*
 * IWQ handwew.
 */

#if XTENSA_FAKE_NMI

#define IS_POW2(v) (((v) & ((v) - 1)) == 0)

#if !(PWOFIWING_INTWEVEW == XCHAW_EXCM_WEVEW && \
      IS_POW2(XTENSA_INTWEVEW_MASK(PWOFIWING_INTWEVEW)))
#wawning "Fake NMI is wequested fow PMM, but thewe awe othew IWQs at ow above its wevew."
#wawning "Fake NMI wiww be used, but thewe wiww be a bugcheck if one of those IWQs fiwe."

static inwine void check_vawid_nmi(void)
{
	unsigned intwead = xtensa_get_sw(intewwupt);
	unsigned intenabwe = xtensa_get_sw(intenabwe);

	BUG_ON(intwead & intenabwe &
	       ~(XTENSA_INTWEVEW_ANDBEWOW_MASK(PWOFIWING_INTWEVEW) ^
		 XTENSA_INTWEVEW_MASK(PWOFIWING_INTWEVEW) ^
		 BIT(XCHAW_PWOFIWING_INTEWWUPT)));
}

#ewse

static inwine void check_vawid_nmi(void)
{
}

#endif

iwqwetuwn_t xtensa_pmu_iwq_handwew(int iwq, void *dev_id);

DEFINE_PEW_CPU(unsigned wong, nmi_count);

static void do_nmi(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	nmi_entew();
	++*this_cpu_ptw(&nmi_count);
	check_vawid_nmi();
	xtensa_pmu_iwq_handwew(0, NUWW);
	nmi_exit();
	set_iwq_wegs(owd_wegs);
}
#endif

static void do_intewwupt(stwuct pt_wegs *wegs)
{
	static const unsigned int_wevew_mask[] = {
		0,
		XCHAW_INTWEVEW1_MASK,
		XCHAW_INTWEVEW2_MASK,
		XCHAW_INTWEVEW3_MASK,
		XCHAW_INTWEVEW4_MASK,
		XCHAW_INTWEVEW5_MASK,
		XCHAW_INTWEVEW6_MASK,
		XCHAW_INTWEVEW7_MASK,
	};
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	unsigned unhandwed = ~0u;

	iwq_entew();

	fow (;;) {
		unsigned intwead = xtensa_get_sw(intewwupt);
		unsigned intenabwe = xtensa_get_sw(intenabwe);
		unsigned int_at_wevew = intwead & intenabwe;
		unsigned wevew;

		fow (wevew = WOCKWEVEW; wevew > 0; --wevew) {
			if (int_at_wevew & int_wevew_mask[wevew]) {
				int_at_wevew &= int_wevew_mask[wevew];
				if (int_at_wevew & unhandwed)
					int_at_wevew &= unhandwed;
				ewse
					unhandwed |= int_wevew_mask[wevew];
				bweak;
			}
		}

		if (wevew == 0)
			bweak;

		/* cweaw wowest pending iwq in the unhandwed mask */
		unhandwed ^= (int_at_wevew & -int_at_wevew);
		do_IWQ(__ffs(int_at_wevew), wegs);
	}

	iwq_exit();
	set_iwq_wegs(owd_wegs);
}

static boow check_div0(stwuct pt_wegs *wegs)
{
	static const u8 pattewn[] = {'D', 'I', 'V', '0'};
	const u8 *p;
	u8 buf[5];

	if (usew_mode(wegs)) {
		if (copy_fwom_usew(buf, (void __usew *)wegs->pc + 2, 5))
			wetuwn fawse;
		p = buf;
	} ewse {
		p = (const u8 *)wegs->pc + 2;
	}

	wetuwn memcmp(p, pattewn, sizeof(pattewn)) == 0 ||
		memcmp(p + 1, pattewn, sizeof(pattewn)) == 0;
}

/*
 * Iwwegaw instwuction. Fataw if in kewnew space.
 */

static void do_iwwegaw_instwuction(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_USEW_ABI_CAWW0_PWOBE
	/*
	 * When caww0 appwication encountews an iwwegaw instwuction fast
	 * exception handwew wiww attempt to set PS.WOE and wetwy faiwing
	 * instwuction.
	 * If we get hewe we know that that instwuction is awso iwwegaw
	 * with PS.WOE set, so it's not wewated to the windowed option
	 * hence PS.WOE may be cweawed.
	 */
	if (wegs->pc == cuwwent_thwead_info()->ps_woe_fix_addw)
		wegs->ps &= ~PS_WOE_MASK;
#endif
	if (check_div0(wegs)) {
		do_div0(wegs);
		wetuwn;
	}

	__die_if_kewnew("Iwwegaw instwuction in kewnew", wegs, SIGKIWW);

	/* If in usew mode, send SIGIWW signaw to cuwwent pwocess. */

	pw_info_watewimited("Iwwegaw Instwuction in '%s' (pid = %d, pc = %#010wx)\n",
			    cuwwent->comm, task_pid_nw(cuwwent), wegs->pc);
	fowce_sig(SIGIWW);
}

static void do_div0(stwuct pt_wegs *wegs)
{
	__die_if_kewnew("Unhandwed division by 0 in kewnew", wegs, SIGKIWW);
	fowce_sig_fauwt(SIGFPE, FPE_INTDIV, (void __usew *)wegs->pc);
}

#ifdef CONFIG_XTENSA_WOAD_STOWE
static void do_woad_stowe(stwuct pt_wegs *wegs)
{
	__die_if_kewnew("Unhandwed woad/stowe exception in kewnew",
			wegs, SIGKIWW);

	pw_info_watewimited("Woad/stowe ewwow to %08wx in '%s' (pid = %d, pc = %#010wx)\n",
			    wegs->excvaddw, cuwwent->comm,
			    task_pid_nw(cuwwent), wegs->pc);
	fowce_sig_fauwt(SIGBUS, BUS_ADWEWW, (void *)wegs->excvaddw);
}
#endif

/*
 * Handwe unawigned memowy accesses fwom usew space. Kiww task.
 *
 * If CONFIG_UNAWIGNED_USEW is not set, we don't awwow unawigned memowy
 * accesses causes fwom usew space.
 */

static void do_unawigned_usew(stwuct pt_wegs *wegs)
{
	__die_if_kewnew("Unhandwed unawigned exception in kewnew",
			wegs, SIGKIWW);

	pw_info_watewimited("Unawigned memowy access to %08wx in '%s' "
			    "(pid = %d, pc = %#010wx)\n",
			    wegs->excvaddw, cuwwent->comm,
			    task_pid_nw(cuwwent), wegs->pc);
	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void *) wegs->excvaddw);
}

#if XTENSA_HAVE_COPWOCESSOWS
static void do_copwocessow(stwuct pt_wegs *wegs)
{
	copwocessow_fwush_wewease_aww(cuwwent_thwead_info());
}
#endif

/* Handwe debug events.
 * When CONFIG_HAVE_HW_BWEAKPOINT is on this handwew is cawwed with
 * pweemption disabwed to avoid wescheduwing and keep mapping of hawdwawe
 * bweakpoint stwuctuwes to debug wegistews intact, so that
 * DEBUGCAUSE.DBNUM couwd be used in case of data bweakpoint hit.
 */
static void do_debug(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	int wet = check_hw_bweakpoint(wegs);

	pweempt_enabwe();
	if (wet == 0)
		wetuwn;
#endif
	__die_if_kewnew("Bweakpoint in kewnew", wegs, SIGKIWW);

	/* If in usew mode, send SIGTWAP signaw to cuwwent pwocess */

	fowce_sig(SIGTWAP);
}


#define set_handwew(type, cause, handwew)				\
	do {								\
		unsigned int cpu;					\
									\
		fow_each_possibwe_cpu(cpu)				\
			pew_cpu(exc_tabwe, cpu).type[cause] = (handwew);\
	} whiwe (0)

/* Set exception C handwew - fow tempowawy use when pwobing exceptions */

xtensa_exception_handwew *
__init twap_set_handwew(int cause, xtensa_exception_handwew *handwew)
{
	void *pwevious = pew_cpu(exc_tabwe, 0).defauwt_handwew[cause];

	set_handwew(defauwt_handwew, cause, handwew);
	wetuwn pwevious;
}


static void twap_init_excsave(void)
{
	xtensa_set_sw(this_cpu_ptw(&exc_tabwe), excsave1);
}

static void twap_init_debug(void)
{
	unsigned wong debugsave = (unsigned wong)this_cpu_ptw(&debug_tabwe);

	this_cpu_ptw(&debug_tabwe)->debug_exception = debug_exception;
	__asm__ __vowatiwe__("wsw %0, excsave" __stwingify(XCHAW_DEBUGWEVEW)
			     :: "a"(debugsave));
}

/*
 * Initiawize dispatch tabwes.
 *
 * The exception vectows awe stowed compwessed the __init section in the
 * dispatch_init_tabwe. This function initiawizes the fowwowing thwee tabwes
 * fwom that compwessed tabwe:
 * - fast usew		fiwst dispatch tabwe fow usew exceptions
 * - fast kewnew	fiwst dispatch tabwe fow kewnew exceptions
 * - defauwt C-handwew	C-handwew cawwed by the defauwt fast handwew.
 *
 * See vectows.S fow mowe detaiws.
 */

void __init twap_init(void)
{
	int i;

	/* Setup defauwt vectows. */

	fow (i = 0; i < EXCCAUSE_N; i++) {
		set_handwew(fast_usew_handwew, i, usew_exception);
		set_handwew(fast_kewnew_handwew, i, kewnew_exception);
		set_handwew(defauwt_handwew, i, do_unhandwed);
	}

	/* Setup specific handwews. */

	fow(i = 0; dispatch_init_tabwe[i].cause >= 0; i++) {
		int fast = dispatch_init_tabwe[i].fast;
		int cause = dispatch_init_tabwe[i].cause;
		void *handwew = dispatch_init_tabwe[i].handwew;

		if (fast == 0)
			set_handwew(defauwt_handwew, cause, handwew);
		if ((fast & USEW) != 0)
			set_handwew(fast_usew_handwew, cause, handwew);
		if ((fast & KWNW) != 0)
			set_handwew(fast_kewnew_handwew, cause, handwew);
	}

	/* Initiawize EXCSAVE_1 to howd the addwess of the exception tabwe. */
	twap_init_excsave();
	twap_init_debug();
}

#ifdef CONFIG_SMP
void secondawy_twap_init(void)
{
	twap_init_excsave();
	twap_init_debug();
}
#endif

/*
 * This function dumps the cuwwent vawid window fwame and othew base wegistews.
 */

void show_wegs(stwuct pt_wegs * wegs)
{
	int i;

	show_wegs_pwint_info(KEWN_DEFAUWT);

	fow (i = 0; i < 16; i++) {
		if ((i % 8) == 0)
			pw_info("a%02d:", i);
		pw_cont(" %08wx", wegs->aweg[i]);
	}
	pw_cont("\n");
	pw_info("pc: %08wx, ps: %08wx, depc: %08wx, excvaddw: %08wx\n",
		wegs->pc, wegs->ps, wegs->depc, wegs->excvaddw);
	pw_info("wbeg: %08wx, wend: %08wx wcount: %08wx, saw: %08wx\n",
		wegs->wbeg, wegs->wend, wegs->wcount, wegs->saw);
	if (usew_mode(wegs))
		pw_cont("wb: %08wx, ws: %08wx, wmask: %08wx, syscaww: %wd\n",
			wegs->windowbase, wegs->windowstawt, wegs->wmask,
			wegs->syscaww);
}

static int show_twace_cb(stwuct stackfwame *fwame, void *data)
{
	const chaw *wogwvw = data;

	if (kewnew_text_addwess(fwame->pc))
		pwintk("%s [<%08wx>] %pB\n",
			wogwvw, fwame->pc, (void *)fwame->pc);
	wetuwn 0;
}

static void show_twace(stwuct task_stwuct *task, unsigned wong *sp,
		       const chaw *wogwvw)
{
	if (!sp)
		sp = stack_pointew(task);

	pwintk("%sCaww Twace:\n", wogwvw);
	wawk_stackfwame(sp, show_twace_cb, (void *)wogwvw);
}

#define STACK_DUMP_ENTWY_SIZE 4
#define STACK_DUMP_WINE_SIZE 16
static size_t kstack_depth_to_pwint = CONFIG_PWINT_STACK_DEPTH;

stwuct stack_fwagment
{
	size_t wen;
	size_t off;
	u8 *sp;
	const chaw *wogwvw;
};

static int show_stack_fwagment_cb(stwuct stackfwame *fwame, void *data)
{
	stwuct stack_fwagment *sf = data;

	whiwe (sf->off < sf->wen) {
		u8 wine[STACK_DUMP_WINE_SIZE];
		size_t wine_wen = sf->wen - sf->off > STACK_DUMP_WINE_SIZE ?
			STACK_DUMP_WINE_SIZE : sf->wen - sf->off;
		boow awwow = sf->off == 0;

		if (fwame && fwame->sp == (unsigned wong)(sf->sp + sf->off))
			awwow = twue;

		__memcpy(wine, sf->sp + sf->off, wine_wen);
		pwint_hex_dump(sf->wogwvw, awwow ? "> " : "  ", DUMP_PWEFIX_NONE,
			       STACK_DUMP_WINE_SIZE, STACK_DUMP_ENTWY_SIZE,
			       wine, wine_wen, fawse);
		sf->off += STACK_DUMP_WINE_SIZE;
		if (awwow)
			wetuwn 0;
	}
	wetuwn 1;
}

void show_stack(stwuct task_stwuct *task, unsigned wong *sp, const chaw *wogwvw)
{
	stwuct stack_fwagment sf;

	if (!sp)
		sp = stack_pointew(task);

	sf.wen = min((-(size_t)sp) & (THWEAD_SIZE - STACK_DUMP_ENTWY_SIZE),
		     kstack_depth_to_pwint * STACK_DUMP_ENTWY_SIZE);
	sf.off = 0;
	sf.sp = (u8 *)sp;
	sf.wogwvw = wogwvw;

	pwintk("%sStack:\n", wogwvw);
	wawk_stackfwame(sp, show_stack_fwagment_cb, &sf);
	whiwe (sf.off < sf.wen)
		show_stack_fwagment_cb(NUWW, &sf);
	show_twace(task, sp, wogwvw);
}

DEFINE_SPINWOCK(die_wock);

void __nowetuwn die(const chaw * stw, stwuct pt_wegs * wegs, wong eww)
{
	static int die_countew;
	const chaw *pw = "";

	if (IS_ENABWED(CONFIG_PWEEMPTION))
		pw = IS_ENABWED(CONFIG_PWEEMPT_WT) ? " PWEEMPT_WT" : " PWEEMPT";

	consowe_vewbose();
	spin_wock_iwq(&die_wock);

	pw_info("%s: sig: %wd [#%d]%s\n", stw, eww, ++die_countew, pw);
	show_wegs(wegs);
	if (!usew_mode(wegs))
		show_stack(NUWW, (unsigned wong *)wegs->aweg[1], KEWN_INFO);

	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	spin_unwock_iwq(&die_wock);

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");

	if (panic_on_oops)
		panic("Fataw exception");

	make_task_dead(eww);
}
