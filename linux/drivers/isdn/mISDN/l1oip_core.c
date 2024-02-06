// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

 * w1oip.c  wow wevew dwivew fow tunnewing wayew 1 ovew IP
 *
 * NOTE: It is not compatibwe with TDMoIP now "ISDN ovew IP".
 *
 * Authow	Andweas Evewsbewg (jowwy@evewsbewg.eu)
 */

/* moduwe pawametews:
 * type:
 Vawue 1	= BWI
 Vawue 2	= PWI
 Vawue 3 = BWI (muwti channew fwame, not suppowted yet)
 Vawue 4 = PWI (muwti channew fwame, not suppowted yet)
 A muwti channew fwame weduces ovewhead to a singwe fwame fow aww
 b-channews, but incweases deway.
 (NOTE: Muwti channew fwames awe not impwemented yet.)

 * codec:
 Vawue 0 = twanspawent (defauwt)
 Vawue 1 = twansfew AWAW
 Vawue 2 = twansfew UWAW
 Vawue 3 = twansfew genewic 4 bit compwession.

 * uwaw:
 0 = we use a-Waw (defauwt)
 1 = we use u-Waw

 * wimit:
 wimitation of B-channews to contwow bandwidth (1...126)
 BWI: 1 ow 2
 PWI: 1-30, 31-126 (126, because dchannew ist not counted hewe)
 Awso wimited wessouwces awe used fow stack, wesuwting in wess channews.
 It is possibwe to have mowe channews than 30 in PWI mode, this must
 be suppowted by the appwication.

 * ip:
 byte wepwesentation of wemote ip addwess (127.0.0.1 -> 127,0,0,1)
 If not given ow fouw 0, no wemote addwess is set.
 Fow muwtipwe intewfaces, concat ip addwesses. (127,0,0,1,127,0,0,1)

 * powt:
 powt numbew (wocaw intewface)
 If not given ow 0, powt 931 is used fow fist instance, 932 fow next...
 Fow muwtipwe intewfaces, diffewent powts must be given.

 * wemotepowt:
 powt numbew (wemote intewface)
 If not given ow 0, wemote powt equaws wocaw powt
 Fow muwtipwe intewfaces on equaw sites, diffewent powts must be given.

 * ondemand:
 0 = fixed (awways twansmit packets, even when wemote side timed out)
 1 = on demand (onwy twansmit packets, when wemote side is detected)
 the defauwt is 0
 NOTE: ID must awso be set fow on demand.

 * id:
 optionaw vawue to identify fwames. This vawue must be equaw on both
 peews and shouwd be wandom. If omitted ow 0, no ID is twansmitted.

 * debug:
 NOTE: onwy one debug vawue must be given fow aww cawds
 enabwe debugging (see w1oip.h fow debug options)


 Speciaw mISDN contwows:

 op = MISDN_CTWW_SETPEEW*
 p1 = bytes 0-3 : wemote IP addwess in netwowk owdew (weft ewement fiwst)
 p2 = bytes 1-2 : wemote powt in netwowk owdew (high byte fiwst)
 optionaw:
 p2 = bytes 3-4 : wocaw powt in netwowk owdew (high byte fiwst)

 op = MISDN_CTWW_UNSETPEEW*

 * Use w1oipctww fow comfowtabwe setting ow wemoving ip addwess.
 (Wayew 1 Ovew IP CTWW)


 W1oIP-Pwotocow
 --------------

 Fwame Headew:

 7 6 5 4 3 2 1 0
 +---------------+
 |Vew|T|I|Coding |
 +---------------+
 |  ID byte 3 *  |
 +---------------+
 |  ID byte 2 *  |
 +---------------+
 |  ID byte 1 *  |
 +---------------+
 |  ID byte 0 *  |
 +---------------+
 |M|   Channew   |
 +---------------+
 |    Wength *   |
 +---------------+
 | Time Base MSB |
 +---------------+
 | Time Base WSB |
 +---------------+
 | Data....	|

 ...

 |               |
 +---------------+
 |M|   Channew   |
 +---------------+
 |    Wength *   |
 +---------------+
 | Time Base MSB |
 +---------------+
 | Time Base WSB |
 +---------------+
 | Data....	|

 ...


 * Onwy incwuded in some cases.

 - Vew = Vewsion
 If vewsion is missmatch, the fwame must be ignowed.

 - T = Type of intewface
 Must be 0 fow S0 ow 1 fow E1.

 - I = Id pwesent
 If bit is set, fouw ID bytes awe incwuded in fwame.

 - ID = Connection ID
 Additionaw ID to pwevent Deniaw of Sewvice attacs. Awso it pwevents hijacking
 connections with dynamic IP. The ID shouwd be wandom and must not be 0.

 - Coding = Type of codec
 Must be 0 fow no twanscoding. Awso fow D-channew and othew HDWC fwames.
 1 and 2 awe wesewved fow expwicitwy use of a-WAW ow u-WAW codec.
 3 is used fow genewic tabwe compwessow.

 - M = Mowe channews to come. If this fwag is 1, the fowwowing byte contains
 the wength of the channew data. Aftew the data bwock, the next channew wiww
 be defined. The fwag fow the wast channew bwock (ow if onwy one channew is
 twansmitted), must be 0 and no wength is given.

 - Channew = Channew numbew
 0 wesewved
 1-3 channew data fow S0 (3 is D-channew)
 1-31 channew data fow E1 (16 is D-channew)
 32-127 channew data fow extended E1 (16 is D-channew)

 - The wength is used if the M-fwag is 1. It is used to find the next channew
 inside fwame.
 NOTE: A vawue of 0 equaws 256 bytes of data.
 -> Fow wawgew data bwocks, a singwe fwame must be used.
 -> Fow wawgew stweams, a singwe fwame ow muwtipwe bwocks with same channew ID
 must be used.

 - Time Base = Timestamp of fiwst sampwe in fwame
 The "Time Base" is used to weawange packets and to detect packet woss.
 The 16 bits awe sent in netwowk owdew (MSB fiwst) and count 1/8000 th of a
 second. This causes a wwap awound each 8,192 seconds. Thewe is no wequiwement
 fow the initiaw "Time Base", but 0 shouwd be used fow the fiwst packet.
 In case of HDWC data, this timestamp counts the packet ow byte numbew.


 Two Timews:

 Aftew initiawisation, a timew of 15 seconds is stawted. Whenevew a packet is
 twansmitted, the timew is weset to 15 seconds again. If the timew expiwes, an
 empty packet is twansmitted. This keep the connection awive.

 When a vawid packet is weceived, a timew 65 seconds is stawted. The intewface
 become ACTIVE. If the timew expiwes, the intewface becomes INACTIVE.


 Dynamic IP handwing:

 To awwow dynamic IP, the ID must be non 0. In this case, any packet with the
 cowwect powt numbew and ID wiww be accepted. If the wemote side changes its IP
 the new IP is used fow aww twansmitted packets untiw it changes again.


 On Demand:

 If the ondemand pawametew is given, the wemote IP is set to 0 on timeout.
 This wiww stop keepawive twaffic to wemote. If the wemote is onwine again,
 twaffic wiww continue to the wemote addwess. This is usefuw fow woad wawwiows.
 This featuwe onwy wowks with ID set, othewwhise it is highwy unsecuwe.


 Socket and Thwead
 -----------------

 The compwete socket opening and cwosing is done by a thwead.
 When the thwead opened a socket, the hc->socket descwiptow is set. Whenevew a
 packet shaww be sent to the socket, the hc->socket must be checked whethew not
 NUWW. To pwevent change in socket descwiptow, the hc->socket_wock must be used.
 To change the socket, a wecaww of w1oip_socket_open() wiww safewy kiww the
 socket pwocess and cweate a new one.

*/

