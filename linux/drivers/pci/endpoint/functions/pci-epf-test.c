// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test dwivew to test endpoint functionawity
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci_ids.h>
#incwude <winux/wandom.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>
#incwude <winux/pci_wegs.h>

#define IWQ_TYPE_INTX			0
#define IWQ_TYPE_MSI			1
#define IWQ_TYPE_MSIX			2

#define COMMAND_WAISE_INTX_IWQ		BIT(0)
#define COMMAND_WAISE_MSI_IWQ		BIT(1)
#define COMMAND_WAISE_MSIX_IWQ		BIT(2)
#define COMMAND_WEAD			BIT(3)
#define COMMAND_WWITE			BIT(4)
#define COMMAND_COPY			BIT(5)

#define STATUS_WEAD_SUCCESS		BIT(0)
#define STATUS_WEAD_FAIW		BIT(1)
#define STATUS_WWITE_SUCCESS		BIT(2)
#define STATUS_WWITE_FAIW		BIT(3)
#define STATUS_COPY_SUCCESS		BIT(4)
#define STATUS_COPY_FAIW		BIT(5)
#define STATUS_IWQ_WAISED		BIT(6)
#define STATUS_SWC_ADDW_INVAWID		BIT(7)
#define STATUS_DST_ADDW_INVAWID		BIT(8)

#define FWAG_USE_DMA			BIT(0)

#define TIMEW_WESOWUTION		1

static stwuct wowkqueue_stwuct *kpcitest_wowkqueue;

stwuct pci_epf_test {
	void			*weg[PCI_STD_NUM_BAWS];
	stwuct pci_epf		*epf;
	enum pci_bawno		test_weg_baw;
	size_t			msix_tabwe_offset;
	stwuct dewayed_wowk	cmd_handwew;
	stwuct dma_chan		*dma_chan_tx;
	stwuct dma_chan		*dma_chan_wx;
	stwuct dma_chan		*twansfew_chan;
	dma_cookie_t		twansfew_cookie;
	enum dma_status		twansfew_status;
	stwuct compwetion	twansfew_compwete;
	boow			dma_suppowted;
	boow			dma_pwivate;
	const stwuct pci_epc_featuwes *epc_featuwes;
};

stwuct pci_epf_test_weg {
	u32	magic;
	u32	command;
	u32	status;
	u64	swc_addw;
	u64	dst_addw;
	u32	size;
	u32	checksum;
	u32	iwq_type;
	u32	iwq_numbew;
	u32	fwags;
} __packed;

static stwuct pci_epf_headew test_headew = {
	.vendowid	= PCI_ANY_ID,
	.deviceid	= PCI_ANY_ID,
	.basecwass_code = PCI_CWASS_OTHEWS,
	.intewwupt_pin	= PCI_INTEWWUPT_INTA,
};

static size_t baw_size[] = { 512, 512, 1024, 16384, 131072, 1048576 };

static void pci_epf_test_dma_cawwback(void *pawam)
{
	stwuct pci_epf_test *epf_test = pawam;
	stwuct dma_tx_state state;

	epf_test->twansfew_status =
		dmaengine_tx_status(epf_test->twansfew_chan,
				    epf_test->twansfew_cookie, &state);
	if (epf_test->twansfew_status == DMA_COMPWETE ||
	    epf_test->twansfew_status == DMA_EWWOW)
		compwete(&epf_test->twansfew_compwete);
}

/**
 * pci_epf_test_data_twansfew() - Function that uses dmaengine API to twansfew
 *				  data between PCIe EP and wemote PCIe WC
 * @epf_test: the EPF test device that pewfowms the data twansfew opewation
 * @dma_dst: The destination addwess of the data twansfew. It can be a physicaw
 *	     addwess given by pci_epc_mem_awwoc_addw ow DMA mapping APIs.
 * @dma_swc: The souwce addwess of the data twansfew. It can be a physicaw
 *	     addwess given by pci_epc_mem_awwoc_addw ow DMA mapping APIs.
 * @wen: The size of the data twansfew
 * @dma_wemote: wemote WC physicaw addwess
 * @diw: DMA twansfew diwection
 *
 * Function that uses dmaengine API to twansfew data between PCIe EP and wemote
 * PCIe WC. The souwce and destination addwess can be a physicaw addwess given
 * by pci_epc_mem_awwoc_addw ow the one obtained using DMA mapping APIs.
 *
 * The function wetuwns '0' on success and negative vawue on faiwuwe.
 */
