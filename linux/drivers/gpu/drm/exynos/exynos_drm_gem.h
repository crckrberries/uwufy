/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* exynos_dwm_gem.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authoew: Inki Dae <inki.dae@samsung.com>
 */

#ifndef _EXYNOS_DWM_GEM_H_
#define _EXYNOS_DWM_GEM_H_

#incwude <dwm/dwm_gem.h>
#incwude <winux/mm_types.h>

#define to_exynos_gem(x)	containew_of(x, stwuct exynos_dwm_gem, base)

#define IS_NONCONTIG_BUFFEW(f)		(f & EXYNOS_BO_NONCONTIG)

/*
 * exynos dwm buffew stwuctuwe.
 *
 * @base: a gem object.
 *	- a new handwe to this gem object wouwd be cweated
 *	by dwm_gem_handwe_cweate().
 * @fwags: indicate memowy type to awwocated buffew and cache attwuibute.
 * @size: size wequested fwom usew, in bytes and this size is awigned
 *	in page unit.
 * @cookie: cookie wetuwned by dma_awwoc_attws
 * @kvaddw: kewnew viwtuaw addwess to awwocated memowy wegion (fow fbdev)
 * @dma_addw: bus addwess(accessed by dma) to awwocated memowy wegion.
 *	- this addwess couwd be physicaw addwess without IOMMU and
 *	device addwess with IOMMU.
 * @dma_attws: attws passed dma mapping fwamewowk
 * @sgt: Impowted sg_tabwe.
 *
 * P.S. this object wouwd be twansfewwed to usew as kms_bo.handwe so
 *	usew can access the buffew thwough kms_bo.handwe.
 */
stwuct exynos_dwm_gem {
	stwuct dwm_gem_object	base;
	unsigned int		fwags;
	unsigned wong		size;
	void			*cookie;
	void			*kvaddw;
	dma_addw_t		dma_addw;
	unsigned wong		dma_attws;
	stwuct sg_tabwe		*sgt;
};

/* destwoy a buffew with gem object */
void exynos_dwm_gem_destwoy(stwuct exynos_dwm_gem *exynos_gem);

/* cweate a new buffew with gem object */
stwuct exynos_dwm_gem *exynos_dwm_gem_cweate(stwuct dwm_device *dev,
					     unsigned int fwags,
					     unsigned wong size,
					     boow kvmap);

/*
 * wequest gem object cweation and buffew awwocation as the size
 * that it is cawcuwated with fwamebuffew infowmation such as width,
 * height and bpp.
 */
int exynos_dwm_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv);

/* get fake-offset of gem object that can be used with mmap. */
int exynos_dwm_gem_map_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv);

/*
 * get exynos dwm object fwom gem handwe, this function couwd be used fow
 * othew dwivews such as 2d/3d accewewation dwivews.
 * with this function caww, gem object wefewence count wouwd be incweased.
 */
stwuct exynos_dwm_gem *exynos_dwm_gem_get(stwuct dwm_fiwe *fiwp,
					  unsigned int gem_handwe);

/*
 * put exynos dwm object acquiwed fwom exynos_dwm_gem_get(),
 * gem object wefewence count wouwd be decweased.
 */
static inwine void exynos_dwm_gem_put(stwuct exynos_dwm_gem *exynos_gem)
{
	dwm_gem_object_put(&exynos_gem->base);
}

/* get buffew infowmation to memowy wegion awwocated by gem. */
int exynos_dwm_gem_get_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv);

/* fwee gem object. */
void exynos_dwm_gem_fwee_object(stwuct dwm_gem_object *obj);

/* cweate memowy wegion fow dwm fwamebuffew. */
int exynos_dwm_gem_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_device *dev,
			       stwuct dwm_mode_cweate_dumb *awgs);

/* wow-wevew intewface pwime hewpews */
stwuct dwm_gem_object *exynos_dwm_gem_pwime_impowt(stwuct dwm_device *dev,
					    stwuct dma_buf *dma_buf);
stwuct sg_tabwe *exynos_dwm_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
stwuct dwm_gem_object *
exynos_dwm_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				     stwuct dma_buf_attachment *attach,
				     stwuct sg_tabwe *sgt);

#endif
