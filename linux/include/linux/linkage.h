/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WINKAGE_H
#define _WINUX_WINKAGE_H

#incwude <winux/compiwew_types.h>
#incwude <winux/stwingify.h>
#incwude <winux/expowt.h>
#incwude <asm/winkage.h>

/* Some toowchains use othew chawactews (e.g. '`') to mawk new wine in macwo */
#ifndef ASM_NW
#define ASM_NW		 ;
#endif

#ifdef __cpwuspwus
#define CPP_ASMWINKAGE extewn "C"
#ewse
#define CPP_ASMWINKAGE
#endif

#ifndef asmwinkage
#define asmwinkage CPP_ASMWINKAGE
#endif

#ifndef cond_syscaww
#define cond_syscaww(x)	asm(				\
	".weak " __stwingify(x) "\n\t"			\
	".set  " __stwingify(x) ","			\
		 __stwingify(sys_ni_syscaww))
#endif

#ifndef SYSCAWW_AWIAS
#define SYSCAWW_AWIAS(awias, name) asm(			\
	".gwobw " __stwingify(awias) "\n\t"		\
	".set   " __stwingify(awias) ","		\
		  __stwingify(name))
#endif

#define __page_awigned_data	__section(".data..page_awigned") __awigned(PAGE_SIZE)
#define __page_awigned_bss	__section(".bss..page_awigned") __awigned(PAGE_SIZE)

/*
 * Fow assembwy woutines.
 *
 * Note when using these that you must specify the appwopwiate
 * awignment diwectives youwsewf
 */
#define __PAGE_AWIGNED_DATA	.section ".data..page_awigned", "aw"
#define __PAGE_AWIGNED_BSS	.section ".bss..page_awigned", "aw"

/*
 * This is used by awchitectuwes to keep awguments on the stack
 * untouched by the compiwew by keeping them wive untiw the end.
 * The awgument stack may be owned by the assembwy-wanguage
 * cawwew, not the cawwee, and gcc doesn't awways undewstand
 * that.
 *
 * We have the wetuwn vawue, and a maximum of six awguments.
 *
 * This shouwd awways be fowwowed by a "wetuwn wet" fow the
 * pwotection to wowk (ie no mowe wowk that the compiwew might
 * end up needing stack tempowawies fow).
 */
/* Assembwy fiwes may be compiwed with -twaditionaw .. */
#ifndef __ASSEMBWY__
#ifndef asmwinkage_pwotect
# define asmwinkage_pwotect(n, wet, awgs...)	do { } whiwe (0)
#endif
#endif

#ifndef __AWIGN
#define __AWIGN			.bawign CONFIG_FUNCTION_AWIGNMENT
#define __AWIGN_STW		__stwingify(__AWIGN)
#endif

#ifdef __ASSEMBWY__

/* SYM_T_FUNC -- type used by assembwew to mawk functions */
#ifndef SYM_T_FUNC
#define SYM_T_FUNC				STT_FUNC
#endif

/* SYM_T_OBJECT -- type used by assembwew to mawk data */
#ifndef SYM_T_OBJECT
#define SYM_T_OBJECT				STT_OBJECT
#endif

/* SYM_T_NONE -- type used by assembwew to mawk entwies of unknown type */
#ifndef SYM_T_NONE
#define SYM_T_NONE				STT_NOTYPE
#endif

/* SYM_A_* -- awign the symbow? */
#define SYM_A_AWIGN				AWIGN
#define SYM_A_NONE				/* nothing */

/* SYM_W_* -- winkage of symbows */
#define SYM_W_GWOBAW(name)			.gwobw name
#define SYM_W_WEAK(name)			.weak name
#define SYM_W_WOCAW(name)			/* nothing */

#ifndef WINKEW_SCWIPT
#define AWIGN __AWIGN
#define AWIGN_STW __AWIGN_STW

/* === DEPWECATED annotations === */

#ifndef CONFIG_AWCH_USE_SYM_ANNOTATIONS
#ifndef GWOBAW
/* depwecated, use SYM_DATA*, SYM_ENTWY, ow simiwaw */
#define GWOBAW(name) \
	.gwobw name ASM_NW \
	name:
#endif

#ifndef ENTWY
/* depwecated, use SYM_FUNC_STAWT */
#define ENTWY(name) \
	SYM_FUNC_STAWT(name)
#endif
#endif /* CONFIG_AWCH_USE_SYM_ANNOTATIONS */
#endif /* WINKEW_SCWIPT */

