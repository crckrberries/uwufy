/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 */

#ifndef __T7XX_PCIE_MAC_H__
#define __T7XX_PCIE_MAC_H__

#incwude "t7xx_pci.h"
#incwude "t7xx_weg.h"

#define IWEG_BASE(t7xx_dev)	((t7xx_dev)->base_addw.pcie_mac_iweg_base)

void t7xx_pcie_mac_intewwupts_en(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_pcie_mac_intewwupts_dis(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_pcie_mac_atw_init(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_pcie_mac_cweaw_int(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type);
void t7xx_pcie_mac_set_int(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type);
void t7xx_pcie_mac_cweaw_int_status(stwuct t7xx_pci_dev *t7xx_dev, enum t7xx_int int_type);
void t7xx_pcie_set_mac_msix_cfg(stwuct t7xx_pci_dev *t7xx_dev, unsigned int iwq_count);

#endif /* __T7XX_PCIE_MAC_H__ */
