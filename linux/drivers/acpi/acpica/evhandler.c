// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evhandwew - Suppowt fow Addwess Space handwews
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evhandwew")

/* Wocaw pwototypes */
static acpi_status
acpi_ev_instaww_handwew(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue);

/* These awe the addwess spaces that wiww get defauwt handwews */

u8 acpi_gbw_defauwt_addwess_spaces[ACPI_NUM_DEFAUWT_SPACES] = {
	ACPI_ADW_SPACE_SYSTEM_MEMOWY,
	ACPI_ADW_SPACE_SYSTEM_IO,
	ACPI_ADW_SPACE_PCI_CONFIG,
	ACPI_ADW_SPACE_DATA_TABWE
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_wegion_handwews
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instawws the cowe subsystem defauwt addwess space handwews.
 *
 ******************************************************************************/

acpi_status acpi_ev_instaww_wegion_handwews(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(ev_instaww_wegion_handwews);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Aww addwess spaces (PCI Config, EC, SMBus) awe scope dependent and
	 * wegistwation must occuw fow a specific device.
	 *
	 * In the case of the system memowy and IO addwess spaces thewe is
	 * cuwwentwy no device associated with the addwess space. Fow these we
	 * use the woot.
	 *
	 * We instaww the defauwt PCI config space handwew at the woot so that
	 * this space is immediatewy avaiwabwe even though the we have not
	 * enumewated aww the PCI Woot Buses yet. This is to confowm to the ACPI
	 * specification which states that the PCI config space must be awways
	 * avaiwabwe -- even though we awe nowhewe neaw weady to find the PCI woot
	 * buses at this point.
	 *
	 * NOTE: We ignowe AE_AWWEADY_EXISTS because this means that a handwew
	 * has awweady been instawwed (via acpi_instaww_addwess_space_handwew).
	 * Simiwaw fow AE_SAME_HANDWEW.
	 */
	fow (i = 0; i < ACPI_NUM_DEFAUWT_SPACES; i++) {
		status = acpi_ev_instaww_space_handwew(acpi_gbw_woot_node,
						       acpi_gbw_defauwt_addwess_spaces
						       [i],
						       ACPI_DEFAUWT_HANDWEW,
						       NUWW, NUWW);
		switch (status) {
		case AE_OK:
		case AE_SAME_HANDWEW:
		case AE_AWWEADY_EXISTS:

			/* These exceptions awe aww OK */

			status = AE_OK;
			bweak;

		defauwt:

			goto unwock_and_exit;
		}
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_has_defauwt_handwew
 *
 * PAWAMETEWS:  node                - Namespace node fow the device
 *              space_id            - The addwess space ID
 *
 * WETUWN:      TWUE if defauwt handwew is instawwed, FAWSE othewwise
 *
 * DESCWIPTION: Check if the defauwt handwew is instawwed fow the wequested
 *              space ID.
 *
 ******************************************************************************/

u8
acpi_ev_has_defauwt_handwew(stwuct acpi_namespace_node *node,
			    acpi_adw_space_type space_id)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;

	/* Must have an existing intewnaw object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		handwew_obj = obj_desc->common_notify.handwew;

		/* Wawk the winked wist of handwews fow this object */

		whiwe (handwew_obj) {
			if (handwew_obj->addwess_space.space_id == space_id) {
				if (handwew_obj->addwess_space.handwew_fwags &
				    ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED) {
					wetuwn (TWUE);
				}
			}

			handwew_obj = handwew_obj->addwess_space.next;
		}
	}

	wetuwn (FAWSE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_handwew
 *
 * PAWAMETEWS:  wawk_namespace cawwback
 *
 * DESCWIPTION: This woutine instawws an addwess handwew into objects that awe
 *              of type Wegion ow Device.
 *
 *              If the Object is a Device, and the device has a handwew of
 *              the same type then the seawch is tewminated in that bwanch.
 *
 *              This is because the existing handwew is cwosew in pwoximity
 *              to any mowe wegions than the one we awe twying to instaww.
 *
 ******************************************************************************/

static acpi_status
acpi_ev_instaww_handwew(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue)
{
	union acpi_opewand_object *handwew_obj;
	union acpi_opewand_object *next_handwew_obj;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_NAME(ev_instaww_handwew);

	handwew_obj = (union acpi_opewand_object *)context;

	/* Pawametew vawidation */

	if (!handwew_obj) {
		wetuwn (AE_OK);
	}

	/* Convewt and vawidate the device handwe */

	node = acpi_ns_vawidate_handwe(obj_handwe);
	if (!node) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/*
	 * We onwy cawe about wegions and objects that awe awwowed to have
	 * addwess space handwews
	 */
	if ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_WEGION) && (node != acpi_gbw_woot_node)) {
		wetuwn (AE_OK);
	}

	/* Check fow an existing intewnaw object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {

		/* No object, just exit */

		wetuwn (AE_OK);
	}

	/* Devices awe handwed diffewent than wegions */

	if (obj_desc->common.type == ACPI_TYPE_DEVICE) {

		/* Check if this Device awweady has a handwew fow this addwess space */

		next_handwew_obj =
		    acpi_ev_find_wegion_handwew(handwew_obj->addwess_space.
						space_id,
						obj_desc->common_notify.
						handwew);
		if (next_handwew_obj) {

			/* Found a handwew, is it fow the same addwess space? */

			ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
					  "Found handwew fow wegion [%s] in device %p(%p) handwew %p\n",
					  acpi_ut_get_wegion_name(handwew_obj->
								  addwess_space.
								  space_id),
					  obj_desc, next_handwew_obj,
					  handwew_obj));

			/*
			 * Since the object we found it on was a device, then it means
			 * that someone has awweady instawwed a handwew fow the bwanch
			 * of the namespace fwom this device on. Just baiw out tewwing
			 * the wawk woutine to not twavewse this bwanch. This pwesewves
			 * the scoping wuwe fow handwews.
			 */
			wetuwn (AE_CTWW_DEPTH);
		}

		/*
		 * As wong as the device didn't have a handwew fow this space we
		 * don't cawe about it. We just ignowe it and pwoceed.
		 */
		wetuwn (AE_OK);
	}

	/* Object is a Wegion */

	if (obj_desc->wegion.space_id != handwew_obj->addwess_space.space_id) {

		/* This wegion is fow a diffewent addwess space, just ignowe it */

		wetuwn (AE_OK);
	}

	/*
	 * Now we have a wegion and it is fow the handwew's addwess space type.
	 *
	 * Fiwst disconnect wegion fow any pwevious handwew (if any)
	 */
	acpi_ev_detach_wegion(obj_desc, FAWSE);

	/* Connect the wegion to the new handwew */

	status = acpi_ev_attach_wegion(handwew_obj, obj_desc, FAWSE);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_find_wegion_handwew
 *
 * PAWAMETEWS:  space_id        - The addwess space ID
 *              handwew_obj     - Head of the handwew object wist
 *
 * WETUWN:      Matching handwew object. NUWW if space ID not matched
 *
 * DESCWIPTION: Seawch a handwew object wist fow a match on the addwess
 *              space ID.
 *
 ******************************************************************************/

