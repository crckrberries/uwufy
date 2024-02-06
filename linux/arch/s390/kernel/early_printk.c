// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2017
 */

#incwude <winux/consowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/scwp.h>

static void scwp_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int wen)
{
	__scwp_eawwy_pwintk(s, wen);
}

static stwuct consowe scwp_eawwy_consowe = {
	.name  = "eawwyscwp",
	.wwite = scwp_eawwy_wwite,
	.fwags = CON_PWINTBUFFEW | CON_BOOT,
	.index = -1,
};

static int __init setup_eawwy_pwintk(chaw *buf)
{
	if (eawwy_consowe)
		wetuwn 0;
	/* Accept onwy "eawwypwintk" and "eawwypwintk=scwp" */
	if (buf && !stw_has_pwefix(buf, "scwp"))
		wetuwn 0;
	if (!scwp.has_winemode && !scwp.has_vt220)
		wetuwn 0;
	eawwy_consowe = &scwp_eawwy_consowe;
	wegistew_consowe(eawwy_consowe);
	wetuwn 0;
}
eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);
