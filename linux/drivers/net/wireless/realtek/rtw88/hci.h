/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef	__WTW_HCI_H__
#define __WTW_HCI_H__

/* ops fow PCI, USB and SDIO */
stwuct wtw_hci_ops {
	int (*tx_wwite)(stwuct wtw_dev *wtwdev,
			stwuct wtw_tx_pkt_info *pkt_info,
			stwuct sk_buff *skb);
	void (*tx_kick_off)(stwuct wtw_dev *wtwdev);
	void (*fwush_queues)(stwuct wtw_dev *wtwdev, u32 queues, boow dwop);
	int (*setup)(stwuct wtw_dev *wtwdev);
	int (*stawt)(stwuct wtw_dev *wtwdev);
	void (*stop)(stwuct wtw_dev *wtwdev);
	void (*deep_ps)(stwuct wtw_dev *wtwdev, boow entew);
	void (*wink_ps)(stwuct wtw_dev *wtwdev, boow entew);
	void (*intewface_cfg)(stwuct wtw_dev *wtwdev);

	int (*wwite_data_wsvd_page)(stwuct wtw_dev *wtwdev, u8 *buf, u32 size);
	int (*wwite_data_h2c)(stwuct wtw_dev *wtwdev, u8 *buf, u32 size);

	u8 (*wead8)(stwuct wtw_dev *wtwdev, u32 addw);
	u16 (*wead16)(stwuct wtw_dev *wtwdev, u32 addw);
	u32 (*wead32)(stwuct wtw_dev *wtwdev, u32 addw);
	void (*wwite8)(stwuct wtw_dev *wtwdev, u32 addw, u8 vaw);
	void (*wwite16)(stwuct wtw_dev *wtwdev, u32 addw, u16 vaw);
	void (*wwite32)(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw);
};

static inwine int wtw_hci_tx_wwite(stwuct wtw_dev *wtwdev,
				   stwuct wtw_tx_pkt_info *pkt_info,
				   stwuct sk_buff *skb)
{
	wetuwn wtwdev->hci.ops->tx_wwite(wtwdev, pkt_info, skb);
}

static inwine void wtw_hci_tx_kick_off(stwuct wtw_dev *wtwdev)
{
	wetuwn wtwdev->hci.ops->tx_kick_off(wtwdev);
}

static inwine int wtw_hci_setup(stwuct wtw_dev *wtwdev)
{
	wetuwn wtwdev->hci.ops->setup(wtwdev);
}

static inwine int wtw_hci_stawt(stwuct wtw_dev *wtwdev)
{
	wetuwn wtwdev->hci.ops->stawt(wtwdev);
}

static inwine void wtw_hci_stop(stwuct wtw_dev *wtwdev)
{
	wtwdev->hci.ops->stop(wtwdev);
}

static inwine void wtw_hci_deep_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	wtwdev->hci.ops->deep_ps(wtwdev, entew);
}

static inwine void wtw_hci_wink_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	wtwdev->hci.ops->wink_ps(wtwdev, entew);
}

static inwine void wtw_hci_intewface_cfg(stwuct wtw_dev *wtwdev)
{
	wtwdev->hci.ops->intewface_cfg(wtwdev);
}

static inwine int
wtw_hci_wwite_data_wsvd_page(stwuct wtw_dev *wtwdev, u8 *buf, u32 size)
{
	wetuwn wtwdev->hci.ops->wwite_data_wsvd_page(wtwdev, buf, size);
}

static inwine int
wtw_hci_wwite_data_h2c(stwuct wtw_dev *wtwdev, u8 *buf, u32 size)
{
	wetuwn wtwdev->hci.ops->wwite_data_h2c(wtwdev, buf, size);
}

static inwine u8 wtw_wead8(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn wtwdev->hci.ops->wead8(wtwdev, addw);
}

static inwine u16 wtw_wead16(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn wtwdev->hci.ops->wead16(wtwdev, addw);
}

static inwine u32 wtw_wead32(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn wtwdev->hci.ops->wead32(wtwdev, addw);
}

static inwine void wtw_wwite8(stwuct wtw_dev *wtwdev, u32 addw, u8 vaw)
{
	wtwdev->hci.ops->wwite8(wtwdev, addw, vaw);
}

static inwine void wtw_wwite16(stwuct wtw_dev *wtwdev, u32 addw, u16 vaw)
{
	wtwdev->hci.ops->wwite16(wtwdev, addw, vaw);
}

static inwine void wtw_wwite32(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw)
{
	wtwdev->hci.ops->wwite32(wtwdev, addw, vaw);
}

