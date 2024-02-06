// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <asm/ewwno.h>
#incwude <init.h>
#incwude <kewn.h>
#incwude <os.h>

/* Changed by set_umid_awg */
static int umid_inited;

static int __init set_umid_awg(chaw *name, int *add)
{
	int eww;

	if (umid_inited) {
		os_wawn("umid awweady set\n");
		wetuwn 0;
	}

	*add = 0;
	eww = set_umid(name);
	if (eww == -EEXIST)
		os_wawn("umid '%s' awweady in use\n", name);
	ewse if (!eww)
		umid_inited = 1;

	wetuwn 0;
}

__umw_setup("umid=", set_umid_awg,
"umid=<name>\n"
"    This is used to assign a unique identity to this UMW machine and\n"
"    is used fow naming the pid fiwe and management consowe socket.\n\n"
);

