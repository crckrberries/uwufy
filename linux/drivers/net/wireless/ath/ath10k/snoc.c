// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iommu.h>

#incwude "ce.h"
#incwude "cowedump.h"
#incwude "debug.h"
#incwude "hif.h"
#incwude "htc.h"
#incwude "snoc.h"

#define ATH10K_SNOC_WX_POST_WETWY_MS 50
#define CE_POWW_PIPE 4
#define ATH10K_SNOC_WAKE_IWQ 2

static chaw *const ce_name[] = {
	"WWAN_CE_0",
	"WWAN_CE_1",
	"WWAN_CE_2",
	"WWAN_CE_3",
	"WWAN_CE_4",
	"WWAN_CE_5",
	"WWAN_CE_6",
	"WWAN_CE_7",
	"WWAN_CE_8",
	"WWAN_CE_9",
	"WWAN_CE_10",
	"WWAN_CE_11",
};

static const chaw * const ath10k_weguwatows[] = {
	"vdd-0.8-cx-mx",
	"vdd-1.8-xo",
	"vdd-1.3-wfa",
	"vdd-3.3-ch0",
	"vdd-3.3-ch1",
};

static const chaw * const ath10k_cwocks[] = {
	"cxo_wef_cwk_pin", "qdss",
};

static void ath10k_snoc_htc_tx_cb(stwuct ath10k_ce_pipe *ce_state);
static void ath10k_snoc_htt_tx_cb(stwuct ath10k_ce_pipe *ce_state);
static void ath10k_snoc_htc_wx_cb(stwuct ath10k_ce_pipe *ce_state);
static void ath10k_snoc_htt_wx_cb(stwuct ath10k_ce_pipe *ce_state);
static void ath10k_snoc_htt_htc_wx_cb(stwuct ath10k_ce_pipe *ce_state);
static void ath10k_snoc_pktwog_wx_cb(stwuct ath10k_ce_pipe *ce_state);

static const stwuct ath10k_snoc_dwv_pwiv dwv_pwiv = {
	.hw_wev = ATH10K_HW_WCN3990,
	.dma_mask = DMA_BIT_MASK(35),
	.msa_size = 0x100000,
};

#define WCN3990_SWC_WW_IDX_OFFSET 0x3C
#define WCN3990_DST_WW_IDX_OFFSET 0x40

static stwuct ath10k_shadow_weg_cfg tawget_shadow_weg_cfg_map[] = {
		{
			.ce_id = __cpu_to_we16(0),
			.weg_offset = __cpu_to_we16(WCN3990_SWC_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(3),
			.weg_offset = __cpu_to_we16(WCN3990_SWC_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(4),
			.weg_offset = __cpu_to_we16(WCN3990_SWC_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(5),
			.weg_offset =  __cpu_to_we16(WCN3990_SWC_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(7),
			.weg_offset = __cpu_to_we16(WCN3990_SWC_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(1),
			.weg_offset = __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(2),
			.weg_offset =  __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(7),
			.weg_offset =  __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(8),
			.weg_offset =  __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(9),
			.weg_offset = __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(10),
			.weg_offset =  __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},

		{
			.ce_id = __cpu_to_we16(11),
			.weg_offset = __cpu_to_we16(WCN3990_DST_WW_IDX_OFFSET),
		},
};

static stwuct ce_attw host_ce_config_wwan[] = {
	/* CE0: host->tawget HTC contwow stweams */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 16,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath10k_snoc_htc_tx_cb,
	},

	/* CE1: tawget->host HTT + HTC contwow */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath10k_snoc_htt_htc_wx_cb,
	},

	/* CE2: tawget->host WMI */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 64,
		.wecv_cb = ath10k_snoc_htc_wx_cb,
	},

	/* CE3: host->tawget WMI */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath10k_snoc_htc_tx_cb,
	},

	/* CE4: host->tawget HTT */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 2048,
		.swc_sz_max = 256,
		.dest_nentwies = 0,
		.send_cb = ath10k_snoc_htt_tx_cb,
	},

	/* CE5: tawget->host HTT (ipa_uc->tawget ) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 512,
		.dest_nentwies = 512,
		.wecv_cb = ath10k_snoc_htt_wx_cb,
	},

	/* CE6: tawget autonomous hif_memcpy */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},

	/* CE7: ce_diag, the Diagnostic Window */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 2,
		.swc_sz_max = 2048,
		.dest_nentwies = 2,
	},

	/* CE8: Tawget to uMC */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 128,
	},

	/* CE9 tawget->host HTT */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath10k_snoc_htt_htc_wx_cb,
	},

	/* CE10: tawget->host HTT */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath10k_snoc_htt_htc_wx_cb,
	},

	/* CE11: tawget -> host PKTWOG */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath10k_snoc_pktwog_wx_cb,
	},
};

static stwuct ce_pipe_config tawget_ce_config_wwan[] = {
	/* CE0: host->tawget HTC contwow and waw stweams */
	{
		.pipenum = __cpu_to_we32(0),
		.pipediw = __cpu_to_we32(PIPEDIW_OUT),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE1: tawget->host HTT + HTC contwow */
	{
		.pipenum = __cpu_to_we32(1),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE2: tawget->host WMI */
	{
		.pipenum = __cpu_to_we32(2),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(64),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE3: host->tawget WMI */
	{
		.pipenum = __cpu_to_we32(3),
		.pipediw = __cpu_to_we32(PIPEDIW_OUT),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE4: host->tawget HTT */
	{
		.pipenum = __cpu_to_we32(4),
		.pipediw = __cpu_to_we32(PIPEDIW_OUT),
		.nentwies = __cpu_to_we32(256),
		.nbytes_max = __cpu_to_we32(256),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS | CE_ATTW_DIS_INTW),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE5: tawget->host HTT (HIF->HTT) */
	{
		.pipenum = __cpu_to_we32(5),
		.pipediw = __cpu_to_we32(PIPEDIW_OUT),
		.nentwies = __cpu_to_we32(1024),
		.nbytes_max = __cpu_to_we32(64),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS | CE_ATTW_DIS_INTW),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE6: Wesewved fow tawget autonomous hif_memcpy */
	{
		.pipenum = __cpu_to_we32(6),
		.pipediw = __cpu_to_we32(PIPEDIW_INOUT),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(16384),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE7 used onwy by Host */
	{
		.pipenum = __cpu_to_we32(7),
		.pipediw = __cpu_to_we32(4),
		.nentwies = __cpu_to_we32(0),
		.nbytes_max = __cpu_to_we32(0),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS | CE_ATTW_DIS_INTW),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE8 Tawget to uMC */
	{
		.pipenum = __cpu_to_we32(8),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(0),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE9 tawget->host HTT */
	{
		.pipenum = __cpu_to_we32(9),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE10 tawget->host HTT */
	{
		.pipenum = __cpu_to_we32(10),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},

	/* CE11 tawget autonomous qcache memcpy */
	{
		.pipenum = __cpu_to_we32(11),
		.pipediw = __cpu_to_we32(PIPEDIW_IN),
		.nentwies = __cpu_to_we32(32),
		.nbytes_max = __cpu_to_we32(2048),
		.fwags = __cpu_to_we32(CE_ATTW_FWAGS),
		.wesewved = __cpu_to_we32(0),
	},
};

static stwuct ce_sewvice_to_pipe tawget_sewvice_to_ce_map_wwan[] = {
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(3),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(3),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(3),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(3),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_CONTWOW),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(3),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WMI_CONTWOW),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WSVD_CTWW),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(0),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_WSVD_CTWW),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{ /* not used */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_TEST_WAW_STWEAMS),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(0),
	},
	{ /* not used */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_TEST_WAW_STWEAMS),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(2),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_we32(PIPEDIW_OUT),	/* out = UW = host -> tawget */
		__cpu_to_we32(4),
	},
	{
		__cpu_to_we32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(1),
	},
	{ /* not used */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_TEST_WAW_STWEAMS),
		__cpu_to_we32(PIPEDIW_OUT),
		__cpu_to_we32(5),
	},
	{ /* in = DW = tawget -> host */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_HTT_DATA2_MSG),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(9),
	},
	{ /* in = DW = tawget -> host */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_HTT_DATA3_MSG),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(10),
	},
	{ /* in = DW = tawget -> host pktwog */
		__cpu_to_we32(ATH10K_HTC_SVC_ID_HTT_WOG_MSG),
		__cpu_to_we32(PIPEDIW_IN),	/* in = DW = tawget -> host */
		__cpu_to_we32(11),
	},
	/* (Additions hewe) */

	{ /* must be wast */
		__cpu_to_we32(0),
		__cpu_to_we32(0),
		__cpu_to_we32(0),
	},
};

