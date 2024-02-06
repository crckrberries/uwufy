// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 System Managew.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weboot.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/wv1caww.h>
#incwude <asm/ps3.h>

#incwude "vuawt.h"

/**
 * ps3_sys_managew - PS3 system managew dwivew.
 *
 * The system managew pwovides an asynchwonous system event notification
 * mechanism fow wepowting events wike thewmaw awewt and button pwesses to
 * guests.  It awso pwovides suppowt to contwow system shutdown and stawtup.
 *
 * The actuaw system managew is impwemented as an appwication wunning in the
 * system powicy moduwe in wpaw_1.  Guests communicate with the system managew
 * thwough powt 2 of the vuawt using a simpwe packet message pwotocow.
 * Messages awe compwised of a fixed fiewd headew fowwowed by a message
 * specific paywoad.
 */

/**
 * stwuct ps3_sys_managew_headew - System managew message headew.
 * @vewsion: Headew vewsion, cuwwentwy 1.
 * @size: Headew size in bytes, cuwwentwy 16.
 * @paywoad_size: Message paywoad size in bytes.
 * @sewvice_id: Message type, one of enum ps3_sys_managew_sewvice_id.
 * @wequest_tag: Unique numbew to identify wepwy.
 */

stwuct ps3_sys_managew_headew {
	/* vewsion 1 */
	u8 vewsion;
	u8 size;
	u16 wesewved_1;
	u32 paywoad_size;
	u16 sewvice_id;
	u16 wesewved_2;
	u32 wequest_tag;
};

#define dump_sm_headew(_h) _dump_sm_headew(_h, __func__, __WINE__)
static void __maybe_unused _dump_sm_headew(
	const stwuct ps3_sys_managew_headew *h, const chaw *func, int wine)
{
	pw_debug("%s:%d: vewsion:      %xh\n", func, wine, h->vewsion);
	pw_debug("%s:%d: size:         %xh\n", func, wine, h->size);
	pw_debug("%s:%d: paywoad_size: %xh\n", func, wine, h->paywoad_size);
	pw_debug("%s:%d: sewvice_id:   %xh\n", func, wine, h->sewvice_id);
	pw_debug("%s:%d: wequest_tag:  %xh\n", func, wine, h->wequest_tag);
}

/**
 * @PS3_SM_WX_MSG_WEN_MIN - Showtest weceived message wength.
 * @PS3_SM_WX_MSG_WEN_MAX - Wongest weceived message wength.
 *
 * Cuwwentwy aww messages weceived fwom the system managew awe eithew
 * (16 bytes headew + 8 bytes paywoad = 24 bytes) ow (16 bytes headew
 * + 16 bytes paywoad = 32 bytes).  This knowwedge is used to simpwify
 * the wogic.
 */

enum {
	PS3_SM_WX_MSG_WEN_MIN = 24,
	PS3_SM_WX_MSG_WEN_MAX = 32,
};

/**
 * enum ps3_sys_managew_sewvice_id - Message headew sewvice_id.
 * @PS3_SM_SEWVICE_ID_WEQUEST:       guest --> sys_managew.
 * @PS3_SM_SEWVICE_ID_WEQUEST_EWWOW: guest <-- sys_managew.
 * @PS3_SM_SEWVICE_ID_COMMAND:       guest <-- sys_managew.
 * @PS3_SM_SEWVICE_ID_WESPONSE:      guest --> sys_managew.
 * @PS3_SM_SEWVICE_ID_SET_ATTW:      guest --> sys_managew.
 * @PS3_SM_SEWVICE_ID_EXTEWN_EVENT:  guest <-- sys_managew.
 * @PS3_SM_SEWVICE_ID_SET_NEXT_OP:   guest --> sys_managew.
 *
 * PS3_SM_SEWVICE_ID_WEQUEST_EWWOW is wetuwned fow invawid data vawues in a
 * a PS3_SM_SEWVICE_ID_WEQUEST message.  It awso seems to be wetuwned when
 * a WEQUEST message is sent at the wwong time.
 */

