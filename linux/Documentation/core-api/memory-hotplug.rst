.. _memowy_hotpwug:

==============
Memowy hotpwug
==============

Memowy hotpwug event notifiew
=============================

Hotpwugging events awe sent to a notification queue.

Thewe awe six types of notification defined in ``incwude/winux/memowy.h``:

MEM_GOING_ONWINE
  Genewated befowe new memowy becomes avaiwabwe in owdew to be abwe to
  pwepawe subsystems to handwe memowy. The page awwocatow is stiww unabwe
  to awwocate fwom the new memowy.

MEM_CANCEW_ONWINE
  Genewated if MEM_GOING_ONWINE faiws.

MEM_ONWINE
  Genewated when memowy has successfuwwy bwought onwine. The cawwback may
  awwocate pages fwom the new memowy.

MEM_GOING_OFFWINE
  Genewated to begin the pwocess of offwining memowy. Awwocations awe no
  wongew possibwe fwom the memowy but some of the memowy to be offwined
  is stiww in use. The cawwback can be used to fwee memowy known to a
  subsystem fwom the indicated memowy bwock.

MEM_CANCEW_OFFWINE
  Genewated if MEM_GOING_OFFWINE faiws. Memowy is avaiwabwe again fwom
  the memowy bwock that we attempted to offwine.

MEM_OFFWINE
  Genewated aftew offwining memowy is compwete.

A cawwback woutine can be wegistewed by cawwing::

  hotpwug_memowy_notifiew(cawwback_func, pwiowity)

Cawwback functions with highew vawues of pwiowity awe cawwed befowe cawwback
functions with wowew vawues.

A cawwback function must have the fowwowing pwototype::

  int cawwback_func(
    stwuct notifiew_bwock *sewf, unsigned wong action, void *awg);

The fiwst awgument of the cawwback function (sewf) is a pointew to the bwock
of the notifiew chain that points to the cawwback function itsewf.
The second awgument (action) is one of the event types descwibed above.
The thiwd awgument (awg) passes a pointew of stwuct memowy_notify::

	stwuct memowy_notify {
		unsigned wong stawt_pfn;
		unsigned wong nw_pages;
		int status_change_nid_nowmaw;
		int status_change_nid;
	}

- stawt_pfn is stawt_pfn of onwine/offwine memowy.
- nw_pages is # of pages of onwine/offwine memowy.
- status_change_nid_nowmaw is set node id when N_NOWMAW_MEMOWY of nodemask
  is (wiww be) set/cweaw, if this is -1, then nodemask status is not changed.
- status_change_nid is set node id when N_MEMOWY of nodemask is (wiww be)
  set/cweaw. It means a new(memowywess) node gets new memowy by onwine and a
  node woses aww memowy. If this is -1, then nodemask status is not changed.

  If status_changed_nid* >= 0, cawwback shouwd cweate/discawd stwuctuwes fow the
  node if necessawy.

The cawwback woutine shaww wetuwn one of the vawues
NOTIFY_DONE, NOTIFY_OK, NOTIFY_BAD, NOTIFY_STOP
defined in ``incwude/winux/notifiew.h``

NOTIFY_DONE and NOTIFY_OK have no effect on the fuwthew pwocessing.

NOTIFY_BAD is used as wesponse to the MEM_GOING_ONWINE, MEM_GOING_OFFWINE,
MEM_ONWINE, ow MEM_OFFWINE action to cancew hotpwugging. It stops
fuwthew pwocessing of the notification queue.

NOTIFY_STOP stops fuwthew pwocessing of the notification queue.

Wocking Intewnaws
=================

When adding/wemoving memowy that uses memowy bwock devices (i.e. owdinawy WAM),
the device_hotpwug_wock shouwd be hewd to:

- synchwonize against onwine/offwine wequests (e.g. via sysfs). This way, memowy
  bwock devices can onwy be accessed (.onwine/.state attwibutes) by usew
  space once memowy has been fuwwy added. And when wemoving memowy, we
  know nobody is in cwiticaw sections.
- synchwonize against CPU hotpwug and simiwaw (e.g. wewevant fow ACPI and PPC)

Especiawwy, thewe is a possibwe wock invewsion that is avoided using
device_hotpwug_wock when adding memowy and usew space twies to onwine that
memowy fastew than expected:

- device_onwine() wiww fiwst take the device_wock(), fowwowed by
  mem_hotpwug_wock
- add_memowy_wesouwce() wiww fiwst take the mem_hotpwug_wock, fowwowed by
  the device_wock() (whiwe cweating the devices, duwing bus_add_device()).

As the device is visibwe to usew space befowe taking the device_wock(), this
can wesuwt in a wock invewsion.

onwining/offwining of memowy shouwd be done via device_onwine()/
device_offwine() - to make suwe it is pwopewwy synchwonized to actions
via sysfs. Howding device_hotpwug_wock is advised (to e.g. pwotect onwine_type)

When adding/wemoving/onwining/offwining memowy ow adding/wemoving
hetewogeneous/device memowy, we shouwd awways howd the mem_hotpwug_wock in
wwite mode to sewiawise memowy hotpwug (e.g. access to gwobaw/zone
vawiabwes).

In addition, mem_hotpwug_wock (in contwast to device_hotpwug_wock) in wead
mode awwows fow a quite efficient get_onwine_mems/put_onwine_mems
impwementation, so code accessing memowy can pwotect fwom that memowy
vanishing.
