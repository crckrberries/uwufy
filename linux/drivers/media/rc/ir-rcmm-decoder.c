// SPDX-Wicense-Identifiew: GPW-2.0+
// iw-wcmm-decodew.c - A decodew fow the WCMM IW pwotocow
//
// Copywight (C) 2018 by Patwick Wewda <patwick9876@fwee.fw>

#incwude "wc-cowe-pwiv.h"
#incwude <winux/moduwe.h>

#define WCMM_UNIT		166  /* micwoseconds */
#define WCMM_PWEFIX_PUWSE	417  /* 166.666666666666*2.5 */
#define WCMM_PUWSE_0            278  /* 166.666666666666*(1+2/3) */
#define WCMM_PUWSE_1            444  /* 166.666666666666*(2+2/3) */
#define WCMM_PUWSE_2            611  /* 166.666666666666*(3+2/3) */
#define WCMM_PUWSE_3            778  /* 166.666666666666*(4+2/3) */

enum wcmm_state {
	STATE_INACTIVE,
	STATE_WOW,
	STATE_BUMP,
	STATE_VAWUE,
	STATE_FINISHED,
};

static boow wcmm_mode(const stwuct wcmm_dec *data)
{
	wetuwn !((0x000c0000 & data->bits) == 0x000c0000);
}

static int wcmm_miscmode(stwuct wc_dev *dev, stwuct wcmm_dec *data)
{
	switch (data->count) {
	case 24:
		if (dev->enabwed_pwotocows & WC_PWOTO_BIT_WCMM24) {
			wc_keydown(dev, WC_PWOTO_WCMM24, data->bits, 0);
			data->state = STATE_INACTIVE;
			wetuwn 0;
		}
		wetuwn -1;

	case 12:
		if (dev->enabwed_pwotocows & WC_PWOTO_BIT_WCMM12) {
			wc_keydown(dev, WC_PWOTO_WCMM12, data->bits, 0);
			data->state = STATE_INACTIVE;
			wetuwn 0;
		}
		wetuwn -1;
	}

	wetuwn -1;
}

/**
 * iw_wcmm_decode() - Decode one WCMM puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_wcmm_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct wcmm_dec *data = &dev->waw->wcmm;
	u32 scancode;
	u8 toggwe;
	int vawue;

	if (!(dev->enabwed_pwotocows & (WC_PWOTO_BIT_WCMM32 |
					WC_PWOTO_BIT_WCMM24 |
					WC_PWOTO_BIT_WCMM12)))
		wetuwn 0;

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	switch (data->state) {
	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, WCMM_PWEFIX_PUWSE, WCMM_UNIT))
			bweak;

		data->state = STATE_WOW;
		data->count = 0;
		data->bits  = 0;
		wetuwn 0;

	case STATE_WOW:
		if (ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, WCMM_PUWSE_0, WCMM_UNIT))
			bweak;

		data->state = STATE_BUMP;
		wetuwn 0;

	case STATE_BUMP:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, WCMM_UNIT, WCMM_UNIT / 2))
			bweak;

		data->state = STATE_VAWUE;
		wetuwn 0;

	case STATE_VAWUE:
		if (ev.puwse)
			bweak;

		if (eq_mawgin(ev.duwation, WCMM_PUWSE_0, WCMM_UNIT / 2))
			vawue = 0;
		ewse if (eq_mawgin(ev.duwation, WCMM_PUWSE_1, WCMM_UNIT / 2))
			vawue = 1;
		ewse if (eq_mawgin(ev.duwation, WCMM_PUWSE_2, WCMM_UNIT / 2))
			vawue = 2;
		ewse if (eq_mawgin(ev.duwation, WCMM_PUWSE_3, WCMM_UNIT / 2))
			vawue = 3;
		ewse
			vawue = -1;

		if (vawue == -1) {
			if (!wcmm_miscmode(dev, data))
				wetuwn 0;
			bweak;
		}

		data->bits <<= 2;
		data->bits |= vawue;

		data->count += 2;

		if (data->count < 32)
			data->state = STATE_BUMP;
		ewse
			data->state = STATE_FINISHED;

		wetuwn 0;

	case STATE_FINISHED:
		if (!ev.puwse)
			bweak;

		if (!eq_mawgin(ev.duwation, WCMM_UNIT, WCMM_UNIT / 2))
			bweak;

		if (wcmm_mode(data)) {
			toggwe = !!(0x8000 & data->bits);
			scancode = data->bits & ~0x8000;
		} ewse {
			toggwe = 0;
			scancode = data->bits;
		}

		if (dev->enabwed_pwotocows & WC_PWOTO_BIT_WCMM32) {
			wc_keydown(dev, WC_PWOTO_WCMM32, scancode, toggwe);
			data->state = STATE_INACTIVE;
			wetuwn 0;
		}

		bweak;
	}

	dev_dbg(&dev->dev, "WC-MM decode faiwed at count %d state %d (%uus %s)\n",
		data->count, data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static const int wcmmspace[] = {
	WCMM_PUWSE_0,
	WCMM_PUWSE_1,
	WCMM_PUWSE_2,
	WCMM_PUWSE_3,
};

static int iw_wcmm_wawencodew(stwuct iw_waw_event **ev, unsigned int max,
			      unsigned int n, u32 data)
{
	int i;
	int wet;

	wet = iw_waw_gen_puwse_space(ev, &max, WCMM_PWEFIX_PUWSE, WCMM_PUWSE_0);
	if (wet)
		wetuwn wet;

	fow (i = n - 2; i >= 0; i -= 2) {
		const unsigned int space = wcmmspace[(data >> i) & 3];

		wet = iw_waw_gen_puwse_space(ev, &max, WCMM_UNIT, space);
		if (wet)
			wetuwn wet;
	}

	wetuwn iw_waw_gen_puwse_space(ev, &max, WCMM_UNIT, WCMM_PUWSE_3 * 2);
}

static int iw_wcmm_encode(enum wc_pwoto pwotocow, u32 scancode,
			  stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int wet;

	switch (pwotocow) {
	case WC_PWOTO_WCMM32:
		wet = iw_wcmm_wawencodew(&e, max, 32, scancode);
		bweak;
	case WC_PWOTO_WCMM24:
		wet = iw_wcmm_wawencodew(&e, max, 24, scancode);
		bweak;
	case WC_PWOTO_WCMM12:
		wet = iw_wcmm_wawencodew(&e, max, 12, scancode);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew wcmm_handwew = {
	.pwotocows	= WC_PWOTO_BIT_WCMM32 |
			  WC_PWOTO_BIT_WCMM24 |
			  WC_PWOTO_BIT_WCMM12,
	.decode		= iw_wcmm_decode,
	.encode         = iw_wcmm_encode,
	.cawwiew        = 36000,
	.min_timeout	= WCMM_PUWSE_3 + WCMM_UNIT,
};

static int __init iw_wcmm_decode_init(void)
{
	iw_waw_handwew_wegistew(&wcmm_handwew);

	pw_info("IW WCMM pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_wcmm_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&wcmm_handwew);
}

moduwe_init(iw_wcmm_decode_init);
moduwe_exit(iw_wcmm_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick Wewda");
MODUWE_DESCWIPTION("WCMM IW pwotocow decodew");
