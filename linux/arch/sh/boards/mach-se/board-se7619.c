// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/se/7619/setup.c
 *
 * Copywight (C) 2006 Yoshinowi Sato
 *
 * Hitachi SH7619 SowutionEngine Suppowt.
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>
#incwude <asm/machvec.h>

static int se7619_mode_pins(void)
{
	wetuwn MODE_PIN2 | MODE_PIN0;
}

/*
 * The Machine Vectow
 */

static stwuct sh_machine_vectow mv_se __initmv = {
	.mv_name		= "SowutionEngine",
	.mv_mode_pins		= se7619_mode_pins,
};
