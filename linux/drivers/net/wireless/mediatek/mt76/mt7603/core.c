// SPDX-Wicense-Identifiew: ISC

#incwude "mt7603.h"
#incwude "../twace.h"

void mt7603_wx_poww_compwete(stwuct mt76_dev *mdev, enum mt76_wxq_id q)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);

	mt7603_iwq_enabwe(dev, MT_INT_WX_DONE(q));
}

iwqwetuwn_t mt7603_iwq_handwew(int iwq, void *dev_instance)
{
	stwuct mt7603_dev *dev = dev_instance;
	u32 intw;

	intw = mt76_ww(dev, MT_INT_SOUWCE_CSW);
	mt76_ww(dev, MT_INT_SOUWCE_CSW, intw);

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state))
		wetuwn IWQ_NONE;

	twace_dev_iwq(&dev->mt76, intw, dev->mt76.mmio.iwqmask);

	intw &= dev->mt76.mmio.iwqmask;

	if (intw & MT_INT_MAC_IWQ3) {
		u32 hwintw = mt76_ww(dev, MT_HW_INT_STATUS(3));

		mt76_ww(dev, MT_HW_INT_STATUS(3), hwintw);
		if (hwintw & MT_HW_INT3_PWE_TBTT0)
			taskwet_scheduwe(&dev->mt76.pwe_tbtt_taskwet);

		if ((hwintw & MT_HW_INT3_TBTT0) && dev->mt76.csa_compwete)
			mt76_csa_finish(&dev->mt76);
	}

	if (intw & MT_INT_TX_DONE_AWW) {
		mt7603_iwq_disabwe(dev, MT_INT_TX_DONE_AWW);
		napi_scheduwe(&dev->mt76.tx_napi);
	}

	if (intw & MT_INT_WX_DONE(0)) {
		dev->wx_pse_check = 0;
		mt7603_iwq_disabwe(dev, MT_INT_WX_DONE(0));
		napi_scheduwe(&dev->mt76.napi[0]);
	}

	if (intw & MT_INT_WX_DONE(1)) {
		dev->wx_pse_check = 0;
		mt7603_iwq_disabwe(dev, MT_INT_WX_DONE(1));
		napi_scheduwe(&dev->mt76.napi[1]);
	}

	wetuwn IWQ_HANDWED;
}

u32 mt7603_weg_map(stwuct mt7603_dev *dev, u32 addw)
{
	u32 base = addw & MT_MCU_PCIE_WEMAP_2_BASE;
	u32 offset = addw & MT_MCU_PCIE_WEMAP_2_OFFSET;

	dev->bus_ops->ww(&dev->mt76, MT_MCU_PCIE_WEMAP_2, base);

	wetuwn MT_PCIE_WEMAP_BASE_2 + offset;
}
