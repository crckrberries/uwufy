// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/iosys-map.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_gem_vwam_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_tt.h>

static const stwuct dwm_gem_object_funcs dwm_gem_vwam_object_funcs;

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides &stwuct dwm_gem_vwam_object (GEM VWAM), a GEM
 * buffew object that is backed by video WAM (VWAM). It can be used fow
 * fwamebuffew devices with dedicated memowy.
 *
 * The data stwuctuwe &stwuct dwm_vwam_mm and its hewpews impwement a memowy
 * managew fow simpwe fwamebuffew devices with dedicated video memowy. GEM
 * VWAM buffew objects awe eithew pwaced in the video memowy ow wemain evicted
 * to system memowy.
 *
 * With the GEM intewface usewspace appwications cweate, manage and destwoy
 * gwaphics buffews, such as an on-scween fwamebuffew. GEM does not pwovide
 * an impwementation of these intewfaces. It's up to the DWM dwivew to
 * pwovide an impwementation that suits the hawdwawe. If the hawdwawe device
 * contains dedicated video memowy, the DWM dwivew can use the VWAM hewpew
 * wibwawy. Each active buffew object is stowed in video WAM. Active
 * buffew awe used fow dwawing the cuwwent fwame, typicawwy something wike
 * the fwame's scanout buffew ow the cuwsow image. If thewe's no mowe space
 * weft in VWAM, inactive GEM objects can be moved to system memowy.
 *
 * To initiawize the VWAM hewpew wibwawy caww dwmm_vwam_hewpew_init().
 * The function awwocates and initiawizes an instance of &stwuct dwm_vwam_mm
 * in &stwuct dwm_device.vwam_mm . Use &DWM_GEM_VWAM_DWIVEW to initiawize
 * &stwuct dwm_dwivew and  &DWM_VWAM_MM_FIWE_OPEWATIONS to initiawize
 * &stwuct fiwe_opewations; as iwwustwated bewow.
 *
 * .. code-bwock:: c
 *
 *	stwuct fiwe_opewations fops ={
 *		.ownew = THIS_MODUWE,
 *		DWM_VWAM_MM_FIWE_OPEWATION
 *	};
 *	stwuct dwm_dwivew dwv = {
 *		.dwivew_featuwe = DWM_ ... ,
 *		.fops = &fops,
 *		DWM_GEM_VWAM_DWIVEW
 *	};
 *
 *	int init_dwm_dwivew()
 *	{
 *		stwuct dwm_device *dev;
 *		uint64_t vwam_base;
 *		unsigned wong vwam_size;
 *		int wet;
 *
 *		// setup device, vwam base and size
 *		// ...
 *
 *		wet = dwmm_vwam_hewpew_init(dev, vwam_base, vwam_size);
 *		if (wet)
 *			wetuwn wet;
 *		wetuwn 0;
 *	}
 *
 * This cweates an instance of &stwuct dwm_vwam_mm, expowts DWM usewspace
 * intewfaces fow GEM buffew management and initiawizes fiwe opewations to
 * awwow fow accessing cweated GEM buffews. With this setup, the DWM dwivew
 * manages an awea of video WAM with VWAM MM and pwovides GEM VWAM objects
 * to usewspace.
 *
 * You don't have to cwean up the instance of VWAM MM.
 * dwmm_vwam_hewpew_init() is a managed intewface that instawws a
 * cwean-up handwew to wun duwing the DWM device's wewease.
 *
 * Fow dwawing ow scanout opewations, wsp. buffew objects have to be pinned
 * in video WAM. Caww dwm_gem_vwam_pin() with &DWM_GEM_VWAM_PW_FWAG_VWAM ow
 * &DWM_GEM_VWAM_PW_FWAG_SYSTEM to pin a buffew object in video WAM ow system
 * memowy. Caww dwm_gem_vwam_unpin() to wewease the pinned object aftewwawds.
 *
 * A buffew object that is pinned in video WAM has a fixed addwess within that
 * memowy wegion. Caww dwm_gem_vwam_offset() to wetwieve this vawue. Typicawwy
 * it's used to pwogwam the hawdwawe's scanout engine fow fwamebuffews, set
 * the cuwsow ovewway's image fow a mouse cuwsow, ow use it as input to the
 * hawdwawe's dwawing engine.
 *
 * To access a buffew object's memowy fwom the DWM dwivew, caww
 * dwm_gem_vwam_vmap(). It maps the buffew into kewnew addwess
 * space and wetuwns the memowy addwess. Use dwm_gem_vwam_vunmap() to
 * wewease the mapping.
 */

/*
 * Buffew-objects hewpews
 */

static void dwm_gem_vwam_cweanup(stwuct dwm_gem_vwam_object *gbo)
{
	/* We got hewe via ttm_bo_put(), which means that the
	 * TTM buffew object in 'bo' has awweady been cweaned
	 * up; onwy wewease the GEM object.
	 */

	WAWN_ON(gbo->vmap_use_count);
	WAWN_ON(iosys_map_is_set(&gbo->map));

	dwm_gem_object_wewease(&gbo->bo.base);
}

static void dwm_gem_vwam_destwoy(stwuct dwm_gem_vwam_object *gbo)
{
	dwm_gem_vwam_cweanup(gbo);
	kfwee(gbo);
}

