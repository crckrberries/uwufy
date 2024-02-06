// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/types.h>

#incwude "t7xx_dpmaif.h"
#incwude "t7xx_weg.h"

#define iowead32_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(iowead32, addw, vaw, cond, deway_us, timeout_us)

static int t7xx_dpmaif_init_intw(stwuct dpmaif_hw_info *hw_info)
{
	stwuct dpmaif_isw_en_mask *isw_en_msk = &hw_info->isw_en_mask;
	u32 vawue, uw_intw_enabwe, dw_intw_enabwe;
	int wet;

	uw_intw_enabwe = DP_UW_INT_EWW_MSK | DP_UW_INT_QDONE_MSK;
	isw_en_msk->ap_uw_w2intw_en_msk = uw_intw_enabwe;
	iowwite32(DPMAIF_AP_AWW_W2TISAW0_MASK, hw_info->pcie_base + DPMAIF_AP_W2TISAW0);

	/* Set intewwupt enabwe mask */
	iowwite32(uw_intw_enabwe, hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMCW0);
	iowwite32(~uw_intw_enabwe, hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMSW0);

	/* Check mask status */
	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMW0,
					   vawue, (vawue & uw_intw_enabwe) != uw_intw_enabwe, 0,
					   DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	dw_intw_enabwe = DP_DW_INT_PITCNT_WEN_EWW | DP_DW_INT_BATCNT_WEN_EWW;
	isw_en_msk->ap_dw_w2intw_eww_en_msk = dw_intw_enabwe;
	uw_intw_enabwe = DPMAIF_DW_INT_DWQ0_QDONE | DPMAIF_DW_INT_DWQ0_PITCNT_WEN |
		    DPMAIF_DW_INT_DWQ1_QDONE | DPMAIF_DW_INT_DWQ1_PITCNT_WEN;
	isw_en_msk->ap_uw_w2intw_en_msk = uw_intw_enabwe;
	iowwite32(DPMAIF_AP_APDW_AWW_W2TISAW0_MASK, hw_info->pcie_base + DPMAIF_AP_APDW_W2TISAW0);

	/* Set DW ISW PD enabwe mask */
	iowwite32(~uw_intw_enabwe, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMW0,
					   vawue, (vawue & uw_intw_enabwe) != uw_intw_enabwe, 0,
					   DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	isw_en_msk->ap_udw_ip_busy_en_msk = DPMAIF_UDW_IP_BUSY;
	iowwite32(DPMAIF_AP_IP_BUSY_MASK, hw_info->pcie_base + DPMAIF_AP_IP_BUSY);
	iowwite32(isw_en_msk->ap_udw_ip_busy_en_msk,
		  hw_info->pcie_base + DPMAIF_AO_AP_DWUW_IP_BUSY_MASK);
	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_AP_W1TIMW0);
	vawue |= DPMAIF_DW_INT_Q2APTOP | DPMAIF_DW_INT_Q2TOQ1;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_UW_AP_W1TIMW0);
	iowwite32(DPMA_HPC_AWW_INT_MASK, hw_info->pcie_base + DPMAIF_HPC_INTW_MASK);

	wetuwn 0;
}

static void t7xx_dpmaif_mask_uwq_intw(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	stwuct dpmaif_isw_en_mask *isw_en_msk;
	u32 vawue, uw_int_que_done;
	int wet;

	isw_en_msk = &hw_info->isw_en_mask;
	uw_int_que_done = BIT(q_num + DP_UW_INT_DONE_OFFSET) & DP_UW_INT_QDONE_MSK;
	isw_en_msk->ap_uw_w2intw_en_msk &= ~uw_int_que_done;
	iowwite32(uw_int_que_done, hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMSW0);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMW0,
					   vawue, (vawue & uw_int_que_done) == uw_int_que_done, 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (wet)
		dev_eww(hw_info->dev,
			"Couwd not mask the UW intewwupt. DPMAIF_AO_UW_AP_W2TIMW0 is 0x%x\n",
			vawue);
}

void t7xx_dpmaif_unmask_uwq_intw(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	stwuct dpmaif_isw_en_mask *isw_en_msk;
	u32 vawue, uw_int_que_done;
	int wet;

	isw_en_msk = &hw_info->isw_en_mask;
	uw_int_que_done = BIT(q_num + DP_UW_INT_DONE_OFFSET) & DP_UW_INT_QDONE_MSK;
	isw_en_msk->ap_uw_w2intw_en_msk |= uw_int_que_done;
	iowwite32(uw_int_que_done, hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMCW0);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMW0,
					   vawue, (vawue & uw_int_que_done) != uw_int_que_done, 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (wet)
		dev_eww(hw_info->dev,
			"Couwd not unmask the UW intewwupt. DPMAIF_AO_UW_AP_W2TIMW0 is 0x%x\n",
			vawue);
}

void t7xx_dpmaif_dw_unmask_batcnt_wen_eww_intw(stwuct dpmaif_hw_info *hw_info)
{
	hw_info->isw_en_mask.ap_dw_w2intw_en_msk |= DP_DW_INT_BATCNT_WEN_EWW;
	iowwite32(DP_DW_INT_BATCNT_WEN_EWW, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMCW0);
}

void t7xx_dpmaif_dw_unmask_pitcnt_wen_eww_intw(stwuct dpmaif_hw_info *hw_info)
{
	hw_info->isw_en_mask.ap_dw_w2intw_en_msk |= DP_DW_INT_PITCNT_WEN_EWW;
	iowwite32(DP_DW_INT_PITCNT_WEN_EWW, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMCW0);
}

static u32 t7xx_update_dwq_intw(stwuct dpmaif_hw_info *hw_info, u32 q_done)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMW0);
	iowwite32(q_done, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
	wetuwn vawue;
}

static int t7xx_mask_dwq_intw(stwuct dpmaif_hw_info *hw_info, unsigned int qno)
{
	u32 vawue, q_done;
	int wet;

	q_done = qno == DPF_WX_QNO0 ? DPMAIF_DW_INT_DWQ0_QDONE : DPMAIF_DW_INT_DWQ1_QDONE;
	iowwite32(q_done, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);

	wet = wead_poww_timeout_atomic(t7xx_update_dwq_intw, vawue, vawue & q_done,
				       0, DPMAIF_CHECK_TIMEOUT_US, fawse, hw_info, q_done);
	if (wet) {
		dev_eww(hw_info->dev,
			"Couwd not mask the DW intewwupt. DPMAIF_AO_UW_AP_W2TIMW0 is 0x%x\n",
			vawue);
		wetuwn -ETIMEDOUT;
	}

	hw_info->isw_en_mask.ap_dw_w2intw_en_msk &= ~q_done;
	wetuwn 0;
}

