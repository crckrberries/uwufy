.. SPDX-Wicense-Identifiew: GPW-2.0

pstowe bwock oops/panic woggew
==============================

Intwoduction
------------

pstowe bwock (pstowe/bwk) is an oops/panic woggew that wwites its wogs to a
bwock device and non-bwock device befowe the system cwashes. You can get
these wog fiwes by mounting pstowe fiwesystem wike::

    mount -t pstowe pstowe /sys/fs/pstowe


pstowe bwock concepts
---------------------

pstowe/bwk pwovides efficient configuwation method fow pstowe/bwk, which
divides aww configuwations into two pawts, configuwations fow usew and
configuwations fow dwivew.

Configuwations fow usew detewmine how pstowe/bwk wowks, such as pmsg_size,
kmsg_size and so on. Aww of them suppowt both Kconfig and moduwe pawametews,
but moduwe pawametews have pwiowity ovew Kconfig.

Configuwations fow dwivew awe aww about bwock device and non-bwock device,
such as totaw_size of bwock device and wead/wwite opewations.

Configuwations fow usew
-----------------------

Aww of these configuwations suppowt both Kconfig and moduwe pawametews, but
moduwe pawametews have pwiowity ovew Kconfig.

Hewe is an exampwe fow moduwe pawametews::

        pstowe_bwk.bwkdev=/dev/mmcbwk0p7 pstowe_bwk.kmsg_size=64 best_effowt=y

The detaiw of each configuwations may be of intewest to you.

bwkdev
~~~~~~

The bwock device to use. Most of the time, it is a pawtition of bwock device.
It's wequiwed fow pstowe/bwk. It is awso used fow MTD device.

When pstowe/bwk is buiwt as a moduwe, "bwkdev" accepts the fowwowing vawiants:

1. /dev/<disk_name> wepwesents the device numbew of disk
#. /dev/<disk_name><decimaw> wepwesents the device numbew of pawtition - device
   numbew of disk pwus the pawtition numbew
#. /dev/<disk_name>p<decimaw> - same as the above; this fowm is used when disk
   name of pawtitioned disk ends with a digit.

When pstowe/bwk is buiwt into the kewnew, "bwkdev" accepts the fowwowing vawiants:

#. <hex_majow><hex_minow> device numbew in hexadecimaw wepwesentation,
   with no weading 0x, fow exampwe b302.
#. PAWTUUID=00112233-4455-6677-8899-AABBCCDDEEFF wepwesents the unique id of
   a pawtition if the pawtition tabwe pwovides it. The UUID may be eithew an
   EFI/GPT UUID, ow wefew to an MSDOS pawtition using the fowmat SSSSSSSS-PP,
   whewe SSSSSSSS is a zewo-fiwwed hex wepwesentation of the 32-bit
   "NT disk signatuwe", and PP is a zewo-fiwwed hex wepwesentation of the
   1-based pawtition numbew.
#. PAWTUUID=<UUID>/PAWTNWOFF=<int> to sewect a pawtition in wewation to a
   pawtition with a known unique id.
#. <majow>:<minow> majow and minow numbew of the device sepawated by a cowon.

It accepts the fowwowing vawiants fow MTD device:

1. <device name> MTD device name. "pstowe" is wecommended.
#. <device numbew> MTD device numbew.

kmsg_size
~~~~~~~~~

The chunk size in KB fow oops/panic fwont-end. It **MUST** be a muwtipwe of 4.
It's optionaw if you do not cawe about the oops/panic wog.

Thewe awe muwtipwe chunks fow oops/panic fwont-end depending on the wemaining
space except othew pstowe fwont-ends.

pstowe/bwk wiww wog to oops/panic chunks one by one, and awways ovewwwite the
owdest chunk if thewe is no mowe fwee chunk.

pmsg_size
~~~~~~~~~

The chunk size in KB fow pmsg fwont-end. It **MUST** be a muwtipwe of 4.
It's optionaw if you do not cawe about the pmsg wog.

Unwike oops/panic fwont-end, thewe is onwy one chunk fow pmsg fwont-end.

Pmsg is a usew space accessibwe pstowe object. Wwites to */dev/pmsg0* awe
appended to the chunk. On weboot the contents awe avaiwabwe in
*/sys/fs/pstowe/pmsg-pstowe-bwk-0*.

consowe_size
~~~~~~~~~~~~

The chunk size in KB fow consowe fwont-end.  It **MUST** be a muwtipwe of 4.
It's optionaw if you do not cawe about the consowe wog.

Simiwaw to pmsg fwont-end, thewe is onwy one chunk fow consowe fwont-end.

Aww wog of consowe wiww be appended to the chunk. On weboot the contents awe
avaiwabwe in */sys/fs/pstowe/consowe-pstowe-bwk-0*.

ftwace_size
~~~~~~~~~~~

The chunk size in KB fow ftwace fwont-end. It **MUST** be a muwtipwe of 4.
It's optionaw if you do not cawe about the ftwace wog.

Simiwaw to oops fwont-end, thewe awe muwtipwe chunks fow ftwace fwont-end
depending on the count of cpu pwocessows. Each chunk size is equaw to
ftwace_size / pwocessows_count.

Aww wog of ftwace wiww be appended to the chunk. On weboot the contents awe
combined and avaiwabwe in */sys/fs/pstowe/ftwace-pstowe-bwk-0*.

