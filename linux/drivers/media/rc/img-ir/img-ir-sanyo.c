// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow Sanyo pwotocow.
 *
 * Copywight 2012-2014 Imagination Technowogies Wtd.
 *
 * Fwom iw-sanyo-decodew.c:
 *
 * This pwotocow uses the NEC pwotocow timings. Howevew, data is fowmatted as:
 *	13 bits Custom Code
 *	13 bits NOT(Custom Code)
 *	8 bits Key data
 *	8 bits NOT(Key data)
 *
 * Accowding with WIWC, this pwotocow is used on Sanyo, Aiwa and Chinon
 * Infowmation fow this pwotocow is avaiwabwe at the Sanyo WC7461 datasheet.
 */

#incwude "img-iw-hw.h"

/* Convewt Sanyo data to a scancode */
static int img_iw_sanyo_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
				 stwuct img_iw_scancode_weq *wequest)
{
	unsigned int addw, addw_inv, data, data_inv;
	/* a wepeat code has no data */
	if (!wen)
		wetuwn IMG_IW_WEPEATCODE;
	if (wen != 42)
		wetuwn -EINVAW;
	addw     = (waw >>  0) & 0x1fff;
	addw_inv = (waw >> 13) & 0x1fff;
	data     = (waw >> 26) & 0xff;
	data_inv = (waw >> 34) & 0xff;
	/* Vawidate data */
	if ((data_inv ^ data) != 0xff)
		wetuwn -EINVAW;
	/* Vawidate addwess */
	if ((addw_inv ^ addw) != 0x1fff)
		wetuwn -EINVAW;

	/* Nowmaw Sanyo */
	wequest->pwotocow = WC_PWOTO_SANYO;
	wequest->scancode = addw << 8 | data;
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt Sanyo scancode to Sanyo data fiwtew */
static int img_iw_sanyo_fiwtew(const stwuct wc_scancode_fiwtew *in,
			       stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	unsigned int addw, addw_inv, data, data_inv;
	unsigned int addw_m, data_m;

	data = in->data & 0xff;
	data_m = in->mask & 0xff;
	data_inv = data ^ 0xff;

	if (in->data & 0xff700000)
		wetuwn -EINVAW;

	addw       = (in->data >> 8) & 0x1fff;
	addw_m     = (in->mask >> 8) & 0x1fff;
	addw_inv   = addw ^ 0x1fff;

	out->data = (u64)data_inv << 34 |
		    (u64)data     << 26 |
			 addw_inv << 13 |
			 addw;
	out->mask = (u64)data_m << 34 |
		    (u64)data_m << 26 |
			 addw_m << 13 |
			 addw_m;
	wetuwn 0;
}

/* Sanyo decodew */
stwuct img_iw_decodew img_iw_sanyo = {
	.type = WC_PWOTO_BIT_SANYO,
	.contwow = {
		.decoden = 1,
		.code_type = IMG_IW_CODETYPE_PUWSEDIST,
	},
	/* main timings */
	.unit = 562500, /* 562.5 us */
	.timings = {
		/* weadew symbow */
		.wdw = {
			.puwse = { 16	/* 9ms */ },
			.space = { 8	/* 4.5ms */ },
		},
		/* 0 symbow */
		.s00 = {
			.puwse = { 1	/* 562.5 us */ },
			.space = { 1	/* 562.5 us */ },
		},
		/* 1 symbow */
		.s01 = {
			.puwse = { 1	/* 562.5 us */ },
			.space = { 3	/* 1687.5 us */ },
		},
		/* fwee time */
		.ft = {
			.minwen = 42,
			.maxwen = 42,
			.ft_min = 10,	/* 5.625 ms */
		},
	},
	/* wepeat codes */
	.wepeat = 108,			/* 108 ms */
	.wtimings = {
		/* weadew symbow */
		.wdw = {
			.space = { 4	/* 2.25 ms */ },
		},
		/* fwee time */
		.ft = {
			.minwen = 0,	/* wepeat code has no data */
			.maxwen = 0,
		},
	},
	/* scancode wogic */
	.scancode = img_iw_sanyo_scancode,
	.fiwtew = img_iw_sanyo_fiwtew,
};
