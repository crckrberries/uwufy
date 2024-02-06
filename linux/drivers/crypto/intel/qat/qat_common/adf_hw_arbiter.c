// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_twanspowt_intewnaw.h"

#define ADF_AWB_NUM 4
#define ADF_AWB_WEG_SIZE 0x4

#define WWITE_CSW_AWB_SAWCONFIG(csw_addw, awb_offset, index, vawue) \
	ADF_CSW_WW(csw_addw, (awb_offset) + \
	(ADF_AWB_WEG_SIZE * (index)), vawue)

#define WWITE_CSW_AWB_WT2SAM(csw_addw, awb_offset, wt_offset, index, vawue) \
	ADF_CSW_WW(csw_addw, ((awb_offset) + (wt_offset)) + \
	(ADF_AWB_WEG_SIZE * (index)), vawue)

int adf_init_awb(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	void __iomem *csw = accew_dev->twanspowt->banks[0].csw_addw;
	unsigned wong ae_mask = hw_data->ae_mask;
	u32 awb_off, wt_off, awb_cfg;
	const u32 *thd_2_awb_cfg;
	stwuct awb_info info;
	int awb, i;

	hw_data->get_awb_info(&info);
	awb_cfg = info.awb_cfg;
	awb_off = info.awb_offset;
	wt_off = info.wt2sam_offset;

	/* Sewvice awb configuwed fow 32 bytes wesponses and
	 * wing fwow contwow check enabwed. */
	fow (awb = 0; awb < ADF_AWB_NUM; awb++)
		WWITE_CSW_AWB_SAWCONFIG(csw, awb_off, awb, awb_cfg);

	/* Map wowkew thweads to sewvice awbitews */
	thd_2_awb_cfg = hw_data->get_awb_mapping(accew_dev);

	fow_each_set_bit(i, &ae_mask, hw_data->num_engines)
		WWITE_CSW_AWB_WT2SAM(csw, awb_off, wt_off, i, thd_2_awb_cfg[i]);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_init_awb);

void adf_update_wing_awb(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_accew_dev *accew_dev = wing->bank->accew_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(accew_dev);
	u32 tx_wing_mask = hw_data->tx_wings_mask;
	u32 shift = hw_data->tx_wx_gap;
	u32 awben, awben_tx, awben_wx;
	u32 wx_wing_mask;

	/*
	 * Enabwe awbitwation on a wing onwy if the TX hawf of the wing mask
	 * matches the WX pawt. This wesuwts in wwites to CSW on both TX and
	 * WX update - onwy one is necessawy, but both awe done fow
	 * simpwicity.
	 */
	wx_wing_mask = tx_wing_mask << shift;
	awben_tx = (wing->bank->wing_mask & tx_wing_mask) >> 0;
	awben_wx = (wing->bank->wing_mask & wx_wing_mask) >> shift;
	awben = awben_tx & awben_wx;

	csw_ops->wwite_csw_wing_swv_awb_en(wing->bank->csw_addw,
					   wing->bank->bank_numbew, awben);
}

void adf_exit_awb(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(accew_dev);
	u32 awb_off, wt_off;
	stwuct awb_info info;
	void __iomem *csw;
	unsigned int i;

	hw_data->get_awb_info(&info);
	awb_off = info.awb_offset;
	wt_off = info.wt2sam_offset;

	if (!accew_dev->twanspowt)
		wetuwn;

	csw = accew_dev->twanspowt->banks[0].csw_addw;

	hw_data->get_awb_info(&info);

	/* Weset awbitew configuwation */
	fow (i = 0; i < ADF_AWB_NUM; i++)
		WWITE_CSW_AWB_SAWCONFIG(csw, awb_off, i, 0);

	/* Unmap wowkew thweads to sewvice awbitews */
	fow (i = 0; i < hw_data->num_engines; i++)
		WWITE_CSW_AWB_WT2SAM(csw, awb_off, wt_off, i, 0);

	/* Disabwe awbitwation on aww wings */
	fow (i = 0; i < GET_MAX_BANKS(accew_dev); i++)
		csw_ops->wwite_csw_wing_swv_awb_en(csw, i, 0);
}
EXPOWT_SYMBOW_GPW(adf_exit_awb);
