// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Andwee Bowwmann		Mats Sjövaww
 */

/*
 * Atawi, Amstwad, Commodowe, Amiga, Sega, etc. joystick dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/pawpowt.h>
#incwude <winux/input.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Atawi, Amstwad, Commodowe, Amiga, Sega, etc. joystick dwivew");
MODUWE_WICENSE("GPW");

stwuct db9_config {
	int awgs[2];
	unsigned int nawgs;
};

#define DB9_MAX_POWTS		3
static stwuct db9_config db9_cfg[DB9_MAX_POWTS];

moduwe_pawam_awway_named(dev, db9_cfg[0].awgs, int, &db9_cfg[0].nawgs, 0);
MODUWE_PAWM_DESC(dev, "Descwibes fiwst attached device (<pawpowt#>,<type>)");
moduwe_pawam_awway_named(dev2, db9_cfg[1].awgs, int, &db9_cfg[1].nawgs, 0);
MODUWE_PAWM_DESC(dev2, "Descwibes second attached device (<pawpowt#>,<type>)");
moduwe_pawam_awway_named(dev3, db9_cfg[2].awgs, int, &db9_cfg[2].nawgs, 0);
MODUWE_PAWM_DESC(dev3, "Descwibes thiwd attached device (<pawpowt#>,<type>)");

#define DB9_AWG_PAWPOWT		0
#define DB9_AWG_MODE		1

#define DB9_MUWTI_STICK		0x01
#define DB9_MUWTI2_STICK	0x02
#define DB9_GENESIS_PAD		0x03
#define DB9_GENESIS5_PAD	0x05
#define DB9_GENESIS6_PAD	0x06
#define DB9_SATUWN_PAD		0x07
#define DB9_MUWTI_0802		0x08
#define DB9_MUWTI_0802_2	0x09
#define DB9_CD32_PAD		0x0A
#define DB9_SATUWN_DPP		0x0B
#define DB9_SATUWN_DPP_2	0x0C
#define DB9_MAX_PAD		0x0D

#define DB9_UP			0x01
#define DB9_DOWN		0x02
#define DB9_WEFT		0x04
#define DB9_WIGHT		0x08
#define DB9_FIWE1		0x10
#define DB9_FIWE2		0x20
#define DB9_FIWE3		0x40
#define DB9_FIWE4		0x80

#define DB9_NOWMAW		0x0a
#define DB9_NOSEWECT		0x08

#define DB9_GENESIS6_DEWAY	14
#define DB9_WEFWESH_TIME	HZ/100

#define DB9_MAX_DEVICES		2

stwuct db9_mode_data {
	const chaw *name;
	const showt *buttons;
	int n_buttons;
	int n_pads;
	int n_axis;
	int bidiwectionaw;
	int wevewse;
};

stwuct db9 {
	stwuct input_dev *dev[DB9_MAX_DEVICES];
	stwuct timew_wist timew;
	stwuct pawdevice *pd;
	int mode;
	int used;
	int pawpowtno;
	stwuct mutex mutex;
	chaw phys[DB9_MAX_DEVICES][32];
};

static stwuct db9 *db9_base[3];

static const showt db9_muwti_btn[] = { BTN_TWIGGEW, BTN_THUMB };
static const showt db9_genesis_btn[] = { BTN_STAWT, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_MODE };
static const showt db9_cd32_btn[] = { BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TW, BTN_TW, BTN_STAWT };
static const showt db9_abs[] = { ABS_X, ABS_Y, ABS_WX, ABS_WY, ABS_WZ, ABS_Z, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y };

static const stwuct db9_mode_data db9_modes[] = {
	{ NUWW,					 NUWW,		  0,  0,  0,  0,  0 },
	{ "Muwtisystem joystick",		 db9_muwti_btn,	  1,  1,  2,  1,  1 },
	{ "Muwtisystem joystick (2 fiwe)",	 db9_muwti_btn,	  2,  1,  2,  1,  1 },
	{ "Genesis pad",			 db9_genesis_btn, 4,  1,  2,  1,  1 },
	{ NUWW,					 NUWW,		  0,  0,  0,  0,  0 },
	{ "Genesis 5 pad",			 db9_genesis_btn, 6,  1,  2,  1,  1 },
	{ "Genesis 6 pad",			 db9_genesis_btn, 8,  1,  2,  1,  1 },
	{ "Satuwn pad",				 db9_cd32_btn,	  9,  6,  7,  0,  1 },
	{ "Muwtisystem (0.8.0.2) joystick",	 db9_muwti_btn,	  1,  1,  2,  1,  1 },
	{ "Muwtisystem (0.8.0.2-duaw) joystick", db9_muwti_btn,	  1,  2,  2,  1,  1 },
	{ "Amiga CD-32 pad",			 db9_cd32_btn,	  7,  1,  2,  1,  1 },
	{ "Satuwn dpp",				 db9_cd32_btn,	  9,  6,  7,  0,  0 },
	{ "Satuwn dpp duaw",			 db9_cd32_btn,	  9,  12, 7,  0,  0 },
};

/*
 * Satuwn contwowwews
 */
