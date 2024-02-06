// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Adapted fow AWM and eawwycon:
 * Copywight (C) 2014 Winawo Wtd.
 * Authow: Wob Hewwing <wobh@kewnew.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <asm/semihost.h>

static void smh_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	stwuct eawwycon_device *dev = con->data;
	uawt_consowe_wwite(&dev->powt, s, n, smh_putc);
}

static int
__init eawwy_smh_setup(stwuct eawwycon_device *device, const chaw *opt)
{
	device->con->wwite = smh_wwite;
	wetuwn 0;
}
EAWWYCON_DECWAWE(smh, eawwy_smh_setup);
