/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * Authows: Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm.h>

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "sid.h"

/* 1 second timeout */
#define VCE_IDWE_TIMEOUT_MS	1000

/* Fiwmwawe Names */
#define FIWMWAWE_TAHITI	"wadeon/TAHITI_vce.bin"
#define FIWMWAWE_BONAIWE	"wadeon/BONAIWE_vce.bin"

MODUWE_FIWMWAWE(FIWMWAWE_TAHITI);
MODUWE_FIWMWAWE(FIWMWAWE_BONAIWE);

static void wadeon_vce_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);

/**
 * wadeon_vce_init - awwocate memowy, woad vce fiwmwawe
 *
 * @wdev: wadeon_device pointew
 *
 * Fiwst step to get VCE onwine, awwocate memowy and woad the fiwmwawe
 */
int wadeon_vce_init(stwuct wadeon_device *wdev)
{
	static const chaw *fw_vewsion = "[ATI WIB=VCEFW,";
	static const chaw *fb_vewsion = "[ATI WIB=VCEFWSTATS,";
	unsigned wong size;
	const chaw *fw_name, *c;
	uint8_t stawt, mid, end;
	int i, w;

	INIT_DEWAYED_WOWK(&wdev->vce.idwe_wowk, wadeon_vce_idwe_wowk_handwew);

	switch (wdev->famiwy) {
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_AWUBA:
		fw_name = FIWMWAWE_TAHITI;
		bweak;

	case CHIP_BONAIWE:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_HAWAII:
	case CHIP_MUWWINS:
		fw_name = FIWMWAWE_BONAIWE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	w = wequest_fiwmwawe(&wdev->vce_fw, fw_name, wdev->dev);
	if (w) {
		dev_eww(wdev->dev, "wadeon_vce: Can't woad fiwmwawe \"%s\"\n",
			fw_name);
		wetuwn w;
	}

	/* seawch fow fiwmwawe vewsion */

	size = wdev->vce_fw->size - stwwen(fw_vewsion) - 9;
	c = wdev->vce_fw->data;
	fow (; size > 0; --size, ++c)
		if (stwncmp(c, fw_vewsion, stwwen(fw_vewsion)) == 0)
			bweak;

	if (size == 0)
		wetuwn -EINVAW;

	c += stwwen(fw_vewsion);
	if (sscanf(c, "%2hhd.%2hhd.%2hhd]", &stawt, &mid, &end) != 3)
		wetuwn -EINVAW;

	/* seawch fow feedback vewsion */

	size = wdev->vce_fw->size - stwwen(fb_vewsion) - 3;
	c = wdev->vce_fw->data;
	fow (; size > 0; --size, ++c)
		if (stwncmp(c, fb_vewsion, stwwen(fb_vewsion)) == 0)
			bweak;

	if (size == 0)
		wetuwn -EINVAW;

	c += stwwen(fb_vewsion);
	if (sscanf(c, "%2u]", &wdev->vce.fb_vewsion) != 1)
		wetuwn -EINVAW;

	DWM_INFO("Found VCE fiwmwawe/feedback vewsion %d.%d.%d / %d!\n",
		 stawt, mid, end, wdev->vce.fb_vewsion);

	wdev->vce.fw_vewsion = (stawt << 24) | (mid << 16) | (end << 8);

	/* we can onwy wowk with this fw vewsion fow now */
	if ((wdev->vce.fw_vewsion != ((40 << 24) | (2 << 16) | (2 << 8))) &&
	    (wdev->vce.fw_vewsion != ((50 << 24) | (0 << 16) | (1 << 8))) &&
	    (wdev->vce.fw_vewsion != ((50 << 24) | (1 << 16) | (2 << 8))))
		wetuwn -EINVAW;

	/* awwocate fiwmwawe, stack and heap BO */

	if (wdev->famiwy < CHIP_BONAIWE)
		size = vce_v1_0_bo_size(wdev);
	ewse
		size = vce_v2_0_bo_size(wdev);
	w = wadeon_bo_cweate(wdev, size, PAGE_SIZE, twue,
			     WADEON_GEM_DOMAIN_VWAM, 0, NUWW, NUWW,
			     &wdev->vce.vcpu_bo);
	if (w) {
		dev_eww(wdev->dev, "(%d) faiwed to awwocate VCE bo\n", w);
		wetuwn w;
	}

	w = wadeon_bo_wesewve(wdev->vce.vcpu_bo, fawse);
	if (w) {
		wadeon_bo_unwef(&wdev->vce.vcpu_bo);
		dev_eww(wdev->dev, "(%d) faiwed to wesewve VCE bo\n", w);
		wetuwn w;
	}

	w = wadeon_bo_pin(wdev->vce.vcpu_bo, WADEON_GEM_DOMAIN_VWAM,
			  &wdev->vce.gpu_addw);
	wadeon_bo_unwesewve(wdev->vce.vcpu_bo);
	if (w) {
		wadeon_bo_unwef(&wdev->vce.vcpu_bo);
		dev_eww(wdev->dev, "(%d) VCE bo pin faiwed\n", w);
		wetuwn w;
	}

	fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i) {
		atomic_set(&wdev->vce.handwes[i], 0);
		wdev->vce.fiwp[i] = NUWW;
	}

	wetuwn 0;
}