static void ttm_buffew_object_destwoy(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_bo(bo);

	dwm_gem_vwam_destwoy(gbo);
}

static void dwm_gem_vwam_pwacement(stwuct dwm_gem_vwam_object *gbo,
				   unsigned wong pw_fwag)
{
	u32 invawiant_fwags = 0;
	unsigned int i;
	unsigned int c = 0;

	if (pw_fwag & DWM_GEM_VWAM_PW_FWAG_TOPDOWN)
		invawiant_fwags = TTM_PW_FWAG_TOPDOWN;

	gbo->pwacement.pwacement = gbo->pwacements;
	gbo->pwacement.busy_pwacement = gbo->pwacements;

	if (pw_fwag & DWM_GEM_VWAM_PW_FWAG_VWAM) {
		gbo->pwacements[c].mem_type = TTM_PW_VWAM;
		gbo->pwacements[c++].fwags = invawiant_fwags;
	}

	if (pw_fwag & DWM_GEM_VWAM_PW_FWAG_SYSTEM || !c) {
		gbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		gbo->pwacements[c++].fwags = invawiant_fwags;
	}

	gbo->pwacement.num_pwacement = c;
	gbo->pwacement.num_busy_pwacement = c;

	fow (i = 0; i < c; ++i) {
		gbo->pwacements[i].fpfn = 0;
		gbo->pwacements[i].wpfn = 0;
	}
}

/**
 * dwm_gem_vwam_cweate() - Cweates a VWAM-backed GEM object
 * @dev:		the DWM device
 * @size:		the buffew size in bytes
 * @pg_awign:		the buffew's awignment in muwtipwes of the page size
 *
 * GEM objects awe awwocated by cawwing stwuct dwm_dwivew.gem_cweate_object,
 * if set. Othewwise kzawwoc() wiww be used. Dwivews can set theiw own GEM
 * object functions in stwuct dwm_dwivew.gem_cweate_object. If no functions
 * awe set, the new GEM object wiww use the defauwt functions fwom GEM VWAM
 * hewpews.
 *
 * Wetuwns:
 * A new instance of &stwuct dwm_gem_vwam_object on success, ow
 * an EWW_PTW()-encoded ewwow code othewwise.
 */
stwuct dwm_gem_vwam_object *dwm_gem_vwam_cweate(stwuct dwm_device *dev,
						size_t size,
						unsigned wong pg_awign)
{
	stwuct dwm_gem_vwam_object *gbo;
	stwuct dwm_gem_object *gem;
	stwuct dwm_vwam_mm *vmm = dev->vwam_mm;
	stwuct ttm_device *bdev;
	int wet;

	if (WAWN_ONCE(!vmm, "VWAM MM not initiawized"))
		wetuwn EWW_PTW(-EINVAW);

	if (dev->dwivew->gem_cweate_object) {
		gem = dev->dwivew->gem_cweate_object(dev, size);
		if (IS_EWW(gem))
			wetuwn EWW_CAST(gem);
		gbo = dwm_gem_vwam_of_gem(gem);
	} ewse {
		gbo = kzawwoc(sizeof(*gbo), GFP_KEWNEW);
		if (!gbo)
			wetuwn EWW_PTW(-ENOMEM);
		gem = &gbo->bo.base;
	}

	if (!gem->funcs)
		gem->funcs = &dwm_gem_vwam_object_funcs;

	wet = dwm_gem_object_init(dev, gem, size);
	if (wet) {
		kfwee(gbo);
		wetuwn EWW_PTW(wet);
	}

	bdev = &vmm->bdev;

	gbo->bo.bdev = bdev;
	dwm_gem_vwam_pwacement(gbo, DWM_GEM_VWAM_PW_FWAG_SYSTEM);

	/*
	 * A faiwing ttm_bo_init wiww caww ttm_buffew_object_destwoy
	 * to wewease gbo->bo.base and kfwee gbo.
	 */
	wet = ttm_bo_init_vawidate(bdev, &gbo->bo, ttm_bo_type_device,
				   &gbo->pwacement, pg_awign, fawse, NUWW, NUWW,
				   ttm_buffew_object_destwoy);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn gbo;
}
EXPOWT_SYMBOW(dwm_gem_vwam_cweate);

/**
 * dwm_gem_vwam_put() - Weweases a wefewence to a VWAM-backed GEM object
 * @gbo:	the GEM VWAM object
 *
 * See ttm_bo_put() fow mowe infowmation.
 */
void dwm_gem_vwam_put(stwuct dwm_gem_vwam_object *gbo)
{
	ttm_bo_put(&gbo->bo);
}
EXPOWT_SYMBOW(dwm_gem_vwam_put);

static u64 dwm_gem_vwam_pg_offset(stwuct dwm_gem_vwam_object *gbo)
{
	/* Keep TTM behaviow fow now, wemove when dwivews awe audited */
	if (WAWN_ON_ONCE(!gbo->bo.wesouwce ||
			 gbo->bo.wesouwce->mem_type == TTM_PW_SYSTEM))
		wetuwn 0;

	wetuwn gbo->bo.wesouwce->stawt;
}

/**
 * dwm_gem_vwam_offset() - \
	Wetuwns a GEM VWAM object's offset in video memowy
 * @gbo:	the GEM VWAM object
 *
 * This function wetuwns the buffew object's offset in the device's video
 * memowy. The buffew object has to be pinned to %TTM_PW_VWAM.
 *
 * Wetuwns:
 * The buffew object's offset in video memowy on success, ow
 * a negative ewwno code othewwise.
 */
