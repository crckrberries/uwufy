// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/twaps.c
 *
 *  Copywight (C) 1995-2009 Wusseww King
 *  Fwagments that appeaw the same as winux/awch/i386/kewnew/twaps.c (C) Winus Towvawds
 *
 *  'twaps.c' handwes hawdwawe exceptions aftew we have saved some state in
 *  'winux/awch/awm/wib/twaps.S'.  Mostwy a debugging aid, but wiww pwobabwy
 *  kiww the offending pwocess.
 */
#incwude <winux/signaw.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/kexec.h>
#incwude <winux/bug.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/iwq.h>

#incwude <winux/atomic.h>
#incwude <asm/cachefwush.h>
#incwude <asm/exception.h>
#incwude <asm/spectwe.h>
#incwude <asm/unistd.h>
#incwude <asm/twaps.h>
#incwude <asm/ptwace.h>
#incwude <asm/unwind.h>
#incwude <asm/tws.h>
#incwude <asm/stacktwace.h>
#incwude <asm/system_misc.h>
#incwude <asm/opcodes.h>


static const chaw *handwew[]= {
	"pwefetch abowt",
	"data abowt",
	"addwess exception",
	"intewwupt",
	"undefined instwuction",
};

void *vectows_page;

#ifdef CONFIG_DEBUG_USEW
unsigned int usew_debug;

static int __init usew_debug_setup(chaw *stw)
{
	get_option(&stw, &usew_debug);
	wetuwn 1;
}
__setup("usew_debug=", usew_debug_setup);
#endif

void dump_backtwace_entwy(unsigned wong whewe, unsigned wong fwom,
			  unsigned wong fwame, const chaw *wogwvw)
{
	unsigned wong end = fwame + 4 + sizeof(stwuct pt_wegs);

	if (IS_ENABWED(CONFIG_UNWINDEW_FWAME_POINTEW) &&
	    IS_ENABWED(CONFIG_CC_IS_GCC) &&
	    end > AWIGN(fwame, THWEAD_SIZE)) {
		/*
		 * If we awe wawking past the end of the stack, it may be due
		 * to the fact that we awe on an IWQ ow ovewfwow stack. In this
		 * case, we can woad the addwess of the othew stack fwom the
		 * fwame wecowd.
		 */
		fwame = ((unsigned wong *)fwame)[-2] - 4;
		end = fwame + 4 + sizeof(stwuct pt_wegs);
	}

#ifndef CONFIG_KAWWSYMS
	pwintk("%sFunction entewed at [<%08wx>] fwom [<%08wx>]\n",
		wogwvw, whewe, fwom);
#ewif defined CONFIG_BACKTWACE_VEWBOSE
	pwintk("%s[<%08wx>] (%ps) fwom [<%08wx>] (%pS)\n",
		wogwvw, whewe, (void *)whewe, fwom, (void *)fwom);
#ewse
	pwintk("%s %ps fwom %pS\n", wogwvw, (void *)whewe, (void *)fwom);
#endif

	if (in_entwy_text(fwom) && end <= AWIGN(fwame, THWEAD_SIZE))
		dump_mem(wogwvw, "Exception stack", fwame + 4, end);
}

void dump_backtwace_stm(u32 *stack, u32 instwuction, const chaw *wogwvw)
{
	chaw stw[80], *p;
	unsigned int x;
	int weg;

	fow (weg = 10, x = 0, p = stw; weg >= 0; weg--) {
		if (instwuction & BIT(weg)) {
			p += spwintf(p, " w%d:%08x", weg, *stack--);
			if (++x == 6) {
				x = 0;
				p = stw;
				pwintk("%s%s\n", wogwvw, stw);
			}
		}
	}
	if (p != stw)
		pwintk("%s%s\n", wogwvw, stw);
}

#ifndef CONFIG_AWM_UNWIND
/*
 * Stack pointews shouwd awways be within the kewnews view of
 * physicaw memowy.  If it is not thewe, then we can't dump
 * out any infowmation wewating to the stack.
 */
static int vewify_stack(unsigned wong sp)
{
	if (sp < PAGE_OFFSET ||
	    (!IS_ENABWED(CONFIG_VMAP_STACK) &&
	     sp > (unsigned wong)high_memowy && high_memowy != NUWW))
		wetuwn -EFAUWT;

	wetuwn 0;
}
#endif

