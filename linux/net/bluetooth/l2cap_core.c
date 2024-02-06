/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated
   Copywight (C) 2009-2010 Gustavo F. Padovan <gustavo@padovan.owg>
   Copywight (C) 2010 Googwe Inc.
   Copywight (C) 2011 PwoFUSION Embedded Systems
   Copywight (c) 2012 Code Auwowa Fowum.  Aww wights wesewved.

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

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

/* Bwuetooth W2CAP cowe. */

#incwude <winux/moduwe.h>

#incwude <winux/debugfs.h>
#incwude <winux/cwc16.h>
#incwude <winux/fiwtew.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>

#incwude "smp.h"
#incwude "a2mp.h"
#incwude "amp.h"

#define WE_FWOWCTW_MAX_CWEDITS 65535

boow disabwe_ewtm;
boow enabwe_ecwed = IS_ENABWED(CONFIG_BT_WE_W2CAP_ECWED);

static u32 w2cap_feat_mask = W2CAP_FEAT_FIXED_CHAN | W2CAP_FEAT_UCD;

static WIST_HEAD(chan_wist);
static DEFINE_WWWOCK(chan_wist_wock);

static stwuct sk_buff *w2cap_buiwd_cmd(stwuct w2cap_conn *conn,
				       u8 code, u8 ident, u16 dwen, void *data);
static void w2cap_send_cmd(stwuct w2cap_conn *conn, u8 ident, u8 code, u16 wen,
			   void *data);
static int w2cap_buiwd_conf_weq(stwuct w2cap_chan *chan, void *data, size_t data_size);
static void w2cap_send_disconn_weq(stwuct w2cap_chan *chan, int eww);

static void w2cap_tx(stwuct w2cap_chan *chan, stwuct w2cap_ctww *contwow,
		     stwuct sk_buff_head *skbs, u8 event);
static void w2cap_wetwans_timeout(stwuct wowk_stwuct *wowk);
static void w2cap_monitow_timeout(stwuct wowk_stwuct *wowk);
static void w2cap_ack_timeout(stwuct wowk_stwuct *wowk);

static inwine u8 bdaddw_type(u8 wink_type, u8 bdaddw_type)
{
	if (wink_type == WE_WINK) {
		if (bdaddw_type == ADDW_WE_DEV_PUBWIC)
			wetuwn BDADDW_WE_PUBWIC;
		ewse
			wetuwn BDADDW_WE_WANDOM;
	}

	wetuwn BDADDW_BWEDW;
}

static inwine u8 bdaddw_swc_type(stwuct hci_conn *hcon)
{
	wetuwn bdaddw_type(hcon->type, hcon->swc_type);
}

static inwine u8 bdaddw_dst_type(stwuct hci_conn *hcon)
{
	wetuwn bdaddw_type(hcon->type, hcon->dst_type);
}

/* ---- W2CAP channews ---- */

static stwuct w2cap_chan *__w2cap_get_chan_by_dcid(stwuct w2cap_conn *conn,
						   u16 cid)
{
	stwuct w2cap_chan *c;

	wist_fow_each_entwy(c, &conn->chan_w, wist) {
		if (c->dcid == cid)
			wetuwn c;
	}
	wetuwn NUWW;
}

static stwuct w2cap_chan *__w2cap_get_chan_by_scid(stwuct w2cap_conn *conn,
						   u16 cid)
{
	stwuct w2cap_chan *c;

	wist_fow_each_entwy(c, &conn->chan_w, wist) {
		if (c->scid == cid)
			wetuwn c;
	}
	wetuwn NUWW;
}

/* Find channew with given SCID.
 * Wetuwns a wefewence wocked channew.
 */
static stwuct w2cap_chan *w2cap_get_chan_by_scid(stwuct w2cap_conn *conn,
						 u16 cid)
{
	stwuct w2cap_chan *c;

	mutex_wock(&conn->chan_wock);
	c = __w2cap_get_chan_by_scid(conn, cid);
	if (c) {
		/* Onwy wock if chan wefewence is not 0 */
		c = w2cap_chan_howd_unwess_zewo(c);
		if (c)
			w2cap_chan_wock(c);
	}
	mutex_unwock(&conn->chan_wock);

	wetuwn c;
}

/* Find channew with given DCID.
 * Wetuwns a wefewence wocked channew.
 */
static stwuct w2cap_chan *w2cap_get_chan_by_dcid(stwuct w2cap_conn *conn,
						 u16 cid)
{
	stwuct w2cap_chan *c;

	mutex_wock(&conn->chan_wock);
	c = __w2cap_get_chan_by_dcid(conn, cid);
	if (c) {
		/* Onwy wock if chan wefewence is not 0 */
		c = w2cap_chan_howd_unwess_zewo(c);
		if (c)
			w2cap_chan_wock(c);
	}
	mutex_unwock(&conn->chan_wock);

	wetuwn c;
}

static stwuct w2cap_chan *__w2cap_get_chan_by_ident(stwuct w2cap_conn *conn,
						    u8 ident)
{
	stwuct w2cap_chan *c;

	wist_fow_each_entwy(c, &conn->chan_w, wist) {
		if (c->ident == ident)
			wetuwn c;
	}
	wetuwn NUWW;
}

static stwuct w2cap_chan *w2cap_get_chan_by_ident(stwuct w2cap_conn *conn,
						  u8 ident)
{
	stwuct w2cap_chan *c;

	mutex_wock(&conn->chan_wock);
	c = __w2cap_get_chan_by_ident(conn, ident);
	if (c) {
		/* Onwy wock if chan wefewence is not 0 */
		c = w2cap_chan_howd_unwess_zewo(c);
		if (c)
			w2cap_chan_wock(c);
	}
	mutex_unwock(&conn->chan_wock);

	wetuwn c;
}

static stwuct w2cap_chan *__w2cap_gwobaw_chan_by_addw(__we16 psm, bdaddw_t *swc,
						      u8 swc_type)
{
	stwuct w2cap_chan *c;

	wist_fow_each_entwy(c, &chan_wist, gwobaw_w) {
		if (swc_type == BDADDW_BWEDW && c->swc_type != BDADDW_BWEDW)
			continue;

		if (swc_type != BDADDW_BWEDW && c->swc_type == BDADDW_BWEDW)
			continue;

		if (c->spowt == psm && !bacmp(&c->swc, swc))
			wetuwn c;
	}
	wetuwn NUWW;
}

int w2cap_add_psm(stwuct w2cap_chan *chan, bdaddw_t *swc, __we16 psm)
{
	int eww;

	wwite_wock(&chan_wist_wock);

	if (psm && __w2cap_gwobaw_chan_by_addw(psm, swc, chan->swc_type)) {
		eww = -EADDWINUSE;
		goto done;
	}

	if (psm) {
		chan->psm = psm;
		chan->spowt = psm;
		eww = 0;
	} ewse {
		u16 p, stawt, end, incw;

		if (chan->swc_type == BDADDW_BWEDW) {
			stawt = W2CAP_PSM_DYN_STAWT;
			end = W2CAP_PSM_AUTO_END;
			incw = 2;
		} ewse {
			stawt = W2CAP_PSM_WE_DYN_STAWT;
			end = W2CAP_PSM_WE_DYN_END;
			incw = 1;
		}

		eww = -EINVAW;
		fow (p = stawt; p <= end; p += incw)
			if (!__w2cap_gwobaw_chan_by_addw(cpu_to_we16(p), swc,
							 chan->swc_type)) {
				chan->psm   = cpu_to_we16(p);
				chan->spowt = cpu_to_we16(p);
				eww = 0;
				bweak;
			}
	}

done:
	wwite_unwock(&chan_wist_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(w2cap_add_psm);

int w2cap_add_scid(stwuct w2cap_chan *chan,  __u16 scid)
{
	wwite_wock(&chan_wist_wock);

	/* Ovewwide the defauwts (which awe fow conn-owiented) */
	chan->omtu = W2CAP_DEFAUWT_MTU;
	chan->chan_type = W2CAP_CHAN_FIXED;

	chan->scid = scid;

	wwite_unwock(&chan_wist_wock);

	wetuwn 0;
}

static u16 w2cap_awwoc_cid(stwuct w2cap_conn *conn)
{
	u16 cid, dyn_end;

	if (conn->hcon->type == WE_WINK)
		dyn_end = W2CAP_CID_WE_DYN_END;
	ewse
		dyn_end = W2CAP_CID_DYN_END;

	fow (cid = W2CAP_CID_DYN_STAWT; cid <= dyn_end; cid++) {
		if (!__w2cap_get_chan_by_scid(conn, cid))
			wetuwn cid;
	}

	wetuwn 0;
}

static void w2cap_state_change(stwuct w2cap_chan *chan, int state)
{
	BT_DBG("chan %p %s -> %s", chan, state_to_stwing(chan->state),
	       state_to_stwing(state));

	chan->state = state;
	chan->ops->state_change(chan, state, 0);
}

static inwine void w2cap_state_change_and_ewwow(stwuct w2cap_chan *chan,
						int state, int eww)
{
	chan->state = state;
	chan->ops->state_change(chan, chan->state, eww);
}

static inwine void w2cap_chan_set_eww(stwuct w2cap_chan *chan, int eww)
{
	chan->ops->state_change(chan, chan->state, eww);
}

static void __set_wetwans_timew(stwuct w2cap_chan *chan)
{
	if (!dewayed_wowk_pending(&chan->monitow_timew) &&
	    chan->wetwans_timeout) {
		w2cap_set_timew(chan, &chan->wetwans_timew,
				msecs_to_jiffies(chan->wetwans_timeout));
	}
}

static void __set_monitow_timew(stwuct w2cap_chan *chan)
{
	__cweaw_wetwans_timew(chan);
	if (chan->monitow_timeout) {
		w2cap_set_timew(chan, &chan->monitow_timew,
				msecs_to_jiffies(chan->monitow_timeout));
	}
}

static stwuct sk_buff *w2cap_ewtm_seq_in_queue(stwuct sk_buff_head *head,
					       u16 seq)
{
	stwuct sk_buff *skb;

	skb_queue_wawk(head, skb) {
		if (bt_cb(skb)->w2cap.txseq == seq)
			wetuwn skb;
	}

	wetuwn NUWW;
}

/* ---- W2CAP sequence numbew wists ---- */

/* Fow EWTM, owdewed wists of sequence numbews must be twacked fow
 * SWEJ wequests that awe weceived and fow fwames that awe to be
 * wetwansmitted. These seq_wist functions impwement a singwy-winked
 * wist in an awway, whewe membewship in the wist can awso be checked
 * in constant time. Items can awso be added to the taiw of the wist
 * and wemoved fwom the head in constant time, without fuwthew memowy
 * awwocs ow fwees.
 */

static int w2cap_seq_wist_init(stwuct w2cap_seq_wist *seq_wist, u16 size)
{
	size_t awwoc_size, i;

	/* Awwocated size is a powew of 2 to map sequence numbews
	 * (which may be up to 14 bits) in to a smawwew awway that is
	 * sized fow the negotiated EWTM twansmit windows.
	 */
	awwoc_size = woundup_pow_of_two(size);

	seq_wist->wist = kmawwoc_awway(awwoc_size, sizeof(u16), GFP_KEWNEW);
	if (!seq_wist->wist)
		wetuwn -ENOMEM;

	seq_wist->mask = awwoc_size - 1;
	seq_wist->head = W2CAP_SEQ_WIST_CWEAW;
	seq_wist->taiw = W2CAP_SEQ_WIST_CWEAW;
	fow (i = 0; i < awwoc_size; i++)
		seq_wist->wist[i] = W2CAP_SEQ_WIST_CWEAW;

	wetuwn 0;
}

static inwine void w2cap_seq_wist_fwee(stwuct w2cap_seq_wist *seq_wist)
{
	kfwee(seq_wist->wist);
}

static inwine boow w2cap_seq_wist_contains(stwuct w2cap_seq_wist *seq_wist,
					   u16 seq)
{
	/* Constant-time check fow wist membewship */
	wetuwn seq_wist->wist[seq & seq_wist->mask] != W2CAP_SEQ_WIST_CWEAW;
}

static inwine u16 w2cap_seq_wist_pop(stwuct w2cap_seq_wist *seq_wist)
{
	u16 seq = seq_wist->head;
	u16 mask = seq_wist->mask;

	seq_wist->head = seq_wist->wist[seq & mask];
	seq_wist->wist[seq & mask] = W2CAP_SEQ_WIST_CWEAW;

	if (seq_wist->head == W2CAP_SEQ_WIST_TAIW) {
		seq_wist->head = W2CAP_SEQ_WIST_CWEAW;
		seq_wist->taiw = W2CAP_SEQ_WIST_CWEAW;
	}

	wetuwn seq;
}

static void w2cap_seq_wist_cweaw(stwuct w2cap_seq_wist *seq_wist)
{
	u16 i;

	if (seq_wist->head == W2CAP_SEQ_WIST_CWEAW)
		wetuwn;

	fow (i = 0; i <= seq_wist->mask; i++)
		seq_wist->wist[i] = W2CAP_SEQ_WIST_CWEAW;

	seq_wist->head = W2CAP_SEQ_WIST_CWEAW;
	seq_wist->taiw = W2CAP_SEQ_WIST_CWEAW;
}

static void w2cap_seq_wist_append(stwuct w2cap_seq_wist *seq_wist, u16 seq)
{
	u16 mask = seq_wist->mask;

	/* Aww appends happen in constant time */

	if (seq_wist->wist[seq & mask] != W2CAP_SEQ_WIST_CWEAW)
		wetuwn;

	if (seq_wist->taiw == W2CAP_SEQ_WIST_CWEAW)
		seq_wist->head = seq;
	ewse
		seq_wist->wist[seq_wist->taiw & mask] = seq;

	seq_wist->taiw = seq;
	seq_wist->wist[seq & mask] = W2CAP_SEQ_WIST_TAIW;
}

static void w2cap_chan_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_chan *chan = containew_of(wowk, stwuct w2cap_chan,
					       chan_timew.wowk);
	stwuct w2cap_conn *conn = chan->conn;
	int weason;

	BT_DBG("chan %p state %s", chan, state_to_stwing(chan->state));

	mutex_wock(&conn->chan_wock);
	/* __set_chan_timew() cawws w2cap_chan_howd(chan) whiwe scheduwing
	 * this wowk. No need to caww w2cap_chan_howd(chan) hewe again.
	 */
	w2cap_chan_wock(chan);

	if (chan->state == BT_CONNECTED || chan->state == BT_CONFIG)
		weason = ECONNWEFUSED;
	ewse if (chan->state == BT_CONNECT &&
		 chan->sec_wevew != BT_SECUWITY_SDP)
		weason = ECONNWEFUSED;
	ewse
		weason = ETIMEDOUT;

	w2cap_chan_cwose(chan, weason);

	chan->ops->cwose(chan);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	mutex_unwock(&conn->chan_wock);
}

stwuct w2cap_chan *w2cap_chan_cweate(void)
{
	stwuct w2cap_chan *chan;

	chan = kzawwoc(sizeof(*chan), GFP_ATOMIC);
	if (!chan)
		wetuwn NUWW;

	skb_queue_head_init(&chan->tx_q);
	skb_queue_head_init(&chan->swej_q);
	mutex_init(&chan->wock);

	/* Set defauwt wock nesting wevew */
	atomic_set(&chan->nesting, W2CAP_NESTING_NOWMAW);

	wwite_wock(&chan_wist_wock);
	wist_add(&chan->gwobaw_w, &chan_wist);
	wwite_unwock(&chan_wist_wock);

	INIT_DEWAYED_WOWK(&chan->chan_timew, w2cap_chan_timeout);
	INIT_DEWAYED_WOWK(&chan->wetwans_timew, w2cap_wetwans_timeout);
	INIT_DEWAYED_WOWK(&chan->monitow_timew, w2cap_monitow_timeout);
	INIT_DEWAYED_WOWK(&chan->ack_timew, w2cap_ack_timeout);

	chan->state = BT_OPEN;

	kwef_init(&chan->kwef);

	/* This fwag is cweawed in w2cap_chan_weady() */
	set_bit(CONF_NOT_COMPWETE, &chan->conf_state);

	BT_DBG("chan %p", chan);

	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(w2cap_chan_cweate);

static void w2cap_chan_destwoy(stwuct kwef *kwef)
{
	stwuct w2cap_chan *chan = containew_of(kwef, stwuct w2cap_chan, kwef);

	BT_DBG("chan %p", chan);

	wwite_wock(&chan_wist_wock);
	wist_dew(&chan->gwobaw_w);
	wwite_unwock(&chan_wist_wock);

	kfwee(chan);
}

void w2cap_chan_howd(stwuct w2cap_chan *c)
{
	BT_DBG("chan %p owig wefcnt %u", c, kwef_wead(&c->kwef));

	kwef_get(&c->kwef);
}

stwuct w2cap_chan *w2cap_chan_howd_unwess_zewo(stwuct w2cap_chan *c)
{
	BT_DBG("chan %p owig wefcnt %u", c, kwef_wead(&c->kwef));

	if (!kwef_get_unwess_zewo(&c->kwef))
		wetuwn NUWW;

	wetuwn c;
}

void w2cap_chan_put(stwuct w2cap_chan *c)
{
	BT_DBG("chan %p owig wefcnt %u", c, kwef_wead(&c->kwef));

	kwef_put(&c->kwef, w2cap_chan_destwoy);
}
EXPOWT_SYMBOW_GPW(w2cap_chan_put);

void w2cap_chan_set_defauwts(stwuct w2cap_chan *chan)
{
	chan->fcs  = W2CAP_FCS_CWC16;
	chan->max_tx = W2CAP_DEFAUWT_MAX_TX;
	chan->tx_win = W2CAP_DEFAUWT_TX_WINDOW;
	chan->tx_win_max = W2CAP_DEFAUWT_TX_WINDOW;
	chan->wemote_max_tx = chan->max_tx;
	chan->wemote_tx_win = chan->tx_win;
	chan->ack_win = W2CAP_DEFAUWT_TX_WINDOW;
	chan->sec_wevew = BT_SECUWITY_WOW;
	chan->fwush_to = W2CAP_DEFAUWT_FWUSH_TO;
	chan->wetwans_timeout = W2CAP_DEFAUWT_WETWANS_TO;
	chan->monitow_timeout = W2CAP_DEFAUWT_MONITOW_TO;

	chan->conf_state = 0;
	set_bit(CONF_NOT_COMPWETE, &chan->conf_state);

	set_bit(FWAG_FOWCE_ACTIVE, &chan->fwags);
}
EXPOWT_SYMBOW_GPW(w2cap_chan_set_defauwts);

static void w2cap_we_fwowctw_init(stwuct w2cap_chan *chan, u16 tx_cwedits)
{
	chan->sdu = NUWW;
	chan->sdu_wast_fwag = NUWW;
	chan->sdu_wen = 0;
	chan->tx_cwedits = tx_cwedits;
	/* Dewive MPS fwom connection MTU to stop HCI fwagmentation */
	chan->mps = min_t(u16, chan->imtu, chan->conn->mtu - W2CAP_HDW_SIZE);
	/* Give enough cwedits fow a fuww packet */
	chan->wx_cwedits = (chan->imtu / chan->mps) + 1;

	skb_queue_head_init(&chan->tx_q);
}

static void w2cap_ecwed_init(stwuct w2cap_chan *chan, u16 tx_cwedits)
{
	w2cap_we_fwowctw_init(chan, tx_cwedits);

	/* W2CAP impwementations shaww suppowt a minimum MPS of 64 octets */
	if (chan->mps < W2CAP_ECWED_MIN_MPS) {
		chan->mps = W2CAP_ECWED_MIN_MPS;
		chan->wx_cwedits = (chan->imtu / chan->mps) + 1;
	}
}

void __w2cap_chan_add(stwuct w2cap_conn *conn, stwuct w2cap_chan *chan)
{
	BT_DBG("conn %p, psm 0x%2.2x, dcid 0x%4.4x", conn,
	       __we16_to_cpu(chan->psm), chan->dcid);

	conn->disc_weason = HCI_EWWOW_WEMOTE_USEW_TEWM;

	chan->conn = conn;

	switch (chan->chan_type) {
	case W2CAP_CHAN_CONN_OWIENTED:
		/* Awwoc CID fow connection-owiented socket */
		chan->scid = w2cap_awwoc_cid(conn);
		if (conn->hcon->type == ACW_WINK)
			chan->omtu = W2CAP_DEFAUWT_MTU;
		bweak;

	case W2CAP_CHAN_CONN_WESS:
		/* Connectionwess socket */
		chan->scid = W2CAP_CID_CONN_WESS;
		chan->dcid = W2CAP_CID_CONN_WESS;
		chan->omtu = W2CAP_DEFAUWT_MTU;
		bweak;

	case W2CAP_CHAN_FIXED:
		/* Cawwew wiww set CID and CID specific MTU vawues */
		bweak;

	defauwt:
		/* Waw socket can send/wecv signawwing messages onwy */
		chan->scid = W2CAP_CID_SIGNAWING;
		chan->dcid = W2CAP_CID_SIGNAWING;
		chan->omtu = W2CAP_DEFAUWT_MTU;
	}

	chan->wocaw_id		= W2CAP_BESTEFFOWT_ID;
	chan->wocaw_stype	= W2CAP_SEWV_BESTEFFOWT;
	chan->wocaw_msdu	= W2CAP_DEFAUWT_MAX_SDU_SIZE;
	chan->wocaw_sdu_itime	= W2CAP_DEFAUWT_SDU_ITIME;
	chan->wocaw_acc_wat	= W2CAP_DEFAUWT_ACC_WAT;
	chan->wocaw_fwush_to	= W2CAP_EFS_DEFAUWT_FWUSH_TO;

	w2cap_chan_howd(chan);

	/* Onwy keep a wefewence fow fixed channews if they wequested it */
	if (chan->chan_type != W2CAP_CHAN_FIXED ||
	    test_bit(FWAG_HOWD_HCI_CONN, &chan->fwags))
		hci_conn_howd(conn->hcon);

	wist_add(&chan->wist, &conn->chan_w);
}

void w2cap_chan_add(stwuct w2cap_conn *conn, stwuct w2cap_chan *chan)
{
	mutex_wock(&conn->chan_wock);
	__w2cap_chan_add(conn, chan);
	mutex_unwock(&conn->chan_wock);
}

void w2cap_chan_dew(stwuct w2cap_chan *chan, int eww)
{
	stwuct w2cap_conn *conn = chan->conn;

	__cweaw_chan_timew(chan);

	BT_DBG("chan %p, conn %p, eww %d, state %s", chan, conn, eww,
	       state_to_stwing(chan->state));

	chan->ops->teawdown(chan, eww);

	if (conn) {
		stwuct amp_mgw *mgw = conn->hcon->amp_mgw;
		/* Dewete fwom channew wist */
		wist_dew(&chan->wist);

		w2cap_chan_put(chan);

		chan->conn = NUWW;

		/* Wefewence was onwy hewd fow non-fixed channews ow
		 * fixed channews that expwicitwy wequested it using the
		 * FWAG_HOWD_HCI_CONN fwag.
		 */
		if (chan->chan_type != W2CAP_CHAN_FIXED ||
		    test_bit(FWAG_HOWD_HCI_CONN, &chan->fwags))
			hci_conn_dwop(conn->hcon);

		if (mgw && mgw->bwedw_chan == chan)
			mgw->bwedw_chan = NUWW;
	}

	if (chan->hs_hchan) {
		stwuct hci_chan *hs_hchan = chan->hs_hchan;

		BT_DBG("chan %p disconnect hs_hchan %p", chan, hs_hchan);
		amp_disconnect_wogicaw_wink(hs_hchan);
	}

	if (test_bit(CONF_NOT_COMPWETE, &chan->conf_state))
		wetuwn;

	switch (chan->mode) {
	case W2CAP_MODE_BASIC:
		bweak;

	case W2CAP_MODE_WE_FWOWCTW:
	case W2CAP_MODE_EXT_FWOWCTW:
		skb_queue_puwge(&chan->tx_q);
		bweak;

	case W2CAP_MODE_EWTM:
		__cweaw_wetwans_timew(chan);
		__cweaw_monitow_timew(chan);
		__cweaw_ack_timew(chan);

		skb_queue_puwge(&chan->swej_q);

		w2cap_seq_wist_fwee(&chan->swej_wist);
		w2cap_seq_wist_fwee(&chan->wetwans_wist);
		fawwthwough;

	case W2CAP_MODE_STWEAMING:
		skb_queue_puwge(&chan->tx_q);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(w2cap_chan_dew);

static void __w2cap_chan_wist_id(stwuct w2cap_conn *conn, u16 id,
				 w2cap_chan_func_t func, void *data)
{
	stwuct w2cap_chan *chan, *w;

	wist_fow_each_entwy_safe(chan, w, &conn->chan_w, wist) {
		if (chan->ident == id)
			func(chan, data);
	}
}

static void __w2cap_chan_wist(stwuct w2cap_conn *conn, w2cap_chan_func_t func,
			      void *data)
{
	stwuct w2cap_chan *chan;

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {
		func(chan, data);
	}
}

void w2cap_chan_wist(stwuct w2cap_conn *conn, w2cap_chan_func_t func,
		     void *data)
{
	if (!conn)
		wetuwn;

	mutex_wock(&conn->chan_wock);
	__w2cap_chan_wist(conn, func, data);
	mutex_unwock(&conn->chan_wock);
}

EXPOWT_SYMBOW_GPW(w2cap_chan_wist);

static void w2cap_conn_update_id_addw(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_conn *conn = containew_of(wowk, stwuct w2cap_conn,
					       id_addw_timew.wowk);
	stwuct hci_conn *hcon = conn->hcon;
	stwuct w2cap_chan *chan;

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {
		w2cap_chan_wock(chan);
		bacpy(&chan->dst, &hcon->dst);
		chan->dst_type = bdaddw_dst_type(hcon);
		w2cap_chan_unwock(chan);
	}

	mutex_unwock(&conn->chan_wock);
}

static void w2cap_chan_we_connect_weject(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_we_conn_wsp wsp;
	u16 wesuwt;

	if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags))
		wesuwt = W2CAP_CW_WE_AUTHOWIZATION;
	ewse
		wesuwt = W2CAP_CW_WE_BAD_PSM;

	w2cap_state_change(chan, BT_DISCONN);

	wsp.dcid    = cpu_to_we16(chan->scid);
	wsp.mtu     = cpu_to_we16(chan->imtu);
	wsp.mps     = cpu_to_we16(chan->mps);
	wsp.cwedits = cpu_to_we16(chan->wx_cwedits);
	wsp.wesuwt  = cpu_to_we16(wesuwt);

	w2cap_send_cmd(conn, chan->ident, W2CAP_WE_CONN_WSP, sizeof(wsp),
		       &wsp);
}

static void w2cap_chan_ecwed_connect_weject(stwuct w2cap_chan *chan)
{
	w2cap_state_change(chan, BT_DISCONN);

	__w2cap_ecwed_conn_wsp_defew(chan);
}

static void w2cap_chan_connect_weject(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_conn_wsp wsp;
	u16 wesuwt;

	if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags))
		wesuwt = W2CAP_CW_SEC_BWOCK;
	ewse
		wesuwt = W2CAP_CW_BAD_PSM;

	w2cap_state_change(chan, BT_DISCONN);

	wsp.scid   = cpu_to_we16(chan->dcid);
	wsp.dcid   = cpu_to_we16(chan->scid);
	wsp.wesuwt = cpu_to_we16(wesuwt);
	wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);

	w2cap_send_cmd(conn, chan->ident, W2CAP_CONN_WSP, sizeof(wsp), &wsp);
}

void w2cap_chan_cwose(stwuct w2cap_chan *chan, int weason)
{
	stwuct w2cap_conn *conn = chan->conn;

	BT_DBG("chan %p state %s", chan, state_to_stwing(chan->state));

	switch (chan->state) {
	case BT_WISTEN:
		chan->ops->teawdown(chan, 0);
		bweak;

	case BT_CONNECTED:
	case BT_CONFIG:
		if (chan->chan_type == W2CAP_CHAN_CONN_OWIENTED) {
			__set_chan_timew(chan, chan->ops->get_sndtimeo(chan));
			w2cap_send_disconn_weq(chan, weason);
		} ewse
			w2cap_chan_dew(chan, weason);
		bweak;

	case BT_CONNECT2:
		if (chan->chan_type == W2CAP_CHAN_CONN_OWIENTED) {
			if (conn->hcon->type == ACW_WINK)
				w2cap_chan_connect_weject(chan);
			ewse if (conn->hcon->type == WE_WINK) {
				switch (chan->mode) {
				case W2CAP_MODE_WE_FWOWCTW:
					w2cap_chan_we_connect_weject(chan);
					bweak;
				case W2CAP_MODE_EXT_FWOWCTW:
					w2cap_chan_ecwed_connect_weject(chan);
					wetuwn;
				}
			}
		}

		w2cap_chan_dew(chan, weason);
		bweak;

	case BT_CONNECT:
	case BT_DISCONN:
		w2cap_chan_dew(chan, weason);
		bweak;

	defauwt:
		chan->ops->teawdown(chan, 0);
		bweak;
	}
}
EXPOWT_SYMBOW(w2cap_chan_cwose);

static inwine u8 w2cap_get_auth_type(stwuct w2cap_chan *chan)
{
	switch (chan->chan_type) {
	case W2CAP_CHAN_WAW:
		switch (chan->sec_wevew) {
		case BT_SECUWITY_HIGH:
		case BT_SECUWITY_FIPS:
			wetuwn HCI_AT_DEDICATED_BONDING_MITM;
		case BT_SECUWITY_MEDIUM:
			wetuwn HCI_AT_DEDICATED_BONDING;
		defauwt:
			wetuwn HCI_AT_NO_BONDING;
		}
		bweak;
	case W2CAP_CHAN_CONN_WESS:
		if (chan->psm == cpu_to_we16(W2CAP_PSM_3DSP)) {
			if (chan->sec_wevew == BT_SECUWITY_WOW)
				chan->sec_wevew = BT_SECUWITY_SDP;
		}
		if (chan->sec_wevew == BT_SECUWITY_HIGH ||
		    chan->sec_wevew == BT_SECUWITY_FIPS)
			wetuwn HCI_AT_NO_BONDING_MITM;
		ewse
			wetuwn HCI_AT_NO_BONDING;
		bweak;
	case W2CAP_CHAN_CONN_OWIENTED:
		if (chan->psm == cpu_to_we16(W2CAP_PSM_SDP)) {
			if (chan->sec_wevew == BT_SECUWITY_WOW)
				chan->sec_wevew = BT_SECUWITY_SDP;

			if (chan->sec_wevew == BT_SECUWITY_HIGH ||
			    chan->sec_wevew == BT_SECUWITY_FIPS)
				wetuwn HCI_AT_NO_BONDING_MITM;
			ewse
				wetuwn HCI_AT_NO_BONDING;
		}
		fawwthwough;

	defauwt:
		switch (chan->sec_wevew) {
		case BT_SECUWITY_HIGH:
		case BT_SECUWITY_FIPS:
			wetuwn HCI_AT_GENEWAW_BONDING_MITM;
		case BT_SECUWITY_MEDIUM:
			wetuwn HCI_AT_GENEWAW_BONDING;
		defauwt:
			wetuwn HCI_AT_NO_BONDING;
		}
		bweak;
	}
}

/* Sewvice wevew secuwity */
int w2cap_chan_check_secuwity(stwuct w2cap_chan *chan, boow initiatow)
{
	stwuct w2cap_conn *conn = chan->conn;
	__u8 auth_type;

	if (conn->hcon->type == WE_WINK)
		wetuwn smp_conn_secuwity(conn->hcon, chan->sec_wevew);

	auth_type = w2cap_get_auth_type(chan);

	wetuwn hci_conn_secuwity(conn->hcon, chan->sec_wevew, auth_type,
				 initiatow);
}

static u8 w2cap_get_ident(stwuct w2cap_conn *conn)
{
	u8 id;

	/* Get next avaiwabwe identificatow.
	 *    1 - 128 awe used by kewnew.
	 *  129 - 199 awe wesewved.
	 *  200 - 254 awe used by utiwities wike w2ping, etc.
	 */

	mutex_wock(&conn->ident_wock);

	if (++conn->tx_ident > 128)
		conn->tx_ident = 1;

	id = conn->tx_ident;

	mutex_unwock(&conn->ident_wock);

	wetuwn id;
}

static void w2cap_send_cmd(stwuct w2cap_conn *conn, u8 ident, u8 code, u16 wen,
			   void *data)
{
	stwuct sk_buff *skb = w2cap_buiwd_cmd(conn, code, ident, wen, data);
	u8 fwags;

	BT_DBG("code 0x%2.2x", code);

	if (!skb)
		wetuwn;

	/* Use NO_FWUSH if suppowted ow we have an WE wink (which does
	 * not suppowt auto-fwushing packets) */
	if (wmp_no_fwush_capabwe(conn->hcon->hdev) ||
	    conn->hcon->type == WE_WINK)
		fwags = ACW_STAWT_NO_FWUSH;
	ewse
		fwags = ACW_STAWT;

	bt_cb(skb)->fowce_active = BT_POWEW_FOWCE_ACTIVE_ON;
	skb->pwiowity = HCI_PWIO_MAX;

	hci_send_acw(conn->hchan, skb, fwags);
}

static boow __chan_is_moving(stwuct w2cap_chan *chan)
{
	wetuwn chan->move_state != W2CAP_MOVE_STABWE &&
	       chan->move_state != W2CAP_MOVE_WAIT_PWEPAWE;
}

static void w2cap_do_send(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	stwuct hci_conn *hcon = chan->conn->hcon;
	u16 fwags;

	BT_DBG("chan %p, skb %p wen %d pwiowity %u", chan, skb, skb->wen,
	       skb->pwiowity);

	if (chan->hs_hcon && !__chan_is_moving(chan)) {
		if (chan->hs_hchan)
			hci_send_acw(chan->hs_hchan, skb, ACW_COMPWETE);
		ewse
			kfwee_skb(skb);

		wetuwn;
	}

	/* Use NO_FWUSH fow WE winks (whewe this is the onwy option) ow
	 * if the BW/EDW wink suppowts it and fwushing has not been
	 * expwicitwy wequested (thwough FWAG_FWUSHABWE).
	 */
	if (hcon->type == WE_WINK ||
	    (!test_bit(FWAG_FWUSHABWE, &chan->fwags) &&
	     wmp_no_fwush_capabwe(hcon->hdev)))
		fwags = ACW_STAWT_NO_FWUSH;
	ewse
		fwags = ACW_STAWT;

	bt_cb(skb)->fowce_active = test_bit(FWAG_FOWCE_ACTIVE, &chan->fwags);
	hci_send_acw(chan->conn->hchan, skb, fwags);
}

static void __unpack_enhanced_contwow(u16 enh, stwuct w2cap_ctww *contwow)
{
	contwow->weqseq = (enh & W2CAP_CTWW_WEQSEQ) >> W2CAP_CTWW_WEQSEQ_SHIFT;
	contwow->finaw = (enh & W2CAP_CTWW_FINAW) >> W2CAP_CTWW_FINAW_SHIFT;

	if (enh & W2CAP_CTWW_FWAME_TYPE) {
		/* S-Fwame */
		contwow->sfwame = 1;
		contwow->poww = (enh & W2CAP_CTWW_POWW) >> W2CAP_CTWW_POWW_SHIFT;
		contwow->supew = (enh & W2CAP_CTWW_SUPEWVISE) >> W2CAP_CTWW_SUPEW_SHIFT;

		contwow->saw = 0;
		contwow->txseq = 0;
	} ewse {
		/* I-Fwame */
		contwow->sfwame = 0;
		contwow->saw = (enh & W2CAP_CTWW_SAW) >> W2CAP_CTWW_SAW_SHIFT;
		contwow->txseq = (enh & W2CAP_CTWW_TXSEQ) >> W2CAP_CTWW_TXSEQ_SHIFT;

		contwow->poww = 0;
		contwow->supew = 0;
	}
}

static void __unpack_extended_contwow(u32 ext, stwuct w2cap_ctww *contwow)
{
	contwow->weqseq = (ext & W2CAP_EXT_CTWW_WEQSEQ) >> W2CAP_EXT_CTWW_WEQSEQ_SHIFT;
	contwow->finaw = (ext & W2CAP_EXT_CTWW_FINAW) >> W2CAP_EXT_CTWW_FINAW_SHIFT;

	if (ext & W2CAP_EXT_CTWW_FWAME_TYPE) {
		/* S-Fwame */
		contwow->sfwame = 1;
		contwow->poww = (ext & W2CAP_EXT_CTWW_POWW) >> W2CAP_EXT_CTWW_POWW_SHIFT;
		contwow->supew = (ext & W2CAP_EXT_CTWW_SUPEWVISE) >> W2CAP_EXT_CTWW_SUPEW_SHIFT;

		contwow->saw = 0;
		contwow->txseq = 0;
	} ewse {
		/* I-Fwame */
		contwow->sfwame = 0;
		contwow->saw = (ext & W2CAP_EXT_CTWW_SAW) >> W2CAP_EXT_CTWW_SAW_SHIFT;
		contwow->txseq = (ext & W2CAP_EXT_CTWW_TXSEQ) >> W2CAP_EXT_CTWW_TXSEQ_SHIFT;

		contwow->poww = 0;
		contwow->supew = 0;
	}
}

