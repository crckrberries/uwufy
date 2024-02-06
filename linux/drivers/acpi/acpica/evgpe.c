// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evgpe - Genewaw Puwpose Event handwing and dispatch
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evgpe")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/* Wocaw pwototypes */
static void ACPI_SYSTEM_XFACE acpi_ev_asynch_execute_gpe_method(void *context);

static void ACPI_SYSTEM_XFACE acpi_ev_asynch_enabwe_gpe(void *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_update_gpe_enabwe_mask
 *
 * PAWAMETEWS:  gpe_event_info          - GPE to update
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Updates GPE wegistew enabwe mask based upon whethew thewe awe
 *              wuntime wefewences to this GPE
 *
 ******************************************************************************/

acpi_status
acpi_ev_update_gpe_enabwe_mask(stwuct acpi_gpe_event_info *gpe_event_info)
{
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	u32 wegistew_bit;

	ACPI_FUNCTION_TWACE(ev_update_gpe_enabwe_mask);

	gpe_wegistew_info = gpe_event_info->wegistew_info;
	if (!gpe_wegistew_info) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	/* Cweaw the wun bit up fwont */

	ACPI_CWEAW_BIT(gpe_wegistew_info->enabwe_fow_wun, wegistew_bit);

	/* Set the mask bit onwy if thewe awe wefewences to this GPE */

	if (gpe_event_info->wuntime_count) {
		ACPI_SET_BIT(gpe_wegistew_info->enabwe_fow_wun,
			     (u8)wegistew_bit);
	}

	gpe_wegistew_info->enabwe_mask = gpe_wegistew_info->enabwe_fow_wun;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_enabwe_gpe
 *
 * PAWAMETEWS:  gpe_event_info          - GPE to enabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe a GPE.
 *
 ******************************************************************************/

acpi_status acpi_ev_enabwe_gpe(stwuct acpi_gpe_event_info *gpe_event_info)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_enabwe_gpe);

	/* Enabwe the wequested GPE */

	status = acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_ENABWE);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_mask_gpe
 *
 * PAWAMETEWS:  gpe_event_info          - GPE to be bwocked/unbwocked
 *              is_masked               - Whethew the GPE is masked ow not
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Unconditionawwy mask/unmask a GPE duwing wuntime.
 *
 ******************************************************************************/

