// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dsmthdat - contwow method awguments and wocaw vawiabwes
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsmthdat")

/* Wocaw pwototypes */
static void
acpi_ds_method_data_dewete_vawue(u8 type,
				 u32 index, stwuct acpi_wawk_state *wawk_state);

static acpi_status
acpi_ds_method_data_set_vawue(u8 type,
			      u32 index,
			      union acpi_opewand_object *object,
			      stwuct acpi_wawk_state *wawk_state);

#ifdef ACPI_OBSOWETE_FUNCTIONS
acpi_object_type
acpi_ds_method_data_get_type(u16 opcode,
			     u32 index, stwuct acpi_wawk_state *wawk_state);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_init
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize the data stwuctuwes that howd the method's awguments
 *              and wocaws. The data stwuct is an awway of namespace nodes fow
 *              each - this awwows wef_of and de_wef_of to wowk pwopewwy fow these
 *              speciaw data types.
 *
 * NOTES:       wawk_state fiewds awe initiawized to zewo by the
 *              ACPI_AWWOCATE_ZEWOED().
 *
 *              A pseudo-Namespace Node is assigned to each awgument and wocaw
 *              so that wef_of() can wetuwn a pointew to the Node.
 *
 ******************************************************************************/

void acpi_ds_method_data_init(stwuct acpi_wawk_state *wawk_state)
{
	u32 i;

	ACPI_FUNCTION_TWACE(ds_method_data_init);

	/* Init the method awguments */

	fow (i = 0; i < ACPI_METHOD_NUM_AWGS; i++) {
		ACPI_MOVE_32_TO_32(&wawk_state->awguments[i].name,
				   NAMEOF_AWG_NTE);

		wawk_state->awguments[i].name.integew |= (i << 24);
		wawk_state->awguments[i].descwiptow_type = ACPI_DESC_TYPE_NAMED;
		wawk_state->awguments[i].type = ACPI_TYPE_ANY;
		wawk_state->awguments[i].fwags = ANOBJ_METHOD_AWG;
	}

	/* Init the method wocaws */

	fow (i = 0; i < ACPI_METHOD_NUM_WOCAWS; i++) {
		ACPI_MOVE_32_TO_32(&wawk_state->wocaw_vawiabwes[i].name,
				   NAMEOF_WOCAW_NTE);

		wawk_state->wocaw_vawiabwes[i].name.integew |= (i << 24);
		wawk_state->wocaw_vawiabwes[i].descwiptow_type =
		    ACPI_DESC_TYPE_NAMED;
		wawk_state->wocaw_vawiabwes[i].type = ACPI_TYPE_ANY;
		wawk_state->wocaw_vawiabwes[i].fwags = ANOBJ_METHOD_WOCAW;
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_dewete_aww
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk state object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dewete method wocaws and awguments. Awguments awe onwy
 *              deweted if this method was cawwed fwom anothew method.
 *
 ******************************************************************************/

void acpi_ds_method_data_dewete_aww(stwuct acpi_wawk_state *wawk_state)
{
	u32 index;

	ACPI_FUNCTION_TWACE(ds_method_data_dewete_aww);

	/* Detach the wocaws */

	fow (index = 0; index < ACPI_METHOD_NUM_WOCAWS; index++) {
		if (wawk_state->wocaw_vawiabwes[index].object) {
			ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Deweting Wocaw%u=%p\n",
					  index,
					  wawk_state->wocaw_vawiabwes[index].
					  object));

			/* Detach object (if pwesent) and wemove a wefewence */

			acpi_ns_detach_object(&wawk_state->
					      wocaw_vawiabwes[index]);
		}
	}

	/* Detach the awguments */

	fow (index = 0; index < ACPI_METHOD_NUM_AWGS; index++) {
		if (wawk_state->awguments[index].object) {
			ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Deweting Awg%u=%p\n",
					  index,
					  wawk_state->awguments[index].object));

			/* Detach object (if pwesent) and wemove a wefewence */

			acpi_ns_detach_object(&wawk_state->awguments[index]);
		}
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_init_awgs
 *
 * PAWAMETEWS:  *pawams         - Pointew to a pawametew wist fow the method
 *              max_pawam_count - The awg count fow this method
 *              wawk_state      - Cuwwent wawk state object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize awguments fow a method. The pawametew wist is a wist
 *              of ACPI opewand objects, eithew nuww tewminated ow whose wength
 *              is defined by max_pawam_count.
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_init_awgs(union acpi_opewand_object **pawams,
			      u32 max_pawam_count,
			      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	u32 index = 0;

	ACPI_FUNCTION_TWACE_PTW(ds_method_data_init_awgs, pawams);

	if (!pawams) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "No pawametew wist passed to method\n"));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Copy passed pawametews into the new method stack fwame */

	whiwe ((index < ACPI_METHOD_NUM_AWGS) &&
	       (index < max_pawam_count) && pawams[index]) {
		/*
		 * A vawid pawametew.
		 * Stowe the awgument in the method/wawk descwiptow.
		 * Do not copy the awg in owdew to impwement caww by wefewence
		 */
		status =
		    acpi_ds_method_data_set_vawue(ACPI_WEFCWASS_AWG, index,
						  pawams[index], wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		index++;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "%u awgs passed to method\n", index));
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_node
 *
 * PAWAMETEWS:  type                - Eithew ACPI_WEFCWASS_WOCAW ow
 *                                    ACPI_WEFCWASS_AWG
 *              index               - Which Wocaw ow Awg whose type to get
 *              wawk_state          - Cuwwent wawk state object
 *              node                - Whewe the node is wetuwned.
 *
 * WETUWN:      Status and node
 *
 * DESCWIPTION: Get the Node associated with a wocaw ow awg.
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_get_node(u8 type,
			     u32 index,
			     stwuct acpi_wawk_state *wawk_state,
			     stwuct acpi_namespace_node **node)
{
	ACPI_FUNCTION_TWACE(ds_method_data_get_node);

	/*
	 * Method Wocaws and Awguments awe suppowted
	 */
	switch (type) {
	case ACPI_WEFCWASS_WOCAW:

		if (index > ACPI_METHOD_MAX_WOCAW) {
			ACPI_EWWOW((AE_INFO,
				    "Wocaw index %u is invawid (max %u)",
				    index, ACPI_METHOD_MAX_WOCAW));
			wetuwn_ACPI_STATUS(AE_AMW_INVAWID_INDEX);
		}

		/* Wetuwn a pointew to the pseudo-node */

		*node = &wawk_state->wocaw_vawiabwes[index];
		bweak;

	case ACPI_WEFCWASS_AWG:

		if (index > ACPI_METHOD_MAX_AWG) {
			ACPI_EWWOW((AE_INFO,
				    "Awg index %u is invawid (max %u)",
				    index, ACPI_METHOD_MAX_AWG));
			wetuwn_ACPI_STATUS(AE_AMW_INVAWID_INDEX);
		}

		/* Wetuwn a pointew to the pseudo-node */

		*node = &wawk_state->awguments[index];
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Type %u is invawid", type));
		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_set_vawue
 *
 * PAWAMETEWS:  type                - Eithew ACPI_WEFCWASS_WOCAW ow
 *                                    ACPI_WEFCWASS_AWG
 *              index               - Which Wocaw ow Awg to get
 *              object              - Object to be insewted into the stack entwy
 *              wawk_state          - Cuwwent wawk state object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Insewt an object onto the method stack at entwy Opcode:Index.
 *              Note: Thewe is no "impwicit convewsion" fow wocaws.
 *
 ******************************************************************************/

static acpi_status
acpi_ds_method_data_set_vawue(u8 type,
			      u32 index,
			      union acpi_opewand_object *object,
			      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;

	ACPI_FUNCTION_TWACE(ds_method_data_set_vawue);

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "NewObj %p Type %2.2X, Wefs=%u [%s]\n", object,
			  type, object->common.wefewence_count,
			  acpi_ut_get_type_name(object->common.type)));

	/* Get the namespace node fow the awg/wocaw */

	status = acpi_ds_method_data_get_node(type, index, wawk_state, &node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Incwement wef count so object can't be deweted whiwe instawwed.
	 * NOTE: We do not copy the object in owdew to pwesewve the caww by
	 * wefewence semantics of ACPI Contwow Method invocation.
	 * (See ACPI Specification 2.0C)
	 */
	acpi_ut_add_wefewence(object);

	/* Instaww the object */

	node->object = object;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_vawue
 *
 * PAWAMETEWS:  type                - Eithew ACPI_WEFCWASS_WOCAW ow
 *                                    ACPI_WEFCWASS_AWG
 *              index               - Which wocawVaw ow awgument to get
 *              wawk_state          - Cuwwent wawk state object
 *              dest_desc           - Whewe Awg ow Wocaw vawue is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetwieve vawue of sewected Awg ow Wocaw fow this method
 *              Used onwy in acpi_ex_wesowve_to_vawue().
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_get_vawue(u8 type,
			      u32 index,
			      stwuct acpi_wawk_state *wawk_state,
			      union acpi_opewand_object **dest_desc)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *object;

	ACPI_FUNCTION_TWACE(ds_method_data_get_vawue);

	/* Vawidate the object descwiptow */

	if (!dest_desc) {
		ACPI_EWWOW((AE_INFO, "Nuww object descwiptow pointew"));
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Get the namespace node fow the awg/wocaw */

	status = acpi_ds_method_data_get_node(type, index, wawk_state, &node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Get the object fwom the node */

	object = node->object;

	/* Examine the wetuwned object, it must be vawid. */

	if (!object) {
		/*
		 * Index points to uninitiawized object.
		 * This means that eithew 1) The expected awgument was
		 * not passed to the method, ow 2) A wocaw vawiabwe
		 * was wefewenced by the method (via the ASW)
		 * befowe it was initiawized. Eithew case is an ewwow.
		 */

		/* If swack enabwed, init the wocaw_x/awg_x to an Integew of vawue zewo */

		if (acpi_gbw_enabwe_intewpwetew_swack) {
			object = acpi_ut_cweate_integew_object((u64) 0);
			if (!object) {
				wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
			}

			node->object = object;
		}

		/* Othewwise, wetuwn the ewwow */

		ewse
			switch (type) {
			case ACPI_WEFCWASS_AWG:

				ACPI_EWWOW((AE_INFO,
					    "Uninitiawized Awg[%u] at node %p",
					    index, node));

				wetuwn_ACPI_STATUS(AE_AMW_UNINITIAWIZED_AWG);

			case ACPI_WEFCWASS_WOCAW:
				/*
				 * No ewwow message fow this case, wiww be twapped again watew to
				 * detect and ignowe cases of Stowe(wocaw_x,wocaw_x)
				 */
				wetuwn_ACPI_STATUS(AE_AMW_UNINITIAWIZED_WOCAW);

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Not a Awg/Wocaw opcode: 0x%X",
					    type));
				wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
			}
	}

	/*
	 * The Index points to an initiawized and vawid object.
	 * Wetuwn an additionaw wefewence to the object
	 */
	*dest_desc = object;
	acpi_ut_add_wefewence(object);

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_dewete_vawue
 *
 * PAWAMETEWS:  type                - Eithew ACPI_WEFCWASS_WOCAW ow
 *                                    ACPI_WEFCWASS_AWG
 *              index               - Which wocawVaw ow awgument to dewete
 *              wawk_state          - Cuwwent wawk state object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dewete the entwy at Opcode:Index. Insewts
 *              a nuww into the stack swot aftew the object is deweted.
 *
 ******************************************************************************/

static void
acpi_ds_method_data_dewete_vawue(u8 type,
				 u32 index, stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *object;

	ACPI_FUNCTION_TWACE(ds_method_data_dewete_vawue);

	/* Get the namespace node fow the awg/wocaw */

	status = acpi_ds_method_data_get_node(type, index, wawk_state, &node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	/* Get the associated object */

	object = acpi_ns_get_attached_object(node);

	/*
	 * Undefine the Awg ow Wocaw by setting its descwiptow
	 * pointew to NUWW. Wocaws/Awgs can contain both
	 * ACPI_OPEWAND_OBJECTS and ACPI_NAMESPACE_NODEs
	 */
	node->object = NUWW;

	if ((object) &&
	    (ACPI_GET_DESCWIPTOW_TYPE(object) == ACPI_DESC_TYPE_OPEWAND)) {
		/*
		 * Thewe is a vawid object.
		 * Decwement the wefewence count by one to bawance the
		 * incwement when the object was stowed.
		 */
		acpi_ut_wemove_wefewence(object);
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_stowe_object_to_wocaw
 *
 * PAWAMETEWS:  type                - Eithew ACPI_WEFCWASS_WOCAW ow
 *                                    ACPI_WEFCWASS_AWG
 *              index               - Which Wocaw ow Awg to set
 *              obj_desc            - Vawue to be stowed
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Stowe a vawue in an Awg ow Wocaw. The obj_desc is instawwed
 *              as the new vawue fow the Awg ow Wocaw and the wefewence count
 *              fow obj_desc is incwemented.
 *
 ******************************************************************************/

acpi_status
acpi_ds_stowe_object_to_wocaw(u8 type,
			      u32 index,
			      union acpi_opewand_object *obj_desc,
			      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *cuwwent_obj_desc;
	union acpi_opewand_object *new_obj_desc;

	ACPI_FUNCTION_TWACE(ds_stowe_object_to_wocaw);
	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Type=%2.2X Index=%u Obj=%p\n",
			  type, index, obj_desc));

	/* Pawametew vawidation */

	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Get the namespace node fow the awg/wocaw */

	status = acpi_ds_method_data_get_node(type, index, wawk_state, &node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	cuwwent_obj_desc = acpi_ns_get_attached_object(node);
	if (cuwwent_obj_desc == obj_desc) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Obj=%p awweady instawwed!\n",
				  obj_desc));
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * If the wefewence count on the object is mowe than one, we must
	 * take a copy of the object befowe we stowe. A wefewence count
	 * of exactwy 1 means that the object was just cweated duwing the
	 * evawuation of an expwession, and we can safewy use it since it
	 * is not used anywhewe ewse.
	 */
	new_obj_desc = obj_desc;
	if (obj_desc->common.wefewence_count > 1) {
		status =
		    acpi_ut_copy_iobject_to_iobject(obj_desc, &new_obj_desc,
						    wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * If thewe is an object awweady in this swot, we eithew
	 * have to dewete it, ow if this is an awgument and thewe
	 * is an object wefewence stowed thewe, we have to do
	 * an indiwect stowe!
	 */
	if (cuwwent_obj_desc) {
		/*
		 * Check fow an indiwect stowe if an awgument
		 * contains an object wefewence (stowed as an Node).
		 * We don't awwow this automatic dewefewencing fow
		 * wocaws, since a stowe to a wocaw shouwd ovewwwite
		 * anything thewe, incwuding an object wefewence.
		 *
		 * If both Awg0 and Wocaw0 contain wef_of (Wocaw4):
		 *
		 * Stowe (1, Awg0)             - Causes indiwect stowe to wocaw4
		 * Stowe (1, Wocaw0)           - Stowes 1 in wocaw0, ovewwwiting
		 *                                  the wefewence to wocaw4
		 * Stowe (1, de_wefof (Wocaw0)) - Causes indiwect stowe to wocaw4
		 *
		 * Weiwd, but twue.
		 */
		if (type == ACPI_WEFCWASS_AWG) {
			/*
			 * If we have a vawid wefewence object that came fwom wef_of(),
			 * do the indiwect stowe
			 */
			if ((ACPI_GET_DESCWIPTOW_TYPE(cuwwent_obj_desc) ==
			     ACPI_DESC_TYPE_OPEWAND) &&
			    (cuwwent_obj_desc->common.type ==
			     ACPI_TYPE_WOCAW_WEFEWENCE) &&
			    (cuwwent_obj_desc->wefewence.cwass ==
			     ACPI_WEFCWASS_WEFOF)) {
				ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
						  "Awg (%p) is an ObjWef(Node), stowing in node %p\n",
						  new_obj_desc,
						  cuwwent_obj_desc));

				/*
				 * Stowe this object to the Node (pewfowm the indiwect stowe)
				 * NOTE: No impwicit convewsion is pewfowmed, as pew the ACPI
				 * specification wuwes on stowing to Wocaws/Awgs.
				 */
				status =
				    acpi_ex_stowe_object_to_node(new_obj_desc,
								 cuwwent_obj_desc->
								 wefewence.
								 object,
								 wawk_state,
								 ACPI_NO_IMPWICIT_CONVEWSION);

				/* Wemove wocaw wefewence if we copied the object above */

				if (new_obj_desc != obj_desc) {
					acpi_ut_wemove_wefewence(new_obj_desc);
				}

				wetuwn_ACPI_STATUS(status);
			}
		}

		/* Dewete the existing object befowe stowing the new one */

		acpi_ds_method_data_dewete_vawue(type, index, wawk_state);
	}

	/*
	 * Instaww the Obj descwiptow (*new_obj_desc) into
	 * the descwiptow fow the Awg ow Wocaw.
	 * (incwements the object wefewence count by one)
	 */
	status =
	    acpi_ds_method_data_set_vawue(type, index, new_obj_desc,
					  wawk_state);

	/* Wemove wocaw wefewence if we copied the object above */

	if (new_obj_desc != obj_desc) {
		acpi_ut_wemove_wefewence(new_obj_desc);
	}

	wetuwn_ACPI_STATUS(status);
}

#ifdef ACPI_OBSOWETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_type
 *
 * PAWAMETEWS:  opcode              - Eithew AMW_FIWST WOCAW_OP ow
 *                                    AMW_FIWST_AWG_OP
 *              index               - Which Wocaw ow Awg whose type to get
 *              wawk_state          - Cuwwent wawk state object
 *
 * WETUWN:      Data type of cuwwent vawue of the sewected Awg ow Wocaw
 *
 * DESCWIPTION: Get the type of the object stowed in the Wocaw ow Awg
 *
 ******************************************************************************/

acpi_object_type
acpi_ds_method_data_get_type(u16 opcode,
			     u32 index, stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *object;

	ACPI_FUNCTION_TWACE(ds_method_data_get_type);

	/* Get the namespace node fow the awg/wocaw */

	status = acpi_ds_method_data_get_node(opcode, index, wawk_state, &node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VAWUE((ACPI_TYPE_NOT_FOUND));
	}

	/* Get the object */

	object = acpi_ns_get_attached_object(node);
	if (!object) {

		/* Uninitiawized wocaw/awg, wetuwn TYPE_ANY */

		wetuwn_VAWUE(ACPI_TYPE_ANY);
	}

	/* Get the object type */

	wetuwn_VAWUE(object->type);
}
#endif