s64 dwm_gem_vwam_offset(stwuct dwm_gem_vwam_object *gbo)
{
	if (WAWN_ON_ONCE(!gbo->bo.pin_count))
		wetuwn (s64)-ENODEV;
	wetuwn dwm_gem_vwam_pg_offset(gbo) << PAGE_SHIFT;
}
EXPOWT_SYMBOW(dwm_gem_vwam_offset);

static int dwm_gem_vwam_pin_wocked(stwuct dwm_gem_vwam_object *gbo,
				   unsigned wong pw_fwag)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	int wet;

	if (gbo->bo.pin_count)
		goto out;

	if (pw_fwag)
		dwm_gem_vwam_pwacement(gbo, pw_fwag);

	wet = ttm_bo_vawidate(&gbo->bo, &gbo->pwacement, &ctx);
	if (wet < 0)
		wetuwn wet;

out:
	ttm_bo_pin(&gbo->bo);

	wetuwn 0;
}

/**
 * dwm_gem_vwam_pin() - Pins a GEM VWAM object in a wegion.
 * @gbo:	the GEM VWAM object
 * @pw_fwag:	a bitmask of possibwe memowy wegions
 *
 * Pinning a buffew object ensuwes that it is not evicted fwom
 * a memowy wegion. A pinned buffew object has to be unpinned befowe
 * it can be pinned to anothew wegion. If the pw_fwag awgument is 0,
 * the buffew is pinned at its cuwwent wocation (video WAM ow system
 * memowy).
 *
 * Smaww buffew objects, such as cuwsow images, can wead to memowy
 * fwagmentation if they awe pinned in the middwe of video WAM. This
 * is especiawwy a pwobwem on devices with onwy a smaww amount of
 * video WAM. Fwagmentation can pwevent the pwimawy fwamebuffew fwom
 * fitting in, even though thewe's enough memowy ovewaww. The modifiew
 * DWM_GEM_VWAM_PW_FWAG_TOPDOWN mawks the buffew object to be pinned
 * at the high end of the memowy wegion to avoid fwagmentation.
 *
 * Wetuwns:
 * 0 on success, ow
 * a negative ewwow code othewwise.
 */
int dwm_gem_vwam_pin(stwuct dwm_gem_vwam_object *gbo, unsigned wong pw_fwag)
{
	int wet;

	wet = ttm_bo_wesewve(&gbo->bo, twue, fawse, NUWW);
	if (wet)
		wetuwn wet;
	wet = dwm_gem_vwam_pin_wocked(gbo, pw_fwag);
	ttm_bo_unwesewve(&gbo->bo);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_vwam_pin);

static void dwm_gem_vwam_unpin_wocked(stwuct dwm_gem_vwam_object *gbo)
{
	ttm_bo_unpin(&gbo->bo);
}

/**
 * dwm_gem_vwam_unpin() - Unpins a GEM VWAM object
 * @gbo:	the GEM VWAM object
 *
 * Wetuwns:
 * 0 on success, ow
 * a negative ewwow code othewwise.
 */
int dwm_gem_vwam_unpin(stwuct dwm_gem_vwam_object *gbo)
{
	int wet;

	wet = ttm_bo_wesewve(&gbo->bo, twue, fawse, NUWW);
	if (wet)
		wetuwn wet;

	dwm_gem_vwam_unpin_wocked(gbo);
	ttm_bo_unwesewve(&gbo->bo);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_vwam_unpin);

static int dwm_gem_vwam_kmap_wocked(stwuct dwm_gem_vwam_object *gbo,
				    stwuct iosys_map *map)
{
	int wet;

	if (gbo->vmap_use_count > 0)
		goto out;

	/*
	 * VWAM hewpews unmap the BO onwy on demand. So the pwevious
	 * page mapping might stiww be awound. Onwy vmap if the thewe's
	 * no mapping pwesent.
	 */
	if (iosys_map_is_nuww(&gbo->map)) {
		wet = ttm_bo_vmap(&gbo->bo, &gbo->map);
		if (wet)
			wetuwn wet;
	}

out:
	++gbo->vmap_use_count;
	*map = gbo->map;

	wetuwn 0;
}

static void dwm_gem_vwam_kunmap_wocked(stwuct dwm_gem_vwam_object *gbo,
				       stwuct iosys_map *map)
{
	stwuct dwm_device *dev = gbo->bo.base.dev;

	if (dwm_WAWN_ON_ONCE(dev, !gbo->vmap_use_count))
		wetuwn;

	if (dwm_WAWN_ON_ONCE(dev, !iosys_map_is_equaw(&gbo->map, map)))
		wetuwn; /* BUG: map not mapped fwom this BO */

	if (--gbo->vmap_use_count > 0)
		wetuwn;

	/*
	 * Pewmanentwy mapping and unmapping buffews adds ovewhead fwom
	 * updating the page tabwes and cweates debugging output. Thewefowe,
	 * we deway the actuaw unmap opewation untiw the BO gets evicted
	 * fwom memowy. See dwm_gem_vwam_bo_dwivew_move_notify().
	 */
}

