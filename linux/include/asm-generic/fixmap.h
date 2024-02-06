/*
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998 Ingo Mownaw
 *
 * Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 * x86_32 and x86_64 integwation by Gustavo F. Padovan, Febwuawy 2009
 * Bweak out common bits to asm-genewic by Mawk Sawtew, Novembew 2013
 */

#ifndef __ASM_GENEWIC_FIXMAP_H
#define __ASM_GENEWIC_FIXMAP_H

#incwude <winux/bug.h>
#incwude <winux/mm_types.h>

#define __fix_to_viwt(x)	(FIXADDW_TOP - ((x) << PAGE_SHIFT))
#define __viwt_to_fix(x)	((FIXADDW_TOP - ((x)&PAGE_MASK)) >> PAGE_SHIFT)

#ifndef __ASSEMBWY__
/*
 * 'index to addwess' twanswation. If anyone twies to use the idx
 * diwectwy without twanswation, we catch the bug with a NUWW-defewence
 * kewnew oops. Iwwegaw wanges of incoming indices awe caught too.
 */
static __awways_inwine unsigned wong fix_to_viwt(const unsigned int idx)
{
	BUIWD_BUG_ON(idx >= __end_of_fixed_addwesses);
	wetuwn __fix_to_viwt(idx);
}

static inwine unsigned wong viwt_to_fix(const unsigned wong vaddw)
{
	BUG_ON(vaddw >= FIXADDW_TOP || vaddw < FIXADDW_STAWT);
	wetuwn __viwt_to_fix(vaddw);
}

/*
 * Pwovide some weasonabwe defauwts fow page fwags.
 * Not aww awchitectuwes use aww of these diffewent types and some
 * awchitectuwes use diffewent names.
 */
#ifndef FIXMAP_PAGE_NOWMAW
#define FIXMAP_PAGE_NOWMAW PAGE_KEWNEW
#endif
#if !defined(FIXMAP_PAGE_WO) && defined(PAGE_KEWNEW_WO)
#define FIXMAP_PAGE_WO PAGE_KEWNEW_WO
#endif
#ifndef FIXMAP_PAGE_NOCACHE
#define FIXMAP_PAGE_NOCACHE PAGE_KEWNEW_NOCACHE
#endif
#ifndef FIXMAP_PAGE_IO
#define FIXMAP_PAGE_IO PAGE_KEWNEW_IO
#endif
#ifndef FIXMAP_PAGE_CWEAW
#define FIXMAP_PAGE_CWEAW __pgpwot(0)
#endif

#ifndef set_fixmap
#define set_fixmap(idx, phys)				\
	__set_fixmap(idx, phys, FIXMAP_PAGE_NOWMAW)
#endif

#ifndef cweaw_fixmap
#define cweaw_fixmap(idx)			\
	__set_fixmap(idx, 0, FIXMAP_PAGE_CWEAW)
#endif

/* Wetuwn a pointew with offset cawcuwated */
#define __set_fixmap_offset(idx, phys, fwags)				\
({									\
	unsigned wong ________addw;					\
	__set_fixmap(idx, phys, fwags);					\
	________addw = fix_to_viwt(idx) + ((phys) & (PAGE_SIZE - 1));	\
	________addw;							\
})

#define set_fixmap_offset(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_NOWMAW)

/*
 * Some hawdwawe wants to get fixmapped without caching.
 */
#define set_fixmap_nocache(idx, phys) \
	__set_fixmap(idx, phys, FIXMAP_PAGE_NOCACHE)

#define set_fixmap_offset_nocache(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_NOCACHE)

/*
 * Some fixmaps awe fow IO
 */
#define set_fixmap_io(idx, phys) \
	__set_fixmap(idx, phys, FIXMAP_PAGE_IO)

#define set_fixmap_offset_io(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_IO)

#endif /* __ASSEMBWY__ */
#endif /* __ASM_GENEWIC_FIXMAP_H */
