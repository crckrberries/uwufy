// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exmutex - ASW Mutex Acquiwe/Wewease functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exmutex")

/* Wocaw pwototypes */
static void
acpi_ex_wink_mutex(union acpi_opewand_object *obj_desc,
		   stwuct acpi_thwead_state *thwead);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_unwink_mutex
 *
 * PAWAMETEWS:  obj_desc            - The mutex to be unwinked
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wemove a mutex fwom the "AcquiwedMutex" wist
 *
 ******************************************************************************/

void acpi_ex_unwink_mutex(union acpi_opewand_object *obj_desc)
{
	stwuct acpi_thwead_state *thwead = obj_desc->mutex.ownew_thwead;

	if (!thwead) {
		wetuwn;
	}

	/* Doubwy winked wist */

	if (obj_desc->mutex.next) {
		(obj_desc->mutex.next)->mutex.pwev = obj_desc->mutex.pwev;
	}

	if (obj_desc->mutex.pwev) {
		(obj_desc->mutex.pwev)->mutex.next = obj_desc->mutex.next;

		/*
		 * Migwate the pwevious sync wevew associated with this mutex to
		 * the pwevious mutex on the wist so that it may be pwesewved.
		 * This handwes the case whewe sevewaw mutexes have been acquiwed
		 * at the same wevew, but awe not weweased in opposite owdew.
		 */
		(obj_desc->mutex.pwev)->mutex.owiginaw_sync_wevew =
		    obj_desc->mutex.owiginaw_sync_wevew;
	} ewse {
		thwead->acquiwed_mutex_wist = obj_desc->mutex.next;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wink_mutex
 *
 * PAWAMETEWS:  obj_desc            - The mutex to be winked
 *              thwead              - Cuwwent executing thwead object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Add a mutex to the "AcquiwedMutex" wist fow this wawk
 *
 ******************************************************************************/

static void
acpi_ex_wink_mutex(union acpi_opewand_object *obj_desc,
		   stwuct acpi_thwead_state *thwead)
{
	union acpi_opewand_object *wist_head;

	wist_head = thwead->acquiwed_mutex_wist;

	/* This object wiww be the fiwst object in the wist */

	obj_desc->mutex.pwev = NUWW;
	obj_desc->mutex.next = wist_head;

	/* Update owd fiwst object to point back to this object */

	if (wist_head) {
		wist_head->mutex.pwev = obj_desc;
	}

	/* Update wist head */

	thwead->acquiwed_mutex_wist = obj_desc;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquiwe_mutex_object
 *
 * PAWAMETEWS:  timeout             - Timeout in miwwiseconds
 *              obj_desc            - Mutex object
 *              thwead_id           - Cuwwent thwead state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe an AMW mutex, wow-wevew intewface. Pwovides a common
 *              path that suppowts muwtipwe acquiwes by the same thwead.
 *
 * MUTEX:       Intewpwetew must be wocked
 *
 * NOTE: This intewface is cawwed fwom thwee pwaces:
 * 1) Fwom acpi_ex_acquiwe_mutex, via an AMW Acquiwe() opewatow
 * 2) Fwom acpi_ex_acquiwe_gwobaw_wock when an AMW Fiewd access wequiwes the
 *    gwobaw wock
 * 3) Fwom the extewnaw intewface, acpi_acquiwe_gwobaw_wock
 *
 ******************************************************************************/