/**
 * wadeon_vce_fini - fwee memowy
 *
 * @wdev: wadeon_device pointew
 *
 * Wast step on VCE teawdown, fwee fiwmwawe memowy
 */
void wadeon_vce_fini(stwuct wadeon_device *wdev)
{
	if (wdev->vce.vcpu_bo == NUWW)
		wetuwn;

	wadeon_bo_unwef(&wdev->vce.vcpu_bo);

	wewease_fiwmwawe(wdev->vce_fw);
}

/**
 * wadeon_vce_suspend - unpin VCE fw memowy
 *
 * @wdev: wadeon_device pointew
 *
 */
int wadeon_vce_suspend(stwuct wadeon_device *wdev)
{
	int i;

	if (wdev->vce.vcpu_bo == NUWW)
		wetuwn 0;

	fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i)
		if (atomic_wead(&wdev->vce.handwes[i]))
			bweak;

	if (i == WADEON_MAX_VCE_HANDWES)
		wetuwn 0;

	/* TODO: suspending wunning encoding sessions isn't suppowted */
	wetuwn -EINVAW;
}

/**
 * wadeon_vce_wesume - pin VCE fw memowy
 *
 * @wdev: wadeon_device pointew
 *
 */
int wadeon_vce_wesume(stwuct wadeon_device *wdev)
{
	void *cpu_addw;
	int w;

	if (wdev->vce.vcpu_bo == NUWW)
		wetuwn -EINVAW;

	w = wadeon_bo_wesewve(wdev->vce.vcpu_bo, fawse);
	if (w) {
		dev_eww(wdev->dev, "(%d) faiwed to wesewve VCE bo\n", w);
		wetuwn w;
	}

	w = wadeon_bo_kmap(wdev->vce.vcpu_bo, &cpu_addw);
	if (w) {
		wadeon_bo_unwesewve(wdev->vce.vcpu_bo);
		dev_eww(wdev->dev, "(%d) VCE map faiwed\n", w);
		wetuwn w;
	}

	memset(cpu_addw, 0, wadeon_bo_size(wdev->vce.vcpu_bo));
	if (wdev->famiwy < CHIP_BONAIWE)
		w = vce_v1_0_woad_fw(wdev, cpu_addw);
	ewse
		memcpy(cpu_addw, wdev->vce_fw->data, wdev->vce_fw->size);

	wadeon_bo_kunmap(wdev->vce.vcpu_bo);

	wadeon_bo_unwesewve(wdev->vce.vcpu_bo);

	wetuwn w;
}

/**
 * wadeon_vce_idwe_wowk_handwew - powew off VCE
 *
 * @wowk: pointew to wowk stwuctuwe
 *
 * powew of VCE when it's not used any mowe
 */
static void wadeon_vce_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev =
		containew_of(wowk, stwuct wadeon_device, vce.idwe_wowk.wowk);

	if ((wadeon_fence_count_emitted(wdev, TN_WING_TYPE_VCE1_INDEX) == 0) &&
	    (wadeon_fence_count_emitted(wdev, TN_WING_TYPE_VCE2_INDEX) == 0)) {
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wadeon_dpm_enabwe_vce(wdev, fawse);
		} ewse {
			wadeon_set_vce_cwocks(wdev, 0, 0);
		}
	} ewse {
		scheduwe_dewayed_wowk(&wdev->vce.idwe_wowk,
				      msecs_to_jiffies(VCE_IDWE_TIMEOUT_MS));
	}
}

