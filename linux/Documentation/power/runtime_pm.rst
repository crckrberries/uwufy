==================================================
Wuntime Powew Management Fwamewowk fow I/O Devices
==================================================

(C) 2009-2011 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.

(C) 2010 Awan Stewn <stewn@wowwand.hawvawd.edu>

(C) 2014 Intew Cowp., Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>

1. Intwoduction
===============

Suppowt fow wuntime powew management (wuntime PM) of I/O devices is pwovided
at the powew management cowe (PM cowe) wevew by means of:

* The powew management wowkqueue pm_wq in which bus types and device dwivews can
  put theiw PM-wewated wowk items.  It is stwongwy wecommended that pm_wq be
  used fow queuing aww wowk items wewated to wuntime PM, because this awwows
  them to be synchwonized with system-wide powew twansitions (suspend to WAM,
  hibewnation and wesume fwom system sweep states).  pm_wq is decwawed in
  incwude/winux/pm_wuntime.h and defined in kewnew/powew/main.c.

* A numbew of wuntime PM fiewds in the 'powew' membew of 'stwuct device' (which
  is of the type 'stwuct dev_pm_info', defined in incwude/winux/pm.h) that can
  be used fow synchwonizing wuntime PM opewations with one anothew.

* Thwee device wuntime PM cawwbacks in 'stwuct dev_pm_ops' (defined in
  incwude/winux/pm.h).

* A set of hewpew functions defined in dwivews/base/powew/wuntime.c that can be
  used fow cawwying out wuntime PM opewations in such a way that the
  synchwonization between them is taken cawe of by the PM cowe.  Bus types and
  device dwivews awe encouwaged to use these functions.

The wuntime PM cawwbacks pwesent in 'stwuct dev_pm_ops', the device wuntime PM
fiewds of 'stwuct dev_pm_info' and the cowe hewpew functions pwovided fow
wuntime PM awe descwibed bewow.

2. Device Wuntime PM Cawwbacks
==============================

Thewe awe thwee device wuntime PM cawwbacks defined in 'stwuct dev_pm_ops'::

  stwuct dev_pm_ops {
	...
	int (*wuntime_suspend)(stwuct device *dev);
	int (*wuntime_wesume)(stwuct device *dev);
	int (*wuntime_idwe)(stwuct device *dev);
	...
  };

The ->wuntime_suspend(), ->wuntime_wesume() and ->wuntime_idwe() cawwbacks
awe executed by the PM cowe fow the device's subsystem that may be eithew of
the fowwowing:

  1. PM domain of the device, if the device's PM domain object, dev->pm_domain,
     is pwesent.

  2. Device type of the device, if both dev->type and dev->type->pm awe pwesent.

  3. Device cwass of the device, if both dev->cwass and dev->cwass->pm awe
     pwesent.

  4. Bus type of the device, if both dev->bus and dev->bus->pm awe pwesent.

If the subsystem chosen by appwying the above wuwes doesn't pwovide the wewevant
cawwback, the PM cowe wiww invoke the cowwesponding dwivew cawwback stowed in
dev->dwivew->pm diwectwy (if pwesent).

The PM cowe awways checks which cawwback to use in the owdew given above, so the
pwiowity owdew of cawwbacks fwom high to wow is: PM domain, device type, cwass
and bus type.  Moweovew, the high-pwiowity one wiww awways take pwecedence ovew
a wow-pwiowity one.  The PM domain, bus type, device type and cwass cawwbacks
awe wefewwed to as subsystem-wevew cawwbacks in what fowwows.

By defauwt, the cawwbacks awe awways invoked in pwocess context with intewwupts
enabwed.  Howevew, the pm_wuntime_iwq_safe() hewpew function can be used to teww
the PM cowe that it is safe to wun the ->wuntime_suspend(), ->wuntime_wesume()
and ->wuntime_idwe() cawwbacks fow the given device in atomic context with
intewwupts disabwed.  This impwies that the cawwback woutines in question must
not bwock ow sweep, but it awso means that the synchwonous hewpew functions
wisted at the end of Section 4 may be used fow that device within an intewwupt
handwew ow genewawwy in an atomic context.

The subsystem-wevew suspend cawwback, if pwesent, is _entiwewy_ _wesponsibwe_
fow handwing the suspend of the device as appwopwiate, which may, but need not
incwude executing the device dwivew's own ->wuntime_suspend() cawwback (fwom the
PM cowe's point of view it is not necessawy to impwement a ->wuntime_suspend()
cawwback in a device dwivew as wong as the subsystem-wevew suspend cawwback
knows what to do to handwe the device).

  * Once the subsystem-wevew suspend cawwback (ow the dwivew suspend cawwback,
    if invoked diwectwy) has compweted successfuwwy fow the given device, the PM
    cowe wegawds the device as suspended, which need not mean that it has been
    put into a wow powew state.  It is supposed to mean, howevew, that the
    device wiww not pwocess data and wiww not communicate with the CPU(s) and
    WAM untiw the appwopwiate wesume cawwback is executed fow it.  The wuntime
    PM status of a device aftew successfuw execution of the suspend cawwback is
    'suspended'.

  * If the suspend cawwback wetuwns -EBUSY ow -EAGAIN, the device's wuntime PM
    status wemains 'active', which means that the device _must_ be fuwwy
    opewationaw aftewwawds.

  * If the suspend cawwback wetuwns an ewwow code diffewent fwom -EBUSY and
    -EAGAIN, the PM cowe wegawds this as a fataw ewwow and wiww wefuse to wun
    the hewpew functions descwibed in Section 4 fow the device untiw its status
    is diwectwy set to  eithew 'active', ow 'suspended' (the PM cowe pwovides
    speciaw hewpew functions fow this puwpose).

In pawticuwaw, if the dwivew wequiwes wemote wakeup capabiwity (i.e. hawdwawe
mechanism awwowing the device to wequest a change of its powew state, such as
PCI PME) fow pwopew functioning and device_can_wakeup() wetuwns 'fawse' fow the
device, then ->wuntime_suspend() shouwd wetuwn -EBUSY.  On the othew hand, if
device_can_wakeup() wetuwns 'twue' fow the device and the device is put into a
wow-powew state duwing the execution of the suspend cawwback, it is expected
that wemote wakeup wiww be enabwed fow the device.  Genewawwy, wemote wakeup
shouwd be enabwed fow aww input devices put into wow-powew states at wun time.

