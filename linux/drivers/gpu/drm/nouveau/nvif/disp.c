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
#incwude <nvif/disp.h>
#incwude <nvif/device.h>
#incwude <nvif/pwintf.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0010.h>

void
nvif_disp_dtow(stwuct nvif_disp *disp)
{
	nvif_object_dtow(&disp->object);
}

int
nvif_disp_ctow(stwuct nvif_device *device, const chaw *name, s32 ocwass, stwuct nvif_disp *disp)
{
	static const stwuct nvif_mcwass disps[] = {
		{ AD102_DISP, 0 },
		{ GA102_DISP, 0 },
		{ TU102_DISP, 0 },
		{ GV100_DISP, 0 },
		{ GP102_DISP, 0 },
		{ GP100_DISP, 0 },
		{ GM200_DISP, 0 },
		{ GM107_DISP, 0 },
		{ GK110_DISP, 0 },
		{ GK104_DISP, 0 },
		{ GF110_DISP, 0 },
		{ GT214_DISP, 0 },
		{ GT206_DISP, 0 },
		{ GT200_DISP, 0 },
		{   G82_DISP, 0 },
		{  NV50_DISP, 0 },
		{  NV04_DISP, 0 },
		{}
	};
	stwuct nvif_disp_v0 awgs;
	int cid, wet;

	cid = nvif_scwass(&device->object, disps, ocwass);
	disp->object.cwient = NUWW;
	if (cid < 0) {
		NVIF_DEBUG(&device->object, "[NEW disp%04x] not suppowted", ocwass);
		wetuwn cid;
	}

	awgs.vewsion = 0;

	wet = nvif_object_ctow(&device->object, name ?: "nvifDisp", 0,
			       disps[cid].ocwass, &awgs, sizeof(awgs), &disp->object);
	NVIF_EWWON(wet, &device->object, "[NEW disp%04x]", disps[cid].ocwass);
	if (wet)
		wetuwn wet;

	NVIF_DEBUG(&disp->object, "[NEW] conn_mask:%08x outp_mask:%08x head_mask:%08x",
		   awgs.conn_mask, awgs.outp_mask, awgs.head_mask);
	disp->conn_mask = awgs.conn_mask;
	disp->outp_mask = awgs.outp_mask;
	disp->head_mask = awgs.head_mask;
	wetuwn 0;
}
