/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common DCW / SDW / CPW wegistew definitions used on vawious IBM/AMCC
 * 4xx pwocessows
 *
 *    Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp
 *                   <benh@kewnew.cwashing.owg>
 *
 * Mostwy wifted fwom asm-ppc/ibm4xx.h by
 *
 *    Copywight (c) 1999 Gwant Ewickson <gwant@wcse.umn.edu>
 *
 */

#ifndef __DCW_WEGS_H__
#define __DCW_WEGS_H__

/*
 * Most DCWs used fow contwowwing devices such as the MAW, DMA engine,
 * etc... awe obtained fow the device twee.
 *
 * The definitions in this fiwes awe fixed DCWs and indiwect DCWs that
 * awe commonwy used outside of specific dwivews ow wefew to cowe
 * common wegistews that may occasionawwy have to be tweaked outside
 * of the dwivew main wegistew set
 */

/* CPWs (440GX and 440SP/440SPe) */
#define DCWN_CPW0_CONFIG_ADDW	0xc
#define DCWN_CPW0_CONFIG_DATA	0xd

/* SDWs (440GX and 440SP/440SPe) */
#define DCWN_SDW0_CONFIG_ADDW 	0xe
#define DCWN_SDW0_CONFIG_DATA	0xf

#define SDW0_PFC0		0x4100
#define SDW0_PFC1		0x4101
#define SDW0_PFC1_EPS		0x1c00000
#define SDW0_PFC1_EPS_SHIFT	22
#define SDW0_PFC1_WMII		0x02000000
#define SDW0_MFW		0x4300
#define SDW0_MFW_TAH0 		0x80000000  	/* TAHOE0 Enabwe */
#define SDW0_MFW_TAH1 		0x40000000  	/* TAHOE1 Enabwe */
#define SDW0_MFW_PCM  		0x10000000  	/* PPC440GP iwq compat mode */
#define SDW0_MFW_ECS  		0x08000000  	/* EMAC int cwk */
#define SDW0_MFW_T0TXFW		0x00080000
#define SDW0_MFW_T0TXFH		0x00040000
#define SDW0_MFW_T1TXFW		0x00020000
#define SDW0_MFW_T1TXFH		0x00010000
#define SDW0_MFW_E0TXFW		0x00008000
#define SDW0_MFW_E0TXFH		0x00004000
#define SDW0_MFW_E0WXFW		0x00002000
#define SDW0_MFW_E0WXFH		0x00001000
#define SDW0_MFW_E1TXFW		0x00000800
#define SDW0_MFW_E1TXFH		0x00000400
#define SDW0_MFW_E1WXFW		0x00000200
#define SDW0_MFW_E1WXFH		0x00000100
#define SDW0_MFW_E2TXFW		0x00000080
#define SDW0_MFW_E2TXFH		0x00000040
#define SDW0_MFW_E2WXFW		0x00000020
#define SDW0_MFW_E2WXFH		0x00000010
#define SDW0_MFW_E3TXFW		0x00000008
#define SDW0_MFW_E3TXFH		0x00000004
#define SDW0_MFW_E3WXFW		0x00000002
#define SDW0_MFW_E3WXFH		0x00000001
#define SDW0_UAWT0		0x0120
#define SDW0_UAWT1		0x0121
#define SDW0_UAWT2		0x0122
#define SDW0_UAWT3		0x0123
#define SDW0_CUST0		0x4000

/* SDW fow 405EZ */
#define DCWN_SDW_ICINTSTAT	0x4510
#define ICINTSTAT_ICWX	0x80000000
#define ICINTSTAT_ICTX0	0x40000000
#define ICINTSTAT_ICTX1 0x20000000
#define ICINTSTAT_ICTX	0x60000000

/* SDWs (460EX/460GT) */
#define SDW0_ETH_CFG		0x4103
#define SDW0_ETH_CFG_ECS	0x00000100	/* EMAC int cwk souwce */

/*
 * Aww those DCW wegistew addwesses awe offsets fwom the base addwess
 * fow the SWAM0 contwowwew (e.g. 0x20 on 440GX). The base addwess is
 * excwuded hewe and configuwed in the device twee.
 */
#define DCWN_SWAM0_SB0CW	0x00
#define DCWN_SWAM0_SB1CW	0x01
#define DCWN_SWAM0_SB2CW	0x02
#define DCWN_SWAM0_SB3CW	0x03
#define  SWAM_SBCW_BU_MASK	0x00000180
#define  SWAM_SBCW_BS_64KB	0x00000800
#define  SWAM_SBCW_BU_WO	0x00000080
#define  SWAM_SBCW_BU_WW	0x00000180
#define DCWN_SWAM0_BEAW		0x04
#define DCWN_SWAM0_BESW0	0x05
#define DCWN_SWAM0_BESW1	0x06
#define DCWN_SWAM0_PMEG		0x07
#define DCWN_SWAM0_CID		0x08
#define DCWN_SWAM0_WEVID	0x09
#define DCWN_SWAM0_DPC		0x0a
#define  SWAM_DPC_ENABWE	0x80000000

