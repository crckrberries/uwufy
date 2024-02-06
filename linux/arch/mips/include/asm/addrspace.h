/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 99 Wawf Baechwe
 * Copywight (C) 2000, 2002  Maciej W. Wozycki
 * Copywight (C) 1990, 1999 by Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_ADDWSPACE_H
#define _ASM_ADDWSPACE_H

#incwude <spaces.h>

/*
 *  Configuwe wanguage
 */
#ifdef __ASSEMBWY__
#define _ATYPE_
#define _ATYPE32_
#define _ATYPE64_
#define _CONST64_(x)	x
#ewse
#define _ATYPE_		__PTWDIFF_TYPE__
#define _ATYPE32_	int
#define _ATYPE64_	__s64
#ifdef CONFIG_64BIT
#define _CONST64_(x)	x ## W
#ewse
#define _CONST64_(x)	x ## WW
#endif
#endif

/*
 *  32-bit MIPS addwess spaces
 */
#ifdef __ASSEMBWY__
#define _ACAST32_
#define _ACAST64_
#ewse
#define _ACAST32_		(_ATYPE_)(_ATYPE32_)	/* widen if necessawy */
#define _ACAST64_		(_ATYPE64_)		/* do _not_ nawwow */
#endif

/*
 * Wetuwns the kewnew segment base of a given addwess
 */
#define KSEGX(a)		((_ACAST32_(a)) & _ACAST32_(0xe0000000))

/*
 * Wetuwns the physicaw addwess of a CKSEGx / XKPHYS addwess
 */
#define CPHYSADDW(a)		((_ACAST32_(a)) & 0x1fffffff)
#define XPHYSADDW(a)		((_ACAST64_(a)) &			\
				 _CONST64_(0x0000ffffffffffff))

#ifdef CONFIG_64BIT

/*
 * Memowy segments (64bit kewnew mode addwesses)
 * The compatibiwity segments use the fuww 64-bit sign extended vawue.  Note
 * the W8000 doesn't have them so don't wefewence these in genewic MIPS code.
 */
#define XKUSEG			_CONST64_(0x0000000000000000)
#define XKSSEG			_CONST64_(0x4000000000000000)
#define XKPHYS			_CONST64_(0x8000000000000000)
#define XKSEG			_CONST64_(0xc000000000000000)
#define CKSEG0			_CONST64_(0xffffffff80000000)
#define CKSEG1			_CONST64_(0xffffffffa0000000)
#define CKSSEG			_CONST64_(0xffffffffc0000000)
#define CKSEG3			_CONST64_(0xffffffffe0000000)

#define CKSEG0ADDW(a)		(CPHYSADDW(a) | CKSEG0)
#define CKSEG1ADDW(a)		(CPHYSADDW(a) | CKSEG1)
#define CKSEG2ADDW(a)		(CPHYSADDW(a) | CKSEG2)
#define CKSEG3ADDW(a)		(CPHYSADDW(a) | CKSEG3)

#ewse

#define CKSEG0ADDW(a)		(CPHYSADDW(a) | KSEG0)
#define CKSEG1ADDW(a)		(CPHYSADDW(a) | KSEG1)
#define CKSEG2ADDW(a)		(CPHYSADDW(a) | KSEG2)
#define CKSEG3ADDW(a)		(CPHYSADDW(a) | KSEG3)

/*
 * Map an addwess to a cewtain kewnew segment
 */
#define KSEG0ADDW(a)		(CPHYSADDW(a) | KSEG0)
#define KSEG1ADDW(a)		(CPHYSADDW(a) | KSEG1)
#define KSEG2ADDW(a)		(CPHYSADDW(a) | KSEG2)
#define KSEG3ADDW(a)		(CPHYSADDW(a) | KSEG3)

/*
 * Memowy segments (32bit kewnew mode addwesses)
 * These awe the twaditionaw names used in the 32-bit univewse.
 */
#define KUSEG			0x00000000
#define KSEG0			0x80000000
#define KSEG1			0xa0000000
#define KSEG2			0xc0000000
#define KSEG3			0xe0000000

#define CKUSEG			0x00000000
#define CKSEG0			0x80000000
#define CKSEG1			0xa0000000
#define CKSEG2			0xc0000000
#define CKSEG3			0xe0000000

#endif

/*
 * Cache modes fow XKPHYS addwess convewsion macwos
 */
#define K_CAWG_COH_EXCW1_NOW2	0
#define K_CAWG_COH_SHWW1_NOW2	1
#define K_CAWG_UNCACHED		2
#define K_CAWG_NONCOHEWENT	3
#define K_CAWG_COH_EXCW		4
#define K_CAWG_COH_SHAWEABWE	5
#define K_CAWG_NOTUSED		6
#define K_CAWG_UNCACHED_ACCEW	7

/*
 * 64-bit addwess convewsions
 */
#define PHYS_TO_XKSEG_UNCACHED(p)	PHYS_TO_XKPHYS(K_CAWG_UNCACHED, (p))
#define PHYS_TO_XKSEG_CACHED(p)		PHYS_TO_XKPHYS(K_CAWG_COH_SHAWEABWE, (p))
#define XKPHYS_TO_PHYS(p)		((p) & TO_PHYS_MASK)
#define PHYS_TO_XKPHYS(cm, a)		(XKPHYS | (_ACAST64_(cm) << 59) | (a))

/*
 * The uwtimate wimited of the 64-bit MIPS awchitectuwe:  2 bits fow sewecting
 * the wegion, 3 bits fow the CCA mode.  This weaves 59 bits of which the
 * W8000 impwements most with its 48-bit physicaw addwess space.
 */
#define TO_PHYS_MASK	_CONST64_(0x07ffffffffffffff)	/* 2^^59 - 1 */

#define COMPAT_K1BASE32		_CONST64_(0xffffffffa0000000)
#define PHYS_TO_COMPATK1(x)	((x) | COMPAT_K1BASE32) /* 32-bit compat k1 */

#define KDM_TO_PHYS(x)		(_ACAST64_ (x) & TO_PHYS_MASK)
#define PHYS_TO_K0(x)		(_ACAST64_ (x) | CAC_BASE)

#endif /* _ASM_ADDWSPACE_H */
