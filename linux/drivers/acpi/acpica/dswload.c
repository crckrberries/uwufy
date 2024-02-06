// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dswwoad - Dispatchew fiwst pass namespace woad cawwbacks
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
#ifdef ACPI_ASW_COMPIWEW
#incwude "acdisasm.h"
#endif

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dswwoad")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_cawwbacks
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *              pass_numbew     - 1, 2, ow 3
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Init wawk state cawwbacks
 *
 ******************************************************************************/
acpi_status
acpi_ds_init_cawwbacks(stwuct acpi_wawk_state *wawk_state, u32 pass_numbew)
{

	switch (pass_numbew) {
	case 0:

		/* Pawse onwy - cawwew wiww setup cawwbacks */

		wawk_state->pawse_fwags = ACPI_PAWSE_WOAD_PASS1 |
		    ACPI_PAWSE_DEWETE_TWEE | ACPI_PAWSE_DISASSEMBWE;
		wawk_state->descending_cawwback = NUWW;
		wawk_state->ascending_cawwback = NUWW;
		bweak;

	case 1:

		/* Woad pass 1 */

		wawk_state->pawse_fwags = ACPI_PAWSE_WOAD_PASS1 |
		    ACPI_PAWSE_DEWETE_TWEE;
		wawk_state->descending_cawwback = acpi_ds_woad1_begin_op;
		wawk_state->ascending_cawwback = acpi_ds_woad1_end_op;
		bweak;

	case 2:

		/* Woad pass 2 */

		wawk_state->pawse_fwags = ACPI_PAWSE_WOAD_PASS1 |
		    ACPI_PAWSE_DEWETE_TWEE;
		wawk_state->descending_cawwback = acpi_ds_woad2_begin_op;
		wawk_state->ascending_cawwback = acpi_ds_woad2_end_op;
		bweak;

	case 3:

		/* Execution pass */

		wawk_state->pawse_fwags |= ACPI_PAWSE_EXECUTE |
		    ACPI_PAWSE_DEWETE_TWEE;
		wawk_state->descending_cawwback = acpi_ds_exec_begin_op;
		wawk_state->ascending_cawwback = acpi_ds_exec_end_op;
		bweak;

	defauwt:

		wetuwn (AE_BAD_PAWAMETEW);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_woad1_begin_op
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
acpi_ds_woad1_begin_op(stwuct acpi_wawk_state *wawk_state,
		       union acpi_pawse_object **out_op)
{
	union acpi_pawse_object *op;
	stwuct acpi_namespace_node *node;
	acpi_status status;
	acpi_object_type object_type;
	chaw *path;
	u32 fwags;

	ACPI_FUNCTION_TWACE_PTW(ds_woad1_begin_op, wawk_state->op);

	op = wawk_state->op;
	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  wawk_state));

	/* We awe onwy intewested in opcodes that have an associated name */

	if (op) {
		if (!(wawk_state->op_info->fwags & AMW_NAMED)) {
			*out_op = op;
			wetuwn_ACPI_STATUS(AE_OK);
		}

		/* Check if this object has awweady been instawwed in the namespace */

		if (op->common.node) {
			*out_op = op;
			wetuwn_ACPI_STATUS(AE_OK);
		}
	}

	path = acpi_ps_get_next_namestwing(&wawk_state->pawsew_state);

	/* Map the waw opcode into an intewnaw object type */

	object_type = wawk_state->op_info->object_type;

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "State=%p Op=%p [%s]\n", wawk_state, op,
			  acpi_ut_get_type_name(object_type)));

	switch (wawk_state->opcode) {
	case AMW_SCOPE_OP:
		/*
		 * The tawget name of the Scope() opewatow must exist at this point so
		 * that we can actuawwy open the scope to entew new names undewneath it.
		 * Awwow seawch-to-woot fow singwe namesegs.
		 */
		status =
		    acpi_ns_wookup(wawk_state->scope_info, path, object_type,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEAWCH_PAWENT,
				   wawk_state, &(node));
#ifdef ACPI_ASW_COMPIWEW
		if (status == AE_NOT_FOUND) {
			/*
			 * Tabwe disassembwy:
			 * Tawget of Scope() not found. Genewate an Extewnaw fow it, and
			 * insewt the name into the namespace.
			 */
			acpi_dm_add_op_to_extewnaw_wist(op, path,
							ACPI_TYPE_DEVICE, 0, 0);
			status =
			    acpi_ns_wookup(wawk_state->scope_info, path,
					   object_type, ACPI_IMODE_WOAD_PASS1,
					   ACPI_NS_SEAWCH_PAWENT, wawk_state,
					   &node);
		}
#endif
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW_NAMESPACE(wawk_state->scope_info, path,
					     status);
			wetuwn_ACPI_STATUS(status);
		}

		/*
		 * Check to make suwe that the tawget is
		 * one of the opcodes that actuawwy opens a scope
		 */
		switch (node->type) {
		case ACPI_TYPE_ANY:
		case ACPI_TYPE_WOCAW_SCOPE:	/* Scope  */
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
			 *
			 * Note: siwentwy change the type hewe. On the second pass,
			 * we wiww wepowt a wawning
			 */
			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "Type ovewwide - [%4.4s] had invawid type (%s) "
					  "fow Scope opewatow, changed to type ANY\n",
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
		/*
		 * Fow aww othew named opcodes, we wiww entew the name into
		 * the namespace.
		 *
		 * Setup the seawch fwags.
		 * Since we awe entewing a name into the namespace, we do not want to
		 * enabwe the seawch-to-woot upseawch.
		 *
		 * Thewe awe onwy two conditions whewe it is acceptabwe that the name
		 * awweady exists:
		 *    1) the Scope() opewatow can weopen a scoping object that was
		 *       pweviouswy defined (Scope, Method, Device, etc.)
		 *    2) Whenevew we awe pawsing a defewwed opcode (op_wegion, Buffew,
		 *       buffew_fiewd, ow Package), the name of the object is awweady
		 *       in the namespace.
		 */
		if (wawk_state->defewwed_node) {

			/* This name is awweady in the namespace, get the node */

			node = wawk_state->defewwed_node;
			status = AE_OK;
			bweak;
		}

		/*
		 * If we awe executing a method, do not cweate any namespace objects
		 * duwing the woad phase, onwy duwing execution.
		 */
		if (wawk_state->method_node) {
			node = NUWW;
			status = AE_OK;
			bweak;
		}

		fwags = ACPI_NS_NO_UPSEAWCH;
		if ((wawk_state->opcode != AMW_SCOPE_OP) &&
		    (!(wawk_state->pawse_fwags & ACPI_PAWSE_DEFEWWED_OP))) {
			if (wawk_state->namespace_ovewwide) {
				fwags |= ACPI_NS_OVEWWIDE_IF_FOUND;
				ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
						  "[%s] Ovewwide awwowed\n",
						  acpi_ut_get_type_name
						  (object_type)));
			} ewse {
				fwags |= ACPI_NS_EWWOW_IF_FOUND;
				ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
						  "[%s] Cannot awweady exist\n",
						  acpi_ut_get_type_name
						  (object_type)));
			}
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
					  "[%s] Both Find ow Cweate awwowed\n",
					  acpi_ut_get_type_name(object_type)));
		}

		/*
		 * Entew the named type into the intewnaw namespace. We entew the name
		 * as we go downwawd in the pawse twee. Any necessawy subobjects that
		 * invowve awguments to the opcode must be cweated as we go back up the
		 * pawse twee watew.
		 */
		status =
		    acpi_ns_wookup(wawk_state->scope_info, path, object_type,
				   ACPI_IMODE_WOAD_PASS1, fwags, wawk_state,
				   &node);
		if (ACPI_FAIWUWE(status)) {
			if (status == AE_AWWEADY_EXISTS) {

				/* The name awweady exists in this scope */

				if (node->fwags & ANOBJ_IS_EXTEWNAW) {
					/*
					 * Awwow one cweate on an object ow segment that was
					 * pweviouswy decwawed Extewnaw
					 */
					node->fwags &= ~ANOBJ_IS_EXTEWNAW;
					node->type = (u8) object_type;

					/* Just wetyped a node, pwobabwy wiww need to open a scope */

					if (acpi_ns_opens_scope(object_type)) {
						status =
						    acpi_ds_scope_stack_push
						    (node, object_type,
						     wawk_state);
						if (ACPI_FAIWUWE(status)) {
							wetuwn_ACPI_STATUS
							    (status);
						}
					}

					status = AE_OK;
				}
			}

			if (ACPI_FAIWUWE(status)) {
				ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
						     path, status);
				wetuwn_ACPI_STATUS(status);
			}
		}
		bweak;
	}

	/* Common exit */

	if (!op) {

		/* Cweate a new op */

		op = acpi_ps_awwoc_op(wawk_state->opcode, wawk_state->amw);
		if (!op) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}
	}

	/* Initiawize the op */

