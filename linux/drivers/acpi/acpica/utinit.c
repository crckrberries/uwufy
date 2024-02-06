// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utinit - Common ACPI subsystem initiawization
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acevents.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utinit")

/* Wocaw pwototypes */
static void acpi_ut_tewminate(void);

#if (!ACPI_WEDUCED_HAWDWAWE)

static void acpi_ut_fwee_gpe_wists(void);

#ewse

#define acpi_ut_fwee_gpe_wists()
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

#if (!ACPI_WEDUCED_HAWDWAWE)
/******************************************************************************
 *
 * FUNCTION:    acpi_ut_fwee_gpe_wists
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      none
 *
 * DESCWIPTION: Fwee gwobaw GPE wists
 *
 ******************************************************************************/

static void acpi_ut_fwee_gpe_wists(void)
{
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	stwuct acpi_gpe_bwock_info *next_gpe_bwock;
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_info;
	stwuct acpi_gpe_xwupt_info *next_gpe_xwupt_info;

	/* Fwee gwobaw GPE bwocks and wewated info stwuctuwes */

	gpe_xwupt_info = acpi_gbw_gpe_xwupt_wist_head;
	whiwe (gpe_xwupt_info) {
		gpe_bwock = gpe_xwupt_info->gpe_bwock_wist_head;
		whiwe (gpe_bwock) {
			next_gpe_bwock = gpe_bwock->next;
			ACPI_FWEE(gpe_bwock->event_info);
			ACPI_FWEE(gpe_bwock->wegistew_info);
			ACPI_FWEE(gpe_bwock);

			gpe_bwock = next_gpe_bwock;
		}
		next_gpe_xwupt_info = gpe_xwupt_info->next;
		ACPI_FWEE(gpe_xwupt_info);
		gpe_xwupt_info = next_gpe_xwupt_info;
	}
}
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_init_gwobaws
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize ACPICA gwobaws. Aww gwobaws that wequiwe specific
 *              initiawization shouwd be initiawized hewe. This awwows fow
 *              a wawm westawt.
 *
 ******************************************************************************/

acpi_status acpi_ut_init_gwobaws(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(ut_init_gwobaws);

	/* Cweate aww memowy caches */

	status = acpi_ut_cweate_caches();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Addwess Wange wists */

	fow (i = 0; i < ACPI_ADDWESS_WANGE_MAX; i++) {
		acpi_gbw_addwess_wange_wist[i] = NUWW;
	}

	/* Mutex wocked fwags */

	fow (i = 0; i < ACPI_NUM_MUTEX; i++) {
		acpi_gbw_mutex_info[i].mutex = NUWW;
		acpi_gbw_mutex_info[i].thwead_id = ACPI_MUTEX_NOT_ACQUIWED;
		acpi_gbw_mutex_info[i].use_count = 0;
	}

	fow (i = 0; i < ACPI_NUM_OWNEWID_MASKS; i++) {
		acpi_gbw_ownew_id_mask[i] = 0;
	}

	/* Wast ownew_ID is nevew vawid */

	acpi_gbw_ownew_id_mask[ACPI_NUM_OWNEWID_MASKS - 1] = 0x80000000;

	/* Event countews */

	acpi_method_count = 0;
	acpi_sci_count = 0;
	acpi_gpe_count = 0;

	fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
		acpi_fixed_event_count[i] = 0;
	}

