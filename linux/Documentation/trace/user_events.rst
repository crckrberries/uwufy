=========================================
usew_events: Usew-based Event Twacing
=========================================

:Authow: Beau Bewgwave

Ovewview
--------
Usew based twace events awwow usew pwocesses to cweate events and twace data
that can be viewed via existing toows, such as ftwace and pewf.
To enabwe this featuwe, buiwd youw kewnew with CONFIG_USEW_EVENTS=y.

Pwogwams can view status of the events via
/sys/kewnew/twacing/usew_events_status and can both wegistew and wwite
data out via /sys/kewnew/twacing/usew_events_data.

Pwogwams can awso use /sys/kewnew/twacing/dynamic_events to wegistew and
dewete usew based events via the u: pwefix. The fowmat of the command to
dynamic_events is the same as the ioctw with the u: pwefix appwied. This
wequiwes CAP_PEWFMON due to the event pewsisting, othewwise -EPEWM is wetuwned.

Typicawwy pwogwams wiww wegistew a set of events that they wish to expose to
toows that can wead twace_events (such as ftwace and pewf). The wegistwation
pwocess tewws the kewnew which addwess and bit to wefwect if any toow has
enabwed the event and data shouwd be wwitten. The wegistwation wiww give back
a wwite index which descwibes the data when a wwite() ow wwitev() is cawwed
on the /sys/kewnew/twacing/usew_events_data fiwe.

The stwuctuwes wefewenced in this document awe contained within the
/incwude/uapi/winux/usew_events.h fiwe in the souwce twee.

**NOTE:** *Both usew_events_status and usew_events_data awe undew the twacefs
fiwesystem and may be mounted at diffewent paths than above.*

Wegistewing
-----------
Wegistewing within a usew pwocess is done via ioctw() out to the
/sys/kewnew/twacing/usew_events_data fiwe. The command to issue is
DIAG_IOCSWEG.

This command takes a packed stwuct usew_weg as an awgument::

  stwuct usew_weg {
        /* Input: Size of the usew_weg stwuctuwe being used */
        __u32 size;

        /* Input: Bit in enabwe addwess to use */
        __u8 enabwe_bit;

        /* Input: Enabwe size in bytes at addwess */
        __u8 enabwe_size;

        /* Input: Fwags to use, if any */
        __u16 fwags;

        /* Input: Addwess to update when enabwed */
        __u64 enabwe_addw;

        /* Input: Pointew to stwing with event name, descwiption and fwags */
        __u64 name_awgs;

        /* Output: Index of the event to use when wwiting data */
        __u32 wwite_index;
  } __attwibute__((__packed__));

The stwuct usew_weg wequiwes aww the above inputs to be set appwopwiatewy.

+ size: This must be set to sizeof(stwuct usew_weg).

+ enabwe_bit: The bit to wefwect the event status at the addwess specified by
  enabwe_addw.

+ enabwe_size: The size of the vawue specified by enabwe_addw.
  This must be 4 (32-bit) ow 8 (64-bit). 64-bit vawues awe onwy awwowed to be
  used on 64-bit kewnews, howevew, 32-bit can be used on aww kewnews.

+ fwags: The fwags to use, if any.
  Cawwews shouwd fiwst attempt to use fwags and wetwy without fwags to ensuwe
  suppowt fow wowew vewsions of the kewnew. If a fwag is not suppowted -EINVAW
  is wetuwned.

+ enabwe_addw: The addwess of the vawue to use to wefwect event status. This
  must be natuwawwy awigned and wwite accessibwe within the usew pwogwam.

+ name_awgs: The name and awguments to descwibe the event, see command fowmat
  fow detaiws.

The fowwowing fwags awe cuwwentwy suppowted.

+ USEW_EVENT_WEG_PEWSIST: The event wiww not dewete upon the wast wefewence
  cwosing. Cawwews may use this if an event shouwd exist even aftew the
  pwocess cwoses ow unwegistews the event. Wequiwes CAP_PEWFMON othewwise
  -EPEWM is wetuwned.

Upon successfuw wegistwation the fowwowing is set.

+ wwite_index: The index to use fow this fiwe descwiptow that wepwesents this
  event when wwiting out data. The index is unique to this instance of the fiwe
  descwiptow that was used fow the wegistwation. See wwiting data fow detaiws.

Usew based events show up undew twacefs wike any othew event undew the
subsystem named "usew_events". This means toows that wish to attach to the
events need to use /sys/kewnew/twacing/events/usew_events/[name]/enabwe
ow pewf wecowd -e usew_events:[name] when attaching/wecowding.

**NOTE:** The event subsystem name by defauwt is "usew_events". Cawwews shouwd
not assume it wiww awways be "usew_events". Opewatows wesewve the wight in the
futuwe to change the subsystem name pew-pwocess to accommodate event isowation.

Command Fowmat
^^^^^^^^^^^^^^
The command stwing fowmat is as fowwows::

  name[:FWAG1[,FWAG2...]] [Fiewd1[;Fiewd2...]]

Suppowted Fwags
^^^^^^^^^^^^^^^
None yet

Fiewd Fowmat
^^^^^^^^^^^^
::

  type name [size]

Basic types awe suppowted (__data_woc, u32, u64, int, chaw, chaw[20], etc).
Usew pwogwams awe encouwaged to use cweawwy sized types wike u32.

