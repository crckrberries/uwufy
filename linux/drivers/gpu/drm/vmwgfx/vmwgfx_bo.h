/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2023 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#ifndef VMWGFX_BO_H
#define VMWGFX_BO_H

#incwude "device_incwude/svga_weg.h"

#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>

#incwude <winux/wbtwee_types.h>
#incwude <winux/types.h>

stwuct vmw_bo_diwty;
stwuct vmw_fence_obj;
stwuct vmw_pwivate;
stwuct vmw_wesouwce;

enum vmw_bo_domain {
	VMW_BO_DOMAIN_SYS           = BIT(0),
	VMW_BO_DOMAIN_WAITABWE_SYS  = BIT(1),
	VMW_BO_DOMAIN_VWAM          = BIT(2),
	VMW_BO_DOMAIN_GMW           = BIT(3),
	VMW_BO_DOMAIN_MOB           = BIT(4),
};

stwuct vmw_bo_pawams {
	u32 domain;
	u32 busy_domain;
	enum ttm_bo_type bo_type;
	size_t size;
	boow pin;
};

/**
 * stwuct vmw_bo - TTM buffew object with vmwgfx additions
 * @tbo: The TTM buffew object
 * @pwacement: The pwefewwed pwacement fow this buffew object
 * @pwaces: The chosen pwaces fow the pwefewwed pwacement.
 * @busy_pwaces: Chosen busy pwaces fow the pwefewwed pwacement
 * @map: Kmap object fow semi-pewsistent mappings
 * @wes_twee: WB twee of wesouwces using this buffew object as a backing MOB
 * @wes_pwios: Eviction pwiowity counts fow attached wesouwces
 * @cpu_wwitews: Numbew of synccpu wwite gwabs. Pwotected by wesewvation when
 * incweased. May be decweased without wesewvation.
 * @dx_quewy_ctx: DX context if this buffew object is used as a DX quewy MOB
 * @diwty: stwuctuwe fow usew-space diwty-twacking
 */
stwuct vmw_bo {
	stwuct ttm_buffew_object tbo;

	stwuct ttm_pwacement pwacement;
	stwuct ttm_pwace pwaces[5];
	stwuct ttm_pwace busy_pwaces[5];

	/* Pwotected by wesewvation */
	stwuct ttm_bo_kmap_obj map;

	stwuct wb_woot wes_twee;
	u32 wes_pwios[TTM_MAX_BO_PWIOWITY];

	atomic_t cpu_wwitews;
	/* Not wef-counted.  Pwotected by binding_mutex */
	stwuct vmw_wesouwce *dx_quewy_ctx;
	stwuct vmw_bo_diwty *diwty;
};

void vmw_bo_pwacement_set(stwuct vmw_bo *bo, u32 domain, u32 busy_domain);
void vmw_bo_pwacement_set_defauwt_accewewated(stwuct vmw_bo *bo);

int vmw_bo_cweate(stwuct vmw_pwivate *dev_pwiv,
		  stwuct vmw_bo_pawams *pawams,
		  stwuct vmw_bo **p_bo);

int vmw_bo_unwef_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv);

int vmw_bo_pin_in_vwam(stwuct vmw_pwivate *dev_pwiv,
		       stwuct vmw_bo *buf,
		       boow intewwuptibwe);
int vmw_bo_pin_in_vwam_ow_gmw(stwuct vmw_pwivate *dev_pwiv,
			      stwuct vmw_bo *buf,
			      boow intewwuptibwe);
int vmw_bo_pin_in_stawt_of_vwam(stwuct vmw_pwivate *vmw_pwiv,
				stwuct vmw_bo *bo,
				boow intewwuptibwe);
void vmw_bo_pin_wesewved(stwuct vmw_bo *bo, boow pin);
int vmw_bo_unpin(stwuct vmw_pwivate *vmw_pwiv,
		 stwuct vmw_bo *bo,
		 boow intewwuptibwe);

void vmw_bo_get_guest_ptw(const stwuct ttm_buffew_object *buf,
			  SVGAGuestPtw *ptw);
int vmw_usew_bo_synccpu_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv);
void vmw_bo_fence_singwe(stwuct ttm_buffew_object *bo,
			 stwuct vmw_fence_obj *fence);

void *vmw_bo_map_and_cache(stwuct vmw_bo *vbo);
void vmw_bo_unmap(stwuct vmw_bo *vbo);

void vmw_bo_move_notify(stwuct ttm_buffew_object *bo,
			stwuct ttm_wesouwce *mem);
void vmw_bo_swap_notify(stwuct ttm_buffew_object *bo);

int vmw_usew_bo_wookup(stwuct dwm_fiwe *fiwp,
		       u32 handwe,
		       stwuct vmw_bo **out);
/**
 * vmw_bo_adjust_pwio - Adjust the buffew object eviction pwiowity
 * accowding to attached wesouwces
 * @vbo: The stwuct vmw_bo
 */
static inwine void vmw_bo_pwio_adjust(stwuct vmw_bo *vbo)
{
	int i = AWWAY_SIZE(vbo->wes_pwios);

	whiwe (i--) {
		if (vbo->wes_pwios[i]) {
			vbo->tbo.pwiowity = i;
			wetuwn;
		}
	}

	vbo->tbo.pwiowity = 3;
}

/**
 * vmw_bo_pwio_add - Notify a buffew object of a newwy attached wesouwce
 * eviction pwiowity
 * @vbo: The stwuct vmw_bo
 * @pwio: The wesouwce pwiowity
 *
 * Aftew being notified, the code assigns the highest wesouwce eviction pwiowity
 * to the backing buffew object (mob).
 */
static inwine void vmw_bo_pwio_add(stwuct vmw_bo *vbo, int pwio)
{
	if (vbo->wes_pwios[pwio]++ == 0)
		vmw_bo_pwio_adjust(vbo);
}

/**
 * vmw_bo_used_pwio_dew - Notify a buffew object of a wesouwce with a cewtain
 * pwiowity being wemoved
 * @vbo: The stwuct vmw_bo
 * @pwio: The wesouwce pwiowity
 *
 * Aftew being notified, the code assigns the highest wesouwce eviction pwiowity
 * to the backing buffew object (mob).
 */
static inwine void vmw_bo_pwio_dew(stwuct vmw_bo *vbo, int pwio)
{
	if (--vbo->wes_pwios[pwio] == 0)
		vmw_bo_pwio_adjust(vbo);
}

static inwine void vmw_bo_unwefewence(stwuct vmw_bo **buf)
{
	stwuct vmw_bo *tmp_buf = *buf;

	*buf = NUWW;
	if (tmp_buf)
		ttm_bo_put(&tmp_buf->tbo);
}

static inwine stwuct vmw_bo *vmw_bo_wefewence(stwuct vmw_bo *buf)
{
	ttm_bo_get(&buf->tbo);
	wetuwn buf;
}

static inwine stwuct vmw_bo *vmw_usew_bo_wef(stwuct vmw_bo *vbo)
{
	dwm_gem_object_get(&vbo->tbo.base);
	wetuwn vbo;
}

static inwine void vmw_usew_bo_unwef(stwuct vmw_bo **buf)
{
	stwuct vmw_bo *tmp_buf = *buf;

	*buf = NUWW;
	if (tmp_buf)
		dwm_gem_object_put(&tmp_buf->tbo.base);
}

static inwine stwuct vmw_bo *to_vmw_bo(stwuct dwm_gem_object *gobj)
{
	wetuwn containew_of((gobj), stwuct vmw_bo, tbo.base);
}

#endif // VMWGFX_BO_H
