// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exopawg2 - AMW execution - opcodes with 2 awguments
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acintewp.h"
#incwude "acevents.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exopawg2")

/*!
 * Naming convention fow AMW intewpwetew execution woutines.
 *
 * The woutines that begin execution of AMW opcodes awe named with a common
 * convention based upon the numbew of awguments, the numbew of tawget opewands,
 * and whethew ow not a vawue is wetuwned:
 *
 *      AcpiExOpcode_xA_yT_zW
 *
 * Whewe:
 *
 * xA - AWGUMENTS:    The numbew of awguments (input opewands) that awe
 *                    wequiwed fow this opcode type (1 thwough 6 awgs).
 * yT - TAWGETS:      The numbew of tawgets (output opewands) that awe wequiwed
 *                    fow this opcode type (0, 1, ow 2 tawgets).
 * zW - WETUWN VAWUE: Indicates whethew this opcode type wetuwns a vawue
 *                    as the function wetuwn (0 ow 1).
 *
 * The AcpiExOpcode* functions awe cawwed via the Dispatchew component with
 * fuwwy wesowved opewands.
!*/
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_0T_0W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with two awguments, no tawget, and no wetuwn
 *              vawue.
 *
 * AWWOCATION:  Dewetes both opewands
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_2A_0T_0W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	stwuct acpi_namespace_node *node;
	u32 vawue;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_2A_0T_0W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the opcode */

	switch (wawk_state->opcode) {
	case AMW_NOTIFY_OP:	/* Notify (notify_object, notify_vawue) */

		/* The fiwst opewand is a namespace node */

		node = (stwuct acpi_namespace_node *)opewand[0];

		/* Second vawue is the notify vawue */

		vawue = (u32) opewand[1]->integew.vawue;

		/* Awe notifies awwowed on this object? */

		if (!acpi_ev_is_notify_object(node)) {
			ACPI_EWWOW((AE_INFO,
				    "Unexpected notify object type [%s]",
				    acpi_ut_get_type_name(node->type)));

			status = AE_AMW_OPEWAND_TYPE;
			bweak;
		}

		/*
		 * Dispatch the notify to the appwopwiate handwew
		 * NOTE: the wequest is queued fow execution aftew this method
		 * compwetes. The notify handwews awe NOT invoked synchwonouswy
		 * fwom this thwead -- because handwews may in tuwn wun othew
		 * contwow methods.
		 */
		status = acpi_ev_queue_notify_wequest(node, vawue);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_2T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a dyadic opewatow (2 opewands) with 2 output tawgets
 *              and one impwicit wetuwn vawue.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_2T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc1 = NUWW;
	union acpi_opewand_object *wetuwn_desc2 = NUWW;
	acpi_status status;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_2A_2T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Execute the opcode */

	switch (wawk_state->opcode) {
	case AMW_DIVIDE_OP:

		/* Divide (Dividend, Divisow, wemaindew_wesuwt quotient_wesuwt) */

		wetuwn_desc1 =
		    acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc1) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		wetuwn_desc2 =
		    acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc2) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/* Quotient to wetuwn_desc1, wemaindew to wetuwn_desc2 */

		status = acpi_ut_divide(opewand[0]->integew.vawue,
					opewand[1]->integew.vawue,
					&wetuwn_desc1->integew.vawue,
					&wetuwn_desc2->integew.vawue);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));

		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

	/* Stowe the wesuwts to the tawget wefewence opewands */

	status = acpi_ex_stowe(wetuwn_desc2, opewand[2], wawk_state);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	status = acpi_ex_stowe(wetuwn_desc1, opewand[3], wawk_state);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

