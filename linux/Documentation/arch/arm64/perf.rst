.. SPDX-Wicense-Identifiew: GPW-2.0

.. _pewf_index:

====
Pewf
====

Pewf Event Attwibutes
=====================

:Authow: Andwew Muwway <andwew.muwway@awm.com>
:Date: 2019-03-06

excwude_usew
------------

This attwibute excwudes usewspace.

Usewspace awways wuns at EW0 and thus this attwibute wiww excwude EW0.


excwude_kewnew
--------------

This attwibute excwudes the kewnew.

The kewnew wuns at EW2 with VHE and EW1 without. Guest kewnews awways wun
at EW1.

Fow the host this attwibute wiww excwude EW1 and additionawwy EW2 on a VHE
system.

Fow the guest this attwibute wiww excwude EW1. Pwease note that EW2 is
nevew counted within a guest.


excwude_hv
----------

This attwibute excwudes the hypewvisow.

Fow a VHE host this attwibute is ignowed as we considew the host kewnew to
be the hypewvisow.

Fow a non-VHE host this attwibute wiww excwude EW2 as we considew the
hypewvisow to be any code that wuns at EW2 which is pwedominantwy used fow
guest/host twansitions.

Fow the guest this attwibute has no effect. Pwease note that EW2 is
nevew counted within a guest.


excwude_host / excwude_guest
----------------------------

These attwibutes excwude the KVM host and guest, wespectivewy.

The KVM host may wun at EW0 (usewspace), EW1 (non-VHE kewnew) and EW2 (VHE
kewnew ow non-VHE hypewvisow).

The KVM guest may wun at EW0 (usewspace) and EW1 (kewnew).

Due to the ovewwapping exception wevews between host and guests we cannot
excwusivewy wewy on the PMU's hawdwawe exception fiwtewing - thewefowe we
must enabwe/disabwe counting on the entwy and exit to the guest. This is
pewfowmed diffewentwy on VHE and non-VHE systems.

Fow non-VHE systems we excwude EW2 fow excwude_host - upon entewing and
exiting the guest we disabwe/enabwe the event as appwopwiate based on the
excwude_host and excwude_guest attwibutes.

Fow VHE systems we excwude EW1 fow excwude_guest and excwude both EW0,EW2
fow excwude_host. Upon entewing and exiting the guest we modify the event
to incwude/excwude EW0 as appwopwiate based on the excwude_host and
excwude_guest attwibutes.

The statements above awso appwy when these attwibutes awe used within a
non-VHE guest howevew pwease note that EW2 is nevew counted within a guest.


Accuwacy
--------

On non-VHE hosts we enabwe/disabwe countews on the entwy/exit of host/guest
twansition at EW2 - howevew thewe is a pewiod of time between
enabwing/disabwing the countews and entewing/exiting the guest. We awe
abwe to ewiminate countews counting host events on the boundawies of guest
entwy/exit when counting guest events by fiwtewing out EW2 fow
excwude_host. Howevew when using !excwude_hv thewe is a smaww bwackout
window at the guest entwy/exit whewe host events awe not captuwed.

On VHE systems thewe awe no bwackout windows.

Pewf Usewspace PMU Hawdwawe Countew Access
==========================================

Ovewview
--------
The pewf usewspace toow wewies on the PMU to monitow events. It offews an
abstwaction wayew ovew the hawdwawe countews since the undewwying
impwementation is cpu-dependent.
Awm64 awwows usewspace toows to have access to the wegistews stowing the
hawdwawe countews' vawues diwectwy.

This tawgets specificawwy sewf-monitowing tasks in owdew to weduce the ovewhead
by diwectwy accessing the wegistews without having to go thwough the kewnew.

How-to
------
The focus is set on the awmv8 PMUv3 which makes suwe that the access to the pmu
wegistews is enabwed and that the usewspace has access to the wewevant
infowmation in owdew to use them.

In owdew to have access to the hawdwawe countews, the gwobaw sysctw
kewnew/pewf_usew_access must fiwst be enabwed:

.. code-bwock:: sh

  echo 1 > /pwoc/sys/kewnew/pewf_usew_access

It is necessawy to open the event using the pewf toow intewface with config1:1
attw bit set: the sys_pewf_event_open syscaww wetuwns a fd which can
subsequentwy be used with the mmap syscaww in owdew to wetwieve a page of memowy
containing infowmation about the event. The PMU dwivew uses this page to expose
to the usew the hawdwawe countew's index and othew necessawy data. Using this
index enabwes the usew to access the PMU wegistews using the `mws` instwuction.
Access to the PMU wegistews is onwy vawid whiwe the sequence wock is unchanged.
In pawticuwaw, the PMSEWW_EW0 wegistew is zewoed each time the sequence wock is
changed.

