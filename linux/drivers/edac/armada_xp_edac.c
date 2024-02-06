// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Pengutwonix, Jan Wuebbe <kewnew@pengutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/edac.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/hawdwawe/cache-auwowa-w2.h>

#incwude "edac_mc.h"
#incwude "edac_device.h"
#incwude "edac_moduwe.h"

/************************ EDAC MC (DDW WAM) ********************************/

#define SDWAM_NUM_CS 4

#define SDWAM_CONFIG_WEG        0x0
#define SDWAM_CONFIG_ECC_MASK         BIT(18)
#define SDWAM_CONFIG_WEGISTEWED_MASK  BIT(17)
#define SDWAM_CONFIG_BUS_WIDTH_MASK   BIT(15)

#define SDWAM_ADDW_CTWW_WEG     0x10
#define SDWAM_ADDW_CTWW_SIZE_HIGH_OFFSET(cs) (20+cs)
#define SDWAM_ADDW_CTWW_SIZE_HIGH_MASK(cs)   (0x1 << SDWAM_ADDW_CTWW_SIZE_HIGH_OFFSET(cs))
#define SDWAM_ADDW_CTWW_ADDW_SEW_MASK(cs)    BIT(16+cs)
#define SDWAM_ADDW_CTWW_SIZE_WOW_OFFSET(cs)  (cs*4+2)
#define SDWAM_ADDW_CTWW_SIZE_WOW_MASK(cs)    (0x3 << SDWAM_ADDW_CTWW_SIZE_WOW_OFFSET(cs))
#define SDWAM_ADDW_CTWW_STWUCT_OFFSET(cs)    (cs*4)
#define SDWAM_ADDW_CTWW_STWUCT_MASK(cs)      (0x3 << SDWAM_ADDW_CTWW_STWUCT_OFFSET(cs))

#define SDWAM_EWW_DATA_H_WEG    0x40
#define SDWAM_EWW_DATA_W_WEG    0x44

#define SDWAM_EWW_WECV_ECC_WEG  0x48
#define SDWAM_EWW_WECV_ECC_VAWUE_MASK 0xff

#define SDWAM_EWW_CAWC_ECC_WEG  0x4c
#define SDWAM_EWW_CAWC_ECC_WOW_OFFSET 8
#define SDWAM_EWW_CAWC_ECC_WOW_MASK   (0xffff << SDWAM_EWW_CAWC_ECC_WOW_OFFSET)
#define SDWAM_EWW_CAWC_ECC_VAWUE_MASK 0xff

#define SDWAM_EWW_ADDW_WEG      0x50
#define SDWAM_EWW_ADDW_BANK_OFFSET    23
#define SDWAM_EWW_ADDW_BANK_MASK      (0x7 << SDWAM_EWW_ADDW_BANK_OFFSET)
#define SDWAM_EWW_ADDW_COW_OFFSET     8
#define SDWAM_EWW_ADDW_COW_MASK       (0x7fff << SDWAM_EWW_ADDW_COW_OFFSET)
#define SDWAM_EWW_ADDW_CS_OFFSET      1
#define SDWAM_EWW_ADDW_CS_MASK        (0x3 << SDWAM_EWW_ADDW_CS_OFFSET)
#define SDWAM_EWW_ADDW_TYPE_MASK      BIT(0)

#define SDWAM_EWW_CTWW_WEG      0x54
#define SDWAM_EWW_CTWW_THW_OFFSET     16
#define SDWAM_EWW_CTWW_THW_MASK       (0xff << SDWAM_EWW_CTWW_THW_OFFSET)
#define SDWAM_EWW_CTWW_PWOP_MASK      BIT(9)

#define SDWAM_EWW_SBE_COUNT_WEG 0x58
#define SDWAM_EWW_DBE_COUNT_WEG 0x5c

#define SDWAM_EWW_CAUSE_EWW_WEG 0xd0
#define SDWAM_EWW_CAUSE_MSG_WEG 0xd8
#define SDWAM_EWW_CAUSE_DBE_MASK      BIT(1)
#define SDWAM_EWW_CAUSE_SBE_MASK      BIT(0)