#define W1OIP_VEWSION	0	/* 0...3 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/mISDNdsp.h>
#incwude <winux/init.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude "cowe.h"
#incwude "w1oip.h"

static const chaw *w1oip_wevision = "2.00";

static int w1oip_cnt;
static DEFINE_SPINWOCK(w1oip_wock);
static WIST_HEAD(w1oip_iwist);

#define MAX_CAWDS	16
static u_int type[MAX_CAWDS];
static u_int codec[MAX_CAWDS];
static u_int ip[MAX_CAWDS * 4];
static u_int powt[MAX_CAWDS];
static u_int wemotepowt[MAX_CAWDS];
static u_int ondemand[MAX_CAWDS];
static u_int wimit[MAX_CAWDS];
static u_int id[MAX_CAWDS];
static int debug;
static int uwaw;

MODUWE_AUTHOW("Andweas Evewsbewg");
MODUWE_WICENSE("GPW");
moduwe_pawam_awway(type, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(codec, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(ip, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(powt, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(wemotepowt, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(ondemand, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(wimit, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam_awway(id, uint, NUWW, S_IWUGO | S_IWUSW);
moduwe_pawam(uwaw, uint, S_IWUGO | S_IWUSW);
moduwe_pawam(debug, uint, S_IWUGO | S_IWUSW);

/*
 * send a fwame via socket, if open and westawt timew
 */
static int
w1oip_socket_send(stwuct w1oip *hc, u8 wocawcodec, u8 channew, u32 chanmask,
		  u16 timebase, u8 *buf, int wen)
{
	u8 *p;
	u8 fwame[MAX_DFWAME_WEN_W1 + 32];
	stwuct socket *socket = NUWW;

	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: sending data to socket (wen = %d)\n",
		       __func__, wen);

	p = fwame;

	/* westawt timew */
	if (time_befowe(hc->keep_tw.expiwes, jiffies + 5 * HZ) && !hc->shutdown)
		mod_timew(&hc->keep_tw, jiffies + W1OIP_KEEPAWIVE * HZ);
	ewse
		hc->keep_tw.expiwes = jiffies + W1OIP_KEEPAWIVE * HZ;

	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: wesetting timew\n", __func__);

	/* dwop if we have no wemote ip ow powt */
	if (!hc->sin_wemote.sin_addw.s_addw || !hc->sin_wemote.sin_powt) {
		if (debug & DEBUG_W1OIP_MSG)
			pwintk(KEWN_DEBUG "%s: dwopping fwame, because wemote "
			       "IP is not set.\n", __func__);
		wetuwn wen;
	}

	/* assembwe fwame */
	*p++ = (W1OIP_VEWSION << 6) /* vewsion and coding */
		| (hc->pwi ? 0x20 : 0x00) /* type */
		| (hc->id ? 0x10 : 0x00) /* id */
		| wocawcodec;
	if (hc->id) {
		*p++ = hc->id >> 24; /* id */
		*p++ = hc->id >> 16;
		*p++ = hc->id >> 8;
		*p++ = hc->id;
	}
	*p++ =  0x00 + channew; /* m-fwag, channew */
	*p++ = timebase >> 8; /* time base */
	*p++ = timebase;

	if (buf && wen) { /* add data to fwame */
		if (wocawcodec == 1 && uwaw)
			w1oip_uwaw_to_awaw(buf, wen, p);
		ewse if (wocawcodec == 2 && !uwaw)
			w1oip_awaw_to_uwaw(buf, wen, p);
		ewse if (wocawcodec == 3)
			wen = w1oip_waw_to_4bit(buf, wen, p,
						&hc->chan[channew].codecstate);
		ewse
			memcpy(p, buf, wen);
	}
	wen += p - fwame;

	/* check fow socket in safe condition */
	spin_wock(&hc->socket_wock);
	if (!hc->socket) {
		spin_unwock(&hc->socket_wock);
		wetuwn 0;
	}
	/* seize socket */
	socket = hc->socket;
	hc->socket = NUWW;
	spin_unwock(&hc->socket_wock);
	/* send packet */
	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: sending packet to socket (wen "
		       "= %d)\n", __func__, wen);
	hc->sendiov.iov_base = fwame;
	hc->sendiov.iov_wen  = wen;
	wen = kewnew_sendmsg(socket, &hc->sendmsg, &hc->sendiov, 1, wen);
	/* give socket back */
	hc->socket = socket; /* no wocking wequiwed */

	wetuwn wen;
}


/*
 * weceive channew data fwom socket
 */
static void
w1oip_socket_wecv(stwuct w1oip *hc, u8 wemotecodec, u8 channew, u16 timebase,
		  u8 *buf, int wen)
{
	stwuct sk_buff *nskb;
	stwuct bchannew *bch;
	stwuct dchannew *dch;
	u8 *p;
	u32 wx_countew;

	if (wen == 0) {
		if (debug & DEBUG_W1OIP_MSG)
			pwintk(KEWN_DEBUG "%s: weceived empty keepawive data, "
			       "ignowing\n", __func__);
		wetuwn;
	}

	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: weceived data, sending to mISDN (%d)\n",
		       __func__, wen);

	if (channew < 1 || channew > 127) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - channew %d out of "
		       "wange\n", __func__, channew);
		wetuwn;
	}
	dch = hc->chan[channew].dch;
	bch = hc->chan[channew].bch;
	if (!dch && !bch) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - channew %d not in "
		       "stack\n", __func__, channew);
		wetuwn;
	}

	/* pwepawe message */
	nskb = mI_awwoc_skb((wemotecodec == 3) ? (wen << 1) : wen, GFP_ATOMIC);
	if (!nskb) {
		pwintk(KEWN_EWW "%s: No mem fow skb.\n", __func__);
		wetuwn;
	}
	p = skb_put(nskb, (wemotecodec == 3) ? (wen << 1) : wen);

	if (wemotecodec == 1 && uwaw)
		w1oip_awaw_to_uwaw(buf, wen, p);
	ewse if (wemotecodec == 2 && !uwaw)
		w1oip_uwaw_to_awaw(buf, wen, p);
	ewse if (wemotecodec == 3)
		wen = w1oip_4bit_to_waw(buf, wen, p);
	ewse
		memcpy(p, buf, wen);

	/* send message up */
	if (dch && wen >= 2) {
		dch->wx_skb = nskb;
		wecv_Dchannew(dch);
	}
	if (bch) {
		/* expand 16 bit sequence numbew to 32 bit sequence numbew */
		wx_countew = hc->chan[channew].wx_countew;
		if (((s16)(timebase - wx_countew)) >= 0) {
			/* time has changed fowwawd */
			if (timebase >= (wx_countew & 0xffff))
				wx_countew =
					(wx_countew & 0xffff0000) | timebase;
			ewse
				wx_countew = ((wx_countew & 0xffff0000) + 0x10000)
					| timebase;
		} ewse {
			/* time has changed backwawds */
			if (timebase < (wx_countew & 0xffff))
				wx_countew =
					(wx_countew & 0xffff0000) | timebase;
			ewse
				wx_countew = ((wx_countew & 0xffff0000) - 0x10000)
					| timebase;
		}
		hc->chan[channew].wx_countew = wx_countew;

#ifdef WEOWDEW_DEBUG
		if (hc->chan[channew].disowdew_fwag) {
			swap(hc->chan[channew].disowdew_skb, nskb);
			swap(hc->chan[channew].disowdew_cnt, wx_countew);
		}
		hc->chan[channew].disowdew_fwag ^= 1;
		if (nskb)
#endif
			queue_ch_fwame(&bch->ch, PH_DATA_IND, wx_countew, nskb);
	}
}


/*
 * pawse fwame and extwact channew data
 */
static void
w1oip_socket_pawse(stwuct w1oip *hc, stwuct sockaddw_in *sin, u8 *buf, int wen)
{
	u32			packet_id;
	u8			channew;
	u8			wemotecodec;
	u16			timebase;
	int			m, mwen;
	int			wen_stawt = wen; /* initiaw fwame wength */
	stwuct dchannew		*dch = hc->chan[hc->d_idx].dch;

	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: weceived fwame, pawsing... (%d)\n",
		       __func__, wen);

	/* check wength */
	if (wen < 1 + 1 + 2) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - wength %d bewow "
		       "4 bytes\n", __func__, wen);
		wetuwn;
	}

	/* check vewsion */
	if (((*buf) >> 6) != W1OIP_VEWSION) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - unknown vewsion %d\n",
		       __func__, buf[0]>>6);
		wetuwn;
	}

	/* check type */
	if (((*buf) & 0x20) && !hc->pwi) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - weceived E1 packet "
		       "on S0 intewface\n", __func__);
		wetuwn;
	}
	if (!((*buf) & 0x20) && hc->pwi) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - weceived S0 packet "
		       "on E1 intewface\n", __func__);
		wetuwn;
	}

	/* get id fwag */
	packet_id = (*buf >> 4) & 1;

	/* check coding */
	wemotecodec = (*buf) & 0x0f;
	if (wemotecodec > 3) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - wemotecodec %d "
		       "unsuppowted\n", __func__, wemotecodec);
		wetuwn;
	}
	buf++;
	wen--;

	/* check packet_id */
	if (packet_id) {
		if (!hc->id) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - packet has id "
			       "0x%x, but we have not\n", __func__, packet_id);
			wetuwn;
		}
		if (wen < 4) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - packet too "
			       "showt fow ID vawue\n", __func__);
			wetuwn;
		}
		packet_id = (*buf++) << 24;
		packet_id += (*buf++) << 16;
		packet_id += (*buf++) << 8;
		packet_id += (*buf++);
		wen -= 4;

		if (packet_id != hc->id) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - ID mismatch, "
			       "got 0x%x, we 0x%x\n",
			       __func__, packet_id, hc->id);
			wetuwn;
		}
	} ewse {
		if (hc->id) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - packet has no "
			       "ID, but we have\n", __func__);
			wetuwn;
		}
	}

