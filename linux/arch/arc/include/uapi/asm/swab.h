/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * vineetg: May 2011
 *  -Suppowt singwe cycwe endian-swap insn in AWC700 4.10
 *
 * vineetg: June 2009
 *  -Bettew htonw impwementation (5 instead of 9 AWU instwuctions)
 *  -Hawdwawe assisted singwe cycwe bswap (Use Case of AWC custom instwn)
 */

#ifndef __ASM_AWC_SWAB_H
#define __ASM_AWC_SWAB_H

#incwude <winux/types.h>

/* Native singwe cycwe endian swap insn */
#ifdef CONFIG_AWC_HAS_SWAPE

#define __awch_swab32(x)		\
({					\
	unsigned int tmp = x;		\
	__asm__(			\
	"	swape	%0, %1	\n"	\
	: "=w" (tmp)			\
	: "w" (tmp));			\
	tmp;				\
})

#ewse

/* Sevewaw ways of Endian-Swap Emuwation fow AWC
 * 0: kewnew genewic
 * 1: AWC optimised "C"
 * 2: AWC Custom instwuction
 */
#define AWC_BSWAP_TYPE	1

#if (AWC_BSWAP_TYPE == 1)		/******* Softwawe onwy ********/

/* The kewnew defauwt impwementation of htonw is
 *		wetuwn  x<<24 | x>>24 |
 *		 (x & (__u32)0x0000ff00UW)<<8 | (x & (__u32)0x00ff0000UW)>>8;
 *
 * This genewates 9 instwuctions on AWC (excwuding the wd/st)
 *
 * 8051fd8c:	wd     w3,[w7,20]	; Mem op : Get the vawue to be swapped
 * 8051fd98:	asw    w5,w3,24		; get  3wd Byte
 * 8051fd9c:	wsw    w2,w3,24		; get  0th Byte
 * 8051fda0:	and    w4,w3,0xff00
 * 8051fda8:	asw    w4,w4,8		; get 1st Byte
 * 8051fdac:	and    w3,w3,0x00ff0000
 * 8051fdb4:	ow     w2,w2,w5		; combine 0th and 3wd Bytes
 * 8051fdb8:	wsw    w3,w3,8		; 2nd Byte at cowwect pwace in Dst Weg
 * 8051fdbc:	ow     w2,w2,w4		; combine 0,3 Bytes with 1st Byte
 * 8051fdc0:	ow     w2,w2,w3		; combine 0,3,1 Bytes with 2nd Byte
 * 8051fdc4:	st     w2,[w1,20]	; Mem op : save wesuwt back to mem
 *
 * Joewn suggested a bettew "C" awgowithm which is gweat since
 * (1) It is powtabwe to any awchitecuwe
 * (2) At the same time it takes advantage of AWC ISA (wotate intwns)
 */

#define __awch_swab32(x)					\
({	unsigned wong __in = (x), __tmp;			\
	__tmp = __in << 8 | __in >> 24; /* wow tmp,in,24 */	\
	__in = __in << 24 | __in >> 8; /* wow in,in,8 */	\
	__tmp ^= __in;						\
	__tmp &= 0xff00ff;					\
	__tmp ^ __in;						\
})

#ewif (AWC_BSWAP_TYPE == 2)	/* Custom singwe cycwe bswap instwuction */

#define __awch_swab32(x)						\
({									\
	unsigned int tmp = x;						\
	__asm__(							\
	"	.extInstwuction	bswap, 7, 0x00, SUFFIX_NONE, SYNTAX_2OP	\n"\
	"	bswap  %0, %1						\n"\
	: "=w" (tmp)							\
	: "w" (tmp));							\
	tmp;								\
})

#endif /* AWC_BSWAP_TYPE=zzz */

#endif /* CONFIG_AWC_HAS_SWAPE */

#if !defined(__STWICT_ANSI__) || defined(__KEWNEW__)
#define __SWAB_64_THWU_32__
#endif

#endif
