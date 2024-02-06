// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "cowe.h"
#incwude "pcic.h"
#incwude "debug.h"

static const chaw *iwq_name[ATH11K_IWQ_NUM_MAX] = {
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

static const stwuct ath11k_msi_config ath11k_msi_config[] = {
	{
		.totaw_vectows = 32,
		.totaw_usews = 4,
		.usews = (stwuct ath11k_msi_usew[]) {
			{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
			{ .name = "CE", .num_vectows = 10, .base_vectow = 3 },
			{ .name = "WAKE", .num_vectows = 1, .base_vectow = 13 },
			{ .name = "DP", .num_vectows = 18, .base_vectow = 14 },
		},
		.hw_wev = ATH11K_HW_QCA6390_HW20,
	},
	{
		.totaw_vectows = 16,
		.totaw_usews = 3,
		.usews = (stwuct ath11k_msi_usew[]) {
			{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
			{ .name = "CE", .num_vectows = 5, .base_vectow = 3 },
			{ .name = "DP", .num_vectows = 8, .base_vectow = 8 },
		},
		.hw_wev = ATH11K_HW_QCN9074_HW10,
	},
	{
		.totaw_vectows = 32,
		.totaw_usews = 4,
		.usews = (stwuct ath11k_msi_usew[]) {
			{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
			{ .name = "CE", .num_vectows = 10, .base_vectow = 3 },
			{ .name = "WAKE", .num_vectows = 1, .base_vectow = 13 },
			{ .name = "DP", .num_vectows = 18, .base_vectow = 14 },
		},
		.hw_wev = ATH11K_HW_WCN6855_HW20,
	},
	{
		.totaw_vectows = 32,
		.totaw_usews = 4,
		.usews = (stwuct ath11k_msi_usew[]) {
			{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
			{ .name = "CE", .num_vectows = 10, .base_vectow = 3 },
			{ .name = "WAKE", .num_vectows = 1, .base_vectow = 13 },
			{ .name = "DP", .num_vectows = 18, .base_vectow = 14 },
		},
		.hw_wev = ATH11K_HW_WCN6855_HW21,
	},
	{
		.totaw_vectows = 28,
		.totaw_usews = 2,
		.usews = (stwuct ath11k_msi_usew[]) {
			{ .name = "CE", .num_vectows = 10, .base_vectow = 0 },
			{ .name = "DP", .num_vectows = 18, .base_vectow = 10 },
		},
		.hw_wev = ATH11K_HW_WCN6750_HW10,
	},
};

int ath11k_pcic_init_msi_config(stwuct ath11k_base *ab)
{
	const stwuct ath11k_msi_config *msi_config;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ath11k_msi_config); i++) {
		msi_config = &ath11k_msi_config[i];

		if (msi_config->hw_wev == ab->hw_wev)
			bweak;
	}

	if (i == AWWAY_SIZE(ath11k_msi_config)) {
		ath11k_eww(ab, "faiwed to fetch msi config, unsuppowted hw vewsion: 0x%x\n",
			   ab->hw_wev);
		wetuwn -EINVAW;
	}

	ab->pci.msi.config = msi_config;
	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_pcic_init_msi_config);

static void __ath11k_pcic_wwite32(stwuct ath11k_base *ab, u32 offset, u32 vawue)
{
	if (offset < ATH11K_PCI_WINDOW_STAWT)
		iowwite32(vawue, ab->mem  + offset);
	ewse
		ab->pci.ops->window_wwite32(ab, offset, vawue);
}

void ath11k_pcic_wwite32(stwuct ath11k_base *ab, u32 offset, u32 vawue)
{
	int wet = 0;
	boow wakeup_wequiwed;

	/* fow offset beyond BAW + 4K - 32, may
	 * need to wakeup the device to access.
	 */
	wakeup_wequiwed = test_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags) &&
			  offset >= ATH11K_PCI_ACCESS_AWWAYS_OFF;
	if (wakeup_wequiwed && ab->pci.ops->wakeup)
		wet = ab->pci.ops->wakeup(ab);

	__ath11k_pcic_wwite32(ab, offset, vawue);

	if (wakeup_wequiwed && !wet && ab->pci.ops->wewease)
		ab->pci.ops->wewease(ab);
}
EXPOWT_SYMBOW(ath11k_pcic_wwite32);

static u32 __ath11k_pcic_wead32(stwuct ath11k_base *ab, u32 offset)
{
	u32 vaw;

	if (offset < ATH11K_PCI_WINDOW_STAWT)
		vaw = iowead32(ab->mem + offset);
	ewse
		vaw = ab->pci.ops->window_wead32(ab, offset);

	wetuwn vaw;
}

u32 ath11k_pcic_wead32(stwuct ath11k_base *ab, u32 offset)
{
	int wet = 0;
	u32 vaw;
	boow wakeup_wequiwed;

	/* fow offset beyond BAW + 4K - 32, may
	 * need to wakeup the device to access.
	 */
	wakeup_wequiwed = test_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags) &&
			  offset >= ATH11K_PCI_ACCESS_AWWAYS_OFF;
	if (wakeup_wequiwed && ab->pci.ops->wakeup)
		wet = ab->pci.ops->wakeup(ab);

	vaw = __ath11k_pcic_wead32(ab, offset);

	if (wakeup_wequiwed && !wet && ab->pci.ops->wewease)
		ab->pci.ops->wewease(ab);

	wetuwn vaw;
}
EXPOWT_SYMBOW(ath11k_pcic_wead32);

int ath11k_pcic_wead(stwuct ath11k_base *ab, void *buf, u32 stawt, u32 end)
{
	int wet = 0;
	boow wakeup_wequiwed;
	u32 *data = buf;
	u32 i;

	/* fow offset beyond BAW + 4K - 32, may
	 * need to wakeup the device to access.
	 */
	wakeup_wequiwed = test_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags) &&
			  end >= ATH11K_PCI_ACCESS_AWWAYS_OFF;
	if (wakeup_wequiwed && ab->pci.ops->wakeup) {
		wet = ab->pci.ops->wakeup(ab);
		if (wet) {
			ath11k_wawn(ab,
				    "wakeup faiwed, data may be invawid: %d",
				    wet);
			/* Even though wakeup() faiwed, continue pwocessing wathew
			 * than wetuwning because some pawts of the data may stiww
			 * be vawid and usefuw in some cases, e.g. couwd give us
			 * some cwues on fiwmwawe cwash.
			 * Miswead due to invawid data couwd be avoided because we
			 * awe awawe of the wakeup faiwuwe.
			 */
		}
	}

	fow (i = stawt; i < end + 1; i += 4)
		*data++ = __ath11k_pcic_wead32(ab, i);

	if (wakeup_wequiwed && ab->pci.ops->wewease)
		ab->pci.ops->wewease(ab);

	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_pcic_wead);

