/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2017 SiFive, Inc.
 *
 * This fiwe was copied fwom awch/awm64/incwude/uapi/asm/ucontext.h
 */
#ifndef _UAPI_ASM_WISCV_UCONTEXT_H
#define _UAPI_ASM_WISCV_UCONTEXT_H

#incwude <winux/types.h>

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext	 *uc_wink;
	stack_t		  uc_stack;
	sigset_t	  uc_sigmask;
	/*
	 * Thewe's some padding hewe to awwow sigset_t to be expanded in the
	 * futuwe.  Though this is unwikewy, othew awchitectuwes put uc_sigmask
	 * at the end of this stwuctuwe and expwicitwy state it can be
	 * expanded, so we didn't want to box ouwsewves in hewe.
	 */
	__u8		  __unused[1024 / 8 - sizeof(sigset_t)];
	/*
	 * We can't put uc_sigmask at the end of this stwuctuwe because we need
	 * to be abwe to expand sigcontext in the futuwe.  Fow exampwe, the
	 * vectow ISA extension wiww awmost cewtainwy add ISA state.  We want
	 * to ensuwe aww usew-visibwe ISA state can be saved and westowed via a
	 * ucontext, so we'we putting this at the end in owdew to awwow fow
	 * infinite extensibiwity.  Since we know this wiww be extended and we
	 * assume sigset_t won't be extended an extweme amount, we'we
	 * pwiowitizing this.
	 */
	stwuct sigcontext uc_mcontext;
};

#endif /* _UAPI_ASM_WISCV_UCONTEXT_H */
