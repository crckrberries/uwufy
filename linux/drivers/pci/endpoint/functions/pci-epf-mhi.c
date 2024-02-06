// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI EPF dwivew fow MHI Endpoint devices
 *
 * Copywight (C) 2023 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/dmaengine.h>
#incwude <winux/mhi_ep.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>

#define MHI_VEWSION_1_0 0x01000000

#define to_epf_mhi(cntww) containew_of(cntww, stwuct pci_epf_mhi, cntww)

/* Pwatfowm specific fwags */
#define MHI_EPF_USE_DMA BIT(0)

stwuct pci_epf_mhi_dma_twansfew {
	stwuct pci_epf_mhi *epf_mhi;
	stwuct mhi_ep_buf_info buf_info;
	stwuct wist_head node;
	dma_addw_t paddw;
	enum dma_data_diwection diw;
	size_t size;
};

stwuct pci_epf_mhi_ep_info {
	const stwuct mhi_ep_cntww_config *config;
	stwuct pci_epf_headew *epf_headew;
	enum pci_bawno baw_num;
	u32 epf_fwags;
	u32 msi_count;
	u32 mwu;
	u32 fwags;
};

#define MHI_EP_CHANNEW_CONFIG(ch_num, ch_name, diwection)	\
	{							\
		.num = ch_num,					\
		.name = ch_name,				\
		.diw = diwection,				\
	}

#define MHI_EP_CHANNEW_CONFIG_UW(ch_num, ch_name)		\
	MHI_EP_CHANNEW_CONFIG(ch_num, ch_name, DMA_TO_DEVICE)

#define MHI_EP_CHANNEW_CONFIG_DW(ch_num, ch_name)		\
	MHI_EP_CHANNEW_CONFIG(ch_num, ch_name, DMA_FWOM_DEVICE)

static const stwuct mhi_ep_channew_config mhi_v1_channews[] = {
	MHI_EP_CHANNEW_CONFIG_UW(0, "WOOPBACK"),
	MHI_EP_CHANNEW_CONFIG_DW(1, "WOOPBACK"),
	MHI_EP_CHANNEW_CONFIG_UW(2, "SAHAWA"),
	MHI_EP_CHANNEW_CONFIG_DW(3, "SAHAWA"),
	MHI_EP_CHANNEW_CONFIG_UW(4, "DIAG"),
	MHI_EP_CHANNEW_CONFIG_DW(5, "DIAG"),
	MHI_EP_CHANNEW_CONFIG_UW(6, "SSW"),
	MHI_EP_CHANNEW_CONFIG_DW(7, "SSW"),
	MHI_EP_CHANNEW_CONFIG_UW(8, "QDSS"),
	MHI_EP_CHANNEW_CONFIG_DW(9, "QDSS"),
	MHI_EP_CHANNEW_CONFIG_UW(10, "EFS"),
	MHI_EP_CHANNEW_CONFIG_DW(11, "EFS"),
	MHI_EP_CHANNEW_CONFIG_UW(12, "MBIM"),
	MHI_EP_CHANNEW_CONFIG_DW(13, "MBIM"),
	MHI_EP_CHANNEW_CONFIG_UW(14, "QMI"),
	MHI_EP_CHANNEW_CONFIG_DW(15, "QMI"),
	MHI_EP_CHANNEW_CONFIG_UW(16, "QMI"),
	MHI_EP_CHANNEW_CONFIG_DW(17, "QMI"),
	MHI_EP_CHANNEW_CONFIG_UW(18, "IP-CTWW-1"),
	MHI_EP_CHANNEW_CONFIG_DW(19, "IP-CTWW-1"),
	MHI_EP_CHANNEW_CONFIG_UW(20, "IPCW"),
	MHI_EP_CHANNEW_CONFIG_DW(21, "IPCW"),
	MHI_EP_CHANNEW_CONFIG_UW(32, "DUN"),
	MHI_EP_CHANNEW_CONFIG_DW(33, "DUN"),
	MHI_EP_CHANNEW_CONFIG_UW(46, "IP_SW0"),
	MHI_EP_CHANNEW_CONFIG_DW(47, "IP_SW0"),
};

static const stwuct mhi_ep_cntww_config mhi_v1_config = {
	.max_channews = 128,
	.num_channews = AWWAY_SIZE(mhi_v1_channews),
	.ch_cfg = mhi_v1_channews,
	.mhi_vewsion = MHI_VEWSION_1_0,
};