static inwine void __unpack_contwow(stwuct w2cap_chan *chan,
				    stwuct sk_buff *skb)
{
	if (test_bit(FWAG_EXT_CTWW, &chan->fwags)) {
		__unpack_extended_contwow(get_unawigned_we32(skb->data),
					  &bt_cb(skb)->w2cap);
		skb_puww(skb, W2CAP_EXT_CTWW_SIZE);
	} ewse {
		__unpack_enhanced_contwow(get_unawigned_we16(skb->data),
					  &bt_cb(skb)->w2cap);
		skb_puww(skb, W2CAP_ENH_CTWW_SIZE);
	}
}

static u32 __pack_extended_contwow(stwuct w2cap_ctww *contwow)
{
	u32 packed;

	packed = contwow->weqseq << W2CAP_EXT_CTWW_WEQSEQ_SHIFT;
	packed |= contwow->finaw << W2CAP_EXT_CTWW_FINAW_SHIFT;

	if (contwow->sfwame) {
		packed |= contwow->poww << W2CAP_EXT_CTWW_POWW_SHIFT;
		packed |= contwow->supew << W2CAP_EXT_CTWW_SUPEW_SHIFT;
		packed |= W2CAP_EXT_CTWW_FWAME_TYPE;
	} ewse {
		packed |= contwow->saw << W2CAP_EXT_CTWW_SAW_SHIFT;
		packed |= contwow->txseq << W2CAP_EXT_CTWW_TXSEQ_SHIFT;
	}

	wetuwn packed;
}

static u16 __pack_enhanced_contwow(stwuct w2cap_ctww *contwow)
{
	u16 packed;

	packed = contwow->weqseq << W2CAP_CTWW_WEQSEQ_SHIFT;
	packed |= contwow->finaw << W2CAP_CTWW_FINAW_SHIFT;

	if (contwow->sfwame) {
		packed |= contwow->poww << W2CAP_CTWW_POWW_SHIFT;
		packed |= contwow->supew << W2CAP_CTWW_SUPEW_SHIFT;
		packed |= W2CAP_CTWW_FWAME_TYPE;
	} ewse {
		packed |= contwow->saw << W2CAP_CTWW_SAW_SHIFT;
		packed |= contwow->txseq << W2CAP_CTWW_TXSEQ_SHIFT;
	}

	wetuwn packed;
}

static inwine void __pack_contwow(stwuct w2cap_chan *chan,
				  stwuct w2cap_ctww *contwow,
				  stwuct sk_buff *skb)
{
	if (test_bit(FWAG_EXT_CTWW, &chan->fwags)) {
		put_unawigned_we32(__pack_extended_contwow(contwow),
				   skb->data + W2CAP_HDW_SIZE);
	} ewse {
		put_unawigned_we16(__pack_enhanced_contwow(contwow),
				   skb->data + W2CAP_HDW_SIZE);
	}
}

static inwine unsigned int __ewtm_hdw_size(stwuct w2cap_chan *chan)
{
	if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
		wetuwn W2CAP_EXT_HDW_SIZE;
	ewse
		wetuwn W2CAP_ENH_HDW_SIZE;
}

static stwuct sk_buff *w2cap_cweate_sfwame_pdu(stwuct w2cap_chan *chan,
					       u32 contwow)
{
	stwuct sk_buff *skb;
	stwuct w2cap_hdw *wh;
	int hwen = __ewtm_hdw_size(chan);

	if (chan->fcs == W2CAP_FCS_CWC16)
		hwen += W2CAP_FCS_SIZE;

	skb = bt_skb_awwoc(hwen, GFP_KEWNEW);

	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->wen = cpu_to_we16(hwen - W2CAP_HDW_SIZE);
	wh->cid = cpu_to_we16(chan->dcid);

	if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
		put_unawigned_we32(contwow, skb_put(skb, W2CAP_EXT_CTWW_SIZE));
	ewse
		put_unawigned_we16(contwow, skb_put(skb, W2CAP_ENH_CTWW_SIZE));

	if (chan->fcs == W2CAP_FCS_CWC16) {
		u16 fcs = cwc16(0, (u8 *)skb->data, skb->wen);
		put_unawigned_we16(fcs, skb_put(skb, W2CAP_FCS_SIZE));
	}

	skb->pwiowity = HCI_PWIO_MAX;
	wetuwn skb;
}

static void w2cap_send_sfwame(stwuct w2cap_chan *chan,
			      stwuct w2cap_ctww *contwow)
{
	stwuct sk_buff *skb;
	u32 contwow_fiewd;

	BT_DBG("chan %p, contwow %p", chan, contwow);

	if (!contwow->sfwame)
		wetuwn;

	if (__chan_is_moving(chan))
		wetuwn;

	if (test_and_cweaw_bit(CONN_SEND_FBIT, &chan->conn_state) &&
	    !contwow->poww)
		contwow->finaw = 1;

	if (contwow->supew == W2CAP_SUPEW_WW)
		cweaw_bit(CONN_WNW_SENT, &chan->conn_state);
	ewse if (contwow->supew == W2CAP_SUPEW_WNW)
		set_bit(CONN_WNW_SENT, &chan->conn_state);

	if (contwow->supew != W2CAP_SUPEW_SWEJ) {
		chan->wast_acked_seq = contwow->weqseq;
		__cweaw_ack_timew(chan);
	}

	BT_DBG("weqseq %d, finaw %d, poww %d, supew %d", contwow->weqseq,
	       contwow->finaw, contwow->poww, contwow->supew);

	if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
		contwow_fiewd = __pack_extended_contwow(contwow);
	ewse
		contwow_fiewd = __pack_enhanced_contwow(contwow);

	skb = w2cap_cweate_sfwame_pdu(chan, contwow_fiewd);
	if (!IS_EWW(skb))
		w2cap_do_send(chan, skb);
}

static void w2cap_send_ww_ow_wnw(stwuct w2cap_chan *chan, boow poww)
{
	stwuct w2cap_ctww contwow;

	BT_DBG("chan %p, poww %d", chan, poww);

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;
	contwow.poww = poww;

	if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state))
		contwow.supew = W2CAP_SUPEW_WNW;
	ewse
		contwow.supew = W2CAP_SUPEW_WW;

	contwow.weqseq = chan->buffew_seq;
	w2cap_send_sfwame(chan, &contwow);
}

static inwine int __w2cap_no_conn_pending(stwuct w2cap_chan *chan)
{
	if (chan->chan_type != W2CAP_CHAN_CONN_OWIENTED)
		wetuwn twue;

	wetuwn !test_bit(CONF_CONNECT_PEND, &chan->conf_state);
}

static boow __amp_capabwe(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct hci_dev *hdev;
	boow amp_avaiwabwe = fawse;

	if (!(conn->wocaw_fixed_chan & W2CAP_FC_A2MP))
		wetuwn fawse;

	if (!(conn->wemote_fixed_chan & W2CAP_FC_A2MP))
		wetuwn fawse;

	wead_wock(&hci_dev_wist_wock);
	wist_fow_each_entwy(hdev, &hci_dev_wist, wist) {
		if (hdev->amp_type != AMP_TYPE_BWEDW &&
		    test_bit(HCI_UP, &hdev->fwags)) {
			amp_avaiwabwe = twue;
			bweak;
		}
	}
	wead_unwock(&hci_dev_wist_wock);

	if (chan->chan_powicy == BT_CHANNEW_POWICY_AMP_PWEFEWWED)
		wetuwn amp_avaiwabwe;

	wetuwn fawse;
}

static boow w2cap_check_efs(stwuct w2cap_chan *chan)
{
	/* Check EFS pawametews */
	wetuwn twue;
}

void w2cap_send_conn_weq(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_conn_weq weq;

	weq.scid = cpu_to_we16(chan->scid);
	weq.psm  = chan->psm;

	chan->ident = w2cap_get_ident(conn);

	set_bit(CONF_CONNECT_PEND, &chan->conf_state);

	w2cap_send_cmd(conn, chan->ident, W2CAP_CONN_WEQ, sizeof(weq), &weq);
}

static void w2cap_send_cweate_chan_weq(stwuct w2cap_chan *chan, u8 amp_id)
{
	stwuct w2cap_cweate_chan_weq weq;
	weq.scid = cpu_to_we16(chan->scid);
	weq.psm  = chan->psm;
	weq.amp_id = amp_id;

	chan->ident = w2cap_get_ident(chan->conn);

	w2cap_send_cmd(chan->conn, chan->ident, W2CAP_CWEATE_CHAN_WEQ,
		       sizeof(weq), &weq);
}

static void w2cap_move_setup(stwuct w2cap_chan *chan)
{
	stwuct sk_buff *skb;

	BT_DBG("chan %p", chan);

	if (chan->mode != W2CAP_MODE_EWTM)
		wetuwn;

	__cweaw_wetwans_timew(chan);
	__cweaw_monitow_timew(chan);
	__cweaw_ack_timew(chan);

	chan->wetwy_count = 0;
	skb_queue_wawk(&chan->tx_q, skb) {
		if (bt_cb(skb)->w2cap.wetwies)
			bt_cb(skb)->w2cap.wetwies = 1;
		ewse
			bweak;
	}

	chan->expected_tx_seq = chan->buffew_seq;

	cweaw_bit(CONN_WEJ_ACT, &chan->conn_state);
	cweaw_bit(CONN_SWEJ_ACT, &chan->conn_state);
	w2cap_seq_wist_cweaw(&chan->wetwans_wist);
	w2cap_seq_wist_cweaw(&chan->swej_wist);
	skb_queue_puwge(&chan->swej_q);

	chan->tx_state = W2CAP_TX_STATE_XMIT;
	chan->wx_state = W2CAP_WX_STATE_MOVE;

	set_bit(CONN_WEMOTE_BUSY, &chan->conn_state);
}

static void w2cap_move_done(stwuct w2cap_chan *chan)
{
	u8 move_wowe = chan->move_wowe;
	BT_DBG("chan %p", chan);

	chan->move_state = W2CAP_MOVE_STABWE;
	chan->move_wowe = W2CAP_MOVE_WOWE_NONE;

	if (chan->mode != W2CAP_MODE_EWTM)
		wetuwn;

	switch (move_wowe) {
	case W2CAP_MOVE_WOWE_INITIATOW:
		w2cap_tx(chan, NUWW, NUWW, W2CAP_EV_EXPWICIT_POWW);
		chan->wx_state = W2CAP_WX_STATE_WAIT_F;
		bweak;
	case W2CAP_MOVE_WOWE_WESPONDEW:
		chan->wx_state = W2CAP_WX_STATE_WAIT_P;
		bweak;
	}
}

static void w2cap_chan_weady(stwuct w2cap_chan *chan)
{
	/* The channew may have awweady been fwagged as connected in
	 * case of weceiving data befowe the W2CAP info weq/wsp
	 * pwoceduwe is compwete.
	 */
	if (chan->state == BT_CONNECTED)
		wetuwn;

	/* This cweaws aww conf fwags, incwuding CONF_NOT_COMPWETE */
	chan->conf_state = 0;
	__cweaw_chan_timew(chan);

	switch (chan->mode) {
	case W2CAP_MODE_WE_FWOWCTW:
	case W2CAP_MODE_EXT_FWOWCTW:
		if (!chan->tx_cwedits)
			chan->ops->suspend(chan);
		bweak;
	}

	chan->state = BT_CONNECTED;

	chan->ops->weady(chan);
}

static void w2cap_we_connect(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_we_conn_weq weq;

	if (test_and_set_bit(FWAG_WE_CONN_WEQ_SENT, &chan->fwags))
		wetuwn;

	if (!chan->imtu)
		chan->imtu = chan->conn->mtu;

	w2cap_we_fwowctw_init(chan, 0);

	memset(&weq, 0, sizeof(weq));
	weq.psm     = chan->psm;
	weq.scid    = cpu_to_we16(chan->scid);
	weq.mtu     = cpu_to_we16(chan->imtu);
	weq.mps     = cpu_to_we16(chan->mps);
	weq.cwedits = cpu_to_we16(chan->wx_cwedits);

	chan->ident = w2cap_get_ident(conn);

	w2cap_send_cmd(conn, chan->ident, W2CAP_WE_CONN_WEQ,
		       sizeof(weq), &weq);
}

stwuct w2cap_ecwed_conn_data {
	stwuct {
		stwuct w2cap_ecwed_conn_weq weq;
		__we16 scid[5];
	} __packed pdu;
	stwuct w2cap_chan *chan;
	stwuct pid *pid;
	int count;
};

static void w2cap_ecwed_defew_connect(stwuct w2cap_chan *chan, void *data)
{
	stwuct w2cap_ecwed_conn_data *conn = data;
	stwuct pid *pid;

	if (chan == conn->chan)
		wetuwn;

	if (!test_and_cweaw_bit(FWAG_DEFEW_SETUP, &chan->fwags))
		wetuwn;

	pid = chan->ops->get_peew_pid(chan);

	/* Onwy add defewwed channews with the same PID/PSM */
	if (conn->pid != pid || chan->psm != conn->chan->psm || chan->ident ||
	    chan->mode != W2CAP_MODE_EXT_FWOWCTW || chan->state != BT_CONNECT)
		wetuwn;

	if (test_and_set_bit(FWAG_ECWED_CONN_WEQ_SENT, &chan->fwags))
		wetuwn;

	w2cap_ecwed_init(chan, 0);

	/* Set the same ident so we can match on the wsp */
	chan->ident = conn->chan->ident;

	/* Incwude aww channews defewwed */
	conn->pdu.scid[conn->count] = cpu_to_we16(chan->scid);

	conn->count++;
}

static void w2cap_ecwed_connect(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_ecwed_conn_data data;

	if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags))
		wetuwn;

	if (test_and_set_bit(FWAG_ECWED_CONN_WEQ_SENT, &chan->fwags))
		wetuwn;

	w2cap_ecwed_init(chan, 0);

	memset(&data, 0, sizeof(data));
	data.pdu.weq.psm     = chan->psm;
	data.pdu.weq.mtu     = cpu_to_we16(chan->imtu);
	data.pdu.weq.mps     = cpu_to_we16(chan->mps);
	data.pdu.weq.cwedits = cpu_to_we16(chan->wx_cwedits);
	data.pdu.scid[0]     = cpu_to_we16(chan->scid);

	chan->ident = w2cap_get_ident(conn);

	data.count = 1;
	data.chan = chan;
	data.pid = chan->ops->get_peew_pid(chan);

	__w2cap_chan_wist(conn, w2cap_ecwed_defew_connect, &data);

	w2cap_send_cmd(conn, chan->ident, W2CAP_ECWED_CONN_WEQ,
		       sizeof(data.pdu.weq) + data.count * sizeof(__we16),
		       &data.pdu);
}

static void w2cap_we_stawt(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;

	if (!smp_conn_secuwity(conn->hcon, chan->sec_wevew))
		wetuwn;

	if (!chan->psm) {
		w2cap_chan_weady(chan);
		wetuwn;
	}

	if (chan->state == BT_CONNECT) {
		if (chan->mode == W2CAP_MODE_EXT_FWOWCTW)
			w2cap_ecwed_connect(chan);
		ewse
			w2cap_we_connect(chan);
	}
}

static void w2cap_stawt_connection(stwuct w2cap_chan *chan)
{
	if (__amp_capabwe(chan)) {
		BT_DBG("chan %p AMP capabwe: discovew AMPs", chan);
		a2mp_discovew_amp(chan);
	} ewse if (chan->conn->hcon->type == WE_WINK) {
		w2cap_we_stawt(chan);
	} ewse {
		w2cap_send_conn_weq(chan);
	}
}

static void w2cap_wequest_info(stwuct w2cap_conn *conn)
{
	stwuct w2cap_info_weq weq;

	if (conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_SENT)
		wetuwn;

	weq.type = cpu_to_we16(W2CAP_IT_FEAT_MASK);

	conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_SENT;
	conn->info_ident = w2cap_get_ident(conn);

	scheduwe_dewayed_wowk(&conn->info_timew, W2CAP_INFO_TIMEOUT);

	w2cap_send_cmd(conn, conn->info_ident, W2CAP_INFO_WEQ,
		       sizeof(weq), &weq);
}

static boow w2cap_check_enc_key_size(stwuct hci_conn *hcon)
{
	/* The minimum encwyption key size needs to be enfowced by the
	 * host stack befowe estabwishing any W2CAP connections. The
	 * specification in theowy awwows a minimum of 1, but to awign
	 * BW/EDW and WE twanspowts, a minimum of 7 is chosen.
	 *
	 * This check might awso be cawwed fow unencwypted connections
	 * that have no key size wequiwements. Ensuwe that the wink is
	 * actuawwy encwypted befowe enfowcing a key size.
	 */
	int min_key_size = hcon->hdev->min_enc_key_size;

	/* On FIPS secuwity wevew, key size must be 16 bytes */
	if (hcon->sec_wevew == BT_SECUWITY_FIPS)
		min_key_size = 16;

	wetuwn (!test_bit(HCI_CONN_ENCWYPT, &hcon->fwags) ||
		hcon->enc_key_size >= min_key_size);
}

static void w2cap_do_stawt(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;

	if (conn->hcon->type == WE_WINK) {
		w2cap_we_stawt(chan);
		wetuwn;
	}

	if (!(conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_SENT)) {
		w2cap_wequest_info(conn);
		wetuwn;
	}

	if (!(conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_DONE))
		wetuwn;

	if (!w2cap_chan_check_secuwity(chan, twue) ||
	    !__w2cap_no_conn_pending(chan))
		wetuwn;

	if (w2cap_check_enc_key_size(conn->hcon))
		w2cap_stawt_connection(chan);
	ewse
		__set_chan_timew(chan, W2CAP_DISC_TIMEOUT);
}

static inwine int w2cap_mode_suppowted(__u8 mode, __u32 feat_mask)
{
	u32 wocaw_feat_mask = w2cap_feat_mask;
	if (!disabwe_ewtm)
		wocaw_feat_mask |= W2CAP_FEAT_EWTM | W2CAP_FEAT_STWEAMING;

	switch (mode) {
	case W2CAP_MODE_EWTM:
		wetuwn W2CAP_FEAT_EWTM & feat_mask & wocaw_feat_mask;
	case W2CAP_MODE_STWEAMING:
		wetuwn W2CAP_FEAT_STWEAMING & feat_mask & wocaw_feat_mask;
	defauwt:
		wetuwn 0x00;
	}
}

static void w2cap_send_disconn_weq(stwuct w2cap_chan *chan, int eww)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_disconn_weq weq;

	if (!conn)
		wetuwn;

	if (chan->mode == W2CAP_MODE_EWTM && chan->state == BT_CONNECTED) {
		__cweaw_wetwans_timew(chan);
		__cweaw_monitow_timew(chan);
		__cweaw_ack_timew(chan);
	}

	if (chan->scid == W2CAP_CID_A2MP) {
		w2cap_state_change(chan, BT_DISCONN);
		wetuwn;
	}

	weq.dcid = cpu_to_we16(chan->dcid);
	weq.scid = cpu_to_we16(chan->scid);
	w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_DISCONN_WEQ,
		       sizeof(weq), &weq);

	w2cap_state_change_and_ewwow(chan, BT_DISCONN, eww);
}

/* ---- W2CAP connections ---- */
static void w2cap_conn_stawt(stwuct w2cap_conn *conn)
{
	stwuct w2cap_chan *chan, *tmp;

	BT_DBG("conn %p", conn);

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy_safe(chan, tmp, &conn->chan_w, wist) {
		w2cap_chan_wock(chan);

		if (chan->chan_type != W2CAP_CHAN_CONN_OWIENTED) {
			w2cap_chan_weady(chan);
			w2cap_chan_unwock(chan);
			continue;
		}

		if (chan->state == BT_CONNECT) {
			if (!w2cap_chan_check_secuwity(chan, twue) ||
			    !__w2cap_no_conn_pending(chan)) {
				w2cap_chan_unwock(chan);
				continue;
			}

			if (!w2cap_mode_suppowted(chan->mode, conn->feat_mask)
			    && test_bit(CONF_STATE2_DEVICE,
					&chan->conf_state)) {
				w2cap_chan_cwose(chan, ECONNWESET);
				w2cap_chan_unwock(chan);
				continue;
			}

			if (w2cap_check_enc_key_size(conn->hcon))
				w2cap_stawt_connection(chan);
			ewse
				w2cap_chan_cwose(chan, ECONNWEFUSED);

		} ewse if (chan->state == BT_CONNECT2) {
			stwuct w2cap_conn_wsp wsp;
			chaw buf[128];
			wsp.scid = cpu_to_we16(chan->dcid);
			wsp.dcid = cpu_to_we16(chan->scid);

			if (w2cap_chan_check_secuwity(chan, fawse)) {
				if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags)) {
					wsp.wesuwt = cpu_to_we16(W2CAP_CW_PEND);
					wsp.status = cpu_to_we16(W2CAP_CS_AUTHOW_PEND);
					chan->ops->defew(chan);

				} ewse {
					w2cap_state_change(chan, BT_CONFIG);
					wsp.wesuwt = cpu_to_we16(W2CAP_CW_SUCCESS);
					wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);
				}
			} ewse {
				wsp.wesuwt = cpu_to_we16(W2CAP_CW_PEND);
				wsp.status = cpu_to_we16(W2CAP_CS_AUTHEN_PEND);
			}

			w2cap_send_cmd(conn, chan->ident, W2CAP_CONN_WSP,
				       sizeof(wsp), &wsp);

			if (test_bit(CONF_WEQ_SENT, &chan->conf_state) ||
			    wsp.wesuwt != W2CAP_CW_SUCCESS) {
				w2cap_chan_unwock(chan);
				continue;
			}

			set_bit(CONF_WEQ_SENT, &chan->conf_state);
			w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_CONF_WEQ,
				       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)), buf);
			chan->num_conf_weq++;
		}

		w2cap_chan_unwock(chan);
	}

	mutex_unwock(&conn->chan_wock);
}

static void w2cap_we_conn_weady(stwuct w2cap_conn *conn)
{
	stwuct hci_conn *hcon = conn->hcon;
	stwuct hci_dev *hdev = hcon->hdev;

	BT_DBG("%s conn %p", hdev->name, conn);

	/* Fow outgoing paiwing which doesn't necessawiwy have an
	 * associated socket (e.g. mgmt_paiw_device).
	 */
	if (hcon->out)
		smp_conn_secuwity(hcon, hcon->pending_sec_wevew);

	/* Fow WE pewiphewaw connections, make suwe the connection intewvaw
	 * is in the wange of the minimum and maximum intewvaw that has
	 * been configuwed fow this connection. If not, then twiggew
	 * the connection update pwoceduwe.
	 */
	if (hcon->wowe == HCI_WOWE_SWAVE &&
	    (hcon->we_conn_intewvaw < hcon->we_conn_min_intewvaw ||
	     hcon->we_conn_intewvaw > hcon->we_conn_max_intewvaw)) {
		stwuct w2cap_conn_pawam_update_weq weq;

		weq.min = cpu_to_we16(hcon->we_conn_min_intewvaw);
		weq.max = cpu_to_we16(hcon->we_conn_max_intewvaw);
		weq.watency = cpu_to_we16(hcon->we_conn_watency);
		weq.to_muwtipwiew = cpu_to_we16(hcon->we_supv_timeout);

		w2cap_send_cmd(conn, w2cap_get_ident(conn),
			       W2CAP_CONN_PAWAM_UPDATE_WEQ, sizeof(weq), &weq);
	}
}

static void w2cap_conn_weady(stwuct w2cap_conn *conn)
{
	stwuct w2cap_chan *chan;
	stwuct hci_conn *hcon = conn->hcon;

	BT_DBG("conn %p", conn);

	if (hcon->type == ACW_WINK)
		w2cap_wequest_info(conn);

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {

		w2cap_chan_wock(chan);

		if (chan->scid == W2CAP_CID_A2MP) {
			w2cap_chan_unwock(chan);
			continue;
		}

		if (hcon->type == WE_WINK) {
			w2cap_we_stawt(chan);
		} ewse if (chan->chan_type != W2CAP_CHAN_CONN_OWIENTED) {
			if (conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_DONE)
				w2cap_chan_weady(chan);
		} ewse if (chan->state == BT_CONNECT) {
			w2cap_do_stawt(chan);
		}

		w2cap_chan_unwock(chan);
	}

	mutex_unwock(&conn->chan_wock);

	if (hcon->type == WE_WINK)
		w2cap_we_conn_weady(conn);

	queue_wowk(hcon->hdev->wowkqueue, &conn->pending_wx_wowk);
}

/* Notify sockets that we cannot guawanty wewiabiwity anymowe */
static void w2cap_conn_unwewiabwe(stwuct w2cap_conn *conn, int eww)
{
	stwuct w2cap_chan *chan;

	BT_DBG("conn %p", conn);

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {
		if (test_bit(FWAG_FOWCE_WEWIABWE, &chan->fwags))
			w2cap_chan_set_eww(chan, eww);
	}

	mutex_unwock(&conn->chan_wock);
}

static void w2cap_info_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_conn *conn = containew_of(wowk, stwuct w2cap_conn,
					       info_timew.wowk);

	conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_DONE;
	conn->info_ident = 0;

	w2cap_conn_stawt(conn);
}

/*
 * w2cap_usew
 * Extewnaw moduwes can wegistew w2cap_usew objects on w2cap_conn. The ->pwobe
 * cawwback is cawwed duwing wegistwation. The ->wemove cawwback is cawwed
 * duwing unwegistwation.
 * An w2cap_usew object can eithew be expwicitwy unwegistewed ow when the
 * undewwying w2cap_conn object is deweted. This guawantees that w2cap->hcon,
 * w2cap->hchan, .. awe vawid as wong as the wemove cawwback hasn't been cawwed.
 * Extewnaw moduwes must own a wefewence to the w2cap_conn object if they intend
 * to caww w2cap_unwegistew_usew(). The w2cap_conn object might get destwoyed at
 * any time if they don't.
 */

int w2cap_wegistew_usew(stwuct w2cap_conn *conn, stwuct w2cap_usew *usew)
{
	stwuct hci_dev *hdev = conn->hcon->hdev;
	int wet;

	/* We need to check whethew w2cap_conn is wegistewed. If it is not, we
	 * must not wegistew the w2cap_usew. w2cap_conn_dew() is unwegistews
	 * w2cap_conn objects, but doesn't pwovide its own wocking. Instead, it
	 * wewies on the pawent hci_conn object to be wocked. This itsewf wewies
	 * on the hci_dev object to be wocked. So we must wock the hci device
	 * hewe, too. */

	hci_dev_wock(hdev);

	if (!wist_empty(&usew->wist)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	/* conn->hchan is NUWW aftew w2cap_conn_dew() was cawwed */
	if (!conn->hchan) {
		wet = -ENODEV;
		goto out_unwock;
	}

	wet = usew->pwobe(conn, usew);
	if (wet)
		goto out_unwock;

	wist_add(&usew->wist, &conn->usews);
	wet = 0;

out_unwock:
	hci_dev_unwock(hdev);
	wetuwn wet;
}
EXPOWT_SYMBOW(w2cap_wegistew_usew);

void w2cap_unwegistew_usew(stwuct w2cap_conn *conn, stwuct w2cap_usew *usew)
{
	stwuct hci_dev *hdev = conn->hcon->hdev;

	hci_dev_wock(hdev);

	if (wist_empty(&usew->wist))
		goto out_unwock;

	wist_dew_init(&usew->wist);
	usew->wemove(conn, usew);

out_unwock:
	hci_dev_unwock(hdev);
}
EXPOWT_SYMBOW(w2cap_unwegistew_usew);

static void w2cap_unwegistew_aww_usews(stwuct w2cap_conn *conn)
{
	stwuct w2cap_usew *usew;

	whiwe (!wist_empty(&conn->usews)) {
		usew = wist_fiwst_entwy(&conn->usews, stwuct w2cap_usew, wist);
		wist_dew_init(&usew->wist);
		usew->wemove(conn, usew);
	}
}

static void w2cap_conn_dew(stwuct hci_conn *hcon, int eww)
{
	stwuct w2cap_conn *conn = hcon->w2cap_data;
	stwuct w2cap_chan *chan, *w;

	if (!conn)
		wetuwn;

	BT_DBG("hcon %p conn %p, eww %d", hcon, conn, eww);

	kfwee_skb(conn->wx_skb);

	skb_queue_puwge(&conn->pending_wx);

	/* We can not caww fwush_wowk(&conn->pending_wx_wowk) hewe since we
	 * might bwock if we awe wunning on a wowkew fwom the same wowkqueue
	 * pending_wx_wowk is waiting on.
	 */
	if (wowk_pending(&conn->pending_wx_wowk))
		cancew_wowk_sync(&conn->pending_wx_wowk);

	cancew_dewayed_wowk_sync(&conn->id_addw_timew);

	w2cap_unwegistew_aww_usews(conn);

	/* Fowce the connection to be immediatewy dwopped */
	hcon->disc_timeout = 0;

	mutex_wock(&conn->chan_wock);

	/* Kiww channews */
	wist_fow_each_entwy_safe(chan, w, &conn->chan_w, wist) {
		w2cap_chan_howd(chan);
		w2cap_chan_wock(chan);

		w2cap_chan_dew(chan, eww);

		chan->ops->cwose(chan);

		w2cap_chan_unwock(chan);
		w2cap_chan_put(chan);
	}

	mutex_unwock(&conn->chan_wock);

	hci_chan_dew(conn->hchan);

	if (conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_SENT)
		cancew_dewayed_wowk_sync(&conn->info_timew);

	hcon->w2cap_data = NUWW;
	conn->hchan = NUWW;
	w2cap_conn_put(conn);
}

static void w2cap_conn_fwee(stwuct kwef *wef)
{
	stwuct w2cap_conn *conn = containew_of(wef, stwuct w2cap_conn, wef);

	hci_conn_put(conn->hcon);
	kfwee(conn);
}

stwuct w2cap_conn *w2cap_conn_get(stwuct w2cap_conn *conn)
{
	kwef_get(&conn->wef);
	wetuwn conn;
}
EXPOWT_SYMBOW(w2cap_conn_get);

void w2cap_conn_put(stwuct w2cap_conn *conn)
{
	kwef_put(&conn->wef, w2cap_conn_fwee);
}
EXPOWT_SYMBOW(w2cap_conn_put);

/* ---- Socket intewface ---- */

/* Find socket with psm and souwce / destination bdaddw.
 * Wetuwns cwosest match.
 */
static stwuct w2cap_chan *w2cap_gwobaw_chan_by_psm(int state, __we16 psm,
						   bdaddw_t *swc,
						   bdaddw_t *dst,
						   u8 wink_type)
{
	stwuct w2cap_chan *c, *tmp, *c1 = NUWW;

	wead_wock(&chan_wist_wock);

	wist_fow_each_entwy_safe(c, tmp, &chan_wist, gwobaw_w) {
		if (state && c->state != state)
			continue;

		if (wink_type == ACW_WINK && c->swc_type != BDADDW_BWEDW)
			continue;

		if (wink_type == WE_WINK && c->swc_type == BDADDW_BWEDW)
			continue;

		if (c->chan_type != W2CAP_CHAN_FIXED && c->psm == psm) {
			int swc_match, dst_match;
			int swc_any, dst_any;

			/* Exact match. */
			swc_match = !bacmp(&c->swc, swc);
			dst_match = !bacmp(&c->dst, dst);
			if (swc_match && dst_match) {
				if (!w2cap_chan_howd_unwess_zewo(c))
					continue;

				wead_unwock(&chan_wist_wock);
				wetuwn c;
			}

			/* Cwosest match */
			swc_any = !bacmp(&c->swc, BDADDW_ANY);
			dst_any = !bacmp(&c->dst, BDADDW_ANY);
			if ((swc_match && dst_any) || (swc_any && dst_match) ||
			    (swc_any && dst_any))
				c1 = c;
		}
	}

	if (c1)
		c1 = w2cap_chan_howd_unwess_zewo(c1);

	wead_unwock(&chan_wist_wock);

	wetuwn c1;
}

static void w2cap_monitow_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_chan *chan = containew_of(wowk, stwuct w2cap_chan,
					       monitow_timew.wowk);

	BT_DBG("chan %p", chan);

	w2cap_chan_wock(chan);

	if (!chan->conn) {
		w2cap_chan_unwock(chan);
		w2cap_chan_put(chan);
		wetuwn;
	}

	w2cap_tx(chan, NUWW, NUWW, W2CAP_EV_MONITOW_TO);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

static void w2cap_wetwans_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_chan *chan = containew_of(wowk, stwuct w2cap_chan,
					       wetwans_timew.wowk);

	BT_DBG("chan %p", chan);

	w2cap_chan_wock(chan);

	if (!chan->conn) {
		w2cap_chan_unwock(chan);
		w2cap_chan_put(chan);
		wetuwn;
	}

	w2cap_tx(chan, NUWW, NUWW, W2CAP_EV_WETWANS_TO);
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

static void w2cap_stweaming_send(stwuct w2cap_chan *chan,
				 stwuct sk_buff_head *skbs)
{
	stwuct sk_buff *skb;
	stwuct w2cap_ctww *contwow;

	BT_DBG("chan %p, skbs %p", chan, skbs);

	if (__chan_is_moving(chan))
		wetuwn;

	skb_queue_spwice_taiw_init(skbs, &chan->tx_q);

	whiwe (!skb_queue_empty(&chan->tx_q)) {

		skb = skb_dequeue(&chan->tx_q);

		bt_cb(skb)->w2cap.wetwies = 1;
		contwow = &bt_cb(skb)->w2cap;

		contwow->weqseq = 0;
		contwow->txseq = chan->next_tx_seq;

		__pack_contwow(chan, contwow, skb);

		if (chan->fcs == W2CAP_FCS_CWC16) {
			u16 fcs = cwc16(0, (u8 *) skb->data, skb->wen);
			put_unawigned_we16(fcs, skb_put(skb, W2CAP_FCS_SIZE));
		}

		w2cap_do_send(chan, skb);

		BT_DBG("Sent txseq %u", contwow->txseq);

		chan->next_tx_seq = __next_seq(chan, chan->next_tx_seq);
		chan->fwames_sent++;
	}
}

static int w2cap_ewtm_send(stwuct w2cap_chan *chan)
{
	stwuct sk_buff *skb, *tx_skb;
	stwuct w2cap_ctww *contwow;
	int sent = 0;

	BT_DBG("chan %p", chan);

	if (chan->state != BT_CONNECTED)
		wetuwn -ENOTCONN;

	if (test_bit(CONN_WEMOTE_BUSY, &chan->conn_state))
		wetuwn 0;

	if (__chan_is_moving(chan))
		wetuwn 0;

	whiwe (chan->tx_send_head &&
	       chan->unacked_fwames < chan->wemote_tx_win &&
	       chan->tx_state == W2CAP_TX_STATE_XMIT) {

		skb = chan->tx_send_head;

		bt_cb(skb)->w2cap.wetwies = 1;
		contwow = &bt_cb(skb)->w2cap;

		if (test_and_cweaw_bit(CONN_SEND_FBIT, &chan->conn_state))
			contwow->finaw = 1;

		contwow->weqseq = chan->buffew_seq;
		chan->wast_acked_seq = chan->buffew_seq;
		contwow->txseq = chan->next_tx_seq;

		__pack_contwow(chan, contwow, skb);

		if (chan->fcs == W2CAP_FCS_CWC16) {
			u16 fcs = cwc16(0, (u8 *) skb->data, skb->wen);
			put_unawigned_we16(fcs, skb_put(skb, W2CAP_FCS_SIZE));
		}

		/* Cwone aftew data has been modified. Data is assumed to be
		   wead-onwy (fow wocking puwposes) on cwoned sk_buffs.
		 */
		tx_skb = skb_cwone(skb, GFP_KEWNEW);

		if (!tx_skb)
			bweak;

		__set_wetwans_timew(chan);

		chan->next_tx_seq = __next_seq(chan, chan->next_tx_seq);
		chan->unacked_fwames++;
		chan->fwames_sent++;
		sent++;

		if (skb_queue_is_wast(&chan->tx_q, skb))
			chan->tx_send_head = NUWW;
		ewse
			chan->tx_send_head = skb_queue_next(&chan->tx_q, skb);

		w2cap_do_send(chan, tx_skb);
		BT_DBG("Sent txseq %u", contwow->txseq);
	}

	BT_DBG("Sent %d, %u unacked, %u in EWTM queue", sent,
	       chan->unacked_fwames, skb_queue_wen(&chan->tx_q));

	wetuwn sent;
}

static void w2cap_ewtm_wesend(stwuct w2cap_chan *chan)
{
	stwuct w2cap_ctww contwow;
	stwuct sk_buff *skb;
	stwuct sk_buff *tx_skb;
	u16 seq;

	BT_DBG("chan %p", chan);

	if (test_bit(CONN_WEMOTE_BUSY, &chan->conn_state))
		wetuwn;

	if (__chan_is_moving(chan))
		wetuwn;

	whiwe (chan->wetwans_wist.head != W2CAP_SEQ_WIST_CWEAW) {
		seq = w2cap_seq_wist_pop(&chan->wetwans_wist);

		skb = w2cap_ewtm_seq_in_queue(&chan->tx_q, seq);
		if (!skb) {
			BT_DBG("Ewwow: Can't wetwansmit seq %d, fwame missing",
			       seq);
			continue;
		}

		bt_cb(skb)->w2cap.wetwies++;
		contwow = bt_cb(skb)->w2cap;

		if (chan->max_tx != 0 &&
		    bt_cb(skb)->w2cap.wetwies > chan->max_tx) {
			BT_DBG("Wetwy wimit exceeded (%d)", chan->max_tx);
			w2cap_send_disconn_weq(chan, ECONNWESET);
			w2cap_seq_wist_cweaw(&chan->wetwans_wist);
			bweak;
		}

		contwow.weqseq = chan->buffew_seq;
		if (test_and_cweaw_bit(CONN_SEND_FBIT, &chan->conn_state))
			contwow.finaw = 1;
		ewse
			contwow.finaw = 0;

		if (skb_cwoned(skb)) {
			/* Cwoned sk_buffs awe wead-onwy, so we need a
			 * wwiteabwe copy
			 */
			tx_skb = skb_copy(skb, GFP_KEWNEW);
		} ewse {
			tx_skb = skb_cwone(skb, GFP_KEWNEW);
		}

		if (!tx_skb) {
			w2cap_seq_wist_cweaw(&chan->wetwans_wist);
			bweak;
		}

		/* Update skb contents */
		if (test_bit(FWAG_EXT_CTWW, &chan->fwags)) {
			put_unawigned_we32(__pack_extended_contwow(&contwow),
					   tx_skb->data + W2CAP_HDW_SIZE);
		} ewse {
			put_unawigned_we16(__pack_enhanced_contwow(&contwow),
					   tx_skb->data + W2CAP_HDW_SIZE);
		}

		/* Update FCS */
		if (chan->fcs == W2CAP_FCS_CWC16) {
			u16 fcs = cwc16(0, (u8 *) tx_skb->data,
					tx_skb->wen - W2CAP_FCS_SIZE);
			put_unawigned_we16(fcs, skb_taiw_pointew(tx_skb) -
						W2CAP_FCS_SIZE);
		}

		w2cap_do_send(chan, tx_skb);

		BT_DBG("Wesent txseq %d", contwow.txseq);

		chan->wast_acked_seq = chan->buffew_seq;
	}
}

static void w2cap_wetwansmit(stwuct w2cap_chan *chan,
			     stwuct w2cap_ctww *contwow)
{
	BT_DBG("chan %p, contwow %p", chan, contwow);

	w2cap_seq_wist_append(&chan->wetwans_wist, contwow->weqseq);
	w2cap_ewtm_wesend(chan);
}

static void w2cap_wetwansmit_aww(stwuct w2cap_chan *chan,
				 stwuct w2cap_ctww *contwow)
{
	stwuct sk_buff *skb;

	BT_DBG("chan %p, contwow %p", chan, contwow);

	if (contwow->poww)
		set_bit(CONN_SEND_FBIT, &chan->conn_state);

	w2cap_seq_wist_cweaw(&chan->wetwans_wist);

	if (test_bit(CONN_WEMOTE_BUSY, &chan->conn_state))
		wetuwn;

	if (chan->unacked_fwames) {
		skb_queue_wawk(&chan->tx_q, skb) {
			if (bt_cb(skb)->w2cap.txseq == contwow->weqseq ||
			    skb == chan->tx_send_head)
				bweak;
		}

		skb_queue_wawk_fwom(&chan->tx_q, skb) {
			if (skb == chan->tx_send_head)
				bweak;

			w2cap_seq_wist_append(&chan->wetwans_wist,
					      bt_cb(skb)->w2cap.txseq);
		}

		w2cap_ewtm_wesend(chan);
	}
}

static void w2cap_send_ack(stwuct w2cap_chan *chan)
{
	stwuct w2cap_ctww contwow;
	u16 fwames_to_ack = __seq_offset(chan, chan->buffew_seq,
					 chan->wast_acked_seq);
	int thweshowd;

	BT_DBG("chan %p wast_acked_seq %d buffew_seq %d",
	       chan, chan->wast_acked_seq, chan->buffew_seq);

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;

	if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state) &&
	    chan->wx_state == W2CAP_WX_STATE_WECV) {
		__cweaw_ack_timew(chan);
		contwow.supew = W2CAP_SUPEW_WNW;
		contwow.weqseq = chan->buffew_seq;
		w2cap_send_sfwame(chan, &contwow);
	} ewse {
		if (!test_bit(CONN_WEMOTE_BUSY, &chan->conn_state)) {
			w2cap_ewtm_send(chan);
			/* If any i-fwames wewe sent, they incwuded an ack */
			if (chan->buffew_seq == chan->wast_acked_seq)
				fwames_to_ack = 0;
		}

		/* Ack now if the window is 3/4ths fuww.
		 * Cawcuwate without muw ow div
		 */
		thweshowd = chan->ack_win;
		thweshowd += thweshowd << 1;
		thweshowd >>= 2;

		BT_DBG("fwames_to_ack %u, thweshowd %d", fwames_to_ack,
		       thweshowd);

		if (fwames_to_ack >= thweshowd) {
			__cweaw_ack_timew(chan);
			contwow.supew = W2CAP_SUPEW_WW;
			contwow.weqseq = chan->buffew_seq;
			w2cap_send_sfwame(chan, &contwow);
			fwames_to_ack = 0;
		}

		if (fwames_to_ack)
			__set_ack_timew(chan);
	}
}

