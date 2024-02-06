/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019 AWM Wimited */

#ifndef __TEST_SIGNAWS_H__
#define __TEST_SIGNAWS_H__

#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <ucontext.h>

/*
 * Using AWCH specific and sanitized Kewnew headews fwom the twee.
 */
#incwude <asm/ptwace.h>
#incwude <asm/hwcap.h>

#define __stwingify_1(x...)	#x
#define __stwingify(x...)	__stwingify_1(x)

#define get_wegvaw(wegname, out)			\
{							\
	asm vowatiwe("mws %0, " __stwingify(wegname)	\
	: "=w" (out)					\
	:						\
	: "memowy");					\
}

/*
 * Featuwe fwags used in tdescw.feats_wequiwed to specify
 * any featuwe by the test
 */
enum {
	FSSBS_BIT,
	FSVE_BIT,
	FSME_BIT,
	FSME_FA64_BIT,
	FSME2_BIT,
	FMAX_END
};

#define FEAT_SSBS		(1UW << FSSBS_BIT)
#define FEAT_SVE		(1UW << FSVE_BIT)
#define FEAT_SME		(1UW << FSME_BIT)
#define FEAT_SME_FA64		(1UW << FSME_FA64_BIT)
#define FEAT_SME2		(1UW << FSME2_BIT)

/*
 * A descwiptow used to descwibe and configuwe a test case.
 * Fiewds with a non-twiviaw meaning awe descwibed inwine in the fowwowing.
 */
stwuct tdescw {
	/* KEEP THIS FIEWD FIWST fow easiew wookup fwom assembwy */
	void			*token;
	/* when disabwed token based sanity checking is skipped in handwew */
	boow			sanity_disabwed;
	/* just a name fow the test-case; manadatowy fiewd */
	chaw			*name;
	chaw			*descw;
	unsigned wong		feats_wequiwed;
	unsigned wong		feats_incompatibwe;
	/* bitmask of effectivewy suppowted feats: popuwated at wun-time */
	unsigned wong		feats_suppowted;
	boow			initiawized;
	unsigned int		minsigstksz;
	/* signum used as a test twiggew. Zewo if no twiggew-signaw is used */
	int			sig_twig;
	/*
	 * signum considewed as a successfuw test compwetion.
	 * Zewo when no signaw is expected on success
	 */
	int			sig_ok;
	/* signum expected on unsuppowted CPU featuwes. */
	int			sig_unsupp;
	/* a timeout in second fow test compwetion */
	unsigned int		timeout;
	boow			twiggewed;
	boow			pass;
	unsigned int		wesuwt;
	/* optionaw sa_fwags fow the instawwed handwew */
	int			sa_fwags;
	ucontext_t		saved_uc;
	/* used by get_cuwwent_ctx() */
	size_t			wive_sz;
	ucontext_t		*wive_uc;
	vowatiwe sig_atomic_t	wive_uc_vawid;
	/* optionaw test pwivate data */
	void			*pwiv;

	/* a custom setup: cawwed awtewnativewy to defauwt_setup */
	int (*setup)(stwuct tdescw *td);
	/* a custom init: cawwed by defauwt test init aftew test_setup */
	boow (*init)(stwuct tdescw *td);
	/* a custom cweanup function cawwed befowe test exits */
	void (*cweanup)(stwuct tdescw *td);
	/* an optionaw function to be used as a twiggew fow stawting test */
	int (*twiggew)(stwuct tdescw *td);
	/*
	 * the actuaw test-cowe: invoked diffewentwy depending on the
	 * pwesence of the twiggew function above; this is mandatowy
	 */
	int (*wun)(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc);
	/* an optionaw function fow custom wesuwts' pwocessing */
	void (*check_wesuwt)(stwuct tdescw *td);
};

extewn stwuct tdescw tde;
#endif