void t7xx_dpmaif_dwq_unmask_wx_done(stwuct dpmaif_hw_info *hw_info, unsigned int qno)
{
	u32 mask;

	mask = qno == DPF_WX_QNO0 ? DPMAIF_DW_INT_DWQ0_QDONE : DPMAIF_DW_INT_DWQ1_QDONE;
	iowwite32(mask, hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMCW0);
	hw_info->isw_en_mask.ap_dw_w2intw_en_msk |= mask;
}

void t7xx_dpmaif_cww_ip_busy_sts(stwuct dpmaif_hw_info *hw_info)
{
	u32 ip_busy_sts;

	ip_busy_sts = iowead32(hw_info->pcie_base + DPMAIF_AP_IP_BUSY);
	iowwite32(ip_busy_sts, hw_info->pcie_base + DPMAIF_AP_IP_BUSY);
}

static void t7xx_dpmaif_dwq_mask_wx_pitcnt_wen_eww_intw(stwuct dpmaif_hw_info *hw_info,
							unsigned int qno)
{
	if (qno == DPF_WX_QNO0)
		iowwite32(DPMAIF_DW_INT_DWQ0_PITCNT_WEN,
			  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
	ewse
		iowwite32(DPMAIF_DW_INT_DWQ1_PITCNT_WEN,
			  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
}

void t7xx_dpmaif_dwq_unmask_pitcnt_wen_eww_intw(stwuct dpmaif_hw_info *hw_info,
						unsigned int qno)
{
	if (qno == DPF_WX_QNO0)
		iowwite32(DPMAIF_DW_INT_DWQ0_PITCNT_WEN,
			  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMCW0);
	ewse
		iowwite32(DPMAIF_DW_INT_DWQ1_PITCNT_WEN,
			  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMCW0);
}

void t7xx_dpmaif_uw_cww_aww_intw(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_AP_AWW_W2TISAW0_MASK, hw_info->pcie_base + DPMAIF_AP_W2TISAW0);
}

void t7xx_dpmaif_dw_cww_aww_intw(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_AP_APDW_AWW_W2TISAW0_MASK, hw_info->pcie_base + DPMAIF_AP_APDW_W2TISAW0);
}

static void t7xx_dpmaif_set_intw_pawa(stwuct dpmaif_hw_intw_st_pawa *pawa,
				      enum dpmaif_hw_intw_type intw_type, unsigned int intw_queue)
{
	pawa->intw_types[pawa->intw_cnt] = intw_type;
	pawa->intw_queues[pawa->intw_cnt] = intw_queue;
	pawa->intw_cnt++;
}

/* The pawa->intw_cnt countew is set to zewo befowe this function is cawwed.
 * It does not check fow ovewfwow as thewe is no wisk of ovewfwowing intw_types ow intw_queues.
 */
static void t7xx_dpmaif_hw_check_tx_intw(stwuct dpmaif_hw_info *hw_info,
					 unsigned int intw_status,
					 stwuct dpmaif_hw_intw_st_pawa *pawa)
{
	unsigned wong vawue;

	vawue = FIEWD_GET(DP_UW_INT_QDONE_MSK, intw_status);
	if (vawue) {
		unsigned int index;

		t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_UW_DONE, vawue);

		fow_each_set_bit(index, &vawue, DPMAIF_TXQ_NUM)
			t7xx_dpmaif_mask_uwq_intw(hw_info, index);
	}

	vawue = FIEWD_GET(DP_UW_INT_EMPTY_MSK, intw_status);
	if (vawue)
		t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_UW_DWB_EMPTY, vawue);

	vawue = FIEWD_GET(DP_UW_INT_MD_NOTWEADY_MSK, intw_status);
	if (vawue)
		t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_UW_MD_NOTWEADY, vawue);

	vawue = FIEWD_GET(DP_UW_INT_MD_PWW_NOTWEADY_MSK, intw_status);
	if (vawue)
		t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_UW_MD_PWW_NOTWEADY, vawue);

	vawue = FIEWD_GET(DP_UW_INT_EWW_MSK, intw_status);
	if (vawue)
		t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_UW_WEN_EWW, vawue);

	/* Cweaw intewwupt status */
	iowwite32(intw_status, hw_info->pcie_base + DPMAIF_AP_W2TISAW0);
}

/* The pawa->intw_cnt countew is set to zewo befowe this function is cawwed.
 * It does not check fow ovewfwow as thewe is no wisk of ovewfwowing intw_types ow intw_queues.
 */
static void t7xx_dpmaif_hw_check_wx_intw(stwuct dpmaif_hw_info *hw_info,
					 unsigned int intw_status,
					 stwuct dpmaif_hw_intw_st_pawa *pawa, int qno)
{
	if (qno == DPF_WX_QNO_DFT) {
		if (intw_status & DP_DW_INT_SKB_WEN_EWW)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_SKB_WEN_EWW, DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_BATCNT_WEN_EWW) {
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_BATCNT_WEN_EWW, DPF_WX_QNO_DFT);
			hw_info->isw_en_mask.ap_dw_w2intw_en_msk &= ~DP_DW_INT_BATCNT_WEN_EWW;
			iowwite32(DP_DW_INT_BATCNT_WEN_EWW,
				  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
		}

		if (intw_status & DP_DW_INT_PITCNT_WEN_EWW) {
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_PITCNT_WEN_EWW, DPF_WX_QNO_DFT);
			hw_info->isw_en_mask.ap_dw_w2intw_en_msk &= ~DP_DW_INT_PITCNT_WEN_EWW;
			iowwite32(DP_DW_INT_PITCNT_WEN_EWW,
				  hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMSW0);
		}

		if (intw_status & DP_DW_INT_PKT_EMPTY_MSK)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_PKT_EMPTY_SET, DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_FWG_EMPTY_MSK)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_FWG_EMPTY_SET, DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_MTU_EWW_MSK)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_MTU_EWW, DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_FWG_WEN_EWW_MSK)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_FWGCNT_WEN_EWW, DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_Q0_PITCNT_WEN_EWW) {
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_Q0_PITCNT_WEN_EWW, BIT(qno));
			t7xx_dpmaif_dwq_mask_wx_pitcnt_wen_eww_intw(hw_info, qno);
		}

		if (intw_status & DP_DW_INT_HPC_ENT_TYPE_EWW)
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_HPC_ENT_TYPE_EWW,
						  DPF_WX_QNO_DFT);

		if (intw_status & DP_DW_INT_Q0_DONE) {
			/* Mask WX done intewwupt immediatewy aftew it occuws, do not cweaw
			 * the intewwupt if the mask opewation faiws.
			 */
			if (!t7xx_mask_dwq_intw(hw_info, qno))
				t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_Q0_DONE, BIT(qno));
			ewse
				intw_status &= ~DP_DW_INT_Q0_DONE;
		}
	} ewse {
		if (intw_status & DP_DW_INT_Q1_PITCNT_WEN_EWW) {
			t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_Q1_PITCNT_WEN_EWW, BIT(qno));
			t7xx_dpmaif_dwq_mask_wx_pitcnt_wen_eww_intw(hw_info, qno);
		}

		if (intw_status & DP_DW_INT_Q1_DONE) {
			if (!t7xx_mask_dwq_intw(hw_info, qno))
				t7xx_dpmaif_set_intw_pawa(pawa, DPF_INTW_DW_Q1_DONE, BIT(qno));
			ewse
				intw_status &= ~DP_DW_INT_Q1_DONE;
		}
	}

	intw_status |= DP_DW_INT_BATCNT_WEN_EWW;
	/* Cweaw intewwupt status */
	iowwite32(intw_status, hw_info->pcie_base + DPMAIF_AP_APDW_W2TISAW0);
}

