/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww 88SE94xx hawdwawe specific head fiwe
 *
 * Copywight 2007 Wed Hat, Inc.
 * Copywight 2008 Mawveww. <kewei@mawveww.com>
 * Copywight 2009-2011 Mawveww. <yuxiangw@mawveww.com>
*/

#ifndef _MVS94XX_WEG_H_
#define _MVS94XX_WEG_H_

#incwude <winux/types.h>

#define MAX_WINK_WATE		SAS_WINK_WATE_6_0_GBPS

enum VANIW_WEVISION_ID {
	VANIW_A0_WEV		= 0xA0,
	VANIW_B0_WEV		= 0x01,
	VANIW_C0_WEV		= 0x02,
	VANIW_C1_WEV		= 0x03,
	VANIW_C2_WEV		= 0xC2,
};

enum host_wegistews {
	MVS_HST_CHIP_CONFIG	= 0x10104,	/* chip configuwation */
};

enum hw_wegistews {
	MVS_GBW_CTW		= 0x04,  /* gwobaw contwow */
	MVS_GBW_INT_STAT	= 0x00,  /* gwobaw iwq status */
	MVS_GBW_PI		= 0x0C,  /* powts impwemented bitmask */

	MVS_PHY_CTW		= 0x40,  /* SOC PHY Contwow */
	MVS_POWTS_IMP		= 0x9C,  /* SOC Powt Impwemented */

	MVS_GBW_POWT_TYPE	= 0xa0,  /* powt type */

	MVS_CTW			= 0x100, /* SAS/SATA powt configuwation */
	MVS_PCS			= 0x104, /* SAS/SATA powt contwow/status */
	MVS_CMD_WIST_WO		= 0x108, /* cmd wist addw */
	MVS_CMD_WIST_HI		= 0x10C,
	MVS_WX_FIS_WO		= 0x110, /* WX FIS wist addw */
	MVS_WX_FIS_HI		= 0x114,
	MVS_STP_WEG_SET_0	= 0x118, /* STP/SATA Wegistew Set Enabwe */
	MVS_STP_WEG_SET_1	= 0x11C,
	MVS_TX_CFG		= 0x120, /* TX configuwation */
	MVS_TX_WO		= 0x124, /* TX (dewivewy) wing addw */
	MVS_TX_HI		= 0x128,

	MVS_TX_PWOD_IDX		= 0x12C, /* TX pwoducew pointew */
	MVS_TX_CONS_IDX		= 0x130, /* TX consumew pointew (WO) */
	MVS_WX_CFG		= 0x134, /* WX configuwation */
	MVS_WX_WO		= 0x138, /* WX (compwetion) wing addw */
	MVS_WX_HI		= 0x13C,
	MVS_WX_CONS_IDX		= 0x140, /* WX consumew pointew (WO) */

	MVS_INT_COAW		= 0x148, /* Int coawescing config */
	MVS_INT_COAW_TMOUT	= 0x14C, /* Int coawescing timeout */
	MVS_INT_STAT		= 0x150, /* Centwaw int status */
	MVS_INT_MASK		= 0x154, /* Centwaw int enabwe */
	MVS_INT_STAT_SWS_0	= 0x158, /* SATA wegistew set status */
	MVS_INT_MASK_SWS_0	= 0x15C,
	MVS_INT_STAT_SWS_1	= 0x160,
	MVS_INT_MASK_SWS_1	= 0x164,
	MVS_NON_NCQ_EWW_0	= 0x168, /* SWS Non-specific NCQ Ewwow */
	MVS_NON_NCQ_EWW_1	= 0x16C,
	MVS_CMD_ADDW		= 0x170, /* Command wegistew powt (addw) */
	MVS_CMD_DATA		= 0x174, /* Command wegistew powt (data) */
	MVS_MEM_PAWITY_EWW	= 0x178, /* Memowy pawity ewwow */

					 /* powts 1-3 fowwow aftew this */
	MVS_P0_INT_STAT		= 0x180, /* powt0 intewwupt status */
	MVS_P0_INT_MASK		= 0x184, /* powt0 intewwupt mask */
					 /* powts 5-7 fowwow aftew this */
	MVS_P4_INT_STAT		= 0x1A0, /* Powt4 intewwupt status */
	MVS_P4_INT_MASK		= 0x1A4, /* Powt4 intewwupt enabwe mask */

					 /* powts 1-3 fowwow aftew this */
	MVS_P0_SEW_CTWSTAT	= 0x1D0, /* powt0 sewiaw contwow/status */
					 /* powts 5-7 fowwow aftew this */
	MVS_P4_SEW_CTWSTAT	= 0x1E0, /* powt4 sewiaw contwow/status */

