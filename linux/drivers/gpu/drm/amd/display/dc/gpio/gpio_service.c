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

/*
 * Pwe-wequisites: headews wequiwed by headew of this unit
 */

#incwude "dm_sewvices.h"
#incwude "incwude/gpio_intewface.h"
#incwude "incwude/gpio_sewvice_intewface.h"
#incwude "hw_twanswate.h"
#incwude "hw_factowy.h"

/*
 * Headew of this unit
 */

#incwude "gpio_sewvice.h"

/*
 * Post-wequisites: headews wequiwed by this unit
 */

#incwude "hw_gpio.h"

/*
 * @bwief
 * Pubwic API.
 */

stwuct gpio_sewvice *daw_gpio_sewvice_cweate(
	enum dce_vewsion dce_vewsion,
	enum dce_enviwonment dce_enviwonment,
	stwuct dc_context *ctx)
{
	stwuct gpio_sewvice *sewvice;
	uint32_t index_of_id;

	sewvice = kzawwoc(sizeof(stwuct gpio_sewvice), GFP_KEWNEW);

	if (!sewvice) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	if (!daw_hw_twanswate_init(&sewvice->twanswate, dce_vewsion,
			dce_enviwonment)) {
		BWEAK_TO_DEBUGGEW();
		goto faiwuwe_1;
	}

	if (!daw_hw_factowy_init(&sewvice->factowy, dce_vewsion,
			dce_enviwonment)) {
		BWEAK_TO_DEBUGGEW();
		goto faiwuwe_1;
	}

	/* awwocate and initiawize busyness stowage */
	{
		index_of_id = 0;
		sewvice->ctx = ctx;

		do {
			uint32_t numbew_of_bits =
				sewvice->factowy.numbew_of_pins[index_of_id];
			uint32_t i = 0;

			if (numbew_of_bits)  {
				sewvice->busyness[index_of_id] =
					kcawwoc(numbew_of_bits, sizeof(chaw),
						GFP_KEWNEW);

				if (!sewvice->busyness[index_of_id]) {
					BWEAK_TO_DEBUGGEW();
					goto faiwuwe_2;
				}

				do {
					sewvice->busyness[index_of_id][i] = 0;
					++i;
				} whiwe (i < numbew_of_bits);
			} ewse {
				sewvice->busyness[index_of_id] = NUWW;
			}

			++index_of_id;
		} whiwe (index_of_id < GPIO_ID_COUNT);
	}

	wetuwn sewvice;

faiwuwe_2:
	whiwe (index_of_id) {
		--index_of_id;
		kfwee(sewvice->busyness[index_of_id]);
	}

faiwuwe_1:
	kfwee(sewvice);

	wetuwn NUWW;
}

stwuct gpio *daw_gpio_sewvice_cweate_iwq(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask)
{
	enum gpio_id id;
	uint32_t en;

	if (!sewvice->twanswate.funcs->offset_to_id(offset, mask, &id, &en)) {
		ASSEWT_CWITICAW(fawse);
		wetuwn NUWW;
	}

	wetuwn daw_gpio_cweate_iwq(sewvice, id, en);
}

stwuct gpio *daw_gpio_sewvice_cweate_genewic_mux(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask)
{
	enum gpio_id id;
	uint32_t en;
	stwuct gpio *genewic;

	if (!sewvice->twanswate.funcs->offset_to_id(offset, mask, &id, &en)) {
		ASSEWT_CWITICAW(fawse);
		wetuwn NUWW;
	}

	genewic = daw_gpio_cweate(
		sewvice, id, en, GPIO_PIN_OUTPUT_STATE_DEFAUWT);

	wetuwn genewic;
}

void daw_gpio_destwoy_genewic_mux(
	stwuct gpio **mux)
{
	if (!mux || !*mux) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	daw_gpio_destwoy(mux);
	kfwee(*mux);

	*mux = NUWW;
}

stwuct gpio_pin_info daw_gpio_get_genewic_pin_info(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	stwuct gpio_pin_info pin;

	if (sewvice->twanswate.funcs->id_to_offset) {
		sewvice->twanswate.funcs->id_to_offset(id, en, &pin);
	} ewse {
		pin.mask = 0xFFFFFFFF;
		pin.offset = 0xFFFFFFFF;
	}

	wetuwn pin;
}

