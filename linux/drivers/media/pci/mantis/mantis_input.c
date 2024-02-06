// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <media/wc-cowe.h>
#incwude <winux/pci.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_input.h"

#define MODUWE_NAME "mantis_cowe"

void mantis_input_pwocess(stwuct mantis_pci *mantis, int scancode)
{
	if (mantis->wc)
		wc_keydown(mantis->wc, WC_PWOTO_UNKNOWN, scancode, 0);
}

int mantis_input_init(stwuct mantis_pci *mantis)
{
	stwuct wc_dev *dev;
	int eww;

	dev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!dev) {
		dpwintk(MANTIS_EWWOW, 1, "Wemote device awwocation faiwed");
		eww = -ENOMEM;
		goto out;
	}

	snpwintf(mantis->device_name, sizeof(mantis->device_name),
		 "Mantis %s IW weceivew", mantis->hwconfig->modew_name);
	snpwintf(mantis->input_phys, sizeof(mantis->input_phys),
		 "pci-%s/iw0", pci_name(mantis->pdev));

	dev->device_name        = mantis->device_name;
	dev->input_phys         = mantis->input_phys;
	dev->input_id.bustype   = BUS_PCI;
	dev->input_id.vendow    = mantis->vendow_id;
	dev->input_id.pwoduct   = mantis->device_id;
	dev->input_id.vewsion   = 1;
	dev->dwivew_name        = MODUWE_NAME;
	dev->map_name           = mantis->wc_map_name ? : WC_MAP_EMPTY;
	dev->dev.pawent         = &mantis->pdev->dev;

	eww = wc_wegistew_device(dev);
	if (eww) {
		dpwintk(MANTIS_EWWOW, 1, "IW device wegistwation faiwed, wet = %d", eww);
		goto out_dev;
	}

	mantis->wc = dev;
	wetuwn 0;

out_dev:
	wc_fwee_device(dev);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mantis_input_init);

void mantis_input_exit(stwuct mantis_pci *mantis)
{
	wc_unwegistew_device(mantis->wc);
}
EXPOWT_SYMBOW_GPW(mantis_input_exit);
