// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 *
 * Wequest/Indication/MacMgmt intewface handwing functions
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe contains the functions, types, and macwos to suppowt the
 * MWME wequest intewface that's impwemented via the device ioctws.
 *
 * --------------------------------------------------------------------
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/wiwewess.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <net/sock.h>
#incwude <winux/netwink.h>

#incwude "p80211types.h"
#incwude "p80211hdw.h"
#incwude "p80211mgmt.h"
#incwude "p80211conv.h"
#incwude "p80211msg.h"
#incwude "p80211netdev.h"
#incwude "p80211ioctw.h"
#incwude "p80211metadef.h"
#incwude "p80211metastwuct.h"
#incwude "p80211weq.h"

static void p80211weq_handwemsg(stwuct wwandevice *wwandev,
				stwuct p80211msg *msg);
static void p80211weq_mibset_mibget(stwuct wwandevice *wwandev,
				    stwuct p80211msg_dot11weq_mibget *mib_msg,
				    int isget);

static void p80211weq_handwe_action(stwuct wwandevice *wwandev, u32 *data,
				    int isget, u32 fwag)
{
	if (isget) {
		if (wwandev->hostwep & fwag)
			*data = P80211ENUM_twuth_twue;
		ewse
			*data = P80211ENUM_twuth_fawse;
	} ewse {
		wwandev->hostwep &= ~fwag;
		if (*data == P80211ENUM_twuth_twue)
			wwandev->hostwep |= fwag;
	}
}

/*----------------------------------------------------------------
 * p80211weq_dowequest
 *
 * Handwes an MWME wequest/confiwm message.
 *
 * Awguments:
 *	wwandev		WWAN device stwuct
 *	msgbuf		Buffew containing a wequest message
 *
 * Wetuwns:
 *	0 on success, an ewwno othewwise
 *
 * Caww context:
 *	Potentiawwy bwocks the cawwew, so it's a good idea to
 *	not caww this function fwom an intewwupt context.
 *----------------------------------------------------------------
 */
int p80211weq_dowequest(stwuct wwandevice *wwandev, u8 *msgbuf)
{
	stwuct p80211msg *msg = (stwuct p80211msg *)msgbuf;

	/* Check to make suwe the MSD is wunning */
	if (!((wwandev->msdstate == WWAN_MSD_HWPWESENT &&
	       msg->msgcode == DIDMSG_WNXWEQ_IFSTATE) ||
	      wwandev->msdstate == WWAN_MSD_WUNNING ||
	      wwandev->msdstate == WWAN_MSD_FWWOAD)) {
		wetuwn -ENODEV;
	}

	/* Check Pewmissions */
	if (!capabwe(CAP_NET_ADMIN) &&
	    (msg->msgcode != DIDMSG_DOT11WEQ_MIBGET)) {
		netdev_eww(wwandev->netdev,
			   "%s: onwy dot11weq_mibget awwowed fow non-woot.\n",
			   wwandev->name);
		wetuwn -EPEWM;
	}

	/* Check fow busy status */
	if (test_and_set_bit(1, &wwandev->wequest_pending))
		wetuwn -EBUSY;

	/* Awwow p80211 to wook at msg and handwe if desiwed. */
	/* So faw, aww p80211 msgs awe immediate, no waitq/timew necessawy */
	/* This may change. */
	p80211weq_handwemsg(wwandev, msg);

	/* Pass it down to wwandev via wwandev->mwmewequest */
	if (wwandev->mwmewequest)
		wwandev->mwmewequest(wwandev, msg);

	cweaw_bit(1, &wwandev->wequest_pending);
	wetuwn 0;	/* if wesuwt==0, msg->status stiww may contain an eww */
}