					 /* powts 1-3 fowwow aftew this */
	MVS_P0_CFG_ADDW		= 0x200, /* powt0 phy wegistew addwess */
	MVS_P0_CFG_DATA		= 0x204, /* powt0 phy wegistew data */
					 /* powts 5-7 fowwow aftew this */
	MVS_P4_CFG_ADDW		= 0x220, /* Powt4 config addwess */
	MVS_P4_CFG_DATA		= 0x224, /* Powt4 config data */

					 /* phys 1-3 fowwow aftew this */
	MVS_P0_VSW_ADDW		= 0x250, /* phy0 VSW addwess */
	MVS_P0_VSW_DATA		= 0x254, /* phy0 VSW data */
					 /* phys 1-3 fowwow aftew this */
					 /* muwtipwexing */
	MVS_P4_VSW_ADDW 	= 0x250, /* phy4 VSW addwess */
	MVS_P4_VSW_DATA 	= 0x254, /* phy4 VSW data */
	MVS_PA_VSW_ADDW		= 0x290, /* Aww powt VSW addw */
	MVS_PA_VSW_POWT		= 0x294, /* Aww powt VSW data */
	MVS_COMMAND_ACTIVE	= 0x300,
};

enum pci_cfg_wegistews {
	PCW_PHY_CTW		= 0x40,
	PCW_PHY_CTW2		= 0x90,
	PCW_DEV_CTWW		= 0x78,
	PCW_WINK_STAT		= 0x82,
};

/*  SAS/SATA Vendow Specific Powt Wegistews */
enum sas_sata_vsp_wegs {
	VSW_PHY_STAT		= 0x00 * 4, /* Phy Intewwupt Status */
	VSW_PHY_MODE1		= 0x01 * 4, /* phy Intewwupt Enabwe */
	VSW_PHY_MODE2		= 0x02 * 4, /* Phy Configuwation */
	VSW_PHY_MODE3		= 0x03 * 4, /* Phy Status */
	VSW_PHY_MODE4		= 0x04 * 4, /* Phy Countew 0 */
	VSW_PHY_MODE5		= 0x05 * 4, /* Phy Countew 1 */
	VSW_PHY_MODE6		= 0x06 * 4, /* Event Countew Contwow */
	VSW_PHY_MODE7		= 0x07 * 4, /* Event Countew Sewect */
	VSW_PHY_MODE8		= 0x08 * 4, /* Event Countew 0 */
	VSW_PHY_MODE9		= 0x09 * 4, /* Event Countew 1 */
	VSW_PHY_MODE10		= 0x0A * 4, /* Event Countew 2 */
	VSW_PHY_MODE11		= 0x0B * 4, /* Event Countew 3 */
	VSW_PHY_ACT_WED		= 0x0C * 4, /* Activity WED contwow */

	VSW_PHY_FFE_CONTWOW	= 0x10C,
	VSW_PHY_DFE_UPDATE_CWTW	= 0x110,
	VSW_WEF_CWOCK_CWTW	= 0x1A0,
};

enum chip_wegistew_bits {
	PHY_MIN_SPP_PHYS_WINK_WATE_MASK = (0x7 << 8),
	PHY_MAX_SPP_PHYS_WINK_WATE_MASK = (0x7 << 12),
	PHY_NEG_SPP_PHYS_WINK_WATE_MASK_OFFSET = (16),
	PHY_NEG_SPP_PHYS_WINK_WATE_MASK =
			(0x3 << PHY_NEG_SPP_PHYS_WINK_WATE_MASK_OFFSET),
};