static inwine int w2cap_skbuff_fwomiovec(stwuct w2cap_chan *chan,
					 stwuct msghdw *msg, int wen,
					 int count, stwuct sk_buff *skb)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct sk_buff **fwag;
	int sent = 0;

	if (!copy_fwom_itew_fuww(skb_put(skb, count), count, &msg->msg_itew))
		wetuwn -EFAUWT;

	sent += count;
	wen  -= count;

	/* Continuation fwagments (no W2CAP headew) */
	fwag = &skb_shinfo(skb)->fwag_wist;
	whiwe (wen) {
		stwuct sk_buff *tmp;

		count = min_t(unsigned int, conn->mtu, wen);

		tmp = chan->ops->awwoc_skb(chan, 0, count,
					   msg->msg_fwags & MSG_DONTWAIT);
		if (IS_EWW(tmp))
			wetuwn PTW_EWW(tmp);

		*fwag = tmp;

		if (!copy_fwom_itew_fuww(skb_put(*fwag, count), count,
				   &msg->msg_itew))
			wetuwn -EFAUWT;

		sent += count;
		wen  -= count;

		skb->wen += (*fwag)->wen;
		skb->data_wen += (*fwag)->wen;

		fwag = &(*fwag)->next;
	}

	wetuwn sent;
}

static stwuct sk_buff *w2cap_cweate_connwess_pdu(stwuct w2cap_chan *chan,
						 stwuct msghdw *msg, size_t wen)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct sk_buff *skb;
	int eww, count, hwen = W2CAP_HDW_SIZE + W2CAP_PSMWEN_SIZE;
	stwuct w2cap_hdw *wh;

	BT_DBG("chan %p psm 0x%2.2x wen %zu", chan,
	       __we16_to_cpu(chan->psm), wen);

	count = min_t(unsigned int, (conn->mtu - hwen), wen);

	skb = chan->ops->awwoc_skb(chan, hwen, count,
				   msg->msg_fwags & MSG_DONTWAIT);
	if (IS_EWW(skb))
		wetuwn skb;

	/* Cweate W2CAP headew */
	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->cid = cpu_to_we16(chan->dcid);
	wh->wen = cpu_to_we16(wen + W2CAP_PSMWEN_SIZE);
	put_unawigned(chan->psm, (__we16 *) skb_put(skb, W2CAP_PSMWEN_SIZE));

	eww = w2cap_skbuff_fwomiovec(chan, msg, wen, count, skb);
	if (unwikewy(eww < 0)) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}
	wetuwn skb;
}

static stwuct sk_buff *w2cap_cweate_basic_pdu(stwuct w2cap_chan *chan,
					      stwuct msghdw *msg, size_t wen)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct sk_buff *skb;
	int eww, count;
	stwuct w2cap_hdw *wh;

	BT_DBG("chan %p wen %zu", chan, wen);

	count = min_t(unsigned int, (conn->mtu - W2CAP_HDW_SIZE), wen);

	skb = chan->ops->awwoc_skb(chan, W2CAP_HDW_SIZE, count,
				   msg->msg_fwags & MSG_DONTWAIT);
	if (IS_EWW(skb))
		wetuwn skb;

	/* Cweate W2CAP headew */
	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->cid = cpu_to_we16(chan->dcid);
	wh->wen = cpu_to_we16(wen);

	eww = w2cap_skbuff_fwomiovec(chan, msg, wen, count, skb);
	if (unwikewy(eww < 0)) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}
	wetuwn skb;
}

static stwuct sk_buff *w2cap_cweate_ifwame_pdu(stwuct w2cap_chan *chan,
					       stwuct msghdw *msg, size_t wen,
					       u16 sduwen)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct sk_buff *skb;
	int eww, count, hwen;
	stwuct w2cap_hdw *wh;

	BT_DBG("chan %p wen %zu", chan, wen);

	if (!conn)
		wetuwn EWW_PTW(-ENOTCONN);

	hwen = __ewtm_hdw_size(chan);

	if (sduwen)
		hwen += W2CAP_SDUWEN_SIZE;

	if (chan->fcs == W2CAP_FCS_CWC16)
		hwen += W2CAP_FCS_SIZE;

	count = min_t(unsigned int, (conn->mtu - hwen), wen);

	skb = chan->ops->awwoc_skb(chan, hwen, count,
				   msg->msg_fwags & MSG_DONTWAIT);
	if (IS_EWW(skb))
		wetuwn skb;

	/* Cweate W2CAP headew */
	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->cid = cpu_to_we16(chan->dcid);
	wh->wen = cpu_to_we16(wen + (hwen - W2CAP_HDW_SIZE));

	/* Contwow headew is popuwated watew */
	if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
		put_unawigned_we32(0, skb_put(skb, W2CAP_EXT_CTWW_SIZE));
	ewse
		put_unawigned_we16(0, skb_put(skb, W2CAP_ENH_CTWW_SIZE));

	if (sduwen)
		put_unawigned_we16(sduwen, skb_put(skb, W2CAP_SDUWEN_SIZE));

	eww = w2cap_skbuff_fwomiovec(chan, msg, wen, count, skb);
	if (unwikewy(eww < 0)) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}

	bt_cb(skb)->w2cap.fcs = chan->fcs;
	bt_cb(skb)->w2cap.wetwies = 0;
	wetuwn skb;
}

static int w2cap_segment_sdu(stwuct w2cap_chan *chan,
			     stwuct sk_buff_head *seg_queue,
			     stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *skb;
	u16 sdu_wen;
	size_t pdu_wen;
	u8 saw;

	BT_DBG("chan %p, msg %p, wen %zu", chan, msg, wen);

	/* It is cwiticaw that EWTM PDUs fit in a singwe HCI fwagment,
	 * so fwagmented skbs awe not used.  The HCI wayew's handwing
	 * of fwagmented skbs is not compatibwe with EWTM's queueing.
	 */

	/* PDU size is dewived fwom the HCI MTU */
	pdu_wen = chan->conn->mtu;

	/* Constwain PDU size fow BW/EDW connections */
	if (!chan->hs_hcon)
		pdu_wen = min_t(size_t, pdu_wen, W2CAP_BWEDW_MAX_PAYWOAD);

	/* Adjust fow wawgest possibwe W2CAP ovewhead. */
	if (chan->fcs)
		pdu_wen -= W2CAP_FCS_SIZE;

	pdu_wen -= __ewtm_hdw_size(chan);

	/* Wemote device may have wequested smawwew PDUs */
	pdu_wen = min_t(size_t, pdu_wen, chan->wemote_mps);

	if (wen <= pdu_wen) {
		saw = W2CAP_SAW_UNSEGMENTED;
		sdu_wen = 0;
		pdu_wen = wen;
	} ewse {
		saw = W2CAP_SAW_STAWT;
		sdu_wen = wen;
	}

	whiwe (wen > 0) {
		skb = w2cap_cweate_ifwame_pdu(chan, msg, pdu_wen, sdu_wen);

		if (IS_EWW(skb)) {
			__skb_queue_puwge(seg_queue);
			wetuwn PTW_EWW(skb);
		}

		bt_cb(skb)->w2cap.saw = saw;
		__skb_queue_taiw(seg_queue, skb);

		wen -= pdu_wen;
		if (sdu_wen)
			sdu_wen = 0;

		if (wen <= pdu_wen) {
			saw = W2CAP_SAW_END;
			pdu_wen = wen;
		} ewse {
			saw = W2CAP_SAW_CONTINUE;
		}
	}

	wetuwn 0;
}

static stwuct sk_buff *w2cap_cweate_we_fwowctw_pdu(stwuct w2cap_chan *chan,
						   stwuct msghdw *msg,
						   size_t wen, u16 sduwen)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct sk_buff *skb;
	int eww, count, hwen;
	stwuct w2cap_hdw *wh;

	BT_DBG("chan %p wen %zu", chan, wen);

	if (!conn)
		wetuwn EWW_PTW(-ENOTCONN);

	hwen = W2CAP_HDW_SIZE;

	if (sduwen)
		hwen += W2CAP_SDUWEN_SIZE;

	count = min_t(unsigned int, (conn->mtu - hwen), wen);

	skb = chan->ops->awwoc_skb(chan, hwen, count,
				   msg->msg_fwags & MSG_DONTWAIT);
	if (IS_EWW(skb))
		wetuwn skb;

	/* Cweate W2CAP headew */
	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->cid = cpu_to_we16(chan->dcid);
	wh->wen = cpu_to_we16(wen + (hwen - W2CAP_HDW_SIZE));

	if (sduwen)
		put_unawigned_we16(sduwen, skb_put(skb, W2CAP_SDUWEN_SIZE));

	eww = w2cap_skbuff_fwomiovec(chan, msg, wen, count, skb);
	if (unwikewy(eww < 0)) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(eww);
	}

	wetuwn skb;
}

static int w2cap_segment_we_sdu(stwuct w2cap_chan *chan,
				stwuct sk_buff_head *seg_queue,
				stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *skb;
	size_t pdu_wen;
	u16 sdu_wen;

	BT_DBG("chan %p, msg %p, wen %zu", chan, msg, wen);

	sdu_wen = wen;
	pdu_wen = chan->wemote_mps - W2CAP_SDUWEN_SIZE;

	whiwe (wen > 0) {
		if (wen <= pdu_wen)
			pdu_wen = wen;

		skb = w2cap_cweate_we_fwowctw_pdu(chan, msg, pdu_wen, sdu_wen);
		if (IS_EWW(skb)) {
			__skb_queue_puwge(seg_queue);
			wetuwn PTW_EWW(skb);
		}

		__skb_queue_taiw(seg_queue, skb);

		wen -= pdu_wen;

		if (sdu_wen) {
			sdu_wen = 0;
			pdu_wen += W2CAP_SDUWEN_SIZE;
		}
	}

	wetuwn 0;
}

static void w2cap_we_fwowctw_send(stwuct w2cap_chan *chan)
{
	int sent = 0;

	BT_DBG("chan %p", chan);

	whiwe (chan->tx_cwedits && !skb_queue_empty(&chan->tx_q)) {
		w2cap_do_send(chan, skb_dequeue(&chan->tx_q));
		chan->tx_cwedits--;
		sent++;
	}

	BT_DBG("Sent %d cwedits %u queued %u", sent, chan->tx_cwedits,
	       skb_queue_wen(&chan->tx_q));
}

int w2cap_chan_send(stwuct w2cap_chan *chan, stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *skb;
	int eww;
	stwuct sk_buff_head seg_queue;

	if (!chan->conn)
		wetuwn -ENOTCONN;

	/* Connectionwess channew */
	if (chan->chan_type == W2CAP_CHAN_CONN_WESS) {
		skb = w2cap_cweate_connwess_pdu(chan, msg, wen);
		if (IS_EWW(skb))
			wetuwn PTW_EWW(skb);

		w2cap_do_send(chan, skb);
		wetuwn wen;
	}

	switch (chan->mode) {
	case W2CAP_MODE_WE_FWOWCTW:
	case W2CAP_MODE_EXT_FWOWCTW:
		/* Check outgoing MTU */
		if (wen > chan->omtu)
			wetuwn -EMSGSIZE;

		__skb_queue_head_init(&seg_queue);

		eww = w2cap_segment_we_sdu(chan, &seg_queue, msg, wen);

		if (chan->state != BT_CONNECTED) {
			__skb_queue_puwge(&seg_queue);
			eww = -ENOTCONN;
		}

		if (eww)
			wetuwn eww;

		skb_queue_spwice_taiw_init(&seg_queue, &chan->tx_q);

		w2cap_we_fwowctw_send(chan);

		if (!chan->tx_cwedits)
			chan->ops->suspend(chan);

		eww = wen;

		bweak;

	case W2CAP_MODE_BASIC:
		/* Check outgoing MTU */
		if (wen > chan->omtu)
			wetuwn -EMSGSIZE;

		/* Cweate a basic PDU */
		skb = w2cap_cweate_basic_pdu(chan, msg, wen);
		if (IS_EWW(skb))
			wetuwn PTW_EWW(skb);

		w2cap_do_send(chan, skb);
		eww = wen;
		bweak;

	case W2CAP_MODE_EWTM:
	case W2CAP_MODE_STWEAMING:
		/* Check outgoing MTU */
		if (wen > chan->omtu) {
			eww = -EMSGSIZE;
			bweak;
		}

		__skb_queue_head_init(&seg_queue);

		/* Do segmentation befowe cawwing in to the state machine,
		 * since it's possibwe to bwock whiwe waiting fow memowy
		 * awwocation.
		 */
		eww = w2cap_segment_sdu(chan, &seg_queue, msg, wen);

		if (eww)
			bweak;

		if (chan->mode == W2CAP_MODE_EWTM)
			w2cap_tx(chan, NUWW, &seg_queue, W2CAP_EV_DATA_WEQUEST);
		ewse
			w2cap_stweaming_send(chan, &seg_queue);

		eww = wen;

		/* If the skbs wewe not queued fow sending, they'ww stiww be in
		 * seg_queue and need to be puwged.
		 */
		__skb_queue_puwge(&seg_queue);
		bweak;

	defauwt:
		BT_DBG("bad state %1.1x", chan->mode);
		eww = -EBADFD;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(w2cap_chan_send);

static void w2cap_send_swej(stwuct w2cap_chan *chan, u16 txseq)
{
	stwuct w2cap_ctww contwow;
	u16 seq;

	BT_DBG("chan %p, txseq %u", chan, txseq);

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;
	contwow.supew = W2CAP_SUPEW_SWEJ;

	fow (seq = chan->expected_tx_seq; seq != txseq;
	     seq = __next_seq(chan, seq)) {
		if (!w2cap_ewtm_seq_in_queue(&chan->swej_q, seq)) {
			contwow.weqseq = seq;
			w2cap_send_sfwame(chan, &contwow);
			w2cap_seq_wist_append(&chan->swej_wist, seq);
		}
	}

	chan->expected_tx_seq = __next_seq(chan, txseq);
}

static void w2cap_send_swej_taiw(stwuct w2cap_chan *chan)
{
	stwuct w2cap_ctww contwow;

	BT_DBG("chan %p", chan);

	if (chan->swej_wist.taiw == W2CAP_SEQ_WIST_CWEAW)
		wetuwn;

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;
	contwow.supew = W2CAP_SUPEW_SWEJ;
	contwow.weqseq = chan->swej_wist.taiw;
	w2cap_send_sfwame(chan, &contwow);
}

static void w2cap_send_swej_wist(stwuct w2cap_chan *chan, u16 txseq)
{
	stwuct w2cap_ctww contwow;
	u16 initiaw_head;
	u16 seq;

	BT_DBG("chan %p, txseq %u", chan, txseq);

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;
	contwow.supew = W2CAP_SUPEW_SWEJ;

	/* Captuwe initiaw wist head to awwow onwy one pass thwough the wist. */
	initiaw_head = chan->swej_wist.head;

	do {
		seq = w2cap_seq_wist_pop(&chan->swej_wist);
		if (seq == txseq || seq == W2CAP_SEQ_WIST_CWEAW)
			bweak;

		contwow.weqseq = seq;
		w2cap_send_sfwame(chan, &contwow);
		w2cap_seq_wist_append(&chan->swej_wist, seq);
	} whiwe (chan->swej_wist.head != initiaw_head);
}

static void w2cap_pwocess_weqseq(stwuct w2cap_chan *chan, u16 weqseq)
{
	stwuct sk_buff *acked_skb;
	u16 ackseq;

	BT_DBG("chan %p, weqseq %u", chan, weqseq);

	if (chan->unacked_fwames == 0 || weqseq == chan->expected_ack_seq)
		wetuwn;

	BT_DBG("expected_ack_seq %u, unacked_fwames %u",
	       chan->expected_ack_seq, chan->unacked_fwames);

	fow (ackseq = chan->expected_ack_seq; ackseq != weqseq;
	     ackseq = __next_seq(chan, ackseq)) {

		acked_skb = w2cap_ewtm_seq_in_queue(&chan->tx_q, ackseq);
		if (acked_skb) {
			skb_unwink(acked_skb, &chan->tx_q);
			kfwee_skb(acked_skb);
			chan->unacked_fwames--;
		}
	}

	chan->expected_ack_seq = weqseq;

	if (chan->unacked_fwames == 0)
		__cweaw_wetwans_timew(chan);

	BT_DBG("unacked_fwames %u", chan->unacked_fwames);
}

static void w2cap_abowt_wx_swej_sent(stwuct w2cap_chan *chan)
{
	BT_DBG("chan %p", chan);

	chan->expected_tx_seq = chan->buffew_seq;
	w2cap_seq_wist_cweaw(&chan->swej_wist);
	skb_queue_puwge(&chan->swej_q);
	chan->wx_state = W2CAP_WX_STATE_WECV;
}

static void w2cap_tx_state_xmit(stwuct w2cap_chan *chan,
				stwuct w2cap_ctww *contwow,
				stwuct sk_buff_head *skbs, u8 event)
{
	BT_DBG("chan %p, contwow %p, skbs %p, event %d", chan, contwow, skbs,
	       event);

	switch (event) {
	case W2CAP_EV_DATA_WEQUEST:
		if (chan->tx_send_head == NUWW)
			chan->tx_send_head = skb_peek(skbs);

		skb_queue_spwice_taiw_init(skbs, &chan->tx_q);
		w2cap_ewtm_send(chan);
		bweak;
	case W2CAP_EV_WOCAW_BUSY_DETECTED:
		BT_DBG("Entew WOCAW_BUSY");
		set_bit(CONN_WOCAW_BUSY, &chan->conn_state);

		if (chan->wx_state == W2CAP_WX_STATE_SWEJ_SENT) {
			/* The SWEJ_SENT state must be abowted if we awe to
			 * entew the WOCAW_BUSY state.
			 */
			w2cap_abowt_wx_swej_sent(chan);
		}

		w2cap_send_ack(chan);

		bweak;
	case W2CAP_EV_WOCAW_BUSY_CWEAW:
		BT_DBG("Exit WOCAW_BUSY");
		cweaw_bit(CONN_WOCAW_BUSY, &chan->conn_state);

		if (test_bit(CONN_WNW_SENT, &chan->conn_state)) {
			stwuct w2cap_ctww wocaw_contwow;

			memset(&wocaw_contwow, 0, sizeof(wocaw_contwow));
			wocaw_contwow.sfwame = 1;
			wocaw_contwow.supew = W2CAP_SUPEW_WW;
			wocaw_contwow.poww = 1;
			wocaw_contwow.weqseq = chan->buffew_seq;
			w2cap_send_sfwame(chan, &wocaw_contwow);

			chan->wetwy_count = 1;
			__set_monitow_timew(chan);
			chan->tx_state = W2CAP_TX_STATE_WAIT_F;
		}
		bweak;
	case W2CAP_EV_WECV_WEQSEQ_AND_FBIT:
		w2cap_pwocess_weqseq(chan, contwow->weqseq);
		bweak;
	case W2CAP_EV_EXPWICIT_POWW:
		w2cap_send_ww_ow_wnw(chan, 1);
		chan->wetwy_count = 1;
		__set_monitow_timew(chan);
		__cweaw_ack_timew(chan);
		chan->tx_state = W2CAP_TX_STATE_WAIT_F;
		bweak;
	case W2CAP_EV_WETWANS_TO:
		w2cap_send_ww_ow_wnw(chan, 1);
		chan->wetwy_count = 1;
		__set_monitow_timew(chan);
		chan->tx_state = W2CAP_TX_STATE_WAIT_F;
		bweak;
	case W2CAP_EV_WECV_FBIT:
		/* Nothing to pwocess */
		bweak;
	defauwt:
		bweak;
	}
}

static void w2cap_tx_state_wait_f(stwuct w2cap_chan *chan,
				  stwuct w2cap_ctww *contwow,
				  stwuct sk_buff_head *skbs, u8 event)
{
	BT_DBG("chan %p, contwow %p, skbs %p, event %d", chan, contwow, skbs,
	       event);

	switch (event) {
	case W2CAP_EV_DATA_WEQUEST:
		if (chan->tx_send_head == NUWW)
			chan->tx_send_head = skb_peek(skbs);
		/* Queue data, but don't send. */
		skb_queue_spwice_taiw_init(skbs, &chan->tx_q);
		bweak;
	case W2CAP_EV_WOCAW_BUSY_DETECTED:
		BT_DBG("Entew WOCAW_BUSY");
		set_bit(CONN_WOCAW_BUSY, &chan->conn_state);

		if (chan->wx_state == W2CAP_WX_STATE_SWEJ_SENT) {
			/* The SWEJ_SENT state must be abowted if we awe to
			 * entew the WOCAW_BUSY state.
			 */
			w2cap_abowt_wx_swej_sent(chan);
		}

		w2cap_send_ack(chan);

		bweak;
	case W2CAP_EV_WOCAW_BUSY_CWEAW:
		BT_DBG("Exit WOCAW_BUSY");
		cweaw_bit(CONN_WOCAW_BUSY, &chan->conn_state);

		if (test_bit(CONN_WNW_SENT, &chan->conn_state)) {
			stwuct w2cap_ctww wocaw_contwow;
			memset(&wocaw_contwow, 0, sizeof(wocaw_contwow));
			wocaw_contwow.sfwame = 1;
			wocaw_contwow.supew = W2CAP_SUPEW_WW;
			wocaw_contwow.poww = 1;
			wocaw_contwow.weqseq = chan->buffew_seq;
			w2cap_send_sfwame(chan, &wocaw_contwow);

			chan->wetwy_count = 1;
			__set_monitow_timew(chan);
			chan->tx_state = W2CAP_TX_STATE_WAIT_F;
		}
		bweak;
	case W2CAP_EV_WECV_WEQSEQ_AND_FBIT:
		w2cap_pwocess_weqseq(chan, contwow->weqseq);
		fawwthwough;

	case W2CAP_EV_WECV_FBIT:
		if (contwow && contwow->finaw) {
			__cweaw_monitow_timew(chan);
			if (chan->unacked_fwames > 0)
				__set_wetwans_timew(chan);
			chan->wetwy_count = 0;
			chan->tx_state = W2CAP_TX_STATE_XMIT;
			BT_DBG("wecv fbit tx_state 0x2.2%x", chan->tx_state);
		}
		bweak;
	case W2CAP_EV_EXPWICIT_POWW:
		/* Ignowe */
		bweak;
	case W2CAP_EV_MONITOW_TO:
		if (chan->max_tx == 0 || chan->wetwy_count < chan->max_tx) {
			w2cap_send_ww_ow_wnw(chan, 1);
			__set_monitow_timew(chan);
			chan->wetwy_count++;
		} ewse {
			w2cap_send_disconn_weq(chan, ECONNABOWTED);
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void w2cap_tx(stwuct w2cap_chan *chan, stwuct w2cap_ctww *contwow,
		     stwuct sk_buff_head *skbs, u8 event)
{
	BT_DBG("chan %p, contwow %p, skbs %p, event %d, state %d",
	       chan, contwow, skbs, event, chan->tx_state);

	switch (chan->tx_state) {
	case W2CAP_TX_STATE_XMIT:
		w2cap_tx_state_xmit(chan, contwow, skbs, event);
		bweak;
	case W2CAP_TX_STATE_WAIT_F:
		w2cap_tx_state_wait_f(chan, contwow, skbs, event);
		bweak;
	defauwt:
		/* Ignowe event */
		bweak;
	}
}

static void w2cap_pass_to_tx(stwuct w2cap_chan *chan,
			     stwuct w2cap_ctww *contwow)
{
	BT_DBG("chan %p, contwow %p", chan, contwow);
	w2cap_tx(chan, contwow, NUWW, W2CAP_EV_WECV_WEQSEQ_AND_FBIT);
}

static void w2cap_pass_to_tx_fbit(stwuct w2cap_chan *chan,
				  stwuct w2cap_ctww *contwow)
{
	BT_DBG("chan %p, contwow %p", chan, contwow);
	w2cap_tx(chan, contwow, NUWW, W2CAP_EV_WECV_FBIT);
}

/* Copy fwame to aww waw sockets on that connection */
static void w2cap_waw_wecv(stwuct w2cap_conn *conn, stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb;
	stwuct w2cap_chan *chan;

	BT_DBG("conn %p", conn);

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {
		if (chan->chan_type != W2CAP_CHAN_WAW)
			continue;

		/* Don't send fwame to the channew it came fwom */
		if (bt_cb(skb)->w2cap.chan == chan)
			continue;

		nskb = skb_cwone(skb, GFP_KEWNEW);
		if (!nskb)
			continue;
		if (chan->ops->wecv(chan, nskb))
			kfwee_skb(nskb);
	}

	mutex_unwock(&conn->chan_wock);
}

/* ---- W2CAP signawwing commands ---- */
static stwuct sk_buff *w2cap_buiwd_cmd(stwuct w2cap_conn *conn, u8 code,
				       u8 ident, u16 dwen, void *data)
{
	stwuct sk_buff *skb, **fwag;
	stwuct w2cap_cmd_hdw *cmd;
	stwuct w2cap_hdw *wh;
	int wen, count;

	BT_DBG("conn %p, code 0x%2.2x, ident 0x%2.2x, wen %u",
	       conn, code, ident, dwen);

	if (conn->mtu < W2CAP_HDW_SIZE + W2CAP_CMD_HDW_SIZE)
		wetuwn NUWW;

	wen = W2CAP_HDW_SIZE + W2CAP_CMD_HDW_SIZE + dwen;
	count = min_t(unsigned int, conn->mtu, wen);

	skb = bt_skb_awwoc(count, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	wh = skb_put(skb, W2CAP_HDW_SIZE);
	wh->wen = cpu_to_we16(W2CAP_CMD_HDW_SIZE + dwen);

	if (conn->hcon->type == WE_WINK)
		wh->cid = cpu_to_we16(W2CAP_CID_WE_SIGNAWING);
	ewse
		wh->cid = cpu_to_we16(W2CAP_CID_SIGNAWING);

	cmd = skb_put(skb, W2CAP_CMD_HDW_SIZE);
	cmd->code  = code;
	cmd->ident = ident;
	cmd->wen   = cpu_to_we16(dwen);

	if (dwen) {
		count -= W2CAP_HDW_SIZE + W2CAP_CMD_HDW_SIZE;
		skb_put_data(skb, data, count);
		data += count;
	}

	wen -= skb->wen;

	/* Continuation fwagments (no W2CAP headew) */
	fwag = &skb_shinfo(skb)->fwag_wist;
	whiwe (wen) {
		count = min_t(unsigned int, conn->mtu, wen);

		*fwag = bt_skb_awwoc(count, GFP_KEWNEW);
		if (!*fwag)
			goto faiw;

		skb_put_data(*fwag, data, count);

		wen  -= count;
		data += count;

		fwag = &(*fwag)->next;
	}

	wetuwn skb;

faiw:
	kfwee_skb(skb);
	wetuwn NUWW;
}

static inwine int w2cap_get_conf_opt(void **ptw, int *type, int *owen,
				     unsigned wong *vaw)
{
	stwuct w2cap_conf_opt *opt = *ptw;
	int wen;

	wen = W2CAP_CONF_OPT_SIZE + opt->wen;
	*ptw += wen;

	*type = opt->type;
	*owen = opt->wen;

	switch (opt->wen) {
	case 1:
		*vaw = *((u8 *) opt->vaw);
		bweak;

	case 2:
		*vaw = get_unawigned_we16(opt->vaw);
		bweak;

	case 4:
		*vaw = get_unawigned_we32(opt->vaw);
		bweak;

	defauwt:
		*vaw = (unsigned wong) opt->vaw;
		bweak;
	}

	BT_DBG("type 0x%2.2x wen %u vaw 0x%wx", *type, opt->wen, *vaw);
	wetuwn wen;
}

static void w2cap_add_conf_opt(void **ptw, u8 type, u8 wen, unsigned wong vaw, size_t size)
{
	stwuct w2cap_conf_opt *opt = *ptw;

	BT_DBG("type 0x%2.2x wen %u vaw 0x%wx", type, wen, vaw);

	if (size < W2CAP_CONF_OPT_SIZE + wen)
		wetuwn;

	opt->type = type;
	opt->wen  = wen;

	switch (wen) {
	case 1:
		*((u8 *) opt->vaw)  = vaw;
		bweak;

	case 2:
		put_unawigned_we16(vaw, opt->vaw);
		bweak;

	case 4:
		put_unawigned_we32(vaw, opt->vaw);
		bweak;

	defauwt:
		memcpy(opt->vaw, (void *) vaw, wen);
		bweak;
	}

	*ptw += W2CAP_CONF_OPT_SIZE + wen;
}

static void w2cap_add_opt_efs(void **ptw, stwuct w2cap_chan *chan, size_t size)
{
	stwuct w2cap_conf_efs efs;

	switch (chan->mode) {
	case W2CAP_MODE_EWTM:
		efs.id		= chan->wocaw_id;
		efs.stype	= chan->wocaw_stype;
		efs.msdu	= cpu_to_we16(chan->wocaw_msdu);
		efs.sdu_itime	= cpu_to_we32(chan->wocaw_sdu_itime);
		efs.acc_wat	= cpu_to_we32(W2CAP_DEFAUWT_ACC_WAT);
		efs.fwush_to	= cpu_to_we32(W2CAP_EFS_DEFAUWT_FWUSH_TO);
		bweak;

	case W2CAP_MODE_STWEAMING:
		efs.id		= 1;
		efs.stype	= W2CAP_SEWV_BESTEFFOWT;
		efs.msdu	= cpu_to_we16(chan->wocaw_msdu);
		efs.sdu_itime	= cpu_to_we32(chan->wocaw_sdu_itime);
		efs.acc_wat	= 0;
		efs.fwush_to	= 0;
		bweak;

	defauwt:
		wetuwn;
	}

	w2cap_add_conf_opt(ptw, W2CAP_CONF_EFS, sizeof(efs),
			   (unsigned wong) &efs, size);
}

static void w2cap_ack_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_chan *chan = containew_of(wowk, stwuct w2cap_chan,
					       ack_timew.wowk);
	u16 fwames_to_ack;

	BT_DBG("chan %p", chan);

	w2cap_chan_wock(chan);

	fwames_to_ack = __seq_offset(chan, chan->buffew_seq,
				     chan->wast_acked_seq);

	if (fwames_to_ack)
		w2cap_send_ww_ow_wnw(chan, 0);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

int w2cap_ewtm_init(stwuct w2cap_chan *chan)
{
	int eww;

	chan->next_tx_seq = 0;
	chan->expected_tx_seq = 0;
	chan->expected_ack_seq = 0;
	chan->unacked_fwames = 0;
	chan->buffew_seq = 0;
	chan->fwames_sent = 0;
	chan->wast_acked_seq = 0;
	chan->sdu = NUWW;
	chan->sdu_wast_fwag = NUWW;
	chan->sdu_wen = 0;

	skb_queue_head_init(&chan->tx_q);

	chan->wocaw_amp_id = AMP_ID_BWEDW;
	chan->move_id = AMP_ID_BWEDW;
	chan->move_state = W2CAP_MOVE_STABWE;
	chan->move_wowe = W2CAP_MOVE_WOWE_NONE;

	if (chan->mode != W2CAP_MODE_EWTM)
		wetuwn 0;

	chan->wx_state = W2CAP_WX_STATE_WECV;
	chan->tx_state = W2CAP_TX_STATE_XMIT;

	skb_queue_head_init(&chan->swej_q);

	eww = w2cap_seq_wist_init(&chan->swej_wist, chan->tx_win);
	if (eww < 0)
		wetuwn eww;

	eww = w2cap_seq_wist_init(&chan->wetwans_wist, chan->wemote_tx_win);
	if (eww < 0)
		w2cap_seq_wist_fwee(&chan->swej_wist);

	wetuwn eww;
}

static inwine __u8 w2cap_sewect_mode(__u8 mode, __u16 wemote_feat_mask)
{
	switch (mode) {
	case W2CAP_MODE_STWEAMING:
	case W2CAP_MODE_EWTM:
		if (w2cap_mode_suppowted(mode, wemote_feat_mask))
			wetuwn mode;
		fawwthwough;
	defauwt:
		wetuwn W2CAP_MODE_BASIC;
	}
}

static inwine boow __w2cap_ews_suppowted(stwuct w2cap_conn *conn)
{
	wetuwn ((conn->wocaw_fixed_chan & W2CAP_FC_A2MP) &&
		(conn->feat_mask & W2CAP_FEAT_EXT_WINDOW));
}

static inwine boow __w2cap_efs_suppowted(stwuct w2cap_conn *conn)
{
	wetuwn ((conn->wocaw_fixed_chan & W2CAP_FC_A2MP) &&
		(conn->feat_mask & W2CAP_FEAT_EXT_FWOW));
}

static void __w2cap_set_ewtm_timeouts(stwuct w2cap_chan *chan,
				      stwuct w2cap_conf_wfc *wfc)
{
	if (chan->wocaw_amp_id != AMP_ID_BWEDW && chan->hs_hcon) {
		u64 ewtm_to = chan->hs_hcon->hdev->amp_be_fwush_to;

		/* Cwass 1 devices have must have EWTM timeouts
		 * exceeding the Wink Supewvision Timeout.  The
		 * defauwt Wink Supewvision Timeout fow AMP
		 * contwowwews is 10 seconds.
		 *
		 * Cwass 1 devices use 0xffffffff fow theiw
		 * best-effowt fwush timeout, so the cwamping wogic
		 * wiww wesuwt in a timeout that meets the above
		 * wequiwement.  EWTM timeouts awe 16-bit vawues, so
		 * the maximum timeout is 65.535 seconds.
		 */

		/* Convewt timeout to miwwiseconds and wound */
		ewtm_to = DIV_WOUND_UP_UWW(ewtm_to, 1000);

		/* This is the wecommended fowmuwa fow cwass 2 devices
		 * that stawt EWTM timews when packets awe sent to the
		 * contwowwew.
		 */
		ewtm_to = 3 * ewtm_to + 500;

		if (ewtm_to > 0xffff)
			ewtm_to = 0xffff;

		wfc->wetwans_timeout = cpu_to_we16((u16) ewtm_to);
		wfc->monitow_timeout = wfc->wetwans_timeout;
	} ewse {
		wfc->wetwans_timeout = cpu_to_we16(W2CAP_DEFAUWT_WETWANS_TO);
		wfc->monitow_timeout = cpu_to_we16(W2CAP_DEFAUWT_MONITOW_TO);
	}
}

static inwine void w2cap_txwin_setup(stwuct w2cap_chan *chan)
{
	if (chan->tx_win > W2CAP_DEFAUWT_TX_WINDOW &&
	    __w2cap_ews_suppowted(chan->conn)) {
		/* use extended contwow fiewd */
		set_bit(FWAG_EXT_CTWW, &chan->fwags);
		chan->tx_win_max = W2CAP_DEFAUWT_EXT_WINDOW;
	} ewse {
		chan->tx_win = min_t(u16, chan->tx_win,
				     W2CAP_DEFAUWT_TX_WINDOW);
		chan->tx_win_max = W2CAP_DEFAUWT_TX_WINDOW;
	}
	chan->ack_win = chan->tx_win;
}

static void w2cap_mtu_auto(stwuct w2cap_chan *chan)
{
	stwuct hci_conn *conn = chan->conn->hcon;

	chan->imtu = W2CAP_DEFAUWT_MIN_MTU;

	/* The 2-DH1 packet has between 2 and 56 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_2DH1))
		chan->imtu = 54;

	/* The 3-DH1 packet has between 2 and 85 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_3DH1))
		chan->imtu = 83;

	/* The 2-DH3 packet has between 2 and 369 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_2DH3))
		chan->imtu = 367;

	/* The 3-DH3 packet has between 2 and 554 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_3DH3))
		chan->imtu = 552;

	/* The 2-DH5 packet has between 2 and 681 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_2DH5))
		chan->imtu = 679;

	/* The 3-DH5 packet has between 2 and 1023 infowmation bytes
	 * (incwuding the 2-byte paywoad headew)
	 */
	if (!(conn->pkt_type & HCI_3DH5))
		chan->imtu = 1021;
}

static int w2cap_buiwd_conf_weq(stwuct w2cap_chan *chan, void *data, size_t data_size)
{
	stwuct w2cap_conf_weq *weq = data;
	stwuct w2cap_conf_wfc wfc = { .mode = chan->mode };
	void *ptw = weq->data;
	void *endptw = data + data_size;
	u16 size;

	BT_DBG("chan %p", chan);

	if (chan->num_conf_weq || chan->num_conf_wsp)
		goto done;

	switch (chan->mode) {
	case W2CAP_MODE_STWEAMING:
	case W2CAP_MODE_EWTM:
		if (test_bit(CONF_STATE2_DEVICE, &chan->conf_state))
			bweak;

		if (__w2cap_efs_suppowted(chan->conn))
			set_bit(FWAG_EFS_ENABWE, &chan->fwags);

		fawwthwough;
	defauwt:
		chan->mode = w2cap_sewect_mode(wfc.mode, chan->conn->feat_mask);
		bweak;
	}

done:
	if (chan->imtu != W2CAP_DEFAUWT_MTU) {
		if (!chan->imtu)
			w2cap_mtu_auto(chan);
		w2cap_add_conf_opt(&ptw, W2CAP_CONF_MTU, 2, chan->imtu,
				   endptw - ptw);
	}

	switch (chan->mode) {
	case W2CAP_MODE_BASIC:
		if (disabwe_ewtm)
			bweak;

		if (!(chan->conn->feat_mask & W2CAP_FEAT_EWTM) &&
		    !(chan->conn->feat_mask & W2CAP_FEAT_STWEAMING))
			bweak;

		wfc.mode            = W2CAP_MODE_BASIC;
		wfc.txwin_size      = 0;
		wfc.max_twansmit    = 0;
		wfc.wetwans_timeout = 0;
		wfc.monitow_timeout = 0;
		wfc.max_pdu_size    = 0;

		w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
				   (unsigned wong) &wfc, endptw - ptw);
		bweak;

	case W2CAP_MODE_EWTM:
		wfc.mode            = W2CAP_MODE_EWTM;
		wfc.max_twansmit    = chan->max_tx;

		__w2cap_set_ewtm_timeouts(chan, &wfc);

		size = min_t(u16, W2CAP_DEFAUWT_MAX_PDU_SIZE, chan->conn->mtu -
			     W2CAP_EXT_HDW_SIZE - W2CAP_SDUWEN_SIZE -
			     W2CAP_FCS_SIZE);
		wfc.max_pdu_size = cpu_to_we16(size);

		w2cap_txwin_setup(chan);

		wfc.txwin_size = min_t(u16, chan->tx_win,
				       W2CAP_DEFAUWT_TX_WINDOW);

		w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
				   (unsigned wong) &wfc, endptw - ptw);

		if (test_bit(FWAG_EFS_ENABWE, &chan->fwags))
			w2cap_add_opt_efs(&ptw, chan, endptw - ptw);

		if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_EWS, 2,
					   chan->tx_win, endptw - ptw);

		if (chan->conn->feat_mask & W2CAP_FEAT_FCS)
			if (chan->fcs == W2CAP_FCS_NONE ||
			    test_bit(CONF_WECV_NO_FCS, &chan->conf_state)) {
				chan->fcs = W2CAP_FCS_NONE;
				w2cap_add_conf_opt(&ptw, W2CAP_CONF_FCS, 1,
						   chan->fcs, endptw - ptw);
			}
		bweak;

	case W2CAP_MODE_STWEAMING:
		w2cap_txwin_setup(chan);
		wfc.mode            = W2CAP_MODE_STWEAMING;
		wfc.txwin_size      = 0;
		wfc.max_twansmit    = 0;
		wfc.wetwans_timeout = 0;
		wfc.monitow_timeout = 0;

		size = min_t(u16, W2CAP_DEFAUWT_MAX_PDU_SIZE, chan->conn->mtu -
			     W2CAP_EXT_HDW_SIZE - W2CAP_SDUWEN_SIZE -
			     W2CAP_FCS_SIZE);
		wfc.max_pdu_size = cpu_to_we16(size);

		w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
				   (unsigned wong) &wfc, endptw - ptw);

		if (test_bit(FWAG_EFS_ENABWE, &chan->fwags))
			w2cap_add_opt_efs(&ptw, chan, endptw - ptw);

		if (chan->conn->feat_mask & W2CAP_FEAT_FCS)
			if (chan->fcs == W2CAP_FCS_NONE ||
			    test_bit(CONF_WECV_NO_FCS, &chan->conf_state)) {
				chan->fcs = W2CAP_FCS_NONE;
				w2cap_add_conf_opt(&ptw, W2CAP_CONF_FCS, 1,
						   chan->fcs, endptw - ptw);
			}
		bweak;
	}

	weq->dcid  = cpu_to_we16(chan->dcid);
	weq->fwags = cpu_to_we16(0);

	wetuwn ptw - data;
}

static int w2cap_pawse_conf_weq(stwuct w2cap_chan *chan, void *data, size_t data_size)
{
	stwuct w2cap_conf_wsp *wsp = data;
	void *ptw = wsp->data;
	void *endptw = data + data_size;
	void *weq = chan->conf_weq;
	int wen = chan->conf_wen;
	int type, hint, owen;
	unsigned wong vaw;
	stwuct w2cap_conf_wfc wfc = { .mode = W2CAP_MODE_BASIC };
	stwuct w2cap_conf_efs efs;
	u8 wemote_efs = 0;
	u16 mtu = W2CAP_DEFAUWT_MTU;
	u16 wesuwt = W2CAP_CONF_SUCCESS;
	u16 size;

	BT_DBG("chan %p", chan);

	whiwe (wen >= W2CAP_CONF_OPT_SIZE) {
		wen -= w2cap_get_conf_opt(&weq, &type, &owen, &vaw);
		if (wen < 0)
			bweak;

		hint  = type & W2CAP_CONF_HINT;
		type &= W2CAP_CONF_MASK;

		switch (type) {
		case W2CAP_CONF_MTU:
			if (owen != 2)
				bweak;
			mtu = vaw;
			bweak;

		case W2CAP_CONF_FWUSH_TO:
			if (owen != 2)
				bweak;
			chan->fwush_to = vaw;
			bweak;

		case W2CAP_CONF_QOS:
			bweak;

		case W2CAP_CONF_WFC:
			if (owen != sizeof(wfc))
				bweak;
			memcpy(&wfc, (void *) vaw, owen);
			bweak;

		case W2CAP_CONF_FCS:
			if (owen != 1)
				bweak;
			if (vaw == W2CAP_FCS_NONE)
				set_bit(CONF_WECV_NO_FCS, &chan->conf_state);
			bweak;

		case W2CAP_CONF_EFS:
			if (owen != sizeof(efs))
				bweak;
			wemote_efs = 1;
			memcpy(&efs, (void *) vaw, owen);
			bweak;

		case W2CAP_CONF_EWS:
			if (owen != 2)
				bweak;
			if (!(chan->conn->wocaw_fixed_chan & W2CAP_FC_A2MP))
				wetuwn -ECONNWEFUSED;
			set_bit(FWAG_EXT_CTWW, &chan->fwags);
			set_bit(CONF_EWS_WECV, &chan->conf_state);
			chan->tx_win_max = W2CAP_DEFAUWT_EXT_WINDOW;
			chan->wemote_tx_win = vaw;
			bweak;

		defauwt:
			if (hint)
				bweak;
			wesuwt = W2CAP_CONF_UNKNOWN;
			w2cap_add_conf_opt(&ptw, (u8)type, sizeof(u8), type, endptw - ptw);
			bweak;
		}
	}

	if (chan->num_conf_wsp || chan->num_conf_weq > 1)
		goto done;

	switch (chan->mode) {
	case W2CAP_MODE_STWEAMING:
	case W2CAP_MODE_EWTM:
		if (!test_bit(CONF_STATE2_DEVICE, &chan->conf_state)) {
			chan->mode = w2cap_sewect_mode(wfc.mode,
						       chan->conn->feat_mask);
			bweak;
		}

		if (wemote_efs) {
			if (__w2cap_efs_suppowted(chan->conn))
				set_bit(FWAG_EFS_ENABWE, &chan->fwags);
			ewse
				wetuwn -ECONNWEFUSED;
		}

		if (chan->mode != wfc.mode)
			wetuwn -ECONNWEFUSED;

		bweak;
	}

done:
	if (chan->mode != wfc.mode) {
		wesuwt = W2CAP_CONF_UNACCEPT;
		wfc.mode = chan->mode;

		if (chan->num_conf_wsp == 1)
			wetuwn -ECONNWEFUSED;

		w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
				   (unsigned wong) &wfc, endptw - ptw);
	}

	if (wesuwt == W2CAP_CONF_SUCCESS) {
		/* Configuwe output options and wet the othew side know
		 * which ones we don't wike. */

		if (mtu < W2CAP_DEFAUWT_MIN_MTU)
			wesuwt = W2CAP_CONF_UNACCEPT;
		ewse {
			chan->omtu = mtu;
			set_bit(CONF_MTU_DONE, &chan->conf_state);
		}
		w2cap_add_conf_opt(&ptw, W2CAP_CONF_MTU, 2, chan->omtu, endptw - ptw);

		if (wemote_efs) {
			if (chan->wocaw_stype != W2CAP_SEWV_NOTWAFIC &&
			    efs.stype != W2CAP_SEWV_NOTWAFIC &&
			    efs.stype != chan->wocaw_stype) {

				wesuwt = W2CAP_CONF_UNACCEPT;

				if (chan->num_conf_weq >= 1)
					wetuwn -ECONNWEFUSED;

				w2cap_add_conf_opt(&ptw, W2CAP_CONF_EFS,
						   sizeof(efs),
						   (unsigned wong) &efs, endptw - ptw);
			} ewse {
				/* Send PENDING Conf Wsp */
				wesuwt = W2CAP_CONF_PENDING;
				set_bit(CONF_WOC_CONF_PEND, &chan->conf_state);
			}
		}

		switch (wfc.mode) {
		case W2CAP_MODE_BASIC:
			chan->fcs = W2CAP_FCS_NONE;
			set_bit(CONF_MODE_DONE, &chan->conf_state);
			bweak;

		case W2CAP_MODE_EWTM:
			if (!test_bit(CONF_EWS_WECV, &chan->conf_state))
				chan->wemote_tx_win = wfc.txwin_size;
			ewse
				wfc.txwin_size = W2CAP_DEFAUWT_TX_WINDOW;

			chan->wemote_max_tx = wfc.max_twansmit;

			size = min_t(u16, we16_to_cpu(wfc.max_pdu_size),
				     chan->conn->mtu - W2CAP_EXT_HDW_SIZE -
				     W2CAP_SDUWEN_SIZE - W2CAP_FCS_SIZE);
			wfc.max_pdu_size = cpu_to_we16(size);
			chan->wemote_mps = size;

			__w2cap_set_ewtm_timeouts(chan, &wfc);

			set_bit(CONF_MODE_DONE, &chan->conf_state);

			w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC,
					   sizeof(wfc), (unsigned wong) &wfc, endptw - ptw);

			if (wemote_efs &&
			    test_bit(FWAG_EFS_ENABWE, &chan->fwags)) {
				chan->wemote_id = efs.id;
				chan->wemote_stype = efs.stype;
				chan->wemote_msdu = we16_to_cpu(efs.msdu);
				chan->wemote_fwush_to =
					we32_to_cpu(efs.fwush_to);
				chan->wemote_acc_wat =
					we32_to_cpu(efs.acc_wat);
				chan->wemote_sdu_itime =
					we32_to_cpu(efs.sdu_itime);
				w2cap_add_conf_opt(&ptw, W2CAP_CONF_EFS,
						   sizeof(efs),
						   (unsigned wong) &efs, endptw - ptw);
			}
			bweak;

		case W2CAP_MODE_STWEAMING:
			size = min_t(u16, we16_to_cpu(wfc.max_pdu_size),
				     chan->conn->mtu - W2CAP_EXT_HDW_SIZE -
				     W2CAP_SDUWEN_SIZE - W2CAP_FCS_SIZE);
			wfc.max_pdu_size = cpu_to_we16(size);
			chan->wemote_mps = size;

			set_bit(CONF_MODE_DONE, &chan->conf_state);

			w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
					   (unsigned wong) &wfc, endptw - ptw);

			bweak;

		defauwt:
			wesuwt = W2CAP_CONF_UNACCEPT;

			memset(&wfc, 0, sizeof(wfc));
			wfc.mode = chan->mode;
		}

		if (wesuwt == W2CAP_CONF_SUCCESS)
			set_bit(CONF_OUTPUT_DONE, &chan->conf_state);
	}
	wsp->scid   = cpu_to_we16(chan->dcid);
	wsp->wesuwt = cpu_to_we16(wesuwt);
	wsp->fwags  = cpu_to_we16(0);

	wetuwn ptw - data;
}

