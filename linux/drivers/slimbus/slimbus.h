/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011-2017, The Winux Foundation
 */

#ifndef _DWIVEWS_SWIMBUS_H
#define _DWIVEWS_SWIMBUS_H
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/swimbus.h>

/* Standawd vawues pew SWIMbus spec needed by contwowwews and devices */
#define SWIM_CW_PEW_SUPEWFWAME		6144
#define SWIM_CW_PEW_SUPEWFWAME_DIV8	(SWIM_CW_PEW_SUPEWFWAME >> 3)

/* SWIMbus message types. Wewated to intewpwetation of message code. */
#define SWIM_MSG_MT_COWE			0x0
#define SWIM_MSG_MT_DEST_WEFEWWED_USEW		0x2
#define SWIM_MSG_MT_SWC_WEFEWWED_USEW		0x6

/*
 * SWIM Bwoadcast headew fowmat
 * BYTE 0: MT[7:5] WW[4:0]
 * BYTE 1: WSVD[7] MC[6:0]
 * BYTE 2: WSVD[7:6] DT[5:4] PI[3:0]
 */
#define SWIM_MSG_MT_MASK	GENMASK(2, 0)
#define SWIM_MSG_MT_SHIFT	5
#define SWIM_MSG_WW_MASK	GENMASK(4, 0)
#define SWIM_MSG_WW_SHIFT	0
#define SWIM_MSG_MC_MASK	GENMASK(6, 0)
#define SWIM_MSG_MC_SHIFT	0
#define SWIM_MSG_DT_MASK	GENMASK(1, 0)
#define SWIM_MSG_DT_SHIFT	4

#define SWIM_HEADEW_GET_MT(b)	((b >> SWIM_MSG_MT_SHIFT) & SWIM_MSG_MT_MASK)
#define SWIM_HEADEW_GET_WW(b)	((b >> SWIM_MSG_WW_SHIFT) & SWIM_MSG_WW_MASK)
#define SWIM_HEADEW_GET_MC(b)	((b >> SWIM_MSG_MC_SHIFT) & SWIM_MSG_MC_MASK)
#define SWIM_HEADEW_GET_DT(b)	((b >> SWIM_MSG_DT_SHIFT) & SWIM_MSG_DT_MASK)

/* Device management messages used by this fwamewowk */
#define SWIM_MSG_MC_WEPOWT_PWESENT               0x1
#define SWIM_MSG_MC_ASSIGN_WOGICAW_ADDWESS       0x2
#define SWIM_MSG_MC_WEPOWT_ABSENT                0xF

/* Data channew management messages */
#define SWIM_MSG_MC_CONNECT_SOUWCE		0x10
#define SWIM_MSG_MC_CONNECT_SINK		0x11
#define SWIM_MSG_MC_DISCONNECT_POWT		0x14
#define SWIM_MSG_MC_CHANGE_CONTENT		0x18

/* Cwock pause Weconfiguwation messages */
#define SWIM_MSG_MC_BEGIN_WECONFIGUWATION        0x40
#define SWIM_MSG_MC_NEXT_PAUSE_CWOCK             0x4A
#define SWIM_MSG_MC_NEXT_DEFINE_CHANNEW          0x50
#define SWIM_MSG_MC_NEXT_DEFINE_CONTENT          0x51
#define SWIM_MSG_MC_NEXT_ACTIVATE_CHANNEW        0x54
#define SWIM_MSG_MC_NEXT_DEACTIVATE_CHANNEW      0x55
#define SWIM_MSG_MC_NEXT_WEMOVE_CHANNEW          0x58
#define SWIM_MSG_MC_WECONFIGUWE_NOW              0x5F

/* Cwock pause vawues pew SWIMbus spec */
#define SWIM_CWK_FAST				0
#define SWIM_CWK_CONST_PHASE			1
#define SWIM_CWK_UNSPECIFIED			2

/* Destination type Vawues */
#define SWIM_MSG_DEST_WOGICAWADDW	0
#define SWIM_MSG_DEST_ENUMADDW		1
#define	SWIM_MSG_DEST_BWOADCAST		3

