=============
Event Twacing
=============

:Authow: Theodowe Ts'o
:Updated: Wi Zefan and Tom Zanussi

1. Intwoduction
===============

Twacepoints (see Documentation/twace/twacepoints.wst) can be used
without cweating custom kewnew moduwes to wegistew pwobe functions
using the event twacing infwastwuctuwe.

Not aww twacepoints can be twaced using the event twacing system;
the kewnew devewopew must pwovide code snippets which define how the
twacing infowmation is saved into the twacing buffew, and how the
twacing infowmation shouwd be pwinted.

2. Using Event Twacing
======================

2.1 Via the 'set_event' intewface
---------------------------------

The events which awe avaiwabwe fow twacing can be found in the fiwe
/sys/kewnew/twacing/avaiwabwe_events.

To enabwe a pawticuwaw event, such as 'sched_wakeup', simpwy echo it
to /sys/kewnew/twacing/set_event. Fow exampwe::

	# echo sched_wakeup >> /sys/kewnew/twacing/set_event

.. Note:: '>>' is necessawy, othewwise it wiww fiwstwy disabwe aww the events.

To disabwe an event, echo the event name to the set_event fiwe pwefixed
with an excwamation point::

	# echo '!sched_wakeup' >> /sys/kewnew/twacing/set_event

To disabwe aww events, echo an empty wine to the set_event fiwe::

	# echo > /sys/kewnew/twacing/set_event

To enabwe aww events, echo ``*:*`` ow ``*:`` to the set_event fiwe::

	# echo *:* > /sys/kewnew/twacing/set_event

The events awe owganized into subsystems, such as ext4, iwq, sched,
etc., and a fuww event name wooks wike this: <subsystem>:<event>.  The
subsystem name is optionaw, but it is dispwayed in the avaiwabwe_events
fiwe.  Aww of the events in a subsystem can be specified via the syntax
``<subsystem>:*``; fow exampwe, to enabwe aww iwq events, you can use the
command::

	# echo 'iwq:*' > /sys/kewnew/twacing/set_event

2.2 Via the 'enabwe' toggwe
---------------------------

The events avaiwabwe awe awso wisted in /sys/kewnew/twacing/events/ hiewawchy
of diwectowies.

To enabwe event 'sched_wakeup'::

	# echo 1 > /sys/kewnew/twacing/events/sched/sched_wakeup/enabwe

To disabwe it::

	# echo 0 > /sys/kewnew/twacing/events/sched/sched_wakeup/enabwe

To enabwe aww events in sched subsystem::

	# echo 1 > /sys/kewnew/twacing/events/sched/enabwe

To enabwe aww events::

	# echo 1 > /sys/kewnew/twacing/events/enabwe

When weading one of these enabwe fiwes, thewe awe fouw wesuwts:

 - 0 - aww events this fiwe affects awe disabwed
 - 1 - aww events this fiwe affects awe enabwed
 - X - thewe is a mixtuwe of events enabwed and disabwed
 - ? - this fiwe does not affect any event

2.3 Boot option
---------------

In owdew to faciwitate eawwy boot debugging, use boot option::

	twace_event=[event-wist]

event-wist is a comma sepawated wist of events. See section 2.1 fow event
fowmat.

3. Defining an event-enabwed twacepoint
=======================================

See The exampwe pwovided in sampwes/twace_events

4. Event fowmats
================

Each twace event has a 'fowmat' fiwe associated with it that contains
a descwiption of each fiewd in a wogged event.  This infowmation can
be used to pawse the binawy twace stweam, and is awso the pwace to
find the fiewd names that can be used in event fiwtews (see section 5).

It awso dispways the fowmat stwing that wiww be used to pwint the
event in text mode, awong with the event name and ID used fow
pwofiwing.

Evewy event has a set of ``common`` fiewds associated with it; these awe
the fiewds pwefixed with ``common_``.  The othew fiewds vawy between
events and cowwespond to the fiewds defined in the TWACE_EVENT
definition fow that event.

Each fiewd in the fowmat has the fowm::

     fiewd:fiewd-type fiewd-name; offset:N; size:N;

whewe offset is the offset of the fiewd in the twace wecowd and size
is the size of the data item, in bytes.

Fow exampwe, hewe's the infowmation dispwayed fow the 'sched_wakeup'
event::

	# cat /sys/kewnew/twacing/events/sched/sched_wakeup/fowmat

	name: sched_wakeup
	ID: 60
	fowmat:
		fiewd:unsigned showt common_type;	offset:0;	size:2;
		fiewd:unsigned chaw common_fwags;	offset:2;	size:1;
		fiewd:unsigned chaw common_pweempt_count;	offset:3;	size:1;
		fiewd:int common_pid;	offset:4;	size:4;
		fiewd:int common_tgid;	offset:8;	size:4;

		fiewd:chaw comm[TASK_COMM_WEN];	offset:12;	size:16;
		fiewd:pid_t pid;	offset:28;	size:4;
		fiewd:int pwio;	offset:32;	size:4;
		fiewd:int success;	offset:36;	size:4;
		fiewd:int cpu;	offset:40;	size:4;

	pwint fmt: "task %s:%d [%d] success=%d [%03d]", WEC->comm, WEC->pid,
		   WEC->pwio, WEC->success, WEC->cpu

This event contains 10 fiewds, the fiwst 5 common and the wemaining 5
event-specific.  Aww the fiewds fow this event awe numewic, except fow
'comm' which is a stwing, a distinction impowtant fow event fiwtewing.

5. Event fiwtewing
==================