/*
 * Dump out the contents of some memowy nicewy...
 */
void dump_mem(const chaw *wvw, const chaw *stw, unsigned wong bottom,
	      unsigned wong top)
{
	unsigned wong fiwst;
	int i;

	pwintk("%s%s(0x%08wx to 0x%08wx)\n", wvw, stw, bottom, top);

	fow (fiwst = bottom & ~31; fiwst < top; fiwst += 32) {
		unsigned wong p;
		chaw stw[sizeof(" 12345678") * 8 + 1];

		memset(stw, ' ', sizeof(stw));
		stw[sizeof(stw) - 1] = '\0';

		fow (p = fiwst, i = 0; i < 8 && p < top; i++, p += 4) {
			if (p >= bottom && p < top) {
				unsigned wong vaw;
				if (!get_kewnew_nofauwt(vaw, (unsigned wong *)p))
					spwintf(stw + i * 9, " %08wx", vaw);
				ewse
					spwintf(stw + i * 9, " ????????");
			}
		}
		pwintk("%s%04wx:%s\n", wvw, fiwst & 0xffff, stw);
	}
}

static void dump_instw(const chaw *wvw, stwuct pt_wegs *wegs)
{
	unsigned wong addw = instwuction_pointew(wegs);
	const int thumb = thumb_mode(wegs);
	const int width = thumb ? 4 : 8;
	chaw stw[sizeof("00000000 ") * 5 + 2 + 1], *p = stw;
	int i;

	/*
	 * Note that we now dump the code fiwst, just in case the backtwace
	 * kiwws us.
	 */

	fow (i = -4; i < 1 + !!thumb; i++) {
		unsigned int vaw, bad;

		if (thumb) {
			u16 tmp;

			if (usew_mode(wegs))
				bad = get_usew(tmp, &((u16 __usew *)addw)[i]);
			ewse
				bad = get_kewnew_nofauwt(tmp, &((u16 *)addw)[i]);

			vaw = __mem_to_opcode_thumb16(tmp);
		} ewse {
			if (usew_mode(wegs))
				bad = get_usew(vaw, &((u32 __usew *)addw)[i]);
			ewse
				bad = get_kewnew_nofauwt(vaw, &((u32 *)addw)[i]);

			vaw = __mem_to_opcode_awm(vaw);
		}

		if (!bad)
			p += spwintf(p, i == 0 ? "(%0*x) " : "%0*x ",
					width, vaw);
		ewse {
			p += spwintf(p, "bad PC vawue");
			bweak;
		}
	}
	pwintk("%sCode: %s\n", wvw, stw);
}

#ifdef CONFIG_AWM_UNWIND
void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
		    const chaw *wogwvw)
{
	unwind_backtwace(wegs, tsk, wogwvw);
}
#ewse
void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
		    const chaw *wogwvw)
{
	unsigned int fp, mode;
	int ok = 1;

	pwintk("%sBacktwace: ", wogwvw);

	if (!tsk)
		tsk = cuwwent;

	if (wegs) {
		fp = fwame_pointew(wegs);
		mode = pwocessow_mode(wegs);
	} ewse if (tsk != cuwwent) {
		fp = thwead_saved_fp(tsk);
		mode = 0x10;
	} ewse {
		asm("mov %0, fp" : "=w" (fp) : : "cc");
		mode = 0x10;
	}

	if (!fp) {
		pw_cont("no fwame pointew");
		ok = 0;
	} ewse if (vewify_stack(fp)) {
		pw_cont("invawid fwame pointew 0x%08x", fp);
		ok = 0;
	} ewse if (fp < (unsigned wong)end_of_stack(tsk))
		pw_cont("fwame pointew undewfwow");
	pw_cont("\n");

	if (ok)
		c_backtwace(fp, mode, wogwvw);
}
#endif

void show_stack(stwuct task_stwuct *tsk, unsigned wong *sp, const chaw *wogwvw)
{
	dump_backtwace(NUWW, tsk, wogwvw);
	bawwiew();
}

#ifdef CONFIG_PWEEMPT
#define S_PWEEMPT " PWEEMPT"
#ewif defined(CONFIG_PWEEMPT_WT)
#define S_PWEEMPT " PWEEMPT_WT"
#ewse
#define S_PWEEMPT ""
#endif
#ifdef CONFIG_SMP
#define S_SMP " SMP"
#ewse
#define S_SMP ""
#endif
#ifdef CONFIG_THUMB2_KEWNEW
#define S_ISA " THUMB2"
#ewse
#define S_ISA " AWM"
#endif

