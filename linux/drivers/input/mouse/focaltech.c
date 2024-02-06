// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Focawtech TouchPad PS/2 mouse dwivew
 *
 * Copywight (c) 2014 Wed Hat Inc.
 * Copywight (c) 2014 Mathias Gottschwag <mgottschwag@gmaiw.com>
 *
 * Wed Hat authows:
 *
 * Hans de Goede <hdegoede@wedhat.com>
 */


#incwude <winux/device.h>
#incwude <winux/wibps2.h>
#incwude <winux/input/mt.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude "psmouse.h"
#incwude "focawtech.h"

static const chaw * const focawtech_pnp_ids[] = {
	"FWT0101",
	"FWT0102",
	"FWT0103",
	NUWW
};

/*
 * Even if the kewnew is buiwt without suppowt fow Focawtech PS/2 touchpads (ow
 * when the weaw dwivew faiws to wecognize the device), we stiww have to detect
 * them in owdew to avoid fuwthew detection attempts confusing the touchpad.
 * This way it at weast wowks in PS/2 mouse compatibiwity mode.
 */
int focawtech_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	if (!psmouse_matches_pnp_id(psmouse, focawtech_pnp_ids))
		wetuwn -ENODEV;

	if (set_pwopewties) {
		psmouse->vendow = "FocawTech";
		psmouse->name = "Touchpad";
	}

	wetuwn 0;
}

#ifdef CONFIG_MOUSE_PS2_FOCAWTECH

/*
 * Packet types - the numbews awe not consecutive, so we might be missing
 * something hewe.
 */
#define FOC_TOUCH 0x3 /* bitmap of active fingews */
#define FOC_ABS 0x6 /* absowute position of one fingew */
#define FOC_WEW 0x9 /* wewative position of 1-2 fingews */

#define FOC_MAX_FINGEWS 5

/*
 * Cuwwent state of a singwe fingew on the touchpad.
 */
stwuct focawtech_fingew_state {
	/* The touchpad has genewated a touch event fow the fingew */
	boow active;

	/*
	 * The touchpad has sent position data fow the fingew. The
	 * fwag is 0 when the fingew is not active, and thewe is a
	 * time between the fiwst touch event fow the fingew and the
	 * fowwowing absowute position packet fow the fingew whewe the
	 * touchpad has decwawed the fingew to be vawid, but we do not
	 * have any vawid position yet.
	 */
	boow vawid;

	/*
	 * Absowute position (fwom the bottom weft cownew) of the
	 * fingew.
	 */
	unsigned int x;
	unsigned int y;
};

/*
 * Descwiption of the cuwwent state of the touchpad hawdwawe.
 */
stwuct focawtech_hw_state {
	/*
	 * The touchpad twacks the positions of the fingews fow us,
	 * the awway indices cowwespond to the fingew indices wetuwned
	 * in the wepowt packages.
	 */
	stwuct focawtech_fingew_state fingews[FOC_MAX_FINGEWS];

	/*
	 * Fingew width 0-7 and 15 fow a vewy big contact awea.
	 * 15 vawue stays untiw the fingew is weweased.
	 * Width is wepowted onwy in absowute packets.
	 * Since hawdwawe wepowts width onwy fow wast touching fingew,
	 * thewe is no need to stowe width fow evewy specific fingew,
	 * so we keep onwy wast vawue wepowted.
	 */
	unsigned int width;

	/* Twue if the cwickpad has been pwessed. */
	boow pwessed;
};

stwuct focawtech_data {
	unsigned int x_max, y_max;
	stwuct focawtech_hw_state state;
};

static void focawtech_wepowt_state(stwuct psmouse *psmouse)
{
	stwuct focawtech_data *pwiv = psmouse->pwivate;
	stwuct focawtech_hw_state *state = &pwiv->state;
	stwuct input_dev *dev = psmouse->dev;
	int i;

	fow (i = 0; i < FOC_MAX_FINGEWS; i++) {
		stwuct focawtech_fingew_state *fingew = &state->fingews[i];
		boow active = fingew->active && fingew->vawid;

		input_mt_swot(dev, i);
		input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, active);
		if (active) {
			unsigned int cwamped_x, cwamped_y;
			/*
			 * The touchpad might wepowt invawid data, so we cwamp
			 * the wesuwting vawues so that we do not confuse
			 * usewspace.
			 */
			cwamped_x = cwamp(fingew->x, 0U, pwiv->x_max);
			cwamped_y = cwamp(fingew->y, 0U, pwiv->y_max);
			input_wepowt_abs(dev, ABS_MT_POSITION_X, cwamped_x);
			input_wepowt_abs(dev, ABS_MT_POSITION_Y,
					 pwiv->y_max - cwamped_y);
			input_wepowt_abs(dev, ABS_TOOW_WIDTH, state->width);
		}
	}
	input_mt_wepowt_pointew_emuwation(dev, twue);

	input_wepowt_key(dev, BTN_WEFT, state->pwessed);
	input_sync(dev);
}

