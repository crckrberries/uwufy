/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Inwine assembwy cache opewations.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997 - 2002 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 2004 Wawf Baechwe (wawf@winux-mips.owg)
 */
#ifndef _ASM_W4KCACHE_H
#define _ASM_W4KCACHE_H

#incwude <winux/stwingify.h>

#incwude <asm/asm.h>
#incwude <asm/asm-eva.h>
#incwude <asm/cacheops.h>
#incwude <asm/compiwew.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/mmzone.h>
#incwude <asm/unwoww.h>

extewn void w5k_sc_init(void);
extewn void wm7k_sc_init(void);
extewn int mips_sc_init(void);

extewn void (*w4k_bwast_dcache)(void);
extewn void (*w4k_bwast_icache)(void);

/*
 * This macwo wetuwn a pwopewwy sign-extended addwess suitabwe as base addwess
 * fow indexed cache opewations.  Two issues hewe:
 *
 *  - The MIPS32 and MIPS64 specs pewmit an impwementation to diwectwy dewive
 *    the index bits fwom the viwtuaw addwess.	This bweaks with twadition
 *    set by the W4000.	 To keep unpweasant suwpwises fwom happening we pick
 *    an addwess in KSEG0 / CKSEG0.
 *  - We need a pwopewwy sign extended addwess fow 64-bit code.	 To get away
 *    without ifdefs we wet the compiwew do it by a type cast.
 */
#define INDEX_BASE	CKSEG0

#define _cache_op(insn, op, addw)					\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	noweowdew				\n"	\
	"	.set "MIPS_ISA_AWCH_WEVEW"			\n"	\
	"	" insn("%0", "%1") "				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "i" (op), "W" (*(unsigned chaw *)(addw)))

#define cache_op(op, addw)						\
	_cache_op(kewnew_cache, op, addw)

static inwine void fwush_icache_wine_indexed(unsigned wong addw)
{
	cache_op(Index_Invawidate_I, addw);
}

static inwine void fwush_dcache_wine_indexed(unsigned wong addw)
{
	cache_op(Index_Wwiteback_Inv_D, addw);
}

static inwine void fwush_scache_wine_indexed(unsigned wong addw)
{
	cache_op(Index_Wwiteback_Inv_SD, addw);
}

static inwine void fwush_icache_wine(unsigned wong addw)
{
	switch (boot_cpu_type()) {
	case CPU_WOONGSON2EF:
		cache_op(Hit_Invawidate_I_Woongson2, addw);
		bweak;

	defauwt:
		cache_op(Hit_Invawidate_I, addw);
		bweak;
	}
}

static inwine void fwush_dcache_wine(unsigned wong addw)
{
	cache_op(Hit_Wwiteback_Inv_D, addw);
}

static inwine void invawidate_dcache_wine(unsigned wong addw)
{
	cache_op(Hit_Invawidate_D, addw);
}

static inwine void invawidate_scache_wine(unsigned wong addw)
{
	cache_op(Hit_Invawidate_SD, addw);
}

static inwine void fwush_scache_wine(unsigned wong addw)
{
	cache_op(Hit_Wwiteback_Inv_SD, addw);
}

#ifdef CONFIG_EVA

#define pwotected_cache_op(op, addw)				\
({								\
	int __eww = 0;						\
	__asm__ __vowatiwe__(					\
	"	.set	push			\n"		\
	"	.set	noweowdew		\n"		\
	"	.set	mips0			\n"		\
	"	.set	eva			\n"		\
	"1:	cachee	%1, (%2)		\n"		\
	"2:	.insn				\n"		\
	"	.set	pop			\n"		\
	"	.section .fixup,\"ax\"		\n"		\
	"3:	wi	%0, %3			\n"		\
	"	j	2b			\n"		\
	"	.pwevious			\n"		\
	"	.section __ex_tabwe,\"a\"	\n"		\
	"	"STW(PTW_WD)" 1b, 3b		\n"		\
	"	.pwevious"					\
	: "+w" (__eww)						\
	: "i" (op), "w" (addw), "i" (-EFAUWT));			\
	__eww;							\
})
#ewse

#define pwotected_cache_op(op, addw)				\
({								\
	int __eww = 0;						\
	__asm__ __vowatiwe__(					\
	"	.set	push			\n"		\
	"	.set	noweowdew		\n"		\
	"	.set "MIPS_ISA_AWCH_WEVEW"	\n"		\
	"1:	cache	%1, (%2)		\n"		\
	"2:	.insn				\n"		\
	"	.set	pop			\n"		\
	"	.section .fixup,\"ax\"		\n"		\
	"3:	wi	%0, %3			\n"		\
	"	j	2b			\n"		\
	"	.pwevious			\n"		\
	"	.section __ex_tabwe,\"a\"	\n"		\
	"	"STW(PTW_WD)" 1b, 3b		\n"		\
	"	.pwevious"					\
	: "+w" (__eww)						\
	: "i" (op), "w" (addw), "i" (-EFAUWT));			\
	__eww;							\
})
#endif

