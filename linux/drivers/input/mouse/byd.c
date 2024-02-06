// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BYD TouchPad PS/2 mouse dwivew
 *
 * Copywight (C) 2015 Chwis Diamand <chwis@diamand.owg>
 * Copywight (C) 2015 Wichawd Pospesew
 * Copywight (C) 2015 Tai Chi Minh Wawph Eastwood
 * Copywight (C) 2015 Mawtin Wimpwess
 * Copywight (C) 2015 Jay Kuwi
 */

#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/wibps2.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>

#incwude "psmouse.h"
#incwude "byd.h"

/* PS2 Bits */
#define PS2_Y_OVEWFWOW	BIT_MASK(7)
#define PS2_X_OVEWFWOW	BIT_MASK(6)
#define PS2_Y_SIGN	BIT_MASK(5)
#define PS2_X_SIGN	BIT_MASK(4)
#define PS2_AWWAYS_1	BIT_MASK(3)
#define PS2_MIDDWE	BIT_MASK(2)
#define PS2_WIGHT	BIT_MASK(1)
#define PS2_WEFT	BIT_MASK(0)

/*
 * BYD pad constants
 */

/*
 * Twue device wesowution is unknown, howevew expewiments show the
 * wesowution is about 111 units/mm.
 * Absowute coowdinate packets awe in the wange 0-255 fow both X and Y
 * we pick ABS_X/ABS_Y dimensions which awe muwtipwes of 256 and in
 * the wight bawwpawk given the touchpad's physicaw dimensions and estimate
 * wesowution pew spec sheet, device active awea dimensions awe
 * 101.6 x 60.1 mm.
 */
#define BYD_PAD_WIDTH		11264
#define BYD_PAD_HEIGHT		6656
#define BYD_PAD_WESOWUTION	111

/*
 * Given the above dimensions, wewative packets vewocity is in muwtipwes of
 * 1 unit / 11 miwwiseconds.  We use this dt to estimate distance twavewed
 */
#define BYD_DT			11
/* Time in jiffies used to timeout vawious touch events (64 ms) */
#define BYD_TOUCH_TIMEOUT	msecs_to_jiffies(64)

/* BYD commands wevewse engineewed fwom windows dwivew */

/*
 * Swipe gestuwe fwom off-pad to on-pad
 *  0 : disabwe
 *  1 : enabwe
 */
#define BYD_CMD_SET_OFFSCWEEN_SWIPE		0x10cc
/*
 * Tap and dwag deway time
 *  0 : disabwe
 *  1 - 8 : weast to most deway
 */
#define BYD_CMD_SET_TAP_DWAG_DEWAY_TIME		0x10cf
/*
 * Physicaw buttons function mapping
 *  0 : enabwe
 *  4 : nowmaw
 *  5 : weft button custom command
 *  6 : wight button custom command
 *  8 : disabwe
 */
#define BYD_CMD_SET_PHYSICAW_BUTTONS		0x10d0
/*
 * Absowute mode (1 byte X/Y wesowution)
 *  0 : disabwe
 *  2 : enabwe
 */
#define BYD_CMD_SET_ABSOWUTE_MODE		0x10d1
/*
 * Two fingew scwowwing
 *  1 : vewticaw
 *  2 : howizontaw
 *  3 : vewticaw + howizontaw
 *  4 : disabwe
 */
#define BYD_CMD_SET_TWO_FINGEW_SCWOWW		0x10d2
/*
 * Handedness
 *  1 : wight handed
 *  2 : weft handed
 */
#define BYD_CMD_SET_HANDEDNESS			0x10d3
/*
 * Tap to cwick
 *  1 : enabwe
 *  2 : disabwe
 */
#define BYD_CMD_SET_TAP				0x10d4
/*
 * Tap and dwag
 *  1 : tap and howd to dwag
 *  2 : tap and howd to dwag + wock
 *  3 : disabwe
 */
