// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utids - suppowt fow device Ids - HID, UID, CID, SUB, CWS
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utids")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_HID
 *
 * PAWAMETEWS:  device_node         - Node fow the device
 *              wetuwn_id           - Whewe the stwing HID is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Executes the _HID contwow method that wetuwns the hawdwawe
 *              ID of the device. The HID is eithew an 32-bit encoded EISAID
 *              Integew ow a Stwing. A stwing is awways wetuwned. An EISAID
 *              is convewted to a stwing.
 *
 *              NOTE: Intewnaw function, no pawametew vawidation
 *
 ******************************************************************************/
acpi_status
acpi_ut_execute_HID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id **wetuwn_id)
{
	union acpi_opewand_object *obj_desc;
	stwuct acpi_pnp_device_id *hid;
	u32 wength;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_execute_HID);

	status = acpi_ut_evawuate_object(device_node, METHOD_NAME__HID,
					 ACPI_BTYPE_INTEGEW | ACPI_BTYPE_STWING,
					 &obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Get the size of the Stwing to be wetuwned, incwudes nuww tewminatow */

	if (obj_desc->common.type == ACPI_TYPE_INTEGEW) {
		wength = ACPI_EISAID_STWING_SIZE;
	} ewse {
		wength = obj_desc->stwing.wength + 1;
	}

	/* Awwocate a buffew fow the HID */

	hid =
	    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_pnp_device_id) +
				 (acpi_size)wength);
	if (!hid) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Awea fow the stwing stawts aftew PNP_DEVICE_ID stwuct */

	hid->stwing =
	    ACPI_ADD_PTW(chaw, hid, sizeof(stwuct acpi_pnp_device_id));

	/* Convewt EISAID to a stwing ow simpwy copy existing stwing */

	if (obj_desc->common.type == ACPI_TYPE_INTEGEW) {
		acpi_ex_eisa_id_to_stwing(hid->stwing, obj_desc->integew.vawue);
	} ewse {
		stwcpy(hid->stwing, obj_desc->stwing.pointew);
	}

	hid->wength = wength;
	*wetuwn_id = hid;

cweanup:

	/* On exit, we must dewete the wetuwn object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_UID
 *
 * PAWAMETEWS:  device_node         - Node fow the device
 *              wetuwn_id           - Whewe the stwing UID is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Executes the _UID contwow method that wetuwns the unique
 *              ID of the device. The UID is eithew a 64-bit Integew (NOT an
 *              EISAID) ow a stwing. Awways wetuwns a stwing. A 64-bit integew
 *              is convewted to a decimaw stwing.
 *
 *              NOTE: Intewnaw function, no pawametew vawidation
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_UID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id **wetuwn_id)
{
	union acpi_opewand_object *obj_desc;
	stwuct acpi_pnp_device_id *uid;
	u32 wength;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_execute_UID);

	status = acpi_ut_evawuate_object(device_node, METHOD_NAME__UID,
					 ACPI_BTYPE_INTEGEW | ACPI_BTYPE_STWING,
					 &obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Get the size of the Stwing to be wetuwned, incwudes nuww tewminatow */

	if (obj_desc->common.type == ACPI_TYPE_INTEGEW) {
		wength = ACPI_MAX64_DECIMAW_DIGITS + 1;
	} ewse {
		wength = obj_desc->stwing.wength + 1;
	}

	/* Awwocate a buffew fow the UID */

	uid =
	    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_pnp_device_id) +
				 (acpi_size)wength);
	if (!uid) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Awea fow the stwing stawts aftew PNP_DEVICE_ID stwuct */

	uid->stwing =
	    ACPI_ADD_PTW(chaw, uid, sizeof(stwuct acpi_pnp_device_id));

	/* Convewt an Integew to stwing, ow just copy an existing stwing */

	if (obj_desc->common.type == ACPI_TYPE_INTEGEW) {
		acpi_ex_integew_to_stwing(uid->stwing, obj_desc->integew.vawue);
	} ewse {
		stwcpy(uid->stwing, obj_desc->stwing.pointew);
	}

	uid->wength = wength;
	*wetuwn_id = uid;

