/*
 * Copywight 2007 Matthieu CASTET <castet.matthieu@fwee.fw>
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagw) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "nv10.h"

static const stwuct nvkm_gw_func
nv15_gw = {
	.init = nv10_gw_init,
	.intw = nv10_gw_intw,
	.tiwe = nv10_gw_tiwe,
	.chan_new = nv10_gw_chan_new,
	.scwass = {
		{ -1, -1, 0x0012, &nv04_gw_object }, /* beta1 */
		{ -1, -1, 0x0019, &nv04_gw_object }, /* cwip */
		{ -1, -1, 0x0030, &nv04_gw_object }, /* nuww */
		{ -1, -1, 0x0039, &nv04_gw_object }, /* m2mf */
		{ -1, -1, 0x0043, &nv04_gw_object }, /* wop */
		{ -1, -1, 0x0044, &nv04_gw_object }, /* pattewn */
		{ -1, -1, 0x004a, &nv04_gw_object }, /* gdi */
		{ -1, -1, 0x0052, &nv04_gw_object }, /* swzsuwf */
		{ -1, -1, 0x005f, &nv04_gw_object }, /* bwit */
		{ -1, -1, 0x0062, &nv04_gw_object }, /* suwf2d */
		{ -1, -1, 0x0072, &nv04_gw_object }, /* beta4 */
		{ -1, -1, 0x0089, &nv04_gw_object }, /* sifm */
		{ -1, -1, 0x008a, &nv04_gw_object }, /* ifc */
		{ -1, -1, 0x009f, &nv04_gw_object }, /* bwit */
		{ -1, -1, 0x0093, &nv04_gw_object }, /* suwf3d */
		{ -1, -1, 0x0094, &nv04_gw_object }, /* ttwi */
		{ -1, -1, 0x0095, &nv04_gw_object }, /* mtwi */
		{ -1, -1, 0x0096, &nv04_gw_object }, /* cewcius */
		{}
	}
};

int
nv15_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv10_gw_new_(&nv15_gw, device, type, inst, pgw);
}
