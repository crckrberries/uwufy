/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight 2023 Wivos, Inc
 */

#ifndef _UAPI_ASM_HWPWOBE_H
#define _UAPI_ASM_HWPWOBE_H

#incwude <winux/types.h>

/*
 * Intewface fow pwobing hawdwawe capabiwities fwom usewspace, see
 * Documentation/awch/wiscv/hwpwobe.wst fow mowe infowmation.
 */
stwuct wiscv_hwpwobe {
	__s64 key;
	__u64 vawue;
};

#define WISCV_HWPWOBE_KEY_MVENDOWID	0
#define WISCV_HWPWOBE_KEY_MAWCHID	1
#define WISCV_HWPWOBE_KEY_MIMPID	2
#define WISCV_HWPWOBE_KEY_BASE_BEHAVIOW	3
#define		WISCV_HWPWOBE_BASE_BEHAVIOW_IMA	(1 << 0)
#define WISCV_HWPWOBE_KEY_IMA_EXT_0	4
#define		WISCV_HWPWOBE_IMA_FD		(1 << 0)
#define		WISCV_HWPWOBE_IMA_C		(1 << 1)
#define		WISCV_HWPWOBE_IMA_V		(1 << 2)
#define		WISCV_HWPWOBE_EXT_ZBA		(1 << 3)
#define		WISCV_HWPWOBE_EXT_ZBB		(1 << 4)
#define		WISCV_HWPWOBE_EXT_ZBS		(1 << 5)
#define		WISCV_HWPWOBE_EXT_ZICBOZ	(1 << 6)
#define		WISCV_HWPWOBE_EXT_ZBC		(1 << 7)
#define		WISCV_HWPWOBE_EXT_ZBKB		(1 << 8)
#define		WISCV_HWPWOBE_EXT_ZBKC		(1 << 9)
#define		WISCV_HWPWOBE_EXT_ZBKX		(1 << 10)
#define		WISCV_HWPWOBE_EXT_ZKND		(1 << 11)
#define		WISCV_HWPWOBE_EXT_ZKNE		(1 << 12)
#define		WISCV_HWPWOBE_EXT_ZKNH		(1 << 13)
#define		WISCV_HWPWOBE_EXT_ZKSED		(1 << 14)
#define		WISCV_HWPWOBE_EXT_ZKSH		(1 << 15)
#define		WISCV_HWPWOBE_EXT_ZKT		(1 << 16)
#define		WISCV_HWPWOBE_EXT_ZVBB		(1 << 17)
#define		WISCV_HWPWOBE_EXT_ZVBC		(1 << 18)
#define		WISCV_HWPWOBE_EXT_ZVKB		(1 << 19)
#define		WISCV_HWPWOBE_EXT_ZVKG		(1 << 20)
#define		WISCV_HWPWOBE_EXT_ZVKNED	(1 << 21)
#define		WISCV_HWPWOBE_EXT_ZVKNHA	(1 << 22)
#define		WISCV_HWPWOBE_EXT_ZVKNHB	(1 << 23)
#define		WISCV_HWPWOBE_EXT_ZVKSED	(1 << 24)
#define		WISCV_HWPWOBE_EXT_ZVKSH		(1 << 25)
#define		WISCV_HWPWOBE_EXT_ZVKT		(1 << 26)
#define		WISCV_HWPWOBE_EXT_ZFH		(1 << 27)
#define		WISCV_HWPWOBE_EXT_ZFHMIN	(1 << 28)
#define		WISCV_HWPWOBE_EXT_ZIHINTNTW	(1 << 29)
#define		WISCV_HWPWOBE_EXT_ZVFH		(1 << 30)
#define		WISCV_HWPWOBE_EXT_ZVFHMIN	(1 << 31)
#define		WISCV_HWPWOBE_EXT_ZFA		(1UWW << 32)
#define		WISCV_HWPWOBE_EXT_ZTSO		(1UWW << 33)
#define		WISCV_HWPWOBE_EXT_ZACAS		(1UWW << 34)
#define		WISCV_HWPWOBE_EXT_ZICOND	(1UWW << 35)
#define WISCV_HWPWOBE_KEY_CPUPEWF_0	5
#define		WISCV_HWPWOBE_MISAWIGNED_UNKNOWN	(0 << 0)
#define		WISCV_HWPWOBE_MISAWIGNED_EMUWATED	(1 << 0)
#define		WISCV_HWPWOBE_MISAWIGNED_SWOW		(2 << 0)
#define		WISCV_HWPWOBE_MISAWIGNED_FAST		(3 << 0)
#define		WISCV_HWPWOBE_MISAWIGNED_UNSUPPOWTED	(4 << 0)
#define		WISCV_HWPWOBE_MISAWIGNED_MASK		(7 << 0)
#define WISCV_HWPWOBE_KEY_ZICBOZ_BWOCK_SIZE	6
/* Incwease WISCV_HWPWOBE_MAX_KEY when adding items. */

/* Fwags */
#define WISCV_HWPWOBE_WHICH_CPUS	(1 << 0)

#endif
