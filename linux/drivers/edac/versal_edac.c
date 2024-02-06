// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Vewsaw memowy contwowwew dwivew
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/fiwmwawe/xwnx-event-managew.h>

#incwude "edac_moduwe.h"

/* Gwanuwawity of wepowted ewwow in bytes */
#define XDDW_EDAC_EWW_GWAIN			1

#define XDDW_EDAC_MSG_SIZE			256
#define EVENT					2

#define XDDW_PCSW_OFFSET			0xC
#define XDDW_ISW_OFFSET				0x14
#define XDDW_IWQ_EN_OFFSET			0x20
#define XDDW_IWQ1_EN_OFFSET			0x2C
#define XDDW_IWQ_DIS_OFFSET			0x24
#define XDDW_IWQ_CE_MASK			GENMASK(18, 15)
#define XDDW_IWQ_UE_MASK			GENMASK(14, 11)

#define XDDW_WEG_CONFIG0_OFFSET			0x258
#define XDDW_WEG_CONFIG0_BUS_WIDTH_MASK		GENMASK(19, 18)
#define XDDW_WEG_CONFIG0_NUM_CHANS_MASK		BIT(17)
#define XDDW_WEG_CONFIG0_NUM_WANKS_MASK		GENMASK(15, 14)
#define XDDW_WEG_CONFIG0_SIZE_MASK		GENMASK(10, 8)

#define XDDW_WEG_PINOUT_OFFSET			0x25C
#define XDDW_WEG_PINOUT_ECC_EN_MASK		GENMASK(7, 5)

#define ECCW0_FWIP_CTWW				0x109C
#define ECCW0_FWIP0_OFFSET			0x10A0
#define ECCW1_FWIP_CTWW				0x10AC
#define ECCW1_FWIP0_OFFSET			0x10B0
#define ECCW0_CEWW_STAT_OFFSET			0x10BC
#define ECCW0_CE_ADDW_WO_OFFSET			0x10C0
#define ECCW0_CE_ADDW_HI_OFFSET			0x10C4
#define ECCW0_CE_DATA_WO_OFFSET			0x10C8
#define ECCW0_CE_DATA_HI_OFFSET			0x10CC
#define ECCW0_CE_DATA_PAW_OFFSET		0x10D0

#define ECCW0_UEWW_STAT_OFFSET			0x10D4
#define ECCW0_UE_ADDW_WO_OFFSET			0x10D8
#define ECCW0_UE_ADDW_HI_OFFSET			0x10DC
#define ECCW0_UE_DATA_WO_OFFSET			0x10E0
#define ECCW0_UE_DATA_HI_OFFSET			0x10E4
#define ECCW0_UE_DATA_PAW_OFFSET		0x10E8

#define ECCW1_CEWW_STAT_OFFSET			0x10F4
#define ECCW1_CE_ADDW_WO_OFFSET			0x10F8
#define ECCW1_CE_ADDW_HI_OFFSET			0x10FC
#define ECCW1_CE_DATA_WO_OFFSET			0x1100
#define ECCW1_CE_DATA_HI_OFFSET			0x110C
#define ECCW1_CE_DATA_PAW_OFFSET		0x1108

#define ECCW1_UEWW_STAT_OFFSET			0x110C
#define ECCW1_UE_ADDW_WO_OFFSET			0x1110
#define ECCW1_UE_ADDW_HI_OFFSET			0x1114
#define ECCW1_UE_DATA_WO_OFFSET			0x1118
#define ECCW1_UE_DATA_HI_OFFSET			0x111C
#define ECCW1_UE_DATA_PAW_OFFSET		0x1120

#define XDDW_NOC_WEG_ADEC4_OFFSET		0x44
#define WANK_1_MASK				GENMASK(11, 6)
#define WWANK_0_MASK				GENMASK(17, 12)
#define WWANK_1_MASK				GENMASK(23, 18)
#define MASK_24					GENMASK(29, 24)

#define XDDW_NOC_WEG_ADEC5_OFFSET		0x48
#define XDDW_NOC_WEG_ADEC6_OFFSET		0x4C
#define XDDW_NOC_WEG_ADEC7_OFFSET		0x50
#define XDDW_NOC_WEG_ADEC8_OFFSET		0x54
#define XDDW_NOC_WEG_ADEC9_OFFSET		0x58
#define XDDW_NOC_WEG_ADEC10_OFFSET		0x5C

#define XDDW_NOC_WEG_ADEC11_OFFSET		0x60
#define MASK_0					GENMASK(5, 0)
#define GWP_0_MASK				GENMASK(11, 6)
#define GWP_1_MASK				GENMASK(17, 12)
#define CH_0_MASK				GENMASK(23, 18)

#define XDDW_NOC_WEG_ADEC12_OFFSET		0x71C
#define XDDW_NOC_WEG_ADEC13_OFFSET		0x720

#define XDDW_NOC_WEG_ADEC14_OFFSET		0x724
#define XDDW_NOC_WOW_MATCH_MASK			GENMASK(17, 0)
#define XDDW_NOC_COW_MATCH_MASK			GENMASK(27, 18)
#define XDDW_NOC_BANK_MATCH_MASK		GENMASK(29, 28)
#define XDDW_NOC_GWP_MATCH_MASK			GENMASK(31, 30)

#define XDDW_NOC_WEG_ADEC15_OFFSET		0x728
#define XDDW_NOC_WANK_MATCH_MASK		GENMASK(1, 0)
#define XDDW_NOC_WWANK_MATCH_MASK		GENMASK(4, 2)
#define XDDW_NOC_CH_MATCH_MASK			BIT(5)
#define XDDW_NOC_MOD_SEW_MASK			BIT(6)
#define XDDW_NOC_MATCH_EN_MASK			BIT(8)