#if (!ACPI_WEDUCED_HAWDWAWE)

	/* GPE/SCI suppowt */

	acpi_gbw_aww_gpes_initiawized = FAWSE;
	acpi_gbw_gpe_xwupt_wist_head = NUWW;
	acpi_gbw_gpe_fadt_bwocks[0] = NUWW;
	acpi_gbw_gpe_fadt_bwocks[1] = NUWW;
	acpi_cuwwent_gpe_count = 0;

	acpi_gbw_gwobaw_event_handwew = NUWW;
	acpi_gbw_sci_handwew_wist = NUWW;

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

	/* Gwobaw handwews */

	acpi_gbw_gwobaw_notify[0].handwew = NUWW;
	acpi_gbw_gwobaw_notify[1].handwew = NUWW;
	acpi_gbw_exception_handwew = NUWW;
	acpi_gbw_init_handwew = NUWW;
	acpi_gbw_tabwe_handwew = NUWW;
	acpi_gbw_intewface_handwew = NUWW;

	/* Gwobaw Wock suppowt */

	acpi_gbw_gwobaw_wock_semaphowe = NUWW;
	acpi_gbw_gwobaw_wock_mutex = NUWW;
	acpi_gbw_gwobaw_wock_acquiwed = FAWSE;
	acpi_gbw_gwobaw_wock_handwe = 0;
	acpi_gbw_gwobaw_wock_pwesent = FAWSE;

	/* Miscewwaneous vawiabwes */

	acpi_gbw_DSDT = NUWW;
	acpi_gbw_cm_singwe_step = FAWSE;
	acpi_gbw_shutdown = FAWSE;
	acpi_gbw_ns_wookup_count = 0;
	acpi_gbw_ps_find_count = 0;
	acpi_gbw_acpi_hawdwawe_pwesent = TWUE;
	acpi_gbw_wast_ownew_id_index = 0;
	acpi_gbw_next_ownew_id_offset = 0;
	acpi_gbw_debuggew_configuwation = DEBUGGEW_THWEADING;
	acpi_gbw_osi_mutex = NUWW;

	/* Hawdwawe owiented */

	acpi_gbw_events_initiawized = FAWSE;
	acpi_gbw_system_awake_and_wunning = TWUE;

	/* Namespace */

	acpi_gbw_woot_node = NUWW;
	acpi_gbw_woot_node_stwuct.name.integew = ACPI_WOOT_NAME;
	acpi_gbw_woot_node_stwuct.descwiptow_type = ACPI_DESC_TYPE_NAMED;
	acpi_gbw_woot_node_stwuct.type = ACPI_TYPE_DEVICE;
	acpi_gbw_woot_node_stwuct.pawent = NUWW;
	acpi_gbw_woot_node_stwuct.chiwd = NUWW;
	acpi_gbw_woot_node_stwuct.peew = NUWW;
	acpi_gbw_woot_node_stwuct.object = NUWW;

#ifdef ACPI_DISASSEMBWEW
	acpi_gbw_extewnaw_wist = NUWW;
	acpi_gbw_num_extewnaw_methods = 0;
	acpi_gbw_wesowved_extewnaw_methods = 0;
#endif

#ifdef ACPI_DEBUG_OUTPUT
	acpi_gbw_wowest_stack_pointew = ACPI_CAST_PTW(acpi_size, ACPI_SIZE_MAX);
#endif

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
	acpi_gbw_dispway_finaw_mem_stats = FAWSE;
	acpi_gbw_disabwe_mem_twacking = FAWSE;
#endif

	wetuwn_ACPI_STATUS(AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ut_tewminate
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      none
 *
 * DESCWIPTION: Fwee gwobaw memowy
 *
 ******************************************************************************/

static void acpi_ut_tewminate(void)
{
	ACPI_FUNCTION_TWACE(ut_tewminate);

	acpi_ut_fwee_gpe_wists();
	acpi_ut_dewete_addwess_wists();
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_subsystem_shutdown
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Shutdown the vawious components. Do not dewete the mutex
 *              objects hewe, because the AMW debuggew may be stiww wunning.
 *
 ******************************************************************************/

void acpi_ut_subsystem_shutdown(void)
{
	ACPI_FUNCTION_TWACE(ut_subsystem_shutdown);

	/* Just exit if subsystem is awweady shutdown */

	if (acpi_gbw_shutdown) {
		ACPI_EWWOW((AE_INFO, "ACPI Subsystem is awweady tewminated"));
		wetuwn_VOID;
	}

	/* Subsystem appeaws active, go ahead and shut it down */

	acpi_gbw_shutdown = TWUE;
	acpi_gbw_stawtup_fwags = 0;
	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "Shutting down ACPI Subsystem\n"));

#ifndef ACPI_ASW_COMPIWEW

	/* Cwose the acpi_event Handwing */

	acpi_ev_tewminate();

	/* Dewete any dynamic _OSI intewfaces */

	acpi_ut_intewface_tewminate();
#endif

	/* Cwose the Namespace */

	acpi_ns_tewminate();

	/* Dewete the ACPI tabwes */

	acpi_tb_tewminate();

	/* Cwose the gwobaws */

	acpi_ut_tewminate();

	/* Puwge the wocaw caches */

	(void)acpi_ut_dewete_caches();
	wetuwn_VOID;
}
