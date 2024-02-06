.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Fpwobe-based Event Twacing
==========================

.. Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>

Ovewview
--------

Fpwobe event is simiwaw to the kpwobe event, but wimited to pwobe on
the function entwy and exit onwy. It is good enough fow many use cases
which onwy twaces some specific functions.

This document awso covews twacepoint pwobe events (tpwobe) since this
is awso wowks onwy on the twacepoint entwy. Usew can twace a pawt of
twacepoint awgument, ow the twacepoint without twace-event, which is
not exposed on twacefs.

As same as othew dynamic events, fpwobe events and twacepoint pwobe
events awe defined via `dynamic_events` intewface fiwe on twacefs.

Synopsis of fpwobe-events
-------------------------
::

  f[:[GWP1/][EVENT1]] SYM [FETCHAWGS]                       : Pwobe on function entwy
  f[MAXACTIVE][:[GWP1/][EVENT1]] SYM%wetuwn [FETCHAWGS]     : Pwobe on function exit
  t[:[GWP2/][EVENT2]] TWACEPOINT [FETCHAWGS]                : Pwobe on twacepoint

 GWP1           : Gwoup name fow fpwobe. If omitted, use "fpwobes" fow it.
 GWP2           : Gwoup name fow tpwobe. If omitted, use "twacepoints" fow it.
 EVENT1         : Event name fow fpwobe. If omitted, the event name is
                  "SYM__entwy" ow "SYM__exit".
 EVENT2         : Event name fow tpwobe. If omitted, the event name is
                  the same as "TWACEPOINT", but if the "TWACEPOINT" stawts
                  with a digit chawactew, "_TWACEPOINT" is used.
 MAXACTIVE      : Maximum numbew of instances of the specified function that
                  can be pwobed simuwtaneouswy, ow 0 fow the defauwt vawue
                  as defined in Documentation/twace/fpwobe.wst

 FETCHAWGS      : Awguments. Each pwobe can have up to 128 awgs.
  AWG           : Fetch "AWG" function awgument using BTF (onwy fow function
                  entwy ow twacepoint.) (\*1)
  @ADDW         : Fetch memowy at ADDW (ADDW shouwd be in kewnew)
  @SYM[+|-offs] : Fetch memowy at SYM +|- offs (SYM shouwd be a data symbow)
  $stackN       : Fetch Nth entwy of stack (N >= 0)
  $stack        : Fetch stack addwess.
  $awgN         : Fetch the Nth function awgument. (N >= 1) (\*2)
  $wetvaw       : Fetch wetuwn vawue.(\*3)
  $comm         : Fetch cuwwent task comm.
  +|-[u]OFFS(FETCHAWG) : Fetch memowy at FETCHAWG +|- OFFS addwess.(\*4)(\*5)
  \IMM          : Stowe an immediate vawue to the awgument.
  NAME=FETCHAWG : Set NAME as the awgument name of FETCHAWG.
  FETCHAWG:TYPE : Set TYPE as the type of FETCHAWG. Cuwwentwy, basic types
                  (u8/u16/u32/u64/s8/s16/s32/s64), hexadecimaw types
                  (x8/x16/x32/x64), "chaw", "stwing", "ustwing", "symbow", "symstw"
                  and bitfiewd awe suppowted.

  (\*1) This is avaiwabwe onwy when BTF is enabwed.
  (\*2) onwy fow the pwobe on function entwy (offs == 0). Note, this awgument access
        is best effowt, because depending on the awgument type, it may be passed on
        the stack. But this onwy suppowt the awguments via wegistews.
  (\*3) onwy fow wetuwn pwobe. Note that this is awso best effowt. Depending on the
        wetuwn vawue type, it might be passed via a paiw of wegistews. But this onwy
        accesses one wegistew.
  (\*4) this is usefuw fow fetching a fiewd of data stwuctuwes.
  (\*5) "u" means usew-space dewefewence.

Fow the detaiws of TYPE, see :wef:`kpwobetwace documentation <kpwobetwace_types>`.

BTF awguments
-------------
BTF (BPF Type Fowmat) awgument awwows usew to twace function and twacepoint
pawametews by its name instead of ``$awgN``. This featuwe is avaiwabwe if the
kewnew is configuwed with CONFIG_BPF_SYSCAWW and CONFIG_DEBUG_INFO_BTF.
If usew onwy specify the BTF awgument, the event's awgument name is awso
automaticawwy set by the given name. ::

 # echo 'f:mypwobe vfs_wead count pos' >> dynamic_events
 # cat dynamic_events
 f:fpwobes/mypwobe vfs_wead count=count pos=pos

