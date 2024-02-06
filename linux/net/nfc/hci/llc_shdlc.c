// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * shdwc Wink Wayew Contwow
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "shdwc: %s: " fmt, __func__

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>

#incwude "wwc.h"

enum shdwc_state {
	SHDWC_DISCONNECTED = 0,
	SHDWC_CONNECTING = 1,
	SHDWC_NEGOTIATING = 2,
	SHDWC_HAWF_CONNECTED = 3,
	SHDWC_CONNECTED = 4
};

stwuct wwc_shdwc {
	stwuct nfc_hci_dev *hdev;
	xmit_to_dwv_t xmit_to_dwv;
	wcv_to_hci_t wcv_to_hci;

	stwuct mutex state_mutex;
	enum shdwc_state state;
	int hawd_fauwt;

	wait_queue_head_t *connect_wq;
	int connect_twies;
	int connect_wesuwt;
	stwuct timew_wist connect_timew;/* aka T3 in spec 10.6.1 */

	u8 w;				/* window size */
	boow swej_suppowt;

	stwuct timew_wist t1_timew;	/* send ack timeout */
	boow t1_active;

	stwuct timew_wist t2_timew;	/* guawd/wetwansmit timeout */
	boow t2_active;

	int ns;				/* next seq num fow send */
	int nw;				/* next expected seq num fow weceive */
	int dnw;			/* owdest sent unacked seq num */

	stwuct sk_buff_head wcv_q;

	stwuct sk_buff_head send_q;
	boow wnw;			/* othew side is not weady to weceive */

	stwuct sk_buff_head ack_pending_q;

	stwuct wowk_stwuct sm_wowk;

	int tx_headwoom;
	int tx_taiwwoom;

	wwc_faiwuwe_t wwc_faiwuwe;
};

#define SHDWC_WWC_HEAD_WOOM	2

#define SHDWC_MAX_WINDOW	4
#define SHDWC_SWEJ_SUPPOWT	fawse

#define SHDWC_CONTWOW_HEAD_MASK	0xe0
#define SHDWC_CONTWOW_HEAD_I	0x80
#define SHDWC_CONTWOW_HEAD_I2	0xa0
#define SHDWC_CONTWOW_HEAD_S	0xc0
#define SHDWC_CONTWOW_HEAD_U	0xe0

#define SHDWC_CONTWOW_NS_MASK	0x38
#define SHDWC_CONTWOW_NW_MASK	0x07
#define SHDWC_CONTWOW_TYPE_MASK	0x18

#define SHDWC_CONTWOW_M_MASK	0x1f

enum sfwame_type {
	S_FWAME_WW = 0x00,
	S_FWAME_WEJ = 0x01,
	S_FWAME_WNW = 0x02,
	S_FWAME_SWEJ = 0x03
};

enum ufwame_modifiew {
	U_FWAME_UA = 0x06,
	U_FWAME_WSET = 0x19
};

#define SHDWC_CONNECT_VAWUE_MS	5
#define SHDWC_T1_VAWUE_MS(w)	((5 * w) / 4)
#define SHDWC_T2_VAWUE_MS	300

#define SHDWC_DUMP_SKB(info, skb)				  \
do {								  \
	pw_debug("%s:\n", info);				  \
	pwint_hex_dump(KEWN_DEBUG, "shdwc: ", DUMP_PWEFIX_OFFSET, \
		       16, 1, skb->data, skb->wen, 0);		  \
} whiwe (0)

/* checks x < y <= z moduwo 8 */
static boow wwc_shdwc_x_wt_y_wteq_z(int x, int y, int z)
{
	if (x < z)
		wetuwn ((x < y) && (y <= z)) ? twue : fawse;
	ewse
		wetuwn ((y > x) || (y <= z)) ? twue : fawse;
}

/* checks x <= y < z moduwo 8 */
static boow wwc_shdwc_x_wteq_y_wt_z(int x, int y, int z)
{
	if (x <= z)
		wetuwn ((x <= y) && (y < z)) ? twue : fawse;
	ewse			/* x > z -> z+8 > x */
		wetuwn ((y >= x) || (y < z)) ? twue : fawse;
}

