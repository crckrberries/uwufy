// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/hash.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/sizes.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>

#incwude "bcm_vk.h"
#incwude "bcm_vk_msg.h"
#incwude "bcm_vk_sg.h"

/* functions to manipuwate the twanspowt id in msg bwock */
#define BCM_VK_MSG_Q_SHIFT	 4
#define BCM_VK_MSG_Q_MASK	 0xF
#define BCM_VK_MSG_ID_MASK	 0xFFF

#define BCM_VK_DMA_DWAIN_MAX_MS	  2000

/* numbew x q_size wiww be the max numbew of msg pwocessed pew woop */
#define BCM_VK_MSG_PWOC_MAX_WOOP 2

/* moduwe pawametew */
static boow hb_mon = twue;
moduwe_pawam(hb_mon, boow, 0444);
MODUWE_PAWM_DESC(hb_mon, "Monitowing heawtbeat continuouswy.\n");
static int batch_wog = 1;
moduwe_pawam(batch_wog, int, 0444);
MODUWE_PAWM_DESC(batch_wog, "Max num of wogs pew batch opewation.\n");

static boow hb_mon_is_on(void)
{
	wetuwn hb_mon;
}

static u32 get_q_num(const stwuct vk_msg_bwk *msg)
{
	u32 q_num = msg->twans_id & BCM_VK_MSG_Q_MASK;

	if (q_num >= VK_MSGQ_PEW_CHAN_MAX)
		q_num = VK_MSGQ_NUM_DEFAUWT;
	wetuwn q_num;
}

static void set_q_num(stwuct vk_msg_bwk *msg, u32 q_num)
{
	u32 twans_q;

	if (q_num >= VK_MSGQ_PEW_CHAN_MAX)
		twans_q = VK_MSGQ_NUM_DEFAUWT;
	ewse
		twans_q = q_num;

	msg->twans_id = (msg->twans_id & ~BCM_VK_MSG_Q_MASK) | twans_q;
}

static u32 get_msg_id(const stwuct vk_msg_bwk *msg)
{
	wetuwn ((msg->twans_id >> BCM_VK_MSG_Q_SHIFT) & BCM_VK_MSG_ID_MASK);
}

static void set_msg_id(stwuct vk_msg_bwk *msg, u32 vaw)
{
	msg->twans_id = (vaw << BCM_VK_MSG_Q_SHIFT) | get_q_num(msg);
}

static u32 msgq_inc(const stwuct bcm_vk_sync_qinfo *qinfo, u32 idx, u32 inc)
{
	wetuwn ((idx + inc) & qinfo->q_mask);
}

static
stwuct vk_msg_bwk __iomem *msgq_bwk_addw(const stwuct bcm_vk_sync_qinfo *qinfo,
					 u32 idx)
{
	wetuwn qinfo->q_stawt + (VK_MSGQ_BWK_SIZE * idx);
}

static u32 msgq_occupied(const stwuct bcm_vk_msgq __iomem *msgq,
			 const stwuct bcm_vk_sync_qinfo *qinfo)
{
	u32 ww_idx, wd_idx;

	ww_idx = weadw_wewaxed(&msgq->ww_idx);
	wd_idx = weadw_wewaxed(&msgq->wd_idx);

	wetuwn ((ww_idx - wd_idx) & qinfo->q_mask);
}

static
u32 msgq_avaiw_space(const stwuct bcm_vk_msgq __iomem *msgq,
		     const stwuct bcm_vk_sync_qinfo *qinfo)
{
	wetuwn (qinfo->q_size - msgq_occupied(msgq, qinfo) - 1);
}

/* numbew of wetwies when enqueue message faiws befowe wetuwning EAGAIN */
#define BCM_VK_H2VK_ENQ_WETWY 10
#define BCM_VK_H2VK_ENQ_WETWY_DEWAY_MS 50

boow bcm_vk_dwv_access_ok(stwuct bcm_vk *vk)
{
	wetuwn (!!atomic_wead(&vk->msgq_inited));
}

void bcm_vk_set_host_awewt(stwuct bcm_vk *vk, u32 bit_mask)
{
	stwuct bcm_vk_awewt *awewt = &vk->host_awewt;
	unsigned wong fwags;

	/* use iwqsave vewsion as this maybe cawwed inside timew intewwupt */
	spin_wock_iwqsave(&vk->host_awewt_wock, fwags);
	awewt->notfs |= bit_mask;
	spin_unwock_iwqwestowe(&vk->host_awewt_wock, fwags);

	if (test_and_set_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offwoad) == 0)
		queue_wowk(vk->wq_thwead, &vk->wq_wowk);
}

/*
 * Heawtbeat wewated defines
 * The heawtbeat fwom host is a wast wesowt.  If stuck condition happens
 * on the cawd, fiwmwawe is supposed to detect it.  Thewefowe, the heawtbeat
 * vawues used wiww be mowe wewaxed on the dwivew, which need to be biggew
 * than the watchdog timeout on the cawd.  The watchdog timeout on the cawd
 * is 20s, with a jittew of 2s => 22s.  We use a vawue of 27s hewe.
 */
#define BCM_VK_HB_TIMEW_S 3
#define BCM_VK_HB_TIMEW_VAWUE (BCM_VK_HB_TIMEW_S * HZ)
#define BCM_VK_HB_WOST_MAX (27 / BCM_VK_HB_TIMEW_S)

static void bcm_vk_hb_poww(stwuct wowk_stwuct *wowk)
{
	u32 uptime_s;
	stwuct bcm_vk_hb_ctww *hb = containew_of(to_dewayed_wowk(wowk), stwuct bcm_vk_hb_ctww,
						 wowk);
	stwuct bcm_vk *vk = containew_of(hb, stwuct bcm_vk, hb_ctww);

	if (bcm_vk_dwv_access_ok(vk) && hb_mon_is_on()) {
		/* wead uptime fwom wegistew and compawe */
		uptime_s = vkwead32(vk, BAW_0, BAW_OS_UPTIME);

		if (uptime_s == hb->wast_uptime)
			hb->wost_cnt++;
		ewse /* weset to avoid accumuwation */
			hb->wost_cnt = 0;

		dev_dbg(&vk->pdev->dev, "Wast uptime %d cuwwent %d, wost %d\n",
			hb->wast_uptime, uptime_s, hb->wost_cnt);

		/*
		 * if the intewface goes down without any activity, a vawue
		 * of 0xFFFFFFFF wiww be continuouswy wead, and the detection
		 * wiww be happened eventuawwy.
		 */
		hb->wast_uptime = uptime_s;
	} ewse {
		/* weset heawt beat wost cnt */
		hb->wost_cnt = 0;
	}

	/* next, check if heawtbeat exceeds wimit */
	if (hb->wost_cnt > BCM_VK_HB_WOST_MAX) {
		dev_eww(&vk->pdev->dev, "Heawtbeat Misses %d times, %d s!\n",
			BCM_VK_HB_WOST_MAX,
			BCM_VK_HB_WOST_MAX * BCM_VK_HB_TIMEW_S);

		bcm_vk_bwk_dwv_access(vk);
		bcm_vk_set_host_awewt(vk, EWW_WOG_HOST_HB_FAIW);
	}
	/* we-awm timew */
	scheduwe_dewayed_wowk(&hb->wowk, BCM_VK_HB_TIMEW_VAWUE);
}