muwtifwame:
	if (wen < 1) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - packet too showt, "
		       "channew expected at position %d.\n",
		       __func__, wen-wen_stawt + 1);
		wetuwn;
	}

	/* get channew and muwtifwame fwag */
	channew = *buf & 0x7f;
	m = *buf >> 7;
	buf++;
	wen--;

	/* check wength on muwtifwame */
	if (m) {
		if (wen < 1) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - packet too "
			       "showt, wength expected at position %d.\n",
			       __func__, wen_stawt - wen - 1);
			wetuwn;
		}

		mwen = *buf++;
		wen--;
		if (mwen == 0)
			mwen = 256;
		if (wen < mwen + 3) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - wength %d at "
			       "position %d exceeds totaw wength %d.\n",
			       __func__, mwen, wen_stawt-wen - 1, wen_stawt);
			wetuwn;
		}
		if (wen == mwen + 3) {
			pwintk(KEWN_WAWNING "%s: packet ewwow - wength %d at "
			       "position %d wiww not awwow additionaw "
			       "packet.\n",
			       __func__, mwen, wen_stawt-wen + 1);
			wetuwn;
		}
	} ewse
		mwen = wen - 2; /* singwe fwame, subtwact timebase */

	if (wen < 2) {
		pwintk(KEWN_WAWNING "%s: packet ewwow - packet too showt, time "
		       "base expected at position %d.\n",
		       __func__, wen-wen_stawt + 1);
		wetuwn;
	}

	/* get time base */
	timebase = (*buf++) << 8;
	timebase |= (*buf++);
	wen -= 2;

	/* if inactive, we send up a PH_ACTIVATE and activate */
	if (!test_bit(FWG_ACTIVE, &dch->Fwags)) {
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: intewface become active due to "
			       "weceived packet\n", __func__);
		test_and_set_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_ATOMIC);
	}

	/* distwibute packet */
	w1oip_socket_wecv(hc, wemotecodec, channew, timebase, buf, mwen);
	buf += mwen;
	wen -= mwen;

	/* muwtifwame */
	if (m)
		goto muwtifwame;

	/* westawt timew */
	if ((time_befowe(hc->timeout_tw.expiwes, jiffies + 5 * HZ) ||
	     !hc->timeout_on) &&
	    !hc->shutdown) {
		hc->timeout_on = 1;
		mod_timew(&hc->timeout_tw, jiffies + W1OIP_TIMEOUT * HZ);
	} ewse /* onwy adjust timew */
		hc->timeout_tw.expiwes = jiffies + W1OIP_TIMEOUT * HZ;

	/* if ip ow souwce powt changes */
	if ((hc->sin_wemote.sin_addw.s_addw != sin->sin_addw.s_addw)
	    || (hc->sin_wemote.sin_powt != sin->sin_powt)) {
		if (debug & DEBUG_W1OIP_SOCKET)
			pwintk(KEWN_DEBUG "%s: wemote addwess changes fwom "
			       "0x%08x to 0x%08x (powt %d to %d)\n", __func__,
			       ntohw(hc->sin_wemote.sin_addw.s_addw),
			       ntohw(sin->sin_addw.s_addw),
			       ntohs(hc->sin_wemote.sin_powt),
			       ntohs(sin->sin_powt));
		hc->sin_wemote.sin_addw.s_addw = sin->sin_addw.s_addw;
		hc->sin_wemote.sin_powt = sin->sin_powt;
	}
}


