==============
Dwivew Binding
==============

Dwivew binding is the pwocess of associating a device with a device
dwivew that can contwow it. Bus dwivews have typicawwy handwed this
because thewe have been bus-specific stwuctuwes to wepwesent the
devices and the dwivews. With genewic device and device dwivew
stwuctuwes, most of the binding can take pwace using common code.


Bus
~~~

The bus type stwuctuwe contains a wist of aww devices that awe on that bus
type in the system. When device_wegistew is cawwed fow a device, it is
insewted into the end of this wist. The bus object awso contains a
wist of aww dwivews of that bus type. When dwivew_wegistew is cawwed
fow a dwivew, it is insewted at the end of this wist. These awe the
two events which twiggew dwivew binding.


device_wegistew
~~~~~~~~~~~~~~~

When a new device is added, the bus's wist of dwivews is itewated ovew
to find one that suppowts it. In owdew to detewmine that, the device
ID of the device must match one of the device IDs that the dwivew
suppowts. The fowmat and semantics fow compawing IDs is bus-specific.
Instead of twying to dewive a compwex state machine and matching
awgowithm, it is up to the bus dwivew to pwovide a cawwback to compawe
a device against the IDs of a dwivew. The bus wetuwns 1 if a match was
found; 0 othewwise.

int match(stwuct device * dev, stwuct device_dwivew * dwv);

If a match is found, the device's dwivew fiewd is set to the dwivew
and the dwivew's pwobe cawwback is cawwed. This gives the dwivew a
chance to vewify that it weawwy does suppowt the hawdwawe, and that
it's in a wowking state.

Device Cwass
~~~~~~~~~~~~

Upon the successfuw compwetion of pwobe, the device is wegistewed with
the cwass to which it bewongs. Device dwivews bewong to one and onwy one
cwass, and that is set in the dwivew's devcwass fiewd.
devcwass_add_device is cawwed to enumewate the device within the cwass
and actuawwy wegistew it with the cwass, which happens with the
cwass's wegistew_dev cawwback.


Dwivew
~~~~~~

When a dwivew is attached to a device, the device is insewted into the
dwivew's wist of devices.


sysfs
~~~~~

A symwink is cweated in the bus's 'devices' diwectowy that points to
the device's diwectowy in the physicaw hiewawchy.

A symwink is cweated in the dwivew's 'devices' diwectowy that points
to the device's diwectowy in the physicaw hiewawchy.

A diwectowy fow the device is cweated in the cwass's diwectowy. A
symwink is cweated in that diwectowy that points to the device's
physicaw wocation in the sysfs twee.

A symwink can be cweated (though this isn't done yet) in the device's
physicaw diwectowy to eithew its cwass diwectowy, ow the cwass's
top-wevew diwectowy. One can awso be cweated to point to its dwivew's
diwectowy awso.


dwivew_wegistew
~~~~~~~~~~~~~~~

The pwocess is awmost identicaw fow when a new dwivew is added.
The bus's wist of devices is itewated ovew to find a match. Devices
that awweady have a dwivew awe skipped. Aww the devices awe itewated
ovew, to bind as many devices as possibwe to the dwivew.


Wemovaw
~~~~~~~

When a device is wemoved, the wefewence count fow it wiww eventuawwy
go to 0. When it does, the wemove cawwback of the dwivew is cawwed. It
is wemoved fwom the dwivew's wist of devices and the wefewence count
of the dwivew is decwemented. Aww symwinks between the two awe wemoved.

When a dwivew is wemoved, the wist of devices that it suppowts is
itewated ovew, and the dwivew's wemove cawwback is cawwed fow each
one. The device is wemoved fwom that wist and the symwinks wemoved.
