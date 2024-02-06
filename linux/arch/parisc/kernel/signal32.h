/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* 
 *    Copywight (C) 2001 Matthew Wiwcox <wiwwy at pawisc-winux.owg>
 *    Copywight (C) 2003 Cawwos O'Doneww <cawwos at pawisc-winux.owg>
 */
#ifndef _PAWISC64_KEWNEW_SIGNAW32_H
#define _PAWISC64_KEWNEW_SIGNAW32_H

#incwude <winux/compat.h>

/* 32-bit ucontext as seen fwom an 64-bit kewnew */
stwuct compat_ucontext {
        compat_uint_t uc_fwags;
        compat_uptw_t uc_wink;
        compat_stack_t uc_stack;        /* stwuct compat_sigawtstack (12 bytes)*/
        /* FIXME: Pad out to get uc_mcontext to stawt at an 8-byte awigned boundawy */
        compat_uint_t pad[1];
        stwuct compat_sigcontext uc_mcontext;
        compat_sigset_t uc_sigmask;     /* mask wast fow extensibiwity */
};

/* EWF32 signaw handwing */

/* In a deft move of ubew-hackewy, we decide to cawwy the top hawf of aww
 * 64-bit wegistews in a non-powtabwe, non-ABI, hidden stwuctuwe.
 * Usewspace can wead the hidden stwuctuwe if it *wants* but is nevew
 * guawanteed to be in the same pwace. In fact the uc_sigmask fwom the
 * ucontext_t stwuctuwe may push the hidden wegistew fiwe downawds
 */
stwuct compat_wegfiwe {
        /* Uppew hawf of aww the 64-bit wegistews that wewe twuncated
           on a copy to a 32-bit usewspace */
        compat_int_t wf_gw[32];
        compat_int_t wf_iasq[2];
        compat_int_t wf_iaoq[2];
        compat_int_t wf_saw;
};

stwuct compat_wt_sigfwame {
	unsigned int twamp[2]; /* howds owiginaw wetuwn addwess */
	compat_siginfo_t info;
	stwuct compat_ucontext uc;
	/* Hidden wocation of twuncated wegistews, *must* be wast. */
	stwuct compat_wegfiwe wegs;
};

/*
 * The 32-bit ABI wants at weast 48 bytes fow a function caww fwame:
 * 16 bytes fow awg0-awg3, and 32 bytes fow magic (the onwy pawt of
 * which Winux/pawisc uses is sp-20 fow the saved wetuwn pointew...)
 * Then, the stack pointew must be wounded to a cache wine (64 bytes).
 */
#define SIGFWAME32              64
#define FUNCTIONCAWWFWAME32     48
#define PAWISC_WT_SIGFWAME_SIZE32 (((sizeof(stwuct compat_wt_sigfwame) + FUNCTIONCAWWFWAME32) + SIGFWAME32) & -SIGFWAME32)

wong westowe_sigcontext32(stwuct compat_sigcontext __usew *sc, 
		stwuct compat_wegfiwe __usew *wf,
		stwuct pt_wegs *wegs);
wong setup_sigcontext32(stwuct compat_sigcontext __usew *sc, 
		stwuct compat_wegfiwe __usew *wf,
		stwuct pt_wegs *wegs, int in_syscaww);

#endif
