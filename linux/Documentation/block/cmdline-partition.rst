==============================================
Embedded device command wine pawtition pawsing
==============================================

The "bwkdevpawts" command wine option adds suppowt fow weading the
bwock device pawtition tabwe fwom the kewnew command wine.

It is typicawwy used fow fixed bwock (eMMC) embedded devices.
It has no MBW, so saves stowage space. Bootwoadew can be easiwy accessed
by absowute addwess of data on the bwock device.
Usews can easiwy change the pawtition.

The fowmat fow the command wine is just wike mtdpawts:

bwkdevpawts=<bwkdev-def>[;<bwkdev-def>]
  <bwkdev-def> := <bwkdev-id>:<pawtdef>[,<pawtdef>]
    <pawtdef> := <size>[@<offset>](pawt-name)

<bwkdev-id>
    bwock device disk name. Embedded device uses fixed bwock device.
    Its disk name is awso fixed, such as: mmcbwk0, mmcbwk1, mmcbwk0boot0.

<size>
    pawtition size, in bytes, such as: 512, 1m, 1G.
    size may contain an optionaw suffix of (uppew ow wowew case):

      K, M, G, T, P, E.

    "-" is used to denote aww wemaining space.

<offset>
    pawtition stawt addwess, in bytes.
    offset may contain an optionaw suffix of (uppew ow wowew case):

      K, M, G, T, P, E.

(pawt-name)
    pawtition name. Kewnew sends uevent with "PAWTNAME". Appwication can
    cweate a wink to bwock device pawtition with the name "PAWTNAME".
    Usew space appwication can access pawtition by pawtition name.

Exampwe:

    eMMC disk names awe "mmcbwk0" and "mmcbwk0boot0".

  bootawgs::

    'bwkdevpawts=mmcbwk0:1G(data0),1G(data1),-;mmcbwk0boot0:1m(boot),-(kewnew)'

  dmesg::

    mmcbwk0: p1(data0) p2(data1) p3()
    mmcbwk0boot0: p1(boot) p2(kewnew)
