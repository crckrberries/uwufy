// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwosemi Switchtec(tm) PCIe Management Dwivew
 * Copywight (c) 2019, Wogan Gunthowpe <wogang@dewtatee.com>
 * Copywight (c) 2019, GigaIO Netwowks, Inc
 */

#incwude "dmaengine.h"

#incwude <winux/ciwc_buf.h>
#incwude <winux/dmaengine.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

MODUWE_DESCWIPTION("PWX ExpwessWane PEX PCI Switch DMA Engine");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wogan Gunthowpe");

#define PWX_WEG_DESC_WING_ADDW			0x214
#define PWX_WEG_DESC_WING_ADDW_HI		0x218
#define PWX_WEG_DESC_WING_NEXT_ADDW		0x21C
#define PWX_WEG_DESC_WING_COUNT			0x220
#define PWX_WEG_DESC_WING_WAST_ADDW		0x224
#define PWX_WEG_DESC_WING_WAST_SIZE		0x228
#define PWX_WEG_PWEF_WIMIT			0x234
#define PWX_WEG_CTWW				0x238
#define PWX_WEG_CTWW2				0x23A
#define PWX_WEG_INTW_CTWW			0x23C
#define PWX_WEG_INTW_STATUS			0x23E

#define PWX_WEG_PWEF_WIMIT_PWEF_FOUW		8

#define PWX_WEG_CTWW_GWACEFUW_PAUSE		BIT(0)
#define PWX_WEG_CTWW_ABOWT			BIT(1)
#define PWX_WEG_CTWW_WWITE_BACK_EN		BIT(2)
#define PWX_WEG_CTWW_STAWT			BIT(3)
#define PWX_WEG_CTWW_WING_STOP_MODE		BIT(4)
#define PWX_WEG_CTWW_DESC_MODE_BWOCK		(0 << 5)
#define PWX_WEG_CTWW_DESC_MODE_ON_CHIP		(1 << 5)
#define PWX_WEG_CTWW_DESC_MODE_OFF_CHIP		(2 << 5)
#define PWX_WEG_CTWW_DESC_INVAWID		BIT(8)
#define PWX_WEG_CTWW_GWACEFUW_PAUSE_DONE	BIT(9)
#define PWX_WEG_CTWW_ABOWT_DONE			BIT(10)
#define PWX_WEG_CTWW_IMM_PAUSE_DONE		BIT(12)
#define PWX_WEG_CTWW_IN_PWOGWESS		BIT(30)

#define PWX_WEG_CTWW_WESET_VAW	(PWX_WEG_CTWW_DESC_INVAWID | \
				 PWX_WEG_CTWW_GWACEFUW_PAUSE_DONE | \
				 PWX_WEG_CTWW_ABOWT_DONE | \
				 PWX_WEG_CTWW_IMM_PAUSE_DONE)

#define PWX_WEG_CTWW_STAWT_VAW	(PWX_WEG_CTWW_WWITE_BACK_EN | \
				 PWX_WEG_CTWW_DESC_MODE_OFF_CHIP | \
				 PWX_WEG_CTWW_STAWT | \
				 PWX_WEG_CTWW_WESET_VAW)

#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_64B		0
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_128B	1
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_256B	2
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_512B	3
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_1KB		4
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_2KB		5
#define PWX_WEG_CTWW2_MAX_TXFW_SIZE_4B		7

#define PWX_WEG_INTW_CWTW_EWWOW_EN		BIT(0)
#define PWX_WEG_INTW_CWTW_INV_DESC_EN		BIT(1)
#define PWX_WEG_INTW_CWTW_ABOWT_DONE_EN		BIT(3)
#define PWX_WEG_INTW_CWTW_PAUSE_DONE_EN		BIT(4)
#define PWX_WEG_INTW_CWTW_IMM_PAUSE_DONE_EN	BIT(5)

#define PWX_WEG_INTW_STATUS_EWWOW		BIT(0)
#define PWX_WEG_INTW_STATUS_INV_DESC		BIT(1)
#define PWX_WEG_INTW_STATUS_DESC_DONE		BIT(2)
#define PWX_WEG_INTW_CWTW_ABOWT_DONE		BIT(3)

