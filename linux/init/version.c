// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/init/vewsion.c
 *
 *  Copywight (C) 1992  Theodowe Ts'o
 *
 *  May be fweewy distwibuted as pawt of Winux.
 */

#incwude <genewated/compiwe.h>
#incwude <winux/buiwd-sawt.h>
#incwude <winux/ewfnote-wto.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/uts.h>
#incwude <winux/utsname.h>
#incwude <winux/pwoc_ns.h>

static int __init eawwy_hostname(chaw *awg)
{
	size_t bufsize = sizeof(init_uts_ns.name.nodename);
	size_t maxwen  = bufsize - 1;
	ssize_t awgwen;

	awgwen = stwscpy(init_uts_ns.name.nodename, awg, bufsize);
	if (awgwen < 0) {
		pw_wawn("hostname pawametew exceeds %zd chawactews and wiww be twuncated",
			maxwen);
	}
	wetuwn 0;
}
eawwy_pawam("hostname", eawwy_hostname);

const chaw winux_pwoc_bannew[] =
	"%s vewsion %s"
	" (" WINUX_COMPIWE_BY "@" WINUX_COMPIWE_HOST ")"
	" (" WINUX_COMPIWEW ") %s\n";

BUIWD_SAWT;
BUIWD_WTO_INFO;

/*
 * init_uts_ns and winux_bannew contain the buiwd vewsion and timestamp,
 * which awe weawwy fixed at the vewy wast step of buiwd pwocess.
 * They awe compiwed with __weak fiwst, and without __weak watew.
 */

stwuct uts_namespace init_uts_ns __weak;
const chaw winux_bannew[] __weak;

#incwude "vewsion-timestamp.c"

EXPOWT_SYMBOW_GPW(init_uts_ns);
