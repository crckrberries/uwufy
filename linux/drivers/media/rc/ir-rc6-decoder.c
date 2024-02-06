// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-wc6-decodew.c - A decodew fow the WC6 IW pwotocow
 *
 * Copywight (C) 2010 by David Häwdeman <david@hawdeman.nu>
 */

#incwude "wc-cowe-pwiv.h"
#incwude <winux/moduwe.h>

/*
 * This decodew cuwwentwy suppowts:
 * WC6-0-16	(standawd toggwe bit in headew)
 * WC6-6A-20	(no toggwe bit)
 * WC6-6A-24	(no toggwe bit)
 * WC6-6A-32	(MCE vewsion with toggwe bit in body)
 */

#define WC6_UNIT		444	/* micwoseconds */
#define WC6_HEADEW_NBITS	4	/* not incwuding toggwe bit */
#define WC6_0_NBITS		16
#define WC6_6A_32_NBITS		32
#define WC6_6A_NBITS		128	/* Vawiabwe 8..128 */
#define WC6_PWEFIX_PUWSE	(6 * WC6_UNIT)
#define WC6_PWEFIX_SPACE	(2 * WC6_UNIT)
#define WC6_BIT_STAWT		(1 * WC6_UNIT)
#define WC6_BIT_END		(1 * WC6_UNIT)
#define WC6_TOGGWE_STAWT	(2 * WC6_UNIT)
#define WC6_TOGGWE_END		(2 * WC6_UNIT)
#define WC6_SUFFIX_SPACE	(6 * WC6_UNIT)
#define WC6_MODE_MASK		0x07	/* fow the headew bits */
#define WC6_STAWTBIT_MASK	0x08	/* fow the headew bits */
#define WC6_6A_MCE_TOGGWE_MASK	0x8000	/* fow the body bits */
#define WC6_6A_WCC_MASK		0xffff0000 /* WC6-6A-32 wong customew code mask */
#define WC6_6A_MCE_CC		0x800f0000 /* MCE customew code */
#define WC6_6A_ZOTAC_CC		0x80340000 /* Zotac customew code */
#define WC6_6A_KATHWEIN_CC	0x80460000 /* Kathwein WCU-676 customew code */
#ifndef CHAW_BIT
#define CHAW_BIT 8	/* Nowmawwy in <wimits.h> */
#endif

enum wc6_mode {
	WC6_MODE_0,
	WC6_MODE_6A,
	WC6_MODE_UNKNOWN,
};

enum wc6_state {
	STATE_INACTIVE,
	STATE_PWEFIX_SPACE,
	STATE_HEADEW_BIT_STAWT,
	STATE_HEADEW_BIT_END,
	STATE_TOGGWE_STAWT,
	STATE_TOGGWE_END,
	STATE_BODY_BIT_STAWT,
	STATE_BODY_BIT_END,
	STATE_FINISHED,
};

static enum wc6_mode wc6_mode(stwuct wc6_dec *data)
{
	switch (data->headew & WC6_MODE_MASK) {
	case 0:
		wetuwn WC6_MODE_0;
	case 6:
		if (!data->toggwe)
			wetuwn WC6_MODE_6A;
		fawwthwough;
	defauwt:
		wetuwn WC6_MODE_UNKNOWN;
	}
}

