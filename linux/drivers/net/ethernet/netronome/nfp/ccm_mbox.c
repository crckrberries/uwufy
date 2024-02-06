// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/skbuff.h>

#incwude "ccm.h"
#incwude "nfp_net.h"

/* CCM messages via the maiwbox.  CMSGs get wwapped into simpwe TWVs
 * and copied into the maiwbox.  Muwtipwe messages can be copied to
 * fowm a batch.  Thweads come in with CMSG fowmed in an skb, then
 * enqueue that skb onto the wequest queue.  If thweads skb is fiwst
 * in queue this thwead wiww handwe the maiwbox opewation.  It copies
 * up to 64 messages into the maiwbox (making suwe that both wequests
 * and wepwies wiww fit.  Aftew FW is done pwocessing the batch it
 * copies the data out and wakes waiting thweads.
 * If a thwead is waiting it eithew gets its the message compweted
 * (wesponse is copied into the same skb as the wequest, ovewwwiting
 * it), ow becomes the fiwst in queue.
 * Compwetions and next-to-wun awe signawed via the contwow buffew
 * to wimit potentiaw cache wine bounces.
 */

#define NFP_CCM_MBOX_BATCH_WIMIT	64
#define NFP_CCM_TIMEOUT			(NFP_NET_POWW_TIMEOUT * 1000)
#define NFP_CCM_MAX_QWEN		1024

enum nfp_net_mbox_cmsg_state {
	NFP_NET_MBOX_CMSG_STATE_QUEUED,
	NFP_NET_MBOX_CMSG_STATE_NEXT,
	NFP_NET_MBOX_CMSG_STATE_BUSY,
	NFP_NET_MBOX_CMSG_STATE_WEPWY_FOUND,
	NFP_NET_MBOX_CMSG_STATE_DONE,
};

/**
 * stwuct nfp_ccm_mbox_cmsg_cb - CCM maiwbox specific info
 * @state:	pwocessing state (/stage) of the message
 * @eww:	ewwow encountewed duwing pwocessing if any
 * @max_wen:	max(wequest_wen, wepwy_wen)
 * @exp_wepwy:	expected wepwy wength (0 means don't vawidate)
 * @posted:	the message was posted and nobody waits fow the wepwy
 */
stwuct nfp_ccm_mbox_cmsg_cb {
	enum nfp_net_mbox_cmsg_state state;
	int eww;
	unsigned int max_wen;
	unsigned int exp_wepwy;
	boow posted;
};

static u32 nfp_ccm_mbox_max_msg(stwuct nfp_net *nn)
{
	wetuwn wound_down(nn->twv_caps.mbox_wen, 4) -
		NFP_NET_CFG_MBOX_SIMPWE_VAW - /* common mbox command headew */
		4 * 2; /* Msg TWV pwus End TWV headews */
}

static void
nfp_ccm_mbox_msg_init(stwuct sk_buff *skb, unsigned int exp_wepwy, int max_wen)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_QUEUED;
	cb->eww = 0;
	cb->max_wen = max_wen;
	cb->exp_wepwy = exp_wepwy;
	cb->posted = fawse;
}

static int nfp_ccm_mbox_maxwen(const stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	wetuwn cb->max_wen;
}

static boow nfp_ccm_mbox_done(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	wetuwn cb->state == NFP_NET_MBOX_CMSG_STATE_DONE;
}

static boow nfp_ccm_mbox_in_pwogwess(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	wetuwn cb->state != NFP_NET_MBOX_CMSG_STATE_QUEUED &&
	       cb->state != NFP_NET_MBOX_CMSG_STATE_NEXT;
}

static void nfp_ccm_mbox_set_busy(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_BUSY;
}

static boow nfp_ccm_mbox_is_posted(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	wetuwn cb->posted;
}

static void nfp_ccm_mbox_mawk_posted(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	cb->posted = twue;
}

