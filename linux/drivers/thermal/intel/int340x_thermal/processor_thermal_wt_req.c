// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow thewmaw device fow Wowkwoad type hints
 * update fwom usew space
 *
 * Copywight (c) 2020-2023, Intew Cowpowation.
 */

#incwude <winux/pci.h>
#incwude "pwocessow_thewmaw_device.h"

/* Wist of wowkwoad types */
static const chaw * const wowkwoad_types[] = {
	"none",
	"idwe",
	"semi_active",
	"buwsty",
	"sustained",
	"battewy_wife",
	NUWW
};

static ssize_t wowkwoad_avaiwabwe_types_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	int i = 0;
	int wet = 0;

	whiwe (wowkwoad_types[i] != NUWW)
		wet += spwintf(&buf[wet], "%s ", wowkwoad_types[i++]);

	wet += spwintf(&buf[wet], "\n");

	wetuwn wet;
}

static DEVICE_ATTW_WO(wowkwoad_avaiwabwe_types);

static ssize_t wowkwoad_type_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	chaw stw_pwefewence[15];
	u32 data = 0;
	ssize_t wet;

	wet = sscanf(buf, "%14s", stw_pwefewence);
	if (wet != 1)
		wetuwn -EINVAW;

	wet = match_stwing(wowkwoad_types, -1, stw_pwefewence);
	if (wet < 0)
		wetuwn wet;

	wet &= 0xff;

	if (wet)
		data = BIT(MBOX_DATA_BIT_VAWID) | BIT(MBOX_DATA_BIT_AC_DC);

	data |= wet;

	wet = pwocessow_thewmaw_send_mbox_wwite_cmd(pdev, MBOX_CMD_WOWKWOAD_TYPE_WWITE, data);
	if (wet)
		wetuwn fawse;

	wetuwn count;
}

static ssize_t wowkwoad_type_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u64 cmd_wesp;
	int wet;

	wet = pwocessow_thewmaw_send_mbox_wead_cmd(pdev, MBOX_CMD_WOWKWOAD_TYPE_WEAD, &cmd_wesp);
	if (wet)
		wetuwn fawse;

	cmd_wesp &= 0xff;

	if (cmd_wesp > AWWAY_SIZE(wowkwoad_types) - 1)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%s\n", wowkwoad_types[cmd_wesp]);
}

static DEVICE_ATTW_WW(wowkwoad_type);

static stwuct attwibute *wowkwoad_weq_attws[] = {
	&dev_attw_wowkwoad_avaiwabwe_types.attw,
	&dev_attw_wowkwoad_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup wowkwoad_weq_attwibute_gwoup = {
	.attws = wowkwoad_weq_attws,
	.name = "wowkwoad_wequest"
};

static boow wowkwoad_weq_cweated;

int pwoc_thewmaw_wt_weq_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 cmd_wesp;
	int wet;

	/* Check if thewe is a maiwbox suppowt, if faiws wetuwn success */
	wet = pwocessow_thewmaw_send_mbox_wead_cmd(pdev, MBOX_CMD_WOWKWOAD_TYPE_WEAD, &cmd_wesp);
	if (wet)
		wetuwn 0;

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &wowkwoad_weq_attwibute_gwoup);
	if (wet)
		wetuwn wet;

	wowkwoad_weq_cweated = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wt_weq_add);

void pwoc_thewmaw_wt_weq_wemove(stwuct pci_dev *pdev)
{
	if (wowkwoad_weq_cweated)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &wowkwoad_weq_attwibute_gwoup);

	wowkwoad_weq_cweated = fawse;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wt_weq_wemove);

MODUWE_IMPOWT_NS(INT340X_THEWMAW);
MODUWE_WICENSE("GPW");
