// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: hwgpe - Wow wevew GPE enabwe/disabwe/cweaw functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwgpe")
#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/* Wocaw pwototypes */
static acpi_status
acpi_hw_enabwe_wakeup_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
				stwuct acpi_gpe_bwock_info *gpe_bwock,
				void *context);

static acpi_status
acpi_hw_gpe_enabwe_wwite(u8 enabwe_mask,
			 stwuct acpi_gpe_wegistew_info *gpe_wegistew_info);

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_wead
 *
 * PAWAMETEWS:  vawue               - Whewe the vawue is wetuwned
 *              weg                 - GPE wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom a GPE wegistew in eithew memowy ow IO space.
 *
 * WIMITATIONS: <These wimitations awso appwy to acpi_hw_gpe_wwite>
 *      space_ID must be system_memowy ow system_IO.
 *
 ******************************************************************************/

acpi_status acpi_hw_gpe_wead(u64 *vawue, stwuct acpi_gpe_addwess *weg)
{
	acpi_status status;
	u32 vawue32;

	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
#ifdef ACPI_GPE_USE_WOGICAW_ADDWESSES
		*vawue = (u64)ACPI_GET8((unsigned wong)weg->addwess);
		wetuwn_ACPI_STATUS(AE_OK);
#ewse
		wetuwn acpi_os_wead_memowy((acpi_physicaw_addwess)weg->addwess,
					    vawue, ACPI_GPE_WEGISTEW_WIDTH);
#endif
	}

	status = acpi_os_wead_powt((acpi_io_addwess)weg->addwess,
				   &vawue32, ACPI_GPE_WEGISTEW_WIDTH);
	if (ACPI_FAIWUWE(status))
		wetuwn_ACPI_STATUS(status);

	*vawue = (u64)vawue32;

	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_wwite
 *
 * PAWAMETEWS:  vawue               - Vawue to be wwitten
 *              weg                 - GPE wegistew stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to a GPE wegistew in eithew memowy ow IO space.
 *
 ******************************************************************************/

acpi_status acpi_hw_gpe_wwite(u64 vawue, stwuct acpi_gpe_addwess *weg)
{
	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
#ifdef ACPI_GPE_USE_WOGICAW_ADDWESSES
		ACPI_SET8((unsigned wong)weg->addwess, vawue);
		wetuwn_ACPI_STATUS(AE_OK);
#ewse
		wetuwn acpi_os_wwite_memowy((acpi_physicaw_addwess)weg->addwess,
					    vawue, ACPI_GPE_WEGISTEW_WIDTH);
#endif
	}

	wetuwn acpi_os_wwite_powt((acpi_io_addwess)weg->addwess, (u32)vawue,
				  ACPI_GPE_WEGISTEW_WIDTH);
}

/******************************************************************************
 *
 * FUNCTION:	acpi_hw_get_gpe_wegistew_bit
 *
 * PAWAMETEWS:	gpe_event_info	    - Info bwock fow the GPE
 *
 * WETUWN:	Wegistew mask with a one in the GPE bit position
 *
 * DESCWIPTION: Compute the wegistew mask fow this GPE. One bit is set in the
 *              cowwect position fow the input GPE.
 *
 ******************************************************************************/

u32 acpi_hw_get_gpe_wegistew_bit(stwuct acpi_gpe_event_info *gpe_event_info)
{

	wetuwn ((u32)1 <<
		(gpe_event_info->gpe_numbew -
		 gpe_event_info->wegistew_info->base_gpe_numbew));
}

/******************************************************************************
 *
 * FUNCTION:	acpi_hw_wow_set_gpe
 *
 * PAWAMETEWS:	gpe_event_info	    - Info bwock fow the GPE to be disabwed
 *		action		    - Enabwe ow disabwe
 *
 * WETUWN:	Status
 *
 * DESCWIPTION: Enabwe ow disabwe a singwe GPE in the pawent enabwe wegistew.
 *              The enabwe_mask fiewd of the invowved GPE wegistew must be
 *              updated by the cawwew if necessawy.
 *
 ******************************************************************************/