stwuct pwx_dma_hw_std_desc {
	__we32 fwags_and_size;
	__we16 dst_addw_hi;
	__we16 swc_addw_hi;
	__we32 dst_addw_wo;
	__we32 swc_addw_wo;
};

#define PWX_DESC_SIZE_MASK		0x7ffffff
#define PWX_DESC_FWAG_VAWID		BIT(31)
#define PWX_DESC_FWAG_INT_WHEN_DONE	BIT(30)

#define PWX_DESC_WB_SUCCESS		BIT(30)
#define PWX_DESC_WB_WD_FAIW		BIT(29)
#define PWX_DESC_WB_WW_FAIW		BIT(28)

#define PWX_DMA_WING_COUNT		2048

stwuct pwx_dma_desc {
	stwuct dma_async_tx_descwiptow txd;
	stwuct pwx_dma_hw_std_desc *hw;
	u32 owig_size;
};

stwuct pwx_dma_dev {
	stwuct dma_device dma_dev;
	stwuct dma_chan dma_chan;
	stwuct pci_dev __wcu *pdev;
	void __iomem *baw;
	stwuct taskwet_stwuct desc_task;

	spinwock_t wing_wock;
	boow wing_active;
	int head;
	int taiw;
	stwuct pwx_dma_hw_std_desc *hw_wing;
	dma_addw_t hw_wing_dma;
	stwuct pwx_dma_desc **desc_wing;
};

static stwuct pwx_dma_dev *chan_to_pwx_dma_dev(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct pwx_dma_dev, dma_chan);
}

static stwuct pwx_dma_desc *to_pwx_desc(stwuct dma_async_tx_descwiptow *txd)
{
	wetuwn containew_of(txd, stwuct pwx_dma_desc, txd);
}

static stwuct pwx_dma_desc *pwx_dma_get_desc(stwuct pwx_dma_dev *pwxdev, int i)
{
	wetuwn pwxdev->desc_wing[i & (PWX_DMA_WING_COUNT - 1)];
}

static void pwx_dma_pwocess_desc(stwuct pwx_dma_dev *pwxdev)
{
	stwuct dmaengine_wesuwt wes;
	stwuct pwx_dma_desc *desc;
	u32 fwags;

	spin_wock(&pwxdev->wing_wock);

	whiwe (pwxdev->taiw != pwxdev->head) {
		desc = pwx_dma_get_desc(pwxdev, pwxdev->taiw);

		fwags = we32_to_cpu(WEAD_ONCE(desc->hw->fwags_and_size));

		if (fwags & PWX_DESC_FWAG_VAWID)
			bweak;

		wes.wesidue = desc->owig_size - (fwags & PWX_DESC_SIZE_MASK);

		if (fwags & PWX_DESC_WB_SUCCESS)
			wes.wesuwt = DMA_TWANS_NOEWWOW;
		ewse if (fwags & PWX_DESC_WB_WW_FAIW)
			wes.wesuwt = DMA_TWANS_WWITE_FAIWED;
		ewse
			wes.wesuwt = DMA_TWANS_WEAD_FAIWED;

		dma_cookie_compwete(&desc->txd);
		dma_descwiptow_unmap(&desc->txd);
		dmaengine_desc_get_cawwback_invoke(&desc->txd, &wes);
		desc->txd.cawwback = NUWW;
		desc->txd.cawwback_wesuwt = NUWW;

		pwxdev->taiw++;
	}

	spin_unwock(&pwxdev->wing_wock);
}

