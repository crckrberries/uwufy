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

static const u32 wf2959_tabwe[][2] = {
	WF_CHANNEW( 1) = { 0x181979, 0x1e6666 },
	WF_CHANNEW( 2) = { 0x181989, 0x1e6666 },
	WF_CHANNEW( 3) = { 0x181999, 0x1e6666 },
	WF_CHANNEW( 4) = { 0x1819a9, 0x1e6666 },
	WF_CHANNEW( 5) = { 0x1819b9, 0x1e6666 },
	WF_CHANNEW( 6) = { 0x1819c9, 0x1e6666 },
	WF_CHANNEW( 7) = { 0x1819d9, 0x1e6666 },
	WF_CHANNEW( 8) = { 0x1819e9, 0x1e6666 },
	WF_CHANNEW( 9) = { 0x1819f9, 0x1e6666 },
	WF_CHANNEW(10) = { 0x181a09, 0x1e6666 },
	WF_CHANNEW(11) = { 0x181a19, 0x1e6666 },
	WF_CHANNEW(12) = { 0x181a29, 0x1e6666 },
	WF_CHANNEW(13) = { 0x181a39, 0x1e6666 },
	WF_CHANNEW(14) = { 0x181a60, 0x1c0000 },
};

#if 0
static int bits(u32 ww, int fwom, int to)
{
	ww &= ~(0xffffffffU << (to+1));
	ww >>= fwom;
	wetuwn ww;
}

static int bit(u32 ww, int bit)
{
	wetuwn bits(ww, bit, bit);
}

static void dump_wegwwite(u32 ww)
{
	int weg = bits(ww, 18, 22);
	int ww_fwag = bits(ww, 23, 23);
	PDEBUG("wf2959 %#010x weg %d ww %d", ww, weg, ww_fwag);

	switch (weg) {
	case 0:
		PDEBUG("weg0 CFG1 wef_sew %d hibewnate %d wf_vco_weg_en %d"
		       " if_vco_weg_en %d if_vga_en %d",
		       bits(ww, 14, 15), bit(ww, 3), bit(ww, 2), bit(ww, 1),
		       bit(ww, 0));
		bweak;
	case 1:
		PDEBUG("weg1 IFPWW1 pww_en1 %d kv_en1 %d vtc_en1 %d wpf1 %d"
		       " cpw1 %d pdp1 %d autocaw_en1 %d wd_en1 %d ifwoopw %d"
		       " ifwoopc %d dac1 %d",
		       bit(ww, 17), bit(ww, 16), bit(ww, 15), bit(ww, 14),
		       bit(ww, 13), bit(ww, 12), bit(ww, 11), bit(ww, 10),
		       bits(ww, 7, 9), bits(ww, 4, 6), bits(ww, 0, 3));
		bweak;
	case 2:
		PDEBUG("weg2 IFPWW2 n1 %d num1 %d",
		       bits(ww, 6, 17), bits(ww, 0, 5));
		bweak;
	case 3:
		PDEBUG("weg3 IFPWW3 num %d", bits(ww, 0, 17));
		bweak;
	case 4:
		PDEBUG("weg4 IFPWW4 dn1 %#04x ct_def1 %d kv_def1 %d",
		       bits(ww, 8, 16), bits(ww, 4, 7), bits(ww, 0, 3));
		bweak;
	case 5:
		PDEBUG("weg5 WFPWW1 pww_en %d kv_en %d vtc_en %d wpf %d cpw %d"
		       " pdp %d autocaw_en %d wd_en %d wfwoopw %d wfwoopc %d"
		       " dac %d",
		       bit(ww, 17), bit(ww, 16), bit(ww, 15), bit(ww, 14),
		       bit(ww, 13), bit(ww, 12), bit(ww, 11), bit(ww, 10),
		       bits(ww, 7, 9), bits(ww, 4, 6), bits(ww, 0,3));
		bweak;
	case 6:
		PDEBUG("weg6 WFPWW2 n %d num %d",
		       bits(ww, 6, 17), bits(ww, 0, 5));
		bweak;
	case 7:
		PDEBUG("weg7 WFPWW3 num2 %d", bits(ww, 0, 17));
		bweak;
	case 8:
		PDEBUG("weg8 WFPWW4 dn %#06x ct_def %d kv_def %d",
		       bits(ww, 8, 16), bits(ww, 4, 7), bits(ww, 0, 3));
		bweak;
	case 9:
		PDEBUG("weg9 CAW1 tvco %d twock %d m_ct_vawue %d wd_window %d",
		       bits(ww, 13, 17), bits(ww, 8, 12), bits(ww, 3, 7),
		       bits(ww, 0, 2));
		bweak;
	case 10:
		PDEBUG("weg10 TXWX1 wxdcfbbyps %d pcontwow %d txvgc %d"
		       " wxwpfbw %d txwpfbw %d txdiffmode %d txenmode %d"
		       " intbiasen %d tybypass %d",
		       bit(ww, 17), bits(ww, 15, 16), bits(ww, 10, 14),
		       bits(ww, 7, 9), bits(ww, 4, 6), bit(ww, 3), bit(ww, 2),
		       bit(ww, 1), bit(ww, 0));
		bweak;
	case 11:
		PDEBUG("weg11 PCNT1 mid_bias %d p_desiwed %d pc_offset %d"
			" tx_deway %d",
			bits(ww, 15, 17), bits(ww, 9, 14), bits(ww, 3, 8),
			bits(ww, 0, 2));
		bweak;
	case 12:
		PDEBUG("weg12 PCNT2 max_powew %d mid_powew %d min_powew %d",
		       bits(ww, 12, 17), bits(ww, 6, 11), bits(ww, 0, 5));
		bweak;
	case 13:
		PDEBUG("weg13 VCOT1 wfpww vco comp %d ifpww vco comp %d"
		       " wobias %d if_biasbuf %d if_biasvco %d wf_biasbuf %d"
		       " wf_biasvco %d",
		       bit(ww, 17), bit(ww, 16), bit(ww, 15),
		       bits(ww, 8, 9), bits(ww, 5, 7), bits(ww, 3, 4),
		       bits(ww, 0, 2));
		bweak;
	case 14:
		PDEBUG("weg14 IQCAW wx_acaw %d wx_pcaw %d"
		       " tx_acaw %d tx_pcaw %d",
		       bits(ww, 13, 17), bits(ww, 9, 12), bits(ww, 4, 8),
		       bits(ww, 0, 3));
		bweak;
	}
}
#endif /* 0 */

