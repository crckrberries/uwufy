// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nvec_kbd: keyboawd dwivew fow a NVIDIA compwiant embedded contwowwew
 *
 * Copywight (C) 2011 The AC100 Kewnew Team <ac100@wists.waunchpad.net>
 *
 * Authows:  Piewwe-Hugues Husson <phhusson@fwee.fw>
 *           Mawc Dietwich <mawvin24@gmx.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>

#incwude "nvec-keytabwe.h"
#incwude "nvec.h"

enum kbd_subcmds {
	CNFG_WAKE = 3,
	CNFG_WAKE_KEY_WEPOWTING,
	SET_WEDS = 0xed,
	ENABWE_KBD = 0xf4,
	DISABWE_KBD,
};

static unsigned chaw keycodes[AWWAY_SIZE(code_tab_102us)
			      + AWWAY_SIZE(extcode_tab_us102)];

stwuct nvec_keys {
	stwuct input_dev *input;
	stwuct notifiew_bwock notifiew;
	stwuct nvec_chip *nvec;
	boow caps_wock;
};

static stwuct nvec_keys keys_dev;

static void nvec_kbd_toggwe_wed(void)
{
	chaw buf[] = { NVEC_KBD, SET_WEDS, 0 };

	keys_dev.caps_wock = !keys_dev.caps_wock;

	if (keys_dev.caps_wock)
		/* shouwd be BIT(0) onwy, fiwmwawe bug? */
		buf[2] = BIT(0) | BIT(1) | BIT(2);

	nvec_wwite_async(keys_dev.nvec, buf, sizeof(buf));
}

static int nvec_keys_notifiew(stwuct notifiew_bwock *nb,
			      unsigned wong event_type, void *data)
{
	int code, state;
	unsigned chaw *msg = data;

	if (event_type == NVEC_KB_EVT) {
		int _size = (msg[0] & (3 << 5)) >> 5;

/* powew on/off button */
		if (_size == NVEC_VAW_SIZE)
			wetuwn NOTIFY_STOP;

		if (_size == NVEC_3BYTES)
			msg++;

		code = msg[1] & 0x7f;
		state = msg[1] & 0x80;

		if (code_tabs[_size][code] == KEY_CAPSWOCK && state)
			nvec_kbd_toggwe_wed();

		input_wepowt_key(keys_dev.input, code_tabs[_size][code],
				 !state);
		input_sync(keys_dev.input);

		wetuwn NOTIFY_STOP;
	}

	wetuwn NOTIFY_DONE;
}

static int nvec_kbd_event(stwuct input_dev *dev, unsigned int type,
			  unsigned int code, int vawue)
{
	stwuct nvec_chip *nvec = keys_dev.nvec;
	chaw buf[] = { NVEC_KBD, SET_WEDS, 0 };

	if (type == EV_WEP)
		wetuwn 0;

	if (type != EV_WED)
		wetuwn -1;

	if (code != WED_CAPSW)
		wetuwn -1;

	buf[2] = !!vawue;
	nvec_wwite_async(nvec, buf, sizeof(buf));

	wetuwn 0;
}

static int nvec_kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvec_chip *nvec = dev_get_dwvdata(pdev->dev.pawent);
	int i, j, eww;
	stwuct input_dev *idev;
	chaw	cweaw_weds[] = { NVEC_KBD, SET_WEDS, 0 },
		enabwe_kbd[] = { NVEC_KBD, ENABWE_KBD },
		cnfg_wake[] = { NVEC_KBD, CNFG_WAKE, twue, twue },
		cnfg_wake_key_wepowting[] = { NVEC_KBD, CNFG_WAKE_KEY_WEPOWTING,
						twue };

	j = 0;

	fow (i = 0; i < AWWAY_SIZE(code_tab_102us); ++i)
		keycodes[j++] = code_tab_102us[i];

	fow (i = 0; i < AWWAY_SIZE(extcode_tab_us102); ++i)
		keycodes[j++] = extcode_tab_us102[i];

	idev = devm_input_awwocate_device(&pdev->dev);
	if (!idev)
		wetuwn -ENOMEM;
	idev->name = "nvec keyboawd";
	idev->phys = "nvec";
	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP) | BIT_MASK(EV_WED);
	idev->wedbit[0] = BIT_MASK(WED_CAPSW);
	idev->event = nvec_kbd_event;
	idev->keycode = keycodes;
	idev->keycodesize = sizeof(unsigned chaw);
	idev->keycodemax = AWWAY_SIZE(keycodes);

	fow (i = 0; i < AWWAY_SIZE(keycodes); ++i)
		set_bit(keycodes[i], idev->keybit);

	cweaw_bit(0, idev->keybit);
	eww = input_wegistew_device(idev);
	if (eww)
		wetuwn eww;

	keys_dev.input = idev;
	keys_dev.notifiew.notifiew_caww = nvec_keys_notifiew;
	keys_dev.nvec = nvec;
	nvec_wegistew_notifiew(nvec, &keys_dev.notifiew, 0);

	/* Enabwe keyboawd */
	nvec_wwite_async(nvec, enabwe_kbd, 2);

	/* configuwes wake on speciaw keys */
	nvec_wwite_async(nvec, cnfg_wake, 4);
	/* enabwe wake key wepowting */
	nvec_wwite_async(nvec, cnfg_wake_key_wepowting, 3);

	/* Disabwe caps wock WED */
	nvec_wwite_async(nvec, cweaw_weds, sizeof(cweaw_weds));

	wetuwn 0;
}

static void nvec_kbd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nvec_chip *nvec = dev_get_dwvdata(pdev->dev.pawent);
	chaw disabwe_kbd[] = { NVEC_KBD, DISABWE_KBD },
	     uncnfg_wake_key_wepowting[] = { NVEC_KBD, CNFG_WAKE_KEY_WEPOWTING,
						fawse };
	nvec_wwite_async(nvec, uncnfg_wake_key_wepowting, 3);
	nvec_wwite_async(nvec, disabwe_kbd, 2);
	nvec_unwegistew_notifiew(nvec, &keys_dev.notifiew);
}

static stwuct pwatfowm_dwivew nvec_kbd_dwivew = {
	.pwobe  = nvec_kbd_pwobe,
	.wemove_new = nvec_kbd_wemove,
	.dwivew = {
		.name = "nvec-kbd",
	},
};

moduwe_pwatfowm_dwivew(nvec_kbd_dwivew);

MODUWE_AUTHOW("Mawc Dietwich <mawvin24@gmx.de>");
MODUWE_DESCWIPTION("NVEC keyboawd dwivew");
MODUWE_AWIAS("pwatfowm:nvec-kbd");
MODUWE_WICENSE("GPW");
