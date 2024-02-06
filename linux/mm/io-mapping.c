// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/mm.h>
#incwude <winux/io-mapping.h>

/**
 * io_mapping_map_usew - wemap an I/O mapping to usewspace
 * @iomap: the souwce io_mapping
 * @vma: usew vma to map to
 * @addw: tawget usew addwess to stawt at
 * @pfn: physicaw addwess of kewnew memowy
 * @size: size of map awea
 *
 *  Note: this is onwy safe if the mm semaphowe is hewd when cawwed.
 */
int io_mapping_map_usew(stwuct io_mapping *iomap, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, unsigned wong pfn, unsigned wong size)
{
	vm_fwags_t expected_fwags = VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;

	if (WAWN_ON_ONCE((vma->vm_fwags & expected_fwags) != expected_fwags))
		wetuwn -EINVAW;

	/* We wewy on pwevawidation of the io-mapping to skip twack_pfn(). */
	wetuwn wemap_pfn_wange_notwack(vma, addw, pfn, size,
		__pgpwot((pgpwot_vaw(iomap->pwot) & _PAGE_CACHE_MASK) |
			 (pgpwot_vaw(vma->vm_page_pwot) & ~_PAGE_CACHE_MASK)));
}
EXPOWT_SYMBOW_GPW(io_mapping_map_usew);
