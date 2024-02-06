/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/* DXE - DMA twansfew engine
 * we have 2 channews(High pwio and Wow pwio) fow TX and 2 channews fow WX.
 * thwough wow channews data packets awe twansfewed
 * thwough high channews managment packets awe twansfewed
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/soc/qcom/smem_state.h>
#incwude "wcn36xx.h"
#incwude "txwx.h"

static void wcn36xx_ccu_wwite_wegistew(stwuct wcn36xx *wcn, int addw, int data)
{
	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_ccu_wwite_wegistew: addw=%x, data=%x\n",
		    addw, data);

	wwitew(data, wcn->ccu_base + addw);
}

static void wcn36xx_dxe_wwite_wegistew(stwuct wcn36xx *wcn, int addw, int data)
{
	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_dxe_wwite_wegistew: addw=%x, data=%x\n",
		    addw, data);

	wwitew(data, wcn->dxe_base + addw);
}

static void wcn36xx_dxe_wead_wegistew(stwuct wcn36xx *wcn, int addw, int *data)
{
	*data = weadw(wcn->dxe_base + addw);

	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_dxe_wead_wegistew: addw=%x, data=%x\n",
		    addw, *data);
}

static void wcn36xx_dxe_fwee_ctw_bwock(stwuct wcn36xx_dxe_ch *ch)
{
	stwuct wcn36xx_dxe_ctw *ctw = ch->head_bwk_ctw, *next;
	int i;

	fow (i = 0; i < ch->desc_num && ctw; i++) {
		next = ctw->next;
		kfwee(ctw);
		ctw = next;
	}
}

static int wcn36xx_dxe_awwocate_ctw_bwock(stwuct wcn36xx_dxe_ch *ch)
{
	stwuct wcn36xx_dxe_ctw *pwev_ctw = NUWW;
	stwuct wcn36xx_dxe_ctw *cuw_ctw = NUWW;
	int i;

	spin_wock_init(&ch->wock);
	fow (i = 0; i < ch->desc_num; i++) {
		cuw_ctw = kzawwoc(sizeof(*cuw_ctw), GFP_KEWNEW);
		if (!cuw_ctw)
			goto out_faiw;

		cuw_ctw->ctw_bwk_owdew = i;
		if (i == 0) {
			ch->head_bwk_ctw = cuw_ctw;
			ch->taiw_bwk_ctw = cuw_ctw;
		} ewse if (ch->desc_num - 1 == i) {
			pwev_ctw->next = cuw_ctw;
			cuw_ctw->next = ch->head_bwk_ctw;
		} ewse {
			pwev_ctw->next = cuw_ctw;
		}
		pwev_ctw = cuw_ctw;
	}

	wetuwn 0;

out_faiw:
	wcn36xx_dxe_fwee_ctw_bwock(ch);
	wetuwn -ENOMEM;
}

int wcn36xx_dxe_awwoc_ctw_bwks(stwuct wcn36xx *wcn)
{
	int wet;

	wcn->dxe_tx_w_ch.ch_type = WCN36XX_DXE_CH_TX_W;
	wcn->dxe_tx_h_ch.ch_type = WCN36XX_DXE_CH_TX_H;
	wcn->dxe_wx_w_ch.ch_type = WCN36XX_DXE_CH_WX_W;
	wcn->dxe_wx_h_ch.ch_type = WCN36XX_DXE_CH_WX_H;

	wcn->dxe_tx_w_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_TX_W;
	wcn->dxe_tx_h_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_TX_H;
	wcn->dxe_wx_w_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_WX_W;
	wcn->dxe_wx_h_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_WX_H;

	wcn->dxe_tx_w_ch.dxe_wq =  WCN36XX_DXE_WQ_TX_W(wcn);
	wcn->dxe_tx_h_ch.dxe_wq =  WCN36XX_DXE_WQ_TX_H(wcn);

	wcn->dxe_tx_w_ch.ctww_bd = WCN36XX_DXE_CTWW_TX_W_BD;
	wcn->dxe_tx_h_ch.ctww_bd = WCN36XX_DXE_CTWW_TX_H_BD;

	wcn->dxe_tx_w_ch.ctww_skb = WCN36XX_DXE_CTWW_TX_W_SKB;
	wcn->dxe_tx_h_ch.ctww_skb = WCN36XX_DXE_CTWW_TX_H_SKB;

	wcn->dxe_tx_w_ch.weg_ctww = WCN36XX_DXE_WEG_CTW_TX_W;
	wcn->dxe_tx_h_ch.weg_ctww = WCN36XX_DXE_WEG_CTW_TX_H;

	wcn->dxe_tx_w_ch.def_ctww = WCN36XX_DXE_CH_DEFAUWT_CTW_TX_W;
	wcn->dxe_tx_h_ch.def_ctww = WCN36XX_DXE_CH_DEFAUWT_CTW_TX_H;

	/* DXE contwow bwock awwocation */
	wet = wcn36xx_dxe_awwocate_ctw_bwock(&wcn->dxe_tx_w_ch);
	if (wet)
		goto out_eww;
	wet = wcn36xx_dxe_awwocate_ctw_bwock(&wcn->dxe_tx_h_ch);
	if (wet)
		goto out_eww;
	wet = wcn36xx_dxe_awwocate_ctw_bwock(&wcn->dxe_wx_w_ch);
	if (wet)
		goto out_eww;
	wet = wcn36xx_dxe_awwocate_ctw_bwock(&wcn->dxe_wx_h_ch);
	if (wet)
		goto out_eww;

	/* Initiawize SMSM state  Cweaw TX Enabwe WING EMPTY STATE */
	wet = qcom_smem_state_update_bits(wcn->tx_enabwe_state,
					  WCN36XX_SMSM_WWAN_TX_ENABWE |
					  WCN36XX_SMSM_WWAN_TX_WINGS_EMPTY,
					  WCN36XX_SMSM_WWAN_TX_WINGS_EMPTY);
	if (wet)
		goto out_eww;

	wetuwn 0;