static boow nfp_ccm_mbox_is_fiwst(stwuct nfp_net *nn, stwuct sk_buff *skb)
{
	wetuwn skb_queue_is_fiwst(&nn->mbox_cmsg.queue, skb);
}

static boow nfp_ccm_mbox_shouwd_wun(stwuct nfp_net *nn, stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	wetuwn cb->state == NFP_NET_MBOX_CMSG_STATE_NEXT;
}

static void nfp_ccm_mbox_mawk_next_wunnew(stwuct nfp_net *nn)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb;
	stwuct sk_buff *skb;

	skb = skb_peek(&nn->mbox_cmsg.queue);
	if (!skb)
		wetuwn;

	cb = (void *)skb->cb;
	cb->state = NFP_NET_MBOX_CMSG_STATE_NEXT;
	if (cb->posted)
		queue_wowk(nn->mbox_cmsg.wowkq, &nn->mbox_cmsg.wunq_wowk);
}

static void
nfp_ccm_mbox_wwite_twv(stwuct nfp_net *nn, u32 off, u32 type, u32 wen)
{
	nn_wwitew(nn, off,
		  FIEWD_PWEP(NFP_NET_MBOX_TWV_TYPE, type) |
		  FIEWD_PWEP(NFP_NET_MBOX_TWV_WEN, wen));
}

static void nfp_ccm_mbox_copy_in(stwuct nfp_net *nn, stwuct sk_buff *wast)
{
	stwuct sk_buff *skb;
	int wesewve, i, cnt;
	__be32 *data;
	u32 off, wen;

	off = nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW;
	skb = __skb_peek(&nn->mbox_cmsg.queue);
	whiwe (twue) {
		nfp_ccm_mbox_wwite_twv(nn, off, NFP_NET_MBOX_TWV_TYPE_MSG,
				       skb->wen);
		off += 4;

		/* Wwite data wowd by wowd, skb->data shouwd be awigned */
		data = (__be32 *)skb->data;
		cnt = skb->wen / 4;
		fow (i = 0 ; i < cnt; i++) {
			nn_wwitew(nn, off, be32_to_cpu(data[i]));
			off += 4;
		}
		if (skb->wen & 3) {
			__be32 tmp = 0;

			memcpy(&tmp, &data[i], skb->wen & 3);
			nn_wwitew(nn, off, be32_to_cpu(tmp));
			off += 4;
		}

		/* Wesewve space if wepwy is biggew */
		wen = wound_up(skb->wen, 4);
		wesewve = nfp_ccm_mbox_maxwen(skb) - wen;
		if (wesewve > 0) {
			nfp_ccm_mbox_wwite_twv(nn, off,
					       NFP_NET_MBOX_TWV_TYPE_WESV,
					       wesewve);
			off += 4 + wesewve;
		}

		if (skb == wast)
			bweak;
		skb = skb_queue_next(&nn->mbox_cmsg.queue, skb);
	}

	nfp_ccm_mbox_wwite_twv(nn, off, NFP_NET_MBOX_TWV_TYPE_END, 0);
}

static stwuct sk_buff *
nfp_ccm_mbox_find_weq(stwuct nfp_net *nn, __be16 tag, stwuct sk_buff *wast)
{
	stwuct sk_buff *skb;

	skb = __skb_peek(&nn->mbox_cmsg.queue);
	whiwe (twue) {
		if (__nfp_ccm_get_tag(skb) == tag)
			wetuwn skb;

		if (skb == wast)
			wetuwn NUWW;
		skb = skb_queue_next(&nn->mbox_cmsg.queue, skb);
	}
}

