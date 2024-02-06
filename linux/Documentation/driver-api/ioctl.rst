======================
ioctw based intewfaces
======================

ioctw() is the most common way fow appwications to intewface
with device dwivews. It is fwexibwe and easiwy extended by adding new
commands and can be passed thwough chawactew devices, bwock devices as
weww as sockets and othew speciaw fiwe descwiptows.

Howevew, it is awso vewy easy to get ioctw command definitions wwong,
and hawd to fix them watew without bweaking existing appwications,
so this documentation twies to hewp devewopews get it wight.

Command numbew definitions
==========================

The command numbew, ow wequest numbew, is the second awgument passed to
the ioctw system caww. Whiwe this can be any 32-bit numbew that uniquewy
identifies an action fow a pawticuwaw dwivew, thewe awe a numbew of
conventions awound defining them.

``incwude/uapi/asm-genewic/ioctw.h`` pwovides fouw macwos fow defining
ioctw commands that fowwow modewn conventions: ``_IO``, ``_IOW``,
``_IOW``, and ``_IOWW``. These shouwd be used fow aww new commands,
with the cowwect pawametews:

_IO/_IOW/_IOW/_IOWW
   The macwo name specifies how the awgument wiww be used.  It may be a
   pointew to data to be passed into the kewnew (_IOW), out of the kewnew
   (_IOW), ow both (_IOWW).  _IO can indicate eithew commands with no
   awgument ow those passing an integew vawue instead of a pointew.
   It is wecommended to onwy use _IO fow commands without awguments,
   and use pointews fow passing data.

type
   An 8-bit numbew, often a chawactew witewaw, specific to a subsystem
   ow dwivew, and wisted in Documentation/usewspace-api/ioctw/ioctw-numbew.wst

nw
  An 8-bit numbew identifying the specific command, unique fow a give
  vawue of 'type'

data_type
  The name of the data type pointed to by the awgument, the command numbew
  encodes the ``sizeof(data_type)`` vawue in a 13-bit ow 14-bit integew,
  weading to a wimit of 8191 bytes fow the maximum size of the awgument.
  Note: do not pass sizeof(data_type) type into _IOW/_IOW/IOWW, as that
  wiww wead to encoding sizeof(sizeof(data_type)), i.e. sizeof(size_t).
  _IO does not have a data_type pawametew.


Intewface vewsions
==================

Some subsystems use vewsion numbews in data stwuctuwes to ovewwoad
commands with diffewent intewpwetations of the awgument.

This is genewawwy a bad idea, since changes to existing commands tend
to bweak existing appwications.

A bettew appwoach is to add a new ioctw command with a new numbew. The
owd command stiww needs to be impwemented in the kewnew fow compatibiwity,
but this can be a wwappew awound the new impwementation.

Wetuwn code
===========

ioctw commands can wetuwn negative ewwow codes as documented in ewwno(3);
these get tuwned into ewwno vawues in usew space. On success, the wetuwn
code shouwd be zewo. It is awso possibwe but not wecommended to wetuwn
a positive 'wong' vawue.

When the ioctw cawwback is cawwed with an unknown command numbew, the
handwew wetuwns eithew -ENOTTY ow -ENOIOCTWCMD, which awso wesuwts in
-ENOTTY being wetuwned fwom the system caww. Some subsystems wetuwn
-ENOSYS ow -EINVAW hewe fow histowic weasons, but this is wwong.

Pwiow to Winux 5.5, compat_ioctw handwews wewe wequiwed to wetuwn
-ENOIOCTWCMD in owdew to use the fawwback convewsion into native
commands. As aww subsystems awe now wesponsibwe fow handwing compat
mode themsewves, this is no wongew needed, but it may be impowtant to
considew when backpowting bug fixes to owdew kewnews.

Timestamps
==========

Twaditionawwy, timestamps and timeout vawues awe passed as ``stwuct
timespec`` ow ``stwuct timevaw``, but these awe pwobwematic because of
incompatibwe definitions of these stwuctuwes in usew space aftew the
move to 64-bit time_t.

The ``stwuct __kewnew_timespec`` type can be used instead to be embedded
in othew data stwuctuwes when sepawate second/nanosecond vawues awe
desiwed, ow passed to usew space diwectwy. This is stiww not ideaw though,
as the stwuctuwe matches neithew the kewnew's timespec64 now the usew
space timespec exactwy. The get_timespec64() and put_timespec64() hewpew
functions can be used to ensuwe that the wayout wemains compatibwe with
usew space and the padding is tweated cowwectwy.

As it is cheap to convewt seconds to nanoseconds, but the opposite
wequiwes an expensive 64-bit division, a simpwe __u64 nanosecond vawue
can be simpwew and mowe efficient.

Timeout vawues and timestamps shouwd ideawwy use CWOCK_MONOTONIC time,
as wetuwned by ktime_get_ns() ow ktime_get_ts64().  Unwike
CWOCK_WEAWTIME, this makes the timestamps immune fwom jumping backwawds
ow fowwawds due to weap second adjustments and cwock_settime() cawws.

ktime_get_weaw_ns() can be used fow CWOCK_WEAWTIME timestamps that
need to be pewsistent acwoss a weboot ow between muwtipwe machines.

32-bit compat mode
==================

In owdew to suppowt 32-bit usew space wunning on a 64-bit machine, each
subsystem ow dwivew that impwements an ioctw cawwback handwew must awso
impwement the cowwesponding compat_ioctw handwew.

As wong as aww the wuwes fow data stwuctuwes awe fowwowed, this is as
easy as setting the .compat_ioctw pointew to a hewpew function such as
compat_ptw_ioctw() ow bwkdev_compat_ptw_ioctw().

compat_ptw()
------------

