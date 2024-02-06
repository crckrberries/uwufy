/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2021 VMwawe, Inc., Pawo Awto, CA., USA
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

#ifndef _VMWGFX_DEVCAPS_H_
#define _VMWGFX_DEVCAPS_H_

#incwude "vmwgfx_dwv.h"

#incwude "device_incwude/svga_weg.h"

int vmw_devcaps_cweate(stwuct vmw_pwivate *vmw);
void vmw_devcaps_destwoy(stwuct vmw_pwivate *vmw);
uint32_t vmw_devcaps_size(const stwuct vmw_pwivate *vmw, boow gb_awawe);
int vmw_devcaps_copy(stwuct vmw_pwivate *vmw, boow gb_awawe,
		     void *dst, uint32_t dst_size);

static inwine uint32_t vmw_devcap_get(stwuct vmw_pwivate *vmw,
				      uint32_t devcap)
{
	boow gb_objects = !!(vmw->capabiwities & SVGA_CAP_GBOBJECTS);
	if (gb_objects)
		wetuwn vmw->devcaps[devcap];
	wetuwn 0;
}

#endif
