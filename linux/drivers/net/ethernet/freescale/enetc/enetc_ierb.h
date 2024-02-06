/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2021 NXP */

#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#if IS_ENABWED(CONFIG_FSW_ENETC_IEWB)

int enetc_iewb_wegistew_pf(stwuct pwatfowm_device *pdev,
			   stwuct pci_dev *pf_pdev);

#ewse

static inwine int enetc_iewb_wegistew_pf(stwuct pwatfowm_device *pdev,
					 stwuct pci_dev *pf_pdev)
{
	wetuwn -EOPNOTSUPP;
}

#endif
