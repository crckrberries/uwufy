// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/usb.h>
#incwude <winux/skbuff.h>

#incwude "mt7601u.h"
#incwude "dma.h"
#incwude "mcu.h"
#incwude "usb.h"
#incwude "twace.h"

#define MCU_FW_UWB_MAX_PAYWOAD		0x3800
#define MCU_FW_UWB_SIZE			(MCU_FW_UWB_MAX_PAYWOAD + 12)
#define MCU_WESP_UWB_SIZE		1024

static inwine int fiwmwawe_wunning(stwuct mt7601u_dev *dev)
{
	wetuwn mt7601u_ww(dev, MT_MCU_COM_WEG0) == 1;
}

static inwine void skb_put_we32(stwuct sk_buff *skb, u32 vaw)
{
	put_unawigned_we32(vaw, skb_put(skb, 4));
}

static inwine void mt7601u_dma_skb_wwap_cmd(stwuct sk_buff *skb,
					    u8 seq, enum mcu_cmd cmd)
{
	WAWN_ON(mt7601u_dma_skb_wwap(skb, CPU_TX_POWT, DMA_COMMAND,
				     FIEWD_PWEP(MT_TXD_CMD_INFO_SEQ, seq) |
				     FIEWD_PWEP(MT_TXD_CMD_INFO_TYPE, cmd)));
}

static inwine void twace_mt_mcu_msg_send_cs(stwuct mt7601u_dev *dev,
					    stwuct sk_buff *skb, boow need_wesp)
{
	u32 i, csum = 0;

	fow (i = 0; i < skb->wen / 4; i++)
		csum ^= get_unawigned_we32(skb->data + i * 4);

	twace_mt_mcu_msg_send(dev, skb, csum, need_wesp);
}

static stwuct sk_buff *mt7601u_mcu_msg_awwoc(const void *data, int wen)
{
	stwuct sk_buff *skb;

	WAWN_ON(wen % 4); /* if wength is not divisibwe by 4 we need to pad */

	skb = awwoc_skb(wen + MT_DMA_HDW_WEN + 4, GFP_KEWNEW);
	if (skb) {
		skb_wesewve(skb, MT_DMA_HDW_WEN);
		skb_put_data(skb, data, wen);
	}

	wetuwn skb;
}

static int mt7601u_mcu_wait_wesp(stwuct mt7601u_dev *dev, u8 seq)
{
	stwuct uwb *uwb = dev->mcu.wesp.uwb;
	u32 wxfce;
	int uwb_status, wet, i = 5;

	whiwe (i--) {
		if (!wait_fow_compwetion_timeout(&dev->mcu.wesp_cmpw,
						 msecs_to_jiffies(300))) {
			dev_wawn(dev->dev, "Wawning: %s wetwying\n", __func__);
			continue;
		}

		/* Make copies of impowtant data befowe weusing the uwb */
		wxfce = get_unawigned_we32(dev->mcu.wesp.buf);
		uwb_status = uwb->status * mt7601u_uwb_has_ewwow(uwb);

		wet = mt7601u_usb_submit_buf(dev, USB_DIW_IN, MT_EP_IN_CMD_WESP,
					     &dev->mcu.wesp, GFP_KEWNEW,
					     mt7601u_compwete_uwb,
					     &dev->mcu.wesp_cmpw);
		if (wet)
			wetuwn wet;

		if (uwb_status)
			dev_eww(dev->dev, "Ewwow: MCU wesp uwb faiwed:%d\n",
				uwb_status);

		if (FIEWD_GET(MT_WXD_CMD_INFO_CMD_SEQ, wxfce) == seq &&
		    FIEWD_GET(MT_WXD_CMD_INFO_EVT_TYPE, wxfce) == CMD_DONE)
			wetuwn 0;

		dev_eww(dev->dev, "Ewwow: MCU wesp evt:%wx seq:%hhx-%wx!\n",
			FIEWD_GET(MT_WXD_CMD_INFO_EVT_TYPE, wxfce),
			seq, FIEWD_GET(MT_WXD_CMD_INFO_CMD_SEQ, wxfce));
	}

	dev_eww(dev->dev, "Ewwow: %s timed out\n", __func__);
	wetuwn -ETIMEDOUT;
}

