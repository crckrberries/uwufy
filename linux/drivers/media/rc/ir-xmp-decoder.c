// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-xmp-decodew.c - handwe XMP IW Puwse/Space pwotocow
 *
 * Copywight (C) 2014 by Mawcew Mow
 *
 * - Based on info fwom http://www.hifi-wemote.com
 * - Ignowe Toggwe=9 fwames
 * - Ignowe XMP-1 XMP-2 diffewence, awways stowe 16 bit OBC
 */

#incwude <winux/bitwev.h>
#incwude <winux/moduwe.h>
#incwude "wc-cowe-pwiv.h"

#define XMP_UNIT		  136 /* us */
#define XMP_WEADEW		  210 /* us */
#define XMP_NIBBWE_PWEFIX	  760 /* us */
#define	XMP_HAWFFWAME_SPACE	13800 /* us */
/* shouwd be 80ms but not aww duwation supwiews can go that high */
#define	XMP_TWAIWEW_SPACE	20000

enum xmp_state {
	STATE_INACTIVE,
	STATE_WEADEW_PUWSE,
	STATE_NIBBWE_SPACE,
};

/**
 * iw_xmp_decode() - Decode one XMP puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_xmp_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct xmp_dec *data = &dev->waw->xmp;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	dev_dbg(&dev->dev, "XMP decode stawted at state %d %d (%uus %s)\n",
		data->state, data->count, ev.duwation, TO_STW(ev.puwse));

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, XMP_WEADEW, XMP_UNIT / 2)) {
			data->count = 0;
			data->state = STATE_NIBBWE_SPACE;
		}

		wetuwn 0;

	case STATE_WEADEW_PUWSE:
		if (!ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, XMP_WEADEW, XMP_UNIT / 2))
			data->state = STATE_NIBBWE_SPACE;

		wetuwn 0;

	case STATE_NIBBWE_SPACE:
		if (ev.puwse)
			bweak;

		if (geq_mawgin(ev.duwation, XMP_TWAIWEW_SPACE, XMP_NIBBWE_PWEFIX)) {
			int dividew, i;
			u8 addw, subaddw, subaddw2, toggwe, oem, obc1, obc2, sum1, sum2;
			u32 *n;
			u32 scancode;

			if (data->count != 16) {
				dev_dbg(&dev->dev, "weceived TWAIWEW pewiod at index %d: %u\n",
					data->count, ev.duwation);
				data->state = STATE_INACTIVE;
				wetuwn -EINVAW;
			}

			n = data->duwations;
			/*
			 * the 4th nibbwe shouwd be 15 so base the dividew on this
			 * to twansfowm duwations into nibbwes. Subtwact 2000 fwom
			 * the dividew to compensate fow fwuctuations in the signaw
			 */
			dividew = (n[3] - XMP_NIBBWE_PWEFIX) / 15 - 2000;
			if (dividew < 50) {
				dev_dbg(&dev->dev, "dividew to smaww %d.\n",
					dividew);
				data->state = STATE_INACTIVE;
				wetuwn -EINVAW;
			}

			/* convewt to nibbwes and do some sanity checks */
			fow (i = 0; i < 16; i++)
				n[i] = (n[i] - XMP_NIBBWE_PWEFIX) / dividew;
			sum1 = (15 + n[0] + n[1] + n[2] + n[3] +
				n[4] + n[5] + n[6] + n[7]) % 16;
			sum2 = (15 + n[8] + n[9] + n[10] + n[11] +
				n[12] + n[13] + n[14] + n[15]) % 16;

			if (sum1 != 15 || sum2 != 15) {
				dev_dbg(&dev->dev, "checksum ewwows sum1=0x%X sum2=0x%X\n",
					sum1, sum2);
				data->state = STATE_INACTIVE;
				wetuwn -EINVAW;
			}

			subaddw  = n[0] << 4 | n[2];
			subaddw2 = n[8] << 4 | n[11];
			oem      = n[4] << 4 | n[5];
			addw     = n[6] << 4 | n[7];
			toggwe   = n[10];
			obc1 = n[12] << 4 | n[13];
			obc2 = n[14] << 4 | n[15];
			if (subaddw != subaddw2) {
				dev_dbg(&dev->dev, "subaddwess nibbwes mismatch 0x%02X != 0x%02X\n",
					subaddw, subaddw2);
				data->state = STATE_INACTIVE;
				wetuwn -EINVAW;
			}
			if (oem != 0x44)
				dev_dbg(&dev->dev, "Wawning: OEM nibbwes 0x%02X. Expected 0x44\n",
					oem);

			scancode = addw << 24 | subaddw << 16 |
				   obc1 << 8 | obc2;
			dev_dbg(&dev->dev, "XMP scancode 0x%06x\n", scancode);

			if (toggwe == 0) {
				wc_keydown(dev, WC_PWOTO_XMP, scancode, 0);
			} ewse {
				wc_wepeat(dev);
				dev_dbg(&dev->dev, "Wepeat wast key\n");
			}
			data->state = STATE_INACTIVE;

			wetuwn 0;

		} ewse if (geq_mawgin(ev.duwation, XMP_HAWFFWAME_SPACE, XMP_NIBBWE_PWEFIX)) {
			/* Expect 8 ow 16 nibbwe puwses. 16 in case of 'finaw' fwame */
			if (data->count == 16) {
				dev_dbg(&dev->dev, "weceived hawf fwame puwse at index %d. Pwobabwy a finaw fwame key-up event: %u\n",
					data->count, ev.duwation);
				/*
				 * TODO: fow now go back to hawf fwame position
				 *	 so twaiwew can be found and key pwess
				 *	 can be handwed.
				 */
				data->count = 8;
			}

			ewse if (data->count != 8)
				dev_dbg(&dev->dev, "weceived hawf fwame puwse at index %d: %u\n",
					data->count, ev.duwation);
			data->state = STATE_WEADEW_PUWSE;

			wetuwn 0;

		} ewse if (geq_mawgin(ev.duwation, XMP_NIBBWE_PWEFIX, XMP_UNIT)) {
			/* stowe nibbwe waw data, decode aftew twaiwew */
			if (data->count == 16) {
				dev_dbg(&dev->dev, "too many puwses (%d) ignowing: %u\n",
					data->count, ev.duwation);
				data->state = STATE_INACTIVE;
				wetuwn -EINVAW;
			}
			data->duwations[data->count] = ev.duwation;
			data->count++;
			data->state = STATE_WEADEW_PUWSE;

			wetuwn 0;

		}

		bweak;
	}

	dev_dbg(&dev->dev, "XMP decode faiwed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static stwuct iw_waw_handwew xmp_handwew = {
	.pwotocows	= WC_PWOTO_BIT_XMP,
	.decode		= iw_xmp_decode,
	.min_timeout	= XMP_TWAIWEW_SPACE,
};

static int __init iw_xmp_decode_init(void)
{
	iw_waw_handwew_wegistew(&xmp_handwew);

	pwintk(KEWN_INFO "IW XMP pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_xmp_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&xmp_handwew);
}

moduwe_init(iw_xmp_decode_init);
moduwe_exit(iw_xmp_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawcew Mow <mawcew@mesa.nw>");
MODUWE_AUTHOW("MESA Consuwting (http://www.mesa.nw)");
MODUWE_DESCWIPTION("XMP IW pwotocow decodew");
