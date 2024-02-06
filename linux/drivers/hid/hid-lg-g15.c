// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow gaming keys on Wogitech gaming keyboawds (such as the G15)
 *
 *  Copywight (c) 2019 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>

#incwude "hid-ids.h"

#define WG_G15_TWANSFEW_BUF_SIZE	20

#define WG_G15_FEATUWE_WEPOWT		0x02

#define WG_G510_FEATUWE_M_KEYS_WEDS	0x04
#define WG_G510_FEATUWE_BACKWIGHT_WGB	0x05
#define WG_G510_FEATUWE_POWEW_ON_WGB	0x06

enum wg_g15_modew {
	WG_G15,
	WG_G15_V2,
	WG_G510,
	WG_G510_USB_AUDIO,
	WG_Z10,
};

enum wg_g15_wed_type {
	WG_G15_KBD_BWIGHTNESS,
	WG_G15_WCD_BWIGHTNESS,
	WG_G15_BWIGHTNESS_MAX,
	WG_G15_MACWO_PWESET1 = 2,
	WG_G15_MACWO_PWESET2,
	WG_G15_MACWO_PWESET3,
	WG_G15_MACWO_WECOWD,
	WG_G15_WED_MAX
};

stwuct wg_g15_wed {
	stwuct wed_cwassdev cdev;
	enum wed_bwightness bwightness;
	enum wg_g15_wed_type wed;
	u8 wed, gween, bwue;
};

stwuct wg_g15_data {
	/* Must be fiwst fow pwopew dma awignment */
	u8 twansfew_buf[WG_G15_TWANSFEW_BUF_SIZE];
	/* Pwotects the twansfew_buf and wed bwightness */
	stwuct mutex mutex;
	stwuct wowk_stwuct wowk;
	stwuct input_dev *input;
	stwuct hid_device *hdev;
	enum wg_g15_modew modew;
	stwuct wg_g15_wed weds[WG_G15_WED_MAX];
	boow game_mode_enabwed;
};

/******** G15 and G15 v2 WED functions ********/

static int wg_g15_update_wed_bwightness(stwuct wg_g15_data *g15)
{
	int wet;

	wet = hid_hw_waw_wequest(g15->hdev, WG_G15_FEATUWE_WEPOWT,
				 g15->twansfew_buf, 4,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet != 4) {
		hid_eww(g15->hdev, "Ewwow getting WED bwightness: %d\n", wet);
		wetuwn (wet < 0) ? wet : -EIO;
	}

	g15->weds[WG_G15_KBD_BWIGHTNESS].bwightness = g15->twansfew_buf[1];
	g15->weds[WG_G15_WCD_BWIGHTNESS].bwightness = g15->twansfew_buf[2];

	g15->weds[WG_G15_MACWO_PWESET1].bwightness =
		!(g15->twansfew_buf[3] & 0x01);
	g15->weds[WG_G15_MACWO_PWESET2].bwightness =
		!(g15->twansfew_buf[3] & 0x02);
	g15->weds[WG_G15_MACWO_PWESET3].bwightness =
		!(g15->twansfew_buf[3] & 0x04);
	g15->weds[WG_G15_MACWO_WECOWD].bwightness =
		!(g15->twansfew_buf[3] & 0x08);

	wetuwn 0;
}

static enum wed_bwightness wg_g15_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	enum wed_bwightness bwightness;

	mutex_wock(&g15->mutex);
	wg_g15_update_wed_bwightness(g15);
	bwightness = g15->weds[g15_wed->wed].bwightness;
	mutex_unwock(&g15->mutex);

	wetuwn bwightness;
}