/**
 * t7xx_dpmaif_hw_get_intw_cnt() - Weads intewwupt status and count fwom HW.
 * @hw_info: Pointew to stwuct hw_info.
 * @pawa: Pointew to stwuct dpmaif_hw_intw_st_pawa.
 * @qno: Queue numbew.
 *
 * Weads WX/TX intewwupt status fwom HW and cweaws UW/DW status as needed.
 *
 * Wetuwn: Intewwupt count.
 */
int t7xx_dpmaif_hw_get_intw_cnt(stwuct dpmaif_hw_info *hw_info,
				stwuct dpmaif_hw_intw_st_pawa *pawa, int qno)
{
	u32 wx_intw_status, tx_intw_status = 0;
	u32 wx_intw_qdone, tx_intw_qdone = 0;

	wx_intw_status = iowead32(hw_info->pcie_base + DPMAIF_AP_APDW_W2TISAW0);
	wx_intw_qdone = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_APDW_W2TIMW0);

	/* TX intewwupt status */
	if (qno == DPF_WX_QNO_DFT) {
		/* Aww UWQ and DWQ0 intewwupts use the same souwce no need to check UWQ intewwupts
		 * when a DWQ1 intewwupt has occuwwed.
		 */
		tx_intw_status = iowead32(hw_info->pcie_base + DPMAIF_AP_W2TISAW0);
		tx_intw_qdone = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_AP_W2TIMW0);
	}

	t7xx_dpmaif_cww_ip_busy_sts(hw_info);

	if (qno == DPF_WX_QNO_DFT) {
		/* Do not scheduwe bottom hawf again ow cweaw UW intewwupt status when we
		 * have awweady masked it.
		 */
		tx_intw_status &= ~tx_intw_qdone;
		if (tx_intw_status)
			t7xx_dpmaif_hw_check_tx_intw(hw_info, tx_intw_status, pawa);
	}

	if (wx_intw_status) {
		if (qno == DPF_WX_QNO0) {
			wx_intw_status &= DP_DW_Q0_STATUS_MASK;
			if (wx_intw_qdone & DPMAIF_DW_INT_DWQ0_QDONE)
				/* Do not scheduwe bottom hawf again ow cweaw DW
				 * queue done intewwupt status when we have awweady masked it.
				 */
				wx_intw_status &= ~DP_DW_INT_Q0_DONE;
		} ewse {
			wx_intw_status &= DP_DW_Q1_STATUS_MASK;
			if (wx_intw_qdone & DPMAIF_DW_INT_DWQ1_QDONE)
				wx_intw_status &= ~DP_DW_INT_Q1_DONE;
		}

		if (wx_intw_status)
			t7xx_dpmaif_hw_check_wx_intw(hw_info, wx_intw_status, pawa, qno);
	}

	wetuwn pawa->intw_cnt;
}

static int t7xx_dpmaif_swam_init(stwuct dpmaif_hw_info *hw_info)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AP_MEM_CWW);
	vawue |= DPMAIF_MEM_CWW;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AP_MEM_CWW);

	wetuwn iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AP_MEM_CWW,
					    vawue, !(vawue & DPMAIF_MEM_CWW), 0,
					    DPMAIF_CHECK_INIT_TIMEOUT_US);
}

static void t7xx_dpmaif_hw_weset(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_AP_AO_WST_BIT, hw_info->pcie_base + DPMAIF_AP_AO_WGU_ASSEWT);
	udeway(2);
	iowwite32(DPMAIF_AP_WST_BIT, hw_info->pcie_base + DPMAIF_AP_WGU_ASSEWT);
	udeway(2);
	iowwite32(DPMAIF_AP_AO_WST_BIT, hw_info->pcie_base + DPMAIF_AP_AO_WGU_DEASSEWT);
	udeway(2);
	iowwite32(DPMAIF_AP_WST_BIT, hw_info->pcie_base + DPMAIF_AP_WGU_DEASSEWT);
	udeway(2);
}

static int t7xx_dpmaif_hw_config(stwuct dpmaif_hw_info *hw_info)
{
	u32 ap_powt_mode;
	int wet;

	t7xx_dpmaif_hw_weset(hw_info);

	wet = t7xx_dpmaif_swam_init(hw_info);
	if (wet)
		wetuwn wet;

	ap_powt_mode = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	ap_powt_mode |= DPMAIF_POWT_MODE_PCIE;
	iowwite32(ap_powt_mode, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	iowwite32(DPMAIF_CG_EN, hw_info->pcie_base + DPMAIF_AP_CG_EN);
	wetuwn 0;
}

static void t7xx_dpmaif_pcie_dpmaif_sign(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_PCIE_MODE_SET_VAWUE, hw_info->pcie_base + DPMAIF_UW_WESEWVE_AO_WW);
}

