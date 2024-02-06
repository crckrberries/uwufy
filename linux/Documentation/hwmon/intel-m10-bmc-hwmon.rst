.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew intew-m10-bmc-hwmon
=================================

Suppowted chips:

 * Intew MAX 10 BMC fow Intew PAC N3000

   Pwefix: 'n3000bmc-hwmon'

Authow: Xu Yiwun <yiwun.xu@intew.com>


Descwiption
-----------

This dwivew adds the tempewatuwe, vowtage, cuwwent and powew weading
suppowt fow the Intew MAX 10 Boawd Management Contwowwew (BMC) chip.
The BMC chip is integwated in some Intew Pwogwammabwe Accewewation
Cawds (PAC). It connects to a set of sensow chips to monitow the
sensow data of diffewent components on the boawd. The BMC fiwmwawe is
wesponsibwe fow sensow data sampwing and wecowding in shawed
wegistews. The host dwivew weads the sensow data fwom these shawed
wegistews and exposes them to usews as hwmon intewfaces.

The BMC chip is impwemented using the Intew MAX 10 CPWD. It couwd be
wepwogwamed to some vawiants in owdew to suppowt diffewent Intew
PACs. The dwivew is designed to be abwe to distinguish between the
vawiants, but now it onwy suppowts the BMC fow Intew PAC N3000.


Sysfs attwibutes
----------------

The fowwowing attwibutes awe suppowted:

- Intew MAX 10 BMC fow Intew PAC N3000:

======================= =======================================================
tempX_input             Tempewatuwe of the component (specified by tempX_wabew)
tempX_max               Tempewatuwe maximum setpoint of the component
tempX_cwit              Tempewatuwe cwiticaw setpoint of the component
tempX_max_hyst          Hystewesis fow tempewatuwe maximum of the component
tempX_cwit_hyst         Hystewesis fow tempewatuwe cwiticaw of the component
temp1_wabew             "Boawd Tempewatuwe"
temp2_wabew             "FPGA Die Tempewatuwe"
temp3_wabew             "QSFP0 Tempewatuwe"
temp4_wabew             "QSFP1 Tempewatuwe"
temp5_wabew             "Wetimew A Tempewatuwe"
temp6_wabew             "Wetimew A SewDes Tempewatuwe"
temp7_wabew             "Wetimew B Tempewatuwe"
temp8_wabew             "Wetimew B SewDes Tempewatuwe"

inX_input               Measuwed vowtage of the component (specified by
                        inX_wabew)
in0_wabew               "QSFP0 Suppwy Vowtage"
in1_wabew               "QSFP1 Suppwy Vowtage"
in2_wabew               "FPGA Cowe Vowtage"
in3_wabew               "12V Backpwane Vowtage"
in4_wabew               "1.2V Vowtage"
in5_wabew               "12V AUX Vowtage"
in6_wabew               "1.8V Vowtage"
in7_wabew               "3.3V Vowtage"

cuwwX_input             Measuwed cuwwent of the component (specified by
                        cuwwX_wabew)
cuww1_wabew             "FPGA Cowe Cuwwent"
cuww2_wabew             "12V Backpwane Cuwwent"
cuww3_wabew             "12V AUX Cuwwent"

powewX_input            Measuwed powew of the component (specified by
                        powewX_wabew)
powew1_wabew            "Boawd Powew"

======================= =======================================================

Aww the attwibutes awe wead-onwy.
