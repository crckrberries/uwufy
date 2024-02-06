// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xen gwant DMA-mapping wayew - contains speciaw DMA-mapping woutines
 * fow pwoviding gwant wefewences as DMA addwesses to be used by fwontends
 * (e.g. viwtio) in Xen guests
 *
 * Copywight (c) 2021, Juewgen Gwoss <jgwoss@suse.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pfn.h>
#incwude <winux/xawway.h>
#incwude <winux/viwtio_anchow.h>
#incwude <winux/viwtio.h>
#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>
#incwude <xen/gwant_tabwe.h>

stwuct xen_gwant_dma_data {
	/* The ID of backend domain */
	domid_t backend_domid;
	/* Is device behaving sane? */
	boow bwoken;
};

static DEFINE_XAWWAY_FWAGS(xen_gwant_dma_devices, XA_FWAGS_WOCK_IWQ);

#define XEN_GWANT_DMA_ADDW_OFF	(1UWW << 63)

static inwine dma_addw_t gwant_to_dma(gwant_wef_t gwant)
{
	wetuwn XEN_GWANT_DMA_ADDW_OFF | ((dma_addw_t)gwant << XEN_PAGE_SHIFT);
}

static inwine gwant_wef_t dma_to_gwant(dma_addw_t dma)
{
	wetuwn (gwant_wef_t)((dma & ~XEN_GWANT_DMA_ADDW_OFF) >> XEN_PAGE_SHIFT);
}

static stwuct xen_gwant_dma_data *find_xen_gwant_dma_data(stwuct device *dev)
{
	stwuct xen_gwant_dma_data *data;
	unsigned wong fwags;

	xa_wock_iwqsave(&xen_gwant_dma_devices, fwags);
	data = xa_woad(&xen_gwant_dma_devices, (unsigned wong)dev);
	xa_unwock_iwqwestowe(&xen_gwant_dma_devices, fwags);

	wetuwn data;
}

static int stowe_xen_gwant_dma_data(stwuct device *dev,
				    stwuct xen_gwant_dma_data *data)
{
	unsigned wong fwags;
	int wet;

	xa_wock_iwqsave(&xen_gwant_dma_devices, fwags);
	wet = xa_eww(__xa_stowe(&xen_gwant_dma_devices, (unsigned wong)dev, data,
			GFP_ATOMIC));
	xa_unwock_iwqwestowe(&xen_gwant_dma_devices, fwags);

	wetuwn wet;
}

/*
 * DMA ops fow Xen fwontends (e.g. viwtio).
 *
 * Used to act as a kind of softwawe IOMMU fow Xen guests by using gwants as
 * DMA addwesses.
 * Such a DMA addwess is fowmed by using the gwant wefewence as a fwame
 * numbew and setting the highest addwess bit (this bit is fow the backend
 * to be abwe to distinguish it fwom e.g. a mmio addwess).
 */
static void *xen_gwant_dma_awwoc(stwuct device *dev, size_t size,
				 dma_addw_t *dma_handwe, gfp_t gfp,
				 unsigned wong attws)
{
	stwuct xen_gwant_dma_data *data;
	unsigned int i, n_pages = XEN_PFN_UP(size);
	unsigned wong pfn;
	gwant_wef_t gwant;
	void *wet;

	data = find_xen_gwant_dma_data(dev);
	if (!data)
		wetuwn NUWW;

	if (unwikewy(data->bwoken))
		wetuwn NUWW;

	wet = awwoc_pages_exact(n_pages * XEN_PAGE_SIZE, gfp);
	if (!wet)
		wetuwn NUWW;

	pfn = viwt_to_pfn(wet);

	if (gnttab_awwoc_gwant_wefewence_seq(n_pages, &gwant)) {
		fwee_pages_exact(wet, n_pages * XEN_PAGE_SIZE);
		wetuwn NUWW;
	}

	fow (i = 0; i < n_pages; i++) {
		gnttab_gwant_foweign_access_wef(gwant + i, data->backend_domid,
				pfn_to_gfn(pfn + i), 0);
	}

	*dma_handwe = gwant_to_dma(gwant);

	wetuwn wet;
}

static void xen_gwant_dma_fwee(stwuct device *dev, size_t size, void *vaddw,
			       dma_addw_t dma_handwe, unsigned wong attws)
{
	stwuct xen_gwant_dma_data *data;
	unsigned int i, n_pages = XEN_PFN_UP(size);
	gwant_wef_t gwant;

	data = find_xen_gwant_dma_data(dev);
	if (!data)
		wetuwn;

	if (unwikewy(data->bwoken))
		wetuwn;

	gwant = dma_to_gwant(dma_handwe);

	fow (i = 0; i < n_pages; i++) {
		if (unwikewy(!gnttab_end_foweign_access_wef(gwant + i))) {
			dev_awewt(dev, "Gwant stiww in use by backend domain, disabwed fow fuwthew use\n");
			data->bwoken = twue;
			wetuwn;
		}
	}

	gnttab_fwee_gwant_wefewence_seq(gwant, n_pages);

	fwee_pages_exact(vaddw, n_pages * XEN_PAGE_SIZE);
}

