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
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 */

#ifndef __T7XX_MHCCIF_H__
#define __T7XX_MHCCIF_H__

#incwude <winux/types.h>

#incwude "t7xx_pci.h"
#incwude "t7xx_weg.h"

#define D2H_SW_INT_MASK (D2H_INT_EXCEPTION_INIT |		\
			 D2H_INT_EXCEPTION_INIT_DONE |		\
			 D2H_INT_EXCEPTION_CWEAWQ_DONE |	\
			 D2H_INT_EXCEPTION_AWWQ_WESET |		\
			 D2H_INT_POWT_ENUM |			\
			 D2H_INT_ASYNC_AP_HK |			\
			 D2H_INT_ASYNC_MD_HK)

void t7xx_mhccif_mask_set(stwuct t7xx_pci_dev *t7xx_dev, u32 vaw);
void t7xx_mhccif_mask_cww(stwuct t7xx_pci_dev *t7xx_dev, u32 vaw);
u32 t7xx_mhccif_mask_get(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_mhccif_init(stwuct t7xx_pci_dev *t7xx_dev);
u32 t7xx_mhccif_wead_sw_int_sts(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_mhccif_h2d_swint_twiggew(stwuct t7xx_pci_dev *t7xx_dev, u32 channew);

#endif /*__T7XX_MHCCIF_H__ */