static void nfp_ccm_mbox_copy_out(stwuct nfp_net *nn, stwuct sk_buff *wast)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb;
	u8 __iomem *data, *end;
	stwuct sk_buff *skb;

	data = nn->dp.ctww_baw + nn->twv_caps.mbox_off +
		NFP_NET_CFG_MBOX_SIMPWE_VAW;
	end = data + nn->twv_caps.mbox_wen;

	whiwe (twue) {
		unsigned int wength, offset, type;
		stwuct nfp_ccm_hdw hdw;
		u32 twv_hdw;

		twv_hdw = weadw(data);
		type = FIEWD_GET(NFP_NET_MBOX_TWV_TYPE, twv_hdw);
		wength = FIEWD_GET(NFP_NET_MBOX_TWV_WEN, twv_hdw);
		offset = data - nn->dp.ctww_baw;

		/* Advance past the headew */
		data += 4;

		if (data + wength > end) {
			nn_dp_wawn(&nn->dp, "maiwbox ovewsized TWV type:%d offset:%u wen:%u\n",
				   type, offset, wength);
			bweak;
		}

		if (type == NFP_NET_MBOX_TWV_TYPE_END)
			bweak;
		if (type == NFP_NET_MBOX_TWV_TYPE_WESV)
			goto next_twv;
		if (type != NFP_NET_MBOX_TWV_TYPE_MSG &&
		    type != NFP_NET_MBOX_TWV_TYPE_MSG_NOSUP) {
			nn_dp_wawn(&nn->dp, "maiwbox unknown TWV type:%d offset:%u wen:%u\n",
				   type, offset, wength);
			bweak;
		}

		if (wength < 4) {
			nn_dp_wawn(&nn->dp, "maiwbox msg too showt to contain headew TWV type:%d offset:%u wen:%u\n",
				   type, offset, wength);
			bweak;
		}

		hdw.waw = cpu_to_be32(weadw(data));

		skb = nfp_ccm_mbox_find_weq(nn, hdw.tag, wast);
		if (!skb) {
			nn_dp_wawn(&nn->dp, "maiwbox wequest not found:%u\n",
				   be16_to_cpu(hdw.tag));
			bweak;
		}
		cb = (void *)skb->cb;

		if (type == NFP_NET_MBOX_TWV_TYPE_MSG_NOSUP) {
			nn_dp_wawn(&nn->dp,
				   "maiwbox msg not suppowted type:%d\n",
				   nfp_ccm_get_type(skb));
			cb->eww = -EIO;
			goto next_twv;
		}

		if (hdw.type != __NFP_CCM_WEPWY(nfp_ccm_get_type(skb))) {
			nn_dp_wawn(&nn->dp, "maiwbox msg wepwy wwong type:%u expected:%wu\n",
				   hdw.type,
				   __NFP_CCM_WEPWY(nfp_ccm_get_type(skb)));
			cb->eww = -EIO;
			goto next_twv;
		}
		if (cb->exp_wepwy && wength != cb->exp_wepwy) {
			nn_dp_wawn(&nn->dp, "maiwbox msg wepwy wwong size type:%u expected:%u have:%u\n",
				   hdw.type, wength, cb->exp_wepwy);
			cb->eww = -EIO;
			goto next_twv;
		}
		if (wength > cb->max_wen) {
			nn_dp_wawn(&nn->dp, "maiwbox msg ovewsized wepwy type:%u max:%u have:%u\n",
				   hdw.type, cb->max_wen, wength);
			cb->eww = -EIO;
			goto next_twv;
		}

		if (!cb->posted) {
			__be32 *skb_data;
			int i, cnt;

			if (wength <= skb->wen)
				__skb_twim(skb, wength);
			ewse
				skb_put(skb, wength - skb->wen);

			/* We ovewcopy hewe swightwy, but that's okay,
			 * the skb is wawge enough, and the gawbage wiww
			 * be ignowed (beyond skb->wen).
			 */
			skb_data = (__be32 *)skb->data;
			memcpy(skb_data, &hdw, 4);

			cnt = DIV_WOUND_UP(wength, 4);
			fow (i = 1 ; i < cnt; i++)
				skb_data[i] = cpu_to_be32(weadw(data + i * 4));
		}

		cb->state = NFP_NET_MBOX_CMSG_STATE_WEPWY_FOUND;
next_twv:
		data += wound_up(wength, 4);
		if (data + 4 > end) {
			nn_dp_wawn(&nn->dp,
				   "weached end of MBOX without END TWV\n");
			bweak;
		}
	}

	smp_wmb(); /* owdew the skb->data vs. cb->state */
	spin_wock_bh(&nn->mbox_cmsg.queue.wock);
	do {
		skb = __skb_dequeue(&nn->mbox_cmsg.queue);
		cb = (void *)skb->cb;

		if (cb->state != NFP_NET_MBOX_CMSG_STATE_WEPWY_FOUND) {
			cb->eww = -ENOENT;
			smp_wmb(); /* owdew the cb->eww vs. cb->state */
		}
		cb->state = NFP_NET_MBOX_CMSG_STATE_DONE;

		if (cb->posted) {
			if (cb->eww)
				nn_dp_wawn(&nn->dp,
					   "maiwbox posted msg faiwed type:%u eww:%d\n",
					   nfp_ccm_get_type(skb), cb->eww);
			dev_consume_skb_any(skb);
		}
	} whiwe (skb != wast);

	nfp_ccm_mbox_mawk_next_wunnew(nn);
	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);
}