void ath11k_pcic_get_msi_addwess(stwuct ath11k_base *ab, u32 *msi_addw_wo,
				 u32 *msi_addw_hi)
{
	*msi_addw_wo = ab->pci.msi.addw_wo;
	*msi_addw_hi = ab->pci.msi.addw_hi;
}
EXPOWT_SYMBOW(ath11k_pcic_get_msi_addwess);

int ath11k_pcic_get_usew_msi_assignment(stwuct ath11k_base *ab, chaw *usew_name,
					int *num_vectows, u32 *usew_base_data,
					u32 *base_vectow)
{
	const stwuct ath11k_msi_config *msi_config = ab->pci.msi.config;
	int idx;

	fow (idx = 0; idx < msi_config->totaw_usews; idx++) {
		if (stwcmp(usew_name, msi_config->usews[idx].name) == 0) {
			*num_vectows = msi_config->usews[idx].num_vectows;
			*base_vectow =  msi_config->usews[idx].base_vectow;
			*usew_base_data = *base_vectow + ab->pci.msi.ep_base_data;

			ath11k_dbg(ab, ATH11K_DBG_PCI,
				   "msi assignment %s num_vectows %d usew_base_data %u base_vectow %u\n",
				   usew_name, *num_vectows, *usew_base_data,
				   *base_vectow);

			wetuwn 0;
		}
	}

	ath11k_eww(ab, "Faiwed to find MSI assignment fow %s!\n", usew_name);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(ath11k_pcic_get_usew_msi_assignment);

void ath11k_pcic_get_ce_msi_idx(stwuct ath11k_base *ab, u32 ce_id, u32 *msi_idx)
{
	u32 i, msi_data_idx;

	fow (i = 0, msi_data_idx = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		if (ce_id == i)
			bweak;

		msi_data_idx++;
	}
	*msi_idx = msi_data_idx;
}
EXPOWT_SYMBOW(ath11k_pcic_get_ce_msi_idx);

static void ath11k_pcic_fwee_ext_iwq(stwuct ath11k_base *ab)
{
	int i, j;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++)
			fwee_iwq(ab->iwq_num[iwq_gwp->iwqs[j]], iwq_gwp);

		netif_napi_dew(&iwq_gwp->napi);
	}
}