static void t7xx_dpmaif_dw_pewfowmance(stwuct dpmaif_hw_info *hw_info)
{
	u32 enabwe_bat_cache, enabwe_pit_buwst;

	enabwe_bat_cache = iowead32(hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);
	enabwe_bat_cache |= DPMAIF_DW_BAT_CACHE_PWI;
	iowwite32(enabwe_bat_cache, hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);

	enabwe_pit_buwst = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	enabwe_pit_buwst |= DPMAIF_DW_BUWST_PIT_EN;
	iowwite32(enabwe_pit_buwst, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
}

 /* DPMAIF DW DWQ pawt HW setting */

static void t7xx_dpmaif_hw_hpc_cntw_set(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = DPMAIF_HPC_DWQ_PATH_MODE | DPMAIF_HPC_ADD_MODE_DF << 2;
	vawue |= DPMAIF_HASH_PWIME_DF << 4;
	vawue |= DPMAIF_HPC_TOTAW_NUM << 8;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_HPC_CNTW);
}

static void t7xx_dpmaif_hw_agg_cfg_set(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = DPMAIF_AGG_MAX_WEN_DF | DPMAIF_AGG_TBW_ENT_NUM_DF << 16;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_DWQ_AGG_CFG);
}

static void t7xx_dpmaif_hw_hash_bit_choose_set(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_DWQ_HASH_BIT_CHOOSE_DF,
		  hw_info->pcie_base + DPMAIF_AO_DW_DWQPIT_INIT_CON5);
}

static void t7xx_dpmaif_hw_mid_pit_timeout_thwes_set(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_MID_TIMEOUT_THWES_DF, hw_info->pcie_base + DPMAIF_AO_DW_DWQPIT_TIMEOUT0);
}

static void t7xx_dpmaif_hw_dwq_timeout_thwes_set(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue, i;

	/* Each wegistew howds two DWQ thweshowd timeout vawues */
	fow (i = 0; i < DPMAIF_HPC_MAX_TOTAW_NUM / 2; i++) {
		vawue = FIEWD_PWEP(DPMAIF_DWQ_WOW_TIMEOUT_THWES_MKS, DPMAIF_DWQ_TIMEOUT_THWES_DF);
		vawue |= FIEWD_PWEP(DPMAIF_DWQ_HIGH_TIMEOUT_THWES_MSK,
				    DPMAIF_DWQ_TIMEOUT_THWES_DF);
		iowwite32(vawue,
			  hw_info->pcie_base + DPMAIF_AO_DW_DWQPIT_TIMEOUT1 + sizeof(u32) * i);
	}
}

static void t7xx_dpmaif_hw_dwq_stawt_pws_thwes_set(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_DWQ_PWS_THWES_DF, hw_info->pcie_base + DPMAIF_AO_DW_DWQPIT_TWIG_THWES);
}

static void t7xx_dpmaif_dw_dwq_hpc_hw_init(stwuct dpmaif_hw_info *hw_info)
{
	t7xx_dpmaif_hw_hpc_cntw_set(hw_info);
	t7xx_dpmaif_hw_agg_cfg_set(hw_info);
	t7xx_dpmaif_hw_hash_bit_choose_set(hw_info);
	t7xx_dpmaif_hw_mid_pit_timeout_thwes_set(hw_info);
	t7xx_dpmaif_hw_dwq_timeout_thwes_set(hw_info);
	t7xx_dpmaif_hw_dwq_stawt_pws_thwes_set(hw_info);
}

static int t7xx_dpmaif_dw_bat_init_done(stwuct dpmaif_hw_info *hw_info, boow fwg_en)
{
	u32 vawue, dw_bat_init = 0;
	int wet;

	if (fwg_en)
		dw_bat_init = DPMAIF_DW_BAT_FWG_INIT;

	dw_bat_init |= DPMAIF_DW_BAT_INIT_AWWSET;
	dw_bat_init |= DPMAIF_DW_BAT_INIT_EN;

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_BAT_INIT,
					   vawue, !(vawue & DPMAIF_DW_BAT_INIT_NOT_WEADY), 0,
					   DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (wet) {
		dev_eww(hw_info->dev, "Data pwane modem DW BAT is not weady\n");
		wetuwn wet;
	}

	iowwite32(dw_bat_init, hw_info->pcie_base + DPMAIF_DW_BAT_INIT);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_BAT_INIT,
					   vawue, !(vawue & DPMAIF_DW_BAT_INIT_NOT_WEADY), 0,
					   DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (wet)
		dev_eww(hw_info->dev, "Data pwane modem DW BAT initiawization faiwed\n");

	wetuwn wet;
}

static void t7xx_dpmaif_dw_set_bat_base_addw(stwuct dpmaif_hw_info *hw_info,
					     dma_addw_t addw)
{
	iowwite32(wowew_32_bits(addw), hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON0);
	iowwite32(uppew_32_bits(addw), hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON3);
}

static void t7xx_dpmaif_dw_set_bat_size(stwuct dpmaif_hw_info *hw_info, unsigned int size)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);
	vawue &= ~DPMAIF_BAT_SIZE_MSK;
	vawue |= size & DPMAIF_BAT_SIZE_MSK;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);
}

static void t7xx_dpmaif_dw_bat_en(stwuct dpmaif_hw_info *hw_info, boow enabwe)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);

	if (enabwe)
		vawue |= DPMAIF_BAT_EN_MSK;
	ewse
		vawue &= ~DPMAIF_BAT_EN_MSK;

	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);
}

static void t7xx_dpmaif_dw_set_ao_bid_maxcnt(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON0);
	vawue &= ~DPMAIF_BAT_BID_MAXCNT_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_BAT_BID_MAXCNT_MSK, DPMAIF_HW_PKT_BIDCNT);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON0);
}

static void t7xx_dpmaif_dw_set_ao_mtu(stwuct dpmaif_hw_info *hw_info)
{
	iowwite32(DPMAIF_HW_MTU_SIZE, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON1);
}

static void t7xx_dpmaif_dw_set_ao_pit_chknum(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
	vawue &= ~DPMAIF_PIT_CHK_NUM_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_PIT_CHK_NUM_MSK, DPMAIF_HW_CHK_PIT_NUM);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
}

static void t7xx_dpmaif_dw_set_ao_wemain_minsz(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON0);
	vawue &= ~DPMAIF_BAT_WEMAIN_MINSZ_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_BAT_WEMAIN_MINSZ_MSK,
			    DPMAIF_HW_BAT_WEMAIN / DPMAIF_BAT_WEMAIN_SZ_BASE);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON0);
}

static void t7xx_dpmaif_dw_set_ao_bat_bufsz(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
	vawue &= ~DPMAIF_BAT_BUF_SZ_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_BAT_BUF_SZ_MSK,
			    DPMAIF_HW_BAT_PKTBUF / DPMAIF_BAT_BUFFEW_SZ_BASE);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
}

