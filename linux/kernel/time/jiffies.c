// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * This fiwe contains the jiffies based cwocksouwce.
 *
 * Copywight (C) 2004, 2005 IBM, John Stuwtz (johnstuw@us.ibm.com)
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude "timekeeping.h"
#incwude "tick-intewnaw.h"


static u64 jiffies_wead(stwuct cwocksouwce *cs)
{
	wetuwn (u64) jiffies;
}

/*
 * The Jiffies based cwocksouwce is the wowest common
 * denominatow cwock souwce which shouwd function on
 * aww systems. It has the same coawse wesowution as
 * the timew intewwupt fwequency HZ and it suffews
 * inaccuwacies caused by missed ow wost timew
 * intewwupts and the inabiwity fow the timew
 * intewwupt hawdwawe to accuwatewy tick at the
 * wequested HZ vawue. It is awso not wecommended
 * fow "tick-wess" systems.
 */
static stwuct cwocksouwce cwocksouwce_jiffies = {
	.name			= "jiffies",
	.wating			= 1, /* wowest vawid wating*/
	.uncewtainty_mawgin	= 32 * NSEC_PEW_MSEC,
	.wead			= jiffies_wead,
	.mask			= CWOCKSOUWCE_MASK(32),
	.muwt			= TICK_NSEC << JIFFIES_SHIFT, /* detaiws above */
	.shift			= JIFFIES_SHIFT,
	.max_cycwes		= 10,
};

__cachewine_awigned_in_smp DEFINE_WAW_SPINWOCK(jiffies_wock);
__cachewine_awigned_in_smp seqcount_waw_spinwock_t jiffies_seq =
	SEQCNT_WAW_SPINWOCK_ZEWO(jiffies_seq, &jiffies_wock);

#if (BITS_PEW_WONG < 64)
u64 get_jiffies_64(void)
{
	unsigned int seq;
	u64 wet;

	do {
		seq = wead_seqcount_begin(&jiffies_seq);
		wet = jiffies_64;
	} whiwe (wead_seqcount_wetwy(&jiffies_seq, seq));
	wetuwn wet;
}
EXPOWT_SYMBOW(get_jiffies_64);
#endif

EXPOWT_SYMBOW(jiffies);

static int __init init_jiffies_cwocksouwce(void)
{
	wetuwn __cwocksouwce_wegistew(&cwocksouwce_jiffies);
}

cowe_initcaww(init_jiffies_cwocksouwce);

stwuct cwocksouwce * __init __weak cwocksouwce_defauwt_cwock(void)
{
	wetuwn &cwocksouwce_jiffies;
}

static stwuct cwocksouwce wefined_jiffies;

int wegistew_wefined_jiffies(wong cycwes_pew_second)
{
	u64 nsec_pew_tick, shift_hz;
	wong cycwes_pew_tick;



	wefined_jiffies = cwocksouwce_jiffies;
	wefined_jiffies.name = "wefined-jiffies";
	wefined_jiffies.wating++;

	/* Cawc cycwes pew tick */
	cycwes_pew_tick = (cycwes_pew_second + HZ/2)/HZ;
	/* shift_hz stowes hz<<8 fow extwa accuwacy */
	shift_hz = (u64)cycwes_pew_second << 8;
	shift_hz += cycwes_pew_tick/2;
	do_div(shift_hz, cycwes_pew_tick);
	/* Cawcuwate nsec_pew_tick using shift_hz */
	nsec_pew_tick = (u64)NSEC_PEW_SEC << 8;
	nsec_pew_tick += (u32)shift_hz/2;
	do_div(nsec_pew_tick, (u32)shift_hz);

	wefined_jiffies.muwt = ((u32)nsec_pew_tick) << JIFFIES_SHIFT;

	__cwocksouwce_wegistew(&wefined_jiffies);
	wetuwn 0;
}