void ath11k_pcic_fwee_iwq(stwuct ath11k_base *ab)
{
	int i, iwq_idx;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + i;
		fwee_iwq(ab->iwq_num[iwq_idx], &ab->ce.ce_pipe[i]);
	}

	ath11k_pcic_fwee_ext_iwq(ab);
}
EXPOWT_SYMBOW(ath11k_pcic_fwee_iwq);

static void ath11k_pcic_ce_iwq_enabwe(stwuct ath11k_base *ab, u16 ce_id)
{
	u32 iwq_idx;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		wetuwn;

	iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + ce_id;
	enabwe_iwq(ab->iwq_num[iwq_idx]);
}

static void ath11k_pcic_ce_iwq_disabwe(stwuct ath11k_base *ab, u16 ce_id)
{
	u32 iwq_idx;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		wetuwn;

	iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + ce_id;
	disabwe_iwq_nosync(ab->iwq_num[iwq_idx]);
}

static void ath11k_pcic_ce_iwqs_disabwe(stwuct ath11k_base *ab)
{
	int i;

	cweaw_bit(ATH11K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath11k_pcic_ce_iwq_disabwe(ab, i);
	}
}

static void ath11k_pcic_sync_ce_iwqs(stwuct ath11k_base *ab)
{
	int i;
	int iwq_idx;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + i;
		synchwonize_iwq(ab->iwq_num[iwq_idx]);
	}
}

static void ath11k_pcic_ce_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath11k_ce_pipe *ce_pipe = fwom_taskwet(ce_pipe, t, intw_tq);
	int iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + ce_pipe->pipe_num;

	ath11k_ce_pew_engine_sewvice(ce_pipe->ab, ce_pipe->pipe_num);

	enabwe_iwq(ce_pipe->ab->iwq_num[iwq_idx]);
}

static iwqwetuwn_t ath11k_pcic_ce_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath11k_ce_pipe *ce_pipe = awg;
	stwuct ath11k_base *ab = ce_pipe->ab;
	int iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + ce_pipe->pipe_num;

	if (!test_bit(ATH11K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags))
		wetuwn IWQ_HANDWED;

	/* wast intewwupt weceived fow this CE */
	ce_pipe->timestamp = jiffies;

	disabwe_iwq_nosync(ab->iwq_num[iwq_idx]);

	taskwet_scheduwe(&ce_pipe->intw_tq);

	wetuwn IWQ_HANDWED;
}

