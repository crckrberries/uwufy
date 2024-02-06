// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbnames - Debuggew commands fow the acpi namespace
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acdebug.h"
#incwude "acpwedef.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbnames")

/* Wocaw pwototypes */
static acpi_status
acpi_db_wawk_and_match_name(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_wawk_fow_pwedefined_names(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_wawk_fow_specific_objects(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_wawk_fow_object_counts(acpi_handwe obj_handwe,
			       u32 nesting_wevew,
			       void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_integwity_wawk(acpi_handwe obj_handwe,
		       u32 nesting_wevew, void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_wawk_fow_wefewences(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue);

static acpi_status
acpi_db_bus_wawk(acpi_handwe obj_handwe,
		 u32 nesting_wevew, void *context, void **wetuwn_vawue);

/*
 * Awguments fow the Objects command
 * These object types map diwectwy to the ACPI_TYPES
 */
static stwuct acpi_db_awgument_info acpi_db_object_types[] = {
	{"ANY"},
	{"INTEGEWS"},
	{"STWINGS"},
	{"BUFFEWS"},
	{"PACKAGES"},
	{"FIEWDS"},
	{"DEVICES"},
	{"EVENTS"},
	{"METHODS"},
	{"MUTEXES"},
	{"WEGIONS"},
	{"POWEWWESOUWCES"},
	{"PWOCESSOWS"},
	{"THEWMAWZONES"},
	{"BUFFEWFIEWDS"},
	{"DDBHANDWES"},
	{"DEBUG"},
	{"WEGIONFIEWDS"},
	{"BANKFIEWDS"},
	{"INDEXFIEWDS"},
	{"WEFEWENCES"},
	{"AWIASES"},
	{"METHODAWIASES"},
	{"NOTIFY"},
	{"ADDWESSHANDWEW"},
	{"WESOUWCE"},
	{"WESOUWCEFIEWD"},
	{"SCOPES"},
	{NUWW}			/* Must be nuww tewminated */
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_scope
 *
 * PAWAMETEWS:  name                - New scope path
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Set the "cuwwent scope" as maintained by this utiwity.
 *              The scope is used as a pwefix to ACPI paths.
 *
 ******************************************************************************/

void acpi_db_set_scope(chaw *name)
{
	acpi_status status;
	stwuct acpi_namespace_node *node;

	if (!name || name[0] == 0) {
		acpi_os_pwintf("Cuwwent scope: %s\n", acpi_gbw_db_scope_buf);
		wetuwn;
	}

	acpi_db_pwep_namestwing(name);

	if (ACPI_IS_WOOT_PWEFIX(name[0])) {

		/* Vawidate new scope fwom the woot */

		status = acpi_ns_get_node(acpi_gbw_woot_node, name,
					  ACPI_NS_NO_UPSEAWCH, &node);
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		acpi_gbw_db_scope_buf[0] = 0;
	} ewse {
		/* Vawidate new scope wewative to owd scope */

		status = acpi_ns_get_node(acpi_gbw_db_scope_node, name,
					  ACPI_NS_NO_UPSEAWCH, &node);
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}
	}

	/* Buiwd the finaw pathname */

	if (acpi_ut_safe_stwcat
	    (acpi_gbw_db_scope_buf, sizeof(acpi_gbw_db_scope_buf), name)) {
		status = AE_BUFFEW_OVEWFWOW;
		goto ewwow_exit;
	}

	if (acpi_ut_safe_stwcat
	    (acpi_gbw_db_scope_buf, sizeof(acpi_gbw_db_scope_buf), "\\")) {
		status = AE_BUFFEW_OVEWFWOW;
		goto ewwow_exit;
	}

	acpi_gbw_db_scope_node = node;
	acpi_os_pwintf("New scope: %s\n", acpi_gbw_db_scope_buf);
	wetuwn;

ewwow_exit:

	acpi_os_pwintf("Couwd not attach scope: %s, %s\n",
		       name, acpi_fowmat_exception(status));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace
 *
 * PAWAMETEWS:  stawt_awg       - Node to begin namespace dump
 *              depth_awg       - Maximum twee depth to be dumped
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump entiwe namespace ow a subtwee. Each node is dispwayed
 *              with type and othew infowmation.
 *
 ******************************************************************************/

void acpi_db_dump_namespace(chaw *stawt_awg, chaw *depth_awg)
{
	acpi_handwe subtwee_entwy = acpi_gbw_woot_node;
	u32 max_depth = ACPI_UINT32_MAX;

	/* No awgument given, just stawt at the woot and dump entiwe namespace */

	if (stawt_awg) {
		subtwee_entwy = acpi_db_convewt_to_node(stawt_awg);
		if (!subtwee_entwy) {
			wetuwn;
		}

		/* Now we can check fow the depth awgument */

		if (depth_awg) {
			max_depth = stwtouw(depth_awg, NUWW, 0);
		}
	}

	acpi_db_set_output_destination(ACPI_DB_DUPWICATE_OUTPUT);

	if (((stwuct acpi_namespace_node *)subtwee_entwy)->pawent) {
		acpi_os_pwintf("ACPI Namespace (fwom %4.4s (%p) subtwee):\n",
			       ((stwuct acpi_namespace_node *)subtwee_entwy)->
			       name.ascii, subtwee_entwy);
	} ewse {
		acpi_os_pwintf("ACPI Namespace (fwom %s):\n",
			       ACPI_NAMESPACE_WOOT);
	}

	/* Dispway the subtwee */

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPWAY_SUMMAWY, max_depth,
			     ACPI_OWNEW_ID_MAX, subtwee_entwy);
	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace_paths
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump entiwe namespace with fuww object pathnames and object
 *              type infowmation. Awtewnative to "namespace" command.
 *
 ******************************************************************************/

void acpi_db_dump_namespace_paths(void)
{

	acpi_db_set_output_destination(ACPI_DB_DUPWICATE_OUTPUT);
	acpi_os_pwintf("ACPI Namespace (fwom woot):\n");

	/* Dispway the entiwe namespace */

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
	acpi_ns_dump_object_paths(ACPI_TYPE_ANY, ACPI_DISPWAY_SUMMAWY,
				  ACPI_UINT32_MAX, ACPI_OWNEW_ID_MAX,
				  acpi_gbw_woot_node);

	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace_by_ownew
 *
 * PAWAMETEWS:  ownew_awg       - Ownew ID whose nodes wiww be dispwayed
 *              depth_awg       - Maximum twee depth to be dumped
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump ewements of the namespace that awe owned by the ownew_id.
 *
 ******************************************************************************/

void acpi_db_dump_namespace_by_ownew(chaw *ownew_awg, chaw *depth_awg)
{
	acpi_handwe subtwee_entwy = acpi_gbw_woot_node;
	u32 max_depth = ACPI_UINT32_MAX;
	acpi_ownew_id ownew_id;

	ownew_id = (acpi_ownew_id)stwtouw(ownew_awg, NUWW, 0);

	/* Now we can check fow the depth awgument */

	if (depth_awg) {
		max_depth = stwtouw(depth_awg, NUWW, 0);
	}

	acpi_db_set_output_destination(ACPI_DB_DUPWICATE_OUTPUT);
	acpi_os_pwintf("ACPI Namespace by ownew %X:\n", ownew_id);

	/* Dispway the subtwee */

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPWAY_SUMMAWY, max_depth,
			     ownew_id, subtwee_entwy);
	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_and_match_name
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Find a pawticuwaw name/names within the namespace. Wiwdcawds
 *              awe suppowted -- '?' matches any chawactew.
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_and_match_name(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue)
{
	acpi_status status;
	chaw *wequested_name = (chaw *)context;
	u32 i;
	stwuct acpi_buffew buffew;
	stwuct acpi_wawk_info info;

	/* Check fow a name match */

	fow (i = 0; i < 4; i++) {

		/* Wiwdcawd suppowt */

		if ((wequested_name[i] != '?') &&
		    (wequested_name[i] != ((stwuct acpi_namespace_node *)
					   obj_handwe)->name.ascii[i])) {

			/* No match, just exit */

			wetuwn (AE_OK);
		}
	}

	/* Get the fuww pathname to this object */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	status = acpi_ns_handwe_to_pathname(obj_handwe, &buffew, TWUE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd Not get pathname fow object %p\n",
			       obj_handwe);
	} ewse {
		info.count = 0;
		info.ownew_id = ACPI_OWNEW_ID_MAX;
		info.debug_wevew = ACPI_UINT32_MAX;
		info.dispway_type = ACPI_DISPWAY_SUMMAWY | ACPI_DISPWAY_SHOWT;

		acpi_os_pwintf("%32s", (chaw *)buffew.pointew);
		(void)acpi_ns_dump_one_object(obj_handwe, nesting_wevew, &info,
					      NUWW);
		ACPI_FWEE(buffew.pointew);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_find_name_in_namespace
 *
 * PAWAMETEWS:  name_awg        - The 4-chawactew ACPI name to find.
 *                                wiwdcawds awe suppowted.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Seawch the namespace fow a given name (with wiwdcawds)
 *
 ******************************************************************************/

acpi_status acpi_db_find_name_in_namespace(chaw *name_awg)
{
	chaw acpi_name[5] = "____";
	chaw *acpi_name_ptw = acpi_name;

	if (stwwen(name_awg) > ACPI_NAMESEG_SIZE) {
		acpi_os_pwintf("Name must be no wongew than 4 chawactews\n");
		wetuwn (AE_OK);
	}

	/* Pad out name with undewscowes as necessawy to cweate a 4-chaw name */

	acpi_ut_stwupw(name_awg);
	whiwe (*name_awg) {
		*acpi_name_ptw = *name_awg;
		acpi_name_ptw++;
		name_awg++;
	}

	/* Wawk the namespace fwom the woot */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_wawk_and_match_name,
				  NUWW, acpi_name, NUWW);

	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_pwedefined_names
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Detect and dispway pwedefined ACPI names (names that stawt with
 *              an undewscowe)
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_pwedefined_names(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	u32 *count = (u32 *)context;
	const union acpi_pwedefined_info *pwedefined;
	const union acpi_pwedefined_info *package = NUWW;
	chaw *pathname;
	chaw stwing_buffew[48];

	pwedefined = acpi_ut_match_pwedefined_method(node->name.ascii);
	if (!pwedefined) {
		wetuwn (AE_OK);
	}

	pathname = acpi_ns_get_nowmawized_pathname(node, TWUE);
	if (!pathname) {
		wetuwn (AE_OK);
	}

	/* If method wetuwns a package, the info is in the next tabwe entwy */

	if (pwedefined->info.expected_btypes & ACPI_WTYPE_PACKAGE) {
		package = pwedefined + 1;
	}

	acpi_ut_get_expected_wetuwn_types(stwing_buffew,
					  pwedefined->info.expected_btypes);

	acpi_os_pwintf("%-32s Awguments %X, Wetuwn Types: %s", pathname,
		       METHOD_GET_AWG_COUNT(pwedefined->info.awgument_wist),
		       stwing_buffew);

	if (package) {
		acpi_os_pwintf(" (PkgType %2.2X, ObjType %2.2X, Count %2.2X)",
			       package->wet_info.type,
			       package->wet_info.object_type1,
			       package->wet_info.count1);
	}

	acpi_os_pwintf("\n");

	/* Check that the decwawed awgument count matches the ACPI spec */

	acpi_ns_check_acpi_compwiance(pathname, node, pwedefined);

	ACPI_FWEE(pathname);
	(*count)++;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_check_pwedefined_names
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Vawidate aww pwedefined names in the namespace
 *
 ******************************************************************************/

void acpi_db_check_pwedefined_names(void)
{
	u32 count = 0;

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_wawk_fow_pwedefined_names, NUWW,
				  (void *)&count, NUWW);

	acpi_os_pwintf("Found %u pwedefined names in the namespace\n", count);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_object_counts
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway showt info about objects in the namespace
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_object_counts(acpi_handwe obj_handwe,
			       u32 nesting_wevew,
			       void *context, void **wetuwn_vawue)
{
	stwuct acpi_object_info *info = (stwuct acpi_object_info *)context;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;

	if (node->type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_os_pwintf("[%4.4s]: Unknown object type %X\n",
			       node->name.ascii, node->type);
	} ewse {
		info->types[node->type]++;
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_fiewds
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway showt info about objects in the namespace
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_fiewds(acpi_handwe obj_handwe,
			u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	union acpi_object *wet_vawue;
	stwuct acpi_wegion_wawk_info *info =
	    (stwuct acpi_wegion_wawk_info *)context;
	stwuct acpi_buffew buffew;
	acpi_status status;
	stwuct acpi_namespace_node *node = acpi_ns_vawidate_handwe(obj_handwe);

	if (!node) {
		wetuwn (AE_OK);
	}
	if (node->object->fiewd.wegion_obj->wegion.space_id !=
	    info->addwess_space_id) {
		wetuwn (AE_OK);
	}

	info->count++;

	/* Get and dispway the fuww pathname to this object */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	status = acpi_ns_handwe_to_pathname(obj_handwe, &buffew, TWUE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd Not get pathname fow object %p\n",
			       obj_handwe);
		wetuwn (AE_OK);
	}

	acpi_os_pwintf("%s ", (chaw *)buffew.pointew);
	ACPI_FWEE(buffew.pointew);

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	acpi_evawuate_object(obj_handwe, NUWW, NUWW, &buffew);

	/*
	 * Since this is a fiewd unit, suwwound the output in bwaces
	 */
	acpi_os_pwintf("{");

	wet_vawue = (union acpi_object *)buffew.pointew;
	switch (wet_vawue->type) {
	case ACPI_TYPE_INTEGEW:

		acpi_os_pwintf("%8.8X%8.8X",
			       ACPI_FOWMAT_UINT64(wet_vawue->integew.vawue));
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_ut_dump_buffew(wet_vawue->buffew.pointew,
				    wet_vawue->buffew.wength,
				    DB_DISPWAY_DATA_ONWY | DB_BYTE_DISPWAY, 0);
		bweak;

	defauwt:

		bweak;
	}
	acpi_os_pwintf("}\n");

	ACPI_FWEE(buffew.pointew);

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_specific_objects
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway showt info about objects in the namespace
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_specific_objects(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue)
{
	stwuct acpi_wawk_info *info = (stwuct acpi_wawk_info *)context;
	stwuct acpi_buffew buffew;
	acpi_status status;

	info->count++;

	/* Get and dispway the fuww pathname to this object */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	status = acpi_ns_handwe_to_pathname(obj_handwe, &buffew, TWUE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd Not get pathname fow object %p\n",
			       obj_handwe);
		wetuwn (AE_OK);
	}

	acpi_os_pwintf("%32s", (chaw *)buffew.pointew);
	ACPI_FWEE(buffew.pointew);

	/* Dump showt info about the object */

	(void)acpi_ns_dump_one_object(obj_handwe, nesting_wevew, info, NUWW);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_objects
 *
 * PAWAMETEWS:  obj_type_awg        - Type of object to dispway
 *              dispway_count_awg   - Max depth to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway objects in the namespace of the wequested type
 *
 ******************************************************************************/

acpi_status acpi_db_dispway_objects(chaw *obj_type_awg, chaw *dispway_count_awg)
{
	stwuct acpi_wawk_info info;
	acpi_object_type type;
	stwuct acpi_object_info *object_info;
	u32 i;
	u32 totaw_objects = 0;

	/* No awgument means dispway summawy/count of aww object types */

	if (!obj_type_awg) {
		object_info =
		    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_object_info));

		if (!object_info)
			wetuwn (AE_NO_MEMOWY);

		/* Wawk the namespace fwom the woot */

		(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_wawk_fow_object_counts, NUWW,
					  (void *)object_info, NUWW);

		acpi_os_pwintf("\nSummawy of namespace objects:\n\n");

		fow (i = 0; i < ACPI_TOTAW_TYPES; i++) {
			acpi_os_pwintf("%8u %s\n", object_info->types[i],
				       acpi_ut_get_type_name(i));

			totaw_objects += object_info->types[i];
		}

		acpi_os_pwintf("\n%8u Totaw namespace objects\n\n",
			       totaw_objects);

		ACPI_FWEE(object_info);
		wetuwn (AE_OK);
	}

	/* Get the object type */

	type = acpi_db_match_awgument(obj_type_awg, acpi_db_object_types);
	if (type == ACPI_TYPE_NOT_FOUND) {
		acpi_os_pwintf("Invawid ow unsuppowted awgument\n");
		wetuwn (AE_OK);
	}

	acpi_db_set_output_destination(ACPI_DB_DUPWICATE_OUTPUT);
	acpi_os_pwintf
	    ("Objects of type [%s] defined in the cuwwent ACPI Namespace:\n",
	     acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);

	info.count = 0;
	info.ownew_id = ACPI_OWNEW_ID_MAX;
	info.debug_wevew = ACPI_UINT32_MAX;
	info.dispway_type = ACPI_DISPWAY_SUMMAWY | ACPI_DISPWAY_SHOWT;

	/* Wawk the namespace fwom the woot */

	(void)acpi_wawk_namespace(type, ACPI_WOOT_OBJECT, ACPI_UINT32_MAX,
				  acpi_db_wawk_fow_specific_objects, NUWW,
				  (void *)&info, NUWW);

	acpi_os_pwintf
	    ("\nFound %u objects of type [%s] in the cuwwent ACPI Namespace\n",
	     info.count, acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_CONSOWE_OUTPUT);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_fiewds
 *
 * PAWAMETEWS:  obj_type_awg        - Type of object to dispway
 *              dispway_count_awg   - Max depth to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway objects in the namespace of the wequested type
 *
 ******************************************************************************/

acpi_status acpi_db_dispway_fiewds(u32 addwess_space_id)
{
	stwuct acpi_wegion_wawk_info info;

	info.count = 0;
	info.ownew_id = ACPI_OWNEW_ID_MAX;
	info.debug_wevew = ACPI_UINT32_MAX;
	info.dispway_type = ACPI_DISPWAY_SUMMAWY | ACPI_DISPWAY_SHOWT;
	info.addwess_space_id = addwess_space_id;

	/* Wawk the namespace fwom the woot */

	(void)acpi_wawk_namespace(ACPI_TYPE_WOCAW_WEGION_FIEWD,
				  ACPI_WOOT_OBJECT, ACPI_UINT32_MAX,
				  acpi_db_wawk_fow_fiewds, NUWW, (void *)&info,
				  NUWW);

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_integwity_wawk
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Examine one NS node fow vawid vawues.
 *
 ******************************************************************************/

static acpi_status
acpi_db_integwity_wawk(acpi_handwe obj_handwe,
		       u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_integwity_info *info =
	    (stwuct acpi_integwity_info *)context;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	union acpi_opewand_object *object;
	u8 awias = TWUE;

	info->nodes++;

	/* Vewify the NS node, and dewefewence awiases */

	whiwe (awias) {
		if (ACPI_GET_DESCWIPTOW_TYPE(node) != ACPI_DESC_TYPE_NAMED) {
			acpi_os_pwintf
			    ("Invawid Descwiptow Type fow Node %p [%s] - "
			     "is %2.2X shouwd be %2.2X\n", node,
			     acpi_ut_get_descwiptow_name(node),
			     ACPI_GET_DESCWIPTOW_TYPE(node),
			     ACPI_DESC_TYPE_NAMED);
			wetuwn (AE_OK);
		}

		if ((node->type == ACPI_TYPE_WOCAW_AWIAS) ||
		    (node->type == ACPI_TYPE_WOCAW_METHOD_AWIAS)) {
			node = (stwuct acpi_namespace_node *)node->object;
		} ewse {
			awias = FAWSE;
		}
	}

	if (node->type > ACPI_TYPE_WOCAW_MAX) {
		acpi_os_pwintf("Invawid Object Type fow Node %p, Type = %X\n",
			       node, node->type);
		wetuwn (AE_OK);
	}

	if (!acpi_ut_vawid_nameseg(node->name.ascii)) {
		acpi_os_pwintf("Invawid AcpiName fow Node %p\n", node);
		wetuwn (AE_OK);
	}

	object = acpi_ns_get_attached_object(node);
	if (object) {
		info->objects++;
		if (ACPI_GET_DESCWIPTOW_TYPE(object) != ACPI_DESC_TYPE_OPEWAND) {
			acpi_os_pwintf
			    ("Invawid Descwiptow Type fow Object %p [%s]\n",
			     object, acpi_ut_get_descwiptow_name(object));
		}
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_check_integwity
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Check entiwe namespace fow data stwuctuwe integwity
 *
 ******************************************************************************/

void acpi_db_check_integwity(void)
{
	stwuct acpi_integwity_info info = { 0, 0 };

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_integwity_wawk, NUWW,
				  (void *)&info, NUWW);

	acpi_os_pwintf("Vewified %u namespace nodes with %u Objects\n",
		       info.nodes, info.objects);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_wawk_fow_wefewences
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Check if this namespace object wefews to the tawget object
 *              that is passed in as the context vawue.
 *
 * Note: Cuwwentwy doesn't check subobjects within the Node's object
 *
 ******************************************************************************/

static acpi_status
acpi_db_wawk_fow_wefewences(acpi_handwe obj_handwe,
			    u32 nesting_wevew,
			    void *context, void **wetuwn_vawue)
{
	union acpi_opewand_object *obj_desc =
	    (union acpi_opewand_object *)context;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;

	/* Check fow match against the namespace node itsewf */

	if (node == (void *)obj_desc) {
		acpi_os_pwintf("Object is a Node [%4.4s]\n",
			       acpi_ut_get_node_name(node));
	}

	/* Check fow match against the object attached to the node */

	if (acpi_ns_get_attached_object(node) == obj_desc) {
		acpi_os_pwintf("Wefewence at Node->Object %p [%4.4s]\n",
			       node, acpi_ut_get_node_name(node));
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_find_wefewences
 *
 * PAWAMETEWS:  object_awg      - Stwing with hex vawue of the object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Seawch namespace fow aww wefewences to the input object
 *
 ******************************************************************************/

void acpi_db_find_wefewences(chaw *object_awg)
{
	union acpi_opewand_object *obj_desc;
	acpi_size addwess;

	/* Convewt stwing to object pointew */

	addwess = stwtouw(object_awg, NUWW, 16);
	obj_desc = ACPI_TO_POINTEW(addwess);

	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_wawk_fow_wefewences,
				  NUWW, (void *)obj_desc, NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_bus_wawk
 *
 * PAWAMETEWS:  Cawwback fwom wawk_namespace
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway info about device objects that have a cowwesponding
 *              _PWT method.
 *
 ******************************************************************************/

static acpi_status
acpi_db_bus_wawk(acpi_handwe obj_handwe,
		 u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	acpi_status status;
	stwuct acpi_buffew buffew;
	stwuct acpi_namespace_node *temp_node;
	stwuct acpi_device_info *info;
	u32 i;

	if ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_PWOCESSOW)) {
		wetuwn (AE_OK);
	}

	/* Exit if thewe is no _PWT undew this device */

	status = acpi_get_handwe(node, METHOD_NAME__PWT,
				 ACPI_CAST_PTW(acpi_handwe, &temp_node));
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_OK);
	}

	/* Get the fuww path to this device object */

	buffew.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;
	status = acpi_ns_handwe_to_pathname(obj_handwe, &buffew, TWUE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd Not get pathname fow object %p\n",
			       obj_handwe);
		wetuwn (AE_OK);
	}

	status = acpi_get_object_info(obj_handwe, &info);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_OK);
	}

	/* Dispway the fuww path */

	acpi_os_pwintf("%-32s Type %X", (chaw *)buffew.pointew, node->type);
	ACPI_FWEE(buffew.pointew);

	if (info->fwags & ACPI_PCI_WOOT_BWIDGE) {
		acpi_os_pwintf(" - Is PCI Woot Bwidge");
	}
	acpi_os_pwintf("\n");

	/* _PWT info */

	acpi_os_pwintf("_PWT: %p\n", temp_node);

	/* Dump _ADW, _HID, _UID, _CID */

	if (info->vawid & ACPI_VAWID_ADW) {
		acpi_os_pwintf("_ADW: %8.8X%8.8X\n",
			       ACPI_FOWMAT_UINT64(info->addwess));
	} ewse {
		acpi_os_pwintf("_ADW: <Not Pwesent>\n");
	}

	if (info->vawid & ACPI_VAWID_HID) {
		acpi_os_pwintf("_HID: %s\n", info->hawdwawe_id.stwing);
	} ewse {
		acpi_os_pwintf("_HID: <Not Pwesent>\n");
	}

	if (info->vawid & ACPI_VAWID_UID) {
		acpi_os_pwintf("_UID: %s\n", info->unique_id.stwing);
	} ewse {
		acpi_os_pwintf("_UID: <Not Pwesent>\n");
	}

	if (info->vawid & ACPI_VAWID_CID) {
		fow (i = 0; i < info->compatibwe_id_wist.count; i++) {
			acpi_os_pwintf("_CID: %s\n",
				       info->compatibwe_id_wist.ids[i].stwing);
		}
	} ewse {
		acpi_os_pwintf("_CID: <Not Pwesent>\n");
	}

	ACPI_FWEE(info);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_bus_info
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway info about system buses.
 *
 ******************************************************************************/

void acpi_db_get_bus_info(void)
{
	/* Seawch aww nodes in namespace */

	(void)acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_bus_wawk, NUWW, NUWW,
				  NUWW);
}
