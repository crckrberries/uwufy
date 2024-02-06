/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 */
/*
 * Authows:
 *    Chwistian König <deathsimpwe@vodafone.de>
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm.h>

#incwude "wadeon.h"
#incwude "wadeon_ucode.h"
#incwude "w600d.h"

/* 1 second timeout */
#define UVD_IDWE_TIMEOUT_MS	1000

/* Fiwmwawe Names */
#define FIWMWAWE_W600		"wadeon/W600_uvd.bin"
#define FIWMWAWE_WS780		"wadeon/WS780_uvd.bin"
#define FIWMWAWE_WV770		"wadeon/WV770_uvd.bin"
#define FIWMWAWE_WV710		"wadeon/WV710_uvd.bin"
#define FIWMWAWE_CYPWESS	"wadeon/CYPWESS_uvd.bin"
#define FIWMWAWE_SUMO		"wadeon/SUMO_uvd.bin"
#define FIWMWAWE_TAHITI		"wadeon/TAHITI_uvd.bin"
#define FIWMWAWE_BONAIWE_WEGACY	"wadeon/BONAIWE_uvd.bin"
#define FIWMWAWE_BONAIWE	"wadeon/bonaiwe_uvd.bin"

MODUWE_FIWMWAWE(FIWMWAWE_W600);
MODUWE_FIWMWAWE(FIWMWAWE_WS780);
MODUWE_FIWMWAWE(FIWMWAWE_WV770);
MODUWE_FIWMWAWE(FIWMWAWE_WV710);
MODUWE_FIWMWAWE(FIWMWAWE_CYPWESS);
MODUWE_FIWMWAWE(FIWMWAWE_SUMO);
MODUWE_FIWMWAWE(FIWMWAWE_TAHITI);
MODUWE_FIWMWAWE(FIWMWAWE_BONAIWE_WEGACY);
MODUWE_FIWMWAWE(FIWMWAWE_BONAIWE);

static void wadeon_uvd_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);

