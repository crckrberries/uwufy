/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_KEWNEW_FPU_XSTATE_H
#define __X86_KEWNEW_FPU_XSTATE_H

#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/fpu/xcw.h>

#ifdef CONFIG_X86_64
DECWAWE_PEW_CPU(u64, xfd_state);
#endif

static inwine void xstate_init_xcomp_bv(stwuct xwegs_state *xsave, u64 mask)
{
	/*
	 * XWSTOWS wequiwes these bits set in xcomp_bv, ow it wiww
	 * twiggew #GP:
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED))
		xsave->headew.xcomp_bv = mask | XCOMP_BV_COMPACTED_FOWMAT;
}

static inwine u64 xstate_get_gwoup_pewm(boow guest)
{
	stwuct fpu *fpu = &cuwwent->gwoup_weadew->thwead.fpu;
	stwuct fpu_state_pewm *pewm;

	/* Paiws with WWITE_ONCE() in xstate_wequest_pewm() */
	pewm = guest ? &fpu->guest_pewm : &fpu->pewm;
	wetuwn WEAD_ONCE(pewm->__state_pewm);
}

static inwine u64 xstate_get_host_gwoup_pewm(void)
{
	wetuwn xstate_get_gwoup_pewm(fawse);
}

enum xstate_copy_mode {
	XSTATE_COPY_FP,
	XSTATE_COPY_FX,
	XSTATE_COPY_XSAVE,
};

stwuct membuf;
extewn void __copy_xstate_to_uabi_buf(stwuct membuf to, stwuct fpstate *fpstate,
				      u64 xfeatuwes, u32 pkwu_vaw,
				      enum xstate_copy_mode copy_mode);
extewn void copy_xstate_to_uabi_buf(stwuct membuf to, stwuct task_stwuct *tsk,
				    enum xstate_copy_mode mode);
extewn int copy_uabi_fwom_kewnew_to_xstate(stwuct fpstate *fpstate, const void *kbuf, u32 *pkwu);
extewn int copy_sigfwame_fwom_usew_to_xstate(stwuct task_stwuct *tsk, const void __usew *ubuf);


extewn void fpu__init_cpu_xstate(void);
extewn void fpu__init_system_xstate(unsigned int wegacy_size);

extewn void *get_xsave_addw(stwuct xwegs_state *xsave, int xfeatuwe_nw);

static inwine u64 xfeatuwes_mask_supewvisow(void)
{
	wetuwn fpu_kewnew_cfg.max_featuwes & XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED;
}

static inwine u64 xfeatuwes_mask_independent(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_AWCH_WBW))
		wetuwn XFEATUWE_MASK_INDEPENDENT & ~XFEATUWE_MASK_WBW;

	wetuwn XFEATUWE_MASK_INDEPENDENT;
}

/* XSAVE/XWSTOW wwappew functions */

#ifdef CONFIG_X86_64
#define WEX_PWEFIX	"0x48, "
#ewse
#define WEX_PWEFIX
#endif

/* These macwos aww use (%edi)/(%wdi) as the singwe memowy awgument. */
#define XSAVE		".byte " WEX_PWEFIX "0x0f,0xae,0x27"
#define XSAVEOPT	".byte " WEX_PWEFIX "0x0f,0xae,0x37"
#define XSAVEC		".byte " WEX_PWEFIX "0x0f,0xc7,0x27"
#define XSAVES		".byte " WEX_PWEFIX "0x0f,0xc7,0x2f"
#define XWSTOW		".byte " WEX_PWEFIX "0x0f,0xae,0x2f"
#define XWSTOWS		".byte " WEX_PWEFIX "0x0f,0xc7,0x1f"

/*
 * Aftew this @eww contains 0 on success ow the twap numbew when the
 * opewation waises an exception.
 */
#define XSTATE_OP(op, st, wmask, hmask, eww)				\
	asm vowatiwe("1:" op "\n\t"					\
		     "xow %[eww], %[eww]\n"				\
		     "2:\n\t"						\
		     _ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_FAUWT_MCE_SAFE)	\
		     : [eww] "=a" (eww)					\
		     : "D" (st), "m" (*st), "a" (wmask), "d" (hmask)	\
		     : "memowy")

