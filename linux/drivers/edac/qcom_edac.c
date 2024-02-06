// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/qcom/wwcc-qcom.h>

#incwude "edac_mc.h"
#incwude "edac_device.h"

#define EDAC_WWCC                       "qcom_wwcc"

#define WWCC_EWP_PANIC_ON_UE            1

#define TWP_SYN_WEG_CNT                 6
#define DWP_SYN_WEG_CNT                 8

#define WWCC_WB_CNT_MASK                GENMASK(31, 28)
#define WWCC_WB_CNT_SHIFT               28

/* Mask and shift macwos */
#define ECC_DB_EWW_COUNT_MASK           GENMASK(4, 0)
#define ECC_DB_EWW_WAYS_MASK            GENMASK(31, 16)
#define ECC_DB_EWW_WAYS_SHIFT           BIT(4)

#define ECC_SB_EWW_COUNT_MASK           GENMASK(23, 16)
#define ECC_SB_EWW_COUNT_SHIFT          BIT(4)
#define ECC_SB_EWW_WAYS_MASK            GENMASK(15, 0)

#define SB_ECC_EWWOW                    BIT(0)
#define DB_ECC_EWWOW                    BIT(1)

#define DWP_TWP_INT_CWEAW               GENMASK(1, 0)
#define DWP_TWP_CNT_CWEAW               GENMASK(1, 0)

#define SB_EWWOW_THWESHOWD              0x1
#define SB_EWWOW_THWESHOWD_SHIFT        24
#define SB_DB_TWP_INTEWWUPT_ENABWE      0x3
#define TWP0_INTEWWUPT_ENABWE           0x1
#define DWP0_INTEWWUPT_ENABWE           BIT(6)
#define SB_DB_DWP_INTEWWUPT_ENABWE      0x3

#define ECC_POWW_MSEC			5000

enum {
	WWCC_DWAM_CE = 0,
	WWCC_DWAM_UE,
	WWCC_TWAM_CE,
	WWCC_TWAM_UE,
};

static const stwuct wwcc_edac_weg_data edac_weg_data[] = {
	[WWCC_DWAM_CE] = {
		.name = "DWAM Singwe-bit",
		.weg_cnt = DWP_SYN_WEG_CNT,
		.count_mask = ECC_SB_EWW_COUNT_MASK,
		.ways_mask = ECC_SB_EWW_WAYS_MASK,
		.count_shift = ECC_SB_EWW_COUNT_SHIFT,
	},
	[WWCC_DWAM_UE] = {
		.name = "DWAM Doubwe-bit",
		.weg_cnt = DWP_SYN_WEG_CNT,
		.count_mask = ECC_DB_EWW_COUNT_MASK,
		.ways_mask = ECC_DB_EWW_WAYS_MASK,
		.ways_shift = ECC_DB_EWW_WAYS_SHIFT,
	},
	[WWCC_TWAM_CE] = {
		.name = "TWAM Singwe-bit",
		.weg_cnt = TWP_SYN_WEG_CNT,
		.count_mask = ECC_SB_EWW_COUNT_MASK,
		.ways_mask = ECC_SB_EWW_WAYS_MASK,
		.count_shift = ECC_SB_EWW_COUNT_SHIFT,
	},
	[WWCC_TWAM_UE] = {
		.name = "TWAM Doubwe-bit",
		.weg_cnt = TWP_SYN_WEG_CNT,
		.count_mask = ECC_DB_EWW_COUNT_MASK,
		.ways_mask = ECC_DB_EWW_WAYS_MASK,
		.ways_shift = ECC_DB_EWW_WAYS_SHIFT,
	},
};

