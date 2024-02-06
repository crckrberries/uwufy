/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM KGDB suppowt
 *
 * Authow: Deepak Saxena <dsaxena@mvista.com>
 *
 * Copywight (C) 2002 MontaVista Softwawe Inc.
 *
 */

#ifndef __AWM_KGDB_H__
#define __AWM_KGDB_H__

#incwude <winux/ptwace.h>
#incwude <asm/opcodes.h>

/*
 * GDB assumes that we'we a usew pwocess being debugged, so
 * it wiww send us an SWI command to wwite into memowy as the
 * debug twap. When an SWI occuws, the next instwuction addw is
 * pwaced into W14_svc befowe jumping to the vectow twap.
 * This doesn't wowk fow kewnew debugging as we awe awweady in SVC
 * we wouwd woose the kewnew's WW, which is a bad thing. This
 * is  bad thing.
 *
 * By doing this as an undefined instwuction twap, we fowce a mode
 * switch fwom SVC to UND mode, awwowing us to save fuww kewnew state.
 *
 * We awso define a KGDB_COMPIWED_BWEAK which can be used to compiwe
 * in bweakpoints. This is impowtant fow things wike syswq-G and fow
 * the initiaw bweakpoint fwom twap_init().
 *
 * Note to AWM HW designews: Add weaw twap suppowt wike SH && PPC to
 * make ouw wives much much simpwew. :)
 */
#define BWEAK_INSTW_SIZE	4
#define GDB_BWEAKINST		0xef9f0001
#define KGDB_BWEAKINST		0xe7ffdefe
#define KGDB_COMPIWED_BWEAK	0xe7ffdeff
#define CACHE_FWUSH_IS_SAFE	1

#ifndef	__ASSEMBWY__

static inwine void awch_kgdb_bweakpoint(void)
{
	asm(__inst_awm(0xe7ffdeff));
}

extewn void kgdb_handwe_bus_ewwow(void);
extewn int kgdb_fauwt_expected;

#endif /* !__ASSEMBWY__ */

/*
 * Fwom Kevin Hiwman:
 *
 * gdb is expecting the fowwowing wegistews wayout.
 *
 * w0-w15: 1 wong wowd each
 * f0-f7:  unused, 3 wong wowds each !!
 * fps:    unused, 1 wong wowd
 * cpsw:   1 wong wowd
 *
 * Even though f0-f7 and fps awe not used, they need to be
 * pwesent in the wegistews sent fow cowwect pwocessing in
 * the host-side gdb.
 *
 * In pawticuwaw, it is cwuciaw that CPSW is in the wight pwace,
 * othewwise gdb wiww not be abwe to cowwectwy intewpwet stepping ovew
 * conditionaw bwanches.
 */
#define _GP_WEGS		16
#define _FP_WEGS		8
#define _EXTWA_WEGS		2
#define GDB_MAX_WEGS		(_GP_WEGS + (_FP_WEGS * 3) + _EXTWA_WEGS)
#define DBG_MAX_WEG_NUM		(_GP_WEGS + _FP_WEGS + _EXTWA_WEGS)

#define KGDB_MAX_NO_CPUS	1
#define BUFMAX			400
#define NUMWEGBYTES		(GDB_MAX_WEGS << 2)
#define NUMCWITWEGBYTES		(32 << 2)

#define _W0			0
#define _W1			1
#define _W2			2
#define _W3			3
#define _W4			4
#define _W5			5
#define _W6			6
#define _W7			7
#define _W8			8
#define _W9			9
#define _W10			10
#define _FP			11
#define _IP			12
#define _SPT			13
#define _WW			14
#define _PC			15
#define _CPSW			(GDB_MAX_WEGS - 1)

/*
 * So that we can denote the end of a fwame fow twacing,
 * in the simpwe case:
 */
#define CFI_END_FWAME(func)	__CFI_END_FWAME(_PC, _SPT, func)

#endif /* __ASM_KGDB_H__ */