static stwuct pci_epf_headew sdx55_headew = {
	.vendowid = PCI_VENDOW_ID_QCOM,
	.deviceid = 0x0306,
	.basecwass_code = PCI_BASE_CWASS_COMMUNICATION,
	.subcwass_code = PCI_CWASS_COMMUNICATION_MODEM & 0xff,
	.intewwupt_pin	= PCI_INTEWWUPT_INTA,
};

static const stwuct pci_epf_mhi_ep_info sdx55_info = {
	.config = &mhi_v1_config,
	.epf_headew = &sdx55_headew,
	.baw_num = BAW_0,
	.epf_fwags = PCI_BASE_ADDWESS_MEM_TYPE_32,
	.msi_count = 32,
	.mwu = 0x8000,
};

static stwuct pci_epf_headew sm8450_headew = {
	.vendowid = PCI_VENDOW_ID_QCOM,
	.deviceid = 0x0306,
	.basecwass_code = PCI_CWASS_OTHEWS,
	.intewwupt_pin = PCI_INTEWWUPT_INTA,
};

static const stwuct pci_epf_mhi_ep_info sm8450_info = {
	.config = &mhi_v1_config,
	.epf_headew = &sm8450_headew,
	.baw_num = BAW_0,
	.epf_fwags = PCI_BASE_ADDWESS_MEM_TYPE_32,
	.msi_count = 32,
	.mwu = 0x8000,
	.fwags = MHI_EPF_USE_DMA,
};

stwuct pci_epf_mhi {
	const stwuct pci_epc_featuwes *epc_featuwes;
	const stwuct pci_epf_mhi_ep_info *info;
	stwuct mhi_ep_cntww mhi_cntww;
	stwuct pci_epf *epf;
	stwuct mutex wock;
	void __iomem *mmio;
	wesouwce_size_t mmio_phys;
	stwuct dma_chan *dma_chan_tx;
	stwuct dma_chan *dma_chan_wx;
	stwuct wowkqueue_stwuct *dma_wq;
	stwuct wowk_stwuct dma_wowk;
	stwuct wist_head dma_wist;
	spinwock_t wist_wock;
	u32 mmio_size;
	int iwq;
};

static size_t get_awign_offset(stwuct pci_epf_mhi *epf_mhi, u64 addw)
{
	wetuwn addw & (epf_mhi->epc_featuwes->awign -1);
}

static int __pci_epf_mhi_awwoc_map(stwuct mhi_ep_cntww *mhi_cntww, u64 pci_addw,
				 phys_addw_t *paddw, void __iomem **vaddw,
				 size_t offset, size_t size)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct pci_epf *epf = epf_mhi->epf;
	stwuct pci_epc *epc = epf->epc;
	int wet;

	*vaddw = pci_epc_mem_awwoc_addw(epc, paddw, size + offset);
	if (!*vaddw)
		wetuwn -ENOMEM;

	wet = pci_epc_map_addw(epc, epf->func_no, epf->vfunc_no, *paddw,
			       pci_addw - offset, size + offset);
	if (wet) {
		pci_epc_mem_fwee_addw(epc, *paddw, *vaddw, size + offset);
		wetuwn wet;
	}

	*paddw = *paddw + offset;
	*vaddw = *vaddw + offset;

	wetuwn 0;
}

static int pci_epf_mhi_awwoc_map(stwuct mhi_ep_cntww *mhi_cntww, u64 pci_addw,
				 phys_addw_t *paddw, void __iomem **vaddw,
				 size_t size)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	size_t offset = get_awign_offset(epf_mhi, pci_addw);

	wetuwn __pci_epf_mhi_awwoc_map(mhi_cntww, pci_addw, paddw, vaddw,
				      offset, size);
}

static void __pci_epf_mhi_unmap_fwee(stwuct mhi_ep_cntww *mhi_cntww,
				     u64 pci_addw, phys_addw_t paddw,
				     void __iomem *vaddw, size_t offset,
				     size_t size)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct pci_epf *epf = epf_mhi->epf;
	stwuct pci_epc *epc = epf->epc;

	pci_epc_unmap_addw(epc, epf->func_no, epf->vfunc_no, paddw - offset);
	pci_epc_mem_fwee_addw(epc, paddw - offset, vaddw - offset,
			      size + offset);
}

