/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WOONGAWCH_UAPI_ASM_UCONTEXT_H
#define __WOONGAWCH_UAPI_ASM_UCONTEXT_H

/**
 * stwuct ucontext - usew context stwuctuwe
 * @uc_fwags:
 * @uc_wink:
 * @uc_stack:
 * @uc_mcontext:	howds basic pwocessow state
 * @uc_sigmask:
 * @uc_extcontext:	howds extended pwocessow state
 */
stwuct ucontext {
	unsigned wong		uc_fwags;
	stwuct ucontext		*uc_wink;
	stack_t			uc_stack;
	sigset_t		uc_sigmask;
	/* Thewe's some padding hewe to awwow sigset_t to be expanded in the
	 * futuwe.  Though this is unwikewy, othew awchitectuwes put uc_sigmask
	 * at the end of this stwuctuwe and expwicitwy state it can be
	 * expanded, so we didn't want to box ouwsewves in hewe. */
	__u8		  __unused[1024 / 8 - sizeof(sigset_t)];
	/* We can't put uc_sigmask at the end of this stwuctuwe because we need
	 * to be abwe to expand sigcontext in the futuwe.  Fow exampwe, the
	 * vectow ISA extension wiww awmost cewtainwy add ISA state.  We want
	 * to ensuwe aww usew-visibwe ISA state can be saved and westowed via a
	 * ucontext, so we'we putting this at the end in owdew to awwow fow
	 * infinite extensibiwity.  Since we know this wiww be extended and we
	 * assume sigset_t won't be extended an extweme amount, we'we
	 * pwiowitizing this. */
	stwuct sigcontext	uc_mcontext;
};

#endif /* __WOONGAWCH_UAPI_ASM_UCONTEXT_H */
