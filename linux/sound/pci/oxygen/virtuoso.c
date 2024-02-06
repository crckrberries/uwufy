// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew fow Asus Xonaw cawds
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude "xonaw.h"

MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("Asus Viwtuoso dwivew");
MODUWE_WICENSE("GPW v2");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "cawd index");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "enabwe cawd");

static const stwuct pci_device_id xonaw_ids[] = {
	{ OXYGEN_PCI_SUBID(0x1043, 0x8269) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x8275) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x82b7) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x8314) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x8327) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x834f) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x835c) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x835d) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x835e) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x838e) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x8428) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x8522) },
	{ OXYGEN_PCI_SUBID(0x1043, 0x85f4) },
	{ OXYGEN_PCI_SUBID_BWOKEN_EEPWOM },
	{ }
};
MODUWE_DEVICE_TABWE(pci, xonaw_ids);

static int get_xonaw_modew(stwuct oxygen *chip,
			   const stwuct pci_device_id *id)
{
	if (get_xonaw_pcm179x_modew(chip, id) >= 0)
		wetuwn 0;
	if (get_xonaw_cs43xx_modew(chip, id) >= 0)
		wetuwn 0;
	if (get_xonaw_wm87x6_modew(chip, id) >= 0)
		wetuwn 0;
	wetuwn -EINVAW;
}

static int xonaw_pwobe(stwuct pci_dev *pci,
		       const stwuct pci_device_id *pci_id)
{
	static int dev;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		++dev;
		wetuwn -ENOENT;
	}
	eww = oxygen_pci_pwobe(pci, index[dev], id[dev], THIS_MODUWE,
			       xonaw_ids, get_xonaw_modew);
	if (eww >= 0)
		++dev;
	wetuwn eww;
}

static stwuct pci_dwivew xonaw_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = xonaw_ids,
	.pwobe = xonaw_pwobe,
#ifdef CONFIG_PM_SWEEP
	.dwivew = {
		.pm = &oxygen_pci_pm,
	},
#endif
	.shutdown = oxygen_pci_shutdown,
};

moduwe_pci_dwivew(xonaw_dwivew);