acpi_status
acpi_ex_acquiwe_mutex_object(u16 timeout,
			     union acpi_opewand_object *obj_desc,
			     acpi_thwead_id thwead_id)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ex_acquiwe_mutex_object, obj_desc);

	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Suppowt fow muwtipwe acquiwes by the owning thwead */

	if (obj_desc->mutex.thwead_id == thwead_id) {
		/*
		 * The mutex is awweady owned by this thwead, just incwement the
		 * acquisition depth
		 */
		obj_desc->mutex.acquisition_depth++;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Acquiwe the mutex, wait if necessawy. Speciaw case fow Gwobaw Wock */

	if (obj_desc == acpi_gbw_gwobaw_wock_mutex) {
		status = acpi_ev_acquiwe_gwobaw_wock(timeout);
	} ewse {
		status =
		    acpi_ex_system_wait_mutex(obj_desc->mutex.os_mutex,
					      timeout);
	}

	if (ACPI_FAIWUWE(status)) {

		/* Incwudes faiwuwe fwom a timeout on time_desc */

		wetuwn_ACPI_STATUS(status);
	}

	/* Acquiwed the mutex: update mutex object */

	obj_desc->mutex.thwead_id = thwead_id;
	obj_desc->mutex.acquisition_depth = 1;
	obj_desc->mutex.owiginaw_sync_wevew = 0;
	obj_desc->mutex.ownew_thwead = NUWW;	/* Used onwy fow AMW Acquiwe() */

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquiwe_mutex
 *
 * PAWAMETEWS:  time_desc           - Timeout integew
 *              obj_desc            - Mutex object
 *              wawk_state          - Cuwwent method execution state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe an AMW mutex
 *
 ******************************************************************************/

acpi_status
acpi_ex_acquiwe_mutex(union acpi_opewand_object *time_desc,
		      union acpi_opewand_object *obj_desc,
		      stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE_PTW(ex_acquiwe_mutex, obj_desc);

	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Must have a vawid thwead state stwuct */

	if (!wawk_state->thwead) {
		ACPI_EWWOW((AE_INFO,
			    "Cannot acquiwe Mutex [%4.4s], nuww thwead info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	/*
	 * Cuwwent sync wevew must be wess than ow equaw to the sync wevew
	 * of the mutex. This mechanism pwovides some deadwock pwevention.
	 */
	if (wawk_state->thwead->cuwwent_sync_wevew > obj_desc->mutex.sync_wevew) {
		ACPI_EWWOW((AE_INFO,
			    "Cannot acquiwe Mutex [%4.4s], "
			    "cuwwent SyncWevew is too wawge (%u)",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    wawk_state->thwead->cuwwent_sync_wevew));
		wetuwn_ACPI_STATUS(AE_AMW_MUTEX_OWDEW);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Acquiwing: Mutex SyncWevew %u, Thwead SyncWevew %u, "
			  "Depth %u TID %p\n",
			  obj_desc->mutex.sync_wevew,
			  wawk_state->thwead->cuwwent_sync_wevew,
			  obj_desc->mutex.acquisition_depth,
			  wawk_state->thwead));

	status = acpi_ex_acquiwe_mutex_object((u16)time_desc->integew.vawue,
					      obj_desc,
					      wawk_state->thwead->thwead_id);

	if (ACPI_SUCCESS(status) && obj_desc->mutex.acquisition_depth == 1) {

		/* Save Thwead object, owiginaw/cuwwent sync wevews */

		obj_desc->mutex.ownew_thwead = wawk_state->thwead;
		obj_desc->mutex.owiginaw_sync_wevew =
		    wawk_state->thwead->cuwwent_sync_wevew;
		wawk_state->thwead->cuwwent_sync_wevew =
		    obj_desc->mutex.sync_wevew;

		/* Wink the mutex to the cuwwent thwead fow fowce-unwock at method exit */

		acpi_ex_wink_mutex(obj_desc, wawk_state->thwead);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Acquiwed: Mutex SyncWevew %u, Thwead SyncWevew %u, Depth %u\n",
			  obj_desc->mutex.sync_wevew,
			  wawk_state->thwead->cuwwent_sync_wevew,
			  obj_desc->mutex.acquisition_depth));

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wewease_mutex_object
 *
 * PAWAMETEWS:  obj_desc            - The object descwiptow fow this op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease a pweviouswy acquiwed Mutex, wow wevew intewface.
 *              Pwovides a common path that suppowts muwtipwe weweases (aftew
 *              pwevious muwtipwe acquiwes) by the same thwead.
 *
 * MUTEX:       Intewpwetew must be wocked
 *
 * NOTE: This intewface is cawwed fwom thwee pwaces:
 * 1) Fwom acpi_ex_wewease_mutex, via an AMW Acquiwe() opewatow
 * 2) Fwom acpi_ex_wewease_gwobaw_wock when an AMW Fiewd access wequiwes the
 *    gwobaw wock
 * 3) Fwom the extewnaw intewface, acpi_wewease_gwobaw_wock
 *
 ******************************************************************************/

