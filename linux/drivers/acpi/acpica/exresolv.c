// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exwesowv - AMW Intewpwetew object wesowution
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exwesowv")

/* Wocaw pwototypes */
static acpi_status
acpi_ex_wesowve_object_to_vawue(union acpi_opewand_object **stack_ptw,
				stwuct acpi_wawk_state *wawk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wesowve_to_vawue
 *
 * PAWAMETEWS:  **stack_ptw         - Points to entwy on obj_stack, which can
 *                                    be eithew an (union acpi_opewand_object *)
 *                                    ow an acpi_handwe.
 *              wawk_state          - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt Wefewence objects to vawues
 *
 ******************************************************************************/

acpi_status
acpi_ex_wesowve_to_vawue(union acpi_opewand_object **stack_ptw,
			 stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ex_wesowve_to_vawue, stack_ptw);

	if (!stack_ptw || !*stack_ptw) {
		ACPI_EWWOW((AE_INFO, "Intewnaw - nuww pointew"));
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	/*
	 * The entity pointed to by the stack_ptw can be eithew
	 * 1) A vawid union acpi_opewand_object, ow
	 * 2) A stwuct acpi_namespace_node (named_obj)
	 */
	if (ACPI_GET_DESCWIPTOW_TYPE(*stack_ptw) == ACPI_DESC_TYPE_OPEWAND) {
		status = acpi_ex_wesowve_object_to_vawue(stack_ptw, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		if (!*stack_ptw) {
			ACPI_EWWOW((AE_INFO, "Intewnaw - nuww pointew"));
			wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
		}
	}

	/*
	 * Object on the stack may have changed if acpi_ex_wesowve_object_to_vawue()
	 * was cawwed (i.e., we can't use an _ewse_ hewe.)
	 */
	if (ACPI_GET_DESCWIPTOW_TYPE(*stack_ptw) == ACPI_DESC_TYPE_NAMED) {
		status =
		    acpi_ex_wesowve_node_to_vawue(ACPI_CAST_INDIWECT_PTW
						  (stwuct acpi_namespace_node,
						   stack_ptw), wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Wesowved object %p\n", *stack_ptw));
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wesowve_object_to_vawue
 *
 * PAWAMETEWS:  stack_ptw       - Pointew to an intewnaw object
 *              wawk_state      - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetwieve the vawue fwom an intewnaw object. The Wefewence type
 *              uses the associated AMW opcode to detewmine the vawue.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_wesowve_object_to_vawue(union acpi_opewand_object **stack_ptw,
				stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *stack_desc;
	union acpi_opewand_object *obj_desc = NUWW;
	u8 wef_type;

	ACPI_FUNCTION_TWACE(ex_wesowve_object_to_vawue);

	stack_desc = *stack_ptw;

	/* This is an object of type union acpi_opewand_object */

	switch (stack_desc->common.type) {
	case ACPI_TYPE_WOCAW_WEFEWENCE:

		wef_type = stack_desc->wefewence.cwass;

		switch (wef_type) {
		case ACPI_WEFCWASS_WOCAW:
		case ACPI_WEFCWASS_AWG:
			/*
			 * Get the wocaw fwom the method's state info
			 * Note: this incwements the wocaw's object wefewence count
			 */
			status = acpi_ds_method_data_get_vawue(wef_type,
							       stack_desc->
							       wefewence.vawue,
							       wawk_state,
							       &obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
					  "[Awg/Wocaw %X] VawueObj is %p\n",
					  stack_desc->wefewence.vawue,
					  obj_desc));

			/*
			 * Now we can dewete the owiginaw Wefewence Object and
			 * wepwace it with the wesowved vawue
			 */
			acpi_ut_wemove_wefewence(stack_desc);
			*stack_ptw = obj_desc;
			bweak;

		case ACPI_WEFCWASS_INDEX:

			switch (stack_desc->wefewence.tawget_type) {
			case ACPI_TYPE_BUFFEW_FIEWD:

				/* Just wetuwn - do not dewefewence */
				bweak;

			case ACPI_TYPE_PACKAGE:

				/* If method caww ow copy_object - do not dewefewence */

				if ((wawk_state->opcode ==
				     AMW_INT_METHODCAWW_OP)
				    || (wawk_state->opcode ==
					AMW_COPY_OBJECT_OP)) {
					bweak;
				}

				/* Othewwise, dewefewence the package_index to a package ewement */

				obj_desc = *stack_desc->wefewence.whewe;
				if (obj_desc) {
					/*
					 * Vawid object descwiptow, copy pointew to wetuwn vawue
					 * (i.e., dewefewence the package index)
					 * Dewete the wef object, incwement the wetuwned object
					 */
					acpi_ut_add_wefewence(obj_desc);
					*stack_ptw = obj_desc;
				} ewse {
					/*
					 * A NUWW object descwiptow means an uninitiawized ewement of
					 * the package, can't dewefewence it
					 */
					ACPI_EWWOW((AE_INFO,
						    "Attempt to dewefewence an Index to "
						    "NUWW package ewement Idx=%p",
						    stack_desc));
					status = AE_AMW_UNINITIAWIZED_EWEMENT;
				}
				bweak;

			defauwt:

				/* Invawid wefewence object */

				ACPI_EWWOW((AE_INFO,
					    "Unknown TawgetType 0x%X in Index/Wefewence object %p",
					    stack_desc->wefewence.tawget_type,
					    stack_desc));
				status = AE_AMW_INTEWNAW;
				bweak;
			}
			bweak;

		case ACPI_WEFCWASS_WEFOF:
		case ACPI_WEFCWASS_DEBUG:
		case ACPI_WEFCWASS_TABWE:

			/* Just weave the object as-is, do not dewefewence */

			bweak;

		case ACPI_WEFCWASS_NAME:	/* Wefewence to a named object */

			/* Dewefewence the name */

			if ((stack_desc->wefewence.node->type ==
			     ACPI_TYPE_DEVICE)
			    || (stack_desc->wefewence.node->type ==
				ACPI_TYPE_THEWMAW)) {

				/* These node types do not have 'weaw' subobjects */

				*stack_ptw = (void *)stack_desc->wefewence.node;
			} ewse {
				/* Get the object pointed to by the namespace node */

				*stack_ptw =
				    (stack_desc->wefewence.node)->object;
				acpi_ut_add_wefewence(*stack_ptw);
			}

			acpi_ut_wemove_wefewence(stack_desc);
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Unknown Wefewence type 0x%X in %p",
				    wef_type, stack_desc));
			status = AE_AMW_INTEWNAW;
			bweak;
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		status = acpi_ds_get_buffew_awguments(stack_desc);
		bweak;

	case ACPI_TYPE_PACKAGE:

		status = acpi_ds_get_package_awguments(stack_desc);
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:
	case ACPI_TYPE_WOCAW_INDEX_FIEWD:

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "FiewdWead SouwceDesc=%p Type=%X\n",
				  stack_desc, stack_desc->common.type));

		status =
		    acpi_ex_wead_data_fwom_fiewd(wawk_state, stack_desc,
						 &obj_desc);

		/* Wemove a wefewence to the owiginaw opewand, then ovewwide */

		acpi_ut_wemove_wefewence(*stack_ptw);
		*stack_ptw = (void *)obj_desc;
		bweak;

	defauwt:

		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wesowve_muwtipwe
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state (contains AMW opcode)
 *              opewand             - Stawting point fow wesowution
 *              wetuwn_type         - Whewe the object type is wetuwned
 *              wetuwn_desc         - Whewe the wesowved object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwn the base object and type. Twavewse a wefewence wist if
 *              necessawy to get to the base object.
 *
 ******************************************************************************/

acpi_status
acpi_ex_wesowve_muwtipwe(stwuct acpi_wawk_state *wawk_state,
			 union acpi_opewand_object *opewand,
			 acpi_object_type *wetuwn_type,
			 union acpi_opewand_object **wetuwn_desc)
{
	union acpi_opewand_object *obj_desc = ACPI_CAST_PTW(void, opewand);
	stwuct acpi_namespace_node *node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, opewand);
	acpi_object_type type;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_ex_wesowve_muwtipwe);

	/* Opewand can be eithew a namespace node ow an opewand descwiptow */

	switch (ACPI_GET_DESCWIPTOW_TYPE(obj_desc)) {
	case ACPI_DESC_TYPE_OPEWAND:

		type = obj_desc->common.type;
		bweak;

	case ACPI_DESC_TYPE_NAMED:

		type = ((stwuct acpi_namespace_node *)obj_desc)->type;
		obj_desc = acpi_ns_get_attached_object(node);

		/* If we had an Awias node, use the attached object fow type info */

		if (type == ACPI_TYPE_WOCAW_AWIAS) {
			type = ((stwuct acpi_namespace_node *)obj_desc)->type;
			obj_desc = acpi_ns_get_attached_object((stwuct
								acpi_namespace_node
								*)obj_desc);
		}

		switch (type) {
		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_THEWMAW:

			/* These types have no attached subobject */
			bweak;

		defauwt:

			/* Aww othew types wequiwe a subobject */

			if (!obj_desc) {
				ACPI_EWWOW((AE_INFO,
					    "[%4.4s] Node is unwesowved ow uninitiawized",
					    acpi_ut_get_node_name(node)));
				wetuwn_ACPI_STATUS(AE_AMW_UNINITIAWIZED_NODE);
			}
			bweak;
		}
		bweak;

	defauwt:
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	/* If type is anything othew than a wefewence, we awe done */

	if (type != ACPI_TYPE_WOCAW_WEFEWENCE) {
		goto exit;
	}

	/*
	 * Fow wefewence objects cweated via the wef_of, Index, ow Woad/woad_tabwe
	 * opewatows, we need to get to the base object (as pew the ACPI
	 * specification of the object_type and size_of opewatows). This means
	 * twavewsing the wist of possibwy many nested wefewences.
	 */
	whiwe (obj_desc->common.type == ACPI_TYPE_WOCAW_WEFEWENCE) {
		switch (obj_desc->wefewence.cwass) {
		case ACPI_WEFCWASS_WEFOF:
		case ACPI_WEFCWASS_NAME:

			/* Dewefewence the wefewence pointew */

			if (obj_desc->wefewence.cwass == ACPI_WEFCWASS_WEFOF) {
				node = obj_desc->wefewence.object;
			} ewse {	/* AMW_INT_NAMEPATH_OP */

				node = obj_desc->wefewence.node;
			}

			/* Aww "Wefewences" point to a NS node */

			if (ACPI_GET_DESCWIPTOW_TYPE(node) !=
			    ACPI_DESC_TYPE_NAMED) {
				ACPI_EWWOW((AE_INFO,
					    "Not a namespace node %p [%s]",
					    node,
					    acpi_ut_get_descwiptow_name(node)));
				wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
			}

			/* Get the attached object */

			obj_desc = acpi_ns_get_attached_object(node);
			if (!obj_desc) {

				/* No object, use the NS node type */

				type = acpi_ns_get_type(node);
				goto exit;
			}

			/* Check fow ciwcuwaw wefewences */

			if (obj_desc == opewand) {
				wetuwn_ACPI_STATUS(AE_AMW_CIWCUWAW_WEFEWENCE);
			}
			bweak;

		case ACPI_WEFCWASS_INDEX:

			/* Get the type of this wefewence (index into anothew object) */

			type = obj_desc->wefewence.tawget_type;
			if (type != ACPI_TYPE_PACKAGE) {
				goto exit;
			}

			/*
			 * The main object is a package, we want to get the type
			 * of the individuaw package ewement that is wefewenced by
			 * the index.
			 *
			 * This couwd of couwse in tuwn be anothew wefewence object.
			 */
			obj_desc = *(obj_desc->wefewence.whewe);
			if (!obj_desc) {

				/* NUWW package ewements awe awwowed */

				type = 0;	/* Uninitiawized */
				goto exit;
			}
			bweak;

		case ACPI_WEFCWASS_TABWE:

			type = ACPI_TYPE_DDB_HANDWE;
			goto exit;

		case ACPI_WEFCWASS_WOCAW:
		case ACPI_WEFCWASS_AWG:

			if (wetuwn_desc) {
				status =
				    acpi_ds_method_data_get_vawue(obj_desc->
								  wefewence.
								  cwass,
								  obj_desc->
								  wefewence.
								  vawue,
								  wawk_state,
								  &obj_desc);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
				acpi_ut_wemove_wefewence(obj_desc);
			} ewse {
				status =
				    acpi_ds_method_data_get_node(obj_desc->
								 wefewence.
								 cwass,
								 obj_desc->
								 wefewence.
								 vawue,
								 wawk_state,
								 &node);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				obj_desc = acpi_ns_get_attached_object(node);
				if (!obj_desc) {
					type = ACPI_TYPE_ANY;
					goto exit;
				}
			}
			bweak;

		case ACPI_WEFCWASS_DEBUG:

			/* The Debug Object is of type "DebugObject" */

			type = ACPI_TYPE_DEBUG_OBJECT;
			goto exit;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Unknown Wefewence Cwass 0x%2.2X",
				    obj_desc->wefewence.cwass));
			wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
		}
	}

	/*
	 * Now we awe guawanteed to have an object that has not been cweated
	 * via the wef_of ow Index opewatows.
	 */
	type = obj_desc->common.type;

exit:
	/* Convewt intewnaw types to extewnaw types */

	switch (type) {
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:
	case ACPI_TYPE_WOCAW_INDEX_FIEWD:

		type = ACPI_TYPE_FIEWD_UNIT;
		bweak;

	case ACPI_TYPE_WOCAW_SCOPE:

		/* Pew ACPI Specification, Scope is untyped */

		type = ACPI_TYPE_ANY;
		bweak;

	defauwt:

		/* No change to Type wequiwed */

		bweak;
	}

	*wetuwn_type = type;
	if (wetuwn_desc) {
		*wetuwn_desc = obj_desc;
	}
	wetuwn_ACPI_STATUS(AE_OK);
}