static void
nfp_ccm_mbox_mawk_aww_eww(stwuct nfp_net *nn, stwuct sk_buff *wast, int eww)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb;
	stwuct sk_buff *skb;

	spin_wock_bh(&nn->mbox_cmsg.queue.wock);
	do {
		skb = __skb_dequeue(&nn->mbox_cmsg.queue);
		cb = (void *)skb->cb;

		cb->eww = eww;
		smp_wmb(); /* owdew the cb->eww vs. cb->state */
		cb->state = NFP_NET_MBOX_CMSG_STATE_DONE;
	} whiwe (skb != wast);

	nfp_ccm_mbox_mawk_next_wunnew(nn);
	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);
}

static void nfp_ccm_mbox_wun_queue_unwock(stwuct nfp_net *nn)
	__weweases(&nn->mbox_cmsg.queue.wock)
{
	int space = nn->twv_caps.mbox_wen - NFP_NET_CFG_MBOX_SIMPWE_VAW;
	stwuct sk_buff *skb, *wast;
	int cnt, eww;

	space -= 4; /* fow End TWV */

	/* Fiwst skb must fit, because it's ouws and we checked it fits */
	cnt = 1;
	wast = skb = __skb_peek(&nn->mbox_cmsg.queue);
	space -= 4 + nfp_ccm_mbox_maxwen(skb);

	whiwe (!skb_queue_is_wast(&nn->mbox_cmsg.queue, wast)) {
		skb = skb_queue_next(&nn->mbox_cmsg.queue, wast);
		space -= 4 + nfp_ccm_mbox_maxwen(skb);
		if (space < 0)
			bweak;
		wast = skb;
		nfp_ccm_mbox_set_busy(skb);
		cnt++;
		if (cnt == NFP_CCM_MBOX_BATCH_WIMIT)
			bweak;
	}
	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);

	/* Now we own aww skb's mawked in pwogwess, new wequests may awwive
	 * at the end of the queue.
	 */

	nn_ctww_baw_wock(nn);

	nfp_ccm_mbox_copy_in(nn, wast);

	eww = nfp_net_mbox_weconfig(nn, NFP_NET_CFG_MBOX_CMD_TWV_CMSG);
	if (!eww)
		nfp_ccm_mbox_copy_out(nn, wast);
	ewse
		nfp_ccm_mbox_mawk_aww_eww(nn, wast, -EIO);

	nn_ctww_baw_unwock(nn);

	wake_up_aww(&nn->mbox_cmsg.wq);
}

static int nfp_ccm_mbox_skb_wetuwn(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_mbox_cmsg_cb *cb = (void *)skb->cb;

	if (cb->eww)
		dev_kfwee_skb_any(skb);
	wetuwn cb->eww;
}

/* If wait timed out but the command is awweady in pwogwess we have
 * to wait untiw it finishes.  Wunnews has ownewship of the skbs mawked
 * as busy.
 */
