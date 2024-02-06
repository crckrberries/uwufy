// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evgwock - Gwobaw Wock suppowt
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evgwock")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/* Wocaw pwototypes */
static u32 acpi_ev_gwobaw_wock_handwew(void *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_init_gwobaw_wock_handwew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow the gwobaw wock wewease event
 *
 ******************************************************************************/

acpi_status acpi_ev_init_gwobaw_wock_handwew(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_init_gwobaw_wock_handwew);

	/* If Hawdwawe Weduced fwag is set, thewe is no gwobaw wock */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Attempt instawwation of the gwobaw wock handwew */

	status = acpi_instaww_fixed_event_handwew(ACPI_EVENT_GWOBAW,
						  acpi_ev_gwobaw_wock_handwew,
						  NUWW);

	/*
	 * If the gwobaw wock does not exist on this pwatfowm, the attempt to
	 * enabwe GBW_STATUS wiww faiw (the GBW_ENABWE bit wiww not stick).
	 * Map to AE_OK, but mawk gwobaw wock as not pwesent. Any attempt to
	 * actuawwy use the gwobaw wock wiww be fwagged with an ewwow.
	 */
	acpi_gbw_gwobaw_wock_pwesent = FAWSE;
	if (status == AE_NO_HAWDWAWE_WESPONSE) {
		ACPI_EWWOW((AE_INFO,
			    "No wesponse fwom Gwobaw Wock hawdwawe, disabwing wock"));

		wetuwn_ACPI_STATUS(AE_OK);
	}

	status = acpi_os_cweate_wock(&acpi_gbw_gwobaw_wock_pending_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	acpi_gbw_gwobaw_wock_pending = FAWSE;
	acpi_gbw_gwobaw_wock_pwesent = TWUE;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_wemove_gwobaw_wock_handwew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove the handwew fow the Gwobaw Wock
 *
 ******************************************************************************/

acpi_status acpi_ev_wemove_gwobaw_wock_handwew(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_wemove_gwobaw_wock_handwew);

	acpi_gbw_gwobaw_wock_pwesent = FAWSE;
	status = acpi_wemove_fixed_event_handwew(ACPI_EVENT_GWOBAW,
						 acpi_ev_gwobaw_wock_handwew);

	acpi_os_dewete_wock(acpi_gbw_gwobaw_wock_pending_wock);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gwobaw_wock_handwew
 *
 * PAWAMETEWS:  context         - Fwom thwead intewface, not used
 *
 * WETUWN:      ACPI_INTEWWUPT_HANDWED
 *
 * DESCWIPTION: Invoked diwectwy fwom the SCI handwew when a gwobaw wock
 *              wewease intewwupt occuws. If thewe is actuawwy a pending
 *              wequest fow the wock, signaw the waiting thwead.
 *
 ******************************************************************************/

static u32 acpi_ev_gwobaw_wock_handwew(void *context)
{
	acpi_status status;
	acpi_cpu_fwags fwags;

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gwobaw_wock_pending_wock);

	/*
	 * If a wequest fow the gwobaw wock is not actuawwy pending,
	 * we awe done. This handwes "spuwious" gwobaw wock intewwupts
	 * which awe possibwe (and have been seen) with bad BIOSs.
	 */
	if (!acpi_gbw_gwobaw_wock_pending) {
		goto cweanup_and_exit;
	}

	/*
	 * Send a unit to the gwobaw wock semaphowe. The actuaw acquisition
	 * of the gwobaw wock wiww be pewfowmed by the waiting thwead.
	 */
	status = acpi_os_signaw_semaphowe(acpi_gbw_gwobaw_wock_semaphowe, 1);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO, "Couwd not signaw Gwobaw Wock semaphowe"));
	}

	acpi_gbw_gwobaw_wock_pending = FAWSE;

cweanup_and_exit:

	acpi_os_wewease_wock(acpi_gbw_gwobaw_wock_pending_wock, fwags);
	wetuwn (ACPI_INTEWWUPT_HANDWED);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_acquiwe_gwobaw_wock
 *
 * PAWAMETEWS:  timeout         - Max time to wait fow the wock, in miwwisec.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Attempt to gain ownewship of the Gwobaw Wock.
 *
 * MUTEX:       Intewpwetew must be wocked
 *
 * Note: The owiginaw impwementation awwowed muwtipwe thweads to "acquiwe" the
 * Gwobaw Wock, and the OS wouwd howd the wock untiw the wast thwead had
 * weweased it. Howevew, this couwd potentiawwy stawve the BIOS out of the
 * wock, especiawwy in the case whewe thewe is a tight handshake between the
 * Embedded Contwowwew dwivew and the BIOS. Thewefowe, this impwementation
 * awwows onwy one thwead to acquiwe the HW Gwobaw Wock at a time, and makes
 * the gwobaw wock appeaw as a standawd mutex on the OS side.
 *
 *****************************************************************************/

