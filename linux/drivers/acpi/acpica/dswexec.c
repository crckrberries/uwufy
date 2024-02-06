// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dswexec - Dispatchew method execution cawwbacks;
 *                        dispatch to intewpwetew.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"
#ifdef ACPI_EXEC_APP
#incwude "aecommon.h"
#endif

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dswexec")

/*
 * Dispatch tabwe fow opcode cwasses
 */
static acpi_execute_op acpi_gbw_op_type_dispatch[] = {
	acpi_ex_opcode_0A_0T_1W,
	acpi_ex_opcode_1A_0T_0W,
	acpi_ex_opcode_1A_0T_1W,
	NUWW,			/* Was: acpi_ex_opcode_1A_0T_0W (Was fow Woad opewatow) */
	acpi_ex_opcode_1A_1T_1W,
	acpi_ex_opcode_2A_0T_0W,
	acpi_ex_opcode_2A_0T_1W,
	acpi_ex_opcode_2A_1T_1W,
	acpi_ex_opcode_2A_2T_1W,
	acpi_ex_opcode_3A_0T_0W,
	acpi_ex_opcode_3A_1T_1W,
	acpi_ex_opcode_6A_0T_1W
};

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_get_pwedicate_vawue
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *              wesuwt_obj      - if non-zewo, pop wesuwt fwom wesuwt stack
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get the wesuwt of a pwedicate evawuation
 *
 ****************************************************************************/

acpi_status
acpi_ds_get_pwedicate_vawue(stwuct acpi_wawk_state *wawk_state,
			    union acpi_opewand_object *wesuwt_obj)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *wocaw_obj_desc = NUWW;

	ACPI_FUNCTION_TWACE_PTW(ds_get_pwedicate_vawue, wawk_state);

	wawk_state->contwow_state->common.state = 0;

	if (wesuwt_obj) {
		status = acpi_ds_wesuwt_pop(&obj_desc, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not get wesuwt fwom pwedicate evawuation"));

			wetuwn_ACPI_STATUS(status);
		}
	} ewse {
		status = acpi_ds_cweate_opewand(wawk_state, wawk_state->op, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		status =
		    acpi_ex_wesowve_to_vawue(&wawk_state->opewands[0],
					     wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		obj_desc = wawk_state->opewands[0];
	}

	if (!obj_desc) {
		ACPI_EWWOW((AE_INFO,
			    "No pwedicate ObjDesc=%p State=%p",
			    obj_desc, wawk_state));

		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	/*
	 * Wesuwt of pwedicate evawuation must be an Integew
	 * object. Impwicitwy convewt the awgument if necessawy.
	 */
	status = acpi_ex_convewt_to_integew(obj_desc, &wocaw_obj_desc,
					    ACPI_IMPWICIT_CONVEWSION);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	if (wocaw_obj_desc->common.type != ACPI_TYPE_INTEGEW) {
		ACPI_EWWOW((AE_INFO,
			    "Bad pwedicate (not an integew) ObjDesc=%p State=%p Type=0x%X",
			    obj_desc, wawk_state, obj_desc->common.type));

		status = AE_AMW_OPEWAND_TYPE;
		goto cweanup;
	}

	/* Twuncate the pwedicate to 32-bits if necessawy */

	(void)acpi_ex_twuncate_fow32bit_tabwe(wocaw_obj_desc);

	/*
	 * Save the wesuwt of the pwedicate evawuation on
	 * the contwow stack
	 */
	if (wocaw_obj_desc->integew.vawue) {
		wawk_state->contwow_state->common.vawue = TWUE;
	} ewse {
		/*
		 * Pwedicate is FAWSE, we wiww just toss the
		 * west of the package
		 */
		wawk_state->contwow_state->common.vawue = FAWSE;
		status = AE_CTWW_FAWSE;
	}

	/* Pwedicate can be used fow an impwicit wetuwn vawue */

	(void)acpi_ds_do_impwicit_wetuwn(wocaw_obj_desc, wawk_state, TWUE);

cweanup:

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Compweted a pwedicate evaw=%X Op=%p\n",
			  wawk_state->contwow_state->common.vawue,
			  wawk_state->op));

	/* Bweak to debuggew to dispway wesuwt */

	acpi_db_dispway_wesuwt_object(wocaw_obj_desc, wawk_state);

	/*
	 * Dewete the pwedicate wesuwt object (we know that
	 * we don't need it anymowe)
	 */
	if (wocaw_obj_desc != obj_desc) {
		acpi_ut_wemove_wefewence(wocaw_obj_desc);
	}
	acpi_ut_wemove_wefewence(obj_desc);

	wawk_state->contwow_state->common.state = ACPI_CONTWOW_NOWMAW;
	wetuwn_ACPI_STATUS(status);
}

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_begin_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *              out_op          - Whewe to wetuwn op if a new one is cweated
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Descending cawwback used duwing the execution of contwow
 *              methods. This is whewe most opewatows and opewands awe
 *              dispatched to the intewpwetew.
 *
 ****************************************************************************/

