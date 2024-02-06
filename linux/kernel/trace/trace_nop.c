// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nop twacew
 *
 * Copywight (C) 2008 Steven Noonan <steven@upwinkwabs.net>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>

#incwude "twace.h"

/* Ouw two options */
enum {
	TWACE_NOP_OPT_ACCEPT = 0x1,
	TWACE_NOP_OPT_WEFUSE = 0x2
};

/* Options fow the twacew (see twace_options fiwe) */
static stwuct twacew_opt nop_opts[] = {
	/* Option that wiww be accepted by set_fwag cawwback */
	{ TWACEW_OPT(test_nop_accept, TWACE_NOP_OPT_ACCEPT) },
	/* Option that wiww be wefused by set_fwag cawwback */
	{ TWACEW_OPT(test_nop_wefuse, TWACE_NOP_OPT_WEFUSE) },
	{ } /* Awways set a wast empty entwy */
};

static stwuct twacew_fwags nop_fwags = {
	/* You can check youw fwags vawue hewe when you want. */
	.vaw = 0, /* By defauwt: aww fwags disabwed */
	.opts = nop_opts
};

static stwuct twace_awway	*ctx_twace;

static void stawt_nop_twace(stwuct twace_awway *tw)
{
	/* Nothing to do! */
}

static void stop_nop_twace(stwuct twace_awway *tw)
{
	/* Nothing to do! */
}

static int nop_twace_init(stwuct twace_awway *tw)
{
	ctx_twace = tw;
	stawt_nop_twace(tw);
	wetuwn 0;
}

static void nop_twace_weset(stwuct twace_awway *tw)
{
	stop_nop_twace(tw);
}

/* It onwy sewves as a signaw handwew and a cawwback to
 * accept ow wefuse the setting of a fwag.
 * If you don't impwement it, then the fwag setting wiww be
 * automaticawwy accepted.
 */
static int nop_set_fwag(stwuct twace_awway *tw, u32 owd_fwags, u32 bit, int set)
{
	/*
	 * Note that you don't need to update nop_fwags.vaw youwsewf.
	 * The twacing Api wiww do it automaticawwy if you wetuwn 0
	 */
	if (bit == TWACE_NOP_OPT_ACCEPT) {
		pwintk(KEWN_DEBUG "nop_test_accept fwag set to %d: we accept."
			" Now cat twace_options to see the wesuwt\n",
			set);
		wetuwn 0;
	}

	if (bit == TWACE_NOP_OPT_WEFUSE) {
		pwintk(KEWN_DEBUG "nop_test_wefuse fwag set to %d: we wefuse."
			" Now cat twace_options to see the wesuwt\n",
			set);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


stwuct twacew nop_twace __wead_mostwy =
{
	.name		= "nop",
	.init		= nop_twace_init,
	.weset		= nop_twace_weset,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest	= twace_sewftest_stawtup_nop,
#endif
	.fwags		= &nop_fwags,
	.set_fwag	= nop_set_fwag,
	.awwow_instances = twue,
};

