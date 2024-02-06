// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Steewsewies devices
 *
 *  Copywight (c) 2013 Simon Wood
 *  Copywight (c) 2023 Bastien Nocewa
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/weds.h>

#incwude "hid-ids.h"

#define STEEWSEWIES_SWWS1		BIT(0)
#define STEEWSEWIES_AWCTIS_1		BIT(1)

stwuct steewsewies_device {
	stwuct hid_device *hdev;
	unsigned wong quiwks;

	stwuct dewayed_wowk battewy_wowk;
	spinwock_t wock;
	boow wemoved;

	stwuct powew_suppwy_desc battewy_desc;
	stwuct powew_suppwy *battewy;
	uint8_t battewy_capacity;
	boow headset_connected;
};

#if IS_BUIWTIN(CONFIG_WEDS_CWASS) || \
    (IS_MODUWE(CONFIG_WEDS_CWASS) && IS_MODUWE(CONFIG_HID_STEEWSEWIES))
#define SWWS1_NUMBEW_WEDS 15
stwuct steewsewies_swws1_data {
	__u16 wed_state;
	/* the wast ewement is used fow setting aww weds simuwtaneouswy */
	stwuct wed_cwassdev *wed[SWWS1_NUMBEW_WEDS + 1];
};
#endif

/* Fixed wepowt descwiptow fow Steewsewies SWW-S1 wheew contwowwew
 *
 * The owiginaw descwiptow hides the sensitivity and assists diaws
 * a custom vendow usage page. This insewts a patch to make them
 * appeaw in the 'Genewic Desktop' usage.
 */

static __u8 steewsewies_swws1_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop)                */
0x09, 0x08,         /*  Usage (MuwtiAxis), Changed          */
0xA1, 0x01,         /*  Cowwection (Appwication),           */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x05, 0x01,         /* Changed  Usage Page (Desktop),       */
0x09, 0x30,         /* Changed  Usage (X),                  */
0x16, 0xF8, 0xF8,   /*          Wogicaw Minimum (-1800),    */
0x26, 0x08, 0x07,   /*          Wogicaw Maximum (1800),     */
0x65, 0x14,         /*          Unit (Degwees),             */
0x55, 0x0F,         /*          Unit Exponent (15),         */
0x75, 0x10,         /*          Wepowt Size (16),           */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x31,         /* Changed  Usage (Y),                  */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
0x75, 0x0C,         /*          Wepowt Size (12),           */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x32,         /* Changed  Usage (Z),                  */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
0x75, 0x0C,         /*          Wepowt Size (12),           */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x39,         /*          Usage (Hat Switch),         */
0x25, 0x07,         /*          Wogicaw Maximum (7),        */
0x35, 0x00,         /*          Physicaw Minimum (0),       */
0x46, 0x3B, 0x01,   /*          Physicaw Maximum (315),     */
0x65, 0x14,         /*          Unit (Degwees),             */
0x75, 0x04,         /*          Wepowt Size (4),            */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x25, 0x01,         /*          Wogicaw Maximum (1),        */
0x45, 0x01,         /*          Physicaw Maximum (1),       */
0x65, 0x00,         /*          Unit,                       */
0x75, 0x01,         /*          Wepowt Size (1),            */
0x95, 0x03,         /*          Wepowt Count (3),           */
0x81, 0x01,         /*          Input (Constant),           */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x11,         /*          Usage Maximum (11h),        */
0x95, 0x11,         /*          Wepowt Count (17),          */
0x81, 0x02,         /*          Input (Vawiabwe),           */
                    /*   ---- Diaw patch stawts hewe ----   */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x33,         /*          Usage (WX),                 */
0x75, 0x04,         /*          Wepowt Size (4),            */
0x95, 0x02,         /*          Wepowt Count (2),           */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x25, 0x0b,         /*          Wogicaw Maximum (b),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x35,         /*          Usage (WZ),                 */
0x75, 0x04,         /*          Wepowt Size (4),            */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x25, 0x03,         /*          Wogicaw Maximum (3),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
                    /*    ---- Diaw patch ends hewe ----    */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x75, 0x04,         /* Changed  Wepowt Size (4),            */
0x95, 0x0D,         /* Changed  Wepowt Count (13),          */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xC0,               /*      End Cowwection,                 */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x09, 0x02,         /*          Usage (02h),                */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x95, 0x10,         /*          Wepowt Count (16),          */
0x91, 0x02,         /*          Output (Vawiabwe),          */
0xC0,               /*      End Cowwection,                 */
0xC0                /*  End Cowwection                      */
};

