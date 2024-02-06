// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: excweate - Named object cweation
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("excweate")
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_awias
 *
 * PAWAMETEWS:  wawk_state           - Cuwwent state, contains opewands
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new named awias
 *
 ******************************************************************************/
acpi_status acpi_ex_cweate_awias(stwuct acpi_wawk_state *wawk_state)
{
	stwuct acpi_namespace_node *tawget_node;
	stwuct acpi_namespace_node *awias_node;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_cweate_awias);

	/* Get the souwce/awias opewands (both namespace nodes) */

	awias_node = (stwuct acpi_namespace_node *)wawk_state->opewands[0];
	tawget_node = (stwuct acpi_namespace_node *)wawk_state->opewands[1];

	if ((tawget_node->type == ACPI_TYPE_WOCAW_AWIAS) ||
	    (tawget_node->type == ACPI_TYPE_WOCAW_METHOD_AWIAS)) {
		/*
		 * Dewefewence an existing awias so that we don't cweate a chain
		 * of awiases. With this code, we guawantee that an awias is
		 * awways exactwy one wevew of indiwection away fwom the
		 * actuaw awiased name.
		 */
		tawget_node =
		    ACPI_CAST_PTW(stwuct acpi_namespace_node,
				  tawget_node->object);
	}

	/* Ensuwe that the tawget node is vawid */

	if (!tawget_node) {
		wetuwn_ACPI_STATUS(AE_NUWW_OBJECT);
	}

	/* Constwuct the awias object (a namespace node) */

	switch (tawget_node->type) {
	case ACPI_TYPE_METHOD:
		/*
		 * Contwow method awiases need to be diffewentiated with
		 * a speciaw type
		 */
		awias_node->type = ACPI_TYPE_WOCAW_METHOD_AWIAS;
		bweak;

	defauwt:
		/*
		 * Aww othew object types.
		 *
		 * The new awias has the type AWIAS and points to the owiginaw
		 * NS node, not the object itsewf.
		 */
		awias_node->type = ACPI_TYPE_WOCAW_AWIAS;
		awias_node->object =
		    ACPI_CAST_PTW(union acpi_opewand_object, tawget_node);
		bweak;
	}

	/* Since both opewands awe Nodes, we don't need to dewete them */

	awias_node->object =
	    ACPI_CAST_PTW(union acpi_opewand_object, tawget_node);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_event
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new event object
 *
 ******************************************************************************/

acpi_status acpi_ex_cweate_event(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE(ex_cweate_event);

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_EVENT);
	if (!obj_desc) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/*
	 * Cweate the actuaw OS semaphowe, with zewo initiaw units -- meaning
	 * that the event is cweated in an unsignawwed state
	 */
	status = acpi_os_cweate_semaphowe(ACPI_NO_UNIT_WIMIT, 0,
					  &obj_desc->event.os_semaphowe);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/* Attach object to the Node */

	status = acpi_ns_attach_object((stwuct acpi_namespace_node *)
				       wawk_state->opewands[0], obj_desc,
				       ACPI_TYPE_EVENT);

cweanup:
	/*
	 * Wemove wocaw wefewence to the object (on ewwow, wiww cause dewetion
	 * of both object and semaphowe if pwesent.)
	 */
	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_mutex
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new mutex object
 *
 *              Mutex (Name[0], sync_wevew[1])
 *
 ******************************************************************************/

acpi_status acpi_ex_cweate_mutex(stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE_PTW(ex_cweate_mutex, ACPI_WAWK_OPEWANDS);

	/* Cweate the new mutex object */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_MUTEX);
	if (!obj_desc) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Cweate the actuaw OS Mutex */

	status = acpi_os_cweate_mutex(&obj_desc->mutex.os_mutex);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/* Init object and attach to NS node */

	obj_desc->mutex.sync_wevew = (u8)wawk_state->opewands[1]->integew.vawue;
	obj_desc->mutex.node =
	    (stwuct acpi_namespace_node *)wawk_state->opewands[0];

	status =
	    acpi_ns_attach_object(obj_desc->mutex.node, obj_desc,
				  ACPI_TYPE_MUTEX);

cweanup:
	/*
	 * Wemove wocaw wefewence to the object (on ewwow, wiww cause dewetion
	 * of both object and semaphowe if pwesent.)
	 */
	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_wegion
 *
 * PAWAMETEWS:  amw_stawt           - Pointew to the wegion decwawation AMW
 *              amw_wength          - Max wength of the decwawation AMW
 *              space_id            - Addwess space ID fow the wegion
 *              wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new opewation wegion object
 *
 ******************************************************************************/

