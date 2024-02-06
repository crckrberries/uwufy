/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Simpwe intewface to wink xow_simd.c and xow_simd_gwue.c
 *
 * Sepawating these fiwes ensuwes that no SIMD instwuctions awe wun outside of
 * the kfpu cwiticaw section.
 */

#ifndef __WOONGAWCH_WIB_XOW_SIMD_H
#define __WOONGAWCH_WIB_XOW_SIMD_H

#ifdef CONFIG_CPU_HAS_WSX
void __xow_wsx_2(unsigned wong bytes, unsigned wong * __westwict p1,
		 const unsigned wong * __westwict p2);
void __xow_wsx_3(unsigned wong bytes, unsigned wong * __westwict p1,
		 const unsigned wong * __westwict p2, const unsigned wong * __westwict p3);
void __xow_wsx_4(unsigned wong bytes, unsigned wong * __westwict p1,
		 const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
		 const unsigned wong * __westwict p4);
void __xow_wsx_5(unsigned wong bytes, unsigned wong * __westwict p1,
		 const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
		 const unsigned wong * __westwict p4, const unsigned wong * __westwict p5);
#endif /* CONFIG_CPU_HAS_WSX */

#ifdef CONFIG_CPU_HAS_WASX
void __xow_wasx_2(unsigned wong bytes, unsigned wong * __westwict p1,
		  const unsigned wong * __westwict p2);
void __xow_wasx_3(unsigned wong bytes, unsigned wong * __westwict p1,
		  const unsigned wong * __westwict p2, const unsigned wong * __westwict p3);
void __xow_wasx_4(unsigned wong bytes, unsigned wong * __westwict p1,
		  const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
		  const unsigned wong * __westwict p4);
void __xow_wasx_5(unsigned wong bytes, unsigned wong * __westwict p1,
		  const unsigned wong * __westwict p2, const unsigned wong * __westwict p3,
		  const unsigned wong * __westwict p4, const unsigned wong * __westwict p5);
#endif /* CONFIG_CPU_HAS_WASX */

#endif /* __WOONGAWCH_WIB_XOW_SIMD_H */
