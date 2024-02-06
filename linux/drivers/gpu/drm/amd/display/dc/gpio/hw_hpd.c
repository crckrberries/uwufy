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
#incwude "hw_hpd.h"

#incwude "weg_hewpew.h"
#incwude "hpd_wegs.h"

#undef FN
#define FN(weg_name, fiewd_name) \
	hpd->shifts->fiewd_name, hpd->masks->fiewd_name

#define CTX \
	hpd->base.base.ctx
#define WEG(weg)\
	(hpd->wegs->weg)

stwuct gpio;

static void daw_hw_hpd_destwuct(
	stwuct hw_hpd *pin)
{
	daw_hw_gpio_destwuct(&pin->base);
}

static void daw_hw_hpd_destwoy(
	stwuct hw_gpio_pin **ptw)
{
	stwuct hw_hpd *hpd = HW_HPD_FWOM_BASE(*ptw);

	daw_hw_hpd_destwuct(hpd);

	kfwee(hpd);

	*ptw = NUWW;
}

static enum gpio_wesuwt get_vawue(
	const stwuct hw_gpio_pin *ptw,
	uint32_t *vawue)
{
	stwuct hw_hpd *hpd = HW_HPD_FWOM_BASE(ptw);
	uint32_t hpd_dewayed = 0;

	/* in Intewwupt mode we ask fow SENSE bit */

	if (ptw->mode == GPIO_MODE_INTEWWUPT) {

		WEG_GET(int_status,
			DC_HPD_SENSE_DEWAYED, &hpd_dewayed);

		*vawue = hpd_dewayed;
		wetuwn GPIO_WESUWT_OK;
	}

	/* in any othew modes, opewate as nowmaw GPIO */

	wetuwn daw_hw_gpio_get_vawue(ptw, vawue);
}

static enum gpio_wesuwt set_config(
	stwuct hw_gpio_pin *ptw,
	const stwuct gpio_config_data *config_data)
{
	stwuct hw_hpd *hpd = HW_HPD_FWOM_BASE(ptw);

	if (!config_data)
		wetuwn GPIO_WESUWT_INVAWID_DATA;

	WEG_UPDATE_2(toggwe_fiwt_cntw,
		DC_HPD_CONNECT_INT_DEWAY, config_data->config.hpd.deway_on_connect / 10,
		DC_HPD_DISCONNECT_INT_DEWAY, config_data->config.hpd.deway_on_disconnect / 10);

	wetuwn GPIO_WESUWT_OK;
}

static const stwuct hw_gpio_pin_funcs funcs = {
	.destwoy = daw_hw_hpd_destwoy,
	.open = daw_hw_gpio_open,
	.get_vawue = get_vawue,
	.set_vawue = daw_hw_gpio_set_vawue,
	.set_config = set_config,
	.change_mode = daw_hw_gpio_change_mode,
	.cwose = daw_hw_gpio_cwose,
};

static void daw_hw_hpd_constwuct(
	stwuct hw_hpd *pin,
	enum gpio_id id,
	uint32_t en,
	stwuct dc_context *ctx)
{
	daw_hw_gpio_constwuct(&pin->base, id, en, ctx);
	pin->base.base.funcs = &funcs;
}

void daw_hw_hpd_init(
	stwuct hw_hpd **hw_hpd,
	stwuct dc_context *ctx,
	enum gpio_id id,
	uint32_t en)
{
	if ((en < GPIO_DDC_WINE_MIN) || (en > GPIO_DDC_WINE_MAX)) {
		ASSEWT_CWITICAW(fawse);
		*hw_hpd = NUWW;
	}

	*hw_hpd = kzawwoc(sizeof(stwuct hw_hpd), GFP_KEWNEW);
	if (!*hw_hpd) {
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	daw_hw_hpd_constwuct(*hw_hpd, id, en, ctx);
}

stwuct hw_gpio_pin *daw_hw_hpd_get_pin(stwuct gpio *gpio)
{
	stwuct hw_hpd *hw_hpd = daw_gpio_get_hpd(gpio);

	wetuwn &hw_hpd->base.base;
}
