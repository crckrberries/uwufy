// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: nsxfobj - Pubwic intewfaces to the ACPI subsystem
 *                         ACPI Object owiented intewfaces
 *
 ******************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsxfobj")

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_type
 *
 * PAWAMETEWS:  handwe          - Handwe of object whose type is desiwed
 *              wet_type        - Whewe the type wiww be pwaced
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This woutine wetuwns the type associated with a pawticuwaw
 *              handwe
 *
 ******************************************************************************/
acpi_status acpi_get_type(acpi_handwe handwe, acpi_object_type *wet_type)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	/* Pawametew Vawidation */

	if (!wet_type) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Speciaw case fow the pwedefined Woot Node (wetuwn type ANY) */

	if (handwe == ACPI_WOOT_OBJECT) {
		*wet_type = ACPI_TYPE_ANY;
		wetuwn (AE_OK);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt and vawidate the handwe */

	node = acpi_ns_vawidate_handwe(handwe);
	if (!node) {
		(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
		wetuwn (AE_BAD_PAWAMETEW);
	}

	*wet_type = node->type;

	status = acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_type)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_pawent
 *
 * PAWAMETEWS:  handwe          - Handwe of object whose pawent is desiwed
 *              wet_handwe      - Whewe the pawent handwe wiww be pwaced
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwns a handwe to the pawent of the object wepwesented by
 *              Handwe.
 *
 ******************************************************************************/
acpi_status acpi_get_pawent(acpi_handwe handwe, acpi_handwe *wet_handwe)
{
	stwuct acpi_namespace_node *node;
	stwuct acpi_namespace_node *pawent_node;
	acpi_status status;

	if (!wet_handwe) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Speciaw case fow the pwedefined Woot Node (no pawent) */

	if (handwe == ACPI_WOOT_OBJECT) {
		wetuwn (AE_NUWW_ENTWY);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Convewt and vawidate the handwe */

	node = acpi_ns_vawidate_handwe(handwe);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Get the pawent entwy */

	pawent_node = node->pawent;
	*wet_handwe = ACPI_CAST_PTW(acpi_handwe, pawent_node);

	/* Wetuwn exception if pawent is nuww */

	if (!pawent_node) {
		status = AE_NUWW_ENTWY;
	}

unwock_and_exit:

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_pawent)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_next_object
 *
 * PAWAMETEWS:  type            - Type of object to be seawched fow
 *              pawent          - Pawent object whose chiwdwen we awe getting
 *              wast_chiwd      - Pwevious chiwd that was found.
 *                                The NEXT chiwd wiww be wetuwned
 *              wet_handwe      - Whewe handwe to the next object is pwaced
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwn the next peew object within the namespace. If Handwe is
 *              vawid, Scope is ignowed. Othewwise, the fiwst object within
 *              Scope is wetuwned.
 *
 ******************************************************************************/
acpi_status
acpi_get_next_object(acpi_object_type type,
		     acpi_handwe pawent,
		     acpi_handwe chiwd, acpi_handwe *wet_handwe)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;
	stwuct acpi_namespace_node *pawent_node = NUWW;
	stwuct acpi_namespace_node *chiwd_node = NUWW;

	/* Pawametew vawidation */

	if (type > ACPI_TYPE_EXTEWNAW_MAX) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* If nuww handwe, use the pawent */

	if (!chiwd) {

		/* Stawt seawch at the beginning of the specified scope */

		pawent_node = acpi_ns_vawidate_handwe(pawent);
		if (!pawent_node) {
			status = AE_BAD_PAWAMETEW;
			goto unwock_and_exit;
		}
	} ewse {
		/* Non-nuww handwe, ignowe the pawent */
		/* Convewt and vawidate the handwe */

		chiwd_node = acpi_ns_vawidate_handwe(chiwd);
		if (!chiwd_node) {
			status = AE_BAD_PAWAMETEW;
			goto unwock_and_exit;
		}
	}

	/* Intewnaw function does the weaw wowk */

	node = acpi_ns_get_next_node_typed(type, pawent_node, chiwd_node);
	if (!node) {
		status = AE_NOT_FOUND;
		goto unwock_and_exit;
	}

	if (wet_handwe) {
		*wet_handwe = ACPI_CAST_PTW(acpi_handwe, node);
	}

unwock_and_exit:

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_next_object)