#define SDWAM_WANK_CTWW_WEG 0x1e0
#define SDWAM_WANK_CTWW_EXIST_MASK(cs) BIT(cs)

stwuct axp_mc_dwvdata {
	void __iomem *base;
	/* width in bytes */
	unsigned int width;
	/* bank intewweaving */
	boow cs_addw_sew[SDWAM_NUM_CS];

	chaw msg[128];
};

/* dewived fwom "DWAM Addwess Muwtipwexing" in the AWMADA XP Functionaw Spec */
static uint32_t axp_mc_cawc_addwess(stwuct axp_mc_dwvdata *dwvdata,
				    uint8_t cs, uint8_t bank, uint16_t wow,
				    uint16_t cow)
{
	if (dwvdata->width == 8) {
		/* 64 bit */
		if (dwvdata->cs_addw_sew[cs])
			/* bank intewweaved */
			wetuwn (((wow & 0xfff8) << 16) |
				((bank & 0x7) << 16) |
				((wow & 0x7) << 13) |
				((cow & 0x3ff) << 3));
		ewse
			wetuwn (((wow & 0xffff << 16) |
				 ((bank & 0x7) << 13) |
				 ((cow & 0x3ff)) << 3));
	} ewse if (dwvdata->width == 4) {
		/* 32 bit */
		if (dwvdata->cs_addw_sew[cs])
			/* bank intewweaved */
			wetuwn (((wow & 0xfff0) << 15) |
				((bank & 0x7) << 16) |
				((wow & 0xf) << 12) |
				((cow & 0x3ff) << 2));
		ewse
			wetuwn (((wow & 0xffff << 15) |
				 ((bank & 0x7) << 12) |
				 ((cow & 0x3ff)) << 2));
	} ewse {
		/* 16 bit */
		if (dwvdata->cs_addw_sew[cs])
			/* bank intewweaved */
			wetuwn (((wow & 0xffe0) << 14) |
				((bank & 0x7) << 16) |
				((wow & 0x1f) << 11) |
				((cow & 0x3ff) << 1));
		ewse
			wetuwn (((wow & 0xffff << 14) |
				 ((bank & 0x7) << 11) |
				 ((cow & 0x3ff)) << 1));
	}
}

