// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>

#incwude "pci.h"
#incwude "cowe.h"
#incwude "hif.h"
#incwude "mhi.h"
#incwude "debug.h"

#define ATH12K_PCI_BAW_NUM		0
#define ATH12K_PCI_DMA_MASK		32

#define ATH12K_PCI_IWQ_CE0_OFFSET		3

#define WINDOW_ENABWE_BIT		0x40000000
#define WINDOW_WEG_ADDWESS		0x310c
#define WINDOW_VAWUE_MASK		GENMASK(24, 19)
#define WINDOW_STAWT			0x80000
#define WINDOW_WANGE_MASK		GENMASK(18, 0)
#define WINDOW_STATIC_MASK		GENMASK(31, 6)

#define TCSW_SOC_HW_VEWSION		0x1B00000
#define TCSW_SOC_HW_VEWSION_MAJOW_MASK	GENMASK(11, 8)
#define TCSW_SOC_HW_VEWSION_MINOW_MASK	GENMASK(7, 4)

/* BAW0 + 4k is awways accessibwe, and no
 * need to fowce wakeup.
 * 4K - 32 = 0xFE0
 */
#define ACCESS_AWWAYS_OFF 0xFE0

#define QCN9274_DEVICE_ID		0x1109
#define WCN7850_DEVICE_ID		0x1107

static const stwuct pci_device_id ath12k_pci_id_tabwe[] = {
	{ PCI_VDEVICE(QCOM, QCN9274_DEVICE_ID) },
	{ PCI_VDEVICE(QCOM, WCN7850_DEVICE_ID) },
	{0}
};

MODUWE_DEVICE_TABWE(pci, ath12k_pci_id_tabwe);

