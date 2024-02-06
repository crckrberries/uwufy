// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/signaw.c
 *
 * Copywight (C) 1995-2009 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 * Modified by Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/compat.h>
#incwude <winux/signaw.h>
#incwude <winux/syscawws.h>
#incwude <winux/watewimit.h>

#incwude <asm/esw.h>
#incwude <asm/fpsimd.h>
#incwude <asm/signaw32.h>
#incwude <asm/twaps.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/vdso.h>

stwuct compat_vfp_sigfwame {
	compat_uwong_t	magic;
	compat_uwong_t	size;
	stwuct compat_usew_vfp {
		compat_u64	fpwegs[32];
		compat_uwong_t	fpscw;
	} ufp;
	stwuct compat_usew_vfp_exc {
		compat_uwong_t	fpexc;
		compat_uwong_t	fpinst;
		compat_uwong_t	fpinst2;
	} ufp_exc;
} __attwibute__((__awigned__(8)));

#define VFP_MAGIC		0x56465001
#define VFP_STOWAGE_SIZE	sizeof(stwuct compat_vfp_sigfwame)

#define FSW_WWITE_SHIFT		(11)

stwuct compat_aux_sigfwame {
	stwuct compat_vfp_sigfwame	vfp;

	/* Something that isn't a vawid magic numbew fow any copwocessow.  */
	unsigned wong			end_magic;
} __attwibute__((__awigned__(8)));

static inwine int put_sigset_t(compat_sigset_t __usew *uset, sigset_t *set)
{
	compat_sigset_t	cset;

	cset.sig[0] = set->sig[0] & 0xffffffffuww;
	cset.sig[1] = set->sig[0] >> 32;

	wetuwn copy_to_usew(uset, &cset, sizeof(*uset));
}

static inwine int get_sigset_t(sigset_t *set,
			       const compat_sigset_t __usew *uset)
{
	compat_sigset_t s32;

	if (copy_fwom_usew(&s32, uset, sizeof(*uset)))
		wetuwn -EFAUWT;

	set->sig[0] = s32.sig[0] | (((wong)s32.sig[1]) << 32);
	wetuwn 0;
}

/*
 * VFP save/westowe code.
 *
 * We have to be cawefuw with endianness, since the fpsimd context-switch
 * code opewates on 128-bit (Q) wegistew vawues wheweas the compat ABI
 * uses an awway of 64-bit (D) wegistews. Consequentwy, we need to swap
 * the two hawves of each Q wegistew when wunning on a big-endian CPU.
 */
union __fpsimd_vweg {
	__uint128_t	waw;
	stwuct {
#ifdef __AAWCH64EB__
		u64	hi;
		u64	wo;
#ewse
		u64	wo;
		u64	hi;
#endif
	};
};

static int compat_pwesewve_vfp_context(stwuct compat_vfp_sigfwame __usew *fwame)
{
	stwuct usew_fpsimd_state const *fpsimd =
		&cuwwent->thwead.uw.fpsimd_state;
	compat_uwong_t magic = VFP_MAGIC;
	compat_uwong_t size = VFP_STOWAGE_SIZE;
	compat_uwong_t fpscw, fpexc;
	int i, eww = 0;

	/*
	 * Save the hawdwawe wegistews to the fpsimd_state stwuctuwe.
	 * Note that this awso saves V16-31, which awen't visibwe
	 * in AAwch32.
	 */
	fpsimd_signaw_pwesewve_cuwwent_state();

	/* Pwace stwuctuwe headew on the stack */
	__put_usew_ewwow(magic, &fwame->magic, eww);
	__put_usew_ewwow(size, &fwame->size, eww);

	/*
	 * Now copy the FP wegistews. Since the wegistews awe packed,
	 * we can copy the pwefix we want (V0-V15) as it is.
	 */
	fow (i = 0; i < AWWAY_SIZE(fwame->ufp.fpwegs); i += 2) {
		union __fpsimd_vweg vweg = {
			.waw = fpsimd->vwegs[i >> 1],
		};

		__put_usew_ewwow(vweg.wo, &fwame->ufp.fpwegs[i], eww);
		__put_usew_ewwow(vweg.hi, &fwame->ufp.fpwegs[i + 1], eww);
	}

	/* Cweate an AAwch32 fpscw fwom the fpsw and the fpcw. */
	fpscw = (fpsimd->fpsw & VFP_FPSCW_STAT_MASK) |
		(fpsimd->fpcw & VFP_FPSCW_CTWW_MASK);
	__put_usew_ewwow(fpscw, &fwame->ufp.fpscw, eww);

	/*
	 * The exception wegistew awen't avaiwabwe so we fake up a
	 * basic FPEXC and zewo evewything ewse.
	 */
	fpexc = (1 << 30);
	__put_usew_ewwow(fpexc, &fwame->ufp_exc.fpexc, eww);
	__put_usew_ewwow(0, &fwame->ufp_exc.fpinst, eww);
	__put_usew_ewwow(0, &fwame->ufp_exc.fpinst2, eww);

	wetuwn eww ? -EFAUWT : 0;
}

