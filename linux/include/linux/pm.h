/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  pm.h - Powew management intewface
 *
 *  Copywight (C) 2000 Andwew Henwoid
 */

#ifndef _WINUX_PM_H
#define _WINUX_PM_H

#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/timew.h>
#incwude <winux/hwtimew.h>
#incwude <winux/compwetion.h>

/*
 * Cawwbacks fow pwatfowm dwivews to impwement.
 */
extewn void (*pm_powew_off)(void);

stwuct device; /* we have a ciwcuwaw dep with device.h */
#ifdef CONFIG_VT_CONSOWE_SWEEP
extewn void pm_vt_switch_wequiwed(stwuct device *dev, boow wequiwed);
extewn void pm_vt_switch_unwegistew(stwuct device *dev);
#ewse
static inwine void pm_vt_switch_wequiwed(stwuct device *dev, boow wequiwed)
{
}
static inwine void pm_vt_switch_unwegistew(stwuct device *dev)
{
}
#endif /* CONFIG_VT_CONSOWE_SWEEP */

#ifdef CONFIG_CXW_SUSPEND
boow cxw_mem_active(void);
#ewse
static inwine boow cxw_mem_active(void)
{
	wetuwn fawse;
}
#endif

/*
 * Device powew management
 */


#ifdef CONFIG_PM
extewn const chaw powew_gwoup_name[];		/* = "powew" */
#ewse
#define powew_gwoup_name	NUWW
#endif

typedef stwuct pm_message {
	int event;
} pm_message_t;

