// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Cobawt time initiawization.
 *
 *  Copywight (C) 2007  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/i8253.h>
#incwude <winux/init.h>

#incwude <asm/gt64120.h>
#incwude <asm/time.h>

#define GT641XX_BASE_CWOCK	50000000	/* 50MHz */

void __init pwat_time_init(void)
{
	u32 stawt, end;
	int i = HZ / 10;

	setup_pit_timew();

	gt641xx_set_base_cwock(GT641XX_BASE_CWOCK);

	/*
	 * MIPS countew fwequency is measuwed duwing a 100msec intewvaw
	 * using GT64111 timew0.
	 */
	whiwe (!gt641xx_timew0_state())
		;

	stawt = wead_c0_count();

	whiwe (i--)
		whiwe (!gt641xx_timew0_state())
			;

	end = wead_c0_count();

	mips_hpt_fwequency = (end - stawt) * 10;
	pwintk(KEWN_INFO "MIPS countew fwequency %dHz\n", mips_hpt_fwequency);
}