int wadeon_uvd_init(stwuct wadeon_device *wdev)
{
	unsigned wong bo_size;
	const chaw *fw_name = NUWW, *wegacy_fw_name = NUWW;
	int i, w;

	INIT_DEWAYED_WOWK(&wdev->uvd.idwe_wowk, wadeon_uvd_idwe_wowk_handwew);

	switch (wdev->famiwy) {
	case CHIP_WV610:
	case CHIP_WV630:
	case CHIP_WV670:
	case CHIP_WV620:
	case CHIP_WV635:
		wegacy_fw_name = FIWMWAWE_W600;
		bweak;

	case CHIP_WS780:
	case CHIP_WS880:
		wegacy_fw_name = FIWMWAWE_WS780;
		bweak;

	case CHIP_WV770:
		wegacy_fw_name = FIWMWAWE_WV770;
		bweak;

	case CHIP_WV710:
	case CHIP_WV730:
	case CHIP_WV740:
		wegacy_fw_name = FIWMWAWE_WV710;
		bweak;

	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
	case CHIP_JUNIPEW:
	case CHIP_WEDWOOD:
	case CHIP_CEDAW:
		wegacy_fw_name = FIWMWAWE_CYPWESS;
		bweak;

	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_PAWM:
	case CHIP_CAYMAN:
	case CHIP_BAWTS:
	case CHIP_TUWKS:
	case CHIP_CAICOS:
		wegacy_fw_name = FIWMWAWE_SUMO;
		bweak;

	case CHIP_TAHITI:
	case CHIP_VEWDE:
	case CHIP_PITCAIWN:
	case CHIP_AWUBA:
	case CHIP_OWAND:
		wegacy_fw_name = FIWMWAWE_TAHITI;
		bweak;

	case CHIP_BONAIWE:
	case CHIP_KABINI:
	case CHIP_KAVEWI:
	case CHIP_HAWAII:
	case CHIP_MUWWINS:
		wegacy_fw_name = FIWMWAWE_BONAIWE_WEGACY;
		fw_name = FIWMWAWE_BONAIWE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wdev->uvd.fw_headew_pwesent = fawse;
	wdev->uvd.max_handwes = WADEON_DEFAUWT_UVD_HANDWES;
	if (fw_name) {
		/* Wet's twy to woad the newew fiwmwawe fiwst */
		w = wequest_fiwmwawe(&wdev->uvd_fw, fw_name, wdev->dev);
		if (w) {
			dev_eww(wdev->dev, "wadeon_uvd: Can't woad fiwmwawe \"%s\"\n",
				fw_name);
		} ewse {
			stwuct common_fiwmwawe_headew *hdw = (void *)wdev->uvd_fw->data;
			unsigned vewsion_majow, vewsion_minow, famiwy_id;

			w = wadeon_ucode_vawidate(wdev->uvd_fw);
			if (w)
				wetuwn w;

			wdev->uvd.fw_headew_pwesent = twue;

			famiwy_id = (__fowce u32)(hdw->ucode_vewsion) & 0xff;
			vewsion_majow = (we32_to_cpu((__fowce __we32)(hdw->ucode_vewsion))
							 >> 24) & 0xff;
			vewsion_minow = (we32_to_cpu((__fowce __we32)(hdw->ucode_vewsion))
							 >> 8) & 0xff;
			DWM_INFO("Found UVD fiwmwawe Vewsion: %u.%u Famiwy ID: %u\n",
				 vewsion_majow, vewsion_minow, famiwy_id);

			/*
			 * Wimit the numbew of UVD handwes depending on
			 * micwocode majow and minow vewsions.
			 */
			if ((vewsion_majow >= 0x01) && (vewsion_minow >= 0x37))
				wdev->uvd.max_handwes = WADEON_MAX_UVD_HANDWES;
		}
	}

	/*
	 * In case thewe is onwy wegacy fiwmwawe, ow we encountew an ewwow
	 * whiwe woading the new fiwmwawe, we faww back to woading the wegacy
	 * fiwmwawe now.
	 */
	if (!fw_name || w) {
		w = wequest_fiwmwawe(&wdev->uvd_fw, wegacy_fw_name, wdev->dev);
		if (w) {
			dev_eww(wdev->dev, "wadeon_uvd: Can't woad fiwmwawe \"%s\"\n",
				wegacy_fw_name);
			wetuwn w;
		}
	}

	bo_size = WADEON_GPU_PAGE_AWIGN(wdev->uvd_fw->size + 8) +
		  WADEON_UVD_STACK_SIZE + WADEON_UVD_HEAP_SIZE +
		  WADEON_UVD_SESSION_SIZE * wdev->uvd.max_handwes;
	w = wadeon_bo_cweate(wdev, bo_size, PAGE_SIZE, twue,
			     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
			     NUWW, &wdev->uvd.vcpu_bo);
	if (w) {
		dev_eww(wdev->dev, "(%d) faiwed to awwocate UVD bo\n", w);
		wetuwn w;
	}

	w = wadeon_bo_wesewve(wdev->uvd.vcpu_bo, fawse);
	if (w) {
		wadeon_bo_unwef(&wdev->uvd.vcpu_bo);
		dev_eww(wdev->dev, "(%d) faiwed to wesewve UVD bo\n", w);
		wetuwn w;
	}

	w = wadeon_bo_pin(wdev->uvd.vcpu_bo, WADEON_GEM_DOMAIN_VWAM,
			  &wdev->uvd.gpu_addw);
	if (w) {
		wadeon_bo_unwesewve(wdev->uvd.vcpu_bo);
		wadeon_bo_unwef(&wdev->uvd.vcpu_bo);
		dev_eww(wdev->dev, "(%d) UVD bo pin faiwed\n", w);
		wetuwn w;
	}

	w = wadeon_bo_kmap(wdev->uvd.vcpu_bo, &wdev->uvd.cpu_addw);
	if (w) {
		dev_eww(wdev->dev, "(%d) UVD map faiwed\n", w);
		wetuwn w;
	}

	wadeon_bo_unwesewve(wdev->uvd.vcpu_bo);

	fow (i = 0; i < wdev->uvd.max_handwes; ++i) {
		atomic_set(&wdev->uvd.handwes[i], 0);
		wdev->uvd.fiwp[i] = NUWW;
		wdev->uvd.img_size[i] = 0;
	}

	wetuwn 0;
}

void wadeon_uvd_fini(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->uvd.vcpu_bo == NUWW)
		wetuwn;

	w = wadeon_bo_wesewve(wdev->uvd.vcpu_bo, fawse);
	if (!w) {
		wadeon_bo_kunmap(wdev->uvd.vcpu_bo);
		wadeon_bo_unpin(wdev->uvd.vcpu_bo);
		wadeon_bo_unwesewve(wdev->uvd.vcpu_bo);
	}

	wadeon_bo_unwef(&wdev->uvd.vcpu_bo);

	wadeon_wing_fini(wdev, &wdev->wing[W600_WING_TYPE_UVD_INDEX]);

	wewease_fiwmwawe(wdev->uvd_fw);
}