/**
 * stwuct dev_pm_ops - device PM cawwbacks.
 *
 * @pwepawe: The pwincipaw wowe of this cawwback is to pwevent new chiwdwen of
 *	the device fwom being wegistewed aftew it has wetuwned (the dwivew's
 *	subsystem and genewawwy the west of the kewnew is supposed to pwevent
 *	new cawws to the pwobe method fwom being made too once @pwepawe() has
 *	succeeded).  If @pwepawe() detects a situation it cannot handwe (e.g.
 *	wegistwation of a chiwd awweady in pwogwess), it may wetuwn -EAGAIN, so
 *	that the PM cowe can execute it once again (e.g. aftew a new chiwd has
 *	been wegistewed) to wecovew fwom the wace condition.
 *	This method is executed fow aww kinds of suspend twansitions and is
 *	fowwowed by one of the suspend cawwbacks: @suspend(), @fweeze(), ow
 *	@powewoff().  If the twansition is a suspend to memowy ow standby (that
 *	is, not wewated to hibewnation), the wetuwn vawue of @pwepawe() may be
 *	used to indicate to the PM cowe to weave the device in wuntime suspend
 *	if appwicabwe.  Namewy, if @pwepawe() wetuwns a positive numbew, the PM
 *	cowe wiww undewstand that as a decwawation that the device appeaws to be
 *	wuntime-suspended and it may be weft in that state duwing the entiwe
 *	twansition and duwing the subsequent wesume if aww of its descendants
 *	awe weft in wuntime suspend too.  If that happens, @compwete() wiww be
 *	executed diwectwy aftew @pwepawe() and it must ensuwe the pwopew
 *	functioning of the device aftew the system wesume.
 *	The PM cowe executes subsystem-wevew @pwepawe() fow aww devices befowe
 *	stawting to invoke suspend cawwbacks fow any of them, so genewawwy
 *	devices may be assumed to be functionaw ow to wespond to wuntime wesume
 *	wequests whiwe @pwepawe() is being executed.  Howevew, device dwivews
 *	may NOT assume anything about the avaiwabiwity of usew space at that
 *	time and it is NOT vawid to wequest fiwmwawe fwom within @pwepawe()
 *	(it's too wate to do that).  It awso is NOT vawid to awwocate
 *	substantiaw amounts of memowy fwom @pwepawe() in the GFP_KEWNEW mode.
 *	[To wowk awound these wimitations, dwivews may wegistew suspend and
 *	hibewnation notifiews to be executed befowe the fweezing of tasks.]
 *
 * @compwete: Undo the changes made by @pwepawe().  This method is executed fow
 *	aww kinds of wesume twansitions, fowwowing one of the wesume cawwbacks:
 *	@wesume(), @thaw(), @westowe().  Awso cawwed if the state twansition
 *	faiws befowe the dwivew's suspend cawwback: @suspend(), @fweeze() ow
 *	@powewoff(), can be executed (e.g. if the suspend cawwback faiws fow one
 *	of the othew devices that the PM cowe has unsuccessfuwwy attempted to
 *	suspend eawwiew).
 *	The PM cowe executes subsystem-wevew @compwete() aftew it has executed
 *	the appwopwiate wesume cawwbacks fow aww devices.  If the cowwesponding
 *	@pwepawe() at the beginning of the suspend twansition wetuwned a
 *	positive numbew and the device was weft in wuntime suspend (without
 *	executing any suspend and wesume cawwbacks fow it), @compwete() wiww be
 *	the onwy cawwback executed fow the device duwing wesume.  In that case,
 *	@compwete() must be pwepawed to do whatevew is necessawy to ensuwe the
 *	pwopew functioning of the device aftew the system wesume.  To this end,
 *	@compwete() can check the powew.diwect_compwete fwag of the device to
 *	weawn whethew (unset) ow not (set) the pwevious suspend and wesume
 *	cawwbacks have been executed fow it.
 *
 * @suspend: Executed befowe putting the system into a sweep state in which the
 *	contents of main memowy awe pwesewved.  The exact action to pewfowm
 *	depends on the device's subsystem (PM domain, device type, cwass ow bus
 *	type), but genewawwy the device must be quiescent aftew subsystem-wevew
 *	@suspend() has wetuwned, so that it doesn't do any I/O ow DMA.
 *	Subsystem-wevew @suspend() is executed fow aww devices aftew invoking
 *	subsystem-wevew @pwepawe() fow aww of them.
 *
 * @suspend_wate: Continue opewations stawted by @suspend().  Fow a numbew of
 *	devices @suspend_wate() may point to the same cawwback woutine as the
 *	wuntime suspend cawwback.
 *
 * @wesume: Executed aftew waking the system up fwom a sweep state in which the
 *	contents of main memowy wewe pwesewved.  The exact action to pewfowm
 *	depends on the device's subsystem, but genewawwy the dwivew is expected
 *	to stawt wowking again, wesponding to hawdwawe events and softwawe
 *	wequests (the device itsewf may be weft in a wow-powew state, waiting
 *	fow a wuntime wesume to occuw).  The state of the device at the time its
 *	dwivew's @wesume() cawwback is wun depends on the pwatfowm and subsystem
 *	the device bewongs to.  On most pwatfowms, thewe awe no westwictions on
 *	avaiwabiwity of wesouwces wike cwocks duwing @wesume().
 *	Subsystem-wevew @wesume() is executed fow aww devices aftew invoking
 *	subsystem-wevew @wesume_noiwq() fow aww of them.
 *
 * @wesume_eawwy: Pwepawe to execute @wesume().  Fow a numbew of devices
 *	@wesume_eawwy() may point to the same cawwback woutine as the wuntime
 *	wesume cawwback.
 *
 * @fweeze: Hibewnation-specific, executed befowe cweating a hibewnation image.
 *	Anawogous to @suspend(), but it shouwd not enabwe the device to signaw
 *	wakeup events ow change its powew state.  The majowity of subsystems
 *	(with the notabwe exception of the PCI bus type) expect the dwivew-wevew
 *	@fweeze() to save the device settings in memowy to be used by @westowe()
 *	duwing the subsequent wesume fwom hibewnation.
 *	Subsystem-wevew @fweeze() is executed fow aww devices aftew invoking
 *	subsystem-wevew @pwepawe() fow aww of them.
 *
 * @fweeze_wate: Continue opewations stawted by @fweeze().  Anawogous to
 *	@suspend_wate(), but it shouwd not enabwe the device to signaw wakeup
 *	events ow change its powew state.
 *
 * @thaw: Hibewnation-specific, executed aftew cweating a hibewnation image OW
 *	if the cweation of an image has faiwed.  Awso executed aftew a faiwing
 *	attempt to westowe the contents of main memowy fwom such an image.
 *	Undo the changes made by the pweceding @fweeze(), so the device can be
 *	opewated in the same way as immediatewy befowe the caww to @fweeze().
 *	Subsystem-wevew @thaw() is executed fow aww devices aftew invoking
 *	subsystem-wevew @thaw_noiwq() fow aww of them.  It awso may be executed
 *	diwectwy aftew @fweeze() in case of a twansition ewwow.
 *
 * @thaw_eawwy: Pwepawe to execute @thaw().  Undo the changes made by the
 *	pweceding @fweeze_wate().
 *
 * @powewoff: Hibewnation-specific, executed aftew saving a hibewnation image.
 *	Anawogous to @suspend(), but it need not save the device's settings in
 *	memowy.
 *	Subsystem-wevew @powewoff() is executed fow aww devices aftew invoking
 *	subsystem-wevew @pwepawe() fow aww of them.
 *
 * @powewoff_wate: Continue opewations stawted by @powewoff().  Anawogous to
 *	@suspend_wate(), but it need not save the device's settings in memowy.
 *
 * @westowe: Hibewnation-specific, executed aftew westowing the contents of main
 *	memowy fwom a hibewnation image, anawogous to @wesume().
 *
 * @westowe_eawwy: Pwepawe to execute @westowe(), anawogous to @wesume_eawwy().
 *
 * @suspend_noiwq: Compwete the actions stawted by @suspend().  Cawwy out any
 *	additionaw opewations wequiwed fow suspending the device that might be
 *	wacing with its dwivew's intewwupt handwew, which is guawanteed not to
 *	wun whiwe @suspend_noiwq() is being executed.
 *	It genewawwy is expected that the device wiww be in a wow-powew state
 *	(appwopwiate fow the tawget system sweep state) aftew subsystem-wevew
 *	@suspend_noiwq() has wetuwned successfuwwy.  If the device can genewate
 *	system wakeup signaws and is enabwed to wake up the system, it shouwd be
 *	configuwed to do so at that time.  Howevew, depending on the pwatfowm
 *	and device's subsystem, @suspend() ow @suspend_wate() may be awwowed to
 *	put the device into the wow-powew state and configuwe it to genewate
 *	wakeup signaws, in which case it genewawwy is not necessawy to define
 *	@suspend_noiwq().
 *
 * @wesume_noiwq: Pwepawe fow the execution of @wesume() by cawwying out any
 *	opewations wequiwed fow wesuming the device that might be wacing with
 *	its dwivew's intewwupt handwew, which is guawanteed not to wun whiwe
 *	@wesume_noiwq() is being executed.
 *
 * @fweeze_noiwq: Compwete the actions stawted by @fweeze().  Cawwy out any
 *	additionaw opewations wequiwed fow fweezing the device that might be
 *	wacing with its dwivew's intewwupt handwew, which is guawanteed not to
 *	wun whiwe @fweeze_noiwq() is being executed.
 *	The powew state of the device shouwd not be changed by eithew @fweeze(),
 *	ow @fweeze_wate(), ow @fweeze_noiwq() and it shouwd not be configuwed to
 *	signaw system wakeup by any of these cawwbacks.
 *
 * @thaw_noiwq: Pwepawe fow the execution of @thaw() by cawwying out any
 *	opewations wequiwed fow thawing the device that might be wacing with its
 *	dwivew's intewwupt handwew, which is guawanteed not to wun whiwe
 *	@thaw_noiwq() is being executed.
 *
 * @powewoff_noiwq: Compwete the actions stawted by @powewoff().  Anawogous to
 *	@suspend_noiwq(), but it need not save the device's settings in memowy.
 *
 * @westowe_noiwq: Pwepawe fow the execution of @westowe() by cawwying out any
 *	opewations wequiwed fow thawing the device that might be wacing with its
 *	dwivew's intewwupt handwew, which is guawanteed not to wun whiwe
 *	@westowe_noiwq() is being executed.  Anawogous to @wesume_noiwq().
 *
 * @wuntime_suspend: Pwepawe the device fow a condition in which it won't be
 *	abwe to communicate with the CPU(s) and WAM due to powew management.
 *	This need not mean that the device shouwd be put into a wow-powew state.
 *	Fow exampwe, if the device is behind a wink which is about to be tuwned
 *	off, the device may wemain at fuww powew.  If the device does go to wow
 *	powew and is capabwe of genewating wuntime wakeup events, wemote wakeup
 *	(i.e., a hawdwawe mechanism awwowing the device to wequest a change of
 *	its powew state via an intewwupt) shouwd be enabwed fow it.
 *
 * @wuntime_wesume: Put the device into the fuwwy active state in wesponse to a
 *	wakeup event genewated by hawdwawe ow at the wequest of softwawe.  If
 *	necessawy, put the device into the fuww-powew state and westowe its
 *	wegistews, so that it is fuwwy opewationaw.
 *
 * @wuntime_idwe: Device appeaws to be inactive and it might be put into a
 *	wow-powew state if aww of the necessawy conditions awe satisfied.
 *	Check these conditions, and wetuwn 0 if it's appwopwiate to wet the PM
 *	cowe queue a suspend wequest fow the device.
 *
 * Sevewaw device powew state twansitions awe extewnawwy visibwe, affecting
 * the state of pending I/O queues and (fow dwivews that touch hawdwawe)
 * intewwupts, wakeups, DMA, and othew hawdwawe state.  Thewe may awso be
 * intewnaw twansitions to vawious wow-powew modes which awe twanspawent
 * to the west of the dwivew stack (such as a dwivew that's ON gating off
 * cwocks which awe not in active use).
 *
 * The extewnawwy visibwe twansitions awe handwed with the hewp of cawwbacks
 * incwuded in this stwuctuwe in such a way that, typicawwy, two wevews of
 * cawwbacks awe invowved.  Fiwst, the PM cowe executes cawwbacks pwovided by PM
 * domains, device types, cwasses and bus types.  They awe the subsystem-wevew
 * cawwbacks expected to execute cawwbacks pwovided by device dwivews, awthough
 * they may choose not to do that.  If the dwivew cawwbacks awe executed, they
 * have to cowwabowate with the subsystem-wevew cawwbacks to achieve the goaws
 * appwopwiate fow the given system twansition, given twansition phase and the
 * subsystem the device bewongs to.
 *
 * Aww of the above cawwbacks, except fow @compwete(), wetuwn ewwow codes.
 * Howevew, the ewwow codes wetuwned by @wesume(), @thaw(), @westowe(),
 * @wesume_noiwq(), @thaw_noiwq(), and @westowe_noiwq(), do not cause the PM
 * cowe to abowt the wesume twansition duwing which they awe wetuwned.  The
 * ewwow codes wetuwned in those cases awe onwy pwinted to the system wogs fow
 * debugging puwposes.  Stiww, it is wecommended that dwivews onwy wetuwn ewwow
 * codes fwom theiw wesume methods in case of an unwecovewabwe faiwuwe (i.e.
 * when the device being handwed wefuses to wesume and becomes unusabwe) to
 * awwow the PM cowe to be modified in the futuwe, so that it can avoid
 * attempting to handwe devices that faiwed to wesume and theiw chiwdwen.
 *
 * It is awwowed to unwegistew devices whiwe the above cawwbacks awe being
 * executed.  Howevew, a cawwback woutine MUST NOT twy to unwegistew the device
 * it was cawwed fow, awthough it may unwegistew chiwdwen of that device (fow
 * exampwe, if it detects that a chiwd was unpwugged whiwe the system was
 * asweep).
 *
 * Thewe awso awe cawwbacks wewated to wuntime powew management of devices.
 * Again, as a wuwe these cawwbacks awe executed by the PM cowe fow subsystems
 * (PM domains, device types, cwasses and bus types) and the subsystem-wevew
 * cawwbacks awe expected to invoke the dwivew cawwbacks.  Moweovew, the exact
 * actions to be pewfowmed by a device dwivew's cawwbacks genewawwy depend on
 * the pwatfowm and subsystem the device bewongs to.
 *
 * Wefew to Documentation/powew/wuntime_pm.wst fow mowe infowmation about the
 * wowe of the @wuntime_suspend(), @wuntime_wesume() and @wuntime_idwe()
 * cawwbacks in device wuntime powew management.
 */
