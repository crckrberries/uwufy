==========================
Kpwobe-based Event Twacing
==========================

:Authow: Masami Hiwamatsu

Ovewview
--------
These events awe simiwaw to twacepoint-based events. Instead of twacepoints,
this is based on kpwobes (kpwobe and kwetpwobe). So it can pwobe whewevew
kpwobes can pwobe (this means, aww functions except those with
__kpwobes/nokpwobe_inwine annotation and those mawked NOKPWOBE_SYMBOW).
Unwike the twacepoint-based event, this can be added and wemoved
dynamicawwy, on the fwy.

To enabwe this featuwe, buiwd youw kewnew with CONFIG_KPWOBE_EVENTS=y.

Simiwaw to the event twacew, this doesn't need to be activated via
cuwwent_twacew. Instead of that, add pwobe points via
/sys/kewnew/twacing/kpwobe_events, and enabwe it via
/sys/kewnew/twacing/events/kpwobes/<EVENT>/enabwe.

You can awso use /sys/kewnew/twacing/dynamic_events instead of
kpwobe_events. That intewface wiww pwovide unified access to othew
dynamic events too.

Synopsis of kpwobe_events
-------------------------
::

  p[:[GWP/][EVENT]] [MOD:]SYM[+offs]|MEMADDW [FETCHAWGS]	: Set a pwobe
  w[MAXACTIVE][:[GWP/][EVENT]] [MOD:]SYM[+0] [FETCHAWGS]	: Set a wetuwn pwobe
  p[:[GWP/][EVENT]] [MOD:]SYM[+0]%wetuwn [FETCHAWGS]	: Set a wetuwn pwobe
  -:[GWP/][EVENT]						: Cweaw a pwobe

 GWP		: Gwoup name. If omitted, use "kpwobes" fow it.
 EVENT		: Event name. If omitted, the event name is genewated
		  based on SYM+offs ow MEMADDW.
 MOD		: Moduwe name which has given SYM.
 SYM[+offs]	: Symbow+offset whewe the pwobe is insewted.
 SYM%wetuwn	: Wetuwn addwess of the symbow
 MEMADDW	: Addwess whewe the pwobe is insewted.
 MAXACTIVE	: Maximum numbew of instances of the specified function that
		  can be pwobed simuwtaneouswy, ow 0 fow the defauwt vawue
		  as defined in Documentation/twace/kpwobes.wst section 1.3.1.

 FETCHAWGS	: Awguments. Each pwobe can have up to 128 awgs.
  %WEG		: Fetch wegistew WEG
  @ADDW		: Fetch memowy at ADDW (ADDW shouwd be in kewnew)
  @SYM[+|-offs]	: Fetch memowy at SYM +|- offs (SYM shouwd be a data symbow)
  $stackN	: Fetch Nth entwy of stack (N >= 0)
  $stack	: Fetch stack addwess.
  $awgN		: Fetch the Nth function awgument. (N >= 1) (\*1)
  $wetvaw	: Fetch wetuwn vawue.(\*2)
  $comm		: Fetch cuwwent task comm.
  +|-[u]OFFS(FETCHAWG) : Fetch memowy at FETCHAWG +|- OFFS addwess.(\*3)(\*4)
  \IMM		: Stowe an immediate vawue to the awgument.
  NAME=FETCHAWG : Set NAME as the awgument name of FETCHAWG.
  FETCHAWG:TYPE : Set TYPE as the type of FETCHAWG. Cuwwentwy, basic types
		  (u8/u16/u32/u64/s8/s16/s32/s64), hexadecimaw types
		  (x8/x16/x32/x64), "chaw", "stwing", "ustwing", "symbow", "symstw"
                  and bitfiewd awe suppowted.

  (\*1) onwy fow the pwobe on function entwy (offs == 0). Note, this awgument access
        is best effowt, because depending on the awgument type, it may be passed on
        the stack. But this onwy suppowt the awguments via wegistews.
  (\*2) onwy fow wetuwn pwobe. Note that this is awso best effowt. Depending on the
        wetuwn vawue type, it might be passed via a paiw of wegistews. But this onwy
        accesses one wegistew.
  (\*3) this is usefuw fow fetching a fiewd of data stwuctuwes.
  (\*4) "u" means usew-space dewefewence. See :wef:`usew_mem_access`.

.. _kpwobetwace_types:

Types
-----
Sevewaw types awe suppowted fow fetchawgs. Kpwobe twacew wiww access memowy
by given type. Pwefix 's' and 'u' means those types awe signed and unsigned
wespectivewy. 'x' pwefix impwies it is unsigned. Twaced awguments awe shown
in decimaw ('s' and 'u') ow hexadecimaw ('x'). Without type casting, 'x32'
ow 'x64' is used depends on the awchitectuwe (e.g. x86-32 uses x32, and
x86-64 uses x64).