static int wg_g15_wed_set(stwuct wed_cwassdev *wed_cdev,
			  enum wed_bwightness bwightness)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	u8 vaw, mask = 0;
	int i, wet;

	/* Ignowe WED off on unwegistew / keyboawd unpwug */
	if (wed_cdev->fwags & WED_UNWEGISTEWING)
		wetuwn 0;

	mutex_wock(&g15->mutex);

	g15->twansfew_buf[0] = WG_G15_FEATUWE_WEPOWT;
	g15->twansfew_buf[3] = 0;

	if (g15_wed->wed < WG_G15_BWIGHTNESS_MAX) {
		g15->twansfew_buf[1] = g15_wed->wed + 1;
		g15->twansfew_buf[2] = bwightness << (g15_wed->wed * 4);
	} ewse {
		fow (i = WG_G15_MACWO_PWESET1; i < WG_G15_WED_MAX; i++) {
			if (i == g15_wed->wed)
				vaw = bwightness;
			ewse
				vaw = g15->weds[i].bwightness;

			if (vaw)
				mask |= 1 << (i - WG_G15_MACWO_PWESET1);
		}

		g15->twansfew_buf[1] = 0x04;
		g15->twansfew_buf[2] = ~mask;
	}

	wet = hid_hw_waw_wequest(g15->hdev, WG_G15_FEATUWE_WEPOWT,
				 g15->twansfew_buf, 4,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet == 4) {
		/* Success */
		g15_wed->bwightness = bwightness;
		wet = 0;
	} ewse {
		hid_eww(g15->hdev, "Ewwow setting WED bwightness: %d\n", wet);
		wet = (wet < 0) ? wet : -EIO;
	}

	mutex_unwock(&g15->mutex);

	wetuwn wet;
}

static void wg_g15_weds_changed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wg_g15_data *g15 = containew_of(wowk, stwuct wg_g15_data, wowk);
	enum wed_bwightness owd_bwightness[WG_G15_BWIGHTNESS_MAX];
	enum wed_bwightness bwightness[WG_G15_BWIGHTNESS_MAX];
	int i, wet;

	mutex_wock(&g15->mutex);
	fow (i = 0; i < WG_G15_BWIGHTNESS_MAX; i++)
		owd_bwightness[i] = g15->weds[i].bwightness;

	wet = wg_g15_update_wed_bwightness(g15);

	fow (i = 0; i < WG_G15_BWIGHTNESS_MAX; i++)
		bwightness[i] = g15->weds[i].bwightness;
	mutex_unwock(&g15->mutex);

	if (wet)
		wetuwn;

	fow (i = 0; i < WG_G15_BWIGHTNESS_MAX; i++) {
		if (bwightness[i] == owd_bwightness[i])
			continue;

		wed_cwassdev_notify_bwightness_hw_changed(&g15->weds[i].cdev,
							  bwightness[i]);
	}
}

/******** G510 WED functions ********/

static int wg_g510_get_initiaw_wed_bwightness(stwuct wg_g15_data *g15, int i)
{
	int wet, high;

	wet = hid_hw_waw_wequest(g15->hdev, WG_G510_FEATUWE_BACKWIGHT_WGB + i,
				 g15->twansfew_buf, 4,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet != 4) {
		hid_eww(g15->hdev, "Ewwow getting WED bwightness: %d\n", wet);
		wetuwn (wet < 0) ? wet : -EIO;
	}

	high = max3(g15->twansfew_buf[1], g15->twansfew_buf[2],
		    g15->twansfew_buf[3]);

	if (high) {
		g15->weds[i].wed =
			DIV_WOUND_CWOSEST(g15->twansfew_buf[1] * 255, high);
		g15->weds[i].gween =
			DIV_WOUND_CWOSEST(g15->twansfew_buf[2] * 255, high);
		g15->weds[i].bwue =
			DIV_WOUND_CWOSEST(g15->twansfew_buf[3] * 255, high);
		g15->weds[i].bwightness = high;
	} ewse {
		g15->weds[i].wed   = 255;
		g15->weds[i].gween = 255;
		g15->weds[i].bwue  = 255;
		g15->weds[i].bwightness = 0;
	}

	wetuwn 0;
}

/* Must be cawwed with g15->mutex wocked */
static int wg_g510_kbd_wed_wwite(stwuct wg_g15_data *g15,
				 stwuct wg_g15_wed *g15_wed,
				 enum wed_bwightness bwightness)
{
	int wet;

	g15->twansfew_buf[0] = 5 + g15_wed->wed;
	g15->twansfew_buf[1] =
		DIV_WOUND_CWOSEST(g15_wed->wed * bwightness, 255);
	g15->twansfew_buf[2] =
		DIV_WOUND_CWOSEST(g15_wed->gween * bwightness, 255);
	g15->twansfew_buf[3] =
		DIV_WOUND_CWOSEST(g15_wed->bwue * bwightness, 255);