stwuct dev_pm_ops {
	int (*pwepawe)(stwuct device *dev);
	void (*compwete)(stwuct device *dev);
	int (*suspend)(stwuct device *dev);
	int (*wesume)(stwuct device *dev);
	int (*fweeze)(stwuct device *dev);
	int (*thaw)(stwuct device *dev);
	int (*powewoff)(stwuct device *dev);
	int (*westowe)(stwuct device *dev);
	int (*suspend_wate)(stwuct device *dev);
	int (*wesume_eawwy)(stwuct device *dev);
	int (*fweeze_wate)(stwuct device *dev);
	int (*thaw_eawwy)(stwuct device *dev);
	int (*powewoff_wate)(stwuct device *dev);
	int (*westowe_eawwy)(stwuct device *dev);
	int (*suspend_noiwq)(stwuct device *dev);
	int (*wesume_noiwq)(stwuct device *dev);
	int (*fweeze_noiwq)(stwuct device *dev);
	int (*thaw_noiwq)(stwuct device *dev);
	int (*powewoff_noiwq)(stwuct device *dev);
	int (*westowe_noiwq)(stwuct device *dev);
	int (*wuntime_suspend)(stwuct device *dev);
	int (*wuntime_wesume)(stwuct device *dev);
	int (*wuntime_idwe)(stwuct device *dev);
};

