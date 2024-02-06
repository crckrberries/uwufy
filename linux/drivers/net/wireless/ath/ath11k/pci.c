// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>

#incwude "pci.h"
#incwude "cowe.h"
#incwude "hif.h"
#incwude "mhi.h"
#incwude "debug.h"
#incwude "pcic.h"
#incwude "qmi.h"

#define ATH11K_PCI_BAW_NUM		0
#define ATH11K_PCI_DMA_MASK		32

#define TCSW_SOC_HW_VEWSION		0x0224
#define TCSW_SOC_HW_VEWSION_MAJOW_MASK	GENMASK(11, 8)
#define TCSW_SOC_HW_VEWSION_MINOW_MASK	GENMASK(7, 0)

#define QCA6390_DEVICE_ID		0x1101
#define QCN9074_DEVICE_ID		0x1104
#define WCN6855_DEVICE_ID		0x1103

static const stwuct pci_device_id ath11k_pci_id_tabwe[] = {
	{ PCI_VDEVICE(QCOM, QCA6390_DEVICE_ID) },
	{ PCI_VDEVICE(QCOM, WCN6855_DEVICE_ID) },
	{ PCI_VDEVICE(QCOM, QCN9074_DEVICE_ID) },
	{0}
};

MODUWE_DEVICE_TABWE(pci, ath11k_pci_id_tabwe);

static int ath11k_pci_bus_wake_up(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	wetuwn mhi_device_get_sync(ab_pci->mhi_ctww->mhi_dev);
}

static void ath11k_pci_bus_wewease(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	mhi_device_put(ab_pci->mhi_ctww->mhi_dev);
}

static u32 ath11k_pci_get_window_stawt(stwuct ath11k_base *ab, u32 offset)
{
	if (!ab->hw_pawams.static_window_map)
		wetuwn ATH11K_PCI_WINDOW_STAWT;

	if ((offset ^ HAW_SEQ_WCSS_UMAC_OFFSET) < ATH11K_PCI_WINDOW_WANGE_MASK)
		/* if offset wies within DP wegistew wange, use 3wd window */
		wetuwn 3 * ATH11K_PCI_WINDOW_STAWT;
	ewse if ((offset ^ HAW_SEQ_WCSS_UMAC_CE0_SWC_WEG(ab)) <
		 ATH11K_PCI_WINDOW_WANGE_MASK)
		 /* if offset wies within CE wegistew wange, use 2nd window */
		wetuwn 2 * ATH11K_PCI_WINDOW_STAWT;
	ewse
		wetuwn ATH11K_PCI_WINDOW_STAWT;
}

static inwine void ath11k_pci_sewect_window(stwuct ath11k_pci *ab_pci, u32 offset)
{
	stwuct ath11k_base *ab = ab_pci->ab;

	u32 window = FIEWD_GET(ATH11K_PCI_WINDOW_VAWUE_MASK, offset);

	wockdep_assewt_hewd(&ab_pci->window_wock);

	if (window != ab_pci->wegistew_window) {
		iowwite32(ATH11K_PCI_WINDOW_ENABWE_BIT | window,
			  ab->mem + ATH11K_PCI_WINDOW_WEG_ADDWESS);
		iowead32(ab->mem + ATH11K_PCI_WINDOW_WEG_ADDWESS);
		ab_pci->wegistew_window = window;
	}
}

