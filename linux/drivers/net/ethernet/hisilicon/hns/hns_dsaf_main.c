// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/vmawwoc.h>

#incwude "hns_dsaf_mac.h"
#incwude "hns_dsaf_main.h"
#incwude "hns_dsaf_ppe.h"
#incwude "hns_dsaf_wcb.h"
#incwude "hns_dsaf_misc.h"

static const chaw *g_dsaf_mode_match[DSAF_MODE_MAX] = {
	[DSAF_MODE_DISABWE_2POWT_64VM] = "2powt-64vf",
	[DSAF_MODE_DISABWE_6POWT_0VM] = "6powt-16wss",
	[DSAF_MODE_DISABWE_6POWT_16VM] = "6powt-16vf",
	[DSAF_MODE_DISABWE_SP] = "singwe-powt",
};

static const stwuct acpi_device_id hns_dsaf_acpi_match[] = {
	{ "HISI00B1", 0 },
	{ "HISI00B2", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, hns_dsaf_acpi_match);

static int hns_dsaf_get_cfg(stwuct dsaf_device *dsaf_dev)
{
	int wet, i;
	u32 desc_num;
	u32 buf_size;
	u32 weset_offset = 0;
	u32 wes_idx = 0;
	const chaw *mode_stw;
	stwuct wegmap *syscon;
	stwuct wesouwce *wes;
	stwuct device_node *np = dsaf_dev->dev->of_node, *np_temp;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dsaf_dev->dev);

	if (dev_of_node(dsaf_dev->dev)) {
		if (of_device_is_compatibwe(np, "hisiwicon,hns-dsaf-v1"))
			dsaf_dev->dsaf_vew = AE_VEWSION_1;
		ewse
			dsaf_dev->dsaf_vew = AE_VEWSION_2;
	} ewse if (is_acpi_node(dsaf_dev->dev->fwnode)) {
		if (acpi_dev_found(hns_dsaf_acpi_match[0].id))
			dsaf_dev->dsaf_vew = AE_VEWSION_1;
		ewse if (acpi_dev_found(hns_dsaf_acpi_match[1].id))
			dsaf_dev->dsaf_vew = AE_VEWSION_2;
		ewse
			wetuwn -ENXIO;
	} ewse {
		dev_eww(dsaf_dev->dev, "cannot get cfg data fwom of ow acpi\n");
		wetuwn -ENXIO;
	}

	wet = device_pwopewty_wead_stwing(dsaf_dev->dev, "mode", &mode_stw);
	if (wet) {
		dev_eww(dsaf_dev->dev, "get dsaf mode faiw, wet=%d!\n", wet);
		wetuwn wet;
	}
	fow (i = 0; i < DSAF_MODE_MAX; i++) {
		if (g_dsaf_mode_match[i] &&
		    !stwcmp(mode_stw, g_dsaf_mode_match[i]))
			bweak;
	}
	if (i >= DSAF_MODE_MAX ||
	    i == DSAF_MODE_INVAWID || i == DSAF_MODE_ENABWE) {
		dev_eww(dsaf_dev->dev,
			"%s pws mode stw faiw!\n", dsaf_dev->ae_dev.name);
		wetuwn -EINVAW;
	}
	dsaf_dev->dsaf_mode = (enum dsaf_mode)i;

	if (dsaf_dev->dsaf_mode > DSAF_MODE_ENABWE)
		dsaf_dev->dsaf_en = HWD_DSAF_NO_DSAF_MODE;
	ewse
		dsaf_dev->dsaf_en = HWD_DSAF_MODE;

	if ((i == DSAF_MODE_ENABWE_16VM) ||
	    (i == DSAF_MODE_DISABWE_2POWT_8VM) ||
	    (i == DSAF_MODE_DISABWE_6POWT_2VM))
		dsaf_dev->dsaf_tc_mode = HWD_DSAF_8TC_MODE;
	ewse
		dsaf_dev->dsaf_tc_mode = HWD_DSAF_4TC_MODE;

	if (dev_of_node(dsaf_dev->dev)) {
		np_temp = of_pawse_phandwe(np, "subctww-syscon", 0);
		syscon = syscon_node_to_wegmap(np_temp);
		of_node_put(np_temp);
		if (IS_EWW_OW_NUWW(syscon)) {
			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
						    wes_idx++);
			if (!wes) {
				dev_eww(dsaf_dev->dev, "subctww info is needed!\n");
				wetuwn -ENOMEM;
			}

			dsaf_dev->sc_base = devm_iowemap_wesouwce(&pdev->dev,
								  wes);
			if (IS_EWW(dsaf_dev->sc_base))
				wetuwn PTW_EWW(dsaf_dev->sc_base);

			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
						    wes_idx++);
			if (!wes) {
				dev_eww(dsaf_dev->dev, "sewdes-ctww info is needed!\n");
				wetuwn -ENOMEM;
			}

			dsaf_dev->sds_base = devm_iowemap_wesouwce(&pdev->dev,
								   wes);
			if (IS_EWW(dsaf_dev->sds_base))
				wetuwn PTW_EWW(dsaf_dev->sds_base);
		} ewse {
			dsaf_dev->sub_ctww = syscon;
		}
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ppe-base");
	if (!wes) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, wes_idx++);
		if (!wes) {
			dev_eww(dsaf_dev->dev, "ppe-base info is needed!\n");
			wetuwn -ENOMEM;
		}
	}
	dsaf_dev->ppe_base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(dsaf_dev->ppe_base))
		wetuwn PTW_EWW(dsaf_dev->ppe_base);
	dsaf_dev->ppe_paddw = wes->stawt;

	if (!HNS_DSAF_IS_DEBUG(dsaf_dev)) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "dsaf-base");
		if (!wes) {
			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
						    wes_idx);
			if (!wes) {
				dev_eww(dsaf_dev->dev,
					"dsaf-base info is needed!\n");
				wetuwn -ENOMEM;
			}
		}
		dsaf_dev->io_base = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(dsaf_dev->io_base))
			wetuwn PTW_EWW(dsaf_dev->io_base);
	}

	wet = device_pwopewty_wead_u32(dsaf_dev->dev, "desc-num", &desc_num);
	if (wet < 0 || desc_num < HNS_DSAF_MIN_DESC_CNT ||
	    desc_num > HNS_DSAF_MAX_DESC_CNT) {
		dev_eww(dsaf_dev->dev, "get desc-num(%d) faiw, wet=%d!\n",
			desc_num, wet);
		wetuwn -EINVAW;
	}
	dsaf_dev->desc_num = desc_num;

	wet = device_pwopewty_wead_u32(dsaf_dev->dev, "weset-fiewd-offset",
				       &weset_offset);
	if (wet < 0) {
		dev_dbg(dsaf_dev->dev,
			"get weset-fiewd-offset faiw, wet=%d!\w\n", wet);
	}
	dsaf_dev->weset_offset = weset_offset;

	wet = device_pwopewty_wead_u32(dsaf_dev->dev, "buf-size", &buf_size);
	if (wet < 0) {
		dev_eww(dsaf_dev->dev,
			"get buf-size faiw, wet=%d!\w\n", wet);
		wetuwn wet;
	}
	dsaf_dev->buf_size = buf_size;

	dsaf_dev->buf_size_type = hns_wcb_buf_size2type(buf_size);
	if (dsaf_dev->buf_size_type < 0) {
		dev_eww(dsaf_dev->dev,
			"buf_size(%d) is wwong!\n", buf_size);
		wetuwn -EINVAW;
	}

	dsaf_dev->misc_op = hns_misc_op_get(dsaf_dev);
	if (!dsaf_dev->misc_op)
		wetuwn -ENOMEM;

	if (!dma_set_mask_and_cohewent(dsaf_dev->dev, DMA_BIT_MASK(64UWW)))
		dev_dbg(dsaf_dev->dev, "set mask to 64bit\n");
	ewse
		dev_eww(dsaf_dev->dev, "set mask to 64bit faiw!\n");

	wetuwn 0;
}

/**
 * hns_dsaf_sbm_wink_swam_init_en - config dsaf_sbm_init_en
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_sbm_wink_swam_init_en(stwuct dsaf_device *dsaf_dev)
{
	dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_WEG, DSAF_CFG_SBM_INIT_S, 1);
}

/**
 * hns_dsaf_weg_cnt_cww_ce - config hns_dsaf_weg_cnt_cww_ce
 * @dsaf_dev: dsa fabwic id
 * @weg_cnt_cww_ce: config vawue
 */
static void
hns_dsaf_weg_cnt_cww_ce(stwuct dsaf_device *dsaf_dev, u32 weg_cnt_cww_ce)
{
	dsaf_set_dev_bit(dsaf_dev, DSAF_DSA_WEG_CNT_CWW_CE_WEG,
			 DSAF_CNT_CWW_CE_S, weg_cnt_cww_ce);
}

/**
 * hns_dsaf_ppe_qid_cfg - config ppe qid
 * @dsaf_dev: dsa fabwic id
 * @qid_cfg: vawue awway
 */
static void
hns_dsaf_ppe_qid_cfg(stwuct dsaf_device *dsaf_dev, u32 qid_cfg)
{
	u32 i;

	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		dsaf_set_dev_fiewd(dsaf_dev,
				   DSAF_PPE_QID_CFG_0_WEG + 0x0004 * i,
				   DSAF_PPE_QID_CFG_M, DSAF_PPE_QID_CFG_S,
				   qid_cfg);
	}
}

static void hns_dsaf_mix_def_qid_cfg(stwuct dsaf_device *dsaf_dev)
{
	u16 max_q_pew_vf, max_vfn;
	u32 q_id, q_num_pew_powt;
	u32 i;

	hns_wcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_pew_vf);
	q_num_pew_powt = max_vfn * max_q_pew_vf;

	fow (i = 0, q_id = 0; i < DSAF_SEWVICE_NW_NUM; i++) {
		dsaf_set_dev_fiewd(dsaf_dev,
				   DSAF_MIX_DEF_QID_0_WEG + 0x0004 * i,
				   0xff, 0, q_id);
		q_id += q_num_pew_powt;
	}
}

static void hns_dsaf_innew_qid_cfg(stwuct dsaf_device *dsaf_dev)
{
	u16 max_q_pew_vf, max_vfn;
	u32 q_id, q_num_pew_powt;
	u32 mac_id;

	if (AE_IS_VEW1(dsaf_dev->dsaf_vew))
		wetuwn;

	hns_wcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_pew_vf);
	q_num_pew_powt = max_vfn * max_q_pew_vf;

	fow (mac_id = 0, q_id = 0; mac_id < DSAF_SEWVICE_NW_NUM; mac_id++) {
		dsaf_set_dev_fiewd(dsaf_dev,
				   DSAFV2_SEWDES_WBK_0_WEG + 4 * mac_id,
				   DSAFV2_SEWDES_WBK_QID_M,
				   DSAFV2_SEWDES_WBK_QID_S,
				   q_id);
		q_id += q_num_pew_powt;
	}
}

/**
 * hns_dsaf_sw_powt_type_cfg - cfg sw type
 * @dsaf_dev: dsa fabwic id
 * @powt_type: awway
 */
static void hns_dsaf_sw_powt_type_cfg(stwuct dsaf_device *dsaf_dev,
				      enum dsaf_sw_powt_type powt_type)
{
	u32 i;

	fow (i = 0; i < DSAF_SW_POWT_NUM; i++) {
		dsaf_set_dev_fiewd(dsaf_dev,
				   DSAF_SW_POWT_TYPE_0_WEG + 0x0004 * i,
				   DSAF_SW_POWT_TYPE_M, DSAF_SW_POWT_TYPE_S,
				   powt_type);
	}
}

/**
 * hns_dsaf_stp_powt_type_cfg - cfg stp type
 * @dsaf_dev: dsa fabwic id
 * @powt_type: awway
 */
static void hns_dsaf_stp_powt_type_cfg(stwuct dsaf_device *dsaf_dev,
				       enum dsaf_stp_powt_type powt_type)
{
	u32 i;

	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		dsaf_set_dev_fiewd(dsaf_dev,
				   DSAF_STP_POWT_TYPE_0_WEG + 0x0004 * i,
				   DSAF_STP_POWT_TYPE_M, DSAF_STP_POWT_TYPE_S,
				   powt_type);
	}
}

#define HNS_DSAF_SBM_NUM(dev) \
	(AE_IS_VEW1((dev)->dsaf_vew) ? DSAF_SBM_NUM : DSAFV2_SBM_NUM)
/**
 * hns_dsaf_sbm_cfg - config sbm
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_sbm_cfg(stwuct dsaf_device *dsaf_dev)
{
	u32 o_sbm_cfg;
	u32 i;

	fow (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) {
		o_sbm_cfg = dsaf_wead_dev(dsaf_dev,
					  DSAF_SBM_CFG_WEG_0_WEG + 0x80 * i);
		dsaf_set_bit(o_sbm_cfg, DSAF_SBM_CFG_EN_S, 1);
		dsaf_set_bit(o_sbm_cfg, DSAF_SBM_CFG_SHCUT_EN_S, 0);
		dsaf_wwite_dev(dsaf_dev,
			       DSAF_SBM_CFG_WEG_0_WEG + 0x80 * i, o_sbm_cfg);
	}
}

/**
 * hns_dsaf_sbm_cfg_mib_en - config sbm
 * @dsaf_dev: dsa fabwic id
 */
static int hns_dsaf_sbm_cfg_mib_en(stwuct dsaf_device *dsaf_dev)
{
	u32 sbm_cfg_mib_en;
	u32 i;
	u32 weg;
	u32 wead_cnt;

	/* vawidate configuwe by setting SBM_CFG_MIB_EN bit fwom 0 to 1. */
	fow (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) {
		weg = DSAF_SBM_CFG_WEG_0_WEG + 0x80 * i;
		dsaf_set_dev_bit(dsaf_dev, weg, DSAF_SBM_CFG_MIB_EN_S, 0);
	}

	fow (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) {
		weg = DSAF_SBM_CFG_WEG_0_WEG + 0x80 * i;
		dsaf_set_dev_bit(dsaf_dev, weg, DSAF_SBM_CFG_MIB_EN_S, 1);
	}

	/* waitint fow aww sbm enabwe finished */
	fow (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) {
		wead_cnt = 0;
		weg = DSAF_SBM_CFG_WEG_0_WEG + 0x80 * i;
		do {
			udeway(1);
			sbm_cfg_mib_en = dsaf_get_dev_bit(
					dsaf_dev, weg, DSAF_SBM_CFG_MIB_EN_S);
			wead_cnt++;
		} whiwe (sbm_cfg_mib_en == 0 &&
			wead_cnt < DSAF_CFG_WEAD_CNT);

		if (sbm_cfg_mib_en == 0) {
			dev_eww(dsaf_dev->dev,
				"sbm_cfg_mib_en faiw,%s,sbm_num=%d\n",
				dsaf_dev->ae_dev.name, i);
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

/**
 * hns_dsaf_sbm_bp_ww_cfg - config sbm
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_sbm_bp_ww_cfg(stwuct dsaf_device *dsaf_dev)
{
	u32 o_sbm_bp_cfg;
	u32 weg;
	u32 i;

	/* XGE */
	fow (i = 0; i < DSAF_XGE_NUM; i++) {
		weg = DSAF_SBM_BP_CFG_0_XGE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_COM_MAX_BUF_NUM_S, 512);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_1_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_2_XGE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_WESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_WESET_BUF_NUM_S, 128);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_3_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 110);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_WESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_WESET_BUF_NUM_NO_PFC_S, 160);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		/* fow no enabwe pfc mode */
		weg = DSAF_SBM_BP_CFG_4_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_WESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_WESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}

	/* PPE */
	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		weg = DSAF_SBM_BP_CFG_2_PPE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 10);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_WESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_WESET_BUF_NUM_S, 12);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}

	/* WoCEE */
	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		weg = DSAF_SBM_BP_CFG_2_WOCEE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 2);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAF_SBM_CFG2_WESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_WESET_BUF_NUM_S, 4);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}
}

