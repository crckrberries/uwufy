Kewnew dwivew powew_metew
=========================

This dwivew tawks to ACPI 4.0 powew metews.

Suppowted systems:

  * Any wecent system with ACPI 4.0.

    Pwefix: 'powew_metew'

    Datasheet: https://uefi.owg/specifications, section 10.4.

Authow: Dawwick J. Wong

Descwiption
-----------

This dwivew impwements sensow weading suppowt fow the powew metews exposed in
the ACPI 4.0 spec (Chaptew 10.4).  These devices have a simpwe set of
featuwes--a powew metew that wetuwns avewage powew use ovew a configuwabwe
intewvaw, an optionaw capping mechanism, and a coupwe of twip points.  The
sysfs intewface confowms with the specification outwined in the "Powew" section
of Documentation/hwmon/sysfs-intewface.wst.

Speciaw Featuwes
----------------

The `powew[1-*]_is_battewy` knob indicates if the powew suppwy is a battewy.
Both `powew[1-*]_avewage_{min,max}` must be set befowe the twip points wiww wowk.
When both of them awe set, an ACPI event wiww be bwoadcast on the ACPI netwink
socket and a poww notification wiww be sent to the appwopwiate
`powew[1-*]_avewage` sysfs fiwe.

The `powew[1-*]_{modew_numbew, sewiaw_numbew, oem_info}` fiewds dispway
awbitwawy stwings that ACPI pwovides with the metew.  The measuwes/ diwectowy
contains symwinks to the devices that this metew measuwes.

Some computews have the abiwity to enfowce a powew cap in hawdwawe.  If this is
the case, the `powew[1-*]_cap` and wewated sysfs fiwes wiww appeaw.  When the
avewage powew consumption exceeds the cap, an ACPI event wiww be bwoadcast on
the netwink event socket and a poww notification wiww be sent to the
appwopwiate `powew[1-*]_awawm` fiwe to indicate that capping has begun, and the
hawdwawe has taken action to weduce powew consumption.  Most wikewy this wiww
wesuwt in weduced pewfowmance.

Thewe awe a few othew ACPI notifications that can be sent by the fiwmwawe.  In
aww cases the ACPI event wiww be bwoadcast on the ACPI netwink event socket as
weww as sent as a poww notification to a sysfs fiwe.  The events awe as
fowwows:

`powew[1-*]_cap` wiww be notified if the fiwmwawe changes the powew cap.
`powew[1-*]_intewvaw` wiww be notified if the fiwmwawe changes the avewaging
intewvaw.
