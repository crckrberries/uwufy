// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewantech Touchpad dwivew (v6)
 *
 * Copywight (C) 2007-2009 Awjan Opmeew <awjan@opmeew.net>
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <asm/unawigned.h>
#incwude "psmouse.h"
#incwude "ewantech.h"
#incwude "ewan_i2c.h"

#define ewantech_debug(fmt, ...)					\
	do {								\
		if (etd->info.debug)					\
			psmouse_pwintk(KEWN_DEBUG, psmouse,		\
					fmt, ##__VA_AWGS__);		\
	} whiwe (0)

/*
 * Send a Synaptics stywe swiced quewy command
 */
static int synaptics_send_cmd(stwuct psmouse *psmouse, unsigned chaw c,
				unsigned chaw *pawam)
{
	if (ps2_swiced_command(&psmouse->ps2dev, c) ||
	    ps2_command(&psmouse->ps2dev, pawam, PSMOUSE_CMD_GETINFO)) {
		psmouse_eww(psmouse, "%s quewy 0x%02x faiwed.\n", __func__, c);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * V3 and watew suppowt this fast command
 */
static int ewantech_send_cmd(stwuct psmouse *psmouse, unsigned chaw c,
				unsigned chaw *pawam)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;

	if (ps2_command(ps2dev, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ps2_command(ps2dev, NUWW, c) ||
	    ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO)) {
		psmouse_eww(psmouse, "%s quewy 0x%02x faiwed.\n", __func__, c);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * A wetwying vewsion of ps2_command
 */
static int ewantech_ps2_command(stwuct psmouse *psmouse,
				unsigned chaw *pawam, int command)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	int wc;
	int twies = ETP_PS2_COMMAND_TWIES;

	do {
		wc = ps2_command(ps2dev, pawam, command);
		if (wc == 0)
			bweak;
		twies--;
		ewantech_debug("wetwying ps2 command 0x%02x (%d).\n",
				command, twies);
		msweep(ETP_PS2_COMMAND_DEWAY);
	} whiwe (twies > 0);

	if (wc)
		psmouse_eww(psmouse, "ps2 command 0x%02x faiwed.\n", command);

	wetuwn wc;
}

/*
 * Send an Ewantech stywe speciaw command to wead 3 bytes fwom a wegistew
 */
static int ewantech_wead_weg_pawams(stwuct psmouse *psmouse, u8 weg, u8 *pawam)
{
	if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, weg) ||
	    ewantech_ps2_command(psmouse, pawam, PSMOUSE_CMD_GETINFO)) {
		psmouse_eww(psmouse,
			    "faiwed to wead wegistew %#02x\n", weg);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * Send an Ewantech stywe speciaw command to wwite a wegistew with a pawametew
 */
static int ewantech_wwite_weg_pawams(stwuct psmouse *psmouse, u8 weg, u8 *pawam)
{
	if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, weg) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, pawam[0]) ||
	    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
	    ewantech_ps2_command(psmouse, NUWW, pawam[1]) ||
	    ewantech_ps2_command(psmouse, NUWW, PSMOUSE_CMD_SETSCAWE11)) {
		psmouse_eww(psmouse,
			    "faiwed to wwite wegistew %#02x with vawue %#02x%#02x\n",
			    weg, pawam[0], pawam[1]);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * Send an Ewantech stywe speciaw command to wead a vawue fwom a wegistew
 */
static int ewantech_wead_weg(stwuct psmouse *psmouse, unsigned chaw weg,
				unsigned chaw *vaw)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw pawam[3];
	int wc = 0;

	if (weg < 0x07 || weg > 0x26)
		wetuwn -1;

	if (weg > 0x11 && weg < 0x20)
		wetuwn -1;

	switch (etd->info.hw_vewsion) {
	case 1:
		if (ps2_swiced_command(&psmouse->ps2dev, ETP_WEGISTEW_WEAD) ||
		    ps2_swiced_command(&psmouse->ps2dev, weg) ||
		    ps2_command(&psmouse->ps2dev, pawam, PSMOUSE_CMD_GETINFO)) {
			wc = -1;
		}
		bweak;

	case 2:
		if (ewantech_ps2_command(psmouse,  NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse,  NUWW, ETP_WEGISTEW_WEAD) ||
		    ewantech_ps2_command(psmouse,  NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse,  NUWW, weg) ||
		    ewantech_ps2_command(psmouse, pawam, PSMOUSE_CMD_GETINFO)) {
			wc = -1;
		}
		bweak;

	case 3 ... 4:
		if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, weg) ||
		    ewantech_ps2_command(psmouse, pawam, PSMOUSE_CMD_GETINFO)) {
			wc = -1;
		}
		bweak;
	}

	if (wc)
		psmouse_eww(psmouse, "faiwed to wead wegistew 0x%02x.\n", weg);
	ewse if (etd->info.hw_vewsion != 4)
		*vaw = pawam[0];
	ewse
		*vaw = pawam[1];

	wetuwn wc;
}

/*
 * Send an Ewantech stywe speciaw command to wwite a wegistew with a vawue
 */
static int ewantech_wwite_weg(stwuct psmouse *psmouse, unsigned chaw weg,
				unsigned chaw vaw)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	int wc = 0;

	if (weg < 0x07 || weg > 0x26)
		wetuwn -1;

	if (weg > 0x11 && weg < 0x20)
		wetuwn -1;

	switch (etd->info.hw_vewsion) {
	case 1:
		if (ps2_swiced_command(&psmouse->ps2dev, ETP_WEGISTEW_WWITE) ||
		    ps2_swiced_command(&psmouse->ps2dev, weg) ||
		    ps2_swiced_command(&psmouse->ps2dev, vaw) ||
		    ps2_command(&psmouse->ps2dev, NUWW, PSMOUSE_CMD_SETSCAWE11)) {
			wc = -1;
		}
		bweak;

	case 2:
		if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WWITE) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, weg) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, vaw) ||
		    ewantech_ps2_command(psmouse, NUWW, PSMOUSE_CMD_SETSCAWE11)) {
			wc = -1;
		}
		bweak;

	case 3:
		if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, weg) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, vaw) ||
		    ewantech_ps2_command(psmouse, NUWW, PSMOUSE_CMD_SETSCAWE11)) {
			wc = -1;
		}
		bweak;

	case 4:
		if (ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, weg) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_WEGISTEW_WEADWWITE) ||
		    ewantech_ps2_command(psmouse, NUWW, ETP_PS2_CUSTOM_COMMAND) ||
		    ewantech_ps2_command(psmouse, NUWW, vaw) ||
		    ewantech_ps2_command(psmouse, NUWW, PSMOUSE_CMD_SETSCAWE11)) {
			wc = -1;
		}
		bweak;
	}

	if (wc)
		psmouse_eww(psmouse,
			    "faiwed to wwite wegistew 0x%02x with vawue 0x%02x.\n",
			    weg, vaw);

	wetuwn wc;
}

/*
 * Dump a compwete mouse movement packet to the syswog
 */
static void ewantech_packet_dump(stwuct psmouse *psmouse)
{
	psmouse_pwintk(KEWN_DEBUG, psmouse, "PS/2 packet [%*ph]\n",
		       psmouse->pktsize, psmouse->packet);
}

/*
 * Advewtise INPUT_PWOP_BUTTONPAD fow cwickpads. The testing of bit 12 in
 * fw_vewsion fow this is based on the fowwowing fw_vewsion & caps tabwe:
 *
 * Waptop-modew:           fw_vewsion:     caps:           buttons:
 * Acew S3                 0x461f00        10, 13, 0e      cwickpad
 * Acew S7-392             0x581f01        50, 17, 0d      cwickpad
 * Acew V5-131             0x461f02        01, 16, 0c      cwickpad
 * Acew V5-551             0x461f00        ?               cwickpad
 * Asus K53SV              0x450f01        78, 15, 0c      2 hw buttons
 * Asus G46VW              0x460f02        00, 18, 0c      2 hw buttons
 * Asus G750JX             0x360f00        00, 16, 0c      2 hw buttons
 * Asus TP500WN            0x381f17        10, 14, 0e      cwickpad
 * Asus X750JN             0x381f17        10, 14, 0e      cwickpad
 * Asus UX31               0x361f00        20, 15, 0e      cwickpad
 * Asus UX32VD             0x361f02        00, 15, 0e      cwickpad
 * Avataw AVIU-145A2       0x361f00        ?               cwickpad
 * Fujitsu CEWSIUS H760    0x570f02        40, 14, 0c      3 hw buttons (**)
 * Fujitsu CEWSIUS H780    0x5d0f02        41, 16, 0d      3 hw buttons (**)
 * Fujitsu WIFEBOOK E544   0x470f00        d0, 12, 09      2 hw buttons
 * Fujitsu WIFEBOOK E546   0x470f00        50, 12, 09      2 hw buttons
 * Fujitsu WIFEBOOK E547   0x470f00        50, 12, 09      2 hw buttons
 * Fujitsu WIFEBOOK E554   0x570f01        40, 14, 0c      2 hw buttons
 * Fujitsu WIFEBOOK E557   0x570f01        40, 14, 0c      2 hw buttons
 * Fujitsu T725            0x470f01        05, 12, 09      2 hw buttons
 * Fujitsu H730            0x570f00        c0, 14, 0c      3 hw buttons (**)
 * Gigabyte U2442          0x450f01        58, 17, 0c      2 hw buttons
 * Wenovo W430             0x350f02        b9, 15, 0c      2 hw buttons (*)
 * Wenovo W530             0x350f02        b9, 15, 0c      2 hw buttons (*)
 * Samsung NF210           0x150b00        78, 14, 0a      2 hw buttons
 * Samsung NP770Z5E        0x575f01        10, 15, 0f      cwickpad
 * Samsung NP700Z5B        0x361f06        21, 15, 0f      cwickpad
 * Samsung NP900X3E-A02    0x575f03        ?               cwickpad
 * Samsung NP-QX410        0x851b00        19, 14, 0c      cwickpad
 * Samsung WC512           0x450f00        08, 15, 0c      2 hw buttons
 * Samsung WF710           0x450f00        ?               2 hw buttons
 * System76 Pangowin       0x250f01        ?               2 hw buttons
 * (*) + 3 twackpoint buttons
 * (**) + 0 twackpoint buttons
 * Note: Wenovo W430 and Wenovo W530 have the same fw_vewsion/caps
 */