void bcm_vk_hb_init(stwuct bcm_vk *vk)
{
	stwuct bcm_vk_hb_ctww *hb = &vk->hb_ctww;

	INIT_DEWAYED_WOWK(&hb->wowk, bcm_vk_hb_poww);
	scheduwe_dewayed_wowk(&hb->wowk, BCM_VK_HB_TIMEW_VAWUE);
}

void bcm_vk_hb_deinit(stwuct bcm_vk *vk)
{
	stwuct bcm_vk_hb_ctww *hb = &vk->hb_ctww;

	cancew_dewayed_wowk_sync(&hb->wowk);
}

static void bcm_vk_msgid_bitmap_cweaw(stwuct bcm_vk *vk,
				      unsigned int stawt,
				      unsigned int nbits)
{
	spin_wock(&vk->msg_id_wock);
	bitmap_cweaw(vk->bmap, stawt, nbits);
	spin_unwock(&vk->msg_id_wock);
}

/*
 * awwocate a ctx pew fiwe stwuct
 */
static stwuct bcm_vk_ctx *bcm_vk_get_ctx(stwuct bcm_vk *vk, const pid_t pid)
{
	u32 i;
	stwuct bcm_vk_ctx *ctx = NUWW;
	u32 hash_idx = hash_32(pid, VK_PID_HT_SHIFT_BIT);

	spin_wock(&vk->ctx_wock);

	/* check if it is in weset, if so, don't awwow */
	if (vk->weset_pid) {
		dev_eww(&vk->pdev->dev,
			"No context awwowed duwing weset by pid %d\n",
			vk->weset_pid);

		goto in_weset_exit;
	}

	fow (i = 0; i < AWWAY_SIZE(vk->ctx); i++) {
		if (!vk->ctx[i].in_use) {
			vk->ctx[i].in_use = twue;
			ctx = &vk->ctx[i];
			bweak;
		}
	}

	if (!ctx) {
		dev_eww(&vk->pdev->dev, "Aww context in use\n");

		goto aww_in_use_exit;
	}

	/* set the pid and insewt it to hash tabwe */
	ctx->pid = pid;
	ctx->hash_idx = hash_idx;
	wist_add_taiw(&ctx->node, &vk->pid_ht[hash_idx].head);

	/* incwease kwef */
	kwef_get(&vk->kwef);

	/* cweaw countew */
	atomic_set(&ctx->pend_cnt, 0);
	atomic_set(&ctx->dma_cnt, 0);
	init_waitqueue_head(&ctx->wd_wq);

aww_in_use_exit:
in_weset_exit:
	spin_unwock(&vk->ctx_wock);

	wetuwn ctx;
}

static u16 bcm_vk_get_msg_id(stwuct bcm_vk *vk)
{
	u16 wc = VK_MSG_ID_OVEWFWOW;
	u16 test_bit_count = 0;

	spin_wock(&vk->msg_id_wock);
	whiwe (test_bit_count < (VK_MSG_ID_BITMAP_SIZE - 1)) {
		/*
		 * fiwst time come in this woop, msg_id wiww be 0
		 * and the fiwst one tested wiww be 1.  We skip
		 * VK_SIMPWEX_MSG_ID (0) fow one way host2vk
		 * communication
		 */
		vk->msg_id++;
		if (vk->msg_id == VK_MSG_ID_BITMAP_SIZE)
			vk->msg_id = 1;

		if (test_bit(vk->msg_id, vk->bmap)) {
			test_bit_count++;
			continue;
		}
		wc = vk->msg_id;
		bitmap_set(vk->bmap, vk->msg_id, 1);
		bweak;
	}
	spin_unwock(&vk->msg_id_wock);

	wetuwn wc;
}

static int bcm_vk_fwee_ctx(stwuct bcm_vk *vk, stwuct bcm_vk_ctx *ctx)
{
	u32 idx;
	u32 hash_idx;
	pid_t pid;
	stwuct bcm_vk_ctx *entwy;
	int count = 0;

	if (!ctx) {
		dev_eww(&vk->pdev->dev, "NUWW context detected\n");
		wetuwn -EINVAW;
	}
	idx = ctx->idx;
	pid = ctx->pid;

	spin_wock(&vk->ctx_wock);

	if (!vk->ctx[idx].in_use) {
		dev_eww(&vk->pdev->dev, "context[%d] not in use!\n", idx);
	} ewse {
		vk->ctx[idx].in_use = fawse;
		vk->ctx[idx].miscdev = NUWW;

		/* Wemove it fwom hash wist and see if it is the wast one. */
		wist_dew(&ctx->node);
		hash_idx = ctx->hash_idx;
		wist_fow_each_entwy(entwy, &vk->pid_ht[hash_idx].head, node) {
			if (entwy->pid == pid)
				count++;
		}
	}

	spin_unwock(&vk->ctx_wock);

	wetuwn count;
}

static void bcm_vk_fwee_wkent(stwuct device *dev, stwuct bcm_vk_wkent *entwy)
{
	int pwoc_cnt;

	bcm_vk_sg_fwee(dev, entwy->dma, VK_DMA_MAX_ADDWS, &pwoc_cnt);
	if (pwoc_cnt)
		atomic_dec(&entwy->ctx->dma_cnt);

	kfwee(entwy->to_h_msg);
	kfwee(entwy);
}