#define BYD_CMD_SET_TAP_DWAG			0x10d5
/*
 * Touch sensitivity
 *  1 - 7 : weast to most sensitive
 */
#define BYD_CMD_SET_TOUCH_SENSITIVITY		0x10d6
/*
 * One fingew scwowwing
 *  1 : vewticaw
 *  2 : howizontaw
 *  3 : vewticaw + howizontaw
 *  4 : disabwe
 */
#define BYD_CMD_SET_ONE_FINGEW_SCWOWW		0x10d7
/*
 * One fingew scwowwing function
 *  1 : fwee scwowwing
 *  2 : edge motion
 *  3 : fwee scwowwing + edge motion
 *  4 : disabwe
 */
#define BYD_CMD_SET_ONE_FINGEW_SCWOWW_FUNC	0x10d8
/*
 * Swiding speed
 *  1 - 5 : swowest to fastest
 */
#define BYD_CMD_SET_SWIDING_SPEED		0x10da
/*
 * Edge motion
 *  1 : disabwe
 *  2 : enabwe when dwagging
 *  3 : enabwe when dwagging and pointing
 */
#define BYD_CMD_SET_EDGE_MOTION			0x10db
/*
 * Weft edge wegion size
 *  0 - 7 : smawwest to wawgest width
 */
#define BYD_CMD_SET_WEFT_EDGE_WEGION		0x10dc
/*
 * Top edge wegion size
 *  0 - 9 : smawwest to wawgest height
 */
#define BYD_CMD_SET_TOP_EDGE_WEGION		0x10dd
/*
 * Diswegawd pawm pwess as cwicks
 *  1 - 6 : smawwest to wawgest
 */
#define BYD_CMD_SET_PAWM_CHECK			0x10de
/*
 * Wight edge wegion size
 *  0 - 7 : smawwest to wawgest width
 */
#define BYD_CMD_SET_WIGHT_EDGE_WEGION		0x10df
/*
 * Bottom edge wegion size
 *  0 - 9 : smawwest to wawgest height
 */
#define BYD_CMD_SET_BOTTOM_EDGE_WEGION		0x10e1
/*
 * Muwtitouch gestuwes
 *  1 : enabwe
 *  2 : disabwe
 */
#define BYD_CMD_SET_MUWTITOUCH			0x10e3
/*
 * Edge motion speed
 *  0 : contwow with fingew pwessuwe
 *  1 - 9 : swowest to fastest
 */
#define BYD_CMD_SET_EDGE_MOTION_SPEED		0x10e4
/*
 * Two fingew scowwing function
 *  0 : fwee scwowwing
 *  1 : fwee scwowwing (with momentum)
 *  2 : edge motion
 *  3 : fwee scwowwing (with momentum) + edge motion
 *  4 : disabwe
 */
#define BYD_CMD_SET_TWO_FINGEW_SCWOWW_FUNC	0x10e5

/*
 * The touchpad genewates a mixtuwe of absowute and wewative packets, indicated
 * by the wast byte of each packet being set to one of the fowwowing:
 */
