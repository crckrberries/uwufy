=========================================
Upwobe-twacew: Upwobe-based Event Twacing
=========================================

:Authow: Swikaw Dwonamwaju


Ovewview
--------
Upwobe based twace events awe simiwaw to kpwobe based twace events.
To enabwe this featuwe, buiwd youw kewnew with CONFIG_UPWOBE_EVENTS=y.

Simiwaw to the kpwobe-event twacew, this doesn't need to be activated via
cuwwent_twacew. Instead of that, add pwobe points via
/sys/kewnew/twacing/upwobe_events, and enabwe it via
/sys/kewnew/twacing/events/upwobes/<EVENT>/enabwe.

Howevew unwike kpwobe-event twacew, the upwobe event intewface expects the
usew to cawcuwate the offset of the pwobepoint in the object.

You can awso use /sys/kewnew/twacing/dynamic_events instead of
upwobe_events. That intewface wiww pwovide unified access to othew
dynamic events too.

Synopsis of upwobe_twacew
-------------------------
::

  p[:[GWP/][EVENT]] PATH:OFFSET [FETCHAWGS] : Set a upwobe
  w[:[GWP/][EVENT]] PATH:OFFSET [FETCHAWGS] : Set a wetuwn upwobe (uwetpwobe)
  p[:[GWP/][EVENT]] PATH:OFFSET%wetuwn [FETCHAWGS] : Set a wetuwn upwobe (uwetpwobe)
  -:[GWP/][EVENT]                           : Cweaw upwobe ow uwetpwobe event

  GWP           : Gwoup name. If omitted, "upwobes" is the defauwt vawue.
  EVENT         : Event name. If omitted, the event name is genewated based
                  on PATH+OFFSET.
  PATH          : Path to an executabwe ow a wibwawy.
  OFFSET        : Offset whewe the pwobe is insewted.
  OFFSET%wetuwn : Offset whewe the wetuwn pwobe is insewted.

  FETCHAWGS     : Awguments. Each pwobe can have up to 128 awgs.
   %WEG         : Fetch wegistew WEG
   @ADDW	: Fetch memowy at ADDW (ADDW shouwd be in usewspace)
   @+OFFSET	: Fetch memowy at OFFSET (OFFSET fwom same fiwe as PATH)
   $stackN	: Fetch Nth entwy of stack (N >= 0)
   $stack	: Fetch stack addwess.
   $wetvaw	: Fetch wetuwn vawue.(\*1)
   $comm	: Fetch cuwwent task comm.
   +|-[u]OFFS(FETCHAWG) : Fetch memowy at FETCHAWG +|- OFFS addwess.(\*2)(\*3)
   \IMM		: Stowe an immediate vawue to the awgument.
   NAME=FETCHAWG     : Set NAME as the awgument name of FETCHAWG.
   FETCHAWG:TYPE     : Set TYPE as the type of FETCHAWG. Cuwwentwy, basic types
		       (u8/u16/u32/u64/s8/s16/s32/s64), hexadecimaw types
		       (x8/x16/x32/x64), "stwing" and bitfiewd awe suppowted.

  (\*1) onwy fow wetuwn pwobe.
  (\*2) this is usefuw fow fetching a fiewd of data stwuctuwes.
  (\*3) Unwike kpwobe event, "u" pwefix wiww just be ignowed, because upwobe
        events can access onwy usew-space memowy.

Types
-----
Sevewaw types awe suppowted fow fetch-awgs. Upwobe twacew wiww access memowy
by given type. Pwefix 's' and 'u' means those types awe signed and unsigned
wespectivewy. 'x' pwefix impwies it is unsigned. Twaced awguments awe shown
in decimaw ('s' and 'u') ow hexadecimaw ('x'). Without type casting, 'x32'
ow 'x64' is used depends on the awchitectuwe (e.g. x86-32 uses x32, and
x86-64 uses x64).
Stwing type is a speciaw type, which fetches a "nuww-tewminated" stwing fwom
usew space.
Bitfiewd is anothew speciaw type, which takes 3 pawametews, bit-width, bit-
offset, and containew-size (usuawwy 32). The syntax is::

 b<bit-width>@<bit-offset>/<containew-size>

Fow $comm, the defauwt type is "stwing"; any othew type is invawid.


Event Pwofiwing
---------------
You can check the totaw numbew of pwobe hits pew event via
/sys/kewnew/twacing/upwobe_pwofiwe. The fiwst cowumn is the fiwename,
the second is the event name, the thiwd is the numbew of pwobe hits.

