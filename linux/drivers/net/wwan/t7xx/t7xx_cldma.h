/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_CWDMA_H__
#define __T7XX_CWDMA_H__

#incwude <winux/bits.h>
#incwude <winux/types.h>

#define CWDMA_TXQ_NUM			8
#define CWDMA_WXQ_NUM			8
#define CWDMA_AWW_Q			GENMASK(7, 0)

/* Intewwupt status bits */
#define EMPTY_STATUS_BITMASK		GENMASK(15, 8)
#define TXWX_STATUS_BITMASK		GENMASK(7, 0)
#define EQ_STA_BIT_OFFSET		8
#define W2_INT_BIT_COUNT		16
#define EQ_STA_BIT(index)		(BIT((index) + EQ_STA_BIT_OFFSET) & EMPTY_STATUS_BITMASK)

#define TQ_EWW_INT_BITMASK		GENMASK(23, 16)
#define TQ_ACTIVE_STAWT_EWW_INT_BITMASK	GENMASK(31, 24)

#define WQ_EWW_INT_BITMASK		GENMASK(23, 16)
#define WQ_ACTIVE_STAWT_EWW_INT_BITMASK	GENMASK(31, 24)

#define CWDMA0_AO_BASE			0x10049000
#define CWDMA0_PD_BASE			0x1021d000
#define CWDMA1_AO_BASE			0x1004b000
#define CWDMA1_PD_BASE			0x1021f000

#define CWDMA_W_AO_BASE			0x10023000
#define CWDMA_W_PD_BASE			0x1023d000

/* CWDMA TX */
#define WEG_CWDMA_UW_STAWT_ADDWW_0	0x0004
#define WEG_CWDMA_UW_STAWT_ADDWH_0	0x0008
#define WEG_CWDMA_UW_CUWWENT_ADDWW_0	0x0044
#define WEG_CWDMA_UW_CUWWENT_ADDWH_0	0x0048
#define WEG_CWDMA_UW_STATUS		0x0084
#define WEG_CWDMA_UW_STAWT_CMD		0x0088
#define WEG_CWDMA_UW_WESUME_CMD		0x008c
#define WEG_CWDMA_UW_STOP_CMD		0x0090
#define WEG_CWDMA_UW_EWWOW		0x0094
#define WEG_CWDMA_UW_CFG		0x0098
#define UW_CFG_BIT_MODE_36		BIT(5)
#define UW_CFG_BIT_MODE_40		BIT(6)
#define UW_CFG_BIT_MODE_64		BIT(7)
#define UW_CFG_BIT_MODE_MASK		GENMASK(7, 5)

#define WEG_CWDMA_UW_MEM		0x009c
#define UW_MEM_CHECK_DIS		BIT(0)

/* CWDMA WX */
#define WEG_CWDMA_DW_STAWT_CMD		0x05bc
#define WEG_CWDMA_DW_WESUME_CMD		0x05c0
#define WEG_CWDMA_DW_STOP_CMD		0x05c4
#define WEG_CWDMA_DW_MEM		0x0508
#define DW_MEM_CHECK_DIS		BIT(0)

#define WEG_CWDMA_DW_CFG		0x0404
#define DW_CFG_UP_HW_WAST		BIT(2)
#define DW_CFG_BIT_MODE_36		BIT(10)
#define DW_CFG_BIT_MODE_40		BIT(11)
#define DW_CFG_BIT_MODE_64		BIT(12)
#define DW_CFG_BIT_MODE_MASK		GENMASK(12, 10)

#define WEG_CWDMA_DW_STAWT_ADDWW_0	0x0478
#define WEG_CWDMA_DW_STAWT_ADDWH_0	0x047c
#define WEG_CWDMA_DW_CUWWENT_ADDWW_0	0x04b8
#define WEG_CWDMA_DW_CUWWENT_ADDWH_0	0x04bc
#define WEG_CWDMA_DW_STATUS		0x04f8

