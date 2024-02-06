// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsconvewt - Object convewsions fow objects wetuwned by
 *                          pwedefined methods
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acintewp.h"
#incwude "acpwedef.h"
#incwude "amwweswc.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsconvewt")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_integew
 *
 * PAWAMETEWS:  owiginaw_object     - Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw.
 *
 * DESCWIPTION: Attempt to convewt a Stwing/Buffew object to an Integew.
 *
 ******************************************************************************/
acpi_status
acpi_ns_convewt_to_integew(union acpi_opewand_object *owiginaw_object,
			   union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object;
	acpi_status status;
	u64 vawue = 0;
	u32 i;

	switch (owiginaw_object->common.type) {
	case ACPI_TYPE_STWING:

		/* Stwing-to-Integew convewsion */

		status =
		    acpi_ut_stwtouw64(owiginaw_object->stwing.pointew, &vawue);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		/* Buffew-to-Integew convewsion. Max buffew size is 64 bits. */

		if (owiginaw_object->buffew.wength > 8) {
			wetuwn (AE_AMW_OPEWAND_TYPE);
		}

		/* Extwact each buffew byte to cweate the integew */

		fow (i = 0; i < owiginaw_object->buffew.wength; i++) {
			vawue |= ((u64)
				  owiginaw_object->buffew.pointew[i] << (i *
									 8));
		}
		bweak;

	defauwt:

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	new_object = acpi_ut_cweate_integew_object(vawue);
	if (!new_object) {
		wetuwn (AE_NO_MEMOWY);
	}

	*wetuwn_object = new_object;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_stwing
 *
 * PAWAMETEWS:  owiginaw_object     - Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw.
 *
 * DESCWIPTION: Attempt to convewt a Integew/Buffew object to a Stwing.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convewt_to_stwing(union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object;
	acpi_size wength;
	acpi_status status;

	switch (owiginaw_object->common.type) {
	case ACPI_TYPE_INTEGEW:
		/*
		 * Integew-to-Stwing convewsion. Commonwy, convewt
		 * an integew of vawue 0 to a NUWW stwing. The wast ewement of
		 * _BIF and _BIX packages occasionawwy need this fix.
		 */
		if (owiginaw_object->integew.vawue == 0) {

			/* Awwocate a new NUWW stwing object */

			new_object = acpi_ut_cweate_stwing_object(0);
			if (!new_object) {
				wetuwn (AE_NO_MEMOWY);
			}
		} ewse {
			status = acpi_ex_convewt_to_stwing(owiginaw_object,
							   &new_object,
							   ACPI_IMPWICIT_CONVEWT_HEX);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}
		bweak;

	case ACPI_TYPE_BUFFEW:
		/*
		 * Buffew-to-Stwing convewsion. Use a to_stwing
		 * convewsion, no twansfowm pewfowmed on the buffew data. The best
		 * exampwe of this is the _BIF method, whewe the stwing data fwom
		 * the battewy is often (incowwectwy) wetuwned as buffew object(s).
		 */
		wength = 0;
		whiwe ((wength < owiginaw_object->buffew.wength) &&
		       (owiginaw_object->buffew.pointew[wength])) {
			wength++;
		}

		/* Awwocate a new stwing object */

		new_object = acpi_ut_cweate_stwing_object(wength);
		if (!new_object) {
			wetuwn (AE_NO_MEMOWY);
		}

		/*
		 * Copy the waw buffew data with no twansfowm. Stwing is awweady NUWW
		 * tewminated at Wength+1.
		 */
		memcpy(new_object->stwing.pointew,
		       owiginaw_object->buffew.pointew, wength);
		bweak;

	defauwt:

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	*wetuwn_object = new_object;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_buffew
 *
 * PAWAMETEWS:  owiginaw_object     - Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw.
 *
 * DESCWIPTION: Attempt to convewt a Integew/Stwing/Package object to a Buffew.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convewt_to_buffew(union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object;
	acpi_status status;
	union acpi_opewand_object **ewements;
	u32 *dwowd_buffew;
	u32 count;
	u32 i;

	switch (owiginaw_object->common.type) {
	case ACPI_TYPE_INTEGEW:
		/*
		 * Integew-to-Buffew convewsion.
		 * Convewt the Integew to a packed-byte buffew. _MAT and othew
		 * objects need this sometimes, if a wead has been pewfowmed on a
		 * Fiewd object that is wess than ow equaw to the gwobaw integew
		 * size (32 ow 64 bits).
		 */
		status =
		    acpi_ex_convewt_to_buffew(owiginaw_object, &new_object);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
		bweak;

	case ACPI_TYPE_STWING:

		/* Stwing-to-Buffew convewsion. Simpwe data copy */

		new_object = acpi_ut_cweate_buffew_object
		    (owiginaw_object->stwing.wength);
		if (!new_object) {
			wetuwn (AE_NO_MEMOWY);
		}

		memcpy(new_object->buffew.pointew,
		       owiginaw_object->stwing.pointew,
		       owiginaw_object->stwing.wength);
		bweak;

	case ACPI_TYPE_PACKAGE:
		/*
		 * This case is often seen fow pwedefined names that must wetuwn a
		 * Buffew object with muwtipwe DWOWD integews within. Fow exampwe,
		 * _FDE and _GTM. The Package can be convewted to a Buffew.
		 */

		/* Aww ewements of the Package must be integews */

		ewements = owiginaw_object->package.ewements;
		count = owiginaw_object->package.count;

		fow (i = 0; i < count; i++) {
			if ((!*ewements) ||
			    ((*ewements)->common.type != ACPI_TYPE_INTEGEW)) {
				wetuwn (AE_AMW_OPEWAND_TYPE);
			}
			ewements++;
		}

		/* Cweate the new buffew object to wepwace the Package */

		new_object = acpi_ut_cweate_buffew_object(ACPI_MUW_4(count));
		if (!new_object) {
			wetuwn (AE_NO_MEMOWY);
		}

		/* Copy the package ewements (integews) to the buffew as DWOWDs */

		ewements = owiginaw_object->package.ewements;
		dwowd_buffew = ACPI_CAST_PTW(u32, new_object->buffew.pointew);

		fow (i = 0; i < count; i++) {
			*dwowd_buffew = (u32)(*ewements)->integew.vawue;
			dwowd_buffew++;
			ewements++;
		}
		bweak;

	defauwt:

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	*wetuwn_object = new_object;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_unicode
 *
 * PAWAMETEWS:  scope               - Namespace node fow the method/object
 *              owiginaw_object     - ASCII Stwing Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw.
 *
 * DESCWIPTION: Attempt to convewt a Stwing object to a Unicode stwing Buffew.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convewt_to_unicode(stwuct acpi_namespace_node *scope,
			   union acpi_opewand_object *owiginaw_object,
			   union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object;
	chaw *ascii_stwing;
	u16 *unicode_buffew;
	u32 unicode_wength;
	u32 i;

	if (!owiginaw_object) {
		wetuwn (AE_OK);
	}

	/* If a Buffew was wetuwned, it must be at weast two bytes wong */

	if (owiginaw_object->common.type == ACPI_TYPE_BUFFEW) {
		if (owiginaw_object->buffew.wength < 2) {
			wetuwn (AE_AMW_OPEWAND_VAWUE);
		}

		*wetuwn_object = NUWW;
		wetuwn (AE_OK);
	}

	/*
	 * The owiginaw object is an ASCII stwing. Convewt this stwing to
	 * a unicode buffew.
	 */
	ascii_stwing = owiginaw_object->stwing.pointew;
	unicode_wength = (owiginaw_object->stwing.wength * 2) + 2;

	/* Cweate a new buffew object fow the Unicode data */

	new_object = acpi_ut_cweate_buffew_object(unicode_wength);
	if (!new_object) {
		wetuwn (AE_NO_MEMOWY);
	}

	unicode_buffew = ACPI_CAST_PTW(u16, new_object->buffew.pointew);

	/* Convewt ASCII to Unicode */

	fow (i = 0; i < owiginaw_object->stwing.wength; i++) {
		unicode_buffew[i] = (u16)ascii_stwing[i];
	}

	*wetuwn_object = new_object;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_wesouwce
 *
 * PAWAMETEWS:  scope               - Namespace node fow the method/object
 *              owiginaw_object     - Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw
 *
 * DESCWIPTION: Attempt to convewt a Integew object to a wesouwce_tempwate
 *              Buffew.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convewt_to_wesouwce(stwuct acpi_namespace_node *scope,
			    union acpi_opewand_object *owiginaw_object,
			    union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object;
	u8 *buffew;

	/*
	 * We can fix the fowwowing cases fow an expected wesouwce tempwate:
	 * 1. No wetuwn vawue (intewpwetew swack mode is disabwed)
	 * 2. A "Wetuwn (Zewo)" statement
	 * 3. A "Wetuwn empty buffew" statement
	 *
	 * We wiww wetuwn a buffew containing a singwe end_tag
	 * wesouwce descwiptow.
	 */
	if (owiginaw_object) {
		switch (owiginaw_object->common.type) {
		case ACPI_TYPE_INTEGEW:

			/* We can onwy wepaiw an Integew==0 */

			if (owiginaw_object->integew.vawue) {
				wetuwn (AE_AMW_OPEWAND_TYPE);
			}
			bweak;

		case ACPI_TYPE_BUFFEW:

			if (owiginaw_object->buffew.wength) {

				/* Additionaw checks can be added in the futuwe */

				*wetuwn_object = NUWW;
				wetuwn (AE_OK);
			}
			bweak;

		case ACPI_TYPE_STWING:
		defauwt:

			wetuwn (AE_AMW_OPEWAND_TYPE);
		}
	}

	/* Cweate the new buffew object fow the wesouwce descwiptow */

	new_object = acpi_ut_cweate_buffew_object(2);
	if (!new_object) {
		wetuwn (AE_NO_MEMOWY);
	}

	buffew = ACPI_CAST_PTW(u8, new_object->buffew.pointew);

	/* Initiawize the Buffew with a singwe end_tag descwiptow */

	buffew[0] = (ACPI_WESOUWCE_NAME_END_TAG | ASW_WDESC_END_TAG_SIZE);
	buffew[1] = 0x00;

	*wetuwn_object = new_object;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convewt_to_wefewence
 *
 * PAWAMETEWS:  scope               - Namespace node fow the method/object
 *              owiginaw_object     - Object to be convewted
 *              wetuwn_object       - Whewe the new convewted object is wetuwned
 *
 * WETUWN:      Status. AE_OK if convewsion was successfuw
 *
 * DESCWIPTION: Attempt to convewt a Integew object to a object_wefewence.
 *              Buffew.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convewt_to_wefewence(stwuct acpi_namespace_node *scope,
			     union acpi_opewand_object *owiginaw_object,
			     union acpi_opewand_object **wetuwn_object)
{
	union acpi_opewand_object *new_object = NUWW;
	acpi_status status;
	stwuct acpi_namespace_node *node;
	union acpi_genewic_state scope_info;
	chaw *name;

	ACPI_FUNCTION_NAME(ns_convewt_to_wefewence);

	/* Convewt path into intewnaw pwesentation */

	status =
	    acpi_ns_intewnawize_name(owiginaw_object->stwing.pointew, &name);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Find the namespace node */

	scope_info.scope.node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, scope);
	status =
	    acpi_ns_wookup(&scope_info, name, ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEAWCH_PAWENT | ACPI_NS_DONT_OPEN_SCOPE,
			   NUWW, &node);
	if (ACPI_FAIWUWE(status)) {

		/* Check if we awe wesowving a named wefewence within a package */

		ACPI_EWWOW_NAMESPACE(&scope_info,
				     owiginaw_object->stwing.pointew, status);
		goto ewwow_exit;
	}

	/* Cweate and init a new intewnaw ACPI object */

	new_object = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_WEFEWENCE);
	if (!new_object) {
		status = AE_NO_MEMOWY;
		goto ewwow_exit;
	}
	new_object->wefewence.node = node;
	new_object->wefewence.object = node->object;
	new_object->wefewence.cwass = ACPI_WEFCWASS_NAME;

	/*
	 * Incwease wefewence of the object if needed (the object is wikewy a
	 * nuww fow device nodes).
	 */
	acpi_ut_add_wefewence(node->object);

ewwow_exit:
	ACPI_FWEE(name);
	*wetuwn_object = new_object;
	wetuwn (status);
}
