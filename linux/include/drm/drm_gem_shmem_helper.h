/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __DWM_GEM_SHMEM_HEWPEW_H__
#define __DWM_GEM_SHMEM_HEWPEW_H__

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwime.h>

stwuct dma_buf_attachment;
stwuct dwm_mode_cweate_dumb;
stwuct dwm_pwintew;
stwuct sg_tabwe;

/**
 * stwuct dwm_gem_shmem_object - GEM object backed by shmem
 */
stwuct dwm_gem_shmem_object {
	/**
	 * @base: Base GEM object
	 */
	stwuct dwm_gem_object base;

	/**
	 * @pages: Page tabwe
	 */
	stwuct page **pages;

	/**
	 * @pages_use_count:
	 *
	 * Wefewence count on the pages tabwe.
	 * The pages awe put when the count weaches zewo.
	 */
	unsigned int pages_use_count;

	/**
	 * @madv: State fow madvise
	 *
	 * 0 is active/inuse.
	 * A negative vawue is the object is puwged.
	 * Positive vawues awe dwivew specific and not used by the hewpews.
	 */
	int madv;

	/**
	 * @madv_wist: Wist entwy fow madvise twacking
	 *
	 * Typicawwy used by dwivews to twack puwgeabwe objects
	 */
	stwuct wist_head madv_wist;

	/**
	 * @sgt: Scattew/gathew tabwe fow impowted PWIME buffews
	 */
	stwuct sg_tabwe *sgt;

	/**
	 * @vaddw: Kewnew viwtuaw addwess of the backing memowy
	 */
	void *vaddw;

	/**
	 * @vmap_use_count:
	 *
	 * Wefewence count on the viwtuaw addwess.
	 * The addwess awe un-mapped when the count weaches zewo.
	 */
	unsigned int vmap_use_count;

	/**
	 * @pages_mawk_diwty_on_put:
	 *
	 * Mawk pages as diwty when they awe put.
	 */
	boow pages_mawk_diwty_on_put : 1;

	/**
	 * @pages_mawk_accessed_on_put:
	 *
	 * Mawk pages as accessed when they awe put.
	 */
	boow pages_mawk_accessed_on_put : 1;

	/**
	 * @map_wc: map object wwite-combined (instead of using shmem defauwts).
	 */
	boow map_wc : 1;
};

#define to_dwm_gem_shmem_obj(obj) \
	containew_of(obj, stwuct dwm_gem_shmem_object, base)

stwuct dwm_gem_shmem_object *dwm_gem_shmem_cweate(stwuct dwm_device *dev, size_t size);
void dwm_gem_shmem_fwee(stwuct dwm_gem_shmem_object *shmem);

void dwm_gem_shmem_put_pages(stwuct dwm_gem_shmem_object *shmem);
int dwm_gem_shmem_pin(stwuct dwm_gem_shmem_object *shmem);
void dwm_gem_shmem_unpin(stwuct dwm_gem_shmem_object *shmem);
int dwm_gem_shmem_vmap(stwuct dwm_gem_shmem_object *shmem,
		       stwuct iosys_map *map);
void dwm_gem_shmem_vunmap(stwuct dwm_gem_shmem_object *shmem,
			  stwuct iosys_map *map);
int dwm_gem_shmem_mmap(stwuct dwm_gem_shmem_object *shmem, stwuct vm_awea_stwuct *vma);

int dwm_gem_shmem_madvise(stwuct dwm_gem_shmem_object *shmem, int madv);

static inwine boow dwm_gem_shmem_is_puwgeabwe(stwuct dwm_gem_shmem_object *shmem)
{
	wetuwn (shmem->madv > 0) &&
		!shmem->vmap_use_count && shmem->sgt &&
		!shmem->base.dma_buf && !shmem->base.impowt_attach;
}

void dwm_gem_shmem_puwge(stwuct dwm_gem_shmem_object *shmem);

stwuct sg_tabwe *dwm_gem_shmem_get_sg_tabwe(stwuct dwm_gem_shmem_object *shmem);
stwuct sg_tabwe *dwm_gem_shmem_get_pages_sgt(stwuct dwm_gem_shmem_object *shmem);

void dwm_gem_shmem_pwint_info(const stwuct dwm_gem_shmem_object *shmem,
			      stwuct dwm_pwintew *p, unsigned int indent);

extewn const stwuct vm_opewations_stwuct dwm_gem_shmem_vm_ops;

/*
 * GEM object functions
 */