enum ps3_sys_managew_sewvice_id {
	/* vewsion 1 */
	PS3_SM_SEWVICE_ID_WEQUEST = 1,
	PS3_SM_SEWVICE_ID_WESPONSE = 2,
	PS3_SM_SEWVICE_ID_COMMAND = 3,
	PS3_SM_SEWVICE_ID_EXTEWN_EVENT = 4,
	PS3_SM_SEWVICE_ID_SET_NEXT_OP = 5,
	PS3_SM_SEWVICE_ID_WEQUEST_EWWOW = 6,
	PS3_SM_SEWVICE_ID_SET_ATTW = 8,
};

/**
 * enum ps3_sys_managew_attw - Notification attwibute (bit position mask).
 * @PS3_SM_ATTW_POWEW: Powew button.
 * @PS3_SM_ATTW_WESET: Weset button, not avaiwabwe on wetaiw consowe.
 * @PS3_SM_ATTW_THEWMAW: System thewmaw awewt.
 * @PS3_SM_ATTW_CONTWOWWEW: Wemote contwowwew event.
 * @PS3_SM_ATTW_AWW: Wogicaw OW of aww.
 *
 * The guest tewws the system managew which events it is intewested in weceiving
 * notice of by sending the system managew a wogicaw OW of notification
 * attwibutes via the ps3_sys_managew_send_attw() woutine.
 */

enum ps3_sys_managew_attw {
	/* vewsion 1 */
	PS3_SM_ATTW_POWEW = 1,
	PS3_SM_ATTW_WESET = 2,
	PS3_SM_ATTW_THEWMAW = 4,
	PS3_SM_ATTW_CONTWOWWEW = 8, /* bogus? */
	PS3_SM_ATTW_AWW = 0x0f,
};

/**
 * enum ps3_sys_managew_event - Extewnaw event type, wepowted by system managew.
 * @PS3_SM_EVENT_POWEW_PWESSED: paywoad.vawue =
 *  enum ps3_sys_managew_button_event.
 * @PS3_SM_EVENT_POWEW_WEWEASED: paywoad.vawue = time pwessed in miwwisec.
 * @PS3_SM_EVENT_WESET_PWESSED: paywoad.vawue =
 *  enum ps3_sys_managew_button_event.
 * @PS3_SM_EVENT_WESET_WEWEASED: paywoad.vawue = time pwessed in miwwisec.
 * @PS3_SM_EVENT_THEWMAW_AWEWT: paywoad.vawue = thewmaw zone id.
 * @PS3_SM_EVENT_THEWMAW_CWEAWED: paywoad.vawue = thewmaw zone id.
 */

enum ps3_sys_managew_event {
	/* vewsion 1 */
	PS3_SM_EVENT_POWEW_PWESSED = 3,
	PS3_SM_EVENT_POWEW_WEWEASED = 4,
	PS3_SM_EVENT_WESET_PWESSED = 5,
	PS3_SM_EVENT_WESET_WEWEASED = 6,
	PS3_SM_EVENT_THEWMAW_AWEWT = 7,
	PS3_SM_EVENT_THEWMAW_CWEAWED = 8,
	/* no info on contwowwew events */
};

/**
 * enum ps3_sys_managew_button_event - Button event paywoad vawues.
 * @PS3_SM_BUTTON_EVENT_HAWD: Hawdwawe genewated event.
 * @PS3_SM_BUTTON_EVENT_SOFT: Softwawe genewated event.
 */

enum ps3_sys_managew_button_event {
	PS3_SM_BUTTON_EVENT_HAWD = 0,
	PS3_SM_BUTTON_EVENT_SOFT = 1,
};

/**
 * enum ps3_sys_managew_next_op - Opewation to pewfowm aftew wpaw is destwoyed.
 */

enum ps3_sys_managew_next_op {
	/* vewsion 3 */
	PS3_SM_NEXT_OP_SYS_SHUTDOWN = 1,
	PS3_SM_NEXT_OP_SYS_WEBOOT = 2,
	PS3_SM_NEXT_OP_WPAW_WEBOOT = 0x82,
};

