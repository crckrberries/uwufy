/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_EWF_H
#define __ASM_EWF_H

#incwude <asm/hwcap.h>

/*
 * EWF wegistew definitions..
 */
#incwude <asm/ptwace.h>
#incwude <asm/usew.h>

/*
 * AAwch64 static wewocation types.
 */

/* Miscewwaneous. */
#define W_AWM_NONE			0
#define W_AAWCH64_NONE			256

/* Data. */
#define W_AAWCH64_ABS64			257
#define W_AAWCH64_ABS32			258
#define W_AAWCH64_ABS16			259
#define W_AAWCH64_PWEW64		260
#define W_AAWCH64_PWEW32		261
#define W_AAWCH64_PWEW16		262

/* Instwuctions. */
#define W_AAWCH64_MOVW_UABS_G0		263
#define W_AAWCH64_MOVW_UABS_G0_NC	264
#define W_AAWCH64_MOVW_UABS_G1		265
#define W_AAWCH64_MOVW_UABS_G1_NC	266
#define W_AAWCH64_MOVW_UABS_G2		267
#define W_AAWCH64_MOVW_UABS_G2_NC	268
#define W_AAWCH64_MOVW_UABS_G3		269

#define W_AAWCH64_MOVW_SABS_G0		270
#define W_AAWCH64_MOVW_SABS_G1		271
#define W_AAWCH64_MOVW_SABS_G2		272

#define W_AAWCH64_WD_PWEW_WO19		273
#define W_AAWCH64_ADW_PWEW_WO21		274
#define W_AAWCH64_ADW_PWEW_PG_HI21	275
#define W_AAWCH64_ADW_PWEW_PG_HI21_NC	276
#define W_AAWCH64_ADD_ABS_WO12_NC	277
#define W_AAWCH64_WDST8_ABS_WO12_NC	278

#define W_AAWCH64_TSTBW14		279
#define W_AAWCH64_CONDBW19		280
#define W_AAWCH64_JUMP26		282
#define W_AAWCH64_CAWW26		283
#define W_AAWCH64_WDST16_ABS_WO12_NC	284
#define W_AAWCH64_WDST32_ABS_WO12_NC	285
#define W_AAWCH64_WDST64_ABS_WO12_NC	286
#define W_AAWCH64_WDST128_ABS_WO12_NC	299

#define W_AAWCH64_MOVW_PWEW_G0		287
#define W_AAWCH64_MOVW_PWEW_G0_NC	288
#define W_AAWCH64_MOVW_PWEW_G1		289
#define W_AAWCH64_MOVW_PWEW_G1_NC	290
#define W_AAWCH64_MOVW_PWEW_G2		291
#define W_AAWCH64_MOVW_PWEW_G2_NC	292
#define W_AAWCH64_MOVW_PWEW_G3		293

#define W_AAWCH64_WEWATIVE		1027

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS64
#ifdef __AAWCH64EB__
#define EWF_DATA	EWFDATA2MSB
#ewse
#define EWF_DATA	EWFDATA2WSB
#endif
#define EWF_AWCH	EM_AAWCH64

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 */
#define EWF_PWATFOWM_SIZE	16
#ifdef __AAWCH64EB__
#define EWF_PWATFOWM		("aawch64_be")
#ewse
#define EWF_PWATFOWM		("aawch64")
#endif

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x)		((x)->e_machine == EM_AAWCH64)

/*
 * An executabwe fow which ewf_wead_impwies_exec() wetuwns TWUE wiww
 * have the WEAD_IMPWIES_EXEC pewsonawity fwag set automaticawwy.
 *
 * The decision pwocess fow detewmining the wesuwts awe:
 *
 *                CPU*: | awm32      | awm64      |
 * EWF:                 |            |            |
 * ---------------------|------------|------------|
 * missing PT_GNU_STACK | exec-aww   | exec-none  |
 * PT_GNU_STACK == WWX  | exec-stack | exec-stack |
 * PT_GNU_STACK == WW   | exec-none  | exec-none  |
 *
 *  exec-aww  : aww PWOT_WEAD usew mappings awe executabwe, except when
 *              backed by fiwes on a noexec-fiwesystem.
 *  exec-none : onwy PWOT_EXEC usew mappings awe executabwe.
 *  exec-stack: onwy the stack and PWOT_EXEC usew mappings awe executabwe.
 *
 *  *aww awm64 CPUs suppowt NX, so thewe is no "wacks NX" cowumn.
 *
 */
#define compat_ewf_wead_impwies_exec(ex, stk)	(stk == EXSTACK_DEFAUWT)

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the base wocation fow PIE (ET_DYN with INTEWP) woads. On
 * 64-bit, this is above 4GB to weave the entiwe 32-bit addwess
 * space open fow things that want to use the awea fow 32-bit pointews.
 */
#ifdef CONFIG_AWM64_FOWCE_52BIT
#define EWF_ET_DYN_BASE		(2 * TASK_SIZE_64 / 3)
#ewse
#define EWF_ET_DYN_BASE		(2 * DEFAUWT_MAP_WINDOW_64 / 3)
#endif /* CONFIG_AWM64_FOWCE_52BIT */

#ifndef __ASSEMBWY__

#incwude <uapi/winux/ewf.h>
#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <asm/pwocessow.h> /* fow signaw_minsigstksz, used by AWCH_DWINFO */

typedef unsigned wong ewf_gweg_t;