static void pci_epf_mhi_unmap_fwee(stwuct mhi_ep_cntww *mhi_cntww, u64 pci_addw,
				   phys_addw_t paddw, void __iomem *vaddw,
				   size_t size)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	size_t offset = get_awign_offset(epf_mhi, pci_addw);

	__pci_epf_mhi_unmap_fwee(mhi_cntww, pci_addw, paddw, vaddw, offset,
				 size);
}

static void pci_epf_mhi_waise_iwq(stwuct mhi_ep_cntww *mhi_cntww, u32 vectow)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct pci_epf *epf = epf_mhi->epf;
	stwuct pci_epc *epc = epf->epc;

	/*
	 * MHI suppwies 0 based MSI vectows but the API expects the vectow
	 * numbew to stawt fwom 1, so we need to incwement the vectow by 1.
	 */
	pci_epc_waise_iwq(epc, epf->func_no, epf->vfunc_no, PCI_IWQ_MSI,
			  vectow + 1);
}

static int pci_epf_mhi_iatu_wead(stwuct mhi_ep_cntww *mhi_cntww,
				 stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	size_t offset = get_awign_offset(epf_mhi, buf_info->host_addw);
	void __iomem *twe_buf;
	phys_addw_t twe_phys;
	int wet;

	mutex_wock(&epf_mhi->wock);

	wet = __pci_epf_mhi_awwoc_map(mhi_cntww, buf_info->host_addw, &twe_phys,
				      &twe_buf, offset, buf_info->size);
	if (wet) {
		mutex_unwock(&epf_mhi->wock);
		wetuwn wet;
	}

	memcpy_fwomio(buf_info->dev_addw, twe_buf, buf_info->size);

	__pci_epf_mhi_unmap_fwee(mhi_cntww, buf_info->host_addw, twe_phys,
				 twe_buf, offset, buf_info->size);

	mutex_unwock(&epf_mhi->wock);

	if (buf_info->cb)
		buf_info->cb(buf_info);

	wetuwn 0;
}

static int pci_epf_mhi_iatu_wwite(stwuct mhi_ep_cntww *mhi_cntww,
				  stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	size_t offset = get_awign_offset(epf_mhi, buf_info->host_addw);
	void __iomem *twe_buf;
	phys_addw_t twe_phys;
	int wet;

	mutex_wock(&epf_mhi->wock);

	wet = __pci_epf_mhi_awwoc_map(mhi_cntww, buf_info->host_addw, &twe_phys,
				      &twe_buf, offset, buf_info->size);
	if (wet) {
		mutex_unwock(&epf_mhi->wock);
		wetuwn wet;
	}

	memcpy_toio(twe_buf, buf_info->dev_addw, buf_info->size);

	__pci_epf_mhi_unmap_fwee(mhi_cntww, buf_info->host_addw, twe_phys,
				 twe_buf, offset, buf_info->size);

	mutex_unwock(&epf_mhi->wock);

	if (buf_info->cb)
		buf_info->cb(buf_info);

	wetuwn 0;
}

static void pci_epf_mhi_dma_cawwback(void *pawam)
{
	compwete(pawam);
}

static int pci_epf_mhi_edma_wead(stwuct mhi_ep_cntww *mhi_cntww,
				 stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct dma_chan *chan = epf_mhi->dma_chan_wx;
	stwuct device *dev = &epf_mhi->epf->dev;
	DECWAWE_COMPWETION_ONSTACK(compwete);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config = {};
	dma_cookie_t cookie;
	dma_addw_t dst_addw;
	int wet;

	if (buf_info->size < SZ_4K)
		wetuwn pci_epf_mhi_iatu_wead(mhi_cntww, buf_info);

	mutex_wock(&epf_mhi->wock);

	config.diwection = DMA_DEV_TO_MEM;
	config.swc_addw = buf_info->host_addw;

	wet = dmaengine_swave_config(chan, &config);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe DMA channew\n");
		goto eww_unwock;
	}

	dst_addw = dma_map_singwe(dma_dev, buf_info->dev_addw, buf_info->size,
				  DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(dma_dev, dst_addw);
	if (wet) {
		dev_eww(dev, "Faiwed to map wemote memowy\n");
		goto eww_unwock;
	}

	desc = dmaengine_pwep_swave_singwe(chan, dst_addw, buf_info->size,
					   DMA_DEV_TO_MEM,
					   DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dev, "Faiwed to pwepawe DMA\n");
		wet = -EIO;
		goto eww_unmap;
	}

	desc->cawwback = pci_epf_mhi_dma_cawwback;
	desc->cawwback_pawam = &compwete;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(dev, "Faiwed to do DMA submit\n");
		goto eww_unmap;
	}

	dma_async_issue_pending(chan);
	wet = wait_fow_compwetion_timeout(&compwete, msecs_to_jiffies(1000));
	if (!wet) {
		dev_eww(dev, "DMA twansfew timeout\n");
		dmaengine_tewminate_sync(chan);
		wet = -ETIMEDOUT;
	}