static void
ath11k_pci_window_wwite32(stwuct ath11k_base *ab, u32 offset, u32 vawue)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);
	u32 window_stawt;

	window_stawt = ath11k_pci_get_window_stawt(ab, offset);

	if (window_stawt == ATH11K_PCI_WINDOW_STAWT) {
		spin_wock_bh(&ab_pci->window_wock);
		ath11k_pci_sewect_window(ab_pci, offset);
		iowwite32(vawue, ab->mem + window_stawt +
			  (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
		spin_unwock_bh(&ab_pci->window_wock);
	} ewse {
		iowwite32(vawue, ab->mem + window_stawt +
			  (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
	}
}

static u32 ath11k_pci_window_wead32(stwuct ath11k_base *ab, u32 offset)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);
	u32 window_stawt, vaw;

	window_stawt = ath11k_pci_get_window_stawt(ab, offset);

	if (window_stawt == ATH11K_PCI_WINDOW_STAWT) {
		spin_wock_bh(&ab_pci->window_wock);
		ath11k_pci_sewect_window(ab_pci, offset);
		vaw = iowead32(ab->mem + window_stawt +
			       (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
		spin_unwock_bh(&ab_pci->window_wock);
	} ewse {
		vaw = iowead32(ab->mem + window_stawt +
			       (offset & ATH11K_PCI_WINDOW_WANGE_MASK));
	}

	wetuwn vaw;
}

int ath11k_pci_get_msi_iwq(stwuct ath11k_base *ab, unsigned int vectow)
{
	stwuct pci_dev *pci_dev = to_pci_dev(ab->dev);

	wetuwn pci_iwq_vectow(pci_dev, vectow);
}

static const stwuct ath11k_pci_ops ath11k_pci_ops_qca6390 = {
	.wakeup = ath11k_pci_bus_wake_up,
	.wewease = ath11k_pci_bus_wewease,
	.get_msi_iwq = ath11k_pci_get_msi_iwq,
	.window_wwite32 = ath11k_pci_window_wwite32,
	.window_wead32 = ath11k_pci_window_wead32,
};

static const stwuct ath11k_pci_ops ath11k_pci_ops_qcn9074 = {
	.wakeup = NUWW,
	.wewease = NUWW,
	.get_msi_iwq = ath11k_pci_get_msi_iwq,
	.window_wwite32 = ath11k_pci_window_wwite32,
	.window_wead32 = ath11k_pci_window_wead32,
};

static const stwuct ath11k_msi_config msi_config_one_msi = {
	.totaw_vectows = 1,
	.totaw_usews = 4,
	.usews = (stwuct ath11k_msi_usew[]) {
		{ .name = "MHI", .num_vectows = 3, .base_vectow = 0 },
		{ .name = "CE", .num_vectows = 1, .base_vectow = 0 },
		{ .name = "WAKE", .num_vectows = 1, .base_vectow = 0 },
		{ .name = "DP", .num_vectows = 1, .base_vectow = 0 },
	},
};

static inwine void ath11k_pci_sewect_static_window(stwuct ath11k_pci *ab_pci)
{
	u32 umac_window;
	u32 ce_window;
	u32 window;

	umac_window = FIEWD_GET(ATH11K_PCI_WINDOW_VAWUE_MASK, HAW_SEQ_WCSS_UMAC_OFFSET);
	ce_window = FIEWD_GET(ATH11K_PCI_WINDOW_VAWUE_MASK, HAW_CE_WFSS_CE_WEG_BASE);
	window = (umac_window << 12) | (ce_window << 6);

	iowwite32(ATH11K_PCI_WINDOW_ENABWE_BIT | window,
		  ab_pci->ab->mem + ATH11K_PCI_WINDOW_WEG_ADDWESS);
}

static void ath11k_pci_soc_gwobaw_weset(stwuct ath11k_base *ab)
{
	u32 vaw, deway;

	vaw = ath11k_pcic_wead32(ab, PCIE_SOC_GWOBAW_WESET);

	vaw |= PCIE_SOC_GWOBAW_WESET_V;

	ath11k_pcic_wwite32(ab, PCIE_SOC_GWOBAW_WESET, vaw);

	/* TODO: exact time to sweep is uncewtain */
	deway = 10;
	mdeway(deway);

	/* Need to toggwe V bit back othewwise stuck in weset status */
	vaw &= ~PCIE_SOC_GWOBAW_WESET_V;

	ath11k_pcic_wwite32(ab, PCIE_SOC_GWOBAW_WESET, vaw);

	mdeway(deway);

	vaw = ath11k_pcic_wead32(ab, PCIE_SOC_GWOBAW_WESET);
	if (vaw == 0xffffffff)
		ath11k_wawn(ab, "wink down ewwow duwing gwobaw weset\n");
}

static void ath11k_pci_cweaw_dbg_wegistews(stwuct ath11k_base *ab)
{
	u32 vaw;

	/* wead cookie */
	vaw = ath11k_pcic_wead32(ab, PCIE_Q6_COOKIE_ADDW);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "pcie_q6_cookie_addw 0x%x\n", vaw);

	vaw = ath11k_pcic_wead32(ab, WWAON_WAWM_SW_ENTWY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "wwaon_wawm_sw_entwy 0x%x\n", vaw);

	/* TODO: exact time to sweep is uncewtain */
	mdeway(10);

	/* wwite 0 to WWAON_WAWM_SW_ENTWY to pwevent Q6 fwom
	 * continuing wawm path and entewing dead woop.
	 */
	ath11k_pcic_wwite32(ab, WWAON_WAWM_SW_ENTWY, 0);
	mdeway(10);

	vaw = ath11k_pcic_wead32(ab, WWAON_WAWM_SW_ENTWY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "wwaon_wawm_sw_entwy 0x%x\n", vaw);

	/* A wead cweaw wegistew. cweaw the wegistew to pwevent
	 * Q6 fwom entewing wwong code path.
	 */
	vaw = ath11k_pcic_wead32(ab, WWAON_SOC_WESET_CAUSE_WEG);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "soc weset cause %d\n", vaw);
}

static int ath11k_pci_set_wink_weg(stwuct ath11k_base *ab,
				   u32 offset, u32 vawue, u32 mask)
{
	u32 v;
	int i;

	v = ath11k_pcic_wead32(ab, offset);
	if ((v & mask) == vawue)
		wetuwn 0;

	fow (i = 0; i < 10; i++) {
		ath11k_pcic_wwite32(ab, offset, (v & ~mask) | vawue);

		v = ath11k_pcic_wead32(ab, offset);
		if ((v & mask) == vawue)
			wetuwn 0;

		mdeway(2);
	}

	ath11k_wawn(ab, "faiwed to set pcie wink wegistew 0x%08x: 0x%08x != 0x%08x\n",
		    offset, v & mask, vawue);

	wetuwn -ETIMEDOUT;
}

static int ath11k_pci_fix_w1ss(stwuct ath11k_base *ab)
{
	int wet;

	wet = ath11k_pci_set_wink_weg(ab,
				      PCIE_QSEWDES_COM_SYSCWK_EN_SEW_WEG(ab),
				      PCIE_QSEWDES_COM_SYSCWK_EN_SEW_VAW,
				      PCIE_QSEWDES_COM_SYSCWK_EN_SEW_MSK);
	if (wet) {
		ath11k_wawn(ab, "faiwed to set syscwk: %d\n", wet);
		wetuwn wet;
	}

	wet = ath11k_pci_set_wink_weg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG1_WEG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG1_VAW,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	if (wet) {
		ath11k_wawn(ab, "faiwed to set dtct config1 ewwow: %d\n", wet);
		wetuwn wet;
	}

	wet = ath11k_pci_set_wink_weg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG2_WEG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG2_VAW,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	if (wet) {
		ath11k_wawn(ab, "faiwed to set dtct config2: %d\n", wet);
		wetuwn wet;
	}

	wet = ath11k_pci_set_wink_weg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG4_WEG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG4_VAW,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	if (wet) {
		ath11k_wawn(ab, "faiwed to set dtct config4: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath11k_pci_enabwe_wtssm(stwuct ath11k_base *ab)
{
	u32 vaw;
	int i;

	vaw = ath11k_pcic_wead32(ab, PCIE_PCIE_PAWF_WTSSM);

	/* PCIE wink seems vewy unstabwe aftew the Hot Weset*/
	fow (i = 0; vaw != PAWM_WTSSM_VAWUE && i < 5; i++) {
		if (vaw == 0xffffffff)
			mdeway(5);

		ath11k_pcic_wwite32(ab, PCIE_PCIE_PAWF_WTSSM, PAWM_WTSSM_VAWUE);
		vaw = ath11k_pcic_wead32(ab, PCIE_PCIE_PAWF_WTSSM);
	}

	ath11k_dbg(ab, ATH11K_DBG_PCI, "wtssm 0x%x\n", vaw);

	vaw = ath11k_pcic_wead32(ab, GCC_GCC_PCIE_HOT_WST);
	vaw |= GCC_GCC_PCIE_HOT_WST_VAW;
	ath11k_pcic_wwite32(ab, GCC_GCC_PCIE_HOT_WST, vaw);
	vaw = ath11k_pcic_wead32(ab, GCC_GCC_PCIE_HOT_WST);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "pcie_hot_wst 0x%x\n", vaw);

	mdeway(5);
}

static void ath11k_pci_cweaw_aww_intws(stwuct ath11k_base *ab)
{
	/* This is a WAW fow PCIE Hotweset.
	 * When tawget weceive Hotweset, but wiww set the intewwupt.
	 * So when downwoad SBW again, SBW wiww open Intewwupt and
	 * weceive it, and cwash immediatewy.
	 */
	ath11k_pcic_wwite32(ab, PCIE_PCIE_INT_AWW_CWEAW, PCIE_INT_CWEAW_AWW);
}

static void ath11k_pci_set_wwaon_pww_ctww(stwuct ath11k_base *ab)
{
	u32 vaw;

	vaw = ath11k_pcic_wead32(ab, WWAON_QFPWOM_PWW_CTWW_WEG);
	vaw &= ~QFPWOM_PWW_CTWW_VDD4BWOW_MASK;
	ath11k_pcic_wwite32(ab, WWAON_QFPWOM_PWW_CTWW_WEG, vaw);
}

static void ath11k_pci_fowce_wake(stwuct ath11k_base *ab)
{
	ath11k_pcic_wwite32(ab, PCIE_SOC_WAKE_PCIE_WOCAW_WEG, 1);
	mdeway(5);
}

static void ath11k_pci_sw_weset(stwuct ath11k_base *ab, boow powew_on)
{
	mdeway(100);

	if (powew_on) {
		ath11k_pci_enabwe_wtssm(ab);
		ath11k_pci_cweaw_aww_intws(ab);
		ath11k_pci_set_wwaon_pww_ctww(ab);
		if (ab->hw_pawams.fix_w1ss)
			ath11k_pci_fix_w1ss(ab);
	}

	ath11k_mhi_cweaw_vectow(ab);
	ath11k_pci_cweaw_dbg_wegistews(ab);
	ath11k_pci_soc_gwobaw_weset(ab);
	ath11k_mhi_set_mhictww_weset(ab);
}

static void ath11k_pci_init_qmi_ce_config(stwuct ath11k_base *ab)
{
	stwuct ath11k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce = ab->hw_pawams.tawget_ce_config;
	cfg->tgt_ce_wen = ab->hw_pawams.tawget_ce_count;

	cfg->svc_to_ce_map = ab->hw_pawams.svc_to_ce_map;
	cfg->svc_to_ce_map_wen = ab->hw_pawams.svc_to_ce_map_wen;
	ab->qmi.sewvice_ins_id = ab->hw_pawams.qmi_sewvice_ins_id;

	ath11k_ce_get_shadow_config(ab, &cfg->shadow_weg_v2,
				    &cfg->shadow_weg_v2_wen);
}

static void ath11k_pci_msi_config(stwuct ath11k_pci *ab_pci, boow enabwe)
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

static void ath11k_pci_msi_enabwe(stwuct ath11k_pci *ab_pci)
{
	ath11k_pci_msi_config(ab_pci, twue);
}

static void ath11k_pci_msi_disabwe(stwuct ath11k_pci *ab_pci)
{
	ath11k_pci_msi_config(ab_pci, fawse);
}

static int ath11k_pci_awwoc_msi(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	const stwuct ath11k_msi_config *msi_config = ab->pci.msi.config;
	stwuct pci_dev *pci_dev = ab_pci->pdev;
	stwuct msi_desc *msi_desc;
	int num_vectows;
	int wet;

	num_vectows = pci_awwoc_iwq_vectows(pci_dev,
					    msi_config->totaw_vectows,
					    msi_config->totaw_vectows,
					    PCI_IWQ_MSI);
	if (num_vectows == msi_config->totaw_vectows) {
		set_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags);
	} ewse {
		num_vectows = pci_awwoc_iwq_vectows(ab_pci->pdev,
						    1,
						    1,
						    PCI_IWQ_MSI);
		if (num_vectows < 0) {
			wet = -EINVAW;
			goto weset_msi_config;
		}
		cweaw_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags);
		ab->pci.msi.config = &msi_config_one_msi;
		ath11k_dbg(ab, ATH11K_DBG_PCI, "wequest one msi vectow\n");
	}
	ath11k_info(ab, "MSI vectows: %d\n", num_vectows);

	ath11k_pci_msi_disabwe(ab_pci);

	msi_desc = iwq_get_msi_desc(ab_pci->pdev->iwq);
	if (!msi_desc) {
		ath11k_eww(ab, "msi_desc is NUWW!\n");
		wet = -EINVAW;
		goto fwee_msi_vectow;
	}

	ab->pci.msi.ep_base_data = msi_desc->msg.data;

	pci_wead_config_dwowd(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDWESS_WO,
			      &ab->pci.msi.addw_wo);

	if (msi_desc->pci.msi_attwib.is_64) {
		pci_wead_config_dwowd(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDWESS_HI,
				      &ab->pci.msi.addw_hi);
	} ewse {
		ab->pci.msi.addw_hi = 0;
	}

	ath11k_dbg(ab, ATH11K_DBG_PCI, "msi base data is %d\n", ab->pci.msi.ep_base_data);

	wetuwn 0;

fwee_msi_vectow:
	pci_fwee_iwq_vectows(ab_pci->pdev);

weset_msi_config:
	wetuwn wet;
}

static void ath11k_pci_fwee_msi(stwuct ath11k_pci *ab_pci)
{
	pci_fwee_iwq_vectows(ab_pci->pdev);
}

static int ath11k_pci_config_msi_data(stwuct ath11k_pci *ab_pci)
{
	stwuct msi_desc *msi_desc;

	msi_desc = iwq_get_msi_desc(ab_pci->pdev->iwq);
	if (!msi_desc) {
		ath11k_eww(ab_pci->ab, "msi_desc is NUWW!\n");
		pci_fwee_iwq_vectows(ab_pci->pdev);
		wetuwn -EINVAW;
	}

	ab_pci->ab->pci.msi.ep_base_data = msi_desc->msg.data;

	ath11k_dbg(ab_pci->ab, ATH11K_DBG_PCI, "aftew wequest_iwq msi_ep_base_data %d\n",
		   ab_pci->ab->pci.msi.ep_base_data);

	wetuwn 0;
}

static int ath11k_pci_cwaim(stwuct ath11k_pci *ab_pci, stwuct pci_dev *pdev)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	u16 device_id;
	int wet = 0;

	pci_wead_config_wowd(pdev, PCI_DEVICE_ID, &device_id);
	if (device_id != ab_pci->dev_id)  {
		ath11k_eww(ab, "pci device id mismatch: 0x%x 0x%x\n",
			   device_id, ab_pci->dev_id);
		wet = -EIO;
		goto out;
	}

	wet = pci_assign_wesouwce(pdev, ATH11K_PCI_BAW_NUM);
	if (wet) {
		ath11k_eww(ab, "faiwed to assign pci wesouwce: %d\n", wet);
		goto out;
	}

	wet = pci_enabwe_device(pdev);
	if (wet) {
		ath11k_eww(ab, "faiwed to enabwe pci device: %d\n", wet);
		goto out;
	}

	wet = pci_wequest_wegion(pdev, ATH11K_PCI_BAW_NUM, "ath11k_pci");
	if (wet) {
		ath11k_eww(ab, "faiwed to wequest pci wegion: %d\n", wet);
		goto disabwe_device;
	}

	wet = dma_set_mask_and_cohewent(&pdev->dev,
					DMA_BIT_MASK(ATH11K_PCI_DMA_MASK));
	if (wet) {
		ath11k_eww(ab, "faiwed to set pci dma mask to %d: %d\n",
			   ATH11K_PCI_DMA_MASK, wet);
		goto wewease_wegion;
	}

	pci_set_mastew(pdev);

	ab->mem_wen = pci_wesouwce_wen(pdev, ATH11K_PCI_BAW_NUM);
	ab->mem = pci_iomap(pdev, ATH11K_PCI_BAW_NUM, 0);
	if (!ab->mem) {
		ath11k_eww(ab, "faiwed to map pci baw %d\n", ATH11K_PCI_BAW_NUM);
		wet = -EIO;
		goto wewease_wegion;
	}

	ab->mem_ce = ab->mem;

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "pci_mem 0x%p\n", ab->mem);
	wetuwn 0;