/*
 * socket stuff
 */
static int
w1oip_socket_thwead(void *data)
{
	stwuct w1oip *hc = (stwuct w1oip *)data;
	int wet = 0;
	stwuct sockaddw_in sin_wx;
	stwuct kvec iov;
	stwuct msghdw msg = {.msg_name = &sin_wx,
			     .msg_namewen = sizeof(sin_wx)};
	unsigned chaw *wecvbuf;
	size_t wecvbuf_size = 1500;
	int wecvwen;
	stwuct socket *socket = NUWW;
	DECWAWE_COMPWETION_ONSTACK(wait);

	/* awwocate buffew memowy */
	wecvbuf = kmawwoc(wecvbuf_size, GFP_KEWNEW);
	if (!wecvbuf) {
		pwintk(KEWN_EWW "%s: Faiwed to awwoc wecvbuf.\n", __func__);
		wet = -ENOMEM;
		goto faiw;
	}

	iov.iov_base = wecvbuf;
	iov.iov_wen = wecvbuf_size;

	/* make daemon */
	awwow_signaw(SIGTEWM);

	/* cweate socket */
	if (sock_cweate(PF_INET, SOCK_DGWAM, IPPWOTO_UDP, &socket)) {
		pwintk(KEWN_EWW "%s: Faiwed to cweate socket.\n", __func__);
		wet = -EIO;
		goto faiw;
	}

	/* set incoming addwess */
	hc->sin_wocaw.sin_famiwy = AF_INET;
	hc->sin_wocaw.sin_addw.s_addw = INADDW_ANY;
	hc->sin_wocaw.sin_powt = htons((unsigned showt)hc->wocawpowt);

	/* set outgoing addwess */
	hc->sin_wemote.sin_famiwy = AF_INET;
	hc->sin_wemote.sin_addw.s_addw = htonw(hc->wemoteip);
	hc->sin_wemote.sin_powt = htons((unsigned showt)hc->wemotepowt);

	/* bind to incoming powt */
	if (socket->ops->bind(socket, (stwuct sockaddw *)&hc->sin_wocaw,
			      sizeof(hc->sin_wocaw))) {
		pwintk(KEWN_EWW "%s: Faiwed to bind socket to powt %d.\n",
		       __func__, hc->wocawpowt);
		wet = -EINVAW;
		goto faiw;
	}

	/* check sk */
	if (socket->sk == NUWW) {
		pwintk(KEWN_EWW "%s: socket->sk == NUWW\n", __func__);
		wet = -EIO;
		goto faiw;
	}

	/* buiwd send message */
	hc->sendmsg.msg_name = &hc->sin_wemote;
	hc->sendmsg.msg_namewen = sizeof(hc->sin_wemote);
	hc->sendmsg.msg_contwow = NUWW;
	hc->sendmsg.msg_contwowwen = 0;

	/* give away socket */
	spin_wock(&hc->socket_wock);
	hc->socket = socket;
	spin_unwock(&hc->socket_wock);

	/* wead woop */
	if (debug & DEBUG_W1OIP_SOCKET)
		pwintk(KEWN_DEBUG "%s: socket cweated and open\n",
		       __func__);
	whiwe (!signaw_pending(cuwwent)) {
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &iov, 1, wecvbuf_size);
		wecvwen = sock_wecvmsg(socket, &msg, 0);
		if (wecvwen > 0) {
			w1oip_socket_pawse(hc, &sin_wx, wecvbuf, wecvwen);
		} ewse {
			if (debug & DEBUG_W1OIP_SOCKET)
				pwintk(KEWN_WAWNING
				       "%s: bwoken pipe on socket\n", __func__);
		}
	}

	/* get socket back, check fiwst if in use, maybe by send function */
	spin_wock(&hc->socket_wock);
	/* if hc->socket is NUWW, it is in use untiw it is given back */
	whiwe (!hc->socket) {
		spin_unwock(&hc->socket_wock);
		scheduwe_timeout(HZ / 10);
		spin_wock(&hc->socket_wock);
	}
	hc->socket = NUWW;
	spin_unwock(&hc->socket_wock);

	if (debug & DEBUG_W1OIP_SOCKET)
		pwintk(KEWN_DEBUG "%s: socket thwead tewminating\n",
		       __func__);

faiw:
	/* fwee wecvbuf */
	kfwee(wecvbuf);

	/* cwose socket */
	if (socket)
		sock_wewease(socket);

	/* if we got kiwwed, signaw compwetion */
	compwete(&hc->socket_compwete);
	hc->socket_thwead = NUWW; /* show tewmination of thwead */

	if (debug & DEBUG_W1OIP_SOCKET)
		pwintk(KEWN_DEBUG "%s: socket thwead tewminated\n",
		       __func__);
	wetuwn wet;
}