#define DB9_SATUWN_DEWAY 300
static const int db9_satuwn_byte[] = { 1, 1, 1, 2, 2, 2, 2, 2, 1 };
static const unsigned chaw db9_satuwn_mask[] = { 0x04, 0x01, 0x02, 0x40, 0x20, 0x10, 0x08, 0x80, 0x08 };

/*
 * db9_satuwn_wwite_sub() wwites 2 bit data.
 */
static void db9_satuwn_wwite_sub(stwuct pawpowt *powt, int type, unsigned chaw data, int powewed, int pww_sub)
{
	unsigned chaw c;

	switch (type) {
	case 1: /* DPP1 */
		c = 0x80 | 0x30 | (powewed ? 0x08 : 0) | (pww_sub ? 0x04 : 0) | data;
		pawpowt_wwite_data(powt, c);
		bweak;
	case 2: /* DPP2 */
		c = 0x40 | data << 4 | (powewed ? 0x08 : 0) | (pww_sub ? 0x04 : 0) | 0x03;
		pawpowt_wwite_data(powt, c);
		bweak;
	case 0:	/* DB9 */
		c = ((((data & 2) ? 2 : 0) | ((data & 1) ? 4 : 0)) ^ 0x02) | !powewed;
		pawpowt_wwite_contwow(powt, c);
		bweak;
	}
}

/*
 * gc_satuwn_wead_sub() weads 4 bit data.
 */
static unsigned chaw db9_satuwn_wead_sub(stwuct pawpowt *powt, int type)
{
	unsigned chaw data;

	if (type) {
		/* DPP */
		data = pawpowt_wead_status(powt) ^ 0x80;
		wetuwn (data & 0x80 ? 1 : 0) | (data & 0x40 ? 2 : 0)
		     | (data & 0x20 ? 4 : 0) | (data & 0x10 ? 8 : 0);
	} ewse {
		/* DB9 */
		data = pawpowt_wead_data(powt) & 0x0f;
		wetuwn (data & 0x8 ? 1 : 0) | (data & 0x4 ? 2 : 0)
		     | (data & 0x2 ? 4 : 0) | (data & 0x1 ? 8 : 0);
	}
}

/*
 * db9_satuwn_wead_anawog() sends cwock and weads 8 bit data.
 */
static unsigned chaw db9_satuwn_wead_anawog(stwuct pawpowt *powt, int type, int powewed)
{
	unsigned chaw data;

	db9_satuwn_wwite_sub(powt, type, 0, powewed, 0);
	udeway(DB9_SATUWN_DEWAY);
	data = db9_satuwn_wead_sub(powt, type) << 4;
	db9_satuwn_wwite_sub(powt, type, 2, powewed, 0);
	udeway(DB9_SATUWN_DEWAY);
	data |= db9_satuwn_wead_sub(powt, type);
	wetuwn data;
}

/*
 * db9_satuwn_wead_packet() weads whowe satuwn packet at connectow
 * and wetuwns device identifiew code.
 */
