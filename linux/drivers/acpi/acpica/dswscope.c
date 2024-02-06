// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dswscope - Scope stack manipuwation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dswscope")

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_cweaw
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pop (and fwee) evewything on the scope stack except the
 *              woot scope object (which wemains at the stack top.)
 *
 ***************************************************************************/
void acpi_ds_scope_stack_cweaw(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *scope_info;

	ACPI_FUNCTION_NAME(ds_scope_stack_cweaw);

	whiwe (wawk_state->scope_info) {

		/* Pop a scope off the stack */

		scope_info = wawk_state->scope_info;
		wawk_state->scope_info = scope_info->scope.next;

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Popped object type (%s)\n",
				  acpi_ut_get_type_name(scope_info->common.
							vawue)));

		acpi_ut_dewete_genewic_state(scope_info);
	}
}

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_push
 *
 * PAWAMETEWS:  node            - Name to be made cuwwent
 *              type            - Type of fwame being pushed
 *              wawk_state      - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Push the cuwwent scope on the scope stack, and make the
 *              passed Node cuwwent.
 *
 ***************************************************************************/

acpi_status
acpi_ds_scope_stack_push(stwuct acpi_namespace_node *node,
			 acpi_object_type type,
			 stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *scope_info;
	union acpi_genewic_state *owd_scope_info;

	ACPI_FUNCTION_TWACE(ds_scope_stack_push);

	if (!node) {

		/* Invawid scope   */

		ACPI_EWWOW((AE_INFO, "Nuww scope pawametew"));
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Make suwe object type is vawid */

	if (!acpi_ut_vawid_object_type(type)) {
		ACPI_WAWNING((AE_INFO, "Invawid object type: 0x%X", type));
	}

	/* Awwocate a new scope object */

	scope_info = acpi_ut_cweate_genewic_state();
	if (!scope_info) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Init new scope object */

	scope_info->common.descwiptow_type = ACPI_DESC_TYPE_STATE_WSCOPE;
	scope_info->scope.node = node;
	scope_info->common.vawue = (u16) type;

	wawk_state->scope_depth++;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "[%.2d] Pushed scope ",
			  (u32) wawk_state->scope_depth));

	owd_scope_info = wawk_state->scope_info;
	if (owd_scope_info) {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC,
				      "[%4.4s] (%s)",
				      acpi_ut_get_node_name(owd_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(owd_scope_info->
							    common.vawue)));
	} ewse {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC, ACPI_NAMESPACE_WOOT));
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC,
			      ", New scope -> [%4.4s] (%s)\n",
			      acpi_ut_get_node_name(scope_info->scope.node),
			      acpi_ut_get_type_name(scope_info->common.vawue)));

	/* Push new scope object onto stack */

	acpi_ut_push_genewic_state(&wawk_state->scope_info, scope_info);
	wetuwn_ACPI_STATUS(AE_OK);
}

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_pop
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pop the scope stack once.
 *
 ***************************************************************************/

acpi_status acpi_ds_scope_stack_pop(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_genewic_state *scope_info;
	union acpi_genewic_state *new_scope_info;

	ACPI_FUNCTION_TWACE(ds_scope_stack_pop);

	/*
	 * Pop scope info object off the stack.
	 */
	scope_info = acpi_ut_pop_genewic_state(&wawk_state->scope_info);
	if (!scope_info) {
		wetuwn_ACPI_STATUS(AE_STACK_UNDEWFWOW);
	}

	wawk_state->scope_depth--;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "[%.2d] Popped scope [%4.4s] (%s), New scope -> ",
			  (u32) wawk_state->scope_depth,
			  acpi_ut_get_node_name(scope_info->scope.node),
			  acpi_ut_get_type_name(scope_info->common.vawue)));

	new_scope_info = wawk_state->scope_info;
	if (new_scope_info) {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC, "[%4.4s] (%s)\n",
				      acpi_ut_get_node_name(new_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(new_scope_info->
							    common.vawue)));
	} ewse {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC, "%s\n",
				      ACPI_NAMESPACE_WOOT));
	}

	acpi_ut_dewete_genewic_state(scope_info);
	wetuwn_ACPI_STATUS(AE_OK);
}