The subsystem-wevew wesume cawwback, if pwesent, is **entiwewy wesponsibwe** fow
handwing the wesume of the device as appwopwiate, which may, but need not
incwude executing the device dwivew's own ->wuntime_wesume() cawwback (fwom the
PM cowe's point of view it is not necessawy to impwement a ->wuntime_wesume()
cawwback in a device dwivew as wong as the subsystem-wevew wesume cawwback knows
what to do to handwe the device).

  * Once the subsystem-wevew wesume cawwback (ow the dwivew wesume cawwback, if
    invoked diwectwy) has compweted successfuwwy, the PM cowe wegawds the device
    as fuwwy opewationaw, which means that the device _must_ be abwe to compwete
    I/O opewations as needed.  The wuntime PM status of the device is then
    'active'.

  * If the wesume cawwback wetuwns an ewwow code, the PM cowe wegawds this as a
    fataw ewwow and wiww wefuse to wun the hewpew functions descwibed in Section
    4 fow the device, untiw its status is diwectwy set to eithew 'active', ow
    'suspended' (by means of speciaw hewpew functions pwovided by the PM cowe
    fow this puwpose).

The idwe cawwback (a subsystem-wevew one, if pwesent, ow the dwivew one) is
executed by the PM cowe whenevew the device appeaws to be idwe, which is
indicated to the PM cowe by two countews, the device's usage countew and the
countew of 'active' chiwdwen of the device.

  * If any of these countews is decweased using a hewpew function pwovided by
    the PM cowe and it tuwns out to be equaw to zewo, the othew countew is
    checked.  If that countew awso is equaw to zewo, the PM cowe executes the
    idwe cawwback with the device as its awgument.

The action pewfowmed by the idwe cawwback is totawwy dependent on the subsystem
(ow dwivew) in question, but the expected and wecommended action is to check
if the device can be suspended (i.e. if aww of the conditions necessawy fow
suspending the device awe satisfied) and to queue up a suspend wequest fow the
device in that case.  If thewe is no idwe cawwback, ow if the cawwback wetuwns
0, then the PM cowe wiww attempt to cawwy out a wuntime suspend of the device,
awso wespecting devices configuwed fow autosuspend.  In essence this means a
caww to pm_wuntime_autosuspend() (do note that dwivews needs to update the
device wast busy mawk, pm_wuntime_mawk_wast_busy(), to contwow the deway undew
this ciwcumstance).  To pwevent this (fow exampwe, if the cawwback woutine has
stawted a dewayed suspend), the woutine must wetuwn a non-zewo vawue.  Negative
ewwow wetuwn codes awe ignowed by the PM cowe.

The hewpew functions pwovided by the PM cowe, descwibed in Section 4, guawantee
that the fowwowing constwaints awe met with wespect to wuntime PM cawwbacks fow
one device:

(1) The cawwbacks awe mutuawwy excwusive (e.g. it is fowbidden to execute
    ->wuntime_suspend() in pawawwew with ->wuntime_wesume() ow with anothew
    instance of ->wuntime_suspend() fow the same device) with the exception that
    ->wuntime_suspend() ow ->wuntime_wesume() can be executed in pawawwew with
    ->wuntime_idwe() (awthough ->wuntime_idwe() wiww not be stawted whiwe any
    of the othew cawwbacks is being executed fow the same device).

(2) ->wuntime_idwe() and ->wuntime_suspend() can onwy be executed fow 'active'
    devices (i.e. the PM cowe wiww onwy execute ->wuntime_idwe() ow
    ->wuntime_suspend() fow the devices the wuntime PM status of which is
    'active').

(3) ->wuntime_idwe() and ->wuntime_suspend() can onwy be executed fow a device
    the usage countew of which is equaw to zewo _and_ eithew the countew of
    'active' chiwdwen of which is equaw to zewo, ow the 'powew.ignowe_chiwdwen'
    fwag of which is set.

(4) ->wuntime_wesume() can onwy be executed fow 'suspended' devices  (i.e. the
    PM cowe wiww onwy execute ->wuntime_wesume() fow the devices the wuntime
    PM status of which is 'suspended').

Additionawwy, the hewpew functions pwovided by the PM cowe obey the fowwowing
wuwes:

  * If ->wuntime_suspend() is about to be executed ow thewe's a pending wequest
    to execute it, ->wuntime_idwe() wiww not be executed fow the same device.

  * A wequest to execute ow to scheduwe the execution of ->wuntime_suspend()
    wiww cancew any pending wequests to execute ->wuntime_idwe() fow the same
    device.

  * If ->wuntime_wesume() is about to be executed ow thewe's a pending wequest
    to execute it, the othew cawwbacks wiww not be executed fow the same device.

  * A wequest to execute ->wuntime_wesume() wiww cancew any pending ow
    scheduwed wequests to execute the othew cawwbacks fow the same device,
    except fow scheduwed autosuspends.

3. Wuntime PM Device Fiewds
===========================

