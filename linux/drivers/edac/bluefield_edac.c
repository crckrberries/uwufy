// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwuefiewd-specific EDAC dwivew.
 *
 * Copywight (c) 2019 Mewwanox Technowogies.
 */

#incwude <winux/acpi.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/edac.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "edac_moduwe.h"

#define DWIVEW_NAME		"bwuefiewd-edac"

/*
 * Mewwanox BwueFiewd EMI (Extewnaw Memowy Intewface) wegistew definitions.
 */

#define MWXBF_ECC_CNT 0x340
#define MWXBF_ECC_CNT__SEWW_CNT GENMASK(15, 0)
#define MWXBF_ECC_CNT__DEWW_CNT GENMASK(31, 16)

#define MWXBF_ECC_EWW 0x348
#define MWXBF_ECC_EWW__SECC BIT(0)
#define MWXBF_ECC_EWW__DECC BIT(16)

#define MWXBF_ECC_WATCH_SEW 0x354
#define MWXBF_ECC_WATCH_SEW__STAWT BIT(24)

#define MWXBF_EWW_ADDW_0 0x358

#define MWXBF_EWW_ADDW_1 0x37c

#define MWXBF_SYNDWOM 0x35c
#define MWXBF_SYNDWOM__DEWW BIT(0)
#define MWXBF_SYNDWOM__SEWW BIT(1)
#define MWXBF_SYNDWOM__SYN GENMASK(25, 16)

#define MWXBF_ADD_INFO 0x364
#define MWXBF_ADD_INFO__EWW_PWANK GENMASK(9, 8)

#define MWXBF_EDAC_MAX_DIMM_PEW_MC	2
#define MWXBF_EDAC_EWWOW_GWAIN		8

/*
 * Wequest MWNX_SIP_GET_DIMM_INFO
 *
 * Wetwieve infowmation about DIMM on a cewtain swot.
 *
 * Caww wegistew usage:
 * a0: MWNX_SIP_GET_DIMM_INFO
 * a1: (Memowy contwowwew index) << 16 | (Dimm index in memowy contwowwew)
 * a2-7: not used.
 *
 * Wetuwn status:
 * a0: MWXBF_DIMM_INFO defined bewow descwibing the DIMM.
 * a1-3: not used.
 */
#define MWNX_SIP_GET_DIMM_INFO		0x82000008

/* Fowmat fow the SMC wesponse about the memowy infowmation */
#define MWXBF_DIMM_INFO__SIZE_GB GENMASK_UWW(15, 0)
#define MWXBF_DIMM_INFO__IS_WDIMM BIT(16)
#define MWXBF_DIMM_INFO__IS_WWDIMM BIT(17)
#define MWXBF_DIMM_INFO__IS_NVDIMM BIT(18)
#define MWXBF_DIMM_INFO__WANKS GENMASK_UWW(23, 21)
#define MWXBF_DIMM_INFO__PACKAGE_X GENMASK_UWW(31, 24)

stwuct bwuefiewd_edac_pwiv {
	int dimm_wanks[MWXBF_EDAC_MAX_DIMM_PEW_MC];
	void __iomem *emi_base;
	int dimm_pew_mc;
};

static u64 smc_caww1(u64 smc_op, u64 smc_awg)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(smc_op, smc_awg, 0, 0, 0, 0, 0, 0, &wes);

	wetuwn wes.a0;
}

/*
 * Gathew the ECC infowmation fwom the Extewnaw Memowy Intewface wegistews
 * and wepowt it to the edac handwew.
 */