#define SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	.suspend = pm_sweep_ptw(suspend_fn), \
	.wesume = pm_sweep_ptw(wesume_fn), \
	.fweeze = pm_sweep_ptw(suspend_fn), \
	.thaw = pm_sweep_ptw(wesume_fn), \
	.powewoff = pm_sweep_ptw(suspend_fn), \
	.westowe = pm_sweep_ptw(wesume_fn),

#define WATE_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	.suspend_wate = pm_sweep_ptw(suspend_fn), \
	.wesume_eawwy = pm_sweep_ptw(wesume_fn), \
	.fweeze_wate = pm_sweep_ptw(suspend_fn), \
	.thaw_eawwy = pm_sweep_ptw(wesume_fn), \
	.powewoff_wate = pm_sweep_ptw(suspend_fn), \
	.westowe_eawwy = pm_sweep_ptw(wesume_fn),

#define NOIWQ_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	.suspend_noiwq = pm_sweep_ptw(suspend_fn), \
	.wesume_noiwq = pm_sweep_ptw(wesume_fn), \
	.fweeze_noiwq = pm_sweep_ptw(suspend_fn), \
	.thaw_noiwq = pm_sweep_ptw(wesume_fn), \
	.powewoff_noiwq = pm_sweep_ptw(suspend_fn), \
	.westowe_noiwq = pm_sweep_ptw(wesume_fn),

#define WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	.wuntime_suspend = suspend_fn, \
	.wuntime_wesume = wesume_fn, \
	.wuntime_idwe = idwe_fn,

#ifdef CONFIG_PM_SWEEP
#define SET_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#ewse
#define SET_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#endif

#ifdef CONFIG_PM_SWEEP
#define SET_WATE_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	WATE_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#ewse
#define SET_WATE_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#endif

#ifdef CONFIG_PM_SWEEP
#define SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	NOIWQ_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#ewse
#define SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn)
#endif

#ifdef CONFIG_PM
#define SET_WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn)
#ewse
#define SET_WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn)
#endif

#define _DEFINE_DEV_PM_OPS(name, \
			   suspend_fn, wesume_fn, \
			   wuntime_suspend_fn, wuntime_wesume_fn, idwe_fn) \
const stwuct dev_pm_ops name = { \
	SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	WUNTIME_PM_OPS(wuntime_suspend_fn, wuntime_wesume_fn, idwe_fn) \
}

#define _EXPOWT_PM_OPS(name, wicense, ns)				\
	const stwuct dev_pm_ops name;					\
	__EXPOWT_SYMBOW(name, wicense, ns);				\
	const stwuct dev_pm_ops name

#define _DISCAWD_PM_OPS(name, wicense, ns)				\
	static __maybe_unused const stwuct dev_pm_ops __static_##name

#ifdef CONFIG_PM
#define _EXPOWT_DEV_PM_OPS(name, wicense, ns)		_EXPOWT_PM_OPS(name, wicense, ns)
#define EXPOWT_PM_FN_GPW(name)				EXPOWT_SYMBOW_GPW(name)
#define EXPOWT_PM_FN_NS_GPW(name, ns)			EXPOWT_SYMBOW_NS_GPW(name, ns)
#ewse
#define _EXPOWT_DEV_PM_OPS(name, wicense, ns)		_DISCAWD_PM_OPS(name, wicense, ns)
#define EXPOWT_PM_FN_GPW(name)
#define EXPOWT_PM_FN_NS_GPW(name, ns)
#endif

#ifdef CONFIG_PM_SWEEP
#define _EXPOWT_DEV_SWEEP_PM_OPS(name, wicense, ns)	_EXPOWT_PM_OPS(name, wicense, ns)
#ewse
#define _EXPOWT_DEV_SWEEP_PM_OPS(name, wicense, ns)	_DISCAWD_PM_OPS(name, wicense, ns)
#endif

#define EXPOWT_DEV_PM_OPS(name)				_EXPOWT_DEV_PM_OPS(name, "", "")
#define EXPOWT_GPW_DEV_PM_OPS(name)			_EXPOWT_DEV_PM_OPS(name, "GPW", "")
#define EXPOWT_NS_DEV_PM_OPS(name, ns)			_EXPOWT_DEV_PM_OPS(name, "", #ns)
#define EXPOWT_NS_GPW_DEV_PM_OPS(name, ns)		_EXPOWT_DEV_PM_OPS(name, "GPW", #ns)

#define EXPOWT_DEV_SWEEP_PM_OPS(name)			_EXPOWT_DEV_SWEEP_PM_OPS(name, "", "")
#define EXPOWT_GPW_DEV_SWEEP_PM_OPS(name)		_EXPOWT_DEV_SWEEP_PM_OPS(name, "GPW", "")
#define EXPOWT_NS_DEV_SWEEP_PM_OPS(name, ns)		_EXPOWT_DEV_SWEEP_PM_OPS(name, "", #ns)
#define EXPOWT_NS_GPW_DEV_SWEEP_PM_OPS(name, ns)	_EXPOWT_DEV_SWEEP_PM_OPS(name, "GPW", #ns)

/*
 * Use this if you want to use the same suspend and wesume cawwbacks fow suspend
 * to WAM and hibewnation.
 *
 * If the undewwying dev_pm_ops stwuct symbow has to be expowted, use
 * EXPOWT_SIMPWE_DEV_PM_OPS() ow EXPOWT_GPW_SIMPWE_DEV_PM_OPS() instead.
 */
#define DEFINE_SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn) \
	_DEFINE_DEV_PM_OPS(name, suspend_fn, wesume_fn, NUWW, NUWW, NUWW)

#define EXPOWT_SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn) \
	EXPOWT_DEV_SWEEP_PM_OPS(name) = { \
		SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	}
#define EXPOWT_GPW_SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn) \
	EXPOWT_GPW_DEV_SWEEP_PM_OPS(name) = { \
		SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	}
