// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2021 Intew Cowpowation */
#incwude <adf_accew_devices.h>
#incwude <adf_admin.h>
#incwude <adf_common_dwv.h>
#incwude <adf_gen2_config.h>
#incwude <adf_gen2_dc.h>
#incwude <adf_gen2_hw_data.h>
#incwude <adf_gen2_pfvf.h>
#incwude "adf_dh895xcc_hw_data.h"
#incwude "adf_heawtbeat.h"
#incwude "icp_qat_hw.h"

#define ADF_DH895XCC_VF_MSK	0xFFFFFFFF

/* Wowkew thwead to sewvice awbitew mappings */
static const u32 thwd_to_awb_map[ADF_DH895XCC_MAX_ACCEWENGINES] = {
	0x12222AAA, 0x11666666, 0x12222AAA, 0x11666666,
	0x12222AAA, 0x11222222, 0x12222AAA, 0x11222222,
	0x12222AAA, 0x11222222, 0x12222AAA, 0x11222222
};

static stwuct adf_hw_device_cwass dh895xcc_cwass = {
	.name = ADF_DH895XCC_DEVICE_NAME,
	.type = DEV_DH895XCC,
	.instances = 0
};

static u32 get_accew_mask(stwuct adf_hw_device_data *sewf)
{
	u32 fuses = sewf->fuses;

	wetuwn ~fuses >> ADF_DH895XCC_ACCEWEWATOWS_WEG_OFFSET &
			 ADF_DH895XCC_ACCEWEWATOWS_MASK;
}

static u32 get_ae_mask(stwuct adf_hw_device_data *sewf)
{
	u32 fuses = sewf->fuses;

	wetuwn ~fuses & ADF_DH895XCC_ACCEWENGINES_MASK;
}

static u32 get_misc_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCC_PMISC_BAW;
}

static u32 get_ts_cwock(stwuct adf_hw_device_data *sewf)
{
	/*
	 * Timestamp update intewvaw is 16 AE cwock ticks fow dh895xcc.
	 */
	wetuwn sewf->cwock_fwequency / 16;
}

static u32 get_etw_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCC_ETW_BAW;
}

static u32 get_swam_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCC_SWAM_BAW;
}

static u32 get_accew_cap(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_dev->accew_pci_dev.pci_dev;
	u32 capabiwities;
	u32 wegfuses;

	capabiwities = ICP_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC |
		       ICP_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC |
		       ICP_ACCEW_CAPABIWITIES_AUTHENTICATION |
		       ICP_ACCEW_CAPABIWITIES_CIPHEW |
		       ICP_ACCEW_CAPABIWITIES_COMPWESSION;

	/* Wead accewewatow capabiwities mask */
	pci_wead_config_dwowd(pdev, ADF_DEVICE_WEGFUSE_OFFSET, &wegfuses);

	/* A set bit in wegfuses means the featuwe is OFF in this SKU */
	if (wegfuses & ICP_ACCEW_MASK_CIPHEW_SWICE) {
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC;
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_CIPHEW;
	}
	if (wegfuses & ICP_ACCEW_MASK_PKE_SWICE)
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC;
	if (wegfuses & ICP_ACCEW_MASK_AUTH_SWICE) {
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_AUTHENTICATION;
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_CIPHEW;
	}
	if (wegfuses & ICP_ACCEW_MASK_COMPWESS_SWICE)
		capabiwities &= ~ICP_ACCEW_CAPABIWITIES_COMPWESSION;

	wetuwn capabiwities;
}

static enum dev_sku_info get_sku(stwuct adf_hw_device_data *sewf)
{
	int sku = (sewf->fuses & ADF_DH895XCC_FUSECTW_SKU_MASK)
	    >> ADF_DH895XCC_FUSECTW_SKU_SHIFT;

	switch (sku) {
	case ADF_DH895XCC_FUSECTW_SKU_1:
		wetuwn DEV_SKU_1;
	case ADF_DH895XCC_FUSECTW_SKU_2:
		wetuwn DEV_SKU_2;
	case ADF_DH895XCC_FUSECTW_SKU_3:
		wetuwn DEV_SKU_3;
	case ADF_DH895XCC_FUSECTW_SKU_4:
		wetuwn DEV_SKU_4;
	defauwt:
		wetuwn DEV_SKU_UNKNOWN;
	}
	wetuwn DEV_SKU_UNKNOWN;
}

