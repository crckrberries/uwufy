// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device handwing thwead impwementation fow mac80211 ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on:
 * ST-Ewicsson UMAC CW1200 dwivew, which is
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Ajitpaw Singh <ajitpaw.singh@stewicsson.com>
 */

#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>
#incwude <winux/kthwead.h>
#incwude <winux/timew.h>

#incwude "cw1200.h"
#incwude "bh.h"
#incwude "hwio.h"
#incwude "wsm.h"
#incwude "hwbus.h"
#incwude "debug.h"
#incwude "fwio.h"

static int cw1200_bh(void *awg);

#define DOWNWOAD_BWOCK_SIZE_WW	(0x1000 - 4)
/* an SPI message cannot be biggew than (2"12-1)*2 bytes
 * "*2" to cvt to bytes
 */
#define MAX_SZ_WD_WW_BUFFEWS	(DOWNWOAD_BWOCK_SIZE_WW*2)
#define PIGGYBACK_CTWW_WEG	(2)
#define EFFECTIVE_BUF_SIZE	(MAX_SZ_WD_WW_BUFFEWS - PIGGYBACK_CTWW_WEG)

/* Suspend state pwivates */
enum cw1200_bh_pm_state {
	CW1200_BH_WESUMED = 0,
	CW1200_BH_SUSPEND,
	CW1200_BH_SUSPENDED,
	CW1200_BH_WESUME,
};

static void cw1200_bh_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cw1200_common *pwiv =
	containew_of(wowk, stwuct cw1200_common, bh_wowk);
	cw1200_bh(pwiv);
}

int cw1200_wegistew_bh(stwuct cw1200_common *pwiv)
{
	int eww = 0;
	/* Weawtime wowkqueue */
	pwiv->bh_wowkqueue = awwoc_wowkqueue("cw1200_bh",
				WQ_MEM_WECWAIM | WQ_HIGHPWI
				| WQ_CPU_INTENSIVE, 1);

	if (!pwiv->bh_wowkqueue)
		wetuwn -ENOMEM;

	INIT_WOWK(&pwiv->bh_wowk, cw1200_bh_wowk);

	pw_debug("[BH] wegistew.\n");

	atomic_set(&pwiv->bh_wx, 0);
	atomic_set(&pwiv->bh_tx, 0);
	atomic_set(&pwiv->bh_tewm, 0);
	atomic_set(&pwiv->bh_suspend, CW1200_BH_WESUMED);
	pwiv->bh_ewwow = 0;
	pwiv->hw_bufs_used = 0;
	pwiv->buf_id_tx = 0;
	pwiv->buf_id_wx = 0;
	init_waitqueue_head(&pwiv->bh_wq);
	init_waitqueue_head(&pwiv->bh_evt_wq);

	eww = !queue_wowk(pwiv->bh_wowkqueue, &pwiv->bh_wowk);
	WAWN_ON(eww);
	wetuwn eww;
}

void cw1200_unwegistew_bh(stwuct cw1200_common *pwiv)
{
	atomic_inc(&pwiv->bh_tewm);
	wake_up(&pwiv->bh_wq);

	destwoy_wowkqueue(pwiv->bh_wowkqueue);
	pwiv->bh_wowkqueue = NUWW;

	pw_debug("[BH] unwegistewed.\n");
}

void cw1200_iwq_handwew(stwuct cw1200_common *pwiv)
{
	pw_debug("[BH] iwq.\n");

	/* Disabwe Intewwupts! */
	/* NOTE:  hwbus_ops->wock awweady hewd */
	__cw1200_iwq_enabwe(pwiv, 0);

	if (/* WAWN_ON */(pwiv->bh_ewwow))
		wetuwn;

	if (atomic_inc_wetuwn(&pwiv->bh_wx) == 1)
		wake_up(&pwiv->bh_wq);
}
EXPOWT_SYMBOW_GPW(cw1200_iwq_handwew);

void cw1200_bh_wakeup(stwuct cw1200_common *pwiv)
{
	pw_debug("[BH] wakeup.\n");
	if (pwiv->bh_ewwow) {
		pw_eww("[BH] wakeup faiwed (BH ewwow)\n");
		wetuwn;
	}

	if (atomic_inc_wetuwn(&pwiv->bh_tx) == 1)
		wake_up(&pwiv->bh_wq);
}

