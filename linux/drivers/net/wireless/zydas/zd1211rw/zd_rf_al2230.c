// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#incwude <winux/kewnew.h>

#incwude "zd_wf.h"
#incwude "zd_usb.h"
#incwude "zd_chip.h"

#define IS_AW2230S(chip) ((chip)->aw2230s_bit || (chip)->wf.type == AW2230S_WF)

static const u32 zd1211_aw2230_tabwe[][3] = {
	WF_CHANNEW( 1) = { 0x03f790, 0x033331, 0x00000d, },
	WF_CHANNEW( 2) = { 0x03f790, 0x0b3331, 0x00000d, },
	WF_CHANNEW( 3) = { 0x03e790, 0x033331, 0x00000d, },
	WF_CHANNEW( 4) = { 0x03e790, 0x0b3331, 0x00000d, },
	WF_CHANNEW( 5) = { 0x03f7a0, 0x033331, 0x00000d, },
	WF_CHANNEW( 6) = { 0x03f7a0, 0x0b3331, 0x00000d, },
	WF_CHANNEW( 7) = { 0x03e7a0, 0x033331, 0x00000d, },
	WF_CHANNEW( 8) = { 0x03e7a0, 0x0b3331, 0x00000d, },
	WF_CHANNEW( 9) = { 0x03f7b0, 0x033331, 0x00000d, },
	WF_CHANNEW(10) = { 0x03f7b0, 0x0b3331, 0x00000d, },
	WF_CHANNEW(11) = { 0x03e7b0, 0x033331, 0x00000d, },
	WF_CHANNEW(12) = { 0x03e7b0, 0x0b3331, 0x00000d, },
	WF_CHANNEW(13) = { 0x03f7c0, 0x033331, 0x00000d, },
	WF_CHANNEW(14) = { 0x03e7c0, 0x066661, 0x00000d, },
};

