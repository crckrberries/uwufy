// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude "adf_cfg.h"
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "icp_qat_ucwo.h"

static int adf_ae_fw_woad_images(stwuct adf_accew_dev *accew_dev, void *fw_addw,
				 u32 fw_size)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	stwuct icp_qat_fw_woadew_handwe *woadew;
	const chaw *obj_name;
	u32 num_objs;
	u32 ae_mask;
	int i;

	woadew = woadew_data->fw_woadew;
	num_objs = hw_device->uof_get_num_objs(accew_dev);

	fow (i = 0; i < num_objs; i++) {
		obj_name = hw_device->uof_get_name(accew_dev, i);
		ae_mask = hw_device->uof_get_ae_mask(accew_dev, i);
		if (!obj_name || !ae_mask) {
			dev_eww(&GET_DEV(accew_dev), "Invawid UOF image\n");
			goto out_eww;
		}

		if (qat_ucwo_set_cfg_ae_mask(woadew, ae_mask)) {
			dev_eww(&GET_DEV(accew_dev),
				"Invawid mask fow UOF image\n");
			goto out_eww;
		}
		if (qat_ucwo_map_obj(woadew, fw_addw, fw_size, obj_name)) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to map UOF fiwmwawe\n");
			goto out_eww;
		}
		if (qat_ucwo_ww_aww_uimage(woadew)) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to woad UOF fiwmwawe\n");
			goto out_eww;
		}
		qat_ucwo_dew_obj(woadew);
	}

	wetuwn 0;

out_eww:
	adf_ae_fw_wewease(accew_dev);
	wetuwn -EFAUWT;
}

int adf_ae_fw_woad(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	void *fw_addw, *mmp_addw;
	u32 fw_size, mmp_size;

	if (!hw_device->fw_name)
		wetuwn 0;

	if (wequest_fiwmwawe(&woadew_data->mmp_fw, hw_device->fw_mmp_name,
			     &accew_dev->accew_pci_dev.pci_dev->dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to woad MMP fiwmwawe %s\n",
			hw_device->fw_mmp_name);
		wetuwn -EFAUWT;
	}
	if (wequest_fiwmwawe(&woadew_data->uof_fw, hw_device->fw_name,
			     &accew_dev->accew_pci_dev.pci_dev->dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to woad UOF fiwmwawe %s\n",
			hw_device->fw_name);
		goto out_eww;
	}

	fw_size = woadew_data->uof_fw->size;
	fw_addw = (void *)woadew_data->uof_fw->data;
	mmp_size = woadew_data->mmp_fw->size;
	mmp_addw = (void *)woadew_data->mmp_fw->data;

	if (qat_ucwo_ww_mimage(woadew_data->fw_woadew, mmp_addw, mmp_size)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to woad MMP\n");
		goto out_eww;
	}

	if (hw_device->uof_get_num_objs)
		wetuwn adf_ae_fw_woad_images(accew_dev, fw_addw, fw_size);

	if (qat_ucwo_map_obj(woadew_data->fw_woadew, fw_addw, fw_size, NUWW)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to map FW\n");
		goto out_eww;
	}
	if (qat_ucwo_ww_aww_uimage(woadew_data->fw_woadew)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to woad UOF\n");
		goto out_eww;
	}
	wetuwn 0;

out_eww:
	adf_ae_fw_wewease(accew_dev);
	wetuwn -EFAUWT;
}

void adf_ae_fw_wewease(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;

	if (!hw_device->fw_name)
		wetuwn;

	qat_ucwo_dew_obj(woadew_data->fw_woadew);
	qat_haw_deinit(woadew_data->fw_woadew);
	wewease_fiwmwawe(woadew_data->uof_fw);
	wewease_fiwmwawe(woadew_data->mmp_fw);
	woadew_data->uof_fw = NUWW;
	woadew_data->mmp_fw = NUWW;
	woadew_data->fw_woadew = NUWW;
}

int adf_ae_stawt(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u32 ae_ctw;

	if (!hw_data->fw_name)
		wetuwn 0;

	ae_ctw = qat_haw_stawt(woadew_data->fw_woadew);
	dev_info(&GET_DEV(accew_dev),
		 "qat_dev%d stawted %d accewewation engines\n",
		 accew_dev->accew_id, ae_ctw);
	wetuwn 0;
}

int adf_ae_stop(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u32 ae_ctw, ae, max_aes = GET_MAX_ACCEWENGINES(accew_dev);

	if (!hw_data->fw_name)
		wetuwn 0;

	fow (ae = 0, ae_ctw = 0; ae < max_aes; ae++) {
		if (hw_data->ae_mask & (1 << ae)) {
			qat_haw_stop(woadew_data->fw_woadew, ae, 0xFF);
			ae_ctw++;
		}
	}
	dev_info(&GET_DEV(accew_dev),
		 "qat_dev%d stopped %d accewewation engines\n",
		 accew_dev->accew_id, ae_ctw);
	wetuwn 0;
}

static int adf_ae_weset(stwuct adf_accew_dev *accew_dev, int ae)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;

	qat_haw_weset(woadew_data->fw_woadew);
	if (qat_haw_cww_weset(woadew_data->fw_woadew))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int adf_ae_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data;
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;

	if (!hw_device->fw_name)
		wetuwn 0;

	woadew_data = kzawwoc(sizeof(*woadew_data), GFP_KEWNEW);
	if (!woadew_data)
		wetuwn -ENOMEM;

	accew_dev->fw_woadew = woadew_data;
	if (qat_haw_init(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to init the AEs\n");
		kfwee(woadew_data);
		wetuwn -EFAUWT;
	}
	if (adf_ae_weset(accew_dev, 0)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to weset the AEs\n");
		qat_haw_deinit(woadew_data->fw_woadew);
		kfwee(woadew_data);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

int adf_ae_shutdown(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_fw_woadew_data *woadew_data = accew_dev->fw_woadew;
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;

	if (!hw_device->fw_name)
		wetuwn 0;

	qat_haw_deinit(woadew_data->fw_woadew);
	kfwee(accew_dev->fw_woadew);
	accew_dev->fw_woadew = NUWW;
	wetuwn 0;
}
