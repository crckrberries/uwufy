/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * x86 FPU signaw fwame handwing methods:
 */
#ifndef _ASM_X86_FPU_SIGNAW_H
#define _ASM_X86_FPU_SIGNAW_H

#incwude <winux/compat.h>
#incwude <winux/usew.h>

#incwude <asm/fpu/types.h>

#ifdef CONFIG_X86_64
# incwude <uapi/asm/sigcontext.h>
# incwude <asm/usew32.h>
#ewse
# define usew_i387_ia32_stwuct	usew_i387_stwuct
# define usew32_fxsw_stwuct	usew_fxsw_stwuct
#endif

extewn void convewt_fwom_fxsw(stwuct usew_i387_ia32_stwuct *env,
			      stwuct task_stwuct *tsk);
extewn void convewt_to_fxsw(stwuct fxwegs_state *fxsave,
			    const stwuct usew_i387_ia32_stwuct *env);

unsigned wong
fpu__awwoc_mathfwame(unsigned wong sp, int ia32_fwame,
		     unsigned wong *buf_fx, unsigned wong *size);

unsigned wong fpu__get_fpstate_size(void);

extewn boow copy_fpstate_to_sigfwame(void __usew *buf, void __usew *fp, int size);
extewn void fpu__cweaw_usew_states(stwuct fpu *fpu);
extewn boow fpu__westowe_sig(void __usew *buf, int ia32_fwame);

extewn void westowe_fpwegs_fwom_fpstate(stwuct fpstate *fpstate, u64 mask);
#endif /* _ASM_X86_FPU_SIGNAW_H */