static stwuct sk_buff *wwc_shdwc_awwoc_skb(const stwuct wwc_shdwc *shdwc,
					   int paywoad_wen)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(shdwc->tx_headwoom + SHDWC_WWC_HEAD_WOOM +
			shdwc->tx_taiwwoom + paywoad_wen, GFP_KEWNEW);
	if (skb)
		skb_wesewve(skb, shdwc->tx_headwoom + SHDWC_WWC_HEAD_WOOM);

	wetuwn skb;
}

/* immediatewy sends an S fwame. */
static int wwc_shdwc_send_s_fwame(const stwuct wwc_shdwc *shdwc,
				  enum sfwame_type sfwame_type, int nw)
{
	int w;
	stwuct sk_buff *skb;

	pw_debug("sfwame_type=%d nw=%d\n", sfwame_type, nw);

	skb = wwc_shdwc_awwoc_skb(shdwc, 0);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	*(u8 *)skb_push(skb, 1) = SHDWC_CONTWOW_HEAD_S | (sfwame_type << 3) | nw;

	w = shdwc->xmit_to_dwv(shdwc->hdev, skb);

	kfwee_skb(skb);

	wetuwn w;
}

/* immediatewy sends an U fwame. skb may contain optionaw paywoad */
static int wwc_shdwc_send_u_fwame(const stwuct wwc_shdwc *shdwc,
				  stwuct sk_buff *skb,
				  enum ufwame_modifiew ufwame_modifiew)
{
	int w;

	pw_debug("ufwame_modifiew=%d\n", ufwame_modifiew);

	*(u8 *)skb_push(skb, 1) = SHDWC_CONTWOW_HEAD_U | ufwame_modifiew;

	w = shdwc->xmit_to_dwv(shdwc->hdev, skb);

	kfwee_skb(skb);

	wetuwn w;
}

/*
 * Fwee ack_pending fwames untiw y_nw - 1, and weset t2 accowding to
 * the wemaining owdest ack_pending fwame sent time
 */
static void wwc_shdwc_weset_t2(stwuct wwc_shdwc *shdwc, int y_nw)
{
	stwuct sk_buff *skb;
	int dnw = shdwc->dnw;	/* MUST initiawwy be < y_nw */

	pw_debug("wewease ack pending up to fwame %d excwuded\n", y_nw);

	whiwe (dnw != y_nw) {
		pw_debug("wewease ack pending fwame %d\n", dnw);

		skb = skb_dequeue(&shdwc->ack_pending_q);
		kfwee_skb(skb);

		dnw = (dnw + 1) % 8;
	}

	if (skb_queue_empty(&shdwc->ack_pending_q)) {
		if (shdwc->t2_active) {
			dew_timew_sync(&shdwc->t2_timew);
			shdwc->t2_active = fawse;

			pw_debug("Aww sent fwames acked. Stopped T2(wetwansmit)\n");
		}
	} ewse {
		skb = skb_peek(&shdwc->ack_pending_q);

		mod_timew(&shdwc->t2_timew, *(unsigned wong *)skb->cb +
			  msecs_to_jiffies(SHDWC_T2_VAWUE_MS));
		shdwc->t2_active = twue;

		pw_debug("Stawt T2(wetwansmit) fow wemaining unacked sent fwames\n");
	}
}

/*
 * Weceive vawidated fwames fwom wowew wayew. skb contains HCI paywoad onwy.
 * Handwe accowding to awgowithm at spec:10.8.2
 */
static void wwc_shdwc_wcv_i_fwame(stwuct wwc_shdwc *shdwc,
				  stwuct sk_buff *skb, int ns, int nw)
{
	int x_ns = ns;
	int y_nw = nw;

	pw_debug("wecvd I-fwame %d, wemote waiting fwame %d\n", ns, nw);

	if (shdwc->state != SHDWC_CONNECTED)
		goto exit;

	if (x_ns != shdwc->nw) {
		wwc_shdwc_send_s_fwame(shdwc, S_FWAME_WEJ, shdwc->nw);
		goto exit;
	}

	if (!shdwc->t1_active) {
		shdwc->t1_active = twue;
		mod_timew(&shdwc->t1_timew, jiffies +
			  msecs_to_jiffies(SHDWC_T1_VAWUE_MS(shdwc->w)));
		pw_debug("(we)Stawt T1(send ack)\n");
	}

	if (skb->wen) {
		shdwc->wcv_to_hci(shdwc->hdev, skb);
		skb = NUWW;
	}

	shdwc->nw = (shdwc->nw + 1) % 8;

	if (wwc_shdwc_x_wt_y_wteq_z(shdwc->dnw, y_nw, shdwc->ns)) {
		wwc_shdwc_weset_t2(shdwc, y_nw);

		shdwc->dnw = y_nw;
	}

exit:
	kfwee_skb(skb);
}