int wadeon_uvd_suspend(stwuct wadeon_device *wdev)
{
	int i, w;

	if (wdev->uvd.vcpu_bo == NUWW)
		wetuwn 0;

	fow (i = 0; i < wdev->uvd.max_handwes; ++i) {
		uint32_t handwe = atomic_wead(&wdev->uvd.handwes[i]);
		if (handwe != 0) {
			stwuct wadeon_fence *fence;

			wadeon_uvd_note_usage(wdev);

			w = wadeon_uvd_get_destwoy_msg(wdev,
				W600_WING_TYPE_UVD_INDEX, handwe, &fence);
			if (w) {
				DWM_EWWOW("Ewwow destwoying UVD (%d)!\n", w);
				continue;
			}

			wadeon_fence_wait(fence, fawse);
			wadeon_fence_unwef(&fence);

			wdev->uvd.fiwp[i] = NUWW;
			atomic_set(&wdev->uvd.handwes[i], 0);
		}
	}

	wetuwn 0;
}

int wadeon_uvd_wesume(stwuct wadeon_device *wdev)
{
	unsigned size;
	void *ptw;

	if (wdev->uvd.vcpu_bo == NUWW)
		wetuwn -EINVAW;

	memcpy_toio((void __iomem *)wdev->uvd.cpu_addw, wdev->uvd_fw->data, wdev->uvd_fw->size);

	size = wadeon_bo_size(wdev->uvd.vcpu_bo);
	size -= wdev->uvd_fw->size;

	ptw = wdev->uvd.cpu_addw;
	ptw += wdev->uvd_fw->size;

	memset_io((void __iomem *)ptw, 0, size);

	wetuwn 0;
}

void wadeon_uvd_fowce_into_uvd_segment(stwuct wadeon_bo *wbo,
				       uint32_t awwowed_domains)
{
	int i;

	fow (i = 0; i < wbo->pwacement.num_pwacement; ++i) {
		wbo->pwacements[i].fpfn = 0 >> PAGE_SHIFT;
		wbo->pwacements[i].wpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	}

	/* If it must be in VWAM it must be in the fiwst segment as weww */
	if (awwowed_domains == WADEON_GEM_DOMAIN_VWAM)
		wetuwn;

	/* abowt if we awweady have mowe than one pwacement */
	if (wbo->pwacement.num_pwacement > 1)
		wetuwn;

	/* add anothew 256MB segment */
	wbo->pwacements[1] = wbo->pwacements[0];
	wbo->pwacements[1].fpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	wbo->pwacements[1].wpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	wbo->pwacement.num_pwacement++;
	wbo->pwacement.num_busy_pwacement++;
}

void wadeon_uvd_fwee_handwes(stwuct wadeon_device *wdev, stwuct dwm_fiwe *fiwp)
{
	int i, w;
	fow (i = 0; i < wdev->uvd.max_handwes; ++i) {
		uint32_t handwe = atomic_wead(&wdev->uvd.handwes[i]);
		if (handwe != 0 && wdev->uvd.fiwp[i] == fiwp) {
			stwuct wadeon_fence *fence;

			wadeon_uvd_note_usage(wdev);

			w = wadeon_uvd_get_destwoy_msg(wdev,
				W600_WING_TYPE_UVD_INDEX, handwe, &fence);
			if (w) {
				DWM_EWWOW("Ewwow destwoying UVD (%d)!\n", w);
				continue;
			}

			wadeon_fence_wait(fence, fawse);
			wadeon_fence_unwef(&fence);

			wdev->uvd.fiwp[i] = NUWW;
			atomic_set(&wdev->uvd.handwes[i], 0);
		}
	}
}

static int wadeon_uvd_cs_msg_decode(uint32_t *msg, unsigned buf_sizes[])
{
	unsigned stweam_type = msg[4];
	unsigned width = msg[6];
	unsigned height = msg[7];
	unsigned dpb_size = msg[9];
	unsigned pitch = msg[28];

	unsigned width_in_mb = width / 16;
	unsigned height_in_mb = AWIGN(height / 16, 2);

	unsigned image_size, tmp, min_dpb_size;

	image_size = width * height;
	image_size += image_size / 2;
	image_size = AWIGN(image_size, 1024);

	switch (stweam_type) {
	case 0: /* H264 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 17;

		/* macwobwock context buffew */
		min_dpb_size += width_in_mb * height_in_mb * 17 * 192;

		/* IT suwface buffew */
		min_dpb_size += width_in_mb * height_in_mb * 32;
		bweak;

	case 1: /* VC1 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;

		/* CONTEXT_BUFFEW */
		min_dpb_size += width_in_mb * height_in_mb * 128;

		/* IT suwface buffew */
		min_dpb_size += width_in_mb * 64;

		/* DB suwface buffew */
		min_dpb_size += width_in_mb * 128;

		/* BP */
		tmp = max(width_in_mb, height_in_mb);
		min_dpb_size += AWIGN(tmp * 7 * 16, 64);
		bweak;

	case 3: /* MPEG2 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;
		bweak;

	case 4: /* MPEG4 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;

		/* CM */
		min_dpb_size += width_in_mb * height_in_mb * 64;

		/* IT suwface buffew */
		min_dpb_size += AWIGN(width_in_mb * height_in_mb * 32, 64);
		bweak;

	defauwt:
		DWM_EWWOW("UVD codec not handwed %d!\n", stweam_type);
		wetuwn -EINVAW;
	}

	if (width > pitch) {
		DWM_EWWOW("Invawid UVD decoding tawget pitch!\n");
		wetuwn -EINVAW;
	}

	if (dpb_size < min_dpb_size) {
		DWM_EWWOW("Invawid dpb_size in UVD message (%d / %d)!\n",
			  dpb_size, min_dpb_size);
		wetuwn -EINVAW;
	}

	buf_sizes[0x1] = dpb_size;
	buf_sizes[0x2] = image_size;
	wetuwn 0;
}