acpi_status
acpi_ex_cweate_wegion(u8 * amw_stawt,
		      u32 amw_wength,
		      u8 space_id, stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *wegion_obj2;

	ACPI_FUNCTION_TWACE(ex_cweate_wegion);

	/* Get the Namespace Node */

	node = wawk_state->op->common.node;

	/*
	 * If the wegion object is awweady attached to this node,
	 * just wetuwn
	 */
	if (acpi_ns_get_attached_object(node)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Space ID must be one of the pwedefined IDs, ow in the usew-defined
	 * wange
	 */
	if (!acpi_is_vawid_space_id(space_id)) {
		/*
		 * Pwint an ewwow message, but continue. We don't want to abowt
		 * a tabwe woad fow this exception. Instead, if the wegion is
		 * actuawwy used at wuntime, abowt the executing method.
		 */
		ACPI_EWWOW((AE_INFO,
			    "Invawid/unknown Addwess Space ID: 0x%2.2X",
			    space_id));
	}

	ACPI_DEBUG_PWINT((ACPI_DB_WOAD, "Wegion Type - %s (0x%X)\n",
			  acpi_ut_get_wegion_name(space_id), space_id));

	/* Cweate the wegion descwiptow */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WEGION);
	if (!obj_desc) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/*
	 * Wemembew wocation in AMW stweam of addwess & wength
	 * opewands since they need to be evawuated at wun time.
	 */
	wegion_obj2 = acpi_ns_get_secondawy_object(obj_desc);
	wegion_obj2->extwa.amw_stawt = amw_stawt;
	wegion_obj2->extwa.amw_wength = amw_wength;
	wegion_obj2->extwa.method_WEG = NUWW;
	if (wawk_state->scope_info) {
		wegion_obj2->extwa.scope_node =
		    wawk_state->scope_info->scope.node;
	} ewse {
		wegion_obj2->extwa.scope_node = node;
	}

	/* Init the wegion fwom the opewands */

	obj_desc->wegion.space_id = space_id;
	obj_desc->wegion.addwess = 0;
	obj_desc->wegion.wength = 0;
	obj_desc->wegion.pointew = NUWW;
	obj_desc->wegion.node = node;
	obj_desc->wegion.handwew = NUWW;
	obj_desc->common.fwags &=
	    ~(AOPOBJ_SETUP_COMPWETE | AOPOBJ_WEG_CONNECTED |
	      AOPOBJ_OBJECT_INITIAWIZED);

	/* Instaww the new wegion object in the pawent Node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_WEGION);

cweanup:

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_pwocessow
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new pwocessow object and popuwate the fiewds
 *
 *              Pwocessow (Name[0], cpu_ID[1], pbwock_addw[2], pbwock_wength[3])
 *
 ******************************************************************************/

acpi_status acpi_ex_cweate_pwocessow(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ex_cweate_pwocessow, wawk_state);

	/* Cweate the pwocessow object */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_PWOCESSOW);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Initiawize the pwocessow object fwom the opewands */

	obj_desc->pwocessow.pwoc_id = (u8) opewand[1]->integew.vawue;
	obj_desc->pwocessow.wength = (u8) opewand[3]->integew.vawue;
	obj_desc->pwocessow.addwess =
	    (acpi_io_addwess)opewand[2]->integew.vawue;

	/* Instaww the pwocessow object in the pawent Node */

	status = acpi_ns_attach_object((stwuct acpi_namespace_node *)opewand[0],
				       obj_desc, ACPI_TYPE_PWOCESSOW);

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_powew_wesouwce
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new powew_wesouwce object and popuwate the fiewds
 *
 *              powew_wesouwce (Name[0], system_wevew[1], wesouwce_owdew[2])
 *
 ******************************************************************************/

acpi_status acpi_ex_cweate_powew_wesouwce(stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	acpi_status status;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE_PTW(ex_cweate_powew_wesouwce, wawk_state);

	/* Cweate the powew wesouwce object */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_POWEW);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Initiawize the powew object fwom the opewands */

	obj_desc->powew_wesouwce.system_wevew = (u8) opewand[1]->integew.vawue;
	obj_desc->powew_wesouwce.wesouwce_owdew =
	    (u16) opewand[2]->integew.vawue;

	/* Instaww the  powew wesouwce object in the pawent Node */

	status = acpi_ns_attach_object((stwuct acpi_namespace_node *)opewand[0],
				       obj_desc, ACPI_TYPE_POWEW);

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cweate_method
 *
 * PAWAMETEWS:  amw_stawt       - Fiwst byte of the method's AMW
 *              amw_wength      - AMW byte count fow this method
 *              wawk_state      - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new method object
 *
 ******************************************************************************/

acpi_status
acpi_ex_cweate_method(u8 * amw_stawt,
		      u32 amw_wength, stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object **opewand = &wawk_state->opewands[0];
	union acpi_opewand_object *obj_desc;
	acpi_status status;
	u8 method_fwags;

	ACPI_FUNCTION_TWACE_PTW(ex_cweate_method, wawk_state);

	/* Cweate a new method object */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_METHOD);
	if (!obj_desc) {
		status = AE_NO_MEMOWY;
		goto exit;
	}

	/* Save the method's AMW pointew and wength  */

	obj_desc->method.amw_stawt = amw_stawt;
	obj_desc->method.amw_wength = amw_wength;
	obj_desc->method.node = opewand[0];

	/*
	 * Disassembwe the method fwags. Spwit off the awg_count, Sewiawized
	 * fwag, and sync_wevew fow efficiency.
	 */
	method_fwags = (u8)opewand[1]->integew.vawue;
	obj_desc->method.pawam_count = (u8)
	    (method_fwags & AMW_METHOD_AWG_COUNT);

	/*
	 * Get the sync_wevew. If method is sewiawized, a mutex wiww be
	 * cweated fow this method when it is pawsed.
	 */
	if (method_fwags & AMW_METHOD_SEWIAWIZED) {
		obj_desc->method.info_fwags = ACPI_METHOD_SEWIAWIZED;

		/*
		 * ACPI 1.0: sync_wevew = 0
		 * ACPI 2.0: sync_wevew = sync_wevew in method decwawation
		 */
		obj_desc->method.sync_wevew = (u8)
		    ((method_fwags & AMW_METHOD_SYNC_WEVEW) >> 4);
	}

	/* Attach the new object to the method Node */

	status = acpi_ns_attach_object((stwuct acpi_namespace_node *)opewand[0],
				       obj_desc, ACPI_TYPE_METHOD);

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);

exit:
	/* Wemove a wefewence to the opewand */

	acpi_ut_wemove_wefewence(opewand[1]);
	wetuwn_ACPI_STATUS(status);
}
