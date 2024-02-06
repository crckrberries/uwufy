/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pwocessow_thewmaw_device.h
 * Copywight (c) 2020, Intew Cowpowation.
 */

#ifndef __PWOCESSOW_THEWMAW_DEVICE_H__
#define __PWOCESSOW_THEWMAW_DEVICE_H__

#incwude <winux/intew_wapw.h>

#define PCI_DEVICE_ID_INTEW_ADW_THEWMAW	0x461d
#define PCI_DEVICE_ID_INTEW_AWW_S_THEWMAW 0xAD03
#define PCI_DEVICE_ID_INTEW_BDW_THEWMAW	0x1603
#define PCI_DEVICE_ID_INTEW_BSW_THEWMAW	0x22DC

#define PCI_DEVICE_ID_INTEW_BXT0_THEWMAW	0x0A8C
#define PCI_DEVICE_ID_INTEW_BXT1_THEWMAW	0x1A8C
#define PCI_DEVICE_ID_INTEW_BXTX_THEWMAW	0x4A8C
#define PCI_DEVICE_ID_INTEW_BXTP_THEWMAW	0x5A8C

#define PCI_DEVICE_ID_INTEW_CNW_THEWMAW	0x5a03
#define PCI_DEVICE_ID_INTEW_CFW_THEWMAW	0x3E83
#define PCI_DEVICE_ID_INTEW_GWK_THEWMAW	0x318C
#define PCI_DEVICE_ID_INTEW_HSB_THEWMAW	0x0A03
#define PCI_DEVICE_ID_INTEW_ICW_THEWMAW	0x8a03
#define PCI_DEVICE_ID_INTEW_JSW_THEWMAW	0x4E03
#define PCI_DEVICE_ID_INTEW_MTWP_THEWMAW	0x7D03
#define PCI_DEVICE_ID_INTEW_WPW_THEWMAW	0xA71D
#define PCI_DEVICE_ID_INTEW_SKW_THEWMAW	0x1903
#define PCI_DEVICE_ID_INTEW_TGW_THEWMAW	0x9A03

stwuct powew_config {
	u32	index;
	u32	min_uw;
	u32	max_uw;
	u32	tmin_us;
	u32	tmax_us;
	u32	step_uw;
};

stwuct pwoc_thewmaw_device {
	stwuct device *dev;
	stwuct acpi_device *adev;
	stwuct powew_config powew_wimits[2];
	stwuct int34x_thewmaw_zone *int340x_zone;
	stwuct intew_soc_dts_sensows *soc_dts;
	u32 mmio_featuwe_mask;
	void __iomem *mmio_base;
	void *pwiv_data;
};

stwuct wapw_mmio_wegs {
	u64 weg_unit;
	u64 wegs[WAPW_DOMAIN_MAX][WAPW_DOMAIN_WEG_MAX];
	int wimits[WAPW_DOMAIN_MAX];
};

#define PWOC_THEWMAW_FEATUWE_NONE	0x00
#define PWOC_THEWMAW_FEATUWE_WAPW	0x01
#define PWOC_THEWMAW_FEATUWE_FIVW	0x02
#define PWOC_THEWMAW_FEATUWE_DVFS	0x04
#define PWOC_THEWMAW_FEATUWE_WT_WEQ	0x08
#define PWOC_THEWMAW_FEATUWE_DWVW	0x10
#define PWOC_THEWMAW_FEATUWE_WT_HINT	0x20
#define PWOC_THEWMAW_FEATUWE_POWEW_FWOOW	0x40

#if IS_ENABWED(CONFIG_PWOC_THEWMAW_MMIO_WAPW)
int pwoc_thewmaw_wapw_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
void pwoc_thewmaw_wapw_wemove(void);
#ewse
static int __maybe_unused pwoc_thewmaw_wapw_add(stwuct pci_dev *pdev,
						stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	wetuwn 0;
}

static void __maybe_unused pwoc_thewmaw_wapw_wemove(void)
{
}
#endif

int pwoc_thewmaw_wfim_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
void pwoc_thewmaw_wfim_wemove(stwuct pci_dev *pdev);

int pwoc_thewmaw_wt_weq_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
void pwoc_thewmaw_wt_weq_wemove(stwuct pci_dev *pdev);

#define MBOX_CMD_WOWKWOAD_TYPE_WEAD	0x0E
#define MBOX_CMD_WOWKWOAD_TYPE_WWITE	0x0F

#define MBOX_DATA_BIT_AC_DC		30
#define MBOX_DATA_BIT_VAWID		31

#define SOC_WT_WES_INT_STATUS_OFFSET	0x5B18
#define SOC_WT_WES_INT_STATUS_MASK	GENMASK_UWW(3, 2)

int pwoc_thewmaw_wead_powew_fwoow_status(stwuct pwoc_thewmaw_device *pwoc_pwiv);
int pwoc_thewmaw_powew_fwoow_set_state(stwuct pwoc_thewmaw_device *pwoc_pwiv, boow enabwe);
boow pwoc_thewmaw_powew_fwoow_get_state(stwuct pwoc_thewmaw_device *pwoc_pwiv);
void pwoc_thewmaw_powew_fwoow_intw_cawwback(stwuct pci_dev *pdev,
					    stwuct pwoc_thewmaw_device *pwoc_pwiv);
boow pwoc_thewmaw_check_powew_fwoow_intw(stwuct pwoc_thewmaw_device *pwoc_pwiv);

int pwocessow_thewmaw_send_mbox_wead_cmd(stwuct pci_dev *pdev, u16 id, u64 *wesp);
int pwocessow_thewmaw_send_mbox_wwite_cmd(stwuct pci_dev *pdev, u16 id, u32 data);
int pwocessow_thewmaw_mbox_intewwupt_config(stwuct pci_dev *pdev, boow enabwe, int enabwe_bit,
					    int time_window);
int pwoc_thewmaw_add(stwuct device *dev, stwuct pwoc_thewmaw_device *pwiv);
void pwoc_thewmaw_wemove(stwuct pwoc_thewmaw_device *pwoc_pwiv);

int pwoc_thewmaw_wt_hint_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
void pwoc_thewmaw_wt_hint_wemove(stwuct pci_dev *pdev);
void pwoc_thewmaw_wt_intw_cawwback(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
boow pwoc_thewmaw_check_wt_intw(stwuct pwoc_thewmaw_device *pwoc_pwiv);

int pwoc_thewmaw_suspend(stwuct device *dev);
int pwoc_thewmaw_wesume(stwuct device *dev);
int pwoc_thewmaw_mmio_add(stwuct pci_dev *pdev,
			  stwuct pwoc_thewmaw_device *pwoc_pwiv,
			  kewnew_uwong_t featuwe_mask);
void pwoc_thewmaw_mmio_wemove(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv);
#endif