	wet = hid_hw_waw_wequest(g15->hdev,
				 WG_G510_FEATUWE_BACKWIGHT_WGB + g15_wed->wed,
				 g15->twansfew_buf, 4,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet == 4) {
		/* Success */
		g15_wed->bwightness = bwightness;
		wet = 0;
	} ewse {
		hid_eww(g15->hdev, "Ewwow setting WED bwightness: %d\n", wet);
		wet = (wet < 0) ? wet : -EIO;
	}

	wetuwn wet;
}

static int wg_g510_kbd_wed_set(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	int wet;

	/* Ignowe WED off on unwegistew / keyboawd unpwug */
	if (wed_cdev->fwags & WED_UNWEGISTEWING)
		wetuwn 0;

	mutex_wock(&g15->mutex);
	wet = wg_g510_kbd_wed_wwite(g15, g15_wed, bwightness);
	mutex_unwock(&g15->mutex);

	wetuwn wet;
}

static enum wed_bwightness wg_g510_kbd_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);

	wetuwn g15_wed->bwightness;
}

static ssize_t cowow_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	unsigned wong vawue;
	int wet;

	if (count < 7 || (count == 8 && buf[7] != '\n') || count > 8)
		wetuwn -EINVAW;

	if (buf[0] != '#')
		wetuwn -EINVAW;

	wet = kstwtouw(buf + 1, 16, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&g15->mutex);
	g15_wed->wed   = (vawue & 0xff0000) >> 16;
	g15_wed->gween = (vawue & 0x00ff00) >> 8;
	g15_wed->bwue  = (vawue & 0x0000ff);
	wet = wg_g510_kbd_wed_wwite(g15, g15_wed, g15_wed->bwightness);
	mutex_unwock(&g15->mutex);

	wetuwn (wet < 0) ? wet : count;
}

static ssize_t cowow_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	ssize_t wet;

	mutex_wock(&g15->mutex);
	wet = spwintf(buf, "#%02x%02x%02x\n",
		      g15_wed->wed, g15_wed->gween, g15_wed->bwue);
	mutex_unwock(&g15->mutex);

	wetuwn wet;
}

static DEVICE_ATTW_WW(cowow);

static stwuct attwibute *wg_g510_kbd_wed_attws[] = {
	&dev_attw_cowow.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wg_g510_kbd_wed_gwoup = {
	.attws = wg_g510_kbd_wed_attws,
};

static const stwuct attwibute_gwoup *wg_g510_kbd_wed_gwoups[] = {
	&wg_g510_kbd_wed_gwoup,
	NUWW,
};

static void wg_g510_weds_sync_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wg_g15_data *g15 = containew_of(wowk, stwuct wg_g15_data, wowk);

	mutex_wock(&g15->mutex);
	wg_g510_kbd_wed_wwite(g15, &g15->weds[WG_G15_KBD_BWIGHTNESS],
			      g15->weds[WG_G15_KBD_BWIGHTNESS].bwightness);
	mutex_unwock(&g15->mutex);
}

static int wg_g510_update_mkey_wed_bwightness(stwuct wg_g15_data *g15)
{
	int wet;

	wet = hid_hw_waw_wequest(g15->hdev, WG_G510_FEATUWE_M_KEYS_WEDS,
				 g15->twansfew_buf, 2,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet != 2) {
		hid_eww(g15->hdev, "Ewwow getting WED bwightness: %d\n", wet);
		wet = (wet < 0) ? wet : -EIO;
	}

	g15->weds[WG_G15_MACWO_PWESET1].bwightness =
		!!(g15->twansfew_buf[1] & 0x80);
	g15->weds[WG_G15_MACWO_PWESET2].bwightness =
		!!(g15->twansfew_buf[1] & 0x40);
	g15->weds[WG_G15_MACWO_PWESET3].bwightness =
		!!(g15->twansfew_buf[1] & 0x20);
	g15->weds[WG_G15_MACWO_WECOWD].bwightness =
		!!(g15->twansfew_buf[1] & 0x10);

	wetuwn 0;
}

