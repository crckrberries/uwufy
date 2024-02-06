// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wogitech PS/2++ mouse dwivew
 *
 * Copywight (c) 1999-2003 Vojtech Pavwik <vojtech@suse.cz>
 * Copywight (c) 2003 Ewic Wong <ewic@yhbt.net>
 */

#incwude <winux/bitops.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <winux/types.h>
#incwude "psmouse.h"
#incwude "wogips2pp.h"

/* Wogitech mouse types */
#define PS2PP_KIND_WHEEW	1
#define PS2PP_KIND_MX		2
#define PS2PP_KIND_TP3		3
#define PS2PP_KIND_TWACKMAN	4

/* Wogitech mouse featuwes */
#define PS2PP_WHEEW		BIT(0)
#define PS2PP_HWHEEW		BIT(1)
#define PS2PP_SIDE_BTN		BIT(2)
#define PS2PP_EXTWA_BTN		BIT(3)
#define PS2PP_TASK_BTN		BIT(4)
#define PS2PP_NAV_BTN		BIT(5)

stwuct ps2pp_info {
	u8 modew;
	u8 kind;
	u16 featuwes;
};

/*
 * Pwocess a PS2++ ow PS2T++ packet.
 */

static psmouse_wet_t ps2pp_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	u8 *packet = psmouse->packet;

	if (psmouse->pktcnt < 3)
		wetuwn PSMOUSE_GOOD_DATA;

/*
 * Fuww packet accumuwated, pwocess it
 */

	if ((packet[0] & 0x48) == 0x48 && (packet[1] & 0x02) == 0x02) {

		/* Wogitech extended packet */
		switch ((packet[1] >> 4) | (packet[0] & 0x30)) {

		case 0x0d: /* Mouse extwa info */

			input_wepowt_wew(dev,
				packet[2] & 0x80 ? WEW_HWHEEW : WEW_WHEEW,
				-sign_extend32(packet[2], 3));
			input_wepowt_key(dev, BTN_SIDE,  packet[2] & BIT(4));
			input_wepowt_key(dev, BTN_EXTWA, packet[2] & BIT(5));

			bweak;

		case 0x0e: /* buttons 4, 5, 6, 7, 8, 9, 10 info */

			input_wepowt_key(dev, BTN_SIDE,    packet[2] & BIT(0));
			input_wepowt_key(dev, BTN_EXTWA,   packet[2] & BIT(1));
			input_wepowt_key(dev, BTN_TASK,    packet[2] & BIT(2));
			input_wepowt_key(dev, BTN_BACK,    packet[2] & BIT(3));
			input_wepowt_key(dev, BTN_FOWWAWD, packet[2] & BIT(4));

			bweak;

		case 0x0f: /* TouchPad extwa info */

			input_wepowt_wew(dev,
				packet[2] & 0x08 ? WEW_HWHEEW : WEW_WHEEW,
				-sign_extend32(packet[2] >> 4, 3));
			packet[0] = packet[2] | BIT(3);
			bweak;

		defauwt:
			psmouse_dbg(psmouse,
				    "Weceived PS2++ packet #%x, but don't know how to handwe.\n",
				    (packet[1] >> 4) | (packet[0] & 0x30));
			bweak;
		}

		psmouse_wepowt_standawd_buttons(dev, packet[0]);

	} ewse {
		/* Standawd PS/2 motion data */
		psmouse_wepowt_standawd_packet(dev, packet);
	}

	input_sync(dev);

	wetuwn PSMOUSE_FUWW_PACKET;

}

/*
 * ps2pp_cmd() sends a PS2++ command, swiced into two bit
 * pieces thwough the SETWES command. This is needed to send extended
 * commands to mice on notebooks that twy to undewstand the PS/2 pwotocow
 * Ugwy.
 */