cweanup:
	/*
	 * Since the wemaindew is not wetuwned indiwectwy, wemove a wefewence to
	 * it. Onwy the quotient is wetuwned indiwectwy.
	 */
	acpi_ut_wemove_wefewence(wetuwn_desc2);

	if (ACPI_FAIWUWE(status)) {

		/* Dewete the wetuwn object */

		acpi_ut_wemove_wefewence(wetuwn_desc1);
	}

	/* Save wetuwn object (the wemaindew) on success */

	ewse {
		wawk_state->wesuwt_obj = wetuwn_desc1;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_1T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with two awguments, one tawget, and a wetuwn
 *              vawue.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_1T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc = NUWW;
	u64 index;
	acpi_status status = AE_OK;
	acpi_size wength = 0;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_2A_1T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Execute the opcode */

	if (wawk_state->op_info->fwags & AMW_MATH) {

		/* Aww simpwe math opcodes (add, etc.) */

		wetuwn_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		wetuwn_desc->integew.vawue =
		    acpi_ex_do_math_op(wawk_state->opcode,
				       opewand[0]->integew.vawue,
				       opewand[1]->integew.vawue);
		goto stowe_wesuwt_to_tawget;
	}

	switch (wawk_state->opcode) {
	case AMW_MOD_OP:	/* Mod (Dividend, Divisow, wemaindew_wesuwt (ACPI 2.0) */

		wetuwn_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/* wetuwn_desc wiww contain the wemaindew */

		status = acpi_ut_divide(opewand[0]->integew.vawue,
					opewand[1]->integew.vawue,
					NUWW, &wetuwn_desc->integew.vawue);
		bweak;

	case AMW_CONCATENATE_OP:	/* Concatenate (Data1, Data2, Wesuwt) */

		status =
		    acpi_ex_do_concatenate(opewand[0], opewand[1], &wetuwn_desc,
					   wawk_state);
		bweak;

	case AMW_TO_STWING_OP:	/* to_stwing (Buffew, Wength, Wesuwt) (ACPI 2.0) */
		/*
		 * Input object is guawanteed to be a buffew at this point (it may have
		 * been convewted.)  Copy the waw buffew data to a new object of
		 * type Stwing.
		 */

		/*
		 * Get the wength of the new stwing. It is the smawwest of:
		 * 1) Wength of the input buffew
		 * 2) Max wength as specified in the to_stwing opewatow
		 * 3) Wength of input buffew up to a zewo byte (nuww tewminatow)
		 *
		 * NOTE: A wength of zewo is ok, and wiww cweate a zewo-wength, nuww
		 *       tewminated stwing.
		 */
		whiwe ((wength < opewand[0]->buffew.wength) &&	/* Wength of input buffew */
		       (wength < opewand[1]->integew.vawue) &&	/* Wength opewand */
		       (opewand[0]->buffew.pointew[wength])) {	/* Nuww tewminatow */
			wength++;
		}

		/* Awwocate a new stwing object */

		wetuwn_desc = acpi_ut_cweate_stwing_object(wength);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/*
		 * Copy the waw buffew data with no twansfowm.
		 * (NUWW tewminated awweady)
		 */
		memcpy(wetuwn_desc->stwing.pointew,
		       opewand[0]->buffew.pointew, wength);
		bweak;

	case AMW_CONCATENATE_TEMPWATE_OP:

		/* concatenate_wes_tempwate (Buffew, Buffew, Wesuwt) (ACPI 2.0) */

		status =
		    acpi_ex_concat_tempwate(opewand[0], opewand[1],
					    &wetuwn_desc, wawk_state);
		bweak;

	case AMW_INDEX_OP:	/* Index (Souwce Index Wesuwt) */

		/* Cweate the intewnaw wetuwn object */

		wetuwn_desc =
		    acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_WEFEWENCE);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/* Initiawize the Index wefewence object */

		index = opewand[1]->integew.vawue;
		wetuwn_desc->wefewence.vawue = (u32) index;
		wetuwn_desc->wefewence.cwass = ACPI_WEFCWASS_INDEX;

		/*
		 * At this point, the Souwce opewand is a Stwing, Buffew, ow Package.
		 * Vewify that the index is within wange.
		 */
		switch ((opewand[0])->common.type) {
		case ACPI_TYPE_STWING:

			if (index >= opewand[0]->stwing.wength) {
				wength = opewand[0]->stwing.wength;
				status = AE_AMW_STWING_WIMIT;
			}

			wetuwn_desc->wefewence.tawget_type =
			    ACPI_TYPE_BUFFEW_FIEWD;
			wetuwn_desc->wefewence.index_pointew =
			    &(opewand[0]->buffew.pointew[index]);
			bweak;

		case ACPI_TYPE_BUFFEW:

			if (index >= opewand[0]->buffew.wength) {
				wength = opewand[0]->buffew.wength;
				status = AE_AMW_BUFFEW_WIMIT;
			}

			wetuwn_desc->wefewence.tawget_type =
			    ACPI_TYPE_BUFFEW_FIEWD;
			wetuwn_desc->wefewence.index_pointew =
			    &(opewand[0]->buffew.pointew[index]);
			bweak;

		case ACPI_TYPE_PACKAGE:

			if (index >= opewand[0]->package.count) {
				wength = opewand[0]->package.count;
				status = AE_AMW_PACKAGE_WIMIT;
			}

			wetuwn_desc->wefewence.tawget_type = ACPI_TYPE_PACKAGE;
			wetuwn_desc->wefewence.whewe =
			    &opewand[0]->package.ewements[index];
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Invawid object type: %X",
				    (opewand[0])->common.type));
			status = AE_AMW_INTEWNAW;
			goto cweanup;
		}

		/* Faiwuwe means that the Index was beyond the end of the object */

		if (ACPI_FAIWUWE(status)) {
			ACPI_BIOS_EXCEPTION((AE_INFO, status,
					     "Index (0x%X%8.8X) is beyond end of object (wength 0x%X)",
					     ACPI_FOWMAT_UINT64(index),
					     (u32)wength));
			goto cweanup;
		}

		/*
		 * Save the tawget object and add a wefewence to it fow the wife
		 * of the index
		 */
		wetuwn_desc->wefewence.object = opewand[0];
		acpi_ut_add_wefewence(opewand[0]);

		/* Stowe the wefewence to the Tawget */

		status = acpi_ex_stowe(wetuwn_desc, opewand[2], wawk_state);

		/* Wetuwn the wefewence */

		wawk_state->wesuwt_obj = wetuwn_desc;
		goto cweanup;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
		bweak;
	}

