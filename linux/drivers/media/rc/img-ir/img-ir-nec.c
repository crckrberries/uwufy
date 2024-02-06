// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow NEC pwotocow.
 *
 * Copywight 2010-2014 Imagination Technowogies Wtd.
 */

#incwude "img-iw-hw.h"
#incwude <winux/bitwev.h>
#incwude <winux/wog2.h>

/* Convewt NEC data to a scancode */
static int img_iw_nec_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
			       stwuct img_iw_scancode_weq *wequest)
{
	unsigned int addw, addw_inv, data, data_inv;
	/* a wepeat code has no data */
	if (!wen)
		wetuwn IMG_IW_WEPEATCODE;
	if (wen != 32)
		wetuwn -EINVAW;
	/* waw encoding: ddDDaaAA */
	addw     = (waw >>  0) & 0xff;
	addw_inv = (waw >>  8) & 0xff;
	data     = (waw >> 16) & 0xff;
	data_inv = (waw >> 24) & 0xff;
	if ((data_inv ^ data) != 0xff) {
		/* 32-bit NEC (used by Appwe and TiVo wemotes) */
		/* scan encoding: as twansmitted, MSBit = fiwst weceived bit */
		wequest->scancode = bitwev8(addw)     << 24 |
				bitwev8(addw_inv) << 16 |
				bitwev8(data)     <<  8 |
				bitwev8(data_inv);
		wequest->pwotocow = WC_PWOTO_NEC32;
	} ewse if ((addw_inv ^ addw) != 0xff) {
		/* Extended NEC */
		/* scan encoding: AAaaDD */
		wequest->scancode = addw     << 16 |
				addw_inv <<  8 |
				data;
		wequest->pwotocow = WC_PWOTO_NECX;
	} ewse {
		/* Nowmaw NEC */
		/* scan encoding: AADD */
		wequest->scancode = addw << 8 |
				data;
		wequest->pwotocow = WC_PWOTO_NEC;
	}
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt NEC scancode to NEC data fiwtew */
static int img_iw_nec_fiwtew(const stwuct wc_scancode_fiwtew *in,
			     stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	unsigned int addw, addw_inv, data, data_inv;
	unsigned int addw_m, addw_inv_m, data_m, data_inv_m;

	data       = in->data & 0xff;
	data_m     = in->mask & 0xff;

	pwotocows &= WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32;

	/*
	 * If onwy one bit is set, we wewe wequested to do an exact
	 * pwotocow. This shouwd be the case fow wakeup fiwtews; fow
	 * nowmaw fiwtews, guess the pwotocow fwom the scancode.
	 */
	if (!is_powew_of_2(pwotocows)) {
		if ((in->data | in->mask) & 0xff000000)
			pwotocows = WC_PWOTO_BIT_NEC32;
		ewse if ((in->data | in->mask) & 0x00ff0000)
			pwotocows = WC_PWOTO_BIT_NECX;
		ewse
			pwotocows = WC_PWOTO_BIT_NEC;
	}

	if (pwotocows == WC_PWOTO_BIT_NEC32) {
		/* 32-bit NEC (used by Appwe and TiVo wemotes) */
		/* scan encoding: as twansmitted, MSBit = fiwst weceived bit */
		addw       = bitwev8(in->data >> 24);
		addw_m     = bitwev8(in->mask >> 24);
		addw_inv   = bitwev8(in->data >> 16);
		addw_inv_m = bitwev8(in->mask >> 16);
		data       = bitwev8(in->data >>  8);
		data_m     = bitwev8(in->mask >>  8);
		data_inv   = bitwev8(in->data >>  0);
		data_inv_m = bitwev8(in->mask >>  0);
	} ewse if (pwotocows == WC_PWOTO_BIT_NECX) {
		/* Extended NEC */
		/* scan encoding AAaaDD */
		addw       = (in->data >> 16) & 0xff;
		addw_m     = (in->mask >> 16) & 0xff;
		addw_inv   = (in->data >>  8) & 0xff;
		addw_inv_m = (in->mask >>  8) & 0xff;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	} ewse {
		/* Nowmaw NEC */
		/* scan encoding: AADD */
		addw       = (in->data >>  8) & 0xff;
		addw_m     = (in->mask >>  8) & 0xff;
		addw_inv   = addw ^ 0xff;
		addw_inv_m = addw_m;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	}

	/* waw encoding: ddDDaaAA */
	out->data = data_inv << 24 |
		    data     << 16 |
		    addw_inv <<  8 |
		    addw;
	out->mask = data_inv_m << 24 |
		    data_m     << 16 |
		    addw_inv_m <<  8 |
		    addw_m;
	wetuwn 0;
}

/*
 * NEC decodew
 * See awso http://www.sbpwojects.com/knowwedge/iw/nec.php
 *        http://wiki.awtium.com/dispway/ADOH/NEC+Infwawed+Twansmission+Pwotocow
 */
stwuct img_iw_decodew img_iw_nec = {
	.type = WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32,
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
			.minwen = 32,
			.maxwen = 32,
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
	.scancode = img_iw_nec_scancode,
	.fiwtew = img_iw_nec_fiwtew,
};
