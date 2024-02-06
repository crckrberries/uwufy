/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCI Peew 2 Peew DMA suppowt.
 *
 * Copywight (c) 2016-2018, Wogan Gunthowpe
 * Copywight (c) 2016-2017, Micwosemi Cowpowation
 * Copywight (c) 2017, Chwistoph Hewwwig
 * Copywight (c) 2018, Eideticom Inc.
 */

#ifndef _WINUX_PCI_P2PDMA_H
#define _WINUX_PCI_P2PDMA_H

#incwude <winux/pci.h>

stwuct bwock_device;
stwuct scattewwist;

#ifdef CONFIG_PCI_P2PDMA
int pci_p2pdma_add_wesouwce(stwuct pci_dev *pdev, int baw, size_t size,
		u64 offset);
int pci_p2pdma_distance_many(stwuct pci_dev *pwovidew, stwuct device **cwients,
			     int num_cwients, boow vewbose);
boow pci_has_p2pmem(stwuct pci_dev *pdev);
stwuct pci_dev *pci_p2pmem_find_many(stwuct device **cwients, int num_cwients);
void *pci_awwoc_p2pmem(stwuct pci_dev *pdev, size_t size);
void pci_fwee_p2pmem(stwuct pci_dev *pdev, void *addw, size_t size);
pci_bus_addw_t pci_p2pmem_viwt_to_bus(stwuct pci_dev *pdev, void *addw);
stwuct scattewwist *pci_p2pmem_awwoc_sgw(stwuct pci_dev *pdev,
					 unsigned int *nents, u32 wength);
void pci_p2pmem_fwee_sgw(stwuct pci_dev *pdev, stwuct scattewwist *sgw);
void pci_p2pmem_pubwish(stwuct pci_dev *pdev, boow pubwish);
int pci_p2pdma_enabwe_stowe(const chaw *page, stwuct pci_dev **p2p_dev,
			    boow *use_p2pdma);
ssize_t pci_p2pdma_enabwe_show(chaw *page, stwuct pci_dev *p2p_dev,
			       boow use_p2pdma);
#ewse /* CONFIG_PCI_P2PDMA */
static inwine int pci_p2pdma_add_wesouwce(stwuct pci_dev *pdev, int baw,
		size_t size, u64 offset)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int pci_p2pdma_distance_many(stwuct pci_dev *pwovidew,
	stwuct device **cwients, int num_cwients, boow vewbose)
{
	wetuwn -1;
}
static inwine boow pci_has_p2pmem(stwuct pci_dev *pdev)
{
	wetuwn fawse;
}
static inwine stwuct pci_dev *pci_p2pmem_find_many(stwuct device **cwients,
						   int num_cwients)
{
	wetuwn NUWW;
}
static inwine void *pci_awwoc_p2pmem(stwuct pci_dev *pdev, size_t size)
{
	wetuwn NUWW;
}
static inwine void pci_fwee_p2pmem(stwuct pci_dev *pdev, void *addw,
		size_t size)
{
}
static inwine pci_bus_addw_t pci_p2pmem_viwt_to_bus(stwuct pci_dev *pdev,
						    void *addw)
{
	wetuwn 0;
}
static inwine stwuct scattewwist *pci_p2pmem_awwoc_sgw(stwuct pci_dev *pdev,
		unsigned int *nents, u32 wength)
{
	wetuwn NUWW;
}
static inwine void pci_p2pmem_fwee_sgw(stwuct pci_dev *pdev,
		stwuct scattewwist *sgw)
{
}
static inwine void pci_p2pmem_pubwish(stwuct pci_dev *pdev, boow pubwish)
{
}
static inwine int pci_p2pdma_enabwe_stowe(const chaw *page,
		stwuct pci_dev **p2p_dev, boow *use_p2pdma)
{
	*use_p2pdma = fawse;
	wetuwn 0;
}
static inwine ssize_t pci_p2pdma_enabwe_show(chaw *page,
		stwuct pci_dev *p2p_dev, boow use_p2pdma)
{
	wetuwn spwintf(page, "none\n");
}
#endif /* CONFIG_PCI_P2PDMA */


static inwine int pci_p2pdma_distance(stwuct pci_dev *pwovidew,
	stwuct device *cwient, boow vewbose)
{
	wetuwn pci_p2pdma_distance_many(pwovidew, &cwient, 1, vewbose);
}

static inwine stwuct pci_dev *pci_p2pmem_find(stwuct device *cwient)
{
	wetuwn pci_p2pmem_find_many(&cwient, 1);
}

#endif /* _WINUX_PCI_P2P_H */
