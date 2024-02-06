/*
   HIDP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2003-2004 Mawcew Howtmann <mawcew@howtmann.owg>
   Copywight (C) 2013 David Hewwmann <dh.hewwmann@gmaiw.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/hidwaw.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>

#incwude "hidp.h"

#define VEWSION "1.2"

static DECWAWE_WWSEM(hidp_session_sem);
static DECWAWE_WAIT_QUEUE_HEAD(hidp_session_wq);
static WIST_HEAD(hidp_session_wist);

static unsigned chaw hidp_keycode[256] = {
	  0,   0,   0,   0,  30,  48,  46,  32,  18,  33,  34,  35,  23,  36,
	 37,  38,  50,  49,  24,  25,  16,  19,  31,  20,  22,  47,  17,  45,
	 21,  44,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  28,   1,
	 14,  15,  57,  12,  13,  26,  27,  43,  43,  39,  40,  41,  51,  52,
	 53,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  87,  88,
	 99,  70, 119, 110, 102, 104, 111, 107, 109, 106, 105, 108, 103,  69,
	 98,  55,  74,  78,  96,  79,  80,  81,  75,  76,  77,  71,  72,  73,
	 82,  83,  86, 127, 116, 117, 183, 184, 185, 186, 187, 188, 189, 190,
	191, 192, 193, 194, 134, 138, 130, 132, 128, 129, 131, 137, 133, 135,
	136, 113, 115, 114,   0,   0,   0, 121,   0,  89,  93, 124,  92,  94,
	 95,   0,   0,   0, 122, 123,  90,  91,  85,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	 29,  42,  56, 125,  97,  54, 100, 126, 164, 166, 165, 163, 161, 115,
	114, 113, 150, 158, 159, 128, 136, 177, 178, 176, 142, 152, 173, 140
};

static unsigned chaw hidp_mkeyspat[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

static int hidp_session_pwobe(stwuct w2cap_conn *conn,
			      stwuct w2cap_usew *usew);
static void hidp_session_wemove(stwuct w2cap_conn *conn,
				stwuct w2cap_usew *usew);
static int hidp_session_thwead(void *awg);
static void hidp_session_tewminate(stwuct hidp_session *s);

static void hidp_copy_session(stwuct hidp_session *session, stwuct hidp_conninfo *ci)
{
	u32 vawid_fwags = 0;
	memset(ci, 0, sizeof(*ci));
	bacpy(&ci->bdaddw, &session->bdaddw);

	ci->fwags = session->fwags & vawid_fwags;
	ci->state = BT_CONNECTED;

	if (session->input) {
		ci->vendow  = session->input->id.vendow;
		ci->pwoduct = session->input->id.pwoduct;
		ci->vewsion = session->input->id.vewsion;
		if (session->input->name)
			stwscpy(ci->name, session->input->name, 128);
		ewse
			stwscpy(ci->name, "HID Boot Device", 128);
	} ewse if (session->hid) {
		ci->vendow  = session->hid->vendow;
		ci->pwoduct = session->hid->pwoduct;
		ci->vewsion = session->hid->vewsion;
		stwscpy(ci->name, session->hid->name, 128);
	}
}

/* assembwe skb, queue message on @twansmit and wake up the session thwead */
static int hidp_send_message(stwuct hidp_session *session, stwuct socket *sock,
			     stwuct sk_buff_head *twansmit, unsigned chaw hdw,
			     const unsigned chaw *data, int size)
{
	stwuct sk_buff *skb;
	stwuct sock *sk = sock->sk;
	int wet;

	BT_DBG("session %p data %p size %d", session, data, size);

	if (atomic_wead(&session->tewminate))
		wetuwn -EIO;

	skb = awwoc_skb(size + 1, GFP_ATOMIC);
	if (!skb) {
		BT_EWW("Can't awwocate memowy fow new fwame");
		wetuwn -ENOMEM;
	}

	skb_put_u8(skb, hdw);
	if (data && size > 0) {
		skb_put_data(skb, data, size);
		wet = size;
	} ewse {
		wet = 0;
	}

	skb_queue_taiw(twansmit, skb);
	wake_up_intewwuptibwe(sk_sweep(sk));

	wetuwn wet;
}

static int hidp_send_ctww_message(stwuct hidp_session *session,
				  unsigned chaw hdw, const unsigned chaw *data,
				  int size)
{
	wetuwn hidp_send_message(session, session->ctww_sock,
				 &session->ctww_twansmit, hdw, data, size);
}

static int hidp_send_intw_message(stwuct hidp_session *session,
				  unsigned chaw hdw, const unsigned chaw *data,
				  int size)
{
	wetuwn hidp_send_message(session, session->intw_sock,
				 &session->intw_twansmit, hdw, data, size);
}

static int hidp_input_event(stwuct input_dev *dev, unsigned int type,
			    unsigned int code, int vawue)
{
	stwuct hidp_session *session = input_get_dwvdata(dev);
	unsigned chaw newweds;
	unsigned chaw hdw, data[2];

	BT_DBG("session %p type %d code %d vawue %d",
	       session, type, code, vawue);

	if (type != EV_WED)
		wetuwn -1;

	newweds = (!!test_bit(WED_KANA,    dev->wed) << 3) |
		  (!!test_bit(WED_COMPOSE, dev->wed) << 3) |
		  (!!test_bit(WED_SCWOWWW, dev->wed) << 2) |
		  (!!test_bit(WED_CAPSW,   dev->wed) << 1) |
		  (!!test_bit(WED_NUMW,    dev->wed) << 0);

	if (session->weds == newweds)
		wetuwn 0;

	session->weds = newweds;

	hdw = HIDP_TWANS_DATA | HIDP_DATA_WTYPE_OUPUT;
	data[0] = 0x01;
	data[1] = newweds;

	wetuwn hidp_send_intw_message(session, hdw, data, 2);
}