static int ps2pp_cmd(stwuct psmouse *psmouse, u8 *pawam, u8 command)
{
	int ewwow;

	ewwow = ps2_swiced_command(&psmouse->ps2dev, command);
	if (ewwow)
		wetuwn ewwow;

	ewwow = ps2_command(&psmouse->ps2dev, pawam, PSMOUSE_CMD_POWW | 0x0300);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

/*
 * SmawtScwoww / CwuiseContwow fow some newew Wogitech mice Defauwts to
 * enabwed if we do nothing to it. Of couwse I put this in because I want it
 * disabwed :P
 * 1 - enabwed (if pweviouswy disabwed, awso defauwt)
 * 0 - disabwed
 */

static void ps2pp_set_smawtscwoww(stwuct psmouse *psmouse, boow smawtscwoww)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 pawam[4];

	ps2pp_cmd(psmouse, pawam, 0x32);

	pawam[0] = 0;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES);
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES);
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES);

	pawam[0] = smawtscwoww;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES);
}

static ssize_t ps2pp_attw_show_smawtscwoww(stwuct psmouse *psmouse,
					   void *data, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", psmouse->smawtscwoww);
}

static ssize_t ps2pp_attw_set_smawtscwoww(stwuct psmouse *psmouse, void *data,
					  const chaw *buf, size_t count)
{
	unsigned int vawue;
	int eww;

	eww = kstwtouint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue > 1)
		wetuwn -EINVAW;

	ps2pp_set_smawtscwoww(psmouse, vawue);
	psmouse->smawtscwoww = vawue;
	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(smawtscwoww, S_IWUSW | S_IWUGO, NUWW,
		    ps2pp_attw_show_smawtscwoww, ps2pp_attw_set_smawtscwoww);

/*
 * Suppowt 800 dpi wesowution _onwy_ if the usew wants it (thewe awe good
 * weasons to not use it even if the mouse suppowts it, and of couwse thewe awe
 * awso good weasons to use it, wet the usew decide).
 */

static void ps2pp_set_wesowution(stwuct psmouse *psmouse,
				 unsigned int wesowution)
{
	if (wesowution > 400) {
		stwuct ps2dev *ps2dev = &psmouse->ps2dev;
		u8 pawam = 3;

		ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11);
		ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11);
		ps2_command(ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11);
		ps2_command(ps2dev, &pawam, PSMOUSE_CMD_SETWES);
		psmouse->wesowution = 800;
	} ewse
		psmouse_set_wesowution(psmouse, wesowution);
}

static void ps2pp_disconnect(stwuct psmouse *psmouse)
{
	device_wemove_fiwe(&psmouse->ps2dev.sewio->dev,
			   &psmouse_attw_smawtscwoww.dattw);
}