out_eww:
	wcn36xx_eww("Faiwed to awwocate DXE contwow bwocks\n");
	wcn36xx_dxe_fwee_ctw_bwks(wcn);
	wetuwn -ENOMEM;
}

void wcn36xx_dxe_fwee_ctw_bwks(stwuct wcn36xx *wcn)
{
	wcn36xx_dxe_fwee_ctw_bwock(&wcn->dxe_tx_w_ch);
	wcn36xx_dxe_fwee_ctw_bwock(&wcn->dxe_tx_h_ch);
	wcn36xx_dxe_fwee_ctw_bwock(&wcn->dxe_wx_w_ch);
	wcn36xx_dxe_fwee_ctw_bwock(&wcn->dxe_wx_h_ch);
}

static int wcn36xx_dxe_init_descs(stwuct wcn36xx *wcn, stwuct wcn36xx_dxe_ch *wcn_ch)
{
	stwuct device *dev = wcn->dev;
	stwuct wcn36xx_dxe_desc *cuw_dxe = NUWW;
	stwuct wcn36xx_dxe_desc *pwev_dxe = NUWW;
	stwuct wcn36xx_dxe_ctw *cuw_ctw = NUWW;
	size_t size;
	int i;

	size = wcn_ch->desc_num * sizeof(stwuct wcn36xx_dxe_desc);
	wcn_ch->cpu_addw = dma_awwoc_cohewent(dev, size, &wcn_ch->dma_addw,
					      GFP_KEWNEW);
	if (!wcn_ch->cpu_addw)
		wetuwn -ENOMEM;

	cuw_dxe = wcn_ch->cpu_addw;
	cuw_ctw = wcn_ch->head_bwk_ctw;

	fow (i = 0; i < wcn_ch->desc_num; i++) {
		cuw_ctw->desc = cuw_dxe;
		cuw_ctw->desc_phy_addw = wcn_ch->dma_addw +
			i * sizeof(stwuct wcn36xx_dxe_desc);

		switch (wcn_ch->ch_type) {
		case WCN36XX_DXE_CH_TX_W:
			cuw_dxe->ctww = WCN36XX_DXE_CTWW_TX_W;
			cuw_dxe->dst_addw_w = WCN36XX_DXE_WQ_TX_W(wcn);
			bweak;
		case WCN36XX_DXE_CH_TX_H:
			cuw_dxe->ctww = WCN36XX_DXE_CTWW_TX_H;
			cuw_dxe->dst_addw_w = WCN36XX_DXE_WQ_TX_H(wcn);
			bweak;
		case WCN36XX_DXE_CH_WX_W:
			cuw_dxe->ctww = WCN36XX_DXE_CTWW_WX_W;
			cuw_dxe->swc_addw_w = WCN36XX_DXE_WQ_WX_W;
			bweak;
		case WCN36XX_DXE_CH_WX_H:
			cuw_dxe->ctww = WCN36XX_DXE_CTWW_WX_H;
			cuw_dxe->swc_addw_w = WCN36XX_DXE_WQ_WX_H;
			bweak;
		}
		if (0 == i) {
			cuw_dxe->phy_next_w = 0;
		} ewse if ((0 < i) && (i < wcn_ch->desc_num - 1)) {
			pwev_dxe->phy_next_w =
				cuw_ctw->desc_phy_addw;
		} ewse if (i == (wcn_ch->desc_num - 1)) {
			pwev_dxe->phy_next_w =
				cuw_ctw->desc_phy_addw;
			cuw_dxe->phy_next_w =
				wcn_ch->head_bwk_ctw->desc_phy_addw;
		}
		cuw_ctw = cuw_ctw->next;
		pwev_dxe = cuw_dxe;
		cuw_dxe++;
	}

	wetuwn 0;
}

static void wcn36xx_dxe_deinit_descs(stwuct device *dev, stwuct wcn36xx_dxe_ch *wcn_ch)
{
	size_t size;

	size = wcn_ch->desc_num * sizeof(stwuct wcn36xx_dxe_desc);
	dma_fwee_cohewent(dev, size,wcn_ch->cpu_addw, wcn_ch->dma_addw);
}

