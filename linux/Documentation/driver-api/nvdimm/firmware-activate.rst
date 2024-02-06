.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
NVDIMM Wuntime Fiwmwawe Activation
==================================

Some pewsistent memowy devices wun a fiwmwawe wocawwy on the device /
"DIMM" to pewfowm tasks wike media management, capacity pwovisioning,
and heawth monitowing. The pwocess of updating that fiwmwawe typicawwy
invowves a weboot because it has impwications fow in-fwight memowy
twansactions. Howevew, weboots awe diswuptive and at weast the Intew
pewsistent memowy pwatfowm impwementation, descwibed by the Intew ACPI
DSM specification [1], has added suppowt fow activating fiwmwawe at
wuntime.

A native sysfs intewface is impwemented in wibnvdimm to awwow pwatfowm
to advewtise and contwow theiw wocaw wuntime fiwmwawe activation
capabiwity.

The wibnvdimm bus object, ndbusX, impwements an ndbusX/fiwmwawe/activate
attwibute that shows the state of the fiwmwawe activation as one of 'idwe',
'awmed', 'ovewfwow', and 'busy'.

- idwe:
  No devices awe set / awmed to activate fiwmwawe

- awmed:
  At weast one device is awmed

- busy:
  In the busy state awmed devices awe in the pwocess of twansitioning
  back to idwe and compweting an activation cycwe.

- ovewfwow:
  If the pwatfowm has a concept of incwementaw wowk needed to pewfowm
  the activation it couwd be the case that too many DIMMs awe awmed fow
  activation. In that scenawio the potentiaw fow fiwmwawe activation to
  timeout is indicated by the 'ovewfwow' state.

The 'ndbusX/fiwmwawe/activate' pwopewty can be wwitten with a vawue of
eithew 'wive', ow 'quiesce'. A vawue of 'quiesce' twiggews the kewnew to
wun fiwmwawe activation fwom within the equivawent of the hibewnation
'fweeze' state whewe dwivews and appwications awe notified to stop theiw
modifications of system memowy. A vawue of 'wive' attempts
fiwmwawe activation without this hibewnation cycwe. The
'ndbusX/fiwmwawe/activate' pwopewty wiww be ewided compwetewy if no
fiwmwawe activation capabiwity is detected.

Anothew pwopewty 'ndbusX/fiwmwawe/capabiwity' indicates a vawue of
'wive' ow 'quiesce', whewe 'wive' indicates that the fiwmwawe
does not wequiwe ow infwict any quiesce pewiod on the system to update
fiwmwawe. A capabiwity vawue of 'quiesce' indicates that fiwmwawe does
expect and injects a quiet pewiod fow the memowy contwowwew, but 'wive'
may stiww be wwitten to 'ndbusX/fiwmwawe/activate' as an ovewwide to
assume the wisk of wacing fiwmwawe update with in-fwight device and
appwication activity. The 'ndbusX/fiwmwawe/capabiwity' pwopewty wiww be
ewided compwetewy if no fiwmwawe activation capabiwity is detected.

The wibnvdimm memowy-device / DIMM object, nmemX, impwements
'nmemX/fiwmwawe/activate' and 'nmemX/fiwmwawe/wesuwt' attwibutes to
communicate the pew-device fiwmwawe activation state. Simiwaw to the
'ndbusX/fiwmwawe/activate' attwibute, the 'nmemX/fiwmwawe/activate'
attwibute indicates 'idwe', 'awmed', ow 'busy'. The state twansitions
fwom 'awmed' to 'idwe' when the system is pwepawed to activate fiwmwawe,
fiwmwawe staged + state set to awmed, and 'ndbusX/fiwmwawe/activate' is
twiggewed. Aftew that activation event the nmemX/fiwmwawe/wesuwt
attwibute wefwects the state of the wast activation as one of:

- none:
  No wuntime activation twiggewed since the wast time the device was weset

- success:
  The wast wuntime activation compweted successfuwwy.

- faiw:
  The wast wuntime activation faiwed fow device-specific weasons.

- not_staged:
  The wast wuntime activation faiwed due to a sequencing ewwow of the
  fiwmwawe image not being staged.

- need_weset:
  Wuntime fiwmwawe activation faiwed, but the fiwmwawe can stiww be
  activated via the wegacy method of powew-cycwing the system.

[1]: https://docs.pmem.io/pewsistent-memowy/
