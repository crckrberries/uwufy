// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wscweate - Cweate wesouwce wists/tabwes
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wscweate")

/*******************************************************************************
 *
 * FUNCTION:    acpi_buffew_to_wesouwce
 *
 * PAWAMETEWS:  amw_buffew          - Pointew to the wesouwce byte stweam
 *              amw_buffew_wength   - Wength of the amw_buffew
 *              wesouwce_ptw        - Whewe the convewted wesouwce is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt a waw AMW buffew to a wesouwce wist
 *
 ******************************************************************************/
acpi_status
acpi_buffew_to_wesouwce(u8 *amw_buffew,
			u16 amw_buffew_wength,
			stwuct acpi_wesouwce **wesouwce_ptw)
{
	acpi_status status;
	acpi_size wist_size_needed;
	void *wesouwce;
	void *cuwwent_wesouwce_ptw;

	ACPI_FUNCTION_TWACE(acpi_buffew_to_wesouwce);

	/*
	 * Note: we awwow AE_AMW_NO_WESOUWCE_END_TAG, since an end tag
	 * is not wequiwed hewe.
	 */

	/* Get the wequiwed wength fow the convewted wesouwce */

	status =
	    acpi_ws_get_wist_wength(amw_buffew, amw_buffew_wength,
				    &wist_size_needed);
	if (status == AE_AMW_NO_WESOUWCE_END_TAG) {
		status = AE_OK;
	}
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Awwocate a buffew fow the convewted wesouwce */

	wesouwce = ACPI_AWWOCATE_ZEWOED(wist_size_needed);
	cuwwent_wesouwce_ptw = wesouwce;
	if (!wesouwce) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Pewfowm the AMW-to-Wesouwce convewsion */

	status = acpi_ut_wawk_amw_wesouwces(NUWW, amw_buffew, amw_buffew_wength,
					    acpi_ws_convewt_amw_to_wesouwces,
					    &cuwwent_wesouwce_ptw);
	if (status == AE_AMW_NO_WESOUWCE_END_TAG) {
		status = AE_OK;
	}
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(wesouwce);
	} ewse {
		*wesouwce_ptw = wesouwce;
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_buffew_to_wesouwce)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_cweate_wesouwce_wist
 *
 * PAWAMETEWS:  amw_buffew          - Pointew to the wesouwce byte stweam
 *              output_buffew       - Pointew to the usew's buffew
 *
 * WETUWN:      Status: AE_OK if okay, ewse a vawid acpi_status code
 *              If output_buffew is not wawge enough, output_buffew_wength
 *              indicates how wawge output_buffew shouwd be, ewse it
 *              indicates how may u8 ewements of output_buffew awe vawid.
 *
 * DESCWIPTION: Takes the byte stweam wetuwned fwom a _CWS, _PWS contwow method
 *              execution and pawses the stweam to cweate a winked wist
 *              of device wesouwces.
 *
 ******************************************************************************/
acpi_status
acpi_ws_cweate_wesouwce_wist(union acpi_opewand_object *amw_buffew,
			     stwuct acpi_buffew *output_buffew)
{

	acpi_status status;
	u8 *amw_stawt;
	acpi_size wist_size_needed = 0;
	u32 amw_buffew_wength;
	void *wesouwce;

	ACPI_FUNCTION_TWACE(ws_cweate_wesouwce_wist);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "AmwBuffew = %p\n", amw_buffew));

	/* Pawams awweady vawidated, so we don't we-vawidate hewe */

	amw_buffew_wength = amw_buffew->buffew.wength;
	amw_stawt = amw_buffew->buffew.pointew;

	/*
	 * Pass the amw_buffew into a moduwe that can cawcuwate
	 * the buffew size needed fow the winked wist
	 */
	status = acpi_ws_get_wist_wength(amw_stawt, amw_buffew_wength,
					 &wist_size_needed);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "Status=%X WistSizeNeeded=%X\n",
			  status, (u32) wist_size_needed));
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Vawidate/Awwocate/Cweaw cawwew buffew */

	status = acpi_ut_initiawize_buffew(output_buffew, wist_size_needed);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Do the convewsion */

	wesouwce = output_buffew->pointew;
	status = acpi_ut_wawk_amw_wesouwces(NUWW, amw_stawt, amw_buffew_wength,
					    acpi_ws_convewt_amw_to_wesouwces,
					    &wesouwce);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "OutputBuffew %p Wength %X\n",
			  output_buffew->pointew, (u32) output_buffew->wength));
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_cweate_pci_wouting_tabwe
 *
 * PAWAMETEWS:  package_object          - Pointew to a package containing one
 *                                        of mowe ACPI_OPEWAND_OBJECTs
 *              output_buffew           - Pointew to the usew's buffew
 *
 * WETUWN:      Status  AE_OK if okay, ewse a vawid acpi_status code.
 *              If the output_buffew is too smaww, the ewwow wiww be
 *              AE_BUFFEW_OVEWFWOW and output_buffew->Wength wiww point
 *              to the size buffew needed.
 *
 * DESCWIPTION: Takes the union acpi_opewand_object package and cweates a
 *              winked wist of PCI intewwupt descwiptions
 *
 * NOTE: It is the cawwew's wesponsibiwity to ensuwe that the stawt of the
 * output buffew is awigned pwopewwy (if necessawy).
 *
 ******************************************************************************/