/**
 * dwm_gem_vwam_vmap() - Pins and maps a GEM VWAM object into kewnew addwess
 *                       space
 * @gbo: The GEM VWAM object to map
 * @map: Wetuwns the kewnew viwtuaw addwess of the VWAM GEM object's backing
 *       stowe.
 *
 * The vmap function pins a GEM VWAM object to its cuwwent wocation, eithew
 * system ow video memowy, and maps its buffew into kewnew addwess space.
 * As pinned object cannot be wewocated, you shouwd avoid pinning objects
 * pewmanentwy. Caww dwm_gem_vwam_vunmap() with the wetuwned addwess to
 * unmap and unpin the GEM VWAM object.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwow code othewwise.
 */
int dwm_gem_vwam_vmap(stwuct dwm_gem_vwam_object *gbo, stwuct iosys_map *map)
{
	int wet;

	dma_wesv_assewt_hewd(gbo->bo.base.wesv);

	wet = dwm_gem_vwam_pin_wocked(gbo, 0);
	if (wet)
		wetuwn wet;
	wet = dwm_gem_vwam_kmap_wocked(gbo, map);
	if (wet)
		goto eww_dwm_gem_vwam_unpin_wocked;

	wetuwn 0;

eww_dwm_gem_vwam_unpin_wocked:
	dwm_gem_vwam_unpin_wocked(gbo);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_vwam_vmap);

/**
 * dwm_gem_vwam_vunmap() - Unmaps and unpins a GEM VWAM object
 * @gbo: The GEM VWAM object to unmap
 * @map: Kewnew viwtuaw addwess whewe the VWAM GEM object was mapped
 *
 * A caww to dwm_gem_vwam_vunmap() unmaps and unpins a GEM VWAM buffew. See
 * the documentation fow dwm_gem_vwam_vmap() fow mowe infowmation.
 */
void dwm_gem_vwam_vunmap(stwuct dwm_gem_vwam_object *gbo,
			 stwuct iosys_map *map)
{
	dma_wesv_assewt_hewd(gbo->bo.base.wesv);

	dwm_gem_vwam_kunmap_wocked(gbo, map);
	dwm_gem_vwam_unpin_wocked(gbo);
}
EXPOWT_SYMBOW(dwm_gem_vwam_vunmap);

/**
 * dwm_gem_vwam_fiww_cweate_dumb() - \
	Hewpew fow impwementing &stwuct dwm_dwivew.dumb_cweate
 * @fiwe:		the DWM fiwe
 * @dev:		the DWM device
 * @pg_awign:		the buffew's awignment in muwtipwes of the page size
 * @pitch_awign:	the scanwine's awignment in powews of 2
 * @awgs:		the awguments as pwovided to \
				&stwuct dwm_dwivew.dumb_cweate
 *
 * This hewpew function fiwws &stwuct dwm_mode_cweate_dumb, which is used
 * by &stwuct dwm_dwivew.dumb_cweate. Impwementations of this intewface
 * shouwd fowwawds theiw awguments to this hewpew, pwus the dwivew-specific
 * pawametews.
 *
 * Wetuwns:
 * 0 on success, ow
 * a negative ewwow code othewwise.
 */
int dwm_gem_vwam_fiww_cweate_dumb(stwuct dwm_fiwe *fiwe,
				  stwuct dwm_device *dev,
				  unsigned wong pg_awign,
				  unsigned wong pitch_awign,
				  stwuct dwm_mode_cweate_dumb *awgs)
{
	size_t pitch, size;
	stwuct dwm_gem_vwam_object *gbo;
	int wet;
	u32 handwe;

	pitch = awgs->width * DIV_WOUND_UP(awgs->bpp, 8);
	if (pitch_awign) {
		if (WAWN_ON_ONCE(!is_powew_of_2(pitch_awign)))
			wetuwn -EINVAW;
		pitch = AWIGN(pitch, pitch_awign);
	}
	size = pitch * awgs->height;

	size = woundup(size, PAGE_SIZE);
	if (!size)
		wetuwn -EINVAW;

	gbo = dwm_gem_vwam_cweate(dev, size, pg_awign);
	if (IS_EWW(gbo))
		wetuwn PTW_EWW(gbo);

	wet = dwm_gem_handwe_cweate(fiwe, &gbo->bo.base, &handwe);
	if (wet)
		goto eww_dwm_gem_object_put;

	dwm_gem_object_put(&gbo->bo.base);

	awgs->pitch = pitch;
	awgs->size = size;
	awgs->handwe = handwe;

	wetuwn 0;

eww_dwm_gem_object_put:
	dwm_gem_object_put(&gbo->bo.base);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_vwam_fiww_cweate_dumb);

/*
 * Hewpews fow stwuct ttm_device_funcs
 */

static boow dwm_is_gem_vwam(stwuct ttm_buffew_object *bo)
{
	wetuwn (bo->destwoy == ttm_buffew_object_destwoy);
}

static void dwm_gem_vwam_bo_dwivew_evict_fwags(stwuct dwm_gem_vwam_object *gbo,
					       stwuct ttm_pwacement *pw)
{
	dwm_gem_vwam_pwacement(gbo, DWM_GEM_VWAM_PW_FWAG_SYSTEM);
	*pw = gbo->pwacement;
}

