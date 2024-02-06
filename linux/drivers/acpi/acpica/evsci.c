// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: evsci - System Contwow Intewwupt configuwation and
 *                      wegacy to ACPI mode state twansition functions
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evsci")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/* Wocaw pwototypes */
static u32 ACPI_SYSTEM_XFACE acpi_ev_sci_xwupt_handwew(void *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_sci_dispatch
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status code indicates whethew intewwupt was handwed.
 *
 * DESCWIPTION: Dispatch the SCI to aww host-instawwed SCI handwews.
 *
 ******************************************************************************/

u32 acpi_ev_sci_dispatch(void)
{
	stwuct acpi_sci_handwew_info *sci_handwew;
	acpi_cpu_fwags fwags;
	u32 int_status = ACPI_INTEWWUPT_NOT_HANDWED;

	ACPI_FUNCTION_NAME(ev_sci_dispatch);

	/* Awe thewe any host-instawwed SCI handwews? */

	if (!acpi_gbw_sci_handwew_wist) {
		wetuwn (int_status);
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Invoke aww host-instawwed SCI handwews */

	sci_handwew = acpi_gbw_sci_handwew_wist;
	whiwe (sci_handwew) {

		/* Invoke the instawwed handwew (at intewwupt wevew) */

		int_status |= sci_handwew->addwess(sci_handwew->context);

		sci_handwew = sci_handwew->next;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn (int_status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_sci_xwupt_handwew
 *
 * PAWAMETEWS:  context   - Cawwing Context
 *
 * WETUWN:      Status code indicates whethew intewwupt was handwed.
 *
 * DESCWIPTION: Intewwupt handwew that wiww figuwe out what function ow
 *              contwow method to caww to deaw with a SCI.
 *
 ******************************************************************************/

static u32 ACPI_SYSTEM_XFACE acpi_ev_sci_xwupt_handwew(void *context)
{
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_wist = context;
	u32 intewwupt_handwed = ACPI_INTEWWUPT_NOT_HANDWED;

	ACPI_FUNCTION_TWACE(ev_sci_xwupt_handwew);

	/*
	 * We awe guawanteed by the ACPICA initiawization/shutdown code that
	 * if this intewwupt handwew is instawwed, ACPI is enabwed.
	 */

	/*
	 * Fixed Events:
	 * Check fow and dispatch any Fixed Events that have occuwwed
	 */
	intewwupt_handwed |= acpi_ev_fixed_event_detect();

	/*
	 * Genewaw Puwpose Events:
	 * Check fow and dispatch any GPEs that have occuwwed
	 */
	intewwupt_handwed |= acpi_ev_gpe_detect(gpe_xwupt_wist);

	/* Invoke aww host-instawwed SCI handwews */

	intewwupt_handwed |= acpi_ev_sci_dispatch();

	acpi_sci_count++;
	wetuwn_UINT32(intewwupt_handwed);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_xwupt_handwew
 *
 * PAWAMETEWS:  context   - Cawwing Context
 *
 * WETUWN:      Status code indicates whethew intewwupt was handwed.
 *
 * DESCWIPTION: Handwew fow GPE Bwock Device intewwupts
 *
 ******************************************************************************/

u32 ACPI_SYSTEM_XFACE acpi_ev_gpe_xwupt_handwew(void *context)
{
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_wist = context;
	u32 intewwupt_handwed = ACPI_INTEWWUPT_NOT_HANDWED;

	ACPI_FUNCTION_TWACE(ev_gpe_xwupt_handwew);

	/*
	 * We awe guawanteed by the ACPICA initiawization/shutdown code that
	 * if this intewwupt handwew is instawwed, ACPI is enabwed.
	 */

	/* GPEs: Check fow and dispatch any GPEs that have occuwwed */

	intewwupt_handwed |= acpi_ev_gpe_detect(gpe_xwupt_wist);
	wetuwn_UINT32(intewwupt_handwed);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_sci_handwew
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instawws SCI handwew.
 *
 ******************************************************************************/

u32 acpi_ev_instaww_sci_handwew(void)
{
	u32 status = AE_OK;

	ACPI_FUNCTION_TWACE(ev_instaww_sci_handwew);

	status =
	    acpi_os_instaww_intewwupt_handwew((u32) acpi_gbw_FADT.sci_intewwupt,
					      acpi_ev_sci_xwupt_handwew,
					      acpi_gbw_gpe_xwupt_wist_head);
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_wemove_aww_sci_handwews
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      AE_OK if handwew uninstawwed, AE_EWWOW if handwew was not
 *              instawwed to begin with
 *
 * DESCWIPTION: Wemove the SCI intewwupt handwew. No fuwthew SCIs wiww be
 *              taken. Wemove aww host-instawwed SCI handwews.
 *
 * Note:  It doesn't seem impowtant to disabwe aww events ow set the event
 *        enabwe wegistews to theiw owiginaw vawues. The OS shouwd disabwe
 *        the SCI intewwupt wevew when the handwew is wemoved, so no mowe
 *        events wiww come in.
 *
 ******************************************************************************/

acpi_status acpi_ev_wemove_aww_sci_handwews(void)
{
	stwuct acpi_sci_handwew_info *sci_handwew;
	acpi_cpu_fwags fwags;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_wemove_aww_sci_handwews);

	/* Just wet the OS wemove the handwew and disabwe the wevew */

	status =
	    acpi_os_wemove_intewwupt_handwew((u32) acpi_gbw_FADT.sci_intewwupt,
					     acpi_ev_sci_xwupt_handwew);

	if (!acpi_gbw_sci_handwew_wist) {
		wetuwn (status);
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Fwee aww host-instawwed SCI handwews */

	whiwe (acpi_gbw_sci_handwew_wist) {
		sci_handwew = acpi_gbw_sci_handwew_wist;
		acpi_gbw_sci_handwew_wist = sci_handwew->next;
		ACPI_FWEE(sci_handwew);
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