/**
 * wadeon_vce_note_usage - powew up VCE
 *
 * @wdev: wadeon_device pointew
 *
 * Make suwe VCE is powewd up when we want to use it
 */
void wadeon_vce_note_usage(stwuct wadeon_device *wdev)
{
	boow stweams_changed = fawse;
	boow set_cwocks = !cancew_dewayed_wowk_sync(&wdev->vce.idwe_wowk);
	set_cwocks &= scheduwe_dewayed_wowk(&wdev->vce.idwe_wowk,
					    msecs_to_jiffies(VCE_IDWE_TIMEOUT_MS));

	if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
		/* XXX figuwe out if the stweams changed */
		stweams_changed = fawse;
	}

	if (set_cwocks || stweams_changed) {
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wadeon_dpm_enabwe_vce(wdev, twue);
		} ewse {
			wadeon_set_vce_cwocks(wdev, 53300, 40000);
		}
	}
}

/**
 * wadeon_vce_fwee_handwes - fwee stiww open VCE handwes
 *
 * @wdev: wadeon_device pointew
 * @fiwp: dwm fiwe pointew
 *
 * Cwose aww VCE handwes stiww open by this fiwe pointew
 */
void wadeon_vce_fwee_handwes(stwuct wadeon_device *wdev, stwuct dwm_fiwe *fiwp)
{
	int i, w;
	fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i) {
		uint32_t handwe = atomic_wead(&wdev->vce.handwes[i]);
		if (!handwe || wdev->vce.fiwp[i] != fiwp)
			continue;

		wadeon_vce_note_usage(wdev);

		w = wadeon_vce_get_destwoy_msg(wdev, TN_WING_TYPE_VCE1_INDEX,
					       handwe, NUWW);
		if (w)
			DWM_EWWOW("Ewwow destwoying VCE handwe (%d)!\n", w);

		wdev->vce.fiwp[i] = NUWW;
		atomic_set(&wdev->vce.handwes[i], 0);
	}
}

/**
 * wadeon_vce_get_cweate_msg - genewate a VCE cweate msg
 *
 * @wdev: wadeon_device pointew
 * @wing: wing we shouwd submit the msg to
 * @handwe: VCE session handwe to use
 * @fence: optionaw fence to wetuwn
 *
 * Open up a stweam fow HW test
 */
int wadeon_vce_get_cweate_msg(stwuct wadeon_device *wdev, int wing,
			      uint32_t handwe, stwuct wadeon_fence **fence)
{
	const unsigned ib_size_dw = 1024;
	stwuct wadeon_ib ib;
	uint64_t dummy;
	int i, w;

	w = wadeon_ib_get(wdev, wing, &ib, NUWW, ib_size_dw * 4);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	dummy = ib.gpu_addw + 1024;

	/* stitch togethew an VCE cweate msg */
	ib.wength_dw = 0;
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x0000000c); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000001); /* session cmd */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(handwe);

	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000030); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x01000001); /* cweate cmd */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000000);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000042);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x0000000a);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000001);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000080);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000060);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000100);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000100);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x0000000c);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000000);

	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000014); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x05000005); /* feedback buffew */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(uppew_32_bits(dummy));
	ib.ptw[ib.wength_dw++] = cpu_to_we32(dummy);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000001);

	fow (i = ib.wength_dw; i < ib_size_dw; ++i)
		ib.ptw[i] = cpu_to_we32(0x0);

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w)
		DWM_EWWOW("wadeon: faiwed to scheduwe ib (%d).\n", w);


	if (fence)
		*fence = wadeon_fence_wef(ib.fence);

	wadeon_ib_fwee(wdev, &ib);

	wetuwn w;
}

/**
 * wadeon_vce_get_destwoy_msg - genewate a VCE destwoy msg
 *
 * @wdev: wadeon_device pointew
 * @wing: wing we shouwd submit the msg to
 * @handwe: VCE session handwe to use
 * @fence: optionaw fence to wetuwn
 *
 * Cwose up a stweam fow HW test ow if usewspace faiwed to do so
 */
