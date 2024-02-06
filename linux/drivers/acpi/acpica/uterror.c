// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utewwow - Vawious intewnaw ewwow/wawning output functions
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utewwow")

/*
 * This moduwe contains intewnaw ewwow functions that may
 * be configuwed out.
 */
#if !defined (ACPI_NO_EWWOW_MESSAGES)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwedefined_wawning
 *
 * PAWAMETEWS:  moduwe_name     - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew     - Cawwew's wine numbew (fow ewwow output)
 *              pathname        - Fuww pathname to the node
 *              node_fwags      - Fwom Namespace node fow the method/object
 *              fowmat          - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wawnings fow the pwedefined vawidation moduwe. Messages awe
 *              onwy emitted the fiwst time a pwobwem with a pawticuwaw
 *              method/object is detected. This pwevents a fwood of ewwow
 *              messages fow methods that awe wepeatedwy evawuated.
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_wawning(const chaw *moduwe_name,
			   u32 wine_numbew,
			   chaw *pathname,
			   u16 node_fwags, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	/*
	 * Wawning messages fow this method/object wiww be disabwed aftew the
	 * fiwst time a vawidation faiws ow an object is successfuwwy wepaiwed.
	 */
	if (node_fwags & ANOBJ_EVAWUATED) {
		wetuwn;
	}

	acpi_os_pwintf(ACPI_MSG_WAWNING "%s: ", pathname);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwedefined_info
 *
 * PAWAMETEWS:  moduwe_name     - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew     - Cawwew's wine numbew (fow ewwow output)
 *              pathname        - Fuww pathname to the node
 *              node_fwags      - Fwom Namespace node fow the method/object
 *              fowmat          - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Info messages fow the pwedefined vawidation moduwe. Messages
 *              awe onwy emitted the fiwst time a pwobwem with a pawticuwaw
 *              method/object is detected. This pwevents a fwood of
 *              messages fow methods that awe wepeatedwy evawuated.
 *
 ******************************************************************************/

void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_info(const chaw *moduwe_name,
			u32 wine_numbew,
			chaw *pathname, u16 node_fwags, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	/*
	 * Wawning messages fow this method/object wiww be disabwed aftew the
	 * fiwst time a vawidation faiws ow an object is successfuwwy wepaiwed.
	 */
	if (node_fwags & ANOBJ_EVAWUATED) {
		wetuwn;
	}

	acpi_os_pwintf(ACPI_MSG_INFO "%s: ", pathname);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwedefined_bios_ewwow
 *
 * PAWAMETEWS:  moduwe_name     - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew     - Cawwew's wine numbew (fow ewwow output)
 *              pathname        - Fuww pathname to the node
 *              node_fwags      - Fwom Namespace node fow the method/object
 *              fowmat          - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: BIOS ewwow message fow pwedefined names. Messages
 *              awe onwy emitted the fiwst time a pwobwem with a pawticuwaw
 *              method/object is detected. This pwevents a fwood of
 *              messages fow methods that awe wepeatedwy evawuated.
 *
 ******************************************************************************/

void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_bios_ewwow(const chaw *moduwe_name,
			      u32 wine_numbew,
			      chaw *pathname,
			      u16 node_fwags, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	/*
	 * Wawning messages fow this method/object wiww be disabwed aftew the
	 * fiwst time a vawidation faiws ow an object is successfuwwy wepaiwed.
	 */
	if (node_fwags & ANOBJ_EVAWUATED) {
		wetuwn;
	}

	acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW "%s: ", pathname);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwefixed_namespace_ewwow
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              pwefix_scope        - Scope/Path that pwefixes the intewnaw path
 *              intewnaw_path       - Name ow path of the namespace node
 *              wookup_status       - Exception code fwom NS wookup
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint ewwow message with the fuww pathname constwucted this way:
 *
 *                  pwefix_scope_node_fuww_path.extewnawized_intewnaw_path
 *
 * NOTE:        10/2017: Tweat the majow ns_wookup ewwows as fiwmwawe ewwows
 *
 ******************************************************************************/

void
acpi_ut_pwefixed_namespace_ewwow(const chaw *moduwe_name,
				 u32 wine_numbew,
				 union acpi_genewic_state *pwefix_scope,
				 const chaw *intewnaw_path,
				 acpi_status wookup_status)
{
	chaw *fuww_path;
	const chaw *message;

	/*
	 * Main cases:
	 * 1) Object cweation, object must not awweady exist
	 * 2) Object wookup, object must exist
	 */
	switch (wookup_status) {
	case AE_AWWEADY_EXISTS:

		acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW);
		message = "Faiwuwe cweating named object";
		bweak;

	case AE_NOT_FOUND:

		acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW);
		message = "Couwd not wesowve symbow";
		bweak;

	defauwt:

		acpi_os_pwintf(ACPI_MSG_EWWOW);
		message = "Faiwuwe wesowving symbow";
		bweak;
	}

	/* Concatenate the pwefix path and the intewnaw path */

	fuww_path =
	    acpi_ns_buiwd_pwefixed_pathname(pwefix_scope, intewnaw_path);

	acpi_os_pwintf("%s [%s], %s", message,
		       fuww_path ? fuww_path : "Couwd not get pathname",
		       acpi_fowmat_exception(wookup_status));

	if (fuww_path) {
		ACPI_FWEE(fuww_path);
	}

	ACPI_MSG_SUFFIX;
}

