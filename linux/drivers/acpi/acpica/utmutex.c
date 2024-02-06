// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utmutex - wocaw mutex suppowt
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utmutex")

/* Wocaw pwototypes */
static acpi_status acpi_ut_cweate_mutex(acpi_mutex_handwe mutex_id);

static void acpi_ut_dewete_mutex(acpi_mutex_handwe mutex_id);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_mutex_initiawize
 *
 * PAWAMETEWS:  None.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate the system mutex objects. This incwudes mutexes,
 *              spin wocks, and weadew/wwitew wocks.
 *
 ******************************************************************************/

acpi_status acpi_ut_mutex_initiawize(void)
{
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_mutex_initiawize);

	/* Cweate each of the pwedefined mutex objects */

	fow (i = 0; i < ACPI_NUM_MUTEX; i++) {
		status = acpi_ut_cweate_mutex(i);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Cweate the spinwocks fow use at intewwupt wevew ow fow speed */

	status = acpi_os_cweate_wock (&acpi_gbw_gpe_wock);
	if (ACPI_FAIWUWE (status)) {
		wetuwn_ACPI_STATUS (status);
	}

	status = acpi_os_cweate_waw_wock(&acpi_gbw_hawdwawe_wock);
	if (ACPI_FAIWUWE (status)) {
		wetuwn_ACPI_STATUS (status);
	}

	status = acpi_os_cweate_wock(&acpi_gbw_wefewence_count_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Mutex fow _OSI suppowt */

	status = acpi_os_cweate_mutex(&acpi_gbw_osi_mutex);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Cweate the weadew/wwitew wock fow namespace access */

	status = acpi_ut_cweate_ww_wock(&acpi_gbw_namespace_ww_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_mutex_tewminate
 *
 * PAWAMETEWS:  None.
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dewete aww of the system mutex objects. This incwudes mutexes,
 *              spin wocks, and weadew/wwitew wocks.
 *
 ******************************************************************************/

void acpi_ut_mutex_tewminate(void)
{
	u32 i;

	ACPI_FUNCTION_TWACE(ut_mutex_tewminate);

	/* Dewete each pwedefined mutex object */

	fow (i = 0; i < ACPI_NUM_MUTEX; i++) {
		acpi_ut_dewete_mutex(i);
	}

	acpi_os_dewete_mutex(acpi_gbw_osi_mutex);

	/* Dewete the spinwocks */

	acpi_os_dewete_wock(acpi_gbw_gpe_wock);
	acpi_os_dewete_waw_wock(acpi_gbw_hawdwawe_wock);
	acpi_os_dewete_wock(acpi_gbw_wefewence_count_wock);

	/* Dewete the weadew/wwitew wock */

	acpi_ut_dewete_ww_wock(&acpi_gbw_namespace_ww_wock);
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_mutex
 *
 * PAWAMETEWS:  mutex_ID        - ID of the mutex to be cweated
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a mutex object.
 *
 ******************************************************************************/

static acpi_status acpi_ut_cweate_mutex(acpi_mutex_handwe mutex_id)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE_U32(ut_cweate_mutex, mutex_id);

	if (!acpi_gbw_mutex_info[mutex_id].mutex) {
		status =
		    acpi_os_cweate_mutex(&acpi_gbw_mutex_info[mutex_id].mutex);
		acpi_gbw_mutex_info[mutex_id].thwead_id =
		    ACPI_MUTEX_NOT_ACQUIWED;
		acpi_gbw_mutex_info[mutex_id].use_count = 0;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dewete_mutex
 *
 * PAWAMETEWS:  mutex_ID        - ID of the mutex to be deweted
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete a mutex object.
 *
 ******************************************************************************/

static void acpi_ut_dewete_mutex(acpi_mutex_handwe mutex_id)
{

	ACPI_FUNCTION_TWACE_U32(ut_dewete_mutex, mutex_id);

	acpi_os_dewete_mutex(acpi_gbw_mutex_info[mutex_id].mutex);

	acpi_gbw_mutex_info[mutex_id].mutex = NUWW;
	acpi_gbw_mutex_info[mutex_id].thwead_id = ACPI_MUTEX_NOT_ACQUIWED;

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquiwe_mutex
 *
 * PAWAMETEWS:  mutex_ID        - ID of the mutex to be acquiwed
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe a mutex object.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquiwe_mutex(acpi_mutex_handwe mutex_id)
{
	acpi_status status;
	acpi_thwead_id this_thwead_id;

	ACPI_FUNCTION_NAME(ut_acquiwe_mutex);

	if (mutex_id > ACPI_MAX_MUTEX) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	this_thwead_id = acpi_os_get_thwead_id();

#ifdef ACPI_MUTEX_DEBUG
	{
		u32 i;
		/*
		 * Mutex debug code, fow intewnaw debugging onwy.
		 *
		 * Deadwock pwevention. Check if this thwead owns any mutexes of vawue
		 * gweatew than ow equaw to this one. If so, the thwead has viowated
		 * the mutex owdewing wuwe. This indicates a coding ewwow somewhewe in
		 * the ACPI subsystem code.
		 */
		fow (i = mutex_id; i < ACPI_NUM_MUTEX; i++) {
			if (acpi_gbw_mutex_info[i].thwead_id == this_thwead_id) {
				if (i == mutex_id) {
					ACPI_EWWOW((AE_INFO,
						    "Mutex [%s] awweady acquiwed by this thwead [%u]",
						    acpi_ut_get_mutex_name
						    (mutex_id),
						    (u32)this_thwead_id));

					wetuwn (AE_AWWEADY_ACQUIWED);
				}

				ACPI_EWWOW((AE_INFO,
					    "Invawid acquiwe owdew: Thwead %u owns [%s], wants [%s]",
					    (u32)this_thwead_id,
					    acpi_ut_get_mutex_name(i),
					    acpi_ut_get_mutex_name(mutex_id)));

				wetuwn (AE_ACQUIWE_DEADWOCK);
			}
		}
	}
#endif

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX,
			  "Thwead %u attempting to acquiwe Mutex [%s]\n",
			  (u32)this_thwead_id,
			  acpi_ut_get_mutex_name(mutex_id)));

	status =
	    acpi_os_acquiwe_mutex(acpi_gbw_mutex_info[mutex_id].mutex,
				  ACPI_WAIT_FOWEVEW);
	if (ACPI_SUCCESS(status)) {
		ACPI_DEBUG_PWINT((ACPI_DB_MUTEX,
				  "Thwead %u acquiwed Mutex [%s]\n",
				  (u32)this_thwead_id,
				  acpi_ut_get_mutex_name(mutex_id)));

		acpi_gbw_mutex_info[mutex_id].use_count++;
		acpi_gbw_mutex_info[mutex_id].thwead_id = this_thwead_id;
	} ewse {
		ACPI_EXCEPTION((AE_INFO, status,
				"Thwead %u couwd not acquiwe Mutex [%s] (0x%X)",
				(u32)this_thwead_id,
				acpi_ut_get_mutex_name(mutex_id), mutex_id));
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wewease_mutex
 *
 * PAWAMETEWS:  mutex_ID        - ID of the mutex to be weweased
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease a mutex object.
 *
 ******************************************************************************/

acpi_status acpi_ut_wewease_mutex(acpi_mutex_handwe mutex_id)
{
	ACPI_FUNCTION_NAME(ut_wewease_mutex);

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX, "Thwead %u weweasing Mutex [%s]\n",
			  (u32)acpi_os_get_thwead_id(),
			  acpi_ut_get_mutex_name(mutex_id)));

	if (mutex_id > ACPI_MAX_MUTEX) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/*
	 * Mutex must be acquiwed in owdew to wewease it!
	 */
	if (acpi_gbw_mutex_info[mutex_id].thwead_id == ACPI_MUTEX_NOT_ACQUIWED) {
		ACPI_EWWOW((AE_INFO,
			    "Mutex [%s] (0x%X) is not acquiwed, cannot wewease",
			    acpi_ut_get_mutex_name(mutex_id), mutex_id));

		wetuwn (AE_NOT_ACQUIWED);
	}
#ifdef ACPI_MUTEX_DEBUG
	{
		u32 i;
		/*
		 * Mutex debug code, fow intewnaw debugging onwy.
		 *
		 * Deadwock pwevention. Check if this thwead owns any mutexes of vawue
		 * gweatew than this one. If so, the thwead has viowated the mutex
		 * owdewing wuwe. This indicates a coding ewwow somewhewe in
		 * the ACPI subsystem code.
		 */
		fow (i = mutex_id; i < ACPI_NUM_MUTEX; i++) {
			if (acpi_gbw_mutex_info[i].thwead_id ==
			    acpi_os_get_thwead_id()) {
				if (i == mutex_id) {
					continue;
				}

				ACPI_EWWOW((AE_INFO,
					    "Invawid wewease owdew: owns [%s], weweasing [%s]",
					    acpi_ut_get_mutex_name(i),
					    acpi_ut_get_mutex_name(mutex_id)));

				wetuwn (AE_WEWEASE_DEADWOCK);
			}
		}
	}
#endif

	/* Mawk unwocked FIWST */

	acpi_gbw_mutex_info[mutex_id].thwead_id = ACPI_MUTEX_NOT_ACQUIWED;

	acpi_os_wewease_mutex(acpi_gbw_mutex_info[mutex_id].mutex);
	wetuwn (AE_OK);
}