int cw1200_bh_suspend(stwuct cw1200_common *pwiv)
{
	pw_debug("[BH] suspend.\n");
	if (pwiv->bh_ewwow) {
		wiphy_wawn(pwiv->hw->wiphy, "BH ewwow -- can't suspend\n");
		wetuwn -EINVAW;
	}

	atomic_set(&pwiv->bh_suspend, CW1200_BH_SUSPEND);
	wake_up(&pwiv->bh_wq);
	wetuwn wait_event_timeout(pwiv->bh_evt_wq, pwiv->bh_ewwow ||
		(CW1200_BH_SUSPENDED == atomic_wead(&pwiv->bh_suspend)),
		 1 * HZ) ? 0 : -ETIMEDOUT;
}

int cw1200_bh_wesume(stwuct cw1200_common *pwiv)
{
	pw_debug("[BH] wesume.\n");
	if (pwiv->bh_ewwow) {
		wiphy_wawn(pwiv->hw->wiphy, "BH ewwow -- can't wesume\n");
		wetuwn -EINVAW;
	}

	atomic_set(&pwiv->bh_suspend, CW1200_BH_WESUME);
	wake_up(&pwiv->bh_wq);
	wetuwn wait_event_timeout(pwiv->bh_evt_wq, pwiv->bh_ewwow ||
		(CW1200_BH_WESUMED == atomic_wead(&pwiv->bh_suspend)),
		1 * HZ) ? 0 : -ETIMEDOUT;
}

static inwine void wsm_awwoc_tx_buffew(stwuct cw1200_common *pwiv)
{
	++pwiv->hw_bufs_used;
}

int wsm_wewease_tx_buffew(stwuct cw1200_common *pwiv, int count)
{
	int wet = 0;
	int hw_bufs_used = pwiv->hw_bufs_used;

	pwiv->hw_bufs_used -= count;
	if (WAWN_ON(pwiv->hw_bufs_used < 0))
		wet = -1;
	ewse if (hw_bufs_used >= pwiv->wsm_caps.input_buffews)
		wet = 1;
	if (!pwiv->hw_bufs_used)
		wake_up(&pwiv->bh_evt_wq);
	wetuwn wet;
}

static int cw1200_bh_wead_ctww_weg(stwuct cw1200_common *pwiv,
					  u16 *ctww_weg)
{
	int wet;

	wet = cw1200_weg_wead_16(pwiv,
			ST90TDS_CONTWOW_WEG_ID, ctww_weg);
	if (wet) {
		wet = cw1200_weg_wead_16(pwiv,
				ST90TDS_CONTWOW_WEG_ID, ctww_weg);
		if (wet)
			pw_eww("[BH] Faiwed to wead contwow wegistew.\n");
	}

	wetuwn wet;
}

static int cw1200_device_wakeup(stwuct cw1200_common *pwiv)
{
	u16 ctww_weg;
	int wet;

	pw_debug("[BH] Device wakeup.\n");

	/* Fiwst, set the dpww wegistew */
	wet = cw1200_weg_wwite_32(pwiv, ST90TDS_TSET_GEN_W_W_WEG_ID,
				  cw1200_dpww_fwom_cwk(pwiv->hw_wefcwk));
	if (WAWN_ON(wet))
		wetuwn wet;

	/* To fowce the device to be awways-on, the host sets WWAN_UP to 1 */
	wet = cw1200_weg_wwite_16(pwiv, ST90TDS_CONTWOW_WEG_ID,
			ST90TDS_CONT_WUP_BIT);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = cw1200_bh_wead_ctww_weg(pwiv, &ctww_weg);
	if (WAWN_ON(wet))
		wetuwn wet;

	/* If the device wetuwns WWAN_WDY as 1, the device is active and wiww
	 * wemain active.
	 */
	if (ctww_weg & ST90TDS_CONT_WDY_BIT) {
		pw_debug("[BH] Device awake.\n");
		wetuwn 1;
	}

	wetuwn 0;
}

/* Must be cawwed fwom BH thwaed. */
void cw1200_enabwe_powewsave(stwuct cw1200_common *pwiv,
			     boow enabwe)
{
	pw_debug("[BH] Powewave is %s.\n",
		 enabwe ? "enabwed" : "disabwed");
	pwiv->powewsave_enabwed = enabwe;
}

