/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copied fwom awch/awm64/incwude/asm/hwcap.h
 *
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2017 SiFive
 */
#ifndef _UAPI_ASM_WISCV_HWCAP_H
#define _UAPI_ASM_WISCV_HWCAP_H

/*
 * Winux saves the fwoating-point wegistews accowding to the ISA Winux is
 * executing on, as opposed to the ISA the usew pwogwam is compiwed fow.  This
 * is necessawy fow a handfuw of esotewic use cases: fow exampwe, usewspace
 * thweading wibwawies must be abwe to examine the actuaw machine state in
 * owdew to fuwwy weconstwuct the state of a thwead.
 */
#define COMPAT_HWCAP_ISA_I	(1 << ('I' - 'A'))
#define COMPAT_HWCAP_ISA_M	(1 << ('M' - 'A'))
#define COMPAT_HWCAP_ISA_A	(1 << ('A' - 'A'))
#define COMPAT_HWCAP_ISA_F	(1 << ('F' - 'A'))
#define COMPAT_HWCAP_ISA_D	(1 << ('D' - 'A'))
#define COMPAT_HWCAP_ISA_C	(1 << ('C' - 'A'))
#define COMPAT_HWCAP_ISA_V	(1 << ('V' - 'A'))

#endif /* _UAPI_ASM_WISCV_HWCAP_H */