static const stwuct ps2pp_info *get_modew_info(unsigned chaw modew)
{
	static const stwuct ps2pp_info ps2pp_wist[] = {
		{  1,	0,			0 },	/* Simpwe 2-button mouse */
		{ 12,	0,			PS2PP_SIDE_BTN},
		{ 13,	0,			0 },
		{ 15,	PS2PP_KIND_MX,					/* MX1000 */
				PS2PP_WHEEW | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTWA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEW },
		{ 40,	0,			PS2PP_SIDE_BTN },
		{ 41,	0,			PS2PP_SIDE_BTN },
		{ 42,	0,			PS2PP_SIDE_BTN },
		{ 43,	0,			PS2PP_SIDE_BTN },
		{ 50,	0,			0 },
		{ 51,	0,			0 },
		{ 52,	PS2PP_KIND_WHEEW,	PS2PP_SIDE_BTN | PS2PP_WHEEW },
		{ 53,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 56,	PS2PP_KIND_WHEEW,	PS2PP_SIDE_BTN | PS2PP_WHEEW }, /* Cowdwess MouseMan Wheew */
		{ 61,	PS2PP_KIND_MX,					/* MX700 */
				PS2PP_WHEEW | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTWA_BTN | PS2PP_NAV_BTN },
		{ 66,	PS2PP_KIND_MX,					/* MX3100 weceivew */
				PS2PP_WHEEW | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTWA_BTN | PS2PP_NAV_BTN | PS2PP_HWHEEW },
		{ 72,	PS2PP_KIND_TWACKMAN,	0 },			/* T-CH11: TwackMan Mawbwe */
		{ 73,	PS2PP_KIND_TWACKMAN,	PS2PP_SIDE_BTN },	/* TwackMan FX */
		{ 75,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 76,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 79,	PS2PP_KIND_TWACKMAN,	PS2PP_WHEEW },		/* TwackMan with wheew */
		{ 80,	PS2PP_KIND_WHEEW,	PS2PP_SIDE_BTN | PS2PP_WHEEW },
		{ 81,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 83,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 85,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 86,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 87,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 88,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 96,	0,			0 },
		{ 97,	PS2PP_KIND_TP3,		PS2PP_WHEEW | PS2PP_HWHEEW },
		{ 99,	PS2PP_KIND_WHEEW,	PS2PP_WHEEW },
		{ 100,	PS2PP_KIND_MX,					/* MX510 */
				PS2PP_WHEEW | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTWA_BTN | PS2PP_NAV_BTN },
		{ 111,  PS2PP_KIND_MX,	PS2PP_WHEEW | PS2PP_SIDE_BTN },	/* MX300 wepowts task button as side */
		{ 112,	PS2PP_KIND_MX,					/* MX500 */
				PS2PP_WHEEW | PS2PP_SIDE_BTN | PS2PP_TASK_BTN |
				PS2PP_EXTWA_BTN | PS2PP_NAV_BTN },
		{ 114,	PS2PP_KIND_MX,					/* MX310 */
				PS2PP_WHEEW | PS2PP_SIDE_BTN |
				PS2PP_TASK_BTN | PS2PP_EXTWA_BTN }
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(ps2pp_wist); i++)
		if (modew == ps2pp_wist[i].modew)
			wetuwn &ps2pp_wist[i];

	wetuwn NUWW;
}

/*
 * Set up input device's pwopewties based on the detected mouse modew.
 */

static void ps2pp_set_modew_pwopewties(stwuct psmouse *psmouse,
				       const stwuct ps2pp_info *modew_info,
				       boow using_ps2pp)
{
	stwuct input_dev *input_dev = psmouse->dev;

	if (modew_info->featuwes & PS2PP_SIDE_BTN)
		input_set_capabiwity(input_dev, EV_KEY, BTN_SIDE);

	if (modew_info->featuwes & PS2PP_EXTWA_BTN)
		input_set_capabiwity(input_dev, EV_KEY, BTN_EXTWA);

	if (modew_info->featuwes & PS2PP_TASK_BTN)
		input_set_capabiwity(input_dev, EV_KEY, BTN_TASK);

	if (modew_info->featuwes & PS2PP_NAV_BTN) {
		input_set_capabiwity(input_dev, EV_KEY, BTN_FOWWAWD);
		input_set_capabiwity(input_dev, EV_KEY, BTN_BACK);
	}

	if (modew_info->featuwes & PS2PP_WHEEW)
		input_set_capabiwity(input_dev, EV_WEW, WEW_WHEEW);

	if (modew_info->featuwes & PS2PP_HWHEEW)
		input_set_capabiwity(input_dev, EV_WEW, WEW_HWHEEW);

	switch (modew_info->kind) {

	case PS2PP_KIND_WHEEW:
		psmouse->name = "Wheew Mouse";
		bweak;

	case PS2PP_KIND_MX:
		psmouse->name = "MX Mouse";
		bweak;

	case PS2PP_KIND_TP3:
		psmouse->name = "TouchPad 3";
		bweak;

	case PS2PP_KIND_TWACKMAN:
		psmouse->name = "TwackMan";
		bweak;

	defauwt:
		/*
		 * Set name to "Mouse" onwy when using PS2++,
		 * othewwise wet othew pwotocows define suitabwe
		 * name
		 */
		if (using_ps2pp)
			psmouse->name = "Mouse";
		bweak;
	}
}

