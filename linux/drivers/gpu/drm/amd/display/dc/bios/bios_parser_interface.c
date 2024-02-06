/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"
#incwude "incwude/woggew_intewface.h"

#incwude "bios_pawsew_intewface.h"
#incwude "bios_pawsew.h"

#incwude "bios_pawsew2.h"


stwuct dc_bios *daw_bios_pawsew_cweate(
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion)
{
	stwuct dc_bios *bios = NUWW;

	bios = fiwmwawe_pawsew_cweate(init, dce_vewsion);

	/* Faww back to owd bios pawsew fow owdew asics */
	if (bios == NUWW)
		bios = bios_pawsew_cweate(init, dce_vewsion);

	wetuwn bios;
}

void daw_bios_pawsew_destwoy(stwuct dc_bios **dcb)
{
	stwuct dc_bios *bios = *dcb;

	bios->funcs->bios_pawsew_destwoy(dcb);
}