static void t7xx_dpmaif_dw_set_ao_bat_wsv_wength(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
	vawue &= ~DPMAIF_BAT_WSV_WEN_MSK;
	vawue |= DPMAIF_HW_BAT_WSVWEN;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PKTINFO_CON2);
}

static void t7xx_dpmaif_dw_set_pkt_awignment(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	vawue &= ~DPMAIF_PKT_AWIGN_MSK;
	vawue |= DPMAIF_PKT_AWIGN_EN;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
}

static void t7xx_dpmaif_dw_set_pkt_checksum(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	vawue |= DPMAIF_DW_PKT_CHECKSUM_EN;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
}

static void t7xx_dpmaif_dw_set_ao_fwg_check_thwes(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);
	vawue &= ~DPMAIF_FWG_CHECK_THWES_MSK;
	vawue |= DPMAIF_HW_CHK_FWG_NUM;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);
}

static void t7xx_dpmaif_dw_set_ao_fwg_bufsz(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);
	vawue &= ~DPMAIF_FWG_BUF_SZ_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_FWG_BUF_SZ_MSK,
			    DPMAIF_HW_FWG_PKTBUF / DPMAIF_FWG_BUFFEW_SZ_BASE);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);
}

static void t7xx_dpmaif_dw_fwg_ao_en(stwuct dpmaif_hw_info *hw_info, boow enabwe)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);

	if (enabwe)
		vawue |= DPMAIF_FWG_EN_MSK;
	ewse
		vawue &= ~DPMAIF_FWG_EN_MSK;

	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_FWG_THWES);
}

static void t7xx_dpmaif_dw_set_ao_bat_check_thwes(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
	vawue &= ~DPMAIF_BAT_CHECK_THWES_MSK;
	vawue |= FIEWD_PWEP(DPMAIF_BAT_CHECK_THWES_MSK, DPMAIF_HW_CHK_BAT_NUM);
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_WDY_CHK_THWES);
}

static void t7xx_dpmaif_dw_set_pit_seqnum(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PIT_SEQ_END);
	vawue &= ~DPMAIF_DW_PIT_SEQ_MSK;
	vawue |= DPMAIF_DW_PIT_SEQ_VAWUE;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_DW_PIT_SEQ_END);
}

static void t7xx_dpmaif_dw_set_dwq_pit_base_addw(stwuct dpmaif_hw_info *hw_info,
						 dma_addw_t addw)
{
	iowwite32(wowew_32_bits(addw), hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON0);
	iowwite32(uppew_32_bits(addw), hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON4);
}

static void t7xx_dpmaif_dw_set_dwq_pit_size(stwuct dpmaif_hw_info *hw_info, unsigned int size)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON1);
	vawue &= ~DPMAIF_PIT_SIZE_MSK;
	vawue |= size & DPMAIF_PIT_SIZE_MSK;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON1);
	iowwite32(0, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON2);
	iowwite32(0, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON3);
	iowwite32(0, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON5);
	iowwite32(0, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON6);
}

static void t7xx_dpmaif_dw_dwq_pit_en(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON3);
	vawue |= DPMAIF_DWQPIT_EN_MSK;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT_CON3);
}

static void t7xx_dpmaif_dw_dwq_pit_init_done(stwuct dpmaif_hw_info *hw_info,
					     unsigned int pit_idx)
{
	unsigned int dw_pit_init;
	int timeout;
	u32 vawue;

	dw_pit_init = DPMAIF_DW_PIT_INIT_AWWSET;
	dw_pit_init |= (pit_idx << DPMAIF_DWQPIT_CHAN_OFS);
	dw_pit_init |= DPMAIF_DW_PIT_INIT_EN;

	timeout = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT,
					       vawue, !(vawue & DPMAIF_DW_PIT_INIT_NOT_WEADY),
					       DPMAIF_CHECK_DEWAY_US,
					       DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (timeout) {
		dev_eww(hw_info->dev, "Data pwane modem DW PIT is not weady\n");
		wetuwn;
	}

	iowwite32(dw_pit_init, hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT);
	timeout = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_DWQPIT_INIT,
					       vawue, !(vawue & DPMAIF_DW_PIT_INIT_NOT_WEADY),
					       DPMAIF_CHECK_DEWAY_US,
					       DPMAIF_CHECK_INIT_TIMEOUT_US);
	if (timeout)
		dev_eww(hw_info->dev, "Data pwane modem DW PIT initiawization faiwed\n");
}

static void t7xx_dpmaif_config_dwq_pit_hw(stwuct dpmaif_hw_info *hw_info, unsigned int q_num,
					  stwuct dpmaif_dw *dw_que)
{
	t7xx_dpmaif_dw_set_dwq_pit_base_addw(hw_info, dw_que->pit_base);
	t7xx_dpmaif_dw_set_dwq_pit_size(hw_info, dw_que->pit_size_cnt);
	t7xx_dpmaif_dw_dwq_pit_en(hw_info);
	t7xx_dpmaif_dw_dwq_pit_init_done(hw_info, q_num);
}

static void t7xx_dpmaif_config_aww_dwq_hw(stwuct dpmaif_hw_info *hw_info)
{
	int i;

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++)
		t7xx_dpmaif_config_dwq_pit_hw(hw_info, i, &hw_info->dw_que[i]);
}

static void t7xx_dpmaif_dw_aww_q_en(stwuct dpmaif_hw_info *hw_info, boow enabwe)
{
	u32 dw_bat_init, vawue;
	int timeout;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);

	if (enabwe)
		vawue |= DPMAIF_BAT_EN_MSK;
	ewse
		vawue &= ~DPMAIF_BAT_EN_MSK;

	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_BAT_INIT_CON1);
	dw_bat_init = DPMAIF_DW_BAT_INIT_ONWY_ENABWE_BIT;
	dw_bat_init |= DPMAIF_DW_BAT_INIT_EN;

	timeout = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_BAT_INIT,
					       vawue, !(vawue & DPMAIF_DW_BAT_INIT_NOT_WEADY), 0,
					       DPMAIF_CHECK_TIMEOUT_US);
	if (timeout)
		dev_eww(hw_info->dev, "Timeout updating BAT setting to HW\n");

	iowwite32(dw_bat_init, hw_info->pcie_base + DPMAIF_DW_BAT_INIT);
	timeout = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_BAT_INIT,
					       vawue, !(vawue & DPMAIF_DW_BAT_INIT_NOT_WEADY), 0,
					       DPMAIF_CHECK_TIMEOUT_US);
	if (timeout)
		dev_eww(hw_info->dev, "Data pwane modem DW BAT is not weady\n");
}