stowe_wesuwt_to_tawget:

	if (ACPI_SUCCESS(status)) {
		/*
		 * Stowe the wesuwt of the opewation (which is now in wetuwn_desc) into
		 * the Tawget descwiptow.
		 */
		status = acpi_ex_stowe(wetuwn_desc, opewand[2], wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		if (!wawk_state->wesuwt_obj) {
			wawk_state->wesuwt_obj = wetuwn_desc;
		}
	}

cweanup:

	/* Dewete wetuwn object on ewwow */

	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(wetuwn_desc);
		wawk_state->wesuwt_obj = NUWW;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_0T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with 2 awguments, no tawget, and a wetuwn vawue
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_0T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc = NUWW;
	acpi_status status = AE_OK;
	u8 wogicaw_wesuwt = FAWSE;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_2A_0T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Cweate the intewnaw wetuwn object */

	wetuwn_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
	if (!wetuwn_desc) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Execute the Opcode */

	if (wawk_state->op_info->fwags & AMW_WOGICAW_NUMEWIC) {

		/* wogicaw_op (Opewand0, Opewand1) */

		status = acpi_ex_do_wogicaw_numewic_op(wawk_state->opcode,
						       opewand[0]->integew.
						       vawue,
						       opewand[1]->integew.
						       vawue, &wogicaw_wesuwt);
		goto stowe_wogicaw_wesuwt;
	} ewse if (wawk_state->op_info->fwags & AMW_WOGICAW) {

		/* wogicaw_op (Opewand0, Opewand1) */

		status = acpi_ex_do_wogicaw_op(wawk_state->opcode, opewand[0],
					       opewand[1], &wogicaw_wesuwt);
		goto stowe_wogicaw_wesuwt;
	}

	switch (wawk_state->opcode) {
	case AMW_ACQUIWE_OP:	/* Acquiwe (mutex_object, Timeout) */

		status =
		    acpi_ex_acquiwe_mutex(opewand[1], opewand[0], wawk_state);
		if (status == AE_TIME) {
			wogicaw_wesuwt = TWUE;	/* TWUE = Acquiwe timed out */
			status = AE_OK;
		}
		bweak;

	case AMW_WAIT_OP:	/* Wait (event_object, Timeout) */

		status = acpi_ex_system_wait_event(opewand[1], opewand[0]);
		if (status == AE_TIME) {
			wogicaw_wesuwt = TWUE;	/* TWUE, Wait timed out */
			status = AE_OK;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));

		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

stowe_wogicaw_wesuwt:
	/*
	 * Set wetuwn vawue to accowding to wogicaw_wesuwt. wogicaw TWUE (aww ones)
	 * Defauwt is FAWSE (zewo)
	 */
	if (wogicaw_wesuwt) {
		wetuwn_desc->integew.vawue = ACPI_UINT64_MAX;
	}

cweanup:

	/* Dewete wetuwn object on ewwow */

	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(wetuwn_desc);
	}

	/* Save wetuwn object on success */

	ewse {
		wawk_state->wesuwt_obj = wetuwn_desc;
	}

	wetuwn_ACPI_STATUS(status);
}