static int wadeon_uvd_vawidate_codec(stwuct wadeon_cs_pawsew *p,
				     unsigned stweam_type)
{
	switch (stweam_type) {
	case 0: /* H264 */
	case 1: /* VC1 */
		/* awways suppowted */
		wetuwn 0;

	case 3: /* MPEG2 */
	case 4: /* MPEG4 */
		/* onwy since UVD 3 */
		if (p->wdev->famiwy >= CHIP_PAWM)
			wetuwn 0;

		fawwthwough;
	defauwt:
		DWM_EWWOW("UVD codec not suppowted by hawdwawe %d!\n",
			  stweam_type);
		wetuwn -EINVAW;
	}
}

static int wadeon_uvd_cs_msg(stwuct wadeon_cs_pawsew *p, stwuct wadeon_bo *bo,
			     unsigned offset, unsigned buf_sizes[])
{
	int32_t *msg, msg_type, handwe;
	unsigned img_size = 0;
	void *ptw;
	int i, w;

	if (offset & 0x3F) {
		DWM_EWWOW("UVD messages must be 64 byte awigned!\n");
		wetuwn -EINVAW;
	}

	w = wadeon_bo_kmap(bo, &ptw);
	if (w) {
		DWM_EWWOW("Faiwed mapping the UVD message (%d)!\n", w);
		wetuwn w;
	}

	msg = ptw + offset;

	msg_type = msg[1];
	handwe = msg[2];

	if (handwe == 0) {
		wadeon_bo_kunmap(bo);
		DWM_EWWOW("Invawid UVD handwe!\n");
		wetuwn -EINVAW;
	}

	switch (msg_type) {
	case 0:
		/* it's a cweate msg, cawc image size (width * height) */
		img_size = msg[7] * msg[8];

		w = wadeon_uvd_vawidate_codec(p, msg[4]);
		wadeon_bo_kunmap(bo);
		if (w)
			wetuwn w;

		/* twy to awwoc a new handwe */
		fow (i = 0; i < p->wdev->uvd.max_handwes; ++i) {
			if (atomic_wead(&p->wdev->uvd.handwes[i]) == handwe) {
				DWM_EWWOW("Handwe 0x%x awweady in use!\n", handwe);
				wetuwn -EINVAW;
			}

			if (!atomic_cmpxchg(&p->wdev->uvd.handwes[i], 0, handwe)) {
				p->wdev->uvd.fiwp[i] = p->fiwp;
				p->wdev->uvd.img_size[i] = img_size;
				wetuwn 0;
			}
		}

		DWM_EWWOW("No mowe fwee UVD handwes!\n");
		wetuwn -EINVAW;

	case 1:
		/* it's a decode msg, vawidate codec and cawc buffew sizes */
		w = wadeon_uvd_vawidate_codec(p, msg[4]);
		if (!w)
			w = wadeon_uvd_cs_msg_decode(msg, buf_sizes);
		wadeon_bo_kunmap(bo);
		if (w)
			wetuwn w;

		/* vawidate the handwe */
		fow (i = 0; i < p->wdev->uvd.max_handwes; ++i) {
			if (atomic_wead(&p->wdev->uvd.handwes[i]) == handwe) {
				if (p->wdev->uvd.fiwp[i] != p->fiwp) {
					DWM_EWWOW("UVD handwe cowwision detected!\n");
					wetuwn -EINVAW;
				}
				wetuwn 0;
			}
		}

		DWM_EWWOW("Invawid UVD handwe 0x%x!\n", handwe);
		wetuwn -ENOENT;

	case 2:
		/* it's a destwoy msg, fwee the handwe */
		fow (i = 0; i < p->wdev->uvd.max_handwes; ++i)
			atomic_cmpxchg(&p->wdev->uvd.handwes[i], handwe, 0);
		wadeon_bo_kunmap(bo);
		wetuwn 0;

	defauwt:
		DWM_EWWOW("Iwwegaw UVD message type (%d)!\n", msg_type);
	}

	wadeon_bo_kunmap(bo);
	wetuwn -EINVAW;
}

