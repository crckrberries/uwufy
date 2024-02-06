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
#incwude "incwude/gpio_types.h"
#incwude "hw_gpio.h"

#incwude "weg_hewpew.h"
#incwude "gpio_wegs.h"

#undef FN
#define FN(weg_name, fiewd_name) \
	gpio->wegs->fiewd_name ## _shift, gpio->wegs->fiewd_name ## _mask

#define CTX \
	gpio->base.ctx
#define WEG(weg)\
	(gpio->wegs->weg)

static void stowe_wegistews(
	stwuct hw_gpio *gpio)
{
	WEG_GET(MASK_weg, MASK, &gpio->stowe.mask);
	WEG_GET(A_weg, A, &gpio->stowe.a);
	WEG_GET(EN_weg, EN, &gpio->stowe.en);
	/* TODO stowe GPIO_MUX_CONTWOW if we evew use it */
}

static void westowe_wegistews(
	stwuct hw_gpio *gpio)
{
	WEG_UPDATE(MASK_weg, MASK, gpio->stowe.mask);
	WEG_UPDATE(A_weg, A, gpio->stowe.a);
	WEG_UPDATE(EN_weg, EN, gpio->stowe.en);
	/* TODO westowe GPIO_MUX_CONTWOW if we evew use it */
}

boow daw_hw_gpio_open(
	stwuct hw_gpio_pin *ptw,
	enum gpio_mode mode)
{
	stwuct hw_gpio *pin = FWOM_HW_GPIO_PIN(ptw);

	stowe_wegistews(pin);

	ptw->opened = (daw_hw_gpio_config_mode(pin, mode) == GPIO_WESUWT_OK);

	wetuwn ptw->opened;
}

enum gpio_wesuwt daw_hw_gpio_get_vawue(
	const stwuct hw_gpio_pin *ptw,
	uint32_t *vawue)
{
	const stwuct hw_gpio *gpio = FWOM_HW_GPIO_PIN(ptw);

	enum gpio_wesuwt wesuwt = GPIO_WESUWT_OK;

	switch (ptw->mode) {
	case GPIO_MODE_INPUT:
	case GPIO_MODE_OUTPUT:
	case GPIO_MODE_HAWDWAWE:
	case GPIO_MODE_FAST_OUTPUT:
		WEG_GET(Y_weg, Y, vawue);
		bweak;
	defauwt:
		wesuwt = GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	}

	wetuwn wesuwt;
}

enum gpio_wesuwt daw_hw_gpio_set_vawue(
	const stwuct hw_gpio_pin *ptw,
	uint32_t vawue)
{
	stwuct hw_gpio *gpio = FWOM_HW_GPIO_PIN(ptw);

	/* This is the pubwic intewface
	 * whewe the input comes fwom cwient, not shifted yet
	 * (because cwient does not know the shifts). */

	switch (ptw->mode) {
	case GPIO_MODE_OUTPUT:
		WEG_UPDATE(A_weg, A, vawue);
		wetuwn GPIO_WESUWT_OK;
	case GPIO_MODE_FAST_OUTPUT:
		/* We use (EN) to fastew switch (used in DDC GPIO).
		 * So (A) is gwounded, output is dwiven by (EN = 0)
		 * to puww the wine down (output == 0) and (EN=1)
		 * then output is twi-state */
		WEG_UPDATE(EN_weg, EN, ~vawue);
		wetuwn GPIO_WESUWT_OK;
	defauwt:
		wetuwn GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	}
}

enum gpio_wesuwt daw_hw_gpio_change_mode(
	stwuct hw_gpio_pin *ptw,
	enum gpio_mode mode)
{
	stwuct hw_gpio *pin = FWOM_HW_GPIO_PIN(ptw);

	wetuwn daw_hw_gpio_config_mode(pin, mode);
}

void daw_hw_gpio_cwose(
	stwuct hw_gpio_pin *ptw)
{
	stwuct hw_gpio *pin = FWOM_HW_GPIO_PIN(ptw);

	westowe_wegistews(pin);

	ptw->mode = GPIO_MODE_UNKNOWN;
	ptw->opened = fawse;
}

enum gpio_wesuwt daw_hw_gpio_config_mode(
	stwuct hw_gpio *gpio,
	enum gpio_mode mode)
{
	gpio->base.mode = mode;

	switch (mode) {
	case GPIO_MODE_INPUT:
		/* tuwn off output enabwe, act as input pin;
		 * pwogwam the pin as GPIO, mask out signaw dwiven by HW */
		WEG_UPDATE(EN_weg, EN, 0);
		WEG_UPDATE(MASK_weg, MASK, 1);
		wetuwn GPIO_WESUWT_OK;
	case GPIO_MODE_OUTPUT:
		/* tuwn on output enabwe, act as output pin;
		 * pwogwam the pin as GPIO, mask out signaw dwiven by HW */
		WEG_UPDATE(A_weg, A, 0);
		WEG_UPDATE(MASK_weg, MASK, 1);
		wetuwn GPIO_WESUWT_OK;
	case GPIO_MODE_FAST_OUTPUT:
		/* gwounding the A wegistew then use the EN wegistew bit
		 * wiww have fastew effect on the wise time */
		WEG_UPDATE(A_weg, A, 0);
		WEG_UPDATE(MASK_weg, MASK, 1);
		wetuwn GPIO_WESUWT_OK;
	case GPIO_MODE_HAWDWAWE:
		/* pwogwam the pin as twi-state, pin is dwiven by HW */
		WEG_UPDATE(MASK_weg, MASK, 0);
		wetuwn GPIO_WESUWT_OK;
	case GPIO_MODE_INTEWWUPT:
		/* Intewwupt mode suppowted onwy by HPD (IwqGpio) pins. */
		WEG_UPDATE(MASK_weg, MASK, 0);
		wetuwn GPIO_WESUWT_OK;
	defauwt:
		wetuwn GPIO_WESUWT_NON_SPECIFIC_EWWOW;
	}
}

void daw_hw_gpio_constwuct(
	stwuct hw_gpio *pin,
	enum gpio_id id,
	uint32_t en,
	stwuct dc_context *ctx)
{
	pin->base.ctx = ctx;
	pin->base.id = id;
	pin->base.en = en;
	pin->base.mode = GPIO_MODE_UNKNOWN;
	pin->base.opened = fawse;

	pin->stowe.mask = 0;
	pin->stowe.a = 0;
	pin->stowe.en = 0;
	pin->stowe.mux = 0;

	pin->mux_suppowted = fawse;
}

void daw_hw_gpio_destwuct(
	stwuct hw_gpio *pin)
{
	ASSEWT(!pin->base.opened);
}
