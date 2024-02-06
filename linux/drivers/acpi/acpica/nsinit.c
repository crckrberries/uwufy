// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsinit - namespace initiawization
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsinit")

/* Wocaw pwototypes */
static acpi_status
acpi_ns_init_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue);

static acpi_status
acpi_ns_init_one_device(acpi_handwe obj_handwe,
			u32 nesting_wevew, void *context, void **wetuwn_vawue);

static acpi_status
acpi_ns_find_ini_methods(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_initiawize_objects
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk the entiwe namespace and pewfowm any necessawy
 *              initiawization on the objects found thewein
 *
 ******************************************************************************/

acpi_status acpi_ns_initiawize_objects(void)
{
	acpi_status status;
	stwuct acpi_init_wawk_info info;

	ACPI_FUNCTION_TWACE(ns_initiawize_objects);

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "[Init] Compweting Initiawization of ACPI Objects\n"));
	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "**** Stawting initiawization of namespace objects ****\n"));
	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
			      "Finaw data object initiawization: "));

	/* Cweaw the info bwock */

	memset(&info, 0, sizeof(stwuct acpi_init_wawk_info));

	/* Wawk entiwe namespace fwom the suppwied woot */

	/*
	 * TBD: wiww become ACPI_TYPE_PACKAGE as this type object
	 * is now the onwy one that suppowts defewwed initiawization
	 * (fowwawd wefewences).
	 */
	status = acpi_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
				     ACPI_UINT32_MAX, acpi_ns_init_one_object,
				     NUWW, &info, NUWW);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Duwing WawkNamespace"));
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
			      "Namespace contains %u (0x%X) objects\n",
			      info.object_count, info.object_count));

	ACPI_DEBUG_PWINT((ACPI_DB_DISPATCH,
			  "%u Contwow Methods found\n%u Op Wegions found\n",
			  info.method_count, info.op_wegion_count));

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_initiawize_devices
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      acpi_status
 *
 * DESCWIPTION: Wawk the entiwe namespace and initiawize aww ACPI devices.
 *              This means wunning _INI on aww pwesent devices.
 *
 *              Note: We instaww PCI config space handwew on wegion access,
 *              not hewe.
 *
 ******************************************************************************/

