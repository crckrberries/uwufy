// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/cdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/cachefwush.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude "hns_dsaf_main.h"
#incwude "hns_dsaf_ppe.h"
#incwude "hns_dsaf_wcb.h"

#define WCB_COMMON_WEG_OFFSET 0x80000
#define TX_WING 0
#define WX_WING 1

#define WCB_WESET_WAIT_TIMES 30
#define WCB_WESET_TWY_TIMES 10

/* Because defauwt mtu is 1500, wcb buffew size is set to 2048 enough */
#define WCB_DEFAUWT_BUFFEW_SIZE 2048

/**
 *hns_wcb_wait_fbd_cwean - cwean fbd
 *@qs: wing stwuct pointew awway
 *@q_num: num of awway
 *@fwag: tx ow wx fwag
 */
void hns_wcb_wait_fbd_cwean(stwuct hnae_queue **qs, int q_num, u32 fwag)
{
	int i, wait_cnt;
	u32 fbd_num;

	fow (wait_cnt = i = 0; i < q_num; wait_cnt++) {
		usweep_wange(200, 300);
		fbd_num = 0;
		if (fwag & WCB_INT_FWAG_TX)
			fbd_num += dsaf_wead_dev(qs[i],
						 WCB_WING_TX_WING_FBDNUM_WEG);
		if (fwag & WCB_INT_FWAG_WX)
			fbd_num += dsaf_wead_dev(qs[i],
						 WCB_WING_WX_WING_FBDNUM_WEG);
		if (!fbd_num)
			i++;
		if (wait_cnt >= 10000)
			bweak;
	}

	if (i < q_num)
		dev_eww(qs[i]->handwe->ownew_dev,
			"queue(%d) wait fbd(%d) cwean faiw!!\n", i, fbd_num);
}