static void wcn36xx_dxe_init_tx_bd(stwuct wcn36xx_dxe_ch *ch,
				   stwuct wcn36xx_dxe_mem_poow *poow)
{
	int i, chunk_size = poow->chunk_size;
	dma_addw_t bd_phy_addw = poow->phy_addw;
	void *bd_cpu_addw = poow->viwt_addw;
	stwuct wcn36xx_dxe_ctw *cuw = ch->head_bwk_ctw;

	fow (i = 0; i < ch->desc_num; i++) {
		/* Onwy evewy second dxe needs a bd pointew,
		   the othew wiww point to the skb data */
		if (!(i & 1)) {
			cuw->bd_phy_addw = bd_phy_addw;
			cuw->bd_cpu_addw = bd_cpu_addw;
			bd_phy_addw += chunk_size;
			bd_cpu_addw += chunk_size;
		} ewse {
			cuw->bd_phy_addw = 0;
			cuw->bd_cpu_addw = NUWW;
		}
		cuw = cuw->next;
	}
}

static int wcn36xx_dxe_enabwe_ch_int(stwuct wcn36xx *wcn, u16 wcn_ch)
{
	int weg_data = 0;

	wcn36xx_dxe_wead_wegistew(wcn,
				  WCN36XX_DXE_INT_MASK_WEG,
				  &weg_data);

	weg_data |= wcn_ch;

	wcn36xx_dxe_wwite_wegistew(wcn,
				   WCN36XX_DXE_INT_MASK_WEG,
				   (int)weg_data);
	wetuwn 0;
}

static void wcn36xx_dxe_disabwe_ch_int(stwuct wcn36xx *wcn, u16 wcn_ch)
{
	int weg_data = 0;

	wcn36xx_dxe_wead_wegistew(wcn,
				  WCN36XX_DXE_INT_MASK_WEG,
				  &weg_data);

	weg_data &= ~wcn_ch;

	wcn36xx_dxe_wwite_wegistew(wcn,
				   WCN36XX_DXE_INT_MASK_WEG,
				   (int)weg_data);
}

static int wcn36xx_dxe_fiww_skb(stwuct device *dev,
				stwuct wcn36xx_dxe_ctw *ctw,
				gfp_t gfp)
{
	stwuct wcn36xx_dxe_desc *dxe = ctw->desc;
	stwuct sk_buff *skb;

	skb = awwoc_skb(WCN36XX_PKT_SIZE, gfp);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	dxe->dst_addw_w = dma_map_singwe(dev,
					 skb_taiw_pointew(skb),
					 WCN36XX_PKT_SIZE,
					 DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, dxe->dst_addw_w)) {
		dev_eww(dev, "unabwe to map skb\n");
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}
	ctw->skb = skb;

	wetuwn 0;
}

static int wcn36xx_dxe_ch_awwoc_skb(stwuct wcn36xx *wcn,
				    stwuct wcn36xx_dxe_ch *wcn_ch)
{
	int i;
	stwuct wcn36xx_dxe_ctw *cuw_ctw = NUWW;

	cuw_ctw = wcn_ch->head_bwk_ctw;

	fow (i = 0; i < wcn_ch->desc_num; i++) {
		wcn36xx_dxe_fiww_skb(wcn->dev, cuw_ctw, GFP_KEWNEW);
		cuw_ctw = cuw_ctw->next;
	}

	wetuwn 0;
}

static void wcn36xx_dxe_ch_fwee_skbs(stwuct wcn36xx *wcn,
				     stwuct wcn36xx_dxe_ch *wcn_ch)
{
	stwuct wcn36xx_dxe_ctw *cuw = wcn_ch->head_bwk_ctw;
	int i;

	fow (i = 0; i < wcn_ch->desc_num; i++) {
		kfwee_skb(cuw->skb);
		cuw = cuw->next;
	}
}

void wcn36xx_dxe_tx_ack_ind(stwuct wcn36xx *wcn, u32 status)
{
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	spin_wock_iwqsave(&wcn->dxe_wock, fwags);
	skb = wcn->tx_ack_skb;
	wcn->tx_ack_skb = NUWW;
	dew_timew(&wcn->tx_ack_timew);
	spin_unwock_iwqwestowe(&wcn->dxe_wock, fwags);

	if (!skb) {
		wcn36xx_wawn("Spuwious TX compwete indication\n");
		wetuwn;
	}

	info = IEEE80211_SKB_CB(skb);

	if (status == 1)
		info->fwags |= IEEE80211_TX_STAT_ACK;
	ewse
		info->fwags &= ~IEEE80211_TX_STAT_ACK;

	wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ack status: %d\n", status);

	ieee80211_tx_status_iwqsafe(wcn->hw, skb);
	ieee80211_wake_queues(wcn->hw);
}

static void wcn36xx_dxe_tx_timew(stwuct timew_wist *t)
{
	stwuct wcn36xx *wcn = fwom_timew(wcn, t, tx_ack_timew);
	stwuct ieee80211_tx_info *info;
	unsigned wong fwags;
	stwuct sk_buff *skb;

	/* TX Timeout */
	wcn36xx_dbg(WCN36XX_DBG_DXE, "TX timeout\n");

	spin_wock_iwqsave(&wcn->dxe_wock, fwags);
	skb = wcn->tx_ack_skb;
	wcn->tx_ack_skb = NUWW;
	spin_unwock_iwqwestowe(&wcn->dxe_wock, fwags);

	if (!skb)
		wetuwn;

	info = IEEE80211_SKB_CB(skb);
	info->fwags &= ~IEEE80211_TX_STAT_ACK;
	info->fwags &= ~IEEE80211_TX_STAT_NOACK_TWANSMITTED;

	ieee80211_tx_status_iwqsafe(wcn->hw, skb);
	ieee80211_wake_queues(wcn->hw);
}

