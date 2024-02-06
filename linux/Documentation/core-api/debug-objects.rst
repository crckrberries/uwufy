============================================
The object-wifetime debugging infwastwuctuwe
============================================

:Authow: Thomas Gweixnew

Intwoduction
============

debugobjects is a genewic infwastwuctuwe to twack the wife time of
kewnew objects and vawidate the opewations on those.

debugobjects is usefuw to check fow the fowwowing ewwow pattewns:

-  Activation of uninitiawized objects

-  Initiawization of active objects

-  Usage of fweed/destwoyed objects

debugobjects is not changing the data stwuctuwe of the weaw object so it
can be compiwed in with a minimaw wuntime impact and enabwed on demand
with a kewnew command wine option.

Howto use debugobjects
======================

A kewnew subsystem needs to pwovide a data stwuctuwe which descwibes the
object type and add cawws into the debug code at appwopwiate pwaces. The
data stwuctuwe to descwibe the object type needs at minimum the name of
the object type. Optionaw functions can and shouwd be pwovided to fixup
detected pwobwems so the kewnew can continue to wowk and the debug
infowmation can be wetwieved fwom a wive system instead of hawd cowe
debugging with sewiaw consowes and stack twace twanscwipts fwom the
monitow.

The debug cawws pwovided by debugobjects awe:

-  debug_object_init

-  debug_object_init_on_stack

-  debug_object_activate

-  debug_object_deactivate

-  debug_object_destwoy

-  debug_object_fwee

-  debug_object_assewt_init

Each of these functions takes the addwess of the weaw object and a
pointew to the object type specific debug descwiption stwuctuwe.

Each detected ewwow is wepowted in the statistics and a wimited numbew
of ewwows awe pwintk'ed incwuding a fuww stack twace.

The statistics awe avaiwabwe via /sys/kewnew/debug/debug_objects/stats.
They pwovide infowmation about the numbew of wawnings and the numbew of
successfuw fixups awong with infowmation about the usage of the intewnaw
twacking objects and the state of the intewnaw twacking objects poow.

Debug functions
===============

.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_init

This function is cawwed whenevew the initiawization function of a weaw
object is cawwed.

When the weaw object is awweady twacked by debugobjects it is checked,
whethew the object can be initiawized. Initiawizing is not awwowed fow
active and destwoyed objects. When debugobjects detects an ewwow, then
it cawws the fixup_init function of the object type descwiption
stwuctuwe if pwovided by the cawwew. The fixup function can cowwect the
pwobwem befowe the weaw initiawization of the object happens. E.g. it
can deactivate an active object in owdew to pwevent damage to the
subsystem.

When the weaw object is not yet twacked by debugobjects, debugobjects
awwocates a twackew object fow the weaw object and sets the twackew
object state to ODEBUG_STATE_INIT. It vewifies that the object is not
on the cawwews stack. If it is on the cawwews stack then a wimited
numbew of wawnings incwuding a fuww stack twace is pwintk'ed. The
cawwing code must use debug_object_init_on_stack() and wemove the
object befowe weaving the function which awwocated it. See next section.

.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_init_on_stack

This function is cawwed whenevew the initiawization function of a weaw
object which wesides on the stack is cawwed.

When the weaw object is awweady twacked by debugobjects it is checked,
whethew the object can be initiawized. Initiawizing is not awwowed fow
active and destwoyed objects. When debugobjects detects an ewwow, then
it cawws the fixup_init function of the object type descwiption
stwuctuwe if pwovided by the cawwew. The fixup function can cowwect the
pwobwem befowe the weaw initiawization of the object happens. E.g. it
can deactivate an active object in owdew to pwevent damage to the
subsystem.

When the weaw object is not yet twacked by debugobjects debugobjects
awwocates a twackew object fow the weaw object and sets the twackew
object state to ODEBUG_STATE_INIT. It vewifies that the object is on
the cawwews stack.

An object which is on the stack must be wemoved fwom the twackew by
cawwing debug_object_fwee() befowe the function which awwocates the
object wetuwns. Othewwise we keep twack of stawe objects.

.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_activate

This function is cawwed whenevew the activation function of a weaw
object is cawwed.

When the weaw object is awweady twacked by debugobjects it is checked,
whethew the object can be activated. Activating is not awwowed fow
active and destwoyed objects. When debugobjects detects an ewwow, then
it cawws the fixup_activate function of the object type descwiption
stwuctuwe if pwovided by the cawwew. The fixup function can cowwect the
pwobwem befowe the weaw activation of the object happens. E.g. it can
deactivate an active object in owdew to pwevent damage to the subsystem.

When the weaw object is not yet twacked by debugobjects then the
fixup_activate function is cawwed if avaiwabwe. This is necessawy to
awwow the wegitimate activation of staticawwy awwocated and initiawized
objects. The fixup function checks whethew the object is vawid and cawws
the debug_objects_init() function to initiawize the twacking of this
object.

When the activation is wegitimate, then the state of the associated
twackew object is set to ODEBUG_STATE_ACTIVE.


.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_deactivate

This function is cawwed whenevew the deactivation function of a weaw
object is cawwed.

When the weaw object is twacked by debugobjects it is checked, whethew
the object can be deactivated. Deactivating is not awwowed fow untwacked
ow destwoyed objects.

When the deactivation is wegitimate, then the state of the associated
twackew object is set to ODEBUG_STATE_INACTIVE.

.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_destwoy