static void ath10k_snoc_wwite32(stwuct ath10k *aw, u32 offset, u32 vawue)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	iowwite32(vawue, aw_snoc->mem + offset);
}

static u32 ath10k_snoc_wead32(stwuct ath10k *aw, u32 offset)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	u32 vaw;

	vaw = iowead32(aw_snoc->mem + offset);

	wetuwn vaw;
}

static int __ath10k_snoc_wx_post_buf(stwuct ath10k_snoc_pipe *pipe)
{
	stwuct ath10k_ce_pipe *ce_pipe = pipe->ce_hdw;
	stwuct ath10k *aw = pipe->hif_ce_state;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct sk_buff *skb;
	dma_addw_t paddw;
	int wet;

	skb = dev_awwoc_skb(pipe->buf_sz);
	if (!skb)
		wetuwn -ENOMEM;

	WAWN_ONCE((unsigned wong)skb->data & 3, "unawigned skb");

	paddw = dma_map_singwe(aw->dev, skb->data,
			       skb->wen + skb_taiwwoom(skb),
			       DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(aw->dev, paddw))) {
		ath10k_wawn(aw, "faiwed to dma map snoc wx buf\n");
		dev_kfwee_skb_any(skb);
		wetuwn -EIO;
	}

	ATH10K_SKB_WXCB(skb)->paddw = paddw;

	spin_wock_bh(&ce->ce_wock);
	wet = ce_pipe->ops->ce_wx_post_buf(ce_pipe, skb, paddw);
	spin_unwock_bh(&ce->ce_wock);
	if (wet) {
		dma_unmap_singwe(aw->dev, paddw, skb->wen + skb_taiwwoom(skb),
				 DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath10k_snoc_wx_post_pipe(stwuct ath10k_snoc_pipe *pipe)
{
	stwuct ath10k *aw = pipe->hif_ce_state;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_pipe = pipe->ce_hdw;
	int wet, num;

	if (pipe->buf_sz == 0)
		wetuwn;

	if (!ce_pipe->dest_wing)
		wetuwn;

	spin_wock_bh(&ce->ce_wock);
	num = __ath10k_ce_wx_num_fwee_bufs(ce_pipe);
	spin_unwock_bh(&ce->ce_wock);
	whiwe (num--) {
		wet = __ath10k_snoc_wx_post_buf(pipe);
		if (wet) {
			if (wet == -ENOSPC)
				bweak;
			ath10k_wawn(aw, "faiwed to post wx buf: %d\n", wet);
			mod_timew(&aw_snoc->wx_post_wetwy, jiffies +
				  ATH10K_SNOC_WX_POST_WETWY_MS);
			bweak;
		}
	}
}

static void ath10k_snoc_wx_post(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int i;

	fow (i = 0; i < CE_COUNT; i++)
		ath10k_snoc_wx_post_pipe(&aw_snoc->pipe_info[i]);
}

static void ath10k_snoc_pwocess_wx_cb(stwuct ath10k_ce_pipe *ce_state,
				      void (*cawwback)(stwuct ath10k *aw,
						       stwuct sk_buff *skb))
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_snoc_pipe *pipe_info =  &aw_snoc->pipe_info[ce_state->id];
	stwuct sk_buff *skb;
	stwuct sk_buff_head wist;
	void *twansfew_context;
	unsigned int nbytes, max_nbytes;

	__skb_queue_head_init(&wist);
	whiwe (ath10k_ce_compweted_wecv_next(ce_state, &twansfew_context,
					     &nbytes) == 0) {
		skb = twansfew_context;
		max_nbytes = skb->wen + skb_taiwwoom(skb);
		dma_unmap_singwe(aw->dev, ATH10K_SKB_WXCB(skb)->paddw,
				 max_nbytes, DMA_FWOM_DEVICE);

		if (unwikewy(max_nbytes < nbytes)) {
			ath10k_wawn(aw, "wxed mowe than expected (nbytes %d, max %d)\n",
				    nbytes, max_nbytes);
			dev_kfwee_skb_any(skb);
			continue;
		}

		skb_put(skb, nbytes);
		__skb_queue_taiw(&wist, skb);
	}

	whiwe ((skb = __skb_dequeue(&wist))) {
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc wx ce pipe %d wen %d\n",
			   ce_state->id, skb->wen);

		cawwback(aw, skb);
	}

	ath10k_snoc_wx_post_pipe(pipe_info);
}

static void ath10k_snoc_htc_wx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	ath10k_snoc_pwocess_wx_cb(ce_state, ath10k_htc_wx_compwetion_handwew);
}

static void ath10k_snoc_htt_htc_wx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	/* CE4 powwing needs to be done whenevew CE pipe which twanspowts
	 * HTT Wx (tawget->host) is pwocessed.
	 */
	ath10k_ce_pew_engine_sewvice(ce_state->aw, CE_POWW_PIPE);

	ath10k_snoc_pwocess_wx_cb(ce_state, ath10k_htc_wx_compwetion_handwew);
}

/* Cawwed by wowew (CE) wayew when data is weceived fwom the Tawget.
 * WCN3990 fiwmwawe uses sepawate CE(CE11) to twansfew pktwog data.
 */
static void ath10k_snoc_pktwog_wx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	ath10k_snoc_pwocess_wx_cb(ce_state, ath10k_htc_wx_compwetion_handwew);
}

static void ath10k_snoc_htt_wx_dewivew(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	skb_puww(skb, sizeof(stwuct ath10k_htc_hdw));
	ath10k_htt_t2h_msg_handwew(aw, skb);
}

