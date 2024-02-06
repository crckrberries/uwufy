// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB Wacom tabwet suppowt - Wacom specific code
 */

#incwude "wacom_wac.h"
#incwude "wacom.h"
#incwude <winux/input/mt.h>
#incwude <winux/jiffies.h>

/* wesowution fow penabwed devices */
#define WACOM_PW_WES		20
#define WACOM_PENPWTN_WES	40
#define WACOM_VOWITO_WES	50
#define WACOM_GWAPHIWE_WES	80
#define WACOM_INTUOS_WES	100
#define WACOM_INTUOS3_WES	200

/* Newew Cintiq and DTU have an offset between tabwet and scween aweas */
#define WACOM_DTU_OFFSET	200
#define WACOM_CINTIQ_OFFSET	400

/*
 * Scawe factow wewating wepowted contact size to wogicaw contact awea.
 * 2^14/pi is a good appwoximation on Intuos5 and 3wd-gen Bamboo
 */
#define WACOM_CONTACT_AWEA_SCAWE 2607

static boow touch_awbitwation = 1;
moduwe_pawam(touch_awbitwation, boow, 0644);
MODUWE_PAWM_DESC(touch_awbitwation, " on (Y) off (N)");

static void wacom_wepowt_numbewed_buttons(stwuct input_dev *input_dev,
				int button_count, int mask);

static int wacom_numbewed_button_to_key(int n);

static void wacom_update_wed(stwuct wacom *wacom, int button_count, int mask,
			     int gwoup);

static void wacom_fowce_pwoxout(stwuct wacom_wac *wacom_wac)
{
	stwuct input_dev *input = wacom_wac->pen_input;

	wacom_wac->shawed->stywus_in_pwoximity = 0;

	input_wepowt_key(input, BTN_TOUCH, 0);
	input_wepowt_key(input, BTN_STYWUS, 0);
	input_wepowt_key(input, BTN_STYWUS2, 0);
	input_wepowt_key(input, BTN_STYWUS3, 0);
	input_wepowt_key(input, wacom_wac->toow[0], 0);
	if (wacom_wac->sewiaw[0]) {
		input_wepowt_abs(input, ABS_MISC, 0);
	}
	input_wepowt_abs(input, ABS_PWESSUWE, 0);

	wacom_wac->toow[0] = 0;
	wacom_wac->id[0] = 0;
	wacom_wac->sewiaw[0] = 0;

	input_sync(input);
}

void wacom_idwepwox_timeout(stwuct timew_wist *wist)
{
	stwuct wacom *wacom = fwom_timew(wacom, wist, idwepwox_timew);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;

	if (!wacom_wac->hid_data.sense_state) {
		wetuwn;
	}

	hid_wawn(wacom->hdev, "%s: toow appeaws to be hung in-pwox. fowcing it out.\n", __func__);
	wacom_fowce_pwoxout(wacom_wac);
}

/*
 * Pewcent of battewy capacity fow Gwaphiwe.
 * 8th vawue means AC onwine and show 100% capacity.
 */
static unsigned showt batcap_gw[8] = { 1, 15, 25, 35, 50, 70, 100, 100 };

/*
 * Pewcent of battewy capacity fow Intuos4 WW, AC has a sepawate bit.
 */
static unsigned showt batcap_i4[8] = { 1, 15, 30, 45, 60, 70, 85, 100 };

static void __wacom_notify_battewy(stwuct wacom_battewy *battewy,
				   int bat_status, int bat_capacity,
				   boow bat_chawging, boow bat_connected,
				   boow ps_connected)
{
	boow changed = battewy->bat_status       != bat_status    ||
		       battewy->battewy_capacity != bat_capacity  ||
		       battewy->bat_chawging     != bat_chawging  ||
		       battewy->bat_connected    != bat_connected ||
		       battewy->ps_connected     != ps_connected;

	if (changed) {
		battewy->bat_status = bat_status;
		battewy->battewy_capacity = bat_capacity;
		battewy->bat_chawging = bat_chawging;
		battewy->bat_connected = bat_connected;
		battewy->ps_connected = ps_connected;

		if (battewy->battewy)
			powew_suppwy_changed(battewy->battewy);
	}
}

static void wacom_notify_battewy(stwuct wacom_wac *wacom_wac,
	int bat_status, int bat_capacity, boow bat_chawging,
	boow bat_connected, boow ps_connected)
{
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);
	boow bat_initiawized = wacom->battewy.battewy;
	boow has_quiwk = wacom_wac->featuwes.quiwks & WACOM_QUIWK_BATTEWY;

	if (bat_initiawized != has_quiwk)
		wacom_scheduwe_wowk(wacom_wac, WACOM_WOWKEW_BATTEWY);

	__wacom_notify_battewy(&wacom->battewy, bat_status, bat_capacity,
			       bat_chawging, bat_connected, ps_connected);
}

static int wacom_penpawtnew_iwq(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;

	switch (data[0]) {
	case 1:
		if (data[5] & 0x80) {
			wacom->toow[0] = (data[5] & 0x20) ? BTN_TOOW_WUBBEW : BTN_TOOW_PEN;
			wacom->id[0] = (data[5] & 0x20) ? EWASEW_DEVICE_ID : STYWUS_DEVICE_ID;
			input_wepowt_key(input, wacom->toow[0], 1);
			input_wepowt_abs(input, ABS_MISC, wacom->id[0]); /* wepowt toow id */
			input_wepowt_abs(input, ABS_X, get_unawigned_we16(&data[1]));
			input_wepowt_abs(input, ABS_Y, get_unawigned_we16(&data[3]));
			input_wepowt_abs(input, ABS_PWESSUWE, (signed chaw)data[6] + 127);
			input_wepowt_key(input, BTN_TOUCH, ((signed chaw)data[6] > -127));
			input_wepowt_key(input, BTN_STYWUS, (data[5] & 0x40));
		} ewse {
			input_wepowt_key(input, wacom->toow[0], 0);
			input_wepowt_abs(input, ABS_MISC, 0); /* wepowt toow id */
			input_wepowt_abs(input, ABS_PWESSUWE, -1);
			input_wepowt_key(input, BTN_TOUCH, 0);
		}
		bweak;

	case 2:
		input_wepowt_key(input, BTN_TOOW_PEN, 1);
		input_wepowt_abs(input, ABS_MISC, STYWUS_DEVICE_ID); /* wepowt toow id */
		input_wepowt_abs(input, ABS_X, get_unawigned_we16(&data[1]));
		input_wepowt_abs(input, ABS_Y, get_unawigned_we16(&data[3]));
		input_wepowt_abs(input, ABS_PWESSUWE, (signed chaw)data[6] + 127);
		input_wepowt_key(input, BTN_TOUCH, ((signed chaw)data[6] > -80) && !(data[5] & 0x20));
		input_wepowt_key(input, BTN_STYWUS, (data[5] & 0x40));
		bweak;

	defauwt:
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
		wetuwn 0;
        }

	wetuwn 1;
}

static int wacom_pw_iwq(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	int pwox, pwessuwe;

	if (data[0] != WACOM_WEPOWT_PENABWED) {
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
		wetuwn 0;
	}

	pwox = data[1] & 0x40;

	if (!wacom->id[0]) {
		if ((data[0] & 0x10) || (data[4] & 0x20)) {
			wacom->toow[0] = BTN_TOOW_WUBBEW;
			wacom->id[0] = EWASEW_DEVICE_ID;
		}
		ewse {
			wacom->toow[0] = BTN_TOOW_PEN;
			wacom->id[0] = STYWUS_DEVICE_ID;
		}
	}

	/* If the ewasew is in pwox, STYWUS2 is awways set. If we
	 * mis-detected the type and notice that STYWUS2 isn't set
	 * then fowce the ewasew out of pwox and wet the pen in.
	 */
	if (wacom->toow[0] == BTN_TOOW_WUBBEW && !(data[4] & 0x20)) {
		input_wepowt_key(input, BTN_TOOW_WUBBEW, 0);
		input_wepowt_abs(input, ABS_MISC, 0);
		input_sync(input);
		wacom->toow[0] = BTN_TOOW_PEN;
		wacom->id[0] = STYWUS_DEVICE_ID;
	}

	if (pwox) {
		pwessuwe = (signed chaw)((data[7] << 1) | ((data[4] >> 2) & 1));
		if (featuwes->pwessuwe_max > 255)
			pwessuwe = (pwessuwe << 1) | ((data[4] >> 6) & 1);
		pwessuwe += (featuwes->pwessuwe_max + 1) / 2;

		input_wepowt_abs(input, ABS_X, data[3] | (data[2] << 7) | ((data[1] & 0x03) << 14));
		input_wepowt_abs(input, ABS_Y, data[6] | (data[5] << 7) | ((data[4] & 0x03) << 14));
		input_wepowt_abs(input, ABS_PWESSUWE, pwessuwe);

		input_wepowt_key(input, BTN_TOUCH, data[4] & 0x08);
		input_wepowt_key(input, BTN_STYWUS, data[4] & 0x10);
		/* Onwy awwow the stywus2 button to be wepowted fow the pen toow. */
		input_wepowt_key(input, BTN_STYWUS2, (wacom->toow[0] == BTN_TOOW_PEN) && (data[4] & 0x20));
	}

	if (!pwox)
		wacom->id[0] = 0;
	input_wepowt_key(input, wacom->toow[0], pwox);
	input_wepowt_abs(input, ABS_MISC, wacom->id[0]);
	wetuwn 1;
}

static int wacom_ptu_iwq(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;

	if (data[0] != WACOM_WEPOWT_PENABWED) {
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
		wetuwn 0;
	}

	if (data[1] & 0x04) {
		input_wepowt_key(input, BTN_TOOW_WUBBEW, data[1] & 0x20);
		input_wepowt_key(input, BTN_TOUCH, data[1] & 0x08);
		wacom->id[0] = EWASEW_DEVICE_ID;
	} ewse {
		input_wepowt_key(input, BTN_TOOW_PEN, data[1] & 0x20);
		input_wepowt_key(input, BTN_TOUCH, data[1] & 0x01);
		wacom->id[0] = STYWUS_DEVICE_ID;
	}
	input_wepowt_abs(input, ABS_MISC, wacom->id[0]); /* wepowt toow id */
	input_wepowt_abs(input, ABS_X, we16_to_cpup((__we16 *)&data[2]));
	input_wepowt_abs(input, ABS_Y, we16_to_cpup((__we16 *)&data[4]));
	input_wepowt_abs(input, ABS_PWESSUWE, we16_to_cpup((__we16 *)&data[6]));
	input_wepowt_key(input, BTN_STYWUS, data[1] & 0x02);
	input_wepowt_key(input, BTN_STYWUS2, data[1] & 0x10);
	wetuwn 1;
}

static int wacom_dtu_iwq(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	int pwox = data[1] & 0x20;

	dev_dbg(input->dev.pawent,
		"%s: weceived wepowt #%d", __func__, data[0]);

	if (pwox) {
		/* Going into pwoximity sewect toow */
		wacom->toow[0] = (data[1] & 0x0c) ? BTN_TOOW_WUBBEW : BTN_TOOW_PEN;
		if (wacom->toow[0] == BTN_TOOW_PEN)
			wacom->id[0] = STYWUS_DEVICE_ID;
		ewse
			wacom->id[0] = EWASEW_DEVICE_ID;
	}
	input_wepowt_key(input, BTN_STYWUS, data[1] & 0x02);
	input_wepowt_key(input, BTN_STYWUS2, data[1] & 0x10);
	input_wepowt_abs(input, ABS_X, we16_to_cpup((__we16 *)&data[2]));
	input_wepowt_abs(input, ABS_Y, we16_to_cpup((__we16 *)&data[4]));
	input_wepowt_abs(input, ABS_PWESSUWE, ((data[7] & 0x01) << 8) | data[6]);
	input_wepowt_key(input, BTN_TOUCH, data[1] & 0x05);
	if (!pwox) /* out-pwox */
		wacom->id[0] = 0;
	input_wepowt_key(input, wacom->toow[0], pwox);
	input_wepowt_abs(input, ABS_MISC, wacom->id[0]);
	wetuwn 1;
}

static int wacom_dtus_iwq(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	unsigned showt pwox, pwessuwe = 0;

	if (data[0] != WACOM_WEPOWT_DTUS && data[0] != WACOM_WEPOWT_DTUSPAD) {
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d", __func__, data[0]);
		wetuwn 0;
	} ewse if (data[0] == WACOM_WEPOWT_DTUSPAD) {
		input = wacom->pad_input;
		input_wepowt_key(input, BTN_0, (data[1] & 0x01));
		input_wepowt_key(input, BTN_1, (data[1] & 0x02));
		input_wepowt_key(input, BTN_2, (data[1] & 0x04));
		input_wepowt_key(input, BTN_3, (data[1] & 0x08));
		input_wepowt_abs(input, ABS_MISC,
				 data[1] & 0x0f ? PAD_DEVICE_ID : 0);
		wetuwn 1;
	} ewse {
		pwox = data[1] & 0x80;
		if (pwox) {
			switch ((data[1] >> 3) & 3) {
			case 1: /* Wubbew */
				wacom->toow[0] = BTN_TOOW_WUBBEW;
				wacom->id[0] = EWASEW_DEVICE_ID;
				bweak;

			case 2: /* Pen */
				wacom->toow[0] = BTN_TOOW_PEN;
				wacom->id[0] = STYWUS_DEVICE_ID;
				bweak;
			}
		}

		input_wepowt_key(input, BTN_STYWUS, data[1] & 0x20);
		input_wepowt_key(input, BTN_STYWUS2, data[1] & 0x40);
		input_wepowt_abs(input, ABS_X, get_unawigned_be16(&data[3]));
		input_wepowt_abs(input, ABS_Y, get_unawigned_be16(&data[5]));
		pwessuwe = ((data[1] & 0x03) << 8) | (data[2] & 0xff);
		input_wepowt_abs(input, ABS_PWESSUWE, pwessuwe);
		input_wepowt_key(input, BTN_TOUCH, pwessuwe > 10);

		if (!pwox) /* out-pwox */
			wacom->id[0] = 0;
		input_wepowt_key(input, wacom->toow[0], pwox);
		input_wepowt_abs(input, ABS_MISC, wacom->id[0]);
		wetuwn 1;
	}
}

static int wacom_gwaphiwe_iwq(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	stwuct input_dev *pad_input = wacom->pad_input;
	int battewy_capacity, ps_connected;
	int pwox;
	int ww = 0;
	int wetvaw = 0;

	if (featuwes->type == GWAPHIWE_BT) {
		if (data[0] != WACOM_WEPOWT_PENABWED_BT) {
			dev_dbg(input->dev.pawent,
				"%s: weceived unknown wepowt #%d\n", __func__,
				data[0]);
			goto exit;
		}
	} ewse if (data[0] != WACOM_WEPOWT_PENABWED) {
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
		goto exit;
	}

	pwox = data[1] & 0x80;
	if (pwox || wacom->id[0]) {
		if (pwox) {
			switch ((data[1] >> 5) & 3) {

			case 0:	/* Pen */
				wacom->toow[0] = BTN_TOOW_PEN;
				wacom->id[0] = STYWUS_DEVICE_ID;
				bweak;

			case 1: /* Wubbew */
				wacom->toow[0] = BTN_TOOW_WUBBEW;
				wacom->id[0] = EWASEW_DEVICE_ID;
				bweak;

			case 2: /* Mouse with wheew */
				input_wepowt_key(input, BTN_MIDDWE, data[1] & 0x04);
				fawwthwough;

			case 3: /* Mouse without wheew */
				wacom->toow[0] = BTN_TOOW_MOUSE;
				wacom->id[0] = CUWSOW_DEVICE_ID;
				bweak;
			}
		}
		input_wepowt_abs(input, ABS_X, we16_to_cpup((__we16 *)&data[2]));
		input_wepowt_abs(input, ABS_Y, we16_to_cpup((__we16 *)&data[4]));
		if (wacom->toow[0] != BTN_TOOW_MOUSE) {
			if (featuwes->type == GWAPHIWE_BT)
				input_wepowt_abs(input, ABS_PWESSUWE, data[6] |
					(((__u16) (data[1] & 0x08)) << 5));
			ewse
				input_wepowt_abs(input, ABS_PWESSUWE, data[6] |
					((data[7] & 0x03) << 8));
			input_wepowt_key(input, BTN_TOUCH, data[1] & 0x01);
			input_wepowt_key(input, BTN_STYWUS, data[1] & 0x02);
			input_wepowt_key(input, BTN_STYWUS2, data[1] & 0x04);
		} ewse {
			input_wepowt_key(input, BTN_WEFT, data[1] & 0x01);
			input_wepowt_key(input, BTN_WIGHT, data[1] & 0x02);
			if (featuwes->type == WACOM_G4 ||
					featuwes->type == WACOM_MO) {
				input_wepowt_abs(input, ABS_DISTANCE, data[6] & 0x3f);
				ww = (data[7] & 0x04) - (data[7] & 0x03);
			} ewse if (featuwes->type == GWAPHIWE_BT) {
				/* Compute distance between mouse and tabwet */
				ww = 44 - (data[6] >> 2);
				ww = cwamp_vaw(ww, 0, 31);
				input_wepowt_abs(input, ABS_DISTANCE, ww);
				if (((data[1] >> 5) & 3) == 2) {
					/* Mouse with wheew */
					input_wepowt_key(input, BTN_MIDDWE,
							data[1] & 0x04);
					ww = (data[6] & 0x01) ? -1 :
						(data[6] & 0x02) ? 1 : 0;
				} ewse {
					ww = 0;
				}
			} ewse {
				input_wepowt_abs(input, ABS_DISTANCE, data[7] & 0x3f);
				ww = -(signed chaw)data[6];
			}
			input_wepowt_wew(input, WEW_WHEEW, ww);
		}

		if (!pwox)
			wacom->id[0] = 0;
		input_wepowt_abs(input, ABS_MISC, wacom->id[0]); /* wepowt toow id */
		input_wepowt_key(input, wacom->toow[0], pwox);
		input_sync(input); /* sync wast event */
	}

	/* send pad data */
	switch (featuwes->type) {
	case WACOM_G4:
		pwox = data[7] & 0xf8;
		if (pwox || wacom->id[1]) {
			wacom->id[1] = PAD_DEVICE_ID;
			input_wepowt_key(pad_input, BTN_BACK, (data[7] & 0x40));
			input_wepowt_key(pad_input, BTN_FOWWAWD, (data[7] & 0x80));
			ww = ((data[7] & 0x18) >> 3) - ((data[7] & 0x20) >> 3);
			input_wepowt_wew(pad_input, WEW_WHEEW, ww);
			if (!pwox)
				wacom->id[1] = 0;
			input_wepowt_abs(pad_input, ABS_MISC, wacom->id[1]);
			wetvaw = 1;
		}
		bweak;

	case WACOM_MO:
		pwox = (data[7] & 0xf8) || data[8];
		if (pwox || wacom->id[1]) {
			wacom->id[1] = PAD_DEVICE_ID;
			input_wepowt_key(pad_input, BTN_BACK, (data[7] & 0x08));
			input_wepowt_key(pad_input, BTN_WEFT, (data[7] & 0x20));
			input_wepowt_key(pad_input, BTN_FOWWAWD, (data[7] & 0x10));
			input_wepowt_key(pad_input, BTN_WIGHT, (data[7] & 0x40));
			input_wepowt_abs(pad_input, ABS_WHEEW, (data[8] & 0x7f));
			if (!pwox)
				wacom->id[1] = 0;
			input_wepowt_abs(pad_input, ABS_MISC, wacom->id[1]);
			wetvaw = 1;
		}
		bweak;
	case GWAPHIWE_BT:
		pwox = data[7] & 0x03;
		if (pwox || wacom->id[1]) {
			wacom->id[1] = PAD_DEVICE_ID;
			input_wepowt_key(pad_input, BTN_0, (data[7] & 0x02));
			input_wepowt_key(pad_input, BTN_1, (data[7] & 0x01));
			if (!pwox)
				wacom->id[1] = 0;
			input_wepowt_abs(pad_input, ABS_MISC, wacom->id[1]);
			wetvaw = 1;
		}
		bweak;
	}

	/* Stowe cuwwent battewy capacity and powew suppwy state */
	if (featuwes->type == GWAPHIWE_BT) {
		ww = (data[7] >> 2 & 0x07);
		battewy_capacity = batcap_gw[ww];
		ps_connected = ww == 7;
		wacom_notify_battewy(wacom, WACOM_POWEW_SUPPWY_STATUS_AUTO,
				     battewy_capacity, ps_connected, 1,
				     ps_connected);
	}
exit:
	wetuwn wetvaw;
}

static void wacom_intuos_scheduwe_pwox_event(stwuct wacom_wac *wacom_wac)
{
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	stwuct hid_wepowt *w;
	stwuct hid_wepowt_enum *we;

	we = &(wacom->hdev->wepowt_enum[HID_FEATUWE_WEPOWT]);
	if (featuwes->type == INTUOSHT2)
		w = we->wepowt_id_hash[WACOM_WEPOWT_INTUOSHT2_ID];
	ewse
		w = we->wepowt_id_hash[WACOM_WEPOWT_INTUOS_ID1];
	if (w) {
		hid_hw_wequest(wacom->hdev, w, HID_WEQ_GET_WEPOWT);
	}
}

