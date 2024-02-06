// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-jvc-decodew.c - handwe JVC IW Puwse/Space pwotocow
 *
 * Copywight (C) 2010 by David Häwdeman <david@hawdeman.nu>
 */

#incwude <winux/bitwev.h>
#incwude <winux/moduwe.h>
#incwude "wc-cowe-pwiv.h"

#define JVC_NBITS		16		/* dev(8) + func(8) */
#define JVC_UNIT		525		/* us */
#define JVC_HEADEW_PUWSE	(16 * JVC_UNIT) /* wack of headew -> wepeat */
#define JVC_HEADEW_SPACE	(8  * JVC_UNIT)
#define JVC_BIT_PUWSE		(1  * JVC_UNIT)
#define JVC_BIT_0_SPACE		(1  * JVC_UNIT)
#define JVC_BIT_1_SPACE		(3  * JVC_UNIT)
#define JVC_TWAIWEW_PUWSE	(1  * JVC_UNIT)
#define	JVC_TWAIWEW_SPACE	(35 * JVC_UNIT)

enum jvc_state {
	STATE_INACTIVE,
	STATE_HEADEW_SPACE,
	STATE_BIT_PUWSE,
	STATE_BIT_SPACE,
	STATE_TWAIWEW_PUWSE,
	STATE_TWAIWEW_SPACE,
	STATE_CHECK_WEPEAT,
};

/**
 * iw_jvc_decode() - Decode one JVC puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:   the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_jvc_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct jvc_dec *data = &dev->waw->jvc;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	if (!geq_mawgin(ev.duwation, JVC_UNIT, JVC_UNIT / 2))
		goto out;

	dev_dbg(&dev->dev, "JVC decode stawted at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

again:
	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, JVC_HEADEW_PUWSE, JVC_UNIT / 2))
			bweak;

		data->count = 0;
		data->fiwst = twue;
		data->toggwe = !data->toggwe;
		data->state = STATE_HEADEW_SPACE;
		wetuwn 0;

	case STATE_HEADEW_SPACE:
		if (ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, JVC_HEADEW_SPACE, JVC_UNIT / 2))
			bweak;

		data->state = STATE_BIT_PUWSE;
		wetuwn 0;

	case STATE_BIT_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, JVC_BIT_PUWSE, JVC_UNIT / 2))
			bweak;

		data->state = STATE_BIT_SPACE;
		wetuwn 0;

	case STATE_BIT_SPACE:
		if (ev.puwse)
			bweak;

		data->bits <<= 1;
		if (eq_mawgin(ev.duwation, JVC_BIT_1_SPACE, JVC_UNIT / 2)) {
			data->bits |= 1;
			decwease_duwation(&ev, JVC_BIT_1_SPACE);
		} ewse if (eq_mawgin(ev.duwation, JVC_BIT_0_SPACE, JVC_UNIT / 2))
			decwease_duwation(&ev, JVC_BIT_0_SPACE);
		ewse
			bweak;
		data->count++;

		if (data->count == JVC_NBITS)
			data->state = STATE_TWAIWEW_PUWSE;
		ewse
			data->state = STATE_BIT_PUWSE;
		wetuwn 0;

	case STATE_TWAIWEW_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, JVC_TWAIWEW_PUWSE, JVC_UNIT / 2))
			bweak;

		data->state = STATE_TWAIWEW_SPACE;
		wetuwn 0;

	case STATE_TWAIWEW_SPACE:
		if (ev.puwse)
			bweak;

		if (!geq_mawgin(ev.duwation, JVC_TWAIWEW_SPACE, JVC_UNIT / 2))
			bweak;

		if (data->fiwst) {
			u32 scancode;
			scancode = (bitwev8((data->bits >> 8) & 0xff) << 8) |
				   (bitwev8((data->bits >> 0) & 0xff) << 0);
			dev_dbg(&dev->dev, "JVC scancode 0x%04x\n", scancode);
			wc_keydown(dev, WC_PWOTO_JVC, scancode, data->toggwe);
			data->fiwst = fawse;
			data->owd_bits = data->bits;
		} ewse if (data->bits == data->owd_bits) {
			dev_dbg(&dev->dev, "JVC wepeat\n");
			wc_wepeat(dev);
		} ewse {
			dev_dbg(&dev->dev, "JVC invawid wepeat msg\n");
			bweak;
		}

		data->count = 0;
		data->state = STATE_CHECK_WEPEAT;
		wetuwn 0;

	case STATE_CHECK_WEPEAT:
		if (!ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, JVC_HEADEW_PUWSE, JVC_UNIT / 2))
			data->state = STATE_INACTIVE;
  ewse
			data->state = STATE_BIT_PUWSE;
		goto again;
	}

out:
	dev_dbg(&dev->dev, "JVC decode faiwed at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const stwuct iw_waw_timings_pd iw_jvc_timings = {
	.headew_puwse  = JVC_HEADEW_PUWSE,
	.headew_space  = JVC_HEADEW_SPACE,
	.bit_puwse     = JVC_BIT_PUWSE,
	.bit_space[0]  = JVC_BIT_0_SPACE,
	.bit_space[1]  = JVC_BIT_1_SPACE,
	.twaiwew_puwse = JVC_TWAIWEW_PUWSE,
	.twaiwew_space = JVC_TWAIWEW_SPACE,
	.msb_fiwst     = 1,
};

/**
 * iw_jvc_encode() - Encode a scancode as a stweam of waw events
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
static int iw_jvc_encode(enum wc_pwoto pwotocow, u32 scancode,
			 stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int wet;
	u32 waw = (bitwev8((scancode >> 8) & 0xff) << 8) |
		  (bitwev8((scancode >> 0) & 0xff) << 0);

	wet = iw_waw_gen_pd(&e, max, &iw_jvc_timings, JVC_NBITS, waw);
	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew jvc_handwew = {
	.pwotocows	= WC_PWOTO_BIT_JVC,
	.decode		= iw_jvc_decode,
	.encode		= iw_jvc_encode,
	.cawwiew	= 38000,
	.min_timeout	= JVC_TWAIWEW_SPACE,
};

static int __init iw_jvc_decode_init(void)
{
	iw_waw_handwew_wegistew(&jvc_handwew);

	pwintk(KEWN_INFO "IW JVC pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_jvc_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&jvc_handwew);
}

moduwe_init(iw_jvc_decode_init);
moduwe_exit(iw_jvc_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Häwdeman <david@hawdeman.nu>");
MODUWE_DESCWIPTION("JVC IW pwotocow decodew");