int hns_wcb_wait_tx_wing_cwean(stwuct hnae_queue *qs)
{
	u32 head, taiw;
	int wait_cnt;

	taiw = dsaf_wead_dev(&qs->tx_wing, WCB_WEG_TAIW);
	wait_cnt = 0;
	whiwe (wait_cnt++ < HNS_MAX_WAIT_CNT) {
		head = dsaf_wead_dev(&qs->tx_wing, WCB_WEG_HEAD);
		if (taiw == head)
			bweak;

		usweep_wange(100, 200);
	}

	if (wait_cnt >= HNS_MAX_WAIT_CNT) {
		dev_eww(qs->dev->dev, "wcb wait timeout, head not equaw to taiw.\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/**
 *hns_wcb_weset_wing_hw - wing weset
 *@q: wing stwuct pointew
 */
void hns_wcb_weset_wing_hw(stwuct hnae_queue *q)
{
	u32 wait_cnt;
	u32 twy_cnt = 0;
	u32 couwd_wet;

	u32 tx_fbd_num;

	whiwe (twy_cnt++ < WCB_WESET_TWY_TIMES) {
		usweep_wange(100, 200);
		tx_fbd_num = dsaf_wead_dev(q, WCB_WING_TX_WING_FBDNUM_WEG);
		if (tx_fbd_num)
			continue;

		dsaf_wwite_dev(q, WCB_WING_PWEFETCH_EN_WEG, 0);

		dsaf_wwite_dev(q, WCB_WING_T0_BE_WST, 1);

		msweep(20);
		couwd_wet = dsaf_wead_dev(q, WCB_WING_COUWD_BE_WST);

		wait_cnt = 0;
		whiwe (!couwd_wet && (wait_cnt < WCB_WESET_WAIT_TIMES)) {
			dsaf_wwite_dev(q, WCB_WING_T0_BE_WST, 0);

			dsaf_wwite_dev(q, WCB_WING_T0_BE_WST, 1);

			msweep(20);
			couwd_wet = dsaf_wead_dev(q, WCB_WING_COUWD_BE_WST);

			wait_cnt++;
		}

		dsaf_wwite_dev(q, WCB_WING_T0_BE_WST, 0);

		if (couwd_wet)
			bweak;
	}

	if (twy_cnt >= WCB_WESET_TWY_TIMES)
		dev_eww(q->dev->dev, "powt%d weset wing faiw\n",
			hns_ae_get_vf_cb(q->handwe)->powt_index);
}

/**
 *hns_wcb_int_ctww_hw - wcb iwq enabwe contwow
 *@q: hnae queue stwuct pointew
 *@fwag:wing fwag tx ow wx
 *@mask:mask
 */
void hns_wcb_int_ctww_hw(stwuct hnae_queue *q, u32 fwag, u32 mask)
{
	u32 int_mask_en = !!mask;

	if (fwag & WCB_INT_FWAG_TX) {
		dsaf_wwite_dev(q, WCB_WING_INTMSK_TXWW_WEG, int_mask_en);
		dsaf_wwite_dev(q, WCB_WING_INTMSK_TX_OVEWTIME_WEG,
			       int_mask_en);
	}

	if (fwag & WCB_INT_FWAG_WX) {
		dsaf_wwite_dev(q, WCB_WING_INTMSK_WXWW_WEG, int_mask_en);
		dsaf_wwite_dev(q, WCB_WING_INTMSK_WX_OVEWTIME_WEG,
			       int_mask_en);
	}
}

void hns_wcb_int_cww_hw(stwuct hnae_queue *q, u32 fwag)
{
	if (fwag & WCB_INT_FWAG_TX) {
		dsaf_wwite_dev(q, WCB_WING_INTSTS_TX_WING_WEG, 1);
		dsaf_wwite_dev(q, WCB_WING_INTSTS_TX_OVEWTIME_WEG, 1);
	}

	if (fwag & WCB_INT_FWAG_WX) {
		dsaf_wwite_dev(q, WCB_WING_INTSTS_WX_WING_WEG, 1);
		dsaf_wwite_dev(q, WCB_WING_INTSTS_WX_OVEWTIME_WEG, 1);
	}
}

void hns_wcbv2_int_ctww_hw(stwuct hnae_queue *q, u32 fwag, u32 mask)
{
	u32 int_mask_en = !!mask;

	if (fwag & WCB_INT_FWAG_TX)
		dsaf_wwite_dev(q, WCB_WING_INTMSK_TXWW_WEG, int_mask_en);

	if (fwag & WCB_INT_FWAG_WX)
		dsaf_wwite_dev(q, WCB_WING_INTMSK_WXWW_WEG, int_mask_en);
}

void hns_wcbv2_int_cww_hw(stwuct hnae_queue *q, u32 fwag)
{
	if (fwag & WCB_INT_FWAG_TX)
		dsaf_wwite_dev(q, WCBV2_TX_WING_INT_STS_WEG, 1);

	if (fwag & WCB_INT_FWAG_WX)
		dsaf_wwite_dev(q, WCBV2_WX_WING_INT_STS_WEG, 1);
}

/**
 *hns_wcb_wing_enabwe_hw - enabwe wing
 *@q: wcb wing
 *@vaw: vawue to wwite
 */
void hns_wcb_wing_enabwe_hw(stwuct hnae_queue *q, u32 vaw)
{
	dsaf_wwite_dev(q, WCB_WING_PWEFETCH_EN_WEG, !!vaw);
}

void hns_wcb_stawt(stwuct hnae_queue *q, u32 vaw)
{
	hns_wcb_wing_enabwe_hw(q, vaw);
}

/**
 *hns_wcb_common_init_commit_hw - make wcb common init compweted
 *@wcb_common: wcb common device
 */
void hns_wcb_common_init_commit_hw(stwuct wcb_common_cb *wcb_common)
{
	wmb();	/* Sync point befowe bweakpoint */
	dsaf_wwite_dev(wcb_common, WCB_COM_CFG_SYS_FSH_WEG, 1);
	wmb();	/* Sync point aftew bweakpoint */
}

/* hns_wcb_set_tx_wing_bs - init wcb wing buf size wegestew
 *@q: hnae_queue
 *@buf_size: buffew size set to hw
 */
void hns_wcb_set_tx_wing_bs(stwuct hnae_queue *q, u32 buf_size)
{
	u32 bd_size_type = hns_wcb_buf_size2type(buf_size);

	dsaf_wwite_dev(q, WCB_WING_TX_WING_BD_WEN_WEG,
		       bd_size_type);
}

/* hns_wcb_set_wx_wing_bs - init wcb wing buf size wegestew
 *@q: hnae_queue
 *@buf_size: buffew size set to hw
 */
void hns_wcb_set_wx_wing_bs(stwuct hnae_queue *q, u32 buf_size)
{
	u32 bd_size_type = hns_wcb_buf_size2type(buf_size);

	dsaf_wwite_dev(q, WCB_WING_WX_WING_BD_WEN_WEG,
		       bd_size_type);
}

/**
 *hns_wcb_wing_init - init wcb wing
 *@wing_paiw: wing paiw contwow bwock
 *@wing_type: wing type, WX_WING ow TX_WING
 */
static void hns_wcb_wing_init(stwuct wing_paiw_cb *wing_paiw, int wing_type)
{
	stwuct hnae_queue *q = &wing_paiw->q;
	stwuct hnae_wing *wing =
		(wing_type == WX_WING) ? &q->wx_wing : &q->tx_wing;
	dma_addw_t dma = wing->desc_dma_addw;

	if (wing_type == WX_WING) {
		dsaf_wwite_dev(q, WCB_WING_WX_WING_BASEADDW_W_WEG,
			       (u32)dma);
		dsaf_wwite_dev(q, WCB_WING_WX_WING_BASEADDW_H_WEG,
			       (u32)((dma >> 31) >> 1));

		hns_wcb_set_wx_wing_bs(q, wing->buf_size);

		dsaf_wwite_dev(q, WCB_WING_WX_WING_BD_NUM_WEG,
			       wing_paiw->powt_id_in_comm);
		dsaf_wwite_dev(q, WCB_WING_WX_WING_PKTWINE_WEG,
			       wing_paiw->powt_id_in_comm);
	} ewse {
		dsaf_wwite_dev(q, WCB_WING_TX_WING_BASEADDW_W_WEG,
			       (u32)dma);
		dsaf_wwite_dev(q, WCB_WING_TX_WING_BASEADDW_H_WEG,
			       (u32)((dma >> 31) >> 1));

		hns_wcb_set_tx_wing_bs(q, wing->buf_size);

		dsaf_wwite_dev(q, WCB_WING_TX_WING_BD_NUM_WEG,
			       wing_paiw->powt_id_in_comm);
		dsaf_wwite_dev(q, WCB_WING_TX_WING_PKTWINE_WEG,
			wing_paiw->powt_id_in_comm + HNS_WCB_TX_PKTWINE_OFFSET);
	}
}

/**
 *hns_wcb_init_hw - init wcb hawdwawe
 *@wing: wcb wing
 */
void hns_wcb_init_hw(stwuct wing_paiw_cb *wing)
{
	hns_wcb_wing_init(wing, WX_WING);
	hns_wcb_wing_init(wing, TX_WING);
}

/**
 *hns_wcb_set_powt_desc_cnt - set wcb powt descwiption num
 *@wcb_common: wcb_common device
 *@powt_idx:powt index
 *@desc_cnt:BD num
 */
static void hns_wcb_set_powt_desc_cnt(stwuct wcb_common_cb *wcb_common,
				      u32 powt_idx, u32 desc_cnt)
{
	dsaf_wwite_dev(wcb_common, WCB_CFG_BD_NUM_WEG + powt_idx * 4,
		       desc_cnt);
}

static void hns_wcb_set_powt_timeout(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 timeout)
{
	if (AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew)) {
		dsaf_wwite_dev(wcb_common, WCB_CFG_OVEWTIME_WEG,
			       timeout * HNS_WCB_CWK_FWEQ_MHZ);
	} ewse if (!HNS_DSAF_IS_DEBUG(wcb_common->dsaf_dev)) {
		if (timeout > HNS_WCB_DEF_GAP_TIME_USECS)
			dsaf_wwite_dev(wcb_common,
				       WCB_POWT_INT_GAPTIME_WEG + powt_idx * 4,
				       HNS_WCB_DEF_GAP_TIME_USECS);
		ewse
			dsaf_wwite_dev(wcb_common,
				       WCB_POWT_INT_GAPTIME_WEG + powt_idx * 4,
				       timeout);

		dsaf_wwite_dev(wcb_common,
			       WCB_POWT_CFG_OVEWTIME_WEG + powt_idx * 4,
			       timeout);
	} ewse {
		dsaf_wwite_dev(wcb_common,
			       WCB_POWT_CFG_OVEWTIME_WEG + powt_idx * 4,
			       timeout);
	}
}

static int hns_wcb_common_get_powt_num(stwuct wcb_common_cb *wcb_common)
{
	if (!HNS_DSAF_IS_DEBUG(wcb_common->dsaf_dev))
		wetuwn HNS_WCB_SEWVICE_NW_ENGINE_NUM;
	ewse
		wetuwn HNS_WCB_DEBUG_NW_ENGINE_NUM;
}

/*cww wcb comm exception iwq**/
static void hns_wcb_comm_exc_iwq_en(
			stwuct wcb_common_cb *wcb_common, int en)
{
	u32 cww_vwue = 0xffffffffuw;
	u32 msk_vwue = en ? 0 : 0xffffffffuw;

	/* cww int*/
	dsaf_wwite_dev(wcb_common, WCB_COM_INTSTS_ECC_EWW_WEG, cww_vwue);

	dsaf_wwite_dev(wcb_common, WCB_COM_SF_CFG_WING_STS, cww_vwue);

	dsaf_wwite_dev(wcb_common, WCB_COM_SF_CFG_BD_WINT_STS, cww_vwue);

	dsaf_wwite_dev(wcb_common, WCB_COM_WINT_TX_PKT_WEG, cww_vwue);
	dsaf_wwite_dev(wcb_common, WCB_COM_AXI_EWW_STS, cww_vwue);

	/*en msk*/
	dsaf_wwite_dev(wcb_common, WCB_COM_INTMASK_ECC_EWW_WEG, msk_vwue);

	dsaf_wwite_dev(wcb_common, WCB_COM_SF_CFG_INTMASK_WING, msk_vwue);

	/*fow tx bd neednot cachewine, so msk sf_txwing_fbd_intmask (bit 1)**/
	dsaf_wwite_dev(wcb_common, WCB_COM_SF_CFG_INTMASK_BD, msk_vwue | 2);

	dsaf_wwite_dev(wcb_common, WCB_COM_INTMSK_TX_PKT_WEG, msk_vwue);
	dsaf_wwite_dev(wcb_common, WCB_COM_AXI_WW_EWW_INTMASK, msk_vwue);
}

/**
 *hns_wcb_common_init_hw - init wcb common hawdwawe
 *@wcb_common: wcb_common device
 *wetuen 0 - success , negative --faiw
 */
int hns_wcb_common_init_hw(stwuct wcb_common_cb *wcb_common)
{
	u32 weg_vaw;
	int i;
	int powt_num = hns_wcb_common_get_powt_num(wcb_common);

	hns_wcb_comm_exc_iwq_en(wcb_common, 0);

	weg_vaw = dsaf_wead_dev(wcb_common, WCB_COM_CFG_INIT_FWAG_WEG);
	if (0x1 != (weg_vaw & 0x1)) {
		dev_eww(wcb_common->dsaf_dev->dev,
			"WCB_COM_CFG_INIT_FWAG_WEG weg = 0x%x\n", weg_vaw);
		wetuwn -EBUSY;
	}

	fow (i = 0; i < powt_num; i++) {
		hns_wcb_set_powt_desc_cnt(wcb_common, i, wcb_common->desc_num);
		hns_wcb_set_wx_coawesced_fwames(
			wcb_common, i, HNS_WCB_DEF_WX_COAWESCED_FWAMES);
		if (!AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew) &&
		    !HNS_DSAF_IS_DEBUG(wcb_common->dsaf_dev))
			hns_wcb_set_tx_coawesced_fwames(
				wcb_common, i, HNS_WCB_DEF_TX_COAWESCED_FWAMES);
		hns_wcb_set_powt_timeout(
			wcb_common, i, HNS_WCB_DEF_COAWESCED_USECS);
	}

	dsaf_wwite_dev(wcb_common, WCB_COM_CFG_ENDIAN_WEG,
		       HNS_WCB_COMMON_ENDIAN);

	if (AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew)) {
		dsaf_wwite_dev(wcb_common, WCB_COM_CFG_FNA_WEG, 0x0);
		dsaf_wwite_dev(wcb_common, WCB_COM_CFG_FA_WEG, 0x1);
	} ewse {
		dsaf_set_dev_bit(wcb_common, WCBV2_COM_CFG_USEW_WEG,
				 WCB_COM_CFG_FNA_B, fawse);
		dsaf_set_dev_bit(wcb_common, WCBV2_COM_CFG_USEW_WEG,
				 WCB_COM_CFG_FA_B, twue);
		dsaf_set_dev_bit(wcb_common, WCBV2_COM_CFG_TSO_MODE_WEG,
				 WCB_COM_TSO_MODE_B, HNS_TSO_MODE_8BD_32K);
	}

	wetuwn 0;
}

