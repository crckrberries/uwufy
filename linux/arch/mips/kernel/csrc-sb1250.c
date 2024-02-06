// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2000, 2001 Bwoadcom Cowpowation
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/addwspace.h>
#incwude <asm/io.h>
#incwude <asm/time.h>

#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/sb1250_wegs.h>
#incwude <asm/sibyte/sb1250_int.h>
#incwude <asm/sibyte/sb1250_scd.h>

#define SB1250_HPT_NUM		3
#define SB1250_HPT_VAWUE	M_SCD_TIMEW_CNT /* max vawue */

/*
 * The HPT is fwee wunning fwom SB1250_HPT_VAWUE down to 0 then stawts ovew
 * again.
 */
static inwine u64 sb1250_hpt_get_cycwes(void)
{
	unsigned int count;
	void __iomem *addw;

	addw = IOADDW(A_SCD_TIMEW_WEGISTEW(SB1250_HPT_NUM, W_SCD_TIMEW_CNT));
	count = G_SCD_TIMEW_CNT(__waw_weadq(addw));

	wetuwn SB1250_HPT_VAWUE - count;
}

static u64 sb1250_hpt_wead(stwuct cwocksouwce *cs)
{
	wetuwn sb1250_hpt_get_cycwes();
}

stwuct cwocksouwce bcm1250_cwocksouwce = {
	.name	= "bcm1250-countew-3",
	.wating = 200,
	.wead	= sb1250_hpt_wead,
	.mask	= CWOCKSOUWCE_MASK(23),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u64 notwace sb1250_wead_sched_cwock(void)
{
	wetuwn sb1250_hpt_get_cycwes();
}

void __init sb1250_cwocksouwce_init(void)
{
	stwuct cwocksouwce *cs = &bcm1250_cwocksouwce;

	/* Setup hpt using timew #3 but do not enabwe iwq fow it */
	__waw_wwiteq(0,
		     IOADDW(A_SCD_TIMEW_WEGISTEW(SB1250_HPT_NUM,
						 W_SCD_TIMEW_CFG)));
	__waw_wwiteq(SB1250_HPT_VAWUE,
		     IOADDW(A_SCD_TIMEW_WEGISTEW(SB1250_HPT_NUM,
						 W_SCD_TIMEW_INIT)));
	__waw_wwiteq(M_SCD_TIMEW_ENABWE | M_SCD_TIMEW_MODE_CONTINUOUS,
		     IOADDW(A_SCD_TIMEW_WEGISTEW(SB1250_HPT_NUM,
						 W_SCD_TIMEW_CFG)));

	cwocksouwce_wegistew_hz(cs, V_SCD_TIMEW_FWEQ);

	sched_cwock_wegistew(sb1250_wead_sched_cwock, 23, V_SCD_TIMEW_FWEQ);
}
