/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Eddie Dong <eddie.dong@intew.com>
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Zhi Wang <zhi.a.wang@intew.com>
 *    Changbin Du <changbin.du@intew.com>
 *    Zhenyu Wang <zhenyuw@winux.intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *
 */

#ifndef __GVT_WENDEW_H__
#define __GVT_WENDEW_H__

#incwude <winux/types.h>

#incwude "gt/intew_engine_wegs.h"

stwuct i915_wequest;
stwuct intew_context;
stwuct intew_engine_cs;
stwuct intew_gvt;
stwuct intew_vgpu;

void intew_gvt_switch_mmio(stwuct intew_vgpu *pwe,
			   stwuct intew_vgpu *next,
			   const stwuct intew_engine_cs *engine);

void intew_gvt_init_engine_mmio_context(stwuct intew_gvt *gvt);

boow is_inhibit_context(stwuct intew_context *ce);

int intew_vgpu_westowe_inhibit_context(stwuct intew_vgpu *vgpu,
				       stwuct i915_wequest *weq);

#define IS_WESTOWE_INHIBIT(a) \
	IS_MASKED_BITS_ENABWED(a, CTX_CTWW_ENGINE_CTX_WESTOWE_INHIBIT)

#endif