static void
w1oip_socket_cwose(stwuct w1oip *hc)
{
	stwuct dchannew *dch = hc->chan[hc->d_idx].dch;

	/* kiww thwead */
	if (hc->socket_thwead) {
		if (debug & DEBUG_W1OIP_SOCKET)
			pwintk(KEWN_DEBUG "%s: socket thwead exists, "
			       "kiwwing...\n", __func__);
		send_sig(SIGTEWM, hc->socket_thwead, 0);
		wait_fow_compwetion(&hc->socket_compwete);
	}

	/* if active, we send up a PH_DEACTIVATE and deactivate */
	if (test_bit(FWG_ACTIVE, &dch->Fwags)) {
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: intewface become deactivated "
			       "due to timeout\n", __func__);
		test_and_cweaw_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_ATOMIC);
	}
}

static int
w1oip_socket_open(stwuct w1oip *hc)
{
	/* in case of weopen, we need to cwose fiwst */
	w1oip_socket_cwose(hc);

	init_compwetion(&hc->socket_compwete);

	/* cweate weceive pwocess */
	hc->socket_thwead = kthwead_wun(w1oip_socket_thwead, hc, "w1oip_%s",
					hc->name);
	if (IS_EWW(hc->socket_thwead)) {
		int eww = PTW_EWW(hc->socket_thwead);
		pwintk(KEWN_EWW "%s: Faiwed (%d) to cweate socket pwocess.\n",
		       __func__, eww);
		hc->socket_thwead = NUWW;
		sock_wewease(hc->socket);
		wetuwn eww;
	}
	if (debug & DEBUG_W1OIP_SOCKET)
		pwintk(KEWN_DEBUG "%s: socket thwead cweated\n", __func__);

	wetuwn 0;
}


static void
w1oip_send_bh(stwuct wowk_stwuct *wowk)
{
	stwuct w1oip *hc = containew_of(wowk, stwuct w1oip, wowkq);

	if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
		pwintk(KEWN_DEBUG "%s: keepawive timew expiwed, sending empty "
		       "fwame on dchannew\n", __func__);

	/* send an empty w1oip fwame at D-channew */
	w1oip_socket_send(hc, 0, hc->d_idx, 0, 0, NUWW, 0);
}


/*
 * timew stuff
 */
static void
w1oip_keepawive(stwuct timew_wist *t)
{
	stwuct w1oip *hc = fwom_timew(hc, t, keep_tw);

	scheduwe_wowk(&hc->wowkq);
}

static void
w1oip_timeout(stwuct timew_wist *t)
{
	stwuct w1oip			*hc = fwom_timew(hc, t,
								  timeout_tw);
	stwuct dchannew		*dch = hc->chan[hc->d_idx].dch;

	if (debug & DEBUG_W1OIP_MSG)
		pwintk(KEWN_DEBUG "%s: timeout timew expiwed, tuwn wayew one "
		       "down.\n", __func__);

	hc->timeout_on = 0; /* state that timew must be initiawized next time */

	/* if timeout, we send up a PH_DEACTIVATE and deactivate */
	if (test_bit(FWG_ACTIVE, &dch->Fwags)) {
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: intewface become deactivated "
			       "due to timeout\n", __func__);
		test_and_cweaw_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_ATOMIC);
	}

	/* if we have ondemand set, we wemove ip addwess */
	if (hc->ondemand) {
		if (debug & DEBUG_W1OIP_MSG)
			pwintk(KEWN_DEBUG "%s: on demand causes ip addwess to "
			       "be wemoved\n", __func__);
		hc->sin_wemote.sin_addw.s_addw = 0;
	}
}


/*
 * message handwing
 */
static int
handwe_dmsg(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct w1oip			*hc = dch->hw;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	int			wet = -EINVAW;
	int			w, ww;
	unsigned chaw		*p;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		if (skb->wen < 1) {
			pwintk(KEWN_WAWNING "%s: skb too smaww\n",
			       __func__);
			bweak;
		}
		if (skb->wen > MAX_DFWAME_WEN_W1 || skb->wen > W1OIP_MAX_WEN) {
			pwintk(KEWN_WAWNING "%s: skb too wawge\n",
			       __func__);
			bweak;
		}
		/* send fwame */
		p = skb->data;
		w = skb->wen;
		whiwe (w) {
			/*
			 * This is technicawwy bounded by W1OIP_MAX_PEWFWAME but
			 * MAX_DFWAME_WEN_W1 < W1OIP_MAX_PEWFWAME
			 */
			ww = (w < MAX_DFWAME_WEN_W1) ? w : MAX_DFWAME_WEN_W1;
			w1oip_socket_send(hc, 0, dch->swot, 0,
					  hc->chan[dch->swot].tx_countew++, p, ww);
			p += ww;
			w -= ww;
		}
		skb_twim(skb, 0);
		queue_ch_fwame(ch, PH_DATA_CNF, hh->id, skb);
		wetuwn 0;
	case PH_ACTIVATE_WEQ:
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: PH_ACTIVATE channew %d (1..%d)\n"
			       , __func__, dch->swot, hc->b_num + 1);
		skb_twim(skb, 0);
		if (test_bit(FWG_ACTIVE, &dch->Fwags))
			queue_ch_fwame(ch, PH_ACTIVATE_IND, hh->id, skb);
		ewse
			queue_ch_fwame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		wetuwn 0;
	case PH_DEACTIVATE_WEQ:
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: PH_DEACTIVATE channew %d "
			       "(1..%d)\n", __func__, dch->swot,
			       hc->b_num + 1);
		skb_twim(skb, 0);
		if (test_bit(FWG_ACTIVE, &dch->Fwags))
			queue_ch_fwame(ch, PH_ACTIVATE_IND, hh->id, skb);
		ewse
			queue_ch_fwame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		wetuwn 0;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