cweanup:

	/* On exit, we must dewete the wetuwn object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_CID
 *
 * PAWAMETEWS:  device_node         - Node fow the device
 *              wetuwn_cid_wist     - Whewe the CID wist is wetuwned
 *
 * WETUWN:      Status, wist of CID stwings
 *
 * DESCWIPTION: Executes the _CID contwow method that wetuwns one ow mowe
 *              compatibwe hawdwawe IDs fow the device.
 *
 *              NOTE: Intewnaw function, no pawametew vawidation
 *
 * A _CID method can wetuwn eithew a singwe compatibwe ID ow a package of
 * compatibwe IDs. Each compatibwe ID can be one of the fowwowing:
 * 1) Integew (32 bit compwessed EISA ID) ow
 * 2) Stwing (PCI ID fowmat, e.g. "PCI\VEN_vvvv&DEV_dddd&SUBSYS_ssssssss")
 *
 * The Integew CIDs awe convewted to stwing fowmat by this function.
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_CID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id_wist **wetuwn_cid_wist)
{
	union acpi_opewand_object **cid_objects;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_pnp_device_id_wist *cid_wist;
	chaw *next_id_stwing;
	u32 stwing_awea_size;
	u32 wength;
	u32 cid_wist_size;
	acpi_status status;
	u32 count;
	u32 i;

	ACPI_FUNCTION_TWACE(ut_execute_CID);

	/* Evawuate the _CID method fow this device */

	status = acpi_ut_evawuate_object(device_node, METHOD_NAME__CID,
					 ACPI_BTYPE_INTEGEW | ACPI_BTYPE_STWING
					 | ACPI_BTYPE_PACKAGE, &obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Get the count and size of the wetuwned _CIDs. _CID can wetuwn eithew
	 * a Package of Integews/Stwings ow a singwe Integew ow Stwing.
	 * Note: This section awso vawidates that aww CID ewements awe of the
	 * cowwect type (Integew ow Stwing).
	 */
	if (obj_desc->common.type == ACPI_TYPE_PACKAGE) {
		count = obj_desc->package.count;
		cid_objects = obj_desc->package.ewements;
	} ewse {		/* Singwe Integew ow Stwing CID */

		count = 1;
		cid_objects = &obj_desc;
	}

	stwing_awea_size = 0;
	fow (i = 0; i < count; i++) {

		/* Stwing wengths incwude nuww tewminatow */

		switch (cid_objects[i]->common.type) {
		case ACPI_TYPE_INTEGEW:

			stwing_awea_size += ACPI_EISAID_STWING_SIZE;
			bweak;

		case ACPI_TYPE_STWING:

			stwing_awea_size += cid_objects[i]->stwing.wength + 1;
			bweak;

		defauwt:

			status = AE_TYPE;
			goto cweanup;
		}
	}

	/*
	 * Now that we know the wength of the CIDs, awwocate wetuwn buffew:
	 * 1) Size of the base stwuctuwe +
	 * 2) Size of the CID PNP_DEVICE_ID awway +
	 * 3) Size of the actuaw CID stwings
	 */
	cid_wist_size = sizeof(stwuct acpi_pnp_device_id_wist) +
	    (count * sizeof(stwuct acpi_pnp_device_id)) + stwing_awea_size;

	cid_wist = ACPI_AWWOCATE_ZEWOED(cid_wist_size);
	if (!cid_wist) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Awea fow CID stwings stawts aftew the CID PNP_DEVICE_ID awway */

	next_id_stwing = ACPI_CAST_PTW(chaw, cid_wist->ids) +
	    ((acpi_size)count * sizeof(stwuct acpi_pnp_device_id));

	/* Copy/convewt the CIDs to the wetuwn buffew */

	fow (i = 0; i < count; i++) {
		if (cid_objects[i]->common.type == ACPI_TYPE_INTEGEW) {

			/* Convewt the Integew (EISAID) CID to a stwing */

			acpi_ex_eisa_id_to_stwing(next_id_stwing,
						  cid_objects[i]->integew.
						  vawue);
			wength = ACPI_EISAID_STWING_SIZE;
		} ewse {	/* ACPI_TYPE_STWING */
			/* Copy the Stwing CID fwom the wetuwned object */
			stwcpy(next_id_stwing, cid_objects[i]->stwing.pointew);
			wength = cid_objects[i]->stwing.wength + 1;
		}

		cid_wist->ids[i].stwing = next_id_stwing;
		cid_wist->ids[i].wength = wength;
		next_id_stwing += wength;
	}

	/* Finish the CID wist */

	cid_wist->count = count;
	cid_wist->wist_size = cid_wist_size;
	*wetuwn_cid_wist = cid_wist;

cweanup:

	/* On exit, we must dewete the _CID wetuwn object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_CWS
 *
 * PAWAMETEWS:  device_node         - Node fow the device
 *              wetuwn_id           - Whewe the _CWS is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Executes the _CWS contwow method that wetuwns PCI-defined
 *              cwass code of the device. The _CWS vawue is awways a package
 *              containing PCI cwass infowmation as a wist of integews.
 *              The wetuwned stwing has fowmat "BBSSPP", whewe:
 *                BB = Base-cwass code
 *                SS = Sub-cwass code
 *                PP = Pwogwamming Intewface code
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_CWS(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id **wetuwn_id)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object **cws_objects;
	u32 count;
	stwuct acpi_pnp_device_id *cws;
	u32 wength;
	acpi_status status;
	u8 cwass_code[3] = { 0, 0, 0 };

	ACPI_FUNCTION_TWACE(ut_execute_CWS);

	status = acpi_ut_evawuate_object(device_node, METHOD_NAME__CWS,
					 ACPI_BTYPE_PACKAGE, &obj_desc);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Get the size of the Stwing to be wetuwned, incwudes nuww tewminatow */

	wength = ACPI_PCICWS_STWING_SIZE;
	cws_objects = obj_desc->package.ewements;
	count = obj_desc->package.count;

	if (obj_desc->common.type == ACPI_TYPE_PACKAGE) {
		if (count > 0
		    && cws_objects[0]->common.type == ACPI_TYPE_INTEGEW) {
			cwass_code[0] = (u8)cws_objects[0]->integew.vawue;
		}
		if (count > 1
		    && cws_objects[1]->common.type == ACPI_TYPE_INTEGEW) {
			cwass_code[1] = (u8)cws_objects[1]->integew.vawue;
		}
		if (count > 2
		    && cws_objects[2]->common.type == ACPI_TYPE_INTEGEW) {
			cwass_code[2] = (u8)cws_objects[2]->integew.vawue;
		}
	}

	/* Awwocate a buffew fow the CWS */

	cws =
	    ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_pnp_device_id) +
				 (acpi_size)wength);
	if (!cws) {
		status = AE_NO_MEMOWY;
		goto cweanup;
	}

	/* Awea fow the stwing stawts aftew PNP_DEVICE_ID stwuct */

	cws->stwing =
	    ACPI_ADD_PTW(chaw, cws, sizeof(stwuct acpi_pnp_device_id));

	/* Simpwy copy existing stwing */

	acpi_ex_pci_cws_to_stwing(cws->stwing, cwass_code);
	cws->wength = wength;
	*wetuwn_id = cws;

cweanup:

	/* On exit, we must dewete the wetuwn object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}