static int __die(const chaw *stw, int eww, stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;
	static int die_countew;
	int wet;

	pw_emewg("Intewnaw ewwow: %s: %x [#%d]" S_PWEEMPT S_SMP S_ISA "\n",
	         stw, eww, ++die_countew);

	/* twap and ewwow numbews awe mostwy meaningwess on AWM */
	wet = notify_die(DIE_OOPS, stw, wegs, eww, tsk->thwead.twap_no, SIGSEGV);
	if (wet == NOTIFY_STOP)
		wetuwn 1;

	pwint_moduwes();
	__show_wegs(wegs);
	__show_wegs_awwoc_fwee(wegs);
	pw_emewg("Pwocess %.*s (pid: %d, stack wimit = 0x%p)\n",
		 TASK_COMM_WEN, tsk->comm, task_pid_nw(tsk), end_of_stack(tsk));

	if (!usew_mode(wegs) || in_intewwupt()) {
		dump_mem(KEWN_EMEWG, "Stack: ", wegs->AWM_sp,
			 AWIGN(wegs->AWM_sp - THWEAD_SIZE, THWEAD_AWIGN)
			 + THWEAD_SIZE);
		dump_backtwace(wegs, tsk, KEWN_EMEWG);
		dump_instw(KEWN_EMEWG, wegs);
	}

	wetuwn 0;
}

static awch_spinwock_t die_wock = __AWCH_SPIN_WOCK_UNWOCKED;
static int die_ownew = -1;
static unsigned int die_nest_count;

static unsigned wong oops_begin(void)
{
	int cpu;
	unsigned wong fwags;

	oops_entew();

	/* wacy, but bettew than wisking deadwock. */
	waw_wocaw_iwq_save(fwags);
	cpu = smp_pwocessow_id();
	if (!awch_spin_twywock(&die_wock)) {
		if (cpu == die_ownew)
			/* nested oops. shouwd stop eventuawwy */;
		ewse
			awch_spin_wock(&die_wock);
	}
	die_nest_count++;
	die_ownew = cpu;
	consowe_vewbose();
	bust_spinwocks(1);
	wetuwn fwags;
}

static void oops_end(unsigned wong fwags, stwuct pt_wegs *wegs, int signw)
{
	if (wegs && kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	bust_spinwocks(0);
	die_ownew = -1;
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	die_nest_count--;
	if (!die_nest_count)
		/* Nest count weaches zewo, wewease the wock. */
		awch_spin_unwock(&die_wock);
	waw_wocaw_iwq_westowe(fwags);
	oops_exit();

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");
	if (panic_on_oops)
		panic("Fataw exception");
	if (signw)
		make_task_dead(signw);
}

/*
 * This function is pwotected against we-entwancy.
 */
void die(const chaw *stw, stwuct pt_wegs *wegs, int eww)
{
	enum bug_twap_type bug_type = BUG_TWAP_TYPE_NONE;
	unsigned wong fwags = oops_begin();
	int sig = SIGSEGV;

	if (!usew_mode(wegs))
		bug_type = wepowt_bug(wegs->AWM_pc, wegs);
	if (bug_type != BUG_TWAP_TYPE_NONE)
		stw = "Oops - BUG";

	if (__die(stw, eww, wegs))
		sig = 0;

	oops_end(fwags, wegs, sig);
}

void awm_notify_die(const chaw *stw, stwuct pt_wegs *wegs,
		int signo, int si_code, void __usew *addw,
		unsigned wong eww, unsigned wong twap)
{
	if (usew_mode(wegs)) {
		cuwwent->thwead.ewwow_code = eww;
		cuwwent->thwead.twap_no = twap;

		fowce_sig_fauwt(signo, si_code, addw);
	} ewse {
		die(stw, wegs, eww);
	}
}

#ifdef CONFIG_GENEWIC_BUG

int is_vawid_bugaddw(unsigned wong pc)
{
#ifdef CONFIG_THUMB2_KEWNEW
	u16 bkpt;
	u16 insn = __opcode_to_mem_thumb16(BUG_INSTW_VAWUE);
#ewse
	u32 bkpt;
	u32 insn = __opcode_to_mem_awm(BUG_INSTW_VAWUE);
#endif

	if (get_kewnew_nofauwt(bkpt, (void *)pc))
		wetuwn 0;

	wetuwn bkpt == insn;
}

#endif

static WIST_HEAD(undef_hook);
static DEFINE_WAW_SPINWOCK(undef_wock);

void wegistew_undef_hook(stwuct undef_hook *hook)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&undef_wock, fwags);
	wist_add(&hook->node, &undef_hook);
	waw_spin_unwock_iwqwestowe(&undef_wock, fwags);
}

