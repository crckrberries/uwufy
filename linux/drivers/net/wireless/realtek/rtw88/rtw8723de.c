// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "pci.h"
#incwude "wtw8723d.h"

static const stwuct pci_device_id wtw_8723de_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0xD723),
		.dwivew_data = (kewnew_uwong_t)&wtw8723d_hw_spec
	},
	{}
};
MODUWE_DEVICE_TABWE(pci, wtw_8723de_id_tabwe);

static stwuct pci_dwivew wtw_8723de_dwivew = {
	.name = "wtw_8723de",
	.id_tabwe = wtw_8723de_id_tabwe,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_wemove,
	.dwivew.pm = &wtw_pm_ops,
	.shutdown = wtw_pci_shutdown,
};
moduwe_pci_dwivew(wtw_8723de_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11n wiwewess 8723de dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