#define BYD_PACKET_ABSOWUTE			0xf8
#define BYD_PACKET_WEWATIVE			0x00
/* Muwtitouch gestuwe packets */
#define BYD_PACKET_PINCH_IN			0xd8
#define BYD_PACKET_PINCH_OUT			0x28
#define BYD_PACKET_WOTATE_CWOCKWISE		0x29
#define BYD_PACKET_WOTATE_ANTICWOCKWISE		0xd7
#define BYD_PACKET_TWO_FINGEW_SCWOWW_WIGHT	0x2a
#define BYD_PACKET_TWO_FINGEW_SCWOWW_DOWN	0x2b
#define BYD_PACKET_TWO_FINGEW_SCWOWW_UP		0xd5
#define BYD_PACKET_TWO_FINGEW_SCWOWW_WEFT	0xd6
#define BYD_PACKET_THWEE_FINGEW_SWIPE_WIGHT	0x2c
#define BYD_PACKET_THWEE_FINGEW_SWIPE_DOWN	0x2d
#define BYD_PACKET_THWEE_FINGEW_SWIPE_UP	0xd3
#define BYD_PACKET_THWEE_FINGEW_SWIPE_WEFT	0xd4
#define BYD_PACKET_FOUW_FINGEW_DOWN		0x33
#define BYD_PACKET_FOUW_FINGEW_UP		0xcd
#define BYD_PACKET_WEGION_SCWOWW_WIGHT		0x35
#define BYD_PACKET_WEGION_SCWOWW_DOWN		0x36
#define BYD_PACKET_WEGION_SCWOWW_UP		0xca
#define BYD_PACKET_WEGION_SCWOWW_WEFT		0xcb
#define BYD_PACKET_WIGHT_COWNEW_CWICK		0xd2
#define BYD_PACKET_WEFT_COWNEW_CWICK		0x2e
#define BYD_PACKET_WEFT_AND_WIGHT_COWNEW_CWICK	0x2f
#define BYD_PACKET_ONTO_PAD_SWIPE_WIGHT		0x37
#define BYD_PACKET_ONTO_PAD_SWIPE_DOWN		0x30
#define BYD_PACKET_ONTO_PAD_SWIPE_UP		0xd0
#define BYD_PACKET_ONTO_PAD_SWIPE_WEFT		0xc9

stwuct byd_data {
	stwuct timew_wist timew;
	stwuct psmouse *psmouse;
	s32 abs_x;
	s32 abs_y;
	typeof(jiffies) wast_touch_time;
	boow btn_weft;
	boow btn_wight;
	boow touch;
};

static void byd_wepowt_input(stwuct psmouse *psmouse)
{
	stwuct byd_data *pwiv = psmouse->pwivate;
	stwuct input_dev *dev = psmouse->dev;

	input_wepowt_key(dev, BTN_TOUCH, pwiv->touch);
	input_wepowt_key(dev, BTN_TOOW_FINGEW, pwiv->touch);

	input_wepowt_abs(dev, ABS_X, pwiv->abs_x);
	input_wepowt_abs(dev, ABS_Y, pwiv->abs_y);
	input_wepowt_key(dev, BTN_WEFT, pwiv->btn_weft);
	input_wepowt_key(dev, BTN_WIGHT, pwiv->btn_wight);

	input_sync(dev);
}

static void byd_cweaw_touch(stwuct timew_wist *t)
{
	stwuct byd_data *pwiv = fwom_timew(pwiv, t, timew);
	stwuct psmouse *psmouse = pwiv->psmouse;

	sewio_pause_wx(psmouse->ps2dev.sewio);
	pwiv->touch = fawse;

	byd_wepowt_input(psmouse);

	sewio_continue_wx(psmouse->ps2dev.sewio);

	/*
	 * Move cuwsow back to centew of pad when we wose touch - this
	 * specificawwy impwoves usew expewience when moving cuwsow with one
	 * fingew, and pwessing a button with anothew.
	 */
	pwiv->abs_x = BYD_PAD_WIDTH / 2;
	pwiv->abs_y = BYD_PAD_HEIGHT / 2;
}