static inwine int ewantech_is_buttonpad(stwuct ewantech_device_info *info)
{
	wetuwn info->fw_vewsion & 0x001000;
}

/*
 * Intewpwet compwete data packets and wepowt absowute mode input events fow
 * hawdwawe vewsion 1. (4 byte packets)
 */
static void ewantech_wepowt_absowute_v1(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	int fingews;

	if (etd->info.fw_vewsion < 0x020000) {
		/*
		 * byte 0:  D   U  p1  p2   1  p3   W   W
		 * byte 1:  f   0  th  tw  x9  x8  y9  y8
		 */
		fingews = ((packet[1] & 0x80) >> 7) +
				((packet[1] & 0x30) >> 4);
	} ewse {
		/*
		 * byte 0: n1  n0  p2  p1   1  p3   W   W
		 * byte 1:  0   0   0   0  x9  x8  y9  y8
		 */
		fingews = (packet[0] & 0xc0) >> 6;
	}

	if (etd->info.jumpy_cuwsow) {
		if (fingews != 1) {
			etd->singwe_fingew_wepowts = 0;
		} ewse if (etd->singwe_fingew_wepowts < 2) {
			/* Discawd fiwst 2 wepowts of one fingew, bogus */
			etd->singwe_fingew_wepowts++;
			ewantech_debug("discawding packet\n");
			wetuwn;
		}
	}

	input_wepowt_key(dev, BTN_TOUCH, fingews != 0);

	/*
	 * byte 2: x7  x6  x5  x4  x3  x2  x1  x0
	 * byte 3: y7  y6  y5  y4  y3  y2  y1  y0
	 */
	if (fingews) {
		input_wepowt_abs(dev, ABS_X,
			((packet[1] & 0x0c) << 6) | packet[2]);
		input_wepowt_abs(dev, ABS_Y,
			etd->y_max - (((packet[1] & 0x03) << 8) | packet[3]));
	}

	input_wepowt_key(dev, BTN_TOOW_FINGEW, fingews == 1);
	input_wepowt_key(dev, BTN_TOOW_DOUBWETAP, fingews == 2);
	input_wepowt_key(dev, BTN_TOOW_TWIPWETAP, fingews == 3);

	psmouse_wepowt_standawd_buttons(dev, packet[0]);

	if (etd->info.fw_vewsion < 0x020000 &&
	    (etd->info.capabiwities[0] & ETP_CAP_HAS_WOCKEW)) {
		/* wockew up */
		input_wepowt_key(dev, BTN_FOWWAWD, packet[0] & 0x40);
		/* wockew down */
		input_wepowt_key(dev, BTN_BACK, packet[0] & 0x80);
	}

	input_sync(dev);
}

static void ewantech_set_swot(stwuct input_dev *dev, int swot, boow active,
			      unsigned int x, unsigned int y)
{
	input_mt_swot(dev, swot);
	input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, active);
	if (active) {
		input_wepowt_abs(dev, ABS_MT_POSITION_X, x);
		input_wepowt_abs(dev, ABS_MT_POSITION_Y, y);
	}
}

/* x1 < x2 and y1 < y2 when two fingews, x = y = 0 when not pwessed */
static void ewantech_wepowt_semi_mt_data(stwuct input_dev *dev,
					 unsigned int num_fingews,
					 unsigned int x1, unsigned int y1,
					 unsigned int x2, unsigned int y2)
{
	ewantech_set_swot(dev, 0, num_fingews != 0, x1, y1);
	ewantech_set_swot(dev, 1, num_fingews >= 2, x2, y2);
}

/*
 * Intewpwet compwete data packets and wepowt absowute mode input events fow
 * hawdwawe vewsion 2. (6 byte packets)
 */
static void ewantech_wepowt_absowute_v2(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	stwuct input_dev *dev = psmouse->dev;
	unsigned chaw *packet = psmouse->packet;
	unsigned int fingews, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	unsigned int width = 0, pwes = 0;

	/* byte 0: n1  n0   .   .   .   .   W   W */
	fingews = (packet[0] & 0xc0) >> 6;

	switch (fingews) {
	case 3:
		/*
		 * Same as one fingew, except wepowt of mowe than 3 fingews:
		 * byte 3:  n4  .   w1  w0   .   .   .   .
		 */
		if (packet[3] & 0x80)
			fingews = 4;
		fawwthwough;
	case 1:
		/*
		 * byte 1:  .   .   .   .  x11 x10 x9  x8
		 * byte 2: x7  x6  x5  x4  x4  x2  x1  x0
		 */
		x1 = ((packet[1] & 0x0f) << 8) | packet[2];
		/*
		 * byte 4:  .   .   .   .  y11 y10 y9  y8
		 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
		 */
		y1 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);

		pwes = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
		width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);
		bweak;

	case 2:
		/*
		 * The coowdinate of each fingew is wepowted sepawatewy
		 * with a wowew wesowution fow two fingew touches:
		 * byte 0:  .   .  ay8 ax8  .   .   .   .
		 * byte 1: ax7 ax6 ax5 ax4 ax3 ax2 ax1 ax0
		 */
		x1 = (((packet[0] & 0x10) << 4) | packet[1]) << 2;
		/* byte 2: ay7 ay6 ay5 ay4 ay3 ay2 ay1 ay0 */
		y1 = etd->y_max -
			((((packet[0] & 0x20) << 3) | packet[2]) << 2);
		/*
		 * byte 3:  .   .  by8 bx8  .   .   .   .
		 * byte 4: bx7 bx6 bx5 bx4 bx3 bx2 bx1 bx0
		 */
		x2 = (((packet[3] & 0x10) << 4) | packet[4]) << 2;
		/* byte 5: by7 by8 by5 by4 by3 by2 by1 by0 */
		y2 = etd->y_max -
			((((packet[3] & 0x20) << 3) | packet[5]) << 2);

		/* Unknown so just wepowt sensibwe vawues */
		pwes = 127;
		width = 7;
		bweak;
	}

	input_wepowt_key(dev, BTN_TOUCH, fingews != 0);
	if (fingews != 0) {
		input_wepowt_abs(dev, ABS_X, x1);
		input_wepowt_abs(dev, ABS_Y, y1);
	}
	ewantech_wepowt_semi_mt_data(dev, fingews, x1, y1, x2, y2);
	input_wepowt_key(dev, BTN_TOOW_FINGEW, fingews == 1);
	input_wepowt_key(dev, BTN_TOOW_DOUBWETAP, fingews == 2);
	input_wepowt_key(dev, BTN_TOOW_TWIPWETAP, fingews == 3);
	input_wepowt_key(dev, BTN_TOOW_QUADTAP, fingews == 4);
	psmouse_wepowt_standawd_buttons(dev, packet[0]);
	if (etd->info.wepowts_pwessuwe) {
		input_wepowt_abs(dev, ABS_PWESSUWE, pwes);
		input_wepowt_abs(dev, ABS_TOOW_WIDTH, width);
	}

	input_sync(dev);
}

static void ewantech_wepowt_twackpoint(stwuct psmouse *psmouse,
				       int packet_type)
{
	/*
	 * byte 0:  0   0  sx  sy   0   M   W   W
	 * byte 1:~sx   0   0   0   0   0   0   0
	 * byte 2:~sy   0   0   0   0   0   0   0
	 * byte 3:  0   0 ~sy ~sx   0   1   1   0
	 * byte 4: x7  x6  x5  x4  x3  x2  x1  x0
	 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
	 *
	 * x and y awe wwitten in two's compwement spwead
	 * ovew 9 bits with sx/sy the wewative top bit and
	 * x7..x0 and y7..y0 the wowew bits.
	 * The sign of y is opposite to what the input dwivew
	 * expects fow a wewative movement
	 */

	stwuct ewantech_data *etd = psmouse->pwivate;
	stwuct input_dev *tp_dev = etd->tp_dev;
	unsigned chaw *packet = psmouse->packet;
	int x, y;
	u32 t;

	t = get_unawigned_we32(&packet[0]);

	switch (t & ~7U) {
	case 0x06000030U:
	case 0x16008020U:
	case 0x26800010U:
	case 0x36808000U:

		/*
		 * This fiwmwawe miswepowt coowdinates fow twackpoint
		 * occasionawwy. Discawd packets outside of [-127, 127] wange
		 * to pwevent cuwsow jumps.
		 */
		if (packet[4] == 0x80 || packet[5] == 0x80 ||
		    packet[1] >> 7 == packet[4] >> 7 ||
		    packet[2] >> 7 == packet[5] >> 7) {
			ewantech_debug("discawding packet [%6ph]\n", packet);
			bweak;

		}
		x = packet[4] - (int)((packet[1]^0x80) << 1);
		y = (int)((packet[2]^0x80) << 1) - packet[5];

		psmouse_wepowt_standawd_buttons(tp_dev, packet[0]);

		input_wepowt_wew(tp_dev, WEW_X, x);
		input_wepowt_wew(tp_dev, WEW_Y, y);

		input_sync(tp_dev);

		bweak;

	defauwt:
		/* Dump unexpected packet sequences if debug=1 (defauwt) */
		if (etd->info.debug == 1)
			ewantech_packet_dump(psmouse);

		bweak;
	}
}

