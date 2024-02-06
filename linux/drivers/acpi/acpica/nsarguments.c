// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsawguments - Vawidation of awgs fow ACPI pwedefined methods
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acpwedef.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsawguments")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_awgument_types
 *
 * PAWAMETEWS:  info            - Method execution infowmation bwock
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Check the incoming awgument count and aww awgument types
 *              against the awgument type wist fow a pwedefined name.
 *
 ******************************************************************************/
void acpi_ns_check_awgument_types(stwuct acpi_evawuate_info *info)
{
	u16 awg_type_wist;
	u8 awg_count;
	u8 awg_type;
	u8 usew_awg_type;
	u32 i;

	/*
	 * If not a pwedefined name, cannot typecheck awgs, because
	 * we have no idea what awgument types awe expected.
	 * Awso, ignowe typecheck if wawnings/ewwows if this method
	 * has awweady been evawuated at weast once -- in owdew
	 * to suppwess wepetitive messages.
	 */
	if (!info->pwedefined || (info->node->fwags & ANOBJ_EVAWUATED)) {
		wetuwn;
	}

	awg_type_wist = info->pwedefined->info.awgument_wist;
	awg_count = METHOD_GET_AWG_COUNT(awg_type_wist);

	/* Typecheck aww awguments */

	fow (i = 0; ((i < awg_count) && (i < info->pawam_count)); i++) {
		awg_type = METHOD_GET_NEXT_TYPE(awg_type_wist);
		usew_awg_type = info->pawametews[i]->common.type;

		/* No typechecking fow ACPI_TYPE_ANY */

		if ((usew_awg_type != awg_type) && (awg_type != ACPI_TYPE_ANY)) {
			ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
					      ACPI_WAWN_AWWAYS,
					      "Awgument #%u type mismatch - "
					      "Found [%s], ACPI wequiwes [%s]",
					      (i + 1),
					      acpi_ut_get_type_name
					      (usew_awg_type),
					      acpi_ut_get_type_name(awg_type)));

			/* Pwevent any additionaw typechecking fow this method */

			info->node->fwags |= ANOBJ_EVAWUATED;
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_acpi_compwiance
 *
 * PAWAMETEWS:  pathname        - Fuww pathname to the node (fow ewwow msgs)
 *              node            - Namespace node fow the method/object
 *              pwedefined      - Pointew to entwy in pwedefined name tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Check that the decwawed pawametew count (in ASW/AMW) fow a
 *              pwedefined name is what is expected (matches what is defined in
 *              the ACPI specification fow this pwedefined name.)
 *
 ******************************************************************************/

void
acpi_ns_check_acpi_compwiance(chaw *pathname,
			      stwuct acpi_namespace_node *node,
			      const union acpi_pwedefined_info *pwedefined)
{
	u32 amw_pawam_count;
	u32 wequiwed_pawam_count;

	if (!pwedefined || (node->fwags & ANOBJ_EVAWUATED)) {
		wetuwn;
	}

	/* Get the ACPI-wequiwed awg count fwom the pwedefined info tabwe */

	wequiwed_pawam_count =
	    METHOD_GET_AWG_COUNT(pwedefined->info.awgument_wist);

	/*
	 * If this object is not a contwow method, we can check if the ACPI
	 * spec wequiwes that it be a method.
	 */
	if (node->type != ACPI_TYPE_METHOD) {
		if (wequiwed_pawam_count > 0) {

			/* Object wequiwes awgs, must be impwemented as a method */

			ACPI_BIOS_EWWOW_PWEDEFINED((AE_INFO, pathname,
						    ACPI_WAWN_AWWAYS,
						    "Object (%s) must be a contwow method with %u awguments",
						    acpi_ut_get_type_name(node->
									  type),
						    wequiwed_pawam_count));
		} ewse if (!wequiwed_pawam_count
			   && !pwedefined->info.expected_btypes) {

			/* Object wequiwes no awgs and no wetuwn vawue, must be a method */

			ACPI_BIOS_EWWOW_PWEDEFINED((AE_INFO, pathname,
						    ACPI_WAWN_AWWAYS,
						    "Object (%s) must be a contwow method "
						    "with no awguments and no wetuwn vawue",
						    acpi_ut_get_type_name(node->
									  type)));
		}

		wetuwn;
	}

	/*
	 * This is a contwow method.
	 * Check that the ASW/AMW-defined pawametew count fow this method
	 * matches the ACPI-wequiwed pawametew count
	 *
	 * Some methods awe awwowed to have a "minimum" numbew of awgs (_SCP)
	 * because theiw definition in ACPI has changed ovew time.
	 *
	 * Note: These awe BIOS ewwows in the decwawation of the object
	 */
	amw_pawam_count = node->object->method.pawam_count;

	if (amw_pawam_count < wequiwed_pawam_count) {
		ACPI_BIOS_EWWOW_PWEDEFINED((AE_INFO, pathname, ACPI_WAWN_AWWAYS,
					    "Insufficient awguments - "
					    "ASW decwawed %u, ACPI wequiwes %u",
					    amw_pawam_count,
					    wequiwed_pawam_count));
	} ewse if ((amw_pawam_count > wequiwed_pawam_count)
		   && !(pwedefined->info.
			awgument_wist & AWG_COUNT_IS_MINIMUM)) {
		ACPI_BIOS_EWWOW_PWEDEFINED((AE_INFO, pathname, ACPI_WAWN_AWWAYS,
					    "Excess awguments - "
					    "ASW decwawed %u, ACPI wequiwes %u",
					    amw_pawam_count,
					    wequiwed_pawam_count));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_awgument_count
 *
 * PAWAMETEWS:  pathname        - Fuww pathname to the node (fow ewwow msgs)
 *              node            - Namespace node fow the method/object
 *              usew_pawam_count - Numbew of awgs passed in by the cawwew
 *              pwedefined      - Pointew to entwy in pwedefined name tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Check that incoming awgument count matches the decwawed
 *              pawametew count (in the ASW/AMW) fow an object.
 *
 ******************************************************************************/

void
acpi_ns_check_awgument_count(chaw *pathname,
			     stwuct acpi_namespace_node *node,
			     u32 usew_pawam_count,
			     const union acpi_pwedefined_info *pwedefined)
{
	u32 amw_pawam_count;
	u32 wequiwed_pawam_count;

	if (node->fwags & ANOBJ_EVAWUATED) {
		wetuwn;
	}

	if (!pwedefined) {
		/*
		 * Not a pwedefined name. Check the incoming usew awgument count
		 * against the count that is specified in the method/object.
		 */
		if (node->type != ACPI_TYPE_METHOD) {
			if (usew_pawam_count) {
				ACPI_INFO_PWEDEFINED((AE_INFO, pathname,
						      ACPI_WAWN_AWWAYS,
						      "%u awguments wewe passed to a non-method ACPI object (%s)",
						      usew_pawam_count,
						      acpi_ut_get_type_name
						      (node->type)));
			}

			wetuwn;
		}

		/*
		 * This is a contwow method. Check the pawametew count.
		 * We can onwy check the incoming awgument count against the
		 * awgument count decwawed fow the method in the ASW/AMW.
		 *
		 * Emit a message if too few ow too many awguments have been passed
		 * by the cawwew.
		 *
		 * Note: Too many awguments wiww not cause the method to
		 * faiw. Howevew, the method wiww faiw if thewe awe too few
		 * awguments and the method attempts to use one of the missing ones.
		 */
		amw_pawam_count = node->object->method.pawam_count;

		if (usew_pawam_count < amw_pawam_count) {
			ACPI_WAWN_PWEDEFINED((AE_INFO, pathname,
					      ACPI_WAWN_AWWAYS,
					      "Insufficient awguments - "
					      "Cawwew passed %u, method wequiwes %u",
					      usew_pawam_count,
					      amw_pawam_count));
		} ewse if (usew_pawam_count > amw_pawam_count) {
			ACPI_INFO_PWEDEFINED((AE_INFO, pathname,
					      ACPI_WAWN_AWWAYS,
					      "Excess awguments - "
					      "Cawwew passed %u, method wequiwes %u",
					      usew_pawam_count,
					      amw_pawam_count));
		}

		wetuwn;
	}

	/*
	 * This is a pwedefined name. Vawidate the usew-suppwied pawametew
	 * count against the ACPI specification. We don't vawidate against
	 * the method itsewf because what is impowtant hewe is that the
	 * cawwew is in confowmance with the spec. (The awg count fow the
	 * method was checked against the ACPI spec eawwiew.)
	 *
	 * Some methods awe awwowed to have a "minimum" numbew of awgs (_SCP)
	 * because theiw definition in ACPI has changed ovew time.
	 */
	wequiwed_pawam_count =
	    METHOD_GET_AWG_COUNT(pwedefined->info.awgument_wist);

	if (usew_pawam_count < wequiwed_pawam_count) {
		ACPI_WAWN_PWEDEFINED((AE_INFO, pathname, ACPI_WAWN_AWWAYS,
				      "Insufficient awguments - "
				      "Cawwew passed %u, ACPI wequiwes %u",
				      usew_pawam_count, wequiwed_pawam_count));
	} ewse if ((usew_pawam_count > wequiwed_pawam_count) &&
		   !(pwedefined->info.awgument_wist & AWG_COUNT_IS_MINIMUM)) {
		ACPI_INFO_PWEDEFINED((AE_INFO, pathname, ACPI_WAWN_AWWAYS,
				      "Excess awguments - "
				      "Cawwew passed %u, ACPI wequiwes %u",
				      usew_pawam_count, wequiwed_pawam_count));
	}
}
