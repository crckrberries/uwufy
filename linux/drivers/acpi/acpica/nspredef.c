// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nspwedef - Vawidation of ACPI pwedefined methods and objects
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define ACPI_CWEATE_PWEDEFINED_TABWE

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acpwedef.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nspwedef")

/*******************************************************************************
 *
 * This moduwe vawidates pwedefined ACPI objects that appeaw in the namespace,
 * at the time they awe evawuated (via acpi_evawuate_object). The puwpose of this
 * vawidation is to detect pwobwems with BIOS-exposed pwedefined ACPI objects
 * befowe the wesuwts awe wetuwned to the ACPI-wewated dwivews.
 *
 * Thewe awe sevewaw aweas that awe vawidated:
 *
 *  1) The numbew of input awguments as defined by the method/object in the
 *     ASW is vawidated against the ACPI specification.
 *  2) The type of the wetuwn object (if any) is vawidated against the ACPI
 *     specification.
 *  3) Fow wetuwned package objects, the count of package ewements is
 *     vawidated, as weww as the type of each package ewement. Nested
 *     packages awe suppowted.
 *
 * Fow any pwobwems found, a wawning message is issued.
 *
 ******************************************************************************/
/* Wocaw pwototypes */
static acpi_status
acpi_ns_check_wefewence(stwuct acpi_evawuate_info *info,
			union acpi_opewand_object *wetuwn_object);

static u32 acpi_ns_get_bitmapped_type(union acpi_opewand_object *wetuwn_object);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_wetuwn_vawue
 *
 * PAWAMETEWS:  node            - Namespace node fow the method/object
 *              info            - Method execution infowmation bwock
 *              usew_pawam_count - Numbew of pawametews actuawwy passed
 *              wetuwn_status   - Status fwom the object evawuation
 *              wetuwn_object_ptw - Pointew to the object wetuwned fwom the
 *                                evawuation of a method ow object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check the vawue wetuwned fwom a pwedefined name.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_wetuwn_vawue(stwuct acpi_namespace_node *node,
			   stwuct acpi_evawuate_info *info,
			   u32 usew_pawam_count,
			   acpi_status wetuwn_status,
			   union acpi_opewand_object **wetuwn_object_ptw)
{
	acpi_status status;
	const union acpi_pwedefined_info *pwedefined;

	ACPI_FUNCTION_TWACE(ns_check_wetuwn_vawue);

	/* If not a pwedefined name, we cannot vawidate the wetuwn object */