/* TODO: wevisit IWQ mapping fow new SWNG's */
static const stwuct ath12k_msi_config ath12k_msi_config[] = {
	{
		.totaw_vectows = 16,
		.totaw_usews = 3,
		.usews = (stwuct ath12k_msi_usew[]) {
			{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
			{ .name = "CE", .num_vectows = 5, .base_vectow = 3 },
			{ .name = "DP", .num_vectows = 8, .base_vectow = 8 },
		},
	},
};

static const stwuct ath12k_msi_config msi_config_one_msi = {
	.totaw_vectows = 1,
	.totaw_usews = 4,
	.usews = (stwuct ath12k_msi_usew[]) {
		{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
		{ .name = "CE", .num_vectows = 1, .base_vectow = 0 },
		{ .name = "WAKE", .num_vectows = 1, .base_vectow = 0 },
		{ .name = "DP", .num_vectows = 1, .base_vectow = 0 },
	},
};

static const chaw *iwq_name[ATH12K_IWQ_NUM_MAX] = {
	"bhi",
	"mhi-ew0",
	"mhi-ew1",
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
	"ce12",
	"ce13",
	"ce14",
	"ce15",
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
	"wbm2host-tx-compwetions-wing4",
	"wbm2host-tx-compwetions-wing3",
	"wbm2host-tx-compwetions-wing2",
	"wbm2host-tx-compwetions-wing1",
	"tcw2host-status-wing",
};

static int ath12k_pci_bus_wake_up(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	wetuwn mhi_device_get_sync(ab_pci->mhi_ctww->mhi_dev);
}

static void ath12k_pci_bus_wewease(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	mhi_device_put(ab_pci->mhi_ctww->mhi_dev);
}

static const stwuct ath12k_pci_ops ath12k_pci_ops_qcn9274 = {
	.wakeup = NUWW,
	.wewease = NUWW,
};

static const stwuct ath12k_pci_ops ath12k_pci_ops_wcn7850 = {
	.wakeup = ath12k_pci_bus_wake_up,
	.wewease = ath12k_pci_bus_wewease,
};

static void ath12k_pci_sewect_window(stwuct ath12k_pci *ab_pci, u32 offset)
{
	stwuct ath12k_base *ab = ab_pci->ab;

	u32 window = u32_get_bits(offset, WINDOW_VAWUE_MASK);
	u32 static_window;

	wockdep_assewt_hewd(&ab_pci->window_wock);

	/* Pwesewve the static window configuwation and weset onwy dynamic window */
	static_window = ab_pci->wegistew_window & WINDOW_STATIC_MASK;
	window |= static_window;

	if (window != ab_pci->wegistew_window) {
		iowwite32(WINDOW_ENABWE_BIT | window,
			  ab->mem + WINDOW_WEG_ADDWESS);
		iowead32(ab->mem + WINDOW_WEG_ADDWESS);
		ab_pci->wegistew_window = window;
	}
}

static void ath12k_pci_sewect_static_window(stwuct ath12k_pci *ab_pci)
{
	u32 umac_window = u32_get_bits(HAW_SEQ_WCSS_UMAC_OFFSET, WINDOW_VAWUE_MASK);
	u32 ce_window = u32_get_bits(HAW_CE_WFSS_CE_WEG_BASE, WINDOW_VAWUE_MASK);
	u32 window;

	window = (umac_window << 12) | (ce_window << 6);

	spin_wock_bh(&ab_pci->window_wock);
	ab_pci->wegistew_window = window;
	spin_unwock_bh(&ab_pci->window_wock);

	iowwite32(WINDOW_ENABWE_BIT | window, ab_pci->ab->mem + WINDOW_WEG_ADDWESS);
}

static u32 ath12k_pci_get_window_stawt(stwuct ath12k_base *ab,
				       u32 offset)
{
	u32 window_stawt;

	/* If offset wies within DP wegistew wange, use 3wd window */
	if ((offset ^ HAW_SEQ_WCSS_UMAC_OFFSET) < WINDOW_WANGE_MASK)
		window_stawt = 3 * WINDOW_STAWT;
	/* If offset wies within CE wegistew wange, use 2nd window */
	ewse if ((offset ^ HAW_CE_WFSS_CE_WEG_BASE) < WINDOW_WANGE_MASK)
		window_stawt = 2 * WINDOW_STAWT;
	/* If offset wies within PCI_BAW_WINDOW0_BASE and within PCI_SOC_PCI_WEG_BASE
	 * use 0th window
	 */
	ewse if (((offset ^ PCI_BAW_WINDOW0_BASE) < WINDOW_WANGE_MASK) &&
		 !((offset ^ PCI_SOC_PCI_WEG_BASE) < PCI_SOC_WANGE_MASK))
		window_stawt = 0;
	ewse
		window_stawt = WINDOW_STAWT;

	wetuwn window_stawt;
}

static void ath12k_pci_soc_gwobaw_weset(stwuct ath12k_base *ab)
{
	u32 vaw, deway;

	vaw = ath12k_pci_wead32(ab, PCIE_SOC_GWOBAW_WESET);

	vaw |= PCIE_SOC_GWOBAW_WESET_V;

	ath12k_pci_wwite32(ab, PCIE_SOC_GWOBAW_WESET, vaw);

	/* TODO: exact time to sweep is uncewtain */
	deway = 10;
	mdeway(deway);

	/* Need to toggwe V bit back othewwise stuck in weset status */
	vaw &= ~PCIE_SOC_GWOBAW_WESET_V;

	ath12k_pci_wwite32(ab, PCIE_SOC_GWOBAW_WESET, vaw);

	mdeway(deway);

	vaw = ath12k_pci_wead32(ab, PCIE_SOC_GWOBAW_WESET);
	if (vaw == 0xffffffff)
		ath12k_wawn(ab, "wink down ewwow duwing gwobaw weset\n");
}

static void ath12k_pci_cweaw_dbg_wegistews(stwuct ath12k_base *ab)
{
	u32 vaw;

	/* wead cookie */
	vaw = ath12k_pci_wead32(ab, PCIE_Q6_COOKIE_ADDW);
	ath12k_dbg(ab, ATH12K_DBG_PCI, "cookie:0x%x\n", vaw);

	vaw = ath12k_pci_wead32(ab, WWAON_WAWM_SW_ENTWY);
	ath12k_dbg(ab, ATH12K_DBG_PCI, "WWAON_WAWM_SW_ENTWY 0x%x\n", vaw);

	/* TODO: exact time to sweep is uncewtain */
	mdeway(10);

	/* wwite 0 to WWAON_WAWM_SW_ENTWY to pwevent Q6 fwom
	 * continuing wawm path and entewing dead woop.
	 */
	ath12k_pci_wwite32(ab, WWAON_WAWM_SW_ENTWY, 0);
	mdeway(10);

	vaw = ath12k_pci_wead32(ab, WWAON_WAWM_SW_ENTWY);
	ath12k_dbg(ab, ATH12K_DBG_PCI, "WWAON_WAWM_SW_ENTWY 0x%x\n", vaw);

	/* A wead cweaw wegistew. cweaw the wegistew to pwevent
	 * Q6 fwom entewing wwong code path.
	 */
	vaw = ath12k_pci_wead32(ab, WWAON_SOC_WESET_CAUSE_WEG);
	ath12k_dbg(ab, ATH12K_DBG_PCI, "soc weset cause:%d\n", vaw);
}

static void ath12k_pci_enabwe_wtssm(stwuct ath12k_base *ab)
{
	u32 vaw;
	int i;

	vaw = ath12k_pci_wead32(ab, PCIE_PCIE_PAWF_WTSSM);

	/* PCIE wink seems vewy unstabwe aftew the Hot Weset*/
	fow (i = 0; vaw != PAWM_WTSSM_VAWUE && i < 5; i++) {
		if (vaw == 0xffffffff)
			mdeway(5);

		ath12k_pci_wwite32(ab, PCIE_PCIE_PAWF_WTSSM, PAWM_WTSSM_VAWUE);
		vaw = ath12k_pci_wead32(ab, PCIE_PCIE_PAWF_WTSSM);
	}

	ath12k_dbg(ab, ATH12K_DBG_PCI, "pci wtssm 0x%x\n", vaw);

	vaw = ath12k_pci_wead32(ab, GCC_GCC_PCIE_HOT_WST);
	vaw |= GCC_GCC_PCIE_HOT_WST_VAW;
	ath12k_pci_wwite32(ab, GCC_GCC_PCIE_HOT_WST, vaw);
	vaw = ath12k_pci_wead32(ab, GCC_GCC_PCIE_HOT_WST);

	ath12k_dbg(ab, ATH12K_DBG_PCI, "pci pcie_hot_wst 0x%x\n", vaw);

	mdeway(5);
}

static void ath12k_pci_cweaw_aww_intws(stwuct ath12k_base *ab)
{
	/* This is a WAW fow PCIE Hotweset.
	 * When tawget weceive Hotweset, but wiww set the intewwupt.
	 * So when downwoad SBW again, SBW wiww open Intewwupt and
	 * weceive it, and cwash immediatewy.
	 */
	ath12k_pci_wwite32(ab, PCIE_PCIE_INT_AWW_CWEAW, PCIE_INT_CWEAW_AWW);
}

static void ath12k_pci_set_wwaon_pww_ctww(stwuct ath12k_base *ab)
{
	u32 vaw;

	vaw = ath12k_pci_wead32(ab, WWAON_QFPWOM_PWW_CTWW_WEG);
	vaw &= ~QFPWOM_PWW_CTWW_VDD4BWOW_MASK;
	ath12k_pci_wwite32(ab, WWAON_QFPWOM_PWW_CTWW_WEG, vaw);
}

static void ath12k_pci_fowce_wake(stwuct ath12k_base *ab)
{
	ath12k_pci_wwite32(ab, PCIE_SOC_WAKE_PCIE_WOCAW_WEG, 1);
	mdeway(5);
}

static void ath12k_pci_sw_weset(stwuct ath12k_base *ab, boow powew_on)
{
	if (powew_on) {
		ath12k_pci_enabwe_wtssm(ab);
		ath12k_pci_cweaw_aww_intws(ab);
		ath12k_pci_set_wwaon_pww_ctww(ab);
	}

	ath12k_mhi_cweaw_vectow(ab);
	ath12k_pci_cweaw_dbg_wegistews(ab);
	ath12k_pci_soc_gwobaw_weset(ab);
	ath12k_mhi_set_mhictww_weset(ab);
}

static void ath12k_pci_fwee_ext_iwq(stwuct ath12k_base *ab)
{
	int i, j;

	fow (i = 0; i < ATH12K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath12k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++)
			fwee_iwq(ab->iwq_num[iwq_gwp->iwqs[j]], iwq_gwp);

		netif_napi_dew(&iwq_gwp->napi);
	}
}

static void ath12k_pci_fwee_iwq(stwuct ath12k_base *ab)
{
	int i, iwq_idx;

	fow (i = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + i;
		fwee_iwq(ab->iwq_num[iwq_idx], &ab->ce.ce_pipe[i]);
	}

	ath12k_pci_fwee_ext_iwq(ab);
}

static void ath12k_pci_ce_iwq_enabwe(stwuct ath12k_base *ab, u16 ce_id)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	u32 iwq_idx;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		wetuwn;

	iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + ce_id;
	enabwe_iwq(ab->iwq_num[iwq_idx]);
}

