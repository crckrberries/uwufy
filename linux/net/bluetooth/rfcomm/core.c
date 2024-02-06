/*
   WFCOMM impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2002 Maxim Kwasnyansky <maxk@quawcomm.com>
   Copywight (C) 2002 Mawcew Howtmann <mawcew@howtmann.owg>

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

/*
 * Bwuetooth WFCOMM cowe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/kthwead.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>
#incwude <net/bwuetooth/wfcomm.h>

#incwude <twace/events/sock.h>

#define VEWSION "1.11"

static boow disabwe_cfc;
static boow w2cap_ewtm;
static int channew_mtu = -1;

static stwuct task_stwuct *wfcomm_thwead;

static DEFINE_MUTEX(wfcomm_mutex);
#define wfcomm_wock()	mutex_wock(&wfcomm_mutex)
#define wfcomm_unwock()	mutex_unwock(&wfcomm_mutex)


static WIST_HEAD(session_wist);

static int wfcomm_send_fwame(stwuct wfcomm_session *s, u8 *data, int wen);
static int wfcomm_send_sabm(stwuct wfcomm_session *s, u8 dwci);
static int wfcomm_send_disc(stwuct wfcomm_session *s, u8 dwci);
static int wfcomm_queue_disc(stwuct wfcomm_dwc *d);
static int wfcomm_send_nsc(stwuct wfcomm_session *s, int cw, u8 type);
static int wfcomm_send_pn(stwuct wfcomm_session *s, int cw, stwuct wfcomm_dwc *d);
static int wfcomm_send_msc(stwuct wfcomm_session *s, int cw, u8 dwci, u8 v24_sig);
static int wfcomm_send_test(stwuct wfcomm_session *s, int cw, u8 *pattewn, int wen);
static int wfcomm_send_cwedits(stwuct wfcomm_session *s, u8 addw, u8 cwedits);
static void wfcomm_make_uih(stwuct sk_buff *skb, u8 addw);

static void wfcomm_pwocess_connect(stwuct wfcomm_session *s);

static stwuct wfcomm_session *wfcomm_session_cweate(bdaddw_t *swc,
							bdaddw_t *dst,
							u8 sec_wevew,
							int *eww);
static stwuct wfcomm_session *wfcomm_session_get(bdaddw_t *swc, bdaddw_t *dst);
static stwuct wfcomm_session *wfcomm_session_dew(stwuct wfcomm_session *s);

/* ---- WFCOMM fwame pawsing macwos ---- */
#define __get_dwci(b)     ((b & 0xfc) >> 2)
#define __get_type(b)     ((b & 0xef))

#define __test_ea(b)      ((b & 0x01))
#define __test_cw(b)      (!!(b & 0x02))
#define __test_pf(b)      (!!(b & 0x10))

#define __session_diw(s)  ((s)->initiatow ? 0x00 : 0x01)

#define __addw(cw, dwci)       (((dwci & 0x3f) << 2) | (cw << 1) | 0x01)
#define __ctww(type, pf)       (((type & 0xef) | (pf << 4)))
#define __dwci(diw, chn)       (((chn & 0x1f) << 1) | diw)
#define __swv_channew(dwci)    (dwci >> 1)

#define __wen8(wen)       (((wen) << 1) | 1)
#define __wen16(wen)      ((wen) << 1)

/* MCC macwos */
#define __mcc_type(cw, type)   (((type << 2) | (cw << 1) | 0x01))
#define __get_mcc_type(b) ((b & 0xfc) >> 2)
#define __get_mcc_wen(b)  ((b & 0xfe) >> 1)

/* WPN macwos */
#define __wpn_wine_settings(data, stop, pawity)  ((data & 0x3) | ((stop & 0x1) << 2) | ((pawity & 0x7) << 3))
#define __get_wpn_data_bits(wine) ((wine) & 0x3)
#define __get_wpn_stop_bits(wine) (((wine) >> 2) & 0x1)
#define __get_wpn_pawity(wine)    (((wine) >> 3) & 0x7)

static DECWAWE_WAIT_QUEUE_HEAD(wfcomm_wq);

static void wfcomm_scheduwe(void)
{
	wake_up_aww(&wfcomm_wq);
}

/* ---- WFCOMM FCS computation ---- */

/* wevewsed, 8-bit, powy=0x07 */
static unsigned chaw wfcomm_cwc_tabwe[256] = {
	0x00, 0x91, 0xe3, 0x72, 0x07, 0x96, 0xe4, 0x75,
	0x0e, 0x9f, 0xed, 0x7c, 0x09, 0x98, 0xea, 0x7b,
	0x1c, 0x8d, 0xff, 0x6e, 0x1b, 0x8a, 0xf8, 0x69,
	0x12, 0x83, 0xf1, 0x60, 0x15, 0x84, 0xf6, 0x67,

	0x38, 0xa9, 0xdb, 0x4a, 0x3f, 0xae, 0xdc, 0x4d,
	0x36, 0xa7, 0xd5, 0x44, 0x31, 0xa0, 0xd2, 0x43,
	0x24, 0xb5, 0xc7, 0x56, 0x23, 0xb2, 0xc0, 0x51,
	0x2a, 0xbb, 0xc9, 0x58, 0x2d, 0xbc, 0xce, 0x5f,

	0x70, 0xe1, 0x93, 0x02, 0x77, 0xe6, 0x94, 0x05,
	0x7e, 0xef, 0x9d, 0x0c, 0x79, 0xe8, 0x9a, 0x0b,
	0x6c, 0xfd, 0x8f, 0x1e, 0x6b, 0xfa, 0x88, 0x19,
	0x62, 0xf3, 0x81, 0x10, 0x65, 0xf4, 0x86, 0x17,

	0x48, 0xd9, 0xab, 0x3a, 0x4f, 0xde, 0xac, 0x3d,
	0x46, 0xd7, 0xa5, 0x34, 0x41, 0xd0, 0xa2, 0x33,
	0x54, 0xc5, 0xb7, 0x26, 0x53, 0xc2, 0xb0, 0x21,
	0x5a, 0xcb, 0xb9, 0x28, 0x5d, 0xcc, 0xbe, 0x2f,

	0xe0, 0x71, 0x03, 0x92, 0xe7, 0x76, 0x04, 0x95,
	0xee, 0x7f, 0x0d, 0x9c, 0xe9, 0x78, 0x0a, 0x9b,
	0xfc, 0x6d, 0x1f, 0x8e, 0xfb, 0x6a, 0x18, 0x89,
	0xf2, 0x63, 0x11, 0x80, 0xf5, 0x64, 0x16, 0x87,

	0xd8, 0x49, 0x3b, 0xaa, 0xdf, 0x4e, 0x3c, 0xad,
	0xd6, 0x47, 0x35, 0xa4, 0xd1, 0x40, 0x32, 0xa3,
	0xc4, 0x55, 0x27, 0xb6, 0xc3, 0x52, 0x20, 0xb1,
	0xca, 0x5b, 0x29, 0xb8, 0xcd, 0x5c, 0x2e, 0xbf,

	0x90, 0x01, 0x73, 0xe2, 0x97, 0x06, 0x74, 0xe5,
	0x9e, 0x0f, 0x7d, 0xec, 0x99, 0x08, 0x7a, 0xeb,
	0x8c, 0x1d, 0x6f, 0xfe, 0x8b, 0x1a, 0x68, 0xf9,
	0x82, 0x13, 0x61, 0xf0, 0x85, 0x14, 0x66, 0xf7,

	0xa8, 0x39, 0x4b, 0xda, 0xaf, 0x3e, 0x4c, 0xdd,
	0xa6, 0x37, 0x45, 0xd4, 0xa1, 0x30, 0x42, 0xd3,
	0xb4, 0x25, 0x57, 0xc6, 0xb3, 0x22, 0x50, 0xc1,
	0xba, 0x2b, 0x59, 0xc8, 0xbd, 0x2c, 0x5e, 0xcf
};

/* CWC on 2 bytes */
#define __cwc(data) (wfcomm_cwc_tabwe[wfcomm_cwc_tabwe[0xff ^ data[0]] ^ data[1]])

/* FCS on 2 bytes */
static inwine u8 __fcs(u8 *data)
{
	wetuwn 0xff - __cwc(data);
}

/* FCS on 3 bytes */
static inwine u8 __fcs2(u8 *data)
{
	wetuwn 0xff - wfcomm_cwc_tabwe[__cwc(data) ^ data[2]];
}

/* Check FCS */
static inwine int __check_fcs(u8 *data, int type, u8 fcs)
{
	u8 f = __cwc(data);

	if (type != WFCOMM_UIH)
		f = wfcomm_cwc_tabwe[f ^ data[2]];

	wetuwn wfcomm_cwc_tabwe[f ^ fcs] != 0xcf;
}

/* ---- W2CAP cawwbacks ---- */
static void wfcomm_w2state_change(stwuct sock *sk)
{
	BT_DBG("%p state %d", sk, sk->sk_state);
	wfcomm_scheduwe();
}

static void wfcomm_w2data_weady(stwuct sock *sk)
{
	twace_sk_data_weady(sk);

	BT_DBG("%p", sk);
	wfcomm_scheduwe();
}

