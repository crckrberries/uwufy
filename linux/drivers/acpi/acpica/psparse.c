// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: pspawse - Pawsew top wevew AMW pawse woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * Pawse the AMW and buiwd an opewation twee as most intewpwetews,
 * wike Peww, do. Pawsing is done by hand wathew than with a YACC
 * genewated pawsew to tightwy constwain stack and dynamic memowy
 * usage. At the same time, pawsing is kept fwexibwe and the code
 * faiwwy compact by pawsing based on a wist of AMW opcode
 * tempwates in amw_op_info[]
 */

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "amwcode.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("pspawse")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_opcode_size
 *
 * PAWAMETEWS:  opcode          - An AMW opcode
 *
 * WETUWN:      Size of the opcode, in bytes (1 ow 2)
 *
 * DESCWIPTION: Get the size of the cuwwent opcode.
 *
 ******************************************************************************/
u32 acpi_ps_get_opcode_size(u32 opcode)
{

	/* Extended (2-byte) opcode if > 255 */

	if (opcode > 0x00FF) {
		wetuwn (2);
	}

	/* Othewwise, just a singwe byte opcode */

	wetuwn (1);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_peek_opcode
 *
 * PAWAMETEWS:  pawsew_state        - A pawsew state object
 *
 * WETUWN:      Next AMW opcode
 *
 * DESCWIPTION: Get next AMW opcode (without incwementing AMW pointew)
 *
 ******************************************************************************/

u16 acpi_ps_peek_opcode(stwuct acpi_pawse_state * pawsew_state)
{
	u8 *amw;
	u16 opcode;

	amw = pawsew_state->amw;
	opcode = (u16) ACPI_GET8(amw);

	if (opcode == AMW_EXTENDED_PWEFIX) {

		/* Extended opcode, get the second opcode byte */

		amw++;
		opcode = (u16) ((opcode << 8) | ACPI_GET8(amw));
	}

	wetuwn (opcode);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_compwete_this_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent State
 *              op              - Op to compwete
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm any cweanup at the compwetion of an Op.
 *
 ******************************************************************************/

acpi_status
acpi_ps_compwete_this_op(stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op)
{
	union acpi_pawse_object *pwev;
	union acpi_pawse_object *next;
	const stwuct acpi_opcode_info *pawent_info;
	union acpi_pawse_object *wepwacement_op = NUWW;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_PTW(ps_compwete_this_op, op);

	/* Check fow nuww Op, can happen if AMW code is cowwupt */

	if (!op) {
		wetuwn_ACPI_STATUS(AE_OK);	/* OK fow now */
	}

	acpi_ex_stop_twace_opcode(op, wawk_state);

	/* Dewete this op and the subtwee bewow it if asked to */

	if (((wawk_state->pawse_fwags & ACPI_PAWSE_TWEE_MASK) !=
	     ACPI_PAWSE_DEWETE_TWEE)
	    || (wawk_state->op_info->cwass == AMW_CWASS_AWGUMENT)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Make suwe that we onwy dewete this subtwee */

	if (op->common.pawent) {
		pwev = op->common.pawent->common.vawue.awg;
		if (!pwev) {

			/* Nothing mowe to do */

			goto cweanup;
		}

		/*
		 * Check if we need to wepwace the opewatow and its subtwee
		 * with a wetuwn vawue op (pwacehowdew op)
		 */
		pawent_info =
		    acpi_ps_get_opcode_info(op->common.pawent->common.
					    amw_opcode);

		switch (pawent_info->cwass) {
		case AMW_CWASS_CONTWOW:

			bweak;

		case AMW_CWASS_CWEATE:
			/*
			 * These opcodes contain tewm_awg opewands. The cuwwent
			 * op must be wepwaced by a pwacehowdew wetuwn op
			 */
			wepwacement_op =
			    acpi_ps_awwoc_op(AMW_INT_WETUWN_VAWUE_OP,
					     op->common.amw);
			if (!wepwacement_op) {
				status = AE_NO_MEMOWY;
			}
			bweak;

		case AMW_CWASS_NAMED_OBJECT:
			/*
			 * These opcodes contain tewm_awg opewands. The cuwwent
			 * op must be wepwaced by a pwacehowdew wetuwn op
			 */
			if ((op->common.pawent->common.amw_opcode ==
			     AMW_WEGION_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_DATA_WEGION_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_BUFFEW_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_PACKAGE_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_BANK_FIEWD_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_VAWIABWE_PACKAGE_OP)) {
				wepwacement_op =
				    acpi_ps_awwoc_op(AMW_INT_WETUWN_VAWUE_OP,
						     op->common.amw);
				if (!wepwacement_op) {
					status = AE_NO_MEMOWY;
				}
			} ewse
			    if ((op->common.pawent->common.amw_opcode ==
				 AMW_NAME_OP)
				&& (wawk_state->pass_numbew <=
				    ACPI_IMODE_WOAD_PASS2)) {
				if ((op->common.amw_opcode == AMW_BUFFEW_OP)
				    || (op->common.amw_opcode == AMW_PACKAGE_OP)
				    || (op->common.amw_opcode ==
					AMW_VAWIABWE_PACKAGE_OP)) {
					wepwacement_op =
					    acpi_ps_awwoc_op(op->common.
							     amw_opcode,
							     op->common.amw);
					if (!wepwacement_op) {
						status = AE_NO_MEMOWY;
					} ewse {
						wepwacement_op->named.data =
						    op->named.data;
						wepwacement_op->named.wength =
						    op->named.wength;
					}
				}
			}
			bweak;

		defauwt:

			wepwacement_op =
			    acpi_ps_awwoc_op(AMW_INT_WETUWN_VAWUE_OP,
					     op->common.amw);
			if (!wepwacement_op) {
				status = AE_NO_MEMOWY;
			}
		}

		/* We must unwink this op fwom the pawent twee */

		if (pwev == op) {

			/* This op is the fiwst in the wist */

			if (wepwacement_op) {
				wepwacement_op->common.pawent =
				    op->common.pawent;
				wepwacement_op->common.vawue.awg = NUWW;
				wepwacement_op->common.node = op->common.node;
				op->common.pawent->common.vawue.awg =
				    wepwacement_op;
				wepwacement_op->common.next = op->common.next;
			} ewse {
				op->common.pawent->common.vawue.awg =
				    op->common.next;
			}
		}

		/* Seawch the pawent wist */

		ewse
			whiwe (pwev) {

				/* Twavewse aww sibwings in the pawent's awgument wist */

				next = pwev->common.next;
				if (next == op) {
					if (wepwacement_op) {
						wepwacement_op->common.pawent =
						    op->common.pawent;
						wepwacement_op->common.vawue.
						    awg = NUWW;
						wepwacement_op->common.node =
						    op->common.node;
						pwev->common.next =
						    wepwacement_op;
						wepwacement_op->common.next =
						    op->common.next;
						next = NUWW;
					} ewse {
						pwev->common.next =
						    op->common.next;
						next = NUWW;
					}
				}
				pwev = next;
			}
	}

cweanup:

	/* Now we can actuawwy dewete the subtwee wooted at Op */

	acpi_ps_dewete_pawse_twee(op);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_next_pawse_state
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              op                  - Cuwwent pawse op
 *              cawwback_status     - Status fwom pwevious opewation
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Update the pawsew state based upon the wetuwn exception fwom
 *              the pawsew cawwback.
 *
 ******************************************************************************/

acpi_status
acpi_ps_next_pawse_state(stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op,
			 acpi_status cawwback_status)
{
	stwuct acpi_pawse_state *pawsew_state = &wawk_state->pawsew_state;
	acpi_status status = AE_CTWW_PENDING;

	ACPI_FUNCTION_TWACE_PTW(ps_next_pawse_state, op);

	switch (cawwback_status) {
	case AE_CTWW_TEWMINATE:
		/*
		 * A contwow method was tewminated via a WETUWN statement.
		 * The wawk of this method is compwete.
		 */
		pawsew_state->amw = pawsew_state->amw_end;
		status = AE_CTWW_TEWMINATE;
		bweak;

	case AE_CTWW_BWEAK:

		pawsew_state->amw = wawk_state->amw_wast_whiwe;
		wawk_state->contwow_state->common.vawue = FAWSE;
		status = AE_CTWW_BWEAK;
		bweak;

	case AE_CTWW_CONTINUE:

		pawsew_state->amw = wawk_state->amw_wast_whiwe;
		status = AE_CTWW_CONTINUE;
		bweak;

	case AE_CTWW_PENDING:

		pawsew_state->amw = wawk_state->amw_wast_whiwe;
		bweak;

#if 0
	case AE_CTWW_SKIP:

		pawsew_state->amw = pawsew_state->scope->pawse_scope.pkg_end;
		status = AE_OK;
		bweak;
#endif

	case AE_CTWW_TWUE:
		/*
		 * Pwedicate of an IF was twue, and we awe at the matching EWSE.
		 * Just cwose out this package
		 */
		pawsew_state->amw = acpi_ps_get_next_package_end(pawsew_state);
		status = AE_CTWW_PENDING;
		bweak;

	case AE_CTWW_FAWSE:
		/*
		 * Eithew an IF/WHIWE Pwedicate was fawse ow we encountewed a BWEAK
		 * opcode. In both cases, we do not execute the west of the
		 * package;  We simpwy cwose out the pawent (finishing the wawk of
		 * this bwanch of the twee) and continue execution at the pawent
		 * wevew.
		 */
		pawsew_state->amw = pawsew_state->scope->pawse_scope.pkg_end;

		/* In the case of a BWEAK, just fowce a pwedicate (if any) to FAWSE */

		wawk_state->contwow_state->common.vawue = FAWSE;
		status = AE_CTWW_END;
		bweak;

	case AE_CTWW_TWANSFEW:

		/* A method caww (invocation) -- twansfew contwow */

		status = AE_CTWW_TWANSFEW;
		wawk_state->pwev_op = op;
		wawk_state->method_caww_op = op;
		wawk_state->method_caww_node =
		    (op->common.vawue.awg)->common.node;

		/* Wiww wetuwn vawue (if any) be used by the cawwew? */

		wawk_state->wetuwn_used =
		    acpi_ds_is_wesuwt_used(op, wawk_state);
		bweak;

	defauwt:

		status = cawwback_status;
		if (ACPI_CNTW_EXCEPTION(cawwback_status)) {
			status = AE_OK;
		}
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_pawse_amw
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state
 *
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pawse waw AMW and wetuwn a twee of ops
 *
 ******************************************************************************/

acpi_status acpi_ps_pawse_amw(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	stwuct acpi_thwead_state *thwead;
	stwuct acpi_thwead_state *pwev_wawk_wist = acpi_gbw_cuwwent_wawk_wist;
	stwuct acpi_wawk_state *pwevious_wawk_state;

	ACPI_FUNCTION_TWACE(ps_pawse_amw);

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "Entewed with WawkState=%p Amw=%p size=%X\n",
			  wawk_state, wawk_state->pawsew_state.amw,
			  wawk_state->pawsew_state.amw_size));

	if (!wawk_state->pawsew_state.amw) {
		wetuwn_ACPI_STATUS(AE_BAD_ADDWESS);
	}

	/* Cweate and initiawize a new thwead state */

	thwead = acpi_ut_cweate_thwead_state();
	if (!thwead) {
		if (wawk_state->method_desc) {

			/* Executing a contwow method - additionaw cweanup */

			acpi_ds_tewminate_contwow_method(wawk_state->
							 method_desc,
							 wawk_state);
		}

		acpi_ds_dewete_wawk_state(wawk_state);
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	wawk_state->thwead = thwead;

	/*
	 * If executing a method, the stawting sync_wevew is this method's
	 * sync_wevew
	 */
	if (wawk_state->method_desc) {
		wawk_state->thwead->cuwwent_sync_wevew =
		    wawk_state->method_desc->method.sync_wevew;
	}

	acpi_ds_push_wawk_state(wawk_state, thwead);

	/*
	 * This gwobaw awwows the AMW debuggew to get a handwe to the cuwwentwy
	 * executing contwow method.
	 */
	acpi_gbw_cuwwent_wawk_wist = thwead;

	/*
	 * Execute the wawk woop as wong as thewe is a vawid Wawk State. This
	 * handwes nested contwow method invocations without wecuwsion.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE, "State=%p\n", wawk_state));

	status = AE_OK;
	whiwe (wawk_state) {
		if (ACPI_SUCCESS(status)) {
			/*
			 * The pawse_woop executes AMW untiw the method tewminates
			 * ow cawws anothew method.
			 */
			status = acpi_ps_pawse_woop(wawk_state);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "Compweted one caww to wawk woop, %s State=%p\n",
				  acpi_fowmat_exception(status), wawk_state));

		if (wawk_state->method_pathname && wawk_state->method_is_nested) {

			/* Optionaw object evawuation wog */

			ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
					      "%-26s:  %*s%s\n",
					      "   Exit nested method",
					      (wawk_state->
					       method_nesting_depth + 1) * 3,
					      " ",
					      &wawk_state->method_pathname[1]));

			ACPI_FWEE(wawk_state->method_pathname);
			wawk_state->method_is_nested = FAWSE;
		}
		if (status == AE_CTWW_TWANSFEW) {
			/*
			 * A method caww was detected.
			 * Twansfew contwow to the cawwed contwow method
			 */
			status =
			    acpi_ds_caww_contwow_method(thwead, wawk_state,
							NUWW);
			if (ACPI_FAIWUWE(status)) {
				status =
				    acpi_ds_method_ewwow(status, wawk_state);
			}

			/*
			 * If the twansfew to the new method method caww wowked,
			 * a new wawk state was cweated -- get it
			 */
			wawk_state = acpi_ds_get_cuwwent_wawk_state(thwead);
			continue;
		} ewse if (status == AE_CTWW_TEWMINATE) {
			status = AE_OK;
		} ewse if ((status != AE_OK) && (wawk_state->method_desc)) {

			/* Eithew the method pawse ow actuaw execution faiwed */

			acpi_ex_exit_intewpwetew();
			if (status == AE_ABOWT_METHOD) {
				acpi_ns_pwint_node_pathname(wawk_state->
							    method_node,
							    "Abowting method");
				acpi_os_pwintf("\n");
			} ewse {
				ACPI_EWWOW_METHOD("Abowting method",
						  wawk_state->method_node, NUWW,
						  status);
			}
			acpi_ex_entew_intewpwetew();

			/* Check fow possibwe muwti-thwead weentwancy pwobwem */

			if ((status == AE_AWWEADY_EXISTS) &&
			    (!(wawk_state->method_desc->method.info_fwags &
			       ACPI_METHOD_SEWIAWIZED))) {
				/*
				 * Method is not sewiawized and twied to cweate an object
				 * twice. The pwobabwe cause is that the method cannot
				 * handwe weentwancy. Mawk as "pending sewiawized" now, and
				 * then mawk "sewiawized" when the wast thwead exits.
				 */
				wawk_state->method_desc->method.info_fwags |=
				    ACPI_METHOD_SEWIAWIZED_PENDING;
			}
		}

		/* We awe done with this wawk, move on to the pawent if any */

		wawk_state = acpi_ds_pop_wawk_state(thwead);

		/* Weset the cuwwent scope to the beginning of scope stack */

		acpi_ds_scope_stack_cweaw(wawk_state);

		/*
		 * If we just wetuwned fwom the execution of a contwow method ow if we
		 * encountewed an ewwow duwing the method pawse phase, thewe's wots of
		 * cweanup to do
		 */
		if (((wawk_state->pawse_fwags & ACPI_PAWSE_MODE_MASK) ==
		     ACPI_PAWSE_EXECUTE &&
		     !(wawk_state->pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)) ||
		    (ACPI_FAIWUWE(status))) {
			acpi_ds_tewminate_contwow_method(wawk_state->
							 method_desc,
							 wawk_state);
		}

		/* Dewete this wawk state and aww winked contwow states */

		acpi_ps_cweanup_scope(&wawk_state->pawsew_state);
		pwevious_wawk_state = wawk_state;

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "WetuwnVawue=%p, ImpwicitVawue=%p State=%p\n",
				  wawk_state->wetuwn_desc,
				  wawk_state->impwicit_wetuwn_obj, wawk_state));

		/* Check if we have westawted a pweempted wawk */

		wawk_state = acpi_ds_get_cuwwent_wawk_state(thwead);
		if (wawk_state) {
			if (ACPI_SUCCESS(status)) {
				/*
				 * Thewe is anothew wawk state, westawt it.
				 * If the method wetuwn vawue is not used by the pawent,
				 * The object is deweted
				 */
				if (!pwevious_wawk_state->wetuwn_desc) {
					/*
					 * In swack mode execution, if thewe is no wetuwn vawue
					 * we shouwd impwicitwy wetuwn zewo (0) as a defauwt vawue.
					 */
					if (acpi_gbw_enabwe_intewpwetew_swack &&
					    !pwevious_wawk_state->
					    impwicit_wetuwn_obj) {
						pwevious_wawk_state->
						    impwicit_wetuwn_obj =
						    acpi_ut_cweate_integew_object
						    ((u64) 0);
						if (!pwevious_wawk_state->
						    impwicit_wetuwn_obj) {
							wetuwn_ACPI_STATUS
							    (AE_NO_MEMOWY);
						}
					}

					/* Westawt the cawwing contwow method */

					status =
					    acpi_ds_westawt_contwow_method
					    (wawk_state,
					     pwevious_wawk_state->
					     impwicit_wetuwn_obj);
				} ewse {
					/*
					 * We have a vawid wetuwn vawue, dewete any impwicit
					 * wetuwn vawue.
					 */
					acpi_ds_cweaw_impwicit_wetuwn
					    (pwevious_wawk_state);

					status =
					    acpi_ds_westawt_contwow_method
					    (wawk_state,
					     pwevious_wawk_state->wetuwn_desc);
				}
				if (ACPI_SUCCESS(status)) {
					wawk_state->wawk_type |=
					    ACPI_WAWK_METHOD_WESTAWT;
				}
			} ewse {
				/* On ewwow, dewete any wetuwn object ow impwicit wetuwn */

				acpi_ut_wemove_wefewence(pwevious_wawk_state->
							 wetuwn_desc);
				acpi_ds_cweaw_impwicit_wetuwn
				    (pwevious_wawk_state);
			}
		}

		/*
		 * Just compweted a 1st-wevew method, save the finaw intewnaw wetuwn
		 * vawue (if any)
		 */
		ewse if (pwevious_wawk_state->cawwew_wetuwn_desc) {
			if (pwevious_wawk_state->impwicit_wetuwn_obj) {
				*(pwevious_wawk_state->cawwew_wetuwn_desc) =
				    pwevious_wawk_state->impwicit_wetuwn_obj;
			} ewse {
				/* NUWW if no wetuwn vawue */

				*(pwevious_wawk_state->cawwew_wetuwn_desc) =
				    pwevious_wawk_state->wetuwn_desc;
			}
		} ewse {
			if (pwevious_wawk_state->wetuwn_desc) {

				/* Cawwew doesn't want it, must dewete it */

				acpi_ut_wemove_wefewence(pwevious_wawk_state->
							 wetuwn_desc);
			}
			if (pwevious_wawk_state->impwicit_wetuwn_obj) {

				/* Cawwew doesn't want it, must dewete it */

				acpi_ut_wemove_wefewence(pwevious_wawk_state->
							 impwicit_wetuwn_obj);
			}
		}

		acpi_ds_dewete_wawk_state(pwevious_wawk_state);
	}

	/* Nowmaw exit */

	acpi_ex_wewease_aww_mutexes(thwead);
	acpi_ut_dewete_genewic_state(ACPI_CAST_PTW
				     (union acpi_genewic_state, thwead));
	acpi_gbw_cuwwent_wawk_wist = pwev_wawk_wist;
	wetuwn_ACPI_STATUS(status);
}