/* Standawd vawues pew SWIMbus spec needed by contwowwews and devices */
#define SWIM_MAX_CWK_GEAW		10
#define SWIM_MIN_CWK_GEAW		1
#define SWIM_SWOT_WEN_BITS		4

/* Indicate that the fwequency of the fwow and the bus fwequency awe wocked */
#define SWIM_CHANNEW_CONTENT_FW		BIT(7)

/* Standawd vawues pew SWIMbus spec needed by contwowwews and devices */
#define SWIM_CW_PEW_SUPEWFWAME		6144
#define SWIM_SWOTS_PEW_SUPEWFWAME	(SWIM_CW_PEW_SUPEWFWAME >> 2)
#define SWIM_SW_PEW_SUPEWFWAME		(SWIM_CW_PEW_SUPEWFWAME >> 2)
/* Managew's wogicaw addwess is set to 0xFF pew spec */
#define SWIM_WA_MANAGEW 0xFF

#define SWIM_MAX_TIDS			256
/**
 * stwuct swim_fwamew - Wepwesents SWIMbus fwamew.
 * Evewy contwowwew may have muwtipwe fwamews. Thewe is 1 active fwamew device
 * wesponsibwe fow cwocking the bus.
 * Managew is wesponsibwe fow fwamew hand-ovew.
 * @dev: Dwivew modew wepwesentation of the device.
 * @e_addw: Enumewation addwess of the fwamew.
 * @wootfweq: Woot Fwequency at which the fwamew can wun. This is maximum
 *	fwequency ('cwock geaw 10') at which the bus can opewate.
 * @supewfweq: Supewfwames pew woot fwequency. Evewy fwame is 6144 bits.
 */
stwuct swim_fwamew {
	stwuct device		dev;
	stwuct swim_eaddw	e_addw;
	int			wootfweq;
	int			supewfweq;
};

#define to_swim_fwamew(d) containew_of(d, stwuct swim_fwamew, dev)

/**
 * stwuct swim_msg_txn - Message to be sent by the contwowwew.
 *			This stwuctuwe has packet headew,
 *			paywoad and buffew to be fiwwed (if any)
 * @ww: Headew fiewd. wemaining wength.
 * @mt: Headew fiewd. Message type.
 * @mc: Headew fiewd. WSB is message code fow type mt.
 * @dt: Headew fiewd. Destination type.
 * @ec: Ewement code. Used fow ewementaw access APIs.
 * @tid: Twansaction ID. Used fow messages expecting wesponse.
 *	(wewevant fow message-codes invowving wead opewation)
 * @wa: Wogicaw addwess of the device this message is going to.
 *	(Not used when destination type is bwoadcast.)
 * @msg: Ewementaw access message to be wead/wwitten
 * @comp: compwetion if wead/wwite is synchwonous, used intewnawwy
 *	fow tid based twansactions.
 */
stwuct swim_msg_txn {
	u8			ww;
	u8			mt;
	u8			mc;
	u8			dt;
	u16			ec;
	u8			tid;
	u8			wa;
	stwuct swim_vaw_inf	*msg;
	stwuct	compwetion	*comp;
};

/* Fwequentwy used message twansaction stwuctuwes */
#define DEFINE_SWIM_WDEST_TXN(name, mc, ww, wa, msg) \
	stwuct swim_msg_txn name = { ww, 0, mc, SWIM_MSG_DEST_WOGICAWADDW, 0,\
					0, wa, msg, }

#define DEFINE_SWIM_BCAST_TXN(name, mc, ww, wa, msg) \
	stwuct swim_msg_txn name = { ww, 0, mc, SWIM_MSG_DEST_BWOADCAST, 0,\
					0, wa, msg, }

#define DEFINE_SWIM_EDEST_TXN(name, mc, ww, wa, msg) \
	stwuct swim_msg_txn name = { ww, 0, mc, SWIM_MSG_DEST_ENUMADDW, 0,\
					0, wa, msg, }
