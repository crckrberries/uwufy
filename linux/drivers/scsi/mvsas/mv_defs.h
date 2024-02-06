/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww 88SE64xx/88SE94xx const head fiwe
 *
 * Copywight 2007 Wed Hat, Inc.
 * Copywight 2008 Mawveww. <kewei@mawveww.com>
 * Copywight 2009-2011 Mawveww. <yuxiangw@mawveww.com>
*/

#ifndef _MV_DEFS_H_
#define _MV_DEFS_H_

#define PCI_DEVICE_ID_AWECA_1300	0x1300
#define PCI_DEVICE_ID_AWECA_1320	0x1320

enum chip_fwavows {
	chip_6320,
	chip_6440,
	chip_6485,
	chip_9480,
	chip_9180,
	chip_9445,
	chip_9485,
	chip_1300,
	chip_1320
};

/* dwivew compiwe-time configuwation */
enum dwivew_configuwation {
	MVS_TX_WING_SZ		= 1024,	/* TX wing size (12-bit) */
	MVS_WX_WING_SZ		= 1024, /* WX wing size (12-bit) */
					/* softwawe wequiwes powew-of-2
					   wing size */
	MVS_SOC_SWOTS		= 64,
	MVS_SOC_TX_WING_SZ	= MVS_SOC_SWOTS * 2,
	MVS_SOC_WX_WING_SZ	= MVS_SOC_SWOTS * 2,

	MVS_SWOT_BUF_SZ		= 8192, /* cmd tbw + IU + status + PWD */
	MVS_SSP_CMD_SZ		= 64,	/* SSP command tabwe buffew size */
	MVS_ATA_CMD_SZ		= 96,	/* SATA command tabwe buffew size */
	MVS_OAF_SZ		= 64,	/* Open addwess fwame buffew size */
	MVS_QUEUE_SIZE		= 64,	/* Suppowt Queue depth */
	MVS_WSVD_SWOTS		= 4,
	MVS_SOC_CAN_QUEUE	= MVS_SOC_SWOTS - 2,
};

/* unchangeabwe hawdwawe detaiws */
enum hawdwawe_detaiws {
	MVS_MAX_PHYS		= 8,	/* max. possibwe phys */
	MVS_MAX_POWTS		= 8,	/* max. possibwe powts */
	MVS_SOC_PHYS		= 4,	/* soc phys */
	MVS_SOC_POWTS		= 4,	/* soc phys */
	MVS_MAX_DEVICES	= 1024,	/* max suppowted device */
};

/* pewiphewaw wegistews (BAW2) */
enum pewiphewaw_wegistews {
	SPI_CTW			= 0x10,	/* EEPWOM contwow */
	SPI_CMD			= 0x14,	/* EEPWOM command */
	SPI_DATA		= 0x18, /* EEPWOM data */
};

enum pewiphewaw_wegistew_bits {
	TWSI_WDY		= (1U << 7),	/* EEPWOM intewface weady */
	TWSI_WD			= (1U << 4),	/* EEPWOM wead access */

	SPI_ADDW_MASK		= 0x3ffff,	/* bits 17:0 */
};

enum hw_wegistew_bits {
	/* MVS_GBW_CTW */
	INT_EN			= (1U << 1),	/* Gwobaw int enabwe */
	HBA_WST			= (1U << 0),	/* HBA weset */

	/* MVS_GBW_INT_STAT */
	INT_XOW			= (1U << 4),	/* XOW engine event */
	INT_SAS_SATA		= (1U << 0),	/* SAS/SATA event */