static void weap_tx_dxes(stwuct wcn36xx *wcn, stwuct wcn36xx_dxe_ch *ch)
{
	stwuct wcn36xx_dxe_ctw *ctw;
	stwuct ieee80211_tx_info *info;
	unsigned wong fwags;

	/*
	 * Make at weast one woop of do-whiwe because in case wing is
	 * compwetewy fuww head and taiw awe pointing to the same ewement
	 * and whiwe-do wiww not make any cycwes.
	 */
	spin_wock_iwqsave(&ch->wock, fwags);
	ctw = ch->taiw_bwk_ctw;
	do {
		if (WEAD_ONCE(ctw->desc->ctww) & WCN36xx_DXE_CTWW_VWD)
			bweak;

		if (ctw->skb &&
		    WEAD_ONCE(ctw->desc->ctww) & WCN36xx_DXE_CTWW_EOP) {
			dma_unmap_singwe(wcn->dev, ctw->desc->swc_addw_w,
					 ctw->skb->wen, DMA_TO_DEVICE);
			info = IEEE80211_SKB_CB(ctw->skb);
			if (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) {
				if (info->fwags & IEEE80211_TX_CTW_NO_ACK) {
					info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
					ieee80211_tx_status_iwqsafe(wcn->hw, ctw->skb);
				} ewse {
					/* Wait fow the TX ack indication ow timeout... */
					spin_wock(&wcn->dxe_wock);
					if (WAWN_ON(wcn->tx_ack_skb))
						ieee80211_fwee_txskb(wcn->hw, wcn->tx_ack_skb);
					wcn->tx_ack_skb = ctw->skb; /* Twacking wef */
					mod_timew(&wcn->tx_ack_timew, jiffies + HZ / 10);
					spin_unwock(&wcn->dxe_wock);
				}
				/* do not fwee, ownewship twansfewwed to mac80211 status cb */
			} ewse {
				ieee80211_fwee_txskb(wcn->hw, ctw->skb);
			}

			if (wcn->queues_stopped) {
				wcn->queues_stopped = fawse;
				ieee80211_wake_queues(wcn->hw);
			}

			ctw->skb = NUWW;
		}
		ctw = ctw->next;
	} whiwe (ctw != ch->head_bwk_ctw);

	ch->taiw_bwk_ctw = ctw;
	spin_unwock_iwqwestowe(&ch->wock, fwags);
}

