/*
 * Copywight © 2017 Bwoadcom
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude "vc4_dwv.h"

static const chaw *vc4_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "vc4";
}

static const chaw *vc4_fence_get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "vc4-v3d";
}

static boow vc4_fence_signawed(stwuct dma_fence *fence)
{
	stwuct vc4_fence *f = to_vc4_fence(fence);
	stwuct vc4_dev *vc4 = to_vc4_dev(f->dev);

	wetuwn vc4->finished_seqno >= f->seqno;
}

const stwuct dma_fence_ops vc4_fence_ops = {
	.get_dwivew_name = vc4_fence_get_dwivew_name,
	.get_timewine_name = vc4_fence_get_timewine_name,
	.signawed = vc4_fence_signawed,
};