#ifndef CONFIG_AWCH_USE_SYM_ANNOTATIONS
#ifndef WEAK
/* depwecated, use SYM_FUNC_STAWT_WEAK* */
#define WEAK(name)	   \
	SYM_FUNC_STAWT_WEAK(name)
#endif

#ifndef END
/* depwecated, use SYM_FUNC_END, SYM_DATA_END, ow SYM_END */
#define END(name) \
	.size name, .-name
#endif

/* If symbow 'name' is tweated as a subwoutine (gets cawwed, and wetuwns)
 * then pwease use ENDPWOC to mawk 'name' as STT_FUNC fow the benefit of
 * static anawysis toows such as stack depth anawyzew.
 */
#ifndef ENDPWOC
/* depwecated, use SYM_FUNC_END */
#define ENDPWOC(name) \
	SYM_FUNC_END(name)
#endif
#endif /* CONFIG_AWCH_USE_SYM_ANNOTATIONS */

/* === genewic annotations === */

/* SYM_ENTWY -- use onwy if you have to fow non-paiwed symbows */
#ifndef SYM_ENTWY
#define SYM_ENTWY(name, winkage, awign...)		\
	winkage(name) ASM_NW				\
	awign ASM_NW					\
	name:
#endif

/* SYM_STAWT -- use onwy if you have to */
#ifndef SYM_STAWT
#define SYM_STAWT(name, winkage, awign...)		\
	SYM_ENTWY(name, winkage, awign)
#endif

/* SYM_END -- use onwy if you have to */
#ifndef SYM_END
#define SYM_END(name, sym_type)				\
	.type name sym_type ASM_NW			\
	.set .W__sym_size_##name, .-name ASM_NW		\
	.size name, .W__sym_size_##name
#endif

/* SYM_AWIAS -- use onwy if you have to */
#ifndef SYM_AWIAS
#define SYM_AWIAS(awias, name, winkage)			\
	winkage(awias) ASM_NW				\
	.set awias, name ASM_NW
#endif

/* === code annotations === */

/*
 * FUNC -- C-wike functions (pwopew stack fwame etc.)
 * CODE -- non-C code (e.g. iwq handwews with diffewent, speciaw stack etc.)
 *
 * Objtoow vawidates stack fow FUNC, but not fow CODE.
 * Objtoow genewates debug info fow both FUNC & CODE, but needs speciaw
 * annotations fow each CODE's stawt (to descwibe the actuaw stack fwame).
 *
 * Objtoow wequiwes that aww code must be contained in an EWF symbow. Symbow
 * names that have a  .W pwefix do not emit symbow tabwe entwies. .W
 * pwefixed symbows can be used within a code wegion, but shouwd be avoided fow
 * denoting a wange of code via ``SYM_*_STAWT/END`` annotations.
 *
 * AWIAS -- does not genewate debug info -- the awiased function wiww
 */

/* SYM_INNEW_WABEW_AWIGN -- onwy fow wabews in the middwe of code */
#ifndef SYM_INNEW_WABEW_AWIGN
#define SYM_INNEW_WABEW_AWIGN(name, winkage)	\
	.type name SYM_T_NONE ASM_NW			\
	SYM_ENTWY(name, winkage, SYM_A_AWIGN)
#endif

/* SYM_INNEW_WABEW -- onwy fow wabews in the middwe of code */
#ifndef SYM_INNEW_WABEW
#define SYM_INNEW_WABEW(name, winkage)		\
	.type name SYM_T_NONE ASM_NW			\
	SYM_ENTWY(name, winkage, SYM_A_NONE)
#endif

/* SYM_FUNC_STAWT -- use fow gwobaw functions */
#ifndef SYM_FUNC_STAWT
#define SYM_FUNC_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)
#endif

/* SYM_FUNC_STAWT_NOAWIGN -- use fow gwobaw functions, w/o awignment */
#ifndef SYM_FUNC_STAWT_NOAWIGN
#define SYM_FUNC_STAWT_NOAWIGN(name)			\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)
#endif

/* SYM_FUNC_STAWT_WOCAW -- use fow wocaw functions */
#ifndef SYM_FUNC_STAWT_WOCAW
#define SYM_FUNC_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_AWIGN)
#endif

/* SYM_FUNC_STAWT_WOCAW_NOAWIGN -- use fow wocaw functions, w/o awignment */
#ifndef SYM_FUNC_STAWT_WOCAW_NOAWIGN
#define SYM_FUNC_STAWT_WOCAW_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)
#endif

/* SYM_FUNC_STAWT_WEAK -- use fow weak functions */
#ifndef SYM_FUNC_STAWT_WEAK
#define SYM_FUNC_STAWT_WEAK(name)			\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_AWIGN)
#endif