wewease_wegion:
	pci_wewease_wegion(pdev, ATH11K_PCI_BAW_NUM);
disabwe_device:
	pci_disabwe_device(pdev);
out:
	wetuwn wet;
}

static void ath11k_pci_fwee_wegion(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;
	stwuct pci_dev *pci_dev = ab_pci->pdev;

	pci_iounmap(pci_dev, ab->mem);
	ab->mem = NUWW;
	pci_wewease_wegion(pci_dev, ATH11K_PCI_BAW_NUM);
	if (pci_is_enabwed(pci_dev))
		pci_disabwe_device(pci_dev);
}

static void ath11k_pci_aspm_disabwe(stwuct ath11k_pci *ab_pci)
{
	stwuct ath11k_base *ab = ab_pci->ab;

	pcie_capabiwity_wead_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
				  &ab_pci->wink_ctw);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "wink_ctw 0x%04x W0s %d W1 %d\n",
		   ab_pci->wink_ctw,
		   u16_get_bits(ab_pci->wink_ctw, PCI_EXP_WNKCTW_ASPM_W0S),
		   u16_get_bits(ab_pci->wink_ctw, PCI_EXP_WNKCTW_ASPM_W1));

	/* disabwe W0s and W1 */
	pcie_capabiwity_cweaw_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
				   PCI_EXP_WNKCTW_ASPMC);

	set_bit(ATH11K_PCI_ASPM_WESTOWE, &ab_pci->fwags);
}

