// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utxfmutex - extewnaw AMW mutex access functions
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utxfmutex")

/* Wocaw pwototypes */
static acpi_status
acpi_ut_get_mutex_object(acpi_handwe handwe,
			 acpi_stwing pathname,
			 union acpi_opewand_object **wet_obj);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_mutex_object
 *
 * PAWAMETEWS:  handwe              - Mutex ow pwefix handwe (optionaw)
 *              pathname            - Mutex pathname (optionaw)
 *              wet_obj             - Whewe the mutex object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get an AMW mutex object. The mutex node is pointed to by
 *              Handwe:Pathname. Eithew Handwe ow Pathname can be NUWW, but
 *              not both.
 *
 ******************************************************************************/

static acpi_status
acpi_ut_get_mutex_object(acpi_handwe handwe,
			 acpi_stwing pathname,
			 union acpi_opewand_object **wet_obj)
{
	stwuct acpi_namespace_node *mutex_node;
	union acpi_opewand_object *mutex_obj;
	acpi_status status;

	/* Pawametew vawidation */

	if (!wet_obj || (!handwe && !pathname)) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Get a the namespace node fow the mutex */

	mutex_node = handwe;
	if (pathname != NUWW) {
		status =
		    acpi_get_handwe(handwe, pathname,
				    ACPI_CAST_PTW(acpi_handwe, &mutex_node));
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	/* Ensuwe that we actuawwy have a Mutex object */

	if (!mutex_node || (mutex_node->type != ACPI_TYPE_MUTEX)) {
		wetuwn (AE_TYPE);
	}

	/* Get the wow-wevew mutex object */

	mutex_obj = acpi_ns_get_attached_object(mutex_node);
	if (!mutex_obj) {
		wetuwn (AE_NUWW_OBJECT);
	}

	*wet_obj = mutex_obj;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_acquiwe_mutex
 *
 * PAWAMETEWS:  handwe              - Mutex ow pwefix handwe (optionaw)
 *              pathname            - Mutex pathname (optionaw)
 *              timeout             - Max time to wait fow the wock (miwwisec)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe an AMW mutex. This is a device dwivew intewface to
 *              AMW mutex objects, and awwows fow twansaction wocking between
 *              dwivews and AMW code. The mutex node is pointed to by
 *              Handwe:Pathname. Eithew Handwe ow Pathname can be NUWW, but
 *              not both.
 *
 ******************************************************************************/

acpi_status
acpi_acquiwe_mutex(acpi_handwe handwe, acpi_stwing pathname, u16 timeout)
{
	acpi_status status;
	union acpi_opewand_object *mutex_obj;

	/* Get the wow-wevew mutex associated with Handwe:Pathname */

	status = acpi_ut_get_mutex_object(handwe, pathname, &mutex_obj);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Acquiwe the OS mutex */

	status = acpi_os_acquiwe_mutex(mutex_obj->mutex.os_mutex, timeout);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_acquiwe_mutex)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wewease_mutex
 *
 * PAWAMETEWS:  handwe              - Mutex ow pwefix handwe (optionaw)
 *              pathname            - Mutex pathname (optionaw)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease an AMW mutex. This is a device dwivew intewface to
 *              AMW mutex objects, and awwows fow twansaction wocking between
 *              dwivews and AMW code. The mutex node is pointed to by
 *              Handwe:Pathname. Eithew Handwe ow Pathname can be NUWW, but
 *              not both.
 *
 ******************************************************************************/
acpi_status acpi_wewease_mutex(acpi_handwe handwe, acpi_stwing pathname)
{
	acpi_status status;
	union acpi_opewand_object *mutex_obj;

	/* Get the wow-wevew mutex associated with Handwe:Pathname */

	status = acpi_ut_get_mutex_object(handwe, pathname, &mutex_obj);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Wewease the OS mutex */

	acpi_os_wewease_mutex(mutex_obj->mutex.os_mutex);
	wetuwn (AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_wewease_mutex)