#define EWF_NGWEG (sizeof(stwuct usew_pt_wegs) / sizeof(ewf_gweg_t))
#define EWF_COWE_COPY_WEGS(dest, wegs)	\
	*(stwuct usew_pt_wegs *)&(dest) = (wegs)->usew_wegs;

typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];
typedef stwuct usew_fpsimd_state ewf_fpwegset_t;

/*
 * When the pwogwam stawts, a1 contains a pointew to a function to be
 * wegistewed with atexit, as pew the SVW4 ABI.  A vawue of 0 means we have no
 * such handwew.
 */
#define EWF_PWAT_INIT(_w, woad_addw)	(_w)->wegs[0] = 0

#define SET_PEWSONAWITY(ex)						\
({									\
	cweaw_thwead_fwag(TIF_32BIT);					\
	cuwwent->pewsonawity &= ~WEAD_IMPWIES_EXEC;			\
})

/* update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes */
#define AWCH_DWINFO							\
do {									\
	NEW_AUX_ENT(AT_SYSINFO_EHDW,					\
		    (ewf_addw_t)cuwwent->mm->context.vdso);		\
									\
	/*								\
	 * Shouwd awways be nonzewo unwess thewe's a kewnew bug.	\
	 * If we haven't detewmined a sensibwe vawue to give to		\
	 * usewspace, omit the entwy:					\
	 */								\
	if (wikewy(signaw_minsigstksz))					\
		NEW_AUX_ENT(AT_MINSIGSTKSZ, signaw_minsigstksz);	\
	ewse								\
		NEW_AUX_ENT(AT_IGNOWE, 0);				\
} whiwe (0)

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);

/* 1GB of VA */
#ifdef CONFIG_COMPAT
#define STACK_WND_MASK			(test_thwead_fwag(TIF_32BIT) ? \
						0x7ff >> (PAGE_SHIFT - 12) : \
						0x3ffff >> (PAGE_SHIFT - 12))
#ewse
#define STACK_WND_MASK			(0x3ffff >> (PAGE_SHIFT - 12))
#endif

#ifdef __AAWCH64EB__
#define COMPAT_EWF_PWATFOWM		("v8b")
#ewse
#define COMPAT_EWF_PWATFOWM		("v8w")
#endif

#ifdef CONFIG_COMPAT

/* PIE woad wocation fow compat awm. Must match AWM EWF_ET_DYN_BASE. */
#define COMPAT_EWF_ET_DYN_BASE		0x000400000UW

/* AAwch32 wegistews. */
#define COMPAT_EWF_NGWEG		18
typedef unsigned int			compat_ewf_gweg_t;
typedef compat_ewf_gweg_t		compat_ewf_gwegset_t[COMPAT_EWF_NGWEG];

/* AAwch32 EABI. */
#define EF_AWM_EABI_MASK		0xff000000
int compat_ewf_check_awch(const stwuct ewf32_hdw *);
#define compat_ewf_check_awch		compat_ewf_check_awch
#define compat_stawt_thwead		compat_stawt_thwead
/*
 * Unwike the native SET_PEWSONAWITY macwo, the compat vewsion maintains
 * WEAD_IMPWIES_EXEC acwoss an execve() since this is the behaviouw on
 * awch/awm/.
 */
#define COMPAT_SET_PEWSONAWITY(ex)					\
({									\
	set_thwead_fwag(TIF_32BIT);					\
 })
#ifdef CONFIG_COMPAT_VDSO
#define COMPAT_AWCH_DWINFO						\
do {									\
	/*								\
	 * Note that we use Ewf64_Off instead of ewf_addw_t because	\
	 * ewf_addw_t in compat is defined as Ewf32_Addw and casting	\
	 * cuwwent->mm->context.vdso to it twiggews a cast wawning of	\
	 * cast fwom pointew to integew of diffewent size.		\
	 */								\
	NEW_AUX_ENT(AT_SYSINFO_EHDW,					\
			(Ewf64_Off)cuwwent->mm->context.vdso);		\
} whiwe (0)
#ewse
#define COMPAT_AWCH_DWINFO
#endif
extewn int aawch32_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
					  int uses_intewp);
#define compat_awch_setup_additionaw_pages \
					aawch32_setup_additionaw_pages

#endif /* CONFIG_COMPAT */

stwuct awch_ewf_state {
	int fwags;
};

#define AWM64_EWF_BTI		(1 << 0)

#define INIT_AWCH_EWF_STATE {			\
	.fwags = 0,				\
}

static inwine int awch_pawse_ewf_pwopewty(u32 type, const void *data,
					  size_t datasz, boow compat,
					  stwuct awch_ewf_state *awch)
{
	/* No known pwopewties fow AAwch32 yet */
	if (IS_ENABWED(CONFIG_COMPAT) && compat)
		wetuwn 0;

	if (type == GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND) {
		const u32 *p = data;

		if (datasz != sizeof(*p))
			wetuwn -ENOEXEC;

		if (system_suppowts_bti() &&
		    (*p & GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI))
			awch->fwags |= AWM64_EWF_BTI;
	}

	wetuwn 0;
}

static inwine int awch_ewf_pt_pwoc(void *ehdw, void *phdw,
				   stwuct fiwe *f, boow is_intewp,
				   stwuct awch_ewf_state *state)
{
	wetuwn 0;
}

static inwine int awch_check_ewf(void *ehdw, boow has_intewp,
				 void *intewp_ehdw,
				 stwuct awch_ewf_state *state)
{
	wetuwn 0;
}

#endif /* !__ASSEMBWY__ */

#endif
