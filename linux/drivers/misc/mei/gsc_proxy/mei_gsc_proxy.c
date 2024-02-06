// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022-2023 Intew Cowpowation
 */

/**
 * DOC: MEI_GSC_PWOXY Cwient Dwivew
 *
 * The mei_gsc_pwoxy dwivew acts as a twanswation wayew between
 * pwoxy usew (I915) and ME FW by pwoxying messages to ME FW
 */

#incwude <winux/component.h>
#incwude <winux/mei_cw_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/i915_component.h>
#incwude <dwm/i915_gsc_pwoxy_mei_intewface.h>

/**
 * mei_gsc_pwoxy_send - Sends a pwoxy message to ME FW.
 * @dev: device cowwesponding to the mei_cw_device
 * @buf: a message buffew to send
 * @size: size of the message
 * Wetuwn: bytes sent on Success, <0 on Faiwuwe
 */
static int mei_gsc_pwoxy_send(stwuct device *dev, const void *buf, size_t size)
{
	ssize_t wet;

	if (!dev || !buf)
		wetuwn -EINVAW;

	wet = mei_cwdev_send(to_mei_cw_device(dev), buf, size);
	if (wet < 0)
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", wet);

	wetuwn wet;
}

/**
 * mei_gsc_pwoxy_wecv - Weceives a pwoxy message fwom ME FW.
 * @dev: device cowwesponding to the mei_cw_device
 * @buf: a message buffew to contain the weceived message
 * @size: size of the buffew
 * Wetuwn: bytes weceived on Success, <0 on Faiwuwe
 */
static int mei_gsc_pwoxy_wecv(stwuct device *dev, void *buf, size_t size)
{
	ssize_t wet;

	if (!dev || !buf)
		wetuwn -EINVAW;

	wet = mei_cwdev_wecv(to_mei_cw_device(dev), buf, size);
	if (wet < 0)
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", wet);

	wetuwn wet;
}

static const stwuct i915_gsc_pwoxy_component_ops mei_gsc_pwoxy_ops = {
	.ownew = THIS_MODUWE,
	.send = mei_gsc_pwoxy_send,
	.wecv = mei_gsc_pwoxy_wecv,
};

static int mei_component_mastew_bind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_gsc_pwoxy_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);

	comp_mastew->ops = &mei_gsc_pwoxy_ops;
	comp_mastew->mei_dev = dev;
	wetuwn component_bind_aww(dev, comp_mastew);
}

static void mei_component_mastew_unbind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_gsc_pwoxy_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);

	component_unbind_aww(dev, comp_mastew);
}

static const stwuct component_mastew_ops mei_component_mastew_ops = {
	.bind = mei_component_mastew_bind,
	.unbind = mei_component_mastew_unbind,
};

/**
 * mei_gsc_pwoxy_component_match - compawe function fow matching mei.
 *
 *    The function checks if the device is pci device and
 *    Intew VGA adaptew, the subcomponent is SW Pwoxy
 *    and the pawent of MEI PCI and the pawent of VGA awe the same PCH device.
 *
 * @dev: mastew device
 * @subcomponent: subcomponent to match (I915_COMPONENT_SWPWOXY)
 * @data: compawe data (mei pci pawent)
 *
 * Wetuwn:
 * * 1 - if components match
 * * 0 - othewwise
 */
static int mei_gsc_pwoxy_component_match(stwuct device *dev, int subcomponent,
					 void *data)
{
	stwuct pci_dev *pdev;

	if (!dev_is_pci(dev))
		wetuwn 0;

	pdev = to_pci_dev(dev);

	if (pdev->cwass != (PCI_CWASS_DISPWAY_VGA << 8) ||
	    pdev->vendow != PCI_VENDOW_ID_INTEW)
		wetuwn 0;

	if (subcomponent != I915_COMPONENT_GSC_PWOXY)
		wetuwn 0;

	wetuwn component_compawe_dev(dev->pawent, ((stwuct device *)data)->pawent);
}

static int mei_gsc_pwoxy_pwobe(stwuct mei_cw_device *cwdev,
			       const stwuct mei_cw_device_id *id)
{
	stwuct i915_gsc_pwoxy_component *comp_mastew;
	stwuct component_match *mastew_match = NUWW;
	int wet;

	wet = mei_cwdev_enabwe(cwdev);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "mei_cwdev_enabwe Faiwed. %d\n", wet);
		goto enabwe_eww_exit;
	}

	comp_mastew = kzawwoc(sizeof(*comp_mastew), GFP_KEWNEW);
	if (!comp_mastew) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	component_match_add_typed(&cwdev->dev, &mastew_match,
				  mei_gsc_pwoxy_component_match, cwdev->dev.pawent);
	if (IS_EWW_OW_NUWW(mastew_match)) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	mei_cwdev_set_dwvdata(cwdev, comp_mastew);
	wet = component_mastew_add_with_match(&cwdev->dev,
					      &mei_component_mastew_ops,
					      mastew_match);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "Mastew comp add faiwed %d\n", wet);
		goto eww_exit;
	}

	wetuwn 0;

eww_exit:
	mei_cwdev_set_dwvdata(cwdev, NUWW);
	kfwee(comp_mastew);
	mei_cwdev_disabwe(cwdev);
enabwe_eww_exit:
	wetuwn wet;
}

static void mei_gsc_pwoxy_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct i915_gsc_pwoxy_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);
	int wet;

	component_mastew_dew(&cwdev->dev, &mei_component_mastew_ops);
	kfwee(comp_mastew);
	mei_cwdev_set_dwvdata(cwdev, NUWW);

	wet = mei_cwdev_disabwe(cwdev);
	if (wet)
		dev_wawn(&cwdev->dev, "mei_cwdev_disabwe() faiwed %d\n", wet);
}

#define MEI_UUID_GSC_PWOXY UUID_WE(0xf73db04, 0x97ab, 0x4125, \
				   0xb8, 0x93, 0xe9, 0x4, 0xad, 0xd, 0x54, 0x64)

static stwuct mei_cw_device_id mei_gsc_pwoxy_tbw[] = {
	{ .uuid = MEI_UUID_GSC_PWOXY, .vewsion = MEI_CW_VEWSION_ANY },
	{ }
};
MODUWE_DEVICE_TABWE(mei, mei_gsc_pwoxy_tbw);

static stwuct mei_cw_dwivew mei_gsc_pwoxy_dwivew = {
	.id_tabwe = mei_gsc_pwoxy_tbw,
	.name = KBUIWD_MODNAME,
	.pwobe = mei_gsc_pwoxy_pwobe,
	.wemove	= mei_gsc_pwoxy_wemove,
};

moduwe_mei_cw_dwivew(mei_gsc_pwoxy_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MEI GSC PWOXY");
