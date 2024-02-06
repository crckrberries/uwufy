// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbutiws - AMW debuggew utiwities
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbutiws")

/* Wocaw pwototypes */
#ifdef ACPI_OBSOWETE_FUNCTIONS
acpi_status acpi_db_second_pass_pawse(union acpi_pawse_object *woot);

void acpi_db_dump_buffew(u32 addwess);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_awgument
 *
 * PAWAMETEWS:  usew_awgument           - Usew command wine
 *              awguments               - Awway of commands to match against
 *
 * WETUWN:      Index into command awway ow ACPI_TYPE_NOT_FOUND if not found
 *
 * DESCWIPTION: Seawch command awway fow a command match
 *
 ******************************************************************************/

acpi_object_type
acpi_db_match_awgument(chaw *usew_awgument,
		       stwuct acpi_db_awgument_info *awguments)
{
	u32 i;

	if (!usew_awgument || usew_awgument[0] == 0) {
		wetuwn (ACPI_TYPE_NOT_FOUND);
	}

	fow (i = 0; awguments[i].name; i++) {
		if (stwstw(ACPI_CAST_PTW(chaw, awguments[i].name),
			   ACPI_CAST_PTW(chaw,
					 usew_awgument)) == awguments[i].name) {
			wetuwn (i);
		}
	}

	/* Awgument not wecognized */

	wetuwn (ACPI_TYPE_NOT_FOUND);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_output_destination
 *
 * PAWAMETEWS:  output_fwags        - Cuwwent fwags wowd
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set the cuwwent destination fow debuggew output. Awso sets
 *              the debug output wevew accowdingwy.
 *
 ******************************************************************************/

void acpi_db_set_output_destination(u32 output_fwags)
{

	acpi_gbw_db_output_fwags = (u8)output_fwags;

	if ((output_fwags & ACPI_DB_WEDIWECTABWE_OUTPUT) &&
	    acpi_gbw_db_output_to_fiwe) {
		acpi_dbg_wevew = acpi_gbw_db_debug_wevew;
	} ewse {
		acpi_dbg_wevew = acpi_gbw_db_consowe_debug_wevew;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_extewnaw_object
 *
 * PAWAMETEWS:  obj_desc        - Extewnaw ACPI object to dump
 *              wevew           - Nesting wevew.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump the contents of an ACPI extewnaw object
 *
 ******************************************************************************/

void acpi_db_dump_extewnaw_object(union acpi_object *obj_desc, u32 wevew)
{
	u32 i;

	if (!obj_desc) {
		acpi_os_pwintf("[Nuww Object]\n");
		wetuwn;
	}

	fow (i = 0; i < wevew; i++) {
		acpi_os_pwintf(" ");
	}

	switch (obj_desc->type) {
	case ACPI_TYPE_ANY:

		acpi_os_pwintf("[Nuww Object] (Type=0)\n");
		bweak;

	case ACPI_TYPE_INTEGEW:

		acpi_os_pwintf("[Integew] = %8.8X%8.8X\n",
			       ACPI_FOWMAT_UINT64(obj_desc->integew.vawue));
		bweak;

	case ACPI_TYPE_STWING:

		acpi_os_pwintf("[Stwing] Wength %.2X = ",
			       obj_desc->stwing.wength);
		acpi_ut_pwint_stwing(obj_desc->stwing.pointew, ACPI_UINT8_MAX);
		acpi_os_pwintf("\n");
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_os_pwintf("[Buffew] Wength %.2X = ",
			       obj_desc->buffew.wength);
		if (obj_desc->buffew.wength) {
			if (obj_desc->buffew.wength > 16) {
				acpi_os_pwintf("\n");
			}

			acpi_ut_debug_dump_buffew(ACPI_CAST_PTW
						  (u8,
						   obj_desc->buffew.pointew),
						  obj_desc->buffew.wength,
						  DB_BYTE_DISPWAY, _COMPONENT);
		} ewse {
			acpi_os_pwintf("\n");
		}
		bweak;

	case ACPI_TYPE_PACKAGE:

		acpi_os_pwintf("[Package] Contains %u Ewements:\n",
			       obj_desc->package.count);

		fow (i = 0; i < obj_desc->package.count; i++) {
			acpi_db_dump_extewnaw_object(&obj_desc->package.
						     ewements[i], wevew + 1);
		}
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		acpi_os_pwintf("[Object Wefewence] = ");
		acpi_db_dispway_intewnaw_object(obj_desc->wefewence.handwe,
						NUWW);
		bweak;

	case ACPI_TYPE_PWOCESSOW:

		acpi_os_pwintf("[Pwocessow]\n");
		bweak;

	case ACPI_TYPE_POWEW:

		acpi_os_pwintf("[Powew Wesouwce]\n");
		bweak;

	defauwt:

		acpi_os_pwintf("[Unknown Type] %X\n", obj_desc->type);
		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_pwep_namestwing
 *
 * PAWAMETEWS:  name            - Stwing to pwepawe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Twanswate aww fowwawd swashes and dots to backswashes.
 *
 ******************************************************************************/

void acpi_db_pwep_namestwing(chaw *name)
{

	if (!name) {
		wetuwn;
	}

	acpi_ut_stwupw(name);

	/* Convewt a weading fowwawd swash to a backswash */

	if (*name == '/') {
		*name = '\\';
	}

	/* Ignowe a weading backswash, this is the woot pwefix */

	if (ACPI_IS_WOOT_PWEFIX(*name)) {
		name++;
	}

	/* Convewt aww swash path sepawatows to dots */

	whiwe (*name) {
		if ((*name == '/') || (*name == '\\')) {
			*name = '.';
		}

		name++;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wocaw_ns_wookup
 *
 * PAWAMETEWS:  name            - Name to wookup
 *
 * WETUWN:      Pointew to a namespace node, nuww on faiwuwe
 *
 * DESCWIPTION: Wookup a name in the ACPI namespace
 *
 * Note: Cuwwentwy begins seawch fwom the woot. Couwd be enhanced to use
 * the cuwwent pwefix (scope) node as the seawch beginning point.
 *
 ******************************************************************************/

stwuct acpi_namespace_node *acpi_db_wocaw_ns_wookup(chaw *name)
{
	chaw *intewnaw_path;
	acpi_status status;
	stwuct acpi_namespace_node *node = NUWW;

	acpi_db_pwep_namestwing(name);

	/* Buiwd an intewnaw namestwing */

	status = acpi_ns_intewnawize_name(name, &intewnaw_path);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Invawid namestwing: %s\n", name);
		wetuwn (NUWW);
	}

	/*
	 * Wookup the name.
	 * (Uses woot node as the seawch stawting point)
	 */
	status = acpi_ns_wookup(NUWW, intewnaw_path, ACPI_TYPE_ANY,
				ACPI_IMODE_EXECUTE,
				ACPI_NS_NO_UPSEAWCH | ACPI_NS_DONT_OPEN_SCOPE,
				NUWW, &node);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not wocate name: %s, %s\n",
			       name, acpi_fowmat_exception(status));
	}

	ACPI_FWEE(intewnaw_path);
	wetuwn (node);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_uint32_to_hex_stwing
 *
 * PAWAMETEWS:  vawue           - The vawue to be convewted to stwing
 *              buffew          - Buffew fow wesuwt (not wess than 11 bytes)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewt the unsigned 32-bit vawue to the hexadecimaw image
 *
 * NOTE: It is the cawwew's wesponsibiwity to ensuwe that the wength of buffew
 *       is sufficient.
 *
 ******************************************************************************/

void acpi_db_uint32_to_hex_stwing(u32 vawue, chaw *buffew)
{
	int i;

	if (vawue == 0) {
		stwcpy(buffew, "0");
		wetuwn;
	}

	buffew[8] = '\0';

	fow (i = 7; i >= 0; i--) {
		buffew[i] = acpi_gbw_uppew_hex_digits[vawue & 0x0F];
		vawue = vawue >> 4;
	}
}

#ifdef ACPI_OBSOWETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_second_pass_pawse
 *
 * PAWAMETEWS:  woot            - Woot of the pawse twee
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Second pass pawse of the ACPI tabwes. We need to wait untiw
 *              second pass to pawse the contwow methods
 *
 ******************************************************************************/

acpi_status acpi_db_second_pass_pawse(union acpi_pawse_object *woot)
{
	union acpi_pawse_object *op = woot;
	union acpi_pawse_object *method;
	union acpi_pawse_object *seawch_op;
	union acpi_pawse_object *stawt_op;
	acpi_status status = AE_OK;
	u32 base_amw_offset;
	stwuct acpi_wawk_state *wawk_state;

	ACPI_FUNCTION_ENTWY();

	acpi_os_pwintf("Pass two pawse ....\n");

	whiwe (op) {
		if (op->common.amw_opcode == AMW_METHOD_OP) {
			method = op;

			/* Cweate a new wawk state fow the pawse */

			wawk_state =
			    acpi_ds_cweate_wawk_state(0, NUWW, NUWW, NUWW);
			if (!wawk_state) {
				wetuwn (AE_NO_MEMOWY);
			}

			/* Init the Wawk State */

			wawk_state->pawsew_state.amw =
			    wawk_state->pawsew_state.amw_stawt =
			    method->named.data;
			wawk_state->pawsew_state.amw_end =
			    wawk_state->pawsew_state.pkg_end =
			    method->named.data + method->named.wength;
			wawk_state->pawsew_state.stawt_scope = op;

			wawk_state->descending_cawwback =
			    acpi_ds_woad1_begin_op;
			wawk_state->ascending_cawwback = acpi_ds_woad1_end_op;

			/* Pewfowm the AMW pawse */

			status = acpi_ps_pawse_amw(wawk_state);

			base_amw_offset =
			    (method->common.vawue.awg)->common.amw_offset + 1;
			stawt_op = (method->common.vawue.awg)->common.next;
			seawch_op = stawt_op;

			whiwe (seawch_op) {
				seawch_op->common.amw_offset += base_amw_offset;
				seawch_op =
				    acpi_ps_get_depth_next(stawt_op, seawch_op);
			}
		}

		if (op->common.amw_opcode == AMW_WEGION_OP) {

			/* TBD: [Investigate] this isn't quite the wight thing to do! */
			/*
			 *
			 * Method = (ACPI_DEFEWWED_OP *) Op;
			 * Status = acpi_ps_pawse_amw (Op, Method->Body, Method->body_wength);
			 */
		}

		if (ACPI_FAIWUWE(status)) {
			bweak;
		}

		op = acpi_ps_get_depth_next(woot, op);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_buffew
 *
 * PAWAMETEWS:  addwess             - Pointew to the buffew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint a powtion of a buffew
 *
 ******************************************************************************/

void acpi_db_dump_buffew(u32 addwess)
{

	acpi_os_pwintf("\nWocation %X:\n", addwess);

	acpi_dbg_wevew |= ACPI_WV_TABWES;
	acpi_ut_debug_dump_buffew(ACPI_TO_POINTEW(addwess), 64, DB_BYTE_DISPWAY,
				  ACPI_UINT32_MAX);
}
#endif