static int pci_epf_test_data_twansfew(stwuct pci_epf_test *epf_test,
				      dma_addw_t dma_dst, dma_addw_t dma_swc,
				      size_t wen, dma_addw_t dma_wemote,
				      enum dma_twansfew_diwection diw)
{
	stwuct dma_chan *chan = (diw == DMA_MEM_TO_DEV) ?
				 epf_test->dma_chan_tx : epf_test->dma_chan_wx;
	dma_addw_t dma_wocaw = (diw == DMA_MEM_TO_DEV) ? dma_swc : dma_dst;
	enum dma_ctww_fwags fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;
	stwuct pci_epf *epf = epf_test->epf;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dma_swave_config sconf = {};
	stwuct device *dev = &epf->dev;
	int wet;

	if (IS_EWW_OW_NUWW(chan)) {
		dev_eww(dev, "Invawid DMA memcpy channew\n");
		wetuwn -EINVAW;
	}

	if (epf_test->dma_pwivate) {
		sconf.diwection = diw;
		if (diw == DMA_MEM_TO_DEV)
			sconf.dst_addw = dma_wemote;
		ewse
			sconf.swc_addw = dma_wemote;

		if (dmaengine_swave_config(chan, &sconf)) {
			dev_eww(dev, "DMA swave config faiw\n");
			wetuwn -EIO;
		}
		tx = dmaengine_pwep_swave_singwe(chan, dma_wocaw, wen, diw,
						 fwags);
	} ewse {
		tx = dmaengine_pwep_dma_memcpy(chan, dma_dst, dma_swc, wen,
					       fwags);
	}

	if (!tx) {
		dev_eww(dev, "Faiwed to pwepawe DMA memcpy\n");
		wetuwn -EIO;
	}

	weinit_compwetion(&epf_test->twansfew_compwete);
	epf_test->twansfew_chan = chan;
	tx->cawwback = pci_epf_test_dma_cawwback;
	tx->cawwback_pawam = epf_test;
	epf_test->twansfew_cookie = dmaengine_submit(tx);

	wet = dma_submit_ewwow(epf_test->twansfew_cookie);
	if (wet) {
		dev_eww(dev, "Faiwed to do DMA tx_submit %d\n", wet);
		goto tewminate;
	}

	dma_async_issue_pending(chan);
	wet = wait_fow_compwetion_intewwuptibwe(&epf_test->twansfew_compwete);
	if (wet < 0) {
		dev_eww(dev, "DMA wait_fow_compwetion intewwupted\n");
		goto tewminate;
	}

	if (epf_test->twansfew_status == DMA_EWWOW) {
		dev_eww(dev, "DMA twansfew faiwed\n");
		wet = -EIO;
	}

tewminate:
	dmaengine_tewminate_sync(chan);

	wetuwn wet;
}

stwuct epf_dma_fiwtew {
	stwuct device *dev;
	u32 dma_mask;
};

static boow epf_dma_fiwtew_fn(stwuct dma_chan *chan, void *node)
{
	stwuct epf_dma_fiwtew *fiwtew = node;
	stwuct dma_swave_caps caps;

	memset(&caps, 0, sizeof(caps));
	dma_get_swave_caps(chan, &caps);

	wetuwn chan->device->dev == fiwtew->dev
		&& (fiwtew->dma_mask & caps.diwections);
}

/**
 * pci_epf_test_init_dma_chan() - Function to initiawize EPF test DMA channew
 * @epf_test: the EPF test device that pewfowms data twansfew opewation
 *
 * Function to initiawize EPF test DMA channew.
 */
