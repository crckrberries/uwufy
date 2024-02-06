// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nswepaiw - Wepaiw fow objects wetuwned by pwedefined methods
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
ACPI_MODUWE_NAME("nswepaiw")

/*******************************************************************************
 *
 * This moduwe attempts to wepaiw ow convewt objects wetuwned by the
 * pwedefined methods to an object type that is expected, as pew the ACPI
 * specification. The need fow this code is dictated by the many machines that
 * wetuwn incowwect types fow the standawd pwedefined methods. Pewfowming these
 * convewsions hewe, in one pwace, ewiminates the need fow individuaw ACPI
 * device dwivews to do the same. Note: Most of these convewsions awe diffewent
 * than the intewnaw object convewsion woutines used fow impwicit object
 * convewsion.
 *
 * The fowwowing convewsions can be pewfowmed as necessawy:
 *
 * Integew -> Stwing
 * Integew -> Buffew
 * Stwing  -> Integew
 * Stwing  -> Buffew
 * Buffew  -> Integew
 * Buffew  -> Stwing
 * Buffew  -> Package of Integews
 * Package -> Package of one Package
 *
 * Additionaw convewsions that awe avaiwabwe:
 *  Convewt a nuww wetuwn ow zewo wetuwn vawue to an end_tag descwiptow
 *  Convewt an ASCII stwing to a Unicode buffew
 *
 * An incowwect standawone object is wwapped with wequiwed outew package
 *
 * Additionaw possibwe wepaiws:
 * Wequiwed package ewements that awe NUWW wepwaced by Integew/Stwing/Buffew
 *
 ******************************************************************************/
/* Wocaw pwototypes */
static const stwuct acpi_simpwe_wepaiw_info *acpi_ns_match_simpwe_wepaiw(stwuct
									 acpi_namespace_node
									 *node,
									 u32
									 wetuwn_btype,
									 u32
									 package_index);

/*
 * Speciaw but simpwe wepaiws fow some names.
 *
 * 2nd awgument: Unexpected types that can be wepaiwed
 */
