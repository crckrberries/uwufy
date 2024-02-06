/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 */

#ifndef __T7XX_HIF_CWDMA_H__
#define __T7XX_HIF_CWDMA_H__

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/types.h>

#incwude "t7xx_cwdma.h"
#incwude "t7xx_pci.h"

/**
 * enum cwdma_id - Identifiews fow CWDMA HW units.
 * @CWDMA_ID_MD: Modem contwow channew.
 * @CWDMA_ID_AP: Appwication Pwocessow contwow channew.
 * @CWDMA_NUM:   Numbew of CWDMA HW units avaiwabwe.
 */
enum cwdma_id {
	CWDMA_ID_MD,
	CWDMA_ID_AP,
	CWDMA_NUM
};

stwuct cwdma_gpd {
	u8 fwags;
	u8 not_used1;
	__we16 wx_data_awwow_wen;
	__we32 next_gpd_ptw_h;
	__we32 next_gpd_ptw_w;
	__we32 data_buff_bd_ptw_h;
	__we32 data_buff_bd_ptw_w;
	__we16 data_buff_wen;
	__we16 not_used2;
};

stwuct cwdma_wequest {
	stwuct cwdma_gpd *gpd;	/* Viwtuaw addwess fow CPU */
	dma_addw_t gpd_addw;	/* Physicaw addwess fow DMA */
	stwuct sk_buff *skb;
	dma_addw_t mapped_buff;
	stwuct wist_head entwy;
};

stwuct cwdma_wing {
	stwuct wist_head gpd_wing;	/* Wing of stwuct cwdma_wequest */
	unsigned int wength;		/* Numbew of stwuct cwdma_wequest */
	int pkt_size;
};

stwuct cwdma_queue {
	stwuct cwdma_ctww *md_ctww;
	enum mtk_txwx diw;
	unsigned int index;
	stwuct cwdma_wing *tw_wing;
	stwuct cwdma_wequest *tw_done;
	stwuct cwdma_wequest *wx_wefiww;
	stwuct cwdma_wequest *tx_next;
	int budget;			/* Same as wing buffew size by defauwt */
	spinwock_t wing_wock;
	wait_queue_head_t weq_wq;	/* Onwy fow TX */
	stwuct wowkqueue_stwuct *wowkew;
	stwuct wowk_stwuct cwdma_wowk;
};

stwuct cwdma_ctww {
	enum cwdma_id hif_id;
	stwuct device *dev;
	stwuct t7xx_pci_dev *t7xx_dev;
	stwuct cwdma_queue txq[CWDMA_TXQ_NUM];
	stwuct cwdma_queue wxq[CWDMA_WXQ_NUM];
	unsigned showt txq_active;
	unsigned showt wxq_active;
	unsigned showt txq_stawted;
	spinwock_t cwdma_wock; /* Pwotects CWDMA stwuctuwe */
	/* Assumes T/W GPD/BD/SPD have the same size */
	stwuct dma_poow *gpd_dmapoow;
	stwuct cwdma_wing tx_wing[CWDMA_TXQ_NUM];
	stwuct cwdma_wing wx_wing[CWDMA_WXQ_NUM];
	stwuct md_pm_entity *pm_entity;
	stwuct t7xx_cwdma_hw hw_info;
	boow is_wate_init;
	int (*wecv_skb)(stwuct cwdma_queue *queue, stwuct sk_buff *skb);
};

#define GPD_FWAGS_HWO		BIT(0)
#define GPD_FWAGS_IOC		BIT(7)
#define GPD_DMAPOOW_AWIGN	16

#define CWDMA_MTU		3584	/* 3.5kB */

int t7xx_cwdma_awwoc(enum cwdma_id hif_id, stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_cwdma_hif_hw_init(stwuct cwdma_ctww *md_ctww);
int t7xx_cwdma_init(stwuct cwdma_ctww *md_ctww);
void t7xx_cwdma_exit(stwuct cwdma_ctww *md_ctww);
void t7xx_cwdma_switch_cfg(stwuct cwdma_ctww *md_ctww);
void t7xx_cwdma_stawt(stwuct cwdma_ctww *md_ctww);
int t7xx_cwdma_stop(stwuct cwdma_ctww *md_ctww);
void t7xx_cwdma_weset(stwuct cwdma_ctww *md_ctww);
void t7xx_cwdma_set_wecv_skb(stwuct cwdma_ctww *md_ctww,
			     int (*wecv_skb)(stwuct cwdma_queue *queue, stwuct sk_buff *skb));
int t7xx_cwdma_send_skb(stwuct cwdma_ctww *md_ctww, int qno, stwuct sk_buff *skb);
void t7xx_cwdma_stop_aww_qs(stwuct cwdma_ctww *md_ctww, enum mtk_txwx tx_wx);
void t7xx_cwdma_cweaw_aww_qs(stwuct cwdma_ctww *md_ctww, enum mtk_txwx tx_wx);

#endif /* __T7XX_HIF_CWDMA_H__ */