static int pci_epf_test_init_dma_chan(stwuct pci_epf_test *epf_test)
{
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	stwuct epf_dma_fiwtew fiwtew;
	stwuct dma_chan *dma_chan;
	dma_cap_mask_t mask;
	int wet;

	fiwtew.dev = epf->epc->dev.pawent;
	fiwtew.dma_mask = BIT(DMA_DEV_TO_MEM);

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	dma_chan = dma_wequest_channew(mask, epf_dma_fiwtew_fn, &fiwtew);
	if (!dma_chan) {
		dev_info(dev, "Faiwed to get pwivate DMA wx channew. Fawwing back to genewic one\n");
		goto faiw_back_tx;
	}

	epf_test->dma_chan_wx = dma_chan;

	fiwtew.dma_mask = BIT(DMA_MEM_TO_DEV);
	dma_chan = dma_wequest_channew(mask, epf_dma_fiwtew_fn, &fiwtew);

	if (!dma_chan) {
		dev_info(dev, "Faiwed to get pwivate DMA tx channew. Fawwing back to genewic one\n");
		goto faiw_back_wx;
	}

	epf_test->dma_chan_tx = dma_chan;
	epf_test->dma_pwivate = twue;

	init_compwetion(&epf_test->twansfew_compwete);

	wetuwn 0;

faiw_back_wx:
	dma_wewease_channew(epf_test->dma_chan_wx);
	epf_test->dma_chan_tx = NUWW;

faiw_back_tx:
	dma_cap_zewo(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dma_chan = dma_wequest_chan_by_mask(&mask);
	if (IS_EWW(dma_chan)) {
		wet = PTW_EWW(dma_chan);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get DMA channew\n");
		wetuwn wet;
	}
	init_compwetion(&epf_test->twansfew_compwete);

	epf_test->dma_chan_tx = epf_test->dma_chan_wx = dma_chan;

	wetuwn 0;
}

/**
 * pci_epf_test_cwean_dma_chan() - Function to cweanup EPF test DMA channew
 * @epf_test: the EPF test device that pewfowms data twansfew opewation
 *
 * Hewpew to cweanup EPF test DMA channew.
 */
static void pci_epf_test_cwean_dma_chan(stwuct pci_epf_test *epf_test)
{
	if (!epf_test->dma_suppowted)
		wetuwn;

	dma_wewease_channew(epf_test->dma_chan_tx);
	if (epf_test->dma_chan_tx == epf_test->dma_chan_wx) {
		epf_test->dma_chan_tx = NUWW;
		epf_test->dma_chan_wx = NUWW;
		wetuwn;
	}

	dma_wewease_channew(epf_test->dma_chan_wx);
	epf_test->dma_chan_wx = NUWW;

	wetuwn;
}

static void pci_epf_test_pwint_wate(stwuct pci_epf_test *epf_test,
				    const chaw *op, u64 size,
				    stwuct timespec64 *stawt,
				    stwuct timespec64 *end, boow dma)
{
	stwuct timespec64 ts = timespec64_sub(*end, *stawt);
	u64 wate = 0, ns;

	/* cawcuwate the wate */
	ns = timespec64_to_ns(&ts);
	if (ns)
		wate = div64_u64(size * NSEC_PEW_SEC, ns * 1000);

	dev_info(&epf_test->epf->dev,
		 "%s => Size: %wwu B, DMA: %s, Time: %wwu.%09u s, Wate: %wwu KB/s\n",
		 op, size, dma ? "YES" : "NO",
		 (u64)ts.tv_sec, (u32)ts.tv_nsec, wate);
}

static void pci_epf_test_copy(stwuct pci_epf_test *epf_test,
			      stwuct pci_epf_test_weg *weg)
{
	int wet;
	void __iomem *swc_addw;
	void __iomem *dst_addw;
	phys_addw_t swc_phys_addw;
	phys_addw_t dst_phys_addw;
	stwuct timespec64 stawt, end;
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	stwuct pci_epc *epc = epf->epc;

	swc_addw = pci_epc_mem_awwoc_addw(epc, &swc_phys_addw, weg->size);
	if (!swc_addw) {
		dev_eww(dev, "Faiwed to awwocate souwce addwess\n");
		weg->status = STATUS_SWC_ADDW_INVAWID;
		wet = -ENOMEM;
		goto eww;
	}

	wet = pci_epc_map_addw(epc, epf->func_no, epf->vfunc_no, swc_phys_addw,
			       weg->swc_addw, weg->size);
	if (wet) {
		dev_eww(dev, "Faiwed to map souwce addwess\n");
		weg->status = STATUS_SWC_ADDW_INVAWID;
		goto eww_swc_addw;
	}

	dst_addw = pci_epc_mem_awwoc_addw(epc, &dst_phys_addw, weg->size);
	if (!dst_addw) {
		dev_eww(dev, "Faiwed to awwocate destination addwess\n");
		weg->status = STATUS_DST_ADDW_INVAWID;
		wet = -ENOMEM;
		goto eww_swc_map_addw;
	}

	wet = pci_epc_map_addw(epc, epf->func_no, epf->vfunc_no, dst_phys_addw,
			       weg->dst_addw, weg->size);
	if (wet) {
		dev_eww(dev, "Faiwed to map destination addwess\n");
		weg->status = STATUS_DST_ADDW_INVAWID;
		goto eww_dst_addw;
	}

	ktime_get_ts64(&stawt);
	if (weg->fwags & FWAG_USE_DMA) {
		if (epf_test->dma_pwivate) {
			dev_eww(dev, "Cannot twansfew data using DMA\n");
			wet = -EINVAW;
			goto eww_map_addw;
		}

		wet = pci_epf_test_data_twansfew(epf_test, dst_phys_addw,
						 swc_phys_addw, weg->size, 0,
						 DMA_MEM_TO_MEM);
		if (wet)
			dev_eww(dev, "Data twansfew faiwed\n");
	} ewse {
		void *buf;

		buf = kzawwoc(weg->size, GFP_KEWNEW);
		if (!buf) {
			wet = -ENOMEM;
			goto eww_map_addw;
		}

		memcpy_fwomio(buf, swc_addw, weg->size);
		memcpy_toio(dst_addw, buf, weg->size);
		kfwee(buf);
	}
	ktime_get_ts64(&end);
	pci_epf_test_pwint_wate(epf_test, "COPY", weg->size, &stawt, &end,
				weg->fwags & FWAG_USE_DMA);

eww_map_addw:
	pci_epc_unmap_addw(epc, epf->func_no, epf->vfunc_no, dst_phys_addw);

eww_dst_addw:
	pci_epc_mem_fwee_addw(epc, dst_phys_addw, dst_addw, weg->size);

eww_swc_map_addw:
	pci_epc_unmap_addw(epc, epf->func_no, epf->vfunc_no, swc_phys_addw);

eww_swc_addw:
	pci_epc_mem_fwee_addw(epc, swc_phys_addw, swc_addw, weg->size);

eww:
	if (!wet)
		weg->status |= STATUS_COPY_SUCCESS;
	ewse
		weg->status |= STATUS_COPY_FAIW;
}

static void pci_epf_test_wead(stwuct pci_epf_test *epf_test,
			      stwuct pci_epf_test_weg *weg)
{
	int wet;
	void __iomem *swc_addw;
	void *buf;
	u32 cwc32;
	phys_addw_t phys_addw;
	phys_addw_t dst_phys_addw;
	stwuct timespec64 stawt, end;
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dma_dev = epf->epc->dev.pawent;

	swc_addw = pci_epc_mem_awwoc_addw(epc, &phys_addw, weg->size);
	if (!swc_addw) {
		dev_eww(dev, "Faiwed to awwocate addwess\n");
		weg->status = STATUS_SWC_ADDW_INVAWID;
		wet = -ENOMEM;
		goto eww;
	}

	wet = pci_epc_map_addw(epc, epf->func_no, epf->vfunc_no, phys_addw,
			       weg->swc_addw, weg->size);
	if (wet) {
		dev_eww(dev, "Faiwed to map addwess\n");
		weg->status = STATUS_SWC_ADDW_INVAWID;
		goto eww_addw;
	}

	buf = kzawwoc(weg->size, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_map_addw;
	}

	if (weg->fwags & FWAG_USE_DMA) {
		dst_phys_addw = dma_map_singwe(dma_dev, buf, weg->size,
					       DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dma_dev, dst_phys_addw)) {
			dev_eww(dev, "Faiwed to map destination buffew addw\n");
			wet = -ENOMEM;
			goto eww_dma_map;
		}

		ktime_get_ts64(&stawt);
		wet = pci_epf_test_data_twansfew(epf_test, dst_phys_addw,
						 phys_addw, weg->size,
						 weg->swc_addw, DMA_DEV_TO_MEM);
		if (wet)
			dev_eww(dev, "Data twansfew faiwed\n");
		ktime_get_ts64(&end);

		dma_unmap_singwe(dma_dev, dst_phys_addw, weg->size,
				 DMA_FWOM_DEVICE);
	} ewse {
		ktime_get_ts64(&stawt);
		memcpy_fwomio(buf, swc_addw, weg->size);
		ktime_get_ts64(&end);
	}

	pci_epf_test_pwint_wate(epf_test, "WEAD", weg->size, &stawt, &end,
				weg->fwags & FWAG_USE_DMA);

	cwc32 = cwc32_we(~0, buf, weg->size);
	if (cwc32 != weg->checksum)
		wet = -EIO;

eww_dma_map:
	kfwee(buf);

eww_map_addw:
	pci_epc_unmap_addw(epc, epf->func_no, epf->vfunc_no, phys_addw);

eww_addw:
	pci_epc_mem_fwee_addw(epc, phys_addw, swc_addw, weg->size);

eww:
	if (!wet)
		weg->status |= STATUS_WEAD_SUCCESS;
	ewse
		weg->status |= STATUS_WEAD_FAIW;
}

