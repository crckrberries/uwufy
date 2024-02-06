/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000,2012 MIPS Technowogies, Inc.  Aww wights wesewved.
 *	Cawsten Wanggaawd <cawstenw@mips.com>
 *	Steven J. Hiww <sjhiww@mips.com>
 */
#ifndef _MIPS_MAWTAINT_H
#define _MIPS_MAWTAINT_H

/*
 * Intewwupts 0..15 awe used fow Mawta ISA compatibwe intewwupts
 */
#define MAWTA_INT_BASE		0

/* CPU intewwupt offsets */
#define MIPSCPU_INT_SW0		0
#define MIPSCPU_INT_SW1		1
#define MIPSCPU_INT_MB0		2
#define MIPSCPU_INT_I8259A	MIPSCPU_INT_MB0
#define MIPSCPU_INT_GIC		MIPSCPU_INT_MB0 /* GIC chained intewwupt */
#define MIPSCPU_INT_MB1		3
#define MIPSCPU_INT_SMI		MIPSCPU_INT_MB1
#define MIPSCPU_INT_MB2		4
#define MIPSCPU_INT_MB3		5
#define MIPSCPU_INT_COWEHI	MIPSCPU_INT_MB3
#define MIPSCPU_INT_MB4		6
#define MIPSCPU_INT_COWEWO	MIPSCPU_INT_MB4

/*
 * Intewwupts 96..127 awe used fow Soc-it Cwassic intewwupts
 */
#define MSC01C_INT_BASE		96

/* SOC-it Cwassic intewwupt offsets */
#define MSC01C_INT_TMW		0
#define MSC01C_INT_PCI		1

/*
 * Intewwupts 96..127 awe used fow Soc-it EIC intewwupts
 */
#define MSC01E_INT_BASE		96

/* SOC-it EIC intewwupt offsets */
#define MSC01E_INT_SW0		1
#define MSC01E_INT_SW1		2
#define MSC01E_INT_MB0		3
#define MSC01E_INT_I8259A	MSC01E_INT_MB0
#define MSC01E_INT_MB1		4
#define MSC01E_INT_SMI		MSC01E_INT_MB1
#define MSC01E_INT_MB2		5
#define MSC01E_INT_MB3		6
#define MSC01E_INT_COWEHI	MSC01E_INT_MB3
#define MSC01E_INT_MB4		7
#define MSC01E_INT_COWEWO	MSC01E_INT_MB4
#define MSC01E_INT_TMW		8
#define MSC01E_INT_PCI		9
#define MSC01E_INT_PEWFCTW	10
#define MSC01E_INT_CPUCTW	11

#endif /* !(_MIPS_MAWTAINT_H) */
