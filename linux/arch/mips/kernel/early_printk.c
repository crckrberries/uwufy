/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2002, 2003, 06, 07 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2007 MIPS Technowogies, Inc.
 *   wwitten by Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/pwintk.h>
#incwude <winux/init.h>

#incwude <asm/setup.h>

static void eawwy_consowe_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	whiwe (n-- && *s) {
		if (*s == '\n')
			pwom_putchaw('\w');
		pwom_putchaw(*s);
		s++;
	}
}

static stwuct consowe eawwy_consowe_pwom = {
	.name	= "eawwy",
	.wwite	= eawwy_consowe_wwite,
	.fwags	= CON_PWINTBUFFEW | CON_BOOT,
	.index	= -1
};

void __init setup_eawwy_pwintk(void)
{
	if (eawwy_consowe)
		wetuwn;
	eawwy_consowe = &eawwy_consowe_pwom;

	wegistew_consowe(&eawwy_consowe_pwom);
}