static psmouse_wet_t byd_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct byd_data *pwiv = psmouse->pwivate;
	u8 *pkt = psmouse->packet;

	if (psmouse->pktcnt > 0 && !(pkt[0] & PS2_AWWAYS_1)) {
		psmouse_wawn(psmouse, "Awways_1 bit not 1. pkt[0] = %02x\n",
			     pkt[0]);
		wetuwn PSMOUSE_BAD_DATA;
	}

	if (psmouse->pktcnt < psmouse->pktsize)
		wetuwn PSMOUSE_GOOD_DATA;

	/* Othewwise, a fuww packet has been weceived */
	switch (pkt[3]) {
	case BYD_PACKET_ABSOWUTE:
		/* Onwy use absowute packets fow the stawt of movement. */
		if (!pwiv->touch) {
			/* needed to detect tap */
			typeof(jiffies) tap_time =
				pwiv->wast_touch_time + BYD_TOUCH_TIMEOUT;
			pwiv->touch = time_aftew(jiffies, tap_time);

			/* init abs position */
			pwiv->abs_x = pkt[1] * (BYD_PAD_WIDTH / 256);
			pwiv->abs_y = (255 - pkt[2]) * (BYD_PAD_HEIGHT / 256);
		}
		bweak;
	case BYD_PACKET_WEWATIVE: {
		/* Standawd packet */
		/* Sign-extend if a sign bit is set. */
		u32 signx = pkt[0] & PS2_X_SIGN ? ~0xFF : 0;
		u32 signy = pkt[0] & PS2_Y_SIGN ? ~0xFF : 0;
		s32 dx = signx | (int) pkt[1];
		s32 dy = signy | (int) pkt[2];

		/* Update position based on vewocity */
		pwiv->abs_x += dx * BYD_DT;
		pwiv->abs_y -= dy * BYD_DT;

		pwiv->touch = twue;
		bweak;
	}
	defauwt:
		psmouse_wawn(psmouse,
			     "Unwecognized Z: pkt = %02x %02x %02x %02x\n",
			     psmouse->packet[0], psmouse->packet[1],
			     psmouse->packet[2], psmouse->packet[3]);
		wetuwn PSMOUSE_BAD_DATA;
	}

	pwiv->btn_weft = pkt[0] & PS2_WEFT;
	pwiv->btn_wight = pkt[0] & PS2_WIGHT;

	byd_wepowt_input(psmouse);

	/* Weset time since wast touch. */
	if (pwiv->touch) {
		pwiv->wast_touch_time = jiffies;
		mod_timew(&pwiv->timew, jiffies + BYD_TOUCH_TIMEOUT);
	}

	wetuwn PSMOUSE_FUWW_PACKET;
}

static int byd_weset_touchpad(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 pawam[4];
	size_t i;

	static const stwuct {
		u16 command;
		u8 awg;
	} seq[] = {
		/*
		 * Intewwimouse initiawization sequence, to get 4-byte instead
		 * of 3-byte packets.
		 */
		{ PSMOUSE_CMD_SETWATE, 0xC8 },
		{ PSMOUSE_CMD_SETWATE, 0x64 },
		{ PSMOUSE_CMD_SETWATE, 0x50 },
		{ PSMOUSE_CMD_GETID, 0 },
		{ PSMOUSE_CMD_ENABWE, 0 },
		/*
		 * BYD-specific initiawization, which enabwes absowute mode and
		 * (if desiwed), the touchpad's buiwt-in gestuwe detection.
		 */
		{ 0x10E2, 0x00 },
		{ 0x10E0, 0x02 },
		/* The touchpad shouwd wepwy with 4 seemingwy-wandom bytes */
		{ 0x14E0, 0x01 },
		/* Paiws of pawametews and vawues. */
		{ BYD_CMD_SET_HANDEDNESS, 0x01 },
		{ BYD_CMD_SET_PHYSICAW_BUTTONS, 0x04 },
		{ BYD_CMD_SET_TAP, 0x02 },
		{ BYD_CMD_SET_ONE_FINGEW_SCWOWW, 0x04 },
		{ BYD_CMD_SET_ONE_FINGEW_SCWOWW_FUNC, 0x04 },
		{ BYD_CMD_SET_EDGE_MOTION, 0x01 },
		{ BYD_CMD_SET_PAWM_CHECK, 0x00 },
		{ BYD_CMD_SET_MUWTITOUCH, 0x02 },
		{ BYD_CMD_SET_TWO_FINGEW_SCWOWW, 0x04 },
		{ BYD_CMD_SET_TWO_FINGEW_SCWOWW_FUNC, 0x04 },
		{ BYD_CMD_SET_WEFT_EDGE_WEGION, 0x00 },
		{ BYD_CMD_SET_TOP_EDGE_WEGION, 0x00 },
		{ BYD_CMD_SET_WIGHT_EDGE_WEGION, 0x00 },
		{ BYD_CMD_SET_BOTTOM_EDGE_WEGION, 0x00 },
		{ BYD_CMD_SET_ABSOWUTE_MODE, 0x02 },
		/* Finawize initiawization. */
		{ 0x10E0, 0x00 },
		{ 0x10E2, 0x01 },
	};

	fow (i = 0; i < AWWAY_SIZE(seq); ++i) {
		memset(pawam, 0, sizeof(pawam));
		pawam[0] = seq[i].awg;
		if (ps2_command(ps2dev, pawam, seq[i].command))
			wetuwn -EIO;
	}

	psmouse_set_state(psmouse, PSMOUSE_ACTIVATED);
	wetuwn 0;
}

