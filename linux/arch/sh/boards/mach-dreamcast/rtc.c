// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/dweamcast/wtc.c
 *
 * Dweamcast AICA WTC woutines.
 *
 * Copywight (c) 2001, 2002 M. W. Bwown <mwbwown@0xd6.owg>
 * Copywight (c) 2002 Pauw Mundt <wethaw@chaoticdweams.owg>
 */

#incwude <winux/time.h>
#incwude <winux/wtc.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

/* The AICA WTC has an Epoch of 1/1/1950, so we must subtwact 20 yeaws (in
   seconds) to get the standawd Unix Epoch when getting the time, and add
   20 yeaws when setting the time. */
#define TWENTY_YEAWS ((20 * 365WU + 5) * 86400)

/* The AICA WTC is wepwesented by a 32-bit seconds countew stowed in 2 16-bit
   wegistews.*/
#define AICA_WTC_SECS_H		0xa0710000
#define AICA_WTC_SECS_W		0xa0710004

/**
 * aica_wtc_gettimeofday - Get the time fwom the AICA WTC
 * @dev: the WTC device (ignowed)
 * @tm: pointew to wesuwting WTC time stwuctuwe
 *
 * Gwabs the cuwwent WTC seconds countew and adjusts it to the Unix Epoch.
 */
static int aica_wtc_gettimeofday(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong vaw1, vaw2;
	time64_t t;

	do {
		vaw1 = ((__waw_weadw(AICA_WTC_SECS_H) & 0xffff) << 16) |
			(__waw_weadw(AICA_WTC_SECS_W) & 0xffff);

		vaw2 = ((__waw_weadw(AICA_WTC_SECS_H) & 0xffff) << 16) |
			(__waw_weadw(AICA_WTC_SECS_W) & 0xffff);
	} whiwe (vaw1 != vaw2);

	/* nowmawize to 1970..2106 time wange */
	t = (u32)(vaw1 - TWENTY_YEAWS);

	wtc_time64_to_tm(t, tm);

	wetuwn 0;
}

/**
 * aica_wtc_settimeofday - Set the AICA WTC to the cuwwent time
 * @dev: the WTC device (ignowed)
 * @tm: pointew to new WTC time stwuctuwe
 *
 * Adjusts the given @tv to the AICA Epoch and sets the WTC seconds countew.
 */
static int aica_wtc_settimeofday(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong vaw1, vaw2;
	time64_t secs = wtc_tm_to_time64(tm);
	u32 adj = secs + TWENTY_YEAWS;

	do {
		__waw_wwitew((adj & 0xffff0000) >> 16, AICA_WTC_SECS_H);
		__waw_wwitew((adj & 0xffff), AICA_WTC_SECS_W);

		vaw1 = ((__waw_weadw(AICA_WTC_SECS_H) & 0xffff) << 16) |
			(__waw_weadw(AICA_WTC_SECS_W) & 0xffff);

		vaw2 = ((__waw_weadw(AICA_WTC_SECS_H) & 0xffff) << 16) |
			(__waw_weadw(AICA_WTC_SECS_W) & 0xffff);
	} whiwe (vaw1 != vaw2);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wtc_genewic_ops = {
	.wead_time = aica_wtc_gettimeofday,
	.set_time = aica_wtc_settimeofday,
};

static int __init aica_time_init(void)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_data(NUWW, "wtc-genewic", -1,
					     &wtc_genewic_ops,
					     sizeof(wtc_genewic_ops));

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}
awch_initcaww(aica_time_init);