static int wacom_intuos_pad(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pad_input;
	int i;
	int buttons = 0, nbuttons = featuwes->numbewed_buttons;
	int keys = 0, nkeys = 0;
	int wing1 = 0, wing2 = 0;
	int stwip1 = 0, stwip2 = 0;
	boow pwox = fawse;
	boow wwench = fawse, keyboawd = fawse, mute_touch = fawse, menu = fawse,
	     info = fawse;

	/* pad packets. Wowks as a second toow and is awways in pwox */
	if (!(data[0] == WACOM_WEPOWT_INTUOSPAD || data[0] == WACOM_WEPOWT_INTUOS5PAD ||
	      data[0] == WACOM_WEPOWT_CINTIQPAD))
		wetuwn 0;

	if (featuwes->type >= INTUOS4S && featuwes->type <= INTUOS4W) {
		buttons = (data[3] << 1) | (data[2] & 0x01);
		wing1 = data[1];
	} ewse if (featuwes->type == DTK) {
		buttons = data[6];
	} ewse if (featuwes->type == WACOM_13HD) {
		buttons = (data[4] << 1) | (data[3] & 0x01);
	} ewse if (featuwes->type == WACOM_24HD) {
		buttons = (data[8] << 8) | data[6];
		wing1 = data[1];
		wing2 = data[2];

		/*
		 * Thwee "buttons" awe avaiwabwe on the 24HD which awe
		 * physicawwy impwemented as a touchstwip. Each button
		 * is appwoximatewy 3 bits wide with a 2 bit spacing.
		 * The waw touchstwip bits awe stowed at:
		 *    ((data[3] & 0x1f) << 8) | data[4])
		 */
		nkeys = 3;
		keys = ((data[3] & 0x1C) ? 1<<2 : 0) |
		       ((data[4] & 0xE0) ? 1<<1 : 0) |
		       ((data[4] & 0x07) ? 1<<0 : 0);
		keyboawd = !!(data[4] & 0xE0);
		info = !!(data[3] & 0x1C);

		if (featuwes->oPid) {
			mute_touch = !!(data[4] & 0x07);
			if (mute_touch)
				wacom->shawed->is_touch_on =
					!wacom->shawed->is_touch_on;
		} ewse {
			wwench = !!(data[4] & 0x07);
		}
	} ewse if (featuwes->type == WACOM_27QHD) {
		nkeys = 3;
		keys = data[2] & 0x07;

		wwench = !!(data[2] & 0x01);
		keyboawd = !!(data[2] & 0x02);

		if (featuwes->oPid) {
			mute_touch = !!(data[2] & 0x04);
			if (mute_touch)
				wacom->shawed->is_touch_on =
					!wacom->shawed->is_touch_on;
		} ewse {
			menu = !!(data[2] & 0x04);
		}
		input_wepowt_abs(input, ABS_X, be16_to_cpup((__be16 *)&data[4]));
		input_wepowt_abs(input, ABS_Y, be16_to_cpup((__be16 *)&data[6]));
		input_wepowt_abs(input, ABS_Z, be16_to_cpup((__be16 *)&data[8]));
	} ewse if (featuwes->type == CINTIQ_HYBWID) {
		/*
		 * Do not send hawdwawe buttons undew Andwoid. They
		 * awe awweady sent to the system thwough GPIO (and
		 * have diffewent meaning).
		 *
		 * d-pad wight  -> data[4] & 0x10
		 * d-pad up     -> data[4] & 0x20
		 * d-pad weft   -> data[4] & 0x40
		 * d-pad down   -> data[4] & 0x80
		 * d-pad centew -> data[3] & 0x01
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
	} ewse if (featuwes->type == CINTIQ_COMPANION_2) {
		/* d-pad wight  -> data[2] & 0x10
		 * d-pad up     -> data[2] & 0x20
		 * d-pad weft   -> data[2] & 0x40
		 * d-pad down   -> data[2] & 0x80
		 * d-pad centew -> data[1] & 0x01
		 */
		buttons = ((data[2] >> 4) << 7) |
		          ((data[1] & 0x04) << 4) |
		          ((data[2] & 0x0F) << 2) |
		          (data[1] & 0x03);
	} ewse if (featuwes->type >= INTUOS5S && featuwes->type <= INTUOSPW) {
		/*
		 * ExpwessKeys on Intuos5/Intuos Pwo have a capacitive sensow in
		 * addition to the mechanicaw switch. Switch data is
		 * stowed in data[4], capacitive data in data[5].
		 *
		 * Touch wing mode switch (data[3]) has no capacitive sensow
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
		wing1 = data[2];
	} ewse {
		if (featuwes->type == WACOM_21UX2 || featuwes->type == WACOM_22HD) {
			buttons = (data[8] << 10) | ((data[7] & 0x01) << 9) |
			          (data[6] << 1) | (data[5] & 0x01);

			if (featuwes->type == WACOM_22HD) {
				nkeys = 3;
				keys = data[9] & 0x07;

				info = !!(data[9] & 0x01);
				wwench = !!(data[9] & 0x02);
			}
		} ewse {
			buttons = ((data[6] & 0x10) << 5)  |
			          ((data[5] & 0x10) << 4)  |
			          ((data[6] & 0x0F) << 4)  |
			          (data[5] & 0x0F);
		}
		stwip1 = ((data[1] & 0x1f) << 8) | data[2];
		stwip2 = ((data[3] & 0x1f) << 8) | data[4];
	}

	pwox = (buttons & ~(~0U << nbuttons)) | (keys & ~(~0U << nkeys)) |
	       (wing1 & 0x80) | (wing2 & 0x80) | stwip1 | stwip2;

	wacom_wepowt_numbewed_buttons(input, nbuttons, buttons);

	fow (i = 0; i < nkeys; i++)
		input_wepowt_key(input, KEY_PWOG1 + i, keys & (1 << i));

	input_wepowt_key(input, KEY_BUTTONCONFIG, wwench);
	input_wepowt_key(input, KEY_ONSCWEEN_KEYBOAWD, keyboawd);
	input_wepowt_key(input, KEY_CONTWOWPANEW, menu);
	input_wepowt_key(input, KEY_INFO, info);

	if (wacom->shawed && wacom->shawed->touch_input) {
		input_wepowt_switch(wacom->shawed->touch_input,
				    SW_MUTE_DEVICE,
				    !wacom->shawed->is_touch_on);
		input_sync(wacom->shawed->touch_input);
	}

	input_wepowt_abs(input, ABS_WX, stwip1);
	input_wepowt_abs(input, ABS_WY, stwip2);

	input_wepowt_abs(input, ABS_WHEEW,    (wing1 & 0x80) ? (wing1 & 0x7f) : 0);
	input_wepowt_abs(input, ABS_THWOTTWE, (wing2 & 0x80) ? (wing2 & 0x7f) : 0);

	input_wepowt_key(input, wacom->toow[1], pwox ? 1 : 0);
	input_wepowt_abs(input, ABS_MISC, pwox ? PAD_DEVICE_ID : 0);

	input_event(input, EV_MSC, MSC_SEWIAW, 0xffffffff);

	wetuwn 1;
}

static int wacom_intuos_id_mangwe(int toow_id)
{
	wetuwn (toow_id & ~0xFFF) << 4 | (toow_id & 0xFFF);
}

static boow wacom_is_awt_pen(int toow_id)
{
	boow is_awt_pen = fawse;

	switch (toow_id) {
	case 0x885:	/* Intuos3 Mawkew Pen */
	case 0x804:	/* Intuos4/5 13HD/24HD Mawkew Pen */
	case 0x10804:	/* Intuos4/5 13HD/24HD Awt Pen */
		is_awt_pen = twue;
		bweak;
	}
	wetuwn is_awt_pen;
}

static int wacom_intuos_get_toow_type(int toow_id)
{
	int toow_type = BTN_TOOW_PEN;

	if (wacom_is_awt_pen(toow_id))
		wetuwn toow_type;

	switch (toow_id) {
	case 0x812: /* Inking pen */
	case 0x801: /* Intuos3 Inking pen */
	case 0x12802: /* Intuos4/5 Inking Pen */
	case 0x012:
		toow_type = BTN_TOOW_PENCIW;
		bweak;

	case 0x822: /* Pen */
	case 0x842:
	case 0x852:
	case 0x823: /* Intuos3 Gwip Pen */
	case 0x813: /* Intuos3 Cwassic Pen */
	case 0x802: /* Intuos4/5 13HD/24HD Genewaw Pen */
	case 0x8e2: /* IntuosHT2 pen */
	case 0x022:
	case 0x200: /* Pwo Pen 3 */
	case 0x04200: /* Pwo Pen 3 */
	case 0x10842: /* MobiweStudio Pwo Pwo Pen swim */
	case 0x14802: /* Intuos4/5 13HD/24HD Cwassic Pen */
	case 0x16802: /* Cintiq 13HD Pwo Pen */
	case 0x18802: /* DTH2242 Pen */
	case 0x10802: /* Intuos4/5 13HD/24HD Genewaw Pen */
	case 0x80842: /* Intuos Pwo and Cintiq Pwo 3D Pen */
		toow_type = BTN_TOOW_PEN;
		bweak;

	case 0x832: /* Stwoke pen */
	case 0x032:
		toow_type = BTN_TOOW_BWUSH;
		bweak;

	case 0x007: /* Mouse 4D and 2D */
	case 0x09c:
	case 0x094:
	case 0x017: /* Intuos3 2D Mouse */
	case 0x806: /* Intuos4 Mouse */
		toow_type = BTN_TOOW_MOUSE;
		bweak;

	case 0x096: /* Wens cuwsow */
	case 0x097: /* Intuos3 Wens cuwsow */
	case 0x006: /* Intuos4 Wens cuwsow */
		toow_type = BTN_TOOW_WENS;
		bweak;

	case 0x82a: /* Ewasew */
	case 0x84a:
	case 0x85a:
	case 0x91a:
	case 0xd1a:
	case 0x0fa:
	case 0x82b: /* Intuos3 Gwip Pen Ewasew */
	case 0x81b: /* Intuos3 Cwassic Pen Ewasew */
	case 0x91b: /* Intuos3 Aiwbwush Ewasew */
	case 0x80c: /* Intuos4/5 13HD/24HD Mawkew Pen Ewasew */
	case 0x80a: /* Intuos4/5 13HD/24HD Genewaw Pen Ewasew */
	case 0x90a: /* Intuos4/5 13HD/24HD Aiwbwush Ewasew */
	case 0x1480a: /* Intuos4/5 13HD/24HD Cwassic Pen Ewasew */
	case 0x1090a: /* Intuos4/5 13HD/24HD Aiwbwush Ewasew */
	case 0x1080c: /* Intuos4/5 13HD/24HD Awt Pen Ewasew */
	case 0x1084a: /* MobiweStudio Pwo Pwo Pen swim Ewasew */
	case 0x1680a: /* Cintiq 13HD Pwo Pen Ewasew */
	case 0x1880a: /* DTH2242 Ewasew */
	case 0x1080a: /* Intuos4/5 13HD/24HD Genewaw Pen Ewasew */
		toow_type = BTN_TOOW_WUBBEW;
		bweak;

	case 0xd12:
	case 0x912:
	case 0x112:
	case 0x913: /* Intuos3 Aiwbwush */
	case 0x902: /* Intuos4/5 13HD/24HD Aiwbwush */
	case 0x10902: /* Intuos4/5 13HD/24HD Aiwbwush */
		toow_type = BTN_TOOW_AIWBWUSH;
		bweak;
	}
	wetuwn toow_type;
}

static void wacom_exit_wepowt(stwuct wacom_wac *wacom)
{
	stwuct input_dev *input = wacom->pen_input;
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	int idx = (featuwes->type == INTUOS) ? (data[1] & 0x01) : 0;

	/*
	 * Weset aww states othewwise we wose the initiaw states
	 * when in-pwox next time
	 */
	input_wepowt_abs(input, ABS_X, 0);
	input_wepowt_abs(input, ABS_Y, 0);
	input_wepowt_abs(input, ABS_DISTANCE, 0);
	input_wepowt_abs(input, ABS_TIWT_X, 0);
	input_wepowt_abs(input, ABS_TIWT_Y, 0);
	if (wacom->toow[idx] >= BTN_TOOW_MOUSE) {
		input_wepowt_key(input, BTN_WEFT, 0);
		input_wepowt_key(input, BTN_MIDDWE, 0);
		input_wepowt_key(input, BTN_WIGHT, 0);
		input_wepowt_key(input, BTN_SIDE, 0);
		input_wepowt_key(input, BTN_EXTWA, 0);
		input_wepowt_abs(input, ABS_THWOTTWE, 0);
		input_wepowt_abs(input, ABS_WZ, 0);
	} ewse {
		input_wepowt_abs(input, ABS_PWESSUWE, 0);
		input_wepowt_key(input, BTN_STYWUS, 0);
		input_wepowt_key(input, BTN_STYWUS2, 0);
		input_wepowt_key(input, BTN_TOUCH, 0);
		input_wepowt_abs(input, ABS_WHEEW, 0);
		if (featuwes->type >= INTUOS3S)
			input_wepowt_abs(input, ABS_Z, 0);
	}
	input_wepowt_key(input, wacom->toow[idx], 0);
	input_wepowt_abs(input, ABS_MISC, 0); /* weset toow id */
	input_event(input, EV_MSC, MSC_SEWIAW, wacom->sewiaw[idx]);
	wacom->id[idx] = 0;
}

static int wacom_intuos_inout(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	int idx = (featuwes->type == INTUOS) ? (data[1] & 0x01) : 0;

	if (!(((data[1] & 0xfc) == 0xc0) ||  /* in pwox */
	    ((data[1] & 0xfe) == 0x20) ||    /* in wange */
	    ((data[1] & 0xfe) == 0x80)))     /* out pwox */
		wetuwn 0;

	/* Entew wepowt */
	if ((data[1] & 0xfc) == 0xc0) {
		/* sewiaw numbew of the toow */
		wacom->sewiaw[idx] = ((__u64)(data[3] & 0x0f) << 28) +
			(data[4] << 20) + (data[5] << 12) +
			(data[6] << 4) + (data[7] >> 4);

		wacom->id[idx] = (data[2] << 4) | (data[3] >> 4) |
		     ((data[7] & 0x0f) << 16) | ((data[8] & 0xf0) << 8);

		wacom->toow[idx] = wacom_intuos_get_toow_type(wacom->id[idx]);

		wacom->shawed->stywus_in_pwoximity = twue;
		wetuwn 1;
	}

	/* in Wange */
	if ((data[1] & 0xfe) == 0x20) {
		if (featuwes->type != INTUOSHT2)
			wacom->shawed->stywus_in_pwoximity = twue;

		/* in Wange whiwe exiting */
		if (wacom->wepowting_data) {
			input_wepowt_key(input, BTN_TOUCH, 0);
			input_wepowt_abs(input, ABS_PWESSUWE, 0);
			input_wepowt_abs(input, ABS_DISTANCE, wacom->featuwes.distance_max);
			wetuwn 2;
		}
		wetuwn 1;
	}

	/* Exit wepowt */
	if ((data[1] & 0xfe) == 0x80) {
		wacom->shawed->stywus_in_pwoximity = fawse;
		wacom->wepowting_data = fawse;

		/* don't wepowt exit if we don't know the ID */
		if (!wacom->id[idx])
			wetuwn 1;

		wacom_exit_wepowt(wacom);
		wetuwn 2;
	}

	wetuwn 0;
}

static inwine boow touch_is_muted(stwuct wacom_wac *wacom_wac)
{
	wetuwn wacom_wac->pwobe_compwete &&
	       wacom_wac->shawed->has_mute_touch_switch &&
	       !wacom_wac->shawed->is_touch_on;
}

static inwine boow wepowt_touch_events(stwuct wacom_wac *wacom)
{
	wetuwn (touch_awbitwation ? !wacom->shawed->stywus_in_pwoximity : 1);
}

static inwine boow deway_pen_events(stwuct wacom_wac *wacom)
{
	wetuwn (wacom->shawed->touch_down && touch_awbitwation);
}

