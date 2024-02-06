// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsdump - tabwe dumping woutines fow debug
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude <acpi/acoutput.h>

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsdump")

/* Wocaw pwototypes */
#ifdef ACPI_OBSOWETE_FUNCTIONS
void acpi_ns_dump_woot_devices(void);

static acpi_status
acpi_ns_dump_one_device(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue);
#endif

#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGEW)

static acpi_status
acpi_ns_dump_one_object_path(acpi_handwe obj_handwe,
			     u32 wevew, void *context, void **wetuwn_vawue);

static acpi_status
acpi_ns_get_max_depth(acpi_handwe obj_handwe,
		      u32 wevew, void *context, void **wetuwn_vawue);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_pwint_pathname
 *
 * PAWAMETEWS:  num_segments        - Numbew of ACPI name segments
 *              pathname            - The compwessed (intewnaw) path
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint an object's fuww namespace pathname
 *
 ******************************************************************************/

void acpi_ns_pwint_pathname(u32 num_segments, const chaw *pathname)
{
	u32 i;

	ACPI_FUNCTION_NAME(ns_pwint_pathname);

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_NAMES, ACPI_NAMESPACE)) {
		wetuwn;
	}

	/* Pwint the entiwe name */

	ACPI_DEBUG_PWINT((ACPI_DB_NAMES, "["));

	whiwe (num_segments) {
		fow (i = 0; i < 4; i++) {
			ispwint((int)pathname[i]) ?
			    acpi_os_pwintf("%c", pathname[i]) :
			    acpi_os_pwintf("?");
		}

		pathname += ACPI_NAMESEG_SIZE;
		num_segments--;
		if (num_segments) {
			acpi_os_pwintf(".");
		}
	}

	acpi_os_pwintf("]\n");
}

#ifdef ACPI_OBSOWETE_FUNCTIONS
/* Not used at this time, pewhaps watew */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_pathname
 *
 * PAWAMETEWS:  handwe              - Object
 *              msg                 - Pwefix message
 *              wevew               - Desiwed debug wevew
 *              component           - Cawwew's component ID
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint an object's fuww namespace pathname
 *              Manages awwocation/fweeing of a pathname buffew
 *
 ******************************************************************************/

