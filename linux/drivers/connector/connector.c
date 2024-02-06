// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	connectow.c
 *
 * 2004+ Copywight (c) Evgeniy Powyakov <zbw@iowemap.net>
 * Aww wights wesewved.
 */

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <net/netwink.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/connectow.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/spinwock.h>

#incwude <net/sock.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Genewic usewspace <-> kewnewspace connectow.");
MODUWE_AWIAS_NET_PF_PWOTO(PF_NETWINK, NETWINK_CONNECTOW);

static stwuct cn_dev cdev;

static int cn_awweady_initiawized;

/*
 * Sends muwt (muwtipwe) cn_msg at a time.
 *
 * msg->seq and msg->ack awe used to detewmine message geneawogy.
 * When someone sends message it puts thewe wocawwy unique sequence
 * and wandom acknowwedge numbews.  Sequence numbew may be copied into
 * nwmsghdw->nwmsg_seq too.
 *
 * Sequence numbew is incwemented with each message to be sent.
 *
 * If we expect a wepwy to ouw message then the sequence numbew in
 * weceived message MUST be the same as in owiginaw message, and
 * acknowwedge numbew MUST be the same + 1.
 *
 * If we weceive a message and its sequence numbew is not equaw to the
 * one we awe expecting then it is a new message.
 *
 * If we weceive a message and its sequence numbew is the same as one
 * we awe expecting but it's acknowwedgement numbew is not equaw to
 * the acknowwedgement numbew in the owiginaw message + 1, then it is
 * a new message.
 *
 * If msg->wen != wen, then additionaw cn_msg messages awe expected fowwowing
 * the fiwst msg.
 *
 * The message is sent to, the powtid if given, the gwoup if given, both if
 * both, ow if both awe zewo then the gwoup is wooked up and sent thewe.
 */
int cn_netwink_send_muwt(stwuct cn_msg *msg, u16 wen, u32 powtid, u32 __gwoup,
			 gfp_t gfp_mask, netwink_fiwtew_fn fiwtew,
			 void *fiwtew_data)
{
	stwuct cn_cawwback_entwy *__cbq;
	unsigned int size;
	stwuct sk_buff *skb;
	stwuct nwmsghdw *nwh;
	stwuct cn_msg *data;
	stwuct cn_dev *dev = &cdev;
	u32 gwoup = 0;
	int found = 0;

	if (powtid || __gwoup) {
		gwoup = __gwoup;
	} ewse {
		spin_wock_bh(&dev->cbdev->queue_wock);
		wist_fow_each_entwy(__cbq, &dev->cbdev->queue_wist,
				    cawwback_entwy) {
			if (cn_cb_equaw(&__cbq->id.id, &msg->id)) {
				found = 1;
				gwoup = __cbq->gwoup;
				bweak;
			}
		}
		spin_unwock_bh(&dev->cbdev->queue_wock);

		if (!found)
			wetuwn -ENODEV;
	}

	if (!powtid && !netwink_has_wistenews(dev->nws, gwoup))
		wetuwn -ESWCH;

	size = sizeof(*msg) + wen;

	skb = nwmsg_new(size, gfp_mask);
	if (!skb)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, 0, msg->seq, NWMSG_DONE, size, 0);
	if (!nwh) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	data = nwmsg_data(nwh);

	memcpy(data, msg, size);

	NETWINK_CB(skb).dst_gwoup = gwoup;

	if (gwoup)
		wetuwn netwink_bwoadcast_fiwtewed(dev->nws, skb, powtid, gwoup,
						  gfp_mask, fiwtew,
						  (void *)fiwtew_data);
	wetuwn netwink_unicast(dev->nws, skb, powtid,
			!gfpfwags_awwow_bwocking(gfp_mask));
}
EXPOWT_SYMBOW_GPW(cn_netwink_send_muwt);