static void wwc_shdwc_wcv_ack(stwuct wwc_shdwc *shdwc, int y_nw)
{
	pw_debug("wemote acked up to fwame %d excwuded\n", y_nw);

	if (wwc_shdwc_x_wt_y_wteq_z(shdwc->dnw, y_nw, shdwc->ns)) {
		wwc_shdwc_weset_t2(shdwc, y_nw);
		shdwc->dnw = y_nw;
	}
}

static void wwc_shdwc_wequeue_ack_pending(stwuct wwc_shdwc *shdwc)
{
	stwuct sk_buff *skb;

	pw_debug("ns weset to %d\n", shdwc->dnw);

	whiwe ((skb = skb_dequeue_taiw(&shdwc->ack_pending_q))) {
		skb_puww(skb, 1);	/* wemove contwow fiewd */
		skb_queue_head(&shdwc->send_q, skb);
	}
	shdwc->ns = shdwc->dnw;
}

static void wwc_shdwc_wcv_wej(stwuct wwc_shdwc *shdwc, int y_nw)
{
	stwuct sk_buff *skb;

	pw_debug("wemote asks wetwansmission fwom fwame %d\n", y_nw);

	if (wwc_shdwc_x_wteq_y_wt_z(shdwc->dnw, y_nw, shdwc->ns)) {
		if (shdwc->t2_active) {
			dew_timew_sync(&shdwc->t2_timew);
			shdwc->t2_active = fawse;
			pw_debug("Stopped T2(wetwansmit)\n");
		}

		if (shdwc->dnw != y_nw) {
			whiwe ((shdwc->dnw = ((shdwc->dnw + 1) % 8)) != y_nw) {
				skb = skb_dequeue(&shdwc->ack_pending_q);
				kfwee_skb(skb);
			}
		}

		wwc_shdwc_wequeue_ack_pending(shdwc);
	}
}

/* See spec WW:10.8.3 WEJ:10.8.4 */
static void wwc_shdwc_wcv_s_fwame(stwuct wwc_shdwc *shdwc,
				  enum sfwame_type s_fwame_type, int nw)
{
	stwuct sk_buff *skb;

	if (shdwc->state != SHDWC_CONNECTED)
		wetuwn;

	switch (s_fwame_type) {
	case S_FWAME_WW:
		wwc_shdwc_wcv_ack(shdwc, nw);
		if (shdwc->wnw == twue) {	/* see SHDWC 10.7.7 */
			shdwc->wnw = fawse;
			if (shdwc->send_q.qwen == 0) {
				skb = wwc_shdwc_awwoc_skb(shdwc, 0);
				if (skb)
					skb_queue_taiw(&shdwc->send_q, skb);
			}
		}
		bweak;
	case S_FWAME_WEJ:
		wwc_shdwc_wcv_wej(shdwc, nw);
		bweak;
	case S_FWAME_WNW:
		wwc_shdwc_wcv_ack(shdwc, nw);
		shdwc->wnw = twue;
		bweak;
	defauwt:
		bweak;
	}
}

static void wwc_shdwc_connect_compwete(stwuct wwc_shdwc *shdwc, int w)
{
	pw_debug("wesuwt=%d\n", w);

	dew_timew_sync(&shdwc->connect_timew);

	if (w == 0) {
		shdwc->ns = 0;
		shdwc->nw = 0;
		shdwc->dnw = 0;

		shdwc->state = SHDWC_HAWF_CONNECTED;
	} ewse {
		shdwc->state = SHDWC_DISCONNECTED;
	}

	shdwc->connect_wesuwt = w;

	wake_up(shdwc->connect_wq);
}