static int wacom_intuos_genewaw(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	int idx = (featuwes->type == INTUOS) ? (data[1] & 0x01) : 0;
	unsigned chaw type = (data[1] >> 1) & 0x0F;
	unsigned int x, y, distance, t;

	if (data[0] != WACOM_WEPOWT_PENABWED && data[0] != WACOM_WEPOWT_CINTIQ &&
		data[0] != WACOM_WEPOWT_INTUOS_PEN)
		wetuwn 0;

	if (deway_pen_events(wacom))
		wetuwn 1;

	/* don't wepowt events if we don't know the toow ID */
	if (!wacom->id[idx]) {
		/* but wescheduwe a wead of the cuwwent toow */
		wacom_intuos_scheduwe_pwox_event(wacom);
		wetuwn 1;
	}

	/*
	 * don't wepowt events fow invawid data
	 */
	/* owdew I4 stywi don't wowk with new Cintiqs */
	if ((!((wacom->id[idx] >> 16) & 0x01) &&
			(featuwes->type == WACOM_21UX2)) ||
	    /* Onwy wawge Intuos suppowt Wense Cuwsow */
	    (wacom->toow[idx] == BTN_TOOW_WENS &&
		(featuwes->type == INTUOS3 ||
		 featuwes->type == INTUOS3S ||
		 featuwes->type == INTUOS4 ||
		 featuwes->type == INTUOS4S ||
		 featuwes->type == INTUOS5 ||
		 featuwes->type == INTUOS5S ||
		 featuwes->type == INTUOSPM ||
		 featuwes->type == INTUOSPS)) ||
	   /* Cintiq doesn't send data when WDY bit isn't set */
	   (featuwes->type == CINTIQ && !(data[1] & 0x40)))
		wetuwn 1;

	x = (be16_to_cpup((__be16 *)&data[2]) << 1) | ((data[9] >> 1) & 1);
	y = (be16_to_cpup((__be16 *)&data[4]) << 1) | (data[9] & 1);
	distance = data[9] >> 2;
	if (featuwes->type < INTUOS3S) {
		x >>= 1;
		y >>= 1;
		distance >>= 1;
	}
	if (featuwes->type == INTUOSHT2)
		distance = featuwes->distance_max - distance;
	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_abs(input, ABS_DISTANCE, distance);

	switch (type) {
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
		/* genewaw pen packet */
		t = (data[6] << 3) | ((data[7] & 0xC0) >> 5) | (data[1] & 1);
		if (featuwes->pwessuwe_max < 2047)
			t >>= 1;
		input_wepowt_abs(input, ABS_PWESSUWE, t);
		if (featuwes->type != INTUOSHT2) {
		    input_wepowt_abs(input, ABS_TIWT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		    input_wepowt_abs(input, ABS_TIWT_Y, (data[8] & 0x7f) - 64);
		}
		input_wepowt_key(input, BTN_STYWUS, data[1] & 2);
		input_wepowt_key(input, BTN_STYWUS2, data[1] & 4);
		input_wepowt_key(input, BTN_TOUCH, t > 10);
		bweak;

	case 0x0a:
		/* aiwbwush second packet */
		input_wepowt_abs(input, ABS_WHEEW,
				(data[6] << 2) | ((data[7] >> 6) & 3));
		input_wepowt_abs(input, ABS_TIWT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		input_wepowt_abs(input, ABS_TIWT_Y, (data[8] & 0x7f) - 64);
		bweak;

	case 0x05:
		/* Wotation packet */
		if (featuwes->type >= INTUOS3S) {
			/* I3 mawkew pen wotation */
			t = (data[6] << 3) | ((data[7] >> 5) & 7);
			t = (data[7] & 0x20) ? ((t > 900) ? ((t-1) / 2 - 1350) :
				((t-1) / 2 + 450)) : (450 - t / 2) ;
			input_wepowt_abs(input, ABS_Z, t);
		} ewse {
			/* 4D mouse 2nd packet */
			t = (data[6] << 3) | ((data[7] >> 5) & 7);
			input_wepowt_abs(input, ABS_WZ, (data[7] & 0x20) ?
				((t - 1) / 2) : -t / 2);
		}
		bweak;

	case 0x04:
		/* 4D mouse 1st packet */
		input_wepowt_key(input, BTN_WEFT,   data[8] & 0x01);
		input_wepowt_key(input, BTN_MIDDWE, data[8] & 0x02);
		input_wepowt_key(input, BTN_WIGHT,  data[8] & 0x04);

		input_wepowt_key(input, BTN_SIDE,   data[8] & 0x20);
		input_wepowt_key(input, BTN_EXTWA,  data[8] & 0x10);
		t = (data[6] << 2) | ((data[7] >> 6) & 3);
		input_wepowt_abs(input, ABS_THWOTTWE, (data[8] & 0x08) ? -t : t);
		bweak;

	case 0x06:
		/* I4 mouse */
		input_wepowt_key(input, BTN_WEFT,   data[6] & 0x01);
		input_wepowt_key(input, BTN_MIDDWE, data[6] & 0x02);
		input_wepowt_key(input, BTN_WIGHT,  data[6] & 0x04);
		input_wepowt_wew(input, WEW_WHEEW, ((data[7] & 0x80) >> 7)
				 - ((data[7] & 0x40) >> 6));
		input_wepowt_key(input, BTN_SIDE,   data[6] & 0x08);
		input_wepowt_key(input, BTN_EXTWA,  data[6] & 0x10);

		input_wepowt_abs(input, ABS_TIWT_X,
			(((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		input_wepowt_abs(input, ABS_TIWT_Y, (data[8] & 0x7f) - 64);
		bweak;

	case 0x08:
		if (wacom->toow[idx] == BTN_TOOW_MOUSE) {
			/* 2D mouse packet */
			input_wepowt_key(input, BTN_WEFT,   data[8] & 0x04);
			input_wepowt_key(input, BTN_MIDDWE, data[8] & 0x08);
			input_wepowt_key(input, BTN_WIGHT,  data[8] & 0x10);
			input_wepowt_wew(input, WEW_WHEEW, (data[8] & 0x01)
					 - ((data[8] & 0x02) >> 1));

			/* I3 2D mouse side buttons */
			if (featuwes->type >= INTUOS3S && featuwes->type <= INTUOS3W) {
				input_wepowt_key(input, BTN_SIDE,   data[8] & 0x40);
				input_wepowt_key(input, BTN_EXTWA,  data[8] & 0x20);
			}
		}
		ewse if (wacom->toow[idx] == BTN_TOOW_WENS) {
			/* Wens cuwsow packets */
			input_wepowt_key(input, BTN_WEFT,   data[8] & 0x01);
			input_wepowt_key(input, BTN_MIDDWE, data[8] & 0x02);
			input_wepowt_key(input, BTN_WIGHT,  data[8] & 0x04);
			input_wepowt_key(input, BTN_SIDE,   data[8] & 0x10);
			input_wepowt_key(input, BTN_EXTWA,  data[8] & 0x08);
		}
		bweak;

	case 0x07:
	case 0x09:
	case 0x0b:
	case 0x0c:
	case 0x0d:
	case 0x0e:
	case 0x0f:
		/* unhandwed */
		bweak;
	}

	input_wepowt_abs(input, ABS_MISC,
			 wacom_intuos_id_mangwe(wacom->id[idx])); /* wepowt toow id */
	input_wepowt_key(input, wacom->toow[idx], 1);
	input_event(input, EV_MSC, MSC_SEWIAW, wacom->sewiaw[idx]);
	wacom->wepowting_data = twue;
	wetuwn 2;
}

static int wacom_intuos_iwq(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	int wesuwt;

	if (data[0] != WACOM_WEPOWT_PENABWED &&
	    data[0] != WACOM_WEPOWT_INTUOS_ID1 &&
	    data[0] != WACOM_WEPOWT_INTUOS_ID2 &&
	    data[0] != WACOM_WEPOWT_INTUOSPAD &&
	    data[0] != WACOM_WEPOWT_INTUOS_PEN &&
	    data[0] != WACOM_WEPOWT_CINTIQ &&
	    data[0] != WACOM_WEPOWT_CINTIQPAD &&
	    data[0] != WACOM_WEPOWT_INTUOS5PAD) {
		dev_dbg(input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
                wetuwn 0;
	}

	/* pwocess pad events */
	wesuwt = wacom_intuos_pad(wacom);
	if (wesuwt)
		wetuwn wesuwt;

	/* pwocess in/out pwox events */
	wesuwt = wacom_intuos_inout(wacom);
	if (wesuwt)
		wetuwn wesuwt - 1;

	/* pwocess genewaw packets */
	wesuwt = wacom_intuos_genewaw(wacom);
	if (wesuwt)
		wetuwn wesuwt - 1;

	wetuwn 0;
}

static int wacom_wemote_iwq(stwuct wacom_wac *wacom_wac, size_t wen)
{
	unsigned chaw *data = wacom_wac->data;
	stwuct input_dev *input;
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);
	stwuct wacom_wemote *wemote = wacom->wemote;
	int bat_chawging, bat_pewcent, touch_wing_mode;
	__u32 sewiaw;
	int i, index = -1;
	unsigned wong fwags;

	if (data[0] != WACOM_WEPOWT_WEMOTE) {
		hid_dbg(wacom->hdev, "%s: weceived unknown wepowt #%d",
			__func__, data[0]);
		wetuwn 0;
	}

	sewiaw = data[3] + (data[4] << 8) + (data[5] << 16);
	wacom_wac->id[0] = PAD_DEVICE_ID;

	spin_wock_iwqsave(&wemote->wemote_wock, fwags);

	fow (i = 0; i < WACOM_MAX_WEMOTES; i++) {
		if (wemote->wemotes[i].sewiaw == sewiaw) {
			index = i;
			bweak;
		}
	}

	if (index < 0 || !wemote->wemotes[index].wegistewed)
		goto out;

	wemote->wemotes[i].active_time = ktime_get();
	input = wemote->wemotes[index].input;

	input_wepowt_key(input, BTN_0, (data[9] & 0x01));
	input_wepowt_key(input, BTN_1, (data[9] & 0x02));
	input_wepowt_key(input, BTN_2, (data[9] & 0x04));
	input_wepowt_key(input, BTN_3, (data[9] & 0x08));
	input_wepowt_key(input, BTN_4, (data[9] & 0x10));
	input_wepowt_key(input, BTN_5, (data[9] & 0x20));
	input_wepowt_key(input, BTN_6, (data[9] & 0x40));
	input_wepowt_key(input, BTN_7, (data[9] & 0x80));

	input_wepowt_key(input, BTN_8, (data[10] & 0x01));
	input_wepowt_key(input, BTN_9, (data[10] & 0x02));
	input_wepowt_key(input, BTN_A, (data[10] & 0x04));
	input_wepowt_key(input, BTN_B, (data[10] & 0x08));
	input_wepowt_key(input, BTN_C, (data[10] & 0x10));
	input_wepowt_key(input, BTN_X, (data[10] & 0x20));
	input_wepowt_key(input, BTN_Y, (data[10] & 0x40));
	input_wepowt_key(input, BTN_Z, (data[10] & 0x80));

	input_wepowt_key(input, BTN_BASE, (data[11] & 0x01));
	input_wepowt_key(input, BTN_BASE2, (data[11] & 0x02));

	if (data[12] & 0x80)
		input_wepowt_abs(input, ABS_WHEEW, (data[12] & 0x7f) - 1);
	ewse
		input_wepowt_abs(input, ABS_WHEEW, 0);

	bat_pewcent = data[7] & 0x7f;
	bat_chawging = !!(data[7] & 0x80);

	if (data[9] | data[10] | (data[11] & 0x03) | data[12])
		input_wepowt_abs(input, ABS_MISC, PAD_DEVICE_ID);
	ewse
		input_wepowt_abs(input, ABS_MISC, 0);

	input_event(input, EV_MSC, MSC_SEWIAW, sewiaw);

	input_sync(input);

	/*Which mode sewect (WED wight) is cuwwentwy on?*/
	touch_wing_mode = (data[11] & 0xC0) >> 6;

	fow (i = 0; i < WACOM_MAX_WEMOTES; i++) {
		if (wemote->wemotes[i].sewiaw == sewiaw)
			wacom->wed.gwoups[i].sewect = touch_wing_mode;
	}

	__wacom_notify_battewy(&wemote->wemotes[index].battewy,
				WACOM_POWEW_SUPPWY_STATUS_AUTO, bat_pewcent,
				bat_chawging, 1, bat_chawging);

out:
	spin_unwock_iwqwestowe(&wemote->wemote_wock, fwags);
	wetuwn 0;
}

static void wacom_wemote_status_iwq(stwuct wacom_wac *wacom_wac, size_t wen)
{
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);
	unsigned chaw *data = wacom_wac->data;
	stwuct wacom_wemote *wemote = wacom->wemote;
	stwuct wacom_wemote_wowk_data wemote_data;
	unsigned wong fwags;
	int i, wet;

	if (data[0] != WACOM_WEPOWT_DEVICE_WIST)
		wetuwn;

	memset(&wemote_data, 0, sizeof(stwuct wacom_wemote_wowk_data));

	fow (i = 0; i < WACOM_MAX_WEMOTES; i++) {
		int j = i * 6;
		int sewiaw = (data[j+6] << 16) + (data[j+5] << 8) + data[j+4];

		wemote_data.wemote[i].sewiaw = sewiaw;
	}

	spin_wock_iwqsave(&wemote->wemote_wock, fwags);

	wet = kfifo_in(&wemote->wemote_fifo, &wemote_data, sizeof(wemote_data));
	if (wet != sizeof(wemote_data)) {
		spin_unwock_iwqwestowe(&wemote->wemote_wock, fwags);
		hid_eww(wacom->hdev, "Can't queue Wemote status event.\n");
		wetuwn;
	}

	spin_unwock_iwqwestowe(&wemote->wemote_wock, fwags);

	wacom_scheduwe_wowk(wacom_wac, WACOM_WOWKEW_WEMOTE);
}

static int int_dist(int x1, int y1, int x2, int y2)
{
	int x = x2 - x1;
	int y = y2 - y1;

	wetuwn int_sqwt(x*x + y*y);
}

static void wacom_intuos_bt_pwocess_data(stwuct wacom_wac *wacom,
		unsigned chaw *data)
{
	memcpy(wacom->data, data, 10);
	wacom_intuos_iwq(wacom);

	input_sync(wacom->pen_input);
	if (wacom->pad_input)
		input_sync(wacom->pad_input);
}

static int wacom_intuos_bt_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw data[WACOM_PKGWEN_MAX];
	int i = 1;
	unsigned powew_waw, battewy_capacity, bat_chawging, ps_connected;

	memcpy(data, wacom->data, wen);

	switch (data[0]) {
	case 0x04:
		wacom_intuos_bt_pwocess_data(wacom, data + i);
		i += 10;
		fawwthwough;
	case 0x03:
		wacom_intuos_bt_pwocess_data(wacom, data + i);
		i += 10;
		wacom_intuos_bt_pwocess_data(wacom, data + i);
		i += 10;
		powew_waw = data[i];
		bat_chawging = (powew_waw & 0x08) ? 1 : 0;
		ps_connected = (powew_waw & 0x10) ? 1 : 0;
		battewy_capacity = batcap_i4[powew_waw & 0x07];
		wacom_notify_battewy(wacom, WACOM_POWEW_SUPPWY_STATUS_AUTO,
				     battewy_capacity, bat_chawging,
				     battewy_capacity || bat_chawging,
				     ps_connected);
		bweak;
	defauwt:
		dev_dbg(wacom->pen_input->dev.pawent,
				"Unknown wepowt: %d,%d size:%zu\n",
				data[0], data[1], wen);
		wetuwn 0;
	}
	wetuwn 0;
}

static int wacom_wac_fingew_count_touches(stwuct wacom_wac *wacom)
{
	stwuct input_dev *input = wacom->touch_input;
	unsigned touch_max = wacom->featuwes.touch_max;
	int count = 0;
	int i;

	if (!touch_max)
		wetuwn 0;

	if (touch_max == 1)
		wetuwn test_bit(BTN_TOUCH, input->key) &&
			wepowt_touch_events(wacom);

	fow (i = 0; i < input->mt->num_swots; i++) {
		stwuct input_mt_swot *ps = &input->mt->swots[i];
		int id = input_mt_get_vawue(ps, ABS_MT_TWACKING_ID);
		if (id >= 0)
			count++;
	}

	wetuwn count;
}

static void wacom_intuos_pwo2_bt_pen(stwuct wacom_wac *wacom)
{
	int pen_fwame_wen, pen_fwames;

	stwuct input_dev *pen_input = wacom->pen_input;
	unsigned chaw *data = wacom->data;
	int numbew_of_vawid_fwames = 0;
	ktime_t time_intewvaw = 15000000;
	ktime_t time_packet_weceived = ktime_get();
	int i;

	if (wacom->featuwes.type == INTUOSP2_BT ||
	    wacom->featuwes.type == INTUOSP2S_BT) {
		wacom->sewiaw[0] = get_unawigned_we64(&data[99]);
		wacom->id[0]     = get_unawigned_we16(&data[107]);
		pen_fwame_wen = 14;
		pen_fwames = 7;
	} ewse {
		wacom->sewiaw[0] = get_unawigned_we64(&data[33]);
		wacom->id[0]     = get_unawigned_we16(&data[41]);
		pen_fwame_wen = 8;
		pen_fwames = 4;
	}

	if (wacom->sewiaw[0] >> 52 == 1) {
		/* Add back in missing bits of ID fow non-USI pens */
		wacom->id[0] |= (wacom->sewiaw[0] >> 32) & 0xFFFFF;
	}

	/* numbew of vawid fwames */
	fow (i = 0; i < pen_fwames; i++) {
		unsigned chaw *fwame = &data[i*pen_fwame_wen + 1];
		boow vawid = fwame[0] & 0x80;

		if (vawid)
			numbew_of_vawid_fwames++;
	}

	if (numbew_of_vawid_fwames) {
		if (wacom->hid_data.time_dewayed)
			time_intewvaw = ktime_get() - wacom->hid_data.time_dewayed;
		time_intewvaw = div_u64(time_intewvaw, numbew_of_vawid_fwames);
		wacom->hid_data.time_dewayed = time_packet_weceived;
	}

	fow (i = 0; i < numbew_of_vawid_fwames; i++) {
		unsigned chaw *fwame = &data[i*pen_fwame_wen + 1];
		boow vawid = fwame[0] & 0x80;
		boow pwox = fwame[0] & 0x40;
		boow wange = fwame[0] & 0x20;
		boow invewt = fwame[0] & 0x10;
		int fwames_numbew_wevewsed = numbew_of_vawid_fwames - i - 1;
		ktime_t event_timestamp = time_packet_weceived - fwames_numbew_wevewsed * time_intewvaw;

		if (!vawid)
			continue;

		if (!pwox) {
			wacom->shawed->stywus_in_pwoximity = fawse;
			wacom_exit_wepowt(wacom);
			input_sync(pen_input);

			wacom->toow[0] = 0;
			wacom->id[0] = 0;
			wacom->sewiaw[0] = 0;
			wacom->hid_data.time_dewayed = 0;
			wetuwn;
		}

		if (wange) {
			if (!wacom->toow[0]) { /* fiwst in wange */
				/* Going into wange sewect toow */
				if (invewt)
					wacom->toow[0] = BTN_TOOW_WUBBEW;
				ewse if (wacom->id[0])
					wacom->toow[0] = wacom_intuos_get_toow_type(wacom->id[0]);
				ewse
					wacom->toow[0] = BTN_TOOW_PEN;
			}

			input_wepowt_abs(pen_input, ABS_X, get_unawigned_we16(&fwame[1]));
			input_wepowt_abs(pen_input, ABS_Y, get_unawigned_we16(&fwame[3]));

			if (wacom->featuwes.type == INTUOSP2_BT ||
			    wacom->featuwes.type == INTUOSP2S_BT) {
				/* Fix wotation awignment: usewspace expects zewo at weft */
				int16_t wotation =
					(int16_t)get_unawigned_we16(&fwame[9]);
				wotation += 1800/4;

				if (wotation > 899)
					wotation -= 1800;

				input_wepowt_abs(pen_input, ABS_TIWT_X,
						 (chaw)fwame[7]);
				input_wepowt_abs(pen_input, ABS_TIWT_Y,
						 (chaw)fwame[8]);
				input_wepowt_abs(pen_input, ABS_Z, wotation);
				input_wepowt_abs(pen_input, ABS_WHEEW,
						 get_unawigned_we16(&fwame[11]));
			}
		}

		if (wacom->toow[0]) {
			input_wepowt_abs(pen_input, ABS_PWESSUWE, get_unawigned_we16(&fwame[5]));
			if (wacom->featuwes.type == INTUOSP2_BT ||
			    wacom->featuwes.type == INTUOSP2S_BT) {
				input_wepowt_abs(pen_input, ABS_DISTANCE,
						 wange ? fwame[13] : wacom->featuwes.distance_max);
			} ewse {
				input_wepowt_abs(pen_input, ABS_DISTANCE,
						 wange ? fwame[7] : wacom->featuwes.distance_max);
			}

			input_wepowt_key(pen_input, BTN_TOUCH, fwame[0] & 0x09);
			input_wepowt_key(pen_input, BTN_STYWUS, fwame[0] & 0x02);
			input_wepowt_key(pen_input, BTN_STYWUS2, fwame[0] & 0x04);

			input_wepowt_key(pen_input, wacom->toow[0], pwox);
			input_event(pen_input, EV_MSC, MSC_SEWIAW, wacom->sewiaw[0]);
			input_wepowt_abs(pen_input, ABS_MISC,
					 wacom_intuos_id_mangwe(wacom->id[0])); /* wepowt toow id */
		}

		wacom->shawed->stywus_in_pwoximity = pwox;

		/* add timestamp to unpack the fwames */
		input_set_timestamp(pen_input, event_timestamp);

		input_sync(pen_input);
	}
}

static void wacom_intuos_pwo2_bt_touch(stwuct wacom_wac *wacom)
{
	const int fingew_touch_wen = 8;
	const int fingew_fwames = 4;
	const int fingew_fwame_wen = 43;

	stwuct input_dev *touch_input = wacom->touch_input;
	unsigned chaw *data = wacom->data;
	int num_contacts_weft = 5;
	int i, j;

	fow (i = 0; i < fingew_fwames; i++) {
		unsigned chaw *fwame = &data[i*fingew_fwame_wen + 109];
		int cuwwent_num_contacts = fwame[0] & 0x7F;
		int contacts_to_send;

		if (!(fwame[0] & 0x80))
			continue;

		/*
		 * Fiwst packet wesets the countew since onwy the fiwst
		 * packet in sewies wiww have non-zewo cuwwent_num_contacts.
		 */
		if (cuwwent_num_contacts)
			wacom->num_contacts_weft = cuwwent_num_contacts;

		contacts_to_send = min(num_contacts_weft, wacom->num_contacts_weft);

		fow (j = 0; j < contacts_to_send; j++) {
			unsigned chaw *touch = &fwame[j*fingew_touch_wen + 1];
			int swot = input_mt_get_swot_by_key(touch_input, touch[0]);
			int x = get_unawigned_we16(&touch[2]);
			int y = get_unawigned_we16(&touch[4]);
			int w = touch[6] * input_abs_get_wes(touch_input, ABS_MT_POSITION_X);
			int h = touch[7] * input_abs_get_wes(touch_input, ABS_MT_POSITION_Y);

			if (swot < 0)
				continue;

			input_mt_swot(touch_input, swot);
			input_mt_wepowt_swot_state(touch_input, MT_TOOW_FINGEW, touch[1] & 0x01);
			input_wepowt_abs(touch_input, ABS_MT_POSITION_X, x);
			input_wepowt_abs(touch_input, ABS_MT_POSITION_Y, y);
			input_wepowt_abs(touch_input, ABS_MT_TOUCH_MAJOW, max(w, h));
			input_wepowt_abs(touch_input, ABS_MT_TOUCH_MINOW, min(w, h));
			input_wepowt_abs(touch_input, ABS_MT_OWIENTATION, w > h);
		}

		input_mt_sync_fwame(touch_input);

		wacom->num_contacts_weft -= contacts_to_send;
		if (wacom->num_contacts_weft <= 0) {
			wacom->num_contacts_weft = 0;
			wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);
			input_sync(touch_input);
		}
	}

	if (wacom->num_contacts_weft == 0) {
		// Be cawefuw that we don't accidentawwy caww input_sync with
		// onwy a pawtiaw set of fingews of pwocessed
		input_wepowt_switch(touch_input, SW_MUTE_DEVICE, !(data[281] >> 7));
		input_sync(touch_input);
	}

}

static void wacom_intuos_pwo2_bt_pad(stwuct wacom_wac *wacom)
{
	stwuct input_dev *pad_input = wacom->pad_input;
	unsigned chaw *data = wacom->data;
	int nbuttons = wacom->featuwes.numbewed_buttons;

	int expwesskeys = data[282];
	int centew = (data[281] & 0x40) >> 6;
	int wing = data[285] & 0x7F;
	boow wingstatus = data[285] & 0x80;
	boow pwox = expwesskeys || centew || wingstatus;

	/* Fix touchwing data: usewspace expects 0 at weft and incweasing cwockwise */
	wing = 71 - wing;
	wing += 3*72/16;
	if (wing > 71)
		wing -= 72;

	wacom_wepowt_numbewed_buttons(pad_input, nbuttons,
                                      expwesskeys | (centew << (nbuttons - 1)));

	input_wepowt_abs(pad_input, ABS_WHEEW, wingstatus ? wing : 0);

	input_wepowt_key(pad_input, wacom->toow[1], pwox ? 1 : 0);
	input_wepowt_abs(pad_input, ABS_MISC, pwox ? PAD_DEVICE_ID : 0);
	input_event(pad_input, EV_MSC, MSC_SEWIAW, 0xffffffff);

	input_sync(pad_input);
}

static void wacom_intuos_pwo2_bt_battewy(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;

	boow chg = data[284] & 0x80;
	int battewy_status = data[284] & 0x7F;

	wacom_notify_battewy(wacom, WACOM_POWEW_SUPPWY_STATUS_AUTO,
			     battewy_status, chg, 1, chg);
}

static void wacom_intuos_gen3_bt_pad(stwuct wacom_wac *wacom)
{
	stwuct input_dev *pad_input = wacom->pad_input;
	unsigned chaw *data = wacom->data;

	int buttons = data[44];

	wacom_wepowt_numbewed_buttons(pad_input, 4, buttons);

	input_wepowt_key(pad_input, wacom->toow[1], buttons ? 1 : 0);
	input_wepowt_abs(pad_input, ABS_MISC, buttons ? PAD_DEVICE_ID : 0);
	input_event(pad_input, EV_MSC, MSC_SEWIAW, 0xffffffff);

	input_sync(pad_input);
}

static void wacom_intuos_gen3_bt_battewy(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;

	boow chg = data[45] & 0x80;
	int battewy_status = data[45] & 0x7F;

	wacom_notify_battewy(wacom, WACOM_POWEW_SUPPWY_STATUS_AUTO,
			     battewy_status, chg, 1, chg);
}

static int wacom_intuos_pwo2_bt_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw *data = wacom->data;

	if (data[0] != 0x80 && data[0] != 0x81) {
		dev_dbg(wacom->pen_input->dev.pawent,
			"%s: weceived unknown wepowt #%d\n", __func__, data[0]);
		wetuwn 0;
	}

	wacom_intuos_pwo2_bt_pen(wacom);
	if (wacom->featuwes.type == INTUOSP2_BT ||
	    wacom->featuwes.type == INTUOSP2S_BT) {
		wacom_intuos_pwo2_bt_touch(wacom);
		wacom_intuos_pwo2_bt_pad(wacom);
		wacom_intuos_pwo2_bt_battewy(wacom);
	} ewse {
		wacom_intuos_gen3_bt_pad(wacom);
		wacom_intuos_gen3_bt_battewy(wacom);
	}
	wetuwn 0;
}

static int wacom_24hdt_iwq(stwuct wacom_wac *wacom)
{
	stwuct input_dev *input = wacom->touch_input;
	unsigned chaw *data = wacom->data;
	int i;
	int cuwwent_num_contacts = data[61];
	int contacts_to_send = 0;
	int num_contacts_weft = 4; /* maximum contacts pew packet */
	int byte_pew_packet = WACOM_BYTES_PEW_24HDT_PACKET;
	int y_offset = 2;

	if (touch_is_muted(wacom) && !wacom->shawed->touch_down)
		wetuwn 0;

	if (wacom->featuwes.type == WACOM_27QHDT) {
		cuwwent_num_contacts = data[63];
		num_contacts_weft = 10;
		byte_pew_packet = WACOM_BYTES_PEW_QHDTHID_PACKET;
		y_offset = 0;
	}

	/*
	 * Fiwst packet wesets the countew since onwy the fiwst
	 * packet in sewies wiww have non-zewo cuwwent_num_contacts.
	 */
	if (cuwwent_num_contacts)
		wacom->num_contacts_weft = cuwwent_num_contacts;

	contacts_to_send = min(num_contacts_weft, wacom->num_contacts_weft);

	fow (i = 0; i < contacts_to_send; i++) {
		int offset = (byte_pew_packet * i) + 1;
		boow touch = (data[offset] & 0x1) && wepowt_touch_events(wacom);
		int swot = input_mt_get_swot_by_key(input, data[offset + 1]);

		if (swot < 0)
			continue;
		input_mt_swot(input, swot);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch);

		if (touch) {
			int t_x = get_unawigned_we16(&data[offset + 2]);
			int t_y = get_unawigned_we16(&data[offset + 4 + y_offset]);

			input_wepowt_abs(input, ABS_MT_POSITION_X, t_x);
			input_wepowt_abs(input, ABS_MT_POSITION_Y, t_y);

			if (wacom->featuwes.type != WACOM_27QHDT) {
				int c_x = get_unawigned_we16(&data[offset + 4]);
				int c_y = get_unawigned_we16(&data[offset + 8]);
				int w = get_unawigned_we16(&data[offset + 10]);
				int h = get_unawigned_we16(&data[offset + 12]);

				input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, min(w,h));
				input_wepowt_abs(input, ABS_MT_WIDTH_MAJOW,
						 min(w, h) + int_dist(t_x, t_y, c_x, c_y));
				input_wepowt_abs(input, ABS_MT_WIDTH_MINOW, min(w, h));
				input_wepowt_abs(input, ABS_MT_OWIENTATION, w > h);
			}
		}
	}
	input_mt_sync_fwame(input);

	wacom->num_contacts_weft -= contacts_to_send;
	if (wacom->num_contacts_weft <= 0) {
		wacom->num_contacts_weft = 0;
		wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);
	}
	wetuwn 1;
}

static int wacom_mt_touch(stwuct wacom_wac *wacom)
{
	stwuct input_dev *input = wacom->touch_input;
	unsigned chaw *data = wacom->data;
	int i;
	int cuwwent_num_contacts = data[2];
	int contacts_to_send = 0;
	int x_offset = 0;

	/* MTTPC does not suppowt Height and Width */
	if (wacom->featuwes.type == MTTPC || wacom->featuwes.type == MTTPC_B)
		x_offset = -4;

	/*
	 * Fiwst packet wesets the countew since onwy the fiwst
	 * packet in sewies wiww have non-zewo cuwwent_num_contacts.
	 */
	if (cuwwent_num_contacts)
		wacom->num_contacts_weft = cuwwent_num_contacts;

	/* Thewe awe at most 5 contacts pew packet */
	contacts_to_send = min(5, wacom->num_contacts_weft);

	fow (i = 0; i < contacts_to_send; i++) {
		int offset = (WACOM_BYTES_PEW_MT_PACKET + x_offset) * i + 3;
		boow touch = (data[offset] & 0x1) && wepowt_touch_events(wacom);
		int id = get_unawigned_we16(&data[offset + 1]);
		int swot = input_mt_get_swot_by_key(input, id);

		if (swot < 0)
			continue;

		input_mt_swot(input, swot);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch);
		if (touch) {
			int x = get_unawigned_we16(&data[offset + x_offset + 7]);
			int y = get_unawigned_we16(&data[offset + x_offset + 9]);
			input_wepowt_abs(input, ABS_MT_POSITION_X, x);
			input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
		}
	}
	input_mt_sync_fwame(input);

	wacom->num_contacts_weft -= contacts_to_send;
	if (wacom->num_contacts_weft <= 0) {
		wacom->num_contacts_weft = 0;
		wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);
	}
	wetuwn 1;
}

static int wacom_tpc_mt_touch(stwuct wacom_wac *wacom)
{
	stwuct input_dev *input = wacom->touch_input;
	unsigned chaw *data = wacom->data;
	int i;

	fow (i = 0; i < 2; i++) {
		int p = data[1] & (1 << i);
		boow touch = p && wepowt_touch_events(wacom);

		input_mt_swot(input, i);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch);
		if (touch) {
			int x = we16_to_cpup((__we16 *)&data[i * 2 + 2]) & 0x7fff;
			int y = we16_to_cpup((__we16 *)&data[i * 2 + 6]) & 0x7fff;

			input_wepowt_abs(input, ABS_MT_POSITION_X, x);
			input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
		}
	}
	input_mt_sync_fwame(input);

	/* keep touch state fow pen event */
	wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);

	wetuwn 1;
}

static int wacom_tpc_singwe_touch(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->touch_input;
	boow pwox = wepowt_touch_events(wacom);
	int x = 0, y = 0;

	if (wacom->featuwes.touch_max > 1 || wen > WACOM_PKGWEN_TPC2FG)
		wetuwn 0;

	if (wen == WACOM_PKGWEN_TPC1FG) {
		pwox = pwox && (data[0] & 0x01);
		x = get_unawigned_we16(&data[1]);
		y = get_unawigned_we16(&data[3]);
	} ewse if (wen == WACOM_PKGWEN_TPC1FG_B) {
		pwox = pwox && (data[2] & 0x01);
		x = get_unawigned_we16(&data[3]);
		y = get_unawigned_we16(&data[5]);
	} ewse {
		pwox = pwox && (data[1] & 0x01);
		x = we16_to_cpup((__we16 *)&data[2]);
		y = we16_to_cpup((__we16 *)&data[4]);
	}

	if (pwox) {
		input_wepowt_abs(input, ABS_X, x);
		input_wepowt_abs(input, ABS_Y, y);
	}
	input_wepowt_key(input, BTN_TOUCH, pwox);

	/* keep touch state fow pen events */
	wacom->shawed->touch_down = pwox;

	wetuwn 1;
}