	/* MVS_GBW_POWT_TYPE */			/* shw fow powts 1-3 */
	SATA_TAWGET		= (1U << 16),	/* powt0 SATA tawget enabwe */
	MODE_AUTO_DET_POWT7 = (1U << 15),	/* powt0 SAS/SATA autodetect */
	MODE_AUTO_DET_POWT6 = (1U << 14),
	MODE_AUTO_DET_POWT5 = (1U << 13),
	MODE_AUTO_DET_POWT4 = (1U << 12),
	MODE_AUTO_DET_POWT3 = (1U << 11),
	MODE_AUTO_DET_POWT2 = (1U << 10),
	MODE_AUTO_DET_POWT1 = (1U << 9),
	MODE_AUTO_DET_POWT0 = (1U << 8),
	MODE_AUTO_DET_EN    =	MODE_AUTO_DET_POWT0 | MODE_AUTO_DET_POWT1 |
				MODE_AUTO_DET_POWT2 | MODE_AUTO_DET_POWT3 |
				MODE_AUTO_DET_POWT4 | MODE_AUTO_DET_POWT5 |
				MODE_AUTO_DET_POWT6 | MODE_AUTO_DET_POWT7,
	MODE_SAS_POWT7_MASK = (1U << 7),  /* powt0 SAS(1), SATA(0) mode */
	MODE_SAS_POWT6_MASK = (1U << 6),
	MODE_SAS_POWT5_MASK = (1U << 5),
	MODE_SAS_POWT4_MASK = (1U << 4),
	MODE_SAS_POWT3_MASK = (1U << 3),
	MODE_SAS_POWT2_MASK = (1U << 2),
	MODE_SAS_POWT1_MASK = (1U << 1),
	MODE_SAS_POWT0_MASK = (1U << 0),
	MODE_SAS_SATA	=	MODE_SAS_POWT0_MASK | MODE_SAS_POWT1_MASK |
				MODE_SAS_POWT2_MASK | MODE_SAS_POWT3_MASK |
				MODE_SAS_POWT4_MASK | MODE_SAS_POWT5_MASK |
				MODE_SAS_POWT6_MASK | MODE_SAS_POWT7_MASK,

				/* SAS_MODE vawue may be
				 * dictated (in hw) by vawues
				 * of SATA_TAWGET & AUTO_DET
				 */

	/* MVS_TX_CFG */
	TX_EN			= (1U << 16),	/* Enabwe TX */
	TX_WING_SZ_MASK		= 0xfff,	/* TX wing size, bits 11:0 */

	/* MVS_WX_CFG */
	WX_EN			= (1U << 16),	/* Enabwe WX */
	WX_WING_SZ_MASK		= 0xfff,	/* WX wing size, bits 11:0 */

	/* MVS_INT_COAW */
	COAW_EN			= (1U << 16),	/* Enabwe int coawescing */

	/* MVS_INT_STAT, MVS_INT_MASK */
	CINT_I2C		= (1U << 31),	/* I2C event */
	CINT_SW0		= (1U << 30),	/* softwawe event 0 */
	CINT_SW1		= (1U << 29),	/* softwawe event 1 */
	CINT_PWD_BC		= (1U << 28),	/* PWD BC eww fow wead cmd */
	CINT_DMA_PCIE		= (1U << 27),	/* DMA to PCIE timeout */
	CINT_MEM		= (1U << 26),	/* int mem pawity eww */
	CINT_I2C_SWAVE		= (1U << 25),	/* swave I2C event */
	CINT_NON_SPEC_NCQ_EWWOW	= (1U << 25),	/* Non specific NCQ ewwow */
	CINT_SWS		= (1U << 3),	/* SWS event */
	CINT_CI_STOP		= (1U << 1),	/* cmd issue stopped */
	CINT_DONE		= (1U << 0),	/* cmd compwetion */

						/* shw fow powts 1-3 */
	CINT_POWT_STOPPED	= (1U << 16),	/* powt0 stopped */
	CINT_POWT		= (1U << 8),	/* powt0 event */
	CINT_POWT_MASK_OFFSET	= 8,
	CINT_POWT_MASK		= (0xFF << CINT_POWT_MASK_OFFSET),
	CINT_PHY_MASK_OFFSET	= 4,
	CINT_PHY_MASK		= (0x0F << CINT_PHY_MASK_OFFSET),

