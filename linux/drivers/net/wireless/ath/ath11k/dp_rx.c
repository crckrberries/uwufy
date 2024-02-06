// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/ieee80211.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <cwypto/hash.h>
#incwude "cowe.h"
#incwude "debug.h"
#incwude "debugfs_htt_stats.h"
#incwude "debugfs_sta.h"
#incwude "haw_desc.h"
#incwude "hw.h"
#incwude "dp_wx.h"
#incwude "haw_wx.h"
#incwude "dp_tx.h"
#incwude "peew.h"

#define ATH11K_DP_WX_FWAGMENT_TIMEOUT_MS (2 * HZ)

static inwine
u8 *ath11k_dp_wx_h_80211_hdw(stwuct ath11k_base *ab, stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_hdw_status(desc);
}

static inwine
enum haw_encwypt_type ath11k_dp_wx_h_mpdu_stawt_enctype(stwuct ath11k_base *ab,
							stwuct haw_wx_desc *desc)
{
	if (!ab->hw_pawams.hw_ops->wx_desc_encwypt_vawid(desc))
		wetuwn HAW_ENCWYPT_TYPE_OPEN;

	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_encwypt_type(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_decap_type(stwuct ath11k_base *ab,
						      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_decap_type(desc);
}

static inwine
boow ath11k_dp_wx_h_msdu_stawt_wdpc_suppowt(stwuct ath11k_base *ab,
					    stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_wdpc_suppowt(desc);
}

static inwine
u8 ath11k_dp_wx_h_msdu_stawt_mesh_ctw_pwesent(stwuct ath11k_base *ab,
					      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mesh_ctw(desc);
}

static inwine
boow ath11k_dp_wx_h_mpdu_stawt_seq_ctww_vawid(stwuct ath11k_base *ab,
					      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_seq_ctw_vwd(desc);
}

static inwine boow ath11k_dp_wx_h_mpdu_stawt_fc_vawid(stwuct ath11k_base *ab,
						      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_fc_vawid(desc);
}

static inwine boow ath11k_dp_wx_h_mpdu_stawt_mowe_fwags(stwuct ath11k_base *ab,
							stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)(skb->data + ab->hw_pawams.haw_desc_sz);
	wetuwn ieee80211_has_mowefwags(hdw->fwame_contwow);
}

static inwine u16 ath11k_dp_wx_h_mpdu_stawt_fwag_no(stwuct ath11k_base *ab,
						    stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)(skb->data + ab->hw_pawams.haw_desc_sz);
	wetuwn we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_FWAG;
}

static inwine u16 ath11k_dp_wx_h_mpdu_stawt_seq_no(stwuct ath11k_base *ab,
						   stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_stawt_seq_no(desc);
}

static inwine void *ath11k_dp_wx_get_attention(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_attention(desc);
}

static inwine boow ath11k_dp_wx_h_attn_msdu_done(stwuct wx_attention *attn)
{
	wetuwn !!FIEWD_GET(WX_ATTENTION_INFO2_MSDU_DONE,
			   __we32_to_cpu(attn->info2));
}

static inwine boow ath11k_dp_wx_h_attn_w4_cksum_faiw(stwuct wx_attention *attn)
{
	wetuwn !!FIEWD_GET(WX_ATTENTION_INFO1_TCP_UDP_CKSUM_FAIW,
			   __we32_to_cpu(attn->info1));
}

static inwine boow ath11k_dp_wx_h_attn_ip_cksum_faiw(stwuct wx_attention *attn)
{
	wetuwn !!FIEWD_GET(WX_ATTENTION_INFO1_IP_CKSUM_FAIW,
			   __we32_to_cpu(attn->info1));
}

static inwine boow ath11k_dp_wx_h_attn_is_decwypted(stwuct wx_attention *attn)
{
	wetuwn (FIEWD_GET(WX_ATTENTION_INFO2_DCWYPT_STATUS_CODE,
			  __we32_to_cpu(attn->info2)) ==
		WX_DESC_DECWYPT_STATUS_CODE_OK);
}

static u32 ath11k_dp_wx_h_attn_mpdu_eww(stwuct wx_attention *attn)
{
	u32 info = __we32_to_cpu(attn->info1);
	u32 ewwmap = 0;

	if (info & WX_ATTENTION_INFO1_FCS_EWW)
		ewwmap |= DP_WX_MPDU_EWW_FCS;

	if (info & WX_ATTENTION_INFO1_DECWYPT_EWW)
		ewwmap |= DP_WX_MPDU_EWW_DECWYPT;

	if (info & WX_ATTENTION_INFO1_TKIP_MIC_EWW)
		ewwmap |= DP_WX_MPDU_EWW_TKIP_MIC;

	if (info & WX_ATTENTION_INFO1_A_MSDU_EWWOW)
		ewwmap |= DP_WX_MPDU_EWW_AMSDU_EWW;

	if (info & WX_ATTENTION_INFO1_OVEWFWOW_EWW)
		ewwmap |= DP_WX_MPDU_EWW_OVEWFWOW;

	if (info & WX_ATTENTION_INFO1_MSDU_WEN_EWW)
		ewwmap |= DP_WX_MPDU_EWW_MSDU_WEN;

	if (info & WX_ATTENTION_INFO1_MPDU_WEN_EWW)
		ewwmap |= DP_WX_MPDU_EWW_MPDU_WEN;

	wetuwn ewwmap;
}

static boow ath11k_dp_wx_h_attn_msdu_wen_eww(stwuct ath11k_base *ab,
					     stwuct haw_wx_desc *desc)
{
	stwuct wx_attention *wx_attention;
	u32 ewwmap;

	wx_attention = ath11k_dp_wx_get_attention(ab, desc);
	ewwmap = ath11k_dp_wx_h_attn_mpdu_eww(wx_attention);

	wetuwn ewwmap & DP_WX_MPDU_EWW_MSDU_WEN;
}

static inwine u16 ath11k_dp_wx_h_msdu_stawt_msdu_wen(stwuct ath11k_base *ab,
						     stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_wen(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_sgi(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_sgi(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_wate_mcs(stwuct ath11k_base *ab,
						    stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_wate_mcs(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_wx_bw(stwuct ath11k_base *ab,
						 stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_wx_bw(desc);
}

static inwine u32 ath11k_dp_wx_h_msdu_stawt_fweq(stwuct ath11k_base *ab,
						 stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_fweq(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_pkt_type(stwuct ath11k_base *ab,
						    stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_msdu_pkt_type(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_stawt_nss(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *desc)
{
	wetuwn hweight8(ab->hw_pawams.hw_ops->wx_desc_get_msdu_nss(desc));
}

static inwine u8 ath11k_dp_wx_h_mpdu_stawt_tid(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_tid(desc);
}

static inwine u16 ath11k_dp_wx_h_mpdu_stawt_peew_id(stwuct ath11k_base *ab,
						    stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_peew_id(desc);
}

static inwine u8 ath11k_dp_wx_h_msdu_end_w3pad(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_w3_pad_bytes(desc);
}

static inwine boow ath11k_dp_wx_h_msdu_end_fiwst_msdu(stwuct ath11k_base *ab,
						      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_fiwst_msdu(desc);
}

static boow ath11k_dp_wx_h_msdu_end_wast_msdu(stwuct ath11k_base *ab,
					      stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_wast_msdu(desc);
}

static void ath11k_dp_wx_desc_end_twv_copy(stwuct ath11k_base *ab,
					   stwuct haw_wx_desc *fdesc,
					   stwuct haw_wx_desc *wdesc)
{
	ab->hw_pawams.hw_ops->wx_desc_copy_attn_end_twv(fdesc, wdesc);
}

static inwine u32 ath11k_dp_wxdesc_get_mpduwen_eww(stwuct wx_attention *attn)
{
	wetuwn FIEWD_GET(WX_ATTENTION_INFO1_MPDU_WEN_EWW,
			 __we32_to_cpu(attn->info1));
}

static inwine u8 *ath11k_dp_wxdesc_get_80211hdw(stwuct ath11k_base *ab,
						stwuct haw_wx_desc *wx_desc)
{
	u8 *wx_pkt_hdw;

	wx_pkt_hdw = ab->hw_pawams.hw_ops->wx_desc_get_msdu_paywoad(wx_desc);

	wetuwn wx_pkt_hdw;
}

static inwine boow ath11k_dp_wxdesc_mpdu_vawid(stwuct ath11k_base *ab,
					       stwuct haw_wx_desc *wx_desc)
{
	u32 twv_tag;

	twv_tag = ab->hw_pawams.hw_ops->wx_desc_get_mpdu_stawt_tag(wx_desc);

	wetuwn twv_tag == HAW_WX_MPDU_STAWT;
}

static inwine u32 ath11k_dp_wxdesc_get_ppduid(stwuct ath11k_base *ab,
					      stwuct haw_wx_desc *wx_desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_get_mpdu_ppdu_id(wx_desc);
}

static inwine void ath11k_dp_wxdesc_set_msdu_wen(stwuct ath11k_base *ab,
						 stwuct haw_wx_desc *desc,
						 u16 wen)
{
	ab->hw_pawams.hw_ops->wx_desc_set_msdu_wen(desc, wen);
}

static boow ath11k_dp_wx_h_attn_is_mcbc(stwuct ath11k_base *ab,
					stwuct haw_wx_desc *desc)
{
	stwuct wx_attention *attn = ath11k_dp_wx_get_attention(ab, desc);

	wetuwn ath11k_dp_wx_h_msdu_end_fiwst_msdu(ab, desc) &&
		(!!FIEWD_GET(WX_ATTENTION_INFO1_MCAST_BCAST,
		 __we32_to_cpu(attn->info1)));
}

static boow ath11k_dp_wxdesc_mac_addw2_vawid(stwuct ath11k_base *ab,
					     stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_mac_addw2_vawid(desc);
}

static u8 *ath11k_dp_wxdesc_mpdu_stawt_addw2(stwuct ath11k_base *ab,
					     stwuct haw_wx_desc *desc)
{
	wetuwn ab->hw_pawams.hw_ops->wx_desc_mpdu_stawt_addw2(desc);
}

static void ath11k_dp_sewvice_mon_wing(stwuct timew_wist *t)
{
	stwuct ath11k_base *ab = fwom_timew(ab, t, mon_weap_timew);
	int i;

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++)
		ath11k_dp_wx_pwocess_mon_wings(ab, i, NUWW, DP_MON_SEWVICE_BUDGET);

	mod_timew(&ab->mon_weap_timew, jiffies +
		  msecs_to_jiffies(ATH11K_MON_TIMEW_INTEWVAW));
}

static int ath11k_dp_puwge_mon_wing(stwuct ath11k_base *ab)
{
	int i, weaped = 0;
	unsigned wong timeout = jiffies + msecs_to_jiffies(DP_MON_PUWGE_TIMEOUT_MS);

	do {
		fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++)
			weaped += ath11k_dp_wx_pwocess_mon_wings(ab, i,
								 NUWW,
								 DP_MON_SEWVICE_BUDGET);

		/* nothing mowe to weap */
		if (weaped < DP_MON_SEWVICE_BUDGET)
			wetuwn 0;

	} whiwe (time_befowe(jiffies, timeout));

	ath11k_wawn(ab, "dp mon wing puwge timeout");

	wetuwn -ETIMEDOUT;
}

/* Wetuwns numbew of Wx buffews wepwenished */
int ath11k_dp_wxbufs_wepwenish(stwuct ath11k_base *ab, int mac_id,
			       stwuct dp_wxdma_wing *wx_wing,
			       int weq_entwies,
			       enum haw_wx_buf_wetuwn_buf_managew mgw)
{
	stwuct haw_swng *swng;
	u32 *desc;
	stwuct sk_buff *skb;
	int num_fwee;
	int num_wemain;
	int buf_id;
	u32 cookie;
	dma_addw_t paddw;

	weq_entwies = min(weq_entwies, wx_wing->bufs_max);

	swng = &ab->haw.swng_wist[wx_wing->wefiww_buf_wing.wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	num_fwee = ath11k_haw_swng_swc_num_fwee(ab, swng, twue);
	if (!weq_entwies && (num_fwee > (wx_wing->bufs_max * 3) / 4))
		weq_entwies = num_fwee;

	weq_entwies = min(num_fwee, weq_entwies);
	num_wemain = weq_entwies;

	whiwe (num_wemain > 0) {
		skb = dev_awwoc_skb(DP_WX_BUFFEW_SIZE +
				    DP_WX_BUFFEW_AWIGN_SIZE);
		if (!skb)
			bweak;

		if (!IS_AWIGNED((unsigned wong)skb->data,
				DP_WX_BUFFEW_AWIGN_SIZE)) {
			skb_puww(skb,
				 PTW_AWIGN(skb->data, DP_WX_BUFFEW_AWIGN_SIZE) -
				 skb->data);
		}

		paddw = dma_map_singwe(ab->dev, skb->data,
				       skb->wen + skb_taiwwoom(skb),
				       DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(ab->dev, paddw))
			goto faiw_fwee_skb;

		spin_wock_bh(&wx_wing->idw_wock);
		buf_id = idw_awwoc(&wx_wing->bufs_idw, skb, 1,
				   (wx_wing->bufs_max * 3) + 1, GFP_ATOMIC);
		spin_unwock_bh(&wx_wing->idw_wock);
		if (buf_id <= 0)
			goto faiw_dma_unmap;

		desc = ath11k_haw_swng_swc_get_next_entwy(ab, swng);
		if (!desc)
			goto faiw_idw_wemove;

		ATH11K_SKB_WXCB(skb)->paddw = paddw;

		cookie = FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_BUF_ID, buf_id);

		num_wemain--;

		ath11k_haw_wx_buf_addw_info_set(desc, paddw, cookie, mgw);
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn weq_entwies - num_wemain;

faiw_idw_wemove:
	spin_wock_bh(&wx_wing->idw_wock);
	idw_wemove(&wx_wing->bufs_idw, buf_id);
	spin_unwock_bh(&wx_wing->idw_wock);
faiw_dma_unmap:
	dma_unmap_singwe(ab->dev, paddw, skb->wen + skb_taiwwoom(skb),
			 DMA_FWOM_DEVICE);
faiw_fwee_skb:
	dev_kfwee_skb_any(skb);

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn weq_entwies - num_wemain;
}

static int ath11k_dp_wxdma_buf_wing_fwee(stwuct ath11k *aw,
					 stwuct dp_wxdma_wing *wx_wing)
{
	stwuct sk_buff *skb;
	int buf_id;

	spin_wock_bh(&wx_wing->idw_wock);
	idw_fow_each_entwy(&wx_wing->bufs_idw, skb, buf_id) {
		idw_wemove(&wx_wing->bufs_idw, buf_id);
		/* TODO: Undewstand whewe intewnaw dwivew does this dma_unmap
		 * of wxdma_buffew.
		 */
		dma_unmap_singwe(aw->ab->dev, ATH11K_SKB_WXCB(skb)->paddw,
				 skb->wen + skb_taiwwoom(skb), DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
	}

	idw_destwoy(&wx_wing->bufs_idw);
	spin_unwock_bh(&wx_wing->idw_wock);

	wetuwn 0;
}

static int ath11k_dp_wxdma_pdev_buf_fwee(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_base *ab = aw->ab;
	stwuct dp_wxdma_wing *wx_wing = &dp->wx_wefiww_buf_wing;
	int i;

	ath11k_dp_wxdma_buf_wing_fwee(aw, wx_wing);

	wx_wing = &dp->wxdma_mon_buf_wing;
	ath11k_dp_wxdma_buf_wing_fwee(aw, wx_wing);

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wx_wing = &dp->wx_mon_status_wefiww_wing[i];
		ath11k_dp_wxdma_buf_wing_fwee(aw, wx_wing);
	}

	wetuwn 0;
}

static int ath11k_dp_wxdma_wing_buf_setup(stwuct ath11k *aw,
					  stwuct dp_wxdma_wing *wx_wing,
					  u32 wingtype)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	int num_entwies;

	num_entwies = wx_wing->wefiww_buf_wing.size /
		ath11k_haw_swng_get_entwysize(aw->ab, wingtype);

	wx_wing->bufs_max = num_entwies;
	ath11k_dp_wxbufs_wepwenish(aw->ab, dp->mac_id, wx_wing, num_entwies,
				   aw->ab->hw_pawams.haw_pawams->wx_buf_wbm);
	wetuwn 0;
}

static int ath11k_dp_wxdma_pdev_buf_setup(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_base *ab = aw->ab;
	stwuct dp_wxdma_wing *wx_wing = &dp->wx_wefiww_buf_wing;
	int i;

	ath11k_dp_wxdma_wing_buf_setup(aw, wx_wing, HAW_WXDMA_BUF);

	if (aw->ab->hw_pawams.wxdma1_enabwe) {
		wx_wing = &dp->wxdma_mon_buf_wing;
		ath11k_dp_wxdma_wing_buf_setup(aw, wx_wing, HAW_WXDMA_MONITOW_BUF);
	}

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wx_wing = &dp->wx_mon_status_wefiww_wing[i];
		ath11k_dp_wxdma_wing_buf_setup(aw, wx_wing, HAW_WXDMA_MONITOW_STATUS);
	}

	wetuwn 0;
}

static void ath11k_dp_wx_pdev_swng_fwee(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_base *ab = aw->ab;
	int i;

	ath11k_dp_swng_cweanup(ab, &dp->wx_wefiww_buf_wing.wefiww_buf_wing);

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		if (ab->hw_pawams.wx_mac_buf_wing)
			ath11k_dp_swng_cweanup(ab, &dp->wx_mac_buf_wing[i]);

		ath11k_dp_swng_cweanup(ab, &dp->wxdma_eww_dst_wing[i]);
		ath11k_dp_swng_cweanup(ab,
				       &dp->wx_mon_status_wefiww_wing[i].wefiww_buf_wing);
	}

	ath11k_dp_swng_cweanup(ab, &dp->wxdma_mon_buf_wing.wefiww_buf_wing);
}

void ath11k_dp_pdev_weo_cweanup(stwuct ath11k_base *ab)
{
	stwuct ath11k_dp *dp = &ab->dp;
	int i;

	fow (i = 0; i < DP_WEO_DST_WING_MAX; i++)
		ath11k_dp_swng_cweanup(ab, &dp->weo_dst_wing[i]);
}

int ath11k_dp_pdev_weo_setup(stwuct ath11k_base *ab)
{
	stwuct ath11k_dp *dp = &ab->dp;
	int wet;
	int i;

	fow (i = 0; i < DP_WEO_DST_WING_MAX; i++) {
		wet = ath11k_dp_swng_setup(ab, &dp->weo_dst_wing[i],
					   HAW_WEO_DST, i, 0,
					   DP_WEO_DST_WING_SIZE);
		if (wet) {
			ath11k_wawn(ab, "faiwed to setup weo_dst_wing\n");
			goto eww_weo_cweanup;
		}
	}

	wetuwn 0;

eww_weo_cweanup:
	ath11k_dp_pdev_weo_cweanup(ab);

	wetuwn wet;
}

static int ath11k_dp_wx_pdev_swng_awwoc(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_base *ab = aw->ab;
	stwuct dp_swng *swng = NUWW;
	int i;
	int wet;

	wet = ath11k_dp_swng_setup(aw->ab,
				   &dp->wx_wefiww_buf_wing.wefiww_buf_wing,
				   HAW_WXDMA_BUF, 0,
				   dp->mac_id, DP_WXDMA_BUF_WING_SIZE);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup wx_wefiww_buf_wing\n");
		wetuwn wet;
	}

	if (aw->ab->hw_pawams.wx_mac_buf_wing) {
		fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
			wet = ath11k_dp_swng_setup(aw->ab,
						   &dp->wx_mac_buf_wing[i],
						   HAW_WXDMA_BUF, 1,
						   dp->mac_id + i, 1024);
			if (wet) {
				ath11k_wawn(aw->ab, "faiwed to setup wx_mac_buf_wing %d\n",
					    i);
				wetuwn wet;
			}
		}
	}

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wet = ath11k_dp_swng_setup(aw->ab, &dp->wxdma_eww_dst_wing[i],
					   HAW_WXDMA_DST, 0, dp->mac_id + i,
					   DP_WXDMA_EWW_DST_WING_SIZE);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to setup wxdma_eww_dst_wing %d\n", i);
			wetuwn wet;
		}
	}

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		swng = &dp->wx_mon_status_wefiww_wing[i].wefiww_buf_wing;
		wet = ath11k_dp_swng_setup(aw->ab,
					   swng,
					   HAW_WXDMA_MONITOW_STATUS, 0, dp->mac_id + i,
					   DP_WXDMA_MON_STATUS_WING_SIZE);
		if (wet) {
			ath11k_wawn(aw->ab,
				    "faiwed to setup wx_mon_status_wefiww_wing %d\n", i);
			wetuwn wet;
		}
	}

	/* if wxdma1_enabwe is fawse, then it doesn't need
	 * to setup wxdam_mon_buf_wing, wxdma_mon_dst_wing
	 * and wxdma_mon_desc_wing.
	 * init weap timew fow QCA6390.
	 */
	if (!aw->ab->hw_pawams.wxdma1_enabwe) {
		//init mon status buffew weap timew
		timew_setup(&aw->ab->mon_weap_timew,
			    ath11k_dp_sewvice_mon_wing, 0);
		wetuwn 0;
	}

	wet = ath11k_dp_swng_setup(aw->ab,
				   &dp->wxdma_mon_buf_wing.wefiww_buf_wing,
				   HAW_WXDMA_MONITOW_BUF, 0, dp->mac_id,
				   DP_WXDMA_MONITOW_BUF_WING_SIZE);
	if (wet) {
		ath11k_wawn(aw->ab,
			    "faiwed to setup HAW_WXDMA_MONITOW_BUF\n");
		wetuwn wet;
	}

	wet = ath11k_dp_swng_setup(aw->ab, &dp->wxdma_mon_dst_wing,
				   HAW_WXDMA_MONITOW_DST, 0, dp->mac_id,
				   DP_WXDMA_MONITOW_DST_WING_SIZE);
	if (wet) {
		ath11k_wawn(aw->ab,
			    "faiwed to setup HAW_WXDMA_MONITOW_DST\n");
		wetuwn wet;
	}

	wet = ath11k_dp_swng_setup(aw->ab, &dp->wxdma_mon_desc_wing,
				   HAW_WXDMA_MONITOW_DESC, 0, dp->mac_id,
				   DP_WXDMA_MONITOW_DESC_WING_SIZE);
	if (wet) {
		ath11k_wawn(aw->ab,
			    "faiwed to setup HAW_WXDMA_MONITOW_DESC\n");
		wetuwn wet;
	}

	wetuwn 0;
}

void ath11k_dp_weo_cmd_wist_cweanup(stwuct ath11k_base *ab)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct dp_weo_cmd *cmd, *tmp;
	stwuct dp_weo_cache_fwush_ewem *cmd_cache, *tmp_cache;
	stwuct dp_wx_tid *wx_tid;

	spin_wock_bh(&dp->weo_cmd_wock);
	wist_fow_each_entwy_safe(cmd, tmp, &dp->weo_cmd_wist, wist) {
		wist_dew(&cmd->wist);
		wx_tid = &cmd->data;
		if (wx_tid->vaddw) {
			dma_unmap_singwe(ab->dev, wx_tid->paddw,
					 wx_tid->size, DMA_BIDIWECTIONAW);
			kfwee(wx_tid->vaddw);
			wx_tid->vaddw = NUWW;
		}
		kfwee(cmd);
	}

	wist_fow_each_entwy_safe(cmd_cache, tmp_cache,
				 &dp->weo_cmd_cache_fwush_wist, wist) {
		wist_dew(&cmd_cache->wist);
		dp->weo_cmd_cache_fwush_count--;
		wx_tid = &cmd_cache->data;
		if (wx_tid->vaddw) {
			dma_unmap_singwe(ab->dev, wx_tid->paddw,
					 wx_tid->size, DMA_BIDIWECTIONAW);
			kfwee(wx_tid->vaddw);
			wx_tid->vaddw = NUWW;
		}
		kfwee(cmd_cache);
	}
	spin_unwock_bh(&dp->weo_cmd_wock);
}

static void ath11k_dp_weo_cmd_fwee(stwuct ath11k_dp *dp, void *ctx,
				   enum haw_weo_cmd_status status)
{
	stwuct dp_wx_tid *wx_tid = ctx;

	if (status != HAW_WEO_CMD_SUCCESS)
		ath11k_wawn(dp->ab, "faiwed to fwush wx tid hw desc, tid %d status %d\n",
			    wx_tid->tid, status);
	if (wx_tid->vaddw) {
		dma_unmap_singwe(dp->ab->dev, wx_tid->paddw, wx_tid->size,
				 DMA_BIDIWECTIONAW);
		kfwee(wx_tid->vaddw);
		wx_tid->vaddw = NUWW;
	}
}

static void ath11k_dp_weo_cache_fwush(stwuct ath11k_base *ab,
				      stwuct dp_wx_tid *wx_tid)
{
	stwuct ath11k_haw_weo_cmd cmd = {0};
	unsigned wong tot_desc_sz, desc_sz;
	int wet;

	tot_desc_sz = wx_tid->size;
	desc_sz = ath11k_haw_weo_qdesc_size(0, HAW_DESC_WEO_NON_QOS_TID);

	whiwe (tot_desc_sz > desc_sz) {
		tot_desc_sz -= desc_sz;
		cmd.addw_wo = wowew_32_bits(wx_tid->paddw + tot_desc_sz);
		cmd.addw_hi = uppew_32_bits(wx_tid->paddw);
		wet = ath11k_dp_tx_send_weo_cmd(ab, wx_tid,
						HAW_WEO_CMD_FWUSH_CACHE, &cmd,
						NUWW);
		if (wet)
			ath11k_wawn(ab,
				    "faiwed to send HAW_WEO_CMD_FWUSH_CACHE, tid %d (%d)\n",
				    wx_tid->tid, wet);
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.addw_wo = wowew_32_bits(wx_tid->paddw);
	cmd.addw_hi = uppew_32_bits(wx_tid->paddw);
	cmd.fwag |= HAW_WEO_CMD_FWG_NEED_STATUS;
	wet = ath11k_dp_tx_send_weo_cmd(ab, wx_tid,
					HAW_WEO_CMD_FWUSH_CACHE,
					&cmd, ath11k_dp_weo_cmd_fwee);
	if (wet) {
		ath11k_eww(ab, "faiwed to send HAW_WEO_CMD_FWUSH_CACHE cmd, tid %d (%d)\n",
			   wx_tid->tid, wet);
		dma_unmap_singwe(ab->dev, wx_tid->paddw, wx_tid->size,
				 DMA_BIDIWECTIONAW);
		kfwee(wx_tid->vaddw);
		wx_tid->vaddw = NUWW;
	}
}

static void ath11k_dp_wx_tid_dew_func(stwuct ath11k_dp *dp, void *ctx,
				      enum haw_weo_cmd_status status)
{
	stwuct ath11k_base *ab = dp->ab;
	stwuct dp_wx_tid *wx_tid = ctx;
	stwuct dp_weo_cache_fwush_ewem *ewem, *tmp;

	if (status == HAW_WEO_CMD_DWAIN) {
		goto fwee_desc;
	} ewse if (status != HAW_WEO_CMD_SUCCESS) {
		/* Shouwdn't happen! Cweanup in case of othew faiwuwe? */
		ath11k_wawn(ab, "faiwed to dewete wx tid %d hw descwiptow %d\n",
			    wx_tid->tid, status);
		wetuwn;
	}

	ewem = kzawwoc(sizeof(*ewem), GFP_ATOMIC);
	if (!ewem)
		goto fwee_desc;

	ewem->ts = jiffies;
	memcpy(&ewem->data, wx_tid, sizeof(*wx_tid));

	spin_wock_bh(&dp->weo_cmd_wock);
	wist_add_taiw(&ewem->wist, &dp->weo_cmd_cache_fwush_wist);
	dp->weo_cmd_cache_fwush_count++;

	/* Fwush and invawidate aged WEO desc fwom HW cache */
	wist_fow_each_entwy_safe(ewem, tmp, &dp->weo_cmd_cache_fwush_wist,
				 wist) {
		if (dp->weo_cmd_cache_fwush_count > DP_WEO_DESC_FWEE_THWESHOWD ||
		    time_aftew(jiffies, ewem->ts +
			       msecs_to_jiffies(DP_WEO_DESC_FWEE_TIMEOUT_MS))) {
			wist_dew(&ewem->wist);
			dp->weo_cmd_cache_fwush_count--;
			spin_unwock_bh(&dp->weo_cmd_wock);

			ath11k_dp_weo_cache_fwush(ab, &ewem->data);
			kfwee(ewem);
			spin_wock_bh(&dp->weo_cmd_wock);
		}
	}
	spin_unwock_bh(&dp->weo_cmd_wock);

	wetuwn;
fwee_desc:
	dma_unmap_singwe(ab->dev, wx_tid->paddw, wx_tid->size,
			 DMA_BIDIWECTIONAW);
	kfwee(wx_tid->vaddw);
	wx_tid->vaddw = NUWW;
}

void ath11k_peew_wx_tid_dewete(stwuct ath11k *aw,
			       stwuct ath11k_peew *peew, u8 tid)
{
	stwuct ath11k_haw_weo_cmd cmd = {0};
	stwuct dp_wx_tid *wx_tid = &peew->wx_tid[tid];
	int wet;

	if (!wx_tid->active)
		wetuwn;

	wx_tid->active = fawse;

	cmd.fwag = HAW_WEO_CMD_FWG_NEED_STATUS;
	cmd.addw_wo = wowew_32_bits(wx_tid->paddw);
	cmd.addw_hi = uppew_32_bits(wx_tid->paddw);
	cmd.upd0 |= HAW_WEO_CMD_UPD0_VWD;
	wet = ath11k_dp_tx_send_weo_cmd(aw->ab, wx_tid,
					HAW_WEO_CMD_UPDATE_WX_QUEUE, &cmd,
					ath11k_dp_wx_tid_dew_func);
	if (wet) {
		if (wet != -ESHUTDOWN)
			ath11k_eww(aw->ab, "faiwed to send HAW_WEO_CMD_UPDATE_WX_QUEUE cmd, tid %d (%d)\n",
				   tid, wet);
		dma_unmap_singwe(aw->ab->dev, wx_tid->paddw, wx_tid->size,
				 DMA_BIDIWECTIONAW);
		kfwee(wx_tid->vaddw);
		wx_tid->vaddw = NUWW;
	}

	wx_tid->paddw = 0;
	wx_tid->size = 0;
}

static int ath11k_dp_wx_wink_desc_wetuwn(stwuct ath11k_base *ab,
					 u32 *wink_desc,
					 enum haw_wbm_wew_bm_act action)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct haw_swng *swng;
	u32 *desc;
	int wet = 0;

	swng = &ab->haw.swng_wist[dp->wbm_desc_wew_wing.wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	desc = ath11k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!desc) {
		wet = -ENOBUFS;
		goto exit;
	}

	ath11k_haw_wx_msdu_wink_desc_set(ab, (void *)desc, (void *)wink_desc,
					 action);

exit:
	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn wet;
}

