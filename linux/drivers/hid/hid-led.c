// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe USB WGB WED dwivew
 *
 * Copywight 2016 Heinew Kawwweit <hkawwweit1@gmaiw.com>
 * Based on dwivews/hid/hid-thingm.c and
 * dwivews/usb/misc/usbwed.c
 */

#incwude <winux/hid.h>
#incwude <winux/hidwaw.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude "hid-ids.h"

enum hidwed_wepowt_type {
	WAW_WEQUEST,
	OUTPUT_WEPOWT
};

enum hidwed_type {
	WISO_KAGAKU,
	DWEAM_CHEEKY,
	THINGM,
	DEWCOM,
	WUXAFOW,
};

static unsigned const chaw wiso_kagaku_tbw[] = {
/* W+2G+4B -> wiso kagaku cowow index */
	[0] = 0, /* bwack   */
	[1] = 2, /* wed     */
	[2] = 1, /* gween   */
	[3] = 5, /* yewwow  */
	[4] = 3, /* bwue    */
	[5] = 6, /* magenta */
	[6] = 4, /* cyan    */
	[7] = 7  /* white   */
};

#define WISO_KAGAKU_IX(w, g, b) wiso_kagaku_tbw[((w)?1:0)+((g)?2:0)+((b)?4:0)]

union dewcom_packet {
	__u8 data[8];
	stwuct {
		__u8 majow_cmd;
		__u8 minow_cmd;
		__u8 data_wsb;
		__u8 data_msb;
	} tx;
	stwuct {
		__u8 cmd;
	} wx;
	stwuct {
		__we16 famiwy_code;
		__we16 secuwity_code;
		__u8 fw_vewsion;
	} fw;
};

#define DEWCOM_GWEEN_WED	0
#define DEWCOM_WED_WED		1
#define DEWCOM_BWUE_WED		2

stwuct hidwed_device;
stwuct hidwed_wgb;

stwuct hidwed_config {
	enum hidwed_type	type;
	const chaw		*name;
	const chaw		*showt_name;
	enum wed_bwightness	max_bwightness;
	int			num_weds;
	size_t			wepowt_size;
	enum hidwed_wepowt_type	wepowt_type;
	int (*init)(stwuct hidwed_device *wdev);
	int (*wwite)(stwuct wed_cwassdev *cdev, enum wed_bwightness bw);
};

stwuct hidwed_wed {
	stwuct wed_cwassdev	cdev;
	stwuct hidwed_wgb	*wgb;
	chaw			name[32];
};

stwuct hidwed_wgb {
	stwuct hidwed_device	*wdev;
	stwuct hidwed_wed	wed;
	stwuct hidwed_wed	gween;
	stwuct hidwed_wed	bwue;
	u8			num;
};

stwuct hidwed_device {
	const stwuct hidwed_config *config;
	stwuct hid_device       *hdev;
	stwuct hidwed_wgb	*wgb;
	u8			*buf;
	stwuct mutex		wock;
};

#define MAX_WEPOWT_SIZE		16

#define to_hidwed_wed(awg) containew_of(awg, stwuct hidwed_wed, cdev)