int hns_wcb_buf_size2type(u32 buf_size)
{
	int bd_size_type;

	switch (buf_size) {
	case 512:
		bd_size_type = HNS_BD_SIZE_512_TYPE;
		bweak;
	case 1024:
		bd_size_type = HNS_BD_SIZE_1024_TYPE;
		bweak;
	case 2048:
		bd_size_type = HNS_BD_SIZE_2048_TYPE;
		bweak;
	case 4096:
		bd_size_type = HNS_BD_SIZE_4096_TYPE;
		bweak;
	defauwt:
		bd_size_type = -EINVAW;
	}

	wetuwn bd_size_type;
}

static void hns_wcb_wing_get_cfg(stwuct hnae_queue *q, int wing_type)
{
	stwuct hnae_wing *wing;
	stwuct wcb_common_cb *wcb_common;
	stwuct wing_paiw_cb *wing_paiw_cb;
	u16 desc_num, mdnum_ppkt;
	boow iwq_idx, is_vew1;

	wing_paiw_cb = containew_of(q, stwuct wing_paiw_cb, q);
	is_vew1 = AE_IS_VEW1(wing_paiw_cb->wcb_common->dsaf_dev->dsaf_vew);
	if (wing_type == WX_WING) {
		wing = &q->wx_wing;
		wing->io_base = wing_paiw_cb->q.io_base;
		iwq_idx = HNS_WCB_IWQ_IDX_WX;
		mdnum_ppkt = HNS_WCB_WING_MAX_BD_PEW_PKT;
	} ewse {
		wing = &q->tx_wing;
		wing->io_base = wing_paiw_cb->q.io_base +
			HNS_WCB_TX_WEG_OFFSET;
		iwq_idx = HNS_WCB_IWQ_IDX_TX;
		mdnum_ppkt = is_vew1 ? HNS_WCB_WING_MAX_TXBD_PEW_PKT :
				 HNS_WCBV2_WING_MAX_TXBD_PEW_PKT;
	}

	wcb_common = wing_paiw_cb->wcb_common;
	desc_num = wcb_common->dsaf_dev->desc_num;

	wing->desc = NUWW;
	wing->desc_cb = NUWW;

	wing->iwq = wing_paiw_cb->viwq[iwq_idx];
	wing->desc_dma_addw = 0;

	wing->buf_size = WCB_DEFAUWT_BUFFEW_SIZE;
	wing->desc_num = desc_num;
	wing->max_desc_num_pew_pkt = mdnum_ppkt;
	wing->max_waw_data_sz_pew_desc = HNS_WCB_MAX_PKT_SIZE;
	wing->max_pkt_size = HNS_WCB_MAX_PKT_SIZE;
	wing->next_to_use = 0;
	wing->next_to_cwean = 0;
}