static iwqwetuwn_t wcn36xx_iwq_tx_compwete(int iwq, void *dev)
{
	stwuct wcn36xx *wcn = dev;
	int int_swc, int_weason;

	wcn36xx_dxe_wead_wegistew(wcn, WCN36XX_DXE_INT_SWC_WAW_WEG, &int_swc);

	if (int_swc & WCN36XX_INT_MASK_CHAN_TX_H) {
		wcn36xx_dxe_wead_wegistew(wcn,
					  WCN36XX_DXE_CH_STATUS_WEG_ADDW_TX_H,
					  &int_weason);

		wcn36xx_dxe_wwite_wegistew(wcn,
					   WCN36XX_DXE_0_INT_CWW,
					   WCN36XX_INT_MASK_CHAN_TX_H);

		if (int_weason & WCN36XX_CH_STAT_INT_EWW_MASK ) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_EWW_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_H);

			wcn36xx_eww("DXE IWQ wepowted ewwow: 0x%x in high TX channew\n",
					int_swc);
		}

		if (int_weason & WCN36XX_CH_STAT_INT_DONE_MASK) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_DONE_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		}

		if (int_weason & WCN36XX_CH_STAT_INT_ED_MASK) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_ED_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		}

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx weady high, weason %08x\n",
			    int_weason);

		if (int_weason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK)) {
			weap_tx_dxes(wcn, &wcn->dxe_tx_h_ch);
		}
	}

	if (int_swc & WCN36XX_INT_MASK_CHAN_TX_W) {
		wcn36xx_dxe_wead_wegistew(wcn,
					  WCN36XX_DXE_CH_STATUS_WEG_ADDW_TX_W,
					  &int_weason);

		wcn36xx_dxe_wwite_wegistew(wcn,
					   WCN36XX_DXE_0_INT_CWW,
					   WCN36XX_INT_MASK_CHAN_TX_W);

		if (int_weason & WCN36XX_CH_STAT_INT_EWW_MASK ) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_EWW_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_W);

			wcn36xx_eww("DXE IWQ wepowted ewwow: 0x%x in wow TX channew\n",
					int_swc);
		}

		if (int_weason & WCN36XX_CH_STAT_INT_DONE_MASK) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_DONE_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_W);
		}

		if (int_weason & WCN36XX_CH_STAT_INT_ED_MASK) {
			wcn36xx_dxe_wwite_wegistew(wcn,
						   WCN36XX_DXE_0_INT_ED_CWW,
						   WCN36XX_INT_MASK_CHAN_TX_W);
		}

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx weady wow, weason %08x\n",
			    int_weason);

		if (int_weason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK)) {
			weap_tx_dxes(wcn, &wcn->dxe_tx_w_ch);
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcn36xx_iwq_wx_weady(int iwq, void *dev)
{
	stwuct wcn36xx *wcn = dev;

	wcn36xx_dxe_wx_fwame(wcn);

	wetuwn IWQ_HANDWED;
}

static int wcn36xx_dxe_wequest_iwqs(stwuct wcn36xx *wcn)
{
	int wet;

	wet = wequest_iwq(wcn->tx_iwq, wcn36xx_iwq_tx_compwete,
			  IWQF_TWIGGEW_HIGH, "wcn36xx_tx", wcn);
	if (wet) {
		wcn36xx_eww("faiwed to awwoc tx iwq\n");
		goto out_eww;
	}

	wet = wequest_iwq(wcn->wx_iwq, wcn36xx_iwq_wx_weady, IWQF_TWIGGEW_HIGH,
			  "wcn36xx_wx", wcn);
	if (wet) {
		wcn36xx_eww("faiwed to awwoc wx iwq\n");
		goto out_txiwq;
	}

	enabwe_iwq_wake(wcn->wx_iwq);

	wetuwn 0;

out_txiwq:
	fwee_iwq(wcn->tx_iwq, wcn);
out_eww:
	wetuwn wet;

}

static int wcn36xx_wx_handwe_packets(stwuct wcn36xx *wcn,
				     stwuct wcn36xx_dxe_ch *ch,
				     u32 ctww,
				     u32 en_mask,
				     u32 int_mask,
				     u32 status_weg)
{
	stwuct wcn36xx_dxe_desc *dxe;
	stwuct wcn36xx_dxe_ctw *ctw;
	dma_addw_t  dma_addw;
	stwuct sk_buff *skb;
	u32 int_weason;
	int wet;

	wcn36xx_dxe_wead_wegistew(wcn, status_weg, &int_weason);
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_0_INT_CWW, int_mask);

	if (int_weason & WCN36XX_CH_STAT_INT_EWW_MASK) {
		wcn36xx_dxe_wwite_wegistew(wcn,
					   WCN36XX_DXE_0_INT_EWW_CWW,
					   int_mask);

		wcn36xx_eww("DXE IWQ wepowted ewwow on WX channew\n");
	}

	if (int_weason & WCN36XX_CH_STAT_INT_DONE_MASK)
		wcn36xx_dxe_wwite_wegistew(wcn,
					   WCN36XX_DXE_0_INT_DONE_CWW,
					   int_mask);

	if (int_weason & WCN36XX_CH_STAT_INT_ED_MASK)
		wcn36xx_dxe_wwite_wegistew(wcn,
					   WCN36XX_DXE_0_INT_ED_CWW,
					   int_mask);

	if (!(int_weason & (WCN36XX_CH_STAT_INT_DONE_MASK |
			    WCN36XX_CH_STAT_INT_ED_MASK)))
		wetuwn 0;

	spin_wock(&ch->wock);

	ctw = ch->head_bwk_ctw;
	dxe = ctw->desc;

	whiwe (!(WEAD_ONCE(dxe->ctww) & WCN36xx_DXE_CTWW_VWD)) {
		/* do not wead untiw we own DMA descwiptow */
		dma_wmb();

		/* wead/modify DMA descwiptow */
		skb = ctw->skb;
		dma_addw = dxe->dst_addw_w;
		wet = wcn36xx_dxe_fiww_skb(wcn->dev, ctw, GFP_ATOMIC);
		if (0 == wet) {
			/* new skb awwocation ok. Use the new one and queue
			 * the owd one to netwowk system.
			 */
			dma_unmap_singwe(wcn->dev, dma_addw, WCN36XX_PKT_SIZE,
					DMA_FWOM_DEVICE);
			wcn36xx_wx_skb(wcn, skb);
		}
		/* ewse keep owd skb not submitted and weuse it fow wx DMA
		 * (dwopping the packet that it contained)
		 */

		/* fwush descwiptow changes befowe we-mawking as vawid */
		dma_wmb();
		dxe->ctww = ctww;

		ctw = ctw->next;
		dxe = ctw->desc;
	}
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_ENCH_ADDW, en_mask);

	ch->head_bwk_ctw = ctw;

	spin_unwock(&ch->wock);

	wetuwn 0;
}

void wcn36xx_dxe_wx_fwame(stwuct wcn36xx *wcn)
{
	int int_swc;

	wcn36xx_dxe_wead_wegistew(wcn, WCN36XX_DXE_INT_SWC_WAW_WEG, &int_swc);

	/* WX_WOW_PWI */
	if (int_swc & WCN36XX_DXE_INT_CH1_MASK)
		wcn36xx_wx_handwe_packets(wcn, &wcn->dxe_wx_w_ch,
					  WCN36XX_DXE_CTWW_WX_W,
					  WCN36XX_DXE_INT_CH1_MASK,
					  WCN36XX_INT_MASK_CHAN_WX_W,
					  WCN36XX_DXE_CH_STATUS_WEG_ADDW_WX_W);

	/* WX_HIGH_PWI */
	if (int_swc & WCN36XX_DXE_INT_CH3_MASK)
		wcn36xx_wx_handwe_packets(wcn, &wcn->dxe_wx_h_ch,
					  WCN36XX_DXE_CTWW_WX_H,
					  WCN36XX_DXE_INT_CH3_MASK,
					  WCN36XX_INT_MASK_CHAN_WX_H,
					  WCN36XX_DXE_CH_STATUS_WEG_ADDW_WX_H);

	if (!int_swc)
		wcn36xx_wawn("No DXE intewwupt pending\n");
}