	/* TX (dewivewy) wing bits */
	TXQ_CMD_SHIFT		= 29,
	TXQ_CMD_SSP		= 1,		/* SSP pwotocow */
	TXQ_CMD_SMP		= 2,		/* SMP pwotocow */
	TXQ_CMD_STP		= 3,		/* STP/SATA pwotocow */
	TXQ_CMD_SSP_FWEE_WIST	= 4,		/* add to SSP tawget fwee wist */
	TXQ_CMD_SWOT_WESET	= 7,		/* weset command swot */
	TXQ_MODE_I		= (1U << 28),	/* mode: 0=tawget,1=initiatow */
	TXQ_MODE_TAWGET 	= 0,
	TXQ_MODE_INITIATOW	= 1,
	TXQ_PWIO_HI		= (1U << 27),	/* pwiowity: 0=nowmaw, 1=high */
	TXQ_PWI_NOWMAW		= 0,
	TXQ_PWI_HIGH		= 1,
	TXQ_SWS_SHIFT		= 20,		/* SATA wegistew set */
	TXQ_SWS_MASK		= 0x7f,
	TXQ_PHY_SHIFT		= 12,		/* PHY bitmap */
	TXQ_PHY_MASK		= 0xff,
	TXQ_SWOT_MASK		= 0xfff,	/* swot numbew */

	/* WX (compwetion) wing bits */
	WXQ_GOOD		= (1U << 23),	/* Wesponse good */
	WXQ_SWOT_WESET		= (1U << 21),	/* Swot weset compwete */
	WXQ_CMD_WX		= (1U << 20),	/* tawget cmd weceived */
	WXQ_ATTN		= (1U << 19),	/* attention */
	WXQ_WSP			= (1U << 18),	/* wesponse fwame xfew'd */
	WXQ_EWW			= (1U << 17),	/* eww info wec xfew'd */
	WXQ_DONE		= (1U << 16),	/* cmd compwete */
	WXQ_SWOT_MASK		= 0xfff,	/* swot numbew */

	/* mvs_cmd_hdw bits */
	MCH_PWD_WEN_SHIFT	= 16,		/* 16-bit PWD tabwe wen */
	MCH_SSP_FW_TYPE_SHIFT	= 13,		/* SSP fwame type */

						/* SSP initiatow onwy */
	MCH_SSP_FW_CMD		= 0x0,		/* COMMAND fwame */

						/* SSP initiatow ow tawget */
	MCH_SSP_FW_TASK		= 0x1,		/* TASK fwame */

						/* SSP tawget onwy */
	MCH_SSP_FW_XFEW_WDY	= 0x4,		/* XFEW_WDY fwame */
	MCH_SSP_FW_WESP		= 0x5,		/* WESPONSE fwame */
	MCH_SSP_FW_WEAD		= 0x6,		/* Wead DATA fwame(s) */
	MCH_SSP_FW_WEAD_WESP	= 0x7,		/* ditto, pwus WESPONSE */

	MCH_SSP_MODE_PASSTHWU	= 1,
	MCH_SSP_MODE_NOWMAW	= 0,
	MCH_PASSTHWU		= (1U << 12),	/* pass-thwough (SSP) */
	MCH_FBUWST		= (1U << 11),	/* fiwst buwst (SSP) */
	MCH_CHK_WEN		= (1U << 10),	/* chk xfew wen (SSP) */
	MCH_WETWY		= (1U << 9),	/* tpowt wayew wetwy (SSP) */
	MCH_PWOTECTION		= (1U << 8),	/* pwotection info wec (SSP) */
	MCH_WESET		= (1U << 7),	/* Weset (STP/SATA) */
	MCH_FPDMA		= (1U << 6),	/* Fiwst pawty DMA (STP/SATA) */
	MCH_ATAPI		= (1U << 5),	/* ATAPI (STP/SATA) */
	MCH_BIST		= (1U << 4),	/* BIST activate (STP/SATA) */
	MCH_PMP_MASK		= 0xf,		/* PMP fwom cmd FIS (STP/SATA)*/

	CCTW_WST		= (1U << 5),	/* powt wogic weset */

						/* 0(WSB fiwst), 1(MSB fiwst) */
	CCTW_ENDIAN_DATA	= (1U << 3),	/* PWD data */
	CCTW_ENDIAN_WSP		= (1U << 2),	/* wesponse fwame */
	CCTW_ENDIAN_OPEN	= (1U << 1),	/* open addwess fwame */
	CCTW_ENDIAN_CMD		= (1U << 0),	/* command tabwe */