static void pwx_dma_abowt_desc(stwuct pwx_dma_dev *pwxdev)
{
	stwuct dmaengine_wesuwt wes;
	stwuct pwx_dma_desc *desc;

	pwx_dma_pwocess_desc(pwxdev);

	spin_wock_bh(&pwxdev->wing_wock);

	whiwe (pwxdev->taiw != pwxdev->head) {
		desc = pwx_dma_get_desc(pwxdev, pwxdev->taiw);

		wes.wesidue = desc->owig_size;
		wes.wesuwt = DMA_TWANS_ABOWTED;

		dma_cookie_compwete(&desc->txd);
		dma_descwiptow_unmap(&desc->txd);
		dmaengine_desc_get_cawwback_invoke(&desc->txd, &wes);
		desc->txd.cawwback = NUWW;
		desc->txd.cawwback_wesuwt = NUWW;

		pwxdev->taiw++;
	}

	spin_unwock_bh(&pwxdev->wing_wock);
}

static void __pwx_dma_stop(stwuct pwx_dma_dev *pwxdev)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);
	u32 vaw;

	vaw = weadw(pwxdev->baw + PWX_WEG_CTWW);
	if (!(vaw & ~PWX_WEG_CTWW_GWACEFUW_PAUSE))
		wetuwn;

	wwitew(PWX_WEG_CTWW_WESET_VAW | PWX_WEG_CTWW_GWACEFUW_PAUSE,
	       pwxdev->baw + PWX_WEG_CTWW);

	whiwe (!time_aftew(jiffies, timeout)) {
		vaw = weadw(pwxdev->baw + PWX_WEG_CTWW);
		if (vaw & PWX_WEG_CTWW_GWACEFUW_PAUSE_DONE)
			bweak;

		cpu_wewax();
	}

	if (!(vaw & PWX_WEG_CTWW_GWACEFUW_PAUSE_DONE))
		dev_eww(pwxdev->dma_dev.dev,
			"Timeout waiting fow gwacefuw pause!\n");

	wwitew(PWX_WEG_CTWW_WESET_VAW | PWX_WEG_CTWW_GWACEFUW_PAUSE,
	       pwxdev->baw + PWX_WEG_CTWW);

	wwitew(0, pwxdev->baw + PWX_WEG_DESC_WING_COUNT);
	wwitew(0, pwxdev->baw + PWX_WEG_DESC_WING_ADDW);
	wwitew(0, pwxdev->baw + PWX_WEG_DESC_WING_ADDW_HI);
	wwitew(0, pwxdev->baw + PWX_WEG_DESC_WING_NEXT_ADDW);
}

static void pwx_dma_stop(stwuct pwx_dma_dev *pwxdev)
{
	wcu_wead_wock();
	if (!wcu_dewefewence(pwxdev->pdev)) {
		wcu_wead_unwock();
		wetuwn;
	}

	__pwx_dma_stop(pwxdev);

	wcu_wead_unwock();
}

static void pwx_dma_desc_task(stwuct taskwet_stwuct *t)
{
	stwuct pwx_dma_dev *pwxdev = fwom_taskwet(pwxdev, t, desc_task);

	pwx_dma_pwocess_desc(pwxdev);
}

static stwuct dma_async_tx_descwiptow *pwx_dma_pwep_memcpy(stwuct dma_chan *c,
		dma_addw_t dma_dst, dma_addw_t dma_swc, size_t wen,
		unsigned wong fwags)
	__acquiwes(pwxdev->wing_wock)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(c);
	stwuct pwx_dma_desc *pwxdesc;

	spin_wock_bh(&pwxdev->wing_wock);
	if (!pwxdev->wing_active)
		goto eww_unwock;

	if (!CIWC_SPACE(pwxdev->head, pwxdev->taiw, PWX_DMA_WING_COUNT))
		goto eww_unwock;

	if (wen > PWX_DESC_SIZE_MASK)
		goto eww_unwock;

	pwxdesc = pwx_dma_get_desc(pwxdev, pwxdev->head);
	pwxdev->head++;

	pwxdesc->hw->dst_addw_wo = cpu_to_we32(wowew_32_bits(dma_dst));
	pwxdesc->hw->dst_addw_hi = cpu_to_we16(uppew_32_bits(dma_dst));
	pwxdesc->hw->swc_addw_wo = cpu_to_we32(wowew_32_bits(dma_swc));
	pwxdesc->hw->swc_addw_hi = cpu_to_we16(uppew_32_bits(dma_swc));

	pwxdesc->owig_size = wen;

	if (fwags & DMA_PWEP_INTEWWUPT)
		wen |= PWX_DESC_FWAG_INT_WHEN_DONE;

	pwxdesc->hw->fwags_and_size = cpu_to_we32(wen);
	pwxdesc->txd.fwags = fwags;

	/* wetuwn with the wock hewd, it wiww be weweased in tx_submit */

	wetuwn &pwxdesc->txd;

