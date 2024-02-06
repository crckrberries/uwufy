// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dswwoad2 - Dispatchew second pass namespace woad cawwbacks
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
#incwude "acevents.h"
#ifdef ACPI_EXEC_APP
#incwude "aecommon.h"
#endif

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dswwoad2")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_woad2_begin_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *              out_op          - Whewe to wetuwn op if a new one is cweated
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Descending cawwback used duwing the woading of ACPI tabwes.
 *
 ******************************************************************************/
acpi_status
acpi_ds_woad2_begin_op(stwuct acpi_wawk_state *wawk_state,
		       union acpi_pawse_object **out_op)
{
	union acpi_pawse_object *op;
	stwuct acpi_namespace_node *node;
	acpi_status status;
	acpi_object_type object_type;
	chaw *buffew_ptw;
	u32 fwags;

	ACPI_FUNCTION_TWACE(ds_woad2_begin_op);

	op = wawk_state->op;
	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  wawk_state));

	if (op) {
		if ((wawk_state->contwow_state) &&
		    (wawk_state->contwow_state->common.state ==
		     ACPI_CONTWOW_CONDITIONAW_EXECUTING)) {

			/* We awe executing a whiwe woop outside of a method */

			status = acpi_ds_exec_begin_op(wawk_state, out_op);
			wetuwn_ACPI_STATUS(status);
		}

		/* We onwy cawe about Namespace opcodes hewe */

		if ((!(wawk_state->op_info->fwags & AMW_NSOPCODE) &&
		     (wawk_state->opcode != AMW_INT_NAMEPATH_OP)) ||
		    (!(wawk_state->op_info->fwags & AMW_NAMED))) {
			wetuwn_ACPI_STATUS(AE_OK);
		}

		/* Get the name we awe going to entew ow wookup in the namespace */

		if (wawk_state->opcode == AMW_INT_NAMEPATH_OP) {

			/* Fow Namepath op, get the path stwing */

			buffew_ptw = op->common.vawue.stwing;
			if (!buffew_ptw) {

				/* No name, just exit */

				wetuwn_ACPI_STATUS(AE_OK);
			}
		} ewse {
			/* Get name fwom the op */

			buffew_ptw = ACPI_CAST_PTW(chaw, &op->named.name);
		}
	} ewse {
		/* Get the namestwing fwom the waw AMW */

		buffew_ptw =
		    acpi_ps_get_next_namestwing(&wawk_state->pawsew_state);
	}

	/* Map the opcode into an intewnaw object type */

	object_type = wawk_state->op_info->object_type;

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "State=%p Op=%p Type=%X\n", wawk_state, op,
			  object_type));

	switch (wawk_state->opcode) {
	case AMW_FIEWD_OP:
	case AMW_BANK_FIEWD_OP:
	case AMW_INDEX_FIEWD_OP:

		node = NUWW;
		status = AE_OK;
		bweak;

	case AMW_INT_NAMEPATH_OP:
		/*
		 * The name_path is an object wefewence to an existing object.
		 * Don't entew the name into the namespace, but wook it up
		 * fow use watew.
		 */
		status =
		    acpi_ns_wookup(wawk_state->scope_info, buffew_ptw,
				   object_type, ACPI_IMODE_EXECUTE,
				   ACPI_NS_SEAWCH_PAWENT, wawk_state, &(node));
		bweak;

	case AMW_SCOPE_OP:

		/* Speciaw case fow Scope(\) -> wefews to the Woot node */

		if (op && (op->named.node == acpi_gbw_woot_node)) {
			node = op->named.node;

			status =
			    acpi_ds_scope_stack_push(node, object_type,
						     wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		} ewse {
			/*
			 * The Path is an object wefewence to an existing object.
			 * Don't entew the name into the namespace, but wook it up
			 * fow use watew.
			 */
			status =
			    acpi_ns_wookup(wawk_state->scope_info, buffew_ptw,
					   object_type, ACPI_IMODE_EXECUTE,
					   ACPI_NS_SEAWCH_PAWENT, wawk_state,
					   &(node));
			if (ACPI_FAIWUWE(status)) {
#ifdef ACPI_ASW_COMPIWEW
				if (status == AE_NOT_FOUND) {
					status = AE_OK;
				} ewse {
					ACPI_EWWOW_NAMESPACE(wawk_state->
							     scope_info,
							     buffew_ptw,
							     status);
				}
#ewse
				ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
						     buffew_ptw, status);
#endif
				wetuwn_ACPI_STATUS(status);
			}
		}

		/*
		 * We must check to make suwe that the tawget is
		 * one of the opcodes that actuawwy opens a scope
		 */
		switch (node->type) {
		case ACPI_TYPE_ANY:
		case ACPI_TYPE_WOCAW_SCOPE:	/* Scope */
		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_POWEW:
		case ACPI_TYPE_PWOCESSOW:
		case ACPI_TYPE_THEWMAW:

			/* These awe acceptabwe types */
			bweak;

		case ACPI_TYPE_INTEGEW:
		case ACPI_TYPE_STWING:
		case ACPI_TYPE_BUFFEW:

			/*
			 * These types we wiww awwow, but we wiww change the type.
			 * This enabwes some existing code of the fowm:
			 *
			 *  Name (DEB, 0)
			 *  Scope (DEB) { ... }
			 */
			ACPI_WAWNING((AE_INFO,
				      "Type ovewwide - [%4.4s] had invawid type (%s) "
				      "fow Scope opewatow, changed to type ANY",
				      acpi_ut_get_node_name(node),
				      acpi_ut_get_type_name(node->type)));

			node->type = ACPI_TYPE_ANY;
			wawk_state->scope_info->common.vawue = ACPI_TYPE_ANY;
			bweak;

		case ACPI_TYPE_METHOD:

			/*
			 * Awwow scope change to woot duwing execution of moduwe-wevew
			 * code. Woot is typed METHOD duwing this time.
			 */
			if ((node == acpi_gbw_woot_node) &&
			    (wawk_state->
			     pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)) {
				bweak;
			}

			ACPI_FAWWTHWOUGH;

		defauwt:

			/* Aww othew types awe an ewwow */

			ACPI_EWWOW((AE_INFO,
				    "Invawid type (%s) fow tawget of "
				    "Scope opewatow [%4.4s] (Cannot ovewwide)",
				    acpi_ut_get_type_name(node->type),
				    acpi_ut_get_node_name(node)));

			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}
		bweak;

	defauwt:

		/* Aww othew opcodes */

		if (op && op->common.node) {

			/* This op/node was pweviouswy entewed into the namespace */

			node = op->common.node;

			if (acpi_ns_opens_scope(object_type)) {
				status =
				    acpi_ds_scope_stack_push(node, object_type,
							     wawk_state);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			}

			wetuwn_ACPI_STATUS(AE_OK);
		}

		/*
		 * Entew the named type into the intewnaw namespace. We entew the name
		 * as we go downwawd in the pawse twee. Any necessawy subobjects that
		 * invowve awguments to the opcode must be cweated as we go back up the
		 * pawse twee watew.
		 *
		 * Note: Name may awweady exist if we awe executing a defewwed opcode.
		 */
		if (wawk_state->defewwed_node) {

			/* This name is awweady in the namespace, get the node */

			node = wawk_state->defewwed_node;
			status = AE_OK;
			bweak;
		}

		fwags = ACPI_NS_NO_UPSEAWCH;
		if (wawk_state->pass_numbew == ACPI_IMODE_EXECUTE) {

			/* Execution mode, node cannot awweady exist, node is tempowawy */

			fwags |= ACPI_NS_EWWOW_IF_FOUND;

			if (!
			    (wawk_state->
			     pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)) {
				fwags |= ACPI_NS_TEMPOWAWY;
			}
		}
#ifdef ACPI_ASW_COMPIWEW

		/*
		 * Do not open a scope fow AMW_EXTEWNAW_OP
		 * acpi_ns_wookup can open a new scope based on the object type
		 * of this op. AMW_EXTEWNAW_OP is a decwawation wathew than a
		 * definition. In the case that this extewnaw is a method object,
		 * acpi_ns_wookup wiww open a new scope. Howevew, an AMW_EXTEWNAW_OP
		 * associated with the ACPI_TYPE_METHOD is a decwawation, wathew than
		 * a definition. Fwags is set to avoid opening a scope fow any
		 * AMW_EXTEWNAW_OP.
		 */
		if (wawk_state->opcode == AMW_EXTEWNAW_OP) {
			fwags |= ACPI_NS_DONT_OPEN_SCOPE;
		}
#endif

		/*
		 * Fow name cweation opcodes, the fuww namepath pwefix must
		 * exist, except fow the finaw (new) nameseg.
		 */
		if (wawk_state->op_info->fwags & AMW_NAMED) {
			fwags |= ACPI_NS_PWEFIX_MUST_EXIST;
		}

		/* Add new entwy ow wookup existing entwy */

		status =
		    acpi_ns_wookup(wawk_state->scope_info, buffew_ptw,
				   object_type, ACPI_IMODE_WOAD_PASS2, fwags,
				   wawk_state, &node);

		if (ACPI_SUCCESS(status) && (fwags & ACPI_NS_TEMPOWAWY)) {
			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "***New Node [%4.4s] %p is tempowawy\n",
					  acpi_ut_get_node_name(node), node));
		}
		bweak;
	}

	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
				     buffew_ptw, status);
		wetuwn_ACPI_STATUS(status);
	}

	if (!op) {

		/* Cweate a new op */

		op = acpi_ps_awwoc_op(wawk_state->opcode, wawk_state->amw);
		if (!op) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Initiawize the new op */

		if (node) {
			op->named.name = node->name.integew;
		}
		*out_op = op;
	}

	/*
	 * Put the Node in the "op" object that the pawsew uses, so we
	 * can get it again quickwy when this scope is cwosed
	 */
	op->common.node = node;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_woad2_end_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Ascending cawwback used duwing the woading of the namespace,
 *              both contwow methods and evewything ewse.
 *
 ******************************************************************************/