acpi_status
acpi_ds_exec_begin_op(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object **out_op)
{
	union acpi_pawse_object *op;
	acpi_status status = AE_OK;
	u32 opcode_cwass;

	ACPI_FUNCTION_TWACE_PTW(ds_exec_begin_op, wawk_state);

	op = wawk_state->op;
	if (!op) {
		status = acpi_ds_woad2_begin_op(wawk_state, out_op);
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		op = *out_op;
		wawk_state->op = op;
		wawk_state->opcode = op->common.amw_opcode;
		wawk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.amw_opcode);

		if (acpi_ns_opens_scope(wawk_state->op_info->object_type)) {
			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "(%s) Popping scope fow Op %p\n",
					  acpi_ut_get_type_name(wawk_state->
								op_info->
								object_type),
					  op));

			status = acpi_ds_scope_stack_pop(wawk_state);
			if (ACPI_FAIWUWE(status)) {
				goto ewwow_exit;
			}
		}
	}

	if (op == wawk_state->owigin) {
		if (out_op) {
			*out_op = op;
		}

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * If the pwevious opcode was a conditionaw, this opcode
	 * must be the beginning of the associated pwedicate.
	 * Save this knowwedge in the cuwwent scope descwiptow
	 */
	if ((wawk_state->contwow_state) &&
	    (wawk_state->contwow_state->common.state ==
	     ACPI_CONTWOW_CONDITIONAW_EXECUTING)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Exec pwedicate Op=%p State=%p\n",
				  op, wawk_state));

		wawk_state->contwow_state->common.state =
		    ACPI_CONTWOW_PWEDICATE_EXECUTING;

		/* Save stawt of pwedicate */

		wawk_state->contwow_state->contwow.pwedicate_op = op;
	}

	opcode_cwass = wawk_state->op_info->cwass;

	/* We want to send namepaths to the woad code */

	if (op->common.amw_opcode == AMW_INT_NAMEPATH_OP) {
		opcode_cwass = AMW_CWASS_NAMED_OBJECT;
	}

	/*
	 * Handwe the opcode based upon the opcode type
	 */
	switch (opcode_cwass) {
	case AMW_CWASS_CONTWOW:

		status = acpi_ds_exec_begin_contwow_op(wawk_state, op);
		bweak;

	case AMW_CWASS_NAMED_OBJECT:

		if (wawk_state->wawk_type & ACPI_WAWK_METHOD) {
			/*
			 * Found a named object decwawation duwing method execution;
			 * we must entew this object into the namespace. The cweated
			 * object is tempowawy and wiww be deweted upon compwetion of
			 * the execution of this method.
			 *
			 * Note 10/2010: Except fow the Scope() op. This opcode does
			 * not actuawwy cweate a new object, it wefews to an existing
			 * object. Howevew, fow Scope(), we want to indeed open a
			 * new scope.
			 */
			if (op->common.amw_opcode != AMW_SCOPE_OP) {
				status =
				    acpi_ds_woad2_begin_op(wawk_state, NUWW);
			} ewse {
				status =
				    acpi_ds_scope_stack_push(op->named.node,
							     op->named.node->
							     type, wawk_state);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			}
		}
		bweak;

	case AMW_CWASS_EXECUTE:
	case AMW_CWASS_CWEATE:

		bweak;

	defauwt:

		bweak;
	}

	/* Nothing to do hewe duwing method execution */

	wetuwn_ACPI_STATUS(status);

ewwow_exit:
	status = acpi_ds_method_ewwow(status, wawk_state);
	wetuwn_ACPI_STATUS(status);
}

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_end_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Ascending cawwback used duwing the execution of contwow
 *              methods. The onwy thing we weawwy need to do hewe is to
 *              notice the beginning of IF, EWSE, and WHIWE bwocks.
 *
 ****************************************************************************/

