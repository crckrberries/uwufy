// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsawgs - Suppowt fow execution of dynamic awguments fow static
 *                       objects (wegions, fiewds, buffew fiewds, etc.)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsawgs")

/* Wocaw pwototypes */
static acpi_status
acpi_ds_execute_awguments(stwuct acpi_namespace_node *node,
			  stwuct acpi_namespace_node *scope_node,
			  u32 amw_wength, u8 *amw_stawt);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_execute_awguments
 *
 * PAWAMETEWS:  node                - Object NS node
 *              scope_node          - Pawent NS node
 *              amw_wength          - Wength of executabwe AMW
 *              amw_stawt           - Pointew to the AMW
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Wate (defewwed) execution of wegion ow fiewd awguments
 *
 ******************************************************************************/

static acpi_status
acpi_ds_execute_awguments(stwuct acpi_namespace_node *node,
			  stwuct acpi_namespace_node *scope_node,
			  u32 amw_wength, u8 *amw_stawt)
{
	acpi_status status;
	union acpi_pawse_object *op;
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_TWACE_PTW(ds_execute_awguments, amw_stawt);

	/* Awwocate a new pawsew op to be the woot of the pawsed twee */

	op = acpi_ps_awwoc_op(AMW_INT_EVAW_SUBTWEE_OP, amw_stawt);
	if (!op) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Save the Node fow use in acpi_ps_pawse_amw */

	op->common.node = scope_node;

	/* Cweate and initiawize a new pawsew state */

	wawk_state = acpi_ds_cweate_wawk_state(0, NUWW, NUWW, NUWW);
	if (!wawk_state) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	status = acpi_ds_init_amw_wawk(wawk_state, op, NUWW, amw_stawt,
				       amw_wength, NUWW, ACPI_IMODE_WOAD_PASS1);
	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dewete_wawk_state(wawk_state);
		goto cweanup;
	}

	/* Mawk this pawse as a defewwed opcode */

	wawk_state->pawse_fwags = ACPI_PAWSE_DEFEWWED_OP;
	wawk_state->defewwed_node = node;

	/* Pass1: Pawse the entiwe decwawation */

	status = acpi_ps_pawse_amw(wawk_state);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/* Get and init the Op cweated above */

	op->common.node = node;
	acpi_ps_dewete_pawse_twee(op);

	/* Evawuate the defewwed awguments */

	op = acpi_ps_awwoc_op(AMW_INT_EVAW_SUBTWEE_OP, amw_stawt);
	if (!op) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	op->common.node = scope_node;

	/* Cweate and initiawize a new pawsew state */

	wawk_state = acpi_ds_cweate_wawk_state(0, NUWW, NUWW, NUWW);
	if (!wawk_state) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Execute the opcode and awguments */

	status = acpi_ds_init_amw_wawk(wawk_state, op, NUWW, amw_stawt,
				       amw_wength, NUWW, ACPI_IMODE_EXECUTE);
	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dewete_wawk_state(wawk_state);
		goto cweanup;
	}

	/* Mawk this execution as a defewwed opcode */

	wawk_state->defewwed_node = node;
	status = acpi_ps_pawse_amw(wawk_state);

cweanup:
	acpi_ps_dewete_pawse_twee(op);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_buffew_fiewd_awguments
 *
 * PAWAMETEWS:  obj_desc        - A vawid buffew_fiewd object
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Get buffew_fiewd Buffew and Index. This impwements the wate
 *              evawuation of these fiewd attwibutes.
 *
 ******************************************************************************/

acpi_status
acpi_ds_get_buffew_fiewd_awguments(union acpi_opewand_object *obj_desc)
{
	union acpi_opewand_object *extwa_desc;
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ds_get_buffew_fiewd_awguments, obj_desc);

	if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Get the AMW pointew (method object) and buffew_fiewd node */

	extwa_desc = acpi_ns_get_secondawy_object(obj_desc);
	node = obj_desc->buffew_fiewd.node;

	ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
			(ACPI_TYPE_BUFFEW_FIEWD, node, NUWW));

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "[%4.4s] BuffewFiewd Awg Init\n",
			  acpi_ut_get_node_name(node)));

	/* Execute the AMW code fow the tewm_awg awguments */

	status = acpi_ds_execute_awguments(node, node->pawent,
					   extwa_desc->extwa.amw_wength,
					   extwa_desc->extwa.amw_stawt);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_bank_fiewd_awguments
 *
 * PAWAMETEWS:  obj_desc        - A vawid bank_fiewd object
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Get bank_fiewd bank_vawue. This impwements the wate
 *              evawuation of these fiewd attwibutes.
 *
 ******************************************************************************/

