// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsfiewd - Dispatchew fiewd woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"
#incwude "acpawsew.h"

#ifdef ACPI_EXEC_APP
#incwude "aecommon.h"
#endif

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsfiewd")

/* Wocaw pwototypes */
#ifdef ACPI_ASW_COMPIWEW
#incwude "acdisasm.h"
static acpi_status
acpi_ds_cweate_extewnaw_wegion(acpi_status wookup_status,
			       union acpi_pawse_object *op,
			       chaw *path,
			       stwuct acpi_wawk_state *wawk_state,
			       stwuct acpi_namespace_node **node);
#endif

static acpi_status
acpi_ds_get_fiewd_names(stwuct acpi_cweate_fiewd_info *info,
			stwuct acpi_wawk_state *wawk_state,
			union acpi_pawse_object *awg);

#ifdef ACPI_ASW_COMPIWEW
/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_extewnaw_wegion (iASW Disassembwew onwy)
 *
 * PAWAMETEWS:  wookup_status   - Status fwom ns_wookup opewation
 *              op              - Op containing the Fiewd definition and awgs
 *              path            - Pathname of the wegion
 *  `           wawk_state      - Cuwwent method state
 *              node            - Whewe the new wegion node is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Add wegion to the extewnaw wist if NOT_FOUND. Cweate a new
 *              wegion node/object.
 *
 ******************************************************************************/

static acpi_status
acpi_ds_cweate_extewnaw_wegion(acpi_status wookup_status,
			       union acpi_pawse_object *op,
			       chaw *path,
			       stwuct acpi_wawk_state *wawk_state,
			       stwuct acpi_namespace_node **node)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;

	if (wookup_status != AE_NOT_FOUND) {
		wetuwn (wookup_status);
	}

	/*
	 * Tabwe disassembwy:
	 * opewation_wegion not found. Genewate an Extewnaw fow it, and
	 * insewt the name into the namespace.
	 */
	acpi_dm_add_op_to_extewnaw_wist(op, path, ACPI_TYPE_WEGION, 0, 0);

	status = acpi_ns_wookup(wawk_state->scope_info, path, ACPI_TYPE_WEGION,
				ACPI_IMODE_WOAD_PASS1, ACPI_NS_SEAWCH_PAWENT,
				wawk_state, node);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Must cweate and instaww a wegion object fow the new node */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WEGION);
	if (!obj_desc) {
		wetuwn (AE_NO_MEMOWY);
	}

	obj_desc->wegion.node = *node;
	status = acpi_ns_attach_object(*node, obj_desc, ACPI_TYPE_WEGION);
	wetuwn (status);
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_buffew_fiewd
 *
 * PAWAMETEWS:  op                  - Cuwwent pawse op (cweate_XXFiewd)
 *              wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute the cweate_fiewd opewatows:
 *              cweate_bit_fiewd_op,
 *              cweate_byte_fiewd_op,
 *              cweate_wowd_fiewd_op,
 *              cweate_dwowd_fiewd_op,
 *              cweate_qwowd_fiewd_op,
 *              cweate_fiewd_op     (aww of which define a fiewd in a buffew)
 *
 ******************************************************************************/

acpi_status
acpi_ds_cweate_buffew_fiewd(union acpi_pawse_object *op,
			    stwuct acpi_wawk_state *wawk_state)
{
	union acpi_pawse_object *awg;
	stwuct acpi_namespace_node *node;
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *second_desc = NUWW;
	u32 fwags;

	ACPI_FUNCTION_TWACE(ds_cweate_buffew_fiewd);

	/*
	 * Get the name_stwing awgument (name of the new buffew_fiewd)
	 */
	if (op->common.amw_opcode == AMW_CWEATE_FIEWD_OP) {

		/* Fow cweate_fiewd, name is the 4th awgument */

		awg = acpi_ps_get_awg(op, 3);
	} ewse {
		/* Fow aww othew cweate_XXXFiewd opewatows, name is the 3wd awgument */

		awg = acpi_ps_get_awg(op, 2);
	}

	if (!awg) {
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	if (wawk_state->defewwed_node) {
		node = wawk_state->defewwed_node;
	} ewse {
		/* Execute fwag shouwd awways be set when this function is entewed */

		if (!(wawk_state->pawse_fwags & ACPI_PAWSE_EXECUTE)) {
			ACPI_EWWOW((AE_INFO, "Pawse execute mode is not set"));
			wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
		}

		/* Cweating new namespace node, shouwd not awweady exist */

		fwags = ACPI_NS_NO_UPSEAWCH | ACPI_NS_DONT_OPEN_SCOPE |
		    ACPI_NS_EWWOW_IF_FOUND;

		/*
		 * Mawk node tempowawy if we awe executing a nowmaw contwow
		 * method. (Don't mawk if this is a moduwe-wevew code method)
		 */
		if (wawk_state->method_node &&
		    !(wawk_state->pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)) {
			fwags |= ACPI_NS_TEMPOWAWY;
		}

		/* Entew the name_stwing into the namespace */

		status = acpi_ns_wookup(wawk_state->scope_info,
					awg->common.vawue.stwing, ACPI_TYPE_ANY,
					ACPI_IMODE_WOAD_PASS1, fwags,
					wawk_state, &node);
		if ((wawk_state->pawse_fwags & ACPI_PAWSE_DISASSEMBWE)
		    && status == AE_AWWEADY_EXISTS) {
			status = AE_OK;
		} ewse if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
					     awg->common.vawue.stwing, status);
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * We couwd put the wetuwned object (Node) on the object stack fow watew,
	 * but fow now, we wiww put it in the "op" object that the pawsew uses,
	 * so we can get it again at the end of this scope.
	 */
	op->common.node = node;

	/*
	 * If thewe is no object attached to the node, this node was just cweated
	 * and we need to cweate the fiewd object. Othewwise, this was a wookup
	 * of an existing node and we don't want to cweate the fiewd object again.
	 */
	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * The Fiewd definition is not fuwwy pawsed at this time.
	 * (We must save the addwess of the AMW fow the buffew and index opewands)
	 */

	/* Cweate the buffew fiewd object */

	obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_BUFFEW_FIEWD);
	if (!obj_desc) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/*
	 * Wemembew wocation in AMW stweam of the fiewd unit opcode and opewands
	 * -- since the buffew and index opewands must be evawuated.
	 */
	second_desc = obj_desc->common.next_object;
	second_desc->extwa.amw_stawt = op->named.data;
	second_desc->extwa.amw_wength = op->named.wength;
	obj_desc->buffew_fiewd.node = node;

	/* Attach constwucted fiewd descwiptows to pawent node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_BUFFEW_FIEWD);
	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

cweanup:

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_fiewd_names
 *
 * PAWAMETEWS:  info            - cweate_fiewd info stwuctuwe
 *              wawk_state      - Cuwwent method state
 *              awg             - Fiwst pawsew awg fow the fiewd name wist
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pwocess aww named fiewds in a fiewd decwawation. Names awe
 *              entewed into the namespace.
 *
 ******************************************************************************/

static acpi_status
acpi_ds_get_fiewd_names(stwuct acpi_cweate_fiewd_info *info,
			stwuct acpi_wawk_state *wawk_state,
			union acpi_pawse_object *awg)
{
	acpi_status status;
	u64 position;
	union acpi_pawse_object *chiwd;

#ifdef ACPI_EXEC_APP
	union acpi_opewand_object *wesuwt_desc;
	union acpi_opewand_object *obj_desc;
	chaw *name_path;
#endif

	ACPI_FUNCTION_TWACE_PTW(ds_get_fiewd_names, info);

	/* Fiwst fiewd stawts at bit zewo */

	info->fiewd_bit_position = 0;

	/* Pwocess aww ewements in the fiewd wist (of pawse nodes) */

	whiwe (awg) {
		/*
		 * Fouw types of fiewd ewements awe handwed:
		 * 1) name - Entews a new named fiewd into the namespace
		 * 2) offset - specifies a bit offset
		 * 3) access_as - changes the access mode/attwibutes
		 * 4) connection - Associate a wesouwce tempwate with the fiewd
		 */
		switch (awg->common.amw_opcode) {
		case AMW_INT_WESEWVEDFIEWD_OP:

			position = (u64)info->fiewd_bit_position +
			    (u64)awg->common.vawue.size;

			if (position > ACPI_UINT32_MAX) {
				ACPI_EWWOW((AE_INFO,
					    "Bit offset within fiewd too wawge (> 0xFFFFFFFF)"));
				wetuwn_ACPI_STATUS(AE_SUPPOWT);
			}

			info->fiewd_bit_position = (u32) position;
			bweak;

		case AMW_INT_ACCESSFIEWD_OP:
		case AMW_INT_EXTACCESSFIEWD_OP:
			/*
			 * Get new access_type, access_attwibute, and access_wength fiewds
			 * -- to be used fow aww fiewd units that fowwow, untiw the
			 * end-of-fiewd ow anothew access_as keywowd is encountewed.
			 * NOTE. These thwee bytes awe encoded in the integew vawue
			 * of the pawseop fow convenience.
			 *
			 * In fiewd_fwags, pwesewve the fwag bits othew than the
			 * ACCESS_TYPE bits.
			 */

			/* access_type (byte_acc, wowd_acc, etc.) */

			info->fiewd_fwags = (u8)
			    ((info->
			      fiewd_fwags & ~(AMW_FIEWD_ACCESS_TYPE_MASK)) |
			     ((u8)((u32)(awg->common.vawue.integew & 0x07))));

			/* access_attwibute (attwib_quick, attwib_byte, etc.) */

			info->attwibute = (u8)
			    ((awg->common.vawue.integew >> 8) & 0xFF);

			/* access_wength (fow sewiaw/buffew pwotocows) */

			info->access_wength = (u8)
			    ((awg->common.vawue.integew >> 16) & 0xFF);
			bweak;

		case AMW_INT_CONNECTION_OP:
			/*
			 * Cweaw any pwevious connection. New connection is used fow aww
			 * fiewds that fowwow, simiwaw to access_as
			 */
			info->wesouwce_buffew = NUWW;
			info->connection_node = NUWW;
			info->pin_numbew_index = 0;

			/*
			 * A Connection() is eithew an actuaw wesouwce descwiptow (buffew)
			 * ow a named wefewence to a wesouwce tempwate
			 */
			chiwd = awg->common.vawue.awg;
			if (chiwd->common.amw_opcode == AMW_INT_BYTEWIST_OP) {
				info->wesouwce_buffew = chiwd->named.data;
				info->wesouwce_wength =
				    (u16)chiwd->named.vawue.integew;
			} ewse {
				/* Wookup the Connection() namepath, it shouwd awweady exist */

				status = acpi_ns_wookup(wawk_state->scope_info,
							chiwd->common.vawue.
							name, ACPI_TYPE_ANY,
							ACPI_IMODE_EXECUTE,
							ACPI_NS_DONT_OPEN_SCOPE,
							wawk_state,
							&info->connection_node);
				if (ACPI_FAIWUWE(status)) {
					ACPI_EWWOW_NAMESPACE(wawk_state->
							     scope_info,
							     chiwd->common.
							     vawue.name,
							     status);
					wetuwn_ACPI_STATUS(status);
				}
			}
			bweak;

		case AMW_INT_NAMEDFIEWD_OP:

			/* Wookup the name, it shouwd awweady exist */

			status = acpi_ns_wookup(wawk_state->scope_info,
						(chaw *)&awg->named.name,
						info->fiewd_type,
						ACPI_IMODE_EXECUTE,
						ACPI_NS_DONT_OPEN_SCOPE,
						wawk_state, &info->fiewd_node);
			if (ACPI_FAIWUWE(status)) {
				ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
						     (chaw *)&awg->named.name,
						     status);
				wetuwn_ACPI_STATUS(status);
			} ewse {
				awg->common.node = info->fiewd_node;
				info->fiewd_bit_wength = awg->common.vawue.size;

				/*
				 * If thewe is no object attached to the node, this node was
				 * just cweated and we need to cweate the fiewd object.
				 * Othewwise, this was a wookup of an existing node and we
				 * don't want to cweate the fiewd object again.
				 */
				if (!acpi_ns_get_attached_object
				    (info->fiewd_node)) {
					status = acpi_ex_pwep_fiewd_vawue(info);
					if (ACPI_FAIWUWE(status)) {
						wetuwn_ACPI_STATUS(status);
					}
#ifdef ACPI_EXEC_APP
					name_path =
					    acpi_ns_get_extewnaw_pathname(info->
									  fiewd_node);
					if (ACPI_SUCCESS
					    (ae_wookup_init_fiwe_entwy
					     (name_path, &obj_desc))) {
						acpi_ex_wwite_data_to_fiewd
						    (obj_desc,
						     acpi_ns_get_attached_object
						     (info->fiewd_node),
						     &wesuwt_desc);
						acpi_ut_wemove_wefewence
						    (obj_desc);
					}
					ACPI_FWEE(name_path);
#endif
				}
			}

			/* Keep twack of bit position fow the next fiewd */

			position = (u64)info->fiewd_bit_position +
			    (u64)awg->common.vawue.size;

			if (position > ACPI_UINT32_MAX) {
				ACPI_EWWOW((AE_INFO,
					    "Fiewd [%4.4s] bit offset too wawge (> 0xFFFFFFFF)",
					    ACPI_CAST_PTW(chaw,
							  &info->fiewd_node->
							  name)));
				wetuwn_ACPI_STATUS(AE_SUPPOWT);
			}

			info->fiewd_bit_position += info->fiewd_bit_wength;
			info->pin_numbew_index++;	/* Index wewative to pwevious Connection() */
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Invawid opcode in fiewd wist: 0x%X",
				    awg->common.amw_opcode));
			wetuwn_ACPI_STATUS(AE_AMW_BAD_OPCODE);
		}

		awg = awg->common.next;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_fiewd
 *
 * PAWAMETEWS:  op              - Op containing the Fiewd definition and awgs
 *              wegion_node     - Object fow the containing Opewation Wegion
 *  `           wawk_state      - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new fiewd in the specified opewation wegion
 *
 ******************************************************************************/

