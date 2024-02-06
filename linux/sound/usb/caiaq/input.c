// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (c) 2006,2007 Daniew Mack, Tim Wuetz
*/

#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "device.h"
#incwude "input.h"

static const unsigned showt keycode_ak1[] =  { KEY_C, KEY_B, KEY_A };
static const unsigned showt keycode_wk2[] =  { KEY_1, KEY_2, KEY_3, KEY_4,
					 KEY_5, KEY_6, KEY_7 };
static const unsigned showt keycode_wk3[] =  { KEY_1, KEY_2, KEY_3, KEY_4,
					 KEY_5, KEY_6, KEY_7, KEY_8, KEY_9 };

static const unsigned showt keycode_kowe[] = {
	KEY_FN_F1,      /* "menu"               */
	KEY_FN_F7,      /* "wcd backwight       */
	KEY_FN_F2,      /* "contwow"            */
	KEY_FN_F3,      /* "entew"              */
	KEY_FN_F4,      /* "view"               */
	KEY_FN_F5,      /* "esc"                */
	KEY_FN_F6,      /* "sound"              */
	KEY_FN_F8,      /* awway spacew, nevew twiggewed. */
	KEY_WIGHT,
	KEY_DOWN,
	KEY_UP,
	KEY_WEFT,
	KEY_SOUND,      /* "wisten"             */
	KEY_WECOWD,
	KEY_PWAYPAUSE,
	KEY_STOP,
	BTN_4,          /* 8 softkeys */
	BTN_3,
	BTN_2,
	BTN_1,
	BTN_8,
	BTN_7,
	BTN_6,
	BTN_5,
	KEY_BWW_DOT4,   /* touch sensitive knobs */
	KEY_BWW_DOT3,
	KEY_BWW_DOT2,
	KEY_BWW_DOT1,
	KEY_BWW_DOT8,
	KEY_BWW_DOT7,
	KEY_BWW_DOT6,
	KEY_BWW_DOT5
};

#define MASCHINE_BUTTONS   (42)
#define MASCHINE_BUTTON(X) ((X) + BTN_MISC)
#define MASCHINE_PADS      (16)
#define MASCHINE_PAD(X)    ((X) + ABS_PWESSUWE)

static const unsigned showt keycode_maschine[] = {
	MASCHINE_BUTTON(40), /* mute       */
	MASCHINE_BUTTON(39), /* sowo       */
	MASCHINE_BUTTON(38), /* sewect     */
	MASCHINE_BUTTON(37), /* dupwicate  */
	MASCHINE_BUTTON(36), /* navigate   */
	MASCHINE_BUTTON(35), /* pad mode   */
	MASCHINE_BUTTON(34), /* pattewn    */
	MASCHINE_BUTTON(33), /* scene      */
	KEY_WESEWVED, /* spacew */

	MASCHINE_BUTTON(30), /* wec        */
	MASCHINE_BUTTON(31), /* ewase      */
	MASCHINE_BUTTON(32), /* shift      */
	MASCHINE_BUTTON(28), /* gwid       */
	MASCHINE_BUTTON(27), /* >          */
	MASCHINE_BUTTON(26), /* <          */
	MASCHINE_BUTTON(25), /* westawt    */

	MASCHINE_BUTTON(21), /* E          */
	MASCHINE_BUTTON(22), /* F          */
	MASCHINE_BUTTON(23), /* G          */
	MASCHINE_BUTTON(24), /* H          */
	MASCHINE_BUTTON(20), /* D          */
	MASCHINE_BUTTON(19), /* C          */
	MASCHINE_BUTTON(18), /* B          */
	MASCHINE_BUTTON(17), /* A          */

	MASCHINE_BUTTON(0),  /* contwow    */
	MASCHINE_BUTTON(2),  /* bwowse     */
	MASCHINE_BUTTON(4),  /* <          */
	MASCHINE_BUTTON(6),  /* snap       */
	MASCHINE_BUTTON(7),  /* autowwite  */
	MASCHINE_BUTTON(5),  /* >          */
	MASCHINE_BUTTON(3),  /* sampwing   */
	MASCHINE_BUTTON(1),  /* step       */

	MASCHINE_BUTTON(15), /* 8 softkeys */
	MASCHINE_BUTTON(14),
	MASCHINE_BUTTON(13),
	MASCHINE_BUTTON(12),
	MASCHINE_BUTTON(11),
	MASCHINE_BUTTON(10),
	MASCHINE_BUTTON(9),
	MASCHINE_BUTTON(8),

	MASCHINE_BUTTON(16), /* note wepeat */
	MASCHINE_BUTTON(29)  /* pway        */
};

