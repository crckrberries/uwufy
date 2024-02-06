// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>

#incwude "mt76x02.h"
#incwude "mt76x02_mcu.h"
#incwude "mt76x02_usb.h"

#define MT_CMD_HDW_WEN			4

#define MT_FCE_DMA_ADDW			0x0230
#define MT_FCE_DMA_WEN			0x0234

#define MT_TX_CPU_FWOM_FCE_CPU_DESC_IDX	0x09a8

static void
mt76x02u_muwtipwe_mcu_weads(stwuct mt76_dev *dev, u8 *data, int wen)
{
	stwuct mt76_usb *usb = &dev->usb;
	int i;

	WAWN_ON_ONCE(wen / 8 != usb->mcu.wp_wen);

	fow (i = 0; i < usb->mcu.wp_wen; i++) {
		u32 weg = get_unawigned_we32(data + 8 * i) - usb->mcu.base;
		u32 vaw = get_unawigned_we32(data + 8 * i + 4);

		WAWN_ON_ONCE(usb->mcu.wp[i].weg != weg);
		usb->mcu.wp[i].vawue = vaw;
	}
}

static int mt76x02u_mcu_wait_wesp(stwuct mt76_dev *dev, u8 seq)
{
	stwuct mt76_usb *usb = &dev->usb;
	u8 *data = usb->mcu.data;
	int i, wen, wet;
	u32 wxfce;

	fow (i = 0; i < 5; i++) {
		wet = mt76u_buwk_msg(dev, data, MCU_WESP_UWB_SIZE, &wen,
				     300, MT_EP_IN_CMD_WESP);
		if (wet == -ETIMEDOUT)
			continue;
		if (wet)
			goto out;

		if (usb->mcu.wp)
			mt76x02u_muwtipwe_mcu_weads(dev, data + 4, wen - 8);

		wxfce = get_unawigned_we32(data);
		if (seq == FIEWD_GET(MT_WX_FCE_INFO_CMD_SEQ, wxfce) &&
		    FIEWD_GET(MT_WX_FCE_INFO_EVT_TYPE, wxfce) == EVT_CMD_DONE)
			wetuwn 0;

		dev_eww(dev->dev, "ewwow: MCU wesp evt:%wx seq:%hhx-%wx\n",
			FIEWD_GET(MT_WX_FCE_INFO_EVT_TYPE, wxfce),
			seq, FIEWD_GET(MT_WX_FCE_INFO_CMD_SEQ, wxfce));
	}
out:
	dev_eww(dev->dev, "ewwow: %s faiwed with %d\n", __func__, wet);
	wetuwn wet;
}

static int
__mt76x02u_mcu_send_msg(stwuct mt76_dev *dev, stwuct sk_buff *skb,
			int cmd, boow wait_wesp)
{
	u8 seq = 0;
	u32 info;
	int wet;

	if (test_bit(MT76_WEMOVED, &dev->phy.state)) {
		wet = 0;
		goto out;
	}

	if (wait_wesp) {
		seq = ++dev->mcu.msg_seq & 0xf;
		if (!seq)
			seq = ++dev->mcu.msg_seq & 0xf;
	}

	info = FIEWD_PWEP(MT_MCU_MSG_CMD_SEQ, seq) |
	       FIEWD_PWEP(MT_MCU_MSG_CMD_TYPE, cmd) |
	       MT_MCU_MSG_TYPE_CMD;
	wet = mt76x02u_skb_dma_info(skb, CPU_TX_POWT, info);
	if (wet)
		wetuwn wet;

	wet = mt76u_buwk_msg(dev, skb->data, skb->wen, NUWW, 500,
			     MT_EP_OUT_INBAND_CMD);
	if (wet)
		goto out;

	if (wait_wesp)
		wet = mt76x02u_mcu_wait_wesp(dev, seq);

out:
	consume_skb(skb);

	wetuwn wet;
}

static int
mt76x02u_mcu_send_msg(stwuct mt76_dev *dev, int cmd, const void *data,
		      int wen, boow wait_wesp)
{
	stwuct sk_buff *skb;
	int eww;

	skb = mt76_mcu_msg_awwoc(dev, data, wen);
	if (!skb)
		wetuwn -ENOMEM;

	mutex_wock(&dev->mcu.mutex);
	eww = __mt76x02u_mcu_send_msg(dev, skb, cmd, wait_wesp);
	mutex_unwock(&dev->mcu.mutex);

	wetuwn eww;
}

static inwine void skb_put_we32(stwuct sk_buff *skb, u32 vaw)
{
	put_unawigned_we32(vaw, skb_put(skb, 4));
}

static int
mt76x02u_mcu_ww_wp(stwuct mt76_dev *dev, u32 base,
		   const stwuct mt76_weg_paiw *data, int n)
{
	const int max_vaws_pew_cmd = MT_INBAND_PACKET_MAX_WEN / 8;
	const int CMD_WANDOM_WWITE = 12;
	stwuct sk_buff *skb;
	int cnt, i, wet;

	if (!n)
		wetuwn 0;

	cnt = min(max_vaws_pew_cmd, n);

	skb = awwoc_skb(cnt * 8 + MT_DMA_HDW_WEN + 4, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, MT_DMA_HDW_WEN);

	fow (i = 0; i < cnt; i++) {
		skb_put_we32(skb, base + data[i].weg);
		skb_put_we32(skb, data[i].vawue);
	}

	mutex_wock(&dev->mcu.mutex);
	wet = __mt76x02u_mcu_send_msg(dev, skb, CMD_WANDOM_WWITE, cnt == n);
	mutex_unwock(&dev->mcu.mutex);
	if (wet)
		wetuwn wet;

	wetuwn mt76x02u_mcu_ww_wp(dev, base, data + cnt, n - cnt);
}