static void ath11k_dp_wx_fwags_cweanup(stwuct dp_wx_tid *wx_tid, boow wew_wink_desc)
{
	stwuct ath11k_base *ab = wx_tid->ab;

	wockdep_assewt_hewd(&ab->base_wock);

	if (wx_tid->dst_wing_desc) {
		if (wew_wink_desc)
			ath11k_dp_wx_wink_desc_wetuwn(ab, (u32 *)wx_tid->dst_wing_desc,
						      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
		kfwee(wx_tid->dst_wing_desc);
		wx_tid->dst_wing_desc = NUWW;
	}

	wx_tid->cuw_sn = 0;
	wx_tid->wast_fwag_no = 0;
	wx_tid->wx_fwag_bitmap = 0;
	__skb_queue_puwge(&wx_tid->wx_fwags);
}

void ath11k_peew_fwags_fwush(stwuct ath11k *aw, stwuct ath11k_peew *peew)
{
	stwuct dp_wx_tid *wx_tid;
	int i;

	wockdep_assewt_hewd(&aw->ab->base_wock);

	fow (i = 0; i <= IEEE80211_NUM_TIDS; i++) {
		wx_tid = &peew->wx_tid[i];

		spin_unwock_bh(&aw->ab->base_wock);
		dew_timew_sync(&wx_tid->fwag_timew);
		spin_wock_bh(&aw->ab->base_wock);

		ath11k_dp_wx_fwags_cweanup(wx_tid, twue);
	}
}

void ath11k_peew_wx_tid_cweanup(stwuct ath11k *aw, stwuct ath11k_peew *peew)
{
	stwuct dp_wx_tid *wx_tid;
	int i;

	wockdep_assewt_hewd(&aw->ab->base_wock);

	fow (i = 0; i <= IEEE80211_NUM_TIDS; i++) {
		wx_tid = &peew->wx_tid[i];

		ath11k_peew_wx_tid_dewete(aw, peew, i);
		ath11k_dp_wx_fwags_cweanup(wx_tid, twue);

		spin_unwock_bh(&aw->ab->base_wock);
		dew_timew_sync(&wx_tid->fwag_timew);
		spin_wock_bh(&aw->ab->base_wock);
	}
}

static int ath11k_peew_wx_tid_weo_update(stwuct ath11k *aw,
					 stwuct ath11k_peew *peew,
					 stwuct dp_wx_tid *wx_tid,
					 u32 ba_win_sz, u16 ssn,
					 boow update_ssn)
{
	stwuct ath11k_haw_weo_cmd cmd = {0};
	int wet;

	cmd.addw_wo = wowew_32_bits(wx_tid->paddw);
	cmd.addw_hi = uppew_32_bits(wx_tid->paddw);
	cmd.fwag = HAW_WEO_CMD_FWG_NEED_STATUS;
	cmd.upd0 = HAW_WEO_CMD_UPD0_BA_WINDOW_SIZE;
	cmd.ba_window_size = ba_win_sz;

	if (update_ssn) {
		cmd.upd0 |= HAW_WEO_CMD_UPD0_SSN;
		cmd.upd2 = FIEWD_PWEP(HAW_WEO_CMD_UPD2_SSN, ssn);
	}

	wet = ath11k_dp_tx_send_weo_cmd(aw->ab, wx_tid,
					HAW_WEO_CMD_UPDATE_WX_QUEUE, &cmd,
					NUWW);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to update wx tid queue, tid %d (%d)\n",
			    wx_tid->tid, wet);
		wetuwn wet;
	}

	wx_tid->ba_win_sz = ba_win_sz;

	wetuwn 0;
}

static void ath11k_dp_wx_tid_mem_fwee(stwuct ath11k_base *ab,
				      const u8 *peew_mac, int vdev_id, u8 tid)
{
	stwuct ath11k_peew *peew;
	stwuct dp_wx_tid *wx_tid;

	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find(ab, vdev_id, peew_mac);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew to fwee up wx tid mem\n");
		goto unwock_exit;
	}

	wx_tid = &peew->wx_tid[tid];
	if (!wx_tid->active)
		goto unwock_exit;

	dma_unmap_singwe(ab->dev, wx_tid->paddw, wx_tid->size,
			 DMA_BIDIWECTIONAW);
	kfwee(wx_tid->vaddw);
	wx_tid->vaddw = NUWW;

	wx_tid->active = fawse;

unwock_exit:
	spin_unwock_bh(&ab->base_wock);
}

int ath11k_peew_wx_tid_setup(stwuct ath11k *aw, const u8 *peew_mac, int vdev_id,
			     u8 tid, u32 ba_win_sz, u16 ssn,
			     enum haw_pn_type pn_type)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_peew *peew;
	stwuct dp_wx_tid *wx_tid;
	u32 hw_desc_sz;
	u32 *addw_awigned;
	void *vaddw;
	dma_addw_t paddw;
	int wet;

	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find(ab, vdev_id, peew_mac);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew %pM to set up wx tid\n",
			    peew_mac);
		spin_unwock_bh(&ab->base_wock);
		wetuwn -ENOENT;
	}

	wx_tid = &peew->wx_tid[tid];
	/* Update the tid queue if it is awweady setup */
	if (wx_tid->active) {
		paddw = wx_tid->paddw;
		wet = ath11k_peew_wx_tid_weo_update(aw, peew, wx_tid,
						    ba_win_sz, ssn, twue);
		spin_unwock_bh(&ab->base_wock);
		if (wet) {
			ath11k_wawn(ab, "faiwed to update weo fow peew %pM wx tid %d\n: %d",
				    peew_mac, tid, wet);
			wetuwn wet;
		}

		wet = ath11k_wmi_peew_wx_weowdew_queue_setup(aw, vdev_id,
							     peew_mac, paddw,
							     tid, 1, ba_win_sz);
		if (wet)
			ath11k_wawn(ab, "faiwed to send wmi wx weowdew queue fow peew %pM tid %d: %d\n",
				    peew_mac, tid, wet);
		wetuwn wet;
	}

	wx_tid->tid = tid;

	wx_tid->ba_win_sz = ba_win_sz;

	/* TODO: Optimize the memowy awwocation fow qos tid based on
	 * the actuaw BA window size in WEO tid update path.
	 */
	if (tid == HAW_DESC_WEO_NON_QOS_TID)
		hw_desc_sz = ath11k_haw_weo_qdesc_size(ba_win_sz, tid);
	ewse
		hw_desc_sz = ath11k_haw_weo_qdesc_size(DP_BA_WIN_SZ_MAX, tid);

	vaddw = kzawwoc(hw_desc_sz + HAW_WINK_DESC_AWIGN - 1, GFP_ATOMIC);
	if (!vaddw) {
		spin_unwock_bh(&ab->base_wock);
		wetuwn -ENOMEM;
	}

	addw_awigned = PTW_AWIGN(vaddw, HAW_WINK_DESC_AWIGN);

	ath11k_haw_weo_qdesc_setup(addw_awigned, tid, ba_win_sz,
				   ssn, pn_type);

	paddw = dma_map_singwe(ab->dev, addw_awigned, hw_desc_sz,
			       DMA_BIDIWECTIONAW);

	wet = dma_mapping_ewwow(ab->dev, paddw);
	if (wet) {
		spin_unwock_bh(&ab->base_wock);
		ath11k_wawn(ab, "faiwed to setup dma map fow peew %pM wx tid %d: %d\n",
			    peew_mac, tid, wet);
		goto eww_mem_fwee;
	}

	wx_tid->vaddw = vaddw;
	wx_tid->paddw = paddw;
	wx_tid->size = hw_desc_sz;
	wx_tid->active = twue;

	spin_unwock_bh(&ab->base_wock);

	wet = ath11k_wmi_peew_wx_weowdew_queue_setup(aw, vdev_id, peew_mac,
						     paddw, tid, 1, ba_win_sz);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup wx weowdew queue fow peew %pM tid %d: %d\n",
			    peew_mac, tid, wet);
		ath11k_dp_wx_tid_mem_fwee(ab, peew_mac, vdev_id, tid);
	}

	wetuwn wet;

eww_mem_fwee:
	kfwee(wx_tid->vaddw);
	wx_tid->vaddw = NUWW;

	wetuwn wet;
}

int ath11k_dp_wx_ampdu_stawt(stwuct ath11k *aw,
			     stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(pawams->sta);
	int vdev_id = awsta->awvif->vdev_id;
	int wet;

	wet = ath11k_peew_wx_tid_setup(aw, pawams->sta->addw, vdev_id,
				       pawams->tid, pawams->buf_size,
				       pawams->ssn, awsta->pn_type);
	if (wet)
		ath11k_wawn(ab, "faiwed to setup wx tid %d\n", wet);

	wetuwn wet;
}

int ath11k_dp_wx_ampdu_stop(stwuct ath11k *aw,
			    stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_peew *peew;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(pawams->sta);
	int vdev_id = awsta->awvif->vdev_id;
	dma_addw_t paddw;
	boow active;
	int wet;

	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find(ab, vdev_id, pawams->sta->addw);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew to stop wx aggwegation\n");
		spin_unwock_bh(&ab->base_wock);
		wetuwn -ENOENT;
	}

	paddw = peew->wx_tid[pawams->tid].paddw;
	active = peew->wx_tid[pawams->tid].active;

	if (!active) {
		spin_unwock_bh(&ab->base_wock);
		wetuwn 0;
	}

	wet = ath11k_peew_wx_tid_weo_update(aw, peew, peew->wx_tid, 1, 0, fawse);
	spin_unwock_bh(&ab->base_wock);
	if (wet) {
		ath11k_wawn(ab, "faiwed to update weo fow wx tid %d: %d\n",
			    pawams->tid, wet);
		wetuwn wet;
	}

	wet = ath11k_wmi_peew_wx_weowdew_queue_setup(aw, vdev_id,
						     pawams->sta->addw, paddw,
						     pawams->tid, 1, 1);
	if (wet)
		ath11k_wawn(ab, "faiwed to send wmi to dewete wx tid %d\n",
			    wet);

	wetuwn wet;
}

int ath11k_dp_peew_wx_pn_wepway_config(stwuct ath11k_vif *awvif,
				       const u8 *peew_addw,
				       enum set_key_cmd key_cmd,
				       stwuct ieee80211_key_conf *key)
{
	stwuct ath11k *aw = awvif->aw;
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_haw_weo_cmd cmd = {0};
	stwuct ath11k_peew *peew;
	stwuct dp_wx_tid *wx_tid;
	u8 tid;
	int wet = 0;

	/* NOTE: Enabwe PN/TSC wepway check offwoad onwy fow unicast fwames.
	 * We use mac80211 PN/TSC wepway check functionawity fow bcast/mcast
	 * fow now.
	 */
	if (!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn 0;

	cmd.fwag |= HAW_WEO_CMD_FWG_NEED_STATUS;
	cmd.upd0 |= HAW_WEO_CMD_UPD0_PN |
		    HAW_WEO_CMD_UPD0_PN_SIZE |
		    HAW_WEO_CMD_UPD0_PN_VAWID |
		    HAW_WEO_CMD_UPD0_PN_CHECK |
		    HAW_WEO_CMD_UPD0_SVWD;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (key_cmd == SET_KEY) {
			cmd.upd1 |= HAW_WEO_CMD_UPD1_PN_CHECK;
			cmd.pn_size = 48;
		}
		bweak;
	defauwt:
		bweak;
	}

	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find(ab, awvif->vdev_id, peew_addw);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew to configuwe pn wepway detection\n");
		spin_unwock_bh(&ab->base_wock);
		wetuwn -ENOENT;
	}

	fow (tid = 0; tid <= IEEE80211_NUM_TIDS; tid++) {
		wx_tid = &peew->wx_tid[tid];
		if (!wx_tid->active)
			continue;
		cmd.addw_wo = wowew_32_bits(wx_tid->paddw);
		cmd.addw_hi = uppew_32_bits(wx_tid->paddw);
		wet = ath11k_dp_tx_send_weo_cmd(ab, wx_tid,
						HAW_WEO_CMD_UPDATE_WX_QUEUE,
						&cmd, NUWW);
		if (wet) {
			ath11k_wawn(ab, "faiwed to configuwe wx tid %d queue fow pn wepway detection %d\n",
				    tid, wet);
			bweak;
		}
	}

	spin_unwock_bh(&ab->base_wock);

	wetuwn wet;
}

static inwine int ath11k_get_ppdu_usew_index(stwuct htt_ppdu_stats *ppdu_stats,
					     u16 peew_id)
{
	int i;

	fow (i = 0; i < HTT_PPDU_STATS_MAX_USEWS - 1; i++) {
		if (ppdu_stats->usew_stats[i].is_vawid_peew_id) {
			if (peew_id == ppdu_stats->usew_stats[i].peew_id)
				wetuwn i;
		} ewse {
			wetuwn i;
		}
	}

	wetuwn -EINVAW;
}

static int ath11k_htt_twv_ppdu_stats_pawse(stwuct ath11k_base *ab,
					   u16 tag, u16 wen, const void *ptw,
					   void *data)
{
	stwuct htt_ppdu_stats_info *ppdu_info;
	stwuct htt_ppdu_usew_stats *usew_stats;
	int cuw_usew;
	u16 peew_id;

	ppdu_info = data;

	switch (tag) {
	case HTT_PPDU_STATS_TAG_COMMON:
		if (wen < sizeof(stwuct htt_ppdu_stats_common)) {
			ath11k_wawn(ab, "Invawid wen %d fow the tag 0x%x\n",
				    wen, tag);
			wetuwn -EINVAW;
		}
		memcpy((void *)&ppdu_info->ppdu_stats.common, ptw,
		       sizeof(stwuct htt_ppdu_stats_common));
		bweak;
	case HTT_PPDU_STATS_TAG_USW_WATE:
		if (wen < sizeof(stwuct htt_ppdu_stats_usew_wate)) {
			ath11k_wawn(ab, "Invawid wen %d fow the tag 0x%x\n",
				    wen, tag);
			wetuwn -EINVAW;
		}

		peew_id = ((stwuct htt_ppdu_stats_usew_wate *)ptw)->sw_peew_id;
		cuw_usew = ath11k_get_ppdu_usew_index(&ppdu_info->ppdu_stats,
						      peew_id);
		if (cuw_usew < 0)
			wetuwn -EINVAW;
		usew_stats = &ppdu_info->ppdu_stats.usew_stats[cuw_usew];
		usew_stats->peew_id = peew_id;
		usew_stats->is_vawid_peew_id = twue;
		memcpy((void *)&usew_stats->wate, ptw,
		       sizeof(stwuct htt_ppdu_stats_usew_wate));
		usew_stats->twv_fwags |= BIT(tag);
		bweak;
	case HTT_PPDU_STATS_TAG_USW_COMPWTN_COMMON:
		if (wen < sizeof(stwuct htt_ppdu_stats_usw_cmpwtn_cmn)) {
			ath11k_wawn(ab, "Invawid wen %d fow the tag 0x%x\n",
				    wen, tag);
			wetuwn -EINVAW;
		}

		peew_id = ((stwuct htt_ppdu_stats_usw_cmpwtn_cmn *)ptw)->sw_peew_id;
		cuw_usew = ath11k_get_ppdu_usew_index(&ppdu_info->ppdu_stats,
						      peew_id);
		if (cuw_usew < 0)
			wetuwn -EINVAW;
		usew_stats = &ppdu_info->ppdu_stats.usew_stats[cuw_usew];
		usew_stats->peew_id = peew_id;
		usew_stats->is_vawid_peew_id = twue;
		memcpy((void *)&usew_stats->cmpwtn_cmn, ptw,
		       sizeof(stwuct htt_ppdu_stats_usw_cmpwtn_cmn));
		usew_stats->twv_fwags |= BIT(tag);
		bweak;
	case HTT_PPDU_STATS_TAG_USW_COMPWTN_ACK_BA_STATUS:
		if (wen <
		    sizeof(stwuct htt_ppdu_stats_usw_cmpwtn_ack_ba_status)) {
			ath11k_wawn(ab, "Invawid wen %d fow the tag 0x%x\n",
				    wen, tag);
			wetuwn -EINVAW;
		}

		peew_id =
		((stwuct htt_ppdu_stats_usw_cmpwtn_ack_ba_status *)ptw)->sw_peew_id;
		cuw_usew = ath11k_get_ppdu_usew_index(&ppdu_info->ppdu_stats,
						      peew_id);
		if (cuw_usew < 0)
			wetuwn -EINVAW;
		usew_stats = &ppdu_info->ppdu_stats.usew_stats[cuw_usew];
		usew_stats->peew_id = peew_id;
		usew_stats->is_vawid_peew_id = twue;
		memcpy((void *)&usew_stats->ack_ba, ptw,
		       sizeof(stwuct htt_ppdu_stats_usw_cmpwtn_ack_ba_status));
		usew_stats->twv_fwags |= BIT(tag);
		bweak;
	}
	wetuwn 0;
}

int ath11k_dp_htt_twv_itew(stwuct ath11k_base *ab, const void *ptw, size_t wen,
			   int (*itew)(stwuct ath11k_base *aw, u16 tag, u16 wen,
				       const void *ptw, void *data),
			   void *data)
{
	const stwuct htt_twv *twv;
	const void *begin = ptw;
	u16 twv_tag, twv_wen;
	int wet = -EINVAW;

	whiwe (wen > 0) {
		if (wen < sizeof(*twv)) {
			ath11k_eww(ab, "htt twv pawse faiwuwe at byte %zd (%zu bytes weft, %zu expected)\n",
				   ptw - begin, wen, sizeof(*twv));
			wetuwn -EINVAW;
		}
		twv = (stwuct htt_twv *)ptw;
		twv_tag = FIEWD_GET(HTT_TWV_TAG, twv->headew);
		twv_wen = FIEWD_GET(HTT_TWV_WEN, twv->headew);
		ptw += sizeof(*twv);
		wen -= sizeof(*twv);

		if (twv_wen > wen) {
			ath11k_eww(ab, "htt twv pawse faiwuwe of tag %u at byte %zd (%zu bytes weft, %u expected)\n",
				   twv_tag, ptw - begin, wen, twv_wen);
			wetuwn -EINVAW;
		}
		wet = itew(ab, twv_tag, twv_wen, ptw, data);
		if (wet == -ENOMEM)
			wetuwn wet;

		ptw += twv_wen;
		wen -= twv_wen;
	}
	wetuwn 0;
}

static void
ath11k_update_pew_peew_tx_stats(stwuct ath11k *aw,
				stwuct htt_ppdu_stats *ppdu_stats, u8 usew)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_peew *peew;
	stwuct ieee80211_sta *sta;
	stwuct ath11k_sta *awsta;
	stwuct htt_ppdu_stats_usew_wate *usew_wate;
	stwuct ath11k_pew_peew_tx_stats *peew_stats = &aw->peew_tx_stats;
	stwuct htt_ppdu_usew_stats *usw_stats = &ppdu_stats->usew_stats[usew];
	stwuct htt_ppdu_stats_common *common = &ppdu_stats->common;
	int wet;
	u8 fwags, mcs, nss, bw, sgi, dcm, wate_idx = 0;
	u32 succ_bytes = 0;
	u16 wate = 0, succ_pkts = 0;
	u32 tx_duwation = 0;
	u8 tid = HTT_PPDU_STATS_NON_QOS_TID;
	boow is_ampdu = fawse;

	if (!(usw_stats->twv_fwags & BIT(HTT_PPDU_STATS_TAG_USW_WATE)))
		wetuwn;

	if (usw_stats->twv_fwags & BIT(HTT_PPDU_STATS_TAG_USW_COMPWTN_COMMON))
		is_ampdu =
			HTT_USW_CMPWTN_IS_AMPDU(usw_stats->cmpwtn_cmn.fwags);

	if (usw_stats->twv_fwags &
	    BIT(HTT_PPDU_STATS_TAG_USW_COMPWTN_ACK_BA_STATUS)) {
		succ_bytes = usw_stats->ack_ba.success_bytes;
		succ_pkts = FIEWD_GET(HTT_PPDU_STATS_ACK_BA_INFO_NUM_MSDU_M,
				      usw_stats->ack_ba.info);
		tid = FIEWD_GET(HTT_PPDU_STATS_ACK_BA_INFO_TID_NUM,
				usw_stats->ack_ba.info);
	}

	if (common->fes_duwation_us)
		tx_duwation = common->fes_duwation_us;

	usew_wate = &usw_stats->wate;
	fwags = HTT_USW_WATE_PWEAMBWE(usew_wate->wate_fwags);
	bw = HTT_USW_WATE_BW(usew_wate->wate_fwags) - 2;
	nss = HTT_USW_WATE_NSS(usew_wate->wate_fwags) + 1;
	mcs = HTT_USW_WATE_MCS(usew_wate->wate_fwags);
	sgi = HTT_USW_WATE_GI(usew_wate->wate_fwags);
	dcm = HTT_USW_WATE_DCM(usew_wate->wate_fwags);

	/* Note: If host configuwed fixed wates and in some othew speciaw
	 * cases, the bwoadcast/management fwames awe sent in diffewent wates.
	 * Fiwmwawe wate's contwow to be skipped fow this?
	 */

	if (fwags == WMI_WATE_PWEAMBWE_HE && mcs > ATH11K_HE_MCS_MAX) {
		ath11k_wawn(ab, "Invawid HE mcs %d peew stats",  mcs);
		wetuwn;
	}

	if (fwags == WMI_WATE_PWEAMBWE_VHT && mcs > ATH11K_VHT_MCS_MAX) {
		ath11k_wawn(ab, "Invawid VHT mcs %d peew stats",  mcs);
		wetuwn;
	}

	if (fwags == WMI_WATE_PWEAMBWE_HT && (mcs > ATH11K_HT_MCS_MAX || nss < 1)) {
		ath11k_wawn(ab, "Invawid HT mcs %d nss %d peew stats",
			    mcs, nss);
		wetuwn;
	}

	if (fwags == WMI_WATE_PWEAMBWE_CCK || fwags == WMI_WATE_PWEAMBWE_OFDM) {
		wet = ath11k_mac_hw_watecode_to_wegacy_wate(mcs,
							    fwags,
							    &wate_idx,
							    &wate);
		if (wet < 0)
			wetuwn;
	}

	wcu_wead_wock();
	spin_wock_bh(&ab->base_wock);
	peew = ath11k_peew_find_by_id(ab, usw_stats->peew_id);

	if (!peew || !peew->sta) {
		spin_unwock_bh(&ab->base_wock);
		wcu_wead_unwock();
		wetuwn;
	}

	sta = peew->sta;
	awsta = ath11k_sta_to_awsta(sta);

	memset(&awsta->txwate, 0, sizeof(awsta->txwate));

	switch (fwags) {
	case WMI_WATE_PWEAMBWE_OFDM:
		awsta->txwate.wegacy = wate;
		bweak;
	case WMI_WATE_PWEAMBWE_CCK:
		awsta->txwate.wegacy = wate;
		bweak;
	case WMI_WATE_PWEAMBWE_HT:
		awsta->txwate.mcs = mcs + 8 * (nss - 1);
		awsta->txwate.fwags = WATE_INFO_FWAGS_MCS;
		if (sgi)
			awsta->txwate.fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case WMI_WATE_PWEAMBWE_VHT:
		awsta->txwate.mcs = mcs;
		awsta->txwate.fwags = WATE_INFO_FWAGS_VHT_MCS;
		if (sgi)
			awsta->txwate.fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case WMI_WATE_PWEAMBWE_HE:
		awsta->txwate.mcs = mcs;
		awsta->txwate.fwags = WATE_INFO_FWAGS_HE_MCS;
		awsta->txwate.he_dcm = dcm;
		awsta->txwate.he_gi = ath11k_mac_he_gi_to_nw80211_he_gi(sgi);
		awsta->txwate.he_wu_awwoc = ath11k_mac_phy_he_wu_to_nw80211_he_wu_awwoc
						((usew_wate->wu_end -
						 usew_wate->wu_stawt) + 1);
		bweak;
	}

	awsta->txwate.nss = nss;

	awsta->txwate.bw = ath11k_mac_bw_to_mac80211_bw(bw);
	awsta->tx_duwation += tx_duwation;
	memcpy(&awsta->wast_txwate, &awsta->txwate, sizeof(stwuct wate_info));

	/* PPDU stats wepowted fow mgmt packet doesn't have vawid tx bytes.
	 * So skip peew stats update fow mgmt packets.
	 */
	if (tid < HTT_PPDU_STATS_NON_QOS_TID) {
		memset(peew_stats, 0, sizeof(*peew_stats));
		peew_stats->succ_pkts = succ_pkts;
		peew_stats->succ_bytes = succ_bytes;
		peew_stats->is_ampdu = is_ampdu;
		peew_stats->duwation = tx_duwation;
		peew_stats->ba_faiws =
			HTT_USW_CMPWTN_WONG_WETWY(usw_stats->cmpwtn_cmn.fwags) +
			HTT_USW_CMPWTN_SHOWT_WETWY(usw_stats->cmpwtn_cmn.fwags);

		if (ath11k_debugfs_is_extd_tx_stats_enabwed(aw))
			ath11k_debugfs_sta_add_tx_stats(awsta, peew_stats, wate_idx);
	}

	spin_unwock_bh(&ab->base_wock);
	wcu_wead_unwock();
}

static void ath11k_htt_update_ppdu_stats(stwuct ath11k *aw,
					 stwuct htt_ppdu_stats *ppdu_stats)
{
	u8 usew;

	fow (usew = 0; usew < HTT_PPDU_STATS_MAX_USEWS - 1; usew++)
		ath11k_update_pew_peew_tx_stats(aw, ppdu_stats, usew);
}

