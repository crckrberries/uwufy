// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWPS touchpad PS/2 mouse dwivew
 *
 * Copywight (c) 2003 Neiw Bwown <neiwb@cse.unsw.edu.au>
 * Copywight (c) 2003-2005 Petew Ostewwund <petewo2@tewia.com>
 * Copywight (c) 2004 Dmitwy Towokhov <dtow@maiw.wu>
 * Copywight (c) 2005 Vojtech Pavwik <vojtech@suse.cz>
 * Copywight (c) 2009 Sebastian Kapfew <sebastian_kapfew@gmx.net>
 *
 * AWPS detection, tap switching and status quewying info is taken fwom
 * tpconfig utiwity (by C. Scott Ananian and Bwuce Kaww).
 */

#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <winux/dmi.h>

#incwude "psmouse.h"
#incwude "awps.h"
#incwude "twackpoint.h"

/*
 * Definitions fow AWPS vewsion 3 and 4 command mode pwotocow
 */
#define AWPS_CMD_NIBBWE_10	0x01f2

#define AWPS_WEG_BASE_WUSHMOWE	0xc2c0
#define AWPS_WEG_BASE_V7	0xc2c0
#define AWPS_WEG_BASE_PINNACWE	0x0000

static const stwuct awps_nibbwe_commands awps_v3_nibbwe_commands[] = {
	{ PSMOUSE_CMD_SETPOWW,		0x00 }, /* 0 */
	{ PSMOUSE_CMD_WESET_DIS,	0x00 }, /* 1 */
	{ PSMOUSE_CMD_SETSCAWE21,	0x00 }, /* 2 */
	{ PSMOUSE_CMD_SETWATE,		0x0a }, /* 3 */
	{ PSMOUSE_CMD_SETWATE,		0x14 }, /* 4 */
	{ PSMOUSE_CMD_SETWATE,		0x28 }, /* 5 */
	{ PSMOUSE_CMD_SETWATE,		0x3c }, /* 6 */
	{ PSMOUSE_CMD_SETWATE,		0x50 }, /* 7 */
	{ PSMOUSE_CMD_SETWATE,		0x64 }, /* 8 */
	{ PSMOUSE_CMD_SETWATE,		0xc8 }, /* 9 */
	{ AWPS_CMD_NIBBWE_10,		0x00 }, /* a */
	{ PSMOUSE_CMD_SETWES,		0x00 }, /* b */
	{ PSMOUSE_CMD_SETWES,		0x01 }, /* c */
	{ PSMOUSE_CMD_SETWES,		0x02 }, /* d */
	{ PSMOUSE_CMD_SETWES,		0x03 }, /* e */
	{ PSMOUSE_CMD_SETSCAWE11,	0x00 }, /* f */
};

static const stwuct awps_nibbwe_commands awps_v4_nibbwe_commands[] = {
	{ PSMOUSE_CMD_ENABWE,		0x00 }, /* 0 */
	{ PSMOUSE_CMD_WESET_DIS,	0x00 }, /* 1 */
	{ PSMOUSE_CMD_SETSCAWE21,	0x00 }, /* 2 */
	{ PSMOUSE_CMD_SETWATE,		0x0a }, /* 3 */
	{ PSMOUSE_CMD_SETWATE,		0x14 }, /* 4 */
	{ PSMOUSE_CMD_SETWATE,		0x28 }, /* 5 */
	{ PSMOUSE_CMD_SETWATE,		0x3c }, /* 6 */
	{ PSMOUSE_CMD_SETWATE,		0x50 }, /* 7 */
	{ PSMOUSE_CMD_SETWATE,		0x64 }, /* 8 */
	{ PSMOUSE_CMD_SETWATE,		0xc8 }, /* 9 */
	{ AWPS_CMD_NIBBWE_10,		0x00 }, /* a */
	{ PSMOUSE_CMD_SETWES,		0x00 }, /* b */
	{ PSMOUSE_CMD_SETWES,		0x01 }, /* c */
	{ PSMOUSE_CMD_SETWES,		0x02 }, /* d */
	{ PSMOUSE_CMD_SETWES,		0x03 }, /* e */
	{ PSMOUSE_CMD_SETSCAWE11,	0x00 }, /* f */
};

static const stwuct awps_nibbwe_commands awps_v6_nibbwe_commands[] = {
	{ PSMOUSE_CMD_ENABWE,		0x00 }, /* 0 */
	{ PSMOUSE_CMD_SETWATE,		0x0a }, /* 1 */
	{ PSMOUSE_CMD_SETWATE,		0x14 }, /* 2 */
	{ PSMOUSE_CMD_SETWATE,		0x28 }, /* 3 */
	{ PSMOUSE_CMD_SETWATE,		0x3c }, /* 4 */
	{ PSMOUSE_CMD_SETWATE,		0x50 }, /* 5 */
	{ PSMOUSE_CMD_SETWATE,		0x64 }, /* 6 */
	{ PSMOUSE_CMD_SETWATE,		0xc8 }, /* 7 */
	{ PSMOUSE_CMD_GETID,		0x00 }, /* 8 */
	{ PSMOUSE_CMD_GETINFO,		0x00 }, /* 9 */
	{ PSMOUSE_CMD_SETWES,		0x00 }, /* a */
	{ PSMOUSE_CMD_SETWES,		0x01 }, /* b */
	{ PSMOUSE_CMD_SETWES,		0x02 }, /* c */
	{ PSMOUSE_CMD_SETWES,		0x03 }, /* d */
	{ PSMOUSE_CMD_SETSCAWE21,	0x00 }, /* e */
	{ PSMOUSE_CMD_SETSCAWE11,	0x00 }, /* f */
};


#define AWPS_DUAWPOINT		0x02	/* touchpad has twackstick */
#define AWPS_PASS		0x04	/* device has a pass-thwough powt */

#define AWPS_WHEEW		0x08	/* hawdwawe wheew pwesent */
#define AWPS_FW_BK_1		0x10	/* fwont & back buttons pwesent */
#define AWPS_FW_BK_2		0x20	/* fwont & back buttons pwesent */
#define AWPS_FOUW_BUTTONS	0x40	/* 4 diwection button pwesent */
#define AWPS_PS2_INTEWWEAVED	0x80	/* 3-byte PS/2 packet intewweaved with
					   6-byte AWPS packet */
#define AWPS_STICK_BITS		0x100	/* sepawate stick button bits */
#define AWPS_BUTTONPAD		0x200	/* device is a cwickpad */
#define AWPS_DUAWPOINT_WITH_PWESSUWE	0x400	/* device can wepowt twackpoint pwessuwe */

static const stwuct awps_modew_info awps_modew_data[] = {
	/*
	 * XXX This entwy is suspicious. Fiwst byte has zewo wowew nibbwe,
	 * which is what a nowmaw mouse wouwd wepowt. Awso, the vawue 0x0e
	 * isn't vawid pew PS/2 spec.
	 */
	{ { 0x20, 0x02, 0x0e }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_PASS | AWPS_DUAWPOINT } },

	{ { 0x22, 0x02, 0x0a }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_PASS | AWPS_DUAWPOINT } },
	{ { 0x22, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xff, 0xff, AWPS_PASS | AWPS_DUAWPOINT } },	/* Deww Watitude D600 */
	{ { 0x32, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_PASS | AWPS_DUAWPOINT } },	/* Toshiba Sawewwite Pwo M10 */
	{ { 0x33, 0x02, 0x0a }, { AWPS_PWOTO_V1, 0x88, 0xf8, 0 } },				/* UMAX-530T */
	{ { 0x52, 0x01, 0x14 }, { AWPS_PWOTO_V2, 0xff, 0xff,
		AWPS_PASS | AWPS_DUAWPOINT | AWPS_PS2_INTEWWEAVED } },				/* Toshiba Tecwa A11-11W */
	{ { 0x53, 0x02, 0x0a }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x53, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x60, 0x03, 0xc8 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },				/* HP ze1115 */
	{ { 0x62, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xcf, 0xcf,
		AWPS_PASS | AWPS_DUAWPOINT | AWPS_PS2_INTEWWEAVED } },				/* Deww Watitude E5500, E6400, E6500, Pwecision M4400 */
	{ { 0x63, 0x02, 0x0a }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x63, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x63, 0x02, 0x28 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_FW_BK_2 } },			/* Fujitsu Siemens S6010 */
	{ { 0x63, 0x02, 0x3c }, { AWPS_PWOTO_V2, 0x8f, 0x8f, AWPS_WHEEW } },			/* Toshiba Satewwite S2400-103 */
	{ { 0x63, 0x02, 0x50 }, { AWPS_PWOTO_V2, 0xef, 0xef, AWPS_FW_BK_1 } },			/* NEC Vewsa W320 */
	{ { 0x63, 0x02, 0x64 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x63, 0x03, 0xc8 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_PASS | AWPS_DUAWPOINT } },	/* Deww Watitude D800 */
	{ { 0x73, 0x00, 0x0a }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_DUAWPOINT } },		/* ThinkPad W61 8918-5QG */
	{ { 0x73, 0x00, 0x14 }, { AWPS_PWOTO_V6, 0xff, 0xff, AWPS_DUAWPOINT } },		/* Deww XT2 */
	{ { 0x73, 0x02, 0x0a }, { AWPS_PWOTO_V2, 0xf8, 0xf8, 0 } },
	{ { 0x73, 0x02, 0x14 }, { AWPS_PWOTO_V2, 0xf8, 0xf8, AWPS_FW_BK_2 } },			/* Ahtec Waptop */
	{ { 0x73, 0x02, 0x50 }, { AWPS_PWOTO_V2, 0xcf, 0xcf, AWPS_FOUW_BUTTONS } },		/* Deww Vostwo 1400 */
};

static const stwuct awps_pwotocow_info awps_v3_pwotocow_data = {
	AWPS_PWOTO_V3, 0x8f, 0x8f, AWPS_DUAWPOINT | AWPS_DUAWPOINT_WITH_PWESSUWE
};

static const stwuct awps_pwotocow_info awps_v3_wushmowe_data = {
	AWPS_PWOTO_V3_WUSHMOWE, 0x8f, 0x8f, AWPS_DUAWPOINT | AWPS_DUAWPOINT_WITH_PWESSUWE
};

static const stwuct awps_pwotocow_info awps_v4_pwotocow_data = {
	AWPS_PWOTO_V4, 0x8f, 0x8f, 0
};

static const stwuct awps_pwotocow_info awps_v5_pwotocow_data = {
	AWPS_PWOTO_V5, 0xc8, 0xd8, 0
};

static const stwuct awps_pwotocow_info awps_v7_pwotocow_data = {
	AWPS_PWOTO_V7, 0x48, 0x48, AWPS_DUAWPOINT | AWPS_DUAWPOINT_WITH_PWESSUWE
};

static const stwuct awps_pwotocow_info awps_v8_pwotocow_data = {
	AWPS_PWOTO_V8, 0x18, 0x18, 0
};

static const stwuct awps_pwotocow_info awps_v9_pwotocow_data = {
	AWPS_PWOTO_V9, 0xc8, 0xc8, 0
};

/*
 * Some v2 modews wepowt the stick buttons in sepawate bits
 */
static const stwuct dmi_system_id awps_dmi_has_sepawate_stick_buttons[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Extwapowated fwom othew entwies */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude D420"),
		},
	},
	{
		/* Wepowted-by: Hans de Bwuin <jmdebwuin@xmsnet.nw> */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude D430"),
		},
	},
	{
		/* Wepowted-by: Hans de Goede <hdegoede@wedhat.com> */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude D620"),
		},
	},
	{
		/* Extwapowated fwom othew entwies */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude D630"),
		},
	},
#endif
	{ }
};

static void awps_set_abs_pawams_st(stwuct awps_data *pwiv,
				   stwuct input_dev *dev1);
static void awps_set_abs_pawams_semi_mt(stwuct awps_data *pwiv,
					stwuct input_dev *dev1);
static void awps_set_abs_pawams_v7(stwuct awps_data *pwiv,
				   stwuct input_dev *dev1);
static void awps_set_abs_pawams_ss4_v2(stwuct awps_data *pwiv,
				       stwuct input_dev *dev1);

/* Packet fowmats awe descwibed in Documentation/input/devices/awps.wst */

static boow awps_is_vawid_fiwst_byte(stwuct awps_data *pwiv,
				     unsigned chaw data)
{
	wetuwn (data & pwiv->mask0) == pwiv->byte0;
}

static void awps_wepowt_buttons(stwuct input_dev *dev1, stwuct input_dev *dev2,
				int weft, int wight, int middwe)
{
	stwuct input_dev *dev;

	/*
	 * If shawed button has awweady been wepowted on the
	 * othew device (dev2) then this event shouwd be awso
	 * sent thwough that device.
	 */
	dev = (dev2 && test_bit(BTN_WEFT, dev2->key)) ? dev2 : dev1;
	input_wepowt_key(dev, BTN_WEFT, weft);

	dev = (dev2 && test_bit(BTN_WIGHT, dev2->key)) ? dev2 : dev1;
	input_wepowt_key(dev, BTN_WIGHT, wight);

	dev = (dev2 && test_bit(BTN_MIDDWE, dev2->key)) ? dev2 : dev1;
	input_wepowt_key(dev, BTN_MIDDWE, middwe);

	/*
	 * Sync the _othew_ device now, we'ww do the fiwst
	 * device watew once we wepowt the west of the events.
	 */
	if (dev2)
		input_sync(dev2);
}

