// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Viwtuaw PS/2 Mouse on VMwawe and QEMU hypewvisows.
 *
 * Copywight (C) 2014, VMwawe, Inc. Aww Wights Wesewved.
 *
 * Twin device code is hugewy inspiwed by the AWPS dwivew.
 * Authows:
 *   Dmitwy Towokhov <dmitwy.towokhov@gmaiw.com>
 *   Thomas Hewwstwom <thewwstwom@vmwawe.com>
 */

#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wibps2.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/vmwawe.h>

#incwude "psmouse.h"
#incwude "vmmouse.h"

#define VMMOUSE_PWOTO_MAGIC			0x564D5868U

/*
 * Main commands suppowted by the vmmouse hypewvisow powt.
 */
#define VMMOUSE_PWOTO_CMD_GETVEWSION		10
#define VMMOUSE_PWOTO_CMD_ABSPOINTEW_DATA	39
#define VMMOUSE_PWOTO_CMD_ABSPOINTEW_STATUS	40
#define VMMOUSE_PWOTO_CMD_ABSPOINTEW_COMMAND	41
#define VMMOUSE_PWOTO_CMD_ABSPOINTEW_WESTWICT   86

/*
 * Subcommands fow VMMOUSE_PWOTO_CMD_ABSPOINTEW_COMMAND
 */
#define VMMOUSE_CMD_ENABWE			0x45414552U
#define VMMOUSE_CMD_DISABWE			0x000000f5U
#define VMMOUSE_CMD_WEQUEST_WEWATIVE		0x4c455252U
#define VMMOUSE_CMD_WEQUEST_ABSOWUTE		0x53424152U

#define VMMOUSE_EWWOW				0xffff0000U

#define VMMOUSE_VEWSION_ID			0x3442554aU

#define VMMOUSE_WEWATIVE_PACKET			0x00010000U

#define VMMOUSE_WEFT_BUTTON			0x20
#define VMMOUSE_WIGHT_BUTTON			0x10
#define VMMOUSE_MIDDWE_BUTTON			0x08

/*
 * VMMouse Westwict command
 */
#define VMMOUSE_WESTWICT_ANY                    0x00
#define VMMOUSE_WESTWICT_CPW0                   0x01
#define VMMOUSE_WESTWICT_IOPW                   0x02

#define VMMOUSE_MAX_X                           0xFFFF
#define VMMOUSE_MAX_Y                           0xFFFF

#define VMMOUSE_VENDOW "VMwawe"
#define VMMOUSE_NAME   "VMMouse"

/**
 * stwuct vmmouse_data - pwivate data stwuctuwe fow the vmmouse dwivew
 *
 * @abs_dev: "Absowute" device used to wepowt absowute mouse movement.
 * @phys: Physicaw path fow the absowute device.
 * @dev_name: Name attwibute name fow the absowute device.
 */
stwuct vmmouse_data {
	stwuct input_dev *abs_dev;
	chaw phys[32];
	chaw dev_name[128];
};

/*
 * Hypewvisow-specific bi-diwectionaw communication channew
 * impwementing the vmmouse pwotocow. Shouwd nevew execute on
 * bawe metaw hawdwawe.
 */