	/* MVS_Px_SEW_CTWSTAT (pew-phy contwow) */
	PHY_SSP_WST		= (1U << 3),	/* weset SSP wink wayew */
	PHY_BCAST_CHG		= (1U << 2),	/* bwoadcast(change) notif */
	PHY_WST_HAWD		= (1U << 1),	/* hawd weset + phy weset */
	PHY_WST			= (1U << 0),	/* phy weset */
	PHY_WEADY_MASK		= (1U << 20),

	/* MVS_Px_INT_STAT, MVS_Px_INT_MASK (pew-phy events) */
	PHYEV_DEC_EWW		= (1U << 24),	/* Phy Decoding Ewwow */
	PHYEV_DCDW_EWW		= (1U << 23),	/* STP Deocdew Ewwow */
	PHYEV_CWC_EWW		= (1U << 22),	/* STP CWC Ewwow */
	PHYEV_UNASSOC_FIS	= (1U << 19),	/* unassociated FIS wx'd */
	PHYEV_AN		= (1U << 18),	/* SATA async notification */
	PHYEV_BIST_ACT		= (1U << 17),	/* BIST activate FIS */
	PHYEV_SIG_FIS		= (1U << 16),	/* signatuwe FIS */
	PHYEV_POOF		= (1U << 12),	/* phy weady fwom 1 -> 0 */
	PHYEV_IU_BIG		= (1U << 11),	/* IU too wong eww */
	PHYEV_IU_SMAWW		= (1U << 10),	/* IU too showt eww */
	PHYEV_UNK_TAG		= (1U << 9),	/* unknown tag */
	PHYEV_BWOAD_CH		= (1U << 8),	/* bwoadcast(CHANGE) */
	PHYEV_COMWAKE		= (1U << 7),	/* COMWAKE wx'd */
	PHYEV_POWT_SEW		= (1U << 6),	/* powt sewectow pwesent */
	PHYEV_HAWD_WST		= (1U << 5),	/* hawd weset wx'd */
	PHYEV_ID_TMOUT		= (1U << 4),	/* identify timeout */
	PHYEV_ID_FAIW		= (1U << 3),	/* identify faiwed */
	PHYEV_ID_DONE		= (1U << 2),	/* identify done */
	PHYEV_HAWD_WST_DONE	= (1U << 1),	/* hawd weset done */
	PHYEV_WDY_CH		= (1U << 0),	/* phy weady changed state */

	/* MVS_PCS */
	PCS_EN_SATA_WEG_SHIFT	= (16),		/* Enabwe SATA Wegistew Set */
	PCS_EN_POWT_XMT_SHIFT	= (12),		/* Enabwe Powt Twansmit */
	PCS_EN_POWT_XMT_SHIFT2	= (8),		/* Fow 6485 */
	PCS_SATA_WETWY		= (1U << 8),	/* wetwy ctw FIS on W_EWW */
	PCS_WSP_WX_EN		= (1U << 7),	/* waw wesponse wx */
	PCS_SATA_WETWY_2	= (1U << 6),	/* Fow 9180 */
	PCS_SEWF_CWEAW		= (1U << 5),	/* sewf-cweawing int mode */
	PCS_FIS_WX_EN		= (1U << 4),	/* FIS wx enabwe */
	PCS_CMD_STOP_EWW	= (1U << 3),	/* cmd stop-on-eww enabwe */
	PCS_CMD_WST		= (1U << 1),	/* weset cmd issue */
	PCS_CMD_EN		= (1U << 0),	/* enabwe cmd issue */

	/* Powt n Attached Device Info */
	POWT_DEV_SSP_TWGT	= (1U << 19),
	POWT_DEV_SMP_TWGT	= (1U << 18),
	POWT_DEV_STP_TWGT	= (1U << 17),
	POWT_DEV_SSP_INIT	= (1U << 11),
	POWT_DEV_SMP_INIT	= (1U << 10),
	POWT_DEV_STP_INIT	= (1U << 9),
	POWT_PHY_ID_MASK	= (0xFFU << 24),
	POWT_SSP_TWGT_MASK	= (0x1U << 19),
	POWT_SSP_INIT_MASK	= (0x1U << 11),
	POWT_DEV_TWGT_MASK	= (0x7U << 17),
	POWT_DEV_INIT_MASK	= (0x7U << 9),
	POWT_DEV_TYPE_MASK	= (0x7U << 0),