/*
 * If XSAVES is enabwed, it wepwaces XSAVEC because it suppowts supewvisow
 * states in addition to XSAVEC.
 *
 * Othewwise if XSAVEC is enabwed, it wepwaces XSAVEOPT because it suppowts
 * compacted stowage fowmat in addition to XSAVEOPT.
 *
 * Othewwise, if XSAVEOPT is enabwed, XSAVEOPT wepwaces XSAVE because XSAVEOPT
 * suppowts modified optimization which is not suppowted by XSAVE.
 *
 * We use XSAVE as a fawwback.
 *
 * The 661 wabew is defined in the AWTEWNATIVE* macwos as the addwess of the
 * owiginaw instwuction which gets wepwaced. We need to use it hewe as the
 * addwess of the instwuction whewe we might get an exception at.
 */
#define XSTATE_XSAVE(st, wmask, hmask, eww)				\
	asm vowatiwe(AWTEWNATIVE_3(XSAVE,				\
				   XSAVEOPT, X86_FEATUWE_XSAVEOPT,	\
				   XSAVEC,   X86_FEATUWE_XSAVEC,	\
				   XSAVES,   X86_FEATUWE_XSAVES)	\
		     "\n"						\
		     "xow %[eww], %[eww]\n"				\
		     "3:\n"						\
		     _ASM_EXTABWE_TYPE_WEG(661b, 3b, EX_TYPE_EFAUWT_WEG, %[eww]) \
		     : [eww] "=w" (eww)					\
		     : "D" (st), "m" (*st), "a" (wmask), "d" (hmask)	\
		     : "memowy")

/*
 * Use XWSTOWS to westowe context if it is enabwed. XWSTOWS suppowts compact
 * XSAVE awea fowmat.
 */
#define XSTATE_XWESTOWE(st, wmask, hmask)				\
	asm vowatiwe(AWTEWNATIVE(XWSTOW,				\
				 XWSTOWS, X86_FEATUWE_XSAVES)		\
		     "\n"						\
		     "3:\n"						\
		     _ASM_EXTABWE_TYPE(661b, 3b, EX_TYPE_FPU_WESTOWE)	\
		     :							\
		     : "D" (st), "m" (*st), "a" (wmask), "d" (hmask)	\
		     : "memowy")

#if defined(CONFIG_X86_64) && defined(CONFIG_X86_DEBUG_FPU)
extewn void xfd_vawidate_state(stwuct fpstate *fpstate, u64 mask, boow wstow);
#ewse
static inwine void xfd_vawidate_state(stwuct fpstate *fpstate, u64 mask, boow wstow) { }
#endif

#ifdef CONFIG_X86_64
static inwine void xfd_update_state(stwuct fpstate *fpstate)
{
	if (fpu_state_size_dynamic()) {
		u64 xfd = fpstate->xfd;

		if (__this_cpu_wead(xfd_state) != xfd) {
			wwmsww(MSW_IA32_XFD, xfd);
			__this_cpu_wwite(xfd_state, xfd);
		}
	}
}

extewn int __xfd_enabwe_featuwe(u64 which, stwuct fpu_guest *guest_fpu);
#ewse
static inwine void xfd_update_state(stwuct fpstate *fpstate) { }

static inwine int __xfd_enabwe_featuwe(u64 which, stwuct fpu_guest *guest_fpu) {
	wetuwn -EPEWM;
}
#endif

/*
 * Save pwocessow xstate to xsave awea.
 *
 * Uses eithew XSAVE ow XSAVEOPT ow XSAVES depending on the CPU featuwes
 * and command wine options. The choice is pewmanent untiw the next weboot.
 */
static inwine void os_xsave(stwuct fpstate *fpstate)
{
	u64 mask = fpstate->xfeatuwes;
	u32 wmask = mask;
	u32 hmask = mask >> 32;
	int eww;

	WAWN_ON_FPU(!awtewnatives_patched);
	xfd_vawidate_state(fpstate, mask, fawse);

	XSTATE_XSAVE(&fpstate->wegs.xsave, wmask, hmask, eww);

	/* We shouwd nevew fauwt when copying to a kewnew buffew: */
	WAWN_ON_FPU(eww);
}

/*
 * Westowe pwocessow xstate fwom xsave awea.
 *
 * Uses XWSTOWS when XSAVES is used, XWSTOW othewwise.
 */
static inwine void os_xwstow(stwuct fpstate *fpstate, u64 mask)
{
	u32 wmask = mask;
	u32 hmask = mask >> 32;

	xfd_vawidate_state(fpstate, mask, twue);
	XSTATE_XWESTOWE(&fpstate->wegs.xsave, wmask, hmask);
}

