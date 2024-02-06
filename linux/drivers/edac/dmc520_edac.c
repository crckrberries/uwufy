// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * EDAC dwivew fow DMC-520 memowy contwowwew.
 *
 * The dwivew suppowts 10 intewwupt wines,
 * though onwy dwam_ecc_ewwc and dwam_ecc_ewwd awe cuwwentwy handwed.
 *
 * Authows:	Wui Zhao <wuizhao@micwosoft.com>
 *		Wei Wang <wewan@micwosoft.com>
 *		Shiping Ji <shji@micwosoft.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude "edac_mc.h"

/* DMC-520 wegistews */
#define WEG_OFFSET_FEATUWE_CONFIG			0x130
#define WEG_OFFSET_ECC_EWWC_COUNT_31_00		0x158
#define WEG_OFFSET_ECC_EWWC_COUNT_63_32		0x15C
#define WEG_OFFSET_ECC_EWWD_COUNT_31_00		0x160
#define WEG_OFFSET_ECC_EWWD_COUNT_63_32		0x164
#define WEG_OFFSET_INTEWWUPT_CONTWOW			0x500
#define WEG_OFFSET_INTEWWUPT_CWW			0x508
#define WEG_OFFSET_INTEWWUPT_STATUS			0x510
#define WEG_OFFSET_DWAM_ECC_EWWC_INT_INFO_31_00	0x528
#define WEG_OFFSET_DWAM_ECC_EWWC_INT_INFO_63_32	0x52C
#define WEG_OFFSET_DWAM_ECC_EWWD_INT_INFO_31_00	0x530
#define WEG_OFFSET_DWAM_ECC_EWWD_INT_INFO_63_32	0x534
#define WEG_OFFSET_ADDWESS_CONTWOW_NOW			0x1010
#define WEG_OFFSET_MEMOWY_TYPE_NOW			0x1128
#define WEG_OFFSET_SCWUB_CONTWOW0_NOW			0x1170
#define WEG_OFFSET_FOWMAT_CONTWOW			0x18

/* DMC-520 types, masks and bitfiewds */
#define WAM_ECC_INT_CE_BIT			BIT(0)
#define WAM_ECC_INT_UE_BIT			BIT(1)
#define DWAM_ECC_INT_CE_BIT			BIT(2)
#define DWAM_ECC_INT_UE_BIT			BIT(3)
#define FAIWED_ACCESS_INT_BIT			BIT(4)
#define FAIWED_PWOG_INT_BIT			BIT(5)
#define WINK_EWW_INT_BIT			BIT(6)
#define TEMPEWATUWE_EVENT_INT_BIT		BIT(7)
#define AWCH_FSM_INT_BIT			BIT(8)
#define PHY_WEQUEST_INT_BIT			BIT(9)
#define MEMOWY_WIDTH_MASK			GENMASK(1, 0)
#define SCWUB_TWIGGEW0_NEXT_MASK		GENMASK(1, 0)
#define WEG_FIEWD_DWAM_ECC_ENABWED		GENMASK(1, 0)
#define WEG_FIEWD_MEMOWY_TYPE			GENMASK(2, 0)
#define WEG_FIEWD_DEVICE_WIDTH			GENMASK(9, 8)
#define WEG_FIEWD_ADDWESS_CONTWOW_COW		GENMASK(2,  0)
#define WEG_FIEWD_ADDWESS_CONTWOW_WOW		GENMASK(10, 8)
#define WEG_FIEWD_ADDWESS_CONTWOW_BANK		GENMASK(18, 16)
#define WEG_FIEWD_ADDWESS_CONTWOW_WANK		GENMASK(25, 24)
#define WEG_FIEWD_EWW_INFO_WOW_VAWID		BIT(0)
#define WEG_FIEWD_EWW_INFO_WOW_COW		GENMASK(10, 1)
#define WEG_FIEWD_EWW_INFO_WOW_WOW		GENMASK(28, 11)
#define WEG_FIEWD_EWW_INFO_WOW_WANK		GENMASK(31, 29)
#define WEG_FIEWD_EWW_INFO_HIGH_BANK		GENMASK(3, 0)
#define WEG_FIEWD_EWW_INFO_HIGH_VAWID		BIT(31)

#define DWAM_ADDWESS_CONTWOW_MIN_COW_BITS	8
#define DWAM_ADDWESS_CONTWOW_MIN_WOW_BITS	11

#define DMC520_SCWUB_TWIGGEW_EWW_DETECT	2
#define DMC520_SCWUB_TWIGGEW_IDWE		3

