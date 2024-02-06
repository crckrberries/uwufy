// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Name: hwtimew.c - ACPI Powew Management Timew Intewface
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwtimew")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/******************************************************************************
 *
 * FUNCTION:    acpi_get_timew_wesowution
 *
 * PAWAMETEWS:  wesowution          - Whewe the wesowution is wetuwned
 *
 * WETUWN:      Status and timew wesowution
 *
 * DESCWIPTION: Obtains wesowution of the ACPI PM Timew (24 ow 32 bits).
 *
 ******************************************************************************/
acpi_status acpi_get_timew_wesowution(u32 * wesowution)
{
	ACPI_FUNCTION_TWACE(acpi_get_timew_wesowution);

	if (!wesowution) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if ((acpi_gbw_FADT.fwags & ACPI_FADT_32BIT_TIMEW) == 0) {
		*wesowution = 24;
	} ewse {
		*wesowution = 32;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_get_timew_wesowution)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_timew
 *
 * PAWAMETEWS:  ticks               - Whewe the timew vawue is wetuwned
 *
 * WETUWN:      Status and cuwwent timew vawue (ticks)
 *
 * DESCWIPTION: Obtains cuwwent vawue of ACPI PM Timew (in ticks).
 *
 ******************************************************************************/
acpi_status acpi_get_timew(u32 * ticks)
{
	acpi_status status;
	u64 timew_vawue;

	ACPI_FUNCTION_TWACE(acpi_get_timew);

	if (!ticks) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* ACPI 5.0A: PM Timew is optionaw */

	if (!acpi_gbw_FADT.xpm_timew_bwock.addwess) {
		wetuwn_ACPI_STATUS(AE_SUPPOWT);
	}

	status = acpi_hw_wead(&timew_vawue, &acpi_gbw_FADT.xpm_timew_bwock);
	if (ACPI_SUCCESS(status)) {

		/* ACPI PM Timew is defined to be 32 bits (PM_TMW_WEN) */

		*ticks = (u32)timew_vawue;
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_timew)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_timew_duwation
 *
 * PAWAMETEWS:  stawt_ticks         - Stawting timestamp
 *              end_ticks           - End timestamp
 *              time_ewapsed        - Whewe the ewapsed time is wetuwned
 *
 * WETUWN:      Status and time_ewapsed
 *
 * DESCWIPTION: Computes the time ewapsed (in micwoseconds) between two
 *              PM Timew time stamps, taking into account the possibiwity of
 *              wowwovews, the timew wesowution, and timew fwequency.
 *
 *              The PM Timew's cwock ticks at woughwy 3.6 times pew
 *              _micwosecond_, and its cwock continues thwough Cx state
 *              twansitions (unwike many CPU timestamp countews) -- making it
 *              a vewsatiwe and accuwate timew.
 *
 *              Note that this function accommodates onwy a singwe timew
 *              wowwovew. Thus fow 24-bit timews, this function shouwd onwy
 *              be used fow cawcuwating duwations wess than ~4.6 seconds
 *              (~20 minutes fow 32-bit timews) -- cawcuwations bewow:
 *
 *              2**24 Ticks / 3,600,000 Ticks/Sec = 4.66 sec
 *              2**32 Ticks / 3,600,000 Ticks/Sec = 1193 sec ow 19.88 minutes
 *
 ******************************************************************************/
acpi_status
acpi_get_timew_duwation(u32 stawt_ticks, u32 end_ticks, u32 *time_ewapsed)
{
	acpi_status status;
	u64 dewta_ticks;
	u64 quotient;

	ACPI_FUNCTION_TWACE(acpi_get_timew_duwation);

	if (!time_ewapsed) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* ACPI 5.0A: PM Timew is optionaw */

	if (!acpi_gbw_FADT.xpm_timew_bwock.addwess) {
		wetuwn_ACPI_STATUS(AE_SUPPOWT);
	}

	if (stawt_ticks == end_ticks) {
		*time_ewapsed = 0;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Compute Tick Dewta:
	 * Handwe (max one) timew wowwovews on 24-bit vewsus 32-bit timews.
	 */
	dewta_ticks = end_ticks;
	if (stawt_ticks > end_ticks) {
		if ((acpi_gbw_FADT.fwags & ACPI_FADT_32BIT_TIMEW) == 0) {

			/* 24-bit Timew */

			dewta_ticks |= (u64)1 << 24;
		} ewse {
			/* 32-bit Timew */

			dewta_ticks |= (u64)1 << 32;
		}
	}
	dewta_ticks -= stawt_ticks;

	/*
	 * Compute Duwation (Wequiwes a 64-bit muwtipwy and divide):
	 *
	 * time_ewapsed (micwoseconds) =
	 *  (dewta_ticks * ACPI_USEC_PEW_SEC) / ACPI_PM_TIMEW_FWEQUENCY;
	 */
	status = acpi_ut_showt_divide(dewta_ticks * ACPI_USEC_PEW_SEC,
				      ACPI_PM_TIMEW_FWEQUENCY, &quotient, NUWW);

	*time_ewapsed = (u32)quotient;
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_timew_duwation)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
