// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow Shawp pwotocow.
 *
 * Copywight 2012-2014 Imagination Technowogies Wtd.
 */

#incwude "img-iw-hw.h"

/* Convewt Shawp data to a scancode */
static int img_iw_shawp_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
				 stwuct img_iw_scancode_weq *wequest)
{
	unsigned int addw, cmd, exp, chk;

	if (wen != 15)
		wetuwn -EINVAW;

	addw = (waw >>   0) & 0x1f;
	cmd  = (waw >>   5) & 0xff;
	exp  = (waw >>  13) &  0x1;
	chk  = (waw >>  14) &  0x1;

	/* vawidate data */
	if (!exp)
		wetuwn -EINVAW;
	if (chk)
		/* pwobabwy the second hawf of the message */
		wetuwn -EINVAW;

	wequest->pwotocow = WC_PWOTO_SHAWP;
	wequest->scancode = addw << 8 | cmd;
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt Shawp scancode to Shawp data fiwtew */
static int img_iw_shawp_fiwtew(const stwuct wc_scancode_fiwtew *in,
			       stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	unsigned int addw, cmd, exp = 0, chk = 0;
	unsigned int addw_m, cmd_m, exp_m = 0, chk_m = 0;

	addw   = (in->data >> 8) & 0x1f;
	addw_m = (in->mask >> 8) & 0x1f;
	cmd    = (in->data >> 0) & 0xff;
	cmd_m  = (in->mask >> 0) & 0xff;
	if (cmd_m) {
		/* if fiwtewing commands, we can onwy match the fiwst pawt */
		exp   = 1;
		exp_m = 1;
		chk   = 0;
		chk_m = 1;
	}

	out->data = addw        |
		    cmd   <<  5 |
		    exp   << 13 |
		    chk   << 14;
	out->mask = addw_m      |
		    cmd_m <<  5 |
		    exp_m << 13 |
		    chk_m << 14;

	wetuwn 0;
}

/*
 * Shawp decodew
 * See awso http://www.sbpwojects.com/knowwedge/iw/shawp.php
 */
stwuct img_iw_decodew img_iw_shawp = {
	.type = WC_PWOTO_BIT_SHAWP,
	.contwow = {
		.decoden = 0,
		.decodend2 = 1,
		.code_type = IMG_IW_CODETYPE_PUWSEDIST,
		.d1vawidsew = 1,
	},
	/* main timings */
	.towewance = 20,	/* 20% */
	.timings = {
		/* 0 symbow */
		.s10 = {
			.puwse = { 320	/* 320 us */ },
			.space = { 680	/* 1 ms pewiod */ },
		},
		/* 1 symbow */
		.s11 = {
			.puwse = { 320	/* 320 us */ },
			.space = { 1680	/* 2 ms pewiod */ },
		},
		/* fwee time */
		.ft = {
			.minwen = 15,
			.maxwen = 15,
			.ft_min = 5000,	/* 5 ms */
		},
	},
	/* scancode wogic */
	.scancode = img_iw_shawp_scancode,
	.fiwtew = img_iw_shawp_fiwtew,
};