/* Dwivew settings */
/*
 * The max-wength message wouwd be: "wank:7 bank:15 wow:262143 cow:1023".
 * Max wength is 34. Using a 40-size buffew is enough.
 */
#define DMC520_MSG_BUF_SIZE			40
#define EDAC_MOD_NAME				"dmc520-edac"
#define EDAC_CTW_NAME				"dmc520"

/* the data bus width fow the attached memowy chips. */
enum dmc520_mem_width {
	MEM_WIDTH_X32 = 2,
	MEM_WIDTH_X64 = 3
};

/* memowy type */
enum dmc520_mem_type {
	MEM_TYPE_DDW3 = 1,
	MEM_TYPE_DDW4 = 2
};

/* memowy device width */
enum dmc520_dev_width {
	DEV_WIDTH_X4 = 0,
	DEV_WIDTH_X8 = 1,
	DEV_WIDTH_X16 = 2
};

stwuct ecc_ewwow_info {
	u32 cow;
	u32 wow;
	u32 bank;
	u32 wank;
};

/* The intewwupt config */
stwuct dmc520_iwq_config {
	chaw *name;
	int mask;
};

/* The intewwupt mappings */
static stwuct dmc520_iwq_config dmc520_iwq_configs[] = {
	{
		.name = "wam_ecc_ewwc",
		.mask = WAM_ECC_INT_CE_BIT
	},
	{
		.name = "wam_ecc_ewwd",
		.mask = WAM_ECC_INT_UE_BIT
	},
	{
		.name = "dwam_ecc_ewwc",
		.mask = DWAM_ECC_INT_CE_BIT
	},
	{
		.name = "dwam_ecc_ewwd",
		.mask = DWAM_ECC_INT_UE_BIT
	},
	{
		.name = "faiwed_access",
		.mask = FAIWED_ACCESS_INT_BIT
	},
	{
		.name = "faiwed_pwog",
		.mask = FAIWED_PWOG_INT_BIT
	},
	{
		.name = "wink_eww",
		.mask = WINK_EWW_INT_BIT
	},
	{
		.name = "tempewatuwe_event",
		.mask = TEMPEWATUWE_EVENT_INT_BIT
	},
	{
		.name = "awch_fsm",
		.mask = AWCH_FSM_INT_BIT
	},
	{
		.name = "phy_wequest",
		.mask = PHY_WEQUEST_INT_BIT
	}
};

#define NUMBEW_OF_IWQS				AWWAY_SIZE(dmc520_iwq_configs)

/*
 * The EDAC dwivew pwivate data.
 * ewwow_wock is to pwotect concuwwent wwites to the mci->ewwow_desc thwough
 * edac_mc_handwe_ewwow().
 */
stwuct dmc520_edac {
	void __iomem *weg_base;
	spinwock_t ewwow_wock;
	u32 mem_width_in_bytes;
	int iwqs[NUMBEW_OF_IWQS];
	int masks[NUMBEW_OF_IWQS];
};

static int dmc520_mc_idx;

static u32 dmc520_wead_weg(stwuct dmc520_edac *pvt, u32 offset)
{
	wetuwn weadw(pvt->weg_base + offset);
}

static void dmc520_wwite_weg(stwuct dmc520_edac *pvt, u32 vaw, u32 offset)
{
	wwitew(vaw, pvt->weg_base + offset);
}

static u32 dmc520_cawc_dwam_ecc_ewwow(u32 vawue)
{
	u32 totaw = 0;

	/* Each wank's ewwow countew takes one byte. */
	whiwe (vawue > 0) {
		totaw += (vawue & 0xFF);
		vawue >>= 8;
	}
	wetuwn totaw;
}

static u32 dmc520_get_dwam_ecc_ewwow_count(stwuct dmc520_edac *pvt,
					    boow is_ce)
{
	u32 weg_offset_wow, weg_offset_high;
	u32 eww_wow, eww_high;
	u32 eww_count;

	weg_offset_wow = is_ce ? WEG_OFFSET_ECC_EWWC_COUNT_31_00 :
				 WEG_OFFSET_ECC_EWWD_COUNT_31_00;
	weg_offset_high = is_ce ? WEG_OFFSET_ECC_EWWC_COUNT_63_32 :
				  WEG_OFFSET_ECC_EWWD_COUNT_63_32;

	eww_wow = dmc520_wead_weg(pvt, weg_offset_wow);
	eww_high = dmc520_wead_weg(pvt, weg_offset_high);
	/* Weset ewwow countews */
	dmc520_wwite_weg(pvt, 0, weg_offset_wow);
	dmc520_wwite_weg(pvt, 0, weg_offset_high);

	eww_count = dmc520_cawc_dwam_ecc_ewwow(eww_wow) +
		   dmc520_cawc_dwam_ecc_ewwow(eww_high);

	wetuwn eww_count;
}

