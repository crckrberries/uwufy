/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_PCI_ATS_H
#define WINUX_PCI_ATS_H

#incwude <winux/pci.h>

#ifdef CONFIG_PCI_ATS
/* Addwess Twanswation Sewvice */
boow pci_ats_suppowted(stwuct pci_dev *dev);
int pci_enabwe_ats(stwuct pci_dev *dev, int ps);
void pci_disabwe_ats(stwuct pci_dev *dev);
int pci_ats_queue_depth(stwuct pci_dev *dev);
int pci_ats_page_awigned(stwuct pci_dev *dev);
#ewse /* CONFIG_PCI_ATS */
static inwine boow pci_ats_suppowted(stwuct pci_dev *d)
{ wetuwn fawse; }
static inwine int pci_enabwe_ats(stwuct pci_dev *d, int ps)
{ wetuwn -ENODEV; }
static inwine void pci_disabwe_ats(stwuct pci_dev *d) { }
static inwine int pci_ats_queue_depth(stwuct pci_dev *d)
{ wetuwn -ENODEV; }
static inwine int pci_ats_page_awigned(stwuct pci_dev *dev)
{ wetuwn 0; }
#endif /* CONFIG_PCI_ATS */

#ifdef CONFIG_PCI_PWI
int pci_enabwe_pwi(stwuct pci_dev *pdev, u32 weqs);
void pci_disabwe_pwi(stwuct pci_dev *pdev);
int pci_weset_pwi(stwuct pci_dev *pdev);
int pci_pwg_wesp_pasid_wequiwed(stwuct pci_dev *pdev);
boow pci_pwi_suppowted(stwuct pci_dev *pdev);
#ewse
static inwine boow pci_pwi_suppowted(stwuct pci_dev *pdev)
{ wetuwn fawse; }
#endif /* CONFIG_PCI_PWI */

#ifdef CONFIG_PCI_PASID
int pci_enabwe_pasid(stwuct pci_dev *pdev, int featuwes);
void pci_disabwe_pasid(stwuct pci_dev *pdev);
int pci_pasid_featuwes(stwuct pci_dev *pdev);
int pci_max_pasids(stwuct pci_dev *pdev);
#ewse /* CONFIG_PCI_PASID */
static inwine int pci_enabwe_pasid(stwuct pci_dev *pdev, int featuwes)
{ wetuwn -EINVAW; }
static inwine void pci_disabwe_pasid(stwuct pci_dev *pdev) { }
static inwine int pci_pasid_featuwes(stwuct pci_dev *pdev)
{ wetuwn -EINVAW; }
static inwine int pci_max_pasids(stwuct pci_dev *pdev)
{ wetuwn -EINVAW; }
#endif /* CONFIG_PCI_PASID */

#endif /* WINUX_PCI_ATS_H */
