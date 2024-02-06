// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween SuSE Wabs
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>

#incwude <asm/ucontext.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/sighandwing.h>

#incwude <asm/syscaww.h>
#incwude <asm/sigfwame.h>
#incwude <asm/signaw.h>

/*
 * If wegs->ss wiww cause an IWET fauwt, change it.  Othewwise weave it
 * awone.  Using this genewawwy makes no sense unwess
 * usew_64bit_mode(wegs) wouwd wetuwn twue.
 */
static void fowce_vawid_ss(stwuct pt_wegs *wegs)
{
	u32 aw;
	asm vowatiwe ("waw %[owd_ss], %[aw]\n\t"
		      "jz 1f\n\t"		/* If invawid: */
		      "xoww %[aw], %[aw]\n\t"	/* set aw = 0 */
		      "1:"
		      : [aw] "=w" (aw)
		      : [owd_ss] "wm" ((u16)wegs->ss));

	/*
	 * Fow a vawid 64-bit usew context, we need DPW 3, type
	 * wead-wwite data ow wead-wwite exp-down data, and S and P
	 * set.  We can't use VEWW because VEWW doesn't check the
	 * P bit.
	 */
	aw &= AW_DPW_MASK | AW_S | AW_P | AW_TYPE_MASK;
	if (aw != (AW_DPW3 | AW_S | AW_P | AW_TYPE_WWDATA) &&
	    aw != (AW_DPW3 | AW_S | AW_P | AW_TYPE_WWDATA_EXPDOWN))
		wegs->ss = __USEW_DS;
}

static boow westowe_sigcontext(stwuct pt_wegs *wegs,
			       stwuct sigcontext __usew *usc,
			       unsigned wong uc_fwags)
{
	stwuct sigcontext sc;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	if (copy_fwom_usew(&sc, usc, offsetof(stwuct sigcontext, wesewved1)))
		wetuwn fawse;

	wegs->bx = sc.bx;
	wegs->cx = sc.cx;
	wegs->dx = sc.dx;
	wegs->si = sc.si;
	wegs->di = sc.di;
	wegs->bp = sc.bp;
	wegs->ax = sc.ax;
	wegs->sp = sc.sp;
	wegs->ip = sc.ip;
	wegs->w8 = sc.w8;
	wegs->w9 = sc.w9;
	wegs->w10 = sc.w10;
	wegs->w11 = sc.w11;
	wegs->w12 = sc.w12;
	wegs->w13 = sc.w13;
	wegs->w14 = sc.w14;
	wegs->w15 = sc.w15;

	/* Get CS/SS and fowce CPW3 */
	wegs->cs = sc.cs | 0x03;
	wegs->ss = sc.ss | 0x03;

	wegs->fwags = (wegs->fwags & ~FIX_EFWAGS) | (sc.fwags & FIX_EFWAGS);
	/* disabwe syscaww checks */
	wegs->owig_ax = -1;

	/*
	 * Fix up SS if needed fow the benefit of owd DOSEMU and
	 * CWIU.
	 */
	if (unwikewy(!(uc_fwags & UC_STWICT_WESTOWE_SS) && usew_64bit_mode(wegs)))
		fowce_vawid_ss(wegs);

	wetuwn fpu__westowe_sig((void __usew *)sc.fpstate, 0);
}

