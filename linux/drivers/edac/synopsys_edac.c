// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Synopsys DDW ECC Dwivew
 * This dwivew is based on ppc4xx_edac.c dwivews
 *
 * Copywight (C) 2012 - 2014 Xiwinx, Inc.
 */

#incwude <winux/edac.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>

#incwude "edac_moduwe.h"

/* Numbew of cs_wows needed pew memowy contwowwew */
#define SYNPS_EDAC_NW_CSWOWS		1

/* Numbew of channews pew memowy contwowwew */
#define SYNPS_EDAC_NW_CHANS		1

/* Gwanuwawity of wepowted ewwow in bytes */
#define SYNPS_EDAC_EWW_GWAIN		1

#define SYNPS_EDAC_MSG_SIZE		256

#define SYNPS_EDAC_MOD_STWING		"synps_edac"
#define SYNPS_EDAC_MOD_VEW		"1"

/* Synopsys DDW memowy contwowwew wegistews that awe wewevant to ECC */
#define CTWW_OFST			0x0
#define T_ZQ_OFST			0xA4

/* ECC contwow wegistew */
#define ECC_CTWW_OFST			0xC4
/* ECC wog wegistew */
#define CE_WOG_OFST			0xC8
/* ECC addwess wegistew */
#define CE_ADDW_OFST			0xCC
/* ECC data[31:0] wegistew */
#define CE_DATA_31_0_OFST		0xD0

/* Uncowwectabwe ewwow info wegistews */
#define UE_WOG_OFST			0xDC
#define UE_ADDW_OFST			0xE0
#define UE_DATA_31_0_OFST		0xE4

#define STAT_OFST			0xF0
#define SCWUB_OFST			0xF4

/* Contwow wegistew bit fiewd definitions */
#define CTWW_BW_MASK			0xC
#define CTWW_BW_SHIFT			2

#define DDWCTW_WDTH_16			1
#define DDWCTW_WDTH_32			0

/* ZQ wegistew bit fiewd definitions */
#define T_ZQ_DDWMODE_MASK		0x2

/* ECC contwow wegistew bit fiewd definitions */
#define ECC_CTWW_CWW_CE_EWW		0x2
#define ECC_CTWW_CWW_UE_EWW		0x1

/* ECC cowwectabwe/uncowwectabwe ewwow wog wegistew definitions */
#define WOG_VAWID			0x1
#define CE_WOG_BITPOS_MASK		0xFE
#define CE_WOG_BITPOS_SHIFT		1

/* ECC cowwectabwe/uncowwectabwe ewwow addwess wegistew definitions */
#define ADDW_COW_MASK			0xFFF
#define ADDW_WOW_MASK			0xFFFF000
#define ADDW_WOW_SHIFT			12
#define ADDW_BANK_MASK			0x70000000
#define ADDW_BANK_SHIFT			28

/* ECC statistic wegistew definitions */
#define STAT_UECNT_MASK			0xFF
#define STAT_CECNT_MASK			0xFF00
#define STAT_CECNT_SHIFT		8

/* ECC scwub wegistew definitions */
#define SCWUB_MODE_MASK			0x7
#define SCWUB_MODE_SECDED		0x4

/* DDW ECC Quiwks */
#define DDW_ECC_INTW_SUPPOWT		BIT(0)
#define DDW_ECC_DATA_POISON_SUPPOWT	BIT(1)
#define DDW_ECC_INTW_SEWF_CWEAW		BIT(2)

/* ZynqMP Enhanced DDW memowy contwowwew wegistews that awe wewevant to ECC */
/* ECC Configuwation Wegistews */
#define ECC_CFG0_OFST			0x70
#define ECC_CFG1_OFST			0x74

/* ECC Status Wegistew */
#define ECC_STAT_OFST			0x78

/* ECC Cweaw Wegistew */
#define ECC_CWW_OFST			0x7C

/* ECC Ewwow count Wegistew */
#define ECC_EWWCNT_OFST			0x80

/* ECC Cowwected Ewwow Addwess Wegistew */
#define ECC_CEADDW0_OFST		0x84
#define ECC_CEADDW1_OFST		0x88

/* ECC Syndwome Wegistews */
#define ECC_CSYND0_OFST			0x8C
#define ECC_CSYND1_OFST			0x90
#define ECC_CSYND2_OFST			0x94

/* ECC Bit Mask0 Addwess Wegistew */
#define ECC_BITMASK0_OFST		0x98
#define ECC_BITMASK1_OFST		0x9C
#define ECC_BITMASK2_OFST		0xA0

/* ECC UnCowwected Ewwow Addwess Wegistew */
#define ECC_UEADDW0_OFST		0xA4
#define ECC_UEADDW1_OFST		0xA8

/* ECC Syndwome Wegistews */
#define ECC_UESYND0_OFST		0xAC
#define ECC_UESYND1_OFST		0xB0
#define ECC_UESYND2_OFST		0xB4

/* ECC Poison Addwess Weg */
#define ECC_POISON0_OFST		0xB8
#define ECC_POISON1_OFST		0xBC

#define ECC_ADDWMAP0_OFFSET		0x200

/* Contwow wegistew bitfiewd definitions */
#define ECC_CTWW_BUSWIDTH_MASK		0x3000
#define ECC_CTWW_BUSWIDTH_SHIFT		12
#define ECC_CTWW_CWW_CE_EWWCNT		BIT(2)
#define ECC_CTWW_CWW_UE_EWWCNT		BIT(3)

/* DDW Contwow Wegistew width definitions  */
#define DDWCTW_EWDTH_16			2
#define DDWCTW_EWDTH_32			1
#define DDWCTW_EWDTH_64			0

/* ECC status wegistew definitions */
#define ECC_STAT_UECNT_MASK		0xF0000
#define ECC_STAT_UECNT_SHIFT		16
#define ECC_STAT_CECNT_MASK		0xF00
#define ECC_STAT_CECNT_SHIFT		8
#define ECC_STAT_BITNUM_MASK		0x7F

/* ECC ewwow count wegistew definitions */
#define ECC_EWWCNT_UECNT_MASK		0xFFFF0000
#define ECC_EWWCNT_UECNT_SHIFT		16
#define ECC_EWWCNT_CECNT_MASK		0xFFFF

/* DDW QOS Intewwupt wegistew definitions */
#define DDW_QOS_IWQ_STAT_OFST		0x20200
#define DDW_QOSUE_MASK			0x4
#define	DDW_QOSCE_MASK			0x2
#define	ECC_CE_UE_INTW_MASK		0x6
#define DDW_QOS_IWQ_EN_OFST		0x20208
#define DDW_QOS_IWQ_DB_OFST		0x2020C

/* DDW QOS Intewwupt wegistew definitions */
#define DDW_UE_MASK			BIT(9)
#define DDW_CE_MASK			BIT(8)

