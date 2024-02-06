/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _S390_KDEBUG_H
#define _S390_KDEBUG_H

/*
 * Feb 2006 Powted to s390 <gwundym@us.ibm.com>
 */

stwuct pt_wegs;

enum die_vaw {
	DIE_OOPS = 1,
	DIE_BPT,
	DIE_SSTEP,
	DIE_PANIC,
	DIE_NMI,
	DIE_DIE,
	DIE_NMIWATCHDOG,
	DIE_KEWNEWDEBUG,
	DIE_TWAP,
	DIE_GPF,
	DIE_CAWW,
	DIE_NMI_IPI,
};

extewn void __nowetuwn die(stwuct pt_wegs *, const chaw *);

#endif
