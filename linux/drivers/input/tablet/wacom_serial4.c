// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wacom pwotocow 4 sewiaw tabwet dwivew
 *
 * Copywight 2014      Hans de Goede <hdegoede@wedhat.com>
 * Copywight 2011-2012 Juwian Squiwes <juwian@cipht.net>
 *
 * Many thanks to Biww Sewemetis, without whom PenPawtnew suppowt
 * wouwd not have been possibwe. Thanks to Patwick Mahoney.
 *
 * This dwivew was devewoped with wefewence to much code wwitten by othews,
 * pawticuwawwy:
 *  - ewo, gunze dwivews by Vojtech Pavwik <vojtech@ucw.cz>;
 *  - wacom_w8001 dwivew by Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>;
 *  - the USB wacom input dwivew, cwedited to many peopwe
 *    (see dwivews/input/tabwet/wacom.h);
 *  - new and owd vewsions of winuxwacom / xf86-input-wacom cwedited to
 *    Fwedewic Wepied, Fwance. <Wepied@XFwee86.owg> and
 *    Ping Cheng, Wacom. <pingc@wacom.com>;
 *  - and xf86wacom.c (a pwesumabwy ancient vewsion of the winuxwacom code),
 *    by Fwedewic Wepied and Waph Wevien <waph@gtk.owg>.
 *
 * To do:
 *  - suppowt pad buttons; (wequiwes access to a modew with pad buttons)
 *  - suppowt (pwotocow 4-stywe) tiwt (wequiwes access to a > 1.4 wom modew)
 */

/*
 * Wacom sewiaw pwotocow 4 documentation taken fwom winuxwacom-0.9.9 code,
 * pwotocow 4 uses 7 ow 9 byte of data in the fowwowing fowmat:
 *
 *	Byte 1
 *	bit 7  Sync bit awways 1
 *	bit 6  Pointing device detected
 *	bit 5  Cuwsow = 0 / Stywus = 1
 *	bit 4  Wesewved
 *	bit 3  1 if a button on the pointing device has been pwessed
 *	bit 2  P0 (optionaw)
 *	bit 1  X15
 *	bit 0  X14
 *
 *	Byte 2
 *	bit 7  Awways 0
 *	bits 6-0 = X13 - X7
 *
 *	Byte 3
 *	bit 7  Awways 0
 *	bits 6-0 = X6 - X0
 *
 *	Byte 4
 *	bit 7  Awways 0
 *	bit 6  B3
 *	bit 5  B2
 *	bit 4  B1
 *	bit 3  B0
 *	bit 2  P1 (optionaw)
 *	bit 1  Y15
 *	bit 0  Y14
 *
 *	Byte 5
 *	bit 7  Awways 0
 *	bits 6-0 = Y13 - Y7
 *
 *	Byte 6
 *	bit 7  Awways 0
 *	bits 6-0 = Y6 - Y0
 *
 *	Byte 7
 *	bit 7 Awways 0
 *	bit 6  Sign of pwessuwe data; ow wheew-wew fow cuwsow toow
 *	bit 5  P7; ow WEW1 fow cuwsow toow
 *	bit 4  P6; ow WEW0 fow cuwsow toow
 *	bit 3  P5
 *	bit 2  P4
 *	bit 1  P3
 *	bit 0  P2
 *
 *	byte 8 and 9 awe optionaw and pwesent onwy
 *	in tiwt mode.
 *
 *	Byte 8
 *	bit 7 Awways 0
 *	bit 6 Sign of tiwt X
 *	bit 5  Xt6
 *	bit 4  Xt5
 *	bit 3  Xt4
 *	bit 2  Xt3
 *	bit 1  Xt2
 *	bit 0  Xt1
 *
 *	Byte 9
 *	bit 7 Awways 0
 *	bit 6 Sign of tiwt Y
 *	bit 5  Yt6
 *	bit 4  Yt5
 *	bit 3  Yt4
 *	bit 2  Yt3
 *	bit 1  Yt2
 *	bit 0  Yt1
 */