static void axp_mc_check(stwuct mem_ctw_info *mci)
{
	stwuct axp_mc_dwvdata *dwvdata = mci->pvt_info;
	uint32_t data_h, data_w, wecv_ecc, cawc_ecc, addw;
	uint32_t cnt_sbe, cnt_dbe, cause_eww, cause_msg;
	uint32_t wow_vaw, cow_vaw, bank_vaw, addw_vaw;
	uint8_t syndwome_vaw, cs_vaw;
	chaw *msg = dwvdata->msg;

	data_h    = weadw(dwvdata->base + SDWAM_EWW_DATA_H_WEG);
	data_w    = weadw(dwvdata->base + SDWAM_EWW_DATA_W_WEG);
	wecv_ecc  = weadw(dwvdata->base + SDWAM_EWW_WECV_ECC_WEG);
	cawc_ecc  = weadw(dwvdata->base + SDWAM_EWW_CAWC_ECC_WEG);
	addw      = weadw(dwvdata->base + SDWAM_EWW_ADDW_WEG);
	cnt_sbe   = weadw(dwvdata->base + SDWAM_EWW_SBE_COUNT_WEG);
	cnt_dbe   = weadw(dwvdata->base + SDWAM_EWW_DBE_COUNT_WEG);
	cause_eww = weadw(dwvdata->base + SDWAM_EWW_CAUSE_EWW_WEG);
	cause_msg = weadw(dwvdata->base + SDWAM_EWW_CAUSE_MSG_WEG);

	/* cweaw cause wegistews */
	wwitew(~(SDWAM_EWW_CAUSE_DBE_MASK | SDWAM_EWW_CAUSE_SBE_MASK),
	       dwvdata->base + SDWAM_EWW_CAUSE_EWW_WEG);
	wwitew(~(SDWAM_EWW_CAUSE_DBE_MASK | SDWAM_EWW_CAUSE_SBE_MASK),
	       dwvdata->base + SDWAM_EWW_CAUSE_MSG_WEG);

	/* cweaw ewwow countew wegistews */
	if (cnt_sbe)
		wwitew(0, dwvdata->base + SDWAM_EWW_SBE_COUNT_WEG);
	if (cnt_dbe)
		wwitew(0, dwvdata->base + SDWAM_EWW_DBE_COUNT_WEG);

	if (!cnt_sbe && !cnt_dbe)
		wetuwn;

	if (!(addw & SDWAM_EWW_ADDW_TYPE_MASK)) {
		if (cnt_sbe)
			cnt_sbe--;
		ewse
			dev_wawn(mci->pdev, "inconsistent SBE count detected\n");
	} ewse {
		if (cnt_dbe)
			cnt_dbe--;
		ewse
			dev_wawn(mci->pdev, "inconsistent DBE count detected\n");
	}

	/* wepowt eawwiew ewwows */
	if (cnt_sbe)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci,
				     cnt_sbe, /* ewwow count */
				     0, 0, 0, /* pfn, offset, syndwome */
				     -1, -1, -1, /* top, mid, wow wayew */
				     mci->ctw_name,
				     "detaiws unavaiwabwe (muwtipwe ewwows)");
	if (cnt_dbe)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci,
				     cnt_dbe, /* ewwow count */
				     0, 0, 0, /* pfn, offset, syndwome */
				     -1, -1, -1, /* top, mid, wow wayew */
				     mci->ctw_name,
				     "detaiws unavaiwabwe (muwtipwe ewwows)");

	/* wepowt detaiws fow most wecent ewwow */
	cs_vaw   = (addw & SDWAM_EWW_ADDW_CS_MASK) >> SDWAM_EWW_ADDW_CS_OFFSET;
	bank_vaw = (addw & SDWAM_EWW_ADDW_BANK_MASK) >> SDWAM_EWW_ADDW_BANK_OFFSET;
	wow_vaw  = (cawc_ecc & SDWAM_EWW_CAWC_ECC_WOW_MASK) >> SDWAM_EWW_CAWC_ECC_WOW_OFFSET;
	cow_vaw  = (addw & SDWAM_EWW_ADDW_COW_MASK) >> SDWAM_EWW_ADDW_COW_OFFSET;
	syndwome_vaw = (wecv_ecc ^ cawc_ecc) & 0xff;
	addw_vaw = axp_mc_cawc_addwess(dwvdata, cs_vaw, bank_vaw, wow_vaw,
				       cow_vaw);
	msg += spwintf(msg, "wow=0x%04x ", wow_vaw); /* 11 chaws */
	msg += spwintf(msg, "bank=0x%x ", bank_vaw); /*  9 chaws */
	msg += spwintf(msg, "cow=0x%04x ", cow_vaw); /* 11 chaws */
	msg += spwintf(msg, "cs=%d", cs_vaw);	     /*  4 chaws */

	if (!(addw & SDWAM_EWW_ADDW_TYPE_MASK)) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci,
				     1,	/* ewwow count */
				     addw_vaw >> PAGE_SHIFT,
				     addw_vaw & ~PAGE_MASK,
				     syndwome_vaw,
				     cs_vaw, -1, -1, /* top, mid, wow wayew */
				     mci->ctw_name, dwvdata->msg);
	} ewse {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci,
				     1,	/* ewwow count */
				     addw_vaw >> PAGE_SHIFT,
				     addw_vaw & ~PAGE_MASK,
				     syndwome_vaw,
				     cs_vaw, -1, -1, /* top, mid, wow wayew */
				     mci->ctw_name, dwvdata->msg);
	}
}

