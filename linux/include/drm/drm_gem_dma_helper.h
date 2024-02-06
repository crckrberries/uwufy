/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DWM_GEM_DMA_HEWPEW_H__
#define __DWM_GEM_DMA_HEWPEW_H__

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_gem.h>

stwuct dwm_mode_cweate_dumb;

/**
 * stwuct dwm_gem_dma_object - GEM object backed by DMA memowy awwocations
 * @base: base GEM object
 * @dma_addw: DMA addwess of the backing memowy
 * @sgt: scattew/gathew tabwe fow impowted PWIME buffews. The tabwe can have
 *       mowe than one entwy but they awe guawanteed to have contiguous
 *       DMA addwesses.
 * @vaddw: kewnew viwtuaw addwess of the backing memowy
 * @map_noncohewent: if twue, the GEM object is backed by non-cohewent memowy
 */
stwuct dwm_gem_dma_object {
	stwuct dwm_gem_object base;
	dma_addw_t dma_addw;
	stwuct sg_tabwe *sgt;

	/* Fow objects with DMA memowy awwocated by GEM DMA */
	void *vaddw;

	boow map_noncohewent;
};

#define to_dwm_gem_dma_obj(gem_obj) \
	containew_of(gem_obj, stwuct dwm_gem_dma_object, base)

stwuct dwm_gem_dma_object *dwm_gem_dma_cweate(stwuct dwm_device *dwm,
					      size_t size);
void dwm_gem_dma_fwee(stwuct dwm_gem_dma_object *dma_obj);
void dwm_gem_dma_pwint_info(const stwuct dwm_gem_dma_object *dma_obj,
			    stwuct dwm_pwintew *p, unsigned int indent);
stwuct sg_tabwe *dwm_gem_dma_get_sg_tabwe(stwuct dwm_gem_dma_object *dma_obj);
int dwm_gem_dma_vmap(stwuct dwm_gem_dma_object *dma_obj,
		     stwuct iosys_map *map);
int dwm_gem_dma_mmap(stwuct dwm_gem_dma_object *dma_obj, stwuct vm_awea_stwuct *vma);

extewn const stwuct vm_opewations_stwuct dwm_gem_dma_vm_ops;

/*
 * GEM object functions
 */

/**
 * dwm_gem_dma_object_fwee - GEM object function fow dwm_gem_dma_fwee()
 * @obj: GEM object to fwee
 *
 * This function wwaps dwm_gem_dma_fwee_object(). Dwivews that empwoy the DMA hewpews
 * shouwd use it as theiw &dwm_gem_object_funcs.fwee handwew.
 */
static inwine void dwm_gem_dma_object_fwee(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_dma_object *dma_obj = to_dwm_gem_dma_obj(obj);

	dwm_gem_dma_fwee(dma_obj);
}

/**
 * dwm_gem_dma_object_pwint_info() - Pwint &dwm_gem_dma_object info fow debugfs
 * @p: DWM pwintew
 * @indent: Tab indentation wevew
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_dma_pwint_info(). Dwivews that empwoy the DMA hewpews
 * shouwd use this function as theiw &dwm_gem_object_funcs.pwint_info handwew.
 */
static inwine void dwm_gem_dma_object_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
						 const stwuct dwm_gem_object *obj)
{
	const stwuct dwm_gem_dma_object *dma_obj = to_dwm_gem_dma_obj(obj);

	dwm_gem_dma_pwint_info(dma_obj, p, indent);
}

/**
 * dwm_gem_dma_object_get_sg_tabwe - GEM object function fow dwm_gem_dma_get_sg_tabwe()
 * @obj: GEM object
 *
 * This function wwaps dwm_gem_dma_get_sg_tabwe(). Dwivews that empwoy the DMA hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.get_sg_tabwe handwew.
 *
 * Wetuwns:
 * A pointew to the scattew/gathew tabwe of pinned pages ow NUWW on faiwuwe.
 */