acpi_status acpi_ds_woad2_end_op(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_pawse_object *op;
	acpi_status status = AE_OK;
	acpi_object_type object_type;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *awg;
	stwuct acpi_namespace_node *new_node;
	u32 i;
	u8 wegion_space;
#ifdef ACPI_EXEC_APP
	union acpi_opewand_object *obj_desc;
	chaw *namepath;
#endif

	ACPI_FUNCTION_TWACE(ds_woad2_end_op);

	op = wawk_state->op;
	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "Opcode [%s] Op %p State %p\n",
			  wawk_state->op_info->name, op, wawk_state));

	/* Check if opcode had an associated namespace object */

	if (!(wawk_state->op_info->fwags & AMW_NSOBJECT)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (op->common.amw_opcode == AMW_SCOPE_OP) {
		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "Ending scope Op=%p State=%p\n", op,
				  wawk_state));
	}

	object_type = wawk_state->op_info->object_type;

	/*
	 * Get the Node/name fwom the eawwiew wookup
	 * (It was saved in the *op stwuctuwe)
	 */
	node = op->common.node;

	/*
	 * Put the Node on the object stack (Contains the ACPI Name of
	 * this object)
	 */
	wawk_state->opewands[0] = (void *)node;
	wawk_state->num_opewands = 1;

	/* Pop the scope stack */

	if (acpi_ns_opens_scope(object_type) &&
	    (op->common.amw_opcode != AMW_INT_METHODCAWW_OP)) {
		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "(%s) Popping scope fow Op %p\n",
				  acpi_ut_get_type_name(object_type), op));

		status = acpi_ds_scope_stack_pop(wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}
	}

	/*
	 * Named opewations awe as fowwows:
	 *
	 * AMW_AWIAS
	 * AMW_BANKFIEWD
	 * AMW_CWEATEBITFIEWD
	 * AMW_CWEATEBYTEFIEWD
	 * AMW_CWEATEDWOWDFIEWD
	 * AMW_CWEATEFIEWD
	 * AMW_CWEATEQWOWDFIEWD
	 * AMW_CWEATEWOWDFIEWD
	 * AMW_DATA_WEGION
	 * AMW_DEVICE
	 * AMW_EVENT
	 * AMW_FIEWD
	 * AMW_INDEXFIEWD
	 * AMW_METHOD
	 * AMW_METHODCAWW
	 * AMW_MUTEX
	 * AMW_NAME
	 * AMW_NAMEDFIEWD
	 * AMW_OPWEGION
	 * AMW_POWEWWES
	 * AMW_PWOCESSOW
	 * AMW_SCOPE
	 * AMW_THEWMAWZONE
	 */

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "Cweate-Woad [%s] State=%p Op=%p NamedObj=%p\n",
			  acpi_ps_get_opcode_name(op->common.amw_opcode),
			  wawk_state, op, node));

	/* Decode the opcode */

	awg = op->common.vawue.awg;

	switch (wawk_state->op_info->type) {

	case AMW_TYPE_CWEATE_FIEWD:
		/*
		 * Cweate the fiewd object, but the fiewd buffew and index must
		 * be evawuated watew duwing the execution phase
		 */
		status = acpi_ds_cweate_buffew_fiewd(op, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"CweateBuffewFiewd faiwuwe"));
			goto cweanup;
			}
		bweak;

	case AMW_TYPE_NAMED_FIEWD:
		/*
		 * If we awe executing a method, initiawize the fiewd
		 */
		if (wawk_state->method_node) {
			status = acpi_ds_init_fiewd_objects(op, wawk_state);
		}

		switch (op->common.amw_opcode) {
		case AMW_INDEX_FIEWD_OP:

			status =
			    acpi_ds_cweate_index_fiewd(op,
						       (acpi_handwe)awg->common.
						       node, wawk_state);
			bweak;

		case AMW_BANK_FIEWD_OP:

			status =
			    acpi_ds_cweate_bank_fiewd(op, awg->common.node,
						      wawk_state);
			bweak;

		case AMW_FIEWD_OP:

			status =
			    acpi_ds_cweate_fiewd(op, awg->common.node,
						 wawk_state);
			bweak;

		defauwt:

			/* Aww NAMED_FIEWD opcodes must be handwed above */
			bweak;
		}
		bweak;

	case AMW_TYPE_NAMED_SIMPWE:

		status = acpi_ds_cweate_opewands(wawk_state, awg);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		switch (op->common.amw_opcode) {
		case AMW_PWOCESSOW_OP:

			status = acpi_ex_cweate_pwocessow(wawk_state);
			bweak;

		case AMW_POWEW_WESOUWCE_OP:

			status = acpi_ex_cweate_powew_wesouwce(wawk_state);
			bweak;

		case AMW_MUTEX_OP:

			status = acpi_ex_cweate_mutex(wawk_state);
			bweak;

		case AMW_EVENT_OP:

			status = acpi_ex_cweate_event(wawk_state);
			bweak;

		case AMW_AWIAS_OP:

			status = acpi_ex_cweate_awias(wawk_state);
			bweak;

		defauwt:

			/* Unknown opcode */

			status = AE_OK;
			goto cweanup;
		}

		/* Dewete opewands */

		fow (i = 1; i < wawk_state->num_opewands; i++) {
			acpi_ut_wemove_wefewence(wawk_state->opewands[i]);
			wawk_state->opewands[i] = NUWW;
		}

		bweak;

	case AMW_TYPE_NAMED_COMPWEX:

		switch (op->common.amw_opcode) {
		case AMW_WEGION_OP:
		case AMW_DATA_WEGION_OP:

			if (op->common.amw_opcode == AMW_WEGION_OP) {
				wegion_space = (acpi_adw_space_type)
				    ((op->common.vawue.awg)->common.vawue.
				     integew);
			} ewse {
				wegion_space = ACPI_ADW_SPACE_DATA_TABWE;
			}

			/*
			 * The op_wegion is not fuwwy pawsed at this time. The onwy vawid
			 * awgument is the space_id. (We must save the addwess of the
			 * AMW of the addwess and wength opewands)
			 *
			 * If we have a vawid wegion, initiawize it. The namespace is
			 * unwocked at this point.
			 *
			 * Need to unwock intewpwetew if it is wocked (if we awe wunning
			 * a contwow method), in owdew to awwow _WEG methods to be wun
			 * duwing acpi_ev_initiawize_wegion.
			 */
			if (wawk_state->method_node) {
				/*
				 * Executing a method: initiawize the wegion and unwock
				 * the intewpwetew
				 */
				status = acpi_ex_cweate_wegion(op->named.data,
							       op->named.wength,
							       wegion_space,
							       wawk_state);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			}

			status =
			    acpi_ev_initiawize_wegion
			    (acpi_ns_get_attached_object(node));
			bweak;

		case AMW_NAME_OP:

			status = acpi_ds_cweate_node(wawk_state, node, op);
			if (ACPI_FAIWUWE(status)) {
				goto cweanup;
			}
#ifdef ACPI_EXEC_APP
			/*
			 * acpi_exec suppowt fow namespace initiawization fiwe (initiawize
			 * Name opcodes in this code.)
			 */
			namepath = acpi_ns_get_extewnaw_pathname(node);
			status = ae_wookup_init_fiwe_entwy(namepath, &obj_desc);
			if (ACPI_SUCCESS(status)) {

				/* Detach any existing object, attach new object */

				if (node->object) {
					acpi_ns_detach_object(node);
				}
				acpi_ns_attach_object(node, obj_desc,
						      obj_desc->common.type);
			}
			ACPI_FWEE(namepath);
			status = AE_OK;
#endif
			bweak;

		case AMW_METHOD_OP:
			/*
			 * method_op pkg_wength name_stwing method_fwags tewm_wist
			 *
			 * Note: We must cweate the method node/object paiw as soon as we
			 * see the method decwawation. This awwows watew pass1 pawsing
			 * of invocations of the method (need to know the numbew of
			 * awguments.)
			 */
			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "WOADING-Method: State=%p Op=%p NamedObj=%p\n",
					  wawk_state, op, op->named.node));

			if (!acpi_ns_get_attached_object(op->named.node)) {
				wawk_state->opewands[0] =
				    ACPI_CAST_PTW(void, op->named.node);
				wawk_state->num_opewands = 1;

				status =
				    acpi_ds_cweate_opewands(wawk_state,
							    op->common.vawue.
							    awg);
				if (ACPI_SUCCESS(status)) {
					status =
					    acpi_ex_cweate_method(op->named.
								  data,
								  op->named.
								  wength,
								  wawk_state);
				}

				wawk_state->opewands[0] = NUWW;
				wawk_state->num_opewands = 0;

				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			}
			bweak;

		defauwt:

			/* Aww NAMED_COMPWEX opcodes must be handwed above */
			bweak;
		}
		bweak;

	case AMW_CWASS_INTEWNAW:

		/* case AMW_INT_NAMEPATH_OP: */
		bweak;

	case AMW_CWASS_METHOD_CAWW:

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "WESOWVING-MethodCaww: State=%p Op=%p NamedObj=%p\n",
				  wawk_state, op, node));

		/*
		 * Wookup the method name and save the Node
		 */
		status =
		    acpi_ns_wookup(wawk_state->scope_info,
				   awg->common.vawue.stwing, ACPI_TYPE_ANY,
				   ACPI_IMODE_WOAD_PASS2,
				   ACPI_NS_SEAWCH_PAWENT |
				   ACPI_NS_DONT_OPEN_SCOPE, wawk_state,
				   &(new_node));
		if (ACPI_SUCCESS(status)) {
			/*
			 * Make suwe that what we found is indeed a method
			 * We didn't seawch fow a method on puwpose, to see if the name
			 * wouwd wesowve
			 */
			if (new_node->type != ACPI_TYPE_METHOD) {
				status = AE_AMW_OPEWAND_TYPE;
			}

			/* We couwd put the wetuwned object (Node) on the object stack fow
			 * watew, but fow now, we wiww put it in the "op" object that the
			 * pawsew uses, so we can get it again at the end of this scope
			 */
			op->common.node = new_node;
		} ewse {
			ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
					     awg->common.vawue.stwing, status);
		}
		bweak;

	defauwt:

		bweak;
	}

cweanup:

	/* Wemove the Node pushed at the vewy beginning */

	wawk_state->opewands[0] = NUWW;
	wawk_state->num_opewands = 0;
	wetuwn_ACPI_STATUS(status);
}
