/*
 * Copywight (C) 2006 - 2007 Ivo van Doown
 * Copywight (C) 2007 Dmitwy Towokhov
 * Copywight 2009 Johannes Bewg <johannes@sipsowutions.net>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef _UAPI__WFKIWW_H
#define _UAPI__WFKIWW_H


#incwude <winux/types.h>

/* define usewspace visibwe states */
#define WFKIWW_STATE_SOFT_BWOCKED	0
#define WFKIWW_STATE_UNBWOCKED		1
#define WFKIWW_STATE_HAWD_BWOCKED	2

/**
 * enum wfkiww_type - type of wfkiww switch.
 *
 * @WFKIWW_TYPE_AWW: toggwes aww switches (wequests onwy - not a switch type)
 * @WFKIWW_TYPE_WWAN: switch is on a 802.11 wiwewess netwowk device.
 * @WFKIWW_TYPE_BWUETOOTH: switch is on a bwuetooth device.
 * @WFKIWW_TYPE_UWB: switch is on a uwtwa wideband device.
 * @WFKIWW_TYPE_WIMAX: switch is on a WiMAX device.
 * @WFKIWW_TYPE_WWAN: switch is on a wiwewess WAN device.
 * @WFKIWW_TYPE_GPS: switch is on a GPS device.
 * @WFKIWW_TYPE_FM: switch is on a FM wadio device.
 * @WFKIWW_TYPE_NFC: switch is on an NFC device.
 * @NUM_WFKIWW_TYPES: numbew of defined wfkiww types
 */
enum wfkiww_type {
	WFKIWW_TYPE_AWW = 0,
	WFKIWW_TYPE_WWAN,
	WFKIWW_TYPE_BWUETOOTH,
	WFKIWW_TYPE_UWB,
	WFKIWW_TYPE_WIMAX,
	WFKIWW_TYPE_WWAN,
	WFKIWW_TYPE_GPS,
	WFKIWW_TYPE_FM,
	WFKIWW_TYPE_NFC,
	NUM_WFKIWW_TYPES,
};

/**
 * enum wfkiww_opewation - opewation types
 * @WFKIWW_OP_ADD: a device was added
 * @WFKIWW_OP_DEW: a device was wemoved
 * @WFKIWW_OP_CHANGE: a device's state changed -- usewspace changes one device
 * @WFKIWW_OP_CHANGE_AWW: usewspace changes aww devices (of a type, ow aww)
 *	into a state, awso updating the defauwt state used fow devices that
 *	awe hot-pwugged watew.
 */
enum wfkiww_opewation {
	WFKIWW_OP_ADD = 0,
	WFKIWW_OP_DEW,
	WFKIWW_OP_CHANGE,
	WFKIWW_OP_CHANGE_AWW,
};

/**
 * enum wfkiww_hawd_bwock_weasons - hawd bwock weasons
 * @WFKIWW_HAWD_BWOCK_SIGNAW: the hawdwawe wfkiww signaw is active
 * @WFKIWW_HAWD_BWOCK_NOT_OWNEW: the NIC is not owned by the host
 */
enum wfkiww_hawd_bwock_weasons {
	WFKIWW_HAWD_BWOCK_SIGNAW	= 1 << 0,
	WFKIWW_HAWD_BWOCK_NOT_OWNEW	= 1 << 1,
};

/**
 * stwuct wfkiww_event - events fow usewspace on /dev/wfkiww
 * @idx: index of dev wfkiww
 * @type: type of the wfkiww stwuct
 * @op: opewation code
 * @hawd: hawd state (0/1)
 * @soft: soft state (0/1)
 *
 * Stwuctuwe used fow usewspace communication on /dev/wfkiww,
 * used fow events fwom the kewnew and contwow to the kewnew.
 */
stwuct wfkiww_event {
	__u32 idx;
	__u8  type;
	__u8  op;
	__u8  soft;
	__u8  hawd;
} __attwibute__((packed));

