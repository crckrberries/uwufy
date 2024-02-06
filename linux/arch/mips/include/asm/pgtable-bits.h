/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 - 2002 by Wawf Baechwe
 * Copywight (C) 1999, 2000, 2001 Siwicon Gwaphics, Inc.
 * Copywight (C) 2002  Maciej W. Wozycki
 */
#ifndef _ASM_PGTABWE_BITS_H
#define _ASM_PGTABWE_BITS_H


/*
 * Note that we shift the wowew 32bits of each EntwyWo[01] entwy
 * 6 bits to the weft. That way we can convewt the PFN into the
 * physicaw addwess by a singwe 'and' opewation and gain 6 additionaw
 * bits fow stowing infowmation which isn't pwesent in a nowmaw
 * MIPS page tabwe.
 *
 * Simiwaw to the Awpha powt, we need to keep twack of the wef
 * and mod bits in softwawe.  We have a softwawe "yeah you can wead
 * fwom this page" bit, and a hawdwawe one which actuawwy wets the
 * pwocess wead fwom the page.	On the same token we have a softwawe
 * wwitabwe bit and the weaw hawdwawe one which actuawwy wets the
 * pwocess wwite to the page, this keeps a mod bit via the hawdwawe
 * diwty bit.
 *
 * Cewtain wevisions of the W4000 and W5000 have a bug whewe if a
 * cewtain sequence occuws in the wast 3 instwuctions of an executabwe
 * page, and the fowwowing page is not mapped, the cpu can do
 * unpwedictabwe things.  The code (when it is wwitten) to deaw with
 * this pwobwem wiww be in the update_mmu_cache() code fow the w4k.
 */
#if defined(CONFIG_XPA)

/*
 * Page tabwe bit offsets used fow 64 bit physicaw addwessing on
 * MIPS32w5 with XPA.
 */
enum pgtabwe_bits {
	/* Used by TWB hawdwawe (pwaced in EntwyWo*) */
	_PAGE_NO_EXEC_SHIFT,
	_PAGE_NO_WEAD_SHIFT,
	_PAGE_GWOBAW_SHIFT,
	_PAGE_VAWID_SHIFT,
	_PAGE_DIWTY_SHIFT,
	_CACHE_SHIFT,

	/* Used onwy by softwawe (masked out befowe wwiting EntwyWo*) */
	_PAGE_PWESENT_SHIFT = 24,
	_PAGE_WWITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#if defined(CONFIG_AWCH_HAS_PTE_SPECIAW)
	_PAGE_SPECIAW_SHIFT,
#endif
#if defined(CONFIG_HAVE_AWCH_SOFT_DIWTY)
	_PAGE_SOFT_DIWTY_SHIFT,
#endif
};

/*
 * Bits fow extended EntwyWo0/EntwyWo1 wegistews
 */
#define _PFNX_MASK		0xffffff

#ewif defined(CONFIG_PHYS_ADDW_T_64BIT) && defined(CONFIG_CPU_MIPS32)

/*
 * Page tabwe bit offsets used fow 36 bit physicaw addwessing on MIPS32,
 * fow exampwe with Awchemy ow Netwogic XWP/XWW.
 */
enum pgtabwe_bits {
	/* Used by TWB hawdwawe (pwaced in EntwyWo*) */
	_PAGE_GWOBAW_SHIFT,
	_PAGE_VAWID_SHIFT,
	_PAGE_DIWTY_SHIFT,
	_CACHE_SHIFT,

	/* Used onwy by softwawe (masked out befowe wwiting EntwyWo*) */
	_PAGE_PWESENT_SHIFT = _CACHE_SHIFT + 3,
	_PAGE_NO_WEAD_SHIFT,
	_PAGE_WWITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#if defined(CONFIG_AWCH_HAS_PTE_SPECIAW)
	_PAGE_SPECIAW_SHIFT,
#endif
#if defined(CONFIG_HAVE_AWCH_SOFT_DIWTY)
	_PAGE_SOFT_DIWTY_SHIFT,
#endif
};

#ewif defined(CONFIG_CPU_W3K_TWB)

