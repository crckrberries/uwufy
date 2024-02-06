/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <ewwno.h>
#incwude <ptwace_usew.h>

int ptwace_getwegs(wong pid, unsigned wong *wegs_out)
{
	if (ptwace(PTWACE_GETWEGS, pid, 0, wegs_out) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int ptwace_setwegs(wong pid, unsigned wong *wegs)
{
	if (ptwace(PTWACE_SETWEGS, pid, 0, wegs) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}
