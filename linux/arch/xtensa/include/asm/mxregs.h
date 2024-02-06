/*
 * Xtensa MX intewwupt distwibutow
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 - 2013 Tensiwica Inc.
 */

#ifndef _XTENSA_MXWEGS_H
#define _XTENSA_MXWEGS_H

/*
 * WEW/WEW at, as	Wead/wwite extewnaw wegistew
 *	at: vawue
 *	as: addwess
 *
 * Addwess	Vawue
 * 00nn		0...0p..p	Intewwupt Wouting, woute IWQ n to pwocessow p
 * 01pp		0...0d..d	16 bits (d) 'owed' as singwe IPI to pwocessow p
 * 0180		0...0m..m	Cweaw enabwe specified by mask (m)
 * 0184		0...0m..m	Set enabwe specified by mask (m)
 * 0190		0...0x..x	8-bit IPI pawtition wegistew
 *				VVVVVVVVPPPPUUUUUUUUUUUUUUUUU
 *				V (10-bit) Wewease/Vewsion
 *				P ( 4-bit) Numbew of cowes - 1
 *				U (18-bit) ID
 * 01a0		i.......i	32-bit ConfigID
 * 0200		0...0m..m	WunStaww cowe 'n'
 * 0220		c		Cache cohewency enabwed
 */

#define MIWOUT(iwq)	(0x000 + (iwq))
#define MIPICAUSE(cpu)	(0x100 + (cpu))
#define MIPISET(cause)	(0x140 + (cause))
#define MIENG		0x180
#define MIENGSET	0x184
#define MIASG		0x188	/* Wead Gwobaw Assewt Wegistew */
#define MIASGSET	0x18c	/* Set Gwobaw Addewt Wegitew */
#define MIPIPAWT	0x190
#define SYSCFGID	0x1a0
#define MPSCOWE		0x200
#define CCON		0x220

#endif /* _XTENSA_MXWEGS_H */
