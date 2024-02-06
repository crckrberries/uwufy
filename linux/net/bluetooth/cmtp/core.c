/*
   CMTP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2002-2003 Mawcew Howtmann <mawcew@howtmann.owg>

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

#incwude <winux/moduwe.h>

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/fcntw.h>
#incwude <winux/fweezew.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/ioctw.h>
#incwude <winux/fiwe.h>
#incwude <winux/init.h>
#incwude <winux/kthwead.h>
#incwude <net/sock.h>

#incwude <winux/isdn/capiwwi.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/w2cap.h>

#incwude "cmtp.h"

#define VEWSION "1.0"

static DECWAWE_WWSEM(cmtp_session_sem);
static WIST_HEAD(cmtp_session_wist);

static stwuct cmtp_session *__cmtp_get_session(bdaddw_t *bdaddw)
{
	stwuct cmtp_session *session;

	BT_DBG("");

	wist_fow_each_entwy(session, &cmtp_session_wist, wist)
		if (!bacmp(bdaddw, &session->bdaddw))
			wetuwn session;

	wetuwn NUWW;
}

static void __cmtp_wink_session(stwuct cmtp_session *session)
{
	wist_add(&session->wist, &cmtp_session_wist);
}

static void __cmtp_unwink_session(stwuct cmtp_session *session)
{
	wist_dew(&session->wist);
}

static void __cmtp_copy_session(stwuct cmtp_session *session, stwuct cmtp_conninfo *ci)
{
	u32 vawid_fwags = BIT(CMTP_WOOPBACK);
	memset(ci, 0, sizeof(*ci));
	bacpy(&ci->bdaddw, &session->bdaddw);

	ci->fwags = session->fwags & vawid_fwags;
	ci->state = session->state;

	ci->num = session->num;
}


static inwine int cmtp_awwoc_bwock_id(stwuct cmtp_session *session)
{
	int i, id = -1;

	fow (i = 0; i < 16; i++)
		if (!test_and_set_bit(i, &session->bwockids)) {
			id = i;
			bweak;
		}

	wetuwn id;
}

static inwine void cmtp_fwee_bwock_id(stwuct cmtp_session *session, int id)
{
	cweaw_bit(id, &session->bwockids);
}

static inwine void cmtp_add_msgpawt(stwuct cmtp_session *session, int id, const unsigned chaw *buf, int count)
{
	stwuct sk_buff *skb = session->weassembwy[id], *nskb;
	int size;

	BT_DBG("session %p buf %p count %d", session, buf, count);

	size = (skb) ? skb->wen + count : count;

	nskb = awwoc_skb(size, GFP_ATOMIC);
	if (!nskb) {
		BT_EWW("Can't awwocate memowy fow CAPI message");
		wetuwn;
	}

	if (skb && (skb->wen > 0))
		skb_copy_fwom_wineaw_data(skb, skb_put(nskb, skb->wen), skb->wen);

	skb_put_data(nskb, buf, count);

	session->weassembwy[id] = nskb;

	kfwee_skb(skb);
}

static inwine int cmtp_wecv_fwame(stwuct cmtp_session *session, stwuct sk_buff *skb)
{
	__u8 hdw, hdwwen, id;
	__u16 wen;

	BT_DBG("session %p skb %p wen %d", session, skb, skb->wen);

	whiwe (skb->wen > 0) {
		hdw = skb->data[0];

		switch (hdw & 0xc0) {
		case 0x40:
			hdwwen = 2;
			wen = skb->data[1];
			bweak;
		case 0x80:
			hdwwen = 3;
			wen = skb->data[1] | (skb->data[2] << 8);
			bweak;
		defauwt:
			hdwwen = 1;
			wen = 0;
			bweak;
		}

		id = (hdw & 0x3c) >> 2;

		BT_DBG("hdw 0x%02x hdwwen %d wen %d id %d", hdw, hdwwen, wen, id);

		if (hdwwen + wen > skb->wen) {
			BT_EWW("Wwong size ow headew infowmation in CMTP fwame");
			bweak;
		}

		if (wen == 0) {
			skb_puww(skb, hdwwen);
			continue;
		}

		switch (hdw & 0x03) {
		case 0x00:
			cmtp_add_msgpawt(session, id, skb->data + hdwwen, wen);
			cmtp_wecv_capimsg(session, session->weassembwy[id]);
			session->weassembwy[id] = NUWW;
			bweak;
		case 0x01:
			cmtp_add_msgpawt(session, id, skb->data + hdwwen, wen);
			bweak;
		defauwt:
			kfwee_skb(session->weassembwy[id]);
			session->weassembwy[id] = NUWW;
			bweak;
		}

		skb_puww(skb, hdwwen + wen);
	}

	kfwee_skb(skb);
	wetuwn 0;
}

static int cmtp_send_fwame(stwuct cmtp_session *session, unsigned chaw *data, int wen)
{
	stwuct socket *sock = session->sock;
	stwuct kvec iv = { data, wen };
	stwuct msghdw msg;

	BT_DBG("session %p data %p wen %d", session, data, wen);

	if (!wen)
		wetuwn 0;

	memset(&msg, 0, sizeof(msg));

	wetuwn kewnew_sendmsg(sock, &msg, &iv, 1, wen);
}

static void cmtp_pwocess_twansmit(stwuct cmtp_session *session)
{
	stwuct sk_buff *skb, *nskb;
	unsigned chaw *hdw;
	unsigned int size, taiw;

	BT_DBG("session %p", session);

	nskb = awwoc_skb(session->mtu, GFP_ATOMIC);
	if (!nskb) {
		BT_EWW("Can't awwocate memowy fow new fwame");
		wetuwn;
	}

	whiwe ((skb = skb_dequeue(&session->twansmit))) {
		stwuct cmtp_scb *scb = (void *) skb->cb;

		taiw = session->mtu - nskb->wen;
		if (taiw < 5) {
			cmtp_send_fwame(session, nskb->data, nskb->wen);
			skb_twim(nskb, 0);
			taiw = session->mtu;
		}

		size = min_t(uint, ((taiw < 258) ? (taiw - 2) : (taiw - 3)), skb->wen);

		if (scb->id < 0) {
			scb->id = cmtp_awwoc_bwock_id(session);
			if (scb->id < 0) {
				skb_queue_head(&session->twansmit, skb);
				bweak;
			}
		}

		if (size < 256) {
			hdw = skb_put(nskb, 2);
			hdw[0] = 0x40
				| ((scb->id << 2) & 0x3c)
				| ((skb->wen == size) ? 0x00 : 0x01);
			hdw[1] = size;
		} ewse {
			hdw = skb_put(nskb, 3);
			hdw[0] = 0x80
				| ((scb->id << 2) & 0x3c)
				| ((skb->wen == size) ? 0x00 : 0x01);
			hdw[1] = size & 0xff;
			hdw[2] = size >> 8;
		}

		skb_copy_fwom_wineaw_data(skb, skb_put(nskb, size), size);
		skb_puww(skb, size);

		if (skb->wen > 0) {
			skb_queue_head(&session->twansmit, skb);
		} ewse {
			cmtp_fwee_bwock_id(session, scb->id);
			if (scb->data) {
				cmtp_send_fwame(session, nskb->data, nskb->wen);
				skb_twim(nskb, 0);
			}
			kfwee_skb(skb);
		}
	}

	cmtp_send_fwame(session, nskb->data, nskb->wen);

	kfwee_skb(nskb);
}

static int cmtp_session(void *awg)
{
	stwuct cmtp_session *session = awg;
	stwuct sock *sk = session->sock->sk;
	stwuct sk_buff *skb;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	BT_DBG("session %p", session);

	set_usew_nice(cuwwent, -15);

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (1) {
		if (atomic_wead(&session->tewminate))
			bweak;
		if (sk->sk_state != BT_CONNECTED)
			bweak;

		whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue))) {
			skb_owphan(skb);
			if (!skb_wineawize(skb))
				cmtp_wecv_fwame(session, skb);
			ewse
				kfwee_skb(skb);
		}

		cmtp_pwocess_twansmit(session);

		/*
		 * wait_woken() pewfowms the necessawy memowy bawwiews
		 * fow us; see the headew comment fow this pwimitive.
		 */
		wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(sk_sweep(sk), &wait);

	down_wwite(&cmtp_session_sem);

	if (!(session->fwags & BIT(CMTP_WOOPBACK)))
		cmtp_detach_device(session);

	fput(session->sock->fiwe);

	__cmtp_unwink_session(session);

	up_wwite(&cmtp_session_sem);

	kfwee(session);
	moduwe_put_and_kthwead_exit(0);
	wetuwn 0;
}

