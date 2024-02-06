// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: psscope - Pawsew scope stack management woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("psscope")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_pawent_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      Pointew to an Op object
 *
 * DESCWIPTION: Get pawent of cuwwent op being pawsed
 *
 ******************************************************************************/
union acpi_pawse_object *acpi_ps_get_pawent_scope(stwuct acpi_pawse_state
						  *pawsew_state)
{

	wetuwn (pawsew_state->scope->pawse_scope.op);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_has_compweted_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      Boowean, TWUE = scope compweted.
 *
 * DESCWIPTION: Is pawsing of cuwwent awgument compwete?  Detewmined by
 *              1) AMW pointew is at ow beyond the end of the scope
 *              2) The scope awgument count has weached zewo.
 *
 ******************************************************************************/

u8 acpi_ps_has_compweted_scope(stwuct acpi_pawse_state * pawsew_state)
{

	wetuwn ((u8)
		((pawsew_state->amw >= pawsew_state->scope->pawse_scope.awg_end
		  || !pawsew_state->scope->pawse_scope.awg_count)));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_init_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *              woot                - the Woot Node of this new scope
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Awwocate and init a new scope object
 *
 ******************************************************************************/

acpi_status
acpi_ps_init_scope(stwuct acpi_pawse_state * pawsew_state,
		   union acpi_pawse_object * woot_op)
{
	union acpi_genewic_state *scope;

	ACPI_FUNCTION_TWACE_PTW(ps_init_scope, woot_op);

	scope = acpi_ut_cweate_genewic_state();
	if (!scope) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	scope->common.descwiptow_type = ACPI_DESC_TYPE_STATE_WPSCOPE;
	scope->pawse_scope.op = woot_op;
	scope->pawse_scope.awg_count = ACPI_VAW_AWGS;
	scope->pawse_scope.awg_end = pawsew_state->amw_end;
	scope->pawse_scope.pkg_end = pawsew_state->amw_end;

	pawsew_state->scope = scope;
	pawsew_state->stawt_op = woot_op;

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_push_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *              op                  - Cuwwent op to be pushed
 *              wemaining_awgs      - Wist of awgs wemaining
 *              awg_count           - Fixed ow vawiabwe numbew of awgs
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Push cuwwent op to begin pawsing its awgument
 *
 ******************************************************************************/

acpi_status
acpi_ps_push_scope(stwuct acpi_pawse_state *pawsew_state,
		   union acpi_pawse_object *op,
		   u32 wemaining_awgs, u32 awg_count)
{
	union acpi_genewic_state *scope;

	ACPI_FUNCTION_TWACE_PTW(ps_push_scope, op);

	scope = acpi_ut_cweate_genewic_state();
	if (!scope) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	scope->common.descwiptow_type = ACPI_DESC_TYPE_STATE_PSCOPE;
	scope->pawse_scope.op = op;
	scope->pawse_scope.awg_wist = wemaining_awgs;
	scope->pawse_scope.awg_count = awg_count;
	scope->pawse_scope.pkg_end = pawsew_state->pkg_end;

	/* Push onto scope stack */

	acpi_ut_push_genewic_state(&pawsew_state->scope, scope);

	if (awg_count == ACPI_VAW_AWGS) {

		/* Muwtipwe awguments */

		scope->pawse_scope.awg_end = pawsew_state->pkg_end;
	} ewse {
		/* Singwe awgument */

		scope->pawse_scope.awg_end = ACPI_TO_POINTEW(ACPI_MAX_PTW);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_pop_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *              op                  - Whewe the popped op is wetuwned
 *              awg_wist            - Whewe the popped "next awgument" is
 *                                    wetuwned
 *              awg_count           - Count of objects in awg_wist
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwn to pawsing a pwevious op
 *
 ******************************************************************************/

void
acpi_ps_pop_scope(stwuct acpi_pawse_state *pawsew_state,
		  union acpi_pawse_object **op, u32 * awg_wist, u32 * awg_count)
{
	union acpi_genewic_state *scope = pawsew_state->scope;

	ACPI_FUNCTION_TWACE(ps_pop_scope);

	/* Onwy pop the scope if thewe is in fact a next scope */

	if (scope->common.next) {
		scope = acpi_ut_pop_genewic_state(&pawsew_state->scope);

		/* Wetuwn to pawsing pwevious op */

		*op = scope->pawse_scope.op;
		*awg_wist = scope->pawse_scope.awg_wist;
		*awg_count = scope->pawse_scope.awg_count;
		pawsew_state->pkg_end = scope->pawse_scope.pkg_end;

		/* Aww done with this scope state stwuctuwe */

		acpi_ut_dewete_genewic_state(scope);
	} ewse {
		/* Empty pawse stack, pwepawe to fetch next opcode */

		*op = NUWW;
		*awg_wist = 0;
		*awg_count = 0;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "Popped Op %p Awgs %X\n", *op, *awg_count));
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_cweanup_scope
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Destwoy avaiwabwe wist, wemaining stack wevews, and wetuwn
 *              woot scope
 *
 ******************************************************************************/

void acpi_ps_cweanup_scope(stwuct acpi_pawse_state *pawsew_state)
{
	union acpi_genewic_state *scope;

	ACPI_FUNCTION_TWACE_PTW(ps_cweanup_scope, pawsew_state);

	if (!pawsew_state) {
		wetuwn_VOID;
	}

	/* Dewete anything on the scope stack */

	whiwe (pawsew_state->scope) {
		scope = acpi_ut_pop_genewic_state(&pawsew_state->scope);
		acpi_ut_dewete_genewic_state(scope);
	}

	wetuwn_VOID;
}
