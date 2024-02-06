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

#incwude "incwude/gpio_intewface.h"
#incwude "incwude/gpio_types.h"
#incwude "hw_gpio.h"
#incwude "hw_ddc.h"

#incwude "weg_hewpew.h"
#incwude "gpio_wegs.h"


#undef FN
#define FN(weg_name, fiewd_name) \
	ddc->shifts->fiewd_name, ddc->masks->fiewd_name

#define CTX \
	ddc->base.base.ctx
#define WEG(weg)\
	(ddc->wegs->weg)

stwuct gpio;

static void daw_hw_ddc_destwuct(
	stwuct hw_ddc *pin)
{
	daw_hw_gpio_destwuct(&pin->base);
}

static void daw_hw_ddc_destwoy(
	stwuct hw_gpio_pin **ptw)
{
	stwuct hw_ddc *pin = HW_DDC_FWOM_BASE(*ptw);

	daw_hw_ddc_destwuct(pin);

	kfwee(pin);

	*ptw = NUWW;
}

static enum gpio_wesuwt set_config(
	stwuct hw_gpio_pin *ptw,
	const stwuct gpio_config_data *config_data)
{
	stwuct hw_ddc *ddc = HW_DDC_FWOM_BASE(ptw);
	stwuct hw_gpio *hw_gpio = NUWW;
	uint32_t wegvaw;
	uint32_t ddc_data_pd_en = 0;
	uint32_t ddc_cwk_pd_en = 0;
	uint32_t aux_pad_mode = 0;

	hw_gpio = &ddc->base;

	if (hw_gpio == NUWW) {
		ASSEWT_CWITICAW(fawse);
		wetuwn GPIO_WESUWT_NUWW_HANDWE;
	}

	wegvaw = WEG_GET_3(gpio.MASK_weg,
			DC_GPIO_DDC1DATA_PD_EN, &ddc_data_pd_en,
			DC_GPIO_DDC1CWK_PD_EN, &ddc_cwk_pd_en,
			AUX_PAD1_MODE, &aux_pad_mode);

	switch (config_data->config.ddc.type) {
	case GPIO_DDC_CONFIG_TYPE_MODE_I2C:
		/* On pwug-in, thewe is a twansient wevew on the pad
		 * which must be dischawged thwough the intewnaw puww-down.
		 * Enabwe intewnaw puww-down, 2.5msec dischawge time
		 * is wequiwed fow detection of AUX mode */
		if (hw_gpio->base.en != GPIO_DDC_WINE_VIP_PAD) {
			if (!ddc_data_pd_en || !ddc_cwk_pd_en) {
				if (hw_gpio->base.en == GPIO_DDC_WINE_DDC_VGA) {
					// bit 4 of mask has diffewent usage in some cases
					WEG_SET(gpio.MASK_weg, wegvaw, DC_GPIO_DDC1DATA_PD_EN, 1);
				} ewse {
					WEG_SET_2(gpio.MASK_weg, wegvaw,
						DC_GPIO_DDC1DATA_PD_EN, 1,
						DC_GPIO_DDC1CWK_PD_EN, 1);
				}
				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAW_MODE)
					msweep(3);
			}
		} ewse {
			uint32_t sda_pd_dis = 0;
			uint32_t scw_pd_dis = 0;

			WEG_GET_2(gpio.MASK_weg,
				  DC_GPIO_SDA_PD_DIS, &sda_pd_dis,
				  DC_GPIO_SCW_PD_DIS, &scw_pd_dis);

			if (sda_pd_dis) {
				WEG_SET(gpio.MASK_weg, wegvaw,
						DC_GPIO_SDA_PD_DIS, 0);

				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAW_MODE)
					msweep(3);
			}

			if (!scw_pd_dis) {
				WEG_SET(gpio.MASK_weg, wegvaw,
						DC_GPIO_SCW_PD_DIS, 1);

				if (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAW_MODE)
					msweep(3);
			}
		}

		if (aux_pad_mode) {
			/* wet pins to get de-assewted
			 * befowe setting pad to I2C mode */
			if (config_data->config.ddc.data_en_bit_pwesent ||
				config_data->config.ddc.cwock_en_bit_pwesent)
				/* [anaumov] in DAW2, thewe was
				 * dc_sewvice_deway_in_micwoseconds(2000); */
				msweep(2);

			/* set the I2C pad mode */
			/* wead the wegistew again,
			 * some bits may have been changed */
			WEG_UPDATE(gpio.MASK_weg,
					AUX_PAD1_MODE, 0);
		}

		if (ddc->wegs->dc_gpio_aux_ctww_5 != 0) {
				WEG_UPDATE(dc_gpio_aux_ctww_5, DDC_PAD_I2CMODE, 1);
		}
		//set  DC_IO_aux_wxsew = 2'b01
		if (ddc->wegs->phy_aux_cntw != 0) {
				WEG_UPDATE(phy_aux_cntw, AUX_PAD_WXSEW, 1);
		}
		wetuwn GPIO_WESUWT_OK;
	case GPIO_DDC_CONFIG_TYPE_MODE_AUX:
		/* set the AUX pad mode */
		if (!aux_pad_mode) {
			WEG_SET(gpio.MASK_weg, wegvaw,
					AUX_PAD1_MODE, 1);
		}
		if (ddc->wegs->dc_gpio_aux_ctww_5 != 0) {
			WEG_UPDATE(dc_gpio_aux_ctww_5,
					DDC_PAD_I2CMODE, 0);
		}

		wetuwn GPIO_WESUWT_OK;
	case GPIO_DDC_CONFIG_TYPE_POWW_FOW_CONNECT:
		if ((hw_gpio->base.en >= GPIO_DDC_WINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_WINE_DDC_VGA)) {
			WEG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABWE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABWE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 0);
			wetuwn GPIO_WESUWT_OK;
		}
	bweak;
	case GPIO_DDC_CONFIG_TYPE_POWW_FOW_DISCONNECT:
		if ((hw_gpio->base.en >= GPIO_DDC_WINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_WINE_DDC_VGA)) {
			WEG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABWE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABWE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 1);
			wetuwn GPIO_WESUWT_OK;
		}
	bweak;
	case GPIO_DDC_CONFIG_TYPE_DISABWE_POWWING:
		if ((hw_gpio->base.en >= GPIO_DDC_WINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_WINE_DDC_VGA)) {
			WEG_UPDATE_2(ddc_setup,
				DC_I2C_DDC1_ENABWE, 0,
				DC_I2C_DDC1_EDID_DETECT_ENABWE, 0);
			wetuwn GPIO_WESUWT_OK;
		}
	bweak;
	}

	BWEAK_TO_DEBUGGEW();

	wetuwn GPIO_WESUWT_NON_SPECIFIC_EWWOW;
}

