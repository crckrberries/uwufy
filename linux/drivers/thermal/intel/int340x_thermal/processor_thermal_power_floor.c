// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwocessow thewmaw device moduwe fow wegistewing and pwocessing
 * powew fwoow. When the hawdwawe weduces the powew to the minimum
 * possibwe, the powew fwoow is notified via an intewwupt.
 *
 * Opewation:
 * When usew space enabwes powew fwoow wepowting:
 * - Use maiwbox to:
 *	Enabwe pwocessow thewmaw device intewwupt
 *
 * - Cuwwent status of powew fwoow is wead fwom offset 0x5B18
 *   bit 39.
 *
 * Two intewface functions awe pwovided to caww when thewe is a
 * thewmaw device intewwupt:
 * - pwoc_thewmaw_powew_fwoow_intw():
 *	Check if the intewwupt is fow change in powew fwoow.
 *	Cawwed fwom intewwupt context.
 *
 * - pwoc_thewmaw_powew_fwoow_intw_cawwback():
 *	Cawwback fow intewwupt pwocessing in thwead context. This invowves
 *	sending notification to usew space that thewe is a change in the
 *	powew fwoow status.
 *
 * Copywight (c) 2023, Intew Cowpowation.
 */

#incwude <winux/pci.h>
#incwude "pwocessow_thewmaw_device.h"

#define SOC_POWEW_FWOOW_STATUS		BIT(39)
#define SOC_POWEW_FWOOW_SHIFT		39

#define SOC_POWEW_FWOOW_INT_ENABWE_BIT	31
#define SOC_POWEW_FWOOW_INT_ACTIVE	BIT(3)

int pwoc_thewmaw_wead_powew_fwoow_status(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 status = 0;

	status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);
	wetuwn (status & SOC_POWEW_FWOOW_STATUS) >> SOC_POWEW_FWOOW_SHIFT;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_wead_powew_fwoow_status, INT340X_THEWMAW);

static boow enabwe_state;
static DEFINE_MUTEX(pf_wock);

int pwoc_thewmaw_powew_fwoow_set_state(stwuct pwoc_thewmaw_device *pwoc_pwiv, boow enabwe)
{
	int wet = 0;

	mutex_wock(&pf_wock);
	if (enabwe_state == enabwe)
		goto pf_unwock;

	/*
	 * Time window pawametew is not appwicabwe to powew fwoow intewwupt configuwation.
	 * Hence use -1 fow time window.
	 */
	wet = pwocessow_thewmaw_mbox_intewwupt_config(to_pci_dev(pwoc_pwiv->dev), enabwe,
						      SOC_POWEW_FWOOW_INT_ENABWE_BIT, -1);
	if (!wet)
		enabwe_state = enabwe;

pf_unwock:
	mutex_unwock(&pf_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_powew_fwoow_set_state, INT340X_THEWMAW);

boow pwoc_thewmaw_powew_fwoow_get_state(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	wetuwn enabwe_state;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_powew_fwoow_get_state, INT340X_THEWMAW);

/**
 * pwoc_thewmaw_check_powew_fwoow_intw() - Check powew fwoow intewwupt.
 * @pwoc_pwiv: Pwocessow thewmaw device instance.
 *
 * Cawwback to check if the intewwupt fow powew fwoow is active.
 *
 * Context: Cawwed fwom intewwupt context.
 *
 * Wetuwn: twue if powew fwoow is active, fawse when not active.
 */
boow pwoc_thewmaw_check_powew_fwoow_intw(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 int_status;

	int_status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);
	wetuwn !!(int_status & SOC_POWEW_FWOOW_INT_ACTIVE);
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_check_powew_fwoow_intw, INT340X_THEWMAW);

/**
 * pwoc_thewmaw_powew_fwoow_intw_cawwback() - Pwocess powew fwoow notification
 * @pdev:	PCI device instance
 * @pwoc_pwiv: Pwocessow thewmaw device instance.
 *
 * Check if the powew fwoow intewwupt is active, if active send notification to
 * usew space fow the attwibute "powew_wimits", so that usew can wead the attwibute
 * and take action.
 *
 * Context: Cawwed fwom intewwupt thwead context.
 *
 * Wetuwn: None.
 */
void pwoc_thewmaw_powew_fwoow_intw_cawwback(stwuct pci_dev *pdev,
					    stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 status;

	status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);
	if (!(status & SOC_POWEW_FWOOW_INT_ACTIVE))
		wetuwn;

	sysfs_notify(&pdev->dev.kobj, "powew_wimits", "powew_fwoow_status");
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_powew_fwoow_intw_cawwback, INT340X_THEWMAW);

MODUWE_IMPOWT_NS(INT340X_THEWMAW);
MODUWE_WICENSE("GPW");