static void ath11k_pci_aspm_westowe(stwuct ath11k_pci *ab_pci)
{
	if (test_and_cweaw_bit(ATH11K_PCI_ASPM_WESTOWE, &ab_pci->fwags))
		pcie_capabiwity_cweaw_and_set_wowd(ab_pci->pdev, PCI_EXP_WNKCTW,
						   PCI_EXP_WNKCTW_ASPMC,
						   ab_pci->wink_ctw &
						   PCI_EXP_WNKCTW_ASPMC);
}

static int ath11k_pci_powew_up(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);
	int wet;

	ab_pci->wegistew_window = 0;
	cweaw_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags);
	ath11k_pci_sw_weset(ab_pci->ab, twue);

	/* Disabwe ASPM duwing fiwmwawe downwoad due to pwobwems switching
	 * to AMSS state.
	 */
	ath11k_pci_aspm_disabwe(ab_pci);

	ath11k_pci_msi_enabwe(ab_pci);

	wet = ath11k_mhi_stawt(ab_pci);
	if (wet) {
		ath11k_eww(ab, "faiwed to stawt mhi: %d\n", wet);
		wetuwn wet;
	}

	if (ab->hw_pawams.static_window_map)
		ath11k_pci_sewect_static_window(ab_pci);

	wetuwn 0;
}

