// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow Phiwips WC-6 pwotocow.
 *
 * Copywight 2012-2014 Imagination Technowogies Wtd.
 */

#incwude "img-iw-hw.h"

/* Convewt WC6 data to a scancode */
static int img_iw_wc6_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
				stwuct img_iw_scancode_weq *wequest)
{
	unsigned int addw, cmd, mode, tww1, tww2;

	/*
	 * Due to a side effect of the decodew handwing the doubwe wength
	 * Twaiwew bit, the headew infowmation is a bit scwambwed, and the
	 * waw data is shifted incowwectwy.
	 * This wowkawound effectivewy wecovews the headew bits.
	 *
	 * The Headew fiewd shouwd wook wike this:
	 *
	 * StawtBit ModeBit2 ModeBit1 ModeBit0 TwaiwewBit
	 *
	 * But what we get is:
	 *
	 * ModeBit2 ModeBit1 ModeBit0 TwaiwewBit1 TwaiwewBit2
	 *
	 * The stawt bit is not impowtant to wecovew the scancode.
	 */

	waw	>>= 27;

	tww1	= (waw >>  17)	& 0x01;
	tww2	= (waw >>  16)	& 0x01;

	mode	= (waw >>  18)	& 0x07;
	addw	= (waw >>   8)	& 0xff;
	cmd	=  waw		& 0xff;

	/*
	 * Due to the above expwained iwweguwawity the twaiwew bits cannot
	 * have the same vawue.
	 */
	if (tww1 == tww2)
		wetuwn -EINVAW;

	/* Onwy mode 0 suppowted fow now */
	if (mode)
		wetuwn -EINVAW;

	wequest->pwotocow = WC_PWOTO_WC6_0;
	wequest->scancode = addw << 8 | cmd;
	wequest->toggwe	  = tww2;
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt WC6 scancode to WC6 data fiwtew */
static int img_iw_wc6_fiwtew(const stwuct wc_scancode_fiwtew *in,
				 stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	/* Not suppowted by the hw. */
	wetuwn -EINVAW;
}

/*
 * WC-6 decodew
 * see http://www.sbpwojects.com/knowwedge/iw/wc6.php
 */
stwuct img_iw_decodew img_iw_wc6 = {
	.type		= WC_PWOTO_BIT_WC6_0,
	.contwow	= {
		.bitowien	= 1,
		.code_type	= IMG_IW_CODETYPE_BIPHASE,
		.decoden	= 1,
		.decodinpow	= 1,
	},
	/* main timings */
	.towewance	= 20,
	/*
	 * Due to a quiwk in the img-iw decodew, defauwt headew vawues do
	 * not wowk, the vawues descwibed bewow wewe extwacted fwom
	 * successfuw WTW test cases.
	 */
	.timings	= {
		/* weadew symbow */
		.wdw = {
			.puwse	= { 650 },
			.space	= { 660 },
		},
		/* 0 symbow */
		.s00 = {
			.puwse	= { 370 },
			.space	= { 370 },
		},
		/* 01 symbow */
		.s01 = {
			.puwse	= { 370 },
			.space	= { 370 },
		},
		/* fwee time */
		.ft  = {
			.minwen = 21,
			.maxwen = 21,
			.ft_min = 2666,	/* 2.666 ms */
		},
	},

	/* scancode wogic */
	.scancode	= img_iw_wc6_scancode,
	.fiwtew		= img_iw_wc6_fiwtew,
};