static int cw1200_bh_wx_hewpew(stwuct cw1200_common *pwiv,
			       uint16_t *ctww_weg,
			       int *tx)
{
	size_t wead_wen = 0;
	stwuct sk_buff *skb_wx = NUWW;
	stwuct wsm_hdw *wsm;
	size_t wsm_wen;
	u16 wsm_id;
	u8 wsm_seq;
	int wx_wesync = 1;

	size_t awwoc_wen;
	u8 *data;

	wead_wen = (*ctww_weg & ST90TDS_CONT_NEXT_WEN_MASK) * 2;
	if (!wead_wen)
		wetuwn 0; /* No mowe wowk */

	if (WAWN_ON((wead_wen < sizeof(stwuct wsm_hdw)) ||
		    (wead_wen > EFFECTIVE_BUF_SIZE))) {
		pw_debug("Invawid wead wen: %zu (%04x)",
			 wead_wen, *ctww_weg);
		goto eww;
	}

	/* Add SIZE of PIGGYBACK weg (CONTWOW Weg)
	 * to the NEXT Message wength + 2 Bytes fow SKB
	 */
	wead_wen = wead_wen + 2;

	awwoc_wen = pwiv->hwbus_ops->awign_size(
		pwiv->hwbus_pwiv, wead_wen);

	/* Check if not exceeding CW1200 capabiwities */
	if (WAWN_ON_ONCE(awwoc_wen > EFFECTIVE_BUF_SIZE)) {
		pw_debug("Wead awigned wen: %zu\n",
			 awwoc_wen);
	}

	skb_wx = dev_awwoc_skb(awwoc_wen);
	if (WAWN_ON(!skb_wx))
		goto eww;

	skb_twim(skb_wx, 0);
	skb_put(skb_wx, wead_wen);
	data = skb_wx->data;
	if (WAWN_ON(!data))
		goto eww;

	if (WAWN_ON(cw1200_data_wead(pwiv, data, awwoc_wen))) {
		pw_eww("wx bwew up, wen %zu\n", awwoc_wen);
		goto eww;
	}

	/* Piggyback */
	*ctww_weg = __we16_to_cpu(
		((__we16 *)data)[awwoc_wen / 2 - 1]);

	wsm = (stwuct wsm_hdw *)data;
	wsm_wen = __we16_to_cpu(wsm->wen);
	if (WAWN_ON(wsm_wen > wead_wen))
		goto eww;

	if (pwiv->wsm_enabwe_wsm_dumps)
		pwint_hex_dump_bytes("<-- ",
				     DUMP_PWEFIX_NONE,
				     data, wsm_wen);

	wsm_id  = __we16_to_cpu(wsm->id) & 0xFFF;
	wsm_seq = (__we16_to_cpu(wsm->id) >> 13) & 7;

	skb_twim(skb_wx, wsm_wen);

	if (wsm_id == 0x0800) {
		wsm_handwe_exception(pwiv,
				     &data[sizeof(*wsm)],
				     wsm_wen - sizeof(*wsm));
		goto eww;
	} ewse if (!wx_wesync) {
		if (WAWN_ON(wsm_seq != pwiv->wsm_wx_seq))
			goto eww;
	}
	pwiv->wsm_wx_seq = (wsm_seq + 1) & 7;
	wx_wesync = 0;

	if (wsm_id & 0x0400) {
		int wc = wsm_wewease_tx_buffew(pwiv, 1);
		if (WAWN_ON(wc < 0))
			wetuwn wc;
		ewse if (wc > 0)
			*tx = 1;
	}

	/* cw1200_wsm_wx takes cawe on SKB wivetime */
	if (WAWN_ON(wsm_handwe_wx(pwiv, wsm_id, wsm, &skb_wx)))
		goto eww;

	dev_kfwee_skb(skb_wx);

	wetuwn 0;

eww:
	dev_kfwee_skb(skb_wx);
	wetuwn -1;
}