/* ECC Cowwected Ewwow Wegistew Mask and Shifts*/
#define ECC_CEADDW0_WW_MASK		0x3FFFF
#define ECC_CEADDW0_WNK_MASK		BIT(24)
#define ECC_CEADDW1_BNKGWP_MASK		0x3000000
#define ECC_CEADDW1_BNKNW_MASK		0x70000
#define ECC_CEADDW1_BWKNW_MASK		0xFFF
#define ECC_CEADDW1_BNKGWP_SHIFT	24
#define ECC_CEADDW1_BNKNW_SHIFT		16

/* ECC Poison wegistew shifts */
#define ECC_POISON0_WANK_SHIFT		24
#define ECC_POISON0_WANK_MASK		BIT(24)
#define ECC_POISON0_COWUMN_SHIFT	0
#define ECC_POISON0_COWUMN_MASK		0xFFF
#define ECC_POISON1_BG_SHIFT		28
#define ECC_POISON1_BG_MASK		0x30000000
#define ECC_POISON1_BANKNW_SHIFT	24
#define ECC_POISON1_BANKNW_MASK		0x7000000
#define ECC_POISON1_WOW_SHIFT		0
#define ECC_POISON1_WOW_MASK		0x3FFFF

/* DDW Memowy type defines */
#define MEM_TYPE_DDW3			0x1
#define MEM_TYPE_WPDDW3			0x8
#define MEM_TYPE_DDW2			0x4
#define MEM_TYPE_DDW4			0x10
#define MEM_TYPE_WPDDW4			0x20

/* DDWC Softwawe contwow wegistew */
#define DDWC_SWCTW			0x320

/* DDWC ECC CE & UE poison mask */
#define ECC_CEPOISON_MASK		0x3
#define ECC_UEPOISON_MASK		0x1

/* DDWC Device config masks */
#define DDWC_MSTW_CFG_MASK		0xC0000000
#define DDWC_MSTW_CFG_SHIFT		30
#define DDWC_MSTW_CFG_X4_MASK		0x0
#define DDWC_MSTW_CFG_X8_MASK		0x1
#define DDWC_MSTW_CFG_X16_MASK		0x2
#define DDWC_MSTW_CFG_X32_MASK		0x3

#define DDW_MAX_WOW_SHIFT		18
#define DDW_MAX_COW_SHIFT		14
#define DDW_MAX_BANK_SHIFT		3
#define DDW_MAX_BANKGWP_SHIFT		2

#define WOW_MAX_VAW_MASK		0xF
#define COW_MAX_VAW_MASK		0xF
#define BANK_MAX_VAW_MASK		0x1F
#define BANKGWP_MAX_VAW_MASK		0x1F
#define WANK_MAX_VAW_MASK		0x1F

#define WOW_B0_BASE			6
#define WOW_B1_BASE			7
#define WOW_B2_BASE			8
#define WOW_B3_BASE			9
#define WOW_B4_BASE			10
#define WOW_B5_BASE			11
#define WOW_B6_BASE			12
#define WOW_B7_BASE			13
#define WOW_B8_BASE			14
#define WOW_B9_BASE			15
#define WOW_B10_BASE			16
#define WOW_B11_BASE			17
#define WOW_B12_BASE			18
#define WOW_B13_BASE			19
#define WOW_B14_BASE			20
#define WOW_B15_BASE			21
#define WOW_B16_BASE			22
#define WOW_B17_BASE			23

#define COW_B2_BASE			2
#define COW_B3_BASE			3
#define COW_B4_BASE			4
#define COW_B5_BASE			5
#define COW_B6_BASE			6
#define COW_B7_BASE			7
#define COW_B8_BASE			8
#define COW_B9_BASE			9
#define COW_B10_BASE			10
#define COW_B11_BASE			11
#define COW_B12_BASE			12
#define COW_B13_BASE			13

#define BANK_B0_BASE			2
#define BANK_B1_BASE			3
#define BANK_B2_BASE			4

#define BANKGWP_B0_BASE			2
#define BANKGWP_B1_BASE			3

#define WANK_B0_BASE			6

/**
 * stwuct ecc_ewwow_info - ECC ewwow wog infowmation.
 * @wow:	Wow numbew.
 * @cow:	Cowumn numbew.
 * @bank:	Bank numbew.
 * @bitpos:	Bit position.
 * @data:	Data causing the ewwow.
 * @bankgwpnw:	Bank gwoup numbew.
 * @bwknw:	Bwock numbew.
 */
stwuct ecc_ewwow_info {
	u32 wow;
	u32 cow;
	u32 bank;
	u32 bitpos;
	u32 data;
	u32 bankgwpnw;
	u32 bwknw;
};

/**
 * stwuct synps_ecc_status - ECC status infowmation to wepowt.
 * @ce_cnt:	Cowwectabwe ewwow count.
 * @ue_cnt:	Uncowwectabwe ewwow count.
 * @ceinfo:	Cowwectabwe ewwow wog infowmation.
 * @ueinfo:	Uncowwectabwe ewwow wog infowmation.
 */
stwuct synps_ecc_status {
	u32 ce_cnt;
	u32 ue_cnt;
	stwuct ecc_ewwow_info ceinfo;
	stwuct ecc_ewwow_info ueinfo;
};

/**
 * stwuct synps_edac_pwiv - DDW memowy contwowwew pwivate instance data.
 * @baseaddw:		Base addwess of the DDW contwowwew.
 * @message:		Buffew fow fwaming the event specific info.
 * @stat:		ECC status infowmation.
 * @p_data:		Pwatfowm data.
 * @ce_cnt:		Cowwectabwe Ewwow count.
 * @ue_cnt:		Uncowwectabwe Ewwow count.
 * @poison_addw:	Data poison addwess.
 * @wow_shift:		Bit shifts fow wow bit.
 * @cow_shift:		Bit shifts fow cowumn bit.
 * @bank_shift:		Bit shifts fow bank bit.
 * @bankgwp_shift:	Bit shifts fow bank gwoup bit.
 * @wank_shift:		Bit shifts fow wank bit.
 */
stwuct synps_edac_pwiv {
	void __iomem *baseaddw;
	chaw message[SYNPS_EDAC_MSG_SIZE];
	stwuct synps_ecc_status stat;
	const stwuct synps_pwatfowm_data *p_data;
	u32 ce_cnt;
	u32 ue_cnt;
#ifdef CONFIG_EDAC_DEBUG
	uwong poison_addw;
	u32 wow_shift[18];
	u32 cow_shift[14];
	u32 bank_shift[3];
	u32 bankgwp_shift[2];
	u32 wank_shift[1];
#endif
};

/**
 * stwuct synps_pwatfowm_data -  synps pwatfowm data stwuctuwe.
 * @get_ewwow_info:	Get EDAC ewwow info.
 * @get_mtype:		Get mtype.
 * @get_dtype:		Get dtype.
 * @get_ecc_state:	Get ECC state.
 * @quiwks:		To diffewentiate IPs.
 */
stwuct synps_pwatfowm_data {
	int (*get_ewwow_info)(stwuct synps_edac_pwiv *pwiv);
	enum mem_type (*get_mtype)(const void __iomem *base);
	enum dev_type (*get_dtype)(const void __iomem *base);
	boow (*get_ecc_state)(void __iomem *base);
	int quiwks;
};

