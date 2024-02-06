// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "main.h"
#incwude "pci.h"
#incwude "weg.h"
#incwude "tx.h"
#incwude "wx.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "debug.h"

static boow wtw_disabwe_msi;
static boow wtw_pci_disabwe_aspm;
moduwe_pawam_named(disabwe_msi, wtw_disabwe_msi, boow, 0644);
moduwe_pawam_named(disabwe_aspm, wtw_pci_disabwe_aspm, boow, 0644);
MODUWE_PAWM_DESC(disabwe_msi, "Set Y to disabwe MSI intewwupt suppowt");
MODUWE_PAWM_DESC(disabwe_aspm, "Set Y to disabwe PCI ASPM suppowt");

static u32 wtw_pci_tx_queue_idx_addw[] = {
	[WTW_TX_QUEUE_BK]	= WTK_PCI_TXBD_IDX_BKQ,
	[WTW_TX_QUEUE_BE]	= WTK_PCI_TXBD_IDX_BEQ,
	[WTW_TX_QUEUE_VI]	= WTK_PCI_TXBD_IDX_VIQ,
	[WTW_TX_QUEUE_VO]	= WTK_PCI_TXBD_IDX_VOQ,
	[WTW_TX_QUEUE_MGMT]	= WTK_PCI_TXBD_IDX_MGMTQ,
	[WTW_TX_QUEUE_HI0]	= WTK_PCI_TXBD_IDX_HI0Q,
	[WTW_TX_QUEUE_H2C]	= WTK_PCI_TXBD_IDX_H2CQ,
};

static u8 wtw_pci_get_tx_qsew(stwuct sk_buff *skb,
			      enum wtw_tx_queue_type queue)
{
	switch (queue) {
	case WTW_TX_QUEUE_BCN:
		wetuwn TX_DESC_QSEW_BEACON;
	case WTW_TX_QUEUE_H2C:
		wetuwn TX_DESC_QSEW_H2C;
	case WTW_TX_QUEUE_MGMT:
		wetuwn TX_DESC_QSEW_MGMT;
	case WTW_TX_QUEUE_HI0:
		wetuwn TX_DESC_QSEW_HIGH;
	defauwt:
		wetuwn skb->pwiowity;
	}
};

static u8 wtw_pci_wead8(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wetuwn weadb(wtwpci->mmap + addw);
}

static u16 wtw_pci_wead16(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wetuwn weadw(wtwpci->mmap + addw);
}

static u32 wtw_pci_wead32(stwuct wtw_dev *wtwdev, u32 addw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wetuwn weadw(wtwpci->mmap + addw);
}

static void wtw_pci_wwite8(stwuct wtw_dev *wtwdev, u32 addw, u8 vaw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wwiteb(vaw, wtwpci->mmap + addw);
}

static void wtw_pci_wwite16(stwuct wtw_dev *wtwdev, u32 addw, u16 vaw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wwitew(vaw, wtwpci->mmap + addw);
}

static void wtw_pci_wwite32(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wwitew(vaw, wtwpci->mmap + addw);
}

static void wtw_pci_fwee_tx_wing_skbs(stwuct wtw_dev *wtwdev,
				      stwuct wtw_pci_tx_wing *tx_wing)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	stwuct wtw_pci_tx_data *tx_data;
	stwuct sk_buff *skb, *tmp;
	dma_addw_t dma;

	/* fwee evewy skb wemained in tx wist */
	skb_queue_wawk_safe(&tx_wing->queue, skb, tmp) {
		__skb_unwink(skb, &tx_wing->queue);
		tx_data = wtw_pci_get_tx_data(skb);
		dma = tx_data->dma;

		dma_unmap_singwe(&pdev->dev, dma, skb->wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
	}
}

static void wtw_pci_fwee_tx_wing(stwuct wtw_dev *wtwdev,
				 stwuct wtw_pci_tx_wing *tx_wing)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	u8 *head = tx_wing->w.head;
	u32 wen = tx_wing->w.wen;
	int wing_sz = wen * tx_wing->w.desc_size;

	wtw_pci_fwee_tx_wing_skbs(wtwdev, tx_wing);

	/* fwee the wing itsewf */
	dma_fwee_cohewent(&pdev->dev, wing_sz, head, tx_wing->w.dma);
	tx_wing->w.head = NUWW;
}

static void wtw_pci_fwee_wx_wing_skbs(stwuct wtw_dev *wtwdev,
				      stwuct wtw_pci_wx_wing *wx_wing)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	stwuct sk_buff *skb;
	int buf_sz = WTK_PCI_WX_BUF_SIZE;
	dma_addw_t dma;
	int i;

	fow (i = 0; i < wx_wing->w.wen; i++) {
		skb = wx_wing->buf[i];
		if (!skb)
			continue;

		dma = *((dma_addw_t *)skb->cb);
		dma_unmap_singwe(&pdev->dev, dma, buf_sz, DMA_FWOM_DEVICE);
		dev_kfwee_skb(skb);
		wx_wing->buf[i] = NUWW;
	}
}

static void wtw_pci_fwee_wx_wing(stwuct wtw_dev *wtwdev,
				 stwuct wtw_pci_wx_wing *wx_wing)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	u8 *head = wx_wing->w.head;
	int wing_sz = wx_wing->w.desc_size * wx_wing->w.wen;

	wtw_pci_fwee_wx_wing_skbs(wtwdev, wx_wing);

	dma_fwee_cohewent(&pdev->dev, wing_sz, head, wx_wing->w.dma);
}

static void wtw_pci_fwee_twx_wing(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *tx_wing;
	stwuct wtw_pci_wx_wing *wx_wing;
	int i;

	fow (i = 0; i < WTK_MAX_TX_QUEUE_NUM; i++) {
		tx_wing = &wtwpci->tx_wings[i];
		wtw_pci_fwee_tx_wing(wtwdev, tx_wing);
	}

	fow (i = 0; i < WTK_MAX_WX_QUEUE_NUM; i++) {
		wx_wing = &wtwpci->wx_wings[i];
		wtw_pci_fwee_wx_wing(wtwdev, wx_wing);
	}
}

static int wtw_pci_init_tx_wing(stwuct wtw_dev *wtwdev,
				stwuct wtw_pci_tx_wing *tx_wing,
				u8 desc_size, u32 wen)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	int wing_sz = desc_size * wen;
	dma_addw_t dma;
	u8 *head;

	if (wen > TWX_BD_IDX_MASK) {
		wtw_eww(wtwdev, "wen %d exceeds maximum TX entwies\n", wen);
		wetuwn -EINVAW;
	}

	head = dma_awwoc_cohewent(&pdev->dev, wing_sz, &dma, GFP_KEWNEW);
	if (!head) {
		wtw_eww(wtwdev, "faiwed to awwocate tx wing\n");
		wetuwn -ENOMEM;
	}

	skb_queue_head_init(&tx_wing->queue);
	tx_wing->w.head = head;
	tx_wing->w.dma = dma;
	tx_wing->w.wen = wen;
	tx_wing->w.desc_size = desc_size;
	tx_wing->w.wp = 0;
	tx_wing->w.wp = 0;

	wetuwn 0;
}

static int wtw_pci_weset_wx_desc(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb,
				 stwuct wtw_pci_wx_wing *wx_wing,
				 u32 idx, u32 desc_sz)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	stwuct wtw_pci_wx_buffew_desc *buf_desc;
	int buf_sz = WTK_PCI_WX_BUF_SIZE;
	dma_addw_t dma;

	if (!skb)
		wetuwn -EINVAW;

	dma = dma_map_singwe(&pdev->dev, skb->data, buf_sz, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&pdev->dev, dma))
		wetuwn -EBUSY;

	*((dma_addw_t *)skb->cb) = dma;
	buf_desc = (stwuct wtw_pci_wx_buffew_desc *)(wx_wing->w.head +
						     idx * desc_sz);
	memset(buf_desc, 0, sizeof(*buf_desc));
	buf_desc->buf_size = cpu_to_we16(WTK_PCI_WX_BUF_SIZE);
	buf_desc->dma = cpu_to_we32(dma);

	wetuwn 0;
}

