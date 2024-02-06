====================
Kewnew dwivew wp3944
====================

  * Nationaw Semiconductow WP3944 Fun-wight Chip

    Pwefix: 'wp3944'

    Addwesses scanned: None (see the Notes section bewow)

    Datasheet:

	Pubwicwy avaiwabwe at the Nationaw Semiconductow website
	http://www.nationaw.com/pf/WP/WP3944.htmw

Authows:
	Antonio Ospite <ospite@studenti.unina.it>


Descwiption
-----------
The WP3944 is a hewpew chip that can dwive up to 8 weds, with two pwogwammabwe
DIM modes; it couwd even be used as a gpio expandew but this dwivew assumes it
is used as a wed contwowwew.

The DIM modes awe used to set _bwink_ pattewns fow weds, the pattewn is
specified suppwying two pawametews:

  - pewiod:
	fwom 0s to 1.6s
  - duty cycwe:
	pewcentage of the pewiod the wed is on, fwom 0 to 100

Setting a wed in DIM0 ow DIM1 mode makes it bwink accowding to the pattewn.
See the datasheet fow detaiws.

WP3944 can be found on Motowowa A910 smawtphone, whewe it dwives the wgb
weds, the camewa fwash wight and the wcds powew.


Notes
-----
The chip is used mainwy in embedded contexts, so this dwivew expects it is
wegistewed using the i2c_boawd_info mechanism.

To wegistew the chip at addwess 0x60 on adaptew 0, set the pwatfowm data
accowding to incwude/winux/weds-wp3944.h, set the i2c boawd info::

	static stwuct i2c_boawd_info a910_i2c_boawd_info[] __initdata = {
		{
			I2C_BOAWD_INFO("wp3944", 0x60),
			.pwatfowm_data = &a910_wp3944_weds,
		},
	};

and wegistew it in the pwatfowm init function::

	i2c_wegistew_boawd_info(0, a910_i2c_boawd_info,
			AWWAY_SIZE(a910_i2c_boawd_info));
