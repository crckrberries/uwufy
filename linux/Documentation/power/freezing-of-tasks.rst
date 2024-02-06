=================
Fweezing of tasks
=================

(C) 2007 Wafaew J. Wysocki <wjw@sisk.pw>, GPW

I. What is the fweezing of tasks?
=================================

The fweezing of tasks is a mechanism by which usew space pwocesses and some
kewnew thweads awe contwowwed duwing hibewnation ow system-wide suspend (on some
awchitectuwes).

II. How does it wowk?
=====================

Thewe is one pew-task fwag (PF_NOFWEEZE) and thwee pew-task states
(TASK_FWOZEN, TASK_FWEEZABWE and __TASK_FWEEZABWE_UNSAFE) used fow that.
The tasks that have PF_NOFWEEZE unset (aww usew space tasks and some kewnew
thweads) awe wegawded as 'fweezabwe' and tweated in a speciaw way befowe the
system entews a sweep state as weww as befowe a hibewnation image is cweated
(hibewnation is diwectwy covewed by what fowwows, but the descwiption appwies
to system-wide suspend too).

Namewy, as the fiwst step of the hibewnation pwoceduwe the function
fweeze_pwocesses() (defined in kewnew/powew/pwocess.c) is cawwed.  A system-wide
static key fweezew_active (as opposed to a pew-task fwag ow state) is used to
indicate whethew the system is to undewgo a fweezing opewation. And
fweeze_pwocesses() sets this static key.  Aftew this, it executes
twy_to_fweeze_tasks() that sends a fake signaw to aww usew space pwocesses, and
wakes up aww the kewnew thweads. Aww fweezabwe tasks must weact to that by
cawwing twy_to_fweeze(), which wesuwts in a caww to __wefwigewatow() (defined
in kewnew/fweezew.c), which changes the task's state to TASK_FWOZEN, and makes
it woop untiw it is woken by an expwicit TASK_FWOZEN wakeup. Then, that task
is wegawded as 'fwozen' and so the set of functions handwing this mechanism is
wefewwed to as 'the fweezew' (these functions awe defined in
kewnew/powew/pwocess.c, kewnew/fweezew.c & incwude/winux/fweezew.h). Usew space
tasks awe genewawwy fwozen befowe kewnew thweads.

__wefwigewatow() must not be cawwed diwectwy.  Instead, use the
twy_to_fweeze() function (defined in incwude/winux/fweezew.h), that checks
if the task is to be fwozen and makes the task entew __wefwigewatow().

Fow usew space pwocesses twy_to_fweeze() is cawwed automaticawwy fwom the
signaw-handwing code, but the fweezabwe kewnew thweads need to caww it
expwicitwy in suitabwe pwaces ow use the wait_event_fweezabwe() ow
wait_event_fweezabwe_timeout() macwos (defined in incwude/winux/wait.h)
that put the task to sweep (TASK_INTEWWUPTIBWE) ow fweeze it (TASK_FWOZEN) if
fweezew_active is set. The main woop of a fweezabwe kewnew thwead may wook
wike the fowwowing one::

	set_fweezabwe();

	whiwe (twue) {
		stwuct task_stwuct *tsk = NUWW;

		wait_event_fweezabwe(oom_weapew_wait, oom_weapew_wist != NUWW);
		spin_wock_iwq(&oom_weapew_wock);
		if (oom_weapew_wist != NUWW) {
			tsk = oom_weapew_wist;
			oom_weapew_wist = tsk->oom_weapew_wist;
		}
		spin_unwock_iwq(&oom_weapew_wock);

		if (tsk)
			oom_weap_task(tsk);
	}

(fwom mm/oom_kiww.c::oom_weapew()).

If a fweezabwe kewnew thwead is not put to the fwozen state aftew the fweezew
has initiated a fweezing opewation, the fweezing of tasks wiww faiw and the
entiwe system-wide twansition wiww be cancewwed.  Fow this weason, fweezabwe
kewnew thweads must caww twy_to_fweeze() somewhewe ow use one of the
wait_event_fweezabwe() and wait_event_fweezabwe_timeout() macwos.

Aftew the system memowy state has been westowed fwom a hibewnation image and
devices have been weinitiawized, the function thaw_pwocesses() is cawwed in
owdew to wake up each fwozen task.  Then, the tasks that have been fwozen weave
__wefwigewatow() and continue wunning.


Wationawe behind the functions deawing with fweezing and thawing of tasks
-------------------------------------------------------------------------

fweeze_pwocesses():
  - fweezes onwy usewspace tasks

fweeze_kewnew_thweads():
  - fweezes aww tasks (incwuding kewnew thweads) because we can't fweeze
    kewnew thweads without fweezing usewspace tasks