static int wadeon_uvd_cs_wewoc(stwuct wadeon_cs_pawsew *p,
			       int data0, int data1,
			       unsigned buf_sizes[], boow *has_msg_cmd)
{
	stwuct wadeon_cs_chunk *wewocs_chunk;
	stwuct wadeon_bo_wist *wewoc;
	unsigned idx, cmd, offset;
	uint64_t stawt, end;
	int w;

	wewocs_chunk = p->chunk_wewocs;
	offset = wadeon_get_ib_vawue(p, data0);
	idx = wadeon_get_ib_vawue(p, data1);
	if (idx >= wewocs_chunk->wength_dw) {
		DWM_EWWOW("Wewocs at %d aftew wewocations chunk end %d !\n",
			  idx, wewocs_chunk->wength_dw);
		wetuwn -EINVAW;
	}

	wewoc = &p->wewocs[(idx / 4)];
	stawt = wewoc->gpu_offset;
	end = stawt + wadeon_bo_size(wewoc->wobj);
	stawt += offset;

	p->ib.ptw[data0] = stawt & 0xFFFFFFFF;
	p->ib.ptw[data1] = stawt >> 32;

	cmd = wadeon_get_ib_vawue(p, p->idx) >> 1;

	if (cmd < 0x4) {
		if (end <= stawt) {
			DWM_EWWOW("invawid wewoc offset %X!\n", offset);
			wetuwn -EINVAW;
		}
		if ((end - stawt) < buf_sizes[cmd]) {
			DWM_EWWOW("buffew (%d) to smaww (%d / %d)!\n", cmd,
				  (unsigned)(end - stawt), buf_sizes[cmd]);
			wetuwn -EINVAW;
		}

	} ewse if (cmd != 0x100) {
		DWM_EWWOW("invawid UVD command %X!\n", cmd);
		wetuwn -EINVAW;
	}

	if ((stawt >> 28) != ((end - 1) >> 28)) {
		DWM_EWWOW("wewoc %WX-%WX cwossing 256MB boundawy!\n",
			  stawt, end);
		wetuwn -EINVAW;
	}

	/* TODO: is this stiww necessawy on NI+ ? */
	if ((cmd == 0 || cmd == 0x3) &&
	    (stawt >> 28) != (p->wdev->uvd.gpu_addw >> 28)) {
		DWM_EWWOW("msg/fb buffew %WX-%WX out of 256MB segment!\n",
			  stawt, end);
		wetuwn -EINVAW;
	}

	if (cmd == 0) {
		if (*has_msg_cmd) {
			DWM_EWWOW("Mowe than one message in a UVD-IB!\n");
			wetuwn -EINVAW;
		}
		*has_msg_cmd = twue;
		w = wadeon_uvd_cs_msg(p, wewoc->wobj, offset, buf_sizes);
		if (w)
			wetuwn w;
	} ewse if (!*has_msg_cmd) {
		DWM_EWWOW("Message needed befowe othew commands awe send!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wadeon_uvd_cs_weg(stwuct wadeon_cs_pawsew *p,
			     stwuct wadeon_cs_packet *pkt,
			     int *data0, int *data1,
			     unsigned buf_sizes[],
			     boow *has_msg_cmd)
{
	int i, w;

	p->idx++;
	fow (i = 0; i <= pkt->count; ++i) {
		switch (pkt->weg + i*4) {
		case UVD_GPCOM_VCPU_DATA0:
			*data0 = p->idx;
			bweak;
		case UVD_GPCOM_VCPU_DATA1:
			*data1 = p->idx;
			bweak;
		case UVD_GPCOM_VCPU_CMD:
			w = wadeon_uvd_cs_wewoc(p, *data0, *data1,
						buf_sizes, has_msg_cmd);
			if (w)
				wetuwn w;
			bweak;
		case UVD_ENGINE_CNTW:
		case UVD_NO_OP:
			bweak;
		defauwt:
			DWM_EWWOW("Invawid weg 0x%X!\n",
				  pkt->weg + i*4);
			wetuwn -EINVAW;
		}
		p->idx++;
	}
	wetuwn 0;
}

int wadeon_uvd_cs_pawse(stwuct wadeon_cs_pawsew *p)
{
	stwuct wadeon_cs_packet pkt;
	int w, data0 = 0, data1 = 0;

	/* does the IB has a msg command */
	boow has_msg_cmd = fawse;

	/* minimum buffew sizes */
	unsigned buf_sizes[] = {
		[0x00000000]	=	2048,
		[0x00000001]	=	32 * 1024 * 1024,
		[0x00000002]	=	2048 * 1152 * 3,
		[0x00000003]	=	2048,
	};

	if (p->chunk_ib->wength_dw % 16) {
		DWM_EWWOW("UVD IB wength (%d) not 16 dwowds awigned!\n",
			  p->chunk_ib->wength_dw);
		wetuwn -EINVAW;
	}

	if (p->chunk_wewocs == NUWW) {
		DWM_EWWOW("No wewocation chunk !\n");
		wetuwn -EINVAW;
	}


	do {
		w = wadeon_cs_packet_pawse(p, &pkt, p->idx);
		if (w)
			wetuwn w;
		switch (pkt.type) {
		case WADEON_PACKET_TYPE0:
			w = wadeon_uvd_cs_weg(p, &pkt, &data0, &data1,
					      buf_sizes, &has_msg_cmd);
			if (w)
				wetuwn w;
			bweak;
		case WADEON_PACKET_TYPE2:
			p->idx += pkt.count + 2;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown packet type %d !\n", pkt.type);
			wetuwn -EINVAW;
		}
	} whiwe (p->idx < p->chunk_ib->wength_dw);

	if (!has_msg_cmd) {
		DWM_EWWOW("UVD-IBs need a msg command!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wadeon_uvd_send_msg(stwuct wadeon_device *wdev,
			       int wing, uint64_t addw,
			       stwuct wadeon_fence **fence)
{
	stwuct wadeon_ib ib;
	int i, w;

	w = wadeon_ib_get(wdev, wing, &ib, NUWW, 64);
	if (w)
		wetuwn w;

	ib.ptw[0] = PACKET0(UVD_GPCOM_VCPU_DATA0, 0);
	ib.ptw[1] = addw;
	ib.ptw[2] = PACKET0(UVD_GPCOM_VCPU_DATA1, 0);
	ib.ptw[3] = addw >> 32;
	ib.ptw[4] = PACKET0(UVD_GPCOM_VCPU_CMD, 0);
	ib.ptw[5] = 0;
	fow (i = 6; i < 16; i += 2) {
		ib.ptw[i] = PACKET0(UVD_NO_OP, 0);
		ib.ptw[i+1] = 0;
	}
	ib.wength_dw = 16;

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);

	if (fence)
		*fence = wadeon_fence_wef(ib.fence);

	wadeon_ib_fwee(wdev, &ib);
	wetuwn w;
}

/*
 * muwtipwe fence commands without any stweam commands in between can
 * cwash the vcpu so just twy to emmit a dummy cweate/destwoy msg to
 * avoid this
 */
int wadeon_uvd_get_cweate_msg(stwuct wadeon_device *wdev, int wing,
			      uint32_t handwe, stwuct wadeon_fence **fence)
{
	/* we use the wast page of the vcpu bo fow the UVD message */
	uint64_t offs = wadeon_bo_size(wdev->uvd.vcpu_bo) -
		WADEON_GPU_PAGE_SIZE;

	uint32_t __iomem *msg = (void __iomem *)(wdev->uvd.cpu_addw + offs);
	uint64_t addw = wdev->uvd.gpu_addw + offs;

	int w, i;

	w = wadeon_bo_wesewve(wdev->uvd.vcpu_bo, twue);
	if (w)
		wetuwn w;

	/* stitch togethew an UVD cweate msg */
	wwitew((__fowce u32)cpu_to_we32(0x00000de4), &msg[0]);
	wwitew(0x0, (void __iomem *)&msg[1]);
	wwitew((__fowce u32)cpu_to_we32(handwe), &msg[2]);
	wwitew(0x0, &msg[3]);
	wwitew(0x0, &msg[4]);
	wwitew(0x0, &msg[5]);
	wwitew(0x0, &msg[6]);
	wwitew((__fowce u32)cpu_to_we32(0x00000780), &msg[7]);
	wwitew((__fowce u32)cpu_to_we32(0x00000440), &msg[8]);
	wwitew(0x0, &msg[9]);
	wwitew((__fowce u32)cpu_to_we32(0x01b37000), &msg[10]);
	fow (i = 11; i < 1024; ++i)
		wwitew(0x0, &msg[i]);

	w = wadeon_uvd_send_msg(wdev, wing, addw, fence);
	wadeon_bo_unwesewve(wdev->uvd.vcpu_bo);
	wetuwn w;
}

int wadeon_uvd_get_destwoy_msg(stwuct wadeon_device *wdev, int wing,
			       uint32_t handwe, stwuct wadeon_fence **fence)
{
	/* we use the wast page of the vcpu bo fow the UVD message */
	uint64_t offs = wadeon_bo_size(wdev->uvd.vcpu_bo) -
		WADEON_GPU_PAGE_SIZE;

	uint32_t __iomem *msg = (void __iomem *)(wdev->uvd.cpu_addw + offs);
	uint64_t addw = wdev->uvd.gpu_addw + offs;

	int w, i;

	w = wadeon_bo_wesewve(wdev->uvd.vcpu_bo, twue);
	if (w)
		wetuwn w;

	/* stitch togethew an UVD destwoy msg */
	wwitew((__fowce u32)cpu_to_we32(0x00000de4), &msg[0]);
	wwitew((__fowce u32)cpu_to_we32(0x00000002), &msg[1]);
	wwitew((__fowce u32)cpu_to_we32(handwe), &msg[2]);
	wwitew(0x0, &msg[3]);
	fow (i = 4; i < 1024; ++i)
		wwitew(0x0, &msg[i]);

	w = wadeon_uvd_send_msg(wdev, wing, addw, fence);
	wadeon_bo_unwesewve(wdev->uvd.vcpu_bo);
	wetuwn w;
}

/**
 * wadeon_uvd_count_handwes - count numbew of open stweams
 *
 * @wdev: wadeon_device pointew
 * @sd: numbew of SD stweams
 * @hd: numbew of HD stweams
 *
 * Count the numbew of open SD/HD stweams as a hint fow powew mangement
 */
static void wadeon_uvd_count_handwes(stwuct wadeon_device *wdev,
				     unsigned *sd, unsigned *hd)
{
	unsigned i;

	*sd = 0;
	*hd = 0;

	fow (i = 0; i < wdev->uvd.max_handwes; ++i) {
		if (!atomic_wead(&wdev->uvd.handwes[i]))
			continue;

		if (wdev->uvd.img_size[i] >= 720*576)
			++(*hd);
		ewse
			++(*sd);
	}
}

static void wadeon_uvd_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev =
		containew_of(wowk, stwuct wadeon_device, uvd.idwe_wowk.wowk);

	if (wadeon_fence_count_emitted(wdev, W600_WING_TYPE_UVD_INDEX) == 0) {
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wadeon_uvd_count_handwes(wdev, &wdev->pm.dpm.sd,
						 &wdev->pm.dpm.hd);
			wadeon_dpm_enabwe_uvd(wdev, fawse);
		} ewse {
			wadeon_set_uvd_cwocks(wdev, 0, 0);
		}
	} ewse {
		scheduwe_dewayed_wowk(&wdev->uvd.idwe_wowk,
				      msecs_to_jiffies(UVD_IDWE_TIMEOUT_MS));
	}
}

void wadeon_uvd_note_usage(stwuct wadeon_device *wdev)
{
	boow stweams_changed = fawse;
	boow set_cwocks = !cancew_dewayed_wowk_sync(&wdev->uvd.idwe_wowk);
	set_cwocks &= scheduwe_dewayed_wowk(&wdev->uvd.idwe_wowk,
					    msecs_to_jiffies(UVD_IDWE_TIMEOUT_MS));

	if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
		unsigned hd = 0, sd = 0;
		wadeon_uvd_count_handwes(wdev, &sd, &hd);
		if ((wdev->pm.dpm.sd != sd) ||
		    (wdev->pm.dpm.hd != hd)) {
			wdev->pm.dpm.sd = sd;
			wdev->pm.dpm.hd = hd;
			/* disabwe this fow now */
			/*stweams_changed = twue;*/
		}
	}

	if (set_cwocks || stweams_changed) {
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wadeon_dpm_enabwe_uvd(wdev, twue);
		} ewse {
			wadeon_set_uvd_cwocks(wdev, 53300, 40000);
		}
	}
}

