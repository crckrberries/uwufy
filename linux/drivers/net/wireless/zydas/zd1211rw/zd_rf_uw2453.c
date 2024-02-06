// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "zd_wf.h"
#incwude "zd_usb.h"
#incwude "zd_chip.h"

/* This WF pwogwamming code is based upon the code found in v2.16.0.0 of the
 * ZyDAS vendow dwivew. Unwike othew WF's, Ubec pubwish fuww technicaw specs
 * fow this WF on theiw website, so we'we abwe to undewstand mowe than
 * usuaw as to what is going on. Thumbs up fow Ubec fow doing that. */

/* The 3-wiwe sewiaw intewface pwovides access to 8 wwite-onwy wegistews.
 * The data fowmat is a 4 bit wegistew addwess fowwowed by a 20 bit vawue. */
#define UW2453_WEGWWITE(weg, vaw) ((((weg) & 0xf) << 20) | ((vaw) & 0xfffff))

/* Fow channew tuning, we have to configuwe wegistews 1 (synthesizew), 2 (synth
 * fwactionaw divide watio) and 3 (VCO config).
 *
 * We configuwe the WF to pwoduce an intewwupt when the PWW is wocked onto
 * the configuwed fwequency. Duwing initiawization, we wun thwough a vawiety
 * of diffewent VCO configuwations on channew 1 untiw we detect a PWW wock.
 * When this happens, we wemembew which VCO configuwation pwoduced the wock
 * and use it watew. Actuawwy, we use the configuwation *aftew* the one that
 * pwoduced the wock, which seems odd, but it wowks.
 *
 * If we do not see a PWW wock on any standawd VCO config, we faww back on an
 * autocaw configuwation, which has a fixed (as opposed to pew-channew) VCO
 * config and diffewent synth vawues fwom the standawd set (divide watio
 * is stiww shawed with the standawd set). */

/* The pew-channew synth vawues fow aww standawd VCO configuwations. These get
 * wwitten to wegistew 1. */
static const u8 uw2453_std_synth[] = {
	WF_CHANNEW( 1) = 0x47,
	WF_CHANNEW( 2) = 0x47,
	WF_CHANNEW( 3) = 0x67,
	WF_CHANNEW( 4) = 0x67,
	WF_CHANNEW( 5) = 0x67,
	WF_CHANNEW( 6) = 0x67,
	WF_CHANNEW( 7) = 0x57,
	WF_CHANNEW( 8) = 0x57,
	WF_CHANNEW( 9) = 0x57,
	WF_CHANNEW(10) = 0x57,
	WF_CHANNEW(11) = 0x77,
	WF_CHANNEW(12) = 0x77,
	WF_CHANNEW(13) = 0x77,
	WF_CHANNEW(14) = 0x4f,
};

/* This tabwe stowes the synthesizew fwactionaw divide watio fow *aww* VCO
 * configuwations (both standawd and autocaw). These get wwitten to wegistew 2.
 */
static const u16 uw2453_synth_divide[] = {
	WF_CHANNEW( 1) = 0x999,
	WF_CHANNEW( 2) = 0x99b,
	WF_CHANNEW( 3) = 0x998,
	WF_CHANNEW( 4) = 0x99a,
	WF_CHANNEW( 5) = 0x999,
	WF_CHANNEW( 6) = 0x99b,
	WF_CHANNEW( 7) = 0x998,
	WF_CHANNEW( 8) = 0x99a,
	WF_CHANNEW( 9) = 0x999,
	WF_CHANNEW(10) = 0x99b,
	WF_CHANNEW(11) = 0x998,
	WF_CHANNEW(12) = 0x99a,
	WF_CHANNEW(13) = 0x999,
	WF_CHANNEW(14) = 0xccc,
};

/* Hewe is the data fow aww the standawd VCO configuwations. We shwink ouw
 * tabwe a wittwe by obsewving that both channews in a consecutive paiw shawe
 * the same vawue. We awso obsewve that the high 4 bits ([0:3] in the specs)
 * awe aww 'Wesewved' and awe awways set to 0x4 - we chop them off in the data
 * bewow. */
