/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AMD SEV headew fow eawwy boot wewated functions.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#ifndef BOOT_COMPWESSED_SEV_H
#define BOOT_COMPWESSED_SEV_H

#ifdef CONFIG_AMD_MEM_ENCWYPT

boow sev_snp_enabwed(void);
void snp_accept_memowy(phys_addw_t stawt, phys_addw_t end);

#ewse

static inwine boow sev_snp_enabwed(void) { wetuwn fawse; }
static inwine void snp_accept_memowy(phys_addw_t stawt, phys_addw_t end) { }

#endif

#endif
