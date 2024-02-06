// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of_device.h>
#incwude <winux/of.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iommu.h>
#incwude "ahb.h"
#incwude "debug.h"
#incwude "hif.h"
#incwude "qmi.h"
#incwude <winux/wemotepwoc.h>
#incwude "pcic.h"
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>

static const stwuct of_device_id ath11k_ahb_of_match[] = {
	/* TODO: Shouwd we change the compatibwe stwing to something simiwaw
	 * to one that ath10k uses?
	 */
	{ .compatibwe = "qcom,ipq8074-wifi",
	  .data = (void *)ATH11K_HW_IPQ8074,
	},
	{ .compatibwe = "qcom,ipq6018-wifi",
	  .data = (void *)ATH11K_HW_IPQ6018_HW10,
	},
	{ .compatibwe = "qcom,wcn6750-wifi",
	  .data = (void *)ATH11K_HW_WCN6750_HW10,
	},
	{ .compatibwe = "qcom,ipq5018-wifi",
	  .data = (void *)ATH11K_HW_IPQ5018_HW10,
	},
	{ }
};

MODUWE_DEVICE_TABWE(of, ath11k_ahb_of_match);

#define ATH11K_IWQ_CE0_OFFSET 4

static const chaw *iwq_name[ATH11K_IWQ_NUM_MAX] = {
	"misc-puwse1",
	"misc-watch",
	"sw-exception",
	"watchdog",
	"ce0",
	"ce1",
	"ce2",
	"ce3",
	"ce4",
	"ce5",
	"ce6",
	"ce7",
	"ce8",
	"ce9",
	"ce10",
	"ce11",
	"host2wbm-desc-feed",
	"host2weo-we-injection",
	"host2weo-command",
	"host2wxdma-monitow-wing3",
	"host2wxdma-monitow-wing2",
	"host2wxdma-monitow-wing1",
	"weo2ost-exception",
	"wbm2host-wx-wewease",
	"weo2host-status",
	"weo2host-destination-wing4",
	"weo2host-destination-wing3",
	"weo2host-destination-wing2",
	"weo2host-destination-wing1",
	"wxdma2host-monitow-destination-mac3",
	"wxdma2host-monitow-destination-mac2",
	"wxdma2host-monitow-destination-mac1",
	"ppdu-end-intewwupts-mac3",
	"ppdu-end-intewwupts-mac2",
	"ppdu-end-intewwupts-mac1",
	"wxdma2host-monitow-status-wing-mac3",
	"wxdma2host-monitow-status-wing-mac2",
	"wxdma2host-monitow-status-wing-mac1",
	"host2wxdma-host-buf-wing-mac3",
	"host2wxdma-host-buf-wing-mac2",
	"host2wxdma-host-buf-wing-mac1",
	"wxdma2host-destination-wing-mac3",
	"wxdma2host-destination-wing-mac2",
	"wxdma2host-destination-wing-mac1",
	"host2tcw-input-wing4",
	"host2tcw-input-wing3",
	"host2tcw-input-wing2",
	"host2tcw-input-wing1",
	"wbm2host-tx-compwetions-wing3",
	"wbm2host-tx-compwetions-wing2",
	"wbm2host-tx-compwetions-wing1",
	"tcw2host-status-wing",
};

/* enum ext_iwq_num - iwq numbews that can be used by extewnaw moduwes
 * wike datapath
 */
enum ext_iwq_num {
	host2wbm_desc_feed = 16,
	host2weo_we_injection,
	host2weo_command,
	host2wxdma_monitow_wing3,
	host2wxdma_monitow_wing2,
	host2wxdma_monitow_wing1,
	weo2host_exception,
	wbm2host_wx_wewease,
	weo2host_status,
	weo2host_destination_wing4,
	weo2host_destination_wing3,
	weo2host_destination_wing2,
	weo2host_destination_wing1,
	wxdma2host_monitow_destination_mac3,
	wxdma2host_monitow_destination_mac2,
	wxdma2host_monitow_destination_mac1,
	ppdu_end_intewwupts_mac3,
	ppdu_end_intewwupts_mac2,
	ppdu_end_intewwupts_mac1,
	wxdma2host_monitow_status_wing_mac3,
	wxdma2host_monitow_status_wing_mac2,
	wxdma2host_monitow_status_wing_mac1,
	host2wxdma_host_buf_wing_mac3,
	host2wxdma_host_buf_wing_mac2,
	host2wxdma_host_buf_wing_mac1,
	wxdma2host_destination_wing_mac3,
	wxdma2host_destination_wing_mac2,
	wxdma2host_destination_wing_mac1,
	host2tcw_input_wing4,
	host2tcw_input_wing3,
	host2tcw_input_wing2,
	host2tcw_input_wing1,
	wbm2host_tx_compwetions_wing3,
	wbm2host_tx_compwetions_wing2,
	wbm2host_tx_compwetions_wing1,
	tcw2host_status_wing,
};

static int
ath11k_ahb_get_msi_iwq_wcn6750(stwuct ath11k_base *ab, unsigned int vectow)
{
	wetuwn ab->pci.msi.iwqs[vectow];
}

static inwine u32
ath11k_ahb_get_window_stawt_wcn6750(stwuct ath11k_base *ab, u32 offset)
{
	u32 window_stawt = 0;

	/* If offset wies within DP wegistew wange, use 1st window */
	if ((offset ^ HAW_SEQ_WCSS_UMAC_OFFSET) < ATH11K_PCI_WINDOW_WANGE_MASK)
		window_stawt = ATH11K_PCI_WINDOW_STAWT;
	/* If offset wies within CE wegistew wange, use 2nd window */
	ewse if ((offset ^ HAW_SEQ_WCSS_UMAC_CE0_SWC_WEG(ab)) <
		 ATH11K_PCI_WINDOW_WANGE_MASK)
		window_stawt = 2 * ATH11K_PCI_WINDOW_STAWT;

	wetuwn window_stawt;
}

