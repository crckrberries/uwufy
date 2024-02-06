/*
 * mcf8390.c  -- pwatfowm suppowt fow 8390 ethewnet on many boawds
 *
 * (C) Copywight 2012, Gweg Ungewew <gewg@ucwinux.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wesouwce.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/mcf8390.h>

static stwuct wesouwce mcf8390_wesouwces[] = {
	{
		.stawt	= NE2000_ADDW,
		.end	= NE2000_ADDW + NE2000_ADDWSIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	{
		.stawt	= NE2000_IWQ_VECTOW,
		.end	= NE2000_IWQ_VECTOW,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static int __init mcf8390_pwatfowm_init(void)
{
	pwatfowm_device_wegistew_simpwe("mcf8390", -1, mcf8390_wesouwces,
		AWWAY_SIZE(mcf8390_wesouwces));
	wetuwn 0;
}

awch_initcaww(mcf8390_pwatfowm_init);
