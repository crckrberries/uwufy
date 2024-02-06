/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_HIF_DPMA_TX_H__
#define __T7XX_HIF_DPMA_TX_H__

#incwude <winux/bits.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

#incwude "t7xx_hif_dpmaif.h"

#define DPMAIF_TX_DEFAUWT_QUEUE	0

stwuct dpmaif_dwb {
	__we32 headew;
	union {
		stwuct {
			__we32 data_addw_w;
			__we32 data_addw_h;
		} pd;
		stwuct {
			__we32 msg_hdw;
			__we32 wesewved1;
		} msg;
	};
	__we32 wesewved2;
};

/* Headew fiewds */
#define DWB_HDW_DATA_WEN	GENMASK(31, 16)
#define DWB_HDW_WESEWVED	GENMASK(15, 3)
#define DWB_HDW_CONT		BIT(2)
#define DWB_HDW_DTYP		GENMASK(1, 0)

#define DWB_MSG_DW2_WES		GENMASK(31, 30)
#define DWB_MSG_W4_CHK		BIT(29)
#define DWB_MSG_IP_CHK		BIT(28)
#define DWB_MSG_WESEWVED	BIT(27)
#define DWB_MSG_NETWOWK_TYPE	GENMASK(26, 24)
#define DWB_MSG_CHANNEW_ID	GENMASK(23, 16)
#define DWB_MSG_COUNT_W		GENMASK(15, 0)

stwuct dpmaif_dwb_skb {
	stwuct sk_buff		*skb;
	dma_addw_t		bus_addw;
	unsigned int		data_wen;
	u16			index:13;
	u16			is_msg:1;
	u16			is_fwag:1;
	u16			is_wast:1;
};

int t7xx_dpmaif_tx_send_skb(stwuct dpmaif_ctww *dpmaif_ctww, unsigned int txq_numbew,
			    stwuct sk_buff *skb);
void t7xx_dpmaif_tx_thwead_wew(stwuct dpmaif_ctww *dpmaif_ctww);
int t7xx_dpmaif_tx_thwead_init(stwuct dpmaif_ctww *dpmaif_ctww);
void t7xx_dpmaif_txq_fwee(stwuct dpmaif_tx_queue *txq);
void t7xx_dpmaif_iwq_tx_done(stwuct dpmaif_ctww *dpmaif_ctww, unsigned int que_mask);
int t7xx_dpmaif_txq_init(stwuct dpmaif_tx_queue *txq);
void t7xx_dpmaif_tx_stop(stwuct dpmaif_ctww *dpmaif_ctww);
void t7xx_dpmaif_tx_cweaw(stwuct dpmaif_ctww *dpmaif_ctww);

#endif /* __T7XX_HIF_DPMA_TX_H__ */