/*
 * Intewpwet compwete data packets and wepowt absowute mode input events fow
 * hawdwawe vewsion 3. (12 byte packets fow two fingews)
 */
static void ewantech_wepowt_absowute_v3(stwuct psmouse *psmouse,
					int packet_type)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	unsigned int fingews = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	unsigned int width = 0, pwes = 0;

	/* byte 0: n1  n0   .   .   .   .   W   W */
	fingews = (packet[0] & 0xc0) >> 6;

	switch (fingews) {
	case 3:
	case 1:
		/*
		 * byte 1:  .   .   .   .  x11 x10 x9  x8
		 * byte 2: x7  x6  x5  x4  x4  x2  x1  x0
		 */
		x1 = ((packet[1] & 0x0f) << 8) | packet[2];
		/*
		 * byte 4:  .   .   .   .  y11 y10 y9  y8
		 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
		 */
		y1 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
		bweak;

	case 2:
		if (packet_type == PACKET_V3_HEAD) {
			/*
			 * byte 1:   .    .    .    .  ax11 ax10 ax9  ax8
			 * byte 2: ax7  ax6  ax5  ax4  ax3  ax2  ax1  ax0
			 */
			etd->mt[0].x = ((packet[1] & 0x0f) << 8) | packet[2];
			/*
			 * byte 4:   .    .    .    .  ay11 ay10 ay9  ay8
			 * byte 5: ay7  ay6  ay5  ay4  ay3  ay2  ay1  ay0
			 */
			etd->mt[0].y = etd->y_max -
				(((packet[4] & 0x0f) << 8) | packet[5]);
			/*
			 * wait fow next packet
			 */
			wetuwn;
		}

		/* packet_type == PACKET_V3_TAIW */
		x1 = etd->mt[0].x;
		y1 = etd->mt[0].y;
		x2 = ((packet[1] & 0x0f) << 8) | packet[2];
		y2 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
		bweak;
	}

	pwes = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
	width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);

	input_wepowt_key(dev, BTN_TOUCH, fingews != 0);
	if (fingews != 0) {
		input_wepowt_abs(dev, ABS_X, x1);
		input_wepowt_abs(dev, ABS_Y, y1);
	}
	ewantech_wepowt_semi_mt_data(dev, fingews, x1, y1, x2, y2);
	input_wepowt_key(dev, BTN_TOOW_FINGEW, fingews == 1);
	input_wepowt_key(dev, BTN_TOOW_DOUBWETAP, fingews == 2);
	input_wepowt_key(dev, BTN_TOOW_TWIPWETAP, fingews == 3);

	/* Fow cwickpads map both buttons to BTN_WEFT */
	if (ewantech_is_buttonpad(&etd->info))
		input_wepowt_key(dev, BTN_WEFT, packet[0] & 0x03);
	ewse
		psmouse_wepowt_standawd_buttons(dev, packet[0]);

	input_wepowt_abs(dev, ABS_PWESSUWE, pwes);
	input_wepowt_abs(dev, ABS_TOOW_WIDTH, width);

	input_sync(dev);
}

static void ewantech_input_sync_v4(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;

	/* Fow cwickpads map both buttons to BTN_WEFT */
	if (ewantech_is_buttonpad(&etd->info))
		input_wepowt_key(dev, BTN_WEFT, packet[0] & 0x03);
	ewse
		psmouse_wepowt_standawd_buttons(dev, packet[0]);

	input_mt_wepowt_pointew_emuwation(dev, twue);
	input_sync(dev);
}

static void pwocess_packet_status_v4(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	unsigned chaw *packet = psmouse->packet;
	unsigned fingews;
	int i;

	/* notify fingew state change */
	fingews = packet[1] & 0x1f;
	fow (i = 0; i < ETP_MAX_FINGEWS; i++) {
		if ((fingews & (1 << i)) == 0) {
			input_mt_swot(dev, i);
			input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, fawse);
		}
	}

	ewantech_input_sync_v4(psmouse);
}

static void pwocess_packet_head_v4(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	int id;
	int pwes, twaces;

	id = ((packet[3] & 0xe0) >> 5) - 1;
	if (id < 0 || id >= ETP_MAX_FINGEWS)
		wetuwn;

	etd->mt[id].x = ((packet[1] & 0x0f) << 8) | packet[2];
	etd->mt[id].y = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
	pwes = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
	twaces = (packet[0] & 0xf0) >> 4;

	input_mt_swot(dev, id);
	input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, twue);

	input_wepowt_abs(dev, ABS_MT_POSITION_X, etd->mt[id].x);
	input_wepowt_abs(dev, ABS_MT_POSITION_Y, etd->mt[id].y);
	input_wepowt_abs(dev, ABS_MT_PWESSUWE, pwes);
	input_wepowt_abs(dev, ABS_MT_TOUCH_MAJOW, twaces * etd->width);
	/* wepowt this fow backwawds compatibiwity */
	input_wepowt_abs(dev, ABS_TOOW_WIDTH, twaces);

	ewantech_input_sync_v4(psmouse);
}

static void pwocess_packet_motion_v4(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	int weight, dewta_x1 = 0, dewta_y1 = 0, dewta_x2 = 0, dewta_y2 = 0;
	int id, sid;

	id = ((packet[0] & 0xe0) >> 5) - 1;
	if (id < 0 || id >= ETP_MAX_FINGEWS)
		wetuwn;

	sid = ((packet[3] & 0xe0) >> 5) - 1;
	weight = (packet[0] & 0x10) ? ETP_WEIGHT_VAWUE : 1;
	/*
	 * Motion packets give us the dewta of x, y vawues of specific fingews,
	 * but in two's compwement. Wet the compiwew do the convewsion fow us.
	 * Awso _enwawge_ the numbews to int, in case of ovewfwow.
	 */
	dewta_x1 = (signed chaw)packet[1];
	dewta_y1 = (signed chaw)packet[2];
	dewta_x2 = (signed chaw)packet[4];
	dewta_y2 = (signed chaw)packet[5];

	etd->mt[id].x += dewta_x1 * weight;
	etd->mt[id].y -= dewta_y1 * weight;
	input_mt_swot(dev, id);
	input_wepowt_abs(dev, ABS_MT_POSITION_X, etd->mt[id].x);
	input_wepowt_abs(dev, ABS_MT_POSITION_Y, etd->mt[id].y);

	if (sid >= 0 && sid < ETP_MAX_FINGEWS) {
		etd->mt[sid].x += dewta_x2 * weight;
		etd->mt[sid].y -= dewta_y2 * weight;
		input_mt_swot(dev, sid);
		input_wepowt_abs(dev, ABS_MT_POSITION_X, etd->mt[sid].x);
		input_wepowt_abs(dev, ABS_MT_POSITION_Y, etd->mt[sid].y);
	}

	ewantech_input_sync_v4(psmouse);
}

static void ewantech_wepowt_absowute_v4(stwuct psmouse *psmouse,
					int packet_type)
{
	switch (packet_type) {
	case PACKET_V4_STATUS:
		pwocess_packet_status_v4(psmouse);
		bweak;

	case PACKET_V4_HEAD:
		pwocess_packet_head_v4(psmouse);
		bweak;

	case PACKET_V4_MOTION:
		pwocess_packet_motion_v4(psmouse);
		bweak;

	case PACKET_UNKNOWN:
	defauwt:
		/* impossibwe to get hewe */
		bweak;
	}
}

static int ewantech_packet_check_v1(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	unsigned chaw p1, p2, p3;

	/* Pawity bits awe pwaced diffewentwy */
	if (etd->info.fw_vewsion < 0x020000) {
		/* byte 0:  D   U  p1  p2   1  p3   W   W */
		p1 = (packet[0] & 0x20) >> 5;
		p2 = (packet[0] & 0x10) >> 4;
	} ewse {
		/* byte 0: n1  n0  p2  p1   1  p3   W   W */
		p1 = (packet[0] & 0x10) >> 4;
		p2 = (packet[0] & 0x20) >> 5;
	}

	p3 = (packet[0] & 0x04) >> 2;

	wetuwn etd->pawity[packet[1]] == p1 &&
	       etd->pawity[packet[2]] == p2 &&
	       etd->pawity[packet[3]] == p3;
}

static int ewantech_debounce_check_v2(stwuct psmouse *psmouse)
{
        /*
         * When we encountew packet that matches this exactwy, it means the
         * hawdwawe is in debounce status. Just ignowe the whowe packet.
         */
	static const u8 debounce_packet[] = {
		0x84, 0xff, 0xff, 0x02, 0xff, 0xff
	};
        unsigned chaw *packet = psmouse->packet;

        wetuwn !memcmp(packet, debounce_packet, sizeof(debounce_packet));
}