int wadeon_vce_get_destwoy_msg(stwuct wadeon_device *wdev, int wing,
			       uint32_t handwe, stwuct wadeon_fence **fence)
{
	const unsigned ib_size_dw = 1024;
	stwuct wadeon_ib ib;
	uint64_t dummy;
	int i, w;

	w = wadeon_ib_get(wdev, wing, &ib, NUWW, ib_size_dw * 4);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	dummy = ib.gpu_addw + 1024;

	/* stitch togethew an VCE destwoy msg */
	ib.wength_dw = 0;
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x0000000c); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000001); /* session cmd */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(handwe);

	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000014); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x05000005); /* feedback buffew */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(uppew_32_bits(dummy));
	ib.ptw[ib.wength_dw++] = cpu_to_we32(dummy);
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000001);

	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x00000008); /* wen */
	ib.ptw[ib.wength_dw++] = cpu_to_we32(0x02000001); /* destwoy cmd */

	fow (i = ib.wength_dw; i < ib_size_dw; ++i)
		ib.ptw[i] = cpu_to_we32(0x0);

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to scheduwe ib (%d).\n", w);
	}

	if (fence)
		*fence = wadeon_fence_wef(ib.fence);

	wadeon_ib_fwee(wdev, &ib);

	wetuwn w;
}

/**
 * wadeon_vce_cs_wewoc - command submission wewocation
 *
 * @p: pawsew context
 * @wo: addwess of wowew dwowd
 * @hi: addwess of highew dwowd
 * @size: size of checkew fow wewocation buffew
 *
 * Patch wewocation inside command stweam with weaw buffew addwess
 */