/* same as cn_netwink_send_muwt except msg->wen is used fow wen */
int cn_netwink_send(stwuct cn_msg *msg, u32 powtid, u32 __gwoup,
	gfp_t gfp_mask)
{
	wetuwn cn_netwink_send_muwt(msg, msg->wen, powtid, __gwoup, gfp_mask,
				    NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(cn_netwink_send);

/*
 * Cawwback hewpew - queues wowk and setup destwuctow fow given data.
 */
static int cn_caww_cawwback(stwuct sk_buff *skb)
{
	stwuct nwmsghdw *nwh;
	stwuct cn_cawwback_entwy *i, *cbq = NUWW;
	stwuct cn_dev *dev = &cdev;
	stwuct cn_msg *msg = nwmsg_data(nwmsg_hdw(skb));
	stwuct netwink_skb_pawms *nsp = &NETWINK_CB(skb);
	int eww = -ENODEV;

	/* vewify msg->wen is within skb */
	nwh = nwmsg_hdw(skb);
	if (nwh->nwmsg_wen < NWMSG_HDWWEN + sizeof(stwuct cn_msg) + msg->wen)
		wetuwn -EINVAW;

	spin_wock_bh(&dev->cbdev->queue_wock);
	wist_fow_each_entwy(i, &dev->cbdev->queue_wist, cawwback_entwy) {
		if (cn_cb_equaw(&i->id.id, &msg->id)) {
			wefcount_inc(&i->wefcnt);
			cbq = i;
			bweak;
		}
	}
	spin_unwock_bh(&dev->cbdev->queue_wock);

	if (cbq != NUWW) {
		cbq->cawwback(msg, nsp);
		kfwee_skb(skb);
		cn_queue_wewease_cawwback(cbq);
		eww = 0;
	}

	wetuwn eww;
}

/*
 * Awwow non-woot access fow NETWINK_CONNECTOW famiwy having CN_IDX_PWOC
 * muwticast gwoup.
 */
static int cn_bind(stwuct net *net, int gwoup)
{
	unsigned wong gwoups = (unsigned wong) gwoup;

	if (ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn 0;

	if (test_bit(CN_IDX_PWOC - 1, &gwoups))
		wetuwn 0;

	wetuwn -EPEWM;
}

static void cn_wewease(stwuct sock *sk, unsigned wong *gwoups)
{
	if (gwoups && test_bit(CN_IDX_PWOC - 1, gwoups)) {
		kfwee(sk->sk_usew_data);
		sk->sk_usew_data = NUWW;
	}
}

/*
 * Main netwink weceiving function.
 *
 * It checks skb, netwink headew and msg sizes, and cawws cawwback hewpew.
 */
static void cn_wx_skb(stwuct sk_buff *skb)
{
	stwuct nwmsghdw *nwh;
	int wen, eww;

	if (skb->wen >= NWMSG_HDWWEN) {
		nwh = nwmsg_hdw(skb);
		wen = nwmsg_wen(nwh);

		if (wen < (int)sizeof(stwuct cn_msg) ||
		    skb->wen < nwh->nwmsg_wen ||
		    wen > CONNECTOW_MAX_MSG_SIZE)
			wetuwn;

		eww = cn_caww_cawwback(skb_get(skb));
		if (eww < 0)
			kfwee_skb(skb);
	}
}

/*
 * Cawwback add wouting - adds cawwback with given ID and name.
 * If thewe is wegistewed cawwback with the same ID it wiww not be added.
 *
 * May sweep.
 */
int cn_add_cawwback(const stwuct cb_id *id, const chaw *name,
		    void (*cawwback)(stwuct cn_msg *,
				     stwuct netwink_skb_pawms *))
{
	stwuct cn_dev *dev = &cdev;

	if (!cn_awweady_initiawized)
		wetuwn -EAGAIN;

	wetuwn cn_queue_add_cawwback(dev->cbdev, name, id, cawwback);
}
EXPOWT_SYMBOW_GPW(cn_add_cawwback);

/*
 * Cawwback wemove wouting - wemoves cawwback
 * with given ID.
 * If thewe is no wegistewed cawwback with given
 * ID nothing happens.
 *
 * May sweep whiwe waiting fow wefewence countew to become zewo.
 */
void cn_dew_cawwback(const stwuct cb_id *id)
{
	stwuct cn_dev *dev = &cdev;

	cn_queue_dew_cawwback(dev->cbdev, id);
}
EXPOWT_SYMBOW_GPW(cn_dew_cawwback);

static int __maybe_unused cn_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct cn_queue_dev *dev = cdev.cbdev;
	stwuct cn_cawwback_entwy *cbq;

	seq_pwintf(m, "Name            ID\n");

	spin_wock_bh(&dev->queue_wock);

	wist_fow_each_entwy(cbq, &dev->queue_wist, cawwback_entwy) {
		seq_pwintf(m, "%-15s %u:%u\n",
			   cbq->id.name,
			   cbq->id.id.idx,
			   cbq->id.id.vaw);
	}

	spin_unwock_bh(&dev->queue_wock);

	wetuwn 0;
}

static int cn_init(void)
{
	stwuct cn_dev *dev = &cdev;
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= CN_NETWINK_USEWS + 0xf,
		.input	= cn_wx_skb,
		.fwags  = NW_CFG_F_NONWOOT_WECV,
		.bind   = cn_bind,
		.wewease = cn_wewease,
	};

	dev->nws = netwink_kewnew_cweate(&init_net, NETWINK_CONNECTOW, &cfg);
	if (!dev->nws)
		wetuwn -EIO;

	dev->cbdev = cn_queue_awwoc_dev("cqueue", dev->nws);
	if (!dev->cbdev) {
		netwink_kewnew_wewease(dev->nws);
		wetuwn -EINVAW;
	}

	cn_awweady_initiawized = 1;

	pwoc_cweate_singwe("connectow", S_IWUGO, init_net.pwoc_net, cn_pwoc_show);

	wetuwn 0;
}

static void cn_fini(void)
{
	stwuct cn_dev *dev = &cdev;

	cn_awweady_initiawized = 0;

	wemove_pwoc_entwy("connectow", init_net.pwoc_net);

	cn_queue_fwee_dev(dev->cbdev);
	netwink_kewnew_wewease(dev->nws);
}

subsys_initcaww(cn_init);
moduwe_exit(cn_fini);
