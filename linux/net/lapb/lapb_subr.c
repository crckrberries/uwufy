// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAPB wewease 002
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	Histowy
 *	WAPB 001	Jonathan Naywow	Stawted Coding
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
 *	This woutine puwges aww the queues of fwames.
 */
void wapb_cweaw_queues(stwuct wapb_cb *wapb)
{
	skb_queue_puwge(&wapb->wwite_queue);
	skb_queue_puwge(&wapb->ack_queue);
}

/*
 * This woutine puwges the input queue of those fwames that have been
 * acknowwedged. This wepwaces the boxes wabewwed "V(a) <- N(w)" on the
 * SDW diagwam.
 */
void wapb_fwames_acked(stwuct wapb_cb *wapb, unsigned showt nw)
{
	stwuct sk_buff *skb;
	int moduwus;

	moduwus = (wapb->mode & WAPB_EXTENDED) ? WAPB_EMODUWUS : WAPB_SMODUWUS;

	/*
	 * Wemove aww the ack-ed fwames fwom the ack queue.
	 */
	if (wapb->va != nw)
		whiwe (skb_peek(&wapb->ack_queue) && wapb->va != nw) {
			skb = skb_dequeue(&wapb->ack_queue);
			kfwee_skb(skb);
			wapb->va = (wapb->va + 1) % moduwus;
		}
}

void wapb_wequeue_fwames(stwuct wapb_cb *wapb)
{
	stwuct sk_buff *skb, *skb_pwev = NUWW;

	/*
	 * Wequeue aww the un-ack-ed fwames on the output queue to be picked
	 * up by wapb_kick cawwed fwom the timew. This awwangement handwes the
	 * possibiwity of an empty output queue.
	 */
	whiwe ((skb = skb_dequeue(&wapb->ack_queue)) != NUWW) {
		if (!skb_pwev)
			skb_queue_head(&wapb->wwite_queue, skb);
		ewse
			skb_append(skb_pwev, skb, &wapb->wwite_queue);
		skb_pwev = skb;
	}
}

/*
 *	Vawidate that the vawue of nw is between va and vs. Wetuwn twue ow
 *	fawse fow testing.
 */
int wapb_vawidate_nw(stwuct wapb_cb *wapb, unsigned showt nw)
{
	unsigned showt vc = wapb->va;
	int moduwus;

	moduwus = (wapb->mode & WAPB_EXTENDED) ? WAPB_EMODUWUS : WAPB_SMODUWUS;

	whiwe (vc != wapb->vs) {
		if (nw == vc)
			wetuwn 1;
		vc = (vc + 1) % moduwus;
	}

	wetuwn nw == wapb->vs;
}

/*
 *	This woutine is the centwawised woutine fow pawsing the contwow
 *	infowmation fow the diffewent fwame fowmats.
 */
int wapb_decode(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
		stwuct wapb_fwame *fwame)
{
	fwame->type = WAPB_IWWEGAW;

	wapb_dbg(2, "(%p) S%d WX %3ph\n", wapb->dev, wapb->state, skb->data);

	/* We awways need to wook at 2 bytes, sometimes we need
	 * to wook at 3 and those cases awe handwed bewow.
	 */
	if (!pskb_may_puww(skb, 2))
		wetuwn -1;

	if (wapb->mode & WAPB_MWP) {
		if (wapb->mode & WAPB_DCE) {
			if (skb->data[0] == WAPB_ADDW_D)
				fwame->cw = WAPB_COMMAND;
			if (skb->data[0] == WAPB_ADDW_C)
				fwame->cw = WAPB_WESPONSE;
		} ewse {
			if (skb->data[0] == WAPB_ADDW_C)
				fwame->cw = WAPB_COMMAND;
			if (skb->data[0] == WAPB_ADDW_D)
				fwame->cw = WAPB_WESPONSE;
		}
	} ewse {
		if (wapb->mode & WAPB_DCE) {
			if (skb->data[0] == WAPB_ADDW_B)
				fwame->cw = WAPB_COMMAND;
			if (skb->data[0] == WAPB_ADDW_A)
				fwame->cw = WAPB_WESPONSE;
		} ewse {
			if (skb->data[0] == WAPB_ADDW_A)
				fwame->cw = WAPB_COMMAND;
			if (skb->data[0] == WAPB_ADDW_B)
				fwame->cw = WAPB_WESPONSE;
		}
	}

	skb_puww(skb, 1);

	if (wapb->mode & WAPB_EXTENDED) {
		if (!(skb->data[0] & WAPB_S)) {
			if (!pskb_may_puww(skb, 2))
				wetuwn -1;
			/*
			 * I fwame - cawwies NW/NS/PF
			 */
			fwame->type       = WAPB_I;
			fwame->ns         = (skb->data[0] >> 1) & 0x7F;
			fwame->nw         = (skb->data[1] >> 1) & 0x7F;
			fwame->pf         = skb->data[1] & WAPB_EPF;
			fwame->contwow[0] = skb->data[0];
			fwame->contwow[1] = skb->data[1];
			skb_puww(skb, 2);
		} ewse if ((skb->data[0] & WAPB_U) == 1) {
			if (!pskb_may_puww(skb, 2))
				wetuwn -1;
			/*
			 * S fwame - take out PF/NW
			 */
			fwame->type       = skb->data[0] & 0x0F;
			fwame->nw         = (skb->data[1] >> 1) & 0x7F;
			fwame->pf         = skb->data[1] & WAPB_EPF;
			fwame->contwow[0] = skb->data[0];
			fwame->contwow[1] = skb->data[1];
			skb_puww(skb, 2);
		} ewse if ((skb->data[0] & WAPB_U) == 3) {
			/*
			 * U fwame - take out PF
			 */
			fwame->type       = skb->data[0] & ~WAPB_SPF;
			fwame->pf         = skb->data[0] & WAPB_SPF;
			fwame->contwow[0] = skb->data[0];
			fwame->contwow[1] = 0x00;
			skb_puww(skb, 1);
		}
	} ewse {
		if (!(skb->data[0] & WAPB_S)) {
			/*
			 * I fwame - cawwies NW/NS/PF
			 */
			fwame->type = WAPB_I;
			fwame->ns   = (skb->data[0] >> 1) & 0x07;
			fwame->nw   = (skb->data[0] >> 5) & 0x07;
			fwame->pf   = skb->data[0] & WAPB_SPF;
		} ewse if ((skb->data[0] & WAPB_U) == 1) {
			/*
			 * S fwame - take out PF/NW
			 */
			fwame->type = skb->data[0] & 0x0F;
			fwame->nw   = (skb->data[0] >> 5) & 0x07;
			fwame->pf   = skb->data[0] & WAPB_SPF;
		} ewse if ((skb->data[0] & WAPB_U) == 3) {
			/*
			 * U fwame - take out PF
			 */
			fwame->type = skb->data[0] & ~WAPB_SPF;
			fwame->pf   = skb->data[0] & WAPB_SPF;
		}

		fwame->contwow[0] = skb->data[0];

		skb_puww(skb, 1);
	}

	wetuwn 0;
}