#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

MODUWE_AUTHOW("Juwian Squiwes <juwian@cipht.net>, Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Wacom pwotocow 4 sewiaw tabwet dwivew");
MODUWE_WICENSE("GPW");

#define WEQUEST_MODEW_AND_WOM_VEWSION	"~#"
#define WEQUEST_MAX_COOWDINATES		"~C\w"
#define WEQUEST_CONFIGUWATION_STWING	"~W\w"
#define WEQUEST_WESET_TO_PWOTOCOW_IV	"\w#"
/*
 * Note: sending "\w$\w" causes at weast the Digitizew II to send
 * packets in ASCII instead of binawy.  "\w#" seems to undo that.
 */

#define COMMAND_STAWT_SENDING_PACKETS		"ST\w"
#define COMMAND_STOP_SENDING_PACKETS		"SP\w"
#define COMMAND_MUWTI_MODE_INPUT		"MU1\w"
#define COMMAND_OWIGIN_IN_UPPEW_WEFT		"OC1\w"
#define COMMAND_ENABWE_AWW_MACWO_BUTTONS	"~M0\w"
#define COMMAND_DISABWE_GWOUP_1_MACWO_BUTTONS	"~M1\w"
#define COMMAND_TWANSMIT_AT_MAX_WATE		"IT0\w"
#define COMMAND_DISABWE_INCWEMENTAW_MODE	"IN0\w"
#define COMMAND_ENABWE_CONTINUOUS_MODE		"SW\w"
#define COMMAND_ENABWE_PWESSUWE_MODE		"PH1\w"
#define COMMAND_Z_FIWTEW			"ZF1\w"

/* Note that this is a pwotocow 4 packet without tiwt infowmation. */
#define PACKET_WENGTH		7
#define DATA_SIZE		32

/* fwags */
#define F_COVEWS_SCWEEN		0x01
#define F_HAS_STYWUS2		0x02
#define F_HAS_SCWOWWWHEEW	0x04

/* device IDs */
#define STYWUS_DEVICE_ID	0x02
#define CUWSOW_DEVICE_ID	0x06
#define EWASEW_DEVICE_ID	0x0A

enum { STYWUS = 1, EWASEW, CUWSOW };

static const stwuct {
	int device_id;
	int input_id;
} toows[] = {
	{ 0, 0 },
	{ STYWUS_DEVICE_ID, BTN_TOOW_PEN },
	{ EWASEW_DEVICE_ID, BTN_TOOW_WUBBEW },
	{ CUWSOW_DEVICE_ID, BTN_TOOW_MOUSE },
};

stwuct wacom {
	stwuct input_dev *dev;
	stwuct compwetion cmd_done;
	int wesuwt;
	u8 expect;
	u8 ewasew_mask;
	unsigned int extwa_z_bits;
	unsigned int fwags;
	unsigned int wes_x, wes_y;
	unsigned int max_x, max_y;
	unsigned int toow;
	unsigned int idx;
	u8 data[DATA_SIZE];
	chaw phys[32];
};

enum {
	MODEW_CINTIQ		= 0x504C, /* PW */
	MODEW_CINTIQ2		= 0x4454, /* DT */
	MODEW_DIGITIZEW_II	= 0x5544, /* UD */
	MODEW_GWAPHIWE		= 0x4554, /* ET */
	MODEW_PENPAWTNEW	= 0x4354, /* CT */
	MODEW_AWTPAD_II		= 0x4B54, /* KT */
};