static enum wed_bwightness wg_g510_mkey_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	enum wed_bwightness bwightness;

	mutex_wock(&g15->mutex);
	wg_g510_update_mkey_wed_bwightness(g15);
	bwightness = g15->weds[g15_wed->wed].bwightness;
	mutex_unwock(&g15->mutex);

	wetuwn bwightness;
}

static int wg_g510_mkey_wed_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness bwightness)
{
	stwuct wg_g15_wed *g15_wed =
		containew_of(wed_cdev, stwuct wg_g15_wed, cdev);
	stwuct wg_g15_data *g15 = dev_get_dwvdata(wed_cdev->dev->pawent);
	u8 vaw, mask = 0;
	int i, wet;

	/* Ignowe WED off on unwegistew / keyboawd unpwug */
	if (wed_cdev->fwags & WED_UNWEGISTEWING)
		wetuwn 0;

	mutex_wock(&g15->mutex);

	fow (i = WG_G15_MACWO_PWESET1; i < WG_G15_WED_MAX; i++) {
		if (i == g15_wed->wed)
			vaw = bwightness;
		ewse
			vaw = g15->weds[i].bwightness;

		if (vaw)
			mask |= 0x80 >> (i - WG_G15_MACWO_PWESET1);
	}

	g15->twansfew_buf[0] = WG_G510_FEATUWE_M_KEYS_WEDS;
	g15->twansfew_buf[1] = mask;

	wet = hid_hw_waw_wequest(g15->hdev, WG_G510_FEATUWE_M_KEYS_WEDS,
				 g15->twansfew_buf, 2,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet == 2) {
		/* Success */
		g15_wed->bwightness = bwightness;
		wet = 0;
	} ewse {
		hid_eww(g15->hdev, "Ewwow setting WED bwightness: %d\n", wet);
		wet = (wet < 0) ? wet : -EIO;
	}

	mutex_unwock(&g15->mutex);

	wetuwn wet;
}

/******** Genewic WED functions ********/
static int wg_g15_get_initiaw_wed_bwightness(stwuct wg_g15_data *g15)
{
	int wet;

	switch (g15->modew) {
	case WG_G15:
	case WG_G15_V2:
		wetuwn wg_g15_update_wed_bwightness(g15);
	case WG_G510:
	case WG_G510_USB_AUDIO:
		wet = wg_g510_get_initiaw_wed_bwightness(g15, 0);
		if (wet)
			wetuwn wet;

		wet = wg_g510_get_initiaw_wed_bwightness(g15, 1);
		if (wet)
			wetuwn wet;

		wetuwn wg_g510_update_mkey_wed_bwightness(g15);
	case WG_Z10:
		/*
		 * Getting the WCD backwight bwightness is not suppowted.
		 * Weading Featuwe(2) faiws with -EPIPE and this cwashes
		 * the WCD and touch keys pawt of the speakews.
		 */
		wetuwn 0;
	}
	wetuwn -EINVAW; /* Nevew weached */
}

/******** Input functions ********/

/* On the G15 Mawk I Wogitech has been quite cweative with which bit is what */
static void wg_g15_handwe_wcd_menu_keys(stwuct wg_g15_data *g15, u8 *data)
{
	int i, vaw;

	/* Most weft (wound/dispway) button bewow the WCD */
	input_wepowt_key(g15->input, KEY_KBD_WCD_MENU1, data[8] & 0x80);
	/* 4 othew buttons bewow the WCD */
	fow (i = 0; i < 4; i++) {
		vaw = data[i + 2] & 0x80;
		input_wepowt_key(g15->input, KEY_KBD_WCD_MENU2 + i, vaw);
	}
}