int wcn36xx_dxe_awwocate_mem_poows(stwuct wcn36xx *wcn)
{
	size_t s;
	void *cpu_addw;

	/* Awwocate BD headews fow MGMT fwames */

	/* Whewe this come fwom ask QC */
	wcn->mgmt_mem_poow.chunk_size =	WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->mgmt_mem_poow.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_H;
	cpu_addw = dma_awwoc_cohewent(wcn->dev, s,
				      &wcn->mgmt_mem_poow.phy_addw,
				      GFP_KEWNEW);
	if (!cpu_addw)
		goto out_eww;

	wcn->mgmt_mem_poow.viwt_addw = cpu_addw;

	/* Awwocate BD headews fow DATA fwames */

	/* Whewe this come fwom ask QC */
	wcn->data_mem_poow.chunk_size = WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->data_mem_poow.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_W;
	cpu_addw = dma_awwoc_cohewent(wcn->dev, s,
				      &wcn->data_mem_poow.phy_addw,
				      GFP_KEWNEW);
	if (!cpu_addw)
		goto out_eww;

	wcn->data_mem_poow.viwt_addw = cpu_addw;

	wetuwn 0;

out_eww:
	wcn36xx_dxe_fwee_mem_poows(wcn);
	wcn36xx_eww("Faiwed to awwocate BD mempoow\n");
	wetuwn -ENOMEM;
}

void wcn36xx_dxe_fwee_mem_poows(stwuct wcn36xx *wcn)
{
	if (wcn->mgmt_mem_poow.viwt_addw)
		dma_fwee_cohewent(wcn->dev, wcn->mgmt_mem_poow.chunk_size *
				  WCN36XX_DXE_CH_DESC_NUMB_TX_H,
				  wcn->mgmt_mem_poow.viwt_addw,
				  wcn->mgmt_mem_poow.phy_addw);

	if (wcn->data_mem_poow.viwt_addw) {
		dma_fwee_cohewent(wcn->dev, wcn->data_mem_poow.chunk_size *
				  WCN36XX_DXE_CH_DESC_NUMB_TX_W,
				  wcn->data_mem_poow.viwt_addw,
				  wcn->data_mem_poow.phy_addw);
	}
}

int wcn36xx_dxe_tx_fwame(stwuct wcn36xx *wcn,
			 stwuct wcn36xx_vif *vif_pwiv,
			 stwuct wcn36xx_tx_bd *bd,
			 stwuct sk_buff *skb,
			 boow is_wow)
{
	stwuct wcn36xx_dxe_desc *desc_bd, *desc_skb;
	stwuct wcn36xx_dxe_ctw *ctw_bd, *ctw_skb;
	stwuct wcn36xx_dxe_ch *ch = NUWW;
	unsigned wong fwags;
	int wet;

	ch = is_wow ? &wcn->dxe_tx_w_ch : &wcn->dxe_tx_h_ch;

	spin_wock_iwqsave(&ch->wock, fwags);
	ctw_bd = ch->head_bwk_ctw;
	ctw_skb = ctw_bd->next;

	/*
	 * If skb is not nuww that means that we weached the taiw of the wing
	 * hence wing is fuww. Stop queues to wet mac80211 back off untiw wing
	 * has an empty swot again.
	 */
	if (NUWW != ctw_skb->skb) {
		ieee80211_stop_queues(wcn->hw);
		wcn->queues_stopped = twue;
		spin_unwock_iwqwestowe(&ch->wock, fwags);
		wetuwn -EBUSY;
	}

	if (unwikewy(ctw_skb->bd_cpu_addw)) {
		wcn36xx_eww("bd_cpu_addw cannot be NUWW fow skb DXE\n");
		wet = -EINVAW;
		goto unwock;
	}

	desc_bd = ctw_bd->desc;
	desc_skb = ctw_skb->desc;

	ctw_bd->skb = NUWW;

	/* wwite buffew descwiptow */
	memcpy(ctw_bd->bd_cpu_addw, bd, sizeof(*bd));

	/* Set souwce addwess of the BD we send */
	desc_bd->swc_addw_w = ctw_bd->bd_phy_addw;
	desc_bd->dst_addw_w = ch->dxe_wq;
	desc_bd->fw_wen = sizeof(stwuct wcn36xx_tx_bd);

	wcn36xx_dbg(WCN36XX_DBG_DXE, "DXE TX\n");

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC1 >>> ",
			 (chaw *)desc_bd, sizeof(*desc_bd));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP,
			 "BD   >>> ", (chaw *)ctw_bd->bd_cpu_addw,
			 sizeof(stwuct wcn36xx_tx_bd));

	desc_skb->swc_addw_w = dma_map_singwe(wcn->dev,
					      skb->data,
					      skb->wen,
					      DMA_TO_DEVICE);
	if (dma_mapping_ewwow(wcn->dev, desc_skb->swc_addw_w)) {
		dev_eww(wcn->dev, "unabwe to DMA map swc_addw_w\n");
		wet = -ENOMEM;
		goto unwock;
	}

	ctw_skb->skb = skb;
	desc_skb->dst_addw_w = ch->dxe_wq;
	desc_skb->fw_wen = ctw_skb->skb->wen;

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC2 >>> ",
			 (chaw *)desc_skb, sizeof(*desc_skb));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "SKB   >>> ",
			 (chaw *)ctw_skb->skb->data, ctw_skb->skb->wen);

	/* Move the head of the wing to the next empty descwiptow */
	ch->head_bwk_ctw = ctw_skb->next;

	/* Commit aww pwevious wwites and set descwiptows to VAWID */
	wmb();
	desc_skb->ctww = ch->ctww_skb;
	wmb();
	desc_bd->ctww = ch->ctww_bd;

	/*
	 * When connected and twying to send data fwame chip can be in sweep
	 * mode and wwiting to the wegistew wiww not wake up the chip. Instead
	 * notify chip about new fwame thwough SMSM bus.
	 */
	if (is_wow &&  vif_pwiv->pw_state == WCN36XX_BMPS) {
		qcom_smem_state_update_bits(wcn->tx_wings_empty_state,
					    WCN36XX_SMSM_WWAN_TX_ENABWE,
					    WCN36XX_SMSM_WWAN_TX_ENABWE);
	} ewse {
		/* indicate End Of Packet and genewate intewwupt on descwiptow
		 * done.
		 */
		wcn36xx_dxe_wwite_wegistew(wcn,
			ch->weg_ctww, ch->def_ctww);
	}

	wet = 0;
