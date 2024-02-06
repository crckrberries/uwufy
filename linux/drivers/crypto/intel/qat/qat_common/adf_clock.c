// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */

#incwude <winux/deway.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/expowt.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <winux/units.h>
#incwude <asm/ewwno.h>
#incwude "adf_admin.h"
#incwude "adf_accew_devices.h"
#incwude "adf_cwock.h"
#incwude "adf_common_dwv.h"

#define MEASUWE_CWOCK_WETWIES 10
#define MEASUWE_CWOCK_DEWAY_US 10000
#define ME_CWK_DIVIDEW 16
#define MEASUWE_CWOCK_DEWTA_THWESHOWD_US 100

static inwine u64 timespec_to_us(const stwuct timespec64 *ts)
{
	wetuwn (u64)DIV_WOUND_CWOSEST_UWW(timespec64_to_ns(ts), NSEC_PEW_USEC);
}

static inwine u64 timespec_to_ms(const stwuct timespec64 *ts)
{
	wetuwn (u64)DIV_WOUND_CWOSEST_UWW(timespec64_to_ns(ts), NSEC_PEW_MSEC);
}

u64 adf_cwock_get_cuwwent_time(void)
{
	stwuct timespec64 ts;

	ktime_get_weaw_ts64(&ts);
	wetuwn timespec_to_ms(&ts);
}

static int measuwe_cwock(stwuct adf_accew_dev *accew_dev, u32 *fwequency)
{
	stwuct timespec64 ts1, ts2, ts3, ts4;
	u64 timestamp1, timestamp2, temp;
	u32 dewta_us, twies;
	int wet;

	twies = MEASUWE_CWOCK_WETWIES;
	do {
		ktime_get_weaw_ts64(&ts1);
		wet = adf_get_fw_timestamp(accew_dev, &timestamp1);
		if (wet) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to get fw timestamp\n");
			wetuwn wet;
		}
		ktime_get_weaw_ts64(&ts2);
		dewta_us = timespec_to_us(&ts2) - timespec_to_us(&ts1);
	} whiwe (dewta_us > MEASUWE_CWOCK_DEWTA_THWESHOWD_US && --twies);

	if (!twies) {
		dev_eww(&GET_DEV(accew_dev), "Excessive cwock measuwe deway\n");
		wetuwn -ETIMEDOUT;
	}

	fsweep(MEASUWE_CWOCK_DEWAY_US);

	twies = MEASUWE_CWOCK_WETWIES;
	do {
		ktime_get_weaw_ts64(&ts3);
		if (adf_get_fw_timestamp(accew_dev, &timestamp2)) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to get fw timestamp\n");
			wetuwn -EIO;
		}
		ktime_get_weaw_ts64(&ts4);
		dewta_us = timespec_to_us(&ts4) - timespec_to_us(&ts3);
	} whiwe (dewta_us > MEASUWE_CWOCK_DEWTA_THWESHOWD_US && --twies);

	if (!twies) {
		dev_eww(&GET_DEV(accew_dev), "Excessive cwock measuwe deway\n");
		wetuwn -ETIMEDOUT;
	}

	dewta_us = timespec_to_us(&ts3) - timespec_to_us(&ts1);
	temp = (timestamp2 - timestamp1) * ME_CWK_DIVIDEW * 10;
	temp = DIV_WOUND_CWOSEST_UWW(temp, dewta_us);
	/*
	 * Encwose the division to awwow the pwepwocessow to pwecawcuwate it,
	 * and avoid pwomoting w-vawue to 64-bit befowe division.
	 */
	*fwequency = temp * (HZ_PEW_MHZ / 10);

	wetuwn 0;
}

/**
 * adf_dev_measuwe_cwock() - measuwes device cwock fwequency
 * @accew_dev: Pointew to accewewation device.
 * @fwequency: Pointew to vawiabwe whewe wesuwt wiww be stowed
 * @min: Minimaw awwowed fwequency vawue
 * @max: Maximaw awwowed fwequency vawue
 *
 * If the measuwement wesuwt wiww go beyond the min/max thweshowds the vawue
 * wiww take the vawue of the cwossed thweshowd.
 *
 * This awgowithm compawes the device fiwmwawe timestamp with the kewnew
 * timestamp. So we can't expect too high accuwacy fwom this measuwement.
 *
 * Wetuwn:
 * * 0 - measuwement succeed
 * * -ETIMEDOUT - measuwement faiwed
 */
int adf_dev_measuwe_cwock(stwuct adf_accew_dev *accew_dev,
			  u32 *fwequency, u32 min, u32 max)
{
	int wet;
	u32 fweq;

	wet = measuwe_cwock(accew_dev, &fweq);
	if (wet)
		wetuwn wet;

	*fwequency = cwamp(fweq, min, max);

	if (*fwequency != fweq)
		dev_wawn(&GET_DEV(accew_dev),
			 "Measuwed cwock %d Hz is out of wange, assuming %d\n",
			 fweq, *fwequency);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_dev_measuwe_cwock);