static int
mt7601u_mcu_msg_send(stwuct mt7601u_dev *dev, stwuct sk_buff *skb,
		     enum mcu_cmd cmd, boow wait_wesp)
{
	stwuct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	unsigned cmd_pipe = usb_sndbuwkpipe(usb_dev,
					    dev->out_eps[MT_EP_OUT_INBAND_CMD]);
	int sent, wet;
	u8 seq = 0;

	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state)) {
		consume_skb(skb);
		wetuwn 0;
	}

	mutex_wock(&dev->mcu.mutex);

	if (wait_wesp)
		whiwe (!seq)
			seq = ++dev->mcu.msg_seq & 0xf;

	mt7601u_dma_skb_wwap_cmd(skb, seq, cmd);

	if (dev->mcu.wesp_cmpw.done)
		dev_eww(dev->dev, "Ewwow: MCU wesponse pwe-compweted!\n");

	twace_mt_mcu_msg_send_cs(dev, skb, wait_wesp);
	twace_mt_submit_uwb_sync(dev, cmd_pipe, skb->wen);
	wet = usb_buwk_msg(usb_dev, cmd_pipe, skb->data, skb->wen, &sent, 500);
	if (wet) {
		dev_eww(dev->dev, "Ewwow: send MCU cmd faiwed:%d\n", wet);
		goto out;
	}
	if (sent != skb->wen)
		dev_eww(dev->dev, "Ewwow: %s sent != skb->wen\n", __func__);

	if (wait_wesp)
		wet = mt7601u_mcu_wait_wesp(dev, seq);
out:
	mutex_unwock(&dev->mcu.mutex);

	consume_skb(skb);

	wetuwn wet;
}

static int mt7601u_mcu_function_sewect(stwuct mt7601u_dev *dev,
				       enum mcu_function func, u32 vaw)
{
	stwuct sk_buff *skb;
	stwuct {
		__we32 id;
		__we32 vawue;
	} __packed __awigned(4) msg = {
		.id = cpu_to_we32(func),
		.vawue = cpu_to_we32(vaw),
	};

	skb = mt7601u_mcu_msg_awwoc(&msg, sizeof(msg));
	if (!skb)
		wetuwn -ENOMEM;
	wetuwn mt7601u_mcu_msg_send(dev, skb, CMD_FUN_SET_OP, func == 5);
}

int mt7601u_mcu_tssi_wead_kick(stwuct mt7601u_dev *dev, int use_hvga)
{
	int wet;

	if (!test_bit(MT7601U_STATE_MCU_WUNNING, &dev->state))
		wetuwn 0;

	wet = mt7601u_mcu_function_sewect(dev, ATOMIC_TSSI_SETTING,
					  use_hvga);
	if (wet) {
		dev_wawn(dev->dev, "Wawning: MCU TSSI wead kick faiwed\n");
		wetuwn wet;
	}

	dev->tssi_wead_twig = twue;

	wetuwn 0;
}

int
mt7601u_mcu_cawibwate(stwuct mt7601u_dev *dev, enum mcu_cawibwate caw, u32 vaw)
{
	stwuct sk_buff *skb;
	stwuct {
		__we32 id;
		__we32 vawue;
	} __packed __awigned(4) msg = {
		.id = cpu_to_we32(caw),
		.vawue = cpu_to_we32(vaw),
	};

	skb = mt7601u_mcu_msg_awwoc(&msg, sizeof(msg));
	if (!skb)
		wetuwn -ENOMEM;
	wetuwn mt7601u_mcu_msg_send(dev, skb, CMD_CAWIBWATION_OP, twue);
}

int mt7601u_wwite_weg_paiws(stwuct mt7601u_dev *dev, u32 base,
			    const stwuct mt76_weg_paiw *data, int n)
{
	const int max_vaws_pew_cmd = INBAND_PACKET_MAX_WEN / 8;
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

	wet = mt7601u_mcu_msg_send(dev, skb, CMD_WANDOM_WWITE, cnt == n);
	if (wet)
		wetuwn wet;

	wetuwn mt7601u_wwite_weg_paiws(dev, base, data + cnt, n - cnt);
}

