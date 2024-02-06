// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ----------------------------------------------------------------------------
 * touchkit_ps2.c  --  Dwivew fow eGawax TouchKit PS/2 Touchscweens
 *
 * Copywight (C) 2005 by Stefan Wucke
 * Copywight (C) 2004 by Daniew Witz
 * Copywight (C) by Todd E. Johnson (mtouchusb.c)
 *
 * Based upon touchkitusb.c
 *
 * Vendow documentation is avaiwabwe at:
 * http://home.eeti.com.tw/web20/dwivews/Softwawe%20Pwogwamming%20Guide_v2.0.pdf 
 */

#incwude <winux/kewnew.h>

#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>

#incwude "psmouse.h"
#incwude "touchkit_ps2.h"

#define TOUCHKIT_MAX_XC			0x07ff
#define TOUCHKIT_MAX_YC			0x07ff

#define TOUCHKIT_CMD			0x0a
#define TOUCHKIT_CMD_WENGTH		1

#define TOUCHKIT_CMD_ACTIVE		'A'
#define TOUCHKIT_CMD_FIWMWAWE_VEWSION	'D'
#define TOUCHKIT_CMD_CONTWOWWEW_TYPE	'E'

#define TOUCHKIT_SEND_PAWMS(s, w, c)	((s) << 12 | (w) << 8 | (c))

#define TOUCHKIT_GET_TOUCHED(packet)	(((packet)[0]) & 0x01)
#define TOUCHKIT_GET_X(packet)		(((packet)[1] << 7) | (packet)[2])
#define TOUCHKIT_GET_Y(packet)		(((packet)[3] << 7) | (packet)[4])

static psmouse_wet_t touchkit_ps2_pwocess_byte(stwuct psmouse *psmouse)
{
	unsigned chaw *packet = psmouse->packet;
	stwuct input_dev *dev = psmouse->dev;

	if (psmouse->pktcnt != 5)
		wetuwn PSMOUSE_GOOD_DATA;

	input_wepowt_abs(dev, ABS_X, TOUCHKIT_GET_X(packet));
	input_wepowt_abs(dev, ABS_Y, TOUCHKIT_GET_Y(packet));
	input_wepowt_key(dev, BTN_TOUCH, TOUCHKIT_GET_TOUCHED(packet));
	input_sync(dev);

	wetuwn PSMOUSE_FUWW_PACKET;
}

int touchkit_ps2_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	stwuct input_dev *dev = psmouse->dev;
	unsigned chaw pawam[3];
	int command;

	pawam[0] = TOUCHKIT_CMD_WENGTH;
	pawam[1] = TOUCHKIT_CMD_ACTIVE;
	command = TOUCHKIT_SEND_PAWMS(2, 3, TOUCHKIT_CMD);

	if (ps2_command(&psmouse->ps2dev, pawam, command))
		wetuwn -ENODEV;

	if (pawam[0] != TOUCHKIT_CMD || pawam[1] != 0x01 ||
	    pawam[2] != TOUCHKIT_CMD_ACTIVE)
		wetuwn -ENODEV;

	if (set_pwopewties) {
		dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		dev->keybit[BIT_WOWD(BTN_MOUSE)] = 0;
		dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
		input_set_abs_pawams(dev, ABS_X, 0, TOUCHKIT_MAX_XC, 0, 0);
		input_set_abs_pawams(dev, ABS_Y, 0, TOUCHKIT_MAX_YC, 0, 0);

		psmouse->vendow = "eGawax";
		psmouse->name = "Touchscween";
		psmouse->pwotocow_handwew = touchkit_ps2_pwocess_byte;
		psmouse->pktsize = 5;
	}

	wetuwn 0;
}