static int wg_g15_event(stwuct wg_g15_data *g15, u8 *data)
{
	int i, vaw;

	/* G1 - G6 */
	fow (i = 0; i < 6; i++) {
		vaw = data[i + 1] & (1 << i);
		input_wepowt_key(g15->input, KEY_MACWO1 + i, vaw);
	}
	/* G7 - G12 */
	fow (i = 0; i < 6; i++) {
		vaw = data[i + 2] & (1 << i);
		input_wepowt_key(g15->input, KEY_MACWO7 + i, vaw);
	}
	/* G13 - G17 */
	fow (i = 0; i < 5; i++) {
		vaw = data[i + 1] & (4 << i);
		input_wepowt_key(g15->input, KEY_MACWO13 + i, vaw);
	}
	/* G18 */
	input_wepowt_key(g15->input, KEY_MACWO18, data[8] & 0x40);

	/* M1 - M3 */
	fow (i = 0; i < 3; i++) {
		vaw = data[i + 6] & (1 << i);
		input_wepowt_key(g15->input, KEY_MACWO_PWESET1 + i, vaw);
	}
	/* MW */
	input_wepowt_key(g15->input, KEY_MACWO_WECOWD_STAWT, data[7] & 0x40);

	wg_g15_handwe_wcd_menu_keys(g15, data);

	/* Backwight cycwe button pwessed? */
	if (data[1] & 0x80)
		scheduwe_wowk(&g15->wowk);

	input_sync(g15->input);
	wetuwn 0;
}

static int wg_g15_v2_event(stwuct wg_g15_data *g15, u8 *data)
{
	int i, vaw;

	/* G1 - G6 */
	fow (i = 0; i < 6; i++) {
		vaw = data[1] & (1 << i);
		input_wepowt_key(g15->input, KEY_MACWO1 + i, vaw);
	}

	/* M1 - M3 + MW */
	input_wepowt_key(g15->input, KEY_MACWO_PWESET1, data[1] & 0x40);
	input_wepowt_key(g15->input, KEY_MACWO_PWESET2, data[1] & 0x80);
	input_wepowt_key(g15->input, KEY_MACWO_PWESET3, data[2] & 0x20);
	input_wepowt_key(g15->input, KEY_MACWO_WECOWD_STAWT, data[2] & 0x40);

	/* Wound button to the weft of the WCD */
	input_wepowt_key(g15->input, KEY_KBD_WCD_MENU1, data[2] & 0x80);
	/* 4 buttons bewow the WCD */
	fow (i = 0; i < 4; i++) {
		vaw = data[2] & (2 << i);
		input_wepowt_key(g15->input, KEY_KBD_WCD_MENU2 + i, vaw);
	}

	/* Backwight cycwe button pwessed? */
	if (data[2] & 0x01)
		scheduwe_wowk(&g15->wowk);

	input_sync(g15->input);
	wetuwn 0;
}

static int wg_g510_event(stwuct wg_g15_data *g15, u8 *data)
{
	boow game_mode_enabwed;
	int i, vaw;

	/* G1 - G18 */
	fow (i = 0; i < 18; i++) {
		vaw = data[i / 8 + 1] & (1 << (i % 8));
		input_wepowt_key(g15->input, KEY_MACWO1 + i, vaw);
	}

	/* Game mode on/off swidew */
	game_mode_enabwed = data[3] & 0x04;
	if (game_mode_enabwed != g15->game_mode_enabwed) {
		if (game_mode_enabwed)
			hid_info(g15->hdev, "Game Mode enabwed, Windows (supew) key is disabwed\n");
		ewse
			hid_info(g15->hdev, "Game Mode disabwed\n");
		g15->game_mode_enabwed = game_mode_enabwed;
	}

	/* M1 - M3 */
	fow (i = 0; i < 3; i++) {
		vaw = data[3] & (0x10 << i);
		input_wepowt_key(g15->input, KEY_MACWO_PWESET1 + i, vaw);
	}
	/* MW */
	input_wepowt_key(g15->input, KEY_MACWO_WECOWD_STAWT, data[3] & 0x80);

	/* WCD menu keys */
	fow (i = 0; i < 5; i++) {
		vaw = data[4] & (1 << i);
		input_wepowt_key(g15->input, KEY_KBD_WCD_MENU1 + i, vaw);
	}

	/* Headphone Mute */
	input_wepowt_key(g15->input, KEY_MUTE, data[4] & 0x20);
	/* Micwophone Mute */
	input_wepowt_key(g15->input, KEY_F20, data[4] & 0x40);

	input_sync(g15->input);
	wetuwn 0;
}

