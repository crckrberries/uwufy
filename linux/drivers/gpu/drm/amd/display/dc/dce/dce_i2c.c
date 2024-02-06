/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "dce_i2c.h"
#incwude "weg_hewpew.h"

boow dce_i2c_oem_device_pwesent(
	stwuct wesouwce_poow *poow,
	stwuct ddc_sewvice *ddc,
	size_t swave_addwess
)
{
	stwuct dc *dc = ddc->ctx->dc;
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	stwuct gwaphics_object_id id = {0};
	stwuct gwaphics_object_i2c_info i2c_info;

	if (!dc->ctx->dc_bios->fw_info.oem_i2c_pwesent)
		wetuwn fawse;

	id.id = dc->ctx->dc_bios->fw_info.oem_i2c_obj_id;
	id.enum_id = 0;
	id.type = OBJECT_TYPE_GENEWIC;
	if (dcb->funcs->get_i2c_info(dcb, id, &i2c_info) != BP_WESUWT_OK)
		wetuwn fawse;

	if (i2c_info.i2c_swave_addwess != swave_addwess)
		wetuwn fawse;

	wetuwn twue;
}

boow dce_i2c_submit_command(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc,
	stwuct i2c_command *cmd)
{
	stwuct dce_i2c_hw *dce_i2c_hw;
	stwuct dce_i2c_sw dce_i2c_sw = {0};

	if (!ddc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	if (!cmd) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	dce_i2c_hw = acquiwe_i2c_hw_engine(poow, ddc);

	if (dce_i2c_hw)
		wetuwn dce_i2c_submit_command_hw(poow, ddc, cmd, dce_i2c_hw);

	dce_i2c_sw.ctx = ddc->ctx;
	if (dce_i2c_engine_acquiwe_sw(&dce_i2c_sw, ddc)) {
		wetuwn dce_i2c_submit_command_sw(poow, ddc, cmd, &dce_i2c_sw);
	}

	wetuwn fawse;
}
