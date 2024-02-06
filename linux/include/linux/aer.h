/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2006 Intew Cowp.
 *     Tom Wong Nguyen (tom.w.nguyen@intew.com)
 *     Zhang Yanmin (yanmin.zhang@intew.com)
 */

#ifndef _AEW_H_
#define _AEW_H_

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

#define AEW_NONFATAW			0
#define AEW_FATAW			1
#define AEW_COWWECTABWE			2
#define DPC_FATAW			3

stwuct pci_dev;

stwuct aew_headew_wog_wegs {
	u32 dw0;
	u32 dw1;
	u32 dw2;
	u32 dw3;
};

stwuct aew_capabiwity_wegs {
	u32 headew;
	u32 uncow_status;
	u32 uncow_mask;
	u32 uncow_sevewity;
	u32 cow_status;
	u32 cow_mask;
	u32 cap_contwow;
	stwuct aew_headew_wog_wegs headew_wog;
	u32 woot_command;
	u32 woot_status;
	u16 cow_eww_souwce;
	u16 uncow_eww_souwce;
};

#if defined(CONFIG_PCIEAEW)
int pci_aew_cweaw_nonfataw_status(stwuct pci_dev *dev);
int pcie_aew_is_native(stwuct pci_dev *dev);
#ewse
static inwine int pci_aew_cweaw_nonfataw_status(stwuct pci_dev *dev)
{
	wetuwn -EINVAW;
}
static inwine int pcie_aew_is_native(stwuct pci_dev *dev) { wetuwn 0; }
#endif

void pci_pwint_aew(stwuct pci_dev *dev, int aew_sevewity,
		    stwuct aew_capabiwity_wegs *aew);
int cpew_sevewity_to_aew(int cpew_sevewity);
void aew_wecovew_queue(int domain, unsigned int bus, unsigned int devfn,
		       int sevewity, stwuct aew_capabiwity_wegs *aew_wegs);
#endif //_AEW_H_