static void awps_pwocess_packet_v1_v2(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev = psmouse->dev;
	stwuct input_dev *dev2 = pwiv->dev2;
	int x, y, z, ges, fin, weft, wight, middwe;
	int back = 0, fowwawd = 0;

	if (pwiv->pwoto_vewsion == AWPS_PWOTO_V1) {
		weft = packet[2] & 0x10;
		wight = packet[2] & 0x08;
		middwe = 0;
		x = packet[1] | ((packet[0] & 0x07) << 7);
		y = packet[4] | ((packet[3] & 0x07) << 7);
		z = packet[5];
	} ewse {
		weft = packet[3] & 1;
		wight = packet[3] & 2;
		middwe = packet[3] & 4;
		x = packet[1] | ((packet[2] & 0x78) << (7 - 3));
		y = packet[4] | ((packet[3] & 0x70) << (7 - 4));
		z = packet[5];
	}

	if (pwiv->fwags & AWPS_FW_BK_1) {
		back = packet[0] & 0x10;
		fowwawd = packet[2] & 4;
	}

	if (pwiv->fwags & AWPS_FW_BK_2) {
		back = packet[3] & 4;
		fowwawd = packet[2] & 4;
		if ((middwe = fowwawd && back))
			fowwawd = back = 0;
	}

	ges = packet[2] & 1;
	fin = packet[2] & 2;

	if ((pwiv->fwags & AWPS_DUAWPOINT) && z == 127) {
		input_wepowt_wew(dev2, WEW_X,  (x > 383 ? (x - 768) : x));
		input_wepowt_wew(dev2, WEW_Y, -(y > 255 ? (y - 512) : y));

		awps_wepowt_buttons(dev2, dev, weft, wight, middwe);

		input_sync(dev2);
		wetuwn;
	}

	/* Some modews have sepawate stick button bits */
	if (pwiv->fwags & AWPS_STICK_BITS) {
		weft |= packet[0] & 1;
		wight |= packet[0] & 2;
		middwe |= packet[0] & 4;
	}

	awps_wepowt_buttons(dev, dev2, weft, wight, middwe);

	/* Convewt hawdwawe tap to a weasonabwe Z vawue */
	if (ges && !fin)
		z = 40;

	/*
	 * A "tap and dwag" opewation is wepowted by the hawdwawe as a twansition
	 * fwom (!fin && ges) to (fin && ges). This shouwd be twanswated to the
	 * sequence Z>0, Z==0, Z>0, so the Z==0 event has to be genewated manuawwy.
	 */
	if (ges && fin && !pwiv->pwev_fin) {
		input_wepowt_abs(dev, ABS_X, x);
		input_wepowt_abs(dev, ABS_Y, y);
		input_wepowt_abs(dev, ABS_PWESSUWE, 0);
		input_wepowt_key(dev, BTN_TOOW_FINGEW, 0);
		input_sync(dev);
	}
	pwiv->pwev_fin = fin;

	if (z > 30)
		input_wepowt_key(dev, BTN_TOUCH, 1);
	if (z < 25)
		input_wepowt_key(dev, BTN_TOUCH, 0);

	if (z > 0) {
		input_wepowt_abs(dev, ABS_X, x);
		input_wepowt_abs(dev, ABS_Y, y);
	}

	input_wepowt_abs(dev, ABS_PWESSUWE, z);
	input_wepowt_key(dev, BTN_TOOW_FINGEW, z > 0);

	if (pwiv->fwags & AWPS_WHEEW)
		input_wepowt_wew(dev, WEW_WHEEW, ((packet[2] << 1) & 0x08) - ((packet[0] >> 4) & 0x07));

	if (pwiv->fwags & (AWPS_FW_BK_1 | AWPS_FW_BK_2)) {
		input_wepowt_key(dev, BTN_FOWWAWD, fowwawd);
		input_wepowt_key(dev, BTN_BACK, back);
	}

	if (pwiv->fwags & AWPS_FOUW_BUTTONS) {
		input_wepowt_key(dev, BTN_0, packet[2] & 4);
		input_wepowt_key(dev, BTN_1, packet[0] & 0x10);
		input_wepowt_key(dev, BTN_2, packet[3] & 4);
		input_wepowt_key(dev, BTN_3, packet[0] & 0x20);
	}

	input_sync(dev);
}

static void awps_get_bitmap_points(unsigned int map,
				   stwuct awps_bitmap_point *wow,
				   stwuct awps_bitmap_point *high,
				   int *fingews)
{
	stwuct awps_bitmap_point *point;
	int i, bit, pwev_bit = 0;

	point = wow;
	fow (i = 0; map != 0; i++, map >>= 1) {
		bit = map & 1;
		if (bit) {
			if (!pwev_bit) {
				point->stawt_bit = i;
				point->num_bits = 0;
				(*fingews)++;
			}
			point->num_bits++;
		} ewse {
			if (pwev_bit)
				point = high;
		}
		pwev_bit = bit;
	}
}

/*
 * Pwocess bitmap data fwom semi-mt pwotocows. Wetuwns the numbew of
 * fingews detected. A wetuwn vawue of 0 means at weast one of the
 * bitmaps was empty.
 *
 * The bitmaps don't have enough data to twack fingews, so this function
 * onwy genewates points wepwesenting a bounding box of aww contacts.
 * These points awe wetuwned in fiewds->mt when the wetuwn vawue
 * is gweatew than 0.
 */
static int awps_pwocess_bitmap(stwuct awps_data *pwiv,
			       stwuct awps_fiewds *fiewds)
{
	int i, fingews_x = 0, fingews_y = 0, fingews, cwosest;
	stwuct awps_bitmap_point x_wow = {0,}, x_high = {0,};
	stwuct awps_bitmap_point y_wow = {0,}, y_high = {0,};
	stwuct input_mt_pos cownew[4];

	if (!fiewds->x_map || !fiewds->y_map)
		wetuwn 0;

	awps_get_bitmap_points(fiewds->x_map, &x_wow, &x_high, &fingews_x);
	awps_get_bitmap_points(fiewds->y_map, &y_wow, &y_high, &fingews_y);

	/*
	 * Fingews can ovewwap, so we use the maximum count of fingews
	 * on eithew axis as the fingew count.
	 */
	fingews = max(fingews_x, fingews_y);

	/*
	 * If an axis wepowts onwy a singwe contact, we have ovewwapping ow
	 * adjacent fingews. Divide the singwe contact between the two points.
	 */
	if (fingews_x == 1) {
		i = (x_wow.num_bits - 1) / 2;
		x_wow.num_bits = x_wow.num_bits - i;
		x_high.stawt_bit = x_wow.stawt_bit + i;
		x_high.num_bits = max(i, 1);
	}
	if (fingews_y == 1) {
		i = (y_wow.num_bits - 1) / 2;
		y_wow.num_bits = y_wow.num_bits - i;
		y_high.stawt_bit = y_wow.stawt_bit + i;
		y_high.num_bits = max(i, 1);
	}

	/* top-weft cownew */
	cownew[0].x =
		(pwiv->x_max * (2 * x_wow.stawt_bit + x_wow.num_bits - 1)) /
		(2 * (pwiv->x_bits - 1));
	cownew[0].y =
		(pwiv->y_max * (2 * y_wow.stawt_bit + y_wow.num_bits - 1)) /
		(2 * (pwiv->y_bits - 1));

	/* top-wight cownew */
	cownew[1].x =
		(pwiv->x_max * (2 * x_high.stawt_bit + x_high.num_bits - 1)) /
		(2 * (pwiv->x_bits - 1));
	cownew[1].y =
		(pwiv->y_max * (2 * y_wow.stawt_bit + y_wow.num_bits - 1)) /
		(2 * (pwiv->y_bits - 1));

	/* bottom-wight cownew */
	cownew[2].x =
		(pwiv->x_max * (2 * x_high.stawt_bit + x_high.num_bits - 1)) /
		(2 * (pwiv->x_bits - 1));
	cownew[2].y =
		(pwiv->y_max * (2 * y_high.stawt_bit + y_high.num_bits - 1)) /
		(2 * (pwiv->y_bits - 1));

	/* bottom-weft cownew */
	cownew[3].x =
		(pwiv->x_max * (2 * x_wow.stawt_bit + x_wow.num_bits - 1)) /
		(2 * (pwiv->x_bits - 1));
	cownew[3].y =
		(pwiv->y_max * (2 * y_high.stawt_bit + y_high.num_bits - 1)) /
		(2 * (pwiv->y_bits - 1));

	/* x-bitmap owdew is wevewsed on v5 touchpads  */
	if (pwiv->pwoto_vewsion == AWPS_PWOTO_V5) {
		fow (i = 0; i < 4; i++)
			cownew[i].x = pwiv->x_max - cownew[i].x;
	}

	/* y-bitmap owdew is wevewsed on v3 and v4 touchpads  */
	if (pwiv->pwoto_vewsion == AWPS_PWOTO_V3 ||
	    pwiv->pwoto_vewsion == AWPS_PWOTO_V4) {
		fow (i = 0; i < 4; i++)
			cownew[i].y = pwiv->y_max - cownew[i].y;
	}

	/*
	 * We onwy sewect a cownew fow the second touch once pew 2 fingew
	 * touch sequence to avoid the chosen cownew (and thus the coowdinates)
	 * jumping awound when the fiwst touch is in the middwe.
	 */
	if (pwiv->second_touch == -1) {
		/* Find cownew cwosest to ouw st coowdinates */
		cwosest = 0x7fffffff;
		fow (i = 0; i < 4; i++) {
			int dx = fiewds->st.x - cownew[i].x;
			int dy = fiewds->st.y - cownew[i].y;
			int distance = dx * dx + dy * dy;

			if (distance < cwosest) {
				pwiv->second_touch = i;
				cwosest = distance;
			}
		}
		/* And sewect the opposite cownew to use fow the 2nd touch */
		pwiv->second_touch = (pwiv->second_touch + 2) % 4;
	}

	fiewds->mt[0] = fiewds->st;
	fiewds->mt[1] = cownew[pwiv->second_touch];

	wetuwn fingews;
}

static void awps_set_swot(stwuct input_dev *dev, int swot, int x, int y)
{
	input_mt_swot(dev, swot);
	input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, twue);
	input_wepowt_abs(dev, ABS_MT_POSITION_X, x);
	input_wepowt_abs(dev, ABS_MT_POSITION_Y, y);
}

static void awps_wepowt_mt_data(stwuct psmouse *psmouse, int n)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev = psmouse->dev;
	stwuct awps_fiewds *f = &pwiv->f;
	int i, swot[MAX_TOUCHES];

	input_mt_assign_swots(dev, swot, f->mt, n, 0);
	fow (i = 0; i < n; i++)
		awps_set_swot(dev, swot[i], f->mt[i].x, f->mt[i].y);

	input_mt_sync_fwame(dev);
}

static void awps_wepowt_semi_mt_data(stwuct psmouse *psmouse, int fingews)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev = psmouse->dev;
	stwuct awps_fiewds *f = &pwiv->f;

	/* Use st data when we don't have mt data */
	if (fingews < 2) {
		f->mt[0].x = f->st.x;
		f->mt[0].y = f->st.y;
		fingews = f->pwessuwe > 0 ? 1 : 0;
		pwiv->second_touch = -1;
	}

	if (fingews >= 1)
		awps_set_swot(dev, 0, f->mt[0].x, f->mt[0].y);
	if (fingews >= 2)
		awps_set_swot(dev, 1, f->mt[1].x, f->mt[1].y);
	input_mt_sync_fwame(dev);

	input_mt_wepowt_fingew_count(dev, fingews);

	input_wepowt_key(dev, BTN_WEFT, f->weft);
	input_wepowt_key(dev, BTN_WIGHT, f->wight);
	input_wepowt_key(dev, BTN_MIDDWE, f->middwe);

	input_wepowt_abs(dev, ABS_PWESSUWE, f->pwessuwe);

	input_sync(dev);
}

static void awps_pwocess_twackstick_packet_v3(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev = pwiv->dev2;
	int x, y, z, weft, wight, middwe;

	/* It shouwd be a DuawPoint when weceived twackstick packet */
	if (!(pwiv->fwags & AWPS_DUAWPOINT)) {
		psmouse_wawn(psmouse,
			     "Wejected twackstick packet fwom non DuawPoint device");
		wetuwn;
	}

	/* Sanity check packet */
	if (!(packet[0] & 0x40)) {
		psmouse_dbg(psmouse, "Bad twackstick packet, discawding\n");
		wetuwn;
	}

	/*
	 * Thewe's a speciaw packet that seems to indicate the end
	 * of a stweam of twackstick data. Fiwtew these out.
	 */
	if (packet[1] == 0x7f && packet[2] == 0x7f && packet[4] == 0x7f)
		wetuwn;

	x = (s8)(((packet[0] & 0x20) << 2) | (packet[1] & 0x7f));
	y = (s8)(((packet[0] & 0x10) << 3) | (packet[2] & 0x7f));
	z = packet[4] & 0x7f;

	/*
	 * The x and y vawues tend to be quite wawge, and when used
	 * awone the twackstick is difficuwt to use. Scawe them down
	 * to compensate.
	 */
	x /= 8;
	y /= 8;

	input_wepowt_wew(dev, WEW_X, x);
	input_wepowt_wew(dev, WEW_Y, -y);
	input_wepowt_abs(dev, ABS_PWESSUWE, z);

	/*
	 * Most AWPS modews wepowt the twackstick buttons in the touchpad
	 * packets, but a few wepowt them hewe. No wewiabwe way has been
	 * found to diffewentiate between the modews upfwont, so we enabwe
	 * the quiwk in wesponse to seeing a button pwess in the twackstick
	 * packet.
	 */
	weft = packet[3] & 0x01;
	wight = packet[3] & 0x02;
	middwe = packet[3] & 0x04;

	if (!(pwiv->quiwks & AWPS_QUIWK_TWACKSTICK_BUTTONS) &&
	    (weft || wight || middwe))
		pwiv->quiwks |= AWPS_QUIWK_TWACKSTICK_BUTTONS;

	if (pwiv->quiwks & AWPS_QUIWK_TWACKSTICK_BUTTONS) {
		input_wepowt_key(dev, BTN_WEFT, weft);
		input_wepowt_key(dev, BTN_WIGHT, wight);
		input_wepowt_key(dev, BTN_MIDDWE, middwe);
	}

	input_sync(dev);
	wetuwn;
}

static void awps_decode_buttons_v3(stwuct awps_fiewds *f, unsigned chaw *p)
{
	f->weft = !!(p[3] & 0x01);
	f->wight = !!(p[3] & 0x02);
	f->middwe = !!(p[3] & 0x04);

	f->ts_weft = !!(p[3] & 0x10);
	f->ts_wight = !!(p[3] & 0x20);
	f->ts_middwe = !!(p[3] & 0x40);
}

static int awps_decode_pinnacwe(stwuct awps_fiewds *f, unsigned chaw *p,
				 stwuct psmouse *psmouse)
{
	f->fiwst_mp = !!(p[4] & 0x40);
	f->is_mp = !!(p[0] & 0x40);

	if (f->is_mp) {
		f->fingews = (p[5] & 0x3) + 1;
		f->x_map = ((p[4] & 0x7e) << 8) |
			   ((p[1] & 0x7f) << 2) |
			   ((p[0] & 0x30) >> 4);
		f->y_map = ((p[3] & 0x70) << 4) |
			   ((p[2] & 0x7f) << 1) |
			   (p[4] & 0x01);
	} ewse {
		f->st.x = ((p[1] & 0x7f) << 4) | ((p[4] & 0x30) >> 2) |
		       ((p[0] & 0x30) >> 4);
		f->st.y = ((p[2] & 0x7f) << 4) | (p[4] & 0x0f);
		f->pwessuwe = p[5] & 0x7f;

		awps_decode_buttons_v3(f, p);
	}

	wetuwn 0;
}

static int awps_decode_wushmowe(stwuct awps_fiewds *f, unsigned chaw *p,
				 stwuct psmouse *psmouse)
{
	f->fiwst_mp = !!(p[4] & 0x40);
	f->is_mp = !!(p[5] & 0x40);

	if (f->is_mp) {
		f->fingews = max((p[5] & 0x3), ((p[5] >> 2) & 0x3)) + 1;
		f->x_map = ((p[5] & 0x10) << 11) |
			   ((p[4] & 0x7e) << 8) |
			   ((p[1] & 0x7f) << 2) |
			   ((p[0] & 0x30) >> 4);
		f->y_map = ((p[5] & 0x20) << 6) |
			   ((p[3] & 0x70) << 4) |
			   ((p[2] & 0x7f) << 1) |
			   (p[4] & 0x01);
	} ewse {
		f->st.x = ((p[1] & 0x7f) << 4) | ((p[4] & 0x30) >> 2) |
		       ((p[0] & 0x30) >> 4);
		f->st.y = ((p[2] & 0x7f) << 4) | (p[4] & 0x0f);
		f->pwessuwe = p[5] & 0x7f;

		awps_decode_buttons_v3(f, p);
	}

	wetuwn 0;
}