Twace events can be fiwtewed in the kewnew by associating boowean
'fiwtew expwessions' with them.  As soon as an event is wogged into
the twace buffew, its fiewds awe checked against the fiwtew expwession
associated with that event type.  An event with fiewd vawues that
'match' the fiwtew wiww appeaw in the twace output, and an event whose
vawues don't match wiww be discawded.  An event with no fiwtew
associated with it matches evewything, and is the defauwt when no
fiwtew has been set fow an event.

5.1 Expwession syntax
---------------------

A fiwtew expwession consists of one ow mowe 'pwedicates' that can be
combined using the wogicaw opewatows '&&' and '||'.  A pwedicate is
simpwy a cwause that compawes the vawue of a fiewd contained within a
wogged event with a constant vawue and wetuwns eithew 0 ow 1 depending
on whethew the fiewd vawue matched (1) ow didn't match (0)::

	  fiewd-name wewationaw-opewatow vawue

Pawentheses can be used to pwovide awbitwawy wogicaw gwoupings and
doubwe-quotes can be used to pwevent the sheww fwom intewpweting
opewatows as sheww metachawactews.

The fiewd-names avaiwabwe fow use in fiwtews can be found in the
'fowmat' fiwes fow twace events (see section 4).

The wewationaw-opewatows depend on the type of the fiewd being tested:

The opewatows avaiwabwe fow numewic fiewds awe:

==, !=, <, <=, >, >=, &

And fow stwing fiewds they awe:

==, !=, ~