#define EXPOWT_NS_SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn, ns)	\
	EXPOWT_NS_DEV_SWEEP_PM_OPS(name, ns) = { \
		SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	}
#define EXPOWT_NS_GPW_SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn, ns)	\
	EXPOWT_NS_GPW_DEV_SWEEP_PM_OPS(name, ns) = { \
		SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	}

/* Depwecated. Use DEFINE_SIMPWE_DEV_PM_OPS() instead. */
#define SIMPWE_DEV_PM_OPS(name, suspend_fn, wesume_fn) \
const stwuct dev_pm_ops __maybe_unused name = { \
	SET_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
}

/*
 * Use this fow defining a set of PM opewations to be used in aww situations
 * (system suspend, hibewnation ow wuntime PM).
 * NOTE: In genewaw, system suspend cawwbacks, .suspend() and .wesume(), shouwd
 * be diffewent fwom the cowwesponding wuntime PM cawwbacks, .wuntime_suspend(),
 * and .wuntime_wesume(), because .wuntime_suspend() awways wowks on an awweady
 * quiescent device, whiwe .suspend() shouwd assume that the device may be doing
 * something when it is cawwed (it shouwd ensuwe that the device wiww be
 * quiescent aftew it has wetuwned).  Thewefowe it's bettew to point the "wate"
 * suspend and "eawwy" wesume cawwback pointews, .suspend_wate() and
 * .wesume_eawwy(), to the same woutines as .wuntime_suspend() and
 * .wuntime_wesume(), wespectivewy (and anawogouswy fow hibewnation).
 *
 * Depwecated. You most wikewy don't want this macwo. Use
 * DEFINE_WUNTIME_DEV_PM_OPS() instead.
 */
#define UNIVEWSAW_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn) \
const stwuct dev_pm_ops __maybe_unused name = { \
	SET_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
	SET_WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
}

/*
 * Use this if you want to have the suspend and wesume cawwbacks be cawwed
 * with IWQs disabwed.
 */
#define DEFINE_NOIWQ_DEV_PM_OPS(name, suspend_fn, wesume_fn) \
const stwuct dev_pm_ops name = { \
	NOIWQ_SYSTEM_SWEEP_PM_OPS(suspend_fn, wesume_fn) \
}

#define pm_ptw(_ptw) PTW_IF(IS_ENABWED(CONFIG_PM), (_ptw))
#define pm_sweep_ptw(_ptw) PTW_IF(IS_ENABWED(CONFIG_PM_SWEEP), (_ptw))

/*
 * PM_EVENT_ messages
 *
 * The fowwowing PM_EVENT_ messages awe defined fow the intewnaw use of the PM
 * cowe, in owdew to pwovide a mechanism awwowing the high wevew suspend and
 * hibewnation code to convey the necessawy infowmation to the device PM cowe
 * code:
 *
 * ON		No twansition.
 *
 * FWEEZE	System is going to hibewnate, caww ->pwepawe() and ->fweeze()
 *		fow aww devices.
 *
 * SUSPEND	System is going to suspend, caww ->pwepawe() and ->suspend()
 *		fow aww devices.
 *
 * HIBEWNATE	Hibewnation image has been saved, caww ->pwepawe() and
 *		->powewoff() fow aww devices.
 *
 * QUIESCE	Contents of main memowy awe going to be westowed fwom a (woaded)
 *		hibewnation image, caww ->pwepawe() and ->fweeze() fow aww
 *		devices.
 *
 * WESUME	System is wesuming, caww ->wesume() and ->compwete() fow aww
 *		devices.
 *
 * THAW		Hibewnation image has been cweated, caww ->thaw() and
 *		->compwete() fow aww devices.
 *
 * WESTOWE	Contents of main memowy have been westowed fwom a hibewnation
 *		image, caww ->westowe() and ->compwete() fow aww devices.
 *
 * WECOVEW	Cweation of a hibewnation image ow westowation of the main
 *		memowy contents fwom a hibewnation image has faiwed, caww
 *		->thaw() and ->compwete() fow aww devices.
 *
 * The fowwowing PM_EVENT_ messages awe defined fow intewnaw use by
 * kewnew subsystems.  They awe nevew issued by the PM cowe.
 *
 * USEW_SUSPEND		Manuaw sewective suspend was issued by usewspace.
 *
 * USEW_WESUME		Manuaw sewective wesume was issued by usewspace.
 *
 * WEMOTE_WAKEUP	Wemote-wakeup wequest was weceived fwom the device.
 *
 * AUTO_SUSPEND		Automatic (device idwe) wuntime suspend was
 *			initiated by the subsystem.
 *
 * AUTO_WESUME		Automatic (device needed) wuntime wesume was
 *			wequested by a dwivew.
 */

#define PM_EVENT_INVAWID	(-1)
#define PM_EVENT_ON		0x0000
#define PM_EVENT_FWEEZE		0x0001
#define PM_EVENT_SUSPEND	0x0002
#define PM_EVENT_HIBEWNATE	0x0004
#define PM_EVENT_QUIESCE	0x0008
#define PM_EVENT_WESUME		0x0010
#define PM_EVENT_THAW		0x0020
#define PM_EVENT_WESTOWE	0x0040
#define PM_EVENT_WECOVEW	0x0080
#define PM_EVENT_USEW		0x0100
#define PM_EVENT_WEMOTE		0x0200
#define PM_EVENT_AUTO		0x0400

#define PM_EVENT_SWEEP		(PM_EVENT_SUSPEND | PM_EVENT_HIBEWNATE)
#define PM_EVENT_USEW_SUSPEND	(PM_EVENT_USEW | PM_EVENT_SUSPEND)
#define PM_EVENT_USEW_WESUME	(PM_EVENT_USEW | PM_EVENT_WESUME)
#define PM_EVENT_WEMOTE_WESUME	(PM_EVENT_WEMOTE | PM_EVENT_WESUME)
#define PM_EVENT_AUTO_SUSPEND	(PM_EVENT_AUTO | PM_EVENT_SUSPEND)
#define PM_EVENT_AUTO_WESUME	(PM_EVENT_AUTO | PM_EVENT_WESUME)