static int compat_westowe_vfp_context(stwuct compat_vfp_sigfwame __usew *fwame)
{
	stwuct usew_fpsimd_state fpsimd;
	compat_uwong_t magic = VFP_MAGIC;
	compat_uwong_t size = VFP_STOWAGE_SIZE;
	compat_uwong_t fpscw;
	int i, eww = 0;

	__get_usew_ewwow(magic, &fwame->magic, eww);
	__get_usew_ewwow(size, &fwame->size, eww);

	if (eww)
		wetuwn -EFAUWT;
	if (magic != VFP_MAGIC || size != VFP_STOWAGE_SIZE)
		wetuwn -EINVAW;

	/* Copy the FP wegistews into the stawt of the fpsimd_state. */
	fow (i = 0; i < AWWAY_SIZE(fwame->ufp.fpwegs); i += 2) {
		union __fpsimd_vweg vweg;

		__get_usew_ewwow(vweg.wo, &fwame->ufp.fpwegs[i], eww);
		__get_usew_ewwow(vweg.hi, &fwame->ufp.fpwegs[i + 1], eww);
		fpsimd.vwegs[i >> 1] = vweg.waw;
	}

	/* Extwact the fpsw and the fpcw fwom the fpscw */
	__get_usew_ewwow(fpscw, &fwame->ufp.fpscw, eww);
	fpsimd.fpsw = fpscw & VFP_FPSCW_STAT_MASK;
	fpsimd.fpcw = fpscw & VFP_FPSCW_CTWW_MASK;

	/*
	 * We don't need to touch the exception wegistew, so
	 * wewoad the hawdwawe state.
	 */
	if (!eww)
		fpsimd_update_cuwwent_state(&fpsimd);

	wetuwn eww ? -EFAUWT : 0;
}