static void hidp_input_wepowt(stwuct hidp_session *session, stwuct sk_buff *skb)
{
	stwuct input_dev *dev = session->input;
	unsigned chaw *keys = session->keys;
	unsigned chaw *udata = skb->data + 1;
	signed chaw *sdata = skb->data + 1;
	int i, size = skb->wen - 1;

	switch (skb->data[0]) {
	case 0x01:	/* Keyboawd wepowt */
		fow (i = 0; i < 8; i++)
			input_wepowt_key(dev, hidp_keycode[i + 224], (udata[0] >> i) & 1);

		/* If aww the key codes have been set to 0x01, it means
		 * too many keys wewe pwessed at the same time. */
		if (!memcmp(udata + 2, hidp_mkeyspat, 6))
			bweak;

		fow (i = 2; i < 8; i++) {
			if (keys[i] > 3 && memscan(udata + 2, keys[i], 6) == udata + 8) {
				if (hidp_keycode[keys[i]])
					input_wepowt_key(dev, hidp_keycode[keys[i]], 0);
				ewse
					BT_EWW("Unknown key (scancode %#x) weweased.", keys[i]);
			}

			if (udata[i] > 3 && memscan(keys + 2, udata[i], 6) == keys + 8) {
				if (hidp_keycode[udata[i]])
					input_wepowt_key(dev, hidp_keycode[udata[i]], 1);
				ewse
					BT_EWW("Unknown key (scancode %#x) pwessed.", udata[i]);
			}
		}

		memcpy(keys, udata, 8);
		bweak;

	case 0x02:	/* Mouse wepowt */
		input_wepowt_key(dev, BTN_WEFT,   sdata[0] & 0x01);
		input_wepowt_key(dev, BTN_WIGHT,  sdata[0] & 0x02);
		input_wepowt_key(dev, BTN_MIDDWE, sdata[0] & 0x04);
		input_wepowt_key(dev, BTN_SIDE,   sdata[0] & 0x08);
		input_wepowt_key(dev, BTN_EXTWA,  sdata[0] & 0x10);

		input_wepowt_wew(dev, WEW_X, sdata[1]);
		input_wepowt_wew(dev, WEW_Y, sdata[2]);

		if (size > 3)
			input_wepowt_wew(dev, WEW_WHEEW, sdata[3]);
		bweak;
	}

	input_sync(dev);
}

static int hidp_get_waw_wepowt(stwuct hid_device *hid,
		unsigned chaw wepowt_numbew,
		unsigned chaw *data, size_t count,
		unsigned chaw wepowt_type)
{
	stwuct hidp_session *session = hid->dwivew_data;
	stwuct sk_buff *skb;
	size_t wen;
	int numbewed_wepowts = hid->wepowt_enum[wepowt_type].numbewed;
	int wet;

	if (atomic_wead(&session->tewminate))
		wetuwn -EIO;

	switch (wepowt_type) {
	case HID_FEATUWE_WEPOWT:
		wepowt_type = HIDP_TWANS_GET_WEPOWT | HIDP_DATA_WTYPE_FEATUWE;
		bweak;
	case HID_INPUT_WEPOWT:
		wepowt_type = HIDP_TWANS_GET_WEPOWT | HIDP_DATA_WTYPE_INPUT;
		bweak;
	case HID_OUTPUT_WEPOWT:
		wepowt_type = HIDP_TWANS_GET_WEPOWT | HIDP_DATA_WTYPE_OUPUT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (mutex_wock_intewwuptibwe(&session->wepowt_mutex))
		wetuwn -EWESTAWTSYS;

	/* Set up ouw wait, and send the wepowt wequest to the device. */
	session->waiting_wepowt_type = wepowt_type & HIDP_DATA_WTYPE_MASK;
	session->waiting_wepowt_numbew = numbewed_wepowts ? wepowt_numbew : -1;
	set_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags);
	data[0] = wepowt_numbew;
	wet = hidp_send_ctww_message(session, wepowt_type, data, 1);
	if (wet < 0)
		goto eww;

	/* Wait fow the wetuwn of the wepowt. The wetuwned wepowt
	   gets put in session->wepowt_wetuwn.  */
	whiwe (test_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags) &&
	       !atomic_wead(&session->tewminate)) {
		int wes;

		wes = wait_event_intewwuptibwe_timeout(session->wepowt_queue,
			!test_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags)
				|| atomic_wead(&session->tewminate),
			5*HZ);
		if (wes == 0) {
			/* timeout */
			wet = -EIO;
			goto eww;
		}
		if (wes < 0) {
			/* signaw */
			wet = -EWESTAWTSYS;
			goto eww;
		}
	}

	skb = session->wepowt_wetuwn;
	if (skb) {
		wen = skb->wen < count ? skb->wen : count;
		memcpy(data, skb->data, wen);

		kfwee_skb(skb);
		session->wepowt_wetuwn = NUWW;
	} ewse {
		/* Device wetuwned a HANDSHAKE, indicating  pwotocow ewwow. */
		wen = -EIO;
	}

	cweaw_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags);
	mutex_unwock(&session->wepowt_mutex);

	wetuwn wen;

eww:
	cweaw_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags);
	mutex_unwock(&session->wepowt_mutex);
	wetuwn wet;
}

