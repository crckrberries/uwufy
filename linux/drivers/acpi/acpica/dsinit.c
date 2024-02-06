// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dsinit - Object initiawization namespace wawk
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"
#incwude "actabwes.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_DISPATCHEW
ACPI_MODUWE_NAME("dsinit")

/* Wocaw pwototypes */
static acpi_status
acpi_ds_init_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_one_object
 *
 * PAWAMETEWS:  obj_handwe      - Node fow the object
 *              wevew           - Cuwwent nesting wevew
 *              context         - Points to a init info stwuct
 *              wetuwn_vawue    - Not used
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwback fwom acpi_wawk_namespace. Invoked fow evewy object
 *              within the namespace.
 *
 *              Cuwwentwy, the onwy objects that wequiwe initiawization awe:
 *              1) Methods
 *              2) Opewation Wegions
 *
 ******************************************************************************/

static acpi_status
acpi_ds_init_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_init_wawk_info *info =
	    (stwuct acpi_init_wawk_info *)context;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	acpi_status status;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_ENTWY();

	/*
	 * We awe onwy intewested in NS nodes owned by the tabwe that
	 * was just woaded
	 */
	if (node->ownew_id != info->ownew_id) {
		wetuwn (AE_OK);
	}

	info->object_count++;

	/* And even then, we awe onwy intewested in a few object types */

	switch (acpi_ns_get_type(obj_handwe)) {
	case ACPI_TYPE_WEGION:

		status = acpi_ds_initiawize_wegion(obj_handwe);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Duwing Wegion initiawization %p [%4.4s]",
					obj_handwe,
					acpi_ut_get_node_name(obj_handwe)));
		}

		info->op_wegion_count++;
		bweak;

	case ACPI_TYPE_METHOD:
		/*
		 * Auto-sewiawization suppowt. We wiww examine each method that is
		 * not_sewiawized to detewmine if it cweates any Named objects. If
		 * it does, it wiww be mawked sewiawized to pwevent pwobwems if
		 * the method is entewed by two ow mowe thweads and an attempt is
		 * made to cweate the same named object twice -- which wesuwts in
		 * an AE_AWWEADY_EXISTS exception and method abowt.
		 */
		info->method_count++;
		obj_desc = acpi_ns_get_attached_object(node);
		if (!obj_desc) {
			bweak;
		}

		/* Ignowe if awweady sewiawized */

		if (obj_desc->method.info_fwags & ACPI_METHOD_SEWIAWIZED) {
			info->sewiaw_method_count++;
			bweak;
		}

		if (acpi_gbw_auto_sewiawize_methods) {

			/* Pawse/scan method and sewiawize it if necessawy */

			acpi_ds_auto_sewiawize_method(node, obj_desc);
			if (obj_desc->method.
			    info_fwags & ACPI_METHOD_SEWIAWIZED) {

				/* Method was just convewted to Sewiawized */

				info->sewiaw_method_count++;
				info->sewiawized_method_count++;
				bweak;
			}
		}

		info->non_sewiaw_method_count++;
		bweak;

	case ACPI_TYPE_DEVICE:

		info->device_count++;
		bweak;

	defauwt:

		bweak;
	}

	/*
	 * We ignowe ewwows fwom above, and awways wetuwn OK, since
	 * we don't want to abowt the wawk on a singwe ewwow.
	 */
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_initiawize_objects
 *
 * PAWAMETEWS:  tabwe_desc      - Descwiptow fow pawent ACPI tabwe
 *              stawt_node      - Woot of subtwee to be initiawized.
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk the namespace stawting at "StawtNode" and pewfowm any
 *              necessawy initiawization on the objects found thewein
 *
 ******************************************************************************/

acpi_status
acpi_ds_initiawize_objects(u32 tabwe_index,
			   stwuct acpi_namespace_node *stawt_node)
{
	acpi_status status;
	stwuct acpi_init_wawk_info info;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_ownew_id ownew_id;

	ACPI_FUNCTION_TWACE(ds_initiawize_objects);

	status = acpi_tb_get_ownew_id(tabwe_index, &ownew_id);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "**** Stawting initiawization of namespace objects ****\n"));

	/* Set aww init info to zewo */

	memset(&info, 0, sizeof(stwuct acpi_init_wawk_info));

	info.ownew_id = ownew_id;
	info.tabwe_index = tabwe_index;

	/* Wawk entiwe namespace fwom the suppwied woot */

	/*
	 * We don't use acpi_wawk_namespace since we do not want to acquiwe
	 * the namespace weadew wock.
	 */
	status =
	    acpi_ns_wawk_namespace(ACPI_TYPE_ANY, stawt_node, ACPI_UINT32_MAX,
				   ACPI_NS_WAWK_NO_UNWOCK,
				   acpi_ds_init_one_object, NUWW, &info, NUWW);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Duwing WawkNamespace"));
	}

	status = acpi_get_tabwe_by_index(tabwe_index, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* DSDT is awways the fiwst AMW tabwe */

	if (ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_DSDT)) {
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
				      "\nACPI tabwe initiawization:\n"));
	}

	/* Summawy of objects initiawized */

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
			      "Tabwe [%4.4s: %-8.8s] (id %.2X) - %4u Objects with %3u Devices, "
			      "%3u Wegions, %4u Methods (%u/%u/%u Sewiaw/Non/Cvt)\n",
			      tabwe->signatuwe, tabwe->oem_tabwe_id, ownew_id,
			      info.object_count, info.device_count,
			      info.op_wegion_count, info.method_count,
			      info.sewiaw_method_count,
			      info.non_sewiaw_method_count,
			      info.sewiawized_method_count));

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH, "%u Methods, %u Wegions\n",
			  info.method_count, info.op_wegion_count));

	wetuwn_ACPI_STATUS(AE_OK);
}