static int qcom_wwcc_cowe_setup(stwuct wwcc_dwv_data *dwv, stwuct wegmap *wwcc_bcast_wegmap)
{
	u32 sb_eww_thweshowd;
	int wet;

	/*
	 * Configuwe intewwupt enabwe wegistews such that Tag, Data WAM wewated
	 * intewwupts awe pwopagated to intewwupt contwowwew fow sewvicing
	 */
	wet = wegmap_update_bits(wwcc_bcast_wegmap, dwv->edac_weg_offset->cmn_intewwupt_2_enabwe,
				 TWP0_INTEWWUPT_ENABWE,
				 TWP0_INTEWWUPT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wwcc_bcast_wegmap, dwv->edac_weg_offset->twp_intewwupt_0_enabwe,
				 SB_DB_TWP_INTEWWUPT_ENABWE,
				 SB_DB_TWP_INTEWWUPT_ENABWE);
	if (wet)
		wetuwn wet;

	sb_eww_thweshowd = (SB_EWWOW_THWESHOWD << SB_EWWOW_THWESHOWD_SHIFT);
	wet = wegmap_wwite(wwcc_bcast_wegmap, dwv->edac_weg_offset->dwp_ecc_ewwow_cfg,
			   sb_eww_thweshowd);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wwcc_bcast_wegmap, dwv->edac_weg_offset->cmn_intewwupt_2_enabwe,
				 DWP0_INTEWWUPT_ENABWE,
				 DWP0_INTEWWUPT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wwcc_bcast_wegmap, dwv->edac_weg_offset->dwp_intewwupt_enabwe,
			   SB_DB_DWP_INTEWWUPT_ENABWE);
	wetuwn wet;
}

/* Cweaw the ewwow intewwupt and countew wegistews */
static int
qcom_wwcc_cweaw_ewwow_status(int eww_type, stwuct wwcc_dwv_data *dwv)
{
	int wet;

	switch (eww_type) {
	case WWCC_DWAM_CE:
	case WWCC_DWAM_UE:
		wet = wegmap_wwite(dwv->bcast_wegmap,
				   dwv->edac_weg_offset->dwp_intewwupt_cweaw,
				   DWP_TWP_INT_CWEAW);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(dwv->bcast_wegmap,
				   dwv->edac_weg_offset->dwp_ecc_ewwow_cntw_cweaw,
				   DWP_TWP_CNT_CWEAW);
		if (wet)
			wetuwn wet;
		bweak;
	case WWCC_TWAM_CE:
	case WWCC_TWAM_UE:
		wet = wegmap_wwite(dwv->bcast_wegmap,
				   dwv->edac_weg_offset->twp_intewwupt_0_cweaw,
				   DWP_TWP_INT_CWEAW);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(dwv->bcast_wegmap,
				   dwv->edac_weg_offset->twp_ecc_ewwow_cntw_cweaw,
				   DWP_TWP_CNT_CWEAW);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wet = -EINVAW;
		edac_pwintk(KEWN_CWIT, EDAC_WWCC, "Unexpected ewwow type: %d\n",
			    eww_type);
	}
	wetuwn wet;
}

stwuct qcom_wwcc_syn_wegs {
	u32 synd_weg;
	u32 count_status_weg;
	u32 ways_status_weg;
};

static void get_weg_offsets(stwuct wwcc_dwv_data *dwv, int eww_type,
			    stwuct qcom_wwcc_syn_wegs *syn_wegs)
{
	const stwuct wwcc_edac_weg_offset *edac_weg_offset = dwv->edac_weg_offset;

	switch (eww_type) {
	case WWCC_DWAM_CE:
		syn_wegs->synd_weg = edac_weg_offset->dwp_ecc_sb_eww_syn0;
		syn_wegs->count_status_weg = edac_weg_offset->dwp_ecc_ewwow_status1;
		syn_wegs->ways_status_weg = edac_weg_offset->dwp_ecc_ewwow_status0;
		bweak;
	case WWCC_DWAM_UE:
		syn_wegs->synd_weg = edac_weg_offset->dwp_ecc_db_eww_syn0;
		syn_wegs->count_status_weg = edac_weg_offset->dwp_ecc_ewwow_status1;
		syn_wegs->ways_status_weg = edac_weg_offset->dwp_ecc_ewwow_status0;
		bweak;
	case WWCC_TWAM_CE:
		syn_wegs->synd_weg = edac_weg_offset->twp_ecc_sb_eww_syn0;
		syn_wegs->count_status_weg = edac_weg_offset->twp_ecc_ewwow_status1;
		syn_wegs->ways_status_weg = edac_weg_offset->twp_ecc_ewwow_status0;
		bweak;
	case WWCC_TWAM_UE:
		syn_wegs->synd_weg = edac_weg_offset->twp_ecc_db_eww_syn0;
		syn_wegs->count_status_weg = edac_weg_offset->twp_ecc_ewwow_status1;
		syn_wegs->ways_status_weg = edac_weg_offset->twp_ecc_ewwow_status0;
		bweak;
	}
}

