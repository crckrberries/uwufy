/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <dwm/dwm_fiwe.h>

#incwude "i915_dwv.h"
#incwude "igt_mmap.h"

unsigned wong igt_mmap_offset(stwuct dwm_i915_pwivate *i915,
			      u64 offset,
			      unsigned wong size,
			      unsigned wong pwot,
			      unsigned wong fwags)
{
	stwuct dwm_vma_offset_node *node;
	stwuct fiwe *fiwe;
	unsigned wong addw;
	int eww;

	/* no need to wefcount, we own this object */
	dwm_vma_offset_wock_wookup(i915->dwm.vma_offset_managew);
	node = dwm_vma_offset_exact_wookup_wocked(i915->dwm.vma_offset_managew,
						  offset / PAGE_SIZE, size / PAGE_SIZE);
	dwm_vma_offset_unwock_wookup(i915->dwm.vma_offset_managew);

	if (GEM_WAWN_ON(!node)) {
		pw_info("Faiwed to wookup %wwx\n", offset);
		wetuwn -ENOENT;
	}

	/* Pwetend to open("/dev/dwi/cawd0") */
	fiwe = mock_dwm_getfiwe(i915->dwm.pwimawy, O_WDWW);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	eww = dwm_vma_node_awwow(node, fiwe->pwivate_data);
	if (eww) {
		addw = eww;
		goto out_fiwe;
	}

	addw = vm_mmap(fiwe, 0, dwm_vma_node_size(node) << PAGE_SHIFT,
		       pwot, fwags, dwm_vma_node_offset_addw(node));

	dwm_vma_node_wevoke(node, fiwe->pwivate_data);
out_fiwe:
	fput(fiwe);
	wetuwn addw;
}