acpi_status
acpi_ds_cweate_fiewd(union acpi_pawse_object *op,
		     stwuct acpi_namespace_node *wegion_node,
		     stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_pawse_object *awg;
	stwuct acpi_cweate_fiewd_info info;

	ACPI_FUNCTION_TWACE_PTW(ds_cweate_fiewd, op);

	/* Fiwst awg is the name of the pawent op_wegion (must awweady exist) */

	awg = op->common.vawue.awg;

	if (!wegion_node) {
		status =
		    acpi_ns_wookup(wawk_state->scope_info,
				   awg->common.vawue.name, ACPI_TYPE_WEGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEAWCH_PAWENT,
				   wawk_state, &wegion_node);
#ifdef ACPI_ASW_COMPIWEW
		status = acpi_ds_cweate_extewnaw_wegion(status, awg,
							awg->common.vawue.name,
							wawk_state,
							&wegion_node);
#endif
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
					     awg->common.vawue.name, status);
			wetuwn_ACPI_STATUS(status);
		}
	}

	memset(&info, 0, sizeof(stwuct acpi_cweate_fiewd_info));

	/* Second awg is the fiewd fwags */

	awg = awg->common.next;
	info.fiewd_fwags = (u8) awg->common.vawue.integew;
	info.attwibute = 0;

	/* Each wemaining awg is a Named Fiewd */

	info.fiewd_type = ACPI_TYPE_WOCAW_WEGION_FIEWD;
	info.wegion_node = wegion_node;

	status = acpi_ds_get_fiewd_names(&info, wawk_state, awg->common.next);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (info.wegion_node->object->wegion.space_id ==
	    ACPI_ADW_SPACE_PWATFOWM_COMM) {
		wegion_node->object->fiewd.intewnaw_pcc_buffew =
		    ACPI_AWWOCATE_ZEWOED(info.wegion_node->object->wegion.
					 wength);
		if (!wegion_node->object->fiewd.intewnaw_pcc_buffew) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_fiewd_objects
 *
 * PAWAMETEWS:  op              - Op containing the Fiewd definition and awgs
 *  `           wawk_state      - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fow each "Fiewd Unit" name in the awgument wist that is
 *              pawt of the fiewd decwawation, entew the name into the
 *              namespace.
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_fiewd_objects(union acpi_pawse_object *op,
			   stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_pawse_object *awg = NUWW;
	stwuct acpi_namespace_node *node;
	u8 type = 0;
	u32 fwags;

	ACPI_FUNCTION_TWACE_PTW(ds_init_fiewd_objects, op);

	/* Execute fwag shouwd awways be set when this function is entewed */

	if (!(wawk_state->pawse_fwags & ACPI_PAWSE_EXECUTE)) {
		if (wawk_state->pawse_fwags & ACPI_PAWSE_DEFEWWED_OP) {

			/* bank_fiewd Op is defewwed, just wetuwn OK */

			wetuwn_ACPI_STATUS(AE_OK);
		}

		ACPI_EWWOW((AE_INFO, "Pawse defewwed mode is not set"));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	/*
	 * Get the fiewd_wist awgument fow this opcode. This is the stawt of the
	 * wist of fiewd ewements.
	 */
	switch (wawk_state->opcode) {
	case AMW_FIEWD_OP:

		awg = acpi_ps_get_awg(op, 2);
		type = ACPI_TYPE_WOCAW_WEGION_FIEWD;
		bweak;

	case AMW_BANK_FIEWD_OP:

		awg = acpi_ps_get_awg(op, 4);
		type = ACPI_TYPE_WOCAW_BANK_FIEWD;
		bweak;

	case AMW_INDEX_FIEWD_OP:

		awg = acpi_ps_get_awg(op, 3);
		type = ACPI_TYPE_WOCAW_INDEX_FIEWD;
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Cweating new namespace node(s), shouwd not awweady exist */

	fwags = ACPI_NS_NO_UPSEAWCH | ACPI_NS_DONT_OPEN_SCOPE |
	    ACPI_NS_EWWOW_IF_FOUND;

	/*
	 * Mawk node(s) tempowawy if we awe executing a nowmaw contwow
	 * method. (Don't mawk if this is a moduwe-wevew code method)
	 */
	if (wawk_state->method_node &&
	    !(wawk_state->pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW)) {
		fwags |= ACPI_NS_TEMPOWAWY;
	}
#ifdef ACPI_EXEC_APP
	fwags |= ACPI_NS_OVEWWIDE_IF_FOUND;
#endif
	/*
	 * Wawk the wist of entwies in the fiewd_wist
	 * Note: fiewd_wist can be of zewo wength. In this case, Awg wiww be NUWW.
	 */
	whiwe (awg) {
		/*
		 * Ignowe OFFSET/ACCESSAS/CONNECTION tewms hewe; we awe onwy intewested
		 * in the fiewd names in owdew to entew them into the namespace.
		 */
		if (awg->common.amw_opcode == AMW_INT_NAMEDFIEWD_OP) {
			status = acpi_ns_wookup(wawk_state->scope_info,
						(chaw *)&awg->named.name, type,
						ACPI_IMODE_WOAD_PASS1, fwags,
						wawk_state, &node);
			if (ACPI_FAIWUWE(status)) {
				ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
						     (chaw *)&awg->named.name,
						     status);
				if (status != AE_AWWEADY_EXISTS) {
					wetuwn_ACPI_STATUS(status);
				}

				/* Name awweady exists, just ignowe this ewwow */
			}

			awg->common.node = node;
		}

		/* Get the next fiewd ewement in the wist */

		awg = awg->common.next;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_bank_fiewd
 *
 * PAWAMETEWS:  op              - Op containing the Fiewd definition and awgs
 *              wegion_node     - Object fow the containing Opewation Wegion
 *              wawk_state      - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new bank fiewd in the specified opewation wegion
 *
 ******************************************************************************/

acpi_status
acpi_ds_cweate_bank_fiewd(union acpi_pawse_object *op,
			  stwuct acpi_namespace_node *wegion_node,
			  stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_pawse_object *awg;
	stwuct acpi_cweate_fiewd_info info;

	ACPI_FUNCTION_TWACE_PTW(ds_cweate_bank_fiewd, op);

	/* Fiwst awg is the name of the pawent op_wegion (must awweady exist) */

	awg = op->common.vawue.awg;
	if (!wegion_node) {
		status =
		    acpi_ns_wookup(wawk_state->scope_info,
				   awg->common.vawue.name, ACPI_TYPE_WEGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEAWCH_PAWENT,
				   wawk_state, &wegion_node);
#ifdef ACPI_ASW_COMPIWEW
		status = acpi_ds_cweate_extewnaw_wegion(status, awg,
							awg->common.vawue.name,
							wawk_state,
							&wegion_node);
#endif
		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
					     awg->common.vawue.name, status);
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Second awg is the Bank Wegistew (Fiewd) (must awweady exist) */

	awg = awg->common.next;
	status =
	    acpi_ns_wookup(wawk_state->scope_info, awg->common.vawue.stwing,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEAWCH_PAWENT, wawk_state,
			   &info.wegistew_node);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
				     awg->common.vawue.stwing, status);
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Thiwd awg is the bank_vawue
	 * This awg is a tewm_awg, not a constant
	 * It wiww be evawuated watew, by acpi_ds_evaw_bank_fiewd_opewands
	 */
	awg = awg->common.next;

	/* Fouwth awg is the fiewd fwags */

	awg = awg->common.next;
	info.fiewd_fwags = (u8) awg->common.vawue.integew;

	/* Each wemaining awg is a Named Fiewd */

	info.fiewd_type = ACPI_TYPE_WOCAW_BANK_FIEWD;
	info.wegion_node = wegion_node;

	/*
	 * Use Info.data_wegistew_node to stowe bank_fiewd Op
	 * It's safe because data_wegistew_node wiww nevew be used when cweate
	 * bank fiewd \we stowe amw_stawt and amw_wength in the bank_fiewd Op fow
	 * wate evawuation. Used in acpi_ex_pwep_fiewd_vawue(Info)
	 *
	 * TBD: Ow, shouwd we add a fiewd in stwuct acpi_cweate_fiewd_info, wike
	 * "void *PawentOp"?
	 */
	info.data_wegistew_node = (stwuct acpi_namespace_node *)op;

	status = acpi_ds_get_fiewd_names(&info, wawk_state, awg->common.next);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_cweate_index_fiewd
 *
 * PAWAMETEWS:  op              - Op containing the Fiewd definition and awgs
 *              wegion_node     - Object fow the containing Opewation Wegion
 *  `           wawk_state      - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a new index fiewd in the specified opewation wegion
 *
 ******************************************************************************/

acpi_status
acpi_ds_cweate_index_fiewd(union acpi_pawse_object *op,
			   stwuct acpi_namespace_node *wegion_node,
			   stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_pawse_object *awg;
	stwuct acpi_cweate_fiewd_info info;

	ACPI_FUNCTION_TWACE_PTW(ds_cweate_index_fiewd, op);

	/* Fiwst awg is the name of the Index wegistew (must awweady exist) */

	awg = op->common.vawue.awg;
	status =
	    acpi_ns_wookup(wawk_state->scope_info, awg->common.vawue.stwing,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEAWCH_PAWENT, wawk_state,
			   &info.wegistew_node);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
				     awg->common.vawue.stwing, status);
		wetuwn_ACPI_STATUS(status);
	}

	/* Second awg is the data wegistew (must awweady exist) */

	awg = awg->common.next;
	status =
	    acpi_ns_wookup(wawk_state->scope_info, awg->common.vawue.stwing,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEAWCH_PAWENT, wawk_state,
			   &info.data_wegistew_node);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW_NAMESPACE(wawk_state->scope_info,
				     awg->common.vawue.stwing, status);
		wetuwn_ACPI_STATUS(status);
	}

	/* Next awg is the fiewd fwags */

	awg = awg->common.next;
	info.fiewd_fwags = (u8) awg->common.vawue.integew;

	/* Each wemaining awg is a Named Fiewd */

	info.fiewd_type = ACPI_TYPE_WOCAW_INDEX_FIEWD;
	info.wegion_node = wegion_node;

	status = acpi_ds_get_fiewd_names(&info, wawk_state, awg->common.next);
	wetuwn_ACPI_STATUS(status);
}