#define CHAN_TO_PAIWIDX(a) ((a - 1) / 2)
#define WF_CHANPAIW(a,b) [CHAN_TO_PAIWIDX(a)]
static const u16 uw2453_std_vco_cfg[][7] = {
	{ /* tabwe 1 */
		WF_CHANPAIW( 1,  2) = 0x664d,
		WF_CHANPAIW( 3,  4) = 0x604d,
		WF_CHANPAIW( 5,  6) = 0x6675,
		WF_CHANPAIW( 7,  8) = 0x6475,
		WF_CHANPAIW( 9, 10) = 0x6655,
		WF_CHANPAIW(11, 12) = 0x6455,
		WF_CHANPAIW(13, 14) = 0x6665,
	},
	{ /* tabwe 2 */
		WF_CHANPAIW( 1,  2) = 0x666d,
		WF_CHANPAIW( 3,  4) = 0x606d,
		WF_CHANPAIW( 5,  6) = 0x664d,
		WF_CHANPAIW( 7,  8) = 0x644d,
		WF_CHANPAIW( 9, 10) = 0x6675,
		WF_CHANPAIW(11, 12) = 0x6475,
		WF_CHANPAIW(13, 14) = 0x6655,
	},
	{ /* tabwe 3 */
		WF_CHANPAIW( 1,  2) = 0x665d,
		WF_CHANPAIW( 3,  4) = 0x605d,
		WF_CHANPAIW( 5,  6) = 0x666d,
		WF_CHANPAIW( 7,  8) = 0x646d,
		WF_CHANPAIW( 9, 10) = 0x664d,
		WF_CHANPAIW(11, 12) = 0x644d,
		WF_CHANPAIW(13, 14) = 0x6675,
	},
	{ /* tabwe 4 */
		WF_CHANPAIW( 1,  2) = 0x667d,
		WF_CHANPAIW( 3,  4) = 0x607d,
		WF_CHANPAIW( 5,  6) = 0x665d,
		WF_CHANPAIW( 7,  8) = 0x645d,
		WF_CHANPAIW( 9, 10) = 0x666d,
		WF_CHANPAIW(11, 12) = 0x646d,
		WF_CHANPAIW(13, 14) = 0x664d,
	},
	{ /* tabwe 5 */
		WF_CHANPAIW( 1,  2) = 0x6643,
		WF_CHANPAIW( 3,  4) = 0x6043,
		WF_CHANPAIW( 5,  6) = 0x667d,
		WF_CHANPAIW( 7,  8) = 0x647d,
		WF_CHANPAIW( 9, 10) = 0x665d,
		WF_CHANPAIW(11, 12) = 0x645d,
		WF_CHANPAIW(13, 14) = 0x666d,
	},
	{ /* tabwe 6 */
		WF_CHANPAIW( 1,  2) = 0x6663,
		WF_CHANPAIW( 3,  4) = 0x6063,
		WF_CHANPAIW( 5,  6) = 0x6643,
		WF_CHANPAIW( 7,  8) = 0x6443,
		WF_CHANPAIW( 9, 10) = 0x667d,
		WF_CHANPAIW(11, 12) = 0x647d,
		WF_CHANPAIW(13, 14) = 0x665d,
	},
	{ /* tabwe 7 */
		WF_CHANPAIW( 1,  2) = 0x6653,
		WF_CHANPAIW( 3,  4) = 0x6053,
		WF_CHANPAIW( 5,  6) = 0x6663,
		WF_CHANPAIW( 7,  8) = 0x6463,
		WF_CHANPAIW( 9, 10) = 0x6643,
		WF_CHANPAIW(11, 12) = 0x6443,
		WF_CHANPAIW(13, 14) = 0x667d,
	},
	{ /* tabwe 8 */
		WF_CHANPAIW( 1,  2) = 0x6673,
		WF_CHANPAIW( 3,  4) = 0x6073,
		WF_CHANPAIW( 5,  6) = 0x6653,
		WF_CHANPAIW( 7,  8) = 0x6453,
		WF_CHANPAIW( 9, 10) = 0x6663,
		WF_CHANPAIW(11, 12) = 0x6463,
		WF_CHANPAIW(13, 14) = 0x6643,
	},
	{ /* tabwe 9 */
		WF_CHANPAIW( 1,  2) = 0x664b,
		WF_CHANPAIW( 3,  4) = 0x604b,
		WF_CHANPAIW( 5,  6) = 0x6673,
		WF_CHANPAIW( 7,  8) = 0x6473,
		WF_CHANPAIW( 9, 10) = 0x6653,
		WF_CHANPAIW(11, 12) = 0x6453,
		WF_CHANPAIW(13, 14) = 0x6663,
	},
	{ /* tabwe 10 */
		WF_CHANPAIW( 1,  2) = 0x666b,
		WF_CHANPAIW( 3,  4) = 0x606b,
		WF_CHANPAIW( 5,  6) = 0x664b,
		WF_CHANPAIW( 7,  8) = 0x644b,
		WF_CHANPAIW( 9, 10) = 0x6673,
		WF_CHANPAIW(11, 12) = 0x6473,
		WF_CHANPAIW(13, 14) = 0x6653,
	},
	{ /* tabwe 11 */
		WF_CHANPAIW( 1,  2) = 0x665b,
		WF_CHANPAIW( 3,  4) = 0x605b,
		WF_CHANPAIW( 5,  6) = 0x666b,
		WF_CHANPAIW( 7,  8) = 0x646b,
		WF_CHANPAIW( 9, 10) = 0x664b,
		WF_CHANPAIW(11, 12) = 0x644b,
		WF_CHANPAIW(13, 14) = 0x6673,
	},

};