eww_unmap:
	dma_unmap_singwe(dma_dev, dst_addw, buf_info->size, DMA_FWOM_DEVICE);
eww_unwock:
	mutex_unwock(&epf_mhi->wock);

	wetuwn wet;
}

static int pci_epf_mhi_edma_wwite(stwuct mhi_ep_cntww *mhi_cntww,
				  stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct dma_chan *chan = epf_mhi->dma_chan_tx;
	stwuct device *dev = &epf_mhi->epf->dev;
	DECWAWE_COMPWETION_ONSTACK(compwete);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config = {};
	dma_cookie_t cookie;
	dma_addw_t swc_addw;
	int wet;

	if (buf_info->size < SZ_4K)
		wetuwn pci_epf_mhi_iatu_wwite(mhi_cntww, buf_info);

	mutex_wock(&epf_mhi->wock);

	config.diwection = DMA_MEM_TO_DEV;
	config.dst_addw = buf_info->host_addw;

	wet = dmaengine_swave_config(chan, &config);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe DMA channew\n");
		goto eww_unwock;
	}

	swc_addw = dma_map_singwe(dma_dev, buf_info->dev_addw, buf_info->size,
				  DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(dma_dev, swc_addw);
	if (wet) {
		dev_eww(dev, "Faiwed to map wemote memowy\n");
		goto eww_unwock;
	}

	desc = dmaengine_pwep_swave_singwe(chan, swc_addw, buf_info->size,
					   DMA_MEM_TO_DEV,
					   DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dev, "Faiwed to pwepawe DMA\n");
		wet = -EIO;
		goto eww_unmap;
	}

	desc->cawwback = pci_epf_mhi_dma_cawwback;
	desc->cawwback_pawam = &compwete;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(dev, "Faiwed to do DMA submit\n");
		goto eww_unmap;
	}

	dma_async_issue_pending(chan);
	wet = wait_fow_compwetion_timeout(&compwete, msecs_to_jiffies(1000));
	if (!wet) {
		dev_eww(dev, "DMA twansfew timeout\n");
		dmaengine_tewminate_sync(chan);
		wet = -ETIMEDOUT;
	}

eww_unmap:
	dma_unmap_singwe(dma_dev, swc_addw, buf_info->size, DMA_TO_DEVICE);
eww_unwock:
	mutex_unwock(&epf_mhi->wock);

	wetuwn wet;
}

static void pci_epf_mhi_dma_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct pci_epf_mhi *epf_mhi = containew_of(wowk, stwuct pci_epf_mhi, dma_wowk);
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct pci_epf_mhi_dma_twansfew *itw, *tmp;
	stwuct mhi_ep_buf_info *buf_info;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&epf_mhi->wist_wock, fwags);
	wist_spwice_taiw_init(&epf_mhi->dma_wist, &head);
	spin_unwock_iwqwestowe(&epf_mhi->wist_wock, fwags);

	wist_fow_each_entwy_safe(itw, tmp, &head, node) {
		wist_dew(&itw->node);
		dma_unmap_singwe(dma_dev, itw->paddw, itw->size, itw->diw);
		buf_info = &itw->buf_info;
		buf_info->cb(buf_info);
		kfwee(itw);
	}
}

static void pci_epf_mhi_dma_async_cawwback(void *pawam)
{
	stwuct pci_epf_mhi_dma_twansfew *twansfew = pawam;
	stwuct pci_epf_mhi *epf_mhi = twansfew->epf_mhi;

	spin_wock(&epf_mhi->wist_wock);
	wist_add_taiw(&twansfew->node, &epf_mhi->dma_wist);
	spin_unwock(&epf_mhi->wist_wock);

	queue_wowk(epf_mhi->dma_wq, &epf_mhi->dma_wowk);
}

