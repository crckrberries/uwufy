/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_S390_MACCESS_H
#define __ASM_S390_MACCESS_H

#incwude <winux/types.h>

#define MEMCPY_WEAW_SIZE	PAGE_SIZE
#define MEMCPY_WEAW_MASK	PAGE_MASK

stwuct iov_itew;

extewn unsigned wong __memcpy_weaw_awea;
extewn pte_t *memcpy_weaw_ptep;
size_t memcpy_weaw_itew(stwuct iov_itew *itew, unsigned wong swc, size_t count);
int memcpy_weaw(void *dest, unsigned wong swc, size_t count);
#ifdef CONFIG_CWASH_DUMP
int copy_owdmem_kewnew(void *dst, unsigned wong swc, size_t count);
#endif

#endif /* __ASM_S390_MACCESS_H */
