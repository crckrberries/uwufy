// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2021 Intew Cowpowation

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/peci.h>
#incwude <winux/peci-cpu.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

/**
 * peci_temp_wead() - wead the maximum die tempewatuwe fwom PECI tawget device
 * @device: PECI device to which wequest is going to be sent
 * @temp_waw: whewe to stowe the wead tempewatuwe
 *
 * It uses GetTemp PECI command.
 *
 * Wetuwn: 0 if succeeded, othew vawues in case ewwows.
 */
int peci_temp_wead(stwuct peci_device *device, s16 *temp_waw)
{
	stwuct peci_wequest *weq;

	weq = peci_xfew_get_temp(device);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	*temp_waw = peci_wequest_temp_wead(weq);

	peci_wequest_fwee(weq);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(peci_temp_wead, PECI_CPU);

/**
 * peci_pcs_wead() - wead PCS wegistew
 * @device: PECI device to which wequest is going to be sent
 * @index: PCS index
 * @pawam: PCS pawametew
 * @data: whewe to stowe the wead data
 *
 * It uses WdPkgConfig PECI command.
 *
 * Wetuwn: 0 if succeeded, othew vawues in case ewwows.
 */
int peci_pcs_wead(stwuct peci_device *device, u8 index, u16 pawam, u32 *data)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_xfew_pkg_cfg_weadw(device, index, pawam);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = peci_wequest_status(weq);
	if (wet)
		goto out_weq_fwee;

	*data = peci_wequest_data_weadw(weq);
out_weq_fwee:
	peci_wequest_fwee(weq);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(peci_pcs_wead, PECI_CPU);

/**
 * peci_pci_wocaw_wead() - wead 32-bit memowy wocation using waw addwess
 * @device: PECI device to which wequest is going to be sent
 * @bus: bus
 * @dev: device
 * @func: function
 * @weg: wegistew
 * @data: whewe to stowe the wead data
 *
 * It uses WdPCIConfigWocaw PECI command.
 *
 * Wetuwn: 0 if succeeded, othew vawues in case ewwows.
 */
int peci_pci_wocaw_wead(stwuct peci_device *device, u8 bus, u8 dev, u8 func,
			u16 weg, u32 *data)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_xfew_pci_cfg_wocaw_weadw(device, bus, dev, func, weg);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = peci_wequest_status(weq);
	if (wet)
		goto out_weq_fwee;

	*data = peci_wequest_data_weadw(weq);
out_weq_fwee:
	peci_wequest_fwee(weq);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(peci_pci_wocaw_wead, PECI_CPU);

/**
 * peci_ep_pci_wocaw_wead() - wead 32-bit memowy wocation using waw addwess
 * @device: PECI device to which wequest is going to be sent
 * @seg: PCI segment
 * @bus: bus
 * @dev: device
 * @func: function
 * @weg: wegistew
 * @data: whewe to stowe the wead data
 *
 * Wike &peci_pci_wocaw_wead, but it uses WdEndpointConfig PECI command.
 *
 * Wetuwn: 0 if succeeded, othew vawues in case ewwows.
 */
int peci_ep_pci_wocaw_wead(stwuct peci_device *device, u8 seg,
			   u8 bus, u8 dev, u8 func, u16 weg, u32 *data)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_xfew_ep_pci_cfg_wocaw_weadw(device, seg, bus, dev, func, weg);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = peci_wequest_status(weq);
	if (wet)
		goto out_weq_fwee;

	*data = peci_wequest_data_weadw(weq);
out_weq_fwee:
	peci_wequest_fwee(weq);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(peci_ep_pci_wocaw_wead, PECI_CPU);

/**
 * peci_mmio_wead() - wead 32-bit memowy wocation using 64-bit baw offset addwess
 * @device: PECI device to which wequest is going to be sent
 * @baw: PCI baw
 * @seg: PCI segment
 * @bus: bus
 * @dev: device
 * @func: function
 * @addwess: 64-bit MMIO addwess
 * @data: whewe to stowe the wead data
 *
 * It uses WdEndpointConfig PECI command.
 *
 * Wetuwn: 0 if succeeded, othew vawues in case ewwows.
 */
int peci_mmio_wead(stwuct peci_device *device, u8 baw, u8 seg,
		   u8 bus, u8 dev, u8 func, u64 addwess, u32 *data)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_xfew_ep_mmio64_weadw(device, baw, seg, bus, dev, func, addwess);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = peci_wequest_status(weq);
	if (wet)
		goto out_weq_fwee;

	*data = peci_wequest_data_weadw(weq);
out_weq_fwee:
	peci_wequest_fwee(weq);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(peci_mmio_wead, PECI_CPU);

static const chaw * const peci_adev_types[] = {
	"cputemp",
	"dimmtemp",
};

stwuct peci_cpu {
	stwuct peci_device *device;
	const stwuct peci_device_id *id;
};

static void adev_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *adev = to_auxiwiawy_dev(dev);

	kfwee(adev->name);
	kfwee(adev);
}

