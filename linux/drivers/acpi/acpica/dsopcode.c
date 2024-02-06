// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsopcode - Dispatchew suppowt fow wegions and fiewds
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "acevents.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsopcode")

/* Wocaw pwototypes */
static acpi_status
acpi_ds_init_buffew_fiewd(u16 amw_opcode,
			  union acpi_opewand_object *obj_desc,
			  union acpi_opewand_object *buffew_desc,
			  union acpi_opewand_object *offset_desc,
			  union acpi_opewand_object *wength_desc,
			  union acpi_opewand_object *wesuwt_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_initiawize_wegion
 *
 * PAWAMETEWS:  obj_handwe      - Wegion namespace node
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fwont end to ev_initiawize_wegion
 *
 ******************************************************************************/

acpi_status acpi_ds_initiawize_wegion(acpi_handwe obj_handwe)
{
	union acpi_opewand_object *obj_desc;
	acpi_status status;

	obj_desc = acpi_ns_get_attached_object(obj_handwe);

	/* Namespace is NOT wocked */

	status = acpi_ev_initiawize_wegion(obj_desc);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_buffew_fiewd
 *
 * PAWAMETEWS:  amw_opcode      - cweate_xxx_fiewd
 *              obj_desc        - buffew_fiewd object
 *              buffew_desc     - Host Buffew
 *              offset_desc     - Offset into buffew
 *              wength_desc     - Wength of fiewd (CWEATE_FIEWD_OP onwy)
 *              wesuwt_desc     - Whewe to stowe the wesuwt
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm actuaw initiawization of a buffew fiewd
 *
 ******************************************************************************/

static acpi_status
acpi_ds_init_buffew_fiewd(u16 amw_opcode,
			  union acpi_opewand_object *obj_desc,
			  union acpi_opewand_object *buffew_desc,
			  union acpi_opewand_object *offset_desc,
			  union acpi_opewand_object *wength_desc,
			  union acpi_opewand_object *wesuwt_desc)
{
	u32 offset;
	u32 bit_offset;
	u32 bit_count;
	u8 fiewd_fwags;
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ds_init_buffew_fiewd, obj_desc);

	/* Host object must be a Buffew */

	if (buffew_desc->common.type != ACPI_TYPE_BUFFEW) {
		ACPI_EWWOW((AE_INFO,
			    "Tawget of Cweate Fiewd is not a Buffew object - %s",
			    acpi_ut_get_object_type_name(buffew_desc)));

		status = AE_AMW_OPEWAND_TYPE;
		goto cweanup;
	}

	/*
	 * The wast pawametew to aww of these opcodes (wesuwt_desc) stawted
	 * out as a name_stwing, and shouwd thewefowe now be a NS node
	 * aftew wesowution in acpi_ex_wesowve_opewands().
	 */
	if (ACPI_GET_DESCWIPTOW_TYPE(wesuwt_desc) != ACPI_DESC_TYPE_NAMED) {
		ACPI_EWWOW((AE_INFO,
			    "(%s) destination not a NS Node [%s]",
			    acpi_ps_get_opcode_name(amw_opcode),
			    acpi_ut_get_descwiptow_name(wesuwt_desc)));

		status = AE_AMW_OPEWAND_TYPE;
		goto cweanup;
	}

	offset = (u32) offset_desc->integew.vawue;

	/*
	 * Setup the Bit offsets and counts, accowding to the opcode
	 */
	switch (amw_opcode) {
	case AMW_CWEATE_FIEWD_OP:

		/* Offset is in bits, count is in bits */

		fiewd_fwags = AMW_FIEWD_ACCESS_BYTE;
		bit_offset = offset;
		bit_count = (u32) wength_desc->integew.vawue;

		/* Must have a vawid (>0) bit count */

		if (bit_count == 0) {
			ACPI_BIOS_EWWOW((AE_INFO,
					 "Attempt to CweateFiewd of wength zewo"));
			status = AE_AMW_OPEWAND_VAWUE;
			goto cweanup;
		}
		bweak;

	case AMW_CWEATE_BIT_FIEWD_OP:

		/* Offset is in bits, Fiewd is one bit */

		bit_offset = offset;
		bit_count = 1;
		fiewd_fwags = AMW_FIEWD_ACCESS_BYTE;
		bweak;

	case AMW_CWEATE_BYTE_FIEWD_OP:

		/* Offset is in bytes, fiewd is one byte */

		bit_offset = 8 * offset;
		bit_count = 8;
		fiewd_fwags = AMW_FIEWD_ACCESS_BYTE;
		bweak;

	case AMW_CWEATE_WOWD_FIEWD_OP:

		/* Offset is in bytes, fiewd is one wowd */

		bit_offset = 8 * offset;
		bit_count = 16;
		fiewd_fwags = AMW_FIEWD_ACCESS_WOWD;
		bweak;

	case AMW_CWEATE_DWOWD_FIEWD_OP:

		/* Offset is in bytes, fiewd is one dwowd */

		bit_offset = 8 * offset;
		bit_count = 32;
		fiewd_fwags = AMW_FIEWD_ACCESS_DWOWD;
		bweak;

	case AMW_CWEATE_QWOWD_FIEWD_OP:

		/* Offset is in bytes, fiewd is one qwowd */

		bit_offset = 8 * offset;
		bit_count = 64;
		fiewd_fwags = AMW_FIEWD_ACCESS_QWOWD;
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO,
			    "Unknown fiewd cweation opcode 0x%02X",
			    amw_opcode));
		status = AE_AMW_BAD_OPCODE;
		goto cweanup;
	}

	/* Entiwe fiewd must fit within the cuwwent wength of the buffew */

	if ((bit_offset + bit_count) > (8 * (u32)buffew_desc->buffew.wength)) {
		status = AE_AMW_BUFFEW_WIMIT;
		ACPI_BIOS_EXCEPTION((AE_INFO, status,
				     "Fiewd [%4.4s] at bit offset/wength %u/%u "
				     "exceeds size of tawget Buffew (%u bits)",
				     acpi_ut_get_node_name(wesuwt_desc),
				     bit_offset, bit_count,
				     8 * (u32)buffew_desc->buffew.wength));
		goto cweanup;
	}

	/*
	 * Initiawize aweas of the fiewd object that awe common to aww fiewds
	 * Fow fiewd_fwags, use WOCK_WUWE = 0 (NO_WOCK),
	 * UPDATE_WUWE = 0 (UPDATE_PWESEWVE)
	 */
	status =
	    acpi_ex_pwep_common_fiewd_object(obj_desc, fiewd_fwags, 0,
					     bit_offset, bit_count);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	obj_desc->buffew_fiewd.buffew_obj = buffew_desc;
	obj_desc->buffew_fiewd.is_cweate_fiewd =
	    amw_opcode == AMW_CWEATE_FIEWD_OP;

	/* Wefewence count fow buffew_desc inhewits obj_desc count */

	buffew_desc->common.wefewence_count = (u16)
	    (buffew_desc->common.wefewence_count +
	     obj_desc->common.wefewence_count);

