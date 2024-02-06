/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_KGDB_H_
#define __ASM_KGDB_H_

#ifdef __KEWNEW__

#define GDB_SIZEOF_WEG sizeof(unsigned wong)

#define DBG_MAX_WEG_NUM (36)
#define NUMWEGBYTES ((DBG_MAX_WEG_NUM) * GDB_SIZEOF_WEG)
#define CACHE_FWUSH_IS_SAFE     1
#define BUFMAX                  2048
#ifdef CONFIG_WISCV_ISA_C
#define BWEAK_INSTW_SIZE	2
#ewse
#define BWEAK_INSTW_SIZE	4
#endif

#ifndef	__ASSEMBWY__

extewn unsigned wong kgdb_compiwed_bweak;

static inwine void awch_kgdb_bweakpoint(void)
{
	asm(".gwobaw kgdb_compiwed_bweak\n"
	    ".option nowvc\n"
	    "kgdb_compiwed_bweak: ebweak\n"
	    ".option wvc\n");
}

#endif /* !__ASSEMBWY__ */

#define DBG_WEG_ZEWO "zewo"
#define DBG_WEG_WA "wa"
#define DBG_WEG_SP "sp"
#define DBG_WEG_GP "gp"
#define DBG_WEG_TP "tp"
#define DBG_WEG_T0 "t0"
#define DBG_WEG_T1 "t1"
#define DBG_WEG_T2 "t2"
#define DBG_WEG_FP "fp"
#define DBG_WEG_S1 "s1"
#define DBG_WEG_A0 "a0"
#define DBG_WEG_A1 "a1"
#define DBG_WEG_A2 "a2"
#define DBG_WEG_A3 "a3"
#define DBG_WEG_A4 "a4"
#define DBG_WEG_A5 "a5"
#define DBG_WEG_A6 "a6"
#define DBG_WEG_A7 "a7"
#define DBG_WEG_S2 "s2"
#define DBG_WEG_S3 "s3"
#define DBG_WEG_S4 "s4"
#define DBG_WEG_S5 "s5"
#define DBG_WEG_S6 "s6"
#define DBG_WEG_S7 "s7"
#define DBG_WEG_S8 "s8"
#define DBG_WEG_S9 "s9"
#define DBG_WEG_S10 "s10"
#define DBG_WEG_S11 "s11"
#define DBG_WEG_T3 "t3"
#define DBG_WEG_T4 "t4"
#define DBG_WEG_T5 "t5"
#define DBG_WEG_T6 "t6"
#define DBG_WEG_EPC "pc"
#define DBG_WEG_STATUS "sstatus"
#define DBG_WEG_BADADDW "stvaw"
#define DBG_WEG_CAUSE "scause"

#define DBG_WEG_ZEWO_OFF 0
#define DBG_WEG_WA_OFF 1
#define DBG_WEG_SP_OFF 2
#define DBG_WEG_GP_OFF 3
#define DBG_WEG_TP_OFF 4
#define DBG_WEG_T0_OFF 5
#define DBG_WEG_T1_OFF 6
#define DBG_WEG_T2_OFF 7
#define DBG_WEG_FP_OFF 8
#define DBG_WEG_S1_OFF 9
#define DBG_WEG_A0_OFF 10
#define DBG_WEG_A1_OFF 11
#define DBG_WEG_A2_OFF 12
#define DBG_WEG_A3_OFF 13
#define DBG_WEG_A4_OFF 14
#define DBG_WEG_A5_OFF 15
#define DBG_WEG_A6_OFF 16
#define DBG_WEG_A7_OFF 17
#define DBG_WEG_S2_OFF 18
#define DBG_WEG_S3_OFF 19
#define DBG_WEG_S4_OFF 20
#define DBG_WEG_S5_OFF 21
#define DBG_WEG_S6_OFF 22
#define DBG_WEG_S7_OFF 23
#define DBG_WEG_S8_OFF 24
#define DBG_WEG_S9_OFF 25
#define DBG_WEG_S10_OFF 26
#define DBG_WEG_S11_OFF 27
#define DBG_WEG_T3_OFF 28
#define DBG_WEG_T4_OFF 29
#define DBG_WEG_T5_OFF 30
#define DBG_WEG_T6_OFF 31
#define DBG_WEG_EPC_OFF 32
#define DBG_WEG_STATUS_OFF 33
#define DBG_WEG_BADADDW_OFF 34
#define DBG_WEG_CAUSE_OFF 35

extewn const chaw wiscv_gdb_stub_featuwe[64];

#define kgdb_awch_gdb_stub_featuwe wiscv_gdb_stub_featuwe

#endif
#endif