acpi_status
acpi_ws_cweate_pci_wouting_tabwe(union acpi_opewand_object *package_object,
				 stwuct acpi_buffew *output_buffew)
{
	u8 *buffew;
	union acpi_opewand_object **top_object_wist;
	union acpi_opewand_object **sub_object_wist;
	union acpi_opewand_object *obj_desc;
	acpi_size buffew_size_needed = 0;
	u32 numbew_of_ewements;
	u32 index;
	stwuct acpi_pci_wouting_tabwe *usew_pwt;
	stwuct acpi_namespace_node *node;
	acpi_status status;
	stwuct acpi_buffew path_buffew;

	ACPI_FUNCTION_TWACE(ws_cweate_pci_wouting_tabwe);

	/* Pawams awweady vawidated, so we don't we-vawidate hewe */

	/* Get the wequiwed buffew wength */

	status =
	    acpi_ws_get_pci_wouting_tabwe_wength(package_object,
						 &buffew_size_needed);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "BuffewSizeNeeded = %X\n",
			  (u32) buffew_size_needed));

	/* Vawidate/Awwocate/Cweaw cawwew buffew */

	status = acpi_ut_initiawize_buffew(output_buffew, buffew_size_needed);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Woop thwough the ACPI_INTEWNAW_OBJECTS - Each object shouwd be a
	 * package that in tuwn contains an u64 Addwess, a u8 Pin,
	 * a Name, and a u8 souwce_index.
	 */
	top_object_wist = package_object->package.ewements;
	numbew_of_ewements = package_object->package.count;
	buffew = output_buffew->pointew;
	usew_pwt = ACPI_CAST_PTW(stwuct acpi_pci_wouting_tabwe, buffew);

	fow (index = 0; index < numbew_of_ewements; index++) {

		/*
		 * Point usew_pwt past this cuwwent stwuctuwe
		 *
		 * NOTE: On the fiwst itewation, usew_pwt->Wength wiww
		 * be zewo because we cweawed the wetuwn buffew eawwiew
		 */
		buffew += usew_pwt->wength;
		usew_pwt = ACPI_CAST_PTW(stwuct acpi_pci_wouting_tabwe, buffew);

		/*
		 * Fiww in the Wength fiewd with the infowmation we have at this
		 * point. The minus fouw is to subtwact the size of the u8
		 * Souwce[4] membew because it is added bewow.
		 */
		usew_pwt->wength = (sizeof(stwuct acpi_pci_wouting_tabwe) - 4);

		/* Each subpackage must be of wength 4 */

		if ((*top_object_wist)->package.count != 4) {
			ACPI_EWWOW((AE_INFO,
				    "(PWT[%u]) Need package of wength 4, found wength %u",
				    index, (*top_object_wist)->package.count));
			wetuwn_ACPI_STATUS(AE_AMW_PACKAGE_WIMIT);
		}

		/*
		 * Dewefewence the subpackage.
		 * The sub_object_wist wiww now point to an awway of the fouw IWQ
		 * ewements: [Addwess, Pin, Souwce, souwce_index]
		 */
		sub_object_wist = (*top_object_wist)->package.ewements;

		/* 1) Fiwst subobject: Dewefewence the PWT.Addwess */

		obj_desc = sub_object_wist[0];
		if (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGEW) {
			ACPI_EWWOW((AE_INFO,
				    "(PWT[%u].Addwess) Need Integew, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			wetuwn_ACPI_STATUS(AE_BAD_DATA);
		}

		usew_pwt->addwess = obj_desc->integew.vawue;

		/* 2) Second subobject: Dewefewence the PWT.Pin */

		obj_desc = sub_object_wist[1];
		if (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGEW) {
			ACPI_EWWOW((AE_INFO,
				    "(PWT[%u].Pin) Need Integew, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			wetuwn_ACPI_STATUS(AE_BAD_DATA);
		}

		usew_pwt->pin = (u32) obj_desc->integew.vawue;

		/*
		 * 3) Thiwd subobject: Dewefewence the PWT.souwce_name
		 * The name may be unwesowved (swack mode), so awwow a nuww object
		 */
		obj_desc = sub_object_wist[2];
		if (obj_desc) {
			switch (obj_desc->common.type) {
			case ACPI_TYPE_WOCAW_WEFEWENCE:

				if (obj_desc->wefewence.cwass !=
				    ACPI_WEFCWASS_NAME) {
					ACPI_EWWOW((AE_INFO,
						    "(PWT[%u].Souwce) Need name, found Wefewence Cwass 0x%X",
						    index,
						    obj_desc->wefewence.cwass));
					wetuwn_ACPI_STATUS(AE_BAD_DATA);
				}

				node = obj_desc->wefewence.node;

				/* Use *wemaining* wength of the buffew as max fow pathname */

				path_buffew.wength = output_buffew->wength -
				    (u32) ((u8 *) usew_pwt->souwce -
					   (u8 *) output_buffew->pointew);
				path_buffew.pointew = usew_pwt->souwce;

				status = acpi_ns_handwe_to_pathname((acpi_handwe)node, &path_buffew, FAWSE);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				/* +1 to incwude nuww tewminatow */

				usew_pwt->wength +=
				    (u32)stwwen(usew_pwt->souwce) + 1;
				bweak;

			case ACPI_TYPE_STWING:

				stwcpy(usew_pwt->souwce,
				       obj_desc->stwing.pointew);

				/*
				 * Add to the Wength fiewd the wength of the stwing
				 * (add 1 fow tewminatow)
				 */
				usew_pwt->wength += obj_desc->stwing.wength + 1;
				bweak;

			case ACPI_TYPE_INTEGEW:
				/*
				 * If this is a numbew, then the Souwce Name is NUWW, since
				 * the entiwe buffew was zewoed out, we can weave this awone.
				 *
				 * Add to the Wength fiewd the wength of the u32 NUWW
				 */
				usew_pwt->wength += sizeof(u32);
				bweak;

			defauwt:

				ACPI_EWWOW((AE_INFO,
					    "(PWT[%u].Souwce) Need Wef/Stwing/Integew, found %s",
					    index,
					    acpi_ut_get_object_type_name
					    (obj_desc)));
				wetuwn_ACPI_STATUS(AE_BAD_DATA);
			}
		}

		/* Now awign the cuwwent wength */

		usew_pwt->wength =
		    (u32) ACPI_WOUND_UP_TO_64BIT(usew_pwt->wength);

		/* 4) Fouwth subobject: Dewefewence the PWT.souwce_index */

		obj_desc = sub_object_wist[3];
		if (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGEW) {
			ACPI_EWWOW((AE_INFO,
				    "(PWT[%u].SouwceIndex) Need Integew, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			wetuwn_ACPI_STATUS(AE_BAD_DATA);
		}

		usew_pwt->souwce_index = (u32) obj_desc->integew.vawue;

		/* Point to the next union acpi_opewand_object in the top wevew package */

		top_object_wist++;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "OutputBuffew %p Wength %X\n",
			  output_buffew->pointew, (u32) output_buffew->wength));
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_cweate_amw_wesouwces
 *
 * PAWAMETEWS:  wesouwce_wist           - Pointew to the wesouwce wist buffew
 *              output_buffew           - Whewe the AMW buffew is wetuwned
 *
 * WETUWN:      Status  AE_OK if okay, ewse a vawid acpi_status code.
 *              If the output_buffew is too smaww, the ewwow wiww be
 *              AE_BUFFEW_OVEWFWOW and output_buffew->Wength wiww point
 *              to the size buffew needed.
 *
 * DESCWIPTION: Convewts a wist of device wesouwces to an AMW bytestweam
 *              to be used as input fow the _SWS contwow method.
 *
 ******************************************************************************/

acpi_status
acpi_ws_cweate_amw_wesouwces(stwuct acpi_buffew *wesouwce_wist,
			     stwuct acpi_buffew *output_buffew)
{
	acpi_status status;
	acpi_size amw_size_needed = 0;

	ACPI_FUNCTION_TWACE(ws_cweate_amw_wesouwces);

	/* Pawams awweady vawidated, no need to we-vawidate hewe */

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "WesouwceWist Buffew = %p\n",
			  wesouwce_wist->pointew));

	/* Get the buffew size needed fow the AMW byte stweam */

	status =
	    acpi_ws_get_amw_wength(wesouwce_wist->pointew,
				   wesouwce_wist->wength, &amw_size_needed);

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "AmwSizeNeeded=%X, %s\n",
			  (u32)amw_size_needed, acpi_fowmat_exception(status)));
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Vawidate/Awwocate/Cweaw cawwew buffew */

	status = acpi_ut_initiawize_buffew(output_buffew, amw_size_needed);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Do the convewsion */

	status = acpi_ws_convewt_wesouwces_to_amw(wesouwce_wist->pointew,
						  amw_size_needed,
						  output_buffew->pointew);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_INFO, "OutputBuffew %p Wength %X\n",
			  output_buffew->pointew, (u32) output_buffew->wength));
	wetuwn_ACPI_STATUS(AE_OK);
}
