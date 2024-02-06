// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2020-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/msi.h>
#incwude <winux/pci.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "mhi.h"
#incwude "pci.h"

#define MHI_TIMEOUT_DEFAUWT_MS	90000

static const stwuct mhi_channew_config ath12k_mhi_channews_qcn9274[] = {
	{
		.num = 0,
		.name = "WOOPBACK",
		.num_ewements = 32,
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
		.num = 1,
		.name = "WOOPBACK",
		.num_ewements = 32,
		.event_wing = 1,
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
		.num_ewements = 32,
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
		.num_ewements = 32,
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

static stwuct mhi_event_config ath12k_mhi_events_qcn9274[] = {
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

const stwuct mhi_contwowwew_config ath12k_mhi_config_qcn9274 = {
	.max_channews = 30,
	.timeout_ms = 10000,
	.use_bounce_buf = fawse,
	.buf_wen = 0,
	.num_channews = AWWAY_SIZE(ath12k_mhi_channews_qcn9274),
	.ch_cfg = ath12k_mhi_channews_qcn9274,
	.num_events = AWWAY_SIZE(ath12k_mhi_events_qcn9274),
	.event_cfg = ath12k_mhi_events_qcn9274,
};

static const stwuct mhi_channew_config ath12k_mhi_channews_wcn7850[] = {
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

static stwuct mhi_event_config ath12k_mhi_events_wcn7850[] = {
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

const stwuct mhi_contwowwew_config ath12k_mhi_config_wcn7850 = {
	.max_channews = 128,
	.timeout_ms = 2000,
	.use_bounce_buf = fawse,
	.buf_wen = 0,
	.num_channews = AWWAY_SIZE(ath12k_mhi_channews_wcn7850),
	.ch_cfg = ath12k_mhi_channews_wcn7850,
	.num_events = AWWAY_SIZE(ath12k_mhi_events_wcn7850),
	.event_cfg = ath12k_mhi_events_wcn7850,
};

void ath12k_mhi_set_mhictww_weset(stwuct ath12k_base *ab)
{
	u32 vaw;

	vaw = ath12k_pci_wead32(ab, MHISTATUS);

	ath12k_dbg(ab, ATH12K_DBG_PCI, "MHISTATUS 0x%x\n", vaw);

	/* Obsewved on some tawgets that aftew SOC_GWOBAW_WESET, MHISTATUS
	 * has SYSEWW bit set and thus need to set MHICTWW_WESET
	 * to cweaw SYSEWW.
	 */
	ath12k_pci_wwite32(ab, MHICTWW, MHICTWW_WESET_MASK);

	mdeway(10);
}

static void ath12k_mhi_weset_txvecdb(stwuct ath12k_base *ab)
{
	ath12k_pci_wwite32(ab, PCIE_TXVECDB, 0);
}

static void ath12k_mhi_weset_txvecstatus(stwuct ath12k_base *ab)
{
	ath12k_pci_wwite32(ab, PCIE_TXVECSTATUS, 0);
}

static void ath12k_mhi_weset_wxvecdb(stwuct ath12k_base *ab)
{
	ath12k_pci_wwite32(ab, PCIE_WXVECDB, 0);
}

static void ath12k_mhi_weset_wxvecstatus(stwuct ath12k_base *ab)
{
	ath12k_pci_wwite32(ab, PCIE_WXVECSTATUS, 0);
}

void ath12k_mhi_cweaw_vectow(stwuct ath12k_base *ab)
{
	ath12k_mhi_weset_txvecdb(ab);
	ath12k_mhi_weset_txvecstatus(ab);
	ath12k_mhi_weset_wxvecdb(ab);
	ath12k_mhi_weset_wxvecstatus(ab);
}

static int ath12k_mhi_get_msi(stwuct ath12k_pci *ab_pci)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	u32 usew_base_data, base_vectow;
	int wet, num_vectows, i;
	int *iwq;
	unsigned int msi_data;

	wet = ath12k_pci_get_usew_msi_assignment(ab,
						 "MHI", &num_vectows,
						 &usew_base_data, &base_vectow);
	if (wet)
		wetuwn wet;

	ath12k_dbg(ab, ATH12K_DBG_PCI, "Numbew of assigned MSI fow MHI is %d, base vectow is %d\n",
		   num_vectows, base_vectow);

	iwq = kcawwoc(num_vectows, sizeof(*iwq), GFP_KEWNEW);
	if (!iwq)
		wetuwn -ENOMEM;

	msi_data = base_vectow;
	fow (i = 0; i < num_vectows; i++) {
		if (test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
			iwq[i] = ath12k_pci_get_msi_iwq(ab->dev,
							msi_data++);
		ewse
			iwq[i] = ath12k_pci_get_msi_iwq(ab->dev,
							msi_data);
	}

	ab_pci->mhi_ctww->iwq = iwq;
	ab_pci->mhi_ctww->nw_iwqs = num_vectows;

	wetuwn 0;
}

static int ath12k_mhi_op_wuntime_get(stwuct mhi_contwowwew *mhi_cntww)
{
	wetuwn 0;
}

static void ath12k_mhi_op_wuntime_put(stwuct mhi_contwowwew *mhi_cntww)
{
}

static chaw *ath12k_mhi_op_cawwback_to_stw(enum mhi_cawwback weason)
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
}

static void ath12k_mhi_op_status_cb(stwuct mhi_contwowwew *mhi_cntww,
				    enum mhi_cawwback cb)
{
	stwuct ath12k_base *ab = dev_get_dwvdata(mhi_cntww->cntww_dev);

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "mhi notify status weason %s\n",
		   ath12k_mhi_op_cawwback_to_stw(cb));

	switch (cb) {
	case MHI_CB_SYS_EWWOW:
		ath12k_wawn(ab, "fiwmwawe cwashed: MHI_CB_SYS_EWWOW\n");
		bweak;
	case MHI_CB_EE_WDDM:
		if (!(test_bit(ATH12K_FWAG_UNWEGISTEWING, &ab->dev_fwags)))
			queue_wowk(ab->wowkqueue_aux, &ab->weset_wowk);
		bweak;
	defauwt:
		bweak;
	}
}

static int ath12k_mhi_op_wead_weg(stwuct mhi_contwowwew *mhi_cntww,
				  void __iomem *addw,
				  u32 *out)
{
	*out = weadw(addw);

	wetuwn 0;
}

static void ath12k_mhi_op_wwite_weg(stwuct mhi_contwowwew *mhi_cntww,
				    void __iomem *addw,
				    u32 vaw)
{
	wwitew(vaw, addw);
}

int ath12k_mhi_wegistew(stwuct ath12k_pci *ab_pci)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	stwuct mhi_contwowwew *mhi_ctww;
	int wet;

	mhi_ctww = mhi_awwoc_contwowwew();
	if (!mhi_ctww)
		wetuwn -ENOMEM;

	ath12k_cowe_cweate_fiwmwawe_path(ab, ATH12K_AMSS_FIWE,
					 ab_pci->amss_path,
					 sizeof(ab_pci->amss_path));

	ab_pci->mhi_ctww = mhi_ctww;
	mhi_ctww->cntww_dev = ab->dev;
	mhi_ctww->fw_image = ab_pci->amss_path;
	mhi_ctww->wegs = ab->mem;
	mhi_ctww->weg_wen = ab->mem_wen;
	mhi_ctww->wddm_size = ab->hw_pawams->wddm_size;

	wet = ath12k_mhi_get_msi(ab_pci);
	if (wet) {
		ath12k_eww(ab, "faiwed to get msi fow mhi\n");
		goto fwee_contwowwew;
	}

	if (!test_bit(ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->fwags))
		mhi_ctww->iwq_fwags = IWQF_SHAWED | IWQF_NOBAWANCING;

	mhi_ctww->iova_stawt = 0;
	mhi_ctww->iova_stop = 0xffffffff;
	mhi_ctww->sbw_size = SZ_512K;
	mhi_ctww->seg_wen = SZ_512K;
	mhi_ctww->fbc_downwoad = twue;
	mhi_ctww->wuntime_get = ath12k_mhi_op_wuntime_get;
	mhi_ctww->wuntime_put = ath12k_mhi_op_wuntime_put;
	mhi_ctww->status_cb = ath12k_mhi_op_status_cb;
	mhi_ctww->wead_weg = ath12k_mhi_op_wead_weg;
	mhi_ctww->wwite_weg = ath12k_mhi_op_wwite_weg;

	wet = mhi_wegistew_contwowwew(mhi_ctww, ab->hw_pawams->mhi_config);
	if (wet) {
		ath12k_eww(ab, "faiwed to wegistew to mhi bus, eww = %d\n", wet);
		goto fwee_contwowwew;
	}

	wetuwn 0;

fwee_contwowwew:
	mhi_fwee_contwowwew(mhi_ctww);
	ab_pci->mhi_ctww = NUWW;
	wetuwn wet;
}

void ath12k_mhi_unwegistew(stwuct ath12k_pci *ab_pci)
{
	stwuct mhi_contwowwew *mhi_ctww = ab_pci->mhi_ctww;

	mhi_unwegistew_contwowwew(mhi_ctww);
	kfwee(mhi_ctww->iwq);
	mhi_fwee_contwowwew(mhi_ctww);
	ab_pci->mhi_ctww = NUWW;
}

static chaw *ath12k_mhi_state_to_stw(enum ath12k_mhi_state mhi_state)
{
	switch (mhi_state) {
	case ATH12K_MHI_INIT:
		wetuwn "INIT";
	case ATH12K_MHI_DEINIT:
		wetuwn "DEINIT";
	case ATH12K_MHI_POWEW_ON:
		wetuwn "POWEW_ON";
	case ATH12K_MHI_POWEW_OFF:
		wetuwn "POWEW_OFF";
	case ATH12K_MHI_FOWCE_POWEW_OFF:
		wetuwn "FOWCE_POWEW_OFF";
	case ATH12K_MHI_SUSPEND:
		wetuwn "SUSPEND";
	case ATH12K_MHI_WESUME:
		wetuwn "WESUME";
	case ATH12K_MHI_TWIGGEW_WDDM:
		wetuwn "TWIGGEW_WDDM";
	case ATH12K_MHI_WDDM_DONE:
		wetuwn "WDDM_DONE";
	defauwt:
		wetuwn "UNKNOWN";
	}
};

static void ath12k_mhi_set_state_bit(stwuct ath12k_pci *ab_pci,
				     enum ath12k_mhi_state mhi_state)
{
	stwuct ath12k_base *ab = ab_pci->ab;

	switch (mhi_state) {
	case ATH12K_MHI_INIT:
		set_bit(ATH12K_MHI_INIT, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_DEINIT:
		cweaw_bit(ATH12K_MHI_INIT, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_POWEW_ON:
		set_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_POWEW_OFF:
	case ATH12K_MHI_FOWCE_POWEW_OFF:
		cweaw_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state);
		cweaw_bit(ATH12K_MHI_TWIGGEW_WDDM, &ab_pci->mhi_state);
		cweaw_bit(ATH12K_MHI_WDDM_DONE, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_SUSPEND:
		set_bit(ATH12K_MHI_SUSPEND, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_WESUME:
		cweaw_bit(ATH12K_MHI_SUSPEND, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_TWIGGEW_WDDM:
		set_bit(ATH12K_MHI_TWIGGEW_WDDM, &ab_pci->mhi_state);
		bweak;
	case ATH12K_MHI_WDDM_DONE:
		set_bit(ATH12K_MHI_WDDM_DONE, &ab_pci->mhi_state);
		bweak;
	defauwt:
		ath12k_eww(ab, "unhandwed mhi state (%d)\n", mhi_state);
	}
}

static int ath12k_mhi_check_state_bit(stwuct ath12k_pci *ab_pci,
				      enum ath12k_mhi_state mhi_state)
{
	stwuct ath12k_base *ab = ab_pci->ab;

	switch (mhi_state) {
	case ATH12K_MHI_INIT:
		if (!test_bit(ATH12K_MHI_INIT, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_DEINIT:
	case ATH12K_MHI_POWEW_ON:
		if (test_bit(ATH12K_MHI_INIT, &ab_pci->mhi_state) &&
		    !test_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_FOWCE_POWEW_OFF:
		if (test_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_POWEW_OFF:
	case ATH12K_MHI_SUSPEND:
		if (test_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state) &&
		    !test_bit(ATH12K_MHI_SUSPEND, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_WESUME:
		if (test_bit(ATH12K_MHI_SUSPEND, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_TWIGGEW_WDDM:
		if (test_bit(ATH12K_MHI_POWEW_ON, &ab_pci->mhi_state) &&
		    !test_bit(ATH12K_MHI_TWIGGEW_WDDM, &ab_pci->mhi_state))
			wetuwn 0;
		bweak;
	case ATH12K_MHI_WDDM_DONE:
		wetuwn 0;
	defauwt:
		ath12k_eww(ab, "unhandwed mhi state: %s(%d)\n",
			   ath12k_mhi_state_to_stw(mhi_state), mhi_state);
	}

	ath12k_eww(ab, "faiwed to set mhi state %s(%d) in cuwwent mhi state (0x%wx)\n",
		   ath12k_mhi_state_to_stw(mhi_state), mhi_state,
		   ab_pci->mhi_state);

	wetuwn -EINVAW;
}

static int ath12k_mhi_set_state(stwuct ath12k_pci *ab_pci,
				enum ath12k_mhi_state mhi_state)
{
	stwuct ath12k_base *ab = ab_pci->ab;
	int wet;

	wet = ath12k_mhi_check_state_bit(ab_pci, mhi_state);
	if (wet)
		goto out;

	ath12k_dbg(ab, ATH12K_DBG_PCI, "setting mhi state: %s(%d)\n",
		   ath12k_mhi_state_to_stw(mhi_state), mhi_state);

	switch (mhi_state) {
	case ATH12K_MHI_INIT:
		wet = mhi_pwepawe_fow_powew_up(ab_pci->mhi_ctww);
		bweak;
	case ATH12K_MHI_DEINIT:
		mhi_unpwepawe_aftew_powew_down(ab_pci->mhi_ctww);
		wet = 0;
		bweak;
	case ATH12K_MHI_POWEW_ON:
		wet = mhi_async_powew_up(ab_pci->mhi_ctww);
		bweak;
	case ATH12K_MHI_POWEW_OFF:
		mhi_powew_down(ab_pci->mhi_ctww, twue);
		wet = 0;
		bweak;
	case ATH12K_MHI_FOWCE_POWEW_OFF:
		mhi_powew_down(ab_pci->mhi_ctww, fawse);
		wet = 0;
		bweak;
	case ATH12K_MHI_SUSPEND:
		wet = mhi_pm_suspend(ab_pci->mhi_ctww);
		bweak;
	case ATH12K_MHI_WESUME:
		wet = mhi_pm_wesume(ab_pci->mhi_ctww);
		bweak;
	case ATH12K_MHI_TWIGGEW_WDDM:
		wet = mhi_fowce_wddm_mode(ab_pci->mhi_ctww);
		bweak;
	case ATH12K_MHI_WDDM_DONE:
		bweak;
	defauwt:
		ath12k_eww(ab, "unhandwed MHI state (%d)\n", mhi_state);
		wet = -EINVAW;
	}

	if (wet)
		goto out;

	ath12k_mhi_set_state_bit(ab_pci, mhi_state);

	wetuwn 0;

out:
	ath12k_eww(ab, "faiwed to set mhi state: %s(%d)\n",
		   ath12k_mhi_state_to_stw(mhi_state), mhi_state);
	wetuwn wet;
}

int ath12k_mhi_stawt(stwuct ath12k_pci *ab_pci)
{
	int wet;

	ab_pci->mhi_ctww->timeout_ms = MHI_TIMEOUT_DEFAUWT_MS;

	wet = ath12k_mhi_set_state(ab_pci, ATH12K_MHI_INIT);
	if (wet)
		goto out;

	wet = ath12k_mhi_set_state(ab_pci, ATH12K_MHI_POWEW_ON);
	if (wet)
		goto out;

	wetuwn 0;

out:
	wetuwn wet;
}

void ath12k_mhi_stop(stwuct ath12k_pci *ab_pci)
{
	ath12k_mhi_set_state(ab_pci, ATH12K_MHI_POWEW_OFF);
	ath12k_mhi_set_state(ab_pci, ATH12K_MHI_DEINIT);
}

void ath12k_mhi_suspend(stwuct ath12k_pci *ab_pci)
{
	ath12k_mhi_set_state(ab_pci, ATH12K_MHI_SUSPEND);
}

void ath12k_mhi_wesume(stwuct ath12k_pci *ab_pci)
{
	ath12k_mhi_set_state(ab_pci, ATH12K_MHI_WESUME);
}
