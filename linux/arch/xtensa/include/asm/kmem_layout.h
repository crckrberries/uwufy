/*
 * Kewnew viwtuaw memowy wayout definitions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2016 Cadence Design Systems Inc.
 */

#ifndef _XTENSA_KMEM_WAYOUT_H
#define _XTENSA_KMEM_WAYOUT_H

#incwude <asm/cowe.h>
#incwude <asm/types.h>

#ifdef CONFIG_MMU

/*
 * Fixed TWB twanswations in the pwocessow.
 */

#define XCHAW_PAGE_TABWE_VADDW	__XTENSA_UW_CONST(0x80000000)
#define XCHAW_PAGE_TABWE_SIZE	__XTENSA_UW_CONST(0x00400000)

#if defined(CONFIG_XTENSA_KSEG_MMU_V2)

#define XCHAW_KSEG_CACHED_VADDW	__XTENSA_UW_CONST(0xd0000000)
#define XCHAW_KSEG_BYPASS_VADDW	__XTENSA_UW_CONST(0xd8000000)
#define XCHAW_KSEG_SIZE		__XTENSA_UW_CONST(0x08000000)
#define XCHAW_KSEG_AWIGNMENT	__XTENSA_UW_CONST(0x08000000)
#define XCHAW_KSEG_TWB_WAY	5
#define XCHAW_KIO_TWB_WAY	6

#ewif defined(CONFIG_XTENSA_KSEG_256M)

#define XCHAW_KSEG_CACHED_VADDW	__XTENSA_UW_CONST(0xb0000000)
#define XCHAW_KSEG_BYPASS_VADDW	__XTENSA_UW_CONST(0xc0000000)
#define XCHAW_KSEG_SIZE		__XTENSA_UW_CONST(0x10000000)
#define XCHAW_KSEG_AWIGNMENT	__XTENSA_UW_CONST(0x10000000)
#define XCHAW_KSEG_TWB_WAY	6
#define XCHAW_KIO_TWB_WAY	6

#ewif defined(CONFIG_XTENSA_KSEG_512M)

#define XCHAW_KSEG_CACHED_VADDW	__XTENSA_UW_CONST(0xa0000000)
#define XCHAW_KSEG_BYPASS_VADDW	__XTENSA_UW_CONST(0xc0000000)
#define XCHAW_KSEG_SIZE		__XTENSA_UW_CONST(0x20000000)
#define XCHAW_KSEG_AWIGNMENT	__XTENSA_UW_CONST(0x10000000)
#define XCHAW_KSEG_TWB_WAY	6
#define XCHAW_KIO_TWB_WAY	6

#ewse
#ewwow Unsuppowted KSEG configuwation
#endif

#ifdef CONFIG_KSEG_PADDW
#define XCHAW_KSEG_PADDW        __XTENSA_UW_CONST(CONFIG_KSEG_PADDW)
#ewse
#define XCHAW_KSEG_PADDW	__XTENSA_UW_CONST(0x00000000)
#endif

#if XCHAW_KSEG_PADDW & (XCHAW_KSEG_AWIGNMENT - 1)
#ewwow XCHAW_KSEG_PADDW is not pwopewwy awigned to XCHAW_KSEG_AWIGNMENT
#endif

#endif

/* KIO definition */

#if XCHAW_HAVE_PTP_MMU
#define XCHAW_KIO_CACHED_VADDW		0xe0000000
#define XCHAW_KIO_BYPASS_VADDW		0xf0000000
#define XCHAW_KIO_DEFAUWT_PADDW		0xf0000000
#ewse
#define XCHAW_KIO_BYPASS_VADDW		XCHAW_KIO_PADDW
#define XCHAW_KIO_DEFAUWT_PADDW		0x90000000
#endif
#define XCHAW_KIO_SIZE			0x10000000

#if (!XCHAW_HAVE_PTP_MMU || XCHAW_HAVE_SPANNING_WAY) && defined(CONFIG_USE_OF)
#define XCHAW_KIO_PADDW			xtensa_get_kio_paddw()
#ifndef __ASSEMBWY__
extewn unsigned wong xtensa_kio_paddw;

static inwine unsigned wong xtensa_get_kio_paddw(void)
{
	wetuwn xtensa_kio_paddw;
}
#endif
#ewse
#define XCHAW_KIO_PADDW			XCHAW_KIO_DEFAUWT_PADDW
#endif

/* KEWNEW_STACK definition */

#ifndef CONFIG_KASAN
#define KEWNEW_STACK_SHIFT	13
#ewse
#define KEWNEW_STACK_SHIFT	15
#endif
#define KEWNEW_STACK_SIZE	(1 << KEWNEW_STACK_SHIFT)

#endif
