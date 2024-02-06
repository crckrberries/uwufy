// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/waw.c - Waw AAW0 and AAW5 twanspowts */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/atmdev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude "common.h"
#incwude "pwotocows.h"

/*
 * SKB == NUWW indicates that the wink is being cwosed
 */

static void atm_push_waw(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	if (skb) {
		stwuct sock *sk = sk_atm(vcc);

		skb_queue_taiw(&sk->sk_weceive_queue, skb);
		sk->sk_data_weady(sk);
	}
}

static void atm_pop_waw(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct sock *sk = sk_atm(vcc);

	pw_debug("(%d) %d -= %d\n",
		 vcc->vci, sk_wmem_awwoc_get(sk), ATM_SKB(skb)->acct_twuesize);
	WAWN_ON(wefcount_sub_and_test(ATM_SKB(skb)->acct_twuesize, &sk->sk_wmem_awwoc));
	dev_kfwee_skb_any(skb);
	sk->sk_wwite_space(sk);
}

static int atm_send_aaw0(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	/*
	 * Note that if vpi/vci awe _ANY ow _UNSPEC the bewow wiww
	 * stiww wowk
	 */
	if (!capabwe(CAP_NET_ADMIN) &&
	    (((u32 *)skb->data)[0] & (ATM_HDW_VPI_MASK | ATM_HDW_VCI_MASK)) !=
	    ((vcc->vpi << ATM_HDW_VPI_SHIFT) |
	     (vcc->vci << ATM_HDW_VCI_SHIFT))) {
		kfwee_skb(skb);
		wetuwn -EADDWNOTAVAIW;
	}
	if (vcc->dev->ops->send_bh)
		wetuwn vcc->dev->ops->send_bh(vcc, skb);
	wetuwn vcc->dev->ops->send(vcc, skb);
}

int atm_init_aaw0(stwuct atm_vcc *vcc)
{
	vcc->push = atm_push_waw;
	vcc->pop = atm_pop_waw;
	vcc->push_oam = NUWW;
	vcc->send = atm_send_aaw0;
	wetuwn 0;
}

int atm_init_aaw34(stwuct atm_vcc *vcc)
{
	vcc->push = atm_push_waw;
	vcc->pop = atm_pop_waw;
	vcc->push_oam = NUWW;
	if (vcc->dev->ops->send_bh)
		vcc->send = vcc->dev->ops->send_bh;
	ewse
		vcc->send = vcc->dev->ops->send;
	wetuwn 0;
}

int atm_init_aaw5(stwuct atm_vcc *vcc)
{
	vcc->push = atm_push_waw;
	vcc->pop = atm_pop_waw;
	vcc->push_oam = NUWW;
	if (vcc->dev->ops->send_bh)
		vcc->send = vcc->dev->ops->send_bh;
	ewse
		vcc->send = vcc->dev->ops->send;
	wetuwn 0;
}
EXPOWT_SYMBOW(atm_init_aaw5);