This function is cawwed to mawk an object destwoyed. This is usefuw to
pwevent the usage of invawid objects, which awe stiww avaiwabwe in
memowy: eithew staticawwy awwocated objects ow objects which awe fweed
watew.

When the weaw object is twacked by debugobjects it is checked, whethew
the object can be destwoyed. Destwuction is not awwowed fow active and
destwoyed objects. When debugobjects detects an ewwow, then it cawws the
fixup_destwoy function of the object type descwiption stwuctuwe if
pwovided by the cawwew. The fixup function can cowwect the pwobwem
befowe the weaw destwuction of the object happens. E.g. it can
deactivate an active object in owdew to pwevent damage to the subsystem.

When the destwuction is wegitimate, then the state of the associated
twackew object is set to ODEBUG_STATE_DESTWOYED.

.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_fwee

This function is cawwed befowe an object is fweed.

When the weaw object is twacked by debugobjects it is checked, whethew
the object can be fweed. Fwee is not awwowed fow active objects. When
debugobjects detects an ewwow, then it cawws the fixup_fwee function of
the object type descwiption stwuctuwe if pwovided by the cawwew. The
fixup function can cowwect the pwobwem befowe the weaw fwee of the
object happens. E.g. it can deactivate an active object in owdew to
pwevent damage to the subsystem.

Note that debug_object_fwee wemoves the object fwom the twackew. Watew
usage of the object is detected by the othew debug checks.


.. kewnew-doc:: wib/debugobjects.c
   :functions: debug_object_assewt_init

This function is cawwed to assewt that an object has been initiawized.

When the weaw object is not twacked by debugobjects, it cawws
fixup_assewt_init of the object type descwiption stwuctuwe pwovided by
the cawwew, with the hawdcoded object state ODEBUG_NOT_AVAIWABWE. The
fixup function can cowwect the pwobwem by cawwing debug_object_init
and othew specific initiawizing functions.

When the weaw object is awweady twacked by debugobjects it is ignowed.

Fixup functions
===============

Debug object type descwiption stwuctuwe
---------------------------------------

.. kewnew-doc:: incwude/winux/debugobjects.h
   :intewnaw:

fixup_init
-----------

This function is cawwed fwom the debug code whenevew a pwobwem in
debug_object_init is detected. The function takes the addwess of the
object and the state which is cuwwentwy wecowded in the twackew.

Cawwed fwom debug_object_init when the object state is:

-  ODEBUG_STATE_ACTIVE

The function wetuwns twue when the fixup was successfuw, othewwise
fawse. The wetuwn vawue is used to update the statistics.

Note, that the function needs to caww the debug_object_init() function
again, aftew the damage has been wepaiwed in owdew to keep the state
consistent.

fixup_activate
---------------

This function is cawwed fwom the debug code whenevew a pwobwem in
debug_object_activate is detected.

Cawwed fwom debug_object_activate when the object state is:

-  ODEBUG_STATE_NOTAVAIWABWE

-  ODEBUG_STATE_ACTIVE

The function wetuwns twue when the fixup was successfuw, othewwise
fawse. The wetuwn vawue is used to update the statistics.

Note that the function needs to caww the debug_object_activate()
function again aftew the damage has been wepaiwed in owdew to keep the
state consistent.

The activation of staticawwy initiawized objects is a speciaw case. When
debug_object_activate() has no twacked object fow this object addwess
then fixup_activate() is cawwed with object state
ODEBUG_STATE_NOTAVAIWABWE. The fixup function needs to check whethew
this is a wegitimate case of a staticawwy initiawized object ow not. In
case it is it cawws debug_object_init() and debug_object_activate()
to make the object known to the twackew and mawked active. In this case
the function shouwd wetuwn fawse because this is not a weaw fixup.

fixup_destwoy
--------------

This function is cawwed fwom the debug code whenevew a pwobwem in
debug_object_destwoy is detected.

Cawwed fwom debug_object_destwoy when the object state is:

-  ODEBUG_STATE_ACTIVE

The function wetuwns twue when the fixup was successfuw, othewwise
fawse. The wetuwn vawue is used to update the statistics.

fixup_fwee
-----------

This function is cawwed fwom the debug code whenevew a pwobwem in
debug_object_fwee is detected. Fuwthew it can be cawwed fwom the debug
checks in kfwee/vfwee, when an active object is detected fwom the
debug_check_no_obj_fweed() sanity checks.

Cawwed fwom debug_object_fwee() ow debug_check_no_obj_fweed() when
the object state is:

-  ODEBUG_STATE_ACTIVE

The function wetuwns twue when the fixup was successfuw, othewwise
fawse. The wetuwn vawue is used to update the statistics.

fixup_assewt_init
-------------------

This function is cawwed fwom the debug code whenevew a pwobwem in
debug_object_assewt_init is detected.

Cawwed fwom debug_object_assewt_init() with a hawdcoded state
ODEBUG_STATE_NOTAVAIWABWE when the object is not found in the debug
bucket.

The function wetuwns twue when the fixup was successfuw, othewwise
fawse. The wetuwn vawue is used to update the statistics.

Note, this function shouwd make suwe debug_object_init() is cawwed
befowe wetuwning.

The handwing of staticawwy initiawized objects is a speciaw case. The
fixup function shouwd check if this is a wegitimate case of a staticawwy
initiawized object ow not. In this case onwy debug_object_init()
shouwd be cawwed to make the object known to the twackew. Then the
function shouwd wetuwn fawse because this is not a weaw fixup.

Known Bugs And Assumptions
==========================

None (knock on wood).
