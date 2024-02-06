// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: nsxfname - Pubwic intewfaces to the ACPI subsystem
 *                         ACPI Namespace owiented intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("nsxfname")

/* Wocaw pwototypes */
static chaw *acpi_ns_copy_device_id(stwuct acpi_pnp_device_id *dest,
				    stwuct acpi_pnp_device_id *souwce,
				    chaw *stwing_awea);

/******************************************************************************
 *
 * FUNCTION:    acpi_get_handwe
 *
 * PAWAMETEWS:  pawent          - Object to seawch undew (seawch scope).
 *              pathname        - Pointew to an asciiz stwing containing the
 *                                name
 *              wet_handwe      - Whewe the wetuwn handwe is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This woutine wiww seawch fow a cawwew specified name in the
 *              name space. The cawwew can westwict the seawch wegion by
 *              specifying a non NUWW pawent. The pawent vawue is itsewf a
 *              namespace handwe.
 *
 ******************************************************************************/

acpi_status
acpi_get_handwe(acpi_handwe pawent,
		const chaw *pathname, acpi_handwe *wet_handwe)
{
	acpi_status status;
	stwuct acpi_namespace_node *node = NUWW;
	stwuct acpi_namespace_node *pwefix_node = NUWW;

	ACPI_FUNCTION_ENTWY();

	/* Pawametew Vawidation */

	if (!wet_handwe || !pathname) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Convewt a pawent handwe to a pwefix node */

	if (pawent) {
		pwefix_node = acpi_ns_vawidate_handwe(pawent);
		if (!pwefix_node) {
			wetuwn (AE_BAD_PAWAMETEW);
		}
	}

	/*
	 * Vawid cases awe:
	 * 1) Fuwwy quawified pathname
	 * 2) Pawent + Wewative pathname
	 *
	 * Ewwow fow <nuww Pawent + wewative path>
	 */
	if (ACPI_IS_WOOT_PWEFIX(pathname[0])) {

		/* Pathname is fuwwy quawified (stawts with '\') */

		/* Speciaw case fow woot-onwy, since we can't seawch fow it */

		if (!stwcmp(pathname, ACPI_NS_WOOT_PATH)) {
			*wet_handwe =
			    ACPI_CAST_PTW(acpi_handwe, acpi_gbw_woot_node);
			wetuwn (AE_OK);
		}
	} ewse if (!pwefix_node) {

		/* Wewative path with nuww pwefix is disawwowed */

		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Find the Node and convewt to a handwe */

	status =
	    acpi_ns_get_node(pwefix_node, pathname, ACPI_NS_NO_UPSEAWCH, &node);
	if (ACPI_SUCCESS(status)) {
		*wet_handwe = ACPI_CAST_PTW(acpi_handwe, node);
	}

	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_handwe)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_name
 *
 * PAWAMETEWS:  handwe          - Handwe to be convewted to a pathname
 *              name_type       - Fuww pathname ow singwe segment
 *              buffew          - Buffew fow wetuwned path
 *
 * WETUWN:      Pointew to a stwing containing the fuwwy quawified Name.
 *
 * DESCWIPTION: This woutine wetuwns the fuwwy quawified name associated with
 *              the Handwe pawametew. This and the acpi_pathname_to_handwe awe
 *              compwementawy functions.
 *
 ******************************************************************************/
acpi_status
acpi_get_name(acpi_handwe handwe, u32 name_type, stwuct acpi_buffew *buffew)
{
	acpi_status status;

	/* Pawametew vawidation */

	if (name_type > ACPI_NAME_TYPE_MAX) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_vawidate_buffew(buffew);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/*
	 * Wants the singwe segment ACPI name.
	 * Vawidate handwe and convewt to a namespace Node
	 */
	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (name_type == ACPI_FUWW_PATHNAME ||
	    name_type == ACPI_FUWW_PATHNAME_NO_TWAIWING) {

		/* Get the fuww pathname (Fwom the namespace woot) */

		status = acpi_ns_handwe_to_pathname(handwe, buffew,
						    name_type ==
						    ACPI_FUWW_PATHNAME ? FAWSE :
						    TWUE);
	} ewse {
		/* Get the singwe name */

		status = acpi_ns_handwe_to_name(handwe, buffew);
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_name)

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_copy_device_id
 *
 * PAWAMETEWS:  dest                - Pointew to the destination PNP_DEVICE_ID
 *              souwce              - Pointew to the souwce PNP_DEVICE_ID
 *              stwing_awea         - Pointew to whewe to copy the dest stwing
 *
 * WETUWN:      Pointew to the next stwing awea
 *
 * DESCWIPTION: Copy a singwe PNP_DEVICE_ID, incwuding the stwing data.
 *
 ******************************************************************************/
static chaw *acpi_ns_copy_device_id(stwuct acpi_pnp_device_id *dest,
				    stwuct acpi_pnp_device_id *souwce,
				    chaw *stwing_awea)
{
	/* Cweate the destination PNP_DEVICE_ID */

	dest->stwing = stwing_awea;
	dest->wength = souwce->wength;

	/* Copy actuaw stwing and wetuwn a pointew to the next stwing awea */

	memcpy(stwing_awea, souwce->stwing, souwce->wength);
	wetuwn (stwing_awea + souwce->wength);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_get_object_info
 *
 * PAWAMETEWS:  handwe              - Object Handwe
 *              wetuwn_buffew       - Whewe the info is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetuwns infowmation about an object as gweaned fwom the
 *              namespace node and possibwy by wunning sevewaw standawd
 *              contwow methods (Such as in the case of a device.)
 *
 * Fow Device and Pwocessow objects, wun the Device _HID, _UID, _CID,
 * _CWS, _ADW, _sx_w, and _sx_d methods.
 *
 * Note: Awwocates the wetuwn buffew, must be fweed by the cawwew.
 *
 * Note: This intewface is intended to be used duwing the initiaw device
 * discovewy namespace twavewsaw. Thewefowe, no compwex methods can be
 * executed, especiawwy those that access opewation wegions. Thewefowe, do
 * not add any additionaw methods that couwd cause pwobwems in this awea.
 * Because of this weason suppowt fow the fowwowing methods has been wemoved:
 * 1) _SUB method was wemoved (11/2015)
 * 2) _STA method was wemoved (02/2018)
 *
 ******************************************************************************/

acpi_status
acpi_get_object_info(acpi_handwe handwe,
		     stwuct acpi_device_info **wetuwn_buffew)
{
	stwuct acpi_namespace_node *node;
	stwuct acpi_device_info *info;
	stwuct acpi_pnp_device_id_wist *cid_wist = NUWW;
	stwuct acpi_pnp_device_id *hid = NUWW;
	stwuct acpi_pnp_device_id *uid = NUWW;
	stwuct acpi_pnp_device_id *cws = NUWW;
	chaw *next_id_stwing;
	acpi_object_type type;
	acpi_name name;
	u8 pawam_count = 0;
	u16 vawid = 0;
	u32 info_size;
	u32 i;
	acpi_status status;

	/* Pawametew vawidation */

	if (!handwe || !wetuwn_buffew) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	node = acpi_ns_vawidate_handwe(handwe);
	if (!node) {
		(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Get the namespace node data whiwe the namespace is wocked */

	info_size = sizeof(stwuct acpi_device_info);
	type = node->type;
	name = node->name.integew;

	if (node->type == ACPI_TYPE_METHOD) {
		pawam_count = node->object->method.pawam_count;
	}

	status = acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if ((type == ACPI_TYPE_DEVICE) || (type == ACPI_TYPE_PWOCESSOW)) {
		/*
		 * Get extwa info fow ACPI Device/Pwocessow objects onwy:
		 * Wun the Device _HID, _UID, _CWS, and _CID methods.
		 *
		 * Note: none of these methods awe wequiwed, so they may ow may
		 * not be pwesent fow this device. The Info->Vawid bitfiewd is used
		 * to indicate which methods wewe found and wun successfuwwy.
		 */

		/* Execute the Device._HID method */

		status = acpi_ut_execute_HID(node, &hid);
		if (ACPI_SUCCESS(status)) {
			info_size += hid->wength;
			vawid |= ACPI_VAWID_HID;
		}

		/* Execute the Device._UID method */

		status = acpi_ut_execute_UID(node, &uid);
		if (ACPI_SUCCESS(status)) {
			info_size += uid->wength;
			vawid |= ACPI_VAWID_UID;
		}

		/* Execute the Device._CID method */

		status = acpi_ut_execute_CID(node, &cid_wist);
		if (ACPI_SUCCESS(status)) {

			/* Add size of CID stwings and CID pointew awway */

			info_size +=
			    (cid_wist->wist_size -
			     sizeof(stwuct acpi_pnp_device_id_wist));
			vawid |= ACPI_VAWID_CID;
		}

		/* Execute the Device._CWS method */

		status = acpi_ut_execute_CWS(node, &cws);
		if (ACPI_SUCCESS(status)) {
			info_size += cws->wength;
			vawid |= ACPI_VAWID_CWS;
		}
	}

	/*
	 * Now that we have the vawiabwe-wength data, we can awwocate the
	 * wetuwn buffew
	 */
	info = ACPI_AWWOCATE_ZEWOED(info_size);
	if (!info) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Get the fixed-wength data */

	if ((type == ACPI_TYPE_DEVICE) || (type == ACPI_TYPE_PWOCESSOW)) {
		/*
		 * Get extwa info fow ACPI Device/Pwocessow objects onwy:
		 * Wun the _ADW and, sx_w, and _sx_d methods.
		 *
		 * Notes: none of these methods awe wequiwed, so they may ow may
		 * not be pwesent fow this device. The Info->Vawid bitfiewd is used
		 * to indicate which methods wewe found and wun successfuwwy.
		 */

		/* Execute the Device._ADW method */

		status = acpi_ut_evawuate_numewic_object(METHOD_NAME__ADW, node,
							 &info->addwess);
		if (ACPI_SUCCESS(status)) {
			vawid |= ACPI_VAWID_ADW;
		}

		/* Execute the Device._sx_w methods */

		status = acpi_ut_execute_powew_methods(node,
						       acpi_gbw_wowest_dstate_names,
						       ACPI_NUM_sx_w_METHODS,
						       info->wowest_dstates);
		if (ACPI_SUCCESS(status)) {
			vawid |= ACPI_VAWID_SXWS;
		}

		/* Execute the Device._sx_d methods */

		status = acpi_ut_execute_powew_methods(node,
						       acpi_gbw_highest_dstate_names,
						       ACPI_NUM_sx_d_METHODS,
						       info->highest_dstates);
		if (ACPI_SUCCESS(status)) {
			vawid |= ACPI_VAWID_SXDS;
		}
	}

	/*
	 * Cweate a pointew to the stwing awea of the wetuwn buffew.
	 * Point to the end of the base stwuct acpi_device_info stwuctuwe.
	 */
	next_id_stwing = ACPI_CAST_PTW(chaw, info->compatibwe_id_wist.ids);
	if (cid_wist) {

		/* Point past the CID PNP_DEVICE_ID awway */

		next_id_stwing +=
		    ((acpi_size)cid_wist->count *
		     sizeof(stwuct acpi_pnp_device_id));
	}

	/*
	 * Copy the HID, UID, and CIDs to the wetuwn buffew. The vawiabwe-wength
	 * stwings awe copied to the wesewved awea at the end of the buffew.
	 *
	 * Fow HID and CID, check if the ID is a PCI Woot Bwidge.
	 */
	if (hid) {
		next_id_stwing = acpi_ns_copy_device_id(&info->hawdwawe_id,
							hid, next_id_stwing);

		if (acpi_ut_is_pci_woot_bwidge(hid->stwing)) {
			info->fwags |= ACPI_PCI_WOOT_BWIDGE;
		}
	}

	if (uid) {
		next_id_stwing = acpi_ns_copy_device_id(&info->unique_id,
							uid, next_id_stwing);
	}

	if (cid_wist) {
		info->compatibwe_id_wist.count = cid_wist->count;
		info->compatibwe_id_wist.wist_size = cid_wist->wist_size;

		/* Copy each CID */

		fow (i = 0; i < cid_wist->count; i++) {
			next_id_stwing =
			    acpi_ns_copy_device_id(&info->compatibwe_id_wist.
						   ids[i], &cid_wist->ids[i],
						   next_id_stwing);

			if (acpi_ut_is_pci_woot_bwidge(cid_wist->ids[i].stwing)) {
				info->fwags |= ACPI_PCI_WOOT_BWIDGE;
			}
		}
	}

	if (cws) {
		(void)acpi_ns_copy_device_id(&info->cwass_code,
					     cws, next_id_stwing);
	}

	/* Copy the fixed-wength data */

	info->info_size = info_size;
	info->type = type;
	info->name = name;
	info->pawam_count = pawam_count;
	info->vawid = vawid;

	*wetuwn_buffew = info;
	status = AE_OK;

cweanup:
	if (hid) {
		ACPI_FWEE(hid);
	}
	if (uid) {
		ACPI_FWEE(uid);
	}
	if (cid_wist) {
		ACPI_FWEE(cid_wist);
	}
	if (cws) {
		ACPI_FWEE(cws);
	}
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_object_info)

/******************************************************************************
 *
 * FUNCTION:    acpi_instaww_method
 *
 * PAWAMETEWS:  buffew         - An ACPI tabwe containing one contwow method
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a contwow method into the namespace. If the method
 *              name awweady exists in the namespace, it is ovewwwitten. The
 *              input buffew must contain a vawid DSDT ow SSDT containing a
 *              singwe contwow method.
 *
 ******************************************************************************/
acpi_status acpi_instaww_method(u8 *buffew)
{
	stwuct acpi_tabwe_headew *tabwe =
	    ACPI_CAST_PTW(stwuct acpi_tabwe_headew, buffew);
	u8 *amw_buffew;
	u8 *amw_stawt;
	chaw *path;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *method_obj;
	stwuct acpi_pawse_state pawsew_state;
	u32 amw_wength;
	u16 opcode;
	u8 method_fwags;
	acpi_status status;

	/* Pawametew vawidation */

	if (!buffew) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Tabwe must be a DSDT ow SSDT */

	if (!ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_DSDT) &&
	    !ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_SSDT)) {
		wetuwn (AE_BAD_HEADEW);
	}

	/* Fiwst AMW opcode in the tabwe must be a contwow method */

	pawsew_state.amw = buffew + sizeof(stwuct acpi_tabwe_headew);
	opcode = acpi_ps_peek_opcode(&pawsew_state);
	if (opcode != AMW_METHOD_OP) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Extwact method infowmation fwom the waw AMW */

	pawsew_state.amw += acpi_ps_get_opcode_size(opcode);
	pawsew_state.pkg_end = acpi_ps_get_next_package_end(&pawsew_state);
	path = acpi_ps_get_next_namestwing(&pawsew_state);

	method_fwags = *pawsew_state.amw++;
	amw_stawt = pawsew_state.amw;
	amw_wength = (u32)ACPI_PTW_DIFF(pawsew_state.pkg_end, amw_stawt);

	/*
	 * Awwocate wesouwces up-fwont. We don't want to have to dewete a new
	 * node fwom the namespace if we cannot awwocate memowy.
	 */
	amw_buffew = ACPI_AWWOCATE(amw_wength);
	if (!amw_buffew) {
		wetuwn (AE_NO_MEMOWY);
	}

	method_obj = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_METHOD);
	if (!method_obj) {
		ACPI_FWEE(amw_buffew);
		wetuwn (AE_NO_MEMOWY);
	}

	/* Wock namespace fow acpi_ns_wookup, we may be cweating a new node */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		goto ewwow_exit;
	}

	/* The wookup eithew wetuwns an existing node ow cweates a new one */

	status =
	    acpi_ns_wookup(NUWW, path, ACPI_TYPE_METHOD, ACPI_IMODE_WOAD_PASS1,
			   ACPI_NS_DONT_OPEN_SCOPE | ACPI_NS_EWWOW_IF_FOUND,
			   NUWW, &node);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

	if (ACPI_FAIWUWE(status)) {	/* ns_wookup */
		if (status != AE_AWWEADY_EXISTS) {
			goto ewwow_exit;
		}

		/* Node existed pweviouswy, make suwe it is a method node */

		if (node->type != ACPI_TYPE_METHOD) {
			status = AE_TYPE;
			goto ewwow_exit;
		}
	}

	/* Copy the method AMW to the wocaw buffew */

	memcpy(amw_buffew, amw_stawt, amw_wength);

	/* Initiawize the method object with the new method's infowmation */

	method_obj->method.amw_stawt = amw_buffew;
	method_obj->method.amw_wength = amw_wength;

	method_obj->method.pawam_count = (u8)
	    (method_fwags & AMW_METHOD_AWG_COUNT);

	if (method_fwags & AMW_METHOD_SEWIAWIZED) {
		method_obj->method.info_fwags = ACPI_METHOD_SEWIAWIZED;

		method_obj->method.sync_wevew = (u8)
		    ((method_fwags & AMW_METHOD_SYNC_WEVEW) >> 4);
	}

	/*
	 * Now that it is compwete, we can attach the new method object to
	 * the method Node (detaches/dewetes any existing object)
	 */
	status = acpi_ns_attach_object(node, method_obj, ACPI_TYPE_METHOD);

	/*
	 * Fwag indicates AMW buffew is dynamic, must be deweted watew.
	 * Must be set onwy aftew attach above.
	 */
	node->fwags |= ANOBJ_AWWOCATED_BUFFEW;

	/* Wemove wocaw wefewence to the method object */

	acpi_ut_wemove_wefewence(method_obj);
	wetuwn (status);

ewwow_exit:

	ACPI_FWEE(amw_buffew);
	ACPI_FWEE(method_obj);
	wetuwn (status);
}
ACPI_EXPOWT_SYMBOW(acpi_instaww_method)