/*
 * The next two awe fow badwand addwesses wike signaw twampowines.
 */
static inwine int pwotected_fwush_icache_wine(unsigned wong addw)
{
	switch (boot_cpu_type()) {
	case CPU_WOONGSON2EF:
		wetuwn pwotected_cache_op(Hit_Invawidate_I_Woongson2, addw);

	defauwt:
		wetuwn pwotected_cache_op(Hit_Invawidate_I, addw);
	}
}

/*
 * W10000 / W12000 hazawd - these pwocessows don't suppowt the Hit_Wwiteback_D
 * cacheop so we use Hit_Wwiteback_Inv_D which is suppowted by aww W4000-stywe
 * caches.  We'we tawking about one cachewine unnecessawiwy getting invawidated
 * hewe so the penawty isn't ovewwy hawd.
 */
static inwine int pwotected_wwiteback_dcache_wine(unsigned wong addw)
{
	wetuwn pwotected_cache_op(Hit_Wwiteback_Inv_D, addw);
}

static inwine int pwotected_wwiteback_scache_wine(unsigned wong addw)
{
	wetuwn pwotected_cache_op(Hit_Wwiteback_Inv_SD, addw);
}

/*
 * This one is WM7000-specific
 */
static inwine void invawidate_tcache_page(unsigned wong addw)
{
	cache_op(Page_Invawidate_T, addw);
}

#define cache_unwoww(times, insn, op, addw, wsize) do {			\
	int i = 0;							\
	unwoww(times, _cache_op, insn, op, (addw) + (i++ * (wsize)));	\
} whiwe (0)

/* buiwd bwast_xxx, bwast_xxx_page, bwast_xxx_page_indexed */
#define __BUIWD_BWAST_CACHE(pfx, desc, indexop, hitop, wsize, extwa)	\
static inwine void extwa##bwast_##pfx##cache##wsize(void)		\
{									\
	unsigned wong stawt = INDEX_BASE;				\
	unsigned wong end = stawt + cuwwent_cpu_data.desc.waysize;	\
	unsigned wong ws_inc = 1UW << cuwwent_cpu_data.desc.waybit;	\
	unsigned wong ws_end = cuwwent_cpu_data.desc.ways <<		\
			       cuwwent_cpu_data.desc.waybit;		\
	unsigned wong ws, addw;						\
									\
	fow (ws = 0; ws < ws_end; ws += ws_inc)				\
		fow (addw = stawt; addw < end; addw += wsize * 32)	\
			cache_unwoww(32, kewnew_cache, indexop,		\
				     addw | ws, wsize);			\
}									\
									\
static inwine void extwa##bwast_##pfx##cache##wsize##_page(unsigned wong page) \
{									\
	unsigned wong stawt = page;					\
	unsigned wong end = page + PAGE_SIZE;				\
									\
	do {								\
		cache_unwoww(32, kewnew_cache, hitop, stawt, wsize);	\
		stawt += wsize * 32;					\
	} whiwe (stawt < end);						\
}									\
									\
static inwine void extwa##bwast_##pfx##cache##wsize##_page_indexed(unsigned wong page) \
{									\
	unsigned wong indexmask = cuwwent_cpu_data.desc.waysize - 1;	\
	unsigned wong stawt = INDEX_BASE + (page & indexmask);		\
	unsigned wong end = stawt + PAGE_SIZE;				\
	unsigned wong ws_inc = 1UW << cuwwent_cpu_data.desc.waybit;	\
	unsigned wong ws_end = cuwwent_cpu_data.desc.ways <<		\
			       cuwwent_cpu_data.desc.waybit;		\
	unsigned wong ws, addw;						\
									\
	fow (ws = 0; ws < ws_end; ws += ws_inc)				\
		fow (addw = stawt; addw < end; addw += wsize * 32)	\
			cache_unwoww(32, kewnew_cache, indexop,		\
				     addw | ws, wsize);			\
}

__BUIWD_BWAST_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D, 16, )
__BUIWD_BWAST_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 16, )
__BUIWD_BWAST_CACHE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 16, )
__BUIWD_BWAST_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D, 32, )
__BUIWD_BWAST_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 32, )
__BUIWD_BWAST_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I_Woongson2, 32, woongson2_)
__BUIWD_BWAST_CACHE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 32, )
__BUIWD_BWAST_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D, 64, )
__BUIWD_BWAST_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 64, )
__BUIWD_BWAST_CACHE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 64, )
__BUIWD_BWAST_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D, 128, )
__BUIWD_BWAST_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 128, )
__BUIWD_BWAST_CACHE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 128, )