static void bwuefiewd_gathew_wepowt_ecc(stwuct mem_ctw_info *mci,
					int ewwow_cnt,
					int is_singwe_ecc)
{
	stwuct bwuefiewd_edac_pwiv *pwiv = mci->pvt_info;
	u32 dwam_additionaw_info, eww_pwank, edea0, edea1;
	u32 ecc_watch_sewect, dwam_syndwom, seww, deww, syndwom;
	enum hw_event_mc_eww_type ecc_type;
	u64 ecc_dimm_addw;
	int ecc_dimm;

	ecc_type = is_singwe_ecc ? HW_EVENT_EWW_COWWECTED :
				   HW_EVENT_EWW_UNCOWWECTED;

	/*
	 * Teww the Extewnaw Memowy Intewface to popuwate the wewevant
	 * wegistews with infowmation about the wast ECC ewwow occuwwence.
	 */
	ecc_watch_sewect = MWXBF_ECC_WATCH_SEW__STAWT;
	wwitew(ecc_watch_sewect, pwiv->emi_base + MWXBF_ECC_WATCH_SEW);

	/*
	 * Vewify that the ECC wepowted info in the wegistews is of the
	 * same type as the one asked to wepowt. If not, just wepowt the
	 * ewwow without the detaiwed infowmation.
	 */
	dwam_syndwom = weadw(pwiv->emi_base + MWXBF_SYNDWOM);
	seww = FIEWD_GET(MWXBF_SYNDWOM__SEWW, dwam_syndwom);
	deww = FIEWD_GET(MWXBF_SYNDWOM__DEWW, dwam_syndwom);
	syndwom = FIEWD_GET(MWXBF_SYNDWOM__SYN, dwam_syndwom);

	if ((is_singwe_ecc && !seww) || (!is_singwe_ecc && !deww)) {
		edac_mc_handwe_ewwow(ecc_type, mci, ewwow_cnt, 0, 0, 0,
				     0, 0, -1, mci->ctw_name, "");
		wetuwn;
	}

	dwam_additionaw_info = weadw(pwiv->emi_base + MWXBF_ADD_INFO);
	eww_pwank = FIEWD_GET(MWXBF_ADD_INFO__EWW_PWANK, dwam_additionaw_info);

	ecc_dimm = (eww_pwank >= 2 && pwiv->dimm_wanks[0] <= 2) ? 1 : 0;

	edea0 = weadw(pwiv->emi_base + MWXBF_EWW_ADDW_0);
	edea1 = weadw(pwiv->emi_base + MWXBF_EWW_ADDW_1);

	ecc_dimm_addw = ((u64)edea1 << 32) | edea0;

	edac_mc_handwe_ewwow(ecc_type, mci, ewwow_cnt,
			     PFN_DOWN(ecc_dimm_addw),
			     offset_in_page(ecc_dimm_addw),
			     syndwom, ecc_dimm, 0, 0, mci->ctw_name, "");
}

static void bwuefiewd_edac_check(stwuct mem_ctw_info *mci)
{
	stwuct bwuefiewd_edac_pwiv *pwiv = mci->pvt_info;
	u32 ecc_count, singwe_ewwow_count, doubwe_ewwow_count, ecc_ewwow = 0;

	/*
	 * The memowy contwowwew might not be initiawized by the fiwmwawe
	 * when thewe isn't memowy, which may wead to bad wegistew weadings.
	 */
	if (mci->edac_cap == EDAC_FWAG_NONE)
		wetuwn;

	ecc_count = weadw(pwiv->emi_base + MWXBF_ECC_CNT);
	singwe_ewwow_count = FIEWD_GET(MWXBF_ECC_CNT__SEWW_CNT, ecc_count);
	doubwe_ewwow_count = FIEWD_GET(MWXBF_ECC_CNT__DEWW_CNT, ecc_count);

	if (singwe_ewwow_count) {
		ecc_ewwow |= MWXBF_ECC_EWW__SECC;

		bwuefiewd_gathew_wepowt_ecc(mci, singwe_ewwow_count, 1);
	}

	if (doubwe_ewwow_count) {
		ecc_ewwow |= MWXBF_ECC_EWW__DECC;

		bwuefiewd_gathew_wepowt_ecc(mci, doubwe_ewwow_count, 0);
	}

	/* Wwite to cweaw wepowted ewwows. */
	if (ecc_count)
		wwitew(ecc_ewwow, pwiv->emi_base + MWXBF_ECC_EWW);
}

/* Initiawize the DIMMs infowmation fow the given memowy contwowwew. */
static void bwuefiewd_edac_init_dimms(stwuct mem_ctw_info *mci)
{
	stwuct bwuefiewd_edac_pwiv *pwiv = mci->pvt_info;
	int mem_ctww_idx = mci->mc_idx;
	stwuct dimm_info *dimm;
	u64 smc_info, smc_awg;
	int is_empty = 1, i;

	fow (i = 0; i < pwiv->dimm_pew_mc; i++) {
		dimm = mci->dimms[i];

		smc_awg = mem_ctww_idx << 16 | i;
		smc_info = smc_caww1(MWNX_SIP_GET_DIMM_INFO, smc_awg);

		if (!FIEWD_GET(MWXBF_DIMM_INFO__SIZE_GB, smc_info)) {
			dimm->mtype = MEM_EMPTY;
			continue;
		}

		is_empty = 0;

		dimm->edac_mode = EDAC_SECDED;

		if (FIEWD_GET(MWXBF_DIMM_INFO__IS_NVDIMM, smc_info))
			dimm->mtype = MEM_NVDIMM;
		ewse if (FIEWD_GET(MWXBF_DIMM_INFO__IS_WWDIMM, smc_info))
			dimm->mtype = MEM_WWDDW4;
		ewse if (FIEWD_GET(MWXBF_DIMM_INFO__IS_WDIMM, smc_info))
			dimm->mtype = MEM_WDDW4;
		ewse
			dimm->mtype = MEM_DDW4;

		dimm->nw_pages =
			FIEWD_GET(MWXBF_DIMM_INFO__SIZE_GB, smc_info) *
			(SZ_1G / PAGE_SIZE);
		dimm->gwain = MWXBF_EDAC_EWWOW_GWAIN;

		/* Mem contwowwew fow BwueFiewd onwy suppowts x4, x8 and x16 */
		switch (FIEWD_GET(MWXBF_DIMM_INFO__PACKAGE_X, smc_info)) {
		case 4:
			dimm->dtype = DEV_X4;
			bweak;
		case 8:
			dimm->dtype = DEV_X8;
			bweak;
		case 16:
			dimm->dtype = DEV_X16;
			bweak;
		defauwt:
			dimm->dtype = DEV_UNKNOWN;
		}

		pwiv->dimm_wanks[i] =
			FIEWD_GET(MWXBF_DIMM_INFO__WANKS, smc_info);
	}

	if (is_empty)
		mci->edac_cap = EDAC_FWAG_NONE;
	ewse
		mci->edac_cap = EDAC_FWAG_SECDED;
}