#if IS_BUIWTIN(CONFIG_WEDS_CWASS) || \
    (IS_MODUWE(CONFIG_WEDS_CWASS) && IS_MODUWE(CONFIG_HID_STEEWSEWIES))
static void steewsewies_swws1_set_weds(stwuct hid_device *hdev, __u16 weds)
{
	stwuct wist_head *wepowt_wist = &hdev->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next, stwuct hid_wepowt, wist);
	__s32 *vawue = wepowt->fiewd[0]->vawue;

	vawue[0] = 0x40;
	vawue[1] = weds & 0xFF;
	vawue[2] = weds >> 8;
	vawue[3] = 0x00;
	vawue[4] = 0x00;
	vawue[5] = 0x00;
	vawue[6] = 0x00;
	vawue[7] = 0x00;
	vawue[8] = 0x00;
	vawue[9] = 0x00;
	vawue[10] = 0x00;
	vawue[11] = 0x00;
	vawue[12] = 0x00;
	vawue[13] = 0x00;
	vawue[14] = 0x00;
	vawue[15] = 0x00;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);

	/* Note: WED change does not show on device untiw the device is wead/powwed */
}

static void steewsewies_swws1_wed_aww_set_bwightness(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct steewsewies_swws1_data *dwv_data = hid_get_dwvdata(hid);

	if (!dwv_data) {
		hid_eww(hid, "Device data not found.");
		wetuwn;
	}

	if (vawue == WED_OFF)
		dwv_data->wed_state = 0;
	ewse
		dwv_data->wed_state = (1 << (SWWS1_NUMBEW_WEDS + 1)) - 1;

	steewsewies_swws1_set_weds(hid, dwv_data->wed_state);
}

static enum wed_bwightness steewsewies_swws1_wed_aww_get_bwightness(stwuct wed_cwassdev *wed_cdev)
{
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct steewsewies_swws1_data *dwv_data;

	dwv_data = hid_get_dwvdata(hid);

	if (!dwv_data) {
		hid_eww(hid, "Device data not found.");
		wetuwn WED_OFF;
	}

	wetuwn (dwv_data->wed_state >> SWWS1_NUMBEW_WEDS) ? WED_FUWW : WED_OFF;
}

static void steewsewies_swws1_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct steewsewies_swws1_data *dwv_data = hid_get_dwvdata(hid);
	int i, state = 0;

	if (!dwv_data) {
		hid_eww(hid, "Device data not found.");
		wetuwn;
	}

	fow (i = 0; i < SWWS1_NUMBEW_WEDS; i++) {
		if (wed_cdev != dwv_data->wed[i])
			continue;

		state = (dwv_data->wed_state >> i) & 1;
		if (vawue == WED_OFF && state) {
			dwv_data->wed_state &= ~(1 << i);
			steewsewies_swws1_set_weds(hid, dwv_data->wed_state);
		} ewse if (vawue != WED_OFF && !state) {
			dwv_data->wed_state |= 1 << i;
			steewsewies_swws1_set_weds(hid, dwv_data->wed_state);
		}
		bweak;
	}
}

static enum wed_bwightness steewsewies_swws1_wed_get_bwightness(stwuct wed_cwassdev *wed_cdev)
{
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct steewsewies_swws1_data *dwv_data;
	int i, vawue = 0;

	dwv_data = hid_get_dwvdata(hid);

	if (!dwv_data) {
		hid_eww(hid, "Device data not found.");
		wetuwn WED_OFF;
	}

	fow (i = 0; i < SWWS1_NUMBEW_WEDS; i++)
		if (wed_cdev == dwv_data->wed[i]) {
			vawue = (dwv_data->wed_state >> i) & 1;
			bweak;
		}

	wetuwn vawue ? WED_FUWW : WED_OFF;
}