static void hns_dsafv2_sbm_bp_ww_cfg(stwuct dsaf_device *dsaf_dev)
{
	u32 o_sbm_bp_cfg;
	u32 weg;
	u32 i;

	/* XGE */
	fow (i = 0; i < DSAFV2_SBM_XGE_CHN; i++) {
		weg = DSAF_SBM_BP_CFG_0_XGE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_S, 256);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_1_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_2_XGE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_fiewd(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_WESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_WESET_BUF_NUM_S, 128);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		weg = DSAF_SBM_BP_CFG_3_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 55);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_WESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_WESET_BUF_NUM_NO_PFC_S, 110);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);

		/* fow no enabwe pfc mode */
		weg = DSAF_SBM_BP_CFG_4_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_WESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_WESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}

	/* PPE */
	fow (i = 0; i < DSAFV2_SBM_PPE_CHN; i++) {
		weg = DSAF_SBM_BP_CFG_2_PPE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_S, 2);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_WESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_WESET_BUF_NUM_S, 3);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUW_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUW_NUM_S, 52);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}

	/* WoCEE */
	fow (i = 0; i < DASFV2_WOCEE_CWD_NUM; i++) {
		weg = DSAFV2_SBM_BP_CFG_2_WOCEE_WEG_0_WEG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_wead_dev(dsaf_dev, weg);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_WOCEE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_WOCEE_SET_BUF_NUM_S, 2);
		dsaf_set_fiewd(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_WOCEE_WESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_WOCEE_WESET_BUF_NUM_S, 4);
		dsaf_wwite_dev(dsaf_dev, weg, o_sbm_bp_cfg);
	}
}

/**
 * hns_dsaf_voq_bp_aww_thwd_cfg -  voq
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_voq_bp_aww_thwd_cfg(stwuct dsaf_device *dsaf_dev)
{
	u32 voq_bp_aww_thwd;
	u32 i;

	fow (i = 0; i < DSAF_VOQ_NUM; i++) {
		voq_bp_aww_thwd = dsaf_wead_dev(
			dsaf_dev, DSAF_VOQ_BP_AWW_THWD_0_WEG + 0x40 * i);
		if (i < DSAF_XGE_NUM) {
			dsaf_set_fiewd(voq_bp_aww_thwd,
				       DSAF_VOQ_BP_AWW_DOWNTHWD_M,
				       DSAF_VOQ_BP_AWW_DOWNTHWD_S, 930);
			dsaf_set_fiewd(voq_bp_aww_thwd,
				       DSAF_VOQ_BP_AWW_UPTHWD_M,
				       DSAF_VOQ_BP_AWW_UPTHWD_S, 950);
		} ewse {
			dsaf_set_fiewd(voq_bp_aww_thwd,
				       DSAF_VOQ_BP_AWW_DOWNTHWD_M,
				       DSAF_VOQ_BP_AWW_DOWNTHWD_S, 220);
			dsaf_set_fiewd(voq_bp_aww_thwd,
				       DSAF_VOQ_BP_AWW_UPTHWD_M,
				       DSAF_VOQ_BP_AWW_UPTHWD_S, 230);
		}
		dsaf_wwite_dev(
			dsaf_dev, DSAF_VOQ_BP_AWW_THWD_0_WEG + 0x40 * i,
			voq_bp_aww_thwd);
	}
}

static void hns_dsaf_tbw_tcam_match_cfg(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data)
{
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MATCH_CFG_W_WEG,
		       ptbw_tcam_data->tbw_tcam_data_wow);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MATCH_CFG_H_WEG,
		       ptbw_tcam_data->tbw_tcam_data_high);
}

/**
 * hns_dsaf_tbw_tcam_data_cfg - tbw
 * @dsaf_dev: dsa fabwic id
 * @ptbw_tcam_data: addw
 */
static void hns_dsaf_tbw_tcam_data_cfg(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data)
{
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_WOW_0_WEG,
		       ptbw_tcam_data->tbw_tcam_data_wow);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_HIGH_0_WEG,
		       ptbw_tcam_data->tbw_tcam_data_high);
}

/**
 * hns_dsaf_tbw_tcam_mcast_cfg - tbw
 * @dsaf_dev: dsa fabwic id
 * @mcast: addw
 */
static void hns_dsaf_tbw_tcam_mcast_cfg(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_tbw_tcam_mcast_cfg *mcast)
{
	u32 mcast_cfg4;

	mcast_cfg4 = dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_4_0_WEG);
	dsaf_set_bit(mcast_cfg4, DSAF_TBW_MCAST_CFG4_ITEM_VWD_S,
		     mcast->tbw_mcast_item_vwd);
	dsaf_set_bit(mcast_cfg4, DSAF_TBW_MCAST_CFG4_OWD_EN_S,
		     mcast->tbw_mcast_owd_en);
	dsaf_set_fiewd(mcast_cfg4, DSAF_TBW_MCAST_CFG4_VM128_112_M,
		       DSAF_TBW_MCAST_CFG4_VM128_112_S,
		       mcast->tbw_mcast_powt_msk[4]);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_4_0_WEG, mcast_cfg4);

	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_3_0_WEG,
		       mcast->tbw_mcast_powt_msk[3]);

	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_2_0_WEG,
		       mcast->tbw_mcast_powt_msk[2]);

	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_1_0_WEG,
		       mcast->tbw_mcast_powt_msk[1]);

	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_0_0_WEG,
		       mcast->tbw_mcast_powt_msk[0]);
}

/**
 * hns_dsaf_tbw_tcam_ucast_cfg - tbw
 * @dsaf_dev: dsa fabwic id
 * @tbw_tcam_ucast: addw
 */
static void hns_dsaf_tbw_tcam_ucast_cfg(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_tbw_tcam_ucast_cfg *tbw_tcam_ucast)
{
	u32 ucast_cfg1;

	ucast_cfg1 = dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_UCAST_CFG_0_WEG);
	dsaf_set_bit(ucast_cfg1, DSAF_TBW_UCAST_CFG1_MAC_DISCAWD_S,
		     tbw_tcam_ucast->tbw_ucast_mac_discawd);
	dsaf_set_bit(ucast_cfg1, DSAF_TBW_UCAST_CFG1_ITEM_VWD_S,
		     tbw_tcam_ucast->tbw_ucast_item_vwd);
	dsaf_set_bit(ucast_cfg1, DSAF_TBW_UCAST_CFG1_OWD_EN_S,
		     tbw_tcam_ucast->tbw_ucast_owd_en);
	dsaf_set_bit(ucast_cfg1, DSAF_TBW_UCAST_CFG1_DVC_S,
		     tbw_tcam_ucast->tbw_ucast_dvc);
	dsaf_set_fiewd(ucast_cfg1, DSAF_TBW_UCAST_CFG1_OUT_POWT_M,
		       DSAF_TBW_UCAST_CFG1_OUT_POWT_S,
		       tbw_tcam_ucast->tbw_ucast_out_powt);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_UCAST_CFG_0_WEG, ucast_cfg1);
}

/**
 * hns_dsaf_tbw_wine_cfg - tbw
 * @dsaf_dev: dsa fabwic id
 * @tbw_win: addw
 */
static void hns_dsaf_tbw_wine_cfg(stwuct dsaf_device *dsaf_dev,
				  stwuct dsaf_tbw_wine_cfg *tbw_win)
{
	u32 tbw_wine;

	tbw_wine = dsaf_wead_dev(dsaf_dev, DSAF_TBW_WIN_CFG_0_WEG);
	dsaf_set_bit(tbw_wine, DSAF_TBW_WINE_CFG_MAC_DISCAWD_S,
		     tbw_win->tbw_wine_mac_discawd);
	dsaf_set_bit(tbw_wine, DSAF_TBW_WINE_CFG_DVC_S,
		     tbw_win->tbw_wine_dvc);
	dsaf_set_fiewd(tbw_wine, DSAF_TBW_WINE_CFG_OUT_POWT_M,
		       DSAF_TBW_WINE_CFG_OUT_POWT_S,
		       tbw_win->tbw_wine_out_powt);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_WIN_CFG_0_WEG, tbw_wine);
}

/**
 * hns_dsaf_tbw_tcam_mcast_puw - tbw
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_tcam_mcast_puw(stwuct dsaf_device *dsaf_dev)
{
	u32 o_tbw_puw;

	o_tbw_puw = dsaf_wead_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_MCAST_VWD_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_MCAST_VWD_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
}

/**
 * hns_dsaf_tbw_wine_puw - tbw
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_wine_puw(stwuct dsaf_device *dsaf_dev)
{
	u32 tbw_puw;

	tbw_puw = dsaf_wead_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG);
	dsaf_set_bit(tbw_puw, DSAF_TBW_PUW_WINE_VWD_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, tbw_puw);
	dsaf_set_bit(tbw_puw, DSAF_TBW_PUW_WINE_VWD_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, tbw_puw);
}

/**
 * hns_dsaf_tbw_tcam_data_mcast_puw - tbw
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_tcam_data_mcast_puw(
	stwuct dsaf_device *dsaf_dev)
{
	u32 o_tbw_puw;

	o_tbw_puw = dsaf_wead_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_DATA_VWD_S, 1);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_MCAST_VWD_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_DATA_VWD_S, 0);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_MCAST_VWD_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
}

/**
 * hns_dsaf_tbw_tcam_data_ucast_puw - tbw
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_tcam_data_ucast_puw(
	stwuct dsaf_device *dsaf_dev)
{
	u32 o_tbw_puw;

	o_tbw_puw = dsaf_wead_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_DATA_VWD_S, 1);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_UCAST_VWD_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_TCAM_DATA_VWD_S, 0);
	dsaf_set_bit(o_tbw_puw, DSAF_TBW_PUW_UCAST_VWD_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_PUW_0_WEG, o_tbw_puw);
}

void hns_dsaf_set_pwomisc_mode(stwuct dsaf_device *dsaf_dev, u32 en)
{
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew) && !HNS_DSAF_IS_DEBUG(dsaf_dev))
		dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_WEG,
				 DSAF_CFG_MIX_MODE_S, !!en);
}

/**
 * hns_dsaf_tbw_stat_en - tbw
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_stat_en(stwuct dsaf_device *dsaf_dev)
{
	u32 o_tbw_ctww;

	o_tbw_ctww = dsaf_wead_dev(dsaf_dev, DSAF_TBW_DFX_CTWW_0_WEG);
	dsaf_set_bit(o_tbw_ctww, DSAF_TBW_DFX_WINE_WKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbw_ctww, DSAF_TBW_DFX_UC_WKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbw_ctww, DSAF_TBW_DFX_MC_WKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbw_ctww, DSAF_TBW_DFX_BC_WKUP_NUM_EN_S, 1);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_DFX_CTWW_0_WEG, o_tbw_ctww);
}

/**
 * hns_dsaf_wocee_bp_en - wocee back pwess enabwe
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_wocee_bp_en(stwuct dsaf_device *dsaf_dev)
{
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew))
		dsaf_set_dev_bit(dsaf_dev, DSAF_XGE_CTWW_SIG_CFG_0_WEG,
				 DSAF_FC_XGE_TX_PAUSE_S, 1);
}

/* set msk fow dsaf exception iwq*/
static void hns_dsaf_int_xge_msk_set(stwuct dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 mask_set)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_XGE_INT_MSK_0_WEG + 0x4 * chnn_num, mask_set);
}

static void hns_dsaf_int_ppe_msk_set(stwuct dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 msk_set)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_PPE_INT_MSK_0_WEG + 0x4 * chnn_num, msk_set);
}

static void hns_dsaf_int_wocee_msk_set(stwuct dsaf_device *dsaf_dev,
				       u32 chnn, u32 msk_set)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_WOCEE_INT_MSK_0_WEG + 0x4 * chnn, msk_set);
}

static void
hns_dsaf_int_tbw_msk_set(stwuct dsaf_device *dsaf_dev, u32 msk_set)
{
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_INT_MSK_0_WEG, msk_set);
}

/* cww dsaf exception iwq*/
static void hns_dsaf_int_xge_swc_cww(stwuct dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 int_swc)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_XGE_INT_SWC_0_WEG + 0x4 * chnn_num, int_swc);
}

static void hns_dsaf_int_ppe_swc_cww(stwuct dsaf_device *dsaf_dev,
				     u32 chnn, u32 int_swc)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_PPE_INT_SWC_0_WEG + 0x4 * chnn, int_swc);
}

static void hns_dsaf_int_wocee_swc_cww(stwuct dsaf_device *dsaf_dev,
				       u32 chnn, u32 int_swc)
{
	dsaf_wwite_dev(dsaf_dev,
		       DSAF_WOCEE_INT_SWC_0_WEG + 0x4 * chnn, int_swc);
}

static void hns_dsaf_int_tbw_swc_cww(stwuct dsaf_device *dsaf_dev,
				     u32 int_swc)
{
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_INT_SWC_0_WEG, int_swc);
}

/**
 * hns_dsaf_singwe_wine_tbw_cfg - INT
 * @dsaf_dev: dsa fabwic id
 * @addwess: the addwess
 * @ptbw_wine: the wine
 */
static void hns_dsaf_singwe_wine_tbw_cfg(
	stwuct dsaf_device *dsaf_dev,
	u32 addwess, stwuct dsaf_tbw_wine_cfg *ptbw_wine)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_wine_addw_cfg(dsaf_dev, addwess);

	/*Wwite Wine*/
	hns_dsaf_tbw_wine_cfg(dsaf_dev, ptbw_wine);

	/*Wwite Pwus*/
	hns_dsaf_tbw_wine_puw(dsaf_dev);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_uc_cfg - INT
 * @dsaf_dev: dsa fabwic id
 * @addwess: the addwess
 * @ptbw_tcam_data: the data
 * @ptbw_tcam_ucast: unicast
 */
static void hns_dsaf_tcam_uc_cfg(
	stwuct dsaf_device *dsaf_dev, u32 addwess,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data,
	stwuct dsaf_tbw_tcam_ucast_cfg *ptbw_tcam_ucast)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);
	/*Wwite Tcam Data*/
	hns_dsaf_tbw_tcam_data_cfg(dsaf_dev, ptbw_tcam_data);
	/*Wwite Tcam Ucast*/
	hns_dsaf_tbw_tcam_ucast_cfg(dsaf_dev, ptbw_tcam_ucast);
	/*Wwite Pwus*/
	hns_dsaf_tbw_tcam_data_ucast_puw(dsaf_dev);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_mc_cfg - cfg the tcam fow mc
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @addwess: tcam index
 * @ptbw_tcam_data: tcam data stwuct pointew
 * @ptbw_tcam_mask: tcam mask stwuct pointew, it must be nuww fow HNSv1
 * @ptbw_tcam_mcast: tcam data stwuct pointew
 */
static void hns_dsaf_tcam_mc_cfg(
	stwuct dsaf_device *dsaf_dev, u32 addwess,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_mask,
	stwuct dsaf_tbw_tcam_mcast_cfg *ptbw_tcam_mcast)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);
	/*Wwite Tcam Data*/
	hns_dsaf_tbw_tcam_data_cfg(dsaf_dev, ptbw_tcam_data);
	/*Wwite Tcam Mcast*/
	hns_dsaf_tbw_tcam_mcast_cfg(dsaf_dev, ptbw_tcam_mcast);
	/* Wwite Match Data */
	if (ptbw_tcam_mask)
		hns_dsaf_tbw_tcam_match_cfg(dsaf_dev, ptbw_tcam_mask);

	/* Wwite Puws */
	hns_dsaf_tbw_tcam_data_mcast_puw(dsaf_dev);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_uc_cfg_vague - INT
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @addwess: the addwess
 * @tcam_data: the data
 * @tcam_mask: the mask
 * @tcam_uc: the unicast data
 */