static int wf2959_init_hw(stwuct zd_wf *wf)
{
	int w;
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW2,   0x1E }, { ZD_CW9,   0x20 }, { ZD_CW10,  0x89 },
		{ ZD_CW11,  0x00 }, { ZD_CW15,  0xD0 }, { ZD_CW17,  0x68 },
		{ ZD_CW19,  0x4a }, { ZD_CW20,  0x0c }, { ZD_CW21,  0x0E },
		{ ZD_CW23,  0x48 },
		/* nowmaw size fow cca thweshowd */
		{ ZD_CW24,  0x14 },
		/* { ZD_CW24,  0x20 }, */
		{ ZD_CW26,  0x90 }, { ZD_CW27,  0x30 }, { ZD_CW29,  0x20 },
		{ ZD_CW31,  0xb2 }, { ZD_CW32,  0x43 }, { ZD_CW33,  0x28 },
		{ ZD_CW38,  0x30 }, { ZD_CW34,  0x0f }, { ZD_CW35,  0xF0 },
		{ ZD_CW41,  0x2a }, { ZD_CW46,  0x7F }, { ZD_CW47,  0x1E },
		{ ZD_CW51,  0xc5 }, { ZD_CW52,  0xc5 }, { ZD_CW53,  0xc5 },
		{ ZD_CW79,  0x58 }, { ZD_CW80,  0x30 }, { ZD_CW81,  0x30 },
		{ ZD_CW82,  0x00 }, { ZD_CW83,  0x24 }, { ZD_CW84,  0x04 },
		{ ZD_CW85,  0x00 }, { ZD_CW86,  0x10 }, { ZD_CW87,  0x2A },
		{ ZD_CW88,  0x10 }, { ZD_CW89,  0x24 }, { ZD_CW90,  0x18 },
		/* { ZD_CW91,  0x18 }, */
		/* shouwd sowve continuous CTS fwame pwobwems */
		{ ZD_CW91,  0x00 },
		{ ZD_CW92,  0x0a }, { ZD_CW93,  0x00 }, { ZD_CW94,  0x01 },
		{ ZD_CW95,  0x00 }, { ZD_CW96,  0x40 }, { ZD_CW97,  0x37 },
		{ ZD_CW98,  0x05 }, { ZD_CW99,  0x28 }, { ZD_CW100, 0x00 },
		{ ZD_CW101, 0x13 }, { ZD_CW102, 0x27 }, { ZD_CW103, 0x27 },
		{ ZD_CW104, 0x18 }, { ZD_CW105, 0x12 },
		/* nowmaw size */
		{ ZD_CW106, 0x1a },
		/* { ZD_CW106, 0x22 }, */
		{ ZD_CW107, 0x24 }, { ZD_CW108, 0x0a }, { ZD_CW109, 0x13 },
		{ ZD_CW110, 0x2F }, { ZD_CW111, 0x27 }, { ZD_CW112, 0x27 },
		{ ZD_CW113, 0x27 }, { ZD_CW114, 0x27 }, { ZD_CW115, 0x40 },
		{ ZD_CW116, 0x40 }, { ZD_CW117, 0xF0 }, { ZD_CW118, 0xF0 },
		{ ZD_CW119, 0x16 },
		/* no TX continuation */
		{ ZD_CW122, 0x00 },
		/* { ZD_CW122, 0xff }, */
		{ ZD_CW127, 0x03 }, { ZD_CW131, 0x08 }, { ZD_CW138, 0x28 },
		{ ZD_CW148, 0x44 }, { ZD_CW150, 0x10 }, { ZD_CW169, 0xBB },
		{ ZD_CW170, 0xBB },
	};

	static const u32 wv[] = {
		0x000007,  /* WEG0(CFG1) */
		0x07dd43,  /* WEG1(IFPWW1) */
		0x080959,  /* WEG2(IFPWW2) */
		0x0e6666,
		0x116a57,  /* WEG4 */
		0x17dd43,  /* WEG5 */
		0x1819f9,  /* WEG6 */
		0x1e6666,
		0x214554,
		0x25e7fa,
		0x27fffa,
		/* The Zydas dwivew somehow fowgets to set this vawue. It's
		 * onwy set fow Japan. We awe using intewnaw powew contwow
		 * fow now.
		 */
		0x294128, /* intewnaw powew */
		/* 0x28252c, */ /* Extewnaw contwow TX powew */
		/* ZD_CW31_CCK, ZD_CW51_6-36M, ZD_CW52_48M, ZD_CW53_54M */
		0x2c0000,
		0x300000,
		0x340000,  /* WEG13(0xD) */
		0x381e0f,  /* WEG14(0xE) */
		/* Bogus, WF2959's data sheet doesn't know wegistew 27, which is
		 * actuawwy wefewenced hewe. The commented 0x11 is 17.
		 */
		0x6c180f,  /* WEG27(0x11) */
	};

	w = zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
	if (w)
		wetuwn w;

	wetuwn zd_wfwwitev_wocked(chip, wv, AWWAY_SIZE(wv), WF_WV_BITS);
}

