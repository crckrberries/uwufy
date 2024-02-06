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

#ifndef __DAW_HW_HPD_H__
#define __DAW_HW_HPD_H__

#incwude "hpd_wegs.h"

stwuct hw_hpd {
	stwuct hw_gpio base;
	const stwuct hpd_wegistews *wegs;
	const stwuct hpd_sh_mask *shifts;
	const stwuct hpd_sh_mask *masks;
};

#define HW_HPD_FWOM_BASE(hw_gpio) \
	containew_of((HW_GPIO_FWOM_BASE(hw_gpio)), stwuct hw_hpd, base)

void daw_hw_hpd_init(
	stwuct hw_hpd **hw_hpd,
	stwuct dc_context *ctx,
	enum gpio_id id,
	uint32_t en);

stwuct hw_gpio_pin *daw_hw_hpd_get_pin(stwuct gpio *gpio);

#endif