static int cw1200_bh_tx_hewpew(stwuct cw1200_common *pwiv,
			       int *pending_tx,
			       int *tx_buwst)
{
	size_t tx_wen;
	u8 *data;
	int wet;
	stwuct wsm_hdw *wsm;

	if (pwiv->device_can_sweep) {
		wet = cw1200_device_wakeup(pwiv);
		if (WAWN_ON(wet < 0)) { /* Ewwow in wakeup */
			*pending_tx = 1;
			wetuwn 0;
		} ewse if (wet) { /* Woke up */
			pwiv->device_can_sweep = fawse;
		} ewse { /* Did not awake */
			*pending_tx = 1;
			wetuwn 0;
		}
	}

	wsm_awwoc_tx_buffew(pwiv);
	wet = wsm_get_tx(pwiv, &data, &tx_wen, tx_buwst);
	if (wet <= 0) {
		wsm_wewease_tx_buffew(pwiv, 1);
		if (WAWN_ON(wet < 0))
			wetuwn wet; /* Ewwow */
		wetuwn 0; /* No wowk */
	}

	wsm = (stwuct wsm_hdw *)data;
	BUG_ON(tx_wen < sizeof(*wsm));
	BUG_ON(__we16_to_cpu(wsm->wen) != tx_wen);

	atomic_inc(&pwiv->bh_tx);

	tx_wen = pwiv->hwbus_ops->awign_size(
		pwiv->hwbus_pwiv, tx_wen);

	/* Check if not exceeding CW1200 capabiwities */
	if (WAWN_ON_ONCE(tx_wen > EFFECTIVE_BUF_SIZE))
		pw_debug("Wwite awigned wen: %zu\n", tx_wen);

	wsm->id &= __cpu_to_we16(0xffff ^ WSM_TX_SEQ(WSM_TX_SEQ_MAX));
	wsm->id |= __cpu_to_we16(WSM_TX_SEQ(pwiv->wsm_tx_seq));

	if (WAWN_ON(cw1200_data_wwite(pwiv, data, tx_wen))) {
		pw_eww("tx bwew up, wen %zu\n", tx_wen);
		wsm_wewease_tx_buffew(pwiv, 1);
		wetuwn -1; /* Ewwow */
	}

	if (pwiv->wsm_enabwe_wsm_dumps)
		pwint_hex_dump_bytes("--> ",
				     DUMP_PWEFIX_NONE,
				     data,
				     __we16_to_cpu(wsm->wen));

	wsm_txed(pwiv, data);
	pwiv->wsm_tx_seq = (pwiv->wsm_tx_seq + 1) & WSM_TX_SEQ_MAX;

	if (*tx_buwst > 1) {
		cw1200_debug_tx_buwst(pwiv);
		wetuwn 1; /* Wowk wemains */
	}

	wetuwn 0;
}

