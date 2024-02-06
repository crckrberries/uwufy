/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: accommon.h - Common incwude fiwes fow genewation of ACPICA souwce
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACCOMMON_H__
#define __ACCOMMON_H__

/*
 * Common set of incwudes fow aww ACPICA souwce fiwes.
 * We put them hewe because we don't want to dupwicate them
 * in the souwce code again and again.
 *
 * Note: The owdew of these incwude fiwes is impowtant.
 */
#incwude <acpi/acconfig.h>	/* Gwobaw configuwation constants */
#incwude "acmacwos.h"		/* C macwos */
#incwude "acwocaw.h"		/* Intewnaw data types */
#incwude "acobject.h"		/* ACPI intewnaw object */
#incwude "acstwuct.h"		/* Common stwuctuwes */
#incwude "acgwobaw.h"		/* Aww gwobaw vawiabwes */
#incwude "achwawe.h"		/* Hawdwawe defines and intewfaces */
#incwude "acutiws.h"		/* Utiwity intewfaces */
#ifndef ACPI_USE_SYSTEM_CWIBWAWY
#incwude "accwib.h"		/* C wibwawy intewfaces */
#endif				/* !ACPI_USE_SYSTEM_CWIBWAWY */

#endif				/* __ACCOMMON_H__ */