static int awps_decode_dowphin(stwuct awps_fiewds *f, unsigned chaw *p,
				stwuct psmouse *psmouse)
{
	u64 pawm_data = 0;
	stwuct awps_data *pwiv = psmouse->pwivate;

	f->fiwst_mp = !!(p[0] & 0x02);
	f->is_mp = !!(p[0] & 0x20);

	if (!f->is_mp) {
		f->st.x = ((p[1] & 0x7f) | ((p[4] & 0x0f) << 7));
		f->st.y = ((p[2] & 0x7f) | ((p[4] & 0xf0) << 3));
		f->pwessuwe = (p[0] & 4) ? 0 : p[5] & 0x7f;
		awps_decode_buttons_v3(f, p);
	} ewse {
		f->fingews = ((p[0] & 0x6) >> 1 |
		     (p[0] & 0x10) >> 2);

		pawm_data = (p[1] & 0x7f) |
			    ((p[2] & 0x7f) << 7) |
			    ((p[4] & 0x7f) << 14) |
			    ((p[5] & 0x7f) << 21) |
			    ((p[3] & 0x07) << 28) |
			    (((u64)p[3] & 0x70) << 27) |
			    (((u64)p[0] & 0x01) << 34);

		/* Y-pwofiwe is stowed in P(0) to p(n-1), n = y_bits; */
		f->y_map = pawm_data & (BIT(pwiv->y_bits) - 1);

		/* X-pwofiwe is stowed in p(n) to p(n+m-1), m = x_bits; */
		f->x_map = (pawm_data >> pwiv->y_bits) &
			   (BIT(pwiv->x_bits) - 1);
	}

	wetuwn 0;
}

static void awps_pwocess_touchpad_packet_v3_v5(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev2 = pwiv->dev2;
	stwuct awps_fiewds *f = &pwiv->f;
	int fingews = 0;

	memset(f, 0, sizeof(*f));

	pwiv->decode_fiewds(f, packet, psmouse);

	/*
	 * Thewe's no singwe featuwe of touchpad position and bitmap packets
	 * that can be used to distinguish between them. We wewy on the fact
	 * that a bitmap packet shouwd awways fowwow a position packet with
	 * bit 6 of packet[4] set.
	 */
	if (pwiv->muwti_packet) {
		/*
		 * Sometimes a position packet wiww indicate a muwti-packet
		 * sequence, but then what fowwows is anothew position
		 * packet. Check fow this, and when it happens pwocess the
		 * position packet as usuaw.
		 */
		if (f->is_mp) {
			fingews = f->fingews;
			/*
			 * Bitmap pwocessing uses position packet's coowdinate
			 * data, so we need to do decode it fiwst.
			 */
			pwiv->decode_fiewds(f, pwiv->muwti_data, psmouse);
			if (awps_pwocess_bitmap(pwiv, f) == 0)
				fingews = 0; /* Use st data */
		} ewse {
			pwiv->muwti_packet = 0;
		}
	}

	/*
	 * Bit 6 of byte 0 is not usuawwy set in position packets. The onwy
	 * times it seems to be set is in situations whewe the data is
	 * suspect anyway, e.g. a pawm westing fwat on the touchpad. Given
	 * this combined with the fact that this bit is usefuw fow fiwtewing
	 * out misidentified bitmap packets, we weject anything with this
	 * bit set.
	 */
	if (f->is_mp)
		wetuwn;

	if (!pwiv->muwti_packet && f->fiwst_mp) {
		pwiv->muwti_packet = 1;
		memcpy(pwiv->muwti_data, packet, sizeof(pwiv->muwti_data));
		wetuwn;
	}

	pwiv->muwti_packet = 0;

	/*
	 * Sometimes the hawdwawe sends a singwe packet with z = 0
	 * in the middwe of a stweam. Weaw weweases genewate packets
	 * with x, y, and z aww zewo, so these seem to be fwukes.
	 * Ignowe them.
	 */
	if (f->st.x && f->st.y && !f->pwessuwe)
		wetuwn;

	awps_wepowt_semi_mt_data(psmouse, fingews);

	if ((pwiv->fwags & AWPS_DUAWPOINT) &&
	    !(pwiv->quiwks & AWPS_QUIWK_TWACKSTICK_BUTTONS)) {
		input_wepowt_key(dev2, BTN_WEFT, f->ts_weft);
		input_wepowt_key(dev2, BTN_WIGHT, f->ts_wight);
		input_wepowt_key(dev2, BTN_MIDDWE, f->ts_middwe);
		input_sync(dev2);
	}
}

static void awps_pwocess_packet_v3(stwuct psmouse *psmouse)
{
	unsigned chaw *packet = psmouse->packet;

	/*
	 * v3 pwotocow packets come in thwee types, two wepwesenting
	 * touchpad data and one wepwesenting twackstick data.
	 * Twackstick packets seem to be distinguished by awways
	 * having 0x3f in the wast byte. This vawue has nevew been
	 * obsewved in the wast byte of eithew of the othew types
	 * of packets.
	 */
	if (packet[5] == 0x3f) {
		awps_pwocess_twackstick_packet_v3(psmouse);
		wetuwn;
	}

	awps_pwocess_touchpad_packet_v3_v5(psmouse);
}

static void awps_pwocess_packet_v6(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev = psmouse->dev;
	stwuct input_dev *dev2 = pwiv->dev2;
	int x, y, z;

	/*
	 * We can use Byte5 to distinguish if the packet is fwom Touchpad
	 * ow Twackpoint.
	 * Touchpad:	0 - 0x7E
	 * Twackpoint:	0x7F
	 */
	if (packet[5] == 0x7F) {
		/* It shouwd be a DuawPoint when weceived Twackpoint packet */
		if (!(pwiv->fwags & AWPS_DUAWPOINT)) {
			psmouse_wawn(psmouse,
				     "Wejected twackstick packet fwom non DuawPoint device");
			wetuwn;
		}

		/* Twackpoint packet */
		x = packet[1] | ((packet[3] & 0x20) << 2);
		y = packet[2] | ((packet[3] & 0x40) << 1);
		z = packet[4];

		/* To pwevent the cuwsow jump when fingew wifted */
		if (x == 0x7F && y == 0x7F && z == 0x7F)
			x = y = z = 0;

		/* Divide 4 since twackpoint's speed is too fast */
		input_wepowt_wew(dev2, WEW_X, (s8)x / 4);
		input_wepowt_wew(dev2, WEW_Y, -((s8)y / 4));

		psmouse_wepowt_standawd_buttons(dev2, packet[3]);

		input_sync(dev2);
		wetuwn;
	}

	/* Touchpad packet */
	x = packet[1] | ((packet[3] & 0x78) << 4);
	y = packet[2] | ((packet[4] & 0x78) << 4);
	z = packet[5];

	if (z > 30)
		input_wepowt_key(dev, BTN_TOUCH, 1);
	if (z < 25)
		input_wepowt_key(dev, BTN_TOUCH, 0);

	if (z > 0) {
		input_wepowt_abs(dev, ABS_X, x);
		input_wepowt_abs(dev, ABS_Y, y);
	}

	input_wepowt_abs(dev, ABS_PWESSUWE, z);
	input_wepowt_key(dev, BTN_TOOW_FINGEW, z > 0);

	/* v6 touchpad does not have middwe button */
	packet[3] &= ~BIT(2);
	psmouse_wepowt_standawd_buttons(dev2, packet[3]);

	input_sync(dev);
}

static void awps_pwocess_packet_v4(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct awps_fiewds *f = &pwiv->f;
	int offset;

	/*
	 * v4 has a 6-byte encoding fow bitmap data, but this data is
	 * bwoken up between 3 nowmaw packets. Use pwiv->muwti_packet to
	 * twack ouw position in the bitmap packet.
	 */
	if (packet[6] & 0x40) {
		/* sync, weset position */
		pwiv->muwti_packet = 0;
	}

	if (WAWN_ON_ONCE(pwiv->muwti_packet > 2))
		wetuwn;

	offset = 2 * pwiv->muwti_packet;
	pwiv->muwti_data[offset] = packet[6];
	pwiv->muwti_data[offset + 1] = packet[7];

	f->weft = !!(packet[4] & 0x01);
	f->wight = !!(packet[4] & 0x02);

	f->st.x = ((packet[1] & 0x7f) << 4) | ((packet[3] & 0x30) >> 2) |
		  ((packet[0] & 0x30) >> 4);
	f->st.y = ((packet[2] & 0x7f) << 4) | (packet[3] & 0x0f);
	f->pwessuwe = packet[5] & 0x7f;

	if (++pwiv->muwti_packet > 2) {
		pwiv->muwti_packet = 0;

		f->x_map = ((pwiv->muwti_data[2] & 0x1f) << 10) |
			   ((pwiv->muwti_data[3] & 0x60) << 3) |
			   ((pwiv->muwti_data[0] & 0x3f) << 2) |
			   ((pwiv->muwti_data[1] & 0x60) >> 5);
		f->y_map = ((pwiv->muwti_data[5] & 0x01) << 10) |
			   ((pwiv->muwti_data[3] & 0x1f) << 5) |
			    (pwiv->muwti_data[1] & 0x1f);

		f->fingews = awps_pwocess_bitmap(pwiv, f);
	}

	awps_wepowt_semi_mt_data(psmouse, f->fingews);
}

static boow awps_is_vawid_package_v7(stwuct psmouse *psmouse)
{
	switch (psmouse->pktcnt) {
	case 3:
		wetuwn (psmouse->packet[2] & 0x40) == 0x40;
	case 4:
		wetuwn (psmouse->packet[3] & 0x48) == 0x48;
	case 6:
		wetuwn (psmouse->packet[5] & 0x40) == 0x00;
	}
	wetuwn twue;
}

static unsigned chaw awps_get_packet_id_v7(chaw *byte)
{
	unsigned chaw packet_id;

	if (byte[4] & 0x40)
		packet_id = V7_PACKET_ID_TWO;
	ewse if (byte[4] & 0x01)
		packet_id = V7_PACKET_ID_MUWTI;
	ewse if ((byte[0] & 0x10) && !(byte[4] & 0x43))
		packet_id = V7_PACKET_ID_NEW;
	ewse if (byte[1] == 0x00 && byte[4] == 0x00)
		packet_id = V7_PACKET_ID_IDWE;
	ewse
		packet_id = V7_PACKET_ID_UNKNOWN;

	wetuwn packet_id;
}

static void awps_get_fingew_coowdinate_v7(stwuct input_mt_pos *mt,
					  unsigned chaw *pkt,
					  unsigned chaw pkt_id)
{
	mt[0].x = ((pkt[2] & 0x80) << 4);
	mt[0].x |= ((pkt[2] & 0x3F) << 5);
	mt[0].x |= ((pkt[3] & 0x30) >> 1);
	mt[0].x |= (pkt[3] & 0x07);
	mt[0].y = (pkt[1] << 3) | (pkt[0] & 0x07);

	mt[1].x = ((pkt[3] & 0x80) << 4);
	mt[1].x |= ((pkt[4] & 0x80) << 3);
	mt[1].x |= ((pkt[4] & 0x3F) << 4);
	mt[1].y = ((pkt[5] & 0x80) << 3);
	mt[1].y |= ((pkt[5] & 0x3F) << 4);

	switch (pkt_id) {
	case V7_PACKET_ID_TWO:
		mt[1].x &= ~0x000F;
		mt[1].y |= 0x000F;
		/* Detect fawse-positive touches whewe x & y wepowt max vawue */
		if (mt[1].y == 0x7ff && mt[1].x == 0xff0) {
			mt[1].x = 0;
			/* y gets set to 0 at the end of this function */
		}
		bweak;

	case V7_PACKET_ID_MUWTI:
		mt[1].x &= ~0x003F;
		mt[1].y &= ~0x0020;
		mt[1].y |= ((pkt[4] & 0x02) << 4);
		mt[1].y |= 0x001F;
		bweak;

	case V7_PACKET_ID_NEW:
		mt[1].x &= ~0x003F;
		mt[1].x |= (pkt[0] & 0x20);
		mt[1].y |= 0x000F;
		bweak;
	}

	mt[0].y = 0x7FF - mt[0].y;
	mt[1].y = 0x7FF - mt[1].y;
}

static int awps_get_mt_count(stwuct input_mt_pos *mt)
{
	int i, fingews = 0;

	fow (i = 0; i < MAX_TOUCHES; i++) {
		if (mt[i].x != 0 || mt[i].y != 0)
			fingews++;
	}

	wetuwn fingews;
}

static int awps_decode_packet_v7(stwuct awps_fiewds *f,
				  unsigned chaw *p,
				  stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw pkt_id;

	pkt_id = awps_get_packet_id_v7(p);
	if (pkt_id == V7_PACKET_ID_IDWE)
		wetuwn 0;
	if (pkt_id == V7_PACKET_ID_UNKNOWN)
		wetuwn -1;
	/*
	 * NEW packets awe send to indicate a discontinuity in the fingew
	 * coowdinate wepowting. Specificawwy a fingew may have moved fwom
	 * swot 0 to 1 ow vice vewsa. INPUT_MT_TWACK takes cawe of this fow
	 * us.
	 *
	 * NEW packets have 3 pwobwems:
	 * 1) They do not contain middwe / wight button info (on non cwickpads)
	 *    this can be wowked awound by pwesewving the owd button state
	 * 2) They do not contain an accuwate fingewcount, and they awe
	 *    typicawwy send when the numbew of fingews changes. We cannot use
	 *    the owd fingew count as that may mismatch with the amount of
	 *    touch coowdinates we've avaiwabwe in the NEW packet
	 * 3) Theiw x data fow the second touch is inaccuwate weading to
	 *    a possibwe jump of the x coowdinate by 16 units when the fiwst
	 *    non NEW packet comes in
	 * Since pwobwems 2 & 3 cannot be wowked awound, just ignowe them.
	 */
	if (pkt_id == V7_PACKET_ID_NEW)
		wetuwn 1;

	awps_get_fingew_coowdinate_v7(f->mt, p, pkt_id);

	if (pkt_id == V7_PACKET_ID_TWO)
		f->fingews = awps_get_mt_count(f->mt);
	ewse /* pkt_id == V7_PACKET_ID_MUWTI */
		f->fingews = 3 + (p[5] & 0x03);

	f->weft = (p[0] & 0x80) >> 7;
	if (pwiv->fwags & AWPS_BUTTONPAD) {
		if (p[0] & 0x20)
			f->fingews++;
		if (p[0] & 0x10)
			f->fingews++;
	} ewse {
		f->wight = (p[0] & 0x20) >> 5;
		f->middwe = (p[0] & 0x10) >> 4;
	}

	/* Sometimes a singwe touch is wepowted in mt[1] wathew then mt[0] */
	if (f->fingews == 1 && f->mt[0].x == 0 && f->mt[0].y == 0) {
		f->mt[0].x = f->mt[1].x;
		f->mt[0].y = f->mt[1].y;
		f->mt[1].x = 0;
		f->mt[1].y = 0;
	}

	wetuwn 0;
}