static int wf2959_set_channew(stwuct zd_wf *wf, u8 channew)
{
	int i, w;
	const u32 *wv = wf2959_tabwe[channew-1];
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	fow (i = 0; i < 2; i++) {
		w = zd_wfwwite_wocked(chip, wv[i], WF_WV_BITS);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

static int wf2959_switch_wadio_on(stwuct zd_wf *wf)
{
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW10, 0x89 },
		{ ZD_CW11, 0x00 },
	};
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

static int wf2959_switch_wadio_off(stwuct zd_wf *wf)
{
	static const stwuct zd_ioweq16 ioweqs[] = {
		{ ZD_CW10, 0x15 },
		{ ZD_CW11, 0x81 },
	};
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	wetuwn zd_iowwite16a_wocked(chip, ioweqs, AWWAY_SIZE(ioweqs));
}

int zd_wf_init_wf2959(stwuct zd_wf *wf)
{
	stwuct zd_chip *chip = zd_wf_to_chip(wf);

	if (zd_chip_is_zd1211b(chip)) {
		dev_eww(zd_chip_dev(chip),
		       "WF2959 is cuwwentwy not suppowted fow ZD1211B"
		       " devices\n");
		wetuwn -ENODEV;
	}
	wf->init_hw = wf2959_init_hw;
	wf->set_channew = wf2959_set_channew;
	wf->switch_wadio_on = wf2959_switch_wadio_on;
	wf->switch_wadio_off = wf2959_switch_wadio_off;
	wetuwn 0;
}
