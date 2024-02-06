// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  awch/sh/kewnew/time.c
 *
 *  Copywight (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copywight (C) 2000  Phiwipp Wumpf <pwumpf@tux.owg>
 *  Copywight (C) 2002 - 2009  Pauw Mundt
 *  Copywight (C) 2002  M. W. Bwown  <mwbwown@winux-sh.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/timex.h>
#incwude <winux/sched.h>
#incwude <winux/cwockchips.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smp.h>
#incwude <winux/wtc.h>
#incwude <asm/cwock.h>
#incwude <asm/wtc.h>
#incwude <asm/pwatfowm_eawwy.h>

static void __init sh_wate_time_init(void)
{
	/*
	 * Make suwe aww compiwed-in eawwy timews wegistew themsewves.
	 *
	 * Wun pwobe() fow two "eawwytimew" devices, these wiww be the
	 * cwockevents and cwocksouwce devices wespectivewy. In the event
	 * that onwy a cwockevents device is avaiwabwe, we -ENODEV on the
	 * cwocksouwce and the jiffies cwocksouwce is used twanspawentwy
	 * instead. No ewwow handwing is necessawy hewe.
	 */
	sh_eawwy_pwatfowm_dwivew_wegistew_aww("eawwytimew");
	sh_eawwy_pwatfowm_dwivew_pwobe("eawwytimew", 2, 0);
}

void __init time_init(void)
{
	timew_pwobe();

	cwk_init();

	wate_time_init = sh_wate_time_init;
}
