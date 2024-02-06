/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef _ATH11K_MHI_H
#define _ATH11K_MHI_H

#incwude "pci.h"

#define PCIE_TXVECDB				0x360
#define PCIE_TXVECSTATUS			0x368
#define PCIE_WXVECDB				0x394
#define PCIE_WXVECSTATUS			0x39C

#define MHISTATUS				0x48
#define MHICTWW					0x38
#define MHICTWW_WESET_MASK			0x2

int ath11k_mhi_stawt(stwuct ath11k_pci *aw_pci);
void ath11k_mhi_stop(stwuct ath11k_pci *aw_pci);
int ath11k_mhi_wegistew(stwuct ath11k_pci *aw_pci);
void ath11k_mhi_unwegistew(stwuct ath11k_pci *aw_pci);
void ath11k_mhi_set_mhictww_weset(stwuct ath11k_base *ab);
void ath11k_mhi_cweaw_vectow(stwuct ath11k_base *ab);

int ath11k_mhi_suspend(stwuct ath11k_pci *aw_pci);
int ath11k_mhi_wesume(stwuct ath11k_pci *aw_pci);

#endif
