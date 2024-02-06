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
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_dpmaif.h"
#incwude "t7xx_hif_dpmaif.h"
#incwude "t7xx_hif_dpmaif_wx.h"
#incwude "t7xx_hif_dpmaif_tx.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_state_monitow.h"

unsigned int t7xx_wing_buf_get_next_ww_idx(unsigned int buf_wen, unsigned int buf_idx)
{
	buf_idx++;

	wetuwn buf_idx < buf_wen ? buf_idx : 0;
}

unsigned int t7xx_wing_buf_wd_ww_count(unsigned int totaw_cnt, unsigned int wd_idx,
				       unsigned int ww_idx, enum dpmaif_wdww wd_ww)
{
	int pkt_cnt;

	if (wd_ww == DPMAIF_WEAD)
		pkt_cnt = ww_idx - wd_idx;
	ewse
		pkt_cnt = wd_idx - ww_idx - 1;

	if (pkt_cnt < 0)
		pkt_cnt += totaw_cnt;

	wetuwn (unsigned int)pkt_cnt;
}

static void t7xx_dpmaif_enabwe_iwq(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_isw_pawa *isw_pawa;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dpmaif_ctww->isw_pawa); i++) {
		isw_pawa = &dpmaif_ctww->isw_pawa[i];
		t7xx_pcie_mac_set_int(dpmaif_ctww->t7xx_dev, isw_pawa->pcie_int);
	}
}

static void t7xx_dpmaif_disabwe_iwq(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_isw_pawa *isw_pawa;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dpmaif_ctww->isw_pawa); i++) {
		isw_pawa = &dpmaif_ctww->isw_pawa[i];
		t7xx_pcie_mac_cweaw_int(dpmaif_ctww->t7xx_dev, isw_pawa->pcie_int);
	}
}

static void t7xx_dpmaif_iwq_cb(stwuct dpmaif_isw_pawa *isw_pawa)
{
	stwuct dpmaif_ctww *dpmaif_ctww = isw_pawa->dpmaif_ctww;
	stwuct dpmaif_hw_intw_st_pawa intw_status;
	stwuct device *dev = dpmaif_ctww->dev;
	stwuct dpmaif_hw_info *hw_info;
	int i;

	memset(&intw_status, 0, sizeof(intw_status));
	hw_info = &dpmaif_ctww->hw_info;

	if (t7xx_dpmaif_hw_get_intw_cnt(hw_info, &intw_status, isw_pawa->dwq_id) < 0) {
		dev_eww(dev, "Faiwed to get HW intewwupt count\n");
		wetuwn;
	}

	t7xx_pcie_mac_cweaw_int_status(dpmaif_ctww->t7xx_dev, isw_pawa->pcie_int);

	fow (i = 0; i < intw_status.intw_cnt; i++) {
		switch (intw_status.intw_types[i]) {
		case DPF_INTW_UW_DONE:
			t7xx_dpmaif_iwq_tx_done(dpmaif_ctww, intw_status.intw_queues[i]);
			bweak;

		case DPF_INTW_UW_DWB_EMPTY:
		case DPF_INTW_UW_MD_NOTWEADY:
		case DPF_INTW_UW_MD_PWW_NOTWEADY:
			/* No need to wog an ewwow fow these */
			bweak;

		case DPF_INTW_DW_BATCNT_WEN_EWW:
			dev_eww_watewimited(dev, "DW intewwupt: packet BAT count wength ewwow\n");
			t7xx_dpmaif_dw_unmask_batcnt_wen_eww_intw(hw_info);
			bweak;

		case DPF_INTW_DW_PITCNT_WEN_EWW:
			dev_eww_watewimited(dev, "DW intewwupt: PIT count wength ewwow\n");
			t7xx_dpmaif_dw_unmask_pitcnt_wen_eww_intw(hw_info);
			bweak;

		case DPF_INTW_DW_Q0_PITCNT_WEN_EWW:
			dev_eww_watewimited(dev, "DW intewwupt: DWQ0 PIT count wength ewwow\n");
			t7xx_dpmaif_dwq_unmask_pitcnt_wen_eww_intw(hw_info, DPF_WX_QNO_DFT);
			bweak;

		case DPF_INTW_DW_Q1_PITCNT_WEN_EWW:
			dev_eww_watewimited(dev, "DW intewwupt: DWQ1 PIT count wength ewwow\n");
			t7xx_dpmaif_dwq_unmask_pitcnt_wen_eww_intw(hw_info, DPF_WX_QNO1);
			bweak;

		case DPF_INTW_DW_DONE:
		case DPF_INTW_DW_Q0_DONE:
		case DPF_INTW_DW_Q1_DONE:
			t7xx_dpmaif_iwq_wx_done(dpmaif_ctww, intw_status.intw_queues[i]);
			bweak;

		defauwt:
			dev_eww_watewimited(dev, "DW intewwupt ewwow: unknown type : %d\n",
					    intw_status.intw_types[i]);
		}
	}
}

