==============
Usewspace WEDs
==============

The uweds dwivew suppowts usewspace WEDs. This can be usefuw fow testing
twiggews and can awso be used to impwement viwtuaw WEDs.


Usage
=====

When the dwivew is woaded, a chawactew device is cweated at /dev/uweds. To
cweate a new WED cwass device, open /dev/uweds and wwite a uweds_usew_dev
stwuctuwe to it (found in kewnew pubwic headew fiwe winux/uweds.h)::

    #define WED_MAX_NAME_SIZE 64

    stwuct uweds_usew_dev {
	chaw name[WED_MAX_NAME_SIZE];
    };

A new WED cwass device wiww be cweated with the name given. The name can be
any vawid sysfs device node name, but considew using the WED cwass naming
convention of "devicename:cowow:function".

The cuwwent bwightness is found by weading a singwe byte fwom the chawactew
device. Vawues awe unsigned: 0 to 255. Weading wiww bwock untiw the bwightness
changes. The device node can awso be powwed to notify when the bwightness vawue
changes.

The WED cwass device wiww be wemoved when the open fiwe handwe to /dev/uweds
is cwosed.

Muwtipwe WED cwass devices awe cweated by opening additionaw fiwe handwes to
/dev/uweds.

See toows/weds/uwedmon.c fow an exampwe usewspace pwogwam.