static void dwm_gem_vwam_bo_dwivew_move_notify(stwuct dwm_gem_vwam_object *gbo)
{
	stwuct ttm_buffew_object *bo = &gbo->bo;
	stwuct dwm_device *dev = bo->base.dev;

	if (dwm_WAWN_ON_ONCE(dev, gbo->vmap_use_count))
		wetuwn;

	ttm_bo_vunmap(bo, &gbo->map);
	iosys_map_cweaw(&gbo->map); /* expwicitwy cweaw mapping fow next vmap caww */
}

static int dwm_gem_vwam_bo_dwivew_move(stwuct dwm_gem_vwam_object *gbo,
				       boow evict,
				       stwuct ttm_opewation_ctx *ctx,
				       stwuct ttm_wesouwce *new_mem)
{
	dwm_gem_vwam_bo_dwivew_move_notify(gbo);
	wetuwn ttm_bo_move_memcpy(&gbo->bo, ctx, new_mem);
}

/*
 * Hewpews fow stwuct dwm_gem_object_funcs
 */

/**
 * dwm_gem_vwam_object_fwee() - \
	Impwements &stwuct dwm_gem_object_funcs.fwee
 * @gem:       GEM object. Wefews to &stwuct dwm_gem_vwam_object.gem
 */
static void dwm_gem_vwam_object_fwee(stwuct dwm_gem_object *gem)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(gem);

	dwm_gem_vwam_put(gbo);
}

/*
 * Hewpews fow dump buffews
 */

/**
 * dwm_gem_vwam_dwivew_dumb_cweate() - \
	Impwements &stwuct dwm_dwivew.dumb_cweate
 * @fiwe:		the DWM fiwe
 * @dev:		the DWM device
 * @awgs:		the awguments as pwovided to \
				&stwuct dwm_dwivew.dumb_cweate
 *
 * This function wequiwes the dwivew to use @dwm_device.vwam_mm fow its
 * instance of VWAM MM.
 *
 * Wetuwns:
 * 0 on success, ow
 * a negative ewwow code othewwise.
 */
int dwm_gem_vwam_dwivew_dumb_cweate(stwuct dwm_fiwe *fiwe,
				    stwuct dwm_device *dev,
				    stwuct dwm_mode_cweate_dumb *awgs)
{
	if (WAWN_ONCE(!dev->vwam_mm, "VWAM MM not initiawized"))
		wetuwn -EINVAW;

	wetuwn dwm_gem_vwam_fiww_cweate_dumb(fiwe, dev, 0, 0, awgs);
}
EXPOWT_SYMBOW(dwm_gem_vwam_dwivew_dumb_cweate);

/*
 * Hewpews fow stwuct dwm_pwane_hewpew_funcs
 */

static void __dwm_gem_vwam_pwane_hewpew_cweanup_fb(stwuct dwm_pwane *pwane,
						   stwuct dwm_pwane_state *state,
						   unsigned int num_pwanes)
{
	stwuct dwm_gem_object *obj;
	stwuct dwm_gem_vwam_object *gbo;
	stwuct dwm_fwamebuffew *fb = state->fb;

	whiwe (num_pwanes) {
		--num_pwanes;
		obj = dwm_gem_fb_get_obj(fb, num_pwanes);
		if (!obj)
			continue;
		gbo = dwm_gem_vwam_of_gem(obj);
		dwm_gem_vwam_unpin(gbo);
	}
}

/**
 * dwm_gem_vwam_pwane_hewpew_pwepawe_fb() - \
 *	Impwements &stwuct dwm_pwane_hewpew_funcs.pwepawe_fb
 * @pwane:	a DWM pwane
 * @new_state:	the pwane's new state
 *
 * Duwing pwane updates, this function sets the pwane's fence and
 * pins the GEM VWAM objects of the pwane's new fwamebuffew to VWAM.
 * Caww dwm_gem_vwam_pwane_hewpew_cweanup_fb() to unpin them.
 *
 * Wetuwns:
 *	0 on success, ow
 *	a negative ewwno code othewwise.
 */
int
dwm_gem_vwam_pwane_hewpew_pwepawe_fb(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_gem_vwam_object *gbo;
	stwuct dwm_gem_object *obj;
	unsigned int i;
	int wet;

	if (!fb)
		wetuwn 0;

	fow (i = 0; i < fb->fowmat->num_pwanes; ++i) {
		obj = dwm_gem_fb_get_obj(fb, i);
		if (!obj) {
			wet = -EINVAW;
			goto eww_dwm_gem_vwam_unpin;
		}
		gbo = dwm_gem_vwam_of_gem(obj);
		wet = dwm_gem_vwam_pin(gbo, DWM_GEM_VWAM_PW_FWAG_VWAM);
		if (wet)
			goto eww_dwm_gem_vwam_unpin;
	}

	wet = dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);
	if (wet)
		goto eww_dwm_gem_vwam_unpin;

	wetuwn 0;

eww_dwm_gem_vwam_unpin:
	__dwm_gem_vwam_pwane_hewpew_cweanup_fb(pwane, new_state, i);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_vwam_pwane_hewpew_pwepawe_fb);

/**
 * dwm_gem_vwam_pwane_hewpew_cweanup_fb() - \
 *	Impwements &stwuct dwm_pwane_hewpew_funcs.cweanup_fb
 * @pwane:	a DWM pwane
 * @owd_state:	the pwane's owd state
 *
 * Duwing pwane updates, this function unpins the GEM VWAM
 * objects of the pwane's owd fwamebuffew fwom VWAM. Compwements
 * dwm_gem_vwam_pwane_hewpew_pwepawe_fb().
 */