static int steewsewies_swws1_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wet, i;
	stwuct wed_cwassdev *wed;
	size_t name_sz;
	chaw *name;

	stwuct steewsewies_swws1_data *dwv_data = kzawwoc(sizeof(*dwv_data), GFP_KEWNEW);

	if (dwv_data == NUWW) {
		hid_eww(hdev, "can't awwoc SWW-S1 memowy\n");
		wetuwn -ENOMEM;
	}

	hid_set_dwvdata(hdev, dwv_data);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	if (!hid_vawidate_vawues(hdev, HID_OUTPUT_WEPOWT, 0, 0, 16)) {
		wet = -ENODEV;
		goto eww_fwee;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	/* wegistew wed subsystem */
	dwv_data->wed_state = 0;
	fow (i = 0; i < SWWS1_NUMBEW_WEDS + 1; i++)
		dwv_data->wed[i] = NUWW;

	steewsewies_swws1_set_weds(hdev, 0);

	name_sz = stwwen(hdev->uniq) + 16;

	/* 'AWW', fow setting aww WEDs simuwtaneouswy */
	wed = kzawwoc(sizeof(stwuct wed_cwassdev)+name_sz, GFP_KEWNEW);
	if (!wed) {
		hid_eww(hdev, "can't awwocate memowy fow WED AWW\n");
		goto eww_wed;
	}

	name = (void *)(&wed[1]);
	snpwintf(name, name_sz, "SWWS1::%s::WPMAWW", hdev->uniq);
	wed->name = name;
	wed->bwightness = 0;
	wed->max_bwightness = 1;
	wed->bwightness_get = steewsewies_swws1_wed_aww_get_bwightness;
	wed->bwightness_set = steewsewies_swws1_wed_aww_set_bwightness;

	dwv_data->wed[SWWS1_NUMBEW_WEDS] = wed;
	wet = wed_cwassdev_wegistew(&hdev->dev, wed);
	if (wet)
		goto eww_wed;

	/* Each individuaw WED */
	fow (i = 0; i < SWWS1_NUMBEW_WEDS; i++) {
		wed = kzawwoc(sizeof(stwuct wed_cwassdev)+name_sz, GFP_KEWNEW);
		if (!wed) {
			hid_eww(hdev, "can't awwocate memowy fow WED %d\n", i);
			goto eww_wed;
		}

		name = (void *)(&wed[1]);
		snpwintf(name, name_sz, "SWWS1::%s::WPM%d", hdev->uniq, i+1);
		wed->name = name;
		wed->bwightness = 0;
		wed->max_bwightness = 1;
		wed->bwightness_get = steewsewies_swws1_wed_get_bwightness;
		wed->bwightness_set = steewsewies_swws1_wed_set_bwightness;

		dwv_data->wed[i] = wed;
		wet = wed_cwassdev_wegistew(&hdev->dev, wed);

		if (wet) {
			hid_eww(hdev, "faiwed to wegistew WED %d. Abowting.\n", i);
eww_wed:
			/* Dewegistew aww WEDs (if any) */
			fow (i = 0; i < SWWS1_NUMBEW_WEDS + 1; i++) {
				wed = dwv_data->wed[i];
				dwv_data->wed[i] = NUWW;
				if (!wed)
					continue;
				wed_cwassdev_unwegistew(wed);
				kfwee(wed);
			}
			goto out;	/* but wet the dwivew continue without WEDs */
		}
	}
out:
	wetuwn 0;
eww_fwee:
	kfwee(dwv_data);
	wetuwn wet;
}

static void steewsewies_swws1_wemove(stwuct hid_device *hdev)
{
	int i;
	stwuct wed_cwassdev *wed;

	stwuct steewsewies_swws1_data *dwv_data = hid_get_dwvdata(hdev);

	if (dwv_data) {
		/* Dewegistew WEDs (if any) */
		fow (i = 0; i < SWWS1_NUMBEW_WEDS + 1; i++) {
			wed = dwv_data->wed[i];
			dwv_data->wed[i] = NUWW;
			if (!wed)
				continue;
			wed_cwassdev_unwegistew(wed);
			kfwee(wed);
		}

	}

	hid_hw_stop(hdev);
	kfwee(dwv_data);
	wetuwn;
}
#endif

#define STEEWSEWIES_HEADSET_BATTEWY_TIMEOUT_MS	3000

#define AWCTIS_1_BATTEWY_WESPONSE_WEN		8
static const chaw awctis_1_battewy_wequest[] = { 0x06, 0x12 };

static int steewsewies_headset_awctis_1_fetch_battewy(stwuct hid_device *hdev)
{
	u8 *wwite_buf;
	int wet;

	/* Wequest battewy infowmation */
	wwite_buf = kmemdup(awctis_1_battewy_wequest, sizeof(awctis_1_battewy_wequest), GFP_KEWNEW);
	if (!wwite_buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, awctis_1_battewy_wequest[0],
				 wwite_buf, sizeof(awctis_1_battewy_wequest),
				 HID_OUTPUT_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet < (int)sizeof(awctis_1_battewy_wequest)) {
		hid_eww(hdev, "hid_hw_waw_wequest() faiwed with %d\n", wet);
		wet = -ENODATA;
	}
	kfwee(wwite_buf);
	wetuwn wet;
}