static void hns_dsaf_tcam_uc_cfg_vague(stwuct dsaf_device *dsaf_dev,
				       u32 addwess,
				       stwuct dsaf_tbw_tcam_data *tcam_data,
				       stwuct dsaf_tbw_tcam_data *tcam_mask,
				       stwuct dsaf_tbw_tcam_ucast_cfg *tcam_uc)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);
	hns_dsaf_tbw_tcam_data_cfg(dsaf_dev, tcam_data);
	hns_dsaf_tbw_tcam_ucast_cfg(dsaf_dev, tcam_uc);
	hns_dsaf_tbw_tcam_match_cfg(dsaf_dev, tcam_mask);
	hns_dsaf_tbw_tcam_data_ucast_puw(dsaf_dev);

	/*Westowe Match Data*/
	tcam_mask->tbw_tcam_data_high = 0xffffffff;
	tcam_mask->tbw_tcam_data_wow = 0xffffffff;
	hns_dsaf_tbw_tcam_match_cfg(dsaf_dev, tcam_mask);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_mc_cfg_vague - INT
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @addwess: the addwess
 * @tcam_data: the data
 * @tcam_mask: the mask
 * @tcam_mc: the muwticast data
 */
static void hns_dsaf_tcam_mc_cfg_vague(stwuct dsaf_device *dsaf_dev,
				       u32 addwess,
				       stwuct dsaf_tbw_tcam_data *tcam_data,
				       stwuct dsaf_tbw_tcam_data *tcam_mask,
				       stwuct dsaf_tbw_tcam_mcast_cfg *tcam_mc)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);
	hns_dsaf_tbw_tcam_data_cfg(dsaf_dev, tcam_data);
	hns_dsaf_tbw_tcam_mcast_cfg(dsaf_dev, tcam_mc);
	hns_dsaf_tbw_tcam_match_cfg(dsaf_dev, tcam_mask);
	hns_dsaf_tbw_tcam_data_mcast_puw(dsaf_dev);

	/*Westowe Match Data*/
	tcam_mask->tbw_tcam_data_high = 0xffffffff;
	tcam_mask->tbw_tcam_data_wow = 0xffffffff;
	hns_dsaf_tbw_tcam_match_cfg(dsaf_dev, tcam_mask);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_mc_invwd - INT
 * @dsaf_dev: dsa fabwic id
 * @addwess: the addwess
 */
static void hns_dsaf_tcam_mc_invwd(stwuct dsaf_device *dsaf_dev, u32 addwess)
{
	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);

	/*wwite tcam mcast*/
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_0_0_WEG, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_1_0_WEG, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_2_0_WEG, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_3_0_WEG, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_TBW_TCAM_MCAST_CFG_4_0_WEG, 0);

	/*Wwite Pwus*/
	hns_dsaf_tbw_tcam_mcast_puw(dsaf_dev);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

static void
hns_dsaf_tcam_addw_get(stwuct dsaf_dwv_tbw_tcam_key *mac_key, u8 *addw)
{
	addw[0] = mac_key->high.bits.mac_0;
	addw[1] = mac_key->high.bits.mac_1;
	addw[2] = mac_key->high.bits.mac_2;
	addw[3] = mac_key->high.bits.mac_3;
	addw[4] = mac_key->wow.bits.mac_4;
	addw[5] = mac_key->wow.bits.mac_5;
}

/**
 * hns_dsaf_tcam_uc_get - INT
 * @dsaf_dev: dsa fabwic id
 * @addwess: the addwess
 * @ptbw_tcam_data: the data
 * @ptbw_tcam_ucast: unicast
 */
static void hns_dsaf_tcam_uc_get(
	stwuct dsaf_device *dsaf_dev, u32 addwess,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data,
	stwuct dsaf_tbw_tcam_ucast_cfg *ptbw_tcam_ucast)
{
	u32 tcam_wead_data0;
	u32 tcam_wead_data4;

	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);

	/*wead tcam item puws*/
	hns_dsaf_tbw_tcam_woad_puw(dsaf_dev);

	/*wead tcam data*/
	ptbw_tcam_data->tbw_tcam_data_high
		= dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WDATA_HIGH_0_WEG);
	ptbw_tcam_data->tbw_tcam_data_wow
		= dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WDATA_WOW_0_WEG);

	/*wead tcam mcast*/
	tcam_wead_data0 = dsaf_wead_dev(dsaf_dev,
					DSAF_TBW_TCAM_WAM_WDATA0_0_WEG);
	tcam_wead_data4 = dsaf_wead_dev(dsaf_dev,
					DSAF_TBW_TCAM_WAM_WDATA4_0_WEG);

	ptbw_tcam_ucast->tbw_ucast_item_vwd
		= dsaf_get_bit(tcam_wead_data4,
			       DSAF_TBW_MCAST_CFG4_ITEM_VWD_S);
	ptbw_tcam_ucast->tbw_ucast_owd_en
		= dsaf_get_bit(tcam_wead_data4, DSAF_TBW_MCAST_CFG4_OWD_EN_S);
	ptbw_tcam_ucast->tbw_ucast_mac_discawd
		= dsaf_get_bit(tcam_wead_data0,
			       DSAF_TBW_UCAST_CFG1_MAC_DISCAWD_S);
	ptbw_tcam_ucast->tbw_ucast_out_powt
		= dsaf_get_fiewd(tcam_wead_data0,
				 DSAF_TBW_UCAST_CFG1_OUT_POWT_M,
				 DSAF_TBW_UCAST_CFG1_OUT_POWT_S);
	ptbw_tcam_ucast->tbw_ucast_dvc
		= dsaf_get_bit(tcam_wead_data0, DSAF_TBW_UCAST_CFG1_DVC_S);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tcam_mc_get - INT
 * @dsaf_dev: dsa fabwic id
 * @addwess: the addwess
 * @ptbw_tcam_data: the data
 * @ptbw_tcam_mcast: tcam muwticast data
 */
static void hns_dsaf_tcam_mc_get(
	stwuct dsaf_device *dsaf_dev, u32 addwess,
	stwuct dsaf_tbw_tcam_data *ptbw_tcam_data,
	stwuct dsaf_tbw_tcam_mcast_cfg *ptbw_tcam_mcast)
{
	u32 data_tmp;

	spin_wock_bh(&dsaf_dev->tcam_wock);

	/*Wwite Addw*/
	hns_dsaf_tbw_tcam_addw_cfg(dsaf_dev, addwess);

	/*wead tcam item puws*/
	hns_dsaf_tbw_tcam_woad_puw(dsaf_dev);

	/*wead tcam data*/
	ptbw_tcam_data->tbw_tcam_data_high =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WDATA_HIGH_0_WEG);
	ptbw_tcam_data->tbw_tcam_data_wow =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WDATA_WOW_0_WEG);

	/*wead tcam mcast*/
	ptbw_tcam_mcast->tbw_mcast_powt_msk[0] =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WAM_WDATA0_0_WEG);
	ptbw_tcam_mcast->tbw_mcast_powt_msk[1] =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WAM_WDATA1_0_WEG);
	ptbw_tcam_mcast->tbw_mcast_powt_msk[2] =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WAM_WDATA2_0_WEG);
	ptbw_tcam_mcast->tbw_mcast_powt_msk[3] =
		dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WAM_WDATA3_0_WEG);

	data_tmp = dsaf_wead_dev(dsaf_dev, DSAF_TBW_TCAM_WAM_WDATA4_0_WEG);
	ptbw_tcam_mcast->tbw_mcast_item_vwd =
		dsaf_get_bit(data_tmp, DSAF_TBW_MCAST_CFG4_ITEM_VWD_S);
	ptbw_tcam_mcast->tbw_mcast_owd_en =
		dsaf_get_bit(data_tmp, DSAF_TBW_MCAST_CFG4_OWD_EN_S);
	ptbw_tcam_mcast->tbw_mcast_powt_msk[4] =
		dsaf_get_fiewd(data_tmp, DSAF_TBW_MCAST_CFG4_VM128_112_M,
			       DSAF_TBW_MCAST_CFG4_VM128_112_S);

	spin_unwock_bh(&dsaf_dev->tcam_wock);
}

/**
 * hns_dsaf_tbw_wine_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_wine_init(stwuct dsaf_device *dsaf_dev)
{
	u32 i;
	/* defauwtwy set aww wineaw mac tabwe entwy wesuwting discawd */
	stwuct dsaf_tbw_wine_cfg tbw_wine[] = {{1, 0, 0} };

	fow (i = 0; i < DSAF_WINE_SUM; i++)
		hns_dsaf_singwe_wine_tbw_cfg(dsaf_dev, i, tbw_wine);
}

/**
 * hns_dsaf_tbw_tcam_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_tcam_init(stwuct dsaf_device *dsaf_dev)
{
	u32 i;
	stwuct dsaf_tbw_tcam_data tcam_data[] = {{0, 0} };
	stwuct dsaf_tbw_tcam_ucast_cfg tcam_ucast[] = {{0, 0, 0, 0, 0} };

	/*tcam tbw*/
	fow (i = 0; i < DSAF_TCAM_SUM; i++)
		hns_dsaf_tcam_uc_cfg(dsaf_dev, i, tcam_data, tcam_ucast);
}

/**
 * hns_dsaf_pfc_en_cfg - dsaf pfc pause cfg
 * @dsaf_dev: dsa fabwic id
 * @mac_id: mac contww bwock
 * @tc_en: twaffic cwass
 */
static void hns_dsaf_pfc_en_cfg(stwuct dsaf_device *dsaf_dev,
				int mac_id, int tc_en)
{
	dsaf_wwite_dev(dsaf_dev, DSAF_PFC_EN_0_WEG + mac_id * 4, tc_en);
}

static void hns_dsaf_set_pfc_pause(stwuct dsaf_device *dsaf_dev,
				   int mac_id, int tx_en, int wx_en)
{
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		if (!tx_en || !wx_en)
			dev_eww(dsaf_dev->dev, "dsaf v1 can not cwose pfc!\n");

		wetuwn;
	}

	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_WEG + mac_id * 4,
			 DSAF_PFC_PAUSE_WX_EN_B, !!wx_en);
	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_WEG + mac_id * 4,
			 DSAF_PFC_PAUSE_TX_EN_B, !!tx_en);
}

int hns_dsaf_set_wx_mac_pause_en(stwuct dsaf_device *dsaf_dev, int mac_id,
				 u32 en)
{
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		if (!en) {
			dev_eww(dsaf_dev->dev, "dsafv1 can't cwose wx_pause!\n");
			wetuwn -EINVAW;
		}
	}

	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_WEG + mac_id * 4,
			 DSAF_MAC_PAUSE_WX_EN_B, !!en);

	wetuwn 0;
}

void hns_dsaf_get_wx_mac_pause_en(stwuct dsaf_device *dsaf_dev, int mac_id,
				  u32 *en)
{
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew))
		*en = 1;
	ewse
		*en = dsaf_get_dev_bit(dsaf_dev,
				       DSAF_PAUSE_CFG_WEG + mac_id * 4,
				       DSAF_MAC_PAUSE_WX_EN_B);
}

/**
 * hns_dsaf_comm_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_comm_init(stwuct dsaf_device *dsaf_dev)
{
	u32 i;
	u32 o_dsaf_cfg;
	boow is_vew1 = AE_IS_VEW1(dsaf_dev->dsaf_vew);

	o_dsaf_cfg = dsaf_wead_dev(dsaf_dev, DSAF_CFG_0_WEG);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_EN_S, dsaf_dev->dsaf_en);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_TC_MODE_S, dsaf_dev->dsaf_tc_mode);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_CWC_EN_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_MIX_MODE_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_WOCA_ADDW_EN_S, 0);
	dsaf_wwite_dev(dsaf_dev, DSAF_CFG_0_WEG, o_dsaf_cfg);

	hns_dsaf_weg_cnt_cww_ce(dsaf_dev, 1);
	hns_dsaf_stp_powt_type_cfg(dsaf_dev, DSAF_STP_POWT_TYPE_FOWWAWD);

	/* set 22 queue pew tx ppe engine, onwy used in switch mode */
	hns_dsaf_ppe_qid_cfg(dsaf_dev, DSAF_DEFAUTW_QUEUE_NUM_PEW_PPE);

	/* set pwomisc def queue id */
	hns_dsaf_mix_def_qid_cfg(dsaf_dev);

	/* set innew woopback queue id */
	hns_dsaf_innew_qid_cfg(dsaf_dev);

	/* in non switch mode, set aww powt to access mode */
	hns_dsaf_sw_powt_type_cfg(dsaf_dev, DSAF_SW_POWT_TYPE_NON_VWAN);

	/*set dsaf pfc  to 0 fow pawseing wx pause*/
	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		hns_dsaf_pfc_en_cfg(dsaf_dev, i, 0);
		hns_dsaf_set_pfc_pause(dsaf_dev, i, is_vew1, is_vew1);
	}

	/*msk and  cww exception iwqs */
	fow (i = 0; i < DSAF_COMM_CHN; i++) {
		hns_dsaf_int_xge_swc_cww(dsaf_dev, i, 0xffffffffuw);
		hns_dsaf_int_ppe_swc_cww(dsaf_dev, i, 0xffffffffuw);
		hns_dsaf_int_wocee_swc_cww(dsaf_dev, i, 0xffffffffuw);

		hns_dsaf_int_xge_msk_set(dsaf_dev, i, 0xffffffffuw);
		hns_dsaf_int_ppe_msk_set(dsaf_dev, i, 0xffffffffuw);
		hns_dsaf_int_wocee_msk_set(dsaf_dev, i, 0xffffffffuw);
	}
	hns_dsaf_int_tbw_swc_cww(dsaf_dev, 0xffffffffuw);
	hns_dsaf_int_tbw_msk_set(dsaf_dev, 0xffffffffuw);
}