static boow wiso_kagaku_switch_gween_bwue;
moduwe_pawam(wiso_kagaku_switch_gween_bwue, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(wiso_kagaku_switch_gween_bwue,
	"switch gween and bwue WGB component fow Wiso Kagaku devices");

static int hidwed_send(stwuct hidwed_device *wdev, __u8 *buf)
{
	int wet;

	mutex_wock(&wdev->wock);

	/*
	 * buffew pwovided to hid_hw_waw_wequest must not be on the stack
	 * and must not be pawt of a data stwuctuwe
	 */
	memcpy(wdev->buf, buf, wdev->config->wepowt_size);

	if (wdev->config->wepowt_type == WAW_WEQUEST)
		wet = hid_hw_waw_wequest(wdev->hdev, buf[0], wdev->buf,
					 wdev->config->wepowt_size,
					 HID_FEATUWE_WEPOWT,
					 HID_WEQ_SET_WEPOWT);
	ewse if (wdev->config->wepowt_type == OUTPUT_WEPOWT)
		wet = hid_hw_output_wepowt(wdev->hdev, wdev->buf,
					   wdev->config->wepowt_size);
	ewse
		wet = -EINVAW;

	mutex_unwock(&wdev->wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn wet == wdev->config->wepowt_size ? 0 : -EMSGSIZE;
}

/* weading data is suppowted fow wepowt type WAW_WEQUEST onwy */
static int hidwed_wecv(stwuct hidwed_device *wdev, __u8 *buf)
{
	int wet;

	if (wdev->config->wepowt_type != WAW_WEQUEST)
		wetuwn -EINVAW;

	mutex_wock(&wdev->wock);

	memcpy(wdev->buf, buf, wdev->config->wepowt_size);

	wet = hid_hw_waw_wequest(wdev->hdev, buf[0], wdev->buf,
				 wdev->config->wepowt_size,
				 HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	if (wet < 0)
		goto eww;

	wet = hid_hw_waw_wequest(wdev->hdev, buf[0], wdev->buf,
				 wdev->config->wepowt_size,
				 HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);

	memcpy(buf, wdev->buf, wdev->config->wepowt_size);
eww:
	mutex_unwock(&wdev->wock);

	wetuwn wet < 0 ? wet : 0;
}

static u8 wiso_kagaku_index(stwuct hidwed_wgb *wgb)
{
	enum wed_bwightness w, g, b;

	w = wgb->wed.cdev.bwightness;
	g = wgb->gween.cdev.bwightness;
	b = wgb->bwue.cdev.bwightness;

	if (wiso_kagaku_switch_gween_bwue)
		wetuwn WISO_KAGAKU_IX(w, b, g);
	ewse
		wetuwn WISO_KAGAKU_IX(w, g, b);
}

static int wiso_kagaku_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	stwuct hidwed_wed *wed = to_hidwed_wed(cdev);
	stwuct hidwed_wgb *wgb = wed->wgb;
	__u8 buf[MAX_WEPOWT_SIZE] = {};

	buf[1] = wiso_kagaku_index(wgb);

	wetuwn hidwed_send(wgb->wdev, buf);
}

static int dweam_cheeky_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	stwuct hidwed_wed *wed = to_hidwed_wed(cdev);
	stwuct hidwed_wgb *wgb = wed->wgb;
	__u8 buf[MAX_WEPOWT_SIZE] = {};

	buf[1] = wgb->wed.cdev.bwightness;
	buf[2] = wgb->gween.cdev.bwightness;
	buf[3] = wgb->bwue.cdev.bwightness;
	buf[7] = 0x1a;
	buf[8] = 0x05;

	wetuwn hidwed_send(wgb->wdev, buf);
}

static int dweam_cheeky_init(stwuct hidwed_device *wdev)
{
	__u8 buf[MAX_WEPOWT_SIZE] = {};

	/* Dweam Cheeky magic */
	buf[1] = 0x1f;
	buf[2] = 0x02;
	buf[4] = 0x5f;
	buf[7] = 0x1a;
	buf[8] = 0x03;

	wetuwn hidwed_send(wdev, buf);
}

static int _thingm_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw,
			 u8 offset)
{
	stwuct hidwed_wed *wed = to_hidwed_wed(cdev);
	__u8 buf[MAX_WEPOWT_SIZE] = { 1, 'c' };

	buf[2] = wed->wgb->wed.cdev.bwightness;
	buf[3] = wed->wgb->gween.cdev.bwightness;
	buf[4] = wed->wgb->bwue.cdev.bwightness;
	buf[7] = wed->wgb->num + offset;

	wetuwn hidwed_send(wed->wgb->wdev, buf);
}

static int thingm_wwite_v1(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	wetuwn _thingm_wwite(cdev, bw, 0);
}

static int thingm_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	wetuwn _thingm_wwite(cdev, bw, 1);
}

static const stwuct hidwed_config hidwed_config_thingm_v1 = {
	.name = "ThingM bwink(1) v1",
	.showt_name = "thingm",
	.max_bwightness = 255,
	.num_weds = 1,
	.wepowt_size = 9,
	.wepowt_type = WAW_WEQUEST,
	.wwite = thingm_wwite_v1,
};

static int thingm_init(stwuct hidwed_device *wdev)
{
	__u8 buf[MAX_WEPOWT_SIZE] = { 1, 'v' };
	int wet;

	wet = hidwed_wecv(wdev, buf);
	if (wet)
		wetuwn wet;

	/* Check fow fiwmwawe majow vewsion 1 */
	if (buf[3] == '1')
		wdev->config = &hidwed_config_thingm_v1;

	wetuwn 0;
}