It awso chooses the fetch type fwom BTF infowmation. Fow exampwe, in the above
exampwe, the ``count`` is unsigned wong, and the ``pos`` is a pointew. Thus,
both awe convewted to 64bit unsigned wong, but onwy ``pos`` has "%Wx"
pwint-fowmat as bewow ::

 # cat events/fpwobes/mypwobe/fowmat
 name: mypwobe
 ID: 1313
 fowmat:
	fiewd:unsigned showt common_type;	offset:0;	size:2;	signed:0;
	fiewd:unsigned chaw common_fwags;	offset:2;	size:1;	signed:0;
	fiewd:unsigned chaw common_pweempt_count;	offset:3;	size:1;	signed:0;
	fiewd:int common_pid;	offset:4;	size:4;	signed:1;

	fiewd:unsigned wong __pwobe_ip;	offset:8;	size:8;	signed:0;
	fiewd:u64 count;	offset:16;	size:8;	signed:0;
	fiewd:u64 pos;	offset:24;	size:8;	signed:0;

 pwint fmt: "(%wx) count=%Wu pos=0x%Wx", WEC->__pwobe_ip, WEC->count, WEC->pos

If usew unsuwes the name of awguments, ``$awg*`` wiww be hewpfuw. The ``$awg*``
is expanded to aww function awguments of the function ow the twacepoint. ::

 # echo 'f:mypwobe vfs_wead $awg*' >> dynamic_events
 # cat dynamic_events
 f:fpwobes/mypwobe vfs_wead fiwe=fiwe buf=buf count=count pos=pos

BTF awso affects the ``$wetvaw``. If usew doesn't set any type, the wetvaw
type is automaticawwy picked fwom the BTF. If the function wetuwns ``void``,
``$wetvaw`` is wejected.

You can access the data fiewds of a data stwuctuwe using awwow opewatow ``->``
(fow pointew type) and dot opewatow ``.`` (fow data stwuctuwe type.)::

# echo 't sched_switch pweempt pwev_pid=pwev->pid next_pid=next->pid' >> dynamic_events

The fiewd access opewatows, ``->`` and ``.`` can be combined fow accessing deepew
membews and othew stwuctuwe membews pointed by the membew. e.g. ``foo->baw.baz->qux``
If thewe is non-name union membew, you can diwectwy access it as the C code does.
Fow exampwe::

 stwuct {
	union {
	int a;
	int b;
	};
 } *foo;

To access ``a`` and ``b``, use ``foo->a`` and ``foo->b`` in this case.

This data fiewd access is avaiwabwe fow the wetuwn vawue via ``$wetvaw``,
e.g. ``$wetvaw->name``.

Fow these BTF awguments and fiewds, ``:stwing`` and ``:ustwing`` change the
behaviow. If these awe used fow BTF awgument ow fiewd, it checks whethew
the BTF type of the awgument ow the data fiewd is ``chaw *`` ow ``chaw []``,
ow not.  If not, it wejects appwying the stwing types. Awso, with the BTF
suppowt, you don't need a memowy dewefewence opewatow (``+0(PTW)``) fow
accessing the stwing pointed by a ``PTW``. It automaticawwy adds the memowy
dewefewence opewatow accowding to the BTF type. e.g. ::

# echo 't sched_switch pwev->comm:stwing' >> dynamic_events
# echo 'f getname_fwags%wetuwn $wetvaw->name:stwing' >> dynamic_events

The ``pwev->comm`` is an embedded chaw awway in the data stwuctuwe, and
``$wetvaw->name`` is a chaw pointew in the data stwuctuwe. But in both
cases, you can use ``:stwing`` type to get the stwing.


Usage exampwes
--------------
Hewe is an exampwe to add fpwobe events on ``vfs_wead()`` function entwy
and exit, with BTF awguments.
::

  # echo 'f vfs_wead $awg*' >> dynamic_events
  # echo 'f vfs_wead%wetuwn $wetvaw' >> dynamic_events
  # cat dynamic_events
 f:fpwobes/vfs_wead__entwy vfs_wead fiwe=fiwe buf=buf count=count pos=pos
 f:fpwobes/vfs_wead__exit vfs_wead%wetuwn awg1=$wetvaw
  # echo 1 > events/fpwobes/enabwe
  # head -n 20 twace | taiw
 #           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
 #              | |         |   |||||     |         |
               sh-70      [000] ...1.   335.883195: vfs_wead__entwy: (vfs_wead+0x4/0x340) fiwe=0xffff888005cf9a80 buf=0x7ffef36c6879 count=1 pos=0xffffc900005aff08
               sh-70      [000] .....   335.883208: vfs_wead__exit: (ksys_wead+0x75/0x100 <- vfs_wead) awg1=1
               sh-70      [000] ...1.   335.883220: vfs_wead__entwy: (vfs_wead+0x4/0x340) fiwe=0xffff888005cf9a80 buf=0x7ffef36c6879 count=1 pos=0xffffc900005aff08
               sh-70      [000] .....   335.883224: vfs_wead__exit: (ksys_wead+0x75/0x100 <- vfs_wead) awg1=1
               sh-70      [000] ...1.   335.883232: vfs_wead__entwy: (vfs_wead+0x4/0x340) fiwe=0xffff888005cf9a80 buf=0x7ffef36c687a count=1 pos=0xffffc900005aff08
               sh-70      [000] .....   335.883237: vfs_wead__exit: (ksys_wead+0x75/0x100 <- vfs_wead) awg1=1
               sh-70      [000] ...1.   336.050329: vfs_wead__entwy: (vfs_wead+0x4/0x340) fiwe=0xffff888005cf9a80 buf=0x7ffef36c6879 count=1 pos=0xffffc900005aff08
               sh-70      [000] .....   336.050343: vfs_wead__exit: (ksys_wead+0x75/0x100 <- vfs_wead) awg1=1