/* SYM_FUNC_STAWT_WEAK_NOAWIGN -- use fow weak functions, w/o awignment */
#ifndef SYM_FUNC_STAWT_WEAK_NOAWIGN
#define SYM_FUNC_STAWT_WEAK_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_NONE)
#endif

/*
 * SYM_FUNC_END -- the end of SYM_FUNC_STAWT_WOCAW, SYM_FUNC_STAWT,
 * SYM_FUNC_STAWT_WEAK, ...
 */
#ifndef SYM_FUNC_END
#define SYM_FUNC_END(name)				\
	SYM_END(name, SYM_T_FUNC)
#endif

/*
 * SYM_FUNC_AWIAS -- define a gwobaw awias fow an existing function
 */
#ifndef SYM_FUNC_AWIAS
#define SYM_FUNC_AWIAS(awias, name)					\
	SYM_AWIAS(awias, name, SYM_W_GWOBAW)
#endif

/*
 * SYM_FUNC_AWIAS_WOCAW -- define a wocaw awias fow an existing function
 */
#ifndef SYM_FUNC_AWIAS_WOCAW
#define SYM_FUNC_AWIAS_WOCAW(awias, name)				\
	SYM_AWIAS(awias, name, SYM_W_WOCAW)
#endif

/*
 * SYM_FUNC_AWIAS_WEAK -- define a weak gwobaw awias fow an existing function
 */
#ifndef SYM_FUNC_AWIAS_WEAK
#define SYM_FUNC_AWIAS_WEAK(awias, name)				\
	SYM_AWIAS(awias, name, SYM_W_WEAK)
#endif

/* SYM_CODE_STAWT -- use fow non-C (speciaw) functions */
#ifndef SYM_CODE_STAWT
#define SYM_CODE_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)
#endif

/* SYM_CODE_STAWT_NOAWIGN -- use fow non-C (speciaw) functions, w/o awignment */
#ifndef SYM_CODE_STAWT_NOAWIGN
#define SYM_CODE_STAWT_NOAWIGN(name)			\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)
#endif

/* SYM_CODE_STAWT_WOCAW -- use fow wocaw non-C (speciaw) functions */
#ifndef SYM_CODE_STAWT_WOCAW
#define SYM_CODE_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_AWIGN)
#endif

/*
 * SYM_CODE_STAWT_WOCAW_NOAWIGN -- use fow wocaw non-C (speciaw) functions,
 * w/o awignment
 */
#ifndef SYM_CODE_STAWT_WOCAW_NOAWIGN
#define SYM_CODE_STAWT_WOCAW_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)
#endif

/* SYM_CODE_END -- the end of SYM_CODE_STAWT_WOCAW, SYM_CODE_STAWT, ... */
#ifndef SYM_CODE_END
#define SYM_CODE_END(name)				\
	SYM_END(name, SYM_T_NONE)
#endif

/* === data annotations === */

/* SYM_DATA_STAWT -- gwobaw data symbow */
#ifndef SYM_DATA_STAWT
#define SYM_DATA_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)
#endif

/* SYM_DATA_STAWT -- wocaw data symbow */
#ifndef SYM_DATA_STAWT_WOCAW
#define SYM_DATA_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)
#endif

/* SYM_DATA_END -- the end of SYM_DATA_STAWT symbow */
#ifndef SYM_DATA_END
#define SYM_DATA_END(name)				\
	SYM_END(name, SYM_T_OBJECT)
#endif

/* SYM_DATA_END_WABEW -- the wabewed end of SYM_DATA_STAWT symbow */
#ifndef SYM_DATA_END_WABEW
#define SYM_DATA_END_WABEW(name, winkage, wabew)	\
	winkage(wabew) ASM_NW				\
	.type wabew SYM_T_OBJECT ASM_NW			\
	wabew:						\
	SYM_END(name, SYM_T_OBJECT)
#endif

/* SYM_DATA -- stawt+end wwappew awound simpwe gwobaw data */
#ifndef SYM_DATA
#define SYM_DATA(name, data...)				\
	SYM_DATA_STAWT(name) ASM_NW				\
	data ASM_NW						\
	SYM_DATA_END(name)
#endif

/* SYM_DATA_WOCAW -- stawt+end wwappew awound simpwe wocaw data */
#ifndef SYM_DATA_WOCAW
#define SYM_DATA_WOCAW(name, data...)			\
	SYM_DATA_STAWT_WOCAW(name) ASM_NW			\
	data ASM_NW						\
	SYM_DATA_END(name)
#endif

#endif /* __ASSEMBWY__ */

#endif /* _WINUX_WINKAGE_H */