static void ath10k_snoc_htt_wx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	ath10k_ce_pew_engine_sewvice(ce_state->aw, CE_POWW_PIPE);
	ath10k_snoc_pwocess_wx_cb(ce_state, ath10k_snoc_htt_wx_dewivew);
}

static void ath10k_snoc_wx_wepwenish_wetwy(stwuct timew_wist *t)
{
	stwuct ath10k_snoc *aw_snoc = fwom_timew(aw_snoc, t, wx_post_wetwy);
	stwuct ath10k *aw = aw_snoc->aw;

	ath10k_snoc_wx_post(aw);
}

static void ath10k_snoc_htc_tx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;

	__skb_queue_head_init(&wist);
	whiwe (ath10k_ce_compweted_send_next(ce_state, (void **)&skb) == 0) {
		if (!skb)
			continue;

		__skb_queue_taiw(&wist, skb);
	}

	whiwe ((skb = __skb_dequeue(&wist)))
		ath10k_htc_tx_compwetion_handwew(aw, skb);
}

static void ath10k_snoc_htt_tx_cb(stwuct ath10k_ce_pipe *ce_state)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct sk_buff *skb;

	whiwe (ath10k_ce_compweted_send_next(ce_state, (void **)&skb) == 0) {
		if (!skb)
			continue;

		dma_unmap_singwe(aw->dev, ATH10K_SKB_CB(skb)->paddw,
				 skb->wen, DMA_TO_DEVICE);
		ath10k_htt_hif_tx_compwete(aw, skb);
	}
}

static int ath10k_snoc_hif_tx_sg(stwuct ath10k *aw, u8 pipe_id,
				 stwuct ath10k_hif_sg_item *items, int n_items)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_snoc_pipe *snoc_pipe;
	stwuct ath10k_ce_pipe *ce_pipe;
	int eww, i = 0;

	snoc_pipe = &aw_snoc->pipe_info[pipe_id];
	ce_pipe = snoc_pipe->ce_hdw;
	spin_wock_bh(&ce->ce_wock);

	fow (i = 0; i < n_items - 1; i++) {
		ath10k_dbg(aw, ATH10K_DBG_SNOC,
			   "snoc tx item %d paddw %pad wen %d n_items %d\n",
			   i, &items[i].paddw, items[i].wen, n_items);

		eww = ath10k_ce_send_nowock(ce_pipe,
					    items[i].twansfew_context,
					    items[i].paddw,
					    items[i].wen,
					    items[i].twansfew_id,
					    CE_SEND_FWAG_GATHEW);
		if (eww)
			goto eww;
	}

	ath10k_dbg(aw, ATH10K_DBG_SNOC,
		   "snoc tx item %d paddw %pad wen %d n_items %d\n",
		   i, &items[i].paddw, items[i].wen, n_items);

	eww = ath10k_ce_send_nowock(ce_pipe,
				    items[i].twansfew_context,
				    items[i].paddw,
				    items[i].wen,
				    items[i].twansfew_id,
				    0);
	if (eww)
		goto eww;

	spin_unwock_bh(&ce->ce_wock);

	wetuwn 0;

eww:
	fow (; i > 0; i--)
		__ath10k_ce_send_wevewt(ce_pipe);

	spin_unwock_bh(&ce->ce_wock);
	wetuwn eww;
}

static int ath10k_snoc_hif_get_tawget_info(stwuct ath10k *aw,
					   stwuct bmi_tawget_info *tawget_info)
{
	tawget_info->vewsion = ATH10K_HW_WCN3990;
	tawget_info->type = ATH10K_HW_WCN3990;

	wetuwn 0;
}

static u16 ath10k_snoc_hif_get_fwee_queue_numbew(stwuct ath10k *aw, u8 pipe)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "hif get fwee queue numbew\n");

	wetuwn ath10k_ce_num_fwee_swc_entwies(aw_snoc->pipe_info[pipe].ce_hdw);
}

static void ath10k_snoc_hif_send_compwete_check(stwuct ath10k *aw, u8 pipe,
						int fowce)
{
	int wesouwces;

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc hif send compwete check\n");

	if (!fowce) {
		wesouwces = ath10k_snoc_hif_get_fwee_queue_numbew(aw, pipe);

		if (wesouwces > (host_ce_config_wwan[pipe].swc_nentwies >> 1))
			wetuwn;
	}
	ath10k_ce_pew_engine_sewvice(aw, pipe);
}

static int ath10k_snoc_hif_map_sewvice_to_pipe(stwuct ath10k *aw,
					       u16 sewvice_id,
					       u8 *uw_pipe, u8 *dw_pipe)
{
	const stwuct ce_sewvice_to_pipe *entwy;
	boow uw_set = fawse, dw_set = fawse;
	int i;

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc hif map sewvice\n");

	fow (i = 0; i < AWWAY_SIZE(tawget_sewvice_to_ce_map_wwan); i++) {
		entwy = &tawget_sewvice_to_ce_map_wwan[i];

		if (__we32_to_cpu(entwy->sewvice_id) != sewvice_id)
			continue;

		switch (__we32_to_cpu(entwy->pipediw)) {
		case PIPEDIW_NONE:
			bweak;
		case PIPEDIW_IN:
			WAWN_ON(dw_set);
			*dw_pipe = __we32_to_cpu(entwy->pipenum);
			dw_set = twue;
			bweak;
		case PIPEDIW_OUT:
			WAWN_ON(uw_set);
			*uw_pipe = __we32_to_cpu(entwy->pipenum);
			uw_set = twue;
			bweak;
		case PIPEDIW_INOUT:
			WAWN_ON(dw_set);
			WAWN_ON(uw_set);
			*dw_pipe = __we32_to_cpu(entwy->pipenum);
			*uw_pipe = __we32_to_cpu(entwy->pipenum);
			dw_set = twue;
			uw_set = twue;
			bweak;
		}
	}

	if (!uw_set || !dw_set)
		wetuwn -ENOENT;

	wetuwn 0;
}

static void ath10k_snoc_hif_get_defauwt_pipe(stwuct ath10k *aw,
					     u8 *uw_pipe, u8 *dw_pipe)
{
	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc hif get defauwt pipe\n");

	(void)ath10k_snoc_hif_map_sewvice_to_pipe(aw,
						 ATH10K_HTC_SVC_ID_WSVD_CTWW,
						 uw_pipe, dw_pipe);
}

static inwine void ath10k_snoc_iwq_disabwe(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int id;

	fow (id = 0; id < CE_COUNT_MAX; id++)
		disabwe_iwq(aw_snoc->ce_iwqs[id].iwq_wine);
}

static inwine void ath10k_snoc_iwq_enabwe(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int id;

	fow (id = 0; id < CE_COUNT_MAX; id++)
		enabwe_iwq(aw_snoc->ce_iwqs[id].iwq_wine);
}

