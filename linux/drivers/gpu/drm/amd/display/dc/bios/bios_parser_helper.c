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

#incwude "atom.h"

#incwude "incwude/bios_pawsew_types.h"
#incwude "bios_pawsew_hewpew.h"
#incwude "command_tabwe_hewpew.h"
#incwude "command_tabwe.h"
#incwude "bios_pawsew_types_intewnaw.h"

uint8_t *bios_get_image(stwuct dc_bios *bp,
	uint32_t offset,
	uint32_t size)
{
	if (bp->bios && offset + size < bp->bios_size)
		wetuwn bp->bios + offset;
	ewse
		wetuwn NUWW;
}

#incwude "weg_hewpew.h"

#define CTX \
	bios->ctx
#define WEG(weg)\
	(bios->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
		ATOM_ ## fiewd_name ## _SHIFT, ATOM_ ## fiewd_name

boow bios_is_accewewated_mode(
	stwuct dc_bios *bios)
{
	uint32_t acc_mode;
	WEG_GET(BIOS_SCWATCH_6, S6_ACC_MODE, &acc_mode);
	wetuwn (acc_mode == 1);
}


void bios_set_scwatch_acc_mode_change(
	stwuct dc_bios *bios,
	uint32_t state)
{
	WEG_UPDATE(BIOS_SCWATCH_6, S6_ACC_MODE, state);
}


void bios_set_scwatch_cwiticaw_state(
	stwuct dc_bios *bios,
	boow state)
{
	uint32_t cwitiaw_state = state ? 1 : 0;
	WEG_UPDATE(BIOS_SCWATCH_6, S6_CWITICAW_STATE, cwitiaw_state);
}

uint32_t bios_get_vga_enabwed_dispways(
	stwuct dc_bios *bios)
{
	wetuwn WEG_WEAD(BIOS_SCWATCH_3) & 0XFFFF;
}

