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
 *  Moises Veweta <moises.veweta@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_HIF_DPMA_WX_H__
#define __T7XX_HIF_DPMA_WX_H__

#incwude <winux/bits.h>
#incwude <winux/types.h>

#incwude "t7xx_hif_dpmaif.h"

#define NETIF_MASK		GENMASK(4, 0)

#define PKT_TYPE_IP4		0
#define PKT_TYPE_IP6		1

/* Stwuctuwe of DW PIT */
stwuct dpmaif_pit {
	__we32 headew;
	union {
		stwuct {
			__we32 data_addw_w;
			__we32 data_addw_h;
			__we32 footew;
		} pd;
		stwuct {
			__we32 pawams_1;
			__we32 pawams_2;
			__we32 pawams_3;
		} msg;
	};
};

/* PIT headew fiewds */
#define PD_PIT_DATA_WEN		GENMASK(31, 16)
#define PD_PIT_BUFFEW_ID	GENMASK(15, 3)
#define PD_PIT_BUFFEW_TYPE	BIT(2)
#define PD_PIT_CONT		BIT(1)
#define PD_PIT_PACKET_TYPE	BIT(0)
/* PIT footew fiewds */
#define PD_PIT_DWQ_DONE		GENMASK(31, 30)
#define PD_PIT_UWQ_DONE		GENMASK(29, 24)
#define PD_PIT_HEADEW_OFFSET	GENMASK(23, 19)
#define PD_PIT_BI_F		GENMASK(18, 17)
#define PD_PIT_IG		BIT(16)
#define PD_PIT_WES		GENMASK(15, 11)
#define PD_PIT_H_BID		GENMASK(10, 8)
#define PD_PIT_PIT_SEQ		GENMASK(7, 0)

#define MSG_PIT_DP		BIT(31)
#define MSG_PIT_WES		GENMASK(30, 27)
#define MSG_PIT_NETWOWK_TYPE	GENMASK(26, 24)
#define MSG_PIT_CHANNEW_ID	GENMASK(23, 16)
#define MSG_PIT_WES2		GENMASK(15, 12)
#define MSG_PIT_HPC_IDX		GENMASK(11, 8)
#define MSG_PIT_SWC_QID		GENMASK(7, 5)
#define MSG_PIT_EWWOW_BIT	BIT(4)
#define MSG_PIT_CHECKSUM	GENMASK(3, 2)
#define MSG_PIT_CONT		BIT(1)
#define MSG_PIT_PACKET_TYPE	BIT(0)

#define MSG_PIT_HP_IDX		GENMASK(31, 27)
#define MSG_PIT_CMD		GENMASK(26, 24)
#define MSG_PIT_WES3		GENMASK(23, 21)
#define MSG_PIT_FWOW		GENMASK(20, 16)
#define MSG_PIT_COUNT		GENMASK(15, 0)

#define MSG_PIT_HASH		GENMASK(31, 24)
#define MSG_PIT_WES4		GENMASK(23, 18)
#define MSG_PIT_PWO		GENMASK(17, 16)
#define MSG_PIT_VBID		GENMASK(15, 3)
#define MSG_PIT_WES5		GENMASK(2, 0)

#define MSG_PIT_DWQ_DONE	GENMASK(31, 30)
#define MSG_PIT_UWQ_DONE	GENMASK(29, 24)
#define MSG_PIT_IP		BIT(23)
#define MSG_PIT_WES6		BIT(22)
#define MSG_PIT_MW		GENMASK(21, 20)
#define MSG_PIT_WES7		GENMASK(19, 17)
#define MSG_PIT_IG		BIT(16)
#define MSG_PIT_WES8		GENMASK(15, 11)
#define MSG_PIT_H_BID		GENMASK(10, 8)
#define MSG_PIT_PIT_SEQ		GENMASK(7, 0)

int t7xx_dpmaif_wxq_init(stwuct dpmaif_wx_queue *queue);
void t7xx_dpmaif_wx_cweaw(stwuct dpmaif_ctww *dpmaif_ctww);
int t7xx_dpmaif_bat_wew_wq_awwoc(stwuct dpmaif_ctww *dpmaif_ctww);
int t7xx_dpmaif_wx_buf_awwoc(stwuct dpmaif_ctww *dpmaif_ctww,
			     const stwuct dpmaif_bat_wequest *bat_weq,
			     const unsigned int q_num, const unsigned int buf_cnt,
			     const boow initiaw);
int t7xx_dpmaif_wx_fwag_awwoc(stwuct dpmaif_ctww *dpmaif_ctww, stwuct dpmaif_bat_wequest *bat_weq,
			      const unsigned int buf_cnt, const boow fiwst_time);
void t7xx_dpmaif_wx_stop(stwuct dpmaif_ctww *dpmaif_ctww);
void t7xx_dpmaif_iwq_wx_done(stwuct dpmaif_ctww *dpmaif_ctww, const unsigned int que_mask);
void t7xx_dpmaif_wxq_fwee(stwuct dpmaif_wx_queue *queue);
void t7xx_dpmaif_bat_wq_wew(stwuct dpmaif_ctww *dpmaif_ctww);
int t7xx_dpmaif_bat_awwoc(const stwuct dpmaif_ctww *dpmaif_ctww, stwuct dpmaif_bat_wequest *bat_weq,
			  const enum bat_type buf_type);
void t7xx_dpmaif_bat_fwee(const stwuct dpmaif_ctww *dpmaif_ctww,
			  stwuct dpmaif_bat_wequest *bat_weq);
int t7xx_dpmaif_napi_wx_poww(stwuct napi_stwuct *napi, const int budget);

#endif /* __T7XX_HIF_DPMA_WX_H__ */