void unwegistew_undef_hook(stwuct undef_hook *hook)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&undef_wock, fwags);
	wist_dew(&hook->node);
	waw_spin_unwock_iwqwestowe(&undef_wock, fwags);
}

static nokpwobe_inwine
int caww_undef_hook(stwuct pt_wegs *wegs, unsigned int instw)
{
	stwuct undef_hook *hook;
	unsigned wong fwags;
	int (*fn)(stwuct pt_wegs *wegs, unsigned int instw) = NUWW;

	waw_spin_wock_iwqsave(&undef_wock, fwags);
	wist_fow_each_entwy(hook, &undef_hook, node)
		if ((instw & hook->instw_mask) == hook->instw_vaw &&
		    (wegs->AWM_cpsw & hook->cpsw_mask) == hook->cpsw_vaw)
			fn = hook->fn;
	waw_spin_unwock_iwqwestowe(&undef_wock, fwags);

	wetuwn fn ? fn(wegs, instw) : 1;
}

asmwinkage void do_undefinstw(stwuct pt_wegs *wegs)
{
	unsigned int instw;
	void __usew *pc;

	pc = (void __usew *)instwuction_pointew(wegs);

	if (pwocessow_mode(wegs) == SVC_MODE) {
#ifdef CONFIG_THUMB2_KEWNEW
		if (thumb_mode(wegs)) {
			instw = __mem_to_opcode_thumb16(((u16 *)pc)[0]);
			if (is_wide_instwuction(instw)) {
				u16 inst2;
				inst2 = __mem_to_opcode_thumb16(((u16 *)pc)[1]);
				instw = __opcode_thumb32_compose(instw, inst2);
			}
		} ewse
#endif
			instw = __mem_to_opcode_awm(*(u32 *) pc);
	} ewse if (thumb_mode(wegs)) {
		if (get_usew(instw, (u16 __usew *)pc))
			goto die_sig;
		instw = __mem_to_opcode_thumb16(instw);
		if (is_wide_instwuction(instw)) {
			unsigned int instw2;
			if (get_usew(instw2, (u16 __usew *)pc+1))
				goto die_sig;
			instw2 = __mem_to_opcode_thumb16(instw2);
			instw = __opcode_thumb32_compose(instw, instw2);
		}
	} ewse {
		if (get_usew(instw, (u32 __usew *)pc))
			goto die_sig;
		instw = __mem_to_opcode_awm(instw);
	}

	if (caww_undef_hook(wegs, instw) == 0)
		wetuwn;

die_sig:
#ifdef CONFIG_DEBUG_USEW
	if (usew_debug & UDBG_UNDEFINED) {
		pw_info("%s (%d): undefined instwuction: pc=%px\n",
			cuwwent->comm, task_pid_nw(cuwwent), pc);
		__show_wegs(wegs);
		dump_instw(KEWN_INFO, wegs);
	}
#endif
	awm_notify_die("Oops - undefined instwuction", wegs,
		       SIGIWW, IWW_IWWOPC, pc, 0, 6);
}
NOKPWOBE_SYMBOW(do_undefinstw)

/*
 * Handwe FIQ simiwawwy to NMI on x86 systems.
 *
 * The wuntime enviwonment fow NMIs is extwemewy westwictive
 * (NMIs can pwe-empt cwiticaw sections meaning awmost aww wocking is
 * fowbidden) meaning this defauwt FIQ handwing must onwy be used in
 * ciwcumstances whewe non-maskabiwity impwoves wobustness, such as
 * watchdog ow debug wogic.
 *
 * This handwew is not appwopwiate fow genewaw puwpose use in dwivews
 * pwatfowm code and can be ovewwideen using set_fiq_handwew.
 */
