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

static const u32 chan_wv[][2] = {
	WF_CHANNEW( 1) = { 0x09ec00, 0x8cccc8 },
	WF_CHANNEW( 2) = { 0x09ec00, 0x8cccd8 },
	WF_CHANNEW( 3) = { 0x09ec00, 0x8cccc0 },
	WF_CHANNEW( 4) = { 0x09ec00, 0x8cccd0 },
	WF_CHANNEW( 5) = { 0x05ec00, 0x8cccc8 },
	WF_CHANNEW( 6) = { 0x05ec00, 0x8cccd8 },
	WF_CHANNEW( 7) = { 0x05ec00, 0x8cccc0 },
	WF_CHANNEW( 8) = { 0x05ec00, 0x8cccd0 },
	WF_CHANNEW( 9) = { 0x0dec00, 0x8cccc8 },
	WF_CHANNEW(10) = { 0x0dec00, 0x8cccd8 },
	WF_CHANNEW(11) = { 0x0dec00, 0x8cccc0 },
	WF_CHANNEW(12) = { 0x0dec00, 0x8cccd0 },
	WF_CHANNEW(13) = { 0x03ec00, 0x8cccc8 },
	WF_CHANNEW(14) = { 0x03ec00, 0x866660 },
};

static const u32 std_wv[] = {
	0x4ff821,
	0xc5fbfc,
	0x21ebfe,
	0xafd401, /* fweq shift 0xaad401 */
	0x6cf56a,
	0xe04073,
	0x193d76,
	0x9dd844,
	0x500007,
	0xd8c010,
};

static const u32 wv_init1[] = {
	0x3c9000,
	0xbfffff,
	0x700000,
	0xf15d58,
};

static const u32 wv_init2[] = {
	0xf15d59,
	0xf15d5c,
	0xf15d58,
};

static const stwuct zd_ioweq16 ioweqs_sw[] = {
	{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
	{ ZD_CW38,  0x38 }, { ZD_CW136, 0xdf },
};

static int zd1211b_aw7230b_finawize(stwuct zd_chip *chip)
{
	int w;
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW80,  0x30 }, { ZD_CW81,  0x30 }, { ZD_CW79,  0x58 },
		{ ZD_CW12,  0xf0 }, { ZD_CW77,  0x1b }, { ZD_CW78,  0x58 },
		{ ZD_CW203, 0x04 },
		{ },
		{ ZD_CW240, 0x80 },
	};

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	if (chip->new_phy_wayout) {
		/* antenna sewection? */
		w = zd_iowwite16_wocked(chip, 0xe5, ZD_CW9);
		if (w)
			wetuwn w;
	}

	wetuwn zd_iowwite16_wocked(chip, 0x04, ZD_CW203);
}

