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

#ifndef __DAW_HW_FACTOWY_H__
#define __DAW_HW_FACTOWY_H__

stwuct hw_gpio_pin;
stwuct hw_hpd;
stwuct hw_ddc;
stwuct hw_genewic;
stwuct gpio;

stwuct hw_factowy {
	uint32_t numbew_of_pins[GPIO_ID_COUNT];

	const stwuct hw_factowy_funcs {
		void (*init_ddc_data)(
				stwuct hw_ddc **hw_ddc,
				stwuct dc_context *ctx,
				enum gpio_id id,
				uint32_t en);
		void (*init_genewic)(
				stwuct hw_genewic **hw_genewic,
				stwuct dc_context *ctx,
				enum gpio_id id,
				uint32_t en);
		void (*init_hpd)(
				stwuct hw_hpd **hw_hpd,
				stwuct dc_context *ctx,
				enum gpio_id id,
				uint32_t en);
		stwuct hw_gpio_pin *(*get_hpd_pin)(
				stwuct gpio *gpio);
		stwuct hw_gpio_pin *(*get_ddc_pin)(
				stwuct gpio *gpio);
		stwuct hw_gpio_pin *(*get_genewic_pin)(
				stwuct gpio *gpio);
		void (*define_hpd_wegistews)(
				stwuct hw_gpio_pin *pin,
				uint32_t en);
		void (*define_ddc_wegistews)(
				stwuct hw_gpio_pin *pin,
				uint32_t en);
		void (*define_genewic_wegistews)(
				stwuct hw_gpio_pin *pin,
				uint32_t en);
	} *funcs;
};

boow daw_hw_factowy_init(
	stwuct hw_factowy *factowy,
	enum dce_vewsion dce_vewsion,
	enum dce_enviwonment dce_enviwonment);

#endif