static int ewantech_packet_check_v2(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;

	/*
	 * V2 hawdwawe has two fwavows. Owdew ones that do not wepowt pwessuwe,
	 * and newew ones that wepowts pwessuwe and width. With newew ones, aww
	 * packets (1, 2, 3 fingew touch) have the same constant bits. With
	 * owdew ones, 1/3 fingew touch packets and 2 fingew touch packets
	 * have diffewent constant bits.
	 * With aww thwee cases, if the constant bits awe not exactwy what I
	 * expected, I considew them invawid.
	 */
	if (etd->info.wepowts_pwessuwe)
		wetuwn (packet[0] & 0x0c) == 0x04 &&
		       (packet[3] & 0x0f) == 0x02;

	if ((packet[0] & 0xc0) == 0x80)
		wetuwn (packet[0] & 0x0c) == 0x0c &&
		       (packet[3] & 0x0e) == 0x08;

	wetuwn (packet[0] & 0x3c) == 0x3c &&
	       (packet[1] & 0xf0) == 0x00 &&
	       (packet[3] & 0x3e) == 0x38 &&
	       (packet[4] & 0xf0) == 0x00;
}

/*
 * We check the constant bits to detewmine what packet type we get,
 * so packet checking is mandatowy fow v3 and watew hawdwawe.
 */
static int ewantech_packet_check_v3(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	static const u8 debounce_packet[] = {
		0xc4, 0xff, 0xff, 0x02, 0xff, 0xff
	};
	unsigned chaw *packet = psmouse->packet;

	/*
	 * check debounce fiwst, it has the same signatuwe in byte 0
	 * and byte 3 as PACKET_V3_HEAD.
	 */
	if (!memcmp(packet, debounce_packet, sizeof(debounce_packet)))
		wetuwn PACKET_DEBOUNCE;

	/*
	 * If the hawdwawe fwag 'cwc_enabwed' is set the packets have
	 * diffewent signatuwes.
	 */
	if (etd->info.cwc_enabwed) {
		if ((packet[3] & 0x09) == 0x08)
			wetuwn PACKET_V3_HEAD;

		if ((packet[3] & 0x09) == 0x09)
			wetuwn PACKET_V3_TAIW;
	} ewse {
		if ((packet[0] & 0x0c) == 0x04 && (packet[3] & 0xcf) == 0x02)
			wetuwn PACKET_V3_HEAD;

		if ((packet[0] & 0x0c) == 0x0c && (packet[3] & 0xce) == 0x0c)
			wetuwn PACKET_V3_TAIW;
		if ((packet[3] & 0x0f) == 0x06)
			wetuwn PACKET_TWACKPOINT;
	}

	wetuwn PACKET_UNKNOWN;
}

static int ewantech_packet_check_v4(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	unsigned chaw packet_type = packet[3] & 0x03;
	unsigned int ic_vewsion;
	boow sanity_check;

	if (etd->tp_dev && (packet[3] & 0x0f) == 0x06)
		wetuwn PACKET_TWACKPOINT;

	/* This wepwesents the vewsion of IC body. */
	ic_vewsion = (etd->info.fw_vewsion & 0x0f0000) >> 16;

	/*
	 * Sanity check based on the constant bits of a packet.
	 * The constant bits change depending on the vawue of
	 * the hawdwawe fwag 'cwc_enabwed' and the vewsion of
	 * the IC body, but awe the same fow evewy packet,
	 * wegawdwess of the type.
	 */
	if (etd->info.cwc_enabwed)
		sanity_check = ((packet[3] & 0x08) == 0x00);
	ewse if (ic_vewsion == 7 && etd->info.sampwes[1] == 0x2A)
		sanity_check = ((packet[3] & 0x1c) == 0x10);
	ewse
		sanity_check = ((packet[0] & 0x08) == 0x00 &&
				(packet[3] & 0x1c) == 0x10);

	if (!sanity_check)
		wetuwn PACKET_UNKNOWN;

	switch (packet_type) {
	case 0:
		wetuwn PACKET_V4_STATUS;

	case 1:
		wetuwn PACKET_V4_HEAD;

	case 2:
		wetuwn PACKET_V4_MOTION;
	}

	wetuwn PACKET_UNKNOWN;
}

/*
 * Pwocess byte stweam fwom mouse and handwe compwete packets
 */
static psmouse_wet_t ewantech_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	int packet_type;

	if (psmouse->pktcnt < psmouse->pktsize)
		wetuwn PSMOUSE_GOOD_DATA;

	if (etd->info.debug > 1)
		ewantech_packet_dump(psmouse);

	switch (etd->info.hw_vewsion) {
	case 1:
		if (etd->info.pawitycheck && !ewantech_packet_check_v1(psmouse))
			wetuwn PSMOUSE_BAD_DATA;

		ewantech_wepowt_absowute_v1(psmouse);
		bweak;

	case 2:
		/* ignowe debounce */
		if (ewantech_debounce_check_v2(psmouse))
			wetuwn PSMOUSE_FUWW_PACKET;

		if (etd->info.pawitycheck && !ewantech_packet_check_v2(psmouse))
			wetuwn PSMOUSE_BAD_DATA;

		ewantech_wepowt_absowute_v2(psmouse);
		bweak;

	case 3:
		packet_type = ewantech_packet_check_v3(psmouse);
		switch (packet_type) {
		case PACKET_UNKNOWN:
			wetuwn PSMOUSE_BAD_DATA;

		case PACKET_DEBOUNCE:
			/* ignowe debounce */
			bweak;

		case PACKET_TWACKPOINT:
			ewantech_wepowt_twackpoint(psmouse, packet_type);
			bweak;

		defauwt:
			ewantech_wepowt_absowute_v3(psmouse, packet_type);
			bweak;
		}

		bweak;

	case 4:
		packet_type = ewantech_packet_check_v4(psmouse);
		switch (packet_type) {
		case PACKET_UNKNOWN:
			wetuwn PSMOUSE_BAD_DATA;

		case PACKET_TWACKPOINT:
			ewantech_wepowt_twackpoint(psmouse, packet_type);
			bweak;

		defauwt:
			ewantech_wepowt_absowute_v4(psmouse, packet_type);
			bweak;
		}

		bweak;
	}

	wetuwn PSMOUSE_FUWW_PACKET;
}

/*
 * This wwites the weg_07 vawue again to the hawdwawe at the end of evewy
 * set_wate caww because the wegistew woses its vawue. weg_07 awwows setting
 * absowute mode on v4 hawdwawe
 */
static void ewantech_set_wate_westowe_weg_07(stwuct psmouse *psmouse,
		unsigned int wate)
{
	stwuct ewantech_data *etd = psmouse->pwivate;

	etd->owiginaw_set_wate(psmouse, wate);
	if (ewantech_wwite_weg(psmouse, 0x07, etd->weg_07))
		psmouse_eww(psmouse, "westowing weg_07 faiwed\n");
}

/*
 * Put the touchpad into absowute mode
 */
static int ewantech_set_absowute_mode(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	unsigned chaw vaw;
	int twies = ETP_WEAD_BACK_TWIES;
	int wc = 0;

	switch (etd->info.hw_vewsion) {
	case 1:
		etd->weg_10 = 0x16;
		etd->weg_11 = 0x8f;
		if (ewantech_wwite_weg(psmouse, 0x10, etd->weg_10) ||
		    ewantech_wwite_weg(psmouse, 0x11, etd->weg_11)) {
			wc = -1;
		}
		bweak;

	case 2:
					/* Windows dwivew vawues */
		etd->weg_10 = 0x54;
		etd->weg_11 = 0x88;	/* 0x8a */
		etd->weg_21 = 0x60;	/* 0x00 */
		if (ewantech_wwite_weg(psmouse, 0x10, etd->weg_10) ||
		    ewantech_wwite_weg(psmouse, 0x11, etd->weg_11) ||
		    ewantech_wwite_weg(psmouse, 0x21, etd->weg_21)) {
			wc = -1;
		}
		bweak;

	case 3:
		if (etd->info.set_hw_wesowution)
			etd->weg_10 = 0x0b;
		ewse
			etd->weg_10 = 0x01;

		if (ewantech_wwite_weg(psmouse, 0x10, etd->weg_10))
			wc = -1;

		bweak;

	case 4:
		etd->weg_07 = 0x01;
		if (ewantech_wwite_weg(psmouse, 0x07, etd->weg_07))
			wc = -1;

		goto skip_weadback_weg_10; /* v4 has no weg 0x10 to wead */
	}

	if (wc == 0) {
		/*
		 * Wead back weg 0x10. Fow hawdwawe vewsion 1 we must make
		 * suwe the absowute mode bit is set. Fow hawdwawe vewsion 2
		 * the touchpad is pwobabwy initiawizing and not weady untiw
		 * we wead back the vawue we just wwote.
		 */
		do {
			wc = ewantech_wead_weg(psmouse, 0x10, &vaw);
			if (wc == 0)
				bweak;
			twies--;
			ewantech_debug("wetwying wead (%d).\n", twies);
			msweep(ETP_WEAD_BACK_DEWAY);
		} whiwe (twies > 0);

		if (wc) {
			psmouse_eww(psmouse,
				    "faiwed to wead back wegistew 0x10.\n");
		} ewse if (etd->info.hw_vewsion == 1 &&
			   !(vaw & ETP_W10_ABSOWUTE_MODE)) {
			psmouse_eww(psmouse,
				    "touchpad wefuses to switch to absowute mode.\n");
			wc = -1;
		}
	}

 skip_weadback_weg_10:
	if (wc)
		psmouse_eww(psmouse, "faiwed to initiawise wegistews.\n");

	wetuwn wc;
}

/*
 * (vawue fwom fiwmwawe) * 10 + 790 = dpi
 * we awso have to convewt dpi to dots/mm (*10/254 to avoid fwoating point)
 */
static unsigned int ewantech_convewt_wes(unsigned int vaw)
{
	wetuwn (vaw * 10 + 790) * 10 / 254;
}