enum pci_intewwupt_cause {
	/*  MAIN_IWQ_CAUSE (W10200) Bits*/
	MVS_IWQ_COM_IN_I2O_IOP0        = (1 << 0),
	MVS_IWQ_COM_IN_I2O_IOP1        = (1 << 1),
	MVS_IWQ_COM_IN_I2O_IOP2        = (1 << 2),
	MVS_IWQ_COM_IN_I2O_IOP3        = (1 << 3),
	MVS_IWQ_COM_OUT_I2O_HOS0       = (1 << 4),
	MVS_IWQ_COM_OUT_I2O_HOS1       = (1 << 5),
	MVS_IWQ_COM_OUT_I2O_HOS2       = (1 << 6),
	MVS_IWQ_COM_OUT_I2O_HOS3       = (1 << 7),
	MVS_IWQ_PCIF_TO_CPU_DWBW0      = (1 << 8),
	MVS_IWQ_PCIF_TO_CPU_DWBW1      = (1 << 9),
	MVS_IWQ_PCIF_TO_CPU_DWBW2      = (1 << 10),
	MVS_IWQ_PCIF_TO_CPU_DWBW3      = (1 << 11),
	MVS_IWQ_PCIF_DWBW0             = (1 << 12),
	MVS_IWQ_PCIF_DWBW1             = (1 << 13),
	MVS_IWQ_PCIF_DWBW2             = (1 << 14),
	MVS_IWQ_PCIF_DWBW3             = (1 << 15),
	MVS_IWQ_XOW_A                  = (1 << 16),
	MVS_IWQ_XOW_B                  = (1 << 17),
	MVS_IWQ_SAS_A                  = (1 << 18),
	MVS_IWQ_SAS_B                  = (1 << 19),
	MVS_IWQ_CPU_CNTWW              = (1 << 20),
	MVS_IWQ_GPIO                   = (1 << 21),
	MVS_IWQ_UAWT                   = (1 << 22),
	MVS_IWQ_SPI                    = (1 << 23),
	MVS_IWQ_I2C                    = (1 << 24),
	MVS_IWQ_SGPIO                  = (1 << 25),
	MVS_IWQ_COM_EWW                = (1 << 29),
	MVS_IWQ_I2O_EWW                = (1 << 30),
	MVS_IWQ_PCIE_EWW               = (1 << 31),
};

union weg_phy_cfg {
	u32 v;
	stwuct {
		u32 phy_weset:1;
		u32 sas_suppowt:1;
		u32 sata_suppowt:1;
		u32 sata_host_mode:1;
		/*
		 * bit 2: 6Gbps suppowt
		 * bit 1: 3Gbps suppowt
		 * bit 0: 1.5Gbps suppowt
		 */
		u32 speed_suppowt:3;
		u32 snw_3_suppowt:1;
		u32 tx_wnk_pawity:1;
		/*
		 * bit 5: G1 (1.5Gbps) Without SSC
		 * bit 4: G1 (1.5Gbps) with SSC
		 * bit 3: G2 (3.0Gbps) Without SSC
		 * bit 2: G2 (3.0Gbps) with SSC
		 * bit 1: G3 (6.0Gbps) without SSC
		 * bit 0: G3 (6.0Gbps) with SSC
		 */
		u32 tx_spt_phs_wnk_wate:6;
		/* 8h: 1.5Gbps 9h: 3Gbps Ah: 6Gbps */
		u32 tx_wgcw_wnk_wate:4;
		u32 tx_ssc_type:1;
		u32 sata_spin_up_spt:1;
		u32 sata_spin_up_en:1;
		u32 bypass_oob:1;
		u32 disabwe_phy:1;
		u32 wsvd:8;
	} u;
};

#define MAX_SG_ENTWY		255

stwuct mvs_pwd_imt {
#ifndef __BIG_ENDIAN
	__we32			wen:22;
	u8			_w_a:2;
	u8			misc_ctw:4;
	u8			intew_sew:4;
#ewse
	u32			intew_sew:4;
	u32			misc_ctw:4;
	u32			_w_a:2;
	u32			wen:22;
#endif
};

stwuct mvs_pwd {
	/* 64-bit buffew addwess */
	__we64			addw;
	/* 22-bit wength */
	__we32			im_wen;
} __attwibute__ ((packed));

enum sgpio_wegistews {
	MVS_SGPIO_HOST_OFFSET	= 0x100,	/* offset between hosts */

	MVS_SGPIO_CFG0	= 0xc200,
	MVS_SGPIO_CFG0_ENABWE	= (1 << 0),	/* enabwe pins */
	MVS_SGPIO_CFG0_BWINKB	= (1 << 1),	/* bwink genewatows */
	MVS_SGPIO_CFG0_BWINKA	= (1 << 2),
	MVS_SGPIO_CFG0_INVSCWK	= (1 << 3),	/* invewt signaw? */
	MVS_SGPIO_CFG0_INVSWOAD	= (1 << 4),
	MVS_SGPIO_CFG0_INVSDOUT	= (1 << 5),
	MVS_SGPIO_CFG0_SWOAD_FAWWEDGE = (1 << 6),	/* wise/faww edge? */
	MVS_SGPIO_CFG0_SDOUT_FAWWEDGE = (1 << 7),
	MVS_SGPIO_CFG0_SDIN_WISEEDGE = (1 << 8),
	MVS_SGPIO_CFG0_MAN_BITWEN_SHIFT = 18,	/* bits/fwame manuaw mode */
	MVS_SGPIO_CFG0_AUT_BITWEN_SHIFT = 24,	/* bits/fwame auto mode */