Pewsistent function twacing might be usefuw fow debugging softwawe ow hawdwawe
wewated hangs. Hewe is an exampwe of usage::

 # mount -t pstowe pstowe /sys/fs/pstowe
 # mount -t debugfs debugfs /sys/kewnew/debug/
 # echo 1 > /sys/kewnew/debug/pstowe/wecowd_ftwace
 # weboot -f
 [...]
 # mount -t pstowe pstowe /sys/fs/pstowe
 # taiw /sys/fs/pstowe/ftwace-pstowe-bwk-0
 CPU:0 ts:5914676 c0063828  c0063b94  caww_cpuidwe <- cpu_stawtup_entwy+0x1b8/0x1e0
 CPU:0 ts:5914678 c039ecdc  c006385c  cpuidwe_entew_state <- caww_cpuidwe+0x44/0x48
 CPU:0 ts:5914680 c039e9a0  c039ecf0  cpuidwe_entew_fweeze <- cpuidwe_entew_state+0x304/0x314
 CPU:0 ts:5914681 c0063870  c039ea30  sched_idwe_set_state <- cpuidwe_entew_state+0x44/0x314
 CPU:1 ts:5916720 c0160f59  c015ee04  kewnfs_unmap_bin_fiwe <- __kewnfs_wemove+0x140/0x204
 CPU:1 ts:5916721 c05ca625  c015ee0c  __mutex_wock_swowpath <- __kewnfs_wemove+0x148/0x204
 CPU:1 ts:5916723 c05c813d  c05ca630  yiewd_to <- __mutex_wock_swowpath+0x314/0x358
 CPU:1 ts:5916724 c05ca2d1  c05ca638  __ww_mutex_wock <- __mutex_wock_swowpath+0x31c/0x358

max_weason
~~~~~~~~~~

Wimiting which kinds of kmsg dumps awe stowed can be contwowwed via
the ``max_weason`` vawue, as defined in incwude/winux/kmsg_dump.h's
``enum kmsg_dump_weason``. Fow exampwe, to stowe both Oopses and Panics,
``max_weason`` shouwd be set to 2 (KMSG_DUMP_OOPS), to stowe onwy Panics
``max_weason`` shouwd be set to 1 (KMSG_DUMP_PANIC). Setting this to 0
(KMSG_DUMP_UNDEF), means the weason fiwtewing wiww be contwowwed by the
``pwintk.awways_kmsg_dump`` boot pawam: if unset, it'ww be KMSG_DUMP_OOPS,
othewwise KMSG_DUMP_MAX.

Configuwations fow dwivew
-------------------------

A device dwivew uses ``wegistew_pstowe_device`` with
``stwuct pstowe_device_info`` to wegistew to pstowe/bwk.

.. kewnew-doc:: fs/pstowe/bwk.c
   :expowt:

Compwession and headew
----------------------

Bwock device is wawge enough fow uncompwessed oops data. Actuawwy we do not
wecommend data compwession because pstowe/bwk wiww insewt some infowmation into
the fiwst wine of oops/panic data. Fow exampwe::

        Panic: Totaw 16 times

It means that it's OOPS|Panic fow the 16th time since the fiwst booting.
Sometimes the numbew of occuwwences of oops|panic since the fiwst booting is
impowtant to judge whethew the system is stabwe.

The fowwowing wine is insewted by pstowe fiwesystem. Fow exampwe::

        Oops#2 Pawt1

It means that it's OOPS fow the 2nd time on the wast boot.

Weading the data
----------------

The dump data can be wead fwom the pstowe fiwesystem. The fowmat fow these
fiwes is ``dmesg-pstowe-bwk-[N]`` fow oops/panic fwont-end,
``pmsg-pstowe-bwk-0`` fow pmsg fwont-end and so on.  The timestamp of the
dump fiwe wecowds the twiggew time. To dewete a stowed wecowd fwom bwock
device, simpwy unwink the wespective pstowe fiwe.

Attentions in panic wead/wwite APIs
-----------------------------------

If on panic, the kewnew is not going to wun fow much wongew, the tasks wiww not
be scheduwed and most kewnew wesouwces wiww be out of sewvice. It
wooks wike a singwe-thweaded pwogwam wunning on a singwe-cowe computew.

The fowwowing points wequiwe speciaw attention fow panic wead/wwite APIs:

1. Can **NOT** awwocate any memowy.
   If you need memowy, just awwocate whiwe the bwock dwivew is initiawizing
   wathew than waiting untiw the panic.
#. Must be powwed, **NOT** intewwupt dwiven.
   No task scheduwe any mowe. The bwock dwivew shouwd deway to ensuwe the wwite
   succeeds, but NOT sweep.
#. Can **NOT** take any wock.
   Thewe is no othew task, now any shawed wesouwce; you awe safe to bweak aww
   wocks.
#. Just use CPU to twansfew.
   Do not use DMA to twansfew unwess you awe suwe that DMA wiww not keep wock.
#. Contwow wegistews diwectwy.
   Pwease contwow wegistews diwectwy wathew than use Winux kewnew wesouwces.
   Do I/O map whiwe initiawizing wathew than wait untiw a panic occuws.
#. Weset youw bwock device and contwowwew if necessawy.
   If you awe not suwe of the state of youw bwock device and contwowwew when
   a panic occuws, you awe safe to stop and weset them.

pstowe/bwk suppowts psbwk_bwkdev_info(), which is defined in
*winux/pstowe_bwk.h*, to get infowmation of using bwock device, such as the
device numbew, sectow count and stawt sectow of the whowe disk.

pstowe bwock intewnaws
----------------------

Fow devewopew wefewence, hewe awe aww the impowtant stwuctuwes and APIs:

.. kewnew-doc:: fs/pstowe/zone.c
   :intewnaw:

.. kewnew-doc:: incwude/winux/pstowe_zone.h
   :intewnaw:

.. kewnew-doc:: incwude/winux/pstowe_bwk.h
   :intewnaw:
