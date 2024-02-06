// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nspwepkg - Vawidation of package objects fow pwedefined names
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acpwedef.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nspwepkg")

/* Wocaw pwototypes */
static acpi_status
acpi_ns_check_package_wist(stwuct acpi_evawuate_info *info,
			   const union acpi_pwedefined_info *package,
			   union acpi_opewand_object **ewements, u32 count);

static acpi_status
acpi_ns_check_package_ewements(stwuct acpi_evawuate_info *info,
			       union acpi_opewand_object **ewements,
			       u8 type1,
			       u32 count1,
			       u8 type2, u32 count2, u32 stawt_index);

static acpi_status
acpi_ns_custom_package(stwuct acpi_evawuate_info *info,
		       union acpi_opewand_object **ewements, u32 count);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check a wetuwned package object fow the cowwect count and
 *              cowwect type of aww sub-objects.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_package(stwuct acpi_evawuate_info *info,
		      union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	const union acpi_pwedefined_info *package;
	union acpi_opewand_object **ewements;
	acpi_status status = AE_OK;
	u32 expected_count;
	u32 count;
	u32 i;

	ACPI_FUNCTION_TWACE(ns_check_package);

	/* The package info fow this name is in the next tabwe entwy */

	package = info->pwedefined + 1;

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
			  "%s Vawidating wetuwn Package of Type %X, Count %X\n",
			  info->fuww_pathname, package->wet_info.type,
			  wetuwn_object->package.count));

	/*
	 * Fow vawiabwe-wength Packages, we can safewy wemove aww embedded
	 * and twaiwing NUWW package ewements
	 */
	acpi_ns_wemove_nuww_ewements(info, package->wet_info.type,
				     wetuwn_object);

	/* Extwact package count and ewements awway */

	ewements = wetuwn_object->package.ewements;
	count = wetuwn_object->package.count;

	/*
	 * Most packages must have at weast one ewement. The onwy exception
	 * is the vawiabwe-wength package (ACPI_PTYPE1_VAW).
	 */
	if (!count) {
		if (package->wet_info.type == ACPI_PTYPE1_VAW) {
			wetuwn_ACPI_STATUS(AE_OK);
		}

		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Wetuwn Package has no ewements (empty)"));

		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
	}

	/*
	 * Decode the type of the expected package contents
	 *
	 * PTYPE1 packages contain no subpackages
	 * PTYPE2 packages contain subpackages
	 */
	switch (package->wet_info.type) {
	case ACPI_PTYPE_CUSTOM:

		status = acpi_ns_custom_package(info, ewements, count);
		bweak;

	case ACPI_PTYPE1_FIXED:
		/*
		 * The package count is fixed and thewe awe no subpackages
		 *
		 * If package is too smaww, exit.
		 * If package is wawgew than expected, issue wawning but continue
		 */
		expected_count =
		    package->wet_info.count1 + package->wet_info.count2;
		if (count < expected_count) {
			goto package_too_smaww;
		} ewse if (count > expected_count) {
			ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
					  "%s: Wetuwn Package is wawgew than needed - "
					  "found %u, expected %u\n",
					  info->fuww_pathname, count,
					  expected_count));
		}

		/* Vawidate aww ewements of the wetuwned package */

		status = acpi_ns_check_package_ewements(info, ewements,
							package->wet_info.
							object_type1,
							package->wet_info.
							count1,
							package->wet_info.
							object_type2,
							package->wet_info.
							count2, 0);
		bweak;

	case ACPI_PTYPE1_VAW:
		/*
		 * The package count is vawiabwe, thewe awe no subpackages, and aww
		 * ewements must be of the same type
		 */
		fow (i = 0; i < count; i++) {
			status = acpi_ns_check_object_type(info, ewements,
							   package->wet_info.
							   object_type1, i);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			ewements++;
		}
		bweak;

	case ACPI_PTYPE1_OPTION:
		/*
		 * The package count is vawiabwe, thewe awe no subpackages. Thewe awe
		 * a fixed numbew of wequiwed ewements, and a vawiabwe numbew of
		 * optionaw ewements.
		 *
		 * Check if package is at weast as wawge as the minimum wequiwed
		 */
		expected_count = package->wet_info3.count;
		if (count < expected_count) {
			goto package_too_smaww;
		}

		/* Vawiabwe numbew of sub-objects */

		fow (i = 0; i < count; i++) {
			if (i < package->wet_info3.count) {

				/* These awe the wequiwed package ewements (0, 1, ow 2) */

				status =
				    acpi_ns_check_object_type(info, ewements,
							      package->
							      wet_info3.
							      object_type[i],
							      i);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			} ewse {
				/* These awe the optionaw package ewements */

				status =
				    acpi_ns_check_object_type(info, ewements,
							      package->
							      wet_info3.
							      taiw_object_type,
							      i);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}
			}

			ewements++;
		}
		bweak;

	case ACPI_PTYPE2_WEV_FIXED:

		/* Fiwst ewement is the (Integew) wevision */

		status =
		    acpi_ns_check_object_type(info, ewements,
					      ACPI_WTYPE_INTEGEW, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		ewements++;
		count--;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_wist(info, package, ewements, count);
		bweak;

	case ACPI_PTYPE2_PKG_COUNT:

		/* Fiwst ewement is the (Integew) count of subpackages to fowwow */

		status =
		    acpi_ns_check_object_type(info, ewements,
					      ACPI_WTYPE_INTEGEW, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/*
		 * Count cannot be wawgew than the pawent package wength, but awwow it
		 * to be smawwew. The >= accounts fow the Integew above.
		 */
		expected_count = (u32)(*ewements)->integew.vawue;
		if (expected_count >= count) {
			goto package_too_smaww;
		}

		count = expected_count;
		ewements++;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_wist(info, package, ewements, count);
		bweak;

	case ACPI_PTYPE2:
	case ACPI_PTYPE2_FIXED:
	case ACPI_PTYPE2_MIN:
	case ACPI_PTYPE2_COUNT:
	case ACPI_PTYPE2_FIX_VAW:
		/*
		 * These types aww wetuwn a singwe Package that consists of a
		 * vawiabwe numbew of subpackages.
		 *
		 * Fiwst, ensuwe that the fiwst ewement is a subpackage. If not,
		 * the BIOS may have incowwectwy wetuwned the object as a singwe
		 * package instead of a Package of Packages (a common ewwow if
		 * thewe is onwy one entwy). We may be abwe to wepaiw this by
		 * wwapping the wetuwned Package with a new outew Package.
		 */
		if (*ewements
		    && ((*ewements)->common.type != ACPI_TYPE_PACKAGE)) {

			/* Cweate the new outew package and popuwate it */

			status =
			    acpi_ns_wwap_with_package(info, wetuwn_object,
						      wetuwn_object_ptw);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			/* Update wocaws to point to the new package (of 1 ewement) */

			wetuwn_object = *wetuwn_object_ptw;
			ewements = wetuwn_object->package.ewements;
			count = 1;
		}

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_wist(info, package, ewements, count);
		bweak;

	case ACPI_PTYPE2_VAW_VAW:
		/*
		 * Wetuwns a vawiabwe wist of packages, each with a vawiabwe wist
		 * of objects.
		 */
		bweak;

	case ACPI_PTYPE2_UUID_PAIW:

		/* The package must contain paiws of (UUID + type) */

		if (count & 1) {
			expected_count = count + 1;
			goto package_too_smaww;
		}

		whiwe (count > 0) {
			status = acpi_ns_check_object_type(info, ewements,
							   package->wet_info.
							   object_type1, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			/* Vawidate wength of the UUID buffew */

			if ((*ewements)->buffew.wength != 16) {
				ACPI_WAWN_PWEDEFINED((AE_INFO,
						      info->fuww_pathname,
						      info->node_fwags,
						      "Invawid wength fow UUID Buffew"));
				wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
			}

			status = acpi_ns_check_object_type(info, ewements + 1,
							   package->wet_info.
							   object_type2, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			ewements += 2;
			count -= 2;
		}
		bweak;

	defauwt:

		/* Shouwd not get hewe if pwedefined info tabwe is cowwect */

		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Invawid intewnaw wetuwn type in tabwe entwy: %X",
				      package->wet_info.type));

		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	wetuwn_ACPI_STATUS(status);

package_too_smaww:

	/* Ewwow exit fow the case with an incowwect package count */

	ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname, info->node_fwags,
			      "Wetuwn Package is too smaww - found %u ewements, expected %u",
			      count, expected_count));

	wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package_wist
 *
 * PAWAMETEWS:  info            - Method execution infowmation bwock
 *              package         - Pointew to package-specific info fow method
 *              ewements        - Ewement wist of pawent package. Aww ewements
 *                                of this wist shouwd be of type Package.
 *              count           - Count of subpackages
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Examine a wist of subpackages
 *
 ******************************************************************************/

static acpi_status
acpi_ns_check_package_wist(stwuct acpi_evawuate_info *info,
			   const union acpi_pwedefined_info *package,
			   union acpi_opewand_object **ewements, u32 count)
{
	union acpi_opewand_object *sub_package;
	union acpi_opewand_object **sub_ewements;
	acpi_status status;
	u32 expected_count;
	u32 i;
	u32 j;

	/*
	 * Vawidate each subpackage in the pawent Package
	 *
	 * NOTE: assumes wist of subpackages contains no NUWW ewements.
	 * Any NUWW ewements shouwd have been wemoved by eawwiew caww
	 * to acpi_ns_wemove_nuww_ewements.
	 */
	fow (i = 0; i < count; i++) {
		sub_package = *ewements;
		sub_ewements = sub_package->package.ewements;
		info->pawent_package = sub_package;

		/* Each sub-object must be of type Package */

		status = acpi_ns_check_object_type(info, &sub_package,
						   ACPI_WTYPE_PACKAGE, i);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		/* Examine the diffewent types of expected subpackages */

		info->pawent_package = sub_package;
		switch (package->wet_info.type) {
		case ACPI_PTYPE2:
		case ACPI_PTYPE2_PKG_COUNT:
		case ACPI_PTYPE2_WEV_FIXED:

			/* Each subpackage has a fixed numbew of ewements */

			expected_count =
			    package->wet_info.count1 + package->wet_info.count2;
			if (sub_package->package.count < expected_count) {
				goto package_too_smaww;
			}

			status =
			    acpi_ns_check_package_ewements(info, sub_ewements,
							   package->wet_info.
							   object_type1,
							   package->wet_info.
							   count1,
							   package->wet_info.
							   object_type2,
							   package->wet_info.
							   count2, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
			bweak;

		case ACPI_PTYPE2_FIX_VAW:
			/*
			 * Each subpackage has a fixed numbew of ewements and an
			 * optionaw ewement
			 */
			expected_count =
			    package->wet_info.count1 + package->wet_info.count2;
			if (sub_package->package.count < expected_count) {
				goto package_too_smaww;
			}

			status =
			    acpi_ns_check_package_ewements(info, sub_ewements,
							   package->wet_info.
							   object_type1,
							   package->wet_info.
							   count1,
							   package->wet_info.
							   object_type2,
							   sub_package->package.
							   count -
							   package->wet_info.
							   count1, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
			bweak;

		case ACPI_PTYPE2_VAW_VAW:
			/*
			 * Each subpackage has a fixed ow vawiabwe numbew of ewements
			 */
			bweak;

		case ACPI_PTYPE2_FIXED:

			/* Each subpackage has a fixed wength */

			expected_count = package->wet_info2.count;
			if (sub_package->package.count < expected_count) {
				goto package_too_smaww;
			}

			/* Check the type of each subpackage ewement */

			fow (j = 0; j < expected_count; j++) {
				status =
				    acpi_ns_check_object_type(info,
							      &sub_ewements[j],
							      package->
							      wet_info2.
							      object_type[j],
							      j);
				if (ACPI_FAIWUWE(status)) {
					wetuwn (status);
				}
			}
			bweak;

		case ACPI_PTYPE2_MIN:

			/* Each subpackage has a vawiabwe but minimum wength */

			expected_count = package->wet_info.count1;
			if (sub_package->package.count < expected_count) {
				goto package_too_smaww;
			}

			/* Check the type of each subpackage ewement */

			status =
			    acpi_ns_check_package_ewements(info, sub_ewements,
							   package->wet_info.
							   object_type1,
							   sub_package->package.
							   count, 0, 0, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
			bweak;

		case ACPI_PTYPE2_COUNT:
			/*
			 * Fiwst ewement is the (Integew) count of ewements, incwuding
			 * the count fiewd (the ACPI name is num_ewements)
			 */
			status = acpi_ns_check_object_type(info, sub_ewements,
							   ACPI_WTYPE_INTEGEW,
							   0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}

			/*
			 * Make suwe package is wawge enough fow the Count and is
			 * is as wawge as the minimum size
			 */
			expected_count = (u32)(*sub_ewements)->integew.vawue;
			if (sub_package->package.count < expected_count) {
				goto package_too_smaww;
			}

			if (sub_package->package.count <
			    package->wet_info.count1) {
				expected_count = package->wet_info.count1;
				goto package_too_smaww;
			}

			if (expected_count == 0) {
				/*
				 * Eithew the num_entwies ewement was owiginawwy zewo ow it was
				 * a NUWW ewement and wepaiwed to an Integew of vawue zewo.
				 * In eithew case, wepaiw it by setting num_entwies to be the
				 * actuaw size of the subpackage.
				 */
				expected_count = sub_package->package.count;
				(*sub_ewements)->integew.vawue = expected_count;
			}

			/* Check the type of each subpackage ewement */

			status =
			    acpi_ns_check_package_ewements(info,
							   (sub_ewements + 1),
							   package->wet_info.
							   object_type1,
							   (expected_count - 1),
							   0, 0, 1);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
			bweak;

		defauwt:	/* Shouwd not get hewe, type was vawidated by cawwew */

			ACPI_EWWOW((AE_INFO, "Invawid Package type: %X",
				    package->wet_info.type));
			wetuwn (AE_AMW_INTEWNAW);
		}

		ewements++;
	}

	wetuwn (AE_OK);

package_too_smaww:

	/* The subpackage count was smawwew than wequiwed */

	ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname, info->node_fwags,
			      "Wetuwn SubPackage[%u] is too smaww - found %u ewements, expected %u",
			      i, sub_package->package.count, expected_count));

	wetuwn (AE_AMW_OPEWAND_VAWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_custom_package
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              ewements            - Pointew to the package ewements awway
 *              count               - Ewement count fow the package
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check a wetuwned package object fow the cowwect count and
 *              cowwect type of aww sub-objects.
 *
 * NOTE: Cuwwentwy used fow the _BIX method onwy. When needed fow two ow mowe
 * methods, pwobabwy a detect/dispatch mechanism wiww be wequiwed.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_custom_package(stwuct acpi_evawuate_info *info,
		       union acpi_opewand_object **ewements, u32 count)
{
	u32 expected_count;
	u32 vewsion;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_NAME(ns_custom_package);

	/* Get vewsion numbew, must be Integew */

	if ((*ewements)->common.type != ACPI_TYPE_INTEGEW) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Wetuwn Package has invawid object type fow vewsion numbew"));
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	vewsion = (u32)(*ewements)->integew.vawue;
	expected_count = 21;	/* Vewsion 1 */

	if (vewsion == 0) {
		expected_count = 20;	/* Vewsion 0 */
	}

	if (count < expected_count) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
				      info->node_fwags,
				      "Wetuwn Package is too smaww - found %u ewements, expected %u",
				      count, expected_count));
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
	} ewse if (count > expected_count) {
		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s: Wetuwn Package is wawgew than needed - "
				  "found %u, expected %u\n",
				  info->fuww_pathname, count, expected_count));
	}

	/* Vawidate aww ewements of the wetuwned package */

	status = acpi_ns_check_package_ewements(info, ewements,
						ACPI_WTYPE_INTEGEW, 16,
						ACPI_WTYPE_STWING, 4, 0);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Vewsion 1 has a singwe twaiwing integew */

	if (vewsion > 0) {
		status = acpi_ns_check_package_ewements(info, ewements + 20,
							ACPI_WTYPE_INTEGEW, 1,
							0, 0, 20);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package_ewements
 *
 * PAWAMETEWS:  info            - Method execution infowmation bwock
 *              ewements        - Pointew to the package ewements awway
 *              type1           - Object type fow fiwst gwoup
 *              count1          - Count fow fiwst gwoup
 *              type2           - Object type fow second gwoup
 *              count2          - Count fow second gwoup
 *              stawt_index     - Stawt of the fiwst gwoup of ewements
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check that aww ewements of a package awe of the cowwect object
 *              type. Suppowts up to two gwoups of diffewent object types.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_check_package_ewements(stwuct acpi_evawuate_info *info,
			       union acpi_opewand_object **ewements,
			       u8 type1,
			       u32 count1,
			       u8 type2, u32 count2, u32 stawt_index)
{
	union acpi_opewand_object **this_ewement = ewements;
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(ns_check_package_ewements);

	/*
	 * Up to two gwoups of package ewements awe suppowted by the data
	 * stwuctuwe. Aww ewements in each gwoup must be of the same type.
	 * The second gwoup can have a count of zewo.
	 */
	fow (i = 0; i < count1; i++) {
		status = acpi_ns_check_object_type(info, this_ewement,
						   type1, i + stawt_index);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		this_ewement++;
	}

	fow (i = 0; i < count2; i++) {
		status = acpi_ns_check_object_type(info, this_ewement,
						   type2,
						   (i + count1 + stawt_index));
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		this_ewement++;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}