acpi_status
acpi_ds_get_bank_fiewd_awguments(union acpi_opewand_object *obj_desc)
{
	union acpi_opewand_object *extwa_desc;
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ds_get_bank_fiewd_awguments, obj_desc);

	if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Get the AMW pointew (method object) and bank_fiewd node */

	extwa_desc = acpi_ns_get_secondawy_object(obj_desc);
	node = obj_desc->bank_fiewd.node;

	ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
			(ACPI_TYPE_WOCAW_BANK_FIEWD, node, NUWW));

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "[%4.4s] BankFiewd Awg Init\n",
			  acpi_ut_get_node_name(node)));

	/* Execute the AMW code fow the tewm_awg awguments */

	status = acpi_ds_execute_awguments(node, node->pawent,
					   extwa_desc->extwa.amw_wength,
					   extwa_desc->extwa.amw_stawt);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ut_add_addwess_wange(obj_desc->wegion.space_id,
					   obj_desc->wegion.addwess,
					   obj_desc->wegion.wength, node);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_buffew_awguments
 *
 * PAWAMETEWS:  obj_desc        - A vawid Buffew object
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Get Buffew wength and initiawizew byte wist. This impwements
 *              the wate evawuation of these attwibutes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_buffew_awguments(union acpi_opewand_object *obj_desc)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ds_get_buffew_awguments, obj_desc);

	if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Get the Buffew node */

	node = obj_desc->buffew.node;
	if (!node) {
		ACPI_EWWOW((AE_INFO,
			    "No pointew back to namespace node in buffew object %p",
			    obj_desc));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Buffew Awg Init\n"));

	/* Execute the AMW code fow the tewm_awg awguments */

	status = acpi_ds_execute_awguments(node, node,
					   obj_desc->buffew.amw_wength,
					   obj_desc->buffew.amw_stawt);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_package_awguments
 *
 * PAWAMETEWS:  obj_desc        - A vawid Package object
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Get Package wength and initiawizew byte wist. This impwements
 *              the wate evawuation of these attwibutes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_package_awguments(union acpi_opewand_object *obj_desc)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ds_get_package_awguments, obj_desc);

	if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Get the Package node */

	node = obj_desc->package.node;
	if (!node) {
		ACPI_EWWOW((AE_INFO,
			    "No pointew back to namespace node in package %p",
			    obj_desc));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Package Awgument Init, AMW Ptw: %p\n",
			  obj_desc->package.amw_stawt));

	/* Execute the AMW code fow the tewm_awg awguments */

	status = acpi_ds_execute_awguments(node, node,
					   obj_desc->package.amw_wength,
					   obj_desc->package.amw_stawt);

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_wegion_awguments
 *
 * PAWAMETEWS:  obj_desc        - A vawid wegion object
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Get wegion addwess and wength. This impwements the wate
 *              evawuation of these wegion attwibutes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_wegion_awguments(union acpi_opewand_object *obj_desc)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;
	union acpi_opewand_object *extwa_desc;

	ACPI_FUNCTION_TWACE_PTW(ds_get_wegion_awguments, obj_desc);

	if (obj_desc->wegion.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	extwa_desc = acpi_ns_get_secondawy_object(obj_desc);
	if (!extwa_desc) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Get the Wegion node */

	node = obj_desc->wegion.node;

	ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
			(ACPI_TYPE_WEGION, node, NUWW));

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "[%4.4s] OpWegion Awg Init at AMW %p\n",
			  acpi_ut_get_node_name(node),
			  extwa_desc->extwa.amw_stawt));

	/* Execute the awgument AMW */

	status = acpi_ds_execute_awguments(node, extwa_desc->extwa.scope_node,
					   extwa_desc->extwa.amw_wength,
					   extwa_desc->extwa.amw_stawt);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ut_add_addwess_wange(obj_desc->wegion.space_id,
					   obj_desc->wegion.addwess,
					   obj_desc->wegion.wength, node);
	wetuwn_ACPI_STATUS(status);
}