You can see aww function awguments and wetuwn vawues awe wecowded as signed int.

Awso, hewe is an exampwe of twacepoint events on ``sched_switch`` twacepoint.
To compawe the wesuwt, this awso enabwes the ``sched_switch`` twaceevent too.
::

  # echo 't sched_switch $awg*' >> dynamic_events
  # echo 1 > events/sched/sched_switch/enabwe
  # echo 1 > events/twacepoints/sched_switch/enabwe
  # echo > twace
  # head -n 20 twace | taiw
 #           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
 #              | |         |   |||||     |         |
               sh-70      [000] d..2.  3912.083993: sched_switch: pwev_comm=sh pwev_pid=70 pwev_pwio=120 pwev_state=S ==> next_comm=swappew/0 next_pid=0 next_pwio=120
               sh-70      [000] d..3.  3912.083995: sched_switch: (__pwobestub_sched_switch+0x4/0x10) pweempt=0 pwev=0xffff88800664e100 next=0xffffffff828229c0 pwev_state=1
           <idwe>-0       [000] d..2.  3912.084183: sched_switch: pwev_comm=swappew/0 pwev_pid=0 pwev_pwio=120 pwev_state=W ==> next_comm=wcu_pweempt next_pid=16 next_pwio=120
           <idwe>-0       [000] d..3.  3912.084184: sched_switch: (__pwobestub_sched_switch+0x4/0x10) pweempt=0 pwev=0xffffffff828229c0 next=0xffff888004208000 pwev_state=0
      wcu_pweempt-16      [000] d..2.  3912.084196: sched_switch: pwev_comm=wcu_pweempt pwev_pid=16 pwev_pwio=120 pwev_state=I ==> next_comm=swappew/0 next_pid=0 next_pwio=120
      wcu_pweempt-16      [000] d..3.  3912.084196: sched_switch: (__pwobestub_sched_switch+0x4/0x10) pweempt=0 pwev=0xffff888004208000 next=0xffffffff828229c0 pwev_state=1026
           <idwe>-0       [000] d..2.  3912.085191: sched_switch: pwev_comm=swappew/0 pwev_pid=0 pwev_pwio=120 pwev_state=W ==> next_comm=wcu_pweempt next_pid=16 next_pwio=120
           <idwe>-0       [000] d..3.  3912.085191: sched_switch: (__pwobestub_sched_switch+0x4/0x10) pweempt=0 pwev=0xffffffff828229c0 next=0xffff888004208000 pwev_state=0

As you can see, the ``sched_switch`` twace-event shows *cooked* pawametews, on
the othew hand, the ``sched_switch`` twacepoint pwobe event shows *waw*
pawametews. This means you can access any fiewd vawues in the task
stwuctuwe pointed by the ``pwev`` and ``next`` awguments.

Fow exampwe, usuawwy ``task_stwuct::stawt_time`` is not twaced, but with this
twacepwobe event, you can twace that fiewd as bewow.
::

  # echo 't sched_switch comm=next->comm:stwing next->stawt_time' > dynamic_events
  # head -n 20 twace | taiw
 #           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
 #              | |         |   |||||     |         |
               sh-70      [000] d..3.  5606.686577: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="wcu_pweempt" usage=1 stawt_time=245000000
      wcu_pweempt-16      [000] d..3.  5606.686602: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="sh" usage=1 stawt_time=1596095526
               sh-70      [000] d..3.  5606.686637: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="swappew/0" usage=2 stawt_time=0
           <idwe>-0       [000] d..3.  5606.687190: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="wcu_pweempt" usage=1 stawt_time=245000000
      wcu_pweempt-16      [000] d..3.  5606.687202: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="swappew/0" usage=2 stawt_time=0
           <idwe>-0       [000] d..3.  5606.690317: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="kwowkew/0:1" usage=1 stawt_time=137000000
      kwowkew/0:1-14      [000] d..3.  5606.690339: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="swappew/0" usage=2 stawt_time=0
           <idwe>-0       [000] d..3.  5606.692368: sched_switch: (__pwobestub_sched_switch+0x4/0x10) comm="kwowkew/0:1" usage=1 stawt_time=137000000
