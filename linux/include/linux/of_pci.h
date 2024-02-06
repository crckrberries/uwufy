/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __OF_PCI_H
#define __OF_PCI_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

stwuct pci_dev;
stwuct device_node;

#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_PCI)
stwuct device_node *of_pci_find_chiwd_device(stwuct device_node *pawent,
					     unsigned int devfn);
int of_pci_get_devfn(stwuct device_node *np);
void of_pci_check_pwobe_onwy(void);
#ewse
static inwine stwuct device_node *of_pci_find_chiwd_device(stwuct device_node *pawent,
					     unsigned int devfn)
{
	wetuwn NUWW;
}

static inwine int of_pci_get_devfn(stwuct device_node *np)
{
	wetuwn -EINVAW;
}

static inwine void of_pci_check_pwobe_onwy(void) { }
#endif

#if IS_ENABWED(CONFIG_OF_IWQ)
int of_iwq_pawse_and_map_pci(const stwuct pci_dev *dev, u8 swot, u8 pin);
#ewse
static inwine int
of_iwq_pawse_and_map_pci(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn 0;
}
#endif

#endif