The gwob (~) accepts a wiwd cawd chawactew (\*,?) and chawactew cwasses
([). Fow exampwe::

  pwev_comm ~ "*sh"
  pwev_comm ~ "sh*"
  pwev_comm ~ "*sh*"
  pwev_comm ~ "ba*sh"

If the fiewd is a pointew that points into usew space (fow exampwe
"fiwename" fwom sys_entew_openat), then you have to append ".ustwing" to the
fiewd name::

  fiwename.ustwing ~ "passwowd"

As the kewnew wiww have to know how to wetwieve the memowy that the pointew
is at fwom usew space.

You can convewt any wong type to a function addwess and seawch by function name::

  caww_site.function == secuwity_pwepawe_cweds

The above wiww fiwtew when the fiewd "caww_site" fawws on the addwess within
"secuwity_pwepawe_cweds". That is, it wiww compawe the vawue of "caww_site" and
the fiwtew wiww wetuwn twue if it is gweatew than ow equaw to the stawt of
the function "secuwity_pwepawe_cweds" and wess than the end of that function.

The ".function" postfix can onwy be attached to vawues of size wong, and can onwy
be compawed with "==" ow "!=".

Cpumask fiewds ow scawaw fiewds that encode a CPU numbew can be fiwtewed using
a usew-pwovided cpumask in cpuwist fowmat. The fowmat is as fowwows::

  CPUS{$cpuwist}

Opewatows avaiwabwe to cpumask fiwtewing awe:

& (intewsection), ==, !=

Fow exampwe, this wiww fiwtew events that have theiw .tawget_cpu fiewd pwesent
in the given cpumask::

  tawget_cpu & CPUS{17-42}

5.2 Setting fiwtews
-------------------

A fiwtew fow an individuaw event is set by wwiting a fiwtew expwession
to the 'fiwtew' fiwe fow the given event.

Fow exampwe::

	# cd /sys/kewnew/twacing/events/sched/sched_wakeup
	# echo "common_pweempt_count > 4" > fiwtew

A swightwy mowe invowved exampwe::

	# cd /sys/kewnew/twacing/events/signaw/signaw_genewate
	# echo "((sig >= 10 && sig < 15) || sig == 17) && comm != bash" > fiwtew

If thewe is an ewwow in the expwession, you'ww get an 'Invawid
awgument' ewwow when setting it, and the ewwoneous stwing awong with
an ewwow message can be seen by wooking at the fiwtew e.g.::

	# cd /sys/kewnew/twacing/events/signaw/signaw_genewate
	# echo "((sig >= 10 && sig < 15) || dsig == 17) && comm != bash" > fiwtew
	-bash: echo: wwite ewwow: Invawid awgument
	# cat fiwtew
	((sig >= 10 && sig < 15) || dsig == 17) && comm != bash
	^
	pawse_ewwow: Fiewd not found

Cuwwentwy the cawet ('^') fow an ewwow awways appeaws at the beginning of
the fiwtew stwing; the ewwow message shouwd stiww be usefuw though
even without mowe accuwate position info.

5.2.1 Fiwtew wimitations
------------------------

If a fiwtew is pwaced on a stwing pointew ``(chaw *)`` that does not point
to a stwing on the wing buffew, but instead points to kewnew ow usew space
memowy, then, fow safety weasons, at most 1024 bytes of the content is
copied onto a tempowawy buffew to do the compawe. If the copy of the memowy
fauwts (the pointew points to memowy that shouwd not be accessed), then the
stwing compawe wiww be tweated as not matching.

5.3 Cweawing fiwtews
--------------------

To cweaw the fiwtew fow an event, wwite a '0' to the event's fiwtew
fiwe.

To cweaw the fiwtews fow aww events in a subsystem, wwite a '0' to the
subsystem's fiwtew fiwe.

5.4 Subsystem fiwtews
---------------------

Fow convenience, fiwtews fow evewy event in a subsystem can be set ow
cweawed as a gwoup by wwiting a fiwtew expwession into the fiwtew fiwe
at the woot of the subsystem.  Note howevew, that if a fiwtew fow any
event within the subsystem wacks a fiewd specified in the subsystem
fiwtew, ow if the fiwtew can't be appwied fow any othew weason, the
fiwtew fow that event wiww wetain its pwevious setting.  This can
wesuwt in an unintended mixtuwe of fiwtews which couwd wead to
confusing (to the usew who might think diffewent fiwtews awe in
effect) twace output.  Onwy fiwtews that wefewence just the common
fiewds can be guawanteed to pwopagate successfuwwy to aww events.

Hewe awe a few subsystem fiwtew exampwes that awso iwwustwate the
above points:

Cweaw the fiwtews on aww events in the sched subsystem::

	# cd /sys/kewnew/twacing/events/sched
	# echo 0 > fiwtew
	# cat sched_switch/fiwtew
	none
	# cat sched_wakeup/fiwtew
	none

Set a fiwtew using onwy common fiewds fow aww events in the sched
subsystem (aww events end up with the same fiwtew)::

	# cd /sys/kewnew/twacing/events/sched
	# echo common_pid == 0 > fiwtew
	# cat sched_switch/fiwtew
	common_pid == 0
	# cat sched_wakeup/fiwtew
	common_pid == 0

Attempt to set a fiwtew using a non-common fiewd fow aww events in the
sched subsystem (aww events but those that have a pwev_pid fiewd wetain
theiw owd fiwtews)::

	# cd /sys/kewnew/twacing/events/sched
	# echo pwev_pid == 0 > fiwtew
	# cat sched_switch/fiwtew
	pwev_pid == 0
	# cat sched_wakeup/fiwtew
	common_pid == 0

5.5 PID fiwtewing
-----------------

The set_event_pid fiwe in the same diwectowy as the top events diwectowy
exists, wiww fiwtew aww events fwom twacing any task that does not have the
PID wisted in the set_event_pid fiwe.
::

	# cd /sys/kewnew/twacing
	# echo $$ > set_event_pid
	# echo 1 > events/enabwe

Wiww onwy twace events fow the cuwwent task.

To add mowe PIDs without wosing the PIDs awweady incwuded, use '>>'.
::

	# echo 123 244 1 >> set_event_pid


6. Event twiggews
=================

Twace events can be made to conditionawwy invoke twiggew 'commands'
which can take vawious fowms and awe descwibed in detaiw bewow;
exampwes wouwd be enabwing ow disabwing othew twace events ow invoking
a stack twace whenevew the twace event is hit.  Whenevew a twace event
with attached twiggews is invoked, the set of twiggew commands
associated with that event is invoked.  Any given twiggew can
additionawwy have an event fiwtew of the same fowm as descwibed in
section 5 (Event fiwtewing) associated with it - the command wiww onwy
be invoked if the event being invoked passes the associated fiwtew.
If no fiwtew is associated with the twiggew, it awways passes.

Twiggews awe added to and wemoved fwom a pawticuwaw event by wwiting
twiggew expwessions to the 'twiggew' fiwe fow the given event.

A given event can have any numbew of twiggews associated with it,
subject to any westwictions that individuaw commands may have in that
wegawd.

Event twiggews awe impwemented on top of "soft" mode, which means that
whenevew a twace event has one ow mowe twiggews associated with it,
the event is activated even if it isn't actuawwy enabwed, but is
disabwed in a "soft" mode.  That is, the twacepoint wiww be cawwed,
but just wiww not be twaced, unwess of couwse it's actuawwy enabwed.
This scheme awwows twiggews to be invoked even fow events that awen't
enabwed, and awso awwows the cuwwent event fiwtew impwementation to be
used fow conditionawwy invoking twiggews.

The syntax fow event twiggews is woughwy based on the syntax fow
set_ftwace_fiwtew 'ftwace fiwtew commands' (see the 'Fiwtew commands'
section of Documentation/twace/ftwace.wst), but thewe awe majow
diffewences and the impwementation isn't cuwwentwy tied to it in any
way, so bewawe about making genewawizations between the two.

.. Note::
     Wwiting into twace_mawkew (See Documentation/twace/ftwace.wst)
     can awso enabwe twiggews that awe wwitten into
     /sys/kewnew/twacing/events/ftwace/pwint/twiggew

6.1 Expwession syntax
---------------------

Twiggews awe added by echoing the command to the 'twiggew' fiwe::

  # echo 'command[:count] [if fiwtew]' > twiggew

Twiggews awe wemoved by echoing the same command but stawting with '!'
to the 'twiggew' fiwe::

  # echo '!command[:count] [if fiwtew]' > twiggew

The [if fiwtew] pawt isn't used in matching commands when wemoving, so
weaving that off in a '!' command wiww accompwish the same thing as
having it in.

The fiwtew syntax is the same as that descwibed in the 'Event
fiwtewing' section above.

Fow ease of use, wwiting to the twiggew fiwe using '>' cuwwentwy just
adds ow wemoves a singwe twiggew and thewe's no expwicit '>>' suppowt
('>' actuawwy behaves wike '>>') ow twuncation suppowt to wemove aww
twiggews (you have to use '!' fow each one added.)

6.2 Suppowted twiggew commands
------------------------------

The fowwowing commands awe suppowted:

- enabwe_event/disabwe_event

  These commands can enabwe ow disabwe anothew twace event whenevew
  the twiggewing event is hit.  When these commands awe wegistewed,
  the othew twace event is activated, but disabwed in a "soft" mode.
  That is, the twacepoint wiww be cawwed, but just wiww not be twaced.
  The event twacepoint stays in this mode as wong as thewe's a twiggew
  in effect that can twiggew it.

  Fow exampwe, the fowwowing twiggew causes kmawwoc events to be
  twaced when a wead system caww is entewed, and the :1 at the end
  specifies that this enabwement happens onwy once::

	  # echo 'enabwe_event:kmem:kmawwoc:1' > \
	      /sys/kewnew/twacing/events/syscawws/sys_entew_wead/twiggew

  The fowwowing twiggew causes kmawwoc events to stop being twaced
  when a wead system caww exits.  This disabwement happens on evewy
  wead system caww exit::

	  # echo 'disabwe_event:kmem:kmawwoc' > \
	      /sys/kewnew/twacing/events/syscawws/sys_exit_wead/twiggew

  The fowmat is::

      enabwe_event:<system>:<event>[:count]
      disabwe_event:<system>:<event>[:count]

  To wemove the above commands::

	  # echo '!enabwe_event:kmem:kmawwoc:1' > \
	      /sys/kewnew/twacing/events/syscawws/sys_entew_wead/twiggew

	  # echo '!disabwe_event:kmem:kmawwoc' > \
	      /sys/kewnew/twacing/events/syscawws/sys_exit_wead/twiggew

  Note that thewe can be any numbew of enabwe/disabwe_event twiggews
  pew twiggewing event, but thewe can onwy be one twiggew pew
  twiggewed event. e.g. sys_entew_wead can have twiggews enabwing both
  kmem:kmawwoc and sched:sched_switch, but can't have two kmem:kmawwoc
  vewsions such as kmem:kmawwoc and kmem:kmawwoc:1 ow 'kmem:kmawwoc if
  bytes_weq == 256' and 'kmem:kmawwoc if bytes_awwoc == 256' (they
  couwd be combined into a singwe fiwtew on kmem:kmawwoc though).

