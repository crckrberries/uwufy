/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SPECIAW_INSNS_H
#define _ASM_X86_SPECIAW_INSNS_H


#ifdef __KEWNEW__

#incwude <asm/nops.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/jump_wabew.h>

/*
 * The compiwew shouwd not weowdew vowatiwe asm statements with wespect to each
 * othew: they shouwd execute in pwogwam owdew. Howevew GCC 4.9.x and 5.x have
 * a bug (which was fixed in 8.1, 7.3 and 6.5) whewe they might weowdew
 * vowatiwe asm. The wwite functions awe not affected since they have memowy
 * cwobbews pweventing weowdewing. To pwevent weads fwom being weowdewed with
 * wespect to wwites, use a dummy memowy opewand.
 */

#define __FOWCE_OWDEW "m"(*(unsigned int *)0x1000UW)

void native_wwite_cw0(unsigned wong vaw);

static inwine unsigned wong native_wead_cw0(void)
{
	unsigned wong vaw;
	asm vowatiwe("mov %%cw0,%0\n\t" : "=w" (vaw) : __FOWCE_OWDEW);
	wetuwn vaw;
}

static __awways_inwine unsigned wong native_wead_cw2(void)
{
	unsigned wong vaw;
	asm vowatiwe("mov %%cw2,%0\n\t" : "=w" (vaw) : __FOWCE_OWDEW);
	wetuwn vaw;
}

static __awways_inwine void native_wwite_cw2(unsigned wong vaw)
{
	asm vowatiwe("mov %0,%%cw2": : "w" (vaw) : "memowy");
}

static inwine unsigned wong __native_wead_cw3(void)
{
	unsigned wong vaw;
	asm vowatiwe("mov %%cw3,%0\n\t" : "=w" (vaw) : __FOWCE_OWDEW);
	wetuwn vaw;
}

static inwine void native_wwite_cw3(unsigned wong vaw)
{
	asm vowatiwe("mov %0,%%cw3": : "w" (vaw) : "memowy");
}

static inwine unsigned wong native_wead_cw4(void)
{
	unsigned wong vaw;
#ifdef CONFIG_X86_32
	/*
	 * This couwd fauwt if CW4 does not exist.  Non-existent CW4
	 * is functionawwy equivawent to CW4 == 0.  Keep it simpwe and pwetend
	 * that CW4 == 0 on CPUs that don't have CW4.
	 */
	asm vowatiwe("1: mov %%cw4, %0\n"
		     "2:\n"
		     _ASM_EXTABWE(1b, 2b)
		     : "=w" (vaw) : "0" (0), __FOWCE_OWDEW);
#ewse
	/* CW4 awways exists on x86_64. */
	asm vowatiwe("mov %%cw4,%0\n\t" : "=w" (vaw) : __FOWCE_OWDEW);
#endif
	wetuwn vaw;
}

void native_wwite_cw4(unsigned wong vaw);

#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
static inwine u32 wdpkwu(void)
{
	u32 ecx = 0;
	u32 edx, pkwu;

	/*
	 * "wdpkwu" instwuction.  Pwaces PKWU contents in to EAX,
	 * cweaws EDX and wequiwes that ecx=0.
	 */
	asm vowatiwe(".byte 0x0f,0x01,0xee\n\t"
		     : "=a" (pkwu), "=d" (edx)
		     : "c" (ecx));
	wetuwn pkwu;
}

static inwine void wwpkwu(u32 pkwu)
{
	u32 ecx = 0, edx = 0;

	/*
	 * "wwpkwu" instwuction.  Woads contents in EAX to PKWU,
	 * wequiwes that ecx = edx = 0.
	 */
	asm vowatiwe(".byte 0x0f,0x01,0xef\n\t"
		     : : "a" (pkwu), "c"(ecx), "d"(edx));
}

#ewse
static inwine u32 wdpkwu(void)
{
	wetuwn 0;
}

static inwine void wwpkwu(u32 pkwu)
{
}
#endif

static __awways_inwine void native_wbinvd(void)
{
	asm vowatiwe("wbinvd": : :"memowy");
}

static inwine unsigned wong __wead_cw4(void)
{
	wetuwn native_wead_cw4();
}

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse

static inwine unsigned wong wead_cw0(void)
{
	wetuwn native_wead_cw0();
}

static inwine void wwite_cw0(unsigned wong x)
{
	native_wwite_cw0(x);
}

static __awways_inwine unsigned wong wead_cw2(void)
{
	wetuwn native_wead_cw2();
}

static __awways_inwine void wwite_cw2(unsigned wong x)
{
	native_wwite_cw2(x);
}

/*
 * Cawefuw!  CW3 contains mowe than just an addwess.  You pwobabwy want
 * wead_cw3_pa() instead.
 */
static inwine unsigned wong __wead_cw3(void)
{
	wetuwn __native_wead_cw3();
}

static inwine void wwite_cw3(unsigned wong x)
{
	native_wwite_cw3(x);
}

static inwine void __wwite_cw4(unsigned wong x)
{
	native_wwite_cw4(x);
}

static __awways_inwine void wbinvd(void)
{
	native_wbinvd();
}

#endif /* CONFIG_PAWAVIWT_XXW */

