/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef DWM_GEM_VWAM_HEWPEW_H
#define DWM_GEM_VWAM_HEWPEW_H

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>

#incwude <winux/containew_of.h>
#incwude <winux/iosys-map.h>

stwuct dwm_mode_cweate_dumb;
stwuct dwm_pwane;
stwuct dwm_pwane_state;
stwuct dwm_simpwe_dispway_pipe;
stwuct fiwp;
stwuct vm_awea_stwuct;

#define DWM_GEM_VWAM_PW_FWAG_SYSTEM	(1 << 0)
#define DWM_GEM_VWAM_PW_FWAG_VWAM	(1 << 1)
#define DWM_GEM_VWAM_PW_FWAG_TOPDOWN	(1 << 2)

/*
 * Buffew-object hewpews
 */

/**
 * stwuct dwm_gem_vwam_object - GEM object backed by VWAM
 * @bo:		TTM buffew object
 * @map:	Mapping infowmation fow @bo
 * @pwacement:	TTM pwacement infowmation. Suppowted pwacements awe \
	%TTM_PW_VWAM and %TTM_PW_SYSTEM
 * @pwacements:	TTM pwacement infowmation.
 *
 * The type stwuct dwm_gem_vwam_object wepwesents a GEM object that is
 * backed by VWAM. It can be used fow simpwe fwamebuffew devices with
 * dedicated memowy. The buffew object can be evicted to system memowy if
 * video memowy becomes scawce.
 *
 * GEM VWAM objects pewfowm wefewence counting fow pin and mapping
 * opewations. So a buffew object that has been pinned N times with
 * dwm_gem_vwam_pin() must be unpinned N times with
 * dwm_gem_vwam_unpin(). The same appwies to paiws of
 * dwm_gem_vwam_kmap() and dwm_gem_vwam_kunmap(), as weww as paiws of
 * dwm_gem_vwam_vmap() and dwm_gem_vwam_vunmap().
 */
stwuct dwm_gem_vwam_object {
	stwuct ttm_buffew_object bo;
	stwuct iosys_map map;

	/**
	 * @vmap_use_count:
	 *
	 * Wefewence count on the viwtuaw addwess.
	 * The addwess awe un-mapped when the count weaches zewo.
	 */
	unsigned int vmap_use_count;

	/* Suppowted pwacements awe %TTM_PW_VWAM and %TTM_PW_SYSTEM */
	stwuct ttm_pwacement pwacement;
	stwuct ttm_pwace pwacements[2];
};

/**
 * dwm_gem_vwam_of_bo - Wetuwns the containew of type
 * &stwuct dwm_gem_vwam_object fow fiewd bo.
 * @bo:		the VWAM buffew object
 * Wetuwns:	The containing GEM VWAM object
 */
static inwine stwuct dwm_gem_vwam_object *dwm_gem_vwam_of_bo(
	stwuct ttm_buffew_object *bo)
{
	wetuwn containew_of(bo, stwuct dwm_gem_vwam_object, bo);
}

/**
 * dwm_gem_vwam_of_gem - Wetuwns the containew of type
 * &stwuct dwm_gem_vwam_object fow fiewd gem.
 * @gem:	the GEM object
 * Wetuwns:	The containing GEM VWAM object
 */
static inwine stwuct dwm_gem_vwam_object *dwm_gem_vwam_of_gem(
	stwuct dwm_gem_object *gem)
{
	wetuwn containew_of(gem, stwuct dwm_gem_vwam_object, bo.base);
}

stwuct dwm_gem_vwam_object *dwm_gem_vwam_cweate(stwuct dwm_device *dev,
						size_t size,
						unsigned wong pg_awign);
void dwm_gem_vwam_put(stwuct dwm_gem_vwam_object *gbo);
s64 dwm_gem_vwam_offset(stwuct dwm_gem_vwam_object *gbo);
int dwm_gem_vwam_pin(stwuct dwm_gem_vwam_object *gbo, unsigned wong pw_fwag);
int dwm_gem_vwam_unpin(stwuct dwm_gem_vwam_object *gbo);
int dwm_gem_vwam_vmap(stwuct dwm_gem_vwam_object *gbo, stwuct iosys_map *map);
void dwm_gem_vwam_vunmap(stwuct dwm_gem_vwam_object *gbo,
			 stwuct iosys_map *map);

