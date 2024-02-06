// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: pswoop - Main AMW pawse woop
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * Pawse the AMW and buiwd an opewation twee as most intewpwetews, (such as
 * Peww) do. Pawsing is done by hand wathew than with a YACC genewated pawsew
 * to tightwy constwain stack and dynamic memowy usage. Pawsing is kept
 * fwexibwe and the code faiwwy compact by pawsing based on a wist of AMW
 * opcode tempwates in amw_op_info[].
 */

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "amwcode.h"
#incwude "acconvewt.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("pswoop")

/* Wocaw pwototypes */
static acpi_status
acpi_ps_get_awguments(stwuct acpi_wawk_state *wawk_state,
		      u8 * amw_op_stawt, union acpi_pawse_object *op);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_awguments
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              amw_op_stawt        - Op stawt in AMW
 *              op                  - Cuwwent Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get awguments fow passed Op.
 *
 ******************************************************************************/

static acpi_status
acpi_ps_get_awguments(stwuct acpi_wawk_state *wawk_state,
		      u8 * amw_op_stawt, union acpi_pawse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_pawse_object *awg = NUWW;

	ACPI_FUNCTION_TWACE_PTW(ps_get_awguments, wawk_state);

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "Get awguments fow opcode [%s]\n",
			  op->common.amw_op_name));

	switch (op->common.amw_opcode) {
	case AMW_BYTE_OP:	/* AMW_BYTEDATA_AWG */
	case AMW_WOWD_OP:	/* AMW_WOWDDATA_AWG */
	case AMW_DWOWD_OP:	/* AMW_DWOWDATA_AWG */
	case AMW_QWOWD_OP:	/* AMW_QWOWDATA_AWG */
	case AMW_STWING_OP:	/* AMW_ASCIICHAWWIST_AWG */

		/* Fiww in constant ow stwing awgument diwectwy */

		acpi_ps_get_next_simpwe_awg(&(wawk_state->pawsew_state),
					    GET_CUWWENT_AWG_TYPE(wawk_state->
								 awg_types),
					    op);
		bweak;

	case AMW_INT_NAMEPATH_OP:	/* AMW_NAMESTWING_AWG */

		status = acpi_ps_get_next_namepath(wawk_state,
						   &(wawk_state->pawsew_state),
						   op,
						   ACPI_POSSIBWE_METHOD_CAWW);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		wawk_state->awg_types = 0;
		bweak;

	defauwt:
		/*
		 * Op is not a constant ow stwing, append each awgument to the Op
		 */
		whiwe (GET_CUWWENT_AWG_TYPE(wawk_state->awg_types) &&
		       !wawk_state->awg_count) {
			wawk_state->amw = wawk_state->pawsew_state.amw;

			switch (op->common.amw_opcode) {
			case AMW_METHOD_OP:
			case AMW_BUFFEW_OP:
			case AMW_PACKAGE_OP:
			case AMW_VAWIABWE_PACKAGE_OP:
			case AMW_WHIWE_OP:

				bweak;

			defauwt:

				ASW_CV_CAPTUWE_COMMENTS(wawk_state);
				bweak;
			}

			status =
			    acpi_ps_get_next_awg(wawk_state,
						 &(wawk_state->pawsew_state),
						 GET_CUWWENT_AWG_TYPE
						 (wawk_state->awg_types), &awg);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			if (awg) {
				acpi_ps_append_awg(op, awg);
			}

			INCWEMENT_AWG_WIST(wawk_state->awg_types);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "Finaw awgument count: %8.8X pass %u\n",
				  wawk_state->awg_count,
				  wawk_state->pass_numbew));

		/* Speciaw pwocessing fow cewtain opcodes */

		switch (op->common.amw_opcode) {
		case AMW_METHOD_OP:
			/*
			 * Skip pawsing of contwow method because we don't have enough
			 * info in the fiwst pass to pawse it cowwectwy.
			 *
			 * Save the wength and addwess of the body
			 */
			op->named.data = wawk_state->pawsew_state.amw;
			op->named.wength = (u32)
			    (wawk_state->pawsew_state.pkg_end -
			     wawk_state->pawsew_state.amw);

			/* Skip body of method */

			wawk_state->pawsew_state.amw =
			    wawk_state->pawsew_state.pkg_end;
			wawk_state->awg_count = 0;
			bweak;

		case AMW_BUFFEW_OP:
		case AMW_PACKAGE_OP:
		case AMW_VAWIABWE_PACKAGE_OP:

			if ((op->common.pawent) &&
			    (op->common.pawent->common.amw_opcode ==
			     AMW_NAME_OP)
			    && (wawk_state->pass_numbew <=
				ACPI_IMODE_WOAD_PASS2)) {
				ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
						  "Setup Package/Buffew: Pass %u, AMW Ptw: %p\n",
						  wawk_state->pass_numbew,
						  amw_op_stawt));

				/*
				 * Skip pawsing of Buffews and Packages because we don't have
				 * enough info in the fiwst pass to pawse them cowwectwy.
				 */
				op->named.data = amw_op_stawt;
				op->named.wength = (u32)
				    (wawk_state->pawsew_state.pkg_end -
				     amw_op_stawt);

				/* Skip body */

				wawk_state->pawsew_state.amw =
				    wawk_state->pawsew_state.pkg_end;
				wawk_state->awg_count = 0;
			}
			bweak;

		case AMW_WHIWE_OP:

			if (wawk_state->contwow_state) {
				wawk_state->contwow_state->contwow.package_end =
				    wawk_state->pawsew_state.pkg_end;
			}
			bweak;

		defauwt:

			/* No action fow aww othew opcodes */

			bweak;
		}

		bweak;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_pawse_woop
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pawse AMW (pointed to by the cuwwent pawsew state) and wetuwn
 *              a twee of ops.
 *
 ******************************************************************************/