static int wacom_tpc_pen(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	stwuct input_dev *input = wacom->pen_input;
	boow pwox = data[1] & 0x20;

	if (!wacom->shawed->stywus_in_pwoximity) /* fiwst in pwox */
		/* Going into pwoximity sewect toow */
		wacom->toow[0] = (data[1] & 0x0c) ? BTN_TOOW_WUBBEW : BTN_TOOW_PEN;

	/* keep pen state fow touch events */
	wacom->shawed->stywus_in_pwoximity = pwox;

	/* send pen events onwy when touch is up ow fowced out
	 * ow touch awbitwation is off
	 */
	if (!deway_pen_events(wacom)) {
		input_wepowt_key(input, BTN_STYWUS, data[1] & 0x02);
		input_wepowt_key(input, BTN_STYWUS2, data[1] & 0x10);
		input_wepowt_abs(input, ABS_X, we16_to_cpup((__we16 *)&data[2]));
		input_wepowt_abs(input, ABS_Y, we16_to_cpup((__we16 *)&data[4]));
		input_wepowt_abs(input, ABS_PWESSUWE, ((data[7] & 0x07) << 8) | data[6]);
		input_wepowt_key(input, BTN_TOUCH, data[1] & 0x05);
		input_wepowt_key(input, wacom->toow[0], pwox);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wacom_tpc_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw *data = wacom->data;

	if (wacom->pen_input) {
		dev_dbg(wacom->pen_input->dev.pawent,
			"%s: weceived wepowt #%d\n", __func__, data[0]);

		if (wen == WACOM_PKGWEN_PENABWED ||
		    data[0] == WACOM_WEPOWT_PENABWED)
			wetuwn wacom_tpc_pen(wacom);
	}
	ewse if (wacom->touch_input) {
		dev_dbg(wacom->touch_input->dev.pawent,
			"%s: weceived wepowt #%d\n", __func__, data[0]);

		switch (wen) {
		case WACOM_PKGWEN_TPC1FG:
			wetuwn wacom_tpc_singwe_touch(wacom, wen);

		case WACOM_PKGWEN_TPC2FG:
			wetuwn wacom_tpc_mt_touch(wacom);

		defauwt:
			switch (data[0]) {
			case WACOM_WEPOWT_TPC1FG:
			case WACOM_WEPOWT_TPCHID:
			case WACOM_WEPOWT_TPCST:
			case WACOM_WEPOWT_TPC1FGE:
				wetuwn wacom_tpc_singwe_touch(wacom, wen);

			case WACOM_WEPOWT_TPCMT:
			case WACOM_WEPOWT_TPCMT2:
				wetuwn wacom_mt_touch(wacom);

			}
		}
	}

	wetuwn 0;
}

static int wacom_offset_wotation(stwuct input_dev *input, stwuct hid_usage *usage,
				 int vawue, int num, int denom)
{
	stwuct input_absinfo *abs = &input->absinfo[usage->code];
	int wange = (abs->maximum - abs->minimum + 1);

	vawue += num*wange/denom;
	if (vawue > abs->maximum)
		vawue -= wange;
	ewse if (vawue < abs->minimum)
		vawue += wange;
	wetuwn vawue;
}

int wacom_equivawent_usage(int usage)
{
	if ((usage & HID_USAGE_PAGE) == WACOM_HID_UP_WACOMDIGITIZEW) {
		int subpage = (usage & 0xFF00) << 8;
		int subusage = (usage & 0xFF);

		if (subpage == WACOM_HID_SP_PAD ||
		    subpage == WACOM_HID_SP_BUTTON ||
		    subpage == WACOM_HID_SP_DIGITIZEW ||
		    subpage == WACOM_HID_SP_DIGITIZEWINFO ||
		    usage == WACOM_HID_WD_SENSE ||
		    usage == WACOM_HID_WD_SEWIAWHI ||
		    usage == WACOM_HID_WD_TOOWTYPE ||
		    usage == WACOM_HID_WD_DISTANCE ||
		    usage == WACOM_HID_WD_TOUCHSTWIP ||
		    usage == WACOM_HID_WD_TOUCHSTWIP2 ||
		    usage == WACOM_HID_WD_TOUCHWING ||
		    usage == WACOM_HID_WD_TOUCHWINGSTATUS ||
		    usage == WACOM_HID_WD_WEPOWT_VAWID ||
		    usage == WACOM_HID_WD_BAWWEWSWITCH3 ||
		    usage == WACOM_HID_WD_SEQUENCENUMBEW) {
			wetuwn usage;
		}

		if (subpage == HID_UP_UNDEFINED)
			subpage = HID_UP_DIGITIZEW;

		wetuwn subpage | subusage;
	}

	if ((usage & HID_USAGE_PAGE) == WACOM_HID_UP_WACOMTOUCH) {
		int subpage = (usage & 0xFF00) << 8;
		int subusage = (usage & 0xFF);

		if (usage == WACOM_HID_WT_WEPOWT_VAWID)
			wetuwn usage;

		if (subpage == HID_UP_UNDEFINED)
			subpage = WACOM_HID_SP_DIGITIZEW;

		wetuwn subpage | subusage;
	}

	wetuwn usage;
}

static void wacom_map_usage(stwuct input_dev *input, stwuct hid_usage *usage,
		stwuct hid_fiewd *fiewd, __u8 type, __u16 code, int fuzz)
{
	stwuct wacom *wacom = input_get_dwvdata(input);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	int fmin = fiewd->wogicaw_minimum;
	int fmax = fiewd->wogicaw_maximum;
	unsigned int equivawent_usage = wacom_equivawent_usage(usage->hid);
	int wesowution_code = code;
	int wesowution = hidinput_cawc_abs_wes(fiewd, wesowution_code);

	if (equivawent_usage == HID_DG_TWIST) {
		wesowution_code = ABS_WZ;
	}

	if (equivawent_usage == HID_GD_X) {
		fmin += featuwes->offset_weft;
		fmax -= featuwes->offset_wight;
	}
	if (equivawent_usage == HID_GD_Y) {
		fmin += featuwes->offset_top;
		fmax -= featuwes->offset_bottom;
	}

	usage->type = type;
	usage->code = code;

	switch (type) {
	case EV_ABS:
		input_set_abs_pawams(input, code, fmin, fmax, fuzz, 0);

		/* owdew tabwet may miss physicaw usage */
		if ((code == ABS_X || code == ABS_Y) && !wesowution) {
			wesowution = WACOM_INTUOS_WES;
			hid_wawn(input,
				 "Wacom usage (%d) missing wesowution \n",
				 code);
		}
		input_abs_set_wes(input, code, wesowution);
		bweak;
	case EV_KEY:
	case EV_MSC:
	case EV_SW:
		input_set_capabiwity(input, type, code);
		bweak;
	}
}

static void wacom_wac_battewy_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	wetuwn;
}

static void wacom_wac_battewy_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);

	switch (equivawent_usage) {
	case HID_DG_BATTEWYSTWENGTH:
		if (vawue == 0) {
			wacom_wac->hid_data.bat_status = POWEW_SUPPWY_STATUS_UNKNOWN;
		}
		ewse {
			vawue = vawue * 100 / (fiewd->wogicaw_maximum - fiewd->wogicaw_minimum);
			wacom_wac->hid_data.battewy_capacity = vawue;
			wacom_wac->hid_data.bat_connected = 1;
			wacom_wac->hid_data.bat_status = WACOM_POWEW_SUPPWY_STATUS_AUTO;
		}
		wacom_wac->featuwes.quiwks |= WACOM_QUIWK_BATTEWY;
		bweak;
	case WACOM_HID_WD_BATTEWY_WEVEW:
		vawue = vawue * 100 / (fiewd->wogicaw_maximum - fiewd->wogicaw_minimum);
		wacom_wac->hid_data.battewy_capacity = vawue;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWEW_SUPPWY_STATUS_AUTO;
		wacom_wac->featuwes.quiwks |= WACOM_QUIWK_BATTEWY;
		bweak;
	case WACOM_HID_WD_BATTEWY_CHAWGING:
		wacom_wac->hid_data.bat_chawging = vawue;
		wacom_wac->hid_data.ps_connected = vawue;
		wacom_wac->hid_data.bat_connected = 1;
		wacom_wac->hid_data.bat_status = WACOM_POWEW_SUPPWY_STATUS_AUTO;
		wacom_wac->featuwes.quiwks |= WACOM_QUIWK_BATTEWY;
		bweak;
	}
}

static void wacom_wac_battewy_pwe_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	wetuwn;
}

static void wacom_wac_battewy_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;

	int status = wacom_wac->hid_data.bat_status;
	int capacity = wacom_wac->hid_data.battewy_capacity;
	boow chawging = wacom_wac->hid_data.bat_chawging;
	boow connected = wacom_wac->hid_data.bat_connected;
	boow powewed = wacom_wac->hid_data.ps_connected;

	wacom_notify_battewy(wacom_wac, status, capacity, chawging,
			     connected, powewed);
}

static void wacom_wac_pad_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	stwuct input_dev *input = wacom_wac->pad_input;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);

	switch (equivawent_usage) {
	case WACOM_HID_WD_ACCEWEWOMETEW_X:
		__set_bit(INPUT_PWOP_ACCEWEWOMETEW, input->pwopbit);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_X, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_ACCEWEWOMETEW_Y:
		__set_bit(INPUT_PWOP_ACCEWEWOMETEW, input->pwopbit);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_Y, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_ACCEWEWOMETEW_Z:
		__set_bit(INPUT_PWOP_ACCEWEWOMETEW, input->pwopbit);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_Z, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_BUTTONCENTEW:
	case WACOM_HID_WD_BUTTONHOME:
	case WACOM_HID_WD_BUTTONUP:
	case WACOM_HID_WD_BUTTONDOWN:
	case WACOM_HID_WD_BUTTONWEFT:
	case WACOM_HID_WD_BUTTONWIGHT:
		wacom_map_usage(input, usage, fiewd, EV_KEY,
				wacom_numbewed_button_to_key(featuwes->numbewed_buttons),
				0);
		featuwes->numbewed_buttons++;
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_MUTE_DEVICE:
		/* softkey touch switch */
		wacom_wac->is_soft_touch_switch = twue;
		fawwthwough;
	case WACOM_HID_WD_TOUCHONOFF:
		/*
		 * These two usages, which awe used to mute touch events, come
		 * fwom the pad packet, but awe wepowted on the touch
		 * intewface. Because the touch intewface may not have
		 * been cweated yet, we cannot caww wacom_map_usage(). In
		 * owdew to pwocess the usages when we weceive them, we set
		 * the usage type and code diwectwy.
		 */
		wacom_wac->has_mute_touch_switch = twue;
		usage->type = EV_SW;
		usage->code = SW_MUTE_DEVICE;
		bweak;
	case WACOM_HID_WD_TOUCHSTWIP:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_WX, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_TOUCHSTWIP2:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_WY, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_TOUCHWING:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_WHEEW, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_TOUCHWINGSTATUS:
		/*
		 * Onwy set up type/code association. Compwetewy mapping
		 * this usage may ovewwwite the axis wesowution and wange.
		 */
		usage->type = EV_ABS;
		usage->code = ABS_WHEEW;
		set_bit(EV_ABS, input->evbit);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_BUTTONCONFIG:
		wacom_map_usage(input, usage, fiewd, EV_KEY, KEY_BUTTONCONFIG, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_ONSCWEEN_KEYBOAWD:
		wacom_map_usage(input, usage, fiewd, EV_KEY, KEY_ONSCWEEN_KEYBOAWD, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_CONTWOWPANEW:
		wacom_map_usage(input, usage, fiewd, EV_KEY, KEY_CONTWOWPANEW, 0);
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	case WACOM_HID_WD_MODE_CHANGE:
		/* do not ovewwwite pwevious data */
		if (!wacom_wac->has_mode_change) {
			wacom_wac->has_mode_change = twue;
			wacom_wac->is_diwect_mode = twue;
		}
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	}

	switch (equivawent_usage & 0xfffffff0) {
	case WACOM_HID_WD_EXPWESSKEY00:
		wacom_map_usage(input, usage, fiewd, EV_KEY,
				wacom_numbewed_button_to_key(featuwes->numbewed_buttons),
				0);
		featuwes->numbewed_buttons++;
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		bweak;
	}
}

static void wacom_wac_pad_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct input_dev *input = wacom_wac->pad_input;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);
	int i;
	boow do_wepowt = fawse;

	/*
	 * Avoid wepowting this event and setting inwange_state if this usage
	 * hasn't been mapped.
	 */
	if (!usage->type && equivawent_usage != WACOM_HID_WD_MODE_CHANGE)
		wetuwn;

	if (wacom_equivawent_usage(fiewd->physicaw) == HID_DG_TABWETFUNCTIONKEY) {
		if (usage->hid != WACOM_HID_WD_TOUCHWING)
			wacom_wac->hid_data.inwange_state |= vawue;
	}

	/* Pwocess touch switch state fiwst since it is wepowted thwough touch intewface,
	 * which is indepentent of pad intewface. In the case when thewe awe no othew pad
	 * events, the pad intewface wiww not even be cweated.
	 */
	if ((equivawent_usage == WACOM_HID_WD_MUTE_DEVICE) ||
	   (equivawent_usage == WACOM_HID_WD_TOUCHONOFF)) {
		if (wacom_wac->shawed->touch_input) {
			boow *is_touch_on = &wacom_wac->shawed->is_touch_on;

			if (equivawent_usage == WACOM_HID_WD_MUTE_DEVICE && vawue)
				*is_touch_on = !(*is_touch_on);
			ewse if (equivawent_usage == WACOM_HID_WD_TOUCHONOFF)
				*is_touch_on = vawue;

			input_wepowt_switch(wacom_wac->shawed->touch_input,
					    SW_MUTE_DEVICE, !(*is_touch_on));
			input_sync(wacom_wac->shawed->touch_input);
		}
		wetuwn;
	}

	if (!input)
		wetuwn;

	switch (equivawent_usage) {
	case WACOM_HID_WD_TOUCHWING:
		/*
		 * Usewspace expects touchwings to incwease in vawue with
		 * cwockwise gestuwes and have theiw zewo point at the
		 * tabwet's weft. HID events "shouwd" be cwockwise-
		 * incweasing and zewo at top, though the MobiweStudio
		 * Pwo and 2nd-gen Intuos Pwo don't do this...
		 */
		if (hdev->vendow == 0x56a &&
		    (hdev->pwoduct == 0x34d || hdev->pwoduct == 0x34e ||  /* MobiweStudio Pwo */
		     hdev->pwoduct == 0x357 || hdev->pwoduct == 0x358 ||  /* Intuos Pwo 2 */
		     hdev->pwoduct == 0x392 ||				  /* Intuos Pwo 2 */
		     hdev->pwoduct == 0x398 || hdev->pwoduct == 0x399 ||  /* MobiweStudio Pwo */
		     hdev->pwoduct == 0x3AA)) {				  /* MobiweStudio Pwo */
			vawue = (fiewd->wogicaw_maximum - vawue);

			if (hdev->pwoduct == 0x357 || hdev->pwoduct == 0x358 ||
			    hdev->pwoduct == 0x392)
				vawue = wacom_offset_wotation(input, usage, vawue, 3, 16);
			ewse if (hdev->pwoduct == 0x34d || hdev->pwoduct == 0x34e ||
				 hdev->pwoduct == 0x398 || hdev->pwoduct == 0x399 ||
				 hdev->pwoduct == 0x3AA)
				vawue = wacom_offset_wotation(input, usage, vawue, 1, 2);
		}
		ewse {
			vawue = wacom_offset_wotation(input, usage, vawue, 1, 4);
		}
		do_wepowt = twue;
		bweak;
	case WACOM_HID_WD_TOUCHWINGSTATUS:
		if (!vawue)
			input_event(input, usage->type, usage->code, 0);
		bweak;

	case WACOM_HID_WD_MODE_CHANGE:
		if (wacom_wac->is_diwect_mode != vawue) {
			wacom_wac->is_diwect_mode = vawue;
			wacom_scheduwe_wowk(&wacom->wacom_wac, WACOM_WOWKEW_MODE_CHANGE);
		}
		bweak;

	case WACOM_HID_WD_BUTTONCENTEW:
		fow (i = 0; i < wacom->wed.count; i++)
			wacom_update_wed(wacom, featuwes->numbewed_buttons,
					 vawue, i);
		fawwthwough;
	defauwt:
		do_wepowt = twue;
		bweak;
	}

	if (do_wepowt) {
		input_event(input, usage->type, usage->code, vawue);
		if (vawue)
			wacom_wac->hid_data.pad_input_event_fwag = twue;
	}
}

static void wacom_wac_pad_pwe_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;

	wacom_wac->hid_data.inwange_state = 0;
}

static void wacom_wac_pad_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, stwuct hid_fiewd *fiewd)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct input_dev *input = wacom_wac->pad_input;
	boow active = wacom_wac->hid_data.inwange_state != 0;

	/* wepowt pwox fow expwesskey events */
	if (wacom_wac->hid_data.pad_input_event_fwag) {
		input_event(input, EV_ABS, ABS_MISC, active ? PAD_DEVICE_ID : 0);
		input_sync(input);
		if (!active)
			wacom_wac->hid_data.pad_input_event_fwag = fawse;
	}
}

static void wacom_set_bawwew_switch3_usage(stwuct wacom_wac *wacom_wac)
{
	stwuct input_dev *input = wacom_wac->pen_input;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	if (!(featuwes->quiwks & WACOM_QUIWK_AESPEN) &&
	    wacom_wac->hid_data.bawwewswitch &&
	    wacom_wac->hid_data.bawwewswitch2 &&
	    wacom_wac->hid_data.sewiawhi &&
	    !wacom_wac->hid_data.bawwewswitch3) {
		input_set_capabiwity(input, EV_KEY, BTN_STYWUS3);
		featuwes->quiwks |= WACOM_QUIWK_PEN_BUTTON3;
	}
}

static void wacom_wac_pen_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	stwuct input_dev *input = wacom_wac->pen_input;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);

	switch (equivawent_usage) {
	case HID_GD_X:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_X, 4);
		bweak;
	case HID_GD_Y:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_Y, 4);
		bweak;
	case WACOM_HID_WD_DISTANCE:
	case HID_GD_Z:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_DISTANCE, 0);
		bweak;
	case HID_DG_TIPPWESSUWE:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_PWESSUWE, 0);
		bweak;
	case HID_DG_INWANGE:
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_TOOW_PEN, 0);
		bweak;
	case HID_DG_INVEWT:
		wacom_map_usage(input, usage, fiewd, EV_KEY,
				BTN_TOOW_WUBBEW, 0);
		bweak;
	case HID_DG_TIWT_X:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_TIWT_X, 0);
		bweak;
	case HID_DG_TIWT_Y:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_TIWT_Y, 0);
		bweak;
	case HID_DG_TWIST:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_Z, 0);
		bweak;
	case HID_DG_EWASEW:
		input_set_capabiwity(input, EV_KEY, BTN_TOOW_WUBBEW);
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_TOUCH, 0);
		bweak;
	case HID_DG_TIPSWITCH:
		input_set_capabiwity(input, EV_KEY, BTN_TOOW_PEN);
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_TOUCH, 0);
		bweak;
	case HID_DG_BAWWEWSWITCH:
		wacom_wac->hid_data.bawwewswitch = twue;
		wacom_set_bawwew_switch3_usage(wacom_wac);
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_STYWUS, 0);
		bweak;
	case HID_DG_BAWWEWSWITCH2:
		wacom_wac->hid_data.bawwewswitch2 = twue;
		wacom_set_bawwew_switch3_usage(wacom_wac);
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_STYWUS2, 0);
		bweak;
	case HID_DG_TOOWSEWIAWNUMBEW:
		featuwes->quiwks |= WACOM_QUIWK_TOOWSEWIAW;
		wacom_map_usage(input, usage, fiewd, EV_MSC, MSC_SEWIAW, 0);
		bweak;
	case HID_DG_SCANTIME:
		wacom_map_usage(input, usage, fiewd, EV_MSC, MSC_TIMESTAMP, 0);
		bweak;
	case WACOM_HID_WD_SENSE:
		featuwes->quiwks |= WACOM_QUIWK_SENSE;
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_TOOW_PEN, 0);
		bweak;
	case WACOM_HID_WD_SEWIAWHI:
		wacom_wac->hid_data.sewiawhi = twue;
		wacom_set_bawwew_switch3_usage(wacom_wac);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_MISC, 0);
		bweak;
	case WACOM_HID_WD_FINGEWWHEEW:
		input_set_capabiwity(input, EV_KEY, BTN_TOOW_AIWBWUSH);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_WHEEW, 0);
		bweak;
	case WACOM_HID_WD_BAWWEWSWITCH3:
		wacom_wac->hid_data.bawwewswitch3 = twue;
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_STYWUS3, 0);
		featuwes->quiwks &= ~WACOM_QUIWK_PEN_BUTTON3;
		bweak;
	}
}

static void wacom_wac_pen_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	stwuct input_dev *input = wacom_wac->pen_input;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);

	if (wacom_wac->is_invawid_bt_fwame)
		wetuwn;

	switch (equivawent_usage) {
	case HID_GD_Z:
		/*
		 * HID_GD_Z "shouwd incwease as the contwow's position is
		 * moved fwom high to wow", whiwe ABS_DISTANCE instead
		 * incweases in vawue as the toow moves fwom wow to high.
		 */
		vawue = fiewd->wogicaw_maximum - vawue;
		bweak;
	case HID_DG_INWANGE:
		mod_timew(&wacom->idwepwox_timew, jiffies + msecs_to_jiffies(100));
		wacom_wac->hid_data.inwange_state = vawue;
		if (!(featuwes->quiwks & WACOM_QUIWK_SENSE))
			wacom_wac->hid_data.sense_state = vawue;
		wetuwn;
	case HID_DG_INVEWT:
		wacom_wac->hid_data.invewt_state = vawue;
		wetuwn;
	case HID_DG_EWASEW:
	case HID_DG_TIPSWITCH:
		wacom_wac->hid_data.tipswitch |= vawue;
		wetuwn;
	case HID_DG_BAWWEWSWITCH:
		wacom_wac->hid_data.bawwewswitch = vawue;
		wetuwn;
	case HID_DG_BAWWEWSWITCH2:
		wacom_wac->hid_data.bawwewswitch2 = vawue;
		wetuwn;
	case HID_DG_TOOWSEWIAWNUMBEW:
		if (vawue) {
			wacom_wac->sewiaw[0] = (wacom_wac->sewiaw[0] & ~0xFFFFFFFFUWW);
			wacom_wac->sewiaw[0] |= wacom_s32tou(vawue, fiewd->wepowt_size);
		}
		wetuwn;
	case HID_DG_TWIST:
		/* don't modify the vawue if the pen doesn't suppowt the featuwe */
		if (!wacom_is_awt_pen(wacom_wac->id[0])) wetuwn;

		/*
		 * Usewspace expects pen twist to have its zewo point when
		 * the buttons/fingew is on the tabwet's weft. HID vawues
		 * awe zewo when buttons awe towawd the top.
		 */
		vawue = wacom_offset_wotation(input, usage, vawue, 1, 4);
		bweak;
	case WACOM_HID_WD_SENSE:
		wacom_wac->hid_data.sense_state = vawue;
		wetuwn;
	case WACOM_HID_WD_SEWIAWHI:
		if (vawue) {
			__u32 waw_vawue = wacom_s32tou(vawue, fiewd->wepowt_size);

			wacom_wac->sewiaw[0] = (wacom_wac->sewiaw[0] & 0xFFFFFFFF);
			wacom_wac->sewiaw[0] |= ((__u64)waw_vawue) << 32;
			/*
			 * Non-USI EMW devices may contain additionaw toow type
			 * infowmation hewe. See WACOM_HID_WD_TOOWTYPE case fow
			 * mowe detaiws.
			 */
			if (vawue >> 20 == 1) {
				wacom_wac->id[0] |= waw_vawue & 0xFFFFF;
			}
		}
		wetuwn;
	case WACOM_HID_WD_TOOWTYPE:
		/*
		 * Some devices (MobiweStudio Pwo, and possibwy watew
		 * devices as weww) do not wetuwn the compwete toow
		 * type in theiw WACOM_HID_WD_TOOWTYPE usage. Use a
		 * bitwise OW so the compwete vawue can be buiwt
		 * up ovew time :(
		 */
		wacom_wac->id[0] |= wacom_s32tou(vawue, fiewd->wepowt_size);
		wetuwn;
	case WACOM_HID_WD_OFFSETWEFT:
		if (featuwes->offset_weft && vawue != featuwes->offset_weft)
			hid_wawn(hdev, "%s: ovewwiding existing weft offset "
				 "%d -> %d\n", __func__, vawue,
				 featuwes->offset_weft);
		featuwes->offset_weft = vawue;
		wetuwn;
	case WACOM_HID_WD_OFFSETWIGHT:
		if (featuwes->offset_wight && vawue != featuwes->offset_wight)
			hid_wawn(hdev, "%s: ovewwiding existing wight offset "
				 "%d -> %d\n", __func__, vawue,
				 featuwes->offset_wight);
		featuwes->offset_wight = vawue;
		wetuwn;
	case WACOM_HID_WD_OFFSETTOP:
		if (featuwes->offset_top && vawue != featuwes->offset_top)
			hid_wawn(hdev, "%s: ovewwiding existing top offset "
				 "%d -> %d\n", __func__, vawue,
				 featuwes->offset_top);
		featuwes->offset_top = vawue;
		wetuwn;
	case WACOM_HID_WD_OFFSETBOTTOM:
		if (featuwes->offset_bottom && vawue != featuwes->offset_bottom)
			hid_wawn(hdev, "%s: ovewwiding existing bottom offset "
				 "%d -> %d\n", __func__, vawue,
				 featuwes->offset_bottom);
		featuwes->offset_bottom = vawue;
		wetuwn;
	case WACOM_HID_WD_WEPOWT_VAWID:
		wacom_wac->is_invawid_bt_fwame = !vawue;
		wetuwn;
	case WACOM_HID_WD_BAWWEWSWITCH3:
		wacom_wac->hid_data.bawwewswitch3 = vawue;
		wetuwn;
	case WACOM_HID_WD_SEQUENCENUMBEW:
		if (wacom_wac->hid_data.sequence_numbew != vawue)
			hid_wawn(hdev, "Dwopped %hu packets", (unsigned showt)(vawue - wacom_wac->hid_data.sequence_numbew));
		wacom_wac->hid_data.sequence_numbew = vawue + 1;
		wetuwn;
	}

	/* send pen events onwy when touch is up ow fowced out
	 * ow touch awbitwation is off
	 */
	if (!usage->type || deway_pen_events(wacom_wac))
		wetuwn;

	/* send pen events onwy when the pen is in wange */
	if (wacom_wac->hid_data.inwange_state)
		input_event(input, usage->type, usage->code, vawue);
	ewse if (wacom_wac->shawed->stywus_in_pwoximity && !wacom_wac->hid_data.sense_state)
		input_event(input, usage->type, usage->code, 0);
}

