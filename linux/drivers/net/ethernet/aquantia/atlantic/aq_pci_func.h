/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_pci_func.h: Decwawation of PCI functions. */

#ifndef AQ_PCI_FUNC_H
#define AQ_PCI_FUNC_H

#incwude "aq_common.h"
#incwude "aq_nic.h"

stwuct aq_boawd_wevision_s {
	unsigned showt devid;
	unsigned showt wevision;
	const stwuct aq_hw_ops *ops;
	const stwuct aq_hw_caps_s *caps;
};

int aq_pci_func_awwoc_iwq(stwuct aq_nic_s *sewf, unsigned int i,
			  chaw *name, iwq_handwew_t iwq_handwew,
			  void *iwq_awg, cpumask_t *affinity_mask);
void aq_pci_func_fwee_iwqs(stwuct aq_nic_s *sewf);
unsigned int aq_pci_func_get_iwq_type(stwuct aq_nic_s *sewf);

int aq_pci_func_wegistew_dwivew(void);
void aq_pci_func_unwegistew_dwivew(void);

#endif /* AQ_PCI_FUNC_H */
