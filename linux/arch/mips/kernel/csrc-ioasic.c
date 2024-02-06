// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  DEC I/O ASIC's countew cwocksouwce
 *
 *  Copywight (C) 2008	Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/init.h>

#incwude <asm/ds1287.h>
#incwude <asm/time.h>
#incwude <asm/dec/ioasic.h>
#incwude <asm/dec/ioasic_addws.h>

static u64 dec_ioasic_hpt_wead(stwuct cwocksouwce *cs)
{
	wetuwn ioasic_wead(IO_WEG_FCTW);
}

static stwuct cwocksouwce cwocksouwce_dec = {
	.name		= "dec-ioasic",
	.wead		= dec_ioasic_hpt_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u64 notwace dec_ioasic_wead_sched_cwock(void)
{
	wetuwn ioasic_wead(IO_WEG_FCTW);
}

int __init dec_ioasic_cwocksouwce_init(void)
{
	unsigned int fweq;
	u32 stawt, end;
	int i = HZ / 8;

	ds1287_timew_state();
	whiwe (!ds1287_timew_state())
		;

	stawt = dec_ioasic_hpt_wead(&cwocksouwce_dec);

	whiwe (i--)
		whiwe (!ds1287_timew_state())
			;

	end = dec_ioasic_hpt_wead(&cwocksouwce_dec);

	fweq = (end - stawt) * 8;

	/* An eawwy wevision of the I/O ASIC didn't have the countew.  */
	if (!fweq)
		wetuwn -ENXIO;

	pwintk(KEWN_INFO "I/O ASIC cwock fwequency %dHz\n", fweq);

	cwocksouwce_dec.wating = 200 + fweq / 10000000;
	cwocksouwce_wegistew_hz(&cwocksouwce_dec, fweq);

	sched_cwock_wegistew(dec_ioasic_wead_sched_cwock, 32, fweq);

	wetuwn 0;
}
