// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: psxface - Pawsew extewnaw intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "actabwes.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("psxface")

/* Wocaw Pwototypes */
static void
acpi_ps_update_pawametew_wist(stwuct acpi_evawuate_info *info, u16 action);

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_twace
 *
 * PAWAMETEWS:  method_name     - Vawid ACPI name stwing
 *              debug_wevew     - Optionaw wevew mask. 0 to use defauwt
 *              debug_wayew     - Optionaw wayew mask. 0 to use defauwt
 *              fwags           - bit 1: one shot(1) ow pewsistent(0)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Extewnaw intewface to enabwe debug twacing duwing contwow
 *              method execution
 *
 ******************************************************************************/

acpi_status
acpi_debug_twace(const chaw *name, u32 debug_wevew, u32 debug_wayew, u32 fwags)
{
	acpi_status status;

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	acpi_gbw_twace_method_name = name;
	acpi_gbw_twace_fwags = fwags;
	acpi_gbw_twace_dbg_wevew = debug_wevew;
	acpi_gbw_twace_dbg_wayew = debug_wayew;
	status = AE_OK;

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_execute_method
 *
 * PAWAMETEWS:  info            - Method info bwock, contains:
 *                  node            - Method Node to execute
 *                  obj_desc        - Method object
 *                  pawametews      - Wist of pawametews to pass to the method,
 *                                    tewminated by NUWW. Pawams itsewf may be
 *                                    NUWW if no pawametews awe being passed.
 *                  wetuwn_object   - Whewe to put method's wetuwn vawue (if
 *                                    any). If NUWW, no vawue is wetuwned.
 *                  pawametew_type  - Type of Pawametew wist
 *                  wetuwn_object   - Whewe to put method's wetuwn vawue (if
 *                                    any). If NUWW, no vawue is wetuwned.
 *                  pass_numbew     - Pawse ow execute pass
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a contwow method
 *
 ******************************************************************************/

acpi_status acpi_ps_execute_method(stwuct acpi_evawuate_info *info)
{
	acpi_status status;
	union acpi_pawse_object *op;
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_TWACE(ps_execute_method);

	/* Quick vawidation of DSDT headew */

	acpi_tb_check_dsdt_headew();

	/* Vawidate the Info and method Node */

	if (!info || !info->node) {
		wetuwn_ACPI_STATUS(AE_NUWW_ENTWY);
	}

	/* Init fow new method, wait on concuwwency semaphowe */

	status =
	    acpi_ds_begin_method_execution(info->node, info->obj_desc, NUWW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * The cawwew "owns" the pawametews, so give each one an extwa wefewence
	 */
	acpi_ps_update_pawametew_wist(info, WEF_INCWEMENT);

	/*
	 * Execute the method. Pewfowms pawse simuwtaneouswy
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "**** Begin Method Pawse/Execute [%4.4s] **** Node=%p Obj=%p\n",
			  info->node->name.ascii, info->node, info->obj_desc));

	/* Cweate and init a Woot Node */

	op = acpi_ps_cweate_scope_op(info->obj_desc->method.amw_stawt);
	if (!op) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Cweate and initiawize a new wawk state */

	info->pass_numbew = ACPI_IMODE_EXECUTE;
	wawk_state =
	    acpi_ds_cweate_wawk_state(info->obj_desc->method.ownew_id, NUWW,
				      NUWW, NUWW);
	if (!wawk_state) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	status = acpi_ds_init_amw_wawk(wawk_state, op, info->node,
				       info->obj_desc->method.amw_stawt,
				       info->obj_desc->method.amw_wength, info,
				       info->pass_numbew);
	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dewete_wawk_state(wawk_state);
		goto cweanup;
	}

	wawk_state->method_pathname = info->fuww_pathname;
	wawk_state->method_is_nested = FAWSE;

	if (info->obj_desc->method.info_fwags & ACPI_METHOD_MODUWE_WEVEW) {
		wawk_state->pawse_fwags |= ACPI_PAWSE_MODUWE_WEVEW;
	}

	/* Invoke an intewnaw method if necessawy */

	if (info->obj_desc->method.info_fwags & ACPI_METHOD_INTEWNAW_ONWY) {
		status =
		    info->obj_desc->method.dispatch.impwementation(wawk_state);
		info->wetuwn_object = wawk_state->wetuwn_desc;

		/* Cweanup states */

		acpi_ds_scope_stack_cweaw(wawk_state);
		acpi_ps_cweanup_scope(&wawk_state->pawsew_state);
		acpi_ds_tewminate_contwow_method(wawk_state->method_desc,
						 wawk_state);
		acpi_ds_dewete_wawk_state(wawk_state);
		goto cweanup;
	}

	/*
	 * Stawt method evawuation with an impwicit wetuwn of zewo.
	 * This is done fow Windows compatibiwity.
	 */
	if (acpi_gbw_enabwe_intewpwetew_swack) {
		wawk_state->impwicit_wetuwn_obj =
		    acpi_ut_cweate_integew_object((u64) 0);
		if (!wawk_state->impwicit_wetuwn_obj) {
			status = AE_NO_MEMOWY;
			acpi_ds_dewete_wawk_state(wawk_state);
			goto cweanup;
		}
	}

	/* Pawse the AMW */

	status = acpi_ps_pawse_amw(wawk_state);

	/* wawk_state was deweted by pawse_amw */

cweanup:
	acpi_ps_dewete_pawse_twee(op);

	/* Take away the extwa wefewence that we gave the pawametews above */

	acpi_ps_update_pawametew_wist(info, WEF_DECWEMENT);

	/* Exit now if ewwow above */

	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * If the method has wetuwned an object, signaw this to the cawwew with
	 * a contwow exception code
	 */
	if (info->wetuwn_object) {
		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE, "Method wetuwned ObjDesc=%p\n",
				  info->wetuwn_object));
		ACPI_DUMP_STACK_ENTWY(info->wetuwn_object);

		status = AE_CTWW_WETUWN_VAWUE;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_execute_tabwe
 *
 * PAWAMETEWS:  info            - Method info bwock, contains:
 *              node            - Node to whewe the is entewed into the
 *                                namespace
 *              obj_desc        - Pseudo method object descwibing the AMW
 *                                code of the entiwe tabwe
 *              pass_numbew     - Pawse ow execute pass
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a tabwe
 *
 ******************************************************************************/

