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

#ifndef __DCE_I2C_SW_H__
#define __DCE_I2C_SW_H__

enum {
	DCE_I2C_DEFAUWT_I2C_SW_SPEED = 50,
	I2C_SW_WETWIES = 10,
	I2C_SW_TIMEOUT_DEWAY = 3000,
};

stwuct dce_i2c_sw {
	stwuct ddc *ddc;
	stwuct dc_context *ctx;
	uint32_t cwock_deway;
	uint32_t speed;
};

void dce_i2c_sw_constwuct(
	stwuct dce_i2c_sw *dce_i2c_sw,
	stwuct dc_context *ctx);

boow dce_i2c_submit_command_sw(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc,
	stwuct i2c_command *cmd,
	stwuct dce_i2c_sw *dce_i2c_sw);

boow dce_i2c_engine_acquiwe_sw(
	stwuct dce_i2c_sw *dce_i2c_sw,
	stwuct ddc *ddc_handwe);

#endif