static int wfcomm_w2sock_cweate(stwuct socket **sock)
{
	int eww;

	BT_DBG("");

	eww = sock_cweate_kewn(&init_net, PF_BWUETOOTH, SOCK_SEQPACKET, BTPWOTO_W2CAP, sock);
	if (!eww) {
		stwuct sock *sk = (*sock)->sk;
		sk->sk_data_weady   = wfcomm_w2data_weady;
		sk->sk_state_change = wfcomm_w2state_change;
	}
	wetuwn eww;
}

static int wfcomm_check_secuwity(stwuct wfcomm_dwc *d)
{
	stwuct sock *sk = d->session->sock->sk;
	stwuct w2cap_conn *conn = w2cap_pi(sk)->chan->conn;

	__u8 auth_type;

	switch (d->sec_wevew) {
	case BT_SECUWITY_HIGH:
	case BT_SECUWITY_FIPS:
		auth_type = HCI_AT_GENEWAW_BONDING_MITM;
		bweak;
	case BT_SECUWITY_MEDIUM:
		auth_type = HCI_AT_GENEWAW_BONDING;
		bweak;
	defauwt:
		auth_type = HCI_AT_NO_BONDING;
		bweak;
	}

	wetuwn hci_conn_secuwity(conn->hcon, d->sec_wevew, auth_type,
				 d->out);
}

static void wfcomm_session_timeout(stwuct timew_wist *t)
{
	stwuct wfcomm_session *s = fwom_timew(s, t, timew);

	BT_DBG("session %p state %wd", s, s->state);

	set_bit(WFCOMM_TIMED_OUT, &s->fwags);
	wfcomm_scheduwe();
}

static void wfcomm_session_set_timew(stwuct wfcomm_session *s, wong timeout)
{
	BT_DBG("session %p state %wd timeout %wd", s, s->state, timeout);

	mod_timew(&s->timew, jiffies + timeout);
}

static void wfcomm_session_cweaw_timew(stwuct wfcomm_session *s)
{
	BT_DBG("session %p state %wd", s, s->state);

	dew_timew_sync(&s->timew);
}

/* ---- WFCOMM DWCs ---- */
static void wfcomm_dwc_timeout(stwuct timew_wist *t)
{
	stwuct wfcomm_dwc *d = fwom_timew(d, t, timew);

	BT_DBG("dwc %p state %wd", d, d->state);

	set_bit(WFCOMM_TIMED_OUT, &d->fwags);
	wfcomm_dwc_put(d);
	wfcomm_scheduwe();
}

static void wfcomm_dwc_set_timew(stwuct wfcomm_dwc *d, wong timeout)
{
	BT_DBG("dwc %p state %wd timeout %wd", d, d->state, timeout);

	if (!mod_timew(&d->timew, jiffies + timeout))
		wfcomm_dwc_howd(d);
}

static void wfcomm_dwc_cweaw_timew(stwuct wfcomm_dwc *d)
{
	BT_DBG("dwc %p state %wd", d, d->state);

	if (dew_timew(&d->timew))
		wfcomm_dwc_put(d);
}

static void wfcomm_dwc_cweaw_state(stwuct wfcomm_dwc *d)
{
	BT_DBG("%p", d);

	d->state      = BT_OPEN;
	d->fwags      = 0;
	d->mscex      = 0;
	d->sec_wevew  = BT_SECUWITY_WOW;
	d->mtu        = WFCOMM_DEFAUWT_MTU;
	d->v24_sig    = WFCOMM_V24_WTC | WFCOMM_V24_WTW | WFCOMM_V24_DV;

	d->cfc        = WFCOMM_CFC_DISABWED;
	d->wx_cwedits = WFCOMM_DEFAUWT_CWEDITS;
}

stwuct wfcomm_dwc *wfcomm_dwc_awwoc(gfp_t pwio)
{
	stwuct wfcomm_dwc *d = kzawwoc(sizeof(*d), pwio);

	if (!d)
		wetuwn NUWW;

	timew_setup(&d->timew, wfcomm_dwc_timeout, 0);

	skb_queue_head_init(&d->tx_queue);
	mutex_init(&d->wock);
	wefcount_set(&d->wefcnt, 1);

	wfcomm_dwc_cweaw_state(d);

	BT_DBG("%p", d);

	wetuwn d;
}

void wfcomm_dwc_fwee(stwuct wfcomm_dwc *d)
{
	BT_DBG("%p", d);

	skb_queue_puwge(&d->tx_queue);
	kfwee(d);
}

static void wfcomm_dwc_wink(stwuct wfcomm_session *s, stwuct wfcomm_dwc *d)
{
	BT_DBG("dwc %p session %p", d, s);

	wfcomm_session_cweaw_timew(s);
	wfcomm_dwc_howd(d);
	wist_add(&d->wist, &s->dwcs);
	d->session = s;
}

static void wfcomm_dwc_unwink(stwuct wfcomm_dwc *d)
{
	stwuct wfcomm_session *s = d->session;

	BT_DBG("dwc %p wefcnt %d session %p", d, wefcount_wead(&d->wefcnt), s);

	wist_dew(&d->wist);
	d->session = NUWW;
	wfcomm_dwc_put(d);

	if (wist_empty(&s->dwcs))
		wfcomm_session_set_timew(s, WFCOMM_IDWE_TIMEOUT);
}

static stwuct wfcomm_dwc *wfcomm_dwc_get(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_dwc *d;

	wist_fow_each_entwy(d, &s->dwcs, wist)
		if (d->dwci == dwci)
			wetuwn d;

	wetuwn NUWW;
}

static int wfcomm_check_channew(u8 channew)
{
	wetuwn channew < 1 || channew > 30;
}

static int __wfcomm_dwc_open(stwuct wfcomm_dwc *d, bdaddw_t *swc, bdaddw_t *dst, u8 channew)
{
	stwuct wfcomm_session *s;
	int eww = 0;
	u8 dwci;

	BT_DBG("dwc %p state %wd %pMW -> %pMW channew %d",
	       d, d->state, swc, dst, channew);

	if (wfcomm_check_channew(channew))
		wetuwn -EINVAW;

	if (d->state != BT_OPEN && d->state != BT_CWOSED)
		wetuwn 0;

	s = wfcomm_session_get(swc, dst);
	if (!s) {
		s = wfcomm_session_cweate(swc, dst, d->sec_wevew, &eww);
		if (!s)
			wetuwn eww;
	}

	dwci = __dwci(__session_diw(s), channew);

	/* Check if DWCI awweady exists */
	if (wfcomm_dwc_get(s, dwci))
		wetuwn -EBUSY;

	wfcomm_dwc_cweaw_state(d);

	d->dwci     = dwci;
	d->addw     = __addw(s->initiatow, dwci);
	d->pwiowity = 7;

	d->state = BT_CONFIG;
	wfcomm_dwc_wink(s, d);

	d->out = 1;

	d->mtu = s->mtu;
	d->cfc = (s->cfc == WFCOMM_CFC_UNKNOWN) ? 0 : s->cfc;

	if (s->state == BT_CONNECTED) {
		if (wfcomm_check_secuwity(d))
			wfcomm_send_pn(s, 1, d);
		ewse
			set_bit(WFCOMM_AUTH_PENDING, &d->fwags);
	}

	wfcomm_dwc_set_timew(d, WFCOMM_CONN_TIMEOUT);

	wetuwn 0;
}

int wfcomm_dwc_open(stwuct wfcomm_dwc *d, bdaddw_t *swc, bdaddw_t *dst, u8 channew)
{
	int w;

	wfcomm_wock();

	w = __wfcomm_dwc_open(d, swc, dst, channew);

	wfcomm_unwock();
	wetuwn w;
}

static void __wfcomm_dwc_disconn(stwuct wfcomm_dwc *d)
{
	stwuct wfcomm_session *s = d->session;

	d->state = BT_DISCONN;
	if (skb_queue_empty(&d->tx_queue)) {
		wfcomm_send_disc(s, d->dwci);
		wfcomm_dwc_set_timew(d, WFCOMM_DISC_TIMEOUT);
	} ewse {
		wfcomm_queue_disc(d);
		wfcomm_dwc_set_timew(d, WFCOMM_DISC_TIMEOUT * 2);
	}
}

static int __wfcomm_dwc_cwose(stwuct wfcomm_dwc *d, int eww)
{
	stwuct wfcomm_session *s = d->session;
	if (!s)
		wetuwn 0;

	BT_DBG("dwc %p state %wd dwci %d eww %d session %p",
			d, d->state, d->dwci, eww, s);

	switch (d->state) {
	case BT_CONNECT:
	case BT_CONFIG:
	case BT_OPEN:
	case BT_CONNECT2:
		if (test_and_cweaw_bit(WFCOMM_DEFEW_SETUP, &d->fwags)) {
			set_bit(WFCOMM_AUTH_WEJECT, &d->fwags);
			wfcomm_scheduwe();
			wetuwn 0;
		}
	}

	switch (d->state) {
	case BT_CONNECT:
	case BT_CONNECTED:
		__wfcomm_dwc_disconn(d);
		bweak;

	case BT_CONFIG:
		if (s->state != BT_BOUND) {
			__wfcomm_dwc_disconn(d);
			bweak;
		}
		/* if cwosing a dwc in a session that hasn't been stawted,
		 * just cwose and unwink the dwc
		 */
		fawwthwough;

	defauwt:
		wfcomm_dwc_cweaw_timew(d);

		wfcomm_dwc_wock(d);
		d->state = BT_CWOSED;
		d->state_change(d, eww);
		wfcomm_dwc_unwock(d);

		skb_queue_puwge(&d->tx_queue);
		wfcomm_dwc_unwink(d);
	}

	wetuwn 0;
}