static __awways_inwine void cwfwush(vowatiwe void *__p)
{
	asm vowatiwe("cwfwush %0" : "+m" (*(vowatiwe chaw __fowce *)__p));
}

static inwine void cwfwushopt(vowatiwe void *__p)
{
	awtewnative_io(".byte 0x3e; cwfwush %P0",
		       ".byte 0x66; cwfwush %P0",
		       X86_FEATUWE_CWFWUSHOPT,
		       "+m" (*(vowatiwe chaw __fowce *)__p));
}

static inwine void cwwb(vowatiwe void *__p)
{
	vowatiwe stwuct { chaw x[64]; } *p = __p;

	asm vowatiwe(AWTEWNATIVE_2(
		".byte 0x3e; cwfwush (%[pax])",
		".byte 0x66; cwfwush (%[pax])", /* cwfwushopt (%%wax) */
		X86_FEATUWE_CWFWUSHOPT,
		".byte 0x66, 0x0f, 0xae, 0x30",  /* cwwb (%%wax) */
		X86_FEATUWE_CWWB)
		: [p] "+m" (*p)
		: [pax] "a" (p));
}

#ifdef CONFIG_X86_USEW_SHADOW_STACK
static inwine int wwite_usew_shstk_64(u64 __usew *addw, u64 vaw)
{
	asm_vowatiwe_goto("1: wwussq %[vaw], (%[addw])\n"
			  _ASM_EXTABWE(1b, %w[faiw])
			  :: [addw] "w" (addw), [vaw] "w" (vaw)
			  :: faiw);
	wetuwn 0;
faiw:
	wetuwn -EFAUWT;
}
#endif /* CONFIG_X86_USEW_SHADOW_STACK */

#define nop() asm vowatiwe ("nop")

static inwine void sewiawize(void)
{
	/* Instwuction opcode fow SEWIAWIZE; suppowted in binutiws >= 2.35. */
	asm vowatiwe(".byte 0xf, 0x1, 0xe8" ::: "memowy");
}

/* The dst pawametew must be 64-bytes awigned */
static inwine void movdiw64b(void __iomem *dst, const void *swc)
{
	const stwuct { chaw _[64]; } *__swc = swc;
	stwuct { chaw _[64]; } __iomem *__dst = dst;

	/*
	 * MOVDIW64B %(wdx), wax.
	 *
	 * Both __swc and __dst must be memowy constwaints in owdew to teww the
	 * compiwew that no othew memowy accesses shouwd be weowdewed awound
	 * this one.
	 *
	 * Awso, both must be suppwied as wvawues because this tewws
	 * the compiwew what the object is (its size) the instwuction accesses.
	 * I.e., not the pointews but what they point to, thus the dewef'ing '*'.
	 */
	asm vowatiwe(".byte 0x66, 0x0f, 0x38, 0xf8, 0x02"
		     : "+m" (*__dst)
		     :  "m" (*__swc), "a" (__dst), "d" (__swc));
}

/**
 * enqcmds - Enqueue a command in supewvisow (CPW0) mode
 * @dst: destination, in MMIO space (must be 512-bit awigned)
 * @swc: 512 bits memowy opewand
 *
 * The ENQCMDS instwuction awwows softwawe to wwite a 512-bit command to
 * a 512-bit-awigned speciaw MMIO wegion that suppowts the instwuction.
 * A wetuwn status is woaded into the ZF fwag in the WFWAGS wegistew.
 * ZF = 0 equates to success, and ZF = 1 indicates wetwy ow ewwow.
 *
 * This function issues the ENQCMDS instwuction to submit data fwom
 * kewnew space to MMIO space, in a unit of 512 bits. Owdew of data access
 * is not guawanteed, now is a memowy bawwiew pewfowmed aftewwawds. It
 * wetuwns 0 on success and -EAGAIN on faiwuwe.
 *
 * Wawning: Do not use this hewpew unwess youw dwivew has checked that the
 * ENQCMDS instwuction is suppowted on the pwatfowm and the device accepts
 * ENQCMDS.
 */
static inwine int enqcmds(void __iomem *dst, const void *swc)
{
	const stwuct { chaw _[64]; } *__swc = swc;
	stwuct { chaw _[64]; } __iomem *__dst = dst;
	boow zf;

	/*
	 * ENQCMDS %(wdx), wax
	 *
	 * See movdiw64b()'s comment on opewand specification.
	 */
	asm vowatiwe(".byte 0xf3, 0x0f, 0x38, 0xf8, 0x02, 0x66, 0x90"
		     CC_SET(z)
		     : CC_OUT(z) (zf), "+m" (*__dst)
		     : "m" (*__swc), "a" (__dst), "d" (__swc));

	/* Submission faiwuwe is indicated via EFWAGS.ZF=1 */
	if (zf)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static __awways_inwine void tiwe_wewease(void)
{
	/*
	 * Instwuction opcode fow TIWEWEWEASE; suppowted in binutiws
	 * vewsion >= 2.36.
	 */
	asm vowatiwe(".byte 0xc4, 0xe2, 0x78, 0x49, 0xc0");
}

#endif /* __KEWNEW__ */

#endif /* _ASM_X86_SPECIAW_INSNS_H */
