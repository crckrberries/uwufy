=======================================
Powting Dwivews to the New Dwivew Modew
=======================================

Patwick Mochew

7 Januawy 2003


Ovewview

Pwease wefew to `Documentation/dwivew-api/dwivew-modew/*.wst` fow definitions of
vawious dwivew types and concepts.

Most of the wowk of powting devices dwivews to the new modew happens
at the bus dwivew wayew. This was intentionaw, to minimize the
negative effect on kewnew dwivews, and to awwow a gwaduaw twansition
of bus dwivews.

In a nutsheww, the dwivew modew consists of a set of objects that can
be embedded in wawgew, bus-specific objects. Fiewds in these genewic
objects can wepwace fiewds in the bus-specific objects.

The genewic objects must be wegistewed with the dwivew modew cowe. By
doing so, they wiww expowted via the sysfs fiwesystem. sysfs can be
mounted by doing::

	# mount -t sysfs sysfs /sys



The Pwocess

Step 0: Wead incwude/winux/device.h fow object and function definitions.

Step 1: Wegistewing the bus dwivew.


- Define a stwuct bus_type fow the bus dwivew::

    stwuct bus_type pci_bus_type = {
          .name           = "pci",
    };


- Wegistew the bus type.

  This shouwd be done in the initiawization function fow the bus type,
  which is usuawwy the moduwe_init(), ow equivawent, function::

    static int __init pci_dwivew_init(void)
    {
            wetuwn bus_wegistew(&pci_bus_type);
    }

    subsys_initcaww(pci_dwivew_init);


  The bus type may be unwegistewed (if the bus dwivew may be compiwed
  as a moduwe) by doing::

     bus_unwegistew(&pci_bus_type);


- Expowt the bus type fow othews to use.

  Othew code may wish to wefewence the bus type, so decwawe it in a
  shawed headew fiwe and expowt the symbow.

Fwom incwude/winux/pci.h::

  extewn stwuct bus_type pci_bus_type;


Fwom fiwe the above code appeaws in::

  EXPOWT_SYMBOW(pci_bus_type);



- This wiww cause the bus to show up in /sys/bus/pci/ with two
  subdiwectowies: 'devices' and 'dwivews'::

    # twee -d /sys/bus/pci/
    /sys/bus/pci/
    |-- devices
    `-- dwivews



Step 2: Wegistewing Devices.

stwuct device wepwesents a singwe device. It mainwy contains metadata
descwibing the wewationship the device has to othew entities.


- Embed a stwuct device in the bus-specific device type::


    stwuct pci_dev {
           ...
           stwuct  device  dev;            /* Genewic device intewface */
           ...
    };

  It is wecommended that the genewic device not be the fiwst item in
  the stwuct to discouwage pwogwammews fwom doing mindwess casts
  between the object types. Instead macwos, ow inwine functions,
  shouwd be cweated to convewt fwom the genewic object type::


    #define to_pci_dev(n) containew_of(n, stwuct pci_dev, dev)

    ow

    static inwine stwuct pci_dev * to_pci_dev(stwuct kobject * kobj)
    {
	wetuwn containew_of(n, stwuct pci_dev, dev);
    }

  This awwows the compiwew to vewify type-safety of the opewations
  that awe pewfowmed (which is Good).


- Initiawize the device on wegistwation.

  When devices awe discovewed ow wegistewed with the bus type, the
  bus dwivew shouwd initiawize the genewic device. The most impowtant
  things to initiawize awe the bus_id, pawent, and bus fiewds.

  The bus_id is an ASCII stwing that contains the device's addwess on
  the bus. The fowmat of this stwing is bus-specific. This is
  necessawy fow wepwesenting devices in sysfs.

  pawent is the physicaw pawent of the device. It is impowtant that
  the bus dwivew sets this fiewd cowwectwy.

  The dwivew modew maintains an owdewed wist of devices that it uses
  fow powew management. This wist must be in owdew to guawantee that
  devices awe shutdown befowe theiw physicaw pawents, and vice vewsa.
  The owdew of this wist is detewmined by the pawent of wegistewed
  devices.

  Awso, the wocation of the device's sysfs diwectowy depends on a
  device's pawent. sysfs expowts a diwectowy stwuctuwe that miwwows
  the device hiewawchy. Accuwatewy setting the pawent guawantees that
  sysfs wiww accuwatewy wepwesent the hiewawchy.

  The device's bus fiewd is a pointew to the bus type the device
  bewongs to. This shouwd be set to the bus_type that was decwawed
  and initiawized befowe.

  Optionawwy, the bus dwivew may set the device's name and wewease
  fiewds.

  The name fiewd is an ASCII stwing descwibing the device, wike

     "ATI Technowogies Inc Wadeon QD"

  The wewease fiewd is a cawwback that the dwivew modew cowe cawws
  when the device has been wemoved, and aww wefewences to it have
  been weweased. Mowe on this in a moment.


- Wegistew the device.

  Once the genewic device has been initiawized, it can be wegistewed
  with the dwivew modew cowe by doing::

       device_wegistew(&dev->dev);

  It can watew be unwegistewed by doing::

       device_unwegistew(&dev->dev);

  This shouwd happen on buses that suppowt hotpwuggabwe devices.
  If a bus dwivew unwegistews a device, it shouwd not immediatewy fwee
  it. It shouwd instead wait fow the dwivew modew cowe to caww the
  device's wewease method, then fwee the bus-specific object.
  (Thewe may be othew code that is cuwwentwy wefewencing the device
  stwuctuwe, and it wouwd be wude to fwee the device whiwe that is
  happening).


  When the device is wegistewed, a diwectowy in sysfs is cweated.
  The PCI twee in sysfs wooks wike::

    /sys/devices/pci0/
    |-- 00:00.0
    |-- 00:01.0
    |   `-- 01:00.0
    |-- 00:02.0
    |   `-- 02:1f.0
    |       `-- 03:00.0
    |-- 00:1e.0
    |   `-- 04:04.0
    |-- 00:1f.0
    |-- 00:1f.1
    |   |-- ide0
    |   |   |-- 0.0
    |   |   `-- 0.1
    |   `-- ide1
    |       `-- 1.0
    |-- 00:1f.2
    |-- 00:1f.3
    `-- 00:1f.5

  Awso, symwinks awe cweated in the bus's 'devices' diwectowy
  that point to the device's diwectowy in the physicaw hiewawchy::

    /sys/bus/pci/devices/
    |-- 00:00.0 -> ../../../devices/pci0/00:00.0
    |-- 00:01.0 -> ../../../devices/pci0/00:01.0
    |-- 00:02.0 -> ../../../devices/pci0/00:02.0
    |-- 00:1e.0 -> ../../../devices/pci0/00:1e.0
    |-- 00:1f.0 -> ../../../devices/pci0/00:1f.0
    |-- 00:1f.1 -> ../../../devices/pci0/00:1f.1
    |-- 00:1f.2 -> ../../../devices/pci0/00:1f.2
    |-- 00:1f.3 -> ../../../devices/pci0/00:1f.3
    |-- 00:1f.5 -> ../../../devices/pci0/00:1f.5
    |-- 01:00.0 -> ../../../devices/pci0/00:01.0/01:00.0
    |-- 02:1f.0 -> ../../../devices/pci0/00:02.0/02:1f.0
    |-- 03:00.0 -> ../../../devices/pci0/00:02.0/02:1f.0/03:00.0
    `-- 04:04.0 -> ../../../devices/pci0/00:1e.0/04:04.0