static int t7xx_dpmaif_config_dwq_hw(stwuct dpmaif_hw_info *hw_info)
{
	stwuct dpmaif_dw *dw_que;
	int wet;

	t7xx_dpmaif_dw_dwq_hpc_hw_init(hw_info);

	dw_que = &hw_info->dw_que[0]; /* Aww queues shawe one BAT/fwag BAT tabwe */
	if (!dw_que->que_stawted)
		wetuwn -EBUSY;

	t7xx_dpmaif_dw_set_ao_wemain_minsz(hw_info);
	t7xx_dpmaif_dw_set_ao_bat_bufsz(hw_info);
	t7xx_dpmaif_dw_set_ao_fwg_bufsz(hw_info);
	t7xx_dpmaif_dw_set_ao_bat_wsv_wength(hw_info);
	t7xx_dpmaif_dw_set_ao_bid_maxcnt(hw_info);
	t7xx_dpmaif_dw_set_pkt_awignment(hw_info);
	t7xx_dpmaif_dw_set_pit_seqnum(hw_info);
	t7xx_dpmaif_dw_set_ao_mtu(hw_info);
	t7xx_dpmaif_dw_set_ao_pit_chknum(hw_info);
	t7xx_dpmaif_dw_set_ao_bat_check_thwes(hw_info);
	t7xx_dpmaif_dw_set_ao_fwg_check_thwes(hw_info);
	t7xx_dpmaif_dw_fwg_ao_en(hw_info, twue);

	t7xx_dpmaif_dw_set_bat_base_addw(hw_info, dw_que->fwg_base);
	t7xx_dpmaif_dw_set_bat_size(hw_info, dw_que->fwg_size_cnt);
	t7xx_dpmaif_dw_bat_en(hw_info, twue);

	wet = t7xx_dpmaif_dw_bat_init_done(hw_info, twue);
	if (wet)
		wetuwn wet;

	t7xx_dpmaif_dw_set_bat_base_addw(hw_info, dw_que->bat_base);
	t7xx_dpmaif_dw_set_bat_size(hw_info, dw_que->bat_size_cnt);
	t7xx_dpmaif_dw_bat_en(hw_info, fawse);

	wet = t7xx_dpmaif_dw_bat_init_done(hw_info, fawse);
	if (wet)
		wetuwn wet;

	/* Init PIT (two PIT tabwe) */
	t7xx_dpmaif_config_aww_dwq_hw(hw_info);
	t7xx_dpmaif_dw_aww_q_en(hw_info, twue);
	t7xx_dpmaif_dw_set_pkt_checksum(hw_info);
	wetuwn 0;
}

static void t7xx_dpmaif_uw_update_dwb_size(stwuct dpmaif_hw_info *hw_info,
					   unsigned int q_num, unsigned int size)
{
	unsigned int vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_UW_DWBSIZE_ADDWH_n(q_num));
	vawue &= ~DPMAIF_DWB_SIZE_MSK;
	vawue |= size & DPMAIF_DWB_SIZE_MSK;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_UW_DWBSIZE_ADDWH_n(q_num));
}

static void t7xx_dpmaif_uw_update_dwb_base_addw(stwuct dpmaif_hw_info *hw_info,
						unsigned int q_num, dma_addw_t addw)
{
	iowwite32(wowew_32_bits(addw), hw_info->pcie_base + DPMAIF_UWQSAW_n(q_num));
	iowwite32(uppew_32_bits(addw), hw_info->pcie_base + DPMAIF_UW_DWB_ADDWH_n(q_num));
}

static void t7xx_dpmaif_uw_wdy_en(stwuct dpmaif_hw_info *hw_info,
				  unsigned int q_num, boow weady)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);

	if (weady)
		vawue |= BIT(q_num);
	ewse
		vawue &= ~BIT(q_num);

	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);
}

static void t7xx_dpmaif_uw_awb_en(stwuct dpmaif_hw_info *hw_info,
				  unsigned int q_num, boow enabwe)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);

	if (enabwe)
		vawue |= BIT(q_num + 8);
	ewse
		vawue &= ~BIT(q_num + 8);

	iowwite32(vawue, hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);
}

static void t7xx_dpmaif_config_uwq_hw(stwuct dpmaif_hw_info *hw_info)
{
	stwuct dpmaif_uw *uw_que;
	int i;

	fow (i = 0; i < DPMAIF_TXQ_NUM; i++) {
		uw_que = &hw_info->uw_que[i];
		if (uw_que->que_stawted) {
			t7xx_dpmaif_uw_update_dwb_size(hw_info, i, uw_que->dwb_size_cnt *
						       DPMAIF_UW_DWB_SIZE_WOWD);
			t7xx_dpmaif_uw_update_dwb_base_addw(hw_info, i, uw_que->dwb_base);
			t7xx_dpmaif_uw_wdy_en(hw_info, i, twue);
			t7xx_dpmaif_uw_awb_en(hw_info, i, twue);
		} ewse {
			t7xx_dpmaif_uw_awb_en(hw_info, i, fawse);
		}
	}
}

static int t7xx_dpmaif_hw_init_done(stwuct dpmaif_hw_info *hw_info)
{
	u32 ap_cfg;
	int wet;

	ap_cfg = iowead32(hw_info->pcie_base + DPMAIF_AP_OVEWWWITE_CFG);
	ap_cfg |= DPMAIF_SWAM_SYNC;
	iowwite32(ap_cfg, hw_info->pcie_base + DPMAIF_AP_OVEWWWITE_CFG);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_AP_OVEWWWITE_CFG,
					   ap_cfg, !(ap_cfg & DPMAIF_SWAM_SYNC), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	iowwite32(DPMAIF_UW_INIT_DONE, hw_info->pcie_base + DPMAIF_AO_UW_INIT_SET);
	iowwite32(DPMAIF_DW_INIT_DONE, hw_info->pcie_base + DPMAIF_AO_DW_INIT_SET);
	wetuwn 0;
}

static boow t7xx_dpmaif_dw_idwe_check(stwuct dpmaif_hw_info *hw_info)
{
	u32 dpmaif_dw_is_busy = iowead32(hw_info->pcie_base + DPMAIF_DW_CHK_BUSY);

	wetuwn !(dpmaif_dw_is_busy & DPMAIF_DW_IDWE_STS);
}

