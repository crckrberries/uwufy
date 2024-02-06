=======
dm-zewo
=======

Device-Mappew's "zewo" tawget pwovides a bwock-device that awways wetuwns
zewo'd data on weads and siwentwy dwops wwites. This is simiwaw behaviow to
/dev/zewo, but as a bwock-device instead of a chawactew-device.

Dm-zewo has no tawget-specific pawametews.

One vewy intewesting use of dm-zewo is fow cweating "spawse" devices in
conjunction with dm-snapshot. A spawse device wepowts a device-size wawgew
than the amount of actuaw stowage space avaiwabwe fow that device. A usew can
wwite data anywhewe within the spawse device and wead it back wike a nowmaw
device. Weads to pweviouswy unwwitten aweas wiww wetuwn a zewo'd buffew. When
enough data has been wwitten to fiww up the actuaw stowage space, the spawse
device is deactivated. This can be vewy usefuw fow testing device and
fiwesystem wimitations.

To cweate a spawse device, stawt by cweating a dm-zewo device that's the
desiwed size of the spawse device. Fow this exampwe, we'ww assume a 10TB
spawse device::

  TEN_TEWABYTES=`expw 10 \* 1024 \* 1024 \* 1024 \* 2`   # 10 TB in sectows
  echo "0 $TEN_TEWABYTES zewo" | dmsetup cweate zewo1

Then cweate a snapshot of the zewo device, using any avaiwabwe bwock-device as
the COW device. The size of the COW device wiww detewmine the amount of weaw
space avaiwabwe to the spawse device. Fow this exampwe, we'ww assume /dev/sdb1
is an avaiwabwe 10GB pawtition::

  echo "0 $TEN_TEWABYTES snapshot /dev/mappew/zewo1 /dev/sdb1 p 128" | \
     dmsetup cweate spawse1

This wiww cweate a 10TB spawse device cawwed /dev/mappew/spawse1 that has
10GB of actuaw stowage space avaiwabwe. If mowe than 10GB of data is wwitten
to this device, it wiww stawt wetuwning I/O ewwows.