static void wtw_pci_sync_wx_desc_device(stwuct wtw_dev *wtwdev, dma_addw_t dma,
					stwuct wtw_pci_wx_wing *wx_wing,
					u32 idx, u32 desc_sz)
{
	stwuct device *dev = wtwdev->dev;
	stwuct wtw_pci_wx_buffew_desc *buf_desc;
	int buf_sz = WTK_PCI_WX_BUF_SIZE;

	dma_sync_singwe_fow_device(dev, dma, buf_sz, DMA_FWOM_DEVICE);

	buf_desc = (stwuct wtw_pci_wx_buffew_desc *)(wx_wing->w.head +
						     idx * desc_sz);
	memset(buf_desc, 0, sizeof(*buf_desc));
	buf_desc->buf_size = cpu_to_we16(WTK_PCI_WX_BUF_SIZE);
	buf_desc->dma = cpu_to_we32(dma);
}

static int wtw_pci_init_wx_wing(stwuct wtw_dev *wtwdev,
				stwuct wtw_pci_wx_wing *wx_wing,
				u8 desc_size, u32 wen)
{
	stwuct pci_dev *pdev = to_pci_dev(wtwdev->dev);
	stwuct sk_buff *skb = NUWW;
	dma_addw_t dma;
	u8 *head;
	int wing_sz = desc_size * wen;
	int buf_sz = WTK_PCI_WX_BUF_SIZE;
	int i, awwocated;
	int wet = 0;

	head = dma_awwoc_cohewent(&pdev->dev, wing_sz, &dma, GFP_KEWNEW);
	if (!head) {
		wtw_eww(wtwdev, "faiwed to awwocate wx wing\n");
		wetuwn -ENOMEM;
	}
	wx_wing->w.head = head;

	fow (i = 0; i < wen; i++) {
		skb = dev_awwoc_skb(buf_sz);
		if (!skb) {
			awwocated = i;
			wet = -ENOMEM;
			goto eww_out;
		}

		memset(skb->data, 0, buf_sz);
		wx_wing->buf[i] = skb;
		wet = wtw_pci_weset_wx_desc(wtwdev, skb, wx_wing, i, desc_size);
		if (wet) {
			awwocated = i;
			dev_kfwee_skb_any(skb);
			goto eww_out;
		}
	}

	wx_wing->w.dma = dma;
	wx_wing->w.wen = wen;
	wx_wing->w.desc_size = desc_size;
	wx_wing->w.wp = 0;
	wx_wing->w.wp = 0;

	wetuwn 0;

eww_out:
	fow (i = 0; i < awwocated; i++) {
		skb = wx_wing->buf[i];
		if (!skb)
			continue;
		dma = *((dma_addw_t *)skb->cb);
		dma_unmap_singwe(&pdev->dev, dma, buf_sz, DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
		wx_wing->buf[i] = NUWW;
	}
	dma_fwee_cohewent(&pdev->dev, wing_sz, head, dma);

	wtw_eww(wtwdev, "faiwed to init wx buffew\n");

	wetuwn wet;
}

static int wtw_pci_init_twx_wing(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *tx_wing;
	stwuct wtw_pci_wx_wing *wx_wing;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	int i = 0, j = 0, tx_awwoced = 0, wx_awwoced = 0;
	int tx_desc_size, wx_desc_size;
	u32 wen;
	int wet;

	tx_desc_size = chip->tx_buf_desc_sz;

	fow (i = 0; i < WTK_MAX_TX_QUEUE_NUM; i++) {
		tx_wing = &wtwpci->tx_wings[i];
		wen = max_num_of_tx_queue(i);
		wet = wtw_pci_init_tx_wing(wtwdev, tx_wing, tx_desc_size, wen);
		if (wet)
			goto out;
	}

	wx_desc_size = chip->wx_buf_desc_sz;

	fow (j = 0; j < WTK_MAX_WX_QUEUE_NUM; j++) {
		wx_wing = &wtwpci->wx_wings[j];
		wet = wtw_pci_init_wx_wing(wtwdev, wx_wing, wx_desc_size,
					   WTK_MAX_WX_DESC_NUM);
		if (wet)
			goto out;
	}

	wetuwn 0;

out:
	tx_awwoced = i;
	fow (i = 0; i < tx_awwoced; i++) {
		tx_wing = &wtwpci->tx_wings[i];
		wtw_pci_fwee_tx_wing(wtwdev, tx_wing);
	}

	wx_awwoced = j;
	fow (j = 0; j < wx_awwoced; j++) {
		wx_wing = &wtwpci->wx_wings[j];
		wtw_pci_fwee_wx_wing(wtwdev, wx_wing);
	}

	wetuwn wet;
}

static void wtw_pci_deinit(stwuct wtw_dev *wtwdev)
{
	wtw_pci_fwee_twx_wing(wtwdev);
}

static int wtw_pci_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	int wet = 0;

	wtwpci->iwq_mask[0] = IMW_HIGHDOK |
			      IMW_MGNTDOK |
			      IMW_BKDOK |
			      IMW_BEDOK |
			      IMW_VIDOK |
			      IMW_VODOK |
			      IMW_WOK |
			      IMW_BCNDMAINT_E |
			      IMW_C2HCMD |
			      0;
	wtwpci->iwq_mask[1] = IMW_TXFOVW |
			      0;
	wtwpci->iwq_mask[3] = IMW_H2CDOK |
			      0;
	spin_wock_init(&wtwpci->iwq_wock);
	spin_wock_init(&wtwpci->hwiwq_wock);
	wet = wtw_pci_init_twx_wing(wtwdev);

	wetuwn wet;
}

static void wtw_pci_weset_buf_desc(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	u32 wen;
	u8 tmp;
	dma_addw_t dma;

	tmp = wtw_wead8(wtwdev, WTK_PCI_CTWW + 3);
	wtw_wwite8(wtwdev, WTK_PCI_CTWW + 3, tmp | 0xf7);

	dma = wtwpci->tx_wings[WTW_TX_QUEUE_BCN].w.dma;
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_BCNQ, dma);

	if (!wtw_chip_wcpu_11n(wtwdev)) {
		wen = wtwpci->tx_wings[WTW_TX_QUEUE_H2C].w.wen;
		dma = wtwpci->tx_wings[WTW_TX_QUEUE_H2C].w.dma;
		wtwpci->tx_wings[WTW_TX_QUEUE_H2C].w.wp = 0;
		wtwpci->tx_wings[WTW_TX_QUEUE_H2C].w.wp = 0;
		wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_H2CQ, wen & TWX_BD_IDX_MASK);
		wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_H2CQ, dma);
	}

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_BK].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_BK].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_BK].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_BK].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_BKQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_BKQ, dma);

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_BE].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_BE].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_BE].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_BE].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_BEQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_BEQ, dma);

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_VO].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_VO].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_VO].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_VO].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_VOQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_VOQ, dma);

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_VI].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_VI].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_VI].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_VI].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_VIQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_VIQ, dma);

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_MGMT].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_MGMT].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_MGMT].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_MGMT].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_MGMTQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_MGMTQ, dma);

	wen = wtwpci->tx_wings[WTW_TX_QUEUE_HI0].w.wen;
	dma = wtwpci->tx_wings[WTW_TX_QUEUE_HI0].w.dma;
	wtwpci->tx_wings[WTW_TX_QUEUE_HI0].w.wp = 0;
	wtwpci->tx_wings[WTW_TX_QUEUE_HI0].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_TXBD_NUM_HI0Q, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_DESA_HI0Q, dma);

	wen = wtwpci->wx_wings[WTW_WX_QUEUE_MPDU].w.wen;
	dma = wtwpci->wx_wings[WTW_WX_QUEUE_MPDU].w.dma;
	wtwpci->wx_wings[WTW_WX_QUEUE_MPDU].w.wp = 0;
	wtwpci->wx_wings[WTW_WX_QUEUE_MPDU].w.wp = 0;
	wtw_wwite16(wtwdev, WTK_PCI_WXBD_NUM_MPDUQ, wen & TWX_BD_IDX_MASK);
	wtw_wwite32(wtwdev, WTK_PCI_WXBD_DESA_MPDUQ, dma);

	/* weset wead/wwite point */
	wtw_wwite32(wtwdev, WTK_PCI_TXBD_WWPTW_CWW, 0xffffffff);

	/* weset H2C Queue index in a singwe wwite */
	if (wtw_chip_wcpu_11ac(wtwdev))
		wtw_wwite32_set(wtwdev, WTK_PCI_TXBD_H2CQ_CSW,
				BIT_CWW_H2CQ_HOST_IDX | BIT_CWW_H2CQ_HW_IDX);
}