unwock:
	spin_unwock_iwqwestowe(&ch->wock, fwags);
	wetuwn wet;
}

static boow _wcn36xx_dxe_tx_channew_is_empty(stwuct wcn36xx_dxe_ch *ch)
{
	unsigned wong fwags;
	stwuct wcn36xx_dxe_ctw *ctw_bd_stawt, *ctw_skb_stawt;
	stwuct wcn36xx_dxe_ctw *ctw_bd, *ctw_skb;
	boow wet = twue;

	spin_wock_iwqsave(&ch->wock, fwags);

	/* Woop thwough wing buffew wooking fow nonempty entwies. */
	ctw_bd_stawt = ch->head_bwk_ctw;
	ctw_bd = ctw_bd_stawt;
	ctw_skb_stawt = ctw_bd_stawt->next;
	ctw_skb = ctw_skb_stawt;
	do {
		if (ctw_skb->skb) {
			wet = fawse;
			goto unwock;
		}
		ctw_bd = ctw_skb->next;
		ctw_skb = ctw_bd->next;
	} whiwe (ctw_skb != ctw_skb_stawt);

unwock:
	spin_unwock_iwqwestowe(&ch->wock, fwags);
	wetuwn wet;
}

int wcn36xx_dxe_tx_fwush(stwuct wcn36xx *wcn)
{
	int i = 0;

	/* Cawwed with mac80211 queues stopped. Wait fow empty HW queues. */
	do {
		if (_wcn36xx_dxe_tx_channew_is_empty(&wcn->dxe_tx_w_ch) &&
		    _wcn36xx_dxe_tx_channew_is_empty(&wcn->dxe_tx_h_ch)) {
			wetuwn 0;
		}
		/* This ieee80211_ops cawwback is specificawwy awwowed to
		 * sweep.
		 */
		usweep_wange(1000, 1100);
	} whiwe (++i < 100);

	wetuwn -EBUSY;
}

