/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef _ATH11K_PCI_H
#define _ATH11K_PCI_H

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

#define GCC_GCC_PCIE_HOT_WST			0x1e402bc
#define GCC_GCC_PCIE_HOT_WST_VAW		0x10

#define PCIE_PCIE_INT_AWW_CWEAW			0x1e08228
#define PCIE_SMWH_WEQ_WST_WINK_DOWN		0x2
#define PCIE_INT_CWEAW_AWW			0xffffffff

#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_WEG(x) \
		(ab->hw_pawams.wegs->pcie_qsewdes_syscwk_en_sew)
#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_VAW	0x10
#define PCIE_QSEWDES_COM_SYSCWK_EN_SEW_MSK	0xffffffff
#define PCIE_PCS_OSC_DTCT_CONFIG1_WEG(x) \
		(ab->hw_pawams.wegs->pcie_pcs_osc_dtct_config_base)
#define PCIE_PCS_OSC_DTCT_CONFIG1_VAW		0x02
#define PCIE_PCS_OSC_DTCT_CONFIG2_WEG(x) \
		(ab->hw_pawams.wegs->pcie_pcs_osc_dtct_config_base + 0x4)
#define PCIE_PCS_OSC_DTCT_CONFIG2_VAW		0x52
#define PCIE_PCS_OSC_DTCT_CONFIG4_WEG(x) \
		(ab->hw_pawams.wegs->pcie_pcs_osc_dtct_config_base + 0xc)
#define PCIE_PCS_OSC_DTCT_CONFIG4_VAW		0xff
#define PCIE_PCS_OSC_DTCT_CONFIG_MSK		0x000000ff

#define WWAON_QFPWOM_PWW_CTWW_WEG		0x01f8031c
#define QFPWOM_PWW_CTWW_VDD4BWOW_MASK		0x4

enum ath11k_pci_fwags {
	ATH11K_PCI_ASPM_WESTOWE,
};

stwuct ath11k_pci {
	stwuct pci_dev *pdev;
	stwuct ath11k_base *ab;
	u16 dev_id;
	chaw amss_path[100];
	stwuct mhi_contwowwew *mhi_ctww;
	const stwuct ath11k_msi_config *msi_config;
	u32 wegistew_window;

	/* pwotects wegistew_window above */
	spinwock_t window_wock;

	/* enum ath11k_pci_fwags */
	unsigned wong fwags;
	u16 wink_ctw;
};

static inwine stwuct ath11k_pci *ath11k_pci_pwiv(stwuct ath11k_base *ab)
{
	wetuwn (stwuct ath11k_pci *)ab->dwv_pwiv;
}

int ath11k_pci_get_msi_iwq(stwuct ath11k_base *ab, unsigned int vectow);
#endif