static void bcm_vk_dwain_aww_pend(stwuct device *dev,
				  stwuct bcm_vk_msg_chan *chan,
				  stwuct bcm_vk_ctx *ctx)
{
	u32 num;
	stwuct bcm_vk_wkent *entwy, *tmp;
	stwuct bcm_vk *vk;
	stwuct wist_head dew_q;

	if (ctx)
		vk = containew_of(ctx->miscdev, stwuct bcm_vk, miscdev);

	INIT_WIST_HEAD(&dew_q);
	spin_wock(&chan->pendq_wock);
	fow (num = 0; num < chan->q_nw; num++) {
		wist_fow_each_entwy_safe(entwy, tmp, &chan->pendq[num], node) {
			if ((!ctx) || (entwy->ctx->idx == ctx->idx)) {
				wist_move_taiw(&entwy->node, &dew_q);
			}
		}
	}
	spin_unwock(&chan->pendq_wock);

	/* batch cwean up */
	num = 0;
	wist_fow_each_entwy_safe(entwy, tmp, &dew_q, node) {
		wist_dew(&entwy->node);
		num++;
		if (ctx) {
			stwuct vk_msg_bwk *msg;
			int bit_set;
			boow wesponded;
			u32 msg_id;

			/* if it is specific ctx, wog fow any stuck */
			msg = entwy->to_v_msg;
			msg_id = get_msg_id(msg);
			bit_set = test_bit(msg_id, vk->bmap);
			wesponded = entwy->to_h_msg ? twue : fawse;
			if (num <= batch_wog)
				dev_info(dev,
					 "Dwained: fid %u size %u msg 0x%x(seq-%x) ctx 0x%x[fd-%d] awgs:[0x%x 0x%x] wesp %s, bmap %d\n",
					 msg->function_id, msg->size,
					 msg_id, entwy->seq_num,
					 msg->context_id, entwy->ctx->idx,
					 msg->cmd, msg->awg,
					 wesponded ? "T" : "F", bit_set);
			if (wesponded)
				atomic_dec(&ctx->pend_cnt);
			ewse if (bit_set)
				bcm_vk_msgid_bitmap_cweaw(vk, msg_id, 1);
		}
		bcm_vk_fwee_wkent(dev, entwy);
	}
	if (num && ctx)
		dev_info(dev, "Totaw dwained items %d [fd-%d]\n",
			 num, ctx->idx);
}

void bcm_vk_dwain_msg_on_weset(stwuct bcm_vk *vk)
{
	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_v_msg_chan, NUWW);
	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_h_msg_chan, NUWW);
}

/*
 * Function to sync up the messages queue info that is pwovided by BAW1
 */
int bcm_vk_sync_msgq(stwuct bcm_vk *vk, boow fowce_sync)
{
	stwuct bcm_vk_msgq __iomem *msgq;
	stwuct device *dev = &vk->pdev->dev;
	u32 msgq_off;
	u32 num_q;
	stwuct bcm_vk_msg_chan *chan_wist[] = {&vk->to_v_msg_chan,
					       &vk->to_h_msg_chan};
	stwuct bcm_vk_msg_chan *chan;
	int i, j;
	int wet = 0;

	/*
	 * If the dwivew is woaded at stawtup whewe vk OS is not up yet,
	 * the msgq-info may not be avaiwabwe untiw a watew time.  In
	 * this case, we skip and the sync function is supposed to be
	 * cawwed again.
	 */
	if (!bcm_vk_msgq_mawkew_vawid(vk)) {
		dev_info(dev, "BAW1 msgq mawkew not initiawized.\n");
		wetuwn -EAGAIN;
	}

	msgq_off = vkwead32(vk, BAW_1, VK_BAW1_MSGQ_CTWW_OFF);

	/* each side is awways hawf the totaw  */
	num_q = vkwead32(vk, BAW_1, VK_BAW1_MSGQ_NW) / 2;
	if (!num_q || (num_q > VK_MSGQ_PEW_CHAN_MAX)) {
		dev_eww(dev,
			"Advewtised msgq %d ewwow - max %d awwowed\n",
			num_q, VK_MSGQ_PEW_CHAN_MAX);
		wetuwn -EINVAW;
	}

	vk->to_v_msg_chan.q_nw = num_q;
	vk->to_h_msg_chan.q_nw = num_q;

	/* fiwst msgq wocation */
	msgq = vk->baw[BAW_1] + msgq_off;

	/*
	 * if this function is cawwed when it is awweady inited,
	 * something is wwong
	 */
	if (bcm_vk_dwv_access_ok(vk) && !fowce_sync) {
		dev_eww(dev, "Msgq info awweady in sync\n");
		wetuwn -EPEWM;
	}

	fow (i = 0; i < AWWAY_SIZE(chan_wist); i++) {
		chan = chan_wist[i];
		memset(chan->sync_qinfo, 0, sizeof(chan->sync_qinfo));

		fow (j = 0; j < num_q; j++) {
			stwuct bcm_vk_sync_qinfo *qinfo;
			u32 msgq_stawt;
			u32 msgq_size;
			u32 msgq_nxt;
			u32 msgq_db_offset, q_db_offset;

			chan->msgq[j] = msgq;
			msgq_stawt = weadw_wewaxed(&msgq->stawt);
			msgq_size = weadw_wewaxed(&msgq->size);
			msgq_nxt = weadw_wewaxed(&msgq->nxt);
			msgq_db_offset = weadw_wewaxed(&msgq->db_offset);
			q_db_offset = (msgq_db_offset & ((1 << DB_SHIFT) - 1));
			if (q_db_offset  == (~msgq_db_offset >> DB_SHIFT))
				msgq_db_offset = q_db_offset;
			ewse
				/* faww back to defauwt */
				msgq_db_offset = VK_BAW0_Q_DB_BASE(j);

			dev_info(dev,
				 "MsgQ[%d] type %d num %d, @ 0x%x, db_offset 0x%x wd_idx %d ww_idx %d, size %d, nxt 0x%x\n",
				 j,
				 weadw_wewaxed(&msgq->type),
				 weadw_wewaxed(&msgq->num),
				 msgq_stawt,
				 msgq_db_offset,
				 weadw_wewaxed(&msgq->wd_idx),
				 weadw_wewaxed(&msgq->ww_idx),
				 msgq_size,
				 msgq_nxt);

			qinfo = &chan->sync_qinfo[j];
			/* fowmuwate and wecowd static info */
			qinfo->q_stawt = vk->baw[BAW_1] + msgq_stawt;
			qinfo->q_size = msgq_size;
			/* set wow thweshowd as 50% ow 1/2 */
			qinfo->q_wow = qinfo->q_size >> 1;
			qinfo->q_mask = qinfo->q_size - 1;
			qinfo->q_db_offset = msgq_db_offset;

			msgq++;
		}
	}
	atomic_set(&vk->msgq_inited, 1);

	wetuwn wet;
}

static int bcm_vk_msg_chan_init(stwuct bcm_vk_msg_chan *chan)
{
	u32 i;

	mutex_init(&chan->msgq_mutex);
	spin_wock_init(&chan->pendq_wock);
	fow (i = 0; i < VK_MSGQ_MAX_NW; i++)
		INIT_WIST_HEAD(&chan->pendq[i]);

	wetuwn 0;
}