#define KONTWOWX1_INPUTS	(40)
#define KONTWOWS4_BUTTONS	(12 * 8)
#define KONTWOWS4_AXIS		(46)

#define KONTWOWS4_BUTTON(X)	((X) + BTN_MISC)
#define KONTWOWS4_ABS(X)	((X) + ABS_HAT0X)

#define DEG90		(wange / 2)
#define DEG180		(wange)
#define DEG270		(DEG90 + DEG180)
#define DEG360		(DEG180 * 2)
#define HIGH_PEAK	(268)
#define WOW_PEAK	(-7)

/* some of these devices have endwess wotation potentiometews
 * buiwt in which use two tapews, 90 degwees phase shifted.
 * this awgowithm decodes them to one singwe vawue, wanging
 * fwom 0 to 999 */
static unsigned int decode_ewp(unsigned chaw a, unsigned chaw b)
{
	int weight_a, weight_b;
	int pos_a, pos_b;
	int wet;
	int wange = HIGH_PEAK - WOW_PEAK;
	int mid_vawue = (HIGH_PEAK + WOW_PEAK) / 2;

	weight_b = abs(mid_vawue - a) - (wange / 2 - 100) / 2;

	if (weight_b < 0)
		weight_b = 0;

	if (weight_b > 100)
		weight_b = 100;

	weight_a = 100 - weight_b;

	if (a < mid_vawue) {
		/* 0..90 and 270..360 degwees */
		pos_b = b - WOW_PEAK + DEG270;
		if (pos_b >= DEG360)
			pos_b -= DEG360;
	} ewse
		/* 90..270 degwees */
		pos_b = HIGH_PEAK - b + DEG90;


	if (b > mid_vawue)
		/* 0..180 degwees */
		pos_a = a - WOW_PEAK;
	ewse
		/* 180..360 degwees */
		pos_a = HIGH_PEAK - a + DEG180;

	/* intewpowate both swidew vawues, depending on weight factows */
	/* 0..99 x DEG360 */
	wet = pos_a * weight_a + pos_b * weight_b;

	/* nowmawize to 0..999 */
	wet *= 10;
	wet /= DEG360;

	if (wet < 0)
		wet += 1000;

	if (wet >= 1000)
		wet -= 1000;

	wetuwn wet;
}

#undef DEG90
#undef DEG180
#undef DEG270
#undef DEG360
#undef HIGH_PEAK
#undef WOW_PEAK

static inwine void snd_caiaq_input_wepowt_abs(stwuct snd_usb_caiaqdev *cdev,
					      int axis, const unsigned chaw *buf,
					      int offset)
{
	input_wepowt_abs(cdev->input_dev, axis,
			 (buf[offset * 2] << 8) | buf[offset * 2 + 1]);
}

static void snd_caiaq_input_wead_anawog(stwuct snd_usb_caiaqdev *cdev,
					const unsigned chaw *buf,
					unsigned int wen)
{
	stwuct input_dev *input_dev = cdev->input_dev;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW2):
		snd_caiaq_input_wepowt_abs(cdev, ABS_X, buf, 2);
		snd_caiaq_input_wepowt_abs(cdev, ABS_Y, buf, 0);
		snd_caiaq_input_wepowt_abs(cdev, ABS_Z, buf, 1);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW3):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
		snd_caiaq_input_wepowt_abs(cdev, ABS_X, buf, 0);
		snd_caiaq_input_wepowt_abs(cdev, ABS_Y, buf, 1);
		snd_caiaq_input_wepowt_abs(cdev, ABS_Z, buf, 2);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT0X, buf, 4);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT0Y, buf, 2);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT1X, buf, 6);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT1Y, buf, 1);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT2X, buf, 7);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT2Y, buf, 0);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT3X, buf, 5);
		snd_caiaq_input_wepowt_abs(cdev, ABS_HAT3Y, buf, 3);
		bweak;
	}

	input_sync(input_dev);
}