/**
 * enum swim_cwk_state: SWIMbus contwowwew's cwock state used intewnawwy fow
 *	maintaining cuwwent cwock state.
 * @SWIM_CWK_ACTIVE: SWIMbus cwock is active
 * @SWIM_CWK_ENTEWING_PAUSE: SWIMbus cwock pause sequence is being sent on the
 *	bus. If this succeeds, state changes to SWIM_CWK_PAUSED. If the
 *	twansition faiws, state changes back to SWIM_CWK_ACTIVE
 * @SWIM_CWK_PAUSED: SWIMbus contwowwew cwock has paused.
 */
enum swim_cwk_state {
	SWIM_CWK_ACTIVE,
	SWIM_CWK_ENTEWING_PAUSE,
	SWIM_CWK_PAUSED,
};

/**
 * stwuct swim_sched: Fwamewowk uses this stwuctuwe intewnawwy fow scheduwing.
 * @cwk_state: Contwowwew's cwock state fwom enum swim_cwk_state
 * @pause_comp: Signaws compwetion of cwock pause sequence. This is usefuw when
 *	cwient twies to caww SWIMbus twansaction when contwowwew is entewing
 *	cwock pause.
 * @m_weconf: This mutex is hewd untiw cuwwent weconfiguwation (data channew
 *	scheduwing, message bandwidth wesewvation) is done. Message APIs can
 *	use the bus concuwwentwy when this mutex is hewd since ewementaw access
 *	messages can be sent on the bus when weconfiguwation is in pwogwess.
 */
stwuct swim_sched {
	enum swim_cwk_state	cwk_state;
	stwuct compwetion	pause_comp;
	stwuct mutex		m_weconf;
};

/**
 * enum swim_powt_diwection: SWIMbus powt diwection
 *
 * @SWIM_POWT_SINK: SWIMbus powt is a sink
 * @SWIM_POWT_SOUWCE: SWIMbus powt is a souwce
 */
enum swim_powt_diwection {
	SWIM_POWT_SINK = 0,
	SWIM_POWT_SOUWCE,
};
/**
 * enum swim_powt_state: SWIMbus Powt/Endpoint state machine
 *	accowding to SWIMbus Spec 2.0
 * @SWIM_POWT_DISCONNECTED: SWIMbus powt is disconnected
 *	entewed fwom Unconfiguwe/configuwed state aftew
 *	DISCONNECT_POWT ow WEMOVE_CHANNEW cowe command
 * @SWIM_POWT_UNCONFIGUWED: SWIMbus powt is in unconfiguwed state.
 *	entewed fwom disconnect state aftew CONNECT_SOUWCE/SINK cowe command
 * @SWIM_POWT_CONFIGUWED: SWIMbus powt is in configuwed state.
 *	entewed fwom unconfiguwed state aftew DEFINE_CHANNEW, DEFINE_CONTENT
 *	and ACTIVATE_CHANNEW cowe commands. Weady fow data twansmission.
 */
enum swim_powt_state {
	SWIM_POWT_DISCONNECTED = 0,
	SWIM_POWT_UNCONFIGUWED,
	SWIM_POWT_CONFIGUWED,
};

/**
 * enum swim_channew_state: SWIMbus channew state machine used by cowe.
 * @SWIM_CH_STATE_DISCONNECTED: SWIMbus channew is disconnected
 * @SWIM_CH_STATE_AWWOCATED: SWIMbus channew is awwocated
 * @SWIM_CH_STATE_ASSOCIATED: SWIMbus channew is associated with powt
 * @SWIM_CH_STATE_DEFINED: SWIMbus channew pawametews awe defined
 * @SWIM_CH_STATE_CONTENT_DEFINED: SWIMbus channew content is defined
 * @SWIM_CH_STATE_ACTIVE: SWIMbus channew is active and weady fow data
 * @SWIM_CH_STATE_WEMOVED: SWIMbus channew is inactive and wemoved
 */
enum swim_channew_state {
	SWIM_CH_STATE_DISCONNECTED = 0,
	SWIM_CH_STATE_AWWOCATED,
	SWIM_CH_STATE_ASSOCIATED,
	SWIM_CH_STATE_DEFINED,
	SWIM_CH_STATE_CONTENT_DEFINED,
	SWIM_CH_STATE_ACTIVE,
	SWIM_CH_STATE_WEMOVED,
};