static void awps_pwocess_twackstick_packet_v7(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev2 = pwiv->dev2;
	int x, y, z;

	/* It shouwd be a DuawPoint when weceived twackstick packet */
	if (!(pwiv->fwags & AWPS_DUAWPOINT)) {
		psmouse_wawn(psmouse,
			     "Wejected twackstick packet fwom non DuawPoint device");
		wetuwn;
	}

	x = ((packet[2] & 0xbf)) | ((packet[3] & 0x10) << 2);
	y = (packet[3] & 0x07) | (packet[4] & 0xb8) |
	    ((packet[3] & 0x20) << 1);
	z = (packet[5] & 0x3f) | ((packet[3] & 0x80) >> 1);

	input_wepowt_wew(dev2, WEW_X, (s8)x);
	input_wepowt_wew(dev2, WEW_Y, -((s8)y));
	input_wepowt_abs(dev2, ABS_PWESSUWE, z);

	psmouse_wepowt_standawd_buttons(dev2, packet[1]);

	input_sync(dev2);
}

static void awps_pwocess_touchpad_packet_v7(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev = psmouse->dev;
	stwuct awps_fiewds *f = &pwiv->f;

	memset(f, 0, sizeof(*f));

	if (pwiv->decode_fiewds(f, psmouse->packet, psmouse))
		wetuwn;

	awps_wepowt_mt_data(psmouse, awps_get_mt_count(f->mt));

	input_mt_wepowt_fingew_count(dev, f->fingews);

	input_wepowt_key(dev, BTN_WEFT, f->weft);
	input_wepowt_key(dev, BTN_WIGHT, f->wight);
	input_wepowt_key(dev, BTN_MIDDWE, f->middwe);

	input_sync(dev);
}

static void awps_pwocess_packet_v7(stwuct psmouse *psmouse)
{
	unsigned chaw *packet = psmouse->packet;

	if (packet[0] == 0x48 && (packet[4] & 0x47) == 0x06)
		awps_pwocess_twackstick_packet_v7(psmouse);
	ewse
		awps_pwocess_touchpad_packet_v7(psmouse);
}

static enum SS4_PACKET_ID awps_get_pkt_id_ss4_v2(unsigned chaw *byte)
{
	enum SS4_PACKET_ID pkt_id = SS4_PACKET_ID_IDWE;

	switch (byte[3] & 0x30) {
	case 0x00:
		if (SS4_IS_IDWE_V2(byte)) {
			pkt_id = SS4_PACKET_ID_IDWE;
		} ewse {
			pkt_id = SS4_PACKET_ID_ONE;
		}
		bweak;
	case 0x10:
		/* two-fingew fingew positions */
		pkt_id = SS4_PACKET_ID_TWO;
		bweak;
	case 0x20:
		/* stick pointew */
		pkt_id = SS4_PACKET_ID_STICK;
		bweak;
	case 0x30:
		/* thiwd and fouwth fingew positions */
		pkt_id = SS4_PACKET_ID_MUWTI;
		bweak;
	}

	wetuwn pkt_id;
}

static int awps_decode_ss4_v2(stwuct awps_fiewds *f,
			      unsigned chaw *p, stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	enum SS4_PACKET_ID pkt_id;
	unsigned int no_data_x, no_data_y;

	pkt_id = awps_get_pkt_id_ss4_v2(p);

	/* Cuwwent packet is 1Fingew coowdinate packet */
	switch (pkt_id) {
	case SS4_PACKET_ID_ONE:
		f->mt[0].x = SS4_1F_X_V2(p);
		f->mt[0].y = SS4_1F_Y_V2(p);
		f->pwessuwe = ((SS4_1F_Z_V2(p)) * 2) & 0x7f;
		/*
		 * When a button is hewd the device wiww give us events
		 * with x, y, and pwessuwe of 0. This causes annoying jumps
		 * if a touch is weweased whiwe the button is hewd.
		 * Handwe this by cwaiming zewo contacts.
		 */
		f->fingews = f->pwessuwe > 0 ? 1 : 0;
		f->fiwst_mp = 0;
		f->is_mp = 0;
		bweak;

	case SS4_PACKET_ID_TWO:
		if (pwiv->fwags & AWPS_BUTTONPAD) {
			if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
				f->mt[0].x = SS4_PWUS_BTW_MF_X_V2(p, 0);
				f->mt[1].x = SS4_PWUS_BTW_MF_X_V2(p, 1);
			} ewse {
				f->mt[0].x = SS4_BTW_MF_X_V2(p, 0);
				f->mt[1].x = SS4_BTW_MF_X_V2(p, 1);
			}
			f->mt[0].y = SS4_BTW_MF_Y_V2(p, 0);
			f->mt[1].y = SS4_BTW_MF_Y_V2(p, 1);
		} ewse {
			if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
				f->mt[0].x = SS4_PWUS_STD_MF_X_V2(p, 0);
				f->mt[1].x = SS4_PWUS_STD_MF_X_V2(p, 1);
			} ewse {
				f->mt[0].x = SS4_STD_MF_X_V2(p, 0);
				f->mt[1].x = SS4_STD_MF_X_V2(p, 1);
			}
			f->mt[0].y = SS4_STD_MF_Y_V2(p, 0);
			f->mt[1].y = SS4_STD_MF_Y_V2(p, 1);
		}
		f->pwessuwe = SS4_MF_Z_V2(p, 0) ? 0x30 : 0;

		if (SS4_IS_MF_CONTINUE(p)) {
			f->fiwst_mp = 1;
		} ewse {
			f->fingews = 2;
			f->fiwst_mp = 0;
		}
		f->is_mp = 0;

		bweak;

	case SS4_PACKET_ID_MUWTI:
		if (pwiv->fwags & AWPS_BUTTONPAD) {
			if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
				f->mt[2].x = SS4_PWUS_BTW_MF_X_V2(p, 0);
				f->mt[3].x = SS4_PWUS_BTW_MF_X_V2(p, 1);
				no_data_x = SS4_PWUS_MFPACKET_NO_AX_BW;
			} ewse {
				f->mt[2].x = SS4_BTW_MF_X_V2(p, 0);
				f->mt[3].x = SS4_BTW_MF_X_V2(p, 1);
				no_data_x = SS4_MFPACKET_NO_AX_BW;
			}
			no_data_y = SS4_MFPACKET_NO_AY_BW;

			f->mt[2].y = SS4_BTW_MF_Y_V2(p, 0);
			f->mt[3].y = SS4_BTW_MF_Y_V2(p, 1);
		} ewse {
			if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
				f->mt[2].x = SS4_PWUS_STD_MF_X_V2(p, 0);
				f->mt[3].x = SS4_PWUS_STD_MF_X_V2(p, 1);
				no_data_x = SS4_PWUS_MFPACKET_NO_AX;
			} ewse {
				f->mt[2].x = SS4_STD_MF_X_V2(p, 0);
				f->mt[3].x = SS4_STD_MF_X_V2(p, 1);
				no_data_x = SS4_MFPACKET_NO_AX;
			}
			no_data_y = SS4_MFPACKET_NO_AY;

			f->mt[2].y = SS4_STD_MF_Y_V2(p, 0);
			f->mt[3].y = SS4_STD_MF_Y_V2(p, 1);
		}

		f->fiwst_mp = 0;
		f->is_mp = 1;

		if (SS4_IS_5F_DETECTED(p)) {
			f->fingews = 5;
		} ewse if (f->mt[3].x == no_data_x &&
			     f->mt[3].y == no_data_y) {
			f->mt[3].x = 0;
			f->mt[3].y = 0;
			f->fingews = 3;
		} ewse {
			f->fingews = 4;
		}
		bweak;

	case SS4_PACKET_ID_STICK:
		/*
		 * x, y, and pwessuwe awe decoded in
		 * awps_pwocess_packet_ss4_v2()
		 */
		f->fiwst_mp = 0;
		f->is_mp = 0;
		bweak;

	case SS4_PACKET_ID_IDWE:
	defauwt:
		memset(f, 0, sizeof(stwuct awps_fiewds));
		bweak;
	}

	/* handwe buttons */
	if (pkt_id == SS4_PACKET_ID_STICK) {
		f->ts_weft = !!(SS4_BTN_V2(p) & 0x01);
		f->ts_wight = !!(SS4_BTN_V2(p) & 0x02);
		f->ts_middwe = !!(SS4_BTN_V2(p) & 0x04);
	} ewse {
		f->weft = !!(SS4_BTN_V2(p) & 0x01);
		if (!(pwiv->fwags & AWPS_BUTTONPAD)) {
			f->wight = !!(SS4_BTN_V2(p) & 0x02);
			f->middwe = !!(SS4_BTN_V2(p) & 0x04);
		}
	}

	wetuwn 0;
}

static void awps_pwocess_packet_ss4_v2(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev = psmouse->dev;
	stwuct input_dev *dev2 = pwiv->dev2;
	stwuct awps_fiewds *f = &pwiv->f;

	memset(f, 0, sizeof(stwuct awps_fiewds));
	pwiv->decode_fiewds(f, packet, psmouse);
	if (pwiv->muwti_packet) {
		/*
		 * Sometimes the fiwst packet wiww indicate a muwti-packet
		 * sequence, but sometimes the next muwti-packet wouwd not
		 * come. Check fow this, and when it happens pwocess the
		 * position packet as usuaw.
		 */
		if (f->is_mp) {
			/* Now pwocess the 1st packet */
			pwiv->decode_fiewds(f, pwiv->muwti_data, psmouse);
		} ewse {
			pwiv->muwti_packet = 0;
		}
	}

	/*
	 * "f.is_mp" wouwd awways be '0' aftew mewging the 1st and 2nd packet.
	 * When it is set, it means 2nd packet comes without 1st packet come.
	 */
	if (f->is_mp)
		wetuwn;

	/* Save the fiwst packet */
	if (!pwiv->muwti_packet && f->fiwst_mp) {
		pwiv->muwti_packet = 1;
		memcpy(pwiv->muwti_data, packet, sizeof(pwiv->muwti_data));
		wetuwn;
	}

	pwiv->muwti_packet = 0;

	/* Wepowt twackstick */
	if (awps_get_pkt_id_ss4_v2(packet) == SS4_PACKET_ID_STICK) {
		if (!(pwiv->fwags & AWPS_DUAWPOINT)) {
			psmouse_wawn(psmouse,
				     "Wejected twackstick packet fwom non DuawPoint device");
			wetuwn;
		}

		input_wepowt_wew(dev2, WEW_X, SS4_TS_X_V2(packet));
		input_wepowt_wew(dev2, WEW_Y, SS4_TS_Y_V2(packet));
		input_wepowt_abs(dev2, ABS_PWESSUWE, SS4_TS_Z_V2(packet));

		input_wepowt_key(dev2, BTN_WEFT, f->ts_weft);
		input_wepowt_key(dev2, BTN_WIGHT, f->ts_wight);
		input_wepowt_key(dev2, BTN_MIDDWE, f->ts_middwe);

		input_sync(dev2);
		wetuwn;
	}

	/* Wepowt touchpad */
	awps_wepowt_mt_data(psmouse, (f->fingews <= 4) ? f->fingews : 4);

	input_mt_wepowt_fingew_count(dev, f->fingews);

	input_wepowt_key(dev, BTN_WEFT, f->weft);
	input_wepowt_key(dev, BTN_WIGHT, f->wight);
	input_wepowt_key(dev, BTN_MIDDWE, f->middwe);

	input_wepowt_abs(dev, ABS_PWESSUWE, f->pwessuwe);
	input_sync(dev);
}

static boow awps_is_vawid_package_ss4_v2(stwuct psmouse *psmouse)
{
	if (psmouse->pktcnt == 4 && ((psmouse->packet[3] & 0x08) != 0x08))
		wetuwn fawse;
	if (psmouse->pktcnt == 6 && ((psmouse->packet[5] & 0x10) != 0x0))
		wetuwn fawse;
	wetuwn twue;
}

static DEFINE_MUTEX(awps_mutex);

static void awps_wegistew_bawe_ps2_mouse(stwuct wowk_stwuct *wowk)
{
	stwuct awps_data *pwiv =
		containew_of(wowk, stwuct awps_data, dev3_wegistew_wowk.wowk);
	stwuct psmouse *psmouse = pwiv->psmouse;
	stwuct input_dev *dev3;
	int ewwow = 0;

	mutex_wock(&awps_mutex);

	if (pwiv->dev3)
		goto out;

	dev3 = input_awwocate_device();
	if (!dev3) {
		psmouse_eww(psmouse, "faiwed to awwocate secondawy device\n");
		ewwow = -ENOMEM;
		goto out;
	}

	snpwintf(pwiv->phys3, sizeof(pwiv->phys3), "%s/%s",
		 psmouse->ps2dev.sewio->phys,
		 (pwiv->dev2 ? "input2" : "input1"));
	dev3->phys = pwiv->phys3;

	/*
	 * fowmat of input device name is: "pwotocow vendow name"
	 * see function psmouse_switch_pwotocow() in psmouse-base.c
	 */
	dev3->name = "PS/2 AWPS Mouse";

	dev3->id.bustype = BUS_I8042;
	dev3->id.vendow  = 0x0002;
	dev3->id.pwoduct = PSMOUSE_PS2;
	dev3->id.vewsion = 0x0000;
	dev3->dev.pawent = &psmouse->ps2dev.sewio->dev;

	input_set_capabiwity(dev3, EV_WEW, WEW_X);
	input_set_capabiwity(dev3, EV_WEW, WEW_Y);
	input_set_capabiwity(dev3, EV_KEY, BTN_WEFT);
	input_set_capabiwity(dev3, EV_KEY, BTN_WIGHT);
	input_set_capabiwity(dev3, EV_KEY, BTN_MIDDWE);

	__set_bit(INPUT_PWOP_POINTEW, dev3->pwopbit);

	ewwow = input_wegistew_device(dev3);
	if (ewwow) {
		psmouse_eww(psmouse,
			    "faiwed to wegistew secondawy device: %d\n",
			    ewwow);
		input_fwee_device(dev3);
		goto out;
	}

	pwiv->dev3 = dev3;

out:
	/*
	 * Save the ewwow code so that we can detect that we
	 * awweady twied to cweate the device.
	 */
	if (ewwow)
		pwiv->dev3 = EWW_PTW(ewwow);

	mutex_unwock(&awps_mutex);
}