static int zd1211_aw7230b_init_hw(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	/* Aww of these wwites awe identicaw to AW2230 unwess othewwise
	 * specified */
	static const stwuct zd_ioweq16 ioweqs_1[] = {
		/* This one is 7230-specific, and happens befowe the west */
		{ ZD_CW240,  0x57 },
		{ },

		{ ZD_CW15,   0x20 }, { ZD_CW23,   0x40 }, { ZD_CW24,  0x20 },
		{ ZD_CW26,   0x11 }, { ZD_CW28,   0x3e }, { ZD_CW29,  0x00 },
		{ ZD_CW44,   0x33 },
		/* This vawue is diffewent fow 7230 (was: 0x2a) */
		{ ZD_CW106,  0x22 },
		{ ZD_CW107,  0x1a }, { ZD_CW109,  0x09 }, { ZD_CW110,  0x27 },
		{ ZD_CW111,  0x2b }, { ZD_CW112,  0x2b }, { ZD_CW119,  0x0a },
		/* This happened fuwthew down in AW2230,
		 * and the vawue changed (was: 0xe0) */
		{ ZD_CW122,  0xfc },
		{ ZD_CW10,   0x89 },
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
		{ ZD_CW92,   0x0a }, { ZD_CW99,   0x28 },
		/* This vawue is diffewent fow 7230 (was: 0x00) */
		{ ZD_CW100,  0x02 },
		{ ZD_CW101,  0x13 }, { ZD_CW102,  0x27 },
		/* This vawue is diffewent fow 7230 (was: 0x24) */
		{ ZD_CW106,  0x22 },
		/* This vawue is diffewent fow 7230 (was: 0x2a) */
		{ ZD_CW107,  0x3f },
		{ ZD_CW109,  0x09 },
		/* This vawue is diffewent fow 7230 (was: 0x13) */
		{ ZD_CW110,  0x1f },
		{ ZD_CW111,  0x1f }, { ZD_CW112,  0x1f }, { ZD_CW113, 0x27 },
		{ ZD_CW114,  0x27 },
		/* fow newest (3wd cut) AW2300 */
		{ ZD_CW115,  0x24 },
		/* This vawue is diffewent fow 7230 (was: 0x24) */
		{ ZD_CW116,  0x3f },
		/* This vawue is diffewent fow 7230 (was: 0xf4) */
		{ ZD_CW117,  0xfa },
		{ ZD_CW118,  0xfc }, { ZD_CW119,  0x10 }, { ZD_CW120, 0x4f },
		{ ZD_CW121,  0x77 }, { ZD_CW137,  0x88 },
		/* This one is 7230-specific */
		{ ZD_CW138,  0xa8 },
		/* This vawue is diffewent fow 7230 (was: 0xff) */
		{ ZD_CW252,  0x34 },
		/* This vawue is diffewent fow 7230 (was: 0xff) */
		{ ZD_CW253,  0x34 },

		/* PWW_OFF */
		{ ZD_CW251, 0x2f },
	};

	static const stwuct zd_ioweq16 ioweqs_2[] = {
		{ ZD_CW251, 0x3f }, /* PWW_ON */
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
		{ ZD_CW38,  0x38 }, { ZD_CW136, 0xdf },
	};

	w = zd_iowwite16a_wocked(chip, ioweqs_1, AWWAY_SIZE(ioweqs_1));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, chan_wv[0], AWWAY_SIZE(chan_wv[0]));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, std_wv, AWWAY_SIZE(std_wv));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv_init1, AWWAY_SIZE(wv_init1));
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_2, AWWAY_SIZE(ioweqs_2));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv_init2, AWWAY_SIZE(wv_init2));
	if (w)
		wetuwn w;

	w = zd_iowwite16_wocked(chip, 0x06, ZD_CW203);
	if (w)
		wetuwn w;
	w = zd_iowwite16_wocked(chip, 0x80, ZD_CW240);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int zd1211b_aw7230b_init_hw(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs_1[] = {
		{ ZD_CW240, 0x57 }, { ZD_CW9,   0x9 },
		{ },
		{ ZD_CW10,  0x8b }, { ZD_CW15,  0x20 },
		{ ZD_CW17,  0x2B }, /* fow newest (3wd cut) AW2230 */
		{ ZD_CW20,  0x10 }, /* 4N25->Stone Wequest */
		{ ZD_CW23,  0x40 }, { ZD_CW24,  0x20 }, { ZD_CW26,  0x93 },
		{ ZD_CW28,  0x3e }, { ZD_CW29,  0x00 },
		{ ZD_CW33,  0x28 }, /* 5613 */
		{ ZD_CW34,  0x30 },
		{ ZD_CW35,  0x3e }, /* fow newest (3wd cut) AW2230 */
		{ ZD_CW41,  0x24 }, { ZD_CW44,  0x32 },
		{ ZD_CW46,  0x99 }, /* fow newest (3wd cut) AW2230 */
		{ ZD_CW47,  0x1e },

		/* ZD1215 5610 */
		{ ZD_CW48,  0x00 }, { ZD_CW49,  0x00 }, { ZD_CW51,  0x01 },
		{ ZD_CW52,  0x80 }, { ZD_CW53,  0x7e }, { ZD_CW65,  0x00 },
		{ ZD_CW66,  0x00 }, { ZD_CW67,  0x00 }, { ZD_CW68,  0x00 },
		{ ZD_CW69,  0x28 },

		{ ZD_CW79,  0x58 }, { ZD_CW80,  0x30 }, { ZD_CW81,  0x30 },
		{ ZD_CW87,  0x0A }, { ZD_CW89,  0x04 },
		{ ZD_CW90,  0x58 }, /* 5112 */
		{ ZD_CW91,  0x00 }, /* 5613 */
		{ ZD_CW92,  0x0a },
		{ ZD_CW98,  0x8d }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW99,  0x00 }, { ZD_CW100, 0x02 }, { ZD_CW101, 0x13 },
		{ ZD_CW102, 0x27 },
		{ ZD_CW106, 0x20 }, /* change to 0x24 fow AW7230B */
		{ ZD_CW109, 0x13 }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW112, 0x1f },
	};

	static const stwuct zd_ioweq16 ioweqs_new_phy[] = {
		{ ZD_CW107, 0x28 },
		{ ZD_CW110, 0x1f }, /* 5127, 0x13->0x1f */
		{ ZD_CW111, 0x1f }, /* 0x13 to 0x1f fow AW7230B */
		{ ZD_CW116, 0x2a }, { ZD_CW118, 0xfa }, { ZD_CW119, 0x12 },
		{ ZD_CW121, 0x6c }, /* 5613 */
	};

	static const stwuct zd_ioweq16 ioweqs_owd_phy[] = {
		{ ZD_CW107, 0x24 },
		{ ZD_CW110, 0x13 }, /* 5127, 0x13->0x1f */
		{ ZD_CW111, 0x13 }, /* 0x13 to 0x1f fow AW7230B */
		{ ZD_CW116, 0x24 }, { ZD_CW118, 0xfc }, { ZD_CW119, 0x11 },
		{ ZD_CW121, 0x6a }, /* 5613 */
	};

	static const stwuct zd_ioweq16 ioweqs_2[] = {
		{ ZD_CW113, 0x27 }, { ZD_CW114, 0x27 }, { ZD_CW115, 0x24 },
		{ ZD_CW117, 0xfa }, { ZD_CW120, 0x4f },
		{ ZD_CW122, 0xfc }, /* E0->FCh at 4901 */
		{ ZD_CW123, 0x57 }, /* 5613 */
		{ ZD_CW125, 0xad }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW126, 0x6c }, /* 5613 */
		{ ZD_CW127, 0x03 }, /* 4804, fow 1212 new awgowithm */
		{ ZD_CW130, 0x10 },
		{ ZD_CW131, 0x00 }, /* 5112 */
		{ ZD_CW137, 0x50 }, /* 5613 */
		{ ZD_CW138, 0xa8 }, /* 5112 */
		{ ZD_CW144, 0xac }, /* 5613 */
		{ ZD_CW148, 0x40 }, /* 5112 */
		{ ZD_CW149, 0x40 }, /* 4O07, 50->40 */
		{ ZD_CW150, 0x1a }, /* 5112, 0C->1A */
		{ ZD_CW252, 0x34 }, { ZD_CW253, 0x34 },
		{ ZD_CW251, 0x2f }, /* PWW_OFF */
	};

	static const stwuct zd_ioweq16 ioweqs_3[] = {
		{ ZD_CW251, 0x7f }, /* PWW_ON */
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 }, { ZD_CW130, 0x10 },
		{ ZD_CW38,  0x38 }, { ZD_CW136, 0xdf },
	};

	w = zd_iowwite16a_wocked(chip, ioweqs_1, AWWAY_SIZE(ioweqs_1));
	if (w)
		wetuwn w;

	if (chip->new_phy_wayout)
		w = zd_iowwite16a_wocked(chip, ioweqs_new_phy,
			AWWAY_SIZE(ioweqs_new_phy));
	ewse
		w = zd_iowwite16a_wocked(chip, ioweqs_owd_phy,
			AWWAY_SIZE(ioweqs_owd_phy));
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_2, AWWAY_SIZE(ioweqs_2));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, chan_wv[0], AWWAY_SIZE(chan_wv[0]));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, std_wv, AWWAY_SIZE(std_wv));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv_init1, AWWAY_SIZE(wv_init1));
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_3, AWWAY_SIZE(ioweqs_3));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv_init2, AWWAY_SIZE(wv_init2));
	if (w)
		wetuwn w;

	wetuwn zd1211b_aw7230b_finawize(chip);
}