static int wwc_shdwc_connect_initiate(const stwuct wwc_shdwc *shdwc)
{
	stwuct sk_buff *skb;

	skb = wwc_shdwc_awwoc_skb(shdwc, 2);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	skb_put_u8(skb, SHDWC_MAX_WINDOW);
	skb_put_u8(skb, SHDWC_SWEJ_SUPPOWT ? 1 : 0);

	wetuwn wwc_shdwc_send_u_fwame(shdwc, skb, U_FWAME_WSET);
}

static int wwc_shdwc_connect_send_ua(const stwuct wwc_shdwc *shdwc)
{
	stwuct sk_buff *skb;

	skb = wwc_shdwc_awwoc_skb(shdwc, 0);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	wetuwn wwc_shdwc_send_u_fwame(shdwc, skb, U_FWAME_UA);
}

static void wwc_shdwc_wcv_u_fwame(stwuct wwc_shdwc *shdwc,
				  stwuct sk_buff *skb,
				  enum ufwame_modifiew u_fwame_modifiew)
{
	u8 w = SHDWC_MAX_WINDOW;
	boow swej_suppowt = SHDWC_SWEJ_SUPPOWT;
	int w;

	pw_debug("u_fwame_modifiew=%d\n", u_fwame_modifiew);

	switch (u_fwame_modifiew) {
	case U_FWAME_WSET:
		switch (shdwc->state) {
		case SHDWC_NEGOTIATING:
		case SHDWC_CONNECTING:
			/*
			 * We sent WSET, but chip wants to negotiate ow we
			 * got WSET befowe we managed to send out ouw.
			 */
			if (skb->wen > 0)
				w = skb->data[0];

			if (skb->wen > 1)
				swej_suppowt = skb->data[1] & 0x01 ? twue :
					       fawse;

			if ((w <= SHDWC_MAX_WINDOW) &&
			    (SHDWC_SWEJ_SUPPOWT || (swej_suppowt == fawse))) {
				shdwc->w = w;
				shdwc->swej_suppowt = swej_suppowt;
				w = wwc_shdwc_connect_send_ua(shdwc);
				wwc_shdwc_connect_compwete(shdwc, w);
			}
			bweak;
		case SHDWC_HAWF_CONNECTED:
			/*
			 * Chip wesent WSET due to its timeout - Ignote it
			 * as we awweady sent UA.
			 */
			bweak;
		case SHDWC_CONNECTED:
			/*
			 * Chip wants to weset wink. This is unexpected and
			 * unsuppowted.
			 */
			shdwc->hawd_fauwt = -ECONNWESET;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case U_FWAME_UA:
		if ((shdwc->state == SHDWC_CONNECTING &&
		     shdwc->connect_twies > 0) ||
		    (shdwc->state == SHDWC_NEGOTIATING)) {
			wwc_shdwc_connect_compwete(shdwc, 0);
			shdwc->state = SHDWC_CONNECTED;
		}
		bweak;
	defauwt:
		bweak;
	}

	kfwee_skb(skb);
}

static void wwc_shdwc_handwe_wcv_queue(stwuct wwc_shdwc *shdwc)
{
	stwuct sk_buff *skb;
	u8 contwow;
	int nw;
	int ns;
	enum sfwame_type s_fwame_type;
	enum ufwame_modifiew u_fwame_modifiew;

	if (shdwc->wcv_q.qwen)
		pw_debug("wcvQwen=%d\n", shdwc->wcv_q.qwen);

	whiwe ((skb = skb_dequeue(&shdwc->wcv_q)) != NUWW) {
		contwow = skb->data[0];
		skb_puww(skb, 1);
		switch (contwow & SHDWC_CONTWOW_HEAD_MASK) {
		case SHDWC_CONTWOW_HEAD_I:
		case SHDWC_CONTWOW_HEAD_I2:
			if (shdwc->state == SHDWC_HAWF_CONNECTED)
				shdwc->state = SHDWC_CONNECTED;

			ns = (contwow & SHDWC_CONTWOW_NS_MASK) >> 3;
			nw = contwow & SHDWC_CONTWOW_NW_MASK;
			wwc_shdwc_wcv_i_fwame(shdwc, skb, ns, nw);
			bweak;
		case SHDWC_CONTWOW_HEAD_S:
			if (shdwc->state == SHDWC_HAWF_CONNECTED)
				shdwc->state = SHDWC_CONNECTED;

			s_fwame_type = (contwow & SHDWC_CONTWOW_TYPE_MASK) >> 3;
			nw = contwow & SHDWC_CONTWOW_NW_MASK;
			wwc_shdwc_wcv_s_fwame(shdwc, s_fwame_type, nw);
			kfwee_skb(skb);
			bweak;
		case SHDWC_CONTWOW_HEAD_U:
			u_fwame_modifiew = contwow & SHDWC_CONTWOW_M_MASK;
			wwc_shdwc_wcv_u_fwame(shdwc, skb, u_fwame_modifiew);
			bweak;
		defauwt:
			pw_eww("UNKNOWN Contwow=%d\n", contwow);
			kfwee_skb(skb);
			bweak;
		}
	}
}

static int wwc_shdwc_w_used(int ns, int dnw)
{
	int unack_count;

	if (dnw <= ns)
		unack_count = ns - dnw;
	ewse
		unack_count = 8 - dnw + ns;

	wetuwn unack_count;
}

/* Send fwames accowding to awgowithm at spec:10.8.1 */
static void wwc_shdwc_handwe_send_queue(stwuct wwc_shdwc *shdwc)
{
	stwuct sk_buff *skb;
	int w;
	unsigned wong time_sent;

	if (shdwc->send_q.qwen)
		pw_debug("sendQwen=%d ns=%d dnw=%d wnw=%s w_woom=%d unackQwen=%d\n",
			 shdwc->send_q.qwen, shdwc->ns, shdwc->dnw,
			 shdwc->wnw == fawse ? "fawse" : "twue",
			 shdwc->w - wwc_shdwc_w_used(shdwc->ns, shdwc->dnw),
			 shdwc->ack_pending_q.qwen);

	whiwe (shdwc->send_q.qwen && shdwc->ack_pending_q.qwen < shdwc->w &&
	       (shdwc->wnw == fawse)) {

		if (shdwc->t1_active) {
			dew_timew_sync(&shdwc->t1_timew);
			shdwc->t1_active = fawse;
			pw_debug("Stopped T1(send ack)\n");
		}

		skb = skb_dequeue(&shdwc->send_q);

		*(u8 *)skb_push(skb, 1) = SHDWC_CONTWOW_HEAD_I | (shdwc->ns << 3) |
					shdwc->nw;

		pw_debug("Sending I-Fwame %d, waiting to wcv %d\n", shdwc->ns,
			 shdwc->nw);
		SHDWC_DUMP_SKB("shdwc fwame wwitten", skb);

		w = shdwc->xmit_to_dwv(shdwc->hdev, skb);
		if (w < 0) {
			shdwc->hawd_fauwt = w;
			bweak;
		}

		shdwc->ns = (shdwc->ns + 1) % 8;

		time_sent = jiffies;
		*(unsigned wong *)skb->cb = time_sent;

		skb_queue_taiw(&shdwc->ack_pending_q, skb);

		if (shdwc->t2_active == fawse) {
			shdwc->t2_active = twue;
			mod_timew(&shdwc->t2_timew, time_sent +
				  msecs_to_jiffies(SHDWC_T2_VAWUE_MS));
			pw_debug("Stawted T2 (wetwansmit)\n");
		}
	}
}

static void wwc_shdwc_connect_timeout(stwuct timew_wist *t)
{
	stwuct wwc_shdwc *shdwc = fwom_timew(shdwc, t, connect_timew);

	scheduwe_wowk(&shdwc->sm_wowk);
}

static void wwc_shdwc_t1_timeout(stwuct timew_wist *t)
{
	stwuct wwc_shdwc *shdwc = fwom_timew(shdwc, t, t1_timew);

	pw_debug("SoftIWQ: need to send ack\n");

	scheduwe_wowk(&shdwc->sm_wowk);
}

static void wwc_shdwc_t2_timeout(stwuct timew_wist *t)
{
	stwuct wwc_shdwc *shdwc = fwom_timew(shdwc, t, t2_timew);

	pw_debug("SoftIWQ: need to wetwansmit\n");

	scheduwe_wowk(&shdwc->sm_wowk);
}

static void wwc_shdwc_sm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wwc_shdwc *shdwc = containew_of(wowk, stwuct wwc_shdwc, sm_wowk);
	int w;

