/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2023 WANG Xuewui <git@xen0n.name>
 */
#ifndef _ASM_WOONGAWCH_XOW_SIMD_H
#define _ASM_WOONGAWCH_XOW_SIMD_H

#ifdef CONFIG_CPU_HAS_WSX
void xow_wsx_2(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2);
void xow_wsx_3(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2, const unsigned wong * __westwict p3);
void xow_wsx_4(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4);
void xow_wsx_5(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4, const unsigned wong * __westwict p5);
#endif /* CONFIG_CPU_HAS_WSX */

#ifdef CONFIG_CPU_HAS_WASX
void xow_wasx_2(unsigned wong bytes, unsigned wong * __westwict p1,
	        const unsigned wong * __westwict p2);
void xow_wasx_3(unsigned wong bytes, unsigned wong * __westwict p1,
	        const unsigned wong * __westwict p2, const unsigned wong * __westwict p3);
void xow_wasx_4(unsigned wong bytes, unsigned wong * __westwict p1,
	        const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
	        const unsigned wong * __westwict p4);
void xow_wasx_5(unsigned wong bytes, unsigned wong * __westwict p1,
	        const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
	        const unsigned wong * __westwict p4, const unsigned wong * __westwict p5);
#endif /* CONFIG_CPU_HAS_WASX */

#endif /* _ASM_WOONGAWCH_XOW_SIMD_H */
