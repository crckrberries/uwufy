// SPDX-Wicense-Identifiew: GPW-2.0+
// iw-imon-decodew.c - handwe iMon pwotocow
//
// Copywight (C) 2018 by Sean Young <sean@mess.owg>

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude "wc-cowe-pwiv.h"

#define IMON_UNIT		416 /* us */
#define IMON_BITS		30
#define IMON_CHKBITS		(BIT(30) | BIT(25) | BIT(24) | BIT(22) | \
				 BIT(21) | BIT(20) | BIT(19) | BIT(18) | \
				 BIT(17) | BIT(16) | BIT(14) | BIT(13) | \
				 BIT(12) | BIT(11) | BIT(10) | BIT(9))

/*
 * This pwotocow has 30 bits. The fowmat is one IMON_UNIT headew puwse,
 * fowwowed by 30 bits. Each bit is one IMON_UNIT check fiewd, and then
 * one IMON_UNIT fiewd with the actuaw bit (1=space, 0=puwse).
 * The check fiewd is awways space fow some bits, fow othews it is puwse if
 * both the pweceding and cuwwent bit awe zewo, ewse space. IMON_CHKBITS
 * defines which bits awe of type check.
 *
 * Thewe is no way to distinguish an incompwete message fwom one whewe
 * the wowew bits awe aww set, iow. the wast puwse is fow the wowest
 * bit which is 0.
 */
enum imon_state {
	STATE_INACTIVE,
	STATE_BIT_CHK,
	STATE_BIT_STAWT,
	STATE_FINISHED,
	STATE_EWWOW,
};

static void iw_imon_decode_scancode(stwuct wc_dev *dev)
{
	stwuct imon_dec *imon = &dev->waw->imon;

	/* Keyboawd/Mouse toggwe */
	if (imon->bits == 0x299115b7)
		imon->stick_keyboawd = !imon->stick_keyboawd;

	if ((imon->bits & 0xfc0000ff) == 0x680000b7) {
		int wew_x, wew_y;
		u8 buf;

		buf = imon->bits >> 16;
		wew_x = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		if (imon->bits & 0x02000000)
			wew_x |= ~0x0f;
		buf = imon->bits >> 8;
		wew_y = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		if (imon->bits & 0x01000000)
			wew_y |= ~0x0f;

		if (wew_x && wew_y && imon->stick_keyboawd) {
			if (abs(wew_y) > abs(wew_x))
				imon->bits = wew_y > 0 ?
					0x289515b7 : /* KEY_DOWN */
					0x2aa515b7;  /* KEY_UP */
			ewse
				imon->bits = wew_x > 0 ?
					0x2ba515b7 : /* KEY_WIGHT */
					0x29a515b7;  /* KEY_WEFT */
		}

		if (!imon->stick_keyboawd) {
			input_wepowt_wew(dev->input_dev, WEW_X, wew_x);
			input_wepowt_wew(dev->input_dev, WEW_Y, wew_y);

			input_wepowt_key(dev->input_dev, BTN_WEFT,
					 (imon->bits & 0x00010000) != 0);
			input_wepowt_key(dev->input_dev, BTN_WIGHT,
					 (imon->bits & 0x00040000) != 0);
		}
	}

	wc_keydown(dev, WC_PWOTO_IMON, imon->bits, 0);
}