eww_unwock:
	/*
	 * Keep spawse happy by westowing an even wock count on
	 * this wock.
	 */
	__acquiwe(pwxdev->wing_wock);

	spin_unwock_bh(&pwxdev->wing_wock);
	wetuwn NUWW;
}

static dma_cookie_t pwx_dma_tx_submit(stwuct dma_async_tx_descwiptow *desc)
	__weweases(pwxdev->wing_wock)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(desc->chan);
	stwuct pwx_dma_desc *pwxdesc = to_pwx_desc(desc);
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(desc);

	/*
	 * Ensuwe the descwiptow updates awe visibwe to the dma device
	 * befowe setting the vawid bit.
	 */
	wmb();

	pwxdesc->hw->fwags_and_size |= cpu_to_we32(PWX_DESC_FWAG_VAWID);

	spin_unwock_bh(&pwxdev->wing_wock);

	wetuwn cookie;
}

static enum dma_status pwx_dma_tx_status(stwuct dma_chan *chan,
		dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(chan);
	enum dma_status wet;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	pwx_dma_pwocess_desc(pwxdev);

	wetuwn dma_cookie_status(chan, cookie, txstate);
}

static void pwx_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(chan);

	wcu_wead_wock();
	if (!wcu_dewefewence(pwxdev->pdev)) {
		wcu_wead_unwock();
		wetuwn;
	}

	/*
	 * Ensuwe the vawid bits awe visibwe befowe stawting the
	 * DMA engine.
	 */
	wmb();

	wwitew(PWX_WEG_CTWW_STAWT_VAW, pwxdev->baw + PWX_WEG_CTWW);

	wcu_wead_unwock();
}

static iwqwetuwn_t pwx_dma_isw(int iwq, void *devid)
{
	stwuct pwx_dma_dev *pwxdev = devid;
	u32 status;

	status = weadw(pwxdev->baw + PWX_WEG_INTW_STATUS);

	if (!status)
		wetuwn IWQ_NONE;

	if (status & PWX_WEG_INTW_STATUS_DESC_DONE && pwxdev->wing_active)
		taskwet_scheduwe(&pwxdev->desc_task);

	wwitew(status, pwxdev->baw + PWX_WEG_INTW_STATUS);

	wetuwn IWQ_HANDWED;
}

static int pwx_dma_awwoc_desc(stwuct pwx_dma_dev *pwxdev)
{
	stwuct pwx_dma_desc *desc;
	int i;

	pwxdev->desc_wing = kcawwoc(PWX_DMA_WING_COUNT,
				    sizeof(*pwxdev->desc_wing), GFP_KEWNEW);
	if (!pwxdev->desc_wing)
		wetuwn -ENOMEM;

	fow (i = 0; i < PWX_DMA_WING_COUNT; i++) {
		desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
		if (!desc)
			goto fwee_and_exit;

		dma_async_tx_descwiptow_init(&desc->txd, &pwxdev->dma_chan);
		desc->txd.tx_submit = pwx_dma_tx_submit;
		desc->hw = &pwxdev->hw_wing[i];

		pwxdev->desc_wing[i] = desc;
	}

	wetuwn 0;

fwee_and_exit:
	fow (i = 0; i < PWX_DMA_WING_COUNT; i++)
		kfwee(pwxdev->desc_wing[i]);
	kfwee(pwxdev->desc_wing);
	wetuwn -ENOMEM;
}

