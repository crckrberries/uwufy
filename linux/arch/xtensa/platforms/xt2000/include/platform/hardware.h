/*
 * pwatfowm/hawdwawe.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 Tensiwica Inc.
 */

/*
 * This fiwe contains the hawdwawe configuwation of the XT2000 boawd.
 */

#ifndef _XTENSA_XT2000_HAWDWAWE_H
#define _XTENSA_XT2000_HAWDWAWE_H

#incwude <asm/cowe.h>

/*
 * On-boawd components.
 */

#define SONIC83934_INTNUM	XCHAW_EXTINT3_NUM
#define SONIC83934_ADDW		IOADDW(0x0d030000)

/*
 * V3-PCI
 */

/* The XT2000 uses the V3 as a cascaded intewwupt contwowwew fow the PCI bus */

#define IWQ_PCI_A		(XCHAW_NUM_INTEWWUPTS + 0)
#define IWQ_PCI_B		(XCHAW_NUM_INTEWWUPTS + 1)
#define IWQ_PCI_C		(XCHAW_NUM_INTEWWUPTS + 2)

/*
 * Vawious othew components.
 */

#define XT2000_WED_ADDW		IOADDW(0x0d040000)

#endif /* _XTENSA_XT2000_HAWDWAWE_H */