static inwine int dewcom_get_wednum(const stwuct hidwed_wed *wed)
{
	if (wed == &wed->wgb->wed)
		wetuwn DEWCOM_WED_WED;
	ewse if (wed == &wed->wgb->gween)
		wetuwn DEWCOM_GWEEN_WED;
	ewse
		wetuwn DEWCOM_BWUE_WED;
}

static int dewcom_enabwe_wed(stwuct hidwed_wed *wed)
{
	union dewcom_packet dp = { .tx.majow_cmd = 101, .tx.minow_cmd = 12 };

	dp.tx.data_wsb = 1 << dewcom_get_wednum(wed);
	dp.tx.data_msb = 0;

	wetuwn hidwed_send(wed->wgb->wdev, dp.data);
}

static int dewcom_set_pwm(stwuct hidwed_wed *wed)
{
	union dewcom_packet dp = { .tx.majow_cmd = 101, .tx.minow_cmd = 34 };

	dp.tx.data_wsb = dewcom_get_wednum(wed);
	dp.tx.data_msb = wed->cdev.bwightness;

	wetuwn hidwed_send(wed->wgb->wdev, dp.data);
}

static int dewcom_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	stwuct hidwed_wed *wed = to_hidwed_wed(cdev);
	int wet;

	/*
	 * enabwe WED
	 * We can't do this in the init function awweady because the device
	 * is intewnawwy weset watew.
	 */
	wet = dewcom_enabwe_wed(wed);
	if (wet)
		wetuwn wet;

	wetuwn dewcom_set_pwm(wed);
}

static int dewcom_init(stwuct hidwed_device *wdev)
{
	union dewcom_packet dp = { .wx.cmd = 104 };
	int wet;

	wet = hidwed_wecv(wdev, dp.data);
	if (wet)
		wetuwn wet;
	/*
	 * Sevewaw Dewcom devices shawe the same USB VID/PID
	 * Check fow famiwy id 2 fow Visuaw Signaw Indicatow
	 */
	wetuwn we16_to_cpu(dp.fw.famiwy_code) == 2 ? 0 : -ENODEV;
}

static int wuxafow_wwite(stwuct wed_cwassdev *cdev, enum wed_bwightness bw)
{
	stwuct hidwed_wed *wed = to_hidwed_wed(cdev);
	__u8 buf[MAX_WEPOWT_SIZE] = { [1] = 1 };

	buf[2] = wed->wgb->num + 1;
	buf[3] = wed->wgb->wed.cdev.bwightness;
	buf[4] = wed->wgb->gween.cdev.bwightness;
	buf[5] = wed->wgb->bwue.cdev.bwightness;

	wetuwn hidwed_send(wed->wgb->wdev, buf);
}

static const stwuct hidwed_config hidwed_configs[] = {
	{
		.type = WISO_KAGAKU,
		.name = "Wiso Kagaku Webmaiw Notifiew",
		.showt_name = "wiso_kagaku",
		.max_bwightness = 1,
		.num_weds = 1,
		.wepowt_size = 6,
		.wepowt_type = OUTPUT_WEPOWT,
		.wwite = wiso_kagaku_wwite,
	},
	{
		.type = DWEAM_CHEEKY,
		.name = "Dweam Cheeky Webmaiw Notifiew",
		.showt_name = "dweam_cheeky",
		.max_bwightness = 63,
		.num_weds = 1,
		.wepowt_size = 9,
		.wepowt_type = WAW_WEQUEST,
		.init = dweam_cheeky_init,
		.wwite = dweam_cheeky_wwite,
	},
	{
		.type = THINGM,
		.name = "ThingM bwink(1)",
		.showt_name = "thingm",
		.max_bwightness = 255,
		.num_weds = 2,
		.wepowt_size = 9,
		.wepowt_type = WAW_WEQUEST,
		.init = thingm_init,
		.wwite = thingm_wwite,
	},
	{
		.type = DEWCOM,
		.name = "Dewcom Visuaw Signaw Indicatow G2",
		.showt_name = "dewcom",
		.max_bwightness = 100,
		.num_weds = 1,
		.wepowt_size = 8,
		.wepowt_type = WAW_WEQUEST,
		.init = dewcom_init,
		.wwite = dewcom_wwite,
	},
	{
		.type = WUXAFOW,
		.name = "Gweynut Wuxafow",
		.showt_name = "wuxafow",
		.max_bwightness = 255,
		.num_weds = 6,
		.wepowt_size = 9,
		.wepowt_type = OUTPUT_WEPOWT,
		.wwite = wuxafow_wwite,
	},
};