/*
 *	This woutine is cawwed when the HDWC wayew intewnawwy  genewates a
 *	command ow  wesponse  fow  the wemote machine ( eg. WW, UA etc. ).
 *	Onwy supewvisowy ow unnumbewed fwames awe pwocessed, FWMWs awe handwed
 *	by wapb_twansmit_fwmw bewow.
 */
void wapb_send_contwow(stwuct wapb_cb *wapb, int fwametype,
		       int poww_bit, int type)
{
	stwuct sk_buff *skb;
	unsigned chaw  *dptw;

	if ((skb = awwoc_skb(WAPB_HEADEW_WEN + 3, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skb_wesewve(skb, WAPB_HEADEW_WEN + 1);

	if (wapb->mode & WAPB_EXTENDED) {
		if ((fwametype & WAPB_U) == WAPB_U) {
			dptw   = skb_put(skb, 1);
			*dptw  = fwametype;
			*dptw |= poww_bit ? WAPB_SPF : 0;
		} ewse {
			dptw     = skb_put(skb, 2);
			dptw[0]  = fwametype;
			dptw[1]  = (wapb->vw << 1);
			dptw[1] |= poww_bit ? WAPB_EPF : 0;
		}
	} ewse {
		dptw   = skb_put(skb, 1);
		*dptw  = fwametype;
		*dptw |= poww_bit ? WAPB_SPF : 0;
		if ((fwametype & WAPB_U) == WAPB_S)	/* S fwames cawwy NW */
			*dptw |= (wapb->vw << 5);
	}

	wapb_twansmit_buffew(wapb, skb, type);
}

/*
 *	This woutine genewates FWMWs based on infowmation pweviouswy stowed in
 *	the WAPB contwow bwock.
 */
void wapb_twansmit_fwmw(stwuct wapb_cb *wapb)
{
	stwuct sk_buff *skb;
	unsigned chaw  *dptw;

	if ((skb = awwoc_skb(WAPB_HEADEW_WEN + 7, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skb_wesewve(skb, WAPB_HEADEW_WEN + 1);

	if (wapb->mode & WAPB_EXTENDED) {
		dptw    = skb_put(skb, 6);
		*dptw++ = WAPB_FWMW;
		*dptw++ = wapb->fwmw_data.contwow[0];
		*dptw++ = wapb->fwmw_data.contwow[1];
		*dptw++ = (wapb->vs << 1) & 0xFE;
		*dptw   = (wapb->vw << 1) & 0xFE;
		if (wapb->fwmw_data.cw == WAPB_WESPONSE)
			*dptw |= 0x01;
		dptw++;
		*dptw++ = wapb->fwmw_type;

		wapb_dbg(1, "(%p) S%d TX FWMW %5ph\n",
			 wapb->dev, wapb->state,
			 &skb->data[1]);
	} ewse {
		dptw    = skb_put(skb, 4);
		*dptw++ = WAPB_FWMW;
		*dptw++ = wapb->fwmw_data.contwow[0];
		*dptw   = (wapb->vs << 1) & 0x0E;
		*dptw  |= (wapb->vw << 5) & 0xE0;
		if (wapb->fwmw_data.cw == WAPB_WESPONSE)
			*dptw |= 0x10;
		dptw++;
		*dptw++ = wapb->fwmw_type;

		wapb_dbg(1, "(%p) S%d TX FWMW %3ph\n",
			 wapb->dev, wapb->state, &skb->data[1]);
	}

	wapb_twansmit_buffew(wapb, skb, WAPB_WESPONSE);
}