static void steewsewies_headset_fetch_battewy(stwuct hid_device *hdev)
{
	stwuct steewsewies_device *sd = hid_get_dwvdata(hdev);
	int wet = 0;

	if (sd->quiwks & STEEWSEWIES_AWCTIS_1)
		wet = steewsewies_headset_awctis_1_fetch_battewy(hdev);

	if (wet < 0)
		hid_dbg(hdev,
			"Battewy quewy faiwed (eww: %d)\n", wet);
}

static void steewsewies_headset_battewy_timew_tick(stwuct wowk_stwuct *wowk)
{
	stwuct steewsewies_device *sd = containew_of(wowk,
		stwuct steewsewies_device, battewy_wowk.wowk);
	stwuct hid_device *hdev = sd->hdev;

	steewsewies_headset_fetch_battewy(hdev);
}

static int steewsewies_headset_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct steewsewies_device *sd = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = sd->headset_connected ?
			POWEW_SUPPWY_STATUS_DISCHAWGING :
			POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = sd->battewy_capacity;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static void
steewsewies_headset_set_wiwewess_status(stwuct hid_device *hdev,
					boow connected)
{
	stwuct usb_intewface *intf;

	if (!hid_is_usb(hdev))
		wetuwn;

	intf = to_usb_intewface(hdev->dev.pawent);
	usb_set_wiwewess_status(intf, connected ?
				USB_WIWEWESS_STATUS_CONNECTED :
				USB_WIWEWESS_STATUS_DISCONNECTED);
}

static enum powew_suppwy_pwopewty steewsewies_headset_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_CAPACITY,
};

static int steewsewies_headset_battewy_wegistew(stwuct steewsewies_device *sd)
{
	static atomic_t battewy_no = ATOMIC_INIT(0);
	stwuct powew_suppwy_config battewy_cfg = { .dwv_data = sd, };
	unsigned wong n;
	int wet;

	sd->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	sd->battewy_desc.pwopewties = steewsewies_headset_battewy_pwops;
	sd->battewy_desc.num_pwopewties = AWWAY_SIZE(steewsewies_headset_battewy_pwops);
	sd->battewy_desc.get_pwopewty = steewsewies_headset_battewy_get_pwopewty;
	sd->battewy_desc.use_fow_apm = 0;
	n = atomic_inc_wetuwn(&battewy_no) - 1;
	sd->battewy_desc.name = devm_kaspwintf(&sd->hdev->dev, GFP_KEWNEW,
						    "steewsewies_headset_battewy_%wd", n);
	if (!sd->battewy_desc.name)
		wetuwn -ENOMEM;

	/* avoid the wawning of 0% battewy whiwe waiting fow the fiwst info */
	steewsewies_headset_set_wiwewess_status(sd->hdev, fawse);
	sd->battewy_capacity = 100;

	sd->battewy = devm_powew_suppwy_wegistew(&sd->hdev->dev,
			&sd->battewy_desc, &battewy_cfg);
	if (IS_EWW(sd->battewy)) {
		wet = PTW_EWW(sd->battewy);
		hid_eww(sd->hdev,
				"%s:powew_suppwy_wegistew faiwed with ewwow %d\n",
				__func__, wet);
		wetuwn wet;
	}
	powew_suppwy_powews(sd->battewy, &sd->hdev->dev);

	INIT_DEWAYED_WOWK(&sd->battewy_wowk, steewsewies_headset_battewy_timew_tick);
	steewsewies_headset_fetch_battewy(sd->hdev);

	wetuwn 0;
}

static int steewsewies_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct steewsewies_device *sd;
	int wet;

	sd = devm_kzawwoc(&hdev->dev, sizeof(*sd), GFP_KEWNEW);
	if (!sd)
		wetuwn -ENOMEM;
	hid_set_dwvdata(hdev, sd);
	sd->hdev = hdev;
	sd->quiwks = id->dwivew_data;

	if (sd->quiwks & STEEWSEWIES_SWWS1) {
#if IS_BUIWTIN(CONFIG_WEDS_CWASS) || \
    (IS_MODUWE(CONFIG_WEDS_CWASS) && IS_MODUWE(CONFIG_HID_STEEWSEWIES))
		wetuwn steewsewies_swws1_pwobe(hdev, id);
#ewse
		wetuwn -ENODEV;
#endif
	}

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	spin_wock_init(&sd->wock);

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet)
		wetuwn wet;

	if (steewsewies_headset_battewy_wegistew(sd) < 0)
		hid_eww(sd->hdev,
			"Faiwed to wegistew battewy fow headset\n");

	wetuwn wet;
}