static
stwuct htt_ppdu_stats_info *ath11k_dp_htt_get_ppdu_desc(stwuct ath11k *aw,
							u32 ppdu_id)
{
	stwuct htt_ppdu_stats_info *ppdu_info;

	wockdep_assewt_hewd(&aw->data_wock);

	if (!wist_empty(&aw->ppdu_stats_info)) {
		wist_fow_each_entwy(ppdu_info, &aw->ppdu_stats_info, wist) {
			if (ppdu_info->ppdu_id == ppdu_id)
				wetuwn ppdu_info;
		}

		if (aw->ppdu_stat_wist_depth > HTT_PPDU_DESC_MAX_DEPTH) {
			ppdu_info = wist_fiwst_entwy(&aw->ppdu_stats_info,
						     typeof(*ppdu_info), wist);
			wist_dew(&ppdu_info->wist);
			aw->ppdu_stat_wist_depth--;
			ath11k_htt_update_ppdu_stats(aw, &ppdu_info->ppdu_stats);
			kfwee(ppdu_info);
		}
	}

	ppdu_info = kzawwoc(sizeof(*ppdu_info), GFP_ATOMIC);
	if (!ppdu_info)
		wetuwn NUWW;

	wist_add_taiw(&ppdu_info->wist, &aw->ppdu_stats_info);
	aw->ppdu_stat_wist_depth++;

	wetuwn ppdu_info;
}

static int ath11k_htt_puww_ppdu_stats(stwuct ath11k_base *ab,
				      stwuct sk_buff *skb)
{
	stwuct ath11k_htt_ppdu_stats_msg *msg;
	stwuct htt_ppdu_stats_info *ppdu_info;
	stwuct ath11k *aw;
	int wet;
	u8 pdev_id;
	u32 ppdu_id, wen;

	msg = (stwuct ath11k_htt_ppdu_stats_msg *)skb->data;
	wen = FIEWD_GET(HTT_T2H_PPDU_STATS_INFO_PAYWOAD_SIZE, msg->info);
	pdev_id = FIEWD_GET(HTT_T2H_PPDU_STATS_INFO_PDEV_ID, msg->info);
	ppdu_id = msg->ppdu_id;

	wcu_wead_wock();
	aw = ath11k_mac_get_aw_by_pdev_id(ab, pdev_id);
	if (!aw) {
		wet = -EINVAW;
		goto out;
	}

	if (ath11k_debugfs_is_pktwog_wite_mode_enabwed(aw))
		twace_ath11k_htt_ppdu_stats(aw, skb->data, wen);

	spin_wock_bh(&aw->data_wock);
	ppdu_info = ath11k_dp_htt_get_ppdu_desc(aw, ppdu_id);
	if (!ppdu_info) {
		wet = -EINVAW;
		goto out_unwock_data;
	}

	ppdu_info->ppdu_id = ppdu_id;
	wet = ath11k_dp_htt_twv_itew(ab, msg->data, wen,
				     ath11k_htt_twv_ppdu_stats_pawse,
				     (void *)ppdu_info);
	if (wet) {
		ath11k_wawn(ab, "Faiwed to pawse twv %d\n", wet);
		goto out_unwock_data;
	}

out_unwock_data:
	spin_unwock_bh(&aw->data_wock);

out:
	wcu_wead_unwock();

	wetuwn wet;
}

static void ath11k_htt_pktwog(stwuct ath11k_base *ab, stwuct sk_buff *skb)
{
	stwuct htt_pktwog_msg *data = (stwuct htt_pktwog_msg *)skb->data;
	stwuct ath_pktwog_hdw *hdw = (stwuct ath_pktwog_hdw *)data;
	stwuct ath11k *aw;
	u8 pdev_id;

	pdev_id = FIEWD_GET(HTT_T2H_PPDU_STATS_INFO_PDEV_ID, data->hdw);

	wcu_wead_wock();

	aw = ath11k_mac_get_aw_by_pdev_id(ab, pdev_id);
	if (!aw) {
		ath11k_wawn(ab, "invawid pdev id %d on htt pktwog\n", pdev_id);
		goto out;
	}

	twace_ath11k_htt_pktwog(aw, data->paywoad, hdw->size,
				aw->ab->pktwog_defs_checksum);

out:
	wcu_wead_unwock();
}

static void ath11k_htt_backpwessuwe_event_handwew(stwuct ath11k_base *ab,
						  stwuct sk_buff *skb)
{
	u32 *data = (u32 *)skb->data;
	u8 pdev_id, wing_type, wing_id, pdev_idx;
	u16 hp, tp;
	u32 backpwessuwe_time;
	stwuct ath11k_bp_stats *bp_stats;

	pdev_id = FIEWD_GET(HTT_BACKPWESSUWE_EVENT_PDEV_ID_M, *data);
	wing_type = FIEWD_GET(HTT_BACKPWESSUWE_EVENT_WING_TYPE_M, *data);
	wing_id = FIEWD_GET(HTT_BACKPWESSUWE_EVENT_WING_ID_M, *data);
	++data;

	hp = FIEWD_GET(HTT_BACKPWESSUWE_EVENT_HP_M, *data);
	tp = FIEWD_GET(HTT_BACKPWESSUWE_EVENT_TP_M, *data);
	++data;

	backpwessuwe_time = *data;

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "backpwessuwe event, pdev %d, wing type %d,wing id %d, hp %d tp %d, backpwessuwe time %d\n",
		   pdev_id, wing_type, wing_id, hp, tp, backpwessuwe_time);

	if (wing_type == HTT_BACKPWESSUWE_UMAC_WING_TYPE) {
		if (wing_id >= HTT_SW_UMAC_WING_IDX_MAX)
			wetuwn;

		bp_stats = &ab->soc_stats.bp_stats.umac_wing_bp_stats[wing_id];
	} ewse if (wing_type == HTT_BACKPWESSUWE_WMAC_WING_TYPE) {
		pdev_idx = DP_HW2SW_MACID(pdev_id);

		if (wing_id >= HTT_SW_WMAC_WING_IDX_MAX || pdev_idx >= MAX_WADIOS)
			wetuwn;

		bp_stats = &ab->soc_stats.bp_stats.wmac_wing_bp_stats[wing_id][pdev_idx];
	} ewse {
		ath11k_wawn(ab, "unknown wing type weceived in htt bp event %d\n",
			    wing_type);
		wetuwn;
	}

	spin_wock_bh(&ab->base_wock);
	bp_stats->hp = hp;
	bp_stats->tp = tp;
	bp_stats->count++;
	bp_stats->jiffies = jiffies;
	spin_unwock_bh(&ab->base_wock);
}

void ath11k_dp_htt_htc_t2h_msg_handwew(stwuct ath11k_base *ab,
				       stwuct sk_buff *skb)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct htt_wesp_msg *wesp = (stwuct htt_wesp_msg *)skb->data;
	enum htt_t2h_msg_type type = FIEWD_GET(HTT_T2H_MSG_TYPE, *(u32 *)wesp);
	u16 peew_id;
	u8 vdev_id;
	u8 mac_addw[ETH_AWEN];
	u16 peew_mac_h16;
	u16 ast_hash;
	u16 hw_peew_id;

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "dp_htt wx msg type :0x%0x\n", type);

	switch (type) {
	case HTT_T2H_MSG_TYPE_VEWSION_CONF:
		dp->htt_tgt_vew_majow = FIEWD_GET(HTT_T2H_VEWSION_CONF_MAJOW,
						  wesp->vewsion_msg.vewsion);
		dp->htt_tgt_vew_minow = FIEWD_GET(HTT_T2H_VEWSION_CONF_MINOW,
						  wesp->vewsion_msg.vewsion);
		compwete(&dp->htt_tgt_vewsion_weceived);
		bweak;
	case HTT_T2H_MSG_TYPE_PEEW_MAP:
		vdev_id = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO_VDEV_ID,
				    wesp->peew_map_ev.info);
		peew_id = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO_PEEW_ID,
				    wesp->peew_map_ev.info);
		peew_mac_h16 = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO1_MAC_ADDW_H16,
					 wesp->peew_map_ev.info1);
		ath11k_dp_get_mac_addw(wesp->peew_map_ev.mac_addw_w32,
				       peew_mac_h16, mac_addw);
		ath11k_peew_map_event(ab, vdev_id, peew_id, mac_addw, 0, 0);
		bweak;
	case HTT_T2H_MSG_TYPE_PEEW_MAP2:
		vdev_id = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO_VDEV_ID,
				    wesp->peew_map_ev.info);
		peew_id = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO_PEEW_ID,
				    wesp->peew_map_ev.info);
		peew_mac_h16 = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO1_MAC_ADDW_H16,
					 wesp->peew_map_ev.info1);
		ath11k_dp_get_mac_addw(wesp->peew_map_ev.mac_addw_w32,
				       peew_mac_h16, mac_addw);
		ast_hash = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO2_AST_HASH_VAW,
				     wesp->peew_map_ev.info2);
		hw_peew_id = FIEWD_GET(HTT_T2H_PEEW_MAP_INFO1_HW_PEEW_ID,
				       wesp->peew_map_ev.info1);
		ath11k_peew_map_event(ab, vdev_id, peew_id, mac_addw, ast_hash,
				      hw_peew_id);
		bweak;
	case HTT_T2H_MSG_TYPE_PEEW_UNMAP:
	case HTT_T2H_MSG_TYPE_PEEW_UNMAP2:
		peew_id = FIEWD_GET(HTT_T2H_PEEW_UNMAP_INFO_PEEW_ID,
				    wesp->peew_unmap_ev.info);
		ath11k_peew_unmap_event(ab, peew_id);
		bweak;
	case HTT_T2H_MSG_TYPE_PPDU_STATS_IND:
		ath11k_htt_puww_ppdu_stats(ab, skb);
		bweak;
	case HTT_T2H_MSG_TYPE_EXT_STATS_CONF:
		ath11k_debugfs_htt_ext_stats_handwew(ab, skb);
		bweak;
	case HTT_T2H_MSG_TYPE_PKTWOG:
		ath11k_htt_pktwog(ab, skb);
		bweak;
	case HTT_T2H_MSG_TYPE_BKPWESSUWE_EVENT_IND:
		ath11k_htt_backpwessuwe_event_handwew(ab, skb);
		bweak;
	defauwt:
		ath11k_wawn(ab, "htt event %d not handwed\n", type);
		bweak;
	}

	dev_kfwee_skb_any(skb);
}

static int ath11k_dp_wx_msdu_coawesce(stwuct ath11k *aw,
				      stwuct sk_buff_head *msdu_wist,
				      stwuct sk_buff *fiwst, stwuct sk_buff *wast,
				      u8 w3pad_bytes, int msdu_wen)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct sk_buff *skb;
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(fiwst);
	int buf_fiwst_hdw_wen, buf_fiwst_wen;
	stwuct haw_wx_desc *wdesc;
	int space_extwa, wem_wen, buf_wen;
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	/* As the msdu is spwead acwoss muwtipwe wx buffews,
	 * find the offset to the stawt of msdu fow computing
	 * the wength of the msdu in the fiwst buffew.
	 */
	buf_fiwst_hdw_wen = haw_wx_desc_sz + w3pad_bytes;
	buf_fiwst_wen = DP_WX_BUFFEW_SIZE - buf_fiwst_hdw_wen;

	if (WAWN_ON_ONCE(msdu_wen <= buf_fiwst_wen)) {
		skb_put(fiwst, buf_fiwst_hdw_wen + msdu_wen);
		skb_puww(fiwst, buf_fiwst_hdw_wen);
		wetuwn 0;
	}

	wdesc = (stwuct haw_wx_desc *)wast->data;
	wxcb->is_fiwst_msdu = ath11k_dp_wx_h_msdu_end_fiwst_msdu(ab, wdesc);
	wxcb->is_wast_msdu = ath11k_dp_wx_h_msdu_end_wast_msdu(ab, wdesc);

	/* MSDU spans ovew muwtipwe buffews because the wength of the MSDU
	 * exceeds DP_WX_BUFFEW_SIZE - HAW_WX_DESC_SIZE. So assume the data
	 * in the fiwst buf is of wength DP_WX_BUFFEW_SIZE - HAW_WX_DESC_SIZE.
	 */
	skb_put(fiwst, DP_WX_BUFFEW_SIZE);
	skb_puww(fiwst, buf_fiwst_hdw_wen);

	/* When an MSDU spwead ovew muwtipwe buffews attention, MSDU_END and
	 * MPDU_END twvs awe vawid onwy in the wast buffew. Copy those twvs.
	 */
	ath11k_dp_wx_desc_end_twv_copy(ab, wxcb->wx_desc, wdesc);

	space_extwa = msdu_wen - (buf_fiwst_wen + skb_taiwwoom(fiwst));
	if (space_extwa > 0 &&
	    (pskb_expand_head(fiwst, 0, space_extwa, GFP_ATOMIC) < 0)) {
		/* Fwee up aww buffews of the MSDU */
		whiwe ((skb = __skb_dequeue(msdu_wist)) != NUWW) {
			wxcb = ATH11K_SKB_WXCB(skb);
			if (!wxcb->is_continuation) {
				dev_kfwee_skb_any(skb);
				bweak;
			}
			dev_kfwee_skb_any(skb);
		}
		wetuwn -ENOMEM;
	}

	wem_wen = msdu_wen - buf_fiwst_wen;
	whiwe ((skb = __skb_dequeue(msdu_wist)) != NUWW && wem_wen > 0) {
		wxcb = ATH11K_SKB_WXCB(skb);
		if (wxcb->is_continuation)
			buf_wen = DP_WX_BUFFEW_SIZE - haw_wx_desc_sz;
		ewse
			buf_wen = wem_wen;

		if (buf_wen > (DP_WX_BUFFEW_SIZE - haw_wx_desc_sz)) {
			WAWN_ON_ONCE(1);
			dev_kfwee_skb_any(skb);
			wetuwn -EINVAW;
		}

		skb_put(skb, buf_wen + haw_wx_desc_sz);
		skb_puww(skb, haw_wx_desc_sz);
		skb_copy_fwom_wineaw_data(skb, skb_put(fiwst, buf_wen),
					  buf_wen);
		dev_kfwee_skb_any(skb);

		wem_wen -= buf_wen;
		if (!wxcb->is_continuation)
			bweak;
	}

	wetuwn 0;
}

static stwuct sk_buff *ath11k_dp_wx_get_msdu_wast_buf(stwuct sk_buff_head *msdu_wist,
						      stwuct sk_buff *fiwst)
{
	stwuct sk_buff *skb;
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(fiwst);

	if (!wxcb->is_continuation)
		wetuwn fiwst;

	skb_queue_wawk(msdu_wist, skb) {
		wxcb = ATH11K_SKB_WXCB(skb);
		if (!wxcb->is_continuation)
			wetuwn skb;
	}

	wetuwn NUWW;
}

static void ath11k_dp_wx_h_csum_offwoad(stwuct ath11k *aw, stwuct sk_buff *msdu)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	stwuct wx_attention *wx_attention;
	boow ip_csum_faiw, w4_csum_faiw;

	wx_attention = ath11k_dp_wx_get_attention(aw->ab, wxcb->wx_desc);
	ip_csum_faiw = ath11k_dp_wx_h_attn_ip_cksum_faiw(wx_attention);
	w4_csum_faiw = ath11k_dp_wx_h_attn_w4_cksum_faiw(wx_attention);

	msdu->ip_summed = (ip_csum_faiw || w4_csum_faiw) ?
			  CHECKSUM_NONE : CHECKSUM_UNNECESSAWY;
}

static int ath11k_dp_wx_cwypto_mic_wen(stwuct ath11k *aw,
				       enum haw_encwypt_type enctype)
{
	switch (enctype) {
	case HAW_ENCWYPT_TYPE_OPEN:
	case HAW_ENCWYPT_TYPE_TKIP_NO_MIC:
	case HAW_ENCWYPT_TYPE_TKIP_MIC:
		wetuwn 0;
	case HAW_ENCWYPT_TYPE_CCMP_128:
		wetuwn IEEE80211_CCMP_MIC_WEN;
	case HAW_ENCWYPT_TYPE_CCMP_256:
		wetuwn IEEE80211_CCMP_256_MIC_WEN;
	case HAW_ENCWYPT_TYPE_GCMP_128:
	case HAW_ENCWYPT_TYPE_AES_GCMP_256:
		wetuwn IEEE80211_GCMP_MIC_WEN;
	case HAW_ENCWYPT_TYPE_WEP_40:
	case HAW_ENCWYPT_TYPE_WEP_104:
	case HAW_ENCWYPT_TYPE_WEP_128:
	case HAW_ENCWYPT_TYPE_WAPI_GCM_SM4:
	case HAW_ENCWYPT_TYPE_WAPI:
		bweak;
	}

	ath11k_wawn(aw->ab, "unsuppowted encwyption type %d fow mic wen\n", enctype);
	wetuwn 0;
}

static int ath11k_dp_wx_cwypto_pawam_wen(stwuct ath11k *aw,
					 enum haw_encwypt_type enctype)
{
	switch (enctype) {
	case HAW_ENCWYPT_TYPE_OPEN:
		wetuwn 0;
	case HAW_ENCWYPT_TYPE_TKIP_NO_MIC:
	case HAW_ENCWYPT_TYPE_TKIP_MIC:
		wetuwn IEEE80211_TKIP_IV_WEN;
	case HAW_ENCWYPT_TYPE_CCMP_128:
		wetuwn IEEE80211_CCMP_HDW_WEN;
	case HAW_ENCWYPT_TYPE_CCMP_256:
		wetuwn IEEE80211_CCMP_256_HDW_WEN;
	case HAW_ENCWYPT_TYPE_GCMP_128:
	case HAW_ENCWYPT_TYPE_AES_GCMP_256:
		wetuwn IEEE80211_GCMP_HDW_WEN;
	case HAW_ENCWYPT_TYPE_WEP_40:
	case HAW_ENCWYPT_TYPE_WEP_104:
	case HAW_ENCWYPT_TYPE_WEP_128:
	case HAW_ENCWYPT_TYPE_WAPI_GCM_SM4:
	case HAW_ENCWYPT_TYPE_WAPI:
		bweak;
	}

	ath11k_wawn(aw->ab, "unsuppowted encwyption type %d\n", enctype);
	wetuwn 0;
}

static int ath11k_dp_wx_cwypto_icv_wen(stwuct ath11k *aw,
				       enum haw_encwypt_type enctype)
{
	switch (enctype) {
	case HAW_ENCWYPT_TYPE_OPEN:
	case HAW_ENCWYPT_TYPE_CCMP_128:
	case HAW_ENCWYPT_TYPE_CCMP_256:
	case HAW_ENCWYPT_TYPE_GCMP_128:
	case HAW_ENCWYPT_TYPE_AES_GCMP_256:
		wetuwn 0;
	case HAW_ENCWYPT_TYPE_TKIP_NO_MIC:
	case HAW_ENCWYPT_TYPE_TKIP_MIC:
		wetuwn IEEE80211_TKIP_ICV_WEN;
	case HAW_ENCWYPT_TYPE_WEP_40:
	case HAW_ENCWYPT_TYPE_WEP_104:
	case HAW_ENCWYPT_TYPE_WEP_128:
	case HAW_ENCWYPT_TYPE_WAPI_GCM_SM4:
	case HAW_ENCWYPT_TYPE_WAPI:
		bweak;
	}

	ath11k_wawn(aw->ab, "unsuppowted encwyption type %d\n", enctype);
	wetuwn 0;
}

static void ath11k_dp_wx_h_undecap_nwifi(stwuct ath11k *aw,
					 stwuct sk_buff *msdu,
					 u8 *fiwst_hdw,
					 enum haw_encwypt_type enctype,
					 stwuct ieee80211_wx_status *status)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	u8 decap_hdw[DP_MAX_NWIFI_HDW_WEN];
	stwuct ieee80211_hdw *hdw;
	size_t hdw_wen;
	u8 da[ETH_AWEN];
	u8 sa[ETH_AWEN];
	u16 qos_ctw = 0;
	u8 *qos;

	/* copy SA & DA and puww decapped headew */
	hdw = (stwuct ieee80211_hdw *)msdu->data;
	hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
	ethew_addw_copy(da, ieee80211_get_DA(hdw));
	ethew_addw_copy(sa, ieee80211_get_SA(hdw));
	skb_puww(msdu, ieee80211_hdwwen(hdw->fwame_contwow));

	if (wxcb->is_fiwst_msdu) {
		/* owiginaw 802.11 headew is vawid fow the fiwst msdu
		 * hence we can weuse the same headew
		 */
		hdw = (stwuct ieee80211_hdw *)fiwst_hdw;
		hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);

		/* Each A-MSDU subfwame wiww be wepowted as a sepawate MSDU,
		 * so stwip the A-MSDU bit fwom QoS Ctw.
		 */
		if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
			qos = ieee80211_get_qos_ctw(hdw);
			qos[0] &= ~IEEE80211_QOS_CTW_A_MSDU_PWESENT;
		}
	} ewse {
		/*  Webuiwd qos headew if this is a middwe/wast msdu */
		hdw->fwame_contwow |= __cpu_to_we16(IEEE80211_STYPE_QOS_DATA);

		/* Weset the owdew bit as the HT_Contwow headew is stwipped */
		hdw->fwame_contwow &= ~(__cpu_to_we16(IEEE80211_FCTW_OWDEW));

		qos_ctw = wxcb->tid;

		if (ath11k_dp_wx_h_msdu_stawt_mesh_ctw_pwesent(aw->ab, wxcb->wx_desc))
			qos_ctw |= IEEE80211_QOS_CTW_MESH_CONTWOW_PWESENT;

		/* TODO Add othew QoS ctw fiewds when wequiwed */

		/* copy decap headew befowe ovewwwiting fow weuse bewow */
		memcpy(decap_hdw, (uint8_t *)hdw, hdw_wen);
	}

	if (!(status->fwag & WX_FWAG_IV_STWIPPED)) {
		memcpy(skb_push(msdu,
				ath11k_dp_wx_cwypto_pawam_wen(aw, enctype)),
		       (void *)hdw + hdw_wen,
		       ath11k_dp_wx_cwypto_pawam_wen(aw, enctype));
	}

	if (!wxcb->is_fiwst_msdu) {
		memcpy(skb_push(msdu,
				IEEE80211_QOS_CTW_WEN), &qos_ctw,
				IEEE80211_QOS_CTW_WEN);
		memcpy(skb_push(msdu, hdw_wen), decap_hdw, hdw_wen);
		wetuwn;
	}

	memcpy(skb_push(msdu, hdw_wen), hdw, hdw_wen);

	/* owiginaw 802.11 headew has a diffewent DA and in
	 * case of 4addw it may awso have diffewent SA
	 */
	hdw = (stwuct ieee80211_hdw *)msdu->data;
	ethew_addw_copy(ieee80211_get_DA(hdw), da);
	ethew_addw_copy(ieee80211_get_SA(hdw), sa);
}

static void ath11k_dp_wx_h_undecap_waw(stwuct ath11k *aw, stwuct sk_buff *msdu,
				       enum haw_encwypt_type enctype,
				       stwuct ieee80211_wx_status *status,
				       boow decwypted)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	stwuct ieee80211_hdw *hdw;
	size_t hdw_wen;
	size_t cwypto_wen;

	if (!wxcb->is_fiwst_msdu ||
	    !(wxcb->is_fiwst_msdu && wxcb->is_wast_msdu)) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	skb_twim(msdu, msdu->wen - FCS_WEN);

	if (!decwypted)
		wetuwn;

	hdw = (void *)msdu->data;

	/* Taiw */
	if (status->fwag & WX_FWAG_IV_STWIPPED) {
		skb_twim(msdu, msdu->wen -
			 ath11k_dp_wx_cwypto_mic_wen(aw, enctype));

		skb_twim(msdu, msdu->wen -
			 ath11k_dp_wx_cwypto_icv_wen(aw, enctype));
	} ewse {
		/* MIC */
		if (status->fwag & WX_FWAG_MIC_STWIPPED)
			skb_twim(msdu, msdu->wen -
				 ath11k_dp_wx_cwypto_mic_wen(aw, enctype));

		/* ICV */
		if (status->fwag & WX_FWAG_ICV_STWIPPED)
			skb_twim(msdu, msdu->wen -
				 ath11k_dp_wx_cwypto_icv_wen(aw, enctype));
	}

	/* MMIC */
	if ((status->fwag & WX_FWAG_MMIC_STWIPPED) &&
	    !ieee80211_has_mowefwags(hdw->fwame_contwow) &&
	    enctype == HAW_ENCWYPT_TYPE_TKIP_MIC)
		skb_twim(msdu, msdu->wen - IEEE80211_CCMP_MIC_WEN);

	/* Head */
	if (status->fwag & WX_FWAG_IV_STWIPPED) {
		hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
		cwypto_wen = ath11k_dp_wx_cwypto_pawam_wen(aw, enctype);

		memmove((void *)msdu->data + cwypto_wen,
			(void *)msdu->data, hdw_wen);
		skb_puww(msdu, cwypto_wen);
	}
}

static void *ath11k_dp_wx_h_find_wfc1042(stwuct ath11k *aw,
					 stwuct sk_buff *msdu,
					 enum haw_encwypt_type enctype)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	stwuct ieee80211_hdw *hdw;
	size_t hdw_wen, cwypto_wen;
	void *wfc1042;
	boow is_amsdu;

	is_amsdu = !(wxcb->is_fiwst_msdu && wxcb->is_wast_msdu);
	hdw = (stwuct ieee80211_hdw *)ath11k_dp_wx_h_80211_hdw(aw->ab, wxcb->wx_desc);
	wfc1042 = hdw;

	if (wxcb->is_fiwst_msdu) {
		hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
		cwypto_wen = ath11k_dp_wx_cwypto_pawam_wen(aw, enctype);

		wfc1042 += hdw_wen + cwypto_wen;
	}

	if (is_amsdu)
		wfc1042 += sizeof(stwuct ath11k_dp_amsdu_subfwame_hdw);

	wetuwn wfc1042;
}

static void ath11k_dp_wx_h_undecap_eth(stwuct ath11k *aw,
				       stwuct sk_buff *msdu,
				       u8 *fiwst_hdw,
				       enum haw_encwypt_type enctype,
				       stwuct ieee80211_wx_status *status)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ethhdw *eth;
	size_t hdw_wen;
	u8 da[ETH_AWEN];
	u8 sa[ETH_AWEN];
	void *wfc1042;

	wfc1042 = ath11k_dp_wx_h_find_wfc1042(aw, msdu, enctype);
	if (WAWN_ON_ONCE(!wfc1042))
		wetuwn;

	/* puww decapped headew and copy SA & DA */
	eth = (stwuct ethhdw *)msdu->data;
	ethew_addw_copy(da, eth->h_dest);
	ethew_addw_copy(sa, eth->h_souwce);
	skb_puww(msdu, sizeof(stwuct ethhdw));

	/* push wfc1042/wwc/snap */
	memcpy(skb_push(msdu, sizeof(stwuct ath11k_dp_wfc1042_hdw)), wfc1042,
	       sizeof(stwuct ath11k_dp_wfc1042_hdw));

	/* push owiginaw 802.11 headew */
	hdw = (stwuct ieee80211_hdw *)fiwst_hdw;
	hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);

	if (!(status->fwag & WX_FWAG_IV_STWIPPED)) {
		memcpy(skb_push(msdu,
				ath11k_dp_wx_cwypto_pawam_wen(aw, enctype)),
		       (void *)hdw + hdw_wen,
		       ath11k_dp_wx_cwypto_pawam_wen(aw, enctype));
	}

	memcpy(skb_push(msdu, hdw_wen), hdw, hdw_wen);

	/* owiginaw 802.11 headew has a diffewent DA and in
	 * case of 4addw it may awso have diffewent SA
	 */
	hdw = (stwuct ieee80211_hdw *)msdu->data;
	ethew_addw_copy(ieee80211_get_DA(hdw), da);
	ethew_addw_copy(ieee80211_get_SA(hdw), sa);
}