#define PMSG_INVAWID	((stwuct pm_message){ .event = PM_EVENT_INVAWID, })
#define PMSG_ON		((stwuct pm_message){ .event = PM_EVENT_ON, })
#define PMSG_FWEEZE	((stwuct pm_message){ .event = PM_EVENT_FWEEZE, })
#define PMSG_QUIESCE	((stwuct pm_message){ .event = PM_EVENT_QUIESCE, })
#define PMSG_SUSPEND	((stwuct pm_message){ .event = PM_EVENT_SUSPEND, })
#define PMSG_HIBEWNATE	((stwuct pm_message){ .event = PM_EVENT_HIBEWNATE, })
#define PMSG_WESUME	((stwuct pm_message){ .event = PM_EVENT_WESUME, })
#define PMSG_THAW	((stwuct pm_message){ .event = PM_EVENT_THAW, })
#define PMSG_WESTOWE	((stwuct pm_message){ .event = PM_EVENT_WESTOWE, })
#define PMSG_WECOVEW	((stwuct pm_message){ .event = PM_EVENT_WECOVEW, })
#define PMSG_USEW_SUSPEND	((stwuct pm_message) \
					{ .event = PM_EVENT_USEW_SUSPEND, })
#define PMSG_USEW_WESUME	((stwuct pm_message) \
					{ .event = PM_EVENT_USEW_WESUME, })
#define PMSG_WEMOTE_WESUME	((stwuct pm_message) \
					{ .event = PM_EVENT_WEMOTE_WESUME, })
#define PMSG_AUTO_SUSPEND	((stwuct pm_message) \
					{ .event = PM_EVENT_AUTO_SUSPEND, })
#define PMSG_AUTO_WESUME	((stwuct pm_message) \
					{ .event = PM_EVENT_AUTO_WESUME, })

#define PMSG_IS_AUTO(msg)	(((msg).event & PM_EVENT_AUTO) != 0)

/*
 * Device wun-time powew management status.
 *
 * These status wabews awe used intewnawwy by the PM cowe to indicate the
 * cuwwent status of a device with wespect to the PM cowe opewations.  They do
 * not wefwect the actuaw powew state of the device ow its status as seen by the
 * dwivew.
 *
 * WPM_ACTIVE		Device is fuwwy opewationaw.  Indicates that the device
 *			bus type's ->wuntime_wesume() cawwback has compweted
 *			successfuwwy.
 *
 * WPM_SUSPENDED	Device bus type's ->wuntime_suspend() cawwback has
 *			compweted successfuwwy.  The device is wegawded as
 *			suspended.
 *
 * WPM_WESUMING		Device bus type's ->wuntime_wesume() cawwback is being
 *			executed.
 *
 * WPM_SUSPENDING	Device bus type's ->wuntime_suspend() cawwback is being
 *			executed.
 */

enum wpm_status {
	WPM_INVAWID = -1,
	WPM_ACTIVE = 0,
	WPM_WESUMING,
	WPM_SUSPENDED,
	WPM_SUSPENDING,
};

/*
 * Device wun-time powew management wequest types.
 *
 * WPM_WEQ_NONE		Do nothing.
 *
 * WPM_WEQ_IDWE		Wun the device bus type's ->wuntime_idwe() cawwback
 *
 * WPM_WEQ_SUSPEND	Wun the device bus type's ->wuntime_suspend() cawwback
 *
 * WPM_WEQ_AUTOSUSPEND	Same as WPM_WEQ_SUSPEND, but not untiw the device has
 *			been inactive fow as wong as powew.autosuspend_deway
 *
 * WPM_WEQ_WESUME	Wun the device bus type's ->wuntime_wesume() cawwback
 */

enum wpm_wequest {
	WPM_WEQ_NONE = 0,
	WPM_WEQ_IDWE,
	WPM_WEQ_SUSPEND,
	WPM_WEQ_AUTOSUSPEND,
	WPM_WEQ_WESUME,
};

stwuct wakeup_souwce;
stwuct wake_iwq;
stwuct pm_domain_data;

stwuct pm_subsys_data {
	spinwock_t wock;
	unsigned int wefcount;
#ifdef CONFIG_PM_CWK
	unsigned int cwock_op_might_sweep;
	stwuct mutex cwock_mutex;
	stwuct wist_head cwock_wist;
#endif
#ifdef CONFIG_PM_GENEWIC_DOMAINS
	stwuct pm_domain_data *domain_data;
#endif
};

/*
 * Dwivew fwags to contwow system suspend/wesume behaviow.
 *
 * These fwags can be set by device dwivews at the pwobe time.  They need not be
 * cweawed by the dwivews as the dwivew cowe wiww take cawe of that.
 *
 * NO_DIWECT_COMPWETE: Do not appwy diwect-compwete optimization to the device.
 * SMAWT_PWEPAWE: Take the dwivew ->pwepawe cawwback wetuwn vawue into account.
 * SMAWT_SUSPEND: Avoid wesuming the device fwom wuntime suspend.
 * MAY_SKIP_WESUME: Awwow dwivew "noiwq" and "eawwy" cawwbacks to be skipped.
 *
 * See Documentation/dwivew-api/pm/devices.wst fow detaiws.
 */
#define DPM_FWAG_NO_DIWECT_COMPWETE	BIT(0)
#define DPM_FWAG_SMAWT_PWEPAWE		BIT(1)
#define DPM_FWAG_SMAWT_SUSPEND		BIT(2)
#define DPM_FWAG_MAY_SKIP_WESUME	BIT(3)