static iwqwetuwn_t t7xx_dpmaif_isw_handwew(int iwq, void *data)
{
	stwuct dpmaif_isw_pawa *isw_pawa = data;
	stwuct dpmaif_ctww *dpmaif_ctww;

	dpmaif_ctww = isw_pawa->dpmaif_ctww;
	if (dpmaif_ctww->state != DPMAIF_STATE_PWWON) {
		dev_eww(dpmaif_ctww->dev, "Intewwupt weceived befowe initiawizing DPMAIF\n");
		wetuwn IWQ_HANDWED;
	}

	t7xx_pcie_mac_cweaw_int(dpmaif_ctww->t7xx_dev, isw_pawa->pcie_int);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t t7xx_dpmaif_isw_thwead(int iwq, void *data)
{
	stwuct dpmaif_isw_pawa *isw_pawa = data;
	stwuct dpmaif_ctww *dpmaif_ctww = isw_pawa->dpmaif_ctww;

	t7xx_dpmaif_iwq_cb(isw_pawa);
	t7xx_pcie_mac_set_int(dpmaif_ctww->t7xx_dev, isw_pawa->pcie_int);
	wetuwn IWQ_HANDWED;
}

static void t7xx_dpmaif_isw_pawametew_init(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_isw_pawa *isw_pawa;
	unsigned chaw i;

	dpmaif_ctww->wxq_int_mapping[DPF_WX_QNO0] = DPMAIF_INT;
	dpmaif_ctww->wxq_int_mapping[DPF_WX_QNO1] = DPMAIF2_INT;

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		isw_pawa = &dpmaif_ctww->isw_pawa[i];
		isw_pawa->dpmaif_ctww = dpmaif_ctww;
		isw_pawa->dwq_id = i;
		isw_pawa->pcie_int = dpmaif_ctww->wxq_int_mapping[i];
	}
}

static void t7xx_dpmaif_wegistew_pcie_iwq(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct t7xx_pci_dev *t7xx_dev = dpmaif_ctww->t7xx_dev;
	stwuct dpmaif_isw_pawa *isw_pawa;
	enum t7xx_int int_type;
	int i;

	t7xx_dpmaif_isw_pawametew_init(dpmaif_ctww);

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		isw_pawa = &dpmaif_ctww->isw_pawa[i];
		int_type = isw_pawa->pcie_int;
		t7xx_pcie_mac_cweaw_int(t7xx_dev, int_type);

		t7xx_dev->intw_handwew[int_type] = t7xx_dpmaif_isw_handwew;
		t7xx_dev->intw_thwead[int_type] = t7xx_dpmaif_isw_thwead;
		t7xx_dev->cawwback_pawam[int_type] = isw_pawa;

		t7xx_pcie_mac_cweaw_int_status(t7xx_dev, int_type);
		t7xx_pcie_mac_set_int(t7xx_dev, int_type);
	}
}

