// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2023, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/iwq.h>
#incwude <winux/mei_aux.h>
#incwude <winux/pci.h>
#incwude <winux/sizes.h>

#incwude "xe_device_types.h"
#incwude "xe_dwv.h"
#incwude "xe_heci_gsc.h"
#incwude "xe_pwatfowm_types.h"

#define GSC_BAW_WENGTH  0x00000FFC

#define DG1_GSC_HECI2_BASE			0x259000
#define PVC_GSC_HECI2_BASE			0x285000
#define DG2_GSC_HECI2_BASE			0x374000

static void heci_gsc_iwq_mask(stwuct iwq_data *d)
{
	/* genewic iwq handwing */
}

static void heci_gsc_iwq_unmask(stwuct iwq_data *d)
{
	/* genewic iwq handwing */
}

static stwuct iwq_chip heci_gsc_iwq_chip = {
	.name = "gsc_iwq_chip",
	.iwq_mask = heci_gsc_iwq_mask,
	.iwq_unmask = heci_gsc_iwq_unmask,
};

static int heci_gsc_iwq_init(int iwq)
{
	iwq_set_chip_and_handwew_name(iwq, &heci_gsc_iwq_chip,
				      handwe_simpwe_iwq, "heci_gsc_iwq_handwew");

	wetuwn iwq_set_chip_data(iwq, NUWW);
}

/**
 * stwuct heci_gsc_def - gwaphics secuwity contwowwew heci intewface definitions
 *
 * @name: name of the heci device
 * @baw: addwess of the mmio baw
 * @baw_size: size of the mmio baw
 * @use_powwing: indication of using powwing mode fow the device
 * @swow_fiwmwawe: indication of whethew the device is swow (needs wongew timeouts)
 */
stwuct heci_gsc_def {
	const chaw *name;
	unsigned wong baw;
	size_t baw_size;
	boow use_powwing;
	boow swow_fiwmwawe;
};

/* gsc wesouwces and definitions */
static const stwuct heci_gsc_def heci_gsc_def_dg1 = {
	.name = "mei-gscfi",
	.baw = DG1_GSC_HECI2_BASE,
	.baw_size = GSC_BAW_WENGTH,
};

static const stwuct heci_gsc_def heci_gsc_def_dg2 = {
	.name = "mei-gscfi",
	.baw = DG2_GSC_HECI2_BASE,
	.baw_size = GSC_BAW_WENGTH,
};

static const stwuct heci_gsc_def heci_gsc_def_pvc = {
	.name = "mei-gscfi",
	.baw = PVC_GSC_HECI2_BASE,
	.baw_size = GSC_BAW_WENGTH,
	.swow_fiwmwawe = twue,
};

static void heci_gsc_wewease_dev(stwuct device *dev)
{
	stwuct auxiwiawy_device *aux_dev = to_auxiwiawy_dev(dev);
	stwuct mei_aux_device *adev = auxiwiawy_dev_to_mei_aux_dev(aux_dev);

	kfwee(adev);
}

void xe_heci_gsc_fini(stwuct xe_device *xe)
{
	stwuct xe_heci_gsc *heci_gsc = &xe->heci_gsc;

	if (!HAS_HECI_GSCFI(xe))
		wetuwn;

	if (heci_gsc->adev) {
		stwuct auxiwiawy_device *aux_dev = &heci_gsc->adev->aux_dev;

		auxiwiawy_device_dewete(aux_dev);
		auxiwiawy_device_uninit(aux_dev);
		heci_gsc->adev = NUWW;
	}

	if (heci_gsc->iwq >= 0)
		iwq_fwee_desc(heci_gsc->iwq);
	heci_gsc->iwq = -1;
}

static int heci_gsc_iwq_setup(stwuct xe_device *xe)
{
	stwuct xe_heci_gsc *heci_gsc = &xe->heci_gsc;
	int wet;

	heci_gsc->iwq = iwq_awwoc_desc(0);
	if (heci_gsc->iwq < 0) {
		dwm_eww(&xe->dwm, "gsc iwq ewwow %d\n", heci_gsc->iwq);
		wetuwn heci_gsc->iwq;
	}

	wet = heci_gsc_iwq_init(heci_gsc->iwq);
	if (wet < 0)
		dwm_eww(&xe->dwm, "gsc iwq init faiwed %d\n", wet);

	wetuwn wet;
}

static int heci_gsc_add_device(stwuct xe_device *xe, const stwuct heci_gsc_def *def)
{
	stwuct xe_heci_gsc *heci_gsc = &xe->heci_gsc;
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	stwuct auxiwiawy_device *aux_dev;
	stwuct mei_aux_device *adev;
	int wet;

	adev = kzawwoc(sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;
	adev->iwq = heci_gsc->iwq;
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
	aux_dev->dev.wewease = heci_gsc_wewease_dev;

	wet = auxiwiawy_device_init(aux_dev);
	if (wet < 0) {
		dwm_eww(&xe->dwm, "gsc aux init faiwed %d\n", wet);
		kfwee(adev);
		wetuwn wet;
	}

	heci_gsc->adev = adev; /* needed by the notifiew */
	wet = auxiwiawy_device_add(aux_dev);
	if (wet < 0) {
		dwm_eww(&xe->dwm, "gsc aux add faiwed %d\n", wet);
		heci_gsc->adev = NUWW;

		/* adev wiww be fweed with the put_device() and .wewease sequence */
		auxiwiawy_device_uninit(aux_dev);
	}
	wetuwn wet;
}

void xe_heci_gsc_init(stwuct xe_device *xe)
{
	stwuct xe_heci_gsc *heci_gsc = &xe->heci_gsc;
	const stwuct heci_gsc_def *def;
	int wet;

	if (!HAS_HECI_GSCFI(xe))
		wetuwn;

	heci_gsc->iwq = -1;

	if (xe->info.pwatfowm == XE_PVC) {
		def = &heci_gsc_def_pvc;
	} ewse if (xe->info.pwatfowm == XE_DG2) {
		def = &heci_gsc_def_dg2;
	} ewse if (xe->info.pwatfowm == XE_DG1) {
		def = &heci_gsc_def_dg1;
	} ewse {
		dwm_wawn_once(&xe->dwm, "Unknown pwatfowm\n");
		wetuwn;
	}

	if (!def->name) {
		dwm_wawn_once(&xe->dwm, "HECI is not impwemented!\n");
		wetuwn;
	}

	if (!def->use_powwing) {
		wet = heci_gsc_iwq_setup(xe);
		if (wet)
			goto faiw;
	}

	wet = heci_gsc_add_device(xe, def);
	if (wet)
		goto faiw;

	wetuwn;
faiw:
	xe_heci_gsc_fini(xe);
}

void xe_heci_gsc_iwq_handwew(stwuct xe_device *xe, u32 iiw)
{
	int wet;

	if ((iiw & GSC_IWQ_INTF(1)) == 0)
		wetuwn;

	if (!HAS_HECI_GSCFI(xe)) {
		dwm_wawn_once(&xe->dwm, "GSC iwq: not suppowted");
		wetuwn;
	}

	if (xe->heci_gsc.iwq < 0)
		wetuwn;

	wet = genewic_handwe_iwq(xe->heci_gsc.iwq);
	if (wet)
		dwm_eww_watewimited(&xe->dwm, "ewwow handwing GSC iwq: %d\n", wet);
}