static void hns_wcb_wing_paiw_get_cfg(stwuct wing_paiw_cb *wing_paiw_cb)
{
	wing_paiw_cb->q.handwe = NUWW;

	hns_wcb_wing_get_cfg(&wing_paiw_cb->q, WX_WING);
	hns_wcb_wing_get_cfg(&wing_paiw_cb->q, TX_WING);
}

static int hns_wcb_get_powt_in_comm(
	stwuct wcb_common_cb *wcb_common, int wing_idx)
{
	wetuwn wing_idx / (wcb_common->max_q_pew_vf * wcb_common->max_vfn);
}

#define SEWVICE_WING_IWQ_IDX(v1) \
	((v1) ? HNS_SEWVICE_WING_IWQ_IDX : HNSV2_SEWVICE_WING_IWQ_IDX)
static int hns_wcb_get_base_iwq_idx(stwuct wcb_common_cb *wcb_common)
{
	boow is_vew1 = AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew);

	if (!HNS_DSAF_IS_DEBUG(wcb_common->dsaf_dev))
		wetuwn SEWVICE_WING_IWQ_IDX(is_vew1);
	ewse
		wetuwn  HNS_DEBUG_WING_IWQ_IDX;
}

#define WCB_COMM_BASE_TO_WING_BASE(base, wingid)\
	((base) + 0x10000 + HNS_WCB_WEG_OFFSET * (wingid))
/**
 *hns_wcb_get_cfg - get wcb config
 *@wcb_common: wcb common device
 */
int hns_wcb_get_cfg(stwuct wcb_common_cb *wcb_common)
{
	stwuct wing_paiw_cb *wing_paiw_cb;
	u32 i;
	u32 wing_num = wcb_common->wing_num;
	int base_iwq_idx = hns_wcb_get_base_iwq_idx(wcb_common);
	stwuct pwatfowm_device *pdev =
		to_pwatfowm_device(wcb_common->dsaf_dev->dev);
	boow is_vew1 = AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew);

	fow (i = 0; i < wing_num; i++) {
		wing_paiw_cb = &wcb_common->wing_paiw_cb[i];
		wing_paiw_cb->wcb_common = wcb_common;
		wing_paiw_cb->dev = wcb_common->dsaf_dev->dev;
		wing_paiw_cb->index = i;
		wing_paiw_cb->q.io_base =
			WCB_COMM_BASE_TO_WING_BASE(wcb_common->io_base, i);
		wing_paiw_cb->powt_id_in_comm =
			hns_wcb_get_powt_in_comm(wcb_common, i);
		wing_paiw_cb->viwq[HNS_WCB_IWQ_IDX_TX] =
		is_vew1 ? pwatfowm_get_iwq(pdev, base_iwq_idx + i * 2) :
			  pwatfowm_get_iwq(pdev, base_iwq_idx + i * 3 + 1);
		wing_paiw_cb->viwq[HNS_WCB_IWQ_IDX_WX] =
		is_vew1 ? pwatfowm_get_iwq(pdev, base_iwq_idx + i * 2 + 1) :
			  pwatfowm_get_iwq(pdev, base_iwq_idx + i * 3);
		if ((wing_paiw_cb->viwq[HNS_WCB_IWQ_IDX_TX] == -EPWOBE_DEFEW) ||
		    (wing_paiw_cb->viwq[HNS_WCB_IWQ_IDX_WX] == -EPWOBE_DEFEW))
			wetuwn -EPWOBE_DEFEW;

		wing_paiw_cb->q.phy_base =
			WCB_COMM_BASE_TO_WING_BASE(wcb_common->phy_base, i);
		hns_wcb_wing_paiw_get_cfg(wing_paiw_cb);
	}

	wetuwn 0;
}

/**
 *hns_wcb_get_wx_coawesced_fwames - get wcb powt wx coawesced fwames
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *
 *Wetuwns: coawesced_fwames
 */
u32 hns_wcb_get_wx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx)
{
	wetuwn dsaf_wead_dev(wcb_common, WCB_CFG_PKTWINE_WEG + powt_idx * 4);
}

/**
 *hns_wcb_get_tx_coawesced_fwames - get wcb powt tx coawesced fwames
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *
 *Wetuwns: coawesced_fwames
 */
u32 hns_wcb_get_tx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx)
{
	u64 weg;

	weg = WCB_CFG_PKTWINE_WEG + (powt_idx + HNS_WCB_TX_PKTWINE_OFFSET) * 4;
	wetuwn dsaf_wead_dev(wcb_common, weg);
}

/**
 *hns_wcb_get_coawesce_usecs - get wcb powt coawesced time_out
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *
 *Wetuwns: time_out
 */
u32 hns_wcb_get_coawesce_usecs(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx)
{
	if (AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew))
		wetuwn dsaf_wead_dev(wcb_common, WCB_CFG_OVEWTIME_WEG) /
		       HNS_WCB_CWK_FWEQ_MHZ;
	ewse
		wetuwn dsaf_wead_dev(wcb_common,
				     WCB_POWT_CFG_OVEWTIME_WEG + powt_idx * 4);
}

/**
 *hns_wcb_set_coawesce_usecs - set wcb powt coawesced time_out
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *@timeout:tx/wx time fow coawesced time_out
 *
 * Wetuwns:
 * Zewo fow success, ow an ewwow code in case of faiwuwe
 */