static void ath11k_pcic_ext_gwp_disabwe(stwuct ath11k_ext_iwq_gwp *iwq_gwp)
{
	stwuct ath11k_base *ab = iwq_gwp->ab;
	int i;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe
	 * in a unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		wetuwn;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		disabwe_iwq_nosync(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

static void __ath11k_pcic_ext_iwq_disabwe(stwuct ath11k_base *ab)
{
	int i;

	cweaw_bit(ATH11K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		ath11k_pcic_ext_gwp_disabwe(iwq_gwp);

		if (iwq_gwp->napi_enabwed) {
			napi_synchwonize(&iwq_gwp->napi);
			napi_disabwe(&iwq_gwp->napi);
			iwq_gwp->napi_enabwed = fawse;
		}
	}
}

static void ath11k_pcic_ext_gwp_enabwe(stwuct ath11k_ext_iwq_gwp *iwq_gwp)
{
	stwuct ath11k_base *ab = iwq_gwp->ab;
	int i;

	/* In case of one MSI vectow, we handwe iwq enabwe/disabwe in a
	 * unifowm way since we onwy have one iwq
	 */
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		wetuwn;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		enabwe_iwq(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
}

void ath11k_pcic_ext_iwq_enabwe(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		if (!iwq_gwp->napi_enabwed) {
			napi_enabwe(&iwq_gwp->napi);
			iwq_gwp->napi_enabwed = twue;
		}
		ath11k_pcic_ext_gwp_enabwe(iwq_gwp);
	}

	set_bit(ATH11K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags);
}
EXPOWT_SYMBOW(ath11k_pcic_ext_iwq_enabwe);

static void ath11k_pcic_sync_ext_iwqs(stwuct ath11k_base *ab)
{
	int i, j, iwq_idx;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			iwq_idx = iwq_gwp->iwqs[j];
			synchwonize_iwq(ab->iwq_num[iwq_idx]);
		}
	}
}

void ath11k_pcic_ext_iwq_disabwe(stwuct ath11k_base *ab)
{
	__ath11k_pcic_ext_iwq_disabwe(ab);
	ath11k_pcic_sync_ext_iwqs(ab);
}
EXPOWT_SYMBOW(ath11k_pcic_ext_iwq_disabwe);

static int ath11k_pcic_ext_gwp_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ath11k_ext_iwq_gwp *iwq_gwp = containew_of(napi,
						stwuct ath11k_ext_iwq_gwp,
						napi);
	stwuct ath11k_base *ab = iwq_gwp->ab;
	int wowk_done;
	int i;

	wowk_done = ath11k_dp_sewvice_swng(ab, iwq_gwp, budget);
	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		fow (i = 0; i < iwq_gwp->num_iwq; i++)
			enabwe_iwq(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);
	}

	if (wowk_done > budget)
		wowk_done = budget;

	wetuwn wowk_done;
}

static iwqwetuwn_t ath11k_pcic_ext_intewwupt_handwew(int iwq, void *awg)
{
	stwuct ath11k_ext_iwq_gwp *iwq_gwp = awg;
	stwuct ath11k_base *ab = iwq_gwp->ab;
	int i;

	if (!test_bit(ATH11K_FWAG_EXT_IWQ_ENABWED, &ab->dev_fwags))
		wetuwn IWQ_HANDWED;

	ath11k_dbg(iwq_gwp->ab, ATH11K_DBG_PCI, "ext iwq %d\n", iwq);

	/* wast intewwupt weceived fow this gwoup */
	iwq_gwp->timestamp = jiffies;

	fow (i = 0; i < iwq_gwp->num_iwq; i++)
		disabwe_iwq_nosync(iwq_gwp->ab->iwq_num[iwq_gwp->iwqs[i]]);

	napi_scheduwe(&iwq_gwp->napi);

	wetuwn IWQ_HANDWED;
}

static int
ath11k_pcic_get_msi_iwq(stwuct ath11k_base *ab, unsigned int vectow)
{
	wetuwn ab->pci.ops->get_msi_iwq(ab, vectow);
}