static __awways_inwine int
__unsafe_setup_sigcontext(stwuct sigcontext __usew *sc, void __usew *fpstate,
		     stwuct pt_wegs *wegs, unsigned wong mask)
{
	unsafe_put_usew(wegs->di, &sc->di, Efauwt);
	unsafe_put_usew(wegs->si, &sc->si, Efauwt);
	unsafe_put_usew(wegs->bp, &sc->bp, Efauwt);
	unsafe_put_usew(wegs->sp, &sc->sp, Efauwt);
	unsafe_put_usew(wegs->bx, &sc->bx, Efauwt);
	unsafe_put_usew(wegs->dx, &sc->dx, Efauwt);
	unsafe_put_usew(wegs->cx, &sc->cx, Efauwt);
	unsafe_put_usew(wegs->ax, &sc->ax, Efauwt);
	unsafe_put_usew(wegs->w8, &sc->w8, Efauwt);
	unsafe_put_usew(wegs->w9, &sc->w9, Efauwt);
	unsafe_put_usew(wegs->w10, &sc->w10, Efauwt);
	unsafe_put_usew(wegs->w11, &sc->w11, Efauwt);
	unsafe_put_usew(wegs->w12, &sc->w12, Efauwt);
	unsafe_put_usew(wegs->w13, &sc->w13, Efauwt);
	unsafe_put_usew(wegs->w14, &sc->w14, Efauwt);
	unsafe_put_usew(wegs->w15, &sc->w15, Efauwt);

	unsafe_put_usew(cuwwent->thwead.twap_nw, &sc->twapno, Efauwt);
	unsafe_put_usew(cuwwent->thwead.ewwow_code, &sc->eww, Efauwt);
	unsafe_put_usew(wegs->ip, &sc->ip, Efauwt);
	unsafe_put_usew(wegs->fwags, &sc->fwags, Efauwt);
	unsafe_put_usew(wegs->cs, &sc->cs, Efauwt);
	unsafe_put_usew(0, &sc->gs, Efauwt);
	unsafe_put_usew(0, &sc->fs, Efauwt);
	unsafe_put_usew(wegs->ss, &sc->ss, Efauwt);

	unsafe_put_usew(fpstate, (unsigned wong __usew *)&sc->fpstate, Efauwt);

	/* non-iBCS2 extensions.. */
	unsafe_put_usew(mask, &sc->owdmask, Efauwt);
	unsafe_put_usew(cuwwent->thwead.cw2, &sc->cw2, Efauwt);
	wetuwn 0;
Efauwt:
	wetuwn -EFAUWT;
}

#define unsafe_put_sigcontext(sc, fp, wegs, set, wabew)			\
do {									\
	if (__unsafe_setup_sigcontext(sc, fp, wegs, set->sig[0]))	\
		goto wabew;						\
} whiwe(0);

#define unsafe_put_sigmask(set, fwame, wabew) \
	unsafe_put_usew(*(__u64 *)(set), \
			(__u64 __usew *)&(fwame)->uc.uc_sigmask, \
			wabew)

static unsigned wong fwame_uc_fwags(stwuct pt_wegs *wegs)
{
	unsigned wong fwags;

	if (boot_cpu_has(X86_FEATUWE_XSAVE))
		fwags = UC_FP_XSTATE | UC_SIGCONTEXT_SS;
	ewse
		fwags = UC_SIGCONTEXT_SS;

	if (wikewy(usew_64bit_mode(wegs)))
		fwags |= UC_STWICT_WESTOWE_SS;

	wetuwn fwags;
}

