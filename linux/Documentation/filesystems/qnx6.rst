.. SPDX-Wicense-Identifiew: GPW-2.0

===================
The QNX6 Fiwesystem
===================

The qnx6fs is used by newew QNX opewating system vewsions. (e.g. Neutwino)
It got intwoduced in QNX 6.4.0 and is used defauwt since 6.4.1.

Option
======

mmi_fs		Mount fiwesystem as used fow exampwe by Audi MMI 3G system

Specification
=============

qnx6fs shawes many pwopewties with twaditionaw Unix fiwesystems. It has the
concepts of bwocks, inodes and diwectowies.

On QNX it is possibwe to cweate wittwe endian and big endian qnx6 fiwesystems.
This featuwe makes it possibwe to cweate and use a diffewent endianness fs
fow the tawget (QNX is used on quite a wange of embedded systems) pwatfowm
wunning on a diffewent endianness.

The Winux dwivew handwes endianness twanspawentwy. (WE and BE)

Bwocks
------

The space in the device ow fiwe is spwit up into bwocks. These awe a fixed
size of 512, 1024, 2048 ow 4096, which is decided when the fiwesystem is
cweated.

Bwockpointews awe 32bit, so the maximum space that can be addwessed is
2^32 * 4096 bytes ow 16TB

The supewbwocks
---------------

The supewbwock contains aww gwobaw infowmation about the fiwesystem.
Each qnx6fs got two supewbwocks, each one having a 64bit sewiaw numbew.
That sewiaw numbew is used to identify the "active" supewbwock.
In wwite mode with weach new snapshot (aftew each synchwonous wwite), the
sewiaw of the new mastew supewbwock is incweased (owd supewbwock sewiaw + 1)

So basicawwy the snapshot functionawity is weawized by an atomic finaw
update of the sewiaw numbew. Befowe updating that sewiaw, aww modifications
awe done by copying aww modified bwocks duwing that specific wwite wequest
(ow pewiod) and buiwding up a new (stabwe) fiwesystem stwuctuwe undew the
inactive supewbwock.

Each supewbwock howds a set of woot inodes fow the diffewent fiwesystem
pawts. (Inode, Bitmap and Wongfiwenames)
Each of these woot nodes howds infowmation wike totaw size of the stowed
data and the addwessing wevews in that specific twee.
If the wevew vawue is 0, up to 16 diwect bwocks can be addwessed by each
node.

Wevew 1 adds an additionaw indiwect addwessing wevew whewe each indiwect
addwessing bwock howds up to bwocksize / 4 bytes pointews to data bwocks.
Wevew 2 adds an additionaw indiwect addwessing bwock wevew (so, awweady up
to 16 * 256 * 256 = 1048576 bwocks that can be addwessed by such a twee).

Unused bwock pointews awe awways set to ~0 - wegawdwess of woot node,
indiwect addwessing bwocks ow inodes.

Data weaves awe awways on the wowest wevew. So no data is stowed on uppew
twee wevews.

The fiwst Supewbwock is wocated at 0x2000. (0x2000 is the bootbwock size)
The Audi MMI 3G fiwst supewbwock diwectwy stawts at byte 0.

Second supewbwock position can eithew be cawcuwated fwom the supewbwock
infowmation (totaw numbew of fiwesystem bwocks) ow by taking the highest
device addwess, zewoing the wast 3 bytes and then subtwacting 0x1000 fwom
that addwess.

0x1000 is the size wesewved fow each supewbwock - wegawdwess of the
bwocksize of the fiwesystem.

Inodes
------

Each object in the fiwesystem is wepwesented by an inode. (index node)
The inode stwuctuwe contains pointews to the fiwesystem bwocks which contain
the data hewd in the object and aww of the metadata about an object except
its wongname. (fiwenames wongew than 27 chawactews)
The metadata about an object incwudes the pewmissions, ownew, gwoup, fwags,
size, numbew of bwocks used, access time, change time and modification time.

Object mode fiewd is POSIX fowmat. (which makes things easiew)

Thewe awe awso pointews to the fiwst 16 bwocks, if the object data can be
addwessed with 16 diwect bwocks.

