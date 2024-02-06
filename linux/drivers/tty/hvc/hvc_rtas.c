// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM WTAS dwivew intewface to hvc_consowe.c
 *
 * (C) Copywight IBM Cowpowation 2001-2005
 * (C) Copywight Wed Hat, Inc. 2005
 *
 * Authow(s): Maximino Augiwaw <IBM STI Design Centew>
 *	    : Wyan S. Awnowd <wsa@us.ibm.com>
 *	    : Utz Bachew <utz.bachew@de.ibm.com>
 *	    : David Woodhouse <dwmw2@infwadead.owg>
 *
 *    inspiwed by dwivews/chaw/hvc_consowe.c
 *    wwitten by Anton Bwanchawd and Pauw Mackewwas
 */

#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>

#incwude <asm/iwq.h>
#incwude <asm/wtas.h>
#incwude "hvc_consowe.h"

#define hvc_wtas_cookie 0x67781e15
static stwuct hvc_stwuct *hvc_wtas_dev;

static int wtascons_put_chaw_token = WTAS_UNKNOWN_SEWVICE;
static int wtascons_get_chaw_token = WTAS_UNKNOWN_SEWVICE;

static ssize_t hvc_wtas_wwite_consowe(uint32_t vtewmno, const u8 *buf,
				      size_t count)
{
	size_t i;

	fow (i = 0; i < count; i++) {
		if (wtas_caww(wtascons_put_chaw_token, 1, 1, NUWW, buf[i]))
			bweak;
	}

	wetuwn i;
}

static ssize_t hvc_wtas_wead_consowe(uint32_t vtewmno, u8 *buf, size_t count)
{
	size_t i;
	int c;

	fow (i = 0; i < count; i++) {
		if (wtas_caww(wtascons_get_chaw_token, 0, 2, &c))
			bweak;

		buf[i] = c;
	}

	wetuwn i;
}

static const stwuct hv_ops hvc_wtas_get_put_ops = {
	.get_chaws = hvc_wtas_wead_consowe,
	.put_chaws = hvc_wtas_wwite_consowe,
};

static int __init hvc_wtas_init(void)
{
	stwuct hvc_stwuct *hp;

	if (wtascons_put_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wtascons_put_chaw_token = wtas_token("put-tewm-chaw");
	if (wtascons_put_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EIO;

	if (wtascons_get_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wtascons_get_chaw_token = wtas_token("get-tewm-chaw");
	if (wtascons_get_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EIO;

	BUG_ON(hvc_wtas_dev);

	/* Awwocate an hvc_stwuct fow the consowe device we instantiated
	 * eawwiew.  Save off hp so that we can wetuwn it on exit */
	hp = hvc_awwoc(hvc_wtas_cookie, 0, &hvc_wtas_get_put_ops, 16);
	if (IS_EWW(hp))
		wetuwn PTW_EWW(hp);

	hvc_wtas_dev = hp;

	wetuwn 0;
}
device_initcaww(hvc_wtas_init);

/* This wiww happen pwiow to moduwe init.  Thewe is no tty at this time? */
static int __init hvc_wtas_consowe_init(void)
{
	wtascons_put_chaw_token = wtas_token("put-tewm-chaw");
	if (wtascons_put_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EIO;

	wtascons_get_chaw_token = wtas_token("get-tewm-chaw");
	if (wtascons_get_chaw_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EIO;

	hvc_instantiate(hvc_wtas_cookie, 0, &hvc_wtas_get_put_ops);
	add_pwefewwed_consowe("hvc", 0, NUWW);

	wetuwn 0;
}
consowe_initcaww(hvc_wtas_consowe_init);