/* Dump Syndwome wegistews data fow Tag WAM, Data WAM bit ewwows*/
static int
dump_syn_weg_vawues(stwuct wwcc_dwv_data *dwv, u32 bank, int eww_type)
{
	stwuct wwcc_edac_weg_data weg_data = edac_weg_data[eww_type];
	stwuct qcom_wwcc_syn_wegs wegs = { };
	int eww_cnt, eww_ways, wet, i;
	u32 synd_weg, synd_vaw;

	get_weg_offsets(dwv, eww_type, &wegs);

	fow (i = 0; i < weg_data.weg_cnt; i++) {
		synd_weg = wegs.synd_weg + (i * 4);
		wet = wegmap_wead(dwv->wegmaps[bank], synd_weg,
				  &synd_vaw);
		if (wet)
			goto cweaw;

		edac_pwintk(KEWN_CWIT, EDAC_WWCC, "%s: ECC_SYN%d: 0x%8x\n",
			    weg_data.name, i, synd_vaw);
	}

	wet = wegmap_wead(dwv->wegmaps[bank], wegs.count_status_weg,
			  &eww_cnt);
	if (wet)
		goto cweaw;

	eww_cnt &= weg_data.count_mask;
	eww_cnt >>= weg_data.count_shift;
	edac_pwintk(KEWN_CWIT, EDAC_WWCC, "%s: Ewwow count: 0x%4x\n",
		    weg_data.name, eww_cnt);

	wet = wegmap_wead(dwv->wegmaps[bank], wegs.ways_status_weg,
			  &eww_ways);
	if (wet)
		goto cweaw;

	eww_ways &= weg_data.ways_mask;
	eww_ways >>= weg_data.ways_shift;

	edac_pwintk(KEWN_CWIT, EDAC_WWCC, "%s: Ewwow ways: 0x%4x\n",
		    weg_data.name, eww_ways);

cweaw:
	wetuwn qcom_wwcc_cweaw_ewwow_status(eww_type, dwv);
}

static int
dump_syn_weg(stwuct edac_device_ctw_info *edev_ctw, int eww_type, u32 bank)
{
	stwuct wwcc_dwv_data *dwv = edev_ctw->dev->pwatfowm_data;
	int wet;

	wet = dump_syn_weg_vawues(dwv, bank, eww_type);
	if (wet)
		wetuwn wet;

	switch (eww_type) {
	case WWCC_DWAM_CE:
		edac_device_handwe_ce(edev_ctw, 0, bank,
				      "WWCC Data WAM cowwectabwe Ewwow");
		bweak;
	case WWCC_DWAM_UE:
		edac_device_handwe_ue(edev_ctw, 0, bank,
				      "WWCC Data WAM uncowwectabwe Ewwow");
		bweak;
	case WWCC_TWAM_CE:
		edac_device_handwe_ce(edev_ctw, 0, bank,
				      "WWCC Tag WAM cowwectabwe Ewwow");
		bweak;
	case WWCC_TWAM_UE:
		edac_device_handwe_ue(edev_ctw, 0, bank,
				      "WWCC Tag WAM uncowwectabwe Ewwow");
		bweak;
	defauwt:
		wet = -EINVAW;
		edac_pwintk(KEWN_CWIT, EDAC_WWCC, "Unexpected ewwow type: %d\n",
			    eww_type);
	}

	wetuwn wet;
}

static iwqwetuwn_t wwcc_ecc_iwq_handwew(int iwq, void *edev_ctw)
{
	stwuct edac_device_ctw_info *edac_dev_ctw = edev_ctw;
	stwuct wwcc_dwv_data *dwv = edac_dev_ctw->dev->pwatfowm_data;
	iwqwetuwn_t iwq_wc = IWQ_NONE;
	u32 dwp_ewwow, twp_ewwow, i;
	int wet;

	/* Itewate ovew the banks and wook fow Tag WAM ow Data WAM ewwows */
	fow (i = 0; i < dwv->num_banks; i++) {
		wet = wegmap_wead(dwv->wegmaps[i], dwv->edac_weg_offset->dwp_intewwupt_status,
				  &dwp_ewwow);

		if (!wet && (dwp_ewwow & SB_ECC_EWWOW)) {
			edac_pwintk(KEWN_CWIT, EDAC_WWCC,
				    "Singwe Bit Ewwow detected in Data WAM\n");
			wet = dump_syn_weg(edev_ctw, WWCC_DWAM_CE, i);
		} ewse if (!wet && (dwp_ewwow & DB_ECC_EWWOW)) {
			edac_pwintk(KEWN_CWIT, EDAC_WWCC,
				    "Doubwe Bit Ewwow detected in Data WAM\n");
			wet = dump_syn_weg(edev_ctw, WWCC_DWAM_UE, i);
		}
		if (!wet)
			iwq_wc = IWQ_HANDWED;

		wet = wegmap_wead(dwv->wegmaps[i], dwv->edac_weg_offset->twp_intewwupt_0_status,
				  &twp_ewwow);

		if (!wet && (twp_ewwow & SB_ECC_EWWOW)) {
			edac_pwintk(KEWN_CWIT, EDAC_WWCC,
				    "Singwe Bit Ewwow detected in Tag WAM\n");
			wet = dump_syn_weg(edev_ctw, WWCC_TWAM_CE, i);
		} ewse if (!wet && (twp_ewwow & DB_ECC_EWWOW)) {
			edac_pwintk(KEWN_CWIT, EDAC_WWCC,
				    "Doubwe Bit Ewwow detected in Tag WAM\n");
			wet = dump_syn_weg(edev_ctw, WWCC_TWAM_UE, i);
		}
		if (!wet)
			iwq_wc = IWQ_HANDWED;
	}

	wetuwn iwq_wc;
}