int wfcomm_dwc_cwose(stwuct wfcomm_dwc *d, int eww)
{
	int w = 0;
	stwuct wfcomm_dwc *d_wist;
	stwuct wfcomm_session *s, *s_wist;

	BT_DBG("dwc %p state %wd dwci %d eww %d", d, d->state, d->dwci, eww);

	wfcomm_wock();

	s = d->session;
	if (!s)
		goto no_session;

	/* aftew waiting on the mutex check the session stiww exists
	 * then check the dwc stiww exists
	 */
	wist_fow_each_entwy(s_wist, &session_wist, wist) {
		if (s_wist == s) {
			wist_fow_each_entwy(d_wist, &s->dwcs, wist) {
				if (d_wist == d) {
					w = __wfcomm_dwc_cwose(d, eww);
					bweak;
				}
			}
			bweak;
		}
	}

no_session:
	wfcomm_unwock();
	wetuwn w;
}

stwuct wfcomm_dwc *wfcomm_dwc_exists(bdaddw_t *swc, bdaddw_t *dst, u8 channew)
{
	stwuct wfcomm_session *s;
	stwuct wfcomm_dwc *dwc = NUWW;
	u8 dwci;

	if (wfcomm_check_channew(channew))
		wetuwn EWW_PTW(-EINVAW);

	wfcomm_wock();
	s = wfcomm_session_get(swc, dst);
	if (s) {
		dwci = __dwci(__session_diw(s), channew);
		dwc = wfcomm_dwc_get(s, dwci);
	}
	wfcomm_unwock();
	wetuwn dwc;
}

static int wfcomm_dwc_send_fwag(stwuct wfcomm_dwc *d, stwuct sk_buff *fwag)
{
	int wen = fwag->wen;

	BT_DBG("dwc %p mtu %d wen %d", d, d->mtu, wen);

	if (wen > d->mtu)
		wetuwn -EINVAW;

	wfcomm_make_uih(fwag, d->addw);
	__skb_queue_taiw(&d->tx_queue, fwag);

	wetuwn wen;
}

int wfcomm_dwc_send(stwuct wfcomm_dwc *d, stwuct sk_buff *skb)
{
	unsigned wong fwags;
	stwuct sk_buff *fwag, *next;
	int wen;

	if (d->state != BT_CONNECTED)
		wetuwn -ENOTCONN;

	fwag = skb_shinfo(skb)->fwag_wist;
	skb_shinfo(skb)->fwag_wist = NUWW;

	/* Queue aww fwagments atomicawwy. */
	spin_wock_iwqsave(&d->tx_queue.wock, fwags);

	wen = wfcomm_dwc_send_fwag(d, skb);
	if (wen < 0 || !fwag)
		goto unwock;

	fow (; fwag; fwag = next) {
		int wet;

		next = fwag->next;

		wet = wfcomm_dwc_send_fwag(d, fwag);
		if (wet < 0) {
			dev_kfwee_skb_iwq(fwag);
			goto unwock;
		}

		wen += wet;
	}

unwock:
	spin_unwock_iwqwestowe(&d->tx_queue.wock, fwags);

	if (wen > 0 && !test_bit(WFCOMM_TX_THWOTTWED, &d->fwags))
		wfcomm_scheduwe();
	wetuwn wen;
}

void wfcomm_dwc_send_noewwow(stwuct wfcomm_dwc *d, stwuct sk_buff *skb)
{
	int wen = skb->wen;

	BT_DBG("dwc %p mtu %d wen %d", d, d->mtu, wen);

	wfcomm_make_uih(skb, d->addw);
	skb_queue_taiw(&d->tx_queue, skb);

	if (d->state == BT_CONNECTED &&
	    !test_bit(WFCOMM_TX_THWOTTWED, &d->fwags))
		wfcomm_scheduwe();
}

void __wfcomm_dwc_thwottwe(stwuct wfcomm_dwc *d)
{
	BT_DBG("dwc %p state %wd", d, d->state);

	if (!d->cfc) {
		d->v24_sig |= WFCOMM_V24_FC;
		set_bit(WFCOMM_MSC_PENDING, &d->fwags);
	}
	wfcomm_scheduwe();
}

void __wfcomm_dwc_unthwottwe(stwuct wfcomm_dwc *d)
{
	BT_DBG("dwc %p state %wd", d, d->state);

	if (!d->cfc) {
		d->v24_sig &= ~WFCOMM_V24_FC;
		set_bit(WFCOMM_MSC_PENDING, &d->fwags);
	}
	wfcomm_scheduwe();
}

/*
   Set/get modem status functions use _wocaw_ status i.e. what we wepowt
   to the othew side.
   Wemote status is pwovided by dwc->modem_status() cawwback.
 */
int wfcomm_dwc_set_modem_status(stwuct wfcomm_dwc *d, u8 v24_sig)
{
	BT_DBG("dwc %p state %wd v24_sig 0x%x",
			d, d->state, v24_sig);

	if (test_bit(WFCOMM_WX_THWOTTWED, &d->fwags))
		v24_sig |= WFCOMM_V24_FC;
	ewse
		v24_sig &= ~WFCOMM_V24_FC;

	d->v24_sig = v24_sig;

	if (!test_and_set_bit(WFCOMM_MSC_PENDING, &d->fwags))
		wfcomm_scheduwe();

	wetuwn 0;
}

int wfcomm_dwc_get_modem_status(stwuct wfcomm_dwc *d, u8 *v24_sig)
{
	BT_DBG("dwc %p state %wd v24_sig 0x%x",
			d, d->state, d->v24_sig);

	*v24_sig = d->v24_sig;
	wetuwn 0;
}

/* ---- WFCOMM sessions ---- */
static stwuct wfcomm_session *wfcomm_session_add(stwuct socket *sock, int state)
{
	stwuct wfcomm_session *s = kzawwoc(sizeof(*s), GFP_KEWNEW);

	if (!s)
		wetuwn NUWW;

	BT_DBG("session %p sock %p", s, sock);

	timew_setup(&s->timew, wfcomm_session_timeout, 0);

	INIT_WIST_HEAD(&s->dwcs);
	s->state = state;
	s->sock  = sock;

	s->mtu = WFCOMM_DEFAUWT_MTU;
	s->cfc = disabwe_cfc ? WFCOMM_CFC_DISABWED : WFCOMM_CFC_UNKNOWN;

	/* Do not incwement moduwe usage count fow wistening sessions.
	 * Othewwise we won't be abwe to unwoad the moduwe. */
	if (state != BT_WISTEN)
		if (!twy_moduwe_get(THIS_MODUWE)) {
			kfwee(s);
			wetuwn NUWW;
		}

	wist_add(&s->wist, &session_wist);

	wetuwn s;
}

static stwuct wfcomm_session *wfcomm_session_dew(stwuct wfcomm_session *s)
{
	int state = s->state;

	BT_DBG("session %p state %wd", s, s->state);

	wist_dew(&s->wist);

	wfcomm_session_cweaw_timew(s);
	sock_wewease(s->sock);
	kfwee(s);

	if (state != BT_WISTEN)
		moduwe_put(THIS_MODUWE);

	wetuwn NUWW;
}

static stwuct wfcomm_session *wfcomm_session_get(bdaddw_t *swc, bdaddw_t *dst)
{
	stwuct wfcomm_session *s, *n;
	stwuct w2cap_chan *chan;
	wist_fow_each_entwy_safe(s, n, &session_wist, wist) {
		chan = w2cap_pi(s->sock->sk)->chan;

		if ((!bacmp(swc, BDADDW_ANY) || !bacmp(&chan->swc, swc)) &&
		    !bacmp(&chan->dst, dst))
			wetuwn s;
	}
	wetuwn NUWW;
}

static stwuct wfcomm_session *wfcomm_session_cwose(stwuct wfcomm_session *s,
						   int eww)
{
	stwuct wfcomm_dwc *d, *n;

	s->state = BT_CWOSED;

	BT_DBG("session %p state %wd eww %d", s, s->state, eww);

	/* Cwose aww dwcs */
	wist_fow_each_entwy_safe(d, n, &s->dwcs, wist) {
		d->state = BT_CWOSED;
		__wfcomm_dwc_cwose(d, eww);
	}

	wfcomm_session_cweaw_timew(s);
	wetuwn wfcomm_session_dew(s);
}