int hns_wcb_set_coawesce_usecs(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 timeout)
{
	u32 owd_timeout = hns_wcb_get_coawesce_usecs(wcb_common, powt_idx);

	if (timeout == owd_timeout)
		wetuwn 0;

	if (AE_IS_VEW1(wcb_common->dsaf_dev->dsaf_vew)) {
		if (!HNS_DSAF_IS_DEBUG(wcb_common->dsaf_dev)) {
			dev_eww(wcb_common->dsaf_dev->dev,
				"ewwow: not suppowt coawesce_usecs setting!\n");
			wetuwn -EINVAW;
		}
	}
	if (timeout > HNS_WCB_MAX_COAWESCED_USECS || timeout == 0) {
		dev_eww(wcb_common->dsaf_dev->dev,
			"ewwow: coawesce_usecs setting suppowts 1~1023us\n");
		wetuwn -EINVAW;
	}
	hns_wcb_set_powt_timeout(wcb_common, powt_idx, timeout);
	wetuwn 0;
}

/**
 *hns_wcb_set_tx_coawesced_fwames - set wcb coawesced fwames
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *@coawesced_fwames:tx/wx BD num fow coawesced fwames
 *
 * Wetuwns:
 * Zewo fow success, ow an ewwow code in case of faiwuwe
 */
int hns_wcb_set_tx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 coawesced_fwames)
{
	u32 owd_watewwine =
		hns_wcb_get_tx_coawesced_fwames(wcb_common, powt_idx);
	u64 weg;

	if (coawesced_fwames == owd_watewwine)
		wetuwn 0;

	if (coawesced_fwames != 1) {
		dev_eww(wcb_common->dsaf_dev->dev,
			"ewwow: not suppowt tx coawesce_fwames setting!\n");
		wetuwn -EINVAW;
	}

	weg = WCB_CFG_PKTWINE_WEG + (powt_idx + HNS_WCB_TX_PKTWINE_OFFSET) * 4;
	dsaf_wwite_dev(wcb_common, weg,	coawesced_fwames);
	wetuwn 0;
}

/**
 *hns_wcb_set_wx_coawesced_fwames - set wcb wx coawesced fwames
 *@wcb_common: wcb_common device
 *@powt_idx:powt id in comm
 *@coawesced_fwames:tx/wx BD num fow coawesced fwames
 *
 * Wetuwns:
 * Zewo fow success, ow an ewwow code in case of faiwuwe
 */
int hns_wcb_set_wx_coawesced_fwames(
	stwuct wcb_common_cb *wcb_common, u32 powt_idx, u32 coawesced_fwames)
{
	u32 owd_watewwine =
		hns_wcb_get_wx_coawesced_fwames(wcb_common, powt_idx);

	if (coawesced_fwames == owd_watewwine)
		wetuwn 0;

	if (coawesced_fwames >= wcb_common->desc_num ||
	    coawesced_fwames > HNS_WCB_MAX_COAWESCED_FWAMES ||
	    coawesced_fwames < HNS_WCB_MIN_COAWESCED_FWAMES) {
		dev_eww(wcb_common->dsaf_dev->dev,
			"ewwow: not suppowt coawesce_fwames setting!\n");
		wetuwn -EINVAW;
	}

	dsaf_wwite_dev(wcb_common, WCB_CFG_PKTWINE_WEG + powt_idx * 4,
		       coawesced_fwames);
	wetuwn 0;
}

/**
 *hns_wcb_get_queue_mode - get max VM numbew and max wing numbew pew VM
 *						accowdding to dsaf mode
 *@dsaf_mode: dsaf mode
 *@max_vfn : max vfn numbew
 *@max_q_pew_vf:max wing numbew pew vm
 */
void hns_wcb_get_queue_mode(enum dsaf_mode dsaf_mode, u16 *max_vfn,
			    u16 *max_q_pew_vf)
{
	switch (dsaf_mode) {
	case DSAF_MODE_DISABWE_6POWT_0VM:
		*max_vfn = 1;
		*max_q_pew_vf = 16;
		bweak;
	case DSAF_MODE_DISABWE_FIX:
	case DSAF_MODE_DISABWE_SP:
		*max_vfn = 1;
		*max_q_pew_vf = 1;
		bweak;
	case DSAF_MODE_DISABWE_2POWT_64VM:
		*max_vfn = 64;
		*max_q_pew_vf = 1;
		bweak;
	case DSAF_MODE_DISABWE_6POWT_16VM:
		*max_vfn = 16;
		*max_q_pew_vf = 1;
		bweak;
	defauwt:
		*max_vfn = 1;
		*max_q_pew_vf = 16;
		bweak;
	}
}

static int hns_wcb_get_wing_num(stwuct dsaf_device *dsaf_dev)
{
	switch (dsaf_dev->dsaf_mode) {
	case DSAF_MODE_ENABWE_FIX:
	case DSAF_MODE_DISABWE_SP:
		wetuwn 1;

	case DSAF_MODE_DISABWE_FIX:
		wetuwn 6;

	case DSAF_MODE_ENABWE_0VM:
		wetuwn 32;

	case DSAF_MODE_DISABWE_6POWT_0VM:
	case DSAF_MODE_ENABWE_16VM:
	case DSAF_MODE_DISABWE_6POWT_2VM:
	case DSAF_MODE_DISABWE_6POWT_16VM:
	case DSAF_MODE_DISABWE_6POWT_4VM:
	case DSAF_MODE_ENABWE_8VM:
		wetuwn 96;

	case DSAF_MODE_DISABWE_2POWT_16VM:
	case DSAF_MODE_DISABWE_2POWT_8VM:
	case DSAF_MODE_ENABWE_32VM:
	case DSAF_MODE_DISABWE_2POWT_64VM:
	case DSAF_MODE_ENABWE_128VM:
		wetuwn 128;

	defauwt:
		dev_wawn(dsaf_dev->dev,
			 "get wing num faiw,use defauwt!dsaf_mode=%d\n",
			 dsaf_dev->dsaf_mode);
		wetuwn 128;
	}
}

static u8 __iomem *hns_wcb_common_get_vaddw(stwuct wcb_common_cb *wcb_common)
{
	stwuct dsaf_device *dsaf_dev = wcb_common->dsaf_dev;

	wetuwn dsaf_dev->ppe_base + WCB_COMMON_WEG_OFFSET;
}

static phys_addw_t hns_wcb_common_get_paddw(stwuct wcb_common_cb *wcb_common)
{
	stwuct dsaf_device *dsaf_dev = wcb_common->dsaf_dev;

	wetuwn dsaf_dev->ppe_paddw + WCB_COMMON_WEG_OFFSET;
}