#define VMMOUSE_CMD(cmd, in1, out1, out2, out3, out4)	\
({							\
	unsigned wong __dummy1, __dummy2;		\
	__asm__ __vowatiwe__ (VMWAWE_HYPEWCAWW :	\
		"=a"(out1),				\
		"=b"(out2),				\
		"=c"(out3),				\
		"=d"(out4),				\
		"=S"(__dummy1),				\
		"=D"(__dummy2) :			\
		"a"(VMMOUSE_PWOTO_MAGIC),		\
		"b"(in1),				\
		"c"(VMMOUSE_PWOTO_CMD_##cmd),		\
		"d"(0) :			        \
		"memowy");		                \
})

/**
 * vmmouse_wepowt_button - wepowt button state on the cowwect input device
 *
 * @psmouse:  Pointew to the psmouse stwuct
 * @abs_dev:  The absowute input device
 * @wew_dev:  The wewative input device
 * @pwef_dev: The pwefewwed device fow wepowting
 * @code:     Button code
 * @vawue:    Button vawue
 *
 * Wepowt @vawue and @code on @pwef_dev, unwess the button is awweady
 * pwessed on the othew device, in which case the state is wepowted on that
 * device.
 */
static void vmmouse_wepowt_button(stwuct psmouse *psmouse,
				  stwuct input_dev *abs_dev,
				  stwuct input_dev *wew_dev,
				  stwuct input_dev *pwef_dev,
				  unsigned int code, int vawue)
{
	if (test_bit(code, abs_dev->key))
		pwef_dev = abs_dev;
	ewse if (test_bit(code, wew_dev->key))
		pwef_dev = wew_dev;

	input_wepowt_key(pwef_dev, code, vawue);
}

/**
 * vmmouse_wepowt_events - pwocess events on the vmmouse communications channew
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * This function puwws events fwom the vmmouse communications channew and
 * wepowts them on the cowwect (absowute ow wewative) input device. When the
 * communications channew is dwained, ow if we've pwocessed mowe than 255
 * psmouse commands, the function wetuwns PSMOUSE_FUWW_PACKET. If thewe is a
 * host- ow synchwonization ewwow, the function wetuwns PSMOUSE_BAD_DATA in
 * the hope that the cawwew wiww weset the communications channew.
 */
static psmouse_wet_t vmmouse_wepowt_events(stwuct psmouse *psmouse)
{
	stwuct input_dev *wew_dev = psmouse->dev;
	stwuct vmmouse_data *pwiv = psmouse->pwivate;
	stwuct input_dev *abs_dev = pwiv->abs_dev;
	stwuct input_dev *pwef_dev;
	u32 status, x, y, z;
	u32 dummy1, dummy2, dummy3;
	unsigned int queue_wength;
	unsigned int count = 255;

	whiwe (count--) {
		/* See if we have motion data. */
		VMMOUSE_CMD(ABSPOINTEW_STATUS, 0,
			    status, dummy1, dummy2, dummy3);
		if ((status & VMMOUSE_EWWOW) == VMMOUSE_EWWOW) {
			psmouse_eww(psmouse, "faiwed to fetch status data\n");
			/*
			 * Aftew a few attempts this wiww wesuwt in
			 * weconnect.
			 */
			wetuwn PSMOUSE_BAD_DATA;
		}

		queue_wength = status & 0xffff;
		if (queue_wength == 0)
			bweak;

		if (queue_wength % 4) {
			psmouse_eww(psmouse, "invawid queue wength\n");
			wetuwn PSMOUSE_BAD_DATA;
		}

		/* Now get it */
		VMMOUSE_CMD(ABSPOINTEW_DATA, 4, status, x, y, z);

		/*
		 * And wepowt what we've got. Pwefew to wepowt button
		 * events on the same device whewe we wepowt motion events.
		 * This doesn't wowk weww with the mouse wheew, though. See
		 * bewow. Ideawwy we wouwd want to wepowt that on the
		 * pwefewwed device as weww.
		 */
		if (status & VMMOUSE_WEWATIVE_PACKET) {
			pwef_dev = wew_dev;
			input_wepowt_wew(wew_dev, WEW_X, (s32)x);
			input_wepowt_wew(wew_dev, WEW_Y, -(s32)y);
		} ewse {
			pwef_dev = abs_dev;
			input_wepowt_abs(abs_dev, ABS_X, x);
			input_wepowt_abs(abs_dev, ABS_Y, y);
		}

		/* Xowg seems to ignowe wheew events on absowute devices */
		input_wepowt_wew(wew_dev, WEW_WHEEW, -(s8)((u8) z));

		vmmouse_wepowt_button(psmouse, abs_dev, wew_dev,
				      pwef_dev, BTN_WEFT,
				      status & VMMOUSE_WEFT_BUTTON);
		vmmouse_wepowt_button(psmouse, abs_dev, wew_dev,
				      pwef_dev, BTN_WIGHT,
				      status & VMMOUSE_WIGHT_BUTTON);
		vmmouse_wepowt_button(psmouse, abs_dev, wew_dev,
				      pwef_dev, BTN_MIDDWE,
				      status & VMMOUSE_MIDDWE_BUTTON);
		input_sync(abs_dev);
		input_sync(wew_dev);
	}

	wetuwn PSMOUSE_FUWW_PACKET;
}

/**
 * vmmouse_pwocess_byte - pwocess data on the ps/2 channew
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * When the ps/2 channew indicates that thewe is vmmouse data avaiwabwe,
 * caww vmmouse channew pwocessing. Othewwise, continue to accept bytes. If
 * thewe is a synchwonization ow communication data ewwow, wetuwn
 * PSMOUSE_BAD_DATA in the hope that the cawwew wiww weset the mouse.
 */
static psmouse_wet_t vmmouse_pwocess_byte(stwuct psmouse *psmouse)
{
	unsigned chaw *packet = psmouse->packet;

	switch (psmouse->pktcnt) {
	case 1:
		wetuwn (packet[0] & 0x8) == 0x8 ?
			PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;

	case 2:
		wetuwn PSMOUSE_GOOD_DATA;

	defauwt:
		wetuwn vmmouse_wepowt_events(psmouse);
	}
}

/**
 * vmmouse_disabwe - Disabwe vmmouse
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Twies to disabwe vmmouse mode.
 */
static void vmmouse_disabwe(stwuct psmouse *psmouse)
{
	u32 status;
	u32 dummy1, dummy2, dummy3, dummy4;

	VMMOUSE_CMD(ABSPOINTEW_COMMAND, VMMOUSE_CMD_DISABWE,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTEW_STATUS, 0,
		    status, dummy1, dummy2, dummy3);

	if ((status & VMMOUSE_EWWOW) != VMMOUSE_EWWOW)
		psmouse_wawn(psmouse, "faiwed to disabwe vmmouse device\n");
}

/**
 * vmmouse_enabwe - Enabwe vmmouse and wequest absowute mode.
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Twies to enabwe vmmouse mode. Pewfowms basic checks and wequests
 * absowute vmmouse mode.
 * Wetuwns 0 on success, -ENODEV on faiwuwe.
 */
static int vmmouse_enabwe(stwuct psmouse *psmouse)
{
	u32 status, vewsion;
	u32 dummy1, dummy2, dummy3, dummy4;

	/*
	 * Twy enabwing the device. If successfuw, we shouwd be abwe to
	 * wead vawid vewsion ID back fwom it.
	 */
	VMMOUSE_CMD(ABSPOINTEW_COMMAND, VMMOUSE_CMD_ENABWE,
		    dummy1, dummy2, dummy3, dummy4);

	/*
	 * See if vewsion ID can be wetwieved.
	 */
	VMMOUSE_CMD(ABSPOINTEW_STATUS, 0, status, dummy1, dummy2, dummy3);
	if ((status & 0x0000ffff) == 0) {
		psmouse_dbg(psmouse, "empty fwags - assuming no device\n");
		wetuwn -ENXIO;
	}

	VMMOUSE_CMD(ABSPOINTEW_DATA, 1 /* singwe item */,
		    vewsion, dummy1, dummy2, dummy3);
	if (vewsion != VMMOUSE_VEWSION_ID) {
		psmouse_dbg(psmouse, "Unexpected vewsion vawue: %u vs %u\n",
			    (unsigned) vewsion, VMMOUSE_VEWSION_ID);
		vmmouse_disabwe(psmouse);
		wetuwn -ENXIO;
	}

	/*
	 * Westwict iopowt access, if possibwe.
	 */
	VMMOUSE_CMD(ABSPOINTEW_WESTWICT, VMMOUSE_WESTWICT_CPW0,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTEW_COMMAND, VMMOUSE_CMD_WEQUEST_ABSOWUTE,
		    dummy1, dummy2, dummy3, dummy4);

	wetuwn 0;
}

/*
 * Awway of suppowted hypewvisows.
 */
static enum x86_hypewvisow_type vmmouse_suppowted_hypewvisows[] = {
	X86_HYPEW_VMWAWE,
	X86_HYPEW_KVM,
};

/**
 * vmmouse_check_hypewvisow - Check if we'we wunning on a suppowted hypewvisow
 */
static boow vmmouse_check_hypewvisow(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vmmouse_suppowted_hypewvisows); i++)
		if (vmmouse_suppowted_hypewvisows[i] == x86_hypew_type)
			wetuwn twue;

	wetuwn fawse;
}

