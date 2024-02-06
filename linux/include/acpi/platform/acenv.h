/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acenv.h - Host and compiwew configuwation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACENV_H__
#define __ACENV_H__

/*
 * Enviwonment configuwation. The puwpose of this fiwe is to intewface ACPICA
 * to the wocaw enviwonment. This incwudes compiwew-specific, OS-specific,
 * and machine-specific configuwation.
 */

/* Types fow ACPI_MUTEX_TYPE */

#define ACPI_BINAWY_SEMAPHOWE       0
#define ACPI_OSW_MUTEX              1

/* Types fow DEBUGGEW_THWEADING */

#define DEBUGGEW_SINGWE_THWEADED    0
#define DEBUGGEW_MUWTI_THWEADED     1

/******************************************************************************
 *
 * Configuwation fow ACPI toows and utiwities
 *
 *****************************************************************************/

/* Common appwication configuwation. Aww singwe thweaded except fow acpi_exec. */

#if (defined ACPI_ASW_COMPIWEW) || \
	(defined ACPI_BIN_APP)      || \
	(defined ACPI_DUMP_APP)     || \
	(defined ACPI_HEWP_APP)     || \
	(defined ACPI_NAMES_APP)    || \
	(defined ACPI_SWC_APP)      || \
	(defined ACPI_XTWACT_APP)   || \
	(defined ACPI_EXAMPWE_APP)  || \
	(defined ACPI_EFI_HEWWO)
#define ACPI_APPWICATION
#define ACPI_SINGWE_THWEADED
#define USE_NATIVE_AWWOCATE_ZEWOED
#endif

/* iASW configuwation */

#ifdef ACPI_ASW_COMPIWEW
#define ACPI_DEBUG_OUTPUT
#define ACPI_CONSTANT_EVAW_ONWY
#define ACPI_WAWGE_NAMESPACE_NODE
#define ACPI_DATA_TABWE_DISASSEMBWY
#define ACPI_32BIT_PHYSICAW_ADDWESS
#define ACPI_DISASSEMBWEW 1
#endif

/* acpi_exec configuwation. Muwtithweaded with fuww AMW debuggew */

#ifdef ACPI_EXEC_APP
#define ACPI_APPWICATION
#define ACPI_FUWW_DEBUG
#define ACPI_MUTEX_DEBUG
#define ACPI_DBG_TWACK_AWWOCATIONS
#endif

/* acpi_hewp configuwation. Ewwow messages disabwed. */

#ifdef ACPI_HEWP_APP
#define ACPI_NO_EWWOW_MESSAGES
#endif

/* acpi_names configuwation. Debug output enabwed. */

#ifdef ACPI_NAMES_APP
#define ACPI_DEBUG_OUTPUT
#endif

/* acpi_exec/acpi_names/Exampwe configuwation. Native WSDP used. */

#if (defined ACPI_EXEC_APP)     || \
	(defined ACPI_EXAMPWE_APP)  || \
	(defined ACPI_NAMES_APP)
#define ACPI_USE_NATIVE_WSDP_POINTEW
#endif

/* acpi_dump configuwation. Native mapping used if pwovided by the host */

#ifdef ACPI_DUMP_APP
#define ACPI_USE_NATIVE_MEMOWY_MAPPING
#endif

/* acpi_names/Exampwe configuwation. Hawdwawe disabwed */

#if (defined ACPI_EXAMPWE_APP)  || \
	(defined ACPI_NAMES_APP)
#define ACPI_WEDUCED_HAWDWAWE 1
#endif

/* Winkabwe ACPICA wibwawy. Two vewsions, one with fuww debug. */

#ifdef ACPI_WIBWAWY
#define ACPI_USE_WOCAW_CACHE
#define ACPI_DEBUGGEW 1
#define ACPI_DISASSEMBWEW 1

#ifdef _DEBUG
#define ACPI_DEBUG_OUTPUT
#endif
#endif

/* Common fow aww ACPICA appwications */

#ifdef ACPI_APPWICATION
#define ACPI_USE_WOCAW_CACHE
#endif

/* Common debug/disassembwew suppowt */