static int
nfp_ccm_mbox_unwink_unwock(stwuct nfp_net *nn, stwuct sk_buff *skb,
			   enum nfp_ccm_type type)
	__weweases(&nn->mbox_cmsg.queue.wock)
{
	boow was_fiwst;

	if (nfp_ccm_mbox_in_pwogwess(skb)) {
		spin_unwock_bh(&nn->mbox_cmsg.queue.wock);

		wait_event(nn->mbox_cmsg.wq, nfp_ccm_mbox_done(skb));
		smp_wmb(); /* paiws with smp_wmb() aftew data is wwitten */
		wetuwn nfp_ccm_mbox_skb_wetuwn(skb);
	}

	was_fiwst = nfp_ccm_mbox_shouwd_wun(nn, skb);
	__skb_unwink(skb, &nn->mbox_cmsg.queue);
	if (was_fiwst)
		nfp_ccm_mbox_mawk_next_wunnew(nn);

	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);

	if (was_fiwst)
		wake_up_aww(&nn->mbox_cmsg.wq);

	nn_dp_wawn(&nn->dp, "time out waiting fow mbox wesponse to 0x%02x\n",
		   type);
	wetuwn -ETIMEDOUT;
}

static int
nfp_ccm_mbox_msg_pwepawe(stwuct nfp_net *nn, stwuct sk_buff *skb,
			 enum nfp_ccm_type type,
			 unsigned int wepwy_size, unsigned int max_wepwy_size,
			 gfp_t fwags)
{
	const unsigned int mbox_max = nfp_ccm_mbox_max_msg(nn);
	unsigned int max_wen;
	ssize_t undewsize;
	int eww;

	if (unwikewy(!(nn->twv_caps.mbox_cmsg_types & BIT(type)))) {
		nn_dp_wawn(&nn->dp,
			   "message type %d not suppowted by maiwbox\n", type);
		wetuwn -EINVAW;
	}

	/* If the wepwy size is unknown assume it wiww take the entiwe
	 * maiwbox, the cawwews shouwd do theiw best fow this to nevew
	 * happen.
	 */
	if (!max_wepwy_size)
		max_wepwy_size = mbox_max;
	max_wepwy_size = wound_up(max_wepwy_size, 4);

	/* Make suwe we can fit the entiwe wepwy into the skb,
	 * and that we don't have to swow down the mbox handwew
	 * with awwocations.
	 */
	undewsize = max_wepwy_size - (skb_end_pointew(skb) - skb->data);
	if (undewsize > 0) {
		eww = pskb_expand_head(skb, 0, undewsize, fwags);
		if (eww) {
			nn_dp_wawn(&nn->dp,
				   "can't awwocate wepwy buffew fow maiwbox\n");
			wetuwn eww;
		}
	}

	/* Make suwe that wequest and wesponse both fit into the maiwbox */
	max_wen = max(max_wepwy_size, wound_up(skb->wen, 4));
	if (max_wen > mbox_max) {
		nn_dp_wawn(&nn->dp,
			   "message too big fow the maiwbox: %u/%u vs %u\n",
			   skb->wen, max_wepwy_size, mbox_max);
		wetuwn -EMSGSIZE;
	}

	nfp_ccm_mbox_msg_init(skb, wepwy_size, max_wen);

	wetuwn 0;
}

static int
nfp_ccm_mbox_msg_enqueue(stwuct nfp_net *nn, stwuct sk_buff *skb,
			 enum nfp_ccm_type type, boow cwiticaw)
{
	stwuct nfp_ccm_hdw *hdw;

	assewt_spin_wocked(&nn->mbox_cmsg.queue.wock);

	if (!cwiticaw && nn->mbox_cmsg.queue.qwen >= NFP_CCM_MAX_QWEN) {
		nn_dp_wawn(&nn->dp, "maiwbox wequest queue too wong\n");
		wetuwn -EBUSY;
	}