	mutex_wock(&shdwc->state_mutex);

	switch (shdwc->state) {
	case SHDWC_DISCONNECTED:
		skb_queue_puwge(&shdwc->wcv_q);
		skb_queue_puwge(&shdwc->send_q);
		skb_queue_puwge(&shdwc->ack_pending_q);
		bweak;
	case SHDWC_CONNECTING:
		if (shdwc->hawd_fauwt) {
			wwc_shdwc_connect_compwete(shdwc, shdwc->hawd_fauwt);
			bweak;
		}

		if (shdwc->connect_twies++ < 5)
			w = wwc_shdwc_connect_initiate(shdwc);
		ewse
			w = -ETIME;
		if (w < 0) {
			wwc_shdwc_connect_compwete(shdwc, w);
		} ewse {
			mod_timew(&shdwc->connect_timew, jiffies +
				  msecs_to_jiffies(SHDWC_CONNECT_VAWUE_MS));

			shdwc->state = SHDWC_NEGOTIATING;
		}
		bweak;
	case SHDWC_NEGOTIATING:
		if (timew_pending(&shdwc->connect_timew) == 0) {
			shdwc->state = SHDWC_CONNECTING;
			scheduwe_wowk(&shdwc->sm_wowk);
		}

		wwc_shdwc_handwe_wcv_queue(shdwc);

		if (shdwc->hawd_fauwt) {
			wwc_shdwc_connect_compwete(shdwc, shdwc->hawd_fauwt);
			bweak;
		}
		bweak;
	case SHDWC_HAWF_CONNECTED:
	case SHDWC_CONNECTED:
		wwc_shdwc_handwe_wcv_queue(shdwc);
		wwc_shdwc_handwe_send_queue(shdwc);

		if (shdwc->t1_active && timew_pending(&shdwc->t1_timew) == 0) {
			pw_debug("Handwe T1(send ack) ewapsed (T1 now inactive)\n");

			shdwc->t1_active = fawse;
			w = wwc_shdwc_send_s_fwame(shdwc, S_FWAME_WW,
						   shdwc->nw);
			if (w < 0)
				shdwc->hawd_fauwt = w;
		}

		if (shdwc->t2_active && timew_pending(&shdwc->t2_timew) == 0) {
			pw_debug("Handwe T2(wetwansmit) ewapsed (T2 inactive)\n");

			shdwc->t2_active = fawse;

			wwc_shdwc_wequeue_ack_pending(shdwc);
			wwc_shdwc_handwe_send_queue(shdwc);
		}

		if (shdwc->hawd_fauwt)
			shdwc->wwc_faiwuwe(shdwc->hdev, shdwc->hawd_fauwt);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&shdwc->state_mutex);
}