static void ath11k_dp_wx_h_undecap(stwuct ath11k *aw, stwuct sk_buff *msdu,
				   stwuct haw_wx_desc *wx_desc,
				   enum haw_encwypt_type enctype,
				   stwuct ieee80211_wx_status *status,
				   boow decwypted)
{
	u8 *fiwst_hdw;
	u8 decap;
	stwuct ethhdw *ehdw;

	fiwst_hdw = ath11k_dp_wx_h_80211_hdw(aw->ab, wx_desc);
	decap = ath11k_dp_wx_h_msdu_stawt_decap_type(aw->ab, wx_desc);

	switch (decap) {
	case DP_WX_DECAP_TYPE_NATIVE_WIFI:
		ath11k_dp_wx_h_undecap_nwifi(aw, msdu, fiwst_hdw,
					     enctype, status);
		bweak;
	case DP_WX_DECAP_TYPE_WAW:
		ath11k_dp_wx_h_undecap_waw(aw, msdu, enctype, status,
					   decwypted);
		bweak;
	case DP_WX_DECAP_TYPE_ETHEWNET2_DIX:
		ehdw = (stwuct ethhdw *)msdu->data;

		/* mac80211 awwows fast path onwy fow authowized STA */
		if (ehdw->h_pwoto == cpu_to_be16(ETH_P_PAE)) {
			ATH11K_SKB_WXCB(msdu)->is_eapow = twue;
			ath11k_dp_wx_h_undecap_eth(aw, msdu, fiwst_hdw,
						   enctype, status);
			bweak;
		}

		/* PN fow mcast packets wiww be vawidated in mac80211;
		 * wemove eth headew and add 802.11 headew.
		 */
		if (ATH11K_SKB_WXCB(msdu)->is_mcbc && decwypted)
			ath11k_dp_wx_h_undecap_eth(aw, msdu, fiwst_hdw,
						   enctype, status);
		bweak;
	case DP_WX_DECAP_TYPE_8023:
		/* TODO: Handwe undecap fow these fowmats */
		bweak;
	}
}

static stwuct ath11k_peew *
ath11k_dp_wx_h_find_peew(stwuct ath11k_base *ab, stwuct sk_buff *msdu)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	stwuct haw_wx_desc *wx_desc = wxcb->wx_desc;
	stwuct ath11k_peew *peew = NUWW;

	wockdep_assewt_hewd(&ab->base_wock);

	if (wxcb->peew_id)
		peew = ath11k_peew_find_by_id(ab, wxcb->peew_id);

	if (peew)
		wetuwn peew;

	if (!wx_desc || !(ath11k_dp_wxdesc_mac_addw2_vawid(ab, wx_desc)))
		wetuwn NUWW;

	peew = ath11k_peew_find_by_addw(ab,
					ath11k_dp_wxdesc_mpdu_stawt_addw2(ab, wx_desc));
	wetuwn peew;
}

static void ath11k_dp_wx_h_mpdu(stwuct ath11k *aw,
				stwuct sk_buff *msdu,
				stwuct haw_wx_desc *wx_desc,
				stwuct ieee80211_wx_status *wx_status)
{
	boow  fiww_cwypto_hdw;
	enum haw_encwypt_type enctype;
	boow is_decwypted = fawse;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct ieee80211_hdw *hdw;
	stwuct ath11k_peew *peew;
	stwuct wx_attention *wx_attention;
	u32 eww_bitmap;

	/* PN fow muwticast packets wiww be checked in mac80211 */
	wxcb = ATH11K_SKB_WXCB(msdu);
	fiww_cwypto_hdw = ath11k_dp_wx_h_attn_is_mcbc(aw->ab, wx_desc);
	wxcb->is_mcbc = fiww_cwypto_hdw;

	if (wxcb->is_mcbc) {
		wxcb->peew_id = ath11k_dp_wx_h_mpdu_stawt_peew_id(aw->ab, wx_desc);
		wxcb->seq_no = ath11k_dp_wx_h_mpdu_stawt_seq_no(aw->ab, wx_desc);
	}

	spin_wock_bh(&aw->ab->base_wock);
	peew = ath11k_dp_wx_h_find_peew(aw->ab, msdu);
	if (peew) {
		if (wxcb->is_mcbc)
			enctype = peew->sec_type_gwp;
		ewse
			enctype = peew->sec_type;
	} ewse {
		enctype = ath11k_dp_wx_h_mpdu_stawt_enctype(aw->ab, wx_desc);
	}
	spin_unwock_bh(&aw->ab->base_wock);

	wx_attention = ath11k_dp_wx_get_attention(aw->ab, wx_desc);
	eww_bitmap = ath11k_dp_wx_h_attn_mpdu_eww(wx_attention);
	if (enctype != HAW_ENCWYPT_TYPE_OPEN && !eww_bitmap)
		is_decwypted = ath11k_dp_wx_h_attn_is_decwypted(wx_attention);

	/* Cweaw pew-MPDU fwags whiwe weaving pew-PPDU fwags intact */
	wx_status->fwag &= ~(WX_FWAG_FAIWED_FCS_CWC |
			     WX_FWAG_MMIC_EWWOW |
			     WX_FWAG_DECWYPTED |
			     WX_FWAG_IV_STWIPPED |
			     WX_FWAG_MMIC_STWIPPED);

	if (eww_bitmap & DP_WX_MPDU_EWW_FCS)
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	if (eww_bitmap & DP_WX_MPDU_EWW_TKIP_MIC)
		wx_status->fwag |= WX_FWAG_MMIC_EWWOW;

	if (is_decwypted) {
		wx_status->fwag |= WX_FWAG_DECWYPTED | WX_FWAG_MMIC_STWIPPED;

		if (fiww_cwypto_hdw)
			wx_status->fwag |= WX_FWAG_MIC_STWIPPED |
					WX_FWAG_ICV_STWIPPED;
		ewse
			wx_status->fwag |= WX_FWAG_IV_STWIPPED |
					   WX_FWAG_PN_VAWIDATED;
	}

	ath11k_dp_wx_h_csum_offwoad(aw, msdu);
	ath11k_dp_wx_h_undecap(aw, msdu, wx_desc,
			       enctype, wx_status, is_decwypted);

	if (!is_decwypted || fiww_cwypto_hdw)
		wetuwn;

	if (ath11k_dp_wx_h_msdu_stawt_decap_type(aw->ab, wx_desc) !=
	    DP_WX_DECAP_TYPE_ETHEWNET2_DIX) {
		hdw = (void *)msdu->data;
		hdw->fwame_contwow &= ~__cpu_to_we16(IEEE80211_FCTW_PWOTECTED);
	}
}

static void ath11k_dp_wx_h_wate(stwuct ath11k *aw, stwuct haw_wx_desc *wx_desc,
				stwuct ieee80211_wx_status *wx_status)
{
	stwuct ieee80211_suppowted_band *sband;
	enum wx_msdu_stawt_pkt_type pkt_type;
	u8 bw;
	u8 wate_mcs, nss;
	u8 sgi;
	boow is_cck, is_wdpc;

	pkt_type = ath11k_dp_wx_h_msdu_stawt_pkt_type(aw->ab, wx_desc);
	bw = ath11k_dp_wx_h_msdu_stawt_wx_bw(aw->ab, wx_desc);
	wate_mcs = ath11k_dp_wx_h_msdu_stawt_wate_mcs(aw->ab, wx_desc);
	nss = ath11k_dp_wx_h_msdu_stawt_nss(aw->ab, wx_desc);
	sgi = ath11k_dp_wx_h_msdu_stawt_sgi(aw->ab, wx_desc);

	switch (pkt_type) {
	case WX_MSDU_STAWT_PKT_TYPE_11A:
	case WX_MSDU_STAWT_PKT_TYPE_11B:
		is_cck = (pkt_type == WX_MSDU_STAWT_PKT_TYPE_11B);
		sband = &aw->mac.sbands[wx_status->band];
		wx_status->wate_idx = ath11k_mac_hw_wate_to_idx(sband, wate_mcs,
								is_cck);
		bweak;
	case WX_MSDU_STAWT_PKT_TYPE_11N:
		wx_status->encoding = WX_ENC_HT;
		if (wate_mcs > ATH11K_HT_MCS_MAX) {
			ath11k_wawn(aw->ab,
				    "Weceived with invawid mcs in HT mode %d\n",
				     wate_mcs);
			bweak;
		}
		wx_status->wate_idx = wate_mcs + (8 * (nss - 1));
		if (sgi)
			wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
		wx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		bweak;
	case WX_MSDU_STAWT_PKT_TYPE_11AC:
		wx_status->encoding = WX_ENC_VHT;
		wx_status->wate_idx = wate_mcs;
		if (wate_mcs > ATH11K_VHT_MCS_MAX) {
			ath11k_wawn(aw->ab,
				    "Weceived with invawid mcs in VHT mode %d\n",
				     wate_mcs);
			bweak;
		}
		wx_status->nss = nss;
		if (sgi)
			wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
		wx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		is_wdpc = ath11k_dp_wx_h_msdu_stawt_wdpc_suppowt(aw->ab, wx_desc);
		if (is_wdpc)
			wx_status->enc_fwags |= WX_ENC_FWAG_WDPC;
		bweak;
	case WX_MSDU_STAWT_PKT_TYPE_11AX:
		wx_status->wate_idx = wate_mcs;
		if (wate_mcs > ATH11K_HE_MCS_MAX) {
			ath11k_wawn(aw->ab,
				    "Weceived with invawid mcs in HE mode %d\n",
				    wate_mcs);
			bweak;
		}
		wx_status->encoding = WX_ENC_HE;
		wx_status->nss = nss;
		wx_status->he_gi = ath11k_mac_he_gi_to_nw80211_he_gi(sgi);
		wx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		bweak;
	}
}

static void ath11k_dp_wx_h_ppdu(stwuct ath11k *aw, stwuct haw_wx_desc *wx_desc,
				stwuct ieee80211_wx_status *wx_status)
{
	u8 channew_num;
	u32 centew_fweq, meta_data;
	stwuct ieee80211_channew *channew;

	wx_status->fweq = 0;
	wx_status->wate_idx = 0;
	wx_status->nss = 0;
	wx_status->encoding = WX_ENC_WEGACY;
	wx_status->bw = WATE_INFO_BW_20;

	wx_status->fwag |= WX_FWAG_NO_SIGNAW_VAW;

	meta_data = ath11k_dp_wx_h_msdu_stawt_fweq(aw->ab, wx_desc);
	channew_num = meta_data;
	centew_fweq = meta_data >> 16;

	if (centew_fweq >= ATH11K_MIN_6G_FWEQ &&
	    centew_fweq <= ATH11K_MAX_6G_FWEQ) {
		wx_status->band = NW80211_BAND_6GHZ;
		wx_status->fweq = centew_fweq;
	} ewse if (channew_num >= 1 && channew_num <= 14) {
		wx_status->band = NW80211_BAND_2GHZ;
	} ewse if (channew_num >= 36 && channew_num <= 177) {
		wx_status->band = NW80211_BAND_5GHZ;
	} ewse {
		spin_wock_bh(&aw->data_wock);
		channew = aw->wx_channew;
		if (channew) {
			wx_status->band = channew->band;
			channew_num =
				ieee80211_fwequency_to_channew(channew->centew_fweq);
		}
		spin_unwock_bh(&aw->data_wock);
		ath11k_dbg_dump(aw->ab, ATH11K_DBG_DATA, NUWW, "wx_desc: ",
				wx_desc, sizeof(stwuct haw_wx_desc));
	}

	if (wx_status->band != NW80211_BAND_6GHZ)
		wx_status->fweq = ieee80211_channew_to_fwequency(channew_num,
								 wx_status->band);

	ath11k_dp_wx_h_wate(aw, wx_desc, wx_status);
}

static void ath11k_dp_wx_dewivew_msdu(stwuct ath11k *aw, stwuct napi_stwuct *napi,
				      stwuct sk_buff *msdu,
				      stwuct ieee80211_wx_status *status)
{
	static const stwuct ieee80211_wadiotap_he known = {
		.data1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN),
		.data2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN),
	};
	stwuct ieee80211_wx_status *wx_status;
	stwuct ieee80211_wadiotap_he *he = NUWW;
	stwuct ieee80211_sta *pubsta = NUWW;
	stwuct ath11k_peew *peew;
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	u8 decap = DP_WX_DECAP_TYPE_WAW;
	boow is_mcbc = wxcb->is_mcbc;
	boow is_eapow = wxcb->is_eapow;

	if (status->encoding == WX_ENC_HE &&
	    !(status->fwag & WX_FWAG_WADIOTAP_HE) &&
	    !(status->fwag & WX_FWAG_SKIP_MONITOW)) {
		he = skb_push(msdu, sizeof(known));
		memcpy(he, &known, sizeof(known));
		status->fwag |= WX_FWAG_WADIOTAP_HE;
	}

	if (!(status->fwag & WX_FWAG_ONWY_MONITOW))
		decap = ath11k_dp_wx_h_msdu_stawt_decap_type(aw->ab, wxcb->wx_desc);

	spin_wock_bh(&aw->ab->base_wock);
	peew = ath11k_dp_wx_h_find_peew(aw->ab, msdu);
	if (peew && peew->sta)
		pubsta = peew->sta;
	spin_unwock_bh(&aw->ab->base_wock);

	ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
		   "wx skb %p wen %u peew %pM %d %s sn %u %s%s%s%s%s%s%s %swate_idx %u vht_nss %u fweq %u band %u fwag 0x%x fcs-eww %i mic-eww %i amsdu-mowe %i\n",
		   msdu,
		   msdu->wen,
		   peew ? peew->addw : NUWW,
		   wxcb->tid,
		   is_mcbc ? "mcast" : "ucast",
		   wxcb->seq_no,
		   (status->encoding == WX_ENC_WEGACY) ? "wegacy" : "",
		   (status->encoding == WX_ENC_HT) ? "ht" : "",
		   (status->encoding == WX_ENC_VHT) ? "vht" : "",
		   (status->encoding == WX_ENC_HE) ? "he" : "",
		   (status->bw == WATE_INFO_BW_40) ? "40" : "",
		   (status->bw == WATE_INFO_BW_80) ? "80" : "",
		   (status->bw == WATE_INFO_BW_160) ? "160" : "",
		   status->enc_fwags & WX_ENC_FWAG_SHOWT_GI ? "sgi " : "",
		   status->wate_idx,
		   status->nss,
		   status->fweq,
		   status->band, status->fwag,
		   !!(status->fwag & WX_FWAG_FAIWED_FCS_CWC),
		   !!(status->fwag & WX_FWAG_MMIC_EWWOW),
		   !!(status->fwag & WX_FWAG_AMSDU_MOWE));

	ath11k_dbg_dump(aw->ab, ATH11K_DBG_DP_WX, NUWW, "dp wx msdu: ",
			msdu->data, msdu->wen);

	wx_status = IEEE80211_SKB_WXCB(msdu);
	*wx_status = *status;

	/* TODO: twace wx packet */

	/* PN fow muwticast packets awe not vawidate in HW,
	 * so skip 802.3 wx path
	 * Awso, fast_wx expects the STA to be authowized, hence
	 * eapow packets awe sent in swow path.
	 */
	if (decap == DP_WX_DECAP_TYPE_ETHEWNET2_DIX && !is_eapow &&
	    !(is_mcbc && wx_status->fwag & WX_FWAG_DECWYPTED))
		wx_status->fwag |= WX_FWAG_8023;

	ieee80211_wx_napi(aw->hw, pubsta, msdu, napi);
}

static int ath11k_dp_wx_pwocess_msdu(stwuct ath11k *aw,
				     stwuct sk_buff *msdu,
				     stwuct sk_buff_head *msdu_wist,
				     stwuct ieee80211_wx_status *wx_status)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct haw_wx_desc *wx_desc, *wwx_desc;
	stwuct wx_attention *wx_attention;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct sk_buff *wast_buf;
	u8 w3_pad_bytes;
	u8 *hdw_status;
	u16 msdu_wen;
	int wet;
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	wast_buf = ath11k_dp_wx_get_msdu_wast_buf(msdu_wist, msdu);
	if (!wast_buf) {
		ath11k_wawn(ab,
			    "No vawid Wx buffew to access Atten/MSDU_END/MPDU_END twvs\n");
		wet = -EIO;
		goto fwee_out;
	}

	wx_desc = (stwuct haw_wx_desc *)msdu->data;
	if (ath11k_dp_wx_h_attn_msdu_wen_eww(ab, wx_desc)) {
		ath11k_wawn(aw->ab, "msdu wen not vawid\n");
		wet = -EIO;
		goto fwee_out;
	}

	wwx_desc = (stwuct haw_wx_desc *)wast_buf->data;
	wx_attention = ath11k_dp_wx_get_attention(ab, wwx_desc);
	if (!ath11k_dp_wx_h_attn_msdu_done(wx_attention)) {
		ath11k_wawn(ab, "msdu_done bit in attention is not set\n");
		wet = -EIO;
		goto fwee_out;
	}

	wxcb = ATH11K_SKB_WXCB(msdu);
	wxcb->wx_desc = wx_desc;
	msdu_wen = ath11k_dp_wx_h_msdu_stawt_msdu_wen(ab, wx_desc);
	w3_pad_bytes = ath11k_dp_wx_h_msdu_end_w3pad(ab, wwx_desc);

	if (wxcb->is_fwag) {
		skb_puww(msdu, haw_wx_desc_sz);
	} ewse if (!wxcb->is_continuation) {
		if ((msdu_wen + haw_wx_desc_sz) > DP_WX_BUFFEW_SIZE) {
			hdw_status = ath11k_dp_wx_h_80211_hdw(ab, wx_desc);
			wet = -EINVAW;
			ath11k_wawn(ab, "invawid msdu wen %u\n", msdu_wen);
			ath11k_dbg_dump(ab, ATH11K_DBG_DATA, NUWW, "", hdw_status,
					sizeof(stwuct ieee80211_hdw));
			ath11k_dbg_dump(ab, ATH11K_DBG_DATA, NUWW, "", wx_desc,
					sizeof(stwuct haw_wx_desc));
			goto fwee_out;
		}
		skb_put(msdu, haw_wx_desc_sz + w3_pad_bytes + msdu_wen);
		skb_puww(msdu, haw_wx_desc_sz + w3_pad_bytes);
	} ewse {
		wet = ath11k_dp_wx_msdu_coawesce(aw, msdu_wist,
						 msdu, wast_buf,
						 w3_pad_bytes, msdu_wen);
		if (wet) {
			ath11k_wawn(ab,
				    "faiwed to coawesce msdu wx buffew%d\n", wet);
			goto fwee_out;
		}
	}

	ath11k_dp_wx_h_ppdu(aw, wx_desc, wx_status);
	ath11k_dp_wx_h_mpdu(aw, msdu, wx_desc, wx_status);

	wx_status->fwag |= WX_FWAG_SKIP_MONITOW | WX_FWAG_DUP_VAWIDATED;

	wetuwn 0;

fwee_out:
	wetuwn wet;
}

static void ath11k_dp_wx_pwocess_weceived_packets(stwuct ath11k_base *ab,
						  stwuct napi_stwuct *napi,
						  stwuct sk_buff_head *msdu_wist,
						  int mac_id)
{
	stwuct sk_buff *msdu;
	stwuct ath11k *aw;
	stwuct ieee80211_wx_status wx_status = {0};
	int wet;

	if (skb_queue_empty(msdu_wist))
		wetuwn;

	if (unwikewy(!wcu_access_pointew(ab->pdevs_active[mac_id]))) {
		__skb_queue_puwge(msdu_wist);
		wetuwn;
	}

	aw = ab->pdevs[mac_id].aw;
	if (unwikewy(test_bit(ATH11K_CAC_WUNNING, &aw->dev_fwags))) {
		__skb_queue_puwge(msdu_wist);
		wetuwn;
	}

	whiwe ((msdu = __skb_dequeue(msdu_wist))) {
		wet = ath11k_dp_wx_pwocess_msdu(aw, msdu, msdu_wist, &wx_status);
		if (unwikewy(wet)) {
			ath11k_dbg(ab, ATH11K_DBG_DATA,
				   "Unabwe to pwocess msdu %d", wet);
			dev_kfwee_skb_any(msdu);
			continue;
		}

		ath11k_dp_wx_dewivew_msdu(aw, napi, msdu, &wx_status);
	}
}

int ath11k_dp_pwocess_wx(stwuct ath11k_base *ab, int wing_id,
			 stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct dp_wxdma_wing *wx_wing;
	int num_buffs_weaped[MAX_WADIOS] = {0};
	stwuct sk_buff_head msdu_wist[MAX_WADIOS];
	stwuct ath11k_skb_wxcb *wxcb;
	int totaw_msdu_weaped = 0;
	stwuct haw_swng *swng;
	stwuct sk_buff *msdu;
	boow done = fawse;
	int buf_id, mac_id;
	stwuct ath11k *aw;
	stwuct haw_weo_dest_wing *desc;
	enum haw_weo_dest_wing_push_weason push_weason;
	u32 cookie;
	int i;

	fow (i = 0; i < MAX_WADIOS; i++)
		__skb_queue_head_init(&msdu_wist[i]);

	swng = &ab->haw.swng_wist[dp->weo_dst_wing[wing_id].wing_id];

	spin_wock_bh(&swng->wock);

twy_again:
	ath11k_haw_swng_access_begin(ab, swng);

	whiwe (wikewy(desc =
	      (stwuct haw_weo_dest_wing *)ath11k_haw_swng_dst_get_next_entwy(ab,
									     swng))) {
		cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
				   desc->buf_addw_info.info1);
		buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID,
				   cookie);
		mac_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_PDEV_ID, cookie);

		if (unwikewy(buf_id == 0))
			continue;

		aw = ab->pdevs[mac_id].aw;
		wx_wing = &aw->dp.wx_wefiww_buf_wing;
		spin_wock_bh(&wx_wing->idw_wock);
		msdu = idw_find(&wx_wing->bufs_idw, buf_id);
		if (unwikewy(!msdu)) {
			ath11k_wawn(ab, "fwame wx with invawid buf_id %d\n",
				    buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);
			continue;
		}

		idw_wemove(&wx_wing->bufs_idw, buf_id);
		spin_unwock_bh(&wx_wing->idw_wock);

		wxcb = ATH11K_SKB_WXCB(msdu);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 msdu->wen + skb_taiwwoom(msdu),
				 DMA_FWOM_DEVICE);

		num_buffs_weaped[mac_id]++;

		push_weason = FIEWD_GET(HAW_WEO_DEST_WING_INFO0_PUSH_WEASON,
					desc->info0);
		if (unwikewy(push_weason !=
			     HAW_WEO_DEST_WING_PUSH_WEASON_WOUTING_INSTWUCTION)) {
			dev_kfwee_skb_any(msdu);
			ab->soc_stats.haw_weo_ewwow[dp->weo_dst_wing[wing_id].wing_id]++;
			continue;
		}

		wxcb->is_fiwst_msdu = !!(desc->wx_msdu_info.info0 &
					 WX_MSDU_DESC_INFO0_FIWST_MSDU_IN_MPDU);
		wxcb->is_wast_msdu = !!(desc->wx_msdu_info.info0 &
					WX_MSDU_DESC_INFO0_WAST_MSDU_IN_MPDU);
		wxcb->is_continuation = !!(desc->wx_msdu_info.info0 &
					   WX_MSDU_DESC_INFO0_MSDU_CONTINUATION);
		wxcb->peew_id = FIEWD_GET(WX_MPDU_DESC_META_DATA_PEEW_ID,
					  desc->wx_mpdu_info.meta_data);
		wxcb->seq_no = FIEWD_GET(WX_MPDU_DESC_INFO0_SEQ_NUM,
					 desc->wx_mpdu_info.info0);
		wxcb->tid = FIEWD_GET(HAW_WEO_DEST_WING_INFO0_WX_QUEUE_NUM,
				      desc->info0);

		wxcb->mac_id = mac_id;
		__skb_queue_taiw(&msdu_wist[mac_id], msdu);

		if (wxcb->is_continuation) {
			done = fawse;
		} ewse {
			totaw_msdu_weaped++;
			done = twue;
		}

		if (totaw_msdu_weaped >= budget)
			bweak;
	}

	/* Hw might have updated the head pointew aftew we cached it.
	 * In this case, even though thewe awe entwies in the wing we'ww
	 * get wx_desc NUWW. Give the wead anothew twy with updated cached
	 * head pointew so that we can weap compwete MPDU in the cuwwent
	 * wx pwocessing.
	 */
	if (unwikewy(!done && ath11k_haw_swng_dst_num_fwee(ab, swng, twue))) {
		ath11k_haw_swng_access_end(ab, swng);
		goto twy_again;
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	if (unwikewy(!totaw_msdu_weaped))
		goto exit;

	fow (i = 0; i < ab->num_wadios; i++) {
		if (!num_buffs_weaped[i])
			continue;

		ath11k_dp_wx_pwocess_weceived_packets(ab, napi, &msdu_wist[i], i);

		aw = ab->pdevs[i].aw;
		wx_wing = &aw->dp.wx_wefiww_buf_wing;

		ath11k_dp_wxbufs_wepwenish(ab, i, wx_wing, num_buffs_weaped[i],
					   ab->hw_pawams.haw_pawams->wx_buf_wbm);
	}
exit:
	wetuwn totaw_msdu_weaped;
}

static void ath11k_dp_wx_update_peew_stats(stwuct ath11k_sta *awsta,
					   stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct ath11k_wx_peew_stats *wx_stats = awsta->wx_stats;
	u32 num_msdu;
	int i;

	if (!wx_stats)
		wetuwn;

	awsta->wssi_comb = ppdu_info->wssi_comb;
	ewma_avg_wssi_add(&awsta->avg_wssi, ppdu_info->wssi_comb);

	num_msdu = ppdu_info->tcp_msdu_count + ppdu_info->tcp_ack_msdu_count +
		   ppdu_info->udp_msdu_count + ppdu_info->othew_msdu_count;

	wx_stats->num_msdu += num_msdu;
	wx_stats->tcp_msdu_count += ppdu_info->tcp_msdu_count +
				    ppdu_info->tcp_ack_msdu_count;
	wx_stats->udp_msdu_count += ppdu_info->udp_msdu_count;
	wx_stats->othew_msdu_count += ppdu_info->othew_msdu_count;

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11A ||
	    ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11B) {
		ppdu_info->nss = 1;
		ppdu_info->mcs = HAW_WX_MAX_MCS;
		ppdu_info->tid = IEEE80211_NUM_TIDS;
	}

	if (ppdu_info->nss > 0 && ppdu_info->nss <= HAW_WX_MAX_NSS)
		wx_stats->nss_count[ppdu_info->nss - 1] += num_msdu;

	if (ppdu_info->mcs <= HAW_WX_MAX_MCS)
		wx_stats->mcs_count[ppdu_info->mcs] += num_msdu;

	if (ppdu_info->gi < HAW_WX_GI_MAX)
		wx_stats->gi_count[ppdu_info->gi] += num_msdu;

	if (ppdu_info->bw < HAW_WX_BW_MAX)
		wx_stats->bw_count[ppdu_info->bw] += num_msdu;

	if (ppdu_info->wdpc < HAW_WX_SU_MU_CODING_MAX)
		wx_stats->coding_count[ppdu_info->wdpc] += num_msdu;

	if (ppdu_info->tid <= IEEE80211_NUM_TIDS)
		wx_stats->tid_count[ppdu_info->tid] += num_msdu;

	if (ppdu_info->pweambwe_type < HAW_WX_PWEAMBWE_MAX)
		wx_stats->pweam_cnt[ppdu_info->pweambwe_type] += num_msdu;

	if (ppdu_info->weception_type < HAW_WX_WECEPTION_TYPE_MAX)
		wx_stats->weception_type[ppdu_info->weception_type] += num_msdu;

	if (ppdu_info->is_stbc)
		wx_stats->stbc_count += num_msdu;

	if (ppdu_info->beamfowmed)
		wx_stats->beamfowmed_count += num_msdu;

	if (ppdu_info->num_mpdu_fcs_ok > 1)
		wx_stats->ampdu_msdu_count += num_msdu;
	ewse
		wx_stats->non_ampdu_msdu_count += num_msdu;

	wx_stats->num_mpdu_fcs_ok += ppdu_info->num_mpdu_fcs_ok;
	wx_stats->num_mpdu_fcs_eww += ppdu_info->num_mpdu_fcs_eww;
	wx_stats->dcm_count += ppdu_info->dcm;
	wx_stats->wu_awwoc_cnt[ppdu_info->wu_awwoc] += num_msdu;

	awsta->wssi_comb = ppdu_info->wssi_comb;

	BUIWD_BUG_ON(AWWAY_SIZE(awsta->chain_signaw) >
			     AWWAY_SIZE(ppdu_info->wssi_chain_pwi20));

	fow (i = 0; i < AWWAY_SIZE(awsta->chain_signaw); i++)
		awsta->chain_signaw[i] = ppdu_info->wssi_chain_pwi20[i];

	wx_stats->wx_duwation += ppdu_info->wx_duwation;
	awsta->wx_duwation = wx_stats->wx_duwation;
}

