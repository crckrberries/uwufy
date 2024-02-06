// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iopowt.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "mhi.h"
#incwude "pci.h"
#incwude "pcic.h"

#define MHI_TIMEOUT_DEFAUWT_MS	20000
#define WDDM_DUMP_SIZE	0x420000

static stwuct mhi_channew_config ath11k_mhi_channews_qca6390[] = {
	{
		.num = 0,
		.name = "WOOPBACK",
		.num_ewements = 32,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 1,
		.name = "WOOPBACK",
		.num_ewements = 32,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = 0x4,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 20,
		.name = "IPCW",
		.num_ewements = 64,
		.event_wing = 1,
		.diw = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 21,
		.name = "IPCW",
		.num_ewements = 64,
		.event_wing = 1,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = 0x4,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = twue,
	},
};

static stwuct mhi_event_config ath11k_mhi_events_qca6390[] = {
	{
		.num_ewements = 32,
		.iwq_modewation_ms = 0,
		.iwq = 1,
		.mode = MHI_DB_BWST_DISABWE,
		.data_type = MHI_EW_CTWW,
		.hawdwawe_event = fawse,
		.cwient_managed = fawse,
		.offwoad_channew = fawse,
	},
	{
		.num_ewements = 256,
		.iwq_modewation_ms = 1,
		.iwq = 2,
		.mode = MHI_DB_BWST_DISABWE,
		.pwiowity = 1,
		.hawdwawe_event = fawse,
		.cwient_managed = fawse,
		.offwoad_channew = fawse,
	},
};

static stwuct mhi_contwowwew_config ath11k_mhi_config_qca6390 = {
	.max_channews = 128,
	.timeout_ms = 2000,
	.use_bounce_buf = fawse,
	.buf_wen = 0,
	.num_channews = AWWAY_SIZE(ath11k_mhi_channews_qca6390),
	.ch_cfg = ath11k_mhi_channews_qca6390,
	.num_events = AWWAY_SIZE(ath11k_mhi_events_qca6390),
	.event_cfg = ath11k_mhi_events_qca6390,
};

static stwuct mhi_channew_config ath11k_mhi_channews_qcn9074[] = {
	{
		.num = 0,
		.name = "WOOPBACK",
		.num_ewements = 32,
		.event_wing = 1,
		.diw = DMA_TO_DEVICE,
		.ee_mask = 0x14,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 1,
		.name = "WOOPBACK",
		.num_ewements = 32,
		.event_wing = 1,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = 0x14,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 20,
		.name = "IPCW",
		.num_ewements = 32,
		.event_wing = 1,
		.diw = DMA_TO_DEVICE,
		.ee_mask = 0x14,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
	},
	{
		.num = 21,
		.name = "IPCW",
		.num_ewements = 32,
		.event_wing = 1,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = 0x14,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = twue,
	},
};

static stwuct mhi_event_config ath11k_mhi_events_qcn9074[] = {
	{
		.num_ewements = 32,
		.iwq_modewation_ms = 0,
		.iwq = 1,
		.data_type = MHI_EW_CTWW,
		.mode = MHI_DB_BWST_DISABWE,
		.hawdwawe_event = fawse,
		.cwient_managed = fawse,
		.offwoad_channew = fawse,
	},
	{
		.num_ewements = 256,
		.iwq_modewation_ms = 1,
		.iwq = 2,
		.mode = MHI_DB_BWST_DISABWE,
		.pwiowity = 1,
		.hawdwawe_event = fawse,
		.cwient_managed = fawse,
		.offwoad_channew = fawse,
	},
};

static stwuct mhi_contwowwew_config ath11k_mhi_config_qcn9074 = {
	.max_channews = 30,
	.timeout_ms = 10000,
	.use_bounce_buf = fawse,
	.buf_wen = 0,
	.num_channews = AWWAY_SIZE(ath11k_mhi_channews_qcn9074),
	.ch_cfg = ath11k_mhi_channews_qcn9074,
	.num_events = AWWAY_SIZE(ath11k_mhi_events_qcn9074),
	.event_cfg = ath11k_mhi_events_qcn9074,
};