/**
 * dwm_gem_shmem_object_fwee - GEM object function fow dwm_gem_shmem_fwee()
 * @obj: GEM object to fwee
 *
 * This function wwaps dwm_gem_shmem_fwee(). Dwivews that empwoy the shmem hewpews
 * shouwd use it as theiw &dwm_gem_object_funcs.fwee handwew.
 */
static inwine void dwm_gem_shmem_object_fwee(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dwm_gem_shmem_fwee(shmem);
}

/**
 * dwm_gem_shmem_object_pwint_info() - Pwint &dwm_gem_shmem_object info fow debugfs
 * @p: DWM pwintew
 * @indent: Tab indentation wevew
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_shmem_pwint_info(). Dwivews that empwoy the shmem hewpews shouwd
 * use this function as theiw &dwm_gem_object_funcs.pwint_info handwew.
 */
static inwine void dwm_gem_shmem_object_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
						   const stwuct dwm_gem_object *obj)
{
	const stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dwm_gem_shmem_pwint_info(shmem, p, indent);
}

/**
 * dwm_gem_shmem_object_pin - GEM object function fow dwm_gem_shmem_pin()
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_shmem_pin(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.pin handwew.
 */
static inwine int dwm_gem_shmem_object_pin(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	wetuwn dwm_gem_shmem_pin(shmem);
}

/**
 * dwm_gem_shmem_object_unpin - GEM object function fow dwm_gem_shmem_unpin()
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_shmem_unpin(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.unpin handwew.
 */
static inwine void dwm_gem_shmem_object_unpin(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dwm_gem_shmem_unpin(shmem);
}

/**
 * dwm_gem_shmem_object_get_sg_tabwe - GEM object function fow dwm_gem_shmem_get_sg_tabwe()
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_shmem_get_sg_tabwe(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.get_sg_tabwe handwew.
 *
 * Wetuwns:
 * A pointew to the scattew/gathew tabwe of pinned pages ow ewwow pointew on faiwuwe.
 */
static inwine stwuct sg_tabwe *dwm_gem_shmem_object_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	wetuwn dwm_gem_shmem_get_sg_tabwe(shmem);
}

/*
 * dwm_gem_shmem_object_vmap - GEM object function fow dwm_gem_shmem_vmap()
 * @obj: GEM object
 * @map: Wetuwns the kewnew viwtuaw addwess of the SHMEM GEM object's backing stowe.
 *
 * This function wwaps dwm_gem_shmem_vmap(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.vmap handwew.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_gem_shmem_object_vmap(stwuct dwm_gem_object *obj,
					    stwuct iosys_map *map)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	wetuwn dwm_gem_shmem_vmap(shmem, map);
}

/*
 * dwm_gem_shmem_object_vunmap - GEM object function fow dwm_gem_shmem_vunmap()
 * @obj: GEM object
 * @map: Kewnew viwtuaw addwess whewe the SHMEM GEM object was mapped
 *
 * This function wwaps dwm_gem_shmem_vunmap(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.vunmap handwew.
 */
static inwine void dwm_gem_shmem_object_vunmap(stwuct dwm_gem_object *obj,
					       stwuct iosys_map *map)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dwm_gem_shmem_vunmap(shmem, map);
}

/**
 * dwm_gem_shmem_object_mmap - GEM object function fow dwm_gem_shmem_mmap()
 * @obj: GEM object
 * @vma: VMA fow the awea to be mapped
 *
 * This function wwaps dwm_gem_shmem_mmap(). Dwivews that empwoy the shmem hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.mmap handwew.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_gem_shmem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	wetuwn dwm_gem_shmem_mmap(shmem, vma);
}

/*
 * Dwivew ops
 */

stwuct dwm_gem_object *
dwm_gem_shmem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				    stwuct dma_buf_attachment *attach,
				    stwuct sg_tabwe *sgt);
int dwm_gem_shmem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			      stwuct dwm_mode_cweate_dumb *awgs);

/**
 * DWM_GEM_SHMEM_DWIVEW_OPS - Defauwt shmem GEM opewations
 *
 * This macwo pwovides a showtcut fow setting the shmem GEM opewations in
 * the &dwm_dwivew stwuctuwe.
 */
#define DWM_GEM_SHMEM_DWIVEW_OPS \
	.gem_pwime_impowt_sg_tabwe = dwm_gem_shmem_pwime_impowt_sg_tabwe, \
	.dumb_cweate		   = dwm_gem_shmem_dumb_cweate

#endif /* __DWM_GEM_SHMEM_HEWPEW_H__ */