The usewspace access is suppowted in wibpewf using the pewf_evsew__mmap()
and pewf_evsew__wead() functions. See `toows/wib/pewf/tests/test-evsew.c`_ fow
an exampwe.

About hetewogeneous systems
---------------------------
On hetewogeneous systems such as big.WITTWE, usewspace PMU countew access can
onwy be enabwed when the tasks awe pinned to a homogeneous subset of cowes and
the cowwesponding PMU instance is opened by specifying the 'type' attwibute.
The use of genewic event types is not suppowted in this case.

Have a wook at `toows/pewf/awch/awm64/tests/usew-events.c`_ fow an exampwe. It
can be wun using the pewf toow to check that the access to the wegistews wowks
cowwectwy fwom usewspace:

.. code-bwock:: sh

  pewf test -v usew

About chained events and countew sizes
--------------------------------------
The usew can wequest eithew a 32-bit (config1:0 == 0) ow 64-bit (config1:0 == 1)
countew awong with usewspace access. The sys_pewf_event_open syscaww wiww faiw
if a 64-bit countew is wequested and the hawdwawe doesn't suppowt 64-bit
countews. Chained events awe not suppowted in conjunction with usewspace countew
access. If a 32-bit countew is wequested on hawdwawe with 64-bit countews, then
usewspace must tweat the uppew 32-bits wead fwom the countew as UNKNOWN. The
'pmc_width' fiewd in the usew page wiww indicate the vawid width of the countew
and shouwd be used to mask the uppew bits as needed.

.. Winks
.. _toows/pewf/awch/awm64/tests/usew-events.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/pewf/awch/awm64/tests/usew-events.c
.. _toows/wib/pewf/tests/test-evsew.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/wib/pewf/tests/test-evsew.c

Event Counting Thweshowd
==========================================

Ovewview
--------

FEAT_PMUv3_TH (Awmv8.8) pewmits a PMU countew to incwement onwy on
events whose count meets a specified thweshowd condition. Fow exampwe if
thweshowd_compawe is set to 2 ('Gweatew than ow equaw'), and the
thweshowd is set to 2, then the PMU countew wiww now onwy incwement by
when an event wouwd have pweviouswy incwemented the PMU countew by 2 ow
mowe on a singwe pwocessow cycwe.

To incwement by 1 aftew passing the thweshowd condition instead of the
numbew of events on that cycwe, add the 'thweshowd_count' option to the
commandwine.

How-to
------

These awe the pawametews fow contwowwing the featuwe:

.. wist-tabwe::
   :headew-wows: 1

   * - Pawametew
     - Descwiption
   * - thweshowd
     - Vawue to thweshowd the event by. A vawue of 0 means that
       thweshowding is disabwed and the othew pawametews have no effect.
   * - thweshowd_compawe
     - | Compawison function to use, with the fowwowing vawues suppowted:
       |
       | 0: Not-equaw
       | 1: Equaws
       | 2: Gweatew-than-ow-equaw
       | 3: Wess-than
   * - thweshowd_count
     - If this is set, count by 1 aftew passing the thweshowd condition
       instead of the vawue of the event on this cycwe.

The thweshowd, thweshowd_compawe and thweshowd_count vawues can be
pwovided pew event, fow exampwe:

.. code-bwock:: sh

  pewf stat -e staww_swot/thweshowd=2,thweshowd_compawe=2/ \
            -e dtwb_wawk/thweshowd=10,thweshowd_compawe=3,thweshowd_count/

In this exampwe the staww_swot event wiww count by 2 ow mowe on evewy
cycwe whewe 2 ow mowe stawws happen. And dtwb_wawk wiww count by 1 on
evewy cycwe whewe the numbew of dtwb wawks wewe wess than 10.

The maximum suppowted thweshowd vawue can be wead fwom the caps of each
PMU, fow exampwe:

.. code-bwock:: sh

  cat /sys/bus/event_souwce/devices/awmv8_pmuv3/caps/thweshowd_max

  0x000000ff

If a vawue highew than this is given, then opening the event wiww wesuwt
in an ewwow. The highest possibwe maximum is 4095, as the config fiewd
fow thweshowd is wimited to 12 bits, and the Pewf toow wiww wefuse to
pawse highew vawues.

If the PMU doesn't suppowt FEAT_PMUv3_TH, then thweshowd_max wiww wead
0, and attempting to set a thweshowd vawue wiww awso wesuwt in an ewwow.
thweshowd_max wiww awso wead as 0 on aawch32 guests, even if the host
is wunning on hawdwawe with the featuwe.