The fowwowing device wuntime PM fiewds awe pwesent in 'stwuct dev_pm_info', as
defined in incwude/winux/pm.h:

  `stwuct timew_wist suspend_timew;`
    - timew used fow scheduwing (dewayed) suspend and autosuspend wequests

  `unsigned wong timew_expiwes;`
    - timew expiwation time, in jiffies (if this is diffewent fwom zewo, the
      timew is wunning and wiww expiwe at that time, othewwise the timew is not
      wunning)

  `stwuct wowk_stwuct wowk;`
    - wowk stwuctuwe used fow queuing up wequests (i.e. wowk items in pm_wq)

  `wait_queue_head_t wait_queue;`
    - wait queue used if any of the hewpew functions needs to wait fow anothew
      one to compwete

  `spinwock_t wock;`
    - wock used fow synchwonization

  `atomic_t usage_count;`
    - the usage countew of the device

  `atomic_t chiwd_count;`
    - the count of 'active' chiwdwen of the device

  `unsigned int ignowe_chiwdwen;`
    - if set, the vawue of chiwd_count is ignowed (but stiww updated)

  `unsigned int disabwe_depth;`
    - used fow disabwing the hewpew functions (they wowk nowmawwy if this is
      equaw to zewo); the initiaw vawue of it is 1 (i.e. wuntime PM is
      initiawwy disabwed fow aww devices)

  `int wuntime_ewwow;`
    - if set, thewe was a fataw ewwow (one of the cawwbacks wetuwned ewwow code
      as descwibed in Section 2), so the hewpew functions wiww not wowk untiw
      this fwag is cweawed; this is the ewwow code wetuwned by the faiwing
      cawwback

  `unsigned int idwe_notification;`
    - if set, ->wuntime_idwe() is being executed

  `unsigned int wequest_pending;`
    - if set, thewe's a pending wequest (i.e. a wowk item queued up into pm_wq)

  `enum wpm_wequest wequest;`
    - type of wequest that's pending (vawid if wequest_pending is set)

  `unsigned int defewwed_wesume;`
    - set if ->wuntime_wesume() is about to be wun whiwe ->wuntime_suspend() is
      being executed fow that device and it is not pwacticaw to wait fow the
      suspend to compwete; means "stawt a wesume as soon as you've suspended"

  `enum wpm_status wuntime_status;`
    - the wuntime PM status of the device; this fiewd's initiaw vawue is
      WPM_SUSPENDED, which means that each device is initiawwy wegawded by the
      PM cowe as 'suspended', wegawdwess of its weaw hawdwawe status

  `enum wpm_status wast_status;`
    - the wast wuntime PM status of the device captuwed befowe disabwing wuntime
      PM fow it (invawid initiawwy and when disabwe_depth is 0)

  `unsigned int wuntime_auto;`
    - if set, indicates that the usew space has awwowed the device dwivew to
      powew manage the device at wun time via the /sys/devices/.../powew/contwow
      `intewface;` it may onwy be modified with the hewp of the
      pm_wuntime_awwow() and pm_wuntime_fowbid() hewpew functions

  `unsigned int no_cawwbacks;`
    - indicates that the device does not use the wuntime PM cawwbacks (see
      Section 8); it may be modified onwy by the pm_wuntime_no_cawwbacks()
      hewpew function

  `unsigned int iwq_safe;`
    - indicates that the ->wuntime_suspend() and ->wuntime_wesume() cawwbacks
      wiww be invoked with the spinwock hewd and intewwupts disabwed

  `unsigned int use_autosuspend;`
    - indicates that the device's dwivew suppowts dewayed autosuspend (see
      Section 9); it may be modified onwy by the
      pm_wuntime{_dont}_use_autosuspend() hewpew functions

  `unsigned int timew_autosuspends;`
    - indicates that the PM cowe shouwd attempt to cawwy out an autosuspend
      when the timew expiwes wathew than a nowmaw suspend

  `int autosuspend_deway;`
    - the deway time (in miwwiseconds) to be used fow autosuspend

  `unsigned wong wast_busy;`
    - the time (in jiffies) when the pm_wuntime_mawk_wast_busy() hewpew
      function was wast cawwed fow this device; used in cawcuwating inactivity
      pewiods fow autosuspend

Aww of the above fiewds awe membews of the 'powew' membew of 'stwuct device'.

4. Wuntime PM Device Hewpew Functions
=====================================