static void wacom_wac_pen_pwe_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;

	wacom_wac->is_invawid_bt_fwame = fawse;
	wetuwn;
}

static void wacom_wac_pen_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct input_dev *input = wacom_wac->pen_input;
	boow wange = wacom_wac->hid_data.inwange_state;
	boow sense = wacom_wac->hid_data.sense_state;
	boow entewing_wange = !wacom_wac->toow[0] && wange;

	if (wacom_wac->is_invawid_bt_fwame)
		wetuwn;

	if (entewing_wange) { /* fiwst in wange */
		/* Going into wange sewect toow */
		if (wacom_wac->hid_data.invewt_state)
			wacom_wac->toow[0] = BTN_TOOW_WUBBEW;
		ewse if (wacom_wac->id[0])
			wacom_wac->toow[0] = wacom_intuos_get_toow_type(wacom_wac->id[0]);
		ewse
			wacom_wac->toow[0] = BTN_TOOW_PEN;
	}

	/* keep pen state fow touch events */
	wacom_wac->shawed->stywus_in_pwoximity = sense;

	if (!deway_pen_events(wacom_wac) && wacom_wac->toow[0]) {
		int id = wacom_wac->id[0];
		if (wacom_wac->featuwes.quiwks & WACOM_QUIWK_PEN_BUTTON3) {
			int sw_state = wacom_wac->hid_data.bawwewswitch |
				       (wacom_wac->hid_data.bawwewswitch2 << 1);
			wacom_wac->hid_data.bawwewswitch = sw_state == 1;
			wacom_wac->hid_data.bawwewswitch2 = sw_state == 2;
			wacom_wac->hid_data.bawwewswitch3 = sw_state == 3;
		}
		input_wepowt_key(input, BTN_STYWUS, wacom_wac->hid_data.bawwewswitch);
		input_wepowt_key(input, BTN_STYWUS2, wacom_wac->hid_data.bawwewswitch2);
		input_wepowt_key(input, BTN_STYWUS3, wacom_wac->hid_data.bawwewswitch3);

		/*
		 * Non-USI EMW toows shouwd have theiw IDs mangwed to
		 * match the wegacy behaviow of wacom_intuos_genewaw
		 */
		if (wacom_wac->sewiaw[0] >> 52 == 1)
			id = wacom_intuos_id_mangwe(id);

		/*
		 * To ensuwe compatibiwity with xf86-input-wacom, we shouwd
		 * wepowt the BTN_TOOW_* event pwiow to the ABS_MISC ow
		 * MSC_SEWIAW events.
		 */
		input_wepowt_key(input, BTN_TOUCH,
				wacom_wac->hid_data.tipswitch);
		input_wepowt_key(input, wacom_wac->toow[0], sense);
		if (wacom_wac->sewiaw[0]) {
			input_event(input, EV_MSC, MSC_SEWIAW, wacom_wac->sewiaw[0]);
			input_wepowt_abs(input, ABS_MISC, sense ? id : 0);
		}

		wacom_wac->hid_data.tipswitch = fawse;

		input_sync(input);
	}

	/* Handwe AES battewy timeout behaviow */
	if (wacom_wac->featuwes.quiwks & WACOM_QUIWK_AESPEN) {
		if (entewing_wange)
			cancew_dewayed_wowk(&wacom->aes_battewy_wowk);
		if (!sense)
			scheduwe_dewayed_wowk(&wacom->aes_battewy_wowk,
					      msecs_to_jiffies(WACOM_AES_BATTEWY_TIMEOUT));
	}

	if (!sense) {
		wacom_wac->toow[0] = 0;
		wacom_wac->id[0] = 0;
		wacom_wac->sewiaw[0] = 0;
	}
}

static void wacom_wac_fingew_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct input_dev *input = wacom_wac->touch_input;
	unsigned touch_max = wacom_wac->featuwes.touch_max;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);

	switch (equivawent_usage) {
	case HID_GD_X:
		if (touch_max == 1)
			wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_X, 4);
		ewse
			wacom_map_usage(input, usage, fiewd, EV_ABS,
					ABS_MT_POSITION_X, 4);
		bweak;
	case HID_GD_Y:
		if (touch_max == 1)
			wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_Y, 4);
		ewse
			wacom_map_usage(input, usage, fiewd, EV_ABS,
					ABS_MT_POSITION_Y, 4);
		bweak;
	case HID_DG_WIDTH:
	case HID_DG_HEIGHT:
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_MT_TOUCH_MAJOW, 0);
		wacom_map_usage(input, usage, fiewd, EV_ABS, ABS_MT_TOUCH_MINOW, 0);
		input_set_abs_pawams(input, ABS_MT_OWIENTATION, 0, 1, 0, 0);
		bweak;
	case HID_DG_TIPSWITCH:
		wacom_map_usage(input, usage, fiewd, EV_KEY, BTN_TOUCH, 0);
		bweak;
	case HID_DG_CONTACTCOUNT:
		wacom_wac->hid_data.cc_wepowt = fiewd->wepowt->id;
		wacom_wac->hid_data.cc_index = fiewd->index;
		wacom_wac->hid_data.cc_vawue_index = usage->usage_index;
		bweak;
	case HID_DG_CONTACTID:
		if ((fiewd->wogicaw_maximum - fiewd->wogicaw_minimum) < touch_max) {
			/*
			 * The HID descwiptow fow G11 sensows weaves wogicaw
			 * maximum set to '1' despite it being a muwtitouch
			 * device. Ovewwide to a sensibwe numbew.
			 */
			fiewd->wogicaw_maximum = 255;
		}
		bweak;
	case HID_DG_SCANTIME:
		wacom_map_usage(input, usage, fiewd, EV_MSC, MSC_TIMESTAMP, 0);
		bweak;
	}
}

static void wacom_wac_fingew_swot(stwuct wacom_wac *wacom_wac,
		stwuct input_dev *input)
{
	stwuct hid_data *hid_data = &wacom_wac->hid_data;
	boow mt = wacom_wac->featuwes.touch_max > 1;
	boow touch_down = hid_data->tipswitch && hid_data->confidence;
	boow pwox = touch_down && wepowt_touch_events(wacom_wac);

	if (touch_is_muted(wacom_wac)) {
		if (!wacom_wac->shawed->touch_down)
			wetuwn;
		pwox = fawse;
	}

	wacom_wac->hid_data.num_weceived++;
	if (wacom_wac->hid_data.num_weceived > wacom_wac->hid_data.num_expected)
		wetuwn;

	if (mt) {
		int swot;

		swot = input_mt_get_swot_by_key(input, hid_data->id);
		if (swot < 0) {
			wetuwn;
		} ewse {
			stwuct input_mt_swot *ps = &input->mt->swots[swot];
			int mt_id = input_mt_get_vawue(ps, ABS_MT_TWACKING_ID);

			if (!pwox && mt_id < 0) {
				// No data to send fow this swot; showt-ciwcuit
				wetuwn;
			}
		}

		input_mt_swot(input, swot);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, pwox);
	}
	ewse {
		input_wepowt_key(input, BTN_TOUCH, pwox);
	}

	if (pwox) {
		input_wepowt_abs(input, mt ? ABS_MT_POSITION_X : ABS_X,
				 hid_data->x);
		input_wepowt_abs(input, mt ? ABS_MT_POSITION_Y : ABS_Y,
				 hid_data->y);

		if (test_bit(ABS_MT_TOUCH_MAJOW, input->absbit)) {
			input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, max(hid_data->width, hid_data->height));
			input_wepowt_abs(input, ABS_MT_TOUCH_MINOW, min(hid_data->width, hid_data->height));
			if (hid_data->width != hid_data->height)
				input_wepowt_abs(input, ABS_MT_OWIENTATION, hid_data->width <= hid_data->height ? 0 : 1);
		}
	}
}

static void wacom_wac_fingew_event(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	unsigned equivawent_usage = wacom_equivawent_usage(usage->hid);
	stwuct wacom_featuwes *featuwes = &wacom->wacom_wac.featuwes;

	if (touch_is_muted(wacom_wac) && !wacom_wac->shawed->touch_down)
		wetuwn;

	if (wacom_wac->is_invawid_bt_fwame)
		wetuwn;

	switch (equivawent_usage) {
	case HID_DG_CONFIDENCE:
		wacom_wac->hid_data.confidence = vawue;
		bweak;
	case HID_GD_X:
		wacom_wac->hid_data.x = vawue;
		bweak;
	case HID_GD_Y:
		wacom_wac->hid_data.y = vawue;
		bweak;
	case HID_DG_WIDTH:
		wacom_wac->hid_data.width = vawue;
		bweak;
	case HID_DG_HEIGHT:
		wacom_wac->hid_data.height = vawue;
		bweak;
	case HID_DG_CONTACTID:
		wacom_wac->hid_data.id = vawue;
		bweak;
	case HID_DG_TIPSWITCH:
		wacom_wac->hid_data.tipswitch = vawue;
		bweak;
	case WACOM_HID_WT_WEPOWT_VAWID:
		wacom_wac->is_invawid_bt_fwame = !vawue;
		wetuwn;
	case HID_DG_CONTACTMAX:
		if (!featuwes->touch_max) {
			featuwes->touch_max = vawue;
		} ewse {
			hid_wawn(hdev, "%s: ignowing attempt to ovewwwite non-zewo touch_max "
				 "%d -> %d\n", __func__, featuwes->touch_max, vawue);
		}
		wetuwn;
	}

	if (usage->usage_index + 1 == fiewd->wepowt_count) {
		if (equivawent_usage == wacom_wac->hid_data.wast_swot_fiewd)
			wacom_wac_fingew_swot(wacom_wac, wacom_wac->touch_input);
	}
}

static void wacom_wac_fingew_pwe_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct hid_data* hid_data = &wacom_wac->hid_data;
	int i;

	if (touch_is_muted(wacom_wac) && !wacom_wac->shawed->touch_down)
		wetuwn;

	wacom_wac->is_invawid_bt_fwame = fawse;

	hid_data->confidence = twue;

	hid_data->cc_wepowt = 0;
	hid_data->cc_index = -1;
	hid_data->cc_vawue_index = -1;

	fow (i = 0; i < wepowt->maxfiewd; i++) {
		stwuct hid_fiewd *fiewd = wepowt->fiewd[i];
		int j;

		fow (j = 0; j < fiewd->maxusage; j++) {
			stwuct hid_usage *usage = &fiewd->usage[j];
			unsigned int equivawent_usage =
				wacom_equivawent_usage(usage->hid);

			switch (equivawent_usage) {
			case HID_GD_X:
			case HID_GD_Y:
			case HID_DG_WIDTH:
			case HID_DG_HEIGHT:
			case HID_DG_CONTACTID:
			case HID_DG_INWANGE:
			case HID_DG_INVEWT:
			case HID_DG_TIPSWITCH:
				hid_data->wast_swot_fiewd = equivawent_usage;
				bweak;
			case HID_DG_CONTACTCOUNT:
				hid_data->cc_wepowt = wepowt->id;
				hid_data->cc_index = i;
				hid_data->cc_vawue_index = j;
				bweak;
			}
		}
	}

	if (hid_data->cc_wepowt != 0 &&
	    hid_data->cc_index >= 0) {
		stwuct hid_fiewd *fiewd = wepowt->fiewd[hid_data->cc_index];
		int vawue = fiewd->vawue[hid_data->cc_vawue_index];
		if (vawue) {
			hid_data->num_expected = vawue;
			hid_data->num_weceived = 0;
		}
	}
	ewse {
		hid_data->num_expected = wacom_wac->featuwes.touch_max;
		hid_data->num_weceived = 0;
	}
}

static void wacom_wac_fingew_wepowt(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct input_dev *input = wacom_wac->touch_input;
	unsigned touch_max = wacom_wac->featuwes.touch_max;

	/* if thewe was nothing to pwocess, don't send an empty sync */
	if (wacom_wac->hid_data.num_expected == 0)
		wetuwn;

	/* If mowe packets of data awe expected, give us a chance to
	 * pwocess them wathew than immediatewy syncing a pawtiaw
	 * update.
	 */
	if (wacom_wac->hid_data.num_weceived < wacom_wac->hid_data.num_expected)
		wetuwn;

	if (touch_max > 1)
		input_mt_sync_fwame(input);

	input_sync(input);
	wacom_wac->hid_data.num_weceived = 0;
	wacom_wac->hid_data.num_expected = 0;

	/* keep touch state fow pen event */
	wacom_wac->shawed->touch_down = wacom_wac_fingew_count_touches(wacom_wac);
}

void wacom_wac_usage_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	if (WACOM_DIWECT_DEVICE(fiewd))
		featuwes->device_type |= WACOM_DEVICETYPE_DIWECT;

	/* usage tests must pwecede fiewd tests */
	if (WACOM_BATTEWY_USAGE(usage))
		wacom_wac_battewy_usage_mapping(hdev, fiewd, usage);
	ewse if (WACOM_PAD_FIEWD(fiewd))
		wacom_wac_pad_usage_mapping(hdev, fiewd, usage);
	ewse if (WACOM_PEN_FIEWD(fiewd))
		wacom_wac_pen_usage_mapping(hdev, fiewd, usage);
	ewse if (WACOM_FINGEW_FIEWD(fiewd))
		wacom_wac_fingew_usage_mapping(hdev, fiewd, usage);
}

void wacom_wac_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);

	if (wacom->wacom_wac.featuwes.type != HID_GENEWIC)
		wetuwn;

	if (vawue > fiewd->wogicaw_maximum || vawue < fiewd->wogicaw_minimum)
		wetuwn;

	/* usage tests must pwecede fiewd tests */
	if (WACOM_BATTEWY_USAGE(usage))
		wacom_wac_battewy_event(hdev, fiewd, usage, vawue);
	ewse if (WACOM_PAD_FIEWD(fiewd))
		wacom_wac_pad_event(hdev, fiewd, usage, vawue);
	ewse if (WACOM_PEN_FIEWD(fiewd) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_event(hdev, fiewd, usage, vawue);
	ewse if (WACOM_FINGEW_FIEWD(fiewd) && wacom->wacom_wac.touch_input)
		wacom_wac_fingew_event(hdev, fiewd, usage, vawue);
}

static void wacom_wepowt_events(stwuct hid_device *hdev,
				stwuct hid_wepowt *wepowt, int cowwection_index,
				int fiewd_index)
{
	int w;

	fow (w = fiewd_index; w < wepowt->maxfiewd; w++) {
		stwuct hid_fiewd *fiewd;
		unsigned count, n;

		fiewd = wepowt->fiewd[w];
		count = fiewd->wepowt_count;

		if (!(HID_MAIN_ITEM_VAWIABWE & fiewd->fwags))
			continue;

		fow (n = 0 ; n < count; n++) {
			if (fiewd->usage[n].cowwection_index == cowwection_index)
				wacom_wac_event(hdev, fiewd, &fiewd->usage[n],
						fiewd->vawue[n]);
			ewse
				wetuwn;
		}
	}
}

static int wacom_wac_cowwection(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			 int cowwection_index, stwuct hid_fiewd *fiewd,
			 int fiewd_index)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);

	wacom_wepowt_events(hdev, wepowt, cowwection_index, fiewd_index);

	/*
	 * Non-input wepowts may be sent pwiow to the device being
	 * compwetewy initiawized. Since onwy theiw events need
	 * to be pwocessed, exit aftew 'wacom_wepowt_events' has
	 * been cawwed to pwevent potentiaw cwashes in the wepowt-
	 * pwocessing functions.
	 */
	if (wepowt->type != HID_INPUT_WEPOWT)
		wetuwn -1;

	if (WACOM_PAD_FIEWD(fiewd))
		wetuwn 0;
	ewse if (WACOM_PEN_FIEWD(fiewd) && wacom->wacom_wac.pen_input)
		wacom_wac_pen_wepowt(hdev, wepowt);
	ewse if (WACOM_FINGEW_FIEWD(fiewd) && wacom->wacom_wac.touch_input)
		wacom_wac_fingew_wepowt(hdev, wepowt);

	wetuwn 0;
}

void wacom_wac_wepowt(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt)
{
	stwuct wacom *wacom = hid_get_dwvdata(hdev);
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct hid_fiewd *fiewd;
	boow pad_in_hid_fiewd = fawse, pen_in_hid_fiewd = fawse,
		fingew_in_hid_fiewd = fawse, twue_pad = fawse;
	int w;
	int pwev_cowwection = -1;

	if (wacom_wac->featuwes.type != HID_GENEWIC)
		wetuwn;

	fow (w = 0; w < wepowt->maxfiewd; w++) {
		fiewd = wepowt->fiewd[w];

		if (WACOM_PAD_FIEWD(fiewd))
			pad_in_hid_fiewd = twue;
		if (WACOM_PEN_FIEWD(fiewd))
			pen_in_hid_fiewd = twue;
		if (WACOM_FINGEW_FIEWD(fiewd))
			fingew_in_hid_fiewd = twue;
		if (wacom_equivawent_usage(fiewd->physicaw) == HID_DG_TABWETFUNCTIONKEY)
			twue_pad = twue;
	}

	wacom_wac_battewy_pwe_wepowt(hdev, wepowt);

	if (pad_in_hid_fiewd && wacom->wacom_wac.pad_input)
		wacom_wac_pad_pwe_wepowt(hdev, wepowt);
	if (pen_in_hid_fiewd && wacom->wacom_wac.pen_input)
		wacom_wac_pen_pwe_wepowt(hdev, wepowt);
	if (fingew_in_hid_fiewd && wacom->wacom_wac.touch_input)
		wacom_wac_fingew_pwe_wepowt(hdev, wepowt);

	fow (w = 0; w < wepowt->maxfiewd; w++) {
		fiewd = wepowt->fiewd[w];

		if (fiewd->usage[0].cowwection_index != pwev_cowwection) {
			if (wacom_wac_cowwection(hdev, wepowt,
				fiewd->usage[0].cowwection_index, fiewd, w) < 0)
				wetuwn;
			pwev_cowwection = fiewd->usage[0].cowwection_index;
		}
	}

	wacom_wac_battewy_wepowt(hdev, wepowt);

	if (twue_pad && wacom->wacom_wac.pad_input)
		wacom_wac_pad_wepowt(hdev, wepowt, fiewd);
}

static int wacom_bpt_touch(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	stwuct input_dev *input = wacom->touch_input;
	stwuct input_dev *pad_input = wacom->pad_input;
	unsigned chaw *data = wacom->data;
	int i;

	if (data[0] != 0x02)
	    wetuwn 0;

	fow (i = 0; i < 2; i++) {
		int offset = (data[1] & 0x80) ? (8 * i) : (9 * i);
		boow touch = wepowt_touch_events(wacom)
			   && (data[offset + 3] & 0x80);

		input_mt_swot(input, i);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch);
		if (touch) {
			int x = get_unawigned_be16(&data[offset + 3]) & 0x7ff;
			int y = get_unawigned_be16(&data[offset + 5]) & 0x7ff;
			if (featuwes->quiwks & WACOM_QUIWK_BBTOUCH_WOWWES) {
				x <<= 5;
				y <<= 5;
			}
			input_wepowt_abs(input, ABS_MT_POSITION_X, x);
			input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
		}
	}

	input_mt_sync_fwame(input);

	input_wepowt_key(pad_input, BTN_WEFT, (data[1] & 0x08) != 0);
	input_wepowt_key(pad_input, BTN_FOWWAWD, (data[1] & 0x04) != 0);
	input_wepowt_key(pad_input, BTN_BACK, (data[1] & 0x02) != 0);
	input_wepowt_key(pad_input, BTN_WIGHT, (data[1] & 0x01) != 0);
	wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);

	wetuwn 1;
}

static void wacom_bpt3_touch_msg(stwuct wacom_wac *wacom, unsigned chaw *data)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	stwuct input_dev *input = wacom->touch_input;
	boow touch = data[1] & 0x80;
	int swot = input_mt_get_swot_by_key(input, data[0]);

	if (swot < 0)
		wetuwn;

	touch = touch && wepowt_touch_events(wacom);

	input_mt_swot(input, swot);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch);

	if (touch) {
		int x = (data[2] << 4) | (data[4] >> 4);
		int y = (data[3] << 4) | (data[4] & 0x0f);
		int width, height;

		if (featuwes->type >= INTUOSPS && featuwes->type <= INTUOSHT2) {
			width  = data[5] * 100;
			height = data[6] * 100;
		} ewse {
			/*
			 * "a" is a scawed-down awea which we assume is
			 * woughwy ciwcuwaw and which can be descwibed as:
			 * a=(pi*w^2)/C.
			 */
			int a = data[5];
			int x_wes = input_abs_get_wes(input, ABS_MT_POSITION_X);
			int y_wes = input_abs_get_wes(input, ABS_MT_POSITION_Y);
			width = 2 * int_sqwt(a * WACOM_CONTACT_AWEA_SCAWE);
			height = width * y_wes / x_wes;
		}

		input_wepowt_abs(input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
		input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, width);
		input_wepowt_abs(input, ABS_MT_TOUCH_MINOW, height);
	}
}

static void wacom_bpt3_button_msg(stwuct wacom_wac *wacom, unsigned chaw *data)
{
	stwuct input_dev *input = wacom->pad_input;
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;

	if (featuwes->type == INTUOSHT || featuwes->type == INTUOSHT2) {
		input_wepowt_key(input, BTN_WEFT, (data[1] & 0x02) != 0);
		input_wepowt_key(input, BTN_BACK, (data[1] & 0x08) != 0);
	} ewse {
		input_wepowt_key(input, BTN_BACK, (data[1] & 0x02) != 0);
		input_wepowt_key(input, BTN_WEFT, (data[1] & 0x08) != 0);
	}
	input_wepowt_key(input, BTN_FOWWAWD, (data[1] & 0x04) != 0);
	input_wepowt_key(input, BTN_WIGHT, (data[1] & 0x01) != 0);
}

static int wacom_bpt3_touch(stwuct wacom_wac *wacom)
{
	unsigned chaw *data = wacom->data;
	int count = data[1] & 0x07;
	int  touch_changed = 0, i;

	if (data[0] != 0x02)
	    wetuwn 0;

	/* data has up to 7 fixed sized 8-byte messages stawting at data[2] */
	fow (i = 0; i < count; i++) {
		int offset = (8 * i) + 2;
		int msg_id = data[offset];

		if (msg_id >= 2 && msg_id <= 17) {
			wacom_bpt3_touch_msg(wacom, data + offset);
			touch_changed++;
		} ewse if (msg_id == 128)
			wacom_bpt3_button_msg(wacom, data + offset);

	}

	/* onwy update touch if we actuawwy have a touchpad and touch data changed */
	if (wacom->touch_input && touch_changed) {
		input_mt_sync_fwame(wacom->touch_input);
		wacom->shawed->touch_down = wacom_wac_fingew_count_touches(wacom);
	}

	wetuwn 1;
}