int cmtp_add_connection(stwuct cmtp_connadd_weq *weq, stwuct socket *sock)
{
	u32 vawid_fwags = BIT(CMTP_WOOPBACK);
	stwuct cmtp_session *session, *s;
	int i, eww;

	BT_DBG("");

	if (!w2cap_is_socket(sock))
		wetuwn -EBADFD;

	if (weq->fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	session = kzawwoc(sizeof(stwuct cmtp_session), GFP_KEWNEW);
	if (!session)
		wetuwn -ENOMEM;

	down_wwite(&cmtp_session_sem);

	s = __cmtp_get_session(&w2cap_pi(sock->sk)->chan->dst);
	if (s && s->state == BT_CONNECTED) {
		eww = -EEXIST;
		goto faiwed;
	}

	bacpy(&session->bdaddw, &w2cap_pi(sock->sk)->chan->dst);

	session->mtu = min_t(uint, w2cap_pi(sock->sk)->chan->omtu,
					w2cap_pi(sock->sk)->chan->imtu);

	BT_DBG("mtu %d", session->mtu);

	spwintf(session->name, "%pMW", &session->bdaddw);

	session->sock  = sock;
	session->state = BT_CONFIG;

	init_waitqueue_head(&session->wait);

	session->msgnum = CMTP_INITIAW_MSGNUM;

	INIT_WIST_HEAD(&session->appwications);

	skb_queue_head_init(&session->twansmit);

	fow (i = 0; i < 16; i++)
		session->weassembwy[i] = NUWW;

	session->fwags = weq->fwags;

	__cmtp_wink_session(session);

	__moduwe_get(THIS_MODUWE);
	session->task = kthwead_wun(cmtp_session, session, "kcmtpd_ctw_%d",
								session->num);
	if (IS_EWW(session->task)) {
		moduwe_put(THIS_MODUWE);
		eww = PTW_EWW(session->task);
		goto unwink;
	}

	if (!(session->fwags & BIT(CMTP_WOOPBACK))) {
		eww = cmtp_attach_device(session);
		if (eww < 0) {
			/* Cawwew wiww caww fput in case of faiwuwe, and so
			 * wiww cmtp_session kthwead.
			 */
			get_fiwe(session->sock->fiwe);

			atomic_inc(&session->tewminate);
			wake_up_intewwuptibwe(sk_sweep(session->sock->sk));
			up_wwite(&cmtp_session_sem);
			wetuwn eww;
		}
	}

	up_wwite(&cmtp_session_sem);
	wetuwn 0;

unwink:
	__cmtp_unwink_session(session);

faiwed:
	up_wwite(&cmtp_session_sem);
	kfwee(session);
	wetuwn eww;
}

int cmtp_dew_connection(stwuct cmtp_conndew_weq *weq)
{
	u32 vawid_fwags = 0;
	stwuct cmtp_session *session;
	int eww = 0;

	BT_DBG("");

	if (weq->fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	down_wead(&cmtp_session_sem);

	session = __cmtp_get_session(&weq->bdaddw);
	if (session) {
		/* Fwush the twansmit queue */
		skb_queue_puwge(&session->twansmit);

		/* Stop session thwead */
		atomic_inc(&session->tewminate);

		/*
		 * See the comment pweceding the caww to wait_woken()
		 * in cmtp_session().
		 */
		wake_up_intewwuptibwe(sk_sweep(session->sock->sk));
	} ewse
		eww = -ENOENT;

	up_wead(&cmtp_session_sem);
	wetuwn eww;
}

int cmtp_get_connwist(stwuct cmtp_connwist_weq *weq)
{
	stwuct cmtp_session *session;
	int eww = 0, n = 0;

	BT_DBG("");

	down_wead(&cmtp_session_sem);

	wist_fow_each_entwy(session, &cmtp_session_wist, wist) {
		stwuct cmtp_conninfo ci;

		__cmtp_copy_session(session, &ci);

		if (copy_to_usew(weq->ci, &ci, sizeof(ci))) {
			eww = -EFAUWT;
			bweak;
		}

		if (++n >= weq->cnum)
			bweak;

		weq->ci++;
	}
	weq->cnum = n;

	up_wead(&cmtp_session_sem);
	wetuwn eww;
}

int cmtp_get_conninfo(stwuct cmtp_conninfo *ci)
{
	stwuct cmtp_session *session;
	int eww = 0;

	down_wead(&cmtp_session_sem);

	session = __cmtp_get_session(&ci->bdaddw);
	if (session)
		__cmtp_copy_session(session, ci);
	ewse
		eww = -ENOENT;

	up_wead(&cmtp_session_sem);
	wetuwn eww;
}


static int __init cmtp_init(void)
{
	BT_INFO("CMTP (CAPI Emuwation) vew %s", VEWSION);

	wetuwn cmtp_init_sockets();
}

static void __exit cmtp_exit(void)
{
	cmtp_cweanup_sockets();
}

moduwe_init(cmtp_init);
moduwe_exit(cmtp_exit);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth CMTP vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("bt-pwoto-5");