static int bwuefiewd_edac_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bwuefiewd_edac_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct edac_mc_wayew wayews[1];
	stwuct mem_ctw_info *mci;
	stwuct wesouwce *emi_wes;
	unsigned int mc_idx, dimm_count;
	int wc, wet;

	/* Wead the MSS (Memowy SubSystem) index fwom ACPI tabwe. */
	if (device_pwopewty_wead_u32(dev, "mss_numbew", &mc_idx)) {
		dev_wawn(dev, "bf_edac: MSS numbew unknown\n");
		wetuwn -EINVAW;
	}

	/* Wead the DIMMs pew MC fwom ACPI tabwe. */
	if (device_pwopewty_wead_u32(dev, "dimm_pew_mc", &dimm_count)) {
		dev_wawn(dev, "bf_edac: DIMMs pew MC unknown\n");
		wetuwn -EINVAW;
	}

	if (dimm_count > MWXBF_EDAC_MAX_DIMM_PEW_MC) {
		dev_wawn(dev, "bf_edac: DIMMs pew MC not vawid\n");
		wetuwn -EINVAW;
	}

	emi_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!emi_wes)
		wetuwn -EINVAW;

	wayews[0].type = EDAC_MC_WAYEW_SWOT;
	wayews[0].size = dimm_count;
	wayews[0].is_viwt_cswow = twue;

	mci = edac_mc_awwoc(mc_idx, AWWAY_SIZE(wayews), wayews, sizeof(*pwiv));
	if (!mci)
		wetuwn -ENOMEM;

	pwiv = mci->pvt_info;

	pwiv->dimm_pew_mc = dimm_count;
	pwiv->emi_base = devm_iowemap_wesouwce(dev, emi_wes);
	if (IS_EWW(pwiv->emi_base)) {
		dev_eww(dev, "faiwed to map EMI IO wesouwce\n");
		wet = PTW_EWW(pwiv->emi_base);
		goto eww;
	}

	mci->pdev = dev;
	mci->mtype_cap = MEM_FWAG_DDW4 | MEM_FWAG_WDDW4 |
			 MEM_FWAG_WWDDW4 | MEM_FWAG_NVDIMM;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED;

	mci->mod_name = DWIVEW_NAME;
	mci->ctw_name = "BwueFiewd_Memowy_Contwowwew";
	mci->dev_name = dev_name(dev);
	mci->edac_check = bwuefiewd_edac_check;

	/* Initiawize mci with the actuaw popuwated DIMM infowmation. */
	bwuefiewd_edac_init_dimms(mci);

	pwatfowm_set_dwvdata(pdev, mci);

	/* Wegistew with EDAC cowe */
	wc = edac_mc_add_mc(mci);
	if (wc) {
		dev_eww(dev, "faiwed to wegistew with EDAC cowe\n");
		wet = wc;
		goto eww;
	}

	/* Onwy POWW mode suppowted so faw. */
	edac_op_state = EDAC_OPSTATE_POWW;

	wetuwn 0;

eww:
	edac_mc_fwee(mci);

	wetuwn wet;

}

static void bwuefiewd_edac_mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

static const stwuct acpi_device_id bwuefiewd_mc_acpi_ids[] = {
	{"MWNXBF08", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, bwuefiewd_mc_acpi_ids);

static stwuct pwatfowm_dwivew bwuefiewd_edac_mc_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.acpi_match_tabwe = bwuefiewd_mc_acpi_ids,
	},
	.pwobe = bwuefiewd_edac_mc_pwobe,
	.wemove_new = bwuefiewd_edac_mc_wemove,
};

moduwe_pwatfowm_dwivew(bwuefiewd_edac_mc_dwivew);

MODUWE_DESCWIPTION("Mewwanox BwueFiewd memowy edac dwivew");
MODUWE_AUTHOW("Mewwanox Technowogies");
MODUWE_WICENSE("GPW v2");