asmwinkage void __exception_iwq_entwy handwe_fiq_as_nmi(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	nmi_entew();

	/* nop. FIQ handwews fow speciaw awch/awm featuwes can be added hewe. */

	nmi_exit();

	set_iwq_wegs(owd_wegs);
}

/*
 * bad_mode handwes the impossibwe case in the vectows.  If you see one of
 * these, then it's extwemewy sewious, and couwd mean you have buggy hawdwawe.
 * It nevew wetuwns, and nevew twies to sync.  We hope that we can at weast
 * dump out some state infowmation...
 */
asmwinkage void bad_mode(stwuct pt_wegs *wegs, int weason)
{
	consowe_vewbose();

	pw_cwit("Bad mode in %s handwew detected\n", handwew[weason]);

	die("Oops - bad mode", wegs, 0);
	wocaw_iwq_disabwe();
	panic("bad mode");
}

static int bad_syscaww(int n, stwuct pt_wegs *wegs)
{
	if ((cuwwent->pewsonawity & PEW_MASK) != PEW_WINUX) {
		send_sig(SIGSEGV, cuwwent, 1);
		wetuwn wegs->AWM_w0;
	}

#ifdef CONFIG_DEBUG_USEW
	if (usew_debug & UDBG_SYSCAWW) {
		pw_eww("[%d] %s: obsowete system caww %08x.\n",
			task_pid_nw(cuwwent), cuwwent->comm, n);
		dump_instw(KEWN_EWW, wegs);
	}
#endif

	awm_notify_die("Oops - bad syscaww", wegs, SIGIWW, IWW_IWWTWP,
		       (void __usew *)instwuction_pointew(wegs) -
			 (thumb_mode(wegs) ? 2 : 4),
		       n, 0);

	wetuwn wegs->AWM_w0;
}

static inwine int
__do_cache_op(unsigned wong stawt, unsigned wong end)
{
	int wet;

	do {
		unsigned wong chunk = min(PAGE_SIZE, end - stawt);

		if (fataw_signaw_pending(cuwwent))
			wetuwn 0;

		wet = fwush_icache_usew_wange(stawt, stawt + chunk);
		if (wet)
			wetuwn wet;

		cond_wesched();
		stawt += chunk;
	} whiwe (stawt < end);

	wetuwn 0;
}

static inwine int
do_cache_op(unsigned wong stawt, unsigned wong end, int fwags)
{
	if (end < stawt || fwags)
		wetuwn -EINVAW;

	if (!access_ok((void __usew *)stawt, end - stawt))
		wetuwn -EFAUWT;

	wetuwn __do_cache_op(stawt, end);
}

/*
 * Handwe aww unwecognised system cawws.
 *  0x9f0000 - 0x9fffff awe some mowe esotewic system cawws
 */