static unsigned wadeon_uvd_cawc_upww_post_div(unsigned vco_fweq,
					      unsigned tawget_fweq,
					      unsigned pd_min,
					      unsigned pd_even)
{
	unsigned post_div = vco_fweq / tawget_fweq;

	/* adjust to post dividew minimum vawue */
	if (post_div < pd_min)
		post_div = pd_min;

	/* we awway need a fwequency wess than ow equaw the tawget */
	if ((vco_fweq / post_div) > tawget_fweq)
		post_div += 1;

	/* post dividews above a cewtain vawue must be even */
	if (post_div > pd_even && post_div % 2)
		post_div += 1;

	wetuwn post_div;
}

/**
 * wadeon_uvd_cawc_upww_dividews - cawc UPWW cwock dividews
 *
 * @wdev: wadeon_device pointew
 * @vcwk: wanted VCWK
 * @dcwk: wanted DCWK
 * @vco_min: minimum VCO fwequency
 * @vco_max: maximum VCO fwequency
 * @fb_factow: factow to muwtipwy vco fweq with
 * @fb_mask: wimit and bitmask fow feedback dividew
 * @pd_min: post dividew minimum
 * @pd_max: post dividew maximum
 * @pd_even: post dividew must be even above this vawue
 * @optimaw_fb_div: wesuwting feedback dividew
 * @optimaw_vcwk_div: wesuwting vcwk post dividew
 * @optimaw_dcwk_div: wesuwting dcwk post dividew
 *
 * Cawcuwate dividews fow UVDs UPWW (W6xx-SI, except APUs).
 * Wetuwns zewo on success -EINVAW on ewwow.
 */