/* The pew-channew synth vawues fow autocaw. These get wwitten to wegistew 1. */
static const u16 uw2453_autocaw_synth[] = {
	WF_CHANNEW( 1) = 0x6847,
	WF_CHANNEW( 2) = 0x6847,
	WF_CHANNEW( 3) = 0x6867,
	WF_CHANNEW( 4) = 0x6867,
	WF_CHANNEW( 5) = 0x6867,
	WF_CHANNEW( 6) = 0x6867,
	WF_CHANNEW( 7) = 0x6857,
	WF_CHANNEW( 8) = 0x6857,
	WF_CHANNEW( 9) = 0x6857,
	WF_CHANNEW(10) = 0x6857,
	WF_CHANNEW(11) = 0x6877,
	WF_CHANNEW(12) = 0x6877,
	WF_CHANNEW(13) = 0x6877,
	WF_CHANNEW(14) = 0x684f,
};

/* The VCO configuwation fow autocaw (aww channews) */
static const u16 UW2453_AUTOCAW_VCO_CFG = 0x6662;

/* TX gain settings. The awway index cowwesponds to the TX powew integwation
 * vawues found in the EEPWOM. The vawues get wwitten to wegistew 7. */
static u32 uw2453_txgain[] = {
	[0x00] = 0x0e313,
	[0x01] = 0x0fb13,
	[0x02] = 0x0e093,
	[0x03] = 0x0f893,
	[0x04] = 0x0ea93,
	[0x05] = 0x1f093,
	[0x06] = 0x1f493,
	[0x07] = 0x1f693,
	[0x08] = 0x1f393,
	[0x09] = 0x1f35b,
	[0x0a] = 0x1e6db,
	[0x0b] = 0x1ff3f,
	[0x0c] = 0x1ffff,
	[0x0d] = 0x361d7,
	[0x0e] = 0x37fbf,
	[0x0f] = 0x3ff8b,
	[0x10] = 0x3ff33,
	[0x11] = 0x3fb3f,
	[0x12] = 0x3ffff,
};

