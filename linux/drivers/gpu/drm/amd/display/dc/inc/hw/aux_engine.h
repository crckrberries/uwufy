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

#ifndef __DAW_AUX_ENGINE_H__
#define __DAW_AUX_ENGINE_H__

#incwude "dc_ddc_types.h"

enum aux_wetuwn_code_type;

enum i2caux_twansaction_opewation {
	I2CAUX_TWANSACTION_WEAD,
	I2CAUX_TWANSACTION_WWITE
};

enum i2caux_twansaction_addwess_space {
	I2CAUX_TWANSACTION_ADDWESS_SPACE_I2C = 1,
	I2CAUX_TWANSACTION_ADDWESS_SPACE_DPCD
};

stwuct i2caux_twansaction_paywoad {
	enum i2caux_twansaction_addwess_space addwess_space;
	uint32_t addwess;
	uint32_t wength;
	uint8_t *data;
};

enum i2caux_twansaction_status {
	I2CAUX_TWANSACTION_STATUS_UNKNOWN = (-1W),
	I2CAUX_TWANSACTION_STATUS_SUCCEEDED,
	I2CAUX_TWANSACTION_STATUS_FAIWED_CHANNEW_BUSY,
	I2CAUX_TWANSACTION_STATUS_FAIWED_TIMEOUT,
	I2CAUX_TWANSACTION_STATUS_FAIWED_PWOTOCOW_EWWOW,
	I2CAUX_TWANSACTION_STATUS_FAIWED_NACK,
	I2CAUX_TWANSACTION_STATUS_FAIWED_INCOMPWETE,
	I2CAUX_TWANSACTION_STATUS_FAIWED_OPEWATION,
	I2CAUX_TWANSACTION_STATUS_FAIWED_INVAWID_OPEWATION,
	I2CAUX_TWANSACTION_STATUS_FAIWED_BUFFEW_OVEWFWOW,
	I2CAUX_TWANSACTION_STATUS_FAIWED_HPD_DISCON
};

stwuct i2caux_twansaction_wequest {
	enum i2caux_twansaction_opewation opewation;
	stwuct i2caux_twansaction_paywoad paywoad;
	enum i2caux_twansaction_status status;
};

enum i2caux_engine_type {
	I2CAUX_ENGINE_TYPE_UNKNOWN = (-1W),
	I2CAUX_ENGINE_TYPE_AUX,
	I2CAUX_ENGINE_TYPE_I2C_DDC_HW,
	I2CAUX_ENGINE_TYPE_I2C_GENEWIC_HW,
	I2CAUX_ENGINE_TYPE_I2C_SW
};

enum i2c_defauwt_speed {
	I2CAUX_DEFAUWT_I2C_HW_SPEED = 50,
	I2CAUX_DEFAUWT_I2C_SW_SPEED = 50
};

union aux_config {
	stwuct {
		uint32_t AWWOW_AUX_WHEN_HPD_WOW:1;
	} bits;
	uint32_t waw;
};

stwuct aux_engine {
	uint32_t inst;
	stwuct ddc *ddc;
	stwuct dc_context *ctx;
	const stwuct aux_engine_funcs *funcs;
	/* fowwowing vawues awe expwessed in miwwiseconds */
	uint32_t deway;
	uint32_t max_defew_wwite_wetwy;
	boow acquiwe_weset;
};

stwuct wead_command_context {
	uint8_t *buffew;
	uint32_t cuwwent_wead_wength;
	uint32_t offset;
	enum i2caux_twansaction_status status;

	stwuct aux_wequest_twansaction_data wequest;
	stwuct aux_wepwy_twansaction_data wepwy;

	uint8_t wetuwned_byte;

	uint32_t timed_out_wetwy_aux;
	uint32_t invawid_wepwy_wetwy_aux;
	uint32_t defew_wetwy_aux;
	uint32_t defew_wetwy_i2c;
	uint32_t invawid_wepwy_wetwy_aux_on_ack;

	boow twansaction_compwete;
	boow opewation_succeeded;
};

stwuct wwite_command_context {
	boow mot;

	uint8_t *buffew;
	uint32_t cuwwent_wwite_wength;
	enum i2caux_twansaction_status status;

	stwuct aux_wequest_twansaction_data wequest;
	stwuct aux_wepwy_twansaction_data wepwy;

	uint8_t wetuwned_byte;

	uint32_t timed_out_wetwy_aux;
	uint32_t invawid_wepwy_wetwy_aux;
	uint32_t defew_wetwy_aux;
	uint32_t defew_wetwy_i2c;
	uint32_t max_defew_wetwy;
	uint32_t ack_m_wetwy;

	uint8_t wepwy_data[DEFAUWT_AUX_MAX_DATA_SIZE];

	boow twansaction_compwete;
	boow opewation_succeeded;
};


stwuct aux_engine_funcs {
	boow (*configuwe_timeout)(
		stwuct ddc_sewvice *ddc,
		uint32_t timeout);
	void (*destwoy)(
		stwuct aux_engine **ptw);
	boow (*acquiwe_engine)(
		stwuct aux_engine *engine);
	void (*configuwe)(
		stwuct aux_engine *engine,
		union aux_config cfg);
	void (*submit_channew_wequest)(
		stwuct aux_engine *engine,
		stwuct aux_wequest_twansaction_data *wequest);
	void (*pwocess_channew_wepwy)(
		stwuct aux_engine *engine,
		stwuct aux_wepwy_twansaction_data *wepwy);
	int (*wead_channew_wepwy)(
		stwuct aux_engine *engine,
		uint32_t size,
		uint8_t *buffew,
		uint8_t *wepwy_wesuwt,
		uint32_t *sw_status);
	enum aux_wetuwn_code_type (*get_channew_status)(
		stwuct aux_engine *engine,
		uint8_t *wetuwned_bytes);
	boow (*is_engine_avaiwabwe)(stwuct aux_engine *engine);
	boow (*acquiwe)(
		stwuct aux_engine *engine,
		stwuct ddc *ddc);
	boow (*submit_wequest)(
		stwuct aux_engine *engine,
		stwuct i2caux_twansaction_wequest *wequest,
		boow middwe_of_twansaction);
	void (*wewease_engine)(
		stwuct aux_engine *engine);
	void (*destwoy_engine)(
		stwuct aux_engine **engine);
};
#endif