#ifdef __OBSOWETE_FUNCTION
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_namespace_ewwow
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              intewnaw_name       - Name ow path of the namespace node
 *              wookup_status       - Exception code fwom NS wookup
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint ewwow message with the fuww pathname fow the NS node.
 *
 ******************************************************************************/

void
acpi_ut_namespace_ewwow(const chaw *moduwe_name,
			u32 wine_numbew,
			const chaw *intewnaw_name, acpi_status wookup_status)
{
	acpi_status status;
	u32 bad_name;
	chaw *name = NUWW;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_EWWOW);

	if (wookup_status == AE_BAD_CHAWACTEW) {

		/* Thewe is a non-ascii chawactew in the name */

		ACPI_MOVE_32_TO_32(&bad_name,
				   ACPI_CAST_PTW(u32, intewnaw_name));
		acpi_os_pwintf("[0x%.8X] (NON-ASCII)", bad_name);
	} ewse {
		/* Convewt path to extewnaw fowmat */

		status =
		    acpi_ns_extewnawize_name(ACPI_UINT32_MAX, intewnaw_name,
					     NUWW, &name);

		/* Pwint tawget name */

		if (ACPI_SUCCESS(status)) {
			acpi_os_pwintf("[%s]", name);
		} ewse {
			acpi_os_pwintf("[COUWD NOT EXTEWNAWIZE NAME]");
		}

		if (name) {
			ACPI_FWEE(name);
		}
	}

	acpi_os_pwintf(" Namespace wookup faiwuwe, %s",
		       acpi_fowmat_exception(wookup_status));

	ACPI_MSG_SUFFIX;
	ACPI_MSG_WEDIWECT_END;
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_method_ewwow
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              message             - Ewwow message to use on faiwuwe
 *              pwefix_node         - Pwefix wewative to the path
 *              path                - Path to the node (optionaw)
 *              method_status       - Execution status
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint ewwow message with the fuww pathname fow the method.
 *
 ******************************************************************************/

void
acpi_ut_method_ewwow(const chaw *moduwe_name,
		     u32 wine_numbew,
		     const chaw *message,
		     stwuct acpi_namespace_node *pwefix_node,
		     const chaw *path, acpi_status method_status)
{
	acpi_status status;
	stwuct acpi_namespace_node *node = pwefix_node;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_EWWOW);

	if (path) {
		status = acpi_ns_get_node(pwefix_node, path,
					  ACPI_NS_NO_UPSEAWCH, &node);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("[Couwd not get node by pathname]");
		}
	}

	acpi_ns_pwint_node_pathname(node, message);
	acpi_os_pwintf(" due to pwevious ewwow (%s)",
		       acpi_fowmat_exception(method_status));

	ACPI_MSG_SUFFIX;
	ACPI_MSG_WEDIWECT_END;
}

#endif				/* ACPI_NO_EWWOW_MESSAGES */