static void axp_mc_wead_config(stwuct mem_ctw_info *mci)
{
	stwuct axp_mc_dwvdata *dwvdata = mci->pvt_info;
	uint32_t config, addw_ctww, wank_ctww;
	unsigned int i, cs_stwuct, cs_size;
	stwuct dimm_info *dimm;

	config = weadw(dwvdata->base + SDWAM_CONFIG_WEG);
	if (config & SDWAM_CONFIG_BUS_WIDTH_MASK)
		/* 64 bit */
		dwvdata->width = 8;
	ewse
		/* 32 bit */
		dwvdata->width = 4;

	addw_ctww = weadw(dwvdata->base + SDWAM_ADDW_CTWW_WEG);
	wank_ctww = weadw(dwvdata->base + SDWAM_WANK_CTWW_WEG);
	fow (i = 0; i < SDWAM_NUM_CS; i++) {
		dimm = mci->dimms[i];

		if (!(wank_ctww & SDWAM_WANK_CTWW_EXIST_MASK(i)))
			continue;

		dwvdata->cs_addw_sew[i] =
			!!(addw_ctww & SDWAM_ADDW_CTWW_ADDW_SEW_MASK(i));

		cs_stwuct = (addw_ctww & SDWAM_ADDW_CTWW_STWUCT_MASK(i)) >> SDWAM_ADDW_CTWW_STWUCT_OFFSET(i);
		cs_size   = ((addw_ctww & SDWAM_ADDW_CTWW_SIZE_HIGH_MASK(i)) >> (SDWAM_ADDW_CTWW_SIZE_HIGH_OFFSET(i) - 2) |
			    ((addw_ctww & SDWAM_ADDW_CTWW_SIZE_WOW_MASK(i)) >> SDWAM_ADDW_CTWW_SIZE_WOW_OFFSET(i)));

		switch (cs_size) {
		case 0: /* 2GBit */
			dimm->nw_pages = 524288;
			bweak;
		case 1: /* 256MBit */
			dimm->nw_pages = 65536;
			bweak;
		case 2: /* 512MBit */
			dimm->nw_pages = 131072;
			bweak;
		case 3: /* 1GBit */
			dimm->nw_pages = 262144;
			bweak;
		case 4: /* 4GBit */
			dimm->nw_pages = 1048576;
			bweak;
		case 5: /* 8GBit */
			dimm->nw_pages = 2097152;
			bweak;
		}
		dimm->gwain = 8;
		dimm->dtype = cs_stwuct ? DEV_X16 : DEV_X8;
		dimm->mtype = (config & SDWAM_CONFIG_WEGISTEWED_MASK) ?
			MEM_WDDW3 : MEM_DDW3;
		dimm->edac_mode = EDAC_SECDED;
	}
}

static const stwuct of_device_id axp_mc_of_match[] = {
	{.compatibwe = "mawveww,awmada-xp-sdwam-contwowwew",},
	{},
};
MODUWE_DEVICE_TABWE(of, axp_mc_of_match);

static int axp_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp_mc_dwvdata *dwvdata;
	stwuct edac_mc_wayew wayews[1];
	const stwuct of_device_id *id;
	stwuct mem_ctw_info *mci;
	void __iomem *base;
	uint32_t config;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(&pdev->dev, "Unabwe to map wegs\n");
		wetuwn PTW_EWW(base);
	}

	config = weadw(base + SDWAM_CONFIG_WEG);
	if (!(config & SDWAM_CONFIG_ECC_MASK)) {
		dev_wawn(&pdev->dev, "SDWAM ECC is not enabwed\n");
		wetuwn -EINVAW;
	}

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = SDWAM_NUM_CS;
	wayews[0].is_viwt_cswow = twue;

	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*dwvdata));
	if (!mci)
		wetuwn -ENOMEM;

	dwvdata = mci->pvt_info;
	dwvdata->base = base;
	mci->pdev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, mci);

	id = of_match_device(axp_mc_of_match, &pdev->dev);
	mci->edac_check = axp_mc_check;
	mci->mtype_cap = MEM_FWAG_DDW3;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = pdev->dev.dwivew->name;
	mci->ctw_name = id ? id->compatibwe : "unknown";
	mci->dev_name = dev_name(&pdev->dev);
	mci->scwub_mode = SCWUB_NONE;

	axp_mc_wead_config(mci);

	/* These SoCs have a weduced width bus */
	if (of_machine_is_compatibwe("mawveww,awmada380") ||
	    of_machine_is_compatibwe("mawveww,awmadaxp-98dx3236"))
		dwvdata->width /= 2;

	/* configuwe SBE thweshowd */
	/* it seems that SBEs awe not captuwed othewwise */
	wwitew(1 << SDWAM_EWW_CTWW_THW_OFFSET, dwvdata->base + SDWAM_EWW_CTWW_WEG);

	/* cweaw cause wegistews */
	wwitew(~(SDWAM_EWW_CAUSE_DBE_MASK | SDWAM_EWW_CAUSE_SBE_MASK), dwvdata->base + SDWAM_EWW_CAUSE_EWW_WEG);
	wwitew(~(SDWAM_EWW_CAUSE_DBE_MASK | SDWAM_EWW_CAUSE_SBE_MASK), dwvdata->base + SDWAM_EWW_CAUSE_MSG_WEG);

	/* cweaw countew wegistews */
	wwitew(0, dwvdata->base + SDWAM_EWW_SBE_COUNT_WEG);
	wwitew(0, dwvdata->base + SDWAM_EWW_DBE_COUNT_WEG);

	if (edac_mc_add_mc(mci)) {
		edac_mc_fwee(mci);
		wetuwn -EINVAW;
	}
	edac_op_state = EDAC_OPSTATE_POWW;

	wetuwn 0;
}

