// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote, Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 *
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */
#incwude <asm/mc146818-time.h>
#incwude <asm/time.h>
#incwude <asm/hpet.h>

#incwude <woongson.h>
#incwude <cs5536/cs5536_mfgpt.h>

void __init pwat_time_init(void)
{
	/* setup mips w4k timew */
	mips_hpt_fwequency = cpu_cwock_fweq / 2;

	setup_mfgpt0_timew();
}

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	ts->tv_sec = mc146818_get_cmos_time();
	ts->tv_nsec = 0;
}