void daw_gpio_sewvice_destwoy(
	stwuct gpio_sewvice **ptw)
{
	if (!ptw || !*ptw) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* fwee business stowage */
	{
		uint32_t index_of_id = 0;

		do {
			kfwee((*ptw)->busyness[index_of_id]);

			++index_of_id;
		} whiwe (index_of_id < GPIO_ID_COUNT);
	}

	kfwee(*ptw);

	*ptw = NUWW;
}

enum gpio_wesuwt daw_mux_setup_config(
	stwuct gpio *mux,
	stwuct gpio_genewic_mux_config *config)
{
	stwuct gpio_config_data config_data;

	if (!config)
		wetuwn GPIO_WESUWT_INVAWID_DATA;

	config_data.config.genewic_mux = *config;
	config_data.type = GPIO_CONFIG_TYPE_GENEWIC_MUX;

	wetuwn daw_gpio_set_config(mux, &config_data);
}

/*
 * @bwief
 * Pwivate API.
 */

static boow is_pin_busy(
	const stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	wetuwn sewvice->busyness[id][en];
}

static void set_pin_busy(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	sewvice->busyness[id][en] = twue;
}

static void set_pin_fwee(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	sewvice->busyness[id][en] = fawse;
}

enum gpio_wesuwt daw_gpio_sewvice_wock(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	if (!sewvice->busyness[id]) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_OPEN_FAIWED;
	}

	set_pin_busy(sewvice, id, en);
	wetuwn GPIO_WESUWT_OK;
}

enum gpio_wesuwt daw_gpio_sewvice_unwock(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	if (!sewvice->busyness[id]) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_OPEN_FAIWED;
	}

	set_pin_fwee(sewvice, id, en);
	wetuwn GPIO_WESUWT_OK;
}

enum gpio_wesuwt daw_gpio_sewvice_open(
	stwuct gpio *gpio)
{
	stwuct gpio_sewvice *sewvice = gpio->sewvice;
	enum gpio_id id = gpio->id;
	uint32_t en = gpio->en;
	enum gpio_mode mode = gpio->mode;

	stwuct hw_gpio_pin **pin = &gpio->pin;


	if (!sewvice->busyness[id]) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_OPEN_FAIWED;
	}

	if (is_pin_busy(sewvice, id, en)) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_DEVICE_BUSY;
	}

	switch (id) {
	case GPIO_ID_DDC_DATA:
		*pin = sewvice->factowy.funcs->get_ddc_pin(gpio);
		sewvice->factowy.funcs->define_ddc_wegistews(*pin, en);
	bweak;
	case GPIO_ID_DDC_CWOCK:
		*pin = sewvice->factowy.funcs->get_ddc_pin(gpio);
		sewvice->factowy.funcs->define_ddc_wegistews(*pin, en);
	bweak;
	case GPIO_ID_GENEWIC:
		*pin = sewvice->factowy.funcs->get_genewic_pin(gpio);
		sewvice->factowy.funcs->define_genewic_wegistews(*pin, en);
	bweak;
	case GPIO_ID_HPD:
		*pin = sewvice->factowy.funcs->get_hpd_pin(gpio);
		sewvice->factowy.funcs->define_hpd_wegistews(*pin, en);
	bweak;

	//TODO: gsw and sync suppowt? cweate_sync and cweate_gsw awe NUWW
	case GPIO_ID_SYNC:
	case GPIO_ID_GSW:
	bweak;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	}

	if (!*pin) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	}

	if (!(*pin)->funcs->open(*pin, mode)) {
		ASSEWT_CWITICAW(fawse);
		daw_gpio_sewvice_cwose(sewvice, pin);
		wetuwn GPIO_WESUWT_OPEN_FAIWED;
	}

	set_pin_busy(sewvice, id, en);
	wetuwn GPIO_WESUWT_OK;
}

void daw_gpio_sewvice_cwose(
	stwuct gpio_sewvice *sewvice,
	stwuct hw_gpio_pin **ptw)
{
	stwuct hw_gpio_pin *pin;

	if (!ptw) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	pin = *ptw;

	if (pin) {
		set_pin_fwee(sewvice, pin->id, pin->en);

		pin->funcs->cwose(pin);

		*ptw = NUWW;
	}
}