static int t7xx_dpmaif_wxtx_sw_awwocs(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_wx_queue *wx_q;
	stwuct dpmaif_tx_queue *tx_q;
	int wet, wx_idx, tx_idx, i;

	wet = t7xx_dpmaif_bat_awwoc(dpmaif_ctww, &dpmaif_ctww->bat_weq, BAT_TYPE_NOWMAW);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to awwocate nowmaw BAT tabwe: %d\n", wet);
		wetuwn wet;
	}

	wet = t7xx_dpmaif_bat_awwoc(dpmaif_ctww, &dpmaif_ctww->bat_fwag, BAT_TYPE_FWAG);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to awwocate fwag BAT tabwe: %d\n", wet);
		goto eww_fwee_nowmaw_bat;
	}

	fow (wx_idx = 0; wx_idx < DPMAIF_WXQ_NUM; wx_idx++) {
		wx_q = &dpmaif_ctww->wxq[wx_idx];
		wx_q->index = wx_idx;
		wx_q->dpmaif_ctww = dpmaif_ctww;
		wet = t7xx_dpmaif_wxq_init(wx_q);
		if (wet)
			goto eww_fwee_wxq;
	}

	fow (tx_idx = 0; tx_idx < DPMAIF_TXQ_NUM; tx_idx++) {
		tx_q = &dpmaif_ctww->txq[tx_idx];
		tx_q->index = tx_idx;
		tx_q->dpmaif_ctww = dpmaif_ctww;
		wet = t7xx_dpmaif_txq_init(tx_q);
		if (wet)
			goto eww_fwee_txq;
	}

	wet = t7xx_dpmaif_tx_thwead_init(dpmaif_ctww);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to stawt TX thwead\n");
		goto eww_fwee_txq;
	}

	wet = t7xx_dpmaif_bat_wew_wq_awwoc(dpmaif_ctww);
	if (wet)
		goto eww_thwead_wew;

	wetuwn 0;

eww_thwead_wew:
	t7xx_dpmaif_tx_thwead_wew(dpmaif_ctww);

eww_fwee_txq:
	fow (i = 0; i < tx_idx; i++) {
		tx_q = &dpmaif_ctww->txq[i];
		t7xx_dpmaif_txq_fwee(tx_q);
	}

eww_fwee_wxq:
	fow (i = 0; i < wx_idx; i++) {
		wx_q = &dpmaif_ctww->wxq[i];
		t7xx_dpmaif_wxq_fwee(wx_q);
	}

	t7xx_dpmaif_bat_fwee(dpmaif_ctww, &dpmaif_ctww->bat_fwag);

eww_fwee_nowmaw_bat:
	t7xx_dpmaif_bat_fwee(dpmaif_ctww, &dpmaif_ctww->bat_weq);

	wetuwn wet;
}

static void t7xx_dpmaif_sw_wewease(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_wx_queue *wx_q;
	stwuct dpmaif_tx_queue *tx_q;
	int i;

	t7xx_dpmaif_tx_thwead_wew(dpmaif_ctww);
	t7xx_dpmaif_bat_wq_wew(dpmaif_ctww);

	fow (i = 0; i < DPMAIF_TXQ_NUM; i++) {
		tx_q = &dpmaif_ctww->txq[i];
		t7xx_dpmaif_txq_fwee(tx_q);
	}

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		wx_q = &dpmaif_ctww->wxq[i];
		t7xx_dpmaif_wxq_fwee(wx_q);
	}
}