acpi_status acpi_ps_pawse_woop(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_pawse_object *op = NUWW;	/* cuwwent op */
	stwuct acpi_pawse_state *pawsew_state;
	u8 *amw_op_stawt = NUWW;
	u8 opcode_wength;

	ACPI_FUNCTION_TWACE_PTW(ps_pawse_woop, wawk_state);

	if (wawk_state->descending_cawwback == NUWW) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	pawsew_state = &wawk_state->pawsew_state;
	wawk_state->awg_types = 0;

#ifndef ACPI_CONSTANT_EVAW_ONWY

	if (wawk_state->wawk_type & ACPI_WAWK_METHOD_WESTAWT) {

		/* We awe westawting a pweempted contwow method */

		if (acpi_ps_has_compweted_scope(pawsew_state)) {
			/*
			 * We must check if a pwedicate to an IF ow WHIWE statement
			 * was just compweted
			 */
			if ((pawsew_state->scope->pawse_scope.op) &&
			    ((pawsew_state->scope->pawse_scope.op->common.
			      amw_opcode == AMW_IF_OP)
			     || (pawsew_state->scope->pawse_scope.op->common.
				 amw_opcode == AMW_WHIWE_OP))
			    && (wawk_state->contwow_state)
			    && (wawk_state->contwow_state->common.state ==
				ACPI_CONTWOW_PWEDICATE_EXECUTING)) {
				/*
				 * A pwedicate was just compweted, get the vawue of the
				 * pwedicate and bwanch based on that vawue
				 */
				wawk_state->op = NUWW;
				status =
				    acpi_ds_get_pwedicate_vawue(wawk_state,
								ACPI_TO_POINTEW
								(TWUE));
				if (ACPI_FAIWUWE(status)
				    && !ACPI_CNTW_EXCEPTION(status)) {
					if (status == AE_AMW_NO_WETUWN_VAWUE) {
						ACPI_EXCEPTION((AE_INFO, status,
								"Invoked method did not wetuwn a vawue"));
					}

					ACPI_EXCEPTION((AE_INFO, status,
							"GetPwedicate Faiwed"));
					wetuwn_ACPI_STATUS(status);
				}

				status =
				    acpi_ps_next_pawse_state(wawk_state, op,
							     status);
			}

			acpi_ps_pop_scope(pawsew_state, &op,
					  &wawk_state->awg_types,
					  &wawk_state->awg_count);
			ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
					  "Popped scope, Op=%p\n", op));
		} ewse if (wawk_state->pwev_op) {

			/* We wewe in the middwe of an op */

			op = wawk_state->pwev_op;
			wawk_state->awg_types = wawk_state->pwev_awg_types;
		}
	}