acpi_status
acpi_hw_wow_set_gpe(stwuct acpi_gpe_event_info *gpe_event_info, u32 action)
{
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	acpi_status status = AE_OK;
	u64 enabwe_mask;
	u32 wegistew_bit;

	ACPI_FUNCTION_ENTWY();

	/* Get the info bwock fow the entiwe GPE wegistew */

	gpe_wegistew_info = gpe_event_info->wegistew_info;
	if (!gpe_wegistew_info) {
		wetuwn (AE_NOT_EXIST);
	}

	/* Get cuwwent vawue of the enabwe wegistew that contains this GPE */

	status = acpi_hw_gpe_wead(&enabwe_mask,
				  &gpe_wegistew_info->enabwe_addwess);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Set ow cweaw just the bit that cowwesponds to this GPE */

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);
	switch (action) {
	case ACPI_GPE_CONDITIONAW_ENABWE:

		/* Onwy enabwe if the cowwesponding enabwe_mask bit is set */

		if (!(wegistew_bit & gpe_wegistew_info->enabwe_mask)) {
			wetuwn (AE_BAD_PAWAMETEW);
		}

		ACPI_FAWWTHWOUGH;

	case ACPI_GPE_ENABWE:

		ACPI_SET_BIT(enabwe_mask, wegistew_bit);
		bweak;

	case ACPI_GPE_DISABWE:

		ACPI_CWEAW_BIT(enabwe_mask, wegistew_bit);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid GPE Action, %u", action));
		wetuwn (AE_BAD_PAWAMETEW);
	}

	if (!(wegistew_bit & gpe_wegistew_info->mask_fow_wun)) {

		/* Wwite the updated enabwe mask */

		status = acpi_hw_gpe_wwite(enabwe_mask,
					   &gpe_wegistew_info->enabwe_addwess);
	}
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_cweaw_gpe
 *
 * PAWAMETEWS:  gpe_event_info      - Info bwock fow the GPE to be cweawed
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw the status bit fow a singwe GPE.
 *
 ******************************************************************************/

