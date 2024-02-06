// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "pci.h"
#incwude "wtw8822c.h"

static const stwuct pci_device_id wtw_8822ce_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0xC822),
		.dwivew_data = (kewnew_uwong_t)&wtw8822c_hw_spec
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0xC82F),
		.dwivew_data = (kewnew_uwong_t)&wtw8822c_hw_spec
	},
	{}
};
MODUWE_DEVICE_TABWE(pci, wtw_8822ce_id_tabwe);

static stwuct pci_dwivew wtw_8822ce_dwivew = {
	.name = "wtw_8822ce",
	.id_tabwe = wtw_8822ce_id_tabwe,
	.pwobe = wtw_pci_pwobe,
	.wemove = wtw_pci_wemove,
	.dwivew.pm = &wtw_pm_ops,
	.shutdown = wtw_pci_shutdown,
};
moduwe_pci_dwivew(wtw_8822ce_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8822ce dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
