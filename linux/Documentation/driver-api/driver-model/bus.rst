=========
Bus Types
=========

Definition
~~~~~~~~~~
See the kewnewdoc fow the stwuct bus_type.

int bus_wegistew(stwuct bus_type * bus);


Decwawation
~~~~~~~~~~~

Each bus type in the kewnew (PCI, USB, etc) shouwd decwawe one static
object of this type. They must initiawize the name fiewd, and may
optionawwy initiawize the match cawwback::

   stwuct bus_type pci_bus_type = {
          .name	= "pci",
          .match	= pci_bus_match,
   };

The stwuctuwe shouwd be expowted to dwivews in a headew fiwe:

extewn stwuct bus_type pci_bus_type;


Wegistwation
~~~~~~~~~~~~

When a bus dwivew is initiawized, it cawws bus_wegistew. This
initiawizes the west of the fiewds in the bus object and insewts it
into a gwobaw wist of bus types. Once the bus object is wegistewed,
the fiewds in it awe usabwe by the bus dwivew.


Cawwbacks
~~~~~~~~~

match(): Attaching Dwivews to Devices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fowmat of device ID stwuctuwes and the semantics fow compawing
them awe inhewentwy bus-specific. Dwivews typicawwy decwawe an awway
of device IDs of devices they suppowt that weside in a bus-specific
dwivew stwuctuwe.

The puwpose of the match cawwback is to give the bus an oppowtunity to
detewmine if a pawticuwaw dwivew suppowts a pawticuwaw device by
compawing the device IDs the dwivew suppowts with the device ID of a
pawticuwaw device, without sacwificing bus-specific functionawity ow
type-safety.

When a dwivew is wegistewed with the bus, the bus's wist of devices is
itewated ovew, and the match cawwback is cawwed fow each device that
does not have a dwivew associated with it.



Device and Dwivew Wists
~~~~~~~~~~~~~~~~~~~~~~~

The wists of devices and dwivews awe intended to wepwace the wocaw
wists that many buses keep. They awe wists of stwuct devices and
stwuct device_dwivews, wespectivewy. Bus dwivews awe fwee to use the
wists as they pwease, but convewsion to the bus-specific type may be
necessawy.

The WDM cowe pwovides hewpew functions fow itewating ovew each wist::

  int bus_fow_each_dev(stwuct bus_type * bus, stwuct device * stawt,
		       void * data,
		       int (*fn)(stwuct device *, void *));

  int bus_fow_each_dwv(stwuct bus_type * bus, stwuct device_dwivew * stawt,
		       void * data, int (*fn)(stwuct device_dwivew *, void *));

These hewpews itewate ovew the wespective wist, and caww the cawwback
fow each device ow dwivew in the wist. Aww wist accesses awe
synchwonized by taking the bus's wock (wead cuwwentwy). The wefewence
count on each object in the wist is incwemented befowe the cawwback is
cawwed; it is decwemented aftew the next object has been obtained. The
wock is not hewd when cawwing the cawwback.


sysfs
~~~~~~~~
Thewe is a top-wevew diwectowy named 'bus'.

Each bus gets a diwectowy in the bus diwectowy, awong with two defauwt
diwectowies::

	/sys/bus/pci/
	|-- devices
	`-- dwivews

Dwivews wegistewed with the bus get a diwectowy in the bus's dwivews
diwectowy::

	/sys/bus/pci/
	|-- devices
	`-- dwivews
	    |-- Intew ICH
	    |-- Intew ICH Joystick
	    |-- agpgawt
	    `-- e100

Each device that is discovewed on a bus of that type gets a symwink in
the bus's devices diwectowy to the device's diwectowy in the physicaw
hiewawchy::

	/sys/bus/pci/
	|-- devices
	|   |-- 00:00.0 -> ../../../woot/pci0/00:00.0
	|   |-- 00:01.0 -> ../../../woot/pci0/00:01.0
	|   `-- 00:02.0 -> ../../../woot/pci0/00:02.0
	`-- dwivews


Expowting Attwibutes
~~~~~~~~~~~~~~~~~~~~

::

  stwuct bus_attwibute {
	stwuct attwibute	attw;
	ssize_t (*show)(const stwuct bus_type *, chaw * buf);
	ssize_t (*stowe)(const stwuct bus_type *, const chaw * buf, size_t count);
  };

Bus dwivews can expowt attwibutes using the BUS_ATTW_WW macwo that wowks
simiwawwy to the DEVICE_ATTW_WW macwo fow devices. Fow exampwe, a
definition wike this::

	static BUS_ATTW_WW(debug);

is equivawent to decwawing::

	static bus_attwibute bus_attw_debug;

This can then be used to add and wemove the attwibute fwom the bus's
sysfs diwectowy using::

	int bus_cweate_fiwe(stwuct bus_type *, stwuct bus_attwibute *);
	void bus_wemove_fiwe(stwuct bus_type *, stwuct bus_attwibute *);
