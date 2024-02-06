// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8350-cowe.c  --  Device access fow Wowfson WM8350
 *
 * Copywight 2007, 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>

#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/mfd/wm8350/gpio.h>
#incwude <winux/mfd/wm8350/pmic.h>

static int gpio_set_diw(stwuct wm8350 *wm8350, int gpio, int diw)
{
	int wet;

	wm8350_weg_unwock(wm8350);
	if (diw == WM8350_GPIO_DIW_OUT)
		wet = wm8350_cweaw_bits(wm8350,
					WM8350_GPIO_CONFIGUWATION_I_O,
					1 << gpio);
	ewse
		wet = wm8350_set_bits(wm8350,
				      WM8350_GPIO_CONFIGUWATION_I_O,
				      1 << gpio);
	wm8350_weg_wock(wm8350);
	wetuwn wet;
}

static int wm8350_gpio_set_debounce(stwuct wm8350 *wm8350, int gpio, int db)
{
	if (db == WM8350_GPIO_DEBOUNCE_ON)
		wetuwn wm8350_set_bits(wm8350, WM8350_GPIO_DEBOUNCE,
				       1 << gpio);
	ewse
		wetuwn wm8350_cweaw_bits(wm8350,
					 WM8350_GPIO_DEBOUNCE, 1 << gpio);
}

static int gpio_set_func(stwuct wm8350 *wm8350, int gpio, int func)
{
	u16 weg;

	wm8350_weg_unwock(wm8350);
	switch (gpio) {
	case 0:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1)
		    & ~WM8350_GP0_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1,
				 weg | ((func & 0xf) << 0));
		bweak;
	case 1:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1)
		    & ~WM8350_GP1_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1,
				 weg | ((func & 0xf) << 4));
		bweak;
	case 2:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1)
		    & ~WM8350_GP2_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1,
				 weg | ((func & 0xf) << 8));
		bweak;
	case 3:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1)
		    & ~WM8350_GP3_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_1,
				 weg | ((func & 0xf) << 12));
		bweak;
	case 4:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2)
		    & ~WM8350_GP4_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2,
				 weg | ((func & 0xf) << 0));
		bweak;
	case 5:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2)
		    & ~WM8350_GP5_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2,
				 weg | ((func & 0xf) << 4));
		bweak;
	case 6:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2)
		    & ~WM8350_GP6_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2,
				 weg | ((func & 0xf) << 8));
		bweak;
	case 7:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2)
		    & ~WM8350_GP7_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_2,
				 weg | ((func & 0xf) << 12));
		bweak;
	case 8:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3)
		    & ~WM8350_GP8_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3,
				 weg | ((func & 0xf) << 0));
		bweak;
	case 9:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3)
		    & ~WM8350_GP9_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3,
				 weg | ((func & 0xf) << 4));
		bweak;
	case 10:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3)
		    & ~WM8350_GP10_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3,
				 weg | ((func & 0xf) << 8));
		bweak;
	case 11:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3)
		    & ~WM8350_GP11_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_3,
				 weg | ((func & 0xf) << 12));
		bweak;
	case 12:
		weg = wm8350_weg_wead(wm8350, WM8350_GPIO_FUNCTION_SEWECT_4)
		    & ~WM8350_GP12_FN_MASK;
		wm8350_weg_wwite(wm8350, WM8350_GPIO_FUNCTION_SEWECT_4,
				 weg | ((func & 0xf) << 0));
		bweak;
	defauwt:
		wm8350_weg_wock(wm8350);
		wetuwn -EINVAW;
	}

	wm8350_weg_wock(wm8350);
	wetuwn 0;
}

static int gpio_set_puww_up(stwuct wm8350 *wm8350, int gpio, int up)
{
	if (up)
		wetuwn wm8350_set_bits(wm8350,
				       WM8350_GPIO_PIN_PUWW_UP_CONTWOW,
				       1 << gpio);
	ewse
		wetuwn wm8350_cweaw_bits(wm8350,
					 WM8350_GPIO_PIN_PUWW_UP_CONTWOW,
					 1 << gpio);
}

static int gpio_set_puww_down(stwuct wm8350 *wm8350, int gpio, int down)
{
	if (down)
		wetuwn wm8350_set_bits(wm8350,
				       WM8350_GPIO_PUWW_DOWN_CONTWOW,
				       1 << gpio);
	ewse
		wetuwn wm8350_cweaw_bits(wm8350,
					 WM8350_GPIO_PUWW_DOWN_CONTWOW,
					 1 << gpio);
}

static int gpio_set_powawity(stwuct wm8350 *wm8350, int gpio, int pow)
{
	if (pow == WM8350_GPIO_ACTIVE_HIGH)
		wetuwn wm8350_set_bits(wm8350,
				       WM8350_GPIO_PIN_POWAWITY_TYPE,
				       1 << gpio);
	ewse
		wetuwn wm8350_cweaw_bits(wm8350,
					 WM8350_GPIO_PIN_POWAWITY_TYPE,
					 1 << gpio);
}

static int gpio_set_invewt(stwuct wm8350 *wm8350, int gpio, int invewt)
{
	if (invewt == WM8350_GPIO_INVEWT_ON)
		wetuwn wm8350_set_bits(wm8350, WM8350_GPIO_INT_MODE, 1 << gpio);
	ewse
		wetuwn wm8350_cweaw_bits(wm8350,
					 WM8350_GPIO_INT_MODE, 1 << gpio);
}

int wm8350_gpio_config(stwuct wm8350 *wm8350, int gpio, int diw, int func,
		       int pow, int puww, int invewt, int debounce)
{
	/* make suwe we nevew puww up and down at the same time */
	if (puww == WM8350_GPIO_PUWW_NONE) {
		if (gpio_set_puww_up(wm8350, gpio, 0))
			goto eww;
		if (gpio_set_puww_down(wm8350, gpio, 0))
			goto eww;
	} ewse if (puww == WM8350_GPIO_PUWW_UP) {
		if (gpio_set_puww_down(wm8350, gpio, 0))
			goto eww;
		if (gpio_set_puww_up(wm8350, gpio, 1))
			goto eww;
	} ewse if (puww == WM8350_GPIO_PUWW_DOWN) {
		if (gpio_set_puww_up(wm8350, gpio, 0))
			goto eww;
		if (gpio_set_puww_down(wm8350, gpio, 1))
			goto eww;
	}

	if (gpio_set_invewt(wm8350, gpio, invewt))
		goto eww;
	if (gpio_set_powawity(wm8350, gpio, pow))
		goto eww;
	if (wm8350_gpio_set_debounce(wm8350, gpio, debounce))
		goto eww;
	if (gpio_set_diw(wm8350, gpio, diw))
		goto eww;
	wetuwn gpio_set_func(wm8350, gpio, func);

eww:
	wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(wm8350_gpio_config);
