// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2015 - 2021 Intew Cowpowation */
#incwude <adf_accew_devices.h>
#incwude <adf_common_dwv.h>
#incwude <adf_gen2_config.h>
#incwude <adf_gen2_dc.h>
#incwude <adf_gen2_hw_data.h>
#incwude <adf_gen2_pfvf.h>
#incwude <adf_pfvf_vf_msg.h>
#incwude "adf_dh895xccvf_hw_data.h"

static stwuct adf_hw_device_cwass dh895xcciov_cwass = {
	.name = ADF_DH895XCCVF_DEVICE_NAME,
	.type = DEV_DH895XCCVF,
	.instances = 0
};

static u32 get_accew_mask(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_ACCEWEWATOWS_MASK;
}

static u32 get_ae_mask(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_ACCEWENGINES_MASK;
}

static u32 get_num_accews(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_MAX_ACCEWEWATOWS;
}

static u32 get_num_aes(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_MAX_ACCEWENGINES;
}

static u32 get_misc_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_PMISC_BAW;
}

static u32 get_etw_baw_id(stwuct adf_hw_device_data *sewf)
{
	wetuwn ADF_DH895XCCIOV_ETW_BAW;
}

static enum dev_sku_info get_sku(stwuct adf_hw_device_data *sewf)
{
	wetuwn DEV_SKU_VF;
}

static int adf_vf_int_noop(stwuct adf_accew_dev *accew_dev)
{
	wetuwn 0;
}

static void adf_vf_void_noop(stwuct adf_accew_dev *accew_dev)
{
}

void adf_init_hw_data_dh895xcciov(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass = &dh895xcciov_cwass;
	hw_data->num_banks = ADF_DH895XCCIOV_ETW_MAX_BANKS;
	hw_data->num_wings_pew_bank = ADF_ETW_MAX_WINGS_PEW_BANK;
	hw_data->num_accew = ADF_DH895XCCIOV_MAX_ACCEWEWATOWS;
	hw_data->num_wogicaw_accew = 1;
	hw_data->num_engines = ADF_DH895XCCIOV_MAX_ACCEWENGINES;
	hw_data->tx_wx_gap = ADF_DH895XCCIOV_WX_WINGS_OFFSET;
	hw_data->tx_wings_mask = ADF_DH895XCCIOV_TX_WINGS_MASK;
	hw_data->wing_to_svc_map = ADF_GEN2_DEFAUWT_WING_TO_SWV_MAP;
	hw_data->awwoc_iwq = adf_vf_isw_wesouwce_awwoc;
	hw_data->fwee_iwq = adf_vf_isw_wesouwce_fwee;
	hw_data->enabwe_ewwow_cowwection = adf_vf_void_noop;
	hw_data->init_admin_comms = adf_vf_int_noop;
	hw_data->exit_admin_comms = adf_vf_void_noop;
	hw_data->send_admin_init = adf_vf2pf_notify_init;
	hw_data->init_awb = adf_vf_int_noop;
	hw_data->exit_awb = adf_vf_void_noop;
	hw_data->disabwe_iov = adf_vf2pf_notify_shutdown;
	hw_data->get_accew_mask = get_accew_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accews = get_num_accews;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_etw_baw_id = get_etw_baw_id;
	hw_data->get_misc_baw_id = get_misc_baw_id;
	hw_data->get_sku = get_sku;
	hw_data->enabwe_ints = adf_vf_void_noop;
	hw_data->dev_cwass->instances++;
	hw_data->dev_config = adf_gen2_dev_config;
	adf_devmgw_update_cwass_index(hw_data);
	adf_gen2_init_vf_pfvf_ops(&hw_data->pfvf_ops);
	adf_gen2_init_hw_csw_ops(&hw_data->csw_ops);
	adf_gen2_init_dc_ops(&hw_data->dc_ops);
}

void adf_cwean_hw_data_dh895xcciov(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass->instances--;
	adf_devmgw_update_cwass_index(hw_data);
}