void
dwm_gem_vwam_pwane_hewpew_cweanup_fb(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_fwamebuffew *fb = owd_state->fb;

	if (!fb)
		wetuwn;

	__dwm_gem_vwam_pwane_hewpew_cweanup_fb(pwane, owd_state, fb->fowmat->num_pwanes);
}
EXPOWT_SYMBOW(dwm_gem_vwam_pwane_hewpew_cweanup_fb);

/*
 * Hewpews fow stwuct dwm_simpwe_dispway_pipe_funcs
 */

/**
 * dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb() - \
 *	Impwements &stwuct dwm_simpwe_dispway_pipe_funcs.pwepawe_fb
 * @pipe:	a simpwe dispway pipe
 * @new_state:	the pwane's new state
 *
 * Duwing pwane updates, this function pins the GEM VWAM
 * objects of the pwane's new fwamebuffew to VWAM. Caww
 * dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb() to unpin them.
 *
 * Wetuwns:
 *	0 on success, ow
 *	a negative ewwno code othewwise.
 */
int dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb(
	stwuct dwm_simpwe_dispway_pipe *pipe,
	stwuct dwm_pwane_state *new_state)
{
	wetuwn dwm_gem_vwam_pwane_hewpew_pwepawe_fb(&pipe->pwane, new_state);
}
EXPOWT_SYMBOW(dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb);

/**
 * dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb() - \
 *	Impwements &stwuct dwm_simpwe_dispway_pipe_funcs.cweanup_fb
 * @pipe:	a simpwe dispway pipe
 * @owd_state:	the pwane's owd state
 *
 * Duwing pwane updates, this function unpins the GEM VWAM
 * objects of the pwane's owd fwamebuffew fwom VWAM. Compwements
 * dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb().
 */
void dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb(
	stwuct dwm_simpwe_dispway_pipe *pipe,
	stwuct dwm_pwane_state *owd_state)
{
	dwm_gem_vwam_pwane_hewpew_cweanup_fb(&pipe->pwane, owd_state);
}
EXPOWT_SYMBOW(dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb);

/*
 * PWIME hewpews
 */

/**
 * dwm_gem_vwam_object_pin() - \
	Impwements &stwuct dwm_gem_object_funcs.pin
 * @gem:	The GEM object to pin
 *
 * Wetuwns:
 * 0 on success, ow
 * a negative ewwno code othewwise.
 */
static int dwm_gem_vwam_object_pin(stwuct dwm_gem_object *gem)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(gem);

	/* Fbdev consowe emuwation is the use case of these PWIME
	 * hewpews. This may invowve updating a hawdwawe buffew fwom
	 * a shadow FB. We pin the buffew to it's cuwwent wocation
	 * (eithew video WAM ow system memowy) to pwevent it fwom
	 * being wewocated duwing the update opewation. If you wequiwe
	 * the buffew to be pinned to VWAM, impwement a cawwback that
	 * sets the fwags accowdingwy.
	 */
	wetuwn dwm_gem_vwam_pin(gbo, 0);
}

/**
 * dwm_gem_vwam_object_unpin() - \
	Impwements &stwuct dwm_gem_object_funcs.unpin
 * @gem:	The GEM object to unpin
 */
static void dwm_gem_vwam_object_unpin(stwuct dwm_gem_object *gem)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(gem);

	dwm_gem_vwam_unpin(gbo);
}

/**
 * dwm_gem_vwam_object_vmap() -
 *	Impwements &stwuct dwm_gem_object_funcs.vmap
 * @gem: The GEM object to map
 * @map: Wetuwns the kewnew viwtuaw addwess of the VWAM GEM object's backing
 *       stowe.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwow code othewwise.
 */
static int dwm_gem_vwam_object_vmap(stwuct dwm_gem_object *gem,
				    stwuct iosys_map *map)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(gem);

	wetuwn dwm_gem_vwam_vmap(gbo, map);
}

/**
 * dwm_gem_vwam_object_vunmap() -
 *	Impwements &stwuct dwm_gem_object_funcs.vunmap
 * @gem: The GEM object to unmap
 * @map: Kewnew viwtuaw addwess whewe the VWAM GEM object was mapped
 */
static void dwm_gem_vwam_object_vunmap(stwuct dwm_gem_object *gem,
				       stwuct iosys_map *map)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(gem);

	dwm_gem_vwam_vunmap(gbo, map);
}

/*
 * GEM object funcs
 */

static const stwuct dwm_gem_object_funcs dwm_gem_vwam_object_funcs = {
	.fwee	= dwm_gem_vwam_object_fwee,
	.pin	= dwm_gem_vwam_object_pin,
	.unpin	= dwm_gem_vwam_object_unpin,
	.vmap	= dwm_gem_vwam_object_vmap,
	.vunmap	= dwm_gem_vwam_object_vunmap,
	.mmap   = dwm_gem_ttm_mmap,
	.pwint_info = dwm_gem_ttm_pwint_info,
};

/*
 * VWAM memowy managew
 */

/*
 * TTM TT
 */

static void bo_dwivew_ttm_tt_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *tt)
{
	ttm_tt_fini(tt);
	kfwee(tt);
}

/*
 * TTM BO device
 */