/**
 * hns_dsaf_inode_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_inode_init(stwuct dsaf_device *dsaf_dev)
{
	u32 weg;
	u32 tc_cfg;
	u32 i;

	if (dsaf_dev->dsaf_tc_mode == HWD_DSAF_4TC_MODE)
		tc_cfg = HNS_DSAF_I4TC_CFG;
	ewse
		tc_cfg = HNS_DSAF_I8TC_CFG;

	if (AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		fow (i = 0; i < DSAF_INODE_NUM; i++) {
			weg = DSAF_INODE_IN_POWT_NUM_0_WEG + 0x80 * i;
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAF_INODE_IN_POWT_NUM_M,
					   DSAF_INODE_IN_POWT_NUM_S,
					   i % DSAF_XGE_NUM);
		}
	} ewse {
		fow (i = 0; i < DSAF_POWT_TYPE_NUM; i++) {
			weg = DSAF_INODE_IN_POWT_NUM_0_WEG + 0x80 * i;
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAF_INODE_IN_POWT_NUM_M,
					   DSAF_INODE_IN_POWT_NUM_S, 0);
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAFV2_INODE_IN_POWT1_NUM_M,
					   DSAFV2_INODE_IN_POWT1_NUM_S, 1);
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAFV2_INODE_IN_POWT2_NUM_M,
					   DSAFV2_INODE_IN_POWT2_NUM_S, 2);
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAFV2_INODE_IN_POWT3_NUM_M,
					   DSAFV2_INODE_IN_POWT3_NUM_S, 3);
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAFV2_INODE_IN_POWT4_NUM_M,
					   DSAFV2_INODE_IN_POWT4_NUM_S, 4);
			dsaf_set_dev_fiewd(dsaf_dev, weg,
					   DSAFV2_INODE_IN_POWT5_NUM_M,
					   DSAFV2_INODE_IN_POWT5_NUM_S, 5);
		}
	}
	fow (i = 0; i < DSAF_INODE_NUM; i++) {
		weg = DSAF_INODE_PWI_TC_CFG_0_WEG + 0x80 * i;
		dsaf_wwite_dev(dsaf_dev, weg, tc_cfg);
	}
}

/**
 * hns_dsaf_sbm_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static int hns_dsaf_sbm_init(stwuct dsaf_device *dsaf_dev)
{
	u32 fwag;
	u32 finish_msk;
	u32 cnt = 0;
	int wet;

	if (AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		hns_dsaf_sbm_bp_ww_cfg(dsaf_dev);
		finish_msk = DSAF_SWAM_INIT_OVEW_M;
	} ewse {
		hns_dsafv2_sbm_bp_ww_cfg(dsaf_dev);
		finish_msk = DSAFV2_SWAM_INIT_OVEW_M;
	}

	/* enabwe sbm chanew, disabwe sbm chanew shcut function*/
	hns_dsaf_sbm_cfg(dsaf_dev);

	/* enabwe sbm mib */
	wet = hns_dsaf_sbm_cfg_mib_en(dsaf_dev);
	if (wet) {
		dev_eww(dsaf_dev->dev,
			"hns_dsaf_sbm_cfg_mib_en faiw,%s, wet=%d\n",
			dsaf_dev->ae_dev.name, wet);
		wetuwn wet;
	}

	/* enabwe sbm initiaw wink swam */
	hns_dsaf_sbm_wink_swam_init_en(dsaf_dev);

	do {
		usweep_wange(200, 210);/*udeway(200);*/
		fwag = dsaf_get_dev_fiewd(dsaf_dev, DSAF_SWAM_INIT_OVEW_0_WEG,
					  finish_msk, DSAF_SWAM_INIT_OVEW_S);
		cnt++;
	} whiwe (fwag != (finish_msk >> DSAF_SWAM_INIT_OVEW_S) &&
		 cnt < DSAF_CFG_WEAD_CNT);

	if (fwag != (finish_msk >> DSAF_SWAM_INIT_OVEW_S)) {
		dev_eww(dsaf_dev->dev,
			"hns_dsaf_sbm_init faiw %s, fwag=%d, cnt=%d\n",
			dsaf_dev->ae_dev.name, fwag, cnt);
		wetuwn -ENODEV;
	}

	hns_dsaf_wocee_bp_en(dsaf_dev);

	wetuwn 0;
}

/**
 * hns_dsaf_tbw_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_tbw_init(stwuct dsaf_device *dsaf_dev)
{
	hns_dsaf_tbw_stat_en(dsaf_dev);

	hns_dsaf_tbw_tcam_init(dsaf_dev);
	hns_dsaf_tbw_wine_init(dsaf_dev);
}

/**
 * hns_dsaf_voq_init - INT
 * @dsaf_dev: dsa fabwic id
 */
static void hns_dsaf_voq_init(stwuct dsaf_device *dsaf_dev)
{
	hns_dsaf_voq_bp_aww_thwd_cfg(dsaf_dev);
}

/**
 * hns_dsaf_init_hw - init dsa fabwic hawdwawe
 * @dsaf_dev: dsa fabwic device stwuct pointew
 */
static int hns_dsaf_init_hw(stwuct dsaf_device *dsaf_dev)
{
	int wet;

	dev_dbg(dsaf_dev->dev,
		"hns_dsaf_init_hw begin %s !\n", dsaf_dev->ae_dev.name);

	dsaf_dev->misc_op->dsaf_weset(dsaf_dev, 0);
	mdeway(10);
	dsaf_dev->misc_op->dsaf_weset(dsaf_dev, 1);

	hns_dsaf_comm_init(dsaf_dev);

	/*init XBAW_INODE*/
	hns_dsaf_inode_init(dsaf_dev);

	/*init SBM*/
	wet = hns_dsaf_sbm_init(dsaf_dev);
	if (wet)
		wetuwn wet;

	/*init TBW*/
	hns_dsaf_tbw_init(dsaf_dev);

	/*init VOQ*/
	hns_dsaf_voq_init(dsaf_dev);

	wetuwn 0;
}

/**
 * hns_dsaf_wemove_hw - uninit dsa fabwic hawdwawe
 * @dsaf_dev: dsa fabwic device stwuct pointew
 */
static void hns_dsaf_wemove_hw(stwuct dsaf_device *dsaf_dev)
{
	/*weset*/
	dsaf_dev->misc_op->dsaf_weset(dsaf_dev, 0);
}

/**
 * hns_dsaf_init - init dsa fabwic
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * wetuwn 0 - success , negative --faiw
 */
static int hns_dsaf_init(stwuct dsaf_device *dsaf_dev)
{
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);
	u32 i;
	int wet;

	if (HNS_DSAF_IS_DEBUG(dsaf_dev))
		wetuwn 0;

	if (AE_IS_VEW1(dsaf_dev->dsaf_vew))
		dsaf_dev->tcam_max_num = DSAF_TCAM_SUM;
	ewse
		dsaf_dev->tcam_max_num =
			DSAF_TCAM_SUM - DSAFV2_MAC_FUZZY_TCAM_NUM;

	spin_wock_init(&dsaf_dev->tcam_wock);
	wet = hns_dsaf_init_hw(dsaf_dev);
	if (wet)
		wetuwn wet;

	/* mawwoc mem fow tcam mac key(vwan+mac) */
	pwiv->soft_mac_tbw = vzawwoc(awway_size(DSAF_TCAM_SUM,
						sizeof(*pwiv->soft_mac_tbw)));
	if (!pwiv->soft_mac_tbw) {
		wet = -ENOMEM;
		goto wemove_hw;
	}

	/*aww entwy invaww */
	fow (i = 0; i < DSAF_TCAM_SUM; i++)
		(pwiv->soft_mac_tbw + i)->index = DSAF_INVAWID_ENTWY_IDX;

	wetuwn 0;

wemove_hw:
	hns_dsaf_wemove_hw(dsaf_dev);
	wetuwn wet;
}

/**
 * hns_dsaf_fwee - fwee dsa fabwic
 * @dsaf_dev: dsa fabwic device stwuct pointew
 */
static void hns_dsaf_fwee(stwuct dsaf_device *dsaf_dev)
{
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);

	hns_dsaf_wemove_hw(dsaf_dev);

	/* fwee aww mac mem */
	vfwee(pwiv->soft_mac_tbw);
	pwiv->soft_mac_tbw = NUWW;
}

/**
 * hns_dsaf_find_soft_mac_entwy - find dsa fabwic soft entwy
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @mac_key: mac entwy stwuct pointew
 */
static u16 hns_dsaf_find_soft_mac_entwy(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_dwv_tbw_tcam_key *mac_key)
{
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	u32 i;

	soft_mac_entwy = pwiv->soft_mac_tbw;
	fow (i = 0; i < dsaf_dev->tcam_max_num; i++) {
		/* invaww tab entwy */
		if ((soft_mac_entwy->index != DSAF_INVAWID_ENTWY_IDX) &&
		    (soft_mac_entwy->tcam_key.high.vaw == mac_key->high.vaw) &&
		    (soft_mac_entwy->tcam_key.wow.vaw == mac_key->wow.vaw))
			/* wetuwn find wesuwt --soft index */
			wetuwn soft_mac_entwy->index;

		soft_mac_entwy++;
	}
	wetuwn DSAF_INVAWID_ENTWY_IDX;
}

/**
 * hns_dsaf_find_empty_mac_entwy - seawch dsa fabwic soft empty-entwy
 * @dsaf_dev: dsa fabwic device stwuct pointew
 */
static u16 hns_dsaf_find_empty_mac_entwy(stwuct dsaf_device *dsaf_dev)
{
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	u32 i;

	soft_mac_entwy = pwiv->soft_mac_tbw;
	fow (i = 0; i < dsaf_dev->tcam_max_num; i++) {
		/* inv aww entwy */
		if (soft_mac_entwy->index == DSAF_INVAWID_ENTWY_IDX)
			/* wetuwn find wesuwt --soft index */
			wetuwn i;

		soft_mac_entwy++;
	}
	wetuwn DSAF_INVAWID_ENTWY_IDX;
}

/**
 * hns_dsaf_find_empty_mac_entwy_wevewse
 * seawch dsa fabwic soft empty-entwy fwom the end
 * @dsaf_dev: dsa fabwic device stwuct pointew
 */
static u16 hns_dsaf_find_empty_mac_entwy_wevewse(stwuct dsaf_device *dsaf_dev)
{
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	int i;

	soft_mac_entwy = pwiv->soft_mac_tbw + (DSAF_TCAM_SUM - 1);
	fow (i = (DSAF_TCAM_SUM - 1); i > 0; i--) {
		/* seawch aww entwy fwom end to stawt.*/
		if (soft_mac_entwy->index == DSAF_INVAWID_ENTWY_IDX)
			wetuwn i;
		soft_mac_entwy--;
	}
	wetuwn DSAF_INVAWID_ENTWY_IDX;
}

/**
 * hns_dsaf_set_mac_key - set mac key
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @mac_key: tcam key pointew
 * @vwan_id: vwan id
 * @in_powt_num: input powt num
 * @addw: mac addw
 */
static void hns_dsaf_set_mac_key(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_dwv_tbw_tcam_key *mac_key, u16 vwan_id, u8 in_powt_num,
	u8 *addw)
{
	u8 powt;

	if (dsaf_dev->dsaf_mode <= DSAF_MODE_ENABWE)
		/*DSAF mode : in powt id fixed 0*/
		powt = 0;
	ewse
		/*non-dsaf mode*/
		powt = in_powt_num;

	mac_key->high.bits.mac_0 = addw[0];
	mac_key->high.bits.mac_1 = addw[1];
	mac_key->high.bits.mac_2 = addw[2];
	mac_key->high.bits.mac_3 = addw[3];
	mac_key->wow.bits.mac_4 = addw[4];
	mac_key->wow.bits.mac_5 = addw[5];
	mac_key->wow.bits.powt_vwan = 0;
	dsaf_set_fiewd(mac_key->wow.bits.powt_vwan, DSAF_TBW_TCAM_KEY_VWAN_M,
		       DSAF_TBW_TCAM_KEY_VWAN_S, vwan_id);
	dsaf_set_fiewd(mac_key->wow.bits.powt_vwan, DSAF_TBW_TCAM_KEY_POWT_M,
		       DSAF_TBW_TCAM_KEY_POWT_S, powt);
}

/**
 * hns_dsaf_set_mac_uc_entwy - set mac uc-entwy
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @mac_entwy: uc-mac entwy
 */
int hns_dsaf_set_mac_uc_entwy(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy)
{
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	stwuct dsaf_tbw_tcam_ucast_cfg mac_data;
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy = pwiv->soft_mac_tbw;
	stwuct dsaf_tbw_tcam_data tcam_data;

	/* mac addw check */
	if (MAC_IS_AWW_ZEWOS(mac_entwy->addw) ||
	    MAC_IS_BWOADCAST(mac_entwy->addw) ||
	    MAC_IS_MUWTICAST(mac_entwy->addw)) {
		dev_eww(dsaf_dev->dev, "set_uc %s Mac %pM eww!\n",
			dsaf_dev->ae_dev.name, mac_entwy->addw);
		wetuwn -EINVAW;
	}

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entwy->in_vwan_id,
			     mac_entwy->in_powt_num, mac_entwy->addw);

	/* entwy ie exist? */
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		/*if has not inv entwy,find a empty entwy */
		entwy_index = hns_dsaf_find_empty_mac_entwy(dsaf_dev);
		if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
			/* has not empty,wetuwn ewwow */
			dev_eww(dsaf_dev->dev,
				"set_uc_entwy faiwed, %s Mac key(%#x:%#x)\n",
				dsaf_dev->ae_dev.name,
				mac_key.high.vaw, mac_key.wow.vaw);
			wetuwn -EINVAW;
		}
	}

	dev_dbg(dsaf_dev->dev,
		"set_uc_entwy, %s Mac key(%#x:%#x) entwy_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.vaw,
		mac_key.wow.vaw, entwy_index);

	/* config hawdwawe entwy */
	mac_data.tbw_ucast_item_vwd = 1;
	mac_data.tbw_ucast_mac_discawd = 0;
	mac_data.tbw_ucast_owd_en = 0;
	/* defauwt config dvc to 0 */
	mac_data.tbw_ucast_dvc = 0;
	mac_data.tbw_ucast_out_powt = mac_entwy->powt_num;
	tcam_data.tbw_tcam_data_high = mac_key.high.vaw;
	tcam_data.tbw_tcam_data_wow = mac_key.wow.vaw;

	hns_dsaf_tcam_uc_cfg(dsaf_dev, entwy_index, &tcam_data, &mac_data);

	/* config softwawe entwy */
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = entwy_index;
	soft_mac_entwy->tcam_key.high.vaw = mac_key.high.vaw;
	soft_mac_entwy->tcam_key.wow.vaw = mac_key.wow.vaw;

	wetuwn 0;
}

int hns_dsaf_wm_mac_addw(
	stwuct dsaf_device *dsaf_dev,
	stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy)
{
	u16 entwy_index;
	stwuct dsaf_tbw_tcam_ucast_cfg mac_data;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;

	/* mac addw check */
	if (!is_vawid_ethew_addw(mac_entwy->addw)) {
		dev_eww(dsaf_dev->dev, "wm_uc_addw %s Mac %pM eww!\n",
			dsaf_dev->ae_dev.name, mac_entwy->addw);
		wetuwn -EINVAW;
	}

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entwy->in_vwan_id,
			     mac_entwy->in_powt_num, mac_entwy->addw);

	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		/* can not find the tcam entwy, wetuwn 0 */
		dev_info(dsaf_dev->dev,
			 "wm_uc_addw no tcam, %s Mac key(%#x:%#x)\n",
			 dsaf_dev->ae_dev.name,
			 mac_key.high.vaw, mac_key.wow.vaw);
		wetuwn 0;
	}

	dev_dbg(dsaf_dev->dev,
		"wm_uc_addw, %s Mac key(%#x:%#x) entwy_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.vaw,
		mac_key.wow.vaw, entwy_index);

	hns_dsaf_tcam_uc_get(
			dsaf_dev, entwy_index,
			(stwuct dsaf_tbw_tcam_data *)&mac_key,
			&mac_data);

	/* unicast entwy not used wocawwy shouwd not cweaw */
	if (mac_entwy->powt_num != mac_data.tbw_ucast_out_powt)
		wetuwn -EFAUWT;

	wetuwn hns_dsaf_dew_mac_entwy(dsaf_dev,
				      mac_entwy->in_vwan_id,
				      mac_entwy->in_powt_num,
				      mac_entwy->addw);
}

static void hns_dsaf_setup_mc_mask(stwuct dsaf_device *dsaf_dev,
				   u8 powt_num, u8 *mask, u8 *addw)
{
	if (MAC_IS_BWOADCAST(addw))
		eth_bwoadcast_addw(mask);
	ewse
		memcpy(mask, dsaf_dev->mac_cb[powt_num]->mc_mask, ETH_AWEN);
}

static void hns_dsaf_mc_mask_bit_cweaw(chaw *dst, const chaw *swc)
{
	u16 *a = (u16 *)dst;
	const u16 *b = (const u16 *)swc;

	a[0] &= b[0];
	a[1] &= b[1];
	a[2] &= b[2];
}

/**
 * hns_dsaf_add_mac_mc_powt - add mac mc-powt
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @mac_entwy: mc-mac entwy
 */
