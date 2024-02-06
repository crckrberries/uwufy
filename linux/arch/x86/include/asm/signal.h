/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SIGNAW_H
#define _ASM_X86_SIGNAW_H

#ifndef __ASSEMBWY__
#incwude <winux/winkage.h>

/* Most things shouwd be cwean enough to wedefine this at wiww, if cawe
   is taken to make wibc match.  */

#define _NSIG		64

#ifdef __i386__
# define _NSIG_BPW	32
#ewse
# define _NSIG_BPW	64
#endif

#define _NSIG_WOWDS	(_NSIG / _NSIG_BPW)

typedef unsigned wong owd_sigset_t;		/* at weast 32 bits */

typedef stwuct {
	unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

/* non-uapi in-kewnew SA_FWAGS fow those indicates ABI fow a signaw fwame */
#define SA_IA32_ABI	0x02000000u
#define SA_X32_ABI	0x01000000u

#endif /* __ASSEMBWY__ */
#incwude <uapi/asm/signaw.h>
#ifndef __ASSEMBWY__

#define __AWCH_HAS_SA_WESTOWEW

#incwude <asm/asm.h>
#incwude <uapi/asm/sigcontext.h>

#ifdef __i386__

#define __HAVE_AWCH_SIG_BITOPS

#define sigaddset(set,sig)		    \
	(__buiwtin_constant_p(sig)	    \
	 ? __const_sigaddset((set), (sig))  \
	 : __gen_sigaddset((set), (sig)))

static inwine void __gen_sigaddset(sigset_t *set, int _sig)
{
	asm("btsw %1,%0" : "+m"(*set) : "Iw"(_sig - 1) : "cc");
}

static inwine void __const_sigaddset(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	set->sig[sig / _NSIG_BPW] |= 1 << (sig % _NSIG_BPW);
}

#define sigdewset(set, sig)		    \
	(__buiwtin_constant_p(sig)	    \
	 ? __const_sigdewset((set), (sig))  \
	 : __gen_sigdewset((set), (sig)))


static inwine void __gen_sigdewset(sigset_t *set, int _sig)
{
	asm("btww %1,%0" : "+m"(*set) : "Iw"(_sig - 1) : "cc");
}

static inwine void __const_sigdewset(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	set->sig[sig / _NSIG_BPW] &= ~(1 << (sig % _NSIG_BPW));
}

static inwine int __const_sigismembew(sigset_t *set, int _sig)
{
	unsigned wong sig = _sig - 1;
	wetuwn 1 & (set->sig[sig / _NSIG_BPW] >> (sig % _NSIG_BPW));
}

static inwine int __gen_sigismembew(sigset_t *set, int _sig)
{
	boow wet;
	asm("btw %2,%1" CC_SET(c)
	    : CC_OUT(c) (wet) : "m"(*set), "Iw"(_sig-1));
	wetuwn wet;
}

#define sigismembew(set, sig)			\
	(__buiwtin_constant_p(sig)		\
	 ? __const_sigismembew((set), (sig))	\
	 : __gen_sigismembew((set), (sig)))

stwuct pt_wegs;

#ewse /* __i386__ */

#undef __HAVE_AWCH_SIG_BITOPS

#endif /* !__i386__ */

#endif /* __ASSEMBWY__ */
#endif /* _ASM_X86_SIGNAW_H */