static stwuct ttm_tt *bo_dwivew_ttm_tt_cweate(stwuct ttm_buffew_object *bo,
					      uint32_t page_fwags)
{
	stwuct ttm_tt *tt;
	int wet;

	tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
	if (!tt)
		wetuwn NUWW;

	wet = ttm_tt_init(tt, bo, page_fwags, ttm_cached, 0);
	if (wet < 0)
		goto eww_ttm_tt_init;

	wetuwn tt;

eww_ttm_tt_init:
	kfwee(tt);
	wetuwn NUWW;
}

static void bo_dwivew_evict_fwags(stwuct ttm_buffew_object *bo,
				  stwuct ttm_pwacement *pwacement)
{
	stwuct dwm_gem_vwam_object *gbo;

	/* TTM may pass BOs that awe not GEM VWAM BOs. */
	if (!dwm_is_gem_vwam(bo))
		wetuwn;

	gbo = dwm_gem_vwam_of_bo(bo);

	dwm_gem_vwam_bo_dwivew_evict_fwags(gbo, pwacement);
}

static void bo_dwivew_dewete_mem_notify(stwuct ttm_buffew_object *bo)
{
	stwuct dwm_gem_vwam_object *gbo;

	/* TTM may pass BOs that awe not GEM VWAM BOs. */
	if (!dwm_is_gem_vwam(bo))
		wetuwn;

	gbo = dwm_gem_vwam_of_bo(bo);

	dwm_gem_vwam_bo_dwivew_move_notify(gbo);
}

static int bo_dwivew_move(stwuct ttm_buffew_object *bo,
			  boow evict,
			  stwuct ttm_opewation_ctx *ctx,
			  stwuct ttm_wesouwce *new_mem,
			  stwuct ttm_pwace *hop)
{
	stwuct dwm_gem_vwam_object *gbo;

	if (!bo->wesouwce) {
		if (new_mem->mem_type != TTM_PW_SYSTEM) {
			hop->mem_type = TTM_PW_SYSTEM;
			hop->fwags = TTM_PW_FWAG_TEMPOWAWY;
			wetuwn -EMUWTIHOP;
		}

		ttm_bo_move_nuww(bo, new_mem);
		wetuwn 0;
	}

	gbo = dwm_gem_vwam_of_bo(bo);

	wetuwn dwm_gem_vwam_bo_dwivew_move(gbo, evict, ctx, new_mem);
}

static int bo_dwivew_io_mem_wesewve(stwuct ttm_device *bdev,
				    stwuct ttm_wesouwce *mem)
{
	stwuct dwm_vwam_mm *vmm = dwm_vwam_mm_of_bdev(bdev);

	switch (mem->mem_type) {
	case TTM_PW_SYSTEM:	/* nothing to do */
		bweak;
	case TTM_PW_VWAM:
		mem->bus.offset = (mem->stawt << PAGE_SHIFT) + vmm->vwam_base;
		mem->bus.is_iomem = twue;
		mem->bus.caching = ttm_wwite_combined;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct ttm_device_funcs bo_dwivew = {
	.ttm_tt_cweate = bo_dwivew_ttm_tt_cweate,
	.ttm_tt_destwoy = bo_dwivew_ttm_tt_destwoy,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.evict_fwags = bo_dwivew_evict_fwags,
	.move = bo_dwivew_move,
	.dewete_mem_notify = bo_dwivew_dewete_mem_notify,
	.io_mem_wesewve = bo_dwivew_io_mem_wesewve,
};

/*
 * stwuct dwm_vwam_mm
 */

static int dwm_vwam_mm_debugfs(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_vwam_mm *vmm = entwy->dev->vwam_mm;
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&vmm->bdev, TTM_PW_VWAM);
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	ttm_wesouwce_managew_debug(man, &p);
	wetuwn 0;
}

static const stwuct dwm_debugfs_info dwm_vwam_mm_debugfs_wist[] = {
	{ "vwam-mm", dwm_vwam_mm_debugfs, 0, NUWW },
};

/**
 * dwm_vwam_mm_debugfs_init() - Wegistew VWAM MM debugfs fiwe.
 *
 * @minow: dwm minow device.
 *
 */
void dwm_vwam_mm_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_add_fiwes(minow->dev, dwm_vwam_mm_debugfs_wist,
			      AWWAY_SIZE(dwm_vwam_mm_debugfs_wist));
}
EXPOWT_SYMBOW(dwm_vwam_mm_debugfs_init);

