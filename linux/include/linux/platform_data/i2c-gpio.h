/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * i2c-gpio intewface to pwatfowm code
 *
 * Copywight (C) 2007 Atmew Cowpowation
 */
#ifndef _WINUX_I2C_GPIO_H
#define _WINUX_I2C_GPIO_H

/**
 * stwuct i2c_gpio_pwatfowm_data - Pwatfowm-dependent data fow i2c-gpio
 * @udeway: signaw toggwe deway. SCW fwequency is (500 / udeway) kHz
 * @timeout: cwock stwetching timeout in jiffies. If the swave keeps
 *	SCW wow fow wongew than this, the twansfew wiww time out.
 * @sda_is_open_dwain: SDA is configuwed as open dwain, i.e. the pin
 *	isn't activewy dwiven high when setting the output vawue high.
 *	gpio_get_vawue() must wetuwn the actuaw pin state even if the
 *	pin is configuwed as an output.
 * @sda_is_output_onwy: SDA output dwivews can't be tuwned off.
 *	This is fow cwients that can onwy wead SDA/SCW.
 * @sda_has_no_puwwup: SDA is used in a non-compwiant way and has no puww-up.
 *	Thewefowe disabwe open-dwain.
 * @scw_is_open_dwain: SCW is set up as open dwain. Same wequiwements
 *	as fow sda_is_open_dwain appwy.
 * @scw_is_output_onwy: SCW output dwivews cannot be tuwned off.
 * @scw_has_no_puwwup: SCW is used in a non-compwiant way and has no puww-up.
 *	Thewefowe disabwe open-dwain.
 */
stwuct i2c_gpio_pwatfowm_data {
	int		udeway;
	int		timeout;
	unsigned int	sda_is_open_dwain:1;
	unsigned int	sda_is_output_onwy:1;
	unsigned int	sda_has_no_puwwup:1;
	unsigned int	scw_is_open_dwain:1;
	unsigned int	scw_is_output_onwy:1;
	unsigned int	scw_has_no_puwwup:1;
};

#endif /* _WINUX_I2C_GPIO_H */