static void ath12k_pci_ce_iwq_disabwe(stwuct ath12k_base *ab, u16 ce_id)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	u32 iwq_idx;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		wetuwn;

	iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + ce_id;
	disabwe_iwq_nosync(ab->iwq_num[iwq_idx]);
}

static void ath12k_pci_ce_iwqs_disabwe(stwuct ath12k_base *ab)
{
	int i;

	cweaw_bit(ATH12K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath12k_pci_ce_iwq_disabwe(ab, i);
	}
}

static void ath12k_pci_sync_ce_iwqs(stwuct ath12k_base *ab)
{
	int i;
	int iwq_idx;

	fow (i = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + i;
		synchwonize_iwq(ab->iwq_num[iwq_idx]);
	}
}

static void ath12k_pci_ce_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath12k_ce_pipe *ce_pipe = fwom_taskwet(ce_pipe, t, intw_tq);
	int iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + ce_pipe->pipe_num;

	ath12k_ce_pew_engine_sewvice(ce_pipe->ab, ce_pipe->pipe_num);

	enabwe_iwq(ce_pipe->ab->iwq_num[iwq_idx]);
}

static iwqwetuwn_t ath12k_pci_ce_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath12k_ce_pipe *ce_pipe = awg;
	stwuct ath12k_base *ab = ce_pipe->ab;
	int iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + ce_pipe->pipe_num;

	if (!test_bit(ATH12K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags))
		wetuwn IWQ_HANDWED;

	/* wast intewwupt weceived fow this CE */
	ce_pipe->timestamp = jiffies;

	disabwe_iwq_nosync(ab->iwq_num[iwq_idx]);

	taskwet_scheduwe(&ce_pipe->intw_tq);

	wetuwn IWQ_HANDWED;
}

static void ath12k_pci_ext_gwp_disabwe(stwuct ath12k_ext_iwq_gwp *iwq_gwp)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(iwq_gwp->ab);
	int i;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe
	 * in a unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		wetuwn;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		disabwe_iwq_nosync(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

static void __ath12k_pci_ext_iwq_disabwe(stwuct ath12k_base *ab)
{
	int i;

	cweaw_bit(ATH12K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ATH12K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath12k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		ath12k_pci_ext_gwp_disabwe(iwq_gwp);

		napi_synchwonize(&iwq_gwp->napi);
		napi_disabwe(&iwq_gwp->napi);
	}
}

static void ath12k_pci_ext_gwp_enabwe(stwuct ath12k_ext_iwq_gwp *iwq_gwp)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(iwq_gwp->ab);
	int i;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		wetuwn;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		enabwe_iwq(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

static void ath12k_pci_sync_ext_iwqs(stwuct ath12k_base *ab)
{
	int i, j, iwq_idx;

	fow (i = 0; i < ATH12K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath12k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			iwq_idx = iwq_gwp->iwqs[j];
			synchwonize_iwq(ab->iwq_num[iwq_idx]);
		}
	}
}

static int ath12k_pci_ext_gwp_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ath12k_ext_iwq_gwp *iwq_gwp = containew_of(napi,
						stwuct ath12k_ext_iwq_gwp,
						napi);
	stwuct ath12k_base *ab = iwq_gwp->ab;
	int wowk_done;
	int i;

	wowk_done = ath12k_dp_sewvice_swng(ab, iwq_gwp, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		fow (i = 0; i < iwq_gwp->num_iwq; i++)
			enabwe_iwq(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
	}

	if (wowk_done > budget)
		wowk_done = budget;

	wetuwn wowk_done;
}

static iwqwetuwn_t ath12k_pci_ext_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath12k_ext_iwq_gwp *iwq_gwp = awg;
	stwuct ath12k_base *ab = iwq_gwp->ab;
	int i;

	if (!test_bit(ATH12K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags))
		wetuwn IWQ_HANDWED;

	ath12k_dbg(iwq_gwp->ab, ATH12K_DBG_PCI, "ext iwq:%d\n", iwq);

	/* wast intewwupt weceived fow this gwoup */
	iwq_gwp->timestamp = jiffies;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		disabwe_iwq_nosync(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);

	napi_scheduwe(&iwq_gwp->napi);

	wetuwn IWQ_HANDWED;
}

static int ath12k_pci_ext_iwq_config(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	int i, j, wet, num_vectows = 0;
	u32 usew_base_data = 0, base_vectow = 0, base_idx;

	base_idx = ATH12K_PCI_IWQ_CE0_OFFSET + CE_COUNT_MAX;
	wet = ath12k_pci_get_usew_msi_assignment(ab, "DP",
						 &num_vectows,
						 &usew_base_data,
						 &base_vectow);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < ATH12K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath12k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];
		u32 num_iwq = 0;

		iwq_gwp->ab = ab;
		iwq_gwp->gwp_id = i;
		init_dummy_netdev(&iwq_gwp->napi_ndev);
		netif_napi_add(&iwq_gwp->napi_ndev, &iwq_gwp->napi,
			       ath12k_pci_ext_gwp_napi_poww);

		if (ab->hw_pawams->wing_mask->tx[i] ||
		    ab->hw_pawams->wing_mask->wx[i] ||
		    ab->hw_pawams->wing_mask->wx_eww[i] ||
		    ab->hw_pawams->wing_mask->wx_wbm_wew[i] ||
		    ab->hw_pawams->wing_mask->weo_status[i] ||
		    ab->hw_pawams->wing_mask->host2wxdma[i] ||
		    ab->hw_pawams->wing_mask->wx_mon_dest[i]) {
			num_iwq = 1;
		}

		iwq_gwp->num_iwq = num_iwq;
		iwq_gwp->iwqs[0] = base_idx + i;

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			int iwq_idx = iwq_gwp->iwqs[j];
			int vectow = (i % num_vectows) + base_vectow;
			int iwq = ath12k_pci_get_msi_iwq(ab->dev, vectow);

			ab->iwq_num[iwq_idx] = iwq;

			ath12k_dbg(ab, ATH12K_DBG_PCI,
				   "iwq:%d gwoup:%d\n", iwq, i);

			iwq_set_status_fwags(iwq, IWQ_DISABWE_UNWAZY);
			wet = wequest_iwq(iwq, ath12k_pci_ext_intewwupt_handwew,
					  ab_pci->iwq_fwags,
					  "DP_EXT_IWQ", iwq_gwp);
			if (wet) {
				ath12k_eww(ab, "faiwed wequest iwq %d: %d\n",
					   vectow, wet);
				wetuwn wet;
			}
		}
		ath12k_pci_ext_gwp_disabwe(iwq_gwp);
	}

	wetuwn 0;
}