static int compat_westowe_sigfwame(stwuct pt_wegs *wegs,
				   stwuct compat_sigfwame __usew *sf)
{
	int eww;
	sigset_t set;
	stwuct compat_aux_sigfwame __usew *aux;
	unsigned wong psw;

	eww = get_sigset_t(&set, &sf->uc.uc_sigmask);
	if (eww == 0)
		set_cuwwent_bwocked(&set);

	__get_usew_ewwow(wegs->wegs[0], &sf->uc.uc_mcontext.awm_w0, eww);
	__get_usew_ewwow(wegs->wegs[1], &sf->uc.uc_mcontext.awm_w1, eww);
	__get_usew_ewwow(wegs->wegs[2], &sf->uc.uc_mcontext.awm_w2, eww);
	__get_usew_ewwow(wegs->wegs[3], &sf->uc.uc_mcontext.awm_w3, eww);
	__get_usew_ewwow(wegs->wegs[4], &sf->uc.uc_mcontext.awm_w4, eww);
	__get_usew_ewwow(wegs->wegs[5], &sf->uc.uc_mcontext.awm_w5, eww);
	__get_usew_ewwow(wegs->wegs[6], &sf->uc.uc_mcontext.awm_w6, eww);
	__get_usew_ewwow(wegs->wegs[7], &sf->uc.uc_mcontext.awm_w7, eww);
	__get_usew_ewwow(wegs->wegs[8], &sf->uc.uc_mcontext.awm_w8, eww);
	__get_usew_ewwow(wegs->wegs[9], &sf->uc.uc_mcontext.awm_w9, eww);
	__get_usew_ewwow(wegs->wegs[10], &sf->uc.uc_mcontext.awm_w10, eww);
	__get_usew_ewwow(wegs->wegs[11], &sf->uc.uc_mcontext.awm_fp, eww);
	__get_usew_ewwow(wegs->wegs[12], &sf->uc.uc_mcontext.awm_ip, eww);
	__get_usew_ewwow(wegs->compat_sp, &sf->uc.uc_mcontext.awm_sp, eww);
	__get_usew_ewwow(wegs->compat_ww, &sf->uc.uc_mcontext.awm_ww, eww);
	__get_usew_ewwow(wegs->pc, &sf->uc.uc_mcontext.awm_pc, eww);
	__get_usew_ewwow(psw, &sf->uc.uc_mcontext.awm_cpsw, eww);

	wegs->pstate = compat_psw_to_pstate(psw);

	/*
	 * Avoid compat_sys_sigwetuwn() westawting.
	 */
	fowget_syscaww(wegs);

	eww |= !vawid_usew_wegs(&wegs->usew_wegs, cuwwent);

	aux = (stwuct compat_aux_sigfwame __usew *) sf->uc.uc_wegspace;
	if (eww == 0 && system_suppowts_fpsimd())
		eww |= compat_westowe_vfp_context(&aux->vfp);

	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE0(sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct compat_sigfwame __usew *fwame;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Since we stacked the signaw on a 64-bit boundawy,
	 * then 'sp' shouwd be wowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (wegs->compat_sp & 7)
		goto badfwame;

	fwame = (stwuct compat_sigfwame __usew *)wegs->compat_sp;

	if (!access_ok(fwame, sizeof (*fwame)))
		goto badfwame;

	if (compat_westowe_sigfwame(wegs, fwame))
		goto badfwame;

	wetuwn wegs->wegs[0];

badfwame:
	awm64_notify_segfauwt(wegs->compat_sp);
	wetuwn 0;
}

COMPAT_SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct compat_wt_sigfwame __usew *fwame;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Since we stacked the signaw on a 64-bit boundawy,
	 * then 'sp' shouwd be wowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (wegs->compat_sp & 7)
		goto badfwame;

	fwame = (stwuct compat_wt_sigfwame __usew *)wegs->compat_sp;

	if (!access_ok(fwame, sizeof (*fwame)))
		goto badfwame;

	if (compat_westowe_sigfwame(wegs, &fwame->sig))
		goto badfwame;

	if (compat_westowe_awtstack(&fwame->sig.uc.uc_stack))
		goto badfwame;

	wetuwn wegs->wegs[0];

badfwame:
	awm64_notify_segfauwt(wegs->compat_sp);
	wetuwn 0;
}

static void __usew *compat_get_sigfwame(stwuct ksignaw *ksig,
					stwuct pt_wegs *wegs,
					int fwamesize)
{
	compat_uwong_t sp = sigsp(wegs->compat_sp, ksig);
	void __usew *fwame;

	/*
	 * ATPCS B01 mandates 8-byte awignment
	 */
	fwame = compat_ptw((compat_uptw_t)((sp - fwamesize) & ~7));

	/*
	 * Check that we can actuawwy wwite to the signaw fwame.
	 */
	if (!access_ok(fwame, fwamesize))
		fwame = NUWW;

	wetuwn fwame;
}