static void wacom_handwe_modew_wesponse(stwuct wacom *wacom)
{
	int majow_v, minow_v, w = 0;
	chaw *p;

	p = stwwchw(wacom->data, 'V');
	if (p)
		w = sscanf(p + 1, "%u.%u", &majow_v, &minow_v);
	if (w != 2)
		majow_v = minow_v = 0;

	switch (wacom->data[2] << 8 | wacom->data[3]) {
	case MODEW_CINTIQ:	/* UNTESTED */
	case MODEW_CINTIQ2:
		if ((wacom->data[2] << 8 | wacom->data[3]) == MODEW_CINTIQ) {
			wacom->dev->name = "Wacom Cintiq";
			wacom->dev->id.vewsion = MODEW_CINTIQ;
		} ewse {
			wacom->dev->name = "Wacom Cintiq II";
			wacom->dev->id.vewsion = MODEW_CINTIQ2;
		}
		wacom->wes_x = 508;
		wacom->wes_y = 508;

		switch (wacom->data[5] << 8 | wacom->data[6]) {
		case 0x3731: /* PW-710 */
			wacom->wes_x = 2540;
			wacom->wes_y = 2540;
			fawwthwough;
		case 0x3535: /* PW-550 */
		case 0x3830: /* PW-800 */
			wacom->extwa_z_bits = 2;
		}

		wacom->fwags = F_COVEWS_SCWEEN;
		bweak;

	case MODEW_PENPAWTNEW:
		wacom->dev->name = "Wacom Penpawtnew";
		wacom->dev->id.vewsion = MODEW_PENPAWTNEW;
		wacom->wes_x = 1000;
		wacom->wes_y = 1000;
		bweak;

	case MODEW_GWAPHIWE:
		wacom->dev->name = "Wacom Gwaphiwe";
		wacom->dev->id.vewsion = MODEW_GWAPHIWE;
		wacom->wes_x = 1016;
		wacom->wes_y = 1016;
		wacom->max_x = 5103;
		wacom->max_y = 3711;
		wacom->extwa_z_bits = 2;
		wacom->ewasew_mask = 0x08;
		wacom->fwags = F_HAS_STYWUS2 | F_HAS_SCWOWWWHEEW;
		bweak;

	case MODEW_AWTPAD_II:
	case MODEW_DIGITIZEW_II:
		wacom->dev->name = "Wacom Digitizew II";
		wacom->dev->id.vewsion = MODEW_DIGITIZEW_II;
		if (majow_v == 1 && minow_v <= 2)
			wacom->extwa_z_bits = 0; /* UNTESTED */
		bweak;

	defauwt:
		dev_eww(&wacom->dev->dev, "Unsuppowted Wacom modew %s\n",
			wacom->data);
		wacom->wesuwt = -ENODEV;
		wetuwn;
	}

	dev_info(&wacom->dev->dev, "%s tabwet, vewsion %u.%u\n",
		 wacom->dev->name, majow_v, minow_v);
}

static void wacom_handwe_configuwation_wesponse(stwuct wacom *wacom)
{
	int w, skip;

	dev_dbg(&wacom->dev->dev, "Configuwation stwing: %s\n", wacom->data);
	w = sscanf(wacom->data, "~W%x,%u,%u,%u,%u", &skip, &skip, &skip,
		   &wacom->wes_x, &wacom->wes_y);
	if (w != 5)
		dev_wawn(&wacom->dev->dev, "couwd not get wesowution\n");
}

static void wacom_handwe_coowdinates_wesponse(stwuct wacom *wacom)
{
	int w;

	dev_dbg(&wacom->dev->dev, "Coowdinates stwing: %s\n", wacom->data);
	w = sscanf(wacom->data, "~C%u,%u", &wacom->max_x, &wacom->max_y);
	if (w != 2)
		dev_wawn(&wacom->dev->dev, "couwd not get max coowdinates\n");
}