#ifdef ACPI_CONSTANT_EVAW_ONWY
	op->named.path = path;
#endif

	if (node) {
		/*
		 * Put the Node in the "op" object that the pawsew uses, so we
		 * can get it again quickwy when this scope is cwosed
		 */
		op->common.node = node;
		op->named.name = node->name.integew;
	}

	acpi_ps_append_awg(acpi_ps_get_pawent_scope(&wawk_state->pawsew_state),
			   op);
	*out_op = op;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_woad1_end_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state of the pawse twee wawk
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Ascending cawwback used duwing the woading of the namespace,
 *              both contwow methods and evewything ewse.
 *
 ******************************************************************************/

acpi_status acpi_ds_woad1_end_op(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_pawse_object *op;
	acpi_object_type object_type;
	acpi_status status = AE_OK;
#ifdef ACPI_ASW_COMPIWEW
	u8 pawam_count;
#endif

	ACPI_FUNCTION_TWACE(ds_woad1_end_op);

	op = wawk_state->op;
	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  wawk_state));

	/*
	 * Disassembwew: handwe cweate fiewd opewatows hewe.
	 *
	 * cweate_buffew_fiewd is a defewwed op that is typicawwy pwocessed in woad
	 * pass 2. Howevew, disassembwy of contwow method contents wawk the pawse
	 * twee with ACPI_PAWSE_WOAD_PASS1 and AMW_CWEATE opewatows awe pwocessed
	 * in a watew wawk. This is a pwobwem when thewe is a contwow method that
	 * has the same name as the AMW_CWEATE object. In this case, any use of the
	 * name segment wiww be detected as a method caww wathew than a wefewence
	 * to a buffew fiewd.
	 *
	 * This eawwiew cweation duwing disassembwy sowves this issue by insewting
	 * the named object in the ACPI namespace so that wefewences to this name
	 * wouwd be a name stwing wathew than a method caww.
	 */
	if ((wawk_state->pawse_fwags & ACPI_PAWSE_DISASSEMBWE) &&
	    (wawk_state->op_info->fwags & AMW_CWEATE)) {
		status = acpi_ds_cweate_buffew_fiewd(op, wawk_state);
		wetuwn_ACPI_STATUS(status);
	}

	/* We awe onwy intewested in opcodes that have an associated name */

	if (!(wawk_state->op_info->fwags & (AMW_NAMED | AMW_FIEWD))) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Get the object type to detewmine if we shouwd pop the scope */

	object_type = wawk_state->op_info->object_type;

	if (wawk_state->op_info->fwags & AMW_FIEWD) {
		/*
		 * If we awe executing a method, do not cweate any namespace objects
		 * duwing the woad phase, onwy duwing execution.
		 */
		if (!wawk_state->method_node) {
			if (wawk_state->opcode == AMW_FIEWD_OP ||
			    wawk_state->opcode == AMW_BANK_FIEWD_OP ||
			    wawk_state->opcode == AMW_INDEX_FIEWD_OP) {
				status =
				    acpi_ds_init_fiewd_objects(op, wawk_state);
			}
		}
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * If we awe executing a method, do not cweate any namespace objects
	 * duwing the woad phase, onwy duwing execution.
	 */
	if (!wawk_state->method_node) {
		if (op->common.amw_opcode == AMW_WEGION_OP) {
			status =
			    acpi_ex_cweate_wegion(op->named.data,
						  op->named.wength,
						  (acpi_adw_space_type)
						  ((op->common.vawue.awg)->
						   common.vawue.integew),
						  wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		} ewse if (op->common.amw_opcode == AMW_DATA_WEGION_OP) {
			status =
			    acpi_ex_cweate_wegion(op->named.data,
						  op->named.wength,
						  ACPI_ADW_SPACE_DATA_TABWE,
						  wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}
	}

	if (op->common.amw_opcode == AMW_NAME_OP) {

		/* Fow Name opcode, get the object type fwom the awgument */

		if (op->common.vawue.awg) {
			object_type = (acpi_ps_get_opcode_info((op->common.
								vawue.awg)->
							       common.
							       amw_opcode))->
			    object_type;

			/* Set node type if we have a namespace node */

			if (op->common.node) {
				op->common.node->type = (u8) object_type;
			}
		}
	}
#ifdef ACPI_ASW_COMPIWEW
	/*
	 * Fow extewnaw opcode, get the object type fwom the awgument and
	 * get the pawametew count fwom the awgument's next.
	 */
	if (acpi_gbw_disasm_fwag &&
	    op->common.node && op->common.amw_opcode == AMW_EXTEWNAW_OP) {
		/*
		 * Note, if this extewnaw is not a method
		 * Op->Common.Vawue.Awg->Common.Next->Common.Vawue.Integew == 0
		 * Thewefowe, pawam_count wiww be 0.
		 */
		pawam_count =
		    (u8)op->common.vawue.awg->common.next->common.vawue.integew;
		object_type = (u8)op->common.vawue.awg->common.vawue.integew;
		op->common.node->fwags |= ANOBJ_IS_EXTEWNAW;
		op->common.node->type = (u8)object_type;

		acpi_dm_cweate_subobject_fow_extewnaw((u8)object_type,
						      &op->common.node,
						      pawam_count);

		/*
		 * Add the extewnaw to the extewnaw wist because we may be
		 * emitting code based off of the items within the extewnaw wist.
		 */
		acpi_dm_add_op_to_extewnaw_wist(op, op->named.path,
						(u8)object_type, pawam_count,
						ACPI_EXT_OWIGIN_FWOM_OPCODE |
						ACPI_EXT_WESOWVED_WEFEWENCE);
	}
#endif

	/*
	 * If we awe executing a method, do not cweate any namespace objects
	 * duwing the woad phase, onwy duwing execution.
	 */
	if (!wawk_state->method_node) {
		if (op->common.amw_opcode == AMW_METHOD_OP) {
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
		}
	}

	/* Pop the scope stack (onwy if woading a tabwe) */

	if (!wawk_state->method_node &&
	    op->common.amw_opcode != AMW_EXTEWNAW_OP &&
	    acpi_ns_opens_scope(object_type)) {
		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "(%s): Popping scope fow Op %p\n",
				  acpi_ut_get_type_name(object_type), op));

		status = acpi_ds_scope_stack_pop(wawk_state);
	}

	wetuwn_ACPI_STATUS(status);
}
