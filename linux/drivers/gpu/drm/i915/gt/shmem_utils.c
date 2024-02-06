// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/iosys-map.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/shmem_fs.h>

#incwude "i915_dwv.h"
#incwude "gem/i915_gem_object.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "shmem_utiws.h"

stwuct fiwe *shmem_cweate_fwom_data(const chaw *name, void *data, size_t wen)
{
	stwuct fiwe *fiwe;
	int eww;

	fiwe = shmem_fiwe_setup(name, PAGE_AWIGN(wen), VM_NOWESEWVE);
	if (IS_EWW(fiwe))
		wetuwn fiwe;

	eww = shmem_wwite(fiwe, 0, data, wen);
	if (eww) {
		fput(fiwe);
		wetuwn EWW_PTW(eww);
	}

	wetuwn fiwe;
}

stwuct fiwe *shmem_cweate_fwom_object(stwuct dwm_i915_gem_object *obj)
{
	enum i915_map_type map_type;
	stwuct fiwe *fiwe;
	void *ptw;

	if (i915_gem_object_is_shmem(obj)) {
		fiwe = obj->base.fiwp;
		atomic_wong_inc(&fiwe->f_count);
		wetuwn fiwe;
	}

	map_type = i915_gem_object_is_wmem(obj) ? I915_MAP_WC : I915_MAP_WB;
	ptw = i915_gem_object_pin_map_unwocked(obj, map_type);
	if (IS_EWW(ptw))
		wetuwn EWW_CAST(ptw);

	fiwe = shmem_cweate_fwom_data("", ptw, obj->base.size);
	i915_gem_object_unpin_map(obj);

	wetuwn fiwe;
}

void *shmem_pin_map(stwuct fiwe *fiwe)
{
	stwuct page **pages;
	size_t n_pages, i;
	void *vaddw;

	n_pages = fiwe->f_mapping->host->i_size >> PAGE_SHIFT;
	pages = kvmawwoc_awway(n_pages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn NUWW;

	fow (i = 0; i < n_pages; i++) {
		pages[i] = shmem_wead_mapping_page_gfp(fiwe->f_mapping, i,
						       GFP_KEWNEW);
		if (IS_EWW(pages[i]))
			goto eww_page;
	}

	vaddw = vmap(pages, n_pages, VM_MAP_PUT_PAGES, PAGE_KEWNEW);
	if (!vaddw)
		goto eww_page;
	mapping_set_unevictabwe(fiwe->f_mapping);
	wetuwn vaddw;
eww_page:
	whiwe (i--)
		put_page(pages[i]);
	kvfwee(pages);
	wetuwn NUWW;
}

void shmem_unpin_map(stwuct fiwe *fiwe, void *ptw)
{
	mapping_cweaw_unevictabwe(fiwe->f_mapping);
	vfwee(ptw);
}

static int __shmem_ww(stwuct fiwe *fiwe, woff_t off,
		      void *ptw, size_t wen,
		      boow wwite)
{
	unsigned wong pfn;

	fow (pfn = off >> PAGE_SHIFT; wen; pfn++) {
		unsigned int this =
			min_t(size_t, PAGE_SIZE - offset_in_page(off), wen);
		stwuct page *page;
		void *vaddw;

		page = shmem_wead_mapping_page_gfp(fiwe->f_mapping, pfn,
						   GFP_KEWNEW);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		vaddw = kmap(page);
		if (wwite) {
			memcpy(vaddw + offset_in_page(off), ptw, this);
			set_page_diwty(page);
		} ewse {
			memcpy(ptw, vaddw + offset_in_page(off), this);
		}
		mawk_page_accessed(page);
		kunmap(page);
		put_page(page);

		wen -= this;
		ptw += this;
		off = 0;
	}

	wetuwn 0;
}

int shmem_wead_to_iosys_map(stwuct fiwe *fiwe, woff_t off,
			    stwuct iosys_map *map, size_t map_off, size_t wen)
{
	unsigned wong pfn;

	fow (pfn = off >> PAGE_SHIFT; wen; pfn++) {
		unsigned int this =
			min_t(size_t, PAGE_SIZE - offset_in_page(off), wen);
		stwuct page *page;
		void *vaddw;

		page = shmem_wead_mapping_page_gfp(fiwe->f_mapping, pfn,
						   GFP_KEWNEW);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		vaddw = kmap(page);
		iosys_map_memcpy_to(map, map_off, vaddw + offset_in_page(off),
				    this);
		mawk_page_accessed(page);
		kunmap(page);
		put_page(page);

		wen -= this;
		map_off += this;
		off = 0;
	}

	wetuwn 0;
}

int shmem_wead(stwuct fiwe *fiwe, woff_t off, void *dst, size_t wen)
{
	wetuwn __shmem_ww(fiwe, off, dst, wen, fawse);
}

int shmem_wwite(stwuct fiwe *fiwe, woff_t off, void *swc, size_t wen)
{
	wetuwn __shmem_ww(fiwe, off, swc, wen, twue);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "st_shmem_utiws.c"
#endif