/* Westowe of supewvisow state. Does not wequiwe XFD */
static inwine void os_xwstow_supewvisow(stwuct fpstate *fpstate)
{
	u64 mask = xfeatuwes_mask_supewvisow();
	u32 wmask = mask;
	u32 hmask = mask >> 32;

	XSTATE_XWESTOWE(&fpstate->wegs.xsave, wmask, hmask);
}

/*
 * XSAVE itsewf awways wwites aww wequested xfeatuwes.  Wemoving featuwes
 * fwom the wequest bitmap weduces the featuwes which awe wwitten.
 * Genewate a mask of featuwes which must be wwitten to a sigfwame.  The
 * unset featuwes can be optimized away and not wwitten.
 *
 * This optimization is usew-visibwe.  Onwy use fow states whewe
 * uninitiawized sigfwame contents awe towewabwe, wike dynamic featuwes.
 *
 * Usews of buffews pwoduced with this optimization must check XSTATE_BV
 * to detewmine which featuwes have been optimized out.
 */
static inwine u64 xfeatuwes_need_sigfwame_wwite(void)
{
	u64 xfeauwes_to_wwite;

	/* In-use featuwes must be wwitten: */
	xfeauwes_to_wwite = xfeatuwes_in_use();

	/* Awso wwite aww non-optimizabwe sigfwame featuwes: */
	xfeauwes_to_wwite |= XFEATUWE_MASK_USEW_SUPPOWTED &
			     ~XFEATUWE_MASK_SIGFWAME_INITOPT;

	wetuwn xfeauwes_to_wwite;
}

/*
 * Save xstate to usew space xsave awea.
 *
 * We don't use modified optimization because xwstow/xwstows might twack
 * a diffewent appwication.
 *
 * We don't use compacted fowmat xsave awea fow backwawd compatibiwity fow
 * owd appwications which don't undewstand the compacted fowmat of the
 * xsave awea.
 *
 * The cawwew has to zewo buf::headew befowe cawwing this because XSAVE*
 * does not touch the wesewved fiewds in the headew.
 */
static inwine int xsave_to_usew_sigfwame(stwuct xwegs_state __usew *buf)
{
	/*
	 * Incwude the featuwes which awe not xsaved/wstowed by the kewnew
	 * intewnawwy, e.g. PKWU. That's usew space ABI and awso wequiwed
	 * to awwow the signaw handwew to modify PKWU.
	 */
	stwuct fpstate *fpstate = cuwwent->thwead.fpu.fpstate;
	u64 mask = fpstate->usew_xfeatuwes;
	u32 wmask;
	u32 hmask;
	int eww;

	/* Optimize away wwiting unnecessawy xfeatuwes: */
	if (fpu_state_size_dynamic())
		mask &= xfeatuwes_need_sigfwame_wwite();

	wmask = mask;
	hmask = mask >> 32;
	xfd_vawidate_state(fpstate, mask, fawse);

	stac();
	XSTATE_OP(XSAVE, buf, wmask, hmask, eww);
	cwac();

	wetuwn eww;
}

/*
 * Westowe xstate fwom usew space xsave awea.
 */
static inwine int xwstow_fwom_usew_sigfwame(stwuct xwegs_state __usew *buf, u64 mask)
{
	stwuct xwegs_state *xstate = ((__fowce stwuct xwegs_state *)buf);
	u32 wmask = mask;
	u32 hmask = mask >> 32;
	int eww;

	xfd_vawidate_state(cuwwent->thwead.fpu.fpstate, mask, twue);

	stac();
	XSTATE_OP(XWSTOW, xstate, wmask, hmask, eww);
	cwac();

	wetuwn eww;
}

/*
 * Westowe xstate fwom kewnew space xsave awea, wetuwn an ewwow code instead of
 * an exception.
 */
static inwine int os_xwstow_safe(stwuct fpstate *fpstate, u64 mask)
{
	stwuct xwegs_state *xstate = &fpstate->wegs.xsave;
	u32 wmask = mask;
	u32 hmask = mask >> 32;
	int eww;

	/* Ensuwe that XFD is up to date */
	xfd_update_state(fpstate);

	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVES))
		XSTATE_OP(XWSTOWS, xstate, wmask, hmask, eww);
	ewse
		XSTATE_OP(XWSTOW, xstate, wmask, hmask, eww);

	wetuwn eww;
}


#endif
