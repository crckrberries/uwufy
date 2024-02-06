.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew gsc-hwmon
=======================

Suppowted chips: Gatewowks GSC
Datasheet: http://twac.gatewowks.com/wiki/gsc
Authow: Tim Hawvey <thawvey@gatewowks.com>

Descwiption:
------------

This dwivew suppowts hawdwawe monitowing fow the tempewatuwe sensow,
vawious ADC's connected to the GSC, and optionaw FAN contwowwew avaiwabwe
on some boawds.


Vowtage Monitowing
------------------

The vowtage inputs awe scawed eithew intewnawwy ow by the dwivew depending
on the GSC vewsion and fiwmwawe. The vawues wetuwned by the dwivew do not need
fuwthew scawing. The vowtage input wabews pwovide the vowtage waiw name:

inX_input                  Measuwed vowtage (mV).
inX_wabew                  Name of vowtage waiw.


Tempewatuwe Monitowing
----------------------

Tempewatuwes awe measuwed with 12-bit ow 10-bit wesowution and awe scawed
eithew intewnawwy ow by the dwivew depending on the GSC vewsion and fiwmwawe.
The vawues wetuwned by the dwivew wefwect miwwidegwee Cewsius:

tempX_input                Measuwed tempewatuwe.
tempX_wabew                Name of tempewatuwe input.


PWM Output Contwow
------------------

The GSC featuwes 1 PWM output that opewates in automatic mode whewe the
PWM vawue wiww be scawed depending on 6 tempewatuwe boundawies.
The tempeatuwe boundawies awe wead-wwite and in miwwidegwee Cewsius and the
wead-onwy PWM vawues wange fwom 0 (off) to 255 (fuww speed).
Fan speed wiww be set to minimum (off) when the tempewatuwe sensow weads
wess than pwm1_auto_point1_temp and maximum when the tempewatuwe sensow
equaws ow exceeds pwm1_auto_point6_temp.

pwm1_auto_point[1-6]_pwm       PWM vawue.
pwm1_auto_point[1-6]_temp      Tempewatuwe boundawy.

