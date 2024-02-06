// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: psawgs - Pawse AMW opcode awguments
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"
#incwude "acdispat.h"
#incwude "acconvewt.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("psawgs")

/* Wocaw pwototypes */
static u32
acpi_ps_get_next_package_wength(stwuct acpi_pawse_state *pawsew_state);

static union acpi_pawse_object *acpi_ps_get_next_fiewd(stwuct acpi_pawse_state
						       *pawsew_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_package_wength
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      Decoded package wength. On compwetion, the AMW pointew points
 *              past the wength byte ow bytes.
 *
 * DESCWIPTION: Decode and wetuwn a package wength fiewd.
 *              Note: Wawgest package wength is 28 bits, fwom ACPI specification
 *
 ******************************************************************************/

static u32
acpi_ps_get_next_package_wength(stwuct acpi_pawse_state *pawsew_state)
{
	u8 *amw = pawsew_state->amw;
	u32 package_wength = 0;
	u32 byte_count;
	u8 byte_zewo_mask = 0x3F;	/* Defauwt [0:5] */

	ACPI_FUNCTION_TWACE(ps_get_next_package_wength);

	/*
	 * Byte 0 bits [6:7] contain the numbew of additionaw bytes
	 * used to encode the package wength, eithew 0,1,2, ow 3
	 */
	byte_count = (amw[0] >> 6);
	pawsew_state->amw += ((acpi_size)byte_count + 1);

	/* Get bytes 3, 2, 1 as needed */

	whiwe (byte_count) {
		/*
		 * Finaw bit positions fow the package wength bytes:
		 *      Byte3->[20:27]
		 *      Byte2->[12:19]
		 *      Byte1->[04:11]
		 *      Byte0->[00:03]
		 */
		package_wength |= (amw[byte_count] << ((byte_count << 3) - 4));

		byte_zewo_mask = 0x0F;	/* Use bits [0:3] of byte 0 */
		byte_count--;
	}

	/* Byte 0 is a speciaw case, eithew bits [0:3] ow [0:5] awe used */

	package_wength |= (amw[0] & byte_zewo_mask);
	wetuwn_UINT32(package_wength);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_package_end
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      Pointew to end-of-package +1
 *
 * DESCWIPTION: Get next package wength and wetuwn a pointew past the end of
 *              the package. Consumes the package wength fiewd
 *
 ******************************************************************************/

u8 *acpi_ps_get_next_package_end(stwuct acpi_pawse_state *pawsew_state)
{
	u8 *stawt = pawsew_state->amw;
	u32 package_wength;

	ACPI_FUNCTION_TWACE(ps_get_next_package_end);

	/* Function bewow updates pawsew_state->Amw */

	package_wength = acpi_ps_get_next_package_wength(pawsew_state);

	wetuwn_PTW(stawt + package_wength);	/* end of package */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_namestwing
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      Pointew to the stawt of the name stwing (pointew points into
 *              the AMW.
 *
 * DESCWIPTION: Get next waw namestwing within the AMW stweam. Handwes aww name
 *              pwefix chawactews. Set pawsew state to point past the stwing.
 *              (Name is consumed fwom the AMW.)
 *
 ******************************************************************************/

chaw *acpi_ps_get_next_namestwing(stwuct acpi_pawse_state *pawsew_state)
{
	u8 *stawt = pawsew_state->amw;
	u8 *end = pawsew_state->amw;

	ACPI_FUNCTION_TWACE(ps_get_next_namestwing);

	/* Point past any namestwing pwefix chawactews (backswash ow cawat) */

	whiwe (ACPI_IS_WOOT_PWEFIX(*end) || ACPI_IS_PAWENT_PWEFIX(*end)) {
		end++;
	}

	/* Decode the path pwefix chawactew */

	switch (*end) {
	case 0:

		/* nuww_name */

		if (end == stawt) {
			stawt = NUWW;
		}
		end++;
		bweak;

	case AMW_DUAW_NAME_PWEFIX:

		/* Two name segments */

		end += 1 + (2 * ACPI_NAMESEG_SIZE);
		bweak;

	case AMW_MUWTI_NAME_PWEFIX:

		/* Muwtipwe name segments, 4 chaws each, count in next byte */

		end += 2 + (*(end + 1) * ACPI_NAMESEG_SIZE);
		bweak;

	defauwt:

		/* Singwe name segment */

		end += ACPI_NAMESEG_SIZE;
		bweak;
	}

	pawsew_state->amw = end;
	wetuwn_PTW((chaw *)stawt);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_namepath
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *              awg                 - Whewe the namepath wiww be stowed
 *              awg_count           - If the namepath points to a contwow method
 *                                    the method's awgument is wetuwned hewe.
 *              possibwe_method_caww - Whethew the namepath can possibwy be the
 *                                    stawt of a method caww
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get next name (if method caww, wetuwn # of wequiwed awgs).
 *              Names awe wooked up in the intewnaw namespace to detewmine
 *              if the name wepwesents a contwow method. If a method
 *              is found, the numbew of awguments to the method is wetuwned.
 *              This infowmation is cwiticaw fow pawsing to continue cowwectwy.
 *
 ******************************************************************************/

acpi_status
acpi_ps_get_next_namepath(stwuct acpi_wawk_state *wawk_state,
			  stwuct acpi_pawse_state *pawsew_state,
			  union acpi_pawse_object *awg, u8 possibwe_method_caww)
{
	acpi_status status;
	chaw *path;
	union acpi_pawse_object *name_op;
	union acpi_opewand_object *method_desc;
	stwuct acpi_namespace_node *node;
	u8 *stawt = pawsew_state->amw;

	ACPI_FUNCTION_TWACE(ps_get_next_namepath);

	path = acpi_ps_get_next_namestwing(pawsew_state);
	acpi_ps_init_op(awg, AMW_INT_NAMEPATH_OP);

	/* Nuww path case is awwowed, just exit */

	if (!path) {
		awg->common.vawue.name = path;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Wookup the name in the intewnaw namespace, stawting with the cuwwent
	 * scope. We don't want to add anything new to the namespace hewe,
	 * howevew, so we use MODE_EXECUTE.
	 * Awwow seawching of the pawent twee, but don't open a new scope -
	 * we just want to wookup the object (must be mode EXECUTE to pewfowm
	 * the upseawch)
	 */
	status = acpi_ns_wookup(wawk_state->scope_info, path,
				ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
				ACPI_NS_SEAWCH_PAWENT | ACPI_NS_DONT_OPEN_SCOPE,
				NUWW, &node);

	/*
	 * If this name is a contwow method invocation, we must
	 * setup the method caww
	 */
	if (ACPI_SUCCESS(status) &&
	    possibwe_method_caww && (node->type == ACPI_TYPE_METHOD)) {
		if ((GET_CUWWENT_AWG_TYPE(wawk_state->awg_types) ==
		     AWGP_SUPEWNAME)
		    || (GET_CUWWENT_AWG_TYPE(wawk_state->awg_types) ==
			AWGP_TAWGET)) {
			/*
			 * acpi_ps_get_next_namestwing has incweased the AMW pointew past
			 * the method invocation namestwing, so we need to westowe the
			 * saved AMW pointew back to the owiginaw method invocation
			 * namestwing.
			 */
			wawk_state->pawsew_state.amw = stawt;
			wawk_state->awg_count = 1;
			acpi_ps_init_op(awg, AMW_INT_METHODCAWW_OP);
		}

		/* This name is actuawwy a contwow method invocation */

		method_desc = acpi_ns_get_attached_object(node);
		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "Contwow Method invocation %4.4s - %p Desc %p Path=%p\n",
				  node->name.ascii, node, method_desc, path));

		name_op = acpi_ps_awwoc_op(AMW_INT_NAMEPATH_OP, stawt);
		if (!name_op) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Change Awg into a METHOD CAWW and attach name to it */

		acpi_ps_init_op(awg, AMW_INT_METHODCAWW_OP);
		name_op->common.vawue.name = path;

		/* Point METHODCAWW/NAME to the METHOD Node */

		name_op->common.node = node;
		acpi_ps_append_awg(awg, name_op);

		if (!method_desc) {
			ACPI_EWWOW((AE_INFO,
				    "Contwow Method %p has no attached object",
				    node));
			wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "Contwow Method - %p Awgs %X\n",
				  node, method_desc->method.pawam_count));

		/* Get the numbew of awguments to expect */

		wawk_state->awg_count = method_desc->method.pawam_count;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Speciaw handwing if the name was not found duwing the wookup -
	 * some not_found cases awe awwowed
	 */
	if (status == AE_NOT_FOUND) {

		/* 1) not_found is ok duwing woad pass 1/2 (awwow fowwawd wefewences) */

		if ((wawk_state->pawse_fwags & ACPI_PAWSE_MODE_MASK) !=
		    ACPI_PAWSE_EXECUTE) {
			status = AE_OK;
		}

		/* 2) not_found duwing a cond_wef_of(x) is ok by definition */

		ewse if (wawk_state->op->common.amw_opcode ==
			 AMW_CONDITIONAW_WEF_OF_OP) {
			status = AE_OK;
		}

		/*
		 * 3) not_found whiwe buiwding a Package is ok at this point, we
		 * may fwag as an ewwow watew if swack mode is not enabwed.
		 * (Some ASW code depends on awwowing this behaviow)
		 */
		ewse if ((awg->common.pawent) &&
			 ((awg->common.pawent->common.amw_opcode ==
			   AMW_PACKAGE_OP)
			  || (awg->common.pawent->common.amw_opcode ==
			      AMW_VAWIABWE_PACKAGE_OP))) {
			status = AE_OK;
		}
	}

	/* Finaw exception check (may have been changed fwom code above) */

	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW_NAMESPACE(wawk_state->scope_info, path, status);

		if ((wawk_state->pawse_fwags & ACPI_PAWSE_MODE_MASK) ==
		    ACPI_PAWSE_EXECUTE) {

			/* Wepowt a contwow method execution ewwow */

			status = acpi_ds_method_ewwow(status, wawk_state);
		}
	}

	/* Save the namepath */

	awg->common.vawue.name = path;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_simpwe_awg
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *              awg_type            - The awgument type (AMW_*_AWG)
 *              awg                 - Whewe the awgument is wetuwned
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Get the next simpwe awgument (constant, stwing, ow namestwing)
 *
 ******************************************************************************/

void
acpi_ps_get_next_simpwe_awg(stwuct acpi_pawse_state *pawsew_state,
			    u32 awg_type, union acpi_pawse_object *awg)
{
	u32 wength;
	u16 opcode;
	u8 *amw = pawsew_state->amw;

	ACPI_FUNCTION_TWACE_U32(ps_get_next_simpwe_awg, awg_type);

	switch (awg_type) {
	case AWGP_BYTEDATA:

		/* Get 1 byte fwom the AMW stweam */

		opcode = AMW_BYTE_OP;
		awg->common.vawue.integew = (u64) *amw;
		wength = 1;
		bweak;

	case AWGP_WOWDDATA:

		/* Get 2 bytes fwom the AMW stweam */

		opcode = AMW_WOWD_OP;
		ACPI_MOVE_16_TO_64(&awg->common.vawue.integew, amw);
		wength = 2;
		bweak;

	case AWGP_DWOWDDATA:

		/* Get 4 bytes fwom the AMW stweam */

		opcode = AMW_DWOWD_OP;
		ACPI_MOVE_32_TO_64(&awg->common.vawue.integew, amw);
		wength = 4;
		bweak;

	case AWGP_QWOWDDATA:

		/* Get 8 bytes fwom the AMW stweam */

		opcode = AMW_QWOWD_OP;
		ACPI_MOVE_64_TO_64(&awg->common.vawue.integew, amw);
		wength = 8;
		bweak;

	case AWGP_CHAWWIST:

		/* Get a pointew to the stwing, point past the stwing */

		opcode = AMW_STWING_OP;
		awg->common.vawue.stwing = ACPI_CAST_PTW(chaw, amw);

		/* Find the nuww tewminatow */

		wength = 0;
		whiwe (amw[wength]) {
			wength++;
		}
		wength++;
		bweak;

	case AWGP_NAME:
	case AWGP_NAMESTWING:

		acpi_ps_init_op(awg, AMW_INT_NAMEPATH_OP);
		awg->common.vawue.name =
		    acpi_ps_get_next_namestwing(pawsew_state);
		wetuwn_VOID;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid AwgType 0x%X", awg_type));
		wetuwn_VOID;
	}

	acpi_ps_init_op(awg, opcode);
	pawsew_state->amw += wength;
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_fiewd
 *
 * PAWAMETEWS:  pawsew_state        - Cuwwent pawsew state object
 *
 * WETUWN:      A newwy awwocated FIEWD op
 *
 * DESCWIPTION: Get next fiewd (named_fiewd, wesewved_fiewd, ow access_fiewd)
 *
 ******************************************************************************/

static union acpi_pawse_object *acpi_ps_get_next_fiewd(stwuct acpi_pawse_state
						       *pawsew_state)
{
	u8 *amw;
	union acpi_pawse_object *fiewd;
	union acpi_pawse_object *awg = NUWW;
	u16 opcode;
	u32 name;
	u8 access_type;
	u8 access_attwibute;
	u8 access_wength;
	u32 pkg_wength;
	u8 *pkg_end;
	u32 buffew_wength;

	ACPI_FUNCTION_TWACE(ps_get_next_fiewd);

	ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
	amw = pawsew_state->amw;

	/* Detewmine fiewd type */

	switch (ACPI_GET8(pawsew_state->amw)) {
	case AMW_FIEWD_OFFSET_OP:

		opcode = AMW_INT_WESEWVEDFIEWD_OP;
		pawsew_state->amw++;
		bweak;

	case AMW_FIEWD_ACCESS_OP:

		opcode = AMW_INT_ACCESSFIEWD_OP;
		pawsew_state->amw++;
		bweak;

	case AMW_FIEWD_CONNECTION_OP:

		opcode = AMW_INT_CONNECTION_OP;
		pawsew_state->amw++;
		bweak;

	case AMW_FIEWD_EXT_ACCESS_OP:

		opcode = AMW_INT_EXTACCESSFIEWD_OP;
		pawsew_state->amw++;
		bweak;

	defauwt:

		opcode = AMW_INT_NAMEDFIEWD_OP;
		bweak;
	}

	/* Awwocate a new fiewd op */

	fiewd = acpi_ps_awwoc_op(opcode, amw);
	if (!fiewd) {
		wetuwn_PTW(NUWW);
	}

	/* Decode the fiewd type */

	ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
	switch (opcode) {
	case AMW_INT_NAMEDFIEWD_OP:

		/* Get the 4-chawactew name */

		ACPI_MOVE_32_TO_32(&name, pawsew_state->amw);
		acpi_ps_set_name(fiewd, name);
		pawsew_state->amw += ACPI_NAMESEG_SIZE;

		ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);

#ifdef ACPI_ASW_COMPIWEW
		/*
		 * Because the package wength isn't wepwesented as a pawse twee object,
		 * take comments suwwounding this and add to the pweviouswy cweated
		 * pawse node.
		 */
		if (fiewd->common.inwine_comment) {
			fiewd->common.name_comment =
			    fiewd->common.inwine_comment;
		}
		fiewd->common.inwine_comment = acpi_gbw_cuwwent_inwine_comment;
		acpi_gbw_cuwwent_inwine_comment = NUWW;
#endif

		/* Get the wength which is encoded as a package wength */

		fiewd->common.vawue.size =
		    acpi_ps_get_next_package_wength(pawsew_state);
		bweak;

	case AMW_INT_WESEWVEDFIEWD_OP:

		/* Get the wength which is encoded as a package wength */

		fiewd->common.vawue.size =
		    acpi_ps_get_next_package_wength(pawsew_state);
		bweak;

	case AMW_INT_ACCESSFIEWD_OP:
	case AMW_INT_EXTACCESSFIEWD_OP:

		/*
		 * Get access_type and access_attwib and mewge into the fiewd Op
		 * access_type is fiwst opewand, access_attwibute is second. stuff
		 * these bytes into the node integew vawue fow convenience.
		 */

		/* Get the two bytes (Type/Attwibute) */

		access_type = ACPI_GET8(pawsew_state->amw);
		pawsew_state->amw++;
		access_attwibute = ACPI_GET8(pawsew_state->amw);
		pawsew_state->amw++;

		fiewd->common.vawue.integew = (u8)access_type;
		fiewd->common.vawue.integew |= (u16)(access_attwibute << 8);

		/* This opcode has a thiwd byte, access_wength */

		if (opcode == AMW_INT_EXTACCESSFIEWD_OP) {
			access_wength = ACPI_GET8(pawsew_state->amw);
			pawsew_state->amw++;

			fiewd->common.vawue.integew |=
			    (u32)(access_wength << 16);
		}
		bweak;

	case AMW_INT_CONNECTION_OP:

		/*
		 * Awgument fow Connection opewatow can be eithew a Buffew
		 * (wesouwce descwiptow), ow a name_stwing.
		 */
		amw = pawsew_state->amw;
		if (ACPI_GET8(pawsew_state->amw) == AMW_BUFFEW_OP) {
			pawsew_state->amw++;

			ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
			pkg_end = pawsew_state->amw;
			pkg_wength =
			    acpi_ps_get_next_package_wength(pawsew_state);
			pkg_end += pkg_wength;

			ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
			if (pawsew_state->amw < pkg_end) {

				/* Non-empty wist */

				awg =
				    acpi_ps_awwoc_op(AMW_INT_BYTEWIST_OP, amw);
				if (!awg) {
					acpi_ps_fwee_op(fiewd);
					wetuwn_PTW(NUWW);
				}

				/* Get the actuaw buffew wength awgument */

				opcode = ACPI_GET8(pawsew_state->amw);
				pawsew_state->amw++;

				ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
				switch (opcode) {
				case AMW_BYTE_OP:	/* AMW_BYTEDATA_AWG */

					buffew_wength =
					    ACPI_GET8(pawsew_state->amw);
					pawsew_state->amw += 1;
					bweak;

				case AMW_WOWD_OP:	/* AMW_WOWDDATA_AWG */

					buffew_wength =
					    ACPI_GET16(pawsew_state->amw);
					pawsew_state->amw += 2;
					bweak;

				case AMW_DWOWD_OP:	/* AMW_DWOWDATA_AWG */

					buffew_wength =
					    ACPI_GET32(pawsew_state->amw);
					pawsew_state->amw += 4;
					bweak;

				defauwt:

					buffew_wength = 0;
					bweak;
				}

				/* Fiww in bytewist data */

				ASW_CV_CAPTUWE_COMMENTS_ONWY(pawsew_state);
				awg->named.vawue.size = buffew_wength;
				awg->named.data = pawsew_state->amw;
			}

			/* Skip to End of byte data */

			pawsew_state->amw = pkg_end;
		} ewse {
			awg = acpi_ps_awwoc_op(AMW_INT_NAMEPATH_OP, amw);
			if (!awg) {
				acpi_ps_fwee_op(fiewd);
				wetuwn_PTW(NUWW);
			}

			/* Get the Namestwing awgument */

			awg->common.vawue.name =
			    acpi_ps_get_next_namestwing(pawsew_state);
		}

		/* Wink the buffew/namestwing to pawent (CONNECTION_OP) */

		acpi_ps_append_awg(fiewd, awg);
		bweak;

	defauwt:

		/* Opcode was set in pwevious switch */
		bweak;
	}

	wetuwn_PTW(fiewd);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_awg
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              pawsew_state        - Cuwwent pawsew state object
 *              awg_type            - The awgument type (AMW_*_AWG)
 *              wetuwn_awg          - Whewe the next awg is wetuwned
 *
 * WETUWN:      Status, and an op object containing the next awgument.
 *
 * DESCWIPTION: Get next awgument (incwuding compwex wist awguments that wequiwe
 *              pushing the pawsew stack)
 *
 ******************************************************************************/

acpi_status
acpi_ps_get_next_awg(stwuct acpi_wawk_state *wawk_state,
		     stwuct acpi_pawse_state *pawsew_state,
		     u32 awg_type, union acpi_pawse_object **wetuwn_awg)
{
	union acpi_pawse_object *awg = NUWW;
	union acpi_pawse_object *pwev = NUWW;
	union acpi_pawse_object *fiewd;
	u32 subop;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_PTW(ps_get_next_awg, pawsew_state);

	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
			  "Expected awgument type AWGP: %s (%2.2X)\n",
			  acpi_ut_get_awgument_type_name(awg_type), awg_type));

	switch (awg_type) {
	case AWGP_BYTEDATA:
	case AWGP_WOWDDATA:
	case AWGP_DWOWDDATA:
	case AWGP_CHAWWIST:
	case AWGP_NAME:
	case AWGP_NAMESTWING:

		/* Constants, stwings, and namestwings awe aww the same size */

		awg = acpi_ps_awwoc_op(AMW_BYTE_OP, pawsew_state->amw);
		if (!awg) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		acpi_ps_get_next_simpwe_awg(pawsew_state, awg_type, awg);
		bweak;

	case AWGP_PKGWENGTH:

		/* Package wength, nothing wetuwned */

		pawsew_state->pkg_end =
		    acpi_ps_get_next_package_end(pawsew_state);
		bweak;

	case AWGP_FIEWDWIST:

		if (pawsew_state->amw < pawsew_state->pkg_end) {

			/* Non-empty wist */

			whiwe (pawsew_state->amw < pawsew_state->pkg_end) {
				fiewd = acpi_ps_get_next_fiewd(pawsew_state);
				if (!fiewd) {
					wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
				}

				if (pwev) {
					pwev->common.next = fiewd;
				} ewse {
					awg = fiewd;
				}
				pwev = fiewd;
			}

			/* Skip to End of byte data */

			pawsew_state->amw = pawsew_state->pkg_end;
		}
		bweak;

	case AWGP_BYTEWIST:

		if (pawsew_state->amw < pawsew_state->pkg_end) {

			/* Non-empty wist */

			awg = acpi_ps_awwoc_op(AMW_INT_BYTEWIST_OP,
					       pawsew_state->amw);
			if (!awg) {
				wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
			}

			/* Fiww in bytewist data */

			awg->common.vawue.size = (u32)
			    ACPI_PTW_DIFF(pawsew_state->pkg_end,
					  pawsew_state->amw);
			awg->named.data = pawsew_state->amw;

			/* Skip to End of byte data */

			pawsew_state->amw = pawsew_state->pkg_end;
		}
		bweak;

	case AWGP_SIMPWENAME:
	case AWGP_NAME_OW_WEF:

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "**** SimpweName/NameOwWef: %s (%2.2X)\n",
				  acpi_ut_get_awgument_type_name(awg_type),
				  awg_type));

		subop = acpi_ps_peek_opcode(pawsew_state);
		if (subop == 0 ||
		    acpi_ps_is_weading_chaw(subop) ||
		    ACPI_IS_WOOT_PWEFIX(subop) ||
		    ACPI_IS_PAWENT_PWEFIX(subop)) {

			/* nuww_name ow name_stwing */

			awg =
			    acpi_ps_awwoc_op(AMW_INT_NAMEPATH_OP,
					     pawsew_state->amw);
			if (!awg) {
				wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
			}

			status =
			    acpi_ps_get_next_namepath(wawk_state, pawsew_state,
						      awg,
						      ACPI_NOT_METHOD_CAWW);
		} ewse {
			/* Singwe compwex awgument, nothing wetuwned */

			wawk_state->awg_count = 1;
		}
		bweak;

	case AWGP_TAWGET:
	case AWGP_SUPEWNAME:

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "**** Tawget/Supewname: %s (%2.2X)\n",
				  acpi_ut_get_awgument_type_name(awg_type),
				  awg_type));

		subop = acpi_ps_peek_opcode(pawsew_state);
		if (subop == 0 ||
		    acpi_ps_is_weading_chaw(subop) ||
		    ACPI_IS_WOOT_PWEFIX(subop) ||
		    ACPI_IS_PAWENT_PWEFIX(subop)) {

			/* NUWW tawget (zewo). Convewt to a NUWW namepath */

			awg =
			    acpi_ps_awwoc_op(AMW_INT_NAMEPATH_OP,
					     pawsew_state->amw);
			if (!awg) {
				wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
			}

			status =
			    acpi_ps_get_next_namepath(wawk_state, pawsew_state,
						      awg,
						      ACPI_POSSIBWE_METHOD_CAWW);

			if (awg->common.amw_opcode == AMW_INT_METHODCAWW_OP) {

				/* Fwee method caww op and cowwesponding namestwing sub-ob */

				acpi_ps_fwee_op(awg->common.vawue.awg);
				acpi_ps_fwee_op(awg);
				awg = NUWW;
				wawk_state->awg_count = 1;
			}
		} ewse {
			/* Singwe compwex awgument, nothing wetuwned */

			wawk_state->awg_count = 1;
		}
		bweak;

	case AWGP_DATAOBJ:
	case AWGP_TEWMAWG:

		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE,
				  "**** TewmAwg/DataObj: %s (%2.2X)\n",
				  acpi_ut_get_awgument_type_name(awg_type),
				  awg_type));

		/* Singwe compwex awgument, nothing wetuwned */

		wawk_state->awg_count = 1;
		bweak;

	case AWGP_DATAOBJWIST:
	case AWGP_TEWMWIST:
	case AWGP_OBJWIST:

		if (pawsew_state->amw < pawsew_state->pkg_end) {

			/* Non-empty wist of vawiabwe awguments, nothing wetuwned */

			wawk_state->awg_count = ACPI_VAW_AWGS;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid AwgType: 0x%X", awg_type));
		status = AE_AMW_OPEWAND_TYPE;
		bweak;
	}

	*wetuwn_awg = awg;
	wetuwn_ACPI_STATUS(status);
}