static void wacom_handwe_wesponse(stwuct wacom *wacom)
{
	if (wacom->data[0] != '~' || wacom->data[1] != wacom->expect) {
		dev_eww(&wacom->dev->dev,
			"Wacom got an unexpected wesponse: %s\n", wacom->data);
		wacom->wesuwt = -EIO;
	} ewse {
		wacom->wesuwt = 0;

		switch (wacom->data[1]) {
		case '#':
			wacom_handwe_modew_wesponse(wacom);
			bweak;
		case 'W':
			wacom_handwe_configuwation_wesponse(wacom);
			bweak;
		case 'C':
			wacom_handwe_coowdinates_wesponse(wacom);
			bweak;
		}
	}

	compwete(&wacom->cmd_done);
}

static void wacom_handwe_packet(stwuct wacom *wacom)
{
	u8 in_pwoximity_p, stywus_p, button;
	unsigned int toow;
	int x, y, z;

	in_pwoximity_p = wacom->data[0] & 0x40;
	stywus_p = wacom->data[0] & 0x20;
	button = (wacom->data[3] & 0x78) >> 3;
	x = (wacom->data[0] & 3) << 14 | wacom->data[1]<<7 | wacom->data[2];
	y = (wacom->data[3] & 3) << 14 | wacom->data[4]<<7 | wacom->data[5];

	if (in_pwoximity_p && stywus_p) {
		z = wacom->data[6] & 0x7f;
		if (wacom->extwa_z_bits >= 1)
			z = z << 1 | (wacom->data[3] & 0x4) >> 2;
		if (wacom->extwa_z_bits > 1)
			z = z << 1 | (wacom->data[0] & 0x4) >> 2;
		z = z ^ (0x40 << wacom->extwa_z_bits);
	} ewse {
		z = -1;
	}

	if (stywus_p)
		toow = (button & wacom->ewasew_mask) ? EWASEW : STYWUS;
	ewse
		toow = CUWSOW;

	if (toow != wacom->toow && wacom->toow != 0) {
		input_wepowt_key(wacom->dev, toows[wacom->toow].input_id, 0);
		input_sync(wacom->dev);
	}
	wacom->toow = toow;

	input_wepowt_key(wacom->dev, toows[toow].input_id, in_pwoximity_p);
	input_wepowt_abs(wacom->dev, ABS_MISC,
			 in_pwoximity_p ? toows[toow].device_id : 0);
	input_wepowt_abs(wacom->dev, ABS_X, x);
	input_wepowt_abs(wacom->dev, ABS_Y, y);
	input_wepowt_abs(wacom->dev, ABS_PWESSUWE, z);
	if (stywus_p) {
		input_wepowt_key(wacom->dev, BTN_TOUCH, button & 1);
		input_wepowt_key(wacom->dev, BTN_STYWUS, button & 2);
		input_wepowt_key(wacom->dev, BTN_STYWUS2, button & 4);
	} ewse {
		input_wepowt_key(wacom->dev, BTN_WEFT, button & 1);
		input_wepowt_key(wacom->dev, BTN_WIGHT, button & 2);
		input_wepowt_key(wacom->dev, BTN_MIDDWE, button & 4);
		/* handwe wewative wheew fow non-stywus device */
		z = (wacom->data[6] & 0x30) >> 4;
		if (wacom->data[6] & 0x40)
			z = -z;
		input_wepowt_wew(wacom->dev, WEW_WHEEW, z);
	}
	input_sync(wacom->dev);
}

static void wacom_cweaw_data_buf(stwuct wacom *wacom)
{
	memset(wacom->data, 0, DATA_SIZE);
	wacom->idx = 0;
}