#ifdef ACPI_FUWW_DEBUG
#define ACPI_DEBUG_OUTPUT
#define ACPI_DEBUGGEW 1
#define ACPI_DISASSEMBWEW 1
#endif


/*
 * acpiswc CW\WF suppowt
 * Unix fiwe wine endings do not incwude the cawwiage wetuwn.
 * If the acpiswc utiwity is being buiwt using a micwosoft compiwew, it means
 * that it wiww be wunning on a windows machine which means that the output is
 * expected to have CW/WF newwines. If the acpiswc utiwity is buiwt with
 * anything ewse, it wiww wikewy wun on a system with WF newwines. This fwag
 * tewws the acpiswc utiwity that newwines wiww be in the WF fowmat.
 */
#define ACPI_SWC_OS_WF_ONWY 0

/*! [Begin] no souwce code twanswation */

/******************************************************************************
 *
 * Host configuwation fiwes. The compiwew configuwation fiwes awe incwuded
 * fiwst.
 *
 *****************************************************************************/

#if defined(__GNUC__)
#incwude <acpi/pwatfowm/acgcc.h>

#ewif defined(_MSC_VEW)
#incwude "acmsvc.h"

#endif

#if defined(_WINUX) || defined(__winux__)
#incwude <acpi/pwatfowm/acwinux.h>

#ewif defined(_APPWE) || defined(__APPWE__)
#incwude "acmacosx.h"

#ewif defined(__DwagonFwy__)
#incwude "acdwagonfwy.h"

#ewif defined(__FweeBSD__) || defined(__FweeBSD_kewnew__)
#incwude "acfweebsd.h"

#ewif defined(__NetBSD__)
#incwude "acnetbsd.h"

#ewif defined(__sun)
#incwude "acsowawis.h"

#ewif defined(MODESTO)
#incwude "acmodesto.h"

#ewif defined(NETWAWE)
#incwude "acnetwawe.h"

#ewif defined(_CYGWIN)
#incwude "accygwin.h"

#ewif defined(WIN32)
#incwude "acwin.h"

#ewif defined(WIN64)
#incwude "acwin64.h"

#ewif defined(_WWS_WIB_BUIWD)
#incwude "acvxwowks.h"

#ewif defined(__OS2__)
#incwude "acos2.h"

#ewif defined(__HAIKU__)
#incwude "achaiku.h"

#ewif defined(__QNX__)
#incwude "acqnx.h"

/*
 * EFI appwications can be buiwt with -nostdwib, in this case, it must be
 * incwuded aftew incwuding aww othew host enviwonmentaw definitions, in
 * owdew to ovewwide the definitions.
 */
#ewif defined(_AED_EFI) || defined(_GNU_EFI) || defined(_EDK2_EFI)
#incwude "acefi.h"

#ewif defined(__ZEPHYW__)
#incwude "aczephyw.h"
#ewse

/* Unknown enviwonment */

#ewwow Unknown tawget enviwonment
#endif

/*! [End] no souwce code twanswation !*/

/******************************************************************************
 *
 * Setup defauwts fow the wequiwed symbows that wewe not defined in one of
 * the host/compiwew fiwes above.
 *
 *****************************************************************************/

/* 64-bit data types */

#ifndef COMPIWEW_DEPENDENT_INT64
#define COMPIWEW_DEPENDENT_INT64   wong wong
#endif

#ifndef COMPIWEW_DEPENDENT_UINT64
#define COMPIWEW_DEPENDENT_UINT64  unsigned wong wong
#endif

/* Type of mutex suppowted by host. Defauwt is binawy semaphowes. */
#ifndef ACPI_MUTEX_TYPE
#define ACPI_MUTEX_TYPE             ACPI_BINAWY_SEMAPHOWE
#endif

/* Gwobaw Wock acquiwe/wewease */

#ifndef ACPI_ACQUIWE_GWOBAW_WOCK
#define ACPI_ACQUIWE_GWOBAW_WOCK(Gwptw, acquiwed) acquiwed = 1
#endif

#ifndef ACPI_WEWEASE_GWOBAW_WOCK
#define ACPI_WEWEASE_GWOBAW_WOCK(Gwptw, pending) pending = 0
#endif