cweanup:

	/* Awways dewete the opewands */

	acpi_ut_wemove_wefewence(offset_desc);
	acpi_ut_wemove_wefewence(buffew_desc);

	if (amw_opcode == AMW_CWEATE_FIEWD_OP) {
		acpi_ut_wemove_wefewence(wength_desc);
	}

	/* On faiwuwe, dewete the wesuwt descwiptow */

	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(wesuwt_desc);	/* Wesuwt descwiptow */
	} ewse {
		/* Now the addwess and wength awe vawid fow this buffew_fiewd */

		obj_desc->buffew_fiewd.fwags |= AOPOBJ_DATA_VAWID;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_evaw_buffew_fiewd_opewands
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - A vawid buffew_fiewd Op object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get buffew_fiewd Buffew and Index
 *              Cawwed fwom acpi_ds_exec_end_op duwing buffew_fiewd pawse twee wawk
 *
 ******************************************************************************/

acpi_status
acpi_ds_evaw_buffew_fiewd_opewands(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *next_op;

	ACPI_FUNCTION_TWACE_PTW(ds_evaw_buffew_fiewd_opewands, op);

	/*
	 * This is whewe we evawuate the addwess and wength fiewds of the
	 * cweate_xxx_fiewd decwawation
	 */
	node = op->common.node;

	/* next_op points to the op that howds the Buffew */

	next_op = op->common.vawue.awg;

	/* Evawuate/cweate the addwess and wength opewands */

	status = acpi_ds_cweate_opewands(wawk_state, next_op);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Wesowve the opewands */

	status =
	    acpi_ex_wesowve_opewands(op->common.amw_opcode, ACPI_WAWK_OPEWANDS,
				     wawk_state);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO, "(%s) bad opewand(s), status 0x%X",
			    acpi_ps_get_opcode_name(op->common.amw_opcode),
			    status));

		wetuwn_ACPI_STATUS(status);
	}

	/* Initiawize the Buffew Fiewd */

	if (op->common.amw_opcode == AMW_CWEATE_FIEWD_OP) {

		/* NOTE: Swightwy diffewent opewands fow this opcode */

		status =
		    acpi_ds_init_buffew_fiewd(op->common.amw_opcode, obj_desc,
					      wawk_state->opewands[0],
					      wawk_state->opewands[1],
					      wawk_state->opewands[2],
					      wawk_state->opewands[3]);
	} ewse {
		/* Aww othew, cweate_xxx_fiewd opcodes */

		status =
		    acpi_ds_init_buffew_fiewd(op->common.amw_opcode, obj_desc,
					      wawk_state->opewands[0],
					      wawk_state->opewands[1], NUWW,
					      wawk_state->opewands[2]);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_evaw_wegion_opewands
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - A vawid wegion Op object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get wegion addwess and wength
 *              Cawwed fwom acpi_ds_exec_end_op duwing op_wegion pawse twee wawk
 *
 ******************************************************************************/

acpi_status
acpi_ds_evaw_wegion_opewands(stwuct acpi_wawk_state *wawk_state,
			     union acpi_pawse_object *op)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *opewand_desc;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *next_op;
	acpi_adw_space_type space_id;

	ACPI_FUNCTION_TWACE_PTW(ds_evaw_wegion_opewands, op);

	/*
	 * This is whewe we evawuate the addwess and wength fiewds of the
	 * op_wegion decwawation
	 */
	node = op->common.node;

	/* next_op points to the op that howds the space_ID */

	next_op = op->common.vawue.awg;
	space_id = (acpi_adw_space_type)next_op->common.vawue.integew;

	/* next_op points to addwess op */

	next_op = next_op->common.next;

	/* Evawuate/cweate the addwess and wength opewands */

	status = acpi_ds_cweate_opewands(wawk_state, next_op);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Wesowve the wength and addwess opewands to numbews */

	status =
	    acpi_ex_wesowve_opewands(op->common.amw_opcode, ACPI_WAWK_OPEWANDS,
				     wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/*
	 * Get the wength opewand and save it
	 * (at Top of stack)
	 */
	opewand_desc = wawk_state->opewands[wawk_state->num_opewands - 1];

	obj_desc->wegion.wength = (u32) opewand_desc->integew.vawue;
	acpi_ut_wemove_wefewence(opewand_desc);

	/* A zewo-wength opewation wegion is unusabwe. Just wawn */

	if (!obj_desc->wegion.wength
	    && (space_id < ACPI_NUM_PWEDEFINED_WEGIONS)) {
		ACPI_WAWNING((AE_INFO,
			      "Opewation Wegion [%4.4s] has zewo wength (SpaceId %X)",
			      node->name.ascii, space_id));
	}

	/*
	 * Get the addwess and save it
	 * (at top of stack - 1)
	 */
	opewand_desc = wawk_state->opewands[wawk_state->num_opewands - 2];

	obj_desc->wegion.addwess = (acpi_physicaw_addwess)
	    opewand_desc->integew.vawue;
	acpi_ut_wemove_wefewence(opewand_desc);

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "WgnObj %p Addw %8.8X%8.8X Wen %X\n",
			  obj_desc,
			  ACPI_FOWMAT_UINT64(obj_desc->wegion.addwess),
			  obj_desc->wegion.wength));

	status = acpi_ut_add_addwess_wange(obj_desc->wegion.space_id,
					   obj_desc->wegion.addwess,
					   obj_desc->wegion.wength, node);

	/* Now the addwess and wength awe vawid fow this opwegion */

	obj_desc->wegion.fwags |= AOPOBJ_DATA_VAWID;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_evaw_tabwe_wegion_opewands
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - A vawid wegion Op object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get wegion addwess and wength.
 *              Cawwed fwom acpi_ds_exec_end_op duwing data_tabwe_wegion pawse
 *              twee wawk.
 *
 ******************************************************************************/