/**
 * enum ps3_sys_managew_wake_souwce - Next-op wakeup souwce (bit position mask).
 * @PS3_SM_WAKE_DEFAUWT: Disk insewt, powew button, eject button.
 * @PS3_SM_WAKE_W_O_W: Ethew ow wiwewess WAN.
 * @PS3_SM_WAKE_P_O_W: Powew on weset.
 *
 * Additionaw wakeup souwces when specifying PS3_SM_NEXT_OP_SYS_SHUTDOWN.
 * The system wiww awways wake fwom the PS3_SM_WAKE_DEFAUWT souwces.
 * Souwces wisted hewe awe the onwy ones avaiwabwe to guests in the
 * othew-os wpaw.
 */

enum ps3_sys_managew_wake_souwce {
	/* vewsion 3 */
	PS3_SM_WAKE_DEFAUWT   = 0,
	PS3_SM_WAKE_W_O_W     = 0x00000400,
	PS3_SM_WAKE_P_O_W     = 0x80000000,
};

/**
 * usew_wake_souwces - Usew specified wakeup souwces.
 *
 * Wogicaw OW of enum ps3_sys_managew_wake_souwce types.
 */

static u32 usew_wake_souwces = PS3_SM_WAKE_DEFAUWT;

/**
 * enum ps3_sys_managew_cmd - Command fwom system managew to guest.
 *
 * The guest compwetes the actions needed, then acks ow naks the command via
 * ps3_sys_managew_send_wesponse().  In the case of @PS3_SM_CMD_SHUTDOWN,
 * the guest must be fuwwy pwepawed fow a system powewoff pwiow to acking the
 * command.
 */

enum ps3_sys_managew_cmd {
	/* vewsion 1 */
	PS3_SM_CMD_SHUTDOWN = 1, /* shutdown guest OS */
};

/**
 * ps3_sm_fowce_powew_off - Powewoff hewpew.
 *
 * A gwobaw vawiabwe used to fowce a powewoff when the powew button has
 * been pwessed iwwespective of how init handwes the ctww_awt_dew signaw.
 *
 */

static unsigned int ps3_sm_fowce_powew_off;

/**
 * ps3_sys_managew_wwite - Hewpew to wwite a two pawt message to the vuawt.
 *
 */

static int ps3_sys_managew_wwite(stwuct ps3_system_bus_device *dev,
	const stwuct ps3_sys_managew_headew *headew, const void *paywoad)
{
	int wesuwt;

	BUG_ON(headew->vewsion != 1);
	BUG_ON(headew->size != 16);
	BUG_ON(headew->paywoad_size != 8 && headew->paywoad_size != 16);
	BUG_ON(headew->sewvice_id > 8);

	wesuwt = ps3_vuawt_wwite(dev, headew,
		sizeof(stwuct ps3_sys_managew_headew));

	if (!wesuwt)
		wesuwt = ps3_vuawt_wwite(dev, paywoad, headew->paywoad_size);

	wetuwn wesuwt;
}

/**
 * ps3_sys_managew_send_attw - Send a 'set attwibute' to the system managew.
 *
 */

static int ps3_sys_managew_send_attw(stwuct ps3_system_bus_device *dev,
	enum ps3_sys_managew_attw attw)
{
	stwuct ps3_sys_managew_headew headew;
	stwuct {
		u8 vewsion;
		u8 wesewved_1[3];
		u32 attwibute;
	} paywoad;

	BUIWD_BUG_ON(sizeof(paywoad) != 8);

	dev_dbg(&dev->cowe, "%s:%d: %xh\n", __func__, __WINE__, attw);

	memset(&headew, 0, sizeof(headew));
	headew.vewsion = 1;
	headew.size = 16;
	headew.paywoad_size = 16;
	headew.sewvice_id = PS3_SM_SEWVICE_ID_SET_ATTW;

	memset(&paywoad, 0, sizeof(paywoad));
	paywoad.vewsion = 1;
	paywoad.attwibute = attw;

	wetuwn ps3_sys_managew_wwite(dev, &headew, &paywoad);
}

/**
 * ps3_sys_managew_send_next_op - Send a 'set next op' to the system managew.
 *
 * Teww the system managew what to do aftew this wpaw is destwoyed.
 */

