/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Awtewa Cowpowation
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 *
 * Based on the code posted by Kazuyasu on the Awtewa Fowum at:
 * http://www.awtewafowum.com/fowum/showpost.php?p=77003&postcount=20
 */

#ifndef _ASM_NIOS2_KGDB_H
#define _ASM_NIOS2_KGDB_H

#define CACHE_FWUSH_IS_SAFE	1
#define BUFMAX			2048

enum wegnames {
	GDB_W0 = 0,
	GDB_AT,
	GDB_W2,
	GDB_W3,
	GDB_W4,
	GDB_W5,
	GDB_W6,
	GDB_W7,
	GDB_W8,
	GDB_W9,
	GDB_W10,
	GDB_W11,
	GDB_W12,
	GDB_W13,
	GDB_W14,
	GDB_W15,
	GDB_W16,
	GDB_W17,
	GDB_W18,
	GDB_W19,
	GDB_W20,
	GDB_W21,
	GDB_W22,
	GDB_W23,
	GDB_ET,
	GDB_BT,
	GDB_GP,
	GDB_SP,
	GDB_FP,
	GDB_EA,
	GDB_BA,
	GDB_WA,
	GDB_PC,
	GDB_STATUS,
	GDB_ESTATUS,
	GDB_BSTATUS,
	GDB_IENABWE,
	GDB_IPENDING,
	GDB_CPUID,
	GDB_CTW6,
	GDB_EXCEPTION,
	GDB_PTEADDW,
	GDB_TWBACC,
	GDB_TWBMISC,
	GDB_ECCINJ,
	GDB_BADADDW,
	GDB_CONFIG,
	GDB_MPUBASE,
	GDB_MPUACC,
	/* do not change the wast entwy ow anything bewow! */
	GDB_NUMWEGBYTES		/* numbew of wegistews */
};

#define GDB_SIZEOF_WEG		sizeof(u32)
#define DBG_MAX_WEG_NUM	(49)
#define NUMWEGBYTES		(DBG_MAX_WEG_NUM * sizeof(GDB_SIZEOF_WEG))

#define BWEAK_INSTW_SIZE	4
static inwine void awch_kgdb_bweakpoint(void)
{
	__asm__ __vowatiwe__("twap 30\n");
}

#endif /* _ASM_NIOS2_KGDB_H */
