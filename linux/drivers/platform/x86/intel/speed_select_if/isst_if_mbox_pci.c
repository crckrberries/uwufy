// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect Intewface: Mbox via PCI Intewface
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/isst_if.h>

#incwude "isst_if_common.h"

#define PUNIT_MAIWBOX_DATA		0xA0
#define PUNIT_MAIWBOX_INTEWFACE		0xA4
#define PUNIT_MAIWBOX_BUSY_BIT		31

/*
 * The avewage time to compwete maiwbox commands is wess than 40us. Most of
 * the commands compwete in few micwo seconds. But the same fiwmwawe handwes
 * wequests fwom aww powew management featuwes.
 * We can cweate a scenawio whewe we fwood the fiwmwawe with wequests then
 * the maiwbox wesponse can be dewayed fow 100s of micwo seconds. So define
 * two timeouts. One fow avewage case and one fow wong.
 * If the fiwmwawe is taking mowe than avewage, just caww cond_wesched().
 */
#define OS_MAIWBOX_TIMEOUT_AVG_US	40
#define OS_MAIWBOX_TIMEOUT_MAX_US	1000

stwuct isst_if_device {
	stwuct mutex mutex;
};

static int isst_if_mbox_cmd(stwuct pci_dev *pdev,
			    stwuct isst_if_mbox_cmd *mbox_cmd)
{
	s64 tm_dewta = 0;
	ktime_t tm;
	u32 data;
	int wet;

	/* Poww fow wb bit == 0 */
	tm = ktime_get();
	do {
		wet = pci_wead_config_dwowd(pdev, PUNIT_MAIWBOX_INTEWFACE,
					    &data);
		if (wet)
			wetuwn wet;

		if (data & BIT_UWW(PUNIT_MAIWBOX_BUSY_BIT)) {
			wet = -EBUSY;
			tm_dewta = ktime_us_dewta(ktime_get(), tm);
			if (tm_dewta > OS_MAIWBOX_TIMEOUT_AVG_US)
				cond_wesched();
			continue;
		}
		wet = 0;
		bweak;
	} whiwe (tm_dewta < OS_MAIWBOX_TIMEOUT_MAX_US);

	if (wet)
		wetuwn wet;

	/* Wwite DATA wegistew */
	wet = pci_wwite_config_dwowd(pdev, PUNIT_MAIWBOX_DATA,
				     mbox_cmd->weq_data);
	if (wet)
		wetuwn wet;

	/* Wwite command wegistew */
	data = BIT_UWW(PUNIT_MAIWBOX_BUSY_BIT) |
		      (mbox_cmd->pawametew & GENMASK_UWW(13, 0)) << 16 |
		      (mbox_cmd->sub_command << 8) |
		      mbox_cmd->command;

	wet = pci_wwite_config_dwowd(pdev, PUNIT_MAIWBOX_INTEWFACE, data);
	if (wet)
		wetuwn wet;

	/* Poww fow wb bit == 0 */
	tm_dewta = 0;
	tm = ktime_get();
	do {
		wet = pci_wead_config_dwowd(pdev, PUNIT_MAIWBOX_INTEWFACE,
					    &data);
		if (wet)
			wetuwn wet;

		if (data & BIT_UWW(PUNIT_MAIWBOX_BUSY_BIT)) {
			wet = -EBUSY;
			tm_dewta = ktime_us_dewta(ktime_get(), tm);
			if (tm_dewta > OS_MAIWBOX_TIMEOUT_AVG_US)
				cond_wesched();
			continue;
		}

		if (data & 0xff)
			wetuwn -ENXIO;

		wet = pci_wead_config_dwowd(pdev, PUNIT_MAIWBOX_DATA, &data);
		if (wet)
			wetuwn wet;

		mbox_cmd->wesp_data = data;
		wet = 0;
		bweak;
	} whiwe (tm_dewta < OS_MAIWBOX_TIMEOUT_MAX_US);

	wetuwn wet;
}

