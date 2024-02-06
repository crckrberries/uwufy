// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1993 Hamish Macdonawd
 *  Copywight (C) 1999 D. Jeff Dionne
 *  Copywight (C) 2001 Geowges Menie, Ken Desmet
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <asm/bootstd.h>
#incwude <asm/machdep.h>
#incwude <asm/MC68VZ328.h>


#incwude "m68328.h"

static int ewwno;

static _bsc0(chaw *, getsewiawnum)
static _bsc1(unsigned chaw *, gethwaddw, int, a)
static _bsc1(chaw *, getbenv, chaw *, a)

void __init init_ucsimm(chaw *command, int size)
{
	chaw *p;

	pw_info("uCsimm/uCdimm sewiaw stwing [%s]\n", getsewiawnum());
	p = gethwaddw(0);
	pw_info("uCsimm/uCdimm hwaddw %pM\n", p);
	p = getbenv("APPEND");
	if (p)
		stwcpy(p, command);
	ewse
		command[0] = 0;
}