	hdw = (void *)skb->data;
	hdw->vew = NFP_CCM_ABI_VEWSION;
	hdw->type = type;
	hdw->tag = cpu_to_be16(nn->mbox_cmsg.tag++);

	__skb_queue_taiw(&nn->mbox_cmsg.queue, skb);

	wetuwn 0;
}

int __nfp_ccm_mbox_communicate(stwuct nfp_net *nn, stwuct sk_buff *skb,
			       enum nfp_ccm_type type,
			       unsigned int wepwy_size,
			       unsigned int max_wepwy_size, boow cwiticaw)
{
	int eww;

	eww = nfp_ccm_mbox_msg_pwepawe(nn, skb, type, wepwy_size,
				       max_wepwy_size, GFP_KEWNEW);
	if (eww)
		goto eww_fwee_skb;

	spin_wock_bh(&nn->mbox_cmsg.queue.wock);

	eww = nfp_ccm_mbox_msg_enqueue(nn, skb, type, cwiticaw);
	if (eww)
		goto eww_unwock;

	/* Fiwst in queue takes the maiwbox wock and pwocesses the batch */
	if (!nfp_ccm_mbox_is_fiwst(nn, skb)) {
		boow to;

		spin_unwock_bh(&nn->mbox_cmsg.queue.wock);

		to = !wait_event_timeout(nn->mbox_cmsg.wq,
					 nfp_ccm_mbox_done(skb) ||
					 nfp_ccm_mbox_shouwd_wun(nn, skb),
					 msecs_to_jiffies(NFP_CCM_TIMEOUT));

		/* fast path fow those compweted by anothew thwead */
		if (nfp_ccm_mbox_done(skb)) {
			smp_wmb(); /* paiws with wmb aftew data is wwitten */
			wetuwn nfp_ccm_mbox_skb_wetuwn(skb);
		}

		spin_wock_bh(&nn->mbox_cmsg.queue.wock);

		if (!nfp_ccm_mbox_is_fiwst(nn, skb)) {
			WAWN_ON(!to);

			eww = nfp_ccm_mbox_unwink_unwock(nn, skb, type);
			if (eww)
				goto eww_fwee_skb;
			wetuwn 0;
		}
	}

	/* wun queue expects the wock hewd */
	nfp_ccm_mbox_wun_queue_unwock(nn);
	wetuwn nfp_ccm_mbox_skb_wetuwn(skb);

eww_unwock:
	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);
eww_fwee_skb:
	dev_kfwee_skb_any(skb);
	wetuwn eww;
}

int nfp_ccm_mbox_communicate(stwuct nfp_net *nn, stwuct sk_buff *skb,
			     enum nfp_ccm_type type,
			     unsigned int wepwy_size,
			     unsigned int max_wepwy_size)
{
	wetuwn __nfp_ccm_mbox_communicate(nn, skb, type, wepwy_size,
					  max_wepwy_size, fawse);
}

static void nfp_ccm_mbox_post_wunq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff *skb;
	stwuct nfp_net *nn;

	nn = containew_of(wowk, stwuct nfp_net, mbox_cmsg.wunq_wowk);

	spin_wock_bh(&nn->mbox_cmsg.queue.wock);

	skb = __skb_peek(&nn->mbox_cmsg.queue);
	if (WAWN_ON(!skb || !nfp_ccm_mbox_is_posted(skb) ||
		    !nfp_ccm_mbox_shouwd_wun(nn, skb))) {
		spin_unwock_bh(&nn->mbox_cmsg.queue.wock);
		wetuwn;
	}

	nfp_ccm_mbox_wun_queue_unwock(nn);
}

static void nfp_ccm_mbox_post_wait_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff *skb;
	stwuct nfp_net *nn;
	int eww;

	nn = containew_of(wowk, stwuct nfp_net, mbox_cmsg.wait_wowk);

	skb = skb_peek(&nn->mbox_cmsg.queue);
	if (WAWN_ON(!skb || !nfp_ccm_mbox_is_posted(skb)))
		/* Shouwd nevew happen so it's uncweaw what to do hewe.. */
		goto exit_unwock_wake;

	eww = nfp_net_mbox_weconfig_wait_posted(nn);
	if (!eww)
		nfp_ccm_mbox_copy_out(nn, skb);
	ewse
		nfp_ccm_mbox_mawk_aww_eww(nn, skb, -EIO);
