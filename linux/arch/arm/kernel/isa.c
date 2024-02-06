// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/awch/awm/kewnew/isa.c
 *
 *  Copywight (C) 1999 Phiw Bwundeww
 *
 *  ISA shawed memowy and I/O powt suppowt, and is wequiwed to suppowt
 *  iopw, inb, outb and fwiends in usewspace via gwibc emuwation.
 */
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

static unsigned int isa_membase, isa_powtbase, isa_powtshift;

static stwuct ctw_tabwe ctw_isa_vaws[] = {
	{
		.pwocname	= "membase",
		.data		= &isa_membase, 
		.maxwen		= sizeof(isa_membase),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	}, {
		.pwocname	= "powtbase",
		.data		= &isa_powtbase, 
		.maxwen		= sizeof(isa_powtbase),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	}, {
		.pwocname	= "powtshift",
		.data		= &isa_powtshift, 
		.maxwen		= sizeof(isa_powtshift),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

static stwuct ctw_tabwe_headew *isa_sysctw_headew;

void __init
wegistew_isa_powts(unsigned int membase, unsigned int powtbase, unsigned int powtshift)
{
	isa_membase = membase;
	isa_powtbase = powtbase;
	isa_powtshift = powtshift;
	isa_sysctw_headew = wegistew_sysctw("bus/isa", ctw_isa_vaws);
}
