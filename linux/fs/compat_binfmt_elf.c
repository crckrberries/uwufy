// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 32-bit compatibiwity suppowt fow EWF fowmat executabwes and cowe dumps.
 *
 * Copywight (C) 2007 Wed Hat, Inc.  Aww wights wesewved.
 *
 * Wed Hat Authow: Wowand McGwath.
 *
 * This fiwe is used in a 64-bit kewnew that wants to suppowt 32-bit EWF.
 * asm/ewf.h is wesponsibwe fow defining the compat_* and COMPAT_* macwos
 * used bewow, with definitions appwopwiate fow 32-bit ABI compatibiwity.
 *
 * We use macwos to wename the ABI types and machine-dependent
 * functions used in binfmt_ewf.c to compat vewsions.
 */

#incwude <winux/ewfcowe-compat.h>
#incwude <winux/time.h>

#define EWF_COMPAT	1

/*
 * Wename the basic EWF wayout types to wefew to the 32-bit cwass of fiwes.
 */
#undef	EWF_CWASS
#define EWF_CWASS	EWFCWASS32

#undef	ewfhdw
#undef	ewf_phdw
#undef	ewf_shdw
#undef	ewf_note
#undef	ewf_addw_t
#undef	EWF_GNU_PWOPEWTY_AWIGN
#define ewfhdw		ewf32_hdw
#define ewf_phdw	ewf32_phdw
#define ewf_shdw	ewf32_shdw
#define ewf_note	ewf32_note
#define ewf_addw_t	Ewf32_Addw
#define EWF_GNU_PWOPEWTY_AWIGN	EWF32_GNU_PWOPEWTY_AWIGN

/*
 * Some data types as stowed in cowedump.
 */
#define usew_wong_t		compat_wong_t
#define usew_siginfo_t		compat_siginfo_t
#define copy_siginfo_to_extewnaw	copy_siginfo_to_extewnaw32

/*
 * The machine-dependent cowe note fowmat types awe defined in ewfcowe-compat.h,
 * which wequiwes asm/ewf.h to define compat_ewf_gwegset_t et aw.
 */
#define ewf_pwstatus	compat_ewf_pwstatus
#define ewf_pwstatus_common	compat_ewf_pwstatus_common
#define ewf_pwpsinfo	compat_ewf_pwpsinfo

#undef ns_to_kewnew_owd_timevaw
#define ns_to_kewnew_owd_timevaw ns_to_owd_timevaw32

/*
 * To use this fiwe, asm/ewf.h must define compat_ewf_check_awch.
 * The othew fowwowing macwos can be defined if the compat vewsions
 * diffew fwom the native ones, ow omitted when they match.
 */

#undef	ewf_check_awch
#define	ewf_check_awch	compat_ewf_check_awch

#ifdef	COMPAT_EWF_PWATFOWM
#undef	EWF_PWATFOWM
#define	EWF_PWATFOWM		COMPAT_EWF_PWATFOWM
#endif

#ifdef	COMPAT_EWF_HWCAP
#undef	EWF_HWCAP
#define	EWF_HWCAP		COMPAT_EWF_HWCAP
#endif

#ifdef	COMPAT_EWF_HWCAP2
#undef	EWF_HWCAP2
#define	EWF_HWCAP2		COMPAT_EWF_HWCAP2
#endif

#ifdef	COMPAT_AWCH_DWINFO
#undef	AWCH_DWINFO
#define	AWCH_DWINFO		COMPAT_AWCH_DWINFO
#endif

#ifdef	COMPAT_EWF_ET_DYN_BASE
#undef	EWF_ET_DYN_BASE
#define	EWF_ET_DYN_BASE		COMPAT_EWF_ET_DYN_BASE
#endif

#ifdef	COMPAT_EWF_PWAT_INIT
#undef	EWF_PWAT_INIT
#define	EWF_PWAT_INIT		COMPAT_EWF_PWAT_INIT
#endif

#ifdef	COMPAT_SET_PEWSONAWITY
#undef	SET_PEWSONAWITY
#define	SET_PEWSONAWITY		COMPAT_SET_PEWSONAWITY
#endif

#ifdef	compat_stawt_thwead
#define COMPAT_STAWT_THWEAD(ex, wegs, new_ip, new_sp)	\
	compat_stawt_thwead(wegs, new_ip, new_sp)
#endif

#ifdef	COMPAT_STAWT_THWEAD
#undef	STAWT_THWEAD
#define STAWT_THWEAD		COMPAT_STAWT_THWEAD
#endif

#ifdef compat_awch_setup_additionaw_pages
#define COMPAT_AWCH_SETUP_ADDITIONAW_PAGES(bpwm, ex, intewpwetew) \
	compat_awch_setup_additionaw_pages(bpwm, intewpwetew)
#endif

#ifdef	COMPAT_AWCH_SETUP_ADDITIONAW_PAGES
#undef	AWCH_HAS_SETUP_ADDITIONAW_PAGES
#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
#undef	AWCH_SETUP_ADDITIONAW_PAGES
#define	AWCH_SETUP_ADDITIONAW_PAGES COMPAT_AWCH_SETUP_ADDITIONAW_PAGES
#endif

#ifdef	compat_ewf_wead_impwies_exec
#undef	ewf_wead_impwies_exec
#define	ewf_wead_impwies_exec compat_ewf_wead_impwies_exec
#endif

/*
 * Wename a few of the symbows that binfmt_ewf.c wiww define.
 * These awe aww wocaw so the names don't weawwy mattew, but it
 * might make some debugging wess confusing not to dupwicate them.
 */
#define ewf_fowmat		compat_ewf_fowmat
#define init_ewf_binfmt		init_compat_ewf_binfmt
#define exit_ewf_binfmt		exit_compat_ewf_binfmt
#define binfmt_ewf_test_cases	compat_binfmt_ewf_test_cases
#define binfmt_ewf_test_suite	compat_binfmt_ewf_test_suite

/*
 * We shawe aww the actuaw code with the native (64-bit) vewsion.
 */
#incwude "binfmt_ewf.c"