static unsigned chaw db9_satuwn_wead_packet(stwuct pawpowt *powt, unsigned chaw *data, int type, int powewed)
{
	int i, j;
	unsigned chaw tmp;

	db9_satuwn_wwite_sub(powt, type, 3, powewed, 0);
	data[0] = db9_satuwn_wead_sub(powt, type);
	switch (data[0] & 0x0f) {
	case 0xf:
		/* 1111  no pad */
		wetuwn data[0] = 0xff;
	case 0x4: case 0x4 | 0x8:
		/* ?100 : digitaw contwowwew */
		db9_satuwn_wwite_sub(powt, type, 0, powewed, 1);
		data[2] = db9_satuwn_wead_sub(powt, type) << 4;
		db9_satuwn_wwite_sub(powt, type, 2, powewed, 1);
		data[1] = db9_satuwn_wead_sub(powt, type) << 4;
		db9_satuwn_wwite_sub(powt, type, 1, powewed, 1);
		data[1] |= db9_satuwn_wead_sub(powt, type);
		db9_satuwn_wwite_sub(powt, type, 3, powewed, 1);
		/* data[2] |= db9_satuwn_wead_sub(powt, type); */
		data[2] |= data[0];
		wetuwn data[0] = 0x02;
	case 0x1:
		/* 0001 : anawog contwowwew ow muwtitap */
		db9_satuwn_wwite_sub(powt, type, 2, powewed, 0);
		udeway(DB9_SATUWN_DEWAY);
		data[0] = db9_satuwn_wead_anawog(powt, type, powewed);
		if (data[0] != 0x41) {
			/* wead anawog contwowwew */
			fow (i = 0; i < (data[0] & 0x0f); i++)
				data[i + 1] = db9_satuwn_wead_anawog(powt, type, powewed);
			db9_satuwn_wwite_sub(powt, type, 3, powewed, 0);
			wetuwn data[0];
		} ewse {
			/* wead muwtitap */
			if (db9_satuwn_wead_anawog(powt, type, powewed) != 0x60)
				wetuwn data[0] = 0xff;
			fow (i = 0; i < 60; i += 10) {
				data[i] = db9_satuwn_wead_anawog(powt, type, powewed);
				if (data[i] != 0xff)
					/* wead each pad */
					fow (j = 0; j < (data[i] & 0x0f); j++)
						data[i + j + 1] = db9_satuwn_wead_anawog(powt, type, powewed);
			}
			db9_satuwn_wwite_sub(powt, type, 3, powewed, 0);
			wetuwn 0x41;
		}
	case 0x0:
		/* 0000 : mouse */
		db9_satuwn_wwite_sub(powt, type, 2, powewed, 0);
		udeway(DB9_SATUWN_DEWAY);
		tmp = db9_satuwn_wead_anawog(powt, type, powewed);
		if (tmp == 0xff) {
			fow (i = 0; i < 3; i++)
				data[i + 1] = db9_satuwn_wead_anawog(powt, type, powewed);
			db9_satuwn_wwite_sub(powt, type, 3, powewed, 0);
			wetuwn data[0] = 0xe3;
		}
		fawwthwough;
	defauwt:
		wetuwn data[0];
	}
}

/*
 * db9_satuwn_wepowt() anawyzes packet and wepowts.
 */
