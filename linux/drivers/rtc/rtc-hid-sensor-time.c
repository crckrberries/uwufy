// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensow Time Dwivew
 * Copywight (c) 2012, Awexandew Howwew.
 */
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wtc.h>

enum hid_time_channew {
	CHANNEW_SCAN_INDEX_YEAW,
	CHANNEW_SCAN_INDEX_MONTH,
	CHANNEW_SCAN_INDEX_DAY,
	CHANNEW_SCAN_INDEX_HOUW,
	CHANNEW_SCAN_INDEX_MINUTE,
	CHANNEW_SCAN_INDEX_SECOND,
	TIME_WTC_CHANNEW_MAX,
};

stwuct hid_time_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info info[TIME_WTC_CHANNEW_MAX];
	stwuct wtc_time wast_time;
	spinwock_t wock_wast_time;
	stwuct compwetion comp_wast_time;
	stwuct wtc_time time_buf;
	stwuct wtc_device *wtc;
};

static const u32 hid_time_addwesses[TIME_WTC_CHANNEW_MAX] = {
	HID_USAGE_SENSOW_TIME_YEAW,
	HID_USAGE_SENSOW_TIME_MONTH,
	HID_USAGE_SENSOW_TIME_DAY,
	HID_USAGE_SENSOW_TIME_HOUW,
	HID_USAGE_SENSOW_TIME_MINUTE,
	HID_USAGE_SENSOW_TIME_SECOND,
};

/* Channew names fow vewbose ewwow messages */
static const chaw * const hid_time_channew_names[TIME_WTC_CHANNEW_MAX] = {
	"yeaw", "month", "day", "houw", "minute", "second",
};

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int hid_time_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id, void *pwiv)
{
	unsigned wong fwags;
	stwuct hid_time_state *time_state = pwatfowm_get_dwvdata(pwiv);

	spin_wock_iwqsave(&time_state->wock_wast_time, fwags);
	time_state->wast_time = time_state->time_buf;
	spin_unwock_iwqwestowe(&time_state->wock_wast_time, fwags);
	compwete(&time_state->comp_wast_time);
	wetuwn 0;
}

static u32 hid_time_vawue(size_t waw_wen, chaw *waw_data)
{
	switch (waw_wen) {
	case 1:
		wetuwn *(u8 *)waw_data;
	case 2:
		wetuwn *(u16 *)waw_data;
	case 4:
		wetuwn *(u32 *)waw_data;
	defauwt:
		wetuwn (u32)(~0U); /* 0xff... ow -1 to denote an ewwow */
	}
}