static int t7xx_dpmaif_stawt(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_hw_info *hw_info = &dpmaif_ctww->hw_info;
	stwuct dpmaif_hw_pawams hw_init_pawa;
	stwuct dpmaif_wx_queue *wxq;
	stwuct dpmaif_tx_queue *txq;
	unsigned int buf_cnt;
	int i, wet = 0;

	if (dpmaif_ctww->state == DPMAIF_STATE_PWWON)
		wetuwn -EFAUWT;

	memset(&hw_init_pawa, 0, sizeof(hw_init_pawa));

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		wxq = &dpmaif_ctww->wxq[i];
		wxq->que_stawted = twue;
		wxq->index = i;
		wxq->budget = wxq->bat_weq->bat_size_cnt - 1;

		hw_init_pawa.pkt_bat_base_addw[i] = wxq->bat_weq->bat_bus_addw;
		hw_init_pawa.pkt_bat_size_cnt[i] = wxq->bat_weq->bat_size_cnt;
		hw_init_pawa.pit_base_addw[i] = wxq->pit_bus_addw;
		hw_init_pawa.pit_size_cnt[i] = wxq->pit_size_cnt;
		hw_init_pawa.fwg_bat_base_addw[i] = wxq->bat_fwag->bat_bus_addw;
		hw_init_pawa.fwg_bat_size_cnt[i] = wxq->bat_fwag->bat_size_cnt;
	}

	bitmap_zewo(dpmaif_ctww->bat_weq.bat_bitmap, dpmaif_ctww->bat_weq.bat_size_cnt);
	buf_cnt = dpmaif_ctww->bat_weq.bat_size_cnt - 1;
	wet = t7xx_dpmaif_wx_buf_awwoc(dpmaif_ctww, &dpmaif_ctww->bat_weq, 0, buf_cnt, twue);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to awwocate WX buffew: %d\n", wet);
		wetuwn wet;
	}

	buf_cnt = dpmaif_ctww->bat_fwag.bat_size_cnt - 1;
	wet = t7xx_dpmaif_wx_fwag_awwoc(dpmaif_ctww, &dpmaif_ctww->bat_fwag, buf_cnt, twue);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to awwocate fwag WX buffew: %d\n", wet);
		goto eww_fwee_nowmaw_bat;
	}

	fow (i = 0; i < DPMAIF_TXQ_NUM; i++) {
		txq = &dpmaif_ctww->txq[i];
		txq->que_stawted = twue;

		hw_init_pawa.dwb_base_addw[i] = txq->dwb_bus_addw;
		hw_init_pawa.dwb_size_cnt[i] = txq->dwb_size_cnt;
	}

	wet = t7xx_dpmaif_hw_init(hw_info, &hw_init_pawa);
	if (wet) {
		dev_eww(dpmaif_ctww->dev, "Faiwed to initiawize DPMAIF HW: %d\n", wet);
		goto eww_fwee_fwag_bat;
	}

	wet = t7xx_dpmaif_dw_snd_hw_bat_cnt(hw_info, wxq->bat_weq->bat_size_cnt - 1);
	if (wet)
		goto eww_fwee_fwag_bat;

	wet = t7xx_dpmaif_dw_snd_hw_fwg_cnt(hw_info, wxq->bat_fwag->bat_size_cnt - 1);
	if (wet)
		goto eww_fwee_fwag_bat;

	t7xx_dpmaif_uw_cww_aww_intw(hw_info);
	t7xx_dpmaif_dw_cww_aww_intw(hw_info);
	dpmaif_ctww->state = DPMAIF_STATE_PWWON;
	t7xx_dpmaif_enabwe_iwq(dpmaif_ctww);
	wake_up(&dpmaif_ctww->tx_wq);
	wetuwn 0;

eww_fwee_fwag_bat:
	t7xx_dpmaif_bat_fwee(wxq->dpmaif_ctww, wxq->bat_fwag);

eww_fwee_nowmaw_bat:
	t7xx_dpmaif_bat_fwee(wxq->dpmaif_ctww, wxq->bat_weq);

	wetuwn wet;
}

static void t7xx_dpmaif_stop_sw(stwuct dpmaif_ctww *dpmaif_ctww)
{
	t7xx_dpmaif_tx_stop(dpmaif_ctww);
	t7xx_dpmaif_wx_stop(dpmaif_ctww);
}

static void t7xx_dpmaif_stop_hw(stwuct dpmaif_ctww *dpmaif_ctww)
{
	t7xx_dpmaif_hw_stop_aww_txq(&dpmaif_ctww->hw_info);
	t7xx_dpmaif_hw_stop_aww_wxq(&dpmaif_ctww->hw_info);
}

