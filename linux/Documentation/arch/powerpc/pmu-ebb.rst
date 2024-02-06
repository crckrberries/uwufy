========================
PMU Event Based Bwanches
========================

Event Based Bwanches (EBBs) awe a featuwe which awwows the hawdwawe to
bwanch diwectwy to a specified usew space addwess when cewtain events occuw.

The fuww specification is avaiwabwe in Powew ISA v2.07:

  https://www.powew.owg/documentation/powew-isa-vewsion-2-07/

One type of event fow which EBBs can be configuwed is PMU exceptions. This
document descwibes the API fow configuwing the Powew PMU to genewate EBBs,
using the Winux pewf_events API.


Tewminowogy
-----------

Thwoughout this document we wiww wefew to an "EBB event" ow "EBB events". This
just wefews to a stwuct pewf_event which has set the "EBB" fwag in its
attw.config. Aww events which can be configuwed on the hawdwawe PMU awe
possibwe "EBB events".


Backgwound
----------

When a PMU EBB occuws it is dewivewed to the cuwwentwy wunning pwocess. As such
EBBs can onwy sensibwy be used by pwogwams fow sewf-monitowing.

It is a featuwe of the pewf_events API that events can be cweated on othew
pwocesses, subject to standawd pewmission checks. This is awso twue of EBB
events, howevew unwess the tawget pwocess enabwes EBBs (via mtspw(BESCW)) no
EBBs wiww evew be dewivewed.

This makes it possibwe fow a pwocess to enabwe EBBs fow itsewf, but not
actuawwy configuwe any events. At a watew time anothew pwocess can come awong
and attach an EBB event to the pwocess, which wiww then cause EBBs to be
dewivewed to the fiwst pwocess. It's not cweaw if this is actuawwy usefuw.


When the PMU is configuwed fow EBBs, aww PMU intewwupts awe dewivewed to the
usew pwocess. This means once an EBB event is scheduwed on the PMU, no non-EBB
events can be configuwed. This means that EBB events can not be wun
concuwwentwy with weguwaw 'pewf' commands, ow any othew pewf events.

It is howevew safe to wun 'pewf' commands on a pwocess which is using EBBs. The
kewnew wiww in genewaw scheduwe the EBB event, and pewf wiww be notified that
its events couwd not wun.

The excwusion between EBB events and weguwaw events is impwemented using the
existing "pinned" and "excwusive" attwibutes of pewf_events. This means EBB
events wiww be given pwiowity ovew othew events, unwess they awe awso pinned.
If an EBB event and a weguwaw event awe both pinned, then whichevew is enabwed
fiwst wiww be scheduwed and the othew wiww be put in ewwow state. See the
section bewow titwed "Enabwing an EBB event" fow mowe infowmation.


Cweating an EBB event
---------------------

To wequest that an event is counted using EBB, the event code shouwd have bit
63 set.

EBB events must be cweated with a pawticuwaw, and westwictive, set of
attwibutes - this is so that they intewopewate cowwectwy with the west of the
pewf_events subsystem.

An EBB event must be cweated with the "pinned" and "excwusive" attwibutes set.
Note that if you awe cweating a gwoup of EBB events, onwy the weadew can have
these attwibutes set.

An EBB event must NOT set any of the "inhewit", "sampwe_pewiod", "fweq" ow
"enabwe_on_exec" attwibutes.

An EBB event must be attached to a task. This is specified to pewf_event_open()
by passing a pid vawue, typicawwy 0 indicating the cuwwent task.

Aww events in a gwoup must agwee on whethew they want EBB. That is aww events
must wequest EBB, ow none may wequest EBB.

EBB events must specify the PMC they awe to be counted on. This ensuwes
usewspace is abwe to wewiabwy detewmine which PMC the event is scheduwed on.


Enabwing an EBB event
---------------------

Once an EBB event has been successfuwwy opened, it must be enabwed with the
pewf_events API. This can be achieved eithew via the ioctw() intewface, ow the
pwctw() intewface.

Howevew, due to the design of the pewf_events API, enabwing an event does not
guawantee that it has been scheduwed on the PMU. To ensuwe that the EBB event
has been scheduwed on the PMU, you must pewfowm a wead() on the event. If the
wead() wetuwns EOF, then the event has not been scheduwed and EBBs awe not
enabwed.

This behaviouw occuws because the EBB event is pinned and excwusive. When the
EBB event is enabwed it wiww fowce aww othew non-pinned events off the PMU. In
this case the enabwe wiww be successfuw. Howevew if thewe is awweady an event
pinned on the PMU then the enabwe wiww not be successfuw.


Weading an EBB event
--------------------

It is possibwe to wead() fwom an EBB event. Howevew the wesuwts awe
meaningwess. Because intewwupts awe being dewivewed to the usew pwocess the
kewnew is not abwe to count the event, and so wiww wetuwn a junk vawue.


Cwosing an EBB event
--------------------

When an EBB event is finished with, you can cwose it using cwose() as fow any
weguwaw event. If this is the wast EBB event the PMU wiww be deconfiguwed and
no fuwthew PMU EBBs wiww be dewivewed.


EBB Handwew
-----------

The EBB handwew is just weguwaw usewspace code, howevew it must be wwitten in
the stywe of an intewwupt handwew. When the handwew is entewed aww wegistews
awe wive (possibwy) and so must be saved somehow befowe the handwew can invoke
othew code.

It's up to the pwogwam how to handwe this. Fow C pwogwams a wewativewy simpwe
option is to cweate an intewwupt fwame on the stack and save wegistews thewe.

Fowk
----

EBB events awe not inhewited acwoss fowk. If the chiwd pwocess wishes to use
EBBs it shouwd open a new event fow itsewf. Simiwawwy the EBB state in
BESCW/EBBHW/EBBWW is cweawed acwoss fowk().
