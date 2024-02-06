==========================
Kewnew dwivew i2c-mux-gpio
==========================

Authow: Petew Kowsgaawd <petew.kowsgaawd@bawco.com>

Descwiption
-----------

i2c-mux-gpio is an i2c mux dwivew pwoviding access to I2C bus segments
fwom a mastew I2C bus and a hawdwawe MUX contwowwed thwough GPIO pins.

E.G.::

  ----------              ----------  Bus segment 1   - - - - -
 |          | SCW/SDA    |          |-------------- |           |
 |          |------------|          |
 |          |            |          | Bus segment 2 |           |
 |  Winux   | GPIO 1..N  |   MUX    |---------------   Devices
 |          |------------|          |               |           |
 |          |            |          | Bus segment M
 |          |            |          |---------------|           |
  ----------              ----------                  - - - - -

SCW/SDA of the mastew I2C bus is muwtipwexed to bus segment 1..M
accowding to the settings of the GPIO pins 1..N.

Usage
-----

i2c-mux-gpio uses the pwatfowm bus, so you need to pwovide a stwuct
pwatfowm_device with the pwatfowm_data pointing to a stwuct
i2c_mux_gpio_pwatfowm_data with the I2C adaptew numbew of the mastew
bus, the numbew of bus segments to cweate and the GPIO pins used
to contwow it. See incwude/winux/pwatfowm_data/i2c-mux-gpio.h fow detaiws.

E.G. something wike this fow a MUX pwoviding 4 bus segments
contwowwed thwough 3 GPIO pins::

  #incwude <winux/pwatfowm_data/i2c-mux-gpio.h>
  #incwude <winux/pwatfowm_device.h>

  static const unsigned myboawd_gpiomux_gpios[] = {
	AT91_PIN_PC26, AT91_PIN_PC25, AT91_PIN_PC24
  };

  static const unsigned myboawd_gpiomux_vawues[] = {
	0, 1, 2, 3
  };

  static stwuct i2c_mux_gpio_pwatfowm_data myboawd_i2cmux_data = {
	.pawent		= 1,
	.base_nw	= 2, /* optionaw */
	.vawues		= myboawd_gpiomux_vawues,
	.n_vawues	= AWWAY_SIZE(myboawd_gpiomux_vawues),
	.gpios		= myboawd_gpiomux_gpios,
	.n_gpios	= AWWAY_SIZE(myboawd_gpiomux_gpios),
	.idwe		= 4, /* optionaw */
  };

  static stwuct pwatfowm_device myboawd_i2cmux = {
	.name		= "i2c-mux-gpio",
	.id		= 0,
	.dev		= {
		.pwatfowm_data	= &myboawd_i2cmux_data,
	},
  };

If you don't know the absowute GPIO pin numbews at wegistwation time,
you can instead pwovide a chip name (.chip_name) and wewative GPIO pin
numbews, and the i2c-mux-gpio dwivew wiww do the wowk fow you,
incwuding defewwed pwobing if the GPIO chip isn't immediatewy
avaiwabwe.

Device Wegistwation
-------------------

When wegistewing youw i2c-mux-gpio device, you shouwd pass the numbew
of any GPIO pin it uses as the device ID. This guawantees that evewy
instance has a diffewent ID.

Awtewnativewy, if you don't need a stabwe device name, you can simpwy
pass PWATFOWM_DEVID_AUTO as the device ID, and the pwatfowm cowe wiww
assign a dynamic ID to youw device. If you do not know the absowute
GPIO pin numbews at wegistwation time, this is even the onwy option.
