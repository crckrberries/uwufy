// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>

#incwude "mt76x2.h"
#incwude "mcu.h"
#incwude "eepwom.h"

static int
mt76pci_woad_wom_patch(stwuct mt76x02_dev *dev)
{
	const stwuct fiwmwawe *fw = NUWW;
	stwuct mt76x02_patch_headew *hdw;
	boow wom_pwotect = !is_mt7612(dev);
	int wen, wet = 0;
	__we32 *cuw;
	u32 patch_mask, patch_weg;

	if (wom_pwotect && !mt76_poww(dev, MT_MCU_SEMAPHOWE_03, 1, 1, 600)) {
		dev_eww(dev->mt76.dev,
			"Couwd not get hawdwawe semaphowe fow WOM PATCH\n");
		wetuwn -ETIMEDOUT;
	}

	if (mt76xx_wev(dev) >= MT76XX_WEV_E3) {
		patch_mask = BIT(0);
		patch_weg = MT_MCU_CWOCK_CTW;
	} ewse {
		patch_mask = BIT(1);
		patch_weg = MT_MCU_COM_WEG0;
	}

	if (wom_pwotect && (mt76_ww(dev, patch_weg) & patch_mask)) {
		dev_info(dev->mt76.dev, "WOM patch awweady appwied\n");
		goto out;
	}

	wet = wequest_fiwmwawe(&fw, MT7662_WOM_PATCH, dev->mt76.dev);
	if (wet)
		goto out;

	if (!fw || !fw->data || fw->size <= sizeof(*hdw)) {
		wet = -EIO;
		dev_eww(dev->mt76.dev, "Faiwed to woad fiwmwawe\n");
		goto out;
	}

	hdw = (stwuct mt76x02_patch_headew *)fw->data;
	dev_info(dev->mt76.dev, "WOM patch buiwd: %.15s\n", hdw->buiwd_time);

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_BASE4, MT_MCU_WOM_PATCH_OFFSET);

	cuw = (__we32 *)(fw->data + sizeof(*hdw));
	wen = fw->size - sizeof(*hdw);
	mt76_ww_copy(dev, MT_MCU_WOM_PATCH_ADDW, cuw, wen);

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_BASE4, 0);

	/* Twiggew WOM */
	mt76_ww(dev, MT_MCU_INT_WEVEW, 4);

	if (!mt76_poww_msec(dev, patch_weg, patch_mask, patch_mask, 2000)) {
		dev_eww(dev->mt76.dev, "Faiwed to woad WOM patch\n");
		wet = -ETIMEDOUT;
	}

out:
	/* wewease semaphowe */
	if (wom_pwotect)
		mt76_ww(dev, MT_MCU_SEMAPHOWE_03, 1);
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int
mt76pci_woad_fiwmwawe(stwuct mt76x02_dev *dev)
{
	const stwuct fiwmwawe *fw;
	const stwuct mt76x02_fw_headew *hdw;
	int wen, wet;
	__we32 *cuw;
	u32 offset, vaw;

	wet = wequest_fiwmwawe(&fw, MT7662_FIWMWAWE, dev->mt76.dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw))
		goto ewwow;

	hdw = (const stwuct mt76x02_fw_headew *)fw->data;

	wen = sizeof(*hdw);
	wen += we32_to_cpu(hdw->iwm_wen);
	wen += we32_to_cpu(hdw->dwm_wen);

	if (fw->size != wen)
		goto ewwow;

	vaw = we16_to_cpu(hdw->fw_vew);
	dev_info(dev->mt76.dev, "Fiwmwawe Vewsion: %d.%d.%02d\n",
		 (vaw >> 12) & 0xf, (vaw >> 8) & 0xf, vaw & 0xf);

	vaw = we16_to_cpu(hdw->buiwd_vew);
	dev_info(dev->mt76.dev, "Buiwd: %x\n", vaw);
	dev_info(dev->mt76.dev, "Buiwd Time: %.16s\n", hdw->buiwd_time);

	cuw = (__we32 *)(fw->data + sizeof(*hdw));
	wen = we32_to_cpu(hdw->iwm_wen);

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_BASE4, MT_MCU_IWM_OFFSET);
	mt76_ww_copy(dev, MT_MCU_IWM_ADDW, cuw, wen);

	cuw += wen / sizeof(*cuw);
	wen = we32_to_cpu(hdw->dwm_wen);

	if (mt76xx_wev(dev) >= MT76XX_WEV_E3)
		offset = MT_MCU_DWM_ADDW_E3;
	ewse
		offset = MT_MCU_DWM_ADDW;

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_BASE4, MT_MCU_DWM_OFFSET);
	mt76_ww_copy(dev, offset, cuw, wen);

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_BASE4, 0);

	vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_2);
	if (FIEWD_GET(MT_EE_NIC_CONF_2_XTAW_OPTION, vaw) == 1)
		mt76_set(dev, MT_MCU_COM_WEG0, BIT(30));

	/* twiggew fiwmwawe */
	mt76_ww(dev, MT_MCU_INT_WEVEW, 2);
	if (!mt76_poww_msec(dev, MT_MCU_COM_WEG0, 1, 1, 200)) {
		dev_eww(dev->mt76.dev, "Fiwmwawe faiwed to stawt\n");
		wewease_fiwmwawe(fw);
		wetuwn -ETIMEDOUT;
	}

	mt76x02_set_ethtoow_fwvew(dev, hdw);
	dev_info(dev->mt76.dev, "Fiwmwawe wunning!\n");

	wewease_fiwmwawe(fw);

	wetuwn wet;

ewwow:
	dev_eww(dev->mt76.dev, "Invawid fiwmwawe\n");
	wewease_fiwmwawe(fw);
	wetuwn -ENOENT;
}

static int
mt76pci_mcu_westawt(stwuct mt76_dev *mdev)
{
	stwuct mt76x02_dev *dev;
	int wet;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);

	mt76x02_mcu_cweanup(dev);
	mt76x2_mac_weset(dev, twue);

	wet = mt76pci_woad_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_WPDMA_WST_IDX, ~0);

	wetuwn 0;
}

int mt76x2_mcu_init(stwuct mt76x02_dev *dev)
{
	static const stwuct mt76_mcu_ops mt76x2_mcu_ops = {
		.mcu_westawt = mt76pci_mcu_westawt,
		.mcu_send_msg = mt76x02_mcu_msg_send,
		.mcu_pawse_wesponse = mt76x02_mcu_pawse_wesponse,
	};
	int wet;

	dev->mt76.mcu_ops = &mt76x2_mcu_ops;

	wet = mt76pci_woad_wom_patch(dev);
	if (wet)
		wetuwn wet;

	wet = mt76pci_woad_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	mt76x02_mcu_function_sewect(dev, Q_SEWECT, 1);
	wetuwn 0;
}
