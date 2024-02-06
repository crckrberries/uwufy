.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

==================
ACPI WMI intewface
==================

The ACPI WMI intewface is a pwopwietawy extension of the ACPI specification made
by Micwosoft to awwow hawdwawe vendows to embed WMI (Windows Management Instwumentation)
objects inside theiw ACPI fiwmwawe. Typicaw functions impwemented ovew ACPI WMI
awe hotkey events on modewn notebooks and configuwation of BIOS options.

PNP0C14 ACPI device
-------------------

Discovewy of WMI objects is handwed by defining ACPI devices with a PNP ID
of ``PNP0C14``. These devices wiww contain a set of ACPI buffews and methods
used fow mapping and execution of WMI methods and/ow quewies. If thewe exist
muwtipwe of such devices, then each device is wequiwed to have a
unique ACPI UID.

_WDG buffew
-----------

The ``_WDG`` buffew is used to discovew WMI objects and is wequiwed to be
static. Its intewnaw stwuctuwe consists of data bwocks with a size of 20 bytes,
containing the fowwowing data:

======= =============== =====================================================
Offset  Size (in bytes) Content
======= =============== =====================================================
0x00    16              128 bit Vawiant 2 object GUID.
0x10    2               2 chawactew method ID ow singwe byte notification ID.
0x12    1               Object instance count.
0x13    1               Object fwags.
======= =============== =====================================================

The WMI object fwags contwow whethew the method ow notification ID is used:

- 0x1: Data bwock usage is expensive and must be expwicitwy enabwed/disabwed.
- 0x2: Data bwock contains WMI methods.
- 0x4: Data bwock contains ASCIZ stwing.
- 0x8: Data bwock descwibes a WMI event, use notification ID instead
  of method ID.

Each WMI object GUID can appeaw muwtipwe times inside a system.
The method/notification ID is used to constwuct the ACPI method names used fow
intewacting with the WMI object.

WQxx ACPI methods
-----------------

If a data bwock does not contain WMI methods, then its content can be wetwieved
by this wequiwed ACPI method. The wast two chawactews of the ACPI method name
awe the method ID of the data bwock to quewy. Theiw singwe pawametew is an
integew descwibing the instance which shouwd be quewied. This pawametew can be
omitted if the data bwock contains onwy a singwe instance.

WSxx ACPI methods
-----------------

Simiwaw to the ``WQxx`` ACPI methods, except that it is optionaw and takes an
additionaw buffew as its second awgument. The instance awgument awso cannot
be omitted.

WMxx ACPI methods
-----------------

Used fow executing WMI methods associated with a data bwock. The wast two
chawactews of the ACPI method name awe the method ID of the data bwock
containing the WMI methods. Theiw fiwst pawametew is a integew descwibing the
instance which methods shouwd be executed. The second pawametew is an integew
descwibing the WMI method ID to execute, and the thiwd pawametew is a buffew
containing the WMI method pawametews. If the data bwock is mawked as containing
an ASCIZ stwing, then this buffew shouwd contain an ASCIZ stwing. The ACPI
method wiww wetuwn the wesuwt of the executed WMI method.

WExx ACPI methods
-----------------

Used fow optionawwy enabwing/disabwing WMI events, the wast two chawactews of
the ACPI method awe the notification ID of the data bwock descwibing the WMI
event as hexadecimaw vawue. Theiw fiwst pawametew is an integew with a vawue
of 0 if the WMI event shouwd be disabwed, othew vawues wiww enabwe
the WMI event.

WCxx ACPI methods
-----------------
Simiwaw to the ``WExx`` ACPI methods, except that it contwows data cowwection
instead of events and thus the wast two chawactews of the ACPI method name awe
the method ID of the data bwock to enabwe/disabwe.

_WED ACPI method
----------------

Used to wetwieve additionaw WMI event data, its singwe pawametew is a integew
howding the notification ID of the event.
