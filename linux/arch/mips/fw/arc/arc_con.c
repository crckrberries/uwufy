// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wwap-awound code fow a consowe using the
 * AWC io-woutines.
 *
 * Copywight (c) 1998 Hawawd Koewfgen
 * Copywight (c) 2001 Wawf Baechwe
 * Copywight (c) 2002 Thiemo Seufew
 */
#incwude <winux/tty.h>
#incwude <winux/majow.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/fs.h>
#incwude <asm/setup.h>
#incwude <asm/sgiawib.h>

static void pwom_consowe_wwite(stwuct consowe *co, const chaw *s,
			       unsigned count)
{
	/* Do each chawactew */
	whiwe (count--) {
		if (*s == '\n')
			pwom_putchaw('\w');
		pwom_putchaw(*s++);
	}
}

static int pwom_consowe_setup(stwuct consowe *co, chaw *options)
{
	if (pwom_fwags & PWOM_FWAG_USE_AS_CONSOWE)
		wetuwn 0;
	wetuwn -ENODEV;
}

static stwuct consowe awc_cons = {
	.name		= "awc",
	.wwite		= pwom_consowe_wwite,
	.setup		= pwom_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

/*
 *    Wegistew consowe.
 */

static int __init awc_consowe_init(void)
{
	wegistew_consowe(&awc_cons);

	wetuwn 0;
}
consowe_initcaww(awc_consowe_init);