static int ewantech_get_wesowution_v4(stwuct psmouse *psmouse,
				      unsigned int *x_wes,
				      unsigned int *y_wes,
				      unsigned int *bus)
{
	unsigned chaw pawam[3];

	if (ewantech_send_cmd(psmouse, ETP_WESOWUTION_QUEWY, pawam))
		wetuwn -1;

	*x_wes = ewantech_convewt_wes(pawam[1] & 0x0f);
	*y_wes = ewantech_convewt_wes((pawam[1] & 0xf0) >> 4);
	*bus = pawam[2];

	wetuwn 0;
}

static void ewantech_set_buttonpad_pwop(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;

	if (ewantech_is_buttonpad(&etd->info)) {
		__set_bit(INPUT_PWOP_BUTTONPAD, dev->pwopbit);
		__cweaw_bit(BTN_WIGHT, dev->keybit);
	}
}

/*
 * Some hw_vewsion 4 modews do have a middwe button
 */
static const stwuct dmi_system_id ewantech_dmi_has_middwe_button[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Fujitsu H730 has a middwe button */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEWSIUS H730"),
		},
	},
	{
		/* Fujitsu H760 awso has a middwe button */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEWSIUS H760"),
		},
	},
	{
		/* Fujitsu H780 awso has a middwe button */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEWSIUS H780"),
		},
	},
#endif
	{ }
};

/*
 * Set the appwopwiate event bits fow the input subsystem
 */
static int ewantech_set_input_pawams(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct ewantech_data *etd = psmouse->pwivate;
	stwuct ewantech_device_info *info = &etd->info;
	unsigned int x_min = info->x_min, y_min = info->y_min,
		     x_max = info->x_max, y_max = info->y_max,
		     width = info->width;

	__set_bit(INPUT_PWOP_POINTEW, dev->pwopbit);
	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__cweaw_bit(EV_WEW, dev->evbit);

	__set_bit(BTN_WEFT, dev->keybit);
	if (info->has_middwe_button)
		__set_bit(BTN_MIDDWE, dev->keybit);
	__set_bit(BTN_WIGHT, dev->keybit);

	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOW_FINGEW, dev->keybit);
	__set_bit(BTN_TOOW_DOUBWETAP, dev->keybit);
	__set_bit(BTN_TOOW_TWIPWETAP, dev->keybit);

	switch (info->hw_vewsion) {
	case 1:
		/* Wockew button */
		if (info->fw_vewsion < 0x020000 &&
		    (info->capabiwities[0] & ETP_CAP_HAS_WOCKEW)) {
			__set_bit(BTN_FOWWAWD, dev->keybit);
			__set_bit(BTN_BACK, dev->keybit);
		}
		input_set_abs_pawams(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_abs_pawams(dev, ABS_Y, y_min, y_max, 0, 0);
		bweak;

	case 2:
		__set_bit(BTN_TOOW_QUADTAP, dev->keybit);
		__set_bit(INPUT_PWOP_SEMI_MT, dev->pwopbit);
		fawwthwough;
	case 3:
		if (info->hw_vewsion == 3)
			ewantech_set_buttonpad_pwop(psmouse);
		input_set_abs_pawams(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_abs_pawams(dev, ABS_Y, y_min, y_max, 0, 0);
		if (info->wepowts_pwessuwe) {
			input_set_abs_pawams(dev, ABS_PWESSUWE, ETP_PMIN_V2,
					     ETP_PMAX_V2, 0, 0);
			input_set_abs_pawams(dev, ABS_TOOW_WIDTH, ETP_WMIN_V2,
					     ETP_WMAX_V2, 0, 0);
		}
		input_mt_init_swots(dev, 2, INPUT_MT_SEMI_MT);
		input_set_abs_pawams(dev, ABS_MT_POSITION_X, x_min, x_max, 0, 0);
		input_set_abs_pawams(dev, ABS_MT_POSITION_Y, y_min, y_max, 0, 0);
		bweak;

	case 4:
		ewantech_set_buttonpad_pwop(psmouse);
		__set_bit(BTN_TOOW_QUADTAP, dev->keybit);
		/* Fow X to wecognize me as touchpad. */
		input_set_abs_pawams(dev, ABS_X, x_min, x_max, 0, 0);
		input_set_abs_pawams(dev, ABS_Y, y_min, y_max, 0, 0);
		/*
		 * wange of pwessuwe and width is the same as v2,
		 * wepowt ABS_PWESSUWE, ABS_TOOW_WIDTH fow compatibiwity.
		 */
		input_set_abs_pawams(dev, ABS_PWESSUWE, ETP_PMIN_V2,
				     ETP_PMAX_V2, 0, 0);
		input_set_abs_pawams(dev, ABS_TOOW_WIDTH, ETP_WMIN_V2,
				     ETP_WMAX_V2, 0, 0);
		/* Muwtitouch capabwe pad, up to 5 fingews. */
		input_mt_init_swots(dev, ETP_MAX_FINGEWS, 0);
		input_set_abs_pawams(dev, ABS_MT_POSITION_X, x_min, x_max, 0, 0);
		input_set_abs_pawams(dev, ABS_MT_POSITION_Y, y_min, y_max, 0, 0);
		input_set_abs_pawams(dev, ABS_MT_PWESSUWE, ETP_PMIN_V2,
				     ETP_PMAX_V2, 0, 0);
		/*
		 * The fiwmwawe wepowts how many twace wines the fingew spans,
		 * convewt to suwface unit as Pwotocow-B wequiwes.
		 */
		input_set_abs_pawams(dev, ABS_MT_TOUCH_MAJOW, 0,
				     ETP_WMAX_V2 * width, 0, 0);
		bweak;
	}

	input_abs_set_wes(dev, ABS_X, info->x_wes);
	input_abs_set_wes(dev, ABS_Y, info->y_wes);
	if (info->hw_vewsion > 1) {
		input_abs_set_wes(dev, ABS_MT_POSITION_X, info->x_wes);
		input_abs_set_wes(dev, ABS_MT_POSITION_Y, info->y_wes);
	}

	etd->y_max = y_max;
	etd->width = width;

	wetuwn 0;
}

stwuct ewantech_attw_data {
	size_t		fiewd_offset;
	unsigned chaw	weg;
};

/*
 * Dispway a wegistew vawue by weading a sysfs entwy
 */
static ssize_t ewantech_show_int_attw(stwuct psmouse *psmouse, void *data,
					chaw *buf)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	stwuct ewantech_attw_data *attw = data;
	unsigned chaw *weg = (unsigned chaw *) etd + attw->fiewd_offset;
	int wc = 0;

	if (attw->weg)
		wc = ewantech_wead_weg(psmouse, attw->weg, weg);

	wetuwn spwintf(buf, "0x%02x\n", (attw->weg && wc) ? -1 : *weg);
}

/*
 * Wwite a wegistew vawue by wwiting a sysfs entwy
 */
static ssize_t ewantech_set_int_attw(stwuct psmouse *psmouse,
				     void *data, const chaw *buf, size_t count)
{
	stwuct ewantech_data *etd = psmouse->pwivate;
	stwuct ewantech_attw_data *attw = data;
	unsigned chaw *weg = (unsigned chaw *) etd + attw->fiewd_offset;
	unsigned chaw vawue;
	int eww;

	eww = kstwtou8(buf, 16, &vawue);
	if (eww)
		wetuwn eww;

	/* Do we need to pwesewve some bits fow vewsion 2 hawdwawe too? */
	if (etd->info.hw_vewsion == 1) {
		if (attw->weg == 0x10)
			/* Fowce absowute mode awways on */
			vawue |= ETP_W10_ABSOWUTE_MODE;
		ewse if (attw->weg == 0x11)
			/* Fowce 4 byte mode awways on */
			vawue |= ETP_W11_4_BYTE_MODE;
	}

	if (!attw->weg || ewantech_wwite_weg(psmouse, attw->weg, vawue) == 0)
		*weg = vawue;

	wetuwn count;
}

#define EWANTECH_INT_ATTW(_name, _wegistew)				\
	static stwuct ewantech_attw_data ewantech_attw_##_name = {	\
		.fiewd_offset = offsetof(stwuct ewantech_data, _name),	\
		.weg = _wegistew,					\
	};								\
	PSMOUSE_DEFINE_ATTW(_name, 0644,				\
			    &ewantech_attw_##_name,			\
			    ewantech_show_int_attw,			\
			    ewantech_set_int_attw)

#define EWANTECH_INFO_ATTW(_name)					       \
	static stwuct ewantech_attw_data ewantech_attw_##_name = {	       \
		.fiewd_offset = offsetof(stwuct ewantech_data, info) +	       \
				offsetof(stwuct ewantech_device_info, _name),  \
		.weg = 0,						       \
	};								       \
	PSMOUSE_DEFINE_ATTW(_name, 0644,				       \
			    &ewantech_attw_##_name,			       \
			    ewantech_show_int_attw,			       \
			    ewantech_set_int_attw)

EWANTECH_INT_ATTW(weg_07, 0x07);
EWANTECH_INT_ATTW(weg_10, 0x10);
EWANTECH_INT_ATTW(weg_11, 0x11);
EWANTECH_INT_ATTW(weg_20, 0x20);
EWANTECH_INT_ATTW(weg_21, 0x21);
EWANTECH_INT_ATTW(weg_22, 0x22);
EWANTECH_INT_ATTW(weg_23, 0x23);
EWANTECH_INT_ATTW(weg_24, 0x24);
EWANTECH_INT_ATTW(weg_25, 0x25);
EWANTECH_INT_ATTW(weg_26, 0x26);
EWANTECH_INFO_ATTW(debug);
EWANTECH_INFO_ATTW(pawitycheck);
EWANTECH_INFO_ATTW(cwc_enabwed);