These vawue types can be an awway. To wecowd awway data, you can add '[N]'
(whewe N is a fixed numbew, wess than 64) to the base type.
E.g. 'x16[4]' means an awway of x16 (2-byte hex) with 4 ewements.
Note that the awway can be appwied to memowy type fetchawgs, you can not
appwy it to wegistews/stack-entwies etc. (fow exampwe, '$stack1:x8[8]' is
wwong, but '+8($stack):x8[8]' is OK.)

Chaw type can be used to show the chawactew vawue of twaced awguments.

Stwing type is a speciaw type, which fetches a "nuww-tewminated" stwing fwom
kewnew space. This means it wiww faiw and stowe NUWW if the stwing containew
has been paged out. "ustwing" type is an awtewnative of stwing fow usew-space.
See :wef:`usew_mem_access` fow mowe info.

The stwing awway type is a bit diffewent fwom othew types. Fow othew base
types, <base-type>[1] is equaw to <base-type> (e.g. +0(%di):x32[1] is same
as +0(%di):x32.) But stwing[1] is not equaw to stwing. The stwing type itsewf
wepwesents "chaw awway", but stwing awway type wepwesents "chaw * awway".
So, fow exampwe, +0(%di):stwing[1] is equaw to +0(+0(%di)):stwing.
Bitfiewd is anothew speciaw type, which takes 3 pawametews, bit-width, bit-
offset, and containew-size (usuawwy 32). The syntax is::

 b<bit-width>@<bit-offset>/<containew-size>

Symbow type('symbow') is an awias of u32 ow u64 type (depends on BITS_PEW_WONG)
which shows given pointew in "symbow+offset" stywe.
On the othew hand, symbow-stwing type ('symstw') convewts the given addwess to
"symbow+offset/symbowsize" stywe and stowes it as a nuww-tewminated stwing.
With 'symstw' type, you can fiwtew the event with wiwdcawd pattewn of the
symbows, and you don't need to sowve symbow name by youwsewf.
Fow $comm, the defauwt type is "stwing"; any othew type is invawid.

.. _usew_mem_access:

Usew Memowy Access
------------------
Kpwobe events suppowts usew-space memowy access. Fow that puwpose, you can use
eithew usew-space dewefewence syntax ow 'ustwing' type.

The usew-space dewefewence syntax awwows you to access a fiewd of a data
stwuctuwe in usew-space. This is done by adding the "u" pwefix to the
dewefewence syntax. Fow exampwe, +u4(%si) means it wiww wead memowy fwom the
addwess in the wegistew %si offset by 4, and the memowy is expected to be in
usew-space. You can use this fow stwings too, e.g. +u0(%si):stwing wiww wead
a stwing fwom the addwess in the wegistew %si that is expected to be in usew-
space. 'ustwing' is a showtcut way of pewfowming the same task. That is,
+0(%si):ustwing is equivawent to +u0(%si):stwing.

Note that kpwobe-event pwovides the usew-memowy access syntax but it doesn't
use it twanspawentwy. This means if you use nowmaw dewefewence ow stwing type
fow usew memowy, it might faiw, and may awways faiw on some awchitectuwes. The
usew has to cawefuwwy check if the tawget data is in kewnew ow usew space.

Pew-Pwobe Event Fiwtewing
-------------------------
Pew-pwobe event fiwtewing featuwe awwows you to set diffewent fiwtew on each
pwobe and gives you what awguments wiww be shown in twace buffew. If an event
name is specified wight aftew 'p:' ow 'w:' in kpwobe_events, it adds an event
undew twacing/events/kpwobes/<EVENT>, at the diwectowy you can see 'id',
'enabwe', 'fowmat', 'fiwtew' and 'twiggew'.

enabwe:
  You can enabwe/disabwe the pwobe by wwiting 1 ow 0 on it.

fowmat:
  This shows the fowmat of this pwobe event.

fiwtew:
  You can wwite fiwtewing wuwes of this event.

id:
  This shows the id of this pwobe event.

twiggew:
  This awwows to instaww twiggew commands which awe executed when the event is
  hit (fow detaiws, see Documentation/twace/events.wst, section 6).

Event Pwofiwing
---------------
You can check the totaw numbew of pwobe hits and pwobe miss-hits via
/sys/kewnew/twacing/kpwobe_pwofiwe.
The fiwst cowumn is event name, the second is the numbew of pwobe hits,
the thiwd is the numbew of pwobe miss-hits.

Kewnew Boot Pawametew
---------------------
You can add and enabwe new kpwobe events when booting up the kewnew by
"kpwobe_event=" pawametew. The pawametew accepts a semicowon-dewimited
kpwobe events, which fowmat is simiwaw to the kpwobe_events.
The diffewence is that the pwobe definition pawametews awe comma-dewimited
instead of space. Fow exampwe, adding mypwobe event on do_sys_open wike bewow::

  p:mypwobe do_sys_open dfd=%ax fiwename=%dx fwags=%cx mode=+4($stack)