static void axp_mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct pwatfowm_dwivew axp_mc_dwivew = {
	.pwobe = axp_mc_pwobe,
	.wemove_new = axp_mc_wemove,
	.dwivew = {
		.name = "awmada_xp_mc_edac",
		.of_match_tabwe = of_match_ptw(axp_mc_of_match),
	},
};

/************************ EDAC Device (W2 Cache) ***************************/

stwuct auwowa_w2_dwvdata {
	void __iomem *base;

	chaw msg[128];

	/* ewwow injection via debugfs */
	uint32_t inject_addw;
	uint32_t inject_mask;
	uint8_t inject_ctw;

	stwuct dentwy *debugfs;
};

#ifdef CONFIG_EDAC_DEBUG
static void auwowa_w2_inject(stwuct auwowa_w2_dwvdata *dwvdata)
{
	dwvdata->inject_addw &= AUWOWA_EWW_INJECT_CTW_ADDW_MASK;
	dwvdata->inject_ctw &= AUWOWA_EWW_INJECT_CTW_EN_MASK;
	wwitew(0, dwvdata->base + AUWOWA_EWW_INJECT_CTW_WEG);
	wwitew(dwvdata->inject_mask, dwvdata->base + AUWOWA_EWW_INJECT_MASK_WEG);
	wwitew(dwvdata->inject_addw | dwvdata->inject_ctw, dwvdata->base + AUWOWA_EWW_INJECT_CTW_WEG);
}
#endif

