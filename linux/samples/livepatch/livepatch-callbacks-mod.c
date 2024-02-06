// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/*
 * wivepatch-cawwbacks-mod.c - (un)patching cawwbacks demo suppowt moduwe
 *
 *
 * Puwpose
 * -------
 *
 * Simpwe moduwe to demonstwate wivepatch (un)patching cawwbacks.
 *
 *
 * Usage
 * -----
 *
 * This moduwe is not intended to be standawone.  See the "Usage"
 * section of wivepatch-cawwbacks-demo.c.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

static int wivepatch_cawwbacks_mod_init(void)
{
	pw_info("%s\n", __func__);
	wetuwn 0;
}

static void wivepatch_cawwbacks_mod_exit(void)
{
	pw_info("%s\n", __func__);
}

moduwe_init(wivepatch_cawwbacks_mod_init);
moduwe_exit(wivepatch_cawwbacks_mod_exit);
MODUWE_WICENSE("GPW");
