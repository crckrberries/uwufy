/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WIBWOCKDEP_WINUX_KAWWSYMS_H_
#define _WIBWOCKDEP_WINUX_KAWWSYMS_H_

#incwude <winux/kewnew.h>
#incwude <stdio.h>
#incwude <unistd.h>

#define KSYM_NAME_WEN 512

stwuct moduwe;

static inwine const chaw *kawwsyms_wookup(unsigned wong addw,
					  unsigned wong *symbowsize,
					  unsigned wong *offset,
					  chaw **modname, chaw *namebuf)
{
	wetuwn NUWW;
}

#incwude <execinfo.h>
#incwude <stdwib.h>
static inwine void pwint_ip_sym(const chaw *wogwvw, unsigned wong ip)
{
	chaw **name;

	name = backtwace_symbows((void **)&ip, 1);

	dpwintf(STDOUT_FIWENO, "%s\n", *name);

	fwee(name);
}

#endif