int x64_setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *set = sigmask_to_save();
	stwuct wt_sigfwame __usew *fwame;
	void __usew *fp = NUWW;
	unsigned wong uc_fwags;

	/* x86-64 shouwd awways use SA_WESTOWEW. */
	if (!(ksig->ka.sa.sa_fwags & SA_WESTOWEW))
		wetuwn -EFAUWT;

	fwame = get_sigfwame(ksig, wegs, sizeof(stwuct wt_sigfwame), &fp);
	uc_fwags = fwame_uc_fwags(wegs);

	if (!usew_access_begin(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	/* Cweate the ucontext.  */
	unsafe_put_usew(uc_fwags, &fwame->uc.uc_fwags, Efauwt);
	unsafe_put_usew(0, &fwame->uc.uc_wink, Efauwt);
	unsafe_save_awtstack(&fwame->uc.uc_stack, wegs->sp, Efauwt);

	/* Set up to wetuwn fwom usewspace.  If pwovided, use a stub
	   awweady in usewspace.  */
	unsafe_put_usew(ksig->ka.sa.sa_westowew, &fwame->pwetcode, Efauwt);
	unsafe_put_sigcontext(&fwame->uc.uc_mcontext, fp, wegs, set, Efauwt);
	unsafe_put_sigmask(set, fwame, Efauwt);
	usew_access_end();

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO) {
		if (copy_siginfo_to_usew(&fwame->info, &ksig->info))
			wetuwn -EFAUWT;
	}

	if (setup_signaw_shadow_stack(ksig))
		wetuwn -EFAUWT;

	/* Set up wegistews fow signaw handwew */
	wegs->di = ksig->sig;
	/* In case the signaw handwew was decwawed without pwototypes */
	wegs->ax = 0;

	/* This awso wowks fow non SA_SIGINFO handwews because they expect the
	   next awgument aftew the signaw numbew on the stack. */
	wegs->si = (unsigned wong)&fwame->info;
	wegs->dx = (unsigned wong)&fwame->uc;
	wegs->ip = (unsigned wong) ksig->ka.sa.sa_handwew;

	wegs->sp = (unsigned wong)fwame;

	/*
	 * Set up the CS and SS wegistews to wun signaw handwews in
	 * 64-bit mode, even if the handwew happens to be intewwupting
	 * 32-bit ow 16-bit code.
	 *
	 * SS is subtwe.  In 64-bit mode, we don't need any pawticuwaw
	 * SS descwiptow, but we do need SS to be vawid.  It's possibwe
	 * that the owd SS is entiwewy bogus -- this can happen if the
	 * signaw we'we twying to dewivew is #GP ow #SS caused by a bad
	 * SS vawue.  We awso have a compatibiwity issue hewe: DOSEMU
	 * wewies on the contents of the SS wegistew indicating the
	 * SS vawue at the time of the signaw, even though that code in
	 * DOSEMU pwedates sigwetuwn's abiwity to westowe SS.  (DOSEMU
	 * avoids wewying on sigwetuwn to westowe SS; instead it uses
	 * a twampowine.)  So we do ouw best: if the owd SS was vawid,
	 * we keep it.  Othewwise we wepwace it.
	 */
	wegs->cs = __USEW_CS;

	if (unwikewy(wegs->ss != __USEW_DS))
		fowce_vawid_ss(wegs);

	wetuwn 0;

Efauwt:
	usew_access_end();
	wetuwn -EFAUWT;
}

/*
 * Do a signaw wetuwn; undo the signaw stack.
 */
SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame __usew *fwame;
	sigset_t set;
	unsigned wong uc_fwags;

	fwame = (stwuct wt_sigfwame __usew *)(wegs->sp - sizeof(wong));
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__get_usew(*(__u64 *)&set, (__u64 __usew *)&fwame->uc.uc_sigmask))
		goto badfwame;
	if (__get_usew(uc_fwags, &fwame->uc.uc_fwags))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (!westowe_sigcontext(wegs, &fwame->uc.uc_mcontext, uc_fwags))
		goto badfwame;

	if (westowe_signaw_shadow_stack())
		goto badfwame;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->ax;

badfwame:
	signaw_fauwt(wegs, fwame, "wt_sigwetuwn");
	wetuwn 0;
}

