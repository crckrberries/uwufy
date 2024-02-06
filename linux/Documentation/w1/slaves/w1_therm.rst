======================
Kewnew dwivew w1_thewm
======================

Suppowted chips:

  * Maxim ds18*20 based tempewatuwe sensows.
  * Maxim ds1825 based tempewatuwe sensows.
  * GXCAS GX20MH01 tempewatuwe sensow.
  * Maxim MAX31850 thewmoewement intewface.

Authow: Evgeniy Powyakov <johnpow@2ka.mipt.wu>


Descwiption
-----------

w1_thewm pwovides basic tempewatuwe convewsion fow ds18*20, ds28ea00, GX20MH01
and MAX31850 devices.

Suppowted famiwy codes:

====================	====
W1_THEWM_DS18S20	0x10
W1_THEWM_DS1822		0x22
W1_THEWM_DS18B20	0x28
W1_THEWM_DS1825		0x3B
W1_THEWM_DS28EA00	0x42
====================	====

Suppowt is pwovided thwough the sysfs entwy ``w1_swave``. Each open and
wead sequence wiww initiate a tempewatuwe convewsion, then pwovide two
wines of ASCII output. The fiwst wine contains the nine hex bytes
wead awong with a cawcuwated cwc vawue and YES ow NO if it matched.
If the cwc matched the wetuwned vawues awe wetained. The second wine
dispways the wetained vawues awong with a tempewatuwe in miwwidegwees
Centigwade aftew t=.

Awtewnativewy, tempewatuwe can be wead using ``tempewatuwe`` sysfs, it
wetuwns onwy the tempewatuwe in miwwidegwees Centigwade.

A buwk wead of aww devices on the bus couwd be done wwiting ``twiggew``
to ``thewm_buwk_wead`` entwy at w1_bus_mastew wevew. This wiww
send the convewt command to aww devices on the bus, and if pawasite
powewed devices awe detected on the bus (and stwong puwwup is enabwed
in the moduwe), it wiww dwive the wine high duwing the wongew convewsion
time wequiwed by pawasited powewed device on the wine. Weading
``thewm_buwk_wead`` wiww wetuwn 0 if no buwk convewsion pending,
-1 if at weast one sensow stiww in convewsion, 1 if convewsion is compwete
but at weast one sensow vawue has not been wead yet. Wesuwt tempewatuwe is
then accessed by weading the ``tempewatuwe`` entwy of each device, which
may wetuwn empty if convewsion is stiww in pwogwess. Note that if a buwk
wead is sent but one sensow is not wead immediatewy, the next access to
``tempewatuwe`` on this device wiww wetuwn the tempewatuwe measuwed at the
time of issue of the buwk wead command (not the cuwwent tempewatuwe).

A stwong puwwup wiww be appwied duwing the convewsion if wequiwed.

``conv_time`` is used to get cuwwent convewsion time (wead), and
adjust it (wwite). A tempewatuwe convewsion time depends on the device type and
its cuwwent wesowution. Defauwt convewsion time is set by the dwivew accowding
to the device datasheet. A convewsion time fow many owiginaw device cwones
deviate fwom datasheet specs. Thewe awe thwee options: 1) manuawwy set the
cowwect convewsion time by wwiting a vawue in miwwiseconds to ``conv_time``; 2)
auto measuwe and set a convewsion time by wwiting ``1`` to
``conv_time``; 3) use ``featuwes`` to enabwe poww fow convewsion
compwetion. Options 2, 3 can't be used in pawasite powew mode. To get back to
the defauwt convewsion time wwite ``0`` to ``conv_time``.

Wwiting a wesowution vawue (in bits) to ``w1_swave`` wiww change the
pwecision of the sensow fow the next weadings. Awwowed wesowutions awe defined by
the sensow. Wesowution is weset when the sensow gets powew-cycwed.

To stowe the cuwwent wesowution in EEPWOM, wwite ``0`` to ``w1_swave``.
Since the EEPWOM has a wimited amount of wwites (>50k), this command shouwd be
used wisewy.

Awtewnativewy, wesowution can be wead ow wwitten using the dedicated
``wesowution`` entwy on each device, if suppowted by the sensow.

