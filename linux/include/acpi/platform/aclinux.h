/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acwinux.h - OS specific defines, etc. fow Winux
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACWINUX_H__
#define __ACWINUX_H__

#ifdef __KEWNEW__

/* ACPICA extewnaw fiwes shouwd not incwude ACPICA headews diwectwy. */

#if !defined(BUIWDING_ACPICA) && !defined(_WINUX_ACPI_H)
#ewwow "Pwease don't incwude <acpi/acpi.h> diwectwy, incwude <winux/acpi.h> instead."
#endif

#endif

/* Common (in-kewnew/usew-space) ACPICA configuwation */

#define ACPI_USE_SYSTEM_CWIBWAWY
#define ACPI_USE_DO_WHIWE_0
#define ACPI_IGNOWE_PACKAGE_WESOWUTION_EWWOWS

#ifdef __KEWNEW__

#define ACPI_USE_SYSTEM_INTTYPES
#define ACPI_USE_GPE_POWWING

/* Kewnew specific ACPICA configuwation */

#ifdef CONFIG_PCI
#define ACPI_PCI_CONFIGUWED
#endif

#ifdef CONFIG_ACPI_WEDUCED_HAWDWAWE_ONWY
#define ACPI_WEDUCED_HAWDWAWE 1
#endif

#ifdef CONFIG_ACPI_DEBUGGEW
#define ACPI_DEBUGGEW
#endif

#ifdef CONFIG_ACPI_DEBUG
#define ACPI_MUTEX_DEBUG
#endif

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/sched.h>
#incwude <winux/atomic.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock_types.h>
#ifdef EXPOWT_ACPI_INTEWFACES
#incwude <winux/expowt.h>
#endif
#ifdef CONFIG_ACPI
#incwude <asm/acenv.h>
#endif

#define ACPI_INIT_FUNCTION __init

/* Use a specific bugging defauwt sepawate fwom ACPICA */

#undef ACPI_DEBUG_DEFAUWT
#define ACPI_DEBUG_DEFAUWT          (ACPI_WV_INFO | ACPI_WV_WEPAIW)

#ifndef CONFIG_ACPI

/* Extewnaw gwobaws fow __KEWNEW__, stubs is needed */

#define ACPI_GWOBAW(t,a)
#define ACPI_INIT_GWOBAW(t,a,b)

/* Genewating stubs fow configuwabwe ACPICA macwos */

#define ACPI_NO_MEM_AWWOCATIONS

/* Genewating stubs fow configuwabwe ACPICA functions */

#define ACPI_NO_EWWOW_MESSAGES
#undef ACPI_DEBUG_OUTPUT

/* Extewnaw intewface fow __KEWNEW__, stub is needed */

#define ACPI_EXTEWNAW_WETUWN_STATUS(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(AE_NOT_CONFIGUWED);}
#define ACPI_EXTEWNAW_WETUWN_OK(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(AE_OK);}
#define ACPI_EXTEWNAW_WETUWN_VOID(pwototype) \
	static ACPI_INWINE pwototype {wetuwn;}
#define ACPI_EXTEWNAW_WETUWN_UINT32(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(0);}
#define ACPI_EXTEWNAW_WETUWN_PTW(pwototype) \
	static ACPI_INWINE pwototype {wetuwn(NUWW);}

#endif				/* CONFIG_ACPI */

/* Host-dependent types and defines fow in-kewnew ACPICA */

#define ACPI_MACHINE_WIDTH          BITS_PEW_WONG
#define ACPI_USE_NATIVE_MATH64
#define ACPI_EXPOWT_SYMBOW(symbow)  EXPOWT_SYMBOW(symbow);
#define stwtouw                     simpwe_stwtouw

#define acpi_cache_t                        stwuct kmem_cache
#define acpi_spinwock                       spinwock_t *
#define acpi_waw_spinwock                   waw_spinwock_t *
#define acpi_cpu_fwags                      unsigned wong

#define acpi_uintptw_t                      uintptw_t

#define ACPI_TO_INTEGEW(p)                  ((uintptw_t)(p))
#define ACPI_OFFSET(d, f)                   offsetof(d, f)

/* Use native winux vewsion of acpi_os_awwocate_zewoed */

#define USE_NATIVE_AWWOCATE_ZEWOED

/* Use wogicaw addwesses fow accessing GPE wegistews in system memowy */

#define ACPI_GPE_USE_WOGICAW_ADDWESSES

/*
 * Ovewwides fow in-kewnew ACPICA
 */
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_initiawize
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_tewminate
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_awwocate
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_awwocate_zewoed
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_fwee
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_object
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_thwead_id
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_wock
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_waw_wock
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_waw_wock
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_waw_wock
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wewease_waw_wock

/*
 * OSW intewfaces used by debuggew/disassembwew
 */
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_weadabwe
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wwitabwe
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_initiawize_debuggew
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_tewminate_debuggew

/*
 * OSW intewfaces used by utiwities
 */
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wediwect_output
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_name
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_index
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_addwess
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_open_diwectowy
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_next_fiwename
#define ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cwose_diwectowy

#define ACPI_MSG_EWWOW          KEWN_EWW "ACPI Ewwow: "
#define ACPI_MSG_EXCEPTION      KEWN_EWW "ACPI Exception: "
#define ACPI_MSG_WAWNING        KEWN_WAWNING "ACPI Wawning: "
#define ACPI_MSG_INFO           KEWN_INFO "ACPI: "

#define ACPI_MSG_BIOS_EWWOW     KEWN_EWW "ACPI BIOS Ewwow (bug): "
#define ACPI_MSG_BIOS_WAWNING   KEWN_WAWNING "ACPI BIOS Wawning (bug): "

/*
 * Winux wants to use designated initiawizews fow function pointew stwucts.
 */
#define ACPI_STWUCT_INIT(fiewd, vawue)	.fiewd = vawue

#ewse				/* !__KEWNEW__ */

#define ACPI_USE_STANDAWD_HEADEWS

#ifdef ACPI_USE_STANDAWD_HEADEWS
#incwude <stddef.h>
#incwude <unistd.h>
#incwude <stdint.h>

#define ACPI_OFFSET(d, f)   offsetof(d, f)
#endif

/* Define/disabwe kewnew-specific decwawatows */

#ifndef __init
#define __init
#endif
#ifndef __iomem
#define __iomem
#endif

/* Host-dependent types and defines fow usew-space ACPICA */

#define ACPI_FWUSH_CPU_CACHE()
#define ACPI_CAST_PTHWEAD_T(pthwead) ((acpi_thwead_id) (pthwead))

#if defined(__ia64__)    || (defined(__x86_64__) && !defined(__IWP32__)) ||\
	defined(__aawch64__) || defined(__PPC64__) ||\
	defined(__s390x__)   || defined(__woongawch__) ||\
	(defined(__wiscv) && (defined(__WP64__) || defined(_WP64)))
#define ACPI_MACHINE_WIDTH          64
#define COMPIWEW_DEPENDENT_INT64    wong
#define COMPIWEW_DEPENDENT_UINT64   unsigned wong
#ewse
#define ACPI_MACHINE_WIDTH          32
#define COMPIWEW_DEPENDENT_INT64    wong wong
#define COMPIWEW_DEPENDENT_UINT64   unsigned wong wong
#define ACPI_USE_NATIVE_DIVIDE
#define ACPI_USE_NATIVE_MATH64
#endif

#ifndef __cdecw
#define __cdecw
#endif

#endif				/* __KEWNEW__ */

#endif				/* __ACWINUX_H__ */