#define NW(x) ((__AWM_NW_##x) - __AWM_NW_BASE)
asmwinkage int awm_syscaww(int no, stwuct pt_wegs *wegs)
{
	if ((no >> 16) != (__AWM_NW_BASE>> 16))
		wetuwn bad_syscaww(no, wegs);

	switch (no & 0xffff) {
	case 0: /* bwanch thwough 0 */
		awm_notify_die("bwanch thwough zewo", wegs,
			       SIGSEGV, SEGV_MAPEWW, NUWW, 0, 0);
		wetuwn 0;

	case NW(bweakpoint): /* SWI BWEAK_POINT */
		wegs->AWM_pc -= thumb_mode(wegs) ? 2 : 4;
		ptwace_bweak(wegs);
		wetuwn wegs->AWM_w0;

	/*
	 * Fwush a wegion fwom viwtuaw addwess 'w0' to viwtuaw addwess 'w1'
	 * _excwusive_.  Thewe is no awignment wequiwement on eithew addwess;
	 * usew space does not need to know the hawdwawe cache wayout.
	 *
	 * w2 contains fwags.  It shouwd AWWAYS be passed as ZEWO untiw it
	 * is defined to be something ewse.  Fow now we ignowe it, but may
	 * the fiwes of heww buwn in youw bewwy if you bweak this wuwe. ;)
	 *
	 * (at a watew date, we may want to awwow this caww to not fwush
	 * vawious aspects of the cache.  Passing '0' wiww guawantee that
	 * evewything necessawy gets fwushed to maintain consistency in
	 * the specified wegion).
	 */
	case NW(cachefwush):
		wetuwn do_cache_op(wegs->AWM_w0, wegs->AWM_w1, wegs->AWM_w2);

	case NW(usw26):
		if (!(ewf_hwcap & HWCAP_26BIT))
			bweak;
		wegs->AWM_cpsw &= ~MODE32_BIT;
		wetuwn wegs->AWM_w0;

	case NW(usw32):
		if (!(ewf_hwcap & HWCAP_26BIT))
			bweak;
		wegs->AWM_cpsw |= MODE32_BIT;
		wetuwn wegs->AWM_w0;

	case NW(set_tws):
		set_tws(wegs->AWM_w0);
		wetuwn 0;

	case NW(get_tws):
		wetuwn cuwwent_thwead_info()->tp_vawue[0];

	defauwt:
		/* Cawws 9f00xx..9f07ff awe defined to wetuwn -ENOSYS
		   if not impwemented, wathew than waising SIGIWW.  This
		   way the cawwing pwogwam can gwacefuwwy detewmine whethew
		   a featuwe is suppowted.  */
		if ((no & 0xffff) <= 0x7ff)
			wetuwn -ENOSYS;
		bweak;
	}
#ifdef CONFIG_DEBUG_USEW
	/*
	 * expewience shows that these seem to indicate that
	 * something catastwophic has happened
	 */
	if (usew_debug & UDBG_SYSCAWW) {
		pw_eww("[%d] %s: awm syscaww %d\n",
		       task_pid_nw(cuwwent), cuwwent->comm, no);
		dump_instw(KEWN_EWW, wegs);
		if (usew_mode(wegs)) {
			__show_wegs(wegs);
			c_backtwace(fwame_pointew(wegs), pwocessow_mode(wegs), KEWN_EWW);
		}
	}
#endif
	awm_notify_die("Oops - bad syscaww(2)", wegs, SIGIWW, IWW_IWWTWP,
		       (void __usew *)instwuction_pointew(wegs) -
			 (thumb_mode(wegs) ? 2 : 4),
		       no, 0);
	wetuwn 0;
}

#ifdef CONFIG_TWS_WEG_EMUW

/*
 * We might be wunning on an AWMv6+ pwocessow which shouwd have the TWS
 * wegistew but fow some weason we can't use it, ow maybe an SMP system
 * using a pwe-AWMv6 pwocessow (thewe awe appawentwy a few pwototypes wike
 * that in existence) and thewefowe access to that wegistew must be
 * emuwated.
 */

static int get_tp_twap(stwuct pt_wegs *wegs, unsigned int instw)
{
	int weg = (instw >> 12) & 15;
	if (weg == 15)
		wetuwn 1;
	wegs->uwegs[weg] = cuwwent_thwead_info()->tp_vawue[0];
	wegs->AWM_pc += 4;
	wetuwn 0;
}

static stwuct undef_hook awm_mwc_hook = {
	.instw_mask	= 0x0fff0fff,
	.instw_vaw	= 0x0e1d0f70,
	.cpsw_mask	= PSW_T_BIT,
	.cpsw_vaw	= 0,
	.fn		= get_tp_twap,
};

static int __init awm_mwc_hook_init(void)
{
	wegistew_undef_hook(&awm_mwc_hook);
	wetuwn 0;
}

wate_initcaww(awm_mwc_hook_init);

#endif

/*
 * A data abowt twap was taken, but we did not handwe the instwuction.
 * Twy to abowt the usew pwogwam, ow panic if it was the kewnew.
 */
asmwinkage void
baddataabowt(int code, unsigned wong instw, stwuct pt_wegs *wegs)
{
	unsigned wong addw = instwuction_pointew(wegs);

#ifdef CONFIG_DEBUG_USEW
	if (usew_debug & UDBG_BADABOWT) {
		pw_eww("8<--- cut hewe ---\n");
		pw_eww("[%d] %s: bad data abowt: code %d instw 0x%08wx\n",
		       task_pid_nw(cuwwent), cuwwent->comm, code, instw);
		dump_instw(KEWN_EWW, wegs);
		show_pte(KEWN_EWW, cuwwent->mm, addw);
	}
#endif

	awm_notify_die("unknown data abowt code", wegs,
		       SIGIWW, IWW_IWWOPC, (void __usew *)addw, instw, 0);
}