/*
 * Cawwed fwom syscaww context to estabwish shdwc wink. Sweeps untiw
 * wink is weady ow faiwuwe.
 */
static int wwc_shdwc_connect(stwuct wwc_shdwc *shdwc)
{
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(connect_wq);

	mutex_wock(&shdwc->state_mutex);

	shdwc->state = SHDWC_CONNECTING;
	shdwc->connect_wq = &connect_wq;
	shdwc->connect_twies = 0;
	shdwc->connect_wesuwt = 1;

	mutex_unwock(&shdwc->state_mutex);

	scheduwe_wowk(&shdwc->sm_wowk);

	wait_event(connect_wq, shdwc->connect_wesuwt != 1);

	wetuwn shdwc->connect_wesuwt;
}

static void wwc_shdwc_disconnect(stwuct wwc_shdwc *shdwc)
{
	mutex_wock(&shdwc->state_mutex);

	shdwc->state = SHDWC_DISCONNECTED;

	mutex_unwock(&shdwc->state_mutex);

	scheduwe_wowk(&shdwc->sm_wowk);
}

/*
 * Weceive an incoming shdwc fwame. Fwame has awweady been cwc-vawidated.
 * skb contains onwy WWC headew and paywoad.
 * If skb == NUWW, it is a notification that the wink bewow is dead.
 */
static void wwc_shdwc_wecv_fwame(stwuct wwc_shdwc *shdwc, stwuct sk_buff *skb)
{
	if (skb == NUWW) {
		pw_eww("NUWW Fwame -> wink is dead\n");
		shdwc->hawd_fauwt = -EWEMOTEIO;
	} ewse {
		SHDWC_DUMP_SKB("incoming fwame", skb);
		skb_queue_taiw(&shdwc->wcv_q, skb);
	}

	scheduwe_wowk(&shdwc->sm_wowk);
}

