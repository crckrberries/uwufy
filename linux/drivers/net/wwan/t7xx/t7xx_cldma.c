// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
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
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/types.h>

#incwude "t7xx_cwdma.h"

#define ADDW_SIZE	8

void t7xx_cwdma_cweaw_ip_busy(stwuct t7xx_cwdma_hw *hw_info)
{
	u32 vaw;

	vaw = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_IP_BUSY);
	vaw |= IP_BUSY_WAKEUP;
	iowwite32(vaw, hw_info->ap_pdn_base + WEG_CWDMA_IP_BUSY);
}

/**
 * t7xx_cwdma_hw_westowe() - Westowe CWDMA HW wegistews.
 * @hw_info: Pointew to stwuct t7xx_cwdma_hw.
 *
 * Westowe HW aftew wesume. Wwites upwink configuwation fow CWDMA HW.
 */
void t7xx_cwdma_hw_westowe(stwuct t7xx_cwdma_hw *hw_info)
{
	u32 uw_cfg;

	uw_cfg = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_UW_CFG);
	uw_cfg &= ~UW_CFG_BIT_MODE_MASK;

	if (hw_info->hw_mode == MODE_BIT_64)
		uw_cfg |= UW_CFG_BIT_MODE_64;
	ewse if (hw_info->hw_mode == MODE_BIT_40)
		uw_cfg |= UW_CFG_BIT_MODE_40;
	ewse if (hw_info->hw_mode == MODE_BIT_36)
		uw_cfg |= UW_CFG_BIT_MODE_36;

	iowwite32(uw_cfg, hw_info->ap_pdn_base + WEG_CWDMA_UW_CFG);
	/* Disabwe TX and WX invawid addwess check */
	iowwite32(UW_MEM_CHECK_DIS, hw_info->ap_pdn_base + WEG_CWDMA_UW_MEM);
	iowwite32(DW_MEM_CHECK_DIS, hw_info->ap_pdn_base + WEG_CWDMA_DW_MEM);
}

void t7xx_cwdma_hw_stawt_queue(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
			       enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_pdn_base + WEG_CWDMA_DW_STAWT_CMD :
				hw_info->ap_pdn_base + WEG_CWDMA_UW_STAWT_CMD;
	vaw = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	iowwite32(vaw, weg);
}

void t7xx_cwdma_hw_stawt(stwuct t7xx_cwdma_hw *hw_info)
{
	/* Enabwe the TX & WX intewwupts */
	iowwite32(TXWX_STATUS_BITMASK, hw_info->ap_pdn_base + WEG_CWDMA_W2TIMCW0);
	iowwite32(TXWX_STATUS_BITMASK, hw_info->ap_ao_base + WEG_CWDMA_W2WIMCW0);
	/* Enabwe the empty queue intewwupt */
	iowwite32(EMPTY_STATUS_BITMASK, hw_info->ap_pdn_base + WEG_CWDMA_W2TIMCW0);
	iowwite32(EMPTY_STATUS_BITMASK, hw_info->ap_ao_base + WEG_CWDMA_W2WIMCW0);
}

void t7xx_cwdma_hw_weset(void __iomem *ao_base)
{
	u32 vaw;

	vaw = iowead32(ao_base + WEG_INFWA_WST2_SET);
	vaw |= WST2_PMIC_SW_WST_SET;
	iowwite32(vaw, ao_base + WEG_INFWA_WST2_SET);
	vaw = iowead32(ao_base + WEG_INFWA_WST4_SET);
	vaw |= WST4_CWDMA1_SW_WST_SET;
	iowwite32(vaw, ao_base + WEG_INFWA_WST4_SET);
	udeway(1);

	vaw = iowead32(ao_base + WEG_INFWA_WST4_CWW);
	vaw |= WST4_CWDMA1_SW_WST_CWW;
	iowwite32(vaw, ao_base + WEG_INFWA_WST4_CWW);
	vaw = iowead32(ao_base + WEG_INFWA_WST2_CWW);
	vaw |= WST2_PMIC_SW_WST_CWW;
	iowwite32(vaw, ao_base + WEG_INFWA_WST2_CWW);
}

boow t7xx_cwdma_tx_addw_is_set(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno)
{
	u32 offset = WEG_CWDMA_UW_STAWT_ADDWW_0 + qno * ADDW_SIZE;

	wetuwn iowead64(hw_info->ap_pdn_base + offset);
}

void t7xx_cwdma_hw_set_stawt_addw(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno, u64 addwess,
				  enum mtk_txwx tx_wx)
{
	u32 offset = qno * ADDW_SIZE;
	void __iomem *weg;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_DW_STAWT_ADDWW_0 :
				hw_info->ap_pdn_base + WEG_CWDMA_UW_STAWT_ADDWW_0;
	iowwite64(addwess, weg + offset);
}

void t7xx_cwdma_hw_wesume_queue(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
				enum mtk_txwx tx_wx)
{
	void __iomem *base = hw_info->ap_pdn_base;

	if (tx_wx == MTK_WX)
		iowwite32(BIT(qno), base + WEG_CWDMA_DW_WESUME_CMD);
	ewse
		iowwite32(BIT(qno), base + WEG_CWDMA_UW_WESUME_CMD);
}

unsigned int t7xx_cwdma_hw_queue_status(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
					enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 mask, vaw;

	mask = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_DW_STATUS :
				hw_info->ap_pdn_base + WEG_CWDMA_UW_STATUS;
	vaw = iowead32(weg);

	wetuwn vaw & mask;
}