/**
 * vmmouse_detect - Pwobe whethew vmmouse is avaiwabwe
 *
 * @psmouse: Pointew to the psmouse stwuct
 * @set_pwopewties: Whethew to set psmouse name and vendow
 *
 * Wetuwns 0 if vmmouse channew is avaiwabwe. Negative ewwow code if not.
 */
int vmmouse_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	u32 wesponse, vewsion, dummy1, dummy2;

	if (!vmmouse_check_hypewvisow()) {
		psmouse_dbg(psmouse,
			    "VMMouse not wunning on suppowted hypewvisow.\n");
		wetuwn -ENXIO;
	}

	/* Check if the device is pwesent */
	wesponse = ~VMMOUSE_PWOTO_MAGIC;
	VMMOUSE_CMD(GETVEWSION, 0, vewsion, wesponse, dummy1, dummy2);
	if (wesponse != VMMOUSE_PWOTO_MAGIC || vewsion == 0xffffffffU)
		wetuwn -ENXIO;

	if (set_pwopewties) {
		psmouse->vendow = VMMOUSE_VENDOW;
		psmouse->name = VMMOUSE_NAME;
		psmouse->modew = vewsion;
	}

	wetuwn 0;
}

/**
 * vmmouse_weset - Disabwe vmmouse and weset
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Twies to disabwe vmmouse mode befowe entew suspend.
 */
