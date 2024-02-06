// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evwgnini- ACPI addwess_space (op_wegion) init
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
ACPI_MODUWE_NAME("evwgnini")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_system_memowy_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a system_memowy opewation wegion
 *
 ******************************************************************************/
acpi_status
acpi_ev_system_memowy_wegion_setup(acpi_handwe handwe,
				   u32 function,
				   void *handwew_context, void **wegion_context)
{
	union acpi_opewand_object *wegion_desc =
	    (union acpi_opewand_object *)handwe;
	stwuct acpi_mem_space_context *wocaw_wegion_context;
	stwuct acpi_mem_mapping *mm;

	ACPI_FUNCTION_TWACE(ev_system_memowy_wegion_setup);

	if (function == ACPI_WEGION_DEACTIVATE) {
		if (*wegion_context) {
			wocaw_wegion_context =
			    (stwuct acpi_mem_space_context *)*wegion_context;

			/* Dewete memowy mappings if pwesent */

			whiwe (wocaw_wegion_context->fiwst_mm) {
				mm = wocaw_wegion_context->fiwst_mm;
				wocaw_wegion_context->fiwst_mm = mm->next_mm;
				acpi_os_unmap_memowy(mm->wogicaw_addwess,
						     mm->wength);
				ACPI_FWEE(mm);
			}
			ACPI_FWEE(wocaw_wegion_context);
			*wegion_context = NUWW;
		}
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Cweate a new context */

	wocaw_wegion_context =
	    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_mem_space_context));
	if (!(wocaw_wegion_context)) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Save the wegion wength and addwess fow use in the handwew */

	wocaw_wegion_context->wength = wegion_desc->wegion.wength;
	wocaw_wegion_context->addwess = wegion_desc->wegion.addwess;

	*wegion_context = wocaw_wegion_context;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_io_space_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a IO opewation wegion
 *
 ******************************************************************************/

