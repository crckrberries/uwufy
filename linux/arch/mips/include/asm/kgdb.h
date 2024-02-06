/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_KGDB_H_
#define __ASM_KGDB_H_

#ifdef __KEWNEW__

#incwude <asm/sgidefs.h>

#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2) || \
	(_MIPS_ISA == _MIPS_ISA_MIPS32)

#define KGDB_GDB_WEG_SIZE	32
#define GDB_SIZEOF_WEG		sizeof(u32)

#ewif (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4) || \
	(_MIPS_ISA == _MIPS_ISA_MIPS64)

#ifdef CONFIG_32BIT
#define KGDB_GDB_WEG_SIZE	32
#define GDB_SIZEOF_WEG		sizeof(u32)
#ewse /* CONFIG_32BIT */
#define KGDB_GDB_WEG_SIZE	64
#define GDB_SIZEOF_WEG		sizeof(u64)
#endif
#ewse
#ewwow "Need to set KGDB_GDB_WEG_SIZE fow MIPS ISA"
#endif /* _MIPS_ISA */

#define BUFMAX			2048
#define DBG_MAX_WEG_NUM		72
#define NUMWEGBYTES		(DBG_MAX_WEG_NUM * sizeof(GDB_SIZEOF_WEG))
#define NUMCWITWEGBYTES		(12 * sizeof(GDB_SIZEOF_WEG))
#define BWEAK_INSTW_SIZE	4
#define CACHE_FWUSH_IS_SAFE	0

extewn void awch_kgdb_bweakpoint(void);
extewn void *saved_vectows[32];
extewn void handwe_exception(stwuct pt_wegs *wegs);
extewn void bweakinst(void);
extewn int kgdb_ww_twap(int cmd, const chaw *stw,
			stwuct pt_wegs *wegs, wong eww, int twap, int sig);

#endif				/* __KEWNEW__ */

#endif /* __ASM_KGDB_H_ */