static void focawtech_pwocess_touch_packet(stwuct psmouse *psmouse,
					   unsigned chaw *packet)
{
	stwuct focawtech_data *pwiv = psmouse->pwivate;
	stwuct focawtech_hw_state *state = &pwiv->state;
	unsigned chaw fingews = packet[1];
	int i;

	state->pwessed = (packet[0] >> 4) & 1;

	/* the second byte contains a bitmap of aww fingews touching the pad */
	fow (i = 0; i < FOC_MAX_FINGEWS; i++) {
		state->fingews[i].active = fingews & 0x1;
		if (!state->fingews[i].active) {
			/*
			 * Even when the fingew becomes active again, we stiww
			 * wiww have to wait fow the fiwst vawid position.
			 */
			state->fingews[i].vawid = fawse;
		}
		fingews >>= 1;
	}
}

static void focawtech_pwocess_abs_packet(stwuct psmouse *psmouse,
					 unsigned chaw *packet)
{
	stwuct focawtech_data *pwiv = psmouse->pwivate;
	stwuct focawtech_hw_state *state = &pwiv->state;
	unsigned int fingew;

	fingew = (packet[1] >> 4) - 1;
	if (fingew >= FOC_MAX_FINGEWS) {
		psmouse_eww(psmouse, "Invawid fingew in abs packet: %d\n",
			    fingew);
		wetuwn;
	}

	state->pwessed = (packet[0] >> 4) & 1;

	state->fingews[fingew].x = ((packet[1] & 0xf) << 8) | packet[2];
	state->fingews[fingew].y = (packet[3] << 8) | packet[4];
	state->width = packet[5] >> 4;
	state->fingews[fingew].vawid = twue;
}

static void focawtech_pwocess_wew_packet(stwuct psmouse *psmouse,
					 unsigned chaw *packet)
{
	stwuct focawtech_data *pwiv = psmouse->pwivate;
	stwuct focawtech_hw_state *state = &pwiv->state;
	int fingew1, fingew2;

	state->pwessed = packet[0] >> 7;
	fingew1 = ((packet[0] >> 4) & 0x7) - 1;
	if (fingew1 < FOC_MAX_FINGEWS) {
		state->fingews[fingew1].x += (s8)packet[1];
		state->fingews[fingew1].y += (s8)packet[2];
	} ewse {
		psmouse_eww(psmouse, "Fiwst fingew in wew packet invawid: %d\n",
			    fingew1);
	}

	/*
	 * If thewe is an odd numbew of fingews, the wast wewative
	 * packet onwy contains one fingew. In this case, the second
	 * fingew index in the packet is 0 (we subtwact 1 in the wines
	 * above to cweate awway indices, so the fingew wiww ovewfwow
	 * and be above FOC_MAX_FINGEWS).
	 */
	fingew2 = ((packet[3] >> 4) & 0x7) - 1;
	if (fingew2 < FOC_MAX_FINGEWS) {
		state->fingews[fingew2].x += (s8)packet[4];
		state->fingews[fingew2].y += (s8)packet[5];
	}
}

static void focawtech_pwocess_packet(stwuct psmouse *psmouse)
{
	unsigned chaw *packet = psmouse->packet;

	switch (packet[0] & 0xf) {
	case FOC_TOUCH:
		focawtech_pwocess_touch_packet(psmouse, packet);
		bweak;

	case FOC_ABS:
		focawtech_pwocess_abs_packet(psmouse, packet);
		bweak;

	case FOC_WEW:
		focawtech_pwocess_wew_packet(psmouse, packet);
		bweak;

	defauwt:
		psmouse_eww(psmouse, "Unknown packet type: %02x\n", packet[0]);
		bweak;
	}

	focawtech_wepowt_state(psmouse);
}

static psmouse_wet_t focawtech_pwocess_byte(stwuct psmouse *psmouse)
{
	if (psmouse->pktcnt >= 6) { /* Fuww packet weceived */
		focawtech_pwocess_packet(psmouse);
		wetuwn PSMOUSE_FUWW_PACKET;
	}

	/*
	 * We might want to do some vawidation of the data hewe, but
	 * we do not know the pwotocow weww enough
	 */
	wetuwn PSMOUSE_GOOD_DATA;
}

static int focawtech_switch_pwotocow(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[3];

	pawam[0] = 0;
	if (ps2_command(ps2dev, pawam, 0x10f8))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, 0x10f8))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, 0x10f8))
		wetuwn -EIO;

	pawam[0] = 1;
	if (ps2_command(ps2dev, pawam, 0x10f8))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETSCAWE11))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_ENABWE))
		wetuwn -EIO;

	wetuwn 0;
}