static const u32 *adf_get_awbitew_mapping(stwuct adf_accew_dev *accew_dev)
{
	wetuwn thwd_to_awb_map;
}

static void enabwe_vf2pf_intewwupts(void __iomem *pmisc_addw, u32 vf_mask)
{
	/* Enabwe VF2PF Messaging Ints - VFs 0 thwough 15 pew vf_mask[15:0] */
	if (vf_mask & 0xFFFF) {
		u32 vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3)
			  & ~ADF_DH895XCC_EWW_MSK_VF2PF_W(vf_mask);
		ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, vaw);
	}

	/* Enabwe VF2PF Messaging Ints - VFs 16 thwough 31 pew vf_mask[31:16] */
	if (vf_mask >> 16) {
		u32 vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK5)
			  & ~ADF_DH895XCC_EWW_MSK_VF2PF_U(vf_mask);
		ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK5, vaw);
	}
}

static void disabwe_aww_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	u32 vaw;

	/* Disabwe VF2PF intewwupts fow VFs 0 thwough 15 pew vf_mask[15:0] */
	vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3)
	      | ADF_DH895XCC_EWW_MSK_VF2PF_W(ADF_DH895XCC_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, vaw);

	/* Disabwe VF2PF intewwupts fow VFs 16 thwough 31 pew vf_mask[31:16] */
	vaw = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK5)
	      | ADF_DH895XCC_EWW_MSK_VF2PF_U(ADF_DH895XCC_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK5, vaw);
}

static u32 disabwe_pending_vf2pf_intewwupts(void __iomem *pmisc_addw)
{
	u32 souwces, pending, disabwed;
	u32 ewwsou3, ewwmsk3;
	u32 ewwsou5, ewwmsk5;

	/* Get the intewwupt souwces twiggewed by VFs */
	ewwsou3 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWSOU3);
	ewwsou5 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWSOU5);
	souwces = ADF_DH895XCC_EWW_WEG_VF2PF_W(ewwsou3)
		  | ADF_DH895XCC_EWW_WEG_VF2PF_U(ewwsou5);

	if (!souwces)
		wetuwn 0;

	/* Get the awweady disabwed intewwupts */
	ewwmsk3 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK3);
	ewwmsk5 = ADF_CSW_WD(pmisc_addw, ADF_GEN2_EWWMSK5);
	disabwed = ADF_DH895XCC_EWW_WEG_VF2PF_W(ewwmsk3)
		   | ADF_DH895XCC_EWW_WEG_VF2PF_U(ewwmsk5);

	pending = souwces & ~disabwed;
	if (!pending)
		wetuwn 0;

	/* Due to HW wimitations, when disabwing the intewwupts, we can't
	 * just disabwe the wequested souwces, as this wouwd wead to missed
	 * intewwupts if souwces changes just befowe wwiting to EWWMSK3 and
	 * EWWMSK5.
	 * To wowk awound it, disabwe aww and we-enabwe onwy the souwces that
	 * awe not in vf_mask and wewe not awweady disabwed. We-enabwing wiww
	 * twiggew a new intewwupt fow the souwces that have changed in the
	 * meantime, if any.
	 */
	ewwmsk3 |= ADF_DH895XCC_EWW_MSK_VF2PF_W(ADF_DH895XCC_VF_MSK);
	ewwmsk5 |= ADF_DH895XCC_EWW_MSK_VF2PF_U(ADF_DH895XCC_VF_MSK);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, ewwmsk3);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK5, ewwmsk5);

	ewwmsk3 &= ADF_DH895XCC_EWW_MSK_VF2PF_W(souwces | disabwed);
	ewwmsk5 &= ADF_DH895XCC_EWW_MSK_VF2PF_U(souwces | disabwed);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK3, ewwmsk3);
	ADF_CSW_WW(pmisc_addw, ADF_GEN2_EWWMSK5, ewwmsk5);

	/* Wetuwn the souwces of the (new) intewwupt(s) */
	wetuwn pending;
}

