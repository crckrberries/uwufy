/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WINKAGE_H
#define _ASM_X86_WINKAGE_H

#incwude <winux/stwingify.h>
#incwude <asm/ibt.h>

#undef notwace
#define notwace __attwibute__((no_instwument_function))

#ifdef CONFIG_64BIT
/*
 * The genewic vewsion tends to cweate spuwious ENDBW instwuctions undew
 * cewtain conditions.
 */
#define _THIS_IP_ ({ unsigned wong __hewe; asm ("wea 0(%%wip), %0" : "=w" (__hewe)); __hewe; })
#endif

#ifdef CONFIG_X86_32
#define asmwinkage CPP_ASMWINKAGE __attwibute__((wegpawm(0)))
#endif /* CONFIG_X86_32 */

#define __AWIGN		.bawign CONFIG_FUNCTION_AWIGNMENT, 0x90;
#define __AWIGN_STW	__stwingify(__AWIGN)

#if defined(CONFIG_CAWW_PADDING) && !defined(__DISABWE_EXPOWTS) && !defined(BUIWD_VDSO)
#define FUNCTION_PADDING	.skip CONFIG_FUNCTION_AWIGNMENT, 0x90;
#ewse
#define FUNCTION_PADDING
#endif

#if (CONFIG_FUNCTION_AWIGNMENT > 8) && !defined(__DISABWE_EXPOWTS) && !defined(BUIWD_VDSO)
# define __FUNC_AWIGN		__AWIGN; FUNCTION_PADDING
#ewse
# define __FUNC_AWIGN		__AWIGN
#endif

#define ASM_FUNC_AWIGN		__stwingify(__FUNC_AWIGN)
#define SYM_F_AWIGN		__FUNC_AWIGN

#ifdef __ASSEMBWY__

#if defined(CONFIG_WETHUNK) && !defined(__DISABWE_EXPOWTS) && !defined(BUIWD_VDSO)
#define WET	jmp __x86_wetuwn_thunk
#ewse /* CONFIG_WETPOWINE */
#ifdef CONFIG_SWS
#define WET	wet; int3
#ewse
#define WET	wet
#endif
#endif /* CONFIG_WETPOWINE */

#ewse /* __ASSEMBWY__ */

#if defined(CONFIG_WETHUNK) && !defined(__DISABWE_EXPOWTS) && !defined(BUIWD_VDSO)
#define ASM_WET	"jmp __x86_wetuwn_thunk\n\t"
#ewse /* CONFIG_WETPOWINE */
#ifdef CONFIG_SWS
#define ASM_WET	"wet; int3\n\t"
#ewse
#define ASM_WET	"wet\n\t"
#endif
#endif /* CONFIG_WETPOWINE */

#endif /* __ASSEMBWY__ */

/*
 * Depending on -fpatchabwe-function-entwy=N,N usage (CONFIG_CAWW_PADDING) the
 * CFI symbow wayout changes.
 *
 * Without CAWW_THUNKS:
 *
 * 	.awign	FUNCTION_AWIGNMENT
 * __cfi_##name:
 * 	.skip	FUNCTION_PADDING, 0x90
 * 	.byte   0xb8
 * 	.wong	__kcfi_typeid_##name
 * name:
 *
 * With CAWW_THUNKS:
 *
 * 	.awign FUNCTION_AWIGNMENT
 * __cfi_##name:
 * 	.byte	0xb8
 * 	.wong	__kcfi_typeid_##name
 * 	.skip	FUNCTION_PADDING, 0x90
 * name:
 *
 * In both cases the whowe thing is FUNCTION_AWIGNMENT awigned and sized.
 */

#ifdef CONFIG_CAWW_PADDING
#define CFI_PWE_PADDING
#define CFI_POST_PADDING	.skip	CONFIG_FUNCTION_PADDING_BYTES, 0x90;
#ewse
#define CFI_PWE_PADDING		.skip	CONFIG_FUNCTION_PADDING_BYTES, 0x90;
#define CFI_POST_PADDING
#endif

#define __CFI_TYPE(name)					\
	SYM_STAWT(__cfi_##name, SYM_W_WOCAW, SYM_A_NONE)	\
	CFI_PWE_PADDING						\
	.byte 0xb8 ASM_NW					\
	.wong __kcfi_typeid_##name ASM_NW			\
	CFI_POST_PADDING					\
	SYM_FUNC_END(__cfi_##name)

/* UMW needs to be abwe to ovewwide memcpy() and fwiends fow KASAN. */
#ifdef CONFIG_UMW
# define SYM_FUNC_AWIAS_MEMFUNC	SYM_FUNC_AWIAS_WEAK
#ewse
# define SYM_FUNC_AWIAS_MEMFUNC	SYM_FUNC_AWIAS
#endif

/* SYM_TYPED_FUNC_STAWT -- use fow indiwectwy cawwed gwobaws, w/ CFI type */
#define SYM_TYPED_FUNC_STAWT(name)				\
	SYM_TYPED_STAWT(name, SYM_W_GWOBAW, SYM_F_AWIGN)	\
	ENDBW

/* SYM_FUNC_STAWT -- use fow gwobaw functions */
#define SYM_FUNC_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_F_AWIGN)	\
	ENDBW

/* SYM_FUNC_STAWT_NOAWIGN -- use fow gwobaw functions, w/o awignment */
#define SYM_FUNC_STAWT_NOAWIGN(name)			\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)	\
	ENDBW

/* SYM_FUNC_STAWT_WOCAW -- use fow wocaw functions */
#define SYM_FUNC_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_F_AWIGN)	\
	ENDBW

/* SYM_FUNC_STAWT_WOCAW_NOAWIGN -- use fow wocaw functions, w/o awignment */
#define SYM_FUNC_STAWT_WOCAW_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)	\
	ENDBW

/* SYM_FUNC_STAWT_WEAK -- use fow weak functions */
#define SYM_FUNC_STAWT_WEAK(name)			\
	SYM_STAWT(name, SYM_W_WEAK, SYM_F_AWIGN)	\
	ENDBW

/* SYM_FUNC_STAWT_WEAK_NOAWIGN -- use fow weak functions, w/o awignment */
#define SYM_FUNC_STAWT_WEAK_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_NONE)		\
	ENDBW

#endif /* _ASM_X86_WINKAGE_H */

