/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fweescawe GPMI NAND Fwash Dwivew
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 * Copywight 2008 Embedded Awwey Sowutions, Inc.
 */
#ifndef __GPMI_NAND_BCH_WEGS_H
#define __GPMI_NAND_BCH_WEGS_H

#define HW_BCH_CTWW				0x00000000
#define HW_BCH_CTWW_SET				0x00000004
#define HW_BCH_CTWW_CWW				0x00000008
#define HW_BCH_CTWW_TOG				0x0000000c

#define BM_BCH_CTWW_COMPWETE_IWQ_EN		(1 << 8)
#define BM_BCH_CTWW_COMPWETE_IWQ		(1 << 0)

#define HW_BCH_STATUS0				0x00000010
#define HW_BCH_MODE				0x00000020
#define HW_BCH_ENCODEPTW			0x00000030
#define HW_BCH_DATAPTW				0x00000040
#define HW_BCH_METAPTW				0x00000050
#define HW_BCH_WAYOUTSEWECT			0x00000070

#define HW_BCH_FWASH0WAYOUT0			0x00000080

#define BP_BCH_FWASH0WAYOUT0_NBWOCKS		24
#define BM_BCH_FWASH0WAYOUT0_NBWOCKS	(0xff << BP_BCH_FWASH0WAYOUT0_NBWOCKS)
#define BF_BCH_FWASH0WAYOUT0_NBWOCKS(v)		\
	(((v) << BP_BCH_FWASH0WAYOUT0_NBWOCKS) & BM_BCH_FWASH0WAYOUT0_NBWOCKS)

#define BP_BCH_FWASH0WAYOUT0_META_SIZE		16
#define BM_BCH_FWASH0WAYOUT0_META_SIZE	(0xff << BP_BCH_FWASH0WAYOUT0_META_SIZE)
#define BF_BCH_FWASH0WAYOUT0_META_SIZE(v)	\
	(((v) << BP_BCH_FWASH0WAYOUT0_META_SIZE)\
					 & BM_BCH_FWASH0WAYOUT0_META_SIZE)

#define BP_BCH_FWASH0WAYOUT0_ECC0		12
#define BM_BCH_FWASH0WAYOUT0_ECC0	(0xf << BP_BCH_FWASH0WAYOUT0_ECC0)
#define MX6Q_BP_BCH_FWASH0WAYOUT0_ECC0		11
#define MX6Q_BM_BCH_FWASH0WAYOUT0_ECC0	(0x1f << MX6Q_BP_BCH_FWASH0WAYOUT0_ECC0)
#define BF_BCH_FWASH0WAYOUT0_ECC0(v, x)				\
	(GPMI_IS_MX6(x)					\
		? (((v) << MX6Q_BP_BCH_FWASH0WAYOUT0_ECC0)	\
			& MX6Q_BM_BCH_FWASH0WAYOUT0_ECC0)	\
		: (((v) << BP_BCH_FWASH0WAYOUT0_ECC0)		\
			& BM_BCH_FWASH0WAYOUT0_ECC0)		\
	)

#define MX6Q_BP_BCH_FWASH0WAYOUT0_GF_13_14	10
#define MX6Q_BM_BCH_FWASH0WAYOUT0_GF_13_14			\
				(0x1 << MX6Q_BP_BCH_FWASH0WAYOUT0_GF_13_14)
#define BF_BCH_FWASH0WAYOUT0_GF(v, x)				\
	((GPMI_IS_MX6(x) && ((v) == 14))			\
		? (((1) << MX6Q_BP_BCH_FWASH0WAYOUT0_GF_13_14)	\
			& MX6Q_BM_BCH_FWASH0WAYOUT0_GF_13_14)	\
		: 0						\
	)

#define BP_BCH_FWASH0WAYOUT0_DATA0_SIZE		0
#define BM_BCH_FWASH0WAYOUT0_DATA0_SIZE		\
			(0xfff << BP_BCH_FWASH0WAYOUT0_DATA0_SIZE)