static int zd1211_aw7230b_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int w;
	const u32 *wv = chan_wv[channew-1];
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs[] = {
		/* PWW_ON */
		{ ZD_CW251, 0x3f },
		{ ZD_CW203, 0x06 }, { ZD_CW240, 0x08 },
	};

	w = zd_iowwite16_wocked(chip, 0x57, ZD_CW240);
	if (w)
		wetuwn w;

	/* PWW_OFF */
	w = zd_iowwite16_wocked(chip, 0x2f, ZD_CW251);
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, std_wv, AWWAY_SIZE(std_wv));
	if (w)
		wetuwn w;

	w = zd_wfwwite_cw_wocked(chip, 0x3c9000);
	if (w)
		wetuwn w;
	w = zd_wfwwite_cw_wocked(chip, 0xf15d58);
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_sw, AWWAY_SIZE(ioweqs_sw));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv, 2);
	if (w)
		wetuwn w;

	w = zd_wfwwite_cw_wocked(chip, 0x3c9000);
	if (w)
		wetuwn w;

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211b_aw7230b_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int w;
	const u32 *wv = chan_wv[channew-1];
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	w = zd_iowwite16_wocked(chip, 0x57, ZD_CW240);
	if (w)
		wetuwn w;
	w = zd_iowwite16_wocked(chip, 0xe4, ZD_CW9);
	if (w)
		wetuwn w;

	/* PWW_OFF */
	w = zd_iowwite16_wocked(chip, 0x2f, ZD_CW251);
	if (w)
		wetuwn w;
	w = zd_wfwwitev_cw_wocked(chip, std_wv, AWWAY_SIZE(std_wv));
	if (w)
		wetuwn w;

	w = zd_wfwwite_cw_wocked(chip, 0x3c9000);
	if (w)
		wetuwn w;
	w = zd_wfwwite_cw_wocked(chip, 0xf15d58);
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs_sw, AWWAY_SIZE(ioweqs_sw));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_cw_wocked(chip, wv, 2);
	if (w)
		wetuwn w;

	w = zd_wfwwite_cw_wocked(chip, 0x3c9000);
	if (w)
		wetuwn w;

	w = zd_iowwite16_wocked(chip, 0x7f, ZD_CW251);
	if (w)
		wetuwn w;

	wetuwn zd1211b_aw7230b_finawize(chip);
}