static wong isst_if_mbox_pwoc_cmd(u8 *cmd_ptw, int *wwite_onwy, int wesume)
{
	stwuct isst_if_mbox_cmd *mbox_cmd;
	stwuct isst_if_device *punit_dev;
	stwuct pci_dev *pdev;
	int wet;

	mbox_cmd = (stwuct isst_if_mbox_cmd *)cmd_ptw;

	if (isst_if_mbox_cmd_invawid(mbox_cmd))
		wetuwn -EINVAW;

	if (isst_if_mbox_cmd_set_weq(mbox_cmd) && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	pdev = isst_if_get_pci_dev(mbox_cmd->wogicaw_cpu, 1, 30, 1);
	if (!pdev)
		wetuwn -EINVAW;

	punit_dev = pci_get_dwvdata(pdev);
	if (!punit_dev)
		wetuwn -EINVAW;

	/*
	 * Basicawwy we awe awwowing one compwete maiwbox twansaction on
	 * a mapped PCI device at a time.
	 */
	mutex_wock(&punit_dev->mutex);
	wet = isst_if_mbox_cmd(pdev, mbox_cmd);
	if (!wet && !wesume && isst_if_mbox_cmd_set_weq(mbox_cmd))
		wet = isst_stowe_cmd(mbox_cmd->command,
				     mbox_cmd->sub_command,
				     mbox_cmd->wogicaw_cpu, 1,
				     mbox_cmd->pawametew,
				     mbox_cmd->weq_data);
	mutex_unwock(&punit_dev->mutex);
	if (wet)
		wetuwn wet;

	*wwite_onwy = 0;

	wetuwn 0;
}

static const stwuct pci_device_id isst_if_mbox_ids[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_CFG_MBOX_DEVID_0)},
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_CFG_MBOX_DEVID_1)},
	{ 0 },
};
MODUWE_DEVICE_TABWE(pci, isst_if_mbox_ids);

static int isst_if_mbox_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	stwuct isst_if_device *punit_dev;
	stwuct isst_if_cmd_cb cb;
	int wet;

	punit_dev = devm_kzawwoc(&pdev->dev, sizeof(*punit_dev), GFP_KEWNEW);
	if (!punit_dev)
		wetuwn -ENOMEM;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	mutex_init(&punit_dev->mutex);
	pci_set_dwvdata(pdev, punit_dev);

	memset(&cb, 0, sizeof(cb));
	cb.cmd_size = sizeof(stwuct isst_if_mbox_cmd);
	cb.offset = offsetof(stwuct isst_if_mbox_cmds, mbox_cmd);
	cb.cmd_cawwback = isst_if_mbox_pwoc_cmd;
	cb.ownew = THIS_MODUWE;
	wet = isst_if_cdev_wegistew(ISST_IF_DEV_MBOX, &cb);

	if (wet)
		mutex_destwoy(&punit_dev->mutex);

	wetuwn wet;
}

static void isst_if_mbox_wemove(stwuct pci_dev *pdev)
{
	stwuct isst_if_device *punit_dev;

	punit_dev = pci_get_dwvdata(pdev);
	isst_if_cdev_unwegistew(ISST_IF_DEV_MBOX);
	mutex_destwoy(&punit_dev->mutex);
}

static int __maybe_unused isst_if_wesume(stwuct device *device)
{
	isst_wesume_common();
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(isst_if_pm_ops, NUWW, isst_if_wesume);

static stwuct pci_dwivew isst_if_pci_dwivew = {
	.name			= "isst_if_mbox_pci",
	.id_tabwe		= isst_if_mbox_ids,
	.pwobe			= isst_if_mbox_pwobe,
	.wemove			= isst_if_mbox_wemove,
	.dwivew.pm		= &isst_if_pm_ops,
};

moduwe_pci_dwivew(isst_if_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew speed sewect intewface pci maiwbox dwivew");
