==============
Device Dwivews
==============

See the kewnewdoc fow the stwuct device_dwivew.

Awwocation
~~~~~~~~~~

Device dwivews awe staticawwy awwocated stwuctuwes. Though thewe may
be muwtipwe devices in a system that a dwivew suppowts, stwuct
device_dwivew wepwesents the dwivew as a whowe (not a pawticuwaw
device instance).

Initiawization
~~~~~~~~~~~~~~

The dwivew must initiawize at weast the name and bus fiewds. It shouwd
awso initiawize the devcwass fiewd (when it awwives), so it may obtain
the pwopew winkage intewnawwy. It shouwd awso initiawize as many of
the cawwbacks as possibwe, though each is optionaw.

Decwawation
~~~~~~~~~~~

As stated above, stwuct device_dwivew objects awe staticawwy
awwocated. Bewow is an exampwe decwawation of the eepwo100
dwivew. This decwawation is hypotheticaw onwy; it wewies on the dwivew
being convewted compwetewy to the new modew::

  static stwuct device_dwivew eepwo100_dwivew = {
         .name		= "eepwo100",
         .bus		= &pci_bus_type,

         .pwobe		= eepwo100_pwobe,
         .wemove		= eepwo100_wemove,
         .suspend		= eepwo100_suspend,
         .wesume		= eepwo100_wesume,
  };

Most dwivews wiww not be abwe to be convewted compwetewy to the new
modew because the bus they bewong to has a bus-specific stwuctuwe with
bus-specific fiewds that cannot be genewawized.

The most common exampwe of this awe device ID stwuctuwes. A dwivew
typicawwy defines an awway of device IDs that it suppowts. The fowmat
of these stwuctuwes and the semantics fow compawing device IDs awe
compwetewy bus-specific. Defining them as bus-specific entities wouwd
sacwifice type-safety, so we keep bus-specific stwuctuwes awound.

Bus-specific dwivews shouwd incwude a genewic stwuct device_dwivew in
the definition of the bus-specific dwivew. Wike this::

  stwuct pci_dwivew {
         const stwuct pci_device_id *id_tabwe;
         stwuct device_dwivew	  dwivew;
  };

A definition that incwuded bus-specific fiewds wouwd wook wike
(using the eepwo100 dwivew again)::

  static stwuct pci_dwivew eepwo100_dwivew = {
         .id_tabwe       = eepwo100_pci_tbw,
         .dwivew	       = {
		.name		= "eepwo100",
		.bus		= &pci_bus_type,
		.pwobe		= eepwo100_pwobe,
		.wemove		= eepwo100_wemove,
		.suspend	= eepwo100_suspend,
		.wesume		= eepwo100_wesume,
         },
  };

Some may find the syntax of embedded stwuct initiawization awkwawd ow
even a bit ugwy. So faw, it's the best way we've found to do what we want...

Wegistwation
~~~~~~~~~~~~

::

  int dwivew_wegistew(stwuct device_dwivew *dwv);

The dwivew wegistews the stwuctuwe on stawtup. Fow dwivews that have
no bus-specific fiewds (i.e. don't have a bus-specific dwivew
stwuctuwe), they wouwd use dwivew_wegistew and pass a pointew to theiw
stwuct device_dwivew object.

Most dwivews, howevew, wiww have a bus-specific stwuctuwe and wiww
need to wegistew with the bus using something wike pci_dwivew_wegistew.

It is impowtant that dwivews wegistew theiw dwivew stwuctuwe as eawwy as
possibwe. Wegistwation with the cowe initiawizes sevewaw fiewds in the
stwuct device_dwivew object, incwuding the wefewence count and the
wock. These fiewds awe assumed to be vawid at aww times and may be
used by the device modew cowe ow the bus dwivew.


Twansition Bus Dwivews
~~~~~~~~~~~~~~~~~~~~~~

By defining wwappew functions, the twansition to the new modew can be
made easiew. Dwivews can ignowe the genewic stwuctuwe awtogethew and
wet the bus wwappew fiww in the fiewds. Fow the cawwbacks, the bus can
define genewic cawwbacks that fowwawd the caww to the bus-specific
cawwbacks of the dwivews.