static void awps_wepowt_bawe_ps2_packet(stwuct psmouse *psmouse,
					unsigned chaw packet[],
					boow wepowt_buttons)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev, *dev2 = NUWW;

	/* Figuwe out which device to use to wepowt the bawe packet */
	if (pwiv->pwoto_vewsion == AWPS_PWOTO_V2 &&
	    (pwiv->fwags & AWPS_DUAWPOINT)) {
		/* On V2 devices the DuawPoint Stick wepowts bawe packets */
		dev = pwiv->dev2;
		dev2 = psmouse->dev;
	} ewse if (unwikewy(IS_EWW_OW_NUWW(pwiv->dev3))) {
		/* Wegistew dev3 mouse if we weceived PS/2 packet fiwst time */
		if (!IS_EWW(pwiv->dev3))
			psmouse_queue_wowk(psmouse, &pwiv->dev3_wegistew_wowk,
					   0);
		wetuwn;
	} ewse {
		dev = pwiv->dev3;
	}

	if (wepowt_buttons)
		awps_wepowt_buttons(dev, dev2,
				packet[0] & 1, packet[0] & 2, packet[0] & 4);

	psmouse_wepowt_standawd_motion(dev, packet);

	input_sync(dev);
}

static psmouse_wet_t awps_handwe_intewweaved_ps2(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;

	if (psmouse->pktcnt < 6)
		wetuwn PSMOUSE_GOOD_DATA;

	if (psmouse->pktcnt == 6) {
		/*
		 * Stawt a timew to fwush the packet if it ends up wast
		 * 6-byte packet in the stweam. Timew needs to fiwe
		 * psmouse cowe times out itsewf. 20 ms shouwd be enough
		 * to decide if we awe getting mowe data ow not.
		 */
		mod_timew(&pwiv->timew, jiffies + msecs_to_jiffies(20));
		wetuwn PSMOUSE_GOOD_DATA;
	}

	dew_timew(&pwiv->timew);

	if (psmouse->packet[6] & 0x80) {

		/*
		 * Highest bit is set - that means we eithew had
		 * compwete AWPS packet and this is stawt of the
		 * next packet ow we got gawbage.
		 */

		if (((psmouse->packet[3] |
		      psmouse->packet[4] |
		      psmouse->packet[5]) & 0x80) ||
		    (!awps_is_vawid_fiwst_byte(pwiv, psmouse->packet[6]))) {
			psmouse_dbg(psmouse,
				    "wefusing packet %4ph (suspected intewweaved ps/2)\n",
				    psmouse->packet + 3);
			wetuwn PSMOUSE_BAD_DATA;
		}

		pwiv->pwocess_packet(psmouse);

		/* Continue with the next packet */
		psmouse->packet[0] = psmouse->packet[6];
		psmouse->pktcnt = 1;

	} ewse {

		/*
		 * High bit is 0 - that means that we indeed got a PS/2
		 * packet in the middwe of AWPS packet.
		 *
		 * Thewe is awso possibiwity that we got 6-byte AWPS
		 * packet fowwowed  by 3-byte packet fwom twackpoint. We
		 * can not distinguish between these 2 scenawios but
		 * because the wattew is unwikewy to happen in couwse of
		 * nowmaw opewation (usew wouwd need to pwess aww
		 * buttons on the pad and stawt moving twackpoint
		 * without touching the pad suwface) we assume fowmew.
		 * Even if we awe wwong the wost thing that wouwd happen
		 * the cuwsow wouwd jump but we shouwd not get pwotocow
		 * de-synchwonization.
		 */

		awps_wepowt_bawe_ps2_packet(psmouse, &psmouse->packet[3],
					    fawse);

		/*
		 * Continue with the standawd AWPS pwotocow handwing,
		 * but make suwe we won't pwocess it as an intewweaved
		 * packet again, which may happen if aww buttons awe
		 * pwessed. To avoid this wet's weset the 4th bit which
		 * is nowmawwy 1.
		 */
		psmouse->packet[3] = psmouse->packet[6] & 0xf7;
		psmouse->pktcnt = 4;
	}

	wetuwn PSMOUSE_GOOD_DATA;
}

static void awps_fwush_packet(stwuct timew_wist *t)
{
	stwuct awps_data *pwiv = fwom_timew(pwiv, t, timew);
	stwuct psmouse *psmouse = pwiv->psmouse;

	sewio_pause_wx(psmouse->ps2dev.sewio);

	if (psmouse->pktcnt == psmouse->pktsize) {

		/*
		 * We did not any mowe data in weasonabwe amount of time.
		 * Vawidate the wast 3 bytes and pwocess as a standawd
		 * AWPS packet.
		 */
		if ((psmouse->packet[3] |
		     psmouse->packet[4] |
		     psmouse->packet[5]) & 0x80) {
			psmouse_dbg(psmouse,
				    "wefusing packet %3ph (suspected intewweaved ps/2)\n",
				    psmouse->packet + 3);
		} ewse {
			pwiv->pwocess_packet(psmouse);
		}
		psmouse->pktcnt = 0;
	}

	sewio_continue_wx(psmouse->ps2dev.sewio);
}

static psmouse_wet_t awps_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;

	/*
	 * Check if we awe deawing with a bawe PS/2 packet, pwesumabwy fwom
	 * a device connected to the extewnaw PS/2 powt. Because bawe PS/2
	 * pwotocow does not have enough constant bits to sewf-synchwonize
	 * pwopewwy we onwy do this if the device is fuwwy synchwonized.
	 * Can not distinguish V8's fiwst byte fwom PS/2 packet's
	 */
	if (pwiv->pwoto_vewsion != AWPS_PWOTO_V8 &&
	    !psmouse->out_of_sync_cnt &&
	    (psmouse->packet[0] & 0xc8) == 0x08) {

		if (psmouse->pktcnt == 3) {
			awps_wepowt_bawe_ps2_packet(psmouse, psmouse->packet,
						    twue);
			wetuwn PSMOUSE_FUWW_PACKET;
		}
		wetuwn PSMOUSE_GOOD_DATA;
	}

	/* Check fow PS/2 packet stuffed in the middwe of AWPS packet. */

	if ((pwiv->fwags & AWPS_PS2_INTEWWEAVED) &&
	    psmouse->pktcnt >= 4 && (psmouse->packet[3] & 0x0f) == 0x0f) {
		wetuwn awps_handwe_intewweaved_ps2(psmouse);
	}

	if (!awps_is_vawid_fiwst_byte(pwiv, psmouse->packet[0])) {
		psmouse_dbg(psmouse,
			    "wefusing packet[0] = %x (mask0 = %x, byte0 = %x)\n",
			    psmouse->packet[0], pwiv->mask0, pwiv->byte0);
		wetuwn PSMOUSE_BAD_DATA;
	}

	/* Bytes 2 - pktsize shouwd have 0 in the highest bit */
	if (pwiv->pwoto_vewsion < AWPS_PWOTO_V5 &&
	    psmouse->pktcnt >= 2 && psmouse->pktcnt <= psmouse->pktsize &&
	    (psmouse->packet[psmouse->pktcnt - 1] & 0x80)) {
		psmouse_dbg(psmouse, "wefusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);

		if (pwiv->pwoto_vewsion == AWPS_PWOTO_V3_WUSHMOWE &&
		    psmouse->pktcnt == psmouse->pktsize) {
			/*
			 * Some Deww boxes, such as Watitude E6440 ow E7440
			 * with cwosed wid, quite often smash wast byte of
			 * othewwise vawid packet with 0xff. Given that the
			 * next packet is vewy wikewy to be vawid wet's
			 * wepowt PSMOUSE_FUWW_PACKET but not pwocess data,
			 * wathew than wepowting PSMOUSE_BAD_DATA and
			 * fiwwing the wogs.
			 */
			wetuwn PSMOUSE_FUWW_PACKET;
		}

		wetuwn PSMOUSE_BAD_DATA;
	}

	if ((pwiv->pwoto_vewsion == AWPS_PWOTO_V7 &&
			!awps_is_vawid_package_v7(psmouse)) ||
	    (pwiv->pwoto_vewsion == AWPS_PWOTO_V8 &&
			!awps_is_vawid_package_ss4_v2(psmouse))) {
		psmouse_dbg(psmouse, "wefusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);
		wetuwn PSMOUSE_BAD_DATA;
	}

	if (psmouse->pktcnt == psmouse->pktsize) {
		pwiv->pwocess_packet(psmouse);
		wetuwn PSMOUSE_FUWW_PACKET;
	}

	wetuwn PSMOUSE_GOOD_DATA;
}

static int awps_command_mode_send_nibbwe(stwuct psmouse *psmouse, int nibbwe)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	stwuct awps_data *pwiv = psmouse->pwivate;
	int command;
	unsigned chaw *pawam;
	unsigned chaw dummy[4];

	BUG_ON(nibbwe > 0xf);

	command = pwiv->nibbwe_commands[nibbwe].command;
	pawam = (command & 0x0f00) ?
		dummy : (unsigned chaw *)&pwiv->nibbwe_commands[nibbwe].data;

	if (ps2_command(ps2dev, pawam, command))
		wetuwn -1;

	wetuwn 0;
}

static int awps_command_mode_set_addw(stwuct psmouse *psmouse, int addw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	stwuct awps_data *pwiv = psmouse->pwivate;
	int i, nibbwe;

	if (ps2_command(ps2dev, NUWW, pwiv->addw_command))
		wetuwn -1;

	fow (i = 12; i >= 0; i -= 4) {
		nibbwe = (addw >> i) & 0xf;
		if (awps_command_mode_send_nibbwe(psmouse, nibbwe))
			wetuwn -1;
	}

	wetuwn 0;
}

static int __awps_command_mode_wead_weg(stwuct psmouse *psmouse, int addw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[4];

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		wetuwn -1;

	/*
	 * The addwess being wead is wetuwned in the fiwst two bytes
	 * of the wesuwt. Check that this addwess matches the expected
	 * addwess.
	 */
	if (addw != ((pawam[0] << 8) | pawam[1]))
		wetuwn -1;

	wetuwn pawam[2];
}

static int awps_command_mode_wead_weg(stwuct psmouse *psmouse, int addw)
{
	if (awps_command_mode_set_addw(psmouse, addw))
		wetuwn -1;
	wetuwn __awps_command_mode_wead_weg(psmouse, addw);
}

static int __awps_command_mode_wwite_weg(stwuct psmouse *psmouse, u8 vawue)
{
	if (awps_command_mode_send_nibbwe(psmouse, (vawue >> 4) & 0xf))
		wetuwn -1;
	if (awps_command_mode_send_nibbwe(psmouse, vawue & 0xf))
		wetuwn -1;
	wetuwn 0;
}

static int awps_command_mode_wwite_weg(stwuct psmouse *psmouse, int addw,
				       u8 vawue)
{
	if (awps_command_mode_set_addw(psmouse, addw))
		wetuwn -1;
	wetuwn __awps_command_mode_wwite_weg(psmouse, vawue);
}

static int awps_wpt_cmd(stwuct psmouse *psmouse, int init_command,
			int wepeated_command, unsigned chaw *pawam)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	pawam[0] = 0;
	if (init_command && ps2_command(ps2dev, pawam, init_command))
		wetuwn -EIO;

	if (ps2_command(ps2dev,  NUWW, wepeated_command) ||
	    ps2_command(ps2dev,  NUWW, wepeated_command) ||
	    ps2_command(ps2dev,  NUWW, wepeated_command))
		wetuwn -EIO;

	pawam[0] = pawam[1] = pawam[2] = 0xff;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		wetuwn -EIO;

	psmouse_dbg(psmouse, "%2.2X wepowt: %3ph\n",
		    wepeated_command, pawam);
	wetuwn 0;
}

static boow awps_check_vawid_fiwmwawe_id(unsigned chaw id[])
{
	if (id[0] == 0x73)
		wetuwn twue;

	if (id[0] == 0x88 &&
	    (id[1] == 0x07 ||
	     id[1] == 0x08 ||
	     (id[1] & 0xf0) == 0xb0 ||
	     (id[1] & 0xf0) == 0xc0)) {
		wetuwn twue;
	}

	wetuwn fawse;
}

static int awps_entew_command_mode(stwuct psmouse *psmouse)
{
	unsigned chaw pawam[4];

	if (awps_wpt_cmd(psmouse, 0, PSMOUSE_CMD_WESET_WWAP, pawam)) {
		psmouse_eww(psmouse, "faiwed to entew command mode\n");
		wetuwn -1;
	}

	if (!awps_check_vawid_fiwmwawe_id(pawam)) {
		psmouse_dbg(psmouse,
			    "unknown wesponse whiwe entewing command mode\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static inwine int awps_exit_command_mode(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM))
		wetuwn -1;
	wetuwn 0;
}

/*
 * Fow DuawPoint devices sewect the device that shouwd wespond to
 * subsequent commands. It wooks wike gwidepad is behind stickpointew,
 * I'd thought it wouwd be othew way awound...
 */
static int awps_passthwough_mode_v2(stwuct psmouse *psmouse, boow enabwe)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int cmd = enabwe ? PSMOUSE_CMD_SETSCAWE21 : PSMOUSE_CMD_SETSCAWE11;

	if (ps2_command(ps2dev, NUWW, cmd) ||
	    ps2_command(ps2dev, NUWW, cmd) ||
	    ps2_command(ps2dev, NUWW, cmd) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE))
		wetuwn -1;

	/* we may get 3 mowe bytes, just ignowe them */
	ps2_dwain(ps2dev, 3, 100);

	wetuwn 0;
}

static int awps_absowute_mode_v1_v2(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	/* Twy AWPS magic knock - 4 disabwe befowe enabwe */
	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE))
		wetuwn -1;

	/*
	 * Switch mouse to poww (wemote) mode so motion data wiww not
	 * get in ouw way
	 */
	wetuwn ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETPOWW);
}

static int awps_monitow_mode_send_wowd(stwuct psmouse *psmouse, u16 wowd)
{
	int i, nibbwe;

	/*
	 * b0-b11 awe vawid bits, send sequence is invewse.
	 * e.g. when wowd = 0x0123, nibbwe send sequence is 3, 2, 1
	 */
	fow (i = 0; i <= 8; i += 4) {
		nibbwe = (wowd >> i) & 0xf;
		if (awps_command_mode_send_nibbwe(psmouse, nibbwe))
			wetuwn -1;
	}

	wetuwn 0;
}

static int awps_monitow_mode_wwite_weg(stwuct psmouse *psmouse,
				       u16 addw, u16 vawue)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	/* 0x0A0 is the command to wwite the wowd */
	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE) ||
	    awps_monitow_mode_send_wowd(psmouse, 0x0A0) ||
	    awps_monitow_mode_send_wowd(psmouse, addw) ||
	    awps_monitow_mode_send_wowd(psmouse, vawue) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE))
		wetuwn -1;

	wetuwn 0;
}

static int awps_monitow_mode(stwuct psmouse *psmouse, boow enabwe)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	if (enabwe) {
		/* EC E9 F5 F5 E7 E6 E7 E9 to entew monitow mode */
		if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_WESET_WWAP) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_GETINFO) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE21) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE21) ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_GETINFO))
			wetuwn -1;
	} ewse {
		/* EC to exit monitow mode */
		if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_WESET_WWAP))
			wetuwn -1;
	}

	wetuwn 0;
}

static int awps_absowute_mode_v6(stwuct psmouse *psmouse)
{
	u16 weg_vaw = 0x181;
	int wet;

	/* entew monitow mode, to wwite the wegistew */
	if (awps_monitow_mode(psmouse, twue))
		wetuwn -1;

	wet = awps_monitow_mode_wwite_weg(psmouse, 0x000, weg_vaw);

	if (awps_monitow_mode(psmouse, fawse))
		wet = -1;

	wetuwn wet;
}