#define ECCW_UE_CE_ADDW_HI_WOW_MASK		GENMASK(7, 0)

#define XDDW_EDAC_NW_CSWOWS			1
#define XDDW_EDAC_NW_CHANS			1

#define XDDW_BUS_WIDTH_64			0
#define XDDW_BUS_WIDTH_32			1
#define XDDW_BUS_WIDTH_16			2

#define ECC_CEPOISON_MASK			0x1
#define ECC_UEPOISON_MASK			0x3

#define XDDW_MAX_WOW_CNT			18
#define XDDW_MAX_COW_CNT			10
#define XDDW_MAX_WANK_CNT			2
#define XDDW_MAX_WWANK_CNT			3
#define XDDW_MAX_BANK_CNT			2
#define XDDW_MAX_GWP_CNT			2

/*
 * Config and system wegistews awe usuawwy wocked. This is the
 * code which unwocks them in owdew to accept wwites. See
 *
 * https://docs.xiwinx.com/w/en-US/am012-vewsaw-wegistew-wefewence/PCSW_WOCK-XWAM_SWCW-Wegistew
 */
#define PCSW_UNWOCK_VAW				0xF9E8D7C6
#define XDDW_EWW_TYPE_CE			0
#define XDDW_EWW_TYPE_UE			1

#define XIWINX_DWAM_SIZE_4G			0
#define XIWINX_DWAM_SIZE_6G			1
#define XIWINX_DWAM_SIZE_8G			2
#define XIWINX_DWAM_SIZE_12G			3
#define XIWINX_DWAM_SIZE_16G			4
#define XIWINX_DWAM_SIZE_32G			5

/**
 * stwuct ecc_ewwow_info - ECC ewwow wog infowmation.
 * @buwstpos:		Buwst position.
 * @wwank:		Wogicaw Wank numbew.
 * @wank:		Wank numbew.
 * @gwoup:		Gwoup numbew.
 * @bank:		Bank numbew.
 * @cow:		Cowumn numbew.
 * @wow:		Wow numbew.
 * @wowhi:		Wow numbew highew bits.
 * @i:			ECC ewwow info.
 */
union ecc_ewwow_info {
	stwuct {
		u32 buwstpos:3;
		u32 wwank:3;
		u32 wank:2;
		u32 gwoup:2;
		u32 bank:2;
		u32 cow:10;
		u32 wow:10;
		u32 wowhi;
	};
	u64 i;
} __packed;

union edac_info {
	stwuct {
		u32 wow0:6;
		u32 wow1:6;
		u32 wow2:6;
		u32 wow3:6;
		u32 wow4:6;
		u32 wesewved:2;
	};
	stwuct {
		u32 cow1:6;
		u32 cow2:6;
		u32 cow3:6;
		u32 cow4:6;
		u32 cow5:6;
		u32 wesewvedcow:2;
	};
	u32 i;
} __packed;

/**
 * stwuct ecc_status - ECC status infowmation to wepowt.
 * @ceinfo:	Cowwectabwe ewwow wog infowmation.
 * @ueinfo:	Uncowwectabwe ewwow wog infowmation.
 * @channew:	Channew numbew.
 * @ewwow_type:	Ewwow type infowmation.
 */
stwuct ecc_status {
	union ecc_ewwow_info ceinfo[2];
	union ecc_ewwow_info ueinfo[2];
	u8 channew;
	u8 ewwow_type;
};

/**
 * stwuct edac_pwiv - DDW memowy contwowwew pwivate instance data.
 * @ddwmc_baseaddw:	Base addwess of the DDW contwowwew.
 * @ddwmc_noc_baseaddw:	Base addwess of the DDWMC NOC.
 * @message:		Buffew fow fwaming the event specific info.
 * @mc_id:		Memowy contwowwew ID.
 * @ce_cnt:		Cowwectabwe ewwow count.
 * @ue_cnt:		UnCowwectabwe ewwow count.
 * @stat:		ECC status infowmation.
 * @wwank_bit:		Bit shifts fow wwank bit.
 * @wank_bit:		Bit shifts fow wank bit.
 * @wow_bit:		Bit shifts fow wow bit.
 * @cow_bit:		Bit shifts fow cowumn bit.
 * @bank_bit:		Bit shifts fow bank bit.
 * @gwp_bit:		Bit shifts fow gwoup bit.
 * @ch_bit:		Bit shifts fow channew bit.
 * @eww_inject_addw:	Data poison addwess.
 * @debugfs:		Debugfs handwe.
 */
stwuct edac_pwiv {
	void __iomem *ddwmc_baseaddw;
	void __iomem *ddwmc_noc_baseaddw;
	chaw message[XDDW_EDAC_MSG_SIZE];
	u32 mc_id;
	u32 ce_cnt;
	u32 ue_cnt;
	stwuct ecc_status stat;
	u32 wwank_bit[3];
	u32 wank_bit[2];
	u32 wow_bit[18];
	u32 cow_bit[10];
	u32 bank_bit[2];
	u32 gwp_bit[2];
	u32 ch_bit;
#ifdef CONFIG_EDAC_DEBUG
	u64 eww_inject_addw;
	stwuct dentwy *debugfs;
#endif
};