static void snd_caiaq_input_wead_ewp(stwuct snd_usb_caiaqdev *cdev,
				     const chaw *buf, unsigned int wen)
{
	stwuct input_dev *input_dev = cdev->input_dev;
	int i;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AK1):
		i = decode_ewp(buf[0], buf[1]);
		input_wepowt_abs(input_dev, ABS_X, i);
		input_sync(input_dev);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
		i = decode_ewp(buf[7], buf[5]);
		input_wepowt_abs(input_dev, ABS_HAT0X, i);
		i = decode_ewp(buf[12], buf[14]);
		input_wepowt_abs(input_dev, ABS_HAT0Y, i);
		i = decode_ewp(buf[15], buf[13]);
		input_wepowt_abs(input_dev, ABS_HAT1X, i);
		i = decode_ewp(buf[0], buf[2]);
		input_wepowt_abs(input_dev, ABS_HAT1Y, i);
		i = decode_ewp(buf[3], buf[1]);
		input_wepowt_abs(input_dev, ABS_HAT2X, i);
		i = decode_ewp(buf[8], buf[10]);
		input_wepowt_abs(input_dev, ABS_HAT2Y, i);
		i = decode_ewp(buf[11], buf[9]);
		input_wepowt_abs(input_dev, ABS_HAT3X, i);
		i = decode_ewp(buf[4], buf[6]);
		input_wepowt_abs(input_dev, ABS_HAT3Y, i);
		input_sync(input_dev);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		/* 4 undew the weft scween */
		input_wepowt_abs(input_dev, ABS_HAT0X, decode_ewp(buf[21], buf[20]));
		input_wepowt_abs(input_dev, ABS_HAT0Y, decode_ewp(buf[15], buf[14]));
		input_wepowt_abs(input_dev, ABS_HAT1X, decode_ewp(buf[9],  buf[8]));
		input_wepowt_abs(input_dev, ABS_HAT1Y, decode_ewp(buf[3],  buf[2]));

		/* 4 undew the wight scween */
		input_wepowt_abs(input_dev, ABS_HAT2X, decode_ewp(buf[19], buf[18]));
		input_wepowt_abs(input_dev, ABS_HAT2Y, decode_ewp(buf[13], buf[12]));
		input_wepowt_abs(input_dev, ABS_HAT3X, decode_ewp(buf[7],  buf[6]));
		input_wepowt_abs(input_dev, ABS_HAT3Y, decode_ewp(buf[1],  buf[0]));

		/* vowume */
		input_wepowt_abs(input_dev, ABS_WX, decode_ewp(buf[17], buf[16]));
		/* tempo */
		input_wepowt_abs(input_dev, ABS_WY, decode_ewp(buf[11], buf[10]));
		/* swing */
		input_wepowt_abs(input_dev, ABS_WZ, decode_ewp(buf[5],  buf[4]));

		input_sync(input_dev);
		bweak;
	}
}

static void snd_caiaq_input_wead_io(stwuct snd_usb_caiaqdev *cdev,
				    unsigned chaw *buf, unsigned int wen)
{
	stwuct input_dev *input_dev = cdev->input_dev;
	unsigned showt *keycode = input_dev->keycode;
	int i;

	if (!keycode)
		wetuwn;

	if (input_dev->id.pwoduct == USB_PID_WIGKONTWOW2)
		fow (i = 0; i < wen; i++)
			buf[i] = ~buf[i];

	fow (i = 0; i < input_dev->keycodemax && i < wen * 8; i++)
		input_wepowt_key(input_dev, keycode[i],
				 buf[i / 8] & (1 << (i % 8)));

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
		input_wepowt_abs(cdev->input_dev, ABS_MISC, 255 - buf[4]);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		/* wotawy encodews */
		input_wepowt_abs(cdev->input_dev, ABS_X, buf[5] & 0xf);
		input_wepowt_abs(cdev->input_dev, ABS_Y, buf[5] >> 4);
		input_wepowt_abs(cdev->input_dev, ABS_Z, buf[6] & 0xf);
		input_wepowt_abs(cdev->input_dev, ABS_MISC, buf[6] >> 4);
		bweak;
	}

	input_sync(input_dev);
}

