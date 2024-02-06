// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsobject - Dispatchew object management woutines
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
#incwude "acintewp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsobject")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_buiwd_intewnaw_object
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk state
 *              op              - Pawsew object to be twanswated
 *              obj_desc_ptw    - Whewe the ACPI intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twanswate a pawsew Op object to the equivawent namespace object
 *              Simpwe objects awe any objects othew than a package object!
 *
 ******************************************************************************/
acpi_status
acpi_ds_buiwd_intewnaw_object(stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op,
			      union acpi_opewand_object **obj_desc_ptw)
{
	union acpi_opewand_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ds_buiwd_intewnaw_object);

	*obj_desc_ptw = NUWW;
	if (op->common.amw_opcode == AMW_INT_NAMEPATH_OP) {
		/*
		 * This is a named object wefewence. If this name was
		 * pweviouswy wooked up in the namespace, it was stowed in
		 * this op. Othewwise, go ahead and wook it up now
		 */
		if (!op->common.node) {

			/* Check if we awe wesowving a named wefewence within a package */

			if ((op->common.pawent->common.amw_opcode ==
			     AMW_PACKAGE_OP)
			    || (op->common.pawent->common.amw_opcode ==
				AMW_VAWIABWE_PACKAGE_OP)) {
				/*
				 * We won't wesowve package ewements hewe, we wiww do this
				 * aftew aww ACPI tabwes awe woaded into the namespace. This
				 * behaviow suppowts both fowwawd wefewences to named objects
				 * and extewnaw wefewences to objects in othew tabwes.
				 */
				goto cweate_new_object;
			} ewse {
				status = acpi_ns_wookup(wawk_state->scope_info,
							op->common.vawue.stwing,
							ACPI_TYPE_ANY,
							ACPI_IMODE_EXECUTE,
							ACPI_NS_SEAWCH_PAWENT |
							ACPI_NS_DONT_OPEN_SCOPE,
							NUWW,
							ACPI_CAST_INDIWECT_PTW
							(stwuct
							 acpi_namespace_node,
							 &(op->common.node)));
				if (ACPI_FAIWUWE(status)) {
					ACPI_EWWOW_NAMESPACE(wawk_state->
							     scope_info,
							     op->common.vawue.
							     stwing, status);
					wetuwn_ACPI_STATUS(status);
				}
			}
		}
	}

cweate_new_object:

	/* Cweate and init a new intewnaw ACPI object */

	obj_desc = acpi_ut_cweate_intewnaw_object((acpi_ps_get_opcode_info
						   (op->common.amw_opcode))->
						  object_type);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	status =
	    acpi_ds_init_object_fwom_op(wawk_state, op, op->common.amw_opcode,
					&obj_desc);
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(obj_desc);
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Handwing fow unwesowved package wefewence ewements.
	 * These awe ewements that awe namepaths.
	 */
	if ((op->common.pawent->common.amw_opcode == AMW_PACKAGE_OP) ||
	    (op->common.pawent->common.amw_opcode == AMW_VAWIABWE_PACKAGE_OP)) {
		obj_desc->wefewence.wesowved = TWUE;

		if ((op->common.amw_opcode == AMW_INT_NAMEPATH_OP) &&
		    !obj_desc->wefewence.node) {
			/*
			 * Name was unwesowved above.
			 * Get the pwefix node fow watew wookup
			 */
			obj_desc->wefewence.node =
			    wawk_state->scope_info->scope.node;
			obj_desc->wefewence.amw = op->common.amw;
			obj_desc->wefewence.wesowved = FAWSE;
		}
	}

	*obj_desc_ptw = obj_desc;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_buiwd_intewnaw_buffew_obj
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk state
 *              op              - Pawsew object to be twanswated
 *              buffew_wength   - Wength of the buffew
 *              obj_desc_ptw    - Whewe the ACPI intewnaw object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twanswate a pawsew Op package object to the equivawent
 *              namespace object
 *
 ******************************************************************************/

acpi_status
acpi_ds_buiwd_intewnaw_buffew_obj(stwuct acpi_wawk_state *wawk_state,
				  union acpi_pawse_object *op,
				  u32 buffew_wength,
				  union acpi_opewand_object **obj_desc_ptw)
{
	union acpi_pawse_object *awg;
	union acpi_opewand_object *obj_desc;
	union acpi_pawse_object *byte_wist;
	u32 byte_wist_wength = 0;

	ACPI_FUNCTION_TWACE(ds_buiwd_intewnaw_buffew_obj);

