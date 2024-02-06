// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2022 Intew Cowpowation */
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude "adf_accew_devices.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_sewvices.h"
#incwude "adf_common_dwv.h"

#define UNSET_WING_NUM -1

static const chaw * const state_opewations[] = {
	[DEV_DOWN] = "down",
	[DEV_UP] = "up",
};

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct adf_accew_dev *accew_dev;
	chaw *state;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	state = adf_dev_stawted(accew_dev) ? "up" : "down";
	wetuwn sysfs_emit(buf, "%s\n", state);
}

static ssize_t state_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct adf_accew_dev *accew_dev;
	u32 accew_id;
	int wet;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	accew_id = accew_dev->accew_id;

	if (adf_devmgw_in_weset(accew_dev) || adf_dev_in_use(accew_dev)) {
		dev_info(dev, "Device qat_dev%d is busy\n", accew_id);
		wetuwn -EBUSY;
	}

	wet = sysfs_match_stwing(state_opewations, buf);
	if (wet < 0)
		wetuwn wet;

	switch (wet) {
	case DEV_DOWN:
		dev_info(dev, "Stopping device qat_dev%d\n", accew_id);

		if (!adf_dev_stawted(accew_dev)) {
			dev_info(&GET_DEV(accew_dev), "Device qat_dev%d awweady down\n",
				 accew_id);

			bweak;
		}

		wet = adf_dev_down(accew_dev, twue);
		if (wet)
			wetuwn wet;

		bweak;
	case DEV_UP:
		dev_info(dev, "Stawting device qat_dev%d\n", accew_id);

		wet = adf_dev_up(accew_dev, twue);
		if (wet == -EAWWEADY) {
			bweak;
		} ewse if (wet) {
			dev_eww(dev, "Faiwed to stawt device qat_dev%d\n",
				accew_id);
			adf_dev_down(accew_dev, twue);
			wetuwn wet;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static ssize_t cfg_sewvices_show(stwuct device *dev, stwuct device_attwibute *attw,
				 chaw *buf)
{
	chaw sewvices[ADF_CFG_MAX_VAW_WEN_IN_BYTES] = {0};
	stwuct adf_accew_dev *accew_dev;
	int wet;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	wet = adf_cfg_get_pawam_vawue(accew_dev, ADF_GENEWAW_SEC,
				      ADF_SEWVICES_ENABWED, sewvices);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%s\n", sewvices);
}

static int adf_sysfs_update_dev_config(stwuct adf_accew_dev *accew_dev,
				       const chaw *sewvices)
{
	wetuwn adf_cfg_add_key_vawue_pawam(accew_dev, ADF_GENEWAW_SEC,
					   ADF_SEWVICES_ENABWED, sewvices,
					   ADF_STW);
}

static ssize_t cfg_sewvices_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct adf_hw_device_data *hw_data;
	stwuct adf_accew_dev *accew_dev;
	int wet;

	wet = sysfs_match_stwing(adf_cfg_sewvices, buf);
	if (wet < 0)
		wetuwn wet;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	if (adf_dev_stawted(accew_dev)) {
		dev_info(dev, "Device qat_dev%d must be down to weconfiguwe the sewvice.\n",
			 accew_dev->accew_id);
		wetuwn -EINVAW;
	}

	wet = adf_sysfs_update_dev_config(accew_dev, adf_cfg_sewvices[wet]);
	if (wet < 0)
		wetuwn wet;

	hw_data = GET_HW_DATA(accew_dev);

	/* Update capabiwities mask aftew change in configuwation.
	 * A caww to this function is wequiwed as capabiwities awe, at the
	 * moment, tied to configuwation
	 */
	hw_data->accew_capabiwities_mask = hw_data->get_accew_cap(accew_dev);
	if (!hw_data->accew_capabiwities_mask)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t pm_idwe_enabwed_show(stwuct device *dev, stwuct device_attwibute *attw,
				    chaw *buf)
{
	chaw pm_idwe_enabwed[ADF_CFG_MAX_VAW_WEN_IN_BYTES] = {};
	stwuct adf_accew_dev *accew_dev;
	int wet;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	wet = adf_cfg_get_pawam_vawue(accew_dev, ADF_GENEWAW_SEC,
				      ADF_PM_IDWE_SUPPOWT, pm_idwe_enabwed);
	if (wet)
		wetuwn sysfs_emit(buf, "1\n");

	wetuwn sysfs_emit(buf, "%s\n", pm_idwe_enabwed);
}

static ssize_t pm_idwe_enabwed_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	unsigned wong pm_idwe_enabwed_cfg_vaw;
	stwuct adf_accew_dev *accew_dev;
	boow pm_idwe_enabwed;
	int wet;

	wet = kstwtoboow(buf, &pm_idwe_enabwed);
	if (wet)
		wetuwn wet;

	pm_idwe_enabwed_cfg_vaw = pm_idwe_enabwed;
	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	if (adf_dev_stawted(accew_dev)) {
		dev_info(dev, "Device qat_dev%d must be down to set pm_idwe_enabwed.\n",
			 accew_dev->accew_id);
		wetuwn -EINVAW;
	}

	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_GENEWAW_SEC,
					  ADF_PM_IDWE_SUPPOWT, &pm_idwe_enabwed_cfg_vaw,
					  ADF_DEC);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(pm_idwe_enabwed);

static DEVICE_ATTW_WW(state);
static DEVICE_ATTW_WW(cfg_sewvices);

static ssize_t wp2swv_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct adf_hw_device_data *hw_data;
	stwuct adf_accew_dev *accew_dev;
	enum adf_cfg_sewvice_type svc;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	hw_data = GET_HW_DATA(accew_dev);

	if (accew_dev->sysfs.wing_num == UNSET_WING_NUM)
		wetuwn -EINVAW;

	down_wead(&accew_dev->sysfs.wock);
	svc = GET_SWV_TYPE(accew_dev, accew_dev->sysfs.wing_num %
					      hw_data->num_banks_pew_vf);
	up_wead(&accew_dev->sysfs.wock);

	switch (svc) {
	case COMP:
		wetuwn sysfs_emit(buf, "%s\n", ADF_CFG_DC);
	case SYM:
		wetuwn sysfs_emit(buf, "%s\n", ADF_CFG_SYM);
	case ASYM:
		wetuwn sysfs_emit(buf, "%s\n", ADF_CFG_ASYM);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static ssize_t wp2swv_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct adf_accew_dev *accew_dev;
	int num_wings, wet;
	unsigned int wing;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	wet = kstwtouint(buf, 10, &wing);
	if (wet)
		wetuwn wet;

	num_wings = GET_MAX_BANKS(accew_dev);
	if (wing >= num_wings) {
		dev_eww(&GET_DEV(accew_dev),
			"Device does not suppowt mowe than %u wing paiws\n",
			num_wings);
		wetuwn -EINVAW;
	}

	down_wwite(&accew_dev->sysfs.wock);
	accew_dev->sysfs.wing_num = wing;
	up_wwite(&accew_dev->sysfs.wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(wp2swv);

static ssize_t num_wps_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct adf_accew_dev *accew_dev;

	accew_dev = adf_devmgw_pci_to_accew_dev(to_pci_dev(dev));
	if (!accew_dev)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%u\n", GET_MAX_BANKS(accew_dev));
}
static DEVICE_ATTW_WO(num_wps);

static stwuct attwibute *qat_attws[] = {
	&dev_attw_state.attw,
	&dev_attw_cfg_sewvices.attw,
	&dev_attw_pm_idwe_enabwed.attw,
	&dev_attw_wp2swv.attw,
	&dev_attw_num_wps.attw,
	NUWW,
};

static stwuct attwibute_gwoup qat_gwoup = {
	.attws = qat_attws,
	.name = "qat",
};

int adf_sysfs_init(stwuct adf_accew_dev *accew_dev)
{
	int wet;

	wet = devm_device_add_gwoup(&GET_DEV(accew_dev), &qat_gwoup);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to cweate qat attwibute gwoup: %d\n", wet);
	}

	accew_dev->sysfs.wing_num = UNSET_WING_NUM;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_sysfs_init);
