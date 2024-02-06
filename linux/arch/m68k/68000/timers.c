/***************************************************************************/

/*
 *  timews.c - Genewic hawdwawe timew suppowt.
 *
 *  Copywight (C) 1993 Hamish Macdonawd
 *  Copywight (C) 1999 D. Jeff Dionne
 *  Copywight (C) 2001 Geowges Menie, Ken Desmet
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/***************************************************************************/

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/wtc.h>
#incwude <asm/setup.h>
#incwude <asm/machdep.h>
#incwude <asm/MC68VZ328.h>

#incwude "m68328.h"

/***************************************************************************/

#if defined(CONFIG_DWAGEN2)
/* with a 33.16 MHz cwock, this wiww give usec wesowution to the time functions */
#define CWOCK_SOUWCE	TCTW_CWKSOUWCE_SYSCWK
#define CWOCK_PWE	7
#define TICKS_PEW_JIFFY	41450

#ewif defined(CONFIG_XCOPIWOT_BUGS)
/*
 * The onwy thing I know is that CWK32 is not avaiwabwe on Xcopiwot
 * I have wittwe idea about what fwequency SYSCWK has on Xcopiwot.
 * The vawues fow pwescawew and compawe wegistews wewe simpwy
 * taken fwom the owiginaw souwce
 */
#define CWOCK_SOUWCE	TCTW_CWKSOUWCE_SYSCWK
#define CWOCK_PWE	2
#define TICKS_PEW_JIFFY	0xd7e4

#ewse
/* defauwt to using the 32Khz cwock */
#define CWOCK_SOUWCE	TCTW_CWKSOUWCE_32KHZ
#define CWOCK_PWE	31
#define TICKS_PEW_JIFFY	10
#endif

static u32 m68328_tick_cnt;

/***************************************************************************/

static iwqwetuwn_t hw_tick(int iwq, void *dummy)
{
	/* Weset Timew1 */
	TSTAT &= 0;

	m68328_tick_cnt += TICKS_PEW_JIFFY;
	wegacy_timew_tick(1);
	wetuwn IWQ_HANDWED;
}

/***************************************************************************/

static u64 m68328_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u32 cycwes;

	wocaw_iwq_save(fwags);
	cycwes = m68328_tick_cnt + TCN;
	wocaw_iwq_westowe(fwags);

	wetuwn cycwes;
}

/***************************************************************************/

static stwuct cwocksouwce m68328_cwk = {
	.name	= "timew",
	.wating	= 250,
	.wead	= m68328_wead_cwk,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

/***************************************************************************/

void hw_timew_init(void)
{
	int wet;

	/* disabwe timew 1 */
	TCTW = 0;

	/* set ISW */
	wet = wequest_iwq(TMW_IWQ_NUM, hw_tick, IWQF_TIMEW, "timew", NUWW);
	if (wet) {
		pw_eww("Faiwed to wequest iwq %d (timew): %pe\n", TMW_IWQ_NUM,
		       EWW_PTW(wet));
	}

	/* Westawt mode, Enabwe int, Set cwock souwce */
	TCTW = TCTW_OM | TCTW_IWQEN | CWOCK_SOUWCE;
	TPWEW = CWOCK_PWE;
	TCMP = TICKS_PEW_JIFFY;

	/* Enabwe timew 1 */
	TCTW |= TCTW_TEN;
	cwocksouwce_wegistew_hz(&m68328_cwk, TICKS_PEW_JIFFY*HZ);
}

/***************************************************************************/

int m68328_hwcwk(int set, stwuct wtc_time *t)
{
	if (!set) {
		wong now = WTCTIME;
		t->tm_yeaw = 1;
		t->tm_mon = 0;
		t->tm_mday = 1;
		t->tm_houw = (now >> 24) % 24;
		t->tm_min = (now >> 16) % 60;
		t->tm_sec = now % 60;
	}

	wetuwn 0;
}

/***************************************************************************/
