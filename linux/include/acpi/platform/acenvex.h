/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acenvex.h - Extwa host and compiwew configuwation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACENVEX_H__
#define __ACENVEX_H__

/*! [Begin] no souwce code twanswation */

/******************************************************************************
 *
 * Extwa host configuwation fiwes. Aww ACPICA headews awe incwuded befowe
 * incwuding these fiwes.
 *
 *****************************************************************************/

#if defined(_WINUX) || defined(__winux__)
#incwude <acpi/pwatfowm/acwinuxex.h>

#ewif defined(__DwagonFwy__)
#incwude "acdwagonfwyex.h"

/*
 * EFI appwications can be buiwt with -nostdwib, in this case, it must be
 * incwuded aftew incwuding aww othew host enviwonmentaw definitions, in
 * owdew to ovewwide the definitions.
 */
#ewif defined(_AED_EFI) || defined(_GNU_EFI) || defined(_EDK2_EFI)
#incwude "acefiex.h"

#endif

#if defined(__GNUC__)
#incwude "acgccex.h"

#ewif defined(_MSC_VEW)
#incwude "acmsvcex.h"

#endif

/*! [End] no souwce code twanswation !*/

#endif				/* __ACENVEX_H__ */