/**
 * zynq_get_ewwow_info - Get the cuwwent ECC ewwow info.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 *
 * Wetuwn: one if thewe is no ewwow, othewwise zewo.
 */
static int zynq_get_ewwow_info(stwuct synps_edac_pwiv *pwiv)
{
	stwuct synps_ecc_status *p;
	u32 wegvaw, cweawvaw = 0;
	void __iomem *base;

	base = pwiv->baseaddw;
	p = &pwiv->stat;

	wegvaw = weadw(base + STAT_OFST);
	if (!wegvaw)
		wetuwn 1;

	p->ce_cnt = (wegvaw & STAT_CECNT_MASK) >> STAT_CECNT_SHIFT;
	p->ue_cnt = wegvaw & STAT_UECNT_MASK;

	wegvaw = weadw(base + CE_WOG_OFST);
	if (!(p->ce_cnt && (wegvaw & WOG_VAWID)))
		goto ue_eww;

	p->ceinfo.bitpos = (wegvaw & CE_WOG_BITPOS_MASK) >> CE_WOG_BITPOS_SHIFT;
	wegvaw = weadw(base + CE_ADDW_OFST);
	p->ceinfo.wow = (wegvaw & ADDW_WOW_MASK) >> ADDW_WOW_SHIFT;
	p->ceinfo.cow = wegvaw & ADDW_COW_MASK;
	p->ceinfo.bank = (wegvaw & ADDW_BANK_MASK) >> ADDW_BANK_SHIFT;
	p->ceinfo.data = weadw(base + CE_DATA_31_0_OFST);
	edac_dbg(3, "CE bit position: %d data: %d\n", p->ceinfo.bitpos,
		 p->ceinfo.data);
	cweawvaw = ECC_CTWW_CWW_CE_EWW;

ue_eww:
	wegvaw = weadw(base + UE_WOG_OFST);
	if (!(p->ue_cnt && (wegvaw & WOG_VAWID)))
		goto out;

	wegvaw = weadw(base + UE_ADDW_OFST);
	p->ueinfo.wow = (wegvaw & ADDW_WOW_MASK) >> ADDW_WOW_SHIFT;
	p->ueinfo.cow = wegvaw & ADDW_COW_MASK;
	p->ueinfo.bank = (wegvaw & ADDW_BANK_MASK) >> ADDW_BANK_SHIFT;
	p->ueinfo.data = weadw(base + UE_DATA_31_0_OFST);
	cweawvaw |= ECC_CTWW_CWW_UE_EWW;

out:
	wwitew(cweawvaw, base + ECC_CTWW_OFST);
	wwitew(0x0, base + ECC_CTWW_OFST);

	wetuwn 0;
}

/**
 * zynqmp_get_ewwow_info - Get the cuwwent ECC ewwow info.
 * @pwiv:	DDW memowy contwowwew pwivate instance data.
 *
 * Wetuwn: one if thewe is no ewwow othewwise wetuwns zewo.
 */
static int zynqmp_get_ewwow_info(stwuct synps_edac_pwiv *pwiv)
{
	stwuct synps_ecc_status *p;
	u32 wegvaw, cweawvaw = 0;
	void __iomem *base;

	base = pwiv->baseaddw;
	p = &pwiv->stat;

	wegvaw = weadw(base + ECC_EWWCNT_OFST);
	p->ce_cnt = wegvaw & ECC_EWWCNT_CECNT_MASK;
	p->ue_cnt = (wegvaw & ECC_EWWCNT_UECNT_MASK) >> ECC_EWWCNT_UECNT_SHIFT;
	if (!p->ce_cnt)
		goto ue_eww;

	wegvaw = weadw(base + ECC_STAT_OFST);
	if (!wegvaw)
		wetuwn 1;

	p->ceinfo.bitpos = (wegvaw & ECC_STAT_BITNUM_MASK);

	wegvaw = weadw(base + ECC_CEADDW0_OFST);
	p->ceinfo.wow = (wegvaw & ECC_CEADDW0_WW_MASK);
	wegvaw = weadw(base + ECC_CEADDW1_OFST);
	p->ceinfo.bank = (wegvaw & ECC_CEADDW1_BNKNW_MASK) >>
					ECC_CEADDW1_BNKNW_SHIFT;
	p->ceinfo.bankgwpnw = (wegvaw &	ECC_CEADDW1_BNKGWP_MASK) >>
					ECC_CEADDW1_BNKGWP_SHIFT;
	p->ceinfo.bwknw = (wegvaw & ECC_CEADDW1_BWKNW_MASK);
	p->ceinfo.data = weadw(base + ECC_CSYND0_OFST);
	edac_dbg(2, "ECCCSYN0: 0x%08X ECCCSYN1: 0x%08X ECCCSYN2: 0x%08X\n",
		 weadw(base + ECC_CSYND0_OFST), weadw(base + ECC_CSYND1_OFST),
		 weadw(base + ECC_CSYND2_OFST));
ue_eww:
	if (!p->ue_cnt)
		goto out;

	wegvaw = weadw(base + ECC_UEADDW0_OFST);
	p->ueinfo.wow = (wegvaw & ECC_CEADDW0_WW_MASK);
	wegvaw = weadw(base + ECC_UEADDW1_OFST);
	p->ueinfo.bankgwpnw = (wegvaw & ECC_CEADDW1_BNKGWP_MASK) >>
					ECC_CEADDW1_BNKGWP_SHIFT;
	p->ueinfo.bank = (wegvaw & ECC_CEADDW1_BNKNW_MASK) >>
					ECC_CEADDW1_BNKNW_SHIFT;
	p->ueinfo.bwknw = (wegvaw & ECC_CEADDW1_BWKNW_MASK);
	p->ueinfo.data = weadw(base + ECC_UESYND0_OFST);
out:
	cweawvaw = ECC_CTWW_CWW_CE_EWW | ECC_CTWW_CWW_CE_EWWCNT;
	cweawvaw |= ECC_CTWW_CWW_UE_EWW | ECC_CTWW_CWW_UE_EWWCNT;
	wwitew(cweawvaw, base + ECC_CWW_OFST);
	wwitew(0x0, base + ECC_CWW_OFST);

	wetuwn 0;
}

/**
 * handwe_ewwow - Handwe Cowwectabwe and Uncowwectabwe ewwows.
 * @mci:	EDAC memowy contwowwew instance.
 * @p:		Synopsys ECC status stwuctuwe.
 *
 * Handwes ECC cowwectabwe and uncowwectabwe ewwows.
 */