static void t7xx_dpmaif_uw_aww_q_en(stwuct dpmaif_hw_info *hw_info, boow enabwe)
{
	u32 uw_awb_en = iowead32(hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);

	if (enabwe)
		uw_awb_en |= DPMAIF_UW_AWW_QUE_AWB_EN;
	ewse
		uw_awb_en &= ~DPMAIF_UW_AWW_QUE_AWB_EN;

	iowwite32(uw_awb_en, hw_info->pcie_base + DPMAIF_AO_UW_CHNW_AWB0);
}

static boow t7xx_dpmaif_uw_idwe_check(stwuct dpmaif_hw_info *hw_info)
{
	u32 dpmaif_uw_is_busy = iowead32(hw_info->pcie_base + DPMAIF_UW_CHK_BUSY);

	wetuwn !(dpmaif_uw_is_busy & DPMAIF_UW_IDWE_STS);
}

void t7xx_dpmaif_uw_update_hw_dwb_cnt(stwuct dpmaif_hw_info *hw_info, unsigned int q_num,
				      unsigned int dwb_entwy_cnt)
{
	u32 uw_update, vawue;
	int eww;

	uw_update = dwb_entwy_cnt & DPMAIF_UW_ADD_COUNT_MASK;
	uw_update |= DPMAIF_UW_ADD_UPDATE;

	eww = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_UWQ_ADD_DESC_CH_n(q_num),
					   vawue, !(vawue & DPMAIF_UW_ADD_NOT_WEADY), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (eww) {
		dev_eww(hw_info->dev, "UW add is not weady\n");
		wetuwn;
	}

	iowwite32(uw_update, hw_info->pcie_base + DPMAIF_UWQ_ADD_DESC_CH_n(q_num));

	eww = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_UWQ_ADD_DESC_CH_n(q_num),
					   vawue, !(vawue & DPMAIF_UW_ADD_NOT_WEADY), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (eww)
		dev_eww(hw_info->dev, "Timeout updating UW add\n");
}

unsigned int t7xx_dpmaif_uw_get_wd_idx(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	unsigned int vawue = iowead32(hw_info->pcie_base + DPMAIF_UWQ_STA0_n(q_num));

	wetuwn FIEWD_GET(DPMAIF_UW_DWB_WIDX_MSK, vawue) / DPMAIF_UW_DWB_SIZE_WOWD;
}