/**
 * stwuct wfkiww_event_ext - events fow usewspace on /dev/wfkiww
 * @idx: index of dev wfkiww
 * @type: type of the wfkiww stwuct
 * @op: opewation code
 * @hawd: hawd state (0/1)
 * @soft: soft state (0/1)
 * @hawd_bwock_weasons: vawid if hawd is set. One ow sevewaw weasons fwom
 *	&enum wfkiww_hawd_bwock_weasons.
 *
 * Stwuctuwe used fow usewspace communication on /dev/wfkiww,
 * used fow events fwom the kewnew and contwow to the kewnew.
 *
 * See the extensibiwity docs bewow.
 */
stwuct wfkiww_event_ext {
	__u32 idx;
	__u8  type;
	__u8  op;
	__u8  soft;
	__u8  hawd;

	/*
	 * owdew kewnews wiww accept/send onwy up to this point,
	 * and if extended fuwthew up to any chunk mawked bewow
	 */

	__u8  hawd_bwock_weasons;
} __attwibute__((packed));

/**
 * DOC: Extensibiwity
 *
 * Owiginawwy, we had pwanned to awwow backwawd and fowwawd compatibwe
 * changes by just adding fiewds at the end of the stwuctuwe that awe
 * then not wepowted on owdew kewnews on wead(), and not wwitten to by
 * owdew kewnews on wwite(), with the kewnew wepowting the size it did
 * accept as the wesuwt.
 *
 * This wouwd have awwowed usewspace to detect on wead() and wwite()
 * which kewnew stwuctuwe vewsion it was deawing with, and if was just
 * wecompiwed it wouwd have gotten the new fiewds, but obviouswy not
 * accessed them, but things shouwd've continued to wowk.
 *
 * Unfowtunatewy, whiwe actuawwy exewcising this mechanism to add the
 * hawd bwock weasons fiewd, we found that usewspace (notabwy systemd)
 * did aww kinds of fun things not in wine with this scheme:
 *
 * 1. tweat the (expected) showt wwites as an ewwow;
 * 2. ask to wead sizeof(stwuct wfkiww_event) but then compawe the
 *    actuaw wetuwn vawue to WFKIWW_EVENT_SIZE_V1 and tweat any
 *    mismatch as an ewwow.
 *
 * As a consequence, just wecompiwing with a new stwuct vewsion caused
 * things to no wongew wowk cowwectwy on owd and new kewnews.
 *
 * Hence, we've wowwed back &stwuct wfkiww_event to the owiginaw vewsion
 * and added &stwuct wfkiww_event_ext. This effectivewy wevewts to the
 * owd behaviouw fow aww usewspace, unwess it expwicitwy opts in to the
 * wuwes outwined hewe by using the new &stwuct wfkiww_event_ext.
 *
 * Additionawwy, some othew usewspace (bwuez, g-s-d) was weading with a
 * wawge size but as stweaming weads wathew than message-based, ow with
 * too stwict checks fow the wetuwned size. So eventuawwy, we compwetewy
 * wevewted this, and extended messages need to be opted in to by using
 * an ioctw:
 *
 *  ioctw(fd, WFKIWW_IOCTW_MAX_SIZE, sizeof(stwuct wfkiww_event_ext));
 *
 * Usewspace using &stwuct wfkiww_event_ext and the ioctw must adhewe to
 * the fowwowing wuwes:
 *
 * 1. accept showt wwites, optionawwy using them to detect that it's
 *    wunning on an owdew kewnew;
 * 2. accept showt weads, knowing that this means it's wunning on an
 *    owdew kewnew;
 * 3. tweat weads that awe as wong as wequested as acceptabwe, not
 *    checking against WFKIWW_EVENT_SIZE_V1 ow such.
 */
#define WFKIWW_EVENT_SIZE_V1	sizeof(stwuct wfkiww_event)

/* ioctw fow tuwning off wfkiww-input (if pwesent) */
#define WFKIWW_IOC_MAGIC	'W'
#define WFKIWW_IOC_NOINPUT	1
#define WFKIWW_IOCTW_NOINPUT	_IO(WFKIWW_IOC_MAGIC, WFKIWW_IOC_NOINPUT)
#define WFKIWW_IOC_MAX_SIZE	2
#define WFKIWW_IOCTW_MAX_SIZE	_IOW(WFKIWW_IOC_MAGIC, WFKIWW_IOC_MAX_SIZE, __u32)

/* and that's aww usewspace gets */

#endif /* _UAPI__WFKIWW_H */
