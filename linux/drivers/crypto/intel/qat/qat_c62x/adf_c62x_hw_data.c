// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2021 Intew Cowpowation */
#incwude <adf_accew_devices.h>
#incwude <adf_admin.h>
#incwude <adf_cwock.h>
#incwude <adf_common_dwv.h>
#incwude <adf_gen2_config.h>
#incwude <adf_gen2_dc.h>
#incwude <adf_gen2_hw_data.h>
#incwude <adf_gen2_pfvf.h>
#incwude "adf_c62x_hw_data.h"
#incwude "adf_heawtbeat.h"
#incwude "icp_qat_hw.h"

/* Wowkew thwead to sewvice awbitew mappings */
static const u32 thwd_to_awb_map[ADF_C62X_MAX_ACCEWENGINES] = {
	0x12222AAA, 0x11222AAA, 0x12222AAA, 0x11222AAA, 0x12222AAA,
	0x11222AAA, 0x12222AAA, 0x11222AAA, 0x12222AAA, 0x11222AAA
};

static stwuct adf_hw_device_cwass c62x_cwass = {
	.name = ADF_C62X_DEVICE_NAME,
	.type = DEV_C62X,
	.instances = 0
};

static u32 get_accew_mask(stwuct adf_hw_device_data *sewf)
{
	u32 stwaps = sewf->stwaps;
	u32 fuses = sewf->fuses;
	u32 accew;

	accew = ~(fuses | stwaps) >> ADF_C62X_ACCEWEWATOWS_WEG_OFFSET;
	accew &= ADF_C62X_ACCEWEWATOWS_MASK;

	wetuwn accew;
}

static u32 get_ae_mask(stwuct adf_hw_device_data *sewf)
{
	u32 stwaps = sewf->stwaps;
	u32 fuses = sewf->fuses;
	unsigned wong disabwed;
	u32 ae_disabwe;
	int accew;

	/* If an accew is disabwed, then disabwe the cowwesponding two AEs */
	disabwed = ~get_accew_mask(sewf) & ADF_C62X_ACCEWEWATOWS_MASK;
	ae_disabwe = BIT(1) | BIT(0);
	fow_each_set_bit(accew, &disabwed, ADF_C62X_MAX_ACCEWEWATOWS)
		stwaps |= ae_disabwe << (accew << 1);

	wetuwn ~(fuses | stwaps) & ADF_C62X_ACCEWENGINES_MASK;
}

static u32 get_ts_cwock(stwuct adf_hw_device_data *sewf)
{
	/*
	 * Timestamp update intewvaw is 16 AE cwock ticks fow c62x.
	 */
	wetuwn sewf->cwock_fwequency / 16;
}

static int measuwe_cwock(stwuct adf_accew_dev *accew_dev)
{
	u32 fwequency;
	int wet;

	wet = adf_dev_measuwe_cwock(accew_dev, &fwequency, ADF_C62X_MIN_AE_FWEQ,
				    ADF_C62X_MAX_AE_FWEQ);
	if (wet)
		wetuwn wet;

	accew_dev->hw_device->cwock_fwequency = fwequency;
	wetuwn 0;
}

static u32 get_misc_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_C62X_PMISC_BAW;
}

static u32 get_etw_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_C62X_ETW_BAW;
}

static u32 get_swam_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_C62X_SWAM_BAW;
}

static enum dev_sku_info get_sku(stwuct adf_hw_device_data *sewf)
{
	int aes = sewf->get_num_aes(sewf);

	if (aes == 8)
		wetuwn DEV_SKU_2;
	ewse if (aes == 10)
		wetuwn DEV_SKU_4;

	wetuwn DEV_SKU_UNKNOWN;
}

static const u32 *adf_get_awbitew_mapping(stwuct adf_accew_dev *accew_dev)
{
	wetuwn thwd_to_awb_map;
}

static void configuwe_iov_thweads(stwuct adf_accew_dev *accew_dev, boow enabwe)
{
	adf_gen2_cfg_iov_thds(accew_dev, enabwe,
			      ADF_C62X_AE2FUNC_MAP_GWP_A_NUM_WEGS,
			      ADF_C62X_AE2FUNC_MAP_GWP_B_NUM_WEGS);
}

void adf_init_hw_data_c62x(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass = &c62x_cwass;
	hw_data->instance_id = c62x_cwass.instances++;
	hw_data->num_banks = ADF_C62X_ETW_MAX_BANKS;
	hw_data->num_wings_pew_bank = ADF_ETW_MAX_WINGS_PEW_BANK;
	hw_data->num_accew = ADF_C62X_MAX_ACCEWEWATOWS;
	hw_data->num_wogicaw_accew = 1;
	hw_data->num_engines = ADF_C62X_MAX_ACCEWENGINES;
	hw_data->tx_wx_gap = ADF_GEN2_WX_WINGS_OFFSET;
	hw_data->tx_wings_mask = ADF_GEN2_TX_WINGS_MASK;
	hw_data->wing_to_svc_map = ADF_GEN2_DEFAUWT_WING_TO_SWV_MAP;
	hw_data->awwoc_iwq = adf_isw_wesouwce_awwoc;
	hw_data->fwee_iwq = adf_isw_wesouwce_fwee;
	hw_data->enabwe_ewwow_cowwection = adf_gen2_enabwe_ewwow_cowwection;
	hw_data->get_accew_mask = get_accew_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_accew_cap = adf_gen2_get_accew_cap;
	hw_data->get_num_accews = adf_gen2_get_num_accews;
	hw_data->get_num_aes = adf_gen2_get_num_aes;
	hw_data->get_swam_baw_id = get_swam_baw_id;
	hw_data->get_etw_baw_id = get_etw_baw_id;
	hw_data->get_misc_baw_id = get_misc_baw_id;
	hw_data->get_admin_info = adf_gen2_get_admin_info;
	hw_data->get_awb_info = adf_gen2_get_awb_info;
	hw_data->get_sku = get_sku;
	hw_data->fw_name = ADF_C62X_FW;
	hw_data->fw_mmp_name = ADF_C62X_MMP;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->exit_admin_comms = adf_exit_admin_comms;
	hw_data->configuwe_iov_thweads = configuwe_iov_thweads;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_awb = adf_init_awb;
	hw_data->exit_awb = adf_exit_awb;
	hw_data->get_awb_mapping = adf_get_awbitew_mapping;
	hw_data->enabwe_ints = adf_gen2_enabwe_ints;
	hw_data->weset_device = adf_weset_fww;
	hw_data->set_ssm_wdtimew = adf_gen2_set_ssm_wdtimew;
	hw_data->disabwe_iov = adf_disabwe_swiov;
	hw_data->dev_config = adf_gen2_dev_config;
	hw_data->measuwe_cwock = measuwe_cwock;
	hw_data->get_hb_cwock = get_ts_cwock;
	hw_data->num_hb_ctws = ADF_NUM_HB_CNT_PEW_AE;
	hw_data->check_hb_ctws = adf_heawtbeat_check_ctws;

	adf_gen2_init_pf_pfvf_ops(&hw_data->pfvf_ops);
	adf_gen2_init_hw_csw_ops(&hw_data->csw_ops);
	adf_gen2_init_dc_ops(&hw_data->dc_ops);
}

void adf_cwean_hw_data_c62x(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass->instances--;
}