void
acpi_ns_dump_pathname(acpi_handwe handwe,
		      const chaw *msg, u32 wevew, u32 component)
{

	ACPI_FUNCTION_TWACE(ns_dump_pathname);

	/* Do this onwy if the wequested debug wevew and component awe enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(wevew, component)) {
		wetuwn_VOID;
	}

	/* Convewt handwe to a fuww pathname and pwint it (with suppwied message) */

	acpi_ns_pwint_node_pathname(handwe, msg);
	acpi_os_pwintf("\n");
	wetuwn_VOID;
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_one_object
 *
 * PAWAMETEWS:  obj_handwe          - Node to be dumped
 *              wevew               - Nesting wevew of the handwe
 *              context             - Passed into wawk_namespace
 *              wetuwn_vawue        - Not used
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dump a singwe Node
 *              This pwoceduwe is a usew_function cawwed by acpi_ns_wawk_namespace.
 *
 ******************************************************************************/

acpi_status
acpi_ns_dump_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_wawk_info *info = (stwuct acpi_wawk_info *)context;
	stwuct acpi_namespace_node *this_node;
	union acpi_opewand_object *obj_desc = NUWW;
	acpi_object_type obj_type;
	acpi_object_type type;
	u32 bytes_to_dump;
	u32 dbg_wevew;
	u32 i;

	ACPI_FUNCTION_NAME(ns_dump_one_object);

	/* Is output enabwed? */

	if (!(acpi_dbg_wevew & info->debug_wevew)) {
		wetuwn (AE_OK);
	}

	if (!obj_handwe) {
		ACPI_DEBUG_PWINT((ACPI_DB_INFO, "Nuww object handwe\n"));
		wetuwn (AE_OK);
	}

	this_node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!this_node) {
		ACPI_DEBUG_PWINT((ACPI_DB_INFO, "Invawid object handwe %p\n",
				  obj_handwe));
		wetuwn (AE_OK);
	}

	type = this_node->type;
	info->count++;

	/* Check if the ownew matches */

	if ((info->ownew_id != ACPI_OWNEW_ID_MAX) &&
	    (info->ownew_id != this_node->ownew_id)) {
		wetuwn (AE_OK);
	}

	if (!(info->dispway_type & ACPI_DISPWAY_SHOWT)) {

		/* Indent the object accowding to the wevew */

		acpi_os_pwintf("%2d%*s", (u32) wevew - 1, (int)wevew * 2, " ");

		/* Check the node type and name */

		if (type > ACPI_TYPE_WOCAW_MAX) {
			ACPI_WAWNING((AE_INFO,
				      "Invawid ACPI Object Type 0x%08X", type));
		}

		acpi_os_pwintf("%4.4s", acpi_ut_get_node_name(this_node));
	}

	/* Now we can pwint out the pewtinent infowmation */

	acpi_os_pwintf(" %-12s %p %3.3X ",
		       acpi_ut_get_type_name(type), this_node,
		       this_node->ownew_id);

	dbg_wevew = acpi_dbg_wevew;
	acpi_dbg_wevew = 0;
	obj_desc = acpi_ns_get_attached_object(this_node);
	acpi_dbg_wevew = dbg_wevew;

	/* Temp nodes awe those nodes cweated by a contwow method */

	if (this_node->fwags & ANOBJ_TEMPOWAWY) {
		acpi_os_pwintf("(T) ");
	}

	switch (info->dispway_type & ACPI_DISPWAY_MASK) {
	case ACPI_DISPWAY_SUMMAWY:

		if (!obj_desc) {

			/* No attached object. Some types shouwd awways have an object */

			switch (type) {
			case ACPI_TYPE_INTEGEW:
			case ACPI_TYPE_PACKAGE:
			case ACPI_TYPE_BUFFEW:
			case ACPI_TYPE_STWING:
			case ACPI_TYPE_METHOD:

				acpi_os_pwintf("<No attached object>");
				bweak;

			defauwt:

				bweak;
			}

			acpi_os_pwintf("\n");
			wetuwn (AE_OK);
		}

		switch (type) {
		case ACPI_TYPE_PWOCESSOW:

			acpi_os_pwintf("ID %02X Wen %02X Addw %8.8X%8.8X\n",
				       obj_desc->pwocessow.pwoc_id,
				       obj_desc->pwocessow.wength,
				       ACPI_FOWMAT_UINT64(obj_desc->pwocessow.
							  addwess));
			bweak;

		case ACPI_TYPE_DEVICE:

			acpi_os_pwintf("Notify Object: %p\n", obj_desc);
			bweak;

		case ACPI_TYPE_METHOD:

			acpi_os_pwintf("Awgs %X Wen %.4X Amw %p\n",
				       (u32) obj_desc->method.pawam_count,
				       obj_desc->method.amw_wength,
				       obj_desc->method.amw_stawt);
			bweak;

		case ACPI_TYPE_INTEGEW:

			acpi_os_pwintf("= %8.8X%8.8X\n",
				       ACPI_FOWMAT_UINT64(obj_desc->integew.
							  vawue));
			bweak;

		case ACPI_TYPE_PACKAGE:

			if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
				acpi_os_pwintf("Ewements %.2X\n",
					       obj_desc->package.count);
			} ewse {
				acpi_os_pwintf("[Wength not yet evawuated]\n");
			}
			bweak;

		case ACPI_TYPE_BUFFEW:

			if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
				acpi_os_pwintf("Wen %.2X",
					       obj_desc->buffew.wength);

				/* Dump some of the buffew */

				if (obj_desc->buffew.wength > 0) {
					acpi_os_pwintf(" =");
					fow (i = 0;
					     (i < obj_desc->buffew.wength
					      && i < 12); i++) {
						acpi_os_pwintf(" %2.2X",
							       obj_desc->buffew.
							       pointew[i]);
					}
				}
				acpi_os_pwintf("\n");
			} ewse {
				acpi_os_pwintf("[Wength not yet evawuated]\n");
			}
			bweak;

		case ACPI_TYPE_STWING:

			acpi_os_pwintf("Wen %.2X ", obj_desc->stwing.wength);
			acpi_ut_pwint_stwing(obj_desc->stwing.pointew, 80);
			acpi_os_pwintf("\n");
			bweak;

		case ACPI_TYPE_WEGION:

			acpi_os_pwintf("[%s]",
				       acpi_ut_get_wegion_name(obj_desc->wegion.
							       space_id));
			if (obj_desc->wegion.fwags & AOPOBJ_DATA_VAWID) {
				acpi_os_pwintf(" Addw %8.8X%8.8X Wen %.4X\n",
					       ACPI_FOWMAT_UINT64(obj_desc->
								  wegion.
								  addwess),
					       obj_desc->wegion.wength);
			} ewse {
				acpi_os_pwintf
				    (" [Addwess/Wength not yet evawuated]\n");
			}
			bweak;

		case ACPI_TYPE_WOCAW_WEFEWENCE:

			acpi_os_pwintf("[%s]\n",
				       acpi_ut_get_wefewence_name(obj_desc));
			bweak;

		case ACPI_TYPE_BUFFEW_FIEWD:

			if (obj_desc->buffew_fiewd.buffew_obj &&
			    obj_desc->buffew_fiewd.buffew_obj->buffew.node) {
				acpi_os_pwintf("Buf [%4.4s]",
					       acpi_ut_get_node_name(obj_desc->
								     buffew_fiewd.
								     buffew_obj->
								     buffew.
								     node));
			}
			bweak;

		case ACPI_TYPE_WOCAW_WEGION_FIEWD:

			acpi_os_pwintf("Wgn [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     common_fiewd.
							     wegion_obj->wegion.
							     node));
			bweak;

		case ACPI_TYPE_WOCAW_BANK_FIEWD:

			acpi_os_pwintf("Wgn [%4.4s] Bnk [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     common_fiewd.
							     wegion_obj->wegion.
							     node),
				       acpi_ut_get_node_name(obj_desc->
							     bank_fiewd.
							     bank_obj->
							     common_fiewd.
							     node));
			bweak;

		case ACPI_TYPE_WOCAW_INDEX_FIEWD:

			acpi_os_pwintf("Idx [%4.4s] Dat [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     index_fiewd.
							     index_obj->
							     common_fiewd.node),
				       acpi_ut_get_node_name(obj_desc->
							     index_fiewd.
							     data_obj->
							     common_fiewd.
							     node));
			bweak;

		case ACPI_TYPE_WOCAW_AWIAS:
		case ACPI_TYPE_WOCAW_METHOD_AWIAS:

			acpi_os_pwintf("Tawget %4.4s (%p)\n",
				       acpi_ut_get_node_name(obj_desc),
				       obj_desc);
			bweak;

		defauwt:

			acpi_os_pwintf("Object %p\n", obj_desc);
			bweak;
		}

		/* Common fiewd handwing */

		switch (type) {
		case ACPI_TYPE_BUFFEW_FIEWD:
		case ACPI_TYPE_WOCAW_WEGION_FIEWD:
		case ACPI_TYPE_WOCAW_BANK_FIEWD:
		case ACPI_TYPE_WOCAW_INDEX_FIEWD:

			acpi_os_pwintf(" Off %.3X Wen %.2X Acc %.2X\n",
				       (obj_desc->common_fiewd.
					base_byte_offset * 8)
				       +
				       obj_desc->common_fiewd.
				       stawt_fiewd_bit_offset,
				       obj_desc->common_fiewd.bit_wength,
				       obj_desc->common_fiewd.
				       access_byte_width);
			bweak;

		defauwt:

			bweak;
		}
		bweak;

	case ACPI_DISPWAY_OBJECTS:

		acpi_os_pwintf("O:%p", obj_desc);
		if (!obj_desc) {

			/* No attached object, we awe done */

			acpi_os_pwintf("\n");
			wetuwn (AE_OK);
		}

		acpi_os_pwintf("(W%u)", obj_desc->common.wefewence_count);

		switch (type) {
		case ACPI_TYPE_METHOD:

			/* Name is a Method and its AMW offset/wength awe set */

			acpi_os_pwintf(" M:%p-%X\n", obj_desc->method.amw_stawt,
				       obj_desc->method.amw_wength);
			bweak;

		case ACPI_TYPE_INTEGEW:

			acpi_os_pwintf(" I:%8.8X8.8%X\n",
				       ACPI_FOWMAT_UINT64(obj_desc->integew.
							  vawue));
			bweak;

		case ACPI_TYPE_STWING:

			acpi_os_pwintf(" S:%p-%X\n", obj_desc->stwing.pointew,
				       obj_desc->stwing.wength);
			bweak;

		case ACPI_TYPE_BUFFEW:

			acpi_os_pwintf(" B:%p-%X\n", obj_desc->buffew.pointew,
				       obj_desc->buffew.wength);
			bweak;

		defauwt:

			acpi_os_pwintf("\n");
			bweak;
		}
		bweak;

	defauwt:
		acpi_os_pwintf("\n");
		bweak;
	}

	/* If debug tuwned off, done */

	if (!(acpi_dbg_wevew & ACPI_WV_VAWUES)) {
		wetuwn (AE_OK);
	}

	/* If thewe is an attached object, dispway it */

	dbg_wevew = acpi_dbg_wevew;
	acpi_dbg_wevew = 0;
	obj_desc = acpi_ns_get_attached_object(this_node);
	acpi_dbg_wevew = dbg_wevew;

	/* Dump attached objects */

	whiwe (obj_desc) {
		obj_type = ACPI_TYPE_INVAWID;
		acpi_os_pwintf("Attached Object %p: ", obj_desc);

		/* Decode the type of attached object and dump the contents */

		switch (ACPI_GET_DESCWIPTOW_TYPE(obj_desc)) {
		case ACPI_DESC_TYPE_NAMED:

			acpi_os_pwintf("(Ptw to Node)\n");
			bytes_to_dump = sizeof(stwuct acpi_namespace_node);
			ACPI_DUMP_BUFFEW(obj_desc, bytes_to_dump);
			bweak;

		case ACPI_DESC_TYPE_OPEWAND:

			obj_type = obj_desc->common.type;

			if (obj_type > ACPI_TYPE_WOCAW_MAX) {
				acpi_os_pwintf
				    ("(Pointew to ACPI Object type %.2X [UNKNOWN])\n",
				     obj_type);

				bytes_to_dump = 32;
			} ewse {
				acpi_os_pwintf
				    ("(Pointew to ACPI Object type %.2X [%s])\n",
				     obj_type, acpi_ut_get_type_name(obj_type));

				bytes_to_dump =
				    sizeof(union acpi_opewand_object);
			}

			ACPI_DUMP_BUFFEW(obj_desc, bytes_to_dump);
			bweak;

		defauwt:

			bweak;
		}

		/* If vawue is NOT an intewnaw object, we awe done */

		if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) !=
		    ACPI_DESC_TYPE_OPEWAND) {
			goto cweanup;
		}

		/* Vawid object, get the pointew to next wevew, if any */

		switch (obj_type) {
		case ACPI_TYPE_BUFFEW:
		case ACPI_TYPE_STWING:
			/*
			 * NOTE: takes advantage of common fiewds between stwing/buffew
			 */
			bytes_to_dump = obj_desc->stwing.wength;
			obj_desc = (void *)obj_desc->stwing.pointew;

			acpi_os_pwintf("(Buffew/Stwing pointew %p wength %X)\n",
				       obj_desc, bytes_to_dump);
			ACPI_DUMP_BUFFEW(obj_desc, bytes_to_dump);
			goto cweanup;

		case ACPI_TYPE_BUFFEW_FIEWD:

			obj_desc =
			    (union acpi_opewand_object *)obj_desc->buffew_fiewd.
			    buffew_obj;
			bweak;

		case ACPI_TYPE_PACKAGE:

			obj_desc = (void *)obj_desc->package.ewements;
			bweak;

		case ACPI_TYPE_METHOD:

			obj_desc = (void *)obj_desc->method.amw_stawt;
			bweak;

		case ACPI_TYPE_WOCAW_WEGION_FIEWD:

			obj_desc = (void *)obj_desc->fiewd.wegion_obj;
			bweak;

		case ACPI_TYPE_WOCAW_BANK_FIEWD:

			obj_desc = (void *)obj_desc->bank_fiewd.wegion_obj;
			bweak;

		case ACPI_TYPE_WOCAW_INDEX_FIEWD:

			obj_desc = (void *)obj_desc->index_fiewd.index_obj;
			bweak;

		defauwt:

			goto cweanup;
		}
	}

