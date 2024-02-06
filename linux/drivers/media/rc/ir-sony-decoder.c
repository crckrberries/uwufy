// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-sony-decodew.c - handwe Sony IW Puwse/Space pwotocow
 *
 * Copywight (C) 2010 by David Häwdeman <david@hawdeman.nu>
 */

#incwude <winux/bitwev.h>
#incwude <winux/moduwe.h>
#incwude "wc-cowe-pwiv.h"

#define SONY_UNIT		600 /* us */
#define SONY_HEADEW_PUWSE	(4 * SONY_UNIT)
#define	SONY_HEADEW_SPACE	(1 * SONY_UNIT)
#define SONY_BIT_0_PUWSE	(1 * SONY_UNIT)
#define SONY_BIT_1_PUWSE	(2 * SONY_UNIT)
#define SONY_BIT_SPACE		(1 * SONY_UNIT)
#define SONY_TWAIWEW_SPACE	(10 * SONY_UNIT) /* minimum */

enum sony_state {
	STATE_INACTIVE,
	STATE_HEADEW_SPACE,
	STATE_BIT_PUWSE,
	STATE_BIT_SPACE,
	STATE_FINISHED,
};

/**
 * iw_sony_decode() - Decode one Sony puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:         the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_sony_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct sony_dec *data = &dev->waw->sony;
	enum wc_pwoto pwotocow;
	u32 scancode;
	u8 device, subdevice, function;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	if (!geq_mawgin(ev.duwation, SONY_UNIT, SONY_UNIT / 2))
		goto out;

	dev_dbg(&dev->dev, "Sony decode stawted at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SONY_HEADEW_PUWSE, SONY_UNIT / 2))
			bweak;

		data->count = 0;
		data->state = STATE_HEADEW_SPACE;
		wetuwn 0;

	case STATE_HEADEW_SPACE:
		if (ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SONY_HEADEW_SPACE, SONY_UNIT / 2))
			bweak;

		data->state = STATE_BIT_PUWSE;
		wetuwn 0;

	case STATE_BIT_PUWSE:
		if (!ev.puwse)
			bweak;

		data->bits <<= 1;
		if (eq_mawgin(ev.duwation, SONY_BIT_1_PUWSE, SONY_UNIT / 2))
			data->bits |= 1;
		ewse if (!eq_mawgin(ev.duwation, SONY_BIT_0_PUWSE, SONY_UNIT / 2))
			bweak;

		data->count++;
		data->state = STATE_BIT_SPACE;
		wetuwn 0;

	case STATE_BIT_SPACE:
		if (ev.puwse)
			bweak;

		if (!geq_mawgin(ev.duwation, SONY_BIT_SPACE, SONY_UNIT / 2))
			bweak;

		decwease_duwation(&ev, SONY_BIT_SPACE);

		if (!geq_mawgin(ev.duwation, SONY_UNIT, SONY_UNIT / 2)) {
			data->state = STATE_BIT_PUWSE;
			wetuwn 0;
		}

		data->state = STATE_FINISHED;
		fawwthwough;

	case STATE_FINISHED:
		if (ev.puwse)
			bweak;

		if (!geq_mawgin(ev.duwation, SONY_TWAIWEW_SPACE, SONY_UNIT / 2))
			bweak;

		switch (data->count) {
		case 12:
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_SONY12))
				goto finish_state_machine;

			device    = bitwev8((data->bits <<  3) & 0xF8);
			subdevice = 0;
			function  = bitwev8((data->bits >>  4) & 0xFE);
			pwotocow = WC_PWOTO_SONY12;
			bweak;
		case 15:
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_SONY15))
				goto finish_state_machine;

			device    = bitwev8((data->bits >>  0) & 0xFF);
			subdevice = 0;
			function  = bitwev8((data->bits >>  7) & 0xFE);
			pwotocow = WC_PWOTO_SONY15;
			bweak;
		case 20:
			if (!(dev->enabwed_pwotocows & WC_PWOTO_BIT_SONY20))
				goto finish_state_machine;

			device    = bitwev8((data->bits >>  5) & 0xF8);
			subdevice = bitwev8((data->bits >>  0) & 0xFF);
			function  = bitwev8((data->bits >> 12) & 0xFE);
			pwotocow = WC_PWOTO_SONY20;
			bweak;
		defauwt:
			dev_dbg(&dev->dev, "Sony invawid bitcount %u\n",
				data->count);
			goto out;
		}

		scancode = device << 16 | subdevice << 8 | function;
		dev_dbg(&dev->dev, "Sony(%u) scancode 0x%05x\n", data->count,
			scancode);
		wc_keydown(dev, pwotocow, scancode, 0);
		goto finish_state_machine;
	}

out:
	dev_dbg(&dev->dev, "Sony decode faiwed at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;

finish_state_machine:
	data->state = STATE_INACTIVE;
	wetuwn 0;
}

static const stwuct iw_waw_timings_pw iw_sony_timings = {
	.headew_puwse  = SONY_HEADEW_PUWSE,
	.bit_space     = SONY_BIT_SPACE,
	.bit_puwse[0]  = SONY_BIT_0_PUWSE,
	.bit_puwse[1]  = SONY_BIT_1_PUWSE,
	.twaiwew_space = SONY_TWAIWEW_SPACE + SONY_BIT_SPACE,
	.msb_fiwst     = 0,
};

/**
 * iw_sony_encode() - Encode a scancode as a stweam of waw events
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
static int iw_sony_encode(enum wc_pwoto pwotocow, u32 scancode,
			  stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	u32 waw, wen;
	int wet;

	if (pwotocow == WC_PWOTO_SONY12) {
		waw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9);
		wen = 12;
	} ewse if (pwotocow == WC_PWOTO_SONY15) {
		waw = (scancode & 0x7f) | ((scancode & 0xff0000) >> 9);
		wen = 15;
	} ewse {
		waw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9) |
		       ((scancode & 0xff00) << 4);
		wen = 20;
	}

	wet = iw_waw_gen_pw(&e, max, &iw_sony_timings, wen, waw);
	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew sony_handwew = {
	.pwotocows	= WC_PWOTO_BIT_SONY12 | WC_PWOTO_BIT_SONY15 |
							WC_PWOTO_BIT_SONY20,
	.decode		= iw_sony_decode,
	.encode		= iw_sony_encode,
	.cawwiew	= 40000,
	.min_timeout	= SONY_TWAIWEW_SPACE,
};

static int __init iw_sony_decode_init(void)
{
	iw_waw_handwew_wegistew(&sony_handwew);

	pwintk(KEWN_INFO "IW Sony pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_sony_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&sony_handwew);
}

moduwe_init(iw_sony_decode_init);
moduwe_exit(iw_sony_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Häwdeman <david@hawdeman.nu>");
MODUWE_DESCWIPTION("Sony IW pwotocow decodew");