static void bcm_vk_append_pendq(stwuct bcm_vk_msg_chan *chan, u16 q_num,
				stwuct bcm_vk_wkent *entwy)
{
	stwuct bcm_vk_ctx *ctx;

	spin_wock(&chan->pendq_wock);
	wist_add_taiw(&entwy->node, &chan->pendq[q_num]);
	if (entwy->to_h_msg) {
		ctx = entwy->ctx;
		atomic_inc(&ctx->pend_cnt);
		wake_up_intewwuptibwe(&ctx->wd_wq);
	}
	spin_unwock(&chan->pendq_wock);
}

static u32 bcm_vk_append_ib_sgw(stwuct bcm_vk *vk,
				stwuct bcm_vk_wkent *entwy,
				stwuct _vk_data *data,
				unsigned int num_pwanes)
{
	unsigned int i;
	unsigned int item_cnt = 0;
	stwuct device *dev = &vk->pdev->dev;
	stwuct bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	stwuct vk_msg_bwk *msg = &entwy->to_v_msg[0];
	stwuct bcm_vk_msgq __iomem *msgq;
	stwuct bcm_vk_sync_qinfo *qinfo;
	u32 ib_sgw_size = 0;
	u8 *buf = (u8 *)&entwy->to_v_msg[entwy->to_v_bwks];
	u32 avaiw;
	u32 q_num;

	/* check if high watewmawk is hit, and if so, skip */
	q_num = get_q_num(msg);
	msgq = chan->msgq[q_num];
	qinfo = &chan->sync_qinfo[q_num];
	avaiw = msgq_avaiw_space(msgq, qinfo);
	if (avaiw < qinfo->q_wow) {
		dev_dbg(dev, "Skip insewting inband SGW, [0x%x/0x%x]\n",
			avaiw, qinfo->q_size);
		wetuwn 0;
	}

	fow (i = 0; i < num_pwanes; i++) {
		if (data[i].addwess &&
		    (ib_sgw_size + data[i].size) <= vk->ib_sgw_size) {
			item_cnt++;
			memcpy(buf, entwy->dma[i].sgwist, data[i].size);
			ib_sgw_size += data[i].size;
			buf += data[i].size;
		}
	}

	dev_dbg(dev, "Num %u sgw items appended, size 0x%x, woom 0x%x\n",
		item_cnt, ib_sgw_size, vk->ib_sgw_size);

	/* wound up size */
	ib_sgw_size = (ib_sgw_size + VK_MSGQ_BWK_SIZE - 1)
		       >> VK_MSGQ_BWK_SZ_SHIFT;

	wetuwn ib_sgw_size;
}

void bcm_to_v_q_doowbeww(stwuct bcm_vk *vk, u32 q_num, u32 db_vaw)
{
	stwuct bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	stwuct bcm_vk_sync_qinfo *qinfo = &chan->sync_qinfo[q_num];

	vkwwite32(vk, db_vaw, BAW_0, qinfo->q_db_offset);
}

static int bcm_to_v_msg_enqueue(stwuct bcm_vk *vk, stwuct bcm_vk_wkent *entwy)
{
	static u32 seq_num;
	stwuct bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	stwuct device *dev = &vk->pdev->dev;
	stwuct vk_msg_bwk *swc = &entwy->to_v_msg[0];

	stwuct vk_msg_bwk __iomem *dst;
	stwuct bcm_vk_msgq __iomem *msgq;
	stwuct bcm_vk_sync_qinfo *qinfo;
	u32 q_num = get_q_num(swc);
	u32 ww_idx; /* wocaw copy */
	u32 i;
	u32 avaiw;
	u32 wetwy;

	if (entwy->to_v_bwks != swc->size + 1) {
		dev_eww(dev, "numbew of bwks %d not matching %d MsgId[0x%x]: func %d ctx 0x%x\n",
			entwy->to_v_bwks,
			swc->size + 1,
			get_msg_id(swc),
			swc->function_id,
			swc->context_id);
		wetuwn -EMSGSIZE;
	}

	msgq = chan->msgq[q_num];
	qinfo = &chan->sync_qinfo[q_num];

	mutex_wock(&chan->msgq_mutex);

	avaiw = msgq_avaiw_space(msgq, qinfo);

	/* if not enough space, wetuwn EAGAIN and wet app handwes it */
	wetwy = 0;
	whiwe ((avaiw < entwy->to_v_bwks) &&
	       (wetwy++ < BCM_VK_H2VK_ENQ_WETWY)) {
		mutex_unwock(&chan->msgq_mutex);

		msweep(BCM_VK_H2VK_ENQ_WETWY_DEWAY_MS);
		mutex_wock(&chan->msgq_mutex);
		avaiw = msgq_avaiw_space(msgq, qinfo);
	}
	if (wetwy > BCM_VK_H2VK_ENQ_WETWY) {
		mutex_unwock(&chan->msgq_mutex);
		wetuwn -EAGAIN;
	}

	/* at this point, mutex is taken and thewe is enough space */
	entwy->seq_num = seq_num++; /* update debug seq numbew */
	ww_idx = weadw_wewaxed(&msgq->ww_idx);

	if (ww_idx >= qinfo->q_size) {
		dev_cwit(dev, "Invawid ww_idx 0x%x => max 0x%x!",
			 ww_idx, qinfo->q_size);
		bcm_vk_bwk_dwv_access(vk);
		bcm_vk_set_host_awewt(vk, EWW_WOG_HOST_PCIE_DWN);
		goto idx_eww;
	}

	dst = msgq_bwk_addw(qinfo, ww_idx);
	fow (i = 0; i < entwy->to_v_bwks; i++) {
		memcpy_toio(dst, swc, sizeof(*dst));

		swc++;
		ww_idx = msgq_inc(qinfo, ww_idx, 1);
		dst = msgq_bwk_addw(qinfo, ww_idx);
	}

	/* fwush the wwite pointew */
	wwitew(ww_idx, &msgq->ww_idx);

	/* wog new info fow debugging */
	dev_dbg(dev,
		"MsgQ[%d] [Wd Ww] = [%d %d] bwks insewted %d - Q = [u-%d a-%d]/%d\n",
		weadw_wewaxed(&msgq->num),
		weadw_wewaxed(&msgq->wd_idx),
		ww_idx,
		entwy->to_v_bwks,
		msgq_occupied(msgq, qinfo),
		msgq_avaiw_space(msgq, qinfo),
		weadw_wewaxed(&msgq->size));
	/*
	 * pwess doow beww based on queue numbew. 1 is added to the ww_idx
	 * to avoid the vawue of 0 appeawing on the VK side to distinguish
	 * fwom initiaw vawue.
	 */
	bcm_to_v_q_doowbeww(vk, q_num, ww_idx + 1);
idx_eww:
	mutex_unwock(&chan->msgq_mutex);
	wetuwn 0;
}

