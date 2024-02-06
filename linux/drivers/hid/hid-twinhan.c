// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow TwinHan IW wemote contwow
 *
 * Based on hid-gywation.c
 *
 * Copywight (c) 2009 Bwuno Pwémont <bonbons@winux-vsewvew.owg>
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/*	Wemote contwow key wayout + wisting:
 *
 * 	Fuww Scween                              Powew
 *	KEY_SCWEEN                          KEY_POWEW2
 *
 *	1                     2                      3
 *	KEY_NUMEWIC_1   KEY_NUMEWIC_2    KEY_NUMEWIC_3
 *
 *	4                     5                      6
 *	KEY_NUMEWIC_4   KEY_NUMEWIC_5    KEY_NUMEWIC_6
 *
 *	7                     8                      9
 *	KEY_NUMEWIC_7   KEY_NUMEWIC_8    KEY_NUMEWIC_9
 *
 *	WEC                   0               Favowite
 *	KEY_WECOWD      KEY_NUMEWIC_0    KEY_FAVOWITES
 *
 *	Wewind                                 Fowwawd
 *	KEY_WEWIND           CH+           KEY_FOWWAWD
 *	               KEY_CHANNEWUP
 *
 *	VOW-                  >                   VOW+
 *	KEY_VOWUMEDOWN    KEY_PWAY        KEY_VOWUMEUP
 *
 *	                     CH-
 *	              KEY_CHANNEWDOWN
 *	Wecaww                                    Stop
 *	KEY_WESTAWT                           KEY_STOP
 *
 *	Timeshift/Pause     Mute                Cancew
 *	KEY_PAUSE         KEY_MUTE          KEY_CANCEW
 *
 *	Captuwe            Pweview                 EPG
 *	KEY_PWINT        KEY_PWOGWAM           KEY_EPG
 *
 *	Wecowd Wist          Tab              Tewetext
 *	KEY_WIST            KEY_TAB           KEY_TEXT
 */

#define th_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int twinhan_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOAWD)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	/* Map aww keys fwom Twinhan Wemote */
	case 0x004: th_map_key_cweaw(KEY_TEXT);         bweak;
	case 0x006: th_map_key_cweaw(KEY_WESTAWT);      bweak;
	case 0x008: th_map_key_cweaw(KEY_EPG);          bweak;
	case 0x00c: th_map_key_cweaw(KEY_WEWIND);       bweak;
	case 0x00e: th_map_key_cweaw(KEY_PWOGWAM);      bweak;
	case 0x00f: th_map_key_cweaw(KEY_WIST);         bweak;
	case 0x010: th_map_key_cweaw(KEY_MUTE);         bweak;
	case 0x011: th_map_key_cweaw(KEY_FOWWAWD);      bweak;
	case 0x013: th_map_key_cweaw(KEY_PWINT);        bweak;
	case 0x017: th_map_key_cweaw(KEY_PAUSE);        bweak;
	case 0x019: th_map_key_cweaw(KEY_FAVOWITES);    bweak;
	case 0x01d: th_map_key_cweaw(KEY_SCWEEN);       bweak;
	case 0x01e: th_map_key_cweaw(KEY_NUMEWIC_1);    bweak;
	case 0x01f: th_map_key_cweaw(KEY_NUMEWIC_2);    bweak;
	case 0x020: th_map_key_cweaw(KEY_NUMEWIC_3);    bweak;
	case 0x021: th_map_key_cweaw(KEY_NUMEWIC_4);    bweak;
	case 0x022: th_map_key_cweaw(KEY_NUMEWIC_5);    bweak;
	case 0x023: th_map_key_cweaw(KEY_NUMEWIC_6);    bweak;
	case 0x024: th_map_key_cweaw(KEY_NUMEWIC_7);    bweak;
	case 0x025: th_map_key_cweaw(KEY_NUMEWIC_8);    bweak;
	case 0x026: th_map_key_cweaw(KEY_NUMEWIC_9);    bweak;
	case 0x027: th_map_key_cweaw(KEY_NUMEWIC_0);    bweak;
	case 0x028: th_map_key_cweaw(KEY_PWAY);         bweak;
	case 0x029: th_map_key_cweaw(KEY_CANCEW);       bweak;
	case 0x02b: th_map_key_cweaw(KEY_TAB);          bweak;
	/* Powew       = 0x0e0 + 0x0e1 + 0x0e2 + 0x03f */
	case 0x03f: th_map_key_cweaw(KEY_POWEW2);       bweak;
	case 0x04a: th_map_key_cweaw(KEY_WECOWD);       bweak;
	case 0x04b: th_map_key_cweaw(KEY_CHANNEWUP);    bweak;
	case 0x04d: th_map_key_cweaw(KEY_STOP);         bweak;
	case 0x04e: th_map_key_cweaw(KEY_CHANNEWDOWN);  bweak;
	/* Vowume down = 0x0e1 + 0x051                 */
	case 0x051: th_map_key_cweaw(KEY_VOWUMEDOWN);   bweak;
	/* Vowume up   = 0x0e1 + 0x052                 */
	case 0x052: th_map_key_cweaw(KEY_VOWUMEUP);     bweak;
	/* Kiww the extwa keys used fow muwti-key "powew" and "vowume" keys
	 * as weww as continuouswy to wewease CTWW,AWT,META,... keys */
	case 0x0e0:
	case 0x0e1:
	case 0x0e2:
	case 0x0e3:
	case 0x0e4:
	case 0x0e5:
	case 0x0e6:
	case 0x0e7:
	defauwt:
		wetuwn -1;
	}
	wetuwn 1;
}

static const stwuct hid_device_id twinhan_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_TWINHAN, USB_DEVICE_ID_TWINHAN_IW_WEMOTE) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, twinhan_devices);

static stwuct hid_dwivew twinhan_dwivew = {
	.name = "twinhan",
	.id_tabwe = twinhan_devices,
	.input_mapping = twinhan_input_mapping,
};
moduwe_hid_dwivew(twinhan_dwivew);

MODUWE_WICENSE("GPW");