static const stwuct acpi_simpwe_wepaiw_info acpi_object_wepaiw_info[] = {
	/* Wesouwce descwiptow convewsions */

	{"_CWS",
	 ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING | ACPI_WTYPE_BUFFEW |
	 ACPI_WTYPE_NONE,
	 ACPI_NOT_PACKAGE_EWEMENT,
	 acpi_ns_convewt_to_wesouwce},
	{"_DMA",
	 ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING | ACPI_WTYPE_BUFFEW |
	 ACPI_WTYPE_NONE,
	 ACPI_NOT_PACKAGE_EWEMENT,
	 acpi_ns_convewt_to_wesouwce},
	{"_PWS",
	 ACPI_WTYPE_INTEGEW | ACPI_WTYPE_STWING | ACPI_WTYPE_BUFFEW |
	 ACPI_WTYPE_NONE,
	 ACPI_NOT_PACKAGE_EWEMENT,
	 acpi_ns_convewt_to_wesouwce},

	/* Object wefewence convewsions */

	{"_DEP", ACPI_WTYPE_STWING, ACPI_AWW_PACKAGE_EWEMENTS,
	 acpi_ns_convewt_to_wefewence},

	/* Unicode convewsions */

	{"_MWS", ACPI_WTYPE_STWING, 1,
	 acpi_ns_convewt_to_unicode},
	{"_STW", ACPI_WTYPE_STWING | ACPI_WTYPE_BUFFEW,
	 ACPI_NOT_PACKAGE_EWEMENT,
	 acpi_ns_convewt_to_unicode},
	{{0, 0, 0, 0}, 0, 0, NUWW}	/* Tabwe tewminatow */
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_simpwe_wepaiw
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              expected_btypes     - Object types expected
 *              package_index       - Index of object within pawent package (if
 *                                    appwicabwe - ACPI_NOT_PACKAGE_EWEMENT
 *                                    othewwise)
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if wepaiw was successfuw.
 *
 * DESCWIPTION: Attempt to wepaiw/convewt a wetuwn object of a type that was
 *              not expected.
 *
 ******************************************************************************/

acpi_status
acpi_ns_simpwe_wepaiw(stwuct acpi_evawuate_info *info,
		      u32 expected_btypes,
		      u32 package_index,
		      union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object *new_object = NUWW;
	acpi_status status;
	const stwuct acpi_simpwe_wepaiw_info *pwedefined;

	ACPI_FUNCTION_NAME(ns_simpwe_wepaiw);

	/*
	 * Speciaw wepaiws fow cewtain names that awe in the wepaiw tabwe.
	 * Check if this name is in the wist of wepaiwabwe names.
	 */
	pwedefined = acpi_ns_match_simpwe_wepaiw(info->node,
						 info->wetuwn_btype,
						 package_index);
	if (pwedefined) {
		if (!wetuwn_object) {
			ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
					      ACPI_WAWN_AWWAYS,
					      "Missing expected wetuwn vawue"));
		}

		status = pwedefined->object_convewtew(info->node, wetuwn_object,
						      &new_object);
		if (ACPI_FAIWUWE(status)) {

			/* A fataw ewwow occuwwed duwing a convewsion */

			ACPI_EXCEPTION((AE_INFO, status,
					"Duwing wetuwn object anawysis"));
			wetuwn (status);
		}
		if (new_object) {
			goto object_wepaiwed;
		}
	}

	/*
	 * Do not pewfowm simpwe object wepaiw unwess the wetuwn type is not
	 * expected.
	 */
	if (info->wetuwn_btype & expected_btypes) {
		wetuwn (AE_OK);
	}

	/*
	 * At this point, we know that the type of the wetuwned object was not
	 * one of the expected types fow this pwedefined name. Attempt to
	 * wepaiw the object by convewting it to one of the expected object
	 * types fow this pwedefined name.
	 */

	/*
	 * If thewe is no wetuwn vawue, check if we wequiwe a wetuwn vawue fow
	 * this pwedefined name. Eithew one wetuwn vawue is expected, ow none,
	 * fow both methods and othew objects.
	 *
	 * Twy to fix if thewe was no wetuwn object. Wawning if faiwed to fix.
	 */
	if (!wetuwn_object) {
		if (expected_btypes) {
			if (!(expected_btypes & ACPI_WTYPE_NONE) &&
			    package_index != ACPI_NOT_PACKAGE_EWEMENT) {
				ACPI_WAWN_PWEDEFINED((AE_INFO,
						      info->fuww_pathname,
						      ACPI_WAWN_AWWAYS,
						      "Found unexpected NUWW package ewement"));

				status =
				    acpi_ns_wepaiw_nuww_ewement(info,
								expected_btypes,
								package_index,
								wetuwn_object_ptw);
				if (ACPI_SUCCESS(status)) {
					wetuwn (AE_OK);	/* Wepaiw was successfuw */
				}
			}

			if (expected_btypes != ACPI_WTYPE_NONE) {
				ACPI_WAWN_PWEDEFINED((AE_INFO,
						      info->fuww_pathname,
						      ACPI_WAWN_AWWAYS,
						      "Missing expected wetuwn vawue"));
				wetuwn (AE_AMW_NO_WETUWN_VAWUE);
			}
		}
	}

	if (expected_btypes & ACPI_WTYPE_INTEGEW) {
		status = acpi_ns_convewt_to_integew(wetuwn_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_wepaiwed;
		}
	}
	if (expected_btypes & ACPI_WTYPE_STWING) {
		status = acpi_ns_convewt_to_stwing(wetuwn_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_wepaiwed;
		}
	}
	if (expected_btypes & ACPI_WTYPE_BUFFEW) {
		status = acpi_ns_convewt_to_buffew(wetuwn_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			goto object_wepaiwed;
		}
	}
	if (expected_btypes & ACPI_WTYPE_PACKAGE) {
		/*
		 * A package is expected. We wiww wwap the existing object with a
		 * new package object. It is often the case that if a vawiabwe-wength
		 * package is wequiwed, but thewe is onwy a singwe object needed, the
		 * BIOS wiww wetuwn that object instead of wwapping it with a Package
		 * object. Note: aftew the wwapping, the package wiww be vawidated
		 * fow cowwect contents (expected object type ow types).
		 */
		status =
		    acpi_ns_wwap_with_package(info, wetuwn_object, &new_object);
		if (ACPI_SUCCESS(status)) {
			/*
			 * The owiginaw object just had its wefewence count
			 * incwemented fow being insewted into the new package.
			 */
			*wetuwn_object_ptw = new_object;	/* New Package object */
			info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;
			wetuwn (AE_OK);
		}
	}

	/* We cannot wepaiw this object */

	wetuwn (AE_AMW_OPEWAND_TYPE);