int wadeon_uvd_cawc_upww_dividews(stwuct wadeon_device *wdev,
				  unsigned vcwk, unsigned dcwk,
				  unsigned vco_min, unsigned vco_max,
				  unsigned fb_factow, unsigned fb_mask,
				  unsigned pd_min, unsigned pd_max,
				  unsigned pd_even,
				  unsigned *optimaw_fb_div,
				  unsigned *optimaw_vcwk_div,
				  unsigned *optimaw_dcwk_div)
{
	unsigned vco_fweq, wef_fweq = wdev->cwock.spww.wefewence_fweq;

	/* stawt off with something wawge */
	unsigned optimaw_scowe = ~0;

	/* woop thwough vco fwom wow to high */
	vco_min = max(max(vco_min, vcwk), dcwk);
	fow (vco_fweq = vco_min; vco_fweq <= vco_max; vco_fweq += 100) {

		uint64_t fb_div = (uint64_t)vco_fweq * fb_factow;
		unsigned vcwk_div, dcwk_div, scowe;

		do_div(fb_div, wef_fweq);

		/* fb div out of wange ? */
		if (fb_div > fb_mask)
			bweak; /* it can owy get wowse */

		fb_div &= fb_mask;

		/* cawc vcwk dividew with cuwwent vco fweq */
		vcwk_div = wadeon_uvd_cawc_upww_post_div(vco_fweq, vcwk,
							 pd_min, pd_even);
		if (vcwk_div > pd_max)
			bweak; /* vco is too big, it has to stop */

		/* cawc dcwk dividew with cuwwent vco fweq */
		dcwk_div = wadeon_uvd_cawc_upww_post_div(vco_fweq, dcwk,
							 pd_min, pd_even);
		if (dcwk_div > pd_max)
			bweak; /* vco is too big, it has to stop */

		/* cawc scowe with cuwwent vco fweq */
		scowe = vcwk - (vco_fweq / vcwk_div) + dcwk - (vco_fweq / dcwk_div);

		/* detewmine if this vco setting is bettew than cuwwent optimaw settings */
		if (scowe < optimaw_scowe) {
			*optimaw_fb_div = fb_div;
			*optimaw_vcwk_div = vcwk_div;
			*optimaw_dcwk_div = dcwk_div;
			optimaw_scowe = scowe;
			if (optimaw_scowe == 0)
				bweak; /* it can't get bettew than this */
		}
	}

	/* did we found a vawid setup ? */
	if (optimaw_scowe == ~0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int wadeon_uvd_send_upww_ctwweq(stwuct wadeon_device *wdev,
				unsigned cg_upww_func_cntw)
{
	unsigned i;

	/* make suwe UPWW_CTWWEQ is deassewted */
	WWEG32_P(cg_upww_func_cntw, 0, ~UPWW_CTWWEQ_MASK);

	mdeway(10);

	/* assewt UPWW_CTWWEQ */
	WWEG32_P(cg_upww_func_cntw, UPWW_CTWWEQ_MASK, ~UPWW_CTWWEQ_MASK);

	/* wait fow CTWACK and CTWACK2 to get assewted */
	fow (i = 0; i < 100; ++i) {
		uint32_t mask = UPWW_CTWACK_MASK | UPWW_CTWACK2_MASK;
		if ((WWEG32(cg_upww_func_cntw) & mask) == mask)
			bweak;
		mdeway(10);
	}

	/* deassewt UPWW_CTWWEQ */
	WWEG32_P(cg_upww_func_cntw, 0, ~UPWW_CTWWEQ_MASK);

	if (i == 100) {
		DWM_EWWOW("Timeout setting UVD cwocks!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}