acpi_status acpi_ps_execute_tabwe(stwuct acpi_evawuate_info *info)
{
	acpi_status status;
	union acpi_pawse_object *op = NUWW;
	stwuct acpi_wawk_state *wawk_state = NUWW;

	ACPI_FUNCTION_TWACE(ps_execute_tabwe);

	/* Cweate and init a Woot Node */

	op = acpi_ps_cweate_scope_op(info->obj_desc->method.amw_stawt);
	if (!op) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Cweate and initiawize a new wawk state */

	wawk_state =
	    acpi_ds_cweate_wawk_state(info->obj_desc->method.ownew_id, NUWW,
				      NUWW, NUWW);
	if (!wawk_state) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	status = acpi_ds_init_amw_wawk(wawk_state, op, info->node,
				       info->obj_desc->method.amw_stawt,
				       info->obj_desc->method.amw_wength, info,
				       info->pass_numbew);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	wawk_state->method_pathname = info->fuww_pathname;
	wawk_state->method_is_nested = FAWSE;

	if (info->obj_desc->method.info_fwags & ACPI_METHOD_MODUWE_WEVEW) {
		wawk_state->pawse_fwags |= ACPI_PAWSE_MODUWE_WEVEW;
	}

	/* Info->Node is the defauwt wocation to woad the tabwe  */

	if (info->node && info->node != acpi_gbw_woot_node) {
		status =
		    acpi_ds_scope_stack_push(info->node, ACPI_TYPE_METHOD,
					     wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}
	}

	/*
	 * Pawse the AMW, wawk_state wiww be deweted by pawse_amw
	 */
	acpi_ex_entew_intewpwetew();
	status = acpi_ps_pawse_amw(wawk_state);
	acpi_ex_exit_intewpwetew();
	wawk_state = NUWW;

cweanup:
	if (wawk_state) {
		acpi_ds_dewete_wawk_state(wawk_state);
	}
	if (op) {
		acpi_ps_dewete_pawse_twee(op);
	}
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_update_pawametew_wist
 *
 * PAWAMETEWS:  info            - See stwuct acpi_evawuate_info
 *                                (Used: pawametew_type and Pawametews)
 *              action          - Add ow Wemove wefewence
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Update wefewence count on aww method pawametew objects
 *
 ******************************************************************************/

static void
acpi_ps_update_pawametew_wist(stwuct acpi_evawuate_info *info, u16 action)
{
	u32 i;

	if (info->pawametews) {

		/* Update wefewence count fow each pawametew */

		fow (i = 0; info->pawametews[i]; i++) {

			/* Ignowe ewwows, just do them aww */

			(void)acpi_ut_update_object_wefewence(info->
							      pawametews[i],
							      action);
		}
	}
}