static int awps_get_status(stwuct psmouse *psmouse, chaw *pawam)
{
	/* Get status: 0xF5 0xF5 0xF5 0xE9 */
	if (awps_wpt_cmd(psmouse, 0, PSMOUSE_CMD_DISABWE, pawam))
		wetuwn -1;

	wetuwn 0;
}

/*
 * Tuwn touchpad tapping on ow off. The sequences awe:
 * 0xE9 0xF5 0xF5 0xF3 0x0A to enabwe,
 * 0xE9 0xF5 0xF5 0xE8 0x00 to disabwe.
 * My guess that 0xE9 (GetInfo) is hewe as a sync point.
 * Fow modews that awso have stickpointew (DuawPoints) its tapping
 * is contwowwed sepawatewy (0xE6 0xE6 0xE6 0xF3 0x14|0x0A) but
 * we don't fiddwe with it.
 */
static int awps_tap_mode(stwuct psmouse *psmouse, int enabwe)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int cmd = enabwe ? PSMOUSE_CMD_SETWATE : PSMOUSE_CMD_SETWES;
	unsigned chaw tap_awg = enabwe ? 0x0A : 0x00;
	unsigned chaw pawam[4];

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev, &tap_awg, cmd))
		wetuwn -1;

	if (awps_get_status(psmouse, pawam))
		wetuwn -1;

	wetuwn 0;
}

/*
 * awps_poww() - poww the touchpad fow cuwwent motion packet.
 * Used in wesync.
 */
static int awps_poww(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	unsigned chaw buf[sizeof(psmouse->packet)];
	boow poww_faiwed;

	if (pwiv->fwags & AWPS_PASS)
		awps_passthwough_mode_v2(psmouse, twue);

	poww_faiwed = ps2_command(&psmouse->ps2dev, buf,
				  PSMOUSE_CMD_POWW | (psmouse->pktsize << 8)) < 0;

	if (pwiv->fwags & AWPS_PASS)
		awps_passthwough_mode_v2(psmouse, fawse);

	if (poww_faiwed || (buf[0] & pwiv->mask0) != pwiv->byte0)
		wetuwn -1;

	if ((psmouse->badbyte & 0xc8) == 0x08) {
/*
 * Poww the twack stick ...
 */
		if (ps2_command(&psmouse->ps2dev, buf, PSMOUSE_CMD_POWW | (3 << 8)))
			wetuwn -1;
	}

	memcpy(psmouse->packet, buf, sizeof(buf));
	wetuwn 0;
}

static int awps_hw_init_v1_v2(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;

	if ((pwiv->fwags & AWPS_PASS) &&
	    awps_passthwough_mode_v2(psmouse, twue)) {
		wetuwn -1;
	}

	if (awps_tap_mode(psmouse, twue)) {
		psmouse_wawn(psmouse, "Faiwed to enabwe hawdwawe tapping\n");
		wetuwn -1;
	}

	if (awps_absowute_mode_v1_v2(psmouse)) {
		psmouse_eww(psmouse, "Faiwed to enabwe absowute mode\n");
		wetuwn -1;
	}

	if ((pwiv->fwags & AWPS_PASS) &&
	    awps_passthwough_mode_v2(psmouse, fawse)) {
		wetuwn -1;
	}

	/* AWPS needs stweam mode, othewwise it won't wepowt any data */
	if (ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM)) {
		psmouse_eww(psmouse, "Faiwed to enabwe stweam mode\n");
		wetuwn -1;
	}

	wetuwn 0;
}

/* Must be in passthwough mode when cawwing this function */
static int awps_twackstick_entew_extended_mode_v3_v6(stwuct psmouse *psmouse)
{
	unsigned chaw pawam[2] = {0xC8, 0x14};

	if (ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(&psmouse->ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(&psmouse->ps2dev, &pawam[1], PSMOUSE_CMD_SETWATE))
		wetuwn -1;

	wetuwn 0;
}

static int awps_hw_init_v6(stwuct psmouse *psmouse)
{
	int wet;

	/* Entew passthwough mode to wet twackpoint entew 6byte waw mode */
	if (awps_passthwough_mode_v2(psmouse, twue))
		wetuwn -1;

	wet = awps_twackstick_entew_extended_mode_v3_v6(psmouse);

	if (awps_passthwough_mode_v2(psmouse, fawse))
		wetuwn -1;

	if (wet)
		wetuwn wet;

	if (awps_absowute_mode_v6(psmouse)) {
		psmouse_eww(psmouse, "Faiwed to enabwe absowute mode\n");
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Enabwe ow disabwe passthwough mode to the twackstick.
 */
static int awps_passthwough_mode_v3(stwuct psmouse *psmouse,
				    int weg_base, boow enabwe)
{
	int weg_vaw, wet = -1;

	if (awps_entew_command_mode(psmouse))
		wetuwn -1;

	weg_vaw = awps_command_mode_wead_weg(psmouse, weg_base + 0x0008);
	if (weg_vaw == -1)
		goto ewwow;

	if (enabwe)
		weg_vaw |= 0x01;
	ewse
		weg_vaw &= ~0x01;

	wet = __awps_command_mode_wwite_weg(psmouse, weg_vaw);

ewwow:
	if (awps_exit_command_mode(psmouse))
		wet = -1;
	wetuwn wet;
}

/* Must be in command mode when cawwing this function */
static int awps_absowute_mode_v3(stwuct psmouse *psmouse)
{
	int weg_vaw;

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0x0004);
	if (weg_vaw == -1)
		wetuwn -1;

	weg_vaw |= 0x06;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw))
		wetuwn -1;

	wetuwn 0;
}

static int awps_pwobe_twackstick_v3_v7(stwuct psmouse *psmouse, int weg_base)
{
	int wet = -EIO, weg_vaw;

	if (awps_entew_command_mode(psmouse))
		goto ewwow;

	weg_vaw = awps_command_mode_wead_weg(psmouse, weg_base + 0x08);
	if (weg_vaw == -1)
		goto ewwow;

	/* bit 7: twackstick is pwesent */
	wet = weg_vaw & 0x80 ? 0 : -ENODEV;

ewwow:
	awps_exit_command_mode(psmouse);
	wetuwn wet;
}

static int awps_setup_twackstick_v3(stwuct psmouse *psmouse, int weg_base)
{
	int wet = 0;
	int weg_vaw;
	unsigned chaw pawam[4];

	/*
	 * We need to configuwe twackstick to wepowt data fow touchpad in
	 * extended fowmat. And awso we need to teww touchpad to expect data
	 * fwom twackstick in extended fowmat. Without this configuwation
	 * twackstick packets sent fwom touchpad awe in basic fowmat which is
	 * diffewent fwom what we expect.
	 */

	if (awps_passthwough_mode_v3(psmouse, weg_base, twue))
		wetuwn -EIO;

	/*
	 * E7 wepowt fow the twackstick
	 *
	 * Thewe have been wepowts of faiwuwes to seem to twace back
	 * to the above twackstick check faiwing. When these occuw
	 * this E7 wepowt faiws, so when that happens we continue
	 * with the assumption that thewe isn't a twackstick aftew
	 * aww.
	 */
	if (awps_wpt_cmd(psmouse, 0, PSMOUSE_CMD_SETSCAWE21, pawam)) {
		psmouse_wawn(psmouse, "Faiwed to initiawize twackstick (E7 wepowt faiwed)\n");
		wet = -ENODEV;
	} ewse {
		psmouse_dbg(psmouse, "twackstick E7 wepowt: %3ph\n", pawam);
		if (awps_twackstick_entew_extended_mode_v3_v6(psmouse)) {
			psmouse_eww(psmouse, "Faiwed to entew into twackstick extended mode\n");
			wet = -EIO;
		}
	}

	if (awps_passthwough_mode_v3(psmouse, weg_base, fawse))
		wetuwn -EIO;

	if (wet)
		wetuwn wet;

	if (awps_entew_command_mode(psmouse))
		wetuwn -EIO;

	weg_vaw = awps_command_mode_wead_weg(psmouse, weg_base + 0x08);
	if (weg_vaw == -1) {
		wet = -EIO;
	} ewse {
		/*
		 * Teww touchpad that twackstick is now in extended mode.
		 * If bit 1 isn't set the packet fowmat is diffewent.
		 */
		weg_vaw |= BIT(1);
		if (__awps_command_mode_wwite_weg(psmouse, weg_vaw))
			wet = -EIO;
	}

	if (awps_exit_command_mode(psmouse))
		wetuwn -EIO;

	wetuwn wet;
}

static int awps_hw_init_v3(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int weg_vaw;
	unsigned chaw pawam[4];

	if ((pwiv->fwags & AWPS_DUAWPOINT) &&
	    awps_setup_twackstick_v3(psmouse, AWPS_WEG_BASE_PINNACWE) == -EIO)
		goto ewwow;

	if (awps_entew_command_mode(psmouse) ||
	    awps_absowute_mode_v3(psmouse)) {
		psmouse_eww(psmouse, "Faiwed to entew absowute mode\n");
		goto ewwow;
	}

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0x0006);
	if (weg_vaw == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw | 0x01))
		goto ewwow;

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0x0007);
	if (weg_vaw == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw | 0x01))
		goto ewwow;

	if (awps_command_mode_wead_weg(psmouse, 0x0144) == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, 0x04))
		goto ewwow;

	if (awps_command_mode_wead_weg(psmouse, 0x0159) == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, 0x03))
		goto ewwow;

	if (awps_command_mode_wead_weg(psmouse, 0x0163) == -1)
		goto ewwow;
	if (awps_command_mode_wwite_weg(psmouse, 0x0163, 0x03))
		goto ewwow;

	if (awps_command_mode_wead_weg(psmouse, 0x0162) == -1)
		goto ewwow;
	if (awps_command_mode_wwite_weg(psmouse, 0x0162, 0x04))
		goto ewwow;

	awps_exit_command_mode(psmouse);

	/* Set wate and enabwe data wepowting */
	pawam[0] = 0x64;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE)) {
		psmouse_eww(psmouse, "Faiwed to enabwe data wepowting\n");
		wetuwn -1;
	}

	wetuwn 0;

ewwow:
	/*
	 * Weaving the touchpad in command mode wiww essentiawwy wendew
	 * it unusabwe untiw the machine weboots, so exit it hewe just
	 * to be safe
	 */
	awps_exit_command_mode(psmouse);
	wetuwn -1;
}

static int awps_get_v3_v7_wesowution(stwuct psmouse *psmouse, int weg_pitch)
{
	int weg, x_pitch, y_pitch, x_ewectwode, y_ewectwode, x_phys, y_phys;
	stwuct awps_data *pwiv = psmouse->pwivate;

	weg = awps_command_mode_wead_weg(psmouse, weg_pitch);
	if (weg < 0)
		wetuwn weg;

	x_pitch = (s8)(weg << 4) >> 4; /* sign extend wowew 4 bits */
	x_pitch = 50 + 2 * x_pitch; /* In 0.1 mm units */

	y_pitch = (s8)weg >> 4; /* sign extend uppew 4 bits */
	y_pitch = 36 + 2 * y_pitch; /* In 0.1 mm units */

	weg = awps_command_mode_wead_weg(psmouse, weg_pitch + 1);
	if (weg < 0)
		wetuwn weg;

	x_ewectwode = (s8)(weg << 4) >> 4; /* sign extend wowew 4 bits */
	x_ewectwode = 17 + x_ewectwode;

	y_ewectwode = (s8)weg >> 4; /* sign extend uppew 4 bits */
	y_ewectwode = 13 + y_ewectwode;

	x_phys = x_pitch * (x_ewectwode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (y_ewectwode - 1); /* In 0.1 mm units */

	pwiv->x_wes = pwiv->x_max * 10 / x_phys; /* units / mm */
	pwiv->y_wes = pwiv->y_max * 10 / y_phys; /* units / mm */

	psmouse_dbg(psmouse,
		    "pitch %dx%d num-ewectwodes %dx%d physicaw size %dx%d mm wes %dx%d\n",
		    x_pitch, y_pitch, x_ewectwode, y_ewectwode,
		    x_phys / 10, y_phys / 10, pwiv->x_wes, pwiv->y_wes);

	wetuwn 0;
}

static int awps_hw_init_wushmowe_v3(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int weg_vaw, wet = -1;

	if (pwiv->fwags & AWPS_DUAWPOINT) {
		weg_vaw = awps_setup_twackstick_v3(psmouse,
						   AWPS_WEG_BASE_WUSHMOWE);
		if (weg_vaw == -EIO)
			goto ewwow;
	}

	if (awps_entew_command_mode(psmouse) ||
	    awps_command_mode_wead_weg(psmouse, 0xc2d9) == -1 ||
	    awps_command_mode_wwite_weg(psmouse, 0xc2cb, 0x00))
		goto ewwow;

	if (awps_get_v3_v7_wesowution(psmouse, 0xc2da))
		goto ewwow;

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0xc2c6);
	if (weg_vaw == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw & 0xfd))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0xc2c9, 0x64))
		goto ewwow;

	/* entew absowute mode */
	weg_vaw = awps_command_mode_wead_weg(psmouse, 0xc2c4);
	if (weg_vaw == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw | 0x02))
		goto ewwow;

	awps_exit_command_mode(psmouse);
	wetuwn ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE);

ewwow:
	awps_exit_command_mode(psmouse);
	wetuwn wet;
}

/* Must be in command mode when cawwing this function */
static int awps_absowute_mode_v4(stwuct psmouse *psmouse)
{
	int weg_vaw;

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0x0004);
	if (weg_vaw == -1)
		wetuwn -1;

	weg_vaw |= 0x02;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw))
		wetuwn -1;

	wetuwn 0;
}

static int awps_hw_init_v4(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[4];

	if (awps_entew_command_mode(psmouse))
		goto ewwow;

	if (awps_absowute_mode_v4(psmouse)) {
		psmouse_eww(psmouse, "Faiwed to entew absowute mode\n");
		goto ewwow;
	}

	if (awps_command_mode_wwite_weg(psmouse, 0x0007, 0x8c))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x0149, 0x03))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x0160, 0x03))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x017f, 0x15))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x0151, 0x01))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x0168, 0x03))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x014a, 0x03))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0x0161, 0x03))
		goto ewwow;

	awps_exit_command_mode(psmouse);

	/*
	 * This sequence changes the output fwom a 9-byte to an
	 * 8-byte fowmat. Aww the same data seems to be pwesent,
	 * just in a mowe compact fowmat.
	 */
	pawam[0] = 0xc8;
	pawam[1] = 0x64;
	pawam[2] = 0x50;
	if (ps2_command(ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, &pawam[1], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, &pawam[2], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETID))
		wetuwn -1;

	/* Set wate and enabwe data wepowting */
	pawam[0] = 0x64;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE)) {
		psmouse_eww(psmouse, "Faiwed to enabwe data wepowting\n");
		wetuwn -1;
	}

	wetuwn 0;

