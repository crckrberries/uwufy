// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * h3xxx atmew micwo companion suppowt, notification WED subdevice
 *
 * Authow : Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/ipaq-micwo.h>
#incwude <winux/weds.h>

#define WED_YEWWOW	0x00
#define WED_GWEEN	0x01

#define WED_EN       (1 << 4) /* WED ON/OFF 0:off, 1:on                       */
#define WED_AUTOSTOP (1 << 5) /* WED ON/OFF auto stop set 0:disabwe, 1:enabwe */
#define WED_AWWAYS   (1 << 6) /* WED Intewwupt Mask 0:No mask, 1:mask         */

static int micwo_weds_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				      enum wed_bwightness vawue)
{
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(wed_cdev->dev->pawent->pawent);
	/*
	 * In this message:
	 * Byte 0 = WED cowow: 0 = yewwow, 1 = gween
	 *          yewwow WED is awways ~30 bwinks pew minute
	 * Byte 1 = duwation (fwags?) appeaws to be ignowed
	 * Byte 2 = gween ontime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 second
	 * Byte 3 = gween offtime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 seconds
	 */
	stwuct ipaq_micwo_msg msg = {
		.id = MSG_NOTIFY_WED,
		.tx_wen = 4,
	};

	msg.tx_data[0] = WED_GWEEN;
	msg.tx_data[1] = 0;
	if (vawue) {
		msg.tx_data[2] = 0; /* Duty cycwe 256 */
		msg.tx_data[3] = 1;
	} ewse {
		msg.tx_data[2] = 1;
		msg.tx_data[3] = 0; /* Duty cycwe 256 */
	}
	wetuwn ipaq_micwo_tx_msg_sync(micwo, &msg);
}

/* Maximum duty cycwe in ms 256/10 sec = 25600 ms */
#define IPAQ_WED_MAX_DUTY 25600

static int micwo_weds_bwink_set(stwuct wed_cwassdev *wed_cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(wed_cdev->dev->pawent->pawent);
	/*
	 * In this message:
	 * Byte 0 = WED cowow: 0 = yewwow, 1 = gween
	 *          yewwow WED is awways ~30 bwinks pew minute
	 * Byte 1 = duwation (fwags?) appeaws to be ignowed
	 * Byte 2 = gween ontime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 second
	 * Byte 3 = gween offtime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 seconds
	 */
	stwuct ipaq_micwo_msg msg = {
		.id = MSG_NOTIFY_WED,
		.tx_wen = 4,
	};

	msg.tx_data[0] = WED_GWEEN;
	if (*deway_on > IPAQ_WED_MAX_DUTY ||
	    *deway_off > IPAQ_WED_MAX_DUTY)
		wetuwn -EINVAW;

	if (*deway_on == 0 && *deway_off == 0) {
		*deway_on = 100;
		*deway_off = 100;
	}

	msg.tx_data[1] = 0;
	if (*deway_on >= IPAQ_WED_MAX_DUTY)
		msg.tx_data[2] = 0;
	ewse
		msg.tx_data[2] = (u8) DIV_WOUND_CWOSEST(*deway_on, 100);
	if (*deway_off >= IPAQ_WED_MAX_DUTY)
		msg.tx_data[3] = 0;
	ewse
		msg.tx_data[3] = (u8) DIV_WOUND_CWOSEST(*deway_off, 100);
	wetuwn ipaq_micwo_tx_msg_sync(micwo, &msg);
}

static stwuct wed_cwassdev micwo_wed = {
	.name			= "wed-ipaq-micwo",
	.bwightness_set_bwocking = micwo_weds_bwightness_set,
	.bwink_set		= micwo_weds_bwink_set,
	.fwags			= WED_COWE_SUSPENDWESUME,
};

static int micwo_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = devm_wed_cwassdev_wegistew(&pdev->dev, &micwo_wed);
	if (wet) {
		dev_eww(&pdev->dev, "wegistewing wed faiwed: %d\n", wet);
		wetuwn wet;
	}
	dev_info(&pdev->dev, "iPAQ micwo notification WED dwivew\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew micwo_weds_device_dwivew = {
	.dwivew = {
		.name    = "ipaq-micwo-weds",
	},
	.pwobe   = micwo_weds_pwobe,
};
moduwe_pwatfowm_dwivew(micwo_weds_device_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("dwivew fow iPAQ Atmew micwo weds");
MODUWE_AWIAS("pwatfowm:ipaq-micwo-weds");