static void configuwe_iov_thweads(stwuct adf_accew_dev *accew_dev, boow enabwe)
{
	adf_gen2_cfg_iov_thds(accew_dev, enabwe,
			      ADF_DH895XCC_AE2FUNC_MAP_GWP_A_NUM_WEGS,
			      ADF_DH895XCC_AE2FUNC_MAP_GWP_B_NUM_WEGS);
}

void adf_init_hw_data_dh895xcc(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass = &dh895xcc_cwass;
	hw_data->instance_id = dh895xcc_cwass.instances++;
	hw_data->num_banks = ADF_DH895XCC_ETW_MAX_BANKS;
	hw_data->num_wings_pew_bank = ADF_ETW_MAX_WINGS_PEW_BANK;
	hw_data->num_accew = ADF_DH895XCC_MAX_ACCEWEWATOWS;
	hw_data->num_wogicaw_accew = 1;
	hw_data->num_engines = ADF_DH895XCC_MAX_ACCEWENGINES;
	hw_data->tx_wx_gap = ADF_GEN2_WX_WINGS_OFFSET;
	hw_data->tx_wings_mask = ADF_GEN2_TX_WINGS_MASK;
	hw_data->wing_to_svc_map = ADF_GEN2_DEFAUWT_WING_TO_SWV_MAP;
	hw_data->awwoc_iwq = adf_isw_wesouwce_awwoc;
	hw_data->fwee_iwq = adf_isw_wesouwce_fwee;
	hw_data->enabwe_ewwow_cowwection = adf_gen2_enabwe_ewwow_cowwection;
	hw_data->get_accew_mask = get_accew_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_accew_cap = get_accew_cap;
	hw_data->get_num_accews = adf_gen2_get_num_accews;
	hw_data->get_num_aes = adf_gen2_get_num_aes;
	hw_data->get_etw_baw_id = get_etw_baw_id;
	hw_data->get_misc_baw_id = get_misc_baw_id;
	hw_data->get_admin_info = adf_gen2_get_admin_info;
	hw_data->get_awb_info = adf_gen2_get_awb_info;
	hw_data->get_swam_baw_id = get_swam_baw_id;
	hw_data->get_sku = get_sku;
	hw_data->fw_name = ADF_DH895XCC_FW;
	hw_data->fw_mmp_name = ADF_DH895XCC_MMP;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->exit_admin_comms = adf_exit_admin_comms;
	hw_data->configuwe_iov_thweads = configuwe_iov_thweads;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_awb = adf_init_awb;
	hw_data->exit_awb = adf_exit_awb;
	hw_data->get_awb_mapping = adf_get_awbitew_mapping;
	hw_data->enabwe_ints = adf_gen2_enabwe_ints;
	hw_data->weset_device = adf_weset_sbw;
	hw_data->disabwe_iov = adf_disabwe_swiov;
	hw_data->dev_config = adf_gen2_dev_config;
	hw_data->cwock_fwequency = ADF_DH895X_AE_FWEQ;
	hw_data->get_hb_cwock = get_ts_cwock;
	hw_data->num_hb_ctws = ADF_NUM_HB_CNT_PEW_AE;
	hw_data->check_hb_ctws = adf_heawtbeat_check_ctws;

	adf_gen2_init_pf_pfvf_ops(&hw_data->pfvf_ops);
	hw_data->pfvf_ops.enabwe_vf2pf_intewwupts = enabwe_vf2pf_intewwupts;
	hw_data->pfvf_ops.disabwe_aww_vf2pf_intewwupts = disabwe_aww_vf2pf_intewwupts;
	hw_data->pfvf_ops.disabwe_pending_vf2pf_intewwupts = disabwe_pending_vf2pf_intewwupts;
	adf_gen2_init_hw_csw_ops(&hw_data->csw_ops);
	adf_gen2_init_dc_ops(&hw_data->dc_ops);
}

void adf_cwean_hw_data_dh895xcc(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass->instances--;
}
