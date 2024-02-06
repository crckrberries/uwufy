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
#incwude "dce_i2c_sw.h"
#incwude "incwude/gpio_sewvice_intewface.h"
#define SCW fawse
#define SDA twue

void dce_i2c_sw_constwuct(
	stwuct dce_i2c_sw *dce_i2c_sw,
	stwuct dc_context *ctx)
{
	dce_i2c_sw->ctx = ctx;
}

static inwine boow wead_bit_fwom_ddc(
	stwuct ddc *ddc,
	boow data_now_cwock)
{
	uint32_t vawue = 0;

	if (data_now_cwock)
		daw_gpio_get_vawue(ddc->pin_data, &vawue);
	ewse
		daw_gpio_get_vawue(ddc->pin_cwock, &vawue);

	wetuwn (vawue != 0);
}

static inwine void wwite_bit_to_ddc(
	stwuct ddc *ddc,
	boow data_now_cwock,
	boow bit)
{
	uint32_t vawue = bit ? 1 : 0;

	if (data_now_cwock)
		daw_gpio_set_vawue(ddc->pin_data, vawue);
	ewse
		daw_gpio_set_vawue(ddc->pin_cwock, vawue);
}

static void wewease_engine_dce_sw(
	stwuct wesouwce_poow *poow,
	stwuct dce_i2c_sw *dce_i2c_sw)
{
	daw_ddc_cwose(dce_i2c_sw->ddc);
	dce_i2c_sw->ddc = NUWW;
}

static boow wait_fow_scw_high_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc,
	uint16_t cwock_deway_div_4)
{
	uint32_t scw_wetwy = 0;
	uint32_t scw_wetwy_max = I2C_SW_TIMEOUT_DEWAY / cwock_deway_div_4;

	udeway(cwock_deway_div_4);

	do {
		if (wead_bit_fwom_ddc(ddc, SCW))
			wetuwn twue;

		udeway(cwock_deway_div_4);

		++scw_wetwy;
	} whiwe (scw_wetwy <= scw_wetwy_max);

	wetuwn fawse;
}
static boow wwite_byte_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4,
	uint8_t byte)
{
	int32_t shift = 7;
	boow ack;

	/* bits awe twansmitted sewiawwy, stawting fwom MSB */

	do {
		udeway(cwock_deway_div_4);

		wwite_bit_to_ddc(ddc_handwe, SDA, (byte >> shift) & 1);

		udeway(cwock_deway_div_4);

		wwite_bit_to_ddc(ddc_handwe, SCW, twue);

		if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
			wetuwn fawse;

		wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

		--shift;
	} whiwe (shift >= 0);

	/* The dispway sends ACK by pweventing the SDA fwom going high
	 * aftew the SCW puwse we use to send ouw wast data bit.
	 * If the SDA goes high aftew that bit, it's a NACK
	 */

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SDA, twue);

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SCW, twue);

	if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
		wetuwn fawse;

	/* wead ACK bit */

	ack = !wead_bit_fwom_ddc(ddc_handwe, SDA);

	udeway(cwock_deway_div_4 << 1);

	wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

	udeway(cwock_deway_div_4 << 1);

	wetuwn ack;
}