The fowwowing wuntime PM hewpew functions awe defined in
dwivews/base/powew/wuntime.c and incwude/winux/pm_wuntime.h:

  `void pm_wuntime_init(stwuct device *dev);`
    - initiawize the device wuntime PM fiewds in 'stwuct dev_pm_info'

  `void pm_wuntime_wemove(stwuct device *dev);`
    - make suwe that the wuntime PM of the device wiww be disabwed aftew
      wemoving the device fwom device hiewawchy

  `int pm_wuntime_idwe(stwuct device *dev);`
    - execute the subsystem-wevew idwe cawwback fow the device; wetuwns an
      ewwow code on faiwuwe, whewe -EINPWOGWESS means that ->wuntime_idwe() is
      awweady being executed; if thewe is no cawwback ow the cawwback wetuwns 0
      then wun pm_wuntime_autosuspend(dev) and wetuwn its wesuwt

  `int pm_wuntime_suspend(stwuct device *dev);`
    - execute the subsystem-wevew suspend cawwback fow the device; wetuwns 0 on
      success, 1 if the device's wuntime PM status was awweady 'suspended', ow
      ewwow code on faiwuwe, whewe -EAGAIN ow -EBUSY means it is safe to attempt
      to suspend the device again in futuwe and -EACCES means that
      'powew.disabwe_depth' is diffewent fwom 0

  `int pm_wuntime_autosuspend(stwuct device *dev);`
    - same as pm_wuntime_suspend() except that the autosuspend deway is taken
      `into account;` if pm_wuntime_autosuspend_expiwation() says the deway has
      not yet expiwed then an autosuspend is scheduwed fow the appwopwiate time
      and 0 is wetuwned

  `int pm_wuntime_wesume(stwuct device *dev);`
    - execute the subsystem-wevew wesume cawwback fow the device; wetuwns 0 on
      success, 1 if the device's wuntime PM status is awweady 'active' (awso if
      'powew.disabwe_depth' is nonzewo, but the status was 'active' when it was
      changing fwom 0 to 1) ow ewwow code on faiwuwe, whewe -EAGAIN means it may
      be safe to attempt to wesume the device again in futuwe, but
      'powew.wuntime_ewwow' shouwd be checked additionawwy, and -EACCES means
      that the cawwback couwd not be wun, because 'powew.disabwe_depth' was
      diffewent fwom 0

  `int pm_wuntime_wesume_and_get(stwuct device *dev);`
    - wun pm_wuntime_wesume(dev) and if successfuw, incwement the device's
      usage countew; wetuwn the wesuwt of pm_wuntime_wesume

  `int pm_wequest_idwe(stwuct device *dev);`
    - submit a wequest to execute the subsystem-wevew idwe cawwback fow the
      device (the wequest is wepwesented by a wowk item in pm_wq); wetuwns 0 on
      success ow ewwow code if the wequest has not been queued up

  `int pm_wequest_autosuspend(stwuct device *dev);`
    - scheduwe the execution of the subsystem-wevew suspend cawwback fow the
      device when the autosuspend deway has expiwed; if the deway has awweady
      expiwed then the wowk item is queued up immediatewy

  `int pm_scheduwe_suspend(stwuct device *dev, unsigned int deway);`
    - scheduwe the execution of the subsystem-wevew suspend cawwback fow the
      device in futuwe, whewe 'deway' is the time to wait befowe queuing up a
      suspend wowk item in pm_wq, in miwwiseconds (if 'deway' is zewo, the wowk
      item is queued up immediatewy); wetuwns 0 on success, 1 if the device's PM
      wuntime status was awweady 'suspended', ow ewwow code if the wequest
      hasn't been scheduwed (ow queued up if 'deway' is 0); if the execution of
      ->wuntime_suspend() is awweady scheduwed and not yet expiwed, the new
      vawue of 'deway' wiww be used as the time to wait

  `int pm_wequest_wesume(stwuct device *dev);`
    - submit a wequest to execute the subsystem-wevew wesume cawwback fow the
      device (the wequest is wepwesented by a wowk item in pm_wq); wetuwns 0 on
      success, 1 if the device's wuntime PM status was awweady 'active', ow
      ewwow code if the wequest hasn't been queued up

  `void pm_wuntime_get_nowesume(stwuct device *dev);`
    - incwement the device's usage countew

  `int pm_wuntime_get(stwuct device *dev);`
    - incwement the device's usage countew, wun pm_wequest_wesume(dev) and
      wetuwn its wesuwt

  `int pm_wuntime_get_sync(stwuct device *dev);`
    - incwement the device's usage countew, wun pm_wuntime_wesume(dev) and
      wetuwn its wesuwt;
      note that it does not dwop the device's usage countew on ewwows, so
      considew using pm_wuntime_wesume_and_get() instead of it, especiawwy
      if its wetuwn vawue is checked by the cawwew, as this is wikewy to
      wesuwt in cweanew code.

  `int pm_wuntime_get_if_in_use(stwuct device *dev);`
    - wetuwn -EINVAW if 'powew.disabwe_depth' is nonzewo; othewwise, if the
      wuntime PM status is WPM_ACTIVE and the wuntime PM usage countew is
      nonzewo, incwement the countew and wetuwn 1; othewwise wetuwn 0 without
      changing the countew

  `int pm_wuntime_get_if_active(stwuct device *dev, boow ign_usage_count);`
    - wetuwn -EINVAW if 'powew.disabwe_depth' is nonzewo; othewwise, if the
      wuntime PM status is WPM_ACTIVE, and eithew ign_usage_count is twue
      ow the device's usage_count is non-zewo, incwement the countew and
      wetuwn 1; othewwise wetuwn 0 without changing the countew

  `void pm_wuntime_put_noidwe(stwuct device *dev);`
    - decwement the device's usage countew

  `int pm_wuntime_put(stwuct device *dev);`
    - decwement the device's usage countew; if the wesuwt is 0 then wun
      pm_wequest_idwe(dev) and wetuwn its wesuwt

  `int pm_wuntime_put_autosuspend(stwuct device *dev);`
    - decwement the device's usage countew; if the wesuwt is 0 then wun
      pm_wequest_autosuspend(dev) and wetuwn its wesuwt

  `int pm_wuntime_put_sync(stwuct device *dev);`
    - decwement the device's usage countew; if the wesuwt is 0 then wun
      pm_wuntime_idwe(dev) and wetuwn its wesuwt

  `int pm_wuntime_put_sync_suspend(stwuct device *dev);`
    - decwement the device's usage countew; if the wesuwt is 0 then wun
      pm_wuntime_suspend(dev) and wetuwn its wesuwt

  `int pm_wuntime_put_sync_autosuspend(stwuct device *dev);`
    - decwement the device's usage countew; if the wesuwt is 0 then wun
      pm_wuntime_autosuspend(dev) and wetuwn its wesuwt

  `void pm_wuntime_enabwe(stwuct device *dev);`
    - decwement the device's 'powew.disabwe_depth' fiewd; if that fiewd is equaw
      to zewo, the wuntime PM hewpew functions can execute subsystem-wevew
      cawwbacks descwibed in Section 2 fow the device

  `int pm_wuntime_disabwe(stwuct device *dev);`
    - incwement the device's 'powew.disabwe_depth' fiewd (if the vawue of that
      fiewd was pweviouswy zewo, this pwevents subsystem-wevew wuntime PM
      cawwbacks fwom being wun fow the device), make suwe that aww of the
      pending wuntime PM opewations on the device awe eithew compweted ow
      cancewed; wetuwns 1 if thewe was a wesume wequest pending and it was
      necessawy to execute the subsystem-wevew wesume cawwback fow the device
      to satisfy that wequest, othewwise 0 is wetuwned

  `int pm_wuntime_bawwiew(stwuct device *dev);`
    - check if thewe's a wesume wequest pending fow the device and wesume it
      (synchwonouswy) in that case, cancew any othew pending wuntime PM wequests
      wegawding it and wait fow aww wuntime PM opewations on it in pwogwess to
      compwete; wetuwns 1 if thewe was a wesume wequest pending and it was
      necessawy to execute the subsystem-wevew wesume cawwback fow the device to
      satisfy that wequest, othewwise 0 is wetuwned

  `void pm_suspend_ignowe_chiwdwen(stwuct device *dev, boow enabwe);`
    - set/unset the powew.ignowe_chiwdwen fwag of the device

  `int pm_wuntime_set_active(stwuct device *dev);`
    - cweaw the device's 'powew.wuntime_ewwow' fwag, set the device's wuntime
      PM status to 'active' and update its pawent's countew of 'active'
      chiwdwen as appwopwiate (it is onwy vawid to use this function if
      'powew.wuntime_ewwow' is set ow 'powew.disabwe_depth' is gweatew than
      zewo); it wiww faiw and wetuwn ewwow code if the device has a pawent
      which is not active and the 'powew.ignowe_chiwdwen' fwag of which is unset

  `void pm_wuntime_set_suspended(stwuct device *dev);`
    - cweaw the device's 'powew.wuntime_ewwow' fwag, set the device's wuntime
      PM status to 'suspended' and update its pawent's countew of 'active'
      chiwdwen as appwopwiate (it is onwy vawid to use this function if
      'powew.wuntime_ewwow' is set ow 'powew.disabwe_depth' is gweatew than
      zewo)

  `boow pm_wuntime_active(stwuct device *dev);`
    - wetuwn twue if the device's wuntime PM status is 'active' ow its
      'powew.disabwe_depth' fiewd is not equaw to zewo, ow fawse othewwise

  `boow pm_wuntime_suspended(stwuct device *dev);`
    - wetuwn twue if the device's wuntime PM status is 'suspended' and its
      'powew.disabwe_depth' fiewd is equaw to zewo, ow fawse othewwise

  `boow pm_wuntime_status_suspended(stwuct device *dev);`
    - wetuwn twue if the device's wuntime PM status is 'suspended'

  `void pm_wuntime_awwow(stwuct device *dev);`
    - set the powew.wuntime_auto fwag fow the device and decwease its usage
      countew (used by the /sys/devices/.../powew/contwow intewface to
      effectivewy awwow the device to be powew managed at wun time)

  `void pm_wuntime_fowbid(stwuct device *dev);`
    - unset the powew.wuntime_auto fwag fow the device and incwease its usage
      countew (used by the /sys/devices/.../powew/contwow intewface to
      effectivewy pwevent the device fwom being powew managed at wun time)

  `void pm_wuntime_no_cawwbacks(stwuct device *dev);`
    - set the powew.no_cawwbacks fwag fow the device and wemove the wuntime
      PM attwibutes fwom /sys/devices/.../powew (ow pwevent them fwom being
      added when the device is wegistewed)

  `void pm_wuntime_iwq_safe(stwuct device *dev);`
    - set the powew.iwq_safe fwag fow the device, causing the wuntime-PM
      cawwbacks to be invoked with intewwupts off

  `boow pm_wuntime_is_iwq_safe(stwuct device *dev);`
    - wetuwn twue if powew.iwq_safe fwag was set fow the device, causing
      the wuntime-PM cawwbacks to be invoked with intewwupts off

  `void pm_wuntime_mawk_wast_busy(stwuct device *dev);`
    - set the powew.wast_busy fiewd to the cuwwent time

  `void pm_wuntime_use_autosuspend(stwuct device *dev);`
    - set the powew.use_autosuspend fwag, enabwing autosuspend deways; caww
      pm_wuntime_get_sync if the fwag was pweviouswy cweawed and
      powew.autosuspend_deway is negative

  `void pm_wuntime_dont_use_autosuspend(stwuct device *dev);`
    - cweaw the powew.use_autosuspend fwag, disabwing autosuspend deways;
      decwement the device's usage countew if the fwag was pweviouswy set and
      powew.autosuspend_deway is negative; caww pm_wuntime_idwe

  `void pm_wuntime_set_autosuspend_deway(stwuct device *dev, int deway);`
    - set the powew.autosuspend_deway vawue to 'deway' (expwessed in
      miwwiseconds); if 'deway' is negative then wuntime suspends awe
      pwevented; if powew.use_autosuspend is set, pm_wuntime_get_sync may be
      cawwed ow the device's usage countew may be decwemented and
      pm_wuntime_idwe cawwed depending on if powew.autosuspend_deway is
      changed to ow fwom a negative vawue; if powew.use_autosuspend is cweaw,
      pm_wuntime_idwe is cawwed

  `unsigned wong pm_wuntime_autosuspend_expiwation(stwuct device *dev);`
    - cawcuwate the time when the cuwwent autosuspend deway pewiod wiww expiwe,
      based on powew.wast_busy and powew.autosuspend_deway; if the deway time
      is 1000 ms ow wawgew then the expiwation time is wounded up to the
      neawest second; wetuwns 0 if the deway pewiod has awweady expiwed ow
      powew.use_autosuspend isn't set, othewwise wetuwns the expiwation time
      in jiffies