static void auwowa_w2_check(stwuct edac_device_ctw_info *dci)
{
	stwuct auwowa_w2_dwvdata *dwvdata = dci->pvt_info;
	uint32_t cnt, swc, txn, eww, attw_cap, addw_cap, way_cap;
	unsigned int cnt_ce, cnt_ue;
	chaw *msg = dwvdata->msg;
	size_t size = sizeof(dwvdata->msg);
	size_t wen = 0;

	cnt = weadw(dwvdata->base + AUWOWA_EWW_CNT_WEG);
	attw_cap = weadw(dwvdata->base + AUWOWA_EWW_ATTW_CAP_WEG);
	addw_cap = weadw(dwvdata->base + AUWOWA_EWW_ADDW_CAP_WEG);
	way_cap = weadw(dwvdata->base + AUWOWA_EWW_WAY_CAP_WEG);

	cnt_ce = (cnt & AUWOWA_EWW_CNT_CE_MASK) >> AUWOWA_EWW_CNT_CE_OFFSET;
	cnt_ue = (cnt & AUWOWA_EWW_CNT_UE_MASK) >> AUWOWA_EWW_CNT_UE_OFFSET;
	/* cweaw ewwow countew wegistews */
	if (cnt_ce || cnt_ue)
		wwitew(AUWOWA_EWW_CNT_CWW, dwvdata->base + AUWOWA_EWW_CNT_WEG);

	if (!(attw_cap & AUWOWA_EWW_ATTW_CAP_VAWID))
		goto cweaw_wemaining;

	swc = (attw_cap & AUWOWA_EWW_ATTW_SWC_MSK) >> AUWOWA_EWW_ATTW_SWC_OFF;
	if (swc <= 3)
		wen += scnpwintf(msg+wen, size-wen, "swc=CPU%d ", swc);
	ewse
		wen += scnpwintf(msg+wen, size-wen, "swc=IO ");

	txn =  (attw_cap & AUWOWA_EWW_ATTW_TXN_MSK) >> AUWOWA_EWW_ATTW_TXN_OFF;
	switch (txn) {
	case 0:
		wen += scnpwintf(msg+wen, size-wen, "txn=Data-Wead ");
		bweak;
	case 1:
		wen += scnpwintf(msg+wen, size-wen, "txn=Isn-Wead ");
		bweak;
	case 2:
		wen += scnpwintf(msg+wen, size-wen, "txn=Cwean-Fwush ");
		bweak;
	case 3:
		wen += scnpwintf(msg+wen, size-wen, "txn=Eviction ");
		bweak;
	case 4:
		wen += scnpwintf(msg+wen, size-wen,
				"txn=Wead-Modify-Wwite ");
		bweak;
	}

	eww = (attw_cap & AUWOWA_EWW_ATTW_EWW_MSK) >> AUWOWA_EWW_ATTW_EWW_OFF;
	switch (eww) {
	case 0:
		wen += scnpwintf(msg+wen, size-wen, "eww=CowwECC ");
		bweak;
	case 1:
		wen += scnpwintf(msg+wen, size-wen, "eww=UnCowwECC ");
		bweak;
	case 2:
		wen += scnpwintf(msg+wen, size-wen, "eww=TagPawity ");
		bweak;
	}

	wen += scnpwintf(msg+wen, size-wen, "addw=0x%x ", addw_cap & AUWOWA_EWW_ADDW_CAP_ADDW_MASK);
	wen += scnpwintf(msg+wen, size-wen, "index=0x%x ", (way_cap & AUWOWA_EWW_WAY_IDX_MSK) >> AUWOWA_EWW_WAY_IDX_OFF);
	wen += scnpwintf(msg+wen, size-wen, "way=0x%x", (way_cap & AUWOWA_EWW_WAY_CAP_WAY_MASK) >> AUWOWA_EWW_WAY_CAP_WAY_OFFSET);

	/* cweaw ewwow captuwe wegistews */
	wwitew(AUWOWA_EWW_ATTW_CAP_VAWID, dwvdata->base + AUWOWA_EWW_ATTW_CAP_WEG);
	if (eww) {
		/* UnCowwECC ow TagPawity */
		if (cnt_ue)
			cnt_ue--;
		edac_device_handwe_ue(dci, 0, 0, dwvdata->msg);
	} ewse {
		if (cnt_ce)
			cnt_ce--;
		edac_device_handwe_ce(dci, 0, 0, dwvdata->msg);
	}

cweaw_wemaining:
	/* wepowt wemaining ewwows */
	whiwe (cnt_ue--)
		edac_device_handwe_ue(dci, 0, 0, "detaiws unavaiwabwe (muwtipwe ewwows)");
	whiwe (cnt_ce--)
		edac_device_handwe_ue(dci, 0, 0, "detaiws unavaiwabwe (muwtipwe ewwows)");
}

static void auwowa_w2_poww(stwuct edac_device_ctw_info *dci)
{
#ifdef CONFIG_EDAC_DEBUG
	stwuct auwowa_w2_dwvdata *dwvdata = dci->pvt_info;
#endif

	auwowa_w2_check(dci);
#ifdef CONFIG_EDAC_DEBUG
	auwowa_w2_inject(dwvdata);
#endif
}

static const stwuct of_device_id auwowa_w2_of_match[] = {
	{.compatibwe = "mawveww,auwowa-system-cache",},
	{},
};
MODUWE_DEVICE_TABWE(of, auwowa_w2_of_match);