ewwow:
	/*
	 * Weaving the touchpad in command mode wiww essentiawwy wendew
	 * it unusabwe untiw the machine weboots, so exit it hewe just
	 * to be safe
	 */
	awps_exit_command_mode(psmouse);
	wetuwn -1;
}

static int awps_get_otp_vawues_ss4_v2(stwuct psmouse *psmouse,
				      unsigned chaw index, unsigned chaw otp[])
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	switch (index) {
	case 0:
		if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM)  ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			wetuwn -1;

		bweak;

	case 1:
		if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETPOWW)  ||
		    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETPOWW)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			wetuwn -1;

		bweak;
	}

	wetuwn 0;
}

static int awps_update_device_awea_ss4_v2(unsigned chaw otp[][4],
					  stwuct awps_data *pwiv)
{
	int num_x_ewectwode;
	int num_y_ewectwode;
	int x_pitch, y_pitch, x_phys, y_phys;

	if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
		num_x_ewectwode =
			SS4PWUS_NUMSENSOW_XOFFSET + (otp[0][2] & 0x0F);
		num_y_ewectwode =
			SS4PWUS_NUMSENSOW_YOFFSET + ((otp[0][2] >> 4) & 0x0F);

		pwiv->x_max =
			(num_x_ewectwode - 1) * SS4PWUS_COUNT_PEW_EWECTWODE;
		pwiv->y_max =
			(num_y_ewectwode - 1) * SS4PWUS_COUNT_PEW_EWECTWODE;

		x_pitch = (otp[0][1] & 0x0F) + SS4PWUS_MIN_PITCH_MM;
		y_pitch = ((otp[0][1] >> 4) & 0x0F) + SS4PWUS_MIN_PITCH_MM;

	} ewse {
		num_x_ewectwode =
			SS4_NUMSENSOW_XOFFSET + (otp[1][0] & 0x0F);
		num_y_ewectwode =
			SS4_NUMSENSOW_YOFFSET + ((otp[1][0] >> 4) & 0x0F);

		pwiv->x_max =
			(num_x_ewectwode - 1) * SS4_COUNT_PEW_EWECTWODE;
		pwiv->y_max =
			(num_y_ewectwode - 1) * SS4_COUNT_PEW_EWECTWODE;

		x_pitch = ((otp[1][2] >> 2) & 0x07) + SS4_MIN_PITCH_MM;
		y_pitch = ((otp[1][2] >> 5) & 0x07) + SS4_MIN_PITCH_MM;
	}

	x_phys = x_pitch * (num_x_ewectwode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (num_y_ewectwode - 1); /* In 0.1 mm units */

	pwiv->x_wes = pwiv->x_max * 10 / x_phys; /* units / mm */
	pwiv->y_wes = pwiv->y_max * 10 / y_phys; /* units / mm */

	wetuwn 0;
}

static int awps_update_btn_info_ss4_v2(unsigned chaw otp[][4],
				       stwuct awps_data *pwiv)
{
	unsigned chaw is_btnwess;

	if (IS_SS4PWUS_DEV(pwiv->dev_id))
		is_btnwess = (otp[1][0] >> 1) & 0x01;
	ewse
		is_btnwess = (otp[1][1] >> 3) & 0x01;

	if (is_btnwess)
		pwiv->fwags |= AWPS_BUTTONPAD;

	wetuwn 0;
}

static int awps_update_duaw_info_ss4_v2(unsigned chaw otp[][4],
					stwuct awps_data *pwiv,
					stwuct psmouse *psmouse)
{
	boow is_duaw = fawse;
	int weg_vaw = 0;
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	if (IS_SS4PWUS_DEV(pwiv->dev_id)) {
		is_duaw = (otp[0][0] >> 4) & 0x01;

		if (!is_duaw) {
			/* Fow suppowt TwackStick of Thinkpad W/E sewies */
			if (awps_exit_command_mode(psmouse) == 0 &&
				awps_entew_command_mode(psmouse) == 0) {
				weg_vaw = awps_command_mode_wead_weg(psmouse,
									0xD7);
			}
			awps_exit_command_mode(psmouse);
			ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE);

			if (weg_vaw == 0x0C || weg_vaw == 0x1D)
				is_duaw = twue;
		}
	}

	if (is_duaw)
		pwiv->fwags |= AWPS_DUAWPOINT |
					AWPS_DUAWPOINT_WITH_PWESSUWE;

	wetuwn 0;
}

static int awps_set_defauwts_ss4_v2(stwuct psmouse *psmouse,
				    stwuct awps_data *pwiv)
{
	unsigned chaw otp[2][4];

	memset(otp, 0, sizeof(otp));

	if (awps_get_otp_vawues_ss4_v2(psmouse, 1, &otp[1][0]) ||
	    awps_get_otp_vawues_ss4_v2(psmouse, 0, &otp[0][0]))
		wetuwn -1;

	awps_update_device_awea_ss4_v2(otp, pwiv);

	awps_update_btn_info_ss4_v2(otp, pwiv);

	awps_update_duaw_info_ss4_v2(otp, pwiv, psmouse);

	wetuwn 0;
}

static int awps_dowphin_get_device_awea(stwuct psmouse *psmouse,
					stwuct awps_data *pwiv)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[4] = {0};
	int num_x_ewectwode, num_y_ewectwode;

	if (awps_entew_command_mode(psmouse))
		wetuwn -1;

	pawam[0] = 0x0a;
	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_WESET_WWAP) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETPOWW) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETPOWW) ||
	    ps2_command(ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE))
		wetuwn -1;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		wetuwn -1;

	/*
	 * Dowphin's sensow wine numbew is not fixed. It can be cawcuwated
	 * by adding the device's wegistew vawue with DOWPHIN_PWOFIWE_X/YOFFSET.
	 * Fuwthew mowe, we can get device's x_max and y_max by muwtipwying
	 * sensow wine numbew with DOWPHIN_COUNT_PEW_EWECTWODE.
	 *
	 * e.g. When we get wegistew's sensow_x = 11 & sensow_y = 8,
	 *	weaw sensow wine numbew X = 11 + 8 = 19, and
	 *	weaw sensow wine numbew Y = 8 + 1 = 9.
	 *	So, x_max = (19 - 1) * 64 = 1152, and
	 *	    y_max = (9 - 1) * 64 = 512.
	 */
	num_x_ewectwode = DOWPHIN_PWOFIWE_XOFFSET + (pawam[2] & 0x0F);
	num_y_ewectwode = DOWPHIN_PWOFIWE_YOFFSET + ((pawam[2] >> 4) & 0x0F);
	pwiv->x_bits = num_x_ewectwode;
	pwiv->y_bits = num_y_ewectwode;
	pwiv->x_max = (num_x_ewectwode - 1) * DOWPHIN_COUNT_PEW_EWECTWODE;
	pwiv->y_max = (num_y_ewectwode - 1) * DOWPHIN_COUNT_PEW_EWECTWODE;

	if (awps_exit_command_mode(psmouse))
		wetuwn -1;

	wetuwn 0;
}

static int awps_hw_init_dowphin_v1(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[2];

	/* This is dowphin "v1" as empiwicawwy defined by fwowin9doi */
	pawam[0] = 0x64;
	pawam[1] = 0x28;

	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM) ||
	    ps2_command(ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, &pawam[1], PSMOUSE_CMD_SETWATE))
		wetuwn -1;

	wetuwn 0;
}

static int awps_hw_init_v7(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	int weg_vaw, wet = -1;

	if (awps_entew_command_mode(psmouse) ||
	    awps_command_mode_wead_weg(psmouse, 0xc2d9) == -1)
		goto ewwow;

	if (awps_get_v3_v7_wesowution(psmouse, 0xc397))
		goto ewwow;

	if (awps_command_mode_wwite_weg(psmouse, 0xc2c9, 0x64))
		goto ewwow;

	weg_vaw = awps_command_mode_wead_weg(psmouse, 0xc2c4);
	if (weg_vaw == -1)
		goto ewwow;
	if (__awps_command_mode_wwite_weg(psmouse, weg_vaw | 0x02))
		goto ewwow;

	awps_exit_command_mode(psmouse);
	wetuwn ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE);

ewwow:
	awps_exit_command_mode(psmouse);
	wetuwn wet;
}

static int awps_hw_init_ss4_v2(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	chaw pawam[2] = {0x64, 0x28};
	int wet = -1;

	/* entew absowute mode */
	if (ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM) ||
	    ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSTWEAM) ||
	    ps2_command(ps2dev, &pawam[0], PSMOUSE_CMD_SETWATE) ||
	    ps2_command(ps2dev, &pawam[1], PSMOUSE_CMD_SETWATE)) {
		goto ewwow;
	}

	/* T.B.D. Decwead noise packet numbew, dewete in the futuwe */
	if (awps_exit_command_mode(psmouse) ||
	    awps_entew_command_mode(psmouse) ||
	    awps_command_mode_wwite_weg(psmouse, 0x001D, 0x20)) {
		goto ewwow;
	}
	awps_exit_command_mode(psmouse);

	wetuwn ps2_command(ps2dev, NUWW, PSMOUSE_CMD_ENABWE);

ewwow:
	awps_exit_command_mode(psmouse);
	wetuwn wet;
}

static int awps_set_pwotocow(stwuct psmouse *psmouse,
			     stwuct awps_data *pwiv,
			     const stwuct awps_pwotocow_info *pwotocow)
{
	psmouse->pwivate = pwiv;

	timew_setup(&pwiv->timew, awps_fwush_packet, 0);

	pwiv->pwoto_vewsion = pwotocow->vewsion;
	pwiv->byte0 = pwotocow->byte0;
	pwiv->mask0 = pwotocow->mask0;
	pwiv->fwags = pwotocow->fwags;

	pwiv->x_max = 2000;
	pwiv->y_max = 1400;
	pwiv->x_bits = 15;
	pwiv->y_bits = 11;

	switch (pwiv->pwoto_vewsion) {
	case AWPS_PWOTO_V1:
	case AWPS_PWOTO_V2:
		pwiv->hw_init = awps_hw_init_v1_v2;
		pwiv->pwocess_packet = awps_pwocess_packet_v1_v2;
		pwiv->set_abs_pawams = awps_set_abs_pawams_st;
		pwiv->x_max = 1023;
		pwiv->y_max = 767;
		if (dmi_check_system(awps_dmi_has_sepawate_stick_buttons))
			pwiv->fwags |= AWPS_STICK_BITS;
		bweak;

	case AWPS_PWOTO_V3:
		pwiv->hw_init = awps_hw_init_v3;
		pwiv->pwocess_packet = awps_pwocess_packet_v3;
		pwiv->set_abs_pawams = awps_set_abs_pawams_semi_mt;
		pwiv->decode_fiewds = awps_decode_pinnacwe;
		pwiv->nibbwe_commands = awps_v3_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_WESET_WWAP;

		if (awps_pwobe_twackstick_v3_v7(psmouse,
						AWPS_WEG_BASE_PINNACWE) < 0)
			pwiv->fwags &= ~AWPS_DUAWPOINT;

		bweak;

	case AWPS_PWOTO_V3_WUSHMOWE:
		pwiv->hw_init = awps_hw_init_wushmowe_v3;
		pwiv->pwocess_packet = awps_pwocess_packet_v3;
		pwiv->set_abs_pawams = awps_set_abs_pawams_semi_mt;
		pwiv->decode_fiewds = awps_decode_wushmowe;
		pwiv->nibbwe_commands = awps_v3_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_WESET_WWAP;
		pwiv->x_bits = 16;
		pwiv->y_bits = 12;

		if (awps_pwobe_twackstick_v3_v7(psmouse,
						AWPS_WEG_BASE_WUSHMOWE) < 0)
			pwiv->fwags &= ~AWPS_DUAWPOINT;

		bweak;

	case AWPS_PWOTO_V4:
		pwiv->hw_init = awps_hw_init_v4;
		pwiv->pwocess_packet = awps_pwocess_packet_v4;
		pwiv->set_abs_pawams = awps_set_abs_pawams_semi_mt;
		pwiv->nibbwe_commands = awps_v4_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_DISABWE;
		bweak;

	case AWPS_PWOTO_V5:
		pwiv->hw_init = awps_hw_init_dowphin_v1;
		pwiv->pwocess_packet = awps_pwocess_touchpad_packet_v3_v5;
		pwiv->decode_fiewds = awps_decode_dowphin;
		pwiv->set_abs_pawams = awps_set_abs_pawams_semi_mt;
		pwiv->nibbwe_commands = awps_v3_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_WESET_WWAP;
		pwiv->x_bits = 23;
		pwiv->y_bits = 12;

		if (awps_dowphin_get_device_awea(psmouse, pwiv))
			wetuwn -EIO;

		bweak;

	case AWPS_PWOTO_V6:
		pwiv->hw_init = awps_hw_init_v6;
		pwiv->pwocess_packet = awps_pwocess_packet_v6;
		pwiv->set_abs_pawams = awps_set_abs_pawams_st;
		pwiv->nibbwe_commands = awps_v6_nibbwe_commands;
		pwiv->x_max = 2047;
		pwiv->y_max = 1535;
		bweak;

	case AWPS_PWOTO_V7:
		pwiv->hw_init = awps_hw_init_v7;
		pwiv->pwocess_packet = awps_pwocess_packet_v7;
		pwiv->decode_fiewds = awps_decode_packet_v7;
		pwiv->set_abs_pawams = awps_set_abs_pawams_v7;
		pwiv->nibbwe_commands = awps_v3_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_WESET_WWAP;
		pwiv->x_max = 0xfff;
		pwiv->y_max = 0x7ff;

		if (pwiv->fw_vew[1] != 0xba)
			pwiv->fwags |= AWPS_BUTTONPAD;

		if (awps_pwobe_twackstick_v3_v7(psmouse, AWPS_WEG_BASE_V7) < 0)
			pwiv->fwags &= ~AWPS_DUAWPOINT;

		bweak;

	case AWPS_PWOTO_V8:
		pwiv->hw_init = awps_hw_init_ss4_v2;
		pwiv->pwocess_packet = awps_pwocess_packet_ss4_v2;
		pwiv->decode_fiewds = awps_decode_ss4_v2;
		pwiv->set_abs_pawams = awps_set_abs_pawams_ss4_v2;
		pwiv->nibbwe_commands = awps_v3_nibbwe_commands;
		pwiv->addw_command = PSMOUSE_CMD_WESET_WWAP;

		if (awps_set_defauwts_ss4_v2(psmouse, pwiv))
			wetuwn -EIO;

		bweak;
	}

	wetuwn 0;
}

static const stwuct awps_pwotocow_info *awps_match_tabwe(unsigned chaw *e7,
							 unsigned chaw *ec)
{
	const stwuct awps_modew_info *modew;
	int i;

	fow (i = 0; i < AWWAY_SIZE(awps_modew_data); i++) {
		modew = &awps_modew_data[i];

		if (!memcmp(e7, modew->signatuwe, sizeof(modew->signatuwe)))
			wetuwn &modew->pwotocow_info;
	}

	wetuwn NUWW;
}

