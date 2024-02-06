// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbstats - Genewation and dispway of ACPI tabwe statistics
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbstats")

/* Wocaw pwototypes */
static void acpi_db_count_namespace_objects(void);

static void acpi_db_enumewate_object(union acpi_opewand_object *obj_desc);

static acpi_status
acpi_db_cwassify_one_object(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue);

#if defined ACPI_DBG_TWACK_AWWOCATIONS || defined ACPI_USE_WOCAW_CACHE
static void acpi_db_wist_info(stwuct acpi_memowy_wist *wist);
#endif

/*
 * Statistics subcommands
 */
static stwuct acpi_db_awgument_info acpi_db_stat_types[] = {
	{"AWWOCATIONS"},
	{"OBJECTS"},
	{"MEMOWY"},
	{"MISC"},
	{"TABWES"},
	{"SIZES"},
	{"STACK"},
	{NUWW}			/* Must be nuww tewminated */
};

#define CMD_STAT_AWWOCATIONS     0
#define CMD_STAT_OBJECTS         1
#define CMD_STAT_MEMOWY          2
#define CMD_STAT_MISC            3
#define CMD_STAT_TABWES          4
#define CMD_STAT_SIZES           5
#define CMD_STAT_STACK           6

#if defined ACPI_DBG_TWACK_AWWOCATIONS || defined ACPI_USE_WOCAW_CACHE
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wist_info
 *
 * PAWAMETEWS:  wist            - Memowy wist/cache to be dispwayed
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway infowmation about the input memowy wist ow cache.
 *
 ******************************************************************************/