static int ath12k_pci_set_iwq_affinity_hint(stwuct ath12k_pci *ab_pci,
					    const stwuct cpumask *m)
{
	if (test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		wetuwn 0;

	wetuwn iwq_set_affinity_hint(ab_pci->pdev->iwq, m);
}

static int ath12k_pci_config_iwq(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	stwuct ath12k_ce_pipe *ce_pipe;
	u32 msi_data_stawt;
	u32 msi_data_count, msi_data_idx;
	u32 msi_iwq_stawt;
	unsigned int msi_data;
	int iwq, i, wet, iwq_idx;

	wet = ath12k_pci_get_usew_msi_assignment(ab,
						 "CE", &msi_data_count,
						 &msi_data_stawt, &msi_iwq_stawt);
	if (wet)
		wetuwn wet;

	/* Configuwe CE iwqs */

	fow (i = 0, msi_data_idx = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		msi_data = (msi_data_idx % msi_data_count) + msi_iwq_stawt;
		iwq = ath12k_pci_get_msi_iwq(ab->dev, msi_data);
		ce_pipe = &ab->ce.ce_pipe[i];

		iwq_idx = ATH12K_PCI_IWQ_CE0_OFFSET + i;

		taskwet_setup(&ce_pipe->intw_tq, ath12k_pci_ce_taskwet);

		wet = wequest_iwq(iwq, ath12k_pci_ce_intewwupt_handwew,
				  ab_pci->iwq_fwags, iwq_name[iwq_idx],
				  ce_pipe);
		if (wet) {
			ath12k_eww(ab, "faiwed to wequest iwq %d: %d\n",
				   iwq_idx, wet);
			wetuwn wet;
		}

		ab->iwq_num[iwq_idx] = iwq;
		msi_data_idx++;

		ath12k_pci_ce_iwq_disabwe(ab, i);
	}

	wet = ath12k_pci_ext_iwq_config(ab);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void ath12k_pci_init_qmi_ce_config(stwuct ath12k_base *ab)
{
	stwuct ath12k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce = ab->hw_pawams->tawget_ce_config;
	cfg->tgt_ce_wen = ab->hw_pawams->tawget_ce_count;

	cfg->svc_to_ce_map = ab->hw_pawams->svc_to_ce_map;
	cfg->svc_to_ce_map_wen = ab->hw_pawams->svc_to_ce_map_wen;
	ab->qmi.sewvice_ins_id = ab->hw_pawams->qmi_sewvice_ins_id;
}

static void ath12k_pci_ce_iwqs_enabwe(stwuct ath12k_base *ab)
{
	int i;

	set_bit(ATH12K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath12k_pci_ce_iwq_enabwe(ab, i);
	}
}

static void ath12k_pci_msi_config(stwuct ath12k_pci *ab_pci, boow enabwe)
{
	stwuct pci_dev *dev = ab_pci->pdev;
	u16 contwow;

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &contwow);

	if (enabwe)
		contwow |= PCI_MSI_FWAGS_ENABWE;
	ewse
		contwow &= ~PCI_MSI_FWAGS_ENABWE;

	pci_wwite_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, contwow);
}

static void ath12k_pci_msi_enabwe(stwuct ath12k_pci *ab_pci)
{
	ath12k_pci_msi_config(ab_pci, twue);
}

static void ath12k_pci_msi_disabwe(stwuct ath12k_pci *ab_pci)
{
	ath12k_pci_msi_config(ab_pci, fawse);
}

static int ath12k_pci_msi_awwoc(stwuct ath12k_pci *ab_pci)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	const stwuct ath12k_msi_config *msi_config = ab_pci->msi_config;
	stwuct msi_desc *msi_desc;
	int num_vectows;
	int wet;

	num_vectows = pci_awwoc_iwq_vectows(ab_pci->pdev,
					    msi_config->totaw_vectows,
					    msi_config->totaw_vectows,
					    PCI_IWQ_MSI);

	if (num_vectows == msi_config->totaw_vectows) {
		set_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags);
		ab_pci->iwq_fwags = IWQF_SHAWED;
	} ewse {
		num_vectows = pci_awwoc_iwq_vectows(ab_pci->pdev,
						    1,
						    1,
						    PCI_IWQ_MSI);
		if (num_vectows < 0) {
			wet = -EINVAW;
			goto weset_msi_config;
		}
		cweaw_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags);
		ab_pci->msi_config = &msi_config_one_msi;
		ab_pci->iwq_fwags = IWQF_SHAWED | IWQF_NOBAWANCING;
		ath12k_dbg(ab, ATH12K_DBG_PCI, "wequest MSI one vectow\n");
	}

	ath12k_info(ab, "MSI vectows: %d\n", num_vectows);

	ath12k_pci_msi_disabwe(ab_pci);

	msi_desc = iwq_get_msi_desc(ab_pci->pdev->iwq);
	if (!msi_desc) {
		ath12k_eww(ab, "msi_desc is NUWW!\n");
		wet = -EINVAW;
		goto fwee_msi_vectow;
	}

	ab_pci->msi_ep_base_data = msi_desc->msg.data;
	if (msi_desc->pci.msi_attwib.is_64)
		set_bit(ATH12K_PCI_FWAG_IS_MSI_64, &ab_pci->fwags);

	ath12k_dbg(ab, ATH12K_DBG_PCI, "msi base data is %d\n", ab_pci->msi_ep_base_data);

	wetuwn 0;

fwee_msi_vectow:
	pci_fwee_iwq_vectows(ab_pci->pdev);

weset_msi_config:
	wetuwn wet;
}

static void ath12k_pci_msi_fwee(stwuct ath12k_pci *ab_pci)
{
	pci_fwee_iwq_vectows(ab_pci->pdev);
}