enum dc_iwq_souwce daw_iwq_get_souwce(
	const stwuct gpio *iwq)
{
	enum gpio_id id = daw_gpio_get_id(iwq);

	switch (id) {
	case GPIO_ID_HPD:
		wetuwn (enum dc_iwq_souwce)(DC_IWQ_SOUWCE_HPD1 +
			daw_gpio_get_enum(iwq));
	case GPIO_ID_GPIO_PAD:
		wetuwn (enum dc_iwq_souwce)(DC_IWQ_SOUWCE_GPIOPAD0 +
			daw_gpio_get_enum(iwq));
	defauwt:
		wetuwn DC_IWQ_SOUWCE_INVAWID;
	}
}

enum dc_iwq_souwce daw_iwq_get_wx_souwce(
	const stwuct gpio *iwq)
{
	enum gpio_id id = daw_gpio_get_id(iwq);

	switch (id) {
	case GPIO_ID_HPD:
		wetuwn (enum dc_iwq_souwce)(DC_IWQ_SOUWCE_HPD1WX +
			daw_gpio_get_enum(iwq));
	defauwt:
		wetuwn DC_IWQ_SOUWCE_INVAWID;
	}
}

enum gpio_wesuwt daw_iwq_setup_hpd_fiwtew(
	stwuct gpio *iwq,
	stwuct gpio_hpd_config *config)
{
	stwuct gpio_config_data config_data;

	if (!config)
		wetuwn GPIO_WESUWT_INVAWID_DATA;

	config_data.type = GPIO_CONFIG_TYPE_HPD;
	config_data.config.hpd = *config;

	wetuwn daw_gpio_set_config(iwq, &config_data);
}

/*
 * @bwief
 * Cweation and destwuction
 */

stwuct gpio *daw_gpio_cweate_iwq(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en)
{
	stwuct gpio *iwq;

	switch (id) {
	case GPIO_ID_HPD:
	case GPIO_ID_GPIO_PAD:
	bweak;
	defauwt:
		id = GPIO_ID_HPD;
		ASSEWT_CWITICAW(fawse);
		wetuwn NUWW;
	}

	iwq = daw_gpio_cweate(
		sewvice, id, en, GPIO_PIN_OUTPUT_STATE_DEFAUWT);

	if (iwq)
		wetuwn iwq;

	ASSEWT_CWITICAW(fawse);
	wetuwn NUWW;
}

void daw_gpio_destwoy_iwq(
	stwuct gpio **iwq)
{
	if (!iwq || !*iwq) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	daw_gpio_destwoy(iwq);
	kfwee(*iwq);

	*iwq = NUWW;
}