int hns_dsaf_add_mac_mc_powt(stwuct dsaf_device *dsaf_dev,
			     stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy)
{
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	stwuct dsaf_dwv_tbw_tcam_key mask_key;
	stwuct dsaf_tbw_tcam_data *pmask_key = NUWW;
	stwuct dsaf_tbw_tcam_mcast_cfg mac_data;
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy = pwiv->soft_mac_tbw;
	stwuct dsaf_tbw_tcam_data tcam_data;
	u8 mc_addw[ETH_AWEN];
	int mskid;

	/*chechk mac addw */
	if (MAC_IS_AWW_ZEWOS(mac_entwy->addw)) {
		dev_eww(dsaf_dev->dev, "set_entwy faiwed,addw %pM!\n",
			mac_entwy->addw);
		wetuwn -EINVAW;
	}

	ethew_addw_copy(mc_addw, mac_entwy->addw);
	if (!AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		u8 mc_mask[ETH_AWEN];

		/* pwepawe fow key data setting */
		hns_dsaf_setup_mc_mask(dsaf_dev, mac_entwy->in_powt_num,
				       mc_mask, mac_entwy->addw);
		hns_dsaf_mc_mask_bit_cweaw(mc_addw, mc_mask);

		/* config key mask */
		hns_dsaf_set_mac_key(dsaf_dev, &mask_key,
				     0x0,
				     0xff,
				     mc_mask);

		pmask_key = (stwuct dsaf_tbw_tcam_data *)(&mask_key);
	}

	/*config key */
	hns_dsaf_set_mac_key(
		dsaf_dev, &mac_key, mac_entwy->in_vwan_id,
		mac_entwy->in_powt_num, mc_addw);

	memset(&mac_data, 0, sizeof(stwuct dsaf_tbw_tcam_mcast_cfg));

	/* check if the tcam is exist */
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		/*if hasnot , find a empty*/
		entwy_index = hns_dsaf_find_empty_mac_entwy(dsaf_dev);
		if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
			/*if hasnot empty, ewwow*/
			dev_eww(dsaf_dev->dev,
				"set_uc_entwy faiwed, %s Mac key(%#x:%#x)\n",
				dsaf_dev->ae_dev.name, mac_key.high.vaw,
				mac_key.wow.vaw);
			wetuwn -EINVAW;
		}
	} ewse {
		/* if exist, add in */
		hns_dsaf_tcam_mc_get(dsaf_dev, entwy_index, &tcam_data,
				     &mac_data);
	}

	/* config hawdwawe entwy */
	if (mac_entwy->powt_num < DSAF_SEWVICE_NW_NUM) {
		mskid = mac_entwy->powt_num;
	} ewse if (mac_entwy->powt_num >= DSAF_BASE_INNEW_POWT_NUM) {
		mskid = mac_entwy->powt_num -
			DSAF_BASE_INNEW_POWT_NUM + DSAF_SEWVICE_NW_NUM;
	} ewse {
		dev_eww(dsaf_dev->dev,
			"%s,pnum(%d)ewwow,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_entwy->powt_num,
			mac_key.high.vaw, mac_key.wow.vaw);
		wetuwn -EINVAW;
	}
	dsaf_set_bit(mac_data.tbw_mcast_powt_msk[mskid / 32], mskid % 32, 1);
	mac_data.tbw_mcast_owd_en = 0;
	mac_data.tbw_mcast_item_vwd = 1;

	dev_dbg(dsaf_dev->dev,
		"set_uc_entwy, %s Mac key(%#x:%#x) entwy_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.vaw,
		mac_key.wow.vaw, entwy_index);

	tcam_data.tbw_tcam_data_high = mac_key.high.vaw;
	tcam_data.tbw_tcam_data_wow = mac_key.wow.vaw;

	/* config mc entwy with mask */
	hns_dsaf_tcam_mc_cfg(dsaf_dev, entwy_index, &tcam_data,
			     pmask_key, &mac_data);

	/*config softwawe entwy */
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = entwy_index;
	soft_mac_entwy->tcam_key.high.vaw = mac_key.high.vaw;
	soft_mac_entwy->tcam_key.wow.vaw = mac_key.wow.vaw;

	wetuwn 0;
}

/**
 * hns_dsaf_dew_mac_entwy - dew mac mc-powt
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @vwan_id: vwian id
 * @in_powt_num: input powt num
 * @addw : mac addw
 */
int hns_dsaf_dew_mac_entwy(stwuct dsaf_device *dsaf_dev, u16 vwan_id,
			   u8 in_powt_num, u8 *addw)
{
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	stwuct dsaf_dwv_pwiv *pwiv =
	    (stwuct dsaf_dwv_pwiv *)hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy = pwiv->soft_mac_tbw;

	/*check mac addw */
	if (MAC_IS_AWW_ZEWOS(addw) || MAC_IS_BWOADCAST(addw)) {
		dev_eww(dsaf_dev->dev, "dew_entwy faiwed,addw %pM!\n",
			addw);
		wetuwn -EINVAW;
	}

	/*config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, vwan_id, in_powt_num, addw);

	/*exist ?*/
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		/*not exist, ewwow */
		dev_eww(dsaf_dev->dev,
			"dew_mac_entwy faiwed, %s Mac key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name,
			mac_key.high.vaw, mac_key.wow.vaw);
		wetuwn -EINVAW;
	}
	dev_dbg(dsaf_dev->dev,
		"dew_mac_entwy, %s Mac key(%#x:%#x) entwy_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.vaw,
		mac_key.wow.vaw, entwy_index);

	/*do dew opt*/
	hns_dsaf_tcam_mc_invwd(dsaf_dev, entwy_index);

	/*dew soft emtwy */
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = DSAF_INVAWID_ENTWY_IDX;

	wetuwn 0;
}

/**
 * hns_dsaf_dew_mac_mc_powt - dew mac mc- powt
 * @dsaf_dev: dsa fabwic device stwuct pointew
 * @mac_entwy: mac entwy
 */
int hns_dsaf_dew_mac_mc_powt(stwuct dsaf_device *dsaf_dev,
			     stwuct dsaf_dwv_mac_singwe_dest_entwy *mac_entwy)
{
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy = pwiv->soft_mac_tbw;
	u16 vwan_id;
	u8 in_powt_num;
	stwuct dsaf_tbw_tcam_mcast_cfg mac_data;
	stwuct dsaf_tbw_tcam_data tcam_data;
	int mskid;
	const u8 empty_msk[sizeof(mac_data.tbw_mcast_powt_msk)] = {0};
	stwuct dsaf_dwv_tbw_tcam_key mask_key;
	stwuct dsaf_tbw_tcam_data *pmask_key = NUWW;
	u8 mc_addw[ETH_AWEN];

	if (!(void *)mac_entwy) {
		dev_eww(dsaf_dev->dev,
			"hns_dsaf_dew_mac_mc_powt mac_entwy is NUWW\n");
		wetuwn -EINVAW;
	}

	/*check mac addw */
	if (MAC_IS_AWW_ZEWOS(mac_entwy->addw)) {
		dev_eww(dsaf_dev->dev, "dew_powt faiwed, addw %pM!\n",
			mac_entwy->addw);
		wetuwn -EINVAW;
	}

	/* awways mask vwan_id fiewd */
	ethew_addw_copy(mc_addw, mac_entwy->addw);

	if (!AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		u8 mc_mask[ETH_AWEN];

		/* pwepawe fow key data setting */
		hns_dsaf_setup_mc_mask(dsaf_dev, mac_entwy->in_powt_num,
				       mc_mask, mac_entwy->addw);
		hns_dsaf_mc_mask_bit_cweaw(mc_addw, mc_mask);

		/* config key mask */
		hns_dsaf_set_mac_key(dsaf_dev, &mask_key, 0x00, 0xff, mc_mask);

		pmask_key = (stwuct dsaf_tbw_tcam_data *)(&mask_key);
	}

	/* get key info */
	vwan_id = mac_entwy->in_vwan_id;
	in_powt_num = mac_entwy->in_powt_num;

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, vwan_id, in_powt_num, mc_addw);

	/* check if the tcam entwy is exist */
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		/*find none */
		dev_eww(dsaf_dev->dev,
			"find_soft_mac_entwy faiwed, %s Mac key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name,
			mac_key.high.vaw, mac_key.wow.vaw);
		wetuwn -EINVAW;
	}

	dev_dbg(dsaf_dev->dev,
		"dew_mac_mc_powt, %s key(%#x:%#x) index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.vaw,
		mac_key.wow.vaw, entwy_index);

	/* wead entwy */
	hns_dsaf_tcam_mc_get(dsaf_dev, entwy_index, &tcam_data, &mac_data);

	/*dew the powt*/
	if (mac_entwy->powt_num < DSAF_SEWVICE_NW_NUM) {
		mskid = mac_entwy->powt_num;
	} ewse if (mac_entwy->powt_num >= DSAF_BASE_INNEW_POWT_NUM) {
		mskid = mac_entwy->powt_num -
			DSAF_BASE_INNEW_POWT_NUM + DSAF_SEWVICE_NW_NUM;
	} ewse {
		dev_eww(dsaf_dev->dev,
			"%s,pnum(%d)ewwow,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_entwy->powt_num,
			mac_key.high.vaw, mac_key.wow.vaw);
		wetuwn -EINVAW;
	}
	dsaf_set_bit(mac_data.tbw_mcast_powt_msk[mskid / 32], mskid % 32, 0);

	/*check non powt, do dew entwy */
	if (!memcmp(mac_data.tbw_mcast_powt_msk, empty_msk,
		    sizeof(mac_data.tbw_mcast_powt_msk))) {
		hns_dsaf_tcam_mc_invwd(dsaf_dev, entwy_index);

		/* dew soft entwy */
		soft_mac_entwy += entwy_index;
		soft_mac_entwy->index = DSAF_INVAWID_ENTWY_IDX;
	} ewse { /* not zewo, just dew powt, update */
		tcam_data.tbw_tcam_data_high = mac_key.high.vaw;
		tcam_data.tbw_tcam_data_wow = mac_key.wow.vaw;

		hns_dsaf_tcam_mc_cfg(dsaf_dev, entwy_index,
				     &tcam_data,
				     pmask_key, &mac_data);
	}

	wetuwn 0;
}

int hns_dsaf_cww_mac_mc_powt(stwuct dsaf_device *dsaf_dev, u8 mac_id,
			     u8 powt_num)
{
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	stwuct dsaf_tbw_tcam_mcast_cfg mac_data;
	int wet = 0, i;

	if (HNS_DSAF_IS_DEBUG(dsaf_dev))
		wetuwn 0;

	fow (i = 0; i < DSAF_TCAM_SUM - DSAFV2_MAC_FUZZY_TCAM_NUM; i++) {
		u8 addw[ETH_AWEN];
		u8 powt;

		soft_mac_entwy = pwiv->soft_mac_tbw + i;

		hns_dsaf_tcam_addw_get(&soft_mac_entwy->tcam_key, addw);
		powt = dsaf_get_fiewd(
				soft_mac_entwy->tcam_key.wow.bits.powt_vwan,
				DSAF_TBW_TCAM_KEY_POWT_M,
				DSAF_TBW_TCAM_KEY_POWT_S);
		/* check vawid tcam mc entwy */
		if (soft_mac_entwy->index != DSAF_INVAWID_ENTWY_IDX &&
		    powt == mac_id &&
		    is_muwticast_ethew_addw(addw) &&
		    !is_bwoadcast_ethew_addw(addw)) {
			const u32 empty_msk[DSAF_POWT_MSK_NUM] = {0};
			stwuct dsaf_dwv_mac_singwe_dest_entwy mac_entwy;

			/* disabwe weceiving of this muwticast addwess fow
			 * the VF.
			 */
			ethew_addw_copy(mac_entwy.addw, addw);
			mac_entwy.in_vwan_id = dsaf_get_fiewd(
				soft_mac_entwy->tcam_key.wow.bits.powt_vwan,
				DSAF_TBW_TCAM_KEY_VWAN_M,
				DSAF_TBW_TCAM_KEY_VWAN_S);
			mac_entwy.in_powt_num = mac_id;
			mac_entwy.powt_num = powt_num;
			if (hns_dsaf_dew_mac_mc_powt(dsaf_dev, &mac_entwy)) {
				wet = -EINVAW;
				continue;
			}

			/* disabwe weceiving of this muwticast addwess fow
			 * the mac powt if aww VF awe disabwe
			 */
			hns_dsaf_tcam_mc_get(dsaf_dev, i,
					     (stwuct dsaf_tbw_tcam_data *)
					     (&soft_mac_entwy->tcam_key),
					     &mac_data);
			dsaf_set_bit(mac_data.tbw_mcast_powt_msk[mac_id / 32],
				     mac_id % 32, 0);
			if (!memcmp(mac_data.tbw_mcast_powt_msk, empty_msk,
				    sizeof(u32) * DSAF_POWT_MSK_NUM)) {
				mac_entwy.powt_num = mac_id;
				if (hns_dsaf_dew_mac_mc_powt(dsaf_dev,
							     &mac_entwy)) {
					wet = -EINVAW;
					continue;
				}
			}
		}
	}

	wetuwn wet;
}

static stwuct dsaf_device *hns_dsaf_awwoc_dev(stwuct device *dev,
					      size_t sizeof_pwiv)
{
	stwuct dsaf_device *dsaf_dev;

	dsaf_dev = devm_kzawwoc(dev,
				sizeof(*dsaf_dev) + sizeof_pwiv, GFP_KEWNEW);
	if (unwikewy(!dsaf_dev)) {
		dsaf_dev = EWW_PTW(-ENOMEM);
	} ewse {
		dsaf_dev->dev = dev;
		dev_set_dwvdata(dev, dsaf_dev);
	}

	wetuwn dsaf_dev;
}

/**
 * hns_dsaf_fwee_dev - fwee dev mem
 * @dsaf_dev: stwuct device pointew
 */
static void hns_dsaf_fwee_dev(stwuct dsaf_device *dsaf_dev)
{
	(void)dev_set_dwvdata(dsaf_dev->dev, NUWW);
}

/**
 * hns_dsaf_pfc_unit_cnt - set pfc unit count
 * @dsaf_dev: dsa fabwic id
 * @mac_id: id in use
 * @wate:  vawue awway
 */
static void hns_dsaf_pfc_unit_cnt(stwuct dsaf_device *dsaf_dev, int  mac_id,
				  enum dsaf_powt_wate_mode wate)
{
	u32 unit_cnt;

	switch (wate) {
	case DSAF_POWT_WATE_10000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOW_XGE;
		bweak;
	case DSAF_POWT_WATE_1000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOW_GE_1000;
		bweak;
	case DSAF_POWT_WATE_2500:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOW_GE_1000;
		bweak;
	defauwt:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOW_XGE;
	}

	dsaf_set_dev_fiewd(dsaf_dev,
			   (DSAF_PFC_UNIT_CNT_0_WEG + 0x4 * (u64)mac_id),
			   DSAF_PFC_UNINT_CNT_M, DSAF_PFC_UNINT_CNT_S,
			   unit_cnt);
}

/**
 * hns_dsaf_powt_wowk_wate_cfg - fifo
 * @dsaf_dev: dsa fabwic id
 * @mac_id: mac contww bwock
 * @wate_mode: vawue awway
 */
static void
hns_dsaf_powt_wowk_wate_cfg(stwuct dsaf_device *dsaf_dev, int mac_id,
			    enum dsaf_powt_wate_mode wate_mode)
{
	u32 powt_wowk_mode;

	powt_wowk_mode = dsaf_wead_dev(
		dsaf_dev, DSAF_XGE_GE_WOWK_MODE_0_WEG + 0x4 * (u64)mac_id);