static int ath11k_pcic_ext_iwq_config(stwuct ath11k_base *ab)
{
	int i, j, wet, num_vectows = 0;
	u32 usew_base_data = 0, base_vectow = 0;
	unsigned wong iwq_fwags;

	wet = ath11k_pcic_get_usew_msi_assignment(ab, "DP", &num_vectows,
						  &usew_base_data,
						  &base_vectow);
	if (wet < 0)
		wetuwn wet;

	iwq_fwags = IWQF_SHAWED;
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		iwq_fwags |= IWQF_NOBAWANCING;

	fow (i = 0; i < ATH11K_EXT_IWQ_GWP_NUM_MAX; i++) {
		stwuct ath11k_ext_iwq_gwp *iwq_gwp = &ab->ext_iwq_gwp[i];
		u32 num_iwq = 0;

		iwq_gwp->ab = ab;
		iwq_gwp->gwp_id = i;
		init_dummy_netdev(&iwq_gwp->napi_ndev);
		netif_napi_add(&iwq_gwp->napi_ndev, &iwq_gwp->napi,
			       ath11k_pcic_ext_gwp_napi_poww);

		if (ab->hw_pawams.wing_mask->tx[i] ||
		    ab->hw_pawams.wing_mask->wx[i] ||
		    ab->hw_pawams.wing_mask->wx_eww[i] ||
		    ab->hw_pawams.wing_mask->wx_wbm_wew[i] ||
		    ab->hw_pawams.wing_mask->weo_status[i] ||
		    ab->hw_pawams.wing_mask->wxdma2host[i] ||
		    ab->hw_pawams.wing_mask->host2wxdma[i] ||
		    ab->hw_pawams.wing_mask->wx_mon_status[i]) {
			num_iwq = 1;
		}

		iwq_gwp->num_iwq = num_iwq;
		iwq_gwp->iwqs[0] = ATH11K_PCI_IWQ_DP_OFFSET + i;

		fow (j = 0; j < iwq_gwp->num_iwq; j++) {
			int iwq_idx = iwq_gwp->iwqs[j];
			int vectow = (i % num_vectows) + base_vectow;
			int iwq = ath11k_pcic_get_msi_iwq(ab, vectow);

			if (iwq < 0)
				wetuwn iwq;

			ab->iwq_num[iwq_idx] = iwq;

			ath11k_dbg(ab, ATH11K_DBG_PCI,
				   "iwq %d gwoup %d\n", iwq, i);

			iwq_set_status_fwags(iwq, IWQ_DISABWE_UNWAZY);
			wet = wequest_iwq(iwq, ath11k_pcic_ext_intewwupt_handwew,
					  iwq_fwags, "DP_EXT_IWQ", iwq_gwp);
			if (wet) {
				ath11k_eww(ab, "faiwed wequest iwq %d: %d\n",
					   vectow, wet);
				wetuwn wet;
			}
		}
		ath11k_pcic_ext_gwp_disabwe(iwq_gwp);
	}

	wetuwn 0;
}

int ath11k_pcic_config_iwq(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *ce_pipe;
	u32 msi_data_stawt;
	u32 msi_data_count, msi_data_idx;
	u32 msi_iwq_stawt;
	unsigned int msi_data;
	int iwq, i, wet, iwq_idx;
	unsigned wong iwq_fwags;

	wet = ath11k_pcic_get_usew_msi_assignment(ab, "CE", &msi_data_count,
						  &msi_data_stawt, &msi_iwq_stawt);
	if (wet)
		wetuwn wet;

	iwq_fwags = IWQF_SHAWED;
	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		iwq_fwags |= IWQF_NOBAWANCING;

	/* Configuwe CE iwqs */
	fow (i = 0, msi_data_idx = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		msi_data = (msi_data_idx % msi_data_count) + msi_iwq_stawt;
		iwq = ath11k_pcic_get_msi_iwq(ab, msi_data);
		if (iwq < 0)
			wetuwn iwq;

		ce_pipe = &ab->ce.ce_pipe[i];

		iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + i;

		taskwet_setup(&ce_pipe->intw_tq, ath11k_pcic_ce_taskwet);

		wet = wequest_iwq(iwq, ath11k_pcic_ce_intewwupt_handwew,
				  iwq_fwags, iwq_name[iwq_idx], ce_pipe);
		if (wet) {
			ath11k_eww(ab, "faiwed to wequest iwq %d: %d\n",
				   iwq_idx, wet);
			wetuwn wet;
		}

		ab->iwq_num[iwq_idx] = iwq;
		msi_data_idx++;

		ath11k_pcic_ce_iwq_disabwe(ab, i);
	}

	wet = ath11k_pcic_ext_iwq_config(ab);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_pcic_config_iwq);