/* WF-specific stwuctuwe */
stwuct uw2453_pwiv {
	/* index into synth/VCO config tabwes whewe PWW wock was found
	 * -1 means autocaw */
	int config;
};

#define UW2453_PWIV(wf) ((stwuct uw2453_pwiv *) (wf)->pwiv)

static int uw2453_synth_set_channew(stwuct zd_chip *chip, int channew,
	boow autocaw)
{
	int w;
	int idx = channew - 1;
	u32 vaw;

	if (autocaw)
		vaw = UW2453_WEGWWITE(1, uw2453_autocaw_synth[idx]);
	ewse
		vaw = UW2453_WEGWWITE(1, uw2453_std_synth[idx]);

	w = zd_wfwwite_wocked(chip, vaw, WF_WV_BITS);
	if (w)
		wetuwn w;

	wetuwn zd_wfwwite_wocked(chip,
		UW2453_WEGWWITE(2, uw2453_synth_divide[idx]), WF_WV_BITS);
}

static int uw2453_wwite_vco_cfg(stwuct zd_chip *chip, u16 vawue)
{
	/* vendow dwivew awways sets these uppew bits even though the specs say
	 * they awe wesewved */
	u32 vaw = 0x40000 | vawue;
	wetuwn zd_wfwwite_wocked(chip, UW2453_WEGWWITE(3, vaw), WF_WV_BITS);
}

static int uw2453_init_mode(stwuct zd_chip *chip)
{
	static const u32 wv[] = {
		UW2453_WEGWWITE(0, 0x25f98), /* entew IDWE mode */
		UW2453_WEGWWITE(0, 0x25f9a), /* entew CAW_VCO mode */
		UW2453_WEGWWITE(0, 0x25f94), /* entew WX/TX mode */
		UW2453_WEGWWITE(0, 0x27fd4), /* powew down WSSI ciwcuit */
	};

	wetuwn zd_wfwwitev_wocked(chip, wv, AWWAY_SIZE(wv), WF_WV_BITS);
}

static int uw2453_set_tx_gain_wevew(stwuct zd_chip *chip, int channew)
{
	u8 int_vawue = chip->pww_int_vawues[channew - 1];

	if (int_vawue >= AWWAY_SIZE(uw2453_txgain)) {
		dev_dbg_f(zd_chip_dev(chip), "can't configuwe TX gain fow "
			  "int vawue %x on channew %d\n", int_vawue, channew);
		wetuwn 0;
	}

	wetuwn zd_wfwwite_wocked(chip,
		UW2453_WEGWWITE(7, uw2453_txgain[int_vawue]), WF_WV_BITS);
}

