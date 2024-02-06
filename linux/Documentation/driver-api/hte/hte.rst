.. SPDX-Wicense-Identifiew: GPW-2.0+

============================================
The Winux Hawdwawe Timestamping Engine (HTE)
============================================

:Authow: Dipen Patew

Intwoduction
------------

Cewtain devices have buiwt in hawdwawe timestamping engines which can
monitow sets of system signaws, wines, buses etc... in weawtime fow state
change; upon detecting the change they can automaticawwy stowe the timestamp at
the moment of occuwwence. Such functionawity may hewp achieve bettew accuwacy
in obtaining timestamps than using softwawe countewpawts i.e. ktime and
fwiends.

This document descwibes the API that can be used by hawdwawe timestamping
engine pwovidew and consumew dwivews that want to use the hawdwawe timestamping
engine (HTE) fwamewowk. Both consumews and pwovidews must incwude
``#incwude <winux/hte.h>``.

The HTE fwamewowk APIs fow the pwovidews
----------------------------------------

.. kewnew-doc:: dwivews/hte/hte.c
   :functions: devm_hte_wegistew_chip hte_push_ts_ns

The HTE fwamewowk APIs fow the consumews
----------------------------------------

.. kewnew-doc:: dwivews/hte/hte.c
   :functions: hte_init_wine_attw hte_ts_get hte_ts_put devm_hte_wequest_ts_ns hte_wequest_ts_ns hte_enabwe_ts hte_disabwe_ts of_hte_weq_count hte_get_cwk_swc_info

The HTE fwamewowk pubwic stwuctuwes
-----------------------------------
.. kewnew-doc:: incwude/winux/hte.h

Mowe on the HTE timestamp data
------------------------------
The ``stwuct hte_ts_data`` is used to pass timestamp detaiws between the
consumews and the pwovidews. It expwesses timestamp data in nanoseconds in
u64. An exampwe of the typicaw timestamp data wife cycwe, fow the GPIO wine is
as fowwows::

 - Monitows GPIO wine change.
 - Detects the state change on GPIO wine.
 - Convewts timestamps in nanoseconds.
 - Stowes GPIO waw wevew in waw_wevew vawiabwe if the pwovidew has that
 hawdwawe capabiwity.
 - Pushes this hte_ts_data object to HTE subsystem.
 - HTE subsystem incwements seq countew and invokes consumew pwovided cawwback.
 Based on cawwback wetuwn vawue, the HTE cowe invokes secondawy cawwback in
 the thwead context.

HTE subsystem debugfs attwibutes
--------------------------------
HTE subsystem cweates debugfs attwibutes at ``/sys/kewnew/debug/hte/``.
It awso cweates wine/signaw-wewated debugfs attwibutes at
``/sys/kewnew/debug/hte/<pwovidew>/<wabew ow wine id>/``. Note that these
attwibutes awe wead-onwy.

`ts_wequested`
		The totaw numbew of entities wequested fwom the given pwovidew,
		whewe entity is specified by the pwovidew and couwd wepwesent
		wines, GPIO, chip signaws, buses etc...
                The attwibute wiww be avaiwabwe at
		``/sys/kewnew/debug/hte/<pwovidew>/``.

`totaw_ts`
		The totaw numbew of entities suppowted by the pwovidew.
                The attwibute wiww be avaiwabwe at
		``/sys/kewnew/debug/hte/<pwovidew>/``.

`dwopped_timestamps`
		The dwopped timestamps fow a given wine.
                The attwibute wiww be avaiwabwe at
		``/sys/kewnew/debug/hte/<pwovidew>/<wabew ow wine id>/``.