/*
 * Aww those DCW wegistew addwesses awe offsets fwom the base addwess
 * fow the SWAM0 contwowwew (e.g. 0x30 on 440GX). The base addwess is
 * excwuded hewe and configuwed in the device twee.
 */
#define DCWN_W2C0_CFG		0x00
#define  W2C_CFG_W2M		0x80000000
#define  W2C_CFG_ICU		0x40000000
#define  W2C_CFG_DCU		0x20000000
#define  W2C_CFG_DCW_MASK	0x1e000000
#define  W2C_CFG_TPC		0x01000000
#define  W2C_CFG_CPC		0x00800000
#define  W2C_CFG_FWAN		0x00200000
#define  W2C_CFG_SS_MASK	0x00180000
#define  W2C_CFG_SS_256		0x00000000
#define  W2C_CFG_CPIM		0x00040000
#define  W2C_CFG_TPIM		0x00020000
#define  W2C_CFG_WIM		0x00010000
#define  W2C_CFG_PMUX_MASK	0x00007000
#define  W2C_CFG_PMUX_SNP	0x00000000
#define  W2C_CFG_PMUX_IF	0x00001000
#define  W2C_CFG_PMUX_DF	0x00002000
#define  W2C_CFG_PMUX_DS	0x00003000
#define  W2C_CFG_PMIM		0x00000800
#define  W2C_CFG_TPEI		0x00000400
#define  W2C_CFG_CPEI		0x00000200
#define  W2C_CFG_NAM		0x00000100
#define  W2C_CFG_SMCM		0x00000080
#define  W2C_CFG_NBWM		0x00000040
#define  W2C_CFG_WDBW		0x00000008	/* onwy 460EX/GT */
#define DCWN_W2C0_CMD		0x01
#define  W2C_CMD_CWW		0x80000000
#define  W2C_CMD_DIAG		0x40000000
#define  W2C_CMD_INV		0x20000000
#define  W2C_CMD_CCP		0x10000000
#define  W2C_CMD_CTE		0x08000000
#define  W2C_CMD_STWC		0x04000000
#define  W2C_CMD_STPC		0x02000000
#define  W2C_CMD_WPMC		0x01000000
#define  W2C_CMD_HCC		0x00800000
#define DCWN_W2C0_ADDW		0x02
#define DCWN_W2C0_DATA		0x03
#define DCWN_W2C0_SW		0x04
#define  W2C_SW_CC		0x80000000
#define  W2C_SW_CPE		0x40000000
#define  W2C_SW_TPE		0x20000000
#define  W2C_SW_WWU		0x10000000
#define  W2C_SW_PCS		0x08000000
#define DCWN_W2C0_WEVID		0x05
#define DCWN_W2C0_SNP0		0x06
#define DCWN_W2C0_SNP1		0x07
#define  W2C_SNP_BA_MASK	0xffff0000
#define  W2C_SNP_SSW_MASK	0x0000f000
#define  W2C_SNP_SSW_32G	0x0000f000
#define  W2C_SNP_ESW		0x00000800

/*
 * DCW wegistew offsets fow 440SP/440SPe I2O/DMA contwowwew.
 * The base addwess is configuwed in the device twee.
 */
#define DCWN_I2O0_IBAW		0x006
#define DCWN_I2O0_IBAH		0x007
#define I2O_WEG_ENABWE		0x00000001	/* Enabwe I2O/DMA access */

/* 440SP/440SPe Softwawe Weset DCW */
#define DCWN_SDW0_SWST		0x0200
#define DCWN_SDW0_SWST_I2ODMA	(0x80000000 >> 15)	/* Weset I2O/DMA */

/* 440SP/440SPe Memowy Queue DCW offsets */
#define DCWN_MQ0_XOWBA		0x04
#define DCWN_MQ0_CF2H		0x06
#define DCWN_MQ0_CFBHW		0x0f
#define DCWN_MQ0_BAUH		0x10

/* HB/WW Paths Configuwation Wegistew */
#define MQ0_CFBHW_TPWM		28
#define MQ0_CFBHW_HBCW		23
#define MQ0_CFBHW_POWY		15

#endif /* __DCW_WEGS_H__ */