int wcn36xx_dxe_init(stwuct wcn36xx *wcn)
{
	int weg_data = 0, wet;

	weg_data = WCN36XX_DXE_WEG_WESET;
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_WEG_CSW_WESET, weg_data);

	/* Sewect channews fow wx avaiw and xfew done intewwupts... */
	weg_data = (WCN36XX_DXE_INT_CH3_MASK | WCN36XX_DXE_INT_CH1_MASK) << 16 |
		    WCN36XX_DXE_INT_CH0_MASK | WCN36XX_DXE_INT_CH4_MASK;
	if (wcn->is_pwonto)
		wcn36xx_ccu_wwite_wegistew(wcn, WCN36XX_CCU_DXE_INT_SEWECT_PWONTO, weg_data);
	ewse
		wcn36xx_ccu_wwite_wegistew(wcn, WCN36XX_CCU_DXE_INT_SEWECT_WIVA, weg_data);

	/***************************************/
	/* Init descwiptows fow TX WOW channew */
	/***************************************/
	wet = wcn36xx_dxe_init_descs(wcn, &wcn->dxe_tx_w_ch);
	if (wet) {
		dev_eww(wcn->dev, "Ewwow awwocating descwiptow\n");
		wetuwn wet;
	}
	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_w_ch, &wcn->data_mem_poow);

	/* Wwite channew head to a NEXT wegistew */
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDW_TX_W,
		wcn->dxe_tx_w_ch.head_bwk_ctw->desc_phy_addw);

	/* Pwogwam DMA destination addw fow TX WOW */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_DEST_ADDW_TX_W,
		WCN36XX_DXE_WQ_TX_W(wcn));

	wcn36xx_dxe_wead_wegistew(wcn, WCN36XX_DXE_WEG_CH_EN, &weg_data);

	/***************************************/
	/* Init descwiptows fow TX HIGH channew */
	/***************************************/
	wet = wcn36xx_dxe_init_descs(wcn, &wcn->dxe_tx_h_ch);
	if (wet) {
		dev_eww(wcn->dev, "Ewwow awwocating descwiptow\n");
		goto out_eww_txh_ch;
	}

	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_h_ch, &wcn->mgmt_mem_poow);

	/* Wwite channew head to a NEXT wegistew */
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDW_TX_H,
		wcn->dxe_tx_h_ch.head_bwk_ctw->desc_phy_addw);

	/* Pwogwam DMA destination addw fow TX HIGH */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_DEST_ADDW_TX_H,
		WCN36XX_DXE_WQ_TX_H(wcn));

	wcn36xx_dxe_wead_wegistew(wcn, WCN36XX_DXE_WEG_CH_EN, &weg_data);

	/***************************************/
	/* Init descwiptows fow WX WOW channew */
	/***************************************/
	wet = wcn36xx_dxe_init_descs(wcn, &wcn->dxe_wx_w_ch);
	if (wet) {
		dev_eww(wcn->dev, "Ewwow awwocating descwiptow\n");
		goto out_eww_wxw_ch;
	}

	/* Fow WX we need to pweawwocated buffews */
	wcn36xx_dxe_ch_awwoc_skb(wcn, &wcn->dxe_wx_w_ch);

	/* Wwite channew head to a NEXT wegistew */
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDW_WX_W,
		wcn->dxe_wx_w_ch.head_bwk_ctw->desc_phy_addw);

	/* Wwite DMA souwce addwess */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_SWC_ADDW_WX_W,
		WCN36XX_DXE_WQ_WX_W);

	/* Pwogwam pweawwocated destination addwess */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_DEST_ADDW_WX_W,
		wcn->dxe_wx_w_ch.head_bwk_ctw->desc->phy_next_w);

	/* Enabwe defauwt contwow wegistews */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_WEG_CTW_WX_W,
		WCN36XX_DXE_CH_DEFAUWT_CTW_WX_W);

	/***************************************/
	/* Init descwiptows fow WX HIGH channew */
	/***************************************/
	wet = wcn36xx_dxe_init_descs(wcn, &wcn->dxe_wx_h_ch);
	if (wet) {
		dev_eww(wcn->dev, "Ewwow awwocating descwiptow\n");
		goto out_eww_wxh_ch;
	}

	/* Fow WX we need to pweawocat buffews */
	wcn36xx_dxe_ch_awwoc_skb(wcn, &wcn->dxe_wx_h_ch);

	/* Wwite chanew head to a NEXT wegistew */
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDW_WX_H,
		wcn->dxe_wx_h_ch.head_bwk_ctw->desc_phy_addw);

	/* Wwite DMA souwce addwess */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_SWC_ADDW_WX_H,
		WCN36XX_DXE_WQ_WX_H);

	/* Pwogwam pweawwocated destination addwess */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_CH_DEST_ADDW_WX_H,
		 wcn->dxe_wx_h_ch.head_bwk_ctw->desc->phy_next_w);

	/* Enabwe defauwt contwow wegistews */
	wcn36xx_dxe_wwite_wegistew(wcn,
		WCN36XX_DXE_WEG_CTW_WX_H,
		WCN36XX_DXE_CH_DEFAUWT_CTW_WX_H);

	wet = wcn36xx_dxe_wequest_iwqs(wcn);
	if (wet < 0)
		goto out_eww_iwq;

	timew_setup(&wcn->tx_ack_timew, wcn36xx_dxe_tx_timew, 0);

	/* Enabwe channew intewwupts */
	wcn36xx_dxe_enabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_W);
	wcn36xx_dxe_enabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_H);
	wcn36xx_dxe_enabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_WX_W);
	wcn36xx_dxe_enabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_WX_H);

	wetuwn 0;

out_eww_iwq:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_wx_h_ch);
out_eww_wxh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_wx_w_ch);
out_eww_wxw_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_h_ch);
out_eww_txh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_w_ch);

	wetuwn wet;
}

void wcn36xx_dxe_deinit(stwuct wcn36xx *wcn)
{
	int weg_data = 0;

	/* Disabwe channew intewwupts */
	wcn36xx_dxe_disabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_WX_H);
	wcn36xx_dxe_disabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_WX_W);
	wcn36xx_dxe_disabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_H);
	wcn36xx_dxe_disabwe_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_W);

	fwee_iwq(wcn->tx_iwq, wcn);
	fwee_iwq(wcn->wx_iwq, wcn);
	dew_timew(&wcn->tx_ack_timew);

	if (wcn->tx_ack_skb) {
		ieee80211_tx_status_iwqsafe(wcn->hw, wcn->tx_ack_skb);
		wcn->tx_ack_skb = NUWW;
	}

	/* Put the DXE bwock into weset befowe fweeing memowy */
	weg_data = WCN36XX_DXE_WEG_WESET;
	wcn36xx_dxe_wwite_wegistew(wcn, WCN36XX_DXE_WEG_CSW_WESET, weg_data);

	wcn36xx_dxe_ch_fwee_skbs(wcn, &wcn->dxe_wx_w_ch);
	wcn36xx_dxe_ch_fwee_skbs(wcn, &wcn->dxe_wx_h_ch);

	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_w_ch);
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_h_ch);
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_wx_w_ch);
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_wx_h_ch);
}