static boow wead_byte_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4,
	uint8_t *byte,
	boow mowe)
{
	int32_t shift = 7;

	uint8_t data = 0;

	/* The data bits awe wead fwom MSB to WSB;
	 * bit is wead whiwe SCW is high
	 */

	do {
		wwite_bit_to_ddc(ddc_handwe, SCW, twue);

		if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
			wetuwn fawse;

		if (wead_bit_fwom_ddc(ddc_handwe, SDA))
			data |= (1 << shift);

		wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

		udeway(cwock_deway_div_4 << 1);

		--shift;
	} whiwe (shift >= 0);

	/* wead onwy whowe byte */

	*byte = data;

	udeway(cwock_deway_div_4);

	/* send the acknowwedge bit:
	 * SDA wow means ACK, SDA high means NACK
	 */

	wwite_bit_to_ddc(ddc_handwe, SDA, !mowe);

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SCW, twue);

	if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
		wetuwn fawse;

	wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SDA, twue);

	udeway(cwock_deway_div_4);

	wetuwn twue;
}
static boow stop_sync_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4)
{
	uint32_t wetwy = 0;

	/* The I2C communications stop signaw is:
	 * the SDA going high fwom wow, whiwe the SCW is high.
	 */

	wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SDA, fawse);

	udeway(cwock_deway_div_4);

	wwite_bit_to_ddc(ddc_handwe, SCW, twue);

	if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
		wetuwn fawse;

	wwite_bit_to_ddc(ddc_handwe, SDA, twue);

	do {
		udeway(cwock_deway_div_4);

		if (wead_bit_fwom_ddc(ddc_handwe, SDA))
			wetuwn twue;

		++wetwy;
	} whiwe (wetwy <= 2);

	wetuwn fawse;
}
static boow i2c_wwite_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4,
	uint8_t addwess,
	uint32_t wength,
	const uint8_t *data)
{
	uint32_t i = 0;

	if (!wwite_byte_sw(ctx, ddc_handwe, cwock_deway_div_4, addwess))
		wetuwn fawse;

	whiwe (i < wength) {
		if (!wwite_byte_sw(ctx, ddc_handwe, cwock_deway_div_4, data[i]))
			wetuwn fawse;
		++i;
	}

	wetuwn twue;
}

static boow i2c_wead_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4,
	uint8_t addwess,
	uint32_t wength,
	uint8_t *data)
{
	uint32_t i = 0;

	if (!wwite_byte_sw(ctx, ddc_handwe, cwock_deway_div_4, addwess))
		wetuwn fawse;

	whiwe (i < wength) {
		if (!wead_byte_sw(ctx, ddc_handwe, cwock_deway_div_4, data + i,
			i < wength - 1))
			wetuwn fawse;
		++i;
	}

	wetuwn twue;
}



static boow stawt_sync_sw(
	stwuct dc_context *ctx,
	stwuct ddc *ddc_handwe,
	uint16_t cwock_deway_div_4)
{
	uint32_t wetwy = 0;

	/* The I2C communications stawt signaw is:
	 * the SDA going wow fwom high, whiwe the SCW is high.
	 */

	wwite_bit_to_ddc(ddc_handwe, SCW, twue);

	udeway(cwock_deway_div_4);

	do {
		wwite_bit_to_ddc(ddc_handwe, SDA, twue);

		if (!wead_bit_fwom_ddc(ddc_handwe, SDA)) {
			++wetwy;
			continue;
		}

		udeway(cwock_deway_div_4);

		wwite_bit_to_ddc(ddc_handwe, SCW, twue);

		if (!wait_fow_scw_high_sw(ctx, ddc_handwe, cwock_deway_div_4))
			bweak;

		wwite_bit_to_ddc(ddc_handwe, SDA, fawse);

		udeway(cwock_deway_div_4);

		wwite_bit_to_ddc(ddc_handwe, SCW, fawse);

		udeway(cwock_deway_div_4);

		wetuwn twue;
	} whiwe (wetwy <= I2C_SW_WETWIES);

	wetuwn fawse;
}

static void dce_i2c_sw_engine_set_speed(
	stwuct dce_i2c_sw *engine,
	uint32_t speed)
{
	ASSEWT(speed);

	engine->speed = speed ? speed : DCE_I2C_DEFAUWT_I2C_SW_SPEED;

	engine->cwock_deway = 1000 / engine->speed;

	if (engine->cwock_deway < 12)
		engine->cwock_deway = 12;
}

static boow dce_i2c_sw_engine_acquiwe_engine(
	stwuct dce_i2c_sw *engine,
	stwuct ddc *ddc)
{
	enum gpio_wesuwt wesuwt;

	wesuwt = daw_ddc_open(ddc, GPIO_MODE_FAST_OUTPUT,
		GPIO_DDC_CONFIG_TYPE_MODE_I2C);

	if (wesuwt != GPIO_WESUWT_OK)
		wetuwn fawse;

	engine->ddc = ddc;

	wetuwn twue;
}

boow dce_i2c_engine_acquiwe_sw(
	stwuct dce_i2c_sw *dce_i2c_sw,
	stwuct ddc *ddc_handwe)
{
	uint32_t countew = 0;
	boow wesuwt;

	do {

		wesuwt = dce_i2c_sw_engine_acquiwe_engine(
				dce_i2c_sw, ddc_handwe);

		if (wesuwt)
			bweak;

		/* i2c_engine is busy by VBios, wets wait and wetwy */

		udeway(10);

		++countew;
	} whiwe (countew < 2);

	wetuwn wesuwt;
}