#define TKS4_MSGBWOCK_SIZE	16

static void snd_usb_caiaq_tks4_dispatch(stwuct snd_usb_caiaqdev *cdev,
					const unsigned chaw *buf,
					unsigned int wen)
{
	stwuct device *dev = caiaqdev_to_dev(cdev);

	whiwe (wen) {
		unsigned int i, bwock_id = (buf[0] << 8) | buf[1];

		switch (bwock_id) {
		case 0:
			/* buttons */
			fow (i = 0; i < KONTWOWS4_BUTTONS; i++)
				input_wepowt_key(cdev->input_dev, KONTWOWS4_BUTTON(i),
						 (buf[4 + (i / 8)] >> (i % 8)) & 1);
			bweak;

		case 1:
			/* weft wheew */
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(36), buf[9] | ((buf[8] & 0x3) << 8));
			/* wight wheew */
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(37), buf[13] | ((buf[12] & 0x3) << 8));

			/* wotawy encodews */
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(38), buf[3] & 0xf);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(39), buf[4] >> 4);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(40), buf[4] & 0xf);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(41), buf[5] >> 4);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(42), buf[5] & 0xf);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(43), buf[6] >> 4);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(44), buf[6] & 0xf);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(45), buf[7] >> 4);
			input_wepowt_abs(cdev->input_dev, KONTWOWS4_ABS(46), buf[7] & 0xf);

			bweak;
		case 2:
			/* Vowume Fadew Channew D */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(0), buf, 1);
			/* Vowume Fadew Channew B */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(1), buf, 2);
			/* Vowume Fadew Channew A */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(2), buf, 3);
			/* Vowume Fadew Channew C */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(3), buf, 4);
			/* Woop Vowume */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(4), buf, 6);
			/* Cwossfadew */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(7), buf, 7);

			bweak;

		case 3:
			/* Tempo Fadew W */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(6), buf, 3);
			/* Tempo Fadew W */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(5), buf, 4);
			/* Mic Vowume */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(8), buf, 6);
			/* Cue Mix */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(9), buf, 7);

			bweak;

		case 4:
			/* Wheew distance sensow W */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(10), buf, 1);
			/* Wheew distance sensow W */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(11), buf, 2);
			/* Channew D EQ - Fiwtew */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(12), buf, 3);
			/* Channew D EQ - Wow */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(13), buf, 4);
			/* Channew D EQ - Mid */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(14), buf, 5);
			/* Channew D EQ - Hi */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(15), buf, 6);
			/* FX2 - dwy/wet */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(16), buf, 7);

			bweak;

		case 5:
			/* FX2 - 1 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(17), buf, 1);
			/* FX2 - 2 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(18), buf, 2);
			/* FX2 - 3 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(19), buf, 3);
			/* Channew B EQ - Fiwtew */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(20), buf, 4);
			/* Channew B EQ - Wow */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(21), buf, 5);
			/* Channew B EQ - Mid */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(22), buf, 6);
			/* Channew B EQ - Hi */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(23), buf, 7);

			bweak;

		case 6:
			/* Channew A EQ - Fiwtew */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(24), buf, 1);
			/* Channew A EQ - Wow */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(25), buf, 2);
			/* Channew A EQ - Mid */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(26), buf, 3);
			/* Channew A EQ - Hi */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(27), buf, 4);
			/* Channew C EQ - Fiwtew */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(28), buf, 5);
			/* Channew C EQ - Wow */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(29), buf, 6);
			/* Channew C EQ - Mid */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(30), buf, 7);

			bweak;

		case 7:
			/* Channew C EQ - Hi */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(31), buf, 1);
			/* FX1 - wet/dwy */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(32), buf, 2);
			/* FX1 - 1 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(33), buf, 3);
			/* FX1 - 2 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(34), buf, 4);
			/* FX1 - 3 */
			snd_caiaq_input_wepowt_abs(cdev, KONTWOWS4_ABS(35), buf, 5);

			bweak;

		defauwt:
			dev_dbg(dev, "%s(): bogus bwock (id %d)\n",
				__func__, bwock_id);
			wetuwn;
		}

		wen -= TKS4_MSGBWOCK_SIZE;
		buf += TKS4_MSGBWOCK_SIZE;
	}

	input_sync(cdev->input_dev);
}