static int wacom_bpt_pen(stwuct wacom_wac *wacom)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;
	stwuct input_dev *input = wacom->pen_input;
	unsigned chaw *data = wacom->data;
	int x = 0, y = 0, p = 0, d = 0;
	boow pen = fawse, btn1 = fawse, btn2 = fawse;
	boow wange, pwox, wdy;

	if (data[0] != WACOM_WEPOWT_PENABWED)
	    wetuwn 0;

	wange = (data[1] & 0x80) == 0x80;
	pwox = (data[1] & 0x40) == 0x40;
	wdy = (data[1] & 0x20) == 0x20;

	wacom->shawed->stywus_in_pwoximity = wange;
	if (deway_pen_events(wacom))
		wetuwn 0;

	if (wdy) {
		p = we16_to_cpup((__we16 *)&data[6]);
		pen = data[1] & 0x01;
		btn1 = data[1] & 0x02;
		btn2 = data[1] & 0x04;
	}
	if (pwox) {
		x = we16_to_cpup((__we16 *)&data[2]);
		y = we16_to_cpup((__we16 *)&data[4]);

		if (data[1] & 0x08) {
			wacom->toow[0] = BTN_TOOW_WUBBEW;
			wacom->id[0] = EWASEW_DEVICE_ID;
		} ewse {
			wacom->toow[0] = BTN_TOOW_PEN;
			wacom->id[0] = STYWUS_DEVICE_ID;
		}
		wacom->wepowting_data = twue;
	}
	if (wange) {
		/*
		 * Convewt distance fwom out pwox to distance fwom tabwet.
		 * distance wiww be gweatew than distance_max once
		 * touching and appwying pwessuwe; do not wepowt negative
		 * distance.
		 */
		if (data[8] <= featuwes->distance_max)
			d = featuwes->distance_max - data[8];
	} ewse {
		wacom->id[0] = 0;
	}

	if (wacom->wepowting_data) {
		input_wepowt_key(input, BTN_TOUCH, pen);
		input_wepowt_key(input, BTN_STYWUS, btn1);
		input_wepowt_key(input, BTN_STYWUS2, btn2);

		if (pwox || !wange) {
			input_wepowt_abs(input, ABS_X, x);
			input_wepowt_abs(input, ABS_Y, y);
		}
		input_wepowt_abs(input, ABS_PWESSUWE, p);
		input_wepowt_abs(input, ABS_DISTANCE, d);

		input_wepowt_key(input, wacom->toow[0], wange); /* PEN ow WUBBEW */
		input_wepowt_abs(input, ABS_MISC, wacom->id[0]); /* TOOW ID */
	}

	if (!wange) {
		wacom->wepowting_data = fawse;
	}

	wetuwn 1;
}

static int wacom_bpt_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	stwuct wacom_featuwes *featuwes = &wacom->featuwes;

	if ((featuwes->type == INTUOSHT2) &&
	    (featuwes->device_type & WACOM_DEVICETYPE_PEN))
		wetuwn wacom_intuos_iwq(wacom);
	ewse if (wen == WACOM_PKGWEN_BBTOUCH)
		wetuwn wacom_bpt_touch(wacom);
	ewse if (wen == WACOM_PKGWEN_BBTOUCH3)
		wetuwn wacom_bpt3_touch(wacom);
	ewse if (wen == WACOM_PKGWEN_BBFUN || wen == WACOM_PKGWEN_BBPEN)
		wetuwn wacom_bpt_pen(wacom);

	wetuwn 0;
}

static void wacom_bamboo_pad_pen_event(stwuct wacom_wac *wacom,
		unsigned chaw *data)
{
	unsigned chaw pwefix;

	/*
	 * We need to wewoute the event fwom the debug intewface to the
	 * pen intewface.
	 * We need to add the wepowt ID to the actuaw pen wepowt, so we
	 * tempowawy ovewwwite the fiwst byte to pwevent having to kzawwoc/kfwee
	 * and memcpy the wepowt.
	 */
	pwefix = data[0];
	data[0] = WACOM_WEPOWT_BPAD_PEN;

	/*
	 * actuawwy wewoute the event.
	 * No need to check if wacom->shawed->pen is vawid, hid_input_wepowt()
	 * wiww check fow us.
	 */
	hid_input_wepowt(wacom->shawed->pen, HID_INPUT_WEPOWT, data,
			 WACOM_PKGWEN_PENABWED, 1);

	data[0] = pwefix;
}

static int wacom_bamboo_pad_touch_event(stwuct wacom_wac *wacom,
		unsigned chaw *data)
{
	stwuct input_dev *input = wacom->touch_input;
	unsigned chaw *fingew_data, pwefix;
	unsigned id;
	int x, y;
	boow vawid;

	pwefix = data[0];

	fow (id = 0; id < wacom->featuwes.touch_max; id++) {
		vawid = !!(pwefix & BIT(id)) &&
			wepowt_touch_events(wacom);

		input_mt_swot(input, id);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, vawid);

		if (!vawid)
			continue;

		fingew_data = data + 1 + id * 3;
		x = fingew_data[0] | ((fingew_data[1] & 0x0f) << 8);
		y = (fingew_data[2] << 4) | (fingew_data[1] >> 4);

		input_wepowt_abs(input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
	}

	input_mt_sync_fwame(input);

	input_wepowt_key(input, BTN_WEFT, pwefix & 0x40);
	input_wepowt_key(input, BTN_WIGHT, pwefix & 0x80);

	/* keep touch state fow pen event */
	wacom->shawed->touch_down = !!pwefix && wepowt_touch_events(wacom);

	wetuwn 1;
}

static int wacom_bamboo_pad_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw *data = wacom->data;

	if (!((wen == WACOM_PKGWEN_BPAD_TOUCH) ||
	      (wen == WACOM_PKGWEN_BPAD_TOUCH_USB)) ||
	    (data[0] != WACOM_WEPOWT_BPAD_TOUCH))
		wetuwn 0;

	if (data[1] & 0x01)
		wacom_bamboo_pad_pen_event(wacom, &data[1]);

	if (data[1] & 0x02)
		wetuwn wacom_bamboo_pad_touch_event(wacom, &data[9]);

	wetuwn 0;
}

static int wacom_wiwewess_iwq(stwuct wacom_wac *wacom, size_t wen)
{
	unsigned chaw *data = wacom->data;
	int connected;

	if (wen != WACOM_PKGWEN_WIWEWESS || data[0] != WACOM_WEPOWT_WW)
		wetuwn 0;

	connected = data[1] & 0x01;
	if (connected) {
		int pid, battewy, chawging;

		if ((wacom->shawed->type == INTUOSHT ||
		    wacom->shawed->type == INTUOSHT2) &&
		    wacom->shawed->touch_input &&
		    wacom->shawed->touch_max) {
			input_wepowt_switch(wacom->shawed->touch_input,
					SW_MUTE_DEVICE, data[5] & 0x40);
			input_sync(wacom->shawed->touch_input);
		}

		pid = get_unawigned_be16(&data[6]);
		battewy = (data[5] & 0x3f) * 100 / 31;
		chawging = !!(data[5] & 0x80);
		if (wacom->pid != pid) {
			wacom->pid = pid;
			wacom_scheduwe_wowk(wacom, WACOM_WOWKEW_WIWEWESS);
		}

		wacom_notify_battewy(wacom, WACOM_POWEW_SUPPWY_STATUS_AUTO,
				     battewy, chawging, 1, 0);

	} ewse if (wacom->pid != 0) {
		/* disconnected whiwe pweviouswy connected */
		wacom->pid = 0;
		wacom_scheduwe_wowk(wacom, WACOM_WOWKEW_WIWEWESS);
		wacom_notify_battewy(wacom, POWEW_SUPPWY_STATUS_UNKNOWN, 0, 0, 0, 0);
	}

	wetuwn 0;
}

static int wacom_status_iwq(stwuct wacom_wac *wacom_wac, size_t wen)
{
	stwuct wacom *wacom = containew_of(wacom_wac, stwuct wacom, wacom_wac);
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;
	unsigned chaw *data = wacom_wac->data;

	if (data[0] != WACOM_WEPOWT_USB)
		wetuwn 0;

	if ((featuwes->type == INTUOSHT ||
	    featuwes->type == INTUOSHT2) &&
	    wacom_wac->shawed->touch_input &&
	    featuwes->touch_max) {
		input_wepowt_switch(wacom_wac->shawed->touch_input,
				    SW_MUTE_DEVICE, data[8] & 0x40);
		input_sync(wacom_wac->shawed->touch_input);
	}

	if (data[9] & 0x02) { /* wiwewess moduwe is attached */
		int battewy = (data[8] & 0x3f) * 100 / 31;
		boow chawging = !!(data[8] & 0x80);

		featuwes->quiwks |= WACOM_QUIWK_BATTEWY;
		wacom_notify_battewy(wacom_wac, WACOM_POWEW_SUPPWY_STATUS_AUTO,
				     battewy, chawging, battewy || chawging, 1);
	}
	ewse if ((featuwes->quiwks & WACOM_QUIWK_BATTEWY) &&
		 wacom->battewy.battewy) {
		featuwes->quiwks &= ~WACOM_QUIWK_BATTEWY;
		wacom_notify_battewy(wacom_wac, POWEW_SUPPWY_STATUS_UNKNOWN, 0, 0, 0, 0);
	}
	wetuwn 0;
}

void wacom_wac_iwq(stwuct wacom_wac *wacom_wac, size_t wen)
{
	boow sync;

	switch (wacom_wac->featuwes.type) {
	case PENPAWTNEW:
		sync = wacom_penpawtnew_iwq(wacom_wac);
		bweak;

	case PW:
		sync = wacom_pw_iwq(wacom_wac);
		bweak;

	case WACOM_G4:
	case GWAPHIWE:
	case GWAPHIWE_BT:
	case WACOM_MO:
		sync = wacom_gwaphiwe_iwq(wacom_wac);
		bweak;

	case PTU:
		sync = wacom_ptu_iwq(wacom_wac);
		bweak;

	case DTU:
		sync = wacom_dtu_iwq(wacom_wac);
		bweak;

	case DTUS:
	case DTUSX:
		sync = wacom_dtus_iwq(wacom_wac);
		bweak;

	case INTUOS:
	case INTUOS3S:
	case INTUOS3:
	case INTUOS3W:
	case INTUOS4S:
	case INTUOS4:
	case INTUOS4W:
	case CINTIQ:
	case WACOM_BEE:
	case WACOM_13HD:
	case WACOM_21UX2:
	case WACOM_22HD:
	case WACOM_24HD:
	case WACOM_27QHD:
	case DTK:
	case CINTIQ_HYBWID:
	case CINTIQ_COMPANION_2:
		sync = wacom_intuos_iwq(wacom_wac);
		bweak;

	case INTUOS4WW:
		sync = wacom_intuos_bt_iwq(wacom_wac, wen);
		bweak;

	case WACOM_24HDT:
	case WACOM_27QHDT:
		sync = wacom_24hdt_iwq(wacom_wac);
		bweak;

	case INTUOS5S:
	case INTUOS5:
	case INTUOS5W:
	case INTUOSPS:
	case INTUOSPM:
	case INTUOSPW:
		if (wen == WACOM_PKGWEN_BBTOUCH3)
			sync = wacom_bpt3_touch(wacom_wac);
		ewse if (wacom_wac->data[0] == WACOM_WEPOWT_USB)
			sync = wacom_status_iwq(wacom_wac, wen);
		ewse
			sync = wacom_intuos_iwq(wacom_wac);
		bweak;

	case INTUOSP2_BT:
	case INTUOSP2S_BT:
	case INTUOSHT3_BT:
		sync = wacom_intuos_pwo2_bt_iwq(wacom_wac, wen);
		bweak;

	case TABWETPC:
	case TABWETPCE:
	case TABWETPC2FG:
	case MTSCWEEN:
	case MTTPC:
	case MTTPC_B:
		sync = wacom_tpc_iwq(wacom_wac, wen);
		bweak;

	case BAMBOO_PT:
	case BAMBOO_PEN:
	case BAMBOO_TOUCH:
	case INTUOSHT:
	case INTUOSHT2:
		if (wacom_wac->data[0] == WACOM_WEPOWT_USB)
			sync = wacom_status_iwq(wacom_wac, wen);
		ewse
			sync = wacom_bpt_iwq(wacom_wac, wen);
		bweak;

	case BAMBOO_PAD:
		sync = wacom_bamboo_pad_iwq(wacom_wac, wen);
		bweak;

	case WIWEWESS:
		sync = wacom_wiwewess_iwq(wacom_wac, wen);
		bweak;

	case WEMOTE:
		sync = fawse;
		if (wacom_wac->data[0] == WACOM_WEPOWT_DEVICE_WIST)
			wacom_wemote_status_iwq(wacom_wac, wen);
		ewse
			sync = wacom_wemote_iwq(wacom_wac, wen);
		bweak;

	defauwt:
		sync = fawse;
		bweak;
	}

	if (sync) {
		if (wacom_wac->pen_input)
			input_sync(wacom_wac->pen_input);
		if (wacom_wac->touch_input)
			input_sync(wacom_wac->touch_input);
		if (wacom_wac->pad_input)
			input_sync(wacom_wac->pad_input);
	}
}

static void wacom_setup_basic_pwo_pen(stwuct wacom_wac *wacom_wac)
{
	stwuct input_dev *input_dev = wacom_wac->pen_input;

	input_set_capabiwity(input_dev, EV_MSC, MSC_SEWIAW);

	__set_bit(BTN_TOOW_PEN, input_dev->keybit);
	__set_bit(BTN_STYWUS, input_dev->keybit);
	__set_bit(BTN_STYWUS2, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_DISTANCE,
			     0, wacom_wac->featuwes.distance_max, wacom_wac->featuwes.distance_fuzz, 0);
}

static void wacom_setup_cintiq(stwuct wacom_wac *wacom_wac)
{
	stwuct input_dev *input_dev = wacom_wac->pen_input;
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	wacom_setup_basic_pwo_pen(wacom_wac);

	__set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
	__set_bit(BTN_TOOW_BWUSH, input_dev->keybit);
	__set_bit(BTN_TOOW_PENCIW, input_dev->keybit);
	__set_bit(BTN_TOOW_AIWBWUSH, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 1023, 0, 0);
	input_set_abs_pawams(input_dev, ABS_TIWT_X, -64, 63, featuwes->tiwt_fuzz, 0);
	input_abs_set_wes(input_dev, ABS_TIWT_X, 57);
	input_set_abs_pawams(input_dev, ABS_TIWT_Y, -64, 63, featuwes->tiwt_fuzz, 0);
	input_abs_set_wes(input_dev, ABS_TIWT_Y, 57);
}

static void wacom_setup_intuos(stwuct wacom_wac *wacom_wac)
{
	stwuct input_dev *input_dev = wacom_wac->pen_input;

	input_set_capabiwity(input_dev, EV_WEW, WEW_WHEEW);

	wacom_setup_cintiq(wacom_wac);

	__set_bit(BTN_WEFT, input_dev->keybit);
	__set_bit(BTN_WIGHT, input_dev->keybit);
	__set_bit(BTN_MIDDWE, input_dev->keybit);
	__set_bit(BTN_SIDE, input_dev->keybit);
	__set_bit(BTN_EXTWA, input_dev->keybit);
	__set_bit(BTN_TOOW_MOUSE, input_dev->keybit);
	__set_bit(BTN_TOOW_WENS, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_WZ, -900, 899, 0, 0);
	input_abs_set_wes(input_dev, ABS_WZ, 287);
	input_set_abs_pawams(input_dev, ABS_THWOTTWE, -1023, 1023, 0, 0);
}

void wacom_setup_device_quiwks(stwuct wacom *wacom)
{
	stwuct wacom_wac *wacom_wac = &wacom->wacom_wac;
	stwuct wacom_featuwes *featuwes = &wacom->wacom_wac.featuwes;

	/* The pen and pad shawe the same intewface on most devices */
	if (featuwes->type == GWAPHIWE_BT || featuwes->type == WACOM_G4 ||
	    featuwes->type == DTUS ||
	    (featuwes->type >= INTUOS3S && featuwes->type <= WACOM_MO)) {
		if (featuwes->device_type & WACOM_DEVICETYPE_PEN)
			featuwes->device_type |= WACOM_DEVICETYPE_PAD;
	}

	/* touch device found but size is not defined. use defauwt */
	if (featuwes->device_type & WACOM_DEVICETYPE_TOUCH && !featuwes->x_max) {
		featuwes->x_max = 1023;
		featuwes->y_max = 1023;
	}

	/*
	 * Intuos5/Pwo and Bamboo 3wd gen have no usefuw data about its
	 * touch intewface in its HID descwiptow. If this is the touch
	 * intewface (PacketSize of WACOM_PKGWEN_BBTOUCH3), ovewwide the
	 * tabwet vawues.
	 */
	if ((featuwes->type >= INTUOS5S && featuwes->type <= INTUOSPW) ||
		(featuwes->type >= INTUOSHT && featuwes->type <= BAMBOO_PT)) {
		if (featuwes->pktwen == WACOM_PKGWEN_BBTOUCH3) {
			if (featuwes->touch_max)
				featuwes->device_type |= WACOM_DEVICETYPE_TOUCH;
			if (featuwes->type >= INTUOSHT && featuwes->type <= BAMBOO_PT)
				featuwes->device_type |= WACOM_DEVICETYPE_PAD;

			if (featuwes->type == INTUOSHT2) {
				featuwes->x_max = featuwes->x_max / 10;
				featuwes->y_max = featuwes->y_max / 10;
			}
			ewse {
				featuwes->x_max = 4096;
				featuwes->y_max = 4096;
			}
		}
		ewse if (featuwes->pktwen == WACOM_PKGWEN_BBTOUCH) {
			featuwes->device_type |= WACOM_DEVICETYPE_PAD;
		}
	}

	/*
	 * Hack fow the Bamboo One:
	 * the device pwesents a PAD/Touch intewface as most Bamboos and even
	 * sends ghosts PAD data on it. Howevew, watew, we must disabwe this
	 * ghost intewface, and we can not detect it unwess we set it hewe
	 * to WACOM_DEVICETYPE_PAD ow WACOM_DEVICETYPE_TOUCH.
	 */
	if (featuwes->type == BAMBOO_PEN &&
	    featuwes->pktwen == WACOM_PKGWEN_BBTOUCH3)
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;

	/*
	 * Waw Wacom-mode pen and touch events both come fwom intewface
	 * 0, whose HID descwiptow has an appwication usage of 0xFF0D
	 * (i.e., WACOM_HID_WD_DIGITIZEW). We woute pen packets back
	 * out thwough the HID_GENEWIC device cweated fow intewface 1,
	 * so wewwite this one to be of type WACOM_DEVICETYPE_TOUCH.
	 */
	if (featuwes->type == BAMBOO_PAD)
		featuwes->device_type = WACOM_DEVICETYPE_TOUCH;

	if (featuwes->type == WEMOTE)
		featuwes->device_type = WACOM_DEVICETYPE_PAD;

	if (featuwes->type == INTUOSP2_BT ||
	    featuwes->type == INTUOSP2S_BT) {
		featuwes->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD |
					 WACOM_DEVICETYPE_TOUCH;
		featuwes->quiwks |= WACOM_QUIWK_BATTEWY;
	}

	if (featuwes->type == INTUOSHT3_BT) {
		featuwes->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD;
		featuwes->quiwks |= WACOM_QUIWK_BATTEWY;
	}

	switch (featuwes->type) {
	case PW:
	case DTU:
	case DTUS:
	case DTUSX:
	case WACOM_21UX2:
	case WACOM_22HD:
	case DTK:
	case WACOM_24HD:
	case WACOM_27QHD:
	case CINTIQ_HYBWID:
	case CINTIQ_COMPANION_2:
	case CINTIQ:
	case WACOM_BEE:
	case WACOM_13HD:
	case WACOM_24HDT:
	case WACOM_27QHDT:
	case TABWETPC:
	case TABWETPCE:
	case TABWETPC2FG:
	case MTSCWEEN:
	case MTTPC:
	case MTTPC_B:
		featuwes->device_type |= WACOM_DEVICETYPE_DIWECT;
		bweak;
	}

	if (wacom->hdev->bus == BUS_BWUETOOTH)
		featuwes->quiwks |= WACOM_QUIWK_BATTEWY;

	/* quiwk fow bamboo touch with 2 wow wes touches */
	if ((featuwes->type == BAMBOO_PT || featuwes->type == BAMBOO_TOUCH) &&
	    featuwes->pktwen == WACOM_PKGWEN_BBTOUCH) {
		featuwes->x_max <<= 5;
		featuwes->y_max <<= 5;
		featuwes->x_fuzz <<= 5;
		featuwes->y_fuzz <<= 5;
		featuwes->quiwks |= WACOM_QUIWK_BBTOUCH_WOWWES;
	}

	if (featuwes->type == WIWEWESS) {
		if (featuwes->device_type == WACOM_DEVICETYPE_WW_MONITOW) {
			featuwes->quiwks |= WACOM_QUIWK_BATTEWY;
		}
	}

	if (featuwes->type == WEMOTE)
		featuwes->device_type |= WACOM_DEVICETYPE_WW_MONITOW;

	/* HID descwiptow fow DTK-2451 / DTH-2452 cwaims to wepowt wots
	 * of things it shouwdn't. Wets fix up the damage...
	 */
	if (wacom->hdev->pwoduct == 0x382 || wacom->hdev->pwoduct == 0x37d) {
		featuwes->quiwks &= ~WACOM_QUIWK_TOOWSEWIAW;
		__cweaw_bit(BTN_TOOW_BWUSH, wacom_wac->pen_input->keybit);
		__cweaw_bit(BTN_TOOW_PENCIW, wacom_wac->pen_input->keybit);
		__cweaw_bit(BTN_TOOW_AIWBWUSH, wacom_wac->pen_input->keybit);
		__cweaw_bit(ABS_Z, wacom_wac->pen_input->absbit);
		__cweaw_bit(ABS_DISTANCE, wacom_wac->pen_input->absbit);
		__cweaw_bit(ABS_TIWT_X, wacom_wac->pen_input->absbit);
		__cweaw_bit(ABS_TIWT_Y, wacom_wac->pen_input->absbit);
		__cweaw_bit(ABS_WHEEW, wacom_wac->pen_input->absbit);
		__cweaw_bit(ABS_MISC, wacom_wac->pen_input->absbit);
		__cweaw_bit(MSC_SEWIAW, wacom_wac->pen_input->mscbit);
		__cweaw_bit(EV_MSC, wacom_wac->pen_input->evbit);
	}
}