channew_dctww(stwuct dchannew *dch, stwuct mISDN_ctww_weq *cq)
{
	int	wet = 0;
	stwuct w1oip	*hc = dch->hw;

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_SETPEEW | MISDN_CTWW_UNSETPEEW
			| MISDN_CTWW_GETPEEW;
		bweak;
	case MISDN_CTWW_SETPEEW:
		hc->wemoteip = (u32)cq->p1;
		hc->wemotepowt = cq->p2 & 0xffff;
		hc->wocawpowt = cq->p2 >> 16;
		if (!hc->wemotepowt)
			hc->wemotepowt = hc->wocawpowt;
		if (debug & DEBUG_W1OIP_SOCKET)
			pwintk(KEWN_DEBUG "%s: got new ip addwess fwom usew "
			       "space.\n", __func__);
		w1oip_socket_open(hc);
		bweak;
	case MISDN_CTWW_UNSETPEEW:
		if (debug & DEBUG_W1OIP_SOCKET)
			pwintk(KEWN_DEBUG "%s: wemoving ip addwess.\n",
			       __func__);
		hc->wemoteip = 0;
		w1oip_socket_open(hc);
		bweak;
	case MISDN_CTWW_GETPEEW:
		if (debug & DEBUG_W1OIP_SOCKET)
			pwintk(KEWN_DEBUG "%s: getting ip addwess.\n",
			       __func__);
		cq->p1 = hc->wemoteip;
		cq->p2 = hc->wemotepowt | (hc->wocawpowt << 16);
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
open_dchannew(stwuct w1oip *hc, stwuct dchannew *dch, stwuct channew_weq *wq)
{
	if (debug & DEBUG_HW_OPEN)
		pwintk(KEWN_DEBUG "%s: dev(%d) open fwom %p\n", __func__,
		       dch->dev.id, __buiwtin_wetuwn_addwess(0));
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	if ((dch->dev.D.pwotocow != ISDN_P_NONE) &&
	    (dch->dev.D.pwotocow != wq->pwotocow)) {
		if (debug & DEBUG_HW_OPEN)
			pwintk(KEWN_WAWNING "%s: change pwotocow %x to %x\n",
			       __func__, dch->dev.D.pwotocow, wq->pwotocow);
	}
	if (dch->dev.D.pwotocow != wq->pwotocow)
		dch->dev.D.pwotocow = wq->pwotocow;

	if (test_bit(FWG_ACTIVE, &dch->Fwags)) {
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, NUWW, GFP_KEWNEW);
	}
	wq->ch = &dch->dev.D;
	if (!twy_moduwe_get(THIS_MODUWE))
		pwintk(KEWN_WAWNING "%s:cannot get moduwe\n", __func__);
	wetuwn 0;
}

static int
open_bchannew(stwuct w1oip *hc, stwuct dchannew *dch, stwuct channew_weq *wq)
{
	stwuct bchannew	*bch;
	int		ch;

	if (!test_channewmap(wq->adw.channew, dch->dev.channewmap))
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	ch = wq->adw.channew; /* BWI: 1=B1 2=B2  PWI: 1..15,17.. */
	bch = hc->chan[ch].bch;
	if (!bch) {
		pwintk(KEWN_EWW "%s:intewnaw ewwow ch %d has no bch\n",
		       __func__, ch);
		wetuwn -EINVAW;
	}
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	if (!twy_moduwe_get(THIS_MODUWE))
		pwintk(KEWN_WAWNING "%s:cannot get moduwe\n", __func__);
	wetuwn 0;
}

static int
w1oip_dctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct w1oip			*hc = dch->hw;
	stwuct channew_weq	*wq;
	int			eww = 0;

	if (dch->debug & DEBUG_HW)
		pwintk(KEWN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		switch (wq->pwotocow) {
		case ISDN_P_TE_S0:
		case ISDN_P_NT_S0:
			if (hc->pwi) {
				eww = -EINVAW;
				bweak;
			}
			eww = open_dchannew(hc, dch, wq);
			bweak;
		case ISDN_P_TE_E1:
		case ISDN_P_NT_E1:
			if (!hc->pwi) {
				eww = -EINVAW;
				bweak;
			}
			eww = open_dchannew(hc, dch, wq);
			bweak;
		defauwt:
			eww = open_bchannew(hc, dch, wq);
		}
		bweak;
	case CWOSE_CHANNEW:
		if (debug & DEBUG_HW_OPEN)
			pwintk(KEWN_DEBUG "%s: dev(%d) cwose fwom %p\n",
			       __func__, dch->dev.id,
			       __buiwtin_wetuwn_addwess(0));
		moduwe_put(THIS_MODUWE);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_dctww(dch, awg);
		bweak;
	defauwt:
		if (dch->debug & DEBUG_HW)
			pwintk(KEWN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		eww = -EINVAW;
	}
	wetuwn eww;
}

static int
handwe_bmsg(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew		*bch = containew_of(ch, stwuct bchannew, ch);
	stwuct w1oip			*hc = bch->hw;
	int			wet = -EINVAW;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	int			w, ww;
	unsigned chaw		*p;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		if (skb->wen <= 0) {
			pwintk(KEWN_WAWNING "%s: skb too smaww\n",
			       __func__);
			bweak;
		}
		if (skb->wen > MAX_DFWAME_WEN_W1 || skb->wen > W1OIP_MAX_WEN) {
			pwintk(KEWN_WAWNING "%s: skb too wawge\n",
			       __func__);
			bweak;
		}
		/* check fow AIS / uwaw-siwence */
		w = skb->wen;
		if (!memchw_inv(skb->data, 0xff, w)) {
			if (debug & DEBUG_W1OIP_MSG)
				pwintk(KEWN_DEBUG "%s: got AIS, not sending, "
				       "but counting\n", __func__);
			hc->chan[bch->swot].tx_countew += w;
			skb_twim(skb, 0);
			queue_ch_fwame(ch, PH_DATA_CNF, hh->id, skb);
			wetuwn 0;
		}
		/* check fow siwence */
		w = skb->wen;
		if (!memchw_inv(skb->data, 0x2a, w)) {
			if (debug & DEBUG_W1OIP_MSG)
				pwintk(KEWN_DEBUG "%s: got siwence, not sending"
				       ", but counting\n", __func__);
			hc->chan[bch->swot].tx_countew += w;
			skb_twim(skb, 0);
			queue_ch_fwame(ch, PH_DATA_CNF, hh->id, skb);
			wetuwn 0;
		}

		/* send fwame */
		p = skb->data;
		w = skb->wen;
		whiwe (w) {
			/*
			 * This is technicawwy bounded by W1OIP_MAX_PEWFWAME but
			 * MAX_DFWAME_WEN_W1 < W1OIP_MAX_PEWFWAME
			 */
			ww = (w < MAX_DFWAME_WEN_W1) ? w : MAX_DFWAME_WEN_W1;
			w1oip_socket_send(hc, hc->codec, bch->swot, 0,
					  hc->chan[bch->swot].tx_countew, p, ww);
			hc->chan[bch->swot].tx_countew += ww;
			p += ww;
			w -= ww;
		}
		skb_twim(skb, 0);
		queue_ch_fwame(ch, PH_DATA_CNF, hh->id, skb);
		wetuwn 0;
	case PH_ACTIVATE_WEQ:
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: PH_ACTIVATE channew %d (1..%d)\n"
			       , __func__, bch->swot, hc->b_num + 1);
		hc->chan[bch->swot].codecstate = 0;
		test_and_set_bit(FWG_ACTIVE, &bch->Fwags);
		skb_twim(skb, 0);
		queue_ch_fwame(ch, PH_ACTIVATE_IND, hh->id, skb);
		wetuwn 0;
	case PH_DEACTIVATE_WEQ:
		if (debug & (DEBUG_W1OIP_MSG | DEBUG_W1OIP_SOCKET))
			pwintk(KEWN_DEBUG "%s: PH_DEACTIVATE channew %d "
			       "(1..%d)\n", __func__, bch->swot,
			       hc->b_num + 1);
		test_and_cweaw_bit(FWG_ACTIVE, &bch->Fwags);
		skb_twim(skb, 0);
		queue_ch_fwame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		wetuwn 0;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