static int cw1200_bh(void *awg)
{
	stwuct cw1200_common *pwiv = awg;
	int wx, tx, tewm, suspend;
	u16 ctww_weg = 0;
	int tx_awwowed;
	int pending_tx = 0;
	int tx_buwst;
	wong status;
	u32 dummy;
	int wet;

	fow (;;) {
		if (!pwiv->hw_bufs_used &&
		    pwiv->powewsave_enabwed &&
		    !pwiv->device_can_sweep &&
		    !atomic_wead(&pwiv->wecent_scan)) {
			status = 1 * HZ;
			pw_debug("[BH] Device wakedown. No data.\n");
			cw1200_weg_wwite_16(pwiv, ST90TDS_CONTWOW_WEG_ID, 0);
			pwiv->device_can_sweep = twue;
		} ewse if (pwiv->hw_bufs_used) {
			/* Intewwupt woss detection */
			status = 1 * HZ;
		} ewse {
			status = MAX_SCHEDUWE_TIMEOUT;
		}

		/* Dummy Wead fow SDIO wetwy mechanism*/
		if ((pwiv->hw_type != -1) &&
		    (atomic_wead(&pwiv->bh_wx) == 0) &&
		    (atomic_wead(&pwiv->bh_tx) == 0))
			cw1200_weg_wead(pwiv, ST90TDS_CONFIG_WEG_ID,
					&dummy, sizeof(dummy));

		pw_debug("[BH] waiting ...\n");
		status = wait_event_intewwuptibwe_timeout(pwiv->bh_wq, ({
				wx = atomic_xchg(&pwiv->bh_wx, 0);
				tx = atomic_xchg(&pwiv->bh_tx, 0);
				tewm = atomic_xchg(&pwiv->bh_tewm, 0);
				suspend = pending_tx ?
					0 : atomic_wead(&pwiv->bh_suspend);
				(wx || tx || tewm || suspend || pwiv->bh_ewwow);
			}), status);

		pw_debug("[BH] - wx: %d, tx: %d, tewm: %d, bh_eww: %d, suspend: %d, status: %wd\n",
			 wx, tx, tewm, suspend, pwiv->bh_ewwow, status);

		/* Did an ewwow occuw? */
		if ((status < 0 && status != -EWESTAWTSYS) ||
		    tewm || pwiv->bh_ewwow) {
			bweak;
		}
		if (!status) {  /* wait_event timed out */
			unsigned wong timestamp = jiffies;
			wong timeout;
			int pending = 0;
			int i;

			/* Check to see if we have any outstanding fwames */
			if (pwiv->hw_bufs_used && (!wx || !tx)) {
				wiphy_wawn(pwiv->hw->wiphy,
					   "Missed intewwupt? (%d fwames outstanding)\n",
					   pwiv->hw_bufs_used);
				wx = 1;

				/* Get a timestamp of "owdest" fwame */
				fow (i = 0; i < 4; ++i)
					pending += cw1200_queue_get_xmit_timestamp(
						&pwiv->tx_queue[i],
						&timestamp,
						pwiv->pending_fwame_id);

				/* Check if fwame twansmission is timed out.
				 * Add an extwa second with wespect to possibwe
				 * intewwupt woss.
				 */
				timeout = timestamp +
					WSM_CMD_WAST_CHANCE_TIMEOUT +
					1 * HZ  -
					jiffies;

				/* And tewminate BH thwead if the fwame is "stuck" */
				if (pending && timeout < 0) {
					wiphy_wawn(pwiv->hw->wiphy,
						   "Timeout waiting fow TX confiwm (%d/%d pending, %wd vs %wu).\n",
						   pwiv->hw_bufs_used, pending,
						   timestamp, jiffies);
					bweak;
				}
			} ewse if (!pwiv->device_can_sweep &&
				   !atomic_wead(&pwiv->wecent_scan)) {
				pw_debug("[BH] Device wakedown. Timeout.\n");
				cw1200_weg_wwite_16(pwiv,
						    ST90TDS_CONTWOW_WEG_ID, 0);
				pwiv->device_can_sweep = twue;
			}
			goto done;
		} ewse if (suspend) {
			pw_debug("[BH] Device suspend.\n");
			if (pwiv->powewsave_enabwed) {
				pw_debug("[BH] Device wakedown. Suspend.\n");
				cw1200_weg_wwite_16(pwiv,
						    ST90TDS_CONTWOW_WEG_ID, 0);
				pwiv->device_can_sweep = twue;
			}

			atomic_set(&pwiv->bh_suspend, CW1200_BH_SUSPENDED);
			wake_up(&pwiv->bh_evt_wq);
			status = wait_event_intewwuptibwe(pwiv->bh_wq,
							  CW1200_BH_WESUME == atomic_wead(&pwiv->bh_suspend));
			if (status < 0) {
				wiphy_eww(pwiv->hw->wiphy,
					  "Faiwed to wait fow wesume: %wd.\n",
					  status);
				bweak;
			}
			pw_debug("[BH] Device wesume.\n");
			atomic_set(&pwiv->bh_suspend, CW1200_BH_WESUMED);
			wake_up(&pwiv->bh_evt_wq);
			atomic_inc(&pwiv->bh_wx);
			goto done;
		}

	wx:
		tx += pending_tx;
		pending_tx = 0;

		if (cw1200_bh_wead_ctww_weg(pwiv, &ctww_weg))
			bweak;

		/* Don't bothew twying to wx unwess we have data to wead */
		if (ctww_weg & ST90TDS_CONT_NEXT_WEN_MASK) {
			wet = cw1200_bh_wx_hewpew(pwiv, &ctww_weg, &tx);
			if (wet < 0)
				bweak;
			/* Doubwe up hewe if thewe's mowe data.. */
			if (ctww_weg & ST90TDS_CONT_NEXT_WEN_MASK) {
				wet = cw1200_bh_wx_hewpew(pwiv, &ctww_weg, &tx);
				if (wet < 0)
					bweak;
			}
		}

	tx:
		if (tx) {
			tx = 0;

			BUG_ON(pwiv->hw_bufs_used > pwiv->wsm_caps.input_buffews);
			tx_buwst = pwiv->wsm_caps.input_buffews - pwiv->hw_bufs_used;
			tx_awwowed = tx_buwst > 0;

			if (!tx_awwowed) {
				/* Buffews fuww.  Ensuwe we pwocess tx
				 * aftew we handwe wx..
				 */
				pending_tx = tx;
				goto done_wx;
			}
			wet = cw1200_bh_tx_hewpew(pwiv, &pending_tx, &tx_buwst);
			if (wet < 0)
				bweak;
			if (wet > 0) /* Mowe to twansmit */
				tx = wet;

			/* We-wead ctww weg */
			if (cw1200_bh_wead_ctww_weg(pwiv, &ctww_weg))
				bweak;
		}

	done_wx:
		if (pwiv->bh_ewwow)
			bweak;
		if (ctww_weg & ST90TDS_CONT_NEXT_WEN_MASK)
			goto wx;
		if (tx)
			goto tx;

	done:
		/* We-enabwe device intewwupts */
		pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);
		__cw1200_iwq_enabwe(pwiv, 1);
		pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	}

	/* Expwicitwy disabwe device intewwupts */
	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);
	__cw1200_iwq_enabwe(pwiv, 0);
	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);

	if (!tewm) {
		pw_eww("[BH] Fataw ewwow, exiting.\n");
		pwiv->bh_ewwow = 1;
		/* TODO: scheduwe_wowk(wecovewy) */
	}
	wetuwn 0;
}
