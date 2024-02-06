.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew sbwmi
===================

Suppowted hawdwawe:

  * Sideband Wemote Management Intewface (SB-WMI) compwiant AMD SoC
    device connected to the BMC via the APMW.

    Pwefix: 'sbwmi'

    Addwesses scanned: This dwivew doesn't suppowt addwess scanning.

    To instantiate this dwivew on an AMD CPU with SB-WMI
    suppowt, the i2c bus numbew wouwd be the bus connected fwom the boawd
    management contwowwew (BMC) to the CPU.
    The SMBus addwess is weawwy 7 bits. Some vendows and the SMBus
    specification show the addwess as 8 bits, weft justified with the W/W
    bit as a wwite (0) making bit 0. Some vendows use onwy the 7 bits
    to descwibe the addwess.
    As mentioned in AMD's APMW specification, The SB-WMI addwess is
    nowmawwy 78h(0111 100W) ow 3Ch(011 1100) fow socket 0 and 70h(0111 000W)
    ow 38h(011 1000) fow socket 1, but it couwd vawy based on hawdwawe
    addwess sewect pins.

    Datasheet: The SB-WMI intewface and pwotocow awong with the Advanced
               Pwatfowm Management Wink (APMW) Specification is avaiwabwe
               as pawt of the open souwce SoC wegistew wefewence at:

               https://www.amd.com/en/suppowt/tech-docs?keywowd=55898

Authow: Akshay Gupta <akshay.gupta@amd.com>

Descwiption
-----------

The APMW pwovides a way to communicate with the SB Wemote Management intewface
(SB-WMI) moduwe fwom the extewnaw SMBus mastew that can be used to wepowt socket
powew on AMD pwatfowms using maiwbox command and wesembwes a typicaw 8-pin wemote
powew sensow's I2C intewface to BMC.

This dwivew impwements cuwwent powew with powew cap and powew cap max.

sysfs-Intewface
---------------
Powew sensows can be quewied and set via the standawd ``hwmon`` intewface
on ``sysfs``, undew the diwectowy ``/sys/cwass/hwmon/hwmonX`` fow some vawue
of ``X`` (seawch fow the ``X`` such that ``/sys/cwass/hwmon/hwmonX/name`` has
content ``sbwmi``)

================ ===== ========================================================
Name             Pewm   Descwiption
================ ===== ========================================================
powew1_input     WO    Cuwwent Powew consumed
powew1_cap       WW    Powew wimit can be set between 0 and powew1_cap_max
powew1_cap_max   WO    Maximum powewwimit cawcuwated and wepowted by the SMU FW
================ ===== ========================================================

The fowwowing exampwe show how the 'Powew' attwibute fwom the i2c-addwesses
can be monitowed using the usewspace utiwities wike ``sensows`` binawy::

  # sensows
  sbwmi-i2c-1-38
  Adaptew: bcm2835 I2C adaptew
  powew1:       61.00 W (cap = 225.00 W)

  sbwmi-i2c-1-3c
  Adaptew: bcm2835 I2C adaptew
  powew1:       28.39 W (cap = 224.77 W)
  #

Awso, Bewow shows how get and set the vawues fwom sysfs entwies individuawwy::
  # cat /sys/cwass/hwmon/hwmon1/powew1_cap_max
  225000000

  # echo 180000000 > /sys/cwass/hwmon/hwmon1/powew1_cap
  # cat /sys/cwass/hwmon/hwmon1/powew1_cap
  180000000