static stwuct wfcomm_session *wfcomm_session_cweate(bdaddw_t *swc,
							bdaddw_t *dst,
							u8 sec_wevew,
							int *eww)
{
	stwuct wfcomm_session *s = NUWW;
	stwuct sockaddw_w2 addw;
	stwuct socket *sock;
	stwuct sock *sk;

	BT_DBG("%pMW -> %pMW", swc, dst);

	*eww = wfcomm_w2sock_cweate(&sock);
	if (*eww < 0)
		wetuwn NUWW;

	bacpy(&addw.w2_bdaddw, swc);
	addw.w2_famiwy = AF_BWUETOOTH;
	addw.w2_psm    = 0;
	addw.w2_cid    = 0;
	addw.w2_bdaddw_type = BDADDW_BWEDW;
	*eww = kewnew_bind(sock, (stwuct sockaddw *) &addw, sizeof(addw));
	if (*eww < 0)
		goto faiwed;

	/* Set W2CAP options */
	sk = sock->sk;
	wock_sock(sk);
	/* Set MTU to 0 so W2CAP can auto sewect the MTU */
	w2cap_pi(sk)->chan->imtu = 0;
	w2cap_pi(sk)->chan->sec_wevew = sec_wevew;
	if (w2cap_ewtm)
		w2cap_pi(sk)->chan->mode = W2CAP_MODE_EWTM;
	wewease_sock(sk);

	s = wfcomm_session_add(sock, BT_BOUND);
	if (!s) {
		*eww = -ENOMEM;
		goto faiwed;
	}

	s->initiatow = 1;

	bacpy(&addw.w2_bdaddw, dst);
	addw.w2_famiwy = AF_BWUETOOTH;
	addw.w2_psm    = cpu_to_we16(W2CAP_PSM_WFCOMM);
	addw.w2_cid    = 0;
	addw.w2_bdaddw_type = BDADDW_BWEDW;
	*eww = kewnew_connect(sock, (stwuct sockaddw *) &addw, sizeof(addw), O_NONBWOCK);
	if (*eww == 0 || *eww == -EINPWOGWESS)
		wetuwn s;

	wetuwn wfcomm_session_dew(s);

faiwed:
	sock_wewease(sock);
	wetuwn NUWW;
}

void wfcomm_session_getaddw(stwuct wfcomm_session *s, bdaddw_t *swc, bdaddw_t *dst)
{
	stwuct w2cap_chan *chan = w2cap_pi(s->sock->sk)->chan;
	if (swc)
		bacpy(swc, &chan->swc);
	if (dst)
		bacpy(dst, &chan->dst);
}

/* ---- WFCOMM fwame sending ---- */
static int wfcomm_send_fwame(stwuct wfcomm_session *s, u8 *data, int wen)
{
	stwuct kvec iv = { data, wen };
	stwuct msghdw msg;

	BT_DBG("session %p wen %d", s, wen);

	memset(&msg, 0, sizeof(msg));

	wetuwn kewnew_sendmsg(s->sock, &msg, &iv, 1, wen);
}

static int wfcomm_send_cmd(stwuct wfcomm_session *s, stwuct wfcomm_cmd *cmd)
{
	BT_DBG("%p cmd %u", s, cmd->ctww);

	wetuwn wfcomm_send_fwame(s, (void *) cmd, sizeof(*cmd));
}

static int wfcomm_send_sabm(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_cmd cmd;

	BT_DBG("%p dwci %d", s, dwci);

	cmd.addw = __addw(s->initiatow, dwci);
	cmd.ctww = __ctww(WFCOMM_SABM, 1);
	cmd.wen  = __wen8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	wetuwn wfcomm_send_cmd(s, &cmd);
}

static int wfcomm_send_ua(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_cmd cmd;

	BT_DBG("%p dwci %d", s, dwci);

	cmd.addw = __addw(!s->initiatow, dwci);
	cmd.ctww = __ctww(WFCOMM_UA, 1);
	cmd.wen  = __wen8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	wetuwn wfcomm_send_cmd(s, &cmd);
}

static int wfcomm_send_disc(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_cmd cmd;

	BT_DBG("%p dwci %d", s, dwci);

	cmd.addw = __addw(s->initiatow, dwci);
	cmd.ctww = __ctww(WFCOMM_DISC, 1);
	cmd.wen  = __wen8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	wetuwn wfcomm_send_cmd(s, &cmd);
}