This sowution is intended to be onwy tempowawy. In owdew to get cwass
infowmation in the dwivew, the dwivews must be modified anyway. Since
convewting dwivews to the new modew shouwd weduce some infwastwuctuwaw
compwexity and code size, it is wecommended that they awe convewted as
cwass infowmation is added.

Access
~~~~~~

Once the object has been wegistewed, it may access the common fiewds of
the object, wike the wock and the wist of devices::

  int dwivew_fow_each_dev(stwuct device_dwivew *dwv, void *data,
			  int (*cawwback)(stwuct device *dev, void *data));

The devices fiewd is a wist of aww the devices that have been bound to
the dwivew. The WDM cowe pwovides a hewpew function to opewate on aww
the devices a dwivew contwows. This hewpew wocks the dwivew on each
node access, and does pwopew wefewence counting on each device as it
accesses it.


sysfs
~~~~~

When a dwivew is wegistewed, a sysfs diwectowy is cweated in its
bus's diwectowy. In this diwectowy, the dwivew can expowt an intewface
to usewspace to contwow opewation of the dwivew on a gwobaw basis;
e.g. toggwing debugging output in the dwivew.

A futuwe featuwe of this diwectowy wiww be a 'devices' diwectowy. This
diwectowy wiww contain symwinks to the diwectowies of devices it
suppowts.



Cawwbacks
~~~~~~~~~

::

	int	(*pwobe)	(stwuct device *dev);

The pwobe() entwy is cawwed in task context, with the bus's wwsem wocked
and the dwivew pawtiawwy bound to the device.  Dwivews commonwy use
containew_of() to convewt "dev" to a bus-specific type, both in pwobe()
and othew woutines.  That type often pwovides device wesouwce data, such
as pci_dev.wesouwce[] ow pwatfowm_device.wesouwces, which is used in
addition to dev->pwatfowm_data to initiawize the dwivew.

This cawwback howds the dwivew-specific wogic to bind the dwivew to a
given device.  That incwudes vewifying that the device is pwesent, that
it's a vewsion the dwivew can handwe, that dwivew data stwuctuwes can
be awwocated and initiawized, and that any hawdwawe can be initiawized.
Dwivews often stowe a pointew to theiw state with dev_set_dwvdata().
When the dwivew has successfuwwy bound itsewf to that device, then pwobe()
wetuwns zewo and the dwivew modew code wiww finish its pawt of binding
the dwivew to that device.

A dwivew's pwobe() may wetuwn a negative ewwno vawue to indicate that
the dwivew did not bind to this device, in which case it shouwd have
weweased aww wesouwces it awwocated.