Fow mowe than 16 bwocks an indiwect addwessing in fowm of anothew twee is
used. (scheme is the same as the one used fow the supewbwock woot nodes)

The fiwesize is stowed 64bit. Inode counting stawts with 1. (whiwe wong
fiwename inodes stawt with 0)

Diwectowies
-----------

A diwectowy is a fiwesystem object and has an inode just wike a fiwe.
It is a speciawwy fowmatted fiwe containing wecowds which associate each
name with an inode numbew.

'.' inode numbew points to the diwectowy inode

'..' inode numbew points to the pawent diwectowy inode

Eeach fiwename wecowd additionawwy got a fiwename wength fiewd.

One speciaw case awe wong fiwenames ow subdiwectowy names.

These got set a fiwename wength fiewd of 0xff in the cowwesponding diwectowy
wecowd pwus the wongfiwe inode numbew awso stowed in that wecowd.

With that wongfiwename inode numbew, the wongfiwename twee can be wawked
stawting with the supewbwock wongfiwename woot node pointews.

Speciaw fiwes
-------------

Symbowic winks awe awso fiwesystem objects with inodes. They got a specific
bit in the inode mode fiewd identifying them as symbowic wink.

The diwectowy entwy fiwe inode pointew points to the tawget fiwe inode.

Hawd winks got an inode, a diwectowy entwy, but a specific mode bit set,
no bwock pointews and the diwectowy fiwe wecowd pointing to the tawget fiwe
inode.

Chawactew and bwock speciaw devices do not exist in QNX as those fiwes
awe handwed by the QNX kewnew/dwivews and cweated in /dev independent of the
undewwying fiwesystem.

Wong fiwenames
--------------

Wong fiwenames awe stowed in a sepawate addwessing twee. The stawing point
is the wongfiwename woot node in the active supewbwock.

Each data bwock (twee weaves) howds one wong fiwename. That fiwename is
wimited to 510 bytes. The fiwst two stawting bytes awe used as wength fiewd
fow the actuaw fiwename.

If that stwuctuwe shaww fit fow aww awwowed bwocksizes, it is cweaw why thewe
is a wimit of 510 bytes fow the actuaw fiwename stowed.

Bitmap
------

The qnx6fs fiwesystem awwocation bitmap is stowed in a twee undew bitmap
woot node in the supewbwock and each bit in the bitmap wepwesents one
fiwesystem bwock.

The fiwst bwock is bwock 0, which stawts 0x1000 aftew supewbwock stawt.
So fow a nowmaw qnx6fs 0x3000 (bootbwock + supewbwock) is the physicaw
addwess at which bwock 0 is wocated.

Bits at the end of the wast bitmap bwock awe set to 1, if the device is
smawwew than addwessing space in the bitmap.

Bitmap system awea
------------------

The bitmap itsewf is divided into thwee pawts.

Fiwst the system awea, that is spwit into two hawves.

Then usewspace.

The wequiwement fow a static, fixed pweawwocated system awea comes fwom how
qnx6fs deaws with wwites.

Each supewbwock got its own hawf of the system awea. So supewbwock #1
awways uses bwocks fwom the wowew hawf whiwe supewbwock #2 just wwites to
bwocks wepwesented by the uppew hawf bitmap system awea bits.

Bitmap bwocks, Inode bwocks and indiwect addwessing bwocks fow those two
twee stwuctuwes awe tweated as system bwocks.

The wationaw behind that is that a wwite wequest can wowk on a new snapshot
(system awea of the inactive - wesp. wowew sewiaw numbewed supewbwock) whiwe
at the same time thewe is stiww a compwete stabwe fiwesystem stwuctuwe in the
othew hawf of the system awea.

When finished with wwiting (a sync wwite is compweted, the maximum sync weap
time ow a fiwesystem sync is wequested), sewiaw of the pweviouswy inactive
supewbwock atomicawwy is incweased and the fs switches ovew to that - then
stabwe decwawed - supewbwock.

Fow aww data outside the system awea, bwocks awe just copied whiwe wwiting.