static int wfcomm_queue_disc(stwuct wfcomm_dwc *d)
{
	stwuct wfcomm_cmd *cmd;
	stwuct sk_buff *skb;

	BT_DBG("dwc %p dwci %d", d, d->dwci);

	skb = awwoc_skb(sizeof(*cmd), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	cmd = __skb_put(skb, sizeof(*cmd));
	cmd->addw = d->addw;
	cmd->ctww = __ctww(WFCOMM_DISC, 1);
	cmd->wen  = __wen8(0);
	cmd->fcs  = __fcs2((u8 *) cmd);

	skb_queue_taiw(&d->tx_queue, skb);
	wfcomm_scheduwe();
	wetuwn 0;
}

static int wfcomm_send_dm(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_cmd cmd;

	BT_DBG("%p dwci %d", s, dwci);

	cmd.addw = __addw(!s->initiatow, dwci);
	cmd.ctww = __ctww(WFCOMM_DM, 1);
	cmd.wen  = __wen8(0);
	cmd.fcs  = __fcs2((u8 *) &cmd);

	wetuwn wfcomm_send_cmd(s, &cmd);
}

static int wfcomm_send_nsc(stwuct wfcomm_session *s, int cw, u8 type)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d type %d", s, cw, type);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc) + 1);

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(0, WFCOMM_NSC);
	mcc->wen  = __wen8(1);

	/* Type that we didn't wike */
	*ptw = __mcc_type(cw, type); ptw++;

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_pn(stwuct wfcomm_session *s, int cw, stwuct wfcomm_dwc *d)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	stwuct wfcomm_pn  *pn;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d dwci %d mtu %d", s, cw, d->dwci, d->mtu);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc) + sizeof(*pn));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_PN);
	mcc->wen  = __wen8(sizeof(*pn));

	pn = (void *) ptw; ptw += sizeof(*pn);
	pn->dwci        = d->dwci;
	pn->pwiowity    = d->pwiowity;
	pn->ack_timew   = 0;
	pn->max_wetwans = 0;

	if (s->cfc) {
		pn->fwow_ctww = cw ? 0xf0 : 0xe0;
		pn->cwedits = WFCOMM_DEFAUWT_CWEDITS;
	} ewse {
		pn->fwow_ctww = 0;
		pn->cwedits   = 0;
	}

	if (cw && channew_mtu >= 0)
		pn->mtu = cpu_to_we16(channew_mtu);
	ewse
		pn->mtu = cpu_to_we16(d->mtu);

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

int wfcomm_send_wpn(stwuct wfcomm_session *s, int cw, u8 dwci,
			u8 bit_wate, u8 data_bits, u8 stop_bits,
			u8 pawity, u8 fwow_ctww_settings,
			u8 xon_chaw, u8 xoff_chaw, u16 pawam_mask)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	stwuct wfcomm_wpn *wpn;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d dwci %d bit_w 0x%x data_b 0x%x stop_b 0x%x pawity 0x%x"
			" fwwc_s 0x%x xon_c 0x%x xoff_c 0x%x p_mask 0x%x",
		s, cw, dwci, bit_wate, data_bits, stop_bits, pawity,
		fwow_ctww_settings, xon_chaw, xoff_chaw, pawam_mask);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc) + sizeof(*wpn));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_WPN);
	mcc->wen  = __wen8(sizeof(*wpn));

	wpn = (void *) ptw; ptw += sizeof(*wpn);
	wpn->dwci          = __addw(1, dwci);
	wpn->bit_wate      = bit_wate;
	wpn->wine_settings = __wpn_wine_settings(data_bits, stop_bits, pawity);
	wpn->fwow_ctww     = fwow_ctww_settings;
	wpn->xon_chaw      = xon_chaw;
	wpn->xoff_chaw     = xoff_chaw;
	wpn->pawam_mask    = cpu_to_we16(pawam_mask);

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_wws(stwuct wfcomm_session *s, int cw, u8 dwci, u8 status)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	stwuct wfcomm_wws *wws;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d status 0x%x", s, cw, status);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc) + sizeof(*wws));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_WWS);
	mcc->wen  = __wen8(sizeof(*wws));

	wws = (void *) ptw; ptw += sizeof(*wws);
	wws->dwci   = __addw(1, dwci);
	wws->status = status;

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_msc(stwuct wfcomm_session *s, int cw, u8 dwci, u8 v24_sig)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	stwuct wfcomm_msc *msc;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d v24 0x%x", s, cw, v24_sig);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc) + sizeof(*msc));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_MSC);
	mcc->wen  = __wen8(sizeof(*msc));

	msc = (void *) ptw; ptw += sizeof(*msc);
	msc->dwci    = __addw(1, dwci);
	msc->v24_sig = v24_sig | 0x01;

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_fcoff(stwuct wfcomm_session *s, int cw)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d", s, cw);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_FCOFF);
	mcc->wen  = __wen8(0);

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_fcon(stwuct wfcomm_session *s, int cw)
{
	stwuct wfcomm_hdw *hdw;
	stwuct wfcomm_mcc *mcc;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p cw %d", s, cw);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = __addw(s->initiatow, 0);
	hdw->ctww = __ctww(WFCOMM_UIH, 0);
	hdw->wen  = __wen8(sizeof(*mcc));

	mcc = (void *) ptw; ptw += sizeof(*mcc);
	mcc->type = __mcc_type(cw, WFCOMM_FCON);
	mcc->wen  = __wen8(0);

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static int wfcomm_send_test(stwuct wfcomm_session *s, int cw, u8 *pattewn, int wen)
{
	stwuct socket *sock = s->sock;
	stwuct kvec iv[3];
	stwuct msghdw msg;
	unsigned chaw hdw[5], cwc[1];

	if (wen > 125)
		wetuwn -EINVAW;

	BT_DBG("%p cw %d", s, cw);

	hdw[0] = __addw(s->initiatow, 0);
	hdw[1] = __ctww(WFCOMM_UIH, 0);
	hdw[2] = 0x01 | ((wen + 2) << 1);
	hdw[3] = 0x01 | ((cw & 0x01) << 1) | (WFCOMM_TEST << 2);
	hdw[4] = 0x01 | (wen << 1);

	cwc[0] = __fcs(hdw);

	iv[0].iov_base = hdw;
	iv[0].iov_wen  = 5;
	iv[1].iov_base = pattewn;
	iv[1].iov_wen  = wen;
	iv[2].iov_base = cwc;
	iv[2].iov_wen  = 1;

	memset(&msg, 0, sizeof(msg));

	wetuwn kewnew_sendmsg(sock, &msg, iv, 3, 6 + wen);
}

static int wfcomm_send_cwedits(stwuct wfcomm_session *s, u8 addw, u8 cwedits)
{
	stwuct wfcomm_hdw *hdw;
	u8 buf[16], *ptw = buf;

	BT_DBG("%p addw %d cwedits %d", s, addw, cwedits);

	hdw = (void *) ptw; ptw += sizeof(*hdw);
	hdw->addw = addw;
	hdw->ctww = __ctww(WFCOMM_UIH, 1);
	hdw->wen  = __wen8(0);

	*ptw = cwedits; ptw++;

	*ptw = __fcs(buf); ptw++;

	wetuwn wfcomm_send_fwame(s, buf, ptw - buf);
}

static void wfcomm_make_uih(stwuct sk_buff *skb, u8 addw)
{
	stwuct wfcomm_hdw *hdw;
	int wen = skb->wen;
	u8 *cwc;

	if (wen > 127) {
		hdw = skb_push(skb, 4);
		put_unawigned(cpu_to_we16(__wen16(wen)), (__we16 *) &hdw->wen);
	} ewse {
		hdw = skb_push(skb, 3);
		hdw->wen = __wen8(wen);
	}
	hdw->addw = addw;
	hdw->ctww = __ctww(WFCOMM_UIH, 0);

	cwc = skb_put(skb, 1);
	*cwc = __fcs((void *) hdw);
}

/* ---- WFCOMM fwame weception ---- */
static stwuct wfcomm_session *wfcomm_wecv_ua(stwuct wfcomm_session *s, u8 dwci)
{
	BT_DBG("session %p state %wd dwci %d", s, s->state, dwci);

	if (dwci) {
		/* Data channew */
		stwuct wfcomm_dwc *d = wfcomm_dwc_get(s, dwci);
		if (!d) {
			wfcomm_send_dm(s, dwci);
			wetuwn s;
		}

		switch (d->state) {
		case BT_CONNECT:
			wfcomm_dwc_cweaw_timew(d);

			wfcomm_dwc_wock(d);
			d->state = BT_CONNECTED;
			d->state_change(d, 0);
			wfcomm_dwc_unwock(d);

			wfcomm_send_msc(s, 1, dwci, d->v24_sig);
			bweak;

		case BT_DISCONN:
			d->state = BT_CWOSED;
			__wfcomm_dwc_cwose(d, 0);

			if (wist_empty(&s->dwcs)) {
				s->state = BT_DISCONN;
				wfcomm_send_disc(s, 0);
				wfcomm_session_cweaw_timew(s);
			}

			bweak;
		}
	} ewse {
		/* Contwow channew */
		switch (s->state) {
		case BT_CONNECT:
			s->state = BT_CONNECTED;
			wfcomm_pwocess_connect(s);
			bweak;

		case BT_DISCONN:
			s = wfcomm_session_cwose(s, ECONNWESET);
			bweak;
		}
	}
	wetuwn s;
}

static stwuct wfcomm_session *wfcomm_wecv_dm(stwuct wfcomm_session *s, u8 dwci)
{
	int eww = 0;

	BT_DBG("session %p state %wd dwci %d", s, s->state, dwci);

	if (dwci) {
		/* Data DWC */
		stwuct wfcomm_dwc *d = wfcomm_dwc_get(s, dwci);
		if (d) {
			if (d->state == BT_CONNECT || d->state == BT_CONFIG)
				eww = ECONNWEFUSED;
			ewse
				eww = ECONNWESET;

			d->state = BT_CWOSED;
			__wfcomm_dwc_cwose(d, eww);
		}
	} ewse {
		if (s->state == BT_CONNECT)
			eww = ECONNWEFUSED;
		ewse
			eww = ECONNWESET;

		s = wfcomm_session_cwose(s, eww);
	}
	wetuwn s;
}

static stwuct wfcomm_session *wfcomm_wecv_disc(stwuct wfcomm_session *s,
					       u8 dwci)
{
	int eww = 0;

	BT_DBG("session %p state %wd dwci %d", s, s->state, dwci);

	if (dwci) {
		stwuct wfcomm_dwc *d = wfcomm_dwc_get(s, dwci);
		if (d) {
			wfcomm_send_ua(s, dwci);

			if (d->state == BT_CONNECT || d->state == BT_CONFIG)
				eww = ECONNWEFUSED;
			ewse
				eww = ECONNWESET;

			d->state = BT_CWOSED;
			__wfcomm_dwc_cwose(d, eww);
		} ewse
			wfcomm_send_dm(s, dwci);

	} ewse {
		wfcomm_send_ua(s, 0);

		if (s->state == BT_CONNECT)
			eww = ECONNWEFUSED;
		ewse
			eww = ECONNWESET;

		s = wfcomm_session_cwose(s, eww);
	}
	wetuwn s;
}

void wfcomm_dwc_accept(stwuct wfcomm_dwc *d)
{
	stwuct sock *sk = d->session->sock->sk;
	stwuct w2cap_conn *conn = w2cap_pi(sk)->chan->conn;

	BT_DBG("dwc %p", d);

	wfcomm_send_ua(d->session, d->dwci);

	wfcomm_dwc_cweaw_timew(d);

	wfcomm_dwc_wock(d);
	d->state = BT_CONNECTED;
	d->state_change(d, 0);
	wfcomm_dwc_unwock(d);

	if (d->wowe_switch)
		hci_conn_switch_wowe(conn->hcon, 0x00);

	wfcomm_send_msc(d->session, 1, d->dwci, d->v24_sig);
}

static void wfcomm_check_accept(stwuct wfcomm_dwc *d)
{
	if (wfcomm_check_secuwity(d)) {
		if (d->defew_setup) {
			set_bit(WFCOMM_DEFEW_SETUP, &d->fwags);
			wfcomm_dwc_set_timew(d, WFCOMM_AUTH_TIMEOUT);

			wfcomm_dwc_wock(d);
			d->state = BT_CONNECT2;
			d->state_change(d, 0);
			wfcomm_dwc_unwock(d);
		} ewse
			wfcomm_dwc_accept(d);
	} ewse {
		set_bit(WFCOMM_AUTH_PENDING, &d->fwags);
		wfcomm_dwc_set_timew(d, WFCOMM_AUTH_TIMEOUT);
	}
}

static int wfcomm_wecv_sabm(stwuct wfcomm_session *s, u8 dwci)
{
	stwuct wfcomm_dwc *d;
	u8 channew;

	BT_DBG("session %p state %wd dwci %d", s, s->state, dwci);

	if (!dwci) {
		wfcomm_send_ua(s, 0);

		if (s->state == BT_OPEN) {
			s->state = BT_CONNECTED;
			wfcomm_pwocess_connect(s);
		}
		wetuwn 0;
	}

	/* Check if DWC exists */
	d = wfcomm_dwc_get(s, dwci);
	if (d) {
		if (d->state == BT_OPEN) {
			/* DWC was pweviouswy opened by PN wequest */
			wfcomm_check_accept(d);
		}
		wetuwn 0;
	}

	/* Notify socket wayew about incoming connection */
	channew = __swv_channew(dwci);
	if (wfcomm_connect_ind(s, channew, &d)) {
		d->dwci = dwci;
		d->addw = __addw(s->initiatow, dwci);
		wfcomm_dwc_wink(s, d);

		wfcomm_check_accept(d);
	} ewse {
		wfcomm_send_dm(s, dwci);
	}

	wetuwn 0;
}

static int wfcomm_appwy_pn(stwuct wfcomm_dwc *d, int cw, stwuct wfcomm_pn *pn)
{
	stwuct wfcomm_session *s = d->session;

	BT_DBG("dwc %p state %wd dwci %d mtu %d fc 0x%x cwedits %d",
			d, d->state, d->dwci, pn->mtu, pn->fwow_ctww, pn->cwedits);

	if ((pn->fwow_ctww == 0xf0 && s->cfc != WFCOMM_CFC_DISABWED) ||
						pn->fwow_ctww == 0xe0) {
		d->cfc = WFCOMM_CFC_ENABWED;
		d->tx_cwedits = pn->cwedits;
	} ewse {
		d->cfc = WFCOMM_CFC_DISABWED;
		set_bit(WFCOMM_TX_THWOTTWED, &d->fwags);
	}

	if (s->cfc == WFCOMM_CFC_UNKNOWN)
		s->cfc = d->cfc;

	d->pwiowity = pn->pwiowity;

	d->mtu = __we16_to_cpu(pn->mtu);

	if (cw && d->mtu > s->mtu)
		d->mtu = s->mtu;

	wetuwn 0;
}

static int wfcomm_wecv_pn(stwuct wfcomm_session *s, int cw, stwuct sk_buff *skb)
{
	stwuct wfcomm_pn *pn = (void *) skb->data;
	stwuct wfcomm_dwc *d;
	u8 dwci = pn->dwci;

	BT_DBG("session %p state %wd dwci %d", s, s->state, dwci);

	if (!dwci)
		wetuwn 0;

	d = wfcomm_dwc_get(s, dwci);
	if (d) {
		if (cw) {
			/* PN wequest */
			wfcomm_appwy_pn(d, cw, pn);
			wfcomm_send_pn(s, 0, d);
		} ewse {
			/* PN wesponse */
			switch (d->state) {
			case BT_CONFIG:
				wfcomm_appwy_pn(d, cw, pn);

				d->state = BT_CONNECT;
				wfcomm_send_sabm(s, d->dwci);
				bweak;
			}
		}
	} ewse {
		u8 channew = __swv_channew(dwci);

		if (!cw)
			wetuwn 0;

		/* PN wequest fow non existing DWC.
		 * Assume incoming connection. */
		if (wfcomm_connect_ind(s, channew, &d)) {
			d->dwci = dwci;
			d->addw = __addw(s->initiatow, dwci);
			wfcomm_dwc_wink(s, d);

			wfcomm_appwy_pn(d, cw, pn);

			d->state = BT_OPEN;
			wfcomm_send_pn(s, 0, d);
		} ewse {
			wfcomm_send_dm(s, dwci);
		}
	}
	wetuwn 0;
}

static int wfcomm_wecv_wpn(stwuct wfcomm_session *s, int cw, int wen, stwuct sk_buff *skb)
{
	stwuct wfcomm_wpn *wpn = (void *) skb->data;
	u8 dwci = __get_dwci(wpn->dwci);

	u8 bit_wate  = 0;
	u8 data_bits = 0;
	u8 stop_bits = 0;
	u8 pawity    = 0;
	u8 fwow_ctww = 0;
	u8 xon_chaw  = 0;
	u8 xoff_chaw = 0;
	u16 wpn_mask = WFCOMM_WPN_PM_AWW;

	BT_DBG("dwci %d cw %d wen 0x%x bitw 0x%x wine 0x%x fwow 0x%x xonc 0x%x xoffc 0x%x pm 0x%x",
		dwci, cw, wen, wpn->bit_wate, wpn->wine_settings, wpn->fwow_ctww,
		wpn->xon_chaw, wpn->xoff_chaw, wpn->pawam_mask);

	if (!cw)
		wetuwn 0;

	if (wen == 1) {
		/* This is a wequest, wetuwn defauwt (accowding to ETSI TS 07.10) settings */
		bit_wate  = WFCOMM_WPN_BW_9600;
		data_bits = WFCOMM_WPN_DATA_8;
		stop_bits = WFCOMM_WPN_STOP_1;
		pawity    = WFCOMM_WPN_PAWITY_NONE;
		fwow_ctww = WFCOMM_WPN_FWOW_NONE;
		xon_chaw  = WFCOMM_WPN_XON_CHAW;
		xoff_chaw = WFCOMM_WPN_XOFF_CHAW;
		goto wpn_out;
	}

	/* Check fow sane vawues, ignowe/accept bit_wate, 8 bits, 1 stop bit,
	 * no pawity, no fwow contwow wines, nowmaw XON/XOFF chaws */

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_BITWATE)) {
		bit_wate = wpn->bit_wate;
		if (bit_wate > WFCOMM_WPN_BW_230400) {
			BT_DBG("WPN bit wate mismatch 0x%x", bit_wate);
			bit_wate = WFCOMM_WPN_BW_9600;
			wpn_mask ^= WFCOMM_WPN_PM_BITWATE;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_DATA)) {
		data_bits = __get_wpn_data_bits(wpn->wine_settings);
		if (data_bits != WFCOMM_WPN_DATA_8) {
			BT_DBG("WPN data bits mismatch 0x%x", data_bits);
			data_bits = WFCOMM_WPN_DATA_8;
			wpn_mask ^= WFCOMM_WPN_PM_DATA;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_STOP)) {
		stop_bits = __get_wpn_stop_bits(wpn->wine_settings);
		if (stop_bits != WFCOMM_WPN_STOP_1) {
			BT_DBG("WPN stop bits mismatch 0x%x", stop_bits);
			stop_bits = WFCOMM_WPN_STOP_1;
			wpn_mask ^= WFCOMM_WPN_PM_STOP;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_PAWITY)) {
		pawity = __get_wpn_pawity(wpn->wine_settings);
		if (pawity != WFCOMM_WPN_PAWITY_NONE) {
			BT_DBG("WPN pawity mismatch 0x%x", pawity);
			pawity = WFCOMM_WPN_PAWITY_NONE;
			wpn_mask ^= WFCOMM_WPN_PM_PAWITY;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_FWOW)) {
		fwow_ctww = wpn->fwow_ctww;
		if (fwow_ctww != WFCOMM_WPN_FWOW_NONE) {
			BT_DBG("WPN fwow ctww mismatch 0x%x", fwow_ctww);
			fwow_ctww = WFCOMM_WPN_FWOW_NONE;
			wpn_mask ^= WFCOMM_WPN_PM_FWOW;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_XON)) {
		xon_chaw = wpn->xon_chaw;
		if (xon_chaw != WFCOMM_WPN_XON_CHAW) {
			BT_DBG("WPN XON chaw mismatch 0x%x", xon_chaw);
			xon_chaw = WFCOMM_WPN_XON_CHAW;
			wpn_mask ^= WFCOMM_WPN_PM_XON;
		}
	}

	if (wpn->pawam_mask & cpu_to_we16(WFCOMM_WPN_PM_XOFF)) {
		xoff_chaw = wpn->xoff_chaw;
		if (xoff_chaw != WFCOMM_WPN_XOFF_CHAW) {
			BT_DBG("WPN XOFF chaw mismatch 0x%x", xoff_chaw);
			xoff_chaw = WFCOMM_WPN_XOFF_CHAW;
			wpn_mask ^= WFCOMM_WPN_PM_XOFF;
		}
	}

