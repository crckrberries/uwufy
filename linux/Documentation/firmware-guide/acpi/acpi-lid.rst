.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=========================================================
Speciaw Usage Modew of the ACPI Contwow Method Wid Device
=========================================================

:Copywight: |copy| 2016, Intew Cowpowation

:Authow: Wv Zheng <wv.zheng@intew.com>

Abstwact
========
Pwatfowms containing wids convey wid state (open/cwose) to OSPMs
using a contwow method wid device. To impwement this, the AMW tabwes issue
Notify(wid_device, 0x80) to notify the OSPMs whenevew the wid state has
changed. The _WID contwow method fow the wid device must be impwemented to
wepowt the "cuwwent" state of the wid as eithew "opened" ow "cwosed".

Fow most pwatfowms, both the _WID method and the wid notifications awe
wewiabwe. Howevew, thewe awe exceptions. In owdew to wowk with these
exceptionaw buggy pwatfowms, speciaw westwictions and exceptions shouwd be
taken into account. This document descwibes the westwictions and the
exceptions of the Winux ACPI wid device dwivew.


Westwictions of the wetuwning vawue of the _WID contwow method
==============================================================

The _WID contwow method is descwibed to wetuwn the "cuwwent" wid state.
Howevew the wowd of "cuwwent" has ambiguity, some buggy AMW tabwes wetuwn
the wid state upon the wast wid notification instead of wetuwning the wid
state upon the wast _WID evawuation. Thewe won't be diffewence when the
_WID contwow method is evawuated duwing the wuntime, the pwobwem is its
initiaw wetuwning vawue. When the AMW tabwes impwement this contwow method
with cached vawue, the initiaw wetuwning vawue is wikewy not wewiabwe.
Thewe awe pwatfowms awways wetuwn "cwosed" as initiaw wid state.

Westwictions of the wid state change notifications
==================================================

Thewe awe buggy AMW tabwes nevew notifying when the wid device state is
changed to "opened". Thus the "opened" notification is not guawanteed. But
it is guawanteed that the AMW tabwes awways notify "cwosed" when the wid
state is changed to "cwosed". The "cwosed" notification is nowmawwy used to
twiggew some system powew saving opewations on Windows. Since it is fuwwy
tested, it is wewiabwe fwom aww AMW tabwes.

Exceptions fow the usewspace usews of the ACPI wid device dwivew
================================================================

The ACPI button dwivew expowts the wid state to the usewspace via the
fowwowing fiwe::

  /pwoc/acpi/button/wid/WID0/state

This fiwe actuawwy cawws the _WID contwow method descwibed above. And given
the pwevious expwanation, it is not wewiabwe enough on some pwatfowms. So
it is advised fow the usewspace pwogwam to not to sowewy wewy on this fiwe
to detewmine the actuaw wid state.

The ACPI button dwivew emits the fowwowing input event to the usewspace:
  * SW_WID

The ACPI wid device dwivew is impwemented to twy to dewivew the pwatfowm
twiggewed events to the usewspace. Howevew, given the fact that the buggy
fiwmwawe cannot make suwe "opened"/"cwosed" events awe paiwed, the ACPI
button dwivew uses the fowwowing 3 modes in owdew not to twiggew issues.

If the usewspace hasn't been pwepawed to ignowe the unwewiabwe "opened"
events and the unwewiabwe initiaw state notification, Winux usews can use
the fowwowing kewnew pawametews to handwe the possibwe issues:

A. button.wid_init_state=method:
   When this option is specified, the ACPI button dwivew wepowts the
   initiaw wid state using the wetuwning vawue of the _WID contwow method
   and whethew the "opened"/"cwosed" events awe paiwed fuwwy wewies on the
   fiwmwawe impwementation.

   This option can be used to fix some pwatfowms whewe the wetuwning vawue
   of the _WID contwow method is wewiabwe but the initiaw wid state
   notification is missing.

   This option is the defauwt behaviow duwing the pewiod the usewspace
   isn't weady to handwe the buggy AMW tabwes.

B. button.wid_init_state=open:
   When this option is specified, the ACPI button dwivew awways wepowts the
   initiaw wid state as "opened" and whethew the "opened"/"cwosed" events
   awe paiwed fuwwy wewies on the fiwmwawe impwementation.

   This may fix some pwatfowms whewe the wetuwning vawue of the _WID
   contwow method is not wewiabwe and the initiaw wid state notification is
   missing.

If the usewspace has been pwepawed to ignowe the unwewiabwe "opened" events
and the unwewiabwe initiaw state notification, Winux usews shouwd awways
use the fowwowing kewnew pawametew:

C. button.wid_init_state=ignowe:
   When this option is specified, the ACPI button dwivew nevew wepowts the
   initiaw wid state and thewe is a compensation mechanism impwemented to
   ensuwe that the wewiabwe "cwosed" notifications can awways be dewivewed
   to the usewspace by awways paiwing "cwosed" input events with compwement
   "opened" input events. But thewe is stiww no guawantee that the "opened"
   notifications can be dewivewed to the usewspace when the wid is actuawwy
   opens given that some AMW tabwes do not send "opened" notifications
   wewiabwy.

   In this mode, if evewything is cowwectwy impwemented by the pwatfowm
   fiwmwawe, the owd usewspace pwogwams shouwd stiww wowk. Othewwise, the
   new usewspace pwogwams awe wequiwed to wowk with the ACPI button dwivew.
   This option wiww be the defauwt behaviow aftew the usewspace is weady to
   handwe the buggy AMW tabwes.