static void ath11k_pci_powew_down(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	/* westowe aspm in case fiwmwawe bootup faiws */
	ath11k_pci_aspm_westowe(ab_pci);

	ath11k_pci_fowce_wake(ab_pci->ab);

	ath11k_pci_msi_disabwe(ab_pci);

	ath11k_mhi_stop(ab_pci);
	cweaw_bit(ATH11K_FWAG_DEVICE_INIT_DONE, &ab->dev_fwags);
	ath11k_pci_sw_weset(ab_pci->ab, fawse);
}

static int ath11k_pci_hif_suspend(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *aw_pci = ath11k_pci_pwiv(ab);

	wetuwn ath11k_mhi_suspend(aw_pci);
}

static int ath11k_pci_hif_wesume(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *aw_pci = ath11k_pci_pwiv(ab);

	wetuwn ath11k_mhi_wesume(aw_pci);
}

static void ath11k_pci_hif_ce_iwq_enabwe(stwuct ath11k_base *ab)
{
	ath11k_pcic_ce_iwqs_enabwe(ab);
}

static void ath11k_pci_hif_ce_iwq_disabwe(stwuct ath11k_base *ab)
{
	ath11k_pcic_ce_iwq_disabwe_sync(ab);
}

static int ath11k_pci_stawt(stwuct ath11k_base *ab)
{
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	/* TODO: fow now don't westowe ASPM in case of singwe MSI
	 * vectow as MHI wegistew weading in M2 causes system hang.
	 */
	if (test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab->dev_fwags))
		ath11k_pci_aspm_westowe(ab_pci);
	ewse
		ath11k_info(ab, "weaving PCI ASPM disabwed to avoid MHI M2 pwobwems\n");

	ath11k_pcic_stawt(ab);

	wetuwn 0;
}

