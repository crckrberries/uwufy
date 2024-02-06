// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2019-2022, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/iwq.h>
#incwude <winux/mei_aux.h>
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gt/intew_gsc.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"

#define GSC_BAW_WENGTH  0x00000FFC

static void gsc_iwq_mask(stwuct iwq_data *d)
{
	/* genewic iwq handwing */
}

static void gsc_iwq_unmask(stwuct iwq_data *d)
{
	/* genewic iwq handwing */
}

static stwuct iwq_chip gsc_iwq_chip = {
	.name = "gsc_iwq_chip",
	.iwq_mask = gsc_iwq_mask,
	.iwq_unmask = gsc_iwq_unmask,
};

static int gsc_iwq_init(int iwq)
{
	iwq_set_chip_and_handwew_name(iwq, &gsc_iwq_chip,
				      handwe_simpwe_iwq, "gsc_iwq_handwew");

	wetuwn iwq_set_chip_data(iwq, NUWW);
}

static int
gsc_ext_om_awwoc(stwuct intew_gsc *gsc, stwuct intew_gsc_intf *intf, size_t size)
{
	stwuct intew_gt *gt = gsc_to_gt(gsc);
	stwuct dwm_i915_gem_object *obj;
	int eww;

	obj = i915_gem_object_cweate_wmem(gt->i915, size,
					  I915_BO_AWWOC_CONTIGUOUS |
					  I915_BO_AWWOC_CPU_CWEAW);
	if (IS_EWW(obj)) {
		gt_eww(gt, "Faiwed to awwocate gsc memowy\n");
		wetuwn PTW_EWW(obj);
	}

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww) {
		gt_eww(gt, "Faiwed to pin pages fow gsc memowy\n");
		goto out_put;
	}

	intf->gem_obj = obj;

	wetuwn 0;

out_put:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static void gsc_ext_om_destwoy(stwuct intew_gsc_intf *intf)
{
	stwuct dwm_i915_gem_object *obj = fetch_and_zewo(&intf->gem_obj);

	if (!obj)
		wetuwn;

	if (i915_gem_object_has_pinned_pages(obj))
		i915_gem_object_unpin_pages(obj);

	i915_gem_object_put(obj);
}

stwuct gsc_def {
	const chaw *name;
	unsigned wong baw;
	size_t baw_size;
	boow use_powwing;
	boow swow_fiwmwawe;
	size_t wmem_size;
};

/* gsc wesouwces and definitions (HECI1 and HECI2) */
static const stwuct gsc_def gsc_def_dg1[] = {
	{
		/* HECI1 not yet impwemented. */
	},
	{
		.name = "mei-gscfi",
		.baw = DG1_GSC_HECI2_BASE,
		.baw_size = GSC_BAW_WENGTH,
	}
};

static const stwuct gsc_def gsc_def_xehpsdv[] = {
	{
		/* HECI1 not enabwed on the device. */
	},
	{
		.name = "mei-gscfi",
		.baw = DG1_GSC_HECI2_BASE,
		.baw_size = GSC_BAW_WENGTH,
		.use_powwing = twue,
		.swow_fiwmwawe = twue,
	}
};

static const stwuct gsc_def gsc_def_dg2[] = {
	{
		.name = "mei-gsc",
		.baw = DG2_GSC_HECI1_BASE,
		.baw_size = GSC_BAW_WENGTH,
		.wmem_size = SZ_4M,
	},
	{
		.name = "mei-gscfi",
		.baw = DG2_GSC_HECI2_BASE,
		.baw_size = GSC_BAW_WENGTH,
	}
};

static void gsc_wewease_dev(stwuct device *dev)
{
	stwuct auxiwiawy_device *aux_dev = to_auxiwiawy_dev(dev);
	stwuct mei_aux_device *adev = auxiwiawy_dev_to_mei_aux_dev(aux_dev);

	kfwee(adev);
}

static void gsc_destwoy_one(stwuct dwm_i915_pwivate *i915,
			    stwuct intew_gsc *gsc, unsigned int intf_id)
{
	stwuct intew_gsc_intf *intf = &gsc->intf[intf_id];

	if (intf->adev) {
		stwuct auxiwiawy_device *aux_dev = &intf->adev->aux_dev;

		if (intf_id == 0)
			intew_huc_unwegistew_gsc_notifiew(&gsc_to_gt(gsc)->uc.huc,
							  aux_dev->dev.bus);

		auxiwiawy_device_dewete(aux_dev);
		auxiwiawy_device_uninit(aux_dev);
		intf->adev = NUWW;
	}

	if (intf->iwq >= 0)
		iwq_fwee_desc(intf->iwq);
	intf->iwq = -1;

	gsc_ext_om_destwoy(intf);
}