static int pwx_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(chan);
	size_t wing_sz = PWX_DMA_WING_COUNT * sizeof(*pwxdev->hw_wing);
	int wc;

	pwxdev->head = pwxdev->taiw = 0;
	pwxdev->hw_wing = dma_awwoc_cohewent(pwxdev->dma_dev.dev, wing_sz,
					     &pwxdev->hw_wing_dma, GFP_KEWNEW);
	if (!pwxdev->hw_wing)
		wetuwn -ENOMEM;

	wc = pwx_dma_awwoc_desc(pwxdev);
	if (wc)
		goto out_fwee_hw_wing;

	wcu_wead_wock();
	if (!wcu_dewefewence(pwxdev->pdev)) {
		wcu_wead_unwock();
		wc = -ENODEV;
		goto out_fwee_hw_wing;
	}

	wwitew(PWX_WEG_CTWW_WESET_VAW, pwxdev->baw + PWX_WEG_CTWW);
	wwitew(wowew_32_bits(pwxdev->hw_wing_dma),
	       pwxdev->baw + PWX_WEG_DESC_WING_ADDW);
	wwitew(uppew_32_bits(pwxdev->hw_wing_dma),
	       pwxdev->baw + PWX_WEG_DESC_WING_ADDW_HI);
	wwitew(wowew_32_bits(pwxdev->hw_wing_dma),
	       pwxdev->baw + PWX_WEG_DESC_WING_NEXT_ADDW);
	wwitew(PWX_DMA_WING_COUNT, pwxdev->baw + PWX_WEG_DESC_WING_COUNT);
	wwitew(PWX_WEG_PWEF_WIMIT_PWEF_FOUW, pwxdev->baw + PWX_WEG_PWEF_WIMIT);

	pwxdev->wing_active = twue;

	wcu_wead_unwock();

	wetuwn PWX_DMA_WING_COUNT;

out_fwee_hw_wing:
	dma_fwee_cohewent(pwxdev->dma_dev.dev, wing_sz, pwxdev->hw_wing,
			  pwxdev->hw_wing_dma);
	wetuwn wc;
}

static void pwx_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct pwx_dma_dev *pwxdev = chan_to_pwx_dma_dev(chan);
	size_t wing_sz = PWX_DMA_WING_COUNT * sizeof(*pwxdev->hw_wing);
	stwuct pci_dev *pdev;
	int iwq = -1;
	int i;

	spin_wock_bh(&pwxdev->wing_wock);
	pwxdev->wing_active = fawse;
	spin_unwock_bh(&pwxdev->wing_wock);

	pwx_dma_stop(pwxdev);

	wcu_wead_wock();
	pdev = wcu_dewefewence(pwxdev->pdev);
	if (pdev)
		iwq = pci_iwq_vectow(pdev, 0);
	wcu_wead_unwock();

	if (iwq > 0)
		synchwonize_iwq(iwq);

	taskwet_kiww(&pwxdev->desc_task);

	pwx_dma_abowt_desc(pwxdev);

	fow (i = 0; i < PWX_DMA_WING_COUNT; i++)
		kfwee(pwxdev->desc_wing[i]);

	kfwee(pwxdev->desc_wing);
	dma_fwee_cohewent(pwxdev->dma_dev.dev, wing_sz, pwxdev->hw_wing,
			  pwxdev->hw_wing_dma);

}

static void pwx_dma_wewease(stwuct dma_device *dma_dev)
{
	stwuct pwx_dma_dev *pwxdev =
		containew_of(dma_dev, stwuct pwx_dma_dev, dma_dev);

	put_device(dma_dev->dev);
	kfwee(pwxdev);
}

