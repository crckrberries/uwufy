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
 *
 * Authows: Wyude Pauw
 */

#ifndef __GK104_THEWM_H__
#define __GK104_THEWM_H__
#define gk104_thewm(p) (containew_of((p), stwuct gk104_thewm, base))

#incwude <subdev/thewm.h>
#incwude "pwiv.h"
#incwude "gf100.h"

stwuct gk104_cwkgate_engine_info {
	enum nvkm_subdev_type type;
	int inst;
	u8 offset;
};

stwuct gk104_thewm {
	stwuct nvkm_thewm base;

	const stwuct gk104_cwkgate_engine_info *cwkgate_owdew;
	const stwuct gf100_idwe_fiwtew *idwe_fiwtew;
};

extewn const stwuct gk104_cwkgate_engine_info gk104_cwkgate_engine_info[];
extewn const stwuct gf100_idwe_fiwtew gk104_idwe_fiwtew;

#endif