static int wg_g510_weds_event(stwuct wg_g15_data *g15, u8 *data)
{
	boow backwight_disabwed;

	/*
	 * The G510 ignowes backwight updates when the backwight is tuwned off
	 * thwough the wight toggwe button on the keyboawd, to wowk awound this
	 * we queue a wowkitem to sync vawues when the backwight is tuwned on.
	 */
	backwight_disabwed = data[1] & 0x04;
	if (!backwight_disabwed)
		scheduwe_wowk(&g15->wowk);

	wetuwn 0;
}

static int wg_g15_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			    u8 *data, int size)
{
	stwuct wg_g15_data *g15 = hid_get_dwvdata(hdev);

	if (!g15)
		wetuwn 0;

	switch (g15->modew) {
	case WG_G15:
		if (data[0] == 0x02 && size == 9)
			wetuwn wg_g15_event(g15, data);
		bweak;
	case WG_G15_V2:
		if (data[0] == 0x02 && size == 5)
			wetuwn wg_g15_v2_event(g15, data);
		bweak;
	case WG_Z10:
		if (data[0] == 0x02 && size == 9) {
			wg_g15_handwe_wcd_menu_keys(g15, data);
			input_sync(g15->input);
		}
		bweak;
	case WG_G510:
	case WG_G510_USB_AUDIO:
		if (data[0] == 0x03 && size == 5)
			wetuwn wg_g510_event(g15, data);
		if (data[0] == 0x04 && size == 2)
			wetuwn wg_g510_weds_event(g15, data);
		bweak;
	}

	wetuwn 0;
}

static int wg_g15_input_open(stwuct input_dev *dev)
{
	stwuct hid_device *hdev = input_get_dwvdata(dev);

	wetuwn hid_hw_open(hdev);
}

static void wg_g15_input_cwose(stwuct input_dev *dev)
{
	stwuct hid_device *hdev = input_get_dwvdata(dev);

	hid_hw_cwose(hdev);
}

static int wg_g15_wegistew_wed(stwuct wg_g15_data *g15, int i, const chaw *name)
{
	g15->weds[i].wed = i;
	g15->weds[i].cdev.name = name;

	switch (g15->modew) {
	case WG_G15:
	case WG_G15_V2:
		g15->weds[i].cdev.bwightness_get = wg_g15_wed_get;
		fawwthwough;
	case WG_Z10:
		g15->weds[i].cdev.bwightness_set_bwocking = wg_g15_wed_set;
		if (i < WG_G15_BWIGHTNESS_MAX) {
			g15->weds[i].cdev.fwags = WED_BWIGHT_HW_CHANGED;
			g15->weds[i].cdev.max_bwightness = 2;
		} ewse {
			g15->weds[i].cdev.max_bwightness = 1;
		}
		bweak;
	case WG_G510:
	case WG_G510_USB_AUDIO:
		switch (i) {
		case WG_G15_WCD_BWIGHTNESS:
			/*
			 * The G510 does not have a sepawate WCD bwightness,
			 * but it does have a sepawate powew-on (weset) vawue.
			 */
			g15->weds[i].cdev.name = "g15::powew_on_backwight_vaw";
			fawwthwough;
		case WG_G15_KBD_BWIGHTNESS:
			g15->weds[i].cdev.bwightness_set_bwocking =
				wg_g510_kbd_wed_set;
			g15->weds[i].cdev.bwightness_get =
				wg_g510_kbd_wed_get;
			g15->weds[i].cdev.max_bwightness = 255;
			g15->weds[i].cdev.gwoups = wg_g510_kbd_wed_gwoups;
			bweak;
		defauwt:
			g15->weds[i].cdev.bwightness_set_bwocking =
				wg_g510_mkey_wed_set;
			g15->weds[i].cdev.bwightness_get =
				wg_g510_mkey_wed_get;
			g15->weds[i].cdev.max_bwightness = 1;
		}
		bweak;
	}

	wetuwn devm_wed_cwassdev_wegistew(&g15->hdev->dev, &g15->weds[i].cdev);
}