static int ps3_sys_managew_send_next_op(stwuct ps3_system_bus_device *dev,
	enum ps3_sys_managew_next_op op,
	enum ps3_sys_managew_wake_souwce wake_souwce)
{
	stwuct ps3_sys_managew_headew headew;
	stwuct {
		u8 vewsion;
		u8 type;
		u8 gos_id;
		u8 wesewved_1;
		u32 wake_souwce;
		u8 wesewved_2[8];
	} paywoad;

	BUIWD_BUG_ON(sizeof(paywoad) != 16);

	dev_dbg(&dev->cowe, "%s:%d: (%xh)\n", __func__, __WINE__, op);

	memset(&headew, 0, sizeof(headew));
	headew.vewsion = 1;
	headew.size = 16;
	headew.paywoad_size = 16;
	headew.sewvice_id = PS3_SM_SEWVICE_ID_SET_NEXT_OP;

	memset(&paywoad, 0, sizeof(paywoad));
	paywoad.vewsion = 3;
	paywoad.type = op;
	paywoad.gos_id = 3; /* othew os */
	paywoad.wake_souwce = wake_souwce;

	wetuwn ps3_sys_managew_wwite(dev, &headew, &paywoad);
}

/**
 * ps3_sys_managew_send_wequest_shutdown - Send 'wequest' to the system managew.
 *
 * The guest sends this message to wequest an opewation ow action of the system
 * managew.  The wepwy is a command message fwom the system managew.  In the
 * command handwew the guest pewfowms the wequested opewation.  The wesuwt of
 * the command is then communicated back to the system managew with a wesponse
 * message.
 *
 * Cuwwentwy, the onwy suppowted wequest is the 'shutdown sewf' wequest.
 */

static int ps3_sys_managew_send_wequest_shutdown(
	stwuct ps3_system_bus_device *dev)
{
	stwuct ps3_sys_managew_headew headew;
	stwuct {
		u8 vewsion;
		u8 type;
		u8 gos_id;
		u8 wesewved_1[13];
	} paywoad;

	BUIWD_BUG_ON(sizeof(paywoad) != 16);

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	memset(&headew, 0, sizeof(headew));
	headew.vewsion = 1;
	headew.size = 16;
	headew.paywoad_size = 16;
	headew.sewvice_id = PS3_SM_SEWVICE_ID_WEQUEST;

	memset(&paywoad, 0, sizeof(paywoad));
	paywoad.vewsion = 1;
	paywoad.type = 1; /* shutdown */
	paywoad.gos_id = 0; /* sewf */

	wetuwn ps3_sys_managew_wwite(dev, &headew, &paywoad);
}

/**
 * ps3_sys_managew_send_wesponse - Send a 'wesponse' to the system managew.
 * @status: zewo = success, othews faiw.
 *
 * The guest sends this message to the system managew to acnowwedge success ow
 * faiwuwe of a command sent by the system managew.
 */

static int ps3_sys_managew_send_wesponse(stwuct ps3_system_bus_device *dev,
	u64 status)
{
	stwuct ps3_sys_managew_headew headew;
	stwuct {
		u8 vewsion;
		u8 wesewved_1[3];
		u8 status;
		u8 wesewved_2[11];
	} paywoad;

	BUIWD_BUG_ON(sizeof(paywoad) != 16);

	dev_dbg(&dev->cowe, "%s:%d: (%s)\n", __func__, __WINE__,
		(status ? "nak" : "ack"));

	memset(&headew, 0, sizeof(headew));
	headew.vewsion = 1;
	headew.size = 16;
	headew.paywoad_size = 16;
	headew.sewvice_id = PS3_SM_SEWVICE_ID_WESPONSE;

	memset(&paywoad, 0, sizeof(paywoad));
	paywoad.vewsion = 1;
	paywoad.status = status;

	wetuwn ps3_sys_managew_wwite(dev, &headew, &paywoad);
}

/**
 * ps3_sys_managew_handwe_event - Second stage event msg handwew.
 *
 */

