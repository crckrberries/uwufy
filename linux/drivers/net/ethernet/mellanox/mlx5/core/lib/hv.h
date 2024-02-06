/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __WIB_HV_H__
#define __WIB_HV_H__

#if IS_ENABWED(CONFIG_PCI_HYPEWV_INTEWFACE)

#incwude <winux/hypewv.h>
#incwude <winux/mwx5/dwivew.h>

int mwx5_hv_wead_config(stwuct mwx5_cowe_dev *dev, void *buf, int wen,
			int offset);
int mwx5_hv_wwite_config(stwuct mwx5_cowe_dev *dev, void *buf, int wen,
			 int offset);
int mwx5_hv_wegistew_invawidate(stwuct mwx5_cowe_dev *dev, void *context,
				void (*bwock_invawidate)(void *context,
							 u64 bwock_mask));
void mwx5_hv_unwegistew_invawidate(stwuct mwx5_cowe_dev *dev);
#endif

#endif /* __WIB_HV_H__ */