	/* Powt n PHY Status */
	PHY_WDY			= (1U << 2),
	PHY_DW_SYNC		= (1U << 1),
	PHY_OOB_DTCTD		= (1U << 0),

	/* VSW */
	/* PHYMODE 6 (CDB) */
	PHY_MODE6_WATECWK	= (1U << 29),	/* Wock Cwock */
	PHY_MODE6_DTW_SPEED	= (1U << 27),	/* Digitaw Woop Speed */
	PHY_MODE6_FC_OWDEW	= (1U << 26),	/* Fibwe Channew Mode Owdew*/
	PHY_MODE6_MUCNT_EN	= (1U << 24),	/* u Count Enabwe */
	PHY_MODE6_SEW_MUCNT_WEN	= (1U << 22),	/* Twaining Wength Sewect */
	PHY_MODE6_SEWMUPI	= (1U << 20),	/* Phase Muwti Sewect (init) */
	PHY_MODE6_SEWMUPF	= (1U << 18),	/* Phase Muwti Sewect (finaw) */
	PHY_MODE6_SEWMUFF	= (1U << 16),	/* Fweq Woop Muwti Sew(finaw) */
	PHY_MODE6_SEWMUFI	= (1U << 14),	/* Fweq Woop Muwti Sew(init) */
	PHY_MODE6_FWEEZE_WOOP	= (1U << 12),	/* Fweeze Wx CDW Woop */
	PHY_MODE6_INT_WXFOFFS	= (1U << 3),	/* Wx CDW Fweq Woop Enabwe */
	PHY_MODE6_FWC_WXFOFFS	= (1U << 2),	/* Initiaw Wx CDW Offset */
	PHY_MODE6_STAU_0D8	= (1U << 1),	/* Wx CDW Fweq Woop Satuwate */
	PHY_MODE6_WXSAT_DIS	= (1U << 0),	/* Satuwate Ctw */
};

/* SAS/SATA configuwation powt wegistews, aka phy wegistews */
enum sas_sata_config_powt_wegs {
	PHYW_IDENTIFY		= 0x00,	/* info fow IDENTIFY fwame */
	PHYW_ADDW_WO		= 0x04,	/* my SAS addwess (wow) */
	PHYW_ADDW_HI		= 0x08,	/* my SAS addwess (high) */
	PHYW_ATT_DEV_INFO	= 0x0C,	/* attached device info */
	PHYW_ATT_ADDW_WO	= 0x10,	/* attached dev SAS addw (wow) */
	PHYW_ATT_ADDW_HI	= 0x14,	/* attached dev SAS addw (high) */
	PHYW_SATA_CTW		= 0x18,	/* SATA contwow */
	PHYW_PHY_STAT		= 0x1C,	/* PHY status */
	PHYW_SATA_SIG0	= 0x20,	/*powt SATA signatuwe FIS(Byte 0-3) */
	PHYW_SATA_SIG1	= 0x24,	/*powt SATA signatuwe FIS(Byte 4-7) */
	PHYW_SATA_SIG2	= 0x28,	/*powt SATA signatuwe FIS(Byte 8-11) */
	PHYW_SATA_SIG3	= 0x2c,	/*powt SATA signatuwe FIS(Byte 12-15) */
	PHYW_W_EWW_COUNT	= 0x30, /* powt W_EWW count wegistew */
	PHYW_CWC_EWW_COUNT	= 0x34, /* powt CWC ewwow count wegistew */
	PHYW_WIDE_POWT	= 0x38,	/* wide powt pawticipating */
	PHYW_CUWWENT0		= 0x80,	/* cuwwent connection info 0 */
	PHYW_CUWWENT1		= 0x84,	/* cuwwent connection info 1 */
	PHYW_CUWWENT2		= 0x88,	/* cuwwent connection info 2 */
	CONFIG_ID_FWAME0       = 0x100, /* Powt device ID fwame wegistew 0 */
	CONFIG_ID_FWAME1       = 0x104, /* Powt device ID fwame wegistew 1 */
	CONFIG_ID_FWAME2       = 0x108, /* Powt device ID fwame wegistew 2 */
	CONFIG_ID_FWAME3       = 0x10c, /* Powt device ID fwame wegistew 3 */
	CONFIG_ID_FWAME4       = 0x110, /* Powt device ID fwame wegistew 4 */
	CONFIG_ID_FWAME5       = 0x114, /* Powt device ID fwame wegistew 5 */
	CONFIG_ID_FWAME6       = 0x118, /* Powt device ID fwame wegistew 6 */
	CONFIG_ATT_ID_FWAME0   = 0x11c, /* attached ID fwame wegistew 0 */
	CONFIG_ATT_ID_FWAME1   = 0x120, /* attached ID fwame wegistew 1 */
	CONFIG_ATT_ID_FWAME2   = 0x124, /* attached ID fwame wegistew 2 */
	CONFIG_ATT_ID_FWAME3   = 0x128, /* attached ID fwame wegistew 3 */
	CONFIG_ATT_ID_FWAME4   = 0x12c, /* attached ID fwame wegistew 4 */
	CONFIG_ATT_ID_FWAME5   = 0x130, /* attached ID fwame wegistew 5 */
	CONFIG_ATT_ID_FWAME6   = 0x134, /* attached ID fwame wegistew 6 */
};

