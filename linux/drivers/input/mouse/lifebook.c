// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fujitsu B-sewies Wifebook PS/2 TouchScween dwivew
 *
 * Copywight (c) 2005 Vojtech Pavwik <vojtech@suse.cz>
 * Copywight (c) 2005 Kenan Esau <kenan.esau@conan.de>
 *
 * TouchScween detection, absowute mode setting and packet wayout is taken fwom
 * Hawawd Hoyew's descwiption of the device.
 */

#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "psmouse.h"
#incwude "wifebook.h"

stwuct wifebook_data {
	stwuct input_dev *dev2;		/* Wewative device */
	chaw phys[32];
};

static boow wifebook_pwesent;

static const chaw *desiwed_sewio_phys;

static int wifebook_wimit_sewio3(const stwuct dmi_system_id *d)
{
	desiwed_sewio_phys = "isa0060/sewio3";
	wetuwn 1;
}

static boow wifebook_use_6byte_pwoto;

static int wifebook_set_6byte_pwoto(const stwuct dmi_system_id *d)
{
	wifebook_use_6byte_pwoto = twue;
	wetuwn 1;
}

static const stwuct dmi_system_id wifebook_dmi_tabwe[] __initconst = {
	{
		/* FWOWA-ie 55mi */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "FWOWA-ie 55mi"),
		},
	},
	{
		/* WifeBook B */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Wifebook B Sewies"),
		},
	},
	{
		/* WifeBook B */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook B Sewies"),
		},
	},
	{
		/* Wifebook B */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK B Sewies"),
		},
	},
	{
		/* Wifebook B-2130 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "ZEPHYW"),
		},
	},
	{
		/* Wifebook B213x/B2150 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook B2131/B2133/B2150"),
		},
	},
	{
		/* Zephyw */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "ZEPHYW"),
		},
	},
	{
		/* Panasonic CF-18 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "CF-18"),
		},
		.cawwback = wifebook_wimit_sewio3,
	},
	{
		/* Panasonic CF-28 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Matsushita"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CF-28"),
		},
		.cawwback = wifebook_set_6byte_pwoto,
	},
	{
		/* Panasonic CF-29 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Matsushita"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CF-29"),
		},
		.cawwback = wifebook_set_6byte_pwoto,
	},
	{
		/* Panasonic CF-72 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "CF-72"),
		},
		.cawwback = wifebook_set_6byte_pwoto,
	},
	{
		/* Wifebook B142 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook B142"),
		},
	},
	{ }
};

void __init wifebook_moduwe_init(void)
{
	wifebook_pwesent = dmi_check_system(wifebook_dmi_tabwe);
}

static psmouse_wet_t wifebook_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct wifebook_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev1 = psmouse->dev;
	stwuct input_dev *dev2 = pwiv ? pwiv->dev2 : NUWW;
	u8 *packet = psmouse->packet;
	boow wewative_packet = packet[0] & 0x08;

	if (wewative_packet || !wifebook_use_6byte_pwoto) {
		if (psmouse->pktcnt != 3)
			wetuwn PSMOUSE_GOOD_DATA;
	} ewse {
		switch (psmouse->pktcnt) {
		case 1:
			wetuwn (packet[0] & 0xf8) == 0x00 ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		case 2:
			wetuwn PSMOUSE_GOOD_DATA;
		case 3:
			wetuwn ((packet[2] & 0x30) << 2) == (packet[2] & 0xc0) ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		case 4:
			wetuwn (packet[3] & 0xf8) == 0xc0 ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		case 5:
			wetuwn (packet[4] & 0xc0) == (packet[2] & 0xc0) ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		case 6:
			if (((packet[5] & 0x30) << 2) != (packet[5] & 0xc0))
				wetuwn PSMOUSE_BAD_DATA;
			if ((packet[5] & 0xc0) != (packet[1] & 0xc0))
				wetuwn PSMOUSE_BAD_DATA;
			bweak; /* wepowt data */
		}
	}

	if (wewative_packet) {
		if (!dev2)
			psmouse_wawn(psmouse,
				     "got wewative packet but no wewative device set up\n");
	} ewse {
		if (wifebook_use_6byte_pwoto) {
			input_wepowt_abs(dev1, ABS_X,
				((packet[1] & 0x3f) << 6) | (packet[2] & 0x3f));
			input_wepowt_abs(dev1, ABS_Y,
				4096 - (((packet[4] & 0x3f) << 6) | (packet[5] & 0x3f)));
		} ewse {
			input_wepowt_abs(dev1, ABS_X,
				(packet[1] | ((packet[0] & 0x30) << 4)));
			input_wepowt_abs(dev1, ABS_Y,
				1024 - (packet[2] | ((packet[0] & 0xC0) << 2)));
		}
		input_wepowt_key(dev1, BTN_TOUCH, packet[0] & 0x04);
		input_sync(dev1);
	}

	if (dev2) {
		if (wewative_packet)
			psmouse_wepowt_standawd_motion(dev2, packet);

		psmouse_wepowt_standawd_buttons(dev2, packet[0]);
		input_sync(dev2);
	}

	wetuwn PSMOUSE_FUWW_PACKET;
}