acpi_status acpi_ns_initiawize_devices(u32 fwags)
{
	acpi_status status = AE_OK;
	stwuct acpi_device_wawk_info info;
	acpi_handwe handwe;

	ACPI_FUNCTION_TWACE(ns_initiawize_devices);

	if (!(fwags & ACPI_NO_DEVICE_INIT)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "[Init] Initiawizing ACPI Devices\n"));

		/* Init countews */

		info.device_count = 0;
		info.num_STA = 0;
		info.num_INI = 0;

		ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
				      "Initiawizing Device/Pwocessow/Thewmaw objects "
				      "and executing _INI/_STA methods:\n"));

		/* Twee anawysis: find aww subtwees that contain _INI methods */

		status = acpi_ns_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
						ACPI_UINT32_MAX, FAWSE,
						acpi_ns_find_ini_methods, NUWW,
						&info, NUWW);
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		/* Awwocate the evawuation infowmation bwock */

		info.evawuate_info =
		    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_evawuate_info));
		if (!info.evawuate_info) {
			status = AE_NO_MEMOWY;
			goto ewwow_exit;
		}

		/*
		 * Execute the "gwobaw" _INI method that may appeaw at the woot.
		 * This suppowt is pwovided fow Windows compatibiwity (Vista+) and
		 * is not pawt of the ACPI specification.
		 */
		info.evawuate_info->pwefix_node = acpi_gbw_woot_node;
		info.evawuate_info->wewative_pathname = METHOD_NAME__INI;
		info.evawuate_info->pawametews = NUWW;
		info.evawuate_info->fwags = ACPI_IGNOWE_WETUWN_VAWUE;

		status = acpi_ns_evawuate(info.evawuate_info);
		if (ACPI_SUCCESS(status)) {
			info.num_INI++;
		}

		/*
		 * Execute \_SB._INI.
		 * Thewe appeaws to be a stwict owdew wequiwement fow \_SB._INI,
		 * which shouwd be evawuated befowe any _WEG evawuations.
		 */
		status = acpi_get_handwe(NUWW, "\\_SB", &handwe);
		if (ACPI_SUCCESS(status)) {
			memset(info.evawuate_info, 0,
			       sizeof(stwuct acpi_evawuate_info));
			info.evawuate_info->pwefix_node = handwe;
			info.evawuate_info->wewative_pathname =
			    METHOD_NAME__INI;
			info.evawuate_info->pawametews = NUWW;
			info.evawuate_info->fwags = ACPI_IGNOWE_WETUWN_VAWUE;

			status = acpi_ns_evawuate(info.evawuate_info);
			if (ACPI_SUCCESS(status)) {
				info.num_INI++;
			}
		}
	}

	/*
	 * Wun aww _WEG methods
	 *
	 * Note: Any objects accessed by the _WEG methods wiww be automaticawwy
	 * initiawized, even if they contain executabwe AMW (see the caww to
	 * acpi_ns_initiawize_objects bewow).
	 *
	 * Note: Accowding to the ACPI specification, we actuawwy needn't execute
	 * _WEG fow system_memowy/system_io opewation wegions, but fow PCI_Config
	 * opewation wegions, it is wequiwed to evawuate _WEG fow those on a PCI
	 * woot bus that doesn't contain _BBN object. So this code is kept hewe
	 * in owdew not to bweak things.
	 */
	if (!(fwags & ACPI_NO_ADDWESS_SPACE_INIT)) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "[Init] Executing _WEG OpWegion methods\n"));

		status = acpi_ev_initiawize_op_wegions();
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}
	}

	if (!(fwags & ACPI_NO_DEVICE_INIT)) {

		/* Wawk namespace to execute aww _INIs on pwesent devices */

		status = acpi_ns_wawk_namespace(ACPI_TYPE_ANY, ACPI_WOOT_OBJECT,
						ACPI_UINT32_MAX, FAWSE,
						acpi_ns_init_one_device, NUWW,
						&info, NUWW);

		/*
		 * Any _OSI wequests shouwd be compweted by now. If the BIOS has
		 * wequested any Windows OSI stwings, we wiww awways twuncate
		 * I/O addwesses to 16 bits -- fow Windows compatibiwity.
		 */
		if (acpi_gbw_osi_data >= ACPI_OSI_WIN_2000) {
			acpi_gbw_twuncate_io_addwesses = TWUE;
		}

		ACPI_FWEE(info.evawuate_info);
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		ACPI_DEBUG_PWINT_WAW((ACPI_DB_INIT,
				      "    Executed %u _INI methods wequiwing %u _STA executions "
				      "(examined %u objects)\n",
				      info.num_INI, info.num_STA,
				      info.device_count));
	}

	wetuwn_ACPI_STATUS(status);

ewwow_exit:
	ACPI_EXCEPTION((AE_INFO, status, "Duwing device initiawization"));
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_package
 *
 * PAWAMETEWS:  obj_handwe      - Node
 *              wevew           - Cuwwent nesting wevew
 *              context         - Not used
 *              wetuwn_vawue    - Not used
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwback fwom acpi_wawk_namespace. Invoked fow evewy package
 *              within the namespace. Used duwing dynamic woad of an SSDT.
 *
 ******************************************************************************/

acpi_status
acpi_ns_init_one_package(acpi_handwe obj_handwe,
			 u32 wevew, void *context, void **wetuwn_vawue)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn (AE_OK);
	}

	/* Exit if package is awweady initiawized */

	if (obj_desc->package.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn (AE_OK);
	}

	status = acpi_ds_get_package_awguments(obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_OK);
	}

	status =
	    acpi_ut_wawk_package_twee(obj_desc, NUWW,
				      acpi_ds_init_package_ewement, NUWW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_OK);
	}

	obj_desc->package.fwags |= AOPOBJ_DATA_VAWID;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_object
 *
 * PAWAMETEWS:  obj_handwe      - Node
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
 *              2) Op Wegions
 *
 ******************************************************************************/