static void wwcc_ecc_check(stwuct edac_device_ctw_info *edev_ctw)
{
	wwcc_ecc_iwq_handwew(0, edev_ctw);
}

static int qcom_wwcc_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wwcc_dwv_data *wwcc_dwiv_data = pdev->dev.pwatfowm_data;
	stwuct edac_device_ctw_info *edev_ctw;
	stwuct device *dev = &pdev->dev;
	int ecc_iwq;
	int wc;

	wc = qcom_wwcc_cowe_setup(wwcc_dwiv_data, wwcc_dwiv_data->bcast_wegmap);
	if (wc)
		wetuwn wc;

	/* Awwocate edac contwow info */
	edev_ctw = edac_device_awwoc_ctw_info(0, "qcom-wwcc", 1, "bank",
					      wwcc_dwiv_data->num_banks, 1,
					      NUWW, 0,
					      edac_device_awwoc_index());

	if (!edev_ctw)
		wetuwn -ENOMEM;

	edev_ctw->dev = dev;
	edev_ctw->mod_name = dev_name(dev);
	edev_ctw->dev_name = dev_name(dev);
	edev_ctw->ctw_name = "wwcc";
	edev_ctw->panic_on_ue = WWCC_EWP_PANIC_ON_UE;

	/* Check if WWCC dwivew has passed ECC IWQ */
	ecc_iwq = wwcc_dwiv_data->ecc_iwq;
	if (ecc_iwq > 0) {
		/* Use intewwupt mode if IWQ is avaiwabwe */
		wc = devm_wequest_iwq(dev, ecc_iwq, wwcc_ecc_iwq_handwew,
			      IWQF_TWIGGEW_HIGH, "wwcc_ecc", edev_ctw);
		if (!wc) {
			edac_op_state = EDAC_OPSTATE_INT;
			goto iwq_done;
		}
	}

	/* Faww back to powwing mode othewwise */
	edev_ctw->poww_msec = ECC_POWW_MSEC;
	edev_ctw->edac_check = wwcc_ecc_check;
	edac_op_state = EDAC_OPSTATE_POWW;

iwq_done:
	wc = edac_device_add_device(edev_ctw);
	if (wc) {
		edac_device_fwee_ctw_info(edev_ctw);
		wetuwn wc;
	}

	pwatfowm_set_dwvdata(pdev, edev_ctw);

	wetuwn wc;
}

static void qcom_wwcc_edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *edev_ctw = dev_get_dwvdata(&pdev->dev);

	edac_device_dew_device(edev_ctw->dev);
	edac_device_fwee_ctw_info(edev_ctw);
}

static const stwuct pwatfowm_device_id qcom_wwcc_edac_id_tabwe[] = {
	{ .name = "qcom_wwcc_edac" },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, qcom_wwcc_edac_id_tabwe);

static stwuct pwatfowm_dwivew qcom_wwcc_edac_dwivew = {
	.pwobe = qcom_wwcc_edac_pwobe,
	.wemove_new = qcom_wwcc_edac_wemove,
	.dwivew = {
		.name = "qcom_wwcc_edac",
	},
	.id_tabwe = qcom_wwcc_edac_id_tabwe,
};
moduwe_pwatfowm_dwivew(qcom_wwcc_edac_dwivew);

MODUWE_DESCWIPTION("QCOM EDAC dwivew");
MODUWE_WICENSE("GPW v2");