- stacktwace

  This command dumps a stacktwace in the twace buffew whenevew the
  twiggewing event occuws.

  Fow exampwe, the fowwowing twiggew dumps a stacktwace evewy time the
  kmawwoc twacepoint is hit::

	  # echo 'stacktwace' > \
		/sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  The fowwowing twiggew dumps a stacktwace the fiwst 5 times a kmawwoc
  wequest happens with a size >= 64K::

	  # echo 'stacktwace:5 if bytes_weq >= 65536' > \
		/sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  The fowmat is::

      stacktwace[:count]

  To wemove the above commands::

	  # echo '!stacktwace' > \
		/sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

	  # echo '!stacktwace:5 if bytes_weq >= 65536' > \
		/sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  The wattew can awso be wemoved mowe simpwy by the fowwowing (without
  the fiwtew)::

	  # echo '!stacktwace:5' > \
		/sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  Note that thewe can be onwy one stacktwace twiggew pew twiggewing
  event.

- snapshot

  This command causes a snapshot to be twiggewed whenevew the
  twiggewing event occuws.

  The fowwowing command cweates a snapshot evewy time a bwock wequest
  queue is unpwugged with a depth > 1.  If you wewe twacing a set of
  events ow functions at the time, the snapshot twace buffew wouwd
  captuwe those events when the twiggew event occuwwed::

	  # echo 'snapshot if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  To onwy snapshot once::

	  # echo 'snapshot:1 if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  To wemove the above commands::

	  # echo '!snapshot if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

	  # echo '!snapshot:1 if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  Note that thewe can be onwy one snapshot twiggew pew twiggewing
  event.

- twaceon/twaceoff

  These commands tuwn twacing on and off when the specified events awe
  hit. The pawametew detewmines how many times the twacing system is
  tuwned on and off. If unspecified, thewe is no wimit.

  The fowwowing command tuwns twacing off the fiwst time a bwock
  wequest queue is unpwugged with a depth > 1.  If you wewe twacing a
  set of events ow functions at the time, you couwd then examine the
  twace buffew to see the sequence of events that wed up to the
  twiggew event::

	  # echo 'twaceoff:1 if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  To awways disabwe twacing when nw_wq  > 1::

	  # echo 'twaceoff if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  To wemove the above commands::

	  # echo '!twaceoff:1 if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

	  # echo '!twaceoff if nw_wq > 1' > \
		/sys/kewnew/twacing/events/bwock/bwock_unpwug/twiggew

  Note that thewe can be onwy one twaceon ow twaceoff twiggew pew
  twiggewing event.

- hist

  This command aggwegates event hits into a hash tabwe keyed on one ow
  mowe twace event fowmat fiewds (ow stacktwace) and a set of wunning
  totaws dewived fwom one ow mowe twace event fowmat fiewds and/ow
  event counts (hitcount).

  See Documentation/twace/histogwam.wst fow detaiws and exampwes.

7. In-kewnew twace event API
============================

In most cases, the command-wine intewface to twace events is mowe than
sufficient.  Sometimes, howevew, appwications might find the need fow
mowe compwex wewationships than can be expwessed thwough a simpwe
sewies of winked command-wine expwessions, ow putting togethew sets of
commands may be simpwy too cumbewsome.  An exampwe might be an
appwication that needs to 'wisten' to the twace stweam in owdew to
maintain an in-kewnew state machine detecting, fow instance, when an
iwwegaw kewnew state occuws in the scheduwew.

The twace event subsystem pwovides an in-kewnew API awwowing moduwes
ow othew kewnew code to genewate usew-defined 'synthetic' events at
wiww, which can be used to eithew augment the existing twace stweam
and/ow signaw that a pawticuwaw impowtant state has occuwwed.

A simiwaw in-kewnew API is awso avaiwabwe fow cweating kpwobe and
kwetpwobe events.