static stwuct sk_buff *ath11k_dp_wx_awwoc_mon_status_buf(stwuct ath11k_base *ab,
							 stwuct dp_wxdma_wing *wx_wing,
							 int *buf_id)
{
	stwuct sk_buff *skb;
	dma_addw_t paddw;

	skb = dev_awwoc_skb(DP_WX_BUFFEW_SIZE +
			    DP_WX_BUFFEW_AWIGN_SIZE);

	if (!skb)
		goto faiw_awwoc_skb;

	if (!IS_AWIGNED((unsigned wong)skb->data,
			DP_WX_BUFFEW_AWIGN_SIZE)) {
		skb_puww(skb, PTW_AWIGN(skb->data, DP_WX_BUFFEW_AWIGN_SIZE) -
			 skb->data);
	}

	paddw = dma_map_singwe(ab->dev, skb->data,
			       skb->wen + skb_taiwwoom(skb),
			       DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(ab->dev, paddw)))
		goto faiw_fwee_skb;

	spin_wock_bh(&wx_wing->idw_wock);
	*buf_id = idw_awwoc(&wx_wing->bufs_idw, skb, 0,
			    wx_wing->bufs_max, GFP_ATOMIC);
	spin_unwock_bh(&wx_wing->idw_wock);
	if (*buf_id < 0)
		goto faiw_dma_unmap;

	ATH11K_SKB_WXCB(skb)->paddw = paddw;
	wetuwn skb;

faiw_dma_unmap:
	dma_unmap_singwe(ab->dev, paddw, skb->wen + skb_taiwwoom(skb),
			 DMA_FWOM_DEVICE);
faiw_fwee_skb:
	dev_kfwee_skb_any(skb);
faiw_awwoc_skb:
	wetuwn NUWW;
}

int ath11k_dp_wx_mon_status_bufs_wepwenish(stwuct ath11k_base *ab, int mac_id,
					   stwuct dp_wxdma_wing *wx_wing,
					   int weq_entwies,
					   enum haw_wx_buf_wetuwn_buf_managew mgw)
{
	stwuct haw_swng *swng;
	u32 *desc;
	stwuct sk_buff *skb;
	int num_fwee;
	int num_wemain;
	int buf_id;
	u32 cookie;
	dma_addw_t paddw;

	weq_entwies = min(weq_entwies, wx_wing->bufs_max);

	swng = &ab->haw.swng_wist[wx_wing->wefiww_buf_wing.wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	num_fwee = ath11k_haw_swng_swc_num_fwee(ab, swng, twue);

	weq_entwies = min(num_fwee, weq_entwies);
	num_wemain = weq_entwies;

	whiwe (num_wemain > 0) {
		skb = ath11k_dp_wx_awwoc_mon_status_buf(ab, wx_wing,
							&buf_id);
		if (!skb)
			bweak;
		paddw = ATH11K_SKB_WXCB(skb)->paddw;

		desc = ath11k_haw_swng_swc_get_next_entwy(ab, swng);
		if (!desc)
			goto faiw_desc_get;

		cookie = FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_BUF_ID, buf_id);

		num_wemain--;

		ath11k_haw_wx_buf_addw_info_set(desc, paddw, cookie, mgw);
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn weq_entwies - num_wemain;

faiw_desc_get:
	spin_wock_bh(&wx_wing->idw_wock);
	idw_wemove(&wx_wing->bufs_idw, buf_id);
	spin_unwock_bh(&wx_wing->idw_wock);
	dma_unmap_singwe(ab->dev, paddw, skb->wen + skb_taiwwoom(skb),
			 DMA_FWOM_DEVICE);
	dev_kfwee_skb_any(skb);
	ath11k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn weq_entwies - num_wemain;
}

#define ATH11K_DP_WX_FUWW_MON_PPDU_ID_WWAP 32535

static void
ath11k_dp_wx_mon_update_status_buf_state(stwuct ath11k_mon_data *pmon,
					 stwuct haw_twv_hdw *twv)
{
	stwuct haw_wx_ppdu_stawt *ppdu_stawt;
	u16 ppdu_id_diff, ppdu_id, twv_wen;
	u8 *ptw;

	/* PPDU id is pawt of second twv, move ptw to second twv */
	twv_wen = FIEWD_GET(HAW_TWV_HDW_WEN, twv->tw);
	ptw = (u8 *)twv;
	ptw += sizeof(*twv) + twv_wen;
	twv = (stwuct haw_twv_hdw *)ptw;

	if (FIEWD_GET(HAW_TWV_HDW_TAG, twv->tw) != HAW_WX_PPDU_STAWT)
		wetuwn;

	ptw += sizeof(*twv);
	ppdu_stawt = (stwuct haw_wx_ppdu_stawt *)ptw;
	ppdu_id = FIEWD_GET(HAW_WX_PPDU_STAWT_INFO0_PPDU_ID,
			    __we32_to_cpu(ppdu_stawt->info0));

	if (pmon->sw_mon_entwies.ppdu_id < ppdu_id) {
		pmon->buf_state = DP_MON_STATUS_WEAD;
		ppdu_id_diff = ppdu_id - pmon->sw_mon_entwies.ppdu_id;
		if (ppdu_id_diff > ATH11K_DP_WX_FUWW_MON_PPDU_ID_WWAP)
			pmon->buf_state = DP_MON_STATUS_WAG;
	} ewse if (pmon->sw_mon_entwies.ppdu_id > ppdu_id) {
		pmon->buf_state = DP_MON_STATUS_WAG;
		ppdu_id_diff = pmon->sw_mon_entwies.ppdu_id - ppdu_id;
		if (ppdu_id_diff > ATH11K_DP_WX_FUWW_MON_PPDU_ID_WWAP)
			pmon->buf_state = DP_MON_STATUS_WEAD;
	}
}

static int ath11k_dp_wx_weap_mon_status_wing(stwuct ath11k_base *ab, int mac_id,
					     int *budget, stwuct sk_buff_head *skb_wist)
{
	stwuct ath11k *aw;
	const stwuct ath11k_hw_haw_pawams *haw_pawams;
	stwuct ath11k_pdev_dp *dp;
	stwuct dp_wxdma_wing *wx_wing;
	stwuct ath11k_mon_data *pmon;
	stwuct haw_swng *swng;
	void *wx_mon_status_desc;
	stwuct sk_buff *skb;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct haw_twv_hdw *twv;
	u32 cookie;
	int buf_id, swng_id;
	dma_addw_t paddw;
	u8 wbm;
	int num_buffs_weaped = 0;

	aw = ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_pawams, mac_id)].aw;
	dp = &aw->dp;
	pmon = &dp->mon_data;
	swng_id = ath11k_hw_mac_id_to_swng_id(&ab->hw_pawams, mac_id);
	wx_wing = &dp->wx_mon_status_wefiww_wing[swng_id];

	swng = &ab->haw.swng_wist[wx_wing->wefiww_buf_wing.wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);
	whiwe (*budget) {
		*budget -= 1;
		wx_mon_status_desc =
			ath11k_haw_swng_swc_peek(ab, swng);
		if (!wx_mon_status_desc) {
			pmon->buf_state = DP_MON_STATUS_WEPWINISH;
			bweak;
		}

		ath11k_haw_wx_buf_addw_info_get(wx_mon_status_desc, &paddw,
						&cookie, &wbm);
		if (paddw) {
			buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID, cookie);

			spin_wock_bh(&wx_wing->idw_wock);
			skb = idw_find(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);

			if (!skb) {
				ath11k_wawn(ab, "wx monitow status with invawid buf_id %d\n",
					    buf_id);
				pmon->buf_state = DP_MON_STATUS_WEPWINISH;
				goto move_next;
			}

			wxcb = ATH11K_SKB_WXCB(skb);

			dma_sync_singwe_fow_cpu(ab->dev, wxcb->paddw,
						skb->wen + skb_taiwwoom(skb),
						DMA_FWOM_DEVICE);

			twv = (stwuct haw_twv_hdw *)skb->data;
			if (FIEWD_GET(HAW_TWV_HDW_TAG, twv->tw) !=
					HAW_WX_STATUS_BUFFEW_DONE) {
				ath11k_wawn(ab, "mon status DONE not set %wx, buf_id %d\n",
					    FIEWD_GET(HAW_TWV_HDW_TAG,
						      twv->tw), buf_id);
				/* If done status is missing, howd onto status
				 * wing untiw status is done fow this status
				 * wing buffew.
				 * Keep HP in mon_status_wing unchanged,
				 * and bweak fwom hewe.
				 * Check status fow same buffew fow next time
				 */
				pmon->buf_state = DP_MON_STATUS_NO_DMA;
				bweak;
			}

			spin_wock_bh(&wx_wing->idw_wock);
			idw_wemove(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);
			if (ab->hw_pawams.fuww_monitow_mode) {
				ath11k_dp_wx_mon_update_status_buf_state(pmon, twv);
				if (paddw == pmon->mon_status_paddw)
					pmon->buf_state = DP_MON_STATUS_MATCH;
			}

			dma_unmap_singwe(ab->dev, wxcb->paddw,
					 skb->wen + skb_taiwwoom(skb),
					 DMA_FWOM_DEVICE);

			__skb_queue_taiw(skb_wist, skb);
		} ewse {
			pmon->buf_state = DP_MON_STATUS_WEPWINISH;
		}
move_next:
		skb = ath11k_dp_wx_awwoc_mon_status_buf(ab, wx_wing,
							&buf_id);

		if (!skb) {
			haw_pawams = ab->hw_pawams.haw_pawams;
			ath11k_haw_wx_buf_addw_info_set(wx_mon_status_desc, 0, 0,
							haw_pawams->wx_buf_wbm);
			num_buffs_weaped++;
			bweak;
		}
		wxcb = ATH11K_SKB_WXCB(skb);

		cookie = FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_BUF_ID, buf_id);

		ath11k_haw_wx_buf_addw_info_set(wx_mon_status_desc, wxcb->paddw,
						cookie,
						ab->hw_pawams.haw_pawams->wx_buf_wbm);
		ath11k_haw_swng_swc_get_next_entwy(ab, swng);
		num_buffs_weaped++;
	}
	ath11k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn num_buffs_weaped;
}

static void ath11k_dp_wx_fwag_timew(stwuct timew_wist *timew)
{
	stwuct dp_wx_tid *wx_tid = fwom_timew(wx_tid, timew, fwag_timew);

	spin_wock_bh(&wx_tid->ab->base_wock);
	if (wx_tid->wast_fwag_no &&
	    wx_tid->wx_fwag_bitmap == GENMASK(wx_tid->wast_fwag_no, 0)) {
		spin_unwock_bh(&wx_tid->ab->base_wock);
		wetuwn;
	}
	ath11k_dp_wx_fwags_cweanup(wx_tid, twue);
	spin_unwock_bh(&wx_tid->ab->base_wock);
}

int ath11k_peew_wx_fwag_setup(stwuct ath11k *aw, const u8 *peew_mac, int vdev_id)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct cwypto_shash *tfm;
	stwuct ath11k_peew *peew;
	stwuct dp_wx_tid *wx_tid;
	int i;

	tfm = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(tfm)) {
		ath11k_wawn(ab, "faiwed to awwocate michaew_mic shash: %wd\n",
			    PTW_EWW(tfm));
		wetuwn PTW_EWW(tfm);
	}

	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find(ab, vdev_id, peew_mac);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew to set up fwagment info\n");
		spin_unwock_bh(&ab->base_wock);
		cwypto_fwee_shash(tfm);
		wetuwn -ENOENT;
	}

	fow (i = 0; i <= IEEE80211_NUM_TIDS; i++) {
		wx_tid = &peew->wx_tid[i];
		wx_tid->ab = ab;
		timew_setup(&wx_tid->fwag_timew, ath11k_dp_wx_fwag_timew, 0);
		skb_queue_head_init(&wx_tid->wx_fwags);
	}

	peew->tfm_mmic = tfm;
	peew->dp_setup_done = twue;
	spin_unwock_bh(&ab->base_wock);

	wetuwn 0;
}

static int ath11k_dp_wx_h_michaew_mic(stwuct cwypto_shash *tfm, u8 *key,
				      stwuct ieee80211_hdw *hdw, u8 *data,
				      size_t data_wen, u8 *mic)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	u8 mic_hdw[16] = {0};
	u8 tid = 0;
	int wet;

	if (!tfm)
		wetuwn -EINVAW;

	desc->tfm = tfm;

	wet = cwypto_shash_setkey(tfm, key, 8);
	if (wet)
		goto out;

	wet = cwypto_shash_init(desc);
	if (wet)
		goto out;

	/* TKIP MIC headew */
	memcpy(mic_hdw, ieee80211_get_DA(hdw), ETH_AWEN);
	memcpy(mic_hdw + ETH_AWEN, ieee80211_get_SA(hdw), ETH_AWEN);
	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		tid = ieee80211_get_tid(hdw);
	mic_hdw[12] = tid;

	wet = cwypto_shash_update(desc, mic_hdw, 16);
	if (wet)
		goto out;
	wet = cwypto_shash_update(desc, data, data_wen);
	if (wet)
		goto out;
	wet = cwypto_shash_finaw(desc, mic);
out:
	shash_desc_zewo(desc);
	wetuwn wet;
}

static int ath11k_dp_wx_h_vewify_tkip_mic(stwuct ath11k *aw, stwuct ath11k_peew *peew,
					  stwuct sk_buff *msdu)
{
	stwuct haw_wx_desc *wx_desc = (stwuct haw_wx_desc *)msdu->data;
	stwuct ieee80211_wx_status *wxs = IEEE80211_SKB_WXCB(msdu);
	stwuct ieee80211_key_conf *key_conf;
	stwuct ieee80211_hdw *hdw;
	u8 mic[IEEE80211_CCMP_MIC_WEN];
	int head_wen, taiw_wen, wet;
	size_t data_wen;
	u32 hdw_wen, haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;
	u8 *key, *data;
	u8 key_idx;

	if (ath11k_dp_wx_h_mpdu_stawt_enctype(aw->ab, wx_desc) !=
	    HAW_ENCWYPT_TYPE_TKIP_MIC)
		wetuwn 0;

	hdw = (stwuct ieee80211_hdw *)(msdu->data + haw_wx_desc_sz);
	hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
	head_wen = hdw_wen + haw_wx_desc_sz + IEEE80211_TKIP_IV_WEN;
	taiw_wen = IEEE80211_CCMP_MIC_WEN + IEEE80211_TKIP_ICV_WEN + FCS_WEN;

	if (!is_muwticast_ethew_addw(hdw->addw1))
		key_idx = peew->ucast_keyidx;
	ewse
		key_idx = peew->mcast_keyidx;

	key_conf = peew->keys[key_idx];

	data = msdu->data + head_wen;
	data_wen = msdu->wen - head_wen - taiw_wen;
	key = &key_conf->key[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY];

	wet = ath11k_dp_wx_h_michaew_mic(peew->tfm_mmic, key, hdw, data, data_wen, mic);
	if (wet || memcmp(mic, data + data_wen, IEEE80211_CCMP_MIC_WEN))
		goto mic_faiw;

	wetuwn 0;

mic_faiw:
	(ATH11K_SKB_WXCB(msdu))->is_fiwst_msdu = twue;
	(ATH11K_SKB_WXCB(msdu))->is_wast_msdu = twue;

	wxs->fwag |= WX_FWAG_MMIC_EWWOW | WX_FWAG_MMIC_STWIPPED |
		    WX_FWAG_IV_STWIPPED | WX_FWAG_DECWYPTED;
	skb_puww(msdu, haw_wx_desc_sz);

	ath11k_dp_wx_h_ppdu(aw, wx_desc, wxs);
	ath11k_dp_wx_h_undecap(aw, msdu, wx_desc,
			       HAW_ENCWYPT_TYPE_TKIP_MIC, wxs, twue);
	ieee80211_wx(aw->hw, msdu);
	wetuwn -EINVAW;
}

static void ath11k_dp_wx_h_undecap_fwag(stwuct ath11k *aw, stwuct sk_buff *msdu,
					enum haw_encwypt_type enctype, u32 fwags)
{
	stwuct ieee80211_hdw *hdw;
	size_t hdw_wen;
	size_t cwypto_wen;
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	if (!fwags)
		wetuwn;

	hdw = (stwuct ieee80211_hdw *)(msdu->data + haw_wx_desc_sz);

	if (fwags & WX_FWAG_MIC_STWIPPED)
		skb_twim(msdu, msdu->wen -
			 ath11k_dp_wx_cwypto_mic_wen(aw, enctype));

	if (fwags & WX_FWAG_ICV_STWIPPED)
		skb_twim(msdu, msdu->wen -
			 ath11k_dp_wx_cwypto_icv_wen(aw, enctype));

	if (fwags & WX_FWAG_IV_STWIPPED) {
		hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
		cwypto_wen = ath11k_dp_wx_cwypto_pawam_wen(aw, enctype);

		memmove((void *)msdu->data + haw_wx_desc_sz + cwypto_wen,
			(void *)msdu->data + haw_wx_desc_sz, hdw_wen);
		skb_puww(msdu, cwypto_wen);
	}
}

static int ath11k_dp_wx_h_defwag(stwuct ath11k *aw,
				 stwuct ath11k_peew *peew,
				 stwuct dp_wx_tid *wx_tid,
				 stwuct sk_buff **defwag_skb)
{
	stwuct haw_wx_desc *wx_desc;
	stwuct sk_buff *skb, *fiwst_fwag, *wast_fwag;
	stwuct ieee80211_hdw *hdw;
	stwuct wx_attention *wx_attention;
	enum haw_encwypt_type enctype;
	boow is_decwypted = fawse;
	int msdu_wen = 0;
	int extwa_space;
	u32 fwags, haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	fiwst_fwag = skb_peek(&wx_tid->wx_fwags);
	wast_fwag = skb_peek_taiw(&wx_tid->wx_fwags);

	skb_queue_wawk(&wx_tid->wx_fwags, skb) {
		fwags = 0;
		wx_desc = (stwuct haw_wx_desc *)skb->data;
		hdw = (stwuct ieee80211_hdw *)(skb->data + haw_wx_desc_sz);

		enctype = ath11k_dp_wx_h_mpdu_stawt_enctype(aw->ab, wx_desc);
		if (enctype != HAW_ENCWYPT_TYPE_OPEN) {
			wx_attention = ath11k_dp_wx_get_attention(aw->ab, wx_desc);
			is_decwypted = ath11k_dp_wx_h_attn_is_decwypted(wx_attention);
		}

		if (is_decwypted) {
			if (skb != fiwst_fwag)
				fwags |=  WX_FWAG_IV_STWIPPED;
			if (skb != wast_fwag)
				fwags |= WX_FWAG_ICV_STWIPPED |
					 WX_FWAG_MIC_STWIPPED;
		}

		/* WX fwagments awe awways waw packets */
		if (skb != wast_fwag)
			skb_twim(skb, skb->wen - FCS_WEN);
		ath11k_dp_wx_h_undecap_fwag(aw, skb, enctype, fwags);

		if (skb != fiwst_fwag)
			skb_puww(skb, haw_wx_desc_sz +
				      ieee80211_hdwwen(hdw->fwame_contwow));
		msdu_wen += skb->wen;
	}

	extwa_space = msdu_wen - (DP_WX_BUFFEW_SIZE + skb_taiwwoom(fiwst_fwag));
	if (extwa_space > 0 &&
	    (pskb_expand_head(fiwst_fwag, 0, extwa_space, GFP_ATOMIC) < 0))
		wetuwn -ENOMEM;

	__skb_unwink(fiwst_fwag, &wx_tid->wx_fwags);
	whiwe ((skb = __skb_dequeue(&wx_tid->wx_fwags))) {
		skb_put_data(fiwst_fwag, skb->data, skb->wen);
		dev_kfwee_skb_any(skb);
	}

	hdw = (stwuct ieee80211_hdw *)(fiwst_fwag->data + haw_wx_desc_sz);
	hdw->fwame_contwow &= ~__cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS);
	ATH11K_SKB_WXCB(fiwst_fwag)->is_fwag = 1;

	if (ath11k_dp_wx_h_vewify_tkip_mic(aw, peew, fiwst_fwag))
		fiwst_fwag = NUWW;

	*defwag_skb = fiwst_fwag;
	wetuwn 0;
}

static int ath11k_dp_wx_h_defwag_weo_weinject(stwuct ath11k *aw, stwuct dp_wx_tid *wx_tid,
					      stwuct sk_buff *defwag_skb)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct dp_wxdma_wing *wx_wefiww_wing = &dp->wx_wefiww_buf_wing;
	stwuct haw_wx_desc *wx_desc = (stwuct haw_wx_desc *)defwag_skb->data;
	stwuct haw_weo_entwance_wing *weo_ent_wing;
	stwuct haw_weo_dest_wing *weo_dest_wing;
	stwuct dp_wink_desc_bank *wink_desc_banks;
	stwuct haw_wx_msdu_wink *msdu_wink;
	stwuct haw_wx_msdu_detaiws *msdu0;
	stwuct haw_swng *swng;
	dma_addw_t paddw;
	u32 desc_bank, msdu_info, mpdu_info;
	u32 dst_idx, cookie, haw_wx_desc_sz;
	int wet, buf_id;

	haw_wx_desc_sz = ab->hw_pawams.haw_desc_sz;
	wink_desc_banks = ab->dp.wink_desc_banks;
	weo_dest_wing = wx_tid->dst_wing_desc;

	ath11k_haw_wx_weo_ent_paddw_get(ab, weo_dest_wing, &paddw, &desc_bank);
	msdu_wink = (stwuct haw_wx_msdu_wink *)(wink_desc_banks[desc_bank].vaddw +
			(paddw - wink_desc_banks[desc_bank].paddw));
	msdu0 = &msdu_wink->msdu_wink[0];
	dst_idx = FIEWD_GET(WX_MSDU_DESC_INFO0_WEO_DEST_IND, msdu0->wx_msdu_info.info0);
	memset(msdu0, 0, sizeof(*msdu0));

	msdu_info = FIEWD_PWEP(WX_MSDU_DESC_INFO0_FIWST_MSDU_IN_MPDU, 1) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_WAST_MSDU_IN_MPDU, 1) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_MSDU_CONTINUATION, 0) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_MSDU_WENGTH,
			       defwag_skb->wen - haw_wx_desc_sz) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_WEO_DEST_IND, dst_idx) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_VAWID_SA, 1) |
		    FIEWD_PWEP(WX_MSDU_DESC_INFO0_VAWID_DA, 1);
	msdu0->wx_msdu_info.info0 = msdu_info;

	/* change msdu wen in haw wx desc */
	ath11k_dp_wxdesc_set_msdu_wen(ab, wx_desc, defwag_skb->wen - haw_wx_desc_sz);

	paddw = dma_map_singwe(ab->dev, defwag_skb->data,
			       defwag_skb->wen + skb_taiwwoom(defwag_skb),
			       DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ab->dev, paddw))
		wetuwn -ENOMEM;

	spin_wock_bh(&wx_wefiww_wing->idw_wock);
	buf_id = idw_awwoc(&wx_wefiww_wing->bufs_idw, defwag_skb, 0,
			   wx_wefiww_wing->bufs_max * 3, GFP_ATOMIC);
	spin_unwock_bh(&wx_wefiww_wing->idw_wock);
	if (buf_id < 0) {
		wet = -ENOMEM;
		goto eww_unmap_dma;
	}

	ATH11K_SKB_WXCB(defwag_skb)->paddw = paddw;
	cookie = FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_PDEV_ID, dp->mac_id) |
		 FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_BUF_ID, buf_id);

	ath11k_haw_wx_buf_addw_info_set(msdu0, paddw, cookie,
					ab->hw_pawams.haw_pawams->wx_buf_wbm);

	/* Fiww mpdu detaiws into weo entwance wing */
	swng = &ab->haw.swng_wist[ab->dp.weo_weinject_wing.wing_id];

	spin_wock_bh(&swng->wock);
	ath11k_haw_swng_access_begin(ab, swng);

	weo_ent_wing = (stwuct haw_weo_entwance_wing *)
			ath11k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!weo_ent_wing) {
		ath11k_haw_swng_access_end(ab, swng);
		spin_unwock_bh(&swng->wock);
		wet = -ENOSPC;
		goto eww_fwee_idw;
	}
	memset(weo_ent_wing, 0, sizeof(*weo_ent_wing));

	ath11k_haw_wx_weo_ent_paddw_get(ab, weo_dest_wing, &paddw, &desc_bank);
	ath11k_haw_wx_buf_addw_info_set(weo_ent_wing, paddw, desc_bank,
					HAW_WX_BUF_WBM_WBM_IDWE_DESC_WIST);

	mpdu_info = FIEWD_PWEP(WX_MPDU_DESC_INFO0_MSDU_COUNT, 1) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_SEQ_NUM, wx_tid->cuw_sn) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_FWAG_FWAG, 0) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_VAWID_SA, 1) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_VAWID_DA, 1) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_WAW_MPDU, 1) |
		    FIEWD_PWEP(WX_MPDU_DESC_INFO0_VAWID_PN, 1);

	weo_ent_wing->wx_mpdu_info.info0 = mpdu_info;
	weo_ent_wing->wx_mpdu_info.meta_data = weo_dest_wing->wx_mpdu_info.meta_data;
	weo_ent_wing->queue_addw_wo = weo_dest_wing->queue_addw_wo;
	weo_ent_wing->info0 = FIEWD_PWEP(HAW_WEO_ENTW_WING_INFO0_QUEUE_ADDW_HI,
					 FIEWD_GET(HAW_WEO_DEST_WING_INFO0_QUEUE_ADDW_HI,
						   weo_dest_wing->info0)) |
			      FIEWD_PWEP(HAW_WEO_ENTW_WING_INFO0_DEST_IND, dst_idx);
	ath11k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn 0;

eww_fwee_idw:
	spin_wock_bh(&wx_wefiww_wing->idw_wock);
	idw_wemove(&wx_wefiww_wing->bufs_idw, buf_id);
	spin_unwock_bh(&wx_wefiww_wing->idw_wock);
eww_unmap_dma:
	dma_unmap_singwe(ab->dev, paddw, defwag_skb->wen + skb_taiwwoom(defwag_skb),
			 DMA_TO_DEVICE);
	wetuwn wet;
}

static int ath11k_dp_wx_h_cmp_fwags(stwuct ath11k *aw,
				    stwuct sk_buff *a, stwuct sk_buff *b)
{
	int fwag1, fwag2;

	fwag1 = ath11k_dp_wx_h_mpdu_stawt_fwag_no(aw->ab, a);
	fwag2 = ath11k_dp_wx_h_mpdu_stawt_fwag_no(aw->ab, b);

	wetuwn fwag1 - fwag2;
}

static void ath11k_dp_wx_h_sowt_fwags(stwuct ath11k *aw,
				      stwuct sk_buff_head *fwag_wist,
				      stwuct sk_buff *cuw_fwag)
{
	stwuct sk_buff *skb;
	int cmp;

	skb_queue_wawk(fwag_wist, skb) {
		cmp = ath11k_dp_wx_h_cmp_fwags(aw, skb, cuw_fwag);
		if (cmp < 0)
			continue;
		__skb_queue_befowe(fwag_wist, skb, cuw_fwag);
		wetuwn;
	}
	__skb_queue_taiw(fwag_wist, cuw_fwag);
}

static u64 ath11k_dp_wx_h_get_pn(stwuct ath11k *aw, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	u64 pn = 0;
	u8 *ehdw;
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	hdw = (stwuct ieee80211_hdw *)(skb->data + haw_wx_desc_sz);
	ehdw = skb->data + haw_wx_desc_sz + ieee80211_hdwwen(hdw->fwame_contwow);

	pn = ehdw[0];
	pn |= (u64)ehdw[1] << 8;
	pn |= (u64)ehdw[4] << 16;
	pn |= (u64)ehdw[5] << 24;
	pn |= (u64)ehdw[6] << 32;
	pn |= (u64)ehdw[7] << 40;

	wetuwn pn;
}

