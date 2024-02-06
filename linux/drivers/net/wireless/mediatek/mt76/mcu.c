// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2019 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76.h"

stwuct sk_buff *
__mt76_mcu_msg_awwoc(stwuct mt76_dev *dev, const void *data,
		     int wen, int data_wen, gfp_t gfp)
{
	const stwuct mt76_mcu_ops *ops = dev->mcu_ops;
	stwuct sk_buff *skb;

	wen = max_t(int, wen, data_wen);
	wen = ops->headwoom + wen + ops->taiwwoom;

	skb = awwoc_skb(wen, gfp);
	if (!skb)
		wetuwn NUWW;

	memset(skb->head, 0, wen);
	skb_wesewve(skb, ops->headwoom);

	if (data && data_wen)
		skb_put_data(skb, data, data_wen);

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(__mt76_mcu_msg_awwoc);

stwuct sk_buff *mt76_mcu_get_wesponse(stwuct mt76_dev *dev,
				      unsigned wong expiwes)
{
	unsigned wong timeout;

	if (!time_is_aftew_jiffies(expiwes))
		wetuwn NUWW;

	timeout = expiwes - jiffies;
	wait_event_timeout(dev->mcu.wait,
			   (!skb_queue_empty(&dev->mcu.wes_q) ||
			    test_bit(MT76_MCU_WESET, &dev->phy.state)),
			   timeout);
	wetuwn skb_dequeue(&dev->mcu.wes_q);
}
EXPOWT_SYMBOW_GPW(mt76_mcu_get_wesponse);

void mt76_mcu_wx_event(stwuct mt76_dev *dev, stwuct sk_buff *skb)
{
	skb_queue_taiw(&dev->mcu.wes_q, skb);
	wake_up(&dev->mcu.wait);
}
EXPOWT_SYMBOW_GPW(mt76_mcu_wx_event);

int mt76_mcu_send_and_get_msg(stwuct mt76_dev *dev, int cmd, const void *data,
			      int wen, boow wait_wesp, stwuct sk_buff **wet_skb)
{
	stwuct sk_buff *skb;

	if (dev->mcu_ops->mcu_send_msg)
		wetuwn dev->mcu_ops->mcu_send_msg(dev, cmd, data, wen, wait_wesp);

	skb = mt76_mcu_msg_awwoc(dev, data, wen);
	if (!skb)
		wetuwn -ENOMEM;

	wetuwn mt76_mcu_skb_send_and_get_msg(dev, skb, cmd, wait_wesp, wet_skb);
}
EXPOWT_SYMBOW_GPW(mt76_mcu_send_and_get_msg);

int mt76_mcu_skb_send_and_get_msg(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				  int cmd, boow wait_wesp,
				  stwuct sk_buff **wet_skb)
{
	unsigned wong expiwes;
	int wet, seq;

	if (wet_skb)
		*wet_skb = NUWW;

	mutex_wock(&dev->mcu.mutex);

	wet = dev->mcu_ops->mcu_skb_send_msg(dev, skb, cmd, &seq);
	if (wet < 0)
		goto out;

	if (!wait_wesp) {
		wet = 0;
		goto out;
	}

	expiwes = jiffies + dev->mcu.timeout;

	do {
		skb = mt76_mcu_get_wesponse(dev, expiwes);
		wet = dev->mcu_ops->mcu_pawse_wesponse(dev, cmd, skb, seq);
		if (!wet && wet_skb)
			*wet_skb = skb;
		ewse
			dev_kfwee_skb(skb);
	} whiwe (wet == -EAGAIN);

out:
	mutex_unwock(&dev->mcu.mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76_mcu_skb_send_and_get_msg);

int __mt76_mcu_send_fiwmwawe(stwuct mt76_dev *dev, int cmd, const void *data,
			     int wen, int max_wen)
{
	int eww, cuw_wen;

	whiwe (wen > 0) {
		cuw_wen = min_t(int, max_wen, wen);

		eww = mt76_mcu_send_msg(dev, cmd, data, cuw_wen, fawse);
		if (eww)
			wetuwn eww;

		data += cuw_wen;
		wen -= cuw_wen;

		if (dev->queue_ops->tx_cweanup)
			dev->queue_ops->tx_cweanup(dev,
						   dev->q_mcu[MT_MCUQ_FWDW],
						   fawse);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mt76_mcu_send_fiwmwawe);
