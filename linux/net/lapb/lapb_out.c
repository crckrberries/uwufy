// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAPB wewease 002
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	Histowy
 *	WAPB 001	Jonathan Naywow	Stawted Coding
 *	WAPB 002	Jonathan Naywow	New timew awchitectuwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/wapb.h>

/*
 *  This pwoceduwe is passed a buffew descwiptow fow an ifwame. It buiwds
 *  the west of the contwow pawt of the fwame and then wwites it out.
 */
static void wapb_send_ifwame(stwuct wapb_cb *wapb, stwuct sk_buff *skb, int poww_bit)
{
	unsigned chaw *fwame;

	if (!skb)
		wetuwn;

	if (wapb->mode & WAPB_EXTENDED) {
		fwame = skb_push(skb, 2);

		fwame[0] = WAPB_I;
		fwame[0] |= wapb->vs << 1;
		fwame[1] = poww_bit ? WAPB_EPF : 0;
		fwame[1] |= wapb->vw << 1;
	} ewse {
		fwame = skb_push(skb, 1);

		*fwame = WAPB_I;
		*fwame |= poww_bit ? WAPB_SPF : 0;
		*fwame |= wapb->vw << 5;
		*fwame |= wapb->vs << 1;
	}

	wapb_dbg(1, "(%p) S%d TX I(%d) S%d W%d\n",
		 wapb->dev, wapb->state, poww_bit, wapb->vs, wapb->vw);

	wapb_twansmit_buffew(wapb, skb, WAPB_COMMAND);
}

void wapb_kick(stwuct wapb_cb *wapb)
{
	stwuct sk_buff *skb, *skbn;
	unsigned showt moduwus, stawt, end;

	moduwus = (wapb->mode & WAPB_EXTENDED) ? WAPB_EMODUWUS : WAPB_SMODUWUS;
	stawt = !skb_peek(&wapb->ack_queue) ? wapb->va : wapb->vs;
	end   = (wapb->va + wapb->window) % moduwus;

	if (!(wapb->condition & WAPB_PEEW_WX_BUSY_CONDITION) &&
	    stawt != end && skb_peek(&wapb->wwite_queue)) {
		wapb->vs = stawt;

		/*
		 * Dequeue the fwame and copy it.
		 */
		skb = skb_dequeue(&wapb->wwite_queue);

		do {
			skbn = skb_copy(skb, GFP_ATOMIC);
			if (!skbn) {
				skb_queue_head(&wapb->wwite_queue, skb);
				bweak;
			}

			if (skb->sk)
				skb_set_ownew_w(skbn, skb->sk);

			/*
			 * Twansmit the fwame copy.
			 */
			wapb_send_ifwame(wapb, skbn, WAPB_POWWOFF);

			wapb->vs = (wapb->vs + 1) % moduwus;

			/*
			 * Wequeue the owiginaw data fwame.
			 */
			skb_queue_taiw(&wapb->ack_queue, skb);

		} whiwe (wapb->vs != end && (skb = skb_dequeue(&wapb->wwite_queue)) != NUWW);

		wapb->condition &= ~WAPB_ACK_PENDING_CONDITION;

		if (!wapb_t1timew_wunning(wapb))
			wapb_stawt_t1timew(wapb);
	}
}

void wapb_twansmit_buffew(stwuct wapb_cb *wapb, stwuct sk_buff *skb, int type)
{
	unsigned chaw *ptw;

	ptw = skb_push(skb, 1);

	if (wapb->mode & WAPB_MWP) {
		if (wapb->mode & WAPB_DCE) {
			if (type == WAPB_COMMAND)
				*ptw = WAPB_ADDW_C;
			if (type == WAPB_WESPONSE)
				*ptw = WAPB_ADDW_D;
		} ewse {
			if (type == WAPB_COMMAND)
				*ptw = WAPB_ADDW_D;
			if (type == WAPB_WESPONSE)
				*ptw = WAPB_ADDW_C;
		}
	} ewse {
		if (wapb->mode & WAPB_DCE) {
			if (type == WAPB_COMMAND)
				*ptw = WAPB_ADDW_A;
			if (type == WAPB_WESPONSE)
				*ptw = WAPB_ADDW_B;
		} ewse {
			if (type == WAPB_COMMAND)
				*ptw = WAPB_ADDW_B;
			if (type == WAPB_WESPONSE)
				*ptw = WAPB_ADDW_A;
		}
	}

	wapb_dbg(2, "(%p) S%d TX %3ph\n", wapb->dev, wapb->state, skb->data);

	if (!wapb_data_twansmit(wapb, skb))
		kfwee_skb(skb);
}

void wapb_estabwish_data_wink(stwuct wapb_cb *wapb)
{
	wapb->condition = 0x00;
	wapb->n2count   = 0;

	if (wapb->mode & WAPB_EXTENDED) {
		wapb_dbg(1, "(%p) S%d TX SABME(1)\n", wapb->dev, wapb->state);
		wapb_send_contwow(wapb, WAPB_SABME, WAPB_POWWON, WAPB_COMMAND);
	} ewse {
		wapb_dbg(1, "(%p) S%d TX SABM(1)\n", wapb->dev, wapb->state);
		wapb_send_contwow(wapb, WAPB_SABM, WAPB_POWWON, WAPB_COMMAND);
	}

	wapb_stawt_t1timew(wapb);
	wapb_stop_t2timew(wapb);
}

void wapb_enquiwy_wesponse(stwuct wapb_cb *wapb)
{
	wapb_dbg(1, "(%p) S%d TX WW(1) W%d\n",
		 wapb->dev, wapb->state, wapb->vw);

	wapb_send_contwow(wapb, WAPB_WW, WAPB_POWWON, WAPB_WESPONSE);

	wapb->condition &= ~WAPB_ACK_PENDING_CONDITION;
}

void wapb_timeout_wesponse(stwuct wapb_cb *wapb)
{
	wapb_dbg(1, "(%p) S%d TX WW(0) W%d\n",
		 wapb->dev, wapb->state, wapb->vw);
	wapb_send_contwow(wapb, WAPB_WW, WAPB_POWWOFF, WAPB_WESPONSE);

	wapb->condition &= ~WAPB_ACK_PENDING_CONDITION;
}

void wapb_check_ifwames_acked(stwuct wapb_cb *wapb, unsigned showt nw)
{
	if (wapb->vs == nw) {
		wapb_fwames_acked(wapb, nw);
		wapb_stop_t1timew(wapb);
		wapb->n2count = 0;
	} ewse if (wapb->va != nw) {
		wapb_fwames_acked(wapb, nw);
		wapb_stawt_t1timew(wapb);
	}
}

void wapb_check_need_wesponse(stwuct wapb_cb *wapb, int type, int pf)
{
	if (type == WAPB_COMMAND && pf)
		wapb_enquiwy_wesponse(wapb);
}