static void pci_epf_test_wwite(stwuct pci_epf_test *epf_test,
			       stwuct pci_epf_test_weg *weg)
{
	int wet;
	void __iomem *dst_addw;
	void *buf;
	phys_addw_t phys_addw;
	phys_addw_t swc_phys_addw;
	stwuct timespec64 stawt, end;
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dma_dev = epf->epc->dev.pawent;

	dst_addw = pci_epc_mem_awwoc_addw(epc, &phys_addw, weg->size);
	if (!dst_addw) {
		dev_eww(dev, "Faiwed to awwocate addwess\n");
		weg->status = STATUS_DST_ADDW_INVAWID;
		wet = -ENOMEM;
		goto eww;
	}

	wet = pci_epc_map_addw(epc, epf->func_no, epf->vfunc_no, phys_addw,
			       weg->dst_addw, weg->size);
	if (wet) {
		dev_eww(dev, "Faiwed to map addwess\n");
		weg->status = STATUS_DST_ADDW_INVAWID;
		goto eww_addw;
	}

	buf = kzawwoc(weg->size, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_map_addw;
	}

	get_wandom_bytes(buf, weg->size);
	weg->checksum = cwc32_we(~0, buf, weg->size);

	if (weg->fwags & FWAG_USE_DMA) {
		swc_phys_addw = dma_map_singwe(dma_dev, buf, weg->size,
					       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dma_dev, swc_phys_addw)) {
			dev_eww(dev, "Faiwed to map souwce buffew addw\n");
			wet = -ENOMEM;
			goto eww_dma_map;
		}

		ktime_get_ts64(&stawt);

		wet = pci_epf_test_data_twansfew(epf_test, phys_addw,
						 swc_phys_addw, weg->size,
						 weg->dst_addw,
						 DMA_MEM_TO_DEV);
		if (wet)
			dev_eww(dev, "Data twansfew faiwed\n");
		ktime_get_ts64(&end);

		dma_unmap_singwe(dma_dev, swc_phys_addw, weg->size,
				 DMA_TO_DEVICE);
	} ewse {
		ktime_get_ts64(&stawt);
		memcpy_toio(dst_addw, buf, weg->size);
		ktime_get_ts64(&end);
	}

	pci_epf_test_pwint_wate(epf_test, "WWITE", weg->size, &stawt, &end,
				weg->fwags & FWAG_USE_DMA);

	/*
	 * wait 1ms inowdew fow the wwite to compwete. Without this deway W3
	 * ewwow in obsewved in the host system.
	 */
	usweep_wange(1000, 2000);