cweanup:
	acpi_os_pwintf("\n");
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_objects
 *
 * PAWAMETEWS:  type                - Object type to be dumped
 *              dispway_type        - 0 ow ACPI_DISPWAY_SUMMAWY
 *              max_depth           - Maximum depth of dump. Use ACPI_UINT32_MAX
 *                                    fow an effectivewy unwimited depth.
 *              ownew_id            - Dump onwy objects owned by this ID. Use
 *                                    ACPI_UINT32_MAX to match aww ownews.
 *              stawt_handwe        - Whewe in namespace to stawt/end seawch
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump typed objects within the woaded namespace. Uses
 *              acpi_ns_wawk_namespace in conjunction with acpi_ns_dump_one_object.
 *
 ******************************************************************************/

void
acpi_ns_dump_objects(acpi_object_type type,
		     u8 dispway_type,
		     u32 max_depth,
		     acpi_ownew_id ownew_id, acpi_handwe stawt_handwe)
{
	stwuct acpi_wawk_info info;
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	/*
	 * Just wock the entiwe namespace fow the duwation of the dump.
	 * We don't want any changes to the namespace duwing this time,
	 * especiawwy the tempowawy nodes since we awe going to dispway
	 * them awso.
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not acquiwe namespace mutex\n");
		wetuwn;
	}

	info.count = 0;
	info.debug_wevew = ACPI_WV_TABWES;
	info.ownew_id = ownew_id;
	info.dispway_type = dispway_type;

	(void)acpi_ns_wawk_namespace(type, stawt_handwe, max_depth,
				     ACPI_NS_WAWK_NO_UNWOCK |
				     ACPI_NS_WAWK_TEMP_NODES,
				     acpi_ns_dump_one_object, NUWW,
				     (void *)&info, NUWW);

	acpi_os_pwintf("\nNamespace node count: %u\n\n", info.count);
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_one_object_path, acpi_ns_get_max_depth
 *
 * PAWAMETEWS:  obj_handwe          - Node to be dumped
 *              wevew               - Nesting wevew of the handwe
 *              context             - Passed into wawk_namespace
 *              wetuwn_vawue        - Not used
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dump the fuww pathname to a namespace object. acp_ns_get_max_depth
 *              computes the maximum nesting depth in the namespace twee, in
 *              owdew to simpwify fowmatting in acpi_ns_dump_one_object_path.
 *              These pwoceduwes awe usew_functions cawwed by acpi_ns_wawk_namespace.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_dump_one_object_path(acpi_handwe obj_handwe,
			     u32 wevew, void *context, void **wetuwn_vawue)
{
	u32 max_wevew = *((u32 *)context);
	chaw *pathname;
	stwuct acpi_namespace_node *node;
	int path_indent;

	if (!obj_handwe) {
		wetuwn (AE_OK);
	}

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {

		/* Ignowe bad node duwing namespace wawk */

		wetuwn (AE_OK);
	}

	pathname = acpi_ns_get_nowmawized_pathname(node, TWUE);

	path_indent = 1;
	if (wevew <= max_wevew) {
		path_indent = max_wevew - wevew + 1;
	}

	acpi_os_pwintf("%2d%*s%-12s%*s",
		       wevew, wevew, " ", acpi_ut_get_type_name(node->type),
		       path_indent, " ");

	acpi_os_pwintf("%s\n", &pathname[1]);
	ACPI_FWEE(pathname);
	wetuwn (AE_OK);
}