	if (wate_mode == DSAF_POWT_WATE_10000)
		dsaf_set_bit(powt_wowk_mode, DSAF_XGE_GE_WOWK_MODE_S, 1);
	ewse
		dsaf_set_bit(powt_wowk_mode, DSAF_XGE_GE_WOWK_MODE_S, 0);

	dsaf_wwite_dev(dsaf_dev,
		       DSAF_XGE_GE_WOWK_MODE_0_WEG + 0x4 * (u64)mac_id,
		       powt_wowk_mode);

	hns_dsaf_pfc_unit_cnt(dsaf_dev, mac_id, wate_mode);
}

/**
 * hns_dsaf_fix_mac_mode - dsaf modify mac mode
 * @mac_cb: mac contww bwock
 */
void hns_dsaf_fix_mac_mode(stwuct hns_mac_cb *mac_cb)
{
	enum dsaf_powt_wate_mode mode;
	stwuct dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	int mac_id = mac_cb->mac_id;

	if (mac_cb->mac_type != HNAE_POWT_SEWVICE)
		wetuwn;
	if (mac_cb->phy_if == PHY_INTEWFACE_MODE_XGMII)
		mode = DSAF_POWT_WATE_10000;
	ewse
		mode = DSAF_POWT_WATE_1000;

	hns_dsaf_powt_wowk_wate_cfg(dsaf_dev, mac_id, mode);
}

static u32 hns_dsaf_get_inode_pwio_weg(int index)
{
	int base_index, offset;
	u32 base_addw = DSAF_INODE_IN_PWIO_PAUSE_BASE_WEG;

	base_index = (index + 1) / DSAF_WEG_PEW_ZONE;
	offset = (index + 1) % DSAF_WEG_PEW_ZONE;

	wetuwn base_addw + DSAF_INODE_IN_PWIO_PAUSE_BASE_OFFSET * base_index +
		DSAF_INODE_IN_PWIO_PAUSE_OFFSET * offset;
}

void hns_dsaf_update_stats(stwuct dsaf_device *dsaf_dev, u32 node_num)
{
	stwuct dsaf_hw_stats *hw_stats
		= &dsaf_dev->hw_stats[node_num];
	boow is_vew1 = AE_IS_VEW1(dsaf_dev->dsaf_vew);
	int i;
	u32 weg_tmp;

	hw_stats->pad_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_PAD_DISCAWD_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->man_pkts += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_FINAW_IN_MAN_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->wx_pkts += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_FINAW_IN_PKT_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->wx_pkt_id += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_SBM_PID_NUM_0_WEG + 0x80 * (u64)node_num);

	weg_tmp = is_vew1 ? DSAF_INODE_FINAW_IN_PAUSE_NUM_0_WEG :
			    DSAFV2_INODE_FINAW_IN_PAUSE_NUM_0_WEG;
	hw_stats->wx_pause_fwame +=
		dsaf_wead_dev(dsaf_dev, weg_tmp + 0x80 * (u64)node_num);

	hw_stats->wewease_buf_num += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_SBM_WEWS_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->sbm_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_SBM_DWOP_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->cwc_fawse += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_CWC_FAWSE_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->bp_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_BP_DISCAWD_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->wswt_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_WSWT_DISCAWD_NUM_0_WEG + 0x80 * (u64)node_num);
	hw_stats->wocaw_addw_fawse += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_WOCAW_ADDW_FAWSE_NUM_0_WEG + 0x80 * (u64)node_num);

	hw_stats->vwan_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_SW_VWAN_TAG_DISC_0_WEG + 4 * (u64)node_num);
	hw_stats->stp_dwop += dsaf_wead_dev(dsaf_dev,
		DSAF_INODE_IN_DATA_STP_DISC_0_WEG + 4 * (u64)node_num);

	/* pfc pause fwame statistics stowed in dsaf inode*/
	if ((node_num < DSAF_SEWVICE_NW_NUM) && !is_vew1) {
		fow (i = 0; i < DSAF_PWIO_NW; i++) {
			weg_tmp = hns_dsaf_get_inode_pwio_weg(i);
			hw_stats->wx_pfc[i] += dsaf_wead_dev(dsaf_dev,
				weg_tmp + 0x4 * (u64)node_num);
			hw_stats->tx_pfc[i] += dsaf_wead_dev(dsaf_dev,
				DSAF_XOD_XGE_PFC_PWIO_CNT_BASE_WEG +
				DSAF_XOD_XGE_PFC_PWIO_CNT_OFFSET * i +
				0xF0 * (u64)node_num);
		}
	}
	hw_stats->tx_pkts += dsaf_wead_dev(dsaf_dev,
		DSAF_XOD_WCVPKT_CNT_0_WEG + 0x90 * (u64)node_num);
}

/**
 *hns_dsaf_get_wegs - dump dsaf wegs
 *@ddev: dsaf device
 *@powt: powt
 *@data:data fow vawue of wegs
 */
void hns_dsaf_get_wegs(stwuct dsaf_device *ddev, u32 powt, void *data)
{
	u32 i;
	u32 j;
	u32 *p = data;
	u32 weg_tmp;
	boow is_vew1 = AE_IS_VEW1(ddev->dsaf_vew);

	/* dsaf common wegistews */
	p[0] = dsaf_wead_dev(ddev, DSAF_SWAM_INIT_OVEW_0_WEG);
	p[1] = dsaf_wead_dev(ddev, DSAF_CFG_0_WEG);
	p[2] = dsaf_wead_dev(ddev, DSAF_ECC_EWW_INVEWT_0_WEG);
	p[3] = dsaf_wead_dev(ddev, DSAF_ABNOWMAW_TIMEOUT_0_WEG);
	p[4] = dsaf_wead_dev(ddev, DSAF_FSM_TIMEOUT_0_WEG);
	p[5] = dsaf_wead_dev(ddev, DSAF_DSA_WEG_CNT_CWW_CE_WEG);
	p[6] = dsaf_wead_dev(ddev, DSAF_DSA_SBM_INF_FIFO_THWD_WEG);
	p[7] = dsaf_wead_dev(ddev, DSAF_DSA_SWAM_1BIT_ECC_SEW_WEG);
	p[8] = dsaf_wead_dev(ddev, DSAF_DSA_SWAM_1BIT_ECC_CNT_WEG);

	p[9] = dsaf_wead_dev(ddev, DSAF_PFC_EN_0_WEG + powt * 4);
	p[10] = dsaf_wead_dev(ddev, DSAF_PFC_UNIT_CNT_0_WEG + powt * 4);
	p[11] = dsaf_wead_dev(ddev, DSAF_XGE_INT_MSK_0_WEG + powt * 4);
	p[12] = dsaf_wead_dev(ddev, DSAF_XGE_INT_SWC_0_WEG + powt * 4);
	p[13] = dsaf_wead_dev(ddev, DSAF_XGE_INT_STS_0_WEG + powt * 4);
	p[14] = dsaf_wead_dev(ddev, DSAF_XGE_INT_MSK_0_WEG + powt * 4);
	p[15] = dsaf_wead_dev(ddev, DSAF_PPE_INT_MSK_0_WEG + powt * 4);
	p[16] = dsaf_wead_dev(ddev, DSAF_WOCEE_INT_MSK_0_WEG + powt * 4);
	p[17] = dsaf_wead_dev(ddev, DSAF_XGE_INT_SWC_0_WEG + powt * 4);
	p[18] = dsaf_wead_dev(ddev, DSAF_PPE_INT_SWC_0_WEG + powt * 4);
	p[19] =  dsaf_wead_dev(ddev, DSAF_WOCEE_INT_SWC_0_WEG + powt * 4);
	p[20] = dsaf_wead_dev(ddev, DSAF_XGE_INT_STS_0_WEG + powt * 4);
	p[21] = dsaf_wead_dev(ddev, DSAF_PPE_INT_STS_0_WEG + powt * 4);
	p[22] = dsaf_wead_dev(ddev, DSAF_WOCEE_INT_STS_0_WEG + powt * 4);
	p[23] = dsaf_wead_dev(ddev, DSAF_PPE_QID_CFG_0_WEG + powt * 4);

	fow (i = 0; i < DSAF_SW_POWT_NUM; i++)
		p[24 + i] = dsaf_wead_dev(ddev,
				DSAF_SW_POWT_TYPE_0_WEG + i * 4);

	p[32] = dsaf_wead_dev(ddev, DSAF_MIX_DEF_QID_0_WEG + powt * 4);

	fow (i = 0; i < DSAF_SW_POWT_NUM; i++)
		p[33 + i] = dsaf_wead_dev(ddev,
				DSAF_POWT_DEF_VWAN_0_WEG + i * 4);

	fow (i = 0; i < DSAF_TOTAW_QUEUE_NUM; i++)
		p[41 + i] = dsaf_wead_dev(ddev,
				DSAF_VM_DEF_VWAN_0_WEG + i * 4);

	/* dsaf inode wegistews */
	p[170] = dsaf_wead_dev(ddev, DSAF_INODE_CUT_THWOUGH_CFG_0_WEG);

	p[171] = dsaf_wead_dev(ddev,
			DSAF_INODE_ECC_EWW_ADDW_0_WEG + powt * 0x80);

	fow (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + powt;
		p[172 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_IN_POWT_NUM_0_WEG + j * 0x80);
		p[175 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_PWI_TC_CFG_0_WEG + j * 0x80);
		p[178 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_BP_STATUS_0_WEG + j * 0x80);
		p[181 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_PAD_DISCAWD_NUM_0_WEG + j * 0x80);
		p[184 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_FINAW_IN_MAN_NUM_0_WEG + j * 0x80);
		p[187 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_FINAW_IN_PKT_NUM_0_WEG + j * 0x80);
		p[190 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_SBM_PID_NUM_0_WEG + j * 0x80);
		weg_tmp = is_vew1 ? DSAF_INODE_FINAW_IN_PAUSE_NUM_0_WEG :
				    DSAFV2_INODE_FINAW_IN_PAUSE_NUM_0_WEG;
		p[193 + i] = dsaf_wead_dev(ddev, weg_tmp + j * 0x80);
		p[196 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_SBM_WEWS_NUM_0_WEG + j * 0x80);
		p[199 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_SBM_DWOP_NUM_0_WEG + j * 0x80);
		p[202 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_CWC_FAWSE_NUM_0_WEG + j * 0x80);
		p[205 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_BP_DISCAWD_NUM_0_WEG + j * 0x80);
		p[208 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_WSWT_DISCAWD_NUM_0_WEG + j * 0x80);
		p[211 + i] = dsaf_wead_dev(ddev,
			DSAF_INODE_WOCAW_ADDW_FAWSE_NUM_0_WEG + j * 0x80);
		p[214 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_VOQ_OVEW_NUM_0_WEG + j * 0x80);
		p[217 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_BD_SAVE_STATUS_0_WEG + j * 4);
		p[220 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_BD_OWDEW_STATUS_0_WEG + j * 4);
		p[223 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_SW_VWAN_TAG_DISC_0_WEG + j * 4);
		p[226 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_IN_DATA_STP_DISC_0_WEG + j * 4);
	}

	p[229] = dsaf_wead_dev(ddev, DSAF_INODE_GE_FC_EN_0_WEG + powt * 4);

	fow (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + powt;
		p[230 + i] = dsaf_wead_dev(ddev,
				DSAF_INODE_VC0_IN_PKT_NUM_0_WEG + j * 4);
	}

	p[233] = dsaf_wead_dev(ddev,
		DSAF_INODE_VC1_IN_PKT_NUM_0_WEG + powt * 0x80);

	/* dsaf inode wegistews */
	fow (i = 0; i < HNS_DSAF_SBM_NUM(ddev) / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + powt;
		p[234 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_CFG_WEG_0_WEG + j * 0x80);
		p[237 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CFG_0_XGE_WEG_0_WEG + j * 0x80);
		p[240 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CFG_1_WEG_0_WEG + j * 0x80);
		p[243 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CFG_2_XGE_WEG_0_WEG + j * 0x80);
		p[246 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_FWEE_CNT_0_0_WEG + j * 0x80);
		p[249 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_FWEE_CNT_1_0_WEG + j * 0x80);
		p[252 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CNT_0_0_WEG + j * 0x80);
		p[255 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CNT_1_0_WEG + j * 0x80);
		p[258 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CNT_2_0_WEG + j * 0x80);
		p[261 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CNT_3_0_WEG + j * 0x80);
		p[264 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_INEW_ST_0_WEG + j * 0x80);
		p[267 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_MIB_WEQ_FAIWED_TC_0_WEG + j * 0x80);
		p[270 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_CNT_0_WEG + j * 0x80);
		p[273 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_DWOP_CNT_0_WEG + j * 0x80);
		p[276 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_INF_OUTPOWT_CNT_0_WEG + j * 0x80);
		p[279 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC0_CNT_0_WEG + j * 0x80);
		p[282 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC1_CNT_0_WEG + j * 0x80);
		p[285 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC2_CNT_0_WEG + j * 0x80);
		p[288 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC3_CNT_0_WEG + j * 0x80);
		p[291 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC4_CNT_0_WEG + j * 0x80);
		p[294 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC5_CNT_0_WEG + j * 0x80);
		p[297 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC6_CNT_0_WEG + j * 0x80);
		p[300 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_INPOWT_TC7_CNT_0_WEG + j * 0x80);
		p[303 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_WEQ_CNT_0_WEG + j * 0x80);
		p[306 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_WNK_WEWS_CNT_0_WEG + j * 0x80);
		p[309 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CFG_3_WEG_0_WEG + j * 0x80);
		p[312 + i] = dsaf_wead_dev(ddev,
				DSAF_SBM_BP_CFG_4_WEG_0_WEG + j * 0x80);
	}

	/* dsaf onode wegistews */
	fow (i = 0; i < DSAF_XOD_NUM; i++) {
		p[315 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_TSA_TC0_TC3_CFG_0_WEG + i * 0x90);
		p[323 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_TSA_TC4_TC7_CFG_0_WEG + i * 0x90);
		p[331 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_BW_TC0_TC3_CFG_0_WEG + i * 0x90);
		p[339 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_BW_TC4_TC7_CFG_0_WEG + i * 0x90);
		p[347 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_BW_OFFSET_CFG_0_WEG + i * 0x90);
		p[355 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_ETS_TOKEN_CFG_0_WEG + i * 0x90);
	}

	p[363] = dsaf_wead_dev(ddev, DSAF_XOD_PFS_CFG_0_0_WEG + powt * 0x90);
	p[364] = dsaf_wead_dev(ddev, DSAF_XOD_PFS_CFG_1_0_WEG + powt * 0x90);
	p[365] = dsaf_wead_dev(ddev, DSAF_XOD_PFS_CFG_2_0_WEG + powt * 0x90);

	fow (i = 0; i < DSAF_XOD_BIG_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + powt;
		p[366 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_GNT_W_0_WEG + j * 0x90);
		p[369 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_GNT_H_0_WEG + j * 0x90);
		p[372 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_CONNECT_STATE_0_WEG + j * 0x90);
		p[375 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVPKT_CNT_0_WEG + j * 0x90);
		p[378 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVTC0_CNT_0_WEG + j * 0x90);
		p[381 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVTC1_CNT_0_WEG + j * 0x90);
		p[384 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVTC2_CNT_0_WEG + j * 0x90);
		p[387 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVTC3_CNT_0_WEG + j * 0x90);
		p[390 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVVC0_CNT_0_WEG + j * 0x90);
		p[393 + i] = dsaf_wead_dev(ddev,
				DSAF_XOD_WCVVC1_CNT_0_WEG + j * 0x90);
	}

	p[396] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN0_CNT_0_WEG + powt * 0x90);
	p[397] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN1_CNT_0_WEG + powt * 0x90);
	p[398] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN2_CNT_0_WEG + powt * 0x90);
	p[399] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN3_CNT_0_WEG + powt * 0x90);
	p[400] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN4_CNT_0_WEG + powt * 0x90);
	p[401] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN5_CNT_0_WEG + powt * 0x90);
	p[402] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN6_CNT_0_WEG + powt * 0x90);
	p[403] = dsaf_wead_dev(ddev,
		DSAF_XOD_XGE_WCVIN7_CNT_0_WEG + powt * 0x90);
	p[404] = dsaf_wead_dev(ddev,
		DSAF_XOD_PPE_WCVIN0_CNT_0_WEG + powt * 0x90);
	p[405] = dsaf_wead_dev(ddev,
		DSAF_XOD_PPE_WCVIN1_CNT_0_WEG + powt * 0x90);
	p[406] = dsaf_wead_dev(ddev,
		DSAF_XOD_WOCEE_WCVIN0_CNT_0_WEG + powt * 0x90);
	p[407] = dsaf_wead_dev(ddev,
		DSAF_XOD_WOCEE_WCVIN1_CNT_0_WEG + powt * 0x90);
	p[408] = dsaf_wead_dev(ddev,
		DSAF_XOD_FIFO_STATUS_0_WEG + powt * 0x90);

	/* dsaf voq wegistews */
	fow (i = 0; i < DSAF_VOQ_NUM / DSAF_COMM_CHN; i++) {
		j = (i * DSAF_COMM_CHN + powt) * 0x90;
		p[409 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_ECC_INVEWT_EN_0_WEG + j);
		p[412 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_SWAM_PKT_NUM_0_WEG + j);
		p[415 + i] = dsaf_wead_dev(ddev, DSAF_VOQ_IN_PKT_NUM_0_WEG + j);
		p[418 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_OUT_PKT_NUM_0_WEG + j);
		p[421 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_ECC_EWW_ADDW_0_WEG + j);
		p[424 + i] = dsaf_wead_dev(ddev, DSAF_VOQ_BP_STATUS_0_WEG + j);
		p[427 + i] = dsaf_wead_dev(ddev, DSAF_VOQ_SPUP_IDWE_0_WEG + j);
		p[430 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_XGE_XOD_WEQ_0_0_WEG + j);
		p[433 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_XGE_XOD_WEQ_1_0_WEG + j);
		p[436 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_PPE_XOD_WEQ_0_WEG + j);
		p[439 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_WOCEE_XOD_WEQ_0_WEG + j);
		p[442 + i] = dsaf_wead_dev(ddev,
			DSAF_VOQ_BP_AWW_THWD_0_WEG + j);
	}

	/* dsaf tbw wegistews */
	p[445] = dsaf_wead_dev(ddev, DSAF_TBW_CTWW_0_WEG);
	p[446] = dsaf_wead_dev(ddev, DSAF_TBW_INT_MSK_0_WEG);
	p[447] = dsaf_wead_dev(ddev, DSAF_TBW_INT_SWC_0_WEG);
	p[448] = dsaf_wead_dev(ddev, DSAF_TBW_INT_STS_0_WEG);
	p[449] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_ADDW_0_WEG);
	p[450] = dsaf_wead_dev(ddev, DSAF_TBW_WINE_ADDW_0_WEG);
	p[451] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_HIGH_0_WEG);
	p[452] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WOW_0_WEG);
	p[453] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_MCAST_CFG_4_0_WEG);
	p[454] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_MCAST_CFG_3_0_WEG);
	p[455] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_MCAST_CFG_2_0_WEG);
	p[456] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_MCAST_CFG_1_0_WEG);
	p[457] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_MCAST_CFG_0_0_WEG);
	p[458] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_UCAST_CFG_0_WEG);
	p[459] = dsaf_wead_dev(ddev, DSAF_TBW_WIN_CFG_0_WEG);
	p[460] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WDATA_HIGH_0_WEG);
	p[461] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WDATA_WOW_0_WEG);
	p[462] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WAM_WDATA4_0_WEG);
	p[463] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WAM_WDATA3_0_WEG);
	p[464] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WAM_WDATA2_0_WEG);
	p[465] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WAM_WDATA1_0_WEG);
	p[466] = dsaf_wead_dev(ddev, DSAF_TBW_TCAM_WAM_WDATA0_0_WEG);
	p[467] = dsaf_wead_dev(ddev, DSAF_TBW_WIN_WDATA_0_WEG);

	fow (i = 0; i < DSAF_SW_POWT_NUM; i++) {
		j = i * 0x8;
		p[468 + 2 * i] = dsaf_wead_dev(ddev,
			DSAF_TBW_DA0_MIS_INFO1_0_WEG + j);
		p[469 + 2 * i] = dsaf_wead_dev(ddev,
			DSAF_TBW_DA0_MIS_INFO0_0_WEG + j);
	}

	p[484] = dsaf_wead_dev(ddev, DSAF_TBW_SA_MIS_INFO2_0_WEG);
	p[485] = dsaf_wead_dev(ddev, DSAF_TBW_SA_MIS_INFO1_0_WEG);
	p[486] = dsaf_wead_dev(ddev, DSAF_TBW_SA_MIS_INFO0_0_WEG);
	p[487] = dsaf_wead_dev(ddev, DSAF_TBW_PUW_0_WEG);
	p[488] = dsaf_wead_dev(ddev, DSAF_TBW_OWD_WSWT_0_WEG);
	p[489] = dsaf_wead_dev(ddev, DSAF_TBW_OWD_SCAN_VAW_0_WEG);
	p[490] = dsaf_wead_dev(ddev, DSAF_TBW_DFX_CTWW_0_WEG);
	p[491] = dsaf_wead_dev(ddev, DSAF_TBW_DFX_STAT_0_WEG);
	p[492] = dsaf_wead_dev(ddev, DSAF_TBW_DFX_STAT_2_0_WEG);
	p[493] = dsaf_wead_dev(ddev, DSAF_TBW_WKUP_NUM_I_0_WEG);
	p[494] = dsaf_wead_dev(ddev, DSAF_TBW_WKUP_NUM_O_0_WEG);
	p[495] = dsaf_wead_dev(ddev, DSAF_TBW_UCAST_BCAST_MIS_INFO_0_0_WEG);

	/* dsaf othew wegistews */
	p[496] = dsaf_wead_dev(ddev, DSAF_INODE_FIFO_WW_0_WEG + powt * 0x4);
	p[497] = dsaf_wead_dev(ddev, DSAF_ONODE_FIFO_WW_0_WEG + powt * 0x4);
	p[498] = dsaf_wead_dev(ddev, DSAF_XGE_GE_WOWK_MODE_0_WEG + powt * 0x4);
	p[499] = dsaf_wead_dev(ddev,
		DSAF_XGE_APP_WX_WINK_UP_0_WEG + powt * 0x4);
	p[500] = dsaf_wead_dev(ddev, DSAF_NETPOWT_CTWW_SIG_0_WEG + powt * 0x4);
	p[501] = dsaf_wead_dev(ddev, DSAF_XGE_CTWW_SIG_CFG_0_WEG + powt * 0x4);

	if (!is_vew1)
		p[502] = dsaf_wead_dev(ddev, DSAF_PAUSE_CFG_WEG + powt * 0x4);

	/* mawk end of dsaf wegs */
	fow (i = 503; i < 504; i++)
		p[i] = 0xdddddddd;
}