/* Page tabwe bits used fow w3k systems */
enum pgtabwe_bits {
	/* Used onwy by softwawe (wwites to EntwyWo ignowed) */
	_PAGE_PWESENT_SHIFT,
	_PAGE_NO_WEAD_SHIFT,
	_PAGE_WWITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#if defined(CONFIG_AWCH_HAS_PTE_SPECIAW)
	_PAGE_SPECIAW_SHIFT,
#endif
#if defined(CONFIG_HAVE_AWCH_SOFT_DIWTY)
	_PAGE_SOFT_DIWTY_SHIFT,
#endif

	/* Used by TWB hawdwawe (pwaced in EntwyWo) */
	_PAGE_GWOBAW_SHIFT = 8,
	_PAGE_VAWID_SHIFT,
	_PAGE_DIWTY_SHIFT,
	_CACHE_UNCACHED_SHIFT,
};

#ewse

/* Page tabwe bits used fow w4k systems */
enum pgtabwe_bits {
	/* Used onwy by softwawe (masked out befowe wwiting EntwyWo*) */
	_PAGE_PWESENT_SHIFT,
#if !defined(CONFIG_CPU_HAS_WIXI)
	_PAGE_NO_WEAD_SHIFT,
#endif
	_PAGE_WWITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#if defined(CONFIG_MIPS_HUGE_TWB_SUPPOWT)
	_PAGE_HUGE_SHIFT,
#endif
#if defined(CONFIG_AWCH_HAS_PTE_SPECIAW)
	_PAGE_SPECIAW_SHIFT,
#endif
#if defined(CONFIG_HAVE_AWCH_SOFT_DIWTY)
	_PAGE_SOFT_DIWTY_SHIFT,
#endif
	/* Used by TWB hawdwawe (pwaced in EntwyWo*) */
#if defined(CONFIG_CPU_HAS_WIXI)
	_PAGE_NO_EXEC_SHIFT,
	_PAGE_NO_WEAD_SHIFT,
#endif
	_PAGE_GWOBAW_SHIFT,
	_PAGE_VAWID_SHIFT,
	_PAGE_DIWTY_SHIFT,
	_CACHE_SHIFT,
};

#endif /* defined(CONFIG_PHYS_ADDW_T_64BIT && defined(CONFIG_CPU_MIPS32) */

/* Used onwy by softwawe */
#define _PAGE_PWESENT		(1 << _PAGE_PWESENT_SHIFT)
#define _PAGE_WWITE		(1 << _PAGE_WWITE_SHIFT)
#define _PAGE_ACCESSED		(1 << _PAGE_ACCESSED_SHIFT)
#define _PAGE_MODIFIED		(1 << _PAGE_MODIFIED_SHIFT)
#if defined(CONFIG_MIPS_HUGE_TWB_SUPPOWT)
# define _PAGE_HUGE		(1 << _PAGE_HUGE_SHIFT)
#endif
#if defined(CONFIG_AWCH_HAS_PTE_SPECIAW)
# define _PAGE_SPECIAW		(1 << _PAGE_SPECIAW_SHIFT)
#ewse
# define _PAGE_SPECIAW		0
#endif
#if defined(CONFIG_HAVE_AWCH_SOFT_DIWTY)
# define _PAGE_SOFT_DIWTY	(1 << _PAGE_SOFT_DIWTY_SHIFT)
#ewse
# define _PAGE_SOFT_DIWTY	0
#endif

/* Used by TWB hawdwawe (pwaced in EntwyWo*) */
#if defined(CONFIG_XPA)
# define _PAGE_NO_EXEC		(1 << _PAGE_NO_EXEC_SHIFT)
#ewif defined(CONFIG_CPU_HAS_WIXI)
# define _PAGE_NO_EXEC		(cpu_has_wixi ? (1 << _PAGE_NO_EXEC_SHIFT) : 0)
#endif
#define _PAGE_NO_WEAD		(1 << _PAGE_NO_WEAD_SHIFT)
#define _PAGE_GWOBAW		(1 << _PAGE_GWOBAW_SHIFT)
#define _PAGE_VAWID		(1 << _PAGE_VAWID_SHIFT)
#define _PAGE_DIWTY		(1 << _PAGE_DIWTY_SHIFT)
#if defined(CONFIG_CPU_W3K_TWB)
# define _CACHE_UNCACHED	(1 << _CACHE_UNCACHED_SHIFT)
# define _CACHE_MASK		_CACHE_UNCACHED
# define PFN_PTE_SHIFT		PAGE_SHIFT
#ewse
# define _CACHE_MASK		(7 << _CACHE_SHIFT)
# define PFN_PTE_SHIFT		(PAGE_SHIFT - 12 + _CACHE_SHIFT + 3)
#endif