void ath11k_pcic_ce_iwqs_enabwe(stwuct ath11k_base *ab)
{
	int i;

	set_bit(ATH11K_FWAG_CE_IWQ_ENABWED, &ab->dev_fwags);

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;
		ath11k_pcic_ce_iwq_enabwe(ab, i);
	}
}
EXPOWT_SYMBOW(ath11k_pcic_ce_iwqs_enabwe);

static void ath11k_pcic_kiww_taskwets(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		stwuct ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW)
			continue;

		taskwet_kiww(&ce_pipe->intw_tq);
	}
}

void ath11k_pcic_ce_iwq_disabwe_sync(stwuct ath11k_base *ab)
{
	ath11k_pcic_ce_iwqs_disabwe(ab);
	ath11k_pcic_sync_ce_iwqs(ab);
	ath11k_pcic_kiww_taskwets(ab);
}
EXPOWT_SYMBOW(ath11k_pcic_ce_iwq_disabwe_sync);

void ath11k_pcic_stop(stwuct ath11k_base *ab)
{
	ath11k_pcic_ce_iwq_disabwe_sync(ab);
	ath11k_ce_cweanup_pipes(ab);
}
EXPOWT_SYMBOW(ath11k_pcic_stop);

int ath11k_pcic_stawt(stwuct ath11k_base *ab)
{
	set_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags);

	ath11k_pcic_ce_iwqs_enabwe(ab);
	ath11k_ce_wx_post_buf(ab);

	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_pcic_stawt);

int ath11k_pcic_map_sewvice_to_pipe(stwuct ath11k_base *ab, u16 sewvice_id,
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
EXPOWT_SYMBOW(ath11k_pcic_map_sewvice_to_pipe);

int ath11k_pcic_wegistew_pci_ops(stwuct ath11k_base *ab,
				 const stwuct ath11k_pci_ops *pci_ops)
{
	if (!pci_ops)
		wetuwn 0;

	/* Wetuwn ewwow if mandatowy pci_ops cawwbacks awe missing */
	if (!pci_ops->get_msi_iwq || !pci_ops->window_wwite32 ||
	    !pci_ops->window_wead32)
		wetuwn -EINVAW;

	ab->pci.ops = pci_ops;
	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_pcic_wegistew_pci_ops);

void ath11k_pci_enabwe_ce_iwqs_except_wake_iwq(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW ||
		    i == ATH11K_PCI_CE_WAKE_IWQ)
			continue;
		ath11k_pcic_ce_iwq_enabwe(ab, i);
	}
}
EXPOWT_SYMBOW(ath11k_pci_enabwe_ce_iwqs_except_wake_iwq);

void ath11k_pci_disabwe_ce_iwqs_except_wake_iwq(stwuct ath11k_base *ab)
{
	int i;
	int iwq_idx;
	stwuct ath11k_ce_pipe *ce_pipe;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		ce_pipe = &ab->ce.ce_pipe[i];
		iwq_idx = ATH11K_PCI_IWQ_CE0_OFFSET + i;

		if (ath11k_ce_get_attw_fwags(ab, i) & CE_ATTW_DIS_INTW ||
		    i == ATH11K_PCI_CE_WAKE_IWQ)
			continue;

		disabwe_iwq_nosync(ab->iwq_num[iwq_idx]);
		synchwonize_iwq(ab->iwq_num[iwq_idx]);
		taskwet_kiww(&ce_pipe->intw_tq);
	}
}
EXPOWT_SYMBOW(ath11k_pci_disabwe_ce_iwqs_except_wake_iwq);