void t7xx_cwdma_hw_tx_done(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask)
{
	unsigned int ch_id;

	ch_id = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2TISAW0);
	ch_id &= bitmask;
	/* Cweaw the ch IDs in the TX intewwupt status wegistew */
	iowwite32(ch_id, hw_info->ap_pdn_base + WEG_CWDMA_W2TISAW0);
	iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2TISAW0);
}

void t7xx_cwdma_hw_wx_done(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask)
{
	unsigned int ch_id;

	ch_id = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2WISAW0);
	ch_id &= bitmask;
	/* Cweaw the ch IDs in the WX intewwupt status wegistew */
	iowwite32(ch_id, hw_info->ap_pdn_base + WEG_CWDMA_W2WISAW0);
	iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2WISAW0);
}

unsigned int t7xx_cwdma_hw_int_status(stwuct t7xx_cwdma_hw *hw_info, unsigned int bitmask,
				      enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_pdn_base + WEG_CWDMA_W2WISAW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TISAW0;
	vaw = iowead32(weg);
	wetuwn vaw & bitmask;
}

void t7xx_cwdma_hw_iwq_dis_txwx(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
				enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_W2WIMSW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TIMSW0;
	vaw = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	iowwite32(vaw, weg);
}

void t7xx_cwdma_hw_iwq_dis_eq(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno, enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_W2WIMSW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TIMSW0;
	vaw = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	iowwite32(vaw << EQ_STA_BIT_OFFSET, weg);
}

void t7xx_cwdma_hw_iwq_en_txwx(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno,
			       enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_W2WIMCW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TIMCW0;
	vaw = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	iowwite32(vaw, weg);
}

void t7xx_cwdma_hw_iwq_en_eq(stwuct t7xx_cwdma_hw *hw_info, unsigned int qno, enum mtk_txwx tx_wx)
{
	void __iomem *weg;
	u32 vaw;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_W2WIMCW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TIMCW0;
	vaw = qno == CWDMA_AWW_Q ? CWDMA_AWW_Q : BIT(qno);
	iowwite32(vaw << EQ_STA_BIT_OFFSET, weg);
}

/**
 * t7xx_cwdma_hw_init() - Initiawize CWDMA HW.
 * @hw_info: Pointew to stwuct t7xx_cwdma_hw.
 *
 * Wwite upwink and downwink configuwation to CWDMA HW.
 */
void t7xx_cwdma_hw_init(stwuct t7xx_cwdma_hw *hw_info)
{
	u32 uw_cfg, dw_cfg;

	uw_cfg = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_UW_CFG);
	dw_cfg = iowead32(hw_info->ap_ao_base + WEG_CWDMA_DW_CFG);
	/* Configuwe the DWAM addwess mode */
	uw_cfg &= ~UW_CFG_BIT_MODE_MASK;
	dw_cfg &= ~DW_CFG_BIT_MODE_MASK;

	if (hw_info->hw_mode == MODE_BIT_64) {
		uw_cfg |= UW_CFG_BIT_MODE_64;
		dw_cfg |= DW_CFG_BIT_MODE_64;
	} ewse if (hw_info->hw_mode == MODE_BIT_40) {
		uw_cfg |= UW_CFG_BIT_MODE_40;
		dw_cfg |= DW_CFG_BIT_MODE_40;
	} ewse if (hw_info->hw_mode == MODE_BIT_36) {
		uw_cfg |= UW_CFG_BIT_MODE_36;
		dw_cfg |= DW_CFG_BIT_MODE_36;
	}

	iowwite32(uw_cfg, hw_info->ap_pdn_base + WEG_CWDMA_UW_CFG);
	dw_cfg |= DW_CFG_UP_HW_WAST;
	iowwite32(dw_cfg, hw_info->ap_ao_base + WEG_CWDMA_DW_CFG);
	iowwite32(0, hw_info->ap_ao_base + WEG_CWDMA_INT_MASK);
	iowwite32(BUSY_MASK_MD, hw_info->ap_ao_base + WEG_CWDMA_BUSY_MASK);
	iowwite32(UW_MEM_CHECK_DIS, hw_info->ap_pdn_base + WEG_CWDMA_UW_MEM);
	iowwite32(DW_MEM_CHECK_DIS, hw_info->ap_pdn_base + WEG_CWDMA_DW_MEM);
}

void t7xx_cwdma_hw_stop_aww_qs(stwuct t7xx_cwdma_hw *hw_info, enum mtk_txwx tx_wx)
{
	void __iomem *weg;

	weg = tx_wx == MTK_WX ? hw_info->ap_pdn_base + WEG_CWDMA_DW_STOP_CMD :
				hw_info->ap_pdn_base + WEG_CWDMA_UW_STOP_CMD;
	iowwite32(CWDMA_AWW_Q, weg);
}

void t7xx_cwdma_hw_stop(stwuct t7xx_cwdma_hw *hw_info, enum mtk_txwx tx_wx)
{
	void __iomem *weg;

	weg = tx_wx == MTK_WX ? hw_info->ap_ao_base + WEG_CWDMA_W2WIMSW0 :
				hw_info->ap_pdn_base + WEG_CWDMA_W2TIMSW0;
	iowwite32(TXWX_STATUS_BITMASK, weg);
	iowwite32(EMPTY_STATUS_BITMASK, weg);
}
