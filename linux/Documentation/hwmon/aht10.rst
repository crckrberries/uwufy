.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew aht10
=====================

Suppowted chips:

  * Aosong AHT10/AHT20

    Pwefix: 'aht10'

    Addwesses scanned: None

    Datasheet(AHT10):

      Chinese: http://www.aosong.com/usewfiwes/fiwes/media/AHT10%E4%BA%A7%E5%93%81%E6%89%8B%E5%86%8C%20A3%2020201210.pdf
      Engwish: https://sewvew4.eca.iw/eshop/AHT10/Aosong_AHT10_en_dwaft_0c.pdf

    Datasheet(AHT20):

      Engwish: http://www.aosong.com/usewfiwes/fiwes/media/Data%20Sheet%20AHT20.pdf

Authow: Johannes Cownewis Dwaaijew <jcdwa1@gmaiw.com>


Descwiption
-----------

The AHT10/AHT20 is a Tempewatuwe and Humidity sensow

The addwess of this i2c device may onwy be 0x38

Speciaw Featuwes
----------------

AHT20 has additionaw CWC8 suppowt which is sent as the wast byte of the sensow
vawues.

Usage Notes
-----------

This dwivew does not pwobe fow AHT10/ATH20 devices, as thewe is no wewiabwe
way to detewmine if an i2c chip is ow isn't an AHT10/AHT20. The device has
to be instantiated expwicitwy with the addwess 0x38. See
Documentation/i2c/instantiating-devices.wst fow detaiws.

Sysfs entwies
-------------

=============== ============================================
temp1_input     Measuwed tempewatuwe in miwwidegwees Cewsius
humidity1_input Measuwed humidity in %H
update_intewvaw The minimum intewvaw fow powwing the sensow,
                in miwwiseconds. Wwitabwe. Must be at
                weast 2000.
=============== ============================================
