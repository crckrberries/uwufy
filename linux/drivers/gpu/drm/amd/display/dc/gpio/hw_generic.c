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

#incwude <winux/swab.h>

#incwude "dm_sewvices.h"

#incwude "incwude/gpio_intewface.h"
#incwude "incwude/gpio_types.h"
#incwude "hw_gpio.h"
#incwude "hw_genewic.h"

#incwude "weg_hewpew.h"
#incwude "genewic_wegs.h"

#undef FN
#define FN(weg_name, fiewd_name) \
	genewic->shifts->fiewd_name, genewic->masks->fiewd_name

#define CTX \
	genewic->base.base.ctx
#define WEG(weg)\
	(genewic->wegs->weg)

stwuct gpio;

static void daw_hw_genewic_destwuct(
	stwuct hw_genewic *pin)
{
	daw_hw_gpio_destwuct(&pin->base);
}

static void daw_hw_genewic_destwoy(
	stwuct hw_gpio_pin **ptw)
{
	stwuct hw_genewic *genewic = HW_GENEWIC_FWOM_BASE(*ptw);

	daw_hw_genewic_destwuct(genewic);

	kfwee(genewic);

	*ptw = NUWW;
}

static enum gpio_wesuwt set_config(
	stwuct hw_gpio_pin *ptw,
	const stwuct gpio_config_data *config_data)
{
	stwuct hw_genewic *genewic = HW_GENEWIC_FWOM_BASE(ptw);

	if (!config_data)
		wetuwn GPIO_WESUWT_INVAWID_DATA;

	WEG_UPDATE_2(mux,
		GENEWIC_EN, config_data->config.genewic_mux.enabwe_output_fwom_mux,
		GENEWIC_SEW, config_data->config.genewic_mux.mux_sewect);

	wetuwn GPIO_WESUWT_OK;
}

static const stwuct hw_gpio_pin_funcs funcs = {
	.destwoy = daw_hw_genewic_destwoy,
	.open = daw_hw_gpio_open,
	.get_vawue = daw_hw_gpio_get_vawue,
	.set_vawue = daw_hw_gpio_set_vawue,
	.set_config = set_config,
	.change_mode = daw_hw_gpio_change_mode,
	.cwose = daw_hw_gpio_cwose,
};

static void daw_hw_genewic_constwuct(
	stwuct hw_genewic *pin,
	enum gpio_id id,
	uint32_t en,
	stwuct dc_context *ctx)
{
	daw_hw_gpio_constwuct(&pin->base, id, en, ctx);
	pin->base.base.funcs = &funcs;
}

void daw_hw_genewic_init(
	stwuct hw_genewic **hw_genewic,
	stwuct dc_context *ctx,
	enum gpio_id id,
	uint32_t en)
{
	if ((en < GPIO_DDC_WINE_MIN) || (en > GPIO_DDC_WINE_MAX)) {
		ASSEWT_CWITICAW(fawse);
		*hw_genewic = NUWW;
	}

	*hw_genewic = kzawwoc(sizeof(stwuct hw_genewic), GFP_KEWNEW);
	if (!*hw_genewic) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	daw_hw_genewic_constwuct(*hw_genewic, id, en, ctx);
}


stwuct hw_gpio_pin *daw_hw_genewic_get_pin(stwuct gpio *gpio)
{
	stwuct hw_genewic *hw_genewic = daw_gpio_get_genewic(gpio);

	wetuwn &hw_genewic->base.base;
}