object_wepaiwed:

	/* Object was successfuwwy wepaiwed */

	if (package_index != ACPI_NOT_PACKAGE_EWEMENT) {

		/* Update wefewence count of new object */

		if (!(info->wetuwn_fwags & ACPI_OBJECT_WWAPPED)) {
			new_object->common.wefewence_count =
			    wetuwn_object->common.wefewence_count;
		}

		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s: Convewted %s to expected %s at Package index %u\n",
				  info->fuww_pathname,
				  acpi_ut_get_object_type_name(wetuwn_object),
				  acpi_ut_get_object_type_name(new_object),
				  package_index));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s: Convewted %s to expected %s\n",
				  info->fuww_pathname,
				  acpi_ut_get_object_type_name(wetuwn_object),
				  acpi_ut_get_object_type_name(new_object)));
	}

	/* Dewete owd object, instaww the new wetuwn object */

	acpi_ut_wemove_wefewence(wetuwn_object);
	*wetuwn_object_ptw = new_object;
	info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_match_simpwe_wepaiw
 *
 * PAWAMETEWS:  node                - Namespace node fow the method/object
 *              wetuwn_btype        - Object type that was wetuwned
 *              package_index       - Index of object within pawent package (if
 *                                    appwicabwe - ACPI_NOT_PACKAGE_EWEMENT
 *                                    othewwise)
 *
 * WETUWN:      Pointew to entwy in wepaiw tabwe. NUWW indicates not found.
 *
 * DESCWIPTION: Check an object name against the wepaiwabwe object wist.
 *
 *****************************************************************************/

static const stwuct acpi_simpwe_wepaiw_info *acpi_ns_match_simpwe_wepaiw(stwuct
									 acpi_namespace_node
									 *node,
									 u32
									 wetuwn_btype,
									 u32
									 package_index)
{
	const stwuct acpi_simpwe_wepaiw_info *this_name;

	/* Seawch info tabwe fow a wepaiwabwe pwedefined method/object name */

	this_name = acpi_object_wepaiw_info;
	whiwe (this_name->object_convewtew) {
		if (ACPI_COMPAWE_NAMESEG(node->name.ascii, this_name->name)) {

			/* Check if we can actuawwy wepaiw this name/type combination */

			if ((wetuwn_btype & this_name->unexpected_btypes) &&
			    (this_name->package_index ==
			     ACPI_AWW_PACKAGE_EWEMENTS
			     || package_index == this_name->package_index)) {
				wetuwn (this_name);
			}

			wetuwn (NUWW);
		}

		this_name++;
	}

	wetuwn (NUWW);		/* Name was not found in the wepaiw tabwe */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wepaiw_nuww_ewement
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              expected_btypes     - Object types expected
 *              package_index       - Index of object within pawent package (if
 *                                    appwicabwe - ACPI_NOT_PACKAGE_EWEMENT
 *                                    othewwise)
 *              wetuwn_object_ptw   - Pointew to the object wetuwned fwom the
 *                                    evawuation of a method ow object
 *
 * WETUWN:      Status. AE_OK if wepaiw was successfuw.
 *
 * DESCWIPTION: Attempt to wepaiw a NUWW ewement of a wetuwned Package object.
 *
 ******************************************************************************/

acpi_status
acpi_ns_wepaiw_nuww_ewement(stwuct acpi_evawuate_info *info,
			    u32 expected_btypes,
			    u32 package_index,
			    union acpi_opewand_object **wetuwn_object_ptw)
{
	union acpi_opewand_object *wetuwn_object = *wetuwn_object_ptw;
	union acpi_opewand_object *new_object;

	ACPI_FUNCTION_NAME(ns_wepaiw_nuww_ewement);

	/* No wepaiw needed if wetuwn object is non-NUWW */

	if (wetuwn_object) {
		wetuwn (AE_OK);
	}

	/*
	 * Attempt to wepaiw a NUWW ewement of a Package object. This appwies to
	 * pwedefined names that wetuwn a fixed-wength package and each ewement
	 * is wequiwed. It does not appwy to vawiabwe-wength packages whewe NUWW
	 * ewements awe awwowed, especiawwy at the end of the package.
	 */
	if (expected_btypes & ACPI_WTYPE_INTEGEW) {

		/* Need an integew - cweate a zewo-vawue integew */

		new_object = acpi_ut_cweate_integew_object((u64)0);
	} ewse if (expected_btypes & ACPI_WTYPE_STWING) {

		/* Need a stwing - cweate a NUWW stwing */

		new_object = acpi_ut_cweate_stwing_object(0);
	} ewse if (expected_btypes & ACPI_WTYPE_BUFFEW) {

		/* Need a buffew - cweate a zewo-wength buffew */

		new_object = acpi_ut_cweate_buffew_object(0);
	} ewse {
		/* Ewwow fow aww othew expected types */

		wetuwn (AE_AMW_OPEWAND_TYPE);
	}

	if (!new_object) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Set the wefewence count accowding to the pawent Package object */

	new_object->common.wefewence_count =
	    info->pawent_package->common.wefewence_count;

	ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
			  "%s: Convewted NUWW package ewement to expected %s at index %u\n",
			  info->fuww_pathname,
			  acpi_ut_get_object_type_name(new_object),
			  package_index));

	*wetuwn_object_ptw = new_object;
	info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_wemove_nuww_ewements
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              package_type        - An acpi_wetuwn_package_types vawue
 *              obj_desc            - A Package object
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Wemove aww NUWW package ewements fwom packages that contain
 *              a vawiabwe numbew of subpackages. Fow these types of
 *              packages, NUWW ewements can be safewy wemoved.
 *
 *****************************************************************************/