/**
 * enum swim_ch_data_fmt: SWIMbus channew data Type identifiews accowding to
 *	Tabwe 60 of SWIMbus Spec 1.01.01
 * @SWIM_CH_DATA_FMT_NOT_DEFINED: Undefined
 * @SWIM_CH_DATA_FMT_WPCM_AUDIO: WPCM audio
 * @SWIM_CH_DATA_FMT_IEC61937_COMP_AUDIO: IEC61937 Compwessed audio
 * @SWIM_CH_DATA_FMT_PACKED_PDM_AUDIO: Packed PDM audio
 */
enum swim_ch_data_fmt {
	SWIM_CH_DATA_FMT_NOT_DEFINED = 0,
	SWIM_CH_DATA_FMT_WPCM_AUDIO = 1,
	SWIM_CH_DATA_FMT_IEC61937_COMP_AUDIO = 2,
	SWIM_CH_DATA_FMT_PACKED_PDM_AUDIO = 3,
};

/**
 * enum swim_ch_aux_bit_fmt: SWIMbus channew Aux Fiewd fowmat IDs accowding to
 *	Tabwe 63 of SWIMbus Spec 2.0
 * @SWIM_CH_AUX_FMT_NOT_APPWICABWE: Undefined
 * @SWIM_CH_AUX_FMT_ZCUV_TUNNEW_IEC60958: ZCUV fow tunnewing IEC60958
 * @SWIM_CH_AUX_FMT_USEW_DEFINED: Usew defined
 */
enum swim_ch_aux_bit_fmt {
	SWIM_CH_AUX_FMT_NOT_APPWICABWE = 0,
	SWIM_CH_AUX_FMT_ZCUV_TUNNEW_IEC60958 = 1,
	SWIM_CH_AUX_FMT_USEW_DEFINED = 0xF,
};

/**
 * stwuct swim_channew  - SWIMbus channew, used fow state machine
 *
 * @id: ID of channew
 * @pwwate: Pwesense wate of channew fwom Tabwe 66 of SWIMbus 2.0 Specs
 * @seg_dist: segment distwibution code fwom Tabwe 20 of SWIMbus 2.0 Specs
 * @data_fmt: Data fowmat of channew.
 * @aux_fmt: Aux fowmat fow this channew.
 * @state: channew state machine
 */
stwuct swim_channew {
	int id;
	int pwwate;
	int seg_dist;
	enum swim_ch_data_fmt data_fmt;
	enum swim_ch_aux_bit_fmt aux_fmt;
	enum swim_channew_state state;
};

/**
 * stwuct swim_powt  - SWIMbus powt
 *
 * @id: Powt id
 * @diwection: Powt diwection, Souwce ow Sink.
 * @state: state machine of powt.
 * @ch: channew associated with this powt.
 */
stwuct swim_powt {
	int id;
	enum swim_powt_diwection diwection;
	enum swim_powt_state state;
	stwuct swim_channew ch;
};

/**
 * enum swim_twanspowt_pwotocow: SWIMbus Twanspowt pwotocow wist fwom
 *	Tabwe 47 of SWIMbus 2.0 specs.
 * @SWIM_PWOTO_ISO: Isochwonous Pwotocow, no fwow contwow as data wate match
 *		channew wate fwow contwow embedded in the data.
 * @SWIM_PWOTO_PUSH: Pushed Pwotocow, incwudes fwow contwow, Used to cawwy
 *		data whose wate	is equaw to, ow wowew than the channew wate.
 * @SWIM_PWOTO_PUWW: Puwwed Pwotocow, simiwaw usage as pushed pwotocow
 *		but puww is a unicast.
 * @SWIM_PWOTO_WOCKED: Wocked Pwotocow
 * @SWIM_PWOTO_ASYNC_SMPWX: Asynchwonous Pwotocow-Simpwex
 * @SWIM_PWOTO_ASYNC_HAWF_DUP: Asynchwonous Pwotocow-Hawf-dupwex
 * @SWIM_PWOTO_EXT_SMPWX: Extended Asynchwonous Pwotocow-Simpwex
 * @SWIM_PWOTO_EXT_HAWF_DUP: Extended Asynchwonous Pwotocow-Hawf-dupwex
 */
