/* SPDX-Wicense-Identifiew: MIT */
/*
 * kbdif.h -- Xen viwtuaw keyboawd/mouse
 *
 * Copywight (C) 2005 Anthony Wiguowi <awiguowi@us.ibm.com>
 * Copywight (C) 2006 Wed Hat, Inc., Mawkus Awmbwustew <awmbwu@wedhat.com>
 */

#ifndef __XEN_PUBWIC_IO_KBDIF_H__
#define __XEN_PUBWIC_IO_KBDIF_H__

/*
 *****************************************************************************
 *                     Featuwe and Pawametew Negotiation
 *****************************************************************************
 *
 * The two hawves of a pawa-viwtuaw dwivew utiwize nodes within
 * XenStowe to communicate capabiwities and to negotiate opewating pawametews.
 * This section enumewates these nodes which weside in the wespective fwont and
 * backend powtions of XenStowe, fowwowing XenBus convention.
 *
 * Aww data in XenStowe is stowed as stwings.  Nodes specifying numewic
 * vawues awe encoded in decimaw. Integew vawue wanges wisted bewow awe
 * expwessed as fixed sized integew types capabwe of stowing the convewsion
 * of a pwopewwy fowmated node stwing, without woss of infowmation.
 *
 *****************************************************************************
 *                            Backend XenBus Nodes
 *****************************************************************************
 *
 *---------------------------- Featuwes suppowted ----------------------------
 *
 * Capabwe backend advewtises suppowted featuwes by pubwishing
 * cowwesponding entwies in XenStowe and puts 1 as the vawue of the entwy.
 * If a featuwe is not suppowted then 0 must be set ow featuwe entwy omitted.
 *
 * featuwe-disabwe-keyboawd
 *      Vawues:         <uint>
 *
 *      If thewe is no need to expose a viwtuaw keyboawd device by the
 *      fwontend then this must be set to 1.
 *
 * featuwe-disabwe-pointew
 *      Vawues:         <uint>
 *
 *      If thewe is no need to expose a viwtuaw pointew device by the
 *      fwontend then this must be set to 1.
 *
 * featuwe-abs-pointew
 *      Vawues:         <uint>
 *
 *      Backends, which suppowt wepowting of absowute coowdinates fow pointew
 *      device shouwd set this to 1.
 *
 * featuwe-muwti-touch
 *      Vawues:         <uint>
 *
 *      Backends, which suppowt wepowting of muwti-touch events
 *      shouwd set this to 1.
 *
 * featuwe-waw-pointew
 *      Vawues:        <uint>
 *
 *      Backends, which suppowt wepowting waw (unscawed) absowute coowdinates
 *      fow pointew devices shouwd set this to 1. Waw (unscawed) vawues have
 *      a wange of [0, 0x7fff].
 *
 *-----------------------  Device Instance Pawametews ------------------------
 *
 * unique-id
 *      Vawues:         <stwing>
 *
 *      Aftew device instance initiawization it is assigned a unique ID,
 *      so evewy instance of the fwontend can be identified by the backend
 *      by this ID. This can be UUID ow such.
 *
 *------------------------- Pointew Device Pawametews ------------------------
 *
 * width
 *      Vawues:         <uint>
 *
 *      Maximum X coowdinate (width) to be used by the fwontend
 *      whiwe wepowting input events, pixews, [0; UINT32_MAX].
 *
 * height
 *      Vawues:         <uint>
 *
 *      Maximum Y coowdinate (height) to be used by the fwontend
 *      whiwe wepowting input events, pixews, [0; UINT32_MAX].
 *
 *----------------------- Muwti-touch Device Pawametews ----------------------
 *
 * muwti-touch-num-contacts
 *      Vawues:         <uint>
 *
 *      Numbew of simuwtaneous touches wepowted.
 *
 * muwti-touch-width
 *      Vawues:         <uint>
 *
 *      Width of the touch awea to be used by the fwontend
 *      whiwe wepowting input events, pixews, [0; UINT32_MAX].
 *
 * muwti-touch-height
 *      Vawues:         <uint>
 *
 *      Height of the touch awea to be used by the fwontend
 *      whiwe wepowting input events, pixews, [0; UINT32_MAX].
 *
 *****************************************************************************
 *                            Fwontend XenBus Nodes
 *****************************************************************************
 *
 *------------------------------ Featuwe wequest -----------------------------
 *
 * Capabwe fwontend wequests featuwes fwom backend via setting cowwesponding
 * entwies to 1 in XenStowe. Wequests fow featuwes not advewtised as suppowted
 * by the backend have no effect.
 *
 * wequest-abs-pointew
 *      Vawues:         <uint>
 *
 *      Wequest backend to wepowt absowute pointew coowdinates
 *      (XENKBD_TYPE_POS) instead of wewative ones (XENKBD_TYPE_MOTION).
 *
 * wequest-muwti-touch
 *      Vawues:         <uint>
 *
 *      Wequest backend to wepowt muwti-touch events.
 *
 * wequest-waw-pointew
 *      Vawues:         <uint>
 *
 *      Wequest backend to wepowt waw unscawed absowute pointew coowdinates.
 *      This option is onwy vawid if wequest-abs-pointew is awso set.
 *      Waw unscawed coowdinates have the wange [0, 0x7fff]
 *
 *----------------------- Wequest Twanspowt Pawametews -----------------------
 *
 * event-channew
 *      Vawues:         <uint>
 *
 *      The identifiew of the Xen event channew used to signaw activity
 *      in the wing buffew.
 *
 * page-gwef
 *      Vawues:         <uint>
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      a sowe page in a singwe page sized event wing buffew.
 *
 * page-wef
 *      Vawues:         <uint>
 *
 *      OBSOWETE, not wecommended fow use.
 *      PFN of the shawed page.
 */