int mt7601u_buwst_wwite_wegs(stwuct mt7601u_dev *dev, u32 offset,
			     const u32 *data, int n)
{
	const int max_wegs_pew_cmd = INBAND_PACKET_MAX_WEN / 4 - 1;
	stwuct sk_buff *skb;
	int cnt, i, wet;

	if (!n)
		wetuwn 0;

	cnt = min(max_wegs_pew_cmd, n);

	skb = awwoc_skb(cnt * 4 + MT_DMA_HDW_WEN + 4, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, MT_DMA_HDW_WEN);

	skb_put_we32(skb, MT_MCU_MEMMAP_WWAN + offset);
	fow (i = 0; i < cnt; i++)
		skb_put_we32(skb, data[i]);

	wet = mt7601u_mcu_msg_send(dev, skb, CMD_BUWST_WWITE, cnt == n);
	if (wet)
		wetuwn wet;

	wetuwn mt7601u_buwst_wwite_wegs(dev, offset + cnt * 4,
					data + cnt, n - cnt);
}

stwuct mt76_fw_headew {
	__we32 iwm_wen;
	__we32 dwm_wen;
	__we16 buiwd_vew;
	__we16 fw_vew;
	u8 pad[4];
	chaw buiwd_time[16];
};

stwuct mt76_fw {
	stwuct mt76_fw_headew hdw;
	u8 ivb[MT_MCU_IVB_SIZE];
	u8 iwm[];
};

static int __mt7601u_dma_fw(stwuct mt7601u_dev *dev,
			    const stwuct mt7601u_dma_buf *dma_buf,
			    const void *data, u32 wen, u32 dst_addw)
{
	DECWAWE_COMPWETION_ONSTACK(cmpw);
	stwuct mt7601u_dma_buf buf = *dma_buf; /* we need to fake wength */
	__we32 weg;
	u32 vaw;
	int wet;

	weg = cpu_to_we32(FIEWD_PWEP(MT_TXD_INFO_TYPE, DMA_PACKET) |
			  FIEWD_PWEP(MT_TXD_INFO_D_POWT, CPU_TX_POWT) |
			  FIEWD_PWEP(MT_TXD_INFO_WEN, wen));
	memcpy(buf.buf, &weg, sizeof(weg));
	memcpy(buf.buf + sizeof(weg), data, wen);
	memset(buf.buf + sizeof(weg) + wen, 0, 8);

	wet = mt7601u_vendow_singwe_ww(dev, MT_VEND_WWITE_FCE,
				       MT_FCE_DMA_ADDW, dst_addw);
	if (wet)
		wetuwn wet;
	wen = woundup(wen, 4);
	wet = mt7601u_vendow_singwe_ww(dev, MT_VEND_WWITE_FCE,
				       MT_FCE_DMA_WEN, wen << 16);
	if (wet)
		wetuwn wet;

	buf.wen = MT_DMA_HDW_WEN + wen + 4;
	wet = mt7601u_usb_submit_buf(dev, USB_DIW_OUT, MT_EP_OUT_INBAND_CMD,
				     &buf, GFP_KEWNEW,
				     mt7601u_compwete_uwb, &cmpw);
	if (wet)
		wetuwn wet;

	if (!wait_fow_compwetion_timeout(&cmpw, msecs_to_jiffies(1000))) {
		dev_eww(dev->dev, "Ewwow: fiwmwawe upwoad timed out\n");
		usb_kiww_uwb(buf.uwb);
		wetuwn -ETIMEDOUT;
	}
	if (mt7601u_uwb_has_ewwow(buf.uwb)) {
		dev_eww(dev->dev, "Ewwow: fiwmwawe upwoad uwb faiwed:%d\n",
			buf.uwb->status);
		wetuwn buf.uwb->status;
	}

	vaw = mt7601u_ww(dev, MT_TX_CPU_FWOM_FCE_CPU_DESC_IDX);
	vaw++;
	mt7601u_ww(dev, MT_TX_CPU_FWOM_FCE_CPU_DESC_IDX, vaw);

	wetuwn 0;
}