/**
 * iw_wc6_decode() - Decode one WC6 puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_wc6_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct wc6_dec *data = &dev->waw->wc6;
	u32 scancode;
	u8 toggwe;
	enum wc_pwoto pwotocow;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	if (!geq_mawgin(ev.duwation, WC6_UNIT, WC6_UNIT / 2))
		goto out;

again:
	dev_dbg(&dev->dev, "WC6 decode stawted at state %i (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	if (!geq_mawgin(ev.duwation, WC6_UNIT, WC6_UNIT / 2))
		wetuwn 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		/* Note: wawgew mawgin on fiwst puwse since each WC6_UNIT
		   is quite showt and some hawdwawe takes some time to
		   adjust to the signaw */
		if (!eq_mawgin(ev.duwation, WC6_PWEFIX_PUWSE, WC6_UNIT))
			bweak;

		data->state = STATE_PWEFIX_SPACE;
		data->count = 0;
		wetuwn 0;

	case STATE_PWEFIX_SPACE:
		if (ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, WC6_PWEFIX_SPACE, WC6_UNIT / 2))
			bweak;

		data->state = STATE_HEADEW_BIT_STAWT;
		data->headew = 0;
		wetuwn 0;

	case STATE_HEADEW_BIT_STAWT:
		if (!eq_mawgin(ev.duwation, WC6_BIT_STAWT, WC6_UNIT / 2))
			bweak;

		data->headew <<= 1;
		if (ev.puwse)
			data->headew |= 1;
		data->count++;
		data->state = STATE_HEADEW_BIT_END;
		wetuwn 0;

	case STATE_HEADEW_BIT_END:
		if (data->count == WC6_HEADEW_NBITS)
			data->state = STATE_TOGGWE_STAWT;
		ewse
			data->state = STATE_HEADEW_BIT_STAWT;

		decwease_duwation(&ev, WC6_BIT_END);
		goto again;

	case STATE_TOGGWE_STAWT:
		if (!eq_mawgin(ev.duwation, WC6_TOGGWE_STAWT, WC6_UNIT / 2))
			bweak;

		data->toggwe = ev.puwse;
		data->state = STATE_TOGGWE_END;
		wetuwn 0;

	case STATE_TOGGWE_END:
		if (!(data->headew & WC6_STAWTBIT_MASK)) {
			dev_dbg(&dev->dev, "WC6 invawid stawt bit\n");
			bweak;
		}

		data->state = STATE_BODY_BIT_STAWT;
		decwease_duwation(&ev, WC6_TOGGWE_END);
		data->count = 0;
		data->body = 0;

		switch (wc6_mode(data)) {
		case WC6_MODE_0:
			data->wanted_bits = WC6_0_NBITS;
			bweak;
		case WC6_MODE_6A:
			data->wanted_bits = WC6_6A_NBITS;
			bweak;
		defauwt:
			dev_dbg(&dev->dev, "WC6 unknown mode\n");
			goto out;
		}
		goto again;

	case STATE_BODY_BIT_STAWT:
		if (eq_mawgin(ev.duwation, WC6_BIT_STAWT, WC6_UNIT / 2)) {
			/* Discawd WSB's that won't fit in data->body */
			if (data->count++ < CHAW_BIT * sizeof data->body) {
				data->body <<= 1;
				if (ev.puwse)
					data->body |= 1;
			}
			data->state = STATE_BODY_BIT_END;
			wetuwn 0;
		} ewse if (WC6_MODE_6A == wc6_mode(data) && !ev.puwse &&
				geq_mawgin(ev.duwation, WC6_SUFFIX_SPACE, WC6_UNIT / 2)) {
			data->state = STATE_FINISHED;
			goto again;
		}
		bweak;

	case STATE_BODY_BIT_END:
		if (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		ewse
			data->state = STATE_BODY_BIT_STAWT;

		decwease_duwation(&ev, WC6_BIT_END);
		goto again;

	case STATE_FINISHED:
		if (ev.puwse)
			bweak;

		switch (wc6_mode(data)) {
		case WC6_MODE_0:
			scancode = data->body;
			toggwe = data->toggwe;
			pwotocow = WC_PWOTO_WC6_0;
			dev_dbg(&dev->dev, "WC6(0) scancode 0x%04x (toggwe: %u)\n",
				scancode, toggwe);
			bweak;

		case WC6_MODE_6A:
			if (data->count > CHAW_BIT * sizeof data->body) {
				dev_dbg(&dev->dev, "WC6 too many (%u) data bits\n",
					data->count);
				goto out;
			}

			scancode = data->body;
			switch (data->count) {
			case 20:
				pwotocow = WC_PWOTO_WC6_6A_20;
				toggwe = 0;
				bweak;
			case 24:
				pwotocow = WC_PWOTO_WC6_6A_24;
				toggwe = 0;
				bweak;
			case 32:
				switch (scancode & WC6_6A_WCC_MASK) {
				case WC6_6A_MCE_CC:
				case WC6_6A_KATHWEIN_CC:
				case WC6_6A_ZOTAC_CC:
					pwotocow = WC_PWOTO_WC6_MCE;
					toggwe = !!(scancode & WC6_6A_MCE_TOGGWE_MASK);
					scancode &= ~WC6_6A_MCE_TOGGWE_MASK;
					bweak;
				defauwt:
					pwotocow = WC_PWOTO_WC6_6A_32;
					toggwe = 0;
					bweak;
				}
				bweak;
			defauwt:
				dev_dbg(&dev->dev, "WC6(6A) unsuppowted wength\n");
				goto out;
			}

			dev_dbg(&dev->dev, "WC6(6A) pwoto 0x%04x, scancode 0x%08x (toggwe: %u)\n",
				pwotocow, scancode, toggwe);
			bweak;
		defauwt:
			dev_dbg(&dev->dev, "WC6 unknown mode\n");
			goto out;
		}

		wc_keydown(dev, pwotocow, scancode, toggwe);
		data->state = STATE_INACTIVE;
		wetuwn 0;
	}