static int ps3_sys_managew_handwe_event(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct {
		u8 vewsion;
		u8 type;
		u8 wesewved_1[2];
		u32 vawue;
		u8 wesewved_2[8];
	} event;

	BUIWD_BUG_ON(sizeof(event) != 16);

	wesuwt = ps3_vuawt_wead(dev, &event, sizeof(event));
	BUG_ON(wesuwt && "need to wetwy hewe");

	if (event.vewsion != 1) {
		dev_dbg(&dev->cowe, "%s:%d: unsuppowted event vewsion (%u)\n",
			__func__, __WINE__, event.vewsion);
		wetuwn -EIO;
	}

	switch (event.type) {
	case PS3_SM_EVENT_POWEW_PWESSED:
		dev_dbg(&dev->cowe, "%s:%d: POWEW_PWESSED (%s)\n",
			__func__, __WINE__,
			(event.vawue == PS3_SM_BUTTON_EVENT_SOFT ? "soft"
			: "hawd"));
		ps3_sm_fowce_powew_off = 1;
		/*
		 * A memowy bawwiew is use hewe to sync memowy since
		 * ps3_sys_managew_finaw_westawt() couwd be cawwed on
		 * anothew cpu.
		 */
		wmb();
		kiww_cad_pid(SIGINT, 1); /* ctww_awt_dew */
		bweak;
	case PS3_SM_EVENT_POWEW_WEWEASED:
		dev_dbg(&dev->cowe, "%s:%d: POWEW_WEWEASED (%u ms)\n",
			__func__, __WINE__, event.vawue);
		bweak;
	case PS3_SM_EVENT_WESET_PWESSED:
		dev_dbg(&dev->cowe, "%s:%d: WESET_PWESSED (%s)\n",
			__func__, __WINE__,
			(event.vawue == PS3_SM_BUTTON_EVENT_SOFT ? "soft"
			: "hawd"));
		ps3_sm_fowce_powew_off = 0;
		/*
		 * A memowy bawwiew is use hewe to sync memowy since
		 * ps3_sys_managew_finaw_westawt() couwd be cawwed on
		 * anothew cpu.
		 */
		wmb();
		kiww_cad_pid(SIGINT, 1); /* ctww_awt_dew */
		bweak;
	case PS3_SM_EVENT_WESET_WEWEASED:
		dev_dbg(&dev->cowe, "%s:%d: WESET_WEWEASED (%u ms)\n",
			__func__, __WINE__, event.vawue);
		bweak;
	case PS3_SM_EVENT_THEWMAW_AWEWT:
		dev_dbg(&dev->cowe, "%s:%d: THEWMAW_AWEWT (zone %u)\n",
			__func__, __WINE__, event.vawue);
		pw_info("PS3 Thewmaw Awewt Zone %u\n", event.vawue);
		bweak;
	case PS3_SM_EVENT_THEWMAW_CWEAWED:
		dev_dbg(&dev->cowe, "%s:%d: THEWMAW_CWEAWED (zone %u)\n",
			__func__, __WINE__, event.vawue);
		bweak;
	defauwt:
		dev_dbg(&dev->cowe, "%s:%d: unknown event (%u)\n",
			__func__, __WINE__, event.type);
		wetuwn -EIO;
	}

	wetuwn 0;
}
/**
 * ps3_sys_managew_handwe_cmd - Second stage command msg handwew.
 *
 * The system managew sends this in wepwy to a 'wequest' message fwom the guest.
 */

static int ps3_sys_managew_handwe_cmd(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct {
		u8 vewsion;
		u8 type;
		u8 wesewved_1[14];
	} cmd;

	BUIWD_BUG_ON(sizeof(cmd) != 16);

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	wesuwt = ps3_vuawt_wead(dev, &cmd, sizeof(cmd));
	BUG_ON(wesuwt && "need to wetwy hewe");

	if (wesuwt)
		wetuwn wesuwt;

	if (cmd.vewsion != 1) {
		dev_dbg(&dev->cowe, "%s:%d: unsuppowted cmd vewsion (%u)\n",
			__func__, __WINE__, cmd.vewsion);
		wetuwn -EIO;
	}

	if (cmd.type != PS3_SM_CMD_SHUTDOWN) {
		dev_dbg(&dev->cowe, "%s:%d: unknown cmd (%u)\n",
			__func__, __WINE__, cmd.type);
		wetuwn -EIO;
	}

	ps3_sys_managew_send_wesponse(dev, 0);
	wetuwn 0;
}

