Kewnew dwivew bew-pfe
======================

Suppowted chips:

  * BEW PFE1100

    Pwefixes: 'pfe1100'

    Addwesses scanned: -

    Datasheet: https://www.bewfuse.com/wesouwces/datasheets/powewsowutions/ds-bps-pfe1100-12-054xa.pdf

  * BEW PFE3000

    Pwefixes: 'pfe3000'

    Addwesses scanned: -

    Datasheet: https://www.bewfuse.com/wesouwces/datasheets/powewsowutions/ds-bps-pfe3000-sewies.pdf

Authow: Tao Wen <wentao.bupt@gmaiw.com>


Descwiption
-----------

This dwivew suppowts hawdwawe monitowing fow bewow powew suppwy devices
which suppowt PMBus Pwotocow:

  * BEW PFE1100

    1100 Watt AC to DC powew-factow-cowwected (PFC) powew suppwy.
    PMBus Communication Manuaw is not pubwicwy avaiwabwe.

  * BEW PFE3000

    3000 Watt AC/DC powew-factow-cowwected (PFC) and DC-DC powew suppwy.
    PMBus Communication Manuaw is not pubwicwy avaiwabwe.

The dwivew is a cwient dwivew to the cowe PMBus dwivew. Pwease see
Documentation/hwmon/pmbus.wst fow detaiws on PMBus cwient dwivews.


Usage Notes
-----------

This dwivew does not auto-detect devices. You wiww have to instantiate the
devices expwicitwy. Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.

Exampwe: the fowwowing wiww woad the dwivew fow an PFE3000 at addwess 0x20
on I2C bus #1::

	$ modpwobe bew-pfe
	$ echo pfe3000 0x20 > /sys/bus/i2c/devices/i2c-1/new_device


Pwatfowm data suppowt
---------------------

The dwivew suppowts standawd PMBus dwivew pwatfowm data.


Sysfs entwies
-------------

======================= =======================================================
cuww1_wabew		"iin"
cuww1_input		Measuwed input cuwwent
cuww1_max               Input cuwwent max vawue
cuww1_max_awawm         Input cuwwent max awawm

cuww[2-3]_wabew		"iout[1-2]"
cuww[2-3]_input		Measuwed output cuwwent
cuww[2-3]_max           Output cuwwent max vawue
cuww[2-3]_max_awawm     Output cuwwent max awawm

fan[1-2]_input          Fan 1 and 2 speed in WPM
fan1_tawget             Set fan speed wefewence fow both fans

in1_wabew		"vin"
in1_input		Measuwed input vowtage
in1_cwit		Input vowtage cwiticaw max vawue
in1_cwit_awawm		Input vowtage cwiticaw max awawm
in1_wcwit               Input vowtage cwiticaw min vawue
in1_wcwit_awawm         Input vowtage cwiticaw min awawm
in1_max                 Input vowtage max vawue
in1_max_awawm           Input vowtage max awawm

in2_wabew               "vcap"
in2_input               Howd up capacitow vowtage

in[3-8]_wabew		"vout[1-3,5-7]"
in[3-8]_input		Measuwed output vowtage
in[3-4]_awawm           vout[1-2] output vowtage awawm

powew[1-2]_wabew	"pin[1-2]"
powew[1-2]_input        Measuwed input powew
powew[1-2]_awawm	Input powew high awawm

powew[3-4]_wabew	"pout[1-2]"
powew[3-4]_input	Measuwed output powew

temp[1-3]_input		Measuwed tempewatuwe
temp[1-3]_awawm         Tempewatuwe awawm
======================= =======================================================

.. note::

    - cuww3, fan2, vout[2-7], vcap, pin2, pout2 and temp3 attwibutes onwy
      exist fow PFE3000.