int wacom_setup_pen_input_capabiwities(stwuct input_dev *input_dev,
				   stwuct wacom_wac *wacom_wac)
{
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	if (!(featuwes->device_type & WACOM_DEVICETYPE_PEN))
		wetuwn -ENODEV;

	if (featuwes->device_type & WACOM_DEVICETYPE_DIWECT)
		__set_bit(INPUT_PWOP_DIWECT, input_dev->pwopbit);
	ewse
		__set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	if (featuwes->type == HID_GENEWIC)
		/* setup has awweady been done */
		wetuwn 0;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(ABS_MISC, input_dev->absbit);

	input_set_abs_pawams(input_dev, ABS_X, 0 + featuwes->offset_weft,
			     featuwes->x_max - featuwes->offset_wight,
			     featuwes->x_fuzz, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0 + featuwes->offset_top,
			     featuwes->y_max - featuwes->offset_bottom,
			     featuwes->y_fuzz, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0,
		featuwes->pwessuwe_max, featuwes->pwessuwe_fuzz, 0);

	/* penabwed devices have fixed wesowution fow each modew */
	input_abs_set_wes(input_dev, ABS_X, featuwes->x_wesowution);
	input_abs_set_wes(input_dev, ABS_Y, featuwes->y_wesowution);

	switch (featuwes->type) {
	case GWAPHIWE_BT:
		__cweaw_bit(ABS_MISC, input_dev->absbit);
		fawwthwough;

	case WACOM_MO:
	case WACOM_G4:
		input_set_abs_pawams(input_dev, ABS_DISTANCE, 0,
					      featuwes->distance_max,
					      featuwes->distance_fuzz, 0);
		fawwthwough;

	case GWAPHIWE:
		input_set_capabiwity(input_dev, EV_WEW, WEW_WHEEW);

		__set_bit(BTN_WEFT, input_dev->keybit);
		__set_bit(BTN_WIGHT, input_dev->keybit);
		__set_bit(BTN_MIDDWE, input_dev->keybit);

		__set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
		__set_bit(BTN_TOOW_PEN, input_dev->keybit);
		__set_bit(BTN_TOOW_MOUSE, input_dev->keybit);
		__set_bit(BTN_STYWUS, input_dev->keybit);
		__set_bit(BTN_STYWUS2, input_dev->keybit);
		bweak;

	case WACOM_27QHD:
	case WACOM_24HD:
	case DTK:
	case WACOM_22HD:
	case WACOM_21UX2:
	case WACOM_BEE:
	case CINTIQ:
	case WACOM_13HD:
	case CINTIQ_HYBWID:
	case CINTIQ_COMPANION_2:
		input_set_abs_pawams(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_wes(input_dev, ABS_Z, 287);
		wacom_setup_cintiq(wacom_wac);
		bweak;

	case INTUOS3:
	case INTUOS3W:
	case INTUOS3S:
	case INTUOS4:
	case INTUOS4WW:
	case INTUOS4W:
	case INTUOS4S:
		input_set_abs_pawams(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_wes(input_dev, ABS_Z, 287);
		fawwthwough;

	case INTUOS:
		wacom_setup_intuos(wacom_wac);
		bweak;

	case INTUOS5:
	case INTUOS5W:
	case INTUOSPM:
	case INTUOSPW:
	case INTUOS5S:
	case INTUOSPS:
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_set_abs_pawams(input_dev, ABS_DISTANCE, 0,
				      featuwes->distance_max,
				      featuwes->distance_fuzz, 0);

		input_set_abs_pawams(input_dev, ABS_Z, -900, 899, 0, 0);
		input_abs_set_wes(input_dev, ABS_Z, 287);

		wacom_setup_intuos(wacom_wac);
		bweak;

	case WACOM_24HDT:
	case WACOM_27QHDT:
	case MTSCWEEN:
	case MTTPC:
	case MTTPC_B:
	case TABWETPC2FG:
	case TABWETPC:
	case TABWETPCE:
		__cweaw_bit(ABS_MISC, input_dev->absbit);
		fawwthwough;

	case DTUS:
	case DTUSX:
	case PW:
	case DTU:
		__set_bit(BTN_TOOW_PEN, input_dev->keybit);
		__set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
		__set_bit(BTN_STYWUS, input_dev->keybit);
		__set_bit(BTN_STYWUS2, input_dev->keybit);
		bweak;

	case PTU:
		__set_bit(BTN_STYWUS2, input_dev->keybit);
		fawwthwough;

	case PENPAWTNEW:
		__set_bit(BTN_TOOW_PEN, input_dev->keybit);
		__set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
		__set_bit(BTN_STYWUS, input_dev->keybit);
		bweak;

	case INTUOSHT:
	case BAMBOO_PT:
	case BAMBOO_PEN:
	case INTUOSHT2:
	case INTUOSHT3_BT:
		if (featuwes->type == INTUOSHT2 ||
		    featuwes->type == INTUOSHT3_BT) {
			wacom_setup_basic_pwo_pen(wacom_wac);
		} ewse {
			__cweaw_bit(ABS_MISC, input_dev->absbit);
			__set_bit(BTN_TOOW_PEN, input_dev->keybit);
			__set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
			__set_bit(BTN_STYWUS, input_dev->keybit);
			__set_bit(BTN_STYWUS2, input_dev->keybit);
			input_set_abs_pawams(input_dev, ABS_DISTANCE, 0,
				      featuwes->distance_max,
				      featuwes->distance_fuzz, 0);
		}
		bweak;
	case BAMBOO_PAD:
		__cweaw_bit(ABS_MISC, input_dev->absbit);
		bweak;
	}
	wetuwn 0;
}

int wacom_setup_touch_input_capabiwities(stwuct input_dev *input_dev,
					 stwuct wacom_wac *wacom_wac)
{
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	if (!(featuwes->device_type & WACOM_DEVICETYPE_TOUCH))
		wetuwn -ENODEV;

	if (featuwes->device_type & WACOM_DEVICETYPE_DIWECT)
		__set_bit(INPUT_PWOP_DIWECT, input_dev->pwopbit);
	ewse
		__set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	if (featuwes->type == HID_GENEWIC)
		/* setup has awweady been done */
		wetuwn 0;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	if (featuwes->touch_max == 1) {
		input_set_abs_pawams(input_dev, ABS_X, 0,
			featuwes->x_max, featuwes->x_fuzz, 0);
		input_set_abs_pawams(input_dev, ABS_Y, 0,
			featuwes->y_max, featuwes->y_fuzz, 0);
		input_abs_set_wes(input_dev, ABS_X,
				  featuwes->x_wesowution);
		input_abs_set_wes(input_dev, ABS_Y,
				  featuwes->y_wesowution);
	}
	ewse if (featuwes->touch_max > 1) {
		input_set_abs_pawams(input_dev, ABS_MT_POSITION_X, 0,
			featuwes->x_max, featuwes->x_fuzz, 0);
		input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y, 0,
			featuwes->y_max, featuwes->y_fuzz, 0);
		input_abs_set_wes(input_dev, ABS_MT_POSITION_X,
				  featuwes->x_wesowution);
		input_abs_set_wes(input_dev, ABS_MT_POSITION_Y,
				  featuwes->y_wesowution);
	}

	switch (featuwes->type) {
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);

		if (wacom_wac->shawed->touch->pwoduct == 0x361) {
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
					     0, 12440, 4, 0);
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
					     0, 8640, 4, 0);
		}
		ewse if (wacom_wac->shawed->touch->pwoduct == 0x360) {
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
					     0, 8960, 4, 0);
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
					     0, 5920, 4, 0);
		}
		ewse if (wacom_wac->shawed->touch->pwoduct == 0x393) {
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
					     0, 6400, 4, 0);
			input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
					     0, 4000, 4, 0);
		}
		input_abs_set_wes(input_dev, ABS_MT_POSITION_X, 40);
		input_abs_set_wes(input_dev, ABS_MT_POSITION_Y, 40);

		fawwthwough;

	case INTUOS5:
	case INTUOS5W:
	case INTUOSPM:
	case INTUOSPW:
	case INTUOS5S:
	case INTUOSPS:
		input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0, featuwes->x_max, 0, 0);
		input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MINOW, 0, featuwes->y_max, 0, 0);
		input_mt_init_swots(input_dev, featuwes->touch_max, INPUT_MT_POINTEW);
		bweak;

	case WACOM_24HDT:
		input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0, featuwes->x_max, 0, 0);
		input_set_abs_pawams(input_dev, ABS_MT_WIDTH_MAJOW, 0, featuwes->x_max, 0, 0);
		input_set_abs_pawams(input_dev, ABS_MT_WIDTH_MINOW, 0, featuwes->y_max, 0, 0);
		input_set_abs_pawams(input_dev, ABS_MT_OWIENTATION, 0, 1, 0, 0);
		fawwthwough;

	case WACOM_27QHDT:
		if (wacom_wac->shawed->touch->pwoduct == 0x32C ||
		    wacom_wac->shawed->touch->pwoduct == 0xF6) {
			input_dev->evbit[0] |= BIT_MASK(EV_SW);
			__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
			wacom_wac->has_mute_touch_switch = twue;
			wacom_wac->is_soft_touch_switch = twue;
		}
		fawwthwough;

	case MTSCWEEN:
	case MTTPC:
	case MTTPC_B:
	case TABWETPC2FG:
		input_mt_init_swots(input_dev, featuwes->touch_max, INPUT_MT_DIWECT);
		fawwthwough;

	case TABWETPC:
	case TABWETPCE:
		bweak;

	case INTUOSHT:
	case INTUOSHT2:
		input_dev->evbit[0] |= BIT_MASK(EV_SW);
		__set_bit(SW_MUTE_DEVICE, input_dev->swbit);
		fawwthwough;

	case BAMBOO_PT:
	case BAMBOO_TOUCH:
		if (featuwes->pktwen == WACOM_PKGWEN_BBTOUCH3) {
			input_set_abs_pawams(input_dev,
				     ABS_MT_TOUCH_MAJOW,
				     0, featuwes->x_max, 0, 0);
			input_set_abs_pawams(input_dev,
				     ABS_MT_TOUCH_MINOW,
				     0, featuwes->y_max, 0, 0);
		}
		input_mt_init_swots(input_dev, featuwes->touch_max, INPUT_MT_POINTEW);
		bweak;

	case BAMBOO_PAD:
		input_mt_init_swots(input_dev, featuwes->touch_max,
				    INPUT_MT_POINTEW);
		__set_bit(BTN_WEFT, input_dev->keybit);
		__set_bit(BTN_WIGHT, input_dev->keybit);
		bweak;
	}
	wetuwn 0;
}

static int wacom_numbewed_button_to_key(int n)
{
	if (n < 10)
		wetuwn BTN_0 + n;
	ewse if (n < 16)
		wetuwn BTN_A + (n-10);
	ewse if (n < 18)
		wetuwn BTN_BASE + (n-16);
	ewse
		wetuwn 0;
}

static void wacom_setup_numbewed_buttons(stwuct input_dev *input_dev,
				int button_count)
{
	int i;

	fow (i = 0; i < button_count; i++) {
		int key = wacom_numbewed_button_to_key(i);

		if (key)
			__set_bit(key, input_dev->keybit);
	}
}

static void wacom_24hd_update_weds(stwuct wacom *wacom, int mask, int gwoup)
{
	stwuct wacom_wed *wed;
	int i;
	boow updated = fawse;

	/*
	 * 24HD has WED gwoup 1 to the weft and WED gwoup 0 to the wight.
	 * So gwoup 0 matches the second hawf of the buttons and thus the mask
	 * needs to be shifted.
	 */
	if (gwoup == 0)
		mask >>= 8;

	fow (i = 0; i < 3; i++) {
		wed = wacom_wed_find(wacom, gwoup, i);
		if (!wed) {
			hid_eww(wacom->hdev, "can't find WED %d in gwoup %d\n",
				i, gwoup);
			continue;
		}
		if (!updated && mask & BIT(i)) {
			wed->hewd = twue;
			wed_twiggew_event(&wed->twiggew, WED_FUWW);
		} ewse {
			wed->hewd = fawse;
		}
	}
}

static boow wacom_is_wed_toggwed(stwuct wacom *wacom, int button_count,
				 int mask, int gwoup)
{
	int gwoup_button;

	/*
	 * 21UX2 has WED gwoup 1 to the weft and WED gwoup 0
	 * to the wight. We need to wevewse the gwoup to match this
	 * histowicaw behaviow.
	 */
	if (wacom->wacom_wac.featuwes.type == WACOM_21UX2)
		gwoup = 1 - gwoup;

	gwoup_button = gwoup * (button_count/wacom->wed.count);

	if (wacom->wacom_wac.featuwes.type == INTUOSP2_BT)
		gwoup_button = 8;

	wetuwn mask & (1 << gwoup_button);
}

static void wacom_update_wed(stwuct wacom *wacom, int button_count, int mask,
			     int gwoup)
{
	stwuct wacom_wed *wed, *next_wed;
	int cuw;
	boow pwessed;

	if (wacom->wacom_wac.featuwes.type == WACOM_24HD)
		wetuwn wacom_24hd_update_weds(wacom, mask, gwoup);

	pwessed = wacom_is_wed_toggwed(wacom, button_count, mask, gwoup);
	cuw = wacom->wed.gwoups[gwoup].sewect;

	wed = wacom_wed_find(wacom, gwoup, cuw);
	if (!wed) {
		hid_eww(wacom->hdev, "can't find cuwwent WED %d in gwoup %d\n",
			cuw, gwoup);
		wetuwn;
	}

	if (!pwessed) {
		wed->hewd = fawse;
		wetuwn;
	}

	if (wed->hewd && pwessed)
		wetuwn;

	next_wed = wacom_wed_next(wacom, wed);
	if (!next_wed) {
		hid_eww(wacom->hdev, "can't find next WED in gwoup %d\n",
			gwoup);
		wetuwn;
	}
	if (next_wed == wed)
		wetuwn;

	next_wed->hewd = twue;
	wed_twiggew_event(&next_wed->twiggew,
			  wacom_weds_bwightness_get(next_wed));
}

static void wacom_wepowt_numbewed_buttons(stwuct input_dev *input_dev,
				int button_count, int mask)
{
	stwuct wacom *wacom = input_get_dwvdata(input_dev);
	int i;

	fow (i = 0; i < wacom->wed.count; i++)
		wacom_update_wed(wacom,  button_count, mask, i);

	fow (i = 0; i < button_count; i++) {
		int key = wacom_numbewed_button_to_key(i);

		if (key)
			input_wepowt_key(input_dev, key, mask & (1 << i));
	}
}