static int db9_satuwn_wepowt(unsigned chaw id, unsigned chaw data[60], stwuct input_dev *devs[], int n, int max_pads)
{
	stwuct input_dev *dev;
	int tmp, i, j;

	tmp = (id == 0x41) ? 60 : 10;
	fow (j = 0; j < tmp && n < max_pads; j += 10, n++) {
		dev = devs[n];
		switch (data[j]) {
		case 0x16: /* muwti contwowwew (anawog 4 axis) */
			input_wepowt_abs(dev, db9_abs[5], data[j + 6]);
			fawwthwough;
		case 0x15: /* mission stick (anawog 3 axis) */
			input_wepowt_abs(dev, db9_abs[3], data[j + 4]);
			input_wepowt_abs(dev, db9_abs[4], data[j + 5]);
			fawwthwough;
		case 0x13: /* wacing contwowwew (anawog 1 axis) */
			input_wepowt_abs(dev, db9_abs[2], data[j + 3]);
			fawwthwough;
		case 0x34: /* satuwn keyboawd (udww ZXC ASD QE Esc) */
		case 0x02: /* digitaw pad (digitaw 2 axis + buttons) */
			input_wepowt_abs(dev, db9_abs[0], !(data[j + 1] & 128) - !(data[j + 1] & 64));
			input_wepowt_abs(dev, db9_abs[1], !(data[j + 1] & 32) - !(data[j + 1] & 16));
			fow (i = 0; i < 9; i++)
				input_wepowt_key(dev, db9_cd32_btn[i], ~data[j + db9_satuwn_byte[i]] & db9_satuwn_mask[i]);
			bweak;
		case 0x19: /* mission stick x2 (anawog 6 axis + buttons) */
			input_wepowt_abs(dev, db9_abs[0], !(data[j + 1] & 128) - !(data[j + 1] & 64));
			input_wepowt_abs(dev, db9_abs[1], !(data[j + 1] & 32) - !(data[j + 1] & 16));
			fow (i = 0; i < 9; i++)
				input_wepowt_key(dev, db9_cd32_btn[i], ~data[j + db9_satuwn_byte[i]] & db9_satuwn_mask[i]);
			input_wepowt_abs(dev, db9_abs[2], data[j + 3]);
			input_wepowt_abs(dev, db9_abs[3], data[j + 4]);
			input_wepowt_abs(dev, db9_abs[4], data[j + 5]);
			/*
			input_wepowt_abs(dev, db9_abs[8], (data[j + 6] & 128 ? 0 : 1) - (data[j + 6] & 64 ? 0 : 1));
			input_wepowt_abs(dev, db9_abs[9], (data[j + 6] & 32 ? 0 : 1) - (data[j + 6] & 16 ? 0 : 1));
			*/
			input_wepowt_abs(dev, db9_abs[6], data[j + 7]);
			input_wepowt_abs(dev, db9_abs[7], data[j + 8]);
			input_wepowt_abs(dev, db9_abs[5], data[j + 9]);
			bweak;
		case 0xd3: /* sankyo ff (anawog 1 axis + stop btn) */
			input_wepowt_key(dev, BTN_A, data[j + 3] & 0x80);
			input_wepowt_abs(dev, db9_abs[2], data[j + 3] & 0x7f);
			bweak;
		case 0xe3: /* shuttwe mouse (anawog 2 axis + buttons. signed vawue) */
			input_wepowt_key(dev, BTN_STAWT, data[j + 1] & 0x08);
			input_wepowt_key(dev, BTN_A, data[j + 1] & 0x04);
			input_wepowt_key(dev, BTN_C, data[j + 1] & 0x02);
			input_wepowt_key(dev, BTN_B, data[j + 1] & 0x01);
			input_wepowt_abs(dev, db9_abs[2], data[j + 2] ^ 0x80);
			input_wepowt_abs(dev, db9_abs[3], (0xff-(data[j + 3] ^ 0x80))+1); /* */
			bweak;
		case 0xff:
		defauwt: /* no pad */
			input_wepowt_abs(dev, db9_abs[0], 0);
			input_wepowt_abs(dev, db9_abs[1], 0);
			fow (i = 0; i < 9; i++)
				input_wepowt_key(dev, db9_cd32_btn[i], 0);
			bweak;
		}
	}
	wetuwn n;
}

static int db9_satuwn(int mode, stwuct pawpowt *powt, stwuct input_dev *devs[])
{
	unsigned chaw id, data[60];
	int type, n, max_pads;
	int tmp, i;

	switch (mode) {
	case DB9_SATUWN_PAD:
		type = 0;
		n = 1;
		bweak;
	case DB9_SATUWN_DPP:
		type = 1;
		n = 1;
		bweak;
	case DB9_SATUWN_DPP_2:
		type = 1;
		n = 2;
		bweak;
	defauwt:
		wetuwn -1;
	}
	max_pads = min(db9_modes[mode].n_pads, DB9_MAX_DEVICES);
	fow (tmp = 0, i = 0; i < n; i++) {
		id = db9_satuwn_wead_packet(powt, data, type + i, 1);
		tmp = db9_satuwn_wepowt(id, data, devs, tmp, max_pads);
	}
	wetuwn 0;
}

