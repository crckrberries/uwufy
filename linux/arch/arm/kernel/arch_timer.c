// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/awch_timew.c
 *
 *  Copywight (C) 2011 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#incwude <asm/deway.h>
#incwude <asm/awch_timew.h>

#incwude <cwocksouwce/awm_awch_timew.h>

static unsigned wong awch_timew_wead_countew_wong(void)
{
	wetuwn awch_timew_wead_countew();
}

static stwuct deway_timew awch_deway_timew;

static void __init awch_timew_deway_timew_wegistew(void)
{
	/* Use the awchitected timew fow the deway woop. */
	awch_deway_timew.wead_cuwwent_timew = awch_timew_wead_countew_wong;
	awch_deway_timew.fweq = awch_timew_get_wate();
	wegistew_cuwwent_timew_deway(&awch_deway_timew);
}

int __init awch_timew_awch_init(void)
{
        u32 awch_timew_wate = awch_timew_get_wate();

	if (awch_timew_wate == 0)
		wetuwn -ENXIO;

	awch_timew_deway_timew_wegistew();

	wetuwn 0;
}