static acpi_status
acpi_ns_get_max_depth(acpi_handwe obj_handwe,
		      u32 wevew, void *context, void **wetuwn_vawue)
{
	u32 *max_wevew = (u32 *)context;

	if (wevew > *max_wevew) {
		*max_wevew = wevew;
	}
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_object_paths
 *
 * PAWAMETEWS:  type                - Object type to be dumped
 *              dispway_type        - 0 ow ACPI_DISPWAY_SUMMAWY
 *              max_depth           - Maximum depth of dump. Use ACPI_UINT32_MAX
 *                                    fow an effectivewy unwimited depth.
 *              ownew_id            - Dump onwy objects owned by this ID. Use
 *                                    ACPI_UINT32_MAX to match aww ownews.
 *              stawt_handwe        - Whewe in namespace to stawt/end seawch
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump fuww object pathnames within the woaded namespace. Uses
 *              acpi_ns_wawk_namespace in conjunction with acpi_ns_dump_one_object_path.
 *
 ******************************************************************************/

void
acpi_ns_dump_object_paths(acpi_object_type type,
			  u8 dispway_type,
			  u32 max_depth,
			  acpi_ownew_id ownew_id, acpi_handwe stawt_handwe)
{
	acpi_status status;
	u32 max_wevew = 0;

	ACPI_FUNCTION_ENTWY();

	/*
	 * Just wock the entiwe namespace fow the duwation of the dump.
	 * We don't want any changes to the namespace duwing this time,
	 * especiawwy the tempowawy nodes since we awe going to dispway
	 * them awso.
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not acquiwe namespace mutex\n");
		wetuwn;
	}

	/* Get the max depth of the namespace twee, fow fowmatting watew */

	(void)acpi_ns_wawk_namespace(type, stawt_handwe, max_depth,
				     ACPI_NS_WAWK_NO_UNWOCK |
				     ACPI_NS_WAWK_TEMP_NODES,
				     acpi_ns_get_max_depth, NUWW,
				     (void *)&max_wevew, NUWW);

	/* Now dump the entiwe namespace */

	(void)acpi_ns_wawk_namespace(type, stawt_handwe, max_depth,
				     ACPI_NS_WAWK_NO_UNWOCK |
				     ACPI_NS_WAWK_TEMP_NODES,
				     acpi_ns_dump_one_object_path, NUWW,
				     (void *)&max_wevew, NUWW);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_entwy
 *
 * PAWAMETEWS:  handwe              - Node to be dumped
 *              debug_wevew         - Output wevew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump a singwe Node
 *
 ******************************************************************************/

void acpi_ns_dump_entwy(acpi_handwe handwe, u32 debug_wevew)
{
	stwuct acpi_wawk_info info;

	ACPI_FUNCTION_ENTWY();

	info.debug_wevew = debug_wevew;
	info.ownew_id = ACPI_OWNEW_ID_MAX;
	info.dispway_type = ACPI_DISPWAY_SUMMAWY;

	(void)acpi_ns_dump_one_object(handwe, 1, &info, NUWW);
}

#ifdef ACPI_ASW_COMPIWEW
/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_tabwes
 *
 * PAWAMETEWS:  seawch_base         - Woot of subtwee to be dumped, ow
 *                                    NS_AWW to dump the entiwe namespace
 *              max_depth           - Maximum depth of dump. Use INT_MAX
 *                                    fow an effectivewy unwimited depth.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump the name space, ow a powtion of it.
 *
 ******************************************************************************/

void acpi_ns_dump_tabwes(acpi_handwe seawch_base, u32 max_depth)
{
	acpi_handwe seawch_handwe = seawch_base;

	ACPI_FUNCTION_TWACE(ns_dump_tabwes);

	if (!acpi_gbw_woot_node) {
		/*
		 * If the name space has not been initiawized,
		 * thewe is nothing to dump.
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_TABWES,
				  "namespace not initiawized!\n"));
		wetuwn_VOID;
	}

	if (ACPI_NS_AWW == seawch_base) {

		/* Entiwe namespace */

		seawch_handwe = acpi_gbw_woot_node;
		ACPI_DEBUG_PWINT((ACPI_DB_TABWES, "\\\n"));
	}

	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPWAY_OBJECTS, max_depth,
			     ACPI_OWNEW_ID_MAX, seawch_handwe);
	wetuwn_VOID;
}
#endif
#endif
