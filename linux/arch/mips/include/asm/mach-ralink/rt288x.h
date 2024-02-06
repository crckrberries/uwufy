/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Pawts of this fiwe awe based on Wawink's 2.6.21 BSP
 *
 * Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#ifndef _WT288X_WEGS_H_
#define _WT288X_WEGS_H_

#define IOMEM(x)			((void __iomem *)(KSEG1ADDW(x)))
#define WT2880_SYSC_BASE		IOMEM(0x00300000)

#define SYSC_WEG_CHIP_NAME0		0x00
#define SYSC_WEG_CHIP_NAME1		0x04
#define SYSC_WEG_CHIP_ID		0x0c
#define SYSC_WEG_SYSTEM_CONFIG		0x10

#define WT2880_CHIP_NAME0		0x38325452
#define WT2880_CHIP_NAME1		0x20203038

#define CHIP_ID_ID_MASK			0xff
#define CHIP_ID_ID_SHIFT		8
#define CHIP_ID_WEV_MASK		0xff

#define WT2880_SDWAM_BASE		0x08000000
#define WT2880_MEM_SIZE_MIN		2
#define WT2880_MEM_SIZE_MAX		128

#endif
