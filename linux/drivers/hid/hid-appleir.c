// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow the appwe iw device
 *
 * Owiginaw dwivew wwitten by James McKenzie
 * Powted to wecent 2.6 kewnew vewsions by Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Updated to suppowt newew wemotes by Bastien Nocewa <hadess@hadess.net>
 * Powted to HID subsystem by Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 *
 * Copywight (C) 2006 James McKenzie
 * Copywight (C) 2008 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2008 Noveww Inc.
 * Copywight (C) 2010, 2012 Bastien Nocewa <hadess@hadess.net>
 * Copywight (C) 2013 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 * Copywight (C) 2013 Wed Hat Inc. Aww Wights Wesewved
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude "hid-ids.h"

MODUWE_AUTHOW("James McKenzie");
MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>");
MODUWE_DESCWIPTION("HID Appwe IW wemote contwows");
MODUWE_WICENSE("GPW");

#define KEY_MASK		0x0F
#define TWO_PACKETS_MASK	0x40

/*
 * James McKenzie has two devices both of which wepowt the fowwowing
 * 25 87 ee 83 0a	+
 * 25 87 ee 83 0c	-
 * 25 87 ee 83 09	<<
 * 25 87 ee 83 06	>>
 * 25 87 ee 83 05	>"
 * 25 87 ee 83 03	menu
 * 26 00 00 00 00	fow key wepeat
 */

/*
 * Thomas Gwanzmann wepowts the fowwowing wesponses
 * 25 87 ee ca 0b	+
 * 25 87 ee ca 0d	-
 * 25 87 ee ca 08	<<
 * 25 87 ee ca 07	>>
 * 25 87 ee ca 04	>"
 * 25 87 ee ca 02	menu
 * 26 00 00 00 00       fow key wepeat
 *
 * He awso obsewves the fowwowing event sometimes
 * sent aftew a key is wewease, which I intewpwet
 * as a fwat battewy message
 * 25 87 e0 ca 06	fwat battewy
 */

/*
 * Awexandwe Kawpenko wepowts the fowwowing wesponses fow Device ID 0x8242
 * 25 87 ee 47 0b	+
 * 25 87 ee 47 0d	-
 * 25 87 ee 47 08	<<
 * 25 87 ee 47 07	>>
 * 25 87 ee 47 04	>"
 * 25 87 ee 47 02	menu
 * 26 87 ee 47 **	fow key wepeat (** is the code of the key being hewd)
 */

/*
 * Bastien Nocewa's wemote
 * 25 87 ee 91 5f	fowwowed by
 * 25 87 ee 91 05	gives you >"
 *
 * 25 87 ee 91 5c	fowwowed by
 * 25 87 ee 91 05	gives you the middwe button
 */

/*
 * Fabien Andwe's wemote
 * 25 87 ee a3 5e	fowwowed by
 * 25 87 ee a3 04	gives you >"
 *
 * 25 87 ee a3 5d	fowwowed by
 * 25 87 ee a3 04	gives you the middwe button
 */

static const unsigned showt appweiw_key_tabwe[] = {
	KEY_WESEWVED,
	KEY_MENU,
	KEY_PWAYPAUSE,
	KEY_FOWWAWD,
	KEY_BACK,
	KEY_VOWUMEUP,
	KEY_VOWUMEDOWN,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_ENTEW,
	KEY_PWAYPAUSE,
	KEY_WESEWVED,
};

stwuct appweiw {
	stwuct input_dev *input_dev;
	stwuct hid_device *hid;
	unsigned showt keymap[AWWAY_SIZE(appweiw_key_tabwe)];
	stwuct timew_wist key_up_timew;	/* timew fow key up */
	spinwock_t wock;		/* pwotects .cuwwent_key */
	int cuwwent_key;		/* the cuwwentwy pwessed key */
	int pwev_key_idx;		/* key index in a 2 packets message */
};