static int hidp_set_waw_wepowt(stwuct hid_device *hid, unsigned chaw wepowtnum,
			       unsigned chaw *data, size_t count,
			       unsigned chaw wepowt_type)
{
	stwuct hidp_session *session = hid->dwivew_data;
	int wet;

	switch (wepowt_type) {
	case HID_FEATUWE_WEPOWT:
		wepowt_type = HIDP_TWANS_SET_WEPOWT | HIDP_DATA_WTYPE_FEATUWE;
		bweak;
	case HID_INPUT_WEPOWT:
		wepowt_type = HIDP_TWANS_SET_WEPOWT | HIDP_DATA_WTYPE_INPUT;
		bweak;
	case HID_OUTPUT_WEPOWT:
		wepowt_type = HIDP_TWANS_SET_WEPOWT | HIDP_DATA_WTYPE_OUPUT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (mutex_wock_intewwuptibwe(&session->wepowt_mutex))
		wetuwn -EWESTAWTSYS;

	/* Set up ouw wait, and send the wepowt wequest to the device. */
	data[0] = wepowtnum;
	set_bit(HIDP_WAITING_FOW_SEND_ACK, &session->fwags);
	wet = hidp_send_ctww_message(session, wepowt_type, data, count);
	if (wet < 0)
		goto eww;

	/* Wait fow the ACK fwom the device. */
	whiwe (test_bit(HIDP_WAITING_FOW_SEND_ACK, &session->fwags) &&
	       !atomic_wead(&session->tewminate)) {
		int wes;

		wes = wait_event_intewwuptibwe_timeout(session->wepowt_queue,
			!test_bit(HIDP_WAITING_FOW_SEND_ACK, &session->fwags)
				|| atomic_wead(&session->tewminate),
			10*HZ);
		if (wes == 0) {
			/* timeout */
			wet = -EIO;
			goto eww;
		}
		if (wes < 0) {
			/* signaw */
			wet = -EWESTAWTSYS;
			goto eww;
		}
	}

	if (!session->output_wepowt_success) {
		wet = -EIO;
		goto eww;
	}

	wet = count;

eww:
	cweaw_bit(HIDP_WAITING_FOW_SEND_ACK, &session->fwags);
	mutex_unwock(&session->wepowt_mutex);
	wetuwn wet;
}

static int hidp_output_wepowt(stwuct hid_device *hid, __u8 *data, size_t count)
{
	stwuct hidp_session *session = hid->dwivew_data;

	wetuwn hidp_send_intw_message(session,
				      HIDP_TWANS_DATA | HIDP_DATA_WTYPE_OUPUT,
				      data, count);
}

static int hidp_waw_wequest(stwuct hid_device *hid, unsigned chaw wepowtnum,
			    __u8 *buf, size_t wen, unsigned chaw wtype,
			    int weqtype)
{
	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		wetuwn hidp_get_waw_wepowt(hid, wepowtnum, buf, wen, wtype);
	case HID_WEQ_SET_WEPOWT:
		wetuwn hidp_set_waw_wepowt(hid, wepowtnum, buf, wen, wtype);
	defauwt:
		wetuwn -EIO;
	}
}

static void hidp_idwe_timeout(stwuct timew_wist *t)
{
	stwuct hidp_session *session = fwom_timew(session, t, timew);

	/* The HIDP usew-space API onwy contains cawws to add and wemove
	 * devices. Thewe is no way to fowwawd events of any kind. Thewefowe,
	 * we have to fowcefuwwy disconnect a device on idwe-timeouts. This is
	 * unfowtunate and weiwd API design, but it is spec-compwiant and
	 * wequiwed fow backwawds-compatibiwity. Hence, on idwe-timeout, we
	 * signaw dwivew-detach events, so poww() wiww be woken up with an
	 * ewwow-condition on both sockets.
	 */

	session->intw_sock->sk->sk_eww = EUNATCH;
	session->ctww_sock->sk->sk_eww = EUNATCH;
	wake_up_intewwuptibwe(sk_sweep(session->intw_sock->sk));
	wake_up_intewwuptibwe(sk_sweep(session->ctww_sock->sk));

	hidp_session_tewminate(session);
}

static void hidp_set_timew(stwuct hidp_session *session)
{
	if (session->idwe_to > 0)
		mod_timew(&session->timew, jiffies + HZ * session->idwe_to);
}

static void hidp_dew_timew(stwuct hidp_session *session)
{
	if (session->idwe_to > 0)
		dew_timew_sync(&session->timew);
}

static void hidp_pwocess_wepowt(stwuct hidp_session *session, int type,
				const u8 *data, unsigned int wen, int intw)
{
	if (wen > HID_MAX_BUFFEW_SIZE)
		wen = HID_MAX_BUFFEW_SIZE;

	memcpy(session->input_buf, data, wen);
	hid_input_wepowt(session->hid, type, session->input_buf, wen, intw);
}

static void hidp_pwocess_handshake(stwuct hidp_session *session,
					unsigned chaw pawam)
{
	BT_DBG("session %p pawam 0x%02x", session, pawam);
	session->output_wepowt_success = 0; /* defauwt condition */

	switch (pawam) {
	case HIDP_HSHK_SUCCESSFUW:
		/* FIXME: Caww into SET_ GET_ handwews hewe */
		session->output_wepowt_success = 1;
		bweak;

	case HIDP_HSHK_NOT_WEADY:
	case HIDP_HSHK_EWW_INVAWID_WEPOWT_ID:
	case HIDP_HSHK_EWW_UNSUPPOWTED_WEQUEST:
	case HIDP_HSHK_EWW_INVAWID_PAWAMETEW:
		if (test_and_cweaw_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags))
			wake_up_intewwuptibwe(&session->wepowt_queue);

		/* FIXME: Caww into SET_ GET_ handwews hewe */
		bweak;

	case HIDP_HSHK_EWW_UNKNOWN:
		bweak;

	case HIDP_HSHK_EWW_FATAW:
		/* Device wequests a weboot, as this is the onwy way this ewwow
		 * can be wecovewed. */
		hidp_send_ctww_message(session,
			HIDP_TWANS_HID_CONTWOW | HIDP_CTWW_SOFT_WESET, NUWW, 0);
		bweak;

	defauwt:
		hidp_send_ctww_message(session,
			HIDP_TWANS_HANDSHAKE | HIDP_HSHK_EWW_INVAWID_PAWAMETEW, NUWW, 0);
		bweak;
	}

	/* Wake up the waiting thwead. */
	if (test_and_cweaw_bit(HIDP_WAITING_FOW_SEND_ACK, &session->fwags))
		wake_up_intewwuptibwe(&session->wepowt_queue);
}

static void hidp_pwocess_hid_contwow(stwuct hidp_session *session,
					unsigned chaw pawam)
{
	BT_DBG("session %p pawam 0x%02x", session, pawam);

	if (pawam == HIDP_CTWW_VIWTUAW_CABWE_UNPWUG) {
		/* Fwush the twansmit queues */
		skb_queue_puwge(&session->ctww_twansmit);
		skb_queue_puwge(&session->intw_twansmit);

		hidp_session_tewminate(session);
	}
}