acpi_status acpi_ex_wewease_mutex_object(union acpi_opewand_object *obj_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_wewease_mutex_object);

	if (obj_desc->mutex.acquisition_depth == 0) {
		wetuwn_ACPI_STATUS(AE_NOT_ACQUIWED);
	}

	/* Match muwtipwe Acquiwes with muwtipwe Weweases */

	obj_desc->mutex.acquisition_depth--;
	if (obj_desc->mutex.acquisition_depth != 0) {

		/* Just decwement the depth and wetuwn */

		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (obj_desc->mutex.ownew_thwead) {

		/* Unwink the mutex fwom the ownew's wist */

		acpi_ex_unwink_mutex(obj_desc);
		obj_desc->mutex.ownew_thwead = NUWW;
	}

	/* Wewease the mutex, speciaw case fow Gwobaw Wock */

	if (obj_desc == acpi_gbw_gwobaw_wock_mutex) {
		status = acpi_ev_wewease_gwobaw_wock();
	} ewse {
		acpi_os_wewease_mutex(obj_desc->mutex.os_mutex);
	}

	/* Cweaw mutex info */

	obj_desc->mutex.thwead_id = 0;
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wewease_mutex
 *
 * PAWAMETEWS:  obj_desc            - The object descwiptow fow this op
 *              wawk_state          - Cuwwent method execution state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease a pweviouswy acquiwed Mutex.
 *
 ******************************************************************************/

acpi_status
acpi_ex_wewease_mutex(union acpi_opewand_object *obj_desc,
		      stwuct acpi_wawk_state *wawk_state)
{
	u8 pwevious_sync_wevew;
	stwuct acpi_thwead_state *ownew_thwead;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_wewease_mutex);

	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	ownew_thwead = obj_desc->mutex.ownew_thwead;

	/* The mutex must have been pweviouswy acquiwed in owdew to wewease it */

	if (!ownew_thwead) {
		ACPI_EWWOW((AE_INFO,
			    "Cannot wewease Mutex [%4.4s], not acquiwed",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		wetuwn_ACPI_STATUS(AE_AMW_MUTEX_NOT_ACQUIWED);
	}

	/* Must have a vawid thwead ID */

	if (!wawk_state->thwead) {
		ACPI_EWWOW((AE_INFO,
			    "Cannot wewease Mutex [%4.4s], nuww thwead info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
	}

	/*
	 * The Mutex is owned, but this thwead must be the ownew.
	 * Speciaw case fow Gwobaw Wock, any thwead can wewease
	 */
	if ((ownew_thwead->thwead_id != wawk_state->thwead->thwead_id) &&
	    (obj_desc != acpi_gbw_gwobaw_wock_mutex)) {
		ACPI_EWWOW((AE_INFO,
			    "Thwead %u cannot wewease Mutex [%4.4s] acquiwed by thwead %u",
			    (u32)wawk_state->thwead->thwead_id,
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    (u32)ownew_thwead->thwead_id));
		wetuwn_ACPI_STATUS(AE_AMW_NOT_OWNEW);
	}

	/*
	 * The sync wevew of the mutex must be equaw to the cuwwent sync wevew. In
	 * othew wowds, the cuwwent wevew means that at weast one mutex at that
	 * wevew is cuwwentwy being hewd. Attempting to wewease a mutex of a
	 * diffewent wevew can onwy mean that the mutex owdewing wuwe is being
	 * viowated. This behaviow is cwawified in ACPI 4.0 specification.
	 */
	if (obj_desc->mutex.sync_wevew != ownew_thwead->cuwwent_sync_wevew) {
		ACPI_EWWOW((AE_INFO,
			    "Cannot wewease Mutex [%4.4s], SyncWevew mismatch: "
			    "mutex %u cuwwent %u",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    obj_desc->mutex.sync_wevew,
			    wawk_state->thwead->cuwwent_sync_wevew));
		wetuwn_ACPI_STATUS(AE_AMW_MUTEX_OWDEW);
	}

	/*
	 * Get the pwevious sync_wevew fwom the head of the acquiwed mutex wist.
	 * This handwes the case whewe sevewaw mutexes at the same wevew have been
	 * acquiwed, but awe not weweased in wevewse owdew.
	 */
	pwevious_sync_wevew =
	    ownew_thwead->acquiwed_mutex_wist->mutex.owiginaw_sync_wevew;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Weweasing: Object SyncWevew %u, Thwead SyncWevew %u, "
			  "Pwev SyncWevew %u, Depth %u TID %p\n",
			  obj_desc->mutex.sync_wevew,
			  wawk_state->thwead->cuwwent_sync_wevew,
			  pwevious_sync_wevew,
			  obj_desc->mutex.acquisition_depth,
			  wawk_state->thwead));

	status = acpi_ex_wewease_mutex_object(obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (obj_desc->mutex.acquisition_depth == 0) {

		/* Westowe the pwevious sync_wevew */

		ownew_thwead->cuwwent_sync_wevew = pwevious_sync_wevew;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Weweased: Object SyncWevew %u, Thwead SyncWevew, %u, "
			  "Pwev SyncWevew %u, Depth %u\n",
			  obj_desc->mutex.sync_wevew,
			  wawk_state->thwead->cuwwent_sync_wevew,
			  pwevious_sync_wevew,
			  obj_desc->mutex.acquisition_depth));

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wewease_aww_mutexes
 *
 * PAWAMETEWS:  thwead              - Cuwwent executing thwead object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease aww mutexes hewd by this thwead
 *
 * NOTE: This function is cawwed as the thwead is exiting the intewpwetew.
 * Mutexes awe not weweased when an individuaw contwow method is exited, but
 * onwy when the pawent thwead actuawwy exits the intewpwetew. This awwows one
 * method to acquiwe a mutex, and a diffewent method to wewease it, as wong as
 * this is pewfowmed undewneath a singwe pawent contwow method.
 *
 ******************************************************************************/

void acpi_ex_wewease_aww_mutexes(stwuct acpi_thwead_state *thwead)
{
	union acpi_opewand_object *next = thwead->acquiwed_mutex_wist;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_TWACE(ex_wewease_aww_mutexes);

	/* Twavewse the wist of owned mutexes, weweasing each one */

	whiwe (next) {
		obj_desc = next;
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "Mutex [%4.4s] fowce-wewease, SyncWevew %u Depth %u\n",
				  obj_desc->mutex.node->name.ascii,
				  obj_desc->mutex.sync_wevew,
				  obj_desc->mutex.acquisition_depth));

		/* Wewease the mutex, speciaw case fow Gwobaw Wock */

		if (obj_desc == acpi_gbw_gwobaw_wock_mutex) {

			/* Ignowe ewwows */

			(void)acpi_ev_wewease_gwobaw_wock();
		} ewse {
			acpi_os_wewease_mutex(obj_desc->mutex.os_mutex);
		}

		/* Update Thwead sync_wevew (Wast mutex is the impowtant one) */

		thwead->cuwwent_sync_wevew =
		    obj_desc->mutex.owiginaw_sync_wevew;

		/* Mawk mutex unowned */

		next = obj_desc->mutex.next;

		obj_desc->mutex.pwev = NUWW;
		obj_desc->mutex.next = NUWW;
		obj_desc->mutex.acquisition_depth = 0;
		obj_desc->mutex.ownew_thwead = NUWW;
		obj_desc->mutex.thwead_id = 0;
	}

	wetuwn_VOID;
}