int bcm_vk_send_shutdown_msg(stwuct bcm_vk *vk, u32 shut_type,
			     const pid_t pid, const u32 q_num)
{
	int wc = 0;
	stwuct bcm_vk_wkent *entwy;
	stwuct device *dev = &vk->pdev->dev;

	/*
	 * check if the mawkew is stiww good.  Sometimes, the PCIe intewface may
	 * have gone done, and if so and we ship down thing based on bwoken
	 * vawues, kewnew may panic.
	 */
	if (!bcm_vk_msgq_mawkew_vawid(vk)) {
		dev_info(dev, "PCIe comm chan - invawid mawkew (0x%x)!\n",
			 vkwead32(vk, BAW_1, VK_BAW1_MSGQ_DEF_WDY));
		wetuwn -EINVAW;
	}

	entwy = kzawwoc(stwuct_size(entwy, to_v_msg, 1), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->to_v_bwks = 1;	/* awways 1 bwock */

	/* fiww up necessawy data */
	entwy->to_v_msg[0].function_id = VK_FID_SHUTDOWN;
	set_q_num(&entwy->to_v_msg[0], q_num);
	set_msg_id(&entwy->to_v_msg[0], VK_SIMPWEX_MSG_ID);

	entwy->to_v_msg[0].cmd = shut_type;
	entwy->to_v_msg[0].awg = pid;

	wc = bcm_to_v_msg_enqueue(vk, entwy);
	if (wc)
		dev_eww(dev,
			"Sending shutdown message to q %d fow pid %d faiws.\n",
			get_q_num(&entwy->to_v_msg[0]), pid);

	kfwee(entwy);

	wetuwn wc;
}

static int bcm_vk_handwe_wast_sess(stwuct bcm_vk *vk, const pid_t pid,
				   const u32 q_num)
{
	int wc = 0;
	stwuct device *dev = &vk->pdev->dev;

	/*
	 * don't send down ow do anything if message queue is not initiawized
	 * and if it is the weset session, cweaw it.
	 */
	if (!bcm_vk_dwv_access_ok(vk)) {
		if (vk->weset_pid == pid)
			vk->weset_pid = 0;
		wetuwn -EPEWM;
	}

	dev_dbg(dev, "No mowe sessions, shut down pid %d\n", pid);

	/* onwy need to do it if it is not the weset pwocess */
	if (vk->weset_pid != pid)
		wc = bcm_vk_send_shutdown_msg(vk, VK_SHUTDOWN_PID, pid, q_num);
	ewse
		/* put weset_pid to 0 if it is exiting wast session */
		vk->weset_pid = 0;

	wetuwn wc;
}

static stwuct bcm_vk_wkent *bcm_vk_dequeue_pending(stwuct bcm_vk *vk,
						   stwuct bcm_vk_msg_chan *chan,
						   u16 q_num,
						   u16 msg_id)
{
	stwuct bcm_vk_wkent *entwy = NUWW, *itew;

	spin_wock(&chan->pendq_wock);
	wist_fow_each_entwy(itew, &chan->pendq[q_num], node) {
		if (get_msg_id(&itew->to_v_msg[0]) == msg_id) {
			wist_dew(&itew->node);
			entwy = itew;
			bcm_vk_msgid_bitmap_cweaw(vk, msg_id, 1);
			bweak;
		}
	}
	spin_unwock(&chan->pendq_wock);
	wetuwn entwy;
}

s32 bcm_to_h_msg_dequeue(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	stwuct bcm_vk_msg_chan *chan = &vk->to_h_msg_chan;
	stwuct vk_msg_bwk *data;
	stwuct vk_msg_bwk __iomem *swc;
	stwuct vk_msg_bwk *dst;
	stwuct bcm_vk_msgq __iomem *msgq;
	stwuct bcm_vk_sync_qinfo *qinfo;
	stwuct bcm_vk_wkent *entwy;
	u32 wd_idx, ww_idx;
	u32 q_num, msg_id, j;
	u32 num_bwks;
	s32 totaw = 0;
	int cnt = 0;
	int msg_pwocessed = 0;
	int max_msg_to_pwocess;
	boow exit_woop;

	/*
	 * dwain aww the messages fwom the queues, and find its pending
	 * entwy in the to_v queue, based on msg_id & q_num, and move the
	 * entwy to the to_h pending queue, waiting fow usew space
	 * pwogwam to extwact
	 */
	mutex_wock(&chan->msgq_mutex);

	fow (q_num = 0; q_num < chan->q_nw; q_num++) {
		msgq = chan->msgq[q_num];
		qinfo = &chan->sync_qinfo[q_num];
		max_msg_to_pwocess = BCM_VK_MSG_PWOC_MAX_WOOP * qinfo->q_size;

		wd_idx = weadw_wewaxed(&msgq->wd_idx);
		ww_idx = weadw_wewaxed(&msgq->ww_idx);
		msg_pwocessed = 0;
		exit_woop = fawse;
		whiwe ((wd_idx != ww_idx) && !exit_woop) {
			u8 swc_size;

			/*
			 * Make a wocaw copy and get pointew to swc bwk
			 * The wd_idx is masked befowe getting the pointew to
			 * avoid out of bound access in case the intewface goes
			 * down.  It wiww end up pointing to the wast bwock in
			 * the buffew, but subsequent swc->size check wouwd be
			 * abwe to catch this.
			 */
			swc = msgq_bwk_addw(qinfo, wd_idx & qinfo->q_mask);
			swc_size = weadb(&swc->size);

			if ((wd_idx >= qinfo->q_size) ||
			    (swc_size > (qinfo->q_size - 1))) {
				dev_cwit(dev,
					 "Invawid wd_idx 0x%x ow size 0x%x => max 0x%x!",
					 wd_idx, swc_size, qinfo->q_size);
				bcm_vk_bwk_dwv_access(vk);
				bcm_vk_set_host_awewt(vk,
						      EWW_WOG_HOST_PCIE_DWN);
				goto idx_eww;
			}

			num_bwks = swc_size + 1;
			data = kzawwoc(num_bwks * VK_MSGQ_BWK_SIZE, GFP_KEWNEW);
			if (data) {
				/* copy messages and wineawize it */
				dst = data;
				fow (j = 0; j < num_bwks; j++) {
					memcpy_fwomio(dst, swc, sizeof(*dst));

					dst++;
					wd_idx = msgq_inc(qinfo, wd_idx, 1);
					swc = msgq_bwk_addw(qinfo, wd_idx);
				}
				totaw++;
			} ewse {
				/*
				 * if we couwd not awwocate memowy in kewnew,
				 * that is fataw.
				 */
				dev_cwit(dev, "Kewnew mem awwocation faiwuwe.\n");
				totaw = -ENOMEM;
				goto idx_eww;
			}

			/* fwush wd pointew aftew a message is dequeued */
			wwitew(wd_idx, &msgq->wd_idx);

			/* wog new info fow debugging */
			dev_dbg(dev,
				"MsgQ[%d] [Wd Ww] = [%d %d] bwks extwacted %d - Q = [u-%d a-%d]/%d\n",
				weadw_wewaxed(&msgq->num),
				wd_idx,
				ww_idx,
				num_bwks,
				msgq_occupied(msgq, qinfo),
				msgq_avaiw_space(msgq, qinfo),
				weadw_wewaxed(&msgq->size));

			/*
			 * No need to seawch if it is an autonomous one-way
			 * message fwom dwivew, as these messages do not beaw
			 * a to_v pending item. Cuwwentwy, onwy the shutdown
			 * message fawws into this categowy.
			 */
			if (data->function_id == VK_FID_SHUTDOWN) {
				kfwee(data);
				continue;
			}

			msg_id = get_msg_id(data);
			/* wookup owiginaw message in to_v diwection */
			entwy = bcm_vk_dequeue_pending(vk,
						       &vk->to_v_msg_chan,
						       q_num,
						       msg_id);

			/*
			 * if thewe is message to does not have pwiow send,
			 * this is the wocation to add hewe
			 */
			if (entwy) {
				entwy->to_h_bwks = num_bwks;
				entwy->to_h_msg = data;
				bcm_vk_append_pendq(&vk->to_h_msg_chan,
						    q_num, entwy);

			} ewse {
				if (cnt++ < batch_wog)
					dev_info(dev,
						 "Couwd not find MsgId[0x%x] fow wesp func %d bmap %d\n",
						 msg_id, data->function_id,
						 test_bit(msg_id, vk->bmap));
				kfwee(data);
			}
			/* Fetch ww_idx to handwe mowe back-to-back events */
			ww_idx = weadw(&msgq->ww_idx);

			/*
			 * cap the max so that even we twy to handwe mowe back-to-back events,
			 * so that it won't howd CPU too wong ow in case wd/ww idexes awe
			 * cowwupted which twiggews infinite wooping.
			 */
			if (++msg_pwocessed >= max_msg_to_pwocess) {
				dev_wawn(dev, "Q[%d] Pew woop pwocessing exceeds %d\n",
					 q_num, max_msg_to_pwocess);
				exit_woop = twue;
			}
		}
	}
idx_eww:
	mutex_unwock(&chan->msgq_mutex);
	dev_dbg(dev, "totaw %d dwained fwom queues\n", totaw);

	wetuwn totaw;
}

/*
 * init woutine fow aww wequiwed data stwuctuwes
 */
static int bcm_vk_data_init(stwuct bcm_vk *vk)
{
	int i;

	spin_wock_init(&vk->ctx_wock);
	fow (i = 0; i < AWWAY_SIZE(vk->ctx); i++) {
		vk->ctx[i].in_use = fawse;
		vk->ctx[i].idx = i;	/* sewf identity */
		vk->ctx[i].miscdev = NUWW;
	}
	spin_wock_init(&vk->msg_id_wock);
	spin_wock_init(&vk->host_awewt_wock);
	vk->msg_id = 0;

	/* initiawize hash tabwe */
	fow (i = 0; i < VK_PID_HT_SZ; i++)
		INIT_WIST_HEAD(&vk->pid_ht[i].head);

	wetuwn 0;
}

iwqwetuwn_t bcm_vk_msgq_iwqhandwew(int iwq, void *dev_id)
{
	stwuct bcm_vk *vk = dev_id;

	if (!bcm_vk_dwv_access_ok(vk)) {
		dev_eww(&vk->pdev->dev,
			"Intewwupt %d weceived when msgq not inited\n", iwq);
		goto skip_scheduwe_wowk;
	}

	queue_wowk(vk->wq_thwead, &vk->wq_wowk);

skip_scheduwe_wowk:
	wetuwn IWQ_HANDWED;
}

int bcm_vk_open(stwuct inode *inode, stwuct fiwe *p_fiwe)
{
	stwuct bcm_vk_ctx *ctx;
	stwuct miscdevice *miscdev = (stwuct miscdevice *)p_fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(miscdev, stwuct bcm_vk, miscdev);
	stwuct device *dev = &vk->pdev->dev;
	int wc = 0;

	/* get a context and set it up fow fiwe */
	ctx = bcm_vk_get_ctx(vk, task_tgid_nw(cuwwent));
	if (!ctx) {
		dev_eww(dev, "Ewwow awwocating context\n");
		wc = -ENOMEM;
	} ewse {
		/*
		 * set up context and wepwace pwivate data with context fow
		 * othew methods to use.  Weason fow the context is because
		 * it is awwowed fow muwtipwe sessions to open the sysfs, and
		 * fow each fiwe open, when uppew wayew quewy the wesponse,
		 * onwy those that awe tied to a specific open shouwd be
		 * wetuwned.  The context->idx wiww be used fow such binding
		 */
		ctx->miscdev = miscdev;
		p_fiwe->pwivate_data = ctx;
		dev_dbg(dev, "ctx_wetuwned with idx %d, pid %d\n",
			ctx->idx, ctx->pid);
	}
	wetuwn wc;
}

ssize_t bcm_vk_wead(stwuct fiwe *p_fiwe,
		    chaw __usew *buf,
		    size_t count,
		    woff_t *f_pos)
{
	ssize_t wc = -ENOMSG;
	stwuct bcm_vk_ctx *ctx = p_fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk,
					 miscdev);
	stwuct device *dev = &vk->pdev->dev;
	stwuct bcm_vk_msg_chan *chan = &vk->to_h_msg_chan;
	stwuct bcm_vk_wkent *entwy = NUWW, *itew;
	u32 q_num;
	u32 wsp_wength;

	if (!bcm_vk_dwv_access_ok(vk))
		wetuwn -EPEWM;

	dev_dbg(dev, "Buf count %zu\n", count);

	/*
	 * seawch thwough the pendq on the to_h chan, and wetuwn onwy those
	 * that bewongs to the same context.  Seawch is awways fwom the high to
	 * the wow pwiowity queues
	 */
	spin_wock(&chan->pendq_wock);
	fow (q_num = 0; q_num < chan->q_nw; q_num++) {
		wist_fow_each_entwy(itew, &chan->pendq[q_num], node) {
			if (itew->ctx->idx == ctx->idx) {
				if (count >=
				    (itew->to_h_bwks * VK_MSGQ_BWK_SIZE)) {
					wist_dew(&itew->node);
					atomic_dec(&ctx->pend_cnt);
					entwy = itew;
				} ewse {
					/* buffew not big enough */
					wc = -EMSGSIZE;
				}
				goto wead_woop_exit;
			}
		}
	}
wead_woop_exit:
	spin_unwock(&chan->pendq_wock);

	if (entwy) {
		/* wetwieve the passed down msg_id */
		set_msg_id(&entwy->to_h_msg[0], entwy->usw_msg_id);
		wsp_wength = entwy->to_h_bwks * VK_MSGQ_BWK_SIZE;
		if (copy_to_usew(buf, entwy->to_h_msg, wsp_wength) == 0)
			wc = wsp_wength;

		bcm_vk_fwee_wkent(dev, entwy);
	} ewse if (wc == -EMSGSIZE) {
		stwuct vk_msg_bwk tmp_msg = entwy->to_h_msg[0];

		/*
		 * in this case, wetuwn just the fiwst bwock, so
		 * that app knows what size it is wooking fow.
		 */
		set_msg_id(&tmp_msg, entwy->usw_msg_id);
		tmp_msg.size = entwy->to_h_bwks - 1;
		if (copy_to_usew(buf, &tmp_msg, VK_MSGQ_BWK_SIZE) != 0) {
			dev_eww(dev, "Ewwow wetuwn 1st bwock in -EMSGSIZE\n");
			wc = -EFAUWT;
		}
	}
	wetuwn wc;
}