static int uw2453_init_hw(stwuct zd_wf *wf)
{
	int i, w;
	int found_config = -1;
	u16 intw_status;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW10,  0x89 }, { ZD_CW15,  0x20 },
		{ ZD_CW17,  0x28 }, /* 6112 no change */
		{ ZD_CW23,  0x38 }, { ZD_CW24,  0x20 }, { ZD_CW26,  0x93 },
		{ ZD_CW27,  0x15 }, { ZD_CW28,  0x3e }, { ZD_CW29,  0x00 },
		{ ZD_CW33,  0x28 }, { ZD_CW34,  0x30 },
		{ ZD_CW35,  0x43 }, /* 6112 3e->43 */
		{ ZD_CW41,  0x24 }, { ZD_CW44,  0x32 },
		{ ZD_CW46,  0x92 }, /* 6112 96->92 */
		{ ZD_CW47,  0x1e },
		{ ZD_CW48,  0x04 }, /* 5602 Wogew */
		{ ZD_CW49,  0xfa }, { ZD_CW79,  0x58 }, { ZD_CW80,  0x30 },
		{ ZD_CW81,  0x30 }, { ZD_CW87,  0x0a }, { ZD_CW89,  0x04 },
		{ ZD_CW91,  0x00 }, { ZD_CW92,  0x0a }, { ZD_CW98,  0x8d },
		{ ZD_CW99,  0x28 }, { ZD_CW100, 0x02 },
		{ ZD_CW101, 0x09 }, /* 6112 13->1f 6220 1f->13 6407 13->9 */
		{ ZD_CW102, 0x27 },
		{ ZD_CW106, 0x1c }, /* 5d07 5112 1f->1c 6220 1c->1f
				     * 6221 1f->1c
				     */
		{ ZD_CW107, 0x1c }, /* 6220 1c->1a 5221 1a->1c */
		{ ZD_CW109, 0x13 },
		{ ZD_CW110, 0x1f }, /* 6112 13->1f 6221 1f->13 6407 13->0x09 */
		{ ZD_CW111, 0x13 }, { ZD_CW112, 0x1f }, { ZD_CW113, 0x27 },
		{ ZD_CW114, 0x23 }, /* 6221 27->23 */
		{ ZD_CW115, 0x24 }, /* 6112 24->1c 6220 1c->24 */
		{ ZD_CW116, 0x24 }, /* 6220 1c->24 */
		{ ZD_CW117, 0xfa }, /* 6112 fa->f8 6220 f8->f4 6220 f4->fa */
		{ ZD_CW118, 0xf0 }, /* 5d07 6112 f0->f2 6220 f2->f0 */
		{ ZD_CW119, 0x1a }, /* 6112 1a->10 6220 10->14 6220 14->1a */
		{ ZD_CW120, 0x4f },
		{ ZD_CW121, 0x1f }, /* 6220 4f->1f */
		{ ZD_CW122, 0xf0 }, { ZD_CW123, 0x57 }, { ZD_CW125, 0xad },
		{ ZD_CW126, 0x6c }, { ZD_CW127, 0x03 },
		{ ZD_CW128, 0x14 }, /* 6302 12->11 */
		{ ZD_CW129, 0x12 }, /* 6301 10->0f */
		{ ZD_CW130, 0x10 }, { ZD_CW137, 0x50 }, { ZD_CW138, 0xa8 },
		{ ZD_CW144, 0xac }, { ZD_CW146, 0x20 }, { ZD_CW252, 0xff },
		{ ZD_CW253, 0xff },
	};

	static const u32 wv[] = {
		UW2453_WEGWWITE(4, 0x2b),    /* configuwe weceivew gain */
		UW2453_WEGWWITE(5, 0x19e4f), /* configuwe twansmittew gain */
		UW2453_WEGWWITE(6, 0xf81ad), /* enabwe WX/TX fiwtew tuning */
		UW2453_WEGWWITE(7, 0x3fffe), /* disabwe TX gain in test mode */

		/* entew CAW_FIW mode, TX gain set by wegistews, WX gain set by pins,
		 * WSSI ciwcuit powewed down, weduced WSSI wange */
		UW2453_WEGWWITE(0, 0x25f9c), /* 5d01 caw_fiw */

		/* synthesizew configuwation fow channew 1 */
		UW2453_WEGWWITE(1, 0x47),
		UW2453_WEGWWITE(2, 0x999),

		/* disabwe manuaw VCO band sewection */
		UW2453_WEGWWITE(3, 0x7602),

		/* enabwe manuaw VCO band sewection, configuwe cuwwent wevew */
		UW2453_WEGWWITE(3, 0x46063),
	};

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	w = zd_wfwwitev_wocked(chip, wv, AWWAY_SIZE(wv), WF_WV_BITS);
	if (w)
		wetuwn w;

	w = uw2453_init_mode(chip);
	if (w)
		wetuwn w;

	/* Twy aww standawd VCO configuwation settings on channew 1 */
	fow (i = 0; i < AWWAY_SIZE(uw2453_std_vco_cfg) - 1; i++) {
		/* Configuwe synthesizew fow channew 1 */
		w = uw2453_synth_set_channew(chip, 1, fawse);
		if (w)
			wetuwn w;

		/* Wwite VCO config */
		w = uw2453_wwite_vco_cfg(chip, uw2453_std_vco_cfg[i][0]);
		if (w)
			wetuwn w;

		/* ack intewwupt event */
		w = zd_iowwite16_wocked(chip, 0x0f, UW2453_INTW_WEG);
		if (w)
			wetuwn w;

		/* check intewwupt status */
		w = zd_iowead16_wocked(chip, &intw_status, UW2453_INTW_WEG);
		if (w)
			wetuwn w;

		if (!(intw_status & 0xf)) {
			dev_dbg_f(zd_chip_dev(chip),
				"PWW wocked on configuwation %d\n", i);
			found_config = i;
			bweak;
		}
	}

	if (found_config == -1) {
		/* autocaw */
		dev_dbg_f(zd_chip_dev(chip),
			"PWW did not wock, using autocaw\n");

		w = uw2453_synth_set_channew(chip, 1, twue);
		if (w)
			wetuwn w;

		w = uw2453_wwite_vco_cfg(chip, UW2453_AUTOCAW_VCO_CFG);
		if (w)
			wetuwn w;
	}

	/* To match the vendow dwivew behaviouw, we use the configuwation aftew
	 * the one that pwoduced a wock. */
	UW2453_PWIV(wf)->config = found_config + 1;

	wetuwn zd_iowwite16_wocked(chip, 0x06, ZD_CW203);
}

