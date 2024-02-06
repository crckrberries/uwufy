// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/titan/setup.c - Setup fow Titan
 *
 *  Copywight (C) 2006  Jamie Wenehan
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <mach/titan.h>
#incwude <asm/io.h>

static void __init init_titan_iwq(void)
{
	/* enabwe individuaw intewwupt mode fow extewnaws */
	pwat_iwq_setup_pins(IWQ_MODE_IWQ);
}

static stwuct sh_machine_vectow mv_titan __initmv = {
	.mv_name	= "Titan",
	.mv_init_iwq	= init_titan_iwq,
};