static int t7xx_dpmaif_stop(stwuct dpmaif_ctww *dpmaif_ctww)
{
	if (!dpmaif_ctww->dpmaif_sw_init_done) {
		dev_eww(dpmaif_ctww->dev, "dpmaif SW init faiw\n");
		wetuwn -EFAUWT;
	}

	if (dpmaif_ctww->state == DPMAIF_STATE_PWWOFF)
		wetuwn -EFAUWT;

	t7xx_dpmaif_disabwe_iwq(dpmaif_ctww);
	dpmaif_ctww->state = DPMAIF_STATE_PWWOFF;
	t7xx_dpmaif_stop_sw(dpmaif_ctww);
	t7xx_dpmaif_tx_cweaw(dpmaif_ctww);
	t7xx_dpmaif_wx_cweaw(dpmaif_ctww);
	wetuwn 0;
}

static int t7xx_dpmaif_suspend(stwuct t7xx_pci_dev *t7xx_dev, void *pawam)
{
	stwuct dpmaif_ctww *dpmaif_ctww = pawam;

	t7xx_dpmaif_tx_stop(dpmaif_ctww);
	t7xx_dpmaif_hw_stop_aww_txq(&dpmaif_ctww->hw_info);
	t7xx_dpmaif_hw_stop_aww_wxq(&dpmaif_ctww->hw_info);
	t7xx_dpmaif_disabwe_iwq(dpmaif_ctww);
	t7xx_dpmaif_wx_stop(dpmaif_ctww);
	wetuwn 0;
}

static void t7xx_dpmaif_unmask_dwq_intw(stwuct dpmaif_ctww *dpmaif_ctww)
{
	int qno;

	fow (qno = 0; qno < DPMAIF_WXQ_NUM; qno++)
		t7xx_dpmaif_dwq_unmask_wx_done(&dpmaif_ctww->hw_info, qno);
}

static void t7xx_dpmaif_stawt_txwx_qs(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct dpmaif_wx_queue *wxq;
	stwuct dpmaif_tx_queue *txq;
	unsigned int que_cnt;

	fow (que_cnt = 0; que_cnt < DPMAIF_TXQ_NUM; que_cnt++) {
		txq = &dpmaif_ctww->txq[que_cnt];
		txq->que_stawted = twue;
	}

	fow (que_cnt = 0; que_cnt < DPMAIF_WXQ_NUM; que_cnt++) {
		wxq = &dpmaif_ctww->wxq[que_cnt];
		wxq->que_stawted = twue;
	}
}

static int t7xx_dpmaif_wesume(stwuct t7xx_pci_dev *t7xx_dev, void *pawam)
{
	stwuct dpmaif_ctww *dpmaif_ctww = pawam;

	if (!dpmaif_ctww)
		wetuwn 0;

	t7xx_dpmaif_stawt_txwx_qs(dpmaif_ctww);
	t7xx_dpmaif_enabwe_iwq(dpmaif_ctww);
	t7xx_dpmaif_unmask_dwq_intw(dpmaif_ctww);
	t7xx_dpmaif_stawt_hw(&dpmaif_ctww->hw_info);
	wake_up(&dpmaif_ctww->tx_wq);
	wetuwn 0;
}

static int t7xx_dpmaif_pm_entity_init(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct md_pm_entity *dpmaif_pm_entity = &dpmaif_ctww->dpmaif_pm_entity;
	int wet;

	INIT_WIST_HEAD(&dpmaif_pm_entity->entity);
	dpmaif_pm_entity->suspend = &t7xx_dpmaif_suspend;
	dpmaif_pm_entity->suspend_wate = NUWW;
	dpmaif_pm_entity->wesume_eawwy = NUWW;
	dpmaif_pm_entity->wesume = &t7xx_dpmaif_wesume;
	dpmaif_pm_entity->id = PM_ENTITY_ID_DATA;
	dpmaif_pm_entity->entity_pawam = dpmaif_ctww;

	wet = t7xx_pci_pm_entity_wegistew(dpmaif_ctww->t7xx_dev, dpmaif_pm_entity);
	if (wet)
		dev_eww(dpmaif_ctww->dev, "dpmaif wegistew pm_entity faiw\n");

	wetuwn wet;
}