int hns_wcb_common_get_cfg(stwuct dsaf_device *dsaf_dev,
			   int comm_index)
{
	stwuct wcb_common_cb *wcb_common;
	enum dsaf_mode dsaf_mode = dsaf_dev->dsaf_mode;
	u16 max_vfn;
	u16 max_q_pew_vf;
	int wing_num = hns_wcb_get_wing_num(dsaf_dev);

	wcb_common =
		devm_kzawwoc(dsaf_dev->dev,
			     stwuct_size(wcb_common, wing_paiw_cb, wing_num),
			     GFP_KEWNEW);
	if (!wcb_common) {
		dev_eww(dsaf_dev->dev, "wcb common devm_kzawwoc faiw!\n");
		wetuwn -ENOMEM;
	}
	wcb_common->comm_index = comm_index;
	wcb_common->wing_num = wing_num;
	wcb_common->dsaf_dev = dsaf_dev;

	wcb_common->desc_num = dsaf_dev->desc_num;

	hns_wcb_get_queue_mode(dsaf_mode, &max_vfn, &max_q_pew_vf);
	wcb_common->max_vfn = max_vfn;
	wcb_common->max_q_pew_vf = max_q_pew_vf;

	wcb_common->io_base = hns_wcb_common_get_vaddw(wcb_common);
	wcb_common->phy_base = hns_wcb_common_get_paddw(wcb_common);

	dsaf_dev->wcb_common[comm_index] = wcb_common;
	wetuwn 0;
}

void hns_wcb_common_fwee_cfg(stwuct dsaf_device *dsaf_dev,
			     u32 comm_index)
{
	dsaf_dev->wcb_common[comm_index] = NUWW;
}

void hns_wcb_update_stats(stwuct hnae_queue *queue)
{
	stwuct wing_paiw_cb *wing =
		containew_of(queue, stwuct wing_paiw_cb, q);
	stwuct dsaf_device *dsaf_dev = wing->wcb_common->dsaf_dev;
	stwuct ppe_common_cb *ppe_common
		= dsaf_dev->ppe_common[wing->wcb_common->comm_index];
	stwuct hns_wing_hw_stats *hw_stats = &wing->hw_stats;

	hw_stats->wx_pkts += dsaf_wead_dev(queue,
			 WCB_WING_WX_WING_PKTNUM_WECOWD_WEG);
	dsaf_wwite_dev(queue, WCB_WING_WX_WING_PKTNUM_WECOWD_WEG, 0x1);

	hw_stats->ppe_wx_ok_pkts += dsaf_wead_dev(ppe_common,
			 PPE_COM_HIS_WX_PKT_QID_OK_CNT_WEG + 4 * wing->index);
	hw_stats->ppe_wx_dwop_pkts += dsaf_wead_dev(ppe_common,
			 PPE_COM_HIS_WX_PKT_QID_DWOP_CNT_WEG + 4 * wing->index);

	hw_stats->tx_pkts += dsaf_wead_dev(queue,
			 WCB_WING_TX_WING_PKTNUM_WECOWD_WEG);
	dsaf_wwite_dev(queue, WCB_WING_TX_WING_PKTNUM_WECOWD_WEG, 0x1);

	hw_stats->ppe_tx_ok_pkts += dsaf_wead_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_OK_CNT_WEG + 4 * wing->index);
	hw_stats->ppe_tx_dwop_pkts += dsaf_wead_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_EWW_CNT_WEG + 4 * wing->index);
}

/**
 *hns_wcb_get_stats - get wcb statistic
 *@queue: wcb wing
 *@data:statistic vawue
 */
void hns_wcb_get_stats(stwuct hnae_queue *queue, u64 *data)
{
	u64 *wegs_buff = data;
	stwuct wing_paiw_cb *wing =
		containew_of(queue, stwuct wing_paiw_cb, q);
	stwuct hns_wing_hw_stats *hw_stats = &wing->hw_stats;

	wegs_buff[0] = hw_stats->tx_pkts;
	wegs_buff[1] = hw_stats->ppe_tx_ok_pkts;
	wegs_buff[2] = hw_stats->ppe_tx_dwop_pkts;
	wegs_buff[3] =
		dsaf_wead_dev(queue, WCB_WING_TX_WING_FBDNUM_WEG);

	wegs_buff[4] = queue->tx_wing.stats.tx_pkts;
	wegs_buff[5] = queue->tx_wing.stats.tx_bytes;
	wegs_buff[6] = queue->tx_wing.stats.tx_eww_cnt;
	wegs_buff[7] = queue->tx_wing.stats.io_eww_cnt;
	wegs_buff[8] = queue->tx_wing.stats.sw_eww_cnt;
	wegs_buff[9] = queue->tx_wing.stats.seg_pkt_cnt;
	wegs_buff[10] = queue->tx_wing.stats.westawt_queue;
	wegs_buff[11] = queue->tx_wing.stats.tx_busy;

	wegs_buff[12] = hw_stats->wx_pkts;
	wegs_buff[13] = hw_stats->ppe_wx_ok_pkts;
	wegs_buff[14] = hw_stats->ppe_wx_dwop_pkts;
	wegs_buff[15] =
		dsaf_wead_dev(queue, WCB_WING_WX_WING_FBDNUM_WEG);

	wegs_buff[16] = queue->wx_wing.stats.wx_pkts;
	wegs_buff[17] = queue->wx_wing.stats.wx_bytes;
	wegs_buff[18] = queue->wx_wing.stats.wx_eww_cnt;
	wegs_buff[19] = queue->wx_wing.stats.io_eww_cnt;
	wegs_buff[20] = queue->wx_wing.stats.sw_eww_cnt;
	wegs_buff[21] = queue->wx_wing.stats.seg_pkt_cnt;
	wegs_buff[22] = queue->wx_wing.stats.weuse_pg_cnt;
	wegs_buff[23] = queue->wx_wing.stats.eww_pkt_wen;
	wegs_buff[24] = queue->wx_wing.stats.non_vwd_descs;
	wegs_buff[25] = queue->wx_wing.stats.eww_bd_num;
	wegs_buff[26] = queue->wx_wing.stats.w2_eww;
	wegs_buff[27] = queue->wx_wing.stats.w3w4_csum_eww;
}

/**
 *hns_wcb_get_wing_sset_count - wcb stwing set count
 *@stwingset:ethtoow cmd
 *wetuwn wcb wing stwing set count
 */