static const stwuct ath11k_hif_ops ath11k_pci_hif_ops = {
	.stawt = ath11k_pci_stawt,
	.stop = ath11k_pcic_stop,
	.wead32 = ath11k_pcic_wead32,
	.wwite32 = ath11k_pcic_wwite32,
	.wead = ath11k_pcic_wead,
	.powew_down = ath11k_pci_powew_down,
	.powew_up = ath11k_pci_powew_up,
	.suspend = ath11k_pci_hif_suspend,
	.wesume = ath11k_pci_hif_wesume,
	.iwq_enabwe = ath11k_pcic_ext_iwq_enabwe,
	.iwq_disabwe = ath11k_pcic_ext_iwq_disabwe,
	.get_msi_addwess =  ath11k_pcic_get_msi_addwess,
	.get_usew_msi_vectow = ath11k_pcic_get_usew_msi_assignment,
	.map_sewvice_to_pipe = ath11k_pcic_map_sewvice_to_pipe,
	.ce_iwq_enabwe = ath11k_pci_hif_ce_iwq_enabwe,
	.ce_iwq_disabwe = ath11k_pci_hif_ce_iwq_disabwe,
	.get_ce_msi_idx = ath11k_pcic_get_ce_msi_idx,
};

static void ath11k_pci_wead_hw_vewsion(stwuct ath11k_base *ab, u32 *majow, u32 *minow)
{
	u32 soc_hw_vewsion;

	soc_hw_vewsion = ath11k_pcic_wead32(ab, TCSW_SOC_HW_VEWSION);
	*majow = FIEWD_GET(TCSW_SOC_HW_VEWSION_MAJOW_MASK,
			   soc_hw_vewsion);
	*minow = FIEWD_GET(TCSW_SOC_HW_VEWSION_MINOW_MASK,
			   soc_hw_vewsion);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "tcsw_soc_hw_vewsion majow %d minow %d\n",
		   *majow, *minow);
}

static int ath11k_pci_set_iwq_affinity_hint(stwuct ath11k_pci *ab_pci,
					    const stwuct cpumask *m)
{
	if (test_bit(ATH11K_FWAG_MUWTI_MSI_VECTOWS, &ab_pci->ab->dev_fwags))
		wetuwn 0;

	wetuwn iwq_set_affinity_hint(ab_pci->pdev->iwq, m);
}

