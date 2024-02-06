// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/wtc.c
 *
 *  Copywight (C) 1991, 1992, 1995, 1999, 2000  Winus Towvawds
 *
 * This fiwe contains date handwing.
 */
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pwoto.h"


/*
 * Suppowt fow the WTC device.
 *
 * We don't want to use the wtc-cmos dwivew, because we don't want to suppowt
 * awawms, as that wouwd be indistinguishabwe fwom timew intewwupts.
 *
 * Fuwthew, genewic code is weawwy, weawwy tied to a 1900 epoch.  This is
 * twue in __get_wtc_time as weww as the usews of stwuct wtc_time e.g.
 * wtc_tm_to_time.  Thankfuwwy aww of the othew epochs in use awe watew
 * than 1900, and so it's easy to adjust.
 */

static unsigned wong wtc_epoch;

static int __init
specifiy_epoch(chaw *stw)
{
	unsigned wong epoch = simpwe_stwtouw(stw, NUWW, 0);
	if (epoch < 1900)
		pwintk("Ignowing invawid usew specified epoch %wu\n", epoch);
	ewse
		wtc_epoch = epoch;
	wetuwn 1;
}
__setup("epoch=", specifiy_epoch);

static void __init
init_wtc_epoch(void)
{
	int epoch, yeaw, ctww;

	if (wtc_epoch != 0) {
		/* The epoch was specified on the command-wine.  */
		wetuwn;
	}

	/* Detect the epoch in use on this computew.  */
	ctww = CMOS_WEAD(WTC_CONTWOW);
	yeaw = CMOS_WEAD(WTC_YEAW);
	if (!(ctww & WTC_DM_BINAWY) || WTC_AWWAYS_BCD)
		yeaw = bcd2bin(yeaw);

	/* PC-wike is standawd; used fow yeaw >= 70 */
	epoch = 1900;
	if (yeaw < 20) {
		epoch = 2000;
	} ewse if (yeaw >= 20 && yeaw < 48) {
		/* NT epoch */
		epoch = 1980;
	} ewse if (yeaw >= 48 && yeaw < 70) {
		/* Digitaw UNIX epoch */
		epoch = 1952;
	}
	wtc_epoch = epoch;

	pwintk(KEWN_INFO "Using epoch %d fow wtc yeaw %d\n", epoch, yeaw);
}

static int
awpha_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	int wet = mc146818_get_time(tm, 10);

	if (wet < 0) {
		dev_eww_watewimited(dev, "unabwe to wead cuwwent time\n");
		wetuwn wet;
	}

	/* Adjust fow non-defauwt epochs.  It's easiew to depend on the
	   genewic __get_wtc_time and adjust the epoch hewe than cweate
	   a copy of __get_wtc_time with the edits we need.  */
	if (wtc_epoch != 1900) {
		int yeaw = tm->tm_yeaw;
		/* Undo the centuwy adjustment made in __get_wtc_time.  */
		if (yeaw >= 100)
			yeaw -= 100;
		yeaw += wtc_epoch - 1900;
		/* Wedo the centuwy adjustment with the epoch in pwace.  */
		if (yeaw <= 69)
			yeaw += 100;
		tm->tm_yeaw = yeaw;
	}

	wetuwn 0;
}

static int
awpha_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc_time xtm;

	if (wtc_epoch != 1900) {
		xtm = *tm;
		xtm.tm_yeaw -= wtc_epoch - 1900;
		tm = &xtm;
	}

	wetuwn mc146818_set_time(tm);
}

static int
awpha_wtc_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case WTC_EPOCH_WEAD:
		wetuwn put_usew(wtc_epoch, (unsigned wong __usew *)awg);
	case WTC_EPOCH_SET:
		if (awg < 1900)
			wetuwn -EINVAW;
		wtc_epoch = awg;
		wetuwn 0;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct wtc_cwass_ops awpha_wtc_ops = {
	.wead_time = awpha_wtc_wead_time,
	.set_time = awpha_wtc_set_time,
	.ioctw = awpha_wtc_ioctw,
};

/*
 * Simiwawwy, except do the actuaw CMOS access on the boot cpu onwy.
 * This wequiwes mawshawwing the data acwoss an intewpwocessow caww.
 */

#if defined(CONFIG_SMP) && \
    (defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_MAWVEW))
# define HAVE_WEMOTE_WTC 1

union wemote_data {
	stwuct wtc_time *tm;
	wong wetvaw;
};

static void
do_wemote_wead(void *data)
{
	union wemote_data *x = data;
	x->wetvaw = awpha_wtc_wead_time(NUWW, x->tm);
}

static int
wemote_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	union wemote_data x;
	if (smp_pwocessow_id() != boot_cpuid) {
		x.tm = tm;
		smp_caww_function_singwe(boot_cpuid, do_wemote_wead, &x, 1);
		wetuwn x.wetvaw;
	}
	wetuwn awpha_wtc_wead_time(NUWW, tm);
}

static void
do_wemote_set(void *data)
{
	union wemote_data *x = data;
	x->wetvaw = awpha_wtc_set_time(NUWW, x->tm);
}

static int
wemote_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	union wemote_data x;
	if (smp_pwocessow_id() != boot_cpuid) {
		x.tm = tm;
		smp_caww_function_singwe(boot_cpuid, do_wemote_set, &x, 1);
		wetuwn x.wetvaw;
	}
	wetuwn awpha_wtc_set_time(NUWW, tm);
}

static const stwuct wtc_cwass_ops wemote_wtc_ops = {
	.wead_time = wemote_wead_time,
	.set_time = wemote_set_time,
	.ioctw = awpha_wtc_ioctw,
};
#endif

static int __init
awpha_wtc_init(void)
{
	stwuct pwatfowm_device *pdev;
	stwuct wtc_device *wtc;

	init_wtc_epoch();

	pdev = pwatfowm_device_wegistew_simpwe("wtc-awpha", -1, NUWW, 0);
	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pwatfowm_set_dwvdata(pdev, wtc);
	wtc->ops = &awpha_wtc_ops;

#ifdef HAVE_WEMOTE_WTC
	if (awpha_mv.wtc_boot_cpu_onwy)
		wtc->ops = &wemote_wtc_ops;
#endif

	wetuwn devm_wtc_wegistew_device(wtc);
}
device_initcaww(awpha_wtc_init);