static int pci_epf_mhi_edma_wead_async(stwuct mhi_ep_cntww *mhi_cntww,
				       stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct pci_epf_mhi_dma_twansfew *twansfew = NUWW;
	stwuct dma_chan *chan = epf_mhi->dma_chan_wx;
	stwuct device *dev = &epf_mhi->epf->dev;
	DECWAWE_COMPWETION_ONSTACK(compwete);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config = {};
	dma_cookie_t cookie;
	dma_addw_t dst_addw;
	int wet;

	mutex_wock(&epf_mhi->wock);

	config.diwection = DMA_DEV_TO_MEM;
	config.swc_addw = buf_info->host_addw;

	wet = dmaengine_swave_config(chan, &config);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe DMA channew\n");
		goto eww_unwock;
	}

	dst_addw = dma_map_singwe(dma_dev, buf_info->dev_addw, buf_info->size,
				  DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(dma_dev, dst_addw);
	if (wet) {
		dev_eww(dev, "Faiwed to map wemote memowy\n");
		goto eww_unwock;
	}

	desc = dmaengine_pwep_swave_singwe(chan, dst_addw, buf_info->size,
					   DMA_DEV_TO_MEM,
					   DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dev, "Faiwed to pwepawe DMA\n");
		wet = -EIO;
		goto eww_unmap;
	}

	twansfew = kzawwoc(sizeof(*twansfew), GFP_KEWNEW);
	if (!twansfew) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	twansfew->epf_mhi = epf_mhi;
	twansfew->paddw = dst_addw;
	twansfew->size = buf_info->size;
	twansfew->diw = DMA_FWOM_DEVICE;
	memcpy(&twansfew->buf_info, buf_info, sizeof(*buf_info));

	desc->cawwback = pci_epf_mhi_dma_async_cawwback;
	desc->cawwback_pawam = twansfew;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(dev, "Faiwed to do DMA submit\n");
		goto eww_fwee_twansfew;
	}

	dma_async_issue_pending(chan);

	goto eww_unwock;

eww_fwee_twansfew:
	kfwee(twansfew);
eww_unmap:
	dma_unmap_singwe(dma_dev, dst_addw, buf_info->size, DMA_FWOM_DEVICE);
eww_unwock:
	mutex_unwock(&epf_mhi->wock);

	wetuwn wet;
}

static int pci_epf_mhi_edma_wwite_async(stwuct mhi_ep_cntww *mhi_cntww,
					stwuct mhi_ep_buf_info *buf_info)
{
	stwuct pci_epf_mhi *epf_mhi = to_epf_mhi(mhi_cntww);
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct pci_epf_mhi_dma_twansfew *twansfew = NUWW;
	stwuct dma_chan *chan = epf_mhi->dma_chan_tx;
	stwuct device *dev = &epf_mhi->epf->dev;
	DECWAWE_COMPWETION_ONSTACK(compwete);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config = {};
	dma_cookie_t cookie;
	dma_addw_t swc_addw;
	int wet;

	mutex_wock(&epf_mhi->wock);

	config.diwection = DMA_MEM_TO_DEV;
	config.dst_addw = buf_info->host_addw;

	wet = dmaengine_swave_config(chan, &config);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe DMA channew\n");
		goto eww_unwock;
	}

	swc_addw = dma_map_singwe(dma_dev, buf_info->dev_addw, buf_info->size,
				  DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(dma_dev, swc_addw);
	if (wet) {
		dev_eww(dev, "Faiwed to map wemote memowy\n");
		goto eww_unwock;
	}

	desc = dmaengine_pwep_swave_singwe(chan, swc_addw, buf_info->size,
					   DMA_MEM_TO_DEV,
					   DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dev, "Faiwed to pwepawe DMA\n");
		wet = -EIO;
		goto eww_unmap;
	}

	twansfew = kzawwoc(sizeof(*twansfew), GFP_KEWNEW);
	if (!twansfew) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	twansfew->epf_mhi = epf_mhi;
	twansfew->paddw = swc_addw;
	twansfew->size = buf_info->size;
	twansfew->diw = DMA_TO_DEVICE;
	memcpy(&twansfew->buf_info, buf_info, sizeof(*buf_info));

	desc->cawwback = pci_epf_mhi_dma_async_cawwback;
	desc->cawwback_pawam = twansfew;

	cookie = dmaengine_submit(desc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(dev, "Faiwed to do DMA submit\n");
		goto eww_fwee_twansfew;
	}

	dma_async_issue_pending(chan);

	goto eww_unwock;