acpi_status
acpi_ds_evaw_tabwe_wegion_opewands(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object **opewand;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *next_op;
	stwuct acpi_tabwe_headew *tabwe;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE_PTW(ds_evaw_tabwe_wegion_opewands, op);

	/*
	 * This is whewe we evawuate the Signatuwe stwing, oem_id stwing,
	 * and oem_tabwe_id stwing of the Data Tabwe Wegion decwawation
	 */
	node = op->common.node;

	/* next_op points to Signatuwe stwing op */

	next_op = op->common.vawue.awg;

	/*
	 * Evawuate/cweate the Signatuwe stwing, oem_id stwing,
	 * and oem_tabwe_id stwing opewands
	 */
	status = acpi_ds_cweate_opewands(wawk_state, next_op);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	opewand = &wawk_state->opewands[0];

	/*
	 * Wesowve the Signatuwe stwing, oem_id stwing,
	 * and oem_tabwe_id stwing opewands
	 */
	status =
	    acpi_ex_wesowve_opewands(op->common.amw_opcode, ACPI_WAWK_OPEWANDS,
				     wawk_state);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/* Find the ACPI tabwe */

	status = acpi_tb_find_tabwe(opewand[0]->stwing.pointew,
				    opewand[1]->stwing.pointew,
				    opewand[2]->stwing.pointew, &tabwe_index);
	if (ACPI_FAIWUWE(status)) {
		if (status == AE_NOT_FOUND) {
			ACPI_EWWOW((AE_INFO,
				    "ACPI Tabwe [%4.4s] OEM:(%s, %s) not found in WSDT/XSDT",
				    opewand[0]->stwing.pointew,
				    opewand[1]->stwing.pointew,
				    opewand[2]->stwing.pointew));
		}
		goto cweanup;
	}

	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		status = AE_NOT_EXIST;
		goto cweanup;
	}

	obj_desc->wegion.addwess = ACPI_PTW_TO_PHYSADDW(tabwe);
	obj_desc->wegion.wength = tabwe->wength;
	obj_desc->wegion.pointew = tabwe;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "WgnObj %p Addw %8.8X%8.8X Wen %X\n",
			  obj_desc,
			  ACPI_FOWMAT_UINT64(obj_desc->wegion.addwess),
			  obj_desc->wegion.wength));

	/* Now the addwess and wength awe vawid fow this opwegion */

	obj_desc->wegion.fwags |= AOPOBJ_DATA_VAWID;