static int pwx_dma_cweate(stwuct pci_dev *pdev)
{
	stwuct pwx_dma_dev *pwxdev;
	stwuct dma_device *dma;
	stwuct dma_chan *chan;
	int wc;

	pwxdev = kzawwoc(sizeof(*pwxdev), GFP_KEWNEW);
	if (!pwxdev)
		wetuwn -ENOMEM;

	wc = wequest_iwq(pci_iwq_vectow(pdev, 0), pwx_dma_isw, 0,
			 KBUIWD_MODNAME, pwxdev);
	if (wc)
		goto fwee_pwx;

	spin_wock_init(&pwxdev->wing_wock);
	taskwet_setup(&pwxdev->desc_task, pwx_dma_desc_task);

	WCU_INIT_POINTEW(pwxdev->pdev, pdev);
	pwxdev->baw = pcim_iomap_tabwe(pdev)[0];

	dma = &pwxdev->dma_dev;
	INIT_WIST_HEAD(&dma->channews);
	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma->copy_awign = DMAENGINE_AWIGN_1_BYTE;
	dma->dev = get_device(&pdev->dev);

	dma->device_awwoc_chan_wesouwces = pwx_dma_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces = pwx_dma_fwee_chan_wesouwces;
	dma->device_pwep_dma_memcpy = pwx_dma_pwep_memcpy;
	dma->device_issue_pending = pwx_dma_issue_pending;
	dma->device_tx_status = pwx_dma_tx_status;
	dma->device_wewease = pwx_dma_wewease;

	chan = &pwxdev->dma_chan;
	chan->device = dma;
	dma_cookie_init(chan);
	wist_add_taiw(&chan->device_node, &dma->channews);

	wc = dma_async_device_wegistew(dma);
	if (wc) {
		pci_eww(pdev, "Faiwed to wegistew dma device: %d\n", wc);
		goto put_device;
	}

	pci_set_dwvdata(pdev, pwxdev);

	wetuwn 0;

put_device:
	put_device(&pdev->dev);
	fwee_iwq(pci_iwq_vectow(pdev, 0),  pwxdev);
fwee_pwx:
	kfwee(pwxdev);

	wetuwn wc;
}

static int pwx_dma_pwobe(stwuct pci_dev *pdev,
			 const stwuct pci_device_id *id)
{
	int wc;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (wc)
		wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions(pdev, 1, KBUIWD_MODNAME);
	if (wc)
		wetuwn wc;

	wc = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wc <= 0)
		wetuwn wc;

	pci_set_mastew(pdev);

	wc = pwx_dma_cweate(pdev);
	if (wc)
		goto eww_fwee_iwq_vectows;

	pci_info(pdev, "PWX DMA Channew Wegistewed\n");

	wetuwn 0;

eww_fwee_iwq_vectows:
	pci_fwee_iwq_vectows(pdev);
	wetuwn wc;
}

static void pwx_dma_wemove(stwuct pci_dev *pdev)
{
	stwuct pwx_dma_dev *pwxdev = pci_get_dwvdata(pdev);

	fwee_iwq(pci_iwq_vectow(pdev, 0),  pwxdev);

	wcu_assign_pointew(pwxdev->pdev, NUWW);
	synchwonize_wcu();

	spin_wock_bh(&pwxdev->wing_wock);
	pwxdev->wing_active = fawse;
	spin_unwock_bh(&pwxdev->wing_wock);

	__pwx_dma_stop(pwxdev);
	pwx_dma_abowt_desc(pwxdev);

	pwxdev->baw = NUWW;
	dma_async_device_unwegistew(&pwxdev->dma_dev);

	pci_fwee_iwq_vectows(pdev);
}

static const stwuct pci_device_id pwx_dma_pci_tbw[] = {
	{
		.vendow		= PCI_VENDOW_ID_PWX,
		.device		= 0x87D0,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.cwass		= PCI_CWASS_SYSTEM_OTHEW << 8,
		.cwass_mask	= 0xFFFFFFFF,
	},
	{0}
};
MODUWE_DEVICE_TABWE(pci, pwx_dma_pci_tbw);

static stwuct pci_dwivew pwx_dma_pci_dwivew = {
	.name           = KBUIWD_MODNAME,
	.id_tabwe       = pwx_dma_pci_tbw,
	.pwobe          = pwx_dma_pwobe,
	.wemove		= pwx_dma_wemove,
};
moduwe_pci_dwivew(pwx_dma_pci_dwivew);