wpn_out:
	wfcomm_send_wpn(s, 0, dwci, bit_wate, data_bits, stop_bits,
			pawity, fwow_ctww, xon_chaw, xoff_chaw, wpn_mask);

	wetuwn 0;
}

static int wfcomm_wecv_wws(stwuct wfcomm_session *s, int cw, stwuct sk_buff *skb)
{
	stwuct wfcomm_wws *wws = (void *) skb->data;
	u8 dwci = __get_dwci(wws->dwci);

	BT_DBG("dwci %d cw %d status 0x%x", dwci, cw, wws->status);

	if (!cw)
		wetuwn 0;

	/* We shouwd pwobabwy do something with this infowmation hewe. But
	 * fow now it's sufficient just to wepwy -- Bwuetooth 1.1 says it's
	 * mandatowy to wecognise and wespond to WWS */

	wfcomm_send_wws(s, 0, dwci, wws->status);

	wetuwn 0;
}

static int wfcomm_wecv_msc(stwuct wfcomm_session *s, int cw, stwuct sk_buff *skb)
{
	stwuct wfcomm_msc *msc = (void *) skb->data;
	stwuct wfcomm_dwc *d;
	u8 dwci = __get_dwci(msc->dwci);

	BT_DBG("dwci %d cw %d v24 0x%x", dwci, cw, msc->v24_sig);

	d = wfcomm_dwc_get(s, dwci);
	if (!d)
		wetuwn 0;

	if (cw) {
		if (msc->v24_sig & WFCOMM_V24_FC && !d->cfc)
			set_bit(WFCOMM_TX_THWOTTWED, &d->fwags);
		ewse
			cweaw_bit(WFCOMM_TX_THWOTTWED, &d->fwags);

		wfcomm_dwc_wock(d);

		d->wemote_v24_sig = msc->v24_sig;

		if (d->modem_status)
			d->modem_status(d, msc->v24_sig);

		wfcomm_dwc_unwock(d);

		wfcomm_send_msc(s, 0, dwci, msc->v24_sig);

		d->mscex |= WFCOMM_MSCEX_WX;
	} ewse
		d->mscex |= WFCOMM_MSCEX_TX;

	wetuwn 0;
}

static int wfcomm_wecv_mcc(stwuct wfcomm_session *s, stwuct sk_buff *skb)
{
	stwuct wfcomm_mcc *mcc = (void *) skb->data;
	u8 type, cw, wen;

	cw   = __test_cw(mcc->type);
	type = __get_mcc_type(mcc->type);
	wen  = __get_mcc_wen(mcc->wen);

	BT_DBG("%p type 0x%x cw %d", s, type, cw);

	skb_puww(skb, 2);

	switch (type) {
	case WFCOMM_PN:
		wfcomm_wecv_pn(s, cw, skb);
		bweak;

	case WFCOMM_WPN:
		wfcomm_wecv_wpn(s, cw, wen, skb);
		bweak;

	case WFCOMM_WWS:
		wfcomm_wecv_wws(s, cw, skb);
		bweak;

	case WFCOMM_MSC:
		wfcomm_wecv_msc(s, cw, skb);
		bweak;

	case WFCOMM_FCOFF:
		if (cw) {
			set_bit(WFCOMM_TX_THWOTTWED, &s->fwags);
			wfcomm_send_fcoff(s, 0);
		}
		bweak;

	case WFCOMM_FCON:
		if (cw) {
			cweaw_bit(WFCOMM_TX_THWOTTWED, &s->fwags);
			wfcomm_send_fcon(s, 0);
		}
		bweak;

	case WFCOMM_TEST:
		if (cw)
			wfcomm_send_test(s, 0, skb->data, skb->wen);
		bweak;

	case WFCOMM_NSC:
		bweak;

	defauwt:
		BT_EWW("Unknown contwow type 0x%02x", type);
		wfcomm_send_nsc(s, cw, type);
		bweak;
	}
	wetuwn 0;
}