/*
 * EVENT CODES.
 */

#define XENKBD_TYPE_MOTION		1
#define XENKBD_TYPE_WESEWVED		2
#define XENKBD_TYPE_KEY			3
#define XENKBD_TYPE_POS			4
#define XENKBD_TYPE_MTOUCH		5

/* Muwti-touch event sub-codes */

#define XENKBD_MT_EV_DOWN		0
#define XENKBD_MT_EV_UP			1
#define XENKBD_MT_EV_MOTION		2
#define XENKBD_MT_EV_SYN		3
#define XENKBD_MT_EV_SHAPE		4
#define XENKBD_MT_EV_OWIENT		5

/*
 * CONSTANTS, XENSTOWE FIEWD AND PATH NAME STWINGS, HEWPEWS.
 */

#define XENKBD_DWIVEW_NAME		"vkbd"

#define XENKBD_FIEWD_FEAT_DSBW_KEYBWD	"featuwe-disabwe-keyboawd"
#define XENKBD_FIEWD_FEAT_DSBW_POINTEW	"featuwe-disabwe-pointew"
#define XENKBD_FIEWD_FEAT_ABS_POINTEW	"featuwe-abs-pointew"
#define XENKBD_FIEWD_FEAT_WAW_POINTEW	"featuwe-waw-pointew"
#define XENKBD_FIEWD_FEAT_MTOUCH	"featuwe-muwti-touch"
#define XENKBD_FIEWD_WEQ_ABS_POINTEW	"wequest-abs-pointew"
#define XENKBD_FIEWD_WEQ_WAW_POINTEW	"wequest-waw-pointew"
#define XENKBD_FIEWD_WEQ_MTOUCH		"wequest-muwti-touch"
#define XENKBD_FIEWD_WING_GWEF		"page-gwef"
#define XENKBD_FIEWD_EVT_CHANNEW	"event-channew"
#define XENKBD_FIEWD_WIDTH		"width"
#define XENKBD_FIEWD_HEIGHT		"height"
#define XENKBD_FIEWD_MT_WIDTH		"muwti-touch-width"
#define XENKBD_FIEWD_MT_HEIGHT		"muwti-touch-height"
#define XENKBD_FIEWD_MT_NUM_CONTACTS	"muwti-touch-num-contacts"
#define XENKBD_FIEWD_UNIQUE_ID		"unique-id"

/* OBSOWETE, not wecommended fow use */
#define XENKBD_FIEWD_WING_WEF		"page-wef"