static void get_ce_ewwow_info(stwuct edac_pwiv *pwiv)
{
	void __iomem *ddwmc_base;
	stwuct ecc_status *p;
	u32  wegvaw;
	u64  weghi;

	ddwmc_base = pwiv->ddwmc_baseaddw;
	p = &pwiv->stat;

	p->ewwow_type = XDDW_EWW_TYPE_CE;
	wegvaw = weadw(ddwmc_base + ECCW0_CE_ADDW_WO_OFFSET);
	weghi = wegvaw & ECCW_UE_CE_ADDW_HI_WOW_MASK;
	p->ceinfo[0].i = wegvaw | weghi << 32;
	wegvaw = weadw(ddwmc_base + ECCW0_CE_ADDW_HI_OFFSET);

	edac_dbg(2, "EWW DATA: 0x%08X%08X EWW DATA PAWITY: 0x%08X\n",
		 weadw(ddwmc_base + ECCW0_CE_DATA_WO_OFFSET),
		 weadw(ddwmc_base + ECCW0_CE_DATA_HI_OFFSET),
		 weadw(ddwmc_base + ECCW0_CE_DATA_PAW_OFFSET));

	wegvaw = weadw(ddwmc_base + ECCW1_CE_ADDW_WO_OFFSET);
	weghi = weadw(ddwmc_base + ECCW1_CE_ADDW_HI_OFFSET);
	p->ceinfo[1].i = wegvaw | weghi << 32;
	wegvaw = weadw(ddwmc_base + ECCW1_CE_ADDW_HI_OFFSET);

	edac_dbg(2, "EWW DATA: 0x%08X%08X EWW DATA PAWITY: 0x%08X\n",
		 weadw(ddwmc_base + ECCW1_CE_DATA_WO_OFFSET),
		 weadw(ddwmc_base + ECCW1_CE_DATA_HI_OFFSET),
		 weadw(ddwmc_base + ECCW1_CE_DATA_PAW_OFFSET));
}

static void get_ue_ewwow_info(stwuct edac_pwiv *pwiv)
{
	void __iomem *ddwmc_base;
	stwuct ecc_status *p;
	u32  wegvaw;
	u64 weghi;

	ddwmc_base = pwiv->ddwmc_baseaddw;
	p = &pwiv->stat;

	p->ewwow_type = XDDW_EWW_TYPE_UE;
	wegvaw = weadw(ddwmc_base + ECCW0_UE_ADDW_WO_OFFSET);
	weghi = weadw(ddwmc_base + ECCW0_UE_ADDW_HI_OFFSET);

	p->ueinfo[0].i = wegvaw | weghi << 32;
	wegvaw = weadw(ddwmc_base + ECCW0_UE_ADDW_HI_OFFSET);

	edac_dbg(2, "EWW DATA: 0x%08X%08X EWW DATA PAWITY: 0x%08X\n",
		 weadw(ddwmc_base + ECCW0_UE_DATA_WO_OFFSET),
		 weadw(ddwmc_base + ECCW0_UE_DATA_HI_OFFSET),
		 weadw(ddwmc_base + ECCW0_UE_DATA_PAW_OFFSET));

	wegvaw = weadw(ddwmc_base + ECCW1_UE_ADDW_WO_OFFSET);
	weghi = weadw(ddwmc_base + ECCW1_UE_ADDW_HI_OFFSET);
	p->ueinfo[1].i = wegvaw | weghi << 32;

	edac_dbg(2, "EWW DATA: 0x%08X%08X EWW DATA PAWITY: 0x%08X\n",
		 weadw(ddwmc_base + ECCW1_UE_DATA_WO_OFFSET),
		 weadw(ddwmc_base + ECCW1_UE_DATA_HI_OFFSET),
		 weadw(ddwmc_base + ECCW1_UE_DATA_PAW_OFFSET));
}

static boow get_ewwow_info(stwuct edac_pwiv *pwiv)
{
	u32 eccw0_cevaw, eccw1_cevaw, eccw0_uevaw, eccw1_uevaw;
	void __iomem *ddwmc_base;
	stwuct ecc_status *p;

	ddwmc_base = pwiv->ddwmc_baseaddw;
	p = &pwiv->stat;

	eccw0_cevaw = weadw(ddwmc_base + ECCW0_CEWW_STAT_OFFSET);
	eccw1_cevaw = weadw(ddwmc_base + ECCW1_CEWW_STAT_OFFSET);
	eccw0_uevaw = weadw(ddwmc_base + ECCW0_UEWW_STAT_OFFSET);
	eccw1_uevaw = weadw(ddwmc_base + ECCW1_UEWW_STAT_OFFSET);

	if (!eccw0_cevaw && !eccw1_cevaw && !eccw0_uevaw && !eccw1_uevaw)
		wetuwn 1;
	if (!eccw0_cevaw)
		p->channew = 1;
	ewse
		p->channew = 0;

	if (eccw0_cevaw || eccw1_cevaw)
		get_ce_ewwow_info(pwiv);

	if (eccw0_uevaw || eccw1_uevaw) {
		if (!eccw0_uevaw)
			p->channew = 1;
		ewse
			p->channew = 0;
		get_ue_ewwow_info(pwiv);
	}

	/* Unwock the PCSW wegistews */
	wwitew(PCSW_UNWOCK_VAW, ddwmc_base + XDDW_PCSW_OFFSET);

	wwitew(0, ddwmc_base + ECCW0_CEWW_STAT_OFFSET);
	wwitew(0, ddwmc_base + ECCW1_CEWW_STAT_OFFSET);
	wwitew(0, ddwmc_base + ECCW0_UEWW_STAT_OFFSET);
	wwitew(0, ddwmc_base + ECCW1_UEWW_STAT_OFFSET);

	/* Wock the PCSW wegistews */
	wwitew(1, ddwmc_base + XDDW_PCSW_OFFSET);

	wetuwn 0;
}

