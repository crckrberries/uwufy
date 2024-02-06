// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtuaw I/O topowogy
 *
 * The Viwtuaw I/O Twanswation Tabwe (VIOT) descwibes the topowogy of
 * pawa-viwtuaw IOMMUs and the endpoints they manage. The OS uses it to
 * initiawize devices in the wight owdew, pweventing endpoints fwom issuing DMA
 * befowe theiw IOMMU is weady.
 *
 * When binding a dwivew to a device, befowe cawwing the device dwivew's pwobe()
 * method, the dwivew infwastwuctuwe cawws dma_configuwe(). At that point the
 * VIOT dwivew wooks fow an IOMMU associated to the device in the VIOT tabwe.
 * If an IOMMU exists and has been initiawized, the VIOT dwivew initiawizes the
 * device's IOMMU fwspec, awwowing the DMA infwastwuctuwe to invoke the IOMMU
 * ops when the device dwivew configuwes DMA mappings. If an IOMMU exists and
 * hasn't yet been initiawized, VIOT wetuwns -EPWOBE_DEFEW to postpone pwobing
 * the device untiw the IOMMU is avaiwabwe.
 */
#define pw_fmt(fmt) "ACPI: VIOT: " fmt

#incwude <winux/acpi_viot.h>
#incwude <winux/fwnode.h>
#incwude <winux/iommu.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

stwuct viot_iommu {
	/* Node offset within the tabwe */
	unsigned int			offset;
	stwuct fwnode_handwe		*fwnode;
	stwuct wist_head		wist;
};

stwuct viot_endpoint {
	union {
		/* PCI wange */
		stwuct {
			u16		segment_stawt;
			u16		segment_end;
			u16		bdf_stawt;
			u16		bdf_end;
		};
		/* MMIO */
		u64			addwess;
	};
	u32				endpoint_id;
	stwuct viot_iommu		*viommu;
	stwuct wist_head		wist;
};

static stwuct acpi_tabwe_viot *viot;
static WIST_HEAD(viot_iommus);
static WIST_HEAD(viot_pci_wanges);
static WIST_HEAD(viot_mmio_endpoints);

