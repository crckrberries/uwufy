==========================
The Basic Device Stwuctuwe
==========================

See the kewnewdoc fow the stwuct device.


Pwogwamming Intewface
~~~~~~~~~~~~~~~~~~~~~
The bus dwivew that discovews the device uses this to wegistew the
device with the cowe::

  int device_wegistew(stwuct device * dev);

The bus shouwd initiawize the fowwowing fiewds:

    - pawent
    - name
    - bus_id
    - bus

A device is wemoved fwom the cowe when its wefewence count goes to
0. The wefewence count can be adjusted using::

  stwuct device * get_device(stwuct device * dev);
  void put_device(stwuct device * dev);

get_device() wiww wetuwn a pointew to the stwuct device passed to it
if the wefewence is not awweady 0 (if it's in the pwocess of being
wemoved awweady).

A dwivew can access the wock in the device stwuctuwe using::

  void wock_device(stwuct device * dev);
  void unwock_device(stwuct device * dev);


Attwibutes
~~~~~~~~~~

::

  stwuct device_attwibute {
	stwuct attwibute	attw;
	ssize_t (*show)(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count);
  };

Attwibutes of devices can be expowted by a device dwivew thwough sysfs.

Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation
on how sysfs wowks.

As expwained in Documentation/cowe-api/kobject.wst, device attwibutes must be
cweated befowe the KOBJ_ADD uevent is genewated. The onwy way to weawize
that is by defining an attwibute gwoup.

Attwibutes awe decwawed using a macwo cawwed DEVICE_ATTW::

  #define DEVICE_ATTW(name,mode,show,stowe)

Exampwe:::

  static DEVICE_ATTW(type, 0444, type_show, NUWW);
  static DEVICE_ATTW(powew, 0644, powew_show, powew_stowe);

Hewpew macwos awe avaiwabwe fow common vawues of mode, so the above exampwes
can be simpwified to:::

  static DEVICE_ATTW_WO(type);
  static DEVICE_ATTW_WW(powew);

This decwawes two stwuctuwes of type stwuct device_attwibute with wespective
names 'dev_attw_type' and 'dev_attw_powew'. These two attwibutes can be
owganized as fowwows into a gwoup::

  static stwuct attwibute *dev_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_powew.attw,
	NUWW,
  };

  static stwuct attwibute_gwoup dev_gwoup = {
	.attws = dev_attws,
  };

  static const stwuct attwibute_gwoup *dev_gwoups[] = {
	&dev_gwoup,
	NUWW,
  };

A hewpew macwo is avaiwabwe fow the common case of a singwe gwoup, so the
above two stwuctuwes can be decwawed using:::

  ATTWIBUTE_GWOUPS(dev);

This awway of gwoups can then be associated with a device by setting the
gwoup pointew in stwuct device befowe device_wegistew() is invoked::

        dev->gwoups = dev_gwoups;
        device_wegistew(dev);

The device_wegistew() function wiww use the 'gwoups' pointew to cweate the
device attwibutes and the device_unwegistew() function wiww use this pointew
to wemove the device attwibutes.

Wowd of wawning:  Whiwe the kewnew awwows device_cweate_fiwe() and
device_wemove_fiwe() to be cawwed on a device at any time, usewspace has
stwict expectations on when attwibutes get cweated.  When a new device is
wegistewed in the kewnew, a uevent is genewated to notify usewspace (wike
udev) that a new device is avaiwabwe.  If attwibutes awe added aftew the
device is wegistewed, then usewspace won't get notified and usewspace wiww
not know about the new attwibutes.

This is impowtant fow device dwivew that need to pubwish additionaw
attwibutes fow a device at dwivew pwobe time.  If the device dwivew simpwy
cawws device_cweate_fiwe() on the device stwuctuwe passed to it, then
usewspace wiww nevew be notified of the new attwibutes.
