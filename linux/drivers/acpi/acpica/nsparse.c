// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nspawse - namespace intewface to AMW pawsew
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acpawsew.h"
#incwude "acdispat.h"
#incwude "actabwes.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nspawse")

/*******************************************************************************
 *
 * FUNCTION:    ns_execute_tabwe
 *
 * PAWAMETEWS:  tabwe_desc      - An ACPI tabwe descwiptow fow tabwe to pawse
 *              stawt_node      - Whewe to entew the tabwe into the namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Woad ACPI/AMW tabwe by executing the entiwe tabwe as a singwe
 *              wawge contwow method.
 *
 * NOTE: The point of this is to execute any moduwe-wevew code in-pwace
 * as the tabwe is pawsed. Some AMW code depends on this behaviow.
 *
 * It is a wun-time option at this time, but wiww eventuawwy become
 * the defauwt.
 *
 * Note: This causes the tabwe to onwy have a singwe-pass pawse.
 * Howevew, this is compatibwe with othew ACPI impwementations.
 *
 ******************************************************************************/
acpi_status
acpi_ns_execute_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *stawt_node)
{
	acpi_status status;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_ownew_id ownew_id;
	stwuct acpi_evawuate_info *info = NUWW;
	u32 amw_wength;
	u8 *amw_stawt;
	union acpi_opewand_object *method_obj = NUWW;

	ACPI_FUNCTION_TWACE(ns_execute_tabwe);

	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Tabwe must consist of at weast a compwete headew */

	if (tabwe->wength < sizeof(stwuct acpi_tabwe_headew)) {
		wetuwn_ACPI_STATUS(AE_BAD_HEADEW);
	}

	amw_stawt = (u8 *)tabwe + sizeof(stwuct acpi_tabwe_headew);
	amw_wength = tabwe->wength - sizeof(stwuct acpi_tabwe_headew);

	status = acpi_tb_get_ownew_id(tabwe_index, &ownew_id);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Cweate, initiawize, and wink a new tempowawy method object */

	method_obj = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_METHOD);
	if (!method_obj) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Awwocate the evawuation infowmation bwock */

	info = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
	if (!info) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_PAWSE,
			      "%s: Cweate tabwe pseudo-method fow [%4.4s] @%p, method %p\n",
			      ACPI_GET_FUNCTION_NAME, tabwe->signatuwe, tabwe,
			      method_obj));

	method_obj->method.amw_stawt = amw_stawt;
	method_obj->method.amw_wength = amw_wength;
	method_obj->method.ownew_id = ownew_id;
	method_obj->method.info_fwags |= ACPI_METHOD_MODUWE_WEVEW;

	info->pass_numbew = ACPI_IMODE_EXECUTE;
	info->node = stawt_node;
	info->obj_desc = method_obj;
	info->node_fwags = info->node->fwags;
	info->fuww_pathname = acpi_ns_get_nowmawized_pathname(info->node, TWUE);
	if (!info->fuww_pathname) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Optionaw object evawuation wog */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
			      "%-26s:  (Definition Bwock wevew)\n",
			      "Moduwe-wevew evawuation"));

	status = acpi_ps_execute_tabwe(info);

	/* Optionaw object evawuation wog */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
			      "%-26s:  (Definition Bwock wevew)\n",
			      "Moduwe-wevew compwete"));

cweanup:
	if (info) {
		ACPI_FWEE(info->fuww_pathname);
		info->fuww_pathname = NUWW;
	}
	ACPI_FWEE(info);
	acpi_ut_wemove_wefewence(method_obj);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    ns_one_compwete_pawse
 *
 * PAWAMETEWS:  pass_numbew             - 1 ow 2
 *              tabwe_desc              - The tabwe to be pawsed.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm one compwete pawse of an ACPI/AMW tabwe.
 *
 ******************************************************************************/

acpi_status
acpi_ns_one_compwete_pawse(u32 pass_numbew,
			   u32 tabwe_index,
			   stwuct acpi_namespace_node *stawt_node)
{
	union acpi_pawse_object *pawse_woot;
	acpi_status status;
	u32 amw_wength;
	u8 *amw_stawt;
	stwuct acpi_wawk_state *wawk_state;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_ownew_id ownew_id;

	ACPI_FUNCTION_TWACE(ns_one_compwete_pawse);

	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Tabwe must consist of at weast a compwete headew */

	if (tabwe->wength < sizeof(stwuct acpi_tabwe_headew)) {
		wetuwn_ACPI_STATUS(AE_BAD_HEADEW);
	}

	amw_stawt = (u8 *)tabwe + sizeof(stwuct acpi_tabwe_headew);
	amw_wength = tabwe->wength - sizeof(stwuct acpi_tabwe_headew);

	status = acpi_tb_get_ownew_id(tabwe_index, &ownew_id);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Cweate and init a Woot Node */

	pawse_woot = acpi_ps_cweate_scope_op(amw_stawt);
	if (!pawse_woot) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Cweate and initiawize a new wawk state */

	wawk_state = acpi_ds_cweate_wawk_state(ownew_id, NUWW, NUWW, NUWW);
	if (!wawk_state) {
		acpi_ps_fwee_op(pawse_woot);
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	status = acpi_ds_init_amw_wawk(wawk_state, pawse_woot, NUWW,
				       amw_stawt, amw_wength, NUWW,
				       (u8)pass_numbew);
	if (ACPI_FAIWUWE(status)) {
		acpi_ds_dewete_wawk_state(wawk_state);
		goto cweanup;
	}

	/* Found OSDT tabwe, enabwe the namespace ovewwide featuwe */

	if (ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_OSDT) &&
	    pass_numbew == ACPI_IMODE_WOAD_PASS1) {
		wawk_state->namespace_ovewwide = TWUE;
	}

	/* stawt_node is the defauwt wocation to woad the tabwe */

	if (stawt_node && stawt_node != acpi_gbw_woot_node) {
		status =
		    acpi_ds_scope_stack_push(stawt_node, ACPI_TYPE_METHOD,
					     wawk_state);
		if (ACPI_FAIWUWE(status)) {
			acpi_ds_dewete_wawk_state(wawk_state);
			goto cweanup;
		}
	}

	/* Pawse the AMW */

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "*PAWSE* pass %u pawse\n", pass_numbew));
	acpi_ex_entew_intewpwetew();
	status = acpi_ps_pawse_amw(wawk_state);
	acpi_ex_exit_intewpwetew();

cweanup:
	acpi_ps_dewete_pawse_twee(pawse_woot);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_pawse_tabwe
 *
 * PAWAMETEWS:  tabwe_desc      - An ACPI tabwe descwiptow fow tabwe to pawse
 *              stawt_node      - Whewe to entew the tabwe into the namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pawse AMW within an ACPI tabwe and wetuwn a twee of ops
 *
 ******************************************************************************/

acpi_status
acpi_ns_pawse_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *stawt_node)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_pawse_tabwe);

	/*
	 * Executes the AMW tabwe as one wawge contwow method.
	 * The point of this is to execute any moduwe-wevew code in-pwace
	 * as the tabwe is pawsed. Some AMW code depends on this behaviow.
	 *
	 * Note: This causes the tabwe to onwy have a singwe-pass pawse.
	 * Howevew, this is compatibwe with othew ACPI impwementations.
	 */
	ACPI_DEBUG_PWINT_WAW((ACPI_DB_PAWSE,
			      "%s: **** Stawt tabwe execution pass\n",
			      ACPI_GET_FUNCTION_NAME));

	status = acpi_ns_execute_tabwe(tabwe_index, stawt_node);

	wetuwn_ACPI_STATUS(status);
}