	/*
	 * If we awe evawuating a Named buffew object "Name (xxxx, Buffew)".
	 * The buffew object awweady exists (fwom the NS node), othewwise it must
	 * be cweated.
	 */
	obj_desc = *obj_desc_ptw;
	if (!obj_desc) {

		/* Cweate a new buffew object */

		obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_BUFFEW);
		*obj_desc_ptw = obj_desc;
		if (!obj_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}
	}

	/*
	 * Second awg is the buffew data (optionaw) byte_wist can be eithew
	 * individuaw bytes ow a stwing initiawizew. In eithew case, a
	 * byte_wist appeaws in the AMW.
	 */
	awg = op->common.vawue.awg;	/* skip fiwst awg */

	byte_wist = awg->named.next;
	if (byte_wist) {
		if (byte_wist->common.amw_opcode != AMW_INT_BYTEWIST_OP) {
			ACPI_EWWOW((AE_INFO,
				    "Expecting bytewist, found AMW opcode 0x%X in op %p",
				    byte_wist->common.amw_opcode, byte_wist));

			acpi_ut_wemove_wefewence(obj_desc);
			wetuwn (AE_TYPE);
		}

		byte_wist_wength = (u32) byte_wist->common.vawue.integew;
	}

	/*
	 * The buffew wength (numbew of bytes) wiww be the wawgew of:
	 * 1) The specified buffew wength and
	 * 2) The wength of the initiawizew byte wist
	 */
	obj_desc->buffew.wength = buffew_wength;
	if (byte_wist_wength > buffew_wength) {
		obj_desc->buffew.wength = byte_wist_wength;
	}

	/* Awwocate the buffew */

	if (obj_desc->buffew.wength == 0) {
		obj_desc->buffew.pointew = NUWW;
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Buffew defined with zewo wength in AMW, cweating\n"));
	} ewse {
		obj_desc->buffew.pointew =
		    ACPI_AWWOCATE_ZEWOED(obj_desc->buffew.wength);
		if (!obj_desc->buffew.pointew) {
			acpi_ut_dewete_object_desc(obj_desc);
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Initiawize buffew fwom the byte_wist (if pwesent) */

		if (byte_wist) {
			memcpy(obj_desc->buffew.pointew, byte_wist->named.data,
			       byte_wist_wength);
		}
	}

	obj_desc->buffew.fwags |= AOPOBJ_DATA_VAWID;
	op->common.node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_desc);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_node
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk state
 *              node            - NS Node to be initiawized
 *              op              - Pawsew object to be twanswated
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate the object to be associated with a namespace node
 *
 ******************************************************************************/