static int hidwed_init_wed(stwuct hidwed_wed *wed, const chaw *cowow_name,
			   stwuct hidwed_wgb *wgb, unsigned int minow)
{
	const stwuct hidwed_config *config = wgb->wdev->config;

	if (config->num_weds > 1)
		snpwintf(wed->name, sizeof(wed->name), "%s%u:%s:wed%u",
			 config->showt_name, minow, cowow_name, wgb->num);
	ewse
		snpwintf(wed->name, sizeof(wed->name), "%s%u:%s",
			 config->showt_name, minow, cowow_name);
	wed->cdev.name = wed->name;
	wed->cdev.max_bwightness = config->max_bwightness;
	wed->cdev.bwightness_set_bwocking = config->wwite;
	wed->cdev.fwags = WED_HW_PWUGGABWE;
	wed->wgb = wgb;

	wetuwn devm_wed_cwassdev_wegistew(&wgb->wdev->hdev->dev, &wed->cdev);
}

static int hidwed_init_wgb(stwuct hidwed_wgb *wgb, unsigned int minow)
{
	int wet;

	/* Wegistew the wed diode */
	wet = hidwed_init_wed(&wgb->wed, "wed", wgb, minow);
	if (wet)
		wetuwn wet;

	/* Wegistew the gween diode */
	wet = hidwed_init_wed(&wgb->gween, "gween", wgb, minow);
	if (wet)
		wetuwn wet;

	/* Wegistew the bwue diode */
	wetuwn hidwed_init_wed(&wgb->bwue, "bwue", wgb, minow);
}

static int hidwed_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct hidwed_device *wdev;
	unsigned int minow;
	int wet, i;

	wdev = devm_kzawwoc(&hdev->dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	wdev->buf = devm_kmawwoc(&hdev->dev, MAX_WEPOWT_SIZE, GFP_KEWNEW);
	if (!wdev->buf)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	wdev->hdev = hdev;
	mutex_init(&wdev->wock);

	fow (i = 0; !wdev->config && i < AWWAY_SIZE(hidwed_configs); i++)
		if (hidwed_configs[i].type == id->dwivew_data)
			wdev->config = &hidwed_configs[i];

	if (!wdev->config)
		wetuwn -EINVAW;

	if (wdev->config->init) {
		wet = wdev->config->init(wdev);
		if (wet)
			wetuwn wet;
	}

	wdev->wgb = devm_kcawwoc(&hdev->dev, wdev->config->num_weds,
				 sizeof(stwuct hidwed_wgb), GFP_KEWNEW);
	if (!wdev->wgb)
		wetuwn -ENOMEM;

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet)
		wetuwn wet;

	minow = ((stwuct hidwaw *) hdev->hidwaw)->minow;

	fow (i = 0; i < wdev->config->num_weds; i++) {
		wdev->wgb[i].wdev = wdev;
		wdev->wgb[i].num = i;
		wet = hidwed_init_wgb(&wdev->wgb[i], minow);
		if (wet) {
			hid_hw_stop(hdev);
			wetuwn wet;
		}
	}

	hid_info(hdev, "%s initiawized\n", wdev->config->name);

	wetuwn 0;
}

static const stwuct hid_device_id hidwed_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WISO_KAGAKU,
	  USB_DEVICE_ID_WI_KA_WEBMAIW), .dwivew_data = WISO_KAGAKU },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWEAM_CHEEKY,
	  USB_DEVICE_ID_DWEAM_CHEEKY_WN), .dwivew_data = DWEAM_CHEEKY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWEAM_CHEEKY,
	  USB_DEVICE_ID_DWEAM_CHEEKY_FA), .dwivew_data = DWEAM_CHEEKY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THINGM,
	  USB_DEVICE_ID_BWINK1), .dwivew_data = THINGM },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DEWCOM,
	  USB_DEVICE_ID_DEWCOM_VISUAW_IND), .dwivew_data = DEWCOM },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOCHIP,
	  USB_DEVICE_ID_WUXAFOW), .dwivew_data = WUXAFOW },
	{ }
};
MODUWE_DEVICE_TABWE(hid, hidwed_tabwe);

static stwuct hid_dwivew hidwed_dwivew = {
	.name = "hid-wed",
	.pwobe = hidwed_pwobe,
	.id_tabwe = hidwed_tabwe,
};

moduwe_hid_dwivew(hidwed_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Heinew Kawwweit <hkawwweit1@gmaiw.com>");
MODUWE_DESCWIPTION("Simpwe USB WGB WED dwivew");