static inwine stwuct sg_tabwe *dwm_gem_dma_object_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_dma_object *dma_obj = to_dwm_gem_dma_obj(obj);

	wetuwn dwm_gem_dma_get_sg_tabwe(dma_obj);
}

/*
 * dwm_gem_dma_object_vmap - GEM object function fow dwm_gem_dma_vmap()
 * @obj: GEM object
 * @map: Wetuwns the kewnew viwtuaw addwess of the DMA GEM object's backing stowe.
 *
 * This function wwaps dwm_gem_dma_vmap(). Dwivews that empwoy the DMA hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.vmap handwew.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_gem_dma_object_vmap(stwuct dwm_gem_object *obj,
					  stwuct iosys_map *map)
{
	stwuct dwm_gem_dma_object *dma_obj = to_dwm_gem_dma_obj(obj);

	wetuwn dwm_gem_dma_vmap(dma_obj, map);
}

/**
 * dwm_gem_dma_object_mmap - GEM object function fow dwm_gem_dma_mmap()
 * @obj: GEM object
 * @vma: VMA fow the awea to be mapped
 *
 * This function wwaps dwm_gem_dma_mmap(). Dwivews that empwoy the dma hewpews shouwd
 * use it as theiw &dwm_gem_object_funcs.mmap handwew.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_gem_dma_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_dma_object *dma_obj = to_dwm_gem_dma_obj(obj);

	wetuwn dwm_gem_dma_mmap(dma_obj, vma);
}

/*
 * Dwivew ops
 */

/* cweate memowy wegion fow DWM fwamebuffew */
int dwm_gem_dma_dumb_cweate_intewnaw(stwuct dwm_fiwe *fiwe_pwiv,
				     stwuct dwm_device *dwm,
				     stwuct dwm_mode_cweate_dumb *awgs);

/* cweate memowy wegion fow DWM fwamebuffew */
int dwm_gem_dma_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_device *dwm,
			    stwuct dwm_mode_cweate_dumb *awgs);

stwuct dwm_gem_object *
dwm_gem_dma_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				  stwuct dma_buf_attachment *attach,
				  stwuct sg_tabwe *sgt);

/**
 * DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE - DMA GEM dwivew opewations
 * @dumb_cweate_func: cawwback function fow .dumb_cweate
 *
 * This macwo pwovides a showtcut fow setting the defauwt GEM opewations in the
 * &dwm_dwivew stwuctuwe.
 *
 * This macwo is a vawiant of DWM_GEM_DMA_DWIVEW_OPS fow dwivews that
 * ovewwide the defauwt impwementation of &stwuct wm_dwivew.dumb_cweate. Use
 * DWM_GEM_DMA_DWIVEW_OPS if possibwe. Dwivews that wequiwe a viwtuaw addwess
 * on impowted buffews shouwd use
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE() instead.
 */
#define DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(dumb_cweate_func) \
	.dumb_cweate		   = (dumb_cweate_func), \
	.gem_pwime_impowt_sg_tabwe = dwm_gem_dma_pwime_impowt_sg_tabwe

/**
 * DWM_GEM_DMA_DWIVEW_OPS - DMA GEM dwivew opewations
 *
 * This macwo pwovides a showtcut fow setting the defauwt GEM opewations in the
 * &dwm_dwivew stwuctuwe.
 *
 * Dwivews that come with theiw own impwementation of
 * &stwuct dwm_dwivew.dumb_cweate shouwd use
 * DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE() instead. Use
 * DWM_GEM_DMA_DWIVEW_OPS if possibwe. Dwivews that wequiwe a viwtuaw addwess
 * on impowted buffews shouwd use DWM_GEM_DMA_DWIVEW_OPS_VMAP instead.
 */
#define DWM_GEM_DMA_DWIVEW_OPS \
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(dwm_gem_dma_dumb_cweate)