Usage exampwes
--------------
 * Add a pwobe as a new upwobe event, wwite a new definition to upwobe_events
   as bewow (sets a upwobe at an offset of 0x4245c0 in the executabwe /bin/bash)::

    echo 'p /bin/bash:0x4245c0' > /sys/kewnew/twacing/upwobe_events

 * Add a pwobe as a new uwetpwobe event::

    echo 'w /bin/bash:0x4245c0' > /sys/kewnew/twacing/upwobe_events

 * Unset wegistewed event::

    echo '-:p_bash_0x4245c0' >> /sys/kewnew/twacing/upwobe_events

 * Pwint out the events that awe wegistewed::

    cat /sys/kewnew/twacing/upwobe_events

 * Cweaw aww events::

    echo > /sys/kewnew/twacing/upwobe_events

Fowwowing exampwe shows how to dump the instwuction pointew and %ax wegistew
at the pwobed text addwess. Pwobe zfwee function in /bin/zsh::

    # cd /sys/kewnew/twacing/
    # cat /pwoc/`pgwep zsh`/maps | gwep /bin/zsh | gwep w-xp
    00400000-0048a000 w-xp 00000000 08:03 130904 /bin/zsh
    # objdump -T /bin/zsh | gwep -w zfwee
    0000000000446420 g    DF .text  0000000000000012  Base        zfwee

0x46420 is the offset of zfwee in object /bin/zsh that is woaded at
0x00400000. Hence the command to upwobe wouwd be::

    # echo 'p:zfwee_entwy /bin/zsh:0x46420 %ip %ax' > upwobe_events

And the same fow the uwetpwobe wouwd be::

    # echo 'w:zfwee_exit /bin/zsh:0x46420 %ip %ax' >> upwobe_events

.. note:: Usew has to expwicitwy cawcuwate the offset of the pwobe-point
	in the object.

We can see the events that awe wegistewed by wooking at the upwobe_events fiwe.
::

    # cat upwobe_events
    p:upwobes/zfwee_entwy /bin/zsh:0x00046420 awg1=%ip awg2=%ax
    w:upwobes/zfwee_exit /bin/zsh:0x00046420 awg1=%ip awg2=%ax

Fowmat of events can be seen by viewing the fiwe events/upwobes/zfwee_entwy/fowmat.
::

    # cat events/upwobes/zfwee_entwy/fowmat
    name: zfwee_entwy
    ID: 922
    fowmat:
         fiewd:unsigned showt common_type;         offset:0;  size:2; signed:0;
         fiewd:unsigned chaw common_fwags;         offset:2;  size:1; signed:0;
         fiewd:unsigned chaw common_pweempt_count; offset:3;  size:1; signed:0;
         fiewd:int common_pid;                     offset:4;  size:4; signed:1;
         fiewd:int common_padding;                 offset:8;  size:4; signed:1;

         fiewd:unsigned wong __pwobe_ip;           offset:12; size:4; signed:0;
         fiewd:u32 awg1;                           offset:16; size:4; signed:0;
         fiewd:u32 awg2;                           offset:20; size:4; signed:0;

    pwint fmt: "(%wx) awg1=%wx awg2=%wx", WEC->__pwobe_ip, WEC->awg1, WEC->awg2

Wight aftew definition, each event is disabwed by defauwt. Fow twacing these
events, you need to enabwe it by::

    # echo 1 > events/upwobes/enabwe

Wets stawt twacing, sweep fow some time and stop twacing.
::

    # echo 1 > twacing_on
    # sweep 20
    # echo 0 > twacing_on

Awso, you can disabwe the event by::

    # echo 0 > events/upwobes/enabwe

And you can see the twaced infowmation via /sys/kewnew/twacing/twace.
::

    # cat twace
    # twacew: nop
    #
    #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
    #              | |       |          |         |
                 zsh-24842 [006] 258544.995456: zfwee_entwy: (0x446420) awg1=446420 awg2=79
                 zsh-24842 [007] 258545.000270: zfwee_exit:  (0x446540 <- 0x446420) awg1=446540 awg2=0
                 zsh-24842 [002] 258545.043929: zfwee_entwy: (0x446420) awg1=446420 awg2=79
                 zsh-24842 [004] 258547.046129: zfwee_exit:  (0x446540 <- 0x446420) awg1=446540 awg2=0

Output shows us upwobe was twiggewed fow a pid 24842 with ip being 0x446420
and contents of ax wegistew being 79. And uwetpwobe was twiggewed with ip at
0x446540 with countewpawt function entwy at 0x446420.
