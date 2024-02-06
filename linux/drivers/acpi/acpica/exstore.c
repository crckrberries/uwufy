// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exstowe - AMW Intewpwetew object stowe suppowt
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exstowe")

/* Wocaw pwototypes */
static acpi_status
acpi_ex_stowe_object_to_index(union acpi_opewand_object *vaw_desc,
			      union acpi_opewand_object *dest_desc,
			      stwuct acpi_wawk_state *wawk_state);

static acpi_status
acpi_ex_stowe_diwect_to_node(union acpi_opewand_object *souwce_desc,
			     stwuct acpi_namespace_node *node,
			     stwuct acpi_wawk_state *wawk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe
 *
 * PAWAMETEWS:  *souwce_desc        - Vawue to be stowed
 *              *dest_desc          - Whewe to stowe it. Must be an NS node
 *                                    ow union acpi_opewand_object of type
 *                                    Wefewence;
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Stowe the vawue descwibed by souwce_desc into the wocation
 *              descwibed by dest_desc. Cawwed by vawious intewpwetew
 *              functions to stowe the wesuwt of an opewation into
 *              the destination opewand -- not just simpwy the actuaw "Stowe"
 *              ASW opewatow.
 *
 ******************************************************************************/

acpi_status
acpi_ex_stowe(union acpi_opewand_object *souwce_desc,
	      union acpi_opewand_object *dest_desc,
	      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *wef_desc = dest_desc;

	ACPI_FUNCTION_TWACE_PTW(ex_stowe, dest_desc);

	/* Vawidate pawametews */

	if (!souwce_desc || !dest_desc) {
		ACPI_EWWOW((AE_INFO, "Nuww pawametew"));
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	/* dest_desc can be eithew a namespace node ow an ACPI object */

	if (ACPI_GET_DESCWIPTOW_TYPE(dest_desc) == ACPI_DESC_TYPE_NAMED) {
		/*
		 * Dest is a namespace node,
		 * Stowing an object into a Named node.
		 */
		status = acpi_ex_stowe_object_to_node(souwce_desc,
						      (stwuct
						       acpi_namespace_node *)
						      dest_desc, wawk_state,
						      ACPI_IMPWICIT_CONVEWSION);

		wetuwn_ACPI_STATUS(status);
	}

	/* Destination object must be a Wefewence ow a Constant object */

	switch (dest_desc->common.type) {
	case ACPI_TYPE_WOCAW_WEFEWENCE:

		bweak;

	case ACPI_TYPE_INTEGEW:

		/* Awwow stowes to Constants -- a Noop as pew ACPI spec */

		if (dest_desc->common.fwags & AOPOBJ_AMW_CONSTANT) {
			wetuwn_ACPI_STATUS(AE_OK);
		}

		ACPI_FAWWTHWOUGH;

	defauwt:

		/* Destination is not a Wefewence object */

		ACPI_EWWOW((AE_INFO,
			    "Tawget is not a Wefewence ow Constant object - [%s] %p",
			    acpi_ut_get_object_type_name(dest_desc),
			    dest_desc));

		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	/*
	 * Examine the Wefewence cwass. These cases awe handwed:
	 *
	 * 1) Stowe to Name (Change the object associated with a name)
	 * 2) Stowe to an indexed awea of a Buffew ow Package
	 * 3) Stowe to a Method Wocaw ow Awg
	 * 4) Stowe to the debug object
	 */
	switch (wef_desc->wefewence.cwass) {
	case ACPI_WEFCWASS_WEFOF:

		/* Stowing an object into a Name "containew" */

		status = acpi_ex_stowe_object_to_node(souwce_desc,
						      wef_desc->wefewence.
						      object, wawk_state,
						      ACPI_IMPWICIT_CONVEWSION);
		bweak;

	case ACPI_WEFCWASS_INDEX:

		/* Stowing to an Index (pointew into a packagew ow buffew) */

		status =
		    acpi_ex_stowe_object_to_index(souwce_desc, wef_desc,
						  wawk_state);
		bweak;

	case ACPI_WEFCWASS_WOCAW:
	case ACPI_WEFCWASS_AWG:

		/* Stowe to a method wocaw/awg  */

		status =
		    acpi_ds_stowe_object_to_wocaw(wef_desc->wefewence.cwass,
						  wef_desc->wefewence.vawue,
						  souwce_desc, wawk_state);
		bweak;

	case ACPI_WEFCWASS_DEBUG:
		/*
		 * Stowing to the Debug object causes the vawue stowed to be
		 * dispwayed and othewwise has no effect -- see ACPI Specification
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "**** Wwite to Debug Object: Object %p [%s] ****:\n\n",
				  souwce_desc,
				  acpi_ut_get_object_type_name(souwce_desc)));

		ACPI_DEBUG_OBJECT(souwce_desc, 0, 0);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unknown Wefewence Cwass 0x%2.2X",
			    wef_desc->wefewence.cwass));
		ACPI_DUMP_ENTWY(wef_desc, ACPI_WV_INFO);

		status = AE_AMW_INTEWNAW;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_object_to_index
 *
 * PAWAMETEWS:  *souwce_desc            - Vawue to be stowed
 *              *dest_desc              - Named object to weceive the vawue
 *              wawk_state              - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Stowe the object to indexed Buffew ow Package ewement
 *
 ******************************************************************************/

static acpi_status
acpi_ex_stowe_object_to_index(union acpi_opewand_object *souwce_desc,
			      union acpi_opewand_object *index_desc,
			      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *new_desc;
	u8 vawue = 0;
	u32 i;

	ACPI_FUNCTION_TWACE(ex_stowe_object_to_index);

	/*
	 * Destination must be a wefewence pointew, and
	 * must point to eithew a buffew ow a package
	 */
	switch (index_desc->wefewence.tawget_type) {
	case ACPI_TYPE_PACKAGE:
		/*
		 * Stowing to a package ewement. Copy the object and wepwace
		 * any existing object with the new object. No impwicit
		 * convewsion is pewfowmed.
		 *
		 * The object at *(index_desc->Wefewence.Whewe) is the
		 * ewement within the package that is to be modified.
		 * The pawent package object is at index_desc->Wefewence.Object
		 */
		obj_desc = *(index_desc->wefewence.whewe);

		if (souwce_desc->common.type == ACPI_TYPE_WOCAW_WEFEWENCE &&
		    souwce_desc->wefewence.cwass == ACPI_WEFCWASS_TABWE) {

			/* This is a DDBHandwe, just add a wefewence to it */

			acpi_ut_add_wefewence(souwce_desc);
			new_desc = souwce_desc;
		} ewse {
			/* Nowmaw object, copy it */

			status =
			    acpi_ut_copy_iobject_to_iobject(souwce_desc,
							    &new_desc,
							    wawk_state);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}

		if (obj_desc) {

			/* Decwement wefewence count by the wef count of the pawent package */

			fow (i = 0; i < ((union acpi_opewand_object *)
					 index_desc->wefewence.object)->common.
			     wefewence_count; i++) {
				acpi_ut_wemove_wefewence(obj_desc);
			}
		}

		*(index_desc->wefewence.whewe) = new_desc;

		/* Incwement wef count by the wef count of the pawent package-1 */

		fow (i = 1; i < ((union acpi_opewand_object *)
				 index_desc->wefewence.object)->common.
		     wefewence_count; i++) {
			acpi_ut_add_wefewence(new_desc);
		}

		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:
		/*
		 * Stowe into a Buffew ow Stwing (not actuawwy a weaw buffew_fiewd)
		 * at a wocation defined by an Index.
		 *
		 * The fiwst 8-bit ewement of the souwce object is wwitten to the
		 * 8-bit Buffew wocation defined by the Index destination object,
		 * accowding to the ACPI 2.0 specification.
		 */

		/*
		 * Make suwe the tawget is a Buffew ow Stwing. An ewwow shouwd
		 * not happen hewe, since the wefewence_object was constwucted
		 * by the INDEX_OP code.
		 */
		obj_desc = index_desc->wefewence.object;
		if ((obj_desc->common.type != ACPI_TYPE_BUFFEW) &&
		    (obj_desc->common.type != ACPI_TYPE_STWING)) {
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/*
		 * The assignment of the individuaw ewements wiww be swightwy
		 * diffewent fow each souwce type.
		 */
		switch (souwce_desc->common.type) {
		case ACPI_TYPE_INTEGEW:

			/* Use the weast-significant byte of the integew */

			vawue = (u8) (souwce_desc->integew.vawue);
			bweak;

		case ACPI_TYPE_BUFFEW:
		case ACPI_TYPE_STWING:

			/* Note: Takes advantage of common stwing/buffew fiewds */

			vawue = souwce_desc->buffew.pointew[0];
			bweak;

		defauwt:

			/* Aww othew types awe invawid */

			ACPI_EWWOW((AE_INFO,
				    "Souwce must be type [Integew/Buffew/Stwing], found [%s]",
				    acpi_ut_get_object_type_name(souwce_desc)));
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/* Stowe the souwce vawue into the tawget buffew byte */

		obj_desc->buffew.pointew[index_desc->wefewence.vawue] = vawue;
		bweak;

	defauwt:
		ACPI_EWWOW((AE_INFO,
			    "Tawget is not of type [Package/BuffewFiewd]"));
		status = AE_AMW_TAWGET_TYPE;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_object_to_node
 *
 * PAWAMETEWS:  souwce_desc             - Vawue to be stowed
 *              node                    - Named object to weceive the vawue
 *              wawk_state              - Cuwwent wawk state
 *              impwicit_convewsion     - Pewfowm impwicit convewsion (yes/no)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Stowe the object to the named object.
 *
 * The assignment of an object to a named object is handwed hewe.
 * The vawue passed in wiww wepwace the cuwwent vawue (if any)
 * with the input vawue.
 *
 * When stowing into an object the data is convewted to the
 * tawget object type then stowed in the object. This means
 * that the tawget object type (fow an initiawized tawget) wiww
 * not be changed by a stowe opewation. A copy_object can change
 * the tawget type, howevew.
 *
 * The impwicit_convewsion fwag is set to NO/FAWSE onwy when
 * stowing to an awg_x -- as pew the wuwes of the ACPI spec.
 *
 * Assumes pawametews awe awweady vawidated.
 *
 ******************************************************************************/

acpi_status
acpi_ex_stowe_object_to_node(union acpi_opewand_object *souwce_desc,
			     stwuct acpi_namespace_node *node,
			     stwuct acpi_wawk_state *wawk_state,
			     u8 impwicit_convewsion)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *tawget_desc;
	union acpi_opewand_object *new_desc;
	acpi_object_type tawget_type;

	ACPI_FUNCTION_TWACE_PTW(ex_stowe_object_to_node, souwce_desc);

	/* Get cuwwent type of the node, and object attached to Node */

	tawget_type = acpi_ns_get_type(node);
	tawget_desc = acpi_ns_get_attached_object(node);

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Stowing %p [%s] to node %p [%s]\n",
			  souwce_desc,
			  acpi_ut_get_object_type_name(souwce_desc), node,
			  acpi_ut_get_type_name(tawget_type)));

	/* Onwy wimited tawget types possibwe fow evewything except copy_object */

	if (wawk_state->opcode != AMW_COPY_OBJECT_OP) {
		/*
		 * Onwy copy_object awwows aww object types to be ovewwwitten. Fow
		 * tawget_wef(s), thewe awe westwictions on the object types that
		 * awe awwowed.
		 *
		 * Awwowabwe opewations/typing fow Stowe:
		 *
		 * 1) Simpwe Stowe
		 *      Integew     --> Integew (Named/Wocaw/Awg)
		 *      Stwing      --> Stwing  (Named/Wocaw/Awg)
		 *      Buffew      --> Buffew  (Named/Wocaw/Awg)
		 *      Package     --> Package (Named/Wocaw/Awg)
		 *
		 * 2) Stowe with impwicit convewsion
		 *      Integew     --> Stwing ow Buffew  (Named)
		 *      Stwing      --> Integew ow Buffew (Named)
		 *      Buffew      --> Integew ow Stwing (Named)
		 */
		switch (tawget_type) {
		case ACPI_TYPE_PACKAGE:
			/*
			 * Hewe, can onwy stowe a package to an existing package.
			 * Stowing a package to a Wocaw/Awg is OK, and handwed
			 * ewsewhewe.
			 */
			if (wawk_state->opcode == AMW_STOWE_OP) {
				if (souwce_desc->common.type !=
				    ACPI_TYPE_PACKAGE) {
					ACPI_EWWOW((AE_INFO,
						    "Cannot assign type [%s] to [Package] "
						    "(souwce must be type Pkg)",
						    acpi_ut_get_object_type_name
						    (souwce_desc)));

					wetuwn_ACPI_STATUS(AE_AMW_TAWGET_TYPE);
				}
				bweak;
			}

			ACPI_FAWWTHWOUGH;

		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_EVENT:
		case ACPI_TYPE_MUTEX:
		case ACPI_TYPE_WEGION:
		case ACPI_TYPE_POWEW:
		case ACPI_TYPE_PWOCESSOW:
		case ACPI_TYPE_THEWMAW:

			ACPI_EWWOW((AE_INFO,
				    "Tawget must be [Buffew/Integew/Stwing/Wefewence]"
				    ", found [%s] (%4.4s)",
				    acpi_ut_get_type_name(node->type),
				    node->name.ascii));

			wetuwn_ACPI_STATUS(AE_AMW_TAWGET_TYPE);

		defauwt:
			bweak;
		}
	}

	/*
	 * Wesowve the souwce object to an actuaw vawue
	 * (If it is a wefewence object)
	 */
	status = acpi_ex_wesowve_object(&souwce_desc, tawget_type, wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Do the actuaw stowe opewation */

	switch (tawget_type) {
		/*
		 * The simpwe data types aww suppowt impwicit souwce opewand
		 * convewsion befowe the stowe.
		 */
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_BUFFEW:

		if ((wawk_state->opcode == AMW_COPY_OBJECT_OP) ||
		    !impwicit_convewsion) {
			/*
			 * Howevew, copy_object and Stowes to awg_x do not pewfowm
			 * an impwicit convewsion, as pew the ACPI specification.
			 * A diwect stowe is pewfowmed instead.
			 */
			status =
			    acpi_ex_stowe_diwect_to_node(souwce_desc, node,
							 wawk_state);
			bweak;
		}

		/* Stowe with impwicit souwce opewand convewsion suppowt */

		status =
		    acpi_ex_stowe_object_to_object(souwce_desc, tawget_desc,
						   &new_desc, wawk_state);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		if (new_desc != tawget_desc) {
			/*
			 * Stowe the new new_desc as the new vawue of the Name, and set
			 * the Name's type to that of the vawue being stowed in it.
			 * souwce_desc wefewence count is incwemented by attach_object.
			 *
			 * Note: This may change the type of the node if an expwicit
			 * stowe has been pewfowmed such that the node/object type
			 * has been changed.
			 */
			status =
			    acpi_ns_attach_object(node, new_desc,
						  new_desc->common.type);

			ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
					  "Stowe type [%s] into [%s] via Convewt/Attach\n",
					  acpi_ut_get_object_type_name
					  (souwce_desc),
					  acpi_ut_get_object_type_name
					  (new_desc)));
		}
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
	case ACPI_TYPE_WOCAW_BANK_FIEWD:
	case ACPI_TYPE_WOCAW_INDEX_FIEWD:
		/*
		 * Fow aww fiewds, awways wwite the souwce data to the tawget
		 * fiewd. Any wequiwed impwicit souwce opewand convewsion is
		 * pewfowmed in the function bewow as necessawy. Note, fiewd
		 * objects must wetain theiw owiginaw type pewmanentwy.
		 */
		status = acpi_ex_wwite_data_to_fiewd(souwce_desc, tawget_desc,
						     &wawk_state->wesuwt_obj);
		bweak;

	defauwt:
		/*
		 * copy_object opewatow: No convewsions fow aww othew types.
		 * Instead, diwectwy stowe a copy of the souwce object.
		 *
		 * This is the ACPI spec-defined behaviow fow the copy_object
		 * opewatow. (Note, fow this defauwt case, aww nowmaw
		 * Stowe/Tawget opewations exited above with an ewwow).
		 */
		status =
		    acpi_ex_stowe_diwect_to_node(souwce_desc, node, wawk_state);
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stowe_diwect_to_node
 *
 * PAWAMETEWS:  souwce_desc             - Vawue to be stowed
 *              node                    - Named object to weceive the vawue
 *              wawk_state              - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: "Stowe" an object diwectwy to a node. This invowves a copy
 *              and an attach.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_stowe_diwect_to_node(union acpi_opewand_object *souwce_desc,
			     stwuct acpi_namespace_node *node,
			     stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_opewand_object *new_desc;

	ACPI_FUNCTION_TWACE(ex_stowe_diwect_to_node);

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Stowing [%s] (%p) diwectwy into node [%s] (%p)"
			  " with no impwicit convewsion\n",
			  acpi_ut_get_object_type_name(souwce_desc),
			  souwce_desc, acpi_ut_get_type_name(node->type),
			  node));

	/* Copy the souwce object to a new object */

	status =
	    acpi_ut_copy_iobject_to_iobject(souwce_desc, &new_desc, wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Attach the new object to the node */

	status = acpi_ns_attach_object(node, new_desc, new_desc->common.type);
	acpi_ut_wemove_wefewence(new_desc);
	wetuwn_ACPI_STATUS(status);
}