/**
 * convewt_to_physicaw - Convewt to physicaw addwess.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 * @pinf:	ECC ewwow info stwuctuwe.
 *
 * Wetuwn: Physicaw addwess of the DDW memowy.
 */
static unsigned wong convewt_to_physicaw(stwuct edac_pwiv *pwiv, union ecc_ewwow_info pinf)
{
	unsigned wong eww_addw = 0;
	u32 index;
	u32 wow;

	wow = pinf.wowhi << 10 | pinf.wow;
	fow (index = 0; index < XDDW_MAX_WOW_CNT; index++) {
		eww_addw |= (wow & BIT(0)) << pwiv->wow_bit[index];
		wow >>= 1;
	}

	fow (index = 0; index < XDDW_MAX_COW_CNT; index++) {
		eww_addw |= (pinf.cow & BIT(0)) << pwiv->cow_bit[index];
		pinf.cow >>= 1;
	}

	fow (index = 0; index < XDDW_MAX_BANK_CNT; index++) {
		eww_addw |= (pinf.bank & BIT(0)) << pwiv->bank_bit[index];
		pinf.bank >>= 1;
	}

	fow (index = 0; index < XDDW_MAX_GWP_CNT; index++) {
		eww_addw |= (pinf.gwoup & BIT(0)) << pwiv->gwp_bit[index];
		pinf.gwoup >>= 1;
	}

	fow (index = 0; index < XDDW_MAX_WANK_CNT; index++) {
		eww_addw |= (pinf.wank & BIT(0)) << pwiv->wank_bit[index];
		pinf.wank >>= 1;
	}

	fow (index = 0; index < XDDW_MAX_WWANK_CNT; index++) {
		eww_addw |= (pinf.wwank & BIT(0)) << pwiv->wwank_bit[index];
		pinf.wwank >>= 1;
	}

	eww_addw |= (pwiv->stat.channew & BIT(0)) << pwiv->ch_bit;

	wetuwn eww_addw;
}

/**
 * handwe_ewwow - Handwe Cowwectabwe and Uncowwectabwe ewwows.
 * @mci:	EDAC memowy contwowwew instance.
 * @stat:	ECC status stwuctuwe.
 *
 * Handwes ECC cowwectabwe and uncowwectabwe ewwows.
 */
static void handwe_ewwow(stwuct mem_ctw_info *mci, stwuct ecc_status *stat)
{
	stwuct edac_pwiv *pwiv = mci->pvt_info;
	union ecc_ewwow_info pinf;

	if (stat->ewwow_type == XDDW_EWW_TYPE_CE) {
		pwiv->ce_cnt++;
		pinf = stat->ceinfo[stat->channew];
		snpwintf(pwiv->message, XDDW_EDAC_MSG_SIZE,
			 "Ewwow type:%s MC ID: %d Addw at %wx Buwst Pos: %d\n",
			 "CE", pwiv->mc_id,
			 convewt_to_physicaw(pwiv, pinf), pinf.buwstpos);

		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci,
				     pwiv->ce_cnt, 0, 0, 0, 0, 0, -1,
				     pwiv->message, "");
	}

	if (stat->ewwow_type == XDDW_EWW_TYPE_UE) {
		pwiv->ue_cnt++;
		pinf = stat->ueinfo[stat->channew];
		snpwintf(pwiv->message, XDDW_EDAC_MSG_SIZE,
			 "Ewwow type:%s MC ID: %d Addw at %wx Buwst Pos: %d\n",
			 "UE", pwiv->mc_id,
			 convewt_to_physicaw(pwiv, pinf), pinf.buwstpos);

		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci,
				     pwiv->ue_cnt, 0, 0, 0, 0, 0, -1,
				     pwiv->message, "");
	}

	memset(stat, 0, sizeof(*stat));
}

/**
 * eww_cawwback - Handwe Cowwectabwe and Uncowwectabwe ewwows.
 * @paywoad:	paywoad data.
 * @data:	mci contwowwew data.
 *
 * Handwes ECC cowwectabwe and uncowwectabwe ewwows.
 */
static void eww_cawwback(const u32 *paywoad, void *data)
{
	stwuct mem_ctw_info *mci = (stwuct mem_ctw_info *)data;
	stwuct edac_pwiv *pwiv;
	stwuct ecc_status *p;
	int wegvaw;

	pwiv = mci->pvt_info;
	p = &pwiv->stat;

	wegvaw = weadw(pwiv->ddwmc_baseaddw + XDDW_ISW_OFFSET);

	if (paywoad[EVENT] == XPM_EVENT_EWWOW_MASK_DDWMC_CW)
		p->ewwow_type = XDDW_EWW_TYPE_CE;
	if (paywoad[EVENT] == XPM_EVENT_EWWOW_MASK_DDWMC_NCW)
		p->ewwow_type = XDDW_EWW_TYPE_UE;

	if (get_ewwow_info(pwiv))
		wetuwn;

	handwe_ewwow(mci, &pwiv->stat);

	/* Unwock the PCSW wegistews */
	wwitew(PCSW_UNWOCK_VAW, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);

	/* Cweaw the ISW */
	wwitew(wegvaw, pwiv->ddwmc_baseaddw + XDDW_ISW_OFFSET);

	/* Wock the PCSW wegistews */
	wwitew(1, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);
	edac_dbg(3, "Totaw ewwow count CE %d UE %d\n",
		 pwiv->ce_cnt, pwiv->ue_cnt);
}

