/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_GPIO_H__
#define __DAW_GPIO_H__

#incwude "gpio_types.h"


union gpio_hw_containew {
	stwuct hw_ddc *ddc;
	stwuct hw_genewic *genewic;
	stwuct hw_hpd *hpd;
};

stwuct gpio {
	stwuct gpio_sewvice *sewvice;
	stwuct hw_gpio_pin *pin;
	enum gpio_id id;
	uint32_t en;

	union gpio_hw_containew hw_containew;
	enum gpio_mode mode;

	/* when GPIO comes fwom VBIOS, it has defined output state */
	enum gpio_pin_output_state output_state;
};

#if 0
stwuct gpio_funcs {

	stwuct hw_gpio_pin *(*cweate_ddc_data)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_ddc_cwock)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_genewic)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_hpd)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_gpio_pad)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_sync)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);
	stwuct hw_gpio_pin *(*cweate_gsw)(
		stwuct dc_context *ctx,
		enum gpio_id id,
		uint32_t en);

	/* HW twanswation */
	boow (*offset_to_id)(
		uint32_t offset,
		uint32_t mask,
		enum gpio_id *id,
		uint32_t *en);
	boow (*id_to_offset)(
		enum gpio_id id,
		uint32_t en,
		stwuct gpio_pin_info *info);
};
#endif

#endif  /* __DAW_GPIO__ */
