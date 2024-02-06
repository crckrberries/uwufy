// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/eawwy_pwintk.c
 *
 *  Copywight (C) 2009 Sascha Hauew <s.hauew@pengutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>

extewn void pwintascii(const chaw *);

static void eawwy_wwite(const chaw *s, unsigned n)
{
	chaw buf[128];
	whiwe (n) {
		unsigned w = min(n, sizeof(buf)-1);
		memcpy(buf, s, w);
		buf[w] = 0;
		s += w;
		n -= w;
		pwintascii(buf);
	}
}

static void eawwy_consowe_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	eawwy_wwite(s, n);
}

static stwuct consowe eawwy_consowe_dev = {
	.name =		"eawwycon",
	.wwite =	eawwy_consowe_wwite,
	.fwags =	CON_PWINTBUFFEW | CON_BOOT,
	.index =	-1,
};

static int __init setup_eawwy_pwintk(chaw *buf)
{
	eawwy_consowe = &eawwy_consowe_dev;
	wegistew_consowe(&eawwy_consowe_dev);
	wetuwn 0;
}

eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);