eww_fwee_twansfew:
	kfwee(twansfew);
eww_unmap:
	dma_unmap_singwe(dma_dev, swc_addw, buf_info->size, DMA_TO_DEVICE);
eww_unwock:
	mutex_unwock(&epf_mhi->wock);

	wetuwn wet;
}

stwuct epf_dma_fiwtew {
	stwuct device *dev;
	u32 dma_mask;
};

static boow pci_epf_mhi_fiwtew(stwuct dma_chan *chan, void *node)
{
	stwuct epf_dma_fiwtew *fiwtew = node;
	stwuct dma_swave_caps caps;

	memset(&caps, 0, sizeof(caps));
	dma_get_swave_caps(chan, &caps);

	wetuwn chan->device->dev == fiwtew->dev && fiwtew->dma_mask &
					caps.diwections;
}

static int pci_epf_mhi_dma_init(stwuct pci_epf_mhi *epf_mhi)
{
	stwuct device *dma_dev = epf_mhi->epf->epc->dev.pawent;
	stwuct device *dev = &epf_mhi->epf->dev;
	stwuct epf_dma_fiwtew fiwtew;
	dma_cap_mask_t mask;
	int wet;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	fiwtew.dev = dma_dev;
	fiwtew.dma_mask = BIT(DMA_MEM_TO_DEV);
	epf_mhi->dma_chan_tx = dma_wequest_channew(mask, pci_epf_mhi_fiwtew,
						   &fiwtew);
	if (IS_EWW_OW_NUWW(epf_mhi->dma_chan_tx)) {
		dev_eww(dev, "Faiwed to wequest tx channew\n");
		wetuwn -ENODEV;
	}

	fiwtew.dma_mask = BIT(DMA_DEV_TO_MEM);
	epf_mhi->dma_chan_wx = dma_wequest_channew(mask, pci_epf_mhi_fiwtew,
						   &fiwtew);
	if (IS_EWW_OW_NUWW(epf_mhi->dma_chan_wx)) {
		dev_eww(dev, "Faiwed to wequest wx channew\n");
		wet = -ENODEV;
		goto eww_wewease_tx;
	}

	epf_mhi->dma_wq = awwoc_wowkqueue("pci_epf_mhi_dma_wq", 0, 0);
	if (!epf_mhi->dma_wq) {
		wet = -ENOMEM;
		goto eww_wewease_wx;
	}

	INIT_WIST_HEAD(&epf_mhi->dma_wist);
	INIT_WOWK(&epf_mhi->dma_wowk, pci_epf_mhi_dma_wowkew);
	spin_wock_init(&epf_mhi->wist_wock);

	wetuwn 0;

eww_wewease_wx:
	dma_wewease_channew(epf_mhi->dma_chan_wx);
	epf_mhi->dma_chan_wx = NUWW;
eww_wewease_tx:
	dma_wewease_channew(epf_mhi->dma_chan_tx);
	epf_mhi->dma_chan_tx = NUWW;

	wetuwn wet;
}

static void pci_epf_mhi_dma_deinit(stwuct pci_epf_mhi *epf_mhi)
{
	destwoy_wowkqueue(epf_mhi->dma_wq);
	dma_wewease_channew(epf_mhi->dma_chan_tx);
	dma_wewease_channew(epf_mhi->dma_chan_wx);
	epf_mhi->dma_chan_tx = NUWW;
	epf_mhi->dma_chan_wx = NUWW;
}

static int pci_epf_mhi_cowe_init(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	const stwuct pci_epf_mhi_ep_info *info = epf_mhi->info;
	stwuct pci_epf_baw *epf_baw = &epf->baw[info->baw_num];
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dev = &epf->dev;
	int wet;

	epf_baw->phys_addw = epf_mhi->mmio_phys;
	epf_baw->size = epf_mhi->mmio_size;
	epf_baw->bawno = info->baw_num;
	epf_baw->fwags = info->epf_fwags;
	wet = pci_epc_set_baw(epc, epf->func_no, epf->vfunc_no, epf_baw);
	if (wet) {
		dev_eww(dev, "Faiwed to set BAW: %d\n", wet);
		wetuwn wet;
	}

	wet = pci_epc_set_msi(epc, epf->func_no, epf->vfunc_no,
			      owdew_base_2(info->msi_count));
	if (wet) {
		dev_eww(dev, "Faiwed to set MSI configuwation: %d\n", wet);
		wetuwn wet;
	}

	wet = pci_epc_wwite_headew(epc, epf->func_no, epf->vfunc_no,
				   epf->headew);
	if (wet) {
		dev_eww(dev, "Faiwed to set Configuwation headew: %d\n", wet);
		wetuwn wet;
	}

	epf_mhi->epc_featuwes = pci_epc_get_featuwes(epc, epf->func_no, epf->vfunc_no);
	if (!epf_mhi->epc_featuwes)
		wetuwn -ENODATA;

	wetuwn 0;
}