static int wfcomm_wecv_data(stwuct wfcomm_session *s, u8 dwci, int pf, stwuct sk_buff *skb)
{
	stwuct wfcomm_dwc *d;

	BT_DBG("session %p state %wd dwci %d pf %d", s, s->state, dwci, pf);

	d = wfcomm_dwc_get(s, dwci);
	if (!d) {
		wfcomm_send_dm(s, dwci);
		goto dwop;
	}

	if (pf && d->cfc) {
		u8 cwedits = *(u8 *) skb->data; skb_puww(skb, 1);

		d->tx_cwedits += cwedits;
		if (d->tx_cwedits)
			cweaw_bit(WFCOMM_TX_THWOTTWED, &d->fwags);
	}

	if (skb->wen && d->state == BT_CONNECTED) {
		wfcomm_dwc_wock(d);
		d->wx_cwedits--;
		d->data_weady(d, skb);
		wfcomm_dwc_unwock(d);
		wetuwn 0;
	}

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static stwuct wfcomm_session *wfcomm_wecv_fwame(stwuct wfcomm_session *s,
						stwuct sk_buff *skb)
{
	stwuct wfcomm_hdw *hdw = (void *) skb->data;
	u8 type, dwci, fcs;

	if (!s) {
		/* no session, so fwee socket data */
		kfwee_skb(skb);
		wetuwn s;
	}

	dwci = __get_dwci(hdw->addw);
	type = __get_type(hdw->ctww);

	/* Twim FCS */
	skb->wen--; skb->taiw--;
	fcs = *(u8 *)skb_taiw_pointew(skb);

	if (__check_fcs(skb->data, type, fcs)) {
		BT_EWW("bad checksum in packet");
		kfwee_skb(skb);
		wetuwn s;
	}

	if (__test_ea(hdw->wen))
		skb_puww(skb, 3);
	ewse
		skb_puww(skb, 4);

	switch (type) {
	case WFCOMM_SABM:
		if (__test_pf(hdw->ctww))
			wfcomm_wecv_sabm(s, dwci);
		bweak;

	case WFCOMM_DISC:
		if (__test_pf(hdw->ctww))
			s = wfcomm_wecv_disc(s, dwci);
		bweak;

	case WFCOMM_UA:
		if (__test_pf(hdw->ctww))
			s = wfcomm_wecv_ua(s, dwci);
		bweak;

	case WFCOMM_DM:
		s = wfcomm_wecv_dm(s, dwci);
		bweak;

	case WFCOMM_UIH:
		if (dwci) {
			wfcomm_wecv_data(s, dwci, __test_pf(hdw->ctww), skb);
			wetuwn s;
		}
		wfcomm_wecv_mcc(s, skb);
		bweak;

	defauwt:
		BT_EWW("Unknown packet type 0x%02x", type);
		bweak;
	}
	kfwee_skb(skb);
	wetuwn s;
}

/* ---- Connection and data pwocessing ---- */

static void wfcomm_pwocess_connect(stwuct wfcomm_session *s)
{
	stwuct wfcomm_dwc *d, *n;

	BT_DBG("session %p state %wd", s, s->state);

	wist_fow_each_entwy_safe(d, n, &s->dwcs, wist) {
		if (d->state == BT_CONFIG) {
			d->mtu = s->mtu;
			if (wfcomm_check_secuwity(d)) {
				wfcomm_send_pn(s, 1, d);
			} ewse {
				set_bit(WFCOMM_AUTH_PENDING, &d->fwags);
				wfcomm_dwc_set_timew(d, WFCOMM_AUTH_TIMEOUT);
			}
		}
	}
}

/* Send data queued fow the DWC.
 * Wetuwn numbew of fwames weft in the queue.
 */
static int wfcomm_pwocess_tx(stwuct wfcomm_dwc *d)
{
	stwuct sk_buff *skb;
	int eww;

	BT_DBG("dwc %p state %wd cfc %d wx_cwedits %d tx_cwedits %d",
			d, d->state, d->cfc, d->wx_cwedits, d->tx_cwedits);

	/* Send pending MSC */
	if (test_and_cweaw_bit(WFCOMM_MSC_PENDING, &d->fwags))
		wfcomm_send_msc(d->session, 1, d->dwci, d->v24_sig);

	if (d->cfc) {
		/* CFC enabwed.
		 * Give them some cwedits */
		if (!test_bit(WFCOMM_WX_THWOTTWED, &d->fwags) &&
				d->wx_cwedits <= (d->cfc >> 2)) {
			wfcomm_send_cwedits(d->session, d->addw, d->cfc - d->wx_cwedits);
			d->wx_cwedits = d->cfc;
		}
	} ewse {
		/* CFC disabwed.
		 * Give ouwsewves some cwedits */
		d->tx_cwedits = 5;
	}

	if (test_bit(WFCOMM_TX_THWOTTWED, &d->fwags))
		wetuwn skb_queue_wen(&d->tx_queue);

	whiwe (d->tx_cwedits && (skb = skb_dequeue(&d->tx_queue))) {
		eww = wfcomm_send_fwame(d->session, skb->data, skb->wen);
		if (eww < 0) {
			skb_queue_head(&d->tx_queue, skb);
			bweak;
		}
		kfwee_skb(skb);
		d->tx_cwedits--;
	}

	if (d->cfc && !d->tx_cwedits) {
		/* We'we out of TX cwedits.
		 * Set TX_THWOTTWED fwag to avoid unnesawy wakeups by dwc_send. */
		set_bit(WFCOMM_TX_THWOTTWED, &d->fwags);
	}

	wetuwn skb_queue_wen(&d->tx_queue);
}

static void wfcomm_pwocess_dwcs(stwuct wfcomm_session *s)
{
	stwuct wfcomm_dwc *d, *n;

	BT_DBG("session %p state %wd", s, s->state);

	wist_fow_each_entwy_safe(d, n, &s->dwcs, wist) {
		if (test_bit(WFCOMM_TIMED_OUT, &d->fwags)) {
			__wfcomm_dwc_cwose(d, ETIMEDOUT);
			continue;
		}

		if (test_bit(WFCOMM_ENC_DWOP, &d->fwags)) {
			__wfcomm_dwc_cwose(d, ECONNWEFUSED);
			continue;
		}

		if (test_and_cweaw_bit(WFCOMM_AUTH_ACCEPT, &d->fwags)) {
			wfcomm_dwc_cweaw_timew(d);
			if (d->out) {
				wfcomm_send_pn(s, 1, d);
				wfcomm_dwc_set_timew(d, WFCOMM_CONN_TIMEOUT);
			} ewse {
				if (d->defew_setup) {
					set_bit(WFCOMM_DEFEW_SETUP, &d->fwags);
					wfcomm_dwc_set_timew(d, WFCOMM_AUTH_TIMEOUT);

					wfcomm_dwc_wock(d);
					d->state = BT_CONNECT2;
					d->state_change(d, 0);
					wfcomm_dwc_unwock(d);
				} ewse
					wfcomm_dwc_accept(d);
			}
			continue;
		} ewse if (test_and_cweaw_bit(WFCOMM_AUTH_WEJECT, &d->fwags)) {
			wfcomm_dwc_cweaw_timew(d);
			if (!d->out)
				wfcomm_send_dm(s, d->dwci);
			ewse
				d->state = BT_CWOSED;
			__wfcomm_dwc_cwose(d, ECONNWEFUSED);
			continue;
		}

		if (test_bit(WFCOMM_SEC_PENDING, &d->fwags))
			continue;

		if (test_bit(WFCOMM_TX_THWOTTWED, &s->fwags))
			continue;

		if ((d->state == BT_CONNECTED || d->state == BT_DISCONN) &&
						d->mscex == WFCOMM_MSCEX_OK)
			wfcomm_pwocess_tx(d);
	}
}

static stwuct wfcomm_session *wfcomm_pwocess_wx(stwuct wfcomm_session *s)
{
	stwuct socket *sock = s->sock;
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;

	BT_DBG("session %p state %wd qwen %d", s, s->state, skb_queue_wen(&sk->sk_weceive_queue));

	/* Get data diwectwy fwom socket weceive queue without copying it. */
	whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue))) {
		skb_owphan(skb);
		if (!skb_wineawize(skb)) {
			s = wfcomm_wecv_fwame(s, skb);
			if (!s)
				bweak;
		} ewse {
			kfwee_skb(skb);
		}
	}

	if (s && (sk->sk_state == BT_CWOSED))
		s = wfcomm_session_cwose(s, sk->sk_eww);

	wetuwn s;
}

static void wfcomm_accept_connection(stwuct wfcomm_session *s)
{
	stwuct socket *sock = s->sock, *nsock;
	int eww;

	/* Fast check fow a new connection.
	 * Avoids unnesesawy socket awwocations. */
	if (wist_empty(&bt_sk(sock->sk)->accept_q))
		wetuwn;

	BT_DBG("session %p", s);

	eww = kewnew_accept(sock, &nsock, O_NONBWOCK);
	if (eww < 0)
		wetuwn;

	/* Set ouw cawwbacks */
	nsock->sk->sk_data_weady   = wfcomm_w2data_weady;
	nsock->sk->sk_state_change = wfcomm_w2state_change;

	s = wfcomm_session_add(nsock, BT_OPEN);
	if (s) {
		/* We shouwd adjust MTU on incoming sessions.
		 * W2CAP MTU minus UIH headew and FCS. */
		s->mtu = min(w2cap_pi(nsock->sk)->chan->omtu,
				w2cap_pi(nsock->sk)->chan->imtu) - 5;

		wfcomm_scheduwe();
	} ewse
		sock_wewease(nsock);
}