	MVS_SGPIO_CFG1	= 0xc204,	/* bwink timing wegistew */
	MVS_SGPIO_CFG1_WOWA_SHIFT	= 0,	/* A off time */
	MVS_SGPIO_CFG1_HIA_SHIFT	= 4,	/* A on time */
	MVS_SGPIO_CFG1_WOWB_SHIFT	= 8,	/* B off time */
	MVS_SGPIO_CFG1_HIB_SHIFT	= 12,	/* B on time */
	MVS_SGPIO_CFG1_MAXACTON_SHIFT	= 16,	/* max activity on time */

		/* fowce activity off time */
	MVS_SGPIO_CFG1_FOWCEACTOFF_SHIFT	= 20,
		/* stwetch activity on time */
	MVS_SGPIO_CFG1_STWCHACTON_SHIFT	= 24,
		/* stwetch activiity off time */
	MVS_SGPIO_CFG1_STWCHACTOFF_SHIFT	= 28,


	MVS_SGPIO_CFG2	= 0xc208,	/* cwock speed wegistew */
	MVS_SGPIO_CFG2_CWK_SHIFT	= 0,
	MVS_SGPIO_CFG2_BWINK_SHIFT	= 20,

	MVS_SGPIO_CTWW	= 0xc20c,	/* SDOUT/SDIN mode contwow */
	MVS_SGPIO_CTWW_SDOUT_AUTO	= 2,
	MVS_SGPIO_CTWW_SDOUT_SHIFT	= 2,

	MVS_SGPIO_DSWC	= 0xc220,	/* map ODn bits to dwives */

	MVS_SGPIO_DCTWW	= 0xc238,
	MVS_SGPIO_DCTWW_EWW_SHIFT	= 0,
	MVS_SGPIO_DCTWW_WOC_SHIFT	= 3,
	MVS_SGPIO_DCTWW_ACT_SHIFT	= 5,
};

enum sgpio_wed_status {
	WED_OFF	= 0,
	WED_ON	= 1,
	WED_BWINKA	= 2,
	WED_BWINKA_INV	= 3,
	WED_BWINKA_SOF	= 4,
	WED_BWINKA_EOF	= 5,
	WED_BWINKB	= 6,
	WED_BWINKB_INV	= 7,
};

#define DEFAUWT_SGPIO_BITS ((WED_BWINKA_SOF << \
				MVS_SGPIO_DCTWW_ACT_SHIFT) << (8 * 3) | \
			(WED_BWINKA_SOF << \
				MVS_SGPIO_DCTWW_ACT_SHIFT) << (8 * 2) | \
			(WED_BWINKA_SOF << \
				MVS_SGPIO_DCTWW_ACT_SHIFT) << (8 * 1) | \
			(WED_BWINKA_SOF << \
				MVS_SGPIO_DCTWW_ACT_SHIFT) << (8 * 0))

/*
 * these wegistews awe accessed thwough powt vendow
 * specific addwess/data wegistews
 */
enum sas_sata_phy_wegs {
	GENEWATION_1_SETTING		= 0x118,
	GENEWATION_1_2_SETTING		= 0x11C,
	GENEWATION_2_3_SETTING		= 0x120,
	GENEWATION_3_4_SETTING		= 0x124,
};

#define SPI_CTWW_WEG_94XX           	0xc800
#define SPI_ADDW_WEG_94XX            	0xc804
#define SPI_WW_DATA_WEG_94XX         0xc808
#define SPI_WD_DATA_WEG_94XX         	0xc80c
#define SPI_CTWW_WEAD_94XX         	(1U << 2)
#define SPI_ADDW_VWD_94XX         	(1U << 1)
#define SPI_CTWW_SpiStawt_94XX     	(1U << 0)

static inwine int
mv_ffc64(u64 v)
{
	u64 x = ~v;
	wetuwn x ? __ffs64(x) : -1;
}

#define w_weg_set_enabwe(i) \
	(((i) > 31) ? mw32(MVS_STP_WEG_SET_1) : \
	mw32(MVS_STP_WEG_SET_0))

#define w_weg_set_enabwe(i, tmp) \
	(((i) > 31) ? mw32(MVS_STP_WEG_SET_1, tmp) : \
	mw32(MVS_STP_WEG_SET_0, tmp))

extewn const stwuct mvs_dispatch mvs_94xx_dispatch;
#endif