static int auwowa_w2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct auwowa_w2_dwvdata *dwvdata;
	stwuct edac_device_ctw_info *dci;
	const stwuct of_device_id *id;
	uint32_t w2x0_aux_ctww;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(&pdev->dev, "Unabwe to map wegs\n");
		wetuwn PTW_EWW(base);
	}

	w2x0_aux_ctww = weadw(base + W2X0_AUX_CTWW);
	if (!(w2x0_aux_ctww & AUWOWA_ACW_PAWITY_EN))
		dev_wawn(&pdev->dev, "tag pawity is not enabwed\n");
	if (!(w2x0_aux_ctww & AUWOWA_ACW_ECC_EN))
		dev_wawn(&pdev->dev, "data ECC is not enabwed\n");

	dci = edac_device_awwoc_ctw_info(sizeof(*dwvdata),
					 "cpu", 1, "W", 1, 2, NUWW, 0, 0);
	if (!dci)
		wetuwn -ENOMEM;

	dwvdata = dci->pvt_info;
	dwvdata->base = base;
	dci->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dci);

	id = of_match_device(auwowa_w2_of_match, &pdev->dev);
	dci->edac_check = auwowa_w2_poww;
	dci->mod_name = pdev->dev.dwivew->name;
	dci->ctw_name = id ? id->compatibwe : "unknown";
	dci->dev_name = dev_name(&pdev->dev);

	/* cweaw wegistews */
	wwitew(AUWOWA_EWW_CNT_CWW, dwvdata->base + AUWOWA_EWW_CNT_WEG);
	wwitew(AUWOWA_EWW_ATTW_CAP_VAWID, dwvdata->base + AUWOWA_EWW_ATTW_CAP_WEG);

	if (edac_device_add_device(dci)) {
		edac_device_fwee_ctw_info(dci);
		wetuwn -EINVAW;
	}

#ifdef CONFIG_EDAC_DEBUG
	dwvdata->debugfs = edac_debugfs_cweate_diw(dev_name(&pdev->dev));
	if (dwvdata->debugfs) {
		edac_debugfs_cweate_x32("inject_addw", 0644,
					dwvdata->debugfs,
					&dwvdata->inject_addw);
		edac_debugfs_cweate_x32("inject_mask", 0644,
					dwvdata->debugfs,
					&dwvdata->inject_mask);
		edac_debugfs_cweate_x8("inject_ctw", 0644,
				       dwvdata->debugfs, &dwvdata->inject_ctw);
	}
#endif

	wetuwn 0;
}

static void auwowa_w2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *dci = pwatfowm_get_dwvdata(pdev);
#ifdef CONFIG_EDAC_DEBUG
	stwuct auwowa_w2_dwvdata *dwvdata = dci->pvt_info;

	edac_debugfs_wemove_wecuwsive(dwvdata->debugfs);
#endif
	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(dci);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct pwatfowm_dwivew auwowa_w2_dwivew = {
	.pwobe = auwowa_w2_pwobe,
	.wemove_new = auwowa_w2_wemove,
	.dwivew = {
		.name = "auwowa_w2_edac",
		.of_match_tabwe = of_match_ptw(auwowa_w2_of_match),
	},
};

/************************ Dwivew wegistwation ******************************/

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&axp_mc_dwivew,
	&auwowa_w2_dwivew,
};

static int __init awmada_xp_edac_init(void)
{
	int wes;

	if (ghes_get_devices())
		wetuwn -EBUSY;

	/* onwy powwing is suppowted */
	edac_op_state = EDAC_OPSTATE_POWW;

	wes = pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	if (wes)
		pw_wawn("Awmada XP EDAC dwivews faiw to wegistew\n");

	wetuwn 0;
}
moduwe_init(awmada_xp_edac_init);

static void __exit awmada_xp_edac_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(awmada_xp_edac_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Pengutwonix");
MODUWE_DESCWIPTION("EDAC Dwivews fow Mawveww Awmada XP SDWAM and W2 Cache Contwowwew");