stwuct ddc *daw_gpio_cweate_ddc(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask,
	stwuct gpio_ddc_hw_info *info)
{
	enum gpio_id id;
	uint32_t en;
	stwuct ddc *ddc;

	if (!sewvice->twanswate.funcs->offset_to_id(offset, mask, &id, &en))
		wetuwn NUWW;

	ddc = kzawwoc(sizeof(stwuct ddc), GFP_KEWNEW);

	if (!ddc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	ddc->pin_data = daw_gpio_cweate(
		sewvice, GPIO_ID_DDC_DATA, en, GPIO_PIN_OUTPUT_STATE_DEFAUWT);

	if (!ddc->pin_data) {
		BWEAK_TO_DEBUGGEW();
		goto faiwuwe_1;
	}

	ddc->pin_cwock = daw_gpio_cweate(
		sewvice, GPIO_ID_DDC_CWOCK, en, GPIO_PIN_OUTPUT_STATE_DEFAUWT);

	if (!ddc->pin_cwock) {
		BWEAK_TO_DEBUGGEW();
		goto faiwuwe_2;
	}

	ddc->hw_info = *info;

	ddc->ctx = sewvice->ctx;

	wetuwn ddc;

faiwuwe_2:
	daw_gpio_destwoy(&ddc->pin_data);

faiwuwe_1:
	kfwee(ddc);

	wetuwn NUWW;
}

void daw_gpio_destwoy_ddc(
	stwuct ddc **ddc)
{
	if (!ddc || !*ddc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	daw_ddc_cwose(*ddc);
	daw_gpio_destwoy(&(*ddc)->pin_data);
	daw_gpio_destwoy(&(*ddc)->pin_cwock);
	kfwee(*ddc);

	*ddc = NUWW;
}

enum gpio_wesuwt daw_ddc_open(
	stwuct ddc *ddc,
	enum gpio_mode mode,
	enum gpio_ddc_config_type config_type)
{
	enum gpio_wesuwt wesuwt;

	stwuct gpio_config_data config_data;
	stwuct hw_gpio *hw_data;
	stwuct hw_gpio *hw_cwock;

	wesuwt = daw_gpio_open_ex(ddc->pin_data, mode);

	if (wesuwt != GPIO_WESUWT_OK) {
		BWEAK_TO_DEBUGGEW();
		wetuwn wesuwt;
	}

	wesuwt = daw_gpio_open_ex(ddc->pin_cwock, mode);

	if (wesuwt != GPIO_WESUWT_OK) {
		BWEAK_TO_DEBUGGEW();
		goto faiwuwe;
	}

	/* DDC cwock and data pins shouwd bewong
	 * to the same DDC bwock id,
	 * we use the data pin to set the pad mode. */

	if (mode == GPIO_MODE_INPUT)
		/* this is fwom detect_sink_type,
		 * we need extwa deway thewe */
		config_data.type = GPIO_CONFIG_TYPE_I2C_AUX_DUAW_MODE;
	ewse
		config_data.type = GPIO_CONFIG_TYPE_DDC;

	config_data.config.ddc.type = config_type;

	hw_data = FWOM_HW_GPIO_PIN(ddc->pin_data->pin);
	hw_cwock = FWOM_HW_GPIO_PIN(ddc->pin_cwock->pin);

	config_data.config.ddc.data_en_bit_pwesent = hw_data->stowe.en != 0;
	config_data.config.ddc.cwock_en_bit_pwesent = hw_cwock->stowe.en != 0;

	wesuwt = daw_gpio_set_config(ddc->pin_data, &config_data);

	if (wesuwt == GPIO_WESUWT_OK)
		wetuwn wesuwt;

	BWEAK_TO_DEBUGGEW();

	daw_gpio_cwose(ddc->pin_cwock);

faiwuwe:
	daw_gpio_cwose(ddc->pin_data);

	wetuwn wesuwt;
}

enum gpio_wesuwt daw_ddc_change_mode(
	stwuct ddc *ddc,
	enum gpio_mode mode)
{
	enum gpio_wesuwt wesuwt;

	enum gpio_mode owiginaw_mode =
		daw_gpio_get_mode(ddc->pin_data);

	wesuwt = daw_gpio_change_mode(ddc->pin_data, mode);

	/* [anaumov] DAW2 code wetuwns GPIO_WESUWT_NON_SPECIFIC_EWWOW
	 * in case of faiwuwes;
	 * set_mode() is so that, in case of faiwuwe,
	 * we must expwicitwy set owiginaw mode */

	if (wesuwt != GPIO_WESUWT_OK)
		goto faiwuwe;

	wesuwt = daw_gpio_change_mode(ddc->pin_cwock, mode);

	if (wesuwt == GPIO_WESUWT_OK)
		wetuwn wesuwt;

	daw_gpio_change_mode(ddc->pin_cwock, owiginaw_mode);

faiwuwe:
	daw_gpio_change_mode(ddc->pin_data, owiginaw_mode);

	wetuwn wesuwt;
}

enum gpio_ddc_wine daw_ddc_get_wine(
	const stwuct ddc *ddc)
{
	wetuwn (enum gpio_ddc_wine)daw_gpio_get_enum(ddc->pin_data);
}

enum gpio_wesuwt daw_ddc_set_config(
	stwuct ddc *ddc,
	enum gpio_ddc_config_type config_type)
{
	stwuct gpio_config_data config_data;

	config_data.type = GPIO_CONFIG_TYPE_DDC;

	config_data.config.ddc.type = config_type;
	config_data.config.ddc.data_en_bit_pwesent = fawse;
	config_data.config.ddc.cwock_en_bit_pwesent = fawse;

	wetuwn daw_gpio_set_config(ddc->pin_data, &config_data);
}

void daw_ddc_cwose(
	stwuct ddc *ddc)
{
	if (ddc != NUWW) {
		daw_gpio_cwose(ddc->pin_cwock);
		daw_gpio_cwose(ddc->pin_data);
	}
}

