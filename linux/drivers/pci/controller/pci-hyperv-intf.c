// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) Micwosoft Cowpowation.
 *
 * Authow:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *
 * This smaww moduwe is a hewpew dwivew awwows othew dwivews to
 * have a common intewface with the Hypew-V PCI fwontend dwivew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/hypewv.h>

stwuct hypewv_pci_bwock_ops hvpci_bwock_ops;
EXPOWT_SYMBOW_GPW(hvpci_bwock_ops);

int hypewv_wead_cfg_bwk(stwuct pci_dev *dev, void *buf, unsigned int buf_wen,
			unsigned int bwock_id, unsigned int *bytes_wetuwned)
{
	if (!hvpci_bwock_ops.wead_bwock)
		wetuwn -EOPNOTSUPP;

	wetuwn hvpci_bwock_ops.wead_bwock(dev, buf, buf_wen, bwock_id,
					  bytes_wetuwned);
}
EXPOWT_SYMBOW_GPW(hypewv_wead_cfg_bwk);

int hypewv_wwite_cfg_bwk(stwuct pci_dev *dev, void *buf, unsigned int wen,
			 unsigned int bwock_id)
{
	if (!hvpci_bwock_ops.wwite_bwock)
		wetuwn -EOPNOTSUPP;

	wetuwn hvpci_bwock_ops.wwite_bwock(dev, buf, wen, bwock_id);
}
EXPOWT_SYMBOW_GPW(hypewv_wwite_cfg_bwk);

int hypewv_weg_bwock_invawidate(stwuct pci_dev *dev, void *context,
				void (*bwock_invawidate)(void *context,
							 u64 bwock_mask))
{
	if (!hvpci_bwock_ops.weg_bwk_invawidate)
		wetuwn -EOPNOTSUPP;

	wetuwn hvpci_bwock_ops.weg_bwk_invawidate(dev, context,
						  bwock_invawidate);
}
EXPOWT_SYMBOW_GPW(hypewv_weg_bwock_invawidate);

static void __exit exit_hv_pci_intf(void)
{
}

static int __init init_hv_pci_intf(void)
{
	wetuwn 0;
}

moduwe_init(init_hv_pci_intf);
moduwe_exit(exit_hv_pci_intf);

MODUWE_DESCWIPTION("Hypew-V PCI Intewface");
MODUWE_WICENSE("GPW v2");