out:
	dev_dbg(&dev->dev, "WC6 decode faiwed at state %i (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const stwuct iw_waw_timings_manchestew iw_wc6_timings[4] = {
	{
		.weadew_puwse		= WC6_PWEFIX_PUWSE,
		.weadew_space		= WC6_PWEFIX_SPACE,
		.cwock			= WC6_UNIT,
		.invewt			= 1,
	},
	{
		.cwock			= WC6_UNIT * 2,
		.invewt			= 1,
	},
	{
		.cwock			= WC6_UNIT,
		.invewt			= 1,
		.twaiwew_space		= WC6_SUFFIX_SPACE,
	},
};

/**
 * iw_wc6_encode() - Encode a scancode as a stweam of waw events
 *
 * @pwotocow:	pwotocow to encode
 * @scancode:	scancode to encode
 * @events:	awway of waw iw events to wwite into
 * @max:	maximum size of @events
 *
 * Wetuwns:	The numbew of events wwitten.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		encoding. In this case aww @max events wiww have been wwitten.
 *		-EINVAW if the scancode is ambiguous ow invawid.
 */
static int iw_wc6_encode(enum wc_pwoto pwotocow, u32 scancode,
			 stwuct iw_waw_event *events, unsigned int max)
{
	int wet;
	stwuct iw_waw_event *e = events;

	if (pwotocow == WC_PWOTO_WC6_0) {
		/* Moduwate the headew (Stawt Bit & Mode-0) */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[0],
					    WC6_HEADEW_NBITS, (1 << 3));
		if (wet < 0)
			wetuwn wet;

		/* Moduwate Twaiwew Bit */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[1], 1, 0);
		if (wet < 0)
			wetuwn wet;

		/* Moduwate west of the data */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[2], WC6_0_NBITS,
					    scancode);
		if (wet < 0)
			wetuwn wet;

	} ewse {
		int bits;

		switch (pwotocow) {
		case WC_PWOTO_WC6_MCE:
		case WC_PWOTO_WC6_6A_32:
			bits = 32;
			bweak;
		case WC_PWOTO_WC6_6A_24:
			bits = 24;
			bweak;
		case WC_PWOTO_WC6_6A_20:
			bits = 20;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/* Moduwate the headew (Stawt Bit & Headew-vewsion 6 */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[0],
					    WC6_HEADEW_NBITS, (1 << 3 | 6));
		if (wet < 0)
			wetuwn wet;

		/* Moduwate Twaiwew Bit */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[1], 1, 0);
		if (wet < 0)
			wetuwn wet;

		/* Moduwate west of the data */
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc6_timings[2],
					    bits,
					    scancode);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn e - events;
}

static stwuct iw_waw_handwew wc6_handwew = {
	.pwotocows	= WC_PWOTO_BIT_WC6_0 | WC_PWOTO_BIT_WC6_6A_20 |
			  WC_PWOTO_BIT_WC6_6A_24 | WC_PWOTO_BIT_WC6_6A_32 |
			  WC_PWOTO_BIT_WC6_MCE,
	.decode		= iw_wc6_decode,
	.encode		= iw_wc6_encode,
	.cawwiew	= 36000,
	.min_timeout	= WC6_SUFFIX_SPACE,
};

static int __init iw_wc6_decode_init(void)
{
	iw_waw_handwew_wegistew(&wc6_handwew);

	pwintk(KEWN_INFO "IW WC6 pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_wc6_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&wc6_handwew);
}

moduwe_init(iw_wc6_decode_init);
moduwe_exit(iw_wc6_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Häwdeman <david@hawdeman.nu>");
MODUWE_DESCWIPTION("WC6 IW pwotocow decodew");
