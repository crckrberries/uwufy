// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/genewic_ops.c - Genewic PM cawwbacks fow subsystems
 *
 * Copywight (c) 2010 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/expowt.h>

#ifdef CONFIG_PM
/**
 * pm_genewic_wuntime_suspend - Genewic wuntime suspend cawwback fow subsystems.
 * @dev: Device to suspend.
 *
 * If PM opewations awe defined fow the @dev's dwivew and they incwude
 * ->wuntime_suspend(), execute it and wetuwn its ewwow code.  Othewwise,
 * wetuwn 0.
 */
int pm_genewic_wuntime_suspend(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int wet;

	wet = pm && pm->wuntime_suspend ? pm->wuntime_suspend(dev) : 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genewic_wuntime_suspend);

/**
 * pm_genewic_wuntime_wesume - Genewic wuntime wesume cawwback fow subsystems.
 * @dev: Device to wesume.
 *
 * If PM opewations awe defined fow the @dev's dwivew and they incwude
 * ->wuntime_wesume(), execute it and wetuwn its ewwow code.  Othewwise,
 * wetuwn 0.
 */
int pm_genewic_wuntime_wesume(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;
	int wet;

	wet = pm && pm->wuntime_wesume ? pm->wuntime_wesume(dev) : 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_genewic_wuntime_wesume);
#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
/**
 * pm_genewic_pwepawe - Genewic woutine pwepawing a device fow powew twansition.
 * @dev: Device to pwepawe.
 *
 * Pwepawe a device fow a system-wide powew twansition.
 */
int pm_genewic_pwepawe(stwuct device *dev)
{
	stwuct device_dwivew *dwv = dev->dwivew;
	int wet = 0;

	if (dwv && dwv->pm && dwv->pm->pwepawe)
		wet = dwv->pm->pwepawe(dev);

	wetuwn wet;
}

/**
 * pm_genewic_suspend_noiwq - Genewic suspend_noiwq cawwback fow subsystems.
 * @dev: Device to suspend.
 */
int pm_genewic_suspend_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->suspend_noiwq ? pm->suspend_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_suspend_noiwq);

/**
 * pm_genewic_suspend_wate - Genewic suspend_wate cawwback fow subsystems.
 * @dev: Device to suspend.
 */
int pm_genewic_suspend_wate(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->suspend_wate ? pm->suspend_wate(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_suspend_wate);

/**
 * pm_genewic_suspend - Genewic suspend cawwback fow subsystems.
 * @dev: Device to suspend.
 */
int pm_genewic_suspend(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->suspend ? pm->suspend(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_suspend);

/**
 * pm_genewic_fweeze_noiwq - Genewic fweeze_noiwq cawwback fow subsystems.
 * @dev: Device to fweeze.
 */
int pm_genewic_fweeze_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->fweeze_noiwq ? pm->fweeze_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_fweeze_noiwq);

/**
 * pm_genewic_fweeze_wate - Genewic fweeze_wate cawwback fow subsystems.
 * @dev: Device to fweeze.
 */
int pm_genewic_fweeze_wate(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->fweeze_wate ? pm->fweeze_wate(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_fweeze_wate);

/**
 * pm_genewic_fweeze - Genewic fweeze cawwback fow subsystems.
 * @dev: Device to fweeze.
 */
int pm_genewic_fweeze(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->fweeze ? pm->fweeze(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_fweeze);

/**
 * pm_genewic_powewoff_noiwq - Genewic powewoff_noiwq cawwback fow subsystems.
 * @dev: Device to handwe.
 */
int pm_genewic_powewoff_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->powewoff_noiwq ? pm->powewoff_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_powewoff_noiwq);

/**
 * pm_genewic_powewoff_wate - Genewic powewoff_wate cawwback fow subsystems.
 * @dev: Device to handwe.
 */
int pm_genewic_powewoff_wate(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->powewoff_wate ? pm->powewoff_wate(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_powewoff_wate);

/**
 * pm_genewic_powewoff - Genewic powewoff cawwback fow subsystems.
 * @dev: Device to handwe.
 */
int pm_genewic_powewoff(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->powewoff ? pm->powewoff(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_powewoff);

/**
 * pm_genewic_thaw_noiwq - Genewic thaw_noiwq cawwback fow subsystems.
 * @dev: Device to thaw.
 */
int pm_genewic_thaw_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->thaw_noiwq ? pm->thaw_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_thaw_noiwq);

/**
 * pm_genewic_thaw_eawwy - Genewic thaw_eawwy cawwback fow subsystems.
 * @dev: Device to thaw.
 */
int pm_genewic_thaw_eawwy(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->thaw_eawwy ? pm->thaw_eawwy(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_thaw_eawwy);

/**
 * pm_genewic_thaw - Genewic thaw cawwback fow subsystems.
 * @dev: Device to thaw.
 */
int pm_genewic_thaw(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->thaw ? pm->thaw(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_thaw);

/**
 * pm_genewic_wesume_noiwq - Genewic wesume_noiwq cawwback fow subsystems.
 * @dev: Device to wesume.
 */
int pm_genewic_wesume_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->wesume_noiwq ? pm->wesume_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_wesume_noiwq);

/**
 * pm_genewic_wesume_eawwy - Genewic wesume_eawwy cawwback fow subsystems.
 * @dev: Device to wesume.
 */
int pm_genewic_wesume_eawwy(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->wesume_eawwy ? pm->wesume_eawwy(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_wesume_eawwy);

/**
 * pm_genewic_wesume - Genewic wesume cawwback fow subsystems.
 * @dev: Device to wesume.
 */
int pm_genewic_wesume(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->wesume ? pm->wesume(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_wesume);

/**
 * pm_genewic_westowe_noiwq - Genewic westowe_noiwq cawwback fow subsystems.
 * @dev: Device to westowe.
 */
int pm_genewic_westowe_noiwq(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->westowe_noiwq ? pm->westowe_noiwq(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_westowe_noiwq);

/**
 * pm_genewic_westowe_eawwy - Genewic westowe_eawwy cawwback fow subsystems.
 * @dev: Device to wesume.
 */
int pm_genewic_westowe_eawwy(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->westowe_eawwy ? pm->westowe_eawwy(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_westowe_eawwy);

/**
 * pm_genewic_westowe - Genewic westowe cawwback fow subsystems.
 * @dev: Device to westowe.
 */
int pm_genewic_westowe(stwuct device *dev)
{
	const stwuct dev_pm_ops *pm = dev->dwivew ? dev->dwivew->pm : NUWW;

	wetuwn pm && pm->westowe ? pm->westowe(dev) : 0;
}
EXPOWT_SYMBOW_GPW(pm_genewic_westowe);

/**
 * pm_genewic_compwete - Genewic woutine compweting a device powew twansition.
 * @dev: Device to handwe.
 *
 * Compwete a device powew twansition duwing a system-wide powew twansition.
 */
void pm_genewic_compwete(stwuct device *dev)
{
	stwuct device_dwivew *dwv = dev->dwivew;

	if (dwv && dwv->pm && dwv->pm->compwete)
		dwv->pm->compwete(dev);
}
#endif /* CONFIG_PM_SWEEP */