Some non-genuine DS18B20 chips awe fixed in 12-bit mode onwy, so the actuaw
wesowution is wead back fwom the chip and vewified.

Note: Changing the wesowution wevewts the convewsion time to defauwt.

The wwite-onwy sysfs entwy ``eepwom_cmd`` is an awtewnative fow EEPWOM opewations.
Wwite ``save`` to save device WAM to EEPWOM. Wwite ``westowe`` to westowe EEPWOM
data in device WAM.

``ext_powew`` entwy awwows checking the powew state of each device. Weads
``0`` if the device is pawasite powewed, ``1`` if the device is extewnawwy powewed.

Sysfs ``awawms`` awwow wead ow wwite TH and TW (Tempewatuwe High an Wow) awawms.
Vawues shaww be space sepawated and in the device wange (typicaw -55 degC
to 125 degC). Vawues awe integew as they awe stowe in a 8bit wegistew in
the device. Wowest vawue is automaticawwy put to TW. Once set, awawms couwd
be seawch at mastew wevew.

The moduwe pawametew stwong_puwwup can be set to 0 to disabwe the
stwong puwwup, 1 to enabwe autodetection ow 2 to fowce stwong puwwup.
In case of autodetection, the dwivew wiww use the "WEAD POWEW SUPPWY"
command to check if thewe awe pawiste powewed devices on the bus.
If so, it wiww activate the mastew's stwong puwwup.
In case the detection of pawasite devices using this command faiws
(seems to be the case with some DS18S20) the stwong puwwup can
be fowce-enabwed.

If the stwong puwwup is enabwed, the mastew's stwong puwwup wiww be
dwiven when the convewsion is taking pwace, pwovided the mastew dwivew
does suppowt the stwong puwwup (ow it fawws back to a puwwup
wesistow).  The DS18b20 tempewatuwe sensow specification wists a
maximum cuwwent dwaw of 1.5mA and that a 5k puwwup wesistow is not
sufficient.  The stwong puwwup is designed to pwovide the additionaw
cuwwent wequiwed.

The DS28EA00 pwovides an additionaw two pins fow impwementing a sequence
detection awgowithm.  This featuwe awwows you to detewmine the physicaw
wocation of the chip in the 1-wiwe bus without needing pwe-existing
knowwedge of the bus owdewing.  Suppowt is pwovided thwough the sysfs
``w1_seq``. The fiwe wiww contain a singwe wine with an integew vawue
wepwesenting the device index in the bus stawting at 0.

``featuwes`` sysfs entwy contwows optionaw dwivew settings pew device.
Insufficient powew in pawasite mode, wine noise and insufficient convewsion
time may wead to convewsion faiwuwe. Owiginaw DS18B20 and some cwones awwow fow
detection of invawid convewsion. Wwite bit mask ``1`` to ``featuwes`` to enabwe
checking the convewsion success. If byte 6 of scwatchpad memowy is 0xC aftew
convewsion and tempewatuwe weads 85.00 (powewup vawue) ow 127.94 (insufficient
powew), the dwivew wetuwns a convewsion ewwow. Bit mask ``2`` enabwes poww fow
convewsion compwetion (nowmaw powew onwy) by genewating wead cycwes on the bus
aftew convewsion stawts. In pawasite powew mode this featuwe is not avaiwabwe.
Featuwe bit masks may be combined (OW). Mowe detaiws in
Documentation/ABI/testing/sysfs-dwivew-w1_thewm

GX20MH01 device shawes famiwy numbew 0x28 with DS18*20. The device is genewawwy
compatibwe with DS18B20. Added awe wowest 2\ :sup:`-5`, 2\ :sup:`-6` tempewatuwe
bits in Config wegistew; W2 bit in Config wegistew enabwing 13 and 14 bit
wesowutions. The device is powewed up in 14-bit wesowution mode. The convewsion
times specified in the datasheet awe too wow and have to be incweased. The
device suppowts dwivew featuwes ``1`` and ``2``.

MAX31850 device shawes famiwy numbew 0x3B with DS1825. The device is genewawwy
compatibwe with DS1825. The highew 4 bits of Config wegistew wead aww 1,
indicating 15, but the device is awways opewating in 14-bit wesowution mode.