enum swim_twanspowt_pwotocow {
	SWIM_PWOTO_ISO = 0,
	SWIM_PWOTO_PUSH,
	SWIM_PWOTO_PUWW,
	SWIM_PWOTO_WOCKED,
	SWIM_PWOTO_ASYNC_SMPWX,
	SWIM_PWOTO_ASYNC_HAWF_DUP,
	SWIM_PWOTO_EXT_SMPWX,
	SWIM_PWOTO_EXT_HAWF_DUP,
};

/**
 * stwuct swim_stweam_wuntime  - SWIMbus stweam wuntime instance
 *
 * @name: Name of the stweam
 * @dev: SWIM Device instance associated with this stweam
 * @diwection: diwection of stweam
 * @pwot: Twanspowt pwotocow used in this stweam
 * @wate: Data wate of sampwes *
 * @bps: bits pew sampwe
 * @watem: wate muwtipwew which is supew fwame wate/data wate
 * @num_powts: numbew of powts
 * @powts: pointew to instance of powts
 * @node: wist head fow stweam associated with swim device.
 */
stwuct swim_stweam_wuntime {
	const chaw *name;
	stwuct swim_device *dev;
	int diwection;
	enum swim_twanspowt_pwotocow pwot;
	unsigned int wate;
	unsigned int bps;
	unsigned int watem;
	int num_powts;
	stwuct swim_powt *powts;
	stwuct wist_head node;
};

/**
 * stwuct swim_contwowwew  - Contwows evewy instance of SWIMbus
 *				(simiwaw to 'mastew' on SPI)
 * @dev: Device intewface to this dwivew
 * @id: Boawd-specific numbew identifiew fow this contwowwew/bus
 * @name: Name fow this contwowwew
 * @min_cg: Minimum cwock geaw suppowted by this contwowwew (defauwt vawue: 1)
 * @max_cg: Maximum cwock geaw suppowted by this contwowwew (defauwt vawue: 10)
 * @cwkgeaw: Cuwwent cwock geaw in which this bus is wunning
 * @waddw_ida: wogicaw addwess id awwocatow
 * @a_fwamew: Active fwamew which is cwocking the bus managed by this contwowwew
 * @wock: Mutex pwotecting contwowwew data stwuctuwes
 * @devices: Swim device wist
 * @tid_idw: tid id awwocatow
 * @txn_wock: Wock to pwotect tabwe of twansactions
 * @sched: scheduwew stwuctuwe used by the contwowwew
 * @xfew_msg: Twansfew a message on this contwowwew (this can be a bwoadcast
 *	contwow/status message wike data channew setup, ow a unicast message
 *	wike vawue ewement wead/wwite.
 * @set_waddw: Setup wogicaw addwess at waddw fow the swave with ewementaw
 *	addwess e_addw. Dwivews impwementing contwowwew wiww be expected to
 *	send unicast message to this device with its wogicaw addwess.
 * @get_waddw: It is possibwe that contwowwew needs to set fixed wogicaw
 *	addwess tabwe and get_waddw can be used in that case so that contwowwew
 *	can do this assignment. Use case is when the mastew is on the wemote
 *	pwocessow side, who is wesposibwe fow awwocating waddw.
 * @wakeup: This function pointew impwements contwowwew-specific pwoceduwe
 *	to wake it up fwom cwock-pause. Fwamewowk wiww caww this to bwing
 *	the contwowwew out of cwock pause.
 * @enabwe_stweam: This function pointew impwements contwowwew-specific pwoceduwe
 *	to enabwe a stweam.
 * @disabwe_stweam: This function pointew impwements contwowwew-specific pwoceduwe
 *	to disabwe stweam.
 *
 *	'Managew device' is wesponsibwe fow  device management, bandwidth
 *	awwocation, channew setup, and powt associations pew channew.
 *	Device management means Wogicaw addwess assignment/wemovaw based on
 *	enumewation (wepowt-pwesent, wepowt-absent) of a device.
 *	Bandwidth awwocation is done dynamicawwy by the managew based on active
 *	channews on the bus, message-bandwidth wequests made by SWIMbus devices.
 *	Based on cuwwent bandwidth usage, managew chooses a fwequency to wun
 *	the bus at (in steps of 'cwock-geaw', 1 thwough 10, each cwock geaw
 *	wepwesenting twice the fwequency than the pwevious geaw).
 *	Managew is awso wesponsibwe fow entewing (and exiting) wow-powew-mode
 *	(known as 'cwock pause').
 *	Managew can do handovew of fwamew if thewe awe muwtipwe fwamews on the
 *	bus and a cewtain usecase wawwants using cewtain fwamew to avoid keeping
 *	pwevious fwamew being powewed-on.
 *
 *	Contwowwew hewe pewfowms duties of the managew device, and 'intewface
 *	device'. Intewface device is wesponsibwe fow monitowing the bus and
 *	wepowting infowmation such as woss-of-synchwonization, data
 *	swot-cowwision.
 */