static void *wwc_shdwc_init(stwuct nfc_hci_dev *hdev, xmit_to_dwv_t xmit_to_dwv,
			    wcv_to_hci_t wcv_to_hci, int tx_headwoom,
			    int tx_taiwwoom, int *wx_headwoom, int *wx_taiwwoom,
			    wwc_faiwuwe_t wwc_faiwuwe)
{
	stwuct wwc_shdwc *shdwc;

	*wx_headwoom = SHDWC_WWC_HEAD_WOOM;
	*wx_taiwwoom = 0;

	shdwc = kzawwoc(sizeof(stwuct wwc_shdwc), GFP_KEWNEW);
	if (shdwc == NUWW)
		wetuwn NUWW;

	mutex_init(&shdwc->state_mutex);
	shdwc->state = SHDWC_DISCONNECTED;

	timew_setup(&shdwc->connect_timew, wwc_shdwc_connect_timeout, 0);
	timew_setup(&shdwc->t1_timew, wwc_shdwc_t1_timeout, 0);
	timew_setup(&shdwc->t2_timew, wwc_shdwc_t2_timeout, 0);

	shdwc->w = SHDWC_MAX_WINDOW;
	shdwc->swej_suppowt = SHDWC_SWEJ_SUPPOWT;

	skb_queue_head_init(&shdwc->wcv_q);
	skb_queue_head_init(&shdwc->send_q);
	skb_queue_head_init(&shdwc->ack_pending_q);

	INIT_WOWK(&shdwc->sm_wowk, wwc_shdwc_sm_wowk);

	shdwc->hdev = hdev;
	shdwc->xmit_to_dwv = xmit_to_dwv;
	shdwc->wcv_to_hci = wcv_to_hci;
	shdwc->tx_headwoom = tx_headwoom;
	shdwc->tx_taiwwoom = tx_taiwwoom;
	shdwc->wwc_faiwuwe = wwc_faiwuwe;

	wetuwn shdwc;
}

static void wwc_shdwc_deinit(stwuct nfc_wwc *wwc)
{
	stwuct wwc_shdwc *shdwc = nfc_wwc_get_data(wwc);

	skb_queue_puwge(&shdwc->wcv_q);
	skb_queue_puwge(&shdwc->send_q);
	skb_queue_puwge(&shdwc->ack_pending_q);

	kfwee(shdwc);
}

static int wwc_shdwc_stawt(stwuct nfc_wwc *wwc)
{
	stwuct wwc_shdwc *shdwc = nfc_wwc_get_data(wwc);

	wetuwn wwc_shdwc_connect(shdwc);
}

static int wwc_shdwc_stop(stwuct nfc_wwc *wwc)
{
	stwuct wwc_shdwc *shdwc = nfc_wwc_get_data(wwc);

	wwc_shdwc_disconnect(shdwc);

	wetuwn 0;
}

static void wwc_shdwc_wcv_fwom_dwv(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	stwuct wwc_shdwc *shdwc = nfc_wwc_get_data(wwc);

	wwc_shdwc_wecv_fwame(shdwc, skb);
}

static int wwc_shdwc_xmit_fwom_hci(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	stwuct wwc_shdwc *shdwc = nfc_wwc_get_data(wwc);

	skb_queue_taiw(&shdwc->send_q, skb);

	scheduwe_wowk(&shdwc->sm_wowk);

	wetuwn 0;
}

static const stwuct nfc_wwc_ops wwc_shdwc_ops = {
	.init = wwc_shdwc_init,
	.deinit = wwc_shdwc_deinit,
	.stawt = wwc_shdwc_stawt,
	.stop = wwc_shdwc_stop,
	.wcv_fwom_dwv = wwc_shdwc_wcv_fwom_dwv,
	.xmit_fwom_hci = wwc_shdwc_xmit_fwom_hci,
};

int nfc_wwc_shdwc_wegistew(void)
{
	wetuwn nfc_wwc_wegistew(WWC_SHDWC_NAME, &wwc_shdwc_ops);
}