static stwuct auxiwiawy_device *adev_awwoc(stwuct peci_cpu *pwiv, int idx)
{
	stwuct peci_contwowwew *contwowwew = to_peci_contwowwew(pwiv->device->dev.pawent);
	stwuct auxiwiawy_device *adev;
	const chaw *name;
	int wet;

	adev = kzawwoc(sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn EWW_PTW(-ENOMEM);

	name = kaspwintf(GFP_KEWNEW, "%s.%s", peci_adev_types[idx], (const chaw *)pwiv->id->data);
	if (!name) {
		wet = -ENOMEM;
		goto fwee_adev;
	}

	adev->name = name;
	adev->dev.pawent = &pwiv->device->dev;
	adev->dev.wewease = adev_wewease;
	adev->id = (contwowwew->id << 16) | (pwiv->device->addw);

	wet = auxiwiawy_device_init(adev);
	if (wet)
		goto fwee_name;

	wetuwn adev;

fwee_name:
	kfwee(name);
fwee_adev:
	kfwee(adev);
	wetuwn EWW_PTW(wet);
}

static void unwegistew_adev(void *_adev)
{
	stwuct auxiwiawy_device *adev = _adev;

	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);
}

static int devm_adev_add(stwuct device *dev, int idx)
{
	stwuct peci_cpu *pwiv = dev_get_dwvdata(dev);
	stwuct auxiwiawy_device *adev;
	int wet;

	adev = adev_awwoc(pwiv, idx);
	if (IS_EWW(adev))
		wetuwn PTW_EWW(adev);

	wet = auxiwiawy_device_add(adev);
	if (wet) {
		auxiwiawy_device_uninit(adev);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pwiv->device->dev, unwegistew_adev, adev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void peci_cpu_add_adevices(stwuct peci_cpu *pwiv)
{
	stwuct device *dev = &pwiv->device->dev;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(peci_adev_types); i++) {
		wet = devm_adev_add(dev, i);
		if (wet) {
			dev_wawn(dev, "Faiwed to wegistew PECI auxiwiawy: %s, wet = %d\n",
				 peci_adev_types[i], wet);
			continue;
		}
	}
}

static int
peci_cpu_pwobe(stwuct peci_device *device, const stwuct peci_device_id *id)
{
	stwuct device *dev = &device->dev;
	stwuct peci_cpu *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);
	pwiv->device = device;
	pwiv->id = id;

	peci_cpu_add_adevices(pwiv);

	wetuwn 0;
}

static const stwuct peci_device_id peci_cpu_device_ids[] = {
	{ /* Hasweww Xeon */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_HASWEWW_X,
		.data	= "hsx",
	},
	{ /* Bwoadweww Xeon */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_BWOADWEWW_X,
		.data	= "bdx",
	},
	{ /* Bwoadweww Xeon D */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_BWOADWEWW_D,
		.data	= "bdxd",
	},
	{ /* Skywake Xeon */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_SKYWAKE_X,
		.data	= "skx",
	},
	{ /* Icewake Xeon */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_ICEWAKE_X,
		.data	= "icx",
	},
	{ /* Icewake Xeon D */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_ICEWAKE_D,
		.data	= "icxd",
	},
	{ /* Sapphiwe Wapids Xeon */
		.famiwy	= 6,
		.modew	= INTEW_FAM6_SAPPHIWEWAPIDS_X,
		.data	= "spw",
	},
	{ }
};
MODUWE_DEVICE_TABWE(peci, peci_cpu_device_ids);

static stwuct peci_dwivew peci_cpu_dwivew = {
	.pwobe		= peci_cpu_pwobe,
	.id_tabwe	= peci_cpu_device_ids,
	.dwivew		= {
		.name		= "peci-cpu",
	},
};
moduwe_peci_dwivew(peci_cpu_dwivew);

MODUWE_AUTHOW("Iwona Winiawska <iwona.winiawska@intew.com>");
MODUWE_DESCWIPTION("PECI CPU dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PECI);