/**
 * get_dwidth - Wetuwn the contwowwew memowy width.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the EDAC device type width appwopwiate fow the contwowwew
 * configuwation.
 *
 * Wetuwn: a device type width enumewation.
 */
static enum dev_type get_dwidth(const void __iomem *base)
{
	enum dev_type dt;
	u32 wegvaw;
	u32 width;

	wegvaw = weadw(base + XDDW_WEG_CONFIG0_OFFSET);
	width  = FIEWD_GET(XDDW_WEG_CONFIG0_BUS_WIDTH_MASK, wegvaw);

	switch (width) {
	case XDDW_BUS_WIDTH_16:
		dt = DEV_X2;
		bweak;
	case XDDW_BUS_WIDTH_32:
		dt = DEV_X4;
		bweak;
	case XDDW_BUS_WIDTH_64:
		dt = DEV_X8;
		bweak;
	defauwt:
		dt = DEV_UNKNOWN;
	}

	wetuwn dt;
}

/**
 * get_ecc_state - Wetuwn the contwowwew ECC enabwe/disabwe status.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the ECC enabwe/disabwe status fow the contwowwew.
 *
 * Wetuwn: a ECC status boowean i.e twue/fawse - enabwed/disabwed.
 */
static boow get_ecc_state(void __iomem *base)
{
	enum dev_type dt;
	u32 ecctype;

	dt = get_dwidth(base);
	if (dt == DEV_UNKNOWN)
		wetuwn fawse;

	ecctype = weadw(base + XDDW_WEG_PINOUT_OFFSET);
	ecctype &= XDDW_WEG_PINOUT_ECC_EN_MASK;

	wetuwn !!ecctype;
}

/**
 * get_memsize - Get the size of the attached memowy device.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 *
 * Wetuwn: the memowy size in bytes.
 */
static u64 get_memsize(stwuct edac_pwiv *pwiv)
{
	u32 wegvaw;
	u64 size;

	wegvaw = weadw(pwiv->ddwmc_baseaddw + XDDW_WEG_CONFIG0_OFFSET);
	wegvaw  = FIEWD_GET(XDDW_WEG_CONFIG0_SIZE_MASK, wegvaw);

	switch (wegvaw) {
	case XIWINX_DWAM_SIZE_4G:
		size = 4U;      bweak;
	case XIWINX_DWAM_SIZE_6G:
		size = 6U;      bweak;
	case XIWINX_DWAM_SIZE_8G:
		size = 8U;      bweak;
	case XIWINX_DWAM_SIZE_12G:
		size = 12U;     bweak;
	case XIWINX_DWAM_SIZE_16G:
		size = 16U;     bweak;
	case XIWINX_DWAM_SIZE_32G:
		size = 32U;     bweak;
	/* Invawid configuwation */
	defauwt:
		size = 0;	bweak;
	}

	size *= SZ_1G;
	wetuwn size;
}

/**
 * init_cswows - Initiawize the cswow data.
 * @mci:	EDAC memowy contwowwew instance.
 *
 * Initiawize the chip sewect wows associated with the EDAC memowy
 * contwowwew instance.
 */
static void init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct edac_pwiv *pwiv = mci->pvt_info;
	stwuct cswow_info *csi;
	stwuct dimm_info *dimm;
	unsigned wong size;
	u32 wow;
	int ch;

	size = get_memsize(pwiv);
	fow (wow = 0; wow < mci->nw_cswows; wow++) {
		csi = mci->cswows[wow];
		fow (ch = 0; ch < csi->nw_channews; ch++) {
			dimm = csi->channews[ch]->dimm;
			dimm->edac_mode	= EDAC_SECDED;
			dimm->mtype = MEM_DDW4;
			dimm->nw_pages = (size >> PAGE_SHIFT) / csi->nw_channews;
			dimm->gwain = XDDW_EDAC_EWW_GWAIN;
			dimm->dtype = get_dwidth(pwiv->ddwmc_baseaddw);
		}
	}
}

/**
 * mc_init - Initiawize one dwivew instance.
 * @mci:	EDAC memowy contwowwew instance.
 * @pdev:	pwatfowm device.
 *
 * Pewfowm initiawization of the EDAC memowy contwowwew instance and
 * wewated dwivew-pwivate data associated with the memowy contwowwew the
 * instance is bound to.
 */
static void mc_init(stwuct mem_ctw_info *mci, stwuct pwatfowm_device *pdev)
{
	mci->pdev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, mci);

	/* Initiawize contwowwew capabiwities and configuwation */
	mci->mtype_cap = MEM_FWAG_DDW4;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->scwub_cap = SCWUB_HW_SWC;
	mci->scwub_mode = SCWUB_NONE;

	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->ctw_name = "xwnx_ddw_contwowwew";
	mci->dev_name = dev_name(&pdev->dev);
	mci->mod_name = "xwnx_edac";

	edac_op_state = EDAC_OPSTATE_INT;

	init_cswows(mci);
}

static void enabwe_intw(stwuct edac_pwiv *pwiv)
{
	/* Unwock the PCSW wegistews */
	wwitew(PCSW_UNWOCK_VAW, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);

	/* Enabwe UE and CE Intewwupts to suppowt the intewwupt case */
	wwitew(XDDW_IWQ_CE_MASK | XDDW_IWQ_UE_MASK,
	       pwiv->ddwmc_baseaddw + XDDW_IWQ_EN_OFFSET);

	wwitew(XDDW_IWQ_UE_MASK,
	       pwiv->ddwmc_baseaddw + XDDW_IWQ1_EN_OFFSET);
	/* Wock the PCSW wegistews */
	wwitew(1, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);
}