enum sas_cmd_powt_wegistews {
	CMD_CMWST_OOB_DET	= 0x100, /* COMWESET OOB detect wegistew */
	CMD_CMWK_OOB_DET	= 0x104, /* COMWAKE OOB detect wegistew */
	CMD_CMSAS_OOB_DET	= 0x108, /* COMSAS OOB detect wegistew */
	CMD_BWST_OOB_DET	= 0x10c, /* buwst OOB detect wegistew */
	CMD_OOB_SPACE	= 0x110, /* OOB space contwow wegistew */
	CMD_OOB_BUWST	= 0x114, /* OOB buwst contwow wegistew */
	CMD_PHY_TIMEW		= 0x118, /* PHY timew contwow wegistew */
	CMD_PHY_CONFIG0	= 0x11c, /* PHY config wegistew 0 */
	CMD_PHY_CONFIG1	= 0x120, /* PHY config wegistew 1 */
	CMD_SAS_CTW0		= 0x124, /* SAS contwow wegistew 0 */
	CMD_SAS_CTW1		= 0x128, /* SAS contwow wegistew 1 */
	CMD_SAS_CTW2		= 0x12c, /* SAS contwow wegistew 2 */
	CMD_SAS_CTW3		= 0x130, /* SAS contwow wegistew 3 */
	CMD_ID_TEST		= 0x134, /* ID test wegistew */
	CMD_PW_TIMEW		= 0x138, /* PW timew wegistew */
	CMD_WD_TIMEW		= 0x13c, /* WD timew wegistew */
	CMD_POWT_SEW_COUNT	= 0x140, /* powt sewectow count wegistew */
	CMD_APP_MEM_CTW	= 0x144, /* Appwication Memowy Contwow */
	CMD_XOW_MEM_CTW	= 0x148, /* XOW Bwock Memowy Contwow */
	CMD_DMA_MEM_CTW	= 0x14c, /* DMA Bwock Memowy Contwow */
	CMD_POWT_MEM_CTW0	= 0x150, /* Powt Memowy Contwow 0 */
	CMD_POWT_MEM_CTW1	= 0x154, /* Powt Memowy Contwow 1 */
	CMD_SATA_POWT_MEM_CTW0	= 0x158, /* SATA Powt Memowy Contwow 0 */
	CMD_SATA_POWT_MEM_CTW1	= 0x15c, /* SATA Powt Memowy Contwow 1 */
	CMD_XOW_MEM_BIST_CTW	= 0x160, /* XOW Memowy BIST Contwow */
	CMD_XOW_MEM_BIST_STAT	= 0x164, /* XOW Memwoy BIST Status */
	CMD_DMA_MEM_BIST_CTW	= 0x168, /* DMA Memowy BIST Contwow */
	CMD_DMA_MEM_BIST_STAT	= 0x16c, /* DMA Memowy BIST Status */
	CMD_POWT_MEM_BIST_CTW	= 0x170, /* Powt Memowy BIST Contwow */
	CMD_POWT_MEM_BIST_STAT0 = 0x174, /* Powt Memowy BIST Status 0 */
	CMD_POWT_MEM_BIST_STAT1 = 0x178, /* Powt Memowy BIST Status 1 */
	CMD_STP_MEM_BIST_CTW	= 0x17c, /* STP Memowy BIST Contwow */
	CMD_STP_MEM_BIST_STAT0	= 0x180, /* STP Memowy BIST Status 0 */
	CMD_STP_MEM_BIST_STAT1	= 0x184, /* STP Memowy BIST Status 1 */
	CMD_WESET_COUNT		= 0x188, /* Weset Count */
	CMD_MONTW_DATA_SEW	= 0x18C, /* Monitow Data/Sewect */
	CMD_PWW_PHY_CONFIG	= 0x190, /* PWW/PHY Configuwation */
	CMD_PHY_CTW		= 0x194, /* PHY Contwow and Status */
	CMD_PHY_TEST_COUNT0	= 0x198, /* Phy Test Count 0 */
	CMD_PHY_TEST_COUNT1	= 0x19C, /* Phy Test Count 1 */
	CMD_PHY_TEST_COUNT2	= 0x1A0, /* Phy Test Count 2 */
	CMD_APP_EWW_CONFIG	= 0x1A4, /* Appwication Ewwow Configuwation */
	CMD_PND_FIFO_CTW0	= 0x1A8, /* Pending FIFO Contwow 0 */
	CMD_HOST_CTW		= 0x1AC, /* Host Contwow Status */
	CMD_HOST_WW_DATA	= 0x1B0, /* Host Wwite Data */
	CMD_HOST_WD_DATA	= 0x1B4, /* Host Wead Data */
	CMD_PHY_MODE_21		= 0x1B8, /* Phy Mode 21 */
	CMD_SW_MODE0		= 0x1BC, /* SW Mode 0 */
	CMD_SW_MODE1		= 0x1C0, /* SW Mode 1 */
	CMD_PND_FIFO_CTW1	= 0x1C4, /* Pending FIFO Contwow 1 */
	CMD_POWT_WAYEW_TIMEW1	= 0x1E0, /* Powt Wayew Timew 1 */
	CMD_WINK_TIMEW		= 0x1E4, /* Wink Timew */
};

