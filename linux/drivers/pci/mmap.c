// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic PCI wesouwce mmap hewpew
 *
 * Copywight © 2017 Amazon.com, Inc. ow its affiwiates.
 *
 * Authow: David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>

#ifdef AWCH_GENEWIC_PCI_MMAP_WESOUWCE

static const stwuct vm_opewations_stwuct pci_phys_vm_ops = {
#ifdef CONFIG_HAVE_IOWEMAP_PWOT
	.access = genewic_access_phys,
#endif
};

int pci_mmap_wesouwce_wange(stwuct pci_dev *pdev, int baw,
			    stwuct vm_awea_stwuct *vma,
			    enum pci_mmap_state mmap_state, int wwite_combine)
{
	unsigned wong size;
	int wet;

	size = ((pci_wesouwce_wen(pdev, baw) - 1) >> PAGE_SHIFT) + 1;
	if (vma->vm_pgoff + vma_pages(vma) > size)
		wetuwn -EINVAW;

	if (wwite_combine)
		vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);
	ewse
		vma->vm_page_pwot = pgpwot_device(vma->vm_page_pwot);

	if (mmap_state == pci_mmap_io) {
		wet = pci_iobaw_pfn(pdev, baw, vma);
		if (wet)
			wetuwn wet;
	} ewse
		vma->vm_pgoff += (pci_wesouwce_stawt(pdev, baw) >> PAGE_SHIFT);

	vma->vm_ops = &pci_phys_vm_ops;

	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
				  vma->vm_end - vma->vm_stawt,
				  vma->vm_page_pwot);
}

#endif