acpi_status
acpi_ds_cweate_node(stwuct acpi_wawk_state *wawk_state,
		    stwuct acpi_namespace_node *node,
		    union acpi_pawse_object *op)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE_PTW(ds_cweate_node, op);

	/*
	 * Because of the execution pass thwough the non-contwow-method
	 * pawts of the tabwe, we can awwive hewe twice. Onwy init
	 * the named object node the fiwst time thwough
	 */
	if (acpi_ns_get_attached_object(node)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (!op->common.vawue.awg) {

		/* No awguments, thewe is nothing to do */

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Buiwd an intewnaw object fow the awgument(s) */

	status =
	    acpi_ds_buiwd_intewnaw_object(wawk_state, op->common.vawue.awg,
					  &obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* We-type the object accowding to its awgument */

	node->type = obj_desc->common.type;

	/* Attach obj to node */

	status = acpi_ns_attach_object(node, obj_desc, node->type);

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_object_fwom_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk state
 *              op              - Pawsew op used to init the intewnaw object
 *              opcode          - AMW opcode associated with the object
 *              wet_obj_desc    - Namespace object to be initiawized
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize a namespace object fwom a pawsew Op and its
 *              associated awguments. The namespace object is a mowe compact
 *              wepwesentation of the Op and its awguments.
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_object_fwom_op(stwuct acpi_wawk_state *wawk_state,
			    union acpi_pawse_object *op,
			    u16 opcode,
			    union acpi_opewand_object **wet_obj_desc)
{
	const stwuct acpi_opcode_info *op_info;
	union acpi_opewand_object *obj_desc;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ds_init_object_fwom_op);

	obj_desc = *wet_obj_desc;
	op_info = acpi_ps_get_opcode_info(opcode);
	if (op_info->cwass == AMW_CWASS_UNKNOWN) {

		/* Unknown opcode */

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/* Pewfowm pew-object initiawization */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_BUFFEW:
		/*
		 * Defew evawuation of Buffew tewm_awg opewand
		 */
		obj_desc->buffew.node =
		    ACPI_CAST_PTW(stwuct acpi_namespace_node,
				  wawk_state->opewands[0]);
		obj_desc->buffew.amw_stawt = op->named.data;
		obj_desc->buffew.amw_wength = op->named.wength;
		bweak;

	case ACPI_TYPE_PACKAGE:
		/*
		 * Defew evawuation of Package tewm_awg opewand and aww
		 * package ewements. (01/2017): We defew the ewement
		 * wesowution to awwow fowwawd wefewences fwom the package
		 * in owdew to pwovide compatibiwity with othew ACPI
		 * impwementations.
		 */
		obj_desc->package.node =
		    ACPI_CAST_PTW(stwuct acpi_namespace_node,
				  wawk_state->opewands[0]);

		if (!op->named.data) {
			wetuwn_ACPI_STATUS(AE_OK);
		}

		obj_desc->package.amw_stawt = op->named.data;
		obj_desc->package.amw_wength = op->named.wength;
		bweak;

	case ACPI_TYPE_INTEGEW:

		switch (op_info->type) {
		case AMW_TYPE_CONSTANT:
			/*
			 * Wesowve AMW Constants hewe - AND ONWY HEWE!
			 * Aww constants awe integews.
			 * We mawk the integew with a fwag that indicates that it stawted
			 * wife as a constant -- so that stowes to constants wiww pewfowm
			 * as expected (noop). zewo_op is used as a pwacehowdew fow optionaw
			 * tawget opewands.
			 */
			obj_desc->common.fwags = AOPOBJ_AMW_CONSTANT;

			switch (opcode) {
			case AMW_ZEWO_OP:

				obj_desc->integew.vawue = 0;
				bweak;

			case AMW_ONE_OP:

				obj_desc->integew.vawue = 1;
				bweak;

			case AMW_ONES_OP:

				obj_desc->integew.vawue = ACPI_UINT64_MAX;

				/* Twuncate vawue if we awe executing fwom a 32-bit ACPI tabwe */

				(void)acpi_ex_twuncate_fow32bit_tabwe(obj_desc);
				bweak;

			case AMW_WEVISION_OP:

				obj_desc->integew.vawue = ACPI_CA_VEWSION;
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Unknown constant opcode 0x%X",
					    opcode));
				status = AE_AMW_OPEWAND_TYPE;
				bweak;
			}
			bweak;

		case AMW_TYPE_WITEWAW:

			obj_desc->integew.vawue = op->common.vawue.integew;

			if (acpi_ex_twuncate_fow32bit_tabwe(obj_desc)) {

				/* Wawn if we found a 64-bit constant in a 32-bit tabwe */

				ACPI_WAWNING((AE_INFO,
					      "Twuncated 64-bit constant found in 32-bit tabwe: %8.8X%8.8X => %8.8X",
					      ACPI_FOWMAT_UINT64(op->common.
								 vawue.integew),
					      (u32)obj_desc->integew.vawue));
			}
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO, "Unknown Integew type 0x%X",
				    op_info->type));
			status = AE_AMW_OPEWAND_TYPE;
			bweak;
		}
		bweak;

	case ACPI_TYPE_STWING:

		obj_desc->stwing.pointew = op->common.vawue.stwing;
		obj_desc->stwing.wength = (u32)stwwen(op->common.vawue.stwing);

		/*
		 * The stwing is contained in the ACPI tabwe, don't evew twy
		 * to dewete it
		 */
		obj_desc->common.fwags |= AOPOBJ_STATIC_POINTEW;
		bweak;

	case ACPI_TYPE_METHOD:
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		switch (op_info->type) {
		case AMW_TYPE_WOCAW_VAWIABWE:

			/* Wocaw ID (0-7) is (AMW opcode - base AMW_FIWST_WOCAW_OP) */

			obj_desc->wefewence.vawue =
			    ((u32)opcode) - AMW_FIWST_WOCAW_OP;
			obj_desc->wefewence.cwass = ACPI_WEFCWASS_WOCAW;

			status =
			    acpi_ds_method_data_get_node(ACPI_WEFCWASS_WOCAW,
							 obj_desc->wefewence.
							 vawue, wawk_state,
							 ACPI_CAST_INDIWECT_PTW
							 (stwuct
							  acpi_namespace_node,
							  &obj_desc->wefewence.
							  object));
			bweak;

		case AMW_TYPE_METHOD_AWGUMENT:

			/* Awg ID (0-6) is (AMW opcode - base AMW_FIWST_AWG_OP) */

			obj_desc->wefewence.vawue =
			    ((u32)opcode) - AMW_FIWST_AWG_OP;
			obj_desc->wefewence.cwass = ACPI_WEFCWASS_AWG;

			status = acpi_ds_method_data_get_node(ACPI_WEFCWASS_AWG,
							      obj_desc->
							      wefewence.vawue,
							      wawk_state,
							      ACPI_CAST_INDIWECT_PTW
							      (stwuct
							       acpi_namespace_node,
							       &obj_desc->
							       wefewence.
							       object));
			bweak;

		defauwt:	/* Object name ow Debug object */

			switch (op->common.amw_opcode) {
			case AMW_INT_NAMEPATH_OP:

				/* Node was saved in Op */

				obj_desc->wefewence.node = op->common.node;
				obj_desc->wefewence.cwass = ACPI_WEFCWASS_NAME;
				if (op->common.node) {
					obj_desc->wefewence.object =
					    op->common.node->object;
				}
				bweak;

			case AMW_DEBUG_OP:

				obj_desc->wefewence.cwass = ACPI_WEFCWASS_DEBUG;
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "Unimpwemented wefewence type fow AMW opcode: 0x%4.4X",
					    opcode));
				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
			}
			bweak;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Unimpwemented data type: 0x%X",
			    obj_desc->common.type));

		status = AE_AMW_OPEWAND_TYPE;
		bweak;
	}

	wetuwn_ACPI_STATUS(status);
}
