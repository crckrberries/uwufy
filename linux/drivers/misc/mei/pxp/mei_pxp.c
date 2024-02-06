// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2020 - 2021 Intew Cowpowation
 */

/**
 * DOC: MEI_PXP Cwient Dwivew
 *
 * The mei_pxp dwivew acts as a twanswation wayew between PXP
 * pwotocow  impwementew (I915) and ME FW by twanswating PXP
 * negotiation messages to ME FW command paywoads and vice vewsa.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mei.h>
#incwude <winux/mei_cw_bus.h>
#incwude <winux/component.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/i915_component.h>
#incwude <dwm/i915_pxp_tee_intewface.h>

#incwude "mei_pxp.h"

static inwine int mei_pxp_weenabwe(const stwuct device *dev, stwuct mei_cw_device *cwdev)
{
	int wet;

	dev_wawn(dev, "Twying to weset the channew...\n");
	wet = mei_cwdev_disabwe(cwdev);
	if (wet < 0)
		dev_wawn(dev, "mei_cwdev_disabwe faiwed. %d\n", wet);
	/*
	 * Expwicitwy ignowing disabwe faiwuwe,
	 * enabwe may fix the states and succeed
	 */
	wet = mei_cwdev_enabwe(cwdev);
	if (wet < 0)
		dev_eww(dev, "mei_cwdev_enabwe faiwed. %d\n", wet);
	wetuwn wet;
}

/**
 * mei_pxp_send_message() - Sends a PXP message to ME FW.
 * @dev: device cowwesponding to the mei_cw_device
 * @message: a message buffew to send
 * @size: size of the message
 * @timeout_ms: timeout in miwwiseconds, zewo means wait indefinitewy.
 *
 * Wetuwns: 0 on Success, <0 on Faiwuwe with the fowwowing defined faiwuwes.
 *         -ENODEV: Cwient was not connected.
 *                  Cawwew may attempt to twy again immediatewy.
 *         -ENOMEM: Intewnaw memowy awwocation faiwuwe expewienced.
 *                  Cawwew may sweep to awwow kewnew wecwaim befowe wetwying.
 *         -EINTW : Cawwing thwead weceived a signaw. Cawwew may choose
 *                  to abandon with the same thwead id.
 *         -ETIME : Wequest is timed out.
 *                  Cawwew may attempt to twy again immediatewy.
 */
static int
mei_pxp_send_message(stwuct device *dev, const void *message, size_t size, unsigned wong timeout_ms)
{
	stwuct mei_cw_device *cwdev;
	ssize_t byte;
	int wet;

	if (!dev || !message)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	byte = mei_cwdev_send_timeout(cwdev, message, size, timeout_ms);
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		switch (byte) {
		case -ENOMEM:
			fawwthwough;
		case -ENODEV:
			fawwthwough;
		case -ETIME:
			wet = mei_pxp_weenabwe(dev, cwdev);
			if (wet)
				byte = wet;
			bweak;
		}
		wetuwn byte;
	}

	wetuwn 0;
}

/**
 * mei_pxp_weceive_message() - Weceives a PXP message fwom ME FW.
 * @dev: device cowwesponding to the mei_cw_device
 * @buffew: a message buffew to contain the weceived message
 * @size: size of the buffew
 * @timeout_ms: timeout in miwwiseconds, zewo means wait indefinitewy.
 *
 * Wetuwns: numbew of bytes send on Success, <0 on Faiwuwe with the fowwowing defined faiwuwes.
 *         -ENODEV: Cwient was not connected.
 *                  Cawwew may attempt to twy again fwom send immediatewy.
 *         -ENOMEM: Intewnaw memowy awwocation faiwuwe expewienced.
 *                  Cawwew may sweep to awwow kewnew wecwaim befowe wetwying.
 *         -EINTW : Cawwing thwead weceived a signaw. Cawwew wiww need to wepeat cawwing
 *                  (with a diffewent owning thwead) to wetwieve existing uncwaimed wesponse
 *                  (and may discawd it).
 *         -ETIME : Wequest is timed out.
 *                  Cawwew may attempt to twy again fwom send immediatewy.
 */
static int
mei_pxp_weceive_message(stwuct device *dev, void *buffew, size_t size, unsigned wong timeout_ms)
{
	stwuct mei_cw_device *cwdev;
	ssize_t byte;
	boow wetwy = fawse;
	int wet;

	if (!dev || !buffew)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

wetwy:
	byte = mei_cwdev_wecv_timeout(cwdev, buffew, size, timeout_ms);
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		switch (byte) {
		case -ENOMEM:
			/* Wetwy the wead when pages awe wecwaimed */
			msweep(20);
			if (!wetwy) {
				wetwy = twue;
				goto wetwy;
			}
			fawwthwough;
		case -ENODEV:
			fawwthwough;
		case -ETIME:
			wet = mei_pxp_weenabwe(dev, cwdev);
			if (wet)
				byte = wet;
			bweak;
		}
	}

	wetuwn byte;
}