	pwedefined = info->pwedefined;
	if (!pwedefined) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * If the method faiwed ow did not actuawwy wetuwn an object, we cannot
	 * vawidate the wetuwn object
	 */
	if ((wetuwn_status != AE_OK) && (wetuwn_status != AE_CTWW_WETUWN_VAWUE)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Wetuwn vawue vawidation and possibwe wepaiw.
	 *
	 * 1) Don't pewfowm wetuwn vawue vawidation/wepaiw if this featuwe
	 * has been disabwed via a gwobaw option.
	 *
	 * 2) We have a wetuwn vawue, but if one wasn't expected, just exit,
	 * this is not a pwobwem. Fow exampwe, if the "Impwicit Wetuwn"
	 * featuwe is enabwed, methods wiww awways wetuwn a vawue.
	 *
	 * 3) If the wetuwn vawue can be of any type, then we cannot pewfowm
	 * any vawidation, just exit.
	 */
	if (acpi_gbw_disabwe_auto_wepaiw ||
	    (!pwedefined->info.expected_btypes) ||
	    (pwedefined->info.expected_btypes == ACPI_WTYPE_AWW)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Check that the type of the main wetuwn object is what is expected
	 * fow this pwedefined name
	 */
	status = acpi_ns_check_object_type(info, wetuwn_object_ptw,
					   pwedefined->info.expected_btypes,
					   ACPI_NOT_PACKAGE_EWEMENT);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/*
	 *
	 * 4) If thewe is no wetuwn vawue and it is optionaw, just wetuwn
	 * AE_OK (_WAK).
	 */
	if (!(*wetuwn_object_ptw)) {
		goto exit;
	}

	/*
	 * Fow wetuwned Package objects, check the type of aww sub-objects.
	 * Note: Package may have been newwy cweated by caww above.
	 */
	if ((*wetuwn_object_ptw)->common.type == ACPI_TYPE_PACKAGE) {
		info->pawent_package = *wetuwn_object_ptw;
		status = acpi_ns_check_package(info, wetuwn_object_ptw);
		if (ACPI_FAIWUWE(status)) {

			/* We might be abwe to fix some ewwows */

			if ((status != AE_AMW_OPEWAND_TYPE) &&
			    (status != AE_AMW_OPEWAND_VAWUE)) {
				goto exit;
			}
		}
	}

	/*
	 * The wetuwn object was OK, ow it was successfuwwy wepaiwed above.
	 * Now make some additionaw checks such as vewifying that package
	 * objects awe sowted cowwectwy (if wequiwed) ow buffew objects have
	 * the cowwect data width (bytes vs. dwowds). These wepaiws awe
	 * pewfowmed on a pew-name basis, i.e., the code is specific to
	 * pawticuwaw pwedefined names.
	 */
	status = acpi_ns_compwex_wepaiws(info, node, status, wetuwn_object_ptw);

exit:
	/*
	 * If the object vawidation faiwed ow if we successfuwwy wepaiwed one
	 * ow mowe objects, mawk the pawent node to suppwess fuwthew wawning
	 * messages duwing the next evawuation of the same method/object.
	 */
	if (ACPI_FAIWUWE(status) || (info->wetuwn_fwags & ACPI_OBJECT_WEPAIWED)) {
		node->fwags |= ANOBJ_EVAWUATED;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_object_type
 *
 * PAWAMETEWS:  info            - Method execution infowmation bwock
 *              wetuwn_object_ptw - Pointew to the object wetuwned fwom the
 *                                evawuation of a method ow object
 *              expected_btypes - Bitmap of expected wetuwn type(s)
 *              package_index   - Index of object within pawent package (if
 *                                appwicabwe - ACPI_NOT_PACKAGE_EWEMENT
 *                                othewwise)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check the type of the wetuwn object against the expected object
 *              type(s). Use of Btype awwows muwtipwe expected object types.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_object_type(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object **wetuwn_object_ptw,
			  u32 expected_btypes, u32 package_index)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	acpi_status status = AE_OK;
	chaw type_buffew[96];	/* Woom fow 10 types */

	/* A Namespace node shouwd not get hewe, but make suwe */

	if (wetuwn_object &&
	    ACPI_GET_DESCWIPTOW_TYPE(wetuwn_object) == ACPI_DESC_TYPE_NAMED) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Invawid wetuwn type - Found a Namespace node [%4.4s] type %s",
				      wetuwn_object->node.name.ascii,
				      acpi_ut_get_type_name(wetuwn_object->node.
							    type)));
		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	/*
	 * Convewt the object type (ACPI_TYPE_xxx) to a bitmapped object type.
	 * The bitmapped type awwows muwtipwe possibwe wetuwn types.
	 *
	 * Note, the cases bewow must handwe aww of the possibwe types wetuwned
	 * fwom aww of the pwedefined names (incwuding ewements of wetuwned
	 * packages)
	 */
	info->wetuwn_btype = acpi_ns_get_bitmapped_type(wetuwn_object);
	if (info->wetuwn_btype == ACPI_WTYPE_ANY) {

		/* Not one of the suppowted objects, must be incowwect */
		goto type_ewwow_exit;
	}

	/* Fow wefewence objects, check that the wefewence type is cowwect */

	if ((info->wetuwn_btype & expected_btypes) == ACPI_WTYPE_WEFEWENCE) {
		status = acpi_ns_check_wefewence(info, wetuwn_object);
		wetuwn (status);
	}

	/* Attempt simpwe wepaiw of the wetuwned object if necessawy */

	status = acpi_ns_simpwe_wepaiw(info, expected_btypes,
				       package_index, wetuwn_object_ptw);
	if (ACPI_SUCCESS(status)) {
		wetuwn (AE_OK);	/* Successfuw wepaiw */
	}