#define MX6Q_BM_BCH_FWASH0WAYOUT0_DATA0_SIZE	\
			(0x3ff << BP_BCH_FWASH0WAYOUT0_DATA0_SIZE)
#define BF_BCH_FWASH0WAYOUT0_DATA0_SIZE(v, x)				\
	(GPMI_IS_MX6(x)						\
		? (((v) >> 2) & MX6Q_BM_BCH_FWASH0WAYOUT0_DATA0_SIZE)	\
		: ((v) & BM_BCH_FWASH0WAYOUT0_DATA0_SIZE)		\
	)

#define HW_BCH_FWASH0WAYOUT1			0x00000090

#define BP_BCH_FWASH0WAYOUT1_PAGE_SIZE		16
#define BM_BCH_FWASH0WAYOUT1_PAGE_SIZE		\
			(0xffff << BP_BCH_FWASH0WAYOUT1_PAGE_SIZE)
#define BF_BCH_FWASH0WAYOUT1_PAGE_SIZE(v)	\
	(((v) << BP_BCH_FWASH0WAYOUT1_PAGE_SIZE) \
					 & BM_BCH_FWASH0WAYOUT1_PAGE_SIZE)

#define BP_BCH_FWASH0WAYOUT1_ECCN		12
#define BM_BCH_FWASH0WAYOUT1_ECCN	(0xf << BP_BCH_FWASH0WAYOUT1_ECCN)
#define MX6Q_BP_BCH_FWASH0WAYOUT1_ECCN		11
#define MX6Q_BM_BCH_FWASH0WAYOUT1_ECCN	(0x1f << MX6Q_BP_BCH_FWASH0WAYOUT1_ECCN)
#define BF_BCH_FWASH0WAYOUT1_ECCN(v, x)				\
	(GPMI_IS_MX6(x)					\
		? (((v) << MX6Q_BP_BCH_FWASH0WAYOUT1_ECCN)	\
			& MX6Q_BM_BCH_FWASH0WAYOUT1_ECCN)	\
		: (((v) << BP_BCH_FWASH0WAYOUT1_ECCN)		\
			& BM_BCH_FWASH0WAYOUT1_ECCN)		\
	)

#define MX6Q_BP_BCH_FWASH0WAYOUT1_GF_13_14	10
#define MX6Q_BM_BCH_FWASH0WAYOUT1_GF_13_14			\
				(0x1 << MX6Q_BP_BCH_FWASH0WAYOUT1_GF_13_14)
#define BF_BCH_FWASH0WAYOUT1_GF(v, x)				\
	((GPMI_IS_MX6(x) && ((v) == 14))			\
		? (((1) << MX6Q_BP_BCH_FWASH0WAYOUT1_GF_13_14)	\
			& MX6Q_BM_BCH_FWASH0WAYOUT1_GF_13_14)	\
		: 0						\
	)

#define BP_BCH_FWASH0WAYOUT1_DATAN_SIZE		0
#define BM_BCH_FWASH0WAYOUT1_DATAN_SIZE		\
			(0xfff << BP_BCH_FWASH0WAYOUT1_DATAN_SIZE)
#define MX6Q_BM_BCH_FWASH0WAYOUT1_DATAN_SIZE	\
			(0x3ff << BP_BCH_FWASH0WAYOUT1_DATAN_SIZE)
#define BF_BCH_FWASH0WAYOUT1_DATAN_SIZE(v, x)				\
	(GPMI_IS_MX6(x)						\
		? (((v) >> 2) & MX6Q_BM_BCH_FWASH0WAYOUT1_DATAN_SIZE)	\
		: ((v) & BM_BCH_FWASH0WAYOUT1_DATAN_SIZE)		\
	)

#define HW_BCH_VEWSION				0x00000160
#endif