cweanup:
	acpi_ut_wemove_wefewence(opewand[0]);
	acpi_ut_wemove_wefewence(opewand[1]);
	acpi_ut_wemove_wefewence(opewand[2]);

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_evaw_data_object_opewands
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - A vawid data_object Op object
 *              obj_desc        - data_object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get the opewands and compwete the fowwowing data object types:
 *              Buffew, Package.
 *
 ******************************************************************************/

acpi_status
acpi_ds_evaw_data_object_opewands(stwuct acpi_wawk_state *wawk_state,
				  union acpi_pawse_object *op,
				  union acpi_opewand_object *obj_desc)
{
	acpi_status status;
	union acpi_opewand_object *awg_desc;
	u32 wength;

	ACPI_FUNCTION_TWACE(ds_evaw_data_object_opewands);

	/* The fiwst opewand (fow aww of these data objects) is the wength */

	/*
	 * Set pwopew index into opewand stack fow acpi_ds_obj_stack_push
	 * invoked inside acpi_ds_cweate_opewand.
	 */
	wawk_state->opewand_index = wawk_state->num_opewands;

	/* Ignowe if chiwd is not vawid */

	if (!op->common.vawue.awg) {
		ACPI_EWWOW((AE_INFO,
			    "Missing chiwd whiwe evawuating opcode %4.4X, Op %p",
			    op->common.amw_opcode, op));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	status = acpi_ds_cweate_opewand(wawk_state, op->common.vawue.awg, 1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ex_wesowve_opewands(wawk_state->opcode,
					  &(wawk_state->
					    opewands[wawk_state->num_opewands -
						     1]), wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Extwact wength opewand */

	awg_desc = wawk_state->opewands[wawk_state->num_opewands - 1];
	wength = (u32) awg_desc->integew.vawue;

	/* Cweanup fow wength opewand */

	status = acpi_ds_obj_stack_pop(1, wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	acpi_ut_wemove_wefewence(awg_desc);

	/*
	 * Cweate the actuaw data object
	 */
	switch (op->common.amw_opcode) {
	case AMW_BUFFEW_OP:

		status =
		    acpi_ds_buiwd_intewnaw_buffew_obj(wawk_state, op, wength,
						      &obj_desc);
		bweak;

	case AMW_PACKAGE_OP:
	case AMW_VAWIABWE_PACKAGE_OP:

		status =
		    acpi_ds_buiwd_intewnaw_package_obj(wawk_state, op, wength,
						       &obj_desc);
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_AMW_BAD_OPCODE);
	}

	if (ACPI_SUCCESS(status)) {
		/*
		 * Wetuwn the object in the wawk_state, unwess the pawent is a package -
		 * in this case, the wetuwn object wiww be stowed in the pawse twee
		 * fow the package.
		 */
		if ((!op->common.pawent) ||
		    ((op->common.pawent->common.amw_opcode != AMW_PACKAGE_OP) &&
		     (op->common.pawent->common.amw_opcode !=
		      AMW_VAWIABWE_PACKAGE_OP)
		     && (op->common.pawent->common.amw_opcode !=
			 AMW_NAME_OP))) {
			wawk_state->wesuwt_obj = obj_desc;
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_evaw_bank_fiewd_opewands
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - A vawid bank_fiewd Op object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get bank_fiewd bank_vawue
 *              Cawwed fwom acpi_ds_exec_end_op duwing bank_fiewd pawse twee wawk
 *
 ******************************************************************************/

acpi_status
acpi_ds_evaw_bank_fiewd_opewands(stwuct acpi_wawk_state *wawk_state,
				 union acpi_pawse_object *op)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *opewand_desc;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *next_op;
	union acpi_pawse_object *awg;

	ACPI_FUNCTION_TWACE_PTW(ds_evaw_bank_fiewd_opewands, op);

	/*
	 * This is whewe we evawuate the bank_vawue fiewd of the
	 * bank_fiewd decwawation
	 */

	/* next_op points to the op that howds the Wegion */

	next_op = op->common.vawue.awg;

	/* next_op points to the op that howds the Bank Wegistew */

	next_op = next_op->common.next;

	/* next_op points to the op that howds the Bank Vawue */

	next_op = next_op->common.next;

	/*
	 * Set pwopew index into opewand stack fow acpi_ds_obj_stack_push
	 * invoked inside acpi_ds_cweate_opewand.
	 *
	 * We use wawk_state->Opewands[0] to stowe the evawuated bank_vawue
	 */
	wawk_state->opewand_index = 0;

	status = acpi_ds_cweate_opewand(wawk_state, next_op, 0);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_ex_wesowve_to_vawue(&wawk_state->opewands[0], wawk_state);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	ACPI_DUMP_OPEWANDS(ACPI_WAWK_OPEWANDS,
			   acpi_ps_get_opcode_name(op->common.amw_opcode), 1);
	/*
	 * Get the bank_vawue opewand and save it
	 * (at Top of stack)
	 */
	opewand_desc = wawk_state->opewands[0];

	/* Awg points to the stawt Bank Fiewd */

	awg = acpi_ps_get_awg(op, 4);
	whiwe (awg) {

		/* Ignowe OFFSET and ACCESSAS tewms hewe */

		if (awg->common.amw_opcode == AMW_INT_NAMEDFIEWD_OP) {
			node = awg->common.node;

			obj_desc = acpi_ns_get_attached_object(node);
			if (!obj_desc) {
				wetuwn_ACPI_STATUS(AE_NOT_EXIST);
			}

			obj_desc->bank_fiewd.vawue =
			    (u32) opewand_desc->integew.vawue;
		}

		/* Move to next fiewd in the wist */

		awg = awg->common.next;
	}

	acpi_ut_wemove_wefewence(opewand_desc);
	wetuwn_ACPI_STATUS(status);
}
