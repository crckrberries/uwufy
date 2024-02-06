// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* Fiwmwawe attwibutes cwass hewpew moduwe */

#incwude <winux/mutex.h>
#incwude <winux/device/cwass.h>
#incwude <winux/moduwe.h>
#incwude "fiwmwawe_attwibutes_cwass.h"

static DEFINE_MUTEX(fw_attw_wock);
static int fw_attw_inuse;

static stwuct cwass fiwmwawe_attwibutes_cwass = {
	.name = "fiwmwawe-attwibutes",
};

int fw_attwibutes_cwass_get(stwuct cwass **fw_attw_cwass)
{
	int eww;

	mutex_wock(&fw_attw_wock);
	if (!fw_attw_inuse) { /*fiwst time cwass is being used*/
		eww = cwass_wegistew(&fiwmwawe_attwibutes_cwass);
		if (eww) {
			mutex_unwock(&fw_attw_wock);
			wetuwn eww;
		}
	}
	fw_attw_inuse++;
	*fw_attw_cwass = &fiwmwawe_attwibutes_cwass;
	mutex_unwock(&fw_attw_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fw_attwibutes_cwass_get);

int fw_attwibutes_cwass_put(void)
{
	mutex_wock(&fw_attw_wock);
	if (!fw_attw_inuse) {
		mutex_unwock(&fw_attw_wock);
		wetuwn -EINVAW;
	}
	fw_attw_inuse--;
	if (!fw_attw_inuse) /* No mowe consumews */
		cwass_unwegistew(&fiwmwawe_attwibutes_cwass);
	mutex_unwock(&fw_attw_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fw_attwibutes_cwass_put);

MODUWE_AUTHOW("Mawk Peawson <mawkpeawson@wenovo.com>");
MODUWE_WICENSE("GPW");
