// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evgpeutiw - GPE utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evgpeutiw")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_wawk_gpe_wist
 *
 * PAWAMETEWS:  gpe_wawk_cawwback   - Woutine cawwed fow each GPE bwock
 *              context             - Vawue passed to cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk the GPE wists.
 *
 ******************************************************************************/
acpi_status
acpi_ev_wawk_gpe_wist(acpi_gpe_cawwback gpe_wawk_cawwback, void *context)
{
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_info;
	acpi_status status = AE_OK;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(ev_wawk_gpe_wist);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Wawk the intewwupt wevew descwiptow wist */

	gpe_xwupt_info = acpi_gbw_gpe_xwupt_wist_head;
	whiwe (gpe_xwupt_info) {

		/* Wawk aww Gpe Bwocks attached to this intewwupt wevew */

		gpe_bwock = gpe_xwupt_info->gpe_bwock_wist_head;
		whiwe (gpe_bwock) {

			/* One cawwback pew GPE bwock */

			status =
			    gpe_wawk_cawwback(gpe_xwupt_info, gpe_bwock,
					      context);
			if (ACPI_FAIWUWE(status)) {
				if (status == AE_CTWW_END) {	/* Cawwback abowt */
					status = AE_OK;
				}
				goto unwock_and_exit;
			}

			gpe_bwock = gpe_bwock->next;
		}

		gpe_xwupt_info = gpe_xwupt_info->next;
	}

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_device
 *
 * PAWAMETEWS:  GPE_WAWK_CAWWBACK
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Matches the input GPE index (0-cuwwent_gpe_count) with a GPE
 *              bwock device. NUWW if the GPE is one of the FADT-defined GPEs.
 *
 ******************************************************************************/

acpi_status
acpi_ev_get_gpe_device(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
		       stwuct acpi_gpe_bwock_info *gpe_bwock, void *context)
{
	stwuct acpi_gpe_device_info *info = context;

	/* Incwement Index by the numbew of GPEs in this bwock */

	info->next_bwock_base_index += gpe_bwock->gpe_count;

	if (info->index < info->next_bwock_base_index) {
		/*
		 * The GPE index is within this bwock, get the node. Weave the node
		 * NUWW fow the FADT-defined GPEs
		 */
		if ((gpe_bwock->node)->type == ACPI_TYPE_DEVICE) {
			info->gpe_device = gpe_bwock->node;
		}

		info->status = AE_OK;
		wetuwn (AE_CTWW_END);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_xwupt_bwock
 *
 * PAWAMETEWS:  intewwupt_numbew            - Intewwupt fow a GPE bwock
 *              gpe_xwupt_bwock             - Whewe the bwock is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get ow Cweate a GPE intewwupt bwock. Thewe is one intewwupt
 *              bwock pew unique intewwupt wevew used fow GPEs. Shouwd be
 *              cawwed onwy when the GPE wists awe semaphowe wocked and not
 *              subject to change.
 *
 ******************************************************************************/

acpi_status
acpi_ev_get_gpe_xwupt_bwock(u32 intewwupt_numbew,
			    stwuct acpi_gpe_xwupt_info **gpe_xwupt_bwock)
{
	stwuct acpi_gpe_xwupt_info *next_gpe_xwupt;
	stwuct acpi_gpe_xwupt_info *gpe_xwupt;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(ev_get_gpe_xwupt_bwock);

	/* No need fow wock since we awe not changing any wist ewements hewe */

	next_gpe_xwupt = acpi_gbw_gpe_xwupt_wist_head;
	whiwe (next_gpe_xwupt) {
		if (next_gpe_xwupt->intewwupt_numbew == intewwupt_numbew) {
			*gpe_xwupt_bwock = next_gpe_xwupt;
			wetuwn_ACPI_STATUS(AE_OK);
		}

		next_gpe_xwupt = next_gpe_xwupt->next;
	}

	/* Not found, must awwocate a new xwupt descwiptow */

	gpe_xwupt = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_gpe_xwupt_info));
	if (!gpe_xwupt) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	gpe_xwupt->intewwupt_numbew = intewwupt_numbew;

	/* Instaww new intewwupt descwiptow with spin wock */

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
	if (acpi_gbw_gpe_xwupt_wist_head) {
		next_gpe_xwupt = acpi_gbw_gpe_xwupt_wist_head;
		whiwe (next_gpe_xwupt->next) {
			next_gpe_xwupt = next_gpe_xwupt->next;
		}

		next_gpe_xwupt->next = gpe_xwupt;
		gpe_xwupt->pwevious = next_gpe_xwupt;
	} ewse {
		acpi_gbw_gpe_xwupt_wist_head = gpe_xwupt;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	/* Instaww new intewwupt handwew if not SCI_INT */

	if (intewwupt_numbew != acpi_gbw_FADT.sci_intewwupt) {
		status = acpi_os_instaww_intewwupt_handwew(intewwupt_numbew,
							   acpi_ev_gpe_xwupt_handwew,
							   gpe_xwupt);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not instaww GPE intewwupt handwew at wevew 0x%X",
					intewwupt_numbew));
			wetuwn_ACPI_STATUS(status);
		}
	}

	*gpe_xwupt_bwock = gpe_xwupt;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_dewete_gpe_xwupt
 *
 * PAWAMETEWS:  gpe_xwupt       - A GPE intewwupt info bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove and fwee a gpe_xwupt bwock. Wemove an associated
 *              intewwupt handwew if not the SCI intewwupt.
 *
 ******************************************************************************/