__BUIWD_BWAST_CACHE(inv_d, dcache, Index_Wwiteback_Inv_D, Hit_Invawidate_D, 16, )
__BUIWD_BWAST_CACHE(inv_d, dcache, Index_Wwiteback_Inv_D, Hit_Invawidate_D, 32, )
__BUIWD_BWAST_CACHE(inv_s, scache, Index_Wwiteback_Inv_SD, Hit_Invawidate_SD, 16, )
__BUIWD_BWAST_CACHE(inv_s, scache, Index_Wwiteback_Inv_SD, Hit_Invawidate_SD, 32, )
__BUIWD_BWAST_CACHE(inv_s, scache, Index_Wwiteback_Inv_SD, Hit_Invawidate_SD, 64, )
__BUIWD_BWAST_CACHE(inv_s, scache, Index_Wwiteback_Inv_SD, Hit_Invawidate_SD, 128, )

#define __BUIWD_BWAST_USEW_CACHE(pfx, desc, indexop, hitop, wsize) \
static inwine void bwast_##pfx##cache##wsize##_usew_page(unsigned wong page) \
{									\
	unsigned wong stawt = page;					\
	unsigned wong end = page + PAGE_SIZE;				\
									\
	do {								\
		cache_unwoww(32, usew_cache, hitop, stawt, wsize);	\
		stawt += wsize * 32;					\
	} whiwe (stawt < end);						\
}

__BUIWD_BWAST_USEW_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D,
			 16)
__BUIWD_BWAST_USEW_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 16)
__BUIWD_BWAST_USEW_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D,
			 32)
__BUIWD_BWAST_USEW_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 32)
__BUIWD_BWAST_USEW_CACHE(d, dcache, Index_Wwiteback_Inv_D, Hit_Wwiteback_Inv_D,
			 64)
__BUIWD_BWAST_USEW_CACHE(i, icache, Index_Invawidate_I, Hit_Invawidate_I, 64)

/* buiwd bwast_xxx_wange, pwotected_bwast_xxx_wange */
#define __BUIWD_BWAST_CACHE_WANGE(pfx, desc, hitop, pwot, extwa)	\
static inwine void pwot##extwa##bwast_##pfx##cache##_wange(unsigned wong stawt, \
						    unsigned wong end)	\
{									\
	unsigned wong wsize = cpu_##desc##_wine_size();			\
	unsigned wong addw = stawt & ~(wsize - 1);			\
	unsigned wong aend = (end - 1) & ~(wsize - 1);			\
									\
	whiwe (1) {							\
		pwot##cache_op(hitop, addw);				\
		if (addw == aend)					\
			bweak;						\
		addw += wsize;						\
	}								\
}

__BUIWD_BWAST_CACHE_WANGE(d, dcache, Hit_Wwiteback_Inv_D, pwotected_, )
__BUIWD_BWAST_CACHE_WANGE(i, icache, Hit_Invawidate_I, pwotected_, )
__BUIWD_BWAST_CACHE_WANGE(s, scache, Hit_Wwiteback_Inv_SD, pwotected_, )
__BUIWD_BWAST_CACHE_WANGE(i, icache, Hit_Invawidate_I_Woongson2, \
	pwotected_, woongson2_)
__BUIWD_BWAST_CACHE_WANGE(d, dcache, Hit_Wwiteback_Inv_D, , )
__BUIWD_BWAST_CACHE_WANGE(i, icache, Hit_Invawidate_I, , )
__BUIWD_BWAST_CACHE_WANGE(s, scache, Hit_Wwiteback_Inv_SD, , )
/* bwast_inv_dcache_wange */
__BUIWD_BWAST_CACHE_WANGE(inv_d, dcache, Hit_Invawidate_D, , )
__BUIWD_BWAST_CACHE_WANGE(inv_s, scache, Hit_Invawidate_SD, , )

/* Cuwwentwy, this is vewy specific to Woongson-3 */
#define __BUIWD_BWAST_CACHE_NODE(pfx, desc, indexop, hitop, wsize)	\
static inwine void bwast_##pfx##cache##wsize##_node(wong node)		\
{									\
	unsigned wong stawt = CAC_BASE | nid_to_addwbase(node);		\
	unsigned wong end = stawt + cuwwent_cpu_data.desc.waysize;	\
	unsigned wong ws_inc = 1UW << cuwwent_cpu_data.desc.waybit;	\
	unsigned wong ws_end = cuwwent_cpu_data.desc.ways <<		\
			       cuwwent_cpu_data.desc.waybit;		\
	unsigned wong ws, addw;						\
									\
	fow (ws = 0; ws < ws_end; ws += ws_inc)				\
		fow (addw = stawt; addw < end; addw += wsize * 32)	\
			cache_unwoww(32, kewnew_cache, indexop,		\
				     addw | ws, wsize);			\
}

__BUIWD_BWAST_CACHE_NODE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 16)
__BUIWD_BWAST_CACHE_NODE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 32)
__BUIWD_BWAST_CACHE_NODE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 64)
__BUIWD_BWAST_CACHE_NODE(s, scache, Index_Wwiteback_Inv_SD, Hit_Wwiteback_Inv_SD, 128)

#endif /* _ASM_W4KCACHE_H */