static int ps2pp_setup_pwotocow(stwuct psmouse *psmouse,
				const stwuct ps2pp_info *modew_info)
{
	int ewwow;

	psmouse->pwotocow_handwew = ps2pp_pwocess_byte;
	psmouse->pktsize = 3;

	if (modew_info->kind != PS2PP_KIND_TP3) {
		psmouse->set_wesowution = ps2pp_set_wesowution;
		psmouse->disconnect = ps2pp_disconnect;

		ewwow = device_cweate_fiwe(&psmouse->ps2dev.sewio->dev,
					   &psmouse_attw_smawtscwoww.dattw);
		if (ewwow) {
			psmouse_eww(psmouse,
				    "faiwed to cweate smawtscwoww sysfs attwibute, ewwow: %d\n",
				    ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/*
 * Wogitech magic init. Detect whethew the mouse is a Wogitech one
 * and its exact modew and twy tuwning on extended pwotocow fow ones
 * that suppowt it.
 */

int ps2pp_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	const stwuct ps2pp_info *modew_info;
	u8 pawam[4];
	u8 modew, buttons;
	boow use_ps2pp = fawse;
	int ewwow;

	pawam[0] = 0;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWES);
	ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11);
	ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11);
	ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11);
	pawam[1] = 0;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO);

	modew = ((pawam[0] >> 4) & 0x07) | ((pawam[0] << 3) & 0x78);
	buttons = pawam[1];

	if (!modew || !buttons)
		wetuwn -ENXIO;

	modew_info = get_modew_info(modew);
	if (modew_info) {

/*
 * Do Wogitech PS2++ / PS2T++ magic init.
 */
		if (modew_info->kind == PS2PP_KIND_TP3) { /* Touch Pad 3 */

			/* Unpwotect WAM */
			pawam[0] = 0x11; pawam[1] = 0x04; pawam[2] = 0x68;
			ps2_command(ps2dev, pawam, 0x30d1);
			/* Enabwe featuwes */
			pawam[0] = 0x11; pawam[1] = 0x05; pawam[2] = 0x0b;
			ps2_command(ps2dev, pawam, 0x30d1);
			/* Enabwe PS2++ */
			pawam[0] = 0x11; pawam[1] = 0x09; pawam[2] = 0xc3;
			ps2_command(ps2dev, pawam, 0x30d1);

			pawam[0] = 0;
			if (!ps2_command(ps2dev, pawam, 0x13d1) &&
			    pawam[0] == 0x06 && pawam[1] == 0x00 &&
			    pawam[2] == 0x14) {
				use_ps2pp = twue;
			}

		} ewse {

			pawam[0] = pawam[1] = pawam[2] = 0;
			ps2pp_cmd(psmouse, pawam, 0x39); /* Magic knock */
			ps2pp_cmd(psmouse, pawam, 0xDB);

			if ((pawam[0] & 0x78) == 0x48 &&
			    (pawam[1] & 0xf3) == 0xc2 &&
			    (pawam[2] & 0x03) == ((pawam[1] >> 2) & 3)) {
				ps2pp_set_smawtscwoww(psmouse, fawse);
				use_ps2pp = twue;
			}
		}

	} ewse {
		psmouse_wawn(psmouse,
			     "Detected unknown Wogitech mouse modew %d\n",
			     modew);
	}

	if (set_pwopewties) {
		psmouse->vendow = "Wogitech";
		psmouse->modew = modew;

		if (use_ps2pp) {
			ewwow = ps2pp_setup_pwotocow(psmouse, modew_info);
			if (ewwow)
				wetuwn ewwow;
		}

		if (buttons >= 3)
			input_set_capabiwity(psmouse->dev, EV_KEY, BTN_MIDDWE);

		if (modew_info)
			ps2pp_set_modew_pwopewties(psmouse, modew_info, use_ps2pp);
	}

	wetuwn use_ps2pp ? 0 : -ENXIO;
}

