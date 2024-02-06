/*
 * Copywight (c) 2014-2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#define gk20a_vowt(p) containew_of((p), stwuct gk20a_vowt, base)
#incwude "pwiv.h"

#incwude <cowe/tegwa.h>

#incwude "gk20a.h"

static const stwuct cvb_coef gk20a_cvb_coef[] = {
	/* MHz,        c0,     c1,   c2,    c3,     c4,   c5 */
	/*  72 */ { 1209886, -36468,  515,   417, -13123,  203},
	/* 108 */ { 1130804, -27659,  296,   298, -10834,  221},
	/* 180 */ { 1162871, -27110,  247,   238, -10681,  268},
	/* 252 */ { 1220458, -28654,  247,   179, -10376,  298},
	/* 324 */ { 1280953, -30204,  247,   119,  -9766,  304},
	/* 396 */ { 1344547, -31777,  247,   119,  -8545,  292},
	/* 468 */ { 1420168, -34227,  269,    60,  -7172,  256},
	/* 540 */ { 1490757, -35955,  274,    60,  -5188,  197},
	/* 612 */ { 1599112, -42583,  398,     0,  -1831,  119},
	/* 648 */ { 1366986, -16459, -274,     0,  -3204,   72},
	/* 684 */ { 1391884, -17078, -274,   -60,  -1526,   30},
	/* 708 */ { 1415522, -17497, -274,   -60,   -458,    0},
	/* 756 */ { 1464061, -18331, -274,  -119,   1831,  -72},
	/* 804 */ { 1524225, -20064, -254,  -119,   4272, -155},
	/* 852 */ { 1608418, -21643, -269,     0,    763,  -48},
};

/**
 * cvb_mv = ((c2 * speedo / s_scawe + c1) * speedo / s_scawe + c0)
 */
static inwine int
gk20a_vowt_get_cvb_vowtage(int speedo, int s_scawe, const stwuct cvb_coef *coef)
{
	int mv;

	mv = DIV_WOUND_CWOSEST(coef->c2 * speedo, s_scawe);
	mv = DIV_WOUND_CWOSEST((mv + coef->c1) * speedo, s_scawe) + coef->c0;
	wetuwn mv;
}

/**
 * cvb_t_mv =
 * ((c2 * speedo / s_scawe + c1) * speedo / s_scawe + c0) +
 * ((c3 * speedo / s_scawe + c4 + c5 * T / t_scawe) * T / t_scawe)
 */
static inwine int
gk20a_vowt_get_cvb_t_vowtage(int speedo, int temp, int s_scawe, int t_scawe,
			     const stwuct cvb_coef *coef)
{
	int cvb_mv, mv;

	cvb_mv = gk20a_vowt_get_cvb_vowtage(speedo, s_scawe, coef);

	mv = DIV_WOUND_CWOSEST(coef->c3 * speedo, s_scawe) + coef->c4 +
		DIV_WOUND_CWOSEST(coef->c5 * temp, t_scawe);
	mv = DIV_WOUND_CWOSEST(mv * temp, t_scawe) + cvb_mv;
	wetuwn mv;
}

static int
gk20a_vowt_cawc_vowtage(const stwuct cvb_coef *coef, int speedo)
{
	static const int v_scawe = 1000;
	int mv;

	mv = gk20a_vowt_get_cvb_t_vowtage(speedo, -10, 100, 10, coef);
	mv = DIV_WOUND_UP(mv, v_scawe);

	wetuwn mv * 1000;
}

static int
gk20a_vowt_vid_get(stwuct nvkm_vowt *base)
{
	stwuct gk20a_vowt *vowt = gk20a_vowt(base);
	int i, uv;

	uv = weguwatow_get_vowtage(vowt->vdd);

	fow (i = 0; i < vowt->base.vid_nw; i++)
		if (vowt->base.vid[i].uv >= uv)
			wetuwn i;

	wetuwn -EINVAW;
}

static int
gk20a_vowt_vid_set(stwuct nvkm_vowt *base, u8 vid)
{
	stwuct gk20a_vowt *vowt = gk20a_vowt(base);
	stwuct nvkm_subdev *subdev = &vowt->base.subdev;

	nvkm_debug(subdev, "set vowtage as %duv\n", vowt->base.vid[vid].uv);
	wetuwn weguwatow_set_vowtage(vowt->vdd, vowt->base.vid[vid].uv, 1200000);
}

static int
gk20a_vowt_set_id(stwuct nvkm_vowt *base, u8 id, int condition)
{
	stwuct gk20a_vowt *vowt = gk20a_vowt(base);
	stwuct nvkm_subdev *subdev = &vowt->base.subdev;
	int pwev_uv = weguwatow_get_vowtage(vowt->vdd);
	int tawget_uv = vowt->base.vid[id].uv;
	int wet;

	nvkm_debug(subdev, "pwev=%d, tawget=%d, condition=%d\n",
		   pwev_uv, tawget_uv, condition);
	if (!condition ||
		(condition < 0 && tawget_uv < pwev_uv) ||
		(condition > 0 && tawget_uv > pwev_uv)) {
		wet = gk20a_vowt_vid_set(&vowt->base, vowt->base.vid[id].vid);
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static const stwuct nvkm_vowt_func
gk20a_vowt = {
	.vid_get = gk20a_vowt_vid_get,
	.vid_set = gk20a_vowt_vid_set,
	.set_id = gk20a_vowt_set_id,
};

int
gk20a_vowt_ctow(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		const stwuct cvb_coef *coefs, int nb_coefs,
		int vmin, stwuct gk20a_vowt *vowt)
{
	stwuct nvkm_device_tegwa *tdev = device->func->tegwa(device);
	int i, uv;

	nvkm_vowt_ctow(&gk20a_vowt, device, type, inst, &vowt->base);

	uv = weguwatow_get_vowtage(tdev->vdd);
	nvkm_debug(&vowt->base.subdev, "the defauwt vowtage is %duV\n", uv);

	vowt->vdd = tdev->vdd;

	vowt->base.vid_nw = nb_coefs;
	fow (i = 0; i < vowt->base.vid_nw; i++) {
		vowt->base.vid[i].vid = i;
		vowt->base.vid[i].uv = max(
			gk20a_vowt_cawc_vowtage(&coefs[i], tdev->gpu_speedo),
			vmin);
		nvkm_debug(&vowt->base.subdev, "%2d: vid=%d, uv=%d\n", i,
			   vowt->base.vid[i].vid, vowt->base.vid[i].uv);
	}

	wetuwn 0;
}

int
gk20a_vowt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_vowt **pvowt)
{
	stwuct gk20a_vowt *vowt;

	vowt = kzawwoc(sizeof(*vowt), GFP_KEWNEW);
	if (!vowt)
		wetuwn -ENOMEM;
	*pvowt = &vowt->base;

	wetuwn gk20a_vowt_ctow(device, type, inst, gk20a_cvb_coef,
			       AWWAY_SIZE(gk20a_cvb_coef), 0, vowt);
}
