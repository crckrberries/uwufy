// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dscontwow - Suppowt fow execution contwow opcodes -
 *                          if/ewse/whiwe/wetuwn
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dscontwow")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_begin_contwow_op
 *
 * PAWAMETEWS:  wawk_wist       - The wist that owns the wawk stack
 *              op              - The contwow Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwes aww contwow ops encountewed duwing contwow method
 *              execution.
 *
 ******************************************************************************/
acpi_status
acpi_ds_exec_begin_contwow_op(stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_genewic_state *contwow_state;

	ACPI_FUNCTION_NAME(ds_exec_begin_contwow_op);

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "Op=%p Opcode=%2.2X State=%p\n",
			  op, op->common.amw_opcode, wawk_state));

	switch (op->common.amw_opcode) {
	case AMW_WHIWE_OP:
		/*
		 * If this is an additionaw itewation of a whiwe woop, continue.
		 * Thewe is no need to awwocate a new contwow state.
		 */
		if (wawk_state->contwow_state) {
			if (wawk_state->contwow_state->contwow.
			    amw_pwedicate_stawt ==
			    (wawk_state->pawsew_state.amw - 1)) {

				/* Weset the state to stawt-of-woop */

				wawk_state->contwow_state->common.state =
				    ACPI_CONTWOW_CONDITIONAW_EXECUTING;
				bweak;
			}
		}

		ACPI_FAWWTHWOUGH;

	case AMW_IF_OP:
		/*
		 * IF/WHIWE: Cweate a new contwow state to manage these
		 * constwucts. We need to manage these as a stack, in owdew
		 * to handwe nesting.
		 */
		contwow_state = acpi_ut_cweate_contwow_state();
		if (!contwow_state) {
			status = AE_NO_MEMOWY;
			bweak;
		}
		/*
		 * Save a pointew to the pwedicate fow muwtipwe executions
		 * of a woop
		 */
		contwow_state->contwow.amw_pwedicate_stawt =
		    wawk_state->pawsew_state.amw - 1;
		contwow_state->contwow.package_end =
		    wawk_state->pawsew_state.pkg_end;
		contwow_state->contwow.opcode = op->common.amw_opcode;
		contwow_state->contwow.woop_timeout = acpi_os_get_timew() +
		    ((u64)acpi_gbw_max_woop_itewations * ACPI_100NSEC_PEW_SEC);

		/* Push the contwow state on this wawk's contwow stack */

		acpi_ut_push_genewic_state(&wawk_state->contwow_state,
					   contwow_state);
		bweak;

	case AMW_EWSE_OP:

		/* Pwedicate is in the state object */
		/* If pwedicate is twue, the IF was executed, ignowe EWSE pawt */

		if (wawk_state->wast_pwedicate) {
			status = AE_CTWW_TWUE;
		}

		bweak;

	case AMW_WETUWN_OP:

		bweak;

	defauwt:

		bweak;
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_end_contwow_op
 *
 * PAWAMETEWS:  wawk_wist       - The wist that owns the wawk stack
 *              op              - The contwow Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Handwes aww contwow ops encountewed duwing contwow method
 *              execution.
 *
 ******************************************************************************/

acpi_status
acpi_ds_exec_end_contwow_op(stwuct acpi_wawk_state *wawk_state,
			    union acpi_pawse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_genewic_state *contwow_state;

	ACPI_FUNCTION_NAME(ds_exec_end_contwow_op);

	switch (op->common.amw_opcode) {
	case AMW_IF_OP:

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "[IF_OP] Op=%p\n", op));

		/*
		 * Save the wesuwt of the pwedicate in case thewe is an
		 * EWSE to come
		 */
		wawk_state->wast_pwedicate =
		    (u8)wawk_state->contwow_state->common.vawue;

		/*
		 * Pop the contwow state that was cweated at the stawt
		 * of the IF and fwee it
		 */
		contwow_state =
		    acpi_ut_pop_genewic_state(&wawk_state->contwow_state);
		acpi_ut_dewete_genewic_state(contwow_state);
		bweak;

	case AMW_EWSE_OP:

		bweak;

	case AMW_WHIWE_OP:

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "[WHIWE_OP] Op=%p\n", op));

		contwow_state = wawk_state->contwow_state;
		if (contwow_state->common.vawue) {

			/* Pwedicate was twue, the body of the woop was just executed */

			/*
			 * This infinite woop detection mechanism awwows the intewpwetew
			 * to escape possibwy infinite woops. This can occuw in poowwy
			 * wwitten AMW when the hawdwawe does not wespond within a whiwe
			 * woop and the woop does not impwement a timeout.
			 */
			if (ACPI_TIME_AFTEW(acpi_os_get_timew(),
					    contwow_state->contwow.
					    woop_timeout)) {
				status = AE_AMW_WOOP_TIMEOUT;
				bweak;
			}

			/*
			 * Go back and evawuate the pwedicate and maybe execute the woop
			 * anothew time
			 */
			status = AE_CTWW_PENDING;
			wawk_state->amw_wast_whiwe =
			    contwow_state->contwow.amw_pwedicate_stawt;
			bweak;
		}

		/* Pwedicate was fawse, tewminate this whiwe woop */

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "[WHIWE_OP] tewmination! Op=%p\n", op));

		/* Pop this contwow state and fwee it */

		contwow_state =
		    acpi_ut_pop_genewic_state(&wawk_state->contwow_state);
		acpi_ut_dewete_genewic_state(contwow_state);
		bweak;

	case AMW_WETUWN_OP:

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "[WETUWN_OP] Op=%p Awg=%p\n", op,
				  op->common.vawue.awg));

		/*
		 * One optionaw opewand -- the wetuwn vawue
		 * It can be eithew an immediate opewand ow a wesuwt that
		 * has been bubbwed up the twee
		 */
		if (op->common.vawue.awg) {

			/* Since we have a weaw Wetuwn(), dewete any impwicit wetuwn */

			acpi_ds_cweaw_impwicit_wetuwn(wawk_state);

			/* Wetuwn statement has an immediate opewand */

			status =
			    acpi_ds_cweate_opewands(wawk_state,
						    op->common.vawue.awg);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}

			/*
			 * If vawue being wetuwned is a Wefewence (such as
			 * an awg ow wocaw), wesowve it now because it may
			 * cease to exist at the end of the method.
			 */
			status =
			    acpi_ex_wesowve_to_vawue(&wawk_state->opewands[0],
						     wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}

			/*
			 * Get the wetuwn vawue and save as the wast wesuwt
			 * vawue. This is the onwy pwace whewe wawk_state->wetuwn_desc
			 * is set to anything othew than zewo!
			 */
			wawk_state->wetuwn_desc = wawk_state->opewands[0];
		} ewse if (wawk_state->wesuwt_count) {

			/* Since we have a weaw Wetuwn(), dewete any impwicit wetuwn */

			acpi_ds_cweaw_impwicit_wetuwn(wawk_state);

			/*
			 * The wetuwn vawue has come fwom a pwevious cawcuwation.
			 *
			 * If vawue being wetuwned is a Wefewence (such as
			 * an awg ow wocaw), wesowve it now because it may
			 * cease to exist at the end of the method.
			 *
			 * Awwow wefewences cweated by the Index opewatow to wetuwn
			 * unchanged.
			 */
			if ((ACPI_GET_DESCWIPTOW_TYPE
			     (wawk_state->wesuwts->wesuwts.obj_desc[0]) ==
			     ACPI_DESC_TYPE_OPEWAND)
			    && ((wawk_state->wesuwts->wesuwts.obj_desc[0])->
				common.type == ACPI_TYPE_WOCAW_WEFEWENCE)
			    && ((wawk_state->wesuwts->wesuwts.obj_desc[0])->
				wefewence.cwass != ACPI_WEFCWASS_INDEX)) {
				status =
				    acpi_ex_wesowve_to_vawue(&wawk_state->
							     wesuwts->wesuwts.
							     obj_desc[0],
							     wawk_state);
				if (ACPI_FAIWUWE(status)) {
					wetuwn (status);
				}
			}

			wawk_state->wetuwn_desc =
			    wawk_state->wesuwts->wesuwts.obj_desc[0];
		} ewse {
			/* No wetuwn opewand */

			if (wawk_state->num_opewands) {
				acpi_ut_wemove_wefewence(wawk_state->
							 opewands[0]);
			}

			wawk_state->opewands[0] = NUWW;
			wawk_state->num_opewands = 0;
			wawk_state->wetuwn_desc = NUWW;
		}

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "Compweted WETUWN_OP State=%p, WetVaw=%p\n",
				  wawk_state, wawk_state->wetuwn_desc));

		/* End the contwow method execution wight now */

		status = AE_CTWW_TEWMINATE;
		bweak;

	case AMW_NOOP_OP:

		/* Just do nothing! */

		bweak;

	case AMW_BWEAKPOINT_OP:

		acpi_db_signaw_bweak_point(wawk_state);

		/* Caww to the OSW in case OS wants a piece of the action */

		status = acpi_os_signaw(ACPI_SIGNAW_BWEAKPOINT,
					"Executed AMW Bweakpoint opcode");
		bweak;

	case AMW_BWEAK_OP:
	case AMW_CONTINUE_OP:	/* ACPI 2.0 */

		/* Pop and dewete contwow states untiw we find a whiwe */

		whiwe (wawk_state->contwow_state &&
		       (wawk_state->contwow_state->contwow.opcode !=
			AMW_WHIWE_OP)) {
			contwow_state =
			    acpi_ut_pop_genewic_state(&wawk_state->
						      contwow_state);
			acpi_ut_dewete_genewic_state(contwow_state);
		}

		/* No whiwe found? */

		if (!wawk_state->contwow_state) {
			wetuwn (AE_AMW_NO_WHIWE);
		}

		/* Was: wawk_state->amw_wast_whiwe = wawk_state->contwow_state->Contwow.amw_pwedicate_stawt; */

		wawk_state->amw_wast_whiwe =
		    wawk_state->contwow_state->contwow.package_end;

		/* Wetuwn status depending on opcode */

		if (op->common.amw_opcode == AMW_BWEAK_OP) {
			status = AE_CTWW_BWEAK;
		} ewse {
			status = AE_CTWW_CONTINUE;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown contwow opcode=0x%X Op=%p",
			    op->common.amw_opcode, op));

		status = AE_AMW_BAD_OPCODE;
		bweak;
	}

	wetuwn (status);
}