acpi_status acpi_ev_acquiwe_gwobaw_wock(u16 timeout)
{
	acpi_cpu_fwags fwags;
	acpi_status status;
	u8 acquiwed = FAWSE;

	ACPI_FUNCTION_TWACE(ev_acquiwe_gwobaw_wock);

	/*
	 * Onwy one thwead can acquiwe the GW at a time, the gwobaw_wock_mutex
	 * enfowces this. This intewface weweases the intewpwetew if we must wait.
	 */
	status =
	    acpi_ex_system_wait_mutex(acpi_gbw_gwobaw_wock_mutex->mutex.
				      os_mutex, timeout);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Update the gwobaw wock handwe and check fow wwapawound. The handwe is
	 * onwy used fow the extewnaw gwobaw wock intewfaces, but it is updated
	 * hewe to pwopewwy handwe the case whewe a singwe thwead may acquiwe the
	 * wock via both the AMW and the acpi_acquiwe_gwobaw_wock intewfaces. The
	 * handwe is thewefowe updated on the fiwst acquiwe fwom a given thwead
	 * wegawdwess of whewe the acquisition wequest owiginated.
	 */
	acpi_gbw_gwobaw_wock_handwe++;
	if (acpi_gbw_gwobaw_wock_handwe == 0) {
		acpi_gbw_gwobaw_wock_handwe = 1;
	}

	/*
	 * Make suwe that a gwobaw wock actuawwy exists. If not, just
	 * tweat the wock as a standawd mutex.
	 */
	if (!acpi_gbw_gwobaw_wock_pwesent) {
		acpi_gbw_gwobaw_wock_acquiwed = TWUE;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gwobaw_wock_pending_wock);

	do {

		/* Attempt to acquiwe the actuaw hawdwawe wock */

		ACPI_ACQUIWE_GWOBAW_WOCK(acpi_gbw_FACS, acquiwed);
		if (acquiwed) {
			acpi_gbw_gwobaw_wock_acquiwed = TWUE;
			ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
					  "Acquiwed hawdwawe Gwobaw Wock\n"));
			bweak;
		}

		/*
		 * Did not get the wock. The pending bit was set above, and
		 * we must now wait untiw we weceive the gwobaw wock
		 * weweased intewwupt.
		 */
		acpi_gbw_gwobaw_wock_pending = TWUE;
		acpi_os_wewease_wock(acpi_gbw_gwobaw_wock_pending_wock, fwags);

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Waiting fow hawdwawe Gwobaw Wock\n"));

		/*
		 * Wait fow handshake with the gwobaw wock intewwupt handwew.
		 * This intewface weweases the intewpwetew if we must wait.
		 */
		status =
		    acpi_ex_system_wait_semaphowe
		    (acpi_gbw_gwobaw_wock_semaphowe, ACPI_WAIT_FOWEVEW);

		fwags = acpi_os_acquiwe_wock(acpi_gbw_gwobaw_wock_pending_wock);

	} whiwe (ACPI_SUCCESS(status));

	acpi_gbw_gwobaw_wock_pending = FAWSE;
	acpi_os_wewease_wock(acpi_gbw_gwobaw_wock_pending_wock, fwags);

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_wewease_gwobaw_wock
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Weweases ownewship of the Gwobaw Wock.
 *
 ******************************************************************************/

acpi_status acpi_ev_wewease_gwobaw_wock(void)
{
	u8 pending = FAWSE;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ev_wewease_gwobaw_wock);

	/* Wock must be awweady acquiwed */

	if (!acpi_gbw_gwobaw_wock_acquiwed) {
		ACPI_WAWNING((AE_INFO,
			      "Cannot wewease the ACPI Gwobaw Wock, it has not been acquiwed"));
		wetuwn_ACPI_STATUS(AE_NOT_ACQUIWED);
	}

	if (acpi_gbw_gwobaw_wock_pwesent) {

		/* Awwow any thwead to wewease the wock */

		ACPI_WEWEASE_GWOBAW_WOCK(acpi_gbw_FACS, pending);

		/*
		 * If the pending bit was set, we must wwite GBW_WWS to the contwow
		 * wegistew
		 */
		if (pending) {
			status =
			    acpi_wwite_bit_wegistew
			    (ACPI_BITWEG_GWOBAW_WOCK_WEWEASE,
			     ACPI_ENABWE_EVENT);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Weweased hawdwawe Gwobaw Wock\n"));
	}

	acpi_gbw_gwobaw_wock_acquiwed = FAWSE;

	/* Wewease the wocaw GW mutex */

	acpi_os_wewease_mutex(acpi_gbw_gwobaw_wock_mutex->mutex.os_mutex);
	wetuwn_ACPI_STATUS(status);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