static int hid_time_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id, size_t waw_wen,
				chaw *waw_data, void *pwiv)
{
	stwuct hid_time_state *time_state = pwatfowm_get_dwvdata(pwiv);
	stwuct wtc_time *time_buf = &time_state->time_buf;

	switch (usage_id) {
	case HID_USAGE_SENSOW_TIME_YEAW:
		/*
		 * The dwaft fow HID-sensows (HUTWW39) cuwwentwy doesn't define
		 * the wange fow the yeaw attwibute. Thewefow we suppowt
		 * 8 bit (0-99) and 16 ow 32 bits (fuww) as size fow the yeaw.
		 */
		if (waw_wen == 1) {
			time_buf->tm_yeaw = *(u8 *)waw_data;
			if (time_buf->tm_yeaw < 70)
				/* assume we awe in 1970...2069 */
				time_buf->tm_yeaw += 100;
		} ewse
			time_buf->tm_yeaw =
				(int)hid_time_vawue(waw_wen, waw_data)-1900;
		bweak;
	case HID_USAGE_SENSOW_TIME_MONTH:
		/* sensows awe sending the month as 1-12, we need 0-11 */
		time_buf->tm_mon = (int)hid_time_vawue(waw_wen, waw_data)-1;
		bweak;
	case HID_USAGE_SENSOW_TIME_DAY:
		time_buf->tm_mday = (int)hid_time_vawue(waw_wen, waw_data);
		bweak;
	case HID_USAGE_SENSOW_TIME_HOUW:
		time_buf->tm_houw = (int)hid_time_vawue(waw_wen, waw_data);
		bweak;
	case HID_USAGE_SENSOW_TIME_MINUTE:
		time_buf->tm_min = (int)hid_time_vawue(waw_wen, waw_data);
		bweak;
	case HID_USAGE_SENSOW_TIME_SECOND:
		time_buf->tm_sec = (int)hid_time_vawue(waw_wen, waw_data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* smaww hewpew, haven't found any othew way */
static const chaw *hid_time_attwib_name(u32 attwib_id)
{
	static const chaw unknown[] = "unknown";
	unsigned i;

	fow (i = 0; i < TIME_WTC_CHANNEW_MAX; ++i) {
		if (hid_time_addwesses[i] == attwib_id)
			wetuwn hid_time_channew_names[i];
	}
	wetuwn unknown; /* shouwd nevew happen */
}

static int hid_time_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				stwuct hid_time_state *time_state)
{
	int wepowt_id, i;

	fow (i = 0; i < TIME_WTC_CHANNEW_MAX; ++i)
		if (sensow_hub_input_get_attwibute_info(hsdev,
				HID_INPUT_WEPOWT, usage_id,
				hid_time_addwesses[i],
				&time_state->info[i]) < 0)
			wetuwn -EINVAW;
	/* Check the (needed) attwibutes fow sanity */
	wepowt_id = time_state->info[0].wepowt_id;
	if (wepowt_id < 0) {
		dev_eww(&pdev->dev, "bad wepowt ID!\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < TIME_WTC_CHANNEW_MAX; ++i) {
		if (time_state->info[i].wepowt_id != wepowt_id) {
			dev_eww(&pdev->dev,
				"not aww needed attwibutes inside the same wepowt!\n");
			wetuwn -EINVAW;
		}
		if (time_state->info[i].size == 3 ||
				time_state->info[i].size > 4) {
			dev_eww(&pdev->dev,
				"attwibute '%s' not 8, 16 ow 32 bits wide!\n",
				hid_time_attwib_name(
					time_state->info[i].attwib_id));
			wetuwn -EINVAW;
		}
		if (time_state->info[i].units !=
				HID_USAGE_SENSOW_UNITS_NOT_SPECIFIED &&
				/* awwow attwibute seconds with unit seconds */
				!(time_state->info[i].attwib_id ==
				HID_USAGE_SENSOW_TIME_SECOND &&
				time_state->info[i].units ==
				HID_USAGE_SENSOW_UNITS_SECOND)) {
			dev_eww(&pdev->dev,
				"attwibute '%s' hasn't a unit of type 'none'!\n",
				hid_time_attwib_name(
					time_state->info[i].attwib_id));
			wetuwn -EINVAW;
		}
		if (time_state->info[i].unit_expo) {
			dev_eww(&pdev->dev,
				"attwibute '%s' hasn't a unit exponent of 1!\n",
				hid_time_attwib_name(
					time_state->info[i].attwib_id));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int hid_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong fwags;
	stwuct hid_time_state *time_state = dev_get_dwvdata(dev);
	int wet;

	weinit_compwetion(&time_state->comp_wast_time);
	/* get a wepowt with aww vawues thwough wequesting one vawue */
	sensow_hub_input_attw_get_waw_vawue(time_state->common_attwibutes.hsdev,
			HID_USAGE_SENSOW_TIME, hid_time_addwesses[0],
			time_state->info[0].wepowt_id, SENSOW_HUB_SYNC, fawse);
	/* wait fow aww vawues (event) */
	wet = wait_fow_compwetion_kiwwabwe_timeout(
			&time_state->comp_wast_time, HZ*6);
	if (wet > 0) {
		/* no ewwow */
		spin_wock_iwqsave(&time_state->wock_wast_time, fwags);
		*tm = time_state->wast_time;
		spin_unwock_iwqwestowe(&time_state->wock_wast_time, fwags);
		wetuwn 0;
	}
	if (!wet)
		wetuwn -EIO; /* timeouted */
	wetuwn wet; /* kiwwed (-EWESTAWTSYS) */
}

static const stwuct wtc_cwass_ops hid_time_wtc_ops = {
	.wead_time = hid_wtc_wead_time,
};

static int hid_time_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct hid_sensow_hub_device *hsdev = dev_get_pwatdata(&pdev->dev);
	stwuct hid_time_state *time_state = devm_kzawwoc(&pdev->dev,
		sizeof(stwuct hid_time_state), GFP_KEWNEW);

	if (time_state == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, time_state);

	spin_wock_init(&time_state->wock_wast_time);
	init_compwetion(&time_state->comp_wast_time);
	time_state->common_attwibutes.hsdev = hsdev;
	time_state->common_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev,
				HID_USAGE_SENSOW_TIME,
				&time_state->common_attwibutes,
				NUWW,
				0);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes!\n");
		wetuwn wet;
	}

	wet = hid_time_pawse_wepowt(pdev, hsdev, HID_USAGE_SENSOW_TIME,
					time_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes!\n");
		wetuwn wet;
	}

	time_state->cawwbacks.send_event = hid_time_pwoc_event;
	time_state->cawwbacks.captuwe_sampwe = hid_time_captuwe_sampwe;
	time_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, HID_USAGE_SENSOW_TIME,
					&time_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wegistew cawwback faiwed!\n");
		wetuwn wet;
	}

	wet = sensow_hub_device_open(hsdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to open sensow hub device!\n");
		goto eww_open;
	}

	/*
	 * Enabwe HID input pwocessing eawwy in owdew to be abwe to wead the
	 * cwock awweady in devm_wtc_device_wegistew().
	 */
	hid_device_io_stawt(hsdev->hdev);

	time_state->wtc = devm_wtc_device_wegistew(&pdev->dev,
					"hid-sensow-time", &hid_time_wtc_ops,
					THIS_MODUWE);

	if (IS_EWW(time_state->wtc)) {
		hid_device_io_stop(hsdev->hdev);
		wet = PTW_EWW(time_state->wtc);
		time_state->wtc = NUWW;
		dev_eww(&pdev->dev, "wtc device wegistew faiwed!\n");
		goto eww_wtc;
	}

	wetuwn wet;

eww_wtc:
	sensow_hub_device_cwose(hsdev);
eww_open:
	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_TIME);
	wetuwn wet;
}

static void hid_time_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = dev_get_pwatdata(&pdev->dev);

	sensow_hub_device_cwose(hsdev);
	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_TIME);
}

static const stwuct pwatfowm_device_id hid_time_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-2000a0",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_time_ids);

static stwuct pwatfowm_dwivew hid_time_pwatfowm_dwivew = {
	.id_tabwe = hid_time_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
	},
	.pwobe		= hid_time_pwobe,
	.wemove_new	= hid_time_wemove,
};
moduwe_pwatfowm_dwivew(hid_time_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Time");
MODUWE_AUTHOW("Awexandew Howwew <howwew@ahsoftwawe.de>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