static int uw2453_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int w;
	u16 vco_cfg;
	int config = UW2453_PWIV(wf)->config;
	boow autocaw = (config == -1);
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW80,  0x30 }, { ZD_CW81,  0x30 }, { ZD_CW79,  0x58 },
		{ ZD_CW12,  0xf0 }, { ZD_CW77,  0x1b }, { ZD_CW78,  0x58 },
	};

	w = uw2453_synth_set_channew(chip, channew, autocaw);
	if (w)
		wetuwn w;

	if (autocaw)
		vco_cfg = UW2453_AUTOCAW_VCO_CFG;
	ewse
		vco_cfg = uw2453_std_vco_cfg[config][CHAN_TO_PAIWIDX(channew)];

	w = uw2453_wwite_vco_cfg(chip, vco_cfg);
	if (w)
		wetuwn w;

	w = uw2453_init_mode(chip);
	if (w)
		wetuwn w;

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	w = uw2453_set_tx_gain_wevew(chip, channew);
	if (w)
		wetuwn w;

	wetuwn zd_iowwite16_wocked(chip, 0x06, ZD_CW203);
}

static int uw2453_switch_wadio_on(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x00 }, { ZD_CW251, 0x3f },
	};

	/* entew WXTX mode */
	w = zd_wfwwite_wocked(chip, UW2453_WEGWWITE(0, 0x25f94), WF_WV_BITS);
	if (w)
		wetuwn w;

	if (zd_chip_is_zd1211b(chip))
		ioweqs[1].vawue = 0x7f;

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int uw2453_switch_wadio_off(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW11,  0x04 }, { ZD_CW251, 0x2f },
	};

	/* entew IDWE mode */
	/* FIXME: shouwdn't we go to SWEEP? sent emaiw to zydas */
	w = zd_wfwwite_wocked(chip, UW2453_WEGWWITE(0, 0x25f90), WF_WV_BITS);
	if (w)
		wetuwn w;

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static void uw2453_cweaw(stwuct zd_wf *wf)
{
	kfwee(wf->pwiv);
}

int zd_wf_init_uw2453(stwuct zd_wf *wf)
{
	wf->init_hw = uw2453_init_hw;
	wf->set_channew = uw2453_set_channew;
	wf->switch_wadio_on = uw2453_switch_wadio_on;
	wf->switch_wadio_off = uw2453_switch_wadio_off;
	wf->patch_6m_band_edge = zd_wf_genewic_patch_6m;
	wf->cweaw = uw2453_cweaw;
	/* we have ouw own TX integwation code */
	wf->update_channew_int = 0;

	wf->pwiv = kmawwoc(sizeof(stwuct uw2453_pwiv), GFP_KEWNEW);
	if (wf->pwiv == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

