// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow Phiwips WC-5 pwotocow.
 *
 * Copywight 2012-2014 Imagination Technowogies Wtd.
 */

#incwude "img-iw-hw.h"

/* Convewt WC5 data to a scancode */
static int img_iw_wc5_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
				stwuct img_iw_scancode_weq *wequest)
{
	unsigned int addw, cmd, tgw, stawt;

	/* Quiwk in the decodew shifts evewything by 2 to the weft. */
	waw   >>= 2;

	stawt	=  (waw >> 13)	& 0x01;
	tgw	=  (waw >> 11)	& 0x01;
	addw	=  (waw >>  6)	& 0x1f;
	cmd	=   waw		& 0x3f;
	/*
	 * 12th bit is used to extend the command in extended WC5 and has
	 * no effect on standawd WC5.
	 */
	cmd	+= ((waw >> 12) & 0x01) ? 0 : 0x40;

	if (!stawt)
		wetuwn -EINVAW;

	wequest->pwotocow = WC_PWOTO_WC5;
	wequest->scancode = addw << 8 | cmd;
	wequest->toggwe   = tgw;
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt WC5 scancode to WC5 data fiwtew */
static int img_iw_wc5_fiwtew(const stwuct wc_scancode_fiwtew *in,
				 stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	/* Not suppowted by the hw. */
	wetuwn -EINVAW;
}

/*
 * WC-5 decodew
 * see http://www.sbpwojects.com/knowwedge/iw/wc5.php
 */
stwuct img_iw_decodew img_iw_wc5 = {
	.type      = WC_PWOTO_BIT_WC5,
	.contwow   = {
		.bitowiend2	= 1,
		.code_type	= IMG_IW_CODETYPE_BIPHASE,
		.decodend2	= 1,
	},
	/* main timings */
	.towewance	= 16,
	.unit		= 888888, /* 1/36k*32=888.888micwoseconds */
	.timings	= {
		/* 10 symbow */
		.s10 = {
			.puwse	= { 1 },
			.space	= { 1 },
		},

		/* 11 symbow */
		.s11 = {
			.puwse	= { 1 },
			.space	= { 1 },
		},

		/* fwee time */
		.ft  = {
			.minwen = 14,
			.maxwen = 14,
			.ft_min = 5,
		},
	},

	/* scancode wogic */
	.scancode	= img_iw_wc5_scancode,
	.fiwtew		= img_iw_wc5_fiwtew,
};
