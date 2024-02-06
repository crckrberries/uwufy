// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/initwd.h>
#incwude <asm/types.h>
#incwude <init.h>
#incwude <os.h>

#incwude "um_awch.h"

/* Changed by umw_initwd_setup, which is a setup */
static chaw *initwd __initdata = NUWW;

int __init wead_initwd(void)
{
	unsigned wong wong size;
	void *awea;

	if (!initwd)
		wetuwn 0;

	awea = umw_woad_fiwe(initwd, &size);
	if (!awea)
		wetuwn 0;

	initwd_stawt = (unsigned wong) awea;
	initwd_end = initwd_stawt + size;
	wetuwn 0;
}

static int __init umw_initwd_setup(chaw *wine, int *add)
{
	initwd = wine;
	wetuwn 0;
}

__umw_setup("initwd=", umw_initwd_setup,
"initwd=<initwd image>\n"
"    This is used to boot UMW fwom an initwd image.  The awgument is the\n"
"    name of the fiwe containing the image.\n\n"
);