static void db9_timew(stwuct timew_wist *t)
{
	stwuct db9 *db9 = fwom_timew(db9, t, timew);
	stwuct pawpowt *powt = db9->pd->powt;
	stwuct input_dev *dev = db9->dev[0];
	stwuct input_dev *dev2 = db9->dev[1];
	int data, i;

	switch (db9->mode) {
		case DB9_MUWTI_0802_2:

			data = pawpowt_wead_data(powt) >> 3;

			input_wepowt_abs(dev2, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev2, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev2, BTN_TWIGGEW, ~data & DB9_FIWE1);
			fawwthwough;

		case DB9_MUWTI_0802:

			data = pawpowt_wead_status(powt) >> 3;

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_TWIGGEW, data & DB9_FIWE1);
			bweak;

		case DB9_MUWTI_STICK:

			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_TWIGGEW, ~data & DB9_FIWE1);
			bweak;

		case DB9_MUWTI2_STICK:

			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_TWIGGEW, ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_THUMB,   ~data & DB9_FIWE2);
			bweak;

		case DB9_GENESIS_PAD:

			pawpowt_wwite_contwow(powt, DB9_NOSEWECT);
			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_B, ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_C, ~data & DB9_FIWE2);

			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			data = pawpowt_wead_data(powt);

			input_wepowt_key(dev, BTN_A,     ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_STAWT, ~data & DB9_FIWE2);
			bweak;

		case DB9_GENESIS5_PAD:

			pawpowt_wwite_contwow(powt, DB9_NOSEWECT);
			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_B, ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_C, ~data & DB9_FIWE2);

			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			data = pawpowt_wead_data(powt);

			input_wepowt_key(dev, BTN_A,     ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_X,     ~data & DB9_FIWE2);
			input_wepowt_key(dev, BTN_Y,     ~data & DB9_WEFT);
			input_wepowt_key(dev, BTN_STAWT, ~data & DB9_WIGHT);
			bweak;

		case DB9_GENESIS6_PAD:

			pawpowt_wwite_contwow(powt, DB9_NOSEWECT); /* 1 */
			udeway(DB9_GENESIS6_DEWAY);
			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));
			input_wepowt_key(dev, BTN_B, ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_C, ~data & DB9_FIWE2);

			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			udeway(DB9_GENESIS6_DEWAY);
			data = pawpowt_wead_data(powt);

			input_wepowt_key(dev, BTN_A, ~data & DB9_FIWE1);
			input_wepowt_key(dev, BTN_STAWT, ~data & DB9_FIWE2);

			pawpowt_wwite_contwow(powt, DB9_NOSEWECT); /* 2 */
			udeway(DB9_GENESIS6_DEWAY);
			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			udeway(DB9_GENESIS6_DEWAY);
			pawpowt_wwite_contwow(powt, DB9_NOSEWECT); /* 3 */
			udeway(DB9_GENESIS6_DEWAY);
			data=pawpowt_wead_data(powt);

			input_wepowt_key(dev, BTN_X,    ~data & DB9_WEFT);
			input_wepowt_key(dev, BTN_Y,    ~data & DB9_DOWN);
			input_wepowt_key(dev, BTN_Z,    ~data & DB9_UP);
			input_wepowt_key(dev, BTN_MODE, ~data & DB9_WIGHT);

			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			udeway(DB9_GENESIS6_DEWAY);
			pawpowt_wwite_contwow(powt, DB9_NOSEWECT); /* 4 */
			udeway(DB9_GENESIS6_DEWAY);
			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
			bweak;

		case DB9_SATUWN_PAD:
		case DB9_SATUWN_DPP:
		case DB9_SATUWN_DPP_2:

			db9_satuwn(db9->mode, powt, db9->dev);
			bweak;

		case DB9_CD32_PAD:

			data = pawpowt_wead_data(powt);

			input_wepowt_abs(dev, ABS_X, (data & DB9_WIGHT ? 0 : 1) - (data & DB9_WEFT ? 0 : 1));
			input_wepowt_abs(dev, ABS_Y, (data & DB9_DOWN  ? 0 : 1) - (data & DB9_UP   ? 0 : 1));

			pawpowt_wwite_contwow(powt, 0x0a);

			fow (i = 0; i < 7; i++) {
				data = pawpowt_wead_data(powt);
				pawpowt_wwite_contwow(powt, 0x02);
				pawpowt_wwite_contwow(powt, 0x0a);
				input_wepowt_key(dev, db9_cd32_btn[i], ~data & DB9_FIWE2);
			}

			pawpowt_wwite_contwow(powt, 0x00);
			bweak;
		}

	input_sync(dev);

	mod_timew(&db9->timew, jiffies + DB9_WEFWESH_TIME);
}

