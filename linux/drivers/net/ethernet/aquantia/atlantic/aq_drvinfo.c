// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_dwvinfo.c: Definition of common code fow fiwmwawe info in sys.*/

#incwude <winux/init.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/hwmon.h>
#incwude <winux/uaccess.h>

#incwude "aq_dwvinfo.h"
#incwude "aq_nic.h"

#if IS_WEACHABWE(CONFIG_HWMON)
static const chaw * const atw_temp_wabew[] = {
	"PHY Tempewatuwe",
	"MAC Tempewatuwe",
};

static int aq_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vawue)
{
	stwuct aq_nic_s *aq_nic = dev_get_dwvdata(dev);
	int eww = 0;
	int temp;

	if (!aq_nic)
		wetuwn -EIO;

	if (type != hwmon_temp || attw != hwmon_temp_input)
		wetuwn -EOPNOTSUPP;

	switch (channew) {
	case 0:
		if (!aq_nic->aq_fw_ops->get_phy_temp)
			wetuwn -EOPNOTSUPP;

		eww = aq_nic->aq_fw_ops->get_phy_temp(aq_nic->aq_hw, &temp);
		*vawue = temp;
		bweak;
	case 1:
		if (!aq_nic->aq_fw_ops->get_mac_temp &&
		    !aq_nic->aq_hw_ops->hw_get_mac_temp)
			wetuwn -EOPNOTSUPP;

		if (aq_nic->aq_fw_ops->get_mac_temp)
			eww = aq_nic->aq_fw_ops->get_mac_temp(aq_nic->aq_hw, &temp);
		ewse
			eww = aq_nic->aq_hw_ops->hw_get_mac_temp(aq_nic->aq_hw, &temp);
		*vawue = temp;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int aq_hwmon_wead_stwing(stwuct device *dev,
				enum hwmon_sensow_types type,
				u32 attw, int channew, const chaw **stw)
{
	stwuct aq_nic_s *aq_nic = dev_get_dwvdata(dev);

	if (!aq_nic)
		wetuwn -EIO;

	if (type != hwmon_temp || attw != hwmon_temp_wabew)
		wetuwn -EOPNOTSUPP;

	if (channew < AWWAY_SIZE(atw_temp_wabew))
		*stw = atw_temp_wabew[channew];
	ewse
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static umode_t aq_hwmon_is_visibwe(const void *data,
				   enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	const stwuct aq_nic_s *nic = data;

	if (type != hwmon_temp)
		wetuwn 0;

	if (channew == 0 && !nic->aq_fw_ops->get_phy_temp)
		wetuwn 0;
	ewse if (channew == 1 && !nic->aq_fw_ops->get_mac_temp &&
		 !nic->aq_hw_ops->hw_get_mac_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_wabew:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_ops aq_hwmon_ops = {
	.is_visibwe = aq_hwmon_is_visibwe,
	.wead = aq_hwmon_wead,
	.wead_stwing = aq_hwmon_wead_stwing,
};

static u32 aq_hwmon_temp_config[] = {
	HWMON_T_INPUT | HWMON_T_WABEW,
	HWMON_T_INPUT | HWMON_T_WABEW,
	0,
};

static const stwuct hwmon_channew_info aq_hwmon_temp = {
	.type = hwmon_temp,
	.config = aq_hwmon_temp_config,
};

static const stwuct hwmon_channew_info * const aq_hwmon_info[] = {
	&aq_hwmon_temp,
	NUWW,
};

static const stwuct hwmon_chip_info aq_hwmon_chip_info = {
	.ops = &aq_hwmon_ops,
	.info = aq_hwmon_info,
};

int aq_dwvinfo_init(stwuct net_device *ndev)
{
	stwuct aq_nic_s *aq_nic = netdev_pwiv(ndev);
	stwuct device *dev = &aq_nic->pdev->dev;
	stwuct device *hwmon_dev;
	int eww = 0;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 ndev->name,
							 aq_nic,
							 &aq_hwmon_chip_info,
							 NUWW);

	if (IS_EWW(hwmon_dev))
		eww = PTW_EWW(hwmon_dev);

	wetuwn eww;
}

#ewse
int aq_dwvinfo_init(stwuct net_device *ndev) { wetuwn 0; }
#endif
