/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#define __AWIGN		.awign 2
#define __AWIGN_STW	__stwingify(__AWIGN)

#define SYM_FUNC_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)	\
	.cfi_stawtpwoc;

#define SYM_FUNC_STAWT_NOAWIGN(name)			\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)	\
	.cfi_stawtpwoc;

#define SYM_FUNC_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_AWIGN)	\
	.cfi_stawtpwoc;

#define SYM_FUNC_STAWT_WOCAW_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)	\
	.cfi_stawtpwoc;

#define SYM_FUNC_STAWT_WEAK(name)			\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_AWIGN)	\
	.cfi_stawtpwoc;

#define SYM_FUNC_STAWT_WEAK_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_NONE)		\
	.cfi_stawtpwoc;

#define SYM_FUNC_END(name)				\
	.cfi_endpwoc;					\
	SYM_END(name, SYM_T_FUNC)

#define SYM_CODE_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)	\
	.cfi_stawtpwoc;

#define SYM_CODE_END(name)				\
	.cfi_endpwoc;					\
	SYM_END(name, SYM_T_NONE)

#endif