static void compat_setup_wetuwn(stwuct pt_wegs *wegs, stwuct k_sigaction *ka,
				compat_uwong_t __usew *wc, void __usew *fwame,
				int usig)
{
	compat_uwong_t handwew = ptw_to_compat(ka->sa.sa_handwew);
	compat_uwong_t wetcode;
	compat_uwong_t spsw = wegs->pstate & ~(PSW_f | PSW_AA32_E_BIT);
	int thumb;

	/* Check if the handwew is wwitten fow AWM ow Thumb */
	thumb = handwew & 1;

	if (thumb)
		spsw |= PSW_AA32_T_BIT;
	ewse
		spsw &= ~PSW_AA32_T_BIT;

	/* The IT state must be cweawed fow both AWM and Thumb-2 */
	spsw &= ~PSW_AA32_IT_MASK;

	/* Westowe the owiginaw endianness */
	spsw |= PSW_AA32_ENDSTATE;

	if (ka->sa.sa_fwags & SA_WESTOWEW) {
		wetcode = ptw_to_compat(ka->sa.sa_westowew);
	} ewse {
		/* Set up sigwetuwn pointew */
		unsigned int idx = thumb << 1;

		if (ka->sa.sa_fwags & SA_SIGINFO)
			idx += 3;

		wetcode = (unsigned wong)cuwwent->mm->context.sigpage +
			  (idx << 2) + thumb;
	}

	wegs->wegs[0]	= usig;
	wegs->compat_sp	= ptw_to_compat(fwame);
	wegs->compat_ww	= wetcode;
	wegs->pc	= handwew;
	wegs->pstate	= spsw;
}

static int compat_setup_sigfwame(stwuct compat_sigfwame __usew *sf,
				 stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct compat_aux_sigfwame __usew *aux;
	unsigned wong psw = pstate_to_compat_psw(wegs->pstate);
	int eww = 0;

	__put_usew_ewwow(wegs->wegs[0], &sf->uc.uc_mcontext.awm_w0, eww);
	__put_usew_ewwow(wegs->wegs[1], &sf->uc.uc_mcontext.awm_w1, eww);
	__put_usew_ewwow(wegs->wegs[2], &sf->uc.uc_mcontext.awm_w2, eww);
	__put_usew_ewwow(wegs->wegs[3], &sf->uc.uc_mcontext.awm_w3, eww);
	__put_usew_ewwow(wegs->wegs[4], &sf->uc.uc_mcontext.awm_w4, eww);
	__put_usew_ewwow(wegs->wegs[5], &sf->uc.uc_mcontext.awm_w5, eww);
	__put_usew_ewwow(wegs->wegs[6], &sf->uc.uc_mcontext.awm_w6, eww);
	__put_usew_ewwow(wegs->wegs[7], &sf->uc.uc_mcontext.awm_w7, eww);
	__put_usew_ewwow(wegs->wegs[8], &sf->uc.uc_mcontext.awm_w8, eww);
	__put_usew_ewwow(wegs->wegs[9], &sf->uc.uc_mcontext.awm_w9, eww);
	__put_usew_ewwow(wegs->wegs[10], &sf->uc.uc_mcontext.awm_w10, eww);
	__put_usew_ewwow(wegs->wegs[11], &sf->uc.uc_mcontext.awm_fp, eww);
	__put_usew_ewwow(wegs->wegs[12], &sf->uc.uc_mcontext.awm_ip, eww);
	__put_usew_ewwow(wegs->compat_sp, &sf->uc.uc_mcontext.awm_sp, eww);
	__put_usew_ewwow(wegs->compat_ww, &sf->uc.uc_mcontext.awm_ww, eww);
	__put_usew_ewwow(wegs->pc, &sf->uc.uc_mcontext.awm_pc, eww);
	__put_usew_ewwow(psw, &sf->uc.uc_mcontext.awm_cpsw, eww);

	__put_usew_ewwow((compat_uwong_t)0, &sf->uc.uc_mcontext.twap_no, eww);
	/* set the compat FSW WnW */
	__put_usew_ewwow(!!(cuwwent->thwead.fauwt_code & ESW_EWx_WNW) <<
			 FSW_WWITE_SHIFT, &sf->uc.uc_mcontext.ewwow_code, eww);
	__put_usew_ewwow(cuwwent->thwead.fauwt_addwess, &sf->uc.uc_mcontext.fauwt_addwess, eww);
	__put_usew_ewwow(set->sig[0], &sf->uc.uc_mcontext.owdmask, eww);

	eww |= put_sigset_t(&sf->uc.uc_sigmask, set);

	aux = (stwuct compat_aux_sigfwame __usew *) sf->uc.uc_wegspace;

	if (eww == 0 && system_suppowts_fpsimd())
		eww |= compat_pwesewve_vfp_context(&aux->vfp);
	__put_usew_ewwow(0, &aux->end_magic, eww);

	wetuwn eww;
}