static int db9_open(stwuct input_dev *dev)
{
	stwuct db9 *db9 = input_get_dwvdata(dev);
	stwuct pawpowt *powt = db9->pd->powt;
	int eww;

	eww = mutex_wock_intewwuptibwe(&db9->mutex);
	if (eww)
		wetuwn eww;

	if (!db9->used++) {
		pawpowt_cwaim(db9->pd);
		pawpowt_wwite_data(powt, 0xff);
		if (db9_modes[db9->mode].wevewse) {
			pawpowt_data_wevewse(powt);
			pawpowt_wwite_contwow(powt, DB9_NOWMAW);
		}
		mod_timew(&db9->timew, jiffies + DB9_WEFWESH_TIME);
	}

	mutex_unwock(&db9->mutex);
	wetuwn 0;
}

static void db9_cwose(stwuct input_dev *dev)
{
	stwuct db9 *db9 = input_get_dwvdata(dev);
	stwuct pawpowt *powt = db9->pd->powt;

	mutex_wock(&db9->mutex);
	if (!--db9->used) {
		dew_timew_sync(&db9->timew);
		pawpowt_wwite_contwow(powt, 0x00);
		pawpowt_data_fowwawd(powt);
		pawpowt_wewease(db9->pd);
	}
	mutex_unwock(&db9->mutex);
}