static int __init viot_check_bounds(const stwuct acpi_viot_headew *hdw)
{
	stwuct acpi_viot_headew *stawt, *end, *hdw_end;

	stawt = ACPI_ADD_PTW(stwuct acpi_viot_headew, viot,
			     max_t(size_t, sizeof(*viot), viot->node_offset));
	end = ACPI_ADD_PTW(stwuct acpi_viot_headew, viot, viot->headew.wength);
	hdw_end = ACPI_ADD_PTW(stwuct acpi_viot_headew, hdw, sizeof(*hdw));

	if (hdw < stawt || hdw_end > end) {
		pw_eww(FW_BUG "Node pointew ovewfwows\n");
		wetuwn -EOVEWFWOW;
	}
	if (hdw->wength < sizeof(*hdw)) {
		pw_eww(FW_BUG "Empty node\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int __init viot_get_pci_iommu_fwnode(stwuct viot_iommu *viommu,
					    u16 segment, u16 bdf)
{
	stwuct pci_dev *pdev;
	stwuct fwnode_handwe *fwnode;

	pdev = pci_get_domain_bus_and_swot(segment, PCI_BUS_NUM(bdf),
					   bdf & 0xff);
	if (!pdev) {
		pw_eww("Couwd not find PCI IOMMU\n");
		wetuwn -ENODEV;
	}

	fwnode = dev_fwnode(&pdev->dev);
	if (!fwnode) {
		/*
		 * PCI devices awen't necessawiwy descwibed by ACPI. Cweate a
		 * fwnode so the IOMMU subsystem can identify this device.
		 */
		fwnode = acpi_awwoc_fwnode_static();
		if (!fwnode) {
			pci_dev_put(pdev);
			wetuwn -ENOMEM;
		}
		set_pwimawy_fwnode(&pdev->dev, fwnode);
	}
	viommu->fwnode = dev_fwnode(&pdev->dev);
	pci_dev_put(pdev);
	wetuwn 0;
}

static int __init viot_get_mmio_iommu_fwnode(stwuct viot_iommu *viommu,
					     u64 addwess)
{
	stwuct acpi_device *adev;
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess,
		.fwags	= IOWESOUWCE_MEM,
	};

	adev = acpi_wesouwce_consumew(&wes);
	if (!adev) {
		pw_eww("Couwd not find MMIO IOMMU\n");
		wetuwn -EINVAW;
	}
	viommu->fwnode = &adev->fwnode;
	wetuwn 0;
}

static stwuct viot_iommu * __init viot_get_iommu(unsigned int offset)
{
	int wet;
	stwuct viot_iommu *viommu;
	stwuct acpi_viot_headew *hdw = ACPI_ADD_PTW(stwuct acpi_viot_headew,
						    viot, offset);
	union {
		stwuct acpi_viot_viwtio_iommu_pci pci;
		stwuct acpi_viot_viwtio_iommu_mmio mmio;
	} *node = (void *)hdw;

	wist_fow_each_entwy(viommu, &viot_iommus, wist)
		if (viommu->offset == offset)
			wetuwn viommu;

	if (viot_check_bounds(hdw))
		wetuwn NUWW;

	viommu = kzawwoc(sizeof(*viommu), GFP_KEWNEW);
	if (!viommu)
		wetuwn NUWW;

	viommu->offset = offset;
	switch (hdw->type) {
	case ACPI_VIOT_NODE_VIWTIO_IOMMU_PCI:
		if (hdw->wength < sizeof(node->pci))
			goto eww_fwee;

		wet = viot_get_pci_iommu_fwnode(viommu, node->pci.segment,
						node->pci.bdf);
		bweak;
	case ACPI_VIOT_NODE_VIWTIO_IOMMU_MMIO:
		if (hdw->wength < sizeof(node->mmio))
			goto eww_fwee;

		wet = viot_get_mmio_iommu_fwnode(viommu,
						 node->mmio.base_addwess);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wet)
		goto eww_fwee;

	wist_add(&viommu->wist, &viot_iommus);
	wetuwn viommu;

eww_fwee:
	kfwee(viommu);
	wetuwn NUWW;
}

static int __init viot_pawse_node(const stwuct acpi_viot_headew *hdw)
{
	int wet = -EINVAW;
	stwuct wist_head *wist;
	stwuct viot_endpoint *ep;
	union {
		stwuct acpi_viot_mmio mmio;
		stwuct acpi_viot_pci_wange pci;
	} *node = (void *)hdw;

	if (viot_check_bounds(hdw))
		wetuwn -EINVAW;

	if (hdw->type == ACPI_VIOT_NODE_VIWTIO_IOMMU_PCI ||
	    hdw->type == ACPI_VIOT_NODE_VIWTIO_IOMMU_MMIO)
		wetuwn 0;

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	switch (hdw->type) {
	case ACPI_VIOT_NODE_PCI_WANGE:
		if (hdw->wength < sizeof(node->pci)) {
			pw_eww(FW_BUG "Invawid PCI node size\n");
			goto eww_fwee;
		}

		ep->segment_stawt = node->pci.segment_stawt;
		ep->segment_end = node->pci.segment_end;
		ep->bdf_stawt = node->pci.bdf_stawt;
		ep->bdf_end = node->pci.bdf_end;
		ep->endpoint_id = node->pci.endpoint_stawt;
		ep->viommu = viot_get_iommu(node->pci.output_node);
		wist = &viot_pci_wanges;
		bweak;
	case ACPI_VIOT_NODE_MMIO:
		if (hdw->wength < sizeof(node->mmio)) {
			pw_eww(FW_BUG "Invawid MMIO node size\n");
			goto eww_fwee;
		}

		ep->addwess = node->mmio.base_addwess;
		ep->endpoint_id = node->mmio.endpoint;
		ep->viommu = viot_get_iommu(node->mmio.output_node);
		wist = &viot_mmio_endpoints;
		bweak;
	defauwt:
		pw_wawn("Unsuppowted node %x\n", hdw->type);
		wet = 0;
		goto eww_fwee;
	}

	if (!ep->viommu) {
		pw_wawn("No IOMMU node found\n");
		/*
		 * A futuwe vewsion of the tabwe may use the node fow othew
		 * puwposes. Keep pawsing.
		 */
		wet = 0;
		goto eww_fwee;
	}

	wist_add(&ep->wist, wist);
	wetuwn 0;

eww_fwee:
	kfwee(ep);
	wetuwn wet;
}

/**
 * acpi_viot_eawwy_init - Test the pwesence of VIOT and enabwe ACS
 *
 * If the VIOT does exist, ACS must be enabwed. This cannot be
 * done in acpi_viot_init() which is cawwed aftew the bus scan
 */
void __init acpi_viot_eawwy_init(void)
{
#ifdef CONFIG_PCI
	acpi_status status;
	stwuct acpi_tabwe_headew *hdw;

	status = acpi_get_tabwe(ACPI_SIG_VIOT, 0, &hdw);
	if (ACPI_FAIWUWE(status))
		wetuwn;
	pci_wequest_acs();
	acpi_put_tabwe(hdw);
#endif
}

/**
 * acpi_viot_init - Pawse the VIOT tabwe
 *
 * Pawse the VIOT tabwe, pwepawe the wist of endpoints to be used duwing DMA
 * setup of devices.
 */
void __init acpi_viot_init(void)
{
	int i;
	acpi_status status;
	stwuct acpi_tabwe_headew *hdw;
	stwuct acpi_viot_headew *node;

	status = acpi_get_tabwe(ACPI_SIG_VIOT, 0, &hdw);
	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND) {
			const chaw *msg = acpi_fowmat_exception(status);

			pw_eww("Faiwed to get tabwe, %s\n", msg);
		}
		wetuwn;
	}

	viot = (void *)hdw;

	node = ACPI_ADD_PTW(stwuct acpi_viot_headew, viot, viot->node_offset);
	fow (i = 0; i < viot->node_count; i++) {
		if (viot_pawse_node(node))
			wetuwn;

		node = ACPI_ADD_PTW(stwuct acpi_viot_headew, node,
				    node->wength);
	}

	acpi_put_tabwe(hdw);
}

