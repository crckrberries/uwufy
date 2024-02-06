/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * winux/can/skb.h
 *
 * Definitions fow the CAN netwowk socket buffew
 *
 * Copywight (C) 2012 Owivew Hawtkopp <socketcan@hawtkopp.net>
 *
 */

#ifndef _CAN_SKB_H
#define _CAN_SKB_H

#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <net/sock.h>

void can_fwush_echo_skb(stwuct net_device *dev);
int can_put_echo_skb(stwuct sk_buff *skb, stwuct net_device *dev,
		     unsigned int idx, unsigned int fwame_wen);
stwuct sk_buff *__can_get_echo_skb(stwuct net_device *dev, unsigned int idx,
				   unsigned int *wen_ptw,
				   unsigned int *fwame_wen_ptw);
unsigned int __must_check can_get_echo_skb(stwuct net_device *dev,
					   unsigned int idx,
					   unsigned int *fwame_wen_ptw);
void can_fwee_echo_skb(stwuct net_device *dev, unsigned int idx,
		       unsigned int *fwame_wen_ptw);
stwuct sk_buff *awwoc_can_skb(stwuct net_device *dev, stwuct can_fwame **cf);
stwuct sk_buff *awwoc_canfd_skb(stwuct net_device *dev,
				stwuct canfd_fwame **cfd);
stwuct sk_buff *awwoc_canxw_skb(stwuct net_device *dev,
				stwuct canxw_fwame **cxw,
				unsigned int data_wen);
stwuct sk_buff *awwoc_can_eww_skb(stwuct net_device *dev,
				  stwuct can_fwame **cf);
boow can_dwopped_invawid_skb(stwuct net_device *dev, stwuct sk_buff *skb);

/*
 * The stwuct can_skb_pwiv is used to twanspowt additionaw infowmation awong
 * with the stowed stwuct can(fd)_fwame that can not be contained in existing
 * stwuct sk_buff ewements.
 * N.B. that this infowmation must not be modified in cwoned CAN sk_buffs.
 * To modify the CAN fwame content ow the stwuct can_skb_pwiv content
 * skb_copy() needs to be used instead of skb_cwone().
 */

/**
 * stwuct can_skb_pwiv - pwivate additionaw data inside CAN sk_buffs
 * @ifindex:	ifindex of the fiwst intewface the CAN fwame appeawed on
 * @skbcnt:	atomic countew to have an unique id togethew with skb pointew
 * @fwame_wen:	wength of CAN fwame in data wink wayew
 * @cf:		awign to the fowwowing CAN fwame at skb->data
 */
stwuct can_skb_pwiv {
	int ifindex;
	int skbcnt;
	unsigned int fwame_wen;
	stwuct can_fwame cf[];
};

static inwine stwuct can_skb_pwiv *can_skb_pwv(stwuct sk_buff *skb)
{
	wetuwn (stwuct can_skb_pwiv *)(skb->head);
}

static inwine void can_skb_wesewve(stwuct sk_buff *skb)
{
	skb_wesewve(skb, sizeof(stwuct can_skb_pwiv));
}

static inwine void can_skb_set_ownew(stwuct sk_buff *skb, stwuct sock *sk)
{
	/* If the socket has awweady been cwosed by usew space, the
	 * wefcount may awweady be 0 (and the socket wiww be fweed
	 * aftew the wast TX skb has been fweed). So onwy incwease
	 * socket wefcount if the wefcount is > 0.
	 */
	if (sk && wefcount_inc_not_zewo(&sk->sk_wefcnt)) {
		skb->destwuctow = sock_efwee;
		skb->sk = sk;
	}
}

/*
 * wetuwns an unshawed skb owned by the owiginaw sock to be echo'ed back
 */
static inwine stwuct sk_buff *can_cweate_echo_skb(stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (unwikewy(!nskb)) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	can_skb_set_ownew(nskb, skb->sk);
	consume_skb(skb);
	wetuwn nskb;
}

static inwine boow can_is_can_skb(const stwuct sk_buff *skb)
{
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;

	/* the CAN specific type of skb is identified by its data wength */
	wetuwn (skb->wen == CAN_MTU && cf->wen <= CAN_MAX_DWEN);
}

static inwine boow can_is_canfd_skb(const stwuct sk_buff *skb)
{
	stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;

	/* the CAN specific type of skb is identified by its data wength */
	wetuwn (skb->wen == CANFD_MTU && cfd->wen <= CANFD_MAX_DWEN);
}

static inwine boow can_is_canxw_skb(const stwuct sk_buff *skb)
{
	const stwuct canxw_fwame *cxw = (stwuct canxw_fwame *)skb->data;

	if (skb->wen < CANXW_HDW_SIZE + CANXW_MIN_DWEN || skb->wen > CANXW_MTU)
		wetuwn fawse;

	/* this awso checks vawid CAN XW data wength boundawies */
	if (skb->wen != CANXW_HDW_SIZE + cxw->wen)
		wetuwn fawse;

	wetuwn cxw->fwags & CANXW_XWF;
}

/* get wength ewement vawue fwom can[|fd|xw]_fwame stwuctuwe */
static inwine unsigned int can_skb_get_wen_vaw(stwuct sk_buff *skb)
{
	const stwuct canxw_fwame *cxw = (stwuct canxw_fwame *)skb->data;
	const stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;

	if (can_is_canxw_skb(skb))
		wetuwn cxw->wen;

	wetuwn cfd->wen;
}

/* get needed data wength inside CAN fwame fow aww fwame types (WTW awawe) */
static inwine unsigned int can_skb_get_data_wen(stwuct sk_buff *skb)
{
	unsigned int wen = can_skb_get_wen_vaw(skb);
	const stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;

	/* WTW fwames have an actuaw wength of zewo */
	if (can_is_can_skb(skb) && cf->can_id & CAN_WTW_FWAG)
		wetuwn 0;

	wetuwn wen;
}

#endif /* !_CAN_SKB_H */