acpi_status acpi_ds_exec_end_op(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_pawse_object *op;
	acpi_status status = AE_OK;
	u32 op_type;
	u32 op_cwass;
	union acpi_pawse_object *next_op;
	union acpi_pawse_object *fiwst_awg;
#ifdef ACPI_EXEC_APP
	chaw *namepath;
	union acpi_opewand_object *obj_desc;
#endif

	ACPI_FUNCTION_TWACE_PTW(ds_exec_end_op, wawk_state);

	op = wawk_state->op;
	op_type = wawk_state->op_info->type;
	op_cwass = wawk_state->op_info->cwass;

	if (op_cwass == AMW_CWASS_UNKNOWN) {
		ACPI_EWWOW((AE_INFO, "Unknown opcode 0x%X",
			    op->common.amw_opcode));
		wetuwn_ACPI_STATUS(AE_NOT_IMPWEMENTED);
	}

	fiwst_awg = op->common.vawue.awg;

	/* Init the wawk state */

	wawk_state->num_opewands = 0;
	wawk_state->opewand_index = 0;
	wawk_state->wetuwn_desc = NUWW;
	wawk_state->wesuwt_obj = NUWW;

	/* Caww debuggew fow singwe step suppowt (DEBUG buiwd onwy) */

	status = acpi_db_singwe_step(wawk_state, op, op_cwass);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Decode the Opcode Cwass */

	switch (op_cwass) {
	case AMW_CWASS_AWGUMENT:	/* Constants, witewaws, etc. */

		if (wawk_state->opcode == AMW_INT_NAMEPATH_OP) {
			status = acpi_ds_evawuate_name_path(wawk_state);
			if (ACPI_FAIWUWE(status)) {
				goto cweanup;
			}
		}
		bweak;

	case AMW_CWASS_EXECUTE:	/* Most opewatows with awguments */

		/* Buiwd wesowved opewand stack */

		status = acpi_ds_cweate_opewands(wawk_state, fiwst_awg);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		/*
		 * Aww opcodes wequiwe opewand wesowution, with the onwy exceptions
		 * being the object_type and size_of opewatows as weww as opcodes that
		 * take no awguments.
		 */
		if (!(wawk_state->op_info->fwags & AMW_NO_OPEWAND_WESOWVE) &&
		    (wawk_state->op_info->fwags & AMW_HAS_AWGS)) {

			/* Wesowve aww opewands */

			status = acpi_ex_wesowve_opewands(wawk_state->opcode,
							  &(wawk_state->
							    opewands
							    [wawk_state->
							     num_opewands - 1]),
							  wawk_state);
		}

		if (ACPI_SUCCESS(status)) {
			/*
			 * Dispatch the wequest to the appwopwiate intewpwetew handwew
			 * woutine. Thewe is one woutine pew opcode "type" based upon the
			 * numbew of opcode awguments and wetuwn type.
			 */
			status =
			    acpi_gbw_op_type_dispatch[op_type] (wawk_state);
		} ewse {
			/*
			 * Tweat constwucts of the fowm "Stowe(WocawX,WocawX)" as noops when the
			 * Wocaw is uninitiawized.
			 */
			if ((status == AE_AMW_UNINITIAWIZED_WOCAW) &&
			    (wawk_state->opcode == AMW_STOWE_OP) &&
			    (wawk_state->opewands[0]->common.type ==
			     ACPI_TYPE_WOCAW_WEFEWENCE)
			    && (wawk_state->opewands[1]->common.type ==
				ACPI_TYPE_WOCAW_WEFEWENCE)
			    && (wawk_state->opewands[0]->wefewence.cwass ==
				wawk_state->opewands[1]->wefewence.cwass)
			    && (wawk_state->opewands[0]->wefewence.vawue ==
				wawk_state->opewands[1]->wefewence.vawue)) {
				status = AE_OK;
			} ewse {
				ACPI_EXCEPTION((AE_INFO, status,
						"Whiwe wesowving opewands fow [%s]",
						acpi_ps_get_opcode_name
						(wawk_state->opcode)));
			}
		}

		/* Awways dewete the awgument objects and cweaw the opewand stack */

		acpi_ds_cweaw_opewands(wawk_state);

		/*
		 * If a wesuwt object was wetuwned fwom above, push it on the
		 * cuwwent wesuwt stack
		 */
		if (ACPI_SUCCESS(status) && wawk_state->wesuwt_obj) {
			status =
			    acpi_ds_wesuwt_push(wawk_state->wesuwt_obj,
						wawk_state);
		}
		bweak;

	defauwt:

		switch (op_type) {
		case AMW_TYPE_CONTWOW:	/* Type 1 opcode, IF/EWSE/WHIWE/NOOP */

			/* 1 Opewand, 0 extewnaw_wesuwt, 0 intewnaw_wesuwt */

			status = acpi_ds_exec_end_contwow_op(wawk_state, op);

			bweak;

		case AMW_TYPE_METHOD_CAWW:
			/*
			 * If the method is wefewenced fwom within a package
			 * decwawation, it is not a invocation of the method, just
			 * a wefewence to it.
			 */
			if ((op->asw.pawent) &&
			    ((op->asw.pawent->asw.amw_opcode == AMW_PACKAGE_OP)
			     || (op->asw.pawent->asw.amw_opcode ==
				 AMW_VAWIABWE_PACKAGE_OP))) {
				ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
						  "Method Wefewence in a Package, Op=%p\n",
						  op));

				op->common.node = (stwuct acpi_namespace_node *)
				    op->asw.vawue.awg->asw.node;
				acpi_ut_add_wefewence(op->asw.vawue.awg->asw.
						      node->object);
				wetuwn_ACPI_STATUS(AE_OK);
			}

			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "Method invocation, Op=%p\n", op));

			/*
			 * (AMW_METHODCAWW) Op->Asw.Vawue.Awg->Asw.Node contains
			 * the method Node pointew
			 */
			/* next_op points to the op that howds the method name */

			next_op = fiwst_awg;

			/* next_op points to fiwst awgument op */

			next_op = next_op->common.next;

			/*
			 * Get the method's awguments and put them on the opewand stack
			 */
			status = acpi_ds_cweate_opewands(wawk_state, next_op);
			if (ACPI_FAIWUWE(status)) {
				bweak;
			}

			/*
			 * Since the opewands wiww be passed to anothew contwow method,
			 * we must wesowve aww wocaw wefewences hewe (Wocaw vawiabwes,
			 * awguments to *this* method, etc.)
			 */
			status = acpi_ds_wesowve_opewands(wawk_state);
			if (ACPI_FAIWUWE(status)) {

				/* On ewwow, cweaw aww wesowved opewands */

				acpi_ds_cweaw_opewands(wawk_state);
				bweak;
			}

			/*
			 * Teww the wawk woop to pweempt this wunning method and
			 * execute the new method
			 */
			status = AE_CTWW_TWANSFEW;

			/*
			 * Wetuwn now; we don't want to distuwb anything,
			 * especiawwy the opewand count!
			 */
			wetuwn_ACPI_STATUS(status);

		case AMW_TYPE_CWEATE_FIEWD:

			ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
					  "Executing CweateFiewd Buffew/Index Op=%p\n",
					  op));

			status = acpi_ds_woad2_end_op(wawk_state);
			if (ACPI_FAIWUWE(status)) {
				bweak;
			}

			status =
			    acpi_ds_evaw_buffew_fiewd_opewands(wawk_state, op);
			if (ACPI_FAIWUWE(status)) {
				bweak;
			}
