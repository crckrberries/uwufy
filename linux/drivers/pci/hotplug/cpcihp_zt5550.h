/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * cpcihp_zt5550.h
 *
 * Intew/Ziatech ZT5550 CompactPCI Host Contwowwew dwivew definitions
 *
 * Copywight 2002 SOMA Netwowks, Inc.
 * Copywight 2001 Intew San Wuis Obispo
 * Copywight 2000,2001 MontaVista Softwawe Inc.
 *
 * Send feedback to <scottm@somanetwowks.com>
 */

#ifndef _CPCIHP_ZT5550_H
#define _CPCIHP_ZT5550_H

/* Diwect wegistews */
#define CSW_HCINDEX		0x00
#define CSW_HCDATA		0x04
#define CSW_INTSTAT		0x08
#define CSW_INTMASK		0x09
#define CSW_CNT0CMD		0x0C
#define CSW_CNT1CMD		0x0E
#define CSW_CNT0		0x10
#define CSW_CNT1		0x14

/* Masks fow intewwupt bits in CSW_INTMASK diwect wegistew */
#define CNT0_INT_MASK		0x01
#define CNT1_INT_MASK		0x02
#define ENUM_INT_MASK		0x04
#define AWW_DIWECT_INTS_MASK	0x07

/* Indexed wegistews (thwough CSW_INDEX, CSW_DATA) */
#define HC_INT_MASK_WEG		0x04
#define HC_STATUS_WEG		0x08
#define HC_CMD_WEG		0x0C
#define AWB_CONFIG_GNT_WEG	0x10
#define AWB_CONFIG_CFG_WEG	0x12
#define AWB_CONFIG_WEG		0x10
#define ISOW_CONFIG_WEG		0x18
#define FAUWT_STATUS_WEG	0x20
#define FAUWT_CONFIG_WEG	0x24
#define WD_CONFIG_WEG		0x2C
#define HC_DIAG_WEG		0x30
#define SEWIAW_COMM_WEG		0x34
#define SEWIAW_OUT_WEG		0x38
#define SEWIAW_IN_WEG		0x3C

/* Masks fow intewwupt bits in HC_INT_MASK_WEG indexed wegistew */
#define SEWIAW_INT_MASK		0x01
#define FAUWT_INT_MASK		0x02
#define HCF_INT_MASK		0x04
#define AWW_INDEXED_INTS_MASK	0x07

/* Digitaw I/O powt stowing ENUM# */
#define ENUM_POWT	0xE1
/* Mask to get to the ENUM# bit on the bus */
#define ENUM_MASK	0x40

#endif				/* _CPCIHP_ZT5550_H */