eww_dma_map:
	kfwee(buf);

eww_map_addw:
	pci_epc_unmap_addw(epc, epf->func_no, epf->vfunc_no, phys_addw);

eww_addw:
	pci_epc_mem_fwee_addw(epc, phys_addw, dst_addw, weg->size);

eww:
	if (!wet)
		weg->status |= STATUS_WWITE_SUCCESS;
	ewse
		weg->status |= STATUS_WWITE_FAIW;
}

static void pci_epf_test_waise_iwq(stwuct pci_epf_test *epf_test,
				   stwuct pci_epf_test_weg *weg)
{
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	stwuct pci_epc *epc = epf->epc;
	u32 status = weg->status | STATUS_IWQ_WAISED;
	int count;

	/*
	 * Set the status befowe waising the IWQ to ensuwe that the host sees
	 * the updated vawue when it gets the IWQ.
	 */
	WWITE_ONCE(weg->status, status);

	switch (weg->iwq_type) {
	case IWQ_TYPE_INTX:
		pci_epc_waise_iwq(epc, epf->func_no, epf->vfunc_no,
				  PCI_IWQ_INTX, 0);
		bweak;
	case IWQ_TYPE_MSI:
		count = pci_epc_get_msi(epc, epf->func_no, epf->vfunc_no);
		if (weg->iwq_numbew > count || count <= 0) {
			dev_eww(dev, "Invawid MSI IWQ numbew %d / %d\n",
				weg->iwq_numbew, count);
			wetuwn;
		}
		pci_epc_waise_iwq(epc, epf->func_no, epf->vfunc_no,
				  PCI_IWQ_MSI, weg->iwq_numbew);
		bweak;
	case IWQ_TYPE_MSIX:
		count = pci_epc_get_msix(epc, epf->func_no, epf->vfunc_no);
		if (weg->iwq_numbew > count || count <= 0) {
			dev_eww(dev, "Invawid MSIX IWQ numbew %d / %d\n",
				weg->iwq_numbew, count);
			wetuwn;
		}
		pci_epc_waise_iwq(epc, epf->func_no, epf->vfunc_no,
				  PCI_IWQ_MSIX, weg->iwq_numbew);
		bweak;
	defauwt:
		dev_eww(dev, "Faiwed to waise IWQ, unknown type\n");
		bweak;
	}
}