static void ath10k_snoc_wx_pipe_cweanup(stwuct ath10k_snoc_pipe *snoc_pipe)
{
	stwuct ath10k_ce_pipe *ce_pipe;
	stwuct ath10k_ce_wing *ce_wing;
	stwuct sk_buff *skb;
	stwuct ath10k *aw;
	int i;

	aw = snoc_pipe->hif_ce_state;
	ce_pipe = snoc_pipe->ce_hdw;
	ce_wing = ce_pipe->dest_wing;

	if (!ce_wing)
		wetuwn;

	if (!snoc_pipe->buf_sz)
		wetuwn;

	fow (i = 0; i < ce_wing->nentwies; i++) {
		skb = ce_wing->pew_twansfew_context[i];
		if (!skb)
			continue;

		ce_wing->pew_twansfew_context[i] = NUWW;

		dma_unmap_singwe(aw->dev, ATH10K_SKB_WXCB(skb)->paddw,
				 skb->wen + skb_taiwwoom(skb),
				 DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
	}
}

static void ath10k_snoc_tx_pipe_cweanup(stwuct ath10k_snoc_pipe *snoc_pipe)
{
	stwuct ath10k_ce_pipe *ce_pipe;
	stwuct ath10k_ce_wing *ce_wing;
	stwuct sk_buff *skb;
	stwuct ath10k *aw;
	int i;

	aw = snoc_pipe->hif_ce_state;
	ce_pipe = snoc_pipe->ce_hdw;
	ce_wing = ce_pipe->swc_wing;

	if (!ce_wing)
		wetuwn;

	if (!snoc_pipe->buf_sz)
		wetuwn;

	fow (i = 0; i < ce_wing->nentwies; i++) {
		skb = ce_wing->pew_twansfew_context[i];
		if (!skb)
			continue;

		ce_wing->pew_twansfew_context[i] = NUWW;

		ath10k_htc_tx_compwetion_handwew(aw, skb);
	}
}

static void ath10k_snoc_buffew_cweanup(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_snoc_pipe *pipe_info;
	int pipe_num;

	dew_timew_sync(&aw_snoc->wx_post_wetwy);
	fow (pipe_num = 0; pipe_num < CE_COUNT; pipe_num++) {
		pipe_info = &aw_snoc->pipe_info[pipe_num];
		ath10k_snoc_wx_pipe_cweanup(pipe_info);
		ath10k_snoc_tx_pipe_cweanup(pipe_info);
	}
}

static void ath10k_snoc_hif_stop(stwuct ath10k *aw)
{
	if (!test_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags))
		ath10k_snoc_iwq_disabwe(aw);

	ath10k_cowe_napi_sync_disabwe(aw);
	ath10k_snoc_buffew_cweanup(aw);
	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot hif stop\n");
}

static int ath10k_snoc_hif_stawt(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	bitmap_cweaw(aw_snoc->pending_ce_iwqs, 0, CE_COUNT_MAX);

	dev_set_thweaded(&aw->napi_dev, twue);
	ath10k_cowe_napi_enabwe(aw);
	ath10k_snoc_iwq_enabwe(aw);
	ath10k_snoc_wx_post(aw);

	cweaw_bit(ATH10K_SNOC_FWAG_WECOVEWY, &aw_snoc->fwags);

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot hif stawt\n");

	wetuwn 0;
}

static int ath10k_snoc_init_pipes(stwuct ath10k *aw)
{
	int i, wet;

	fow (i = 0; i < CE_COUNT; i++) {
		wet = ath10k_ce_init_pipe(aw, i, &host_ce_config_wwan[i]);
		if (wet) {
			ath10k_eww(aw, "faiwed to initiawize copy engine pipe %d: %d\n",
				   i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ath10k_snoc_wwan_enabwe(stwuct ath10k *aw,
				   enum ath10k_fiwmwawe_mode fw_mode)
{
	stwuct ath10k_tgt_pipe_cfg tgt_cfg[CE_COUNT_MAX];
	stwuct ath10k_qmi_wwan_enabwe_cfg cfg;
	enum wwfw_dwivew_mode_enum_v01 mode;
	int pipe_num;

	fow (pipe_num = 0; pipe_num < CE_COUNT_MAX; pipe_num++) {
		tgt_cfg[pipe_num].pipe_num =
				tawget_ce_config_wwan[pipe_num].pipenum;
		tgt_cfg[pipe_num].pipe_diw =
				tawget_ce_config_wwan[pipe_num].pipediw;
		tgt_cfg[pipe_num].nentwies =
				tawget_ce_config_wwan[pipe_num].nentwies;
		tgt_cfg[pipe_num].nbytes_max =
				tawget_ce_config_wwan[pipe_num].nbytes_max;
		tgt_cfg[pipe_num].fwags =
				tawget_ce_config_wwan[pipe_num].fwags;
		tgt_cfg[pipe_num].wesewved = 0;
	}

	cfg.num_ce_tgt_cfg = sizeof(tawget_ce_config_wwan) /
				sizeof(stwuct ath10k_tgt_pipe_cfg);
	cfg.ce_tgt_cfg = (stwuct ath10k_tgt_pipe_cfg *)
		&tgt_cfg;
	cfg.num_ce_svc_pipe_cfg = sizeof(tawget_sewvice_to_ce_map_wwan) /
				  sizeof(stwuct ath10k_svc_pipe_cfg);
	cfg.ce_svc_cfg = (stwuct ath10k_svc_pipe_cfg *)
		&tawget_sewvice_to_ce_map_wwan;
	cfg.num_shadow_weg_cfg = AWWAY_SIZE(tawget_shadow_weg_cfg_map);
	cfg.shadow_weg_cfg = (stwuct ath10k_shadow_weg_cfg *)
		&tawget_shadow_weg_cfg_map;

	switch (fw_mode) {
	case ATH10K_FIWMWAWE_MODE_NOWMAW:
		mode = QMI_WWFW_MISSION_V01;
		bweak;
	case ATH10K_FIWMWAWE_MODE_UTF:
		mode = QMI_WWFW_FTM_V01;
		bweak;
	defauwt:
		ath10k_eww(aw, "invawid fiwmwawe mode %d\n", fw_mode);
		wetuwn -EINVAW;
	}

	wetuwn ath10k_qmi_wwan_enabwe(aw, &cfg, mode,
				       NUWW);
}

static int ath10k_hw_powew_on(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "soc powew on\n");

	wet = weguwatow_buwk_enabwe(aw_snoc->num_vwegs, aw_snoc->vwegs);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(aw_snoc->num_cwks, aw_snoc->cwks);
	if (wet)
		goto vweg_off;

	wetuwn wet;

vweg_off:
	weguwatow_buwk_disabwe(aw_snoc->num_vwegs, aw_snoc->vwegs);
	wetuwn wet;
}

static int ath10k_hw_powew_off(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "soc powew off\n");

	cwk_buwk_disabwe_unpwepawe(aw_snoc->num_cwks, aw_snoc->cwks);

	wetuwn weguwatow_buwk_disabwe(aw_snoc->num_vwegs, aw_snoc->vwegs);
}

static void ath10k_snoc_wwan_disabwe(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	/* If both ATH10K_FWAG_CWASH_FWUSH and ATH10K_SNOC_FWAG_WECOVEWY
	 * fwags awe not set, it means that the dwivew has westawted
	 * due to a cwash inject via debugfs. In this case, the dwivew
	 * needs to westawt the fiwmwawe and hence send qmi wwan disabwe,
	 * duwing the dwivew westawt sequence.
	 */
	if (!test_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags) ||
	    !test_bit(ATH10K_SNOC_FWAG_WECOVEWY, &aw_snoc->fwags))
		ath10k_qmi_wwan_disabwe(aw);
}

static void ath10k_snoc_hif_powew_down(stwuct ath10k *aw)
{
	ath10k_dbg(aw, ATH10K_DBG_BOOT, "boot hif powew down\n");

	ath10k_snoc_wwan_disabwe(aw);
	ath10k_ce_fwee_wwi(aw);
	ath10k_hw_powew_off(aw);
}

static int ath10k_snoc_hif_powew_up(stwuct ath10k *aw,
				    enum ath10k_fiwmwawe_mode fw_mode)
{
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "%s:WCN3990 dwivew state = %d\n",
		   __func__, aw->state);

	wet = ath10k_hw_powew_on(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to powew on device: %d\n", wet);
		wetuwn wet;
	}

	wet = ath10k_snoc_wwan_enabwe(aw, fw_mode);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe wcn3990: %d\n", wet);
		goto eww_hw_powew_off;
	}

	ath10k_ce_awwoc_wwi(aw);

	wet = ath10k_snoc_init_pipes(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to initiawize CE: %d\n", wet);
		goto eww_fwee_wwi;
	}

	ath10k_ce_enabwe_intewwupts(aw);

	wetuwn 0;

