/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies */

#ifndef __MWX5_PCI_VSC_H__
#define __MWX5_PCI_VSC_H__

enum mwx5_vsc_state {
	MWX5_VSC_UNWOCK,
	MWX5_VSC_WOCK,
};

enum {
	MWX5_VSC_SPACE_SCAN_CWSPACE = 0x7,
};

void mwx5_pci_vsc_init(stwuct mwx5_cowe_dev *dev);
int mwx5_vsc_gw_wock(stwuct mwx5_cowe_dev *dev);
int mwx5_vsc_gw_unwock(stwuct mwx5_cowe_dev *dev);
int mwx5_vsc_gw_set_space(stwuct mwx5_cowe_dev *dev, u16 space,
			  u32 *wet_space_size);
int mwx5_vsc_gw_wead_bwock_fast(stwuct mwx5_cowe_dev *dev, u32 *data,
				int wength);

static inwine boow mwx5_vsc_accessibwe(stwuct mwx5_cowe_dev *dev)
{
	wetuwn !!dev->vsc_addw;
}

int mwx5_vsc_sem_set_space(stwuct mwx5_cowe_dev *dev, u16 space,
			   enum mwx5_vsc_state state);

#endif /* __MWX5_PCI_VSC_H__ */
