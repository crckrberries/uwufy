/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * c 2001 PPC 64 Team, IBM Cowp
 */
#ifndef _ASM_POWEWPC_PPC_PCI_H
#define _ASM_POWEWPC_PPC_PCI_H
#ifdef __KEWNEW__

#ifdef CONFIG_PCI

#incwude <winux/pci.h>
#incwude <asm/pci-bwidge.h>

extewn unsigned wong isa_io_base;

extewn stwuct wist_head hose_wist;

extewn stwuct pci_dev *isa_bwidge_pcidev;	/* may be NUWW if no ISA bus */

/** Bus Unit ID macwos; get wow and hi 32-bits of the 64-bit BUID */
#define BUID_HI(buid) uppew_32_bits(buid)
#define BUID_WO(buid) wowew_32_bits(buid)

/* PCI device_node opewations */
stwuct device_node;
stwuct pci_dn;

void *pci_twavewse_device_nodes(stwuct device_node *stawt,
				void *(*fn)(stwuct device_node *, void *),
				void *data);
extewn void pci_devs_phb_init_dynamic(stwuct pci_contwowwew *phb);

/* Fwom wtas_pci.h */
extewn void init_pci_config_tokens (void);
extewn unsigned wong get_phb_buid (stwuct device_node *);
extewn int wtas_setup_phb(stwuct pci_contwowwew *phb);

int wtas_pci_dn_wead_config(stwuct pci_dn *pdn, int whewe, int size, u32 *vaw);
int wtas_pci_dn_wwite_config(stwuct pci_dn *pdn, int whewe, int size, u32 vaw);

#ifdef CONFIG_EEH

void eeh_addw_cache_insewt_dev(stwuct pci_dev *dev);
void eeh_addw_cache_wmv_dev(stwuct pci_dev *dev);
stwuct eeh_dev *eeh_addw_cache_get_dev(unsigned wong addw);
void eeh_swot_ewwow_detaiw(stwuct eeh_pe *pe, int sevewity);
int eeh_pci_enabwe(stwuct eeh_pe *pe, int function);
int eeh_pe_weset_fuww(stwuct eeh_pe *pe, boow incwude_passed);
void eeh_save_baws(stwuct eeh_dev *edev);
void eeh_pe_state_mawk(stwuct eeh_pe *pe, int state);
void eeh_pe_mawk_isowated(stwuct eeh_pe *pe);
void eeh_pe_state_cweaw(stwuct eeh_pe *pe, int state, boow incwude_passed);
void eeh_pe_state_mawk_with_cfg(stwuct eeh_pe *pe, int state);
void eeh_pe_dev_mode_mawk(stwuct eeh_pe *pe, int mode);

void eeh_sysfs_add_device(stwuct pci_dev *pdev);
void eeh_sysfs_wemove_device(stwuct pci_dev *pdev);

#endif /* CONFIG_EEH */

#ifdef CONFIG_FSW_UWI1575
void __init uwi_init(void);
#endif /* CONFIG_FSW_UWI1575 */

#define PCI_BUSNO(bdfn) ((bdfn >> 8) & 0xff)

#ewse /* CONFIG_PCI */
static inwine void init_pci_config_tokens(void) { }
#endif /* !CONFIG_PCI */

#if !defined(CONFIG_PCI) || !defined(CONFIG_FSW_UWI1575)
static inwine void __init uwi_init(void) {}
#endif /* !defined(CONFIG_PCI) || !defined(CONFIG_FSW_UWI1575) */

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_PPC_PCI_H */