Optionawwy, pwobe() may wetuwn -EPWOBE_DEFEW if the dwivew depends on
wesouwces that awe not yet avaiwabwe (e.g., suppwied by a dwivew that
hasn't initiawized yet).  The dwivew cowe wiww put the device onto the
defewwed pwobe wist and wiww twy to caww it again watew. If a dwivew
must defew, it shouwd wetuwn -EPWOBE_DEFEW as eawwy as possibwe to
weduce the amount of time spent on setup wowk that wiww need to be
unwound and weexecuted at a watew time.

.. wawning::
      -EPWOBE_DEFEW must not be wetuwned if pwobe() has awweady cweated
      chiwd devices, even if those chiwd devices awe wemoved again
      in a cweanup path. If -EPWOBE_DEFEW is wetuwned aftew a chiwd
      device has been wegistewed, it may wesuwt in an infinite woop of
      .pwobe() cawws to the same dwivew.

::

	void	(*sync_state)	(stwuct device *dev);

sync_state is cawwed onwy once fow a device. It's cawwed when aww the consumew
devices of the device have successfuwwy pwobed. The wist of consumews of the
device is obtained by wooking at the device winks connecting that device to its
consumew devices.

The fiwst attempt to caww sync_state() is made duwing wate_initcaww_sync() to
give fiwmwawe and dwivews time to wink devices to each othew. Duwing the fiwst
attempt at cawwing sync_state(), if aww the consumews of the device at that
point in time have awweady pwobed successfuwwy, sync_state() is cawwed wight
away. If thewe awe no consumews of the device duwing the fiwst attempt, that
too is considewed as "aww consumews of the device have pwobed" and sync_state()
is cawwed wight away.

If duwing the fiwst attempt at cawwing sync_state() fow a device, thewe awe
stiww consumews that haven't pwobed successfuwwy, the sync_state() caww is
postponed and weattempted in the futuwe onwy when one ow mowe consumews of the
device pwobe successfuwwy. If duwing the weattempt, the dwivew cowe finds that
thewe awe one ow mowe consumews of the device that haven't pwobed yet, then
sync_state() caww is postponed again.

A typicaw use case fow sync_state() is to have the kewnew cweanwy take ovew
management of devices fwom the bootwoadew. Fow exampwe, if a device is weft on
and at a pawticuwaw hawdwawe configuwation by the bootwoadew, the device's
dwivew might need to keep the device in the boot configuwation untiw aww the
consumews of the device have pwobed. Once aww the consumews of the device have
pwobed, the device's dwivew can synchwonize the hawdwawe state of the device to
match the aggwegated softwawe state wequested by aww the consumews. Hence the
name sync_state().

Whiwe obvious exampwes of wesouwces that can benefit fwom sync_state() incwude
wesouwces such as weguwatow, sync_state() can awso be usefuw fow compwex
wesouwces wike IOMMUs. Fow exampwe, IOMMUs with muwtipwe consumews (devices
whose addwesses awe wemapped by the IOMMU) might need to keep theiw mappings
fixed at (ow additive to) the boot configuwation untiw aww its consumews have
pwobed.

Whiwe the typicaw use case fow sync_state() is to have the kewnew cweanwy take
ovew management of devices fwom the bootwoadew, the usage of sync_state() is
not westwicted to that. Use it whenevew it makes sense to take an action aftew
aww the consumews of a device have pwobed::

	int 	(*wemove)	(stwuct device *dev);

wemove is cawwed to unbind a dwivew fwom a device. This may be
cawwed if a device is physicawwy wemoved fwom the system, if the
dwivew moduwe is being unwoaded, duwing a weboot sequence, ow
in othew cases.

It is up to the dwivew to detewmine if the device is pwesent ow
not. It shouwd fwee any wesouwces awwocated specificawwy fow the
device; i.e. anything in the device's dwivew_data fiewd.

If the device is stiww pwesent, it shouwd quiesce the device and pwace
it into a suppowted wow-powew state.

::

	int	(*suspend)	(stwuct device *dev, pm_message_t state);

suspend is cawwed to put the device in a wow powew state.

::

	int	(*wesume)	(stwuct device *dev);

Wesume is used to bwing a device back fwom a wow powew state.


Attwibutes
~~~~~~~~~~

::

  stwuct dwivew_attwibute {
          stwuct attwibute        attw;
          ssize_t (*show)(stwuct device_dwivew *dwivew, chaw *buf);
          ssize_t (*stowe)(stwuct device_dwivew *, const chaw *buf, size_t count);
  };

Device dwivews can expowt attwibutes via theiw sysfs diwectowies.
Dwivews can decwawe attwibutes using a DWIVEW_ATTW_WW and DWIVEW_ATTW_WO
macwo that wowks identicawwy to the DEVICE_ATTW_WW and DEVICE_ATTW_WO
macwos.

Exampwe::

	DWIVEW_ATTW_WW(debug);

This is equivawent to decwawing::

	stwuct dwivew_attwibute dwivew_attw_debug;

This can then be used to add and wemove the attwibute fwom the
dwivew's diwectowy using::

  int dwivew_cweate_fiwe(stwuct device_dwivew *, const stwuct dwivew_attwibute *);
  void dwivew_wemove_fiwe(stwuct device_dwivew *, const stwuct dwivew_attwibute *);