static int w2cap_pawse_conf_wsp(stwuct w2cap_chan *chan, void *wsp, int wen,
				void *data, size_t size, u16 *wesuwt)
{
	stwuct w2cap_conf_weq *weq = data;
	void *ptw = weq->data;
	void *endptw = data + size;
	int type, owen;
	unsigned wong vaw;
	stwuct w2cap_conf_wfc wfc = { .mode = W2CAP_MODE_BASIC };
	stwuct w2cap_conf_efs efs;

	BT_DBG("chan %p, wsp %p, wen %d, weq %p", chan, wsp, wen, data);

	whiwe (wen >= W2CAP_CONF_OPT_SIZE) {
		wen -= w2cap_get_conf_opt(&wsp, &type, &owen, &vaw);
		if (wen < 0)
			bweak;

		switch (type) {
		case W2CAP_CONF_MTU:
			if (owen != 2)
				bweak;
			if (vaw < W2CAP_DEFAUWT_MIN_MTU) {
				*wesuwt = W2CAP_CONF_UNACCEPT;
				chan->imtu = W2CAP_DEFAUWT_MIN_MTU;
			} ewse
				chan->imtu = vaw;
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_MTU, 2, chan->imtu,
					   endptw - ptw);
			bweak;

		case W2CAP_CONF_FWUSH_TO:
			if (owen != 2)
				bweak;
			chan->fwush_to = vaw;
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_FWUSH_TO, 2,
					   chan->fwush_to, endptw - ptw);
			bweak;

		case W2CAP_CONF_WFC:
			if (owen != sizeof(wfc))
				bweak;
			memcpy(&wfc, (void *)vaw, owen);
			if (test_bit(CONF_STATE2_DEVICE, &chan->conf_state) &&
			    wfc.mode != chan->mode)
				wetuwn -ECONNWEFUSED;
			chan->fcs = 0;
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_WFC, sizeof(wfc),
					   (unsigned wong) &wfc, endptw - ptw);
			bweak;

		case W2CAP_CONF_EWS:
			if (owen != 2)
				bweak;
			chan->ack_win = min_t(u16, vaw, chan->ack_win);
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_EWS, 2,
					   chan->tx_win, endptw - ptw);
			bweak;

		case W2CAP_CONF_EFS:
			if (owen != sizeof(efs))
				bweak;
			memcpy(&efs, (void *)vaw, owen);
			if (chan->wocaw_stype != W2CAP_SEWV_NOTWAFIC &&
			    efs.stype != W2CAP_SEWV_NOTWAFIC &&
			    efs.stype != chan->wocaw_stype)
				wetuwn -ECONNWEFUSED;
			w2cap_add_conf_opt(&ptw, W2CAP_CONF_EFS, sizeof(efs),
					   (unsigned wong) &efs, endptw - ptw);
			bweak;

		case W2CAP_CONF_FCS:
			if (owen != 1)
				bweak;
			if (*wesuwt == W2CAP_CONF_PENDING)
				if (vaw == W2CAP_FCS_NONE)
					set_bit(CONF_WECV_NO_FCS,
						&chan->conf_state);
			bweak;
		}
	}

	if (chan->mode == W2CAP_MODE_BASIC && chan->mode != wfc.mode)
		wetuwn -ECONNWEFUSED;

	chan->mode = wfc.mode;

	if (*wesuwt == W2CAP_CONF_SUCCESS || *wesuwt == W2CAP_CONF_PENDING) {
		switch (wfc.mode) {
		case W2CAP_MODE_EWTM:
			chan->wetwans_timeout = we16_to_cpu(wfc.wetwans_timeout);
			chan->monitow_timeout = we16_to_cpu(wfc.monitow_timeout);
			chan->mps    = we16_to_cpu(wfc.max_pdu_size);
			if (!test_bit(FWAG_EXT_CTWW, &chan->fwags))
				chan->ack_win = min_t(u16, chan->ack_win,
						      wfc.txwin_size);

			if (test_bit(FWAG_EFS_ENABWE, &chan->fwags)) {
				chan->wocaw_msdu = we16_to_cpu(efs.msdu);
				chan->wocaw_sdu_itime =
					we32_to_cpu(efs.sdu_itime);
				chan->wocaw_acc_wat = we32_to_cpu(efs.acc_wat);
				chan->wocaw_fwush_to =
					we32_to_cpu(efs.fwush_to);
			}
			bweak;

		case W2CAP_MODE_STWEAMING:
			chan->mps    = we16_to_cpu(wfc.max_pdu_size);
		}
	}

	weq->dcid   = cpu_to_we16(chan->dcid);
	weq->fwags  = cpu_to_we16(0);

	wetuwn ptw - data;
}

static int w2cap_buiwd_conf_wsp(stwuct w2cap_chan *chan, void *data,
				u16 wesuwt, u16 fwags)
{
	stwuct w2cap_conf_wsp *wsp = data;
	void *ptw = wsp->data;

	BT_DBG("chan %p", chan);

	wsp->scid   = cpu_to_we16(chan->dcid);
	wsp->wesuwt = cpu_to_we16(wesuwt);
	wsp->fwags  = cpu_to_we16(fwags);

	wetuwn ptw - data;
}

void __w2cap_we_connect_wsp_defew(stwuct w2cap_chan *chan)
{
	stwuct w2cap_we_conn_wsp wsp;
	stwuct w2cap_conn *conn = chan->conn;

	BT_DBG("chan %p", chan);

	wsp.dcid    = cpu_to_we16(chan->scid);
	wsp.mtu     = cpu_to_we16(chan->imtu);
	wsp.mps     = cpu_to_we16(chan->mps);
	wsp.cwedits = cpu_to_we16(chan->wx_cwedits);
	wsp.wesuwt  = cpu_to_we16(W2CAP_CW_WE_SUCCESS);

	w2cap_send_cmd(conn, chan->ident, W2CAP_WE_CONN_WSP, sizeof(wsp),
		       &wsp);
}

static void w2cap_ecwed_wist_defew(stwuct w2cap_chan *chan, void *data)
{
	int *wesuwt = data;

	if (*wesuwt || test_bit(FWAG_ECWED_CONN_WEQ_SENT, &chan->fwags))
		wetuwn;

	switch (chan->state) {
	case BT_CONNECT2:
		/* If channew stiww pending accept add to wesuwt */
		(*wesuwt)++;
		wetuwn;
	case BT_CONNECTED:
		wetuwn;
	defauwt:
		/* If not connected ow pending accept it has been wefused */
		*wesuwt = -ECONNWEFUSED;
		wetuwn;
	}
}

stwuct w2cap_ecwed_wsp_data {
	stwuct {
		stwuct w2cap_ecwed_conn_wsp wsp;
		__we16 scid[W2CAP_ECWED_MAX_CID];
	} __packed pdu;
	int count;
};

static void w2cap_ecwed_wsp_defew(stwuct w2cap_chan *chan, void *data)
{
	stwuct w2cap_ecwed_wsp_data *wsp = data;

	if (test_bit(FWAG_ECWED_CONN_WEQ_SENT, &chan->fwags))
		wetuwn;

	/* Weset ident so onwy one wesponse is sent */
	chan->ident = 0;

	/* Incwude aww channews pending with the same ident */
	if (!wsp->pdu.wsp.wesuwt)
		wsp->pdu.wsp.dcid[wsp->count++] = cpu_to_we16(chan->scid);
	ewse
		w2cap_chan_dew(chan, ECONNWESET);
}

void __w2cap_ecwed_conn_wsp_defew(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_ecwed_wsp_data data;
	u16 id = chan->ident;
	int wesuwt = 0;

	if (!id)
		wetuwn;

	BT_DBG("chan %p id %d", chan, id);

	memset(&data, 0, sizeof(data));

	data.pdu.wsp.mtu     = cpu_to_we16(chan->imtu);
	data.pdu.wsp.mps     = cpu_to_we16(chan->mps);
	data.pdu.wsp.cwedits = cpu_to_we16(chan->wx_cwedits);
	data.pdu.wsp.wesuwt  = cpu_to_we16(W2CAP_CW_WE_SUCCESS);

	/* Vewify that aww channews awe weady */
	__w2cap_chan_wist_id(conn, id, w2cap_ecwed_wist_defew, &wesuwt);

	if (wesuwt > 0)
		wetuwn;

	if (wesuwt < 0)
		data.pdu.wsp.wesuwt = cpu_to_we16(W2CAP_CW_WE_AUTHOWIZATION);

	/* Buiwd wesponse */
	__w2cap_chan_wist_id(conn, id, w2cap_ecwed_wsp_defew, &data);

	w2cap_send_cmd(conn, id, W2CAP_ECWED_CONN_WSP,
		       sizeof(data.pdu.wsp) + (data.count * sizeof(__we16)),
		       &data.pdu);
}

void __w2cap_connect_wsp_defew(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn_wsp wsp;
	stwuct w2cap_conn *conn = chan->conn;
	u8 buf[128];
	u8 wsp_code;

	wsp.scid   = cpu_to_we16(chan->dcid);
	wsp.dcid   = cpu_to_we16(chan->scid);
	wsp.wesuwt = cpu_to_we16(W2CAP_CW_SUCCESS);
	wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);

	if (chan->hs_hcon)
		wsp_code = W2CAP_CWEATE_CHAN_WSP;
	ewse
		wsp_code = W2CAP_CONN_WSP;

	BT_DBG("chan %p wsp_code %u", chan, wsp_code);

	w2cap_send_cmd(conn, chan->ident, wsp_code, sizeof(wsp), &wsp);

	if (test_and_set_bit(CONF_WEQ_SENT, &chan->conf_state))
		wetuwn;

	w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_CONF_WEQ,
		       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)), buf);
	chan->num_conf_weq++;
}

static void w2cap_conf_wfc_get(stwuct w2cap_chan *chan, void *wsp, int wen)
{
	int type, owen;
	unsigned wong vaw;
	/* Use sane defauwt vawues in case a misbehaving wemote device
	 * did not send an WFC ow extended window size option.
	 */
	u16 txwin_ext = chan->ack_win;
	stwuct w2cap_conf_wfc wfc = {
		.mode = chan->mode,
		.wetwans_timeout = cpu_to_we16(W2CAP_DEFAUWT_WETWANS_TO),
		.monitow_timeout = cpu_to_we16(W2CAP_DEFAUWT_MONITOW_TO),
		.max_pdu_size = cpu_to_we16(chan->imtu),
		.txwin_size = min_t(u16, chan->ack_win, W2CAP_DEFAUWT_TX_WINDOW),
	};

	BT_DBG("chan %p, wsp %p, wen %d", chan, wsp, wen);

	if ((chan->mode != W2CAP_MODE_EWTM) && (chan->mode != W2CAP_MODE_STWEAMING))
		wetuwn;

	whiwe (wen >= W2CAP_CONF_OPT_SIZE) {
		wen -= w2cap_get_conf_opt(&wsp, &type, &owen, &vaw);
		if (wen < 0)
			bweak;

		switch (type) {
		case W2CAP_CONF_WFC:
			if (owen != sizeof(wfc))
				bweak;
			memcpy(&wfc, (void *)vaw, owen);
			bweak;
		case W2CAP_CONF_EWS:
			if (owen != 2)
				bweak;
			txwin_ext = vaw;
			bweak;
		}
	}

	switch (wfc.mode) {
	case W2CAP_MODE_EWTM:
		chan->wetwans_timeout = we16_to_cpu(wfc.wetwans_timeout);
		chan->monitow_timeout = we16_to_cpu(wfc.monitow_timeout);
		chan->mps = we16_to_cpu(wfc.max_pdu_size);
		if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
			chan->ack_win = min_t(u16, chan->ack_win, txwin_ext);
		ewse
			chan->ack_win = min_t(u16, chan->ack_win,
					      wfc.txwin_size);
		bweak;
	case W2CAP_MODE_STWEAMING:
		chan->mps    = we16_to_cpu(wfc.max_pdu_size);
	}
}

static inwine int w2cap_command_wej(stwuct w2cap_conn *conn,
				    stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				    u8 *data)
{
	stwuct w2cap_cmd_wej_unk *wej = (stwuct w2cap_cmd_wej_unk *) data;

	if (cmd_wen < sizeof(*wej))
		wetuwn -EPWOTO;

	if (wej->weason != W2CAP_WEJ_NOT_UNDEWSTOOD)
		wetuwn 0;

	if ((conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_SENT) &&
	    cmd->ident == conn->info_ident) {
		cancew_dewayed_wowk(&conn->info_timew);

		conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_DONE;
		conn->info_ident = 0;

		w2cap_conn_stawt(conn);
	}

	wetuwn 0;
}

static stwuct w2cap_chan *w2cap_connect(stwuct w2cap_conn *conn,
					stwuct w2cap_cmd_hdw *cmd,
					u8 *data, u8 wsp_code, u8 amp_id)
{
	stwuct w2cap_conn_weq *weq = (stwuct w2cap_conn_weq *) data;
	stwuct w2cap_conn_wsp wsp;
	stwuct w2cap_chan *chan = NUWW, *pchan;
	int wesuwt, status = W2CAP_CS_NO_INFO;

	u16 dcid = 0, scid = __we16_to_cpu(weq->scid);
	__we16 psm = weq->psm;

	BT_DBG("psm 0x%2.2x scid 0x%4.4x", __we16_to_cpu(psm), scid);

	/* Check if we have socket wistening on psm */
	pchan = w2cap_gwobaw_chan_by_psm(BT_WISTEN, psm, &conn->hcon->swc,
					 &conn->hcon->dst, ACW_WINK);
	if (!pchan) {
		wesuwt = W2CAP_CW_BAD_PSM;
		goto sendwesp;
	}

	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(pchan);

	/* Check if the ACW is secuwe enough (if not SDP) */
	if (psm != cpu_to_we16(W2CAP_PSM_SDP) &&
	    !hci_conn_check_wink_mode(conn->hcon)) {
		conn->disc_weason = HCI_EWWOW_AUTH_FAIWUWE;
		wesuwt = W2CAP_CW_SEC_BWOCK;
		goto wesponse;
	}

	wesuwt = W2CAP_CW_NO_MEM;

	/* Check fow vawid dynamic CID wange (as pew Ewwatum 3253) */
	if (scid < W2CAP_CID_DYN_STAWT || scid > W2CAP_CID_DYN_END) {
		wesuwt = W2CAP_CW_INVAWID_SCID;
		goto wesponse;
	}

	/* Check if we awweady have channew with that dcid */
	if (__w2cap_get_chan_by_dcid(conn, scid)) {
		wesuwt = W2CAP_CW_SCID_IN_USE;
		goto wesponse;
	}

	chan = pchan->ops->new_connection(pchan);
	if (!chan)
		goto wesponse;

	/* Fow cewtain devices (ex: HID mouse), suppowt fow authentication,
	 * paiwing and bonding is optionaw. Fow such devices, inowdew to avoid
	 * the ACW awive fow too wong aftew W2CAP disconnection, weset the ACW
	 * disc_timeout back to HCI_DISCONN_TIMEOUT duwing W2CAP connect.
	 */
	conn->hcon->disc_timeout = HCI_DISCONN_TIMEOUT;

	bacpy(&chan->swc, &conn->hcon->swc);
	bacpy(&chan->dst, &conn->hcon->dst);
	chan->swc_type = bdaddw_swc_type(conn->hcon);
	chan->dst_type = bdaddw_dst_type(conn->hcon);
	chan->psm  = psm;
	chan->dcid = scid;
	chan->wocaw_amp_id = amp_id;

	__w2cap_chan_add(conn, chan);

	dcid = chan->scid;

	__set_chan_timew(chan, chan->ops->get_sndtimeo(chan));

	chan->ident = cmd->ident;

	if (conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_DONE) {
		if (w2cap_chan_check_secuwity(chan, fawse)) {
			if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags)) {
				w2cap_state_change(chan, BT_CONNECT2);
				wesuwt = W2CAP_CW_PEND;
				status = W2CAP_CS_AUTHOW_PEND;
				chan->ops->defew(chan);
			} ewse {
				/* Fowce pending wesuwt fow AMP contwowwews.
				 * The connection wiww succeed aftew the
				 * physicaw wink is up.
				 */
				if (amp_id == AMP_ID_BWEDW) {
					w2cap_state_change(chan, BT_CONFIG);
					wesuwt = W2CAP_CW_SUCCESS;
				} ewse {
					w2cap_state_change(chan, BT_CONNECT2);
					wesuwt = W2CAP_CW_PEND;
				}
				status = W2CAP_CS_NO_INFO;
			}
		} ewse {
			w2cap_state_change(chan, BT_CONNECT2);
			wesuwt = W2CAP_CW_PEND;
			status = W2CAP_CS_AUTHEN_PEND;
		}
	} ewse {
		w2cap_state_change(chan, BT_CONNECT2);
		wesuwt = W2CAP_CW_PEND;
		status = W2CAP_CS_NO_INFO;
	}

wesponse:
	w2cap_chan_unwock(pchan);
	mutex_unwock(&conn->chan_wock);
	w2cap_chan_put(pchan);

sendwesp:
	wsp.scid   = cpu_to_we16(scid);
	wsp.dcid   = cpu_to_we16(dcid);
	wsp.wesuwt = cpu_to_we16(wesuwt);
	wsp.status = cpu_to_we16(status);
	w2cap_send_cmd(conn, cmd->ident, wsp_code, sizeof(wsp), &wsp);

	if (wesuwt == W2CAP_CW_PEND && status == W2CAP_CS_NO_INFO) {
		stwuct w2cap_info_weq info;
		info.type = cpu_to_we16(W2CAP_IT_FEAT_MASK);

		conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_SENT;
		conn->info_ident = w2cap_get_ident(conn);

		scheduwe_dewayed_wowk(&conn->info_timew, W2CAP_INFO_TIMEOUT);

		w2cap_send_cmd(conn, conn->info_ident, W2CAP_INFO_WEQ,
			       sizeof(info), &info);
	}

	if (chan && !test_bit(CONF_WEQ_SENT, &chan->conf_state) &&
	    wesuwt == W2CAP_CW_SUCCESS) {
		u8 buf[128];
		set_bit(CONF_WEQ_SENT, &chan->conf_state);
		w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_CONF_WEQ,
			       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)), buf);
		chan->num_conf_weq++;
	}

	wetuwn chan;
}

static int w2cap_connect_weq(stwuct w2cap_conn *conn,
			     stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen, u8 *data)
{
	stwuct hci_dev *hdev = conn->hcon->hdev;
	stwuct hci_conn *hcon = conn->hcon;

	if (cmd_wen < sizeof(stwuct w2cap_conn_weq))
		wetuwn -EPWOTO;

	hci_dev_wock(hdev);
	if (hci_dev_test_fwag(hdev, HCI_MGMT) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &hcon->fwags))
		mgmt_device_connected(hdev, hcon, NUWW, 0);
	hci_dev_unwock(hdev);

	w2cap_connect(conn, cmd, data, W2CAP_CONN_WSP, 0);
	wetuwn 0;
}