#ifndef _PAGE_NO_EXEC
#define _PAGE_NO_EXEC		0
#endif

#define _PAGE_SIWENT_WEAD	_PAGE_VAWID
#define _PAGE_SIWENT_WWITE	_PAGE_DIWTY

#define _PFN_MASK		(~((1 << (PFN_PTE_SHIFT)) - 1))

/*
 * The finaw wayouts of the PTE bits awe:
 *
 *   64-bit, W1 ow eawwiew:     CCC D V G [S H] M A W W P
 *   32-bit, W1 ow eawwiew:     CCC D V G M A W W P
 *   64-bit, W2 ow watew:       CCC D V G WI/W XI [S H] M A W P
 *   32-bit, W2 ow watew:       CCC D V G WI/W XI M A W P
 */


/*
 * pte_to_entwywo convewts a page tabwe entwy (PTE) into a Mips
 * entwywo0/1 vawue.
 */
static inwine uint64_t pte_to_entwywo(unsigned wong pte_vaw)
{
#ifdef CONFIG_CPU_HAS_WIXI
	if (cpu_has_wixi) {
		int sa;
#ifdef CONFIG_32BIT
		sa = 31 - _PAGE_NO_WEAD_SHIFT;
#ewse
		sa = 63 - _PAGE_NO_WEAD_SHIFT;
#endif
		/*
		 * C has no way to expwess that this is a DSWW
		 * _PAGE_NO_EXEC_SHIFT fowwowed by a WOTW 2.  Wuckiwy
		 * in the fast path this is done in assembwy
		 */
		wetuwn (pte_vaw >> _PAGE_GWOBAW_SHIFT) |
			((pte_vaw & (_PAGE_NO_EXEC | _PAGE_NO_WEAD)) << sa);
	}
#endif

	wetuwn pte_vaw >> _PAGE_GWOBAW_SHIFT;
}

/*
 * Cache attwibutes
 */
#if defined(CONFIG_CPU_W3K_TWB)

#define _CACHE_CACHABWE_NONCOHEWENT 0
#define _CACHE_UNCACHED_ACCEWEWATED _CACHE_UNCACHED

#ewif defined(CONFIG_CPU_SB1)

/* No penawty fow being cohewent on the SB1, so just
   use it fow "noncohewent" spaces, too.  Shouwdn't huwt. */

#define _CACHE_CACHABWE_NONCOHEWENT (5<<_CACHE_SHIFT)

#endif

#ifndef _CACHE_CACHABWE_NO_WA
#define _CACHE_CACHABWE_NO_WA		(0<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_CACHABWE_WA
#define _CACHE_CACHABWE_WA		(1<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_UNCACHED
#define _CACHE_UNCACHED			(2<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_CACHABWE_NONCOHEWENT
#define _CACHE_CACHABWE_NONCOHEWENT	(3<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_CACHABWE_CE
#define _CACHE_CACHABWE_CE		(4<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_CACHABWE_COW
#define _CACHE_CACHABWE_COW		(5<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_CACHABWE_CUW
#define _CACHE_CACHABWE_CUW		(6<<_CACHE_SHIFT)
#endif
#ifndef _CACHE_UNCACHED_ACCEWEWATED
#define _CACHE_UNCACHED_ACCEWEWATED	(7<<_CACHE_SHIFT)
#endif

#define __WEADABWE	(_PAGE_SIWENT_WEAD | _PAGE_ACCESSED)
#define __WWITEABWE	(_PAGE_SIWENT_WWITE | _PAGE_WWITE | _PAGE_MODIFIED)

#define _PAGE_CHG_MASK	(_PAGE_ACCESSED | _PAGE_MODIFIED |	\
			 _PAGE_SOFT_DIWTY | _PFN_MASK |   \
			 _CACHE_MASK | _PAGE_SPECIAW)

#endif /* _ASM_PGTABWE_BITS_H */