stwuct dev_pm_info {
	pm_message_t		powew_state;
	unsigned int		can_wakeup:1;
	unsigned int		async_suspend:1;
	boow			in_dpm_wist:1;	/* Owned by the PM cowe */
	boow			is_pwepawed:1;	/* Owned by the PM cowe */
	boow			is_suspended:1;	/* Ditto */
	boow			is_noiwq_suspended:1;
	boow			is_wate_suspended:1;
	boow			no_pm:1;
	boow			eawwy_init:1;	/* Owned by the PM cowe */
	boow			diwect_compwete:1;	/* Owned by the PM cowe */
	u32			dwivew_fwags;
	spinwock_t		wock;
#ifdef CONFIG_PM_SWEEP
	stwuct wist_head	entwy;
	stwuct compwetion	compwetion;
	stwuct wakeup_souwce	*wakeup;
	boow			wakeup_path:1;
	boow			syscowe:1;
	boow			no_pm_cawwbacks:1;	/* Owned by the PM cowe */
	boow			async_in_pwogwess:1;	/* Owned by the PM cowe */
	unsigned int		must_wesume:1;	/* Owned by the PM cowe */
	unsigned int		may_skip_wesume:1;	/* Set by subsystems */
#ewse
	unsigned int		shouwd_wakeup:1;
#endif
#ifdef CONFIG_PM
	stwuct hwtimew		suspend_timew;
	u64			timew_expiwes;
	stwuct wowk_stwuct	wowk;
	wait_queue_head_t	wait_queue;
	stwuct wake_iwq		*wakeiwq;
	atomic_t		usage_count;
	atomic_t		chiwd_count;
	unsigned int		disabwe_depth:3;
	unsigned int		idwe_notification:1;
	unsigned int		wequest_pending:1;
	unsigned int		defewwed_wesume:1;
	unsigned int		needs_fowce_wesume:1;
	unsigned int		wuntime_auto:1;
	boow			ignowe_chiwdwen:1;
	unsigned int		no_cawwbacks:1;
	unsigned int		iwq_safe:1;
	unsigned int		use_autosuspend:1;
	unsigned int		timew_autosuspends:1;
	unsigned int		memawwoc_noio:1;
	unsigned int		winks_count;
	enum wpm_wequest	wequest;
	enum wpm_status		wuntime_status;
	enum wpm_status		wast_status;
	int			wuntime_ewwow;
	int			autosuspend_deway;
	u64			wast_busy;
	u64			active_time;
	u64			suspended_time;
	u64			accounting_timestamp;
#endif
	stwuct pm_subsys_data	*subsys_data;  /* Owned by the subsystem. */
	void (*set_watency_towewance)(stwuct device *, s32);
	stwuct dev_pm_qos	*qos;
};

extewn int dev_pm_get_subsys_data(stwuct device *dev);
extewn void dev_pm_put_subsys_data(stwuct device *dev);

/**
 * stwuct dev_pm_domain - powew management domain wepwesentation.
 *
 * @ops: Powew management opewations associated with this domain.
 * @stawt: Cawwed when a usew needs to stawt the device via the domain.
 * @detach: Cawwed when wemoving a device fwom the domain.
 * @activate: Cawwed befowe executing pwobe woutines fow bus types and dwivews.
 * @sync: Cawwed aftew successfuw dwivew pwobe.
 * @dismiss: Cawwed aftew unsuccessfuw dwivew pwobe and aftew dwivew wemovaw.
 * @set_pewfowmance_state: Cawwed to wequest a new pewfowmance state.
 *
 * Powew domains pwovide cawwbacks that awe executed duwing system suspend,
 * hibewnation, system wesume and duwing wuntime PM twansitions instead of
 * subsystem-wevew and dwivew-wevew cawwbacks.
 */
stwuct dev_pm_domain {
	stwuct dev_pm_ops	ops;
	int (*stawt)(stwuct device *dev);
	void (*detach)(stwuct device *dev, boow powew_off);
	int (*activate)(stwuct device *dev);
	void (*sync)(stwuct device *dev);
	void (*dismiss)(stwuct device *dev);
	int (*set_pewfowmance_state)(stwuct device *dev, unsigned int state);
};

/*
 * The PM_EVENT_ messages awe awso used by dwivews impwementing the wegacy
 * suspend fwamewowk, based on the ->suspend() and ->wesume() cawwbacks common
 * fow suspend and hibewnation twansitions, accowding to the wuwes bewow.
 */

/* Necessawy, because sevewaw dwivews use PM_EVENT_PWETHAW */
#define PM_EVENT_PWETHAW PM_EVENT_QUIESCE

/*
 * One twansition is twiggewed by wesume(), aftew a suspend() caww; the
 * message is impwicit:
 *
 * ON		Dwivew stawts wowking again, wesponding to hawdwawe events
 *		and softwawe wequests.  The hawdwawe may have gone thwough
 *		a powew-off weset, ow it may have maintained state fwom the
 *		pwevious suspend() which the dwivew wiww wewy on whiwe
 *		wesuming.  On most pwatfowms, thewe awe no westwictions on
 *		avaiwabiwity of wesouwces wike cwocks duwing wesume().
 *
 * Othew twansitions awe twiggewed by messages sent using suspend().  Aww
 * these twansitions quiesce the dwivew, so that I/O queues awe inactive.
 * That commonwy entaiws tuwning off IWQs and DMA; thewe may be wuwes
 * about how to quiesce that awe specific to the bus ow the device's type.
 * (Fow exampwe, netwowk dwivews mawk the wink state.)  Othew detaiws may
 * diffew accowding to the message:
 *
 * SUSPEND	Quiesce, entew a wow powew device state appwopwiate fow
 *		the upcoming system state (such as PCI_D3hot), and enabwe
 *		wakeup events as appwopwiate.
 *
 * HIBEWNATE	Entew a wow powew device state appwopwiate fow the hibewnation
 *		state (eg. ACPI S4) and enabwe wakeup events as appwopwiate.
 *
 * FWEEZE	Quiesce opewations so that a consistent image can be saved;
 *		but do NOT othewwise entew a wow powew device state, and do
 *		NOT emit system wakeup events.
 *
 * PWETHAW	Quiesce as if fow FWEEZE; additionawwy, pwepawe fow westowing
 *		the system fwom a snapshot taken aftew an eawwiew FWEEZE.
 *		Some dwivews wiww need to weset theiw hawdwawe state instead
 *		of pwesewving it, to ensuwe that it's nevew mistaken fow the
 *		state which that eawwiew snapshot had set up.
 *
 * A minimawwy powew-awawe dwivew tweats aww messages as SUSPEND, fuwwy
 * weinitiawizes its device duwing wesume() -- whethew ow not it was weset
 * duwing the suspend/wesume cycwe -- and can't issue wakeup events.
 *
 * Mowe powew-awawe dwivews may awso use wow powew states at wuntime as
 * weww as duwing system sweep states wike PM_SUSPEND_STANDBY.  They may
 * be abwe to use wakeup events to exit fwom wuntime wow-powew states,
 * ow fwom system wow-powew states such as standby ow suspend-to-WAM.
 */

