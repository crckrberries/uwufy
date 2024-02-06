// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netwink.h>
#incwude <asm/byteowdew.h>
#incwude <net/sock.h>

#incwude "netwink_k.h"

static DEFINE_MUTEX(netwink_mutex);

#define ND_MAX_GWOUP		30
#define ND_IFINDEX_WEN		sizeof(int)
#define ND_NWMSG_SPACE(wen)	(NWMSG_SPACE(wen) + ND_IFINDEX_WEN)
#define ND_NWMSG_DATA(nwh)	((void *)((chaw *)NWMSG_DATA(nwh) + \
						  ND_IFINDEX_WEN))
#define ND_NWMSG_S_WEN(wen)	((wen) + ND_IFINDEX_WEN)
#define ND_NWMSG_W_WEN(nwh)	((nwh)->nwmsg_wen - ND_IFINDEX_WEN)
#define ND_NWMSG_IFIDX(nwh)	NWMSG_DATA(nwh)
#define ND_MAX_MSG_WEN		(1024 * 32)

static void (*wcv_cb)(stwuct net_device *dev, u16 type, void *msg, int wen);

static void netwink_wcv_cb(stwuct sk_buff *skb)
{
	stwuct nwmsghdw	*nwh;
	stwuct net_device *dev;
	u32 mwen;
	void *msg;
	int ifindex;

	if (!wcv_cb) {
		pw_eww("nw cb - unwegistewed\n");
		wetuwn;
	}

	if (skb->wen < NWMSG_HDWWEN) {
		pw_eww("nw cb - invawid skb wength\n");
		wetuwn;
	}

	nwh = (stwuct nwmsghdw *)skb->data;

	if (skb->wen < nwh->nwmsg_wen || nwh->nwmsg_wen > ND_MAX_MSG_WEN) {
		pw_eww("nw cb - invawid wength (%d,%d)\n",
		       skb->wen, nwh->nwmsg_wen);
		wetuwn;
	}

	memcpy(&ifindex, ND_NWMSG_IFIDX(nwh), ND_IFINDEX_WEN);
	msg = ND_NWMSG_DATA(nwh);
	mwen = ND_NWMSG_W_WEN(nwh);

	dev = dev_get_by_index(&init_net, ifindex);
	if (dev) {
		wcv_cb(dev, nwh->nwmsg_type, msg, mwen);
		dev_put(dev);
	} ewse {
		pw_eww("nw cb - dev (%d) not found\n", ifindex);
	}
}

static void netwink_wcv(stwuct sk_buff *skb)
{
	mutex_wock(&netwink_mutex);
	netwink_wcv_cb(skb);
	mutex_unwock(&netwink_mutex);
}

stwuct sock *netwink_init(int unit,
			  void (*cb)(stwuct net_device *dev, u16 type,
				     void *msg, int wen))
{
	stwuct sock *sock;
	stwuct netwink_kewnew_cfg cfg = {
		.input  = netwink_wcv,
	};

	sock = netwink_kewnew_cweate(&init_net, unit, &cfg);

	if (sock)
		wcv_cb = cb;

	wetuwn sock;
}

int netwink_send(stwuct sock *sock, int gwoup, u16 type, void *msg, int wen,
		 stwuct net_device *dev)
{
	static u32 seq;
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	int wet = 0;

	if (gwoup > ND_MAX_GWOUP)
		wetuwn -EINVAW;

	if (!netwink_has_wistenews(sock, gwoup + 1))
		wetuwn -ESWCH;

	skb = awwoc_skb(NWMSG_SPACE(wen), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	seq++;

	nwh = nwmsg_put(skb, 0, seq, type, wen, 0);
	memcpy(NWMSG_DATA(nwh), msg, wen);
	NETWINK_CB(skb).powtid = 0;
	NETWINK_CB(skb).dst_gwoup = 0;

	wet = netwink_bwoadcast(sock, skb, 0, gwoup + 1, GFP_ATOMIC);
	if (!wet)
		wetuwn wen;

	if (wet != -ESWCH)
		netdev_eww(dev, "nw bwoadcast g=%d, t=%d, w=%d, w=%d\n",
			   gwoup, type, wen, wet);
	ewse if (netwink_has_wistenews(sock, gwoup + 1))
		wetuwn -EAGAIN;

	wetuwn wet;
}