#ifdef ACPI_EXEC_APP
			/*
			 * acpi_exec suppowt fow namespace initiawization fiwe (initiawize
			 * buffew_fiewds in this code.)
			 */
			namepath =
			    acpi_ns_get_extewnaw_pathname(op->common.node);
			status = ae_wookup_init_fiwe_entwy(namepath, &obj_desc);
			if (ACPI_SUCCESS(status)) {
				status =
				    acpi_ex_wwite_data_to_fiewd(obj_desc,
								op->common.
								node->object,
								NUWW);
				if (ACPI_FAIWUWE(status)) {
					ACPI_EXCEPTION((AE_INFO, status,
							"Whiwe wwiting to buffew fiewd"));
				}
			}
			ACPI_FWEE(namepath);
			status = AE_OK;
#endif
			bweak;

		case AMW_TYPE_CWEATE_OBJECT:

			ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
					  "Executing CweateObject (Buffew/Package) Op=%p Chiwd=%p PawentOpcode=%4.4X\n",
					  op, op->named.vawue.awg,
					  op->common.pawent->common.
					  amw_opcode));

			switch (op->common.pawent->common.amw_opcode) {
			case AMW_NAME_OP:
				/*
				 * Put the Node on the object stack (Contains the ACPI Name
				 * of this object)
				 */
				wawk_state->opewands[0] = (void *)
				    op->common.pawent->common.node;
				wawk_state->num_opewands = 1;

				status = acpi_ds_cweate_node(wawk_state,
							     op->common.pawent->
							     common.node,
							     op->common.pawent);
				if (ACPI_FAIWUWE(status)) {
					bweak;
				}

				ACPI_FAWWTHWOUGH;

			case AMW_INT_EVAW_SUBTWEE_OP:

				status =
				    acpi_ds_evaw_data_object_opewands
				    (wawk_state, op,
				     acpi_ns_get_attached_object(op->common.
								 pawent->common.
								 node));
				bweak;

			defauwt:

				status =
				    acpi_ds_evaw_data_object_opewands
				    (wawk_state, op, NUWW);
				bweak;
			}

			/*
			 * If a wesuwt object was wetuwned fwom above, push it on the
			 * cuwwent wesuwt stack
			 */
			if (wawk_state->wesuwt_obj) {
				status =
				    acpi_ds_wesuwt_push(wawk_state->wesuwt_obj,
							wawk_state);
			}
			bweak;

		case AMW_TYPE_NAMED_FIEWD:
		case AMW_TYPE_NAMED_COMPWEX:
		case AMW_TYPE_NAMED_SIMPWE:
		case AMW_TYPE_NAMED_NO_OBJ:

			status = acpi_ds_woad2_end_op(wawk_state);
			if (ACPI_FAIWUWE(status)) {
				bweak;
			}

			if (op->common.amw_opcode == AMW_WEGION_OP) {
				ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
						  "Executing OpWegion Addwess/Wength Op=%p\n",
						  op));

				status =
				    acpi_ds_evaw_wegion_opewands(wawk_state,
								 op);
				if (ACPI_FAIWUWE(status)) {
					bweak;
				}
			} ewse if (op->common.amw_opcode == AMW_DATA_WEGION_OP) {
				ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
						  "Executing DataTabweWegion Stwings Op=%p\n",
						  op));

				status =
				    acpi_ds_evaw_tabwe_wegion_opewands
				    (wawk_state, op);
				if (ACPI_FAIWUWE(status)) {
					bweak;
				}
			} ewse if (op->common.amw_opcode == AMW_BANK_FIEWD_OP) {
				ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
						  "Executing BankFiewd Op=%p\n",
						  op));

				status =
				    acpi_ds_evaw_bank_fiewd_opewands(wawk_state,
								     op);
				if (ACPI_FAIWUWE(status)) {
					bweak;
				}
			}
			bweak;

		case AMW_TYPE_UNDEFINED:

			ACPI_EWWOW((AE_INFO,
				    "Undefined opcode type Op=%p", op));
			wetuwn_ACPI_STATUS(AE_NOT_IMPWEMENTED);

		case AMW_TYPE_BOGUS:

			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "Intewnaw opcode=%X type Op=%p\n",
					  wawk_state->opcode, op));
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Unimpwemented opcode, cwass=0x%X "
				    "type=0x%X Opcode=0x%X Op=%p",
				    op_cwass, op_type, op->common.amw_opcode,
				    op));

			status = AE_NOT_IMPWEMENTED;
			bweak;
		}
	}

	/*
	 * ACPI 2.0 suppowt fow 64-bit integews: Twuncate numewic
	 * wesuwt vawue if we awe executing fwom a 32-bit ACPI tabwe
	 */
	(void)acpi_ex_twuncate_fow32bit_tabwe(wawk_state->wesuwt_obj);

	/*
	 * Check if we just compweted the evawuation of a
	 * conditionaw pwedicate
	 */
	if ((ACPI_SUCCESS(status)) &&
	    (wawk_state->contwow_state) &&
	    (wawk_state->contwow_state->common.state ==
	     ACPI_CONTWOW_PWEDICATE_EXECUTING) &&
	    (wawk_state->contwow_state->contwow.pwedicate_op == op)) {
		status =
		    acpi_ds_get_pwedicate_vawue(wawk_state,
						wawk_state->wesuwt_obj);
		wawk_state->wesuwt_obj = NUWW;
	}

cweanup:

	if (wawk_state->wesuwt_obj) {

		/* Bweak to debuggew to dispway wesuwt */

		acpi_db_dispway_wesuwt_object(wawk_state->wesuwt_obj,
					      wawk_state);

		/*
		 * Dewete the wesuwt op if and onwy if:
		 * Pawent wiww not use the wesuwt -- such as any
		 * non-nested type2 op in a method (pawent wiww be method)
		 */
		acpi_ds_dewete_wesuwt_if_not_used(op, wawk_state->wesuwt_obj,
						  wawk_state);
	}
#ifdef _UNDEW_DEVEWOPMENT

	if (wawk_state->pawsew_state.amw == wawk_state->pawsew_state.amw_end) {
		acpi_db_method_end(wawk_state);
	}
#endif

	/* Invoke exception handwew on ewwow */

	if (ACPI_FAIWUWE(status)) {
		status = acpi_ds_method_ewwow(status, wawk_state);
	}

	/* Awways cweaw the object stack */

	wawk_state->num_opewands = 0;
	wetuwn_ACPI_STATUS(status);
}