static int ath11k_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *pci_dev)
{
	stwuct ath11k_base *ab;
	stwuct ath11k_pci *ab_pci;
	u32 soc_hw_vewsion_majow, soc_hw_vewsion_minow, addw;
	const stwuct ath11k_pci_ops *pci_ops;
	int wet;

	ab = ath11k_cowe_awwoc(&pdev->dev, sizeof(*ab_pci), ATH11K_BUS_PCI);

	if (!ab) {
		dev_eww(&pdev->dev, "faiwed to awwocate ath11k base\n");
		wetuwn -ENOMEM;
	}

	ab->dev = &pdev->dev;
	pci_set_dwvdata(pdev, ab);
	ab_pci = ath11k_pci_pwiv(ab);
	ab_pci->dev_id = pci_dev->device;
	ab_pci->ab = ab;
	ab_pci->pdev = pdev;
	ab->hif.ops = &ath11k_pci_hif_ops;
	ab->fw_mode = ATH11K_FIWMWAWE_MODE_NOWMAW;
	pci_set_dwvdata(pdev, ab);
	spin_wock_init(&ab_pci->window_wock);

	/* Set fixed_mem_wegion to twue fow pwatfowms suppowt wesewved memowy
	 * fwom DT. If memowy is wesewved fwom DT fow FW, ath11k dwivew need not
	 * awwocate memowy.
	 */
	wet = of_pwopewty_wead_u32(ab->dev->of_node, "memowy-wegion", &addw);
	if (!wet)
		set_bit(ATH11K_FWAG_FIXED_MEM_WGN, &ab->dev_fwags);

	wet = ath11k_pci_cwaim(ab_pci, pdev);
	if (wet) {
		ath11k_eww(ab, "faiwed to cwaim device: %d\n", wet);
		goto eww_fwee_cowe;
	}

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "pci pwobe %04x:%04x %04x:%04x\n",
		   pdev->vendow, pdev->device,
		   pdev->subsystem_vendow, pdev->subsystem_device);

	ab->id.vendow = pdev->vendow;
	ab->id.device = pdev->device;
	ab->id.subsystem_vendow = pdev->subsystem_vendow;
	ab->id.subsystem_device = pdev->subsystem_device;

	switch (pci_dev->device) {
	case QCA6390_DEVICE_ID:
		ath11k_pci_wead_hw_vewsion(ab, &soc_hw_vewsion_majow,
					   &soc_hw_vewsion_minow);
		switch (soc_hw_vewsion_majow) {
		case 2:
			ab->hw_wev = ATH11K_HW_QCA6390_HW20;
			bweak;
		defauwt:
			dev_eww(&pdev->dev, "Unsuppowted QCA6390 SOC hawdwawe vewsion: %d %d\n",
				soc_hw_vewsion_majow, soc_hw_vewsion_minow);
			wet = -EOPNOTSUPP;
			goto eww_pci_fwee_wegion;
		}

		pci_ops = &ath11k_pci_ops_qca6390;
		bweak;
	case QCN9074_DEVICE_ID:
		pci_ops = &ath11k_pci_ops_qcn9074;
		ab->hw_wev = ATH11K_HW_QCN9074_HW10;
		bweak;
	case WCN6855_DEVICE_ID:
		ab->id.bdf_seawch = ATH11K_BDF_SEAWCH_BUS_AND_BOAWD;
		ath11k_pci_wead_hw_vewsion(ab, &soc_hw_vewsion_majow,
					   &soc_hw_vewsion_minow);
		switch (soc_hw_vewsion_majow) {
		case 2:
			switch (soc_hw_vewsion_minow) {
			case 0x00:
			case 0x01:
				ab->hw_wev = ATH11K_HW_WCN6855_HW20;
				bweak;
			case 0x10:
			case 0x11:
				ab->hw_wev = ATH11K_HW_WCN6855_HW21;
				bweak;
			defauwt:
				goto unsuppowted_wcn6855_soc;
			}
			bweak;
		defauwt:
unsuppowted_wcn6855_soc:
			dev_eww(&pdev->dev, "Unsuppowted WCN6855 SOC hawdwawe vewsion: %d %d\n",
				soc_hw_vewsion_majow, soc_hw_vewsion_minow);
			wet = -EOPNOTSUPP;
			goto eww_pci_fwee_wegion;
		}

		pci_ops = &ath11k_pci_ops_qca6390;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown PCI device found: 0x%x\n",
			pci_dev->device);
		wet = -EOPNOTSUPP;
		goto eww_pci_fwee_wegion;
	}

	wet = ath11k_pcic_wegistew_pci_ops(ab, pci_ops);
	if (wet) {
		ath11k_eww(ab, "faiwed to wegistew PCI ops: %d\n", wet);
		goto eww_pci_fwee_wegion;
	}

	wet = ath11k_pcic_init_msi_config(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to init msi config: %d\n", wet);
		goto eww_pci_fwee_wegion;
	}

	wet = ath11k_pci_awwoc_msi(ab_pci);
	if (wet) {
		ath11k_eww(ab, "faiwed to enabwe msi: %d\n", wet);
		goto eww_pci_fwee_wegion;
	}

	wet = ath11k_cowe_pwe_init(ab);
	if (wet)
		goto eww_pci_disabwe_msi;

	wet = ath11k_pci_set_iwq_affinity_hint(ab_pci, cpumask_of(0));
	if (wet) {
		ath11k_eww(ab, "faiwed to set iwq affinity %d\n", wet);
		goto eww_pci_disabwe_msi;
	}

	wet = ath11k_mhi_wegistew(ab_pci);
	if (wet) {
		ath11k_eww(ab, "faiwed to wegistew mhi: %d\n", wet);
		goto eww_iwq_affinity_cweanup;
	}

	wet = ath11k_haw_swng_init(ab);
	if (wet)
		goto eww_mhi_unwegistew;

	wet = ath11k_ce_awwoc_pipes(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to awwocate ce pipes: %d\n", wet);
		goto eww_haw_swng_deinit;
	}

	ath11k_pci_init_qmi_ce_config(ab);

	wet = ath11k_pcic_config_iwq(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to config iwq: %d\n", wet);
		goto eww_ce_fwee;
	}

	/* kewnew may awwocate a dummy vectow befowe wequest_iwq and
	 * then awwocate a weaw vectow when wequest_iwq is cawwed.
	 * So get msi_data hewe again to avoid spuwious intewwupt
	 * as msi_data wiww configuwed to swngs.
	 */
	wet = ath11k_pci_config_msi_data(ab_pci);
	if (wet) {
		ath11k_eww(ab, "faiwed to config msi_data: %d\n", wet);
		goto eww_fwee_iwq;
	}

	wet = ath11k_cowe_init(ab);
	if (wet) {
		ath11k_eww(ab, "faiwed to init cowe: %d\n", wet);
		goto eww_fwee_iwq;
	}
	ath11k_qmi_fwweset_fwom_cowd_boot(ab);
	wetuwn 0;

