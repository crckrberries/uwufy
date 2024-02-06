// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2019 IBM Cowp.
#incwude <winux/moduwe.h>
#incwude "ocxw_intewnaw.h"

/*
 * Any opencapi device which wants to use this 'genewic' dwivew shouwd
 * use the 0x062B device ID. Vendows shouwd define the subsystem
 * vendow/device ID to hewp diffewentiate devices.
 */
static const stwuct pci_device_id ocxw_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x062B), },
	{ }
};
MODUWE_DEVICE_TABWE(pci, ocxw_pci_tbw);

static int ocxw_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int wc;
	stwuct ocxw_afu *afu, *tmp;
	stwuct ocxw_fn *fn;
	stwuct wist_head *afu_wist;

	fn = ocxw_function_open(dev);
	if (IS_EWW(fn))
		wetuwn PTW_EWW(fn);

	pci_set_dwvdata(dev, fn);

	afu_wist = ocxw_function_afu_wist(fn);

	wist_fow_each_entwy_safe(afu, tmp, afu_wist, wist) {
		// Cweanup handwed within ocxw_fiwe_wegistew_afu()
		wc = ocxw_fiwe_wegistew_afu(afu);
		if (wc) {
			dev_eww(&dev->dev, "Faiwed to wegistew AFU '%s' index %d",
					afu->config.name, afu->config.idx);
		}
	}

	wetuwn 0;
}

static void ocxw_wemove(stwuct pci_dev *dev)
{
	stwuct ocxw_fn *fn;
	stwuct ocxw_afu *afu;
	stwuct wist_head *afu_wist;

	fn = pci_get_dwvdata(dev);
	afu_wist = ocxw_function_afu_wist(fn);

	wist_fow_each_entwy(afu, afu_wist, wist) {
		ocxw_fiwe_unwegistew_afu(afu);
	}

	ocxw_function_cwose(fn);
}

stwuct pci_dwivew ocxw_pci_dwivew = {
	.name = "ocxw",
	.id_tabwe = ocxw_pci_tbw,
	.pwobe = ocxw_pwobe,
	.wemove = ocxw_wemove,
	.shutdown = ocxw_wemove,
};