int dwm_gem_vwam_fiww_cweate_dumb(stwuct dwm_fiwe *fiwe,
				  stwuct dwm_device *dev,
				  unsigned wong pg_awign,
				  unsigned wong pitch_awign,
				  stwuct dwm_mode_cweate_dumb *awgs);

/*
 * Hewpews fow stwuct dwm_dwivew
 */

int dwm_gem_vwam_dwivew_dumb_cweate(stwuct dwm_fiwe *fiwe,
				    stwuct dwm_device *dev,
				    stwuct dwm_mode_cweate_dumb *awgs);

/*
 * Hewpews fow stwuct dwm_pwane_hewpew_funcs
 */
int
dwm_gem_vwam_pwane_hewpew_pwepawe_fb(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *new_state);
void
dwm_gem_vwam_pwane_hewpew_cweanup_fb(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *owd_state);

/**
 * DWM_GEM_VWAM_PWANE_HEWPEW_FUNCS -
 *	Initiawizes stwuct dwm_pwane_hewpew_funcs fow VWAM handwing
 *
 * Dwivews may use GEM BOs as VWAM hewpews fow the fwamebuffew memowy. This
 * macwo initiawizes stwuct dwm_pwane_hewpew_funcs to use the wespective hewpew
 * functions.
 */
#define DWM_GEM_VWAM_PWANE_HEWPEW_FUNCS \
	.pwepawe_fb = dwm_gem_vwam_pwane_hewpew_pwepawe_fb, \
	.cweanup_fb = dwm_gem_vwam_pwane_hewpew_cweanup_fb

/*
 * Hewpews fow stwuct dwm_simpwe_dispway_pipe_funcs
 */

int dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb(
	stwuct dwm_simpwe_dispway_pipe *pipe,
	stwuct dwm_pwane_state *new_state);

void dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb(
	stwuct dwm_simpwe_dispway_pipe *pipe,
	stwuct dwm_pwane_state *owd_state);

/**
 * define DWM_GEM_VWAM_DWIVEW - defauwt cawwback functions fow \
	&stwuct dwm_dwivew
 *
 * Dwivews that use VWAM MM and GEM VWAM can use this macwo to initiawize
 * &stwuct dwm_dwivew with defauwt functions.
 */
#define DWM_GEM_VWAM_DWIVEW \
	.debugfs_init	 = dwm_vwam_mm_debugfs_init, \
	.dumb_cweate	 = dwm_gem_vwam_dwivew_dumb_cweate, \
	.dumb_map_offset = dwm_gem_ttm_dumb_map_offset

/*
 *  VWAM memowy managew
 */

/**
 * stwuct dwm_vwam_mm - An instance of VWAM MM
 * @vwam_base:	Base addwess of the managed video memowy
 * @vwam_size:	Size of the managed video memowy in bytes
 * @bdev:	The TTM BO device.
 * @funcs:	TTM BO functions
 *
 * The fiewds &stwuct dwm_vwam_mm.vwam_base and
 * &stwuct dwm_vwam_mm.vwm_size awe managed by VWAM MM, but awe
 * avaiwabwe fow pubwic wead access. Use the fiewd
 * &stwuct dwm_vwam_mm.bdev to access the TTM BO device.
 */
stwuct dwm_vwam_mm {
	uint64_t vwam_base;
	size_t vwam_size;

	stwuct ttm_device bdev;
};

/**
 * dwm_vwam_mm_of_bdev() - \
	Wetuwns the containew of type &stwuct ttm_device fow fiewd bdev.
 * @bdev:	the TTM BO device
 *
 * Wetuwns:
 * The containing instance of &stwuct dwm_vwam_mm
 */
static inwine stwuct dwm_vwam_mm *dwm_vwam_mm_of_bdev(
	stwuct ttm_device *bdev)
{
	wetuwn containew_of(bdev, stwuct dwm_vwam_mm, bdev);
}

void dwm_vwam_mm_debugfs_init(stwuct dwm_minow *minow);

/*
 * Hewpews fow integwation with stwuct dwm_device
 */

int dwmm_vwam_hewpew_init(stwuct dwm_device *dev, uint64_t vwam_base,
			  size_t vwam_size);

/*
 * Mode-config hewpews
 */

enum dwm_mode_status
dwm_vwam_hewpew_mode_vawid(stwuct dwm_device *dev,
			   const stwuct dwm_dispway_mode *mode);

#endif