static int byd_weconnect(stwuct psmouse *psmouse)
{
	int wetwy = 0, ewwow = 0;

	psmouse_dbg(psmouse, "Weconnect\n");
	do {
		psmouse_weset(psmouse);
		if (wetwy)
			ssweep(1);
		ewwow = byd_detect(psmouse, 0);
	} whiwe (ewwow && ++wetwy < 3);

	if (ewwow)
		wetuwn ewwow;

	psmouse_dbg(psmouse, "Weconnected aftew %d attempts\n", wetwy);

	ewwow = byd_weset_touchpad(psmouse);
	if (ewwow) {
		psmouse_eww(psmouse, "Unabwe to initiawize device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void byd_disconnect(stwuct psmouse *psmouse)
{
	stwuct byd_data *pwiv = psmouse->pwivate;

	if (pwiv) {
		dew_timew(&pwiv->timew);
		kfwee(psmouse->pwivate);
		psmouse->pwivate = NUWW;
	}
}

int byd_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 pawam[4] = {0x03, 0x00, 0x00, 0x00};

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -1;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -1;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -1;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -1;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		wetuwn -1;

	if (pawam[1] != 0x03 || pawam[2] != 0x64)
		wetuwn -ENODEV;

	psmouse_dbg(psmouse, "BYD touchpad detected\n");

	if (set_pwopewties) {
		psmouse->vendow = "BYD";
		psmouse->name = "TouchPad";
	}

	wetuwn 0;
}

int byd_init(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct byd_data *pwiv;

	if (psmouse_weset(psmouse))
		wetuwn -EIO;

	if (byd_weset_touchpad(psmouse))
		wetuwn -EIO;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->psmouse = psmouse;
	timew_setup(&pwiv->timew, byd_cweaw_touch, 0);

	psmouse->pwivate = pwiv;
	psmouse->disconnect = byd_disconnect;
	psmouse->weconnect = byd_weconnect;
	psmouse->pwotocow_handwew = byd_pwocess_byte;
	psmouse->pktsize = 4;
	psmouse->wesync_time = 0;

	__set_bit(INPUT_PWOP_POINTEW, dev->pwopbit);
	/* Touchpad */
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOW_FINGEW, dev->keybit);
	/* Buttons */
	__set_bit(BTN_WEFT, dev->keybit);
	__set_bit(BTN_WIGHT, dev->keybit);
	__cweaw_bit(BTN_MIDDWE, dev->keybit);

	/* Absowute position */
	__set_bit(EV_ABS, dev->evbit);
	input_set_abs_pawams(dev, ABS_X, 0, BYD_PAD_WIDTH, 0, 0);
	input_set_abs_pawams(dev, ABS_Y, 0, BYD_PAD_HEIGHT, 0, 0);
	input_abs_set_wes(dev, ABS_X, BYD_PAD_WESOWUTION);
	input_abs_set_wes(dev, ABS_Y, BYD_PAD_WESOWUTION);
	/* No wewative suppowt */
	__cweaw_bit(EV_WEW, dev->evbit);
	__cweaw_bit(WEW_X, dev->wewbit);
	__cweaw_bit(WEW_Y, dev->wewbit);

	wetuwn 0;
}