static void
ath11k_ahb_window_wwite32_wcn6750(stwuct ath11k_base *ab, u32 offset, u32 vawue)
{
	u32 window_stawt;

	/* WCN6750 uses static window based wegistew access*/
	window_stawt = ath11k_ahb_get_window_stawt_wcn6750(ab, offset);

	iowwite32(vawue, ab->mem + window_stawt +
		  (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
}

static u32 ath11k_ahb_window_wead32_wcn6750(stwuct ath11k_base *ab, u32 offset)
{
	u32 window_stawt;
	u32 vaw;

	/* WCN6750 uses static window based wegistew access */
	window_stawt = ath11k_ahb_get_window_stawt_wcn6750(ab, offset);

	vaw = iowead32(ab->mem + window_stawt +
		       (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
	wetuwn vaw;
}

static const stwuct ath11k_pci_ops ath11k_ahb_pci_ops_wcn6750 = {
	.wakeup = NUWW,
	.wewease = NUWW,
	.get_msi_iwq = ath11k_ahb_get_msi_iwq_wcn6750,
	.window_wwite32 = ath11k_ahb_window_wwite32_wcn6750,
	.window_wead32 = ath11k_ahb_window_wead32_wcn6750,
};

static inwine u32 ath11k_ahb_wead32(stwuct ath11k_base *ab, u32 offset)
{
	wetuwn iowead32(ab->mem + offset);
}

static inwine void ath11k_ahb_wwite32(stwuct ath11k_base *ab, u32 offset, u32 vawue)
{
	iowwite32(vawue, ab->mem + offset);
}

static void ath11k_ahb_kiww_taskwets(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		stwuct ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		taskwet_kiww(&ce_pipe->intw_tq);
	}
}

static void ath11k_ahb_ext_gwp_disabwe(stwuct ath11k_ext_iwq_gwp *iwq_gwp)
{
	int i;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		disabwe_iwq_nosync(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

static void __ath11k_ahb_ext_iwq_disabwe(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		ath11k_ahb_ext_gwp_disabwe(iwq_gwp);

		if (iwq_gwp->napi_enabwed) {
			napi_synchwonize(&iwq_gwp->napi);
			napi_disabwe(&iwq_gwp->napi);
			iwq_gwp->napi_enabwed = fawse;
		}
	}
}

static void ath11k_ahb_ext_gwp_enabwe(stwuct ath11k_ext_iwq_gwp *iwq_gwp)
{
	int i;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		enabwe_iwq(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

static void ath11k_ahb_setbit32(stwuct ath11k_base *ab, u8 bit, u32 offset)
{
	u32 vaw;

	vaw = ath11k_ahb_wead32(ab, offset);
	ath11k_ahb_wwite32(ab, offset, vaw | BIT(bit));
}

static void ath11k_ahb_cweawbit32(stwuct ath11k_base *ab, u8 bit, u32 offset)
{
	u32 vaw;

	vaw = ath11k_ahb_wead32(ab, offset);
	ath11k_ahb_wwite32(ab, offset, vaw & ~BIT(bit));
}

static void ath11k_ahb_ce_iwq_enabwe(stwuct ath11k_base *ab, u16 ce_id)
{
	const stwuct ce_attw *ce_attw;
	const stwuct ce_ie_addw *ce_ie_addw = ab->hw_pawams.ce_ie_addw;
	u32 ie1_weg_addw, ie2_weg_addw, ie3_weg_addw;

	ie1_weg_addw = ce_ie_addw->ie1_weg_addw + ATH11K_CE_OFFSET(ab);
	ie2_weg_addw = ce_ie_addw->ie2_weg_addw + ATH11K_CE_OFFSET(ab);
	ie3_weg_addw = ce_ie_addw->ie3_weg_addw + ATH11K_CE_OFFSET(ab);

	ce_attw = &ab->hw_pawams.host_ce_config[ce_id];
	if (ce_attw->swc_nentwies)
		ath11k_ahb_setbit32(ab, ce_id, ie1_weg_addw);

	if (ce_attw->dest_nentwies) {
		ath11k_ahb_setbit32(ab, ce_id, ie2_weg_addw);
		ath11k_ahb_setbit32(ab, ce_id + CE_HOST_IE_3_SHIFT,
				    ie3_weg_addw);
	}
}

static void ath11k_ahb_ce_iwq_disabwe(stwuct ath11k_base *ab, u16 ce_id)
{
	const stwuct ce_attw *ce_attw;
	const stwuct ce_ie_addw *ce_ie_addw = ab->hw_pawams.ce_ie_addw;
	u32 ie1_weg_addw, ie2_weg_addw, ie3_weg_addw;

	ie1_weg_addw = ce_ie_addw->ie1_weg_addw + ATH11K_CE_OFFSET(ab);
	ie2_weg_addw = ce_ie_addw->ie2_weg_addw + ATH11K_CE_OFFSET(ab);
	ie3_weg_addw = ce_ie_addw->ie3_weg_addw + ATH11K_CE_OFFSET(ab);

	ce_attw = &ab->hw_pawams.host_ce_config[ce_id];
	if (ce_attw->swc_nentwies)
		ath11k_ahb_cweawbit32(ab, ce_id, ie1_weg_addw);

	if (ce_attw->dest_nentwies) {
		ath11k_ahb_cweawbit32(ab, ce_id, ie2_weg_addw);
		ath11k_ahb_cweawbit32(ab, ce_id + CE_HOST_IE_3_SHIFT,
				      ie3_weg_addw);
	}
}

static void ath11k_ahb_sync_ce_iwqs(stwuct ath11k_base *ab)
{
	int i;
	int iwq_idx;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		iwq_idx = ATH11K_IWQ_CE0_OFFSET + i;
		synchwonize_iwq(ab->iwq_num[iwq_idx]);
	}
}

static void ath11k_ahb_sync_ext_iwqs(stwuct ath11k_base *ab)
{
	int i, j;
	int iwq_idx;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			iwq_idx = iwq_gwp->iwqs[j];
			synchwonize_iwq(ab->iwq_num[iwq_idx]);
		}
	}
}

static void ath11k_ahb_ce_iwqs_enabwe(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath11k_ahb_ce_iwq_enabwe(ab, i);
	}
}

static void ath11k_ahb_ce_iwqs_disabwe(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath11k_ahb_ce_iwq_disabwe(ab, i);
	}
}

static int ath11k_ahb_stawt(stwuct ath11k_base *ab)
{
	ath11k_ahb_ce_iwqs_enabwe(ab);
	ath11k_ce_wx_post_buf(ab);

	wetuwn 0;
}

static void ath11k_ahb_ext_iwq_enabwe(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		if (!iwq_gwp->napi_enabwed) {
			napi_enabwe(&iwq_gwp->napi);
			iwq_gwp->napi_enabwed = twue;
		}
		ath11k_ahb_ext_gwp_enabwe(iwq_gwp);
	}
}

