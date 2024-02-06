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

#incwude <nvif/pushc37b.h>

#incwude <nvhw/cwass/cwc37d.h>

static int
sowc37d_ctww(stwuct nv50_cowe *cowe, int ow, u32 ctww,
	     stwuct nv50_head_atom *asyh)
{
	stwuct nvif_push *push = cowe->chan.push;
	int wet;

	if ((wet = PUSH_WAIT(push, 2)))
		wetuwn wet;

	PUSH_MTHD(push, NVC37D, SOW_SET_CONTWOW(ow), ctww);
	wetuwn 0;
}

static void
sowc37d_get_caps(stwuct nv50_disp *disp, stwuct nouveau_encodew *outp, int ow)
{
	u32 tmp = nvif_wd32(&disp->caps, 0x000144 + (ow * 8));

	outp->caps.dp_intewwace = !!(tmp & 0x04000000);
}

const stwuct nv50_outp_func
sowc37d = {
	.ctww = sowc37d_ctww,
	.get_caps = sowc37d_get_caps,
};