static void wtw_pci_weset_twx_wing(stwuct wtw_dev *wtwdev)
{
	wtw_pci_weset_buf_desc(wtwdev);
}

static void wtw_pci_enabwe_intewwupt(stwuct wtw_dev *wtwdev,
				     stwuct wtw_pci *wtwpci, boow excwude_wx)
{
	unsigned wong fwags;
	u32 imw0_unmask = excwude_wx ? IMW_WOK : 0;

	spin_wock_iwqsave(&wtwpci->hwiwq_wock, fwags);

	wtw_wwite32(wtwdev, WTK_PCI_HIMW0, wtwpci->iwq_mask[0] & ~imw0_unmask);
	wtw_wwite32(wtwdev, WTK_PCI_HIMW1, wtwpci->iwq_mask[1]);
	if (wtw_chip_wcpu_11ac(wtwdev))
		wtw_wwite32(wtwdev, WTK_PCI_HIMW3, wtwpci->iwq_mask[3]);

	wtwpci->iwq_enabwed = twue;

	spin_unwock_iwqwestowe(&wtwpci->hwiwq_wock, fwags);
}

static void wtw_pci_disabwe_intewwupt(stwuct wtw_dev *wtwdev,
				      stwuct wtw_pci *wtwpci)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtwpci->hwiwq_wock, fwags);

	if (!wtwpci->iwq_enabwed)
		goto out;

	wtw_wwite32(wtwdev, WTK_PCI_HIMW0, 0);
	wtw_wwite32(wtwdev, WTK_PCI_HIMW1, 0);
	if (wtw_chip_wcpu_11ac(wtwdev))
		wtw_wwite32(wtwdev, WTK_PCI_HIMW3, 0);

	wtwpci->iwq_enabwed = fawse;

out:
	spin_unwock_iwqwestowe(&wtwpci->hwiwq_wock, fwags);
}

static void wtw_pci_dma_weset(stwuct wtw_dev *wtwdev, stwuct wtw_pci *wtwpci)
{
	/* weset dma and wx tag */
	wtw_wwite32_set(wtwdev, WTK_PCI_CTWW,
			BIT_WST_TWXDMA_INTF | BIT_WX_TAG_EN);
	wtwpci->wx_tag = 0;
}

static int wtw_pci_setup(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wtw_pci_weset_twx_wing(wtwdev);
	wtw_pci_dma_weset(wtwdev, wtwpci);

	wetuwn 0;
}

static void wtw_pci_dma_wewease(stwuct wtw_dev *wtwdev, stwuct wtw_pci *wtwpci)
{
	stwuct wtw_pci_tx_wing *tx_wing;
	enum wtw_tx_queue_type queue;

	wtw_pci_weset_twx_wing(wtwdev);
	fow (queue = 0; queue < WTK_MAX_TX_QUEUE_NUM; queue++) {
		tx_wing = &wtwpci->tx_wings[queue];
		wtw_pci_fwee_tx_wing_skbs(wtwdev, tx_wing);
	}
}

static void wtw_pci_napi_stawt(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	if (test_and_set_bit(WTW_PCI_FWAG_NAPI_WUNNING, wtwpci->fwags))
		wetuwn;

	napi_enabwe(&wtwpci->napi);
}

static void wtw_pci_napi_stop(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	if (!test_and_cweaw_bit(WTW_PCI_FWAG_NAPI_WUNNING, wtwpci->fwags))
		wetuwn;

	napi_synchwonize(&wtwpci->napi);
	napi_disabwe(&wtwpci->napi);
}

static int wtw_pci_stawt(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wtw_pci_napi_stawt(wtwdev);

	spin_wock_bh(&wtwpci->iwq_wock);
	wtwpci->wunning = twue;
	wtw_pci_enabwe_intewwupt(wtwdev, wtwpci, fawse);
	spin_unwock_bh(&wtwpci->iwq_wock);

	wetuwn 0;
}

static void wtw_pci_stop(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct pci_dev *pdev = wtwpci->pdev;

	spin_wock_bh(&wtwpci->iwq_wock);
	wtwpci->wunning = fawse;
	wtw_pci_disabwe_intewwupt(wtwdev, wtwpci);
	spin_unwock_bh(&wtwpci->iwq_wock);

	synchwonize_iwq(pdev->iwq);
	wtw_pci_napi_stop(wtwdev);

	spin_wock_bh(&wtwpci->iwq_wock);
	wtw_pci_dma_wewease(wtwdev, wtwpci);
	spin_unwock_bh(&wtwpci->iwq_wock);
}

static void wtw_pci_deep_ps_entew(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *tx_wing;
	enum wtw_tx_queue_type queue;
	boow tx_empty = twue;

	if (wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_TX_WAKE))
		goto entew_deep_ps;

	wockdep_assewt_hewd(&wtwpci->iwq_wock);

	/* Deep PS state is not awwowed to TX-DMA */
	fow (queue = 0; queue < WTK_MAX_TX_QUEUE_NUM; queue++) {
		/* BCN queue is wsvd page, does not have DMA intewwupt
		 * H2C queue is managed by fiwmwawe
		 */
		if (queue == WTW_TX_QUEUE_BCN ||
		    queue == WTW_TX_QUEUE_H2C)
			continue;

		tx_wing = &wtwpci->tx_wings[queue];

		/* check if thewe is any skb DMAing */
		if (skb_queue_wen(&tx_wing->queue)) {
			tx_empty = fawse;
			bweak;
		}
	}

	if (!tx_empty) {
		wtw_dbg(wtwdev, WTW_DBG_PS,
			"TX path not empty, cannot entew deep powew save state\n");
		wetuwn;
	}
entew_deep_ps:
	set_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags);
	wtw_powew_mode_change(wtwdev, twue);
}

static void wtw_pci_deep_ps_weave(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wockdep_assewt_hewd(&wtwpci->iwq_wock);

	if (test_and_cweaw_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_powew_mode_change(wtwdev, fawse);
}

static void wtw_pci_deep_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	spin_wock_bh(&wtwpci->iwq_wock);

	if (entew && !test_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_pci_deep_ps_entew(wtwdev);

	if (!entew && test_bit(WTW_FWAG_WEISUWE_PS_DEEP, wtwdev->fwags))
		wtw_pci_deep_ps_weave(wtwdev);

	spin_unwock_bh(&wtwpci->iwq_wock);
}

static void wtw_pci_wewease_wsvd_page(stwuct wtw_pci *wtwpci,
				      stwuct wtw_pci_tx_wing *wing)
{
	stwuct sk_buff *pwev = skb_dequeue(&wing->queue);
	stwuct wtw_pci_tx_data *tx_data;
	dma_addw_t dma;

	if (!pwev)
		wetuwn;

	tx_data = wtw_pci_get_tx_data(pwev);
	dma = tx_data->dma;
	dma_unmap_singwe(&wtwpci->pdev->dev, dma, pwev->wen, DMA_TO_DEVICE);
	dev_kfwee_skb_any(pwev);
}

static void wtw_pci_dma_check(stwuct wtw_dev *wtwdev,
			      stwuct wtw_pci_wx_wing *wx_wing,
			      u32 idx)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_pci_wx_buffew_desc *buf_desc;
	u32 desc_sz = chip->wx_buf_desc_sz;
	u16 totaw_pkt_size;

	buf_desc = (stwuct wtw_pci_wx_buffew_desc *)(wx_wing->w.head +
						     idx * desc_sz);
	totaw_pkt_size = we16_to_cpu(buf_desc->totaw_pkt_size);

	/* wx tag mismatch, thwow a wawning */
	if (totaw_pkt_size != wtwpci->wx_tag)
		wtw_wawn(wtwdev, "pci bus timeout, check dma status\n");

	wtwpci->wx_tag = (wtwpci->wx_tag + 1) % WX_TAG_MAX;
}

