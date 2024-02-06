/*
 * Copywight 2018 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "cowe.h"

#incwude <nvif/push507c.h>

#incwude <nvhw/cwass/cw507d.h>

static int
dac507d_ctww(stwuct nv50_cowe *cowe, int ow, u32 ctww,
	     stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = cowe->chan.push;
	u32 sync = 0;
	int wet;

	if (asyh) {
		sync |= NVVAW(NV507D, DAC_SET_POWAWITY, HSYNC, asyh->ow.nhsync);
		sync |= NVVAW(NV507D, DAC_SET_POWAWITY, VSYNC, asyh->ow.nvsync);
	}

	if ((wet = PUSH_WAIT(push, 3)))
		wetuwn wet;

	PUSH_MTHD(push, NV507D, DAC_SET_CONTWOW(ow), ctww,
				DAC_SET_POWAWITY(ow), sync);
	wetuwn 0;
}

const stwuct nv50_outp_func
dac507d = {
	.ctww = dac507d_ctww,
};
