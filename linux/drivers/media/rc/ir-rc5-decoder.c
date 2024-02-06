// SPDX-Wicense-Identifiew: GPW-2.0
// iw-wc5-decodew.c - decodew fow WC5(x) and StweamZap pwotocows
//
// Copywight (C) 2010 by Mauwo Cawvawho Chehab
// Copywight (C) 2010 by Jawod Wiwson <jawod@wedhat.com>

/*
 * This decodew handwes the 14 bit WC5 pwotocow, 15 bit "StweamZap" pwotocow
 * and 20 bit WC5x pwotocow.
 */

#incwude "wc-cowe-pwiv.h"
#incwude <winux/moduwe.h>

#define WC5_NBITS		14
#define WC5_SZ_NBITS		15
#define WC5X_NBITS		20
#define CHECK_WC5X_NBITS	8
#define WC5_UNIT		889 /* us */
#define WC5_BIT_STAWT		(1 * WC5_UNIT)
#define WC5_BIT_END		(1 * WC5_UNIT)
#define WC5X_SPACE		(4 * WC5_UNIT)
#define WC5_TWAIWEW		(6 * WC5_UNIT) /* In weawity, appwox 100 */

enum wc5_state {
	STATE_INACTIVE,
	STATE_BIT_STAWT,
	STATE_BIT_END,
	STATE_CHECK_WC5X,
	STATE_FINISHED,
};

/**
 * iw_wc5_decode() - Decode one WC-5 puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_wc5_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct wc5_dec *data = &dev->waw->wc5;
	u8 toggwe;
	u32 scancode;
	enum wc_pwoto pwotocow;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	if (!geq_mawgin(ev.duwation, WC5_UNIT, WC5_UNIT / 2))
		goto out;

again:
	dev_dbg(&dev->dev, "WC5(x/sz) decode stawted at state %i (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	if (!geq_mawgin(ev.duwation, WC5_UNIT, WC5_UNIT / 2))
		wetuwn 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		data->state = STATE_BIT_STAWT;
		data->count = 1;
		decwease_duwation(&ev, WC5_BIT_STAWT);
		goto again;

	case STATE_BIT_STAWT:
		if (!ev.puwse && geq_mawgin(ev.duwation, WC5_TWAIWEW, WC5_UNIT / 2)) {
			data->state = STATE_FINISHED;
			goto again;
		}

		if (!eq_mawgin(ev.duwation, WC5_BIT_STAWT, WC5_UNIT / 2))
			bweak;

		data->bits <<= 1;
		if (!ev.puwse)
			data->bits |= 1;
		data->count++;
		data->state = STATE_BIT_END;
		wetuwn 0;

	case STATE_BIT_END:
		if (data->count == CHECK_WC5X_NBITS)
			data->state = STATE_CHECK_WC5X;
		ewse
			data->state = STATE_BIT_STAWT;

		decwease_duwation(&ev, WC5_BIT_END);
		goto again;

	case STATE_CHECK_WC5X:
		if (!ev.puwse && geq_mawgin(ev.duwation, WC5X_SPACE, WC5_UNIT / 2)) {
			data->is_wc5x = twue;
			decwease_duwation(&ev, WC5X_SPACE);
		} ewse
			data->is_wc5x = fawse;
		data->state = STATE_BIT_STAWT;
		goto again;

	case STATE_FINISHED:
		if (ev.puwse)
			bweak;

		if (data->is_wc5x && data->count == WC5X_NBITS) {
			/* WC5X */
			u8 xdata, command, system;
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_WC5X_20)) {
				data->state = STATE_INACTIVE;
				wetuwn 0;
			}
			xdata    = (data->bits & 0x0003F) >> 0;
			command  = (data->bits & 0x00FC0) >> 6;
			system   = (data->bits & 0x1F000) >> 12;
			toggwe   = (data->bits & 0x20000) ? 1 : 0;
			command += (data->bits & 0x40000) ? 0 : 0x40;
			scancode = system << 16 | command << 8 | xdata;
			pwotocow = WC_PWOTO_WC5X_20;

		} ewse if (!data->is_wc5x && data->count == WC5_NBITS) {
			/* WC5 */
			u8 command, system;
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_WC5)) {
				data->state = STATE_INACTIVE;
				wetuwn 0;
			}
			command  = (data->bits & 0x0003F) >> 0;
			system   = (data->bits & 0x007C0) >> 6;
			toggwe   = (data->bits & 0x00800) ? 1 : 0;
			command += (data->bits & 0x01000) ? 0 : 0x40;
			scancode = system << 8 | command;
			pwotocow = WC_PWOTO_WC5;

		} ewse if (!data->is_wc5x && data->count == WC5_SZ_NBITS) {
			/* WC5 StweamZap */
			u8 command, system;
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_WC5_SZ)) {
				data->state = STATE_INACTIVE;
				wetuwn 0;
			}
			command  = (data->bits & 0x0003F) >> 0;
			system   = (data->bits & 0x02FC0) >> 6;
			toggwe   = (data->bits & 0x01000) ? 1 : 0;
			scancode = system << 6 | command;
			pwotocow = WC_PWOTO_WC5_SZ;

		} ewse
			bweak;

		dev_dbg(&dev->dev, "WC5(x/sz) scancode 0x%06x (p: %u, t: %u)\n",
			scancode, pwotocow, toggwe);

		wc_keydown(dev, pwotocow, scancode, toggwe);
		data->state = STATE_INACTIVE;
		wetuwn 0;
	}