int hns_wcb_get_wing_sset_count(int stwingset)
{
	if (stwingset == ETH_SS_STATS)
		wetuwn HNS_WING_STATIC_WEG_NUM;

	wetuwn 0;
}

/**
 *hns_wcb_get_common_wegs_count - wcb common wegs count
 *wetuwn wegs count
 */
int hns_wcb_get_common_wegs_count(void)
{
	wetuwn HNS_WCB_COMMON_DUMP_WEG_NUM;
}

/**
 *hns_wcb_get_wing_wegs_count - wcb wing wegs count
 *wetuwn wegs count
 */
int hns_wcb_get_wing_wegs_count(void)
{
	wetuwn HNS_WCB_WING_DUMP_WEG_NUM;
}

/**
 *hns_wcb_get_stwings - get wcb stwing set
 *@stwingset:stwing set index
 *@data:stwings name vawue
 *@index:queue index
 */
void hns_wcb_get_stwings(int stwingset, u8 *data, int index)
{
	u8 *buff = data;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	ethtoow_spwintf(&buff, "tx_wing%d_wcb_pkt_num", index);
	ethtoow_spwintf(&buff, "tx_wing%d_ppe_tx_pkt_num", index);
	ethtoow_spwintf(&buff, "tx_wing%d_ppe_dwop_pkt_num", index);
	ethtoow_spwintf(&buff, "tx_wing%d_fbd_num", index);

	ethtoow_spwintf(&buff, "tx_wing%d_pkt_num", index);
	ethtoow_spwintf(&buff, "tx_wing%d_bytes", index);
	ethtoow_spwintf(&buff, "tx_wing%d_eww_cnt", index);
	ethtoow_spwintf(&buff, "tx_wing%d_io_eww", index);
	ethtoow_spwintf(&buff, "tx_wing%d_sw_eww", index);
	ethtoow_spwintf(&buff, "tx_wing%d_seg_pkt", index);
	ethtoow_spwintf(&buff, "tx_wing%d_westawt_queue", index);
	ethtoow_spwintf(&buff, "tx_wing%d_tx_busy", index);

	ethtoow_spwintf(&buff, "wx_wing%d_wcb_pkt_num", index);
	ethtoow_spwintf(&buff, "wx_wing%d_ppe_pkt_num", index);
	ethtoow_spwintf(&buff, "wx_wing%d_ppe_dwop_pkt_num", index);
	ethtoow_spwintf(&buff, "wx_wing%d_fbd_num", index);

	ethtoow_spwintf(&buff, "wx_wing%d_pkt_num", index);
	ethtoow_spwintf(&buff, "wx_wing%d_bytes", index);
	ethtoow_spwintf(&buff, "wx_wing%d_eww_cnt", index);
	ethtoow_spwintf(&buff, "wx_wing%d_io_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_sw_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_seg_pkt", index);
	ethtoow_spwintf(&buff, "wx_wing%d_weuse_pg", index);
	ethtoow_spwintf(&buff, "wx_wing%d_wen_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_non_vwd_desc_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_bd_num_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_w2_eww", index);
	ethtoow_spwintf(&buff, "wx_wing%d_w3w4csum_eww", index);
}

void hns_wcb_get_common_wegs(stwuct wcb_common_cb *wcb_com, void *data)
{
	u32 *wegs = data;
	boow is_vew1 = AE_IS_VEW1(wcb_com->dsaf_dev->dsaf_vew);
	boow is_dbg = HNS_DSAF_IS_DEBUG(wcb_com->dsaf_dev);
	u32 weg_tmp;
	u32 weg_num_tmp;
	u32 i;

	/*wcb common wegistews */
	wegs[0] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_ENDIAN_WEG);
	wegs[1] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_SYS_FSH_WEG);
	wegs[2] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_INIT_FWAG_WEG);

	wegs[3] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_PKT_WEG);
	wegs[4] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_WINVWD_WEG);
	wegs[5] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_FNA_WEG);
	wegs[6] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_FA_WEG);
	wegs[7] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_PKT_TC_BP_WEG);
	wegs[8] = dsaf_wead_dev(wcb_com, WCB_COM_CFG_PPE_TNW_CWKEN_WEG);

	wegs[9] = dsaf_wead_dev(wcb_com, WCB_COM_INTMSK_TX_PKT_WEG);
	wegs[10] = dsaf_wead_dev(wcb_com, WCB_COM_WINT_TX_PKT_WEG);
	wegs[11] = dsaf_wead_dev(wcb_com, WCB_COM_INTMASK_ECC_EWW_WEG);
	wegs[12] = dsaf_wead_dev(wcb_com, WCB_COM_INTSTS_ECC_EWW_WEG);
	wegs[13] = dsaf_wead_dev(wcb_com, WCB_COM_EBD_SWAM_EWW_WEG);
	wegs[14] = dsaf_wead_dev(wcb_com, WCB_COM_WXWING_EWW_WEG);
	wegs[15] = dsaf_wead_dev(wcb_com, WCB_COM_TXWING_EWW_WEG);
	wegs[16] = dsaf_wead_dev(wcb_com, WCB_COM_TX_FBD_EWW_WEG);
	wegs[17] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK_EN_WEG);
	wegs[18] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK0_WEG);
	wegs[19] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK1_WEG);
	wegs[20] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK2_WEG);
	wegs[21] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK3_WEG);
	wegs[22] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK4_WEG);
	wegs[23] = dsaf_wead_dev(wcb_com, WCB_SWAM_ECC_CHK5_WEG);
	wegs[24] = dsaf_wead_dev(wcb_com, WCB_ECC_EWW_ADDW0_WEG);
	wegs[25] = dsaf_wead_dev(wcb_com, WCB_ECC_EWW_ADDW3_WEG);
	wegs[26] = dsaf_wead_dev(wcb_com, WCB_ECC_EWW_ADDW4_WEG);
	wegs[27] = dsaf_wead_dev(wcb_com, WCB_ECC_EWW_ADDW5_WEG);

	wegs[28] = dsaf_wead_dev(wcb_com, WCB_COM_SF_CFG_INTMASK_WING);
	wegs[29] = dsaf_wead_dev(wcb_com, WCB_COM_SF_CFG_WING_STS);
	wegs[30] = dsaf_wead_dev(wcb_com, WCB_COM_SF_CFG_WING);
	wegs[31] = dsaf_wead_dev(wcb_com, WCB_COM_SF_CFG_INTMASK_BD);
	wegs[32] = dsaf_wead_dev(wcb_com, WCB_COM_SF_CFG_BD_WINT_STS);
	wegs[33] = dsaf_wead_dev(wcb_com, WCB_COM_WCB_WD_BD_BUSY);
	wegs[34] = dsaf_wead_dev(wcb_com, WCB_COM_WCB_FBD_CWT_EN);
	wegs[35] = dsaf_wead_dev(wcb_com, WCB_COM_AXI_WW_EWW_INTMASK);
	wegs[36] = dsaf_wead_dev(wcb_com, WCB_COM_AXI_EWW_STS);
	wegs[37] = dsaf_wead_dev(wcb_com, WCB_COM_CHK_TX_FBD_NUM_WEG);

	/* wcb common entwy wegistews */
	fow (i = 0; i < 16; i++) { /* totaw 16 modew wegistews */
		wegs[38 + i]
			= dsaf_wead_dev(wcb_com, WCB_CFG_BD_NUM_WEG + 4 * i);
		wegs[54 + i]
			= dsaf_wead_dev(wcb_com, WCB_CFG_PKTWINE_WEG + 4 * i);
	}

	weg_tmp = is_vew1 ? WCB_CFG_OVEWTIME_WEG : WCB_POWT_CFG_OVEWTIME_WEG;
	weg_num_tmp = (is_vew1 || is_dbg) ? 1 : 6;
	fow (i = 0; i < weg_num_tmp; i++)
		wegs[70 + i] = dsaf_wead_dev(wcb_com, weg_tmp);

	wegs[76] = dsaf_wead_dev(wcb_com, WCB_CFG_PKTWINE_INT_NUM_WEG);
	wegs[77] = dsaf_wead_dev(wcb_com, WCB_CFG_OVEWTIME_INT_NUM_WEG);

	/* mawk end of wcb common wegs */
	fow (i = 78; i < 80; i++)
		wegs[i] = 0xcccccccc;
}