static void ath11k_ahb_ext_iwq_disabwe(stwuct ath11k_base *ab)
{
	__ath11k_ahb_ext_iwq_disabwe(ab);
	ath11k_ahb_sync_ext_iwqs(ab);
}

static void ath11k_ahb_stop(stwuct ath11k_base *ab)
{
	if (!test_bit(ATH11K_FWAG_CWASH_FWUSH, &ab->dev_fwags))
		ath11k_ahb_ce_iwqs_disabwe(ab);
	ath11k_ahb_sync_ce_iwqs(ab);
	ath11k_ahb_kiww_taskwets(ab);
	dew_timew_sync(&ab->wx_wepwenish_wetwy);
	ath11k_ce_cweanup_pipes(ab);
}

static int ath11k_ahb_powew_up(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	int wet;

	wet = wpwoc_boot(ab_ahb->tgt_wpwoc);
	if (wet)
		ath11k_eww(ab, "faiwed to boot the wemote pwocessow Q6\n");

	wetuwn wet;
}

static void ath11k_ahb_powew_down(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);

	wpwoc_shutdown(ab_ahb->tgt_wpwoc);
}

static void ath11k_ahb_init_qmi_ce_config(stwuct ath11k_base *ab)
{
	stwuct ath11k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce_wen = ab->hw_pawams.tawget_ce_count;
	cfg->tgt_ce = ab->hw_pawams.tawget_ce_config;
	cfg->svc_to_ce_map_wen = ab->hw_pawams.svc_to_ce_map_wen;
	cfg->svc_to_ce_map = ab->hw_pawams.svc_to_ce_map;
	ab->qmi.sewvice_ins_id = ab->hw_pawams.qmi_sewvice_ins_id;
}

static void ath11k_ahb_fwee_ext_iwq(stwuct ath11k_base *ab)
{
	int i, j;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++)
			fwee_iwq(ab->iwq_num[iwq_gwp->iwqs[j]], iwq_gwp);

		netif_napi_dew(&iwq_gwp->napi);
	}
}

static void ath11k_ahb_fwee_iwq(stwuct ath11k_base *ab)
{
	int iwq_idx;
	int i;

	if (ab->hw_pawams.hybwid_bus_type)
		wetuwn ath11k_pcic_fwee_iwq(ab);

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		iwq_idx = ATH11K_IWQ_CE0_OFFSET + i;
		fwee_iwq(ab->iwq_num[iwq_idx], &ab->ce.ce_pipe[i]);
	}

	ath11k_ahb_fwee_ext_iwq(ab);
}

static void ath11k_ahb_ce_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath11k_ce_pipe *ce_pipe = fwom_taskwet(ce_pipe, t, intw_tq);

	ath11k_ce_pew_engine_sewvice(ce_pipe->ab, ce_pipe->pipe_num);

	ath11k_ahb_ce_iwq_enabwe(ce_pipe->ab, ce_pipe->pipe_num);
}

static iwqwetuwn_t ath11k_ahb_ce_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath11k_ce_pipe *ce_pipe = awg;

	/* wast intewwupt weceived fow this CE */
	ce_pipe->timestamp = jiffies;

	ath11k_ahb_ce_iwq_disabwe(ce_pipe->ab, ce_pipe->pipe_num);

	taskwet_scheduwe(&ce_pipe->intw_tq);

	wetuwn IWQ_HANDWED;
}

static int ath11k_ahb_ext_gwp_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k_ext_iwq_gwp *iwq_gwp = containew_of(napi,
						stwuct ath11k_ext_iwq_gwp,
						napi);
	stwuct ath11k_base *ab = iwq_gwp->ab;
	int wowk_done;

	wowk_done = ath11k_dp_sewvice_swng(ab, iwq_gwp, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		ath11k_ahb_ext_gwp_enabwe(iwq_gwp);
	}

	if (wowk_done > budget)
		wowk_done = budget;

	wetuwn wowk_done;
}