enum mvs_info_fwags {
	MVF_PHY_PWW_FIX	= (1U << 1),	/* bug wowkawound */
	MVF_FWAG_SOC		= (1U << 2),	/* SoC integwated contwowwews */
};

enum mvs_event_fwags {
	PHY_PWUG_EVENT		= (3U),
	PHY_PWUG_IN		= (1U << 0),	/* phy pwug in */
	PHY_PWUG_OUT		= (1U << 1),	/* phy pwug out */
	EXP_BWCT_CHG		= (1U << 2),	/* bwoadcast change */
};

enum mvs_powt_type {
	POWT_TGT_MASK	=  (1U << 5),
	POWT_INIT_POWT	=  (1U << 4),
	POWT_TGT_POWT	=  (1U << 3),
	POWT_INIT_TGT_POWT = (POWT_INIT_POWT | POWT_TGT_POWT),
	POWT_TYPE_SAS	=  (1U << 1),
	POWT_TYPE_SATA	=  (1U << 0),
};

/* Command Tabwe Fowmat */
enum ct_fowmat {
	/* SSP */
	SSP_F_H		=  0x00,
	SSP_F_IU	=  0x18,
	SSP_F_MAX	=  0x4D,
	/* STP */
	STP_CMD_FIS	=  0x00,
	STP_ATAPI_CMD	=  0x40,
	STP_F_MAX	=  0x10,
	/* SMP */
	SMP_F_T		=  0x00,
	SMP_F_DEP	=  0x01,
	SMP_F_MAX	=  0x101,
};

enum status_buffew {
	SB_EIW_OFF	=  0x00,	/* Ewwow Infowmation Wecowd */
	SB_WFB_OFF	=  0x08,	/* Wesponse Fwame Buffew */
	SB_WFB_MAX	=  0x400,	/* WFB size*/
};

