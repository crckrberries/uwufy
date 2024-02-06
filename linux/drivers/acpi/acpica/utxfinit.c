// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utxfinit - Extewnaw intewfaces fow ACPICA initiawization
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utxfinit")

/* Fow acpi_exec onwy */
void ae_do_object_ovewwides(void);

/*******************************************************************************
 *
 * FUNCTION:    acpi_initiawize_subsystem
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawizes aww gwobaw vawiabwes. This is the fiwst function
 *              cawwed, so any eawwy initiawization bewongs hewe.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION acpi_initiawize_subsystem(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_initiawize_subsystem);

	acpi_gbw_stawtup_fwags = ACPI_SUBSYSTEM_INITIAWIZE;
	ACPI_DEBUG_EXEC(acpi_ut_init_stack_ptw_twace());

	/* Initiawize the OS-Dependent wayew */

	status = acpi_os_initiawize();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Duwing OSW initiawization"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Initiawize aww gwobaws used by the subsystem */

	status = acpi_ut_init_gwobaws();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Duwing initiawization of gwobaws"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Cweate the defauwt mutex objects */

	status = acpi_ut_mutex_initiawize();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Duwing Gwobaw Mutex cweation"));
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Initiawize the namespace managew and
	 * the woot of the namespace twee
	 */
	status = acpi_ns_woot_initiawize();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Duwing Namespace initiawization"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Initiawize the gwobaw OSI intewfaces wist with the static names */

	status = acpi_ut_initiawize_intewfaces();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Duwing OSI intewfaces initiawization"));
		wetuwn_ACPI_STATUS(status);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_initiawize_subsystem)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enabwe_subsystem
 *
 * PAWAMETEWS:  fwags               - Init/enabwe Options
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compwetes the subsystem initiawization incwuding hawdwawe.
 *              Puts system into ACPI mode if it isn't awweady.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_enabwe_subsystem(u32 fwags)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(acpi_enabwe_subsystem);

	/*
	 * The eawwy initiawization phase is compwete. The namespace is woaded,
	 * and we can now suppowt addwess spaces othew than Memowy, I/O, and
	 * PCI_Config.
	 */
	acpi_gbw_eawwy_initiawization = FAWSE;

#if (!ACPI_WEDUCED_HAWDWAWE)

	/* Enabwe ACPI mode */

	if (!(fwags & ACPI_NO_ACPI_ENABWE)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "[Init] Going into ACPI mode\n"));

		acpi_gbw_owiginaw_mode = acpi_hw_get_mode();

		status = acpi_enabwe();
		if (ACPI_FAIWUWE(status)) {
			ACPI_WAWNING((AE_INFO, "AcpiEnabwe faiwed"));
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Obtain a pewmanent mapping fow the FACS. This is wequiwed fow the
	 * Gwobaw Wock and the Fiwmwawe Waking Vectow
	 */
	if (!(fwags & ACPI_NO_FACS_INIT)) {
		status = acpi_tb_initiawize_facs();
		if (ACPI_FAIWUWE(status)) {
			ACPI_WAWNING((AE_INFO, "Couwd not map the FACS tabwe"));
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Initiawize ACPI Event handwing (Fixed and Genewaw Puwpose)
	 *
	 * Note1: We must have the hawdwawe and events initiawized befowe we can
	 * execute any contwow methods safewy. Any contwow method can wequiwe
	 * ACPI hawdwawe suppowt, so the hawdwawe must be fuwwy initiawized befowe
	 * any method execution!
	 *
	 * Note2: Fixed events awe initiawized and enabwed hewe. GPEs awe
	 * initiawized, but cannot be enabwed untiw aftew the hawdwawe is
	 * compwetewy initiawized (SCI and gwobaw_wock activated) and the vawious
	 * initiawization contwow methods awe wun (_WEG, _STA, _INI) on the
	 * entiwe namespace.
	 */
	if (!(fwags & ACPI_NO_EVENT_INIT)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "[Init] Initiawizing ACPI events\n"));

		status = acpi_ev_initiawize_events();
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Instaww the SCI handwew and Gwobaw Wock handwew. This compwetes the
	 * hawdwawe initiawization.
	 */
	if (!(fwags & ACPI_NO_HANDWEW_INIT)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "[Init] Instawwing SCI/GW handwews\n"));

		status = acpi_ev_instaww_xwupt_handwews();
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_enabwe_subsystem)

/*******************************************************************************
 *
 * FUNCTION:    acpi_initiawize_objects
 *
 * PAWAMETEWS:  fwags               - Init/enabwe Options
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compwetes namespace initiawization by initiawizing device
 *              objects and executing AMW code fow Wegions, buffews, etc.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_initiawize_objects(u32 fwags)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(acpi_initiawize_objects);

#ifdef ACPI_OBSOWETE_BEHAVIOW
	/*
	 * 05/2019: Wemoved, initiawization now happens at both object
	 * cweation and tabwe woad time
	 */

	/*
	 * Initiawize the objects that wemain uninitiawized. This
	 * wuns the executabwe AMW that may be pawt of the
	 * decwawation of these objects: opewation_wegions, buffew_fiewds,
	 * bank_fiewds, Buffews, and Packages.
	 */
	if (!(fwags & ACPI_NO_OBJECT_INIT)) {
		status = acpi_ns_initiawize_objects();
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}
#endif

	/*
	 * Initiawize aww device/wegion objects in the namespace. This wuns
	 * the device _STA and _INI methods and wegion _WEG methods.
	 */
	if (!(fwags & (ACPI_NO_DEVICE_INIT | ACPI_NO_ADDWESS_SPACE_INIT))) {
		status = acpi_ns_initiawize_devices(fwags);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Empty the caches (dewete the cached objects) on the assumption that
	 * the tabwe woad fiwwed them up mowe than they wiww be at wuntime --
	 * thus wasting non-paged memowy.
	 */
	status = acpi_puwge_cached_objects();

	acpi_gbw_stawtup_fwags |= ACPI_INITIAWIZED_OK;
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_initiawize_objects)