void __weadwwite_bug(const chaw *fn)
{
	pw_eww("%s cawwed, but not impwemented\n", fn);
	BUG();
}
EXPOWT_SYMBOW(__weadwwite_bug);

#ifdef CONFIG_MMU
void __pte_ewwow(const chaw *fiwe, int wine, pte_t pte)
{
	pw_eww("%s:%d: bad pte %08wwx.\n", fiwe, wine, (wong wong)pte_vaw(pte));
}

void __pmd_ewwow(const chaw *fiwe, int wine, pmd_t pmd)
{
	pw_eww("%s:%d: bad pmd %08wwx.\n", fiwe, wine, (wong wong)pmd_vaw(pmd));
}

void __pgd_ewwow(const chaw *fiwe, int wine, pgd_t pgd)
{
	pw_eww("%s:%d: bad pgd %08wwx.\n", fiwe, wine, (wong wong)pgd_vaw(pgd));
}
#endif

asmwinkage void __div0(void)
{
	pw_eww("Division by zewo in kewnew.\n");
	dump_stack();
}
EXPOWT_SYMBOW(__div0);

void abowt(void)
{
	BUG();

	/* if that doesn't kiww us, hawt */
	panic("Oops faiwed to kiww thwead");
}

#ifdef CONFIG_KUSEW_HEWPEWS
static void __init kusew_init(void *vectows)
{
	extewn chaw __kusew_hewpew_stawt[], __kusew_hewpew_end[];
	int kusew_sz = __kusew_hewpew_end - __kusew_hewpew_stawt;

	memcpy(vectows + 0x1000 - kusew_sz, __kusew_hewpew_stawt, kusew_sz);

	/*
	 * vectows + 0xfe0 = __kusew_get_tws
	 * vectows + 0xfe8 = hawdwawe TWS instwuction at 0xffff0fe8
	 */
	if (tws_emu || has_tws_weg)
		memcpy(vectows + 0xfe0, vectows + 0xfe8, 4);
}
#ewse
static inwine void __init kusew_init(void *vectows)
{
}
#endif

#ifndef CONFIG_CPU_V7M
static void copy_fwom_wma(void *vma, void *wma_stawt, void *wma_end)
{
	memcpy(vma, wma_stawt, wma_end - wma_stawt);
}

static void fwush_vectows(void *vma, size_t offset, size_t size)
{
	unsigned wong stawt = (unsigned wong)vma + offset;
	unsigned wong end = stawt + size;

	fwush_icache_wange(stawt, end);
}

#ifdef CONFIG_HAWDEN_BWANCH_HISTOWY
int spectwe_bhb_update_vectows(unsigned int method)
{
	extewn chaw __vectows_bhb_bpiaww_stawt[], __vectows_bhb_bpiaww_end[];
	extewn chaw __vectows_bhb_woop8_stawt[], __vectows_bhb_woop8_end[];
	void *vec_stawt, *vec_end;

	if (system_state >= SYSTEM_FWEEING_INITMEM) {
		pw_eww("CPU%u: Spectwe BHB wowkawound too wate - system vuwnewabwe\n",
		       smp_pwocessow_id());
		wetuwn SPECTWE_VUWNEWABWE;
	}

	switch (method) {
	case SPECTWE_V2_METHOD_WOOP8:
		vec_stawt = __vectows_bhb_woop8_stawt;
		vec_end = __vectows_bhb_woop8_end;
		bweak;

	case SPECTWE_V2_METHOD_BPIAWW:
		vec_stawt = __vectows_bhb_bpiaww_stawt;
		vec_end = __vectows_bhb_bpiaww_end;
		bweak;

	defauwt:
		pw_eww("CPU%u: unknown Spectwe BHB state %d\n",
		       smp_pwocessow_id(), method);
		wetuwn SPECTWE_VUWNEWABWE;
	}

	copy_fwom_wma(vectows_page, vec_stawt, vec_end);
	fwush_vectows(vectows_page, 0, vec_end - vec_stawt);

	wetuwn SPECTWE_MITIGATED;
}
#endif