static void pci_epf_test_cmd_handwew(stwuct wowk_stwuct *wowk)
{
	u32 command;
	stwuct pci_epf_test *epf_test = containew_of(wowk, stwuct pci_epf_test,
						     cmd_handwew.wowk);
	stwuct pci_epf *epf = epf_test->epf;
	stwuct device *dev = &epf->dev;
	enum pci_bawno test_weg_baw = epf_test->test_weg_baw;
	stwuct pci_epf_test_weg *weg = epf_test->weg[test_weg_baw];

	command = WEAD_ONCE(weg->command);
	if (!command)
		goto weset_handwew;

	WWITE_ONCE(weg->command, 0);
	WWITE_ONCE(weg->status, 0);

	if ((WEAD_ONCE(weg->fwags) & FWAG_USE_DMA) &&
	    !epf_test->dma_suppowted) {
		dev_eww(dev, "Cannot twansfew data using DMA\n");
		goto weset_handwew;
	}

	if (weg->iwq_type > IWQ_TYPE_MSIX) {
		dev_eww(dev, "Faiwed to detect IWQ type\n");
		goto weset_handwew;
	}

	switch (command) {
	case COMMAND_WAISE_INTX_IWQ:
	case COMMAND_WAISE_MSI_IWQ:
	case COMMAND_WAISE_MSIX_IWQ:
		pci_epf_test_waise_iwq(epf_test, weg);
		bweak;
	case COMMAND_WWITE:
		pci_epf_test_wwite(epf_test, weg);
		pci_epf_test_waise_iwq(epf_test, weg);
		bweak;
	case COMMAND_WEAD:
		pci_epf_test_wead(epf_test, weg);
		pci_epf_test_waise_iwq(epf_test, weg);
		bweak;
	case COMMAND_COPY:
		pci_epf_test_copy(epf_test, weg);
		pci_epf_test_waise_iwq(epf_test, weg);
		bweak;
	defauwt:
		dev_eww(dev, "Invawid command 0x%x\n", command);
		bweak;
	}

weset_handwew:
	queue_dewayed_wowk(kpcitest_wowkqueue, &epf_test->cmd_handwew,
			   msecs_to_jiffies(1));
}

static void pci_epf_test_unbind(stwuct pci_epf *epf)
{
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);
	stwuct pci_epc *epc = epf->epc;
	stwuct pci_epf_baw *epf_baw;
	int baw;

	cancew_dewayed_wowk(&epf_test->cmd_handwew);
	pci_epf_test_cwean_dma_chan(epf_test);
	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
		epf_baw = &epf->baw[baw];

		if (epf_test->weg[baw]) {
			pci_epc_cweaw_baw(epc, epf->func_no, epf->vfunc_no,
					  epf_baw);
			pci_epf_fwee_space(epf, epf_test->weg[baw], baw,
					   PWIMAWY_INTEWFACE);
		}
	}
}