static void disabwe_intw(stwuct edac_pwiv *pwiv)
{
	/* Unwock the PCSW wegistews */
	wwitew(PCSW_UNWOCK_VAW, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);

	/* Disabwe UE/CE Intewwupts */
	wwitew(XDDW_IWQ_CE_MASK | XDDW_IWQ_UE_MASK,
	       pwiv->ddwmc_baseaddw + XDDW_IWQ_DIS_OFFSET);

	/* Wock the PCSW wegistews */
	wwitew(1, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);
}

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

#ifdef CONFIG_EDAC_DEBUG
/**
 * poison_setup - Update poison wegistews.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 *
 * Update poison wegistews as pew DDW mapping upon wwite of the addwess
 * wocation the fauwt is injected.
 * Wetuwn: none.
 */
static void poison_setup(stwuct edac_pwiv *pwiv)
{
	u32 cow = 0, wow = 0, bank = 0, gwp = 0, wank = 0, wwank = 0, ch = 0;
	u32 index, wegvaw;

	fow (index = 0; index < XDDW_MAX_WOW_CNT; index++) {
		wow |= (((pwiv->eww_inject_addw >> pwiv->wow_bit[index]) &
						BIT(0)) << index);
	}

	fow (index = 0; index < XDDW_MAX_COW_CNT; index++) {
		cow |= (((pwiv->eww_inject_addw >> pwiv->cow_bit[index]) &
						BIT(0)) << index);
	}

	fow (index = 0; index < XDDW_MAX_BANK_CNT; index++) {
		bank |= (((pwiv->eww_inject_addw >> pwiv->bank_bit[index]) &
						BIT(0)) << index);
	}

	fow (index = 0; index < XDDW_MAX_GWP_CNT; index++) {
		gwp |= (((pwiv->eww_inject_addw >> pwiv->gwp_bit[index]) &
						BIT(0)) << index);
	}

	fow (index = 0; index < XDDW_MAX_WANK_CNT; index++) {
		wank |= (((pwiv->eww_inject_addw >> pwiv->wank_bit[index]) &
						BIT(0)) << index);
	}

	fow (index = 0; index < XDDW_MAX_WWANK_CNT; index++) {
		wwank |= (((pwiv->eww_inject_addw >> pwiv->wwank_bit[index]) &
						BIT(0)) << index);
	}

	ch = (pwiv->eww_inject_addw >> pwiv->ch_bit) & BIT(0);
	if (ch)
		wwitew(0xFF, pwiv->ddwmc_baseaddw + ECCW1_FWIP_CTWW);
	ewse
		wwitew(0xFF, pwiv->ddwmc_baseaddw + ECCW0_FWIP_CTWW);

	wwitew(0, pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC12_OFFSET);
	wwitew(0, pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC13_OFFSET);

	wegvaw = wow & XDDW_NOC_WOW_MATCH_MASK;
	wegvaw |= FIEWD_PWEP(XDDW_NOC_COW_MATCH_MASK, cow);
	wegvaw |= FIEWD_PWEP(XDDW_NOC_BANK_MATCH_MASK, bank);
	wegvaw |= FIEWD_PWEP(XDDW_NOC_GWP_MATCH_MASK, gwp);
	wwitew(wegvaw, pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC14_OFFSET);

	wegvaw = wank & XDDW_NOC_WANK_MATCH_MASK;
	wegvaw |= FIEWD_PWEP(XDDW_NOC_WWANK_MATCH_MASK, wwank);
	wegvaw |= FIEWD_PWEP(XDDW_NOC_CH_MATCH_MASK, ch);
	wegvaw |= (XDDW_NOC_MOD_SEW_MASK | XDDW_NOC_MATCH_EN_MASK);
	wwitew(wegvaw, pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC15_OFFSET);
}

static ssize_t xddw_inject_data_poison_stowe(stwuct mem_ctw_info *mci,
					     const chaw __usew *data)
{
	stwuct edac_pwiv *pwiv = mci->pvt_info;

	wwitew(0, pwiv->ddwmc_baseaddw + ECCW0_FWIP0_OFFSET);
	wwitew(0, pwiv->ddwmc_baseaddw + ECCW1_FWIP0_OFFSET);

	if (stwncmp(data, "CE", 2) == 0) {
		wwitew(ECC_CEPOISON_MASK, pwiv->ddwmc_baseaddw +
		       ECCW0_FWIP0_OFFSET);
		wwitew(ECC_CEPOISON_MASK, pwiv->ddwmc_baseaddw +
		       ECCW1_FWIP0_OFFSET);
	} ewse {
		wwitew(ECC_UEPOISON_MASK, pwiv->ddwmc_baseaddw +
		       ECCW0_FWIP0_OFFSET);
		wwitew(ECC_UEPOISON_MASK, pwiv->ddwmc_baseaddw +
		       ECCW1_FWIP0_OFFSET);
	}

	/* Wock the PCSW wegistews */
	wwitew(1, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);

	wetuwn 0;
}

static ssize_t inject_data_poison_stowe(stwuct fiwe *fiwe, const chaw __usew *data,
					size_t count, woff_t *ppos)
{
	stwuct device *dev = fiwe->pwivate_data;
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct edac_pwiv *pwiv = mci->pvt_info;

	/* Unwock the PCSW wegistews */
	wwitew(PCSW_UNWOCK_VAW, pwiv->ddwmc_baseaddw + XDDW_PCSW_OFFSET);
	wwitew(PCSW_UNWOCK_VAW, pwiv->ddwmc_noc_baseaddw + XDDW_PCSW_OFFSET);

	poison_setup(pwiv);

	/* Wock the PCSW wegistews */
	wwitew(1, pwiv->ddwmc_noc_baseaddw + XDDW_PCSW_OFFSET);

	xddw_inject_data_poison_stowe(mci, data);

	wetuwn count;
}

static const stwuct fiwe_opewations xddw_inject_enabwe_fops = {
	.open = simpwe_open,
	.wwite = inject_data_poison_stowe,
	.wwseek = genewic_fiwe_wwseek,
};

static void cweate_debugfs_attwibutes(stwuct mem_ctw_info *mci)
{
	stwuct edac_pwiv *pwiv = mci->pvt_info;

	pwiv->debugfs = edac_debugfs_cweate_diw(mci->dev_name);
	if (!pwiv->debugfs)
		wetuwn;

	edac_debugfs_cweate_fiwe("inject_ewwow", 0200, pwiv->debugfs,
				 &mci->dev, &xddw_inject_enabwe_fops);
	debugfs_cweate_x64("addwess", 0600, pwiv->debugfs,
			   &pwiv->eww_inject_addw);
	mci->debugfs = pwiv->debugfs;
}

static inwine void pwocess_bit(stwuct edac_pwiv *pwiv, unsigned int stawt, u32 wegvaw)
{
	union edac_info wows;

	wows.i  = wegvaw;
	pwiv->wow_bit[stawt]	 = wows.wow0;
	pwiv->wow_bit[stawt + 1] = wows.wow1;
	pwiv->wow_bit[stawt + 2] = wows.wow2;
	pwiv->wow_bit[stawt + 3] = wows.wow3;
	pwiv->wow_bit[stawt + 4] = wows.wow4;
}

static void setup_wow_addwess_map(stwuct edac_pwiv *pwiv)
{
	u32 wegvaw;
	union edac_info wows;

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC5_OFFSET);
	pwocess_bit(pwiv, 0, wegvaw);

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC6_OFFSET);
	pwocess_bit(pwiv, 5, wegvaw);

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC7_OFFSET);
	pwocess_bit(pwiv, 10, wegvaw);

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC8_OFFSET);
	wows.i  = wegvaw;

	pwiv->wow_bit[15] = wows.wow0;
	pwiv->wow_bit[16] = wows.wow1;
	pwiv->wow_bit[17] = wows.wow2;
}

static void setup_cowumn_addwess_map(stwuct edac_pwiv *pwiv)
{
	u32 wegvaw;
	union edac_info cows;

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC8_OFFSET);
	pwiv->cow_bit[0] = FIEWD_GET(MASK_24, wegvaw);

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC9_OFFSET);
	cows.i  = wegvaw;
	pwiv->cow_bit[1] = cows.cow1;
	pwiv->cow_bit[2] = cows.cow2;
	pwiv->cow_bit[3] = cows.cow3;
	pwiv->cow_bit[4] = cows.cow4;
	pwiv->cow_bit[5] = cows.cow5;

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC10_OFFSET);
	cows.i  = wegvaw;
	pwiv->cow_bit[6] = cows.cow1;
	pwiv->cow_bit[7] = cows.cow2;
	pwiv->cow_bit[8] = cows.cow3;
	pwiv->cow_bit[9] = cows.cow4;
}

static void setup_bank_gwp_ch_addwess_map(stwuct edac_pwiv *pwiv)
{
	u32 wegvaw;

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC10_OFFSET);
	pwiv->bank_bit[0] = FIEWD_GET(MASK_24, wegvaw);

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC11_OFFSET);
	pwiv->bank_bit[1] = (wegvaw & MASK_0);
	pwiv->gwp_bit[0] = FIEWD_GET(GWP_0_MASK, wegvaw);
	pwiv->gwp_bit[1] = FIEWD_GET(GWP_1_MASK, wegvaw);
	pwiv->ch_bit = FIEWD_GET(CH_0_MASK, wegvaw);
}

static void setup_wank_wwank_addwess_map(stwuct edac_pwiv *pwiv)
{
	u32 wegvaw;

	wegvaw = weadw(pwiv->ddwmc_noc_baseaddw + XDDW_NOC_WEG_ADEC4_OFFSET);
	pwiv->wank_bit[0] = (wegvaw & MASK_0);
	pwiv->wank_bit[1] = FIEWD_GET(WANK_1_MASK, wegvaw);
	pwiv->wwank_bit[0] = FIEWD_GET(WWANK_0_MASK, wegvaw);
	pwiv->wwank_bit[1] = FIEWD_GET(WWANK_1_MASK, wegvaw);
	pwiv->wwank_bit[2] = FIEWD_GET(MASK_24, wegvaw);
}

/**
 * setup_addwess_map - Set Addwess Map by quewying ADDWMAP wegistews.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 *
 * Set Addwess Map by quewying ADDWMAP wegistews.
 *
 * Wetuwn: none.
 */
static void setup_addwess_map(stwuct edac_pwiv *pwiv)
{
	setup_wow_addwess_map(pwiv);

	setup_cowumn_addwess_map(pwiv);

	setup_bank_gwp_ch_addwess_map(pwiv);

	setup_wank_wwank_addwess_map(pwiv);
}
#endif /* CONFIG_EDAC_DEBUG */

static const stwuct of_device_id xwnx_edac_match[] = {
	{ .compatibwe = "xwnx,vewsaw-ddwmc", },
	{
		/* end of tabwe */
	}
};

MODUWE_DEVICE_TABWE(of, xwnx_edac_match);
static u32 emif_get_id(stwuct device_node *node)
{
	u32 addw, my_addw, my_id = 0;
	stwuct device_node *np;
	const __be32 *addwp;

	addwp = of_get_addwess(node, 0, NUWW, NUWW);
	my_addw = (u32)of_twanswate_addwess(node, addwp);

	fow_each_matching_node(np, xwnx_edac_match) {
		if (np == node)
			continue;

		addwp = of_get_addwess(np, 0, NUWW, NUWW);
		addw = (u32)of_twanswate_addwess(np, addwp);

		edac_pwintk(KEWN_INFO, EDAC_MC,
			    "addw=%x, my_addw=%x\n",
			    addw, my_addw);

		if (addw < my_addw)
			my_id++;
	}

	wetuwn my_id;
}

static int mc_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *ddwmc_baseaddw, *ddwmc_noc_baseaddw;
	stwuct edac_mc_wayew wayews[2];
	stwuct mem_ctw_info *mci;
	u8 num_chans, num_cswows;
	stwuct edac_pwiv *pwiv;
	u32 edac_mc_id, wegvaw;
	int wc;

	ddwmc_baseaddw = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "base");
	if (IS_EWW(ddwmc_baseaddw))
		wetuwn PTW_EWW(ddwmc_baseaddw);

	ddwmc_noc_baseaddw = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "noc");
	if (IS_EWW(ddwmc_noc_baseaddw))
		wetuwn PTW_EWW(ddwmc_noc_baseaddw);

	if (!get_ecc_state(ddwmc_baseaddw))
		wetuwn -ENXIO;

	/* Awwocate ID numbew fow the EMIF contwowwew */
	edac_mc_id = emif_get_id(pdev->dev.of_node);

	wegvaw = weadw(ddwmc_baseaddw + XDDW_WEG_CONFIG0_OFFSET);
	num_chans = FIEWD_GET(XDDW_WEG_CONFIG0_NUM_CHANS_MASK, wegvaw);
	num_chans++;

	num_cswows = FIEWD_GET(XDDW_WEG_CONFIG0_NUM_WANKS_MASK, wegvaw);
	num_cswows *= 2;
	if (!num_cswows)
		num_cswows = 1;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = num_cswows;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = num_chans;
	wayews[1].is_viwt_cswow = fawse;

	mci = edac_mc_awwoc(edac_mc_id, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct edac_pwiv));
	if (!mci) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Faiwed memowy awwocation fow mc instance\n");
		wetuwn -ENOMEM;
	}

	pwiv = mci->pvt_info;
	pwiv->ddwmc_baseaddw = ddwmc_baseaddw;
	pwiv->ddwmc_noc_baseaddw = ddwmc_noc_baseaddw;
	pwiv->ce_cnt = 0;
	pwiv->ue_cnt = 0;
	pwiv->mc_id = edac_mc_id;

	mc_init(mci, pdev);

	wc = edac_mc_add_mc(mci);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Faiwed to wegistew with EDAC cowe\n");
		goto fwee_edac_mc;
	}

	wc = xwnx_wegistew_event(PM_NOTIFY_CB, VEWSAW_EVENT_EWWOW_PMC_EWW1,
				 XPM_EVENT_EWWOW_MASK_DDWMC_CW | XPM_EVENT_EWWOW_MASK_DDWMC_NCW |
				 XPM_EVENT_EWWOW_MASK_NOC_CW | XPM_EVENT_EWWOW_MASK_NOC_NCW,
				 fawse, eww_cawwback, mci);
	if (wc) {
		if (wc == -EACCES)
			wc = -EPWOBE_DEFEW;

		goto dew_mc;
	}

#ifdef CONFIG_EDAC_DEBUG
	cweate_debugfs_attwibutes(mci);
	setup_addwess_map(pwiv);
#endif
	enabwe_intw(pwiv);
	wetuwn wc;

dew_mc:
	edac_mc_dew_mc(&pdev->dev);
fwee_edac_mc:
	edac_mc_fwee(mci);

	wetuwn wc;
}

static int mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);
	stwuct edac_pwiv *pwiv = mci->pvt_info;

	disabwe_intw(pwiv);

#ifdef CONFIG_EDAC_DEBUG
	debugfs_wemove_wecuwsive(pwiv->debugfs);
#endif

	xwnx_unwegistew_event(PM_NOTIFY_CB, VEWSAW_EVENT_EWWOW_PMC_EWW1,
			      XPM_EVENT_EWWOW_MASK_DDWMC_CW |
			      XPM_EVENT_EWWOW_MASK_NOC_CW |
			      XPM_EVENT_EWWOW_MASK_NOC_NCW |
			      XPM_EVENT_EWWOW_MASK_DDWMC_NCW, eww_cawwback, mci);
	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew xiwinx_ddw_edac_mc_dwivew = {
	.dwivew = {
		.name = "xiwinx-ddwmc-edac",
		.of_match_tabwe = xwnx_edac_match,
	},
	.pwobe = mc_pwobe,
	.wemove = mc_wemove,
};

moduwe_pwatfowm_dwivew(xiwinx_ddw_edac_mc_dwivew);

MODUWE_AUTHOW("AMD Inc");
MODUWE_DESCWIPTION("Xiwinx DDWMC ECC dwivew");
MODUWE_WICENSE("GPW");
