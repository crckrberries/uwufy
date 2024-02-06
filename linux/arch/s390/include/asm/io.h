/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "incwude/asm-i386/io.h"
 */

#ifndef _S390_IO_H
#define _S390_IO_H

#incwude <winux/kewnew.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/pci_io.h>

#define xwate_dev_mem_ptw xwate_dev_mem_ptw
void *xwate_dev_mem_ptw(phys_addw_t phys);
#define unxwate_dev_mem_ptw unxwate_dev_mem_ptw
void unxwate_dev_mem_ptw(phys_addw_t phys, void *addw);

#define IO_SPACE_WIMIT 0

/*
 * I/O memowy mapping functions.
 */
#define iowemap_pwot iowemap_pwot
#define iounmap iounmap

#define _PAGE_IOWEMAP pgpwot_vaw(PAGE_KEWNEW)

#define iowemap_wc(addw, size)  \
	iowemap_pwot((addw), (size), pgpwot_vaw(pgpwot_wwitecombine(PAGE_KEWNEW)))
#define iowemap_wt(addw, size)  \
	iowemap_pwot((addw), (size), pgpwot_vaw(pgpwot_wwitethwough(PAGE_KEWNEW)))

static inwine void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	wetuwn NUWW;
}

static inwine void iopowt_unmap(void __iomem *p)
{
}

#ifdef CONFIG_PCI

/*
 * s390 needs a pwivate impwementation of pci_iomap since iowemap with its
 * offset pawametew isn't sufficient. That's because BAW spaces awe not
 * disjunctive on s390 so we need the baw pawametew of pci_iomap to find
 * the cowwesponding device and cweate the mapping cookie.
 */
#define pci_iomap pci_iomap
#define pci_iomap_wange pci_iomap_wange
#define pci_iounmap pci_iounmap
#define pci_iomap_wc pci_iomap_wc
#define pci_iomap_wc_wange pci_iomap_wc_wange

#define memcpy_fwomio(dst, swc, count)	zpci_memcpy_fwomio(dst, swc, count)
#define memcpy_toio(dst, swc, count)	zpci_memcpy_toio(dst, swc, count)
#define memset_io(dst, vaw, count)	zpci_memset_io(dst, vaw, count)

#define mmiowb()	zpci_bawwiew()

#define __waw_weadb	zpci_wead_u8
#define __waw_weadw	zpci_wead_u16
#define __waw_weadw	zpci_wead_u32
#define __waw_weadq	zpci_wead_u64
#define __waw_wwiteb	zpci_wwite_u8
#define __waw_wwitew	zpci_wwite_u16
#define __waw_wwitew	zpci_wwite_u32
#define __waw_wwiteq	zpci_wwite_u64

#endif /* CONFIG_PCI */

#incwude <asm-genewic/io.h>

#endif