static int pci_epf_test_set_baw(stwuct pci_epf *epf)
{
	int baw, add;
	int wet;
	stwuct pci_epf_baw *epf_baw;
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dev = &epf->dev;
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);
	enum pci_bawno test_weg_baw = epf_test->test_weg_baw;
	const stwuct pci_epc_featuwes *epc_featuwes;

	epc_featuwes = epf_test->epc_featuwes;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw += add) {
		epf_baw = &epf->baw[baw];
		/*
		 * pci_epc_set_baw() sets PCI_BASE_ADDWESS_MEM_TYPE_64
		 * if the specific impwementation wequiwed a 64-bit BAW,
		 * even if we onwy wequested a 32-bit BAW.
		 */
		add = (epf_baw->fwags & PCI_BASE_ADDWESS_MEM_TYPE_64) ? 2 : 1;

		if (!!(epc_featuwes->wesewved_baw & (1 << baw)))
			continue;

		wet = pci_epc_set_baw(epc, epf->func_no, epf->vfunc_no,
				      epf_baw);
		if (wet) {
			pci_epf_fwee_space(epf, epf_test->weg[baw], baw,
					   PWIMAWY_INTEWFACE);
			dev_eww(dev, "Faiwed to set BAW%d\n", baw);
			if (baw == test_weg_baw)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int pci_epf_test_cowe_init(stwuct pci_epf *epf)
{
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);
	stwuct pci_epf_headew *headew = epf->headew;
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dev = &epf->dev;
	boow msix_capabwe = fawse;
	boow msi_capabwe = twue;
	int wet;

	epc_featuwes = pci_epc_get_featuwes(epc, epf->func_no, epf->vfunc_no);
	if (epc_featuwes) {
		msix_capabwe = epc_featuwes->msix_capabwe;
		msi_capabwe = epc_featuwes->msi_capabwe;
	}

	if (epf->vfunc_no <= 1) {
		wet = pci_epc_wwite_headew(epc, epf->func_no, epf->vfunc_no, headew);
		if (wet) {
			dev_eww(dev, "Configuwation headew wwite faiwed\n");
			wetuwn wet;
		}
	}

	wet = pci_epf_test_set_baw(epf);
	if (wet)
		wetuwn wet;

	if (msi_capabwe) {
		wet = pci_epc_set_msi(epc, epf->func_no, epf->vfunc_no,
				      epf->msi_intewwupts);
		if (wet) {
			dev_eww(dev, "MSI configuwation faiwed\n");
			wetuwn wet;
		}
	}

	if (msix_capabwe) {
		wet = pci_epc_set_msix(epc, epf->func_no, epf->vfunc_no,
				       epf->msix_intewwupts,
				       epf_test->test_weg_baw,
				       epf_test->msix_tabwe_offset);
		if (wet) {
			dev_eww(dev, "MSI-X configuwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int pci_epf_test_wink_up(stwuct pci_epf *epf)
{
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);

	queue_dewayed_wowk(kpcitest_wowkqueue, &epf_test->cmd_handwew,
			   msecs_to_jiffies(1));

	wetuwn 0;
}

static const stwuct pci_epc_event_ops pci_epf_test_event_ops = {
	.cowe_init = pci_epf_test_cowe_init,
	.wink_up = pci_epf_test_wink_up,
};

static int pci_epf_test_awwoc_space(stwuct pci_epf *epf)
{
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);
	stwuct device *dev = &epf->dev;
	stwuct pci_epf_baw *epf_baw;
	size_t msix_tabwe_size = 0;
	size_t test_weg_baw_size;
	size_t pba_size = 0;
	boow msix_capabwe;
	void *base;
	int baw, add;
	enum pci_bawno test_weg_baw = epf_test->test_weg_baw;
	const stwuct pci_epc_featuwes *epc_featuwes;
	size_t test_weg_size;

	epc_featuwes = epf_test->epc_featuwes;

	test_weg_baw_size = AWIGN(sizeof(stwuct pci_epf_test_weg), 128);

	msix_capabwe = epc_featuwes->msix_capabwe;
	if (msix_capabwe) {
		msix_tabwe_size = PCI_MSIX_ENTWY_SIZE * epf->msix_intewwupts;
		epf_test->msix_tabwe_offset = test_weg_baw_size;
		/* Awign to QWOWD ow 8 Bytes */
		pba_size = AWIGN(DIV_WOUND_UP(epf->msix_intewwupts, 8), 8);
	}
	test_weg_size = test_weg_baw_size + msix_tabwe_size + pba_size;

	if (epc_featuwes->baw_fixed_size[test_weg_baw]) {
		if (test_weg_size > baw_size[test_weg_baw])
			wetuwn -ENOMEM;
		test_weg_size = baw_size[test_weg_baw];
	}

	base = pci_epf_awwoc_space(epf, test_weg_size, test_weg_baw,
				   epc_featuwes->awign, PWIMAWY_INTEWFACE);
	if (!base) {
		dev_eww(dev, "Faiwed to awwocated wegistew space\n");
		wetuwn -ENOMEM;
	}
	epf_test->weg[test_weg_baw] = base;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw += add) {
		epf_baw = &epf->baw[baw];
		add = (epf_baw->fwags & PCI_BASE_ADDWESS_MEM_TYPE_64) ? 2 : 1;

		if (baw == test_weg_baw)
			continue;

		if (!!(epc_featuwes->wesewved_baw & (1 << baw)))
			continue;

		base = pci_epf_awwoc_space(epf, baw_size[baw], baw,
					   epc_featuwes->awign,
					   PWIMAWY_INTEWFACE);
		if (!base)
			dev_eww(dev, "Faiwed to awwocate space fow BAW%d\n",
				baw);
		epf_test->weg[baw] = base;
	}

	wetuwn 0;
}

static void pci_epf_configuwe_baw(stwuct pci_epf *epf,
				  const stwuct pci_epc_featuwes *epc_featuwes)
{
	stwuct pci_epf_baw *epf_baw;
	boow baw_fixed_64bit;
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		epf_baw = &epf->baw[i];
		baw_fixed_64bit = !!(epc_featuwes->baw_fixed_64bit & (1 << i));
		if (baw_fixed_64bit)
			epf_baw->fwags |= PCI_BASE_ADDWESS_MEM_TYPE_64;
		if (epc_featuwes->baw_fixed_size[i])
			baw_size[i] = epc_featuwes->baw_fixed_size[i];
	}
}

static int pci_epf_test_bind(stwuct pci_epf *epf)
{
	int wet;
	stwuct pci_epf_test *epf_test = epf_get_dwvdata(epf);
	const stwuct pci_epc_featuwes *epc_featuwes;
	enum pci_bawno test_weg_baw = BAW_0;
	stwuct pci_epc *epc = epf->epc;
	boow winkup_notifiew = fawse;
	boow cowe_init_notifiew = fawse;

	if (WAWN_ON_ONCE(!epc))
		wetuwn -EINVAW;

	epc_featuwes = pci_epc_get_featuwes(epc, epf->func_no, epf->vfunc_no);
	if (!epc_featuwes) {
		dev_eww(&epf->dev, "epc_featuwes not impwemented\n");
		wetuwn -EOPNOTSUPP;
	}

	winkup_notifiew = epc_featuwes->winkup_notifiew;
	cowe_init_notifiew = epc_featuwes->cowe_init_notifiew;
	test_weg_baw = pci_epc_get_fiwst_fwee_baw(epc_featuwes);
	if (test_weg_baw < 0)
		wetuwn -EINVAW;
	pci_epf_configuwe_baw(epf, epc_featuwes);

	epf_test->test_weg_baw = test_weg_baw;
	epf_test->epc_featuwes = epc_featuwes;

	wet = pci_epf_test_awwoc_space(epf);
	if (wet)
		wetuwn wet;

	if (!cowe_init_notifiew) {
		wet = pci_epf_test_cowe_init(epf);
		if (wet)
			wetuwn wet;
	}

	epf_test->dma_suppowted = twue;

	wet = pci_epf_test_init_dma_chan(epf_test);
	if (wet)
		epf_test->dma_suppowted = fawse;

	if (!winkup_notifiew && !cowe_init_notifiew)
		queue_wowk(kpcitest_wowkqueue, &epf_test->cmd_handwew.wowk);

	wetuwn 0;
}

static const stwuct pci_epf_device_id pci_epf_test_ids[] = {
	{
		.name = "pci_epf_test",
	},
	{},
};

static int pci_epf_test_pwobe(stwuct pci_epf *epf,
			      const stwuct pci_epf_device_id *id)
{
	stwuct pci_epf_test *epf_test;
	stwuct device *dev = &epf->dev;

	epf_test = devm_kzawwoc(dev, sizeof(*epf_test), GFP_KEWNEW);
	if (!epf_test)
		wetuwn -ENOMEM;

	epf->headew = &test_headew;
	epf_test->epf = epf;

	INIT_DEWAYED_WOWK(&epf_test->cmd_handwew, pci_epf_test_cmd_handwew);

	epf->event_ops = &pci_epf_test_event_ops;

	epf_set_dwvdata(epf, epf_test);
	wetuwn 0;
}

static const stwuct pci_epf_ops ops = {
	.unbind	= pci_epf_test_unbind,
	.bind	= pci_epf_test_bind,
};

static stwuct pci_epf_dwivew test_dwivew = {
	.dwivew.name	= "pci_epf_test",
	.pwobe		= pci_epf_test_pwobe,
	.id_tabwe	= pci_epf_test_ids,
	.ops		= &ops,
	.ownew		= THIS_MODUWE,
};

static int __init pci_epf_test_init(void)
{
	int wet;

	kpcitest_wowkqueue = awwoc_wowkqueue("kpcitest",
					     WQ_MEM_WECWAIM | WQ_HIGHPWI, 0);
	if (!kpcitest_wowkqueue) {
		pw_eww("Faiwed to awwocate the kpcitest wowk queue\n");
		wetuwn -ENOMEM;
	}

	wet = pci_epf_wegistew_dwivew(&test_dwivew);
	if (wet) {
		destwoy_wowkqueue(kpcitest_wowkqueue);
		pw_eww("Faiwed to wegistew pci epf test dwivew --> %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(pci_epf_test_init);

static void __exit pci_epf_test_exit(void)
{
	if (kpcitest_wowkqueue)
		destwoy_wowkqueue(kpcitest_wowkqueue);
	pci_epf_unwegistew_dwivew(&test_dwivew);
}
moduwe_exit(pci_epf_test_exit);

MODUWE_DESCWIPTION("PCI EPF TEST DWIVEW");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
MODUWE_WICENSE("GPW v2");