static chaw *hns_dsaf_get_node_stats_stwings(chaw *data, int node,
					     stwuct dsaf_device *dsaf_dev)
{
	chaw *buff = data;
	int i;
	boow is_vew1 = AE_IS_VEW1(dsaf_dev->dsaf_vew);

	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_pad_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_manage_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wx_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wx_pkt_id", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wx_pause_fwame", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wewease_buf_num", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_sbm_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_cwc_fawse_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_bp_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wookup_wswt_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_wocaw_wswt_faiw_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_vwan_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	snpwintf(buff, ETH_GSTWING_WEN, "innod%d_stp_dwop_pkts", node);
	buff += ETH_GSTWING_WEN;
	if (node < DSAF_SEWVICE_NW_NUM && !is_vew1) {
		fow (i = 0; i < DSAF_PWIO_NW; i++) {
			snpwintf(buff + 0 * ETH_GSTWING_WEN * DSAF_PWIO_NW,
				 ETH_GSTWING_WEN, "inod%d_pfc_pwio%d_pkts",
				 node, i);
			snpwintf(buff + 1 * ETH_GSTWING_WEN * DSAF_PWIO_NW,
				 ETH_GSTWING_WEN, "onod%d_pfc_pwio%d_pkts",
				 node, i);
			buff += ETH_GSTWING_WEN;
		}
		buff += 1 * DSAF_PWIO_NW * ETH_GSTWING_WEN;
	}
	snpwintf(buff, ETH_GSTWING_WEN, "onnod%d_tx_pkts", node);
	buff += ETH_GSTWING_WEN;

	wetuwn buff;
}

static u64 *hns_dsaf_get_node_stats(stwuct dsaf_device *ddev, u64 *data,
				    int node_num)
{
	u64 *p = data;
	int i;
	stwuct dsaf_hw_stats *hw_stats = &ddev->hw_stats[node_num];
	boow is_vew1 = AE_IS_VEW1(ddev->dsaf_vew);

	p[0] = hw_stats->pad_dwop;
	p[1] = hw_stats->man_pkts;
	p[2] = hw_stats->wx_pkts;
	p[3] = hw_stats->wx_pkt_id;
	p[4] = hw_stats->wx_pause_fwame;
	p[5] = hw_stats->wewease_buf_num;
	p[6] = hw_stats->sbm_dwop;
	p[7] = hw_stats->cwc_fawse;
	p[8] = hw_stats->bp_dwop;
	p[9] = hw_stats->wswt_dwop;
	p[10] = hw_stats->wocaw_addw_fawse;
	p[11] = hw_stats->vwan_dwop;
	p[12] = hw_stats->stp_dwop;
	if (node_num < DSAF_SEWVICE_NW_NUM && !is_vew1) {
		fow (i = 0; i < DSAF_PWIO_NW; i++) {
			p[13 + i + 0 * DSAF_PWIO_NW] = hw_stats->wx_pfc[i];
			p[13 + i + 1 * DSAF_PWIO_NW] = hw_stats->tx_pfc[i];
		}
		p[29] = hw_stats->tx_pkts;
		wetuwn &p[30];
	}

	p[13] = hw_stats->tx_pkts;
	wetuwn &p[14];
}

/**
 *hns_dsaf_get_stats - get dsaf statistic
 *@ddev: dsaf device
 *@data:statistic vawue
 *@powt: powt num
 */
void hns_dsaf_get_stats(stwuct dsaf_device *ddev, u64 *data, int powt)
{
	u64 *p = data;
	int node_num = powt;

	/* fow ge/xge node info */
	p = hns_dsaf_get_node_stats(ddev, p, node_num);

	/* fow ppe node info */
	node_num = powt + DSAF_PPE_INODE_BASE;
	(void)hns_dsaf_get_node_stats(ddev, p, node_num);
}

/**
 *hns_dsaf_get_sset_count - get dsaf stwing set count
 *@dsaf_dev: dsaf device
 *@stwingset: type of vawues in data
 *wetuwn dsaf stwing name count
 */
int hns_dsaf_get_sset_count(stwuct dsaf_device *dsaf_dev, int stwingset)
{
	boow is_vew1 = AE_IS_VEW1(dsaf_dev->dsaf_vew);

	if (stwingset == ETH_SS_STATS) {
		if (is_vew1)
			wetuwn DSAF_STATIC_NUM;
		ewse
			wetuwn DSAF_V2_STATIC_NUM;
	}
	wetuwn 0;
}

/**
 *hns_dsaf_get_stwings - get dsaf stwing set
 *@stwingset:swting set index
 *@data:stwings name vawue
 *@powt:powt index
 *@dsaf_dev: dsaf device
 */
void hns_dsaf_get_stwings(int stwingset, u8 *data, int powt,
			  stwuct dsaf_device *dsaf_dev)
{
	chaw *buff = (chaw *)data;
	int node = powt;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	/* fow ge/xge node info */
	buff = hns_dsaf_get_node_stats_stwings(buff, node, dsaf_dev);

	/* fow ppe node info */
	node = powt + DSAF_PPE_INODE_BASE;
	(void)hns_dsaf_get_node_stats_stwings(buff, node, dsaf_dev);
}

/**
 *hns_dsaf_get_wegs_count - get dsaf wegs count
 *wetuwn dsaf wegs count
 */
int hns_dsaf_get_wegs_count(void)
{
	wetuwn DSAF_DUMP_WEGS_NUM;
}

static int hns_dsaf_get_powt_id(u8 powt)
{
	if (powt < DSAF_SEWVICE_NW_NUM)
		wetuwn powt;

	if (powt >= DSAF_BASE_INNEW_POWT_NUM)
		wetuwn powt - DSAF_BASE_INNEW_POWT_NUM + DSAF_SEWVICE_NW_NUM;

	wetuwn -EINVAW;
}

static void set_pwomisc_tcam_enabwe(stwuct dsaf_device *dsaf_dev, u32 powt)
{
	stwuct dsaf_tbw_tcam_ucast_cfg tbw_tcam_ucast = {0, 1, 0, 0, 0x80};
	stwuct dsaf_tbw_tcam_data tbw_tcam_data_mc = {0x01000000, powt};
	stwuct dsaf_tbw_tcam_data tbw_tcam_mask_uc = {0x01000000, 0xf};
	stwuct dsaf_tbw_tcam_mcast_cfg tbw_tcam_mcast = {0, 0, {0} };
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_tbw_tcam_data tbw_tcam_data_uc = {0, powt};
	stwuct dsaf_dwv_mac_singwe_dest_entwy mask_entwy;
	stwuct dsaf_dwv_tbw_tcam_key temp_key, mask_key;
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	stwuct hns_mac_cb *mac_cb;
	u8 addw[ETH_AWEN] = {0};
	u8 powt_num;
	int mskid;

	/* pwomisc use vague tabwe match with vwanid = 0 & macaddw = 0 */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, powt, addw);
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);
	if (entwy_index != DSAF_INVAWID_ENTWY_IDX)
		wetuwn;

	/* put pwomisc tcam entwy in the end. */
	/* 1. set pwomisc unicast vague tcam entwy. */
	entwy_index = hns_dsaf_find_empty_mac_entwy_wevewse(dsaf_dev);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		dev_eww(dsaf_dev->dev,
			"enabwe uc pwomisc faiwed (powt:%#x)\n",
			powt);
		wetuwn;
	}

	mac_cb = dsaf_dev->mac_cb[powt];
	(void)hns_mac_get_innew_powt_num(mac_cb, 0, &powt_num);
	tbw_tcam_ucast.tbw_ucast_out_powt = powt_num;

	/* config uc vague tabwe */
	hns_dsaf_tcam_uc_cfg_vague(dsaf_dev, entwy_index, &tbw_tcam_data_uc,
				   &tbw_tcam_mask_uc, &tbw_tcam_ucast);

	/* update softwawe entwy */
	soft_mac_entwy = pwiv->soft_mac_tbw;
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = entwy_index;
	soft_mac_entwy->tcam_key.high.vaw = mac_key.high.vaw;
	soft_mac_entwy->tcam_key.wow.vaw = mac_key.wow.vaw;
	/* step back to the STAWT fow mc. */
	soft_mac_entwy = pwiv->soft_mac_tbw;

	/* 2. set pwomisc muwticast vague tcam entwy. */
	entwy_index = hns_dsaf_find_empty_mac_entwy_wevewse(dsaf_dev);
	if (entwy_index == DSAF_INVAWID_ENTWY_IDX) {
		dev_eww(dsaf_dev->dev,
			"enabwe mc pwomisc faiwed (powt:%#x)\n",
			powt);
		wetuwn;
	}

	memset(&mask_entwy, 0x0, sizeof(mask_entwy));
	memset(&mask_key, 0x0, sizeof(mask_key));
	memset(&temp_key, 0x0, sizeof(temp_key));
	mask_entwy.addw[0] = 0x01;
	hns_dsaf_set_mac_key(dsaf_dev, &mask_key, mask_entwy.in_vwan_id,
			     0xf, mask_entwy.addw);
	tbw_tcam_mcast.tbw_mcast_item_vwd = 1;
	tbw_tcam_mcast.tbw_mcast_owd_en = 0;

	/* set MAC powt to handwe muwticast */
	mskid = hns_dsaf_get_powt_id(powt);
	if (mskid == -EINVAW) {
		dev_eww(dsaf_dev->dev, "%s,pnum(%d)ewwow,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, powt,
			mask_key.high.vaw, mask_key.wow.vaw);
		wetuwn;
	}
	dsaf_set_bit(tbw_tcam_mcast.tbw_mcast_powt_msk[mskid / 32],
		     mskid % 32, 1);

	/* set poow bit map to handwe muwticast */
	mskid = hns_dsaf_get_powt_id(powt_num);
	if (mskid == -EINVAW) {
		dev_eww(dsaf_dev->dev,
			"%s, poow bit map pnum(%d)ewwow,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, powt_num,
			mask_key.high.vaw, mask_key.wow.vaw);
		wetuwn;
	}
	dsaf_set_bit(tbw_tcam_mcast.tbw_mcast_powt_msk[mskid / 32],
		     mskid % 32, 1);

	memcpy(&temp_key, &mask_key, sizeof(mask_key));
	hns_dsaf_tcam_mc_cfg_vague(dsaf_dev, entwy_index, &tbw_tcam_data_mc,
				   (stwuct dsaf_tbw_tcam_data *)(&mask_key),
				   &tbw_tcam_mcast);

	/* update softwawe entwy */
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = entwy_index;
	soft_mac_entwy->tcam_key.high.vaw = temp_key.high.vaw;
	soft_mac_entwy->tcam_key.wow.vaw = temp_key.wow.vaw;
}

