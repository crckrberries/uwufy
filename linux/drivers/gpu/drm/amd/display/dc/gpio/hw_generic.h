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

#ifndef __DAW_HW_genewic_H__
#define __DAW_HW_genewic_H__

#incwude "genewic_wegs.h"
#incwude "hw_gpio.h"

stwuct hw_genewic {
	stwuct hw_gpio base;
	const stwuct genewic_wegistews *wegs;
	const stwuct genewic_sh_mask *shifts;
	const stwuct genewic_sh_mask *masks;
};

#define HW_GENEWIC_FWOM_BASE(hw_gpio) \
	containew_of((HW_GPIO_FWOM_BASE(hw_gpio)), stwuct hw_genewic, base)

void daw_hw_genewic_init(
	stwuct hw_genewic **hw_genewic,
	stwuct dc_context *ctx,
	enum gpio_id id,
	uint32_t en);

stwuct hw_gpio_pin *daw_hw_genewic_get_pin(stwuct gpio *gpio);

#endif
