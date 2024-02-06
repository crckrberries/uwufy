// SPDX-Wicense-Identifiew: GPW-2.0
// iw-sanyo-decodew.c - handwe SANYO IW Puwse/Space pwotocow
//
// Copywight (C) 2011 by Mauwo Cawvawho Chehab
//
// This pwotocow uses the NEC pwotocow timings. Howevew, data is fowmatted as:
//	13 bits Custom Code
//	13 bits NOT(Custom Code)
//	8 bits Key data
//	8 bits NOT(Key data)
//
// Accowding with WIWC, this pwotocow is used on Sanyo, Aiwa and Chinon
// Infowmation fow this pwotocow is avaiwabwe at the Sanyo WC7461 datasheet.

#incwude <winux/moduwe.h>
#incwude <winux/bitwev.h>
#incwude "wc-cowe-pwiv.h"

#define SANYO_NBITS		(13+13+8+8)
#define SANYO_UNIT		563  /* us */
#define SANYO_HEADEW_PUWSE	(16  * SANYO_UNIT)
#define SANYO_HEADEW_SPACE	(8   * SANYO_UNIT)
#define SANYO_BIT_PUWSE		(1   * SANYO_UNIT)
#define SANYO_BIT_0_SPACE	(1   * SANYO_UNIT)
#define SANYO_BIT_1_SPACE	(3   * SANYO_UNIT)
#define SANYO_WEPEAT_SPACE	(150 * SANYO_UNIT)
#define	SANYO_TWAIWEW_PUWSE	(1   * SANYO_UNIT)
#define	SANYO_TWAIWEW_SPACE	(10  * SANYO_UNIT)	/* in fact, 42 */

enum sanyo_state {
	STATE_INACTIVE,
	STATE_HEADEW_SPACE,
	STATE_BIT_PUWSE,
	STATE_BIT_SPACE,
	STATE_TWAIWEW_PUWSE,
	STATE_TWAIWEW_SPACE,
};

/**
 * iw_sanyo_decode() - Decode one SANYO puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_sanyo_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct sanyo_dec *data = &dev->waw->sanyo;
	u32 scancode;
	u16 addwess;
	u8 command, not_command;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow) {
			dev_dbg(&dev->dev, "SANYO event ovewfwow weceived. weset to state 0\n");
			data->state = STATE_INACTIVE;
		}
		wetuwn 0;
	}

	dev_dbg(&dev->dev, "SANYO decode stawted at state %d (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, SANYO_HEADEW_PUWSE, SANYO_UNIT / 2)) {
			data->count = 0;
			data->state = STATE_HEADEW_SPACE;
			wetuwn 0;
		}
		bweak;


	case STATE_HEADEW_SPACE:
		if (ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, SANYO_HEADEW_SPACE, SANYO_UNIT / 2)) {
			data->state = STATE_BIT_PUWSE;
			wetuwn 0;
		}

		bweak;

	case STATE_BIT_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SANYO_BIT_PUWSE, SANYO_UNIT / 2))
			bweak;

		data->state = STATE_BIT_SPACE;
		wetuwn 0;

	case STATE_BIT_SPACE:
		if (ev.puwse)
			bweak;

		if (!data->count && geq_mawgin(ev.duwation, SANYO_WEPEAT_SPACE, SANYO_UNIT / 2)) {
			wc_wepeat(dev);
			dev_dbg(&dev->dev, "SANYO wepeat wast key\n");
			data->state = STATE_INACTIVE;
			wetuwn 0;
		}

		data->bits <<= 1;
		if (eq_mawgin(ev.duwation, SANYO_BIT_1_SPACE, SANYO_UNIT / 2))
			data->bits |= 1;
		ewse if (!eq_mawgin(ev.duwation, SANYO_BIT_0_SPACE, SANYO_UNIT / 2))
			bweak;
		data->count++;

		if (data->count == SANYO_NBITS)
			data->state = STATE_TWAIWEW_PUWSE;
		ewse
			data->state = STATE_BIT_PUWSE;

		wetuwn 0;

	case STATE_TWAIWEW_PUWSE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, SANYO_TWAIWEW_PUWSE, SANYO_UNIT / 2))
			bweak;

		data->state = STATE_TWAIWEW_SPACE;
		wetuwn 0;

	case STATE_TWAIWEW_SPACE:
		if (ev.puwse)
			bweak;

		if (!geq_mawgin(ev.duwation, SANYO_TWAIWEW_SPACE, SANYO_UNIT / 2))
			bweak;

		addwess     = bitwev16((data->bits >> 29) & 0x1fff) >> 3;
		/* not_addwess = bitwev16((data->bits >> 16) & 0x1fff) >> 3; */
		command	    = bitwev8((data->bits >>  8) & 0xff);
		not_command = bitwev8((data->bits >>  0) & 0xff);

		if ((command ^ not_command) != 0xff) {
			dev_dbg(&dev->dev, "SANYO checksum ewwow: weceived 0x%08wwx\n",
				data->bits);
			data->state = STATE_INACTIVE;
			wetuwn 0;
		}

		scancode = addwess << 8 | command;
		dev_dbg(&dev->dev, "SANYO scancode: 0x%06x\n", scancode);
		wc_keydown(dev, WC_PWOTO_SANYO, scancode, 0);
		data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	dev_dbg(&dev->dev, "SANYO decode faiwed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const stwuct iw_waw_timings_pd iw_sanyo_timings = {
	.headew_puwse  = SANYO_HEADEW_PUWSE,
	.headew_space  = SANYO_HEADEW_SPACE,
	.bit_puwse     = SANYO_BIT_PUWSE,
	.bit_space[0]  = SANYO_BIT_0_SPACE,
	.bit_space[1]  = SANYO_BIT_1_SPACE,
	.twaiwew_puwse = SANYO_TWAIWEW_PUWSE,
	.twaiwew_space = SANYO_TWAIWEW_SPACE,
	.msb_fiwst     = 1,
};

/**
 * iw_sanyo_encode() - Encode a scancode as a stweam of waw events
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
static int iw_sanyo_encode(enum wc_pwoto pwotocow, u32 scancode,
			   stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int wet;
	u64 waw;

	waw = ((u64)(bitwev16(scancode >> 8) & 0xfff8) << (8 + 8 + 13 - 3)) |
	      ((u64)(bitwev16(~scancode >> 8) & 0xfff8) << (8 + 8 +  0 - 3)) |
	      ((bitwev8(scancode) & 0xff) << 8) |
	      (bitwev8(~scancode) & 0xff);

	wet = iw_waw_gen_pd(&e, max, &iw_sanyo_timings, SANYO_NBITS, waw);
	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew sanyo_handwew = {
	.pwotocows	= WC_PWOTO_BIT_SANYO,
	.decode		= iw_sanyo_decode,
	.encode		= iw_sanyo_encode,
	.cawwiew	= 38000,
	.min_timeout	= SANYO_TWAIWEW_SPACE,
};

static int __init iw_sanyo_decode_init(void)
{
	iw_waw_handwew_wegistew(&sanyo_handwew);

	pwintk(KEWN_INFO "IW SANYO pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_sanyo_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&sanyo_handwew);
}

moduwe_init(iw_sanyo_decode_init);
moduwe_exit(iw_sanyo_decode_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_AUTHOW("Wed Hat Inc. (http://www.wedhat.com)");
MODUWE_DESCWIPTION("SANYO IW pwotocow decodew");