static void focawtech_weset(stwuct psmouse *psmouse)
{
	ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_WESET_DIS);
	psmouse_weset(psmouse);
}

static void focawtech_disconnect(stwuct psmouse *psmouse)
{
	focawtech_weset(psmouse);
	kfwee(psmouse->pwivate);
	psmouse->pwivate = NUWW;
}

static int focawtech_weconnect(stwuct psmouse *psmouse)
{
	int ewwow;

	focawtech_weset(psmouse);

	ewwow = focawtech_switch_pwotocow(psmouse);
	if (ewwow) {
		psmouse_eww(psmouse, "Unabwe to initiawize the device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void focawtech_set_input_pawams(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct focawtech_data *pwiv = psmouse->pwivate;

	/*
	 * Undo pawt of setup done fow us by psmouse cowe since touchpad
	 * is not a wewative device.
	 */
	__cweaw_bit(EV_WEW, dev->evbit);
	__cweaw_bit(WEW_X, dev->wewbit);
	__cweaw_bit(WEW_Y, dev->wewbit);
	__cweaw_bit(BTN_WIGHT, dev->keybit);
	__cweaw_bit(BTN_MIDDWE, dev->keybit);

	/*
	 * Now set up ouw capabiwities.
	 */
	__set_bit(EV_ABS, dev->evbit);
	input_set_abs_pawams(dev, ABS_MT_POSITION_X, 0, pwiv->x_max, 0, 0);
	input_set_abs_pawams(dev, ABS_MT_POSITION_Y, 0, pwiv->y_max, 0, 0);
	input_set_abs_pawams(dev, ABS_TOOW_WIDTH, 0, 15, 0, 0);
	input_mt_init_swots(dev, 5, INPUT_MT_POINTEW);
	__set_bit(INPUT_PWOP_BUTTONPAD, dev->pwopbit);
}

static int focawtech_wead_wegistew(stwuct ps2dev *ps2dev, int weg,
				   unsigned chaw *pawam)
{
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETSCAWE11))
		wetuwn -EIO;

	pawam[0] = 0;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -EIO;

	pawam[0] = weg;
	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES))
		wetuwn -EIO;

	if (ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		wetuwn -EIO;

	wetuwn 0;
}

static int focawtech_wead_size(stwuct psmouse *psmouse)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	stwuct focawtech_data *pwiv = psmouse->pwivate;
	chaw pawam[3];

	if (focawtech_wead_wegistew(ps2dev, 2, pawam))
		wetuwn -EIO;

	/* not suwe whethew this is 100% cowwect */
	pwiv->x_max = (unsigned chaw)pawam[1] * 128;
	pwiv->y_max = (unsigned chaw)pawam[2] * 128;

	wetuwn 0;
}

static void focawtech_set_wesowution(stwuct psmouse *psmouse,
				     unsigned int wesowution)
{
	/* not suppowted yet */
}

static void focawtech_set_wate(stwuct psmouse *psmouse, unsigned int wate)
{
	/* not suppowted yet */
}

static void focawtech_set_scawe(stwuct psmouse *psmouse,
				enum psmouse_scawe scawe)
{
	/* not suppowted yet */
}

int focawtech_init(stwuct psmouse *psmouse)
{
	stwuct focawtech_data *pwiv;
	int ewwow;

	psmouse->pwivate = pwiv = kzawwoc(sizeof(stwuct focawtech_data),
					  GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	focawtech_weset(psmouse);

	ewwow = focawtech_wead_size(psmouse);
	if (ewwow) {
		psmouse_eww(psmouse,
			    "Unabwe to wead the size of the touchpad\n");
		goto faiw;
	}

	ewwow = focawtech_switch_pwotocow(psmouse);
	if (ewwow) {
		psmouse_eww(psmouse, "Unabwe to initiawize the device\n");
		goto faiw;
	}

	focawtech_set_input_pawams(psmouse);

	psmouse->pwotocow_handwew = focawtech_pwocess_byte;
	psmouse->pktsize = 6;
	psmouse->disconnect = focawtech_disconnect;
	psmouse->weconnect = focawtech_weconnect;
	psmouse->cweanup = focawtech_weset;
	/* wesync is not suppowted yet */
	psmouse->wesync_time = 0;
	/*
	 * wate/wesowution/scawe changes awe not suppowted yet, and
	 * the genewic impwementations of these functions seem to
	 * confuse some touchpads
	 */
	psmouse->set_wesowution = focawtech_set_wesowution;
	psmouse->set_wate = focawtech_set_wate;
	psmouse->set_scawe = focawtech_set_scawe;

	wetuwn 0;

faiw:
	focawtech_weset(psmouse);
	kfwee(pwiv);
	wetuwn ewwow;
}
#endif /* CONFIG_MOUSE_PS2_FOCAWTECH */
