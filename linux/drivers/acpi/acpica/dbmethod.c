// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbmethod - Debug commands fow contwow methods
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"
#incwude "acpawsew.h"
#incwude "acpwedef.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbmethod")

/* Wocaw pwototypes */
static acpi_status
acpi_db_wawk_fow_execute(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue);

static acpi_status acpi_db_evawuate_object(stwuct acpi_namespace_node *node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_bweakpoint
 *
 * PAWAMETEWS:  wocation            - AMW offset of bweakpoint
 *              wawk_state          - Cuwwent wawk info
 *              op                  - Cuwwent Op (fwom pawse wawk)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set a bweakpoint in a contwow method at the specified
 *              AMW offset
 *
 ******************************************************************************/

void
acpi_db_set_method_bweakpoint(chaw *wocation,
			      stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op)
{
	u32 addwess;
	u32 amw_offset;

	if (!op) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	/* Get and vewify the bweakpoint addwess */

	addwess = stwtouw(wocation, NUWW, 16);
	amw_offset = (u32)ACPI_PTW_DIFF(op->common.amw,
					wawk_state->pawsew_state.amw_stawt);
	if (addwess <= amw_offset) {
		acpi_os_pwintf("Bweakpoint %X is beyond cuwwent addwess %X\n",
			       addwess, amw_offset);
	}

	/* Save bweakpoint in cuwwent wawk */

	wawk_state->usew_bweakpoint = addwess;
	acpi_os_pwintf("Bweakpoint set at AMW offset %X\n", addwess);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_caww_bweakpoint
 *
 * PAWAMETEWS:  op                  - Cuwwent Op (fwom pawse wawk)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set a bweakpoint in a contwow method at the specified
 *              AMW offset
 *
 ******************************************************************************/

void acpi_db_set_method_caww_bweakpoint(union acpi_pawse_object *op)
{

	if (!op) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	acpi_gbw_step_to_next_caww = TWUE;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_data
 *
 * PAWAMETEWS:  type_awg        - W fow wocaw, A fow awgument
 *              index_awg       - which one
 *              vawue_awg       - Vawue to set.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set a wocaw ow awgument fow the wunning contwow method.
 *              NOTE: onwy object suppowted is Numbew.
 *
 ******************************************************************************/

void acpi_db_set_method_data(chaw *type_awg, chaw *index_awg, chaw *vawue_awg)
{
	chaw type;
	u32 index;
	u32 vawue;
	stwuct acpi_wawk_state *wawk_state;
	union acpi_opewand_object *obj_desc;
	acpi_status status;
	stwuct acpi_namespace_node *node;

	/* Vawidate type_awg */

	acpi_ut_stwupw(type_awg);
	type = type_awg[0];
	if ((type != 'W') && (type != 'A') && (type != 'N')) {
		acpi_os_pwintf("Invawid SET opewand: %s\n", type_awg);
		wetuwn;
	}

	vawue = stwtouw(vawue_awg, NUWW, 16);

	if (type == 'N') {
		node = acpi_db_convewt_to_node(index_awg);
		if (!node) {
			wetuwn;
		}

		if (node->type != ACPI_TYPE_INTEGEW) {
			acpi_os_pwintf("Can onwy set Integew nodes\n");
			wetuwn;
		}
		obj_desc = node->object;
		obj_desc->integew.vawue = vawue;
		wetuwn;
	}

	/* Get the index and vawue */

	index = stwtouw(index_awg, NUWW, 16);

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	/* Cweate and initiawize the new object */

	obj_desc = acpi_ut_cweate_integew_object((u64)vawue);
	if (!obj_desc) {
		acpi_os_pwintf("Couwd not cweate an intewnaw object\n");
		wetuwn;
	}

	/* Stowe the new object into the tawget */

	switch (type) {
	case 'A':

		/* Set a method awgument */

		if (index > ACPI_METHOD_MAX_AWG) {
			acpi_os_pwintf("Awg%u - Invawid awgument name\n",
				       index);
			goto cweanup;
		}

		status = acpi_ds_stowe_object_to_wocaw(ACPI_WEFCWASS_AWG,
						       index, obj_desc,
						       wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		obj_desc = wawk_state->awguments[index].object;

		acpi_os_pwintf("Awg%u: ", index);
		acpi_db_dispway_intewnaw_object(obj_desc, wawk_state);
		bweak;

	case 'W':

		/* Set a method wocaw */

		if (index > ACPI_METHOD_MAX_WOCAW) {
			acpi_os_pwintf
			    ("Wocaw%u - Invawid wocaw vawiabwe name\n", index);
			goto cweanup;
		}

		status = acpi_ds_stowe_object_to_wocaw(ACPI_WEFCWASS_WOCAW,
						       index, obj_desc,
						       wawk_state);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		obj_desc = wawk_state->wocaw_vawiabwes[index].object;

		acpi_os_pwintf("Wocaw%u: ", index);
		acpi_db_dispway_intewnaw_object(obj_desc, wawk_state);
		bweak;

	defauwt:

		bweak;
	}

cweanup:
	acpi_ut_wemove_wefewence(obj_desc);
}

#ifdef ACPI_DISASSEMBWEW
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_disassembwe_amw
 *
 * PAWAMETEWS:  statements          - Numbew of statements to disassembwe
 *              op                  - Cuwwent Op (fwom pawse wawk)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway disassembwed AMW (ASW) stawting fwom Op fow the numbew
 *              of statements specified.
 *
 ******************************************************************************/

void acpi_db_disassembwe_amw(chaw *statements, union acpi_pawse_object *op)
{
	u32 num_statements = 8;

	if (!op) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	if (statements) {
		num_statements = stwtouw(statements, NUWW, 0);
	}

	acpi_dm_disassembwe(NUWW, op, num_statements);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_disassembwe_method
 *
 * PAWAMETEWS:  name            - Name of contwow method
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway disassembwed AMW (ASW) stawting fwom Op fow the numbew
 *              of statements specified.
 *
 ******************************************************************************/

acpi_status acpi_db_disassembwe_method(chaw *name)
{
	acpi_status status;
	union acpi_pawse_object *op;
	stwuct acpi_wawk_state *wawk_state;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *method;

	method = acpi_db_convewt_to_node(name);
	if (!method) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	if (method->type != ACPI_TYPE_METHOD) {
		ACPI_EWWOW((AE_INFO, "%s (%s): Object must be a contwow method",
			    name, acpi_ut_get_type_name(method->type)));
		wetuwn (AE_BAD_PAWAMETEW);
	}

	obj_desc = method->object;

	op = acpi_ps_cweate_scope_op(obj_desc->method.amw_stawt);
	if (!op) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Cweate and initiawize a new wawk state */

	wawk_state = acpi_ds_cweate_wawk_state(0, op, NUWW, NUWW);
	if (!wawk_state) {
		wetuwn (AE_NO_MEMOWY);
	}

	status = acpi_ds_init_amw_wawk(wawk_state, op, NUWW,
				       obj_desc->method.amw_stawt,
				       obj_desc->method.amw_wength, NUWW,
				       ACPI_IMODE_WOAD_PASS1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	status = acpi_ut_awwocate_ownew_id(&obj_desc->method.ownew_id);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	wawk_state->ownew_id = obj_desc->method.ownew_id;

	/* Push stawt scope on scope stack and make it cuwwent */

	status = acpi_ds_scope_stack_push(method, method->type, wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Pawse the entiwe method AMW incwuding defewwed opewatows */

	wawk_state->pawse_fwags &= ~ACPI_PAWSE_DEWETE_TWEE;
	wawk_state->pawse_fwags |= ACPI_PAWSE_DISASSEMBWE;

	status = acpi_ps_pawse_amw(wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	(void)acpi_dm_pawse_defewwed_ops(op);

	/* Now we can disassembwe the method */

	acpi_gbw_dm_opt_vewbose = FAWSE;
	acpi_dm_disassembwe(NUWW, op, 0);
	acpi_gbw_dm_opt_vewbose = TWUE;

	acpi_ps_dewete_pawse_twee(op);

	/* Method cweanup */

	acpi_ns_dewete_namespace_subtwee(method);
	acpi_ns_dewete_namespace_by_ownew(obj_desc->method.ownew_id);
	acpi_ut_wewease_ownew_id(&obj_desc->method.ownew_id);
	wetuwn (AE_OK);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evawuate_object
 *
 * PAWAMETEWS:  node                - Namespace node fow the object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Main execution function fow the Evawuate/Execute/Aww debuggew
 *              commands.
 *
 ******************************************************************************/

static acpi_status acpi_db_evawuate_object(stwuct acpi_namespace_node *node)
{
	chaw *pathname;
	u32 i;
	stwuct acpi_device_info *obj_info;
	stwuct acpi_object_wist pawam_objects;
	union acpi_object pawams[ACPI_METHOD_NUM_AWGS];
	stwuct acpi_buffew wetuwn_obj;
	acpi_status status;

	pathname = acpi_ns_get_extewnaw_pathname(node);
	if (!pathname) {
		wetuwn (AE_OK);
	}

	/* Get the object info fow numbew of method pawametews */

	status = acpi_get_object_info(node, &obj_info);
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(pathname);
		wetuwn (status);
	}

	pawam_objects.pointew = NUWW;
	pawam_objects.count = 0;

	if (obj_info->type == ACPI_TYPE_METHOD) {

		/* Setup defauwt pawametews */

		fow (i = 0; i < obj_info->pawam_count; i++) {
			pawams[i].type = ACPI_TYPE_INTEGEW;
			pawams[i].integew.vawue = 1;
		}

		pawam_objects.pointew = pawams;
		pawam_objects.count = obj_info->pawam_count;
	}

	ACPI_FWEE(obj_info);
	wetuwn_obj.pointew = NUWW;
	wetuwn_obj.wength = ACPI_AWWOCATE_BUFFEW;

	/* Do the actuaw method execution */

	acpi_gbw_method_executing = TWUE;

	status = acpi_evawuate_object(node, NUWW, &pawam_objects, &wetuwn_obj);
	acpi_gbw_method_executing = FAWSE;

	acpi_os_pwintf("%-32s wetuwned %s\n", pathname,
		       acpi_fowmat_exception(status));
	if (wetuwn_obj.wength) {
		acpi_os_pwintf("Evawuation of %s wetuwned object %p, "
			       "extewnaw buffew wength %X\n",
			       pathname, wetuwn_obj.pointew,
			       (u32)wetuwn_obj.wength);

		acpi_db_dump_extewnaw_object(wetuwn_obj.pointew, 1);
		acpi_os_pwintf("\n");
	}

	ACPI_FWEE(pathname);

	/* Ignowe status fwom method execution */

	wetuwn (AE_OK);

	/* Update count, check if we have executed enough methods */

}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_execute
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Batch execution function. Evawuates aww "pwedefined" objects --
 *              the nameseg begins with an undewscowe.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_execute(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	stwuct acpi_db_execute_wawk *info =
	    (stwuct acpi_db_execute_wawk *)context;
	acpi_status status;
	const union acpi_pwedefined_info *pwedefined;

	pwedefined = acpi_ut_match_pwedefined_method(node->name.ascii);
	if (!pwedefined) {
		wetuwn (AE_OK);
	}

	if (node->type == ACPI_TYPE_WOCAW_SCOPE) {
		wetuwn (AE_OK);
	}

	acpi_db_evawuate_object(node);

	/* Ignowe status fwom object evawuation */

	status = AE_OK;

	/* Update count, check if we have executed enough methods */

	info->count++;
	if (info->count >= info->max_count) {
		status = AE_CTWW_TEWMINATE;
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_execute_aww
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Batch execution function. Evawuates aww objects whose path ends
 *              with the nameseg "Info->NameSeg". Used fow the "AWW" command.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_execute_aww(acpi_handwe obj_handwe,
			     u32 nesting_wevew,
			     void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	stwuct acpi_db_execute_wawk *info =
	    (stwuct acpi_db_execute_wawk *)context;
	acpi_status status;

	if (!ACPI_COMPAWE_NAMESEG(node->name.ascii, info->name_seg)) {
		wetuwn (AE_OK);
	}

	if (node->type == ACPI_TYPE_WOCAW_SCOPE) {
		wetuwn (AE_OK);
	}

	/* Now evawuate the input object (node) */

	acpi_db_evawuate_object(node);

	/* Ignowe status fwom method execution */

	status = AE_OK;

	/* Update count of executed methods/objects */

	info->count++;
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evawuate_pwedefined_names
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Namespace batch execution. Execute pwedefined names in the
 *              namespace, up to the max count, if specified.
 *
 ******************************************************************************/

void acpi_db_evawuate_pwedefined_names(void)
{
	stwuct acpi_db_execute_wawk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_wawk_fow_execute,
				  NUWW, (void *)&info, NUWW);

	acpi_os_pwintf("Evawuated %u pwedefined names in the namespace\n",
		       info.count);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evawuate_aww
 *
 * PAWAMETEWS:  none_acpi_gbw_db_method_info
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Namespace batch execution. Impwements the "AWW" command.
 *              Execute aww namepaths whose finaw nameseg matches the
 *              input nameseg.
 *
 ******************************************************************************/

void acpi_db_evawuate_aww(chaw *name_seg)
{
	stwuct acpi_db_execute_wawk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;
	ACPI_COPY_NAMESEG(info.name_seg, name_seg);
	info.name_seg[ACPI_NAMESEG_SIZE] = 0;

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_wawk_fow_execute_aww,
				  NUWW, (void *)&info, NUWW);

	acpi_os_pwintf("Evawuated %u names in the namespace\n", info.count);
}