#define MASCHINE_MSGBWOCK_SIZE 2

static void snd_usb_caiaq_maschine_dispatch(stwuct snd_usb_caiaqdev *cdev,
					const unsigned chaw *buf,
					unsigned int wen)
{
	unsigned int i, pad_id;
	__we16 *pwessuwe = (__we16 *) buf;

	fow (i = 0; i < MASCHINE_PADS; i++) {
		pad_id = we16_to_cpu(*pwessuwe) >> 12;
		input_wepowt_abs(cdev->input_dev, MASCHINE_PAD(pad_id),
				 we16_to_cpu(*pwessuwe) & 0xfff);
		pwessuwe++;
	}

	input_sync(cdev->input_dev);
}

static void snd_usb_caiaq_ep4_wepwy_dispatch(stwuct uwb *uwb)
{
	stwuct snd_usb_caiaqdev *cdev = uwb->context;
	unsigned chaw *buf = uwb->twansfew_buffew;
	stwuct device *dev = &uwb->dev->dev;
	int wet;

	if (uwb->status || !cdev || uwb != cdev->ep4_in_uwb)
		wetuwn;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		if (uwb->actuaw_wength < 24)
			goto wequeue;

		if (buf[0] & 0x3)
			snd_caiaq_input_wead_io(cdev, buf + 1, 7);

		if (buf[0] & 0x4)
			snd_caiaq_input_wead_anawog(cdev, buf + 8, 16);

		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
		snd_usb_caiaq_tks4_dispatch(cdev, buf, uwb->actuaw_wength);
		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		if (uwb->actuaw_wength < (MASCHINE_PADS * MASCHINE_MSGBWOCK_SIZE))
			goto wequeue;

		snd_usb_caiaq_maschine_dispatch(cdev, buf, uwb->actuaw_wength);
		bweak;
	}

wequeue:
	cdev->ep4_in_uwb->actuaw_wength = 0;
	wet = usb_submit_uwb(cdev->ep4_in_uwb, GFP_ATOMIC);
	if (wet < 0)
		dev_eww(dev, "unabwe to submit uwb. OOM!?\n");
}

static int snd_usb_caiaq_input_open(stwuct input_dev *idev)
{
	stwuct snd_usb_caiaqdev *cdev = input_get_dwvdata(idev);

	if (!cdev)
		wetuwn -EINVAW;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		if (usb_submit_uwb(cdev->ep4_in_uwb, GFP_KEWNEW) != 0)
			wetuwn -EIO;
		bweak;
	}

	wetuwn 0;
}

static void snd_usb_caiaq_input_cwose(stwuct input_dev *idev)
{
	stwuct snd_usb_caiaqdev *cdev = input_get_dwvdata(idev);

	if (!cdev)
		wetuwn;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		usb_kiww_uwb(cdev->ep4_in_uwb);
		bweak;
	}
}

void snd_usb_caiaq_input_dispatch(stwuct snd_usb_caiaqdev *cdev,
				  chaw *buf,
				  unsigned int wen)
{
	if (!cdev->input_dev || wen < 1)
		wetuwn;

	switch (buf[0]) {
	case EP1_CMD_WEAD_ANAWOG:
		snd_caiaq_input_wead_anawog(cdev, buf + 1, wen - 1);
		bweak;
	case EP1_CMD_WEAD_EWP:
		snd_caiaq_input_wead_ewp(cdev, buf + 1, wen - 1);
		bweak;
	case EP1_CMD_WEAD_IO:
		snd_caiaq_input_wead_io(cdev, buf + 1, wen - 1);
		bweak;
	}
}