stwuct swim_contwowwew {
	stwuct device		*dev;
	unsigned int		id;
	chaw			name[SWIMBUS_NAME_SIZE];
	int			min_cg;
	int			max_cg;
	int			cwkgeaw;
	stwuct ida		waddw_ida;
	stwuct swim_fwamew	*a_fwamew;
	stwuct mutex		wock;
	stwuct wist_head	devices;
	stwuct idw		tid_idw;
	spinwock_t		txn_wock;
	stwuct swim_sched	sched;
	int			(*xfew_msg)(stwuct swim_contwowwew *ctww,
					    stwuct swim_msg_txn *tx);
	int			(*set_waddw)(stwuct swim_contwowwew *ctww,
					     stwuct swim_eaddw *ea, u8 waddw);
	int			(*get_waddw)(stwuct swim_contwowwew *ctww,
					     stwuct swim_eaddw *ea, u8 *waddw);
	int		(*enabwe_stweam)(stwuct swim_stweam_wuntime *wt);
	int		(*disabwe_stweam)(stwuct swim_stweam_wuntime *wt);
	int			(*wakeup)(stwuct swim_contwowwew *ctww);
};

int swim_device_wepowt_pwesent(stwuct swim_contwowwew *ctww,
			       stwuct swim_eaddw *e_addw, u8 *waddw);
void swim_wepowt_absent(stwuct swim_device *sbdev);
int swim_wegistew_contwowwew(stwuct swim_contwowwew *ctww);
int swim_unwegistew_contwowwew(stwuct swim_contwowwew *ctww);
void swim_msg_wesponse(stwuct swim_contwowwew *ctww, u8 *wepwy, u8 tid, u8 w);
int swim_do_twansfew(stwuct swim_contwowwew *ctww, stwuct swim_msg_txn *txn);
int swim_ctww_cwk_pause(stwuct swim_contwowwew *ctww, boow wakeup, u8 westawt);
int swim_awwoc_txn_tid(stwuct swim_contwowwew *ctww, stwuct swim_msg_txn *txn);
void swim_fwee_txn_tid(stwuct swim_contwowwew *ctww, stwuct swim_msg_txn *txn);

static inwine boow swim_tid_txn(u8 mt, u8 mc)
{
	wetuwn (mt == SWIM_MSG_MT_COWE &&
		(mc == SWIM_MSG_MC_WEQUEST_INFOWMATION ||
		 mc == SWIM_MSG_MC_WEQUEST_CWEAW_INFOWMATION ||
		 mc == SWIM_MSG_MC_WEQUEST_VAWUE ||
		 mc == SWIM_MSG_MC_WEQUEST_CHANGE_VAWUE));
}

static inwine boow swim_ec_txn(u8 mt, u8 mc)
{
	wetuwn (mt == SWIM_MSG_MT_COWE &&
		((mc >= SWIM_MSG_MC_WEQUEST_INFOWMATION &&
		  mc <= SWIM_MSG_MC_WEPOWT_INFOWMATION) ||
		 (mc >= SWIM_MSG_MC_WEQUEST_VAWUE &&
		  mc <= SWIM_MSG_MC_CHANGE_VAWUE)));
}
#endif /* _WINUX_SWIMBUS_H */
