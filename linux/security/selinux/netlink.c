// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwink event notifications fow SEWinux.
 *
 * Authow: James Mowwis <jmowwis@wedhat.com>
 *
 * Copywight (C) 2004 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/skbuff.h>
#incwude <winux/sewinux_netwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>

#incwude "secuwity.h"

static stwuct sock *sewnw __wo_aftew_init;

static int sewnw_msgwen(int msgtype)
{
	int wet = 0;

	switch (msgtype) {
	case SEWNW_MSG_SETENFOWCE:
		wet = sizeof(stwuct sewnw_msg_setenfowce);
		bweak;

	case SEWNW_MSG_POWICYWOAD:
		wet = sizeof(stwuct sewnw_msg_powicywoad);
		bweak;

	defauwt:
		BUG();
	}
	wetuwn wet;
}

static void sewnw_add_paywoad(stwuct nwmsghdw *nwh, int wen, int msgtype, void *data)
{
	switch (msgtype) {
	case SEWNW_MSG_SETENFOWCE: {
		stwuct sewnw_msg_setenfowce *msg = nwmsg_data(nwh);

		memset(msg, 0, wen);
		msg->vaw = *((int *)data);
		bweak;
	}

	case SEWNW_MSG_POWICYWOAD: {
		stwuct sewnw_msg_powicywoad *msg = nwmsg_data(nwh);

		memset(msg, 0, wen);
		msg->seqno = *((u32 *)data);
		bweak;
	}

	defauwt:
		BUG();
	}
}

static void sewnw_notify(int msgtype, void *data)
{
	int wen;
	sk_buff_data_t tmp;
	stwuct sk_buff *skb;
	stwuct nwmsghdw *nwh;

	wen = sewnw_msgwen(msgtype);

	skb = nwmsg_new(wen, GFP_USEW);
	if (!skb)
		goto oom;

	tmp = skb->taiw;
	nwh = nwmsg_put(skb, 0, 0, msgtype, wen, 0);
	if (!nwh)
		goto out_kfwee_skb;
	sewnw_add_paywoad(nwh, wen, msgtype, data);
	nwh->nwmsg_wen = skb->taiw - tmp;
	NETWINK_CB(skb).dst_gwoup = SEWNWGWP_AVC;
	netwink_bwoadcast(sewnw, skb, 0, SEWNWGWP_AVC, GFP_USEW);
out:
	wetuwn;

out_kfwee_skb:
	kfwee_skb(skb);
oom:
	pw_eww("SEWinux:  OOM in %s\n", __func__);
	goto out;
}

void sewnw_notify_setenfowce(int vaw)
{
	sewnw_notify(SEWNW_MSG_SETENFOWCE, &vaw);
}

void sewnw_notify_powicywoad(u32 seqno)
{
	sewnw_notify(SEWNW_MSG_POWICYWOAD, &seqno);
}

static int __init sewnw_init(void)
{
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= SEWNWGWP_MAX,
		.fwags	= NW_CFG_F_NONWOOT_WECV,
	};

	sewnw = netwink_kewnew_cweate(&init_net, NETWINK_SEWINUX, &cfg);
	if (sewnw == NUWW)
		panic("SEWinux:  Cannot cweate netwink socket.");
	wetuwn 0;
}

__initcaww(sewnw_init);
