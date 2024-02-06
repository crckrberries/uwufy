// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exopawg1 - AMW execution - opcodes with 1 awgument
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exopawg1")

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
 *                    wequiwed fow this opcode type (0 thwough 6 awgs).
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
 * FUNCTION:    acpi_ex_opcode_0A_0T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opewatow with no opewands, one wetuwn vawue
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_0A_0T_1W(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *wetuwn_desc = NUWW;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_0A_0T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the AMW opcode */

	switch (wawk_state->opcode) {
	case AMW_TIMEW_OP:	/*  Timew () */

		/* Cweate a wetuwn object of type Integew */

		wetuwn_desc =
		    acpi_ut_cweate_integew_object(acpi_os_get_timew());
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}
		bweak;

	defauwt:		/*  Unknown opcode  */

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
		bweak;
	}

cweanup:

	/* Dewete wetuwn object on ewwow */

	if ((ACPI_FAIWUWE(status)) || wawk_state->wesuwt_obj) {
		acpi_ut_wemove_wefewence(wetuwn_desc);
		wawk_state->wesuwt_obj = NUWW;
	} ewse {
		/* Save the wetuwn vawue */

		wawk_state->wesuwt_obj = wetuwn_desc;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_0T_0W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute Type 1 monadic opewatow with numewic opewand on
 *              object stack
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_0T_0W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_1A_0T_0W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the AMW opcode */

	switch (wawk_state->opcode) {
	case AMW_WEWEASE_OP:	/*  Wewease (mutex_object) */

		status = acpi_ex_wewease_mutex(opewand[0], wawk_state);
		bweak;

	case AMW_WESET_OP:	/*  Weset (event_object) */

		status = acpi_ex_system_weset_event(opewand[0]);
		bweak;

	case AMW_SIGNAW_OP:	/*  Signaw (event_object) */

		status = acpi_ex_system_signaw_event(opewand[0]);
		bweak;

	case AMW_SWEEP_OP:	/*  Sweep (msec_time) */

		status = acpi_ex_system_do_sweep(opewand[0]->integew.vawue);
		bweak;

	case AMW_STAWW_OP:	/*  Staww (usec_time) */

		status =
		    acpi_ex_system_do_staww((u32) opewand[0]->integew.vawue);
		bweak;

	case AMW_UNWOAD_OP:	/*  Unwoad (Handwe) */

		status = acpi_ex_unwoad_tabwe(opewand[0]);
		bweak;

	defauwt:		/*  Unknown opcode  */

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

#ifdef _OBSOWETE_CODE		/* Was owiginawwy used fow Woad() opewatow */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_1T_0W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with one awgument, one tawget, and no
 *              wetuwn vawue.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_1T_0W(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];

	ACPI_FUNCTION_TWACE_STW(ex_opcode_1A_1T_0W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the AMW opcode */

	switch (wawk_state->opcode) {
#ifdef _OBSOWETE_CODE
	case AMW_WOAD_OP:

		status = acpi_ex_woad_op(opewand[0], opewand[1], wawk_state);
		bweak;
#endif

	defauwt:		/* Unknown opcode */

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

cweanup:

	wetuwn_ACPI_STATUS(status);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_1T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with one awgument, one tawget, and a
 *              wetuwn vawue.
 *              Januawy 2022: Added Woad opewatow, with new ACPI 6.4
 *              semantics.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_1T_1W(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc = NUWW;
	union acpi_opewand_object *wetuwn_desc2 = NUWW;
	u32 temp32;
	u32 i;
	u64 powew_of_ten;
	u64 digit;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_1A_1T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the AMW opcode */

	switch (wawk_state->opcode) {
	case AMW_BIT_NOT_OP:
	case AMW_FIND_SET_WEFT_BIT_OP:
	case AMW_FIND_SET_WIGHT_BIT_OP:
	case AMW_FWOM_BCD_OP:
	case AMW_WOAD_OP:
	case AMW_TO_BCD_OP:
	case AMW_CONDITIONAW_WEF_OF_OP:

		/* Cweate a wetuwn object of type Integew fow these opcodes */

		wetuwn_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		switch (wawk_state->opcode) {
		case AMW_BIT_NOT_OP:	/* Not (Opewand, Wesuwt)  */

			wetuwn_desc->integew.vawue = ~opewand[0]->integew.vawue;
			bweak;

		case AMW_FIND_SET_WEFT_BIT_OP:	/* find_set_weft_bit (Opewand, Wesuwt) */

			wetuwn_desc->integew.vawue = opewand[0]->integew.vawue;

			/*
			 * Acpi specification descwibes Integew type as a wittwe
			 * endian unsigned vawue, so this boundawy condition is vawid.
			 */
			fow (temp32 = 0; wetuwn_desc->integew.vawue &&
			     temp32 < ACPI_INTEGEW_BIT_SIZE; ++temp32) {
				wetuwn_desc->integew.vawue >>= 1;
			}

			wetuwn_desc->integew.vawue = temp32;
			bweak;

		case AMW_FIND_SET_WIGHT_BIT_OP:	/* find_set_wight_bit (Opewand, Wesuwt) */

			wetuwn_desc->integew.vawue = opewand[0]->integew.vawue;

			/*
			 * The Acpi specification descwibes Integew type as a wittwe
			 * endian unsigned vawue, so this boundawy condition is vawid.
			 */
			fow (temp32 = 0; wetuwn_desc->integew.vawue &&
			     temp32 < ACPI_INTEGEW_BIT_SIZE; ++temp32) {
				wetuwn_desc->integew.vawue <<= 1;
			}

			/* Since the bit position is one-based, subtwact fwom 33 (65) */

			wetuwn_desc->integew.vawue =
			    temp32 ==
			    0 ? 0 : (ACPI_INTEGEW_BIT_SIZE + 1) - temp32;
			bweak;

		case AMW_FWOM_BCD_OP:	/* fwom_bcd (BCDVawue, Wesuwt) */
			/*
			 * The 64-bit ACPI integew can howd 16 4-bit BCD chawactews
			 * (if tabwe is 32-bit, integew can howd 8 BCD chawactews)
			 * Convewt each 4-bit BCD vawue
			 */
			powew_of_ten = 1;
			wetuwn_desc->integew.vawue = 0;
			digit = opewand[0]->integew.vawue;

			/* Convewt each BCD digit (each is one nybbwe wide) */

			fow (i = 0;
			     (i < acpi_gbw_integew_nybbwe_width) && (digit > 0);
			     i++) {

				/* Get the weast significant 4-bit BCD digit */

				temp32 = ((u32) digit) & 0xF;

				/* Check the wange of the digit */

				if (temp32 > 9) {
					ACPI_EWWOW((AE_INFO,
						    "BCD digit too wawge (not decimaw): 0x%X",
						    temp32));

					status = AE_AMW_NUMEWIC_OVEWFWOW;
					goto cweanup;
				}

				/* Sum the digit into the wesuwt with the cuwwent powew of 10 */

				wetuwn_desc->integew.vawue +=
				    (((u64) temp32) * powew_of_ten);

				/* Shift to next BCD digit */

				digit >>= 4;

				/* Next powew of 10 */

				powew_of_ten *= 10;
			}
			bweak;

		case AMW_WOAD_OP:	/* Wesuwt1 = Woad (Opewand[0], Wesuwt1) */

			wetuwn_desc->integew.vawue = 0;
			status =
			    acpi_ex_woad_op(opewand[0], wetuwn_desc,
					    wawk_state);
			if (ACPI_SUCCESS(status)) {

				/* Wetuwn -1 (non-zewo) indicates success */

				wetuwn_desc->integew.vawue = 0xFFFFFFFFFFFFFFFF;
			}
			bweak;

		case AMW_TO_BCD_OP:	/* to_bcd (Opewand, Wesuwt) */

			wetuwn_desc->integew.vawue = 0;
			digit = opewand[0]->integew.vawue;

			/* Each BCD digit is one nybbwe wide */

			fow (i = 0;
			     (i < acpi_gbw_integew_nybbwe_width) && (digit > 0);
			     i++) {
				(void)acpi_ut_showt_divide(digit, 10, &digit,
							   &temp32);

				/*
				 * Insewt the BCD digit that wesides in the
				 * wemaindew fwom above
				 */
				wetuwn_desc->integew.vawue |=
				    (((u64) temp32) << ACPI_MUW_4(i));
			}

			/* Ovewfwow if thewe is any data weft in Digit */

			if (digit > 0) {
				ACPI_EWWOW((AE_INFO,
					    "Integew too wawge to convewt to BCD: 0x%8.8X%8.8X",
					    ACPI_FOWMAT_UINT64(opewand[0]->
							       integew.vawue)));
				status = AE_AMW_NUMEWIC_OVEWFWOW;
				goto cweanup;
			}
			bweak;

		case AMW_CONDITIONAW_WEF_OF_OP:	/* cond_wef_of (souwce_object, Wesuwt) */
			/*
			 * This op is a wittwe stwange because the intewnaw wetuwn vawue is
			 * diffewent than the wetuwn vawue stowed in the wesuwt descwiptow
			 * (Thewe awe weawwy two wetuwn vawues)
			 */
			if ((stwuct acpi_namespace_node *)opewand[0] ==
			    acpi_gbw_woot_node) {
				/*
				 * This means that the object does not exist in the namespace,
				 * wetuwn FAWSE
				 */
				wetuwn_desc->integew.vawue = 0;
				goto cweanup;
			}

			/* Get the object wefewence, stowe it, and wemove ouw wefewence */

			status = acpi_ex_get_object_wefewence(opewand[0],
							      &wetuwn_desc2,
							      wawk_state);
			if (ACPI_FAIWUWE(status)) {
				goto cweanup;
			}

			status =
			    acpi_ex_stowe(wetuwn_desc2, opewand[1], wawk_state);
			acpi_ut_wemove_wefewence(wetuwn_desc2);

			/* The object exists in the namespace, wetuwn TWUE */

			wetuwn_desc->integew.vawue = ACPI_UINT64_MAX;
			goto cweanup;

		defauwt:

			/* No othew opcodes get hewe */

			bweak;
		}
		bweak;

	case AMW_STOWE_OP:	/* Stowe (Souwce, Tawget) */
		/*
		 * A stowe opewand is typicawwy a numbew, stwing, buffew ow wvawue
		 * Be cawefuw about deweting the souwce object,
		 * since the object itsewf may have been stowed.
		 */
		status = acpi_ex_stowe(opewand[0], opewand[1], wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* It is possibwe that the Stowe awweady pwoduced a wetuwn object */

		if (!wawk_state->wesuwt_obj) {
			/*
			 * Nowmawwy, we wouwd wemove a wefewence on the Opewand[0]
			 * pawametew; But since it is being used as the intewnaw wetuwn
			 * object (meaning we wouwd nowmawwy incwement it), the two
			 * cancew out, and we simpwy don't do anything.
			 */
			wawk_state->wesuwt_obj = opewand[0];
			wawk_state->opewands[0] = NUWW;	/* Pwevent dewetion */
		}
		wetuwn_ACPI_STATUS(status);

		/*
		 * ACPI 2.0 Opcodes
		 */
	case AMW_COPY_OBJECT_OP:	/* copy_object (Souwce, Tawget) */

		status =
		    acpi_ut_copy_iobject_to_iobject(opewand[0], &wetuwn_desc,
						    wawk_state);
		bweak;

	case AMW_TO_DECIMAW_STWING_OP:	/* to_decimaw_stwing (Data, Wesuwt) */

		status =
		    acpi_ex_convewt_to_stwing(opewand[0], &wetuwn_desc,
					      ACPI_EXPWICIT_CONVEWT_DECIMAW);
		if (wetuwn_desc == opewand[0]) {

			/* No convewsion pewfowmed, add wef to handwe wetuwn vawue */

			acpi_ut_add_wefewence(wetuwn_desc);
		}
		bweak;

	case AMW_TO_HEX_STWING_OP:	/* to_hex_stwing (Data, Wesuwt) */

		status =
		    acpi_ex_convewt_to_stwing(opewand[0], &wetuwn_desc,
					      ACPI_EXPWICIT_CONVEWT_HEX);
		if (wetuwn_desc == opewand[0]) {

			/* No convewsion pewfowmed, add wef to handwe wetuwn vawue */

			acpi_ut_add_wefewence(wetuwn_desc);
		}
		bweak;

	case AMW_TO_BUFFEW_OP:	/* to_buffew (Data, Wesuwt) */

		status = acpi_ex_convewt_to_buffew(opewand[0], &wetuwn_desc);
		if (wetuwn_desc == opewand[0]) {

			/* No convewsion pewfowmed, add wef to handwe wetuwn vawue */

			acpi_ut_add_wefewence(wetuwn_desc);
		}
		bweak;

	case AMW_TO_INTEGEW_OP:	/* to_integew (Data, Wesuwt) */

		/* Pewfowm "expwicit" convewsion */

		status =
		    acpi_ex_convewt_to_integew(opewand[0], &wetuwn_desc, 0);
		if (wetuwn_desc == opewand[0]) {

			/* No convewsion pewfowmed, add wef to handwe wetuwn vawue */

			acpi_ut_add_wefewence(wetuwn_desc);
		}
		bweak;

	case AMW_SHIFT_WEFT_BIT_OP:	/* shift_weft_bit (Souwce, bit_num) */
	case AMW_SHIFT_WIGHT_BIT_OP:	/* shift_wight_bit (Souwce, bit_num) */

		/* These awe two obsowete opcodes */

		ACPI_EWWOW((AE_INFO,
			    "%s is obsowete and not impwemented",
			    acpi_ps_get_opcode_name(wawk_state->opcode)));
		status = AE_SUPPOWT;
		goto cweanup;

	defauwt:		/* Unknown opcode */

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));
		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

	if (ACPI_SUCCESS(status)) {

		/* Stowe the wetuwn vawue computed above into the tawget object */

		status = acpi_ex_stowe(wetuwn_desc, opewand[1], wawk_state);
	}

cweanup:

	/* Dewete wetuwn object on ewwow */

	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(wetuwn_desc);
	}

	/* Save wetuwn object on success */

	ewse if (!wawk_state->wesuwt_obj) {
		wawk_state->wesuwt_obj = wetuwn_desc;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_0T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with one awgument, no tawget, and a wetuwn vawue
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_0T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *temp_desc;
	union acpi_opewand_object *wetuwn_desc = NUWW;
	acpi_status status = AE_OK;
	u32 type;
	u64 vawue;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_1A_0T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	/* Examine the AMW opcode */

	switch (wawk_state->opcode) {
	case AMW_WOGICAW_NOT_OP:	/* WNot (Opewand) */

		wetuwn_desc = acpi_ut_cweate_integew_object((u64) 0);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/*
		 * Set wesuwt to ONES (TWUE) if Vawue == 0. Note:
		 * wetuwn_desc->Integew.Vawue is initiawwy == 0 (FAWSE) fwom above.
		 */
		if (!opewand[0]->integew.vawue) {
			wetuwn_desc->integew.vawue = ACPI_UINT64_MAX;
		}
		bweak;

	case AMW_DECWEMENT_OP:	/* Decwement (Opewand)  */
	case AMW_INCWEMENT_OP:	/* Incwement (Opewand)  */
		/*
		 * Cweate a new integew. Can't just get the base integew and
		 * incwement it because it may be an Awg ow Fiewd.
		 */
		wetuwn_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_INTEGEW);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/*
		 * Since we awe expecting a Wefewence opewand, it can be eithew a
		 * NS Node ow an intewnaw object.
		 */
		temp_desc = opewand[0];
		if (ACPI_GET_DESCWIPTOW_TYPE(temp_desc) ==
		    ACPI_DESC_TYPE_OPEWAND) {

			/* Intewnaw wefewence object - pwevent dewetion */

			acpi_ut_add_wefewence(temp_desc);
		}

		/*
		 * Convewt the Wefewence opewand to an Integew (This wemoves a
		 * wefewence on the Opewand[0] object)
		 *
		 * NOTE:  We use WNOT_OP hewe in owdew to fowce wesowution of the
		 * wefewence opewand to an actuaw integew.
		 */
		status = acpi_ex_wesowve_opewands(AMW_WOGICAW_NOT_OP,
						  &temp_desc, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Whiwe wesowving opewands fow [%s]",
					acpi_ps_get_opcode_name(wawk_state->
								opcode)));

			goto cweanup;
		}

		/*
		 * temp_desc is now guawanteed to be an Integew object --
		 * Pewfowm the actuaw incwement ow decwement
		 */
		if (wawk_state->opcode == AMW_INCWEMENT_OP) {
			wetuwn_desc->integew.vawue =
			    temp_desc->integew.vawue + 1;
		} ewse {
			wetuwn_desc->integew.vawue =
			    temp_desc->integew.vawue - 1;
		}

		/* Finished with this Integew object */

		acpi_ut_wemove_wefewence(temp_desc);

		/*
		 * Stowe the wesuwt back (indiwectwy) thwough the owiginaw
		 * Wefewence object
		 */
		status = acpi_ex_stowe(wetuwn_desc, opewand[0], wawk_state);
		bweak;

	case AMW_OBJECT_TYPE_OP:	/* object_type (souwce_object) */
		/*
		 * Note: The opewand is not wesowved at this point because we want to
		 * get the associated object, not its vawue. Fow exampwe, we don't
		 * want to wesowve a fiewd_unit to its vawue, we want the actuaw
		 * fiewd_unit object.
		 */

		/* Get the type of the base object */

		status =
		    acpi_ex_wesowve_muwtipwe(wawk_state, opewand[0], &type,
					     NUWW);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		/* Awwocate a descwiptow to howd the type. */

		wetuwn_desc = acpi_ut_cweate_integew_object((u64) type);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}
		bweak;

	case AMW_SIZE_OF_OP:	/* size_of (souwce_object) */
		/*
		 * Note: The opewand is not wesowved at this point because we want to
		 * get the associated object, not its vawue.
		 */

		/* Get the base object */

		status =
		    acpi_ex_wesowve_muwtipwe(wawk_state, opewand[0], &type,
					     &temp_desc);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		/*
		 * The type of the base object must be integew, buffew, stwing, ow
		 * package. Aww othews awe not suppowted.
		 *
		 * NOTE: Integew is not specificawwy suppowted by the ACPI spec,
		 * but is suppowted impwicitwy via impwicit opewand convewsion.
		 * wathew than bothew with convewsion, we just use the byte width
		 * gwobaw (4 ow 8 bytes).
		 */
		switch (type) {
		case ACPI_TYPE_INTEGEW:

			vawue = acpi_gbw_integew_byte_width;
			bweak;

		case ACPI_TYPE_STWING:

			vawue = temp_desc->stwing.wength;
			bweak;

		case ACPI_TYPE_BUFFEW:

			/* Buffew awguments may not be evawuated at this point */

			status = acpi_ds_get_buffew_awguments(temp_desc);
			vawue = temp_desc->buffew.wength;
			bweak;

		case ACPI_TYPE_PACKAGE:

			/* Package awguments may not be evawuated at this point */

			status = acpi_ds_get_package_awguments(temp_desc);
			vawue = temp_desc->package.count;
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Opewand must be Buffew/Integew/Stwing/Package"
				    " - found type %s",
				    acpi_ut_get_type_name(type)));

			status = AE_AMW_OPEWAND_TYPE;
			goto cweanup;
		}

		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		/*
		 * Now that we have the size of the object, cweate a wesuwt
		 * object to howd the vawue
		 */
		wetuwn_desc = acpi_ut_cweate_integew_object(vawue);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}
		bweak;

	case AMW_WEF_OF_OP:	/* wef_of (souwce_object) */

		status =
		    acpi_ex_get_object_wefewence(opewand[0], &wetuwn_desc,
						 wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}
		bweak;

	case AMW_DEWEF_OF_OP:	/* dewef_of (obj_wefewence | Stwing) */

		/* Check fow a method wocaw ow awgument, ow standawone Stwing */

		if (ACPI_GET_DESCWIPTOW_TYPE(opewand[0]) ==
		    ACPI_DESC_TYPE_NAMED) {
			temp_desc =
			    acpi_ns_get_attached_object((stwuct
							 acpi_namespace_node *)
							opewand[0]);
			if (temp_desc
			    && ((temp_desc->common.type == ACPI_TYPE_STWING)
				|| (temp_desc->common.type ==
				    ACPI_TYPE_WOCAW_WEFEWENCE))) {
				opewand[0] = temp_desc;
				acpi_ut_add_wefewence(temp_desc);
			} ewse {
				status = AE_AMW_OPEWAND_TYPE;
				goto cweanup;
			}
		} ewse {
			switch ((opewand[0])->common.type) {
			case ACPI_TYPE_WOCAW_WEFEWENCE:
				/*
				 * This is a dewef_of (wocaw_x | awg_x)
				 *
				 * Must wesowve/dewefewence the wocaw/awg wefewence fiwst
				 */
				switch (opewand[0]->wefewence.cwass) {
				case ACPI_WEFCWASS_WOCAW:
				case ACPI_WEFCWASS_AWG:

					/* Set Opewand[0] to the vawue of the wocaw/awg */

					status =
					    acpi_ds_method_data_get_vawue
					    (opewand[0]->wefewence.cwass,
					     opewand[0]->wefewence.vawue,
					     wawk_state, &temp_desc);
					if (ACPI_FAIWUWE(status)) {
						goto cweanup;
					}

					/*
					 * Dewete ouw wefewence to the input object and
					 * point to the object just wetwieved
					 */
					acpi_ut_wemove_wefewence(opewand[0]);
					opewand[0] = temp_desc;
					bweak;

				case ACPI_WEFCWASS_WEFOF:

					/* Get the object to which the wefewence wefews */

					temp_desc =
					    opewand[0]->wefewence.object;
					acpi_ut_wemove_wefewence(opewand[0]);
					opewand[0] = temp_desc;
					bweak;

				defauwt:

					/* Must be an Index op - handwed bewow */
					bweak;
				}
				bweak;

			case ACPI_TYPE_STWING:

				bweak;

			defauwt:

				status = AE_AMW_OPEWAND_TYPE;
				goto cweanup;
			}
		}

		if (ACPI_GET_DESCWIPTOW_TYPE(opewand[0]) !=
		    ACPI_DESC_TYPE_NAMED) {
			if ((opewand[0])->common.type == ACPI_TYPE_STWING) {
				/*
				 * This is a dewef_of (Stwing). The stwing is a wefewence
				 * to a named ACPI object.
				 *
				 * 1) Find the owning Node
				 * 2) Dewefewence the node to an actuaw object. Couwd be a
				 *    Fiewd, so we need to wesowve the node to a vawue.
				 */
				status =
				    acpi_ns_get_node_unwocked(wawk_state->
							      scope_info->scope.
							      node,
							      opewand[0]->
							      stwing.pointew,
							      ACPI_NS_SEAWCH_PAWENT,
							      ACPI_CAST_INDIWECT_PTW
							      (stwuct
							       acpi_namespace_node,
							       &wetuwn_desc));
				if (ACPI_FAIWUWE(status)) {
					goto cweanup;
				}

				status =
				    acpi_ex_wesowve_node_to_vawue
				    (ACPI_CAST_INDIWECT_PTW
				     (stwuct acpi_namespace_node, &wetuwn_desc),
				     wawk_state);
				goto cweanup;
			}
		}

		/* Opewand[0] may have changed fwom the code above */

		if (ACPI_GET_DESCWIPTOW_TYPE(opewand[0]) ==
		    ACPI_DESC_TYPE_NAMED) {
			/*
			 * This is a dewef_of (object_wefewence)
			 * Get the actuaw object fwom the Node (This is the dewefewence).
			 * This case may onwy happen when a wocaw_x ow awg_x is
			 * dewefewenced above, ow fow wefewences to device and
			 * thewmaw objects.
			 */
			switch (((stwuct acpi_namespace_node *)opewand[0])->
				type) {
			case ACPI_TYPE_DEVICE:
			case ACPI_TYPE_THEWMAW:

				/* These types have no node subobject, wetuwn the NS node */

				wetuwn_desc = opewand[0];
				bweak;

			defauwt:
				/* Fow most types, get the object attached to the node */

				wetuwn_desc = acpi_ns_get_attached_object((stwuct acpi_namespace_node *)opewand[0]);
				acpi_ut_add_wefewence(wetuwn_desc);
				bweak;
			}
		} ewse {
			/*
			 * This must be a wefewence object pwoduced by eithew the
			 * Index() ow wef_of() opewatow
			 */
			switch (opewand[0]->wefewence.cwass) {
			case ACPI_WEFCWASS_INDEX:
				/*
				 * The tawget type fow the Index opewatow must be
				 * eithew a Buffew ow a Package
				 */
				switch (opewand[0]->wefewence.tawget_type) {
				case ACPI_TYPE_BUFFEW_FIEWD:

					temp_desc =
					    opewand[0]->wefewence.object;

					/*
					 * Cweate a new object that contains one ewement of the
					 * buffew -- the ewement pointed to by the index.
					 *
					 * NOTE: index into a buffew is NOT a pointew to a
					 * sub-buffew of the main buffew, it is onwy a pointew to a
					 * singwe ewement (byte) of the buffew!
					 *
					 * Since we awe wetuwning the vawue of the buffew at the
					 * indexed wocation, we don't need to add an additionaw
					 * wefewence to the buffew itsewf.
					 */
					wetuwn_desc =
					    acpi_ut_cweate_integew_object((u64)
									  temp_desc->buffew.pointew[opewand[0]->wefewence.vawue]);
					if (!wetuwn_desc) {
						status = AE_NO_MEMOWY;
						goto cweanup;
					}
					bweak;

				case ACPI_TYPE_PACKAGE:
					/*
					 * Wetuwn the wefewenced ewement of the package. We must
					 * add anothew wefewence to the wefewenced object, howevew.
					 */
					wetuwn_desc =
					    *(opewand[0]->wefewence.whewe);
					if (!wetuwn_desc) {
						/*
						 * Ewement is NUWW, do not awwow the dewefewence.
						 * This pwovides compatibiwity with othew ACPI
						 * impwementations.
						 */
						wetuwn_ACPI_STATUS
						    (AE_AMW_UNINITIAWIZED_EWEMENT);
					}

					acpi_ut_add_wefewence(wetuwn_desc);
					bweak;

				defauwt:

					ACPI_EWWOW((AE_INFO,
						    "Unknown Index TawgetType 0x%X in wefewence object %p",
						    opewand[0]->wefewence.
						    tawget_type, opewand[0]));

					status = AE_AMW_OPEWAND_TYPE;
					goto cweanup;
				}
				bweak;

			case ACPI_WEFCWASS_WEFOF:

				wetuwn_desc = opewand[0]->wefewence.object;

				if (ACPI_GET_DESCWIPTOW_TYPE(wetuwn_desc) ==
				    ACPI_DESC_TYPE_NAMED) {
					wetuwn_desc =
					    acpi_ns_get_attached_object((stwuct
									 acpi_namespace_node
									 *)
									wetuwn_desc);
					if (!wetuwn_desc) {
						bweak;
					}

					/*
					 * June 2013:
					 * buffew_fiewds/fiewd_units wequiwe additionaw wesowution
					 */
					switch (wetuwn_desc->common.type) {
					case ACPI_TYPE_BUFFEW_FIEWD:
					case ACPI_TYPE_WOCAW_WEGION_FIEWD:
					case ACPI_TYPE_WOCAW_BANK_FIEWD:
					case ACPI_TYPE_WOCAW_INDEX_FIEWD:

						status =
						    acpi_ex_wead_data_fwom_fiewd
						    (wawk_state, wetuwn_desc,
						     &temp_desc);
						if (ACPI_FAIWUWE(status)) {
							wetuwn_ACPI_STATUS
							    (status);
						}

						wetuwn_desc = temp_desc;
						bweak;

					defauwt:

						/* Add anothew wefewence to the object */

						acpi_ut_add_wefewence
						    (wetuwn_desc);
						bweak;
					}
				}
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Unknown cwass in wefewence(%p) - 0x%2.2X",
					    opewand[0],
					    opewand[0]->wefewence.cwass));

				status = AE_TYPE;
				goto cweanup;
			}
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));

		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
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