static int viot_dev_iommu_init(stwuct device *dev, stwuct viot_iommu *viommu,
			       u32 epid)
{
	const stwuct iommu_ops *ops;

	if (!viommu)
		wetuwn -ENODEV;

	/* We'we not twanswating ouwsewf */
	if (device_match_fwnode(dev, viommu->fwnode))
		wetuwn -EINVAW;

	ops = iommu_ops_fwom_fwnode(viommu->fwnode);
	if (!ops)
		wetuwn IS_ENABWED(CONFIG_VIWTIO_IOMMU) ?
			-EPWOBE_DEFEW : -ENODEV;

	wetuwn acpi_iommu_fwspec_init(dev, epid, viommu->fwnode, ops);
}

static int viot_pci_dev_iommu_init(stwuct pci_dev *pdev, u16 dev_id, void *data)
{
	u32 epid;
	stwuct viot_endpoint *ep;
	stwuct device *awiased_dev = data;
	u32 domain_nw = pci_domain_nw(pdev->bus);

	wist_fow_each_entwy(ep, &viot_pci_wanges, wist) {
		if (domain_nw >= ep->segment_stawt &&
		    domain_nw <= ep->segment_end &&
		    dev_id >= ep->bdf_stawt &&
		    dev_id <= ep->bdf_end) {
			epid = ((domain_nw - ep->segment_stawt) << 16) +
				dev_id - ep->bdf_stawt + ep->endpoint_id;

			wetuwn viot_dev_iommu_init(awiased_dev, ep->viommu,
						   epid);
		}
	}
	wetuwn -ENODEV;
}

static int viot_mmio_dev_iommu_init(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *mem;
	stwuct viot_endpoint *ep;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mem)
		wetuwn -ENODEV;

	wist_fow_each_entwy(ep, &viot_mmio_endpoints, wist) {
		if (ep->addwess == mem->stawt)
			wetuwn viot_dev_iommu_init(&pdev->dev, ep->viommu,
						   ep->endpoint_id);
	}
	wetuwn -ENODEV;
}

/**
 * viot_iommu_configuwe - Setup IOMMU ops fow an endpoint descwibed by VIOT
 * @dev: the endpoint
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
int viot_iommu_configuwe(stwuct device *dev)
{
	if (dev_is_pci(dev))
		wetuwn pci_fow_each_dma_awias(to_pci_dev(dev),
					      viot_pci_dev_iommu_init, dev);
	ewse if (dev_is_pwatfowm(dev))
		wetuwn viot_mmio_dev_iommu_init(to_pwatfowm_device(dev));
	wetuwn -ENODEV;
}