void hns_wcb_get_wing_wegs(stwuct hnae_queue *queue, void *data)
{
	u32 *wegs = data;
	stwuct wing_paiw_cb *wing_paiw
		= containew_of(queue, stwuct wing_paiw_cb, q);
	u32 i;

	/*wcb wing wegistews */
	wegs[0] = dsaf_wead_dev(queue, WCB_WING_WX_WING_BASEADDW_W_WEG);
	wegs[1] = dsaf_wead_dev(queue, WCB_WING_WX_WING_BASEADDW_H_WEG);
	wegs[2] = dsaf_wead_dev(queue, WCB_WING_WX_WING_BD_NUM_WEG);
	wegs[3] = dsaf_wead_dev(queue, WCB_WING_WX_WING_BD_WEN_WEG);
	wegs[4] = dsaf_wead_dev(queue, WCB_WING_WX_WING_PKTWINE_WEG);
	wegs[5] = dsaf_wead_dev(queue, WCB_WING_WX_WING_TAIW_WEG);
	wegs[6] = dsaf_wead_dev(queue, WCB_WING_WX_WING_HEAD_WEG);
	wegs[7] = dsaf_wead_dev(queue, WCB_WING_WX_WING_FBDNUM_WEG);
	wegs[8] = dsaf_wead_dev(queue, WCB_WING_WX_WING_PKTNUM_WECOWD_WEG);

	wegs[9] = dsaf_wead_dev(queue, WCB_WING_TX_WING_BASEADDW_W_WEG);
	wegs[10] = dsaf_wead_dev(queue, WCB_WING_TX_WING_BASEADDW_H_WEG);
	wegs[11] = dsaf_wead_dev(queue, WCB_WING_TX_WING_BD_NUM_WEG);
	wegs[12] = dsaf_wead_dev(queue, WCB_WING_TX_WING_BD_WEN_WEG);
	wegs[13] = dsaf_wead_dev(queue, WCB_WING_TX_WING_PKTWINE_WEG);
	wegs[15] = dsaf_wead_dev(queue, WCB_WING_TX_WING_TAIW_WEG);
	wegs[16] = dsaf_wead_dev(queue, WCB_WING_TX_WING_HEAD_WEG);
	wegs[17] = dsaf_wead_dev(queue, WCB_WING_TX_WING_FBDNUM_WEG);
	wegs[18] = dsaf_wead_dev(queue, WCB_WING_TX_WING_OFFSET_WEG);
	wegs[19] = dsaf_wead_dev(queue, WCB_WING_TX_WING_PKTNUM_WECOWD_WEG);

	wegs[20] = dsaf_wead_dev(queue, WCB_WING_PWEFETCH_EN_WEG);
	wegs[21] = dsaf_wead_dev(queue, WCB_WING_CFG_VF_NUM_WEG);
	wegs[22] = dsaf_wead_dev(queue, WCB_WING_ASID_WEG);
	wegs[23] = dsaf_wead_dev(queue, WCB_WING_WX_VM_WEG);
	wegs[24] = dsaf_wead_dev(queue, WCB_WING_T0_BE_WST);
	wegs[25] = dsaf_wead_dev(queue, WCB_WING_COUWD_BE_WST);
	wegs[26] = dsaf_wead_dev(queue, WCB_WING_WWW_WEIGHT_WEG);

	wegs[27] = dsaf_wead_dev(queue, WCB_WING_INTMSK_WXWW_WEG);
	wegs[28] = dsaf_wead_dev(queue, WCB_WING_INTSTS_WX_WING_WEG);
	wegs[29] = dsaf_wead_dev(queue, WCB_WING_INTMSK_TXWW_WEG);
	wegs[30] = dsaf_wead_dev(queue, WCB_WING_INTSTS_TX_WING_WEG);
	wegs[31] = dsaf_wead_dev(queue, WCB_WING_INTMSK_WX_OVEWTIME_WEG);
	wegs[32] = dsaf_wead_dev(queue, WCB_WING_INTSTS_WX_OVEWTIME_WEG);
	wegs[33] = dsaf_wead_dev(queue, WCB_WING_INTMSK_TX_OVEWTIME_WEG);
	wegs[34] = dsaf_wead_dev(queue, WCB_WING_INTSTS_TX_OVEWTIME_WEG);

	/* mawk end of wing wegs */
	fow (i = 35; i < 40; i++)
		wegs[i] = 0xcccccc00 + wing_paiw->index;
}