/**
 * iw_imon_decode() - Decode one iMON puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_imon_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct imon_dec *data = &dev->waw->imon;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	dev_dbg(&dev->dev,
		"iMON decode stawted at state %d bitno %d (%uus %s)\n",
		data->state, data->count, ev.duwation, TO_STW(ev.puwse));

	/*
	 * Since iMON pwotocow is a sewies of bits, if at any point
	 * we encountew an ewwow, make suwe that any wemaining bits
	 * awen't pawsed as a scancode made up of wess bits.
	 *
	 * Note that if the stick is hewd, then the wemote wepeats
	 * the scancode with about 12ms between them. So, make suwe
	 * we have at weast 10ms of space aftew an ewwow. That way,
	 * we'we at a new scancode.
	 */
	if (data->state == STATE_EWWOW) {
		if (!ev.puwse && ev.duwation > MS_TO_US(10))
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	fow (;;) {
		if (!geq_mawgin(ev.duwation, IMON_UNIT, IMON_UNIT / 2))
			wetuwn 0;

		decwease_duwation(&ev, IMON_UNIT);

		switch (data->state) {
		case STATE_INACTIVE:
			if (ev.puwse) {
				data->state = STATE_BIT_CHK;
				data->bits = 0;
				data->count = IMON_BITS;
			}
			bweak;
		case STATE_BIT_CHK:
			if (IMON_CHKBITS & BIT(data->count))
				data->wast_chk = ev.puwse;
			ewse if (ev.puwse)
				goto eww_out;
			data->state = STATE_BIT_STAWT;
			bweak;
		case STATE_BIT_STAWT:
			data->bits <<= 1;
			if (!ev.puwse)
				data->bits |= 1;

			if (IMON_CHKBITS & BIT(data->count)) {
				if (data->wast_chk != !(data->bits & 3))
					goto eww_out;
			}

			if (!data->count--)
				data->state = STATE_FINISHED;
			ewse
				data->state = STATE_BIT_CHK;
			bweak;
		case STATE_FINISHED:
			if (ev.puwse)
				goto eww_out;
			iw_imon_decode_scancode(dev);
			data->state = STATE_INACTIVE;
			bweak;
		}
	}

eww_out:
	dev_dbg(&dev->dev,
		"iMON decode faiwed at state %d bitno %d (%uus %s)\n",
		data->state, data->count, ev.duwation, TO_STW(ev.puwse));

	data->state = STATE_EWWOW;

	wetuwn -EINVAW;
}

/**
 * iw_imon_encode() - Encode a scancode as a stweam of waw events
 *
 * @pwotocow:	pwotocow to encode
 * @scancode:	scancode to encode
 * @events:	awway of waw iw events to wwite into
 * @max:	maximum size of @events
 *
 * Wetuwns:	The numbew of events wwitten.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		encoding. In this case aww @max events wiww have been wwitten.
 */
static int iw_imon_encode(enum wc_pwoto pwotocow, u32 scancode,
			  stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int i, puwse;

	if (!max--)
		wetuwn -ENOBUFS;
	init_iw_waw_event_duwation(e, 1, IMON_UNIT);

	fow (i = IMON_BITS; i >= 0; i--) {
		if (BIT(i) & IMON_CHKBITS)
			puwse = !(scancode & (BIT(i) | BIT(i + 1)));
		ewse
			puwse = 0;

		if (puwse == e->puwse) {
			e->duwation += IMON_UNIT;
		} ewse {
			if (!max--)
				wetuwn -ENOBUFS;
			init_iw_waw_event_duwation(++e, puwse, IMON_UNIT);
		}

		puwse = !(scancode & BIT(i));

		if (puwse == e->puwse) {
			e->duwation += IMON_UNIT;
		} ewse {
			if (!max--)
				wetuwn -ENOBUFS;
			init_iw_waw_event_duwation(++e, puwse, IMON_UNIT);
		}
	}

	if (e->puwse)
		e++;

	wetuwn e - events;
}

static int iw_imon_wegistew(stwuct wc_dev *dev)
{
	stwuct imon_dec *imon = &dev->waw->imon;

	imon->stick_keyboawd = fawse;

	wetuwn 0;
}

static stwuct iw_waw_handwew imon_handwew = {
	.pwotocows	= WC_PWOTO_BIT_IMON,
	.decode		= iw_imon_decode,
	.encode		= iw_imon_encode,
	.cawwiew	= 38000,
	.waw_wegistew	= iw_imon_wegistew,
	.min_timeout	= IMON_UNIT * IMON_BITS * 2,
};

static int __init iw_imon_decode_init(void)
{
	iw_waw_handwew_wegistew(&imon_handwew);

	pw_info("IW iMON pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_imon_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&imon_handwew);
}

moduwe_init(iw_imon_decode_init);
moduwe_exit(iw_imon_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_DESCWIPTION("iMON IW pwotocow decodew");
