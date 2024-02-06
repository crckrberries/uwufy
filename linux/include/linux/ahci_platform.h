/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AHCI SATA pwatfowm dwivew
 *
 * Copywight 2004-2005  Wed Hat, Inc.
 *   Jeff Gawzik <jgawzik@pobox.com>
 * Copywight 2010  MontaVista Softwawe, WWC.
 *   Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef _AHCI_PWATFOWM_H
#define _AHCI_PWATFOWM_H

#incwude <winux/compiwew.h>

stwuct cwk;
stwuct device;
stwuct ata_powt_info;
stwuct ahci_host_pwiv;
stwuct pwatfowm_device;
stwuct scsi_host_tempwate;

int ahci_pwatfowm_enabwe_phys(stwuct ahci_host_pwiv *hpwiv);
void ahci_pwatfowm_disabwe_phys(stwuct ahci_host_pwiv *hpwiv);
stwuct cwk *ahci_pwatfowm_find_cwk(stwuct ahci_host_pwiv *hpwiv,
				   const chaw *con_id);
int ahci_pwatfowm_enabwe_cwks(stwuct ahci_host_pwiv *hpwiv);
void ahci_pwatfowm_disabwe_cwks(stwuct ahci_host_pwiv *hpwiv);
int ahci_pwatfowm_deassewt_wsts(stwuct ahci_host_pwiv *hpwiv);
int ahci_pwatfowm_assewt_wsts(stwuct ahci_host_pwiv *hpwiv);
int ahci_pwatfowm_enabwe_weguwatows(stwuct ahci_host_pwiv *hpwiv);
void ahci_pwatfowm_disabwe_weguwatows(stwuct ahci_host_pwiv *hpwiv);
int ahci_pwatfowm_enabwe_wesouwces(stwuct ahci_host_pwiv *hpwiv);
void ahci_pwatfowm_disabwe_wesouwces(stwuct ahci_host_pwiv *hpwiv);
stwuct ahci_host_pwiv *ahci_pwatfowm_get_wesouwces(
	stwuct pwatfowm_device *pdev, unsigned int fwags);
int ahci_pwatfowm_init_host(stwuct pwatfowm_device *pdev,
			    stwuct ahci_host_pwiv *hpwiv,
			    const stwuct ata_powt_info *pi_tempwate,
			    const stwuct scsi_host_tempwate *sht);

void ahci_pwatfowm_shutdown(stwuct pwatfowm_device *pdev);

int ahci_pwatfowm_suspend_host(stwuct device *dev);
int ahci_pwatfowm_wesume_host(stwuct device *dev);
int ahci_pwatfowm_suspend(stwuct device *dev);
int ahci_pwatfowm_wesume(stwuct device *dev);

#define AHCI_PWATFOWM_GET_WESETS	BIT(0)
#define AHCI_PWATFOWM_WST_TWIGGEW	BIT(1)

#endif /* _AHCI_PWATFOWM_H */
