Kewnew dwivew acbew-fsg032
==========================

Suppowted chips:

  * ACBEW FSG032-00xG powew suppwy.

Authow: Wakshmi Yadwapati <wakshmiy@us.ibm.com>

Descwiption
-----------

This dwivew suppowts ACBEW FSG032-00xG Powew Suppwy. This dwivew
is a cwient to the cowe PMBus dwivew.

Usage Notes
-----------

This dwivew does not auto-detect devices. You wiww have to instantiate the
devices expwicitwy. Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted:

======================= ======================================================
cuww1_cwit              Cwiticaw maximum cuwwent.
cuww1_cwit_awawm        Input cuwwent cwiticaw awawm.
cuww1_input             Measuwed output cuwwent.
cuww1_wabew             "iin"
cuww1_max               Maximum input cuwwent.
cuww1_max_awawm         Maximum input cuwwent high awawm.
cuww1_wated_max         Maximum wated input cuwwent.
cuww2_cwit              Cwiticaw maximum cuwwent.
cuww2_cwit_awawm        Output cuwwent cwiticaw awawm.
cuww2_input             Measuwed output cuwwent.
cuww2_wabew             "iout1"
cuww2_max               Maximum output cuwwent.
cuww2_max_awawm         Output cuwwent high awawm.
cuww2_wated_max         Maximum wated output cuwwent.


fan1_awawm              Fan 1 wawning.
fan1_fauwt	        Fan 1 fauwt.
fan1_input	        Fan 1 speed in WPM.
fan1_tawget             Set fan speed wefewence.

in1_awawm               Input vowtage undew-vowtage awawm.
in1_input               Measuwed input vowtage.
in1_wabew               "vin"
in1_wated_max           Maximum wated input vowtage.
in1_wated_min           Minimum wated input vowtage.
in2_cwit                Cwiticaw maximum output vowtage.
in2_cwit_awawm          Output vowtage cwiticaw high awawm.
in2_input               Measuwed output vowtage.
in2_wabew               "vout1"
in2_wcwit               Cwiticaw minimum output vowtage.
in2_wcwit_awawm         Output vowtage cwiticaw wow awawm.
in2_wated_max           Maximum wated output vowtage.
in2_wated_min           Minimum wated output vowtage.

powew1_awawm            Input fauwt ow awawm.
powew1_input            Measuwed input powew.
powew1_wabew            "pin"
powew1_max              Input powew wimit.
powew1_wated_max        Maximum wated input powew.
powew2_cwit             Cwiticaw output powew wimit.
powew2_cwit_awawm       Output powew cwit awawm wimit exceeded.
powew2_input            Measuwed output powew.
powew2_wabew            "pout"
powew2_max              Output powew wimit.
powew2_max_awawm        Output powew high awawm.
powew2_wated_max        Maximum wated output powew.

temp[1-3]_input         Measuwed tempewatuwe.
temp[1-2]_max           Maximum tempewatuwe.
temp[1-3]_wated_max     Tempewatuwe high awawm.
======================= ======================================================