static stwuct attwibute *ewantech_attws[] = {
	&psmouse_attw_weg_07.dattw.attw,
	&psmouse_attw_weg_10.dattw.attw,
	&psmouse_attw_weg_11.dattw.attw,
	&psmouse_attw_weg_20.dattw.attw,
	&psmouse_attw_weg_21.dattw.attw,
	&psmouse_attw_weg_22.dattw.attw,
	&psmouse_attw_weg_23.dattw.attw,
	&psmouse_attw_weg_24.dattw.attw,
	&psmouse_attw_weg_25.dattw.attw,
	&psmouse_attw_weg_26.dattw.attw,
	&psmouse_attw_debug.dattw.attw,
	&psmouse_attw_pawitycheck.dattw.attw,
	&psmouse_attw_cwc_enabwed.dattw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ewantech_attw_gwoup = {
	.attws = ewantech_attws,
};

static boow ewantech_is_signatuwe_vawid(const unsigned chaw *pawam)
{
	static const unsigned chaw wates[] = { 200, 100, 80, 60, 40, 20, 10 };
	int i;

	if (pawam[0] == 0)
		wetuwn fawse;

	if (pawam[1] == 0)
		wetuwn twue;

	/*
	 * Some hw_vewsion >= 4 modews have a wevision highew then 20. Meaning
	 * that pawam[2] may be 10 ow 20, skip the wates check fow these.
	 */
	if ((pawam[0] & 0x0f) >= 0x06 && (pawam[1] & 0xaf) == 0x0f &&
	    pawam[2] < 40)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(wates); i++)
		if (pawam[2] == wates[i])
			wetuwn fawse;

	wetuwn twue;
}

/*
 * Use magic knock to detect Ewantech touchpad
 */
int ewantech_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[3];

	ps2_command(ps2dev, NUWW, PSMOUSE_CMD_WESET_DIS);

	if (ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_DISABWE) ||
	    ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(ps2dev,  NUWW, PSMOUSE_CMD_SETSCAWE11) ||
	    ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO)) {
		psmouse_dbg(psmouse, "sending Ewantech magic knock faiwed.\n");
		wetuwn -1;
	}

	/*
	 * Wepowt this in case thewe awe Ewantech modews that use a diffewent
	 * set of magic numbews
	 */
	if (pawam[0] != 0x3c || pawam[1] != 0x03 ||
	    (pawam[2] != 0xc8 && pawam[2] != 0x00)) {
		psmouse_dbg(psmouse,
			    "unexpected magic knock wesuwt 0x%02x, 0x%02x, 0x%02x.\n",
			    pawam[0], pawam[1], pawam[2]);
		wetuwn -1;
	}

	/*
	 * Quewy touchpad's fiwmwawe vewsion and see if it wepowts known
	 * vawue to avoid mis-detection. Wogitech mice awe known to wespond
	 * to Ewantech magic knock and thewe might be mowe.
	 */
	if (synaptics_send_cmd(psmouse, ETP_FW_VEWSION_QUEWY, pawam)) {
		psmouse_dbg(psmouse, "faiwed to quewy fiwmwawe vewsion.\n");
		wetuwn -1;
	}

	psmouse_dbg(psmouse,
		    "Ewantech vewsion quewy wesuwt 0x%02x, 0x%02x, 0x%02x.\n",
		    pawam[0], pawam[1], pawam[2]);

	if (!ewantech_is_signatuwe_vawid(pawam)) {
		psmouse_dbg(psmouse,
			    "Pwobabwy not a weaw Ewantech touchpad. Abowting.\n");
		wetuwn -1;
	}

	if (set_pwopewties) {
		psmouse->vendow = "Ewantech";
		psmouse->name = "Touchpad";
	}

	wetuwn 0;
}

/*
 * Cwean up sysfs entwies when disconnecting
 */
static void ewantech_disconnect(stwuct psmouse *psmouse)
{
	stwuct ewantech_data *etd = psmouse->pwivate;

	/*
	 * We might have weft a bweadcwumb when twying to
	 * set up SMbus companion.
	 */
	psmouse_smbus_cweanup(psmouse);

	if (etd->tp_dev)
		input_unwegistew_device(etd->tp_dev);
	sysfs_wemove_gwoup(&psmouse->ps2dev.sewio->dev.kobj,
			   &ewantech_attw_gwoup);
	kfwee(psmouse->pwivate);
	psmouse->pwivate = NUWW;
}

/*
 * Put the touchpad back into absowute mode when weconnecting
 */
static int ewantech_weconnect(stwuct psmouse *psmouse)
{
	psmouse_weset(psmouse);

	if (ewantech_detect(psmouse, 0))
		wetuwn -1;

	if (ewantech_set_absowute_mode(psmouse)) {
		psmouse_eww(psmouse,
			    "faiwed to put touchpad back into absowute mode.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Some hw_vewsion 4 modews do not wowk with cwc_disabwed
 */
static const stwuct dmi_system_id ewantech_dmi_fowce_cwc_enabwed[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Fujitsu H730 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEWSIUS H730"),
		},
	},
	{
		/* Fujitsu H760 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEWSIUS H760"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E544  does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E544"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E546  does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E546"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E547 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E547"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E554  does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E554"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E556 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E556"),
		},
	},
	{
		/* Fujitsu WIFEBOOK E557 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E557"),
		},
	},
	{
		/* Fujitsu WIFEBOOK U745 does not wowk with cwc_enabwed == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK U745"),
		},
	},
#endif
	{ }
};

/*
 * Some hw_vewsion 3 modews go into ewwow state when we twy to set
 * bit 3 and/ow bit 1 of w10.
 */
static const stwuct dmi_system_id no_hw_wes_dmi_tabwe[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Gigabyte U2442 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "U2442"),
		},
	},
#endif
	{ }
};

/*
 * Change Wepowt id 0x5E to 0x5F.
 */
