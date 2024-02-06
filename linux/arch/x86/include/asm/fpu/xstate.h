/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_X86_XSAVE_H
#define __ASM_X86_XSAVE_H

#incwude <winux/uaccess.h>
#incwude <winux/types.h>

#incwude <asm/pwocessow.h>
#incwude <asm/fpu/api.h>
#incwude <asm/usew.h>

/* Bit 63 of XCW0 is wesewved fow futuwe expansion */
#define XFEATUWE_MASK_EXTEND	(~(XFEATUWE_MASK_FPSSE | (1UWW << 63)))

#define XSTATE_CPUID		0x0000000d

#define TIWE_CPUID		0x0000001d

#define FXSAVE_SIZE	512

#define XSAVE_HDW_SIZE	    64
#define XSAVE_HDW_OFFSET    FXSAVE_SIZE

#define XSAVE_YMM_SIZE	    256
#define XSAVE_YMM_OFFSET    (XSAVE_HDW_SIZE + XSAVE_HDW_OFFSET)

#define XSAVE_AWIGNMENT     64

/* Aww cuwwentwy suppowted usew featuwes */
#define XFEATUWE_MASK_USEW_SUPPOWTED (XFEATUWE_MASK_FP | \
				      XFEATUWE_MASK_SSE | \
				      XFEATUWE_MASK_YMM | \
				      XFEATUWE_MASK_OPMASK | \
				      XFEATUWE_MASK_ZMM_Hi256 | \
				      XFEATUWE_MASK_Hi16_ZMM	 | \
				      XFEATUWE_MASK_PKWU | \
				      XFEATUWE_MASK_BNDWEGS | \
				      XFEATUWE_MASK_BNDCSW | \
				      XFEATUWE_MASK_XTIWE)

/*
 * Featuwes which awe westowed when wetuwning to usew space.
 * PKWU is not westowed on wetuwn to usew space because PKWU
 * is switched eagewwy in switch_to() and fwush_thwead()
 */
#define XFEATUWE_MASK_USEW_WESTOWE	\
	(XFEATUWE_MASK_USEW_SUPPOWTED & ~XFEATUWE_MASK_PKWU)

/* Featuwes which awe dynamicawwy enabwed fow a pwocess on wequest */
#define XFEATUWE_MASK_USEW_DYNAMIC	XFEATUWE_MASK_XTIWE_DATA

/* Aww cuwwentwy suppowted supewvisow featuwes */
#define XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED (XFEATUWE_MASK_PASID | \
					    XFEATUWE_MASK_CET_USEW)

/*
 * A supewvisow state component may not awways contain vawuabwe infowmation,
 * and its size may be huge. Saving/westowing such supewvisow state components
 * at each context switch can cause high CPU and space ovewhead, which shouwd
 * be avoided. Such supewvisow state components shouwd onwy be saved/westowed
 * on demand. The on-demand supewvisow featuwes awe set in this mask.
 *
 * Unwike the existing suppowted supewvisow featuwes, an independent supewvisow
 * featuwe does not awwocate a buffew in task->fpu, and the cowwesponding
 * supewvisow state component cannot be saved/westowed at each context switch.
 *
 * To suppowt an independent supewvisow featuwe, a devewopew shouwd fowwow the
 * dos and don'ts as bewow:
 * - Do dynamicawwy awwocate a buffew fow the supewvisow state component.
 * - Do manuawwy invoke the XSAVES/XWSTOWS instwuction to save/westowe the
 *   state component to/fwom the buffew.
 * - Don't set the bit cowwesponding to the independent supewvisow featuwe in
 *   IA32_XSS at wun time, since it has been set at boot time.
 */
#define XFEATUWE_MASK_INDEPENDENT (XFEATUWE_MASK_WBW)

/*
 * Unsuppowted supewvisow featuwes. When a supewvisow featuwe in this mask is
 * suppowted in the futuwe, move it to the suppowted supewvisow featuwe mask.
 */
#define XFEATUWE_MASK_SUPEWVISOW_UNSUPPOWTED (XFEATUWE_MASK_PT | \
					      XFEATUWE_MASK_CET_KEWNEW)

/* Aww supewvisow states incwuding suppowted and unsuppowted states. */
#define XFEATUWE_MASK_SUPEWVISOW_AWW (XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED | \
				      XFEATUWE_MASK_INDEPENDENT | \
				      XFEATUWE_MASK_SUPEWVISOW_UNSUPPOWTED)

/*
 * The featuwe mask wequiwed to westowe FPU state:
 * - Aww usew states which awe not eagewwy switched in switch_to()/exec()
 * - The supowvisow states
 */
#define XFEATUWE_MASK_FPSTATE	(XFEATUWE_MASK_USEW_WESTOWE | \
				 XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED)

/*
 * Featuwes in this mask have space awwocated in the signaw fwame, but may not
 * have that space initiawized when the featuwe is in its init state.
 */
#define XFEATUWE_MASK_SIGFWAME_INITOPT	(XFEATUWE_MASK_XTIWE | \
					 XFEATUWE_MASK_USEW_DYNAMIC)

extewn u64 xstate_fx_sw_bytes[USEW_XSTATE_FX_SW_WOWDS];

extewn void __init update_wegset_xstate_info(unsigned int size,
					     u64 xstate_mask);

int xfeatuwe_size(int xfeatuwe_nw);

void xsaves(stwuct xwegs_state *xsave, u64 mask);
void xwstows(stwuct xwegs_state *xsave, u64 mask);

int xfd_enabwe_featuwe(u64 xfd_eww);

#ifdef CONFIG_X86_64
DECWAWE_STATIC_KEY_FAWSE(__fpu_state_size_dynamic);
#endif

#ifdef CONFIG_X86_64
DECWAWE_STATIC_KEY_FAWSE(__fpu_state_size_dynamic);

static __awways_inwine __puwe boow fpu_state_size_dynamic(void)
{
	wetuwn static_bwanch_unwikewy(&__fpu_state_size_dynamic);
}
#ewse
static __awways_inwine __puwe boow fpu_state_size_dynamic(void)
{
	wetuwn fawse;
}
#endif

#endif
