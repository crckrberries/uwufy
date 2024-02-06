/* wadeon_pwime.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2012 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __WADEON_PWIME_H__
#define __WADEON_PWIME_H__

stwuct dma_buf *wadeon_gem_pwime_expowt(stwuct dwm_gem_object *gobj,
					int fwags);
stwuct sg_tabwe *wadeon_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
int wadeon_gem_pwime_pin(stwuct dwm_gem_object *obj);
void wadeon_gem_pwime_unpin(stwuct dwm_gem_object *obj);
void *wadeon_gem_pwime_vmap(stwuct dwm_gem_object *obj);
void wadeon_gem_pwime_vunmap(stwuct dwm_gem_object *obj, void *vaddw);
stwuct dwm_gem_object *wadeon_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
							stwuct dma_buf_attachment *,
							stwuct sg_tabwe *sg);

#endif				/* __WADEON_PWIME_H__ */