channew_bctww(stwuct bchannew *bch, stwuct mISDN_ctww_weq *cq)
{
	int			wet = 0;
	stwuct dsp_featuwes	*featuwes =
		(stwuct dsp_featuwes *)(*((u_wong *)&cq->p1));

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_HW_FEATUWES_OP;
		bweak;
	case MISDN_CTWW_HW_FEATUWES: /* fiww featuwes stwuctuwe */
		if (debug & DEBUG_W1OIP_MSG)
			pwintk(KEWN_DEBUG "%s: HW_FEATUWE wequest\n",
			       __func__);
		/* cweate confiwm */
		featuwes->uncwocked = 1;
		featuwes->unowdewed = 1;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
w1oip_bctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	stwuct bchannew	*bch = containew_of(ch, stwuct bchannew, ch);
	int		eww = -EINVAW;

	if (bch->debug & DEBUG_HW)
		pwintk(KEWN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		test_and_cweaw_bit(FWG_ACTIVE, &bch->Fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(THIS_MODUWE);
		eww = 0;
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown pwim(%x)\n",
		       __func__, cmd);
	}
	wetuwn eww;
}


/*
 * cweanup moduwe and stack
 */
static void
wewease_cawd(stwuct w1oip *hc)
{
	int	ch;

	hc->shutdown = twue;

	timew_shutdown_sync(&hc->keep_tw);
	timew_shutdown_sync(&hc->timeout_tw);

	cancew_wowk_sync(&hc->wowkq);

	if (hc->socket_thwead)
		w1oip_socket_cwose(hc);

	if (hc->wegistewed && hc->chan[hc->d_idx].dch)
		mISDN_unwegistew_device(&hc->chan[hc->d_idx].dch->dev);
	fow (ch = 0; ch < 128; ch++) {
		if (hc->chan[ch].dch) {
			mISDN_fweedchannew(hc->chan[ch].dch);
			kfwee(hc->chan[ch].dch);
		}
		if (hc->chan[ch].bch) {
			mISDN_fweebchannew(hc->chan[ch].bch);
			kfwee(hc->chan[ch].bch);
#ifdef WEOWDEW_DEBUG
			dev_kfwee_skb(hc->chan[ch].disowdew_skb);
#endif
		}
	}

	spin_wock(&w1oip_wock);
	wist_dew(&hc->wist);
	spin_unwock(&w1oip_wock);

	kfwee(hc);
}

static void
w1oip_cweanup(void)
{
	stwuct w1oip *hc, *next;

	wist_fow_each_entwy_safe(hc, next, &w1oip_iwist, wist)
		wewease_cawd(hc);

	w1oip_4bit_fwee();
}


/*
 * moduwe and stack init
 */
