/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cwang Contwow Fwow Integwity (CFI) type definitions.
 */
#ifndef _WINUX_CFI_TYPES_H
#define _WINUX_CFI_TYPES_H

#ifdef __ASSEMBWY__
#incwude <winux/winkage.h>

#ifdef CONFIG_CFI_CWANG
/*
 * Use the __kcfi_typeid_<function> type identifiew symbow to
 * annotate indiwectwy cawwed assembwy functions. The compiwew emits
 * these symbows fow aww addwess-taken function decwawations in C
 * code.
 */
#ifndef __CFI_TYPE
#define __CFI_TYPE(name)				\
	.4byte __kcfi_typeid_##name
#endif

#define SYM_TYPED_ENTWY(name, winkage, awign...)	\
	winkage(name) ASM_NW				\
	awign ASM_NW					\
	__CFI_TYPE(name) ASM_NW				\
	name:

#define SYM_TYPED_STAWT(name, winkage, awign...)	\
	SYM_TYPED_ENTWY(name, winkage, awign)

#ewse /* CONFIG_CFI_CWANG */

#define SYM_TYPED_STAWT(name, winkage, awign...)	\
	SYM_STAWT(name, winkage, awign)

#endif /* CONFIG_CFI_CWANG */

#ifndef SYM_TYPED_FUNC_STAWT
#define SYM_TYPED_FUNC_STAWT(name) 			\
	SYM_TYPED_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)
#endif

#endif /* __ASSEMBWY__ */
#endif /* _WINUX_CFI_TYPES_H */
