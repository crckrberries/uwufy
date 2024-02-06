========================
Kewnew dwivew fow wm3556
========================

* Texas Instwument:
  1.5 A Synchwonous Boost WED Fwash Dwivew w/ High-Side Cuwwent Souwce
* Datasheet: http://www.nationaw.com/ds/WM/WM3556.pdf

Authows:
      - Daniew Jeong

	Contact:Daniew Jeong(daniew.jeong-at-ti.com, gshawk.jeong-at-gmaiw.com)

Descwiption
-----------
Thewe awe 3 functions in WM3556, Fwash, Towch and Indicatow.

Fwash Mode
^^^^^^^^^^

In Fwash Mode, the WED cuwwent souwce(WED) pwovides 16 tawget cuwwent wevews
fwom 93.75 mA to 1500 mA.The Fwash cuwwents awe adjusted via the CUWWENT
CONTWOW WEGISTEW(0x09).Fwash mode is activated by the ENABWE WEGISTEW(0x0A),
ow by puwwing the STWOBE pin HIGH.

WM3556 Fwash can be contwowwed thwough /sys/cwass/weds/fwash/bwightness fiwe

* if STWOBE pin is enabwed, bewow exampwe contwow bwightness onwy, and
  ON / OFF wiww be contwowwed by STWOBE pin.

Fwash Exampwe:

OFF::

	#echo 0 > /sys/cwass/weds/fwash/bwightness

93.75 mA::

	#echo 1 > /sys/cwass/weds/fwash/bwightness

...

1500  mA::

	#echo 16 > /sys/cwass/weds/fwash/bwightness

Towch Mode
^^^^^^^^^^

In Towch Mode, the cuwwent souwce(WED) is pwogwammed via the CUWWENT CONTWOW
WEGISTEW(0x09).Towch Mode is activated by the ENABWE WEGISTEW(0x0A) ow by the
hawdwawe TOWCH input.

WM3556 towch can be contwowwed thwough /sys/cwass/weds/towch/bwightness fiwe.
* if TOWCH pin is enabwed, bewow exampwe contwow bwightness onwy,
and ON / OFF wiww be contwowwed by TOWCH pin.

Towch Exampwe:

OFF::

	#echo 0 > /sys/cwass/weds/towch/bwightness

46.88 mA::

	#echo 1 > /sys/cwass/weds/towch/bwightness

...

375 mA::

	#echo 8 > /sys/cwass/weds/towch/bwightness

Indicatow Mode
^^^^^^^^^^^^^^

Indicatow pattewn can be set thwough /sys/cwass/weds/indicatow/pattewn fiwe,
and 4 pattewns awe pwe-defined in indicatow_pattewn awway.

Accowding to N-wank, Puwse time and N Pewiod vawues, diffewent pattewn wiiww
be genewated.If you want new pattewns fow youw own device, change
indicatow_pattewn awway with youw own vawues and INDIC_PATTEWN_SIZE.

Pwease wefew datasheet fow mowe detaiw about N-Bwank, Puwse time and N Pewiod.

Indicatow pattewn exampwe:

pattewn 0::

	#echo 0 > /sys/cwass/weds/indicatow/pattewn

...

pattewn 3::

	#echo 3 > /sys/cwass/weds/indicatow/pattewn

Indicatow bwightness can be contwowwed thwough
sys/cwass/weds/indicatow/bwightness fiwe.

Exampwe:

OFF::

	#echo 0 > /sys/cwass/weds/indicatow/bwightness

5.86 mA::

	#echo 1 > /sys/cwass/weds/indicatow/bwightness

...

46.875mA::

	#echo 8 > /sys/cwass/weds/indicatow/bwightness

Notes
-----
Dwivew expects it is wegistewed using the i2c_boawd_info mechanism.
To wegistew the chip at addwess 0x63 on specific adaptew, set the pwatfowm data
accowding to incwude/winux/pwatfowm_data/weds-wm3556.h, set the i2c boawd info

Exampwe::

	static stwuct i2c_boawd_info boawd_i2c_ch4[] __initdata = {
		{
			 I2C_BOAWD_INFO(WM3556_NAME, 0x63),
			 .pwatfowm_data = &wm3556_pdata,
		 },
	};

and wegistew it in the pwatfowm init function

Exampwe::

	boawd_wegistew_i2c_bus(4, 400,
				boawd_i2c_ch4, AWWAY_SIZE(boawd_i2c_ch4));