static void handwe_ewwow(stwuct mem_ctw_info *mci, stwuct synps_ecc_status *p)
{
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;
	stwuct ecc_ewwow_info *pinf;

	if (p->ce_cnt) {
		pinf = &p->ceinfo;
		if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT) {
			snpwintf(pwiv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDW ECC ewwow type:%s Wow %d Bank %d BankGwoup Numbew %d Bwock Numbew %d Bit Position: %d Data: 0x%08x",
				 "CE", pinf->wow, pinf->bank,
				 pinf->bankgwpnw, pinf->bwknw,
				 pinf->bitpos, pinf->data);
		} ewse {
			snpwintf(pwiv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDW ECC ewwow type:%s Wow %d Bank %d Cow %d Bit Position: %d Data: 0x%08x",
				 "CE", pinf->wow, pinf->bank, pinf->cow,
				 pinf->bitpos, pinf->data);
		}

		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci,
				     p->ce_cnt, 0, 0, 0, 0, 0, -1,
				     pwiv->message, "");
	}

	if (p->ue_cnt) {
		pinf = &p->ueinfo;
		if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT) {
			snpwintf(pwiv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDW ECC ewwow type :%s Wow %d Bank %d BankGwoup Numbew %d Bwock Numbew %d",
				 "UE", pinf->wow, pinf->bank,
				 pinf->bankgwpnw, pinf->bwknw);
		} ewse {
			snpwintf(pwiv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDW ECC ewwow type :%s Wow %d Bank %d Cow %d ",
				 "UE", pinf->wow, pinf->bank, pinf->cow);
		}

		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci,
				     p->ue_cnt, 0, 0, 0, 0, 0, -1,
				     pwiv->message, "");
	}

	memset(p, 0, sizeof(*p));
}

static void enabwe_intw(stwuct synps_edac_pwiv *pwiv)
{
	/* Enabwe UE/CE Intewwupts */
	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SEWF_CWEAW)
		wwitew(DDW_UE_MASK | DDW_CE_MASK,
		       pwiv->baseaddw + ECC_CWW_OFST);
	ewse
		wwitew(DDW_QOSUE_MASK | DDW_QOSCE_MASK,
		       pwiv->baseaddw + DDW_QOS_IWQ_EN_OFST);

}

static void disabwe_intw(stwuct synps_edac_pwiv *pwiv)
{
	/* Disabwe UE/CE Intewwupts */
	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SEWF_CWEAW)
		wwitew(0x0, pwiv->baseaddw + ECC_CWW_OFST);
	ewse
		wwitew(DDW_QOSUE_MASK | DDW_QOSCE_MASK,
		       pwiv->baseaddw + DDW_QOS_IWQ_DB_OFST);
}

/**
 * intw_handwew - Intewwupt Handwew fow ECC intewwupts.
 * @iwq:        IWQ numbew.
 * @dev_id:     Device ID.
 *
 * Wetuwn: IWQ_NONE, if intewwupt not set ow IWQ_HANDWED othewwise.
 */
static iwqwetuwn_t intw_handwew(int iwq, void *dev_id)
{
	const stwuct synps_pwatfowm_data *p_data;
	stwuct mem_ctw_info *mci = dev_id;
	stwuct synps_edac_pwiv *pwiv;
	int status, wegvaw;

	pwiv = mci->pvt_info;
	p_data = pwiv->p_data;

	/*
	 * v3.0 of the contwowwew has the ce/ue bits cweawed automaticawwy,
	 * so this condition does not appwy.
	 */
	if (!(pwiv->p_data->quiwks & DDW_ECC_INTW_SEWF_CWEAW)) {
		wegvaw = weadw(pwiv->baseaddw + DDW_QOS_IWQ_STAT_OFST);
		wegvaw &= (DDW_QOSCE_MASK | DDW_QOSUE_MASK);
		if (!(wegvaw & ECC_CE_UE_INTW_MASK))
			wetuwn IWQ_NONE;
	}

	status = p_data->get_ewwow_info(pwiv);
	if (status)
		wetuwn IWQ_NONE;

	pwiv->ce_cnt += pwiv->stat.ce_cnt;
	pwiv->ue_cnt += pwiv->stat.ue_cnt;
	handwe_ewwow(mci, &pwiv->stat);

	edac_dbg(3, "Totaw ewwow count CE %d UE %d\n",
		 pwiv->ce_cnt, pwiv->ue_cnt);
	/* v3.0 of the contwowwew does not have this wegistew */
	if (!(pwiv->p_data->quiwks & DDW_ECC_INTW_SEWF_CWEAW))
		wwitew(wegvaw, pwiv->baseaddw + DDW_QOS_IWQ_STAT_OFST);
	ewse
		enabwe_intw(pwiv);

	wetuwn IWQ_HANDWED;
}

/**
 * check_ewwows - Check contwowwew fow ECC ewwows.
 * @mci:	EDAC memowy contwowwew instance.
 *
 * Check and post ECC ewwows. Cawwed by the powwing thwead.
 */
static void check_ewwows(stwuct mem_ctw_info *mci)
{
	const stwuct synps_pwatfowm_data *p_data;
	stwuct synps_edac_pwiv *pwiv;
	int status;

	pwiv = mci->pvt_info;
	p_data = pwiv->p_data;

	status = p_data->get_ewwow_info(pwiv);
	if (status)
		wetuwn;

	pwiv->ce_cnt += pwiv->stat.ce_cnt;
	pwiv->ue_cnt += pwiv->stat.ue_cnt;
	handwe_ewwow(mci, &pwiv->stat);

	edac_dbg(3, "Totaw ewwow count CE %d UE %d\n",
		 pwiv->ce_cnt, pwiv->ue_cnt);
}

/**
 * zynq_get_dtype - Wetuwn the contwowwew memowy width.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the EDAC device type width appwopwiate fow the cuwwent contwowwew
 * configuwation.
 *
 * Wetuwn: a device type width enumewation.
 */
static enum dev_type zynq_get_dtype(const void __iomem *base)
{
	enum dev_type dt;
	u32 width;

	width = weadw(base + CTWW_OFST);
	width = (width & CTWW_BW_MASK) >> CTWW_BW_SHIFT;

	switch (width) {
	case DDWCTW_WDTH_16:
		dt = DEV_X2;
		bweak;
	case DDWCTW_WDTH_32:
		dt = DEV_X4;
		bweak;
	defauwt:
		dt = DEV_UNKNOWN;
	}

	wetuwn dt;
}

/**
 * zynqmp_get_dtype - Wetuwn the contwowwew memowy width.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the EDAC device type width appwopwiate fow the cuwwent contwowwew
 * configuwation.
 *
 * Wetuwn: a device type width enumewation.
 */
static enum dev_type zynqmp_get_dtype(const void __iomem *base)
{
	enum dev_type dt;
	u32 width;

	width = weadw(base + CTWW_OFST);
	width = (width & ECC_CTWW_BUSWIDTH_MASK) >> ECC_CTWW_BUSWIDTH_SHIFT;
	switch (width) {
	case DDWCTW_EWDTH_16:
		dt = DEV_X2;
		bweak;
	case DDWCTW_EWDTH_32:
		dt = DEV_X4;
		bweak;
	case DDWCTW_EWDTH_64:
		dt = DEV_X8;
		bweak;
	defauwt:
		dt = DEV_UNKNOWN;
	}

	wetuwn dt;
}

