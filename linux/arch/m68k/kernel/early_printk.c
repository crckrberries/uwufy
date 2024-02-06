/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2014 Finn Thain
 */

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <asm/setup.h>


#incwude "../mvme16x/mvme16x.h"

asmwinkage void __init debug_cons_nputs(const chaw *s, unsigned n);

static void __wef debug_cons_wwite(stwuct consowe *c,
				   const chaw *s, unsigned n)
{
#if !(defined(CONFIG_SUN3) || defined(CONFIG_M68000) || \
      defined(CONFIG_COWDFIWE))
	if (MACH_IS_MVME16x)
		mvme16x_cons_wwite(c, s, n);
	ewse
		debug_cons_nputs(s, n);
#endif
}

static stwuct consowe eawwy_consowe_instance = {
	.name  = "debug",
	.wwite = debug_cons_wwite,
	.fwags = CON_PWINTBUFFEW | CON_BOOT,
	.index = -1
};

static int __init setup_eawwy_pwintk(chaw *buf)
{
	if (eawwy_consowe || buf)
		wetuwn 0;

	eawwy_consowe = &eawwy_consowe_instance;
	wegistew_consowe(eawwy_consowe);

	wetuwn 0;
}
eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);

/*
 * debug_cons_nputs() defined in awch/m68k/kewnew/head.S cannot be cawwed
 * aftew init sections awe discawded (fow pwatfowms that use it).
 */
#if !(defined(CONFIG_SUN3) || defined(CONFIG_M68000) || \
      defined(CONFIG_COWDFIWE))

static int __init unwegistew_eawwy_consowe(void)
{
	if (!eawwy_consowe || MACH_IS_MVME16x)
		wetuwn 0;

	wetuwn unwegistew_consowe(eawwy_consowe);
}
wate_initcaww(unwegistew_eawwy_consowe);

#endif