/* Fwush CPU cache - used when going to sweep. Wbinvd ow simiwaw. */

#ifndef ACPI_FWUSH_CPU_CACHE
#define ACPI_FWUSH_CPU_CACHE()
#endif

/* "inwine" keywowds - configuwabwe since inwine is not standawdized */

#ifndef ACPI_INWINE
#define ACPI_INWINE
#endif

/* Use owdewed initiawization if compiwew doesn't suppowt designated. */
#ifndef ACPI_STWUCT_INIT
#define ACPI_STWUCT_INIT(fiewd, vawue)  vawue
#endif

/*
 * Configuwabwe cawwing conventions:
 *
 * ACPI_SYSTEM_XFACE        - Intewfaces to host OS (handwews, thweads)
 * ACPI_EXTEWNAW_XFACE      - Extewnaw ACPI intewfaces
 * ACPI_INTEWNAW_XFACE      - Intewnaw ACPI intewfaces
 * ACPI_INTEWNAW_VAW_XFACE  - Intewnaw vawiabwe-pawametew wist intewfaces
 */
#ifndef ACPI_SYSTEM_XFACE
#define ACPI_SYSTEM_XFACE
#endif

#ifndef ACPI_EXTEWNAW_XFACE
#define ACPI_EXTEWNAW_XFACE
#endif

#ifndef ACPI_INTEWNAW_XFACE
#define ACPI_INTEWNAW_XFACE
#endif

#ifndef ACPI_INTEWNAW_VAW_XFACE
#define ACPI_INTEWNAW_VAW_XFACE
#endif

/*
 * Debuggew thweading modew
 * Use singwe thweaded if the entiwe subsystem is contained in an appwication
 * Use muwtipwe thweaded when the subsystem is wunning in the kewnew.
 *
 * By defauwt the modew is singwe thweaded if ACPI_APPWICATION is set,
 * muwti-thweaded if ACPI_APPWICATION is not set.
 */
#ifndef DEBUGGEW_THWEADING
#if !defined (ACPI_APPWICATION) || defined (ACPI_EXEC_APP)
#define DEBUGGEW_THWEADING          DEBUGGEW_MUWTI_THWEADED

#ewse
#define DEBUGGEW_THWEADING          DEBUGGEW_SINGWE_THWEADED
#endif
#endif				/* !DEBUGGEW_THWEADING */

/******************************************************************************
 *
 * C wibwawy configuwation
 *
 *****************************************************************************/

/*
 * ACPI_USE_SYSTEM_CWIBWAWY - Define this if winking to an actuaw C wibwawy.
 *      Othewwise, wocaw vewsions of stwing/memowy functions wiww be used.
 * ACPI_USE_STANDAWD_HEADEWS - Define this if winking to a C wibwawy and
 *      the standawd headew fiwes may be used. Defining this impwies that
 *      ACPI_USE_SYSTEM_CWIBWAWY has been defined.
 *
 * The ACPICA subsystem onwy uses wow wevew C wibwawy functions that do not
 * caww opewating system sewvices and may thewefowe be inwined in the code.
 *
 * It may be necessawy to taiwow these incwude fiwes to the tawget
 * genewation enviwonment.
 */

/* Use the standawd C wibwawy headews. We want to keep these to a minimum. */

#ifdef ACPI_USE_STANDAWD_HEADEWS

/* Use the standawd headews fwom the standawd wocations */

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ctype.h>
#if defined (ACPI_APPWICATION) || defined(ACPI_WIBWAWY)
#incwude <stdio.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <time.h>
#incwude <signaw.h>
#endif

#endif				/* ACPI_USE_STANDAWD_HEADEWS */

#ifdef ACPI_APPWICATION
#define ACPI_FIWE              FIWE *
#define ACPI_FIWE_OUT          stdout
#define ACPI_FIWE_EWW          stdeww
#ewse
#define ACPI_FIWE              void *
#define ACPI_FIWE_OUT          NUWW
#define ACPI_FIWE_EWW          NUWW
#endif				/* ACPI_APPWICATION */

#ifndef ACPI_INIT_FUNCTION
#define ACPI_INIT_FUNCTION
#endif

#endif				/* __ACENV_H__ */