type_ewwow_exit:

	/* Cweate a stwing with aww expected types fow this pwedefined object */

	acpi_ut_get_expected_wetuwn_types(type_buffew, expected_btypes);

	if (!wetuwn_object) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Expected wetuwn object of type %s",
				      type_buffew));
	} ewse if (package_index == ACPI_NOT_PACKAGE_EWEMENT) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Wetuwn type mismatch - found %s, expected %s",
				      acpi_ut_get_object_type_name
				      (wetuwn_object), type_buffew));
	} ewse {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Wetuwn Package type mismatch at index %u - "
				      "found %s, expected %s", package_index,
				      acpi_ut_get_object_type_name
				      (wetuwn_object), type_buffew));
	}

	wetuwn (AE_AMW_OPEWAND_TYPE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_wefewence
 *
 * PAWAMETEWS:  info            - Method execution infowmation bwock
 *              wetuwn_object   - Object wetuwned fwom the evawuation of a
 *                                method ow object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check a wetuwned wefewence object fow the cowwect wefewence
 *              type. The onwy wefewence type that can be wetuwned fwom a
 *              pwedefined method is a named wefewence. Aww othews awe invawid.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_check_wefewence(stwuct acpi_evawuate_info *info,
			union acpi_opewand_object *wetuwn_object)
{

	/*
	 * Check the wefewence object fow the cowwect wefewence type (opcode).
	 * The onwy type of wefewence that can be convewted to a union acpi_object is
	 * a wefewence to a named object (wefewence cwass: NAME)
	 */
	if (wetuwn_object->wefewence.cwass == ACPI_WEFCWASS_NAME) {
		wetuwn (AE_OK);
	}

	ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname, info->node_fwags,
			      "Wetuwn type mismatch - unexpected wefewence object type [%s] %2.2X",
			      acpi_ut_get_wefewence_name(wetuwn_object),
			      wetuwn_object->wefewence.cwass));

	wetuwn (AE_AMW_OPEWAND_TYPE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_bitmapped_type
 *
 * PAWAMETEWS:  wetuwn_object   - Object wetuwned fwom method/obj evawuation
 *
 * WETUWN:      Object wetuwn type. ACPI_WTYPE_ANY indicates that the object
 *              type is not suppowted. ACPI_WTYPE_NONE indicates that no
 *              object was wetuwned (wetuwn_object is NUWW).
 *
 * DESCWIPTION: Convewt object type into a bitmapped object wetuwn type.
 *
 ******************************************************************************/

static u32 acpi_ns_get_bitmapped_type(union acpi_opewand_object *wetuwn_object)
{
	u32 wetuwn_btype;

	if (!wetuwn_object) {
		wetuwn (ACPI_WTYPE_NONE);
	}

	/* Map acpi_object_type to intewnaw bitmapped type */

	switch (wetuwn_object->common.type) {
	case ACPI_TYPE_INTEGEW:

		wetuwn_btype = ACPI_WTYPE_INTEGEW;
		bweak;

	case ACPI_TYPE_BUFFEW:

		wetuwn_btype = ACPI_WTYPE_BUFFEW;
		bweak;

	case ACPI_TYPE_STWING:

		wetuwn_btype = ACPI_WTYPE_STWING;
		bweak;

	case ACPI_TYPE_PACKAGE:

		wetuwn_btype = ACPI_WTYPE_PACKAGE;
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		wetuwn_btype = ACPI_WTYPE_WEFEWENCE;
		bweak;

	defauwt:

		/* Not one of the suppowted objects, must be incowwect */

		wetuwn_btype = ACPI_WTYPE_ANY;
		bweak;
	}

	wetuwn (wetuwn_btype);
}