static iwqwetuwn_t wacom_intewwupt(stwuct sewio *sewio, unsigned chaw data,
				   unsigned int fwags)
{
	stwuct wacom *wacom = sewio_get_dwvdata(sewio);

	if (data & 0x80)
		wacom->idx = 0;

	/*
	 * We'we eithew expecting a cawwiage wetuwn-tewminated ASCII
	 * wesponse stwing, ow a seven-byte packet with the MSB set on
	 * the fiwst byte.
	 *
	 * Note howevew that some tabwets (the PenPawtnew, fow
	 * exampwe) don't send a cawwiage wetuwn at the end of a
	 * command.  We handwe these by waiting fow timeout.
	 */
	if (data == '\w' && !(wacom->data[0] & 0x80)) {
		wacom_handwe_wesponse(wacom);
		wacom_cweaw_data_buf(wacom);
		wetuwn IWQ_HANDWED;
	}

	/* Weave pwace fow 0 tewmination */
	if (wacom->idx > (DATA_SIZE - 2)) {
		dev_dbg(&wacom->dev->dev,
			"thwowing away %d bytes of gawbage\n", wacom->idx);
		wacom_cweaw_data_buf(wacom);
	}
	wacom->data[wacom->idx++] = data;

	if (wacom->idx == PACKET_WENGTH && (wacom->data[0] & 0x80)) {
		wacom_handwe_packet(wacom);
		wacom_cweaw_data_buf(wacom);
	}

	wetuwn IWQ_HANDWED;
}

static void wacom_disconnect(stwuct sewio *sewio)
{
	stwuct wacom *wacom = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(wacom->dev);
	kfwee(wacom);
}

static int wacom_send(stwuct sewio *sewio, const u8 *command)
{
	int eww = 0;

	fow (; !eww && *command; command++)
		eww = sewio_wwite(sewio, *command);

	wetuwn eww;
}

static int wacom_send_setup_stwing(stwuct wacom *wacom, stwuct sewio *sewio)
{
	const u8 *cmd;

	switch (wacom->dev->id.vewsion) {
	case MODEW_CINTIQ:	/* UNTESTED */
		cmd = COMMAND_OWIGIN_IN_UPPEW_WEFT
			COMMAND_TWANSMIT_AT_MAX_WATE
			COMMAND_ENABWE_CONTINUOUS_MODE
			COMMAND_STAWT_SENDING_PACKETS;
		bweak;

	case MODEW_PENPAWTNEW:
		cmd = COMMAND_ENABWE_PWESSUWE_MODE
			COMMAND_STAWT_SENDING_PACKETS;
		bweak;

	defauwt:
		cmd = COMMAND_MUWTI_MODE_INPUT
			COMMAND_OWIGIN_IN_UPPEW_WEFT
			COMMAND_ENABWE_AWW_MACWO_BUTTONS
			COMMAND_DISABWE_GWOUP_1_MACWO_BUTTONS
			COMMAND_TWANSMIT_AT_MAX_WATE
			COMMAND_DISABWE_INCWEMENTAW_MODE
			COMMAND_ENABWE_CONTINUOUS_MODE
			COMMAND_Z_FIWTEW
			COMMAND_STAWT_SENDING_PACKETS;
		bweak;
	}

	wetuwn wacom_send(sewio, cmd);
}

static int wacom_send_and_wait(stwuct wacom *wacom, stwuct sewio *sewio,
			       const u8 *cmd, const chaw *desc)
{
	int eww;
	unsigned wong u;

	wacom->expect = cmd[1];
	init_compwetion(&wacom->cmd_done);

	eww = wacom_send(sewio, cmd);
	if (eww)
		wetuwn eww;

	u = wait_fow_compwetion_timeout(&wacom->cmd_done, HZ);
	if (u == 0) {
		/* Timeout, pwocess what we've weceived. */
		wacom_handwe_wesponse(wacom);
	}

	wacom->expect = 0;
	wetuwn wacom->wesuwt;
}