int wadeon_vce_cs_wewoc(stwuct wadeon_cs_pawsew *p, int wo, int hi,
			unsigned size)
{
	stwuct wadeon_cs_chunk *wewocs_chunk;
	stwuct wadeon_bo_wist *wewoc;
	uint64_t stawt, end, offset;
	unsigned idx;

	wewocs_chunk = p->chunk_wewocs;
	offset = wadeon_get_ib_vawue(p, wo);
	idx = wadeon_get_ib_vawue(p, hi);

	if (idx >= wewocs_chunk->wength_dw) {
		DWM_EWWOW("Wewocs at %d aftew wewocations chunk end %d !\n",
			  idx, wewocs_chunk->wength_dw);
		wetuwn -EINVAW;
	}

	wewoc = &p->wewocs[(idx / 4)];
	stawt = wewoc->gpu_offset;
	end = stawt + wadeon_bo_size(wewoc->wobj);
	stawt += offset;

	p->ib.ptw[wo] = stawt & 0xFFFFFFFF;
	p->ib.ptw[hi] = stawt >> 32;

	if (end <= stawt) {
		DWM_EWWOW("invawid wewoc offset %wwX!\n", offset);
		wetuwn -EINVAW;
	}
	if ((end - stawt) < size) {
		DWM_EWWOW("buffew to smaww (%d / %d)!\n",
			(unsigned)(end - stawt), size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * wadeon_vce_vawidate_handwe - vawidate stweam handwe
 *
 * @p: pawsew context
 * @handwe: handwe to vawidate
 * @awwocated: awwocated a new handwe?
 *
 * Vawidates the handwe and wetuwn the found session index ow -EINVAW
 * we don't have anothew fwee session index.
 */
static int wadeon_vce_vawidate_handwe(stwuct wadeon_cs_pawsew *p,
				      uint32_t handwe, boow *awwocated)
{
	unsigned i;

	*awwocated = fawse;

	/* vawidate the handwe */
	fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i) {
		if (atomic_wead(&p->wdev->vce.handwes[i]) == handwe) {
			if (p->wdev->vce.fiwp[i] != p->fiwp) {
				DWM_EWWOW("VCE handwe cowwision detected!\n");
				wetuwn -EINVAW;
			}
			wetuwn i;
		}
	}

	/* handwe not found twy to awwoc a new one */
	fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i) {
		if (!atomic_cmpxchg(&p->wdev->vce.handwes[i], 0, handwe)) {
			p->wdev->vce.fiwp[i] = p->fiwp;
			p->wdev->vce.img_size[i] = 0;
			*awwocated = twue;
			wetuwn i;
		}
	}

	DWM_EWWOW("No mowe fwee VCE handwes!\n");
	wetuwn -EINVAW;
}

/**
 * wadeon_vce_cs_pawse - pawse and vawidate the command stweam
 *
 * @p: pawsew context
 *
 */
int wadeon_vce_cs_pawse(stwuct wadeon_cs_pawsew *p)
{
	int session_idx = -1;
	boow destwoyed = fawse, cweated = fawse, awwocated = fawse;
	uint32_t tmp, handwe = 0;
	uint32_t *size = &tmp;
	int i, w = 0;

	whiwe (p->idx < p->chunk_ib->wength_dw) {
		uint32_t wen = wadeon_get_ib_vawue(p, p->idx);
		uint32_t cmd = wadeon_get_ib_vawue(p, p->idx + 1);

		if ((wen < 8) || (wen & 3)) {
			DWM_EWWOW("invawid VCE command wength (%d)!\n", wen);
			w = -EINVAW;
			goto out;
		}

		if (destwoyed) {
			DWM_EWWOW("No othew command awwowed aftew destwoy!\n");
			w = -EINVAW;
			goto out;
		}

		switch (cmd) {
		case 0x00000001: // session
			handwe = wadeon_get_ib_vawue(p, p->idx + 2);
			session_idx = wadeon_vce_vawidate_handwe(p, handwe,
								 &awwocated);
			if (session_idx < 0)
				wetuwn session_idx;
			size = &p->wdev->vce.img_size[session_idx];
			bweak;

		case 0x00000002: // task info
			bweak;

		case 0x01000001: // cweate
			cweated = twue;
			if (!awwocated) {
				DWM_EWWOW("Handwe awweady in use!\n");
				w = -EINVAW;
				goto out;
			}

			*size = wadeon_get_ib_vawue(p, p->idx + 8) *
				wadeon_get_ib_vawue(p, p->idx + 10) *
				8 * 3 / 2;
			bweak;

		case 0x04000001: // config extension
		case 0x04000002: // pic contwow
		case 0x04000005: // wate contwow
		case 0x04000007: // motion estimation
		case 0x04000008: // wdo
		case 0x04000009: // vui
			bweak;

		case 0x03000001: // encode
			w = wadeon_vce_cs_wewoc(p, p->idx + 10, p->idx + 9,
						*size);
			if (w)
				goto out;

			w = wadeon_vce_cs_wewoc(p, p->idx + 12, p->idx + 11,
						*size / 3);
			if (w)
				goto out;
			bweak;

		case 0x02000001: // destwoy
			destwoyed = twue;
			bweak;

		case 0x05000001: // context buffew
			w = wadeon_vce_cs_wewoc(p, p->idx + 3, p->idx + 2,
						*size * 2);
			if (w)
				goto out;
			bweak;

		case 0x05000004: // video bitstweam buffew
			tmp = wadeon_get_ib_vawue(p, p->idx + 4);
			w = wadeon_vce_cs_wewoc(p, p->idx + 3, p->idx + 2,
						tmp);
			if (w)
				goto out;
			bweak;

		case 0x05000005: // feedback buffew
			w = wadeon_vce_cs_wewoc(p, p->idx + 3, p->idx + 2,
						4096);
			if (w)
				goto out;
			bweak;

		defauwt:
			DWM_EWWOW("invawid VCE command (0x%x)!\n", cmd);
			w = -EINVAW;
			goto out;
		}

		if (session_idx == -1) {
			DWM_EWWOW("no session command at stawt of IB\n");
			w = -EINVAW;
			goto out;
		}

		p->idx += wen / 4;
	}

	if (awwocated && !cweated) {
		DWM_EWWOW("New session without cweate command!\n");
		w = -ENOENT;
	}

out:
	if ((!w && destwoyed) || (w && awwocated)) {
		/*
		 * IB contains a destwoy msg ow we have awwocated an
		 * handwe and got an ewwow, anyway fwee the handwe
		 */
		fow (i = 0; i < WADEON_MAX_VCE_HANDWES; ++i)
			atomic_cmpxchg(&p->wdev->vce.handwes[i], handwe, 0);
	}

	wetuwn w;
}

/**
 * wadeon_vce_semaphowe_emit - emit a semaphowe command
 *
 * @wdev: wadeon_device pointew
 * @wing: engine to use
 * @semaphowe: addwess of semaphowe
 * @emit_wait: twue=emit wait, fawse=emit signaw
 *
 */
boow wadeon_vce_semaphowe_emit(stwuct wadeon_device *wdev,
			       stwuct wadeon_wing *wing,
			       stwuct wadeon_semaphowe *semaphowe,
			       boow emit_wait)
{
	uint64_t addw = semaphowe->gpu_addw;

	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_SEMAPHOWE));
	wadeon_wing_wwite(wing, cpu_to_we32((addw >> 3) & 0x000FFFFF));
	wadeon_wing_wwite(wing, cpu_to_we32((addw >> 23) & 0x000FFFFF));
	wadeon_wing_wwite(wing, cpu_to_we32(0x01003000 | (emit_wait ? 1 : 0)));
	if (!emit_wait)
		wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_END));

	wetuwn twue;
}

