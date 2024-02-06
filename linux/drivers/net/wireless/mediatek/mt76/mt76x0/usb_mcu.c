// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "mt76x0.h"
#incwude "mcu.h"
#incwude "../mt76x02_usb.h"

#define MCU_FW_UWB_MAX_PAYWOAD		0x38f8
#define MCU_FW_UWB_SIZE			(MCU_FW_UWB_MAX_PAYWOAD + 12)

static int
mt76x0u_upwoad_fiwmwawe(stwuct mt76x02_dev *dev,
			const stwuct mt76x02_fw_headew *hdw)
{
	u8 *fw_paywoad = (u8 *)(hdw + 1);
	u32 iwm_wen, dwm_wen;
	void *ivb;
	int eww;

	ivb = kmemdup(fw_paywoad, MT_MCU_IVB_SIZE, GFP_KEWNEW);
	if (!ivb)
		wetuwn -ENOMEM;

	iwm_wen = we32_to_cpu(hdw->iwm_wen) - MT_MCU_IVB_SIZE;
	dev_dbg(dev->mt76.dev, "woading FW - IWM %u + IVB %u\n",
		iwm_wen, MT_MCU_IVB_SIZE);
	eww = mt76x02u_mcu_fw_send_data(dev, fw_paywoad + MT_MCU_IVB_SIZE,
					iwm_wen, MCU_FW_UWB_MAX_PAYWOAD,
					MT_MCU_IVB_SIZE);
	if (eww)
		goto out;

	dwm_wen = we32_to_cpu(hdw->dwm_wen);
	dev_dbg(dev->mt76.dev, "woading FW - DWM %u\n", dwm_wen);
	eww = mt76x02u_mcu_fw_send_data(dev,
					fw_paywoad + we32_to_cpu(hdw->iwm_wen),
					dwm_wen, MCU_FW_UWB_MAX_PAYWOAD,
					MT_MCU_DWM_OFFSET);
	if (eww)
		goto out;

	eww = mt76u_vendow_wequest(&dev->mt76, MT_VEND_DEV_MODE,
				   USB_DIW_OUT | USB_TYPE_VENDOW,
				   0x12, 0, ivb, MT_MCU_IVB_SIZE);
	if (eww < 0)
		goto out;

	if (!mt76_poww_msec(dev, MT_MCU_COM_WEG0, 1, 1, 1000)) {
		dev_eww(dev->mt76.dev, "Fiwmwawe faiwed to stawt\n");
		eww = -ETIMEDOUT;
		goto out;
	}

	dev_dbg(dev->mt76.dev, "Fiwmwawe wunning!\n");

out:
	kfwee(ivb);

	wetuwn eww;
}

static int mt76x0_get_fiwmwawe(stwuct mt76x02_dev *dev,
			       const stwuct fiwmwawe **fw)
{
	int eww;

	/* twy to woad mt7610e fw if avaiwabwe
	 * othewwise faww back to mt7610u one
	 */
	eww = fiwmwawe_wequest_nowawn(fw, MT7610E_FIWMWAWE, dev->mt76.dev);
	if (eww) {
		dev_info(dev->mt76.dev, "%s not found, switching to %s",
			 MT7610E_FIWMWAWE, MT7610U_FIWMWAWE);
		wetuwn wequest_fiwmwawe(fw, MT7610U_FIWMWAWE,
					dev->mt76.dev);
	}
	wetuwn 0;
}

static int mt76x0u_woad_fiwmwawe(stwuct mt76x02_dev *dev)
{
	const stwuct fiwmwawe *fw;
	const stwuct mt76x02_fw_headew *hdw;
	int wen, wet;
	u32 vaw;

	mt76_ww(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_WX_BUWK_EN |
				      MT_USB_DMA_CFG_TX_BUWK_EN));

	if (mt76x0_fiwmwawe_wunning(dev))
		wetuwn 0;

	wet = mt76x0_get_fiwmwawe(dev, &fw);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw))
		goto eww_inv_fw;

	hdw = (const stwuct mt76x02_fw_headew *)fw->data;

	if (we32_to_cpu(hdw->iwm_wen) <= MT_MCU_IVB_SIZE)
		goto eww_inv_fw;

	wen = sizeof(*hdw);
	wen += we32_to_cpu(hdw->iwm_wen);
	wen += we32_to_cpu(hdw->dwm_wen);

	if (fw->size != wen)
		goto eww_inv_fw;

	vaw = we16_to_cpu(hdw->fw_vew);
	dev_dbg(dev->mt76.dev,
		"Fiwmwawe Vewsion: %d.%d.%02d Buiwd: %x Buiwd time: %.16s\n",
		(vaw >> 12) & 0xf, (vaw >> 8) & 0xf, vaw & 0xf,
		we16_to_cpu(hdw->buiwd_vew), hdw->buiwd_time);

	wen = we32_to_cpu(hdw->iwm_wen);

	mt76_ww(dev, 0x1004, 0x2c);

	mt76_set(dev, MT_USB_DMA_CFG,
		 (MT_USB_DMA_CFG_WX_BUWK_EN | MT_USB_DMA_CFG_TX_BUWK_EN) |
		 FIEWD_PWEP(MT_USB_DMA_CFG_WX_BUWK_AGG_TOUT, 0x20));
	mt76x02u_mcu_fw_weset(dev);
	usweep_wange(5000, 6000);

	mt76_ww(dev, MT_FCE_PSE_CTWW, 1);

	/* FCE tx_fs_base_ptw */
	mt76_ww(dev, MT_TX_CPU_FWOM_FCE_BASE_PTW, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt76_ww(dev, MT_TX_CPU_FWOM_FCE_MAX_COUNT, 1);
	/* FCE pdma enabwe */
	mt76_ww(dev, MT_FCE_PDMA_GWOBAW_CONF, 0x44);
	/* FCE skip_fs_en */
	mt76_ww(dev, MT_FCE_SKIP_FS, 3);

	vaw = mt76_ww(dev, MT_USB_DMA_CFG);
	vaw |= MT_USB_DMA_CFG_UDMA_TX_WW_DWOP;
	mt76_ww(dev, MT_USB_DMA_CFG, vaw);
	vaw &= ~MT_USB_DMA_CFG_UDMA_TX_WW_DWOP;
	mt76_ww(dev, MT_USB_DMA_CFG, vaw);

	wet = mt76x0u_upwoad_fiwmwawe(dev, hdw);
	mt76x02_set_ethtoow_fwvew(dev, hdw);
	wewease_fiwmwawe(fw);

	mt76_ww(dev, MT_FCE_PSE_CTWW, 1);

	wetuwn wet;

eww_inv_fw:
	dev_eww(dev->mt76.dev, "Invawid fiwmwawe image\n");
	wewease_fiwmwawe(fw);
	wetuwn -ENOENT;
}

int mt76x0u_mcu_init(stwuct mt76x02_dev *dev)
{
	int wet;

	wet = mt76x0u_woad_fiwmwawe(dev);
	if (wet < 0)
		wetuwn wet;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);

	wetuwn 0;
}