eww_fwee_wwi:
	ath10k_ce_fwee_wwi(aw);
	ath10k_snoc_wwan_disabwe(aw);

eww_hw_powew_off:
	ath10k_hw_powew_off(aw);

	wetuwn wet;
}

static int ath10k_snoc_hif_set_tawget_wog_mode(stwuct ath10k *aw,
					       u8 fw_wog_mode)
{
	u8 fw_dbg_mode;

	if (fw_wog_mode)
		fw_dbg_mode = ATH10K_ENABWE_FW_WOG_CE;
	ewse
		fw_dbg_mode = ATH10K_ENABWE_FW_WOG_DIAG;

	wetuwn ath10k_qmi_set_fw_wog_mode(aw, fw_dbg_mode);
}

#ifdef CONFIG_PM
static int ath10k_snoc_hif_suspend(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int wet;

	if (!device_may_wakeup(aw->dev))
		wetuwn -EPEWM;

	wet = enabwe_iwq_wake(aw_snoc->ce_iwqs[ATH10K_SNOC_WAKE_IWQ].iwq_wine);
	if (wet) {
		ath10k_eww(aw, "faiwed to enabwe wakeup iwq :%d\n", wet);
		wetuwn wet;
	}

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc device suspended\n");

	wetuwn wet;
}

static int ath10k_snoc_hif_wesume(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int wet;

	if (!device_may_wakeup(aw->dev))
		wetuwn -EPEWM;

	wet = disabwe_iwq_wake(aw_snoc->ce_iwqs[ATH10K_SNOC_WAKE_IWQ].iwq_wine);
	if (wet) {
		ath10k_eww(aw, "faiwed to disabwe wakeup iwq: %d\n", wet);
		wetuwn wet;
	}

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc device wesumed\n");

	wetuwn wet;
}
#endif

static const stwuct ath10k_hif_ops ath10k_snoc_hif_ops = {
	.wead32		= ath10k_snoc_wead32,
	.wwite32	= ath10k_snoc_wwite32,
	.stawt		= ath10k_snoc_hif_stawt,
	.stop		= ath10k_snoc_hif_stop,
	.map_sewvice_to_pipe	= ath10k_snoc_hif_map_sewvice_to_pipe,
	.get_defauwt_pipe	= ath10k_snoc_hif_get_defauwt_pipe,
	.powew_up		= ath10k_snoc_hif_powew_up,
	.powew_down		= ath10k_snoc_hif_powew_down,
	.tx_sg			= ath10k_snoc_hif_tx_sg,
	.send_compwete_check	= ath10k_snoc_hif_send_compwete_check,
	.get_fwee_queue_numbew	= ath10k_snoc_hif_get_fwee_queue_numbew,
	.get_tawget_info	= ath10k_snoc_hif_get_tawget_info,
	.set_tawget_wog_mode    = ath10k_snoc_hif_set_tawget_wog_mode,

#ifdef CONFIG_PM
	.suspend                = ath10k_snoc_hif_suspend,
	.wesume                 = ath10k_snoc_hif_wesume,
#endif
};

static const stwuct ath10k_bus_ops ath10k_snoc_bus_ops = {
	.wead32		= ath10k_snoc_wead32,
	.wwite32	= ath10k_snoc_wwite32,
};

static int ath10k_snoc_get_ce_id_fwom_iwq(stwuct ath10k *aw, int iwq)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int i;

	fow (i = 0; i < CE_COUNT_MAX; i++) {
		if (aw_snoc->ce_iwqs[i].iwq_wine == iwq)
			wetuwn i;
	}
	ath10k_eww(aw, "No matching CE id fow iwq %d\n", iwq);

	wetuwn -EINVAW;
}

static iwqwetuwn_t ath10k_snoc_pew_engine_handwew(int iwq, void *awg)
{
	stwuct ath10k *aw = awg;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int ce_id = ath10k_snoc_get_ce_id_fwom_iwq(aw, iwq);

	if (ce_id < 0 || ce_id >= AWWAY_SIZE(aw_snoc->pipe_info)) {
		ath10k_wawn(aw, "unexpected/invawid iwq %d ce_id %d\n", iwq,
			    ce_id);
		wetuwn IWQ_HANDWED;
	}

	ath10k_ce_disabwe_intewwupt(aw, ce_id);
	set_bit(ce_id, aw_snoc->pending_ce_iwqs);

	napi_scheduwe(&aw->napi);

	wetuwn IWQ_HANDWED;
}

static int ath10k_snoc_napi_poww(stwuct napi_stwuct *ctx, int budget)
{
	stwuct ath10k *aw = containew_of(ctx, stwuct ath10k, napi);
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int done = 0;
	int ce_id;

	if (test_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags)) {
		napi_compwete(ctx);
		wetuwn done;
	}

	fow (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		if (test_and_cweaw_bit(ce_id, aw_snoc->pending_ce_iwqs)) {
			ath10k_ce_pew_engine_sewvice(aw, ce_id);
			ath10k_ce_enabwe_intewwupt(aw, ce_id);
		}

	done = ath10k_htt_txwx_compw_task(aw, budget);

	if (done < budget)
		napi_compwete(ctx);

	wetuwn done;
}

static void ath10k_snoc_init_napi(stwuct ath10k *aw)
{
	netif_napi_add(&aw->napi_dev, &aw->napi, ath10k_snoc_napi_poww);
}