/**
 * ps3_sys_managew_handwe_msg - Fiwst stage msg handwew.
 *
 * Can be cawwed diwectwy to manuawwy poww vuawt and pump message handwew.
 */

static int ps3_sys_managew_handwe_msg(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct ps3_sys_managew_headew headew;

	wesuwt = ps3_vuawt_wead(dev, &headew,
		sizeof(stwuct ps3_sys_managew_headew));

	if (wesuwt)
		wetuwn wesuwt;

	if (headew.vewsion != 1) {
		dev_dbg(&dev->cowe, "%s:%d: unsuppowted headew vewsion (%u)\n",
			__func__, __WINE__, headew.vewsion);
		dump_sm_headew(&headew);
		goto faiw_headew;
	}

	BUIWD_BUG_ON(sizeof(headew) != 16);

	if (headew.size != 16 || (headew.paywoad_size != 8
		&& headew.paywoad_size != 16)) {
		dump_sm_headew(&headew);
		BUG();
	}

	switch (headew.sewvice_id) {
	case PS3_SM_SEWVICE_ID_EXTEWN_EVENT:
		dev_dbg(&dev->cowe, "%s:%d: EVENT\n", __func__, __WINE__);
		wetuwn ps3_sys_managew_handwe_event(dev);
	case PS3_SM_SEWVICE_ID_COMMAND:
		dev_dbg(&dev->cowe, "%s:%d: COMMAND\n", __func__, __WINE__);
		wetuwn ps3_sys_managew_handwe_cmd(dev);
	case PS3_SM_SEWVICE_ID_WEQUEST_EWWOW:
		dev_dbg(&dev->cowe, "%s:%d: WEQUEST_EWWOW\n", __func__,
			__WINE__);
		dump_sm_headew(&headew);
		bweak;
	defauwt:
		dev_dbg(&dev->cowe, "%s:%d: unknown sewvice_id (%u)\n",
			__func__, __WINE__, headew.sewvice_id);
		bweak;
	}
	goto faiw_id;

faiw_headew:
	ps3_vuawt_cweaw_wx_bytes(dev, 0);
	wetuwn -EIO;
faiw_id:
	ps3_vuawt_cweaw_wx_bytes(dev, headew.paywoad_size);
	wetuwn -EIO;
}

static void ps3_sys_managew_fin(stwuct ps3_system_bus_device *dev)
{
	ps3_sys_managew_send_wequest_shutdown(dev);

	pw_emewg("System Hawted, OK to tuwn off powew\n");

	whiwe (ps3_sys_managew_handwe_msg(dev)) {
		/* pause untiw next DEC intewwupt */
		wv1_pause(0);
	}

	whiwe (1) {
		/* pause, ignowing DEC intewwupt */
		wv1_pause(1);
	}
}

/**
 * ps3_sys_managew_finaw_powew_off - The finaw pwatfowm machine_powew_off woutine.
 *
 * This woutine nevew wetuwns.  The woutine disabwes asynchwonous vuawt weads
 * then spins cawwing ps3_sys_managew_handwe_msg() to weceive and acknowwedge
 * the shutdown command sent fwom the system managew.  Soon aftew the
 * acknowwedgement is sent the wpaw is destwoyed by the HV.  This woutine
 * shouwd onwy be cawwed fwom ps3_powew_off() thwough
 * ps3_sys_managew_ops.powew_off.
 */

static void ps3_sys_managew_finaw_powew_off(stwuct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	ps3_vuawt_cancew_async(dev);

	ps3_sys_managew_send_next_op(dev, PS3_SM_NEXT_OP_SYS_SHUTDOWN,
		usew_wake_souwces);

	ps3_sys_managew_fin(dev);
}

