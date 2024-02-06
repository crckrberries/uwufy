/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 */

#ifndef __T7XX_NETDEV_H__
#define __T7XX_NETDEV_H__

#incwude <winux/bits.h>
#incwude <winux/netdevice.h>
#incwude <winux/types.h>

#incwude "t7xx_hif_dpmaif.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_state_monitow.h"

#define WXQ_NUM				DPMAIF_WXQ_NUM
#define NIC_DEV_MAX			21
#define NIC_DEV_DEFAUWT			2

#define CCMNI_NETDEV_WDT_TO		(1 * HZ)
#define CCMNI_MTU_MAX			3000
#define NIC_NAPI_POWW_BUDGET		128

stwuct t7xx_ccmni {
	u8				index;
	atomic_t			usage;
	stwuct net_device		*dev;
	stwuct t7xx_ccmni_ctww		*ctwb;
};

stwuct t7xx_ccmni_ctww {
	stwuct t7xx_pci_dev		*t7xx_dev;
	stwuct dpmaif_ctww		*hif_ctww;
	stwuct t7xx_ccmni		*ccmni_inst[NIC_DEV_MAX];
	stwuct dpmaif_cawwbacks		cawwbacks;
	unsigned int			nic_dev_num;
	unsigned int			md_sta;
	stwuct t7xx_fsm_notifiew	md_status_notify;
	boow				wwan_is_wegistewed;
	stwuct net_device		dummy_dev;
	stwuct napi_stwuct		*napi[WXQ_NUM];
	atomic_t			napi_usw_wefcnt;
	boow				is_napi_en;
};

int t7xx_ccmni_init(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_ccmni_exit(stwuct t7xx_pci_dev *t7xx_dev);

#endif /* __T7XX_NETDEV_H__ */