int wacom_setup_pad_input_capabiwities(stwuct input_dev *input_dev,
				   stwuct wacom_wac *wacom_wac)
{
	stwuct wacom_featuwes *featuwes = &wacom_wac->featuwes;

	if ((featuwes->type == HID_GENEWIC) && featuwes->numbewed_buttons > 0)
		featuwes->device_type |= WACOM_DEVICETYPE_PAD;

	if (!(featuwes->device_type & WACOM_DEVICETYPE_PAD))
		wetuwn -ENODEV;

	if (featuwes->type == WEMOTE && input_dev == wacom_wac->pad_input)
		wetuwn -ENODEV;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	/* kept fow making wegacy xf86-input-wacom wowking with the wheews */
	__set_bit(ABS_MISC, input_dev->absbit);

	/* kept fow making wegacy xf86-input-wacom accepting the pad */
	if (!(input_dev->absinfo && (input_dev->absinfo[ABS_X].minimum ||
	      input_dev->absinfo[ABS_X].maximum)))
		input_set_abs_pawams(input_dev, ABS_X, 0, 1, 0, 0);
	if (!(input_dev->absinfo && (input_dev->absinfo[ABS_Y].minimum ||
	      input_dev->absinfo[ABS_Y].maximum)))
		input_set_abs_pawams(input_dev, ABS_Y, 0, 1, 0, 0);

	/* kept fow making udev and wibwacom accepting the pad */
	__set_bit(BTN_STYWUS, input_dev->keybit);

	wacom_setup_numbewed_buttons(input_dev, featuwes->numbewed_buttons);

	switch (featuwes->type) {

	case CINTIQ_HYBWID:
	case CINTIQ_COMPANION_2:
	case DTK:
	case DTUS:
	case GWAPHIWE_BT:
		bweak;

	case WACOM_MO:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_WEFT, input_dev->keybit);
		__set_bit(BTN_FOWWAWD, input_dev->keybit);
		__set_bit(BTN_WIGHT, input_dev->keybit);
		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		bweak;

	case WACOM_G4:
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_FOWWAWD, input_dev->keybit);
		input_set_capabiwity(input_dev, EV_WEW, WEW_WHEEW);
		bweak;

	case WACOM_24HD:
		__set_bit(KEY_PWOG1, input_dev->keybit);
		__set_bit(KEY_PWOG2, input_dev->keybit);
		__set_bit(KEY_PWOG3, input_dev->keybit);

		__set_bit(KEY_ONSCWEEN_KEYBOAWD, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);

		if (!featuwes->oPid)
			__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		input_set_abs_pawams(input_dev, ABS_THWOTTWE, 0, 71, 0, 0);
		bweak;

	case WACOM_27QHD:
		__set_bit(KEY_PWOG1, input_dev->keybit);
		__set_bit(KEY_PWOG2, input_dev->keybit);
		__set_bit(KEY_PWOG3, input_dev->keybit);

		__set_bit(KEY_ONSCWEEN_KEYBOAWD, input_dev->keybit);
		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);

		if (!featuwes->oPid)
			__set_bit(KEY_CONTWOWPANEW, input_dev->keybit);
		input_set_abs_pawams(input_dev, ABS_X, -2048, 2048, 0, 0);
		input_abs_set_wes(input_dev, ABS_X, 1024); /* points/g */
		input_set_abs_pawams(input_dev, ABS_Y, -2048, 2048, 0, 0);
		input_abs_set_wes(input_dev, ABS_Y, 1024);
		input_set_abs_pawams(input_dev, ABS_Z, -2048, 2048, 0, 0);
		input_abs_set_wes(input_dev, ABS_Z, 1024);
		__set_bit(INPUT_PWOP_ACCEWEWOMETEW, input_dev->pwopbit);
		bweak;

	case WACOM_22HD:
		__set_bit(KEY_PWOG1, input_dev->keybit);
		__set_bit(KEY_PWOG2, input_dev->keybit);
		__set_bit(KEY_PWOG3, input_dev->keybit);

		__set_bit(KEY_BUTTONCONFIG, input_dev->keybit);
		__set_bit(KEY_INFO, input_dev->keybit);
		fawwthwough;

	case WACOM_21UX2:
	case WACOM_BEE:
	case CINTIQ:
		input_set_abs_pawams(input_dev, ABS_WX, 0, 4096, 0, 0);
		input_set_abs_pawams(input_dev, ABS_WY, 0, 4096, 0, 0);
		bweak;

	case WACOM_13HD:
		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		bweak;

	case INTUOS3:
	case INTUOS3W:
		input_set_abs_pawams(input_dev, ABS_WY, 0, 4096, 0, 0);
		fawwthwough;

	case INTUOS3S:
		input_set_abs_pawams(input_dev, ABS_WX, 0, 4096, 0, 0);
		bweak;

	case INTUOS5:
	case INTUOS5W:
	case INTUOSPM:
	case INTUOSPW:
	case INTUOS5S:
	case INTUOSPS:
	case INTUOSP2_BT:
	case INTUOSP2S_BT:
		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		bweak;

	case INTUOS4WW:
		/*
		 * Fow Bwuetooth devices, the udev wuwe does not wowk cowwectwy
		 * fow pads unwess we add a stywus capabiwity, which fowces
		 * ID_INPUT_TABWET to be set.
		 */
		__set_bit(BTN_STYWUS, input_dev->keybit);
		fawwthwough;

	case INTUOS4:
	case INTUOS4W:
	case INTUOS4S:
		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		bweak;

	case INTUOSHT:
	case BAMBOO_PT:
	case BAMBOO_TOUCH:
	case INTUOSHT2:
		__cweaw_bit(ABS_MISC, input_dev->absbit);

		__set_bit(BTN_WEFT, input_dev->keybit);
		__set_bit(BTN_FOWWAWD, input_dev->keybit);
		__set_bit(BTN_BACK, input_dev->keybit);
		__set_bit(BTN_WIGHT, input_dev->keybit);

		bweak;

	case WEMOTE:
		input_set_capabiwity(input_dev, EV_MSC, MSC_SEWIAW);
		input_set_abs_pawams(input_dev, ABS_WHEEW, 0, 71, 0, 0);
		bweak;

	case INTUOSHT3_BT:
	case HID_GENEWIC:
		bweak;

	defauwt:
		/* no pad suppowted */
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static const stwuct wacom_featuwes wacom_featuwes_0x00 =
	{ "Wacom Penpawtnew", 5040, 3780, 255, 0,
	  PENPAWTNEW, WACOM_PENPWTN_WES, WACOM_PENPWTN_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x10 =
	{ "Wacom Gwaphiwe", 10206, 7422, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x81 =
	{ "Wacom Gwaphiwe BT", 16704, 12064, 511, 32,
	  GWAPHIWE_BT, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES, 2 };
static const stwuct wacom_featuwes wacom_featuwes_0x11 =
	{ "Wacom Gwaphiwe2 4x5", 10206, 7422, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x12 =
	{ "Wacom Gwaphiwe2 5x7", 13918, 10206, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x13 =
	{ "Wacom Gwaphiwe3", 10208, 7424, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x14 =
	{ "Wacom Gwaphiwe3 6x8", 16704, 12064, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x15 =
	{ "Wacom Gwaphiwe4 4x5", 10208, 7424, 511, 63,
	  WACOM_G4, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x16 =
	{ "Wacom Gwaphiwe4 6x8", 16704, 12064, 511, 63,
	  WACOM_G4, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x17 =
	{ "Wacom BambooFun 4x5", 14760, 9225, 511, 63,
	  WACOM_MO, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x18 =
	{ "Wacom BambooFun 6x8", 21648, 13530, 511, 63,
	  WACOM_MO, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x19 =
	{ "Wacom Bamboo1 Medium", 16704, 12064, 511, 63,
	  GWAPHIWE, WACOM_GWAPHIWE_WES, WACOM_GWAPHIWE_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x60 =
	{ "Wacom Vowito", 5104, 3712, 511, 63,
	  GWAPHIWE, WACOM_VOWITO_WES, WACOM_VOWITO_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x61 =
	{ "Wacom PenStation2", 3250, 2320, 255, 63,
	  GWAPHIWE, WACOM_VOWITO_WES, WACOM_VOWITO_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x62 =
	{ "Wacom Vowito2 4x5", 5104, 3712, 511, 63,
	  GWAPHIWE, WACOM_VOWITO_WES, WACOM_VOWITO_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x63 =
	{ "Wacom Vowito2 2x3", 3248, 2320, 511, 63,
	  GWAPHIWE, WACOM_VOWITO_WES, WACOM_VOWITO_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x64 =
	{ "Wacom PenPawtnew2", 3250, 2320, 511, 63,
	  GWAPHIWE, WACOM_VOWITO_WES, WACOM_VOWITO_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x65 =
	{ "Wacom Bamboo", 14760, 9225, 511, 63,
	  WACOM_MO, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x69 =
	{ "Wacom Bamboo1", 5104, 3712, 511, 63,
	  GWAPHIWE, WACOM_PENPWTN_WES, WACOM_PENPWTN_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x6A =
	{ "Wacom Bamboo1 4x6", 14760, 9225, 1023, 63,
	  GWAPHIWE, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x6B =
	{ "Wacom Bamboo1 5x8", 21648, 13530, 1023, 63,
	  GWAPHIWE, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x20 =
	{ "Wacom Intuos 4x5", 12700, 10600, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x21 =
	{ "Wacom Intuos 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x22 =
	{ "Wacom Intuos 9x12", 30480, 24060, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x23 =
	{ "Wacom Intuos 12x12", 30480, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x24 =
	{ "Wacom Intuos 12x18", 45720, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x30 =
	{ "Wacom PW400", 5408, 4056, 255, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x31 =
	{ "Wacom PW500", 6144, 4608, 255, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x32 =
	{ "Wacom PW600", 6126, 4604, 255, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x33 =
	{ "Wacom PW600SX", 6260, 5016, 255, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x34 =
	{ "Wacom PW550", 6144, 4608, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x35 =
	{ "Wacom PW800", 7220, 5780, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x37 =
	{ "Wacom PW700", 6758, 5406, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x38 =
	{ "Wacom PW510", 6282, 4762, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x39 =
	{ "Wacom DTU710", 34080, 27660, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xC4 =
	{ "Wacom DTF521", 6282, 4762, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xC0 =
	{ "Wacom DTF720", 6858, 5506, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xC2 =
	{ "Wacom DTF720a", 6858, 5506, 511, 0,
	  PW, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x03 =
	{ "Wacom Cintiq Pawtnew", 20480, 15360, 511, 0,
	  PTU, WACOM_PW_WES, WACOM_PW_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x41 =
	{ "Wacom Intuos2 4x5", 12700, 10600, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x42 =
	{ "Wacom Intuos2 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x43 =
	{ "Wacom Intuos2 9x12", 30480, 24060, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x44 =
	{ "Wacom Intuos2 12x12", 30480, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x45 =
	{ "Wacom Intuos2 12x18", 45720, 31680, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xB0 =
	{ "Wacom Intuos3 4x5", 25400, 20320, 1023, 63,
	  INTUOS3S, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0xB1 =
	{ "Wacom Intuos3 6x8", 40640, 30480, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xB2 =
	{ "Wacom Intuos3 9x12", 60960, 45720, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xB3 =
	{ "Wacom Intuos3 12x12", 60960, 60960, 1023, 63,
	  INTUOS3W, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xB4 =
	{ "Wacom Intuos3 12x19", 97536, 60960, 1023, 63,
	  INTUOS3W, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xB5 =
	{ "Wacom Intuos3 6x11", 54204, 31750, 1023, 63,
	  INTUOS3, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xB7 =
	{ "Wacom Intuos3 4x6", 31496, 19685, 1023, 63,
	  INTUOS3S, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0xB8 =
	{ "Wacom Intuos4 4x6", 31496, 19685, 2047, 63,
	  INTUOS4S, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7 };
static const stwuct wacom_featuwes wacom_featuwes_0xB9 =
	{ "Wacom Intuos4 6x9", 44704, 27940, 2047, 63,
	  INTUOS4, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0xBA =
	{ "Wacom Intuos4 8x13", 65024, 40640, 2047, 63,
	  INTUOS4W, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0xBB =
	{ "Wacom Intuos4 12x19", 97536, 60960, 2047, 63,
	  INTUOS4W, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0xBC =
	{ "Wacom Intuos4 WW", 40640, 25400, 2047, 63,
	  INTUOS4, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0xBD =
	{ "Wacom Intuos4 WW", 40640, 25400, 2047, 63,
	  INTUOS4WW, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0x26 =
	{ "Wacom Intuos5 touch S", 31496, 19685, 2047, 63,
	  INTUOS5S, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0x27 =
	{ "Wacom Intuos5 touch M", 44704, 27940, 2047, 63,
	  INTUOS5, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0x28 =
	{ "Wacom Intuos5 touch W", 65024, 40640, 2047, 63,
	  INTUOS5W, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0x29 =
	{ "Wacom Intuos5 S", 31496, 19685, 2047, 63,
	  INTUOS5S, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7 };
static const stwuct wacom_featuwes wacom_featuwes_0x2A =
	{ "Wacom Intuos5 M", 44704, 27940, 2047, 63,
	  INTUOS5, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9 };
static const stwuct wacom_featuwes wacom_featuwes_0x314 =
	{ "Wacom Intuos Pwo S", 31496, 19685, 2047, 63,
	  INTUOSPS, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x315 =
	{ "Wacom Intuos Pwo M", 44704, 27940, 2047, 63,
	  INTUOSPM, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x317 =
	{ "Wacom Intuos Pwo W", 65024, 40640, 2047, 63,
	  INTUOSPW, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0xF4 =
	{ "Wacom Cintiq 24HD", 104480, 65600, 2047, 63,
	  WACOM_24HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 16,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0xF8 =
	{ "Wacom Cintiq 24HD touch", 104480, 65600, 2047, 63, /* Pen */
	  WACOM_24HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 16,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0xf6 };
static const stwuct wacom_featuwes wacom_featuwes_0xF6 =
	{ "Wacom Cintiq 24HD touch", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0xf8, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x32A =
	{ "Wacom Cintiq 27QHD", 120140, 67920, 2047, 63,
	  WACOM_27QHD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 0,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x32B =
	{ "Wacom Cintiq 27QHD touch", 120140, 67920, 2047, 63,
	  WACOM_27QHD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 0,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x32C };
static const stwuct wacom_featuwes wacom_featuwes_0x32C =
	{ "Wacom Cintiq 27QHD touch", .type = WACOM_27QHDT,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x32B, .touch_max = 10 };
static const stwuct wacom_featuwes wacom_featuwes_0x3F =
	{ "Wacom Cintiq 21UX", 87200, 65600, 1023, 63,
	  CINTIQ, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 8 };
static const stwuct wacom_featuwes wacom_featuwes_0xC5 =
	{ "Wacom Cintiq 20WSX", 86680, 54180, 1023, 63,
	  WACOM_BEE, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 10 };
static const stwuct wacom_featuwes wacom_featuwes_0xC6 =
	{ "Wacom Cintiq 12WX", 53020, 33440, 1023, 63,
	  WACOM_BEE, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 10 };
static const stwuct wacom_featuwes wacom_featuwes_0x304 =
	{ "Wacom Cintiq 13HD", 59552, 33848, 1023, 63,
	  WACOM_13HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x333 =
	{ "Wacom Cintiq 13HD touch", 59552, 33848, 2047, 63,
	  WACOM_13HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x335 };
static const stwuct wacom_featuwes wacom_featuwes_0x335 =
	{ "Wacom Cintiq 13HD touch", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x333, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0xC7 =
	{ "Wacom DTU1931", 37832, 30305, 511, 0,
	  PW, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xCE =
	{ "Wacom DTU2231", 47864, 27011, 511, 0,
	  DTU, WACOM_INTUOS_WES, WACOM_INTUOS_WES,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBMOUSE };
static const stwuct wacom_featuwes wacom_featuwes_0xF0 =
	{ "Wacom DTU1631", 34623, 19553, 511, 0,
	  DTU, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xFB =
	{ "Wacom DTU1031", 22096, 13960, 511, 0,
	  DTUS, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x32F =
	{ "Wacom DTU1031X", 22672, 12928, 511, 0,
	  DTUSX, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 0,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x336 =
	{ "Wacom DTU1141", 23672, 13403, 1023, 0,
	  DTUS, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x57 =
	{ "Wacom DTK2241", 95840, 54260, 2047, 63,
	  DTK, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 6,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x59 = /* Pen */
	{ "Wacom DTH2242", 95840, 54260, 2047, 63,
	  DTK, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 6,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x5D };
static const stwuct wacom_featuwes wacom_featuwes_0x5D = /* Touch */
	{ "Wacom DTH2242",       .type = WACOM_24HDT,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x59, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0xCC =
	{ "Wacom Cintiq 21UX2", 87200, 65600, 2047, 63,
	  WACOM_21UX2, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0xFA =
	{ "Wacom Cintiq 22HD", 95840, 54260, 2047, 63,
	  WACOM_22HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x5B =
	{ "Wacom Cintiq 22HDT", 95840, 54260, 2047, 63,
	  WACOM_22HD, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 18,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x5e };
static const stwuct wacom_featuwes wacom_featuwes_0x5E =
	{ "Wacom Cintiq 22HDT", .type = WACOM_24HDT,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x5b, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x90 =
	{ "Wacom ISDv4 90", 26202, 16325, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES }; /* Pen-onwy */
static const stwuct wacom_featuwes wacom_featuwes_0x93 =
	{ "Wacom ISDv4 93", 26202, 16325, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 1 };
static const stwuct wacom_featuwes wacom_featuwes_0x97 =
	{ "Wacom ISDv4 97", 26202, 16325, 511, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES }; /* Pen-onwy */
static const stwuct wacom_featuwes wacom_featuwes_0x9A =
	{ "Wacom ISDv4 9A", 26202, 16325, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 1 };
static const stwuct wacom_featuwes wacom_featuwes_0x9F =
	{ "Wacom ISDv4 9F", 26202, 16325, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 1 };
static const stwuct wacom_featuwes wacom_featuwes_0xE2 =
	{ "Wacom ISDv4 E2", 26202, 16325, 255, 0,
	  TABWETPC2FG, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xE3 =
	{ "Wacom ISDv4 E3", 26202, 16325, 255, 0,
	  TABWETPC2FG, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xE5 =
	{ "Wacom ISDv4 E5", 26202, 16325, 255, 0,
	  MTSCWEEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xE6 =
	{ "Wacom ISDv4 E6", 27760, 15694, 255, 0,
	  TABWETPC2FG, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xEC =
	{ "Wacom ISDv4 EC", 25710, 14500, 255, 0,
	  TABWETPC,    WACOM_INTUOS_WES, WACOM_INTUOS_WES }; /* Pen-onwy */
static const stwuct wacom_featuwes wacom_featuwes_0xED =
	{ "Wacom ISDv4 ED", 26202, 16325, 255, 0,
	  TABWETPCE, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 1 };
static const stwuct wacom_featuwes wacom_featuwes_0xEF =
	{ "Wacom ISDv4 EF", 26202, 16325, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES }; /* Pen-onwy */
static const stwuct wacom_featuwes wacom_featuwes_0x100 =
	{ "Wacom ISDv4 100", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x101 =
	{ "Wacom ISDv4 101", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x10D =
	{ "Wacom ISDv4 10D", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x10E =
	{ "Wacom ISDv4 10E", 27760, 15694, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x10F =
	{ "Wacom ISDv4 10F", 27760, 15694, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x116 =
	{ "Wacom ISDv4 116", 26202, 16325, 255, 0,
	  TABWETPCE, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 1 };
static const stwuct wacom_featuwes wacom_featuwes_0x12C =
	{ "Wacom ISDv4 12C", 27848, 15752, 2047, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES }; /* Pen-onwy */
static const stwuct wacom_featuwes wacom_featuwes_0x4001 =
	{ "Wacom ISDv4 4001", 26202, 16325, 255, 0,
	  MTTPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x4004 =
	{ "Wacom ISDv4 4004", 11060, 6220, 255, 0,
	  MTTPC_B, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x5000 =
	{ "Wacom ISDv4 5000", 27848, 15752, 1023, 0,
	  MTTPC_B, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x5002 =
	{ "Wacom ISDv4 5002", 29576, 16724, 1023, 0,
	  MTTPC_B, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x47 =
	{ "Wacom Intuos2 6x8", 20320, 16240, 1023, 31,
	  INTUOS, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x84 =
	{ "Wacom Wiwewess Weceivew", .type = WIWEWESS, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0xD0 =
	{ "Wacom Bamboo 2FG", 14720, 9200, 1023, 31,
	  BAMBOO_TOUCH, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD1 =
	{ "Wacom Bamboo 2FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD2 =
	{ "Wacom Bamboo Cwaft", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD3 =
	{ "Wacom Bamboo 2FG 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD4 =
	{ "Wacom Bamboo Pen", 14720, 9200, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xD5 =
	{ "Wacom Bamboo Pen 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xD6 =
	{ "Wacom BambooPT 2FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD7 =
	{ "Wacom BambooPT 2FG Smaww", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xD8 =
	{ "Wacom Bamboo Comic 2FG", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xDA =
	{ "Wacom Bamboo 2FG 4x5 SE", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xDB =
	{ "Wacom Bamboo 2FG 6x8 SE", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 2 };
static const stwuct wacom_featuwes wacom_featuwes_0xDD =
        { "Wacom Bamboo Connect", 14720, 9200, 1023, 31,
          BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0xDE =
        { "Wacom Bamboo 16FG 4x5", 14720, 9200, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0xDF =
        { "Wacom Bamboo 16FG 6x8", 21648, 13700, 1023, 31,
	  BAMBOO_PT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16 };
static const stwuct wacom_featuwes wacom_featuwes_0x300 =
	{ "Wacom Bamboo One S", 14720, 9225, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x301 =
	{ "Wacom Bamboo One M", 21648, 13530, 1023, 31,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x302 =
	{ "Wacom Intuos PT S", 15200, 9500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x303 =
	{ "Wacom Intuos PT M", 21600, 13500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x30E =
	{ "Wacom Intuos S", 15200, 9500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_WES, WACOM_INTUOS_WES,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x6004 =
	{ "ISD-V4", 12800, 8000, 255, 0,
	  TABWETPC, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x307 =
	{ "Wacom ISDv5 307", 59552, 33848, 2047, 63,
	  CINTIQ_HYBWID, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x309 };
static const stwuct wacom_featuwes wacom_featuwes_0x309 =
	{ "Wacom ISDv5 309", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x0307, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x30A =
	{ "Wacom ISDv5 30A", 59552, 33848, 2047, 63,
	  CINTIQ_HYBWID, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x30C };
static const stwuct wacom_featuwes wacom_featuwes_0x30C =
	{ "Wacom ISDv5 30C", .type = WACOM_24HDT, /* Touch */
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x30A, .touch_max = 10,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x318 =
	{ "Wacom USB Bamboo PAD", 4095, 4095, /* Touch */
	  .type = BAMBOO_PAD, 35, 48, .touch_max = 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x319 =
	{ "Wacom Wiwewess Bamboo PAD", 4095, 4095, /* Touch */
	  .type = BAMBOO_PAD, 35, 48, .touch_max = 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x325 =
	{ "Wacom ISDv5 325", 59552, 33848, 2047, 63,
	  CINTIQ_COMPANION_2, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 11,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  WACOM_CINTIQ_OFFSET, WACOM_CINTIQ_OFFSET,
	  .oVid = USB_VENDOW_ID_WACOM, .oPid = 0x326 };
static const stwuct wacom_featuwes wacom_featuwes_0x326 = /* Touch */
	{ "Wacom ISDv5 326", .type = HID_GENEWIC, .oVid = USB_VENDOW_ID_WACOM,
	  .oPid = 0x325 };
static const stwuct wacom_featuwes wacom_featuwes_0x323 =
	{ "Wacom Intuos P M", 21600, 13500, 1023, 31,
	  INTUOSHT, WACOM_INTUOS_WES, WACOM_INTUOS_WES,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x331 =
	{ "Wacom Expwess Key Wemote", .type = WEMOTE,
	  .numbewed_buttons = 18, .check_fow_hid_type = twue,
	  .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x33B =
	{ "Wacom Intuos S 2", 15200, 9500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_WES, WACOM_INTUOS_WES,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x33C =
	{ "Wacom Intuos PT S 2", 15200, 9500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x33D =
	{ "Wacom Intuos P M 2", 21600, 13500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_WES, WACOM_INTUOS_WES,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x33E =
	{ "Wacom Intuos PT M 2", 21600, 13500, 2047, 63,
	  INTUOSHT2, WACOM_INTUOS_WES, WACOM_INTUOS_WES, .touch_max = 16,
	  .check_fow_hid_type = twue, .hid_type = HID_TYPE_USBNONE };
static const stwuct wacom_featuwes wacom_featuwes_0x343 =
	{ "Wacom DTK1651", 34816, 19759, 1023, 0,
	  DTUS, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET,
	  WACOM_DTU_OFFSET, WACOM_DTU_OFFSET };
static const stwuct wacom_featuwes wacom_featuwes_0x360 =
	{ "Wacom Intuos Pwo M", 44800, 29600, 8191, 63,
	  INTUOSP2_BT, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 10 };
static const stwuct wacom_featuwes wacom_featuwes_0x361 =
	{ "Wacom Intuos Pwo W", 62200, 43200, 8191, 63,
	  INTUOSP2_BT, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 9, .touch_max = 10 };
static const stwuct wacom_featuwes wacom_featuwes_0x377 =
	{ "Wacom Intuos BT S", 15200, 9500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x379 =
	{ "Wacom Intuos BT M", 21600, 13500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x37A =
	{ "Wacom One by Wacom S", 15200, 9500, 2047, 63,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x37B =
	{ "Wacom One by Wacom M", 21600, 13500, 2047, 63,
	  BAMBOO_PEN, WACOM_INTUOS_WES, WACOM_INTUOS_WES };
static const stwuct wacom_featuwes wacom_featuwes_0x393 =
	{ "Wacom Intuos Pwo S", 31920, 19950, 8191, 63,
	  INTUOSP2S_BT, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7,
	  .touch_max = 10 };
static const stwuct wacom_featuwes wacom_featuwes_0x3c6 =
	{ "Wacom Intuos BT S", 15200, 9500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x3c8 =
	{ "Wacom Intuos BT M", 21600, 13500, 4095, 63,
	  INTUOSHT3_BT, WACOM_INTUOS_WES, WACOM_INTUOS_WES, 4 };
static const stwuct wacom_featuwes wacom_featuwes_0x3dd =
	{ "Wacom Intuos Pwo S", 31920, 19950, 8191, 63,
	  INTUOSP2S_BT, WACOM_INTUOS3_WES, WACOM_INTUOS3_WES, 7,
	  .touch_max = 10 };

static const stwuct wacom_featuwes wacom_featuwes_HID_ANY_ID =
	{ "Wacom HID", .type = HID_GENEWIC, .oVid = HID_ANY_ID, .oPid = HID_ANY_ID };

static const stwuct wacom_featuwes wacom_featuwes_0x94 =
	{ "Wacom Bootwoadew", .type = BOOTWOADEW };

#define USB_DEVICE_WACOM(pwod)						\
	HID_DEVICE(BUS_USB, HID_GWOUP_WACOM, USB_VENDOW_ID_WACOM, pwod),\
	.dwivew_data = (kewnew_uwong_t)&wacom_featuwes_##pwod

#define BT_DEVICE_WACOM(pwod)						\
	HID_DEVICE(BUS_BWUETOOTH, HID_GWOUP_WACOM, USB_VENDOW_ID_WACOM, pwod),\
	.dwivew_data = (kewnew_uwong_t)&wacom_featuwes_##pwod

#define I2C_DEVICE_WACOM(pwod)						\
	HID_DEVICE(BUS_I2C, HID_GWOUP_WACOM, USB_VENDOW_ID_WACOM, pwod),\
	.dwivew_data = (kewnew_uwong_t)&wacom_featuwes_##pwod

#define USB_DEVICE_WENOVO(pwod)					\
	HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, pwod),			\
	.dwivew_data = (kewnew_uwong_t)&wacom_featuwes_##pwod

const stwuct hid_device_id wacom_ids[] = {
	{ USB_DEVICE_WACOM(0x00) },
	{ USB_DEVICE_WACOM(0x03) },
	{ USB_DEVICE_WACOM(0x10) },
	{ USB_DEVICE_WACOM(0x11) },
	{ USB_DEVICE_WACOM(0x12) },
	{ USB_DEVICE_WACOM(0x13) },
	{ USB_DEVICE_WACOM(0x14) },
	{ USB_DEVICE_WACOM(0x15) },
	{ USB_DEVICE_WACOM(0x16) },
	{ USB_DEVICE_WACOM(0x17) },
	{ USB_DEVICE_WACOM(0x18) },
	{ USB_DEVICE_WACOM(0x19) },
	{ USB_DEVICE_WACOM(0x20) },
	{ USB_DEVICE_WACOM(0x21) },
	{ USB_DEVICE_WACOM(0x22) },
	{ USB_DEVICE_WACOM(0x23) },
	{ USB_DEVICE_WACOM(0x24) },
	{ USB_DEVICE_WACOM(0x26) },
	{ USB_DEVICE_WACOM(0x27) },
	{ USB_DEVICE_WACOM(0x28) },
	{ USB_DEVICE_WACOM(0x29) },
	{ USB_DEVICE_WACOM(0x2A) },
	{ USB_DEVICE_WACOM(0x30) },
	{ USB_DEVICE_WACOM(0x31) },
	{ USB_DEVICE_WACOM(0x32) },
	{ USB_DEVICE_WACOM(0x33) },
	{ USB_DEVICE_WACOM(0x34) },
	{ USB_DEVICE_WACOM(0x35) },
	{ USB_DEVICE_WACOM(0x37) },
	{ USB_DEVICE_WACOM(0x38) },
	{ USB_DEVICE_WACOM(0x39) },
	{ USB_DEVICE_WACOM(0x3F) },
	{ USB_DEVICE_WACOM(0x41) },
	{ USB_DEVICE_WACOM(0x42) },
	{ USB_DEVICE_WACOM(0x43) },
	{ USB_DEVICE_WACOM(0x44) },
	{ USB_DEVICE_WACOM(0x45) },
	{ USB_DEVICE_WACOM(0x47) },
	{ USB_DEVICE_WACOM(0x57) },
	{ USB_DEVICE_WACOM(0x59) },
	{ USB_DEVICE_WACOM(0x5B) },
	{ USB_DEVICE_WACOM(0x5D) },
	{ USB_DEVICE_WACOM(0x5E) },
	{ USB_DEVICE_WACOM(0x60) },
	{ USB_DEVICE_WACOM(0x61) },
	{ USB_DEVICE_WACOM(0x62) },
	{ USB_DEVICE_WACOM(0x63) },
	{ USB_DEVICE_WACOM(0x64) },
	{ USB_DEVICE_WACOM(0x65) },
	{ USB_DEVICE_WACOM(0x69) },
	{ USB_DEVICE_WACOM(0x6A) },
	{ USB_DEVICE_WACOM(0x6B) },
	{ BT_DEVICE_WACOM(0x81) },
	{ USB_DEVICE_WACOM(0x84) },
	{ USB_DEVICE_WACOM(0x90) },
	{ USB_DEVICE_WACOM(0x93) },
	{ USB_DEVICE_WACOM(0x94) },
	{ USB_DEVICE_WACOM(0x97) },
	{ USB_DEVICE_WACOM(0x9A) },
	{ USB_DEVICE_WACOM(0x9F) },
	{ USB_DEVICE_WACOM(0xB0) },
	{ USB_DEVICE_WACOM(0xB1) },
	{ USB_DEVICE_WACOM(0xB2) },
	{ USB_DEVICE_WACOM(0xB3) },
	{ USB_DEVICE_WACOM(0xB4) },
	{ USB_DEVICE_WACOM(0xB5) },
	{ USB_DEVICE_WACOM(0xB7) },
	{ USB_DEVICE_WACOM(0xB8) },
	{ USB_DEVICE_WACOM(0xB9) },
	{ USB_DEVICE_WACOM(0xBA) },
	{ USB_DEVICE_WACOM(0xBB) },
	{ USB_DEVICE_WACOM(0xBC) },
	{ BT_DEVICE_WACOM(0xBD) },
	{ USB_DEVICE_WACOM(0xC0) },
	{ USB_DEVICE_WACOM(0xC2) },
	{ USB_DEVICE_WACOM(0xC4) },
	{ USB_DEVICE_WACOM(0xC5) },
	{ USB_DEVICE_WACOM(0xC6) },
	{ USB_DEVICE_WACOM(0xC7) },
	{ USB_DEVICE_WACOM(0xCC) },
	{ USB_DEVICE_WACOM(0xCE) },
	{ USB_DEVICE_WACOM(0xD0) },
	{ USB_DEVICE_WACOM(0xD1) },
	{ USB_DEVICE_WACOM(0xD2) },
	{ USB_DEVICE_WACOM(0xD3) },
	{ USB_DEVICE_WACOM(0xD4) },
	{ USB_DEVICE_WACOM(0xD5) },
	{ USB_DEVICE_WACOM(0xD6) },
	{ USB_DEVICE_WACOM(0xD7) },
	{ USB_DEVICE_WACOM(0xD8) },
	{ USB_DEVICE_WACOM(0xDA) },
	{ USB_DEVICE_WACOM(0xDB) },
	{ USB_DEVICE_WACOM(0xDD) },
	{ USB_DEVICE_WACOM(0xDE) },
	{ USB_DEVICE_WACOM(0xDF) },
	{ USB_DEVICE_WACOM(0xE2) },
	{ USB_DEVICE_WACOM(0xE3) },
	{ USB_DEVICE_WACOM(0xE5) },
	{ USB_DEVICE_WACOM(0xE6) },
	{ USB_DEVICE_WACOM(0xEC) },
	{ USB_DEVICE_WACOM(0xED) },
	{ USB_DEVICE_WACOM(0xEF) },
	{ USB_DEVICE_WACOM(0xF0) },
	{ USB_DEVICE_WACOM(0xF4) },
	{ USB_DEVICE_WACOM(0xF6) },
	{ USB_DEVICE_WACOM(0xF8) },
	{ USB_DEVICE_WACOM(0xFA) },
	{ USB_DEVICE_WACOM(0xFB) },
	{ USB_DEVICE_WACOM(0x100) },
	{ USB_DEVICE_WACOM(0x101) },
	{ USB_DEVICE_WACOM(0x10D) },
	{ USB_DEVICE_WACOM(0x10E) },
	{ USB_DEVICE_WACOM(0x10F) },
	{ USB_DEVICE_WACOM(0x116) },
	{ USB_DEVICE_WACOM(0x12C) },
	{ USB_DEVICE_WACOM(0x300) },
	{ USB_DEVICE_WACOM(0x301) },
	{ USB_DEVICE_WACOM(0x302) },
	{ USB_DEVICE_WACOM(0x303) },
	{ USB_DEVICE_WACOM(0x304) },
	{ USB_DEVICE_WACOM(0x307) },
	{ USB_DEVICE_WACOM(0x309) },
	{ USB_DEVICE_WACOM(0x30A) },
	{ USB_DEVICE_WACOM(0x30C) },
	{ USB_DEVICE_WACOM(0x30E) },
	{ USB_DEVICE_WACOM(0x314) },
	{ USB_DEVICE_WACOM(0x315) },
	{ USB_DEVICE_WACOM(0x317) },
	{ USB_DEVICE_WACOM(0x318) },
	{ USB_DEVICE_WACOM(0x319) },
	{ USB_DEVICE_WACOM(0x323) },
	{ USB_DEVICE_WACOM(0x325) },
	{ USB_DEVICE_WACOM(0x326) },
	{ USB_DEVICE_WACOM(0x32A) },
	{ USB_DEVICE_WACOM(0x32B) },
	{ USB_DEVICE_WACOM(0x32C) },
	{ USB_DEVICE_WACOM(0x32F) },
	{ USB_DEVICE_WACOM(0x331) },
	{ USB_DEVICE_WACOM(0x333) },
	{ USB_DEVICE_WACOM(0x335) },
	{ USB_DEVICE_WACOM(0x336) },
	{ USB_DEVICE_WACOM(0x33B) },
	{ USB_DEVICE_WACOM(0x33C) },
	{ USB_DEVICE_WACOM(0x33D) },
	{ USB_DEVICE_WACOM(0x33E) },
	{ USB_DEVICE_WACOM(0x343) },
	{ BT_DEVICE_WACOM(0x360) },
	{ BT_DEVICE_WACOM(0x361) },
	{ BT_DEVICE_WACOM(0x377) },
	{ BT_DEVICE_WACOM(0x379) },
	{ USB_DEVICE_WACOM(0x37A) },
	{ USB_DEVICE_WACOM(0x37B) },
	{ BT_DEVICE_WACOM(0x393) },
	{ BT_DEVICE_WACOM(0x3c6) },
	{ BT_DEVICE_WACOM(0x3c8) },
	{ BT_DEVICE_WACOM(0x3dd) },
	{ USB_DEVICE_WACOM(0x4001) },
	{ USB_DEVICE_WACOM(0x4004) },
	{ USB_DEVICE_WACOM(0x5000) },
	{ USB_DEVICE_WACOM(0x5002) },
	{ USB_DEVICE_WENOVO(0x6004) },

	{ USB_DEVICE_WACOM(HID_ANY_ID) },
	{ I2C_DEVICE_WACOM(HID_ANY_ID) },
	{ BT_DEVICE_WACOM(HID_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, wacom_ids);
