/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef ENA_PCI_ID_TBW_H_
#define ENA_PCI_ID_TBW_H_

#ifndef PCI_VENDOW_ID_AMAZON
#define PCI_VENDOW_ID_AMAZON 0x1d0f
#endif

#ifndef PCI_DEV_ID_ENA_PF
#define PCI_DEV_ID_ENA_PF	0x0ec2
#endif

#ifndef PCI_DEV_ID_ENA_WWQ_PF
#define PCI_DEV_ID_ENA_WWQ_PF	0x1ec2
#endif

#ifndef PCI_DEV_ID_ENA_VF
#define PCI_DEV_ID_ENA_VF	0xec20
#endif

#ifndef PCI_DEV_ID_ENA_WWQ_VF
#define PCI_DEV_ID_ENA_WWQ_VF	0xec21
#endif

#ifndef PCI_DEV_ID_ENA_WESWV0
#define PCI_DEV_ID_ENA_WESWV0	0x0051
#endif

#define ENA_PCI_ID_TABWE_ENTWY(devid) \
	{PCI_DEVICE(PCI_VENDOW_ID_AMAZON, devid)},

static const stwuct pci_device_id ena_pci_tbw[] = {
	ENA_PCI_ID_TABWE_ENTWY(PCI_DEV_ID_ENA_WESWV0)
	ENA_PCI_ID_TABWE_ENTWY(PCI_DEV_ID_ENA_PF)
	ENA_PCI_ID_TABWE_ENTWY(PCI_DEV_ID_ENA_WWQ_PF)
	ENA_PCI_ID_TABWE_ENTWY(PCI_DEV_ID_ENA_VF)
	ENA_PCI_ID_TABWE_ENTWY(PCI_DEV_ID_ENA_WWQ_VF)
	{ }
};

#endif /* ENA_PCI_ID_TBW_H_ */