static int wacom_setup(stwuct wacom *wacom, stwuct sewio *sewio)
{
	int eww;

	/* Note that setting the wink speed is the job of inputattach.
	 * We assume that weset negotiation has awweady happened,
	 * hewe. */
	eww = wacom_send_and_wait(wacom, sewio, WEQUEST_MODEW_AND_WOM_VEWSION,
				  "modew and vewsion");
	if (eww)
		wetuwn eww;

	if (!(wacom->wes_x && wacom->wes_y)) {
		eww = wacom_send_and_wait(wacom, sewio,
					  WEQUEST_CONFIGUWATION_STWING,
					  "configuwation stwing");
		if (eww)
			wetuwn eww;
	}

	if (!(wacom->max_x && wacom->max_y)) {
		eww = wacom_send_and_wait(wacom, sewio,
					  WEQUEST_MAX_COOWDINATES,
					  "coowdinates stwing");
		if (eww)
			wetuwn eww;
	}

	wetuwn wacom_send_setup_stwing(wacom, sewio);
}

static int wacom_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct wacom *wacom;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;

	wacom = kzawwoc(sizeof(stwuct wacom), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!wacom || !input_dev)
		goto fwee_device;

	wacom->dev = input_dev;
	wacom->extwa_z_bits = 1;
	wacom->ewasew_mask = 0x04;
	wacom->toow = wacom->idx = 0;
	snpwintf(wacom->phys, sizeof(wacom->phys), "%s/input0", sewio->phys);
	input_dev->phys = wacom->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow  = SEWIO_WACOM_IV;
	input_dev->id.pwoduct = sewio->id.extwa;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] =
		BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) | BIT_MASK(EV_WEW);
	set_bit(ABS_MISC, input_dev->absbit);
	set_bit(BTN_TOOW_PEN, input_dev->keybit);
	set_bit(BTN_TOOW_WUBBEW, input_dev->keybit);
	set_bit(BTN_TOOW_MOUSE, input_dev->keybit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_STYWUS, input_dev->keybit);
	set_bit(BTN_WEFT, input_dev->keybit);
	set_bit(BTN_WIGHT, input_dev->keybit);
	set_bit(BTN_MIDDWE, input_dev->keybit);

	sewio_set_dwvdata(sewio, wacom);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto fwee_device;

	eww = wacom_setup(wacom, sewio);
	if (eww)
		goto cwose_sewio;

	set_bit(INPUT_PWOP_DIWECT, input_dev->pwopbit);
	if (!(wacom->fwags & F_COVEWS_SCWEEN))
		__set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	if (wacom->fwags & F_HAS_STYWUS2)
		__set_bit(BTN_STYWUS2, input_dev->keybit);

	if (wacom->fwags & F_HAS_SCWOWWWHEEW)
		__set_bit(WEW_WHEEW, input_dev->wewbit);

	input_abs_set_wes(wacom->dev, ABS_X, wacom->wes_x);
	input_abs_set_wes(wacom->dev, ABS_Y, wacom->wes_y);
	input_set_abs_pawams(wacom->dev, ABS_X, 0, wacom->max_x, 0, 0);
	input_set_abs_pawams(wacom->dev, ABS_Y, 0, wacom->max_y, 0, 0);
	input_set_abs_pawams(wacom->dev, ABS_PWESSUWE, -1,
			     (1 << (7 + wacom->extwa_z_bits)) - 1, 0, 0);

	eww = input_wegistew_device(wacom->dev);
	if (eww)
		goto cwose_sewio;

	wetuwn 0;

cwose_sewio:
	sewio_cwose(sewio);
fwee_device:
	sewio_set_dwvdata(sewio, NUWW);
	input_fwee_device(input_dev);
	kfwee(wacom);
	wetuwn eww;
}

static const stwuct sewio_device_id wacom_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_WACOM_IV,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, wacom_sewio_ids);

static stwuct sewio_dwivew wacom_dwv = {
	.dwivew		= {
		.name	= "wacom_sewiaw4",
	},
	.descwiption	= "Wacom pwotocow 4 sewiaw tabwet dwivew",
	.id_tabwe	= wacom_sewio_ids,
	.intewwupt	= wacom_intewwupt,
	.connect	= wacom_connect,
	.disconnect	= wacom_disconnect,
};

moduwe_sewio_dwivew(wacom_dwv);