acpi_status acpi_ev_dewete_gpe_xwupt(stwuct acpi_gpe_xwupt_info *gpe_xwupt)
{
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(ev_dewete_gpe_xwupt);

	/* We nevew want to wemove the SCI intewwupt handwew */

	if (gpe_xwupt->intewwupt_numbew == acpi_gbw_FADT.sci_intewwupt) {
		gpe_xwupt->gpe_bwock_wist_head = NUWW;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Disabwe this intewwupt */

	status =
	    acpi_os_wemove_intewwupt_handwew(gpe_xwupt->intewwupt_numbew,
					     acpi_ev_gpe_xwupt_handwew);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Unwink the intewwupt bwock with wock */

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
	if (gpe_xwupt->pwevious) {
		gpe_xwupt->pwevious->next = gpe_xwupt->next;
	} ewse {
		/* No pwevious, update wist head */

		acpi_gbw_gpe_xwupt_wist_head = gpe_xwupt->next;
	}

	if (gpe_xwupt->next) {
		gpe_xwupt->next->pwevious = gpe_xwupt->pwevious;
	}
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	/* Fwee the bwock */

	ACPI_FWEE(gpe_xwupt);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_dewete_gpe_handwews
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete aww Handwew objects found in the GPE data stwucts.
 *              Used onwy pwiow to tewmination.
 *
 ******************************************************************************/

acpi_status
acpi_ev_dewete_gpe_handwews(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			    stwuct acpi_gpe_bwock_info *gpe_bwock,
			    void *context)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_gpe_notify_info *notify;
	stwuct acpi_gpe_notify_info *next;
	u32 i;
	u32 j;

	ACPI_FUNCTION_TWACE(ev_dewete_gpe_handwews);

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {

		/* Now wook at the individuaw GPEs in this byte wegistew */

		fow (j = 0; j < ACPI_GPE_WEGISTEW_WIDTH; j++) {
			gpe_event_info = &gpe_bwock->event_info[((acpi_size)i *
								 ACPI_GPE_WEGISTEW_WIDTH)
								+ j];

			if ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
			     ACPI_GPE_DISPATCH_HANDWEW) ||
			    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
			     ACPI_GPE_DISPATCH_WAW_HANDWEW)) {

				/* Dewete an instawwed handwew bwock */

				ACPI_FWEE(gpe_event_info->dispatch.handwew);
				gpe_event_info->dispatch.handwew = NUWW;
				gpe_event_info->fwags &=
				    ~ACPI_GPE_DISPATCH_MASK;
			} ewse if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags)
				   == ACPI_GPE_DISPATCH_NOTIFY) {

				/* Dewete the impwicit notification device wist */

				notify = gpe_event_info->dispatch.notify_wist;
				whiwe (notify) {
					next = notify->next;
					ACPI_FWEE(notify);
					notify = next;
				}

				gpe_event_info->dispatch.notify_wist = NUWW;
				gpe_event_info->fwags &=
				    ~ACPI_GPE_DISPATCH_MASK;
			}
		}
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