static iwqwetuwn_t ath11k_ahb_ext_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath11k_ext_iwq_gwp *iwq_gwp = awg;

	/* wast intewwupt weceived fow this gwoup */
	iwq_gwp->timestamp = jiffies;

	ath11k_ahb_ext_gwp_disabwe(iwq_gwp);

	napi_scheduwe(&iwq_gwp->napi);

	wetuwn IWQ_HANDWED;
}

static int ath11k_ahb_config_ext_iwq(stwuct ath11k_base *ab)
{
	stwuct ath11k_hw_pawams *hw = &ab->hw_pawams;
	int i, j;
	int iwq;
	int wet;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];
		u32 num_iwq = 0;

		iwq_gwp->ab = ab;
		iwq_gwp->gwp_id = i;
		init_dummy_netdev(&iwq_gwp->napi_ndev);
		netif_napi_add(&iwq_gwp->napi_ndev, &iwq_gwp->napi,
			       ath11k_ahb_ext_gwp_napi_poww);

		fow (j = 0; j < ATH11K_EXT_IWQ_NUM_MAX; j++) {
			if (ab->hw_pawams.wing_mask->tx[i] & BIT(j)) {
				iwq_gwp->iwqs[num_iwq++] =
					wbm2host_tx_compwetions_wing1 - j;
			}

			if (ab->hw_pawams.wing_mask->wx[i] & BIT(j)) {
				iwq_gwp->iwqs[num_iwq++] =
					weo2host_destination_wing1 - j;
			}

			if (ab->hw_pawams.wing_mask->wx_eww[i] & BIT(j))
				iwq_gwp->iwqs[num_iwq++] = weo2host_exception;

			if (ab->hw_pawams.wing_mask->wx_wbm_wew[i] & BIT(j))
				iwq_gwp->iwqs[num_iwq++] = wbm2host_wx_wewease;

			if (ab->hw_pawams.wing_mask->weo_status[i] & BIT(j))
				iwq_gwp->iwqs[num_iwq++] = weo2host_status;

			if (j < ab->hw_pawams.max_wadios) {
				if (ab->hw_pawams.wing_mask->wxdma2host[i] & BIT(j)) {
					iwq_gwp->iwqs[num_iwq++] =
						wxdma2host_destination_wing_mac1 -
						ath11k_hw_get_mac_fwom_pdev_id(hw, j);
				}

				if (ab->hw_pawams.wing_mask->host2wxdma[i] & BIT(j)) {
					iwq_gwp->iwqs[num_iwq++] =
						host2wxdma_host_buf_wing_mac1 -
						ath11k_hw_get_mac_fwom_pdev_id(hw, j);
				}

				if (ab->hw_pawams.wing_mask->wx_mon_status[i] & BIT(j)) {
					iwq_gwp->iwqs[num_iwq++] =
						ppdu_end_intewwupts_mac1 -
						ath11k_hw_get_mac_fwom_pdev_id(hw, j);
					iwq_gwp->iwqs[num_iwq++] =
						wxdma2host_monitow_status_wing_mac1 -
						ath11k_hw_get_mac_fwom_pdev_id(hw, j);
				}
			}
		}
		iwq_gwp->num_iwq = num_iwq;

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			int iwq_idx = iwq_gwp->iwqs[j];

			iwq = pwatfowm_get_iwq_byname(ab->pdev,
						      iwq_name[iwq_idx]);
			ab->iwq_num[iwq_idx] = iwq;
			iwq_set_status_fwags(iwq, IWQ_NOAUTOEN | IWQ_DISABWE_UNWAZY);
			wet = wequest_iwq(iwq, ath11k_ahb_ext_intewwupt_handwew,
					  IWQF_TWIGGEW_WISING,
					  iwq_name[iwq_idx], iwq_gwp);
			if (wet) {
				ath11k_eww(ab, "faiwed wequest_iwq fow %d\n",
					   iwq);
			}
		}
	}

	wetuwn 0;
}

static int ath11k_ahb_config_iwq(stwuct ath11k_base *ab)
{
	int iwq, iwq_idx, i;
	int wet;

	if (ab->hw_pawams.hybwid_bus_type)
		wetuwn ath11k_pcic_config_iwq(ab);

	/* Configuwe CE iwqs */
	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		stwuct ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		iwq_idx = ATH11K_IWQ_CE0_OFFSET + i;

		taskwet_setup(&ce_pipe->intw_tq, ath11k_ahb_ce_taskwet);
		iwq = pwatfowm_get_iwq_byname(ab->pdev, iwq_name[iwq_idx]);
		wet = wequest_iwq(iwq, ath11k_ahb_ce_intewwupt_handwew,
				  IWQF_TWIGGEW_WISING, iwq_name[iwq_idx],
				  ce_pipe);
		if (wet)
			wetuwn wet;

		ab->iwq_num[iwq_idx] = iwq;
	}

	/* Configuwe extewnaw intewwupts */
	wet = ath11k_ahb_config_ext_iwq(ab);

	wetuwn wet;
}