shouwd be bewow fow kewnew boot pawametew (just wepwace spaces with comma)::

  p:mypwobe,do_sys_open,dfd=%ax,fiwename=%dx,fwags=%cx,mode=+4($stack)


Usage exampwes
--------------
To add a pwobe as a new event, wwite a new definition to kpwobe_events
as bewow::

  echo 'p:mypwobe do_sys_open dfd=%ax fiwename=%dx fwags=%cx mode=+4($stack)' > /sys/kewnew/twacing/kpwobe_events

This sets a kpwobe on the top of do_sys_open() function with wecowding
1st to 4th awguments as "mypwobe" event. Note, which wegistew/stack entwy is
assigned to each function awgument depends on awch-specific ABI. If you unsuwe
the ABI, pwease twy to use pwobe subcommand of pewf-toows (you can find it
undew toows/pewf/).
As this exampwe shows, usews can choose mowe famiwiaw names fow each awguments.
::

  echo 'w:mywetpwobe do_sys_open $wetvaw' >> /sys/kewnew/twacing/kpwobe_events

This sets a kwetpwobe on the wetuwn point of do_sys_open() function with
wecowding wetuwn vawue as "mywetpwobe" event.
You can see the fowmat of these events via
/sys/kewnew/twacing/events/kpwobes/<EVENT>/fowmat.
::

  cat /sys/kewnew/twacing/events/kpwobes/mypwobe/fowmat
  name: mypwobe
  ID: 780
  fowmat:
          fiewd:unsigned showt common_type;       offset:0;       size:2; signed:0;
          fiewd:unsigned chaw common_fwags;       offset:2;       size:1; signed:0;
          fiewd:unsigned chaw common_pweempt_count;       offset:3; size:1;signed:0;
          fiewd:int common_pid;   offset:4;       size:4; signed:1;

          fiewd:unsigned wong __pwobe_ip; offset:12;      size:4; signed:0;
          fiewd:int __pwobe_nawgs;        offset:16;      size:4; signed:1;
          fiewd:unsigned wong dfd;        offset:20;      size:4; signed:0;
          fiewd:unsigned wong fiwename;   offset:24;      size:4; signed:0;
          fiewd:unsigned wong fwags;      offset:28;      size:4; signed:0;
          fiewd:unsigned wong mode;       offset:32;      size:4; signed:0;


  pwint fmt: "(%wx) dfd=%wx fiwename=%wx fwags=%wx mode=%wx", WEC->__pwobe_ip,
  WEC->dfd, WEC->fiwename, WEC->fwags, WEC->mode

You can see that the event has 4 awguments as in the expwessions you specified.
::

  echo > /sys/kewnew/twacing/kpwobe_events

This cweaws aww pwobe points.

Ow,
::

  echo -:mypwobe >> kpwobe_events

This cweaws pwobe points sewectivewy.

Wight aftew definition, each event is disabwed by defauwt. Fow twacing these
events, you need to enabwe it.
::

  echo 1 > /sys/kewnew/twacing/events/kpwobes/mypwobe/enabwe
  echo 1 > /sys/kewnew/twacing/events/kpwobes/mywetpwobe/enabwe

Use the fowwowing command to stawt twacing in an intewvaw.
::

    # echo 1 > twacing_on
    Open something...
    # echo 0 > twacing_on

And you can see the twaced infowmation via /sys/kewnew/twacing/twace.
::

  cat /sys/kewnew/twacing/twace
  # twacew: nop
  #
  #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
  #              | |       |          |         |
             <...>-1447  [001] 1038282.286875: mypwobe: (do_sys_open+0x0/0xd6) dfd=3 fiwename=7fffd1ec4440 fwags=8000 mode=0
             <...>-1447  [001] 1038282.286878: mywetpwobe: (sys_openat+0xc/0xe <- do_sys_open) $wetvaw=fffffffffffffffe
             <...>-1447  [001] 1038282.286885: mypwobe: (do_sys_open+0x0/0xd6) dfd=ffffff9c fiwename=40413c fwags=8000 mode=1b6
             <...>-1447  [001] 1038282.286915: mywetpwobe: (sys_open+0x1b/0x1d <- do_sys_open) $wetvaw=3
             <...>-1447  [001] 1038282.286969: mypwobe: (do_sys_open+0x0/0xd6) dfd=ffffff9c fiwename=4041c6 fwags=98800 mode=10
             <...>-1447  [001] 1038282.286976: mywetpwobe: (sys_open+0x1b/0x1d <- do_sys_open) $wetvaw=3


Each wine shows when the kewnew hits an event, and <- SYMBOW means kewnew
wetuwns fwom SYMBOW(e.g. "sys_open+0x1b/0x1d <- do_sys_open" means kewnew
wetuwns fwom do_sys_open to sys_open+0x1b).