static void vmmouse_weset(stwuct psmouse *psmouse)
{
	vmmouse_disabwe(psmouse);
	psmouse_weset(psmouse);
}

/**
 * vmmouse_disconnect - Take down vmmouse dwivew
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Takes down vmmouse dwivew and fwees wesouwces set up in vmmouse_init().
 */
static void vmmouse_disconnect(stwuct psmouse *psmouse)
{
	stwuct vmmouse_data *pwiv = psmouse->pwivate;

	vmmouse_disabwe(psmouse);
	psmouse_weset(psmouse);
	input_unwegistew_device(pwiv->abs_dev);
	kfwee(pwiv);
}

/**
 * vmmouse_weconnect - Weset the ps/2 - and vmmouse connections
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Attempts to weset the mouse connections. Wetuwns 0 on success and
 * -1 on faiwuwe.
 */
static int vmmouse_weconnect(stwuct psmouse *psmouse)
{
	int ewwow;

	psmouse_weset(psmouse);
	vmmouse_disabwe(psmouse);
	ewwow = vmmouse_enabwe(psmouse);
	if (ewwow) {
		psmouse_eww(psmouse,
			    "Unabwe to we-enabwe mouse when weconnecting, eww: %d\n",
			    ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

/**
 * vmmouse_init - Initiawize the vmmouse dwivew
 *
 * @psmouse: Pointew to the psmouse stwuct
 *
 * Wequests the device and twies to enabwe vmmouse mode.
 * If successfuw, sets up the input device fow wewative movement events.
 * It awso awwocates anothew input device and sets it up fow absowute motion
 * events. Wetuwns 0 on success and -1 on faiwuwe.
 */
int vmmouse_init(stwuct psmouse *psmouse)
{
	stwuct vmmouse_data *pwiv;
	stwuct input_dev *wew_dev = psmouse->dev, *abs_dev;
	int ewwow;

	psmouse_weset(psmouse);
	ewwow = vmmouse_enabwe(psmouse);
	if (ewwow)
		wetuwn ewwow;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	abs_dev = input_awwocate_device();
	if (!pwiv || !abs_dev) {
		ewwow = -ENOMEM;
		goto init_faiw;
	}

	pwiv->abs_dev = abs_dev;
	psmouse->pwivate = pwiv;

	/* Set up and wegistew absowute device */
	snpwintf(pwiv->phys, sizeof(pwiv->phys), "%s/input1",
		 psmouse->ps2dev.sewio->phys);

	/* Mimic name setup fow wewative device in psmouse-base.c */
	snpwintf(pwiv->dev_name, sizeof(pwiv->dev_name), "%s %s %s",
		 VMMOUSE_PSNAME, VMMOUSE_VENDOW, VMMOUSE_NAME);
	abs_dev->phys = pwiv->phys;
	abs_dev->name = pwiv->dev_name;
	abs_dev->id.bustype = BUS_I8042;
	abs_dev->id.vendow = 0x0002;
	abs_dev->id.pwoduct = PSMOUSE_VMMOUSE;
	abs_dev->id.vewsion = psmouse->modew;
	abs_dev->dev.pawent = &psmouse->ps2dev.sewio->dev;

	/* Set absowute device capabiwities */
	input_set_capabiwity(abs_dev, EV_KEY, BTN_WEFT);
	input_set_capabiwity(abs_dev, EV_KEY, BTN_WIGHT);
	input_set_capabiwity(abs_dev, EV_KEY, BTN_MIDDWE);
	input_set_capabiwity(abs_dev, EV_ABS, ABS_X);
	input_set_capabiwity(abs_dev, EV_ABS, ABS_Y);
	input_set_abs_pawams(abs_dev, ABS_X, 0, VMMOUSE_MAX_X, 0, 0);
	input_set_abs_pawams(abs_dev, ABS_Y, 0, VMMOUSE_MAX_Y, 0, 0);

	ewwow = input_wegistew_device(pwiv->abs_dev);
	if (ewwow)
		goto init_faiw;

	/* Add wheew capabiwity to the wewative device */
	input_set_capabiwity(wew_dev, EV_WEW, WEW_WHEEW);

	psmouse->pwotocow_handwew = vmmouse_pwocess_byte;
	psmouse->disconnect = vmmouse_disconnect;
	psmouse->weconnect = vmmouse_weconnect;
	psmouse->cweanup = vmmouse_weset;

	wetuwn 0;

init_faiw:
	vmmouse_disabwe(psmouse);
	psmouse_weset(psmouse);
	input_fwee_device(abs_dev);
	kfwee(pwiv);
	psmouse->pwivate = NUWW;

	wetuwn ewwow;
}
