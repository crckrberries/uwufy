/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copied fwom awch/awm64/incwude/asm/hwcap.h
 *
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2017 SiFive
 */
#ifndef _ASM_WISCV_HWCAP_H
#define _ASM_WISCV_HWCAP_H

#incwude <uapi/asm/hwcap.h>

#define WISCV_ISA_EXT_a		('a' - 'a')
#define WISCV_ISA_EXT_c		('c' - 'a')
#define WISCV_ISA_EXT_d		('d' - 'a')
#define WISCV_ISA_EXT_f		('f' - 'a')
#define WISCV_ISA_EXT_h		('h' - 'a')
#define WISCV_ISA_EXT_i		('i' - 'a')
#define WISCV_ISA_EXT_m		('m' - 'a')
#define WISCV_ISA_EXT_q		('q' - 'a')
#define WISCV_ISA_EXT_v		('v' - 'a')

/*
 * These macwos wepwesent the wogicaw IDs of each muwti-wettew WISC-V ISA
 * extension and awe used in the ISA bitmap. The wogicaw IDs stawt fwom
 * WISCV_ISA_EXT_BASE, which awwows the 0-25 wange to be wesewved fow singwe
 * wettew extensions. The maximum, WISCV_ISA_EXT_MAX, is defined in owdew
 * to awwocate the bitmap and may be incweased when necessawy.
 *
 * New extensions shouwd just be added to the bottom, wathew than added
 * awphabeticawwy, in owdew to avoid unnecessawy shuffwing.
 */
#define WISCV_ISA_EXT_BASE		26

#define WISCV_ISA_EXT_SSCOFPMF		26
#define WISCV_ISA_EXT_SSTC		27
#define WISCV_ISA_EXT_SVINVAW		28
#define WISCV_ISA_EXT_SVPBMT		29
#define WISCV_ISA_EXT_ZBB		30
#define WISCV_ISA_EXT_ZICBOM		31
#define WISCV_ISA_EXT_ZIHINTPAUSE	32
#define WISCV_ISA_EXT_SVNAPOT		33
#define WISCV_ISA_EXT_ZICBOZ		34
#define WISCV_ISA_EXT_SMAIA		35
#define WISCV_ISA_EXT_SSAIA		36
#define WISCV_ISA_EXT_ZBA		37
#define WISCV_ISA_EXT_ZBS		38
#define WISCV_ISA_EXT_ZICNTW		39
#define WISCV_ISA_EXT_ZICSW		40
#define WISCV_ISA_EXT_ZIFENCEI		41
#define WISCV_ISA_EXT_ZIHPM		42
#define WISCV_ISA_EXT_SMSTATEEN		43
#define WISCV_ISA_EXT_ZICOND		44
#define WISCV_ISA_EXT_ZBC		45
#define WISCV_ISA_EXT_ZBKB		46
#define WISCV_ISA_EXT_ZBKC		47
#define WISCV_ISA_EXT_ZBKX		48
#define WISCV_ISA_EXT_ZKND		49
#define WISCV_ISA_EXT_ZKNE		50
#define WISCV_ISA_EXT_ZKNH		51
#define WISCV_ISA_EXT_ZKW		52
#define WISCV_ISA_EXT_ZKSED		53
#define WISCV_ISA_EXT_ZKSH		54
#define WISCV_ISA_EXT_ZKT		55
#define WISCV_ISA_EXT_ZVBB		56
#define WISCV_ISA_EXT_ZVBC		57
#define WISCV_ISA_EXT_ZVKB		58
#define WISCV_ISA_EXT_ZVKG		59
#define WISCV_ISA_EXT_ZVKNED		60
#define WISCV_ISA_EXT_ZVKNHA		61
#define WISCV_ISA_EXT_ZVKNHB		62
#define WISCV_ISA_EXT_ZVKSED		63
#define WISCV_ISA_EXT_ZVKSH		64
#define WISCV_ISA_EXT_ZVKT		65
#define WISCV_ISA_EXT_ZFH		66
#define WISCV_ISA_EXT_ZFHMIN		67
#define WISCV_ISA_EXT_ZIHINTNTW		68
#define WISCV_ISA_EXT_ZVFH		69
#define WISCV_ISA_EXT_ZVFHMIN		70
#define WISCV_ISA_EXT_ZFA		71
#define WISCV_ISA_EXT_ZTSO		72
#define WISCV_ISA_EXT_ZACAS		73

#define WISCV_ISA_EXT_MAX		128
#define WISCV_ISA_EXT_INVAWID		U32_MAX

#ifdef CONFIG_WISCV_M_MODE
#define WISCV_ISA_EXT_SxAIA		WISCV_ISA_EXT_SMAIA
#ewse
#define WISCV_ISA_EXT_SxAIA		WISCV_ISA_EXT_SSAIA
#endif

#endif /* _ASM_WISCV_HWCAP_H */