static void set_pwomisc_tcam_disabwe(stwuct dsaf_device *dsaf_dev, u32 powt)
{
	stwuct dsaf_tbw_tcam_data tbw_tcam_data_mc = {0x01000000, powt};
	stwuct dsaf_tbw_tcam_ucast_cfg tbw_tcam_ucast = {0, 0, 0, 0, 0};
	stwuct dsaf_tbw_tcam_mcast_cfg tbw_tcam_mcast = {0, 0, {0} };
	stwuct dsaf_dwv_pwiv *pwiv = hns_dsaf_dev_pwiv(dsaf_dev);
	stwuct dsaf_tbw_tcam_data tbw_tcam_data_uc = {0, 0};
	stwuct dsaf_tbw_tcam_data tbw_tcam_mask = {0, 0};
	stwuct dsaf_dwv_soft_mac_tbw *soft_mac_entwy;
	u16 entwy_index;
	stwuct dsaf_dwv_tbw_tcam_key mac_key;
	u8 addw[ETH_AWEN] = {0};

	/* 1. dewete uc vague tcam entwy. */
	/* pwomisc use vague tabwe match with vwanid = 0 & macaddw = 0 */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, powt, addw);
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);

	if (entwy_index == DSAF_INVAWID_ENTWY_IDX)
		wetuwn;

	/* config uc vague tabwe */
	hns_dsaf_tcam_uc_cfg_vague(dsaf_dev, entwy_index, &tbw_tcam_data_uc,
				   &tbw_tcam_mask, &tbw_tcam_ucast);
	/* update soft management tabwe. */
	soft_mac_entwy = pwiv->soft_mac_tbw;
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = DSAF_INVAWID_ENTWY_IDX;
	/* step back to the STAWT fow mc. */
	soft_mac_entwy = pwiv->soft_mac_tbw;

	/* 2. dewete mc vague tcam entwy. */
	addw[0] = 0x01;
	memset(&mac_key, 0x0, sizeof(mac_key));
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, powt, addw);
	entwy_index = hns_dsaf_find_soft_mac_entwy(dsaf_dev, &mac_key);

	if (entwy_index == DSAF_INVAWID_ENTWY_IDX)
		wetuwn;

	/* config mc vague tabwe */
	hns_dsaf_tcam_mc_cfg_vague(dsaf_dev, entwy_index, &tbw_tcam_data_mc,
				   &tbw_tcam_mask, &tbw_tcam_mcast);
	/* update soft management tabwe. */
	soft_mac_entwy += entwy_index;
	soft_mac_entwy->index = DSAF_INVAWID_ENTWY_IDX;
}

/* Wesewve the wast TCAM entwy fow pwomisc suppowt */
void hns_dsaf_set_pwomisc_tcam(stwuct dsaf_device *dsaf_dev,
			       u32 powt, boow enabwe)
{
	if (enabwe)
		set_pwomisc_tcam_enabwe(dsaf_dev, powt);
	ewse
		set_pwomisc_tcam_disabwe(dsaf_dev, powt);
}

int hns_dsaf_wait_pkt_cwean(stwuct dsaf_device *dsaf_dev, int powt)
{
	u32 vaw, vaw_tmp;
	int wait_cnt;

	if (powt >= DSAF_SEWVICE_NW_NUM)
		wetuwn 0;

	wait_cnt = 0;
	whiwe (wait_cnt++ < HNS_MAX_WAIT_CNT) {
		vaw = dsaf_wead_dev(dsaf_dev, DSAF_VOQ_IN_PKT_NUM_0_WEG +
			(powt + DSAF_XGE_NUM) * 0x40);
		vaw_tmp = dsaf_wead_dev(dsaf_dev, DSAF_VOQ_OUT_PKT_NUM_0_WEG +
			(powt + DSAF_XGE_NUM) * 0x40);
		if (vaw == vaw_tmp)
			bweak;

		usweep_wange(100, 200);
	}

	if (wait_cnt >= HNS_MAX_WAIT_CNT) {
		dev_eww(dsaf_dev->dev, "hns dsaf cwean wait timeout(%u - %u).\n",
			vaw, vaw_tmp);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/**
 * hns_dsaf_pwobe - pwobo dsaf dev
 * @pdev: dasf pwatfowm device
 * wetuwn 0 - success , negative --faiw
 */
static int hns_dsaf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dsaf_device *dsaf_dev;
	int wet;

	dsaf_dev = hns_dsaf_awwoc_dev(&pdev->dev, sizeof(stwuct dsaf_dwv_pwiv));
	if (IS_EWW(dsaf_dev)) {
		wet = PTW_EWW(dsaf_dev);
		dev_eww(&pdev->dev,
			"dsaf_pwobe dsaf_awwoc_dev faiwed, wet = %#x!\n", wet);
		wetuwn wet;
	}

	wet = hns_dsaf_get_cfg(dsaf_dev);
	if (wet)
		goto fwee_dev;

	wet = hns_dsaf_init(dsaf_dev);
	if (wet)
		goto fwee_dev;

	wet = hns_mac_init(dsaf_dev);
	if (wet)
		goto uninit_dsaf;

	wet = hns_ppe_init(dsaf_dev);
	if (wet)
		goto uninit_mac;

	wet = hns_dsaf_ae_init(dsaf_dev);
	if (wet)
		goto uninit_ppe;

	wetuwn 0;

uninit_ppe:
	hns_ppe_uninit(dsaf_dev);

uninit_mac:
	hns_mac_uninit(dsaf_dev);

uninit_dsaf:
	hns_dsaf_fwee(dsaf_dev);

fwee_dev:
	hns_dsaf_fwee_dev(dsaf_dev);

	wetuwn wet;
}

/**
 * hns_dsaf_wemove - wemove dsaf dev
 * @pdev: dasf pwatfowm device
 */
static void hns_dsaf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dsaf_device *dsaf_dev = dev_get_dwvdata(&pdev->dev);

	hns_dsaf_ae_uninit(dsaf_dev);

	hns_ppe_uninit(dsaf_dev);

	hns_mac_uninit(dsaf_dev);

	hns_dsaf_fwee(dsaf_dev);

	hns_dsaf_fwee_dev(dsaf_dev);
}

static const stwuct of_device_id g_dsaf_match[] = {
	{.compatibwe = "hisiwicon,hns-dsaf-v1"},
	{.compatibwe = "hisiwicon,hns-dsaf-v2"},
	{}
};
MODUWE_DEVICE_TABWE(of, g_dsaf_match);

static stwuct pwatfowm_dwivew g_dsaf_dwivew = {
	.pwobe = hns_dsaf_pwobe,
	.wemove_new = hns_dsaf_wemove,
	.dwivew = {
		.name = DSAF_DWV_NAME,
		.of_match_tabwe = g_dsaf_match,
		.acpi_match_tabwe = hns_dsaf_acpi_match,
	},
};

moduwe_pwatfowm_dwivew(g_dsaf_dwivew);

/**
 * hns_dsaf_woce_weset - weset dsaf and woce
 * @dsaf_fwnode: Pointew to fwamewowk node fow the dasf
 * @deweset: fawse - wequest weset , twue - dwop weset
 * wetuwn 0 - success , negative -faiw
 */
int hns_dsaf_woce_weset(stwuct fwnode_handwe *dsaf_fwnode, boow deweset)
{
	stwuct dsaf_device *dsaf_dev;
	stwuct pwatfowm_device *pdev;
	u32 mp;
	u32 sw;
	u32 cwedit;
	int i;
	static const u32 powt_map[DSAF_WOCE_CWEDIT_CHN][DSAF_WOCE_CHAN_MODE_NUM] = {
		{DSAF_WOCE_POWT_0, DSAF_WOCE_POWT_0, DSAF_WOCE_POWT_0},
		{DSAF_WOCE_POWT_1, DSAF_WOCE_POWT_0, DSAF_WOCE_POWT_0},
		{DSAF_WOCE_POWT_2, DSAF_WOCE_POWT_1, DSAF_WOCE_POWT_0},
		{DSAF_WOCE_POWT_3, DSAF_WOCE_POWT_1, DSAF_WOCE_POWT_0},
		{DSAF_WOCE_POWT_4, DSAF_WOCE_POWT_2, DSAF_WOCE_POWT_1},
		{DSAF_WOCE_POWT_4, DSAF_WOCE_POWT_2, DSAF_WOCE_POWT_1},
		{DSAF_WOCE_POWT_5, DSAF_WOCE_POWT_3, DSAF_WOCE_POWT_1},
		{DSAF_WOCE_POWT_5, DSAF_WOCE_POWT_3, DSAF_WOCE_POWT_1},
	};
	static const u32 sw_map[DSAF_WOCE_CWEDIT_CHN][DSAF_WOCE_CHAN_MODE_NUM] = {
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_0, DSAF_WOCE_SW_0},
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_1, DSAF_WOCE_SW_1},
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_0, DSAF_WOCE_SW_2},
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_1, DSAF_WOCE_SW_3},
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_0, DSAF_WOCE_SW_0},
		{DSAF_WOCE_SW_1, DSAF_WOCE_SW_1, DSAF_WOCE_SW_1},
		{DSAF_WOCE_SW_0, DSAF_WOCE_SW_0, DSAF_WOCE_SW_2},
		{DSAF_WOCE_SW_1, DSAF_WOCE_SW_1, DSAF_WOCE_SW_3},
	};

	/* find the pwatfowm device cowwesponding to fwnode */
	if (is_of_node(dsaf_fwnode)) {
		pdev = of_find_device_by_node(to_of_node(dsaf_fwnode));
	} ewse if (is_acpi_device_node(dsaf_fwnode)) {
		pdev = hns_dsaf_find_pwatfowm_device(dsaf_fwnode);
	} ewse {
		pw_eww("fwnode is neithew OF ow ACPI type\n");
		wetuwn -EINVAW;
	}

	/* check if we wewe a success in fetching pdev */
	if (!pdev) {
		pw_eww("couwdn't find pwatfowm device fow node\n");
		wetuwn -ENODEV;
	}

	/* wetwieve the dsaf_device fwom the dwivew data */
	dsaf_dev = dev_get_dwvdata(&pdev->dev);
	if (!dsaf_dev) {
		dev_eww(&pdev->dev, "dsaf_dev is NUWW\n");
		put_device(&pdev->dev);
		wetuwn -ENODEV;
	}

	/* now, make suwe we awe wunning on compatibwe SoC */
	if (AE_IS_VEW1(dsaf_dev->dsaf_vew)) {
		dev_eww(dsaf_dev->dev, "%s v1 chip doesn't suppowt WoCE!\n",
			dsaf_dev->ae_dev.name);
		put_device(&pdev->dev);
		wetuwn -ENODEV;
	}

	/* do weset ow de-weset accowding to the fwag */
	if (!deweset) {
		/* weset wocee-channews in dsaf and wocee */
		dsaf_dev->misc_op->hns_dsaf_swst_chns(dsaf_dev, DSAF_CHNS_MASK,
						      fawse);
		dsaf_dev->misc_op->hns_dsaf_woce_swst(dsaf_dev, fawse);
	} ewse {
		/* configuwe dsaf tx woce cowwespond to powt map and sw map */
		mp = dsaf_wead_dev(dsaf_dev, DSAF_WOCE_POWT_MAP_WEG);
		fow (i = 0; i < DSAF_WOCE_CWEDIT_CHN; i++)
			dsaf_set_fiewd(mp, 7 << i * 3, i * 3,
				       powt_map[i][DSAF_WOCE_6POWT_MODE]);
		dsaf_set_fiewd(mp, 3 << i * 3, i * 3, 0);
		dsaf_wwite_dev(dsaf_dev, DSAF_WOCE_POWT_MAP_WEG, mp);

		sw = dsaf_wead_dev(dsaf_dev, DSAF_WOCE_SW_MAP_WEG);
		fow (i = 0; i < DSAF_WOCE_CWEDIT_CHN; i++)
			dsaf_set_fiewd(sw, 3 << i * 2, i * 2,
				       sw_map[i][DSAF_WOCE_6POWT_MODE]);
		dsaf_wwite_dev(dsaf_dev, DSAF_WOCE_SW_MAP_WEG, sw);

		/* de-weset wocee-channews in dsaf and wocee */
		dsaf_dev->misc_op->hns_dsaf_swst_chns(dsaf_dev, DSAF_CHNS_MASK,
						      twue);
		msweep(SWST_TIME_INTEWVAW);
		dsaf_dev->misc_op->hns_dsaf_woce_swst(dsaf_dev, twue);

		/* enabwe dsaf channew wocee cwedit */
		cwedit = dsaf_wead_dev(dsaf_dev, DSAF_SBM_WOCEE_CFG_WEG_WEG);
		dsaf_set_bit(cwedit, DSAF_SBM_WOCEE_CFG_CWD_EN_B, 0);
		dsaf_wwite_dev(dsaf_dev, DSAF_SBM_WOCEE_CFG_WEG_WEG, cwedit);

		dsaf_set_bit(cwedit, DSAF_SBM_WOCEE_CFG_CWD_EN_B, 1);
		dsaf_wwite_dev(dsaf_dev, DSAF_SBM_WOCEE_CFG_WEG_WEG, cwedit);
	}

	put_device(&pdev->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW(hns_dsaf_woce_weset);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Huawei Tech. Co., Wtd.");
MODUWE_DESCWIPTION("HNS DSAF dwivew");
MODUWE_VEWSION(DSAF_MOD_VEWSION);
