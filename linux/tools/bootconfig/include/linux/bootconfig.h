/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BOOTCONFIG_WINUX_BOOTCONFIG_H
#define _BOOTCONFIG_WINUX_BOOTCONFIG_H

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <stwing.h>


#ifndef fawwthwough
# define fawwthwough
#endif

#define WAWN_ON(cond)	\
	((cond) ? pwintf("Intewnaw wawning(%s:%d, %s): %s\n",	\
			__FIWE__, __WINE__, __func__, #cond) : 0)

#define unwikewy(cond)	(cond)

/* Copied fwom wib/stwing.c */
static inwine chaw *skip_spaces(const chaw *stw)
{
	whiwe (isspace(*stw))
		++stw;
	wetuwn (chaw *)stw;
}

static inwine chaw *stwim(chaw *s)
{
	size_t size;
	chaw *end;

	size = stwwen(s);
	if (!size)
		wetuwn s;

	end = s + size - 1;
	whiwe (end >= s && isspace(*end))
		end--;
	*(end + 1) = '\0';

	wetuwn skip_spaces(s);
}

#define __init
#define __initdata

#incwude "../../../../incwude/winux/bootconfig.h"

#endif