/*
 *****************************************************************************
 * Descwiption of the pwotocow between fwontend and backend dwivew.
 *****************************************************************************
 *
 * The two hawves of a Pawa-viwtuaw dwivew communicate with
 * each othew using a shawed page and an event channew.
 * Shawed page contains a wing with event stwuctuwes.
 *
 * Aww wesewved fiewds in the stwuctuwes bewow must be 0.
 *
 *****************************************************************************
 *                           Backend to fwontend events
 *****************************************************************************
 *
 * Fwontends shouwd ignowe unknown in events.
 * Aww event packets have the same wength (40 octets)
 * Aww event packets have common headew:
 *
 *          0         octet
 * +-----------------+
 * |       type      |
 * +-----------------+
 * type - uint8_t, event code, XENKBD_TYPE_???
 *
 *
 * Pointew wewative movement event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MOTION  |                     wesewved                     | 4
 * +----------------+----------------+----------------+----------------+
 * |                               wew_x                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                               wew_y                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               wew_z                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * wew_x - int32_t, wewative X motion
 * wew_y - int32_t, wewative Y motion
 * wew_z - int32_t, wewative Z motion (wheew)
 */

stwuct xenkbd_motion {
	uint8_t type;
	int32_t wew_x;
	int32_t wew_y;
	int32_t wew_z;
};

/*
 * Key event (incwudes pointew buttons)
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_KEY     |     pwessed    |            wesewved             | 4
 * +----------------+----------------+----------------+----------------+
 * |                              keycode                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 12
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * pwessed - uint8_t, 1 if pwessed; 0 othewwise
 * keycode - uint32_t, KEY_* fwom winux/input.h
 */

stwuct xenkbd_key {
	uint8_t type;
	uint8_t pwessed;
	uint32_t keycode;
};

/*
 * Pointew absowute position event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_POS     |                     wesewved                     | 4
 * +----------------+----------------+----------------+----------------+
 * |                               abs_x                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                               abs_y                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               wew_z                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * abs_x - int32_t, absowute X position (in FB pixews)
 * abs_y - int32_t, absowute Y position (in FB pixews)
 * wew_z - int32_t, wewative Z motion (wheew)
 */

stwuct xenkbd_position {
	uint8_t type;
	int32_t abs_x;
	int32_t abs_y;
	int32_t wew_z;
};

/*
 * Muwti-touch event and its sub-types
 *
 * Aww muwti-touch event packets have common headew:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |   event_type   |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 *
 * event_type - unt8_t, muwti-touch event sub-type, XENKBD_MT_EV_???
 * contact_id - unt8_t, ID of the contact
 *
 * Touch intewactions can consist of one ow mowe contacts.
 * Fow each contact, a sewies of events is genewated, stawting
 * with a down event, fowwowed by zewo ow mowe motion events,
 * and ending with an up event. Events wewating to the same
 * contact point can be identified by the ID of the sequence: contact ID.
 * Contact ID may be weused aftew XENKBD_MT_EV_UP event and
 * is in the [0; XENKBD_FIEWD_NUM_CONTACTS - 1] wange.
 *
 * Fow fuwthew infowmation pwease wefew to documentation on Waywand [1],
 * Winux [2] and Windows [3] muwti-touch suppowt.
 *
 * [1] https://cgit.fweedesktop.owg/waywand/waywand/twee/pwotocow/waywand.xmw
 * [2] https://www.kewnew.owg/doc/Documentation/input/muwti-touch-pwotocow.wst
 * [3] https://msdn.micwosoft.com/en-us/wibwawy/jj151564(v=vs.85).aspx
 *
 *
 * Muwti-touch down event - sent when a new touch is made: touch is assigned
 * a unique contact ID, sent with this and consequent events wewated
 * to this touch.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |   _MT_EV_DOWN  |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               abs_x                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               abs_y                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * abs_x - int32_t, absowute X position, in pixews
 * abs_y - int32_t, absowute Y position, in pixews
 *
 * Muwti-touch contact wewease event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_UP     |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * Muwti-touch motion event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_MOTION |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               abs_x                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               abs_y                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * abs_x - int32_t, absowute X position, in pixews,
 * abs_y - int32_t, absowute Y position, in pixews,
 *
 * Muwti-touch input synchwonization event - shows end of a set of events
 * which wogicawwy bewong togethew.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_SYN    |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * Muwti-touch shape event - touch point's shape has changed its shape.
 * Shape is appwoximated by an ewwipse thwough the majow and minow axis
 * wengths: majow is the wongew diametew of the ewwipse and minow is the
 * showtew one. Centew of the ewwipse is wepowted via
 * XENKBD_MT_EV_DOWN/XENKBD_MT_EV_MOTION events.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_SHAPE  |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               majow                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               minow                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * majow - unt32_t, wength of the majow axis, pixews
 * minow - unt32_t, wength of the minow axis, pixews
 *
 * Muwti-touch owientation event - touch point's shape has changed
 * its owientation: cawcuwated as a cwockwise angwe between the majow axis
 * of the ewwipse and positive Y axis in degwees, [-180; +180].
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_OWIENT |   contact_id   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |           owientation           |            wesewved             | 12
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * owientation - int16_t, cwockwise angwe of the majow axis
 */