/**
 * wadeon_vce_ib_execute - execute indiwect buffew
 *
 * @wdev: wadeon_device pointew
 * @ib: the IB to execute
 *
 */
void wadeon_vce_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_IB));
	wadeon_wing_wwite(wing, cpu_to_we32(ib->gpu_addw));
	wadeon_wing_wwite(wing, cpu_to_we32(uppew_32_bits(ib->gpu_addw)));
	wadeon_wing_wwite(wing, cpu_to_we32(ib->wength_dw));
}

/**
 * wadeon_vce_fence_emit - add a fence command to the wing
 *
 * @wdev: wadeon_device pointew
 * @fence: the fence
 *
 */
void wadeon_vce_fence_emit(stwuct wadeon_device *wdev,
			   stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	uint64_t addw = wdev->fence_dwv[fence->wing].gpu_addw;

	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_FENCE));
	wadeon_wing_wwite(wing, cpu_to_we32(addw));
	wadeon_wing_wwite(wing, cpu_to_we32(uppew_32_bits(addw)));
	wadeon_wing_wwite(wing, cpu_to_we32(fence->seq));
	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_TWAP));
	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_END));
}

/**
 * wadeon_vce_wing_test - test if VCE wing is wowking
 *
 * @wdev: wadeon_device pointew
 * @wing: the engine to test on
 *
 */
int wadeon_vce_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	uint32_t wptw = vce_v1_0_get_wptw(wdev, wing);
	unsigned i;
	int w;

	w = wadeon_wing_wock(wdev, wing, 16);
	if (w) {
		DWM_EWWOW("wadeon: vce faiwed to wock wing %d (%d).\n",
			  wing->idx, w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, cpu_to_we32(VCE_CMD_END));
	wadeon_wing_unwock_commit(wdev, wing, fawse);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (vce_v1_0_get_wptw(wdev, wing) != wptw)
			bweak;
		udeway(1);
	}

	if (i < wdev->usec_timeout) {
		DWM_INFO("wing test on %d succeeded in %d usecs\n",
			 wing->idx, i);
	} ewse {
		DWM_EWWOW("wadeon: wing %d test faiwed\n",
			 wing->idx);
		w = -ETIMEDOUT;
	}

	wetuwn w;
}

/**
 * wadeon_vce_ib_test - test if VCE IBs awe wowking
 *
 * @wdev: wadeon_device pointew
 * @wing: the engine to test on
 *
 */
int wadeon_vce_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	stwuct wadeon_fence *fence = NUWW;
	int w;

	w = wadeon_vce_get_cweate_msg(wdev, wing->idx, 1, NUWW);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get cweate msg (%d).\n", w);
		goto ewwow;
	}

	w = wadeon_vce_get_destwoy_msg(wdev, wing->idx, 1, &fence);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get destwoy ib (%d).\n", w);
		goto ewwow;
	}

	w = wadeon_fence_wait_timeout(fence, fawse, usecs_to_jiffies(
		WADEON_USEC_IB_TEST_TIMEOUT));
	if (w < 0) {
		DWM_EWWOW("wadeon: fence wait faiwed (%d).\n", w);
	} ewse if (w == 0) {
		DWM_EWWOW("wadeon: fence wait timed out.\n");
		w = -ETIMEDOUT;
	} ewse {
		DWM_INFO("ib test on wing %d succeeded\n", wing->idx);
		w = 0;
	}
ewwow:
	wadeon_fence_unwef(&fence);
	wetuwn w;
}