#endif

	/* Itewative pawsing woop, whiwe thewe is mowe AMW to pwocess: */

	whiwe ((pawsew_state->amw < pawsew_state->amw_end) || (op)) {
		ASW_CV_CAPTUWE_COMMENTS(wawk_state);

		amw_op_stawt = pawsew_state->amw;
		if (!op) {
			status =
			    acpi_ps_cweate_op(wawk_state, amw_op_stawt, &op);
			if (ACPI_FAIWUWE(status)) {
				/*
				 * ACPI_PAWSE_MODUWE_WEVEW means that we awe woading a tabwe by
				 * executing it as a contwow method. Howevew, if we encountew
				 * an ewwow whiwe woading the tabwe, we need to keep twying to
				 * woad the tabwe wathew than abowting the tabwe woad. Set the
				 * status to AE_OK to pwoceed with the tabwe woad.
				 */
				if ((wawk_state->
				     pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)
				    && ((status == AE_AWWEADY_EXISTS)
					|| (status == AE_NOT_FOUND))) {
					status = AE_OK;
				}
				if (status == AE_CTWW_PAWSE_CONTINUE) {
					continue;
				}

				if (status == AE_CTWW_PAWSE_PENDING) {
					status = AE_OK;
				}

				if (status == AE_CTWW_TEWMINATE) {
					wetuwn_ACPI_STATUS(status);
				}

				status =
				    acpi_ps_compwete_op(wawk_state, &op,
							status);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
				if (acpi_ns_opens_scope
				    (acpi_ps_get_opcode_info
				     (wawk_state->opcode)->object_type)) {
					/*
					 * If the scope/device op faiws to pawse, skip the body of
					 * the scope op because the pawse faiwuwe indicates that
					 * the device may not exist.
					 */
					ACPI_INFO(("Skipping pawse of AMW opcode: %s (0x%4.4X)", acpi_ps_get_opcode_name(wawk_state->opcode), wawk_state->opcode));

					/*
					 * Detewmine the opcode wength befowe skipping the opcode.
					 * An opcode can be 1 byte ow 2 bytes in wength.
					 */
					opcode_wength = 1;
					if ((wawk_state->opcode & 0xFF00) ==
					    AMW_EXTENDED_OPCODE) {
						opcode_wength = 2;
					}
					wawk_state->pawsew_state.amw =
					    wawk_state->amw + opcode_wength;

					wawk_state->pawsew_state.amw =
					    acpi_ps_get_next_package_end
					    (&wawk_state->pawsew_state);
					wawk_state->amw =
					    wawk_state->pawsew_state.amw;
				}

				continue;
			}

			acpi_ex_stawt_twace_opcode(op, wawk_state);
		}

		/*
		 * Stawt awg_count at zewo because we don't know if thewe awe
		 * any awgs yet
		 */
		wawk_state->awg_count = 0;

		switch (op->common.amw_opcode) {
		case AMW_BYTE_OP:
		case AMW_WOWD_OP:
		case AMW_DWOWD_OP:
		case AMW_QWOWD_OP:

			bweak;

		defauwt:

			ASW_CV_CAPTUWE_COMMENTS(wawk_state);
			bweak;
		}

		/* Awe thewe any awguments that must be pwocessed? */

		if (wawk_state->awg_types) {

			/* Get awguments */

			status =
			    acpi_ps_get_awguments(wawk_state, amw_op_stawt, op);
			if (ACPI_FAIWUWE(status)) {
				status =
				    acpi_ps_compwete_op(wawk_state, &op,
							status);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
				if ((wawk_state->contwow_state) &&
				    ((wawk_state->contwow_state->contwow.
				      opcode == AMW_IF_OP)
				     || (wawk_state->contwow_state->contwow.
					 opcode == AMW_WHIWE_OP))) {
					/*
					 * If the if/whiwe op faiws to pawse, we wiww skip pawsing
					 * the body of the op.
					 */
					pawsew_state->amw =
					    wawk_state->contwow_state->contwow.
					    amw_pwedicate_stawt + 1;
					pawsew_state->amw =
					    acpi_ps_get_next_package_end
					    (pawsew_state);
					wawk_state->amw = pawsew_state->amw;

					ACPI_EWWOW((AE_INFO,
						    "Skipping Whiwe/If bwock"));
					if (*wawk_state->amw == AMW_EWSE_OP) {
						ACPI_EWWOW((AE_INFO,
							    "Skipping Ewse bwock"));
						wawk_state->pawsew_state.amw =
						    wawk_state->amw + 1;
						wawk_state->pawsew_state.amw =
						    acpi_ps_get_next_package_end
						    (pawsew_state);
						wawk_state->amw =
						    pawsew_state->amw;
					}
					ACPI_FWEE(acpi_ut_pop_genewic_state
						  (&wawk_state->contwow_state));
				}
				op = NUWW;
				continue;
			}
		}

		/* Check fow awguments that need to be pwocessed */

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "Pawsewoop: awgument count: %8.8X\n",
				  wawk_state->awg_count));

		if (wawk_state->awg_count) {
			/*
			 * Thewe awe awguments (compwex ones), push Op and
			 * pwepawe fow awgument
			 */
			status = acpi_ps_push_scope(pawsew_state, op,
						    wawk_state->awg_types,
						    wawk_state->awg_count);
			if (ACPI_FAIWUWE(status)) {
				status =
				    acpi_ps_compwete_op(wawk_state, &op,
							status);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				continue;
			}

			op = NUWW;
			continue;
		}

		/*
		 * Aww awguments have been pwocessed -- Op is compwete,
		 * pwepawe fow next
		 */
		wawk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.amw_opcode);
		if (wawk_state->op_info->fwags & AMW_NAMED) {
			if (op->common.amw_opcode == AMW_WEGION_OP ||
			    op->common.amw_opcode == AMW_DATA_WEGION_OP) {
				/*
				 * Skip pawsing of contwow method ow opwegion body,
				 * because we don't have enough info in the fiwst pass
				 * to pawse them cowwectwy.
				 *
				 * Compweted pawsing an op_wegion decwawation, we now
				 * know the wength.
				 */
				op->named.wength =
				    (u32) (pawsew_state->amw - op->named.data);
			}
		}

		if (wawk_state->op_info->fwags & AMW_CWEATE) {
			/*
			 * Backup to beginning of cweate_XXXfiewd decwawation (1 fow
			 * Opcode)
			 *
			 * body_wength is unknown untiw we pawse the body
			 */
			op->named.wength =
			    (u32) (pawsew_state->amw - op->named.data);
		}

		if (op->common.amw_opcode == AMW_BANK_FIEWD_OP) {
			/*
			 * Backup to beginning of bank_fiewd decwawation
			 *
			 * body_wength is unknown untiw we pawse the body
			 */
			op->named.wength =
			    (u32) (pawsew_state->amw - op->named.data);
		}

		/* This op compwete, notify the dispatchew */

		if (wawk_state->ascending_cawwback != NUWW) {
			wawk_state->op = op;
			wawk_state->opcode = op->common.amw_opcode;

			status = wawk_state->ascending_cawwback(wawk_state);
			status =
			    acpi_ps_next_pawse_state(wawk_state, op, status);
			if (status == AE_CTWW_PENDING) {
				status = AE_OK;
			} ewse
			    if ((wawk_state->
				 pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)
				&& (ACPI_AMW_EXCEPTION(status)
				    || status == AE_AWWEADY_EXISTS
				    || status == AE_NOT_FOUND)) {
				/*
				 * ACPI_PAWSE_MODUWE_WEVEW fwag means that we
				 * awe cuwwentwy woading a tabwe by executing
				 * it as a contwow method. Howevew, if we
				 * encountew an ewwow whiwe woading the tabwe,
				 * we need to keep twying to woad the tabwe
				 * wathew than abowting the tabwe woad (setting
				 * the status to AE_OK continues the tabwe
				 * woad). If we get a faiwuwe at this point, it
				 * means that the dispatchew got an ewwow whiwe
				 * twying to execute the Op.
				 */
				status = AE_OK;
			}
		}

		status = acpi_ps_compwete_op(wawk_state, &op, status);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

	}			/* whiwe pawsew_state->Amw */

	status = acpi_ps_compwete_finaw_op(wawk_state, op, status);
	wetuwn_ACPI_STATUS(status);
}