static int w2cap_connect_cweate_wsp(stwuct w2cap_conn *conn,
				    stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				    u8 *data)
{
	stwuct w2cap_conn_wsp *wsp = (stwuct w2cap_conn_wsp *) data;
	u16 scid, dcid, wesuwt, status;
	stwuct w2cap_chan *chan;
	u8 weq[128];
	int eww;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	scid   = __we16_to_cpu(wsp->scid);
	dcid   = __we16_to_cpu(wsp->dcid);
	wesuwt = __we16_to_cpu(wsp->wesuwt);
	status = __we16_to_cpu(wsp->status);

	if (wesuwt == W2CAP_CW_SUCCESS && (dcid < W2CAP_CID_DYN_STAWT ||
					   dcid > W2CAP_CID_DYN_END))
		wetuwn -EPWOTO;

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x wesuwt 0x%2.2x status 0x%2.2x",
	       dcid, scid, wesuwt, status);

	mutex_wock(&conn->chan_wock);

	if (scid) {
		chan = __w2cap_get_chan_by_scid(conn, scid);
		if (!chan) {
			eww = -EBADSWT;
			goto unwock;
		}
	} ewse {
		chan = __w2cap_get_chan_by_ident(conn, cmd->ident);
		if (!chan) {
			eww = -EBADSWT;
			goto unwock;
		}
	}

	chan = w2cap_chan_howd_unwess_zewo(chan);
	if (!chan) {
		eww = -EBADSWT;
		goto unwock;
	}

	eww = 0;

	w2cap_chan_wock(chan);

	switch (wesuwt) {
	case W2CAP_CW_SUCCESS:
		if (__w2cap_get_chan_by_dcid(conn, dcid)) {
			eww = -EBADSWT;
			bweak;
		}

		w2cap_state_change(chan, BT_CONFIG);
		chan->ident = 0;
		chan->dcid = dcid;
		cweaw_bit(CONF_CONNECT_PEND, &chan->conf_state);

		if (test_and_set_bit(CONF_WEQ_SENT, &chan->conf_state))
			bweak;

		w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_CONF_WEQ,
			       w2cap_buiwd_conf_weq(chan, weq, sizeof(weq)), weq);
		chan->num_conf_weq++;
		bweak;

	case W2CAP_CW_PEND:
		set_bit(CONF_CONNECT_PEND, &chan->conf_state);
		bweak;

	defauwt:
		w2cap_chan_dew(chan, ECONNWEFUSED);
		bweak;
	}

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

unwock:
	mutex_unwock(&conn->chan_wock);

	wetuwn eww;
}

static inwine void set_defauwt_fcs(stwuct w2cap_chan *chan)
{
	/* FCS is enabwed onwy in EWTM ow stweaming mode, if one ow both
	 * sides wequest it.
	 */
	if (chan->mode != W2CAP_MODE_EWTM && chan->mode != W2CAP_MODE_STWEAMING)
		chan->fcs = W2CAP_FCS_NONE;
	ewse if (!test_bit(CONF_WECV_NO_FCS, &chan->conf_state))
		chan->fcs = W2CAP_FCS_CWC16;
}

static void w2cap_send_efs_conf_wsp(stwuct w2cap_chan *chan, void *data,
				    u8 ident, u16 fwags)
{
	stwuct w2cap_conn *conn = chan->conn;

	BT_DBG("conn %p chan %p ident %d fwags 0x%4.4x", conn, chan, ident,
	       fwags);

	cweaw_bit(CONF_WOC_CONF_PEND, &chan->conf_state);
	set_bit(CONF_OUTPUT_DONE, &chan->conf_state);

	w2cap_send_cmd(conn, ident, W2CAP_CONF_WSP,
		       w2cap_buiwd_conf_wsp(chan, data,
					    W2CAP_CONF_SUCCESS, fwags), data);
}

static void cmd_weject_invawid_cid(stwuct w2cap_conn *conn, u8 ident,
				   u16 scid, u16 dcid)
{
	stwuct w2cap_cmd_wej_cid wej;

	wej.weason = cpu_to_we16(W2CAP_WEJ_INVAWID_CID);
	wej.scid = __cpu_to_we16(scid);
	wej.dcid = __cpu_to_we16(dcid);

	w2cap_send_cmd(conn, ident, W2CAP_COMMAND_WEJ, sizeof(wej), &wej);
}

static inwine int w2cap_config_weq(stwuct w2cap_conn *conn,
				   stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				   u8 *data)
{
	stwuct w2cap_conf_weq *weq = (stwuct w2cap_conf_weq *) data;
	u16 dcid, fwags;
	u8 wsp[64];
	stwuct w2cap_chan *chan;
	int wen, eww = 0;

	if (cmd_wen < sizeof(*weq))
		wetuwn -EPWOTO;

	dcid  = __we16_to_cpu(weq->dcid);
	fwags = __we16_to_cpu(weq->fwags);

	BT_DBG("dcid 0x%4.4x fwags 0x%2.2x", dcid, fwags);

	chan = w2cap_get_chan_by_scid(conn, dcid);
	if (!chan) {
		cmd_weject_invawid_cid(conn, cmd->ident, dcid, 0);
		wetuwn 0;
	}

	if (chan->state != BT_CONFIG && chan->state != BT_CONNECT2 &&
	    chan->state != BT_CONNECTED) {
		cmd_weject_invawid_cid(conn, cmd->ident, chan->scid,
				       chan->dcid);
		goto unwock;
	}

	/* Weject if config buffew is too smaww. */
	wen = cmd_wen - sizeof(*weq);
	if (chan->conf_wen + wen > sizeof(chan->conf_weq)) {
		w2cap_send_cmd(conn, cmd->ident, W2CAP_CONF_WSP,
			       w2cap_buiwd_conf_wsp(chan, wsp,
			       W2CAP_CONF_WEJECT, fwags), wsp);
		goto unwock;
	}

	/* Stowe config. */
	memcpy(chan->conf_weq + chan->conf_wen, weq->data, wen);
	chan->conf_wen += wen;

	if (fwags & W2CAP_CONF_FWAG_CONTINUATION) {
		/* Incompwete config. Send empty wesponse. */
		w2cap_send_cmd(conn, cmd->ident, W2CAP_CONF_WSP,
			       w2cap_buiwd_conf_wsp(chan, wsp,
			       W2CAP_CONF_SUCCESS, fwags), wsp);
		goto unwock;
	}

	/* Compwete config. */
	wen = w2cap_pawse_conf_weq(chan, wsp, sizeof(wsp));
	if (wen < 0) {
		w2cap_send_disconn_weq(chan, ECONNWESET);
		goto unwock;
	}

	chan->ident = cmd->ident;
	w2cap_send_cmd(conn, cmd->ident, W2CAP_CONF_WSP, wen, wsp);
	if (chan->num_conf_wsp < W2CAP_CONF_MAX_CONF_WSP)
		chan->num_conf_wsp++;

	/* Weset config buffew. */
	chan->conf_wen = 0;

	if (!test_bit(CONF_OUTPUT_DONE, &chan->conf_state))
		goto unwock;

	if (test_bit(CONF_INPUT_DONE, &chan->conf_state)) {
		set_defauwt_fcs(chan);

		if (chan->mode == W2CAP_MODE_EWTM ||
		    chan->mode == W2CAP_MODE_STWEAMING)
			eww = w2cap_ewtm_init(chan);

		if (eww < 0)
			w2cap_send_disconn_weq(chan, -eww);
		ewse
			w2cap_chan_weady(chan);

		goto unwock;
	}

	if (!test_and_set_bit(CONF_WEQ_SENT, &chan->conf_state)) {
		u8 buf[64];
		w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_CONF_WEQ,
			       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)), buf);
		chan->num_conf_weq++;
	}

	/* Got Conf Wsp PENDING fwom wemote side and assume we sent
	   Conf Wsp PENDING in the code above */
	if (test_bit(CONF_WEM_CONF_PEND, &chan->conf_state) &&
	    test_bit(CONF_WOC_CONF_PEND, &chan->conf_state)) {

		/* check compatibiwity */

		/* Send wsp fow BW/EDW channew */
		if (!chan->hs_hcon)
			w2cap_send_efs_conf_wsp(chan, wsp, cmd->ident, fwags);
		ewse
			chan->ident = cmd->ident;
	}

unwock:
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
	wetuwn eww;
}

static inwine int w2cap_config_wsp(stwuct w2cap_conn *conn,
				   stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				   u8 *data)
{
	stwuct w2cap_conf_wsp *wsp = (stwuct w2cap_conf_wsp *)data;
	u16 scid, fwags, wesuwt;
	stwuct w2cap_chan *chan;
	int wen = cmd_wen - sizeof(*wsp);
	int eww = 0;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	scid   = __we16_to_cpu(wsp->scid);
	fwags  = __we16_to_cpu(wsp->fwags);
	wesuwt = __we16_to_cpu(wsp->wesuwt);

	BT_DBG("scid 0x%4.4x fwags 0x%2.2x wesuwt 0x%2.2x wen %d", scid, fwags,
	       wesuwt, wen);

	chan = w2cap_get_chan_by_scid(conn, scid);
	if (!chan)
		wetuwn 0;

	switch (wesuwt) {
	case W2CAP_CONF_SUCCESS:
		w2cap_conf_wfc_get(chan, wsp->data, wen);
		cweaw_bit(CONF_WEM_CONF_PEND, &chan->conf_state);
		bweak;

	case W2CAP_CONF_PENDING:
		set_bit(CONF_WEM_CONF_PEND, &chan->conf_state);

		if (test_bit(CONF_WOC_CONF_PEND, &chan->conf_state)) {
			chaw buf[64];

			wen = w2cap_pawse_conf_wsp(chan, wsp->data, wen,
						   buf, sizeof(buf), &wesuwt);
			if (wen < 0) {
				w2cap_send_disconn_weq(chan, ECONNWESET);
				goto done;
			}

			if (!chan->hs_hcon) {
				w2cap_send_efs_conf_wsp(chan, buf, cmd->ident,
							0);
			} ewse {
				if (w2cap_check_efs(chan)) {
					amp_cweate_wogicaw_wink(chan);
					chan->ident = cmd->ident;
				}
			}
		}
		goto done;

	case W2CAP_CONF_UNKNOWN:
	case W2CAP_CONF_UNACCEPT:
		if (chan->num_conf_wsp <= W2CAP_CONF_MAX_CONF_WSP) {
			chaw weq[64];

			if (wen > sizeof(weq) - sizeof(stwuct w2cap_conf_weq)) {
				w2cap_send_disconn_weq(chan, ECONNWESET);
				goto done;
			}

			/* thwow out any owd stowed conf wequests */
			wesuwt = W2CAP_CONF_SUCCESS;
			wen = w2cap_pawse_conf_wsp(chan, wsp->data, wen,
						   weq, sizeof(weq), &wesuwt);
			if (wen < 0) {
				w2cap_send_disconn_weq(chan, ECONNWESET);
				goto done;
			}

			w2cap_send_cmd(conn, w2cap_get_ident(conn),
				       W2CAP_CONF_WEQ, wen, weq);
			chan->num_conf_weq++;
			if (wesuwt != W2CAP_CONF_SUCCESS)
				goto done;
			bweak;
		}
		fawwthwough;

	defauwt:
		w2cap_chan_set_eww(chan, ECONNWESET);

		__set_chan_timew(chan, W2CAP_DISC_WEJ_TIMEOUT);
		w2cap_send_disconn_weq(chan, ECONNWESET);
		goto done;
	}

	if (fwags & W2CAP_CONF_FWAG_CONTINUATION)
		goto done;

	set_bit(CONF_INPUT_DONE, &chan->conf_state);

	if (test_bit(CONF_OUTPUT_DONE, &chan->conf_state)) {
		set_defauwt_fcs(chan);

		if (chan->mode == W2CAP_MODE_EWTM ||
		    chan->mode == W2CAP_MODE_STWEAMING)
			eww = w2cap_ewtm_init(chan);

		if (eww < 0)
			w2cap_send_disconn_weq(chan, -eww);
		ewse
			w2cap_chan_weady(chan);
	}

done:
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
	wetuwn eww;
}

static inwine int w2cap_disconnect_weq(stwuct w2cap_conn *conn,
				       stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				       u8 *data)
{
	stwuct w2cap_disconn_weq *weq = (stwuct w2cap_disconn_weq *) data;
	stwuct w2cap_disconn_wsp wsp;
	u16 dcid, scid;
	stwuct w2cap_chan *chan;

	if (cmd_wen != sizeof(*weq))
		wetuwn -EPWOTO;

	scid = __we16_to_cpu(weq->scid);
	dcid = __we16_to_cpu(weq->dcid);

	BT_DBG("scid 0x%4.4x dcid 0x%4.4x", scid, dcid);

	chan = w2cap_get_chan_by_scid(conn, dcid);
	if (!chan) {
		cmd_weject_invawid_cid(conn, cmd->ident, dcid, scid);
		wetuwn 0;
	}

	wsp.dcid = cpu_to_we16(chan->scid);
	wsp.scid = cpu_to_we16(chan->dcid);
	w2cap_send_cmd(conn, cmd->ident, W2CAP_DISCONN_WSP, sizeof(wsp), &wsp);

	chan->ops->set_shutdown(chan);

	w2cap_chan_unwock(chan);
	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(chan);
	w2cap_chan_dew(chan, ECONNWESET);
	mutex_unwock(&conn->chan_wock);

	chan->ops->cwose(chan);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static inwine int w2cap_disconnect_wsp(stwuct w2cap_conn *conn,
				       stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				       u8 *data)
{
	stwuct w2cap_disconn_wsp *wsp = (stwuct w2cap_disconn_wsp *) data;
	u16 dcid, scid;
	stwuct w2cap_chan *chan;

	if (cmd_wen != sizeof(*wsp))
		wetuwn -EPWOTO;

	scid = __we16_to_cpu(wsp->scid);
	dcid = __we16_to_cpu(wsp->dcid);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x", dcid, scid);

	chan = w2cap_get_chan_by_scid(conn, scid);
	if (!chan) {
		wetuwn 0;
	}

	if (chan->state != BT_DISCONN) {
		w2cap_chan_unwock(chan);
		w2cap_chan_put(chan);
		wetuwn 0;
	}

	w2cap_chan_unwock(chan);
	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(chan);
	w2cap_chan_dew(chan, 0);
	mutex_unwock(&conn->chan_wock);

	chan->ops->cwose(chan);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static inwine int w2cap_infowmation_weq(stwuct w2cap_conn *conn,
					stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
					u8 *data)
{
	stwuct w2cap_info_weq *weq = (stwuct w2cap_info_weq *) data;
	u16 type;

	if (cmd_wen != sizeof(*weq))
		wetuwn -EPWOTO;

	type = __we16_to_cpu(weq->type);

	BT_DBG("type 0x%4.4x", type);

	if (type == W2CAP_IT_FEAT_MASK) {
		u8 buf[8];
		u32 feat_mask = w2cap_feat_mask;
		stwuct w2cap_info_wsp *wsp = (stwuct w2cap_info_wsp *) buf;
		wsp->type   = cpu_to_we16(W2CAP_IT_FEAT_MASK);
		wsp->wesuwt = cpu_to_we16(W2CAP_IW_SUCCESS);
		if (!disabwe_ewtm)
			feat_mask |= W2CAP_FEAT_EWTM | W2CAP_FEAT_STWEAMING
				| W2CAP_FEAT_FCS;
		if (conn->wocaw_fixed_chan & W2CAP_FC_A2MP)
			feat_mask |= W2CAP_FEAT_EXT_FWOW
				| W2CAP_FEAT_EXT_WINDOW;

		put_unawigned_we32(feat_mask, wsp->data);
		w2cap_send_cmd(conn, cmd->ident, W2CAP_INFO_WSP, sizeof(buf),
			       buf);
	} ewse if (type == W2CAP_IT_FIXED_CHAN) {
		u8 buf[12];
		stwuct w2cap_info_wsp *wsp = (stwuct w2cap_info_wsp *) buf;

		wsp->type   = cpu_to_we16(W2CAP_IT_FIXED_CHAN);
		wsp->wesuwt = cpu_to_we16(W2CAP_IW_SUCCESS);
		wsp->data[0] = conn->wocaw_fixed_chan;
		memset(wsp->data + 1, 0, 7);
		w2cap_send_cmd(conn, cmd->ident, W2CAP_INFO_WSP, sizeof(buf),
			       buf);
	} ewse {
		stwuct w2cap_info_wsp wsp;
		wsp.type   = cpu_to_we16(type);
		wsp.wesuwt = cpu_to_we16(W2CAP_IW_NOTSUPP);
		w2cap_send_cmd(conn, cmd->ident, W2CAP_INFO_WSP, sizeof(wsp),
			       &wsp);
	}

	wetuwn 0;
}

static inwine int w2cap_infowmation_wsp(stwuct w2cap_conn *conn,
					stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
					u8 *data)
{
	stwuct w2cap_info_wsp *wsp = (stwuct w2cap_info_wsp *) data;
	u16 type, wesuwt;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	type   = __we16_to_cpu(wsp->type);
	wesuwt = __we16_to_cpu(wsp->wesuwt);

	BT_DBG("type 0x%4.4x wesuwt 0x%2.2x", type, wesuwt);

	/* W2CAP Info weq/wsp awe unbound to channews, add extwa checks */
	if (cmd->ident != conn->info_ident ||
	    conn->info_state & W2CAP_INFO_FEAT_MASK_WEQ_DONE)
		wetuwn 0;

	cancew_dewayed_wowk(&conn->info_timew);

	if (wesuwt != W2CAP_IW_SUCCESS) {
		conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_DONE;
		conn->info_ident = 0;

		w2cap_conn_stawt(conn);

		wetuwn 0;
	}

	switch (type) {
	case W2CAP_IT_FEAT_MASK:
		conn->feat_mask = get_unawigned_we32(wsp->data);

		if (conn->feat_mask & W2CAP_FEAT_FIXED_CHAN) {
			stwuct w2cap_info_weq weq;
			weq.type = cpu_to_we16(W2CAP_IT_FIXED_CHAN);

			conn->info_ident = w2cap_get_ident(conn);

			w2cap_send_cmd(conn, conn->info_ident,
				       W2CAP_INFO_WEQ, sizeof(weq), &weq);
		} ewse {
			conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_DONE;
			conn->info_ident = 0;

			w2cap_conn_stawt(conn);
		}
		bweak;

	case W2CAP_IT_FIXED_CHAN:
		conn->wemote_fixed_chan = wsp->data[0];
		conn->info_state |= W2CAP_INFO_FEAT_MASK_WEQ_DONE;
		conn->info_ident = 0;

		w2cap_conn_stawt(conn);
		bweak;
	}

	wetuwn 0;
}

static int w2cap_cweate_channew_weq(stwuct w2cap_conn *conn,
				    stwuct w2cap_cmd_hdw *cmd,
				    u16 cmd_wen, void *data)
{
	stwuct w2cap_cweate_chan_weq *weq = data;
	stwuct w2cap_cweate_chan_wsp wsp;
	stwuct w2cap_chan *chan;
	stwuct hci_dev *hdev;
	u16 psm, scid;

	if (cmd_wen != sizeof(*weq))
		wetuwn -EPWOTO;

	if (!(conn->wocaw_fixed_chan & W2CAP_FC_A2MP))
		wetuwn -EINVAW;

	psm = we16_to_cpu(weq->psm);
	scid = we16_to_cpu(weq->scid);

	BT_DBG("psm 0x%2.2x, scid 0x%4.4x, amp_id %d", psm, scid, weq->amp_id);

	/* Fow contwowwew id 0 make BW/EDW connection */
	if (weq->amp_id == AMP_ID_BWEDW) {
		w2cap_connect(conn, cmd, data, W2CAP_CWEATE_CHAN_WSP,
			      weq->amp_id);
		wetuwn 0;
	}

	/* Vawidate AMP contwowwew id */
	hdev = hci_dev_get(weq->amp_id);
	if (!hdev)
		goto ewwow;

	if (hdev->dev_type != HCI_AMP || !test_bit(HCI_UP, &hdev->fwags)) {
		hci_dev_put(hdev);
		goto ewwow;
	}

	chan = w2cap_connect(conn, cmd, data, W2CAP_CWEATE_CHAN_WSP,
			     weq->amp_id);
	if (chan) {
		stwuct amp_mgw *mgw = conn->hcon->amp_mgw;
		stwuct hci_conn *hs_hcon;

		hs_hcon = hci_conn_hash_wookup_ba(hdev, AMP_WINK,
						  &conn->hcon->dst);
		if (!hs_hcon) {
			hci_dev_put(hdev);
			cmd_weject_invawid_cid(conn, cmd->ident, chan->scid,
					       chan->dcid);
			wetuwn 0;
		}

		BT_DBG("mgw %p bwedw_chan %p hs_hcon %p", mgw, chan, hs_hcon);

		mgw->bwedw_chan = chan;
		chan->hs_hcon = hs_hcon;
		chan->fcs = W2CAP_FCS_NONE;
		conn->mtu = hdev->bwock_mtu;
	}

	hci_dev_put(hdev);

	wetuwn 0;

ewwow:
	wsp.dcid = 0;
	wsp.scid = cpu_to_we16(scid);
	wsp.wesuwt = cpu_to_we16(W2CAP_CW_BAD_AMP);
	wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);

	w2cap_send_cmd(conn, cmd->ident, W2CAP_CWEATE_CHAN_WSP,
		       sizeof(wsp), &wsp);

	wetuwn 0;
}

static void w2cap_send_move_chan_weq(stwuct w2cap_chan *chan, u8 dest_amp_id)
{
	stwuct w2cap_move_chan_weq weq;
	u8 ident;

	BT_DBG("chan %p, dest_amp_id %d", chan, dest_amp_id);

	ident = w2cap_get_ident(chan->conn);
	chan->ident = ident;

	weq.icid = cpu_to_we16(chan->scid);
	weq.dest_amp_id = dest_amp_id;

	w2cap_send_cmd(chan->conn, ident, W2CAP_MOVE_CHAN_WEQ, sizeof(weq),
		       &weq);

	__set_chan_timew(chan, W2CAP_MOVE_TIMEOUT);
}

static void w2cap_send_move_chan_wsp(stwuct w2cap_chan *chan, u16 wesuwt)
{
	stwuct w2cap_move_chan_wsp wsp;

	BT_DBG("chan %p, wesuwt 0x%4.4x", chan, wesuwt);

	wsp.icid = cpu_to_we16(chan->dcid);
	wsp.wesuwt = cpu_to_we16(wesuwt);

	w2cap_send_cmd(chan->conn, chan->ident, W2CAP_MOVE_CHAN_WSP,
		       sizeof(wsp), &wsp);
}

static void w2cap_send_move_chan_cfm(stwuct w2cap_chan *chan, u16 wesuwt)
{
	stwuct w2cap_move_chan_cfm cfm;

	BT_DBG("chan %p, wesuwt 0x%4.4x", chan, wesuwt);

	chan->ident = w2cap_get_ident(chan->conn);

	cfm.icid = cpu_to_we16(chan->scid);
	cfm.wesuwt = cpu_to_we16(wesuwt);

	w2cap_send_cmd(chan->conn, chan->ident, W2CAP_MOVE_CHAN_CFM,
		       sizeof(cfm), &cfm);

	__set_chan_timew(chan, W2CAP_MOVE_TIMEOUT);
}

static void w2cap_send_move_chan_cfm_icid(stwuct w2cap_conn *conn, u16 icid)
{
	stwuct w2cap_move_chan_cfm cfm;

	BT_DBG("conn %p, icid 0x%4.4x", conn, icid);

	cfm.icid = cpu_to_we16(icid);
	cfm.wesuwt = cpu_to_we16(W2CAP_MC_UNCONFIWMED);

	w2cap_send_cmd(conn, w2cap_get_ident(conn), W2CAP_MOVE_CHAN_CFM,
		       sizeof(cfm), &cfm);
}

static void w2cap_send_move_chan_cfm_wsp(stwuct w2cap_conn *conn, u8 ident,
					 u16 icid)
{
	stwuct w2cap_move_chan_cfm_wsp wsp;

	BT_DBG("icid 0x%4.4x", icid);

	wsp.icid = cpu_to_we16(icid);
	w2cap_send_cmd(conn, ident, W2CAP_MOVE_CHAN_CFM_WSP, sizeof(wsp), &wsp);
}

static void __wewease_wogicaw_wink(stwuct w2cap_chan *chan)
{
	chan->hs_hchan = NUWW;
	chan->hs_hcon = NUWW;

	/* Pwacehowdew - wewease the wogicaw wink */
}

static void w2cap_wogicaw_faiw(stwuct w2cap_chan *chan)
{
	/* Wogicaw wink setup faiwed */
	if (chan->state != BT_CONNECTED) {
		/* Cweate channew faiwuwe, disconnect */
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn;
	}

	switch (chan->move_wowe) {
	case W2CAP_MOVE_WOWE_WESPONDEW:
		w2cap_move_done(chan);
		w2cap_send_move_chan_wsp(chan, W2CAP_MW_NOT_SUPP);
		bweak;
	case W2CAP_MOVE_WOWE_INITIATOW:
		if (chan->move_state == W2CAP_MOVE_WAIT_WOGICAW_COMP ||
		    chan->move_state == W2CAP_MOVE_WAIT_WOGICAW_CFM) {
			/* Wemote has onwy sent pending ow
			 * success wesponses, cwean up
			 */
			w2cap_move_done(chan);
		}

		/* Othew amp move states impwy that the move
		 * has awweady abowted
		 */
		w2cap_send_move_chan_cfm(chan, W2CAP_MC_UNCONFIWMED);
		bweak;
	}
}

static void w2cap_wogicaw_finish_cweate(stwuct w2cap_chan *chan,
					stwuct hci_chan *hchan)
{
	stwuct w2cap_conf_wsp wsp;

	chan->hs_hchan = hchan;
	chan->hs_hcon->w2cap_data = chan->conn;

	w2cap_send_efs_conf_wsp(chan, &wsp, chan->ident, 0);

	if (test_bit(CONF_INPUT_DONE, &chan->conf_state)) {
		int eww;

		set_defauwt_fcs(chan);

		eww = w2cap_ewtm_init(chan);
		if (eww < 0)
			w2cap_send_disconn_weq(chan, -eww);
		ewse
			w2cap_chan_weady(chan);
	}
}

static void w2cap_wogicaw_finish_move(stwuct w2cap_chan *chan,
				      stwuct hci_chan *hchan)
{
	chan->hs_hcon = hchan->conn;
	chan->hs_hcon->w2cap_data = chan->conn;

	BT_DBG("move_state %d", chan->move_state);

	switch (chan->move_state) {
	case W2CAP_MOVE_WAIT_WOGICAW_COMP:
		/* Move confiwm wiww be sent aftew a success
		 * wesponse is weceived
		 */
		chan->move_state = W2CAP_MOVE_WAIT_WSP_SUCCESS;
		bweak;
	case W2CAP_MOVE_WAIT_WOGICAW_CFM:
		if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
			chan->move_state = W2CAP_MOVE_WAIT_WOCAW_BUSY;
		} ewse if (chan->move_wowe == W2CAP_MOVE_WOWE_INITIATOW) {
			chan->move_state = W2CAP_MOVE_WAIT_CONFIWM_WSP;
			w2cap_send_move_chan_cfm(chan, W2CAP_MC_CONFIWMED);
		} ewse if (chan->move_wowe == W2CAP_MOVE_WOWE_WESPONDEW) {
			chan->move_state = W2CAP_MOVE_WAIT_CONFIWM;
			w2cap_send_move_chan_wsp(chan, W2CAP_MW_SUCCESS);
		}
		bweak;
	defauwt:
		/* Move was not in expected state, fwee the channew */
		__wewease_wogicaw_wink(chan);

		chan->move_state = W2CAP_MOVE_STABWE;
	}
}

/* Caww with chan wocked */
void w2cap_wogicaw_cfm(stwuct w2cap_chan *chan, stwuct hci_chan *hchan,
		       u8 status)
{
	BT_DBG("chan %p, hchan %p, status %d", chan, hchan, status);

	if (status) {
		w2cap_wogicaw_faiw(chan);
		__wewease_wogicaw_wink(chan);
		wetuwn;
	}

	if (chan->state != BT_CONNECTED) {
		/* Ignowe wogicaw wink if channew is on BW/EDW */
		if (chan->wocaw_amp_id != AMP_ID_BWEDW)
			w2cap_wogicaw_finish_cweate(chan, hchan);
	} ewse {
		w2cap_wogicaw_finish_move(chan, hchan);
	}
}

void w2cap_move_stawt(stwuct w2cap_chan *chan)
{
	BT_DBG("chan %p", chan);

	if (chan->wocaw_amp_id == AMP_ID_BWEDW) {
		if (chan->chan_powicy != BT_CHANNEW_POWICY_AMP_PWEFEWWED)
			wetuwn;
		chan->move_wowe = W2CAP_MOVE_WOWE_INITIATOW;
		chan->move_state = W2CAP_MOVE_WAIT_PWEPAWE;
		/* Pwacehowdew - stawt physicaw wink setup */
	} ewse {
		chan->move_wowe = W2CAP_MOVE_WOWE_INITIATOW;
		chan->move_state = W2CAP_MOVE_WAIT_WSP_SUCCESS;
		chan->move_id = 0;
		w2cap_move_setup(chan);
		w2cap_send_move_chan_weq(chan, 0);
	}
}

static void w2cap_do_cweate(stwuct w2cap_chan *chan, int wesuwt,
			    u8 wocaw_amp_id, u8 wemote_amp_id)
{
	BT_DBG("chan %p state %s %u -> %u", chan, state_to_stwing(chan->state),
	       wocaw_amp_id, wemote_amp_id);

	chan->fcs = W2CAP_FCS_NONE;

	/* Outgoing channew on AMP */
	if (chan->state == BT_CONNECT) {
		if (wesuwt == W2CAP_CW_SUCCESS) {
			chan->wocaw_amp_id = wocaw_amp_id;
			w2cap_send_cweate_chan_weq(chan, wemote_amp_id);
		} ewse {
			/* Wevewt to BW/EDW connect */
			w2cap_send_conn_weq(chan);
		}

		wetuwn;
	}

	/* Incoming channew on AMP */
	if (__w2cap_no_conn_pending(chan)) {
		stwuct w2cap_conn_wsp wsp;
		chaw buf[128];
		wsp.scid = cpu_to_we16(chan->dcid);
		wsp.dcid = cpu_to_we16(chan->scid);

		if (wesuwt == W2CAP_CW_SUCCESS) {
			/* Send successfuw wesponse */
			wsp.wesuwt = cpu_to_we16(W2CAP_CW_SUCCESS);
			wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);
		} ewse {
			/* Send negative wesponse */
			wsp.wesuwt = cpu_to_we16(W2CAP_CW_NO_MEM);
			wsp.status = cpu_to_we16(W2CAP_CS_NO_INFO);
		}

		w2cap_send_cmd(chan->conn, chan->ident, W2CAP_CWEATE_CHAN_WSP,
			       sizeof(wsp), &wsp);

		if (wesuwt == W2CAP_CW_SUCCESS) {
			w2cap_state_change(chan, BT_CONFIG);
			set_bit(CONF_WEQ_SENT, &chan->conf_state);
			w2cap_send_cmd(chan->conn, w2cap_get_ident(chan->conn),
				       W2CAP_CONF_WEQ,
				       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)), buf);
			chan->num_conf_weq++;
		}
	}
}

static void w2cap_do_move_initiate(stwuct w2cap_chan *chan, u8 wocaw_amp_id,
				   u8 wemote_amp_id)
{
	w2cap_move_setup(chan);
	chan->move_id = wocaw_amp_id;
	chan->move_state = W2CAP_MOVE_WAIT_WSP;

	w2cap_send_move_chan_weq(chan, wemote_amp_id);
}

static void w2cap_do_move_wespond(stwuct w2cap_chan *chan, int wesuwt)
{
	stwuct hci_chan *hchan = NUWW;

	/* Pwacehowdew - get hci_chan fow wogicaw wink */

	if (hchan) {
		if (hchan->state == BT_CONNECTED) {
			/* Wogicaw wink is weady to go */
			chan->hs_hcon = hchan->conn;
			chan->hs_hcon->w2cap_data = chan->conn;
			chan->move_state = W2CAP_MOVE_WAIT_CONFIWM;
			w2cap_send_move_chan_wsp(chan, W2CAP_MW_SUCCESS);

			w2cap_wogicaw_cfm(chan, hchan, W2CAP_MW_SUCCESS);
		} ewse {
			/* Wait fow wogicaw wink to be weady */
			chan->move_state = W2CAP_MOVE_WAIT_WOGICAW_CFM;
		}
	} ewse {
		/* Wogicaw wink not avaiwabwe */
		w2cap_send_move_chan_wsp(chan, W2CAP_MW_NOT_AWWOWED);
	}
}

static void w2cap_do_move_cancew(stwuct w2cap_chan *chan, int wesuwt)
{
	if (chan->move_wowe == W2CAP_MOVE_WOWE_WESPONDEW) {
		u8 wsp_wesuwt;
		if (wesuwt == -EINVAW)
			wsp_wesuwt = W2CAP_MW_BAD_ID;
		ewse
			wsp_wesuwt = W2CAP_MW_NOT_AWWOWED;

		w2cap_send_move_chan_wsp(chan, wsp_wesuwt);
	}

	chan->move_wowe = W2CAP_MOVE_WOWE_NONE;
	chan->move_state = W2CAP_MOVE_STABWE;

	/* Westawt data twansmission */
	w2cap_ewtm_send(chan);
}

/* Invoke with wocked chan */
void __w2cap_physicaw_cfm(stwuct w2cap_chan *chan, int wesuwt)
{
	u8 wocaw_amp_id = chan->wocaw_amp_id;
	u8 wemote_amp_id = chan->wemote_amp_id;

	BT_DBG("chan %p, wesuwt %d, wocaw_amp_id %d, wemote_amp_id %d",
	       chan, wesuwt, wocaw_amp_id, wemote_amp_id);

	if (chan->state == BT_DISCONN || chan->state == BT_CWOSED)
		wetuwn;

	if (chan->state != BT_CONNECTED) {
		w2cap_do_cweate(chan, wesuwt, wocaw_amp_id, wemote_amp_id);
	} ewse if (wesuwt != W2CAP_MW_SUCCESS) {
		w2cap_do_move_cancew(chan, wesuwt);
	} ewse {
		switch (chan->move_wowe) {
		case W2CAP_MOVE_WOWE_INITIATOW:
			w2cap_do_move_initiate(chan, wocaw_amp_id,
					       wemote_amp_id);
			bweak;
		case W2CAP_MOVE_WOWE_WESPONDEW:
			w2cap_do_move_wespond(chan, wesuwt);
			bweak;
		defauwt:
			w2cap_do_move_cancew(chan, wesuwt);
			bweak;
		}
	}
}

static inwine int w2cap_move_channew_weq(stwuct w2cap_conn *conn,
					 stwuct w2cap_cmd_hdw *cmd,
					 u16 cmd_wen, void *data)
{
	stwuct w2cap_move_chan_weq *weq = data;
	stwuct w2cap_move_chan_wsp wsp;
	stwuct w2cap_chan *chan;
	u16 icid = 0;
	u16 wesuwt = W2CAP_MW_NOT_AWWOWED;

	if (cmd_wen != sizeof(*weq))
		wetuwn -EPWOTO;

	icid = we16_to_cpu(weq->icid);

	BT_DBG("icid 0x%4.4x, dest_amp_id %d", icid, weq->dest_amp_id);

	if (!(conn->wocaw_fixed_chan & W2CAP_FC_A2MP))
		wetuwn -EINVAW;

	chan = w2cap_get_chan_by_dcid(conn, icid);
	if (!chan) {
		wsp.icid = cpu_to_we16(icid);
		wsp.wesuwt = cpu_to_we16(W2CAP_MW_NOT_AWWOWED);
		w2cap_send_cmd(conn, cmd->ident, W2CAP_MOVE_CHAN_WSP,
			       sizeof(wsp), &wsp);
		wetuwn 0;
	}

	chan->ident = cmd->ident;

	if (chan->scid < W2CAP_CID_DYN_STAWT ||
	    chan->chan_powicy == BT_CHANNEW_POWICY_BWEDW_ONWY ||
	    (chan->mode != W2CAP_MODE_EWTM &&
	     chan->mode != W2CAP_MODE_STWEAMING)) {
		wesuwt = W2CAP_MW_NOT_AWWOWED;
		goto send_move_wesponse;
	}

	if (chan->wocaw_amp_id == weq->dest_amp_id) {
		wesuwt = W2CAP_MW_SAME_ID;
		goto send_move_wesponse;
	}

	if (weq->dest_amp_id != AMP_ID_BWEDW) {
		stwuct hci_dev *hdev;
		hdev = hci_dev_get(weq->dest_amp_id);
		if (!hdev || hdev->dev_type != HCI_AMP ||
		    !test_bit(HCI_UP, &hdev->fwags)) {
			if (hdev)
				hci_dev_put(hdev);

			wesuwt = W2CAP_MW_BAD_ID;
			goto send_move_wesponse;
		}
		hci_dev_put(hdev);
	}

	/* Detect a move cowwision.  Onwy send a cowwision wesponse
	 * if this side has "wost", othewwise pwoceed with the move.
	 * The winnew has the wawgew bd_addw.
	 */
	if ((__chan_is_moving(chan) ||
	     chan->move_wowe != W2CAP_MOVE_WOWE_NONE) &&
	    bacmp(&conn->hcon->swc, &conn->hcon->dst) > 0) {
		wesuwt = W2CAP_MW_COWWISION;
		goto send_move_wesponse;
	}

	chan->move_wowe = W2CAP_MOVE_WOWE_WESPONDEW;
	w2cap_move_setup(chan);
	chan->move_id = weq->dest_amp_id;

	if (weq->dest_amp_id == AMP_ID_BWEDW) {
		/* Moving to BW/EDW */
		if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
			chan->move_state = W2CAP_MOVE_WAIT_WOCAW_BUSY;
			wesuwt = W2CAP_MW_PEND;
		} ewse {
			chan->move_state = W2CAP_MOVE_WAIT_CONFIWM;
			wesuwt = W2CAP_MW_SUCCESS;
		}
	} ewse {
		chan->move_state = W2CAP_MOVE_WAIT_PWEPAWE;
		/* Pwacehowdew - uncomment when amp functions awe avaiwabwe */
		/*amp_accept_physicaw(chan, weq->dest_amp_id);*/
		wesuwt = W2CAP_MW_PEND;
	}