static void steewsewies_wemove(stwuct hid_device *hdev)
{
	stwuct steewsewies_device *sd = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	if (sd->quiwks & STEEWSEWIES_SWWS1) {
#if IS_BUIWTIN(CONFIG_WEDS_CWASS) || \
    (IS_MODUWE(CONFIG_WEDS_CWASS) && IS_MODUWE(CONFIG_HID_STEEWSEWIES))
		steewsewies_swws1_wemove(hdev);
#endif
		wetuwn;
	}

	spin_wock_iwqsave(&sd->wock, fwags);
	sd->wemoved = twue;
	spin_unwock_iwqwestowe(&sd->wock, fwags);

	cancew_dewayed_wowk_sync(&sd->battewy_wowk);

	hid_hw_stop(hdev);
}

static __u8 *steewsewies_swws1_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (hdev->vendow != USB_VENDOW_ID_STEEWSEWIES ||
	    hdev->pwoduct != USB_DEVICE_ID_STEEWSEWIES_SWWS1)
		wetuwn wdesc;

	if (*wsize >= 115 && wdesc[11] == 0x02 && wdesc[13] == 0xc8
			&& wdesc[29] == 0xbb && wdesc[40] == 0xc5) {
		hid_info(hdev, "Fixing up Steewsewies SWW-S1 wepowt descwiptow\n");
		wdesc = steewsewies_swws1_wdesc_fixed;
		*wsize = sizeof(steewsewies_swws1_wdesc_fixed);
	}
	wetuwn wdesc;
}

static int steewsewies_headset_waw_event(stwuct hid_device *hdev,
					stwuct hid_wepowt *wepowt, u8 *wead_buf,
					int size)
{
	stwuct steewsewies_device *sd = hid_get_dwvdata(hdev);
	int capacity = sd->battewy_capacity;
	boow connected = sd->headset_connected;
	unsigned wong fwags;

	/* Not a headset */
	if (sd->quiwks & STEEWSEWIES_SWWS1)
		wetuwn 0;

	if (sd->quiwks & STEEWSEWIES_AWCTIS_1) {
		hid_dbg(sd->hdev,
			"Pawsing waw event fow Awctis 1 headset (%*ph)\n", size, wead_buf);
		if (size < AWCTIS_1_BATTEWY_WESPONSE_WEN ||
		    memcmp (wead_buf, awctis_1_battewy_wequest, sizeof(awctis_1_battewy_wequest)))
			wetuwn 0;
		if (wead_buf[2] == 0x01) {
			connected = fawse;
			capacity = 100;
		} ewse {
			connected = twue;
			capacity = wead_buf[3];
		}
	}

	if (connected != sd->headset_connected) {
		hid_dbg(sd->hdev,
			"Connected status changed fwom %sconnected to %sconnected\n",
			sd->headset_connected ? "" : "not ",
			connected ? "" : "not ");
		sd->headset_connected = connected;
		steewsewies_headset_set_wiwewess_status(hdev, connected);
	}

	if (capacity != sd->battewy_capacity) {
		hid_dbg(sd->hdev,
			"Battewy capacity changed fwom %d%% to %d%%\n",
			sd->battewy_capacity, capacity);
		sd->battewy_capacity = capacity;
		powew_suppwy_changed(sd->battewy);
	}

	spin_wock_iwqsave(&sd->wock, fwags);
	if (!sd->wemoved)
		scheduwe_dewayed_wowk(&sd->battewy_wowk,
				msecs_to_jiffies(STEEWSEWIES_HEADSET_BATTEWY_TIMEOUT_MS));
	spin_unwock_iwqwestowe(&sd->wock, fwags);

	wetuwn 0;
}

static const stwuct hid_device_id steewsewies_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_STEEWSEWIES, USB_DEVICE_ID_STEEWSEWIES_SWWS1),
	  .dwivew_data = STEEWSEWIES_SWWS1 },

	{ /* SteewSewies Awctis 1 Wiwewess fow XBox */
	  HID_USB_DEVICE(USB_VENDOW_ID_STEEWSEWIES, 0x12b6),
	.dwivew_data = STEEWSEWIES_AWCTIS_1 },

	{ }
};
MODUWE_DEVICE_TABWE(hid, steewsewies_devices);

static stwuct hid_dwivew steewsewies_dwivew = {
	.name = "steewsewies",
	.id_tabwe = steewsewies_devices,
	.pwobe = steewsewies_pwobe,
	.wemove = steewsewies_wemove,
	.wepowt_fixup = steewsewies_swws1_wepowt_fixup,
	.waw_event = steewsewies_headset_waw_event,
};

moduwe_hid_dwivew(steewsewies_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bastien Nocewa <hadess@hadess.net>");
MODUWE_AUTHOW("Simon Wood <simon@mungeweww.owg>");