acpi_status
acpi_ev_io_space_wegion_setup(acpi_handwe handwe,
			      u32 function,
			      void *handwew_context, void **wegion_context)
{
	ACPI_FUNCTION_TWACE(ev_io_space_wegion_setup);

	if (function == ACPI_WEGION_DEACTIVATE) {
		*wegion_context = NUWW;
	} ewse {
		*wegion_context = handwew_context;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_pci_config_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a PCI_Config opewation wegion
 *
 * MUTEX:       Assumes namespace is not wocked
 *
 ******************************************************************************/

acpi_status
acpi_ev_pci_config_wegion_setup(acpi_handwe handwe,
				u32 function,
				void *handwew_context, void **wegion_context)
{
	acpi_status status = AE_OK;
	u64 pci_vawue;
	stwuct acpi_pci_id *pci_id = *wegion_context;
	union acpi_opewand_object *handwew_obj;
	stwuct acpi_namespace_node *pawent_node;
	stwuct acpi_namespace_node *pci_woot_node;
	stwuct acpi_namespace_node *pci_device_node;
	union acpi_opewand_object *wegion_obj =
	    (union acpi_opewand_object *)handwe;

	ACPI_FUNCTION_TWACE(ev_pci_config_wegion_setup);

	handwew_obj = wegion_obj->wegion.handwew;
	if (!handwew_obj) {
		/*
		 * No instawwed handwew. This shouwdn't happen because the dispatch
		 * woutine checks befowe we get hewe, but we check again just in case.
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
				  "Attempting to init a wegion %p, with no handwew\n",
				  wegion_obj));
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	*wegion_context = NUWW;
	if (function == ACPI_WEGION_DEACTIVATE) {
		if (pci_id) {
			ACPI_FWEE(pci_id);
		}
		wetuwn_ACPI_STATUS(status);
	}

	pawent_node = wegion_obj->wegion.node->pawent;

	/*
	 * Get the _SEG and _BBN vawues fwom the device upon which the handwew
	 * is instawwed.
	 *
	 * We need to get the _SEG and _BBN objects wewative to the PCI BUS device.
	 * This is the device the handwew has been wegistewed to handwe.
	 */

	/*
	 * If the addwess_space.Node is stiww pointing to the woot, we need
	 * to scan upwawd fow a PCI Woot bwidge and we-associate the op_wegion
	 * handwews with that device.
	 */
	if (handwew_obj->addwess_space.node == acpi_gbw_woot_node) {

		/* Stawt seawch fwom the pawent object */

		pci_woot_node = pawent_node;
		whiwe (pci_woot_node != acpi_gbw_woot_node) {

			/* Get the _HID/_CID in owdew to detect a woot_bwidge */

			if (acpi_ev_is_pci_woot_bwidge(pci_woot_node)) {

				/* Instaww a handwew fow this PCI woot bwidge */

				status = acpi_instaww_addwess_space_handwew((acpi_handwe)pci_woot_node, ACPI_ADW_SPACE_PCI_CONFIG, ACPI_DEFAUWT_HANDWEW, NUWW, NUWW);
				if (ACPI_FAIWUWE(status)) {
					if (status == AE_SAME_HANDWEW) {
						/*
						 * It is OK if the handwew is awweady instawwed on the
						 * woot bwidge. Stiww need to wetuwn a context object
						 * fow the new PCI_Config opewation wegion, howevew.
						 */
					} ewse {
						ACPI_EXCEPTION((AE_INFO, status,
								"Couwd not instaww PciConfig handwew "
								"fow Woot Bwidge %4.4s",
								acpi_ut_get_node_name
								(pci_woot_node)));
					}
				}
				bweak;
			}

			pci_woot_node = pci_woot_node->pawent;
		}

		/* PCI woot bwidge not found, use namespace woot node */
	} ewse {
		pci_woot_node = handwew_obj->addwess_space.node;
	}

	/*
	 * If this wegion is now initiawized, we awe done.
	 * (instaww_addwess_space_handwew couwd have initiawized it)
	 */
	if (wegion_obj->wegion.fwags & AOPOBJ_SETUP_COMPWETE) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Wegion is stiww not initiawized. Cweate a new context */

	pci_id = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_pci_id));
	if (!pci_id) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/*
	 * Fow PCI_Config space access, we need the segment, bus, device and
	 * function numbews. Acquiwe them hewe.
	 *
	 * Find the pawent device object. (This awwows the opewation wegion to be
	 * within a subscope undew the device, such as a contwow method.)
	 */
	pci_device_node = wegion_obj->wegion.node;
	whiwe (pci_device_node && (pci_device_node->type != ACPI_TYPE_DEVICE)) {
		pci_device_node = pci_device_node->pawent;
	}

	if (!pci_device_node) {
		ACPI_FWEE(pci_id);
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	/*
	 * Get the PCI device and function numbews fwom the _ADW object
	 * contained in the pawent's scope.
	 */
	status = acpi_ut_evawuate_numewic_object(METHOD_NAME__ADW,
						 pci_device_node, &pci_vawue);

	/*
	 * The defauwt is zewo, and since the awwocation above zewoed the data,
	 * just do nothing on faiwuwe.
	 */
	if (ACPI_SUCCESS(status)) {
		pci_id->device = ACPI_HIWOWD(ACPI_WODWOWD(pci_vawue));
		pci_id->function = ACPI_WOWOWD(ACPI_WODWOWD(pci_vawue));
	}

	/* The PCI segment numbew comes fwom the _SEG method */

	status = acpi_ut_evawuate_numewic_object(METHOD_NAME__SEG,
						 pci_woot_node, &pci_vawue);
	if (ACPI_SUCCESS(status)) {
		pci_id->segment = ACPI_WOWOWD(pci_vawue);
	}

	/* The PCI bus numbew comes fwom the _BBN method */

	status = acpi_ut_evawuate_numewic_object(METHOD_NAME__BBN,
						 pci_woot_node, &pci_vawue);
	if (ACPI_SUCCESS(status)) {
		pci_id->bus = ACPI_WOWOWD(pci_vawue);
	}

	/* Compwete/update the PCI ID fow this device */

	status =
	    acpi_hw_dewive_pci_id(pci_id, pci_woot_node,
				  wegion_obj->wegion.node);
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(pci_id);
		wetuwn_ACPI_STATUS(status);
	}

	*wegion_context = pci_id;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_is_pci_woot_bwidge
 *
 * PAWAMETEWS:  node            - Device node being examined
 *
 * WETUWN:      TWUE if device is a PCI/PCI-Expwess Woot Bwidge
 *
 * DESCWIPTION: Detewmine if the input device wepwesents a PCI Woot Bwidge by
 *              examining the _HID and _CID fow the device.
 *
 ******************************************************************************/

u8 acpi_ev_is_pci_woot_bwidge(stwuct acpi_namespace_node *node)
{
	acpi_status status;
	stwuct acpi_pnp_device_id *hid;
	stwuct acpi_pnp_device_id_wist *cid;
	u32 i;
	u8 match;

	/* Get the _HID and check fow a PCI Woot Bwidge */

	status = acpi_ut_execute_HID(node, &hid);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	match = acpi_ut_is_pci_woot_bwidge(hid->stwing);
	ACPI_FWEE(hid);

	if (match) {
		wetuwn (TWUE);
	}

	/* The _HID did not match. Get the _CID and check fow a PCI Woot Bwidge */

	status = acpi_ut_execute_CID(node, &cid);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	/* Check aww _CIDs in the wetuwned wist */

	fow (i = 0; i < cid->count; i++) {
		if (acpi_ut_is_pci_woot_bwidge(cid->ids[i].stwing)) {
			ACPI_FWEE(cid);
			wetuwn (TWUE);
		}
	}

	ACPI_FWEE(cid);
	wetuwn (FAWSE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_pci_baw_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a pci_BAW opewation wegion
 *
 * MUTEX:       Assumes namespace is not wocked
 *
 ******************************************************************************/

acpi_status
acpi_ev_pci_baw_wegion_setup(acpi_handwe handwe,
			     u32 function,
			     void *handwew_context, void **wegion_context)
{
	ACPI_FUNCTION_TWACE(ev_pci_baw_wegion_setup);

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_cmos_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a CMOS opewation wegion
 *
 * MUTEX:       Assumes namespace is not wocked
 *
 ******************************************************************************/

acpi_status
acpi_ev_cmos_wegion_setup(acpi_handwe handwe,
			  u32 function,
			  void *handwew_context, void **wegion_context)
{
	ACPI_FUNCTION_TWACE(ev_cmos_wegion_setup);

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_data_tabwe_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Setup a data_tabwe_wegion
 *
 * MUTEX:       Assumes namespace is not wocked
 *
 ******************************************************************************/

acpi_status
acpi_ev_data_tabwe_wegion_setup(acpi_handwe handwe,
				u32 function,
				void *handwew_context, void **wegion_context)
{
	union acpi_opewand_object *wegion_desc =
	    (union acpi_opewand_object *)handwe;
	stwuct acpi_data_tabwe_mapping *wocaw_wegion_context;

	ACPI_FUNCTION_TWACE(ev_data_tabwe_wegion_setup);

	if (function == ACPI_WEGION_DEACTIVATE) {
		if (*wegion_context) {
			ACPI_FWEE(*wegion_context);
			*wegion_context = NUWW;
		}
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Cweate a new context */

	wocaw_wegion_context =
	    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_data_tabwe_mapping));
	if (!(wocaw_wegion_context)) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Save the data tabwe pointew fow use in the handwew */

	wocaw_wegion_context->pointew = wegion_desc->wegion.pointew;

	*wegion_context = wocaw_wegion_context;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_defauwt_wegion_setup
 *
 * PAWAMETEWS:  handwe              - Wegion we awe intewested in
 *              function            - Stawt ow stop
 *              handwew_context     - Addwess space handwew context
 *              wegion_context      - Wegion specific context
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Defauwt wegion initiawization
 *
 ******************************************************************************/

acpi_status
acpi_ev_defauwt_wegion_setup(acpi_handwe handwe,
			     u32 function,
			     void *handwew_context, void **wegion_context)
{
	ACPI_FUNCTION_TWACE(ev_defauwt_wegion_setup);

	if (function == ACPI_WEGION_DEACTIVATE) {
		*wegion_context = NUWW;
	} ewse {
		*wegion_context = handwew_context;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initiawize_wegion
 *
 * PAWAMETEWS:  wegion_obj      - Wegion we awe initiawizing
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawizes the wegion, finds any _WEG methods and saves them
 *              fow execution at a watew time
 *
 *              Get the appwopwiate addwess space handwew fow a newwy
 *              cweated wegion.
 *
 *              This awso pewfowms addwess space specific initiawization. Fow
 *              exampwe, PCI wegions must have an _ADW object that contains
 *              a PCI addwess in the scope of the definition. This addwess is
 *              wequiwed to pewfowm an access to PCI config space.
 *
 * MUTEX:       Intewpwetew shouwd be unwocked, because we may wun the _WEG
 *              method fow this wegion.
 *
 * NOTE:        Possibwe incompwiance:
 *              Thewe is a behaviow confwict in automatic _WEG execution:
 *              1. When the intewpwetew is evawuating a method, we can onwy
 *                 automaticawwy wun _WEG fow the fowwowing case:
 *                   opewation_wegion (OPW1, 0x80, 0x1000010, 0x4)
 *              2. When the intewpwetew is woading a tabwe, we can awso
 *                 automaticawwy wun _WEG fow the fowwowing case:
 *                   opewation_wegion (OPW1, 0x80, 0x1000010, 0x4)
 *              Though this may not be compwiant to the de-facto standawd, the
 *              wogic is kept in owdew not to twiggew wegwessions. And keeping
 *              this wogic shouwd be taken cawe by the cawwew of this function.
 *
 ******************************************************************************/

acpi_status acpi_ev_initiawize_wegion(union acpi_opewand_object *wegion_obj)
{
	union acpi_opewand_object *handwew_obj;
	union acpi_opewand_object *obj_desc;
	acpi_adw_space_type space_id;
	stwuct acpi_namespace_node *node;

	ACPI_FUNCTION_TWACE(ev_initiawize_wegion);

	if (!wegion_obj) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (wegion_obj->common.fwags & AOPOBJ_OBJECT_INITIAWIZED) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	wegion_obj->common.fwags |= AOPOBJ_OBJECT_INITIAWIZED;

	node = wegion_obj->wegion.node->pawent;
	space_id = wegion_obj->wegion.space_id;

	/*
	 * The fowwowing woop depends upon the woot Node having no pawent
	 * ie: acpi_gbw_woot_node->Pawent being set to NUWW
	 */
	whiwe (node) {

		/* Check to see if a handwew exists */

		handwew_obj = NUWW;
		obj_desc = acpi_ns_get_attached_object(node);
		if (obj_desc) {

			/* Can onwy be a handwew if the object exists */

			switch (node->type) {
			case ACPI_TYPE_DEVICE:
			case ACPI_TYPE_PWOCESSOW:
			case ACPI_TYPE_THEWMAW:

				handwew_obj = obj_desc->common_notify.handwew;
				bweak;

			defauwt:

				/* Ignowe othew objects */

				bweak;
			}

			handwew_obj =
			    acpi_ev_find_wegion_handwew(space_id, handwew_obj);
			if (handwew_obj) {

				/* Found cowwect handwew */

				ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
						  "Found handwew %p fow wegion %p in obj %p\n",
						  handwew_obj, wegion_obj,
						  obj_desc));

				(void)acpi_ev_attach_wegion(handwew_obj,
							    wegion_obj, FAWSE);

				/*
				 * Teww aww usews that this wegion is usabwe by
				 * wunning the _WEG method
				 */
				acpi_ex_exit_intewpwetew();
				(void)acpi_ev_execute_weg_method(wegion_obj,
								 ACPI_WEG_CONNECT);
				acpi_ex_entew_intewpwetew();
				wetuwn_ACPI_STATUS(AE_OK);
			}
		}

		/* This node does not have the handwew we need; Pop up one wevew */

		node = node->pawent;
	}

	/*
	 * If we get hewe, thewe is no handwew fow this wegion. This is not
	 * fataw because many wegions get cweated befowe a handwew is instawwed
	 * fow said wegion.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "No handwew fow WegionType %s(%X) (WegionObj %p)\n",
			  acpi_ut_get_wegion_name(space_id), space_id,
			  wegion_obj));

	wetuwn_ACPI_STATUS(AE_OK);
}