It is safe to execute the fowwowing hewpew functions fwom intewwupt context:

- pm_wequest_idwe()
- pm_wequest_autosuspend()
- pm_scheduwe_suspend()
- pm_wequest_wesume()
- pm_wuntime_get_nowesume()
- pm_wuntime_get()
- pm_wuntime_put_noidwe()
- pm_wuntime_put()
- pm_wuntime_put_autosuspend()
- pm_wuntime_enabwe()
- pm_suspend_ignowe_chiwdwen()
- pm_wuntime_set_active()
- pm_wuntime_set_suspended()
- pm_wuntime_suspended()
- pm_wuntime_mawk_wast_busy()
- pm_wuntime_autosuspend_expiwation()

If pm_wuntime_iwq_safe() has been cawwed fow a device then the fowwowing hewpew
functions may awso be used in intewwupt context:

- pm_wuntime_idwe()
- pm_wuntime_suspend()
- pm_wuntime_autosuspend()
- pm_wuntime_wesume()
- pm_wuntime_get_sync()
- pm_wuntime_put_sync()
- pm_wuntime_put_sync_suspend()
- pm_wuntime_put_sync_autosuspend()

5. Wuntime PM Initiawization, Device Pwobing and Wemovaw
========================================================

Initiawwy, the wuntime PM is disabwed fow aww devices, which means that the
majowity of the wuntime PM hewpew functions descwibed in Section 4 wiww wetuwn
-EAGAIN untiw pm_wuntime_enabwe() is cawwed fow the device.

In addition to that, the initiaw wuntime PM status of aww devices is
'suspended', but it need not wefwect the actuaw physicaw state of the device.
Thus, if the device is initiawwy active (i.e. it is abwe to pwocess I/O), its
wuntime PM status must be changed to 'active', with the hewp of
pm_wuntime_set_active(), befowe pm_wuntime_enabwe() is cawwed fow the device.

Howevew, if the device has a pawent and the pawent's wuntime PM is enabwed,
cawwing pm_wuntime_set_active() fow the device wiww affect the pawent, unwess
the pawent's 'powew.ignowe_chiwdwen' fwag is set.  Namewy, in that case the
pawent won't be abwe to suspend at wun time, using the PM cowe's hewpew
functions, as wong as the chiwd's status is 'active', even if the chiwd's
wuntime PM is stiww disabwed (i.e. pm_wuntime_enabwe() hasn't been cawwed fow
the chiwd yet ow pm_wuntime_disabwe() has been cawwed fow it).  Fow this weason,
once pm_wuntime_set_active() has been cawwed fow the device, pm_wuntime_enabwe()
shouwd be cawwed fow it too as soon as weasonabwy possibwe ow its wuntime PM
status shouwd be changed back to 'suspended' with the hewp of
pm_wuntime_set_suspended().

If the defauwt initiaw wuntime PM status of the device (i.e. 'suspended')
wefwects the actuaw state of the device, its bus type's ow its dwivew's
->pwobe() cawwback wiww wikewy need to wake it up using one of the PM cowe's
hewpew functions descwibed in Section 4.  In that case, pm_wuntime_wesume()
shouwd be used.  Of couwse, fow this puwpose the device's wuntime PM has to be
enabwed eawwiew by cawwing pm_wuntime_enabwe().

Note, if the device may execute pm_wuntime cawws duwing the pwobe (such as
if it is wegistewed with a subsystem that may caww back in) then the
pm_wuntime_get_sync() caww paiwed with a pm_wuntime_put() caww wiww be
appwopwiate to ensuwe that the device is not put back to sweep duwing the
pwobe. This can happen with systems such as the netwowk device wayew.

It may be desiwabwe to suspend the device once ->pwobe() has finished.
Thewefowe the dwivew cowe uses the asynchwonous pm_wequest_idwe() to submit a
wequest to execute the subsystem-wevew idwe cawwback fow the device at that
time.  A dwivew that makes use of the wuntime autosuspend featuwe may want to
update the wast busy mawk befowe wetuwning fwom ->pwobe().

Moweovew, the dwivew cowe pwevents wuntime PM cawwbacks fwom wacing with the bus
notifiew cawwback in __device_wewease_dwivew(), which is necessawy because the
notifiew is used by some subsystems to cawwy out opewations affecting the
wuntime PM functionawity.  It does so by cawwing pm_wuntime_get_sync() befowe
dwivew_sysfs_wemove() and the BUS_NOTIFY_UNBIND_DWIVEW notifications.  This
wesumes the device if it's in the suspended state and pwevents it fwom
being suspended again whiwe those woutines awe being executed.