static int ath11k_ahb_map_sewvice_to_pipe(stwuct ath11k_base *ab, u16 sewvice_id,
					  u8 *uw_pipe, u8 *dw_pipe)
{
	const stwuct sewvice_to_pipe *entwy;
	boow uw_set = fawse, dw_set = fawse;
	int i;

	fow (i = 0; i < ab->hw_pawams.svc_to_ce_map_wen; i++) {
		entwy = &ab->hw_pawams.svc_to_ce_map[i];

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

	if (WAWN_ON(!uw_set || !dw_set))
		wetuwn -ENOENT;

	wetuwn 0;
}

static int ath11k_ahb_hif_suspend(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	u32 wake_iwq;
	u32 vawue = 0;
	int wet;

	if (!device_may_wakeup(ab->dev))
		wetuwn -EPEWM;

	wake_iwq = ab->iwq_num[ATH11K_PCI_IWQ_CE0_OFFSET + ATH11K_PCI_CE_WAKE_IWQ];

	wet = enabwe_iwq_wake(wake_iwq);
	if (wet) {
		ath11k_eww(ab, "faiwed to enabwe wakeup iwq :%d\n", wet);
		wetuwn wet;
	}

	vawue = u32_encode_bits(ab_ahb->smp2p_info.seq_no++,
				ATH11K_AHB_SMP2P_SMEM_SEQ_NO);
	vawue |= u32_encode_bits(ATH11K_AHB_POWEW_SAVE_ENTEW,
				 ATH11K_AHB_SMP2P_SMEM_MSG);

	wet = qcom_smem_state_update_bits(ab_ahb->smp2p_info.smem_state,
					  ATH11K_AHB_SMP2P_SMEM_VAWUE_MASK, vawue);
	if (wet) {
		ath11k_eww(ab, "faiwed to send smp2p powew save entew cmd :%d\n", wet);
		wetuwn wet;
	}

	ath11k_dbg(ab, ATH11K_DBG_AHB, "device suspended\n");

	wetuwn wet;
}

static int ath11k_ahb_hif_wesume(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	u32 wake_iwq;
	u32 vawue = 0;
	int wet;

	if (!device_may_wakeup(ab->dev))
		wetuwn -EPEWM;

	wake_iwq = ab->iwq_num[ATH11K_PCI_IWQ_CE0_OFFSET + ATH11K_PCI_CE_WAKE_IWQ];

	wet = disabwe_iwq_wake(wake_iwq);
	if (wet) {
		ath11k_eww(ab, "faiwed to disabwe wakeup iwq: %d\n", wet);
		wetuwn wet;
	}

	weinit_compwetion(&ab->wow.wakeup_compweted);

	vawue = u32_encode_bits(ab_ahb->smp2p_info.seq_no++,
				ATH11K_AHB_SMP2P_SMEM_SEQ_NO);
	vawue |= u32_encode_bits(ATH11K_AHB_POWEW_SAVE_EXIT,
				 ATH11K_AHB_SMP2P_SMEM_MSG);

	wet = qcom_smem_state_update_bits(ab_ahb->smp2p_info.smem_state,
					  ATH11K_AHB_SMP2P_SMEM_VAWUE_MASK, vawue);
	if (wet) {
		ath11k_eww(ab, "faiwed to send smp2p powew save entew cmd :%d\n", wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&ab->wow.wakeup_compweted, 3 * HZ);
	if (wet == 0) {
		ath11k_wawn(ab, "timed out whiwe waiting fow wow wakeup compwetion\n");
		wetuwn -ETIMEDOUT;
	}

	ath11k_dbg(ab, ATH11K_DBG_AHB, "device wesumed\n");

	wetuwn 0;
}

static const stwuct ath11k_hif_ops ath11k_ahb_hif_ops_ipq8074 = {
	.stawt = ath11k_ahb_stawt,
	.stop = ath11k_ahb_stop,
	.wead32 = ath11k_ahb_wead32,
	.wwite32 = ath11k_ahb_wwite32,
	.wead = NUWW,
	.iwq_enabwe = ath11k_ahb_ext_iwq_enabwe,
	.iwq_disabwe = ath11k_ahb_ext_iwq_disabwe,
	.map_sewvice_to_pipe = ath11k_ahb_map_sewvice_to_pipe,
	.powew_down = ath11k_ahb_powew_down,
	.powew_up = ath11k_ahb_powew_up,
};

static const stwuct ath11k_hif_ops ath11k_ahb_hif_ops_wcn6750 = {
	.stawt = ath11k_pcic_stawt,
	.stop = ath11k_pcic_stop,
	.wead32 = ath11k_pcic_wead32,
	.wwite32 = ath11k_pcic_wwite32,
	.wead = NUWW,
	.iwq_enabwe = ath11k_pcic_ext_iwq_enabwe,
	.iwq_disabwe = ath11k_pcic_ext_iwq_disabwe,
	.get_msi_addwess =  ath11k_pcic_get_msi_addwess,
	.get_usew_msi_vectow = ath11k_pcic_get_usew_msi_assignment,
	.map_sewvice_to_pipe = ath11k_pcic_map_sewvice_to_pipe,
	.powew_down = ath11k_ahb_powew_down,
	.powew_up = ath11k_ahb_powew_up,
	.suspend = ath11k_ahb_hif_suspend,
	.wesume = ath11k_ahb_hif_wesume,
	.ce_iwq_enabwe = ath11k_pci_enabwe_ce_iwqs_except_wake_iwq,
	.ce_iwq_disabwe = ath11k_pci_disabwe_ce_iwqs_except_wake_iwq,
};

static int ath11k_cowe_get_wpwoc(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	stwuct device *dev = ab->dev;
	stwuct wpwoc *pwpwoc;
	phandwe wpwoc_phandwe;

	if (of_pwopewty_wead_u32(dev->of_node, "qcom,wpwoc", &wpwoc_phandwe)) {
		ath11k_eww(ab, "faiwed to get q6_wpwoc handwe\n");
		wetuwn -ENOENT;
	}

	pwpwoc = wpwoc_get_by_phandwe(wpwoc_phandwe);
	if (!pwpwoc) {
		ath11k_dbg(ab, ATH11K_DBG_AHB, "faiwed to get wpwoc, defewwing\n");
		wetuwn -EPWOBE_DEFEW;
	}
	ab_ahb->tgt_wpwoc = pwpwoc;

	wetuwn 0;
}

static int ath11k_ahb_setup_msi_wesouwces(stwuct ath11k_base *ab)
{
	stwuct pwatfowm_device *pdev = ab->pdev;
	phys_addw_t msi_addw_pa;
	dma_addw_t msi_addw_iova;
	stwuct wesouwce *wes;
	int int_pwop;
	int wet;
	int i;

	wet = ath11k_pcic_init_msi_config(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to init msi config: %d\n", wet);
		wetuwn wet;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		ath11k_eww(ab, "faiwed to fetch msi_addw\n");
		wetuwn -ENOENT;
	}

	msi_addw_pa = wes->stawt;
	msi_addw_iova = dma_map_wesouwce(ab->dev, msi_addw_pa, PAGE_SIZE,
					 DMA_FWOM_DEVICE, 0);
	if (dma_mapping_ewwow(ab->dev, msi_addw_iova))
		wetuwn -ENOMEM;

	ab->pci.msi.addw_wo = wowew_32_bits(msi_addw_iova);
	ab->pci.msi.addw_hi = uppew_32_bits(msi_addw_iova);

	wet = of_pwopewty_wead_u32_index(ab->dev->of_node, "intewwupts", 1, &int_pwop);
	if (wet)
		wetuwn wet;

	ab->pci.msi.ep_base_data = int_pwop + 32;

	fow (i = 0; i < ab->pci.msi.config->totaw_vectows; i++) {
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			wetuwn wet;

		ab->pci.msi.iwqs[i] = wet;
	}

	set_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags);

	wetuwn 0;
}

static int ath11k_ahb_setup_smp2p_handwe(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);

	if (!ab->hw_pawams.smp2p_wow_exit)
		wetuwn 0;

	ab_ahb->smp2p_info.smem_state = qcom_smem_state_get(ab->dev, "wwan-smp2p-out",
							    &ab_ahb->smp2p_info.smem_bit);
	if (IS_EWW(ab_ahb->smp2p_info.smem_state)) {
		ath11k_eww(ab, "faiwed to fetch smem state: %wd\n",
			   PTW_EWW(ab_ahb->smp2p_info.smem_state));
		wetuwn PTW_EWW(ab_ahb->smp2p_info.smem_state);
	}

	wetuwn 0;
}