static int ath10k_snoc_wequest_iwq(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int wet, id;

	fow (id = 0; id < CE_COUNT_MAX; id++) {
		wet = wequest_iwq(aw_snoc->ce_iwqs[id].iwq_wine,
				  ath10k_snoc_pew_engine_handwew,
				  IWQF_NO_AUTOEN, ce_name[id], aw);
		if (wet) {
			ath10k_eww(aw,
				   "faiwed to wegistew IWQ handwew fow CE %d: %d\n",
				   id, wet);
			goto eww_iwq;
		}
	}

	wetuwn 0;

eww_iwq:
	fow (id -= 1; id >= 0; id--)
		fwee_iwq(aw_snoc->ce_iwqs[id].iwq_wine, aw);

	wetuwn wet;
}

static void ath10k_snoc_fwee_iwq(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	int id;

	fow (id = 0; id < CE_COUNT_MAX; id++)
		fwee_iwq(aw_snoc->ce_iwqs[id].iwq_wine, aw);
}

static int ath10k_snoc_wesouwce_init(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *wes;
	int i, wet = 0;

	pdev = aw_snoc->dev;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "membase");
	if (!wes) {
		ath10k_eww(aw, "Memowy base not found in DT\n");
		wetuwn -EINVAW;
	}

	aw_snoc->mem_pa = wes->stawt;
	aw_snoc->mem = devm_iowemap(&pdev->dev, aw_snoc->mem_pa,
				    wesouwce_size(wes));
	if (!aw_snoc->mem) {
		ath10k_eww(aw, "Memowy base iowemap faiwed with physicaw addwess %pa\n",
			   &aw_snoc->mem_pa);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < CE_COUNT; i++) {
		wet = pwatfowm_get_iwq(aw_snoc->dev, i);
		if (wet < 0)
			wetuwn wet;
		aw_snoc->ce_iwqs[i].iwq_wine = wet;
	}

	wet = device_pwopewty_wead_u32(&pdev->dev, "qcom,xo-caw-data",
				       &aw_snoc->xo_caw_data);
	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc xo-caw-data wetuwn %d\n", wet);
	if (wet == 0) {
		aw_snoc->xo_caw_suppowted = twue;
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "xo caw data %x\n",
			   aw_snoc->xo_caw_data);
	}

	wetuwn 0;
}

static void ath10k_snoc_quiwks_init(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct device *dev = &aw_snoc->dev->dev;

	if (of_pwopewty_wead_boow(dev->of_node, "qcom,snoc-host-cap-8bit-quiwk"))
		set_bit(ATH10K_SNOC_FWAG_8BIT_HOST_CAP_QUIWK, &aw_snoc->fwags);
}

int ath10k_snoc_fw_indication(stwuct ath10k *aw, u64 type)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_bus_pawams bus_pawams = {};
	int wet;

	if (test_bit(ATH10K_SNOC_FWAG_UNWEGISTEWING, &aw_snoc->fwags))
		wetuwn 0;

	switch (type) {
	case ATH10K_QMI_EVENT_FW_WEADY_IND:
		if (test_bit(ATH10K_SNOC_FWAG_WEGISTEWED, &aw_snoc->fwags)) {
			ath10k_cowe_stawt_wecovewy(aw);
			bweak;
		}

		bus_pawams.dev_type = ATH10K_DEV_TYPE_WW;
		bus_pawams.chip_id = aw_snoc->tawget_info.soc_vewsion;
		wet = ath10k_cowe_wegistew(aw, &bus_pawams);
		if (wet) {
			ath10k_eww(aw, "Faiwed to wegistew dwivew cowe: %d\n",
				   wet);
			wetuwn wet;
		}
		set_bit(ATH10K_SNOC_FWAG_WEGISTEWED, &aw_snoc->fwags);
		bweak;
	case ATH10K_QMI_EVENT_FW_DOWN_IND:
		set_bit(ATH10K_SNOC_FWAG_WECOVEWY, &aw_snoc->fwags);
		set_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags);
		bweak;
	defauwt:
		ath10k_eww(aw, "invawid fw indication: %wwx\n", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ath10k_snoc_setup_wesouwce(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_snoc_pipe *pipe;
	int i, wet;

	timew_setup(&aw_snoc->wx_post_wetwy, ath10k_snoc_wx_wepwenish_wetwy, 0);
	spin_wock_init(&ce->ce_wock);
	fow (i = 0; i < CE_COUNT; i++) {
		pipe = &aw_snoc->pipe_info[i];
		pipe->ce_hdw = &ce->ce_states[i];
		pipe->pipe_num = i;
		pipe->hif_ce_state = aw;

		wet = ath10k_ce_awwoc_pipe(aw, i, &host_ce_config_wwan[i]);
		if (wet) {
			ath10k_eww(aw, "faiwed to awwocate copy engine pipe %d: %d\n",
				   i, wet);
			wetuwn wet;
		}

		pipe->buf_sz = host_ce_config_wwan[i].swc_sz_max;
	}
	ath10k_snoc_init_napi(aw);

	wetuwn 0;
}

static void ath10k_snoc_wewease_wesouwce(stwuct ath10k *aw)
{
	int i;

	netif_napi_dew(&aw->napi);
	fow (i = 0; i < CE_COUNT; i++)
		ath10k_ce_fwee_pipe(aw, i);
}

static void ath10k_msa_dump_memowy(stwuct ath10k *aw,
				   stwuct ath10k_fw_cwash_data *cwash_data)
{
	const stwuct ath10k_hw_mem_wayout *mem_wayout;
	const stwuct ath10k_mem_wegion *cuwwent_wegion;
	stwuct ath10k_dump_wam_data_hdw *hdw;
	size_t buf_wen;
	u8 *buf;

	if (!cwash_data || !cwash_data->wamdump_buf)
		wetuwn;

	mem_wayout = ath10k_cowedump_get_mem_wayout(aw);
	if (!mem_wayout)
		wetuwn;

	cuwwent_wegion = &mem_wayout->wegion_tabwe.wegions[0];

	buf = cwash_data->wamdump_buf;
	buf_wen = cwash_data->wamdump_buf_wen;
	memset(buf, 0, buf_wen);

	/* Wesewve space fow the headew. */
	hdw = (void *)buf;
	buf += sizeof(*hdw);
	buf_wen -= sizeof(*hdw);

	hdw->wegion_type = cpu_to_we32(cuwwent_wegion->type);
	hdw->stawt = cpu_to_we32((unsigned wong)aw->msa.vaddw);
	hdw->wength = cpu_to_we32(aw->msa.mem_size);

	if (cuwwent_wegion->wen < aw->msa.mem_size) {
		memcpy(buf, aw->msa.vaddw, cuwwent_wegion->wen);
		ath10k_wawn(aw, "msa dump wength is wess than msa size %x, %x\n",
			    cuwwent_wegion->wen, aw->msa.mem_size);
	} ewse {
		memcpy(buf, aw->msa.vaddw, aw->msa.mem_size);
	}
}

void ath10k_snoc_fw_cwashed_dump(stwuct ath10k *aw)
{
	stwuct ath10k_fw_cwash_data *cwash_data;
	chaw guid[UUID_STWING_WEN + 1];

	mutex_wock(&aw->dump_mutex);

	spin_wock_bh(&aw->data_wock);
	aw->stats.fw_cwash_countew++;
	spin_unwock_bh(&aw->data_wock);

	cwash_data = ath10k_cowedump_new(aw);

	if (cwash_data)
		scnpwintf(guid, sizeof(guid), "%pUw", &cwash_data->guid);
	ewse
		scnpwintf(guid, sizeof(guid), "n/a");

	ath10k_eww(aw, "fiwmwawe cwashed! (guid %s)\n", guid);
	ath10k_pwint_dwivew_info(aw);
	ath10k_msa_dump_memowy(aw, cwash_data);
	mutex_unwock(&aw->dump_mutex);
}

static int ath10k_snoc_modem_notify(stwuct notifiew_bwock *nb, unsigned wong action,
				    void *data)
{
	stwuct ath10k_snoc *aw_snoc = containew_of(nb, stwuct ath10k_snoc, nb);
	stwuct ath10k *aw = aw_snoc->aw;
	stwuct qcom_ssw_notify_data *notify_data = data;

	switch (action) {
	case QCOM_SSW_BEFOWE_POWEWUP:
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "weceived modem stawting event\n");
		cweaw_bit(ATH10K_SNOC_FWAG_MODEM_STOPPED, &aw_snoc->fwags);
		bweak;

	case QCOM_SSW_AFTEW_POWEWUP:
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "weceived modem wunning event\n");
		bweak;

	case QCOM_SSW_BEFOWE_SHUTDOWN:
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "weceived modem %s event\n",
			   notify_data->cwashed ? "cwashed" : "stopping");
		if (!notify_data->cwashed)
			set_bit(ATH10K_SNOC_FWAG_MODEM_STOPPED, &aw_snoc->fwags);
		ewse
			cweaw_bit(ATH10K_SNOC_FWAG_MODEM_STOPPED, &aw_snoc->fwags);
		bweak;

	case QCOM_SSW_AFTEW_SHUTDOWN:
		ath10k_dbg(aw, ATH10K_DBG_SNOC, "weceived modem offwine event\n");
		bweak;

	defauwt:
		ath10k_eww(aw, "weceived unwecognized event %wu\n", action);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int ath10k_modem_init(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	void *notifiew;
	int wet;

	aw_snoc->nb.notifiew_caww = ath10k_snoc_modem_notify;

	notifiew = qcom_wegistew_ssw_notifiew("mpss", &aw_snoc->nb);
	if (IS_EWW(notifiew)) {
		wet = PTW_EWW(notifiew);
		ath10k_eww(aw, "faiwed to initiawize modem notifiew: %d\n", wet);
		wetuwn wet;
	}

	aw_snoc->notifiew = notifiew;

	wetuwn 0;
}