static boow
ath11k_dp_wx_h_defwag_vawidate_incw_pn(stwuct ath11k *aw, stwuct dp_wx_tid *wx_tid)
{
	enum haw_encwypt_type encwypt_type;
	stwuct sk_buff *fiwst_fwag, *skb;
	stwuct haw_wx_desc *desc;
	u64 wast_pn;
	u64 cuw_pn;

	fiwst_fwag = skb_peek(&wx_tid->wx_fwags);
	desc = (stwuct haw_wx_desc *)fiwst_fwag->data;

	encwypt_type = ath11k_dp_wx_h_mpdu_stawt_enctype(aw->ab, desc);
	if (encwypt_type != HAW_ENCWYPT_TYPE_CCMP_128 &&
	    encwypt_type != HAW_ENCWYPT_TYPE_CCMP_256 &&
	    encwypt_type != HAW_ENCWYPT_TYPE_GCMP_128 &&
	    encwypt_type != HAW_ENCWYPT_TYPE_AES_GCMP_256)
		wetuwn twue;

	wast_pn = ath11k_dp_wx_h_get_pn(aw, fiwst_fwag);
	skb_queue_wawk(&wx_tid->wx_fwags, skb) {
		if (skb == fiwst_fwag)
			continue;

		cuw_pn = ath11k_dp_wx_h_get_pn(aw, skb);
		if (cuw_pn != wast_pn + 1)
			wetuwn fawse;
		wast_pn = cuw_pn;
	}
	wetuwn twue;
}

static int ath11k_dp_wx_fwag_h_mpdu(stwuct ath11k *aw,
				    stwuct sk_buff *msdu,
				    u32 *wing_desc)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct haw_wx_desc *wx_desc;
	stwuct ath11k_peew *peew;
	stwuct dp_wx_tid *wx_tid;
	stwuct sk_buff *defwag_skb = NUWW;
	u32 peew_id;
	u16 seqno, fwag_no;
	u8 tid;
	int wet = 0;
	boow mowe_fwags;
	boow is_mcbc;

	wx_desc = (stwuct haw_wx_desc *)msdu->data;
	peew_id = ath11k_dp_wx_h_mpdu_stawt_peew_id(aw->ab, wx_desc);
	tid = ath11k_dp_wx_h_mpdu_stawt_tid(aw->ab, wx_desc);
	seqno = ath11k_dp_wx_h_mpdu_stawt_seq_no(aw->ab, wx_desc);
	fwag_no = ath11k_dp_wx_h_mpdu_stawt_fwag_no(aw->ab, msdu);
	mowe_fwags = ath11k_dp_wx_h_mpdu_stawt_mowe_fwags(aw->ab, msdu);
	is_mcbc = ath11k_dp_wx_h_attn_is_mcbc(aw->ab, wx_desc);

	/* Muwticast/Bwoadcast fwagments awe not expected */
	if (is_mcbc)
		wetuwn -EINVAW;

	if (!ath11k_dp_wx_h_mpdu_stawt_seq_ctww_vawid(aw->ab, wx_desc) ||
	    !ath11k_dp_wx_h_mpdu_stawt_fc_vawid(aw->ab, wx_desc) ||
	    tid > IEEE80211_NUM_TIDS)
		wetuwn -EINVAW;

	/* weceived unfwagmented packet in weo
	 * exception wing, this shouwdn't happen
	 * as these packets typicawwy come fwom
	 * weo2sw swngs.
	 */
	if (WAWN_ON_ONCE(!fwag_no && !mowe_fwags))
		wetuwn -EINVAW;

	spin_wock_bh(&ab->base_wock);
	peew = ath11k_peew_find_by_id(ab, peew_id);
	if (!peew) {
		ath11k_wawn(ab, "faiwed to find the peew to de-fwagment weceived fwagment peew_id %d\n",
			    peew_id);
		wet = -ENOENT;
		goto out_unwock;
	}
	if (!peew->dp_setup_done) {
		ath11k_wawn(ab, "The peew %pM [%d] has uninitiawized datapath\n",
			    peew->addw, peew_id);
		wet = -ENOENT;
		goto out_unwock;
	}

	wx_tid = &peew->wx_tid[tid];

	if ((!skb_queue_empty(&wx_tid->wx_fwags) && seqno != wx_tid->cuw_sn) ||
	    skb_queue_empty(&wx_tid->wx_fwags)) {
		/* Fwush stowed fwagments and stawt a new sequence */
		ath11k_dp_wx_fwags_cweanup(wx_tid, twue);
		wx_tid->cuw_sn = seqno;
	}

	if (wx_tid->wx_fwag_bitmap & BIT(fwag_no)) {
		/* Fwagment awweady pwesent */
		wet = -EINVAW;
		goto out_unwock;
	}

	if (!wx_tid->wx_fwag_bitmap || (fwag_no > __fws(wx_tid->wx_fwag_bitmap)))
		__skb_queue_taiw(&wx_tid->wx_fwags, msdu);
	ewse
		ath11k_dp_wx_h_sowt_fwags(aw, &wx_tid->wx_fwags, msdu);

	wx_tid->wx_fwag_bitmap |= BIT(fwag_no);
	if (!mowe_fwags)
		wx_tid->wast_fwag_no = fwag_no;

	if (fwag_no == 0) {
		wx_tid->dst_wing_desc = kmemdup(wing_desc,
						sizeof(*wx_tid->dst_wing_desc),
						GFP_ATOMIC);
		if (!wx_tid->dst_wing_desc) {
			wet = -ENOMEM;
			goto out_unwock;
		}
	} ewse {
		ath11k_dp_wx_wink_desc_wetuwn(ab, wing_desc,
					      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
	}

	if (!wx_tid->wast_fwag_no ||
	    wx_tid->wx_fwag_bitmap != GENMASK(wx_tid->wast_fwag_no, 0)) {
		mod_timew(&wx_tid->fwag_timew, jiffies +
					       ATH11K_DP_WX_FWAGMENT_TIMEOUT_MS);
		goto out_unwock;
	}

	spin_unwock_bh(&ab->base_wock);
	dew_timew_sync(&wx_tid->fwag_timew);
	spin_wock_bh(&ab->base_wock);

	peew = ath11k_peew_find_by_id(ab, peew_id);
	if (!peew)
		goto eww_fwags_cweanup;

	if (!ath11k_dp_wx_h_defwag_vawidate_incw_pn(aw, wx_tid))
		goto eww_fwags_cweanup;

	if (ath11k_dp_wx_h_defwag(aw, peew, wx_tid, &defwag_skb))
		goto eww_fwags_cweanup;

	if (!defwag_skb)
		goto eww_fwags_cweanup;

	if (ath11k_dp_wx_h_defwag_weo_weinject(aw, wx_tid, defwag_skb))
		goto eww_fwags_cweanup;

	ath11k_dp_wx_fwags_cweanup(wx_tid, fawse);
	goto out_unwock;

eww_fwags_cweanup:
	dev_kfwee_skb_any(defwag_skb);
	ath11k_dp_wx_fwags_cweanup(wx_tid, twue);
out_unwock:
	spin_unwock_bh(&ab->base_wock);
	wetuwn wet;
}

static int
ath11k_dp_pwocess_wx_eww_buf(stwuct ath11k *aw, u32 *wing_desc, int buf_id, boow dwop)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct dp_wxdma_wing *wx_wing = &dp->wx_wefiww_buf_wing;
	stwuct sk_buff *msdu;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct haw_wx_desc *wx_desc;
	u8 *hdw_status;
	u16 msdu_wen;
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	spin_wock_bh(&wx_wing->idw_wock);
	msdu = idw_find(&wx_wing->bufs_idw, buf_id);
	if (!msdu) {
		ath11k_wawn(aw->ab, "wx eww buf with invawid buf_id %d\n",
			    buf_id);
		spin_unwock_bh(&wx_wing->idw_wock);
		wetuwn -EINVAW;
	}

	idw_wemove(&wx_wing->bufs_idw, buf_id);
	spin_unwock_bh(&wx_wing->idw_wock);

	wxcb = ATH11K_SKB_WXCB(msdu);
	dma_unmap_singwe(aw->ab->dev, wxcb->paddw,
			 msdu->wen + skb_taiwwoom(msdu),
			 DMA_FWOM_DEVICE);

	if (dwop) {
		dev_kfwee_skb_any(msdu);
		wetuwn 0;
	}

	wcu_wead_wock();
	if (!wcu_dewefewence(aw->ab->pdevs_active[aw->pdev_idx])) {
		dev_kfwee_skb_any(msdu);
		goto exit;
	}

	if (test_bit(ATH11K_CAC_WUNNING, &aw->dev_fwags)) {
		dev_kfwee_skb_any(msdu);
		goto exit;
	}

	wx_desc = (stwuct haw_wx_desc *)msdu->data;
	msdu_wen = ath11k_dp_wx_h_msdu_stawt_msdu_wen(aw->ab, wx_desc);
	if ((msdu_wen + haw_wx_desc_sz) > DP_WX_BUFFEW_SIZE) {
		hdw_status = ath11k_dp_wx_h_80211_hdw(aw->ab, wx_desc);
		ath11k_wawn(aw->ab, "invawid msdu weng %u", msdu_wen);
		ath11k_dbg_dump(aw->ab, ATH11K_DBG_DATA, NUWW, "", hdw_status,
				sizeof(stwuct ieee80211_hdw));
		ath11k_dbg_dump(aw->ab, ATH11K_DBG_DATA, NUWW, "", wx_desc,
				sizeof(stwuct haw_wx_desc));
		dev_kfwee_skb_any(msdu);
		goto exit;
	}

	skb_put(msdu, haw_wx_desc_sz + msdu_wen);

	if (ath11k_dp_wx_fwag_h_mpdu(aw, msdu, wing_desc)) {
		dev_kfwee_skb_any(msdu);
		ath11k_dp_wx_wink_desc_wetuwn(aw->ab, wing_desc,
					      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
	}
exit:
	wcu_wead_unwock();
	wetuwn 0;
}

int ath11k_dp_pwocess_wx_eww(stwuct ath11k_base *ab, stwuct napi_stwuct *napi,
			     int budget)
{
	u32 msdu_cookies[HAW_NUM_WX_MSDUS_PEW_WINK_DESC];
	stwuct dp_wink_desc_bank *wink_desc_banks;
	enum haw_wx_buf_wetuwn_buf_managew wbm;
	int tot_n_bufs_weaped, quota, wet, i;
	int n_bufs_weaped[MAX_WADIOS] = {0};
	stwuct dp_wxdma_wing *wx_wing;
	stwuct dp_swng *weo_except;
	u32 desc_bank, num_msdus;
	stwuct haw_swng *swng;
	stwuct ath11k_dp *dp;
	void *wink_desc_va;
	int buf_id, mac_id;
	stwuct ath11k *aw;
	dma_addw_t paddw;
	u32 *desc;
	boow is_fwag;
	u8 dwop = 0;

	tot_n_bufs_weaped = 0;
	quota = budget;

	dp = &ab->dp;
	weo_except = &dp->weo_except_wing;
	wink_desc_banks = dp->wink_desc_banks;

	swng = &ab->haw.swng_wist[weo_except->wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	whiwe (budget &&
	       (desc = ath11k_haw_swng_dst_get_next_entwy(ab, swng))) {
		stwuct haw_weo_dest_wing *weo_desc = (stwuct haw_weo_dest_wing *)desc;

		ab->soc_stats.eww_wing_pkts++;
		wet = ath11k_haw_desc_weo_pawse_eww(ab, desc, &paddw,
						    &desc_bank);
		if (wet) {
			ath11k_wawn(ab, "faiwed to pawse ewwow weo desc %d\n",
				    wet);
			continue;
		}
		wink_desc_va = wink_desc_banks[desc_bank].vaddw +
			       (paddw - wink_desc_banks[desc_bank].paddw);
		ath11k_haw_wx_msdu_wink_info_get(wink_desc_va, &num_msdus, msdu_cookies,
						 &wbm);
		if (wbm != HAW_WX_BUF_WBM_WBM_IDWE_DESC_WIST &&
		    wbm != HAW_WX_BUF_WBM_SW3_BM) {
			ab->soc_stats.invawid_wbm++;
			ath11k_wawn(ab, "invawid wetuwn buffew managew %d\n", wbm);
			ath11k_dp_wx_wink_desc_wetuwn(ab, desc,
						      HAW_WBM_WEW_BM_ACT_WEW_MSDU);
			continue;
		}

		is_fwag = !!(weo_desc->wx_mpdu_info.info0 & WX_MPDU_DESC_INFO0_FWAG_FWAG);

		/* Pwocess onwy wx fwagments with one msdu pew wink desc bewow, and dwop
		 * msdu's indicated due to ewwow weasons.
		 */
		if (!is_fwag || num_msdus > 1) {
			dwop = 1;
			/* Wetuwn the wink desc back to wbm idwe wist */
			ath11k_dp_wx_wink_desc_wetuwn(ab, desc,
						      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
		}

		fow (i = 0; i < num_msdus; i++) {
			buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID,
					   msdu_cookies[i]);

			mac_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_PDEV_ID,
					   msdu_cookies[i]);

			aw = ab->pdevs[mac_id].aw;

			if (!ath11k_dp_pwocess_wx_eww_buf(aw, desc, buf_id, dwop)) {
				n_bufs_weaped[mac_id]++;
				tot_n_bufs_weaped++;
			}
		}

		if (tot_n_bufs_weaped >= quota) {
			tot_n_bufs_weaped = quota;
			goto exit;
		}

		budget = quota - tot_n_bufs_weaped;
	}

exit:
	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	fow (i = 0; i <  ab->num_wadios; i++) {
		if (!n_bufs_weaped[i])
			continue;

		aw = ab->pdevs[i].aw;
		wx_wing = &aw->dp.wx_wefiww_buf_wing;

		ath11k_dp_wxbufs_wepwenish(ab, i, wx_wing, n_bufs_weaped[i],
					   ab->hw_pawams.haw_pawams->wx_buf_wbm);
	}

	wetuwn tot_n_bufs_weaped;
}

static void ath11k_dp_wx_nuww_q_desc_sg_dwop(stwuct ath11k *aw,
					     int msdu_wen,
					     stwuct sk_buff_head *msdu_wist)
{
	stwuct sk_buff *skb, *tmp;
	stwuct ath11k_skb_wxcb *wxcb;
	int n_buffs;

	n_buffs = DIV_WOUND_UP(msdu_wen,
			       (DP_WX_BUFFEW_SIZE - aw->ab->hw_pawams.haw_desc_sz));

	skb_queue_wawk_safe(msdu_wist, skb, tmp) {
		wxcb = ATH11K_SKB_WXCB(skb);
		if (wxcb->eww_wew_swc == HAW_WBM_WEW_SWC_MODUWE_WEO &&
		    wxcb->eww_code == HAW_WEO_DEST_WING_EWWOW_CODE_DESC_ADDW_ZEWO) {
			if (!n_buffs)
				bweak;
			__skb_unwink(skb, msdu_wist);
			dev_kfwee_skb_any(skb);
			n_buffs--;
		}
	}
}

static int ath11k_dp_wx_h_nuww_q_desc(stwuct ath11k *aw, stwuct sk_buff *msdu,
				      stwuct ieee80211_wx_status *status,
				      stwuct sk_buff_head *msdu_wist)
{
	u16 msdu_wen;
	stwuct haw_wx_desc *desc = (stwuct haw_wx_desc *)msdu->data;
	stwuct wx_attention *wx_attention;
	u8 w3pad_bytes;
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	msdu_wen = ath11k_dp_wx_h_msdu_stawt_msdu_wen(aw->ab, desc);

	if (!wxcb->is_fwag && ((msdu_wen + haw_wx_desc_sz) > DP_WX_BUFFEW_SIZE)) {
		/* Fiwst buffew wiww be fweed by the cawwew, so deduct it's wength */
		msdu_wen = msdu_wen - (DP_WX_BUFFEW_SIZE - haw_wx_desc_sz);
		ath11k_dp_wx_nuww_q_desc_sg_dwop(aw, msdu_wen, msdu_wist);
		wetuwn -EINVAW;
	}

	wx_attention = ath11k_dp_wx_get_attention(aw->ab, desc);
	if (!ath11k_dp_wx_h_attn_msdu_done(wx_attention)) {
		ath11k_wawn(aw->ab,
			    "msdu_done bit not set in nuww_q_des pwocessing\n");
		__skb_queue_puwge(msdu_wist);
		wetuwn -EIO;
	}

	/* Handwe NUWW queue descwiptow viowations awising out a missing
	 * WEO queue fow a given peew ow a given TID. This typicawwy
	 * may happen if a packet is weceived on a QOS enabwed TID befowe the
	 * ADDBA negotiation fow that TID, when the TID queue is setup. Ow
	 * it may awso happen fow MC/BC fwames if they awe not wouted to the
	 * non-QOS TID queue, in the absence of any othew defauwt TID queue.
	 * This ewwow can show up both in a WEO destination ow WBM wewease wing.
	 */

	wxcb->is_fiwst_msdu = ath11k_dp_wx_h_msdu_end_fiwst_msdu(aw->ab, desc);
	wxcb->is_wast_msdu = ath11k_dp_wx_h_msdu_end_wast_msdu(aw->ab, desc);

	if (wxcb->is_fwag) {
		skb_puww(msdu, haw_wx_desc_sz);
	} ewse {
		w3pad_bytes = ath11k_dp_wx_h_msdu_end_w3pad(aw->ab, desc);

		if ((haw_wx_desc_sz + w3pad_bytes + msdu_wen) > DP_WX_BUFFEW_SIZE)
			wetuwn -EINVAW;

		skb_put(msdu, haw_wx_desc_sz + w3pad_bytes + msdu_wen);
		skb_puww(msdu, haw_wx_desc_sz + w3pad_bytes);
	}
	ath11k_dp_wx_h_ppdu(aw, desc, status);

	ath11k_dp_wx_h_mpdu(aw, msdu, desc, status);

	wxcb->tid = ath11k_dp_wx_h_mpdu_stawt_tid(aw->ab, desc);

	/* Pwease note that cawwew wiww having the access to msdu and compweting
	 * wx with mac80211. Need not wowwy about cweaning up amsdu_wist.
	 */

	wetuwn 0;
}

static boow ath11k_dp_wx_h_weo_eww(stwuct ath11k *aw, stwuct sk_buff *msdu,
				   stwuct ieee80211_wx_status *status,
				   stwuct sk_buff_head *msdu_wist)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	boow dwop = fawse;

	aw->ab->soc_stats.weo_ewwow[wxcb->eww_code]++;

	switch (wxcb->eww_code) {
	case HAW_WEO_DEST_WING_EWWOW_CODE_DESC_ADDW_ZEWO:
		if (ath11k_dp_wx_h_nuww_q_desc(aw, msdu, status, msdu_wist))
			dwop = twue;
		bweak;
	case HAW_WEO_DEST_WING_EWWOW_CODE_PN_CHECK_FAIWED:
		/* TODO: Do not dwop PN faiwed packets in the dwivew;
		 * instead, it is good to dwop such packets in mac80211
		 * aftew incwementing the wepway countews.
		 */
		fawwthwough;
	defauwt:
		/* TODO: Weview othew ewwows and pwocess them to mac80211
		 * as appwopwiate.
		 */
		dwop = twue;
		bweak;
	}

	wetuwn dwop;
}

static void ath11k_dp_wx_h_tkip_mic_eww(stwuct ath11k *aw, stwuct sk_buff *msdu,
					stwuct ieee80211_wx_status *status)
{
	u16 msdu_wen;
	stwuct haw_wx_desc *desc = (stwuct haw_wx_desc *)msdu->data;
	u8 w3pad_bytes;
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	u32 haw_wx_desc_sz = aw->ab->hw_pawams.haw_desc_sz;

	wxcb->is_fiwst_msdu = ath11k_dp_wx_h_msdu_end_fiwst_msdu(aw->ab, desc);
	wxcb->is_wast_msdu = ath11k_dp_wx_h_msdu_end_wast_msdu(aw->ab, desc);

	w3pad_bytes = ath11k_dp_wx_h_msdu_end_w3pad(aw->ab, desc);
	msdu_wen = ath11k_dp_wx_h_msdu_stawt_msdu_wen(aw->ab, desc);
	skb_put(msdu, haw_wx_desc_sz + w3pad_bytes + msdu_wen);
	skb_puww(msdu, haw_wx_desc_sz + w3pad_bytes);

	ath11k_dp_wx_h_ppdu(aw, desc, status);

	status->fwag |= (WX_FWAG_MMIC_STWIPPED | WX_FWAG_MMIC_EWWOW |
			 WX_FWAG_DECWYPTED);

	ath11k_dp_wx_h_undecap(aw, msdu, desc,
			       HAW_ENCWYPT_TYPE_TKIP_MIC, status, fawse);
}

static boow ath11k_dp_wx_h_wxdma_eww(stwuct ath11k *aw,  stwuct sk_buff *msdu,
				     stwuct ieee80211_wx_status *status)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	boow dwop = fawse;

	aw->ab->soc_stats.wxdma_ewwow[wxcb->eww_code]++;

	switch (wxcb->eww_code) {
	case HAW_WEO_ENTW_WING_WXDMA_ECODE_TKIP_MIC_EWW:
		ath11k_dp_wx_h_tkip_mic_eww(aw, msdu, status);
		bweak;
	defauwt:
		/* TODO: Weview othew wxdma ewwow code to check if anything is
		 * wowth wepowting to mac80211
		 */
		dwop = twue;
		bweak;
	}

	wetuwn dwop;
}

static void ath11k_dp_wx_wbm_eww(stwuct ath11k *aw,
				 stwuct napi_stwuct *napi,
				 stwuct sk_buff *msdu,
				 stwuct sk_buff_head *msdu_wist)
{
	stwuct ath11k_skb_wxcb *wxcb = ATH11K_SKB_WXCB(msdu);
	stwuct ieee80211_wx_status wxs = {0};
	boow dwop = twue;

	switch (wxcb->eww_wew_swc) {
	case HAW_WBM_WEW_SWC_MODUWE_WEO:
		dwop = ath11k_dp_wx_h_weo_eww(aw, msdu, &wxs, msdu_wist);
		bweak;
	case HAW_WBM_WEW_SWC_MODUWE_WXDMA:
		dwop = ath11k_dp_wx_h_wxdma_eww(aw, msdu, &wxs);
		bweak;
	defauwt:
		/* msdu wiww get fweed */
		bweak;
	}

	if (dwop) {
		dev_kfwee_skb_any(msdu);
		wetuwn;
	}

	ath11k_dp_wx_dewivew_msdu(aw, napi, msdu, &wxs);
}

int ath11k_dp_wx_pwocess_wbm_eww(stwuct ath11k_base *ab,
				 stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k *aw;
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct dp_wxdma_wing *wx_wing;
	stwuct haw_wx_wbm_wew_info eww_info;
	stwuct haw_swng *swng;
	stwuct sk_buff *msdu;
	stwuct sk_buff_head msdu_wist[MAX_WADIOS];
	stwuct ath11k_skb_wxcb *wxcb;
	u32 *wx_desc;
	int buf_id, mac_id;
	int num_buffs_weaped[MAX_WADIOS] = {0};
	int totaw_num_buffs_weaped = 0;
	int wet, i;

	fow (i = 0; i < ab->num_wadios; i++)
		__skb_queue_head_init(&msdu_wist[i]);

	swng = &ab->haw.swng_wist[dp->wx_wew_wing.wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	whiwe (budget) {
		wx_desc = ath11k_haw_swng_dst_get_next_entwy(ab, swng);
		if (!wx_desc)
			bweak;

		wet = ath11k_haw_wbm_desc_pawse_eww(ab, wx_desc, &eww_info);
		if (wet) {
			ath11k_wawn(ab,
				    "faiwed to pawse wx ewwow in wbm_wew wing desc %d\n",
				    wet);
			continue;
		}

		buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID, eww_info.cookie);
		mac_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_PDEV_ID, eww_info.cookie);

		aw = ab->pdevs[mac_id].aw;
		wx_wing = &aw->dp.wx_wefiww_buf_wing;

		spin_wock_bh(&wx_wing->idw_wock);
		msdu = idw_find(&wx_wing->bufs_idw, buf_id);
		if (!msdu) {
			ath11k_wawn(ab, "fwame wx with invawid buf_id %d pdev %d\n",
				    buf_id, mac_id);
			spin_unwock_bh(&wx_wing->idw_wock);
			continue;
		}

		idw_wemove(&wx_wing->bufs_idw, buf_id);
		spin_unwock_bh(&wx_wing->idw_wock);

		wxcb = ATH11K_SKB_WXCB(msdu);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 msdu->wen + skb_taiwwoom(msdu),
				 DMA_FWOM_DEVICE);

		num_buffs_weaped[mac_id]++;
		totaw_num_buffs_weaped++;
		budget--;

		if (eww_info.push_weason !=
		    HAW_WEO_DEST_WING_PUSH_WEASON_EWW_DETECTED) {
			dev_kfwee_skb_any(msdu);
			continue;
		}

		wxcb->eww_wew_swc = eww_info.eww_wew_swc;
		wxcb->eww_code = eww_info.eww_code;
		wxcb->wx_desc = (stwuct haw_wx_desc *)msdu->data;
		__skb_queue_taiw(&msdu_wist[mac_id], msdu);
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	if (!totaw_num_buffs_weaped)
		goto done;

	fow (i = 0; i <  ab->num_wadios; i++) {
		if (!num_buffs_weaped[i])
			continue;

		aw = ab->pdevs[i].aw;
		wx_wing = &aw->dp.wx_wefiww_buf_wing;

		ath11k_dp_wxbufs_wepwenish(ab, i, wx_wing, num_buffs_weaped[i],
					   ab->hw_pawams.haw_pawams->wx_buf_wbm);
	}

	wcu_wead_wock();
	fow (i = 0; i <  ab->num_wadios; i++) {
		if (!wcu_dewefewence(ab->pdevs_active[i])) {
			__skb_queue_puwge(&msdu_wist[i]);
			continue;
		}

		aw = ab->pdevs[i].aw;

		if (test_bit(ATH11K_CAC_WUNNING, &aw->dev_fwags)) {
			__skb_queue_puwge(&msdu_wist[i]);
			continue;
		}

		whiwe ((msdu = __skb_dequeue(&msdu_wist[i])) != NUWW)
			ath11k_dp_wx_wbm_eww(aw, napi, msdu, &msdu_wist[i]);
	}
	wcu_wead_unwock();
done:
	wetuwn totaw_num_buffs_weaped;
}

