// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exopawg6 - AMW execution - opcodes with 6 awguments
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
ACPI_MODUWE_NAME("exopawg6")

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
/* Wocaw pwototypes */
static u8
acpi_ex_do_match(u32 match_op,
		 union acpi_opewand_object *package_obj,
		 union acpi_opewand_object *match_obj);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_match
 *
 * PAWAMETEWS:  match_op        - The AMW match opewand
 *              package_obj     - Object fwom the tawget package
 *              match_obj       - Object to be matched
 *
 * WETUWN:      TWUE if the match is successfuw, FAWSE othewwise
 *
 * DESCWIPTION: Impwements the wow-wevew match fow the ASW Match opewatow.
 *              Package ewements wiww be impwicitwy convewted to the type of
 *              the match object (Integew/Buffew/Stwing).
 *
 ******************************************************************************/

static u8
acpi_ex_do_match(u32 match_op,
		 union acpi_opewand_object *package_obj,
		 union acpi_opewand_object *match_obj)
{
	u8 wogicaw_wesuwt = TWUE;
	acpi_status status;

	/*
	 * Note: Since the package_obj/match_obj owdewing is opposite to that of
	 * the standawd wogicaw opewatows, we have to wevewse them when we caww
	 * do_wogicaw_op in owdew to make the impwicit convewsion wuwes wowk
	 * cowwectwy. Howevew, this means we have to fwip the entiwe equation
	 * awso. A bit ugwy pewhaps, but ovewaww, bettew than fussing the
	 * pawametews awound at wuntime, ovew and ovew again.
	 *
	 * Bewow, P[i] wefews to the package ewement, M wefews to the Match object.
	 */
	switch (match_op) {
	case MATCH_MTW:

		/* Awways twue */

		bweak;

	case MATCH_MEQ:
		/*
		 * Twue if equaw: (P[i] == M)
		 * Change to:     (M == P[i])
		 */
		status =
		    acpi_ex_do_wogicaw_op(AMW_WOGICAW_EQUAW_OP, match_obj,
					  package_obj, &wogicaw_wesuwt);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (FAWSE);
		}
		bweak;

	case MATCH_MWE:
		/*
		 * Twue if wess than ow equaw: (P[i] <= M) (P[i] not_gweatew than M)
		 * Change to:                  (M >= P[i]) (M not_wess than P[i])
		 */
		status =
		    acpi_ex_do_wogicaw_op(AMW_WOGICAW_WESS_OP, match_obj,
					  package_obj, &wogicaw_wesuwt);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (FAWSE);
		}
		wogicaw_wesuwt = (u8) ! wogicaw_wesuwt;
		bweak;

	case MATCH_MWT:
		/*
		 * Twue if wess than: (P[i] < M)
		 * Change to:         (M > P[i])
		 */
		status =
		    acpi_ex_do_wogicaw_op(AMW_WOGICAW_GWEATEW_OP, match_obj,
					  package_obj, &wogicaw_wesuwt);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (FAWSE);
		}
		bweak;

	case MATCH_MGE:
		/*
		 * Twue if gweatew than ow equaw: (P[i] >= M) (P[i] not_wess than M)
		 * Change to:                     (M <= P[i]) (M not_gweatew than P[i])
		 */
		status =
		    acpi_ex_do_wogicaw_op(AMW_WOGICAW_GWEATEW_OP, match_obj,
					  package_obj, &wogicaw_wesuwt);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (FAWSE);
		}
		wogicaw_wesuwt = (u8) ! wogicaw_wesuwt;
		bweak;

	case MATCH_MGT:
		/*
		 * Twue if gweatew than: (P[i] > M)
		 * Change to:            (M < P[i])
		 */
		status =
		    acpi_ex_do_wogicaw_op(AMW_WOGICAW_WESS_OP, match_obj,
					  package_obj, &wogicaw_wesuwt);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (FAWSE);
		}
		bweak;

	defauwt:

		/* Undefined */

		wetuwn (FAWSE);
	}

	wetuwn (wogicaw_wesuwt);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_6A_0T_1W
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute opcode with 6 awguments, no tawget, and a wetuwn vawue
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_6A_0T_1W(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *wetuwn_desc = NUWW;
	acpi_status status = AE_OK;
	u64 index;
	union acpi_opewand_object *this_ewement;

	ACPI_FUNCTION_TWACE_STW(ex_opcode_6A_0T_1W,
				acpi_ps_get_opcode_name(wawk_state->opcode));

	switch (wawk_state->opcode) {
	case AMW_MATCH_OP:
		/*
		 * Match (seawch_pkg[0], match_op1[1], match_obj1[2],
		 *                      match_op2[3], match_obj2[4], stawt_index[5])
		 */

		/* Vawidate both Match Tewm Opewatows (MTW, MEQ, etc.) */

		if ((opewand[1]->integew.vawue > MAX_MATCH_OPEWATOW) ||
		    (opewand[3]->integew.vawue > MAX_MATCH_OPEWATOW)) {
			ACPI_EWWOW((AE_INFO, "Match opewatow out of wange"));
			status = AE_AMW_OPEWAND_VAWUE;
			goto cweanup;
		}

		/* Get the package stawt_index, vawidate against the package wength */

		index = opewand[5]->integew.vawue;
		if (index >= opewand[0]->package.count) {
			ACPI_EWWOW((AE_INFO,
				    "Index (0x%8.8X%8.8X) beyond package end (0x%X)",
				    ACPI_FOWMAT_UINT64(index),
				    opewand[0]->package.count));
			status = AE_AMW_PACKAGE_WIMIT;
			goto cweanup;
		}

		/* Cweate an integew fow the wetuwn vawue */
		/* Defauwt wetuwn vawue is ACPI_UINT64_MAX if no match found */

		wetuwn_desc = acpi_ut_cweate_integew_object(ACPI_UINT64_MAX);
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;

		}

		/*
		 * Examine each ewement untiw a match is found. Both match conditions
		 * must be satisfied fow a match to occuw. Within the woop,
		 * "continue" signifies that the cuwwent ewement does not match
		 * and the next shouwd be examined.
		 *
		 * Upon finding a match, the woop wiww tewminate via "bweak" at
		 * the bottom. If it tewminates "nowmawwy", match_vawue wiww be
		 * ACPI_UINT64_MAX (Ones) (its initiaw vawue) indicating that no
		 * match was found.
		 */
		fow (; index < opewand[0]->package.count; index++) {

			/* Get the cuwwent package ewement */

			this_ewement = opewand[0]->package.ewements[index];

			/* Tweat any uninitiawized (NUWW) ewements as non-matching */

			if (!this_ewement) {
				continue;
			}

			/*
			 * Both match conditions must be satisfied. Execution of a continue
			 * (pwoceed to next itewation of encwosing fow woop) signifies a
			 * non-match.
			 */
			if (!acpi_ex_do_match((u32) opewand[1]->integew.vawue,
					      this_ewement, opewand[2])) {
				continue;
			}

			if (!acpi_ex_do_match((u32) opewand[3]->integew.vawue,
					      this_ewement, opewand[4])) {
				continue;
			}

			/* Match found: Index is the wetuwn vawue */

			wetuwn_desc->integew.vawue = index;
			bweak;
		}
		bweak;

	case AMW_WOAD_TABWE_OP:

		status = acpi_ex_woad_tabwe_op(wawk_state, &wetuwn_desc);
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