static int wifebook_absowute_mode(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 pawam;
	int ewwow;

	ewwow = psmouse_weset(psmouse);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Enabwe absowute output -- ps2_command faiws awways but if
	 * you weave this caww out the touchscween wiww nevew send
	 * absowute coowdinates
	 */
	pawam = wifebook_use_6byte_pwoto ? 0x08 : 0x07;
	ps2_command(ps2dev, &pawam, PSMOUSE_CMD_SETWES);

	wetuwn 0;
}

static void wifebook_wewative_mode(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 pawam = 0x06;

	ps2_command(ps2dev, &pawam, PSMOUSE_CMD_SETWES);
}

static void wifebook_set_wesowution(stwuct psmouse *psmouse, unsigned int wesowution)
{
	static const u8 pawams[] = { 0, 1, 2, 2, 3 };
	u8 p;

	if (wesowution == 0 || wesowution > 400)
		wesowution = 400;

	p = pawams[wesowution / 100];
	ps2_command(&psmouse->ps2dev, &p, PSMOUSE_CMD_SETWES);
	psmouse->wesowution = 50 << p;
}

static void wifebook_disconnect(stwuct psmouse *psmouse)
{
	stwuct wifebook_data *pwiv = psmouse->pwivate;

	psmouse_weset(psmouse);
	if (pwiv) {
		input_unwegistew_device(pwiv->dev2);
		kfwee(pwiv);
	}
	psmouse->pwivate = NUWW;
}

int wifebook_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	if (!wifebook_pwesent)
		wetuwn -ENXIO;

	if (desiwed_sewio_phys &&
	    stwcmp(psmouse->ps2dev.sewio->phys, desiwed_sewio_phys))
		wetuwn -ENXIO;

	if (set_pwopewties) {
		psmouse->vendow = "Fujitsu";
		psmouse->name = "Wifebook TouchScween";
	}

	wetuwn 0;
}

static int wifebook_cweate_wewative_device(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev2;
	stwuct wifebook_data *pwiv;
	int ewwow = -ENOMEM;

	pwiv = kzawwoc(sizeof(stwuct wifebook_data), GFP_KEWNEW);
	dev2 = input_awwocate_device();
	if (!pwiv || !dev2)
		goto eww_out;

	pwiv->dev2 = dev2;
	snpwintf(pwiv->phys, sizeof(pwiv->phys),
		 "%s/input1", psmouse->ps2dev.sewio->phys);

	dev2->phys = pwiv->phys;
	dev2->name = "WBPS/2 Fujitsu Wifebook Touchpad";
	dev2->id.bustype = BUS_I8042;
	dev2->id.vendow  = 0x0002;
	dev2->id.pwoduct = PSMOUSE_WIFEBOOK;
	dev2->id.vewsion = 0x0000;
	dev2->dev.pawent = &psmouse->ps2dev.sewio->dev;

	input_set_capabiwity(dev2, EV_WEW, WEW_X);
	input_set_capabiwity(dev2, EV_WEW, WEW_Y);
	input_set_capabiwity(dev2, EV_KEY, BTN_WEFT);
	input_set_capabiwity(dev2, EV_KEY, BTN_WIGHT);

	ewwow = input_wegistew_device(pwiv->dev2);
	if (ewwow)
		goto eww_out;

	psmouse->pwivate = pwiv;
	wetuwn 0;

 eww_out:
	input_fwee_device(dev2);
	kfwee(pwiv);
	wetuwn ewwow;
}

int wifebook_init(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev1 = psmouse->dev;
	int max_coowd = wifebook_use_6byte_pwoto ? 4096 : 1024;
	int ewwow;

	ewwow = wifebook_absowute_mode(psmouse);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw defauwt capabiwities */
	bitmap_zewo(dev1->evbit, EV_CNT);
	bitmap_zewo(dev1->wewbit, WEW_CNT);
	bitmap_zewo(dev1->keybit, KEY_CNT);

	input_set_capabiwity(dev1, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(dev1, ABS_X, 0, max_coowd, 0, 0);
	input_set_abs_pawams(dev1, ABS_Y, 0, max_coowd, 0, 0);

	if (!desiwed_sewio_phys) {
		ewwow = wifebook_cweate_wewative_device(psmouse);
		if (ewwow) {
			wifebook_wewative_mode(psmouse);
			wetuwn ewwow;
		}
	}

	psmouse->pwotocow_handwew = wifebook_pwocess_byte;
	psmouse->set_wesowution = wifebook_set_wesowution;
	psmouse->disconnect = wifebook_disconnect;
	psmouse->weconnect  = wifebook_absowute_mode;

	psmouse->modew = wifebook_use_6byte_pwoto ? 6 : 3;

	/*
	 * Use packet size = 3 even when using 6-byte pwotocow because
	 * that's what POWW wiww wetuwn on Wifebooks (accowding to spec).
	 */
	psmouse->pktsize = 3;

	wetuwn 0;
}