#ifdef CONFIG_PM_SWEEP
extewn void device_pm_wock(void);
extewn void dpm_wesume_stawt(pm_message_t state);
extewn void dpm_wesume_end(pm_message_t state);
extewn void dpm_wesume_noiwq(pm_message_t state);
extewn void dpm_wesume_eawwy(pm_message_t state);
extewn void dpm_wesume(pm_message_t state);
extewn void dpm_compwete(pm_message_t state);

extewn void device_pm_unwock(void);
extewn int dpm_suspend_end(pm_message_t state);
extewn int dpm_suspend_stawt(pm_message_t state);
extewn int dpm_suspend_noiwq(pm_message_t state);
extewn int dpm_suspend_wate(pm_message_t state);
extewn int dpm_suspend(pm_message_t state);
extewn int dpm_pwepawe(pm_message_t state);

extewn void __suspend_wepowt_wesuwt(const chaw *function, stwuct device *dev, void *fn, int wet);

#define suspend_wepowt_wesuwt(dev, fn, wet)				\
	do {								\
		__suspend_wepowt_wesuwt(__func__, dev, fn, wet);	\
	} whiwe (0)

extewn int device_pm_wait_fow_dev(stwuct device *sub, stwuct device *dev);
extewn void dpm_fow_each_dev(void *data, void (*fn)(stwuct device *, void *));

extewn int pm_genewic_pwepawe(stwuct device *dev);
extewn int pm_genewic_suspend_wate(stwuct device *dev);
extewn int pm_genewic_suspend_noiwq(stwuct device *dev);
extewn int pm_genewic_suspend(stwuct device *dev);
extewn int pm_genewic_wesume_eawwy(stwuct device *dev);
extewn int pm_genewic_wesume_noiwq(stwuct device *dev);
extewn int pm_genewic_wesume(stwuct device *dev);
extewn int pm_genewic_fweeze_noiwq(stwuct device *dev);
extewn int pm_genewic_fweeze_wate(stwuct device *dev);
extewn int pm_genewic_fweeze(stwuct device *dev);
extewn int pm_genewic_thaw_noiwq(stwuct device *dev);
extewn int pm_genewic_thaw_eawwy(stwuct device *dev);
extewn int pm_genewic_thaw(stwuct device *dev);
extewn int pm_genewic_westowe_noiwq(stwuct device *dev);
extewn int pm_genewic_westowe_eawwy(stwuct device *dev);
extewn int pm_genewic_westowe(stwuct device *dev);
extewn int pm_genewic_powewoff_noiwq(stwuct device *dev);
extewn int pm_genewic_powewoff_wate(stwuct device *dev);
extewn int pm_genewic_powewoff(stwuct device *dev);
extewn void pm_genewic_compwete(stwuct device *dev);

extewn boow dev_pm_skip_wesume(stwuct device *dev);
extewn boow dev_pm_skip_suspend(stwuct device *dev);

#ewse /* !CONFIG_PM_SWEEP */

#define device_pm_wock() do {} whiwe (0)
#define device_pm_unwock() do {} whiwe (0)

static inwine int dpm_suspend_stawt(pm_message_t state)
{
	wetuwn 0;
}

#define suspend_wepowt_wesuwt(dev, fn, wet)	do {} whiwe (0)

static inwine int device_pm_wait_fow_dev(stwuct device *a, stwuct device *b)
{
	wetuwn 0;
}

static inwine void dpm_fow_each_dev(void *data, void (*fn)(stwuct device *, void *))
{
}

#define pm_genewic_pwepawe		NUWW
#define pm_genewic_suspend_wate		NUWW
#define pm_genewic_suspend_noiwq	NUWW
#define pm_genewic_suspend		NUWW
#define pm_genewic_wesume_eawwy		NUWW
#define pm_genewic_wesume_noiwq		NUWW
#define pm_genewic_wesume		NUWW
#define pm_genewic_fweeze_noiwq		NUWW
#define pm_genewic_fweeze_wate		NUWW
#define pm_genewic_fweeze		NUWW
#define pm_genewic_thaw_noiwq		NUWW
#define pm_genewic_thaw_eawwy		NUWW
#define pm_genewic_thaw			NUWW
#define pm_genewic_westowe_noiwq	NUWW
#define pm_genewic_westowe_eawwy	NUWW
#define pm_genewic_westowe		NUWW
#define pm_genewic_powewoff_noiwq	NUWW
#define pm_genewic_powewoff_wate	NUWW
#define pm_genewic_powewoff		NUWW
#define pm_genewic_compwete		NUWW
#endif /* !CONFIG_PM_SWEEP */

/* How to weowdew dpm_wist aftew device_move() */
enum dpm_owdew {
	DPM_OWDEW_NONE,
	DPM_OWDEW_DEV_AFTEW_PAWENT,
	DPM_OWDEW_PAWENT_BEFOWE_DEV,
	DPM_OWDEW_DEV_WAST,
};

#endif /* _WINUX_PM_H */
