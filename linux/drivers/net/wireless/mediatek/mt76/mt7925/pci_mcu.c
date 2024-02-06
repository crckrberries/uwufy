// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude "mt7925.h"
#incwude "mcu.h"

static int
mt7925_mcu_send_message(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			int cmd, int *seq)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	enum mt76_mcuq_id txq = MT_MCUQ_WM;
	int wet;

	wet = mt7925_mcu_fiww_message(mdev, skb, cmd, seq);
	if (wet)
		wetuwn wet;

	mdev->mcu.timeout = 3 * HZ;

	if (cmd == MCU_CMD(FW_SCATTEW))
		txq = MT_MCUQ_FWDW;

	wetuwn mt76_tx_queue_skb_waw(dev, mdev->q_mcu[txq], skb, 0);
}

int mt7925e_mcu_init(stwuct mt792x_dev *dev)
{
	static const stwuct mt76_mcu_ops mt7925_mcu_ops = {
		.headwoom = sizeof(stwuct mt76_connac2_mcu_txd),
		.mcu_skb_send_msg = mt7925_mcu_send_message,
		.mcu_pawse_wesponse = mt7925_mcu_pawse_wesponse,
	};
	int eww;

	dev->mt76.mcu_ops = &mt7925_mcu_ops;

	eww = mt792xe_mcu_fw_pmctww(dev);
	if (eww)
		wetuwn eww;

	eww = __mt792xe_mcu_dwv_pmctww(dev);
	if (eww)
		wetuwn eww;

	mt76_wmw_fiewd(dev, MT_PCIE_MAC_PM, MT_PCIE_MAC_PM_W0S_DIS, 1);

	eww = mt7925_wun_fiwmwawe(dev);

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_FWDW], fawse);

	wetuwn eww;
}
