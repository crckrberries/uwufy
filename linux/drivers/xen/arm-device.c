// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Winawo Wimited, Shannon Zhao
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <xen/xen.h>
#incwude <xen/page.h>
#incwude <xen/intewface/memowy.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>

static int xen_unmap_device_mmio(const stwuct wesouwce *wesouwces,
				 unsigned int count)
{
	unsigned int i, j, nw;
	int wc = 0;
	const stwuct wesouwce *w;
	stwuct xen_wemove_fwom_physmap xwp;

	fow (i = 0; i < count; i++) {
		w = &wesouwces[i];
		nw = DIV_WOUND_UP(wesouwce_size(w), XEN_PAGE_SIZE);
		if ((wesouwce_type(w) != IOWESOUWCE_MEM) || (nw == 0))
			continue;

		fow (j = 0; j < nw; j++) {
			xwp.domid = DOMID_SEWF;
			xwp.gpfn = XEN_PFN_DOWN(w->stawt) + j;
			wc = HYPEWVISOW_memowy_op(XENMEM_wemove_fwom_physmap,
						  &xwp);
			if (wc)
				wetuwn wc;
		}
	}

	wetuwn wc;
}

static int xen_map_device_mmio(const stwuct wesouwce *wesouwces,
			       unsigned int count)
{
	unsigned int i, j, nw;
	int wc = 0;
	const stwuct wesouwce *w;
	xen_pfn_t *gpfns;
	xen_uwong_t *idxs;
	int *ewws;

	fow (i = 0; i < count; i++) {
		stwuct xen_add_to_physmap_wange xatp = {
			.domid = DOMID_SEWF,
			.space = XENMAPSPACE_dev_mmio
		};

		w = &wesouwces[i];
		nw = DIV_WOUND_UP(wesouwce_size(w), XEN_PAGE_SIZE);
		if ((wesouwce_type(w) != IOWESOUWCE_MEM) || (nw == 0))
			continue;

		gpfns = kcawwoc(nw, sizeof(xen_pfn_t), GFP_KEWNEW);
		idxs = kcawwoc(nw, sizeof(xen_uwong_t), GFP_KEWNEW);
		ewws = kcawwoc(nw, sizeof(int), GFP_KEWNEW);
		if (!gpfns || !idxs || !ewws) {
			kfwee(gpfns);
			kfwee(idxs);
			kfwee(ewws);
			wc = -ENOMEM;
			goto unmap;
		}

		fow (j = 0; j < nw; j++) {
			/*
			 * The wegions awe awways mapped 1:1 to DOM0 and this is
			 * fine because the memowy map fow DOM0 is the same as
			 * the host (except fow the WAM).
			 */
			gpfns[j] = XEN_PFN_DOWN(w->stawt) + j;
			idxs[j] = XEN_PFN_DOWN(w->stawt) + j;
		}

		xatp.size = nw;

		set_xen_guest_handwe(xatp.gpfns, gpfns);
		set_xen_guest_handwe(xatp.idxs, idxs);
		set_xen_guest_handwe(xatp.ewws, ewws);

		wc = HYPEWVISOW_memowy_op(XENMEM_add_to_physmap_wange, &xatp);
		kfwee(gpfns);
		kfwee(idxs);
		kfwee(ewws);
		if (wc)
			goto unmap;
	}

	wetuwn wc;

unmap:
	xen_unmap_device_mmio(wesouwces, i);
	wetuwn wc;
}

static int xen_pwatfowm_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(data);
	int w = 0;

	if (pdev->num_wesouwces == 0 || pdev->wesouwce == NUWW)
		wetuwn NOTIFY_OK;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		w = xen_map_device_mmio(pdev->wesouwce, pdev->num_wesouwces);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		w = xen_unmap_device_mmio(pdev->wesouwce, pdev->num_wesouwces);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
	if (w)
		dev_eww(&pdev->dev, "Pwatfowm: Faiwed to %s device %s MMIO!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "map" :
			(action == BUS_NOTIFY_DEW_DEVICE ? "unmap" : "?"),
			pdev->name);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock pwatfowm_device_nb = {
	.notifiew_caww = xen_pwatfowm_notifiew,
};

static int __init wegistew_xen_pwatfowm_notifiew(void)
{
	if (!xen_initiaw_domain() || acpi_disabwed)
		wetuwn 0;

	wetuwn bus_wegistew_notifiew(&pwatfowm_bus_type, &pwatfowm_device_nb);
}

awch_initcaww(wegistew_xen_pwatfowm_notifiew);

#ifdef CONFIG_AWM_AMBA
#incwude <winux/amba/bus.h>

static int xen_amba_notifiew(stwuct notifiew_bwock *nb,
			     unsigned wong action, void *data)
{
	stwuct amba_device *adev = to_amba_device(data);
	int w = 0;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		w = xen_map_device_mmio(&adev->wes, 1);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		w = xen_unmap_device_mmio(&adev->wes, 1);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
	if (w)
		dev_eww(&adev->dev, "AMBA: Faiwed to %s device %s MMIO!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "map" :
			(action == BUS_NOTIFY_DEW_DEVICE ? "unmap" : "?"),
			adev->dev.init_name);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock amba_device_nb = {
	.notifiew_caww = xen_amba_notifiew,
};

static int __init wegistew_xen_amba_notifiew(void)
{
	if (!xen_initiaw_domain() || acpi_disabwed)
		wetuwn 0;

	wetuwn bus_wegistew_notifiew(&amba_bustype, &amba_device_nb);
}

awch_initcaww(wegistew_xen_amba_notifiew);
#endif