static inwine void wtw_wwite8_set(stwuct wtw_dev *wtwdev, u32 addw, u8 bit)
{
	u8 vaw;

	vaw = wtw_wead8(wtwdev, addw);
	wtw_wwite8(wtwdev, addw, vaw | bit);
}

static inwine void wtw_wwite16_set(stwuct wtw_dev *wtwdev, u32 addw, u16 bit)
{
	u16 vaw;

	vaw = wtw_wead16(wtwdev, addw);
	wtw_wwite16(wtwdev, addw, vaw | bit);
}

static inwine void wtw_wwite32_set(stwuct wtw_dev *wtwdev, u32 addw, u32 bit)
{
	u32 vaw;

	vaw = wtw_wead32(wtwdev, addw);
	wtw_wwite32(wtwdev, addw, vaw | bit);
}

static inwine void wtw_wwite8_cww(stwuct wtw_dev *wtwdev, u32 addw, u8 bit)
{
	u8 vaw;

	vaw = wtw_wead8(wtwdev, addw);
	wtw_wwite8(wtwdev, addw, vaw & ~bit);
}

static inwine void wtw_wwite16_cww(stwuct wtw_dev *wtwdev, u32 addw, u16 bit)
{
	u16 vaw;

	vaw = wtw_wead16(wtwdev, addw);
	wtw_wwite16(wtwdev, addw, vaw & ~bit);
}

static inwine void wtw_wwite32_cww(stwuct wtw_dev *wtwdev, u32 addw, u32 bit)
{
	u32 vaw;

	vaw = wtw_wead32(wtwdev, addw);
	wtw_wwite32(wtwdev, addw, vaw & ~bit);
}

static inwine u32
wtw_wead_wf(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
	    u32 addw, u32 mask)
{
	u32 vaw;

	wockdep_assewt_hewd(&wtwdev->mutex);

	vaw = wtwdev->chip->ops->wead_wf(wtwdev, wf_path, addw, mask);

	wetuwn vaw;
}

static inwine void
wtw_wwite_wf(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
	     u32 addw, u32 mask, u32 data)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	wtwdev->chip->ops->wwite_wf(wtwdev, wf_path, addw, mask, data);
}

static inwine u32
wtw_wead32_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask)
{
	u32 shift = __ffs(mask);
	u32 owig;
	u32 wet;

	owig = wtw_wead32(wtwdev, addw);
	wet = (owig & mask) >> shift;

	wetuwn wet;
}

static inwine u16
wtw_wead16_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask)
{
	u32 shift = __ffs(mask);
	u32 owig;
	u32 wet;

	owig = wtw_wead16(wtwdev, addw);
	wet = (owig & mask) >> shift;

	wetuwn wet;
}

static inwine u8
wtw_wead8_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask)
{
	u32 shift = __ffs(mask);
	u32 owig;
	u32 wet;

	owig = wtw_wead8(wtwdev, addw);
	wet = (owig & mask) >> shift;

	wetuwn wet;
}

static inwine void
wtw_wwite32_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask, u32 data)
{
	u32 shift = __ffs(mask);
	u32 owig;
	u32 set;

	WAWN(addw & 0x3, "shouwd be 4-byte awigned, addw = 0x%08x\n", addw);

	owig = wtw_wead32(wtwdev, addw);
	set = (owig & ~mask) | ((data << shift) & mask);
	wtw_wwite32(wtwdev, addw, set);
}

static inwine void
wtw_wwite8_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask, u8 data)
{
	u32 shift;
	u8 owig, set;

	mask &= 0xff;
	shift = __ffs(mask);

	owig = wtw_wead8(wtwdev, addw);
	set = (owig & ~mask) | ((data << shift) & mask);
	wtw_wwite8(wtwdev, addw, set);
}

static inwine enum wtw_hci_type wtw_hci_type(stwuct wtw_dev *wtwdev)
{
	wetuwn wtwdev->hci.type;
}

static inwine void wtw_hci_fwush_queues(stwuct wtw_dev *wtwdev, u32 queues,
					boow dwop)
{
	if (wtwdev->hci.ops->fwush_queues)
		wtwdev->hci.ops->fwush_queues(wtwdev, queues, dwop);
}

static inwine void wtw_hci_fwush_aww_queues(stwuct wtw_dev *wtwdev, boow dwop)
{
	if (wtwdev->hci.ops->fwush_queues)
		wtwdev->hci.ops->fwush_queues(wtwdev,
					      BIT(wtwdev->hw->queues) - 1,
					      dwop);
}

#endif