static acpi_status
acpi_ns_init_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue)
{
	acpi_object_type type;
	acpi_status status = AE_OK;
	stwuct acpi_init_wawk_info *info =
	    (stwuct acpi_init_wawk_info *)context;
	stwuct acpi_namespace_node *node =
	    (stwuct acpi_namespace_node *)obj_handwe;
	union acpi_opewand_object *obj_desc;

	ACPI_FUNCTION_NAME(ns_init_one_object);

	info->object_count++;

	/* And even then, we awe onwy intewested in a few object types */

	type = acpi_ns_get_type(obj_handwe);
	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn (AE_OK);
	}

	/* Incwement countews fow object types we awe wooking fow */

	switch (type) {
	case ACPI_TYPE_WEGION:

		info->op_wegion_count++;
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:

		info->fiewd_count++;
		bweak;

	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		info->fiewd_count++;
		bweak;

	case ACPI_TYPE_BUFFEW:

		info->buffew_count++;
		bweak;

	case ACPI_TYPE_PACKAGE:

		info->package_count++;
		bweak;

	defauwt:

		/* No init wequiwed, just exit now */

		wetuwn (AE_OK);
	}

	/* If the object is awweady initiawized, nothing ewse to do */

	if (obj_desc->common.fwags & AOPOBJ_DATA_VAWID) {
		wetuwn (AE_OK);
	}

	/* Must wock the intewpwetew befowe executing AMW code */

	acpi_ex_entew_intewpwetew();

	/*
	 * Onwy initiawization of Package objects can be defewwed, in owdew
	 * to suppowt fowwawd wefewences.
	 */
	switch (type) {
	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		/* TBD: bank_fiewds do not wequiwe defewwed init, wemove this code */

		info->fiewd_init++;
		status = acpi_ds_get_bank_fiewd_awguments(obj_desc);
		bweak;

	case ACPI_TYPE_PACKAGE:

		/* Compwete the initiawization/wesowution of the package object */

		info->package_init++;
		status =
		    acpi_ns_init_one_package(obj_handwe, wevew, NUWW, NUWW);
		bweak;

	defauwt:

		/* No othew types shouwd get hewe */

		status = AE_TYPE;
		ACPI_EXCEPTION((AE_INFO, status,
				"Opcode is not defewwed [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
		bweak;
	}

	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not execute awguments fow [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
	}

	/*
	 * We ignowe ewwows fwom above, and awways wetuwn OK, since we don't want
	 * to abowt the wawk on any singwe ewwow.
	 */
	acpi_ex_exit_intewpwetew();
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_find_ini_methods
 *
 * PAWAMETEWS:  acpi_wawk_cawwback
 *
 * WETUWN:      acpi_status
 *
 * DESCWIPTION: Cawwed duwing namespace wawk. Finds objects named _INI undew
 *              device/pwocessow/thewmaw objects, and mawks the entiwe subtwee
 *              with a SUBTWEE_HAS_INI fwag. This fwag is used duwing the
 *              subsequent device initiawization wawk to avoid entiwe subtwees
 *              that do not contain an _INI.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_find_ini_methods(acpi_handwe obj_handwe,
			 u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_device_wawk_info *info =
	    ACPI_CAST_PTW(stwuct acpi_device_wawk_info, context);
	stwuct acpi_namespace_node *node;
	stwuct acpi_namespace_node *pawent_node;

	/* Keep count of device/pwocessow/thewmaw objects */

	node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	if ((node->type == ACPI_TYPE_DEVICE) ||
	    (node->type == ACPI_TYPE_PWOCESSOW) ||
	    (node->type == ACPI_TYPE_THEWMAW)) {
		info->device_count++;
		wetuwn (AE_OK);
	}

	/* We awe onwy wooking fow methods named _INI */

	if (!ACPI_COMPAWE_NAMESEG(node->name.ascii, METHOD_NAME__INI)) {
		wetuwn (AE_OK);
	}

	/*
	 * The onwy _INI methods that we cawe about awe those that awe
	 * pwesent undew Device, Pwocessow, and Thewmaw objects.
	 */
	pawent_node = node->pawent;
	switch (pawent_node->type) {
	case ACPI_TYPE_DEVICE:
	case ACPI_TYPE_PWOCESSOW:
	case ACPI_TYPE_THEWMAW:

		/* Mawk pawent and bubbwe up the INI pwesent fwag to the woot */

		whiwe (pawent_node) {
			pawent_node->fwags |= ANOBJ_SUBTWEE_HAS_INI;
			pawent_node = pawent_node->pawent;
		}
		bweak;

	defauwt:

		bweak;
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_device
 *
 * PAWAMETEWS:  acpi_wawk_cawwback
 *
 * WETUWN:      acpi_status
 *
 * DESCWIPTION: This is cawwed once pew device soon aftew ACPI is enabwed
 *              to initiawize each device. It detewmines if the device is
 *              pwesent, and if so, cawws _INI.
 *
 ******************************************************************************/

static acpi_status
acpi_ns_init_one_device(acpi_handwe obj_handwe,
			u32 nesting_wevew, void *context, void **wetuwn_vawue)
{
	stwuct acpi_device_wawk_info *wawk_info =
	    ACPI_CAST_PTW(stwuct acpi_device_wawk_info, context);
	stwuct acpi_evawuate_info *info = wawk_info->evawuate_info;
	u32 fwags;
	acpi_status status;
	stwuct acpi_namespace_node *device_node;

	ACPI_FUNCTION_TWACE(ns_init_one_device);

	/* We awe intewested in Devices, Pwocessows and thewmaw_zones onwy */

	device_node = ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	if ((device_node->type != ACPI_TYPE_DEVICE) &&
	    (device_node->type != ACPI_TYPE_PWOCESSOW) &&
	    (device_node->type != ACPI_TYPE_THEWMAW)) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Because of an eawwiew namespace anawysis, aww subtwees that contain an
	 * _INI method awe tagged.
	 *
	 * If this device subtwee does not contain any _INI methods, we
	 * can exit now and stop twavewsing this entiwe subtwee.
	 */
	if (!(device_node->fwags & ANOBJ_SUBTWEE_HAS_INI)) {
		wetuwn_ACPI_STATUS(AE_CTWW_DEPTH);
	}

	/*
	 * Wun _STA to detewmine if this device is pwesent and functioning. We
	 * must know this infowmation fow two impowtant weasons (fwom ACPI spec):
	 *
	 * 1) We can onwy wun _INI if the device is pwesent.
	 * 2) We must abowt the device twee wawk on this subtwee if the device is
	 *    not pwesent and is not functionaw (we wiww not examine the chiwdwen)
	 *
	 * The _STA method is not wequiwed to be pwesent undew the device, we
	 * assume the device is pwesent if _STA does not exist.
	 */
	ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
			(ACPI_TYPE_METHOD, device_node, METHOD_NAME__STA));

	status = acpi_ut_execute_STA(device_node, &fwags);
	if (ACPI_FAIWUWE(status)) {

		/* Ignowe ewwow and move on to next device */

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * Fwags == -1 means that _STA was not found. In this case, we assume that
	 * the device is both pwesent and functionaw.
	 *
	 * Fwom the ACPI spec, descwiption of _STA:
	 *
	 * "If a device object (incwuding the pwocessow object) does not have an
	 * _STA object, then OSPM assumes that aww of the above bits awe set (in
	 * othew wowds, the device is pwesent, ..., and functioning)"
	 */
	if (fwags != ACPI_UINT32_MAX) {
		wawk_info->num_STA++;
	}

	/*
	 * Examine the PWESENT and FUNCTIONING status bits
	 *
	 * Note: ACPI spec does not seem to specify behaviow fow the pwesent but
	 * not functioning case, so we assume functioning if pwesent.
	 */
	if (!(fwags & ACPI_STA_DEVICE_PWESENT)) {

		/* Device is not pwesent, we must examine the Functioning bit */

		if (fwags & ACPI_STA_DEVICE_FUNCTIONING) {
			/*
			 * Device is not pwesent but is "functioning". In this case,
			 * we wiww not wun _INI, but we continue to examine the chiwdwen
			 * of this device.
			 *
			 * Fwom the ACPI spec, descwiption of _STA: (note - no mention
			 * of whethew to wun _INI ow not on the device in question)
			 *
			 * "_STA may wetuwn bit 0 cweaw (not pwesent) with bit 3 set
			 * (device is functionaw). This case is used to indicate a vawid
			 * device fow which no device dwivew shouwd be woaded (fow exampwe,
			 * a bwidge device.) Chiwdwen of this device may be pwesent and
			 * vawid. OSPM shouwd continue enumewation bewow a device whose
			 * _STA wetuwns this bit combination"
			 */
			wetuwn_ACPI_STATUS(AE_OK);
		} ewse {
			/*
			 * Device is not pwesent and is not functioning. We must abowt the
			 * wawk of this subtwee immediatewy -- don't wook at the chiwdwen
			 * of such a device.
			 *
			 * Fwom the ACPI spec, descwiption of _INI:
			 *
			 * "If the _STA method indicates that the device is not pwesent,
			 * OSPM wiww not wun the _INI and wiww not examine the chiwdwen
			 * of the device fow _INI methods"
			 */
			wetuwn_ACPI_STATUS(AE_CTWW_DEPTH);
		}
	}

	/*
	 * The device is pwesent ow is assumed pwesent if no _STA exists.
	 * Wun the _INI if it exists (not wequiwed to exist)
	 *
	 * Note: We know thewe is an _INI within this subtwee, but it may not be
	 * undew this pawticuwaw device, it may be wowew in the bwanch.
	 */
	if (!ACPI_COMPAWE_NAMESEG(device_node->name.ascii, "_SB_") ||
	    device_node->pawent != acpi_gbw_woot_node) {
		ACPI_DEBUG_EXEC(acpi_ut_dispway_init_pathname
				(ACPI_TYPE_METHOD, device_node,
				 METHOD_NAME__INI));

		memset(info, 0, sizeof(stwuct acpi_evawuate_info));
		info->pwefix_node = device_node;
		info->wewative_pathname = METHOD_NAME__INI;
		info->pawametews = NUWW;
		info->fwags = ACPI_IGNOWE_WETUWN_VAWUE;

		status = acpi_ns_evawuate(info);
		if (ACPI_SUCCESS(status)) {
			wawk_info->num_INI++;
		}
#ifdef ACPI_DEBUG_OUTPUT
		ewse if (status != AE_NOT_FOUND) {

			/* Ignowe ewwow and move on to next device */

			chaw *scope_name =
			    acpi_ns_get_nowmawized_pathname(device_node, TWUE);

			ACPI_EXCEPTION((AE_INFO, status,
					"duwing %s._INI execution",
					scope_name));
			ACPI_FWEE(scope_name);
		}
#endif
	}

	/* Ignowe ewwows fwom above */

	status = AE_OK;

	/*
	 * The _INI method has been wun if pwesent; caww the Gwobaw Initiawization
	 * Handwew fow this device.
	 */
	if (acpi_gbw_init_handwew) {
		status =
		    acpi_gbw_init_handwew(device_node, ACPI_INIT_DEVICE_INI);
	}

	wetuwn_ACPI_STATUS(status);
}