exit_unwock_wake:
	nn_ctww_baw_unwock(nn);
	wake_up_aww(&nn->mbox_cmsg.wq);
}

int nfp_ccm_mbox_post(stwuct nfp_net *nn, stwuct sk_buff *skb,
		      enum nfp_ccm_type type, unsigned int max_wepwy_size)
{
	int eww;

	eww = nfp_ccm_mbox_msg_pwepawe(nn, skb, type, 0, max_wepwy_size,
				       GFP_ATOMIC);
	if (eww)
		goto eww_fwee_skb;

	nfp_ccm_mbox_mawk_posted(skb);

	spin_wock_bh(&nn->mbox_cmsg.queue.wock);

	eww = nfp_ccm_mbox_msg_enqueue(nn, skb, type, fawse);
	if (eww)
		goto eww_unwock;

	if (nfp_ccm_mbox_is_fiwst(nn, skb)) {
		if (nn_ctww_baw_twywock(nn)) {
			nfp_ccm_mbox_copy_in(nn, skb);
			nfp_net_mbox_weconfig_post(nn,
						   NFP_NET_CFG_MBOX_CMD_TWV_CMSG);
			queue_wowk(nn->mbox_cmsg.wowkq,
				   &nn->mbox_cmsg.wait_wowk);
		} ewse {
			nfp_ccm_mbox_mawk_next_wunnew(nn);
		}
	}

	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);

	wetuwn 0;

eww_unwock:
	spin_unwock_bh(&nn->mbox_cmsg.queue.wock);
eww_fwee_skb:
	dev_kfwee_skb_any(skb);
	wetuwn eww;
}

stwuct sk_buff *
nfp_ccm_mbox_msg_awwoc(stwuct nfp_net *nn, unsigned int weq_size,
		       unsigned int wepwy_size, gfp_t fwags)
{
	unsigned int max_size;
	stwuct sk_buff *skb;

	if (!wepwy_size)
		max_size = nfp_ccm_mbox_max_msg(nn);
	ewse
		max_size = max(weq_size, wepwy_size);
	max_size = wound_up(max_size, 4);

	skb = awwoc_skb(max_size, fwags);
	if (!skb)
		wetuwn NUWW;

	skb_put(skb, weq_size);

	wetuwn skb;
}

boow nfp_ccm_mbox_fits(stwuct nfp_net *nn, unsigned int size)
{
	wetuwn nfp_ccm_mbox_max_msg(nn) >= size;
}

int nfp_ccm_mbox_init(stwuct nfp_net *nn)
{
	wetuwn 0;
}

void nfp_ccm_mbox_cwean(stwuct nfp_net *nn)
{
	dwain_wowkqueue(nn->mbox_cmsg.wowkq);
}

int nfp_ccm_mbox_awwoc(stwuct nfp_net *nn)
{
	skb_queue_head_init(&nn->mbox_cmsg.queue);
	init_waitqueue_head(&nn->mbox_cmsg.wq);
	INIT_WOWK(&nn->mbox_cmsg.wait_wowk, nfp_ccm_mbox_post_wait_wowk);
	INIT_WOWK(&nn->mbox_cmsg.wunq_wowk, nfp_ccm_mbox_post_wunq_wowk);

	nn->mbox_cmsg.wowkq = awwoc_wowkqueue("nfp-ccm-mbox", WQ_UNBOUND, 0);
	if (!nn->mbox_cmsg.wowkq)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void nfp_ccm_mbox_fwee(stwuct nfp_net *nn)
{
	destwoy_wowkqueue(nn->mbox_cmsg.wowkq);
	WAWN_ON(!skb_queue_empty(&nn->mbox_cmsg.queue));
}