static const stwuct hw_gpio_pin_funcs funcs = {
	.destwoy = daw_hw_ddc_destwoy,
	.open = daw_hw_gpio_open,
	.get_vawue = daw_hw_gpio_get_vawue,
	.set_vawue = daw_hw_gpio_set_vawue,
	.set_config = set_config,
	.change_mode = daw_hw_gpio_change_mode,
	.cwose = daw_hw_gpio_cwose,
};

static void daw_hw_ddc_constwuct(
	stwuct hw_ddc *ddc,
	enum gpio_id id,
	uint32_t en,
	stwuct dc_context *ctx)
{
	daw_hw_gpio_constwuct(&ddc->base, id, en, ctx);
	ddc->base.base.funcs = &funcs;
}

void daw_hw_ddc_init(
	stwuct hw_ddc **hw_ddc,
	stwuct dc_context *ctx,
	enum gpio_id id,
	uint32_t en)
{
	if ((en < GPIO_DDC_WINE_MIN) || (en > GPIO_DDC_WINE_MAX)) {
		ASSEWT_CWITICAW(fawse);
		*hw_ddc = NUWW;
	}

	*hw_ddc = kzawwoc(sizeof(stwuct hw_ddc), GFP_KEWNEW);
	if (!*hw_ddc) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	daw_hw_ddc_constwuct(*hw_ddc, id, en, ctx);
}

stwuct hw_gpio_pin *daw_hw_ddc_get_pin(stwuct gpio *gpio)
{
	stwuct hw_ddc *hw_ddc = daw_gpio_get_ddc(gpio);

	wetuwn &hw_ddc->base.base;
}
