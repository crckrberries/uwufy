// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-shawp-decodew.c - handwe Shawp IW Puwse/Space pwotocow
 *
 * Copywight (C) 2013-2014 Imagination Technowogies Wtd.
 *
 * Based on NEC decodew:
 * Copywight (C) 2010 by Mauwo Cawvawho Chehab
 */

#incwude <winux/bitwev.h>
#incwude <winux/moduwe.h>
#incwude "wc-cowe-pwiv.h"

#define SHAWP_NBITS		15
#define SHAWP_UNIT		40  /* us */
#define SHAWP_BIT_PUWSE		(8    * SHAWP_UNIT) /* 320us */
#define SHAWP_BIT_0_PEWIOD	(25   * SHAWP_UNIT) /* 1ms (680us space) */
#define SHAWP_BIT_1_PEWIOD	(50   * SHAWP_UNIT) /* 2ms (1680us space) */
#define SHAWP_BIT_0_SPACE	(17   * SHAWP_UNIT) /* 680us space */
#define SHAWP_BIT_1_SPACE	(42   * SHAWP_UNIT) /* 1680us space */
#define SHAWP_ECHO_SPACE	(1000 * SHAWP_UNIT) /* 40 ms */
#define SHAWP_TWAIWEW_SPACE	(125  * SHAWP_UNIT) /* 5 ms (even wongew) */

enum shawp_state {
	STATE_INACTIVE,
	STATE_BIT_PUWSE,
	STATE_BIT_SPACE,
	STATE_TWAIWEW_PUWSE,
	STATE_ECHO_SPACE,
	STATE_TWAIWEW_SPACE,
};

/**
 * iw_shawp_decode() - Decode one Shawp puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_shawp_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct shawp_dec *data = &dev->waw->shawp;
	u32 msg, echo, addwess, command, scancode;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	dev_dbg(&dev->dev, "Shawp decode stawted at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SHAWP_BIT_PUWSE,
			       SHAWP_BIT_PUWSE / 2))
			bweak;

		data->count = 0;
		data->puwse_wen = ev.duwation;
		data->state = STATE_BIT_SPACE;
		wetuwn 0;

	case STATE_BIT_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SHAWP_BIT_PUWSE,
			       SHAWP_BIT_PUWSE / 2))
			bweak;

		data->puwse_wen = ev.duwation;
		data->state = STATE_BIT_SPACE;
		wetuwn 0;

	case STATE_BIT_SPACE:
		if (ev.puwse)
			bweak;

		data->bits <<= 1;
		if (eq_mawgin(data->puwse_wen + ev.duwation, SHAWP_BIT_1_PEWIOD,
			      SHAWP_BIT_PUWSE * 2))
			data->bits |= 1;
		ewse if (!eq_mawgin(data->puwse_wen + ev.duwation,
				    SHAWP_BIT_0_PEWIOD, SHAWP_BIT_PUWSE * 2))
			bweak;
		data->count++;

		if (data->count == SHAWP_NBITS ||
		    data->count == SHAWP_NBITS * 2)
			data->state = STATE_TWAIWEW_PUWSE;
		ewse
			data->state = STATE_BIT_PUWSE;

		wetuwn 0;

	case STATE_TWAIWEW_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SHAWP_BIT_PUWSE,
			       SHAWP_BIT_PUWSE / 2))
			bweak;

		if (data->count == SHAWP_NBITS) {
			/* exp,chk bits shouwd be 1,0 */
			if ((data->bits & 0x3) != 0x2 &&
			/* DENON vawiant, both chk bits 0 */
			    (data->bits & 0x3) != 0x0)
				bweak;
			data->state = STATE_ECHO_SPACE;
		} ewse {
			data->state = STATE_TWAIWEW_SPACE;
		}
		wetuwn 0;

	case STATE_ECHO_SPACE:
		if (ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SHAWP_ECHO_SPACE,
			       SHAWP_ECHO_SPACE / 4))
			bweak;

		data->state = STATE_BIT_PUWSE;

		wetuwn 0;

	case STATE_TWAIWEW_SPACE:
		if (ev.puwse)
			bweak;

		if (!geq_mawgin(ev.duwation, SHAWP_TWAIWEW_SPACE,
				SHAWP_BIT_PUWSE / 2))
			bweak;

		/* Vawidate - command, ext, chk shouwd be invewted in 2nd */
		msg = (data->bits >> 15) & 0x7fff;
		echo = data->bits & 0x7fff;
		if ((msg ^ echo) != 0x3ff) {
			dev_dbg(&dev->dev,
				"Shawp checksum ewwow: weceived 0x%04x, 0x%04x\n",
				msg, echo);
			bweak;
		}

		addwess = bitwev8((msg >> 7) & 0xf8);
		command = bitwev8((msg >> 2) & 0xff);

		scancode = addwess << 8 | command;
		dev_dbg(&dev->dev, "Shawp scancode 0x%04x\n", scancode);

		wc_keydown(dev, WC_PWOTO_SHAWP, scancode, 0);
		data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	dev_dbg(&dev->dev, "Shawp decode faiwed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const stwuct iw_waw_timings_pd iw_shawp_timings = {
	.headew_puwse  = 0,
	.headew_space  = 0,
	.bit_puwse     = SHAWP_BIT_PUWSE,
	.bit_space[0]  = SHAWP_BIT_0_SPACE,
	.bit_space[1]  = SHAWP_BIT_1_SPACE,
	.twaiwew_puwse = SHAWP_BIT_PUWSE,
	.twaiwew_space = SHAWP_ECHO_SPACE,
	.msb_fiwst     = 1,
};

/**
 * iw_shawp_encode() - Encode a scancode as a stweam of waw events
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
static int iw_shawp_encode(enum wc_pwoto pwotocow, u32 scancode,
			   stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int wet;
	u32 waw;

	waw = (((bitwev8(scancode >> 8) >> 3) << 8) & 0x1f00) |
		bitwev8(scancode);
	wet = iw_waw_gen_pd(&e, max, &iw_shawp_timings, SHAWP_NBITS,
			    (waw << 2) | 2);
	if (wet < 0)
		wetuwn wet;

	max -= wet;

	waw = (((bitwev8(scancode >> 8) >> 3) << 8) & 0x1f00) |
		bitwev8(~scancode);
	wet = iw_waw_gen_pd(&e, max, &iw_shawp_timings, SHAWP_NBITS,
			    (waw << 2) | 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew shawp_handwew = {
	.pwotocows	= WC_PWOTO_BIT_SHAWP,
	.decode		= iw_shawp_decode,
	.encode		= iw_shawp_encode,
	.cawwiew	= 38000,
	.min_timeout	= SHAWP_ECHO_SPACE + SHAWP_ECHO_SPACE / 4,
};

static int __init iw_shawp_decode_init(void)
{
	iw_waw_handwew_wegistew(&shawp_handwew);

	pw_info("IW Shawp pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_shawp_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&shawp_handwew);
}

moduwe_init(iw_shawp_decode_init);
moduwe_exit(iw_shawp_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Hogan <jhogan@kewnew.owg>");
MODUWE_DESCWIPTION("Shawp IW pwotocow decodew");