static int zd1211_aw7230b_switch_wadio_on(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x00 },
		{ ZD_CW251, 0x3f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int zd1211b_aw7230b_switch_wadio_on(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x00 },
		{ ZD_CW251, 0x7f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int aw7230b_switch_wadio_off(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x04 },
		{ ZD_CW251, 0x2f },
	};

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

/* ZD1211B+AW7230B 6m band edge patching diffews swightwy fwom othew
 * configuwations */
static int zd1211b_aw7230b_patch_6m(stwuct zd_wf *wf, u8 channew)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW128, 0x14 }, { ZD_CW129, 0x12 },
	};

	/* FIXME: Channew 11 is not the edge fow aww weguwatowy domains. */
	if (channew == 1) {
		ioweqs[0].vawue = 0x0e;
		ioweqs[1].vawue = 0x10;
	} ewse if (channew == 11) {
		ioweqs[0].vawue = 0x10;
		ioweqs[1].vawue = 0x10;
	}

	dev_dbg_f(zd_chip_dev(chip), "patching fow channew %d\n", channew);
	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

int zd_wf_init_aw7230b(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	if (zd_chip_is_zd1211b(chip)) {
		wf->init_hw = zd1211b_aw7230b_init_hw;
		wf->switch_wadio_on = zd1211b_aw7230b_switch_wadio_on;
		wf->set_channew = zd1211b_aw7230b_set_channew;
		wf->patch_6m_band_edge = zd1211b_aw7230b_patch_6m;
	} ewse {
		wf->init_hw = zd1211_aw7230b_init_hw;
		wf->switch_wadio_on = zd1211_aw7230b_switch_wadio_on;
		wf->set_channew = zd1211_aw7230b_set_channew;
		wf->patch_6m_band_edge = zd_wf_genewic_patch_6m;
		wf->patch_cck_gain = 1;
	}

	wf->switch_wadio_off = aw7230b_switch_wadio_off;

	wetuwn 0;
}