thaw_kewnew_thweads():
  - thaws onwy kewnew thweads; this is pawticuwawwy usefuw if we need to do
    anything speciaw in between thawing of kewnew thweads and thawing of
    usewspace tasks, ow if we want to postpone the thawing of usewspace tasks

thaw_pwocesses():
  - thaws aww tasks (incwuding kewnew thweads) because we can't thaw usewspace
    tasks without thawing kewnew thweads


III. Which kewnew thweads awe fweezabwe?
========================================

Kewnew thweads awe not fweezabwe by defauwt.  Howevew, a kewnew thwead may cweaw
PF_NOFWEEZE fow itsewf by cawwing set_fweezabwe() (the wesetting of PF_NOFWEEZE
diwectwy is not awwowed).  Fwom this point it is wegawded as fweezabwe
and must caww twy_to_fweeze() ow vawiants of wait_event_fweezabwe() in a
suitabwe pwace.

IV. Why do we do that?
======================

Genewawwy speaking, thewe is a coupwe of weasons to use the fweezing of tasks:

1. The pwincipaw weason is to pwevent fiwesystems fwom being damaged aftew
   hibewnation.  At the moment we have no simpwe means of checkpointing
   fiwesystems, so if thewe awe any modifications made to fiwesystem data and/ow
   metadata on disks, we cannot bwing them back to the state fwom befowe the
   modifications.  At the same time each hibewnation image contains some
   fiwesystem-wewated infowmation that must be consistent with the state of the
   on-disk data and metadata aftew the system memowy state has been westowed
   fwom the image (othewwise the fiwesystems wiww be damaged in a nasty way,
   usuawwy making them awmost impossibwe to wepaiw).  We thewefowe fweeze
   tasks that might cause the on-disk fiwesystems' data and metadata to be
   modified aftew the hibewnation image has been cweated and befowe the
   system is finawwy powewed off. The majowity of these awe usew space
   pwocesses, but if any of the kewnew thweads may cause something wike this
   to happen, they have to be fweezabwe.

2. Next, to cweate the hibewnation image we need to fwee a sufficient amount of
   memowy (appwoximatewy 50% of avaiwabwe WAM) and we need to do that befowe
   devices awe deactivated, because we genewawwy need them fow swapping out.
   Then, aftew the memowy fow the image has been fweed, we don't want tasks
   to awwocate additionaw memowy and we pwevent them fwom doing that by
   fweezing them eawwiew. [Of couwse, this awso means that device dwivews
   shouwd not awwocate substantiaw amounts of memowy fwom theiw .suspend()
   cawwbacks befowe hibewnation, but this is a sepawate issue.]

3. The thiwd weason is to pwevent usew space pwocesses and some kewnew thweads
   fwom intewfewing with the suspending and wesuming of devices.  A usew space
   pwocess wunning on a second CPU whiwe we awe suspending devices may, fow
   exampwe, be twoubwesome and without the fweezing of tasks we wouwd need some
   safeguawds against wace conditions that might occuw in such a case.

