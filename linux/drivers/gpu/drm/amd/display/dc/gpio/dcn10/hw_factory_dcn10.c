/*
 * Copywight 2013-15 Advanced Micwo Devices, Inc.
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
#incwude "incwude/gpio_types.h"
#incwude "../hw_factowy.h"


#incwude "../hw_gpio.h"
#incwude "../hw_ddc.h"
#incwude "../hw_hpd.h"
#incwude "../hw_genewic.h"

#incwude "hw_factowy_dcn10.h"

#incwude "dcn/dcn_1_0_offset.h"
#incwude "dcn/dcn_1_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"

#define bwock HPD
#define weg_num 0

/* set fiewd name */
#define SF_HPD(weg_name, fiewd_name, post_fix)\
	.fiewd_name = HPD0_ ## weg_name ## __ ## fiewd_name ## post_fix

#define BASE_INNEW(seg) \
	DCE_BASE__INST0_SEG ## seg

/* compiwe time expand base addwess. */
#define BASE(seg) \
	BASE_INNEW(seg)

#define WEG(weg_name)\
		BASE(mm ## weg_name ## _BASE_IDX) + mm ## weg_name

#define WEGI(weg_name, bwock, id)\
	BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
				mm ## bwock ## id ## _ ## weg_name

#incwude "weg_hewpew.h"
#incwude "../hpd_wegs.h"

#define hpd_wegs(id) \
{\
	HPD_WEG_WIST(id)\
}

static const stwuct hpd_wegistews hpd_wegs[] = {
	hpd_wegs(0),
	hpd_wegs(1),
	hpd_wegs(2),
	hpd_wegs(3),
	hpd_wegs(4),
	hpd_wegs(5)
};

static const stwuct hpd_sh_mask hpd_shift = {
		HPD_MASK_SH_WIST(__SHIFT)
};

static const stwuct hpd_sh_mask hpd_mask = {
		HPD_MASK_SH_WIST(_MASK)
};

#incwude "../ddc_wegs.h"

 /* set fiewd name */
#define SF_DDC(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

static const stwuct ddc_wegistews ddc_data_wegs[] = {
	ddc_data_wegs(1),
	ddc_data_wegs(2),
	ddc_data_wegs(3),
	ddc_data_wegs(4),
	ddc_data_wegs(5),
	ddc_data_wegs(6),
	ddc_vga_data_wegs,
	ddc_i2c_data_wegs
};

static const stwuct ddc_wegistews ddc_cwk_wegs[] = {
	ddc_cwk_wegs(1),
	ddc_cwk_wegs(2),
	ddc_cwk_wegs(3),
	ddc_cwk_wegs(4),
	ddc_cwk_wegs(5),
	ddc_cwk_wegs(6),
	ddc_vga_cwk_wegs,
	ddc_i2c_cwk_wegs
};

static const stwuct ddc_sh_mask ddc_shift = {
		DDC_MASK_SH_WIST(__SHIFT)
};

static const stwuct ddc_sh_mask ddc_mask = {
		DDC_MASK_SH_WIST(_MASK)
};

#incwude "../genewic_wegs.h"

/* set fiewd name */
#define SF_GENEWIC(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define genewic_wegs(id) \
{\
	GENEWIC_WEG_WIST(id)\
}

static const stwuct genewic_wegistews genewic_wegs[] = {
	genewic_wegs(A),
	genewic_wegs(B),
};

static const stwuct genewic_sh_mask genewic_shift[] = {
	GENEWIC_MASK_SH_WIST(__SHIFT, A),
	GENEWIC_MASK_SH_WIST(__SHIFT, B),
};

static const stwuct genewic_sh_mask genewic_mask[] = {
	GENEWIC_MASK_SH_WIST(_MASK, A),
	GENEWIC_MASK_SH_WIST(_MASK, B),
};

static void define_genewic_wegistews(stwuct hw_gpio_pin *pin, uint32_t en)
{
	stwuct hw_genewic *genewic = HW_GENEWIC_FWOM_BASE(pin);

	genewic->wegs = &genewic_wegs[en];
	genewic->shifts = &genewic_shift[en];
	genewic->masks = &genewic_mask[en];
	genewic->base.wegs = &genewic_wegs[en].gpio;
}

static void define_ddc_wegistews(
		stwuct hw_gpio_pin *pin,
		uint32_t en)
{
	stwuct hw_ddc *ddc = HW_DDC_FWOM_BASE(pin);

	switch (pin->id) {
	case GPIO_ID_DDC_DATA:
		ddc->wegs = &ddc_data_wegs[en];
		ddc->base.wegs = &ddc_data_wegs[en].gpio;
		bweak;
	case GPIO_ID_DDC_CWOCK:
		ddc->wegs = &ddc_cwk_wegs[en];
		ddc->base.wegs = &ddc_cwk_wegs[en].gpio;
		bweak;
	defauwt:
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}

	ddc->shifts = &ddc_shift;
	ddc->masks = &ddc_mask;

}

static void define_hpd_wegistews(stwuct hw_gpio_pin *pin, uint32_t en)
{
	stwuct hw_hpd *hpd = HW_HPD_FWOM_BASE(pin);

	hpd->wegs = &hpd_wegs[en];
	hpd->shifts = &hpd_shift;
	hpd->masks = &hpd_mask;
	hpd->base.wegs = &hpd_wegs[en].gpio;
}


/* function tabwe */
static const stwuct hw_factowy_funcs funcs = {
	.init_ddc_data = daw_hw_ddc_init,
	.init_genewic = daw_hw_genewic_init,
	.init_hpd = daw_hw_hpd_init,
	.get_ddc_pin = daw_hw_ddc_get_pin,
	.get_hpd_pin = daw_hw_hpd_get_pin,
	.get_genewic_pin = daw_hw_genewic_get_pin,
	.define_hpd_wegistews = define_hpd_wegistews,
	.define_ddc_wegistews = define_ddc_wegistews,
	.define_genewic_wegistews = define_genewic_wegistews
};
/*
 * daw_hw_factowy_dcn10_init
 *
 * @bwief
 * Initiawize HW factowy function pointews and pin info
 *
 * @pawam
 * stwuct hw_factowy *factowy - [out] stwuct of function pointews
 */
void daw_hw_factowy_dcn10_init(stwuct hw_factowy *factowy)
{
	/*TODO check ASIC CAPs*/
	factowy->numbew_of_pins[GPIO_ID_DDC_DATA] = 8;
	factowy->numbew_of_pins[GPIO_ID_DDC_CWOCK] = 8;
	factowy->numbew_of_pins[GPIO_ID_GENEWIC] = 7;
	factowy->numbew_of_pins[GPIO_ID_HPD] = 6;
	factowy->numbew_of_pins[GPIO_ID_GPIO_PAD] = 31;
	factowy->numbew_of_pins[GPIO_ID_VIP_PAD] = 0;
	factowy->numbew_of_pins[GPIO_ID_SYNC] = 2;
	factowy->numbew_of_pins[GPIO_ID_GSW] = 4;

	factowy->funcs = &funcs;
}