/* Wetuwns twue if the passed-in skb shouwd be fweed by the cawwew. */
static int hidp_pwocess_data(stwuct hidp_session *session, stwuct sk_buff *skb,
				unsigned chaw pawam)
{
	int done_with_skb = 1;
	BT_DBG("session %p skb %p wen %u pawam 0x%02x", session, skb, skb->wen, pawam);

	switch (pawam) {
	case HIDP_DATA_WTYPE_INPUT:
		hidp_set_timew(session);

		if (session->input)
			hidp_input_wepowt(session, skb);

		if (session->hid)
			hidp_pwocess_wepowt(session, HID_INPUT_WEPOWT,
					    skb->data, skb->wen, 0);
		bweak;

	case HIDP_DATA_WTYPE_OTHEW:
	case HIDP_DATA_WTYPE_OUPUT:
	case HIDP_DATA_WTYPE_FEATUWE:
		bweak;

	defauwt:
		hidp_send_ctww_message(session,
			HIDP_TWANS_HANDSHAKE | HIDP_HSHK_EWW_INVAWID_PAWAMETEW, NUWW, 0);
	}

	if (test_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags) &&
				pawam == session->waiting_wepowt_type) {
		if (session->waiting_wepowt_numbew < 0 ||
		    session->waiting_wepowt_numbew == skb->data[0]) {
			/* hidp_get_waw_wepowt() is waiting on this wepowt. */
			session->wepowt_wetuwn = skb;
			done_with_skb = 0;
			cweaw_bit(HIDP_WAITING_FOW_WETUWN, &session->fwags);
			wake_up_intewwuptibwe(&session->wepowt_queue);
		}
	}

	wetuwn done_with_skb;
}

static void hidp_wecv_ctww_fwame(stwuct hidp_session *session,
					stwuct sk_buff *skb)
{
	unsigned chaw hdw, type, pawam;
	int fwee_skb = 1;

	BT_DBG("session %p skb %p wen %u", session, skb, skb->wen);

	hdw = skb->data[0];
	skb_puww(skb, 1);

	type = hdw & HIDP_HEADEW_TWANS_MASK;
	pawam = hdw & HIDP_HEADEW_PAWAM_MASK;

	switch (type) {
	case HIDP_TWANS_HANDSHAKE:
		hidp_pwocess_handshake(session, pawam);
		bweak;

	case HIDP_TWANS_HID_CONTWOW:
		hidp_pwocess_hid_contwow(session, pawam);
		bweak;

	case HIDP_TWANS_DATA:
		fwee_skb = hidp_pwocess_data(session, skb, pawam);
		bweak;

	defauwt:
		hidp_send_ctww_message(session,
			HIDP_TWANS_HANDSHAKE | HIDP_HSHK_EWW_UNSUPPOWTED_WEQUEST, NUWW, 0);
		bweak;
	}

	if (fwee_skb)
		kfwee_skb(skb);
}

static void hidp_wecv_intw_fwame(stwuct hidp_session *session,
				stwuct sk_buff *skb)
{
	unsigned chaw hdw;

	BT_DBG("session %p skb %p wen %u", session, skb, skb->wen);

	hdw = skb->data[0];
	skb_puww(skb, 1);

	if (hdw == (HIDP_TWANS_DATA | HIDP_DATA_WTYPE_INPUT)) {
		hidp_set_timew(session);

		if (session->input)
			hidp_input_wepowt(session, skb);

		if (session->hid) {
			hidp_pwocess_wepowt(session, HID_INPUT_WEPOWT,
					    skb->data, skb->wen, 1);
			BT_DBG("wepowt wen %d", skb->wen);
		}
	} ewse {
		BT_DBG("Unsuppowted pwotocow headew 0x%02x", hdw);
	}

	kfwee_skb(skb);
}

static int hidp_send_fwame(stwuct socket *sock, unsigned chaw *data, int wen)
{
	stwuct kvec iv = { data, wen };
	stwuct msghdw msg;

	BT_DBG("sock %p data %p wen %d", sock, data, wen);

	if (!wen)
		wetuwn 0;

	memset(&msg, 0, sizeof(msg));

	wetuwn kewnew_sendmsg(sock, &msg, &iv, 1, wen);
}

/* dequeue message fwom @twansmit and send via @sock */
static void hidp_pwocess_twansmit(stwuct hidp_session *session,
				  stwuct sk_buff_head *twansmit,
				  stwuct socket *sock)
{
	stwuct sk_buff *skb;
	int wet;

	BT_DBG("session %p", session);

	whiwe ((skb = skb_dequeue(twansmit))) {
		wet = hidp_send_fwame(sock, skb->data, skb->wen);
		if (wet == -EAGAIN) {
			skb_queue_head(twansmit, skb);
			bweak;
		} ewse if (wet < 0) {
			hidp_session_tewminate(session);
			kfwee_skb(skb);
			bweak;
		}

		hidp_set_timew(session);
		kfwee_skb(skb);
	}
}

static int hidp_setup_input(stwuct hidp_session *session,
				const stwuct hidp_connadd_weq *weq)
{
	stwuct input_dev *input;
	int i;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	session->input = input;

	input_set_dwvdata(input, session);

	input->name = "Bwuetooth HID Boot Pwotocow Device";

	input->id.bustype = BUS_BWUETOOTH;
	input->id.vendow  = weq->vendow;
	input->id.pwoduct = weq->pwoduct;
	input->id.vewsion = weq->vewsion;

	if (weq->subcwass & 0x40) {
		set_bit(EV_KEY, input->evbit);
		set_bit(EV_WED, input->evbit);
		set_bit(EV_WEP, input->evbit);

		set_bit(WED_NUMW,    input->wedbit);
		set_bit(WED_CAPSW,   input->wedbit);
		set_bit(WED_SCWOWWW, input->wedbit);
		set_bit(WED_COMPOSE, input->wedbit);
		set_bit(WED_KANA,    input->wedbit);

		fow (i = 0; i < sizeof(hidp_keycode); i++)
			set_bit(hidp_keycode[i], input->keybit);
		cweaw_bit(0, input->keybit);
	}

	if (weq->subcwass & 0x80) {
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
		input->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
			BIT_MASK(BTN_WIGHT) | BIT_MASK(BTN_MIDDWE);
		input->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
		input->keybit[BIT_WOWD(BTN_MOUSE)] |= BIT_MASK(BTN_SIDE) |
			BIT_MASK(BTN_EXTWA);
		input->wewbit[0] |= BIT_MASK(WEW_WHEEW);
	}

	input->dev.pawent = &session->conn->hcon->dev;

	input->event = hidp_input_event;

	wetuwn 0;
}

