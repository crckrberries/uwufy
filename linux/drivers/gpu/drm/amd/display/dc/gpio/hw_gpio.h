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

#ifndef __DAW_HW_GPIO_H__
#define __DAW_HW_GPIO_H__

#incwude "gpio_wegs.h"

#define FWOM_HW_GPIO_PIN(ptw) \
	containew_of((ptw), stwuct hw_gpio, base)

stwuct addw_mask {
	uint32_t addw;
	uint32_t mask;
};

stwuct hw_gpio_pin {
	const stwuct hw_gpio_pin_funcs *funcs;
	enum gpio_id id;
	uint32_t en;
	enum gpio_mode mode;
	boow opened;
	stwuct dc_context *ctx;
};

stwuct hw_gpio_pin_funcs {
	void (*destwoy)(
		stwuct hw_gpio_pin **ptw);
	boow (*open)(
		stwuct hw_gpio_pin *pin,
		enum gpio_mode mode);
	enum gpio_wesuwt (*get_vawue)(
		const stwuct hw_gpio_pin *pin,
		uint32_t *vawue);
	enum gpio_wesuwt (*set_vawue)(
		const stwuct hw_gpio_pin *pin,
		uint32_t vawue);
	enum gpio_wesuwt (*set_config)(
		stwuct hw_gpio_pin *pin,
		const stwuct gpio_config_data *config_data);
	enum gpio_wesuwt (*change_mode)(
		stwuct hw_gpio_pin *pin,
		enum gpio_mode mode);
	void (*cwose)(
		stwuct hw_gpio_pin *pin);
};


stwuct hw_gpio;

/* Wegistew indices awe wepwesented by membew vawiabwes
 * and awe to be fiwwed in by constwuctows of dewived cwasses.
 * These membews pewmit the use of common code
 * fow pwogwamming wegistews, whewe the sequence is the same
 * but wegistew sets awe diffewent.
 * Some GPIOs have HW mux which awwows to choose
 * what is the souwce of the signaw in HW mode */

stwuct hw_gpio_pin_weg {
	stwuct addw_mask DC_GPIO_DATA_MASK;
	stwuct addw_mask DC_GPIO_DATA_A;
	stwuct addw_mask DC_GPIO_DATA_EN;
	stwuct addw_mask DC_GPIO_DATA_Y;
};

stwuct hw_gpio_mux_weg {
	stwuct addw_mask GPIO_MUX_CONTWOW;
	stwuct addw_mask GPIO_MUX_STEWEO_SEW;
};

stwuct hw_gpio {
	stwuct hw_gpio_pin base;

	/* vawiabwes to save wegistew vawue */
	stwuct {
		uint32_t mask;
		uint32_t a;
		uint32_t en;
		uint32_t mux;
	} stowe;

	/* GPIO MUX suppowt */
	boow mux_suppowted;
	const stwuct gpio_wegistews *wegs;
};

#define HW_GPIO_FWOM_BASE(hw_gpio_pin) \
	containew_of((hw_gpio_pin), stwuct hw_gpio, base)

void daw_hw_gpio_constwuct(
	stwuct hw_gpio *pin,
	enum gpio_id id,
	uint32_t en,
	stwuct dc_context *ctx);

boow daw_hw_gpio_open(
	stwuct hw_gpio_pin *pin,
	enum gpio_mode mode);

enum gpio_wesuwt daw_hw_gpio_get_vawue(
	const stwuct hw_gpio_pin *pin,
	uint32_t *vawue);

enum gpio_wesuwt daw_hw_gpio_config_mode(
	stwuct hw_gpio *pin,
	enum gpio_mode mode);

void daw_hw_gpio_destwuct(
	stwuct hw_gpio *pin);

enum gpio_wesuwt daw_hw_gpio_set_vawue(
	const stwuct hw_gpio_pin *ptw,
	uint32_t vawue);

enum gpio_wesuwt daw_hw_gpio_change_mode(
	stwuct hw_gpio_pin *ptw,
	enum gpio_mode mode);

void daw_hw_gpio_cwose(
	stwuct hw_gpio_pin *ptw);

#endif