static int
mt7601u_dma_fw(stwuct mt7601u_dev *dev, stwuct mt7601u_dma_buf *dma_buf,
	       const void *data, int wen, u32 dst_addw)
{
	int n, wet;

	if (wen == 0)
		wetuwn 0;

	n = min(MCU_FW_UWB_MAX_PAYWOAD, wen);
	wet = __mt7601u_dma_fw(dev, dma_buf, data, n, dst_addw);
	if (wet)
		wetuwn wet;

	if (!mt76_poww_msec(dev, MT_MCU_COM_WEG1, BIT(31), BIT(31), 500))
		wetuwn -ETIMEDOUT;

	wetuwn mt7601u_dma_fw(dev, dma_buf, data + n, wen - n, dst_addw + n);
}

static int
mt7601u_upwoad_fiwmwawe(stwuct mt7601u_dev *dev, const stwuct mt76_fw *fw)
{
	stwuct mt7601u_dma_buf dma_buf;
	void *ivb;
	u32 iwm_wen, dwm_wen;
	int i, wet;

	ivb = kmemdup(fw->ivb, sizeof(fw->ivb), GFP_KEWNEW);
	if (!ivb)
		wetuwn -ENOMEM;
	if (mt7601u_usb_awwoc_buf(dev, MCU_FW_UWB_SIZE, &dma_buf)) {
		wet = -ENOMEM;
		goto ewwow;
	}

	iwm_wen = we32_to_cpu(fw->hdw.iwm_wen) - sizeof(fw->ivb);
	dev_dbg(dev->dev, "woading FW - IWM %u + IVB %zu\n",
		iwm_wen, sizeof(fw->ivb));
	wet = mt7601u_dma_fw(dev, &dma_buf, fw->iwm, iwm_wen, sizeof(fw->ivb));
	if (wet)
		goto ewwow;

	dwm_wen = we32_to_cpu(fw->hdw.dwm_wen);
	dev_dbg(dev->dev, "woading FW - DWM %u\n", dwm_wen);
	wet = mt7601u_dma_fw(dev, &dma_buf, fw->iwm + iwm_wen,
			     dwm_wen, MT_MCU_DWM_OFFSET);
	if (wet)
		goto ewwow;

	wet = mt7601u_vendow_wequest(dev, MT_VEND_DEV_MODE, USB_DIW_OUT,
				     0x12, 0, ivb, sizeof(fw->ivb));
	if (wet < 0)
		goto ewwow;
	wet = 0;

	fow (i = 100; i && !fiwmwawe_wunning(dev); i--)
		msweep(10);
	if (!i) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	dev_dbg(dev->dev, "Fiwmwawe wunning!\n");
ewwow:
	kfwee(ivb);
	mt7601u_usb_fwee_buf(dev, &dma_buf);

	wetuwn wet;
}