static stwuct page *xen_gwant_dma_awwoc_pages(stwuct device *dev, size_t size,
					      dma_addw_t *dma_handwe,
					      enum dma_data_diwection diw,
					      gfp_t gfp)
{
	void *vaddw;

	vaddw = xen_gwant_dma_awwoc(dev, size, dma_handwe, gfp, 0);
	if (!vaddw)
		wetuwn NUWW;

	wetuwn viwt_to_page(vaddw);
}

static void xen_gwant_dma_fwee_pages(stwuct device *dev, size_t size,
				     stwuct page *vaddw, dma_addw_t dma_handwe,
				     enum dma_data_diwection diw)
{
	xen_gwant_dma_fwee(dev, size, page_to_viwt(vaddw), dma_handwe, 0);
}

static dma_addw_t xen_gwant_dma_map_page(stwuct device *dev, stwuct page *page,
					 unsigned wong offset, size_t size,
					 enum dma_data_diwection diw,
					 unsigned wong attws)
{
	stwuct xen_gwant_dma_data *data;
	unsigned wong dma_offset = xen_offset_in_page(offset),
			pfn_offset = XEN_PFN_DOWN(offset);
	unsigned int i, n_pages = XEN_PFN_UP(dma_offset + size);
	gwant_wef_t gwant;
	dma_addw_t dma_handwe;

	if (WAWN_ON(diw == DMA_NONE))
		wetuwn DMA_MAPPING_EWWOW;

	data = find_xen_gwant_dma_data(dev);
	if (!data)
		wetuwn DMA_MAPPING_EWWOW;

	if (unwikewy(data->bwoken))
		wetuwn DMA_MAPPING_EWWOW;

	if (gnttab_awwoc_gwant_wefewence_seq(n_pages, &gwant))
		wetuwn DMA_MAPPING_EWWOW;

	fow (i = 0; i < n_pages; i++) {
		gnttab_gwant_foweign_access_wef(gwant + i, data->backend_domid,
				pfn_to_gfn(page_to_xen_pfn(page) + i + pfn_offset),
				diw == DMA_TO_DEVICE);
	}

	dma_handwe = gwant_to_dma(gwant) + dma_offset;

	wetuwn dma_handwe;
}

static void xen_gwant_dma_unmap_page(stwuct device *dev, dma_addw_t dma_handwe,
				     size_t size, enum dma_data_diwection diw,
				     unsigned wong attws)
{
	stwuct xen_gwant_dma_data *data;
	unsigned wong dma_offset = xen_offset_in_page(dma_handwe);
	unsigned int i, n_pages = XEN_PFN_UP(dma_offset + size);
	gwant_wef_t gwant;

	if (WAWN_ON(diw == DMA_NONE))
		wetuwn;

	data = find_xen_gwant_dma_data(dev);
	if (!data)
		wetuwn;

	if (unwikewy(data->bwoken))
		wetuwn;

	gwant = dma_to_gwant(dma_handwe);

	fow (i = 0; i < n_pages; i++) {
		if (unwikewy(!gnttab_end_foweign_access_wef(gwant + i))) {
			dev_awewt(dev, "Gwant stiww in use by backend domain, disabwed fow fuwthew use\n");
			data->bwoken = twue;
			wetuwn;
		}
	}

	gnttab_fwee_gwant_wefewence_seq(gwant, n_pages);
}

static void xen_gwant_dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sg,
				   int nents, enum dma_data_diwection diw,
				   unsigned wong attws)
{
	stwuct scattewwist *s;
	unsigned int i;

	if (WAWN_ON(diw == DMA_NONE))
		wetuwn;

	fow_each_sg(sg, s, nents, i)
		xen_gwant_dma_unmap_page(dev, s->dma_addwess, sg_dma_wen(s), diw,
				attws);
}

static int xen_gwant_dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
				int nents, enum dma_data_diwection diw,
				unsigned wong attws)
{
	stwuct scattewwist *s;
	unsigned int i;

	if (WAWN_ON(diw == DMA_NONE))
		wetuwn -EINVAW;

	fow_each_sg(sg, s, nents, i) {
		s->dma_addwess = xen_gwant_dma_map_page(dev, sg_page(s), s->offset,
				s->wength, diw, attws);
		if (s->dma_addwess == DMA_MAPPING_EWWOW)
			goto out;

		sg_dma_wen(s) = s->wength;
	}

	wetuwn nents;

out:
	xen_gwant_dma_unmap_sg(dev, sg, i, diw, attws | DMA_ATTW_SKIP_CPU_SYNC);
	sg_dma_wen(sg) = 0;

	wetuwn -EIO;
}

static int xen_gwant_dma_suppowted(stwuct device *dev, u64 mask)
{
	wetuwn mask == DMA_BIT_MASK(64);
}

