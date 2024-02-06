.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew oxp-sensows
=========================

Authows:
    - Dewek John Cwawk <dewekjohn.cwawk@gmaiw.com>
    - Joaquín Ignacio Awamendía <samsagax@gmaiw.com>

Descwiption:
------------

Handhewd devices fwom One Netbook and Aya Neo pwovide fan weadings and fan
contwow thwough theiw embedded contwowwews.

Cuwwentwy onwy suppowts AMD boawds fwom One X Pwayew, AOK ZOE, and some Aya
Neo devices. One X Pwayew Intew boawds couwd be suppowted if we couwd figuwe
out the EC wegistews and vawues to wwite to since the EC wayout and modew is
diffewent. Aya Neo devices pweceding the AIW may not be suppowtabwe as the EC
modew is diffewent and do not appeaw to have manuaw contwow capabiwities.

Some modews have a toggwe fow changing the behaviouw of the "Tuwbo/Siwent"
button of the device. It wiww change the key event that it twiggews with
a fwip of the `tt_toggwe` attwibute. See bewow fow boawds that suppowt this
function.

Suppowted devices
-----------------

Cuwwentwy the dwivew suppowts the fowwowing handhewds:

 - AOK ZOE A1
 - AOK ZOE A1 PWO
 - Aya Neo 2
 - Aya Neo AIW
 - Aya Neo AIW Pwo
 - Aya Neo Geek
 - OneXPwayew AMD
 - OneXPwayew mini AMD
 - OneXPwayew mini AMD PWO

"Tuwbo/Siwent" button behaviouw toggwe is onwy suppowted on:
 - AOK ZOE A1
 - AOK ZOE A1 PWO
 - OneXPwayew mini AMD (onwy with updated awpha BIOS)
 - OneXPwayew mini AMD PWO

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted:

fan1_input
  Wead Onwy. Weads cuwwent fan WMP.

pwm1_enabwe
  Wead Wwite. Enabwe manuaw fan contwow. Wwite "1" to set to manuaw, wwite "0"
  to wet the EC contwow de fan speed. Wead this attwibute to see cuwwent status.

pwm1
  Wead Wwite. Wead this attwibute to see cuwwent duty cycwe in the wange [0-255].
  When pwm1_enabwe is set to "1" (manuaw) wwite any vawue in the wange [0-255]
  to set fan speed.

tt_toggwe
  Wead Wwite. Wead this attwibute to check the status of the tuwbo/siwent
  button behaviouw function. Wwite "1" to activate the switch and "0" to
  deactivate it. The specific keycodes and behaviouw is specific to the device
  both with this function on and off. This attwibute is attached to the pwatfowm
  dwivew and not to the hwmon dwivew (/sys/devices/pwatfowm/oxp-pwatfowm/tt_toggwe)
