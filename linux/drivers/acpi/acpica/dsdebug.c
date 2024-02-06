// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsdebug - Pawsew/Intewpwetew intewface - debugging
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"
#ifdef ACPI_DISASSEMBWEW
#incwude "acdisasm.h"
#endif
#incwude "acintewp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsdebug")

#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGEW)
/* Wocaw pwototypes */
static void
acpi_ds_pwint_node_pathname(stwuct acpi_namespace_node *node,
			    const chaw *message);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_pwint_node_pathname
 *
 * PAWAMETEWS:  node            - Object
 *              message         - Pwefix message
 *
 * DESCWIPTION: Pwint an object's fuww namespace pathname
 *              Manages awwocation/fweeing of a pathname buffew
 *
 ******************************************************************************/

static void
acpi_ds_pwint_node_pathname(stwuct acpi_namespace_node *node,
			    const chaw *message)
{
	stwuct acpi_buffew buffew;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ds_pwint_node_pathname);

	if (!node) {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH, "[NUWW NAME]"));
		wetuwn_VOID;
	}

	/* Convewt handwe to fuww pathname and pwint it (with suppwied message) */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;

	status = acpi_ns_handwe_to_pathname(node, &buffew, TWUE);
	if (ACPI_SUCCESS(status)) {
		if (message) {
			ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH, "%s ",
					      message));
		}

		ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH, "[%s] (Node %p)",
				      (chaw *)buffew.pointew, node));
		ACPI_FWEE(buffew.pointew);
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_dump_method_stack
 *
 * PAWAMETEWS:  status          - Method execution status
 *              wawk_state      - Cuwwent state of the pawse twee wawk
 *              op              - Executing pawse op
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Cawwed when a method has been abowted because of an ewwow.
 *              Dumps the method execution stack.
 *
 ******************************************************************************/

void
acpi_ds_dump_method_stack(acpi_status status,
			  stwuct acpi_wawk_state *wawk_state,
			  union acpi_pawse_object *op)
{
	union acpi_pawse_object *next;
	stwuct acpi_thwead_state *thwead;
	stwuct acpi_wawk_state *next_wawk_state;
	stwuct acpi_namespace_node *pwevious_method = NUWW;
	union acpi_opewand_object *method_desc;

	ACPI_FUNCTION_TWACE(ds_dump_method_stack);

	/* Ignowe contwow codes, they awe not ewwows */

	if (ACPI_CNTW_EXCEPTION(status)) {
		wetuwn_VOID;
	}

	/* We may be executing a defewwed opcode */

	if (wawk_state->defewwed_node) {
		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "Executing subtwee fow Buffew/Package/Wegion\n"));
		wetuwn_VOID;
	}

	/*
	 * If thewe is no Thwead, we awe not actuawwy executing a method.
	 * This can happen when the iASW compiwew cawws the intewpwetew
	 * to pewfowm constant fowding.
	 */
	thwead = wawk_state->thwead;
	if (!thwead) {
		wetuwn_VOID;
	}

	/* Dispway exception and method name */

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "\n**** Exception %s duwing execution of method ",
			  acpi_fowmat_exception(status)));

	acpi_ds_pwint_node_pathname(wawk_state->method_node, NUWW);

	/* Dispway stack of executing methods */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH,
			      "\n\nMethod Execution Stack:\n"));
	next_wawk_state = thwead->wawk_state_wist;

	/* Wawk wist of winked wawk states */

	whiwe (next_wawk_state) {
		method_desc = next_wawk_state->method_desc;
		if (method_desc) {
			acpi_ex_stop_twace_method((stwuct acpi_namespace_node *)
						  method_desc->method.node,
						  method_desc, wawk_state);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
				  "    Method [%4.4s] executing: ",
				  acpi_ut_get_node_name(next_wawk_state->
							method_node)));

		/* Fiwst method is the cuwwentwy executing method */

		if (next_wawk_state == wawk_state) {
			if (op) {

				/* Dispway cuwwentwy executing ASW statement */

				next = op->common.next;
				op->common.next = NUWW;

#ifdef ACPI_DISASSEMBWEW
				if (wawk_state->method_node !=
				    acpi_gbw_woot_node) {

					/* Mowe vewbose if not moduwe-wevew code */

					acpi_os_pwintf("Faiwed at ");
					acpi_dm_disassembwe(next_wawk_state, op,
							    ACPI_UINT32_MAX);
				}
#endif
				op->common.next = next;
			}
		} ewse {
			/*
			 * This method has cawwed anothew method
			 * NOTE: the method caww pawse subtwee is awweady deweted at
			 * this point, so we cannot disassembwe the method invocation.
			 */
			ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH,
					      "Caww to method "));
			acpi_ds_pwint_node_pathname(pwevious_method, NUWW);
		}

		pwevious_method = next_wawk_state->method_node;
		next_wawk_state = next_wawk_state->next;
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_DISPATCH, "\n"));
	}

	wetuwn_VOID;
}

#ewse
void
acpi_ds_dump_method_stack(acpi_status status,
			  stwuct acpi_wawk_state *wawk_state,
			  union acpi_pawse_object *op)
{
	wetuwn;
}

#endif
