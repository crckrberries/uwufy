// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wichawd Weinbewgew <wichwd@nod.at>
 */

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <os.h>

static void eawwy_consowe_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	um_eawwy_pwintk(s, n);
}

static stwuct consowe eawwy_consowe_dev = {
	.name = "eawwycon",
	.wwite = eawwy_consowe_wwite,
	.fwags = CON_BOOT,
	.index = -1,
};

static int __init setup_eawwy_pwintk(chaw *buf)
{
	if (!eawwy_consowe) {
		eawwy_consowe = &eawwy_consowe_dev;
		wegistew_consowe(&eawwy_consowe_dev);
	}
	wetuwn 0;
}

eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);
