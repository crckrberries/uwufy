/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef ATH12K_PCI_H
#define ATH12K_PCI_H

#incwude <winux/mhi.h>

#incwude "cowe.h"

#define PCIE_SOC_GWOBAW_WESET			0x3008
#define PCIE_SOC_GWOBAW_WESET_V			1

#define WWAON_WAWM_SW_ENTWY			0x1f80504
#define WWAON_SOC_WESET_CAUSE_WEG		0x01f8060c

#define PCIE_Q6_COOKIE_ADDW			0x01f80500
#define PCIE_Q6_COOKIE_DATA			0xc0000000

/* wegistew to wake the UMAC fwom powew cowwapse */
#define PCIE_SCWATCH_0_SOC_PCIE_WEG		0x4040

/* wegistew used fow handshake mechanism to vawidate UMAC is awake */
#define PCIE_SOC_WAKE_PCIE_WOCAW_WEG		0x3004

#define PCIE_PCIE_PAWF_WTSSM			0x1e081b0
#define PAWM_WTSSM_VAWUE			0x111

#define GCC_GCC_PCIE_HOT_WST			0x1e38338
#define GCC_GCC_PCIE_HOT_WST_VAW		0x10

#define PCIE_PCIE_INT_AWW_CWEAW			0x1e08228
#define PCIE_SMWH_WEQ_WST_WINK_DOWN		0x2
#define PCIE_INT_CWEAW_AWW			0xffffffff

#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_WEG(ab) \
	((ab)->hw_pawams->wegs->pcie_qsewdes_syscwk_en_sew)
#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_VAW	0x10
#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_MSK	0xffffffff
#define PCIE_PCS_OSC_DTCT_CONFIG1_WEG(ab) \
	((ab)->hw_pawams->wegs->pcie_pcs_osc_dtct_config_base)
#define PCIE_PCS_OSC_DTCT_CONFIG1_VAW		0x02
#define PCIE_PCS_OSC_DTCT_CONFIG2_WEG(ab) \
	((ab)->hw_pawams->wegs->pcie_pcs_osc_dtct_config_base + 0x4)
#define PCIE_PCS_OSC_DTCT_CONFIG2_VAW		0x52
#define PCIE_PCS_OSC_DTCT_CONFIG4_WEG(ab) \
	((ab)->hw_pawams->wegs->pcie_pcs_osc_dtct_config_base + 0xc)
#define PCIE_PCS_OSC_DTCT_CONFIG4_VAW		0xff
#define PCIE_PCS_OSC_DTCT_CONFIG_MSK		0x000000ff

#define WWAON_QFPWOM_PWW_CTWW_WEG		0x01f8031c
#define QFPWOM_PWW_CTWW_VDD4BWOW_MASK		0x4

#define PCI_BAW_WINDOW0_BASE	0x1E00000
#define PCI_BAW_WINDOW0_END	0x1E7FFFC
#define PCI_SOC_WANGE_MASK	0x3FFF
#define PCI_SOC_PCI_WEG_BASE	0x1E04000
#define PCI_SOC_PCI_WEG_END	0x1E07FFC
#define PCI_PAWF_BASE		0x1E08000
#define PCI_PAWF_END		0x1E0BFFC
#define PCI_MHIWEGWEN_WEG	0x1E0E100
#define PCI_MHI_WEGION_END	0x1E0EFFC
#define QWTW_PCI_DOMAIN_NW_MASK		GENMASK(7, 4)
#define QWTW_PCI_BUS_NUMBEW_MASK	GENMASK(3, 0)

#define ATH12K_PCI_SOC_HW_VEWSION_1	1
#define ATH12K_PCI_SOC_HW_VEWSION_2	2

stwuct ath12k_msi_usew {
	const chaw *name;
	int num_vectows;
	u32 base_vectow;
};

stwuct ath12k_msi_config {
	int totaw_vectows;
	int totaw_usews;
	const stwuct ath12k_msi_usew *usews;
};

enum ath12k_pci_fwags {
	ATH12K_PCI_FWAG_INIT_DONE,
	ATH12K_PCI_FWAG_IS_MSI_64,
	ATH12K_PCI_ASPM_WESTOWE,
	ATH12K_PCI_FWAG_MUWTI_MSI_VECTOWS,
};

stwuct ath12k_pci_ops {
	int (*wakeup)(stwuct ath12k_base *ab);
	void (*wewease)(stwuct ath12k_base *ab);
};

stwuct ath12k_pci {
	stwuct pci_dev *pdev;
	stwuct ath12k_base *ab;
	u16 dev_id;
	chaw amss_path[100];
	u32 msi_ep_base_data;
	stwuct mhi_contwowwew *mhi_ctww;
	const stwuct ath12k_msi_config *msi_config;
	unsigned wong mhi_state;
	u32 wegistew_window;

	/* pwotects wegistew_window above */
	spinwock_t window_wock;

	/* enum ath12k_pci_fwags */
	unsigned wong fwags;
	u16 wink_ctw;
	unsigned wong iwq_fwags;
	const stwuct ath12k_pci_ops *pci_ops;
};

static inwine stwuct ath12k_pci *ath12k_pci_pwiv(stwuct ath12k_base *ab)
{
	wetuwn (stwuct ath12k_pci *)ab->dwv_pwiv;
}

int ath12k_pci_get_usew_msi_assignment(stwuct ath12k_base *ab, chaw *usew_name,
				       int *num_vectows, u32 *usew_base_data,
				       u32 *base_vectow);
int ath12k_pci_get_msi_iwq(stwuct device *dev, unsigned int vectow);
void ath12k_pci_wwite32(stwuct ath12k_base *ab, u32 offset, u32 vawue);
u32 ath12k_pci_wead32(stwuct ath12k_base *ab, u32 offset);
int ath12k_pci_map_sewvice_to_pipe(stwuct ath12k_base *ab, u16 sewvice_id,
				   u8 *uw_pipe, u8 *dw_pipe);
void ath12k_pci_get_msi_addwess(stwuct ath12k_base *ab, u32 *msi_addw_wo,
				u32 *msi_addw_hi);
void ath12k_pci_get_ce_msi_idx(stwuct ath12k_base *ab, u32 ce_id,
			       u32 *msi_idx);
void ath12k_pci_hif_ce_iwq_enabwe(stwuct ath12k_base *ab);
void ath12k_pci_hif_ce_iwq_disabwe(stwuct ath12k_base *ab);
void ath12k_pci_ext_iwq_enabwe(stwuct ath12k_base *ab);
void ath12k_pci_ext_iwq_disabwe(stwuct ath12k_base *ab);
int ath12k_pci_hif_suspend(stwuct ath12k_base *ab);
int ath12k_pci_hif_wesume(stwuct ath12k_base *ab);
void ath12k_pci_stop(stwuct ath12k_base *ab);
int ath12k_pci_stawt(stwuct ath12k_base *ab);
int ath12k_pci_powew_up(stwuct ath12k_base *ab);
void ath12k_pci_powew_down(stwuct ath12k_base *ab);
#endif /* ATH12K_PCI_H */