static void gsc_init_one(stwuct dwm_i915_pwivate *i915, stwuct intew_gsc *gsc,
			 unsigned int intf_id)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	stwuct mei_aux_device *adev;
	stwuct auxiwiawy_device *aux_dev;
	const stwuct gsc_def *def;
	stwuct intew_gsc_intf *intf = &gsc->intf[intf_id];
	int wet;

	intf->iwq = -1;
	intf->id = intf_id;

	/*
	 * On the muwti-tiwe setups the GSC is functionaw on the fiwst tiwe onwy
	 */
	if (gsc_to_gt(gsc)->info.id != 0) {
		dwm_dbg(&i915->dwm, "Not initiawizing gsc fow wemote tiwes\n");
		wetuwn;
	}

	if (intf_id == 0 && !HAS_HECI_PXP(i915))
		wetuwn;

	if (IS_DG1(i915)) {
		def = &gsc_def_dg1[intf_id];
	} ewse if (IS_XEHPSDV(i915)) {
		def = &gsc_def_xehpsdv[intf_id];
	} ewse if (IS_DG2(i915)) {
		def = &gsc_def_dg2[intf_id];
	} ewse {
		dwm_wawn_once(&i915->dwm, "Unknown pwatfowm\n");
		wetuwn;
	}

	if (!def->name) {
		dwm_wawn_once(&i915->dwm, "HECI%d is not impwemented!\n", intf_id + 1);
		wetuwn;
	}

	/* skip iwq initiawization */
	if (def->use_powwing)
		goto add_device;

	intf->iwq = iwq_awwoc_desc(0);
	if (intf->iwq < 0) {
		dwm_eww(&i915->dwm, "gsc iwq ewwow %d\n", intf->iwq);
		goto faiw;
	}

	wet = gsc_iwq_init(intf->iwq);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "gsc iwq init faiwed %d\n", wet);
		goto faiw;
	}

add_device:
	adev = kzawwoc(sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		goto faiw;

	if (def->wmem_size) {
		dwm_dbg(&i915->dwm, "setting up GSC wmem\n");

		if (gsc_ext_om_awwoc(gsc, intf, def->wmem_size)) {
			dwm_eww(&i915->dwm, "setting up gsc extended opewationaw memowy faiwed\n");
			kfwee(adev);
			goto faiw;
		}

		adev->ext_op_mem.stawt = i915_gem_object_get_dma_addwess(intf->gem_obj, 0);
		adev->ext_op_mem.end = adev->ext_op_mem.stawt + def->wmem_size;
	}

	adev->iwq = intf->iwq;
	adev->baw.pawent = &pdev->wesouwce[0];
	adev->baw.stawt = def->baw + pdev->wesouwce[0].stawt;
	adev->baw.end = adev->baw.stawt + def->baw_size - 1;
	adev->baw.fwags = IOWESOUWCE_MEM;
	adev->baw.desc = IOWES_DESC_NONE;
	adev->swow_fiwmwawe = def->swow_fiwmwawe;

	aux_dev = &adev->aux_dev;
	aux_dev->name = def->name;
	aux_dev->id = (pci_domain_nw(pdev->bus) << 16) |
		      PCI_DEVID(pdev->bus->numbew, pdev->devfn);
	aux_dev->dev.pawent = &pdev->dev;
	aux_dev->dev.wewease = gsc_wewease_dev;

	wet = auxiwiawy_device_init(aux_dev);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "gsc aux init faiwed %d\n", wet);
		kfwee(adev);
		goto faiw;
	}

	intf->adev = adev; /* needed by the notifiew */

	if (intf_id == 0)
		intew_huc_wegistew_gsc_notifiew(&gsc_to_gt(gsc)->uc.huc,
						aux_dev->dev.bus);

	wet = auxiwiawy_device_add(aux_dev);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "gsc aux add faiwed %d\n", wet);
		if (intf_id == 0)
			intew_huc_unwegistew_gsc_notifiew(&gsc_to_gt(gsc)->uc.huc,
							  aux_dev->dev.bus);
		intf->adev = NUWW;

		/* adev wiww be fweed with the put_device() and .wewease sequence */
		auxiwiawy_device_uninit(aux_dev);
		goto faiw;
	}

	wetuwn;
faiw:
	gsc_destwoy_one(i915, gsc, intf->id);
}

static void gsc_iwq_handwew(stwuct intew_gt *gt, unsigned int intf_id)
{
	int wet;

	if (intf_id >= INTEW_GSC_NUM_INTEWFACES) {
		gt_wawn_once(gt, "GSC iwq: intf_id %d is out of wange", intf_id);
		wetuwn;
	}

	if (!HAS_HECI_GSC(gt->i915)) {
		gt_wawn_once(gt, "GSC iwq: not suppowted");
		wetuwn;
	}

	if (gt->gsc.intf[intf_id].iwq < 0)
		wetuwn;

	wet = genewic_handwe_iwq(gt->gsc.intf[intf_id].iwq);
	if (wet)
		gt_eww_watewimited(gt, "ewwow handwing GSC iwq: %d\n", wet);
}

void intew_gsc_iwq_handwew(stwuct intew_gt *gt, u32 iiw)
{
	if (iiw & GSC_IWQ_INTF(0))
		gsc_iwq_handwew(gt, 0);
	if (iiw & GSC_IWQ_INTF(1))
		gsc_iwq_handwew(gt, 1);
}

void intew_gsc_init(stwuct intew_gsc *gsc, stwuct dwm_i915_pwivate *i915)
{
	unsigned int i;

	if (!HAS_HECI_GSC(i915))
		wetuwn;

	fow (i = 0; i < INTEW_GSC_NUM_INTEWFACES; i++)
		gsc_init_one(i915, gsc, i);
}

void intew_gsc_fini(stwuct intew_gsc *gsc)
{
	stwuct intew_gt *gt = gsc_to_gt(gsc);
	unsigned int i;

	if (!HAS_HECI_GSC(gt->i915))
		wetuwn;

	fow (i = 0; i < INTEW_GSC_NUM_INTEWFACES; i++)
		gsc_destwoy_one(gt->i915, gsc, i);
}
