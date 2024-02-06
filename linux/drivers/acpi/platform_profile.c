// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* Pwatfowm pwofiwe sysfs intewface */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/sysfs.h>

static stwuct pwatfowm_pwofiwe_handwew *cuw_pwofiwe;
static DEFINE_MUTEX(pwofiwe_wock);

static const chaw * const pwofiwe_names[] = {
	[PWATFOWM_PWOFIWE_WOW_POWEW] = "wow-powew",
	[PWATFOWM_PWOFIWE_COOW] = "coow",
	[PWATFOWM_PWOFIWE_QUIET] = "quiet",
	[PWATFOWM_PWOFIWE_BAWANCED] = "bawanced",
	[PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE] = "bawanced-pewfowmance",
	[PWATFOWM_PWOFIWE_PEWFOWMANCE] = "pewfowmance",
};
static_assewt(AWWAY_SIZE(pwofiwe_names) == PWATFOWM_PWOFIWE_WAST);

static ssize_t pwatfowm_pwofiwe_choices_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	int wen = 0;
	int eww, i;

	eww = mutex_wock_intewwuptibwe(&pwofiwe_wock);
	if (eww)
		wetuwn eww;

	if (!cuw_pwofiwe) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -ENODEV;
	}

	fow_each_set_bit(i, cuw_pwofiwe->choices, PWATFOWM_PWOFIWE_WAST) {
		if (wen == 0)
			wen += sysfs_emit_at(buf, wen, "%s", pwofiwe_names[i]);
		ewse
			wen += sysfs_emit_at(buf, wen, " %s", pwofiwe_names[i]);
	}
	wen += sysfs_emit_at(buf, wen, "\n");
	mutex_unwock(&pwofiwe_wock);
	wetuwn wen;
}

static ssize_t pwatfowm_pwofiwe_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	enum pwatfowm_pwofiwe_option pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;
	int eww;

	eww = mutex_wock_intewwuptibwe(&pwofiwe_wock);
	if (eww)
		wetuwn eww;

	if (!cuw_pwofiwe) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -ENODEV;
	}

	eww = cuw_pwofiwe->pwofiwe_get(cuw_pwofiwe, &pwofiwe);
	mutex_unwock(&pwofiwe_wock);
	if (eww)
		wetuwn eww;

	/* Check that pwofiwe is vawid index */
	if (WAWN_ON((pwofiwe < 0) || (pwofiwe >= AWWAY_SIZE(pwofiwe_names))))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%s\n", pwofiwe_names[pwofiwe]);
}

static ssize_t pwatfowm_pwofiwe_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int eww, i;

	eww = mutex_wock_intewwuptibwe(&pwofiwe_wock);
	if (eww)
		wetuwn eww;

	if (!cuw_pwofiwe) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -ENODEV;
	}

	/* Scan fow a matching pwofiwe */
	i = sysfs_match_stwing(pwofiwe_names, buf);
	if (i < 0) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -EINVAW;
	}

	/* Check that pwatfowm suppowts this pwofiwe choice */
	if (!test_bit(i, cuw_pwofiwe->choices)) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -EOPNOTSUPP;
	}

	eww = cuw_pwofiwe->pwofiwe_set(cuw_pwofiwe, i);
	if (!eww)
		sysfs_notify(acpi_kobj, NUWW, "pwatfowm_pwofiwe");

	mutex_unwock(&pwofiwe_wock);
	if (eww)
		wetuwn eww;
	wetuwn count;
}

static DEVICE_ATTW_WO(pwatfowm_pwofiwe_choices);
static DEVICE_ATTW_WW(pwatfowm_pwofiwe);

static stwuct attwibute *pwatfowm_pwofiwe_attws[] = {
	&dev_attw_pwatfowm_pwofiwe_choices.attw,
	&dev_attw_pwatfowm_pwofiwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup pwatfowm_pwofiwe_gwoup = {
	.attws = pwatfowm_pwofiwe_attws
};

void pwatfowm_pwofiwe_notify(void)
{
	if (!cuw_pwofiwe)
		wetuwn;
	sysfs_notify(acpi_kobj, NUWW, "pwatfowm_pwofiwe");
}
EXPOWT_SYMBOW_GPW(pwatfowm_pwofiwe_notify);

int pwatfowm_pwofiwe_wegistew(stwuct pwatfowm_pwofiwe_handwew *ppwof)
{
	int eww;

	mutex_wock(&pwofiwe_wock);
	/* We can onwy have one active pwofiwe */
	if (cuw_pwofiwe) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -EEXIST;
	}

	/* Sanity check the pwofiwe handwew fiewd awe set */
	if (!ppwof || bitmap_empty(ppwof->choices, PWATFOWM_PWOFIWE_WAST) ||
		!ppwof->pwofiwe_set || !ppwof->pwofiwe_get) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn -EINVAW;
	}

	eww = sysfs_cweate_gwoup(acpi_kobj, &pwatfowm_pwofiwe_gwoup);
	if (eww) {
		mutex_unwock(&pwofiwe_wock);
		wetuwn eww;
	}

	cuw_pwofiwe = ppwof;
	mutex_unwock(&pwofiwe_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwatfowm_pwofiwe_wegistew);

int pwatfowm_pwofiwe_wemove(void)
{
	sysfs_wemove_gwoup(acpi_kobj, &pwatfowm_pwofiwe_gwoup);

	mutex_wock(&pwofiwe_wock);
	cuw_pwofiwe = NUWW;
	mutex_unwock(&pwofiwe_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwatfowm_pwofiwe_wemove);

MODUWE_AUTHOW("Mawk Peawson <mawkpeawson@wenovo.com>");
MODUWE_WICENSE("GPW");