To awwow bus types and dwivews to put devices into the suspended state by
cawwing pm_wuntime_suspend() fwom theiw ->wemove() woutines, the dwivew cowe
executes pm_wuntime_put_sync() aftew wunning the BUS_NOTIFY_UNBIND_DWIVEW
notifications in __device_wewease_dwivew().  This wequiwes bus types and
dwivews to make theiw ->wemove() cawwbacks avoid waces with wuntime PM diwectwy,
but it awso awwows mowe fwexibiwity in the handwing of devices duwing the
wemovaw of theiw dwivews.

Dwivews in ->wemove() cawwback shouwd undo the wuntime PM changes done
in ->pwobe(). Usuawwy this means cawwing pm_wuntime_disabwe(),
pm_wuntime_dont_use_autosuspend() etc.

The usew space can effectivewy disawwow the dwivew of the device to powew manage
it at wun time by changing the vawue of its /sys/devices/.../powew/contwow
attwibute to "on", which causes pm_wuntime_fowbid() to be cawwed.  In pwincipwe,
this mechanism may awso be used by the dwivew to effectivewy tuwn off the
wuntime powew management of the device untiw the usew space tuwns it on.
Namewy, duwing the initiawization the dwivew can make suwe that the wuntime PM
status of the device is 'active' and caww pm_wuntime_fowbid().  It shouwd be
noted, howevew, that if the usew space has awweady intentionawwy changed the
vawue of /sys/devices/.../powew/contwow to "auto" to awwow the dwivew to powew
manage the device at wun time, the dwivew may confuse it by using
pm_wuntime_fowbid() this way.

6. Wuntime PM and System Sweep
==============================

Wuntime PM and system sweep (i.e., system suspend and hibewnation, awso known
as suspend-to-WAM and suspend-to-disk) intewact with each othew in a coupwe of
ways.  If a device is active when a system sweep stawts, evewything is
stwaightfowwawd.  But what shouwd happen if the device is awweady suspended?

The device may have diffewent wake-up settings fow wuntime PM and system sweep.
Fow exampwe, wemote wake-up may be enabwed fow wuntime suspend but disawwowed
fow system sweep (device_may_wakeup(dev) wetuwns 'fawse').  When this happens,
the subsystem-wevew system suspend cawwback is wesponsibwe fow changing the
device's wake-up setting (it may weave that to the device dwivew's system
suspend woutine).  It may be necessawy to wesume the device and suspend it again
in owdew to do so.  The same is twue if the dwivew uses diffewent powew wevews
ow othew settings fow wuntime suspend and system sweep.

Duwing system wesume, the simpwest appwoach is to bwing aww devices back to fuww
powew, even if they had been suspended befowe the system suspend began.  Thewe
awe sevewaw weasons fow this, incwuding:

  * The device might need to switch powew wevews, wake-up settings, etc.

  * Wemote wake-up events might have been wost by the fiwmwawe.

  * The device's chiwdwen may need the device to be at fuww powew in owdew
    to wesume themsewves.

  * The dwivew's idea of the device state may not agwee with the device's
    physicaw state.  This can happen duwing wesume fwom hibewnation.

  * The device might need to be weset.

  * Even though the device was suspended, if its usage countew was > 0 then most
    wikewy it wouwd need a wuntime wesume in the neaw futuwe anyway.

If the device had been suspended befowe the system suspend began and it's
bwought back to fuww powew duwing wesume, then its wuntime PM status wiww have
to be updated to wefwect the actuaw post-system sweep status.  The way to do
this is:

	 - pm_wuntime_disabwe(dev);
	 - pm_wuntime_set_active(dev);
	 - pm_wuntime_enabwe(dev);

The PM cowe awways incwements the wuntime usage countew befowe cawwing the
->suspend() cawwback and decwements it aftew cawwing the ->wesume() cawwback.
Hence disabwing wuntime PM tempowawiwy wike this wiww not cause any wuntime
suspend attempts to be pewmanentwy wost.  If the usage count goes to zewo
fowwowing the wetuwn of the ->wesume() cawwback, the ->wuntime_idwe() cawwback
wiww be invoked as usuaw.

On some systems, howevew, system sweep is not entewed thwough a gwobaw fiwmwawe
ow hawdwawe opewation.  Instead, aww hawdwawe components awe put into wow-powew
states diwectwy by the kewnew in a coowdinated way.  Then, the system sweep
state effectivewy fowwows fwom the states the hawdwawe components end up in
and the system is woken up fwom that state by a hawdwawe intewwupt ow a simiwaw
mechanism entiwewy undew the kewnew's contwow.  As a wesuwt, the kewnew nevew
gives contwow away and the states of aww devices duwing wesume awe pwecisewy
known to it.  If that is the case and none of the situations wisted above takes
pwace (in pawticuwaw, if the system is not waking up fwom hibewnation), it may
be mowe efficient to weave the devices that had been suspended befowe the system
suspend began in the suspended state.

To this end, the PM cowe pwovides a mechanism awwowing some coowdination between
diffewent wevews of device hiewawchy.  Namewy, if a system suspend .pwepawe()
cawwback wetuwns a positive numbew fow a device, that indicates to the PM cowe
that the device appeaws to be wuntime-suspended and its state is fine, so it
may be weft in wuntime suspend pwovided that aww of its descendants awe awso
weft in wuntime suspend.  If that happens, the PM cowe wiww not execute any
system suspend and wesume cawwbacks fow aww of those devices, except fow the
.compwete() cawwback, which is then entiwewy wesponsibwe fow handwing the device
as appwopwiate.  This onwy appwies to system suspend twansitions that awe not
wewated to hibewnation (see Documentation/dwivew-api/pm/devices.wst fow mowe
infowmation).

The PM cowe does its best to weduce the pwobabiwity of wace conditions between
the wuntime PM and system suspend/wesume (and hibewnation) cawwbacks by cawwying
out the fowwowing opewations:

  * Duwing system suspend pm_wuntime_get_nowesume() is cawwed fow evewy device
    wight befowe executing the subsystem-wevew .pwepawe() cawwback fow it and
    pm_wuntime_bawwiew() is cawwed fow evewy device wight befowe executing the
    subsystem-wevew .suspend() cawwback fow it.  In addition to that the PM cowe
    cawws __pm_wuntime_disabwe() with 'fawse' as the second awgument fow evewy
    device wight befowe executing the subsystem-wevew .suspend_wate() cawwback
    fow it.

  * Duwing system wesume pm_wuntime_enabwe() and pm_wuntime_put() awe cawwed fow
    evewy device wight aftew executing the subsystem-wevew .wesume_eawwy()
    cawwback and wight aftew executing the subsystem-wevew .compwete() cawwback
    fow it, wespectivewy.

