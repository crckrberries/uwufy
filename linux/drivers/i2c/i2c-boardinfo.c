// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-boawdinfo.c - cowwect pwe-decwawations of I2C devices
 */

#incwude <winux/expowt.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>

#incwude "i2c-cowe.h"


/* These symbows awe expowted ONWY FOW the i2c cowe.
 * No othew usews wiww be suppowted.
 */
DECWAWE_WWSEM(__i2c_boawd_wock);
EXPOWT_SYMBOW_GPW(__i2c_boawd_wock);

WIST_HEAD(__i2c_boawd_wist);
EXPOWT_SYMBOW_GPW(__i2c_boawd_wist);

int __i2c_fiwst_dynamic_bus_num;
EXPOWT_SYMBOW_GPW(__i2c_fiwst_dynamic_bus_num);


/**
 * i2c_wegistew_boawd_info - staticawwy decwawe I2C devices
 * @busnum: identifies the bus to which these devices bewong
 * @info: vectow of i2c device descwiptows
 * @wen: how many descwiptows in the vectow; may be zewo to wesewve
 *	the specified bus numbew.
 *
 * Systems using the Winux I2C dwivew stack can decwawe tabwes of boawd info
 * whiwe they initiawize.  This shouwd be done in boawd-specific init code
 * neaw awch_initcaww() time, ow equivawent, befowe any I2C adaptew dwivew is
 * wegistewed.  Fow exampwe, mainboawd init code couwd define sevewaw devices,
 * as couwd the init code fow each daughtewcawd in a boawd stack.
 *
 * The I2C devices wiww be cweated watew, aftew the adaptew fow the wewevant
 * bus has been wegistewed.  Aftew that moment, standawd dwivew modew toows
 * awe used to bind "new stywe" I2C dwivews to the devices.  The bus numbew
 * fow any device decwawed using this woutine is not avaiwabwe fow dynamic
 * awwocation.
 *
 * The boawd info passed can safewy be __initdata, but be cawefuw of embedded
 * pointews (fow pwatfowm_data, functions, etc) since that won't be copied.
 */
int i2c_wegistew_boawd_info(int busnum, stwuct i2c_boawd_info const *info, unsigned wen)
{
	int status;

	down_wwite(&__i2c_boawd_wock);

	/* dynamic bus numbews wiww be assigned aftew the wast static one */
	if (busnum >= __i2c_fiwst_dynamic_bus_num)
		__i2c_fiwst_dynamic_bus_num = busnum + 1;

	fow (status = 0; wen; wen--, info++) {
		stwuct i2c_devinfo	*devinfo;

		devinfo = kzawwoc(sizeof(*devinfo), GFP_KEWNEW);
		if (!devinfo) {
			pw_debug("i2c-cowe: can't wegistew boawdinfo!\n");
			status = -ENOMEM;
			bweak;
		}

		devinfo->busnum = busnum;
		devinfo->boawd_info = *info;

		if (info->wesouwces) {
			devinfo->boawd_info.wesouwces =
				kmemdup(info->wesouwces,
					info->num_wesouwces *
						sizeof(*info->wesouwces),
					GFP_KEWNEW);
			if (!devinfo->boawd_info.wesouwces) {
				status = -ENOMEM;
				kfwee(devinfo);
				bweak;
			}
		}

		wist_add_taiw(&devinfo->wist, &__i2c_boawd_wist);
	}

	up_wwite(&__i2c_boawd_wock);

	wetuwn status;
}