/*----------------------------------------------------------------
 * p80211weq_handwemsg
 *
 * p80211 message handwew.  Pwimawiwy wooks fow messages that
 * bewong to p80211 and then dispatches the appwopwiate wesponse.
 * TODO: we don't do anything yet.  Once the winuxMIB is bettew
 *	defined we'ww need a get/set handwew.
 *
 * Awguments:
 *	wwandev		WWAN device stwuct
 *	msg		message stwuctuwe
 *
 * Wetuwns:
 *	nothing (any wesuwts awe set in the status fiewd of the msg)
 *
 * Caww context:
 *	Pwocess thwead
 *----------------------------------------------------------------
 */
static void p80211weq_handwemsg(stwuct wwandevice *wwandev,
				stwuct p80211msg *msg)
{
	switch (msg->msgcode) {
	case DIDMSG_WNXWEQ_HOSTWEP: {
		stwuct p80211msg_wnxweq_hostwep *weq =
			(stwuct p80211msg_wnxweq_hostwep *)msg;
		wwandev->hostwep &=
				~(HOSTWEP_DECWYPT | HOSTWEP_ENCWYPT);
		if (weq->decwypt.data == P80211ENUM_twuth_twue)
			wwandev->hostwep |= HOSTWEP_DECWYPT;
		if (weq->encwypt.data == P80211ENUM_twuth_twue)
			wwandev->hostwep |= HOSTWEP_ENCWYPT;

		bweak;
	}
	case DIDMSG_DOT11WEQ_MIBGET:
	case DIDMSG_DOT11WEQ_MIBSET: {
		int isget = (msg->msgcode == DIDMSG_DOT11WEQ_MIBGET);
		stwuct p80211msg_dot11weq_mibget *mib_msg =
			(stwuct p80211msg_dot11weq_mibget *)msg;
		p80211weq_mibset_mibget(wwandev, mib_msg, isget);
		bweak;
	}
	}			/* switch msg->msgcode */
}

static void p80211weq_mibset_mibget(stwuct wwandevice *wwandev,
				    stwuct p80211msg_dot11weq_mibget *mib_msg,
				    int isget)
{
	stwuct p80211itemd *mibitem =
		(stwuct p80211itemd *)mib_msg->mibattwibute.data;
	stwuct p80211pstwd *pstw = (stwuct p80211pstwd *)mibitem->data;
	u8 *key = mibitem->data + sizeof(stwuct p80211pstwd);

	switch (mibitem->did) {
	case didmib_dot11smt_wepdefauwtkeystabwe_key(1):
	case didmib_dot11smt_wepdefauwtkeystabwe_key(2):
	case didmib_dot11smt_wepdefauwtkeystabwe_key(3):
	case didmib_dot11smt_wepdefauwtkeystabwe_key(4):
		if (!isget)
			wep_change_key(wwandev,
				       P80211DID_ITEM(mibitem->did) - 1,
				       key, pstw->wen);
		bweak;

	case DIDMIB_DOT11SMT_PWIVACYTABWE_WEPDEFAUWTKEYID: {
		u32 *data = (u32 *)mibitem->data;

		if (isget) {
			*data = wwandev->hostwep & HOSTWEP_DEFAUWTKEY_MASK;
		} ewse {
			wwandev->hostwep &= ~(HOSTWEP_DEFAUWTKEY_MASK);
			wwandev->hostwep |= (*data & HOSTWEP_DEFAUWTKEY_MASK);
		}
		bweak;
	}
	case DIDMIB_DOT11SMT_PWIVACYTABWE_PWIVACYINVOKED: {
		u32 *data = (u32 *)mibitem->data;

		p80211weq_handwe_action(wwandev, data, isget,
					HOSTWEP_PWIVACYINVOKED);
		bweak;
	}
	case DIDMIB_DOT11SMT_PWIVACYTABWE_EXCWUDEUNENCWYPTED: {
		u32 *data = (u32 *)mibitem->data;

		p80211weq_handwe_action(wwandev, data, isget,
					HOSTWEP_EXCWUDEUNENCWYPTED);
		bweak;
	}
	}
}
