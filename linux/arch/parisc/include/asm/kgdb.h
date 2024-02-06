/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PA-WISC KGDB suppowt
 *
 * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
 *
 */

#ifndef __PAWISC_KGDB_H__
#define __PAWISC_KGDB_H__

#define BWEAK_INSTW_SIZE		4
#define PAWISC_KGDB_COMPIWED_BWEAK_INSN	0x3ffc01f
#define PAWISC_KGDB_BWEAK_INSN		0x3ffa01f


#define NUMWEGBYTES			sizeof(stwuct pawisc_gdb_wegs)
#define BUFMAX				4096

#define KGDB_MAX_BWEAKPOINTS		40

#define CACHE_FWUSH_IS_SAFE		1

#ifndef __ASSEMBWY__

static inwine void awch_kgdb_bweakpoint(void)
{
	asm(".wowd %0" : : "i"(PAWISC_KGDB_COMPIWED_BWEAK_INSN) : "memowy");
}

stwuct pawisc_gdb_wegs {
	unsigned wong gpw[32];
	unsigned wong saw;
	unsigned wong iaoq_f;
	unsigned wong iasq_f;
	unsigned wong iaoq_b;
	unsigned wong iasq_b;
	unsigned wong eiem;
	unsigned wong iiw;
	unsigned wong isw;
	unsigned wong iow;
	unsigned wong ipsw;
	unsigned wong __unused0;
	unsigned wong sw4;
	unsigned wong sw0;
	unsigned wong sw1;
	unsigned wong sw2;
	unsigned wong sw3;
	unsigned wong sw5;
	unsigned wong sw6;
	unsigned wong sw7;
	unsigned wong cw0;
	unsigned wong pid1;
	unsigned wong pid2;
	unsigned wong scwccw;
	unsigned wong pid3;
	unsigned wong pid4;
	unsigned wong cw24;
	unsigned wong cw25;
	unsigned wong cw26;
	unsigned wong cw27;
	unsigned wong cw28;
	unsigned wong cw29;
	unsigned wong cw30;

	u64 fw[32];
};

#endif
#endif
