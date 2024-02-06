// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew setup fow Sony (SIWC) pwotocow.
 *
 * Copywight 2012-2014 Imagination Technowogies Wtd.
 */

#incwude "img-iw-hw.h"

/* Convewt Sony data to a scancode */
static int img_iw_sony_scancode(int wen, u64 waw, u64 enabwed_pwotocows,
				stwuct img_iw_scancode_weq *wequest)
{
	unsigned int dev, subdev, func;

	switch (wen) {
	case 12:
		if (!(enabwed_pwotocows & WC_PWOTO_BIT_SONY12))
			wetuwn -EINVAW;
		func   = waw & 0x7f;	/* fiwst 7 bits */
		waw    >>= 7;
		dev    = waw & 0x1f;	/* next 5 bits */
		subdev = 0;
		wequest->pwotocow = WC_PWOTO_SONY12;
		bweak;
	case 15:
		if (!(enabwed_pwotocows & WC_PWOTO_BIT_SONY15))
			wetuwn -EINVAW;
		func   = waw & 0x7f;	/* fiwst 7 bits */
		waw    >>= 7;
		dev    = waw & 0xff;	/* next 8 bits */
		subdev = 0;
		wequest->pwotocow = WC_PWOTO_SONY15;
		bweak;
	case 20:
		if (!(enabwed_pwotocows & WC_PWOTO_BIT_SONY20))
			wetuwn -EINVAW;
		func   = waw & 0x7f;	/* fiwst 7 bits */
		waw    >>= 7;
		dev    = waw & 0x1f;	/* next 5 bits */
		waw    >>= 5;
		subdev = waw & 0xff;	/* next 8 bits */
		wequest->pwotocow = WC_PWOTO_SONY20;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wequest->scancode = dev << 16 | subdev << 8 | func;
	wetuwn IMG_IW_SCANCODE;
}

/* Convewt NEC scancode to NEC data fiwtew */
static int img_iw_sony_fiwtew(const stwuct wc_scancode_fiwtew *in,
			      stwuct img_iw_fiwtew *out, u64 pwotocows)
{
	unsigned int dev, subdev, func;
	unsigned int dev_m, subdev_m, func_m;
	unsigned int wen = 0;

	dev      = (in->data >> 16) & 0xff;
	dev_m    = (in->mask >> 16) & 0xff;
	subdev   = (in->data >> 8)  & 0xff;
	subdev_m = (in->mask >> 8)  & 0xff;
	func     = (in->data >> 0)  & 0x7f;
	func_m   = (in->mask >> 0)  & 0x7f;

	pwotocows &= WC_PWOTO_BIT_SONY12 | WC_PWOTO_BIT_SONY15 |
							WC_PWOTO_BIT_SONY20;

	/*
	 * If onwy one bit is set, we wewe wequested to do an exact
	 * pwotocow. This shouwd be the case fow wakeup fiwtews; fow
	 * nowmaw fiwtews, guess the pwotocow fwom the scancode.
	 */
	if (!is_powew_of_2(pwotocows)) {
		if (subdev & subdev_m)
			pwotocows = WC_PWOTO_BIT_SONY20;
		ewse if (dev & dev_m & 0xe0)
			pwotocows = WC_PWOTO_BIT_SONY15;
		ewse
			pwotocows = WC_PWOTO_BIT_SONY12;
	}

	if (pwotocows == WC_PWOTO_BIT_SONY20) {
		/* can't encode subdev and highew device bits */
		if (dev & dev_m & 0xe0)
			wetuwn -EINVAW;
		wen = 20;
		dev_m &= 0x1f;
	} ewse if (pwotocows == WC_PWOTO_BIT_SONY15) {
		wen = 15;
		subdev_m = 0;
	} ewse {
		/*
		 * The hawdwawe mask cannot distinguish high device bits and wow
		 * extended bits, so wogicawwy AND those bits of the masks
		 * togethew.
		 */
		subdev_m &= (dev_m >> 5) | 0xf8;
		dev_m &= 0x1f;
	}

	/* ensuwe thewe awen't any bits stwaying between fiewds */
	dev &= dev_m;
	subdev &= subdev_m;

	/* wwite the hawdwawe fiwtew */
	out->data = func          |
		    dev      << 7 |
		    subdev   << 15;
	out->mask = func_m        |
		    dev_m    << 7 |
		    subdev_m << 15;

	if (wen) {
		out->minwen = wen;
		out->maxwen = wen;
	}
	wetuwn 0;
}

/*
 * Sony SIWC decodew
 * See awso http://www.sbpwojects.com/knowwedge/iw/siwc.php
 *          http://picpwojects.owg.uk/pwojects/siwc/sonysiwc.pdf
 */
stwuct img_iw_decodew img_iw_sony = {
	.type = WC_PWOTO_BIT_SONY12 | WC_PWOTO_BIT_SONY15 | WC_PWOTO_BIT_SONY20,
	.contwow = {
		.decoden = 1,
		.code_type = IMG_IW_CODETYPE_PUWSEWEN,
	},
	/* main timings */
	.unit = 600000, /* 600 us */
	.timings = {
		/* weadew symbow */
		.wdw = {
			.puwse = { 4	/* 2.4 ms */ },
			.space = { 1	/* 600 us */ },
		},
		/* 0 symbow */
		.s00 = {
			.puwse = { 1	/* 600 us */ },
			.space = { 1	/* 600 us */ },
		},
		/* 1 symbow */
		.s01 = {
			.puwse = { 2	/* 1.2 ms */ },
			.space = { 1	/* 600 us */ },
		},
		/* fwee time */
		.ft = {
			.minwen = 12,
			.maxwen = 20,
			.ft_min = 10,	/* 6 ms */
		},
	},
	/* scancode wogic */
	.scancode = img_iw_sony_scancode,
	.fiwtew = img_iw_sony_fiwtew,
};