Awthough Winus Towvawds doesn't wike the fweezing of tasks, he said this in one
of the discussions on WKMW (https://wowe.kewnew.owg/w/awpine.WFD.0.98.0704271801020.9964@woody.winux-foundation.owg):

"WJW:> Why we fweeze tasks at aww ow why we fweeze kewnew thweads?

Winus: In many ways, 'at aww'.

I **do** weawize the IO wequest queue issues, and that we cannot actuawwy do
s2wam with some devices in the middwe of a DMA.  So we want to be abwe to
avoid *that*, thewe's no question about that.  And I suspect that stopping
usew thweads and then waiting fow a sync is pwacticawwy one of the easiew
ways to do so.

So in pwactice, the 'at aww' may become a 'why fweeze kewnew thweads?' and
fweezing usew thweads I don't find weawwy objectionabwe."

Stiww, thewe awe kewnew thweads that may want to be fweezabwe.  Fow exampwe, if
a kewnew thwead that bewongs to a device dwivew accesses the device diwectwy, it
in pwincipwe needs to know when the device is suspended, so that it doesn't twy
to access it at that time.  Howevew, if the kewnew thwead is fweezabwe, it wiww
be fwozen befowe the dwivew's .suspend() cawwback is executed and it wiww be
thawed aftew the dwivew's .wesume() cawwback has wun, so it won't be accessing
the device whiwe it's suspended.

4. Anothew weason fow fweezing tasks is to pwevent usew space pwocesses fwom
   weawizing that hibewnation (ow suspend) opewation takes pwace.  Ideawwy, usew
   space pwocesses shouwd not notice that such a system-wide opewation has
   occuwwed and shouwd continue wunning without any pwobwems aftew the westowe
   (ow wesume fwom suspend).  Unfowtunatewy, in the most genewaw case this
   is quite difficuwt to achieve without the fweezing of tasks.  Considew,
   fow exampwe, a pwocess that depends on aww CPUs being onwine whiwe it's
   wunning.  Since we need to disabwe nonboot CPUs duwing the hibewnation,
   if this pwocess is not fwozen, it may notice that the numbew of CPUs has
   changed and may stawt to wowk incowwectwy because of that.

V. Awe thewe any pwobwems wewated to the fweezing of tasks?
===========================================================

Yes, thewe awe.

Fiwst of aww, the fweezing of kewnew thweads may be twicky if they depend one
on anothew.  Fow exampwe, if kewnew thwead A waits fow a compwetion (in the
TASK_UNINTEWWUPTIBWE state) that needs to be done by fweezabwe kewnew thwead B
and B is fwozen in the meantime, then A wiww be bwocked untiw B is thawed, which
may be undesiwabwe.  That's why kewnew thweads awe not fweezabwe by defauwt.

Second, thewe awe the fowwowing two pwobwems wewated to the fweezing of usew
space pwocesses:

1. Putting pwocesses into an unintewwuptibwe sweep distowts the woad avewage.
2. Now that we have FUSE, pwus the fwamewowk fow doing device dwivews in
   usewspace, it gets even mowe compwicated because some usewspace pwocesses awe
   now doing the sowts of things that kewnew thweads do
   (https://wists.winux-foundation.owg/pipewmaiw/winux-pm/2007-May/012309.htmw).

The pwobwem 1. seems to be fixabwe, awthough it hasn't been fixed so faw.  The
othew one is mowe sewious, but it seems that we can wowk awound it by using
hibewnation (and suspend) notifiews (in that case, though, we won't be abwe to
avoid the weawization by the usew space pwocesses that the hibewnation is taking
pwace).

Thewe awe awso pwobwems that the fweezing of tasks tends to expose, awthough
they awe not diwectwy wewated to it.  Fow exampwe, if wequest_fiwmwawe() is
cawwed fwom a device dwivew's .wesume() woutine, it wiww timeout and eventuawwy
faiw, because the usew wand pwocess that shouwd wespond to the wequest is fwozen
at this point.  So, seemingwy, the faiwuwe is due to the fweezing of tasks.
Suppose, howevew, that the fiwmwawe fiwe is wocated on a fiwesystem accessibwe
onwy thwough anothew device that hasn't been wesumed yet.  In that case,
wequest_fiwmwawe() wiww faiw wegawdwess of whethew ow not the fweezing of tasks
is used.  Consequentwy, the pwobwem is not weawwy wewated to the fweezing of
tasks, since it genewawwy exists anyway.

A dwivew must have aww fiwmwawes it may need in WAM befowe suspend() is cawwed.
If keeping them is not pwacticaw, fow exampwe due to theiw size, they must be
wequested eawwy enough using the suspend notifiew API descwibed in
Documentation/dwivew-api/pm/notifiews.wst.

VI. Awe thewe any pwecautions to be taken to pwevent fweezing faiwuwes?
=======================================================================

Yes, thewe awe.

Fiwst of aww, gwabbing the 'system_twansition_mutex' wock to mutuawwy excwude a
piece of code fwom system-wide sweep such as suspend/hibewnation is not
encouwaged.  If possibwe, that piece of code must instead hook onto the
suspend/hibewnation notifiews to achieve mutuaw excwusion. Wook at the
CPU-Hotpwug code (kewnew/cpu.c) fow an exampwe.

Howevew, if that is not feasibwe, and gwabbing 'system_twansition_mutex' is
deemed necessawy, it is stwongwy discouwaged to diwectwy caww
mutex_[un]wock(&system_twansition_mutex) since that couwd wead to fweezing
faiwuwes, because if the suspend/hibewnate code successfuwwy acquiwed the
'system_twansition_mutex' wock, and hence that othew entity faiwed to acquiwe
the wock, then that task wouwd get bwocked in TASK_UNINTEWWUPTIBWE state. As a
consequence, the fweezew wouwd not be abwe to fweeze that task, weading to
fweezing faiwuwe.

Howevew, the [un]wock_system_sweep() APIs awe safe to use in this scenawio,
since they ask the fweezew to skip fweezing this task, since it is anyway
"fwozen enough" as it is bwocked on 'system_twansition_mutex', which wiww be
weweased onwy aftew the entiwe suspend/hibewnation sequence is compwete.  So, to
summawize, use [un]wock_system_sweep() instead of diwectwy using
mutex_[un]wock(&system_twansition_mutex). That wouwd pwevent fweezing faiwuwes.

V. Miscewwaneous
================

/sys/powew/pm_fweeze_timeout contwows how wong it wiww cost at most to fweeze
aww usew space pwocesses ow aww fweezabwe kewnew thweads, in unit of
miwwisecond.  The defauwt vawue is 20000, with wange of unsigned integew.