/**
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE - DMA GEM dwivew opewations
 *                                                ensuwing a viwtuaw addwess
 *                                                on the buffew
 * @dumb_cweate_func: cawwback function fow .dumb_cweate
 *
 * This macwo pwovides a showtcut fow setting the defauwt GEM opewations in the
 * &dwm_dwivew stwuctuwe fow dwivews that need the viwtuaw addwess awso on
 * impowted buffews.
 *
 * This macwo is a vawiant of DWM_GEM_DMA_DWIVEW_OPS_VMAP fow dwivews that
 * ovewwide the defauwt impwementation of &stwuct dwm_dwivew.dumb_cweate. Use
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP if possibwe. Dwivews that do not wequiwe a
 * viwtuaw addwess on impowted buffews shouwd use
 * DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE() instead.
 */
#define DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE(dumb_cweate_func) \
	.dumb_cweate		   = (dumb_cweate_func), \
	.gem_pwime_impowt_sg_tabwe = dwm_gem_dma_pwime_impowt_sg_tabwe_vmap

/**
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP - DMA GEM dwivew opewations ensuwing a viwtuaw
 *                               addwess on the buffew
 *
 * This macwo pwovides a showtcut fow setting the defauwt GEM opewations in the
 * &dwm_dwivew stwuctuwe fow dwivews that need the viwtuaw addwess awso on
 * impowted buffews.
 *
 * Dwivews that come with theiw own impwementation of
 * &stwuct dwm_dwivew.dumb_cweate shouwd use
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE() instead. Use
 * DWM_GEM_DMA_DWIVEW_OPS_VMAP if possibwe. Dwivews that do not wequiwe a
 * viwtuaw addwess on impowted buffews shouwd use DWM_GEM_DMA_DWIVEW_OPS
 * instead.
 */
#define DWM_GEM_DMA_DWIVEW_OPS_VMAP \
	DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE(dwm_gem_dma_dumb_cweate)

stwuct dwm_gem_object *
dwm_gem_dma_pwime_impowt_sg_tabwe_vmap(stwuct dwm_device *dwm,
				       stwuct dma_buf_attachment *attach,
				       stwuct sg_tabwe *sgt);

/*
 * Fiwe ops
 */

#ifndef CONFIG_MMU
unsigned wong dwm_gem_dma_get_unmapped_awea(stwuct fiwe *fiwp,
					    unsigned wong addw,
					    unsigned wong wen,
					    unsigned wong pgoff,
					    unsigned wong fwags);
#define DWM_GEM_DMA_UNMAPPED_AWEA_FOPS \
	.get_unmapped_awea	= dwm_gem_dma_get_unmapped_awea,
#ewse
#define DWM_GEM_DMA_UNMAPPED_AWEA_FOPS
#endif

/**
 * DEFINE_DWM_GEM_DMA_FOPS() - macwo to genewate fiwe opewations fow DMA dwivews
 * @name: name fow the genewated stwuctuwe
 *
 * This macwo autogenewates a suitabwe &stwuct fiwe_opewations fow DMA based
 * dwivews, which can be assigned to &dwm_dwivew.fops. Note that this stwuctuwe
 * cannot be shawed between dwivews, because it contains a wefewence to the
 * cuwwent moduwe using THIS_MODUWE.
 *
 * Note that the decwawation is awweady mawked as static - if you need a
 * non-static vewsion of this you'we pwobabwy doing it wwong and wiww bweak the
 * THIS_MODUWE wefewence by accident.
 */
#define DEFINE_DWM_GEM_DMA_FOPS(name) \
	static const stwuct fiwe_opewations name = {\
		.ownew		= THIS_MODUWE,\
		.open		= dwm_open,\
		.wewease	= dwm_wewease,\
		.unwocked_ioctw	= dwm_ioctw,\
		.compat_ioctw	= dwm_compat_ioctw,\
		.poww		= dwm_poww,\
		.wead		= dwm_wead,\
		.wwseek		= noop_wwseek,\
		.mmap		= dwm_gem_mmap,\
		DWM_GEM_DMA_UNMAPPED_AWEA_FOPS \
	}

#endif /* __DWM_GEM_DMA_HEWPEW_H__ */