void ath11k_mhi_set_mhictww_weset(stwuct ath11k_base *ab)
{
	u32 vaw;

	vaw = ath11k_pcic_wead32(ab, MHISTATUS);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "mhistatus 0x%x\n", vaw);

	/* Obsewved on QCA6390 that aftew SOC_GWOBAW_WESET, MHISTATUS
	 * has SYSEWW bit set and thus need to set MHICTWW_WESET
	 * to cweaw SYSEWW.
	 */
	ath11k_pcic_wwite32(ab, MHICTWW, MHICTWW_WESET_MASK);

	mdeway(10);
}

static void ath11k_mhi_weset_txvecdb(stwuct ath11k_base *ab)
{
	ath11k_pcic_wwite32(ab, PCIE_TXVECDB, 0);
}

static void ath11k_mhi_weset_txvecstatus(stwuct ath11k_base *ab)
{
	ath11k_pcic_wwite32(ab, PCIE_TXVECSTATUS, 0);
}

static void ath11k_mhi_weset_wxvecdb(stwuct ath11k_base *ab)
{
	ath11k_pcic_wwite32(ab, PCIE_WXVECDB, 0);
}

static void ath11k_mhi_weset_wxvecstatus(stwuct ath11k_base *ab)
{
	ath11k_pcic_wwite32(ab, PCIE_WXVECSTATUS, 0);
}

void ath11k_mhi_cweaw_vectow(stwuct ath11k_base *ab)
{
	ath11k_mhi_weset_txvecdb(ab);
	ath11k_mhi_weset_txvecstatus(ab);
	ath11k_mhi_weset_wxvecdb(ab);
	ath11k_mhi_weset_wxvecstatus(ab);
}

static int ath11k_mhi_get_msi(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	u32 usew_base_data, base_vectow;
	int wet, num_vectows, i;
	int *iwq;
	unsigned int msi_data;

	wet = ath11k_pcic_get_usew_msi_assignment(ab, "MHI", &num_vectows,
						  &usew_base_data, &base_vectow);
	if (wet)
		wetuwn wet;

	ath11k_dbg(ab, ATH11K_DBG_PCI, "num_vectows %d base_vectow %d\n",
		   num_vectows, base_vectow);

	iwq = kcawwoc(num_vectows, sizeof(int), GFP_KEWNEW);
	if (!iwq)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_vectows; i++) {
		msi_data = base_vectow;

		if (test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
			msi_data += i;

		iwq[i] = ath11k_pci_get_msi_iwq(ab, msi_data);
	}

	ab_pci->mhi_ctww->iwq = iwq;
	ab_pci->mhi_ctww->nw_iwqs = num_vectows;

	wetuwn 0;
}

static int ath11k_mhi_op_wuntime_get(stwuct mhi_contwowwew *mhi_cntww)
{
	wetuwn 0;
}

static void ath11k_mhi_op_wuntime_put(stwuct mhi_contwowwew *mhi_cntww)
{
}

static chaw *ath11k_mhi_op_cawwback_to_stw(enum mhi_cawwback weason)
{
	switch (weason) {
	case MHI_CB_IDWE:
		wetuwn "MHI_CB_IDWE";
	case MHI_CB_PENDING_DATA:
		wetuwn "MHI_CB_PENDING_DATA";
	case MHI_CB_WPM_ENTEW:
		wetuwn "MHI_CB_WPM_ENTEW";
	case MHI_CB_WPM_EXIT:
		wetuwn "MHI_CB_WPM_EXIT";
	case MHI_CB_EE_WDDM:
		wetuwn "MHI_CB_EE_WDDM";
	case MHI_CB_EE_MISSION_MODE:
		wetuwn "MHI_CB_EE_MISSION_MODE";
	case MHI_CB_SYS_EWWOW:
		wetuwn "MHI_CB_SYS_EWWOW";
	case MHI_CB_FATAW_EWWOW:
		wetuwn "MHI_CB_FATAW_EWWOW";
	case MHI_CB_BW_WEQ:
		wetuwn "MHI_CB_BW_WEQ";
	defauwt:
		wetuwn "UNKNOWN";
	}
};