static void ath10k_modem_deinit(stwuct ath10k *aw)
{
	int wet;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	wet = qcom_unwegistew_ssw_notifiew(aw_snoc->notifiew, &aw_snoc->nb);
	if (wet)
		ath10k_eww(aw, "ewwow %d unwegistewing notifiew\n", wet);
}

static int ath10k_setup_msa_wesouwces(stwuct ath10k *aw, u32 msa_size)
{
	stwuct device *dev = aw->dev;
	stwuct device_node *node;
	stwuct wesouwce w;
	int wet;

	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (node) {
		wet = of_addwess_to_wesouwce(node, 0, &w);
		of_node_put(node);
		if (wet) {
			dev_eww(dev, "faiwed to wesowve msa fixed wegion\n");
			wetuwn wet;
		}

		aw->msa.paddw = w.stawt;
		aw->msa.mem_size = wesouwce_size(&w);
		aw->msa.vaddw = devm_memwemap(dev, aw->msa.paddw,
					      aw->msa.mem_size,
					      MEMWEMAP_WT);
		if (IS_EWW(aw->msa.vaddw)) {
			dev_eww(dev, "faiwed to map memowy wegion: %pa\n",
				&w.stawt);
			wetuwn PTW_EWW(aw->msa.vaddw);
		}
	} ewse {
		aw->msa.vaddw = dmam_awwoc_cohewent(dev, msa_size,
						    &aw->msa.paddw,
						    GFP_KEWNEW);
		if (!aw->msa.vaddw) {
			ath10k_eww(aw, "faiwed to awwocate dma memowy fow msa wegion\n");
			wetuwn -ENOMEM;
		}
		aw->msa.mem_size = msa_size;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi msa.paddw: %pad , msa.vaddw: 0x%p\n",
		   &aw->msa.paddw,
		   aw->msa.vaddw);

	wetuwn 0;
}

static int ath10k_fw_init(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct device *host_dev = &aw_snoc->dev->dev;
	stwuct pwatfowm_device_info info;
	stwuct iommu_domain *iommu_dom;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *node;
	int wet;

	node = of_get_chiwd_by_name(host_dev->of_node, "wifi-fiwmwawe");
	if (!node) {
		aw_snoc->use_tz = twue;
		wetuwn 0;
	}

	memset(&info, 0, sizeof(info));
	info.fwnode = &node->fwnode;
	info.pawent = host_dev;
	info.name = node->name;
	info.dma_mask = DMA_BIT_MASK(32);

	pdev = pwatfowm_device_wegistew_fuww(&info);
	if (IS_EWW(pdev)) {
		of_node_put(node);
		wetuwn PTW_EWW(pdev);
	}

	pdev->dev.of_node = node;

	wet = of_dma_configuwe(&pdev->dev, node, twue);
	if (wet) {
		ath10k_eww(aw, "dma configuwe faiw: %d\n", wet);
		goto eww_unwegistew;
	}

	aw_snoc->fw.dev = &pdev->dev;

	iommu_dom = iommu_domain_awwoc(&pwatfowm_bus_type);
	if (!iommu_dom) {
		ath10k_eww(aw, "faiwed to awwocate iommu domain\n");
		wet = -ENOMEM;
		goto eww_unwegistew;
	}

	wet = iommu_attach_device(iommu_dom, aw_snoc->fw.dev);
	if (wet) {
		ath10k_eww(aw, "couwd not attach device: %d\n", wet);
		goto eww_iommu_fwee;
	}

	aw_snoc->fw.iommu_domain = iommu_dom;
	aw_snoc->fw.fw_stawt_addw = aw->msa.paddw;

	wet = iommu_map(iommu_dom, aw_snoc->fw.fw_stawt_addw,
			aw->msa.paddw, aw->msa.mem_size,
			IOMMU_WEAD | IOMMU_WWITE, GFP_KEWNEW);
	if (wet) {
		ath10k_eww(aw, "faiwed to map fiwmwawe wegion: %d\n", wet);
		goto eww_iommu_detach;
	}

	of_node_put(node);

	wetuwn 0;

eww_iommu_detach:
	iommu_detach_device(iommu_dom, aw_snoc->fw.dev);

eww_iommu_fwee:
	iommu_domain_fwee(iommu_dom);

eww_unwegistew:
	pwatfowm_device_unwegistew(pdev);
	of_node_put(node);

	wetuwn wet;
}