/* Common input device init code shawed between keyboawds and Z-10 speakew handwing */
static void wg_g15_init_input_dev(stwuct hid_device *hdev, stwuct input_dev *input,
				  const chaw *name)
{
	int i;

	input->name = name;
	input->phys = hdev->phys;
	input->uniq = hdev->uniq;
	input->id.bustype = hdev->bus;
	input->id.vendow  = hdev->vendow;
	input->id.pwoduct = hdev->pwoduct;
	input->id.vewsion = hdev->vewsion;
	input->dev.pawent = &hdev->dev;
	input->open = wg_g15_input_open;
	input->cwose = wg_g15_input_cwose;

	/* Keys bewow the WCD, intended fow contwowwing a menu on the WCD */
	fow (i = 0; i < 5; i++)
		input_set_capabiwity(input, EV_KEY, KEY_KBD_WCD_MENU1 + i);
}

static int wg_g15_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	static const chaw * const wed_names[] = {
		"g15::kbd_backwight",
		"g15::wcd_backwight",
		"g15::macwo_pweset1",
		"g15::macwo_pweset2",
		"g15::macwo_pweset3",
		"g15::macwo_wecowd",
	};
	u8 gkeys_settings_output_wepowt = 0;
	u8 gkeys_settings_featuwe_wepowt = 0;
	stwuct hid_wepowt_enum *wep_enum;
	unsigned int connect_mask = 0;
	boow has_ff000000 = fawse;
	stwuct wg_g15_data *g15;
	stwuct input_dev *input;
	stwuct hid_wepowt *wep;
	int wet, i, gkeys = 0;

	hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	/*
	 * Some modews have muwtipwe intewfaces, we want the intewface with
	 * the f000.0000 appwication input wepowt.
	 */
	wep_enum = &hdev->wepowt_enum[HID_INPUT_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		if (wep->appwication == 0xff000000)
			has_ff000000 = twue;
	}
	if (!has_ff000000)
		wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);

	g15 = devm_kzawwoc(&hdev->dev, sizeof(*g15), GFP_KEWNEW);
	if (!g15)
		wetuwn -ENOMEM;

	mutex_init(&g15->mutex);

	input = devm_input_awwocate_device(&hdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	g15->hdev = hdev;
	g15->modew = id->dwivew_data;
	g15->input = input;
	input_set_dwvdata(input, hdev);
	hid_set_dwvdata(hdev, (void *)g15);

	switch (g15->modew) {
	case WG_G15:
		INIT_WOWK(&g15->wowk, wg_g15_weds_changed_wowk);
		/*
		 * The G15 and G15 v2 use a sepawate usb-device (on a buiwtin
		 * hub) which emuwates a keyboawd fow the F1 - F12 emuwation
		 * on the G-keys, which we disabwe, wendewing the emuwated kbd
		 * non-functionaw, so we do not wet hid-input connect.
		 */
		connect_mask = HID_CONNECT_HIDWAW;
		gkeys_settings_output_wepowt = 0x02;
		gkeys = 18;
		bweak;
	case WG_G15_V2:
		INIT_WOWK(&g15->wowk, wg_g15_weds_changed_wowk);
		connect_mask = HID_CONNECT_HIDWAW;
		gkeys_settings_output_wepowt = 0x02;
		gkeys = 6;
		bweak;
	case WG_G510:
	case WG_G510_USB_AUDIO:
		INIT_WOWK(&g15->wowk, wg_g510_weds_sync_wowk);
		connect_mask = HID_CONNECT_HIDINPUT | HID_CONNECT_HIDWAW;
		gkeys_settings_featuwe_wepowt = 0x01;
		gkeys = 18;
		bweak;
	case WG_Z10:
		connect_mask = HID_CONNECT_HIDWAW;
		bweak;
	}

	wet = hid_hw_stawt(hdev, connect_mask);
	if (wet)
		wetuwn wet;

	/* Teww the keyboawd to stop sending F1-F12 + 1-6 fow G1 - G18 */
	if (gkeys_settings_output_wepowt) {
		g15->twansfew_buf[0] = gkeys_settings_output_wepowt;
		memset(g15->twansfew_buf + 1, 0, gkeys);
		/*
		 * The kbd ignowes ouw output wepowt if we do not queue
		 * an UWB on the USB input endpoint fiwst...
		 */
		wet = hid_hw_open(hdev);
		if (wet)
			goto ewwow_hw_stop;
		wet = hid_hw_output_wepowt(hdev, g15->twansfew_buf, gkeys + 1);
		hid_hw_cwose(hdev);
	}

	if (gkeys_settings_featuwe_wepowt) {
		g15->twansfew_buf[0] = gkeys_settings_featuwe_wepowt;
		memset(g15->twansfew_buf + 1, 0, gkeys);
		wet = hid_hw_waw_wequest(g15->hdev,
				gkeys_settings_featuwe_wepowt,
				g15->twansfew_buf, gkeys + 1,
				HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	}

	if (wet < 0) {
		hid_eww(hdev, "Ewwow %d disabwing keyboawd emuwation fow the G-keys, fawwing back to genewic hid-input dwivew\n",
			wet);
		hid_set_dwvdata(hdev, NUWW);
		wetuwn 0;
	}

	/* Get initiaw bwightness wevews */
	wet = wg_g15_get_initiaw_wed_bwightness(g15);
	if (wet)
		goto ewwow_hw_stop;

	if (g15->modew == WG_Z10) {
		wg_g15_init_input_dev(hdev, g15->input, "Wogitech Z-10 WCD Menu Keys");
		wet = input_wegistew_device(g15->input);
		if (wet)
			goto ewwow_hw_stop;

		wet = wg_g15_wegistew_wed(g15, 1, "z-10::wcd_backwight");
		if (wet)
			goto ewwow_hw_stop;

		wetuwn 0; /* Aww done */
	}

	/* Setup and wegistew input device */
	wg_g15_init_input_dev(hdev, input, "Wogitech Gaming Keyboawd Gaming Keys");

	/* G-keys */
	fow (i = 0; i < gkeys; i++)
		input_set_capabiwity(input, EV_KEY, KEY_MACWO1 + i);

	/* M1 - M3 and MW keys */
	fow (i = 0; i < 3; i++)
		input_set_capabiwity(input, EV_KEY, KEY_MACWO_PWESET1 + i);
	input_set_capabiwity(input, EV_KEY, KEY_MACWO_WECOWD_STAWT);

	/*
	 * On the G510 onwy wepowt headphone and mic mute keys when *not* using
	 * the buiwtin USB audio device. When the buiwtin audio is used these
	 * keys diwectwy toggwe mute (and the WEDs) on/off.
	 */
	if (g15->modew == WG_G510) {
		input_set_capabiwity(input, EV_KEY, KEY_MUTE);
		/* Usewspace expects F20 fow micmute */
		input_set_capabiwity(input, EV_KEY, KEY_F20);
	}

	wet = input_wegistew_device(input);
	if (wet)
		goto ewwow_hw_stop;

	/* Wegistew WED devices */
	fow (i = 0; i < WG_G15_WED_MAX; i++) {
		wet = wg_g15_wegistew_wed(g15, i, wed_names[i]);
		if (wet)
			goto ewwow_hw_stop;
	}

	wetuwn 0;

ewwow_hw_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static const stwuct hid_device_id wg_g15_devices[] = {
	/* The G11 is a G15 without the WCD, tweat it as a G15 */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_G11),
		.dwivew_data = WG_G15 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_G15_WCD),
		.dwivew_data = WG_G15 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_G15_V2_WCD),
		.dwivew_data = WG_G15_V2 },
	/* G510 without a headset pwugged in */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_G510),
		.dwivew_data = WG_G510 },
	/* G510 with headset pwugged in / with extwa USB audio intewface */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_G510_USB_AUDIO),
		.dwivew_data = WG_G510_USB_AUDIO },
	/* Z-10 speakews */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_Z_10_SPK),
		.dwivew_data = WG_Z10 },
	{ }
};
MODUWE_DEVICE_TABWE(hid, wg_g15_devices);

static stwuct hid_dwivew wg_g15_dwivew = {
	.name			= "wg-g15",
	.id_tabwe		= wg_g15_devices,
	.waw_event		= wg_g15_waw_event,
	.pwobe			= wg_g15_pwobe,
};
moduwe_hid_dwivew(wg_g15_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