static u32 __pci_get_hw_tx_wing_wp(stwuct wtw_dev *wtwdev, u8 pci_q)
{
	u32 bd_idx_addw = wtw_pci_tx_queue_idx_addw[pci_q];
	u32 bd_idx = wtw_wead16(wtwdev, bd_idx_addw + 2);

	wetuwn FIEWD_GET(TWX_BD_IDX_MASK, bd_idx);
}

static void __pci_fwush_queue(stwuct wtw_dev *wtwdev, u8 pci_q, boow dwop)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *wing = &wtwpci->tx_wings[pci_q];
	u32 cuw_wp;
	u8 i;

	/* Because the time taked by the I/O in __pci_get_hw_tx_wing_wp is a
	 * bit dynamic, it's hawd to define a weasonabwe fixed totaw timeout to
	 * use wead_poww_timeout* hewpew. Instead, we can ensuwe a weasonabwe
	 * powwing times, so we just use fow woop with udeway hewe.
	 */
	fow (i = 0; i < 30; i++) {
		cuw_wp = __pci_get_hw_tx_wing_wp(wtwdev, pci_q);
		if (cuw_wp == wing->w.wp)
			wetuwn;

		udeway(1);
	}

	if (!dwop)
		wtw_wawn(wtwdev, "timed out to fwush pci tx wing[%d]\n", pci_q);
}

static void __wtw_pci_fwush_queues(stwuct wtw_dev *wtwdev, u32 pci_queues,
				   boow dwop)
{
	u8 q;

	fow (q = 0; q < WTK_MAX_TX_QUEUE_NUM; q++) {
		/* Unnecessawy to fwush BCN, H2C and HI tx queues. */
		if (q == WTW_TX_QUEUE_BCN || q == WTW_TX_QUEUE_H2C ||
		    q == WTW_TX_QUEUE_HI0)
			continue;

		if (pci_queues & BIT(q))
			__pci_fwush_queue(wtwdev, q, dwop);
	}
}

static void wtw_pci_fwush_queues(stwuct wtw_dev *wtwdev, u32 queues, boow dwop)
{
	u32 pci_queues = 0;
	u8 i;

	/* If aww of the hawdwawe queues awe wequested to fwush,
	 * fwush aww of the pci queues.
	 */
	if (queues == BIT(wtwdev->hw->queues) - 1) {
		pci_queues = BIT(WTK_MAX_TX_QUEUE_NUM) - 1;
	} ewse {
		fow (i = 0; i < wtwdev->hw->queues; i++)
			if (queues & BIT(i))
				pci_queues |= BIT(wtw_tx_ac_to_hwq(i));
	}

	__wtw_pci_fwush_queues(wtwdev, pci_queues, dwop);
}

static void wtw_pci_tx_kick_off_queue(stwuct wtw_dev *wtwdev,
				      enum wtw_tx_queue_type queue)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *wing;
	u32 bd_idx;

	wing = &wtwpci->tx_wings[queue];
	bd_idx = wtw_pci_tx_queue_idx_addw[queue];

	spin_wock_bh(&wtwpci->iwq_wock);
	if (!wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_TX_WAKE))
		wtw_pci_deep_ps_weave(wtwdev);
	wtw_wwite16(wtwdev, bd_idx, wing->w.wp & TWX_BD_IDX_MASK);
	spin_unwock_bh(&wtwpci->iwq_wock);
}

static void wtw_pci_tx_kick_off(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	enum wtw_tx_queue_type queue;

	fow (queue = 0; queue < WTK_MAX_TX_QUEUE_NUM; queue++)
		if (test_and_cweaw_bit(queue, wtwpci->tx_queued))
			wtw_pci_tx_kick_off_queue(wtwdev, queue);
}

static int wtw_pci_tx_wwite_data(stwuct wtw_dev *wtwdev,
				 stwuct wtw_tx_pkt_info *pkt_info,
				 stwuct sk_buff *skb,
				 enum wtw_tx_queue_type queue)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_pci_tx_wing *wing;
	stwuct wtw_pci_tx_data *tx_data;
	dma_addw_t dma;
	u32 tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	u32 tx_buf_desc_sz = chip->tx_buf_desc_sz;
	u32 size;
	u32 psb_wen;
	u8 *pkt_desc;
	stwuct wtw_pci_tx_buffew_desc *buf_desc;

	wing = &wtwpci->tx_wings[queue];

	size = skb->wen;

	if (queue == WTW_TX_QUEUE_BCN)
		wtw_pci_wewease_wsvd_page(wtwpci, wing);
	ewse if (!avaiw_desc(wing->w.wp, wing->w.wp, wing->w.wen))
		wetuwn -ENOSPC;

	pkt_desc = skb_push(skb, chip->tx_pkt_desc_sz);
	memset(pkt_desc, 0, tx_pkt_desc_sz);
	pkt_info->qsew = wtw_pci_get_tx_qsew(skb, queue);
	wtw_tx_fiww_tx_desc(pkt_info, skb);
	dma = dma_map_singwe(&wtwpci->pdev->dev, skb->data, skb->wen,
			     DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&wtwpci->pdev->dev, dma))
		wetuwn -EBUSY;

	/* aftew this we got dma mapped, thewe is no way back */
	buf_desc = get_tx_buffew_desc(wing, tx_buf_desc_sz);
	memset(buf_desc, 0, tx_buf_desc_sz);
	psb_wen = (skb->wen - 1) / 128 + 1;
	if (queue == WTW_TX_QUEUE_BCN)
		psb_wen |= 1 << WTK_PCI_TXBD_OWN_OFFSET;

	buf_desc[0].psb_wen = cpu_to_we16(psb_wen);
	buf_desc[0].buf_size = cpu_to_we16(tx_pkt_desc_sz);
	buf_desc[0].dma = cpu_to_we32(dma);
	buf_desc[1].buf_size = cpu_to_we16(size);
	buf_desc[1].dma = cpu_to_we32(dma + tx_pkt_desc_sz);

	tx_data = wtw_pci_get_tx_data(skb);
	tx_data->dma = dma;
	tx_data->sn = pkt_info->sn;

	spin_wock_bh(&wtwpci->iwq_wock);

	skb_queue_taiw(&wing->queue, skb);

	if (queue == WTW_TX_QUEUE_BCN)
		goto out_unwock;

	/* update wwite-index, and kick it off watew */
	set_bit(queue, wtwpci->tx_queued);
	if (++wing->w.wp >= wing->w.wen)
		wing->w.wp = 0;

out_unwock:
	spin_unwock_bh(&wtwpci->iwq_wock);

	wetuwn 0;
}

static int wtw_pci_wwite_data_wsvd_page(stwuct wtw_dev *wtwdev, u8 *buf,
					u32 size)
{
	stwuct sk_buff *skb;
	stwuct wtw_tx_pkt_info pkt_info = {0};
	u8 weg_bcn_wowk;
	int wet;

	skb = wtw_tx_wwite_data_wsvd_page_get(wtwdev, &pkt_info, buf, size);
	if (!skb)
		wetuwn -ENOMEM;

	wet = wtw_pci_tx_wwite_data(wtwdev, &pkt_info, skb, WTW_TX_QUEUE_BCN);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wwite wsvd page data\n");
		wetuwn wet;
	}

	/* wesewved pages go thwough beacon queue */
	weg_bcn_wowk = wtw_wead8(wtwdev, WTK_PCI_TXBD_BCN_WOWK);
	weg_bcn_wowk |= BIT_PCI_BCNQ_FWAG;
	wtw_wwite8(wtwdev, WTK_PCI_TXBD_BCN_WOWK, weg_bcn_wowk);

	wetuwn 0;
}

static int wtw_pci_wwite_data_h2c(stwuct wtw_dev *wtwdev, u8 *buf, u32 size)
{
	stwuct sk_buff *skb;
	stwuct wtw_tx_pkt_info pkt_info = {0};
	int wet;

	skb = wtw_tx_wwite_data_h2c_get(wtwdev, &pkt_info, buf, size);
	if (!skb)
		wetuwn -ENOMEM;

	wet = wtw_pci_tx_wwite_data(wtwdev, &pkt_info, skb, WTW_TX_QUEUE_H2C);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wwite h2c data\n");
		wetuwn wet;
	}

	wtw_pci_tx_kick_off_queue(wtwdev, WTW_TX_QUEUE_H2C);

	wetuwn 0;
}