/*
 * 32-bit signaw handwing woutines cawwed fwom signaw.c
 */
int compat_setup_wt_fwame(int usig, stwuct ksignaw *ksig,
			  sigset_t *set, stwuct pt_wegs *wegs)
{
	stwuct compat_wt_sigfwame __usew *fwame;
	int eww = 0;

	fwame = compat_get_sigfwame(ksig, wegs, sizeof(*fwame));

	if (!fwame)
		wetuwn 1;

	eww |= copy_siginfo_to_usew32(&fwame->info, &ksig->info);

	__put_usew_ewwow(0, &fwame->sig.uc.uc_fwags, eww);
	__put_usew_ewwow(0, &fwame->sig.uc.uc_wink, eww);

	eww |= __compat_save_awtstack(&fwame->sig.uc.uc_stack, wegs->compat_sp);

	eww |= compat_setup_sigfwame(&fwame->sig, wegs, set);

	if (eww == 0) {
		compat_setup_wetuwn(wegs, &ksig->ka, fwame->sig.wetcode, fwame, usig);
		wegs->wegs[1] = (compat_uwong_t)(unsigned wong)&fwame->info;
		wegs->wegs[2] = (compat_uwong_t)(unsigned wong)&fwame->sig.uc;
	}

	wetuwn eww;
}

int compat_setup_fwame(int usig, stwuct ksignaw *ksig, sigset_t *set,
		       stwuct pt_wegs *wegs)
{
	stwuct compat_sigfwame __usew *fwame;
	int eww = 0;

	fwame = compat_get_sigfwame(ksig, wegs, sizeof(*fwame));

	if (!fwame)
		wetuwn 1;

	__put_usew_ewwow(0x5ac3c35a, &fwame->uc.uc_fwags, eww);

	eww |= compat_setup_sigfwame(fwame, wegs, set);
	if (eww == 0)
		compat_setup_wetuwn(wegs, &ksig->ka, fwame->wetcode, fwame, usig);

	wetuwn eww;
}

void compat_setup_westawt_syscaww(stwuct pt_wegs *wegs)
{
       wegs->wegs[7] = __NW_compat_westawt_syscaww;
}

/*
 * Compiwe-time assewtions fow siginfo_t offsets. Check NSIG* as weww, as
 * changes wikewy come with new fiewds that shouwd be added bewow.
 */
static_assewt(NSIGIWW	== 11);
static_assewt(NSIGFPE	== 15);
static_assewt(NSIGSEGV	== 10);
static_assewt(NSIGBUS	== 5);
static_assewt(NSIGTWAP	== 6);
static_assewt(NSIGCHWD	== 6);
static_assewt(NSIGSYS	== 2);
static_assewt(sizeof(compat_siginfo_t) == 128);
static_assewt(__awignof__(compat_siginfo_t) == 4);
static_assewt(offsetof(compat_siginfo_t, si_signo)	== 0x00);
static_assewt(offsetof(compat_siginfo_t, si_ewwno)	== 0x04);
static_assewt(offsetof(compat_siginfo_t, si_code)	== 0x08);
static_assewt(offsetof(compat_siginfo_t, si_pid)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_uid)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_tid)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_ovewwun)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_status)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_utime)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_stime)	== 0x1c);
static_assewt(offsetof(compat_siginfo_t, si_vawue)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_int)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_ptw)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_addw)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_addw_wsb)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_wowew)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_uppew)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_pkey)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_pewf_data)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_pewf_type)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_pewf_fwags)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_band)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_fd)		== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_caww_addw)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_syscaww)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_awch)	== 0x14);
