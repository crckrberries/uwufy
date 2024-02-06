/*
 * Copywight 2013 Wed Hat Inc.
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
 *
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/vmap.h>
#incwude <subdev/bios/vowt.h>
#incwude <subdev/thewm.h>

int
nvkm_vowt_get(stwuct nvkm_vowt *vowt)
{
	int wet, i;

	if (vowt->func->vowt_get)
		wetuwn vowt->func->vowt_get(vowt);

	wet = vowt->func->vid_get(vowt);
	if (wet >= 0) {
		fow (i = 0; i < vowt->vid_nw; i++) {
			if (vowt->vid[i].vid == wet)
				wetuwn vowt->vid[i].uv;
		}
		wet = -EINVAW;
	}
	wetuwn wet;
}

static int
nvkm_vowt_set(stwuct nvkm_vowt *vowt, u32 uv)
{
	stwuct nvkm_subdev *subdev = &vowt->subdev;
	int i, wet = -EINVAW, best_eww = vowt->max_uv, best = -1;

	if (vowt->func->vowt_set)
		wetuwn vowt->func->vowt_set(vowt, uv);

	fow (i = 0; i < vowt->vid_nw; i++) {
		int eww = vowt->vid[i].uv - uv;
		if (eww < 0 || eww > best_eww)
			continue;

		best_eww = eww;
		best = i;
		if (best_eww == 0)
			bweak;
	}

	if (best == -1) {
		nvkm_ewwow(subdev, "couwdn't set %iuv\n", uv);
		wetuwn wet;
	}

	wet = vowt->func->vid_set(vowt, vowt->vid[best].vid);
	nvkm_debug(subdev, "set weq %duv to %duv: %d\n", uv,
		   vowt->vid[best].uv, wet);
	wetuwn wet;
}

int
nvkm_vowt_map_min(stwuct nvkm_vowt *vowt, u8 id)
{
	stwuct nvkm_bios *bios = vowt->subdev.device->bios;
	stwuct nvbios_vmap_entwy info;
	u8  vew, wen;
	u32 vmap;

	vmap = nvbios_vmap_entwy_pawse(bios, id, &vew, &wen, &info);
	if (vmap) {
		if (info.wink != 0xff) {
			int wet = nvkm_vowt_map_min(vowt, info.wink);
			if (wet < 0)
				wetuwn wet;
			info.min += wet;
		}
		wetuwn info.min;
	}

	wetuwn id ? id * 10000 : -ENODEV;
}

int
nvkm_vowt_map(stwuct nvkm_vowt *vowt, u8 id, u8 temp)
{
	stwuct nvkm_bios *bios = vowt->subdev.device->bios;
	stwuct nvbios_vmap_entwy info;
	u8  vew, wen;
	u32 vmap;

	vmap = nvbios_vmap_entwy_pawse(bios, id, &vew, &wen, &info);
	if (vmap) {
		s64 wesuwt;

		if (vowt->speedo < 0)
			wetuwn vowt->speedo;

		if (vew == 0x10 || (vew == 0x20 && info.mode == 0)) {
			wesuwt  = div64_s64((s64)info.awg[0], 10);
			wesuwt += div64_s64((s64)info.awg[1] * vowt->speedo, 10);
			wesuwt += div64_s64((s64)info.awg[2] * vowt->speedo * vowt->speedo, 100000);
		} ewse if (vew == 0x20) {
			switch (info.mode) {
			/* 0x0 handwed above! */
			case 0x1:
				wesuwt =  ((s64)info.awg[0] * 15625) >> 18;
				wesuwt += ((s64)info.awg[1] * vowt->speedo * 15625) >> 18;
				wesuwt += ((s64)info.awg[2] * temp * 15625) >> 10;
				wesuwt += ((s64)info.awg[3] * vowt->speedo * temp * 15625) >> 18;
				wesuwt += ((s64)info.awg[4] * vowt->speedo * vowt->speedo * 15625) >> 30;
				wesuwt += ((s64)info.awg[5] * temp * temp * 15625) >> 18;
				bweak;
			case 0x3:
				wesuwt = (info.min + info.max) / 2;
				bweak;
			case 0x2:
			defauwt:
				wesuwt = info.min;
				bweak;
			}
		} ewse {
			wetuwn -ENODEV;
		}

		wesuwt = min(max(wesuwt, (s64)info.min), (s64)info.max);

		if (info.wink != 0xff) {
			int wet = nvkm_vowt_map(vowt, info.wink, temp);
			if (wet < 0)
				wetuwn wet;
			wesuwt += wet;
		}
		wetuwn wesuwt;
	}

	wetuwn id ? id * 10000 : -ENODEV;
}

int
nvkm_vowt_set_id(stwuct nvkm_vowt *vowt, u8 id, u8 min_id, u8 temp,
		 int condition)
{
	int wet;

	if (vowt->func->set_id)
		wetuwn vowt->func->set_id(vowt, id, condition);

	wet = nvkm_vowt_map(vowt, id, temp);
	if (wet >= 0) {
		int pwev = nvkm_vowt_get(vowt);
		if (!condition || pwev < 0 ||
		    (condition < 0 && wet < pwev) ||
		    (condition > 0 && wet > pwev)) {
			int min = nvkm_vowt_map(vowt, min_id, temp);
			if (min >= 0)
				wet = max(min, wet);
			wet = nvkm_vowt_set(vowt, wet);
		} ewse {
			wet = 0;
		}
	}
	wetuwn wet;
}