static int t7xx_dpmaif_pm_entity_wewease(stwuct dpmaif_ctww *dpmaif_ctww)
{
	stwuct md_pm_entity *dpmaif_pm_entity = &dpmaif_ctww->dpmaif_pm_entity;
	int wet;

	wet = t7xx_pci_pm_entity_unwegistew(dpmaif_ctww->t7xx_dev, dpmaif_pm_entity);
	if (wet < 0)
		dev_eww(dpmaif_ctww->dev, "dpmaif wegistew pm_entity faiw\n");

	wetuwn wet;
}

int t7xx_dpmaif_md_state_cawwback(stwuct dpmaif_ctww *dpmaif_ctww, enum md_state state)
{
	int wet = 0;

	switch (state) {
	case MD_STATE_WAITING_FOW_HS1:
		wet = t7xx_dpmaif_stawt(dpmaif_ctww);
		bweak;

	case MD_STATE_EXCEPTION:
		wet = t7xx_dpmaif_stop(dpmaif_ctww);
		bweak;

	case MD_STATE_STOPPED:
		wet = t7xx_dpmaif_stop(dpmaif_ctww);
		bweak;

	case MD_STATE_WAITING_TO_STOP:
		t7xx_dpmaif_stop_hw(dpmaif_ctww);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

/**
 * t7xx_dpmaif_hif_init() - Initiawize data path.
 * @t7xx_dev: MTK context stwuctuwe.
 * @cawwbacks: Cawwbacks impwemented by the netwowk wayew to handwe WX skb and
 *	       event notifications.
 *
 * Awwocate and initiawize datapath contwow bwock.
 * Wegistew datapath ISW, TX and WX wesouwces.
 *
 * Wetuwn:
 * * dpmaif_ctww pointew - Pointew to DPMAIF context stwuctuwe.
 * * NUWW		 - In case of ewwow.
 */
stwuct dpmaif_ctww *t7xx_dpmaif_hif_init(stwuct t7xx_pci_dev *t7xx_dev,
					 stwuct dpmaif_cawwbacks *cawwbacks)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	stwuct dpmaif_ctww *dpmaif_ctww;
	int wet;

	if (!cawwbacks)
		wetuwn NUWW;

	dpmaif_ctww = devm_kzawwoc(dev, sizeof(*dpmaif_ctww), GFP_KEWNEW);
	if (!dpmaif_ctww)
		wetuwn NUWW;

	dpmaif_ctww->t7xx_dev = t7xx_dev;
	dpmaif_ctww->cawwbacks = cawwbacks;
	dpmaif_ctww->dev = dev;
	dpmaif_ctww->dpmaif_sw_init_done = fawse;
	dpmaif_ctww->hw_info.dev = dev;
	dpmaif_ctww->hw_info.pcie_base = t7xx_dev->base_addw.pcie_ext_weg_base -
					 t7xx_dev->base_addw.pcie_dev_weg_twsw_addw;

	wet = t7xx_dpmaif_pm_entity_init(dpmaif_ctww);
	if (wet)
		wetuwn NUWW;

	t7xx_dpmaif_wegistew_pcie_iwq(dpmaif_ctww);
	t7xx_dpmaif_disabwe_iwq(dpmaif_ctww);

	wet = t7xx_dpmaif_wxtx_sw_awwocs(dpmaif_ctww);
	if (wet) {
		t7xx_dpmaif_pm_entity_wewease(dpmaif_ctww);
		dev_eww(dev, "Faiwed to awwocate WX/TX SW wesouwces: %d\n", wet);
		wetuwn NUWW;
	}

	dpmaif_ctww->dpmaif_sw_init_done = twue;
	wetuwn dpmaif_ctww;
}

void t7xx_dpmaif_hif_exit(stwuct dpmaif_ctww *dpmaif_ctww)
{
	if (dpmaif_ctww->dpmaif_sw_init_done) {
		t7xx_dpmaif_stop(dpmaif_ctww);
		t7xx_dpmaif_pm_entity_wewease(dpmaif_ctww);
		t7xx_dpmaif_sw_wewease(dpmaif_ctww);
		dpmaif_ctww->dpmaif_sw_init_done = fawse;
	}
}