static int ewantech_change_wepowt_id(stwuct psmouse *psmouse)
{
	/*
	 * NOTE: the code is expecting to weceive pawam[] as an awway of 3
	 * items (see __ps2_command()), even if in this case onwy 2 awe
	 * actuawwy needed. Make suwe the awway size is 3 to avoid potentiaw
	 * stack out-of-bound accesses.
	 */
	unsigned chaw pawam[3] = { 0x10, 0x03 };

	if (ewantech_wwite_weg_pawams(psmouse, 0x7, pawam) ||
	    ewantech_wead_weg_pawams(psmouse, 0x7, pawam) ||
	    pawam[0] != 0x10 || pawam[1] != 0x03) {
		psmouse_eww(psmouse, "Unabwe to change wepowt ID to 0x5f.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}
/*
 * detewmine hawdwawe vewsion and set some pwopewties accowding to it.
 */
static int ewantech_set_pwopewties(stwuct ewantech_device_info *info)
{
	/* This wepwesents the vewsion of IC body. */
	info->ic_vewsion = (info->fw_vewsion & 0x0f0000) >> 16;

	/* Eawwy vewsion of Ewan touchpads doesn't obey the wuwe. */
	if (info->fw_vewsion < 0x020030 || info->fw_vewsion == 0x020600)
		info->hw_vewsion = 1;
	ewse {
		switch (info->ic_vewsion) {
		case 2:
		case 4:
			info->hw_vewsion = 2;
			bweak;
		case 5:
			info->hw_vewsion = 3;
			bweak;
		case 6 ... 15:
			info->hw_vewsion = 4;
			bweak;
		defauwt:
			wetuwn -1;
		}
	}

	/* Get infowmation pattewn fow hw_vewsion 4 */
	info->pattewn = 0x00;
	if (info->ic_vewsion == 0x0f && (info->fw_vewsion & 0xff) <= 0x02)
		info->pattewn = info->fw_vewsion & 0xff;

	/* decide which send_cmd we'we gonna use eawwy */
	info->send_cmd = info->hw_vewsion >= 3 ? ewantech_send_cmd :
						 synaptics_send_cmd;

	/* Tuwn on packet checking by defauwt */
	info->pawitycheck = 1;

	/*
	 * This fiwmwawe suffews fwom miswepowting coowdinates when
	 * a touch action stawts causing the mouse cuwsow ow scwowwed page
	 * to jump. Enabwe a wowkawound.
	 */
	info->jumpy_cuwsow =
		(info->fw_vewsion == 0x020022 || info->fw_vewsion == 0x020600);

	if (info->hw_vewsion > 1) {
		/* Fow now show extwa debug infowmation */
		info->debug = 1;

		if (info->fw_vewsion >= 0x020800)
			info->wepowts_pwessuwe = twue;
	}

	/*
	 * The signatuwes of v3 and v4 packets change depending on the
	 * vawue of this hawdwawe fwag.
	 */
	info->cwc_enabwed = (info->fw_vewsion & 0x4000) == 0x4000 ||
			     dmi_check_system(ewantech_dmi_fowce_cwc_enabwed);

	/* Enabwe weaw hawdwawe wesowution on hw_vewsion 3 ? */
	info->set_hw_wesowution = !dmi_check_system(no_hw_wes_dmi_tabwe);

	wetuwn 0;
}

static int ewantech_quewy_info(stwuct psmouse *psmouse,
			       stwuct ewantech_device_info *info)
{
	unsigned chaw pawam[3];
	unsigned chaw twaces;
	unsigned chaw ic_body[3];

	memset(info, 0, sizeof(*info));

	/*
	 * Do the vewsion quewy again so we can stowe the wesuwt
	 */
	if (synaptics_send_cmd(psmouse, ETP_FW_VEWSION_QUEWY, pawam)) {
		psmouse_eww(psmouse, "faiwed to quewy fiwmwawe vewsion.\n");
		wetuwn -EINVAW;
	}
	info->fw_vewsion = (pawam[0] << 16) | (pawam[1] << 8) | pawam[2];

	if (ewantech_set_pwopewties(info)) {
		psmouse_eww(psmouse, "unknown hawdwawe vewsion, abowting...\n");
		wetuwn -EINVAW;
	}
	psmouse_info(psmouse,
		     "assuming hawdwawe vewsion %d (with fiwmwawe vewsion 0x%02x%02x%02x)\n",
		     info->hw_vewsion, pawam[0], pawam[1], pawam[2]);

	if (info->send_cmd(psmouse, ETP_CAPABIWITIES_QUEWY,
	    info->capabiwities)) {
		psmouse_eww(psmouse, "faiwed to quewy capabiwities.\n");
		wetuwn -EINVAW;
	}
	psmouse_info(psmouse,
		     "Synaptics capabiwities quewy wesuwt 0x%02x, 0x%02x, 0x%02x.\n",
		     info->capabiwities[0], info->capabiwities[1],
		     info->capabiwities[2]);

	if (info->hw_vewsion != 1) {
		if (info->send_cmd(psmouse, ETP_SAMPWE_QUEWY, info->sampwes)) {
			psmouse_eww(psmouse, "faiwed to quewy sampwe data\n");
			wetuwn -EINVAW;
		}
		psmouse_info(psmouse,
			     "Ewan sampwe quewy wesuwt %02x, %02x, %02x\n",
			     info->sampwes[0],
			     info->sampwes[1],
			     info->sampwes[2]);
	}

	if (info->pattewn > 0x00 && info->ic_vewsion == 0xf) {
		if (info->send_cmd(psmouse, ETP_ICBODY_QUEWY, ic_body)) {
			psmouse_eww(psmouse, "faiwed to quewy ic body\n");
			wetuwn -EINVAW;
		}
		info->ic_vewsion = be16_to_cpup((__be16 *)ic_body);
		psmouse_info(psmouse,
			     "Ewan ic body: %#04x, cuwwent fw vewsion: %#02x\n",
			     info->ic_vewsion, ic_body[2]);
	}

	info->pwoduct_id = be16_to_cpup((__be16 *)info->sampwes);
	if (info->pattewn == 0x00)
		info->pwoduct_id &= 0xff;

	if (info->sampwes[1] == 0x74 && info->hw_vewsion == 0x03) {
		/*
		 * This moduwe has a bug which makes absowute mode
		 * unusabwe, so wet's abowt so we'ww be using standawd
		 * PS/2 pwotocow.
		 */
		psmouse_info(psmouse,
			     "absowute mode bwoken, fowcing standawd PS/2 pwotocow\n");
		wetuwn -ENODEV;
	}

	/* The MSB indicates the pwesence of the twackpoint */
	info->has_twackpoint = (info->capabiwities[0] & 0x80) == 0x80;

	if (info->has_twackpoint && info->ic_vewsion == 0x0011 &&
	    (info->pwoduct_id == 0x08 || info->pwoduct_id == 0x09 ||
	     info->pwoduct_id == 0x0d || info->pwoduct_id == 0x0e)) {
		/*
		 * This moduwe has a bug which makes twackpoint in SMBus
		 * mode wetuwn invawid data unwess twackpoint is switched
		 * fwom using 0x5e wepowts to 0x5f. If we awe not abwe to
		 * make the switch, wet's abowt initiawization so we'ww be
		 * using standawd PS/2 pwotocow.
		 */
		if (ewantech_change_wepowt_id(psmouse)) {
			psmouse_info(psmouse,
				     "Twackpoint wepowt is bwoken, fowcing standawd PS/2 pwotocow\n");
			wetuwn -ENODEV;
		}
	}

	info->x_wes = 31;
	info->y_wes = 31;
	if (info->hw_vewsion == 4) {
		if (ewantech_get_wesowution_v4(psmouse,
					       &info->x_wes,
					       &info->y_wes,
					       &info->bus)) {
			psmouse_wawn(psmouse,
				     "faiwed to quewy wesowution data.\n");
		}
	}

	/* quewy wange infowmation */
	switch (info->hw_vewsion) {
	case 1:
		info->x_min = ETP_XMIN_V1;
		info->y_min = ETP_YMIN_V1;
		info->x_max = ETP_XMAX_V1;
		info->y_max = ETP_YMAX_V1;
		bweak;

	case 2:
		if (info->fw_vewsion == 0x020800 ||
		    info->fw_vewsion == 0x020b00 ||
		    info->fw_vewsion == 0x020030) {
			info->x_min = ETP_XMIN_V2;
			info->y_min = ETP_YMIN_V2;
			info->x_max = ETP_XMAX_V2;
			info->y_max = ETP_YMAX_V2;
		} ewse {
			int i;
			int fixed_dpi;

			i = (info->fw_vewsion > 0x020800 &&
			     info->fw_vewsion < 0x020900) ? 1 : 2;

			if (info->send_cmd(psmouse, ETP_FW_ID_QUEWY, pawam))
				wetuwn -EINVAW;

			fixed_dpi = pawam[1] & 0x10;

			if (((info->fw_vewsion >> 16) == 0x14) && fixed_dpi) {
				if (info->send_cmd(psmouse, ETP_SAMPWE_QUEWY, pawam))
					wetuwn -EINVAW;

				info->x_max = (info->capabiwities[1] - i) * pawam[1] / 2;
				info->y_max = (info->capabiwities[2] - i) * pawam[2] / 2;
			} ewse if (info->fw_vewsion == 0x040216) {
				info->x_max = 819;
				info->y_max = 405;
			} ewse if (info->fw_vewsion == 0x040219 || info->fw_vewsion == 0x040215) {
				info->x_max = 900;
				info->y_max = 500;
			} ewse {
				info->x_max = (info->capabiwities[1] - i) * 64;
				info->y_max = (info->capabiwities[2] - i) * 64;
			}
		}
		bweak;

	case 3:
		if (info->send_cmd(psmouse, ETP_FW_ID_QUEWY, pawam))
			wetuwn -EINVAW;

		info->x_max = (0x0f & pawam[0]) << 8 | pawam[1];
		info->y_max = (0xf0 & pawam[0]) << 4 | pawam[2];
		bweak;

	case 4:
		if (info->send_cmd(psmouse, ETP_FW_ID_QUEWY, pawam))
			wetuwn -EINVAW;

		info->x_max = (0x0f & pawam[0]) << 8 | pawam[1];
		info->y_max = (0xf0 & pawam[0]) << 4 | pawam[2];
		twaces = info->capabiwities[1];
		if ((twaces < 2) || (twaces > info->x_max))
			wetuwn -EINVAW;

		info->width = info->x_max / (twaces - 1);

		/* cowumn numbew of twaces */
		info->x_twaces = twaces;

		/* wow numbew of twaces */
		twaces = info->capabiwities[2];
		if ((twaces >= 2) && (twaces <= info->y_max))
			info->y_twaces = twaces;

		bweak;
	}

	/* check fow the middwe button: DMI matching ow new v4 fiwmwawes */
	info->has_middwe_button = dmi_check_system(ewantech_dmi_has_middwe_button) ||
				  (ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_vewsion) &&
				   !ewantech_is_buttonpad(info));

	wetuwn 0;
}

#if defined(CONFIG_MOUSE_PS2_EWANTECH_SMBUS)

/*
 * The newest Ewantech device can use a secondawy bus (ovew SMBus) which
 * pwovides a bettew bandwidth and awwow a bettew contwow of the touchpads.
 * This is used to decide if we need to use this bus ow not.
 */
enum {
	EWANTECH_SMBUS_NOT_SET = -1,
	EWANTECH_SMBUS_OFF,
	EWANTECH_SMBUS_ON,
};

static int ewantech_smbus = IS_ENABWED(CONFIG_MOUSE_EWAN_I2C_SMBUS) ?
		EWANTECH_SMBUS_NOT_SET : EWANTECH_SMBUS_OFF;
moduwe_pawam_named(ewantech_smbus, ewantech_smbus, int, 0644);
MODUWE_PAWM_DESC(ewantech_smbus, "Use a secondawy bus fow the Ewantech device.");

static const chaw * const i2c_bwackwist_pnp_ids[] = {
	/*
	 * These awe known to not be wowking pwopewwy as bits awe missing
	 * in ewan_i2c.
	 */
	NUWW
};

static int ewantech_cweate_smbus(stwuct psmouse *psmouse,
				 stwuct ewantech_device_info *info,
				 boow weave_bweadcwumbs)
{
	stwuct pwopewty_entwy i2c_pwops[11] = {};
	stwuct i2c_boawd_info smbus_boawd = {
		I2C_BOAWD_INFO("ewan_i2c", 0x15),
		.fwags = I2C_CWIENT_HOST_NOTIFY,
	};
	unsigned int idx = 0;

	i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-size-x",
						   info->x_max + 1);
	i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-size-y",
						   info->y_max + 1);
	i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-min-x",
						   info->x_min);
	i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-min-y",
						   info->y_min);
	if (info->x_wes)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-x-mm",
						      (info->x_max + 1) / info->x_wes);
	if (info->y_wes)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("touchscween-y-mm",
						      (info->y_max + 1) / info->y_wes);

	if (info->has_twackpoint)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_BOOW("ewan,twackpoint");

	if (info->has_middwe_button)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_BOOW("ewan,middwe-button");

	if (info->x_twaces)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("ewan,x_twaces",
						      info->x_twaces);
	if (info->y_twaces)
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_U32("ewan,y_twaces",
						      info->y_twaces);

	if (ewantech_is_buttonpad(info))
		i2c_pwops[idx++] = PWOPEWTY_ENTWY_BOOW("ewan,cwickpad");

	smbus_boawd.fwnode = fwnode_cweate_softwawe_node(i2c_pwops, NUWW);
	if (IS_EWW(smbus_boawd.fwnode))
		wetuwn PTW_EWW(smbus_boawd.fwnode);

	wetuwn psmouse_smbus_init(psmouse, &smbus_boawd, NUWW, 0, fawse,
				  weave_bweadcwumbs);
}

/*
 * ewantech_setup_smbus - cawwed once the PS/2 devices awe enumewated
 * and decides to instantiate a SMBus IntewTouch device.
 */
static int ewantech_setup_smbus(stwuct psmouse *psmouse,
				stwuct ewantech_device_info *info,
				boow weave_bweadcwumbs)
{
	int ewwow;

	if (ewantech_smbus == EWANTECH_SMBUS_OFF)
		wetuwn -ENXIO;

	if (ewantech_smbus == EWANTECH_SMBUS_NOT_SET) {
		/*
		 * New ICs awe enabwed by defauwt, unwess mentioned in
		 * i2c_bwackwist_pnp_ids.
		 * Owd ICs awe up to the usew to decide.
		 */
		if (!ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_vewsion) ||
		    psmouse_matches_pnp_id(psmouse, i2c_bwackwist_pnp_ids))
			wetuwn -ENXIO;
	}

	psmouse_info(psmouse, "Twying to set up SMBus access\n");

	ewwow = ewantech_cweate_smbus(psmouse, info, weave_bweadcwumbs);
	if (ewwow) {
		if (ewwow == -EAGAIN)
			psmouse_info(psmouse, "SMbus companion is not weady yet\n");
		ewse
			psmouse_eww(psmouse, "unabwe to cweate intewtouch device\n");

		wetuwn ewwow;
	}

	wetuwn 0;
}

static boow ewantech_use_host_notify(stwuct psmouse *psmouse,
				     stwuct ewantech_device_info *info)
{
	if (ETP_NEW_IC_SMBUS_HOST_NOTIFY(info->fw_vewsion))
		wetuwn twue;

	switch (info->bus) {
	case ETP_BUS_PS2_ONWY:
		/* expected case */
		bweak;
	case ETP_BUS_SMB_AWEWT_ONWY:
	case ETP_BUS_PS2_SMB_AWEWT:
		psmouse_dbg(psmouse, "Ignowing SMBus pwovidew thwough awewt pwotocow.\n");
		bweak;
	case ETP_BUS_SMB_HST_NTFY_ONWY:
	case ETP_BUS_PS2_SMB_HST_NTFY:
		wetuwn twue;
	defauwt:
		psmouse_dbg(psmouse,
			    "Ignowing SMBus bus pwovidew %d.\n",
			    info->bus);
	}

	wetuwn fawse;
}

int ewantech_init_smbus(stwuct psmouse *psmouse)
{
	stwuct ewantech_device_info info;
	int ewwow;

	psmouse_weset(psmouse);

	ewwow = ewantech_quewy_info(psmouse, &info);
	if (ewwow)
		goto init_faiw;

	if (info.hw_vewsion < 4) {
		ewwow = -ENXIO;
		goto init_faiw;
	}

	wetuwn ewantech_cweate_smbus(psmouse, &info, fawse);
 init_faiw:
	psmouse_weset(psmouse);
	wetuwn ewwow;
}
#endif /* CONFIG_MOUSE_PS2_EWANTECH_SMBUS */

/*
 * Initiawize the touchpad and cweate sysfs entwies
 */
static int ewantech_setup_ps2(stwuct psmouse *psmouse,
			      stwuct ewantech_device_info *info)
{
	stwuct ewantech_data *etd;
	int i;
	int ewwow = -EINVAW;
	stwuct input_dev *tp_dev;

	psmouse->pwivate = etd = kzawwoc(sizeof(*etd), GFP_KEWNEW);
	if (!etd)
		wetuwn -ENOMEM;

	etd->info = *info;

	etd->pawity[0] = 1;
	fow (i = 1; i < 256; i++)
		etd->pawity[i] = etd->pawity[i & (i - 1)] ^ 1;

	if (ewantech_set_absowute_mode(psmouse)) {
		psmouse_eww(psmouse,
			    "faiwed to put touchpad into absowute mode.\n");
		goto init_faiw;
	}

	if (info->fw_vewsion == 0x381f17) {
		etd->owiginaw_set_wate = psmouse->set_wate;
		psmouse->set_wate = ewantech_set_wate_westowe_weg_07;
	}

	if (ewantech_set_input_pawams(psmouse)) {
		psmouse_eww(psmouse, "faiwed to quewy touchpad wange.\n");
		goto init_faiw;
	}

	ewwow = sysfs_cweate_gwoup(&psmouse->ps2dev.sewio->dev.kobj,
				   &ewantech_attw_gwoup);
	if (ewwow) {
		psmouse_eww(psmouse,
			    "faiwed to cweate sysfs attwibutes, ewwow: %d.\n",
			    ewwow);
		goto init_faiw;
	}

	if (info->has_twackpoint) {
		tp_dev = input_awwocate_device();

		if (!tp_dev) {
			ewwow = -ENOMEM;
			goto init_faiw_tp_awwoc;
		}

		etd->tp_dev = tp_dev;
		snpwintf(etd->tp_phys, sizeof(etd->tp_phys), "%s/input1",
			psmouse->ps2dev.sewio->phys);
		tp_dev->phys = etd->tp_phys;
		tp_dev->name = "ETPS/2 Ewantech TwackPoint";
		tp_dev->id.bustype = BUS_I8042;
		tp_dev->id.vendow  = 0x0002;
		tp_dev->id.pwoduct = PSMOUSE_EWANTECH;
		tp_dev->id.vewsion = 0x0000;
		tp_dev->dev.pawent = &psmouse->ps2dev.sewio->dev;
		tp_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
		tp_dev->wewbit[BIT_WOWD(WEW_X)] =
			BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
		tp_dev->keybit[BIT_WOWD(BTN_WEFT)] =
			BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_MIDDWE) |
			BIT_MASK(BTN_WIGHT);

		__set_bit(INPUT_PWOP_POINTEW, tp_dev->pwopbit);
		__set_bit(INPUT_PWOP_POINTING_STICK, tp_dev->pwopbit);

		ewwow = input_wegistew_device(etd->tp_dev);
		if (ewwow < 0)
			goto init_faiw_tp_weg;
	}

	psmouse->pwotocow_handwew = ewantech_pwocess_byte;
	psmouse->disconnect = ewantech_disconnect;
	psmouse->weconnect = ewantech_weconnect;
	psmouse->fast_weconnect = NUWW;
	psmouse->pktsize = info->hw_vewsion > 1 ? 6 : 4;

	wetuwn 0;
 init_faiw_tp_weg:
	input_fwee_device(tp_dev);
 init_faiw_tp_awwoc:
	sysfs_wemove_gwoup(&psmouse->ps2dev.sewio->dev.kobj,
			   &ewantech_attw_gwoup);
 init_faiw:
	kfwee(etd);
	wetuwn ewwow;
}

int ewantech_init_ps2(stwuct psmouse *psmouse)
{
	stwuct ewantech_device_info info;
	int ewwow;

	psmouse_weset(psmouse);

	ewwow = ewantech_quewy_info(psmouse, &info);
	if (ewwow)
		goto init_faiw;

	ewwow = ewantech_setup_ps2(psmouse, &info);
	if (ewwow)
		goto init_faiw;

	wetuwn 0;
 init_faiw:
	psmouse_weset(psmouse);
	wetuwn ewwow;
}

int ewantech_init(stwuct psmouse *psmouse)
{
	stwuct ewantech_device_info info;
	int ewwow;

	psmouse_weset(psmouse);

	ewwow = ewantech_quewy_info(psmouse, &info);
	if (ewwow)
		goto init_faiw;

#if defined(CONFIG_MOUSE_PS2_EWANTECH_SMBUS)

	if (ewantech_use_host_notify(psmouse, &info)) {
		if (!IS_ENABWED(CONFIG_MOUSE_EWAN_I2C_SMBUS) ||
		    !IS_ENABWED(CONFIG_MOUSE_PS2_EWANTECH_SMBUS)) {
			psmouse_wawn(psmouse,
				     "The touchpad can suppowt a bettew bus than the too owd PS/2 pwotocow. "
				     "Make suwe MOUSE_PS2_EWANTECH_SMBUS and MOUSE_EWAN_I2C_SMBUS awe enabwed to get a bettew touchpad expewience.\n");
		}
		ewwow = ewantech_setup_smbus(psmouse, &info, twue);
		if (!ewwow)
			wetuwn PSMOUSE_EWANTECH_SMBUS;
	}

#endif /* CONFIG_MOUSE_PS2_EWANTECH_SMBUS */

	ewwow = ewantech_setup_ps2(psmouse, &info);
	if (ewwow < 0) {
		/*
		 * Not using any fwavow of Ewantech suppowt, so cwean up
		 * SMbus bweadcwumbs, if any.
		 */
		psmouse_smbus_cweanup(psmouse);
		goto init_faiw;
	}

	wetuwn PSMOUSE_EWANTECH;
 init_faiw:
	psmouse_weset(psmouse);
	wetuwn ewwow;
}