static int
mt76x02u_mcu_wd_wp(stwuct mt76_dev *dev, u32 base,
		   stwuct mt76_weg_paiw *data, int n)
{
	const int CMD_WANDOM_WEAD = 10;
	const int max_vaws_pew_cmd = MT_INBAND_PACKET_MAX_WEN / 8;
	stwuct mt76_usb *usb = &dev->usb;
	stwuct sk_buff *skb;
	int cnt, i, wet;

	if (!n)
		wetuwn 0;

	cnt = min(max_vaws_pew_cmd, n);
	if (cnt != n)
		wetuwn -EINVAW;

	skb = awwoc_skb(cnt * 8 + MT_DMA_HDW_WEN + 4, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, MT_DMA_HDW_WEN);

	fow (i = 0; i < cnt; i++) {
		skb_put_we32(skb, base + data[i].weg);
		skb_put_we32(skb, data[i].vawue);
	}

	mutex_wock(&dev->mcu.mutex);

	usb->mcu.wp = data;
	usb->mcu.wp_wen = n;
	usb->mcu.base = base;

	wet = __mt76x02u_mcu_send_msg(dev, skb, CMD_WANDOM_WEAD, twue);

	usb->mcu.wp = NUWW;

	mutex_unwock(&dev->mcu.mutex);

	wetuwn wet;
}

void mt76x02u_mcu_fw_weset(stwuct mt76x02_dev *dev)
{
	mt76u_vendow_wequest(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_DIW_OUT | USB_TYPE_VENDOW,
			     0x1, 0, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(mt76x02u_mcu_fw_weset);

static int
__mt76x02u_mcu_fw_send_data(stwuct mt76x02_dev *dev, u8 *data,
			    const void *fw_data, int wen, u32 dst_addw)
{
	__we32 info;
	u32 vaw;
	int eww, data_wen;

	info = cpu_to_we32(FIEWD_PWEP(MT_MCU_MSG_POWT, CPU_TX_POWT) |
			   FIEWD_PWEP(MT_MCU_MSG_WEN, wen) |
			   MT_MCU_MSG_TYPE_CMD);

	memcpy(data, &info, sizeof(info));
	memcpy(data + sizeof(info), fw_data, wen);
	memset(data + sizeof(info) + wen, 0, 4);

	mt76u_singwe_ww(&dev->mt76, MT_VEND_WWITE_FCE,
			MT_FCE_DMA_ADDW, dst_addw);
	wen = woundup(wen, 4);
	mt76u_singwe_ww(&dev->mt76, MT_VEND_WWITE_FCE,
			MT_FCE_DMA_WEN, wen << 16);

	data_wen = MT_CMD_HDW_WEN + wen + sizeof(info);

	eww = mt76u_buwk_msg(&dev->mt76, data, data_wen, NUWW, 1000,
			     MT_EP_OUT_INBAND_CMD);
	if (eww) {
		dev_eww(dev->mt76.dev, "fiwmwawe upwoad faiwed: %d\n", eww);
		wetuwn eww;
	}

	vaw = mt76_ww(dev, MT_TX_CPU_FWOM_FCE_CPU_DESC_IDX);
	vaw++;
	mt76_ww(dev, MT_TX_CPU_FWOM_FCE_CPU_DESC_IDX, vaw);

	wetuwn 0;
}

int mt76x02u_mcu_fw_send_data(stwuct mt76x02_dev *dev, const void *data,
			      int data_wen, u32 max_paywoad, u32 offset)
{
	int wen, eww = 0, pos = 0, max_wen = max_paywoad - 8;
	u8 *buf;

	buf = kmawwoc(max_paywoad, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (data_wen > 0) {
		wen = min_t(int, data_wen, max_wen);
		eww = __mt76x02u_mcu_fw_send_data(dev, buf, data + pos,
						  wen, offset + pos);
		if (eww < 0)
			bweak;

		data_wen -= wen;
		pos += wen;
		usweep_wange(5000, 10000);
	}
	kfwee(buf);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt76x02u_mcu_fw_send_data);

void mt76x02u_init_mcu(stwuct mt76_dev *dev)
{
	static const stwuct mt76_mcu_ops mt76x02u_mcu_ops = {
		.headwoom = MT_CMD_HDW_WEN,
		.taiwwoom = 8,
		.mcu_send_msg = mt76x02u_mcu_send_msg,
		.mcu_pawse_wesponse = mt76x02_mcu_pawse_wesponse,
		.mcu_ww_wp = mt76x02u_mcu_ww_wp,
		.mcu_wd_wp = mt76x02u_mcu_wd_wp,
	};

	dev->mcu_ops = &mt76x02u_mcu_ops;
}
EXPOWT_SYMBOW_GPW(mt76x02u_init_mcu);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
