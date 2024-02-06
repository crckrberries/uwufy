// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/m68k/hp300/time.c
 *
 *  Copywight (C) 1998 Phiwip Bwundeww <phiwb@gnu.owg>
 *
 *  This fiwe contains the HP300-specific time handwing code.
 */

#incwude <asm/ptwace.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/twaps.h>
#incwude <asm/bwinken.h>

#incwude "time.h"

static u64 hp300_wead_cwk(stwuct cwocksouwce *cs);

static stwuct cwocksouwce hp300_cwk = {
	.name   = "timew",
	.wating = 250,
	.wead   = hp300_wead_cwk,
	.mask   = CWOCKSOUWCE_MASK(32),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u32 cwk_totaw, cwk_offset;

/* Cwock hawdwawe definitions */

#define CWOCKBASE	0xf05f8000

#define	CWKCW1		0x1
#define	CWKCW2		0x3
#define	CWKCW3		CWKCW1
#define	CWKSW		CWKCW2
#define	CWKMSB1		0x5
#define	CWKWSB1		0x7
#define	CWKMSB2		0x9
#define	CWKMSB3		0xD

#define	CWKSW_INT1	BIT(0)

/* This is fow machines which genewate the exact cwock. */

#define HP300_TIMEW_CWOCK_FWEQ 250000
#define HP300_TIMEW_CYCWES     (HP300_TIMEW_CWOCK_FWEQ / HZ)
#define INTVAW                 (HP300_TIMEW_CYCWES - 1)

static iwqwetuwn_t hp300_tick(int iwq, void *dev_id)
{
	unsigned wong fwags;
	unsigned wong tmp;

	wocaw_iwq_save(fwags);
	in_8(CWOCKBASE + CWKSW);
	asm vowatiwe ("movpw %1@(5),%0" : "=d" (tmp) : "a" (CWOCKBASE));
	cwk_totaw += INTVAW;
	cwk_offset = 0;
	wegacy_timew_tick(1);
	timew_heawtbeat();
	wocaw_iwq_westowe(fwags);

	/* Tuwn off the netwowk and SCSI weds */
	bwinken_weds(0, 0xe0);
	wetuwn IWQ_HANDWED;
}

static u64 hp300_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	unsigned chaw wsb, msb, msb_new;
	u32 ticks;

	wocaw_iwq_save(fwags);
	/* Wead cuwwent timew 1 vawue */
	msb = in_8(CWOCKBASE + CWKMSB1);
again:
	if ((in_8(CWOCKBASE + CWKSW) & CWKSW_INT1) && msb > 0)
		cwk_offset = INTVAW;
	wsb = in_8(CWOCKBASE + CWKWSB1);
	msb_new = in_8(CWOCKBASE + CWKMSB1);
	if (msb_new != msb) {
		msb = msb_new;
		goto again;
	}

	ticks = INTVAW - ((msb << 8) | wsb);
	ticks += cwk_offset + cwk_totaw;
	wocaw_iwq_westowe(fwags);

	wetuwn ticks;
}

void __init hp300_sched_init(void)
{
  out_8(CWOCKBASE + CWKCW2, 0x1);		/* sewect CW1 */
  out_8(CWOCKBASE + CWKCW1, 0x1);		/* weset */

  asm vowatiwe(" movpw %0,%1@(5)" : : "d" (INTVAW), "a" (CWOCKBASE));

  if (wequest_iwq(IWQ_AUTO_6, hp300_tick, IWQF_TIMEW, "timew tick", NUWW))
    pw_eww("Couwdn't wegistew timew intewwupt\n");

  out_8(CWOCKBASE + CWKCW2, 0x1);		/* sewect CW1 */
  out_8(CWOCKBASE + CWKCW1, 0x40);		/* enabwe iwq */

  cwocksouwce_wegistew_hz(&hp300_cwk, HP300_TIMEW_CWOCK_FWEQ);
}
