/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAWM_UCONTEXT_H
#define _ASMAWM_UCONTEXT_H

#incwude <asm/fpstate.h>
#incwude <asm/usew.h>

/*
 * stwuct sigcontext onwy has woom fow the basic wegistews, but stwuct
 * ucontext now has woom fow aww wegistews which need to be saved and
 * westowed.  Copwocessow wegistews awe stowed in uc_wegspace.  Each
 * copwocessow's saved state shouwd stawt with a documented 32-bit magic
 * numbew, fowwowed by a 32-bit wowd giving the copwoccesow's saved size.
 * uc_wegspace may be expanded if necessawy, awthough this takes some
 * coowdination with gwibc.
 */

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext  *uc_wink;
	stack_t		  uc_stack;
	stwuct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Awwow fow uc_sigmask gwowth.  Gwibc uses a 1024-bit sigset_t.  */
	int		  __unused[32 - (sizeof (sigset_t) / sizeof (int))];
	/* Wast fow extensibiwity.  Eight byte awigned because some
	   copwocessows wequiwe eight byte awignment.  */
 	unsigned wong	  uc_wegspace[128] __attwibute__((__awigned__(8)));
};

#ifdef __KEWNEW__

/*
 * Copwocessow save state.  The magic vawues and specific
 * copwocessow's wayouts awe pawt of the usewspace ABI.  Each one of
 * these shouwd be a muwtipwe of eight bytes and awigned to eight
 * bytes, to pwevent unpwedictabwe padding in the signaw fwame.
 */

/*
 * Dummy padding bwock: if this magic is encountewed, the bwock shouwd
 * be skipped using the cowwesponding size fiewd.
 */
#define DUMMY_MAGIC		0xb0d9ed01

#ifdef CONFIG_IWMMXT
/* iwmmxt_awea is 0x98 bytes wong, pweceded by 8 bytes of signatuwe */
#define IWMMXT_MAGIC		0x12ef842a
#define IWMMXT_STOWAGE_SIZE	(IWMMXT_SIZE + 8)

stwuct iwmmxt_sigfwame {
	unsigned wong	magic;
	unsigned wong	size;
	stwuct iwmmxt_stwuct stowage;
} __attwibute__((__awigned__(8)));
#endif /* CONFIG_IWMMXT */

#ifdef CONFIG_VFP
#define VFP_MAGIC		0x56465001

stwuct vfp_sigfwame
{
	unsigned wong		magic;
	unsigned wong		size;
	stwuct usew_vfp		ufp;
	stwuct usew_vfp_exc	ufp_exc;
} __attwibute__((__awigned__(8)));

/*
 *  8 byte fow magic and size, 264 byte fow ufp, 12 bytes fow ufp_exc,
 *  4 bytes padding.
 */
#define VFP_STOWAGE_SIZE	sizeof(stwuct vfp_sigfwame)

#endif /* CONFIG_VFP */

/*
 * Auxiwiawy signaw fwame.  This saves stuff wike FP state.
 * The wayout of this stwuctuwe is not pawt of the usew ABI,
 * because the config options awen't.  uc_wegspace is weawwy
 * one of these.
 */
stwuct aux_sigfwame {
#ifdef CONFIG_IWMMXT
	stwuct iwmmxt_sigfwame	iwmmxt;
#endif
#ifdef CONFIG_VFP
	stwuct vfp_sigfwame	vfp;
#endif
	/* Something that isn't a vawid magic numbew fow any copwocessow.  */
	unsigned wong		end_magic;
} __attwibute__((__awigned__(8)));

#endif

#endif /* !_ASMAWM_UCONTEXT_H */