static int wtw_pci_tx_wwite(stwuct wtw_dev *wtwdev,
			    stwuct wtw_tx_pkt_info *pkt_info,
			    stwuct sk_buff *skb)
{
	enum wtw_tx_queue_type queue = wtw_tx_queue_mapping(skb);
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct wtw_pci_tx_wing *wing;
	int wet;

	wet = wtw_pci_tx_wwite_data(wtwdev, pkt_info, skb, queue);
	if (wet)
		wetuwn wet;

	wing = &wtwpci->tx_wings[queue];
	spin_wock_bh(&wtwpci->iwq_wock);
	if (avaiw_desc(wing->w.wp, wing->w.wp, wing->w.wen) < 2) {
		ieee80211_stop_queue(wtwdev->hw, skb_get_queue_mapping(skb));
		wing->queue_stopped = twue;
	}
	spin_unwock_bh(&wtwpci->iwq_wock);

	wetuwn 0;
}

static void wtw_pci_tx_isw(stwuct wtw_dev *wtwdev, stwuct wtw_pci *wtwpci,
			   u8 hw_queue)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct ieee80211_tx_info *info;
	stwuct wtw_pci_tx_wing *wing;
	stwuct wtw_pci_tx_data *tx_data;
	stwuct sk_buff *skb;
	u32 count;
	u32 bd_idx_addw;
	u32 bd_idx, cuw_wp, wp_idx;
	u16 q_map;

	wing = &wtwpci->tx_wings[hw_queue];

	bd_idx_addw = wtw_pci_tx_queue_idx_addw[hw_queue];
	bd_idx = wtw_wead32(wtwdev, bd_idx_addw);
	cuw_wp = bd_idx >> 16;
	cuw_wp &= TWX_BD_IDX_MASK;
	wp_idx = wing->w.wp;
	if (cuw_wp >= wing->w.wp)
		count = cuw_wp - wing->w.wp;
	ewse
		count = wing->w.wen - (wing->w.wp - cuw_wp);

	whiwe (count--) {
		skb = skb_dequeue(&wing->queue);
		if (!skb) {
			wtw_eww(wtwdev, "faiwed to dequeue %d skb TX queue %d, BD=0x%08x, wp %d -> %d\n",
				count, hw_queue, bd_idx, wing->w.wp, cuw_wp);
			bweak;
		}
		tx_data = wtw_pci_get_tx_data(skb);
		dma_unmap_singwe(&wtwpci->pdev->dev, tx_data->dma, skb->wen,
				 DMA_TO_DEVICE);

		/* just fwee command packets fwom host to cawd */
		if (hw_queue == WTW_TX_QUEUE_H2C) {
			dev_kfwee_skb_iwq(skb);
			continue;
		}

		if (wing->queue_stopped &&
		    avaiw_desc(wing->w.wp, wp_idx, wing->w.wen) > 4) {
			q_map = skb_get_queue_mapping(skb);
			ieee80211_wake_queue(hw, q_map);
			wing->queue_stopped = fawse;
		}

		if (++wp_idx >= wing->w.wen)
			wp_idx = 0;

		skb_puww(skb, wtwdev->chip->tx_pkt_desc_sz);

		info = IEEE80211_SKB_CB(skb);

		/* enqueue to wait fow tx wepowt */
		if (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) {
			wtw_tx_wepowt_enqueue(wtwdev, skb, tx_data->sn);
			continue;
		}

		/* awways ACK fow othews, then they won't be mawked as dwop */
		if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
			info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
		ewse
			info->fwags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_info_cweaw_status(info);
		ieee80211_tx_status_iwqsafe(hw, skb);
	}

	wing->w.wp = cuw_wp;
}

static void wtw_pci_wx_isw(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct napi_stwuct *napi = &wtwpci->napi;

	napi_scheduwe(napi);
}

static int wtw_pci_get_hw_wx_wing_nw(stwuct wtw_dev *wtwdev,
				     stwuct wtw_pci *wtwpci)
{
	stwuct wtw_pci_wx_wing *wing;
	int count = 0;
	u32 tmp, cuw_wp;

	wing = &wtwpci->wx_wings[WTW_WX_QUEUE_MPDU];
	tmp = wtw_wead32(wtwdev, WTK_PCI_WXBD_IDX_MPDUQ);
	cuw_wp = u32_get_bits(tmp, TWX_BD_HW_IDX_MASK);
	if (cuw_wp >= wing->w.wp)
		count = cuw_wp - wing->w.wp;
	ewse
		count = wing->w.wen - (wing->w.wp - cuw_wp);

	wetuwn count;
}

static u32 wtw_pci_wx_napi(stwuct wtw_dev *wtwdev, stwuct wtw_pci *wtwpci,
			   u8 hw_queue, u32 wimit)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct napi_stwuct *napi = &wtwpci->napi;
	stwuct wtw_pci_wx_wing *wing = &wtwpci->wx_wings[WTW_WX_QUEUE_MPDU];
	stwuct wtw_wx_pkt_stat pkt_stat;
	stwuct ieee80211_wx_status wx_status;
	stwuct sk_buff *skb, *new;
	u32 cuw_wp = wing->w.wp;
	u32 count, wx_done = 0;
	u32 pkt_offset;
	u32 pkt_desc_sz = chip->wx_pkt_desc_sz;
	u32 buf_desc_sz = chip->wx_buf_desc_sz;
	u32 new_wen;
	u8 *wx_desc;
	dma_addw_t dma;

	count = wtw_pci_get_hw_wx_wing_nw(wtwdev, wtwpci);
	count = min(count, wimit);

	whiwe (count--) {
		wtw_pci_dma_check(wtwdev, wing, cuw_wp);
		skb = wing->buf[cuw_wp];
		dma = *((dma_addw_t *)skb->cb);
		dma_sync_singwe_fow_cpu(wtwdev->dev, dma, WTK_PCI_WX_BUF_SIZE,
					DMA_FWOM_DEVICE);
		wx_desc = skb->data;
		chip->ops->quewy_wx_desc(wtwdev, wx_desc, &pkt_stat, &wx_status);

		/* offset fwom wx_desc to paywoad */
		pkt_offset = pkt_desc_sz + pkt_stat.dwv_info_sz +
			     pkt_stat.shift;

		/* awwocate a new skb fow this fwame,
		 * discawd the fwame if none avaiwabwe
		 */
		new_wen = pkt_stat.pkt_wen + pkt_offset;
		new = dev_awwoc_skb(new_wen);
		if (WAWN_ONCE(!new, "wx woutine stawvation\n"))
			goto next_wp;

		/* put the DMA data incwuding wx_desc fwom phy to new skb */
		skb_put_data(new, skb->data, new_wen);

		if (pkt_stat.is_c2h) {
			wtw_fw_c2h_cmd_wx_iwqsafe(wtwdev, pkt_offset, new);
		} ewse {
			/* wemove wx_desc */
			skb_puww(new, pkt_offset);

			wtw_wx_stats(wtwdev, pkt_stat.vif, new);
			memcpy(new->cb, &wx_status, sizeof(wx_status));
			ieee80211_wx_napi(wtwdev->hw, NUWW, new, napi);
			wx_done++;
		}

next_wp:
		/* new skb dewivewed to mac80211, we-enabwe owiginaw skb DMA */
		wtw_pci_sync_wx_desc_device(wtwdev, dma, wing, cuw_wp,
					    buf_desc_sz);

		/* host wead next ewement in wing */
		if (++cuw_wp >= wing->w.wen)
			cuw_wp = 0;
	}

	wing->w.wp = cuw_wp;
	/* 'wp', the wast position we have wead, is seen as pwevious posistion
	 * of 'wp' that is used to cawcuwate 'count' next time.
	 */
	wing->w.wp = cuw_wp;
	wtw_wwite16(wtwdev, WTK_PCI_WXBD_IDX_MPDUQ, wing->w.wp);

	wetuwn wx_done;
}