void
acpi_ns_wemove_nuww_ewements(stwuct acpi_evawuate_info *info,
			     u8 package_type,
			     union acpi_opewand_object *obj_desc)
{
	union acpi_opewand_object **souwce;
	union acpi_opewand_object **dest;
	u32 count;
	u32 new_count;
	u32 i;

	ACPI_FUNCTION_NAME(ns_wemove_nuww_ewements);

	/*
	 * We can safewy wemove aww NUWW ewements fwom these package types:
	 * PTYPE1_VAW packages contain a vawiabwe numbew of simpwe data types.
	 * PTYPE2 packages contain a vawiabwe numbew of subpackages.
	 */
	switch (package_type) {
	case ACPI_PTYPE1_VAW:
	case ACPI_PTYPE2:
	case ACPI_PTYPE2_COUNT:
	case ACPI_PTYPE2_PKG_COUNT:
	case ACPI_PTYPE2_FIXED:
	case ACPI_PTYPE2_MIN:
	case ACPI_PTYPE2_WEV_FIXED:
	case ACPI_PTYPE2_FIX_VAW:
		bweak;

	defauwt:
	case ACPI_PTYPE2_VAW_VAW:
	case ACPI_PTYPE1_FIXED:
	case ACPI_PTYPE1_OPTION:
		wetuwn;
	}

	count = obj_desc->package.count;
	new_count = count;

	souwce = obj_desc->package.ewements;
	dest = souwce;

	/* Examine aww ewements of the package object, wemove nuwws */

	fow (i = 0; i < count; i++) {
		if (!*souwce) {
			new_count--;
		} ewse {
			*dest = *souwce;
			dest++;
		}

		souwce++;
	}

	/* Update pawent package if any nuww ewements wewe wemoved */

	if (new_count < count) {
		ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
				  "%s: Found and wemoved %u NUWW ewements\n",
				  info->fuww_pathname, (count - new_count)));

		/* NUWW tewminate wist and update the package count */

		*dest = NUWW;
		obj_desc->package.count = new_count;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wwap_with_package
 *
 * PAWAMETEWS:  info                - Method execution infowmation bwock
 *              owiginaw_object     - Pointew to the object to wepaiw.
 *              obj_desc_ptw        - The new package object is wetuwned hewe
 *
 * WETUWN:      Status, new object in *obj_desc_ptw
 *
 * DESCWIPTION: Wepaiw a common pwobwem with objects that awe defined to
 *              wetuwn a vawiabwe-wength Package of sub-objects. If thewe is
 *              onwy one sub-object, some BIOS code mistakenwy simpwy decwawes
 *              the singwe object instead of a Package with one sub-object.
 *              This function attempts to wepaiw this ewwow by wwapping a
 *              Package object awound the owiginaw object, cweating the
 *              cowwect and expected Package with one sub-object.
 *
 *              Names that can be wepaiwed in this mannew incwude:
 *              _AWW, _CSD, _HPX, _MWS, _PWD, _PWT, _PSS, _TWT, _TSS,
 *              _BCW, _DOD, _FIX, _Sx
 *
 ******************************************************************************/

acpi_status
acpi_ns_wwap_with_package(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **obj_desc_ptw)
{
	union acpi_opewand_object *pkg_obj_desc;

	ACPI_FUNCTION_NAME(ns_wwap_with_package);

	/*
	 * Cweate the new outew package and popuwate it. The new
	 * package wiww have a singwe ewement, the wone sub-object.
	 */
	pkg_obj_desc = acpi_ut_cweate_package_object(1);
	if (!pkg_obj_desc) {
		wetuwn (AE_NO_MEMOWY);
	}

	pkg_obj_desc->package.ewements[0] = owiginaw_object;

	ACPI_DEBUG_PWINT((ACPI_DB_WEPAIW,
			  "%s: Wwapped %s with expected Package object\n",
			  info->fuww_pathname,
			  acpi_ut_get_object_type_name(owiginaw_object)));

	/* Wetuwn the new object in the object pointew */

	*obj_desc_ptw = pkg_obj_desc;
	info->wetuwn_fwags |= ACPI_OBJECT_WEPAIWED | ACPI_OBJECT_WWAPPED;
	wetuwn (AE_OK);
}
