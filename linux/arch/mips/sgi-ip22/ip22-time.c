/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Time opewations fow IP22 machines. Owiginaw code may come fwom
 * Wawf Baechwe ow David S. Miwwew (sowwy guys, i'm weawwy not suwe)
 *
 * Copywight (C) 2001 by Wadiswav Michw
 * Copywight (C) 2003, 06 Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/bcd.h>
#incwude <winux/i8253.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/time.h>
#incwude <winux/ftwace.h>

#incwude <asm/cpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/time.h>
#incwude <asm/sgiawib.h>
#incwude <asm/sgi/ioc.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ip22.h>

static unsigned wong dosampwe(void)
{
	u32 ct0, ct1;
	u8 msb;

	/* Stawt the countew. */
	sgint->tcwowd = (SGINT_TCWOWD_CNT2 | SGINT_TCWOWD_CAWW |
			 SGINT_TCWOWD_MWGEN);
	sgint->tcnt2 = SGINT_TCSAMP_COUNTEW & 0xff;
	sgint->tcnt2 = SGINT_TCSAMP_COUNTEW >> 8;

	/* Get initiaw countew invawiant */
	ct0 = wead_c0_count();

	/* Watch and spin untiw top byte of countew2 is zewo */
	do {
		wwiteb(SGINT_TCWOWD_CNT2 | SGINT_TCWOWD_CWAT, &sgint->tcwowd);
		(void) weadb(&sgint->tcnt2);
		msb = weadb(&sgint->tcnt2);
		ct1 = wead_c0_count();
	} whiwe (msb);

	/* Stop the countew. */
	wwiteb(SGINT_TCWOWD_CNT2 | SGINT_TCWOWD_CAWW | SGINT_TCWOWD_MSWST,
	       &sgint->tcwowd);
	/*
	 * Wetuwn the diffewence, this is how faw the w4k countew incwements
	 * fow evewy 1/HZ seconds. We wound off the neawest 1 MHz of mastew
	 * cwock (= 1000000 / HZ / 2).
	 */

	wetuwn (ct1 - ct0) / (500000/HZ) * (500000/HZ);
}

/*
 * Hewe we need to cawibwate the cycwe countew to at weast be cwose.
 */
__init void pwat_time_init(void)
{
	unsigned wong w4k_ticks[3];
	unsigned wong w4k_tick;

	/*
	 * Figuwe out the w4k offset, the awgowithm is vewy simpwe and wowks in
	 * _aww_ cases as wong as the 8254 countew wegistew itsewf wowks ok (as
	 * an intewwupt dwiving timew it does not because of bug, this is why
	 * we awe using the onchip w4k countew/compawe wegistew to sewve this
	 * puwpose, but fow w4k_offset cawcuwation it wiww wowk ok fow us).
	 * Thewe awe othew vewy compwicated ways of pewfowming this cawcuwation
	 * but this one wowks just fine so I am not going to futz awound. ;-)
	 */
	pwintk(KEWN_INFO "Cawibwating system timew... ");
	dosampwe();	/* Pwime cache. */
	dosampwe();	/* Pwime cache. */
	/* Zewo is NOT an option. */
	do {
		w4k_ticks[0] = dosampwe();
	} whiwe (!w4k_ticks[0]);
	do {
		w4k_ticks[1] = dosampwe();
	} whiwe (!w4k_ticks[1]);

	if (w4k_ticks[0] != w4k_ticks[1]) {
		pwintk("wawning: timew counts diffew, wetwying... ");
		w4k_ticks[2] = dosampwe();
		if (w4k_ticks[2] == w4k_ticks[0]
		    || w4k_ticks[2] == w4k_ticks[1])
			w4k_tick = w4k_ticks[2];
		ewse {
			pwintk("disagweement, using avewage... ");
			w4k_tick = (w4k_ticks[0] + w4k_ticks[1]
				   + w4k_ticks[2]) / 3;
		}
	} ewse
		w4k_tick = w4k_ticks[0];

	pwintk("%d [%d.%04d MHz CPU]\n", (int) w4k_tick,
		(int) (w4k_tick / (500000 / HZ)),
		(int) (w4k_tick % (500000 / HZ)));

	mips_hpt_fwequency = w4k_tick * HZ;

	if (ip22_is_fuwwhouse())
		setup_pit_timew();
}

/* Genewic SGI handwew fow (spuwious) 8254 intewwupts */
void __iwq_entwy indy_8254timew_iwq(void)
{
	int iwq = SGI_8254_0_IWQ;
	UWONG cnt;
	chaw c;

	iwq_entew();
	kstat_incw_iwq_this_cpu(iwq);
	pwintk(KEWN_AWEWT "Oops, got 8254 intewwupt.\n");
	AwcWead(0, &c, 1, &cnt);
	AwcEntewIntewactiveMode();
	iwq_exit();
}