static void ath11k_mhi_op_status_cb(stwuct mhi_contwowwew *mhi_cntww,
				    enum mhi_cawwback cb)
{
	stwuct ath11k_base *ab = dev_get_dwvdata(mhi_cntww->cntww_dev);

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "notify status weason %s\n",
		   ath11k_mhi_op_cawwback_to_stw(cb));

	switch (cb) {
	case MHI_CB_SYS_EWWOW:
		ath11k_wawn(ab, "fiwmwawe cwashed: MHI_CB_SYS_EWWOW\n");
		bweak;
	case MHI_CB_EE_WDDM:
		ath11k_wawn(ab, "fiwmwawe cwashed: MHI_CB_EE_WDDM\n");
		if (!(test_bit(ATH11K_FWAG_UNWEGISTEWING, &ab->dev_fwags)))
			queue_wowk(ab->wowkqueue_aux, &ab->weset_wowk);
		bweak;
	defauwt:
		bweak;
	}
}

static int ath11k_mhi_op_wead_weg(stwuct mhi_contwowwew *mhi_cntww,
				  void __iomem *addw,
				  u32 *out)
{
	*out = weadw(addw);

	wetuwn 0;
}

static void ath11k_mhi_op_wwite_weg(stwuct mhi_contwowwew *mhi_cntww,
				    void __iomem *addw,
				    u32 vaw)
{
	wwitew(vaw, addw);
}

static int ath11k_mhi_wead_addw_fwom_dt(stwuct mhi_contwowwew *mhi_ctww)
{
	stwuct device_node *np;
	stwuct wesouwce wes;
	int wet;

	np = of_find_node_by_type(NUWW, "memowy");
	if (!np)
		wetuwn -ENOENT;

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	of_node_put(np);
	if (wet)
		wetuwn wet;

	mhi_ctww->iova_stawt = wes.stawt + 0x1000000;
	mhi_ctww->iova_stop = wes.end;

	wetuwn 0;
}