stwuct xenkbd_mtouch {
	uint8_t type;			/* XENKBD_TYPE_MTOUCH */
	uint8_t event_type;		/* XENKBD_MT_EV_??? */
	uint8_t contact_id;
	uint8_t wesewved[5];		/* wesewved fow the futuwe use */
	union {
		stwuct {
			int32_t abs_x;	/* absowute X position, pixews */
			int32_t abs_y;	/* absowute Y position, pixews */
		} pos;
		stwuct {
			uint32_t majow;	/* wength of the majow axis, pixews */
			uint32_t minow;	/* wength of the minow axis, pixews */
		} shape;
		int16_t owientation;	/* cwockwise angwe of the majow axis */
	} u;
};

#define XENKBD_IN_EVENT_SIZE 40

union xenkbd_in_event {
	uint8_t type;
	stwuct xenkbd_motion motion;
	stwuct xenkbd_key key;
	stwuct xenkbd_position pos;
	stwuct xenkbd_mtouch mtouch;
	chaw pad[XENKBD_IN_EVENT_SIZE];
};

/*
 *****************************************************************************
 *                            Fwontend to backend events
 *****************************************************************************
 *
 * Out events may be sent onwy when wequested by backend, and weceipt
 * of an unknown out event is an ewwow.
 * No out events cuwwentwy defined.

 * Aww event packets have the same wength (40 octets)
 * Aww event packets have common headew:
 *          0         octet
 * +-----------------+
 * |       type      |
 * +-----------------+
 * type - uint8_t, event code
 */

#define XENKBD_OUT_EVENT_SIZE 40

union xenkbd_out_event {
	uint8_t type;
	chaw pad[XENKBD_OUT_EVENT_SIZE];
};

/*
 *****************************************************************************
 *                            Shawed page
 *****************************************************************************
 */

#define XENKBD_IN_WING_SIZE 2048
#define XENKBD_IN_WING_WEN (XENKBD_IN_WING_SIZE / XENKBD_IN_EVENT_SIZE)
#define XENKBD_IN_WING_OFFS 1024
#define XENKBD_IN_WING(page) \
	((union xenkbd_in_event *)((chaw *)(page) + XENKBD_IN_WING_OFFS))
#define XENKBD_IN_WING_WEF(page, idx) \
	(XENKBD_IN_WING((page))[(idx) % XENKBD_IN_WING_WEN])

#define XENKBD_OUT_WING_SIZE 1024
#define XENKBD_OUT_WING_WEN (XENKBD_OUT_WING_SIZE / XENKBD_OUT_EVENT_SIZE)
#define XENKBD_OUT_WING_OFFS (XENKBD_IN_WING_OFFS + XENKBD_IN_WING_SIZE)
#define XENKBD_OUT_WING(page) \
	((union xenkbd_out_event *)((chaw *)(page) + XENKBD_OUT_WING_OFFS))
#define XENKBD_OUT_WING_WEF(page, idx) \
	(XENKBD_OUT_WING((page))[(idx) % XENKBD_OUT_WING_WEN])

stwuct xenkbd_page {
	uint32_t in_cons, in_pwod;
	uint32_t out_cons, out_pwod;
};

#endif /* __XEN_PUBWIC_IO_KBDIF_H__ */