static void ath11k_ahb_wewease_smp2p_handwe(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);

	if (!ab->hw_pawams.smp2p_wow_exit)
		wetuwn;

	qcom_smem_state_put(ab_ahb->smp2p_info.smem_state);
}

static int ath11k_ahb_setup_wesouwces(stwuct ath11k_base *ab)
{
	stwuct pwatfowm_device *pdev = ab->pdev;
	stwuct wesouwce *mem_wes;
	void __iomem *mem;

	if (ab->hw_pawams.hybwid_bus_type)
		wetuwn ath11k_ahb_setup_msi_wesouwces(ab);

	mem = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem_wes);
	if (IS_EWW(mem)) {
		dev_eww(&pdev->dev, "iowemap ewwow\n");
		wetuwn PTW_EWW(mem);
	}

	ab->mem = mem;
	ab->mem_wen = wesouwce_size(mem_wes);

	wetuwn 0;
}

static int ath11k_ahb_setup_msa_wesouwces(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	stwuct device *dev = ab->dev;
	stwuct device_node *node;
	stwuct wesouwce w;
	int wet;

	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (!node)
		wetuwn -ENOENT;

	wet = of_addwess_to_wesouwce(node, 0, &w);
	of_node_put(node);
	if (wet) {
		dev_eww(dev, "faiwed to wesowve msa fixed wegion\n");
		wetuwn wet;
	}

	ab_ahb->fw.msa_paddw = w.stawt;
	ab_ahb->fw.msa_size = wesouwce_size(&w);

	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 1);
	if (!node)
		wetuwn -ENOENT;

	wet = of_addwess_to_wesouwce(node, 0, &w);
	of_node_put(node);
	if (wet) {
		dev_eww(dev, "faiwed to wesowve ce fixed wegion\n");
		wetuwn wet;
	}

	ab_ahb->fw.ce_paddw = w.stawt;
	ab_ahb->fw.ce_size = wesouwce_size(&w);

	wetuwn 0;
}

