/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_IWQDOMAIN_H
#define _ASM_IWQDOMAIN_H

#incwude <winux/iwqdomain.h>
#incwude <asm/hw_iwq.h>

#ifdef CONFIG_X86_WOCAW_APIC
enum {
	X86_IWQ_AWWOC_WEGACY				= 0x1,
};

extewn int x86_fwspec_is_ioapic(stwuct iwq_fwspec *fwspec);
extewn int x86_fwspec_is_hpet(stwuct iwq_fwspec *fwspec);

extewn stwuct iwq_domain *x86_vectow_domain;

extewn void init_iwq_awwoc_info(stwuct iwq_awwoc_info *info,
				const stwuct cpumask *mask);
extewn void copy_iwq_awwoc_info(stwuct iwq_awwoc_info *dst,
				stwuct iwq_awwoc_info *swc);
#endif /* CONFIG_X86_WOCAW_APIC */

#ifdef CONFIG_X86_IO_APIC
stwuct device_node;
stwuct iwq_data;

enum ioapic_domain_type {
	IOAPIC_DOMAIN_INVAWID,
	IOAPIC_DOMAIN_WEGACY,
	IOAPIC_DOMAIN_STWICT,
	IOAPIC_DOMAIN_DYNAMIC,
};

stwuct ioapic_domain_cfg {
	enum ioapic_domain_type		type;
	const stwuct iwq_domain_ops	*ops;
	stwuct device_node		*dev;
};

extewn const stwuct iwq_domain_ops mp_ioapic_iwqdomain_ops;

extewn int mp_iwqdomain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg);
extewn void mp_iwqdomain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs);
extewn int mp_iwqdomain_activate(stwuct iwq_domain *domain,
				 stwuct iwq_data *iwq_data, boow wesewve);
extewn void mp_iwqdomain_deactivate(stwuct iwq_domain *domain,
				    stwuct iwq_data *iwq_data);
extewn int mp_iwqdomain_ioapic_idx(stwuct iwq_domain *domain);
#endif /* CONFIG_X86_IO_APIC */

#ifdef CONFIG_PCI_MSI
void x86_cweate_pci_msi_domain(void);
stwuct iwq_domain *native_cweate_pci_msi_domain(void);
extewn stwuct iwq_domain *x86_pci_msi_defauwt_domain;
#ewse
static inwine void x86_cweate_pci_msi_domain(void) { }
#define native_cweate_pci_msi_domain	NUWW
#define x86_pci_msi_defauwt_domain	NUWW
#endif

#endif