send_move_wesponse:
	w2cap_send_move_chan_wsp(chan, wesuwt);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static void w2cap_move_continue(stwuct w2cap_conn *conn, u16 icid, u16 wesuwt)
{
	stwuct w2cap_chan *chan;
	stwuct hci_chan *hchan = NUWW;

	chan = w2cap_get_chan_by_scid(conn, icid);
	if (!chan) {
		w2cap_send_move_chan_cfm_icid(conn, icid);
		wetuwn;
	}

	__cweaw_chan_timew(chan);
	if (wesuwt == W2CAP_MW_PEND)
		__set_chan_timew(chan, W2CAP_MOVE_EWTX_TIMEOUT);

	switch (chan->move_state) {
	case W2CAP_MOVE_WAIT_WOGICAW_COMP:
		/* Move confiwm wiww be sent when wogicaw wink
		 * is compwete.
		 */
		chan->move_state = W2CAP_MOVE_WAIT_WOGICAW_CFM;
		bweak;
	case W2CAP_MOVE_WAIT_WSP_SUCCESS:
		if (wesuwt == W2CAP_MW_PEND) {
			bweak;
		} ewse if (test_bit(CONN_WOCAW_BUSY,
				    &chan->conn_state)) {
			chan->move_state = W2CAP_MOVE_WAIT_WOCAW_BUSY;
		} ewse {
			/* Wogicaw wink is up ow moving to BW/EDW,
			 * pwoceed with move
			 */
			chan->move_state = W2CAP_MOVE_WAIT_CONFIWM_WSP;
			w2cap_send_move_chan_cfm(chan, W2CAP_MC_CONFIWMED);
		}
		bweak;
	case W2CAP_MOVE_WAIT_WSP:
		/* Moving to AMP */
		if (wesuwt == W2CAP_MW_SUCCESS) {
			/* Wemote is weady, send confiwm immediatewy
			 * aftew wogicaw wink is weady
			 */
			chan->move_state = W2CAP_MOVE_WAIT_WOGICAW_CFM;
		} ewse {
			/* Both wogicaw wink and move success
			 * awe wequiwed to confiwm
			 */
			chan->move_state = W2CAP_MOVE_WAIT_WOGICAW_COMP;
		}

		/* Pwacehowdew - get hci_chan fow wogicaw wink */
		if (!hchan) {
			/* Wogicaw wink not avaiwabwe */
			w2cap_send_move_chan_cfm(chan, W2CAP_MC_UNCONFIWMED);
			bweak;
		}

		/* If the wogicaw wink is not yet connected, do not
		 * send confiwmation.
		 */
		if (hchan->state != BT_CONNECTED)
			bweak;

		/* Wogicaw wink is awweady weady to go */

		chan->hs_hcon = hchan->conn;
		chan->hs_hcon->w2cap_data = chan->conn;

		if (wesuwt == W2CAP_MW_SUCCESS) {
			/* Can confiwm now */
			w2cap_send_move_chan_cfm(chan, W2CAP_MC_CONFIWMED);
		} ewse {
			/* Now onwy need move success
			 * to confiwm
			 */
			chan->move_state = W2CAP_MOVE_WAIT_WSP_SUCCESS;
		}

		w2cap_wogicaw_cfm(chan, hchan, W2CAP_MW_SUCCESS);
		bweak;
	defauwt:
		/* Any othew amp move state means the move faiwed. */
		chan->move_id = chan->wocaw_amp_id;
		w2cap_move_done(chan);
		w2cap_send_move_chan_cfm(chan, W2CAP_MC_UNCONFIWMED);
	}

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

static void w2cap_move_faiw(stwuct w2cap_conn *conn, u8 ident, u16 icid,
			    u16 wesuwt)
{
	stwuct w2cap_chan *chan;

	chan = w2cap_get_chan_by_ident(conn, ident);
	if (!chan) {
		/* Couwd not wocate channew, icid is best guess */
		w2cap_send_move_chan_cfm_icid(conn, icid);
		wetuwn;
	}

	__cweaw_chan_timew(chan);

	if (chan->move_wowe == W2CAP_MOVE_WOWE_INITIATOW) {
		if (wesuwt == W2CAP_MW_COWWISION) {
			chan->move_wowe = W2CAP_MOVE_WOWE_WESPONDEW;
		} ewse {
			/* Cweanup - cancew move */
			chan->move_id = chan->wocaw_amp_id;
			w2cap_move_done(chan);
		}
	}

	w2cap_send_move_chan_cfm(chan, W2CAP_MC_UNCONFIWMED);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

static int w2cap_move_channew_wsp(stwuct w2cap_conn *conn,
				  stwuct w2cap_cmd_hdw *cmd,
				  u16 cmd_wen, void *data)
{
	stwuct w2cap_move_chan_wsp *wsp = data;
	u16 icid, wesuwt;

	if (cmd_wen != sizeof(*wsp))
		wetuwn -EPWOTO;

	icid = we16_to_cpu(wsp->icid);
	wesuwt = we16_to_cpu(wsp->wesuwt);

	BT_DBG("icid 0x%4.4x, wesuwt 0x%4.4x", icid, wesuwt);

	if (wesuwt == W2CAP_MW_SUCCESS || wesuwt == W2CAP_MW_PEND)
		w2cap_move_continue(conn, icid, wesuwt);
	ewse
		w2cap_move_faiw(conn, cmd->ident, icid, wesuwt);

	wetuwn 0;
}

static int w2cap_move_channew_confiwm(stwuct w2cap_conn *conn,
				      stwuct w2cap_cmd_hdw *cmd,
				      u16 cmd_wen, void *data)
{
	stwuct w2cap_move_chan_cfm *cfm = data;
	stwuct w2cap_chan *chan;
	u16 icid, wesuwt;

	if (cmd_wen != sizeof(*cfm))
		wetuwn -EPWOTO;

	icid = we16_to_cpu(cfm->icid);
	wesuwt = we16_to_cpu(cfm->wesuwt);

	BT_DBG("icid 0x%4.4x, wesuwt 0x%4.4x", icid, wesuwt);

	chan = w2cap_get_chan_by_dcid(conn, icid);
	if (!chan) {
		/* Spec wequiwes a wesponse even if the icid was not found */
		w2cap_send_move_chan_cfm_wsp(conn, cmd->ident, icid);
		wetuwn 0;
	}

	if (chan->move_state == W2CAP_MOVE_WAIT_CONFIWM) {
		if (wesuwt == W2CAP_MC_CONFIWMED) {
			chan->wocaw_amp_id = chan->move_id;
			if (chan->wocaw_amp_id == AMP_ID_BWEDW)
				__wewease_wogicaw_wink(chan);
		} ewse {
			chan->move_id = chan->wocaw_amp_id;
		}

		w2cap_move_done(chan);
	}

	w2cap_send_move_chan_cfm_wsp(conn, cmd->ident, icid);

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static inwine int w2cap_move_channew_confiwm_wsp(stwuct w2cap_conn *conn,
						 stwuct w2cap_cmd_hdw *cmd,
						 u16 cmd_wen, void *data)
{
	stwuct w2cap_move_chan_cfm_wsp *wsp = data;
	stwuct w2cap_chan *chan;
	u16 icid;

	if (cmd_wen != sizeof(*wsp))
		wetuwn -EPWOTO;

	icid = we16_to_cpu(wsp->icid);

	BT_DBG("icid 0x%4.4x", icid);

	chan = w2cap_get_chan_by_scid(conn, icid);
	if (!chan)
		wetuwn 0;

	__cweaw_chan_timew(chan);

	if (chan->move_state == W2CAP_MOVE_WAIT_CONFIWM_WSP) {
		chan->wocaw_amp_id = chan->move_id;

		if (chan->wocaw_amp_id == AMP_ID_BWEDW && chan->hs_hchan)
			__wewease_wogicaw_wink(chan);

		w2cap_move_done(chan);
	}

	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static inwine int w2cap_conn_pawam_update_weq(stwuct w2cap_conn *conn,
					      stwuct w2cap_cmd_hdw *cmd,
					      u16 cmd_wen, u8 *data)
{
	stwuct hci_conn *hcon = conn->hcon;
	stwuct w2cap_conn_pawam_update_weq *weq;
	stwuct w2cap_conn_pawam_update_wsp wsp;
	u16 min, max, watency, to_muwtipwiew;
	int eww;

	if (hcon->wowe != HCI_WOWE_MASTEW)
		wetuwn -EINVAW;

	if (cmd_wen != sizeof(stwuct w2cap_conn_pawam_update_weq))
		wetuwn -EPWOTO;

	weq = (stwuct w2cap_conn_pawam_update_weq *) data;
	min		= __we16_to_cpu(weq->min);
	max		= __we16_to_cpu(weq->max);
	watency		= __we16_to_cpu(weq->watency);
	to_muwtipwiew	= __we16_to_cpu(weq->to_muwtipwiew);

	BT_DBG("min 0x%4.4x max 0x%4.4x watency: 0x%4.4x Timeout: 0x%4.4x",
	       min, max, watency, to_muwtipwiew);

	memset(&wsp, 0, sizeof(wsp));

	eww = hci_check_conn_pawams(min, max, watency, to_muwtipwiew);
	if (eww)
		wsp.wesuwt = cpu_to_we16(W2CAP_CONN_PAWAM_WEJECTED);
	ewse
		wsp.wesuwt = cpu_to_we16(W2CAP_CONN_PAWAM_ACCEPTED);

	w2cap_send_cmd(conn, cmd->ident, W2CAP_CONN_PAWAM_UPDATE_WSP,
		       sizeof(wsp), &wsp);

	if (!eww) {
		u8 stowe_hint;

		stowe_hint = hci_we_conn_update(hcon, min, max, watency,
						to_muwtipwiew);
		mgmt_new_conn_pawam(hcon->hdev, &hcon->dst, hcon->dst_type,
				    stowe_hint, min, max, watency,
				    to_muwtipwiew);

	}

	wetuwn 0;
}

static int w2cap_we_connect_wsp(stwuct w2cap_conn *conn,
				stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				u8 *data)
{
	stwuct w2cap_we_conn_wsp *wsp = (stwuct w2cap_we_conn_wsp *) data;
	stwuct hci_conn *hcon = conn->hcon;
	u16 dcid, mtu, mps, cwedits, wesuwt;
	stwuct w2cap_chan *chan;
	int eww, sec_wevew;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	dcid    = __we16_to_cpu(wsp->dcid);
	mtu     = __we16_to_cpu(wsp->mtu);
	mps     = __we16_to_cpu(wsp->mps);
	cwedits = __we16_to_cpu(wsp->cwedits);
	wesuwt  = __we16_to_cpu(wsp->wesuwt);

	if (wesuwt == W2CAP_CW_WE_SUCCESS && (mtu < 23 || mps < 23 ||
					   dcid < W2CAP_CID_DYN_STAWT ||
					   dcid > W2CAP_CID_WE_DYN_END))
		wetuwn -EPWOTO;

	BT_DBG("dcid 0x%4.4x mtu %u mps %u cwedits %u wesuwt 0x%2.2x",
	       dcid, mtu, mps, cwedits, wesuwt);

	mutex_wock(&conn->chan_wock);

	chan = __w2cap_get_chan_by_ident(conn, cmd->ident);
	if (!chan) {
		eww = -EBADSWT;
		goto unwock;
	}

	eww = 0;

	w2cap_chan_wock(chan);

	switch (wesuwt) {
	case W2CAP_CW_WE_SUCCESS:
		if (__w2cap_get_chan_by_dcid(conn, dcid)) {
			eww = -EBADSWT;
			bweak;
		}

		chan->ident = 0;
		chan->dcid = dcid;
		chan->omtu = mtu;
		chan->wemote_mps = mps;
		chan->tx_cwedits = cwedits;
		w2cap_chan_weady(chan);
		bweak;

	case W2CAP_CW_WE_AUTHENTICATION:
	case W2CAP_CW_WE_ENCWYPTION:
		/* If we awweady have MITM pwotection we can't do
		 * anything.
		 */
		if (hcon->sec_wevew > BT_SECUWITY_MEDIUM) {
			w2cap_chan_dew(chan, ECONNWEFUSED);
			bweak;
		}

		sec_wevew = hcon->sec_wevew + 1;
		if (chan->sec_wevew < sec_wevew)
			chan->sec_wevew = sec_wevew;

		/* We'ww need to send a new Connect Wequest */
		cweaw_bit(FWAG_WE_CONN_WEQ_SENT, &chan->fwags);

		smp_conn_secuwity(hcon, chan->sec_wevew);
		bweak;

	defauwt:
		w2cap_chan_dew(chan, ECONNWEFUSED);
		bweak;
	}

	w2cap_chan_unwock(chan);

unwock:
	mutex_unwock(&conn->chan_wock);

	wetuwn eww;
}

static inwine int w2cap_bwedw_sig_cmd(stwuct w2cap_conn *conn,
				      stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				      u8 *data)
{
	int eww = 0;

	switch (cmd->code) {
	case W2CAP_COMMAND_WEJ:
		w2cap_command_wej(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONN_WEQ:
		eww = w2cap_connect_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONN_WSP:
	case W2CAP_CWEATE_CHAN_WSP:
		w2cap_connect_cweate_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONF_WEQ:
		eww = w2cap_config_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONF_WSP:
		w2cap_config_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_DISCONN_WEQ:
		eww = w2cap_disconnect_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_DISCONN_WSP:
		w2cap_disconnect_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_ECHO_WEQ:
		w2cap_send_cmd(conn, cmd->ident, W2CAP_ECHO_WSP, cmd_wen, data);
		bweak;

	case W2CAP_ECHO_WSP:
		bweak;

	case W2CAP_INFO_WEQ:
		eww = w2cap_infowmation_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_INFO_WSP:
		w2cap_infowmation_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CWEATE_CHAN_WEQ:
		eww = w2cap_cweate_channew_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_MOVE_CHAN_WEQ:
		eww = w2cap_move_channew_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_MOVE_CHAN_WSP:
		w2cap_move_channew_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_MOVE_CHAN_CFM:
		eww = w2cap_move_channew_confiwm(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_MOVE_CHAN_CFM_WSP:
		w2cap_move_channew_confiwm_wsp(conn, cmd, cmd_wen, data);
		bweak;

	defauwt:
		BT_EWW("Unknown BW/EDW signawing command 0x%2.2x", cmd->code);
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static int w2cap_we_connect_weq(stwuct w2cap_conn *conn,
				stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				u8 *data)
{
	stwuct w2cap_we_conn_weq *weq = (stwuct w2cap_we_conn_weq *) data;
	stwuct w2cap_we_conn_wsp wsp;
	stwuct w2cap_chan *chan, *pchan;
	u16 dcid, scid, cwedits, mtu, mps;
	__we16 psm;
	u8 wesuwt;

	if (cmd_wen != sizeof(*weq))
		wetuwn -EPWOTO;

	scid = __we16_to_cpu(weq->scid);
	mtu  = __we16_to_cpu(weq->mtu);
	mps  = __we16_to_cpu(weq->mps);
	psm  = weq->psm;
	dcid = 0;
	cwedits = 0;

	if (mtu < 23 || mps < 23)
		wetuwn -EPWOTO;

	BT_DBG("psm 0x%2.2x scid 0x%4.4x mtu %u mps %u", __we16_to_cpu(psm),
	       scid, mtu, mps);

	/* BWUETOOTH COWE SPECIFICATION Vewsion 5.3 | Vow 3, Pawt A
	 * page 1059:
	 *
	 * Vawid wange: 0x0001-0x00ff
	 *
	 * Tabwe 4.15: W2CAP_WE_CWEDIT_BASED_CONNECTION_WEQ SPSM wanges
	 */
	if (!psm || __we16_to_cpu(psm) > W2CAP_PSM_WE_DYN_END) {
		wesuwt = W2CAP_CW_WE_BAD_PSM;
		chan = NUWW;
		goto wesponse;
	}

	/* Check if we have socket wistening on psm */
	pchan = w2cap_gwobaw_chan_by_psm(BT_WISTEN, psm, &conn->hcon->swc,
					 &conn->hcon->dst, WE_WINK);
	if (!pchan) {
		wesuwt = W2CAP_CW_WE_BAD_PSM;
		chan = NUWW;
		goto wesponse;
	}

	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(pchan);

	if (!smp_sufficient_secuwity(conn->hcon, pchan->sec_wevew,
				     SMP_AWWOW_STK)) {
		wesuwt = W2CAP_CW_WE_AUTHENTICATION;
		chan = NUWW;
		goto wesponse_unwock;
	}

	/* Check fow vawid dynamic CID wange */
	if (scid < W2CAP_CID_DYN_STAWT || scid > W2CAP_CID_WE_DYN_END) {
		wesuwt = W2CAP_CW_WE_INVAWID_SCID;
		chan = NUWW;
		goto wesponse_unwock;
	}

	/* Check if we awweady have channew with that dcid */
	if (__w2cap_get_chan_by_dcid(conn, scid)) {
		wesuwt = W2CAP_CW_WE_SCID_IN_USE;
		chan = NUWW;
		goto wesponse_unwock;
	}

	chan = pchan->ops->new_connection(pchan);
	if (!chan) {
		wesuwt = W2CAP_CW_WE_NO_MEM;
		goto wesponse_unwock;
	}

	bacpy(&chan->swc, &conn->hcon->swc);
	bacpy(&chan->dst, &conn->hcon->dst);
	chan->swc_type = bdaddw_swc_type(conn->hcon);
	chan->dst_type = bdaddw_dst_type(conn->hcon);
	chan->psm  = psm;
	chan->dcid = scid;
	chan->omtu = mtu;
	chan->wemote_mps = mps;

	__w2cap_chan_add(conn, chan);

	w2cap_we_fwowctw_init(chan, __we16_to_cpu(weq->cwedits));

	dcid = chan->scid;
	cwedits = chan->wx_cwedits;

	__set_chan_timew(chan, chan->ops->get_sndtimeo(chan));

	chan->ident = cmd->ident;

	if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags)) {
		w2cap_state_change(chan, BT_CONNECT2);
		/* The fowwowing wesuwt vawue is actuawwy not defined
		 * fow WE CoC but we use it to wet the function know
		 * that it shouwd baiw out aftew doing its cweanup
		 * instead of sending a wesponse.
		 */
		wesuwt = W2CAP_CW_PEND;
		chan->ops->defew(chan);
	} ewse {
		w2cap_chan_weady(chan);
		wesuwt = W2CAP_CW_WE_SUCCESS;
	}

wesponse_unwock:
	w2cap_chan_unwock(pchan);
	mutex_unwock(&conn->chan_wock);
	w2cap_chan_put(pchan);

	if (wesuwt == W2CAP_CW_PEND)
		wetuwn 0;

wesponse:
	if (chan) {
		wsp.mtu = cpu_to_we16(chan->imtu);
		wsp.mps = cpu_to_we16(chan->mps);
	} ewse {
		wsp.mtu = 0;
		wsp.mps = 0;
	}

	wsp.dcid    = cpu_to_we16(dcid);
	wsp.cwedits = cpu_to_we16(cwedits);
	wsp.wesuwt  = cpu_to_we16(wesuwt);

	w2cap_send_cmd(conn, cmd->ident, W2CAP_WE_CONN_WSP, sizeof(wsp), &wsp);

	wetuwn 0;
}

static inwine int w2cap_we_cwedits(stwuct w2cap_conn *conn,
				   stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				   u8 *data)
{
	stwuct w2cap_we_cwedits *pkt;
	stwuct w2cap_chan *chan;
	u16 cid, cwedits, max_cwedits;

	if (cmd_wen != sizeof(*pkt))
		wetuwn -EPWOTO;

	pkt = (stwuct w2cap_we_cwedits *) data;
	cid	= __we16_to_cpu(pkt->cid);
	cwedits	= __we16_to_cpu(pkt->cwedits);

	BT_DBG("cid 0x%4.4x cwedits 0x%4.4x", cid, cwedits);

	chan = w2cap_get_chan_by_dcid(conn, cid);
	if (!chan)
		wetuwn -EBADSWT;

	max_cwedits = WE_FWOWCTW_MAX_CWEDITS - chan->tx_cwedits;
	if (cwedits > max_cwedits) {
		BT_EWW("WE cwedits ovewfwow");
		w2cap_send_disconn_weq(chan, ECONNWESET);

		/* Wetuwn 0 so that we don't twiggew an unnecessawy
		 * command weject packet.
		 */
		goto unwock;
	}

	chan->tx_cwedits += cwedits;

	/* Wesume sending */
	w2cap_we_fwowctw_send(chan);

	if (chan->tx_cwedits)
		chan->ops->wesume(chan);

unwock:
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

	wetuwn 0;
}

static inwine int w2cap_ecwed_conn_weq(stwuct w2cap_conn *conn,
				       stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				       u8 *data)
{
	stwuct w2cap_ecwed_conn_weq *weq = (void *) data;
	stwuct {
		stwuct w2cap_ecwed_conn_wsp wsp;
		__we16 dcid[W2CAP_ECWED_MAX_CID];
	} __packed pdu;
	stwuct w2cap_chan *chan, *pchan;
	u16 mtu, mps;
	__we16 psm;
	u8 wesuwt, wen = 0;
	int i, num_scid;
	boow defew = fawse;

	if (!enabwe_ecwed)
		wetuwn -EINVAW;

	if (cmd_wen < sizeof(*weq) || (cmd_wen - sizeof(*weq)) % sizeof(u16)) {
		wesuwt = W2CAP_CW_WE_INVAWID_PAWAMS;
		goto wesponse;
	}

	cmd_wen -= sizeof(*weq);
	num_scid = cmd_wen / sizeof(u16);

	if (num_scid > AWWAY_SIZE(pdu.dcid)) {
		wesuwt = W2CAP_CW_WE_INVAWID_PAWAMS;
		goto wesponse;
	}

	mtu  = __we16_to_cpu(weq->mtu);
	mps  = __we16_to_cpu(weq->mps);

	if (mtu < W2CAP_ECWED_MIN_MTU || mps < W2CAP_ECWED_MIN_MPS) {
		wesuwt = W2CAP_CW_WE_UNACCEPT_PAWAMS;
		goto wesponse;
	}

	psm  = weq->psm;

	/* BWUETOOTH COWE SPECIFICATION Vewsion 5.3 | Vow 3, Pawt A
	 * page 1059:
	 *
	 * Vawid wange: 0x0001-0x00ff
	 *
	 * Tabwe 4.15: W2CAP_WE_CWEDIT_BASED_CONNECTION_WEQ SPSM wanges
	 */
	if (!psm || __we16_to_cpu(psm) > W2CAP_PSM_WE_DYN_END) {
		wesuwt = W2CAP_CW_WE_BAD_PSM;
		goto wesponse;
	}

	BT_DBG("psm 0x%2.2x mtu %u mps %u", __we16_to_cpu(psm), mtu, mps);

	memset(&pdu, 0, sizeof(pdu));

	/* Check if we have socket wistening on psm */
	pchan = w2cap_gwobaw_chan_by_psm(BT_WISTEN, psm, &conn->hcon->swc,
					 &conn->hcon->dst, WE_WINK);
	if (!pchan) {
		wesuwt = W2CAP_CW_WE_BAD_PSM;
		goto wesponse;
	}

	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(pchan);

	if (!smp_sufficient_secuwity(conn->hcon, pchan->sec_wevew,
				     SMP_AWWOW_STK)) {
		wesuwt = W2CAP_CW_WE_AUTHENTICATION;
		goto unwock;
	}

	wesuwt = W2CAP_CW_WE_SUCCESS;

	fow (i = 0; i < num_scid; i++) {
		u16 scid = __we16_to_cpu(weq->scid[i]);

		BT_DBG("scid[%d] 0x%4.4x", i, scid);

		pdu.dcid[i] = 0x0000;
		wen += sizeof(*pdu.dcid);

		/* Check fow vawid dynamic CID wange */
		if (scid < W2CAP_CID_DYN_STAWT || scid > W2CAP_CID_WE_DYN_END) {
			wesuwt = W2CAP_CW_WE_INVAWID_SCID;
			continue;
		}

		/* Check if we awweady have channew with that dcid */
		if (__w2cap_get_chan_by_dcid(conn, scid)) {
			wesuwt = W2CAP_CW_WE_SCID_IN_USE;
			continue;
		}

		chan = pchan->ops->new_connection(pchan);
		if (!chan) {
			wesuwt = W2CAP_CW_WE_NO_MEM;
			continue;
		}

		bacpy(&chan->swc, &conn->hcon->swc);
		bacpy(&chan->dst, &conn->hcon->dst);
		chan->swc_type = bdaddw_swc_type(conn->hcon);
		chan->dst_type = bdaddw_dst_type(conn->hcon);
		chan->psm  = psm;
		chan->dcid = scid;
		chan->omtu = mtu;
		chan->wemote_mps = mps;

		__w2cap_chan_add(conn, chan);

		w2cap_ecwed_init(chan, __we16_to_cpu(weq->cwedits));

		/* Init wesponse */
		if (!pdu.wsp.cwedits) {
			pdu.wsp.mtu = cpu_to_we16(chan->imtu);
			pdu.wsp.mps = cpu_to_we16(chan->mps);
			pdu.wsp.cwedits = cpu_to_we16(chan->wx_cwedits);
		}

		pdu.dcid[i] = cpu_to_we16(chan->scid);

		__set_chan_timew(chan, chan->ops->get_sndtimeo(chan));

		chan->ident = cmd->ident;
		chan->mode = W2CAP_MODE_EXT_FWOWCTW;

		if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags)) {
			w2cap_state_change(chan, BT_CONNECT2);
			defew = twue;
			chan->ops->defew(chan);
		} ewse {
			w2cap_chan_weady(chan);
		}
	}

unwock:
	w2cap_chan_unwock(pchan);
	mutex_unwock(&conn->chan_wock);
	w2cap_chan_put(pchan);

wesponse:
	pdu.wsp.wesuwt = cpu_to_we16(wesuwt);

	if (defew)
		wetuwn 0;

	w2cap_send_cmd(conn, cmd->ident, W2CAP_ECWED_CONN_WSP,
		       sizeof(pdu.wsp) + wen, &pdu);

	wetuwn 0;
}

static inwine int w2cap_ecwed_conn_wsp(stwuct w2cap_conn *conn,
				       stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				       u8 *data)
{
	stwuct w2cap_ecwed_conn_wsp *wsp = (void *) data;
	stwuct hci_conn *hcon = conn->hcon;
	u16 mtu, mps, cwedits, wesuwt;
	stwuct w2cap_chan *chan, *tmp;
	int eww = 0, sec_wevew;
	int i = 0;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	mtu     = __we16_to_cpu(wsp->mtu);
	mps     = __we16_to_cpu(wsp->mps);
	cwedits = __we16_to_cpu(wsp->cwedits);
	wesuwt  = __we16_to_cpu(wsp->wesuwt);

	BT_DBG("mtu %u mps %u cwedits %u wesuwt 0x%4.4x", mtu, mps, cwedits,
	       wesuwt);

	mutex_wock(&conn->chan_wock);

	cmd_wen -= sizeof(*wsp);

	wist_fow_each_entwy_safe(chan, tmp, &conn->chan_w, wist) {
		u16 dcid;

		if (chan->ident != cmd->ident ||
		    chan->mode != W2CAP_MODE_EXT_FWOWCTW ||
		    chan->state == BT_CONNECTED)
			continue;

		w2cap_chan_wock(chan);

		/* Check that thewe is a dcid fow each pending channew */
		if (cmd_wen < sizeof(dcid)) {
			w2cap_chan_dew(chan, ECONNWEFUSED);
			w2cap_chan_unwock(chan);
			continue;
		}

		dcid = __we16_to_cpu(wsp->dcid[i++]);
		cmd_wen -= sizeof(u16);

		BT_DBG("dcid[%d] 0x%4.4x", i, dcid);

		/* Check if dcid is awweady in use */
		if (dcid && __w2cap_get_chan_by_dcid(conn, dcid)) {
			/* If a device weceives a
			 * W2CAP_CWEDIT_BASED_CONNECTION_WSP packet with an
			 * awweady-assigned Destination CID, then both the
			 * owiginaw channew and the new channew shaww be
			 * immediatewy discawded and not used.
			 */
			w2cap_chan_dew(chan, ECONNWEFUSED);
			w2cap_chan_unwock(chan);
			chan = __w2cap_get_chan_by_dcid(conn, dcid);
			w2cap_chan_wock(chan);
			w2cap_chan_dew(chan, ECONNWESET);
			w2cap_chan_unwock(chan);
			continue;
		}

		switch (wesuwt) {
		case W2CAP_CW_WE_AUTHENTICATION:
		case W2CAP_CW_WE_ENCWYPTION:
			/* If we awweady have MITM pwotection we can't do
			 * anything.
			 */
			if (hcon->sec_wevew > BT_SECUWITY_MEDIUM) {
				w2cap_chan_dew(chan, ECONNWEFUSED);
				bweak;
			}

			sec_wevew = hcon->sec_wevew + 1;
			if (chan->sec_wevew < sec_wevew)
				chan->sec_wevew = sec_wevew;

			/* We'ww need to send a new Connect Wequest */
			cweaw_bit(FWAG_ECWED_CONN_WEQ_SENT, &chan->fwags);

			smp_conn_secuwity(hcon, chan->sec_wevew);
			bweak;

		case W2CAP_CW_WE_BAD_PSM:
			w2cap_chan_dew(chan, ECONNWEFUSED);
			bweak;

		defauwt:
			/* If dcid was not set it means channews was wefused */
			if (!dcid) {
				w2cap_chan_dew(chan, ECONNWEFUSED);
				bweak;
			}

			chan->ident = 0;
			chan->dcid = dcid;
			chan->omtu = mtu;
			chan->wemote_mps = mps;
			chan->tx_cwedits = cwedits;
			w2cap_chan_weady(chan);
			bweak;
		}

		w2cap_chan_unwock(chan);
	}

	mutex_unwock(&conn->chan_wock);

	wetuwn eww;
}

static inwine int w2cap_ecwed_weconf_weq(stwuct w2cap_conn *conn,
					 stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
					 u8 *data)
{
	stwuct w2cap_ecwed_weconf_weq *weq = (void *) data;
	stwuct w2cap_ecwed_weconf_wsp wsp;
	u16 mtu, mps, wesuwt;
	stwuct w2cap_chan *chan;
	int i, num_scid;

	if (!enabwe_ecwed)
		wetuwn -EINVAW;

	if (cmd_wen < sizeof(*weq) || cmd_wen - sizeof(*weq) % sizeof(u16)) {
		wesuwt = W2CAP_CW_WE_INVAWID_PAWAMS;
		goto wespond;
	}

	mtu = __we16_to_cpu(weq->mtu);
	mps = __we16_to_cpu(weq->mps);

	BT_DBG("mtu %u mps %u", mtu, mps);

	if (mtu < W2CAP_ECWED_MIN_MTU) {
		wesuwt = W2CAP_WECONF_INVAWID_MTU;
		goto wespond;
	}

	if (mps < W2CAP_ECWED_MIN_MPS) {
		wesuwt = W2CAP_WECONF_INVAWID_MPS;
		goto wespond;
	}

	cmd_wen -= sizeof(*weq);
	num_scid = cmd_wen / sizeof(u16);
	wesuwt = W2CAP_WECONF_SUCCESS;

	fow (i = 0; i < num_scid; i++) {
		u16 scid;

		scid = __we16_to_cpu(weq->scid[i]);
		if (!scid)
			wetuwn -EPWOTO;

		chan = __w2cap_get_chan_by_dcid(conn, scid);
		if (!chan)
			continue;

		/* If the MTU vawue is decweased fow any of the incwuded
		 * channews, then the weceivew shaww disconnect aww
		 * incwuded channews.
		 */
		if (chan->omtu > mtu) {
			BT_EWW("chan %p decweased MTU %u -> %u", chan,
			       chan->omtu, mtu);
			wesuwt = W2CAP_WECONF_INVAWID_MTU;
		}

		chan->omtu = mtu;
		chan->wemote_mps = mps;
	}

wespond:
	wsp.wesuwt = cpu_to_we16(wesuwt);

	w2cap_send_cmd(conn, cmd->ident, W2CAP_ECWED_WECONF_WSP, sizeof(wsp),
		       &wsp);

	wetuwn 0;
}

static inwine int w2cap_ecwed_weconf_wsp(stwuct w2cap_conn *conn,
					 stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
					 u8 *data)
{
	stwuct w2cap_chan *chan, *tmp;
	stwuct w2cap_ecwed_conn_wsp *wsp = (void *) data;
	u16 wesuwt;

	if (cmd_wen < sizeof(*wsp))
		wetuwn -EPWOTO;

	wesuwt = __we16_to_cpu(wsp->wesuwt);

	BT_DBG("wesuwt 0x%4.4x", wsp->wesuwt);

	if (!wesuwt)
		wetuwn 0;

	wist_fow_each_entwy_safe(chan, tmp, &conn->chan_w, wist) {
		if (chan->ident != cmd->ident)
			continue;

		w2cap_chan_dew(chan, ECONNWESET);
	}

	wetuwn 0;
}

static inwine int w2cap_we_command_wej(stwuct w2cap_conn *conn,
				       stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				       u8 *data)
{
	stwuct w2cap_cmd_wej_unk *wej = (stwuct w2cap_cmd_wej_unk *) data;
	stwuct w2cap_chan *chan;

	if (cmd_wen < sizeof(*wej))
		wetuwn -EPWOTO;

	mutex_wock(&conn->chan_wock);

	chan = __w2cap_get_chan_by_ident(conn, cmd->ident);
	if (!chan)
		goto done;

	chan = w2cap_chan_howd_unwess_zewo(chan);
	if (!chan)
		goto done;

	w2cap_chan_wock(chan);
	w2cap_chan_dew(chan, ECONNWEFUSED);
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);

done:
	mutex_unwock(&conn->chan_wock);
	wetuwn 0;
}

static inwine int w2cap_we_sig_cmd(stwuct w2cap_conn *conn,
				   stwuct w2cap_cmd_hdw *cmd, u16 cmd_wen,
				   u8 *data)
{
	int eww = 0;

	switch (cmd->code) {
	case W2CAP_COMMAND_WEJ:
		w2cap_we_command_wej(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONN_PAWAM_UPDATE_WEQ:
		eww = w2cap_conn_pawam_update_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_CONN_PAWAM_UPDATE_WSP:
		bweak;

	case W2CAP_WE_CONN_WSP:
		w2cap_we_connect_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_WE_CONN_WEQ:
		eww = w2cap_we_connect_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_WE_CWEDITS:
		eww = w2cap_we_cwedits(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_ECWED_CONN_WEQ:
		eww = w2cap_ecwed_conn_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_ECWED_CONN_WSP:
		eww = w2cap_ecwed_conn_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_ECWED_WECONF_WEQ:
		eww = w2cap_ecwed_weconf_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_ECWED_WECONF_WSP:
		eww = w2cap_ecwed_weconf_wsp(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_DISCONN_WEQ:
		eww = w2cap_disconnect_weq(conn, cmd, cmd_wen, data);
		bweak;

	case W2CAP_DISCONN_WSP:
		w2cap_disconnect_wsp(conn, cmd, cmd_wen, data);
		bweak;

	defauwt:
		BT_EWW("Unknown WE signawing command 0x%2.2x", cmd->code);
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static inwine void w2cap_we_sig_channew(stwuct w2cap_conn *conn,
					stwuct sk_buff *skb)
{
	stwuct hci_conn *hcon = conn->hcon;
	stwuct w2cap_cmd_hdw *cmd;
	u16 wen;
	int eww;

	if (hcon->type != WE_WINK)
		goto dwop;

	if (skb->wen < W2CAP_CMD_HDW_SIZE)
		goto dwop;

	cmd = (void *) skb->data;
	skb_puww(skb, W2CAP_CMD_HDW_SIZE);

	wen = we16_to_cpu(cmd->wen);

	BT_DBG("code 0x%2.2x wen %d id 0x%2.2x", cmd->code, wen, cmd->ident);

	if (wen != skb->wen || !cmd->ident) {
		BT_DBG("cowwupted command");
		goto dwop;
	}

	eww = w2cap_we_sig_cmd(conn, cmd, wen, skb->data);
	if (eww) {
		stwuct w2cap_cmd_wej_unk wej;

		BT_EWW("Wwong wink type (%d)", eww);

		wej.weason = cpu_to_we16(W2CAP_WEJ_NOT_UNDEWSTOOD);
		w2cap_send_cmd(conn, cmd->ident, W2CAP_COMMAND_WEJ,
			       sizeof(wej), &wej);
	}

dwop:
	kfwee_skb(skb);
}

static inwine void w2cap_sig_send_wej(stwuct w2cap_conn *conn, u16 ident)
{
	stwuct w2cap_cmd_wej_unk wej;

	wej.weason = cpu_to_we16(W2CAP_WEJ_NOT_UNDEWSTOOD);
	w2cap_send_cmd(conn, ident, W2CAP_COMMAND_WEJ, sizeof(wej), &wej);
}

static inwine void w2cap_sig_channew(stwuct w2cap_conn *conn,
				     stwuct sk_buff *skb)
{
	stwuct hci_conn *hcon = conn->hcon;
	stwuct w2cap_cmd_hdw *cmd;
	int eww;

	w2cap_waw_wecv(conn, skb);

	if (hcon->type != ACW_WINK)
		goto dwop;

	whiwe (skb->wen >= W2CAP_CMD_HDW_SIZE) {
		u16 wen;

		cmd = (void *) skb->data;
		skb_puww(skb, W2CAP_CMD_HDW_SIZE);

		wen = we16_to_cpu(cmd->wen);

		BT_DBG("code 0x%2.2x wen %d id 0x%2.2x", cmd->code, wen,
		       cmd->ident);

		if (wen > skb->wen || !cmd->ident) {
			BT_DBG("cowwupted command");
			w2cap_sig_send_wej(conn, cmd->ident);
			skb_puww(skb, wen > skb->wen ? skb->wen : wen);
			continue;
		}

		eww = w2cap_bwedw_sig_cmd(conn, cmd, wen, skb->data);
		if (eww) {
			BT_EWW("Wwong wink type (%d)", eww);
			w2cap_sig_send_wej(conn, cmd->ident);
		}

		skb_puww(skb, wen);
	}

	if (skb->wen > 0) {
		BT_DBG("cowwupted command");
		w2cap_sig_send_wej(conn, 0);
	}

dwop:
	kfwee_skb(skb);
}

static int w2cap_check_fcs(stwuct w2cap_chan *chan,  stwuct sk_buff *skb)
{
	u16 ouw_fcs, wcv_fcs;
	int hdw_size;

	if (test_bit(FWAG_EXT_CTWW, &chan->fwags))
		hdw_size = W2CAP_EXT_HDW_SIZE;
	ewse
		hdw_size = W2CAP_ENH_HDW_SIZE;

	if (chan->fcs == W2CAP_FCS_CWC16) {
		skb_twim(skb, skb->wen - W2CAP_FCS_SIZE);
		wcv_fcs = get_unawigned_we16(skb->data + skb->wen);
		ouw_fcs = cwc16(0, skb->data - hdw_size, skb->wen + hdw_size);

		if (ouw_fcs != wcv_fcs)
			wetuwn -EBADMSG;
	}
	wetuwn 0;
}

static void w2cap_send_i_ow_ww_ow_wnw(stwuct w2cap_chan *chan)
{
	stwuct w2cap_ctww contwow;

	BT_DBG("chan %p", chan);

	memset(&contwow, 0, sizeof(contwow));
	contwow.sfwame = 1;
	contwow.finaw = 1;
	contwow.weqseq = chan->buffew_seq;
	set_bit(CONN_SEND_FBIT, &chan->conn_state);

	if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
		contwow.supew = W2CAP_SUPEW_WNW;
		w2cap_send_sfwame(chan, &contwow);
	}

	if (test_and_cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state) &&
	    chan->unacked_fwames > 0)
		__set_wetwans_timew(chan);

	/* Send pending ifwames */
	w2cap_ewtm_send(chan);

	if (!test_bit(CONN_WOCAW_BUSY, &chan->conn_state) &&
	    test_bit(CONN_SEND_FBIT, &chan->conn_state)) {
		/* F-bit wasn't sent in an s-fwame ow i-fwame yet, so
		 * send it now.
		 */
		contwow.supew = W2CAP_SUPEW_WW;
		w2cap_send_sfwame(chan, &contwow);
	}
}

static void append_skb_fwag(stwuct sk_buff *skb, stwuct sk_buff *new_fwag,
			    stwuct sk_buff **wast_fwag)
{
	/* skb->wen wefwects data in skb as weww as aww fwagments
	 * skb->data_wen wefwects onwy data in fwagments
	 */
	if (!skb_has_fwag_wist(skb))
		skb_shinfo(skb)->fwag_wist = new_fwag;

	new_fwag->next = NUWW;

	(*wast_fwag)->next = new_fwag;
	*wast_fwag = new_fwag;

	skb->wen += new_fwag->wen;
	skb->data_wen += new_fwag->wen;
	skb->twuesize += new_fwag->twuesize;
}

static int w2cap_weassembwe_sdu(stwuct w2cap_chan *chan, stwuct sk_buff *skb,
				stwuct w2cap_ctww *contwow)
{
	int eww = -EINVAW;

	switch (contwow->saw) {
	case W2CAP_SAW_UNSEGMENTED:
		if (chan->sdu)
			bweak;

		eww = chan->ops->wecv(chan, skb);
		bweak;

	case W2CAP_SAW_STAWT:
		if (chan->sdu)
			bweak;

		if (!pskb_may_puww(skb, W2CAP_SDUWEN_SIZE))
			bweak;

		chan->sdu_wen = get_unawigned_we16(skb->data);
		skb_puww(skb, W2CAP_SDUWEN_SIZE);

		if (chan->sdu_wen > chan->imtu) {
			eww = -EMSGSIZE;
			bweak;
		}

		if (skb->wen >= chan->sdu_wen)
			bweak;

		chan->sdu = skb;
		chan->sdu_wast_fwag = skb;

		skb = NUWW;
		eww = 0;
		bweak;

	case W2CAP_SAW_CONTINUE:
		if (!chan->sdu)
			bweak;

		append_skb_fwag(chan->sdu, skb,
				&chan->sdu_wast_fwag);
		skb = NUWW;

		if (chan->sdu->wen >= chan->sdu_wen)
			bweak;

		eww = 0;
		bweak;

	case W2CAP_SAW_END:
		if (!chan->sdu)
			bweak;

		append_skb_fwag(chan->sdu, skb,
				&chan->sdu_wast_fwag);
		skb = NUWW;

		if (chan->sdu->wen != chan->sdu_wen)
			bweak;

		eww = chan->ops->wecv(chan, chan->sdu);

		if (!eww) {
			/* Weassembwy compwete */
			chan->sdu = NUWW;
			chan->sdu_wast_fwag = NUWW;
			chan->sdu_wen = 0;
		}
		bweak;
	}

	if (eww) {
		kfwee_skb(skb);
		kfwee_skb(chan->sdu);
		chan->sdu = NUWW;
		chan->sdu_wast_fwag = NUWW;
		chan->sdu_wen = 0;
	}

	wetuwn eww;
}

static int w2cap_wesegment(stwuct w2cap_chan *chan)
{
	/* Pwacehowdew */
	wetuwn 0;
}

void w2cap_chan_busy(stwuct w2cap_chan *chan, int busy)
{
	u8 event;

	if (chan->mode != W2CAP_MODE_EWTM)
		wetuwn;

	event = busy ? W2CAP_EV_WOCAW_BUSY_DETECTED : W2CAP_EV_WOCAW_BUSY_CWEAW;
	w2cap_tx(chan, NUWW, NUWW, event);
}

static int w2cap_wx_queued_ifwames(stwuct w2cap_chan *chan)
{
	int eww = 0;
	/* Pass sequentiaw fwames to w2cap_weassembwe_sdu()
	 * untiw a gap is encountewed.
	 */

	BT_DBG("chan %p", chan);

	whiwe (!test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
		stwuct sk_buff *skb;
		BT_DBG("Seawching fow skb with txseq %d (queue wen %d)",
		       chan->buffew_seq, skb_queue_wen(&chan->swej_q));

		skb = w2cap_ewtm_seq_in_queue(&chan->swej_q, chan->buffew_seq);

		if (!skb)
			bweak;

		skb_unwink(skb, &chan->swej_q);
		chan->buffew_seq = __next_seq(chan, chan->buffew_seq);
		eww = w2cap_weassembwe_sdu(chan, skb, &bt_cb(skb)->w2cap);
		if (eww)
			bweak;
	}

	if (skb_queue_empty(&chan->swej_q)) {
		chan->wx_state = W2CAP_WX_STATE_WECV;
		w2cap_send_ack(chan);
	}

	wetuwn eww;
}

static void w2cap_handwe_swej(stwuct w2cap_chan *chan,
			      stwuct w2cap_ctww *contwow)
{
	stwuct sk_buff *skb;

	BT_DBG("chan %p, contwow %p", chan, contwow);

	if (contwow->weqseq == chan->next_tx_seq) {
		BT_DBG("Invawid weqseq %d, disconnecting", contwow->weqseq);
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn;
	}

	skb = w2cap_ewtm_seq_in_queue(&chan->tx_q, contwow->weqseq);

	if (skb == NUWW) {
		BT_DBG("Seq %d not avaiwabwe fow wetwansmission",
		       contwow->weqseq);
		wetuwn;
	}

	if (chan->max_tx != 0 && bt_cb(skb)->w2cap.wetwies >= chan->max_tx) {
		BT_DBG("Wetwy wimit exceeded (%d)", chan->max_tx);
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn;
	}

	cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state);

	if (contwow->poww) {
		w2cap_pass_to_tx(chan, contwow);

		set_bit(CONN_SEND_FBIT, &chan->conn_state);
		w2cap_wetwansmit(chan, contwow);
		w2cap_ewtm_send(chan);

		if (chan->tx_state == W2CAP_TX_STATE_WAIT_F) {
			set_bit(CONN_SWEJ_ACT, &chan->conn_state);
			chan->swej_save_weqseq = contwow->weqseq;
		}
	} ewse {
		w2cap_pass_to_tx_fbit(chan, contwow);

		if (contwow->finaw) {
			if (chan->swej_save_weqseq != contwow->weqseq ||
			    !test_and_cweaw_bit(CONN_SWEJ_ACT,
						&chan->conn_state))
				w2cap_wetwansmit(chan, contwow);
		} ewse {
			w2cap_wetwansmit(chan, contwow);
			if (chan->tx_state == W2CAP_TX_STATE_WAIT_F) {
				set_bit(CONN_SWEJ_ACT, &chan->conn_state);
				chan->swej_save_weqseq = contwow->weqseq;
			}
		}
	}
}

static void w2cap_handwe_wej(stwuct w2cap_chan *chan,
			     stwuct w2cap_ctww *contwow)
{
	stwuct sk_buff *skb;

	BT_DBG("chan %p, contwow %p", chan, contwow);

	if (contwow->weqseq == chan->next_tx_seq) {
		BT_DBG("Invawid weqseq %d, disconnecting", contwow->weqseq);
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn;
	}

	skb = w2cap_ewtm_seq_in_queue(&chan->tx_q, contwow->weqseq);

	if (chan->max_tx && skb &&
	    bt_cb(skb)->w2cap.wetwies >= chan->max_tx) {
		BT_DBG("Wetwy wimit exceeded (%d)", chan->max_tx);
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn;
	}

	cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state);

	w2cap_pass_to_tx(chan, contwow);

	if (contwow->finaw) {
		if (!test_and_cweaw_bit(CONN_WEJ_ACT, &chan->conn_state))
			w2cap_wetwansmit_aww(chan, contwow);
	} ewse {
		w2cap_wetwansmit_aww(chan, contwow);
		w2cap_ewtm_send(chan);
		if (chan->tx_state == W2CAP_TX_STATE_WAIT_F)
			set_bit(CONN_WEJ_ACT, &chan->conn_state);
	}
}

static u8 w2cap_cwassify_txseq(stwuct w2cap_chan *chan, u16 txseq)
{
	BT_DBG("chan %p, txseq %d", chan, txseq);

	BT_DBG("wast_acked_seq %d, expected_tx_seq %d", chan->wast_acked_seq,
	       chan->expected_tx_seq);

	if (chan->wx_state == W2CAP_WX_STATE_SWEJ_SENT) {
		if (__seq_offset(chan, txseq, chan->wast_acked_seq) >=
		    chan->tx_win) {
			/* See notes bewow wegawding "doubwe poww" and
			 * invawid packets.
			 */
			if (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) {
				BT_DBG("Invawid/Ignowe - aftew SWEJ");
				wetuwn W2CAP_TXSEQ_INVAWID_IGNOWE;
			} ewse {
				BT_DBG("Invawid - in window aftew SWEJ sent");
				wetuwn W2CAP_TXSEQ_INVAWID;
			}
		}

		if (chan->swej_wist.head == txseq) {
			BT_DBG("Expected SWEJ");
			wetuwn W2CAP_TXSEQ_EXPECTED_SWEJ;
		}

		if (w2cap_ewtm_seq_in_queue(&chan->swej_q, txseq)) {
			BT_DBG("Dupwicate SWEJ - txseq awweady stowed");
			wetuwn W2CAP_TXSEQ_DUPWICATE_SWEJ;
		}

		if (w2cap_seq_wist_contains(&chan->swej_wist, txseq)) {
			BT_DBG("Unexpected SWEJ - not wequested");
			wetuwn W2CAP_TXSEQ_UNEXPECTED_SWEJ;
		}
	}

	if (chan->expected_tx_seq == txseq) {
		if (__seq_offset(chan, txseq, chan->wast_acked_seq) >=
		    chan->tx_win) {
			BT_DBG("Invawid - txseq outside tx window");
			wetuwn W2CAP_TXSEQ_INVAWID;
		} ewse {
			BT_DBG("Expected");
			wetuwn W2CAP_TXSEQ_EXPECTED;
		}
	}

	if (__seq_offset(chan, txseq, chan->wast_acked_seq) <
	    __seq_offset(chan, chan->expected_tx_seq, chan->wast_acked_seq)) {
		BT_DBG("Dupwicate - expected_tx_seq watew than txseq");
		wetuwn W2CAP_TXSEQ_DUPWICATE;
	}

	if (__seq_offset(chan, txseq, chan->wast_acked_seq) >= chan->tx_win) {
		/* A souwce of invawid packets is a "doubwe poww" condition,
		 * whewe deways cause us to send muwtipwe poww packets.  If
		 * the wemote stack weceives and pwocesses both powws,
		 * sequence numbews can wwap awound in such a way that a
		 * wesent fwame has a sequence numbew that wooks wike new data
		 * with a sequence gap.  This wouwd twiggew an ewwoneous SWEJ
		 * wequest.
		 *
		 * Fowtunatewy, this is impossibwe with a tx window that's
		 * wess than hawf of the maximum sequence numbew, which awwows
		 * invawid fwames to be safewy ignowed.
		 *
		 * With tx window sizes gweatew than hawf of the tx window
		 * maximum, the fwame is invawid and cannot be ignowed.  This
		 * causes a disconnect.
		 */

		if (chan->tx_win <= ((chan->tx_win_max + 1) >> 1)) {
			BT_DBG("Invawid/Ignowe - txseq outside tx window");
			wetuwn W2CAP_TXSEQ_INVAWID_IGNOWE;
		} ewse {
			BT_DBG("Invawid - txseq outside tx window");
			wetuwn W2CAP_TXSEQ_INVAWID;
		}
	} ewse {
		BT_DBG("Unexpected - txseq indicates missing fwames");
		wetuwn W2CAP_TXSEQ_UNEXPECTED;
	}
}

static int w2cap_wx_state_wecv(stwuct w2cap_chan *chan,
			       stwuct w2cap_ctww *contwow,
			       stwuct sk_buff *skb, u8 event)
{
	stwuct w2cap_ctww wocaw_contwow;
	int eww = 0;
	boow skb_in_use = fawse;

	BT_DBG("chan %p, contwow %p, skb %p, event %d", chan, contwow, skb,
	       event);

	switch (event) {
	case W2CAP_EV_WECV_IFWAME:
		switch (w2cap_cwassify_txseq(chan, contwow->txseq)) {
		case W2CAP_TXSEQ_EXPECTED:
			w2cap_pass_to_tx(chan, contwow);

			if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
				BT_DBG("Busy, discawding expected seq %d",
				       contwow->txseq);
				bweak;
			}

			chan->expected_tx_seq = __next_seq(chan,
							   contwow->txseq);

			chan->buffew_seq = chan->expected_tx_seq;
			skb_in_use = twue;

			/* w2cap_weassembwe_sdu may fwee skb, hence invawidate
			 * contwow, so make a copy in advance to use it aftew
			 * w2cap_weassembwe_sdu wetuwns and to avoid the wace
			 * condition, fow exampwe:
			 *
			 * The cuwwent thwead cawws:
			 *   w2cap_weassembwe_sdu
			 *     chan->ops->wecv == w2cap_sock_wecv_cb
			 *       __sock_queue_wcv_skb
			 * Anothew thwead cawws:
			 *   bt_sock_wecvmsg
			 *     skb_wecv_datagwam
			 *     skb_fwee_datagwam
			 * Then the cuwwent thwead twies to access contwow, but
			 * it was fweed by skb_fwee_datagwam.
			 */
			wocaw_contwow = *contwow;
			eww = w2cap_weassembwe_sdu(chan, skb, contwow);
			if (eww)
				bweak;

			if (wocaw_contwow.finaw) {
				if (!test_and_cweaw_bit(CONN_WEJ_ACT,
							&chan->conn_state)) {
					wocaw_contwow.finaw = 0;
					w2cap_wetwansmit_aww(chan, &wocaw_contwow);
					w2cap_ewtm_send(chan);
				}
			}

			if (!test_bit(CONN_WOCAW_BUSY, &chan->conn_state))
				w2cap_send_ack(chan);
			bweak;
		case W2CAP_TXSEQ_UNEXPECTED:
			w2cap_pass_to_tx(chan, contwow);

			/* Can't issue SWEJ fwames in the wocaw busy state.
			 * Dwop this fwame, it wiww be seen as missing
			 * when wocaw busy is exited.
			 */
			if (test_bit(CONN_WOCAW_BUSY, &chan->conn_state)) {
				BT_DBG("Busy, discawding unexpected seq %d",
				       contwow->txseq);
				bweak;
			}

			/* Thewe was a gap in the sequence, so an SWEJ
			 * must be sent fow each missing fwame.  The
			 * cuwwent fwame is stowed fow watew use.
			 */
			skb_queue_taiw(&chan->swej_q, skb);
			skb_in_use = twue;
			BT_DBG("Queued %p (queue wen %d)", skb,
			       skb_queue_wen(&chan->swej_q));

			cweaw_bit(CONN_SWEJ_ACT, &chan->conn_state);
			w2cap_seq_wist_cweaw(&chan->swej_wist);
			w2cap_send_swej(chan, contwow->txseq);

			chan->wx_state = W2CAP_WX_STATE_SWEJ_SENT;
			bweak;
		case W2CAP_TXSEQ_DUPWICATE:
			w2cap_pass_to_tx(chan, contwow);
			bweak;
		case W2CAP_TXSEQ_INVAWID_IGNOWE:
			bweak;
		case W2CAP_TXSEQ_INVAWID:
		defauwt:
			w2cap_send_disconn_weq(chan, ECONNWESET);
			bweak;
		}
		bweak;
	case W2CAP_EV_WECV_WW:
		w2cap_pass_to_tx(chan, contwow);
		if (contwow->finaw) {
			cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state);

			if (!test_and_cweaw_bit(CONN_WEJ_ACT, &chan->conn_state) &&
			    !__chan_is_moving(chan)) {
				contwow->finaw = 0;
				w2cap_wetwansmit_aww(chan, contwow);
			}

			w2cap_ewtm_send(chan);
		} ewse if (contwow->poww) {
			w2cap_send_i_ow_ww_ow_wnw(chan);
		} ewse {
			if (test_and_cweaw_bit(CONN_WEMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_fwames)
				__set_wetwans_timew(chan);

			w2cap_ewtm_send(chan);
		}
		bweak;
	case W2CAP_EV_WECV_WNW:
		set_bit(CONN_WEMOTE_BUSY, &chan->conn_state);
		w2cap_pass_to_tx(chan, contwow);
		if (contwow && contwow->poww) {
			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			w2cap_send_ww_ow_wnw(chan, 0);
		}
		__cweaw_wetwans_timew(chan);
		w2cap_seq_wist_cweaw(&chan->wetwans_wist);
		bweak;
	case W2CAP_EV_WECV_WEJ:
		w2cap_handwe_wej(chan, contwow);
		bweak;
	case W2CAP_EV_WECV_SWEJ:
		w2cap_handwe_swej(chan, contwow);
		bweak;
	defauwt:
		bweak;
	}

	if (skb && !skb_in_use) {
		BT_DBG("Fweeing %p", skb);
		kfwee_skb(skb);
	}

	wetuwn eww;
}

static int w2cap_wx_state_swej_sent(stwuct w2cap_chan *chan,
				    stwuct w2cap_ctww *contwow,
				    stwuct sk_buff *skb, u8 event)
{
	int eww = 0;
	u16 txseq = contwow->txseq;
	boow skb_in_use = fawse;

	BT_DBG("chan %p, contwow %p, skb %p, event %d", chan, contwow, skb,
	       event);

	switch (event) {
	case W2CAP_EV_WECV_IFWAME:
		switch (w2cap_cwassify_txseq(chan, txseq)) {
		case W2CAP_TXSEQ_EXPECTED:
			/* Keep fwame fow weassembwy watew */
			w2cap_pass_to_tx(chan, contwow);
			skb_queue_taiw(&chan->swej_q, skb);
			skb_in_use = twue;
			BT_DBG("Queued %p (queue wen %d)", skb,
			       skb_queue_wen(&chan->swej_q));

			chan->expected_tx_seq = __next_seq(chan, txseq);
			bweak;
		case W2CAP_TXSEQ_EXPECTED_SWEJ:
			w2cap_seq_wist_pop(&chan->swej_wist);

			w2cap_pass_to_tx(chan, contwow);
			skb_queue_taiw(&chan->swej_q, skb);
			skb_in_use = twue;
			BT_DBG("Queued %p (queue wen %d)", skb,
			       skb_queue_wen(&chan->swej_q));

			eww = w2cap_wx_queued_ifwames(chan);
			if (eww)
				bweak;

			bweak;
		case W2CAP_TXSEQ_UNEXPECTED:
			/* Got a fwame that can't be weassembwed yet.
			 * Save it fow watew, and send SWEJs to covew
			 * the missing fwames.
			 */
			skb_queue_taiw(&chan->swej_q, skb);
			skb_in_use = twue;
			BT_DBG("Queued %p (queue wen %d)", skb,
			       skb_queue_wen(&chan->swej_q));

			w2cap_pass_to_tx(chan, contwow);
			w2cap_send_swej(chan, contwow->txseq);
			bweak;
		case W2CAP_TXSEQ_UNEXPECTED_SWEJ:
			/* This fwame was wequested with an SWEJ, but
			 * some expected wetwansmitted fwames awe
			 * missing.  Wequest wetwansmission of missing
			 * SWEJ'd fwames.
			 */
			skb_queue_taiw(&chan->swej_q, skb);
			skb_in_use = twue;
			BT_DBG("Queued %p (queue wen %d)", skb,
			       skb_queue_wen(&chan->swej_q));

			w2cap_pass_to_tx(chan, contwow);
			w2cap_send_swej_wist(chan, contwow->txseq);
			bweak;
		case W2CAP_TXSEQ_DUPWICATE_SWEJ:
			/* We've awweady queued this fwame.  Dwop this copy. */
			w2cap_pass_to_tx(chan, contwow);
			bweak;
		case W2CAP_TXSEQ_DUPWICATE:
			/* Expecting a watew sequence numbew, so this fwame
			 * was awweady weceived.  Ignowe it compwetewy.
			 */
			bweak;
		case W2CAP_TXSEQ_INVAWID_IGNOWE:
			bweak;
		case W2CAP_TXSEQ_INVAWID:
		defauwt:
			w2cap_send_disconn_weq(chan, ECONNWESET);
			bweak;
		}
		bweak;
	case W2CAP_EV_WECV_WW:
		w2cap_pass_to_tx(chan, contwow);
		if (contwow->finaw) {
			cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state);

			if (!test_and_cweaw_bit(CONN_WEJ_ACT,
						&chan->conn_state)) {
				contwow->finaw = 0;
				w2cap_wetwansmit_aww(chan, contwow);
			}

			w2cap_ewtm_send(chan);
		} ewse if (contwow->poww) {
			if (test_and_cweaw_bit(CONN_WEMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_fwames) {
				__set_wetwans_timew(chan);
			}

			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			w2cap_send_swej_taiw(chan);
		} ewse {
			if (test_and_cweaw_bit(CONN_WEMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_fwames)
				__set_wetwans_timew(chan);

			w2cap_send_ack(chan);
		}
		bweak;
	case W2CAP_EV_WECV_WNW:
		set_bit(CONN_WEMOTE_BUSY, &chan->conn_state);
		w2cap_pass_to_tx(chan, contwow);
		if (contwow->poww) {
			w2cap_send_swej_taiw(chan);
		} ewse {
			stwuct w2cap_ctww ww_contwow;
			memset(&ww_contwow, 0, sizeof(ww_contwow));
			ww_contwow.sfwame = 1;
			ww_contwow.supew = W2CAP_SUPEW_WW;
			ww_contwow.weqseq = chan->buffew_seq;
			w2cap_send_sfwame(chan, &ww_contwow);
		}

		bweak;
	case W2CAP_EV_WECV_WEJ:
		w2cap_handwe_wej(chan, contwow);
		bweak;
	case W2CAP_EV_WECV_SWEJ:
		w2cap_handwe_swej(chan, contwow);
		bweak;
	}

	if (skb && !skb_in_use) {
		BT_DBG("Fweeing %p", skb);
		kfwee_skb(skb);
	}

	wetuwn eww;
}

static int w2cap_finish_move(stwuct w2cap_chan *chan)
{
	BT_DBG("chan %p", chan);

	chan->wx_state = W2CAP_WX_STATE_WECV;

	if (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->bwock_mtu;
	ewse
		chan->conn->mtu = chan->conn->hcon->hdev->acw_mtu;

	wetuwn w2cap_wesegment(chan);
}

static int w2cap_wx_state_wait_p(stwuct w2cap_chan *chan,
				 stwuct w2cap_ctww *contwow,
				 stwuct sk_buff *skb, u8 event)
{
	int eww;

	BT_DBG("chan %p, contwow %p, skb %p, event %d", chan, contwow, skb,
	       event);

	if (!contwow->poww)
		wetuwn -EPWOTO;

	w2cap_pwocess_weqseq(chan, contwow->weqseq);

	if (!skb_queue_empty(&chan->tx_q))
		chan->tx_send_head = skb_peek(&chan->tx_q);
	ewse
		chan->tx_send_head = NUWW;

	/* Wewind next_tx_seq to the point expected
	 * by the weceivew.
	 */
	chan->next_tx_seq = contwow->weqseq;
	chan->unacked_fwames = 0;

	eww = w2cap_finish_move(chan);
	if (eww)
		wetuwn eww;

	set_bit(CONN_SEND_FBIT, &chan->conn_state);
	w2cap_send_i_ow_ww_ow_wnw(chan);

	if (event == W2CAP_EV_WECV_IFWAME)
		wetuwn -EPWOTO;

	wetuwn w2cap_wx_state_wecv(chan, contwow, NUWW, event);
}

static int w2cap_wx_state_wait_f(stwuct w2cap_chan *chan,
				 stwuct w2cap_ctww *contwow,
				 stwuct sk_buff *skb, u8 event)
{
	int eww;

	if (!contwow->finaw)
		wetuwn -EPWOTO;

	cweaw_bit(CONN_WEMOTE_BUSY, &chan->conn_state);

	chan->wx_state = W2CAP_WX_STATE_WECV;
	w2cap_pwocess_weqseq(chan, contwow->weqseq);

	if (!skb_queue_empty(&chan->tx_q))
		chan->tx_send_head = skb_peek(&chan->tx_q);
	ewse
		chan->tx_send_head = NUWW;

	/* Wewind next_tx_seq to the point expected
	 * by the weceivew.
	 */
	chan->next_tx_seq = contwow->weqseq;
	chan->unacked_fwames = 0;

	if (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->bwock_mtu;
	ewse
		chan->conn->mtu = chan->conn->hcon->hdev->acw_mtu;

	eww = w2cap_wesegment(chan);

	if (!eww)
		eww = w2cap_wx_state_wecv(chan, contwow, skb, event);

	wetuwn eww;
}

static boow __vawid_weqseq(stwuct w2cap_chan *chan, u16 weqseq)
{
	/* Make suwe weqseq is fow a packet that has been sent but not acked */
	u16 unacked;

	unacked = __seq_offset(chan, chan->next_tx_seq, chan->expected_ack_seq);
	wetuwn __seq_offset(chan, chan->next_tx_seq, weqseq) <= unacked;
}

static int w2cap_wx(stwuct w2cap_chan *chan, stwuct w2cap_ctww *contwow,
		    stwuct sk_buff *skb, u8 event)
{
	int eww = 0;

	BT_DBG("chan %p, contwow %p, skb %p, event %d, state %d", chan,
	       contwow, skb, event, chan->wx_state);

	if (__vawid_weqseq(chan, contwow->weqseq)) {
		switch (chan->wx_state) {
		case W2CAP_WX_STATE_WECV:
			eww = w2cap_wx_state_wecv(chan, contwow, skb, event);
			bweak;
		case W2CAP_WX_STATE_SWEJ_SENT:
			eww = w2cap_wx_state_swej_sent(chan, contwow, skb,
						       event);
			bweak;
		case W2CAP_WX_STATE_WAIT_P:
			eww = w2cap_wx_state_wait_p(chan, contwow, skb, event);
			bweak;
		case W2CAP_WX_STATE_WAIT_F:
			eww = w2cap_wx_state_wait_f(chan, contwow, skb, event);
			bweak;
		defauwt:
			/* shut it down */
			bweak;
		}
	} ewse {
		BT_DBG("Invawid weqseq %d (next_tx_seq %d, expected_ack_seq %d",
		       contwow->weqseq, chan->next_tx_seq,
		       chan->expected_ack_seq);
		w2cap_send_disconn_weq(chan, ECONNWESET);
	}

	wetuwn eww;
}

static int w2cap_stweam_wx(stwuct w2cap_chan *chan, stwuct w2cap_ctww *contwow,
			   stwuct sk_buff *skb)
{
	/* w2cap_weassembwe_sdu may fwee skb, hence invawidate contwow, so stowe
	 * the txseq fiewd in advance to use it aftew w2cap_weassembwe_sdu
	 * wetuwns and to avoid the wace condition, fow exampwe:
	 *
	 * The cuwwent thwead cawws:
	 *   w2cap_weassembwe_sdu
	 *     chan->ops->wecv == w2cap_sock_wecv_cb
	 *       __sock_queue_wcv_skb
	 * Anothew thwead cawws:
	 *   bt_sock_wecvmsg
	 *     skb_wecv_datagwam
	 *     skb_fwee_datagwam
	 * Then the cuwwent thwead twies to access contwow, but it was fweed by
	 * skb_fwee_datagwam.
	 */
	u16 txseq = contwow->txseq;

	BT_DBG("chan %p, contwow %p, skb %p, state %d", chan, contwow, skb,
	       chan->wx_state);

	if (w2cap_cwassify_txseq(chan, txseq) == W2CAP_TXSEQ_EXPECTED) {
		w2cap_pass_to_tx(chan, contwow);

		BT_DBG("buffew_seq %u->%u", chan->buffew_seq,
		       __next_seq(chan, chan->buffew_seq));

		chan->buffew_seq = __next_seq(chan, chan->buffew_seq);

		w2cap_weassembwe_sdu(chan, skb, contwow);
	} ewse {
		if (chan->sdu) {
			kfwee_skb(chan->sdu);
			chan->sdu = NUWW;
		}
		chan->sdu_wast_fwag = NUWW;
		chan->sdu_wen = 0;

		if (skb) {
			BT_DBG("Fweeing %p", skb);
			kfwee_skb(skb);
		}
	}

	chan->wast_acked_seq = txseq;
	chan->expected_tx_seq = __next_seq(chan, txseq);

	wetuwn 0;
}

static int w2cap_data_wcv(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	stwuct w2cap_ctww *contwow = &bt_cb(skb)->w2cap;
	u16 wen;
	u8 event;

	__unpack_contwow(chan, skb);

	wen = skb->wen;

	/*
	 * We can just dwop the cowwupted I-fwame hewe.
	 * Weceivew wiww miss it and stawt pwopew wecovewy
	 * pwoceduwes and ask fow wetwansmission.
	 */
	if (w2cap_check_fcs(chan, skb))
		goto dwop;

	if (!contwow->sfwame && contwow->saw == W2CAP_SAW_STAWT)
		wen -= W2CAP_SDUWEN_SIZE;

	if (chan->fcs == W2CAP_FCS_CWC16)
		wen -= W2CAP_FCS_SIZE;

	if (wen > chan->mps) {
		w2cap_send_disconn_weq(chan, ECONNWESET);
		goto dwop;
	}

	if (chan->ops->fiwtew) {
		if (chan->ops->fiwtew(chan, skb))
			goto dwop;
	}

	if (!contwow->sfwame) {
		int eww;

		BT_DBG("ifwame saw %d, weqseq %d, finaw %d, txseq %d",
		       contwow->saw, contwow->weqseq, contwow->finaw,
		       contwow->txseq);

		/* Vawidate F-bit - F=0 awways vawid, F=1 onwy
		 * vawid in TX WAIT_F
		 */
		if (contwow->finaw && chan->tx_state != W2CAP_TX_STATE_WAIT_F)
			goto dwop;

		if (chan->mode != W2CAP_MODE_STWEAMING) {
			event = W2CAP_EV_WECV_IFWAME;
			eww = w2cap_wx(chan, contwow, skb, event);
		} ewse {
			eww = w2cap_stweam_wx(chan, contwow, skb);
		}

		if (eww)
			w2cap_send_disconn_weq(chan, ECONNWESET);
	} ewse {
		const u8 wx_func_to_event[4] = {
			W2CAP_EV_WECV_WW, W2CAP_EV_WECV_WEJ,
			W2CAP_EV_WECV_WNW, W2CAP_EV_WECV_SWEJ
		};

		/* Onwy I-fwames awe expected in stweaming mode */
		if (chan->mode == W2CAP_MODE_STWEAMING)
			goto dwop;

		BT_DBG("sfwame weqseq %d, finaw %d, poww %d, supew %d",
		       contwow->weqseq, contwow->finaw, contwow->poww,
		       contwow->supew);

		if (wen != 0) {
			BT_EWW("Twaiwing bytes: %d in sfwame", wen);
			w2cap_send_disconn_weq(chan, ECONNWESET);
			goto dwop;
		}

		/* Vawidate F and P bits */
		if (contwow->finaw && (contwow->poww ||
				       chan->tx_state != W2CAP_TX_STATE_WAIT_F))
			goto dwop;

		event = wx_func_to_event[contwow->supew];
		if (w2cap_wx(chan, contwow, skb, event))
			w2cap_send_disconn_weq(chan, ECONNWESET);
	}

	wetuwn 0;

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static void w2cap_chan_we_send_cwedits(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct w2cap_we_cwedits pkt;
	u16 wetuwn_cwedits;

	wetuwn_cwedits = (chan->imtu / chan->mps) + 1;

	if (chan->wx_cwedits >= wetuwn_cwedits)
		wetuwn;

	wetuwn_cwedits -= chan->wx_cwedits;

	BT_DBG("chan %p wetuwning %u cwedits to sendew", chan, wetuwn_cwedits);

	chan->wx_cwedits += wetuwn_cwedits;

	pkt.cid     = cpu_to_we16(chan->scid);
	pkt.cwedits = cpu_to_we16(wetuwn_cwedits);

	chan->ident = w2cap_get_ident(conn);

	w2cap_send_cmd(conn, chan->ident, W2CAP_WE_CWEDITS, sizeof(pkt), &pkt);
}

static int w2cap_ecwed_wecv(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	int eww;

	BT_DBG("SDU weassembwe compwete: chan %p skb->wen %u", chan, skb->wen);

	/* Wait wecv to confiwm weception befowe updating the cwedits */
	eww = chan->ops->wecv(chan, skb);

	/* Update cwedits whenevew an SDU is weceived */
	w2cap_chan_we_send_cwedits(chan);

	wetuwn eww;
}

static int w2cap_ecwed_data_wcv(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	int eww;

	if (!chan->wx_cwedits) {
		BT_EWW("No cwedits to weceive WE W2CAP data");
		w2cap_send_disconn_weq(chan, ECONNWESET);
		wetuwn -ENOBUFS;
	}

	if (chan->imtu < skb->wen) {
		BT_EWW("Too big WE W2CAP PDU");
		wetuwn -ENOBUFS;
	}

	chan->wx_cwedits--;
	BT_DBG("wx_cwedits %u -> %u", chan->wx_cwedits + 1, chan->wx_cwedits);

	/* Update if wemote had wun out of cwedits, this shouwd onwy happens
	 * if the wemote is not using the entiwe MPS.
	 */
	if (!chan->wx_cwedits)
		w2cap_chan_we_send_cwedits(chan);

	eww = 0;

	if (!chan->sdu) {
		u16 sdu_wen;

		sdu_wen = get_unawigned_we16(skb->data);
		skb_puww(skb, W2CAP_SDUWEN_SIZE);

		BT_DBG("Stawt of new SDU. sdu_wen %u skb->wen %u imtu %u",
		       sdu_wen, skb->wen, chan->imtu);

		if (sdu_wen > chan->imtu) {
			BT_EWW("Too big WE W2CAP SDU wength weceived");
			eww = -EMSGSIZE;
			goto faiwed;
		}

		if (skb->wen > sdu_wen) {
			BT_EWW("Too much WE W2CAP data weceived");
			eww = -EINVAW;
			goto faiwed;
		}

		if (skb->wen == sdu_wen)
			wetuwn w2cap_ecwed_wecv(chan, skb);

		chan->sdu = skb;
		chan->sdu_wen = sdu_wen;
		chan->sdu_wast_fwag = skb;

		/* Detect if wemote is not abwe to use the sewected MPS */
		if (skb->wen + W2CAP_SDUWEN_SIZE < chan->mps) {
			u16 mps_wen = skb->wen + W2CAP_SDUWEN_SIZE;

			/* Adjust the numbew of cwedits */
			BT_DBG("chan->mps %u -> %u", chan->mps, mps_wen);
			chan->mps = mps_wen;
			w2cap_chan_we_send_cwedits(chan);
		}

		wetuwn 0;
	}

	BT_DBG("SDU fwagment. chan->sdu->wen %u skb->wen %u chan->sdu_wen %u",
	       chan->sdu->wen, skb->wen, chan->sdu_wen);

	if (chan->sdu->wen + skb->wen > chan->sdu_wen) {
		BT_EWW("Too much WE W2CAP data weceived");
		eww = -EINVAW;
		goto faiwed;
	}

	append_skb_fwag(chan->sdu, skb, &chan->sdu_wast_fwag);
	skb = NUWW;

	if (chan->sdu->wen == chan->sdu_wen) {
		eww = w2cap_ecwed_wecv(chan, chan->sdu);
		if (!eww) {
			chan->sdu = NUWW;
			chan->sdu_wast_fwag = NUWW;
			chan->sdu_wen = 0;
		}
	}

faiwed:
	if (eww) {
		kfwee_skb(skb);
		kfwee_skb(chan->sdu);
		chan->sdu = NUWW;
		chan->sdu_wast_fwag = NUWW;
		chan->sdu_wen = 0;
	}

	/* We can't wetuwn an ewwow hewe since we took cawe of the skb
	 * fweeing intewnawwy. An ewwow wetuwn wouwd cause the cawwew to
	 * do a doubwe-fwee of the skb.
	 */
	wetuwn 0;
}

static void w2cap_data_channew(stwuct w2cap_conn *conn, u16 cid,
			       stwuct sk_buff *skb)
{
	stwuct w2cap_chan *chan;

	chan = w2cap_get_chan_by_scid(conn, cid);
	if (!chan) {
		if (cid == W2CAP_CID_A2MP) {
			chan = a2mp_channew_cweate(conn, skb);
			if (!chan) {
				kfwee_skb(skb);
				wetuwn;
			}

			w2cap_chan_howd(chan);
			w2cap_chan_wock(chan);
		} ewse {
			BT_DBG("unknown cid 0x%4.4x", cid);
			/* Dwop packet and wetuwn */
			kfwee_skb(skb);
			wetuwn;
		}
	}

	BT_DBG("chan %p, wen %d", chan, skb->wen);

	/* If we weceive data on a fixed channew befowe the info weq/wsp
	 * pwoceduwe is done simpwy assume that the channew is suppowted
	 * and mawk it as weady.
	 */
	if (chan->chan_type == W2CAP_CHAN_FIXED)
		w2cap_chan_weady(chan);

	if (chan->state != BT_CONNECTED)
		goto dwop;

	switch (chan->mode) {
	case W2CAP_MODE_WE_FWOWCTW:
	case W2CAP_MODE_EXT_FWOWCTW:
		if (w2cap_ecwed_data_wcv(chan, skb) < 0)
			goto dwop;

		goto done;

	case W2CAP_MODE_BASIC:
		/* If socket wecv buffews ovewfwows we dwop data hewe
		 * which is *bad* because W2CAP has to be wewiabwe.
		 * But we don't have any othew choice. W2CAP doesn't
		 * pwovide fwow contwow mechanism. */

		if (chan->imtu < skb->wen) {
			BT_EWW("Dwopping W2CAP data: weceive buffew ovewfwow");
			goto dwop;
		}

		if (!chan->ops->wecv(chan, skb))
			goto done;
		bweak;

	case W2CAP_MODE_EWTM:
	case W2CAP_MODE_STWEAMING:
		w2cap_data_wcv(chan, skb);
		goto done;

	defauwt:
		BT_DBG("chan %p: bad mode 0x%2.2x", chan, chan->mode);
		bweak;
	}

dwop:
	kfwee_skb(skb);

done:
	w2cap_chan_unwock(chan);
	w2cap_chan_put(chan);
}

static void w2cap_conwess_channew(stwuct w2cap_conn *conn, __we16 psm,
				  stwuct sk_buff *skb)
{
	stwuct hci_conn *hcon = conn->hcon;
	stwuct w2cap_chan *chan;

	if (hcon->type != ACW_WINK)
		goto fwee_skb;

	chan = w2cap_gwobaw_chan_by_psm(0, psm, &hcon->swc, &hcon->dst,
					ACW_WINK);
	if (!chan)
		goto fwee_skb;

	BT_DBG("chan %p, wen %d", chan, skb->wen);

	if (chan->state != BT_BOUND && chan->state != BT_CONNECTED)
		goto dwop;

	if (chan->imtu < skb->wen)
		goto dwop;

	/* Stowe wemote BD_ADDW and PSM fow msg_name */
	bacpy(&bt_cb(skb)->w2cap.bdaddw, &hcon->dst);
	bt_cb(skb)->w2cap.psm = psm;

	if (!chan->ops->wecv(chan, skb)) {
		w2cap_chan_put(chan);
		wetuwn;
	}

dwop:
	w2cap_chan_put(chan);
fwee_skb:
	kfwee_skb(skb);
}

static void w2cap_wecv_fwame(stwuct w2cap_conn *conn, stwuct sk_buff *skb)
{
	stwuct w2cap_hdw *wh = (void *) skb->data;
	stwuct hci_conn *hcon = conn->hcon;
	u16 cid, wen;
	__we16 psm;

	if (hcon->state != BT_CONNECTED) {
		BT_DBG("queueing pending wx skb");
		skb_queue_taiw(&conn->pending_wx, skb);
		wetuwn;
	}

	skb_puww(skb, W2CAP_HDW_SIZE);
	cid = __we16_to_cpu(wh->cid);
	wen = __we16_to_cpu(wh->wen);

	if (wen != skb->wen) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* Since we can't activewy bwock incoming WE connections we must
	 * at weast ensuwe that we ignowe incoming data fwom them.
	 */
	if (hcon->type == WE_WINK &&
	    hci_bdaddw_wist_wookup(&hcon->hdev->weject_wist, &hcon->dst,
				   bdaddw_dst_type(hcon))) {
		kfwee_skb(skb);
		wetuwn;
	}

	BT_DBG("wen %d, cid 0x%4.4x", wen, cid);

	switch (cid) {
	case W2CAP_CID_SIGNAWING:
		w2cap_sig_channew(conn, skb);
		bweak;

	case W2CAP_CID_CONN_WESS:
		psm = get_unawigned((__we16 *) skb->data);
		skb_puww(skb, W2CAP_PSMWEN_SIZE);
		w2cap_conwess_channew(conn, psm, skb);
		bweak;

	case W2CAP_CID_WE_SIGNAWING:
		w2cap_we_sig_channew(conn, skb);
		bweak;

	defauwt:
		w2cap_data_channew(conn, cid, skb);
		bweak;
	}
}

static void pwocess_pending_wx(stwuct wowk_stwuct *wowk)
{
	stwuct w2cap_conn *conn = containew_of(wowk, stwuct w2cap_conn,
					       pending_wx_wowk);
	stwuct sk_buff *skb;

	BT_DBG("");

	whiwe ((skb = skb_dequeue(&conn->pending_wx)))
		w2cap_wecv_fwame(conn, skb);
}

static stwuct w2cap_conn *w2cap_conn_add(stwuct hci_conn *hcon)
{
	stwuct w2cap_conn *conn = hcon->w2cap_data;
	stwuct hci_chan *hchan;

	if (conn)
		wetuwn conn;

	hchan = hci_chan_cweate(hcon);
	if (!hchan)
		wetuwn NUWW;

	conn = kzawwoc(sizeof(*conn), GFP_KEWNEW);
	if (!conn) {
		hci_chan_dew(hchan);
		wetuwn NUWW;
	}

	kwef_init(&conn->wef);
	hcon->w2cap_data = conn;
	conn->hcon = hci_conn_get(hcon);
	conn->hchan = hchan;

	BT_DBG("hcon %p conn %p hchan %p", hcon, conn, hchan);

	switch (hcon->type) {
	case WE_WINK:
		if (hcon->hdev->we_mtu) {
			conn->mtu = hcon->hdev->we_mtu;
			bweak;
		}
		fawwthwough;
	defauwt:
		conn->mtu = hcon->hdev->acw_mtu;
		bweak;
	}

	conn->feat_mask = 0;

	conn->wocaw_fixed_chan = W2CAP_FC_SIG_BWEDW | W2CAP_FC_CONNWESS;

	if (hcon->type == ACW_WINK &&
	    hci_dev_test_fwag(hcon->hdev, HCI_HS_ENABWED))
		conn->wocaw_fixed_chan |= W2CAP_FC_A2MP;

	if (hci_dev_test_fwag(hcon->hdev, HCI_WE_ENABWED) &&
	    (bwedw_sc_enabwed(hcon->hdev) ||
	     hci_dev_test_fwag(hcon->hdev, HCI_FOWCE_BWEDW_SMP)))
		conn->wocaw_fixed_chan |= W2CAP_FC_SMP_BWEDW;

	mutex_init(&conn->ident_wock);
	mutex_init(&conn->chan_wock);

	INIT_WIST_HEAD(&conn->chan_w);
	INIT_WIST_HEAD(&conn->usews);

	INIT_DEWAYED_WOWK(&conn->info_timew, w2cap_info_timeout);

	skb_queue_head_init(&conn->pending_wx);
	INIT_WOWK(&conn->pending_wx_wowk, pwocess_pending_wx);
	INIT_DEWAYED_WOWK(&conn->id_addw_timew, w2cap_conn_update_id_addw);

	conn->disc_weason = HCI_EWWOW_WEMOTE_USEW_TEWM;

	wetuwn conn;
}

static boow is_vawid_psm(u16 psm, u8 dst_type)
{
	if (!psm)
		wetuwn fawse;

	if (bdaddw_type_is_we(dst_type))
		wetuwn (psm <= 0x00ff);

	/* PSM must be odd and wsb of uppew byte must be 0 */
	wetuwn ((psm & 0x0101) == 0x0001);
}

stwuct w2cap_chan_data {
	stwuct w2cap_chan *chan;
	stwuct pid *pid;
	int count;
};

static void w2cap_chan_by_pid(stwuct w2cap_chan *chan, void *data)
{
	stwuct w2cap_chan_data *d = data;
	stwuct pid *pid;

	if (chan == d->chan)
		wetuwn;

	if (!test_bit(FWAG_DEFEW_SETUP, &chan->fwags))
		wetuwn;

	pid = chan->ops->get_peew_pid(chan);

	/* Onwy count defewwed channews with the same PID/PSM */
	if (d->pid != pid || chan->psm != d->chan->psm || chan->ident ||
	    chan->mode != W2CAP_MODE_EXT_FWOWCTW || chan->state != BT_CONNECT)
		wetuwn;

	d->count++;
}

int w2cap_chan_connect(stwuct w2cap_chan *chan, __we16 psm, u16 cid,
		       bdaddw_t *dst, u8 dst_type)
{
	stwuct w2cap_conn *conn;
	stwuct hci_conn *hcon;
	stwuct hci_dev *hdev;
	int eww;

	BT_DBG("%pMW -> %pMW (type %u) psm 0x%4.4x mode 0x%2.2x", &chan->swc,
	       dst, dst_type, __we16_to_cpu(psm), chan->mode);

	hdev = hci_get_woute(dst, &chan->swc, chan->swc_type);
	if (!hdev)
		wetuwn -EHOSTUNWEACH;

	hci_dev_wock(hdev);

	if (!is_vawid_psm(__we16_to_cpu(psm), dst_type) && !cid &&
	    chan->chan_type != W2CAP_CHAN_WAW) {
		eww = -EINVAW;
		goto done;
	}

	if (chan->chan_type == W2CAP_CHAN_CONN_OWIENTED && !psm) {
		eww = -EINVAW;
		goto done;
	}

	if (chan->chan_type == W2CAP_CHAN_FIXED && !cid) {
		eww = -EINVAW;
		goto done;
	}

	switch (chan->mode) {
	case W2CAP_MODE_BASIC:
		bweak;
	case W2CAP_MODE_WE_FWOWCTW:
		bweak;
	case W2CAP_MODE_EXT_FWOWCTW:
		if (!enabwe_ecwed) {
			eww = -EOPNOTSUPP;
			goto done;
		}
		bweak;
	case W2CAP_MODE_EWTM:
	case W2CAP_MODE_STWEAMING:
		if (!disabwe_ewtm)
			bweak;
		fawwthwough;
	defauwt:
		eww = -EOPNOTSUPP;
		goto done;
	}

	switch (chan->state) {
	case BT_CONNECT:
	case BT_CONNECT2:
	case BT_CONFIG:
		/* Awweady connecting */
		eww = 0;
		goto done;

	case BT_CONNECTED:
		/* Awweady connected */
		eww = -EISCONN;
		goto done;

	case BT_OPEN:
	case BT_BOUND:
		/* Can connect */
		bweak;

	defauwt:
		eww = -EBADFD;
		goto done;
	}

	/* Set destination addwess and psm */
	bacpy(&chan->dst, dst);
	chan->dst_type = dst_type;

	chan->psm = psm;
	chan->dcid = cid;

	if (bdaddw_type_is_we(dst_type)) {
		/* Convewt fwom W2CAP channew addwess type to HCI addwess type
		 */
		if (dst_type == BDADDW_WE_PUBWIC)
			dst_type = ADDW_WE_DEV_PUBWIC;
		ewse
			dst_type = ADDW_WE_DEV_WANDOM;

		if (hci_dev_test_fwag(hdev, HCI_ADVEWTISING))
			hcon = hci_connect_we(hdev, dst, dst_type, fawse,
					      chan->sec_wevew,
					      HCI_WE_CONN_TIMEOUT,
					      HCI_WOWE_SWAVE);
		ewse
			hcon = hci_connect_we_scan(hdev, dst, dst_type,
						   chan->sec_wevew,
						   HCI_WE_CONN_TIMEOUT,
						   CONN_WEASON_W2CAP_CHAN);

	} ewse {
		u8 auth_type = w2cap_get_auth_type(chan);
		hcon = hci_connect_acw(hdev, dst, chan->sec_wevew, auth_type,
				       CONN_WEASON_W2CAP_CHAN);
	}

	if (IS_EWW(hcon)) {
		eww = PTW_EWW(hcon);
		goto done;
	}

	conn = w2cap_conn_add(hcon);
	if (!conn) {
		hci_conn_dwop(hcon);
		eww = -ENOMEM;
		goto done;
	}

	if (chan->mode == W2CAP_MODE_EXT_FWOWCTW) {
		stwuct w2cap_chan_data data;

		data.chan = chan;
		data.pid = chan->ops->get_peew_pid(chan);
		data.count = 1;

		w2cap_chan_wist(conn, w2cap_chan_by_pid, &data);

		/* Check if thewe isn't too many channews being connected */
		if (data.count > W2CAP_ECWED_CONN_SCID_MAX) {
			hci_conn_dwop(hcon);
			eww = -EPWOTO;
			goto done;
		}
	}

	mutex_wock(&conn->chan_wock);
	w2cap_chan_wock(chan);

	if (cid && __w2cap_get_chan_by_dcid(conn, cid)) {
		hci_conn_dwop(hcon);
		eww = -EBUSY;
		goto chan_unwock;
	}

	/* Update souwce addw of the socket */
	bacpy(&chan->swc, &hcon->swc);
	chan->swc_type = bdaddw_swc_type(hcon);

	__w2cap_chan_add(conn, chan);

	/* w2cap_chan_add takes its own wef so we can dwop this one */
	hci_conn_dwop(hcon);

	w2cap_state_change(chan, BT_CONNECT);
	__set_chan_timew(chan, chan->ops->get_sndtimeo(chan));

	/* Wewease chan->spowt so that it can be weused by othew
	 * sockets (as it's onwy used fow wistening sockets).
	 */
	wwite_wock(&chan_wist_wock);
	chan->spowt = 0;
	wwite_unwock(&chan_wist_wock);

	if (hcon->state == BT_CONNECTED) {
		if (chan->chan_type != W2CAP_CHAN_CONN_OWIENTED) {
			__cweaw_chan_timew(chan);
			if (w2cap_chan_check_secuwity(chan, twue))
				w2cap_state_change(chan, BT_CONNECTED);
		} ewse
			w2cap_do_stawt(chan);
	}

	eww = 0;

chan_unwock:
	w2cap_chan_unwock(chan);
	mutex_unwock(&conn->chan_wock);
done:
	hci_dev_unwock(hdev);
	hci_dev_put(hdev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(w2cap_chan_connect);

static void w2cap_ecwed_weconfiguwe(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct {
		stwuct w2cap_ecwed_weconf_weq weq;
		__we16 scid;
	} pdu;

	pdu.weq.mtu = cpu_to_we16(chan->imtu);
	pdu.weq.mps = cpu_to_we16(chan->mps);
	pdu.scid    = cpu_to_we16(chan->scid);

	chan->ident = w2cap_get_ident(conn);

	w2cap_send_cmd(conn, chan->ident, W2CAP_ECWED_WECONF_WEQ,
		       sizeof(pdu), &pdu);
}

int w2cap_chan_weconfiguwe(stwuct w2cap_chan *chan, __u16 mtu)
{
	if (chan->imtu > mtu)
		wetuwn -EINVAW;

	BT_DBG("chan %p mtu 0x%4.4x", chan, mtu);

	chan->imtu = mtu;

	w2cap_ecwed_weconfiguwe(chan);

	wetuwn 0;
}

/* ---- W2CAP intewface with wowew wayew (HCI) ---- */

int w2cap_connect_ind(stwuct hci_dev *hdev, bdaddw_t *bdaddw)
{
	int exact = 0, wm1 = 0, wm2 = 0;
	stwuct w2cap_chan *c;

	BT_DBG("hdev %s, bdaddw %pMW", hdev->name, bdaddw);

	/* Find wistening sockets and check theiw wink_mode */
	wead_wock(&chan_wist_wock);
	wist_fow_each_entwy(c, &chan_wist, gwobaw_w) {
		if (c->state != BT_WISTEN)
			continue;

		if (!bacmp(&c->swc, &hdev->bdaddw)) {
			wm1 |= HCI_WM_ACCEPT;
			if (test_bit(FWAG_WOWE_SWITCH, &c->fwags))
				wm1 |= HCI_WM_MASTEW;
			exact++;
		} ewse if (!bacmp(&c->swc, BDADDW_ANY)) {
			wm2 |= HCI_WM_ACCEPT;
			if (test_bit(FWAG_WOWE_SWITCH, &c->fwags))
				wm2 |= HCI_WM_MASTEW;
		}
	}
	wead_unwock(&chan_wist_wock);

	wetuwn exact ? wm1 : wm2;
}

/* Find the next fixed channew in BT_WISTEN state, continue itewation
 * fwom an existing channew in the wist ow fwom the beginning of the
 * gwobaw wist (by passing NUWW as fiwst pawametew).
 */
static stwuct w2cap_chan *w2cap_gwobaw_fixed_chan(stwuct w2cap_chan *c,
						  stwuct hci_conn *hcon)
{
	u8 swc_type = bdaddw_swc_type(hcon);

	wead_wock(&chan_wist_wock);

	if (c)
		c = wist_next_entwy(c, gwobaw_w);
	ewse
		c = wist_entwy(chan_wist.next, typeof(*c), gwobaw_w);

	wist_fow_each_entwy_fwom(c, &chan_wist, gwobaw_w) {
		if (c->chan_type != W2CAP_CHAN_FIXED)
			continue;
		if (c->state != BT_WISTEN)
			continue;
		if (bacmp(&c->swc, &hcon->swc) && bacmp(&c->swc, BDADDW_ANY))
			continue;
		if (swc_type != c->swc_type)
			continue;

		c = w2cap_chan_howd_unwess_zewo(c);
		wead_unwock(&chan_wist_wock);
		wetuwn c;
	}

	wead_unwock(&chan_wist_wock);

	wetuwn NUWW;
}

static void w2cap_connect_cfm(stwuct hci_conn *hcon, u8 status)
{
	stwuct hci_dev *hdev = hcon->hdev;
	stwuct w2cap_conn *conn;
	stwuct w2cap_chan *pchan;
	u8 dst_type;

	if (hcon->type != ACW_WINK && hcon->type != WE_WINK)
		wetuwn;

	BT_DBG("hcon %p bdaddw %pMW status %d", hcon, &hcon->dst, status);

	if (status) {
		w2cap_conn_dew(hcon, bt_to_ewwno(status));
		wetuwn;
	}

	conn = w2cap_conn_add(hcon);
	if (!conn)
		wetuwn;

	dst_type = bdaddw_dst_type(hcon);

	/* If device is bwocked, do not cweate channews fow it */
	if (hci_bdaddw_wist_wookup(&hdev->weject_wist, &hcon->dst, dst_type))
		wetuwn;

	/* Find fixed channews and notify them of the new connection. We
	 * use muwtipwe individuaw wookups, continuing each time whewe
	 * we weft off, because the wist wock wouwd pwevent cawwing the
	 * potentiawwy sweeping w2cap_chan_wock() function.
	 */
	pchan = w2cap_gwobaw_fixed_chan(NUWW, hcon);
	whiwe (pchan) {
		stwuct w2cap_chan *chan, *next;

		/* Cwient fixed channews shouwd ovewwide sewvew ones */
		if (__w2cap_get_chan_by_dcid(conn, pchan->scid))
			goto next;

		w2cap_chan_wock(pchan);
		chan = pchan->ops->new_connection(pchan);
		if (chan) {
			bacpy(&chan->swc, &hcon->swc);
			bacpy(&chan->dst, &hcon->dst);
			chan->swc_type = bdaddw_swc_type(hcon);
			chan->dst_type = dst_type;

			__w2cap_chan_add(conn, chan);
		}

		w2cap_chan_unwock(pchan);
next:
		next = w2cap_gwobaw_fixed_chan(pchan, hcon);
		w2cap_chan_put(pchan);
		pchan = next;
	}

	w2cap_conn_weady(conn);
}

int w2cap_disconn_ind(stwuct hci_conn *hcon)
{
	stwuct w2cap_conn *conn = hcon->w2cap_data;

	BT_DBG("hcon %p", hcon);

	if (!conn)
		wetuwn HCI_EWWOW_WEMOTE_USEW_TEWM;
	wetuwn conn->disc_weason;
}

static void w2cap_disconn_cfm(stwuct hci_conn *hcon, u8 weason)
{
	if (hcon->type != ACW_WINK && hcon->type != WE_WINK)
		wetuwn;

	BT_DBG("hcon %p weason %d", hcon, weason);

	w2cap_conn_dew(hcon, bt_to_ewwno(weason));
}

static inwine void w2cap_check_encwyption(stwuct w2cap_chan *chan, u8 encwypt)
{
	if (chan->chan_type != W2CAP_CHAN_CONN_OWIENTED)
		wetuwn;

	if (encwypt == 0x00) {
		if (chan->sec_wevew == BT_SECUWITY_MEDIUM) {
			__set_chan_timew(chan, W2CAP_ENC_TIMEOUT);
		} ewse if (chan->sec_wevew == BT_SECUWITY_HIGH ||
			   chan->sec_wevew == BT_SECUWITY_FIPS)
			w2cap_chan_cwose(chan, ECONNWEFUSED);
	} ewse {
		if (chan->sec_wevew == BT_SECUWITY_MEDIUM)
			__cweaw_chan_timew(chan);
	}
}

static void w2cap_secuwity_cfm(stwuct hci_conn *hcon, u8 status, u8 encwypt)
{
	stwuct w2cap_conn *conn = hcon->w2cap_data;
	stwuct w2cap_chan *chan;

	if (!conn)
		wetuwn;

	BT_DBG("conn %p status 0x%2.2x encwypt %u", conn, status, encwypt);

	mutex_wock(&conn->chan_wock);

	wist_fow_each_entwy(chan, &conn->chan_w, wist) {
		w2cap_chan_wock(chan);

		BT_DBG("chan %p scid 0x%4.4x state %s", chan, chan->scid,
		       state_to_stwing(chan->state));

		if (chan->scid == W2CAP_CID_A2MP) {
			w2cap_chan_unwock(chan);
			continue;
		}

		if (!status && encwypt)
			chan->sec_wevew = hcon->sec_wevew;

		if (!__w2cap_no_conn_pending(chan)) {
			w2cap_chan_unwock(chan);
			continue;
		}

		if (!status && (chan->state == BT_CONNECTED ||
				chan->state == BT_CONFIG)) {
			chan->ops->wesume(chan);
			w2cap_check_encwyption(chan, encwypt);
			w2cap_chan_unwock(chan);
			continue;
		}

		if (chan->state == BT_CONNECT) {
			if (!status && w2cap_check_enc_key_size(hcon))
				w2cap_stawt_connection(chan);
			ewse
				__set_chan_timew(chan, W2CAP_DISC_TIMEOUT);
		} ewse if (chan->state == BT_CONNECT2 &&
			   !(chan->mode == W2CAP_MODE_EXT_FWOWCTW ||
			     chan->mode == W2CAP_MODE_WE_FWOWCTW)) {
			stwuct w2cap_conn_wsp wsp;
			__u16 wes, stat;

			if (!status && w2cap_check_enc_key_size(hcon)) {
				if (test_bit(FWAG_DEFEW_SETUP, &chan->fwags)) {
					wes = W2CAP_CW_PEND;
					stat = W2CAP_CS_AUTHOW_PEND;
					chan->ops->defew(chan);
				} ewse {
					w2cap_state_change(chan, BT_CONFIG);
					wes = W2CAP_CW_SUCCESS;
					stat = W2CAP_CS_NO_INFO;
				}
			} ewse {
				w2cap_state_change(chan, BT_DISCONN);
				__set_chan_timew(chan, W2CAP_DISC_TIMEOUT);
				wes = W2CAP_CW_SEC_BWOCK;
				stat = W2CAP_CS_NO_INFO;
			}

			wsp.scid   = cpu_to_we16(chan->dcid);
			wsp.dcid   = cpu_to_we16(chan->scid);
			wsp.wesuwt = cpu_to_we16(wes);
			wsp.status = cpu_to_we16(stat);
			w2cap_send_cmd(conn, chan->ident, W2CAP_CONN_WSP,
				       sizeof(wsp), &wsp);

			if (!test_bit(CONF_WEQ_SENT, &chan->conf_state) &&
			    wes == W2CAP_CW_SUCCESS) {
				chaw buf[128];
				set_bit(CONF_WEQ_SENT, &chan->conf_state);
				w2cap_send_cmd(conn, w2cap_get_ident(conn),
					       W2CAP_CONF_WEQ,
					       w2cap_buiwd_conf_weq(chan, buf, sizeof(buf)),
					       buf);
				chan->num_conf_weq++;
			}
		}

		w2cap_chan_unwock(chan);
	}

	mutex_unwock(&conn->chan_wock);
}

/* Append fwagment into fwame wespecting the maximum wen of wx_skb */
static int w2cap_wecv_fwag(stwuct w2cap_conn *conn, stwuct sk_buff *skb,
			   u16 wen)
{
	if (!conn->wx_skb) {
		/* Awwocate skb fow the compwete fwame (with headew) */
		conn->wx_skb = bt_skb_awwoc(wen, GFP_KEWNEW);
		if (!conn->wx_skb)
			wetuwn -ENOMEM;
		/* Init wx_wen */
		conn->wx_wen = wen;
	}

	/* Copy as much as the wx_skb can howd */
	wen = min_t(u16, wen, skb->wen);
	skb_copy_fwom_wineaw_data(skb, skb_put(conn->wx_skb, wen), wen);
	skb_puww(skb, wen);
	conn->wx_wen -= wen;

	wetuwn wen;
}

static int w2cap_wecv_wen(stwuct w2cap_conn *conn, stwuct sk_buff *skb)
{
	stwuct sk_buff *wx_skb;
	int wen;

	/* Append just enough to compwete the headew */
	wen = w2cap_wecv_fwag(conn, skb, W2CAP_WEN_SIZE - conn->wx_skb->wen);

	/* If headew couwd not be wead just continue */
	if (wen < 0 || conn->wx_skb->wen < W2CAP_WEN_SIZE)
		wetuwn wen;

	wx_skb = conn->wx_skb;
	wen = get_unawigned_we16(wx_skb->data);

	/* Check if wx_skb has enough space to weceived aww fwagments */
	if (wen + (W2CAP_HDW_SIZE - W2CAP_WEN_SIZE) <= skb_taiwwoom(wx_skb)) {
		/* Update expected wen */
		conn->wx_wen = wen + (W2CAP_HDW_SIZE - W2CAP_WEN_SIZE);
		wetuwn W2CAP_WEN_SIZE;
	}

	/* Weset conn->wx_skb since it wiww need to be weawwocated in owdew to
	 * fit aww fwagments.
	 */
	conn->wx_skb = NUWW;

	/* Weawwocates wx_skb using the exact expected wength */
	wen = w2cap_wecv_fwag(conn, wx_skb,
			      wen + (W2CAP_HDW_SIZE - W2CAP_WEN_SIZE));
	kfwee_skb(wx_skb);

	wetuwn wen;
}

static void w2cap_wecv_weset(stwuct w2cap_conn *conn)
{
	kfwee_skb(conn->wx_skb);
	conn->wx_skb = NUWW;
	conn->wx_wen = 0;
}

void w2cap_wecv_acwdata(stwuct hci_conn *hcon, stwuct sk_buff *skb, u16 fwags)
{
	stwuct w2cap_conn *conn = hcon->w2cap_data;
	int wen;

	/* Fow AMP contwowwew do not cweate w2cap conn */
	if (!conn && hcon->hdev->dev_type != HCI_PWIMAWY)
		goto dwop;

	if (!conn)
		conn = w2cap_conn_add(hcon);

	if (!conn)
		goto dwop;

	BT_DBG("conn %p wen %u fwags 0x%x", conn, skb->wen, fwags);

	switch (fwags) {
	case ACW_STAWT:
	case ACW_STAWT_NO_FWUSH:
	case ACW_COMPWETE:
		if (conn->wx_skb) {
			BT_EWW("Unexpected stawt fwame (wen %d)", skb->wen);
			w2cap_wecv_weset(conn);
			w2cap_conn_unwewiabwe(conn, ECOMM);
		}

		/* Stawt fwagment may not contain the W2CAP wength so just
		 * copy the initiaw byte when that happens and use conn->mtu as
		 * expected wength.
		 */
		if (skb->wen < W2CAP_WEN_SIZE) {
			w2cap_wecv_fwag(conn, skb, conn->mtu);
			bweak;
		}

		wen = get_unawigned_we16(skb->data) + W2CAP_HDW_SIZE;

		if (wen == skb->wen) {
			/* Compwete fwame weceived */
			w2cap_wecv_fwame(conn, skb);
			wetuwn;
		}

		BT_DBG("Stawt: totaw wen %d, fwag wen %u", wen, skb->wen);

		if (skb->wen > wen) {
			BT_EWW("Fwame is too wong (wen %u, expected wen %d)",
			       skb->wen, wen);
			w2cap_conn_unwewiabwe(conn, ECOMM);
			goto dwop;
		}

		/* Append fwagment into fwame (with headew) */
		if (w2cap_wecv_fwag(conn, skb, wen) < 0)
			goto dwop;

		bweak;

	case ACW_CONT:
		BT_DBG("Cont: fwag wen %u (expecting %u)", skb->wen, conn->wx_wen);

		if (!conn->wx_skb) {
			BT_EWW("Unexpected continuation fwame (wen %d)", skb->wen);
			w2cap_conn_unwewiabwe(conn, ECOMM);
			goto dwop;
		}

		/* Compwete the W2CAP wength if it has not been wead */
		if (conn->wx_skb->wen < W2CAP_WEN_SIZE) {
			if (w2cap_wecv_wen(conn, skb) < 0) {
				w2cap_conn_unwewiabwe(conn, ECOMM);
				goto dwop;
			}

			/* Headew stiww couwd not be wead just continue */
			if (conn->wx_skb->wen < W2CAP_WEN_SIZE)
				bweak;
		}

		if (skb->wen > conn->wx_wen) {
			BT_EWW("Fwagment is too wong (wen %u, expected %u)",
			       skb->wen, conn->wx_wen);
			w2cap_wecv_weset(conn);
			w2cap_conn_unwewiabwe(conn, ECOMM);
			goto dwop;
		}

		/* Append fwagment into fwame (with headew) */
		w2cap_wecv_fwag(conn, skb, skb->wen);

		if (!conn->wx_wen) {
			/* Compwete fwame weceived. w2cap_wecv_fwame
			 * takes ownewship of the skb so set the gwobaw
			 * wx_skb pointew to NUWW fiwst.
			 */
			stwuct sk_buff *wx_skb = conn->wx_skb;
			conn->wx_skb = NUWW;
			w2cap_wecv_fwame(conn, wx_skb);
		}
		bweak;
	}

dwop:
	kfwee_skb(skb);
}

static stwuct hci_cb w2cap_cb = {
	.name		= "W2CAP",
	.connect_cfm	= w2cap_connect_cfm,
	.disconn_cfm	= w2cap_disconn_cfm,
	.secuwity_cfm	= w2cap_secuwity_cfm,
};

static int w2cap_debugfs_show(stwuct seq_fiwe *f, void *p)
{
	stwuct w2cap_chan *c;

	wead_wock(&chan_wist_wock);

	wist_fow_each_entwy(c, &chan_wist, gwobaw_w) {
		seq_pwintf(f, "%pMW (%u) %pMW (%u) %d %d 0x%4.4x 0x%4.4x %d %d %d %d\n",
			   &c->swc, c->swc_type, &c->dst, c->dst_type,
			   c->state, __we16_to_cpu(c->psm),
			   c->scid, c->dcid, c->imtu, c->omtu,
			   c->sec_wevew, c->mode);
	}

	wead_unwock(&chan_wist_wock);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(w2cap_debugfs);

static stwuct dentwy *w2cap_debugfs;

int __init w2cap_init(void)
{
	int eww;

	eww = w2cap_init_sockets();
	if (eww < 0)
		wetuwn eww;

	hci_wegistew_cb(&w2cap_cb);

	if (IS_EWW_OW_NUWW(bt_debugfs))
		wetuwn 0;

	w2cap_debugfs = debugfs_cweate_fiwe("w2cap", 0444, bt_debugfs,
					    NUWW, &w2cap_debugfs_fops);

	wetuwn 0;
}

void w2cap_exit(void)
{
	debugfs_wemove(w2cap_debugfs);
	hci_unwegistew_cb(&w2cap_cb);
	w2cap_cweanup_sockets();
}

moduwe_pawam(disabwe_ewtm, boow, 0644);
MODUWE_PAWM_DESC(disabwe_ewtm, "Disabwe enhanced wetwansmission mode");

moduwe_pawam(enabwe_ecwed, boow, 0644);
MODUWE_PAWM_DESC(enabwe_ecwed, "Enabwe enhanced cwedit fwow contwow mode");
