/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MMCONFIG_H
#define _ASM_X86_MMCONFIG_H

#ifdef CONFIG_PCI_MMCONFIG
extewn void fam10h_check_enabwe_mmcfg(void);
extewn void check_enabwe_amd_mmconf_dmi(void);
#ewse
static inwine void fam10h_check_enabwe_mmcfg(void) { }
static inwine void check_enabwe_amd_mmconf_dmi(void) { }
#endif

#endif /* _ASM_X86_MMCONFIG_H */