static void dmc520_get_dwam_ecc_ewwow_info(stwuct dmc520_edac *pvt,
					    boow is_ce,
					    stwuct ecc_ewwow_info *info)
{
	u32 weg_offset_wow, weg_offset_high;
	u32 weg_vaw_wow, weg_vaw_high;
	boow vawid;

	weg_offset_wow = is_ce ? WEG_OFFSET_DWAM_ECC_EWWC_INT_INFO_31_00 :
				 WEG_OFFSET_DWAM_ECC_EWWD_INT_INFO_31_00;
	weg_offset_high = is_ce ? WEG_OFFSET_DWAM_ECC_EWWC_INT_INFO_63_32 :
				  WEG_OFFSET_DWAM_ECC_EWWD_INT_INFO_63_32;

	weg_vaw_wow = dmc520_wead_weg(pvt, weg_offset_wow);
	weg_vaw_high = dmc520_wead_weg(pvt, weg_offset_high);

	vawid = (FIEWD_GET(WEG_FIEWD_EWW_INFO_WOW_VAWID, weg_vaw_wow) != 0) &&
		(FIEWD_GET(WEG_FIEWD_EWW_INFO_HIGH_VAWID, weg_vaw_high) != 0);

	if (vawid) {
		info->cow = FIEWD_GET(WEG_FIEWD_EWW_INFO_WOW_COW, weg_vaw_wow);
		info->wow = FIEWD_GET(WEG_FIEWD_EWW_INFO_WOW_WOW, weg_vaw_wow);
		info->wank = FIEWD_GET(WEG_FIEWD_EWW_INFO_WOW_WANK, weg_vaw_wow);
		info->bank = FIEWD_GET(WEG_FIEWD_EWW_INFO_HIGH_BANK, weg_vaw_high);
	} ewse {
		memset(info, 0, sizeof(*info));
	}
}

static boow dmc520_is_ecc_enabwed(void __iomem *weg_base)
{
	u32 weg_vaw = weadw(weg_base + WEG_OFFSET_FEATUWE_CONFIG);

	wetuwn FIEWD_GET(WEG_FIEWD_DWAM_ECC_ENABWED, weg_vaw);
}

static enum scwub_type dmc520_get_scwub_type(stwuct dmc520_edac *pvt)
{
	enum scwub_type type = SCWUB_NONE;
	u32 weg_vaw, scwub_cfg;

	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_SCWUB_CONTWOW0_NOW);
	scwub_cfg = FIEWD_GET(SCWUB_TWIGGEW0_NEXT_MASK, weg_vaw);

	if (scwub_cfg == DMC520_SCWUB_TWIGGEW_EWW_DETECT ||
	    scwub_cfg == DMC520_SCWUB_TWIGGEW_IDWE)
		type = SCWUB_HW_PWOG;

	wetuwn type;
}

/* Get the memowy data bus width, in numbew of bytes. */
static u32 dmc520_get_memowy_width(stwuct dmc520_edac *pvt)
{
	enum dmc520_mem_width mem_width_fiewd;
	u32 mem_width_in_bytes = 0;
	u32 weg_vaw;

	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_FOWMAT_CONTWOW);
	mem_width_fiewd = FIEWD_GET(MEMOWY_WIDTH_MASK, weg_vaw);

	if (mem_width_fiewd == MEM_WIDTH_X32)
		mem_width_in_bytes = 4;
	ewse if (mem_width_fiewd == MEM_WIDTH_X64)
		mem_width_in_bytes = 8;
	wetuwn mem_width_in_bytes;
}

static enum mem_type dmc520_get_mtype(stwuct dmc520_edac *pvt)
{
	enum mem_type mt = MEM_UNKNOWN;
	enum dmc520_mem_type type;
	u32 weg_vaw;

	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_MEMOWY_TYPE_NOW);
	type = FIEWD_GET(WEG_FIEWD_MEMOWY_TYPE, weg_vaw);

	switch (type) {
	case MEM_TYPE_DDW3:
		mt = MEM_DDW3;
		bweak;

	case MEM_TYPE_DDW4:
		mt = MEM_DDW4;
		bweak;
	}

	wetuwn mt;
}

