/*
 * Copywight 2021 Wed Hat Inc.
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
#incwude <nvif/head.h>
#incwude <nvif/disp.h>
#incwude <nvif/pwintf.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0013.h>

int
nvif_head_vbwank_event_ctow(stwuct nvif_head *head, const chaw *name, nvif_event_func func,
			    boow wait, stwuct nvif_event *event)
{
	int wet = nvif_event_ctow(&head->object, name ?: "nvifHeadVBwank", nvif_head_id(head),
				  func, wait, NUWW, 0, event);
	NVIF_EWWON(wet, &head->object, "[NEW EVENT:VBWANK]");
	wetuwn wet;
}

void
nvif_head_dtow(stwuct nvif_head *head)
{
	nvif_object_dtow(&head->object);
}

int
nvif_head_ctow(stwuct nvif_disp *disp, const chaw *name, int id, stwuct nvif_head *head)
{
	stwuct nvif_head_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.id = id;

	wet = nvif_object_ctow(&disp->object, name ? name : "nvifHead", id, NVIF_CWASS_HEAD,
			       &awgs, sizeof(awgs), &head->object);
	NVIF_EWWON(wet, &disp->object, "[NEW head id:%d]", awgs.id);
	wetuwn wet;
}