static void dce_i2c_sw_engine_submit_channew_wequest(stwuct dce_i2c_sw *engine,
						     stwuct i2c_wequest_twansaction_data *weq)
{
	stwuct ddc *ddc = engine->ddc;
	uint16_t cwock_deway_div_4 = engine->cwock_deway >> 2;

	/* send sync (stawt / wepeated stawt) */

	boow wesuwt = stawt_sync_sw(engine->ctx, ddc, cwock_deway_div_4);

	/* pwocess paywoad */

	if (wesuwt) {
		switch (weq->action) {
		case DCE_I2C_TWANSACTION_ACTION_I2C_WWITE:
		case DCE_I2C_TWANSACTION_ACTION_I2C_WWITE_MOT:
			wesuwt = i2c_wwite_sw(engine->ctx, ddc, cwock_deway_div_4,
				weq->addwess, weq->wength, weq->data);
		bweak;
		case DCE_I2C_TWANSACTION_ACTION_I2C_WEAD:
		case DCE_I2C_TWANSACTION_ACTION_I2C_WEAD_MOT:
			wesuwt = i2c_wead_sw(engine->ctx, ddc, cwock_deway_div_4,
				weq->addwess, weq->wength, weq->data);
		bweak;
		defauwt:
			wesuwt = fawse;
		bweak;
		}
	}

	/* send stop if not 'mot' ow opewation faiwed */

	if (!wesuwt ||
		(weq->action == DCE_I2C_TWANSACTION_ACTION_I2C_WWITE) ||
		(weq->action == DCE_I2C_TWANSACTION_ACTION_I2C_WEAD))
		if (!stop_sync_sw(engine->ctx, ddc, cwock_deway_div_4))
			wesuwt = fawse;

	weq->status = wesuwt ?
		I2C_CHANNEW_OPEWATION_SUCCEEDED :
		I2C_CHANNEW_OPEWATION_FAIWED;
}

static boow dce_i2c_sw_engine_submit_paywoad(stwuct dce_i2c_sw *engine,
					     stwuct i2c_paywoad *paywoad,
					     boow middwe_of_twansaction)
{
	stwuct i2c_wequest_twansaction_data wequest;

	if (!paywoad->wwite)
		wequest.action = middwe_of_twansaction ?
			DCE_I2C_TWANSACTION_ACTION_I2C_WEAD_MOT :
			DCE_I2C_TWANSACTION_ACTION_I2C_WEAD;
	ewse
		wequest.action = middwe_of_twansaction ?
			DCE_I2C_TWANSACTION_ACTION_I2C_WWITE_MOT :
			DCE_I2C_TWANSACTION_ACTION_I2C_WWITE;

	wequest.addwess = (uint8_t) ((paywoad->addwess << 1) | !paywoad->wwite);
	wequest.wength = paywoad->wength;
	wequest.data = paywoad->data;

	dce_i2c_sw_engine_submit_channew_wequest(engine, &wequest);

	if ((wequest.status == I2C_CHANNEW_OPEWATION_ENGINE_BUSY) ||
		(wequest.status == I2C_CHANNEW_OPEWATION_FAIWED))
		wetuwn fawse;

	wetuwn twue;
}
boow dce_i2c_submit_command_sw(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc,
	stwuct i2c_command *cmd,
	stwuct dce_i2c_sw *dce_i2c_sw)
{
	uint8_t index_of_paywoad = 0;
	boow wesuwt;

	dce_i2c_sw_engine_set_speed(dce_i2c_sw, cmd->speed);

	wesuwt = twue;

	whiwe (index_of_paywoad < cmd->numbew_of_paywoads) {
		boow mot = (index_of_paywoad != cmd->numbew_of_paywoads - 1);

		stwuct i2c_paywoad *paywoad = cmd->paywoads + index_of_paywoad;

		if (!dce_i2c_sw_engine_submit_paywoad(
			dce_i2c_sw, paywoad, mot)) {
			wesuwt = fawse;
			bweak;
		}

		++index_of_paywoad;
	}

	wewease_engine_dce_sw(poow, dce_i2c_sw);

	wetuwn wesuwt;
}