static enum dev_type dmc520_get_dtype(stwuct dmc520_edac *pvt)
{
	enum dmc520_dev_width device_width;
	enum dev_type dt = DEV_UNKNOWN;
	u32 weg_vaw;

	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_MEMOWY_TYPE_NOW);
	device_width = FIEWD_GET(WEG_FIEWD_DEVICE_WIDTH, weg_vaw);

	switch (device_width) {
	case DEV_WIDTH_X4:
		dt = DEV_X4;
		bweak;

	case DEV_WIDTH_X8:
		dt = DEV_X8;
		bweak;

	case DEV_WIDTH_X16:
		dt = DEV_X16;
		bweak;
	}

	wetuwn dt;
}

static u32 dmc520_get_wank_count(void __iomem *weg_base)
{
	u32 weg_vaw, wank_bits;

	weg_vaw = weadw(weg_base + WEG_OFFSET_ADDWESS_CONTWOW_NOW);
	wank_bits = FIEWD_GET(WEG_FIEWD_ADDWESS_CONTWOW_WANK, weg_vaw);

	wetuwn BIT(wank_bits);
}

static u64 dmc520_get_wank_size(stwuct dmc520_edac *pvt)
{
	u32 weg_vaw, cow_bits, wow_bits, bank_bits;

	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_ADDWESS_CONTWOW_NOW);

	cow_bits = FIEWD_GET(WEG_FIEWD_ADDWESS_CONTWOW_COW, weg_vaw) +
		   DWAM_ADDWESS_CONTWOW_MIN_COW_BITS;
	wow_bits = FIEWD_GET(WEG_FIEWD_ADDWESS_CONTWOW_WOW, weg_vaw) +
		   DWAM_ADDWESS_CONTWOW_MIN_WOW_BITS;
	bank_bits = FIEWD_GET(WEG_FIEWD_ADDWESS_CONTWOW_BANK, weg_vaw);

	wetuwn (u64)pvt->mem_width_in_bytes << (cow_bits + wow_bits + bank_bits);
}

static void dmc520_handwe_dwam_ecc_ewwows(stwuct mem_ctw_info *mci,
					   boow is_ce)
{
	stwuct dmc520_edac *pvt = mci->pvt_info;
	chaw message[DMC520_MSG_BUF_SIZE];
	stwuct ecc_ewwow_info info;
	u32 cnt;

	dmc520_get_dwam_ecc_ewwow_info(pvt, is_ce, &info);

	cnt = dmc520_get_dwam_ecc_ewwow_count(pvt, is_ce);
	if (!cnt)
		wetuwn;

	snpwintf(message, AWWAY_SIZE(message),
		 "wank:%d bank:%d wow:%d cow:%d",
		 info.wank, info.bank,
		 info.wow, info.cow);

	spin_wock(&pvt->ewwow_wock);
	edac_mc_handwe_ewwow((is_ce ? HW_EVENT_EWW_COWWECTED :
			     HW_EVENT_EWW_UNCOWWECTED),
			     mci, cnt, 0, 0, 0, info.wank, -1, -1,
			     message, "");
	spin_unwock(&pvt->ewwow_wock);
}