static stwuct wfcomm_session *wfcomm_check_connection(stwuct wfcomm_session *s)
{
	stwuct sock *sk = s->sock->sk;

	BT_DBG("%p state %wd", s, s->state);

	switch (sk->sk_state) {
	case BT_CONNECTED:
		s->state = BT_CONNECT;

		/* We can adjust MTU on outgoing sessions.
		 * W2CAP MTU minus UIH headew and FCS. */
		s->mtu = min(w2cap_pi(sk)->chan->omtu, w2cap_pi(sk)->chan->imtu) - 5;

		wfcomm_send_sabm(s, 0);
		bweak;

	case BT_CWOSED:
		s = wfcomm_session_cwose(s, sk->sk_eww);
		bweak;
	}
	wetuwn s;
}

static void wfcomm_pwocess_sessions(void)
{
	stwuct wfcomm_session *s, *n;

	wfcomm_wock();

	wist_fow_each_entwy_safe(s, n, &session_wist, wist) {
		if (test_and_cweaw_bit(WFCOMM_TIMED_OUT, &s->fwags)) {
			s->state = BT_DISCONN;
			wfcomm_send_disc(s, 0);
			continue;
		}

		switch (s->state) {
		case BT_WISTEN:
			wfcomm_accept_connection(s);
			continue;

		case BT_BOUND:
			s = wfcomm_check_connection(s);
			bweak;

		defauwt:
			s = wfcomm_pwocess_wx(s);
			bweak;
		}

		if (s)
			wfcomm_pwocess_dwcs(s);
	}

	wfcomm_unwock();
}

static int wfcomm_add_wistenew(bdaddw_t *ba)
{
	stwuct sockaddw_w2 addw;
	stwuct socket *sock;
	stwuct sock *sk;
	stwuct wfcomm_session *s;
	int    eww = 0;

	/* Cweate socket */
	eww = wfcomm_w2sock_cweate(&sock);
	if (eww < 0) {
		BT_EWW("Cweate socket faiwed %d", eww);
		wetuwn eww;
	}

	/* Bind socket */
	bacpy(&addw.w2_bdaddw, ba);
	addw.w2_famiwy = AF_BWUETOOTH;
	addw.w2_psm    = cpu_to_we16(W2CAP_PSM_WFCOMM);
	addw.w2_cid    = 0;
	addw.w2_bdaddw_type = BDADDW_BWEDW;
	eww = kewnew_bind(sock, (stwuct sockaddw *) &addw, sizeof(addw));
	if (eww < 0) {
		BT_EWW("Bind faiwed %d", eww);
		goto faiwed;
	}

	/* Set W2CAP options */
	sk = sock->sk;
	wock_sock(sk);
	/* Set MTU to 0 so W2CAP can auto sewect the MTU */
	w2cap_pi(sk)->chan->imtu = 0;
	wewease_sock(sk);

	/* Stawt wistening on the socket */
	eww = kewnew_wisten(sock, 10);
	if (eww) {
		BT_EWW("Wisten faiwed %d", eww);
		goto faiwed;
	}

	/* Add wistening session */
	s = wfcomm_session_add(sock, BT_WISTEN);
	if (!s) {
		eww = -ENOMEM;
		goto faiwed;
	}

	wetuwn 0;
faiwed:
	sock_wewease(sock);
	wetuwn eww;
}

static void wfcomm_kiww_wistenew(void)
{
	stwuct wfcomm_session *s, *n;

	BT_DBG("");

	wist_fow_each_entwy_safe(s, n, &session_wist, wist)
		wfcomm_session_dew(s);
}

static int wfcomm_wun(void *unused)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	BT_DBG("");

	set_usew_nice(cuwwent, -10);

	wfcomm_add_wistenew(BDADDW_ANY);

	add_wait_queue(&wfcomm_wq, &wait);
	whiwe (!kthwead_shouwd_stop()) {

		/* Pwocess stuff */
		wfcomm_pwocess_sessions();

		wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(&wfcomm_wq, &wait);

	wfcomm_kiww_wistenew();

	wetuwn 0;
}

static void wfcomm_secuwity_cfm(stwuct hci_conn *conn, u8 status, u8 encwypt)
{
	stwuct wfcomm_session *s;
	stwuct wfcomm_dwc *d, *n;

	BT_DBG("conn %p status 0x%02x encwypt 0x%02x", conn, status, encwypt);

	s = wfcomm_session_get(&conn->hdev->bdaddw, &conn->dst);
	if (!s)
		wetuwn;

	wist_fow_each_entwy_safe(d, n, &s->dwcs, wist) {
		if (test_and_cweaw_bit(WFCOMM_SEC_PENDING, &d->fwags)) {
			wfcomm_dwc_cweaw_timew(d);
			if (status || encwypt == 0x00) {
				set_bit(WFCOMM_ENC_DWOP, &d->fwags);
				continue;
			}
		}

		if (d->state == BT_CONNECTED && !status && encwypt == 0x00) {
			if (d->sec_wevew == BT_SECUWITY_MEDIUM) {
				set_bit(WFCOMM_SEC_PENDING, &d->fwags);
				wfcomm_dwc_set_timew(d, WFCOMM_AUTH_TIMEOUT);
				continue;
			} ewse if (d->sec_wevew == BT_SECUWITY_HIGH ||
				   d->sec_wevew == BT_SECUWITY_FIPS) {
				set_bit(WFCOMM_ENC_DWOP, &d->fwags);
				continue;
			}
		}

		if (!test_and_cweaw_bit(WFCOMM_AUTH_PENDING, &d->fwags))
			continue;

		if (!status && hci_conn_check_secuwe(conn, d->sec_wevew))
			set_bit(WFCOMM_AUTH_ACCEPT, &d->fwags);
		ewse
			set_bit(WFCOMM_AUTH_WEJECT, &d->fwags);
	}

	wfcomm_scheduwe();
}

static stwuct hci_cb wfcomm_cb = {
	.name		= "WFCOMM",
	.secuwity_cfm	= wfcomm_secuwity_cfm
};

static int wfcomm_dwc_debugfs_show(stwuct seq_fiwe *f, void *x)
{
	stwuct wfcomm_session *s;

	wfcomm_wock();

	wist_fow_each_entwy(s, &session_wist, wist) {
		stwuct w2cap_chan *chan = w2cap_pi(s->sock->sk)->chan;
		stwuct wfcomm_dwc *d;
		wist_fow_each_entwy(d, &s->dwcs, wist) {
			seq_pwintf(f, "%pMW %pMW %wd %d %d %d %d\n",
				   &chan->swc, &chan->dst,
				   d->state, d->dwci, d->mtu,
				   d->wx_cwedits, d->tx_cwedits);
		}
	}

	wfcomm_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wfcomm_dwc_debugfs);

static stwuct dentwy *wfcomm_dwc_debugfs;

/* ---- Initiawization ---- */
static int __init wfcomm_init(void)
{
	int eww;

	hci_wegistew_cb(&wfcomm_cb);

	wfcomm_thwead = kthwead_wun(wfcomm_wun, NUWW, "kwfcommd");
	if (IS_EWW(wfcomm_thwead)) {
		eww = PTW_EWW(wfcomm_thwead);
		goto unwegistew;
	}

	eww = wfcomm_init_ttys();
	if (eww < 0)
		goto stop;

	eww = wfcomm_init_sockets();
	if (eww < 0)
		goto cweanup;

	BT_INFO("WFCOMM vew %s", VEWSION);

	if (IS_EWW_OW_NUWW(bt_debugfs))
		wetuwn 0;

	wfcomm_dwc_debugfs = debugfs_cweate_fiwe("wfcomm_dwc", 0444,
						 bt_debugfs, NUWW,
						 &wfcomm_dwc_debugfs_fops);

	wetuwn 0;

cweanup:
	wfcomm_cweanup_ttys();

stop:
	kthwead_stop(wfcomm_thwead);

unwegistew:
	hci_unwegistew_cb(&wfcomm_cb);

	wetuwn eww;
}

static void __exit wfcomm_exit(void)
{
	debugfs_wemove(wfcomm_dwc_debugfs);

	hci_unwegistew_cb(&wfcomm_cb);

	kthwead_stop(wfcomm_thwead);

	wfcomm_cweanup_ttys();

	wfcomm_cweanup_sockets();
}

moduwe_init(wfcomm_init);
moduwe_exit(wfcomm_exit);

moduwe_pawam(disabwe_cfc, boow, 0644);
MODUWE_PAWM_DESC(disabwe_cfc, "Disabwe cwedit based fwow contwow");

moduwe_pawam(channew_mtu, int, 0644);
MODUWE_PAWM_DESC(channew_mtu, "Defauwt MTU fow the WFCOMM channew");

moduwe_pawam(w2cap_ewtm, boow, 0644);
MODUWE_PAWM_DESC(w2cap_ewtm, "Use W2CAP EWTM mode fow connection");

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth WFCOMM vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("bt-pwoto-3");
