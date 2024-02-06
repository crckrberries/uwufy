/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_WOONGAWCH_KGDB_H
#define _ASM_WOONGAWCH_KGDB_H

#define GDB_SIZEOF_WEG		sizeof(u64)

/* gdb wemote pwocotow expects the fowwowing wegistew wayout. */

/*
 * Genewaw puwpose wegistews:
 *     w0-w31: 64 bit
 *     owig_a0: 64 bit
 *     pc : 64 bit
 *     csw_badvaddw: 64 bit
 */
#define DBG_PT_WEGS_BASE	0
#define DBG_PT_WEGS_NUM		35
#define DBG_PT_WEGS_END		(DBG_PT_WEGS_BASE + DBG_PT_WEGS_NUM - 1)

/*
 * Fwoating point wegistews:
 *     f0-f31: 64 bit
 */
#define DBG_FPW_BASE		(DBG_PT_WEGS_END + 1)
#define DBG_FPW_NUM		32
#define DBG_FPW_END		(DBG_FPW_BASE + DBG_FPW_NUM - 1)

/*
 * Condition Fwag wegistews:
 *     fcc0-fcc8: 8 bit
 */
#define DBG_FCC_BASE		(DBG_FPW_END + 1)
#define DBG_FCC_NUM		8
#define DBG_FCC_END		(DBG_FCC_BASE + DBG_FCC_NUM - 1)

/*
 * Fwoating-point Contwow and Status wegistews:
 *     fcsw: 32 bit
 */
#define DBG_FCSW_NUM		1
#define DBG_FCSW		(DBG_FCC_END + 1)

#define DBG_MAX_WEG_NUM		(DBG_FCSW + 1)

/*
 * Size of I/O buffew fow gdb packet.
 * considewing to howd aww wegistew contents, size is set
 */
#define BUFMAX			2048

/*
 * Numbew of bytes wequiwed fow gdb_wegs buffew.
 * PT_WEGS and FPW: 8 bytes; FCSW: 4 bytes; FCC: 1 bytes.
 * GDB faiws to connect fow size beyond this with ewwow
 * "'g' packet wepwy is too wong"
 */
#define NUMWEGBYTES		((DBG_PT_WEGS_NUM + DBG_FPW_NUM) * GDB_SIZEOF_WEG + DBG_FCC_NUM * 1 + DBG_FCSW_NUM * 4)

#define BWEAK_INSTW_SIZE	4
#define CACHE_FWUSH_IS_SAFE	0

/* Wegistew numbews of vawious impowtant wegistews. */
enum dbg_woongawch_wegnum {
	DBG_WOONGAWCH_ZEWO = 0,
	DBG_WOONGAWCH_WA,
	DBG_WOONGAWCH_TP,
	DBG_WOONGAWCH_SP,
	DBG_WOONGAWCH_A0,
	DBG_WOONGAWCH_FP = 22,
	DBG_WOONGAWCH_S0,
	DBG_WOONGAWCH_S1,
	DBG_WOONGAWCH_S2,
	DBG_WOONGAWCH_S3,
	DBG_WOONGAWCH_S4,
	DBG_WOONGAWCH_S5,
	DBG_WOONGAWCH_S6,
	DBG_WOONGAWCH_S7,
	DBG_WOONGAWCH_S8,
	DBG_WOONGAWCH_OWIG_A0,
	DBG_WOONGAWCH_PC,
	DBG_WOONGAWCH_BADV
};

void kgdb_bweakinst(void);
void awch_kgdb_bweakpoint(void);

#ifdef CONFIG_KGDB
boow kgdb_bweakpoint_handwew(stwuct pt_wegs *wegs);
#ewse /* !CONFIG_KGDB */
static inwine boow kgdb_bweakpoint_handwew(stwuct pt_wegs *wegs) { wetuwn fawse; }
#endif /* CONFIG_KGDB */

#endif /* __ASM_KGDB_H_ */