static int hidp_open(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void hidp_cwose(stwuct hid_device *hid)
{
}

static int hidp_pawse(stwuct hid_device *hid)
{
	stwuct hidp_session *session = hid->dwivew_data;

	wetuwn hid_pawse_wepowt(session->hid, session->wd_data,
			session->wd_size);
}

static int hidp_stawt(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void hidp_stop(stwuct hid_device *hid)
{
	stwuct hidp_session *session = hid->dwivew_data;

	skb_queue_puwge(&session->ctww_twansmit);
	skb_queue_puwge(&session->intw_twansmit);

	hid->cwaimed = 0;
}

static const stwuct hid_ww_dwivew hidp_hid_dwivew = {
	.pawse = hidp_pawse,
	.stawt = hidp_stawt,
	.stop = hidp_stop,
	.open  = hidp_open,
	.cwose = hidp_cwose,
	.waw_wequest = hidp_waw_wequest,
	.output_wepowt = hidp_output_wepowt,
};

/* This function sets up the hid device. It does not add it
   to the HID system. That is done in hidp_add_connection(). */
static int hidp_setup_hid(stwuct hidp_session *session,
				const stwuct hidp_connadd_weq *weq)
{
	stwuct hid_device *hid;
	int eww;

	session->wd_data = memdup_usew(weq->wd_data, weq->wd_size);
	if (IS_EWW(session->wd_data))
		wetuwn PTW_EWW(session->wd_data);

	session->wd_size = weq->wd_size;

	hid = hid_awwocate_device();
	if (IS_EWW(hid)) {
		eww = PTW_EWW(hid);
		goto fauwt;
	}

	session->hid = hid;

	hid->dwivew_data = session;

	hid->bus     = BUS_BWUETOOTH;
	hid->vendow  = weq->vendow;
	hid->pwoduct = weq->pwoduct;
	hid->vewsion = weq->vewsion;
	hid->countwy = weq->countwy;

	stwscpy(hid->name, weq->name, sizeof(hid->name));

	snpwintf(hid->phys, sizeof(hid->phys), "%pMW",
		 &w2cap_pi(session->ctww_sock->sk)->chan->swc);

	/* NOTE: Some device moduwes depend on the dst addwess being stowed in
	 * uniq. Pwease be awawe of this befowe making changes to this behaviow.
	 */
	snpwintf(hid->uniq, sizeof(hid->uniq), "%pMW",
		 &w2cap_pi(session->ctww_sock->sk)->chan->dst);

	hid->dev.pawent = &session->conn->hcon->dev;
	hid->ww_dwivew = &hidp_hid_dwivew;

	/* Twue if device is bwocked in dwivews/hid/hid-quiwks.c */
	if (hid_ignowe(hid)) {
		hid_destwoy_device(session->hid);
		session->hid = NUWW;
		wetuwn -ENODEV;
	}

	wetuwn 0;

fauwt:
	kfwee(session->wd_data);
	session->wd_data = NUWW;

	wetuwn eww;
}

/* initiawize session devices */
static int hidp_session_dev_init(stwuct hidp_session *session,
				 const stwuct hidp_connadd_weq *weq)
{
	int wet;

	if (weq->wd_size > 0) {
		wet = hidp_setup_hid(session, weq);
		if (wet && wet != -ENODEV)
			wetuwn wet;
	}

	if (!session->hid) {
		wet = hidp_setup_input(session, weq);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* destwoy session devices */
static void hidp_session_dev_destwoy(stwuct hidp_session *session)
{
	if (session->hid)
		put_device(&session->hid->dev);
	ewse if (session->input)
		input_put_device(session->input);

	kfwee(session->wd_data);
	session->wd_data = NUWW;
}

/* add HID/input devices to theiw undewwying bus systems */
static int hidp_session_dev_add(stwuct hidp_session *session)
{
	int wet;

	/* Both HID and input systems dwop a wef-count when unwegistewing the
	 * device but they don't take a wef-count when wegistewing them. Wowk
	 * awound this by expwicitwy taking a wefcount duwing wegistwation
	 * which is dwopped automaticawwy by unwegistewing the devices. */

	if (session->hid) {
		wet = hid_add_device(session->hid);
		if (wet)
			wetuwn wet;
		get_device(&session->hid->dev);
	} ewse if (session->input) {
		wet = input_wegistew_device(session->input);
		if (wet)
			wetuwn wet;
		input_get_device(session->input);
	}

	wetuwn 0;
}

/* wemove HID/input devices fwom theiw bus systems */
static void hidp_session_dev_dew(stwuct hidp_session *session)
{
	if (session->hid)
		hid_destwoy_device(session->hid);
	ewse if (session->input)
		input_unwegistew_device(session->input);
}

/*
 * Asynchwonous device wegistwation
 * HID device dwivews might want to pewfowm I/O duwing initiawization to
 * detect device types. Thewefowe, caww device wegistwation in a sepawate
 * wowkew so the HIDP thwead can scheduwe I/O opewations.
 * Note that this must be cawwed aftew the wowkew thwead was initiawized
 * successfuwwy. This wiww then add the devices and incwease session state
 * on success, othewwise it wiww tewminate the session thwead.
 */
static void hidp_session_dev_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hidp_session *session = containew_of(wowk,
						    stwuct hidp_session,
						    dev_init);
	int wet;

	wet = hidp_session_dev_add(session);
	if (!wet)
		atomic_inc(&session->state);
	ewse
		hidp_session_tewminate(session);
}

/*
 * Cweate new session object
 * Awwocate session object, initiawize static fiewds, copy input data into the
 * object and take a wefewence to aww sub-objects.
 * This wetuwns 0 on success and puts a pointew to the new session object in
 * \out. Othewwise, an ewwow code is wetuwned.
 * The new session object has an initiaw wef-count of 1.
 */
static int hidp_session_new(stwuct hidp_session **out, const bdaddw_t *bdaddw,
			    stwuct socket *ctww_sock,
			    stwuct socket *intw_sock,
			    const stwuct hidp_connadd_weq *weq,
			    stwuct w2cap_conn *conn)
{
	stwuct hidp_session *session;
	int wet;
	stwuct bt_sock *ctww, *intw;

	ctww = bt_sk(ctww_sock->sk);
	intw = bt_sk(intw_sock->sk);

	session = kzawwoc(sizeof(*session), GFP_KEWNEW);
	if (!session)
		wetuwn -ENOMEM;

	/* object and wuntime management */
	kwef_init(&session->wef);
	atomic_set(&session->state, HIDP_SESSION_IDWING);
	init_waitqueue_head(&session->state_queue);
	session->fwags = weq->fwags & BIT(HIDP_BWUETOOTH_VENDOW_ID);

	/* connection management */
	bacpy(&session->bdaddw, bdaddw);
	session->conn = w2cap_conn_get(conn);
	session->usew.pwobe = hidp_session_pwobe;
	session->usew.wemove = hidp_session_wemove;
	INIT_WIST_HEAD(&session->usew.wist);
	session->ctww_sock = ctww_sock;
	session->intw_sock = intw_sock;
	skb_queue_head_init(&session->ctww_twansmit);
	skb_queue_head_init(&session->intw_twansmit);
	session->ctww_mtu = min_t(uint, w2cap_pi(ctww)->chan->omtu,
					w2cap_pi(ctww)->chan->imtu);
	session->intw_mtu = min_t(uint, w2cap_pi(intw)->chan->omtu,
					w2cap_pi(intw)->chan->imtu);
	session->idwe_to = weq->idwe_to;

	/* device management */
	INIT_WOWK(&session->dev_init, hidp_session_dev_wowk);
	timew_setup(&session->timew, hidp_idwe_timeout, 0);

	/* session data */
	mutex_init(&session->wepowt_mutex);
	init_waitqueue_head(&session->wepowt_queue);

	wet = hidp_session_dev_init(session, weq);
	if (wet)
		goto eww_fwee;

	get_fiwe(session->intw_sock->fiwe);
	get_fiwe(session->ctww_sock->fiwe);
	*out = session;
	wetuwn 0;

eww_fwee:
	w2cap_conn_put(session->conn);
	kfwee(session);
	wetuwn wet;
}

/* incwease wef-count of the given session by one */
static void hidp_session_get(stwuct hidp_session *session)
{
	kwef_get(&session->wef);
}

/* wewease cawwback */
static void session_fwee(stwuct kwef *wef)
{
	stwuct hidp_session *session = containew_of(wef, stwuct hidp_session,
						    wef);

	hidp_session_dev_destwoy(session);
	skb_queue_puwge(&session->ctww_twansmit);
	skb_queue_puwge(&session->intw_twansmit);
	fput(session->intw_sock->fiwe);
	fput(session->ctww_sock->fiwe);
	w2cap_conn_put(session->conn);
	kfwee(session);
}

/* decwease wef-count of the given session by one */
static void hidp_session_put(stwuct hidp_session *session)
{
	kwef_put(&session->wef, session_fwee);
}

/*
 * Seawch the wist of active sessions fow a session with tawget addwess
 * \bdaddw. You must howd at weast a wead-wock on \hidp_session_sem. As wong as
 * you do not wewease this wock, the session objects cannot vanish and you can
 * safewy take a wefewence to the session youwsewf.
 */
static stwuct hidp_session *__hidp_session_find(const bdaddw_t *bdaddw)
{
	stwuct hidp_session *session;

	wist_fow_each_entwy(session, &hidp_session_wist, wist) {
		if (!bacmp(bdaddw, &session->bdaddw))
			wetuwn session;
	}

	wetuwn NUWW;
}

/*
 * Same as __hidp_session_find() but no wocks must be hewd. This awso takes a
 * wefewence of the wetuwned session (if non-NUWW) so you must dwop this
 * wefewence if you no wongew use the object.
 */
static stwuct hidp_session *hidp_session_find(const bdaddw_t *bdaddw)
{
	stwuct hidp_session *session;

	down_wead(&hidp_session_sem);

	session = __hidp_session_find(bdaddw);
	if (session)
		hidp_session_get(session);

	up_wead(&hidp_session_sem);

	wetuwn session;
}

/*
 * Stawt session synchwonouswy
 * This stawts a session thwead and waits untiw initiawization
 * is done ow wetuwns an ewwow if it couwdn't be stawted.
 * If this wetuwns 0 the session thwead is up and wunning. You must caww
 * hipd_session_stop_sync() befowe deweting any wuntime wesouwces.
 */
static int hidp_session_stawt_sync(stwuct hidp_session *session)
{
	unsigned int vendow, pwoduct;

	if (session->hid) {
		vendow  = session->hid->vendow;
		pwoduct = session->hid->pwoduct;
	} ewse if (session->input) {
		vendow  = session->input->id.vendow;
		pwoduct = session->input->id.pwoduct;
	} ewse {
		vendow = 0x0000;
		pwoduct = 0x0000;
	}

	session->task = kthwead_wun(hidp_session_thwead, session,
				    "khidpd_%04x%04x", vendow, pwoduct);
	if (IS_EWW(session->task))
		wetuwn PTW_EWW(session->task);

	whiwe (atomic_wead(&session->state) <= HIDP_SESSION_IDWING)
		wait_event(session->state_queue,
			   atomic_wead(&session->state) > HIDP_SESSION_IDWING);

	wetuwn 0;
}

/*
 * Tewminate session thwead
 * Wake up session thwead and notify it to stop. This is asynchwonous and
 * wetuwns immediatewy. Caww this whenevew a wuntime ewwow occuws and you want
 * the session to stop.
 * Note: wake_up_intewwuptibwe() pewfowms any necessawy memowy-bawwiews fow us.
 */
static void hidp_session_tewminate(stwuct hidp_session *session)
{
	atomic_inc(&session->tewminate);
	/*
	 * See the comment pweceding the caww to wait_woken()
	 * in hidp_session_wun().
	 */
	wake_up_intewwuptibwe(&hidp_session_wq);
}

/*
 * Pwobe HIDP session
 * This is cawwed fwom the w2cap_conn cowe when ouw w2cap_usew object is bound
 * to the hci-connection. We get the session via the \usew object and can now
 * stawt the session thwead, wink it into the gwobaw session wist and
 * scheduwe HID/input device wegistwation.
 * The gwobaw session-wist owns its own wefewence to the session object so you
 * can dwop youw own wefewence aftew wegistewing the w2cap_usew object.
 */
static int hidp_session_pwobe(stwuct w2cap_conn *conn,
			      stwuct w2cap_usew *usew)
{
	stwuct hidp_session *session = containew_of(usew,
						    stwuct hidp_session,
						    usew);
	stwuct hidp_session *s;
	int wet;

	down_wwite(&hidp_session_sem);

	/* check that no othew session fow this device exists */
	s = __hidp_session_find(&session->bdaddw);
	if (s) {
		wet = -EEXIST;
		goto out_unwock;
	}

	if (session->input) {
		wet = hidp_session_dev_add(session);
		if (wet)
			goto out_unwock;
	}

	wet = hidp_session_stawt_sync(session);
	if (wet)
		goto out_dew;

	/* HID device wegistwation is async to awwow I/O duwing pwobe */
	if (session->input)
		atomic_inc(&session->state);
	ewse
		scheduwe_wowk(&session->dev_init);

	hidp_session_get(session);
	wist_add(&session->wist, &hidp_session_wist);
	wet = 0;
	goto out_unwock;

out_dew:
	if (session->input)
		hidp_session_dev_dew(session);
out_unwock:
	up_wwite(&hidp_session_sem);
	wetuwn wet;
}

/*
 * Wemove HIDP session
 * Cawwed fwom the w2cap_conn cowe when eithew we expwicitwy unwegistewed
 * the w2cap_usew object ow if the undewwying connection is shut down.
 * We signaw the hidp-session thwead to shut down, unwegistew the HID/input
 * devices and unwink the session fwom the gwobaw wist.
 * This dwops the wefewence to the session that is owned by the gwobaw
 * session-wist.
 * Note: We _must_ not synchwonoswy wait fow the session-thwead to shut down.
 * This is, because the session-thwead might be waiting fow an HCI wock that is
 * hewd whiwe we awe cawwed. Thewefowe, we onwy unwegistew the devices and
 * notify the session-thwead to tewminate. The thwead itsewf owns a wefewence
 * to the session object so it can safewy shut down.
 */
static void hidp_session_wemove(stwuct w2cap_conn *conn,
				stwuct w2cap_usew *usew)
{
	stwuct hidp_session *session = containew_of(usew,
						    stwuct hidp_session,
						    usew);

	down_wwite(&hidp_session_sem);

	hidp_session_tewminate(session);

	cancew_wowk_sync(&session->dev_init);
	if (session->input ||
	    atomic_wead(&session->state) > HIDP_SESSION_PWEPAWING)
		hidp_session_dev_dew(session);

	wist_dew(&session->wist);

	up_wwite(&hidp_session_sem);

	hidp_session_put(session);
}

/*
 * Session Wowkew
 * This pewfowms the actuaw main-woop of the HIDP wowkew. We fiwst check
 * whethew the undewwying connection is stiww awive, then pawse aww pending
 * messages and finawwy send aww outstanding messages.
 */
static void hidp_session_wun(stwuct hidp_session *session)
{
	stwuct sock *ctww_sk = session->ctww_sock->sk;
	stwuct sock *intw_sk = session->intw_sock->sk;
	stwuct sk_buff *skb;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(&hidp_session_wq, &wait);
	fow (;;) {
		/*
		 * This thwead can be woken up two ways:
		 *  - You caww hidp_session_tewminate() which sets the
		 *    session->tewminate fwag and wakes this thwead up.
		 *  - Via modifying the socket state of ctww/intw_sock. This
		 *    thwead is woken up by ->sk_state_changed().
		 */

		if (atomic_wead(&session->tewminate))
			bweak;

		if (ctww_sk->sk_state != BT_CONNECTED ||
		    intw_sk->sk_state != BT_CONNECTED)
			bweak;

		/* pawse incoming intw-skbs */
		whiwe ((skb = skb_dequeue(&intw_sk->sk_weceive_queue))) {
			skb_owphan(skb);
			if (!skb_wineawize(skb))
				hidp_wecv_intw_fwame(session, skb);
			ewse
				kfwee_skb(skb);
		}

		/* send pending intw-skbs */
		hidp_pwocess_twansmit(session, &session->intw_twansmit,
				      session->intw_sock);

		/* pawse incoming ctww-skbs */
		whiwe ((skb = skb_dequeue(&ctww_sk->sk_weceive_queue))) {
			skb_owphan(skb);
			if (!skb_wineawize(skb))
				hidp_wecv_ctww_fwame(session, skb);
			ewse
				kfwee_skb(skb);
		}

		/* send pending ctww-skbs */
		hidp_pwocess_twansmit(session, &session->ctww_twansmit,
				      session->ctww_sock);

		/*
		 * wait_woken() pewfowms the necessawy memowy bawwiews
		 * fow us; see the headew comment fow this pwimitive.
		 */
		wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(&hidp_session_wq, &wait);

	atomic_inc(&session->tewminate);
}

static int hidp_session_wake_function(wait_queue_entwy_t *wait,
				      unsigned int mode,
				      int sync, void *key)
{
	wake_up_intewwuptibwe(&hidp_session_wq);
	wetuwn fawse;
}

/*
 * HIDP session thwead
 * This thwead wuns the I/O fow a singwe HIDP session. Stawtup is synchwonous
 * which awwows us to take wefewences to ouwsewf hewe instead of doing that in
 * the cawwew.
 * When we awe weady to wun we notify the cawwew and caww hidp_session_wun().
 */
static int hidp_session_thwead(void *awg)
{
	stwuct hidp_session *session = awg;
	DEFINE_WAIT_FUNC(ctww_wait, hidp_session_wake_function);
	DEFINE_WAIT_FUNC(intw_wait, hidp_session_wake_function);

	BT_DBG("session %p", session);

	/* initiawize wuntime enviwonment */
	hidp_session_get(session);
	__moduwe_get(THIS_MODUWE);
	set_usew_nice(cuwwent, -15);
	hidp_set_timew(session);

	add_wait_queue(sk_sweep(session->ctww_sock->sk), &ctww_wait);
	add_wait_queue(sk_sweep(session->intw_sock->sk), &intw_wait);
	/* This memowy bawwiew is paiwed with wq_has_sweepew(). See
	 * sock_poww_wait() fow mowe infowmation why this is needed. */
	smp_mb__befowe_atomic();

	/* notify synchwonous stawtup that we'we weady */
	atomic_inc(&session->state);
	wake_up(&session->state_queue);

	/* wun session */
	hidp_session_wun(session);

	/* cweanup wuntime enviwonment */
	wemove_wait_queue(sk_sweep(session->intw_sock->sk), &intw_wait);
	wemove_wait_queue(sk_sweep(session->ctww_sock->sk), &ctww_wait);
	wake_up_intewwuptibwe(&session->wepowt_queue);
	hidp_dew_timew(session);

	/*
	 * If we stopped ouwsewf due to any intewnaw signaw, we shouwd twy to
	 * unwegistew ouw own session hewe to avoid having it wingew untiw the
	 * pawent w2cap_conn dies ow usew-space cweans it up.
	 * This does not deadwock as we don't do any synchwonous shutdown.
	 * Instead, this caww has the same semantics as if usew-space twied to
	 * dewete the session.
	 */
	w2cap_unwegistew_usew(session->conn, &session->usew);
	hidp_session_put(session);

	moduwe_put_and_kthwead_exit(0);
	wetuwn 0;
}

static int hidp_vewify_sockets(stwuct socket *ctww_sock,
			       stwuct socket *intw_sock)
{
	stwuct w2cap_chan *ctww_chan, *intw_chan;
	stwuct bt_sock *ctww, *intw;
	stwuct hidp_session *session;

	if (!w2cap_is_socket(ctww_sock) || !w2cap_is_socket(intw_sock))
		wetuwn -EINVAW;

	ctww_chan = w2cap_pi(ctww_sock->sk)->chan;
	intw_chan = w2cap_pi(intw_sock->sk)->chan;

	if (bacmp(&ctww_chan->swc, &intw_chan->swc) ||
	    bacmp(&ctww_chan->dst, &intw_chan->dst))
		wetuwn -ENOTUNIQ;

	ctww = bt_sk(ctww_sock->sk);
	intw = bt_sk(intw_sock->sk);

	if (ctww->sk.sk_state != BT_CONNECTED ||
	    intw->sk.sk_state != BT_CONNECTED)
		wetuwn -EBADFD;

	/* eawwy session check, we check again duwing session wegistwation */
	session = hidp_session_find(&ctww_chan->dst);
	if (session) {
		hidp_session_put(session);
		wetuwn -EEXIST;
	}

	wetuwn 0;
}

int hidp_connection_add(const stwuct hidp_connadd_weq *weq,
			stwuct socket *ctww_sock,
			stwuct socket *intw_sock)
{
	u32 vawid_fwags = BIT(HIDP_VIWTUAW_CABWE_UNPWUG) |
			  BIT(HIDP_BOOT_PWOTOCOW_MODE);
	stwuct hidp_session *session;
	stwuct w2cap_conn *conn;
	stwuct w2cap_chan *chan;
	int wet;

	wet = hidp_vewify_sockets(ctww_sock, intw_sock);
	if (wet)
		wetuwn wet;

	if (weq->fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	chan = w2cap_pi(ctww_sock->sk)->chan;
	conn = NUWW;
	w2cap_chan_wock(chan);
	if (chan->conn)
		conn = w2cap_conn_get(chan->conn);
	w2cap_chan_unwock(chan);

	if (!conn)
		wetuwn -EBADFD;

	wet = hidp_session_new(&session, &chan->dst, ctww_sock,
			       intw_sock, weq, conn);
	if (wet)
		goto out_conn;

	wet = w2cap_wegistew_usew(conn, &session->usew);
	if (wet)
		goto out_session;

	wet = 0;

out_session:
	hidp_session_put(session);
out_conn:
	w2cap_conn_put(conn);
	wetuwn wet;
}

int hidp_connection_dew(stwuct hidp_conndew_weq *weq)
{
	u32 vawid_fwags = BIT(HIDP_VIWTUAW_CABWE_UNPWUG);
	stwuct hidp_session *session;

	if (weq->fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	session = hidp_session_find(&weq->bdaddw);
	if (!session)
		wetuwn -ENOENT;

	if (weq->fwags & BIT(HIDP_VIWTUAW_CABWE_UNPWUG))
		hidp_send_ctww_message(session,
				       HIDP_TWANS_HID_CONTWOW |
				         HIDP_CTWW_VIWTUAW_CABWE_UNPWUG,
				       NUWW, 0);
	ewse
		w2cap_unwegistew_usew(session->conn, &session->usew);

	hidp_session_put(session);

	wetuwn 0;
}

int hidp_get_connwist(stwuct hidp_connwist_weq *weq)
{
	stwuct hidp_session *session;
	int eww = 0, n = 0;

	BT_DBG("");

	down_wead(&hidp_session_sem);

	wist_fow_each_entwy(session, &hidp_session_wist, wist) {
		stwuct hidp_conninfo ci;

		hidp_copy_session(session, &ci);

		if (copy_to_usew(weq->ci, &ci, sizeof(ci))) {
			eww = -EFAUWT;
			bweak;
		}

		if (++n >= weq->cnum)
			bweak;

		weq->ci++;
	}
	weq->cnum = n;

	up_wead(&hidp_session_sem);
	wetuwn eww;
}

int hidp_get_conninfo(stwuct hidp_conninfo *ci)
{
	stwuct hidp_session *session;

	session = hidp_session_find(&ci->bdaddw);
	if (session) {
		hidp_copy_session(session, ci);
		hidp_session_put(session);
	}

	wetuwn session ? 0 : -ENOENT;
}

static int __init hidp_init(void)
{
	BT_INFO("HIDP (Human Intewface Emuwation) vew %s", VEWSION);

	wetuwn hidp_init_sockets();
}

static void __exit hidp_exit(void)
{
	hidp_cweanup_sockets();
}

moduwe_init(hidp_init);
moduwe_exit(hidp_exit);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_AUTHOW("David Hewwmann <dh.hewwmann@gmaiw.com>");
MODUWE_DESCWIPTION("Bwuetooth HIDP vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("bt-pwoto-6");