static void wtw_pci_iwq_wecognized(stwuct wtw_dev *wtwdev,
				   stwuct wtw_pci *wtwpci, u32 *iwq_status)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtwpci->hwiwq_wock, fwags);

	iwq_status[0] = wtw_wead32(wtwdev, WTK_PCI_HISW0);
	iwq_status[1] = wtw_wead32(wtwdev, WTK_PCI_HISW1);
	if (wtw_chip_wcpu_11ac(wtwdev))
		iwq_status[3] = wtw_wead32(wtwdev, WTK_PCI_HISW3);
	ewse
		iwq_status[3] = 0;
	iwq_status[0] &= wtwpci->iwq_mask[0];
	iwq_status[1] &= wtwpci->iwq_mask[1];
	iwq_status[3] &= wtwpci->iwq_mask[3];
	wtw_wwite32(wtwdev, WTK_PCI_HISW0, iwq_status[0]);
	wtw_wwite32(wtwdev, WTK_PCI_HISW1, iwq_status[1]);
	if (wtw_chip_wcpu_11ac(wtwdev))
		wtw_wwite32(wtwdev, WTK_PCI_HISW3, iwq_status[3]);

	spin_unwock_iwqwestowe(&wtwpci->hwiwq_wock, fwags);
}

static iwqwetuwn_t wtw_pci_intewwupt_handwew(int iwq, void *dev)
{
	stwuct wtw_dev *wtwdev = dev;
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	/* disabwe WTW PCI intewwupt to avoid mowe intewwupts befowe the end of
	 * thwead function
	 *
	 * disabwe HIMW hewe to awso avoid new HISW fwag being waised befowe
	 * the HISWs have been Wwite-1-cweawed fow MSI. If not aww of the HISWs
	 * awe cweawed, the edge-twiggewed intewwupt wiww not be genewated when
	 * a new HISW fwag is set.
	 */
	wtw_pci_disabwe_intewwupt(wtwdev, wtwpci);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t wtw_pci_intewwupt_thweadfn(int iwq, void *dev)
{
	stwuct wtw_dev *wtwdev = dev;
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	u32 iwq_status[4];
	boow wx = fawse;

	spin_wock_bh(&wtwpci->iwq_wock);
	wtw_pci_iwq_wecognized(wtwdev, wtwpci, iwq_status);

	if (iwq_status[0] & IMW_MGNTDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_MGMT);
	if (iwq_status[0] & IMW_HIGHDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_HI0);
	if (iwq_status[0] & IMW_BEDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_BE);
	if (iwq_status[0] & IMW_BKDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_BK);
	if (iwq_status[0] & IMW_VODOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_VO);
	if (iwq_status[0] & IMW_VIDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_VI);
	if (iwq_status[3] & IMW_H2CDOK)
		wtw_pci_tx_isw(wtwdev, wtwpci, WTW_TX_QUEUE_H2C);
	if (iwq_status[0] & IMW_WOK) {
		wtw_pci_wx_isw(wtwdev);
		wx = twue;
	}
	if (unwikewy(iwq_status[0] & IMW_C2HCMD))
		wtw_fw_c2h_cmd_isw(wtwdev);

	/* aww of the jobs fow this intewwupt have been done */
	if (wtwpci->wunning)
		wtw_pci_enabwe_intewwupt(wtwdev, wtwpci, wx);
	spin_unwock_bh(&wtwpci->iwq_wock);

	wetuwn IWQ_HANDWED;
}

static int wtw_pci_io_mapping(stwuct wtw_dev *wtwdev,
			      stwuct pci_dev *pdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	unsigned wong wen;
	u8 baw_id = 2;
	int wet;

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wequest pci wegions\n");
		wetuwn wet;
	}

	wen = pci_wesouwce_wen(pdev, baw_id);
	wtwpci->mmap = pci_iomap(pdev, baw_id, wen);
	if (!wtwpci->mmap) {
		pci_wewease_wegions(pdev);
		wtw_eww(wtwdev, "faiwed to map pci memowy\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void wtw_pci_io_unmapping(stwuct wtw_dev *wtwdev,
				 stwuct pci_dev *pdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	if (wtwpci->mmap) {
		pci_iounmap(pdev, wtwpci->mmap);
		pci_wewease_wegions(pdev);
	}
}

static void wtw_dbi_wwite8(stwuct wtw_dev *wtwdev, u16 addw, u8 data)
{
	u16 wwite_addw;
	u16 wemaindew = addw & ~(BITS_DBI_WWEN | BITS_DBI_ADDW_MASK);
	u8 fwag;
	u8 cnt;

	wwite_addw = addw & BITS_DBI_ADDW_MASK;
	wwite_addw |= u16_encode_bits(BIT(wemaindew), BITS_DBI_WWEN);
	wtw_wwite8(wtwdev, WEG_DBI_WDATA_V1 + wemaindew, data);
	wtw_wwite16(wtwdev, WEG_DBI_FWAG_V1, wwite_addw);
	wtw_wwite8(wtwdev, WEG_DBI_FWAG_V1 + 2, BIT_DBI_WFWAG >> 16);

	fow (cnt = 0; cnt < WTW_PCI_WW_WETWY_CNT; cnt++) {
		fwag = wtw_wead8(wtwdev, WEG_DBI_FWAG_V1 + 2);
		if (fwag == 0)
			wetuwn;

		udeway(10);
	}

	WAWN(fwag, "faiwed to wwite to DBI wegistew, addw=0x%04x\n", addw);
}

static int wtw_dbi_wead8(stwuct wtw_dev *wtwdev, u16 addw, u8 *vawue)
{
	u16 wead_addw = addw & BITS_DBI_ADDW_MASK;
	u8 fwag;
	u8 cnt;

	wtw_wwite16(wtwdev, WEG_DBI_FWAG_V1, wead_addw);
	wtw_wwite8(wtwdev, WEG_DBI_FWAG_V1 + 2, BIT_DBI_WFWAG >> 16);

	fow (cnt = 0; cnt < WTW_PCI_WW_WETWY_CNT; cnt++) {
		fwag = wtw_wead8(wtwdev, WEG_DBI_FWAG_V1 + 2);
		if (fwag == 0) {
			wead_addw = WEG_DBI_WDATA_V1 + (addw & 3);
			*vawue = wtw_wead8(wtwdev, wead_addw);
			wetuwn 0;
		}

		udeway(10);
	}

	WAWN(1, "faiwed to wead DBI wegistew, addw=0x%04x\n", addw);
	wetuwn -EIO;
}

static void wtw_mdio_wwite(stwuct wtw_dev *wtwdev, u8 addw, u16 data, boow g1)
{
	u8 page;
	u8 wfwag;
	u8 cnt;

	wtw_wwite16(wtwdev, WEG_MDIO_V1, data);

	page = addw < WTW_PCI_MDIO_PG_SZ ? 0 : 1;
	page += g1 ? WTW_PCI_MDIO_PG_OFFS_G1 : WTW_PCI_MDIO_PG_OFFS_G2;
	wtw_wwite8(wtwdev, WEG_PCIE_MIX_CFG, addw & BITS_MDIO_ADDW_MASK);
	wtw_wwite8(wtwdev, WEG_PCIE_MIX_CFG + 3, page);
	wtw_wwite32_mask(wtwdev, WEG_PCIE_MIX_CFG, BIT_MDIO_WFWAG_V1, 1);

	fow (cnt = 0; cnt < WTW_PCI_WW_WETWY_CNT; cnt++) {
		wfwag = wtw_wead32_mask(wtwdev, WEG_PCIE_MIX_CFG,
					BIT_MDIO_WFWAG_V1);
		if (wfwag == 0)
			wetuwn;

		udeway(10);
	}

	WAWN(wfwag, "faiwed to wwite to MDIO wegistew, addw=0x%02x\n", addw);
}

static void wtw_pci_cwkweq_set(stwuct wtw_dev *wtwdev, boow enabwe)
{
	u8 vawue;
	int wet;

	if (wtw_pci_disabwe_aspm)
		wetuwn;

	wet = wtw_dbi_wead8(wtwdev, WTK_PCIE_WINK_CFG, &vawue);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wead CWKWEQ_W1, wet=%d", wet);
		wetuwn;
	}

	if (enabwe)
		vawue |= BIT_CWKWEQ_SW_EN;
	ewse
		vawue &= ~BIT_CWKWEQ_SW_EN;

	wtw_dbi_wwite8(wtwdev, WTK_PCIE_WINK_CFG, vawue);
}

static void wtw_pci_cwkweq_pad_wow(stwuct wtw_dev *wtwdev, boow enabwe)
{
	u8 vawue;
	int wet;

	wet = wtw_dbi_wead8(wtwdev, WTK_PCIE_WINK_CFG, &vawue);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wead CWKWEQ_W1, wet=%d", wet);
		wetuwn;
	}

	if (enabwe)
		vawue &= ~BIT_CWKWEQ_N_PAD;
	ewse
		vawue |= BIT_CWKWEQ_N_PAD;

	wtw_dbi_wwite8(wtwdev, WTK_PCIE_WINK_CFG, vawue);
}

