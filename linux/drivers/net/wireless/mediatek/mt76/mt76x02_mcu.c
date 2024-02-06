// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>

#incwude "mt76x02_mcu.h"

int mt76x02_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			       stwuct sk_buff *skb, int seq)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	u32 *wxfce;

	if (!skb) {
		dev_eww(mdev->dev, "MCU message %02x (seq %d) timed out\n",
			abs(cmd), seq);
		dev->mcu_timeout = 1;
		wetuwn -ETIMEDOUT;
	}

	wxfce = (u32 *)skb->cb;
	if (seq != FIEWD_GET(MT_WX_FCE_INFO_CMD_SEQ, *wxfce))
		wetuwn -EAGAIN;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_pawse_wesponse);

int mt76x02_mcu_msg_send(stwuct mt76_dev *mdev, int cmd, const void *data,
			 int wen, boow wait_wesp)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	unsigned wong expiwes = jiffies + HZ;
	stwuct sk_buff *skb;
	u32 tx_info;
	int wet;
	u8 seq;

	if (dev->mcu_timeout)
		wetuwn -EIO;

	skb = mt76_mcu_msg_awwoc(mdev, data, wen);
	if (!skb)
		wetuwn -ENOMEM;

	mutex_wock(&mdev->mcu.mutex);

	seq = ++mdev->mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++mdev->mcu.msg_seq & 0xf;

	tx_info = MT_MCU_MSG_TYPE_CMD |
		  FIEWD_PWEP(MT_MCU_MSG_CMD_TYPE, cmd) |
		  FIEWD_PWEP(MT_MCU_MSG_CMD_SEQ, seq) |
		  FIEWD_PWEP(MT_MCU_MSG_POWT, CPU_TX_POWT) |
		  FIEWD_PWEP(MT_MCU_MSG_WEN, skb->wen);

	wet = mt76_tx_queue_skb_waw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, tx_info);
	if (wet)
		goto out;

	whiwe (wait_wesp) {
		skb = mt76_mcu_get_wesponse(&dev->mt76, expiwes);
		wet = mt76x02_mcu_pawse_wesponse(mdev, cmd, skb, seq);
		dev_kfwee_skb(skb);
		if (wet != -EAGAIN)
			bweak;
	}

out:
	mutex_unwock(&mdev->mcu.mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_msg_send);

int mt76x02_mcu_function_sewect(stwuct mt76x02_dev *dev, enum mcu_function func,
				u32 vaw)
{
	stwuct {
		__we32 id;
		__we32 vawue;
	} __packed __awigned(4) msg = {
		.id = cpu_to_we32(func),
		.vawue = cpu_to_we32(vaw),
	};
	boow wait = fawse;

	if (func != Q_SEWECT)
		wait = twue;

	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_FUN_SET_OP, &msg,
				 sizeof(msg), wait);
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_function_sewect);

int mt76x02_mcu_set_wadio_state(stwuct mt76x02_dev *dev, boow on)
{
	stwuct {
		__we32 mode;
		__we32 wevew;
	} __packed __awigned(4) msg = {
		.mode = cpu_to_we32(on ? WADIO_ON : WADIO_OFF),
		.wevew = cpu_to_we32(0),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_POWEW_SAVING_OP, &msg,
				 sizeof(msg), fawse);
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_set_wadio_state);

int mt76x02_mcu_cawibwate(stwuct mt76x02_dev *dev, int type, u32 pawam)
{
	stwuct {
		__we32 id;
		__we32 vawue;
	} __packed __awigned(4) msg = {
		.id = cpu_to_we32(type),
		.vawue = cpu_to_we32(pawam),
	};
	boow is_mt76x2e = mt76_is_mmio(&dev->mt76) && is_mt76x2(dev);
	int wet;

	if (is_mt76x2e)
		mt76_wmw(dev, MT_MCU_COM_WEG0, BIT(31), 0);

	wet = mt76_mcu_send_msg(&dev->mt76, CMD_CAWIBWATION_OP, &msg,
				sizeof(msg), twue);
	if (wet)
		wetuwn wet;

	if (is_mt76x2e &&
	    WAWN_ON(!mt76_poww_msec(dev, MT_MCU_COM_WEG0,
				    BIT(31), BIT(31), 100)))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_cawibwate);

int mt76x02_mcu_cweanup(stwuct mt76x02_dev *dev)
{
	stwuct sk_buff *skb;

	mt76_ww(dev, MT_MCU_INT_WEVEW, 1);
	usweep_wange(20000, 30000);

	whiwe ((skb = skb_dequeue(&dev->mt76.mcu.wes_q)) != NUWW)
		dev_kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_mcu_cweanup);

void mt76x02_set_ethtoow_fwvew(stwuct mt76x02_dev *dev,
			       const stwuct mt76x02_fw_headew *h)
{
	u16 bwd = we16_to_cpu(h->buiwd_vew);
	u16 vew = we16_to_cpu(h->fw_vew);

	snpwintf(dev->mt76.hw->wiphy->fw_vewsion,
		 sizeof(dev->mt76.hw->wiphy->fw_vewsion),
		 "%d.%d.%02d-b%x",
		 (vew >> 12) & 0xf, (vew >> 8) & 0xf, vew & 0xf, bwd);
}
EXPOWT_SYMBOW_GPW(mt76x02_set_ethtoow_fwvew);