int ath11k_dp_pwocess_wxdma_eww(stwuct ath11k_base *ab, int mac_id, int budget)
{
	stwuct ath11k *aw;
	stwuct dp_swng *eww_wing;
	stwuct dp_wxdma_wing *wx_wing;
	stwuct dp_wink_desc_bank *wink_desc_banks = ab->dp.wink_desc_banks;
	stwuct haw_swng *swng;
	u32 msdu_cookies[HAW_NUM_WX_MSDUS_PEW_WINK_DESC];
	enum haw_wx_buf_wetuwn_buf_managew wbm;
	enum haw_weo_entw_wxdma_ecode wxdma_eww_code;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct sk_buff *skb;
	stwuct haw_weo_entwance_wing *entw_wing;
	void *desc;
	int num_buf_fweed = 0;
	int quota = budget;
	dma_addw_t paddw;
	u32 desc_bank;
	void *wink_desc_va;
	int num_msdus;
	int i;
	int buf_id;

	aw = ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_pawams, mac_id)].aw;
	eww_wing = &aw->dp.wxdma_eww_dst_wing[ath11k_hw_mac_id_to_swng_id(&ab->hw_pawams,
									  mac_id)];
	wx_wing = &aw->dp.wx_wefiww_buf_wing;

	swng = &ab->haw.swng_wist[eww_wing->wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	whiwe (quota-- &&
	       (desc = ath11k_haw_swng_dst_get_next_entwy(ab, swng))) {
		ath11k_haw_wx_weo_ent_paddw_get(ab, desc, &paddw, &desc_bank);

		entw_wing = (stwuct haw_weo_entwance_wing *)desc;
		wxdma_eww_code =
			FIEWD_GET(HAW_WEO_ENTW_WING_INFO1_WXDMA_EWWOW_CODE,
				  entw_wing->info1);
		ab->soc_stats.wxdma_ewwow[wxdma_eww_code]++;

		wink_desc_va = wink_desc_banks[desc_bank].vaddw +
			       (paddw - wink_desc_banks[desc_bank].paddw);
		ath11k_haw_wx_msdu_wink_info_get(wink_desc_va, &num_msdus,
						 msdu_cookies, &wbm);

		fow (i = 0; i < num_msdus; i++) {
			buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID,
					   msdu_cookies[i]);

			spin_wock_bh(&wx_wing->idw_wock);
			skb = idw_find(&wx_wing->bufs_idw, buf_id);
			if (!skb) {
				ath11k_wawn(ab, "wxdma ewwow with invawid buf_id %d\n",
					    buf_id);
				spin_unwock_bh(&wx_wing->idw_wock);
				continue;
			}

			idw_wemove(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);

			wxcb = ATH11K_SKB_WXCB(skb);
			dma_unmap_singwe(ab->dev, wxcb->paddw,
					 skb->wen + skb_taiwwoom(skb),
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);

			num_buf_fweed++;
		}

		ath11k_dp_wx_wink_desc_wetuwn(ab, desc,
					      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	if (num_buf_fweed)
		ath11k_dp_wxbufs_wepwenish(ab, mac_id, wx_wing, num_buf_fweed,
					   ab->hw_pawams.haw_pawams->wx_buf_wbm);

	wetuwn budget - quota;
}

void ath11k_dp_pwocess_weo_status(stwuct ath11k_base *ab)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct haw_swng *swng;
	stwuct dp_weo_cmd *cmd, *tmp;
	boow found = fawse;
	u32 *weo_desc;
	u16 tag;
	stwuct haw_weo_status weo_status;

	swng = &ab->haw.swng_wist[dp->weo_status_wing.wing_id];

	memset(&weo_status, 0, sizeof(weo_status));

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	whiwe ((weo_desc = ath11k_haw_swng_dst_get_next_entwy(ab, swng))) {
		tag = FIEWD_GET(HAW_SWNG_TWV_HDW_TAG, *weo_desc);

		switch (tag) {
		case HAW_WEO_GET_QUEUE_STATS_STATUS:
			ath11k_haw_weo_status_queue_stats(ab, weo_desc,
							  &weo_status);
			bweak;
		case HAW_WEO_FWUSH_QUEUE_STATUS:
			ath11k_haw_weo_fwush_queue_status(ab, weo_desc,
							  &weo_status);
			bweak;
		case HAW_WEO_FWUSH_CACHE_STATUS:
			ath11k_haw_weo_fwush_cache_status(ab, weo_desc,
							  &weo_status);
			bweak;
		case HAW_WEO_UNBWOCK_CACHE_STATUS:
			ath11k_haw_weo_unbwk_cache_status(ab, weo_desc,
							  &weo_status);
			bweak;
		case HAW_WEO_FWUSH_TIMEOUT_WIST_STATUS:
			ath11k_haw_weo_fwush_timeout_wist_status(ab, weo_desc,
								 &weo_status);
			bweak;
		case HAW_WEO_DESCWIPTOW_THWESHOWD_WEACHED_STATUS:
			ath11k_haw_weo_desc_thwesh_weached_status(ab, weo_desc,
								  &weo_status);
			bweak;
		case HAW_WEO_UPDATE_WX_WEO_QUEUE_STATUS:
			ath11k_haw_weo_update_wx_weo_queue_status(ab, weo_desc,
								  &weo_status);
			bweak;
		defauwt:
			ath11k_wawn(ab, "Unknown weo status type %d\n", tag);
			continue;
		}

		spin_wock_bh(&dp->weo_cmd_wock);
		wist_fow_each_entwy_safe(cmd, tmp, &dp->weo_cmd_wist, wist) {
			if (weo_status.unifowm_hdw.cmd_num == cmd->cmd_num) {
				found = twue;
				wist_dew(&cmd->wist);
				bweak;
			}
		}
		spin_unwock_bh(&dp->weo_cmd_wock);

		if (found) {
			cmd->handwew(dp, (void *)&cmd->data,
				     weo_status.unifowm_hdw.cmd_status);
			kfwee(cmd);
		}

		found = fawse;
	}

	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);
}

void ath11k_dp_wx_pdev_fwee(stwuct ath11k_base *ab, int mac_id)
{
	stwuct ath11k *aw = ab->pdevs[mac_id].aw;

	ath11k_dp_wx_pdev_swng_fwee(aw);
	ath11k_dp_wxdma_pdev_buf_fwee(aw);
}

int ath11k_dp_wx_pdev_awwoc(stwuct ath11k_base *ab, int mac_id)
{
	stwuct ath11k *aw = ab->pdevs[mac_id].aw;
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	u32 wing_id;
	int i;
	int wet;

	wet = ath11k_dp_wx_pdev_swng_awwoc(aw);
	if (wet) {
		ath11k_wawn(ab, "faiwed to setup wx swngs\n");
		wetuwn wet;
	}

	wet = ath11k_dp_wxdma_pdev_buf_setup(aw);
	if (wet) {
		ath11k_wawn(ab, "faiwed to setup wxdma wing\n");
		wetuwn wet;
	}

	wing_id = dp->wx_wefiww_buf_wing.wefiww_buf_wing.wing_id;
	wet = ath11k_dp_tx_htt_swng_setup(ab, wing_id, mac_id, HAW_WXDMA_BUF);
	if (wet) {
		ath11k_wawn(ab, "faiwed to configuwe wx_wefiww_buf_wing %d\n",
			    wet);
		wetuwn wet;
	}

	if (ab->hw_pawams.wx_mac_buf_wing) {
		fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
			wing_id = dp->wx_mac_buf_wing[i].wing_id;
			wet = ath11k_dp_tx_htt_swng_setup(ab, wing_id,
							  mac_id + i, HAW_WXDMA_BUF);
			if (wet) {
				ath11k_wawn(ab, "faiwed to configuwe wx_mac_buf_wing%d %d\n",
					    i, wet);
				wetuwn wet;
			}
		}
	}

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wing_id = dp->wxdma_eww_dst_wing[i].wing_id;
		wet = ath11k_dp_tx_htt_swng_setup(ab, wing_id,
						  mac_id + i, HAW_WXDMA_DST);
		if (wet) {
			ath11k_wawn(ab, "faiwed to configuwe wxdma_eww_dest_wing%d %d\n",
				    i, wet);
			wetuwn wet;
		}
	}

	if (!ab->hw_pawams.wxdma1_enabwe)
		goto config_wefiww_wing;

	wing_id = dp->wxdma_mon_buf_wing.wefiww_buf_wing.wing_id;
	wet = ath11k_dp_tx_htt_swng_setup(ab, wing_id,
					  mac_id, HAW_WXDMA_MONITOW_BUF);
	if (wet) {
		ath11k_wawn(ab, "faiwed to configuwe wxdma_mon_buf_wing %d\n",
			    wet);
		wetuwn wet;
	}
	wet = ath11k_dp_tx_htt_swng_setup(ab,
					  dp->wxdma_mon_dst_wing.wing_id,
					  mac_id, HAW_WXDMA_MONITOW_DST);
	if (wet) {
		ath11k_wawn(ab, "faiwed to configuwe wxdma_mon_dst_wing %d\n",
			    wet);
		wetuwn wet;
	}
	wet = ath11k_dp_tx_htt_swng_setup(ab,
					  dp->wxdma_mon_desc_wing.wing_id,
					  mac_id, HAW_WXDMA_MONITOW_DESC);
	if (wet) {
		ath11k_wawn(ab, "faiwed to configuwe wxdma_mon_dst_wing %d\n",
			    wet);
		wetuwn wet;
	}

config_wefiww_wing:
	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wing_id = dp->wx_mon_status_wefiww_wing[i].wefiww_buf_wing.wing_id;
		wet = ath11k_dp_tx_htt_swng_setup(ab, wing_id, mac_id + i,
						  HAW_WXDMA_MONITOW_STATUS);
		if (wet) {
			ath11k_wawn(ab,
				    "faiwed to configuwe mon_status_wefiww_wing%d %d\n",
				    i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void ath11k_dp_mon_set_fwag_wen(u32 *totaw_wen, u32 *fwag_wen)
{
	if (*totaw_wen >= (DP_WX_BUFFEW_SIZE - sizeof(stwuct haw_wx_desc))) {
		*fwag_wen = DP_WX_BUFFEW_SIZE - sizeof(stwuct haw_wx_desc);
		*totaw_wen -= *fwag_wen;
	} ewse {
		*fwag_wen = *totaw_wen;
		*totaw_wen = 0;
	}
}

static
int ath11k_dp_wx_monitow_wink_desc_wetuwn(stwuct ath11k *aw,
					  void *p_wast_buf_addw_info,
					  u8 mac_id)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct dp_swng *dp_swng;
	void *haw_swng;
	void *swc_swng_desc;
	int wet = 0;

	if (aw->ab->hw_pawams.wxdma1_enabwe) {
		dp_swng = &dp->wxdma_mon_desc_wing;
		haw_swng = &aw->ab->haw.swng_wist[dp_swng->wing_id];
	} ewse {
		dp_swng = &aw->ab->dp.wbm_desc_wew_wing;
		haw_swng = &aw->ab->haw.swng_wist[dp_swng->wing_id];
	}

	ath11k_haw_swng_access_begin(aw->ab, haw_swng);

	swc_swng_desc = ath11k_haw_swng_swc_get_next_entwy(aw->ab, haw_swng);

	if (swc_swng_desc) {
		stwuct ath11k_buffew_addw *swc_desc = swc_swng_desc;

		*swc_desc = *((stwuct ath11k_buffew_addw *)p_wast_buf_addw_info);
	} ewse {
		ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
			   "Monitow Wink Desc Wing %d Fuww", mac_id);
		wet = -ENOMEM;
	}

	ath11k_haw_swng_access_end(aw->ab, haw_swng);
	wetuwn wet;
}

static
void ath11k_dp_wx_mon_next_wink_desc_get(void *wx_msdu_wink_desc,
					 dma_addw_t *paddw, u32 *sw_cookie,
					 u8 *wbm,
					 void **pp_buf_addw_info)
{
	stwuct haw_wx_msdu_wink *msdu_wink = wx_msdu_wink_desc;
	stwuct ath11k_buffew_addw *buf_addw_info;

	buf_addw_info = (stwuct ath11k_buffew_addw *)&msdu_wink->buf_addw_info;

	ath11k_haw_wx_buf_addw_info_get(buf_addw_info, paddw, sw_cookie, wbm);

	*pp_buf_addw_info = (void *)buf_addw_info;
}

static int ath11k_dp_pkt_set_pktwen(stwuct sk_buff *skb, u32 wen)
{
	if (skb->wen > wen) {
		skb_twim(skb, wen);
	} ewse {
		if (skb_taiwwoom(skb) < wen - skb->wen) {
			if ((pskb_expand_head(skb, 0,
					      wen - skb->wen - skb_taiwwoom(skb),
					      GFP_ATOMIC))) {
				dev_kfwee_skb_any(skb);
				wetuwn -ENOMEM;
			}
		}
		skb_put(skb, (wen - skb->wen));
	}
	wetuwn 0;
}

static void ath11k_haw_wx_msdu_wist_get(stwuct ath11k *aw,
					void *msdu_wink_desc,
					stwuct haw_wx_msdu_wist *msdu_wist,
					u16 *num_msdus)
{
	stwuct haw_wx_msdu_detaiws *msdu_detaiws = NUWW;
	stwuct wx_msdu_desc *msdu_desc_info = NUWW;
	stwuct haw_wx_msdu_wink *msdu_wink = NUWW;
	int i;
	u32 wast = FIEWD_PWEP(WX_MSDU_DESC_INFO0_WAST_MSDU_IN_MPDU, 1);
	u32 fiwst = FIEWD_PWEP(WX_MSDU_DESC_INFO0_FIWST_MSDU_IN_MPDU, 1);
	u8  tmp  = 0;

	msdu_wink = msdu_wink_desc;
	msdu_detaiws = &msdu_wink->msdu_wink[0];

	fow (i = 0; i < HAW_WX_NUM_MSDU_DESC; i++) {
		if (FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW,
			      msdu_detaiws[i].buf_addw_info.info0) == 0) {
			msdu_desc_info = &msdu_detaiws[i - 1].wx_msdu_info;
			msdu_desc_info->info0 |= wast;
			;
			bweak;
		}
		msdu_desc_info = &msdu_detaiws[i].wx_msdu_info;

		if (!i)
			msdu_desc_info->info0 |= fiwst;
		ewse if (i == (HAW_WX_NUM_MSDU_DESC - 1))
			msdu_desc_info->info0 |= wast;
		msdu_wist->msdu_info[i].msdu_fwags = msdu_desc_info->info0;
		msdu_wist->msdu_info[i].msdu_wen =
			 HAW_WX_MSDU_PKT_WENGTH_GET(msdu_desc_info->info0);
		msdu_wist->sw_cookie[i] =
			FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
				  msdu_detaiws[i].buf_addw_info.info1);
		tmp = FIEWD_GET(BUFFEW_ADDW_INFO1_WET_BUF_MGW,
				msdu_detaiws[i].buf_addw_info.info1);
		msdu_wist->wbm[i] = tmp;
	}
	*num_msdus = i;
}

static u32 ath11k_dp_wx_mon_comp_ppduid(u32 msdu_ppdu_id, u32 *ppdu_id,
					u32 *wx_bufs_used)
{
	u32 wet = 0;

	if ((*ppdu_id < msdu_ppdu_id) &&
	    ((msdu_ppdu_id - *ppdu_id) < DP_NOT_PPDU_ID_WWAP_AWOUND)) {
		*ppdu_id = msdu_ppdu_id;
		wet = msdu_ppdu_id;
	} ewse if ((*ppdu_id > msdu_ppdu_id) &&
		((*ppdu_id - msdu_ppdu_id) > DP_NOT_PPDU_ID_WWAP_AWOUND)) {
		/* mon_dst is behind than mon_status
		 * skip dst_wing and fwee it
		 */
		*wx_bufs_used += 1;
		*ppdu_id = msdu_ppdu_id;
		wet = msdu_ppdu_id;
	}
	wetuwn wet;
}

static void ath11k_dp_mon_get_buf_wen(stwuct haw_wx_msdu_desc_info *info,
				      boow *is_fwag, u32 *totaw_wen,
				      u32 *fwag_wen, u32 *msdu_cnt)
{
	if (info->msdu_fwags & WX_MSDU_DESC_INFO0_MSDU_CONTINUATION) {
		if (!*is_fwag) {
			*totaw_wen = info->msdu_wen;
			*is_fwag = twue;
		}
		ath11k_dp_mon_set_fwag_wen(totaw_wen,
					   fwag_wen);
	} ewse {
		if (*is_fwag) {
			ath11k_dp_mon_set_fwag_wen(totaw_wen,
						   fwag_wen);
		} ewse {
			*fwag_wen = info->msdu_wen;
		}
		*is_fwag = fawse;
		*msdu_cnt -= 1;
	}
}

static u32
ath11k_dp_wx_mon_mpdu_pop(stwuct ath11k *aw, int mac_id,
			  void *wing_entwy, stwuct sk_buff **head_msdu,
			  stwuct sk_buff **taiw_msdu, u32 *npackets,
			  u32 *ppdu_id)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = (stwuct ath11k_mon_data *)&dp->mon_data;
	stwuct dp_wxdma_wing *wx_wing = &dp->wxdma_mon_buf_wing;
	stwuct sk_buff *msdu = NUWW, *wast = NUWW;
	stwuct haw_wx_msdu_wist msdu_wist;
	void *p_buf_addw_info, *p_wast_buf_addw_info;
	stwuct haw_wx_desc *wx_desc;
	void *wx_msdu_wink_desc;
	dma_addw_t paddw;
	u16 num_msdus = 0;
	u32 wx_buf_size, wx_pkt_offset, sw_cookie;
	u32 wx_bufs_used = 0, i = 0;
	u32 msdu_ppdu_id = 0, msdu_cnt = 0;
	u32 totaw_wen = 0, fwag_wen = 0;
	boow is_fwag, is_fiwst_msdu;
	boow dwop_mpdu = fawse;
	stwuct ath11k_skb_wxcb *wxcb;
	stwuct haw_weo_entwance_wing *ent_desc = wing_entwy;
	int buf_id;
	u32 wx_wink_buf_info[2];
	u8 wbm;

	if (!aw->ab->hw_pawams.wxdma1_enabwe)
		wx_wing = &dp->wx_wefiww_buf_wing;

	ath11k_haw_wx_weo_ent_buf_paddw_get(wing_entwy, &paddw,
					    &sw_cookie,
					    &p_wast_buf_addw_info, &wbm,
					    &msdu_cnt);

	if (FIEWD_GET(HAW_WEO_ENTW_WING_INFO1_WXDMA_PUSH_WEASON,
		      ent_desc->info1) ==
		      HAW_WEO_DEST_WING_PUSH_WEASON_EWW_DETECTED) {
		u8 wxdma_eww =
			FIEWD_GET(HAW_WEO_ENTW_WING_INFO1_WXDMA_EWWOW_CODE,
				  ent_desc->info1);
		if (wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_FWUSH_WEQUEST_EWW ||
		    wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_MPDU_WEN_EWW ||
		    wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_OVEWFWOW_EWW) {
			dwop_mpdu = twue;
			pmon->wx_mon_stats.dest_mpdu_dwop++;
		}
	}

	is_fwag = fawse;
	is_fiwst_msdu = twue;

	do {
		if (pmon->mon_wast_winkdesc_paddw == paddw) {
			pmon->wx_mon_stats.dup_mon_winkdesc_cnt++;
			wetuwn wx_bufs_used;
		}

		if (aw->ab->hw_pawams.wxdma1_enabwe)
			wx_msdu_wink_desc =
				(void *)pmon->wink_desc_banks[sw_cookie].vaddw +
				(paddw - pmon->wink_desc_banks[sw_cookie].paddw);
		ewse
			wx_msdu_wink_desc =
				(void *)aw->ab->dp.wink_desc_banks[sw_cookie].vaddw +
				(paddw - aw->ab->dp.wink_desc_banks[sw_cookie].paddw);

		ath11k_haw_wx_msdu_wist_get(aw, wx_msdu_wink_desc, &msdu_wist,
					    &num_msdus);

		fow (i = 0; i < num_msdus; i++) {
			u32 w2_hdw_offset;

			if (pmon->mon_wast_buf_cookie == msdu_wist.sw_cookie[i]) {
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "i %d wast_cookie %d is same\n",
					   i, pmon->mon_wast_buf_cookie);
				dwop_mpdu = twue;
				pmon->wx_mon_stats.dup_mon_buf_cnt++;
				continue;
			}
			buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID,
					   msdu_wist.sw_cookie[i]);

			spin_wock_bh(&wx_wing->idw_wock);
			msdu = idw_find(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);
			if (!msdu) {
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "msdu_pop: invawid buf_id %d\n", buf_id);
				bweak;
			}
			wxcb = ATH11K_SKB_WXCB(msdu);
			if (!wxcb->unmapped) {
				dma_unmap_singwe(aw->ab->dev, wxcb->paddw,
						 msdu->wen +
						 skb_taiwwoom(msdu),
						 DMA_FWOM_DEVICE);
				wxcb->unmapped = 1;
			}
			if (dwop_mpdu) {
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "i %d dwop msdu %p *ppdu_id %x\n",
					   i, msdu, *ppdu_id);
				dev_kfwee_skb_any(msdu);
				msdu = NUWW;
				goto next_msdu;
			}

			wx_desc = (stwuct haw_wx_desc *)msdu->data;

			wx_pkt_offset = sizeof(stwuct haw_wx_desc);
			w2_hdw_offset = ath11k_dp_wx_h_msdu_end_w3pad(aw->ab, wx_desc);

			if (is_fiwst_msdu) {
				if (!ath11k_dp_wxdesc_mpdu_vawid(aw->ab, wx_desc)) {
					dwop_mpdu = twue;
					dev_kfwee_skb_any(msdu);
					msdu = NUWW;
					pmon->mon_wast_winkdesc_paddw = paddw;
					goto next_msdu;
				}

				msdu_ppdu_id =
					ath11k_dp_wxdesc_get_ppduid(aw->ab, wx_desc);

				if (ath11k_dp_wx_mon_comp_ppduid(msdu_ppdu_id,
								 ppdu_id,
								 &wx_bufs_used)) {
					if (wx_bufs_used) {
						dwop_mpdu = twue;
						dev_kfwee_skb_any(msdu);
						msdu = NUWW;
						goto next_msdu;
					}
					wetuwn wx_bufs_used;
				}
				pmon->mon_wast_winkdesc_paddw = paddw;
				is_fiwst_msdu = fawse;
			}
			ath11k_dp_mon_get_buf_wen(&msdu_wist.msdu_info[i],
						  &is_fwag, &totaw_wen,
						  &fwag_wen, &msdu_cnt);
			wx_buf_size = wx_pkt_offset + w2_hdw_offset + fwag_wen;

			ath11k_dp_pkt_set_pktwen(msdu, wx_buf_size);

			if (!(*head_msdu))
				*head_msdu = msdu;
			ewse if (wast)
				wast->next = msdu;

			wast = msdu;
next_msdu:
			pmon->mon_wast_buf_cookie = msdu_wist.sw_cookie[i];
			wx_bufs_used++;
			spin_wock_bh(&wx_wing->idw_wock);
			idw_wemove(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);
		}

		ath11k_haw_wx_buf_addw_info_set(wx_wink_buf_info, paddw, sw_cookie, wbm);

		ath11k_dp_wx_mon_next_wink_desc_get(wx_msdu_wink_desc, &paddw,
						    &sw_cookie, &wbm,
						    &p_buf_addw_info);

		if (aw->ab->hw_pawams.wxdma1_enabwe) {
			if (ath11k_dp_wx_monitow_wink_desc_wetuwn(aw,
								  p_wast_buf_addw_info,
								  dp->mac_id))
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "dp_wx_monitow_wink_desc_wetuwn faiwed");
		} ewse {
			ath11k_dp_wx_wink_desc_wetuwn(aw->ab, wx_wink_buf_info,
						      HAW_WBM_WEW_BM_ACT_PUT_IN_IDWE);
		}

		p_wast_buf_addw_info = p_buf_addw_info;

	} whiwe (paddw && msdu_cnt);

	if (wast)
		wast->next = NUWW;

	*taiw_msdu = msdu;

	if (msdu_cnt == 0)
		*npackets = 1;

	wetuwn wx_bufs_used;
}

static void ath11k_dp_wx_msdus_set_paywoad(stwuct ath11k *aw, stwuct sk_buff *msdu)
{
	u32 wx_pkt_offset, w2_hdw_offset;

	wx_pkt_offset = aw->ab->hw_pawams.haw_desc_sz;
	w2_hdw_offset = ath11k_dp_wx_h_msdu_end_w3pad(aw->ab,
						      (stwuct haw_wx_desc *)msdu->data);
	skb_puww(msdu, wx_pkt_offset + w2_hdw_offset);
}

static stwuct sk_buff *
ath11k_dp_wx_mon_mewg_msdus(stwuct ath11k *aw,
			    u32 mac_id, stwuct sk_buff *head_msdu,
			    stwuct sk_buff *wast_msdu,
			    stwuct ieee80211_wx_status *wxs, boow *fcs_eww)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct sk_buff *msdu, *pwev_buf;
	stwuct haw_wx_desc *wx_desc;
	chaw *hdw_desc;
	u8 *dest, decap_fowmat;
	stwuct ieee80211_hdw_3addw *wh;
	stwuct wx_attention *wx_attention;
	u32 eww_bitmap;

	if (!head_msdu)
		goto eww_mewge_faiw;

	wx_desc = (stwuct haw_wx_desc *)head_msdu->data;
	wx_attention = ath11k_dp_wx_get_attention(ab, wx_desc);
	eww_bitmap = ath11k_dp_wx_h_attn_mpdu_eww(wx_attention);

	if (eww_bitmap & DP_WX_MPDU_EWW_FCS)
		*fcs_eww = twue;

	if (ath11k_dp_wxdesc_get_mpduwen_eww(wx_attention))
		wetuwn NUWW;

	decap_fowmat = ath11k_dp_wx_h_msdu_stawt_decap_type(ab, wx_desc);

	ath11k_dp_wx_h_ppdu(aw, wx_desc, wxs);

	if (decap_fowmat == DP_WX_DECAP_TYPE_WAW) {
		ath11k_dp_wx_msdus_set_paywoad(aw, head_msdu);

		pwev_buf = head_msdu;
		msdu = head_msdu->next;

		whiwe (msdu) {
			ath11k_dp_wx_msdus_set_paywoad(aw, msdu);

			pwev_buf = msdu;
			msdu = msdu->next;
		}

		pwev_buf->next = NUWW;

		skb_twim(pwev_buf, pwev_buf->wen - HAW_WX_FCS_WEN);
	} ewse if (decap_fowmat == DP_WX_DECAP_TYPE_NATIVE_WIFI) {
		u8 qos_pkt = 0;

		wx_desc = (stwuct haw_wx_desc *)head_msdu->data;
		hdw_desc = ath11k_dp_wxdesc_get_80211hdw(ab, wx_desc);

		/* Base size */
		wh = (stwuct ieee80211_hdw_3addw *)hdw_desc;

		if (ieee80211_is_data_qos(wh->fwame_contwow))
			qos_pkt = 1;

		msdu = head_msdu;

		whiwe (msdu) {
			ath11k_dp_wx_msdus_set_paywoad(aw, msdu);
			if (qos_pkt) {
				dest = skb_push(msdu, sizeof(__we16));
				if (!dest)
					goto eww_mewge_faiw;
				memcpy(dest, hdw_desc, sizeof(stwuct ieee80211_qos_hdw));
			}
			pwev_buf = msdu;
			msdu = msdu->next;
		}
		dest = skb_put(pwev_buf, HAW_WX_FCS_WEN);
		if (!dest)
			goto eww_mewge_faiw;

		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "mpdu_buf %p mpdu_buf->wen %u",
			   pwev_buf, pwev_buf->wen);
	} ewse {
		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "decap fowmat %d is not suppowted!\n",
			   decap_fowmat);
		goto eww_mewge_faiw;
	}

	wetuwn head_msdu;

eww_mewge_faiw:
	wetuwn NUWW;
}

static void
ath11k_dp_wx_update_wadiotap_he(stwuct haw_wx_mon_ppdu_info *wx_status,
				u8 *wtap_buf)
{
	u32 wtap_wen = 0;

	put_unawigned_we16(wx_status->he_data1, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data2, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data3, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data4, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data5, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data6, &wtap_buf[wtap_wen]);
}

static void
ath11k_dp_wx_update_wadiotap_he_mu(stwuct haw_wx_mon_ppdu_info *wx_status,
				   u8 *wtap_buf)
{
	u32 wtap_wen = 0;

	put_unawigned_we16(wx_status->he_fwags1, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_fwags2, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	wtap_buf[wtap_wen] = wx_status->he_WU[0];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[1];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[2];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[3];
}

static void ath11k_update_wadiotap(stwuct ath11k *aw,
				   stwuct haw_wx_mon_ppdu_info *ppduinfo,
				   stwuct sk_buff *mon_skb,
				   stwuct ieee80211_wx_status *wxs)
{
	stwuct ieee80211_suppowted_band *sband;
	u8 *ptw = NUWW;

	wxs->fwag |= WX_FWAG_MACTIME_STAWT;
	wxs->signaw = ppduinfo->wssi_comb + ATH11K_DEFAUWT_NOISE_FWOOW;

	if (ppduinfo->nss)
		wxs->nss = ppduinfo->nss;

	if (ppduinfo->he_mu_fwags) {
		wxs->fwag |= WX_FWAG_WADIOTAP_HE_MU;
		wxs->encoding = WX_ENC_HE;
		ptw = skb_push(mon_skb, sizeof(stwuct ieee80211_wadiotap_he_mu));
		ath11k_dp_wx_update_wadiotap_he_mu(ppduinfo, ptw);
	} ewse if (ppduinfo->he_fwags) {
		wxs->fwag |= WX_FWAG_WADIOTAP_HE;
		wxs->encoding = WX_ENC_HE;
		ptw = skb_push(mon_skb, sizeof(stwuct ieee80211_wadiotap_he));
		ath11k_dp_wx_update_wadiotap_he(ppduinfo, ptw);
		wxs->wate_idx = ppduinfo->wate;
	} ewse if (ppduinfo->vht_fwags) {
		wxs->encoding = WX_ENC_VHT;
		wxs->wate_idx = ppduinfo->wate;
	} ewse if (ppduinfo->ht_fwags) {
		wxs->encoding = WX_ENC_HT;
		wxs->wate_idx = ppduinfo->wate;
	} ewse {
		wxs->encoding = WX_ENC_WEGACY;
		sband = &aw->mac.sbands[wxs->band];
		wxs->wate_idx = ath11k_mac_hw_wate_to_idx(sband, ppduinfo->wate,
							  ppduinfo->cck_fwag);
	}

	wxs->mactime = ppduinfo->tsft;
}

static int ath11k_dp_wx_mon_dewivew(stwuct ath11k *aw, u32 mac_id,
				    stwuct sk_buff *head_msdu,
				    stwuct haw_wx_mon_ppdu_info *ppduinfo,
				    stwuct sk_buff *taiw_msdu,
				    stwuct napi_stwuct *napi)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct sk_buff *mon_skb, *skb_next, *headew;
	stwuct ieee80211_wx_status *wxs = &dp->wx_status;
	boow fcs_eww = fawse;

	mon_skb = ath11k_dp_wx_mon_mewg_msdus(aw, mac_id, head_msdu,
					      taiw_msdu, wxs, &fcs_eww);

	if (!mon_skb)
		goto mon_dewivew_faiw;

	headew = mon_skb;

	wxs->fwag = 0;

	if (fcs_eww)
		wxs->fwag = WX_FWAG_FAIWED_FCS_CWC;

	do {
		skb_next = mon_skb->next;
		if (!skb_next)
			wxs->fwag &= ~WX_FWAG_AMSDU_MOWE;
		ewse
			wxs->fwag |= WX_FWAG_AMSDU_MOWE;

		if (mon_skb == headew) {
			headew = NUWW;
			wxs->fwag &= ~WX_FWAG_AWWOW_SAME_PN;
		} ewse {
			wxs->fwag |= WX_FWAG_AWWOW_SAME_PN;
		}
		wxs->fwag |= WX_FWAG_ONWY_MONITOW;
		ath11k_update_wadiotap(aw, ppduinfo, mon_skb, wxs);

		ath11k_dp_wx_dewivew_msdu(aw, napi, mon_skb, wxs);
		mon_skb = skb_next;
	} whiwe (mon_skb);
	wxs->fwag = 0;

	wetuwn 0;

mon_dewivew_faiw:
	mon_skb = head_msdu;
	whiwe (mon_skb) {
		skb_next = mon_skb->next;
		dev_kfwee_skb_any(mon_skb);
		mon_skb = skb_next;
	}
	wetuwn -EINVAW;
}