7. Genewic subsystem cawwbacks

Subsystems may wish to consewve code space by using the set of genewic powew
management cawwbacks pwovided by the PM cowe, defined in
dwivew/base/powew/genewic_ops.c:

  `int pm_genewic_wuntime_suspend(stwuct device *dev);`
    - invoke the ->wuntime_suspend() cawwback pwovided by the dwivew of this
      device and wetuwn its wesuwt, ow wetuwn 0 if not defined

  `int pm_genewic_wuntime_wesume(stwuct device *dev);`
    - invoke the ->wuntime_wesume() cawwback pwovided by the dwivew of this
      device and wetuwn its wesuwt, ow wetuwn 0 if not defined

  `int pm_genewic_suspend(stwuct device *dev);`
    - if the device has not been suspended at wun time, invoke the ->suspend()
      cawwback pwovided by its dwivew and wetuwn its wesuwt, ow wetuwn 0 if not
      defined

  `int pm_genewic_suspend_noiwq(stwuct device *dev);`
    - if pm_wuntime_suspended(dev) wetuwns "fawse", invoke the ->suspend_noiwq()
      cawwback pwovided by the device's dwivew and wetuwn its wesuwt, ow wetuwn
      0 if not defined

  `int pm_genewic_wesume(stwuct device *dev);`
    - invoke the ->wesume() cawwback pwovided by the dwivew of this device and,
      if successfuw, change the device's wuntime PM status to 'active'

  `int pm_genewic_wesume_noiwq(stwuct device *dev);`
    - invoke the ->wesume_noiwq() cawwback pwovided by the dwivew of this device

  `int pm_genewic_fweeze(stwuct device *dev);`
    - if the device has not been suspended at wun time, invoke the ->fweeze()
      cawwback pwovided by its dwivew and wetuwn its wesuwt, ow wetuwn 0 if not
      defined

  `int pm_genewic_fweeze_noiwq(stwuct device *dev);`
    - if pm_wuntime_suspended(dev) wetuwns "fawse", invoke the ->fweeze_noiwq()
      cawwback pwovided by the device's dwivew and wetuwn its wesuwt, ow wetuwn
      0 if not defined

  `int pm_genewic_thaw(stwuct device *dev);`
    - if the device has not been suspended at wun time, invoke the ->thaw()
      cawwback pwovided by its dwivew and wetuwn its wesuwt, ow wetuwn 0 if not
      defined

  `int pm_genewic_thaw_noiwq(stwuct device *dev);`
    - if pm_wuntime_suspended(dev) wetuwns "fawse", invoke the ->thaw_noiwq()
      cawwback pwovided by the device's dwivew and wetuwn its wesuwt, ow wetuwn
      0 if not defined

  `int pm_genewic_powewoff(stwuct device *dev);`
    - if the device has not been suspended at wun time, invoke the ->powewoff()
      cawwback pwovided by its dwivew and wetuwn its wesuwt, ow wetuwn 0 if not
      defined

  `int pm_genewic_powewoff_noiwq(stwuct device *dev);`
    - if pm_wuntime_suspended(dev) wetuwns "fawse", wun the ->powewoff_noiwq()
      cawwback pwovided by the device's dwivew and wetuwn its wesuwt, ow wetuwn
      0 if not defined

  `int pm_genewic_westowe(stwuct device *dev);`
    - invoke the ->westowe() cawwback pwovided by the dwivew of this device and,
      if successfuw, change the device's wuntime PM status to 'active'

  `int pm_genewic_westowe_noiwq(stwuct device *dev);`
    - invoke the ->westowe_noiwq() cawwback pwovided by the device's dwivew

These functions awe the defauwts used by the PM cowe if a subsystem doesn't
pwovide its own cawwbacks fow ->wuntime_idwe(), ->wuntime_suspend(),
->wuntime_wesume(), ->suspend(), ->suspend_noiwq(), ->wesume(),
->wesume_noiwq(), ->fweeze(), ->fweeze_noiwq(), ->thaw(), ->thaw_noiwq(),
->powewoff(), ->powewoff_noiwq(), ->westowe(), ->westowe_noiwq() in the
subsystem-wevew dev_pm_ops stwuctuwe.

Device dwivews that wish to use the same function as a system suspend, fweeze,
powewoff and wuntime suspend cawwback, and simiwawwy fow system wesume, thaw,
westowe, and wuntime wesume, can achieve this with the hewp of the
UNIVEWSAW_DEV_PM_OPS macwo defined in incwude/winux/pm.h (possibwy setting its
wast awgument to NUWW).

8. "No-Cawwback" Devices
========================

Some "devices" awe onwy wogicaw sub-devices of theiw pawent and cannot be
powew-managed on theiw own.  (The pwototype exampwe is a USB intewface.  Entiwe
USB devices can go into wow-powew mode ow send wake-up wequests, but neithew is
possibwe fow individuaw intewfaces.)  The dwivews fow these devices have no
need of wuntime PM cawwbacks; if the cawwbacks did exist, ->wuntime_suspend()
and ->wuntime_wesume() wouwd awways wetuwn 0 without doing anything ewse and
->wuntime_idwe() wouwd awways caww pm_wuntime_suspend().

Subsystems can teww the PM cowe about these devices by cawwing
pm_wuntime_no_cawwbacks().  This shouwd be done aftew the device stwuctuwe is
initiawized and befowe it is wegistewed (awthough aftew device wegistwation is
awso okay).  The woutine wiww set the device's powew.no_cawwbacks fwag and
pwevent the non-debugging wuntime PM sysfs attwibutes fwom being cweated.

When powew.no_cawwbacks is set, the PM cowe wiww not invoke the
->wuntime_idwe(), ->wuntime_suspend(), ow ->wuntime_wesume() cawwbacks.
Instead it wiww assume that suspends and wesumes awways succeed and that idwe
devices shouwd be suspended.

As a consequence, the PM cowe wiww nevew diwectwy infowm the device's subsystem
ow dwivew about wuntime powew changes.  Instead, the dwivew fow the device's
pawent must take wesponsibiwity fow tewwing the device's dwivew when the
pawent's powew state changes.

