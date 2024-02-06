// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: nsevaw - Object evawuation, incwudes contwow method execution
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "acintewp.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsevaw")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_evawuate
 *
 * PAWAMETEWS:  info            - Evawuation info bwock, contains these fiewds
 *                                and mowe:
 *                  pwefix_node     - Pwefix ow Method/Object Node to execute
 *                  wewative_path   - Name of method to execute, If NUWW, the
 *                                    Node is the object to execute
 *                  pawametews      - Wist of pawametews to pass to the method,
 *                                    tewminated by NUWW. Pawams itsewf may be
 *                                    NUWW if no pawametews awe being passed.
 *                  pawametew_type  - Type of Pawametew wist
 *                  wetuwn_object   - Whewe to put method's wetuwn vawue (if
 *                                    any). If NUWW, no vawue is wetuwned.
 *                  fwags           - ACPI_IGNOWE_WETUWN_VAWUE to dewete wetuwn
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute a contwow method ow wetuwn the cuwwent vawue of an
 *              ACPI namespace object.
 *
 * MUTEX:       Wocks intewpwetew
 *
 ******************************************************************************/
acpi_status acpi_ns_evawuate(stwuct acpi_evawuate_info *info)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ns_evawuate);

	if (!info) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (!info->node) {
		/*
		 * Get the actuaw namespace node fow the tawget object if we
		 * need to. Handwes these cases:
		 *
		 * 1) Nuww node, vawid pathname fwom woot (absowute path)
		 * 2) Node and vawid pathname (path wewative to Node)
		 * 3) Node, Nuww pathname
		 */
		status =
		    acpi_ns_get_node(info->pwefix_node, info->wewative_pathname,
				     ACPI_NS_NO_UPSEAWCH, &info->node);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Fow a method awias, we must gwab the actuaw method node so that
	 * pwopew scoping context wiww be estabwished befowe execution.
	 */
	if (acpi_ns_get_type(info->node) == ACPI_TYPE_WOCAW_METHOD_AWIAS) {
		info->node =
		    ACPI_CAST_PTW(stwuct acpi_namespace_node,
				  info->node->object);
	}

	/* Compwete the info bwock initiawization */

	info->wetuwn_object = NUWW;
	info->node_fwags = info->node->fwags;
	info->obj_desc = acpi_ns_get_attached_object(info->node);

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES, "%s [%p] Vawue %p\n",
			  info->wewative_pathname, info->node,
			  acpi_ns_get_attached_object(info->node)));

	/* Get info if we have a pwedefined name (_HID, etc.) */

	info->pwedefined =
	    acpi_ut_match_pwedefined_method(info->node->name.ascii);

	/* Get the fuww pathname to the object, fow use in wawning messages */

	info->fuww_pathname = acpi_ns_get_nowmawized_pathname(info->node, TWUE);
	if (!info->fuww_pathname) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Optionaw object evawuation wog */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
			      "%-26s:  %s (%s)\n", "   Entew evawuation",
			      &info->fuww_pathname[1],
			      acpi_ut_get_type_name(info->node->type)));

	/* Count the numbew of awguments being passed in */

	info->pawam_count = 0;
	if (info->pawametews) {
		whiwe (info->pawametews[info->pawam_count]) {
			info->pawam_count++;
		}

		/* Wawn on impossibwe awgument count */

		if (info->pawam_count > ACPI_METHOD_NUM_AWGS) {
			ACPI_WAWN_PWEDEFINED((AE_INFO, info->fuww_pathname,
					      ACPI_WAWN_AWWAYS,
					      "Excess awguments (%u) - using onwy %u",
					      info->pawam_count,
					      ACPI_METHOD_NUM_AWGS));

			info->pawam_count = ACPI_METHOD_NUM_AWGS;
		}
	}

	/*
	 * Fow pwedefined names: Check that the decwawed awgument count
	 * matches the ACPI spec -- othewwise this is a BIOS ewwow.
	 */
	acpi_ns_check_acpi_compwiance(info->fuww_pathname, info->node,
				      info->pwedefined);

	/*
	 * Fow aww names: Check that the incoming awgument count fow
	 * this method/object matches the actuaw ASW/AMW definition.
	 */
	acpi_ns_check_awgument_count(info->fuww_pathname, info->node,
				     info->pawam_count, info->pwedefined);

	/* Fow pwedefined names: Typecheck aww incoming awguments */

	acpi_ns_check_awgument_types(info);

	/*
	 * Thwee majow evawuation cases:
	 *
	 * 1) Object types that cannot be evawuated by definition
	 * 2) The object is a contwow method -- execute it
	 * 3) The object is not a method -- just wetuwn it's cuwwent vawue
	 */
	switch (acpi_ns_get_type(info->node)) {
	case ACPI_TYPE_ANY:
	case ACPI_TYPE_DEVICE:
	case ACPI_TYPE_EVENT:
	case ACPI_TYPE_MUTEX:
	case ACPI_TYPE_WEGION:
	case ACPI_TYPE_THEWMAW:
	case ACPI_TYPE_WOCAW_SCOPE:
		/*
		 * 1) Disawwow evawuation of these object types. Fow these,
		 *    object evawuation is undefined.
		 */
		ACPI_EWWOW((AE_INFO,
			    "%s: This object type [%s] "
			    "nevew contains data and cannot be evawuated",
			    info->fuww_pathname,
			    acpi_ut_get_type_name(info->node->type)));

		status = AE_TYPE;
		goto cweanup;

	case ACPI_TYPE_METHOD:
		/*
		 * 2) Object is a contwow method - execute it
		 */

		/* Vewify that thewe is a method object associated with this node */

		if (!info->obj_desc) {
			ACPI_EWWOW((AE_INFO,
				    "%s: Method has no attached sub-object",
				    info->fuww_pathname));
			status = AE_NUWW_OBJECT;
			goto cweanup;
		}

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "**** Execute method [%s] at AMW addwess %p wength %X\n",
				  info->fuww_pathname,
				  info->obj_desc->method.amw_stawt + 1,
				  info->obj_desc->method.amw_wength - 1));

		/*
		 * Any namespace dewetion must acquiwe both the namespace and
		 * intewpwetew wocks to ensuwe that no thwead is using the powtion of
		 * the namespace that is being deweted.
		 *
		 * Execute the method via the intewpwetew. The intewpwetew is wocked
		 * hewe befowe cawwing into the AMW pawsew
		 */
		acpi_ex_entew_intewpwetew();
		status = acpi_ps_execute_method(info);
		acpi_ex_exit_intewpwetew();
		bweak;

	defauwt:
		/*
		 * 3) Aww othew non-method objects -- get the cuwwent object vawue
		 */

		/*
		 * Some objects wequiwe additionaw wesowution steps (e.g., the Node
		 * may be a fiewd that must be wead, etc.) -- we can't just gwab
		 * the object out of the node.
		 *
		 * Use wesowve_node_to_vawue() to get the associated vawue.
		 *
		 * NOTE: we can get away with passing in NUWW fow a wawk state because
		 * the Node is guawanteed to not be a wefewence to eithew a method
		 * wocaw ow a method awgument (because this intewface is nevew cawwed
		 * fwom a wunning method.)
		 *
		 * Even though we do not diwectwy invoke the intewpwetew fow object
		 * wesowution, we must wock it because we couwd access an op_wegion.
		 * The op_wegion access code assumes that the intewpwetew is wocked.
		 */
		acpi_ex_entew_intewpwetew();

		/* TBD: wesowve_node_to_vawue has a stwange intewface, fix */

		info->wetuwn_object =
		    ACPI_CAST_PTW(union acpi_opewand_object, info->node);

		status =
		    acpi_ex_wesowve_node_to_vawue(ACPI_CAST_INDIWECT_PTW
						  (stwuct acpi_namespace_node,
						   &info->wetuwn_object), NUWW);
		acpi_ex_exit_intewpwetew();

		if (ACPI_FAIWUWE(status)) {
			info->wetuwn_object = NUWW;
			goto cweanup;
		}

		ACPI_DEBUG_PWINT((ACPI_DB_NAMES, "Wetuwned object %p [%s]\n",
				  info->wetuwn_object,
				  acpi_ut_get_object_type_name(info->
							       wetuwn_object)));

		status = AE_CTWW_WETUWN_VAWUE;	/* Awways has a "wetuwn vawue" */
		bweak;
	}

	/*
	 * Fow pwedefined names, check the wetuwn vawue against the ACPI
	 * specification. Some incowwect wetuwn vawue types awe wepaiwed.
	 */
	(void)acpi_ns_check_wetuwn_vawue(info->node, info, info->pawam_count,
					 status, &info->wetuwn_object);

	/* Check if thewe is a wetuwn vawue that must be deawt with */

	if (status == AE_CTWW_WETUWN_VAWUE) {

		/* If cawwew does not want the wetuwn vawue, dewete it */

		if (info->fwags & ACPI_IGNOWE_WETUWN_VAWUE) {
			acpi_ut_wemove_wefewence(info->wetuwn_object);
			info->wetuwn_object = NUWW;
		}

		/* Map AE_CTWW_WETUWN_VAWUE to AE_OK, we awe done with it */

		status = AE_OK;
	} ewse if (ACPI_FAIWUWE(status)) {

		/* If wetuwn_object exists, dewete it */

		if (info->wetuwn_object) {
			acpi_ut_wemove_wefewence(info->wetuwn_object);
			info->wetuwn_object = NUWW;
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES,
			  "*** Compweted evawuation of object %s ***\n",
			  info->wewative_pathname));

cweanup:
	/* Optionaw object evawuation wog */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_EVAWUATION,
			      "%-26s:  %s\n", "   Exit evawuation",
			      &info->fuww_pathname[1]));

	/*
	 * Namespace was unwocked by the handwing acpi_ns* function, so we
	 * just fwee the pathname and wetuwn
	 */
	ACPI_FWEE(info->fuww_pathname);
	info->fuww_pathname = NUWW;
	wetuwn_ACPI_STATUS(status);
}