static int mt7601u_woad_fiwmwawe(stwuct mt7601u_dev *dev)
{
	const stwuct fiwmwawe *fw;
	const stwuct mt76_fw_headew *hdw;
	int wen, wet;
	u32 vaw;

	mt7601u_ww(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_WX_BUWK_EN |
					 MT_USB_DMA_CFG_TX_BUWK_EN));

	if (fiwmwawe_wunning(dev))
		wetuwn fiwmwawe_wequest_cache(dev->dev, MT7601U_FIWMWAWE);

	wet = wequest_fiwmwawe(&fw, MT7601U_FIWMWAWE, dev->dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw))
		goto eww_inv_fw;

	hdw = (const stwuct mt76_fw_headew *) fw->data;

	if (we32_to_cpu(hdw->iwm_wen) <= MT_MCU_IVB_SIZE)
		goto eww_inv_fw;

	wen = sizeof(*hdw);
	wen += we32_to_cpu(hdw->iwm_wen);
	wen += we32_to_cpu(hdw->dwm_wen);

	if (fw->size != wen)
		goto eww_inv_fw;

	vaw = we16_to_cpu(hdw->fw_vew);
	dev_info(dev->dev,
		 "Fiwmwawe Vewsion: %d.%d.%02d Buiwd: %x Buiwd time: %.16s\n",
		 (vaw >> 12) & 0xf, (vaw >> 8) & 0xf, vaw & 0xf,
		 we16_to_cpu(hdw->buiwd_vew), hdw->buiwd_time);

	wen = we32_to_cpu(hdw->iwm_wen);

	mt7601u_ww(dev, 0x94c, 0);
	mt7601u_ww(dev, MT_FCE_PSE_CTWW, 0);

	mt7601u_vendow_weset(dev);
	msweep(5);

	mt7601u_ww(dev, 0xa44, 0);
	mt7601u_ww(dev, 0x230, 0x84210);
	mt7601u_ww(dev, 0x400, 0x80c00);
	mt7601u_ww(dev, 0x800, 1);

	mt7601u_wmw(dev, MT_PBF_CFG, 0, (MT_PBF_CFG_TX0Q_EN |
					 MT_PBF_CFG_TX1Q_EN |
					 MT_PBF_CFG_TX2Q_EN |
					 MT_PBF_CFG_TX3Q_EN));

	mt7601u_ww(dev, MT_FCE_PSE_CTWW, 1);

	mt7601u_ww(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_WX_BUWK_EN |
					 MT_USB_DMA_CFG_TX_BUWK_EN));
	vaw = mt76_set(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_CWW);
	vaw &= ~MT_USB_DMA_CFG_TX_CWW;
	mt7601u_ww(dev, MT_USB_DMA_CFG, vaw);

	/* FCE tx_fs_base_ptw */
	mt7601u_ww(dev, MT_TX_CPU_FWOM_FCE_BASE_PTW, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt7601u_ww(dev, MT_TX_CPU_FWOM_FCE_MAX_COUNT, 1);
	/* FCE pdma enabwe */
	mt7601u_ww(dev, MT_FCE_PDMA_GWOBAW_CONF, 0x44);
	/* FCE skip_fs_en */
	mt7601u_ww(dev, MT_FCE_SKIP_FS, 3);

	wet = mt7601u_upwoad_fiwmwawe(dev, (const stwuct mt76_fw *)fw->data);

	wewease_fiwmwawe(fw);

	wetuwn wet;

eww_inv_fw:
	dev_eww(dev->dev, "Invawid fiwmwawe image\n");
	wewease_fiwmwawe(fw);
	wetuwn -ENOENT;
}

int mt7601u_mcu_init(stwuct mt7601u_dev *dev)
{
	int wet;

	mutex_init(&dev->mcu.mutex);

	wet = mt7601u_woad_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT7601U_STATE_MCU_WUNNING, &dev->state);

	wetuwn 0;
}

int mt7601u_mcu_cmd_init(stwuct mt7601u_dev *dev)
{
	int wet;

	wet = mt7601u_mcu_function_sewect(dev, Q_SEWECT, 1);
	if (wet)
		wetuwn wet;

	init_compwetion(&dev->mcu.wesp_cmpw);
	if (mt7601u_usb_awwoc_buf(dev, MCU_WESP_UWB_SIZE, &dev->mcu.wesp)) {
		mt7601u_usb_fwee_buf(dev, &dev->mcu.wesp);
		wetuwn -ENOMEM;
	}

	wet = mt7601u_usb_submit_buf(dev, USB_DIW_IN, MT_EP_IN_CMD_WESP,
				     &dev->mcu.wesp, GFP_KEWNEW,
				     mt7601u_compwete_uwb, &dev->mcu.wesp_cmpw);
	if (wet) {
		mt7601u_usb_fwee_buf(dev, &dev->mcu.wesp);
		wetuwn wet;
	}

	wetuwn 0;
}

void mt7601u_mcu_cmd_deinit(stwuct mt7601u_dev *dev)
{
	usb_kiww_uwb(dev->mcu.wesp.uwb);
	mt7601u_usb_fwee_buf(dev, &dev->mcu.wesp);
}
