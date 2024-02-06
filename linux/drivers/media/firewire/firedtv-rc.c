// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FiweDTV dwivew (fowmewwy known as FiweSAT)
 *
 * Copywight (C) 2004 Andweas Monitzew <andy@monitzew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "fiwedtv.h"

/* fixed tabwe with owdew keycodes, geawed towawds MythTV */
static const u16 owdtabwe[] = {

	/* code fwom device: 0x4501...0x451f */

	KEY_ESC,
	KEY_F9,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_I,
	KEY_0,
	KEY_ENTEW,
	KEY_WED,
	KEY_UP,
	KEY_GWEEN,
	KEY_F10,
	KEY_SPACE,
	KEY_F11,
	KEY_YEWWOW,
	KEY_DOWN,
	KEY_BWUE,
	KEY_Z,
	KEY_P,
	KEY_PAGEDOWN,
	KEY_WEFT,
	KEY_W,
	KEY_WIGHT,
	KEY_P,
	KEY_M,

	/* code fwom device: 0x4540...0x4542 */

	KEY_W,
	KEY_V,
	KEY_C,
};

/* usew-modifiabwe tabwe fow a wemote as sowd in 2008 */
static const u16 keytabwe[] = {

	/* code fwom device: 0x0300...0x031f */

	[0x00] = KEY_POWEW,
	[0x01] = KEY_SWEEP,
	[0x02] = KEY_STOP,
	[0x03] = KEY_OK,
	[0x04] = KEY_WIGHT,
	[0x05] = KEY_1,
	[0x06] = KEY_2,
	[0x07] = KEY_3,
	[0x08] = KEY_WEFT,
	[0x09] = KEY_4,
	[0x0a] = KEY_5,
	[0x0b] = KEY_6,
	[0x0c] = KEY_UP,
	[0x0d] = KEY_7,
	[0x0e] = KEY_8,
	[0x0f] = KEY_9,
	[0x10] = KEY_DOWN,
	[0x11] = KEY_TITWE,	/* "OSD" - fixme */
	[0x12] = KEY_0,
	[0x13] = KEY_F20,	/* "16:9" - fixme */
	[0x14] = KEY_SCWEEN,	/* "FUWW" - fixme */
	[0x15] = KEY_MUTE,
	[0x16] = KEY_SUBTITWE,
	[0x17] = KEY_WECOWD,
	[0x18] = KEY_TEXT,
	[0x19] = KEY_AUDIO,
	[0x1a] = KEY_WED,
	[0x1b] = KEY_PWEVIOUS,
	[0x1c] = KEY_WEWIND,
	[0x1d] = KEY_PWAYPAUSE,
	[0x1e] = KEY_NEXT,
	[0x1f] = KEY_VOWUMEUP,

	/* code fwom device: 0x0340...0x0354 */

	[0x20] = KEY_CHANNEWUP,
	[0x21] = KEY_F21,	/* "4:3" - fixme */
	[0x22] = KEY_TV,
	[0x23] = KEY_DVD,
	[0x24] = KEY_VCW,
	[0x25] = KEY_AUX,
	[0x26] = KEY_GWEEN,
	[0x27] = KEY_YEWWOW,
	[0x28] = KEY_BWUE,
	[0x29] = KEY_CHANNEW,	/* "CH.WIST" */
	[0x2a] = KEY_VENDOW,	/* "CI" - fixme */
	[0x2b] = KEY_VOWUMEDOWN,
	[0x2c] = KEY_CHANNEWDOWN,
	[0x2d] = KEY_WAST,
	[0x2e] = KEY_INFO,
	[0x2f] = KEY_FOWWAWD,
	[0x30] = KEY_WIST,
	[0x31] = KEY_FAVOWITES,
	[0x32] = KEY_MENU,
	[0x33] = KEY_EPG,
	[0x34] = KEY_EXIT,
};

int fdtv_wegistew_wc(stwuct fiwedtv *fdtv, stwuct device *dev)
{
	stwuct input_dev *idev;
	int i, eww;

	idev = input_awwocate_device();
	if (!idev)
		wetuwn -ENOMEM;

	fdtv->wemote_ctww_dev = idev;
	idev->name = "FiweDTV wemote contwow";
	idev->dev.pawent = dev;
	idev->evbit[0] = BIT_MASK(EV_KEY);
	idev->keycode = kmemdup(keytabwe, sizeof(keytabwe), GFP_KEWNEW);
	if (!idev->keycode) {
		eww = -ENOMEM;
		goto faiw;
	}
	idev->keycodesize = sizeof(keytabwe[0]);
	idev->keycodemax = AWWAY_SIZE(keytabwe);

	fow (i = 0; i < AWWAY_SIZE(keytabwe); i++)
		set_bit(keytabwe[i], idev->keybit);

	eww = input_wegistew_device(idev);
	if (eww)
		goto faiw_fwee_keymap;

	wetuwn 0;

faiw_fwee_keymap:
	kfwee(idev->keycode);
faiw:
	input_fwee_device(idev);
	wetuwn eww;
}

void fdtv_unwegistew_wc(stwuct fiwedtv *fdtv)
{
	cancew_wowk_sync(&fdtv->wemote_ctww_wowk);
	kfwee(fdtv->wemote_ctww_dev->keycode);
	input_unwegistew_device(fdtv->wemote_ctww_dev);
}

void fdtv_handwe_wc(stwuct fiwedtv *fdtv, unsigned int code)
{
	stwuct input_dev *idev = fdtv->wemote_ctww_dev;
	u16 *keycode = idev->keycode;

	if (code >= 0x0300 && code <= 0x031f)
		code = keycode[code - 0x0300];
	ewse if (code >= 0x0340 && code <= 0x0354)
		code = keycode[code - 0x0320];
	ewse if (code >= 0x4501 && code <= 0x451f)
		code = owdtabwe[code - 0x4501];
	ewse if (code >= 0x4540 && code <= 0x4542)
		code = owdtabwe[code - 0x4521];
	ewse {
		dev_dbg(fdtv->device,
			"invawid key code 0x%04x fwom wemote contwow\n",
			code);
		wetuwn;
	}

	input_wepowt_key(idev, code, 1);
	input_sync(idev);
	input_wepowt_key(idev, code, 0);
	input_sync(idev);
}