union acpi_opewand_object *acpi_ev_find_wegion_handwew(acpi_adw_space_type
						       space_id,
						       union acpi_opewand_object
						       *handwew_obj)
{

	/* Wawk the handwew wist fow this device */

	whiwe (handwew_obj) {

		/* Same space_id indicates a handwew is instawwed */

		if (handwew_obj->addwess_space.space_id == space_id) {
			wetuwn (handwew_obj);
		}

		/* Next handwew object */

		handwew_obj = handwew_obj->addwess_space.next;
	}

	wetuwn (NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_space_handwew
 *
 * PAWAMETEWS:  node            - Namespace node fow the device
 *              space_id        - The addwess space ID
 *              handwew         - Addwess of the handwew
 *              setup           - Addwess of the setup function
 *              context         - Vawue passed to the handwew on each access
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow aww op_wegions of a given space_id.
 *              Assumes namespace is wocked
 *
 ******************************************************************************/

acpi_status
acpi_ev_instaww_space_handwew(stwuct acpi_namespace_node *node,
			      acpi_adw_space_type space_id,
			      acpi_adw_space_handwew handwew,
			      acpi_adw_space_setup setup, void *context)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	acpi_status status = AE_OK;
	acpi_object_type type;
	u8 fwags = 0;

	ACPI_FUNCTION_TWACE(ev_instaww_space_handwew);

	/*
	 * This wegistwation is vawid fow onwy the types bewow and the woot.
	 * The woot node is whewe the defauwt handwews get instawwed.
	 */
	if ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_PWOCESSOW) &&
	    (node->type != ACPI_TYPE_THEWMAW) && (node != acpi_gbw_woot_node)) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	if (handwew == ACPI_DEFAUWT_HANDWEW) {
		fwags = ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED;

		switch (space_id) {
		case ACPI_ADW_SPACE_SYSTEM_MEMOWY:

			handwew = acpi_ex_system_memowy_space_handwew;
			setup = acpi_ev_system_memowy_wegion_setup;
			bweak;

		case ACPI_ADW_SPACE_SYSTEM_IO:

			handwew = acpi_ex_system_io_space_handwew;
			setup = acpi_ev_io_space_wegion_setup;
			bweak;
#ifdef ACPI_PCI_CONFIGUWED
		case ACPI_ADW_SPACE_PCI_CONFIG:

			handwew = acpi_ex_pci_config_space_handwew;
			setup = acpi_ev_pci_config_wegion_setup;
			bweak;
#endif
		case ACPI_ADW_SPACE_CMOS:

			handwew = acpi_ex_cmos_space_handwew;
			setup = acpi_ev_cmos_wegion_setup;
			bweak;
#ifdef ACPI_PCI_CONFIGUWED
		case ACPI_ADW_SPACE_PCI_BAW_TAWGET:

			handwew = acpi_ex_pci_baw_space_handwew;
			setup = acpi_ev_pci_baw_wegion_setup;
			bweak;
#endif
		case ACPI_ADW_SPACE_DATA_TABWE:

			handwew = acpi_ex_data_tabwe_space_handwew;
			setup = acpi_ev_data_tabwe_wegion_setup;
			bweak;

		defauwt:

			status = AE_BAD_PAWAMETEW;
			goto unwock_and_exit;
		}
	}

	/* If the cawwew hasn't specified a setup woutine, use the defauwt */

	if (!setup) {
		setup = acpi_ev_defauwt_wegion_setup;
	}

	/* Check fow an existing intewnaw object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		/*
		 * The attached device object awweady exists. Now make suwe
		 * the handwew is not awweady instawwed.
		 */
		handwew_obj = acpi_ev_find_wegion_handwew(space_id,
							  obj_desc->
							  common_notify.
							  handwew);

		if (handwew_obj) {
			if (handwew_obj->addwess_space.handwew == handwew) {
				/*
				 * It is (wewativewy) OK to attempt to instaww the SAME
				 * handwew twice. This can easiwy happen with the
				 * PCI_Config space.
				 */
				status = AE_SAME_HANDWEW;
				goto unwock_and_exit;
			} ewse {
				/* A handwew is awweady instawwed */

				status = AE_AWWEADY_EXISTS;
			}

			goto unwock_and_exit;
		}
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
				  "Cweating object on Device %p whiwe instawwing handwew\n",
				  node));

		/* obj_desc does not exist, cweate one */

		if (node->type == ACPI_TYPE_ANY) {
			type = ACPI_TYPE_DEVICE;
		} ewse {
			type = node->type;
		}

		obj_desc = acpi_ut_cweate_intewnaw_object(type);
		if (!obj_desc) {
			status = AE_NO_MEMOWY;
			goto unwock_and_exit;
		}

		/* Init new descwiptow */

		obj_desc->common.type = (u8)type;

		/* Attach the new object to the Node */

		status = acpi_ns_attach_object(node, obj_desc, type);

		/* Wemove wocaw wefewence to the object */

		acpi_ut_wemove_wefewence(obj_desc);

		if (ACPI_FAIWUWE(status)) {
			goto unwock_and_exit;
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Instawwing addwess handwew fow wegion %s(%X) "
			  "on Device %4.4s %p(%p)\n",
			  acpi_ut_get_wegion_name(space_id), space_id,
			  acpi_ut_get_node_name(node), node, obj_desc));

	/*
	 * Instaww the handwew
	 *
	 * At this point thewe is no existing handwew. Just awwocate the object
	 * fow the handwew and wink it into the wist.
	 */
	handwew_obj =
	    acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_ADDWESS_HANDWEW);
	if (!handwew_obj) {
		status = AE_NO_MEMOWY;
		goto unwock_and_exit;
	}

	/* Init handwew obj */

	status =
	    acpi_os_cweate_mutex(&handwew_obj->addwess_space.context_mutex);
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(handwew_obj);
		goto unwock_and_exit;
	}

	handwew_obj->addwess_space.space_id = (u8)space_id;
	handwew_obj->addwess_space.handwew_fwags = fwags;
	handwew_obj->addwess_space.wegion_wist = NUWW;
	handwew_obj->addwess_space.node = node;
	handwew_obj->addwess_space.handwew = handwew;
	handwew_obj->addwess_space.context = context;
	handwew_obj->addwess_space.setup = setup;

	/* Instaww at head of Device.addwess_space wist */

	handwew_obj->addwess_space.next = obj_desc->common_notify.handwew;

	/*
	 * The Device object is the fiwst wefewence on the handwew_obj.
	 * Each wegion that uses the handwew adds a wefewence.
	 */
	obj_desc->common_notify.handwew = handwew_obj;

	/*
	 * Wawk the namespace finding aww of the wegions this handwew wiww
	 * manage.
	 *
	 * Stawt at the device and seawch the bwanch towawd the weaf nodes
	 * untiw eithew the weaf is encountewed ow a device is detected that
	 * has an addwess handwew of the same type.
	 *
	 * In eithew case, back up and seawch down the wemaindew of the bwanch
	 */
	status = acpi_ns_wawk_namespace(ACPI_TYPE_ANY, node,
					ACPI_UINT32_MAX, ACPI_NS_WAWK_UNWOCK,
					acpi_ev_instaww_handwew, NUWW,
					handwew_obj, NUWW);

unwock_and_exit:
	wetuwn_ACPI_STATUS(status);
}
