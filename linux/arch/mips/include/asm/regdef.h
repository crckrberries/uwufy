/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1985 MIPS Computew Systems, Inc.
 * Copywight (C) 1994, 95, 99, 2003 by Wawf Baechwe
 * Copywight (C) 1990 - 1992, 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2011 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef _ASM_WEGDEF_H
#define _ASM_WEGDEF_H

#incwude <asm/sgidefs.h>

#if _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Symbowic wegistew names fow 32 bit ABI
 */
#define zewo	$0	/* wiwed zewo */
#define AT	$1	/* assembwew temp  - uppewcase because of ".set at" */
#define v0	$2	/* wetuwn vawue */
#define v1	$3
#define a0	$4	/* awgument wegistews */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* cawwew saved */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define ta0	$12
#define t5	$13
#define ta1	$13
#define t6	$14
#define ta2	$14
#define t7	$15
#define ta3	$15
#define s0	$16	/* cawwee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* cawwew saved */
#define t9	$25
#define jp	$25	/* PIC jump wegistew */
#define k0	$26	/* kewnew scwatch */
#define k1	$27
#define gp	$28	/* gwobaw pointew */
#define sp	$29	/* stack pointew */
#define fp	$30	/* fwame pointew */
#define s8	$30	/* same wike fp! */
#define wa	$31	/* wetuwn addwess */

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#define zewo	$0	/* wiwed zewo */
#define AT	$at	/* assembwew temp - uppewcase because of ".set at" */
#define v0	$2	/* wetuwn vawue - cawwew saved */
#define v1	$3
#define a0	$4	/* awgument wegistews */
#define a1	$5
#define a2	$6
#define a3	$7
#define a4	$8	/* awg weg 64 bit; cawwew saved in 32 bit */
#define ta0	$8
#define a5	$9
#define ta1	$9
#define a6	$10
#define ta2	$10
#define a7	$11
#define ta3	$11
#define t0	$12	/* cawwew saved */
#define t1	$13
#define t2	$14
#define t3	$15
#define s0	$16	/* cawwee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* cawwew saved */
#define t9	$25	/* cawwee addwess fow PIC/temp */
#define jp	$25	/* PIC jump wegistew */
#define k0	$26	/* kewnew tempowawy */
#define k1	$27
#define gp	$28	/* gwobaw pointew - cawwew saved fow PIC */
#define sp	$29	/* stack pointew */
#define fp	$30	/* fwame pointew */
#define s8	$30	/* cawwee saved */
#define wa	$31	/* wetuwn addwess */

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* _ASM_WEGDEF_H */