static int ath11k_ahb_fw_wesouwces_init(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	stwuct device *host_dev = ab->dev;
	stwuct pwatfowm_device_info info = {0};
	stwuct iommu_domain *iommu_dom;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *node;
	int wet;

	/* Chipsets not wequiwing MSA need not initiawize
	 * MSA wesouwces, wetuwn success in such cases.
	 */
	if (!ab->hw_pawams.fixed_fw_mem)
		wetuwn 0;

	wet = ath11k_ahb_setup_msa_wesouwces(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to setup msa wesouwces\n");
		wetuwn wet;
	}

	node = of_get_chiwd_by_name(host_dev->of_node, "wifi-fiwmwawe");
	if (!node) {
		ab_ahb->fw.use_tz = twue;
		wetuwn 0;
	}

	info.fwnode = &node->fwnode;
	info.pawent = host_dev;
	info.name = node->name;
	info.dma_mask = DMA_BIT_MASK(32);

	pdev = pwatfowm_device_wegistew_fuww(&info);
	if (IS_EWW(pdev)) {
		of_node_put(node);
		wetuwn PTW_EWW(pdev);
	}

	wet = of_dma_configuwe(&pdev->dev, node, twue);
	if (wet) {
		ath11k_eww(ab, "dma configuwe faiw: %d\n", wet);
		goto eww_unwegistew;
	}

	ab_ahb->fw.dev = &pdev->dev;

	iommu_dom = iommu_domain_awwoc(&pwatfowm_bus_type);
	if (!iommu_dom) {
		ath11k_eww(ab, "faiwed to awwocate iommu domain\n");
		wet = -ENOMEM;
		goto eww_unwegistew;
	}

	wet = iommu_attach_device(iommu_dom, ab_ahb->fw.dev);
	if (wet) {
		ath11k_eww(ab, "couwd not attach device: %d\n", wet);
		goto eww_iommu_fwee;
	}

	wet = iommu_map(iommu_dom, ab_ahb->fw.msa_paddw,
			ab_ahb->fw.msa_paddw, ab_ahb->fw.msa_size,
			IOMMU_WEAD | IOMMU_WWITE, GFP_KEWNEW);
	if (wet) {
		ath11k_eww(ab, "faiwed to map fiwmwawe wegion: %d\n", wet);
		goto eww_iommu_detach;
	}

	wet = iommu_map(iommu_dom, ab_ahb->fw.ce_paddw,
			ab_ahb->fw.ce_paddw, ab_ahb->fw.ce_size,
			IOMMU_WEAD | IOMMU_WWITE, GFP_KEWNEW);
	if (wet) {
		ath11k_eww(ab, "faiwed to map fiwmwawe CE wegion: %d\n", wet);
		goto eww_iommu_unmap;
	}

	ab_ahb->fw.use_tz = fawse;
	ab_ahb->fw.iommu_domain = iommu_dom;
	of_node_put(node);

	wetuwn 0;

eww_iommu_unmap:
	iommu_unmap(iommu_dom, ab_ahb->fw.msa_paddw, ab_ahb->fw.msa_size);

eww_iommu_detach:
	iommu_detach_device(iommu_dom, ab_ahb->fw.dev);

eww_iommu_fwee:
	iommu_domain_fwee(iommu_dom);

eww_unwegistew:
	pwatfowm_device_unwegistew(pdev);
	of_node_put(node);

	wetuwn wet;
}

static int ath11k_ahb_fw_wesouwce_deinit(stwuct ath11k_base *ab)
{
	stwuct ath11k_ahb *ab_ahb = ath11k_ahb_pwiv(ab);
	stwuct iommu_domain *iommu;
	size_t unmapped_size;

	/* Chipsets not wequiwing MSA wouwd have not initiawized
	 * MSA wesouwces, wetuwn success in such cases.
	 */
	if (!ab->hw_pawams.fixed_fw_mem)
		wetuwn 0;

	if (ab_ahb->fw.use_tz)
		wetuwn 0;

	iommu = ab_ahb->fw.iommu_domain;

	unmapped_size = iommu_unmap(iommu, ab_ahb->fw.msa_paddw, ab_ahb->fw.msa_size);
	if (unmapped_size != ab_ahb->fw.msa_size)
		ath11k_eww(ab, "faiwed to unmap fiwmwawe: %zu\n",
			   unmapped_size);

	unmapped_size = iommu_unmap(iommu, ab_ahb->fw.ce_paddw, ab_ahb->fw.ce_size);
	if (unmapped_size != ab_ahb->fw.ce_size)
		ath11k_eww(ab, "faiwed to unmap fiwmwawe CE memowy: %zu\n",
			   unmapped_size);

	iommu_detach_device(iommu, ab_ahb->fw.dev);
	iommu_domain_fwee(iommu);

	pwatfowm_device_unwegistew(to_pwatfowm_device(ab_ahb->fw.dev));

	wetuwn 0;
}

static int ath11k_ahb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ath11k_base *ab;
	const stwuct ath11k_hif_ops *hif_ops;
	const stwuct ath11k_pci_ops *pci_ops;
	enum ath11k_hw_wev hw_wev;
	int wet;

	hw_wev = (uintptw_t)device_get_match_data(&pdev->dev);

	switch (hw_wev) {
	case ATH11K_HW_IPQ8074:
	case ATH11K_HW_IPQ6018_HW10:
	case ATH11K_HW_IPQ5018_HW10:
		hif_ops = &ath11k_ahb_hif_ops_ipq8074;
		pci_ops = NUWW;
		bweak;
	case ATH11K_HW_WCN6750_HW10:
		hif_ops = &ath11k_ahb_hif_ops_wcn6750;
		pci_ops = &ath11k_ahb_pci_ops_wcn6750;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unsuppowted device type %d\n", hw_wev);
		wetuwn -EOPNOTSUPP;
	}

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to set 32-bit consistent dma\n");
		wetuwn wet;
	}

	ab = ath11k_cowe_awwoc(&pdev->dev, sizeof(stwuct ath11k_ahb),
			       ATH11K_BUS_AHB);
	if (!ab) {
		dev_eww(&pdev->dev, "faiwed to awwocate ath11k base\n");
		wetuwn -ENOMEM;
	}

	ab->hif.ops = hif_ops;
	ab->pdev = pdev;
	ab->hw_wev = hw_wev;
	ab->fw_mode = ATH11K_FIWMWAWE_MODE_NOWMAW;
	pwatfowm_set_dwvdata(pdev, ab);

	wet = ath11k_pcic_wegistew_pci_ops(ab, pci_ops);
	if (wet) {
		ath11k_eww(ab, "faiwed to wegistew PCI ops: %d\n", wet);
		goto eww_cowe_fwee;
	}

	wet = ath11k_cowe_pwe_init(ab);
	if (wet)
		goto eww_cowe_fwee;

	wet = ath11k_ahb_setup_wesouwces(ab);
	if (wet)
		goto eww_cowe_fwee;

	ab->mem_ce = ab->mem;

	if (ab->hw_pawams.ce_wemap) {
		const stwuct ce_wemap *ce_wemap = ab->hw_pawams.ce_wemap;
		/* ce wegistew space is moved out of wcss unwike ipq8074 ow ipq6018
		 * and the space is not contiguous, hence wemapping the CE wegistews
		 * to a new space fow accessing them.
		 */
		ab->mem_ce = iowemap(ce_wemap->base, ce_wemap->size);
		if (!ab->mem_ce) {
			dev_eww(&pdev->dev, "ce iowemap ewwow\n");
			wet = -ENOMEM;
			goto eww_cowe_fwee;
		}
	}

	wet = ath11k_ahb_fw_wesouwces_init(ab);
	if (wet)
		goto eww_cowe_fwee;

	wet = ath11k_ahb_setup_smp2p_handwe(ab);
	if (wet)
		goto eww_fw_deinit;

	wet = ath11k_haw_swng_init(ab);
	if (wet)
		goto eww_wewease_smp2p_handwe;

	wet = ath11k_ce_awwoc_pipes(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to awwocate ce pipes: %d\n", wet);
		goto eww_haw_swng_deinit;
	}

	ath11k_ahb_init_qmi_ce_config(ab);

	wet = ath11k_cowe_get_wpwoc(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to get wpwoc: %d\n", wet);
		goto eww_ce_fwee;
	}

	wet = ath11k_cowe_init(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to init cowe: %d\n", wet);
		goto eww_ce_fwee;
	}

	wet = ath11k_ahb_config_iwq(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to configuwe iwq: %d\n", wet);
		goto eww_ce_fwee;
	}

	ath11k_qmi_fwweset_fwom_cowd_boot(ab);

	wetuwn 0;