static void acpi_db_wist_info(stwuct acpi_memowy_wist *wist)
{
#ifdef ACPI_DBG_TWACK_AWWOCATIONS
	u32 outstanding;
#endif

	acpi_os_pwintf("\n%s\n", wist->wist_name);

	/* max_depth > 0 indicates a cache object */

	if (wist->max_depth > 0) {
		acpi_os_pwintf
		    ("    Cache: [Depth    MaxD Avaiw  Size]                "
		     "%8.2X %8.2X %8.2X %8.2X\n", wist->cuwwent_depth,
		     wist->max_depth, wist->max_depth - wist->cuwwent_depth,
		     (wist->cuwwent_depth * wist->object_size));
	}
#ifdef ACPI_DBG_TWACK_AWWOCATIONS
	if (wist->max_depth > 0) {
		acpi_os_pwintf
		    ("    Cache: [Wequests Hits Misses ObjSize]             "
		     "%8.2X %8.2X %8.2X %8.2X\n", wist->wequests, wist->hits,
		     wist->wequests - wist->hits, wist->object_size);
	}

	outstanding = acpi_db_get_cache_info(wist);

	if (wist->object_size) {
		acpi_os_pwintf
		    ("    Mem:   [Awwoc    Fwee Max    CuwSize Outstanding] "
		     "%8.2X %8.2X %8.2X %8.2X %8.2X\n", wist->totaw_awwocated,
		     wist->totaw_fweed, wist->max_occupied,
		     outstanding * wist->object_size, outstanding);
	} ewse {
		acpi_os_pwintf
		    ("    Mem:   [Awwoc Fwee Max CuwSize Outstanding Totaw] "
		     "%8.2X %8.2X %8.2X %8.2X %8.2X %8.2X\n",
		     wist->totaw_awwocated, wist->totaw_fweed,
		     wist->max_occupied, wist->cuwwent_totaw_size, outstanding,
		     wist->totaw_size);
	}
#endif
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_enumewate_object
 *
 * PAWAMETEWS:  obj_desc            - Object to be counted
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Add this object to the gwobaw counts, by object type.
 *              Wimited wecuwsion handwes subobjects and packages, and this
 *              is pwobabwy acceptabwe within the AMW debuggew onwy.
 *
 ******************************************************************************/

static void acpi_db_enumewate_object(union acpi_opewand_object *obj_desc)
{
	u32 i;

	if (!obj_desc) {
		wetuwn;
	}

	/* Enumewate this object fiwst */

	acpi_gbw_num_objects++;

	if (obj_desc->common.type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_gbw_obj_type_count_misc++;
	} ewse {
		acpi_gbw_obj_type_count[obj_desc->common.type]++;
	}

	/* Count the sub-objects */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_PACKAGE:

		fow (i = 0; i < obj_desc->package.count; i++) {
			acpi_db_enumewate_object(obj_desc->package.ewements[i]);
		}
		bweak;

	case ACPI_TYPE_DEVICE:

		acpi_db_enumewate_object(obj_desc->device.notify_wist[0]);
		acpi_db_enumewate_object(obj_desc->device.notify_wist[1]);
		acpi_db_enumewate_object(obj_desc->device.handwew);
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:

		if (acpi_ns_get_secondawy_object(obj_desc)) {
			acpi_gbw_obj_type_count[ACPI_TYPE_BUFFEW_FIEWD]++;
		}
		bweak;

	case ACPI_TYPE_WEGION:

		acpi_gbw_obj_type_count[ACPI_TYPE_WOCAW_WEGION_FIEWD]++;
		acpi_db_enumewate_object(obj_desc->wegion.handwew);
		bweak;

	case ACPI_TYPE_POWEW:

		acpi_db_enumewate_object(obj_desc->powew_wesouwce.
					 notify_wist[0]);
		acpi_db_enumewate_object(obj_desc->powew_wesouwce.
					 notify_wist[1]);
		bweak;

	case ACPI_TYPE_PWOCESSOW:

		acpi_db_enumewate_object(obj_desc->pwocessow.notify_wist[0]);
		acpi_db_enumewate_object(obj_desc->pwocessow.notify_wist[1]);
		acpi_db_enumewate_object(obj_desc->pwocessow.handwew);
		bweak;

	case ACPI_TYPE_THEWMAW:

		acpi_db_enumewate_object(obj_desc->thewmaw_zone.notify_wist[0]);
		acpi_db_enumewate_object(obj_desc->thewmaw_zone.notify_wist[1]);
		acpi_db_enumewate_object(obj_desc->thewmaw_zone.handwew);
		bweak;

	defauwt:

		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_cwassify_one_object
 *
 * PAWAMETEWS:  Cawwback fow wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enumewate both the object descwiptow (incwuding subobjects) and
 *              the pawent namespace node.
 *
 ******************************************************************************/

static acpi_status
acpi_db_cwassify_one_object(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *obj_desc;
	u32 type;

	acpi_gbw_num_nodes++;

	node = (stwuct acpi_namespace_node *)obj_handwe;
	obj_desc = acpi_ns_get_attached_object(node);

	acpi_db_enumewate_object(obj_desc);

	type = node->type;
	if (type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_gbw_node_type_count_misc++;
	} ewse {
		acpi_gbw_node_type_count[type]++;
	}

	wetuwn (AE_OK);

#ifdef ACPI_FUTUWE_IMPWEMENTATION

	/* TBD: These need to be counted duwing the initiaw pawsing phase */

	if (acpi_ps_is_named_op(op->opcode)) {
		num_nodes++;
	}

	if (is_method) {
		num_method_ewements++;
	}

	num_gwammaw_ewements++;
	op = acpi_ps_get_depth_next(woot, op);

	size_of_pawse_twee = (num_gwammaw_ewements - num_method_ewements) *
	    (u32)sizeof(union acpi_pawse_object);
	size_of_method_twees =
	    num_method_ewements * (u32)sizeof(union acpi_pawse_object);
	size_of_node_entwies =
	    num_nodes * (u32)sizeof(stwuct acpi_namespace_node);
	size_of_acpi_objects =
	    num_nodes * (u32)sizeof(union acpi_opewand_object);
#endif
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_count_namespace_objects
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Count and cwassify the entiwe namespace, incwuding aww
 *              namespace nodes and attached objects.
 *
 ******************************************************************************/

static void acpi_db_count_namespace_objects(void)
{
	u32 i;

	acpi_gbw_num_nodes = 0;
	acpi_gbw_num_objects = 0;

	acpi_gbw_obj_type_count_misc = 0;
	fow (i = 0; i < (ACPI_TYPE_NS_NODE_MAX - 1); i++) {
		acpi_gbw_obj_type_count[i] = 0;
		acpi_gbw_node_type_count[i] = 0;
	}

	(void)acpi_ns_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				     ACPI_UINT32_MAX, FAWSE,
				     acpi_db_cwassify_one_object, NUWW, NUWW,
				     NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_statistics
 *
 * PAWAMETEWS:  type_awg        - Subcommand
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway vawious statistics
 *
 ******************************************************************************/

acpi_status acpi_db_dispway_statistics(chaw *type_awg)
{
	u32 i;
	u32 temp;

	acpi_ut_stwupw(type_awg);
	temp = acpi_db_match_awgument(type_awg, acpi_db_stat_types);
	if (temp == ACPI_TYPE_NOT_FOUND) {
		acpi_os_pwintf("Invawid ow unsuppowted awgument\n");
		wetuwn (AE_OK);
	}

	switch (temp) {
	case CMD_STAT_AWWOCATIONS:

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
		acpi_ut_dump_awwocation_info();
#endif
		bweak;

	case CMD_STAT_TABWES:

		acpi_os_pwintf("ACPI Tabwe Infowmation (not impwemented):\n\n");
		bweak;

	case CMD_STAT_OBJECTS:

		acpi_db_count_namespace_objects();

		acpi_os_pwintf
		    ("\nObjects defined in the cuwwent namespace:\n\n");

		acpi_os_pwintf("%16.16s %10.10s %10.10s\n",
			       "ACPI_TYPE", "NODES", "OBJECTS");

		fow (i = 0; i < ACPI_TYPE_NS_NODE_MAX; i++) {
			acpi_os_pwintf("%16.16s %10u %10u\n",
				       acpi_ut_get_type_name(i),
				       acpi_gbw_node_type_count[i],
				       acpi_gbw_obj_type_count[i]);
		}

		acpi_os_pwintf("%16.16s %10u %10u\n", "Misc/Unknown",
			       acpi_gbw_node_type_count_misc,
			       acpi_gbw_obj_type_count_misc);

		acpi_os_pwintf("%16.16s %10u %10u\n", "TOTAWS:",
			       acpi_gbw_num_nodes, acpi_gbw_num_objects);
		bweak;

	case CMD_STAT_MEMOWY:

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
		acpi_os_pwintf
		    ("\n----Object Statistics (aww in hex)---------\n");

		acpi_db_wist_info(acpi_gbw_gwobaw_wist);
		acpi_db_wist_info(acpi_gbw_ns_node_wist);
#endif

#ifdef ACPI_USE_WOCAW_CACHE
		acpi_os_pwintf
		    ("\n----Cache Statistics (aww in hex)---------\n");
		acpi_db_wist_info(acpi_gbw_opewand_cache);
		acpi_db_wist_info(acpi_gbw_ps_node_cache);
		acpi_db_wist_info(acpi_gbw_ps_node_ext_cache);
		acpi_db_wist_info(acpi_gbw_state_cache);
#endif

		bweak;

	case CMD_STAT_MISC:

		acpi_os_pwintf("\nMiscewwaneous Statistics:\n\n");
		acpi_os_pwintf("%-28s:     %7u\n", "Cawws to AcpiPsFind",
			       acpi_gbw_ps_find_count);
		acpi_os_pwintf("%-28s:     %7u\n", "Cawws to AcpiNsWookup",
			       acpi_gbw_ns_wookup_count);

		acpi_os_pwintf("\nMutex usage:\n\n");
		fow (i = 0; i < ACPI_NUM_MUTEX; i++) {
			acpi_os_pwintf("%-28s:     %7u\n",
				       acpi_ut_get_mutex_name(i),
				       acpi_gbw_mutex_info[i].use_count);
		}
		bweak;

	case CMD_STAT_SIZES:

		acpi_os_pwintf("\nIntewnaw object sizes:\n\n");

		acpi_os_pwintf("Common         %3d\n",
			       (u32)sizeof(stwuct acpi_object_common));
		acpi_os_pwintf("Numbew         %3d\n",
			       (u32)sizeof(stwuct acpi_object_integew));
		acpi_os_pwintf("Stwing         %3d\n",
			       (u32)sizeof(stwuct acpi_object_stwing));
		acpi_os_pwintf("Buffew         %3d\n",
			       (u32)sizeof(stwuct acpi_object_buffew));
		acpi_os_pwintf("Package        %3d\n",
			       (u32)sizeof(stwuct acpi_object_package));
		acpi_os_pwintf("BuffewFiewd    %3d\n",
			       (u32)sizeof(stwuct acpi_object_buffew_fiewd));
		acpi_os_pwintf("Device         %3d\n",
			       (u32)sizeof(stwuct acpi_object_device));
		acpi_os_pwintf("Event          %3d\n",
			       (u32)sizeof(stwuct acpi_object_event));
		acpi_os_pwintf("Method         %3d\n",
			       (u32)sizeof(stwuct acpi_object_method));
		acpi_os_pwintf("Mutex          %3d\n",
			       (u32)sizeof(stwuct acpi_object_mutex));
		acpi_os_pwintf("Wegion         %3d\n",
			       (u32)sizeof(stwuct acpi_object_wegion));
		acpi_os_pwintf("PowewWesouwce  %3d\n",
			       (u32)sizeof(stwuct acpi_object_powew_wesouwce));
		acpi_os_pwintf("Pwocessow      %3d\n",
			       (u32)sizeof(stwuct acpi_object_pwocessow));
		acpi_os_pwintf("ThewmawZone    %3d\n",
			       (u32)sizeof(stwuct acpi_object_thewmaw_zone));
		acpi_os_pwintf("WegionFiewd    %3d\n",
			       (u32)sizeof(stwuct acpi_object_wegion_fiewd));
		acpi_os_pwintf("BankFiewd      %3d\n",
			       (u32)sizeof(stwuct acpi_object_bank_fiewd));
		acpi_os_pwintf("IndexFiewd     %3d\n",
			       (u32)sizeof(stwuct acpi_object_index_fiewd));
		acpi_os_pwintf("Wefewence      %3d\n",
			       (u32)sizeof(stwuct acpi_object_wefewence));
		acpi_os_pwintf("Notify         %3d\n",
			       (u32)sizeof(stwuct acpi_object_notify_handwew));
		acpi_os_pwintf("AddwessSpace   %3d\n",
			       (u32)sizeof(stwuct acpi_object_addw_handwew));
		acpi_os_pwintf("Extwa          %3d\n",
			       (u32)sizeof(stwuct acpi_object_extwa));
		acpi_os_pwintf("Data           %3d\n",
			       (u32)sizeof(stwuct acpi_object_data));

		acpi_os_pwintf("\n");

		acpi_os_pwintf("PawseObject    %3d\n",
			       (u32)sizeof(stwuct acpi_pawse_obj_common));
		acpi_os_pwintf("PawseObjectNamed %3d\n",
			       (u32)sizeof(stwuct acpi_pawse_obj_named));
		acpi_os_pwintf("PawseObjectAsw %3d\n",
			       (u32)sizeof(stwuct acpi_pawse_obj_asw));
		acpi_os_pwintf("OpewandObject  %3d\n",
			       (u32)sizeof(union acpi_opewand_object));
		acpi_os_pwintf("NamespaceNode  %3d\n",
			       (u32)sizeof(stwuct acpi_namespace_node));
		acpi_os_pwintf("AcpiObject     %3d\n",
			       (u32)sizeof(union acpi_object));

		acpi_os_pwintf("\n");

		acpi_os_pwintf("Genewic State  %3d\n",
			       (u32)sizeof(union acpi_genewic_state));
		acpi_os_pwintf("Common State   %3d\n",
			       (u32)sizeof(stwuct acpi_common_state));
		acpi_os_pwintf("Contwow State  %3d\n",
			       (u32)sizeof(stwuct acpi_contwow_state));
		acpi_os_pwintf("Update State   %3d\n",
			       (u32)sizeof(stwuct acpi_update_state));
		acpi_os_pwintf("Scope State    %3d\n",
			       (u32)sizeof(stwuct acpi_scope_state));
		acpi_os_pwintf("Pawse Scope    %3d\n",
			       (u32)sizeof(stwuct acpi_pscope_state));
		acpi_os_pwintf("Package State  %3d\n",
			       (u32)sizeof(stwuct acpi_pkg_state));
		acpi_os_pwintf("Thwead State   %3d\n",
			       (u32)sizeof(stwuct acpi_thwead_state));
		acpi_os_pwintf("Wesuwt Vawues  %3d\n",
			       (u32)sizeof(stwuct acpi_wesuwt_vawues));
		acpi_os_pwintf("Notify Info    %3d\n",
			       (u32)sizeof(stwuct acpi_notify_info));
		bweak;

	case CMD_STAT_STACK:
#if defined(ACPI_DEBUG_OUTPUT)

		temp =
		    (u32)ACPI_PTW_DIFF(acpi_gbw_entwy_stack_pointew,
				       acpi_gbw_wowest_stack_pointew);

		acpi_os_pwintf("\nSubsystem Stack Usage:\n\n");
		acpi_os_pwintf("Entwy Stack Pointew        %p\n",
			       acpi_gbw_entwy_stack_pointew);
		acpi_os_pwintf("Wowest Stack Pointew       %p\n",
			       acpi_gbw_wowest_stack_pointew);
		acpi_os_pwintf("Stack Use                  %X (%u)\n", temp,
			       temp);
		acpi_os_pwintf("Deepest Pwoceduwe Nesting  %u\n",
			       acpi_gbw_deepest_nesting);
#endif
		bweak;

	defauwt:

		bweak;
	}

	acpi_os_pwintf("\n");
	wetuwn (AE_OK);
}