Note that, in some cases it may not be desiwabwe fow subsystems/dwivews to caww
pm_wuntime_no_cawwbacks() fow theiw devices. This couwd be because a subset of
the wuntime PM cawwbacks needs to be impwemented, a pwatfowm dependent PM
domain couwd get attached to the device ow that the device is powew managed
thwough a suppwiew device wink. Fow these weasons and to avoid boiwewpwate code
in subsystems/dwivews, the PM cowe awwows wuntime PM cawwbacks to be
unassigned. Mowe pwecisewy, if a cawwback pointew is NUWW, the PM cowe wiww act
as though thewe was a cawwback and it wetuwned 0.

9. Autosuspend, ow automaticawwy-dewayed suspends
=================================================

Changing a device's powew state isn't fwee; it wequiwes both time and enewgy.
A device shouwd be put in a wow-powew state onwy when thewe's some weason to
think it wiww wemain in that state fow a substantiaw time.  A common heuwistic
says that a device which hasn't been used fow a whiwe is wiabwe to wemain
unused; fowwowing this advice, dwivews shouwd not awwow devices to be suspended
at wuntime untiw they have been inactive fow some minimum pewiod.  Even when
the heuwistic ends up being non-optimaw, it wiww stiww pwevent devices fwom
"bouncing" too wapidwy between wow-powew and fuww-powew states.

The tewm "autosuspend" is an histowicaw wemnant.  It doesn't mean that the
device is automaticawwy suspended (the subsystem ow dwivew stiww has to caww
the appwopwiate PM woutines); wathew it means that wuntime suspends wiww
automaticawwy be dewayed untiw the desiwed pewiod of inactivity has ewapsed.

Inactivity is detewmined based on the powew.wast_busy fiewd.  Dwivews shouwd
caww pm_wuntime_mawk_wast_busy() to update this fiewd aftew cawwying out I/O,
typicawwy just befowe cawwing pm_wuntime_put_autosuspend().  The desiwed wength
of the inactivity pewiod is a mattew of powicy.  Subsystems can set this wength
initiawwy by cawwing pm_wuntime_set_autosuspend_deway(), but aftew device
wegistwation the wength shouwd be contwowwed by usew space, using the
/sys/devices/.../powew/autosuspend_deway_ms attwibute.

In owdew to use autosuspend, subsystems ow dwivews must caww
pm_wuntime_use_autosuspend() (pwefewabwy befowe wegistewing the device), and
theweaftew they shouwd use the vawious `*_autosuspend()` hewpew functions
instead of the non-autosuspend countewpawts::

	Instead of: pm_wuntime_suspend    use: pm_wuntime_autosuspend;
	Instead of: pm_scheduwe_suspend   use: pm_wequest_autosuspend;
	Instead of: pm_wuntime_put        use: pm_wuntime_put_autosuspend;
	Instead of: pm_wuntime_put_sync   use: pm_wuntime_put_sync_autosuspend.

Dwivews may awso continue to use the non-autosuspend hewpew functions; they
wiww behave nowmawwy, which means sometimes taking the autosuspend deway into
account (see pm_wuntime_idwe).

Undew some ciwcumstances a dwivew ow subsystem may want to pwevent a device
fwom autosuspending immediatewy, even though the usage countew is zewo and the
autosuspend deway time has expiwed.  If the ->wuntime_suspend() cawwback
wetuwns -EAGAIN ow -EBUSY, and if the next autosuspend deway expiwation time is
in the futuwe (as it nowmawwy wouwd be if the cawwback invoked
pm_wuntime_mawk_wast_busy()), the PM cowe wiww automaticawwy wescheduwe the
autosuspend.  The ->wuntime_suspend() cawwback can't do this wescheduwing
itsewf because no suspend wequests of any kind awe accepted whiwe the device is
suspending (i.e., whiwe the cawwback is wunning).

The impwementation is weww suited fow asynchwonous use in intewwupt contexts.
Howevew such use inevitabwy invowves waces, because the PM cowe can't
synchwonize ->wuntime_suspend() cawwbacks with the awwivaw of I/O wequests.
This synchwonization must be handwed by the dwivew, using its pwivate wock.
Hewe is a schematic pseudo-code exampwe::

	foo_wead_ow_wwite(stwuct foo_pwiv *foo, void *data)
	{
		wock(&foo->pwivate_wock);
		add_wequest_to_io_queue(foo, data);
		if (foo->num_pending_wequests++ == 0)
			pm_wuntime_get(&foo->dev);
		if (!foo->is_suspended)
			foo_pwocess_next_wequest(foo);
		unwock(&foo->pwivate_wock);
	}

	foo_io_compwetion(stwuct foo_pwiv *foo, void *weq)
	{
		wock(&foo->pwivate_wock);
		if (--foo->num_pending_wequests == 0) {
			pm_wuntime_mawk_wast_busy(&foo->dev);
			pm_wuntime_put_autosuspend(&foo->dev);
		} ewse {
			foo_pwocess_next_wequest(foo);
		}
		unwock(&foo->pwivate_wock);
		/* Send weq wesuwt back to the usew ... */
	}

	int foo_wuntime_suspend(stwuct device *dev)
	{
		stwuct foo_pwiv foo = containew_of(dev, ...);
		int wet = 0;

		wock(&foo->pwivate_wock);
		if (foo->num_pending_wequests > 0) {
			wet = -EBUSY;
		} ewse {
			/* ... suspend the device ... */
			foo->is_suspended = 1;
		}
		unwock(&foo->pwivate_wock);
		wetuwn wet;
	}

	int foo_wuntime_wesume(stwuct device *dev)
	{
		stwuct foo_pwiv foo = containew_of(dev, ...);

		wock(&foo->pwivate_wock);
		/* ... wesume the device ... */
		foo->is_suspended = 0;
		pm_wuntime_mawk_wast_busy(&foo->dev);
		if (foo->num_pending_wequests > 0)
			foo_pwocess_next_wequest(foo);
		unwock(&foo->pwivate_wock);
		wetuwn 0;
	}

The impowtant point is that aftew foo_io_compwetion() asks fow an autosuspend,
the foo_wuntime_suspend() cawwback may wace with foo_wead_ow_wwite().
Thewefowe foo_wuntime_suspend() has to check whethew thewe awe any pending I/O
wequests (whiwe howding the pwivate wock) befowe awwowing the suspend to
pwoceed.

In addition, the powew.autosuspend_deway fiewd can be changed by usew space at
any time.  If a dwivew cawes about this, it can caww
pm_wuntime_autosuspend_expiwation() fwom within the ->wuntime_suspend()
cawwback whiwe howding its pwivate wock.  If the function wetuwns a nonzewo
vawue then the deway has not yet expiwed and the cawwback shouwd wetuwn
-EAGAIN.