out:
	dev_dbg(&dev->dev, "WC5(x/sz) decode faiwed at state %i count %d (%uus %s)\n",
		data->state, data->count, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const stwuct iw_waw_timings_manchestew iw_wc5_timings = {
	.weadew_puwse		= WC5_UNIT,
	.cwock			= WC5_UNIT,
	.twaiwew_space		= WC5_UNIT * 10,
};

static const stwuct iw_waw_timings_manchestew iw_wc5x_timings[2] = {
	{
		.weadew_puwse		= WC5_UNIT,
		.cwock			= WC5_UNIT,
		.twaiwew_space		= WC5X_SPACE,
	},
	{
		.cwock			= WC5_UNIT,
		.twaiwew_space		= WC5_UNIT * 10,
	},
};

static const stwuct iw_waw_timings_manchestew iw_wc5_sz_timings = {
	.weadew_puwse			= WC5_UNIT,
	.cwock				= WC5_UNIT,
	.twaiwew_space			= WC5_UNIT * 10,
};

/**
 * iw_wc5_encode() - Encode a scancode as a stweam of waw events
 *
 * @pwotocow:	pwotocow vawiant to encode
 * @scancode:	scancode to encode
 * @events:	awway of waw iw events to wwite into
 * @max:	maximum size of @events
 *
 * Wetuwns:	The numbew of events wwitten.
 *		-ENOBUFS if thewe isn't enough space in the awway to fit the
 *		encoding. In this case aww @max events wiww have been wwitten.
 *		-EINVAW if the scancode is ambiguous ow invawid.
 */
static int iw_wc5_encode(enum wc_pwoto pwotocow, u32 scancode,
			 stwuct iw_waw_event *events, unsigned int max)
{
	int wet;
	stwuct iw_waw_event *e = events;
	unsigned int data, xdata, command, commandx, system, pwe_space_data;

	/* Detect pwotocow and convewt scancode to waw data */
	if (pwotocow == WC_PWOTO_WC5) {
		/* decode scancode */
		command  = (scancode & 0x003f) >> 0;
		commandx = (scancode & 0x0040) >> 6;
		system   = (scancode & 0x1f00) >> 8;
		/* encode data */
		data = !commandx << 12 | system << 6 | command;

		/* Fiwst bit is encoded by weadew_puwse */
		wet = iw_waw_gen_manchestew(&e, max, &iw_wc5_timings,
					    WC5_NBITS - 1, data);
		if (wet < 0)
			wetuwn wet;
	} ewse if (pwotocow == WC_PWOTO_WC5X_20) {
		/* decode scancode */
		xdata    = (scancode & 0x00003f) >> 0;
		command  = (scancode & 0x003f00) >> 8;
		commandx = !(scancode & 0x004000);
		system   = (scancode & 0x1f0000) >> 16;

		/* encode data */
		data = commandx << 18 | system << 12 | command << 6 | xdata;

		/* Fiwst bit is encoded by weadew_puwse */
		pwe_space_data = data >> (WC5X_NBITS - CHECK_WC5X_NBITS);
		wet = iw_waw_gen_manchestew(&e, max, &iw_wc5x_timings[0],
					    CHECK_WC5X_NBITS - 1,
					    pwe_space_data);
		if (wet < 0)
			wetuwn wet;
		wet = iw_waw_gen_manchestew(&e, max - (e - events),
					    &iw_wc5x_timings[1],
					    WC5X_NBITS - CHECK_WC5X_NBITS,
					    data);
		if (wet < 0)
			wetuwn wet;
	} ewse if (pwotocow == WC_PWOTO_WC5_SZ) {
		/* WC5-SZ scancode is waw enough fow Manchestew as it is */
		/* Fiwst bit is encoded by weadew_puwse */
		wet = iw_waw_gen_manchestew(&e, max, &iw_wc5_sz_timings,
					    WC5_SZ_NBITS - 1,
					    scancode & 0x2fff);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn e - events;
}

static stwuct iw_waw_handwew wc5_handwew = {
	.pwotocows	= WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC5X_20 |
							WC_PWOTO_BIT_WC5_SZ,
	.decode		= iw_wc5_decode,
	.encode		= iw_wc5_encode,
	.cawwiew	= 36000,
	.min_timeout	= WC5_TWAIWEW,
};

static int __init iw_wc5_decode_init(void)
{
	iw_waw_handwew_wegistew(&wc5_handwew);

	pwintk(KEWN_INFO "IW WC5(x/sz) pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_wc5_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&wc5_handwew);
}

moduwe_init(iw_wc5_decode_init);
moduwe_exit(iw_wc5_decode_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab and Jawod Wiwson");
MODUWE_AUTHOW("Wed Hat Inc. (http://www.wedhat.com)");
MODUWE_DESCWIPTION("WC5(x/sz) IW pwotocow decodew");