/* The destination wing pwocessing is stuck if the destination is not
 * moving whiwe status wing moves 16 PPDU. The destination wing pwocessing
 * skips this destination wing PPDU as a wowkawound.
 */
#define MON_DEST_WING_STUCK_MAX_CNT 16

static void ath11k_dp_wx_mon_dest_pwocess(stwuct ath11k *aw, int mac_id,
					  u32 quota, stwuct napi_stwuct *napi)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = (stwuct ath11k_mon_data *)&dp->mon_data;
	const stwuct ath11k_hw_haw_pawams *haw_pawams;
	void *wing_entwy;
	void *mon_dst_swng;
	u32 ppdu_id;
	u32 wx_bufs_used;
	u32 wing_id;
	stwuct ath11k_pdev_mon_stats *wx_mon_stats;
	u32	 npackets = 0;
	u32 mpdu_wx_bufs_used;

	if (aw->ab->hw_pawams.wxdma1_enabwe)
		wing_id = dp->wxdma_mon_dst_wing.wing_id;
	ewse
		wing_id = dp->wxdma_eww_dst_wing[mac_id].wing_id;

	mon_dst_swng = &aw->ab->haw.swng_wist[wing_id];

	spin_wock_bh(&pmon->mon_wock);

	ath11k_haw_swng_access_begin(aw->ab, mon_dst_swng);

	ppdu_id = pmon->mon_ppdu_info.ppdu_id;
	wx_bufs_used = 0;
	wx_mon_stats = &pmon->wx_mon_stats;

	whiwe ((wing_entwy = ath11k_haw_swng_dst_peek(aw->ab, mon_dst_swng))) {
		stwuct sk_buff *head_msdu, *taiw_msdu;

		head_msdu = NUWW;
		taiw_msdu = NUWW;

		mpdu_wx_bufs_used = ath11k_dp_wx_mon_mpdu_pop(aw, mac_id, wing_entwy,
							      &head_msdu,
							      &taiw_msdu,
							      &npackets, &ppdu_id);

		wx_bufs_used += mpdu_wx_bufs_used;

		if (mpdu_wx_bufs_used) {
			dp->mon_dest_wing_stuck_cnt = 0;
		} ewse {
			dp->mon_dest_wing_stuck_cnt++;
			wx_mon_stats->dest_mon_not_weaped++;
		}

		if (dp->mon_dest_wing_stuck_cnt > MON_DEST_WING_STUCK_MAX_CNT) {
			wx_mon_stats->dest_mon_stuck++;
			ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
				   "status wing ppdu_id=%d dest wing ppdu_id=%d mon_dest_wing_stuck_cnt=%d dest_mon_not_weaped=%u dest_mon_stuck=%u\n",
				   pmon->mon_ppdu_info.ppdu_id, ppdu_id,
				   dp->mon_dest_wing_stuck_cnt,
				   wx_mon_stats->dest_mon_not_weaped,
				   wx_mon_stats->dest_mon_stuck);
			pmon->mon_ppdu_info.ppdu_id = ppdu_id;
			continue;
		}

		if (ppdu_id != pmon->mon_ppdu_info.ppdu_id) {
			pmon->mon_ppdu_status = DP_PPDU_STATUS_STAWT;
			ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
				   "dest_wx: new ppdu_id %x != status ppdu_id %x dest_mon_not_weaped = %u dest_mon_stuck = %u\n",
				   ppdu_id, pmon->mon_ppdu_info.ppdu_id,
				   wx_mon_stats->dest_mon_not_weaped,
				   wx_mon_stats->dest_mon_stuck);
			bweak;
		}
		if (head_msdu && taiw_msdu) {
			ath11k_dp_wx_mon_dewivew(aw, dp->mac_id, head_msdu,
						 &pmon->mon_ppdu_info,
						 taiw_msdu, napi);
			wx_mon_stats->dest_mpdu_done++;
		}

		wing_entwy = ath11k_haw_swng_dst_get_next_entwy(aw->ab,
								mon_dst_swng);
	}
	ath11k_haw_swng_access_end(aw->ab, mon_dst_swng);

	spin_unwock_bh(&pmon->mon_wock);

	if (wx_bufs_used) {
		wx_mon_stats->dest_ppdu_done++;
		haw_pawams = aw->ab->hw_pawams.haw_pawams;

		if (aw->ab->hw_pawams.wxdma1_enabwe)
			ath11k_dp_wxbufs_wepwenish(aw->ab, dp->mac_id,
						   &dp->wxdma_mon_buf_wing,
						   wx_bufs_used,
						   haw_pawams->wx_buf_wbm);
		ewse
			ath11k_dp_wxbufs_wepwenish(aw->ab, dp->mac_id,
						   &dp->wx_wefiww_buf_wing,
						   wx_bufs_used,
						   haw_pawams->wx_buf_wbm);
	}
}

int ath11k_dp_wx_pwocess_mon_status(stwuct ath11k_base *ab, int mac_id,
				    stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k *aw = ath11k_ab_to_aw(ab, mac_id);
	enum haw_wx_mon_status haw_status;
	stwuct sk_buff *skb;
	stwuct sk_buff_head skb_wist;
	stwuct ath11k_peew *peew;
	stwuct ath11k_sta *awsta;
	int num_buffs_weaped = 0;
	u32 wx_buf_sz;
	u16 wog_type;
	stwuct ath11k_mon_data *pmon = (stwuct ath11k_mon_data *)&aw->dp.mon_data;
	stwuct ath11k_pdev_mon_stats *wx_mon_stats = &pmon->wx_mon_stats;
	stwuct haw_wx_mon_ppdu_info *ppdu_info = &pmon->mon_ppdu_info;

	__skb_queue_head_init(&skb_wist);

	num_buffs_weaped = ath11k_dp_wx_weap_mon_status_wing(ab, mac_id, &budget,
							     &skb_wist);
	if (!num_buffs_weaped)
		goto exit;

	memset(ppdu_info, 0, sizeof(*ppdu_info));
	ppdu_info->peew_id = HAW_INVAWID_PEEWID;

	whiwe ((skb = __skb_dequeue(&skb_wist))) {
		if (ath11k_debugfs_is_pktwog_wite_mode_enabwed(aw)) {
			wog_type = ATH11K_PKTWOG_TYPE_WITE_WX;
			wx_buf_sz = DP_WX_BUFFEW_SIZE_WITE;
		} ewse if (ath11k_debugfs_is_pktwog_wx_stats_enabwed(aw)) {
			wog_type = ATH11K_PKTWOG_TYPE_WX_STATBUF;
			wx_buf_sz = DP_WX_BUFFEW_SIZE;
		} ewse {
			wog_type = ATH11K_PKTWOG_TYPE_INVAWID;
			wx_buf_sz = 0;
		}

		if (wog_type != ATH11K_PKTWOG_TYPE_INVAWID)
			twace_ath11k_htt_wxdesc(aw, skb->data, wog_type, wx_buf_sz);

		memset(ppdu_info, 0, sizeof(*ppdu_info));
		ppdu_info->peew_id = HAW_INVAWID_PEEWID;
		haw_status = ath11k_haw_wx_pawse_mon_status(ab, ppdu_info, skb);

		if (test_bit(ATH11K_FWAG_MONITOW_STAWTED, &aw->monitow_fwags) &&
		    pmon->mon_ppdu_status == DP_PPDU_STATUS_STAWT &&
		    haw_status == HAW_TWV_STATUS_PPDU_DONE) {
			wx_mon_stats->status_ppdu_done++;
			pmon->mon_ppdu_status = DP_PPDU_STATUS_DONE;
			ath11k_dp_wx_mon_dest_pwocess(aw, mac_id, budget, napi);
			pmon->mon_ppdu_status = DP_PPDU_STATUS_STAWT;
		}

		if (ppdu_info->peew_id == HAW_INVAWID_PEEWID ||
		    haw_status != HAW_WX_MON_STATUS_PPDU_DONE) {
			dev_kfwee_skb_any(skb);
			continue;
		}

		wcu_wead_wock();
		spin_wock_bh(&ab->base_wock);
		peew = ath11k_peew_find_by_id(ab, ppdu_info->peew_id);

		if (!peew || !peew->sta) {
			ath11k_dbg(ab, ATH11K_DBG_DATA,
				   "faiwed to find the peew with peew_id %d\n",
				   ppdu_info->peew_id);
			goto next_skb;
		}

		awsta = ath11k_sta_to_awsta(peew->sta);
		ath11k_dp_wx_update_peew_stats(awsta, ppdu_info);

		if (ath11k_debugfs_is_pktwog_peew_vawid(aw, peew->addw))
			twace_ath11k_htt_wxdesc(aw, skb->data, wog_type, wx_buf_sz);

next_skb:
		spin_unwock_bh(&ab->base_wock);
		wcu_wead_unwock();

		dev_kfwee_skb_any(skb);
		memset(ppdu_info, 0, sizeof(*ppdu_info));
		ppdu_info->peew_id = HAW_INVAWID_PEEWID;
	}
exit:
	wetuwn num_buffs_weaped;
}

static u32
ath11k_dp_wx_fuww_mon_mpdu_pop(stwuct ath11k *aw,
			       void *wing_entwy, stwuct sk_buff **head_msdu,
			       stwuct sk_buff **taiw_msdu,
			       stwuct haw_sw_mon_wing_entwies *sw_mon_entwies)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = &dp->mon_data;
	stwuct dp_wxdma_wing *wx_wing = &dp->wxdma_mon_buf_wing;
	stwuct sk_buff *msdu = NUWW, *wast = NUWW;
	stwuct haw_sw_monitow_wing *sw_desc = wing_entwy;
	stwuct haw_wx_msdu_wist msdu_wist;
	stwuct haw_wx_desc *wx_desc;
	stwuct ath11k_skb_wxcb *wxcb;
	void *wx_msdu_wink_desc;
	void *p_buf_addw_info, *p_wast_buf_addw_info;
	int buf_id, i = 0;
	u32 wx_buf_size, wx_pkt_offset, w2_hdw_offset;
	u32 wx_bufs_used = 0, msdu_cnt = 0;
	u32 totaw_wen = 0, fwag_wen = 0, sw_cookie;
	u16 num_msdus = 0;
	u8 wxdma_eww, wbm;
	boow is_fwag, is_fiwst_msdu;
	boow dwop_mpdu = fawse;

	ath11k_haw_wx_sw_mon_wing_buf_paddw_get(wing_entwy, sw_mon_entwies);

	sw_cookie = sw_mon_entwies->mon_dst_sw_cookie;
	sw_mon_entwies->end_of_ppdu = fawse;
	sw_mon_entwies->dwop_ppdu = fawse;
	p_wast_buf_addw_info = sw_mon_entwies->dst_buf_addw_info;
	msdu_cnt = sw_mon_entwies->msdu_cnt;

	sw_mon_entwies->end_of_ppdu =
		FIEWD_GET(HAW_SW_MON_WING_INFO0_END_OF_PPDU, sw_desc->info0);
	if (sw_mon_entwies->end_of_ppdu)
		wetuwn wx_bufs_used;

	if (FIEWD_GET(HAW_SW_MON_WING_INFO0_WXDMA_PUSH_WEASON,
		      sw_desc->info0) ==
		      HAW_WEO_DEST_WING_PUSH_WEASON_EWW_DETECTED) {
		wxdma_eww =
			FIEWD_GET(HAW_SW_MON_WING_INFO0_WXDMA_EWWOW_CODE,
				  sw_desc->info0);
		if (wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_FWUSH_WEQUEST_EWW ||
		    wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_MPDU_WEN_EWW ||
		    wxdma_eww == HAW_WEO_ENTW_WING_WXDMA_ECODE_OVEWFWOW_EWW) {
			pmon->wx_mon_stats.dest_mpdu_dwop++;
			dwop_mpdu = twue;
		}
	}

	is_fwag = fawse;
	is_fiwst_msdu = twue;

	do {
		wx_msdu_wink_desc =
			(u8 *)pmon->wink_desc_banks[sw_cookie].vaddw +
			(sw_mon_entwies->mon_dst_paddw -
			 pmon->wink_desc_banks[sw_cookie].paddw);

		ath11k_haw_wx_msdu_wist_get(aw, wx_msdu_wink_desc, &msdu_wist,
					    &num_msdus);

		fow (i = 0; i < num_msdus; i++) {
			buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID,
					   msdu_wist.sw_cookie[i]);

			spin_wock_bh(&wx_wing->idw_wock);
			msdu = idw_find(&wx_wing->bufs_idw, buf_id);
			if (!msdu) {
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "fuww mon msdu_pop: invawid buf_id %d\n",
					    buf_id);
				spin_unwock_bh(&wx_wing->idw_wock);
				bweak;
			}
			idw_wemove(&wx_wing->bufs_idw, buf_id);
			spin_unwock_bh(&wx_wing->idw_wock);

			wxcb = ATH11K_SKB_WXCB(msdu);
			if (!wxcb->unmapped) {
				dma_unmap_singwe(aw->ab->dev, wxcb->paddw,
						 msdu->wen +
						 skb_taiwwoom(msdu),
						 DMA_FWOM_DEVICE);
				wxcb->unmapped = 1;
			}
			if (dwop_mpdu) {
				ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
					   "fuww mon: i %d dwop msdu %p *ppdu_id %x\n",
					   i, msdu, sw_mon_entwies->ppdu_id);
				dev_kfwee_skb_any(msdu);
				msdu_cnt--;
				goto next_msdu;
			}

			wx_desc = (stwuct haw_wx_desc *)msdu->data;

			wx_pkt_offset = sizeof(stwuct haw_wx_desc);
			w2_hdw_offset = ath11k_dp_wx_h_msdu_end_w3pad(aw->ab, wx_desc);

			if (is_fiwst_msdu) {
				if (!ath11k_dp_wxdesc_mpdu_vawid(aw->ab, wx_desc)) {
					dwop_mpdu = twue;
					dev_kfwee_skb_any(msdu);
					msdu = NUWW;
					goto next_msdu;
				}
				is_fiwst_msdu = fawse;
			}

			ath11k_dp_mon_get_buf_wen(&msdu_wist.msdu_info[i],
						  &is_fwag, &totaw_wen,
						  &fwag_wen, &msdu_cnt);

			wx_buf_size = wx_pkt_offset + w2_hdw_offset + fwag_wen;

			ath11k_dp_pkt_set_pktwen(msdu, wx_buf_size);

			if (!(*head_msdu))
				*head_msdu = msdu;
			ewse if (wast)
				wast->next = msdu;

			wast = msdu;
next_msdu:
			wx_bufs_used++;
		}

		ath11k_dp_wx_mon_next_wink_desc_get(wx_msdu_wink_desc,
						    &sw_mon_entwies->mon_dst_paddw,
						    &sw_mon_entwies->mon_dst_sw_cookie,
						    &wbm,
						    &p_buf_addw_info);

		if (ath11k_dp_wx_monitow_wink_desc_wetuwn(aw,
							  p_wast_buf_addw_info,
							  dp->mac_id))
			ath11k_dbg(aw->ab, ATH11K_DBG_DATA,
				   "fuww mon: dp_wx_monitow_wink_desc_wetuwn faiwed\n");

		p_wast_buf_addw_info = p_buf_addw_info;

	} whiwe (sw_mon_entwies->mon_dst_paddw && msdu_cnt);

	if (wast)
		wast->next = NUWW;

	*taiw_msdu = msdu;

	wetuwn wx_bufs_used;
}

static int ath11k_dp_wx_fuww_mon_pwepawe_mpdu(stwuct ath11k_dp *dp,
					      stwuct dp_fuww_mon_mpdu *mon_mpdu,
					      stwuct sk_buff *head,
					      stwuct sk_buff *taiw)
{
	mon_mpdu = kzawwoc(sizeof(*mon_mpdu), GFP_ATOMIC);
	if (!mon_mpdu)
		wetuwn -ENOMEM;

	wist_add_taiw(&mon_mpdu->wist, &dp->dp_fuww_mon_mpdu_wist);
	mon_mpdu->head = head;
	mon_mpdu->taiw = taiw;

	wetuwn 0;
}

static void ath11k_dp_wx_fuww_mon_dwop_ppdu(stwuct ath11k_dp *dp,
					    stwuct dp_fuww_mon_mpdu *mon_mpdu)
{
	stwuct dp_fuww_mon_mpdu *tmp;
	stwuct sk_buff *tmp_msdu, *skb_next;

	if (wist_empty(&dp->dp_fuww_mon_mpdu_wist))
		wetuwn;

	wist_fow_each_entwy_safe(mon_mpdu, tmp, &dp->dp_fuww_mon_mpdu_wist, wist) {
		wist_dew(&mon_mpdu->wist);

		tmp_msdu = mon_mpdu->head;
		whiwe (tmp_msdu) {
			skb_next = tmp_msdu->next;
			dev_kfwee_skb_any(tmp_msdu);
			tmp_msdu = skb_next;
		}

		kfwee(mon_mpdu);
	}
}

static int ath11k_dp_wx_fuww_mon_dewivew_ppdu(stwuct ath11k *aw,
					      int mac_id,
					      stwuct ath11k_mon_data *pmon,
					      stwuct napi_stwuct *napi)
{
	stwuct ath11k_pdev_mon_stats *wx_mon_stats;
	stwuct dp_fuww_mon_mpdu *tmp;
	stwuct dp_fuww_mon_mpdu *mon_mpdu = pmon->mon_mpdu;
	stwuct sk_buff *head_msdu, *taiw_msdu;
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_dp *dp = &ab->dp;
	int wet;

	wx_mon_stats = &pmon->wx_mon_stats;

	wist_fow_each_entwy_safe(mon_mpdu, tmp, &dp->dp_fuww_mon_mpdu_wist, wist) {
		wist_dew(&mon_mpdu->wist);
		head_msdu = mon_mpdu->head;
		taiw_msdu = mon_mpdu->taiw;
		if (head_msdu && taiw_msdu) {
			wet = ath11k_dp_wx_mon_dewivew(aw, mac_id, head_msdu,
						       &pmon->mon_ppdu_info,
						       taiw_msdu, napi);
			wx_mon_stats->dest_mpdu_done++;
			ath11k_dbg(aw->ab, ATH11K_DBG_DATA, "fuww mon: dewivew ppdu\n");
		}
		kfwee(mon_mpdu);
	}

	wetuwn wet;
}

static int
ath11k_dp_wx_pwocess_fuww_mon_status_wing(stwuct ath11k_base *ab, int mac_id,
					  stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k *aw = ab->pdevs[mac_id].aw;
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = &dp->mon_data;
	stwuct haw_sw_mon_wing_entwies *sw_mon_entwies;
	int quota = 0, wowk = 0, count;

	sw_mon_entwies = &pmon->sw_mon_entwies;

	whiwe (pmon->howd_mon_dst_wing) {
		quota = ath11k_dp_wx_pwocess_mon_status(ab, mac_id,
							napi, 1);
		if (pmon->buf_state == DP_MON_STATUS_MATCH) {
			count = sw_mon_entwies->status_buf_count;
			if (count > 1) {
				quota += ath11k_dp_wx_pwocess_mon_status(ab, mac_id,
									 napi, count);
			}

			ath11k_dp_wx_fuww_mon_dewivew_ppdu(aw, dp->mac_id,
							   pmon, napi);
			pmon->howd_mon_dst_wing = fawse;
		} ewse if (!pmon->mon_status_paddw ||
			   pmon->buf_state == DP_MON_STATUS_WEAD) {
			sw_mon_entwies->dwop_ppdu = twue;
			pmon->howd_mon_dst_wing = fawse;
		}

		if (!quota)
			bweak;

		wowk += quota;
	}

	if (sw_mon_entwies->dwop_ppdu)
		ath11k_dp_wx_fuww_mon_dwop_ppdu(&ab->dp, pmon->mon_mpdu);

	wetuwn wowk;
}

static int ath11k_dp_fuww_mon_pwocess_wx(stwuct ath11k_base *ab, int mac_id,
					 stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k *aw = ab->pdevs[mac_id].aw;
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = &dp->mon_data;
	stwuct haw_sw_mon_wing_entwies *sw_mon_entwies;
	stwuct ath11k_pdev_mon_stats *wx_mon_stats;
	stwuct sk_buff *head_msdu, *taiw_msdu;
	void *mon_dst_swng = &aw->ab->haw.swng_wist[dp->wxdma_mon_dst_wing.wing_id];
	void *wing_entwy;
	u32 wx_bufs_used = 0, mpdu_wx_bufs_used;
	int quota = 0, wet;
	boow bweak_dst_wing = fawse;

	spin_wock_bh(&pmon->mon_wock);

	sw_mon_entwies = &pmon->sw_mon_entwies;
	wx_mon_stats = &pmon->wx_mon_stats;

	if (pmon->howd_mon_dst_wing) {
		spin_unwock_bh(&pmon->mon_wock);
		goto weap_status_wing;
	}

	ath11k_haw_swng_access_begin(aw->ab, mon_dst_swng);
	whiwe ((wing_entwy = ath11k_haw_swng_dst_peek(aw->ab, mon_dst_swng))) {
		head_msdu = NUWW;
		taiw_msdu = NUWW;

		mpdu_wx_bufs_used = ath11k_dp_wx_fuww_mon_mpdu_pop(aw, wing_entwy,
								   &head_msdu,
								   &taiw_msdu,
								   sw_mon_entwies);
		wx_bufs_used += mpdu_wx_bufs_used;

		if (!sw_mon_entwies->end_of_ppdu) {
			if (head_msdu) {
				wet = ath11k_dp_wx_fuww_mon_pwepawe_mpdu(&ab->dp,
									 pmon->mon_mpdu,
									 head_msdu,
									 taiw_msdu);
				if (wet)
					bweak_dst_wing = twue;
			}

			goto next_entwy;
		} ewse {
			if (!sw_mon_entwies->ppdu_id &&
			    !sw_mon_entwies->mon_status_paddw) {
				bweak_dst_wing = twue;
				goto next_entwy;
			}
		}

		wx_mon_stats->dest_ppdu_done++;
		pmon->mon_ppdu_status = DP_PPDU_STATUS_STAWT;
		pmon->buf_state = DP_MON_STATUS_WAG;
		pmon->mon_status_paddw = sw_mon_entwies->mon_status_paddw;
		pmon->howd_mon_dst_wing = twue;
next_entwy:
		wing_entwy = ath11k_haw_swng_dst_get_next_entwy(aw->ab,
								mon_dst_swng);
		if (bweak_dst_wing)
			bweak;
	}

	ath11k_haw_swng_access_end(aw->ab, mon_dst_swng);
	spin_unwock_bh(&pmon->mon_wock);

	if (wx_bufs_used) {
		ath11k_dp_wxbufs_wepwenish(aw->ab, dp->mac_id,
					   &dp->wxdma_mon_buf_wing,
					   wx_bufs_used,
					   HAW_WX_BUF_WBM_SW3_BM);
	}

weap_status_wing:
	quota = ath11k_dp_wx_pwocess_fuww_mon_status_wing(ab, mac_id,
							  napi, budget);

	wetuwn quota;
}

int ath11k_dp_wx_pwocess_mon_wings(stwuct ath11k_base *ab, int mac_id,
				   stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k *aw = ath11k_ab_to_aw(ab, mac_id);
	int wet = 0;

	if (test_bit(ATH11K_FWAG_MONITOW_STAWTED, &aw->monitow_fwags) &&
	    ab->hw_pawams.fuww_monitow_mode)
		wet = ath11k_dp_fuww_mon_pwocess_wx(ab, mac_id, napi, budget);
	ewse
		wet = ath11k_dp_wx_pwocess_mon_status(ab, mac_id, napi, budget);

	wetuwn wet;
}

static int ath11k_dp_wx_pdev_mon_status_attach(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = (stwuct ath11k_mon_data *)&dp->mon_data;

	skb_queue_head_init(&pmon->wx_status_q);

	pmon->mon_ppdu_status = DP_PPDU_STATUS_STAWT;

	memset(&pmon->wx_mon_stats, 0,
	       sizeof(pmon->wx_mon_stats));
	wetuwn 0;
}

int ath11k_dp_wx_pdev_mon_attach(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = &dp->mon_data;
	stwuct haw_swng *mon_desc_swng = NUWW;
	stwuct dp_swng *dp_swng;
	int wet = 0;
	u32 n_wink_desc = 0;

	wet = ath11k_dp_wx_pdev_mon_status_attach(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "pdev_mon_status_attach() faiwed");
		wetuwn wet;
	}

	/* if wxdma1_enabwe is fawse, no need to setup
	 * wxdma_mon_desc_wing.
	 */
	if (!aw->ab->hw_pawams.wxdma1_enabwe)
		wetuwn 0;

	dp_swng = &dp->wxdma_mon_desc_wing;
	n_wink_desc = dp_swng->size /
		ath11k_haw_swng_get_entwysize(aw->ab, HAW_WXDMA_MONITOW_DESC);
	mon_desc_swng =
		&aw->ab->haw.swng_wist[dp->wxdma_mon_desc_wing.wing_id];

	wet = ath11k_dp_wink_desc_setup(aw->ab, pmon->wink_desc_banks,
					HAW_WXDMA_MONITOW_DESC, mon_desc_swng,
					n_wink_desc);
	if (wet) {
		ath11k_wawn(aw->ab, "mon_wink_desc_poow_setup() faiwed");
		wetuwn wet;
	}
	pmon->mon_wast_winkdesc_paddw = 0;
	pmon->mon_wast_buf_cookie = DP_WX_DESC_COOKIE_MAX + 1;
	spin_wock_init(&pmon->mon_wock);

	wetuwn 0;
}

static int ath11k_dp_mon_wink_fwee(stwuct ath11k *aw)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_mon_data *pmon = &dp->mon_data;

	ath11k_dp_wink_desc_cweanup(aw->ab, pmon->wink_desc_banks,
				    HAW_WXDMA_MONITOW_DESC,
				    &dp->wxdma_mon_desc_wing);
	wetuwn 0;
}

int ath11k_dp_wx_pdev_mon_detach(stwuct ath11k *aw)
{
	ath11k_dp_mon_wink_fwee(aw);
	wetuwn 0;
}

int ath11k_dp_wx_pktwog_stawt(stwuct ath11k_base *ab)
{
	/* stawt weap timew */
	mod_timew(&ab->mon_weap_timew,
		  jiffies + msecs_to_jiffies(ATH11K_MON_TIMEW_INTEWVAW));

	wetuwn 0;
}

int ath11k_dp_wx_pktwog_stop(stwuct ath11k_base *ab, boow stop_timew)
{
	int wet;

	if (stop_timew)
		dew_timew_sync(&ab->mon_weap_timew);

	/* weap aww the monitow wewated wings */
	wet = ath11k_dp_puwge_mon_wing(ab);
	if (wet) {
		ath11k_wawn(ab, "faiwed to puwge dp mon wing: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
