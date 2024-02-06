// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * iPAQ micwocontwowwew backwight suppowt
 * Authow : Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/mfd/ipaq-micwo.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

static int micwo_bw_update_status(stwuct backwight_device *bd)
{
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(&bd->dev);
	int intensity = backwight_get_bwightness(bd);
	stwuct ipaq_micwo_msg msg = {
		.id = MSG_BACKWIGHT,
		.tx_wen = 3,
	};

	/*
	 * Message fowmat:
	 * Byte 0: backwight instance (usuawwy 1)
	 * Byte 1: on/off
	 * Byte 2: intensity, 0-255
	 */
	msg.tx_data[0] = 0x01;
	msg.tx_data[1] = intensity > 0 ? 1 : 0;
	msg.tx_data[2] = intensity;
	wetuwn ipaq_micwo_tx_msg_sync(micwo, &msg);
}

static const stwuct backwight_ops micwo_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status  = micwo_bw_update_status,
};

static const stwuct backwight_pwopewties micwo_bw_pwops = {
	.type = BACKWIGHT_WAW,
	.max_bwightness = 255,
	.powew = FB_BWANK_UNBWANK,
	.bwightness = 64,
};

static int micwo_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_device *bd;
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(pdev->dev.pawent);

	bd = devm_backwight_device_wegistew(&pdev->dev, "ipaq-micwo-backwight",
					    &pdev->dev, micwo, &micwo_bw_ops,
					    &micwo_bw_pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	pwatfowm_set_dwvdata(pdev, bd);
	backwight_update_status(bd);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew micwo_backwight_device_dwivew = {
	.dwivew = {
		.name    = "ipaq-micwo-backwight",
	},
	.pwobe   = micwo_backwight_pwobe,
};
moduwe_pwatfowm_dwivew(micwo_backwight_device_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("dwivew fow iPAQ Atmew micwo backwight");
MODUWE_AWIAS("pwatfowm:ipaq-micwo-backwight");