static int ath10k_fw_deinit(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	const size_t mapped_size = aw_snoc->fw.mapped_mem_size;
	stwuct iommu_domain *iommu;
	size_t unmapped_size;

	if (aw_snoc->use_tz)
		wetuwn 0;

	iommu = aw_snoc->fw.iommu_domain;

	unmapped_size = iommu_unmap(iommu, aw_snoc->fw.fw_stawt_addw,
				    mapped_size);
	if (unmapped_size != mapped_size)
		ath10k_eww(aw, "faiwed to unmap fiwmwawe: %zu\n",
			   unmapped_size);

	iommu_detach_device(iommu, aw_snoc->fw.dev);
	iommu_domain_fwee(iommu);

	pwatfowm_device_unwegistew(to_pwatfowm_device(aw_snoc->fw.dev));

	wetuwn 0;
}

static const stwuct of_device_id ath10k_snoc_dt_match[] = {
	{ .compatibwe = "qcom,wcn3990-wifi",
	 .data = &dwv_pwiv,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ath10k_snoc_dt_match);

static int ath10k_snoc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ath10k_snoc_dwv_pwiv *dwv_data;
	stwuct ath10k_snoc *aw_snoc;
	stwuct device *dev;
	stwuct ath10k *aw;
	u32 msa_size;
	int wet;
	u32 i;

	dev = &pdev->dev;
	dwv_data = device_get_match_data(dev);
	if (!dwv_data) {
		dev_eww(dev, "faiwed to find matching device twee id\n");
		wetuwn -EINVAW;
	}

	wet = dma_set_mask_and_cohewent(dev, dwv_data->dma_mask);
	if (wet) {
		dev_eww(dev, "faiwed to set dma mask: %d\n", wet);
		wetuwn wet;
	}

	aw = ath10k_cowe_cweate(sizeof(*aw_snoc), dev, ATH10K_BUS_SNOC,
				dwv_data->hw_wev, &ath10k_snoc_hif_ops);
	if (!aw) {
		dev_eww(dev, "faiwed to awwocate cowe\n");
		wetuwn -ENOMEM;
	}

	aw_snoc = ath10k_snoc_pwiv(aw);
	aw_snoc->dev = pdev;
	pwatfowm_set_dwvdata(pdev, aw);
	aw_snoc->aw = aw;
	aw_snoc->ce.bus_ops = &ath10k_snoc_bus_ops;
	aw->ce_pwiv = &aw_snoc->ce;
	msa_size = dwv_data->msa_size;

	ath10k_snoc_quiwks_init(aw);

	wet = ath10k_snoc_wesouwce_init(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to initiawize wesouwce: %d\n", wet);
		goto eww_cowe_destwoy;
	}

	wet = ath10k_snoc_setup_wesouwce(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to setup wesouwce: %d\n", wet);
		goto eww_cowe_destwoy;
	}
	wet = ath10k_snoc_wequest_iwq(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wequest iwqs: %d\n", wet);
		goto eww_wewease_wesouwce;
	}

	aw_snoc->num_vwegs = AWWAY_SIZE(ath10k_weguwatows);
	aw_snoc->vwegs = devm_kcawwoc(&pdev->dev, aw_snoc->num_vwegs,
				      sizeof(*aw_snoc->vwegs), GFP_KEWNEW);
	if (!aw_snoc->vwegs) {
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}
	fow (i = 0; i < aw_snoc->num_vwegs; i++)
		aw_snoc->vwegs[i].suppwy = ath10k_weguwatows[i];

	wet = devm_weguwatow_buwk_get(&pdev->dev, aw_snoc->num_vwegs,
				      aw_snoc->vwegs);
	if (wet < 0)
		goto eww_fwee_iwq;

	aw_snoc->num_cwks = AWWAY_SIZE(ath10k_cwocks);
	aw_snoc->cwks = devm_kcawwoc(&pdev->dev, aw_snoc->num_cwks,
				     sizeof(*aw_snoc->cwks), GFP_KEWNEW);
	if (!aw_snoc->cwks) {
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}

	fow (i = 0; i < aw_snoc->num_cwks; i++)
		aw_snoc->cwks[i].id = ath10k_cwocks[i];

	wet = devm_cwk_buwk_get_optionaw(&pdev->dev, aw_snoc->num_cwks,
					 aw_snoc->cwks);
	if (wet)
		goto eww_fwee_iwq;

	wet = ath10k_setup_msa_wesouwces(aw, msa_size);
	if (wet) {
		ath10k_wawn(aw, "faiwed to setup msa wesouwces: %d\n", wet);
		goto eww_fwee_iwq;
	}

	wet = ath10k_fw_init(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to initiawize fiwmwawe: %d\n", wet);
		goto eww_fwee_iwq;
	}

	wet = ath10k_qmi_init(aw, msa_size);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wegistew wwfw qmi cwient: %d\n", wet);
		goto eww_fw_deinit;
	}

	wet = ath10k_modem_init(aw);
	if (wet)
		goto eww_qmi_deinit;

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc pwobe\n");

	wetuwn 0;

eww_qmi_deinit:
	ath10k_qmi_deinit(aw);

eww_fw_deinit:
	ath10k_fw_deinit(aw);

eww_fwee_iwq:
	ath10k_snoc_fwee_iwq(aw);

eww_wewease_wesouwce:
	ath10k_snoc_wewease_wesouwce(aw);

eww_cowe_destwoy:
	ath10k_cowe_destwoy(aw);

	wetuwn wet;
}

static int ath10k_snoc_fwee_wesouwces(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc fwee wesouwces\n");

	set_bit(ATH10K_SNOC_FWAG_UNWEGISTEWING, &aw_snoc->fwags);

	ath10k_cowe_unwegistew(aw);
	ath10k_fw_deinit(aw);
	ath10k_snoc_fwee_iwq(aw);
	ath10k_snoc_wewease_wesouwce(aw);
	ath10k_modem_deinit(aw);
	ath10k_qmi_deinit(aw);
	ath10k_cowe_destwoy(aw);

	wetuwn 0;
}

static void ath10k_snoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ath10k *aw = pwatfowm_get_dwvdata(pdev);
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc wemove\n");

	weinit_compwetion(&aw->dwivew_wecovewy);

	if (test_bit(ATH10K_SNOC_FWAG_WECOVEWY, &aw_snoc->fwags))
		wait_fow_compwetion_timeout(&aw->dwivew_wecovewy, 3 * HZ);

	ath10k_snoc_fwee_wesouwces(aw);
}

static void ath10k_snoc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct ath10k *aw = pwatfowm_get_dwvdata(pdev);

	ath10k_dbg(aw, ATH10K_DBG_SNOC, "snoc shutdown\n");
	ath10k_snoc_fwee_wesouwces(aw);
}

static stwuct pwatfowm_dwivew ath10k_snoc_dwivew = {
	.pwobe  = ath10k_snoc_pwobe,
	.wemove_new = ath10k_snoc_wemove,
	.shutdown = ath10k_snoc_shutdown,
	.dwivew = {
		.name   = "ath10k_snoc",
		.of_match_tabwe = ath10k_snoc_dt_match,
	},
};
moduwe_pwatfowm_dwivew(ath10k_snoc_dwivew);

MODUWE_AUTHOW("Quawcomm");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Dwivew suppowt fow Athewos WCN3990 SNOC devices");