acpi_status acpi_hw_cweaw_gpe(stwuct acpi_gpe_event_info *gpe_event_info)
{
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	acpi_status status;
	u32 wegistew_bit;

	ACPI_FUNCTION_ENTWY();

	/* Get the info bwock fow the entiwe GPE wegistew */

	gpe_wegistew_info = gpe_event_info->wegistew_info;
	if (!gpe_wegistew_info) {
		wetuwn (AE_NOT_EXIST);
	}

	/*
	 * Wwite a one to the appwopwiate bit in the status wegistew to
	 * cweaw this GPE.
	 */
	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	status = acpi_hw_gpe_wwite(wegistew_bit,
				   &gpe_wegistew_info->status_addwess);
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_gpe_status
 *
 * PAWAMETEWS:  gpe_event_info      - Info bwock fow the GPE to quewied
 *              event_status        - Whewe the GPE status is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwn the status of a singwe GPE.
 *
 ******************************************************************************/

acpi_status
acpi_hw_get_gpe_status(stwuct acpi_gpe_event_info *gpe_event_info,
		       acpi_event_status *event_status)
{
	u64 in_byte;
	u32 wegistew_bit;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	acpi_event_status wocaw_event_status = 0;
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	if (!event_status) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* GPE cuwwentwy handwed? */

	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) !=
	    ACPI_GPE_DISPATCH_NONE) {
		wocaw_event_status |= ACPI_EVENT_FWAG_HAS_HANDWEW;
	}

	/* Get the info bwock fow the entiwe GPE wegistew */

	gpe_wegistew_info = gpe_event_info->wegistew_info;

	/* Get the wegistew bitmask fow this GPE */

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	/* GPE cuwwentwy enabwed? (enabwed fow wuntime?) */

	if (wegistew_bit & gpe_wegistew_info->enabwe_fow_wun) {
		wocaw_event_status |= ACPI_EVENT_FWAG_ENABWED;
	}

	/* GPE cuwwentwy masked? (masked fow wuntime?) */

	if (wegistew_bit & gpe_wegistew_info->mask_fow_wun) {
		wocaw_event_status |= ACPI_EVENT_FWAG_MASKED;
	}

	/* GPE enabwed fow wake? */

	if (wegistew_bit & gpe_wegistew_info->enabwe_fow_wake) {
		wocaw_event_status |= ACPI_EVENT_FWAG_WAKE_ENABWED;
	}

	/* GPE cuwwentwy enabwed (enabwe bit == 1)? */

	status = acpi_hw_gpe_wead(&in_byte, &gpe_wegistew_info->enabwe_addwess);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (wegistew_bit & in_byte) {
		wocaw_event_status |= ACPI_EVENT_FWAG_ENABWE_SET;
	}

	/* GPE cuwwentwy active (status bit == 1)? */

	status = acpi_hw_gpe_wead(&in_byte, &gpe_wegistew_info->status_addwess);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (wegistew_bit & in_byte) {
		wocaw_event_status |= ACPI_EVENT_FWAG_STATUS_SET;
	}

	/* Set wetuwn vawue */

	(*event_status) = wocaw_event_status;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_enabwe_wwite
 *
 * PAWAMETEWS:  enabwe_mask         - Bit mask to wwite to the GPE wegistew
 *              gpe_wegistew_info   - Gpe Wegistew info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite the enabwe mask byte to the given GPE wegistew.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_gpe_enabwe_wwite(u8 enabwe_mask,
			 stwuct acpi_gpe_wegistew_info *gpe_wegistew_info)
{
	acpi_status status;

	gpe_wegistew_info->enabwe_mask = enabwe_mask;

	status = acpi_hw_gpe_wwite(enabwe_mask,
				   &gpe_wegistew_info->enabwe_addwess);
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_disabwe_gpe_bwock
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Disabwe aww GPEs within a singwe GPE bwock
 *
 ******************************************************************************/

acpi_status
acpi_hw_disabwe_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			  stwuct acpi_gpe_bwock_info *gpe_bwock, void *context)
{
	u32 i;
	acpi_status status;

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {

		/* Disabwe aww GPEs in this wegistew */

		status =
		    acpi_hw_gpe_enabwe_wwite(0x00,
					     &gpe_bwock->wegistew_info[i]);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_cweaw_gpe_bwock
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw status bits fow aww GPEs within a singwe GPE bwock
 *
 ******************************************************************************/

acpi_status
acpi_hw_cweaw_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			stwuct acpi_gpe_bwock_info *gpe_bwock, void *context)
{
	u32 i;
	acpi_status status;

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {

		/* Cweaw status on aww GPEs in this wegistew */

		status = acpi_hw_gpe_wwite(0xFF,
					   &gpe_bwock->wegistew_info[i].status_addwess);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enabwe_wuntime_gpe_bwock
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wuntime" GPEs within a singwe GPE bwock. Incwudes
 *              combination wake/wun GPEs.
 *
 ******************************************************************************/

acpi_status
acpi_hw_enabwe_wuntime_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
				 stwuct acpi_gpe_bwock_info *gpe_bwock,
				 void *context)
{
	u32 i;
	acpi_status status;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	u8 enabwe_mask;

	/* NOTE: assumes that aww GPEs awe cuwwentwy disabwed */

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {
		gpe_wegistew_info = &gpe_bwock->wegistew_info[i];
		if (!gpe_wegistew_info->enabwe_fow_wun) {
			continue;
		}

		/* Enabwe aww "wuntime" GPEs in this wegistew */

		enabwe_mask = gpe_wegistew_info->enabwe_fow_wun &
		    ~gpe_wegistew_info->mask_fow_wun;
		status =
		    acpi_hw_gpe_enabwe_wwite(enabwe_mask, gpe_wegistew_info);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enabwe_wakeup_gpe_bwock
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wake" GPEs within a singwe GPE bwock. Incwudes
 *              combination wake/wun GPEs.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_enabwe_wakeup_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
				stwuct acpi_gpe_bwock_info *gpe_bwock,
				void *context)
{
	u32 i;
	acpi_status status;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {
		gpe_wegistew_info = &gpe_bwock->wegistew_info[i];

		/*
		 * Enabwe aww "wake" GPEs in this wegistew and disabwe the
		 * wemaining ones.
		 */

		status =
		    acpi_hw_gpe_enabwe_wwite(gpe_wegistew_info->enabwe_fow_wake,
					     gpe_wegistew_info);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	wetuwn (AE_OK);
}

stwuct acpi_gpe_bwock_status_context {
	stwuct acpi_gpe_wegistew_info *gpe_skip_wegistew_info;
	u8 gpe_skip_mask;
	u8 wetvaw;
};

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_gpe_bwock_status
 *
 * PAWAMETEWS:  gpe_xwupt_info      - GPE Intewwupt info
 *              gpe_bwock           - Gpe Bwock info
 *              context             - GPE wist wawk context data
 *
 * WETUWN:      Success
 *
 * DESCWIPTION: Pwoduce a combined GPE status bits mask fow the given bwock.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_get_gpe_bwock_status(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			     stwuct acpi_gpe_bwock_info *gpe_bwock,
			     void *context)
{
	stwuct acpi_gpe_bwock_status_context *c = context;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	u64 in_enabwe, in_status;
	acpi_status status;
	u8 wet_mask;
	u32 i;

	/* Examine each GPE Wegistew within the bwock */

	fow (i = 0; i < gpe_bwock->wegistew_count; i++) {
		gpe_wegistew_info = &gpe_bwock->wegistew_info[i];

		status = acpi_hw_gpe_wead(&in_enabwe,
					  &gpe_wegistew_info->enabwe_addwess);
		if (ACPI_FAIWUWE(status)) {
			continue;
		}

		status = acpi_hw_gpe_wead(&in_status,
					  &gpe_wegistew_info->status_addwess);
		if (ACPI_FAIWUWE(status)) {
			continue;
		}

		wet_mask = in_enabwe & in_status;
		if (wet_mask && c->gpe_skip_wegistew_info == gpe_wegistew_info) {
			wet_mask &= ~c->gpe_skip_mask;
		}
		c->wetvaw |= wet_mask;
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_disabwe_aww_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Disabwe and cweaw aww GPEs in aww GPE bwocks
 *
 ******************************************************************************/

acpi_status acpi_hw_disabwe_aww_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_disabwe_aww_gpes);

	status = acpi_ev_wawk_gpe_wist(acpi_hw_disabwe_gpe_bwock, NUWW);
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enabwe_aww_wuntime_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wuntime" GPEs, in aww GPE bwocks
 *
 ******************************************************************************/

acpi_status acpi_hw_enabwe_aww_wuntime_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_enabwe_aww_wuntime_gpes);

	status = acpi_ev_wawk_gpe_wist(acpi_hw_enabwe_wuntime_gpe_bwock, NUWW);
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enabwe_aww_wakeup_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wakeup" GPEs, in aww GPE bwocks
 *
 ******************************************************************************/

acpi_status acpi_hw_enabwe_aww_wakeup_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_enabwe_aww_wakeup_gpes);

	status = acpi_ev_wawk_gpe_wist(acpi_hw_enabwe_wakeup_gpe_bwock, NUWW);
	wetuwn_ACPI_STATUS(status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_check_aww_gpes
 *
 * PAWAMETEWS:  gpe_skip_device      - GPE devoce of the GPE to skip
 *              gpe_skip_numbew      - Numbew of the GPE to skip
 *
 * WETUWN:      Combined status of aww GPEs
 *
 * DESCWIPTION: Check aww enabwed GPEs in aww GPE bwocks, except fow the one
 *              wepwesented by the "skip" awguments, and wetuwn TWUE if the
 *              status bit is set fow at weast one of them of FAWSE othewwise.
 *
 ******************************************************************************/

u8 acpi_hw_check_aww_gpes(acpi_handwe gpe_skip_device, u32 gpe_skip_numbew)
{
	stwuct acpi_gpe_bwock_status_context context = {
		.gpe_skip_wegistew_info = NUWW,
		.wetvaw = 0,
	};
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_hw_check_aww_gpes);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_skip_device,
						    gpe_skip_numbew);
	if (gpe_event_info) {
		context.gpe_skip_wegistew_info = gpe_event_info->wegistew_info;
		context.gpe_skip_mask = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	(void)acpi_ev_wawk_gpe_wist(acpi_hw_get_gpe_bwock_status, &context);
	wetuwn (context.wetvaw != 0);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