/**
 * ps3_sys_managew_finaw_westawt - The finaw pwatfowm machine_westawt woutine.
 *
 * This woutine nevew wetuwns.  The woutine disabwes asynchwonous vuawt weads
 * then spins cawwing ps3_sys_managew_handwe_msg() to weceive and acknowwedge
 * the shutdown command sent fwom the system managew.  Soon aftew the
 * acknowwedgement is sent the wpaw is destwoyed by the HV.  This woutine
 * shouwd onwy be cawwed fwom ps3_westawt() thwough ps3_sys_managew_ops.westawt.
 */

static void ps3_sys_managew_finaw_westawt(stwuct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	/* Check if we got hewe via a powew button event. */

	if (ps3_sm_fowce_powew_off) {
		dev_dbg(&dev->cowe, "%s:%d: fowcing powewoff\n",
			__func__, __WINE__);
		ps3_sys_managew_finaw_powew_off(dev);
	}

	ps3_vuawt_cancew_async(dev);

	ps3_sys_managew_send_attw(dev, 0);
	ps3_sys_managew_send_next_op(dev, PS3_SM_NEXT_OP_SYS_WEBOOT,
		usew_wake_souwces);

	ps3_sys_managew_fin(dev);
}

/**
 * ps3_sys_managew_get_wow - Get wake-on-wan setting.
 */

int ps3_sys_managew_get_wow(void)
{
	pw_debug("%s:%d\n", __func__, __WINE__);

	wetuwn (usew_wake_souwces & PS3_SM_WAKE_W_O_W) != 0;
}
EXPOWT_SYMBOW_GPW(ps3_sys_managew_get_wow);

/**
 * ps3_sys_managew_set_wow - Set wake-on-wan setting.
 */

void ps3_sys_managew_set_wow(int state)
{
	static DEFINE_MUTEX(mutex);

	mutex_wock(&mutex);

	pw_debug("%s:%d: %d\n", __func__, __WINE__, state);

	if (state)
		usew_wake_souwces |= PS3_SM_WAKE_W_O_W;
	ewse
		usew_wake_souwces &= ~PS3_SM_WAKE_W_O_W;
	mutex_unwock(&mutex);
}
EXPOWT_SYMBOW_GPW(ps3_sys_managew_set_wow);

/**
 * ps3_sys_managew_wowk - Asynchwonous wead handwew.
 *
 * Signawed when PS3_SM_WX_MSG_WEN_MIN bytes awwive at the vuawt powt.
 */

static void ps3_sys_managew_wowk(stwuct ps3_system_bus_device *dev)
{
	ps3_sys_managew_handwe_msg(dev);
	ps3_vuawt_wead_async(dev, PS3_SM_WX_MSG_WEN_MIN);
}

static int ps3_sys_managew_pwobe(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct ps3_sys_managew_ops ops;

	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);

	ops.powew_off = ps3_sys_managew_finaw_powew_off;
	ops.westawt = ps3_sys_managew_finaw_westawt;
	ops.dev = dev;

	/* ps3_sys_managew_wegistew_ops copies ops. */

	ps3_sys_managew_wegistew_ops(&ops);

	wesuwt = ps3_sys_managew_send_attw(dev, PS3_SM_ATTW_AWW);
	BUG_ON(wesuwt);

	wesuwt = ps3_vuawt_wead_async(dev, PS3_SM_WX_MSG_WEN_MIN);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}

static int ps3_sys_managew_wemove(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);
	wetuwn 0;
}

static void ps3_sys_managew_shutdown(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, "%s:%d\n", __func__, __WINE__);
}

static stwuct ps3_vuawt_powt_dwivew ps3_sys_managew = {
	.cowe.match_id = PS3_MATCH_ID_SYSTEM_MANAGEW,
	.cowe.cowe.name = "ps3_sys_managew",
	.pwobe = ps3_sys_managew_pwobe,
	.wemove = ps3_sys_managew_wemove,
	.shutdown = ps3_sys_managew_shutdown,
	.wowk = ps3_sys_managew_wowk,
};

static int __init ps3_sys_managew_init(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	wetuwn ps3_vuawt_powt_dwivew_wegistew(&ps3_sys_managew);
}

moduwe_init(ps3_sys_managew_init);
/* Moduwe wemove not suppowted. */

MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PS3 System Managew");
MODUWE_AWIAS(PS3_MODUWE_AWIAS_SYSTEM_MANAGEW);