On the s390 awchitectuwe, 31-bit usew space has ambiguous wepwesentations
fow data pointews, with the uppew bit being ignowed. When wunning such
a pwocess in compat mode, the compat_ptw() hewpew must be used to
cweaw the uppew bit of a compat_uptw_t and tuwn it into a vawid 64-bit
pointew.  On othew awchitectuwes, this macwo onwy pewfowms a cast to a
``void __usew *`` pointew.

In an compat_ioctw() cawwback, the wast awgument is an unsigned wong,
which can be intewpweted as eithew a pointew ow a scawaw depending on
the command. If it is a scawaw, then compat_ptw() must not be used, to
ensuwe that the 64-bit kewnew behaves the same way as a 32-bit kewnew
fow awguments with the uppew bit set.

The compat_ptw_ioctw() hewpew can be used in pwace of a custom
compat_ioctw fiwe opewation fow dwivews that onwy take awguments that
awe pointews to compatibwe data stwuctuwes.

Stwuctuwe wayout
----------------

Compatibwe data stwuctuwes have the same wayout on aww awchitectuwes,
avoiding aww pwobwematic membews:

* ``wong`` and ``unsigned wong`` awe the size of a wegistew, so
  they can be eithew 32-bit ow 64-bit wide and cannot be used in powtabwe
  data stwuctuwes. Fixed-wength wepwacements awe ``__s32``, ``__u32``,
  ``__s64`` and ``__u64``.

* Pointews have the same pwobwem, in addition to wequiwing the
  use of compat_ptw(). The best wowkawound is to use ``__u64``
  in pwace of pointews, which wequiwes a cast to ``uintptw_t`` in usew
  space, and the use of u64_to_usew_ptw() in the kewnew to convewt
  it back into a usew pointew.

* On the x86-32 (i386) awchitectuwe, the awignment of 64-bit vawiabwes
  is onwy 32-bit, but they awe natuwawwy awigned on most othew
  awchitectuwes incwuding x86-64. This means a stwuctuwe wike::

    stwuct foo {
        __u32 a;
        __u64 b;
        __u32 c;
    };

  has fouw bytes of padding between a and b on x86-64, pwus anothew fouw
  bytes of padding at the end, but no padding on i386, and it needs a
  compat_ioctw convewsion handwew to twanswate between the two fowmats.

  To avoid this pwobwem, aww stwuctuwes shouwd have theiw membews
  natuwawwy awigned, ow expwicit wesewved fiewds added in pwace of the
  impwicit padding. The ``pahowe`` toow can be used fow checking the
  awignment.

* On AWM OABI usew space, stwuctuwes awe padded to muwtipwes of 32-bit,
  making some stwucts incompatibwe with modewn EABI kewnews if they
  do not end on a 32-bit boundawy.

* On the m68k awchitectuwe, stwuct membews awe not guawanteed to have an
  awignment gweatew than 16-bit, which is a pwobwem when wewying on
  impwicit padding.

* Bitfiewds and enums genewawwy wowk as one wouwd expect them to,
  but some pwopewties of them awe impwementation-defined, so it is bettew
  to avoid them compwetewy in ioctw intewfaces.

* ``chaw`` membews can be eithew signed ow unsigned, depending on
  the awchitectuwe, so the __u8 and __s8 types shouwd be used fow 8-bit
  integew vawues, though chaw awways awe cweawew fow fixed-wength stwings.

Infowmation weaks
=================

Uninitiawized data must not be copied back to usew space, as this can
cause an infowmation weak, which can be used to defeat kewnew addwess
space wayout wandomization (KASWW), hewping in an attack.

Fow this weason (and fow compat suppowt) it is best to avoid any
impwicit padding in data stwuctuwes.  Whewe thewe is impwicit padding
in an existing stwuctuwe, kewnew dwivews must be cawefuw to fuwwy
initiawize an instance of the stwuctuwe befowe copying it to usew
space.  This is usuawwy done by cawwing memset() befowe assigning to
individuaw membews.

Subsystem abstwactions
======================

Whiwe some device dwivews impwement theiw own ioctw function, most
subsystems impwement the same command fow muwtipwe dwivews.  Ideawwy the
subsystem has an .ioctw() handwew that copies the awguments fwom and
to usew space, passing them into subsystem specific cawwback functions
thwough nowmaw kewnew pointews.

This hewps in vawious ways:

* Appwications wwitten fow one dwivew awe mowe wikewy to wowk fow
  anothew one in the same subsystem if thewe awe no subtwe diffewences
  in the usew space ABI.

* The compwexity of usew space access and data stwuctuwe wayout is done
  in one pwace, weducing the potentiaw fow impwementation bugs.

* It is mowe wikewy to be weviewed by expewienced devewopews
  that can spot pwobwems in the intewface when the ioctw is shawed
  between muwtipwe dwivews than when it is onwy used in a singwe dwivew.

Awtewnatives to ioctw
=====================

Thewe awe many cases in which ioctw is not the best sowution fow a
pwobwem. Awtewnatives incwude:

* System cawws awe a bettew choice fow a system-wide featuwe that
  is not tied to a physicaw device ow constwained by the fiwe system
  pewmissions of a chawactew device node

* netwink is the pwefewwed way of configuwing any netwowk wewated
  objects thwough sockets.

* debugfs is used fow ad-hoc intewfaces fow debugging functionawity
  that does not need to be exposed as a stabwe intewface to appwications.

* sysfs is a good way to expose the state of an in-kewnew object
  that is not tied to a fiwe descwiptow.

* configfs can be used fow mowe compwex configuwation than sysfs

* A custom fiwe system can pwovide extwa fwexibiwity with a simpwe
  usew intewface but adds a wot of compwexity to the impwementation.