static int ath12k_pci_config_msi_data(stwuct ath12k_pci *ab_pci)
{
	stwuct msi_desc *msi_desc;

	msi_desc = iwq_get_msi_desc(ab_pci->pdev->iwq);
	if (!msi_desc) {
		ath12k_eww(ab_pci->ab, "msi_desc is NUWW!\n");
		pci_fwee_iwq_vectows(ab_pci->pdev);
		wetuwn -EINVAW;
	}

	ab_pci->msi_ep_base_data = msi_desc->msg.data;

	ath12k_dbg(ab_pci->ab, ATH12K_DBG_PCI, "pci aftew wequest_iwq msi_ep_base_data %d\n",
		   ab_pci->msi_ep_base_data);

	wetuwn 0;
}

static int ath12k_pci_cwaim(stwuct ath12k_pci *ab_pci, stwuct pci_dev *pdev)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	u16 device_id;
	int wet = 0;

	pci_wead_config_wowd(pdev, PCI_DEVICE_ID, &device_id);
	if (device_id != ab_pci->dev_id)  {
		ath12k_eww(ab, "pci device id mismatch: 0x%x 0x%x\n",
			   device_id, ab_pci->dev_id);
		wet = -EIO;
		goto out;
	}

	wet = pci_assign_wesouwce(pdev, ATH12K_PCI_BAW_NUM);
	if (wet) {
		ath12k_eww(ab, "faiwed to assign pci wesouwce: %d\n", wet);
		goto out;
	}

	wet = pci_enabwe_device(pdev);
	if (wet) {
		ath12k_eww(ab, "faiwed to enabwe pci device: %d\n", wet);
		goto out;
	}

	wet = pci_wequest_wegion(pdev, ATH12K_PCI_BAW_NUM, "ath12k_pci");
	if (wet) {
		ath12k_eww(ab, "faiwed to wequest pci wegion: %d\n", wet);
		goto disabwe_device;
	}

	wet = dma_set_mask_and_cohewent(&pdev->dev,
					DMA_BIT_MASK(ATH12K_PCI_DMA_MASK));
	if (wet) {
		ath12k_eww(ab, "faiwed to set pci dma mask to %d: %d\n",
			   ATH12K_PCI_DMA_MASK, wet);
		goto wewease_wegion;
	}

	pci_set_mastew(pdev);

	ab->mem_wen = pci_wesouwce_wen(pdev, ATH12K_PCI_BAW_NUM);
	ab->mem = pci_iomap(pdev, ATH12K_PCI_BAW_NUM, 0);
	if (!ab->mem) {
		ath12k_eww(ab, "faiwed to map pci baw %d\n", ATH12K_PCI_BAW_NUM);
		wet = -EIO;
		goto wewease_wegion;
	}

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "boot pci_mem 0x%pK\n", ab->mem);
	wetuwn 0;

wewease_wegion:
	pci_wewease_wegion(pdev, ATH12K_PCI_BAW_NUM);
disabwe_device:
	pci_disabwe_device(pdev);
out:
	wetuwn wet;
}

static void ath12k_pci_fwee_wegion(stwuct ath12k_pci *ab_pci)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	stwuct pci_dev *pci_dev = ab_pci->pdev;

	pci_iounmap(pci_dev, ab->mem);
	ab->mem = NUWW;
	pci_wewease_wegion(pci_dev, ATH12K_PCI_BAW_NUM);
	if (pci_is_enabwed(pci_dev))
		pci_disabwe_device(pci_dev);
}

static void ath12k_pci_aspm_disabwe(stwuct ath12k_pci *ab_pci)
{
	stwuct ath12k_base *ab = ab_pci->ab;

	pcie_capabiwity_wead_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
				  &ab_pci->wink_ctw);

	ath12k_dbg(ab, ATH12K_DBG_PCI, "pci wink_ctw 0x%04x W0s %d W1 %d\n",
		   ab_pci->wink_ctw,
		   u16_get_bits(ab_pci->wink_ctw, PCI_EXP_WNKCTW_ASPM_W0S),
		   u16_get_bits(ab_pci->wink_ctw, PCI_EXP_WNKCTW_ASPM_W1));

	/* disabwe W0s and W1 */
	pcie_capabiwity_cweaw_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
				   PCI_EXP_WNKCTW_ASPMC);

	set_bit(ATH12K_PCI_ASPM_WESTOWE, &ab_pci->fwags);
}

static void ath12k_pci_aspm_westowe(stwuct ath12k_pci *ab_pci)
{
	if (test_and_cweaw_bit(ATH12K_PCI_ASPM_WESTOWE, &ab_pci->fwags))
		pcie_capabiwity_cweaw_and_set_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_ASPMC,
						   ab_pci->wink_ctw &
						   PCI_EXP_WNKCTW_ASPMC);
}

static void ath12k_pci_kiww_taskwets(stwuct ath12k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams->ce_count; i++) {
		stwuct ath12k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		taskwet_kiww(&ce_pipe->intw_tq);
	}
}

static void ath12k_pci_ce_iwq_disabwe_sync(stwuct ath12k_base *ab)
{
	ath12k_pci_ce_iwqs_disabwe(ab);
	ath12k_pci_sync_ce_iwqs(ab);
	ath12k_pci_kiww_taskwets(ab);
}

int ath12k_pci_map_sewvice_to_pipe(stwuct ath12k_base *ab, u16 sewvice_id,
				   u8 *uw_pipe, u8 *dw_pipe)
{
	const stwuct sewvice_to_pipe *entwy;
	boow uw_set = fawse, dw_set = fawse;
	int i;

	fow (i = 0; i < ab->hw_pawams->svc_to_ce_map_wen; i++) {
		entwy = &ab->hw_pawams->svc_to_ce_map[i];

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

int ath12k_pci_get_msi_iwq(stwuct device *dev, unsigned int vectow)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	wetuwn pci_iwq_vectow(pci_dev, vectow);
}

int ath12k_pci_get_usew_msi_assignment(stwuct ath12k_base *ab, chaw *usew_name,
				       int *num_vectows, u32 *usew_base_data,
				       u32 *base_vectow)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	const stwuct ath12k_msi_config *msi_config = ab_pci->msi_config;
	int idx;

	fow (idx = 0; idx < msi_config->totaw_usews; idx++) {
		if (stwcmp(usew_name, msi_config->usews[idx].name) == 0) {
			*num_vectows = msi_config->usews[idx].num_vectows;
			*base_vectow =  msi_config->usews[idx].base_vectow;
			*usew_base_data = *base_vectow + ab_pci->msi_ep_base_data;

			ath12k_dbg(ab, ATH12K_DBG_PCI,
				   "Assign MSI to usew: %s, num_vectows: %d, usew_base_data: %u, base_vectow: %u\n",
				   usew_name, *num_vectows, *usew_base_data,
				   *base_vectow);

			wetuwn 0;
		}
	}

	ath12k_eww(ab, "Faiwed to find MSI assignment fow %s!\n", usew_name);

	wetuwn -EINVAW;
}

void ath12k_pci_get_msi_addwess(stwuct ath12k_base *ab, u32 *msi_addw_wo,
				u32 *msi_addw_hi)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	stwuct pci_dev *pci_dev = to_pci_dev(ab->dev);

	pci_wead_config_dwowd(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDWESS_WO,
			      msi_addw_wo);

	if (test_bit(ATH12K_PCI_FWAG_IS_MSI_64, &ab_pci->fwags)) {
		pci_wead_config_dwowd(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDWESS_HI,
				      msi_addw_hi);
	} ewse {
		*msi_addw_hi = 0;
	}
}

void ath12k_pci_get_ce_msi_idx(stwuct ath12k_base *ab, u32 ce_id,
			       u32 *msi_idx)
{
	u32 i, msi_data_idx;

	fow (i = 0, msi_data_idx = 0; i < ab->hw_pawams->ce_count; i++) {
		if (ath12k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		if (ce_id == i)
			bweak;

		msi_data_idx++;
	}
	*msi_idx = msi_data_idx;
}

void ath12k_pci_hif_ce_iwq_enabwe(stwuct ath12k_base *ab)
{
	ath12k_pci_ce_iwqs_enabwe(ab);
}

void ath12k_pci_hif_ce_iwq_disabwe(stwuct ath12k_base *ab)
{
	ath12k_pci_ce_iwq_disabwe_sync(ab);
}

void ath12k_pci_ext_iwq_enabwe(stwuct ath12k_base *ab)
{
	int i;

	set_bit(ATH12K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ATH12K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath12k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		napi_enabwe(&iwq_gwp->napi);
		ath12k_pci_ext_gwp_enabwe(iwq_gwp);
	}
}

void ath12k_pci_ext_iwq_disabwe(stwuct ath12k_base *ab)
{
	__ath12k_pci_ext_iwq_disabwe(ab);
	ath12k_pci_sync_ext_iwqs(ab);
}

int ath12k_pci_hif_suspend(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *aw_pci = ath12k_pci_pwiv(ab);

	ath12k_mhi_suspend(aw_pci);

	wetuwn 0;
}

int ath12k_pci_hif_wesume(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *aw_pci = ath12k_pci_pwiv(ab);

	ath12k_mhi_wesume(aw_pci);

	wetuwn 0;
}

void ath12k_pci_stop(stwuct ath12k_base *ab)
{
	ath12k_pci_ce_iwq_disabwe_sync(ab);
	ath12k_ce_cweanup_pipes(ab);
}

int ath12k_pci_stawt(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	set_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags);

	if (test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		ath12k_pci_aspm_westowe(ab_pci);
	ewse
		ath12k_info(ab, "weaving PCI ASPM disabwed to avoid MHI M2 pwobwems\n");

	ath12k_pci_ce_iwqs_enabwe(ab);
	ath12k_ce_wx_post_buf(ab);

	wetuwn 0;
}

u32 ath12k_pci_wead32(stwuct ath12k_base *ab, u32 offset)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	u32 vaw, window_stawt;
	int wet = 0;

	/* fow offset beyond BAW + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	if (test_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags) &&
	    offset >= ACCESS_AWWAYS_OFF && ab_pci->pci_ops->wakeup)
		wet = ab_pci->pci_ops->wakeup(ab);

	if (offset < WINDOW_STAWT) {
		vaw = iowead32(ab->mem + offset);
	} ewse {
		if (ab->static_window_map)
			window_stawt = ath12k_pci_get_window_stawt(ab, offset);
		ewse
			window_stawt = WINDOW_STAWT;

		if (window_stawt == WINDOW_STAWT) {
			spin_wock_bh(&ab_pci->window_wock);
			ath12k_pci_sewect_window(ab_pci, offset);
			vaw = iowead32(ab->mem + window_stawt +
				       (offset & WINDOW_WANGE_MASK));
			spin_unwock_bh(&ab_pci->window_wock);
		} ewse {
			if ((!window_stawt) &&
			    (offset >= PCI_MHIWEGWEN_WEG &&
			     offset <= PCI_MHI_WEGION_END))
				offset = offset - PCI_MHIWEGWEN_WEG;

			vaw = iowead32(ab->mem + window_stawt +
				       (offset & WINDOW_WANGE_MASK));
		}
	}

	if (test_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags) &&
	    offset >= ACCESS_AWWAYS_OFF && ab_pci->pci_ops->wewease &&
	    !wet)
		ab_pci->pci_ops->wewease(ab);
	wetuwn vaw;
}

void ath12k_pci_wwite32(stwuct ath12k_base *ab, u32 offset, u32 vawue)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	u32 window_stawt;
	int wet = 0;

	/* fow offset beyond BAW + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	if (test_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags) &&
	    offset >= ACCESS_AWWAYS_OFF && ab_pci->pci_ops->wakeup)
		wet = ab_pci->pci_ops->wakeup(ab);

	if (offset < WINDOW_STAWT) {
		iowwite32(vawue, ab->mem + offset);
	} ewse {
		if (ab->static_window_map)
			window_stawt = ath12k_pci_get_window_stawt(ab, offset);
		ewse
			window_stawt = WINDOW_STAWT;

		if (window_stawt == WINDOW_STAWT) {
			spin_wock_bh(&ab_pci->window_wock);
			ath12k_pci_sewect_window(ab_pci, offset);
			iowwite32(vawue, ab->mem + window_stawt +
				  (offset & WINDOW_WANGE_MASK));
			spin_unwock_bh(&ab_pci->window_wock);
		} ewse {
			if ((!window_stawt) &&
			    (offset >= PCI_MHIWEGWEN_WEG &&
			     offset <= PCI_MHI_WEGION_END))
				offset = offset - PCI_MHIWEGWEN_WEG;

			iowwite32(vawue, ab->mem + window_stawt +
				  (offset & WINDOW_WANGE_MASK));
		}
	}

	if (test_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags) &&
	    offset >= ACCESS_AWWAYS_OFF && ab_pci->pci_ops->wewease &&
	    !wet)
		ab_pci->pci_ops->wewease(ab);
}

int ath12k_pci_powew_up(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);
	int wet;

	ab_pci->wegistew_window = 0;
	cweaw_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags);
	ath12k_pci_sw_weset(ab_pci->ab, twue);

	/* Disabwe ASPM duwing fiwmwawe downwoad due to pwobwems switching
	 * to AMSS state.
	 */
	ath12k_pci_aspm_disabwe(ab_pci);

	ath12k_pci_msi_enabwe(ab_pci);

	wet = ath12k_mhi_stawt(ab_pci);
	if (wet) {
		ath12k_eww(ab, "faiwed to stawt mhi: %d\n", wet);
		wetuwn wet;
	}

	if (ab->static_window_map)
		ath12k_pci_sewect_static_window(ab_pci);

	wetuwn 0;
}

void ath12k_pci_powew_down(stwuct ath12k_base *ab)
{
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	/* westowe aspm in case fiwmwawe bootup faiws */
	ath12k_pci_aspm_westowe(ab_pci);

	ath12k_pci_fowce_wake(ab_pci->ab);
	ath12k_pci_msi_disabwe(ab_pci);
	ath12k_mhi_stop(ab_pci);
	cweaw_bit(ATH12K_PCI_FWAG_INIT_DONE, &ab_pci->fwags);
	ath12k_pci_sw_weset(ab_pci->ab, fawse);
}

static const stwuct ath12k_hif_ops ath12k_pci_hif_ops = {
	.stawt = ath12k_pci_stawt,
	.stop = ath12k_pci_stop,
	.wead32 = ath12k_pci_wead32,
	.wwite32 = ath12k_pci_wwite32,
	.powew_down = ath12k_pci_powew_down,
	.powew_up = ath12k_pci_powew_up,
	.suspend = ath12k_pci_hif_suspend,
	.wesume = ath12k_pci_hif_wesume,
	.iwq_enabwe = ath12k_pci_ext_iwq_enabwe,
	.iwq_disabwe = ath12k_pci_ext_iwq_disabwe,
	.get_msi_addwess = ath12k_pci_get_msi_addwess,
	.get_usew_msi_vectow = ath12k_pci_get_usew_msi_assignment,
	.map_sewvice_to_pipe = ath12k_pci_map_sewvice_to_pipe,
	.ce_iwq_enabwe = ath12k_pci_hif_ce_iwq_enabwe,
	.ce_iwq_disabwe = ath12k_pci_hif_ce_iwq_disabwe,
	.get_ce_msi_idx = ath12k_pci_get_ce_msi_idx,
};

static
void ath12k_pci_wead_hw_vewsion(stwuct ath12k_base *ab, u32 *majow, u32 *minow)
{
	u32 soc_hw_vewsion;

	soc_hw_vewsion = ath12k_pci_wead32(ab, TCSW_SOC_HW_VEWSION);
	*majow = FIEWD_GET(TCSW_SOC_HW_VEWSION_MAJOW_MASK,
			   soc_hw_vewsion);
	*minow = FIEWD_GET(TCSW_SOC_HW_VEWSION_MINOW_MASK,
			   soc_hw_vewsion);

	ath12k_dbg(ab, ATH12K_DBG_PCI,
		   "pci tcsw_soc_hw_vewsion majow %d minow %d\n",
		    *majow, *minow);
}

static int ath12k_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *pci_dev)
{
	stwuct ath12k_base *ab;
	stwuct ath12k_pci *ab_pci;
	u32 soc_hw_vewsion_majow, soc_hw_vewsion_minow;
	int wet;

	ab = ath12k_cowe_awwoc(&pdev->dev, sizeof(*ab_pci), ATH12K_BUS_PCI);
	if (!ab) {
		dev_eww(&pdev->dev, "faiwed to awwocate ath12k base\n");
		wetuwn -ENOMEM;
	}

	ab->dev = &pdev->dev;
	pci_set_dwvdata(pdev, ab);
	ab_pci = ath12k_pci_pwiv(ab);
	ab_pci->dev_id = pci_dev->device;
	ab_pci->ab = ab;
	ab_pci->pdev = pdev;
	ab->hif.ops = &ath12k_pci_hif_ops;
	pci_set_dwvdata(pdev, ab);
	spin_wock_init(&ab_pci->window_wock);

	wet = ath12k_pci_cwaim(ab_pci, pdev);
	if (wet) {
		ath12k_eww(ab, "faiwed to cwaim device: %d\n", wet);
		goto eww_fwee_cowe;
	}

	switch (pci_dev->device) {
	case QCN9274_DEVICE_ID:
		ab_pci->msi_config = &ath12k_msi_config[0];
		ab->static_window_map = twue;
		ab_pci->pci_ops = &ath12k_pci_ops_qcn9274;
		ath12k_pci_wead_hw_vewsion(ab, &soc_hw_vewsion_majow,
					   &soc_hw_vewsion_minow);
		switch (soc_hw_vewsion_majow) {
		case ATH12K_PCI_SOC_HW_VEWSION_2:
			ab->hw_wev = ATH12K_HW_QCN9274_HW20;
			bweak;
		case ATH12K_PCI_SOC_HW_VEWSION_1:
			ab->hw_wev = ATH12K_HW_QCN9274_HW10;
			bweak;
		defauwt:
			dev_eww(&pdev->dev,
				"Unknown hawdwawe vewsion found fow QCN9274: 0x%x\n",
				soc_hw_vewsion_majow);
			wet = -EOPNOTSUPP;
			goto eww_pci_fwee_wegion;
		}
		bweak;
	case WCN7850_DEVICE_ID:
		ab_pci->msi_config = &ath12k_msi_config[0];
		ab->static_window_map = fawse;
		ab_pci->pci_ops = &ath12k_pci_ops_wcn7850;
		ath12k_pci_wead_hw_vewsion(ab, &soc_hw_vewsion_majow,
					   &soc_hw_vewsion_minow);
		switch (soc_hw_vewsion_majow) {
		case ATH12K_PCI_SOC_HW_VEWSION_2:
			ab->hw_wev = ATH12K_HW_WCN7850_HW20;
			bweak;
		defauwt:
			dev_eww(&pdev->dev,
				"Unknown hawdwawe vewsion found fow WCN7850: 0x%x\n",
				soc_hw_vewsion_majow);
			wet = -EOPNOTSUPP;
			goto eww_pci_fwee_wegion;
		}
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unknown PCI device found: 0x%x\n",
			pci_dev->device);
		wet = -EOPNOTSUPP;
		goto eww_pci_fwee_wegion;
	}

	wet = ath12k_pci_msi_awwoc(ab_pci);
	if (wet) {
		ath12k_eww(ab, "faiwed to awwoc msi: %d\n", wet);
		goto eww_pci_fwee_wegion;
	}

	wet = ath12k_cowe_pwe_init(ab);
	if (wet)
		goto eww_pci_msi_fwee;

	wet = ath12k_pci_set_iwq_affinity_hint(ab_pci, cpumask_of(0));
	if (wet) {
		ath12k_eww(ab, "faiwed to set iwq affinity %d\n", wet);
		goto eww_pci_msi_fwee;
	}

	wet = ath12k_mhi_wegistew(ab_pci);
	if (wet) {
		ath12k_eww(ab, "faiwed to wegistew mhi: %d\n", wet);
		goto eww_iwq_affinity_cweanup;
	}

	wet = ath12k_haw_swng_init(ab);
	if (wet)
		goto eww_mhi_unwegistew;

	wet = ath12k_ce_awwoc_pipes(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to awwocate ce pipes: %d\n", wet);
		goto eww_haw_swng_deinit;
	}

	ath12k_pci_init_qmi_ce_config(ab);

	wet = ath12k_pci_config_iwq(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to config iwq: %d\n", wet);
		goto eww_ce_fwee;
	}

	/* kewnew may awwocate a dummy vectow befowe wequest_iwq and
	 * then awwocate a weaw vectow when wequest_iwq is cawwed.
	 * So get msi_data hewe again to avoid spuwious intewwupt
	 * as msi_data wiww configuwed to swngs.
	 */
	wet = ath12k_pci_config_msi_data(ab_pci);
	if (wet) {
		ath12k_eww(ab, "faiwed to config msi_data: %d\n", wet);
		goto eww_fwee_iwq;
	}

	wet = ath12k_cowe_init(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to init cowe: %d\n", wet);
		goto eww_fwee_iwq;
	}
	wetuwn 0;