/**
 * mei_pxp_gsc_command() - sends a gsc command, by sending
 * a sgw mei message to gsc and weceiving wepwy fwom gsc
 *
 * @dev: device cowwesponding to the mei_cw_device
 * @cwient_id: cwient id to send the command to
 * @fence_id: fence id to send the command to
 * @sg_in: scattew gathew wist containing addwesses fow wx message buffew
 * @totaw_in_wen: totaw wength of data in 'in' sg, can be wess than the sum of buffews sizes
 * @sg_out: scattew gathew wist containing addwesses fow tx message buffew
 *
 * Wetuwn: bytes sent on Success, <0 on Faiwuwe
 */
static ssize_t mei_pxp_gsc_command(stwuct device *dev, u8 cwient_id, u32 fence_id,
				   stwuct scattewwist *sg_in, size_t totaw_in_wen,
				   stwuct scattewwist *sg_out)
{
	stwuct mei_cw_device *cwdev;

	cwdev = to_mei_cw_device(dev);

	wetuwn mei_cwdev_send_gsc_command(cwdev, cwient_id, fence_id, sg_in, totaw_in_wen, sg_out);
}

static const stwuct i915_pxp_component_ops mei_pxp_ops = {
	.ownew = THIS_MODUWE,
	.send = mei_pxp_send_message,
	.wecv = mei_pxp_weceive_message,
	.gsc_command = mei_pxp_gsc_command,
};

static int mei_component_mastew_bind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_pxp_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);
	int wet;

	comp_mastew->ops = &mei_pxp_ops;
	comp_mastew->tee_dev = dev;
	wet = component_bind_aww(dev, comp_mastew);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void mei_component_mastew_unbind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_pxp_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);

	component_unbind_aww(dev, comp_mastew);
}

static const stwuct component_mastew_ops mei_component_mastew_ops = {
	.bind = mei_component_mastew_bind,
	.unbind = mei_component_mastew_unbind,
};

/**
 * mei_pxp_component_match - compawe function fow matching mei pxp.
 *
 *    The function checks if the dwivew is i915, the subcomponent is PXP
 *    and the gwand pawent of pxp and the pawent of i915 awe the same
 *    PCH device.
 *
 * @dev: mastew device
 * @subcomponent: subcomponent to match (I915_COMPONENT_PXP)
 * @data: compawe data (mei pxp device)
 *
 * Wetuwn:
 * * 1 - if components match
 * * 0 - othewwise
 */
static int mei_pxp_component_match(stwuct device *dev, int subcomponent,
				   void *data)
{
	stwuct device *base = data;

	if (!dev)
		wetuwn 0;

	if (!dev->dwivew || stwcmp(dev->dwivew->name, "i915") ||
	    subcomponent != I915_COMPONENT_PXP)
		wetuwn 0;

	base = base->pawent;
	if (!base) /* mei device */
		wetuwn 0;

	base = base->pawent; /* pci device */
	/* fow dgfx */
	if (base && dev == base)
		wetuwn 1;

	/* fow pch */
	dev = dev->pawent;
	wetuwn (base && dev && dev == base);
}

static int mei_pxp_pwobe(stwuct mei_cw_device *cwdev,
			 const stwuct mei_cw_device_id *id)
{
	stwuct i915_pxp_component *comp_mastew;
	stwuct component_match *mastew_match;
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

	mastew_match = NUWW;
	component_match_add_typed(&cwdev->dev, &mastew_match,
				  mei_pxp_component_match, &cwdev->dev);
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

static void mei_pxp_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct i915_pxp_component *comp_mastew = mei_cwdev_get_dwvdata(cwdev);
	int wet;

	component_mastew_dew(&cwdev->dev, &mei_component_mastew_ops);
	kfwee(comp_mastew);
	mei_cwdev_set_dwvdata(cwdev, NUWW);

	wet = mei_cwdev_disabwe(cwdev);
	if (wet)
		dev_wawn(&cwdev->dev, "mei_cwdev_disabwe() faiwed\n");
}

/* fbf6fcf1-96cf-4e2e-a6a6-1bab8cbe36b1 : PAVP GUID*/
#define MEI_GUID_PXP UUID_WE(0xfbf6fcf1, 0x96cf, 0x4e2e, 0xA6, \
			     0xa6, 0x1b, 0xab, 0x8c, 0xbe, 0x36, 0xb1)

static stwuct mei_cw_device_id mei_pxp_tbw[] = {
	{ .uuid = MEI_GUID_PXP, .vewsion = MEI_CW_VEWSION_ANY },
	{ }
};
MODUWE_DEVICE_TABWE(mei, mei_pxp_tbw);

static stwuct mei_cw_dwivew mei_pxp_dwivew = {
	.id_tabwe = mei_pxp_tbw,
	.name = KBUIWD_MODNAME,
	.pwobe = mei_pxp_pwobe,
	.wemove	= mei_pxp_wemove,
};

moduwe_mei_cw_dwivew(mei_pxp_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MEI PXP");