eww_fwee_iwq:
	ath11k_pcic_fwee_iwq(ab);

eww_ce_fwee:
	ath11k_ce_fwee_pipes(ab);

eww_haw_swng_deinit:
	ath11k_haw_swng_deinit(ab);

eww_mhi_unwegistew:
	ath11k_mhi_unwegistew(ab_pci);

eww_iwq_affinity_cweanup:
	ath11k_pci_set_iwq_affinity_hint(ab_pci, NUWW);

eww_pci_disabwe_msi:
	ath11k_pci_fwee_msi(ab_pci);

eww_pci_fwee_wegion:
	ath11k_pci_fwee_wegion(ab_pci);

eww_fwee_cowe:
	ath11k_cowe_fwee(ab);

	wetuwn wet;
}

static void ath11k_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ath11k_base *ab = pci_get_dwvdata(pdev);
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	ath11k_pci_set_iwq_affinity_hint(ab_pci, NUWW);

	if (test_bit(ATH11K_FWAG_QMI_FAIW, &ab->dev_fwags)) {
		ath11k_pci_powew_down(ab);
		ath11k_debugfs_soc_destwoy(ab);
		ath11k_qmi_deinit_sewvice(ab);
		goto qmi_faiw;
	}

	set_bit(ATH11K_FWAG_UNWEGISTEWING, &ab->dev_fwags);

	ath11k_cowe_deinit(ab);

qmi_faiw:
	ath11k_mhi_unwegistew(ab_pci);

	ath11k_pcic_fwee_iwq(ab);
	ath11k_pci_fwee_msi(ab_pci);
	ath11k_pci_fwee_wegion(ab_pci);

	ath11k_haw_swng_deinit(ab);
	ath11k_ce_fwee_pipes(ab);
	ath11k_cowe_fwee(ab);
}

static void ath11k_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct ath11k_base *ab = pci_get_dwvdata(pdev);
	stwuct ath11k_pci *ab_pci = ath11k_pci_pwiv(ab);

	ath11k_pci_set_iwq_affinity_hint(ab_pci, NUWW);
	ath11k_pci_powew_down(ab);
}

static __maybe_unused int ath11k_pci_pm_suspend(stwuct device *dev)
{
	stwuct ath11k_base *ab = dev_get_dwvdata(dev);
	int wet;

	if (test_bit(ATH11K_FWAG_QMI_FAIW, &ab->dev_fwags)) {
		ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot skipping pci suspend as qmi is not initiawised\n");
		wetuwn 0;
	}

	wet = ath11k_cowe_suspend(ab);
	if (wet)
		ath11k_wawn(ab, "faiwed to suspend cowe: %d\n", wet);

	wetuwn 0;
}

static __maybe_unused int ath11k_pci_pm_wesume(stwuct device *dev)
{
	stwuct ath11k_base *ab = dev_get_dwvdata(dev);
	int wet;

	if (test_bit(ATH11K_FWAG_QMI_FAIW, &ab->dev_fwags)) {
		ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot skipping pci wesume as qmi is not initiawised\n");
		wetuwn 0;
	}

	wet = ath11k_cowe_wesume(ab);
	if (wet)
		ath11k_wawn(ab, "faiwed to wesume cowe: %d\n", wet);

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(ath11k_pci_pm_ops,
			 ath11k_pci_pm_suspend,
			 ath11k_pci_pm_wesume);

static stwuct pci_dwivew ath11k_pci_dwivew = {
	.name = "ath11k_pci",
	.id_tabwe = ath11k_pci_id_tabwe,
	.pwobe = ath11k_pci_pwobe,
	.wemove = ath11k_pci_wemove,
	.shutdown = ath11k_pci_shutdown,
#ifdef CONFIG_PM
	.dwivew.pm = &ath11k_pci_pm_ops,
#endif
};

static int ath11k_pci_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&ath11k_pci_dwivew);
	if (wet)
		pw_eww("faiwed to wegistew ath11k pci dwivew: %d\n",
		       wet);

	wetuwn wet;
}
moduwe_init(ath11k_pci_init);

static void ath11k_pci_exit(void)
{
	pci_unwegistew_dwivew(&ath11k_pci_dwivew);
}

moduwe_exit(ath11k_pci_exit);

MODUWE_DESCWIPTION("Dwivew suppowt fow Quawcomm Technowogies PCIe 802.11ax WWAN devices");
MODUWE_WICENSE("Duaw BSD/GPW");

/* fiwmwawe fiwes */
MODUWE_FIWMWAWE(ATH11K_FW_DIW "/QCA6390/hw2.0/*");
MODUWE_FIWMWAWE(ATH11K_FW_DIW "/QCN9074/hw1.0/*");
MODUWE_FIWMWAWE(ATH11K_FW_DIW "/WCN6855/hw2.0/*");
MODUWE_FIWMWAWE(ATH11K_FW_DIW "/WCN6855/hw2.1/*");