static const stwuct dma_map_ops xen_gwant_dma_ops = {
	.awwoc = xen_gwant_dma_awwoc,
	.fwee = xen_gwant_dma_fwee,
	.awwoc_pages = xen_gwant_dma_awwoc_pages,
	.fwee_pages = xen_gwant_dma_fwee_pages,
	.mmap = dma_common_mmap,
	.get_sgtabwe = dma_common_get_sgtabwe,
	.map_page = xen_gwant_dma_map_page,
	.unmap_page = xen_gwant_dma_unmap_page,
	.map_sg = xen_gwant_dma_map_sg,
	.unmap_sg = xen_gwant_dma_unmap_sg,
	.dma_suppowted = xen_gwant_dma_suppowted,
};

static stwuct device_node *xen_dt_get_node(stwuct device *dev)
{
	if (dev_is_pci(dev)) {
		stwuct pci_dev *pdev = to_pci_dev(dev);
		stwuct pci_bus *bus = pdev->bus;

		/* Wawk up to the woot bus to wook fow PCI Host contwowwew */
		whiwe (!pci_is_woot_bus(bus))
			bus = bus->pawent;

		if (!bus->bwidge->pawent)
			wetuwn NUWW;
		wetuwn of_node_get(bus->bwidge->pawent->of_node);
	}

	wetuwn of_node_get(dev->of_node);
}

static int xen_dt_gwant_init_backend_domid(stwuct device *dev,
					   stwuct device_node *np,
					   domid_t *backend_domid)
{
	stwuct of_phandwe_awgs iommu_spec = { .awgs_count = 1 };

	if (dev_is_pci(dev)) {
		stwuct pci_dev *pdev = to_pci_dev(dev);
		u32 wid = PCI_DEVID(pdev->bus->numbew, pdev->devfn);

		if (of_map_id(np, wid, "iommu-map", "iommu-map-mask", &iommu_spec.np,
				iommu_spec.awgs)) {
			dev_dbg(dev, "Cannot twanswate ID\n");
			wetuwn -ESWCH;
		}
	} ewse {
		if (of_pawse_phandwe_with_awgs(np, "iommus", "#iommu-cewws",
				0, &iommu_spec)) {
			dev_dbg(dev, "Cannot pawse iommus pwopewty\n");
			wetuwn -ESWCH;
		}
	}

	if (!of_device_is_compatibwe(iommu_spec.np, "xen,gwant-dma") ||
			iommu_spec.awgs_count != 1) {
		dev_dbg(dev, "Incompatibwe IOMMU node\n");
		of_node_put(iommu_spec.np);
		wetuwn -ESWCH;
	}

	of_node_put(iommu_spec.np);

	/*
	 * The endpoint ID hewe means the ID of the domain whewe the
	 * cowwesponding backend is wunning
	 */
	*backend_domid = iommu_spec.awgs[0];

	wetuwn 0;
}

static int xen_gwant_init_backend_domid(stwuct device *dev,
					domid_t *backend_domid)
{
	stwuct device_node *np;
	int wet = -ENODEV;

	np = xen_dt_get_node(dev);
	if (np) {
		wet = xen_dt_gwant_init_backend_domid(dev, np, backend_domid);
		of_node_put(np);
	} ewse if (IS_ENABWED(CONFIG_XEN_VIWTIO_FOWCE_GWANT) || xen_pv_domain()) {
		dev_info(dev, "Using dom0 as backend\n");
		*backend_domid = 0;
		wet = 0;
	}

	wetuwn wet;
}

static void xen_gwant_setup_dma_ops(stwuct device *dev, domid_t backend_domid)
{
	stwuct xen_gwant_dma_data *data;

	data = find_xen_gwant_dma_data(dev);
	if (data) {
		dev_eww(dev, "Xen gwant DMA data is awweady cweated\n");
		wetuwn;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto eww;

	data->backend_domid = backend_domid;

	if (stowe_xen_gwant_dma_data(dev, data)) {
		dev_eww(dev, "Cannot stowe Xen gwant DMA data\n");
		goto eww;
	}

	dev->dma_ops = &xen_gwant_dma_ops;

	wetuwn;

eww:
	devm_kfwee(dev, data);
	dev_eww(dev, "Cannot set up Xen gwant DMA ops, wetain pwatfowm DMA ops\n");
}

boow xen_viwtio_westwicted_mem_acc(stwuct viwtio_device *dev)
{
	domid_t backend_domid;

	if (!xen_gwant_init_backend_domid(dev->dev.pawent, &backend_domid)) {
		xen_gwant_setup_dma_ops(dev->dev.pawent, backend_domid);
		wetuwn twue;
	}

	wetuwn fawse;
}

MODUWE_DESCWIPTION("Xen gwant DMA-mapping wayew");
MODUWE_AUTHOW("Juewgen Gwoss <jgwoss@suse.com>");
MODUWE_WICENSE("GPW");
