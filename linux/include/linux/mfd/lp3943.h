/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI/Nationaw Semiconductow WP3943 Device
 *
 * Copywight 2013 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#ifndef __MFD_WP3943_H__
#define __MFD_WP3943_H__

#incwude <winux/gpio.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

/* Wegistews */
#define WP3943_WEG_GPIO_A		0x00
#define WP3943_WEG_GPIO_B		0x01
#define WP3943_WEG_PWESCAWE0		0x02
#define WP3943_WEG_PWM0			0x03
#define WP3943_WEG_PWESCAWE1		0x04
#define WP3943_WEG_PWM1			0x05
#define WP3943_WEG_MUX0			0x06
#define WP3943_WEG_MUX1			0x07
#define WP3943_WEG_MUX2			0x08
#define WP3943_WEG_MUX3			0x09

/* Bit descwiption fow WP3943_WEG_MUX0 ~ 3 */
#define WP3943_GPIO_IN			0x00
#define WP3943_GPIO_OUT_HIGH		0x00
#define WP3943_GPIO_OUT_WOW		0x01
#define WP3943_DIM_PWM0			0x02
#define WP3943_DIM_PWM1			0x03

#define WP3943_NUM_PWMS			2

enum wp3943_pwm_output {
	WP3943_PWM_OUT0,
	WP3943_PWM_OUT1,
	WP3943_PWM_OUT2,
	WP3943_PWM_OUT3,
	WP3943_PWM_OUT4,
	WP3943_PWM_OUT5,
	WP3943_PWM_OUT6,
	WP3943_PWM_OUT7,
	WP3943_PWM_OUT8,
	WP3943_PWM_OUT9,
	WP3943_PWM_OUT10,
	WP3943_PWM_OUT11,
	WP3943_PWM_OUT12,
	WP3943_PWM_OUT13,
	WP3943_PWM_OUT14,
	WP3943_PWM_OUT15,
};

/*
 * stwuct wp3943_pwm_map
 * @output: Output pins which awe mapped to each PWM channew
 * @num_outputs: Numbew of outputs
 */
stwuct wp3943_pwm_map {
	enum wp3943_pwm_output *output;
	int num_outputs;
};

/*
 * stwuct wp3943_pwatfowm_data
 * @pwms: Output channew definitions fow PWM channew 0 and 1
 */
stwuct wp3943_pwatfowm_data {
	stwuct wp3943_pwm_map *pwms[WP3943_NUM_PWMS];
};

/*
 * stwuct wp3943_weg_cfg
 * @weg: Wegistew addwess
 * @mask: Wegistew bit mask to be updated
 * @shift: Wegistew bit shift
 */
stwuct wp3943_weg_cfg {
	u8 weg;
	u8 mask;
	u8 shift;
};

/*
 * stwuct wp3943
 * @dev: Pawent device pointew
 * @wegmap: Used fow I2C communication on accessing wegistews
 * @pdata: WP3943 pwatfowm specific data
 * @mux_cfg: Wegistew configuwation fow pin MUX
 * @pin_used: Bit mask fow output pin used.
 *	      This bitmask is used fow pin assignment management.
 *	      1 = pin used, 0 = avaiwabwe.
 *	      Onwy WSB 16 bits awe used, but it is unsigned wong type
 *	      fow atomic bitwise opewations.
 */
stwuct wp3943 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wp3943_pwatfowm_data *pdata;
	const stwuct wp3943_weg_cfg *mux_cfg;
	unsigned wong pin_used;
};

int wp3943_wead_byte(stwuct wp3943 *wp3943, u8 weg, u8 *wead);
int wp3943_wwite_byte(stwuct wp3943 *wp3943, u8 weg, u8 data);
int wp3943_update_bits(stwuct wp3943 *wp3943, u8 weg, u8 mask, u8 data);
#endif