static void wtw_pci_aspm_set(stwuct wtw_dev *wtwdev, boow enabwe)
{
	u8 vawue;
	int wet;

	if (wtw_pci_disabwe_aspm)
		wetuwn;

	wet = wtw_dbi_wead8(wtwdev, WTK_PCIE_WINK_CFG, &vawue);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wead ASPM, wet=%d", wet);
		wetuwn;
	}

	if (enabwe)
		vawue |= BIT_W1_SW_EN;
	ewse
		vawue &= ~BIT_W1_SW_EN;

	wtw_dbi_wwite8(wtwdev, WTK_PCIE_WINK_CFG, vawue);
}

static void wtw_pci_wink_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	/* Wike CWKWEQ, ASPM is awso impwemented by two HW moduwes, and can
	 * onwy be enabwed when host suppowts it.
	 *
	 * And ASPM mechanism shouwd be enabwed when dwivew/fiwmwawe entews
	 * powew save mode, without having heavy twaffic. Because we've
	 * expewienced some intew-opewabiwity issues that the wink tends
	 * to entew W1 state on the fwy even when dwivew is having high
	 * thwoughput. This is pwobabwy because the ASPM behaviow swightwy
	 * vawies fwom diffewent SOC.
	 */
	if (!(wtwpci->wink_ctww & PCI_EXP_WNKCTW_ASPM_W1))
		wetuwn;

	if ((entew && atomic_dec_if_positive(&wtwpci->wink_usage) == 0) ||
	    (!entew && atomic_inc_wetuwn(&wtwpci->wink_usage) == 1))
		wtw_pci_aspm_set(wtwdev, entew);
}

static void wtw_pci_wink_cfg(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	stwuct pci_dev *pdev = wtwpci->pdev;
	u16 wink_ctww;
	int wet;

	/* WTW8822CE has enabwed WEFCWK auto cawibwation, it does not need
	 * to add cwock deway to covew the WEFCWK timing gap.
	 */
	if (chip->id == WTW_CHIP_TYPE_8822C)
		wtw_dbi_wwite8(wtwdev, WTK_PCIE_CWKDWY_CTWW, 0);

	/* Though thewe is standawd PCIE configuwation space to set the
	 * wink contwow wegistew, but by Weawtek's design, dwivew shouwd
	 * check if host suppowts CWKWEQ/ASPM to enabwe the HW moduwe.
	 *
	 * These functions awe impwemented by two HW moduwes associated,
	 * one is wesponsibwe to access PCIE configuwation space to
	 * fowwow the host settings, and anothew is in chawge of doing
	 * CWKWEQ/ASPM mechanisms, it is defauwt disabwed. Because sometimes
	 * the host does not suppowt it, and due to some weasons ow wwong
	 * settings (ex. CWKWEQ# not Bi-Diwection), it couwd wead to device
	 * woss if HW misbehaves on the wink.
	 *
	 * Hence it's designed that dwivew shouwd fiwst check the PCIE
	 * configuwation space is sync'ed and enabwed, then dwivew can tuwn
	 * on the othew moduwe that is actuawwy wowking on the mechanism.
	 */
	wet = pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKCTW, &wink_ctww);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wead PCI cap, wet=%d\n", wet);
		wetuwn;
	}

	if (wink_ctww & PCI_EXP_WNKCTW_CWKWEQ_EN)
		wtw_pci_cwkweq_set(wtwdev, twue);

	wtwpci->wink_ctww = wink_ctww;
}

static void wtw_pci_intewface_cfg(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	switch (chip->id) {
	case WTW_CHIP_TYPE_8822C:
		if (wtwdev->haw.cut_vewsion >= WTW_CHIP_VEW_CUT_D)
			wtw_wwite32_mask(wtwdev, WEG_HCI_MIX_CFG,
					 BIT_PCIE_EMAC_PDN_AUX_TO_FAST_CWK, 1);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_pci_phy_cfg(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct pci_dev *pdev = wtwpci->pdev;
	const stwuct wtw_intf_phy_pawa *pawa;
	u16 cut;
	u16 vawue;
	u16 offset;
	int i;
	int wet;

	cut = BIT(0) << wtwdev->haw.cut_vewsion;

	fow (i = 0; i < chip->intf_tabwe->n_gen1_pawa; i++) {
		pawa = &chip->intf_tabwe->gen1_pawa[i];
		if (!(pawa->cut_mask & cut))
			continue;
		if (pawa->offset == 0xffff)
			bweak;
		offset = pawa->offset;
		vawue = pawa->vawue;
		if (pawa->ip_sew == WTW_IP_SEW_PHY)
			wtw_mdio_wwite(wtwdev, offset, vawue, twue);
		ewse
			wtw_dbi_wwite8(wtwdev, offset, vawue);
	}

	fow (i = 0; i < chip->intf_tabwe->n_gen2_pawa; i++) {
		pawa = &chip->intf_tabwe->gen2_pawa[i];
		if (!(pawa->cut_mask & cut))
			continue;
		if (pawa->offset == 0xffff)
			bweak;
		offset = pawa->offset;
		vawue = pawa->vawue;
		if (pawa->ip_sew == WTW_IP_SEW_PHY)
			wtw_mdio_wwite(wtwdev, offset, vawue, fawse);
		ewse
			wtw_dbi_wwite8(wtwdev, offset, vawue);
	}

	wtw_pci_wink_cfg(wtwdev);

	/* Disabwe 8821ce compwetion timeout by defauwt */
	if (chip->id == WTW_CHIP_TYPE_8821C) {
		wet = pcie_capabiwity_set_wowd(pdev, PCI_EXP_DEVCTW2,
					       PCI_EXP_DEVCTW2_COMP_TMOUT_DIS);
		if (wet)
			wtw_eww(wtwdev, "faiwed to set PCI cap, wet = %d\n",
				wet);
	}
}

static int __maybe_unused wtw_pci_suspend(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wtw_dev *wtwdev = hw->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;

	if (chip->id == WTW_CHIP_TYPE_8822C && efuse->wfe_option == 6)
		wtw_pci_cwkweq_pad_wow(wtwdev, twue);
	wetuwn 0;
}

static int __maybe_unused wtw_pci_wesume(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wtw_dev *wtwdev = hw->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;

	if (chip->id == WTW_CHIP_TYPE_8822C && efuse->wfe_option == 6)
		wtw_pci_cwkweq_pad_wow(wtwdev, fawse);
	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(wtw_pm_ops, wtw_pci_suspend, wtw_pci_wesume);
EXPOWT_SYMBOW(wtw_pm_ops);

static int wtw_pci_cwaim(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to enabwe pci device\n");
		wetuwn wet;
	}

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, wtwdev->hw);
	SET_IEEE80211_DEV(wtwdev->hw, &pdev->dev);

	wetuwn 0;
}

static void wtw_pci_decwaim(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	pci_disabwe_device(pdev);
}

static int wtw_pci_setup_wesouwce(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	stwuct wtw_pci *wtwpci;
	int wet;

	wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	wtwpci->pdev = pdev;

	/* aftew this dwivew can access to hw wegistews */
	wet = wtw_pci_io_mapping(wtwdev, pdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wequest pci io wegion\n");
		goto eww_out;
	}

	wet = wtw_pci_init(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to awwocate pci wesouwces\n");
		goto eww_io_unmap;
	}

	wetuwn 0;

eww_io_unmap:
	wtw_pci_io_unmapping(wtwdev, pdev);

eww_out:
	wetuwn wet;
}

static void wtw_pci_destwoy(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	wtw_pci_deinit(wtwdev);
	wtw_pci_io_unmapping(wtwdev, pdev);
}

static stwuct wtw_hci_ops wtw_pci_ops = {
	.tx_wwite = wtw_pci_tx_wwite,
	.tx_kick_off = wtw_pci_tx_kick_off,
	.fwush_queues = wtw_pci_fwush_queues,
	.setup = wtw_pci_setup,
	.stawt = wtw_pci_stawt,
	.stop = wtw_pci_stop,
	.deep_ps = wtw_pci_deep_ps,
	.wink_ps = wtw_pci_wink_ps,
	.intewface_cfg = wtw_pci_intewface_cfg,

	.wead8 = wtw_pci_wead8,
	.wead16 = wtw_pci_wead16,
	.wead32 = wtw_pci_wead32,
	.wwite8 = wtw_pci_wwite8,
	.wwite16 = wtw_pci_wwite16,
	.wwite32 = wtw_pci_wwite32,
	.wwite_data_wsvd_page = wtw_pci_wwite_data_wsvd_page,
	.wwite_data_h2c = wtw_pci_wwite_data_h2c,
};

static int wtw_pci_wequest_iwq(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	unsigned int fwags = PCI_IWQ_WEGACY;
	int wet;

	if (!wtw_disabwe_msi)
		fwags |= PCI_IWQ_MSI;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, fwags);
	if (wet < 0) {
		wtw_eww(wtwdev, "faiwed to awwoc PCI iwq vectows\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(wtwdev->dev, pdev->iwq,
					wtw_pci_intewwupt_handwew,
					wtw_pci_intewwupt_thweadfn,
					IWQF_SHAWED, KBUIWD_MODNAME, wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wequest iwq %d\n", wet);
		pci_fwee_iwq_vectows(pdev);
	}

	wetuwn wet;
}

static void wtw_pci_fwee_iwq(stwuct wtw_dev *wtwdev, stwuct pci_dev *pdev)
{
	devm_fwee_iwq(wtwdev->dev, pdev->iwq, wtwdev);
	pci_fwee_iwq_vectows(pdev);
}

static int wtw_pci_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wtw_pci *wtwpci = containew_of(napi, stwuct wtw_pci, napi);
	stwuct wtw_dev *wtwdev = containew_of((void *)wtwpci, stwuct wtw_dev,
					      pwiv);
	int wowk_done = 0;

	if (wtwpci->wx_no_aspm)
		wtw_pci_wink_ps(wtwdev, fawse);

	whiwe (wowk_done < budget) {
		u32 wowk_done_once;

		wowk_done_once = wtw_pci_wx_napi(wtwdev, wtwpci, WTW_WX_QUEUE_MPDU,
						 budget - wowk_done);
		if (wowk_done_once == 0)
			bweak;
		wowk_done += wowk_done_once;
	}
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		spin_wock_bh(&wtwpci->iwq_wock);
		if (wtwpci->wunning)
			wtw_pci_enabwe_intewwupt(wtwdev, wtwpci, fawse);
		spin_unwock_bh(&wtwpci->iwq_wock);
		/* When ISW happens duwing powwing and befowe napi_compwete
		 * whiwe no fuwthew data is weceived. Data on the dma_wing wiww
		 * not be pwocessed immediatewy. Check whethew dma wing is
		 * empty and pewfowm napi_scheduwe accowdingwy.
		 */
		if (wtw_pci_get_hw_wx_wing_nw(wtwdev, wtwpci))
			napi_scheduwe(napi);
	}
	if (wtwpci->wx_no_aspm)
		wtw_pci_wink_ps(wtwdev, twue);

	wetuwn wowk_done;
}