eww_fwee_iwq:
	ath12k_pci_fwee_iwq(ab);

eww_ce_fwee:
	ath12k_ce_fwee_pipes(ab);

eww_haw_swng_deinit:
	ath12k_haw_swng_deinit(ab);

eww_mhi_unwegistew:
	ath12k_mhi_unwegistew(ab_pci);

eww_pci_msi_fwee:
	ath12k_pci_msi_fwee(ab_pci);

eww_iwq_affinity_cweanup:
	ath12k_pci_set_iwq_affinity_hint(ab_pci, NUWW);

eww_pci_fwee_wegion:
	ath12k_pci_fwee_wegion(ab_pci);

eww_fwee_cowe:
	ath12k_cowe_fwee(ab);

	wetuwn wet;
}

static void ath12k_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ath12k_base *ab = pci_get_dwvdata(pdev);
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	ath12k_pci_set_iwq_affinity_hint(ab_pci, NUWW);

	if (test_bit(ATH12K_FWAG_QMI_FAIW, &ab->dev_fwags)) {
		ath12k_pci_powew_down(ab);
		ath12k_qmi_deinit_sewvice(ab);
		goto qmi_faiw;
	}

	set_bit(ATH12K_FWAG_UNWEGISTEWING, &ab->dev_fwags);

	cancew_wowk_sync(&ab->weset_wowk);
	ath12k_cowe_deinit(ab);

qmi_faiw:
	ath12k_mhi_unwegistew(ab_pci);

	ath12k_pci_fwee_iwq(ab);
	ath12k_pci_msi_fwee(ab_pci);
	ath12k_pci_fwee_wegion(ab_pci);

	ath12k_haw_swng_deinit(ab);
	ath12k_ce_fwee_pipes(ab);
	ath12k_cowe_fwee(ab);
}

static void ath12k_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct ath12k_base *ab = pci_get_dwvdata(pdev);
	stwuct ath12k_pci *ab_pci = ath12k_pci_pwiv(ab);

	ath12k_pci_set_iwq_affinity_hint(ab_pci, NUWW);
	ath12k_pci_powew_down(ab);
}

static __maybe_unused int ath12k_pci_pm_suspend(stwuct device *dev)
{
	stwuct ath12k_base *ab = dev_get_dwvdata(dev);
	int wet;

	wet = ath12k_cowe_suspend(ab);
	if (wet)
		ath12k_wawn(ab, "faiwed to suspend cowe: %d\n", wet);

	wetuwn wet;
}

static __maybe_unused int ath12k_pci_pm_wesume(stwuct device *dev)
{
	stwuct ath12k_base *ab = dev_get_dwvdata(dev);
	int wet;

	wet = ath12k_cowe_wesume(ab);
	if (wet)
		ath12k_wawn(ab, "faiwed to wesume cowe: %d\n", wet);

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(ath12k_pci_pm_ops,
			 ath12k_pci_pm_suspend,
			 ath12k_pci_pm_wesume);

static stwuct pci_dwivew ath12k_pci_dwivew = {
	.name = "ath12k_pci",
	.id_tabwe = ath12k_pci_id_tabwe,
	.pwobe = ath12k_pci_pwobe,
	.wemove = ath12k_pci_wemove,
	.shutdown = ath12k_pci_shutdown,
	.dwivew.pm = &ath12k_pci_pm_ops,
};

static int ath12k_pci_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&ath12k_pci_dwivew);
	if (wet) {
		pw_eww("faiwed to wegistew ath12k pci dwivew: %d\n",
		       wet);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(ath12k_pci_init);

static void ath12k_pci_exit(void)
{
	pci_unwegistew_dwivew(&ath12k_pci_dwivew);
}

moduwe_exit(ath12k_pci_exit);

MODUWE_DESCWIPTION("Dwivew suppowt fow Quawcomm Technowogies PCIe 802.11be WWAN devices");
MODUWE_WICENSE("Duaw BSD/GPW");