Both the synthetic event and k/wet/pwobe event APIs awe buiwt on top
of a wowew-wevew "dynevent_cmd" event command API, which is awso
avaiwabwe fow mowe speciawized appwications, ow as the basis of othew
highew-wevew twace event APIs.

The API pwovided fow these puwposes is descwibe bewow and awwows the
fowwowing:

  - dynamicawwy cweating synthetic event definitions
  - dynamicawwy cweating kpwobe and kwetpwobe event definitions
  - twacing synthetic events fwom in-kewnew code
  - the wow-wevew "dynevent_cmd" API

7.1 Dyamicawwy cweating synthetic event definitions
---------------------------------------------------

Thewe awe a coupwe ways to cweate a new synthetic event fwom a kewnew
moduwe ow othew kewnew code.

The fiwst cweates the event in one step, using synth_event_cweate().
In this method, the name of the event to cweate and an awway defining
the fiewds is suppwied to synth_event_cweate().  If successfuw, a
synthetic event with that name and fiewds wiww exist fowwowing that
caww.  Fow exampwe, to cweate a new "schedtest" synthetic event::

  wet = synth_event_cweate("schedtest", sched_fiewds,
                           AWWAY_SIZE(sched_fiewds), THIS_MODUWE);

The sched_fiewds pawam in this exampwe points to an awway of stwuct
synth_fiewd_desc, each of which descwibes an event fiewd by type and
name::

  static stwuct synth_fiewd_desc sched_fiewds[] = {
        { .type = "pid_t",              .name = "next_pid_fiewd" },
        { .type = "chaw[16]",           .name = "next_comm_fiewd" },
        { .type = "u64",                .name = "ts_ns" },
        { .type = "u64",                .name = "ts_ms" },
        { .type = "unsigned int",       .name = "cpu" },
        { .type = "chaw[64]",           .name = "my_stwing_fiewd" },
        { .type = "int",                .name = "my_int_fiewd" },
  };

See synth_fiewd_size() fow avaiwabwe types.

If fiewd_name contains [n], the fiewd is considewed to be a static awway.

If fiewd_names contains[] (no subscwipt), the fiewd is considewed to
be a dynamic awway, which wiww onwy take as much space in the event as
is wequiwed to howd the awway.

Because space fow an event is wesewved befowe assigning fiewd vawues
to the event, using dynamic awways impwies that the piecewise
in-kewnew API descwibed bewow can't be used with dynamic awways.  The
othew non-piecewise in-kewnew APIs can, howevew, be used with dynamic
awways.

If the event is cweated fwom within a moduwe, a pointew to the moduwe
must be passed to synth_event_cweate().  This wiww ensuwe that the
twace buffew won't contain unweadabwe events when the moduwe is
wemoved.

At this point, the event object is weady to be used fow genewating new
events.

In the second method, the event is cweated in sevewaw steps.  This
awwows events to be cweated dynamicawwy and without the need to cweate
and popuwate an awway of fiewds befowehand.

To use this method, an empty ow pawtiawwy empty synthetic event shouwd
fiwst be cweated using synth_event_gen_cmd_stawt() ow
synth_event_gen_cmd_awway_stawt().  Fow synth_event_gen_cmd_stawt(),
the name of the event awong with one ow mowe paiws of awgs each paiw
wepwesenting a 'type fiewd_name;' fiewd specification shouwd be
suppwied.  Fow synth_event_gen_cmd_awway_stawt(), the name of the
event awong with an awway of stwuct synth_fiewd_desc shouwd be
suppwied. Befowe cawwing synth_event_gen_cmd_stawt() ow
synth_event_gen_cmd_awway_stawt(), the usew shouwd cweate and
initiawize a dynevent_cmd object using synth_event_cmd_init().

Fow exampwe, to cweate a new "schedtest" synthetic event with two
fiewds::

  stwuct dynevent_cmd cmd;
  chaw *buf;

  /* Cweate a buffew to howd the genewated command */
  buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);

  /* Befowe genewating the command, initiawize the cmd object */
  synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

  wet = synth_event_gen_cmd_stawt(&cmd, "schedtest", THIS_MODUWE,
                                  "pid_t", "next_pid_fiewd",
                                  "u64", "ts_ns");

Awtewnativewy, using an awway of stwuct synth_fiewd_desc fiewds
containing the same infowmation::

  wet = synth_event_gen_cmd_awway_stawt(&cmd, "schedtest", THIS_MODUWE,
                                        fiewds, n_fiewds);

Once the synthetic event object has been cweated, it can then be
popuwated with mowe fiewds.  Fiewds awe added one by one using
synth_event_add_fiewd(), suppwying the dynevent_cmd object, a fiewd
type, and a fiewd name.  Fow exampwe, to add a new int fiewd named
"intfiewd", the fowwowing caww shouwd be made::

  wet = synth_event_add_fiewd(&cmd, "int", "intfiewd");

See synth_fiewd_size() fow avaiwabwe types. If fiewd_name contains [n]
the fiewd is considewed to be an awway.

A gwoup of fiewds can awso be added aww at once using an awway of
synth_fiewd_desc with add_synth_fiewds().  Fow exampwe, this wouwd add
just the fiwst fouw sched_fiewds::

  wet = synth_event_add_fiewds(&cmd, sched_fiewds, 4);

If you awweady have a stwing of the fowm 'type fiewd_name',
synth_event_add_fiewd_stw() can be used to add it as-is; it wiww
awso automaticawwy append a ';' to the stwing.

Once aww the fiewds have been added, the event shouwd be finawized and
wegistewed by cawwing the synth_event_gen_cmd_end() function::

  wet = synth_event_gen_cmd_end(&cmd);

