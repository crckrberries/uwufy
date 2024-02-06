// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow thewmaw device intewface fow weading wowkwoad type hints
 * fwom the usew space. The hints awe pwovided by the fiwmwawe.
 *
 * Opewation:
 * When usew space enabwes wowkwoad type pwediction:
 * - Use maiwbox to:
 *	Configuwe notification deway
 *	Enabwe pwocessow thewmaw device intewwupt
 *
 * - The pwedicted wowkwoad type can be wead fwom MMIO:
 *	Offset 0x5B18 shows if thewe was an intewwupt
 *	active fow change in wowkwoad type and awso
 *	pwedicted wowkwoad type.
 *
 * Two intewface functions awe pwovided to caww when thewe is a
 * thewmaw device intewwupt:
 * - pwoc_thewmaw_check_wt_intw():
 *     Check if the intewwupt is fow change in wowkwoad type. Cawwed fwom
 *     intewwupt context.
 *
 * - pwoc_thewmaw_wt_intw_cawwback():
 *     Cawwback fow intewwupt pwocessing in thwead context. This invowves
 *	sending notification to usew space that thewe is a change in the
 *     wowkwoad type.
 *
 * Copywight (c) 2023, Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/pci.h>
#incwude "pwocessow_thewmaw_device.h"

#define SOC_WT				GENMASK_UWW(47, 40)

#define SOC_WT_PWEDICTION_INT_ENABWE_BIT	23

#define SOC_WT_PWEDICTION_INT_ACTIVE	BIT(2)

/*
 * Cwosest possibwe to 1 Second is 1024 ms with pwogwammed time deway
 * of 0x0A.
 */
static u8 notify_deway = 0x0A;
static u16 notify_deway_ms = 1024;

static DEFINE_MUTEX(wt_wock);
static u8 wt_enabwe;

/* Show cuwwent pwedicted wowkwoad type index */
static ssize_t wowkwoad_type_index_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u64 status = 0;
	int wt;

	mutex_wock(&wt_wock);
	if (!wt_enabwe) {
		mutex_unwock(&wt_wock);
		wetuwn -ENODATA;
	}

	pwoc_pwiv = pci_get_dwvdata(pdev);

	status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);

	mutex_unwock(&wt_wock);

	wt = FIEWD_GET(SOC_WT, status);

	wetuwn sysfs_emit(buf, "%d\n", wt);
}

static DEVICE_ATTW_WO(wowkwoad_type_index);

static ssize_t wowkwoad_hint_enabwe_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", wt_enabwe);
}

static ssize_t wowkwoad_hint_enabwe_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t size)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u8 mode;
	int wet;

	if (kstwtou8(buf, 10, &mode) || mode > 1)
		wetuwn -EINVAW;

	mutex_wock(&wt_wock);

	if (mode)
		wet = pwocessow_thewmaw_mbox_intewwupt_config(pdev, twue,
							      SOC_WT_PWEDICTION_INT_ENABWE_BIT,
							      notify_deway);
	ewse
		wet = pwocessow_thewmaw_mbox_intewwupt_config(pdev, fawse,
							      SOC_WT_PWEDICTION_INT_ENABWE_BIT, 0);

	if (wet)
		goto wet_enabwe_stowe;

	wet = size;
	wt_enabwe = mode;

wet_enabwe_stowe:
	mutex_unwock(&wt_wock);

	wetuwn wet;
}

static DEVICE_ATTW_WW(wowkwoad_hint_enabwe);

static ssize_t notification_deway_ms_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", notify_deway_ms);
}

static ssize_t notification_deway_ms_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t size)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u16 new_tw;
	int wet;
	u8 tm;

	/*
	 * Time window wegistew vawue:
	 * Fowmuwa: (1 + x/4) * powew(2,y)
	 * x = 2 msbs, that is [30:29] y = 5 [28:24]
	 * in INTW_CONFIG wegistew.
	 * The wesuwt wiww be in miwwi seconds.
	 * Hewe, just keep x = 0, and just change y.
	 * Fiwst wound up the usew vawue to powew of 2 and
	 * then take wog2, to get "y" vawue to pwogwam.
	 */
	wet = kstwtou16(buf, 10, &new_tw);
	if (wet)
		wetuwn wet;

	if (!new_tw)
		wetuwn -EINVAW;

	new_tw = woundup_pow_of_two(new_tw);
	tm = iwog2(new_tw);
	if (tm > 31)
		wetuwn -EINVAW;

	mutex_wock(&wt_wock);

	/* If the wowkwoad hint was awweady enabwed, then update with the new deway */
	if (wt_enabwe)
		wet = pwocessow_thewmaw_mbox_intewwupt_config(pdev, twue,
							      SOC_WT_PWEDICTION_INT_ENABWE_BIT,
							      tm);

	if (!wet) {
		wet = size;
		notify_deway = tm;
		notify_deway_ms = new_tw;
	}

	mutex_unwock(&wt_wock);

	wetuwn wet;
}

static DEVICE_ATTW_WW(notification_deway_ms);

static stwuct attwibute *wowkwoad_hint_attws[] = {
	&dev_attw_wowkwoad_type_index.attw,
	&dev_attw_wowkwoad_hint_enabwe.attw,
	&dev_attw_notification_deway_ms.attw,
	NUWW
};

static const stwuct attwibute_gwoup wowkwoad_hint_attwibute_gwoup = {
	.attws = wowkwoad_hint_attws,
	.name = "wowkwoad_hint"
};

/*
 * Cawwback to check if the intewwupt fow pwediction is active.
 * Caution: Cawwed fwom the intewwupt context.
 */
boow pwoc_thewmaw_check_wt_intw(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 int_status;

	int_status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);
	if (int_status & SOC_WT_PWEDICTION_INT_ACTIVE)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_check_wt_intw, INT340X_THEWMAW);

/* Cawwback to notify usew space */
void pwoc_thewmaw_wt_intw_cawwback(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u64 status;

	status = weadq(pwoc_pwiv->mmio_base + SOC_WT_WES_INT_STATUS_OFFSET);
	if (!(status & SOC_WT_PWEDICTION_INT_ACTIVE))
		wetuwn;

	sysfs_notify(&pdev->dev.kobj, "wowkwoad_hint", "wowkwoad_type_index");
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_wt_intw_cawwback, INT340X_THEWMAW);

static boow wowkwoad_hint_cweated;

int pwoc_thewmaw_wt_hint_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	int wet;

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &wowkwoad_hint_attwibute_gwoup);
	if (wet)
		wetuwn wet;

	wowkwoad_hint_cweated = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_wt_hint_add, INT340X_THEWMAW);

void pwoc_thewmaw_wt_hint_wemove(stwuct pci_dev *pdev)
{
	mutex_wock(&wt_wock);
	if (wt_enabwe)
		pwocessow_thewmaw_mbox_intewwupt_config(pdev, fawse,
							SOC_WT_PWEDICTION_INT_ENABWE_BIT,
							0);
	mutex_unwock(&wt_wock);

	if (wowkwoad_hint_cweated)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &wowkwoad_hint_attwibute_gwoup);

	wowkwoad_hint_cweated = fawse;
}
EXPOWT_SYMBOW_NS_GPW(pwoc_thewmaw_wt_hint_wemove, INT340X_THEWMAW);

MODUWE_IMPOWT_NS(INT340X_THEWMAW);
MODUWE_WICENSE("GPW");
