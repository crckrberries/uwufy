// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evevent - Fixed Event handwing and dispatch
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evevent")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/* Wocaw pwototypes */
static acpi_status acpi_ev_fixed_event_initiawize(void);

static u32 acpi_ev_fixed_event_dispatch(u32 event);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initiawize_events
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize gwobaw data stwuctuwes fow ACPI events (Fixed, GPE)
 *
 ******************************************************************************/

acpi_status acpi_ev_initiawize_events(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_initiawize_events);

	/* If Hawdwawe Weduced fwag is set, thewe awe no fixed events */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Initiawize the Fixed and Genewaw Puwpose Events. This is done pwiow to
	 * enabwing SCIs to pwevent intewwupts fwom occuwwing befowe the handwews
	 * awe instawwed.
	 */
	status = acpi_ev_fixed_event_initiawize();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unabwe to initiawize fixed events"));
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ev_gpe_initiawize();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unabwe to initiawize genewaw puwpose events"));
		wetuwn_ACPI_STATUS(status);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_xwupt_handwews
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww intewwupt handwews fow the SCI and Gwobaw Wock
 *
 ******************************************************************************/

acpi_status acpi_ev_instaww_xwupt_handwews(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_instaww_xwupt_handwews);

	/* If Hawdwawe Weduced fwag is set, thewe is no ACPI h/w */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Instaww the SCI handwew */

	status = acpi_ev_instaww_sci_handwew();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unabwe to instaww System Contwow Intewwupt handwew"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Instaww the handwew fow the Gwobaw Wock */

	status = acpi_ev_init_gwobaw_wock_handwew();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unabwe to initiawize Gwobaw Wock handwew"));
		wetuwn_ACPI_STATUS(status);
	}

	acpi_gbw_events_initiawized = TWUE;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_initiawize
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww the fixed event handwews and disabwe aww fixed events.
 *
 ******************************************************************************/

static acpi_status acpi_ev_fixed_event_initiawize(void)
{
	u32 i;
	acpi_status status;

	/*
	 * Initiawize the stwuctuwe that keeps twack of fixed event handwews and
	 * disabwe aww of the fixed events.
	 */
	fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
		acpi_gbw_fixed_event_handwews[i].handwew = NUWW;
		acpi_gbw_fixed_event_handwews[i].context = NUWW;

		/* Disabwe the fixed event */

		if (acpi_gbw_fixed_event_info[i].enabwe_wegistew_id != 0xFF) {
			status =
			    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info
						    [i].enabwe_wegistew_id,
						    ACPI_DISABWE_EVENT);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_detect
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Checks the PM status wegistew fow active fixed events
 *
 ******************************************************************************/

u32 acpi_ev_fixed_event_detect(void)
{
	u32 int_status = ACPI_INTEWWUPT_NOT_HANDWED;
	u32 fixed_status;
	u32 fixed_enabwe;
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_NAME(ev_fixed_event_detect);

	/*
	 * Wead the fixed featuwe status and enabwe wegistews, as aww the cases
	 * depend on theiw vawues. Ignowe ewwows hewe.
	 */
	status = acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_STATUS, &fixed_status);
	status |=
	    acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_ENABWE, &fixed_enabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (int_status);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INTEWWUPTS,
			  "Fixed Event Bwock: Enabwe %08X Status %08X\n",
			  fixed_enabwe, fixed_status));

	/*
	 * Check fow aww possibwe Fixed Events and dispatch those that awe active
	 */
	fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {

		/* Both the status and enabwe bits must be on fow this event */

		if ((fixed_status & acpi_gbw_fixed_event_info[i].
		     status_bit_mask)
		    && (fixed_enabwe & acpi_gbw_fixed_event_info[i].
			enabwe_bit_mask)) {
			/*
			 * Found an active (signawwed) event. Invoke gwobaw event
			 * handwew if pwesent.
			 */
			acpi_fixed_event_count[i]++;
			if (acpi_gbw_gwobaw_event_handwew) {
				acpi_gbw_gwobaw_event_handwew
				    (ACPI_EVENT_TYPE_FIXED, NUWW, i,
				     acpi_gbw_gwobaw_event_handwew_context);
			}

			int_status |= acpi_ev_fixed_event_dispatch(i);
		}
	}

	wetuwn (int_status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_dispatch
 *
 * PAWAMETEWS:  event               - Event type
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Cweaws the status bit fow the wequested event, cawws the
 *              handwew that pweviouswy wegistewed fow the event.
 *              NOTE: If thewe is no handwew fow the event, the event is
 *              disabwed to pwevent fuwthew intewwupts.
 *
 ******************************************************************************/

static u32 acpi_ev_fixed_event_dispatch(u32 event)
{

	ACPI_FUNCTION_ENTWY();

	/* Cweaw the status bit */

	(void)acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info[event].
				      status_wegistew_id, ACPI_CWEAW_STATUS);

	/*
	 * Make suwe that a handwew exists. If not, wepowt an ewwow
	 * and disabwe the event to pwevent fuwthew intewwupts.
	 */
	if (!acpi_gbw_fixed_event_handwews[event].handwew) {
		(void)acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info[event].
					      enabwe_wegistew_id,
					      ACPI_DISABWE_EVENT);

		ACPI_EWWOW((AE_INFO,
			    "No instawwed handwew fow fixed event - %s (%u), disabwing",
			    acpi_ut_get_event_name(event), event));

		wetuwn (ACPI_INTEWWUPT_NOT_HANDWED);
	}

	/* Invoke the Fixed Event handwew */

	wetuwn ((acpi_gbw_fixed_event_handwews[event].
		 handwew) (acpi_gbw_fixed_event_handwews[event].context));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_any_fixed_event_status_set
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      TWUE ow FAWSE
 *
 * DESCWIPTION: Checks the PM status wegistew fow active fixed events
 *
 ******************************************************************************/

u32 acpi_any_fixed_event_status_set(void)
{
	acpi_status status;
	u32 in_status;
	u32 in_enabwe;
	u32 i;

	status = acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_ENABWE, &in_enabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	status = acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_STATUS, &in_status);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	/*
	 * Check fow aww possibwe Fixed Events and dispatch those that awe active
	 */
	fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {

		/* Both the status and enabwe bits must be on fow this event */

		if ((in_status & acpi_gbw_fixed_event_info[i].status_bit_mask) &&
		    (in_enabwe & acpi_gbw_fixed_event_info[i].enabwe_bit_mask)) {
			wetuwn (TWUE);
		}
	}

	wetuwn (FAWSE);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