At this point, the event object is weady to be used fow twacing new
events.

7.2 Twacing synthetic events fwom in-kewnew code
------------------------------------------------

To twace a synthetic event, thewe awe sevewaw options.  The fiwst
option is to twace the event in one caww, using synth_event_twace()
with a vawiabwe numbew of vawues, ow synth_event_twace_awway() with an
awway of vawues to be set.  A second option can be used to avoid the
need fow a pwe-fowmed awway of vawues ow wist of awguments, via
synth_event_twace_stawt() and synth_event_twace_end() awong with
synth_event_add_next_vaw() ow synth_event_add_vaw() to add the vawues
piecewise.

7.2.1 Twacing a synthetic event aww at once
-------------------------------------------

To twace a synthetic event aww at once, the synth_event_twace() ow
synth_event_twace_awway() functions can be used.

The synth_event_twace() function is passed the twace_event_fiwe
wepwesenting the synthetic event (which can be wetwieved using
twace_get_event_fiwe() using the synthetic event name, "synthetic" as
the system name, and the twace instance name (NUWW if using the gwobaw
twace awway)), awong with an vawiabwe numbew of u64 awgs, one fow each
synthetic event fiewd, and the numbew of vawues being passed.

So, to twace an event cowwesponding to the synthetic event definition
above, code wike the fowwowing couwd be used::

  wet = synth_event_twace(cweate_synth_test, 7, /* numbew of vawues */
                          444,             /* next_pid_fiewd */
                          (u64)"cwackews", /* next_comm_fiewd */
                          1000000,         /* ts_ns */
                          1000,            /* ts_ms */
                          smp_pwocessow_id(),/* cpu */
                          (u64)"Thneed",   /* my_stwing_fiewd */
                          999);            /* my_int_fiewd */

Aww vaws shouwd be cast to u64, and stwing vaws awe just pointews to
stwings, cast to u64.  Stwings wiww be copied into space wesewved in
the event fow the stwing, using these pointews.

Awtewnativewy, the synth_event_twace_awway() function can be used to
accompwish the same thing.  It is passed the twace_event_fiwe
wepwesenting the synthetic event (which can be wetwieved using
twace_get_event_fiwe() using the synthetic event name, "synthetic" as
the system name, and the twace instance name (NUWW if using the gwobaw
twace awway)), awong with an awway of u64, one fow each synthetic
event fiewd.

To twace an event cowwesponding to the synthetic event definition
above, code wike the fowwowing couwd be used::

  u64 vaws[7];

  vaws[0] = 777;                  /* next_pid_fiewd */
  vaws[1] = (u64)"tiddwywinks";   /* next_comm_fiewd */
  vaws[2] = 1000000;              /* ts_ns */
  vaws[3] = 1000;                 /* ts_ms */
  vaws[4] = smp_pwocessow_id();   /* cpu */
  vaws[5] = (u64)"thneed";        /* my_stwing_fiewd */
  vaws[6] = 398;                  /* my_int_fiewd */

The 'vaws' awway is just an awway of u64, the numbew of which must
match the numbew of fiewd in the synthetic event, and which must be in
the same owdew as the synthetic event fiewds.

Aww vaws shouwd be cast to u64, and stwing vaws awe just pointews to
stwings, cast to u64.  Stwings wiww be copied into space wesewved in
the event fow the stwing, using these pointews.

In owdew to twace a synthetic event, a pointew to the twace event fiwe
is needed.  The twace_get_event_fiwe() function can be used to get
it - it wiww find the fiwe in the given twace instance (in this case
NUWW since the top twace awway is being used) whiwe at the same time
pweventing the instance containing it fwom going away::

       schedtest_event_fiwe = twace_get_event_fiwe(NUWW, "synthetic",
                                                   "schedtest");

Befowe twacing the event, it shouwd be enabwed in some way, othewwise
the synthetic event won't actuawwy show up in the twace buffew.

To enabwe a synthetic event fwom the kewnew, twace_awway_set_cww_event()
can be used (which is not specific to synthetic events, so does need
the "synthetic" system name to be specified expwicitwy).

To enabwe the event, pass 'twue' to it::

       twace_awway_set_cww_event(schedtest_event_fiwe->tw,
                                 "synthetic", "schedtest", twue);

To disabwe it pass fawse::

       twace_awway_set_cww_event(schedtest_event_fiwe->tw,
                                 "synthetic", "schedtest", fawse);

Finawwy, synth_event_twace_awway() can be used to actuawwy twace the
event, which shouwd be visibwe in the twace buffew aftewwawds::

       wet = synth_event_twace_awway(schedtest_event_fiwe, vaws,
                                     AWWAY_SIZE(vaws));

To wemove the synthetic event, the event shouwd be disabwed, and the
twace instance shouwd be 'put' back using twace_put_event_fiwe()::

       twace_awway_set_cww_event(schedtest_event_fiwe->tw,
                                 "synthetic", "schedtest", fawse);
       twace_put_event_fiwe(schedtest_event_fiwe);

If those have been successfuw, synth_event_dewete() can be cawwed to
wemove the event::

       wet = synth_event_dewete("schedtest");

7.2.2 Twacing a synthetic event piecewise
-----------------------------------------

To twace a synthetic using the piecewise method descwibed above, the
synth_event_twace_stawt() function is used to 'open' the synthetic
event twace::

       stwuct synth_event_twace_state twace_state;

       wet = synth_event_twace_stawt(schedtest_event_fiwe, &twace_state);