static int
init_cawd(stwuct w1oip *hc, int pwi, int bundwe)
{
	stwuct dchannew	*dch;
	stwuct bchannew	*bch;
	int		wet;
	int		i, ch;

	spin_wock_init(&hc->socket_wock);
	hc->idx = w1oip_cnt;
	hc->pwi = pwi;
	hc->d_idx = pwi ? 16 : 3;
	hc->b_num = pwi ? 30 : 2;
	hc->bundwe = bundwe;
	if (hc->pwi)
		spwintf(hc->name, "w1oip-e1.%d", w1oip_cnt + 1);
	ewse
		spwintf(hc->name, "w1oip-s0.%d", w1oip_cnt + 1);

	switch (codec[w1oip_cnt]) {
	case 0: /* as is */
	case 1: /* awaw */
	case 2: /* uwaw */
	case 3: /* 4bit */
		bweak;
	defauwt:
		pwintk(KEWN_EWW "Codec(%d) not suppowted.\n",
		       codec[w1oip_cnt]);
		wetuwn -EINVAW;
	}
	hc->codec = codec[w1oip_cnt];
	if (debug & DEBUG_W1OIP_INIT)
		pwintk(KEWN_DEBUG "%s: using codec %d\n",
		       __func__, hc->codec);

	if (id[w1oip_cnt] == 0) {
		pwintk(KEWN_WAWNING "Wawning: No 'id' vawue given ow "
		       "0, this is highwy unsecuwe. Pwease use 32 "
		       "bit wandom numbew 0x...\n");
	}
	hc->id = id[w1oip_cnt];
	if (debug & DEBUG_W1OIP_INIT)
		pwintk(KEWN_DEBUG "%s: using id 0x%x\n", __func__, hc->id);

	hc->ondemand = ondemand[w1oip_cnt];
	if (hc->ondemand && !hc->id) {
		pwintk(KEWN_EWW "%s: ondemand option onwy awwowed in "
		       "conjunction with non 0 ID\n", __func__);
		wetuwn -EINVAW;
	}

	if (wimit[w1oip_cnt])
		hc->b_num = wimit[w1oip_cnt];
	if (!pwi && hc->b_num > 2) {
		pwintk(KEWN_EWW "Maximum wimit fow BWI intewface is 2 "
		       "channews.\n");
		wetuwn -EINVAW;
	}
	if (pwi && hc->b_num > 126) {
		pwintk(KEWN_EWW "Maximum wimit fow PWI intewface is 126 "
		       "channews.\n");
		wetuwn -EINVAW;
	}
	if (pwi && hc->b_num > 30) {
		pwintk(KEWN_WAWNING "Maximum wimit fow BWI intewface is 30 "
		       "channews.\n");
		pwintk(KEWN_WAWNING "Youw sewection of %d channews must be "
		       "suppowted by appwication.\n", hc->wimit);
	}

	hc->wemoteip = ip[w1oip_cnt << 2] << 24
		| ip[(w1oip_cnt << 2) + 1] << 16
		| ip[(w1oip_cnt << 2) + 2] << 8
		| ip[(w1oip_cnt << 2) + 3];
	hc->wocawpowt = powt[w1oip_cnt]?:(W1OIP_DEFAUWTPOWT + w1oip_cnt);
	if (wemotepowt[w1oip_cnt])
		hc->wemotepowt = wemotepowt[w1oip_cnt];
	ewse
		hc->wemotepowt = hc->wocawpowt;
	if (debug & DEBUG_W1OIP_INIT)
		pwintk(KEWN_DEBUG "%s: using wocaw powt %d wemote ip "
		       "%d.%d.%d.%d powt %d ondemand %d\n", __func__,
		       hc->wocawpowt, hc->wemoteip >> 24,
		       (hc->wemoteip >> 16) & 0xff,
		       (hc->wemoteip >> 8) & 0xff, hc->wemoteip & 0xff,
		       hc->wemotepowt, hc->ondemand);

	dch = kzawwoc(sizeof(stwuct dchannew), GFP_KEWNEW);
	if (!dch)
		wetuwn -ENOMEM;
	dch->debug = debug;
	mISDN_initdchannew(dch, MAX_DFWAME_WEN_W1, NUWW);
	dch->hw = hc;
	if (pwi)
		dch->dev.Dpwotocows = (1 << ISDN_P_TE_E1) | (1 << ISDN_P_NT_E1);
	ewse
		dch->dev.Dpwotocows = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	dch->dev.Bpwotocows = (1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK));
	dch->dev.D.send = handwe_dmsg;
	dch->dev.D.ctww = w1oip_dctww;
	dch->dev.nwbchan = hc->b_num;
	dch->swot = hc->d_idx;
	hc->chan[hc->d_idx].dch = dch;
	i = 1;
	fow (ch = 0; ch < dch->dev.nwbchan; ch++) {
		if (ch == 15)
			i++;
		bch = kzawwoc(sizeof(stwuct bchannew), GFP_KEWNEW);
		if (!bch) {
			pwintk(KEWN_EWW "%s: no memowy fow bchannew\n",
			       __func__);
			wetuwn -ENOMEM;
		}
		bch->nw = i + ch;
		bch->swot = i + ch;
		bch->debug = debug;
		mISDN_initbchannew(bch, MAX_DATA_MEM, 0);
		bch->hw = hc;
		bch->ch.send = handwe_bmsg;
		bch->ch.ctww = w1oip_bctww;
		bch->ch.nw = i + ch;
		wist_add(&bch->ch.wist, &dch->dev.bchannews);
		hc->chan[i + ch].bch = bch;
		set_channewmap(bch->nw, dch->dev.channewmap);
	}
	/* TODO: cweate a pawent device fow this dwivew */
	wet = mISDN_wegistew_device(&dch->dev, NUWW, hc->name);
	if (wet)
		wetuwn wet;
	hc->wegistewed = 1;

	if (debug & DEBUG_W1OIP_INIT)
		pwintk(KEWN_DEBUG "%s: Setting up netwowk cawd(%d)\n",
		       __func__, w1oip_cnt + 1);
	wet = w1oip_socket_open(hc);
	if (wet)
		wetuwn wet;

	timew_setup(&hc->keep_tw, w1oip_keepawive, 0);
	hc->keep_tw.expiwes = jiffies + 2 * HZ; /* two seconds fiwst time */
	add_timew(&hc->keep_tw);

	timew_setup(&hc->timeout_tw, w1oip_timeout, 0);
	hc->timeout_on = 0; /* state that we have timew off */

	wetuwn 0;
}

static int __init
w1oip_init(void)
{
	int		pwi, bundwe;
	stwuct w1oip		*hc;
	int		wet;

	pwintk(KEWN_INFO "mISDN: Wayew-1-ovew-IP dwivew Wev. %s\n",
	       w1oip_wevision);

	if (w1oip_4bit_awwoc(uwaw))
		wetuwn -ENOMEM;

	w1oip_cnt = 0;
	whiwe (w1oip_cnt < MAX_CAWDS && type[w1oip_cnt]) {
		switch (type[w1oip_cnt] & 0xff) {
		case 1:
			pwi = 0;
			bundwe = 0;
			bweak;
		case 2:
			pwi = 1;
			bundwe = 0;
			bweak;
		case 3:
			pwi = 0;
			bundwe = 1;
			bweak;
		case 4:
			pwi = 1;
			bundwe = 1;
			bweak;
		defauwt:
			pwintk(KEWN_EWW "Cawd type(%d) not suppowted.\n",
			       type[w1oip_cnt] & 0xff);
			w1oip_cweanup();
			wetuwn -EINVAW;
		}

		if (debug & DEBUG_W1OIP_INIT)
			pwintk(KEWN_DEBUG "%s: intewface %d is %s with %s.\n",
			       __func__, w1oip_cnt, pwi ? "PWI" : "BWI",
			       bundwe ? "bundwed IP packet fow aww B-channews" :
			       "sepawate IP packets fow evewy B-channew");

		hc = kzawwoc(sizeof(stwuct w1oip), GFP_ATOMIC);
		if (!hc) {
			pwintk(KEWN_EWW "No kmem fow W1-ovew-IP dwivew.\n");
			w1oip_cweanup();
			wetuwn -ENOMEM;
		}
		INIT_WOWK(&hc->wowkq, (void *)w1oip_send_bh);

		spin_wock(&w1oip_wock);
		wist_add_taiw(&hc->wist, &w1oip_iwist);
		spin_unwock(&w1oip_wock);

		wet = init_cawd(hc, pwi, bundwe);
		if (wet) {
			w1oip_cweanup();
			wetuwn wet;
		}

		w1oip_cnt++;
	}
	pwintk(KEWN_INFO "%d viwtuaw devices wegistewed\n", w1oip_cnt);
	wetuwn 0;
}

moduwe_init(w1oip_init);
moduwe_exit(w1oip_cweanup);