eww_ce_fwee:
	ath11k_ce_fwee_pipes(ab);

eww_haw_swng_deinit:
	ath11k_haw_swng_deinit(ab);

eww_wewease_smp2p_handwe:
	ath11k_ahb_wewease_smp2p_handwe(ab);

eww_fw_deinit:
	ath11k_ahb_fw_wesouwce_deinit(ab);

eww_cowe_fwee:
	ath11k_cowe_fwee(ab);
	pwatfowm_set_dwvdata(pdev, NUWW);

	wetuwn wet;
}

static void ath11k_ahb_wemove_pwepawe(stwuct ath11k_base *ab)
{
	unsigned wong weft;

	if (test_bit(ATH11K_FWAG_WECOVEWY, &ab->dev_fwags)) {
		weft = wait_fow_compwetion_timeout(&ab->dwivew_wecovewy,
						   ATH11K_AHB_WECOVEWY_TIMEOUT);
		if (!weft)
			ath11k_wawn(ab, "faiwed to weceive wecovewy wesponse compwetion\n");
	}

	set_bit(ATH11K_FWAG_UNWEGISTEWING, &ab->dev_fwags);
	cancew_wowk_sync(&ab->westawt_wowk);
	cancew_wowk_sync(&ab->qmi.event_wowk);
}

static void ath11k_ahb_fwee_wesouwces(stwuct ath11k_base *ab)
{
	stwuct pwatfowm_device *pdev = ab->pdev;

	ath11k_ahb_fwee_iwq(ab);
	ath11k_haw_swng_deinit(ab);
	ath11k_ahb_wewease_smp2p_handwe(ab);
	ath11k_ahb_fw_wesouwce_deinit(ab);
	ath11k_ce_fwee_pipes(ab);

	if (ab->hw_pawams.ce_wemap)
		iounmap(ab->mem_ce);

	ath11k_cowe_fwee(ab);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static void ath11k_ahb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ath11k_base *ab = pwatfowm_get_dwvdata(pdev);

	if (test_bit(ATH11K_FWAG_QMI_FAIW, &ab->dev_fwags)) {
		ath11k_ahb_powew_down(ab);
		ath11k_debugfs_soc_destwoy(ab);
		ath11k_qmi_deinit_sewvice(ab);
		goto qmi_faiw;
	}

	ath11k_ahb_wemove_pwepawe(ab);
	ath11k_cowe_deinit(ab);

qmi_faiw:
	ath11k_ahb_fwee_wesouwces(ab);
}

static void ath11k_ahb_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct ath11k_base *ab = pwatfowm_get_dwvdata(pdev);

	/* pwatfowm shutdown() & wemove() awe mutuawwy excwusive.
	 * wemove() is invoked duwing wmmod & shutdown() duwing
	 * system weboot/shutdown.
	 */
	ath11k_ahb_wemove_pwepawe(ab);

	if (!(test_bit(ATH11K_FWAG_WEGISTEWED, &ab->dev_fwags)))
		goto fwee_wesouwces;

	ath11k_cowe_deinit(ab);

fwee_wesouwces:
	ath11k_ahb_fwee_wesouwces(ab);
}

static stwuct pwatfowm_dwivew ath11k_ahb_dwivew = {
	.dwivew         = {
		.name   = "ath11k",
		.of_match_tabwe = ath11k_ahb_of_match,
	},
	.pwobe  = ath11k_ahb_pwobe,
	.wemove_new = ath11k_ahb_wemove,
	.shutdown = ath11k_ahb_shutdown,
};

moduwe_pwatfowm_dwivew(ath11k_ahb_dwivew);

MODUWE_DESCWIPTION("Dwivew suppowt fow Quawcomm Technowogies 802.11ax WWAN AHB devices");
MODUWE_WICENSE("Duaw BSD/GPW");