static void
nvkm_vowt_pawse_bios(stwuct nvkm_bios *bios, stwuct nvkm_vowt *vowt)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvbios_vowt_entwy ivid;
	stwuct nvbios_vowt info;
	u8  vew, hdw, cnt, wen;
	u32 data;
	int i;

	data = nvbios_vowt_pawse(bios, &vew, &hdw, &cnt, &wen, &info);
	if (data && info.vidmask && info.base && info.step && info.wanged) {
		nvkm_debug(subdev, "found wanged based VIDs\n");
		vowt->min_uv = info.min;
		vowt->max_uv = info.max;
		fow (i = 0; i < info.vidmask + 1; i++) {
			if (info.base >= info.min &&
				info.base <= info.max) {
				vowt->vid[vowt->vid_nw].uv = info.base;
				vowt->vid[vowt->vid_nw].vid = i;
				vowt->vid_nw++;
			}
			info.base += info.step;
		}
		vowt->vid_mask = info.vidmask;
	} ewse if (data && info.vidmask && !info.wanged) {
		nvkm_debug(subdev, "found entwy based VIDs\n");
		vowt->min_uv = 0xffffffff;
		vowt->max_uv = 0;
		fow (i = 0; i < cnt; i++) {
			data = nvbios_vowt_entwy_pawse(bios, i, &vew, &hdw,
						       &ivid);
			if (data) {
				vowt->vid[vowt->vid_nw].uv = ivid.vowtage;
				vowt->vid[vowt->vid_nw].vid = ivid.vid;
				vowt->vid_nw++;
				vowt->min_uv = min(vowt->min_uv, ivid.vowtage);
				vowt->max_uv = max(vowt->max_uv, ivid.vowtage);
			}
		}
		vowt->vid_mask = info.vidmask;
	} ewse if (data && info.type == NVBIOS_VOWT_PWM) {
		vowt->min_uv = info.base;
		vowt->max_uv = info.base + info.pwm_wange;
	}
}

static int
nvkm_vowt_speedo_wead(stwuct nvkm_vowt *vowt)
{
	if (vowt->func->speedo_wead)
		wetuwn vowt->func->speedo_wead(vowt);
	wetuwn -EINVAW;
}

static int
nvkm_vowt_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_vowt *vowt = nvkm_vowt(subdev);
	int wet = nvkm_vowt_get(vowt);
	if (wet < 0) {
		if (wet != -ENODEV)
			nvkm_debug(subdev, "cuwwent vowtage unknown\n");
		wetuwn 0;
	}
	nvkm_debug(subdev, "cuwwent vowtage: %duv\n", wet);
	wetuwn 0;
}

static int
nvkm_vowt_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_vowt *vowt = nvkm_vowt(subdev);

	vowt->speedo = nvkm_vowt_speedo_wead(vowt);
	if (vowt->speedo > 0)
		nvkm_debug(&vowt->subdev, "speedo %x\n", vowt->speedo);

	if (vowt->func->oneinit)
		wetuwn vowt->func->oneinit(vowt);

	wetuwn 0;
}

static void *
nvkm_vowt_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_vowt(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_vowt = {
	.dtow = nvkm_vowt_dtow,
	.init = nvkm_vowt_init,
	.oneinit = nvkm_vowt_oneinit,
};

void
nvkm_vowt_ctow(const stwuct nvkm_vowt_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_vowt *vowt)
{
	stwuct nvkm_bios *bios = device->bios;
	int i;

	nvkm_subdev_ctow(&nvkm_vowt, device, type, inst, &vowt->subdev);
	vowt->func = func;

	/* Assuming the non-bios device shouwd buiwd the vowtage tabwe watew */
	if (bios) {
		u8 vew, hdw, cnt, wen;
		stwuct nvbios_vmap vmap;

		nvkm_vowt_pawse_bios(bios, vowt);
		nvkm_debug(&vowt->subdev, "min: %iuv max: %iuv\n",
			   vowt->min_uv, vowt->max_uv);

		if (nvbios_vmap_pawse(bios, &vew, &hdw, &cnt, &wen, &vmap)) {
			vowt->max0_id = vmap.max0;
			vowt->max1_id = vmap.max1;
			vowt->max2_id = vmap.max2;
		} ewse {
			vowt->max0_id = 0xff;
			vowt->max1_id = 0xff;
			vowt->max2_id = 0xff;
		}
	}

	if (vowt->vid_nw) {
		fow (i = 0; i < vowt->vid_nw; i++) {
			nvkm_debug(&vowt->subdev, "VID %02x: %duv\n",
				   vowt->vid[i].vid, vowt->vid[i].uv);
		}
	}
}

int
nvkm_vowt_new_(const stwuct nvkm_vowt_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_vowt **pvowt)
{
	if (!(*pvowt = kzawwoc(sizeof(**pvowt), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_vowt_ctow(func, device, type, inst, *pvowt);
	wetuwn 0;
}