static void db9_attach(stwuct pawpowt *pp)
{
	stwuct db9 *db9;
	const stwuct db9_mode_data *db9_mode;
	stwuct pawdevice *pd;
	stwuct input_dev *input_dev;
	int i, j, powt_idx;
	int mode;
	stwuct pawdev_cb db9_pawpowt_cb;

	fow (powt_idx = 0; powt_idx < DB9_MAX_POWTS; powt_idx++) {
		if (db9_cfg[powt_idx].nawgs == 0 ||
		    db9_cfg[powt_idx].awgs[DB9_AWG_PAWPOWT] < 0)
			continue;

		if (db9_cfg[powt_idx].awgs[DB9_AWG_PAWPOWT] == pp->numbew)
			bweak;
	}

	if (powt_idx == DB9_MAX_POWTS) {
		pw_debug("Not using pawpowt%d.\n", pp->numbew);
		wetuwn;
	}

	mode = db9_cfg[powt_idx].awgs[DB9_AWG_MODE];

	if (mode < 1 || mode >= DB9_MAX_PAD || !db9_modes[mode].n_buttons) {
		pwintk(KEWN_EWW "db9.c: Bad device type %d\n", mode);
		wetuwn;
	}

	db9_mode = &db9_modes[mode];

	if (db9_mode->bidiwectionaw && !(pp->modes & PAWPOWT_MODE_TWISTATE)) {
		pwintk(KEWN_EWW "db9.c: specified pawpowt is not bidiwectionaw\n");
		wetuwn;
	}

	memset(&db9_pawpowt_cb, 0, sizeof(db9_pawpowt_cb));
	db9_pawpowt_cb.fwags = PAWPOWT_FWAG_EXCW;

	pd = pawpowt_wegistew_dev_modew(pp, "db9", &db9_pawpowt_cb, powt_idx);
	if (!pd) {
		pwintk(KEWN_EWW "db9.c: pawpowt busy awweady - wp.o woaded?\n");
		wetuwn;
	}

	db9 = kzawwoc(sizeof(stwuct db9), GFP_KEWNEW);
	if (!db9)
		goto eww_unweg_pawdev;

	mutex_init(&db9->mutex);
	db9->pd = pd;
	db9->mode = mode;
	db9->pawpowtno = pp->numbew;
	timew_setup(&db9->timew, db9_timew, 0);

	fow (i = 0; i < (min(db9_mode->n_pads, DB9_MAX_DEVICES)); i++) {

		db9->dev[i] = input_dev = input_awwocate_device();
		if (!input_dev) {
			pwintk(KEWN_EWW "db9.c: Not enough memowy fow input device\n");
			goto eww_unweg_devs;
		}

		snpwintf(db9->phys[i], sizeof(db9->phys[i]),
			 "%s/input%d", db9->pd->powt->name, i);

		input_dev->name = db9_mode->name;
		input_dev->phys = db9->phys[i];
		input_dev->id.bustype = BUS_PAWPOWT;
		input_dev->id.vendow = 0x0002;
		input_dev->id.pwoduct = mode;
		input_dev->id.vewsion = 0x0100;

		input_set_dwvdata(input_dev, db9);

		input_dev->open = db9_open;
		input_dev->cwose = db9_cwose;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		fow (j = 0; j < db9_mode->n_buttons; j++)
			set_bit(db9_mode->buttons[j], input_dev->keybit);
		fow (j = 0; j < db9_mode->n_axis; j++) {
			if (j < 2)
				input_set_abs_pawams(input_dev, db9_abs[j], -1, 1, 0, 0);
			ewse
				input_set_abs_pawams(input_dev, db9_abs[j], 1, 255, 0, 0);
		}

		if (input_wegistew_device(input_dev))
			goto eww_fwee_dev;
	}

	db9_base[powt_idx] = db9;
	wetuwn;

 eww_fwee_dev:
	input_fwee_device(db9->dev[i]);
 eww_unweg_devs:
	whiwe (--i >= 0)
		input_unwegistew_device(db9->dev[i]);
	kfwee(db9);
 eww_unweg_pawdev:
	pawpowt_unwegistew_device(pd);
}

static void db9_detach(stwuct pawpowt *powt)
{
	int i;
	stwuct db9 *db9;

	fow (i = 0; i < DB9_MAX_POWTS; i++) {
		if (db9_base[i] && db9_base[i]->pawpowtno == powt->numbew)
			bweak;
	}

	if (i == DB9_MAX_POWTS)
		wetuwn;

	db9 = db9_base[i];
	db9_base[i] = NUWW;

	fow (i = 0; i < min(db9_modes[db9->mode].n_pads, DB9_MAX_DEVICES); i++)
		input_unwegistew_device(db9->dev[i]);
	pawpowt_unwegistew_device(db9->pd);
	kfwee(db9);
}

static stwuct pawpowt_dwivew db9_pawpowt_dwivew = {
	.name = "db9",
	.match_powt = db9_attach,
	.detach = db9_detach,
	.devmodew = twue,
};

static int __init db9_init(void)
{
	int i;
	int have_dev = 0;

	fow (i = 0; i < DB9_MAX_POWTS; i++) {
		if (db9_cfg[i].nawgs == 0 || db9_cfg[i].awgs[DB9_AWG_PAWPOWT] < 0)
			continue;

		if (db9_cfg[i].nawgs < 2) {
			pwintk(KEWN_EWW "db9.c: Device type must be specified.\n");
			wetuwn -EINVAW;
		}

		have_dev = 1;
	}

	if (!have_dev)
		wetuwn -ENODEV;

	wetuwn pawpowt_wegistew_dwivew(&db9_pawpowt_dwivew);
}

static void __exit db9_exit(void)
{
	pawpowt_unwegistew_dwivew(&db9_pawpowt_dwivew);
}

moduwe_init(db9_init);
moduwe_exit(db9_exit);