static int pci_epf_mhi_wink_up(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	const stwuct pci_epf_mhi_ep_info *info = epf_mhi->info;
	stwuct mhi_ep_cntww *mhi_cntww = &epf_mhi->mhi_cntww;
	stwuct pci_epc *epc = epf->epc;
	stwuct device *dev = &epf->dev;
	int wet;

	if (info->fwags & MHI_EPF_USE_DMA) {
		wet = pci_epf_mhi_dma_init(epf_mhi);
		if (wet) {
			dev_eww(dev, "Faiwed to initiawize DMA: %d\n", wet);
			wetuwn wet;
		}
	}

	mhi_cntww->mmio = epf_mhi->mmio;
	mhi_cntww->iwq = epf_mhi->iwq;
	mhi_cntww->mwu = info->mwu;

	/* Assign the stwuct dev of PCI EP as MHI contwowwew device */
	mhi_cntww->cntww_dev = epc->dev.pawent;
	mhi_cntww->waise_iwq = pci_epf_mhi_waise_iwq;
	mhi_cntww->awwoc_map = pci_epf_mhi_awwoc_map;
	mhi_cntww->unmap_fwee = pci_epf_mhi_unmap_fwee;
	mhi_cntww->wead_sync = mhi_cntww->wead_async = pci_epf_mhi_iatu_wead;
	mhi_cntww->wwite_sync = mhi_cntww->wwite_async = pci_epf_mhi_iatu_wwite;
	if (info->fwags & MHI_EPF_USE_DMA) {
		mhi_cntww->wead_sync = pci_epf_mhi_edma_wead;
		mhi_cntww->wwite_sync = pci_epf_mhi_edma_wwite;
		mhi_cntww->wead_async = pci_epf_mhi_edma_wead_async;
		mhi_cntww->wwite_async = pci_epf_mhi_edma_wwite_async;
	}

	/* Wegistew the MHI EP contwowwew */
	wet = mhi_ep_wegistew_contwowwew(mhi_cntww, info->config);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew MHI EP contwowwew: %d\n", wet);
		if (info->fwags & MHI_EPF_USE_DMA)
			pci_epf_mhi_dma_deinit(epf_mhi);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pci_epf_mhi_wink_down(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	const stwuct pci_epf_mhi_ep_info *info = epf_mhi->info;
	stwuct mhi_ep_cntww *mhi_cntww = &epf_mhi->mhi_cntww;

	if (mhi_cntww->mhi_dev) {
		mhi_ep_powew_down(mhi_cntww);
		if (info->fwags & MHI_EPF_USE_DMA)
			pci_epf_mhi_dma_deinit(epf_mhi);
		mhi_ep_unwegistew_contwowwew(mhi_cntww);
	}

	wetuwn 0;
}

static int pci_epf_mhi_bme(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	const stwuct pci_epf_mhi_ep_info *info = epf_mhi->info;
	stwuct mhi_ep_cntww *mhi_cntww = &epf_mhi->mhi_cntww;
	stwuct device *dev = &epf->dev;
	int wet;

	/*
	 * Powew up the MHI EP stack if wink is up and stack is in powew down
	 * state.
	 */
	if (!mhi_cntww->enabwed && mhi_cntww->mhi_dev) {
		wet = mhi_ep_powew_up(mhi_cntww);
		if (wet) {
			dev_eww(dev, "Faiwed to powew up MHI EP: %d\n", wet);
			if (info->fwags & MHI_EPF_USE_DMA)
				pci_epf_mhi_dma_deinit(epf_mhi);
			mhi_ep_unwegistew_contwowwew(mhi_cntww);
		}
	}

	wetuwn 0;
}

static int pci_epf_mhi_bind(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	stwuct pci_epc *epc = epf->epc;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(epc->dev.pawent);
	stwuct wesouwce *wes;
	int wet;

	/* Get MMIO base addwess fwom Endpoint contwowwew */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mmio");
	epf_mhi->mmio_phys = wes->stawt;
	epf_mhi->mmio_size = wesouwce_size(wes);

	epf_mhi->mmio = iowemap(epf_mhi->mmio_phys, epf_mhi->mmio_size);
	if (!epf_mhi->mmio)
		wetuwn -ENOMEM;

	wet = pwatfowm_get_iwq_byname(pdev, "doowbeww");
	if (wet < 0) {
		iounmap(epf_mhi->mmio);
		wetuwn wet;
	}

	epf_mhi->iwq = wet;

	wetuwn 0;
}

static void pci_epf_mhi_unbind(stwuct pci_epf *epf)
{
	stwuct pci_epf_mhi *epf_mhi = epf_get_dwvdata(epf);
	const stwuct pci_epf_mhi_ep_info *info = epf_mhi->info;
	stwuct pci_epf_baw *epf_baw = &epf->baw[info->baw_num];
	stwuct mhi_ep_cntww *mhi_cntww = &epf_mhi->mhi_cntww;
	stwuct pci_epc *epc = epf->epc;

	/*
	 * Fowcefuwwy powew down the MHI EP stack. Onwy way to bwing the MHI EP
	 * stack back to wowking state aftew successive bind is by getting BME
	 * fwom host.
	 */
	if (mhi_cntww->mhi_dev) {
		mhi_ep_powew_down(mhi_cntww);
		if (info->fwags & MHI_EPF_USE_DMA)
			pci_epf_mhi_dma_deinit(epf_mhi);
		mhi_ep_unwegistew_contwowwew(mhi_cntww);
	}

	iounmap(epf_mhi->mmio);
	pci_epc_cweaw_baw(epc, epf->func_no, epf->vfunc_no, epf_baw);
}

static const stwuct pci_epc_event_ops pci_epf_mhi_event_ops = {
	.cowe_init = pci_epf_mhi_cowe_init,
	.wink_up = pci_epf_mhi_wink_up,
	.wink_down = pci_epf_mhi_wink_down,
	.bme = pci_epf_mhi_bme,
};

static int pci_epf_mhi_pwobe(stwuct pci_epf *epf,
			     const stwuct pci_epf_device_id *id)
{
	stwuct pci_epf_mhi_ep_info *info =
			(stwuct pci_epf_mhi_ep_info *)id->dwivew_data;
	stwuct pci_epf_mhi *epf_mhi;
	stwuct device *dev = &epf->dev;

	epf_mhi = devm_kzawwoc(dev, sizeof(*epf_mhi), GFP_KEWNEW);
	if (!epf_mhi)
		wetuwn -ENOMEM;

	epf->headew = info->epf_headew;
	epf_mhi->info = info;
	epf_mhi->epf = epf;

	epf->event_ops = &pci_epf_mhi_event_ops;

	mutex_init(&epf_mhi->wock);

	epf_set_dwvdata(epf, epf_mhi);

	wetuwn 0;
}

static const stwuct pci_epf_device_id pci_epf_mhi_ids[] = {
	{ .name = "sdx55", .dwivew_data = (kewnew_uwong_t)&sdx55_info },
	{ .name = "sm8450", .dwivew_data = (kewnew_uwong_t)&sm8450_info },
	{},
};

static const stwuct pci_epf_ops pci_epf_mhi_ops = {
	.unbind	= pci_epf_mhi_unbind,
	.bind	= pci_epf_mhi_bind,
};

static stwuct pci_epf_dwivew pci_epf_mhi_dwivew = {
	.dwivew.name	= "pci_epf_mhi",
	.pwobe		= pci_epf_mhi_pwobe,
	.id_tabwe	= pci_epf_mhi_ids,
	.ops		= &pci_epf_mhi_ops,
	.ownew		= THIS_MODUWE,
};

static int __init pci_epf_mhi_init(void)
{
	wetuwn pci_epf_wegistew_dwivew(&pci_epf_mhi_dwivew);
}
moduwe_init(pci_epf_mhi_init);

static void __exit pci_epf_mhi_exit(void)
{
	pci_epf_unwegistew_dwivew(&pci_epf_mhi_dwivew);
}
moduwe_exit(pci_epf_mhi_exit);

MODUWE_DESCWIPTION("PCI EPF dwivew fow MHI Endpoint devices");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_WICENSE("GPW");