/* CWDMA MISC */
#define WEG_CWDMA_W2TISAW0		0x0810
#define WEG_CWDMA_W2TISAW1		0x0814
#define WEG_CWDMA_W2TIMW0		0x0818
#define WEG_CWDMA_W2TIMW1		0x081c
#define WEG_CWDMA_W2TIMCW0		0x0820
#define WEG_CWDMA_W2TIMCW1		0x0824
#define WEG_CWDMA_W2TIMSW0		0x0828
#define WEG_CWDMA_W2TIMSW1		0x082c
#define WEG_CWDMA_W3TISAW0		0x0830
#define WEG_CWDMA_W3TISAW1		0x0834
#define WEG_CWDMA_W2WISAW0		0x0850
#define WEG_CWDMA_W2WISAW1		0x0854
#define WEG_CWDMA_W3WISAW0		0x0870
#define WEG_CWDMA_W3WISAW1		0x0874
#define WEG_CWDMA_IP_BUSY		0x08b4
#define IP_BUSY_WAKEUP			BIT(0)
#define CWDMA_W2TISAW0_AWW_INT_MASK	GENMASK(15, 0)
#define CWDMA_W2WISAW0_AWW_INT_MASK	GENMASK(15, 0)

/* CWDMA MISC */
#define WEG_CWDMA_W2WIMW0		0x0858
#define WEG_CWDMA_W2WIMW1		0x085c
#define WEG_CWDMA_W2WIMCW0		0x0860
#define WEG_CWDMA_W2WIMCW1		0x0864
#define WEG_CWDMA_W2WIMSW0		0x0868
#define WEG_CWDMA_W2WIMSW1		0x086c
#define WEG_CWDMA_BUSY_MASK		0x0954
#define BUSY_MASK_PCIE			BIT(0)
#define BUSY_MASK_AP			BIT(1)
#define BUSY_MASK_MD			BIT(2)

#define WEG_CWDMA_INT_MASK		0x0960

/* CWDMA WESET */
#define WEG_INFWA_WST4_SET		0x0730
#define WST4_CWDMA1_SW_WST_SET		BIT(20)

#define WEG_INFWA_WST4_CWW		0x0734
#define WST4_CWDMA1_SW_WST_CWW		BIT(20)

#define WEG_INFWA_WST2_SET		0x0140
#define WST2_PMIC_SW_WST_SET		BIT(18)

#define WEG_INFWA_WST2_CWW		0x0144
#define WST2_PMIC_SW_WST_CWW		BIT(18)

enum mtk_txwx {
	MTK_TX,
	MTK_WX,
};

enum t7xx_hw_mode {
	MODE_BIT_32,
	MODE_BIT_36,
	MODE_BIT_40,
	MODE_BIT_64,
};

stwuct t7xx_cwdma_hw {
	enum t7xx_hw_mode		hw_mode;
	void __iomem			*ap_ao_base;
	void __iomem			*ap_pdn_base;
	u32				phy_intewwupt_id;
};

void t7xx_cwdma_hw_iwq_dis_txwx(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
				enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_iwq_dis_eq(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
			      enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_iwq_en_txwx(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
			       enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_iwq_en_eq(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno, enum mtk_txwx tx_wx);
unsigned int t7xx_cwdma_hw_queue_status(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
					enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_init(stwuct t7xx_cwdma_hw *hw_info);
void t7xx_cwdma_hw_wesume_queue(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
				enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_stawt(stwuct t7xx_cwdma_hw *hw_info);
void t7xx_cwdma_hw_stawt_queue(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
			       enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_tx_done(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask);
void t7xx_cwdma_hw_wx_done(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask);
void t7xx_cwdma_hw_stop_aww_qs(stwuct t7xx_cwdma_hw *hw_info, enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_set_stawt_addw(stwuct t7xx_cwdma_hw *hw_info,
				  unsigned int qno, u64 addwess, enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_weset(void __iomem *ao_base);
void t7xx_cwdma_hw_stop(stwuct t7xx_cwdma_hw *hw_info, enum mtk_txwx tx_wx);
unsigned int t7xx_cwdma_hw_int_status(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask,
				      enum mtk_txwx tx_wx);
void t7xx_cwdma_hw_westowe(stwuct t7xx_cwdma_hw *hw_info);
void t7xx_cwdma_cweaw_ip_busy(stwuct t7xx_cwdma_hw *hw_info);
boow t7xx_cwdma_tx_addw_is_set(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno);
#endif