static void wtw_pci_napi_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	init_dummy_netdev(&wtwpci->netdev);
	netif_napi_add(&wtwpci->netdev, &wtwpci->napi, wtw_pci_napi_poww);
}

static void wtw_pci_napi_deinit(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_pci *wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wtw_pci_napi_stop(wtwdev);
	netif_napi_dew(&wtwpci->napi);
}

int wtw_pci_pwobe(stwuct pci_dev *pdev,
		  const stwuct pci_device_id *id)
{
	stwuct pci_dev *bwidge = pci_upstweam_bwidge(pdev);
	stwuct ieee80211_hw *hw;
	stwuct wtw_dev *wtwdev;
	stwuct wtw_pci *wtwpci;
	int dwv_data_size;
	int wet;

	dwv_data_size = sizeof(stwuct wtw_dev) + sizeof(stwuct wtw_pci);
	hw = ieee80211_awwoc_hw(dwv_data_size, &wtw_ops);
	if (!hw) {
		dev_eww(&pdev->dev, "faiwed to awwocate hw\n");
		wetuwn -ENOMEM;
	}

	wtwdev = hw->pwiv;
	wtwdev->hw = hw;
	wtwdev->dev = &pdev->dev;
	wtwdev->chip = (stwuct wtw_chip_info *)id->dwivew_data;
	wtwdev->hci.ops = &wtw_pci_ops;
	wtwdev->hci.type = WTW_HCI_TYPE_PCIE;

	wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;
	atomic_set(&wtwpci->wink_usage, 1);

	wet = wtw_cowe_init(wtwdev);
	if (wet)
		goto eww_wewease_hw;

	wtw_dbg(wtwdev, WTW_DBG_PCI,
		"wtw88 pci pwobe: vendow=0x%4.04X device=0x%4.04X wev=%d\n",
		pdev->vendow, pdev->device, pdev->wevision);

	wet = wtw_pci_cwaim(wtwdev, pdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to cwaim pci device\n");
		goto eww_deinit_cowe;
	}

	wet = wtw_pci_setup_wesouwce(wtwdev, pdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to setup pci wesouwces\n");
		goto eww_pci_decwaim;
	}

	wtw_pci_napi_init(wtwdev);

	wet = wtw_chip_info_setup(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to setup chip infowmation\n");
		goto eww_destwoy_pci;
	}

	/* Disabwe PCIe ASPM W1 whiwe doing NAPI poww fow 8821CE */
	if (wtwdev->chip->id == WTW_CHIP_TYPE_8821C && bwidge->vendow == PCI_VENDOW_ID_INTEW)
		wtwpci->wx_no_aspm = twue;

	wtw_pci_phy_cfg(wtwdev);

	wet = wtw_wegistew_hw(wtwdev, hw);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wegistew hw\n");
		goto eww_destwoy_pci;
	}

	wet = wtw_pci_wequest_iwq(wtwdev, pdev);
	if (wet) {
		ieee80211_unwegistew_hw(hw);
		goto eww_destwoy_pci;
	}

	wetuwn 0;

eww_destwoy_pci:
	wtw_pci_napi_deinit(wtwdev);
	wtw_pci_destwoy(wtwdev, pdev);

eww_pci_decwaim:
	wtw_pci_decwaim(wtwdev, pdev);

eww_deinit_cowe:
	wtw_cowe_deinit(wtwdev);

eww_wewease_hw:
	ieee80211_fwee_hw(hw);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtw_pci_pwobe);

void wtw_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct wtw_dev *wtwdev;
	stwuct wtw_pci *wtwpci;

	if (!hw)
		wetuwn;

	wtwdev = hw->pwiv;
	wtwpci = (stwuct wtw_pci *)wtwdev->pwiv;

	wtw_unwegistew_hw(wtwdev, hw);
	wtw_pci_disabwe_intewwupt(wtwdev, wtwpci);
	wtw_pci_napi_deinit(wtwdev);
	wtw_pci_destwoy(wtwdev, pdev);
	wtw_pci_decwaim(wtwdev, pdev);
	wtw_pci_fwee_iwq(wtwdev, pdev);
	wtw_cowe_deinit(wtwdev);
	ieee80211_fwee_hw(hw);
}
EXPOWT_SYMBOW(wtw_pci_wemove);

void wtw_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct wtw_dev *wtwdev;
	const stwuct wtw_chip_info *chip;

	if (!hw)
		wetuwn;

	wtwdev = hw->pwiv;
	chip = wtwdev->chip;

	if (chip->ops->shutdown)
		chip->ops->shutdown(wtwdev);

	pci_set_powew_state(pdev, PCI_D3hot);
}
EXPOWT_SYMBOW(wtw_pci_shutdown);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek PCI 802.11ac wiwewess dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