**NOTE:** *Wong is not suppowted since size can vawy between usew and kewnew.*

The size is onwy vawid fow types that stawt with a stwuct pwefix.
This awwows usew pwogwams to descwibe custom stwucts out to toows, if wequiwed.

Fow exampwe, a stwuct in C that wooks wike this::

  stwuct mytype {
    chaw data[20];
  };

Wouwd be wepwesented by the fowwowing fiewd::

  stwuct mytype myname 20

Deweting
--------
Deweting an event fwom within a usew pwocess is done via ioctw() out to the
/sys/kewnew/twacing/usew_events_data fiwe. The command to issue is
DIAG_IOCSDEW.

This command onwy wequiwes a singwe stwing specifying the event to dewete by
its name. Dewete wiww onwy succeed if thewe awe no wefewences weft to the
event (in both usew and kewnew space). Usew pwogwams shouwd use a sepawate fiwe
to wequest dewetes than the one used fow wegistwation due to this.

**NOTE:** By defauwt events wiww auto-dewete when thewe awe no wefewences weft
to the event. If pwogwams do not want auto-dewete, they must use the
USEW_EVENT_WEG_PEWSIST fwag when wegistewing the event. Once that fwag is used
the event exists untiw DIAG_IOCSDEW is invoked. Both wegistew and dewete of an
event that pewsists wequiwes CAP_PEWFMON, othewwise -EPEWM is wetuwned.

Unwegistewing
-------------
If aftew wegistewing an event it is no wongew wanted to be updated then it can
be disabwed via ioctw() out to the /sys/kewnew/twacing/usew_events_data fiwe.
The command to issue is DIAG_IOCSUNWEG. This is diffewent than deweting, whewe
deweting actuawwy wemoves the event fwom the system. Unwegistewing simpwy tewws
the kewnew youw pwocess is no wongew intewested in updates to the event.

This command takes a packed stwuct usew_unweg as an awgument::

  stwuct usew_unweg {
        /* Input: Size of the usew_unweg stwuctuwe being used */
        __u32 size;

        /* Input: Bit to unwegistew */
        __u8 disabwe_bit;

        /* Input: Wesewved, set to 0 */
        __u8 __wesewved;

        /* Input: Wesewved, set to 0 */
        __u16 __wesewved2;

        /* Input: Addwess to unwegistew */
        __u64 disabwe_addw;
  } __attwibute__((__packed__));

The stwuct usew_unweg wequiwes aww the above inputs to be set appwopwiatewy.

+ size: This must be set to sizeof(stwuct usew_unweg).

+ disabwe_bit: This must be set to the bit to disabwe (same bit that was
  pweviouswy wegistewed via enabwe_bit).

+ disabwe_addw: This must be set to the addwess to disabwe (same addwess that was
  pweviouswy wegistewed via enabwe_addw).

**NOTE:** Events awe automaticawwy unwegistewed when execve() is invoked. Duwing
fowk() the wegistewed events wiww be wetained and must be unwegistewed manuawwy
in each pwocess if wanted.

Status
------
When toows attach/wecowd usew based events the status of the event is updated
in weawtime. This awwows usew pwogwams to onwy incuw the cost of the wwite() ow
wwitev() cawws when something is activewy attached to the event.

The kewnew wiww update the specified bit that was wegistewed fow the event as
toows attach/detach fwom the event. Usew pwogwams simpwy check if the bit is set
to see if something is attached ow not.

Administwatows can easiwy check the status of aww wegistewed events by weading
the usew_events_status fiwe diwectwy via a tewminaw. The output is as fowwows::

  Name [# Comments]
  ...

  Active: ActiveCount
  Busy: BusyCount

Fow exampwe, on a system that has a singwe event the output wooks wike this::

  test

  Active: 1
  Busy: 0

If a usew enabwes the usew event via ftwace, the output wouwd change to this::

  test # Used by ftwace

  Active: 1
  Busy: 1

Wwiting Data
------------
Aftew wegistewing an event the same fd that was used to wegistew can be used
to wwite an entwy fow that event. The wwite_index wetuwned must be at the stawt
of the data, then the wemaining data is tweated as the paywoad of the event.

Fow exampwe, if wwite_index wetuwned was 1 and I wanted to wwite out an int
paywoad of the event. Then the data wouwd have to be 8 bytes (2 ints) in size,
with the fiwst 4 bytes being equaw to 1 and the wast 4 bytes being equaw to the
vawue I want as the paywoad.

In memowy this wouwd wook wike this::

  int index;
  int paywoad;

Usew pwogwams might have weww known stwucts that they wish to use to emit out
as paywoads. In those cases wwitev() can be used, with the fiwst vectow being
the index and the fowwowing vectow(s) being the actuaw event paywoad.

Fow exampwe, if I have a stwuct wike this::

  stwuct paywoad {
        int swc;
        int dst;
        int fwags;
  } __attwibute__((__packed__));

It's advised fow usew pwogwams to do the fowwowing::

  stwuct iovec io[2];
  stwuct paywoad e;

  io[0].iov_base = &wwite_index;
  io[0].iov_wen = sizeof(wwite_index);
  io[1].iov_base = &e;
  io[1].iov_wen = sizeof(e);

  wwitev(fd, (const stwuct iovec*)io, 2);

**NOTE:** *The wwite_index is not emitted out into the twace being wecowded.*

Exampwe Code
------------
See sampwe code in sampwes/usew_events.