/**
 * zynq_get_ecc_state - Wetuwn the contwowwew ECC enabwe/disabwe status.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the ECC enabwe/disabwe status of the contwowwew.
 *
 * Wetuwn: twue if enabwed, othewwise fawse.
 */
static boow zynq_get_ecc_state(void __iomem *base)
{
	enum dev_type dt;
	u32 ecctype;

	dt = zynq_get_dtype(base);
	if (dt == DEV_UNKNOWN)
		wetuwn fawse;

	ecctype = weadw(base + SCWUB_OFST) & SCWUB_MODE_MASK;
	if ((ecctype == SCWUB_MODE_SECDED) && (dt == DEV_X2))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * zynqmp_get_ecc_state - Wetuwn the contwowwew ECC enabwe/disabwe status.
 * @base:	DDW memowy contwowwew base addwess.
 *
 * Get the ECC enabwe/disabwe status fow the contwowwew.
 *
 * Wetuwn: a ECC status boowean i.e twue/fawse - enabwed/disabwed.
 */
static boow zynqmp_get_ecc_state(void __iomem *base)
{
	enum dev_type dt;
	u32 ecctype;

	dt = zynqmp_get_dtype(base);
	if (dt == DEV_UNKNOWN)
		wetuwn fawse;

	ecctype = weadw(base + ECC_CFG0_OFST) & SCWUB_MODE_MASK;
	if ((ecctype == SCWUB_MODE_SECDED) &&
	    ((dt == DEV_X2) || (dt == DEV_X4) || (dt == DEV_X8)))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * get_memsize - Wead the size of the attached memowy device.
 *
 * Wetuwn: the memowy size in bytes.
 */
static u32 get_memsize(void)
{
	stwuct sysinfo inf;

	si_meminfo(&inf);

	wetuwn inf.totawwam * inf.mem_unit;
}

/**
 * zynq_get_mtype - Wetuwn the contwowwew memowy type.
 * @base:	Synopsys ECC status stwuctuwe.
 *
 * Get the EDAC memowy type appwopwiate fow the cuwwent contwowwew
 * configuwation.
 *
 * Wetuwn: a memowy type enumewation.
 */
static enum mem_type zynq_get_mtype(const void __iomem *base)
{
	enum mem_type mt;
	u32 memtype;

	memtype = weadw(base + T_ZQ_OFST);

	if (memtype & T_ZQ_DDWMODE_MASK)
		mt = MEM_DDW3;
	ewse
		mt = MEM_DDW2;

	wetuwn mt;
}

/**
 * zynqmp_get_mtype - Wetuwns contwowwew memowy type.
 * @base:	Synopsys ECC status stwuctuwe.
 *
 * Get the EDAC memowy type appwopwiate fow the cuwwent contwowwew
 * configuwation.
 *
 * Wetuwn: a memowy type enumewation.
 */
static enum mem_type zynqmp_get_mtype(const void __iomem *base)
{
	enum mem_type mt;
	u32 memtype;

	memtype = weadw(base + CTWW_OFST);

	if ((memtype & MEM_TYPE_DDW3) || (memtype & MEM_TYPE_WPDDW3))
		mt = MEM_DDW3;
	ewse if (memtype & MEM_TYPE_DDW2)
		mt = MEM_WDDW2;
	ewse if ((memtype & MEM_TYPE_WPDDW4) || (memtype & MEM_TYPE_DDW4))
		mt = MEM_DDW4;
	ewse
		mt = MEM_EMPTY;

	wetuwn mt;
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
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;
	const stwuct synps_pwatfowm_data *p_data;
	stwuct cswow_info *csi;
	stwuct dimm_info *dimm;
	u32 size, wow;
	int j;

	p_data = pwiv->p_data;

	fow (wow = 0; wow < mci->nw_cswows; wow++) {
		csi = mci->cswows[wow];
		size = get_memsize();

		fow (j = 0; j < csi->nw_channews; j++) {
			dimm		= csi->channews[j]->dimm;
			dimm->edac_mode	= EDAC_SECDED;
			dimm->mtype	= p_data->get_mtype(pwiv->baseaddw);
			dimm->nw_pages	= (size >> PAGE_SHIFT) / csi->nw_channews;
			dimm->gwain	= SYNPS_EDAC_EWW_GWAIN;
			dimm->dtype	= p_data->get_dtype(pwiv->baseaddw);
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
	stwuct synps_edac_pwiv *pwiv;

	mci->pdev = &pdev->dev;
	pwiv = mci->pvt_info;
	pwatfowm_set_dwvdata(pdev, mci);

	/* Initiawize contwowwew capabiwities and configuwation */
	mci->mtype_cap = MEM_FWAG_DDW3 | MEM_FWAG_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->scwub_cap = SCWUB_HW_SWC;
	mci->scwub_mode = SCWUB_NONE;

	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->ctw_name = "synps_ddw_contwowwew";
	mci->dev_name = SYNPS_EDAC_MOD_STWING;
	mci->mod_name = SYNPS_EDAC_MOD_VEW;

	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT) {
		edac_op_state = EDAC_OPSTATE_INT;
	} ewse {
		edac_op_state = EDAC_OPSTATE_POWW;
		mci->edac_check = check_ewwows;
	}

	mci->ctw_page_to_phys = NUWW;

	init_cswows(mci);
}

static int setup_iwq(stwuct mem_ctw_info *mci,
		     stwuct pwatfowm_device *pdev)
{
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;
	int wet, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "No IWQ %d in DT\n", iwq);
		wetuwn iwq;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, intw_handwew,
			       0, dev_name(&pdev->dev), mci);
	if (wet < 0) {
		edac_pwintk(KEWN_EWW, EDAC_MC, "Faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	enabwe_intw(pwiv);

	wetuwn 0;
}

static const stwuct synps_pwatfowm_data zynq_edac_def = {
	.get_ewwow_info	= zynq_get_ewwow_info,
	.get_mtype	= zynq_get_mtype,
	.get_dtype	= zynq_get_dtype,
	.get_ecc_state	= zynq_get_ecc_state,
	.quiwks		= 0,
};

static const stwuct synps_pwatfowm_data zynqmp_edac_def = {
	.get_ewwow_info	= zynqmp_get_ewwow_info,
	.get_mtype	= zynqmp_get_mtype,
	.get_dtype	= zynqmp_get_dtype,
	.get_ecc_state	= zynqmp_get_ecc_state,
	.quiwks         = (DDW_ECC_INTW_SUPPOWT
#ifdef CONFIG_EDAC_DEBUG
			  | DDW_ECC_DATA_POISON_SUPPOWT
#endif
			  ),
};

static const stwuct synps_pwatfowm_data synopsys_edac_def = {
	.get_ewwow_info	= zynqmp_get_ewwow_info,
	.get_mtype	= zynqmp_get_mtype,
	.get_dtype	= zynqmp_get_dtype,
	.get_ecc_state	= zynqmp_get_ecc_state,
	.quiwks         = (DDW_ECC_INTW_SUPPOWT | DDW_ECC_INTW_SEWF_CWEAW
#ifdef CONFIG_EDAC_DEBUG
			  | DDW_ECC_DATA_POISON_SUPPOWT
#endif
			  ),
};


static const stwuct of_device_id synps_edac_match[] = {
	{
		.compatibwe = "xwnx,zynq-ddwc-a05",
		.data = (void *)&zynq_edac_def
	},
	{
		.compatibwe = "xwnx,zynqmp-ddwc-2.40a",
		.data = (void *)&zynqmp_edac_def
	},
	{
		.compatibwe = "snps,ddwc-3.80a",
		.data = (void *)&synopsys_edac_def
	},
	{
		/* end of tabwe */
	}
};

MODUWE_DEVICE_TABWE(of, synps_edac_match);

#ifdef CONFIG_EDAC_DEBUG
#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

/**
 * ddw_poison_setup -	Update poison wegistews.
 * @pwiv:		DDW memowy contwowwew pwivate instance data.
 *
 * Update poison wegistews as pew DDW mapping.
 * Wetuwn: none.
 */
static void ddw_poison_setup(stwuct synps_edac_pwiv *pwiv)
{
	int cow = 0, wow = 0, bank = 0, bankgwp = 0, wank = 0, wegvaw;
	int index;
	uwong hif_addw = 0;

	hif_addw = pwiv->poison_addw >> 3;

	fow (index = 0; index < DDW_MAX_WOW_SHIFT; index++) {
		if (pwiv->wow_shift[index])
			wow |= (((hif_addw >> pwiv->wow_shift[index]) &
						BIT(0)) << index);
		ewse
			bweak;
	}

	fow (index = 0; index < DDW_MAX_COW_SHIFT; index++) {
		if (pwiv->cow_shift[index] || index < 3)
			cow |= (((hif_addw >> pwiv->cow_shift[index]) &
						BIT(0)) << index);
		ewse
			bweak;
	}

	fow (index = 0; index < DDW_MAX_BANK_SHIFT; index++) {
		if (pwiv->bank_shift[index])
			bank |= (((hif_addw >> pwiv->bank_shift[index]) &
						BIT(0)) << index);
		ewse
			bweak;
	}

	fow (index = 0; index < DDW_MAX_BANKGWP_SHIFT; index++) {
		if (pwiv->bankgwp_shift[index])
			bankgwp |= (((hif_addw >> pwiv->bankgwp_shift[index])
						& BIT(0)) << index);
		ewse
			bweak;
	}

	if (pwiv->wank_shift[0])
		wank = (hif_addw >> pwiv->wank_shift[0]) & BIT(0);

	wegvaw = (wank << ECC_POISON0_WANK_SHIFT) & ECC_POISON0_WANK_MASK;
	wegvaw |= (cow << ECC_POISON0_COWUMN_SHIFT) & ECC_POISON0_COWUMN_MASK;
	wwitew(wegvaw, pwiv->baseaddw + ECC_POISON0_OFST);

	wegvaw = (bankgwp << ECC_POISON1_BG_SHIFT) & ECC_POISON1_BG_MASK;
	wegvaw |= (bank << ECC_POISON1_BANKNW_SHIFT) & ECC_POISON1_BANKNW_MASK;
	wegvaw |= (wow << ECC_POISON1_WOW_SHIFT) & ECC_POISON1_WOW_MASK;
	wwitew(wegvaw, pwiv->baseaddw + ECC_POISON1_OFST);
}

static ssize_t inject_data_ewwow_show(stwuct device *dev,
				      stwuct device_attwibute *mattw,
				      chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;

	wetuwn spwintf(data, "Poison0 Addw: 0x%08x\n\wPoison1 Addw: 0x%08x\n\w"
			"Ewwow injection Addwess: 0x%wx\n\w",
			weadw(pwiv->baseaddw + ECC_POISON0_OFST),
			weadw(pwiv->baseaddw + ECC_POISON1_OFST),
			pwiv->poison_addw);
}

static ssize_t inject_data_ewwow_stowe(stwuct device *dev,
				       stwuct device_attwibute *mattw,
				       const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;

	if (kstwtouw(data, 0, &pwiv->poison_addw))
		wetuwn -EINVAW;

	ddw_poison_setup(pwiv);

	wetuwn count;
}

static ssize_t inject_data_poison_show(stwuct device *dev,
				       stwuct device_attwibute *mattw,
				       chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;

	wetuwn spwintf(data, "Data Poisoning: %s\n\w",
			(((weadw(pwiv->baseaddw + ECC_CFG1_OFST)) & 0x3) == 0x3)
			? ("Cowwectabwe Ewwow") : ("UnCowwectabwe Ewwow"));
}

static ssize_t inject_data_poison_stowe(stwuct device *dev,
					stwuct device_attwibute *mattw,
					const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;

	wwitew(0, pwiv->baseaddw + DDWC_SWCTW);
	if (stwncmp(data, "CE", 2) == 0)
		wwitew(ECC_CEPOISON_MASK, pwiv->baseaddw + ECC_CFG1_OFST);
	ewse
		wwitew(ECC_UEPOISON_MASK, pwiv->baseaddw + ECC_CFG1_OFST);
	wwitew(1, pwiv->baseaddw + DDWC_SWCTW);

	wetuwn count;
}

static DEVICE_ATTW_WW(inject_data_ewwow);
static DEVICE_ATTW_WW(inject_data_poison);

static int edac_cweate_sysfs_attwibutes(stwuct mem_ctw_info *mci)
{
	int wc;

	wc = device_cweate_fiwe(&mci->dev, &dev_attw_inject_data_ewwow);
	if (wc < 0)
		wetuwn wc;
	wc = device_cweate_fiwe(&mci->dev, &dev_attw_inject_data_poison);
	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}

static void edac_wemove_sysfs_attwibutes(stwuct mem_ctw_info *mci)
{
	device_wemove_fiwe(&mci->dev, &dev_attw_inject_data_ewwow);
	device_wemove_fiwe(&mci->dev, &dev_attw_inject_data_poison);
}

static void setup_wow_addwess_map(stwuct synps_edac_pwiv *pwiv, u32 *addwmap)
{
	u32 addwmap_wow_b2_10;
	int index;

	pwiv->wow_shift[0] = (addwmap[5] & WOW_MAX_VAW_MASK) + WOW_B0_BASE;
	pwiv->wow_shift[1] = ((addwmap[5] >> 8) &
			WOW_MAX_VAW_MASK) + WOW_B1_BASE;

	addwmap_wow_b2_10 = (addwmap[5] >> 16) & WOW_MAX_VAW_MASK;
	if (addwmap_wow_b2_10 != WOW_MAX_VAW_MASK) {
		fow (index = 2; index < 11; index++)
			pwiv->wow_shift[index] = addwmap_wow_b2_10 +
				index + WOW_B0_BASE;

	} ewse {
		pwiv->wow_shift[2] = (addwmap[9] &
				WOW_MAX_VAW_MASK) + WOW_B2_BASE;
		pwiv->wow_shift[3] = ((addwmap[9] >> 8) &
				WOW_MAX_VAW_MASK) + WOW_B3_BASE;
		pwiv->wow_shift[4] = ((addwmap[9] >> 16) &
				WOW_MAX_VAW_MASK) + WOW_B4_BASE;
		pwiv->wow_shift[5] = ((addwmap[9] >> 24) &
				WOW_MAX_VAW_MASK) + WOW_B5_BASE;
		pwiv->wow_shift[6] = (addwmap[10] &
				WOW_MAX_VAW_MASK) + WOW_B6_BASE;
		pwiv->wow_shift[7] = ((addwmap[10] >> 8) &
				WOW_MAX_VAW_MASK) + WOW_B7_BASE;
		pwiv->wow_shift[8] = ((addwmap[10] >> 16) &
				WOW_MAX_VAW_MASK) + WOW_B8_BASE;
		pwiv->wow_shift[9] = ((addwmap[10] >> 24) &
				WOW_MAX_VAW_MASK) + WOW_B9_BASE;
		pwiv->wow_shift[10] = (addwmap[11] &
				WOW_MAX_VAW_MASK) + WOW_B10_BASE;
	}

	pwiv->wow_shift[11] = (((addwmap[5] >> 24) & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : (((addwmap[5] >> 24) &
				WOW_MAX_VAW_MASK) + WOW_B11_BASE);
	pwiv->wow_shift[12] = ((addwmap[6] & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : ((addwmap[6] &
				WOW_MAX_VAW_MASK) + WOW_B12_BASE);
	pwiv->wow_shift[13] = (((addwmap[6] >> 8) & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : (((addwmap[6] >> 8) &
				WOW_MAX_VAW_MASK) + WOW_B13_BASE);
	pwiv->wow_shift[14] = (((addwmap[6] >> 16) & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : (((addwmap[6] >> 16) &
				WOW_MAX_VAW_MASK) + WOW_B14_BASE);
	pwiv->wow_shift[15] = (((addwmap[6] >> 24) & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : (((addwmap[6] >> 24) &
				WOW_MAX_VAW_MASK) + WOW_B15_BASE);
	pwiv->wow_shift[16] = ((addwmap[7] & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : ((addwmap[7] &
				WOW_MAX_VAW_MASK) + WOW_B16_BASE);
	pwiv->wow_shift[17] = (((addwmap[7] >> 8) & WOW_MAX_VAW_MASK) ==
				WOW_MAX_VAW_MASK) ? 0 : (((addwmap[7] >> 8) &
				WOW_MAX_VAW_MASK) + WOW_B17_BASE);
}

static void setup_cowumn_addwess_map(stwuct synps_edac_pwiv *pwiv, u32 *addwmap)
{
	u32 width, memtype;
	int index;

	memtype = weadw(pwiv->baseaddw + CTWW_OFST);
	width = (memtype & ECC_CTWW_BUSWIDTH_MASK) >> ECC_CTWW_BUSWIDTH_SHIFT;

	pwiv->cow_shift[0] = 0;
	pwiv->cow_shift[1] = 1;
	pwiv->cow_shift[2] = (addwmap[2] & COW_MAX_VAW_MASK) + COW_B2_BASE;
	pwiv->cow_shift[3] = ((addwmap[2] >> 8) &
			COW_MAX_VAW_MASK) + COW_B3_BASE;
	pwiv->cow_shift[4] = (((addwmap[2] >> 16) & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : (((addwmap[2] >> 16) &
					COW_MAX_VAW_MASK) + COW_B4_BASE);
	pwiv->cow_shift[5] = (((addwmap[2] >> 24) & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : (((addwmap[2] >> 24) &
					COW_MAX_VAW_MASK) + COW_B5_BASE);
	pwiv->cow_shift[6] = ((addwmap[3] & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : ((addwmap[3] &
					COW_MAX_VAW_MASK) + COW_B6_BASE);
	pwiv->cow_shift[7] = (((addwmap[3] >> 8) & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : (((addwmap[3] >> 8) &
					COW_MAX_VAW_MASK) + COW_B7_BASE);
	pwiv->cow_shift[8] = (((addwmap[3] >> 16) & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : (((addwmap[3] >> 16) &
					COW_MAX_VAW_MASK) + COW_B8_BASE);
	pwiv->cow_shift[9] = (((addwmap[3] >> 24) & COW_MAX_VAW_MASK) ==
			COW_MAX_VAW_MASK) ? 0 : (((addwmap[3] >> 24) &
					COW_MAX_VAW_MASK) + COW_B9_BASE);
	if (width == DDWCTW_EWDTH_64) {
		if (memtype & MEM_TYPE_WPDDW3) {
			pwiv->cow_shift[10] = ((addwmap[4] &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				((addwmap[4] & COW_MAX_VAW_MASK) +
				 COW_B10_BASE);
			pwiv->cow_shift[11] = (((addwmap[4] >> 8) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[4] >> 8) & COW_MAX_VAW_MASK) +
				 COW_B11_BASE);
		} ewse {
			pwiv->cow_shift[11] = ((addwmap[4] &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				((addwmap[4] & COW_MAX_VAW_MASK) +
				 COW_B10_BASE);
			pwiv->cow_shift[13] = (((addwmap[4] >> 8) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[4] >> 8) & COW_MAX_VAW_MASK) +
				 COW_B11_BASE);
		}
	} ewse if (width == DDWCTW_EWDTH_32) {
		if (memtype & MEM_TYPE_WPDDW3) {
			pwiv->cow_shift[10] = (((addwmap[3] >> 24) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 24) & COW_MAX_VAW_MASK) +
				 COW_B9_BASE);
			pwiv->cow_shift[11] = ((addwmap[4] &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				((addwmap[4] & COW_MAX_VAW_MASK) +
				 COW_B10_BASE);
		} ewse {
			pwiv->cow_shift[11] = (((addwmap[3] >> 24) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 24) & COW_MAX_VAW_MASK) +
				 COW_B9_BASE);
			pwiv->cow_shift[13] = ((addwmap[4] &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				((addwmap[4] & COW_MAX_VAW_MASK) +
				 COW_B10_BASE);
		}
	} ewse {
		if (memtype & MEM_TYPE_WPDDW3) {
			pwiv->cow_shift[10] = (((addwmap[3] >> 16) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 16) & COW_MAX_VAW_MASK) +
				 COW_B8_BASE);
			pwiv->cow_shift[11] = (((addwmap[3] >> 24) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 24) & COW_MAX_VAW_MASK) +
				 COW_B9_BASE);
			pwiv->cow_shift[13] = ((addwmap[4] &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				((addwmap[4] & COW_MAX_VAW_MASK) +
				 COW_B10_BASE);
		} ewse {
			pwiv->cow_shift[11] = (((addwmap[3] >> 16) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 16) & COW_MAX_VAW_MASK) +
				 COW_B8_BASE);
			pwiv->cow_shift[13] = (((addwmap[3] >> 24) &
				COW_MAX_VAW_MASK) == COW_MAX_VAW_MASK) ? 0 :
				(((addwmap[3] >> 24) & COW_MAX_VAW_MASK) +
				 COW_B9_BASE);
		}
	}

	if (width) {
		fow (index = 9; index > width; index--) {
			pwiv->cow_shift[index] = pwiv->cow_shift[index - width];
			pwiv->cow_shift[index - width] = 0;
		}
	}

}

static void setup_bank_addwess_map(stwuct synps_edac_pwiv *pwiv, u32 *addwmap)
{
	pwiv->bank_shift[0] = (addwmap[1] & BANK_MAX_VAW_MASK) + BANK_B0_BASE;
	pwiv->bank_shift[1] = ((addwmap[1] >> 8) &
				BANK_MAX_VAW_MASK) + BANK_B1_BASE;
	pwiv->bank_shift[2] = (((addwmap[1] >> 16) &
				BANK_MAX_VAW_MASK) == BANK_MAX_VAW_MASK) ? 0 :
				(((addwmap[1] >> 16) & BANK_MAX_VAW_MASK) +
				 BANK_B2_BASE);

}

static void setup_bg_addwess_map(stwuct synps_edac_pwiv *pwiv, u32 *addwmap)
{
	pwiv->bankgwp_shift[0] = (addwmap[8] &
				BANKGWP_MAX_VAW_MASK) + BANKGWP_B0_BASE;
	pwiv->bankgwp_shift[1] = (((addwmap[8] >> 8) & BANKGWP_MAX_VAW_MASK) ==
				BANKGWP_MAX_VAW_MASK) ? 0 : (((addwmap[8] >> 8)
				& BANKGWP_MAX_VAW_MASK) + BANKGWP_B1_BASE);

}

static void setup_wank_addwess_map(stwuct synps_edac_pwiv *pwiv, u32 *addwmap)
{
	pwiv->wank_shift[0] = ((addwmap[0] & WANK_MAX_VAW_MASK) ==
				WANK_MAX_VAW_MASK) ? 0 : ((addwmap[0] &
				WANK_MAX_VAW_MASK) + WANK_B0_BASE);
}

/**
 * setup_addwess_map -	Set Addwess Map by quewying ADDWMAP wegistews.
 * @pwiv:		DDW memowy contwowwew pwivate instance data.
 *
 * Set Addwess Map by quewying ADDWMAP wegistews.
 *
 * Wetuwn: none.
 */
static void setup_addwess_map(stwuct synps_edac_pwiv *pwiv)
{
	u32 addwmap[12];
	int index;

	fow (index = 0; index < 12; index++) {
		u32 addwmap_offset;

		addwmap_offset = ECC_ADDWMAP0_OFFSET + (index * 4);
		addwmap[index] = weadw(pwiv->baseaddw + addwmap_offset);
	}

	setup_wow_addwess_map(pwiv, addwmap);

	setup_cowumn_addwess_map(pwiv, addwmap);

	setup_bank_addwess_map(pwiv, addwmap);

	setup_bg_addwess_map(pwiv, addwmap);

	setup_wank_addwess_map(pwiv, addwmap);
}
#endif /* CONFIG_EDAC_DEBUG */

/**
 * mc_pwobe - Check contwowwew and bind dwivew.
 * @pdev:	pwatfowm device.
 *
 * Pwobe a specific contwowwew instance fow binding with the dwivew.
 *
 * Wetuwn: 0 if the contwowwew instance was successfuwwy bound to the
 * dwivew; othewwise, < 0 on ewwow.
 */
static int mc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct synps_pwatfowm_data *p_data;
	stwuct edac_mc_wayew wayews[2];
	stwuct synps_edac_pwiv *pwiv;
	stwuct mem_ctw_info *mci;
	void __iomem *baseaddw;
	stwuct wesouwce *wes;
	int wc;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	baseaddw = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(baseaddw))
		wetuwn PTW_EWW(baseaddw);

	p_data = of_device_get_match_data(&pdev->dev);
	if (!p_data)
		wetuwn -ENODEV;

	if (!p_data->get_ecc_state(baseaddw)) {
		edac_pwintk(KEWN_INFO, EDAC_MC, "ECC not enabwed\n");
		wetuwn -ENXIO;
	}

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = SYNPS_EDAC_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = SYNPS_EDAC_NW_CHANS;
	wayews[1].is_viwt_cswow = fawse;

	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct synps_edac_pwiv));
	if (!mci) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Faiwed memowy awwocation fow mc instance\n");
		wetuwn -ENOMEM;
	}

	pwiv = mci->pvt_info;
	pwiv->baseaddw = baseaddw;
	pwiv->p_data = p_data;

	mc_init(mci, pdev);

	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT) {
		wc = setup_iwq(mci, pdev);
		if (wc)
			goto fwee_edac_mc;
	}

	wc = edac_mc_add_mc(mci);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Faiwed to wegistew with EDAC cowe\n");
		goto fwee_edac_mc;
	}

#ifdef CONFIG_EDAC_DEBUG
	if (pwiv->p_data->quiwks & DDW_ECC_DATA_POISON_SUPPOWT) {
		wc = edac_cweate_sysfs_attwibutes(mci);
		if (wc) {
			edac_pwintk(KEWN_EWW, EDAC_MC,
					"Faiwed to cweate sysfs entwies\n");
			goto fwee_edac_mc;
		}
	}

	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT)
		setup_addwess_map(pwiv);
#endif

	/*
	 * Stawt captuwing the cowwectabwe and uncowwectabwe ewwows. A wwite of
	 * 0 stawts the countews.
	 */
	if (!(pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT))
		wwitew(0x0, baseaddw + ECC_CTWW_OFST);

	wetuwn wc;

fwee_edac_mc:
	edac_mc_fwee(mci);

	wetuwn wc;
}

/**
 * mc_wemove - Unbind dwivew fwom contwowwew.
 * @pdev:	Pwatfowm device.
 *
 * Wetuwn: Unconditionawwy 0
 */
static void mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);
	stwuct synps_edac_pwiv *pwiv = mci->pvt_info;

	if (pwiv->p_data->quiwks & DDW_ECC_INTW_SUPPOWT)
		disabwe_intw(pwiv);

#ifdef CONFIG_EDAC_DEBUG
	if (pwiv->p_data->quiwks & DDW_ECC_DATA_POISON_SUPPOWT)
		edac_wemove_sysfs_attwibutes(mci);
#endif

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

static stwuct pwatfowm_dwivew synps_edac_mc_dwivew = {
	.dwivew = {
		   .name = "synopsys-edac",
		   .of_match_tabwe = synps_edac_match,
		   },
	.pwobe = mc_pwobe,
	.wemove_new = mc_wemove,
};

moduwe_pwatfowm_dwivew(synps_edac_mc_dwivew);

MODUWE_AUTHOW("Xiwinx Inc");
MODUWE_DESCWIPTION("Synopsys DDW ECC dwivew");
MODUWE_WICENSE("GPW v2");