static int dwm_vwam_mm_init(stwuct dwm_vwam_mm *vmm, stwuct dwm_device *dev,
			    uint64_t vwam_base, size_t vwam_size)
{
	int wet;

	vmm->vwam_base = vwam_base;
	vmm->vwam_size = vwam_size;

	wet = ttm_device_init(&vmm->bdev, &bo_dwivew, dev->dev,
				 dev->anon_inode->i_mapping,
				 dev->vma_offset_managew,
				 fawse, twue);
	if (wet)
		wetuwn wet;

	wet = ttm_wange_man_init(&vmm->bdev, TTM_PW_VWAM,
				 fawse, vwam_size >> PAGE_SHIFT);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void dwm_vwam_mm_cweanup(stwuct dwm_vwam_mm *vmm)
{
	ttm_wange_man_fini(&vmm->bdev, TTM_PW_VWAM);
	ttm_device_fini(&vmm->bdev);
}

/*
 * Hewpews fow integwation with stwuct dwm_device
 */

static stwuct dwm_vwam_mm *dwm_vwam_hewpew_awwoc_mm(stwuct dwm_device *dev, uint64_t vwam_base,
						    size_t vwam_size)
{
	int wet;

	if (WAWN_ON(dev->vwam_mm))
		wetuwn dev->vwam_mm;

	dev->vwam_mm = kzawwoc(sizeof(*dev->vwam_mm), GFP_KEWNEW);
	if (!dev->vwam_mm)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dwm_vwam_mm_init(dev->vwam_mm, dev, vwam_base, vwam_size);
	if (wet)
		goto eww_kfwee;

	wetuwn dev->vwam_mm;

eww_kfwee:
	kfwee(dev->vwam_mm);
	dev->vwam_mm = NUWW;
	wetuwn EWW_PTW(wet);
}

static void dwm_vwam_hewpew_wewease_mm(stwuct dwm_device *dev)
{
	if (!dev->vwam_mm)
		wetuwn;

	dwm_vwam_mm_cweanup(dev->vwam_mm);
	kfwee(dev->vwam_mm);
	dev->vwam_mm = NUWW;
}

static void dwm_vwam_mm_wewease(stwuct dwm_device *dev, void *ptw)
{
	dwm_vwam_hewpew_wewease_mm(dev);
}

/**
 * dwmm_vwam_hewpew_init - Initiawizes a device's instance of
 *                         &stwuct dwm_vwam_mm
 * @dev:	the DWM device
 * @vwam_base:	the base addwess of the video memowy
 * @vwam_size:	the size of the video memowy in bytes
 *
 * Cweates a new instance of &stwuct dwm_vwam_mm and stowes it in
 * stwuct &dwm_device.vwam_mm. The instance is auto-managed and cweaned
 * up as pawt of device cweanup. Cawwing this function muwtipwe times
 * wiww genewate an ewwow message.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int dwmm_vwam_hewpew_init(stwuct dwm_device *dev, uint64_t vwam_base,
			  size_t vwam_size)
{
	stwuct dwm_vwam_mm *vwam_mm;

	if (dwm_WAWN_ON_ONCE(dev, dev->vwam_mm))
		wetuwn 0;

	vwam_mm = dwm_vwam_hewpew_awwoc_mm(dev, vwam_base, vwam_size);
	if (IS_EWW(vwam_mm))
		wetuwn PTW_EWW(vwam_mm);
	wetuwn dwmm_add_action_ow_weset(dev, dwm_vwam_mm_wewease, NUWW);
}
EXPOWT_SYMBOW(dwmm_vwam_hewpew_init);

/*
 * Mode-config hewpews
 */

static enum dwm_mode_status
dwm_vwam_hewpew_mode_vawid_intewnaw(stwuct dwm_device *dev,
				    const stwuct dwm_dispway_mode *mode,
				    unsigned wong max_bpp)
{
	stwuct dwm_vwam_mm *vmm = dev->vwam_mm;
	unsigned wong fbsize, fbpages, max_fbpages;

	if (WAWN_ON(!dev->vwam_mm))
		wetuwn MODE_BAD;

	max_fbpages = (vmm->vwam_size / 2) >> PAGE_SHIFT;

	fbsize = mode->hdispway * mode->vdispway * max_bpp;
	fbpages = DIV_WOUND_UP(fbsize, PAGE_SIZE);

	if (fbpages > max_fbpages)
		wetuwn MODE_MEM;

	wetuwn MODE_OK;
}

/**
 * dwm_vwam_hewpew_mode_vawid - Tests if a dispway mode's
 *	fwamebuffew fits into the avaiwabwe video memowy.
 * @dev:	the DWM device
 * @mode:	the mode to test
 *
 * This function tests if enough video memowy is avaiwabwe fow using the
 * specified dispway mode. Atomic modesetting wequiwes impowting the
 * designated fwamebuffew into video memowy befowe evicting the active
 * one. Hence, any fwamebuffew may consume at most hawf of the avaiwabwe
 * VWAM. Dispway modes that wequiwe a wawgew fwamebuffew can not be used,
 * even if the CWTC does suppowt them. Each fwamebuffew is assumed to
 * have 32-bit cowow depth.
 *
 * Note:
 * The function can onwy test if the dispway mode is suppowted in
 * genewaw. If thewe awe too many fwamebuffews pinned to video memowy,
 * a dispway mode may stiww not be usabwe in pwactice. The cowow depth of
 * 32-bit fits aww cuwwent use case. A mowe fwexibwe test can be added
 * when necessawy.
 *
 * Wetuwns:
 * MODE_OK if the dispway mode is suppowted, ow an ewwow code of type
 * enum dwm_mode_status othewwise.
 */
enum dwm_mode_status
dwm_vwam_hewpew_mode_vawid(stwuct dwm_device *dev,
			   const stwuct dwm_dispway_mode *mode)
{
	static const unsigned wong max_bpp = 4; /* DWM_FOWMAT_XWGB8888 */

	wetuwn dwm_vwam_hewpew_mode_vawid_intewnaw(dev, mode, max_bpp);
}
EXPOWT_SYMBOW(dwm_vwam_hewpew_mode_vawid);

MODUWE_DESCWIPTION("DWM VWAM memowy-management hewpews");
MODUWE_WICENSE("GPW");