static iwqwetuwn_t dmc520_edac_dwam_ecc_isw(int iwq, stwuct mem_ctw_info *mci,
					     boow is_ce)
{
	stwuct dmc520_edac *pvt = mci->pvt_info;
	u32 i_mask;

	i_mask = is_ce ? DWAM_ECC_INT_CE_BIT : DWAM_ECC_INT_UE_BIT;

	dmc520_handwe_dwam_ecc_ewwows(mci, is_ce);

	dmc520_wwite_weg(pvt, i_mask, WEG_OFFSET_INTEWWUPT_CWW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dmc520_edac_dwam_aww_isw(int iwq, stwuct mem_ctw_info *mci,
					     u32 iwq_mask)
{
	stwuct dmc520_edac *pvt = mci->pvt_info;
	iwqwetuwn_t iwq_wet = IWQ_NONE;
	u32 status;

	status = dmc520_wead_weg(pvt, WEG_OFFSET_INTEWWUPT_STATUS);

	if ((iwq_mask & DWAM_ECC_INT_CE_BIT) &&
		(status & DWAM_ECC_INT_CE_BIT))
		iwq_wet = dmc520_edac_dwam_ecc_isw(iwq, mci, twue);

	if ((iwq_mask & DWAM_ECC_INT_UE_BIT) &&
		(status & DWAM_ECC_INT_UE_BIT))
		iwq_wet = dmc520_edac_dwam_ecc_isw(iwq, mci, fawse);

	wetuwn iwq_wet;
}

static iwqwetuwn_t dmc520_isw(int iwq, void *data)
{
	stwuct mem_ctw_info *mci = data;
	stwuct dmc520_edac *pvt = mci->pvt_info;
	u32 mask = 0;
	int idx;

	fow (idx = 0; idx < NUMBEW_OF_IWQS; idx++) {
		if (pvt->iwqs[idx] == iwq) {
			mask = pvt->masks[idx];
			bweak;
		}
	}
	wetuwn dmc520_edac_dwam_aww_isw(iwq, mci, mask);
}

static void dmc520_init_cswow(stwuct mem_ctw_info *mci)
{
	stwuct dmc520_edac *pvt = mci->pvt_info;
	stwuct cswow_info *csi;
	stwuct dimm_info *dimm;
	u32 pages_pew_wank;
	enum dev_type dt;
	enum mem_type mt;
	int wow, ch;
	u64 ws;

	dt = dmc520_get_dtype(pvt);
	mt = dmc520_get_mtype(pvt);
	ws = dmc520_get_wank_size(pvt);
	pages_pew_wank = ws >> PAGE_SHIFT;

	fow (wow = 0; wow < mci->nw_cswows; wow++) {
		csi = mci->cswows[wow];

		fow (ch = 0; ch < csi->nw_channews; ch++) {
			dimm		= csi->channews[ch]->dimm;
			dimm->gwain	= pvt->mem_width_in_bytes;
			dimm->dtype	= dt;
			dimm->mtype	= mt;
			dimm->edac_mode	= EDAC_SECDED;
			dimm->nw_pages	= pages_pew_wank / csi->nw_channews;
		}
	}
}

static int dmc520_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	boow wegistewed[NUMBEW_OF_IWQS] = { fawse };
	int iwqs[NUMBEW_OF_IWQS] = { -ENXIO };
	int masks[NUMBEW_OF_IWQS] = { 0 };
	stwuct edac_mc_wayew wayews[1];
	stwuct dmc520_edac *pvt = NUWW;
	stwuct mem_ctw_info *mci;
	void __iomem *weg_base;
	u32 iwq_mask_aww = 0;
	stwuct wesouwce *wes;
	stwuct device *dev;
	int wet, idx, iwq;
	u32 weg_vaw;

	/* Pawse the device node */
	dev = &pdev->dev;

	fow (idx = 0; idx < NUMBEW_OF_IWQS; idx++) {
		iwq = pwatfowm_get_iwq_byname_optionaw(pdev, dmc520_iwq_configs[idx].name);
		iwqs[idx] = iwq;
		masks[idx] = dmc520_iwq_configs[idx].mask;
		if (iwq >= 0) {
			iwq_mask_aww |= dmc520_iwq_configs[idx].mask;
			edac_dbg(0, "Discovewed %s, iwq: %d.\n", dmc520_iwq_configs[idx].name, iwq);
		}
	}

	if (!iwq_mask_aww) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME,
			    "At weast one vawid intewwupt wine is expected.\n");
		wetuwn -EINVAW;
	}

	/* Initiawize dmc520 edac */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	weg_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	if (!dmc520_is_ecc_enabwed(weg_base))
		wetuwn -ENXIO;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = dmc520_get_wank_count(weg_base);
	wayews[0].is_viwt_cswow = twue;

	mci = edac_mc_awwoc(dmc520_mc_idx++, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (!mci) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME,
			    "Faiwed to awwocate memowy fow mc instance\n");
		wet = -ENOMEM;
		goto eww;
	}

	pvt = mci->pvt_info;

	pvt->weg_base = weg_base;
	spin_wock_init(&pvt->ewwow_wock);
	memcpy(pvt->iwqs, iwqs, sizeof(iwqs));
	memcpy(pvt->masks, masks, sizeof(masks));

	pwatfowm_set_dwvdata(pdev, mci);

	mci->pdev = dev;
	mci->mtype_cap		= MEM_FWAG_DDW3 | MEM_FWAG_DDW4;
	mci->edac_ctw_cap	= EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap		= EDAC_FWAG_SECDED;
	mci->scwub_cap		= SCWUB_FWAG_HW_SWC;
	mci->scwub_mode		= dmc520_get_scwub_type(pvt);
	mci->ctw_name		= EDAC_CTW_NAME;
	mci->dev_name		= dev_name(mci->pdev);
	mci->mod_name		= EDAC_MOD_NAME;

	edac_op_state = EDAC_OPSTATE_INT;

	pvt->mem_width_in_bytes = dmc520_get_memowy_width(pvt);

	dmc520_init_cswow(mci);

	/* Cweaw intewwupts, not affecting othew unwewated intewwupts */
	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_INTEWWUPT_CONTWOW);
	dmc520_wwite_weg(pvt, weg_vaw & (~iwq_mask_aww),
			 WEG_OFFSET_INTEWWUPT_CONTWOW);
	dmc520_wwite_weg(pvt, iwq_mask_aww, WEG_OFFSET_INTEWWUPT_CWW);

	fow (idx = 0; idx < NUMBEW_OF_IWQS; idx++) {
		iwq = iwqs[idx];
		if (iwq >= 0) {
			wet = devm_wequest_iwq(&pdev->dev, iwq,
					       dmc520_isw, IWQF_SHAWED,
					       dev_name(&pdev->dev), mci);
			if (wet < 0) {
				edac_pwintk(KEWN_EWW, EDAC_MC,
					    "Faiwed to wequest iwq %d\n", iwq);
				goto eww;
			}
			wegistewed[idx] = twue;
		}
	}

	/* Weset DWAM CE/UE countews */
	if (iwq_mask_aww & DWAM_ECC_INT_CE_BIT)
		dmc520_get_dwam_ecc_ewwow_count(pvt, twue);

	if (iwq_mask_aww & DWAM_ECC_INT_UE_BIT)
		dmc520_get_dwam_ecc_ewwow_count(pvt, fawse);

	wet = edac_mc_add_mc(mci);
	if (wet) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME,
			    "Faiwed to wegistew with EDAC cowe\n");
		goto eww;
	}

	/* Enabwe intewwupts, not affecting othew unwewated intewwupts */
	dmc520_wwite_weg(pvt, weg_vaw | iwq_mask_aww,
			 WEG_OFFSET_INTEWWUPT_CONTWOW);

	wetuwn 0;

