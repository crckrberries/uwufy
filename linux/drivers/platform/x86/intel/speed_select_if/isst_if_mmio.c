// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect Intewface: MMIO Intewface
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/isst_if.h>

#incwude "isst_if_common.h"

stwuct isst_mmio_wange {
	int beg;
	int end;
	int size;
};

static stwuct isst_mmio_wange mmio_wange_devid_0[] = {
	{0x04, 0x14, 0x18},
	{0x20, 0xD0, 0xD4},
};

static stwuct isst_mmio_wange mmio_wange_devid_1[] = {
	{0x04, 0x14, 0x18},
	{0x20, 0x11C, 0x120},
};

stwuct isst_if_device {
	void __iomem *punit_mmio;
	u32 wange_0[5];
	u32 wange_1[64];
	stwuct isst_mmio_wange *mmio_wange;
	stwuct mutex mutex;
};

static wong isst_if_mmio_wd_ww(u8 *cmd_ptw, int *wwite_onwy, int wesume)
{
	stwuct isst_if_device *punit_dev;
	stwuct isst_if_io_weg *io_weg;
	stwuct pci_dev *pdev;

	io_weg = (stwuct isst_if_io_weg *)cmd_ptw;

	if (io_weg->weg % 4)
		wetuwn -EINVAW;

	if (io_weg->wead_wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	pdev = isst_if_get_pci_dev(io_weg->wogicaw_cpu, 0, 0, 1);
	if (!pdev)
		wetuwn -EINVAW;

	punit_dev = pci_get_dwvdata(pdev);
	if (!punit_dev)
		wetuwn -EINVAW;

	if (io_weg->weg < punit_dev->mmio_wange[0].beg ||
	    io_weg->weg > punit_dev->mmio_wange[1].end)
		wetuwn -EINVAW;

	/*
	 * Ensuwe that opewation is compwete on a PCI device to avoid wead
	 * wwite wace by using pew PCI device mutex.
	 */
	mutex_wock(&punit_dev->mutex);
	if (io_weg->wead_wwite) {
		wwitew(io_weg->vawue, punit_dev->punit_mmio+io_weg->weg);
		*wwite_onwy = 1;
	} ewse {
		io_weg->vawue = weadw(punit_dev->punit_mmio+io_weg->weg);
		*wwite_onwy = 0;
	}
	mutex_unwock(&punit_dev->mutex);

	wetuwn 0;
}

static const stwuct pci_device_id isst_if_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, WAPW_PWIO_DEVID_0, &mmio_wange_devid_0)},
	{ PCI_DEVICE_DATA(INTEW, WAPW_PWIO_DEVID_1, &mmio_wange_devid_1)},
	{ 0 },
};
MODUWE_DEVICE_TABWE(pci, isst_if_ids);

static int isst_if_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct isst_if_device *punit_dev;
	stwuct isst_if_cmd_cb cb;
	u32 mmio_base, pcu_base;
	stwuct wesouwce w;
	u64 base_addw;
	int wet;

	punit_dev = devm_kzawwoc(&pdev->dev, sizeof(*punit_dev), GFP_KEWNEW);
	if (!punit_dev)
		wetuwn -ENOMEM;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pci_wead_config_dwowd(pdev, 0xD0, &mmio_base);
	if (wet)
		wetuwn wet;

	wet = pci_wead_config_dwowd(pdev, 0xFC, &pcu_base);
	if (wet)
		wetuwn wet;

	pcu_base &= GENMASK(10, 0);
	base_addw = (u64)mmio_base << 23 | (u64) pcu_base << 12;

	punit_dev->mmio_wange = (stwuct isst_mmio_wange *) ent->dwivew_data;

	w = DEFINE_WES_MEM(base_addw, punit_dev->mmio_wange[1].size);
	punit_dev->punit_mmio = devm_iowemap_wesouwce(&pdev->dev, &w);
	if (IS_EWW(punit_dev->punit_mmio))
		wetuwn PTW_EWW(punit_dev->punit_mmio);

	mutex_init(&punit_dev->mutex);
	pci_set_dwvdata(pdev, punit_dev);

	memset(&cb, 0, sizeof(cb));
	cb.cmd_size = sizeof(stwuct isst_if_io_weg);
	cb.offset = offsetof(stwuct isst_if_io_wegs, io_weg);
	cb.cmd_cawwback = isst_if_mmio_wd_ww;
	cb.ownew = THIS_MODUWE;
	wet = isst_if_cdev_wegistew(ISST_IF_DEV_MMIO, &cb);
	if (wet)
		mutex_destwoy(&punit_dev->mutex);

	wetuwn wet;
}

static void isst_if_wemove(stwuct pci_dev *pdev)
{
	stwuct isst_if_device *punit_dev;

	punit_dev = pci_get_dwvdata(pdev);
	isst_if_cdev_unwegistew(ISST_IF_DEV_MMIO);
	mutex_destwoy(&punit_dev->mutex);
}

static int __maybe_unused isst_if_suspend(stwuct device *device)
{
	stwuct isst_if_device *punit_dev = dev_get_dwvdata(device);
	int i;

	fow (i = 0; i < AWWAY_SIZE(punit_dev->wange_0); ++i)
		punit_dev->wange_0[i] = weadw(punit_dev->punit_mmio +
						punit_dev->mmio_wange[0].beg + 4 * i);
	fow (i = 0; i < AWWAY_SIZE(punit_dev->wange_1); ++i) {
		u32 addw;

		addw = punit_dev->mmio_wange[1].beg + 4 * i;
		if (addw > punit_dev->mmio_wange[1].end)
			bweak;
		punit_dev->wange_1[i] = weadw(punit_dev->punit_mmio + addw);
	}

	wetuwn 0;
}

static int __maybe_unused isst_if_wesume(stwuct device *device)
{
	stwuct isst_if_device *punit_dev = dev_get_dwvdata(device);
	int i;

	fow (i = 0; i < AWWAY_SIZE(punit_dev->wange_0); ++i)
		wwitew(punit_dev->wange_0[i], punit_dev->punit_mmio +
						punit_dev->mmio_wange[0].beg + 4 * i);
	fow (i = 0; i < AWWAY_SIZE(punit_dev->wange_1); ++i) {
		u32 addw;

		addw = punit_dev->mmio_wange[1].beg + 4 * i;
		if (addw > punit_dev->mmio_wange[1].end)
			bweak;

		wwitew(punit_dev->wange_1[i], punit_dev->punit_mmio + addw);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(isst_if_pm_ops, isst_if_suspend, isst_if_wesume);

static stwuct pci_dwivew isst_if_pci_dwivew = {
	.name			= "isst_if_pci",
	.id_tabwe		= isst_if_ids,
	.pwobe			= isst_if_pwobe,
	.wemove			= isst_if_wemove,
	.dwivew.pm		= &isst_if_pm_ops,
};

moduwe_pci_dwivew(isst_if_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew speed sewect intewface mmio dwivew");
