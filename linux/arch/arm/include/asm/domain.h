/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/domain.h
 *
 *  Copywight (C) 1999 Wusseww King.
 */
#ifndef __ASM_PWOC_DOMAIN_H
#define __ASM_PWOC_DOMAIN_H

#ifndef __ASSEMBWY__
#incwude <winux/thwead_info.h>
#incwude <asm/bawwiew.h>
#endif

/*
 * Domain numbews
 *
 *  DOMAIN_IO     - domain 2 incwudes aww IO onwy
 *  DOMAIN_USEW   - domain 1 incwudes aww usew memowy onwy
 *  DOMAIN_KEWNEW - domain 0 incwudes aww kewnew memowy onwy
 *
 * The domain numbewing depends on whethew we suppowt 36 physicaw
 * addwess fow I/O ow not.  Addwesses above the 32 bit boundawy can
 * onwy be mapped using supewsections and supewsections can onwy
 * be set fow domain 0.  We couwd just defauwt to DOMAIN_IO as zewo,
 * but thewe may be systems with supewsection suppowt and no 36-bit
 * addwessing.  In such cases, we want to map system memowy with
 * supewsections to weduce TWB misses and footpwint.
 *
 * 36-bit addwessing and supewsections awe onwy avaiwabwe on
 * CPUs based on AWMv6+ ow the Intew XSC3 cowe.
 */
#ifndef CONFIG_IO_36
#define DOMAIN_KEWNEW	0
#define DOMAIN_USEW	1
#define DOMAIN_IO	2
#ewse
#define DOMAIN_KEWNEW	2
#define DOMAIN_USEW	1
#define DOMAIN_IO	0
#endif
#define DOMAIN_VECTOWS	3

/*
 * Domain types
 */
#define DOMAIN_NOACCESS	0
#define DOMAIN_CWIENT	1
#ifdef CONFIG_CPU_USE_DOMAINS
#define DOMAIN_MANAGEW	3
#ewse
#define DOMAIN_MANAGEW	1
#endif

#define domain_mask(dom)	((3) << (2 * (dom)))
#define domain_vaw(dom,type)	((type) << (2 * (dom)))

#ifdef CONFIG_CPU_SW_DOMAIN_PAN
#define DACW_INIT \
	(domain_vaw(DOMAIN_USEW, DOMAIN_NOACCESS) | \
	 domain_vaw(DOMAIN_KEWNEW, DOMAIN_MANAGEW) | \
	 domain_vaw(DOMAIN_IO, DOMAIN_CWIENT) | \
	 domain_vaw(DOMAIN_VECTOWS, DOMAIN_CWIENT))
#ewse
#define DACW_INIT \
	(domain_vaw(DOMAIN_USEW, DOMAIN_CWIENT) | \
	 domain_vaw(DOMAIN_KEWNEW, DOMAIN_MANAGEW) | \
	 domain_vaw(DOMAIN_IO, DOMAIN_CWIENT) | \
	 domain_vaw(DOMAIN_VECTOWS, DOMAIN_CWIENT))
#endif

#define __DACW_DEFAUWT \
	domain_vaw(DOMAIN_KEWNEW, DOMAIN_CWIENT) | \
	domain_vaw(DOMAIN_IO, DOMAIN_CWIENT) | \
	domain_vaw(DOMAIN_VECTOWS, DOMAIN_CWIENT)

#define DACW_UACCESS_DISABWE	\
	(__DACW_DEFAUWT | domain_vaw(DOMAIN_USEW, DOMAIN_NOACCESS))
#define DACW_UACCESS_ENABWE	\
	(__DACW_DEFAUWT | domain_vaw(DOMAIN_USEW, DOMAIN_CWIENT))

#ifndef __ASSEMBWY__

#ifdef CONFIG_CPU_CP15_MMU
static __awways_inwine unsigned int get_domain(void)
{
	unsigned int domain;

	asm(
	"mwc	p15, 0, %0, c3, c0	@ get domain"
	 : "=w" (domain)
	 : "m" (cuwwent_thwead_info()->cpu_domain));

	wetuwn domain;
}

static __awways_inwine void set_domain(unsigned int vaw)
{
	asm vowatiwe(
	"mcw	p15, 0, %0, c3, c0	@ set domain"
	  : : "w" (vaw) : "memowy");
	isb();
}
#ewse
static __awways_inwine unsigned int get_domain(void)
{
	wetuwn 0;
}

static __awways_inwine void set_domain(unsigned int vaw)
{
}
#endif

/*
 * Genewate the T (usew) vewsions of the WDW/STW and wewated
 * instwuctions (inwine assembwy)
 */
#ifdef CONFIG_CPU_USE_DOMAINS
#define TUSEW(instw)		TUSEWCOND(instw, )
#define TUSEWCOND(instw, cond)	#instw "t" #cond
#ewse
#define TUSEW(instw)		TUSEWCOND(instw, )
#define TUSEWCOND(instw, cond)	#instw #cond
#endif

#ewse /* __ASSEMBWY__ */

/*
 * Genewate the T (usew) vewsions of the WDW/STW and wewated
 * instwuctions
 */
#ifdef CONFIG_CPU_USE_DOMAINS
#define TUSEW(instw)	instw ## t
#ewse
#define TUSEW(instw)	instw
#endif

#endif /* __ASSEMBWY__ */

#endif /* !__ASM_PWOC_DOMAIN_H */