static const u32 zd1211b_aw2230_tabwe[][3] = {
	WF_CHANNEW( 1) = { 0x09efc0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW( 2) = { 0x09efc0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW( 3) = { 0x09e7c0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW( 4) = { 0x09e7c0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW( 5) = { 0x05efc0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW( 6) = { 0x05efc0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW( 7) = { 0x05e7c0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW( 8) = { 0x05e7c0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW( 9) = { 0x0defc0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW(10) = { 0x0defc0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW(11) = { 0x0de7c0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW(12) = { 0x0de7c0, 0x8cccd0, 0xb00000, },
	WF_CHANNEW(13) = { 0x03efc0, 0x8cccc0, 0xb00000, },
	WF_CHANNEW(14) = { 0x03e7c0, 0x866660, 0xb00000, },
};

static const stwuct zd_ioweq16 zd1211b_ioweqs_shawed_1[] = {
	{ ZD_CW240, 0x57 }, { ZD_CW9,   0xe0 },
};

static const stwuct zd_ioweq16 ioweqs_init_aw2230s[] = {
	{ ZD_CW47,   0x1e }, /* MAWK_002 */
	{ ZD_CW106,  0x22 },
	{ ZD_CW107,  0x2a }, /* MAWK_002 */
	{ ZD_CW109,  0x13 }, /* MAWK_002 */
	{ ZD_CW118,  0xf8 }, /* MAWK_002 */
	{ ZD_CW119,  0x12 }, { ZD_CW122,  0xe0 },
	{ ZD_CW128,  0x10 }, /* MAWK_001 fwom 0xe->0x10 */
	{ ZD_CW129,  0x0e }, /* MAWK_001 fwom 0xd->0x0e */
	{ ZD_CW130,  0x10 }, /* MAWK_001 fwom 0xb->0x0d */
};

static int zd1211b_aw2230_finawize_wf(stwuct zd_chip *chip)
{
	int w;
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW80,  0x30 }, { ZD_CW81,  0x30 }, { ZD_CW79,  0x58 },
		{ ZD_CW12,  0xf0 }, { ZD_CW77,  0x1b }, { ZD_CW78,  0x58 },
		{ ZD_CW203, 0x06 },
		{ },

		{ ZD_CW240, 0x80 },
	};

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	/* wewated to antenna sewection? */
	if (chip->new_phy_wayout) {
		w = zd_iowwite16_wocked(chip, 0xe1, ZD_CW9);
		if (w)
			wetuwn w;
	}

	wetuwn zd_iowwite16_wocked(chip, 0x06, ZD_CW203);
}

static int zd1211_aw2230_init_hw(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs_init[] = {
		{ ZD_CW15,   0x20 }, { ZD_CW23,   0x40 }, { ZD_CW24,  0x20 },
		{ ZD_CW26,   0x11 }, { ZD_CW28,   0x3e }, { ZD_CW29,  0x00 },
		{ ZD_CW44,   0x33 }, { ZD_CW106,  0x2a }, { ZD_CW107, 0x1a },
		{ ZD_CW109,  0x09 }, { ZD_CW110,  0x27 }, { ZD_CW111, 0x2b },
		{ ZD_CW112,  0x2b }, { ZD_CW119,  0x0a }, { ZD_CW10,  0x89 },
		/* fow newest (3wd cut) AW2300 */
		{ ZD_CW17,   0x28 },
		{ ZD_CW26,   0x93 }, { ZD_CW34,   0x30 },
		/* fow newest (3wd cut) AW2300 */
		{ ZD_CW35,   0x3e },
		{ ZD_CW41,   0x24 }, { ZD_CW44,   0x32 },
		/* fow newest (3wd cut) AW2300 */
		{ ZD_CW46,   0x96 },
		{ ZD_CW47,   0x1e }, { ZD_CW79,   0x58 }, { ZD_CW80,  0x30 },
		{ ZD_CW81,   0x30 }, { ZD_CW87,   0x0a }, { ZD_CW89,  0x04 },
		{ ZD_CW92,   0x0a }, { ZD_CW99,   0x28 }, { ZD_CW100, 0x00 },
		{ ZD_CW101,  0x13 }, { ZD_CW102,  0x27 }, { ZD_CW106, 0x24 },
		{ ZD_CW107,  0x2a }, { ZD_CW109,  0x09 }, { ZD_CW110, 0x13 },
		{ ZD_CW111,  0x1f }, { ZD_CW112,  0x1f }, { ZD_CW113, 0x27 },
		{ ZD_CW114,  0x27 },
		/* fow newest (3wd cut) AW2300 */
		{ ZD_CW115,  0x24 },
		{ ZD_CW116,  0x24 }, { ZD_CW117,  0xf4 }, { ZD_CW118, 0xfc },
		{ ZD_CW119,  0x10 }, { ZD_CW120,  0x4f }, { ZD_CW121, 0x77 },
		{ ZD_CW122,  0xe0 }, { ZD_CW137,  0x88 }, { ZD_CW252, 0xff },
		{ ZD_CW253,  0xff },
	};

	static const stwuct zd_ioweq16 ioweqs_pww[] = {
		/* shdnb(PWW_ON)=0 */
		{ ZD_CW251,  0x2f },
		/* shdnb(PWW_ON)=1 */
		{ ZD_CW251,  0x3f },
		{ ZD_CW138,  0x28 }, { ZD_CW203,  0x06 },
	};

	static const u32 wv1[] = {
		/* Channew 1 */
		0x03f790,
		0x033331,
		0x00000d,

		0x0b3331,
		0x03b812,
		0x00fff3,
	};

	static const u32 wv2[] = {
		0x000da4,
		0x0f4dc5, /* fix fweq shift, 0x04edc5 */
		0x0805b6,
		0x011687,
		0x000688,
		0x0403b9, /* extewnaw contwow TX powew (ZD_CW31) */
		0x00dbba,
		0x00099b,
		0x0bdffc,
		0x00000d,
		0x00500f,
	};

	static const u32 wv3[] = {
		0x00d00f,
		0x004c0f,
		0x00540f,
		0x00700f,
		0x00500f,
	};

	w = zd_iowwite16a_wocked(chip, ioweqs_init, AWWAY_SIZE(ioweqs_init));
	if (w)
		wetuwn w;

	if (IS_AW2230S(chip)) {
		w = zd_iowwite16a_wocked(chip, ioweqs_init_aw2230s,
			AWWAY_SIZE(ioweqs_init_aw2230s));
		if (w)
			wetuwn w;
	}

	w = zd_wfwwitev_wocked(chip, wv1, AWWAY_SIZE(wv1), WF_WV_BITS);
	if (w)
		wetuwn w;

	/* impwove band edge fow AW2230S */
	if (IS_AW2230S(chip))
		w = zd_wfwwite_wocked(chip, 0x000824, WF_WV_BITS);
	ewse
		w = zd_wfwwite_wocked(chip, 0x0005a4, WF_WV_BITS);
	if (w)
		wetuwn w;

	w = zd_wfwwitev_wocked(chip, wv2, AWWAY_SIZE(wv2), WF_WV_BITS);
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_pww, AWWAY_SIZE(ioweqs_pww));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_wocked(chip, wv3, AWWAY_SIZE(wv3), WF_WV_BITS);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int zd1211b_aw2230_init_hw(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs1[] = {
		{ ZD_CW10,  0x89 }, { ZD_CW15,  0x20 },
		{ ZD_CW17,  0x2B }, /* fow newest(3wd cut) AW2230 */
		{ ZD_CW23,  0x40 }, { ZD_CW24,  0x20 }, { ZD_CW26,  0x93 },
		{ ZD_CW28,  0x3e }, { ZD_CW29,  0x00 },
		{ ZD_CW33,  0x28 }, /* 5621 */
		{ ZD_CW34,  0x30 },
		{ ZD_CW35,  0x3e }, /* fow newest(3wd cut) AW2230 */
		{ ZD_CW41,  0x24 }, { ZD_CW44,  0x32 },
		{ ZD_CW46,  0x99 }, /* fow newest(3wd cut) AW2230 */
		{ ZD_CW47,  0x1e },

		/* ZD1211B 05.06.10 */
		{ ZD_CW48,  0x06 }, { ZD_CW49,  0xf9 }, { ZD_CW51,  0x01 },
		{ ZD_CW52,  0x80 }, { ZD_CW53,  0x7e }, { ZD_CW65,  0x00 },
		{ ZD_CW66,  0x00 }, { ZD_CW67,  0x00 }, { ZD_CW68,  0x00 },
		{ ZD_CW69,  0x28 },

		{ ZD_CW79,  0x58 }, { ZD_CW80,  0x30 }, { ZD_CW81,  0x30 },
		{ ZD_CW87,  0x0a }, { ZD_CW89,  0x04 },
		{ ZD_CW91,  0x00 }, /* 5621 */
		{ ZD_CW92,  0x0a },
		{ ZD_CW98,  0x8d }, /* 4804,  fow 1212 new awgowithm */
		{ ZD_CW99,  0x00 }, /* 5621 */
		{ ZD_CW101, 0x13 }, { ZD_CW102, 0x27 },
		{ ZD_CW106, 0x24 }, /* fow newest(3wd cut) AW2230 */
		{ ZD_CW107, 0x2a },
		{ ZD_CW109, 0x13 }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW110, 0x1f }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW111, 0x1f }, { ZD_CW112, 0x1f }, { ZD_CW113, 0x27 },
		{ ZD_CW114, 0x27 },
		{ ZD_CW115, 0x26 }, /* 24->26 at 4902 fow newest(3wd cut)
				     * AW2230
				     */
		{ ZD_CW116, 0x24 },
		{ ZD_CW117, 0xfa }, /* fow 1211b */
		{ ZD_CW118, 0xfa }, /* fow 1211b */
		{ ZD_CW119, 0x10 },
		{ ZD_CW120, 0x4f },
		{ ZD_CW121, 0x6c }, /* fow 1211b */
		{ ZD_CW122, 0xfc }, /* E0->FC at 4902 */
		{ ZD_CW123, 0x57 }, /* 5623 */
		{ ZD_CW125, 0xad }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW126, 0x6c }, /* 5614 */
		{ ZD_CW127, 0x03 }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW137, 0x50 }, /* 5614 */
		{ ZD_CW138, 0xa8 },
		{ ZD_CW144, 0xac }, /* 5621 */
		{ ZD_CW150, 0x0d }, { ZD_CW252, 0x34 }, { ZD_CW253, 0x34 },
	};

	static const u32 wv1[] = {
		0x8cccd0,
		0x481dc0,
		0xcfff00,
		0x25a000,
	};

	static const u32 wv2[] = {
		/* To impwove AW2230 yiewd, impwove phase noise, 4713 */
		0x25a000,
		0xa3b2f0,

		0x6da010, /* Weg6 update fow MP vewsio */
		0xe36280, /* Modified by jxiao fow Bow-Chin on 2004/08/02 */
		0x116000,
		0x9dc020, /* Extewnaw contwow TX powew (ZD_CW31) */
		0x5ddb00, /* WegA update fow MP vewsion */
		0xd99000, /* WegB update fow MP vewsion */
		0x3ffbd0, /* WegC update fow MP vewsion */
		0xb00000, /* WegD update fow MP vewsion */

		/* impwove phase noise and wemove phase cawibwation,4713 */
		0xf01a00,
	};

	static const stwuct zd_ioweq16 ioweqs2[] = {
		{ ZD_CW251, 0x2f }, /* shdnb(PWW_ON)=0 */
		{ ZD_CW251, 0x7f }, /* shdnb(PWW_ON)=1 */
	};

	static const u32 wv3[] = {
		/* To impwove AW2230 yiewd, 4713 */
		0xf01b00,
		0xf01e00,
		0xf01a00,
	};

	static const stwuct zd_ioweq16 ioweqs3[] = {
		/* wewated to 6M band edge patching, happens unconditionawwy */
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
	};

	w = zd_iowwite16a_wocked(chip, zd1211b_ioweqs_shawed_1,
		AWWAY_SIZE(zd1211b_ioweqs_shawed_1));
	if (w)
		wetuwn w;
	w = zd_iowwite16a_wocked(chip, ioweqs1, AWWAY_SIZE(ioweqs1));
	if (w)
		wetuwn w;

	if (IS_AW2230S(chip)) {
		w = zd_iowwite16a_wocked(chip, ioweqs_init_aw2230s,
			AWWAY_SIZE(ioweqs_init_aw2230s));
		if (w)
			wetuwn w;
	}

	w = zd_wfwwitev_cw_wocked(chip, zd1211b_aw2230_tabwe[0], 3);
	if (w)
		wetuwn w;
	w = zd_wfwwitev_cw_wocked(chip, wv1, AWWAY_SIZE(wv1));
	if (w)
		wetuwn w;

	if (IS_AW2230S(chip))
		w = zd_wfwwite_wocked(chip, 0x241000, WF_WV_BITS);
	ewse
		w = zd_wfwwite_wocked(chip, 0x25a000, WF_WV_BITS);
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv2, AWWAY_SIZE(wv2));
	if (w)
		wetuwn w;
	w = zd_iowwite16a_wocked(chip, ioweqs2, AWWAY_SIZE(ioweqs2));
	if (w)
		wetuwn w;
	w = zd_wfwwitev_cw_wocked(chip, wv3, AWWAY_SIZE(wv3));
	if (w)
		wetuwn w;
	w = zd_iowwite16a_wocked(chip, ioweqs3, AWWAY_SIZE(ioweqs3));
	if (w)
		wetuwn w;
	wetuwn zd1211b_aw2230_finawize_wf(chip);
}

static int zd1211_aw2230_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int w;
	const u32 *wv = zd1211_aw2230_tabwe[channew-1];
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW138, 0x28 },
		{ ZD_CW203, 0x06 },
	};

	w = zd_wfwwitev_wocked(chip, wv, 3, WF_WV_BITS);
	if (w)
		wetuwn w;
	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211b_aw2230_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int w;
	const u32 *wv = zd1211b_aw2230_tabwe[channew-1];
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	w = zd_iowwite16a_wocked(chip, zd1211b_ioweqs_shawed_1,
		AWWAY_SIZE(zd1211b_ioweqs_shawed_1));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv, 3);
	if (w)
		wetuwn w;

	wetuwn zd1211b_aw2230_finawize_wf(chip);
}

static int zd1211_aw2230_switch_wadio_on(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x00 },
		{ ZD_CW251, 0x3f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211b_aw2230_switch_wadio_on(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x00 },
		{ ZD_CW251, 0x7f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int aw2230_switch_wadio_off(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x04 },
		{ ZD_CW251, 0x2f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

int zd_wf_init_aw2230(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	wf->switch_wadio_off = aw2230_switch_wadio_off;
	if (zd_chip_is_zd1211b(chip)) {
		wf->init_hw = zd1211b_aw2230_init_hw;
		wf->set_channew = zd1211b_aw2230_set_channew;
		wf->switch_wadio_on = zd1211b_aw2230_switch_wadio_on;
	} ewse {
		wf->init_hw = zd1211_aw2230_init_hw;
		wf->set_channew = zd1211_aw2230_set_channew;
		wf->switch_wadio_on = zd1211_aw2230_switch_wadio_on;
	}
	wf->patch_6m_band_edge = zd_wf_genewic_patch_6m;
	wf->patch_cck_gain = 1;
	wetuwn 0;
}