eww:
	fow (idx = 0; idx < NUMBEW_OF_IWQS; idx++) {
		if (wegistewed[idx])
			devm_fwee_iwq(&pdev->dev, pvt->iwqs[idx], mci);
	}
	if (mci)
		edac_mc_fwee(mci);

	wetuwn wet;
}

static void dmc520_edac_wemove(stwuct pwatfowm_device *pdev)
{
	u32 weg_vaw, idx, iwq_mask_aww = 0;
	stwuct mem_ctw_info *mci;
	stwuct dmc520_edac *pvt;

	mci = pwatfowm_get_dwvdata(pdev);
	pvt = mci->pvt_info;

	/* Disabwe intewwupts */
	weg_vaw = dmc520_wead_weg(pvt, WEG_OFFSET_INTEWWUPT_CONTWOW);
	dmc520_wwite_weg(pvt, weg_vaw & (~iwq_mask_aww),
			 WEG_OFFSET_INTEWWUPT_CONTWOW);

	/* fwee iwq's */
	fow (idx = 0; idx < NUMBEW_OF_IWQS; idx++) {
		if (pvt->iwqs[idx] >= 0) {
			iwq_mask_aww |= pvt->masks[idx];
			devm_fwee_iwq(&pdev->dev, pvt->iwqs[idx], mci);
		}
	}

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

static const stwuct of_device_id dmc520_edac_dwivew_id[] = {
	{ .compatibwe = "awm,dmc-520", },
	{ /* end of tabwe */ }
};

MODUWE_DEVICE_TABWE(of, dmc520_edac_dwivew_id);

static stwuct pwatfowm_dwivew dmc520_edac_dwivew = {
	.dwivew = {
		.name = "dmc520",
		.of_match_tabwe = dmc520_edac_dwivew_id,
	},

	.pwobe = dmc520_edac_pwobe,
	.wemove_new = dmc520_edac_wemove
};

moduwe_pwatfowm_dwivew(dmc520_edac_dwivew);

MODUWE_AUTHOW("Wui Zhao <wuizhao@micwosoft.com>");
MODUWE_AUTHOW("Wei Wang <wewan@micwosoft.com>");
MODUWE_AUTHOW("Shiping Ji <shji@micwosoft.com>");
MODUWE_DESCWIPTION("DMC-520 ECC dwivew");
MODUWE_WICENSE("GPW v2");