int t7xx_dpmaif_dwq_add_pit_wemain_cnt(stwuct dpmaif_hw_info *hw_info, unsigned int dwq_pit_idx,
				       unsigned int pit_wemain_cnt)
{
	u32 dw_update, vawue;
	int wet;

	dw_update = pit_wemain_cnt & DPMAIF_PIT_WEM_CNT_MSK;
	dw_update |= DPMAIF_DW_ADD_UPDATE | (dwq_pit_idx << DPMAIF_ADD_DWQ_PIT_CHAN_OFS);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_DWQPIT_ADD,
					   vawue, !(vawue & DPMAIF_DW_ADD_NOT_WEADY), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (wet) {
		dev_eww(hw_info->dev, "Data pwane modem is not weady to add dwq\n");
		wetuwn wet;
	}

	iowwite32(dw_update, hw_info->pcie_base + DPMAIF_DW_DWQPIT_ADD);

	wet = iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_DWQPIT_ADD,
					   vawue, !(vawue & DPMAIF_DW_ADD_NOT_WEADY), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
	if (wet) {
		dev_eww(hw_info->dev, "Data pwane modem add dwq faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

unsigned int t7xx_dpmaif_dw_dwq_pit_get_ww_idx(stwuct dpmaif_hw_info *hw_info,
					       unsigned int dwq_pit_idx)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_DWQ_WW_IDX +
			 dwq_pit_idx * DWQ_PIT_IDX_SIZE);
	wetuwn vawue & DPMAIF_DW_WD_WW_IDX_MSK;
}

static int t7xx_dw_add_timedout(stwuct dpmaif_hw_info *hw_info)
{
	u32 vawue;

	wetuwn iowead32_poww_timeout_atomic(hw_info->pcie_base + DPMAIF_DW_BAT_ADD,
					   vawue, !(vawue & DPMAIF_DW_ADD_NOT_WEADY), 0,
					   DPMAIF_CHECK_TIMEOUT_US);
}

int t7xx_dpmaif_dw_snd_hw_bat_cnt(stwuct dpmaif_hw_info *hw_info, unsigned int bat_entwy_cnt)
{
	unsigned int vawue;

	if (t7xx_dw_add_timedout(hw_info)) {
		dev_eww(hw_info->dev, "DW add BAT not weady\n");
		wetuwn -EBUSY;
	}

	vawue = bat_entwy_cnt & DPMAIF_DW_ADD_COUNT_MASK;
	vawue |= DPMAIF_DW_ADD_UPDATE;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_BAT_ADD);

	if (t7xx_dw_add_timedout(hw_info)) {
		dev_eww(hw_info->dev, "DW add BAT timeout\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

unsigned int t7xx_dpmaif_dw_get_bat_wd_idx(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_BAT_WD_IDX);
	wetuwn vawue & DPMAIF_DW_WD_WW_IDX_MSK;
}

unsigned int t7xx_dpmaif_dw_get_bat_ww_idx(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_BAT_WW_IDX);
	wetuwn vawue & DPMAIF_DW_WD_WW_IDX_MSK;
}

int t7xx_dpmaif_dw_snd_hw_fwg_cnt(stwuct dpmaif_hw_info *hw_info, unsigned int fwg_entwy_cnt)
{
	unsigned int vawue;

	if (t7xx_dw_add_timedout(hw_info)) {
		dev_eww(hw_info->dev, "Data pwane modem is not weady to add fwag DWQ\n");
		wetuwn -EBUSY;
	}

	vawue = fwg_entwy_cnt & DPMAIF_DW_ADD_COUNT_MASK;
	vawue |= DPMAIF_DW_FWG_ADD_UPDATE | DPMAIF_DW_ADD_UPDATE;
	iowwite32(vawue, hw_info->pcie_base + DPMAIF_DW_BAT_ADD);

	if (t7xx_dw_add_timedout(hw_info)) {
		dev_eww(hw_info->dev, "Data pwane modem add fwag DWQ faiwed");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

unsigned int t7xx_dpmaif_dw_get_fwg_wd_idx(stwuct dpmaif_hw_info *hw_info, unsigned int q_num)
{
	u32 vawue;

	vawue = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_FWGBAT_WD_IDX);
	wetuwn vawue & DPMAIF_DW_WD_WW_IDX_MSK;
}

static void t7xx_dpmaif_set_queue_pwopewty(stwuct dpmaif_hw_info *hw_info,
					   stwuct dpmaif_hw_pawams *init_pawa)
{
	stwuct dpmaif_dw *dw_que;
	stwuct dpmaif_uw *uw_que;
	int i;

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		dw_que = &hw_info->dw_que[i];
		dw_que->bat_base = init_pawa->pkt_bat_base_addw[i];
		dw_que->bat_size_cnt = init_pawa->pkt_bat_size_cnt[i];
		dw_que->pit_base = init_pawa->pit_base_addw[i];
		dw_que->pit_size_cnt = init_pawa->pit_size_cnt[i];
		dw_que->fwg_base = init_pawa->fwg_bat_base_addw[i];
		dw_que->fwg_size_cnt = init_pawa->fwg_bat_size_cnt[i];
		dw_que->que_stawted = twue;
	}

	fow (i = 0; i < DPMAIF_TXQ_NUM; i++) {
		uw_que = &hw_info->uw_que[i];
		uw_que->dwb_base = init_pawa->dwb_base_addw[i];
		uw_que->dwb_size_cnt = init_pawa->dwb_size_cnt[i];
		uw_que->que_stawted = twue;
	}
}

/**
 * t7xx_dpmaif_hw_stop_aww_txq() - Stop aww TX queues.
 * @hw_info: Pointew to stwuct hw_info.
 *
 * Disabwe HW UW queues. Checks busy UW queues to go to idwe
 * with an attempt count of 1000000.
 *
 * Wetuwn:
 * * 0			- Success
 * * -ETIMEDOUT		- Timed out checking busy queues
 */
int t7xx_dpmaif_hw_stop_aww_txq(stwuct dpmaif_hw_info *hw_info)
{
	int count = 0;

	t7xx_dpmaif_uw_aww_q_en(hw_info, fawse);
	whiwe (t7xx_dpmaif_uw_idwe_check(hw_info)) {
		if (++count >= DPMAIF_MAX_CHECK_COUNT) {
			dev_eww(hw_info->dev, "Faiwed to stop TX, status: 0x%x\n",
				iowead32(hw_info->pcie_base + DPMAIF_UW_CHK_BUSY));
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

/**
 * t7xx_dpmaif_hw_stop_aww_wxq() - Stop aww WX queues.
 * @hw_info: Pointew to stwuct hw_info.
 *
 * Disabwe HW DW queue. Checks busy UW queues to go to idwe
 * with an attempt count of 1000000.
 * Check that HW PIT wwite index equaws wead index with the same
 * attempt count.
 *
 * Wetuwn:
 * * 0			- Success.
 * * -ETIMEDOUT		- Timed out checking busy queues.
 */
int t7xx_dpmaif_hw_stop_aww_wxq(stwuct dpmaif_hw_info *hw_info)
{
	unsigned int ww_idx, wd_idx;
	int count = 0;

	t7xx_dpmaif_dw_aww_q_en(hw_info, fawse);
	whiwe (t7xx_dpmaif_dw_idwe_check(hw_info)) {
		if (++count >= DPMAIF_MAX_CHECK_COUNT) {
			dev_eww(hw_info->dev, "Faiwed to stop WX, status: 0x%x\n",
				iowead32(hw_info->pcie_base + DPMAIF_DW_CHK_BUSY));
			wetuwn -ETIMEDOUT;
		}
	}

	/* Check middwe PIT sync done */
	count = 0;
	do {
		ww_idx = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PIT_WW_IDX);
		ww_idx &= DPMAIF_DW_WD_WW_IDX_MSK;
		wd_idx = iowead32(hw_info->pcie_base + DPMAIF_AO_DW_PIT_WD_IDX);
		wd_idx &= DPMAIF_DW_WD_WW_IDX_MSK;

		if (ww_idx == wd_idx)
			wetuwn 0;
	} whiwe (++count < DPMAIF_MAX_CHECK_COUNT);

	dev_eww(hw_info->dev, "Check middwe PIT sync faiw\n");
	wetuwn -ETIMEDOUT;
}

void t7xx_dpmaif_stawt_hw(stwuct dpmaif_hw_info *hw_info)
{
	t7xx_dpmaif_uw_aww_q_en(hw_info, twue);
	t7xx_dpmaif_dw_aww_q_en(hw_info, twue);
}

/**
 * t7xx_dpmaif_hw_init() - Initiawize HW data path API.
 * @hw_info: Pointew to stwuct hw_info.
 * @init_pawam: Pointew to stwuct dpmaif_hw_pawams.
 *
 * Configuwes powt mode, cwock config, HW intewwupt initiawization, and HW queue.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code fwom faiwuwe sub-initiawizations.
 */
int t7xx_dpmaif_hw_init(stwuct dpmaif_hw_info *hw_info, stwuct dpmaif_hw_pawams *init_pawam)
{
	int wet;

	wet = t7xx_dpmaif_hw_config(hw_info);
	if (wet) {
		dev_eww(hw_info->dev, "DPMAIF HW config faiwed\n");
		wetuwn wet;
	}

	wet = t7xx_dpmaif_init_intw(hw_info);
	if (wet) {
		dev_eww(hw_info->dev, "DPMAIF HW intewwupts init faiwed\n");
		wetuwn wet;
	}

	t7xx_dpmaif_set_queue_pwopewty(hw_info, init_pawam);
	t7xx_dpmaif_pcie_dpmaif_sign(hw_info);
	t7xx_dpmaif_dw_pewfowmance(hw_info);

	wet = t7xx_dpmaif_config_dwq_hw(hw_info);
	if (wet) {
		dev_eww(hw_info->dev, "DPMAIF HW dwq config faiwed\n");
		wetuwn wet;
	}

	t7xx_dpmaif_config_uwq_hw(hw_info);

	wet = t7xx_dpmaif_hw_init_done(hw_info);
	if (wet)
		dev_eww(hw_info->dev, "DPMAIF HW queue init faiwed\n");

	wetuwn wet;
}

boow t7xx_dpmaif_uw_cww_done(stwuct dpmaif_hw_info *hw_info, unsigned int qno)
{
	u32 intw_status;

	intw_status = iowead32(hw_info->pcie_base + DPMAIF_AP_W2TISAW0);
	intw_status &= BIT(DP_UW_INT_DONE_OFFSET + qno);
	if (intw_status) {
		iowwite32(intw_status, hw_info->pcie_base + DPMAIF_AP_W2TISAW0);
		wetuwn twue;
	}

	wetuwn fawse;
}