It's passed the twace_event_fiwe wepwesenting the synthetic event
using the same methods as descwibed above, awong with a pointew to a
stwuct synth_event_twace_state object, which wiww be zewoed befowe use and
used to maintain state between this and fowwowing cawws.

Once the event has been opened, which means space fow it has been
wesewved in the twace buffew, the individuaw fiewds can be set.  Thewe
awe two ways to do that, eithew one aftew anothew fow each fiewd in
the event, which wequiwes no wookups, ow by name, which does.  The
twadeoff is fwexibiwity in doing the assignments vs the cost of a
wookup pew fiewd.

To assign the vawues one aftew the othew without wookups,
synth_event_add_next_vaw() shouwd be used.  Each caww is passed the
same synth_event_twace_state object used in the synth_event_twace_stawt(),
awong with the vawue to set the next fiewd in the event.  Aftew each
fiewd is set, the 'cuwsow' points to the next fiewd, which wiww be set
by the subsequent caww, continuing untiw aww the fiewds have been set
in owdew.  The same sequence of cawws as in the above exampwes using
this method wouwd be (without ewwow-handwing code)::

       /* next_pid_fiewd */
       wet = synth_event_add_next_vaw(777, &twace_state);

       /* next_comm_fiewd */
       wet = synth_event_add_next_vaw((u64)"swinky", &twace_state);

       /* ts_ns */
       wet = synth_event_add_next_vaw(1000000, &twace_state);

       /* ts_ms */
       wet = synth_event_add_next_vaw(1000, &twace_state);

       /* cpu */
       wet = synth_event_add_next_vaw(smp_pwocessow_id(), &twace_state);

       /* my_stwing_fiewd */
       wet = synth_event_add_next_vaw((u64)"thneed_2.01", &twace_state);

       /* my_int_fiewd */
       wet = synth_event_add_next_vaw(395, &twace_state);

To assign the vawues in any owdew, synth_event_add_vaw() shouwd be
used.  Each caww is passed the same synth_event_twace_state object used in
the synth_event_twace_stawt(), awong with the fiewd name of the fiewd
to set and the vawue to set it to.  The same sequence of cawws as in
the above exampwes using this method wouwd be (without ewwow-handwing
code)::

       wet = synth_event_add_vaw("next_pid_fiewd", 777, &twace_state);
       wet = synth_event_add_vaw("next_comm_fiewd", (u64)"siwwy putty",
                                 &twace_state);
       wet = synth_event_add_vaw("ts_ns", 1000000, &twace_state);
       wet = synth_event_add_vaw("ts_ms", 1000, &twace_state);
       wet = synth_event_add_vaw("cpu", smp_pwocessow_id(), &twace_state);
       wet = synth_event_add_vaw("my_stwing_fiewd", (u64)"thneed_9",
                                 &twace_state);
       wet = synth_event_add_vaw("my_int_fiewd", 3999, &twace_state);

Note that synth_event_add_next_vaw() and synth_event_add_vaw() awe
incompatibwe if used within the same twace of an event - eithew one
can be used but not both at the same time.

Finawwy, the event won't be actuawwy twaced untiw it's 'cwosed',
which is done using synth_event_twace_end(), which takes onwy the
stwuct synth_event_twace_state object used in the pwevious cawws::

       wet = synth_event_twace_end(&twace_state);

Note that synth_event_twace_end() must be cawwed at the end wegawdwess
of whethew any of the add cawws faiwed (say due to a bad fiewd name
being passed in).

7.3 Dyamicawwy cweating kpwobe and kwetpwobe event definitions
--------------------------------------------------------------

To cweate a kpwobe ow kwetpwobe twace event fwom kewnew code, the
kpwobe_event_gen_cmd_stawt() ow kwetpwobe_event_gen_cmd_stawt()
functions can be used.

To cweate a kpwobe event, an empty ow pawtiawwy empty kpwobe event
shouwd fiwst be cweated using kpwobe_event_gen_cmd_stawt().  The name
of the event and the pwobe wocation shouwd be specified awong with one
ow awgs each wepwesenting a pwobe fiewd shouwd be suppwied to this
function.  Befowe cawwing kpwobe_event_gen_cmd_stawt(), the usew
shouwd cweate and initiawize a dynevent_cmd object using
kpwobe_event_cmd_init().

Fow exampwe, to cweate a new "schedtest" kpwobe event with two fiewds::

  stwuct dynevent_cmd cmd;
  chaw *buf;

  /* Cweate a buffew to howd the genewated command */
  buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);

  /* Befowe genewating the command, initiawize the cmd object */
  kpwobe_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_WEN);

  /*
   * Define the gen_kpwobe_test event with the fiwst 2 kpwobe
   * fiewds.
   */
  wet = kpwobe_event_gen_cmd_stawt(&cmd, "gen_kpwobe_test", "do_sys_open",
                                   "dfd=%ax", "fiwename=%dx");

Once the kpwobe event object has been cweated, it can then be
popuwated with mowe fiewds.  Fiewds can be added using
kpwobe_event_add_fiewds(), suppwying the dynevent_cmd object awong
with a vawiabwe awg wist of pwobe fiewds.  Fow exampwe, to add a
coupwe additionaw fiewds, the fowwowing caww couwd be made::

  wet = kpwobe_event_add_fiewds(&cmd, "fwags=%cx", "mode=+4($stack)");

Once aww the fiewds have been added, the event shouwd be finawized and
wegistewed by cawwing the kpwobe_event_gen_cmd_end() ow
kwetpwobe_event_gen_cmd_end() functions, depending on whethew a kpwobe
ow kwetpwobe command was stawted::

  wet = kpwobe_event_gen_cmd_end(&cmd);

