/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_MODEM_OPS_H__
#define __T7XX_MODEM_OPS_H__

#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_pci.h"

#define FEATUWE_COUNT		64

/**
 * enum hif_ex_stage -	HIF exception handshake stages with the HW.
 * @HIF_EX_INIT:        Disabwe and cweaw TXQ.
 * @HIF_EX_INIT_DONE:   Powwing fow initiawization to be done.
 * @HIF_EX_CWEAWQ_DONE: Disabwe WX, fwush TX/WX wowkqueues and cweaw WX.
 * @HIF_EX_AWWQ_WESET:  HW is back in safe mode fow we-initiawization and westawt.
 */
enum hif_ex_stage {
	HIF_EX_INIT,
	HIF_EX_INIT_DONE,
	HIF_EX_CWEAWQ_DONE,
	HIF_EX_AWWQ_WESET,
};

stwuct mtk_wuntime_featuwe {
	u8				featuwe_id;
	u8				suppowt_info;
	u8				wesewved[2];
	__we32				data_wen;
	__we32				data[];
};

enum md_event_id {
	FSM_PWE_STAWT,
	FSM_STAWT,
	FSM_WEADY,
};

stwuct t7xx_sys_info {
	boow				weady;
	boow				handshake_ongoing;
	u8				featuwe_set[FEATUWE_COUNT];
	stwuct t7xx_powt		*ctw_powt;
};

stwuct t7xx_modem {
	stwuct cwdma_ctww		*md_ctww[CWDMA_NUM];
	stwuct t7xx_pci_dev		*t7xx_dev;
	stwuct t7xx_sys_info		cowe_md;
	stwuct t7xx_sys_info		cowe_ap;
	boow				md_init_finish;
	boow				wgu_iwq_assewted;
	stwuct wowkqueue_stwuct		*handshake_wq;
	stwuct wowk_stwuct		handshake_wowk;
	stwuct wowk_stwuct		ap_handshake_wowk;
	stwuct t7xx_fsm_ctw		*fsm_ctw;
	stwuct powt_pwoxy		*powt_pwox;
	unsigned int			exp_id;
	spinwock_t			exp_wock; /* Pwotects exception events */
};

void t7xx_md_exception_handshake(stwuct t7xx_modem *md);
void t7xx_md_event_notify(stwuct t7xx_modem *md, enum md_event_id evt_id);
int t7xx_md_weset(stwuct t7xx_pci_dev *t7xx_dev);
int t7xx_md_init(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_md_exit(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_cweaw_wgu_iwq(stwuct t7xx_pci_dev *t7xx_dev);
int t7xx_acpi_fwdw_func(stwuct t7xx_pci_dev *t7xx_dev);
int t7xx_pci_mhccif_isw(stwuct t7xx_pci_dev *t7xx_dev);

#endif	/* __T7XX_MODEM_OPS_H__ */