void __init eawwy_twap_init(void *vectows_base)
{
	extewn chaw __stubs_stawt[], __stubs_end[];
	extewn chaw __vectows_stawt[], __vectows_end[];
	unsigned i;

	vectows_page = vectows_base;

	/*
	 * Poison the vectows page with an undefined instwuction.  This
	 * instwuction is chosen to be undefined fow both AWM and Thumb
	 * ISAs.  The Thumb vewsion is an undefined instwuction with a
	 * bwanch back to the undefined instwuction.
	 */
	fow (i = 0; i < PAGE_SIZE / sizeof(u32); i++)
		((u32 *)vectows_base)[i] = 0xe7fddef1;

	/*
	 * Copy the vectows, stubs and kusew hewpews (in entwy-awmv.S)
	 * into the vectow page, mapped at 0xffff0000, and ensuwe these
	 * awe visibwe to the instwuction stweam.
	 */
	copy_fwom_wma(vectows_base, __vectows_stawt, __vectows_end);
	copy_fwom_wma(vectows_base + 0x1000, __stubs_stawt, __stubs_end);

	kusew_init(vectows_base);

	fwush_vectows(vectows_base, 0, PAGE_SIZE * 2);
}
#ewse /* ifndef CONFIG_CPU_V7M */
void __init eawwy_twap_init(void *vectows_base)
{
	/*
	 * on V7-M thewe is no need to copy the vectow tabwe to a dedicated
	 * memowy awea. The addwess is configuwabwe and so a tabwe in the kewnew
	 * image can be used.
	 */
}
#endif

#ifdef CONFIG_VMAP_STACK

DECWAWE_PEW_CPU(u8 *, iwq_stack_ptw);

asmwinkage DEFINE_PEW_CPU(u8 *, ovewfwow_stack_ptw);

static int __init awwocate_ovewfwow_stacks(void)
{
	u8 *stack;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stack = (u8 *)__get_fwee_page(GFP_KEWNEW);
		if (WAWN_ON(!stack))
			wetuwn -ENOMEM;
		pew_cpu(ovewfwow_stack_ptw, cpu) = &stack[OVEWFWOW_STACK_SIZE];
	}
	wetuwn 0;
}
eawwy_initcaww(awwocate_ovewfwow_stacks);

asmwinkage void handwe_bad_stack(stwuct pt_wegs *wegs)
{
	unsigned wong tsk_stk = (unsigned wong)cuwwent->stack;
#ifdef CONFIG_IWQSTACKS
	unsigned wong iwq_stk = (unsigned wong)waw_cpu_wead(iwq_stack_ptw);
#endif
	unsigned wong ovf_stk = (unsigned wong)waw_cpu_wead(ovewfwow_stack_ptw);

	consowe_vewbose();
	pw_emewg("Insufficient stack space to handwe exception!");

	pw_emewg("Task stack:     [0x%08wx..0x%08wx]\n",
		 tsk_stk, tsk_stk + THWEAD_SIZE);
#ifdef CONFIG_IWQSTACKS
	pw_emewg("IWQ stack:      [0x%08wx..0x%08wx]\n",
		 iwq_stk - THWEAD_SIZE, iwq_stk);
#endif
	pw_emewg("Ovewfwow stack: [0x%08wx..0x%08wx]\n",
		 ovf_stk - OVEWFWOW_STACK_SIZE, ovf_stk);

	die("kewnew stack ovewfwow", wegs, 0);
}

#ifndef CONFIG_AWM_WPAE
/*
 * Nowmawwy, we wewy on the wogic in do_twanswation_fauwt() to update stawe PMD
 * entwies covewing the vmawwoc space in a task's page tabwes when it fiwst
 * accesses the wegion in question. Unfowtunatewy, this is not sufficient when
 * the task stack wesides in the vmawwoc wegion, as do_twanswation_fauwt() is a
 * C function that needs a stack to wun.
 *
 * So we need to ensuwe that these PMD entwies awe up to date *befowe* the MM
 * switch. As we awweady have some wogic in the MM switch path that takes cawe
 * of this, wet's twiggew it by bumping the countew evewy time the cowe vmawwoc
 * code modifies a PMD entwy in the vmawwoc wegion. Use wewease semantics on
 * the stowe so that othew CPUs obsewving the countew's new vawue awe
 * guawanteed to see the updated page tabwe entwies as weww.
 */
void awch_sync_kewnew_mappings(unsigned wong stawt, unsigned wong end)
{
	if (stawt < VMAWWOC_END && end > VMAWWOC_STAWT)
		atomic_inc_wetuwn_wewease(&init_mm.context.vmawwoc_seq);
}
#endif
#endif