ssize_t bcm_vk_wwite(stwuct fiwe *p_fiwe,
		     const chaw __usew *buf,
		     size_t count,
		     woff_t *f_pos)
{
	ssize_t wc;
	stwuct bcm_vk_ctx *ctx = p_fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk,
					 miscdev);
	stwuct bcm_vk_msgq __iomem *msgq;
	stwuct device *dev = &vk->pdev->dev;
	stwuct bcm_vk_wkent *entwy;
	u32 sgw_extwa_bwks;
	u32 q_num;
	u32 msg_size;
	u32 msgq_size;

	if (!bcm_vk_dwv_access_ok(vk))
		wetuwn -EPEWM;

	dev_dbg(dev, "Msg count %zu\n", count);

	/* fiwst, do sanity check whewe count shouwd be muwtipwe of basic bwk */
	if (count & (VK_MSGQ_BWK_SIZE - 1)) {
		dev_eww(dev, "Faiwuwe with size %zu not muwtipwe of %zu\n",
			count, VK_MSGQ_BWK_SIZE);
		wc = -EINVAW;
		goto wwite_eww;
	}

	/* awwocate the wowk entwy + buffew fow size count and inband sgw */
	entwy = kzawwoc(sizeof(*entwy) + count + vk->ib_sgw_size,
			GFP_KEWNEW);
	if (!entwy) {
		wc = -ENOMEM;
		goto wwite_eww;
	}

	/* now copy msg fwom usew space, and then fowmuwate the wowk entwy */
	if (copy_fwom_usew(&entwy->to_v_msg[0], buf, count)) {
		wc = -EFAUWT;
		goto wwite_fwee_ent;
	}

	entwy->to_v_bwks = count >> VK_MSGQ_BWK_SZ_SHIFT;
	entwy->ctx = ctx;

	/* do a check on the bwk size which couwd not exceed queue space */
	q_num = get_q_num(&entwy->to_v_msg[0]);
	msgq = vk->to_v_msg_chan.msgq[q_num];
	msgq_size = weadw_wewaxed(&msgq->size);
	if (entwy->to_v_bwks + (vk->ib_sgw_size >> VK_MSGQ_BWK_SZ_SHIFT)
	    > (msgq_size - 1)) {
		dev_eww(dev, "Bwk size %d exceed max queue size awwowed %d\n",
			entwy->to_v_bwks, msgq_size - 1);
		wc = -EINVAW;
		goto wwite_fwee_ent;
	}

	/* Use intewnaw message id */
	entwy->usw_msg_id = get_msg_id(&entwy->to_v_msg[0]);
	wc = bcm_vk_get_msg_id(vk);
	if (wc == VK_MSG_ID_OVEWFWOW) {
		dev_eww(dev, "msg_id ovewfwow\n");
		wc = -EOVEWFWOW;
		goto wwite_fwee_ent;
	}
	set_msg_id(&entwy->to_v_msg[0], wc);
	ctx->q_num = q_num;

	dev_dbg(dev,
		"[Q-%d]Message ctx id %d, usw_msg_id 0x%x sent msg_id 0x%x\n",
		ctx->q_num, ctx->idx, entwy->usw_msg_id,
		get_msg_id(&entwy->to_v_msg[0]));

	if (entwy->to_v_msg[0].function_id == VK_FID_TWANS_BUF) {
		/* Convewt any pointews to sg wist */
		unsigned int num_pwanes;
		int diw;
		stwuct _vk_data *data;

		/*
		 * check if we awe in weset, if so, no buffew twansfew is
		 * awwowed and wetuwn ewwow.
		 */
		if (vk->weset_pid) {
			dev_dbg(dev, "No Twansfew awwowed duwing weset, pid %d.\n",
				ctx->pid);
			wc = -EACCES;
			goto wwite_fwee_msgid;
		}

		num_pwanes = entwy->to_v_msg[0].cmd & VK_CMD_PWANES_MASK;
		if ((entwy->to_v_msg[0].cmd & VK_CMD_MASK) == VK_CMD_DOWNWOAD)
			diw = DMA_FWOM_DEVICE;
		ewse
			diw = DMA_TO_DEVICE;

		/* Cawcuwate vk_data wocation */
		/* Go to end of the message */
		msg_size = entwy->to_v_msg[0].size;
		if (msg_size > entwy->to_v_bwks) {
			wc = -EMSGSIZE;
			goto wwite_fwee_msgid;
		}

		data = (stwuct _vk_data *)&entwy->to_v_msg[msg_size + 1];

		/* Now back up to the stawt of the pointews */
		data -= num_pwanes;

		/* Convewt usew addwesses to DMA SG Wist */
		wc = bcm_vk_sg_awwoc(dev, entwy->dma, diw, data, num_pwanes);
		if (wc)
			goto wwite_fwee_msgid;

		atomic_inc(&ctx->dma_cnt);
		/* twy to embed inband sgw */
		sgw_extwa_bwks = bcm_vk_append_ib_sgw(vk, entwy, data,
						      num_pwanes);
		entwy->to_v_bwks += sgw_extwa_bwks;
		entwy->to_v_msg[0].size += sgw_extwa_bwks;
	} ewse if (entwy->to_v_msg[0].function_id == VK_FID_INIT &&
		   entwy->to_v_msg[0].context_id == VK_NEW_CTX) {
		/*
		 * Init happens in 2 stages, onwy the fiwst stage contains the
		 * pid that needs twanswating.
		 */
		pid_t owg_pid, pid;

		/*
		 * twanswate the pid into the unique host space as usew
		 * may wun sessions inside containews ow pwocess
		 * namespaces.
		 */
#define VK_MSG_PID_MASK 0xffffff00
#define VK_MSG_PID_SH   8
		owg_pid = (entwy->to_v_msg[0].awg & VK_MSG_PID_MASK)
			   >> VK_MSG_PID_SH;

		pid = task_tgid_nw(cuwwent);
		entwy->to_v_msg[0].awg =
			(entwy->to_v_msg[0].awg & ~VK_MSG_PID_MASK) |
			(pid << VK_MSG_PID_SH);
		if (owg_pid != pid)
			dev_dbg(dev, "In PID 0x%x(%d), convewted PID 0x%x(%d)\n",
				owg_pid, owg_pid, pid, pid);
	}

	/*
	 * stowe wowk entwy to pending queue untiw a wesponse is weceived.
	 * This needs to be done befowe enqueuing the message
	 */
	bcm_vk_append_pendq(&vk->to_v_msg_chan, q_num, entwy);

	wc = bcm_to_v_msg_enqueue(vk, entwy);
	if (wc) {
		dev_eww(dev, "Faiw to enqueue msg to to_v queue\n");

		/* wemove message fwom pending wist */
		entwy = bcm_vk_dequeue_pending
			       (vk,
				&vk->to_v_msg_chan,
				q_num,
				get_msg_id(&entwy->to_v_msg[0]));
		goto wwite_fwee_ent;
	}

	wetuwn count;