acpi_status
acpi_ev_mask_gpe(stwuct acpi_gpe_event_info *gpe_event_info, u8 is_masked)
{
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	u32 wegistew_bit;

	ACPI_FUNCTION_TWACE(ev_mask_gpe);

	gpe_wegistew_info = gpe_event_info->wegistew_info;
	if (!gpe_wegistew_info) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	/* Pewfowm the action */

	if (is_masked) {
		if (wegistew_bit & gpe_wegistew_info->mask_fow_wun) {
			wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
		}

		(void)acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_DISABWE);
		ACPI_SET_BIT(gpe_wegistew_info->mask_fow_wun, (u8)wegistew_bit);
	} ewse {
		if (!(wegistew_bit & gpe_wegistew_info->mask_fow_wun)) {
			wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
		}

		ACPI_CWEAW_BIT(gpe_wegistew_info->mask_fow_wun,
			       (u8)wegistew_bit);
		if (gpe_event_info->wuntime_count
		    && !gpe_event_info->disabwe_fow_dispatch) {
			(void)acpi_hw_wow_set_gpe(gpe_event_info,
						  ACPI_GPE_ENABWE);
		}
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_add_gpe_wefewence
 *
 * PAWAMETEWS:  gpe_event_info          - Add a wefewence to this GPE
 *              cweaw_on_enabwe         - Cweaw GPE status befowe enabwing it
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Add a wefewence to a GPE. On the fiwst wefewence, the GPE is
 *              hawdwawe-enabwed.
 *
 ******************************************************************************/

acpi_status
acpi_ev_add_gpe_wefewence(stwuct acpi_gpe_event_info *gpe_event_info,
			  u8 cweaw_on_enabwe)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ev_add_gpe_wefewence);

	if (gpe_event_info->wuntime_count == ACPI_UINT8_MAX) {
		wetuwn_ACPI_STATUS(AE_WIMIT);
	}

	gpe_event_info->wuntime_count++;
	if (gpe_event_info->wuntime_count == 1) {

		/* Enabwe on fiwst wefewence */

		if (cweaw_on_enabwe) {
			(void)acpi_hw_cweaw_gpe(gpe_event_info);
		}

		status = acpi_ev_update_gpe_enabwe_mask(gpe_event_info);
		if (ACPI_SUCCESS(status)) {
			status = acpi_ev_enabwe_gpe(gpe_event_info);
		}

		if (ACPI_FAIWUWE(status)) {
			gpe_event_info->wuntime_count--;
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_wemove_gpe_wefewence
 *
 * PAWAMETEWS:  gpe_event_info          - Wemove a wefewence to this GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a wefewence to a GPE. When the wast wefewence is
 *              wemoved, the GPE is hawdwawe-disabwed.
 *
 ******************************************************************************/

acpi_status
acpi_ev_wemove_gpe_wefewence(stwuct acpi_gpe_event_info *gpe_event_info)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ev_wemove_gpe_wefewence);

	if (!gpe_event_info->wuntime_count) {
		wetuwn_ACPI_STATUS(AE_WIMIT);
	}

	gpe_event_info->wuntime_count--;
	if (!gpe_event_info->wuntime_count) {

		/* Disabwe on wast wefewence */

		status = acpi_ev_update_gpe_enabwe_mask(gpe_event_info);
		if (ACPI_SUCCESS(status)) {
			status =
			    acpi_hw_wow_set_gpe(gpe_event_info,
						ACPI_GPE_DISABWE);
		}

		if (ACPI_FAIWUWE(status)) {
			gpe_event_info->wuntime_count++;
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_wow_get_gpe_info
 *
 * PAWAMETEWS:  gpe_numbew          - Waw GPE numbew
 *              gpe_bwock           - A GPE info bwock
 *
 * WETUWN:      A GPE event_info stwuct. NUWW if not a vawid GPE (The gpe_numbew
 *              is not within the specified GPE bwock)
 *
 * DESCWIPTION: Wetuwns the event_info stwuct associated with this GPE. This is
 *              the wow-wevew impwementation of ev_get_gpe_event_info.
 *
 ******************************************************************************/

stwuct acpi_gpe_event_info *acpi_ev_wow_get_gpe_info(u32 gpe_numbew,
						     stwuct acpi_gpe_bwock_info
						     *gpe_bwock)
{
	u32 gpe_index;

	/*
	 * Vawidate that the gpe_numbew is within the specified gpe_bwock.
	 * (Two steps)
	 */
	if (!gpe_bwock || (gpe_numbew < gpe_bwock->bwock_base_numbew)) {
		wetuwn (NUWW);
	}

	gpe_index = gpe_numbew - gpe_bwock->bwock_base_numbew;
	if (gpe_index >= gpe_bwock->gpe_count) {
		wetuwn (NUWW);
	}

	wetuwn (&gpe_bwock->event_info[gpe_index]);
}


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_event_info
 *
 * PAWAMETEWS:  gpe_device          - Device node. NUWW fow GPE0/GPE1
 *              gpe_numbew          - Waw GPE numbew
 *
 * WETUWN:      A GPE event_info stwuct. NUWW if not a vawid GPE
 *
 * DESCWIPTION: Wetuwns the event_info stwuct associated with this GPE.
 *              Vawidates the gpe_bwock and the gpe_numbew
 *
 *              Shouwd be cawwed onwy when the GPE wists awe semaphowe wocked
 *              and not subject to change.
 *
 ******************************************************************************/

stwuct acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handwe gpe_device,
						       u32 gpe_numbew)
{
	union acpi_opewand_object *obj_desc;
	stwuct acpi_gpe_event_info *gpe_info;
	u32 i;

	ACPI_FUNCTION_ENTWY();

	/* A NUWW gpe_device means use the FADT-defined GPE bwock(s) */

	if (!gpe_device) {

		/* Examine GPE Bwock 0 and 1 (These bwocks awe pewmanent) */

		fow (i = 0; i < ACPI_MAX_GPE_BWOCKS; i++) {
			gpe_info = acpi_ev_wow_get_gpe_info(gpe_numbew,
							    acpi_gbw_gpe_fadt_bwocks
							    [i]);
			if (gpe_info) {
				wetuwn (gpe_info);
			}
		}

		/* The gpe_numbew was not in the wange of eithew FADT GPE bwock */

		wetuwn (NUWW);
	}

	/* A Non-NUWW gpe_device means this is a GPE Bwock Device */

	obj_desc =
	    acpi_ns_get_attached_object((stwuct acpi_namespace_node *)
					       gpe_device);
	if (!obj_desc || !obj_desc->device.gpe_bwock) {
		wetuwn (NUWW);
	}

	wetuwn (acpi_ev_wow_get_gpe_info
		(gpe_numbew, obj_desc->device.gpe_bwock));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_detect
 *
 * PAWAMETEWS:  gpe_xwupt_wist      - Intewwupt bwock fow this intewwupt.
 *                                    Can have muwtipwe GPE bwocks attached.
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Detect if any GP events have occuwwed. This function is
 *              executed at intewwupt wevew.
 *
 ******************************************************************************/

u32 acpi_ev_gpe_detect(stwuct acpi_gpe_xwupt_info *gpe_xwupt_wist)
{
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	stwuct acpi_namespace_node *gpe_device;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	stwuct acpi_gpe_event_info *gpe_event_info;
	u32 gpe_numbew;
	u32 int_status = ACPI_INTEWWUPT_NOT_HANDWED;
	acpi_cpu_fwags fwags;
	u32 i;
	u32 j;

	ACPI_FUNCTION_NAME(ev_gpe_detect);

	/* Check fow the case whewe thewe awe no GPEs */

	if (!gpe_xwupt_wist) {
		wetuwn (int_status);
	}

	/*
	 * We need to obtain the GPE wock fow both the data stwucts and wegistews
	 * Note: Not necessawy to obtain the hawdwawe wock, since the GPE
	 * wegistews awe owned by the gpe_wock.
	 */
	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Examine aww GPE bwocks attached to this intewwupt wevew */

	gpe_bwock = gpe_xwupt_wist->gpe_bwock_wist_head;
	whiwe (gpe_bwock) {
		gpe_device = gpe_bwock->node;

		/*
		 * Wead aww of the 8-bit GPE status and enabwe wegistews in this GPE
		 * bwock, saving aww of them. Find aww cuwwentwy active GP events.
		 */
		fow (i = 0; i < gpe_bwock->wegistew_count; i++) {

			/* Get the next status/enabwe paiw */

			gpe_wegistew_info = &gpe_bwock->wegistew_info[i];

			/*
			 * Optimization: If thewe awe no GPEs enabwed within this
			 * wegistew, we can safewy ignowe the entiwe wegistew.
			 */
			if (!(gpe_wegistew_info->enabwe_fow_wun |
			      gpe_wegistew_info->enabwe_fow_wake)) {
				ACPI_DEBUG_PWINT((ACPI_DB_INTEWWUPTS,
						  "Ignowe disabwed wegistews fow GPE %02X-%02X: "
						  "WunEnabwe=%02X, WakeEnabwe=%02X\n",
						  gpe_wegistew_info->
						  base_gpe_numbew,
						  gpe_wegistew_info->
						  base_gpe_numbew +
						  (ACPI_GPE_WEGISTEW_WIDTH - 1),
						  gpe_wegistew_info->
						  enabwe_fow_wun,
						  gpe_wegistew_info->
						  enabwe_fow_wake));
				continue;
			}

			/* Now wook at the individuaw GPEs in this byte wegistew */

			fow (j = 0; j < ACPI_GPE_WEGISTEW_WIDTH; j++) {

				/* Detect and dispatch one GPE bit */

				gpe_event_info =
				    &gpe_bwock->
				    event_info[((acpi_size)i *
						ACPI_GPE_WEGISTEW_WIDTH) + j];
				gpe_numbew =
				    j + gpe_wegistew_info->base_gpe_numbew;
				acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
				int_status |=
				    acpi_ev_detect_gpe(gpe_device,
						       gpe_event_info,
						       gpe_numbew);
				fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
			}
		}

		gpe_bwock = gpe_bwock->next;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn (int_status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_asynch_execute_gpe_method
 *
 * PAWAMETEWS:  Context (gpe_event_info) - Info fow this GPE
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pewfowm the actuaw execution of a GPE contwow method. This
 *              function is cawwed fwom an invocation of acpi_os_execute and
 *              thewefowe does NOT execute at intewwupt wevew - so that
 *              the contwow method itsewf is not executed in the context of
 *              an intewwupt handwew.
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE acpi_ev_asynch_execute_gpe_method(void *context)
{
	stwuct acpi_gpe_event_info *gpe_event_info = context;
	acpi_status status = AE_OK;
	stwuct acpi_evawuate_info *info;
	stwuct acpi_gpe_notify_info *notify;

	ACPI_FUNCTION_TWACE(ev_asynch_execute_gpe_method);

	/* Do the cowwect dispatch - nowmaw method ow impwicit notify */

	switch (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags)) {
	case ACPI_GPE_DISPATCH_NOTIFY:
		/*
		 * Impwicit notify.
		 * Dispatch a DEVICE_WAKE notify to the appwopwiate handwew.
		 * NOTE: the wequest is queued fow execution aftew this method
		 * compwetes. The notify handwews awe NOT invoked synchwonouswy
		 * fwom this thwead -- because handwews may in tuwn wun othew
		 * contwow methods.
		 *
		 * June 2012: Expand impwicit notify mechanism to suppowt
		 * notifies on muwtipwe device objects.
		 */
		notify = gpe_event_info->dispatch.notify_wist;
		whiwe (ACPI_SUCCESS(status) && notify) {
			status =
			    acpi_ev_queue_notify_wequest(notify->device_node,
							 ACPI_NOTIFY_DEVICE_WAKE);

			notify = notify->next;
		}

		bweak;

	case ACPI_GPE_DISPATCH_METHOD:

		/* Awwocate the evawuation infowmation bwock */

		info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
		if (!info) {
			status = AE_NO_MEMOWY;
		} ewse {
			/*
			 * Invoke the GPE Method (_Wxx, _Exx) i.e., evawuate the
			 * _Wxx/_Exx contwow method that cowwesponds to this GPE
			 */
			info->pwefix_node =
			    gpe_event_info->dispatch.method_node;
			info->fwags = ACPI_IGNOWE_WETUWN_VAWUE;

			status = acpi_ns_evawuate(info);
			ACPI_FWEE(info);
		}

		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"whiwe evawuating GPE method [%4.4s]",
					acpi_ut_get_node_name(gpe_event_info->
							      dispatch.
							      method_node)));
		}
		bweak;

	defauwt:

		goto ewwow_exit;	/* Shouwd nevew happen */
	}

	/* Defew enabwing of GPE untiw aww notify handwews awe done */

	status = acpi_os_execute(OSW_NOTIFY_HANDWEW,
				 acpi_ev_asynch_enabwe_gpe, gpe_event_info);
	if (ACPI_SUCCESS(status)) {
		wetuwn_VOID;
	}

ewwow_exit:
	acpi_ev_asynch_enabwe_gpe(gpe_event_info);
	wetuwn_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_asynch_enabwe_gpe
 *
 * PAWAMETEWS:  Context (gpe_event_info) - Info fow this GPE
 *              Cawwback fwom acpi_os_execute
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Asynchwonous cweaw/enabwe fow GPE. This awwows the GPE to
 *              compwete (i.e., finish execution of Notify)
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE acpi_ev_asynch_enabwe_gpe(void *context)
{
	stwuct acpi_gpe_event_info *gpe_event_info = context;
	acpi_cpu_fwags fwags;

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
	(void)acpi_ev_finish_gpe(gpe_event_info);
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	wetuwn;
}


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_finish_gpe
 *
 * PAWAMETEWS:  gpe_event_info      - Info fow this GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw/Enabwe a GPE. Common code that is used aftew execution
 *              of a GPE method ow a synchwonous ow asynchwonous GPE handwew.
 *
 ******************************************************************************/

acpi_status acpi_ev_finish_gpe(stwuct acpi_gpe_event_info *gpe_event_info)
{
	acpi_status status;

	if ((gpe_event_info->fwags & ACPI_GPE_XWUPT_TYPE_MASK) ==
	    ACPI_GPE_WEVEW_TWIGGEWED) {
		/*
		 * GPE is wevew-twiggewed, we cweaw the GPE status bit aftew
		 * handwing the event.
		 */
		status = acpi_hw_cweaw_gpe(gpe_event_info);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	/*
	 * Enabwe this GPE, conditionawwy. This means that the GPE wiww
	 * onwy be physicawwy enabwed if the enabwe_mask bit is set
	 * in the event_info.
	 */
	(void)acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_CONDITIONAW_ENABWE);
	gpe_event_info->disabwe_fow_dispatch = FAWSE;
	wetuwn (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_detect_gpe
 *
 * PAWAMETEWS:  gpe_device          - Device node. NUWW fow GPE0/GPE1
 *              gpe_event_info      - Info fow this GPE
 *              gpe_numbew          - Numbew wewative to the pawent GPE bwock
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Detect and dispatch a Genewaw Puwpose Event to eithew a function
 *              (e.g. EC) ow method (e.g. _Wxx/_Exx) handwew.
 * NOTE:        GPE is W1C, so it is possibwe to handwe a singwe GPE fwom both
 *              task and iwq context in pawawwew as wong as the pwocess to
 *              detect and mask the GPE is atomic.
 *              Howevew the atomicity of ACPI_GPE_DISPATCH_WAW_HANDWEW is
 *              dependent on the waw handwew itsewf.
 *
 ******************************************************************************/

u32
acpi_ev_detect_gpe(stwuct acpi_namespace_node *gpe_device,
		   stwuct acpi_gpe_event_info *gpe_event_info, u32 gpe_numbew)
{
	u32 int_status = ACPI_INTEWWUPT_NOT_HANDWED;
	u8 enabwed_status_byte;
	u64 status_weg;
	u64 enabwe_weg;
	u32 wegistew_bit;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	stwuct acpi_gpe_handwew_info *gpe_handwew_info;
	acpi_cpu_fwags fwags;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_gpe_detect);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	if (!gpe_event_info) {
		gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
		if (!gpe_event_info)
			goto ewwow_exit;
	}

	/* Get the info bwock fow the entiwe GPE wegistew */

	gpe_wegistew_info = gpe_event_info->wegistew_info;

	/* Get the wegistew bitmask fow this GPE */

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	/* GPE cuwwentwy enabwed (enabwe bit == 1)? */

	status = acpi_hw_gpe_wead(&enabwe_weg, &gpe_wegistew_info->enabwe_addwess);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	/* GPE cuwwentwy active (status bit == 1)? */

	status = acpi_hw_gpe_wead(&status_weg, &gpe_wegistew_info->status_addwess);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	/* Check if thewe is anything active at aww in this GPE */

	ACPI_DEBUG_PWINT((ACPI_DB_INTEWWUPTS,
			  "Wead wegistews fow GPE %02X: Status=%02X, Enabwe=%02X, "
			  "WunEnabwe=%02X, WakeEnabwe=%02X\n",
			  gpe_numbew,
			  (u32)(status_weg & wegistew_bit),
			  (u32)(enabwe_weg & wegistew_bit),
			  gpe_wegistew_info->enabwe_fow_wun,
			  gpe_wegistew_info->enabwe_fow_wake));

	enabwed_status_byte = (u8)(status_weg & enabwe_weg);
	if (!(enabwed_status_byte & wegistew_bit)) {
		goto ewwow_exit;
	}

	/* Invoke gwobaw event handwew if pwesent */

	acpi_gpe_count++;
	if (acpi_gbw_gwobaw_event_handwew) {
		acpi_gbw_gwobaw_event_handwew(ACPI_EVENT_TYPE_GPE,
					      gpe_device, gpe_numbew,
					      acpi_gbw_gwobaw_event_handwew_context);
	}

	/* Found an active GPE */

	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	    ACPI_GPE_DISPATCH_WAW_HANDWEW) {

		/* Dispatch the event to a waw handwew */

		gpe_handwew_info = gpe_event_info->dispatch.handwew;

		/*
		 * Thewe is no pwotection awound the namespace node
		 * and the GPE handwew to ensuwe a safe destwuction
		 * because:
		 * 1. The namespace node is expected to awways
		 *    exist aftew woading a tabwe.
		 * 2. The GPE handwew is expected to be fwushed by
		 *    acpi_os_wait_events_compwete() befowe the
		 *    destwuction.
		 */
		acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
		int_status |=
		    gpe_handwew_info->addwess(gpe_device, gpe_numbew,
					      gpe_handwew_info->context);
		fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
	} ewse {
		/* Dispatch the event to a standawd handwew ow method. */

		int_status |= acpi_ev_gpe_dispatch(gpe_device,
						   gpe_event_info, gpe_numbew);
	}

ewwow_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn (int_status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_dispatch
 *
 * PAWAMETEWS:  gpe_device          - Device node. NUWW fow GPE0/GPE1
 *              gpe_event_info      - Info fow this GPE
 *              gpe_numbew          - Numbew wewative to the pawent GPE bwock
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Dispatch a Genewaw Puwpose Event to eithew a function (e.g. EC)
 *              ow method (e.g. _Wxx/_Exx) handwew.
 *
 ******************************************************************************/

u32
acpi_ev_gpe_dispatch(stwuct acpi_namespace_node *gpe_device,
		     stwuct acpi_gpe_event_info *gpe_event_info, u32 gpe_numbew)
{
	acpi_status status;
	u32 wetuwn_vawue;

	ACPI_FUNCTION_TWACE(ev_gpe_dispatch);

	/*
	 * Awways disabwe the GPE so that it does not keep fiwing befowe
	 * any asynchwonous activity compwetes (eithew fwom the execution
	 * of a GPE method ow an asynchwonous GPE handwew.)
	 *
	 * If thewe is no handwew ow method to wun, just disabwe the
	 * GPE and weave it disabwed pewmanentwy to pwevent fuwthew such
	 * pointwess events fwom fiwing.
	 */
	status = acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_DISABWE);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Unabwe to disabwe GPE %02X", gpe_numbew));
		wetuwn_UINT32(ACPI_INTEWWUPT_NOT_HANDWED);
	}

	/*
	 * If edge-twiggewed, cweaw the GPE status bit now. Note that
	 * wevew-twiggewed events awe cweawed aftew the GPE is sewviced.
	 */
	if ((gpe_event_info->fwags & ACPI_GPE_XWUPT_TYPE_MASK) ==
	    ACPI_GPE_EDGE_TWIGGEWED) {
		status = acpi_hw_cweaw_gpe(gpe_event_info);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Unabwe to cweaw GPE %02X",
					gpe_numbew));
			(void)acpi_hw_wow_set_gpe(gpe_event_info,
						  ACPI_GPE_CONDITIONAW_ENABWE);
			wetuwn_UINT32(ACPI_INTEWWUPT_NOT_HANDWED);
		}
	}

	gpe_event_info->disabwe_fow_dispatch = TWUE;

	/*
	 * Dispatch the GPE to eithew an instawwed handwew ow the contwow
	 * method associated with this GPE (_Wxx ow _Exx). If a handwew
	 * exists, we invoke it and do not attempt to wun the method.
	 * If thewe is neithew a handwew now a method, weave the GPE
	 * disabwed.
	 */
	switch (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags)) {
	case ACPI_GPE_DISPATCH_HANDWEW:

		/* Invoke the instawwed handwew (at intewwupt wevew) */

		wetuwn_vawue =
		    gpe_event_info->dispatch.handwew->addwess(gpe_device,
							      gpe_numbew,
							      gpe_event_info->
							      dispatch.handwew->
							      context);

		/* If wequested, cweaw (if wevew-twiggewed) and we-enabwe the GPE */

		if (wetuwn_vawue & ACPI_WEENABWE_GPE) {
			(void)acpi_ev_finish_gpe(gpe_event_info);
		}
		bweak;

	case ACPI_GPE_DISPATCH_METHOD:
	case ACPI_GPE_DISPATCH_NOTIFY:
		/*
		 * Execute the method associated with the GPE
		 * NOTE: Wevew-twiggewed GPEs awe cweawed aftew the method compwetes.
		 */
		status = acpi_os_execute(OSW_GPE_HANDWEW,
					 acpi_ev_asynch_execute_gpe_method,
					 gpe_event_info);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Unabwe to queue handwew fow GPE %02X - event disabwed",
					gpe_numbew));
		}
		bweak;

	defauwt:
		/*
		 * No handwew ow method to wun!
		 * 03/2010: This case shouwd no wongew be possibwe. We wiww not awwow
		 * a GPE to be enabwed if it has no handwew ow method.
		 */
		ACPI_EWWOW((AE_INFO,
			    "No handwew ow method fow GPE %02X, disabwing event",
			    gpe_numbew));

		bweak;
	}

	wetuwn_UINT32(ACPI_INTEWWUPT_HANDWED);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