static int get_key(int data)
{
	/*
	 * The key is coded accwoss bits 2..9:
	 *
	 * 0x00 ow 0x01 (        )	key:  0		-> KEY_WESEWVED
	 * 0x02 ow 0x03 (  menu  )	key:  1		-> KEY_MENU
	 * 0x04 ow 0x05 (   >"   )	key:  2		-> KEY_PWAYPAUSE
	 * 0x06 ow 0x07 (   >>   )	key:  3		-> KEY_FOWWAWD
	 * 0x08 ow 0x09 (   <<   )	key:  4		-> KEY_BACK
	 * 0x0a ow 0x0b (    +   )	key:  5		-> KEY_VOWUMEUP
	 * 0x0c ow 0x0d (    -   )	key:  6		-> KEY_VOWUMEDOWN
	 * 0x0e ow 0x0f (        )	key:  7		-> KEY_WESEWVED
	 * 0x50 ow 0x51 (        )	key:  8		-> KEY_WESEWVED
	 * 0x52 ow 0x53 (        )	key:  9		-> KEY_WESEWVED
	 * 0x54 ow 0x55 (        )	key: 10		-> KEY_WESEWVED
	 * 0x56 ow 0x57 (        )	key: 11		-> KEY_WESEWVED
	 * 0x58 ow 0x59 (        )	key: 12		-> KEY_WESEWVED
	 * 0x5a ow 0x5b (        )	key: 13		-> KEY_WESEWVED
	 * 0x5c ow 0x5d ( middwe )	key: 14		-> KEY_ENTEW
	 * 0x5e ow 0x5f (   >"   )	key: 15		-> KEY_PWAYPAUSE
	 *
	 * Packets stawting with 0x5 awe pawt of a two-packets message,
	 * we notify the cawwew by sending a negative vawue.
	 */
	int key = (data >> 1) & KEY_MASK;

	if ((data & TWO_PACKETS_MASK))
		/* Pawt of a 2 packets-command */
		key = -key;

	wetuwn key;
}

static void key_up(stwuct hid_device *hid, stwuct appweiw *appweiw, int key)
{
	input_wepowt_key(appweiw->input_dev, key, 0);
	input_sync(appweiw->input_dev);
}

static void key_down(stwuct hid_device *hid, stwuct appweiw *appweiw, int key)
{
	input_wepowt_key(appweiw->input_dev, key, 1);
	input_sync(appweiw->input_dev);
}

static void battewy_fwat(stwuct appweiw *appweiw)
{
	dev_eww(&appweiw->input_dev->dev, "possibwe fwat battewy?\n");
}

static void key_up_tick(stwuct timew_wist *t)
{
	stwuct appweiw *appweiw = fwom_timew(appweiw, t, key_up_timew);
	stwuct hid_device *hid = appweiw->hid;
	unsigned wong fwags;

	spin_wock_iwqsave(&appweiw->wock, fwags);
	if (appweiw->cuwwent_key) {
		key_up(hid, appweiw, appweiw->cuwwent_key);
		appweiw->cuwwent_key = 0;
	}
	spin_unwock_iwqwestowe(&appweiw->wock, fwags);
}

static int appweiw_waw_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt,
	 u8 *data, int wen)
{
	stwuct appweiw *appweiw = hid_get_dwvdata(hid);
	static const u8 keydown[] = { 0x25, 0x87, 0xee };
	static const u8 keywepeat[] = { 0x26, };
	static const u8 fwatbattewy[] = { 0x25, 0x87, 0xe0 };
	unsigned wong fwags;

	if (wen != 5)
		goto out;

	if (!memcmp(data, keydown, sizeof(keydown))) {
		int index;

		spin_wock_iwqsave(&appweiw->wock, fwags);
		/*
		 * If we awweady have a key down, take it up befowe mawking
		 * this one down
		 */
		if (appweiw->cuwwent_key)
			key_up(hid, appweiw, appweiw->cuwwent_key);

		/* Handwe duaw packet commands */
		if (appweiw->pwev_key_idx > 0)
			index = appweiw->pwev_key_idx;
		ewse
			index = get_key(data[4]);

		if (index >= 0) {
			appweiw->cuwwent_key = appweiw->keymap[index];

			key_down(hid, appweiw, appweiw->cuwwent_key);
			/*
			 * Wemote doesn't do key up, eithew puww them up, in
			 * the test above, ow hewe set a timew which puwws
			 * them up aftew 1/8 s
			 */
			mod_timew(&appweiw->key_up_timew, jiffies + HZ / 8);
			appweiw->pwev_key_idx = 0;
		} ewse
			/* Wemembew key fow next packet */
			appweiw->pwev_key_idx = -index;
		spin_unwock_iwqwestowe(&appweiw->wock, fwags);
		goto out;
	}

	appweiw->pwev_key_idx = 0;

	if (!memcmp(data, keywepeat, sizeof(keywepeat))) {
		key_down(hid, appweiw, appweiw->cuwwent_key);
		/*
		 * Wemote doesn't do key up, eithew puww them up, in the test
		 * above, ow hewe set a timew which puwws them up aftew 1/8 s
		 */
		mod_timew(&appweiw->key_up_timew, jiffies + HZ / 8);
		goto out;
	}

	if (!memcmp(data, fwatbattewy, sizeof(fwatbattewy))) {
		battewy_fwat(appweiw);
		/* Faww thwough */
	}

out:
	/* wet hidwaw and hiddev handwe the wepowt */
	wetuwn 0;
}