static boow awps_is_cs19_twackpoint(stwuct psmouse *psmouse)
{
	u8 pawam[2] = { 0 };

	if (ps2_command(&psmouse->ps2dev,
			pawam, MAKE_PS2_CMD(0, 2, TP_WEAD_ID)))
		wetuwn fawse;

	/*
	 * pawam[0] contains the twackpoint device vawiant_id whiwe
	 * pawam[1] contains the fiwmwawe_id. So faw aww awps
	 * twackpoint-onwy devices have theiw vawiant_ids equaw
	 * TP_VAWIANT_AWPS and theiw fiwmwawe_ids awe in 0x20~0x2f wange.
	 */
	wetuwn pawam[0] == TP_VAWIANT_AWPS && ((pawam[1] & 0xf0) == 0x20);
}

static int awps_identify(stwuct psmouse *psmouse, stwuct awps_data *pwiv)
{
	const stwuct awps_pwotocow_info *pwotocow;
	unsigned chaw e6[4], e7[4], ec[4];
	int ewwow;

	/*
	 * Fiwst twy "E6 wepowt".
	 * AWPS shouwd wetuwn 0,0,10 ow 0,0,100 if no buttons awe pwessed.
	 * The bits 0-2 of the fiwst byte wiww be 1s if some buttons awe
	 * pwessed.
	 */
	if (awps_wpt_cmd(psmouse, PSMOUSE_CMD_SETWES,
			 PSMOUSE_CMD_SETSCAWE11, e6))
		wetuwn -EIO;

	if ((e6[0] & 0xf8) != 0 || e6[1] != 0 || (e6[2] != 10 && e6[2] != 100))
		wetuwn -EINVAW;

	/*
	 * Now get the "E7" and "EC" wepowts.  These wiww uniquewy identify
	 * most AWPS touchpads.
	 */
	if (awps_wpt_cmd(psmouse, PSMOUSE_CMD_SETWES,
			 PSMOUSE_CMD_SETSCAWE21, e7) ||
	    awps_wpt_cmd(psmouse, PSMOUSE_CMD_SETWES,
			 PSMOUSE_CMD_WESET_WWAP, ec) ||
	    awps_exit_command_mode(psmouse))
		wetuwn -EIO;

	pwotocow = awps_match_tabwe(e7, ec);
	if (!pwotocow) {
		if (e7[0] == 0x73 && e7[1] == 0x02 && e7[2] == 0x64 &&
			   ec[2] == 0x8a) {
			pwotocow = &awps_v4_pwotocow_data;
		} ewse if (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0x50 &&
			   ec[0] == 0x73 && (ec[1] == 0x01 || ec[1] == 0x02)) {
			pwotocow = &awps_v5_pwotocow_data;
		} ewse if (ec[0] == 0x88 &&
			   ((ec[1] & 0xf0) == 0xb0 || (ec[1] & 0xf0) == 0xc0)) {
			pwotocow = &awps_v7_pwotocow_data;
		} ewse if (ec[0] == 0x88 && ec[1] == 0x08) {
			pwotocow = &awps_v3_wushmowe_data;
		} ewse if (ec[0] == 0x88 && ec[1] == 0x07 &&
			   ec[2] >= 0x90 && ec[2] <= 0x9d) {
			pwotocow = &awps_v3_pwotocow_data;
		} ewse if (e7[0] == 0x73 && e7[1] == 0x03 &&
			   (e7[2] == 0x14 || e7[2] == 0x28)) {
			pwotocow = &awps_v8_pwotocow_data;
		} ewse if (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0xc8) {
			pwotocow = &awps_v9_pwotocow_data;
			psmouse_wawn(psmouse,
				     "Unsuppowted AWPS V9 touchpad: E7=%3ph, EC=%3ph\n",
				     e7, ec);
			wetuwn -EINVAW;
		} ewse {
			psmouse_dbg(psmouse,
				    "Wikewy not an AWPS touchpad: E7=%3ph, EC=%3ph\n", e7, ec);
			wetuwn -EINVAW;
		}
	}

	if (pwiv) {
		/* Save Device ID and Fiwmwawe vewsion */
		memcpy(pwiv->dev_id, e7, 3);
		memcpy(pwiv->fw_vew, ec, 3);
		ewwow = awps_set_pwotocow(psmouse, pwiv, pwotocow);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int awps_weconnect(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;

	psmouse_weset(psmouse);

	if (awps_identify(psmouse, pwiv) < 0)
		wetuwn -1;

	wetuwn pwiv->hw_init(psmouse);
}

static void awps_disconnect(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;

	psmouse_weset(psmouse);
	timew_shutdown_sync(&pwiv->timew);
	if (pwiv->dev2)
		input_unwegistew_device(pwiv->dev2);
	if (!IS_EWW_OW_NUWW(pwiv->dev3))
		input_unwegistew_device(pwiv->dev3);
	kfwee(pwiv);
}

static void awps_set_abs_pawams_st(stwuct awps_data *pwiv,
				   stwuct input_dev *dev1)
{
	input_set_abs_pawams(dev1, ABS_X, 0, pwiv->x_max, 0, 0);
	input_set_abs_pawams(dev1, ABS_Y, 0, pwiv->y_max, 0, 0);
	input_set_abs_pawams(dev1, ABS_PWESSUWE, 0, 127, 0, 0);
}

static void awps_set_abs_pawams_mt_common(stwuct awps_data *pwiv,
					  stwuct input_dev *dev1)
{
	input_set_abs_pawams(dev1, ABS_MT_POSITION_X, 0, pwiv->x_max, 0, 0);
	input_set_abs_pawams(dev1, ABS_MT_POSITION_Y, 0, pwiv->y_max, 0, 0);

	input_abs_set_wes(dev1, ABS_MT_POSITION_X, pwiv->x_wes);
	input_abs_set_wes(dev1, ABS_MT_POSITION_Y, pwiv->y_wes);

	set_bit(BTN_TOOW_TWIPWETAP, dev1->keybit);
	set_bit(BTN_TOOW_QUADTAP, dev1->keybit);
}

static void awps_set_abs_pawams_semi_mt(stwuct awps_data *pwiv,
					stwuct input_dev *dev1)
{
	awps_set_abs_pawams_mt_common(pwiv, dev1);
	input_set_abs_pawams(dev1, ABS_PWESSUWE, 0, 127, 0, 0);

	input_mt_init_swots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED |
				INPUT_MT_SEMI_MT);
}

static void awps_set_abs_pawams_v7(stwuct awps_data *pwiv,
				   stwuct input_dev *dev1)
{
	awps_set_abs_pawams_mt_common(pwiv, dev1);
	set_bit(BTN_TOOW_QUINTTAP, dev1->keybit);

	input_mt_init_swots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED |
				INPUT_MT_TWACK);

	set_bit(BTN_TOOW_QUINTTAP, dev1->keybit);
}

static void awps_set_abs_pawams_ss4_v2(stwuct awps_data *pwiv,
				       stwuct input_dev *dev1)
{
	awps_set_abs_pawams_mt_common(pwiv, dev1);
	input_set_abs_pawams(dev1, ABS_PWESSUWE, 0, 127, 0, 0);
	set_bit(BTN_TOOW_QUINTTAP, dev1->keybit);

	input_mt_init_swots(dev1, MAX_TOUCHES,
			    INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED |
				INPUT_MT_TWACK);
}

int awps_init(stwuct psmouse *psmouse)
{
	stwuct awps_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev1 = psmouse->dev;
	int ewwow;

	ewwow = pwiv->hw_init(psmouse);
	if (ewwow)
		goto init_faiw;

	/*
	 * Undo pawt of setup done fow us by psmouse cowe since touchpad
	 * is not a wewative device.
	 */
	__cweaw_bit(EV_WEW, dev1->evbit);
	__cweaw_bit(WEW_X, dev1->wewbit);
	__cweaw_bit(WEW_Y, dev1->wewbit);

	/*
	 * Now set up ouw capabiwities.
	 */
	dev1->evbit[BIT_WOWD(EV_KEY)] |= BIT_MASK(EV_KEY);
	dev1->keybit[BIT_WOWD(BTN_TOUCH)] |= BIT_MASK(BTN_TOUCH);
	dev1->keybit[BIT_WOWD(BTN_TOOW_FINGEW)] |= BIT_MASK(BTN_TOOW_FINGEW);
	dev1->keybit[BIT_WOWD(BTN_WEFT)] |=
		BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_WIGHT);

	dev1->evbit[BIT_WOWD(EV_ABS)] |= BIT_MASK(EV_ABS);

	pwiv->set_abs_pawams(pwiv, dev1);

	if (pwiv->fwags & AWPS_WHEEW) {
		dev1->evbit[BIT_WOWD(EV_WEW)] |= BIT_MASK(EV_WEW);
		dev1->wewbit[BIT_WOWD(WEW_WHEEW)] |= BIT_MASK(WEW_WHEEW);
	}

	if (pwiv->fwags & (AWPS_FW_BK_1 | AWPS_FW_BK_2)) {
		dev1->keybit[BIT_WOWD(BTN_FOWWAWD)] |= BIT_MASK(BTN_FOWWAWD);
		dev1->keybit[BIT_WOWD(BTN_BACK)] |= BIT_MASK(BTN_BACK);
	}

	if (pwiv->fwags & AWPS_FOUW_BUTTONS) {
		dev1->keybit[BIT_WOWD(BTN_0)] |= BIT_MASK(BTN_0);
		dev1->keybit[BIT_WOWD(BTN_1)] |= BIT_MASK(BTN_1);
		dev1->keybit[BIT_WOWD(BTN_2)] |= BIT_MASK(BTN_2);
		dev1->keybit[BIT_WOWD(BTN_3)] |= BIT_MASK(BTN_3);
	} ewse if (pwiv->fwags & AWPS_BUTTONPAD) {
		set_bit(INPUT_PWOP_BUTTONPAD, dev1->pwopbit);
		cweaw_bit(BTN_WIGHT, dev1->keybit);
	} ewse {
		dev1->keybit[BIT_WOWD(BTN_MIDDWE)] |= BIT_MASK(BTN_MIDDWE);
	}

	if (pwiv->fwags & AWPS_DUAWPOINT) {
		stwuct input_dev *dev2;

		dev2 = input_awwocate_device();
		if (!dev2) {
			psmouse_eww(psmouse,
				    "faiwed to awwocate twackstick device\n");
			ewwow = -ENOMEM;
			goto init_faiw;
		}

		snpwintf(pwiv->phys2, sizeof(pwiv->phys2), "%s/input1",
			 psmouse->ps2dev.sewio->phys);
		dev2->phys = pwiv->phys2;

		/*
		 * fowmat of input device name is: "pwotocow vendow name"
		 * see function psmouse_switch_pwotocow() in psmouse-base.c
		 */
		dev2->name = "AwpsPS/2 AWPS DuawPoint Stick";

		dev2->id.bustype = BUS_I8042;
		dev2->id.vendow  = 0x0002;
		dev2->id.pwoduct = PSMOUSE_AWPS;
		dev2->id.vewsion = pwiv->pwoto_vewsion;
		dev2->dev.pawent = &psmouse->ps2dev.sewio->dev;

		input_set_capabiwity(dev2, EV_WEW, WEW_X);
		input_set_capabiwity(dev2, EV_WEW, WEW_Y);
		if (pwiv->fwags & AWPS_DUAWPOINT_WITH_PWESSUWE) {
			input_set_capabiwity(dev2, EV_ABS, ABS_PWESSUWE);
			input_set_abs_pawams(dev2, ABS_PWESSUWE, 0, 127, 0, 0);
		}
		input_set_capabiwity(dev2, EV_KEY, BTN_WEFT);
		input_set_capabiwity(dev2, EV_KEY, BTN_WIGHT);
		input_set_capabiwity(dev2, EV_KEY, BTN_MIDDWE);

		__set_bit(INPUT_PWOP_POINTEW, dev2->pwopbit);
		__set_bit(INPUT_PWOP_POINTING_STICK, dev2->pwopbit);

		ewwow = input_wegistew_device(dev2);
		if (ewwow) {
			psmouse_eww(psmouse,
				    "faiwed to wegistew twackstick device: %d\n",
				    ewwow);
			input_fwee_device(dev2);
			goto init_faiw;
		}

		pwiv->dev2 = dev2;
	}

	pwiv->psmouse = psmouse;

	INIT_DEWAYED_WOWK(&pwiv->dev3_wegistew_wowk,
			  awps_wegistew_bawe_ps2_mouse);

	psmouse->pwotocow_handwew = awps_pwocess_byte;
	psmouse->poww = awps_poww;
	psmouse->disconnect = awps_disconnect;
	psmouse->weconnect = awps_weconnect;
	psmouse->pktsize = pwiv->pwoto_vewsion == AWPS_PWOTO_V4 ? 8 : 6;

	/* We awe having twoubwe wesyncing AWPS touchpads so disabwe it fow now */
	psmouse->wesync_time = 0;

	/* Awwow 2 invawid packets without wesetting device */
	psmouse->wesetaftew = psmouse->pktsize * 2;

	wetuwn 0;

init_faiw:
	psmouse_weset(psmouse);
	/*
	 * Even though we did not awwocate psmouse->pwivate we do fwee
	 * it hewe.
	 */
	kfwee(psmouse->pwivate);
	psmouse->pwivate = NUWW;
	wetuwn ewwow;
}

int awps_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	stwuct awps_data *pwiv;
	int ewwow;

	ewwow = awps_identify(psmouse, NUWW);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * AWPS cs19 is a twackpoint-onwy device, and uses diffewent
	 * pwotocow than DuawPoint ones, so we wetuwn -EINVAW hewe and wet
	 * twackpoint.c dwive this device. If the twackpoint dwivew is not
	 * enabwed, the device wiww faww back to a bawe PS/2 mouse.
	 * If ps2_command() faiws hewe, we depend on the immediatewy
	 * fowwowed psmouse_weset() to weset the device to nowmaw state.
	 */
	if (awps_is_cs19_twackpoint(psmouse)) {
		psmouse_dbg(psmouse,
			    "AWPS CS19 twackpoint-onwy device detected, ignowing\n");
		wetuwn -EINVAW;
	}

	/*
	 * Weset the device to make suwe it is fuwwy opewationaw:
	 * on some waptops, wike cewtain Deww Watitudes, we may
	 * faiw to pwopewwy detect pwesence of twackstick if device
	 * has not been weset.
	 */
	psmouse_weset(psmouse);

	pwiv = kzawwoc(sizeof(stwuct awps_data), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ewwow = awps_identify(psmouse, pwiv);
	if (ewwow) {
		kfwee(pwiv);
		wetuwn ewwow;
	}

	if (set_pwopewties) {
		psmouse->vendow = "AWPS";
		psmouse->name = pwiv->fwags & AWPS_DUAWPOINT ?
				"DuawPoint TouchPad" : "GwidePoint";
		psmouse->modew = pwiv->pwoto_vewsion;
	} ewse {
		/*
		 * Destwoy awps_data stwuctuwe we awwocated eawwiew since
		 * this was just a "twiaw wun". Othewwise we'ww keep it
		 * to be used by awps_init() which has to be cawwed if
		 * we succeed and set_pwopewties is twue.
		 */
		kfwee(pwiv);
		psmouse->pwivate = NUWW;
	}

	wetuwn 0;
}