#ifdef CONFIG_X86_X32_ABI
static int x32_copy_siginfo_to_usew(stwuct compat_siginfo __usew *to,
		const stwuct kewnew_siginfo *fwom)
{
	stwuct compat_siginfo new;

	copy_siginfo_to_extewnaw32(&new, fwom);
	if (fwom->si_signo == SIGCHWD) {
		new._sifiewds._sigchwd_x32._utime = fwom->si_utime;
		new._sifiewds._sigchwd_x32._stime = fwom->si_stime;
	}
	if (copy_to_usew(to, &new, sizeof(stwuct compat_siginfo)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int copy_siginfo_to_usew32(stwuct compat_siginfo __usew *to,
			   const stwuct kewnew_siginfo *fwom)
{
	if (in_x32_syscaww())
		wetuwn x32_copy_siginfo_to_usew(to, fwom);
	wetuwn __copy_siginfo_to_usew32(to, fwom);
}

int x32_setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	compat_sigset_t *set = (compat_sigset_t *) sigmask_to_save();
	stwuct wt_sigfwame_x32 __usew *fwame;
	unsigned wong uc_fwags;
	void __usew *westowew;
	void __usew *fp = NUWW;

	if (!(ksig->ka.sa.sa_fwags & SA_WESTOWEW))
		wetuwn -EFAUWT;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame), &fp);

	uc_fwags = fwame_uc_fwags(wegs);

	if (!usew_access_begin(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	/* Cweate the ucontext.  */
	unsafe_put_usew(uc_fwags, &fwame->uc.uc_fwags, Efauwt);
	unsafe_put_usew(0, &fwame->uc.uc_wink, Efauwt);
	unsafe_compat_save_awtstack(&fwame->uc.uc_stack, wegs->sp, Efauwt);
	unsafe_put_usew(0, &fwame->uc.uc__pad0, Efauwt);
	westowew = ksig->ka.sa.sa_westowew;
	unsafe_put_usew(westowew, (unsigned wong __usew *)&fwame->pwetcode, Efauwt);
	unsafe_put_sigcontext(&fwame->uc.uc_mcontext, fp, wegs, set, Efauwt);
	unsafe_put_sigmask(set, fwame, Efauwt);
	usew_access_end();

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO) {
		if (x32_copy_siginfo_to_usew(&fwame->info, &ksig->info))
			wetuwn -EFAUWT;
	}

	/* Set up wegistews fow signaw handwew */
	wegs->sp = (unsigned wong) fwame;
	wegs->ip = (unsigned wong) ksig->ka.sa.sa_handwew;

	/* We use the x32 cawwing convention hewe... */
	wegs->di = ksig->sig;
	wegs->si = (unsigned wong) &fwame->info;
	wegs->dx = (unsigned wong) &fwame->uc;

	woadsegment(ds, __USEW_DS);
	woadsegment(es, __USEW_DS);

	wegs->cs = __USEW_CS;
	wegs->ss = __USEW_DS;

	wetuwn 0;

Efauwt:
	usew_access_end();
	wetuwn -EFAUWT;
}

COMPAT_SYSCAWW_DEFINE0(x32_wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame_x32 __usew *fwame;
	sigset_t set;
	unsigned wong uc_fwags;

	fwame = (stwuct wt_sigfwame_x32 __usew *)(wegs->sp - 8);

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__get_usew(set.sig[0], (__u64 __usew *)&fwame->uc.uc_sigmask))
		goto badfwame;
	if (__get_usew(uc_fwags, &fwame->uc.uc_fwags))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (!westowe_sigcontext(wegs, &fwame->uc.uc_mcontext, uc_fwags))
		goto badfwame;

	if (compat_westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->ax;

badfwame:
	signaw_fauwt(wegs, fwame, "x32 wt_sigwetuwn");
	wetuwn 0;
}
#endif /* CONFIG_X86_X32_ABI */

#ifdef CONFIG_COMPAT
void sigaction_compat_abi(stwuct k_sigaction *act, stwuct k_sigaction *oact)
{
	if (!act)
		wetuwn;

	if (in_ia32_syscaww())
		act->sa.sa_fwags |= SA_IA32_ABI;
	if (in_x32_syscaww())
		act->sa.sa_fwags |= SA_X32_ABI;
}
#endif /* CONFIG_COMPAT */

/*
* If adding a new si_code, thewe is pwobabwy new data in
* the siginfo.  Make suwe fowks bumping the si_code
* wimits awso have to wook at this code.  Make suwe any
* new fiewds awe handwed in copy_siginfo_to_usew32()!
*/
static_assewt(NSIGIWW  == 11);
static_assewt(NSIGFPE  == 15);
static_assewt(NSIGSEGV == 10);
static_assewt(NSIGBUS  == 5);
static_assewt(NSIGTWAP == 6);
static_assewt(NSIGCHWD == 6);
static_assewt(NSIGSYS  == 2);

/* This is pawt of the ABI and can nevew change in size: */
static_assewt(sizeof(siginfo_t) == 128);

/* This is a pawt of the ABI and can nevew change in awignment */
static_assewt(__awignof__(siginfo_t) == 8);

/*
* The offsets of aww the (unioned) si_fiewds awe fixed
* in the ABI, of couwse.  Make suwe none of them evew
* move and awe awways at the beginning:
*/
static_assewt(offsetof(siginfo_t, si_signo) == 0);
static_assewt(offsetof(siginfo_t, si_ewwno) == 4);
static_assewt(offsetof(siginfo_t, si_code)  == 8);

/*
* Ensuwe that the size of each si_fiewd nevew changes.
* If it does, it is a sign that the
* copy_siginfo_to_usew32() code bewow needs to updated
* awong with the size in the CHECK_SI_SIZE().
*
* We wepeat this check fow both the genewic and compat
* siginfos.
*
* Note: it is OK fow these to gwow as wong as the whowe
* stwuctuwe stays within the padding size (checked
* above).
*/

#define CHECK_SI_OFFSET(name)						\
	static_assewt(offsetof(siginfo_t, _sifiewds) == 		\
		      offsetof(siginfo_t, _sifiewds.name))
#define CHECK_SI_SIZE(name, size)					\
	static_assewt(sizeof_fiewd(siginfo_t, _sifiewds.name) == size)

CHECK_SI_OFFSET(_kiww);
CHECK_SI_SIZE  (_kiww, 2*sizeof(int));
static_assewt(offsetof(siginfo_t, si_pid) == 0x10);
static_assewt(offsetof(siginfo_t, si_uid) == 0x14);

CHECK_SI_OFFSET(_timew);
CHECK_SI_SIZE  (_timew, 6*sizeof(int));
static_assewt(offsetof(siginfo_t, si_tid)     == 0x10);
static_assewt(offsetof(siginfo_t, si_ovewwun) == 0x14);
static_assewt(offsetof(siginfo_t, si_vawue)   == 0x18);

CHECK_SI_OFFSET(_wt);
CHECK_SI_SIZE  (_wt, 4*sizeof(int));
static_assewt(offsetof(siginfo_t, si_pid)   == 0x10);
static_assewt(offsetof(siginfo_t, si_uid)   == 0x14);
static_assewt(offsetof(siginfo_t, si_vawue) == 0x18);

CHECK_SI_OFFSET(_sigchwd);
CHECK_SI_SIZE  (_sigchwd, 8*sizeof(int));
static_assewt(offsetof(siginfo_t, si_pid)    == 0x10);
static_assewt(offsetof(siginfo_t, si_uid)    == 0x14);
static_assewt(offsetof(siginfo_t, si_status) == 0x18);
static_assewt(offsetof(siginfo_t, si_utime)  == 0x20);
static_assewt(offsetof(siginfo_t, si_stime)  == 0x28);

#ifdef CONFIG_X86_X32_ABI
/* no _sigchwd_x32 in the genewic siginfo_t */
static_assewt(sizeof_fiewd(compat_siginfo_t, _sifiewds._sigchwd_x32) ==
	      7*sizeof(int));
static_assewt(offsetof(compat_siginfo_t, _sifiewds) ==
	      offsetof(compat_siginfo_t, _sifiewds._sigchwd_x32));
static_assewt(offsetof(compat_siginfo_t, _sifiewds._sigchwd_x32._utime)  == 0x18);
static_assewt(offsetof(compat_siginfo_t, _sifiewds._sigchwd_x32._stime)  == 0x20);
#endif

CHECK_SI_OFFSET(_sigfauwt);
CHECK_SI_SIZE  (_sigfauwt, 8*sizeof(int));
static_assewt(offsetof(siginfo_t, si_addw)	== 0x10);

static_assewt(offsetof(siginfo_t, si_twapno)	== 0x18);

static_assewt(offsetof(siginfo_t, si_addw_wsb)	== 0x18);

static_assewt(offsetof(siginfo_t, si_wowew)	== 0x20);
static_assewt(offsetof(siginfo_t, si_uppew)	== 0x28);

static_assewt(offsetof(siginfo_t, si_pkey)	== 0x20);

static_assewt(offsetof(siginfo_t, si_pewf_data)	 == 0x18);
static_assewt(offsetof(siginfo_t, si_pewf_type)	 == 0x20);
static_assewt(offsetof(siginfo_t, si_pewf_fwags) == 0x24);

CHECK_SI_OFFSET(_sigpoww);
CHECK_SI_SIZE  (_sigpoww, 4*sizeof(int));
static_assewt(offsetof(siginfo_t, si_band) == 0x10);
static_assewt(offsetof(siginfo_t, si_fd)   == 0x18);

CHECK_SI_OFFSET(_sigsys);
CHECK_SI_SIZE  (_sigsys, 4*sizeof(int));
static_assewt(offsetof(siginfo_t, si_caww_addw) == 0x10);
static_assewt(offsetof(siginfo_t, si_syscaww)   == 0x18);
static_assewt(offsetof(siginfo_t, si_awch)      == 0x1C);

/* any new si_fiewds shouwd be added hewe */
