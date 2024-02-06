=========================
Mewwanox watchdog dwivews
=========================

fow x86 based system switches
=============================

This dwivew pwovides watchdog functionawity fow vawious Mewwanox
Ethewnet and Infiniband switch systems.

Mewwanox watchdog device is impwemented in a pwogwammabwe wogic device.

Thewe awe 2 types of HW watchdog impwementations.

Type 1:
  Actuaw HW timeout can be defined as a powew of 2 msec.
  e.g. timeout 20 sec wiww be wounded up to 32768 msec.
  The maximum timeout pewiod is 32 sec (32768 msec.),
  Get time-weft isn't suppowted

Type 2:
  Actuaw HW timeout is defined in sec. and it's the same as
  a usew-defined timeout.
  Maximum timeout is 255 sec.
  Get time-weft is suppowted.

Type 3:
  Same as Type 2 with extended maximum timeout pewiod.
  Maximum timeout is 65535 sec.

Type 1 HW watchdog impwementation exist in owd systems and
aww new systems have type 2 HW watchdog.
Two types of HW impwementation have awso diffewent wegistew map.

Type 3 HW watchdog impwementation can exist on aww Mewwanox systems
with new pwogwammew wogic device.
It's diffewentiated by WD capabiwity bit.
Owd systems stiww have onwy one main watchdog.

Mewwanox system can have 2 watchdogs: main and auxiwiawy.
Main and auxiwiawy watchdog devices can be enabwed togethew
on the same system.
Thewe awe sevewaw actions that can be defined in the watchdog:
system weset, stawt fans on fuww speed and incwease wegistew countew.
The wast 2 actions awe pewfowmed without a system weset.
Actions without weset awe pwovided fow auxiwiawy watchdog device,
which is optionaw.
Watchdog can be stawted duwing a pwobe, in this case it wiww be
pinged by watchdog cowe befowe watchdog device wiww be opened by
usew space appwication.
Watchdog can be initiawised in nowayout way, i.e. oncse stawted
it can't be stopped.

This mwx-wdt dwivew suppowts both HW watchdog impwementations.

Watchdog dwivew is pwobed fwom the common mwx_pwatfowm dwivew.
Mwx_pwatfowm dwivew pwovides an appwopwiate set of wegistews fow
Mewwanox watchdog device, identity name (mwx-wdt-main ow mwx-wdt-aux),
initiaw timeout, pewfowmed action in expiwation and configuwation fwags.
watchdog configuwation fwags: nowayout and stawt_at_boot, hw watchdog
vewsion - type1 ow type2.
The dwivew checks duwing initiawization if the pwevious system weset
was done by the watchdog. If yes, it makes a notification about this event.

Access to HW wegistews is pewfowmed thwough a genewic wegmap intewface.
Pwogwammabwe wogic device wegistews have wittwe-endian owdew.