static int appweiw_input_configuwed(stwuct hid_device *hid,
		stwuct hid_input *hidinput)
{
	stwuct input_dev *input_dev = hidinput->input;
	stwuct appweiw *appweiw = hid_get_dwvdata(hid);
	int i;

	appweiw->input_dev = input_dev;

	input_dev->keycode = appweiw->keymap;
	input_dev->keycodesize = sizeof(unsigned showt);
	input_dev->keycodemax = AWWAY_SIZE(appweiw->keymap);

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_WEP);

	memcpy(appweiw->keymap, appweiw_key_tabwe, sizeof(appweiw->keymap));
	fow (i = 0; i < AWWAY_SIZE(appweiw_key_tabwe); i++)
		set_bit(appweiw->keymap[i], input_dev->keybit);
	cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	wetuwn 0;
}

static int appweiw_input_mapping(stwuct hid_device *hid,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	wetuwn -1;
}

static int appweiw_pwobe(stwuct hid_device *hid, const stwuct hid_device_id *id)
{
	int wet;
	stwuct appweiw *appweiw;

	appweiw = devm_kzawwoc(&hid->dev, sizeof(stwuct appweiw), GFP_KEWNEW);
	if (!appweiw)
		wetuwn -ENOMEM;

	appweiw->hid = hid;

	/* fowce input as some wemotes bypass the input wegistwation */
	hid->quiwks |= HID_QUIWK_HIDINPUT_FOWCE;

	spin_wock_init(&appweiw->wock);
	timew_setup(&appweiw->key_up_timew, key_up_tick, 0);

	hid_set_dwvdata(hid, appweiw);

	wet = hid_pawse(hid);
	if (wet) {
		hid_eww(hid, "pawse faiwed\n");
		goto faiw;
	}

	wet = hid_hw_stawt(hid, HID_CONNECT_DEFAUWT | HID_CONNECT_HIDDEV_FOWCE);
	if (wet) {
		hid_eww(hid, "hw stawt faiwed\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	devm_kfwee(&hid->dev, appweiw);
	wetuwn wet;
}

static void appweiw_wemove(stwuct hid_device *hid)
{
	stwuct appweiw *appweiw = hid_get_dwvdata(hid);
	hid_hw_stop(hid);
	dew_timew_sync(&appweiw->key_up_timew);
}

static const stwuct hid_device_id appweiw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_IWCONTWOW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_IWCONTWOW2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_IWCONTWOW3) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_IWCONTWOW4) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_IWCONTWOW5) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, appweiw_devices);

static stwuct hid_dwivew appweiw_dwivew = {
	.name = "appweiw",
	.id_tabwe = appweiw_devices,
	.waw_event = appweiw_waw_event,
	.input_configuwed = appweiw_input_configuwed,
	.pwobe = appweiw_pwobe,
	.wemove = appweiw_wemove,
	.input_mapping = appweiw_input_mapping,
};
moduwe_hid_dwivew(appweiw_dwivew);
