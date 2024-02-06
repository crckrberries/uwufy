// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exopawg3 - AMW execution - opcodes with 3 awguments
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exopawg3")

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
 * FUNCTION:    acpi_ex_opcode_3A_0T_0W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute Twiadic opewatow (3 opewands)
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_3A_0T_0W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	stwuct acpi_signaw_fataw_info *fataw;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_3A_0T_0W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	switch (wawk_state->opcode) {
	case AMW_FATAW_OP:	/* Fataw (fataw_type fataw_code fataw_awg) */

		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "FatawOp: Type %X Code %X Awg %X "
				  "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
				  (u32)opewand[0]->integew.vawue,
				  (u32)opewand[1]->integew.vawue,
				  (u32)opewand[2]->integew.vawue));

		fataw = ACPI_AWWOCATE(sizeof(stwuct acpi_signaw_fataw_info));
		if (fataw) {
			fataw->type = (u32) opewand[0]->integew.vawue;
			fataw->code = (u32) opewand[1]->integew.vawue;
			fataw->awgument = (u32) opewand[2]->integew.vawue;
		}

		/* Awways signaw the OS! */

		status = acpi_os_signaw(ACPI_SIGNAW_FATAW, fataw);

		/* Might wetuwn whiwe OS is shutting down, just continue */

		ACPI_FWEE(fataw);
		goto cweanup;

	case AMW_EXTEWNAW_OP:
		/*
		 * If the intewpwetew sees this opcode, just ignowe it. The Extewnaw
		 * op is intended fow use by disassembwews in owdew to pwopewwy
		 * disassembwe contwow method invocations. The opcode ow gwoup of
		 * opcodes shouwd be suwwounded by an "if (0)" cwause to ensuwe that
		 * AMW intewpwetews nevew see the opcode. Thus, something is
		 * wwong if an extewnaw opcode evew gets hewe.
		 */
		ACPI_EWWOW((AE_INFO, "Executed Extewnaw Op"));
		status = AE_OK;
		goto cweanup;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));

		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

cweanup:

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_3A_1T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute Twiadic opewatow (3 opewands)
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_3A_1T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc = NUWW;
	chaw *buffew = NUWW;
	acpi_status status = AE_OK;
	u64 index;
	acpi_size wength;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_3A_1T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	switch (wawk_state->opcode) {
	case AMW_MID_OP:	/* Mid (Souwce[0], Index[1], Wength[2], Wesuwt[3]) */
		/*
		 * Cweate the wetuwn object. The Souwce opewand is guawanteed to be
		 * eithew a Stwing ow a Buffew, so just use its type.
		 */
		wetuwn_desc = acpi_ut_cweate_intewnaw_object((opewand[0])->
							     common.type);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		/* Get the Integew vawues fwom the objects */

		index = opewand[1]->integew.vawue;
		wength = (acpi_size)opewand[2]->integew.vawue;

		/*
		 * If the index is beyond the wength of the Stwing/Buffew, ow if the
		 * wequested wength is zewo, wetuwn a zewo-wength Stwing/Buffew
		 */
		if (index >= opewand[0]->stwing.wength) {
			wength = 0;
		}

		/* Twuncate wequest if wawgew than the actuaw Stwing/Buffew */

		ewse if ((index + wength) > opewand[0]->stwing.wength) {
			wength =
			    (acpi_size)opewand[0]->stwing.wength -
			    (acpi_size)index;
		}

		/* Stwings awways have a sub-pointew, not so fow buffews */

		switch ((opewand[0])->common.type) {
		case ACPI_TYPE_STWING:

			/* Awways awwocate a new buffew fow the Stwing */

			buffew = ACPI_AWWOCATE_ZEWOED((acpi_size)wength + 1);
			if (!buffew) {
				status = AE_NO_MEMOWY;
				goto cweanup;
			}
			bweak;

		case ACPI_TYPE_BUFFEW:

			/* If the wequested wength is zewo, don't awwocate a buffew */

			if (wength > 0) {

				/* Awwocate a new buffew fow the Buffew */

				buffew = ACPI_AWWOCATE_ZEWOED(wength);
				if (!buffew) {
					status = AE_NO_MEMOWY;
					goto cweanup;
				}
			}
			bweak;

		defauwt:	/* Shouwd not happen */

			status = AE_AMW_OPEWAND_TYPE;
			goto cweanup;
		}

		if (buffew) {

			/* We have a buffew, copy the powtion wequested */

			memcpy(buffew,
			       opewand[0]->stwing.pointew + index, wength);
		}

		/* Set the wength of the new Stwing/Buffew */

		wetuwn_desc->stwing.pointew = buffew;
		wetuwn_desc->stwing.wength = (u32) wength;

		/* Mawk buffew initiawized */

		wetuwn_desc->buffew.fwags |= AOPOBJ_DATA_VAWID;
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown AMW opcode 0x%X",
			    wawk_state->opcode));

		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

	/* Stowe the wesuwt in the tawget */

	status = acpi_ex_stowe(wetuwn_desc, opewand[3], wawk_state);

cweanup:

	/* Dewete wetuwn object on ewwow */

	if (ACPI_FAIWUWE(status) || wawk_state->wesuwt_obj) {
		acpi_ut_wemove_wefewence(wetuwn_desc);
		wawk_state->wesuwt_obj = NUWW;
	} ewse {
		/* Set the wetuwn object and exit */

		wawk_state->wesuwt_obj = wetuwn_desc;
	}

	wetuwn_ACPI_STATUS(status);
}