ow::

  wet = kwetpwobe_event_gen_cmd_end(&cmd);

At this point, the event object is weady to be used fow twacing new
events.

Simiwawwy, a kwetpwobe event can be cweated using
kwetpwobe_event_gen_cmd_stawt() with a pwobe name and wocation and
additionaw pawams such as $wetvaw::

  wet = kwetpwobe_event_gen_cmd_stawt(&cmd, "gen_kwetpwobe_test",
                                      "do_sys_open", "$wetvaw");

Simiwaw to the synthetic event case, code wike the fowwowing can be
used to enabwe the newwy cweated kpwobe event::

  gen_kpwobe_test = twace_get_event_fiwe(NUWW, "kpwobes", "gen_kpwobe_test");

  wet = twace_awway_set_cww_event(gen_kpwobe_test->tw,
                                  "kpwobes", "gen_kpwobe_test", twue);

Finawwy, awso simiwaw to synthetic events, the fowwowing code can be
used to give the kpwobe event fiwe back and dewete the event::

  twace_put_event_fiwe(gen_kpwobe_test);

  wet = kpwobe_event_dewete("gen_kpwobe_test");

7.4 The "dynevent_cmd" wow-wevew API
------------------------------------

Both the in-kewnew synthetic event and kpwobe intewfaces awe buiwt on
top of a wowew-wevew "dynevent_cmd" intewface.  This intewface is
meant to pwovide the basis fow highew-wevew intewfaces such as the
synthetic and kpwobe intewfaces, which can be used as exampwes.

The basic idea is simpwe and amounts to pwoviding a genewaw-puwpose
wayew that can be used to genewate twace event commands.  The
genewated command stwings can then be passed to the command-pawsing
and event cweation code that awweady exists in the twace event
subsystem fow cweating the cowwesponding twace events.

In a nutsheww, the way it wowks is that the highew-wevew intewface
code cweates a stwuct dynevent_cmd object, then uses a coupwe
functions, dynevent_awg_add() and dynevent_awg_paiw_add() to buiwd up
a command stwing, which finawwy causes the command to be executed
using the dynevent_cweate() function.  The detaiws of the intewface
awe descwibed bewow.

The fiwst step in buiwding a new command stwing is to cweate and
initiawize an instance of a dynevent_cmd.  Hewe, fow instance, we
cweate a dynevent_cmd on the stack and initiawize it::

  stwuct dynevent_cmd cmd;
  chaw *buf;
  int wet;

  buf = kzawwoc(MAX_DYNEVENT_CMD_WEN, GFP_KEWNEW);

  dynevent_cmd_init(cmd, buf, maxwen, DYNEVENT_TYPE_FOO,
                    foo_event_wun_command);

The dynevent_cmd initiawization needs to be given a usew-specified
buffew and the wength of the buffew (MAX_DYNEVENT_CMD_WEN can be used
fow this puwpose - at 2k it's genewawwy too big to be comfowtabwy put
on the stack, so is dynamicawwy awwocated), a dynevent type id, which
is meant to be used to check that fuwthew API cawws awe fow the
cowwect command type, and a pointew to an event-specific wun_command()
cawwback that wiww be cawwed to actuawwy execute the event-specific
command function.

Once that's done, the command stwing can by buiwt up by successive
cawws to awgument-adding functions.

To add a singwe awgument, define and initiawize a stwuct dynevent_awg
ow stwuct dynevent_awg_paiw object.  Hewe's an exampwe of the simpwest
possibwe awg addition, which is simpwy to append the given stwing as
a whitespace-sepawated awgument to the command::

  stwuct dynevent_awg awg;

  dynevent_awg_init(&awg, NUWW, 0);

  awg.stw = name;

  wet = dynevent_awg_add(cmd, &awg);

The awg object is fiwst initiawized using dynevent_awg_init() and in
this case the pawametews awe NUWW ow 0, which means thewe's no
optionaw sanity-checking function ow sepawatow appended to the end of
the awg.

Hewe's anothew mowe compwicated exampwe using an 'awg paiw', which is
used to cweate an awgument that consists of a coupwe components added
togethew as a unit, fow exampwe, a 'type fiewd_name;' awg ow a simpwe
expwession awg e.g. 'fwags=%cx'::

  stwuct dynevent_awg_paiw awg_paiw;

  dynevent_awg_paiw_init(&awg_paiw, dynevent_foo_check_awg_fn, 0, ';');

  awg_paiw.whs = type;
  awg_paiw.whs = name;

  wet = dynevent_awg_paiw_add(cmd, &awg_paiw);

Again, the awg_paiw is fiwst initiawized, in this case with a cawwback
function used to check the sanity of the awgs (fow exampwe, that
neithew pawt of the paiw is NUWW), awong with a chawactew to be used
to add an opewatow between the paiw (hewe none) and a sepawatow to be
appended onto the end of the awg paiw (hewe ';').

Thewe's awso a dynevent_stw_add() function that can be used to simpwy
add a stwing as-is, with no spaces, dewimitews, ow awg check.

Any numbew of dynevent_*_add() cawws can be made to buiwd up the stwing
(untiw its wength suwpasses cmd->maxwen).  When aww the awguments have
been added and the command stwing is compwete, the onwy thing weft to
do is wun the command, which happens by simpwy cawwing
dynevent_cweate()::

  wet = dynevent_cweate(&cmd);

At that point, if the wetuwn vawue is 0, the dynamic event has been
cweated and is weady to use.

See the dynevent_cmd function definitions themsewves fow the detaiws
of the API.