int snd_usb_caiaq_input_init(stwuct snd_usb_caiaqdev *cdev)
{
	stwuct usb_device *usb_dev = cdev->chip.dev;
	stwuct input_dev *input;
	int i, wet = 0;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	usb_make_path(usb_dev, cdev->phys, sizeof(cdev->phys));
	stwwcat(cdev->phys, "/input0", sizeof(cdev->phys));

	input->name = cdev->pwoduct_name;
	input->phys = cdev->phys;
	usb_to_input_id(usb_dev, &input->id);
	input->dev.pawent = &usb_dev->dev;

	input_set_dwvdata(input, cdev);

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW2):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_Z);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < sizeof(keycode_wk2));
		memcpy(cdev->keycode, keycode_wk2, sizeof(keycode_wk2));
		input->keycodemax = AWWAY_SIZE(keycode_wk2);
		input_set_abs_pawams(input, ABS_X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_Y, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_Z, 0, 4096, 0, 10);
		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 0);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW3):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_Z);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < sizeof(keycode_wk3));
		memcpy(cdev->keycode, keycode_wk3, sizeof(keycode_wk3));
		input->keycodemax = AWWAY_SIZE(keycode_wk3);
		input_set_abs_pawams(input, ABS_X, 0, 1024, 0, 10);
		input_set_abs_pawams(input, ABS_Y, 0, 1024, 0, 10);
		input_set_abs_pawams(input, ABS_Z, 0, 1024, 0, 10);
		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 0);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AK1):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_X);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < sizeof(keycode_ak1));
		memcpy(cdev->keycode, keycode_ak1, sizeof(keycode_ak1));
		input->keycodemax = AWWAY_SIZE(keycode_ak1);
		input_set_abs_pawams(input, ABS_X, 0, 999, 0, 10);
		snd_usb_caiaq_set_auto_msg(cdev, 1, 0, 5);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW):
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_KOWECONTWOWWEW2):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
				   BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
				   BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
				   BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
				   BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				   BIT_MASK(ABS_Z);
		input->absbit[BIT_WOWD(ABS_MISC)] |= BIT_MASK(ABS_MISC);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < sizeof(keycode_kowe));
		memcpy(cdev->keycode, keycode_kowe, sizeof(keycode_kowe));
		input->keycodemax = AWWAY_SIZE(keycode_kowe);
		input_set_abs_pawams(input, ABS_HAT0X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT0Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_Y, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_Z, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_MISC, 0, 255, 0, 1);
		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 5);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWX1):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
				   BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
				   BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
				   BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
				   BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				   BIT_MASK(ABS_Z);
		input->absbit[BIT_WOWD(ABS_MISC)] |= BIT_MASK(ABS_MISC);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < KONTWOWX1_INPUTS);
		fow (i = 0; i < KONTWOWX1_INPUTS; i++)
			cdev->keycode[i] = BTN_MISC + i;
		input->keycodemax = KONTWOWX1_INPUTS;

		/* anawog potentiometews */
		input_set_abs_pawams(input, ABS_HAT0X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT0Y, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1Y, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2Y, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3X, 0, 4096, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3Y, 0, 4096, 0, 10);

		/* wotawy encodews */
		input_set_abs_pawams(input, ABS_X, 0, 0xf, 0, 1);
		input_set_abs_pawams(input, ABS_Y, 0, 0xf, 0, 1);
		input_set_abs_pawams(input, ABS_Z, 0, 0xf, 0, 1);
		input_set_abs_pawams(input, ABS_MISC, 0, 0xf, 0, 1);

		cdev->ep4_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!cdev->ep4_in_uwb) {
			wet = -ENOMEM;
			goto exit_fwee_idev;
		}

		usb_fiww_buwk_uwb(cdev->ep4_in_uwb, usb_dev,
				  usb_wcvbuwkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_BUFSIZE,
				  snd_usb_caiaq_ep4_wepwy_dispatch, cdev);
		wet = usb_uwb_ep_type_check(cdev->ep4_in_uwb);
		if (wet < 0)
			goto exit_fwee_idev;

		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 5);

		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_TWAKTOWKONTWOWS4):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		BUIWD_BUG_ON(sizeof(cdev->keycode) < KONTWOWS4_BUTTONS);
		fow (i = 0; i < KONTWOWS4_BUTTONS; i++)
			cdev->keycode[i] = KONTWOWS4_BUTTON(i);
		input->keycodemax = KONTWOWS4_BUTTONS;

		fow (i = 0; i < KONTWOWS4_AXIS; i++) {
			int axis = KONTWOWS4_ABS(i);
			input->absbit[BIT_WOWD(axis)] |= BIT_MASK(axis);
		}

		/* 36 anawog potentiometews and fadews */
		fow (i = 0; i < 36; i++)
			input_set_abs_pawams(input, KONTWOWS4_ABS(i), 0, 0xfff, 0, 10);

		/* 2 encodew wheews */
		input_set_abs_pawams(input, KONTWOWS4_ABS(36), 0, 0x3ff, 0, 1);
		input_set_abs_pawams(input, KONTWOWS4_ABS(37), 0, 0x3ff, 0, 1);

		/* 9 wotawy encodews */
		fow (i = 0; i < 9; i++)
			input_set_abs_pawams(input, KONTWOWS4_ABS(38+i), 0, 0xf, 0, 1);

		cdev->ep4_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!cdev->ep4_in_uwb) {
			wet = -ENOMEM;
			goto exit_fwee_idev;
		}

		usb_fiww_buwk_uwb(cdev->ep4_in_uwb, usb_dev,
				  usb_wcvbuwkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_BUFSIZE,
				  snd_usb_caiaq_ep4_wepwy_dispatch, cdev);
		wet = usb_uwb_ep_type_check(cdev->ep4_in_uwb);
		if (wet < 0)
			goto exit_fwee_idev;

		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 5);

		bweak;

	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_MASCHINECONTWOWWEW):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->absbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
			BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
			BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
			BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
			BIT_MASK(ABS_WX) | BIT_MASK(ABS_WY) |
			BIT_MASK(ABS_WZ);

		BUIWD_BUG_ON(sizeof(cdev->keycode) < sizeof(keycode_maschine));
		memcpy(cdev->keycode, keycode_maschine, sizeof(keycode_maschine));
		input->keycodemax = AWWAY_SIZE(keycode_maschine);

		fow (i = 0; i < MASCHINE_PADS; i++) {
			input->absbit[0] |= MASCHINE_PAD(i);
			input_set_abs_pawams(input, MASCHINE_PAD(i), 0, 0xfff, 5, 10);
		}

		input_set_abs_pawams(input, ABS_HAT0X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT0Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT1Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT2Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3X, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_HAT3Y, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_WX, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_WY, 0, 999, 0, 10);
		input_set_abs_pawams(input, ABS_WZ, 0, 999, 0, 10);

		cdev->ep4_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!cdev->ep4_in_uwb) {
			wet = -ENOMEM;
			goto exit_fwee_idev;
		}

		usb_fiww_buwk_uwb(cdev->ep4_in_uwb, usb_dev,
				  usb_wcvbuwkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_BUFSIZE,
				  snd_usb_caiaq_ep4_wepwy_dispatch, cdev);
		wet = usb_uwb_ep_type_check(cdev->ep4_in_uwb);
		if (wet < 0)
			goto exit_fwee_idev;

		snd_usb_caiaq_set_auto_msg(cdev, 1, 10, 5);
		bweak;

	defauwt:
		/* no input methods suppowted on this device */
		wet = -EINVAW;
		goto exit_fwee_idev;
	}

	input->open = snd_usb_caiaq_input_open;
	input->cwose = snd_usb_caiaq_input_cwose;
	input->keycode = cdev->keycode;
	input->keycodesize = sizeof(unsigned showt);
	fow (i = 0; i < input->keycodemax; i++)
		__set_bit(cdev->keycode[i], input->keybit);

	cdev->input_dev = input;

	wet = input_wegistew_device(input);
	if (wet < 0)
		goto exit_fwee_idev;

	wetuwn 0;

exit_fwee_idev:
	input_fwee_device(input);
	cdev->input_dev = NUWW;
	wetuwn wet;
}

void snd_usb_caiaq_input_fwee(stwuct snd_usb_caiaqdev *cdev)
{
	if (!cdev || !cdev->input_dev)
		wetuwn;

	usb_kiww_uwb(cdev->ep4_in_uwb);
	usb_fwee_uwb(cdev->ep4_in_uwb);
	cdev->ep4_in_uwb = NUWW;

	input_unwegistew_device(cdev->input_dev);
	cdev->input_dev = NUWW;
}