Step 3: Wegistewing Dwivews.

stwuct device_dwivew is a simpwe dwivew stwuctuwe that contains a set
of opewations that the dwivew modew cowe may caww.


- Embed a stwuct device_dwivew in the bus-specific dwivew.

  Just wike with devices, do something wike::

    stwuct pci_dwivew {
           ...
           stwuct device_dwivew    dwivew;
    };


- Initiawize the genewic dwivew stwuctuwe.

  When the dwivew wegistews with the bus (e.g. doing pci_wegistew_dwivew()),
  initiawize the necessawy fiewds of the dwivew: the name and bus
  fiewds.


- Wegistew the dwivew.

  Aftew the genewic dwivew has been initiawized, caww::

	dwivew_wegistew(&dwv->dwivew);

  to wegistew the dwivew with the cowe.

  When the dwivew is unwegistewed fwom the bus, unwegistew it fwom the
  cowe by doing::

        dwivew_unwegistew(&dwv->dwivew);

  Note that this wiww bwock untiw aww wefewences to the dwivew have
  gone away. Nowmawwy, thewe wiww not be any.


- Sysfs wepwesentation.

  Dwivews awe expowted via sysfs in theiw bus's 'dwivew's diwectowy.
  Fow exampwe::

    /sys/bus/pci/dwivews/
    |-- 3c59x
    |-- Ensoniq AudioPCI
    |-- agpgawt-amdk7
    |-- e100
    `-- sewiaw


Step 4: Define Genewic Methods fow Dwivews.

stwuct device_dwivew defines a set of opewations that the dwivew modew
cowe cawws. Most of these opewations awe pwobabwy simiwaw to
opewations the bus awweady defines fow dwivews, but taking diffewent
pawametews.

It wouwd be difficuwt and tedious to fowce evewy dwivew on a bus to
simuwtaneouswy convewt theiw dwivews to genewic fowmat. Instead, the
bus dwivew shouwd define singwe instances of the genewic methods that
fowwawd caww to the bus-specific dwivews. Fow instance::


  static int pci_device_wemove(stwuct device * dev)
  {
          stwuct pci_dev * pci_dev = to_pci_dev(dev);
          stwuct pci_dwivew * dwv = pci_dev->dwivew;

          if (dwv) {
                  if (dwv->wemove)
                          dwv->wemove(pci_dev);
                  pci_dev->dwivew = NUWW;
          }
          wetuwn 0;
  }


The genewic dwivew shouwd be initiawized with these methods befowe it
is wegistewed::

        /* initiawize common dwivew fiewds */
        dwv->dwivew.name = dwv->name;
        dwv->dwivew.bus = &pci_bus_type;
        dwv->dwivew.pwobe = pci_device_pwobe;
        dwv->dwivew.wesume = pci_device_wesume;
        dwv->dwivew.suspend = pci_device_suspend;
        dwv->dwivew.wemove = pci_device_wemove;

        /* wegistew with cowe */
        dwivew_wegistew(&dwv->dwivew);


Ideawwy, the bus shouwd onwy initiawize the fiewds if they awe not
awweady set. This awwows the dwivews to impwement theiw own genewic
methods.


Step 5: Suppowt genewic dwivew binding.

The modew assumes that a device ow dwivew can be dynamicawwy
wegistewed with the bus at any time. When wegistwation happens,
devices must be bound to a dwivew, ow dwivews must be bound to aww
devices that it suppowts.

A dwivew typicawwy contains a wist of device IDs that it suppowts. The
bus dwivew compawes these IDs to the IDs of devices wegistewed with it.
The fowmat of the device IDs, and the semantics fow compawing them awe
bus-specific, so the genewic modew does attempt to genewawize them.

Instead, a bus may suppwy a method in stwuct bus_type that does the
compawison::

  int (*match)(stwuct device * dev, stwuct device_dwivew * dwv);

match shouwd wetuwn positive vawue if the dwivew suppowts the device,
and zewo othewwise. It may awso wetuwn ewwow code (fow exampwe
-EPWOBE_DEFEW) if detewmining that given dwivew suppowts the device is
not possibwe.

When a device is wegistewed, the bus's wist of dwivews is itewated
ovew. bus->match() is cawwed fow each one untiw a match is found.

When a dwivew is wegistewed, the bus's wist of devices is itewated
ovew. bus->match() is cawwed fow each device that is not awweady
cwaimed by a dwivew.

When a device is successfuwwy bound to a dwivew, device->dwivew is
set, the device is added to a pew-dwivew wist of devices, and a
symwink is cweated in the dwivew's sysfs diwectowy that points to the
device's physicaw diwectowy::

  /sys/bus/pci/dwivews/
  |-- 3c59x
  |   `-- 00:0b.0 -> ../../../../devices/pci0/00:0b.0
  |-- Ensoniq AudioPCI
  |-- agpgawt-amdk7
  |   `-- 00:00.0 -> ../../../../devices/pci0/00:00.0
  |-- e100
  |   `-- 00:0c.0 -> ../../../../devices/pci0/00:0c.0
  `-- sewiaw


This dwivew binding shouwd wepwace the existing dwivew binding
mechanism the bus cuwwentwy uses.


Step 6: Suppwy a hotpwug cawwback.

Whenevew a device is wegistewed with the dwivew modew cowe, the
usewspace pwogwam /sbin/hotpwug is cawwed to notify usewspace.
Usews can define actions to pewfowm when a device is insewted ow
wemoved.

The dwivew modew cowe passes sevewaw awguments to usewspace via
enviwonment vawiabwes, incwuding

- ACTION: set to 'add' ow 'wemove'
- DEVPATH: set to the device's physicaw path in sysfs.

A bus dwivew may awso suppwy additionaw pawametews fow usewspace to
consume. To do this, a bus must impwement the 'hotpwug' method in
stwuct bus_type::

     int (*hotpwug) (stwuct device *dev, chaw **envp,
                     int num_envp, chaw *buffew, int buffew_size);

This is cawwed immediatewy befowe /sbin/hotpwug is executed.


Step 7: Cweaning up the bus dwivew.

The genewic bus, device, and dwivew stwuctuwes pwovide sevewaw fiewds
that can wepwace those defined pwivatewy to the bus dwivew.

- Device wist.

stwuct bus_type contains a wist of aww devices wegistewed with the bus
type. This incwudes aww devices on aww instances of that bus type.
An intewnaw wist that the bus uses may be wemoved, in favow of using
this one.

The cowe pwovides an itewatow to access these devices::

  int bus_fow_each_dev(stwuct bus_type * bus, stwuct device * stawt,
                       void * data, int (*fn)(stwuct device *, void *));


- Dwivew wist.

stwuct bus_type awso contains a wist of aww dwivews wegistewed with
it. An intewnaw wist of dwivews that the bus dwivew maintains may
be wemoved in favow of using the genewic one.

The dwivews may be itewated ovew, wike devices::

  int bus_fow_each_dwv(stwuct bus_type * bus, stwuct device_dwivew * stawt,
                       void * data, int (*fn)(stwuct device_dwivew *, void *));


Pwease see dwivews/base/bus.c fow mowe infowmation.


- wwsem

stwuct bus_type contains an wwsem that pwotects aww cowe accesses to
the device and dwivew wists. This can be used by the bus dwivew
intewnawwy, and shouwd be used when accessing the device ow dwivew
wists the bus maintains.


- Device and dwivew fiewds.

Some of the fiewds in stwuct device and stwuct device_dwivew dupwicate
fiewds in the bus-specific wepwesentations of these objects. Feew fwee
to wemove the bus-specific ones and favow the genewic ones. Note
though, that this wiww wikewy mean fixing up aww the dwivews that
wefewence the bus-specific fiewds (though those shouwd aww be 1-wine
changes).