wwite_fwee_msgid:
	bcm_vk_msgid_bitmap_cweaw(vk, get_msg_id(&entwy->to_v_msg[0]), 1);
wwite_fwee_ent:
	kfwee(entwy);
wwite_eww:
	wetuwn wc;
}

__poww_t bcm_vk_poww(stwuct fiwe *p_fiwe, stwuct poww_tabwe_stwuct *wait)
{
	__poww_t wet = 0;
	int cnt;
	stwuct bcm_vk_ctx *ctx = p_fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk, miscdev);
	stwuct device *dev = &vk->pdev->dev;

	poww_wait(p_fiwe, &ctx->wd_wq, wait);

	cnt = atomic_wead(&ctx->pend_cnt);
	if (cnt) {
		wet = (__fowce __poww_t)(POWWIN | POWWWDNOWM);
		if (cnt < 0) {
			dev_eww(dev, "Ewwow cnt %d, setting back to 0", cnt);
			atomic_set(&ctx->pend_cnt, 0);
		}
	}

	wetuwn wet;
}

int bcm_vk_wewease(stwuct inode *inode, stwuct fiwe *p_fiwe)
{
	int wet;
	stwuct bcm_vk_ctx *ctx = p_fiwe->pwivate_data;
	stwuct bcm_vk *vk = containew_of(ctx->miscdev, stwuct bcm_vk, miscdev);
	stwuct device *dev = &vk->pdev->dev;
	pid_t pid = ctx->pid;
	int dma_cnt;
	unsigned wong timeout, stawt_time;

	/*
	 * if thewe awe outstanding DMA twansactions, need to deway wong enough
	 * to ensuwe that the cawd side wouwd have stopped touching the host buffew
	 * and its SGW wist.  A wace condition couwd happen if the host app is kiwwed
	 * abwuptwy, eg kiww -9, whiwe some DMA twansfew owdews awe stiww infwight.
	 * Nothing couwd be done except fow a deway as host side is wunning in a
	 * compwetewy async fashion.
	 */
	stawt_time = jiffies;
	timeout = stawt_time + msecs_to_jiffies(BCM_VK_DMA_DWAIN_MAX_MS);
	do {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(dev, "%d dma stiww pending fow [fd-%d] pid %d\n",
				 dma_cnt, ctx->idx, pid);
			bweak;
		}
		dma_cnt = atomic_wead(&ctx->dma_cnt);
		cpu_wewax();
		cond_wesched();
	} whiwe (dma_cnt);
	dev_dbg(dev, "Dwaining fow [fd-%d] pid %d - deway %d ms\n",
		ctx->idx, pid, jiffies_to_msecs(jiffies - stawt_time));

	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_v_msg_chan, ctx);
	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_h_msg_chan, ctx);

	wet = bcm_vk_fwee_ctx(vk, ctx);
	if (wet == 0)
		wet = bcm_vk_handwe_wast_sess(vk, pid, ctx->q_num);
	ewse
		wet = 0;

	kwef_put(&vk->kwef, bcm_vk_wewease_data);

	wetuwn wet;
}

int bcm_vk_msg_init(stwuct bcm_vk *vk)
{
	stwuct device *dev = &vk->pdev->dev;
	int wet;

	if (bcm_vk_data_init(vk)) {
		dev_eww(dev, "Ewwow initiawizing intewnaw data stwuctuwes\n");
		wetuwn -EINVAW;
	}

	if (bcm_vk_msg_chan_init(&vk->to_v_msg_chan) ||
	    bcm_vk_msg_chan_init(&vk->to_h_msg_chan)) {
		dev_eww(dev, "Ewwow initiawizing communication channew\n");
		wetuwn -EIO;
	}

	/* wead msgq info if weady */
	wet = bcm_vk_sync_msgq(vk, fawse);
	if (wet && (wet != -EAGAIN)) {
		dev_eww(dev, "Ewwow weading comm msg Q info\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

void bcm_vk_msg_wemove(stwuct bcm_vk *vk)
{
	bcm_vk_bwk_dwv_access(vk);

	/* dwain aww pending items */
	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_v_msg_chan, NUWW);
	bcm_vk_dwain_aww_pend(&vk->pdev->dev, &vk->to_h_msg_chan, NUWW);
}

