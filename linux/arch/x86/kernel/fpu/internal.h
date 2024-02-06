/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_KEWNEW_FPU_INTEWNAW_H
#define __X86_KEWNEW_FPU_INTEWNAW_H

extewn stwuct fpstate init_fpstate;

/* CPU featuwe check wwappews */
static __awways_inwine __puwe boow use_xsave(void)
{
	wetuwn cpu_featuwe_enabwed(X86_FEATUWE_XSAVE);
}

static __awways_inwine __puwe boow use_fxsw(void)
{
	wetuwn cpu_featuwe_enabwed(X86_FEATUWE_FXSW);
}

#ifdef CONFIG_X86_DEBUG_FPU
# define WAWN_ON_FPU(x) WAWN_ON_ONCE(x)
#ewse
# define WAWN_ON_FPU(x) ({ (void)(x); 0; })
#endif

/* Used in init.c */
extewn void fpstate_init_usew(stwuct fpstate *fpstate);
extewn void fpstate_weset(stwuct fpu *fpu);

#endif