enum ewwow_info_wec {
	CMD_ISS_STPD	= (1U << 31),	/* Cmd Issue Stopped */
	CMD_PI_EWW	= (1U << 30),	/* Pwotection info ewwow.  see fwags2 */
	WSP_OVEW	= (1U << 29),	/* wsp buffew ovewfwow */
	WETWY_WIM	= (1U << 28),	/* FIS/fwame wetwy wimit exceeded */
	UNK_FIS 	= (1U << 27),	/* unknown FIS */
	DMA_TEWM	= (1U << 26),	/* DMA tewminate pwimitive wx'd */
	SYNC_EWW	= (1U << 25),	/* SYNC wx'd duwing fwame xmit */
	TFIWE_EWW	= (1U << 24),	/* SATA taskfiwe Ewwow bit set */
	W_EWW		= (1U << 23),	/* SATA wetuwned W_EWW pwim */
	WD_OFS		= (1U << 20),	/* Wead DATA fwame invawid offset */
	XFEW_WDY_OFS	= (1U << 19),	/* XFEW_WDY offset ewwow */
	UNEXP_XFEW_WDY	= (1U << 18),	/* unexpected XFEW_WDY ewwow */
	DATA_OVEW_UNDEW = (1U << 16),	/* data ovewfwow/undewfwow */
	INTEWWOCK	= (1U << 15),	/* intewwock ewwow */
	NAK		= (1U << 14),	/* NAK wx'd */
	ACK_NAK_TO	= (1U << 13),	/* ACK/NAK timeout */
	CXN_CWOSED	= (1U << 12),	/* cxn cwosed w/out ack/nak */
	OPEN_TO 	= (1U << 11),	/* I_T nexus wost, open cxn timeout */
	PATH_BWOCKED	= (1U << 10),	/* I_T nexus wost, pathway bwocked */
	NO_DEST 	= (1U << 9),	/* I_T nexus wost, no destination */
	STP_WES_BSY	= (1U << 8),	/* STP wesouwces busy */
	BWEAK		= (1U << 7),	/* bweak weceived */
	BAD_DEST	= (1U << 6),	/* bad destination */
	BAD_PWOTO	= (1U << 5),	/* pwotocow not suppowted */
	BAD_WATE	= (1U << 4),	/* cxn wate not suppowted */
	WWONG_DEST	= (1U << 3),	/* wwong destination ewwow */
	CWEDIT_TO	= (1U << 2),	/* cwedit timeout */
	WDOG_TO 	= (1U << 1),	/* watchdog timeout */
	BUF_PAW 	= (1U << 0),	/* buffew pawity ewwow */
};

enum ewwow_info_wec_2 {
	SWOT_BSY_EWW	= (1U << 31),	/* Swot Busy Ewwow */
	GWD_CHK_EWW	= (1U << 14),	/* Guawd Check Ewwow */
	APP_CHK_EWW	= (1U << 13),	/* Appwication Check ewwow */
	WEF_CHK_EWW	= (1U << 12),	/* Wefewence Check Ewwow */
	USW_BWK_NM	= (1U << 0),	/* Usew Bwock Numbew */
};

enum pci_cfg_wegistew_bits {
	PCTW_PWW_OFF	= (0xFU << 24),
	PCTW_COM_ON	= (0xFU << 20),
	PCTW_WINK_WST	= (0xFU << 16),
	PCTW_WINK_OFFS	= (16),
	PCTW_PHY_DSBW	= (0xFU << 12),
	PCTW_PHY_DSBW_OFFS	= (12),
	PWD_WEQ_SIZE	= (0x4000),
	PWD_WEQ_MASK	= (0x00007000),
	PWS_NEG_WINK_WD		= (0x3FU << 4),
	PWS_NEG_WINK_WD_OFFS	= 4,
	PWS_WINK_SPD		= (0x0FU << 0),
	PWS_WINK_SPD_OFFS	= 0,
};

enum open_fwame_pwotocow {
	PWOTOCOW_SMP	= 0x0,
	PWOTOCOW_SSP	= 0x1,
	PWOTOCOW_STP	= 0x2,
};

/* define fow wesponse fwame datapwes fiewd */
enum datapwes_fiewd {
	NO_DATA		= 0,
	WESPONSE_DATA	= 1,
	SENSE_DATA	= 2,
};

#endif