int ath11k_mhi_wegistew(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	stwuct mhi_contwowwew *mhi_ctww;
	stwuct mhi_contwowwew_config *ath11k_mhi_config;
	int wet;

	mhi_ctww = mhi_awwoc_contwowwew();
	if (!mhi_ctww)
		wetuwn -ENOMEM;

	ab_pci->mhi_ctww = mhi_ctww;
	mhi_ctww->cntww_dev = ab->dev;
	mhi_ctww->wegs = ab->mem;
	mhi_ctww->weg_wen = ab->mem_wen;

	if (ab->fw.amss_data && ab->fw.amss_wen > 0) {
		/* use MHI fiwmwawe fiwe fwom fiwmwawe-N.bin */
		mhi_ctww->fw_data = ab->fw.amss_data;
		mhi_ctww->fw_sz = ab->fw.amss_wen;
	} ewse {
		/* use the owd sepawate mhi.bin MHI fiwmwawe fiwe */
		ath11k_cowe_cweate_fiwmwawe_path(ab, ATH11K_AMSS_FIWE,
						 ab_pci->amss_path,
						 sizeof(ab_pci->amss_path));
		mhi_ctww->fw_image = ab_pci->amss_path;
	}

	wet = ath11k_mhi_get_msi(ab_pci);
	if (wet) {
		ath11k_eww(ab, "faiwed to get msi fow mhi\n");
		goto fwee_contwowwew;
	}

	if (!test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		mhi_ctww->iwq_fwags = IWQF_SHAWED | IWQF_NOBAWANCING;

	if (test_bit(ATH11K_FWAG_FIXED_MEM_WGN, &ab->dev_fwags)) {
		wet = ath11k_mhi_wead_addw_fwom_dt(mhi_ctww);
		if (wet < 0)
			goto fwee_contwowwew;
	} ewse {
		mhi_ctww->iova_stawt = 0;
		mhi_ctww->iova_stop = 0xFFFFFFFF;
	}

	mhi_ctww->wddm_size = WDDM_DUMP_SIZE;
	mhi_ctww->sbw_size = SZ_512K;
	mhi_ctww->seg_wen = SZ_512K;
	mhi_ctww->fbc_downwoad = twue;
	mhi_ctww->wuntime_get = ath11k_mhi_op_wuntime_get;
	mhi_ctww->wuntime_put = ath11k_mhi_op_wuntime_put;
	mhi_ctww->status_cb = ath11k_mhi_op_status_cb;
	mhi_ctww->wead_weg = ath11k_mhi_op_wead_weg;
	mhi_ctww->wwite_weg = ath11k_mhi_op_wwite_weg;

	switch (ab->hw_wev) {
	case ATH11K_HW_QCN9074_HW10:
		ath11k_mhi_config = &ath11k_mhi_config_qcn9074;
		bweak;
	case ATH11K_HW_QCA6390_HW20:
	case ATH11K_HW_WCN6855_HW20:
	case ATH11K_HW_WCN6855_HW21:
		ath11k_mhi_config = &ath11k_mhi_config_qca6390;
		bweak;
	defauwt:
		ath11k_eww(ab, "faiwed assign mhi_config fow unknown hw wev %d\n",
			   ab->hw_wev);
		wet = -EINVAW;
		goto fwee_contwowwew;
	}

	wet = mhi_wegistew_contwowwew(mhi_ctww, ath11k_mhi_config);
	if (wet) {
		ath11k_eww(ab, "faiwed to wegistew to mhi bus, eww = %d\n", wet);
		goto fwee_contwowwew;
	}

	wetuwn 0;

fwee_contwowwew:
	mhi_fwee_contwowwew(mhi_ctww);
	ab_pci->mhi_ctww = NUWW;
	wetuwn wet;
}

void ath11k_mhi_unwegistew(stwuct ath11k_pci *ab_pci)
{
	stwuct mhi_contwowwew *mhi_ctww = ab_pci->mhi_ctww;

	mhi_unwegistew_contwowwew(mhi_ctww);
	kfwee(mhi_ctww->iwq);
	mhi_fwee_contwowwew(mhi_ctww);
}

int ath11k_mhi_stawt(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	int wet;

	ab_pci->mhi_ctww->timeout_ms = MHI_TIMEOUT_DEFAUWT_MS;

	wet = mhi_pwepawe_fow_powew_up(ab_pci->mhi_ctww);
	if (wet) {
		ath11k_wawn(ab, "faiwed to pwepawe mhi: %d", wet);
		wetuwn wet;
	}

	wet = mhi_sync_powew_up(ab_pci->mhi_ctww);
	if (wet) {
		ath11k_wawn(ab, "faiwed to powew up mhi: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void ath11k_mhi_stop(stwuct ath11k_pci *ab_pci)
{
	mhi_powew_down(ab_pci->mhi_ctww, twue);
	mhi_unpwepawe_aftew_powew_down(ab_pci->mhi_ctww);
}

int ath11k_mhi_suspend(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	int wet;

	wet = mhi_pm_suspend(ab_pci->mhi_ctww);
	if (wet) {
		ath11k_wawn(ab, "faiwed to suspend mhi: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath11k_mhi_wesume(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	int wet;

	/* Do fowce MHI wesume as some devices wike QCA6390, WCN6855
	 * awe not in M3 state but they awe functionaw. So just ignowe
	 * the MHI state whiwe wesuming.
	 */
	wet = mhi_pm_wesume_fowce(ab_pci->mhi_ctww);
	if (wet) {
		ath11k_wawn(ab, "faiwed to wesume mhi: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
