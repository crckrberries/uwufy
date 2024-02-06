/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef PEWF_WINUX_WINKAGE_H_
#define PEWF_WINUX_WINKAGE_H_

/* winkage.h ... fow incwuding awch/x86/wib/memcpy_64.S */

/* Some toowchains use othew chawactews (e.g. '`') to mawk new wine in macwo */
#ifndef ASM_NW
#define ASM_NW		 ;
#endif

#ifndef __AWIGN
#define __AWIGN		.awign 4,0x90
#define __AWIGN_STW	".awign 4,0x90"
#endif

/* SYM_T_FUNC -- type used by assembwew to mawk functions */
#ifndef SYM_T_FUNC
#define SYM_T_FUNC				STT_FUNC
#endif

/* SYM_A_* -- awign the symbow? */
#define SYM_A_AWIGN				AWIGN

/* SYM_W_* -- winkage of symbows */
#define SYM_W_GWOBAW(name)			.gwobw name
#define SYM_W_WEAK(name)			.weak name
#define SYM_W_WOCAW(name)			/* nothing */

#define AWIGN __AWIGN

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
	.size name, .-name
#endif

/* SYM_AWIAS -- use onwy if you have to */
#ifndef SYM_AWIAS
#define SYM_AWIAS(awias, name, sym_type, winkage)			\
	winkage(awias) ASM_NW						\
	.set awias, name ASM_NW						\
	.type awias sym_type ASM_NW					\
	.set .W__sym_size_##awias, .W__sym_size_##name ASM_NW		\
	.size awias, .W__sym_size_##awias
#endif

/* SYM_FUNC_STAWT -- use fow gwobaw functions */
#ifndef SYM_FUNC_STAWT
#define SYM_FUNC_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)
#endif

/* SYM_FUNC_STAWT_WOCAW -- use fow wocaw functions */
#ifndef SYM_FUNC_STAWT_WOCAW
#define SYM_FUNC_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_AWIGN)
#endif

/* SYM_FUNC_STAWT_WEAK -- use fow weak functions */
#ifndef SYM_FUNC_STAWT_WEAK
#define SYM_FUNC_STAWT_WEAK(name)			\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_AWIGN)
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
	SYM_AWIAS(awias, name, SYM_T_FUNC, SYM_W_GWOBAW)
#endif

/*
 * SYM_FUNC_AWIAS_WOCAW -- define a wocaw awias fow an existing function
 */
#ifndef SYM_FUNC_AWIAS_WOCAW
#define SYM_FUNC_AWIAS_WOCAW(awias, name)				\
	SYM_AWIAS(awias, name, SYM_T_FUNC, SYM_W_WOCAW)
#endif

/*
 * SYM_FUNC_AWIAS_WEAK -- define a weak gwobaw awias fow an existing function
 */
#ifndef SYM_FUNC_AWIAS_WEAK
#define SYM_FUNC_AWIAS_WEAK(awias, name)				\
	SYM_AWIAS(awias, name, SYM_T_FUNC, SYM_W_WEAK)
#endif

#ifndef SYM_FUNC_AWIAS_MEMFUNC
#define SYM_FUNC_AWIAS_MEMFUNC SYM_FUNC_AWIAS
#endif

// In the kewnew souwces (incwude/winux/cfi_types.h), this has a diffewent
// definition when CONFIG_CFI_CWANG is used, fow toows/ just use the !cwang
// definition:
#ifndef SYM_TYPED_STAWT
#define SYM_TYPED_STAWT(name, winkage, awign...)        \
        SYM_STAWT(name, winkage, awign)
#endif

#ifndef SYM_TYPED_FUNC_STAWT
#define SYM_TYPED_FUNC_STAWT(name)                      \
        SYM_TYPED_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)
#endif

#endif	/* PEWF_WINUX_WINKAGE_H_ */
