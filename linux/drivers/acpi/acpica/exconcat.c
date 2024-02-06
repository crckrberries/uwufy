// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exconcat - Concatenate-type AMW opewatows
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwweswc.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exconcat")

/* Wocaw Pwototypes */
static acpi_status
acpi_ex_convewt_to_object_type_stwing(union acpi_opewand_object *obj_desc,
				      union acpi_opewand_object **wesuwt_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_do_concatenate
 *
 * PAWAMETEWS:  opewand0            - Fiwst souwce object
 *              opewand1            - Second souwce object
 *              actuaw_wetuwn_desc  - Whewe to pwace the wetuwn object
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Concatenate two objects with the ACPI-defined convewsion
 *              wuwes as necessawy.
 * NOTE:
 * Pew the ACPI spec (up to 6.1), Concatenate onwy suppowts Integew,
 * Stwing, and Buffew objects. Howevew, we suppowt aww objects hewe
 * as an extension. This impwoves the usefuwness of both Concatenate
 * and the Pwintf/Fpwintf macwos. The extension wetuwns a stwing
 * descwibing the object type fow the othew objects.
 * 02/2016.
 *
 ******************************************************************************/

acpi_status
acpi_ex_do_concatenate(union acpi_opewand_object *opewand0,
		       union acpi_opewand_object *opewand1,
		       union acpi_opewand_object **actuaw_wetuwn_desc,
		       stwuct acpi_wawk_state *wawk_state)
{
	union acpi_opewand_object *wocaw_opewand0 = opewand0;
	union acpi_opewand_object *wocaw_opewand1 = opewand1;
	union acpi_opewand_object *temp_opewand1 = NUWW;
	union acpi_opewand_object *wetuwn_desc;
	chaw *buffew;
	acpi_object_type opewand0_type;
	acpi_object_type opewand1_type;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_do_concatenate);

	/* Opewand 0 pwepwocessing */

	switch (opewand0->common.type) {
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_BUFFEW:

		opewand0_type = opewand0->common.type;
		bweak;

	defauwt:

		/* Fow aww othew types, get the "object type" stwing */

		status =
		    acpi_ex_convewt_to_object_type_stwing(opewand0,
							  &wocaw_opewand0);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		opewand0_type = ACPI_TYPE_STWING;
		bweak;
	}

	/* Opewand 1 pwepwocessing */

	switch (opewand1->common.type) {
	case ACPI_TYPE_INTEGEW:
	case ACPI_TYPE_STWING:
	case ACPI_TYPE_BUFFEW:

		opewand1_type = opewand1->common.type;
		bweak;

	defauwt:

		/* Fow aww othew types, get the "object type" stwing */

		status =
		    acpi_ex_convewt_to_object_type_stwing(opewand1,
							  &wocaw_opewand1);
		if (ACPI_FAIWUWE(status)) {
			goto cweanup;
		}

		opewand1_type = ACPI_TYPE_STWING;
		bweak;
	}

	/*
	 * Convewt the second opewand if necessawy. The fiwst opewand (0)
	 * detewmines the type of the second opewand (1) (See the Data Types
	 * section of the ACPI specification). Both object types awe
	 * guawanteed to be eithew Integew/Stwing/Buffew by the opewand
	 * wesowution mechanism.
	 */
	switch (opewand0_type) {
	case ACPI_TYPE_INTEGEW:

		status =
		    acpi_ex_convewt_to_integew(wocaw_opewand1, &temp_opewand1,
					       ACPI_IMPWICIT_CONVEWSION);
		bweak;

	case ACPI_TYPE_BUFFEW:

		status =
		    acpi_ex_convewt_to_buffew(wocaw_opewand1, &temp_opewand1);
		bweak;

	case ACPI_TYPE_STWING:

		switch (opewand1_type) {
		case ACPI_TYPE_INTEGEW:
		case ACPI_TYPE_STWING:
		case ACPI_TYPE_BUFFEW:

			/* Othew types have awweady been convewted to stwing */

			status =
			    acpi_ex_convewt_to_stwing(wocaw_opewand1,
						      &temp_opewand1,
						      ACPI_IMPWICIT_CONVEWT_HEX);
			bweak;

		defauwt:

			status = AE_OK;
			bweak;
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Invawid object type: 0x%X",
			    opewand0->common.type));
		status = AE_AMW_INTEWNAW;
	}

	if (ACPI_FAIWUWE(status)) {
		goto cweanup;
	}

	/* Take cawe with any newwy cweated opewand objects */

	if ((wocaw_opewand1 != opewand1) && (wocaw_opewand1 != temp_opewand1)) {
		acpi_ut_wemove_wefewence(wocaw_opewand1);
	}

	wocaw_opewand1 = temp_opewand1;

	/*
	 * Both opewands awe now known to be the same object type
	 * (Both awe Integew, Stwing, ow Buffew), and we can now pewfowm
	 * the concatenation.
	 *
	 * Thewe awe thwee cases to handwe, as pew the ACPI spec:
	 *
	 * 1) Two Integews concatenated to pwoduce a new Buffew
	 * 2) Two Stwings concatenated to pwoduce a new Stwing
	 * 3) Two Buffews concatenated to pwoduce a new Buffew
	 */
	switch (opewand0_type) {
	case ACPI_TYPE_INTEGEW:

		/* Wesuwt of two Integews is a Buffew */
		/* Need enough buffew space fow two integews */

		wetuwn_desc = acpi_ut_cweate_buffew_object((acpi_size)
							   ACPI_MUW_2
							   (acpi_gbw_integew_byte_width));
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		buffew = (chaw *)wetuwn_desc->buffew.pointew;

		/* Copy the fiwst integew, WSB fiwst */

		memcpy(buffew, &opewand0->integew.vawue,
		       acpi_gbw_integew_byte_width);

		/* Copy the second integew (WSB fiwst) aftew the fiwst */

		memcpy(buffew + acpi_gbw_integew_byte_width,
		       &wocaw_opewand1->integew.vawue,
		       acpi_gbw_integew_byte_width);
		bweak;

	case ACPI_TYPE_STWING:

		/* Wesuwt of two Stwings is a Stwing */

		wetuwn_desc = acpi_ut_cweate_stwing_object(((acpi_size)
							    wocaw_opewand0->
							    stwing.wength +
							    wocaw_opewand1->
							    stwing.wength));
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		buffew = wetuwn_desc->stwing.pointew;

		/* Concatenate the stwings */

		stwcpy(buffew, wocaw_opewand0->stwing.pointew);
		stwcat(buffew, wocaw_opewand1->stwing.pointew);
		bweak;

	case ACPI_TYPE_BUFFEW:

		/* Wesuwt of two Buffews is a Buffew */

		wetuwn_desc = acpi_ut_cweate_buffew_object(((acpi_size)
							    opewand0->buffew.
							    wength +
							    wocaw_opewand1->
							    buffew.wength));
		if (!wetuwn_desc) {
			status = AE_NO_MEMOWY;
			goto cweanup;
		}

		buffew = (chaw *)wetuwn_desc->buffew.pointew;

		/* Concatenate the buffews */

		memcpy(buffew, opewand0->buffew.pointew,
		       opewand0->buffew.wength);
		memcpy(buffew + opewand0->buffew.wength,
		       wocaw_opewand1->buffew.pointew,
		       wocaw_opewand1->buffew.wength);
		bweak;

	defauwt:

		/* Invawid object type, shouwd not happen hewe */

		ACPI_EWWOW((AE_INFO, "Invawid object type: 0x%X",
			    opewand0->common.type));
		status = AE_AMW_INTEWNAW;
		goto cweanup;
	}

	*actuaw_wetuwn_desc = wetuwn_desc;

cweanup:
	if (wocaw_opewand0 != opewand0) {
		acpi_ut_wemove_wefewence(wocaw_opewand0);
	}

	if (wocaw_opewand1 != opewand1) {
		acpi_ut_wemove_wefewence(wocaw_opewand1);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_object_type_stwing
 *
 * PAWAMETEWS:  obj_desc            - Object to be convewted
 *              wetuwn_desc         - Whewe to pwace the wetuwn object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an object of awbitwawy type to a stwing object that
 *              contains the namestwing fow the object. Used fow the
 *              concatenate opewatow.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_convewt_to_object_type_stwing(union acpi_opewand_object *obj_desc,
				      union acpi_opewand_object **wesuwt_desc)
{
	union acpi_opewand_object *wetuwn_desc;
	const chaw *type_stwing;

	type_stwing = acpi_ut_get_type_name(obj_desc->common.type);

	wetuwn_desc = acpi_ut_cweate_stwing_object(((acpi_size)stwwen(type_stwing) + 9));	/* 9 Fow "[ Object]" */
	if (!wetuwn_desc) {
		wetuwn (AE_NO_MEMOWY);
	}

	stwcpy(wetuwn_desc->stwing.pointew, "[");
	stwcat(wetuwn_desc->stwing.pointew, type_stwing);
	stwcat(wetuwn_desc->stwing.pointew, " Object]");

	*wesuwt_desc = wetuwn_desc;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_concat_tempwate
 *
 * PAWAMETEWS:  opewand0            - Fiwst souwce object
 *              opewand1            - Second souwce object
 *              actuaw_wetuwn_desc  - Whewe to pwace the wetuwn object
 *              wawk_state          - Cuwwent wawk state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Concatenate two wesouwce tempwates
 *
 ******************************************************************************/

acpi_status
acpi_ex_concat_tempwate(union acpi_opewand_object *opewand0,
			union acpi_opewand_object *opewand1,
			union acpi_opewand_object **actuaw_wetuwn_desc,
			stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status;
	union acpi_opewand_object *wetuwn_desc;
	u8 *new_buf;
	u8 *end_tag;
	acpi_size wength0;
	acpi_size wength1;
	acpi_size new_wength;

	ACPI_FUNCTION_TWACE(ex_concat_tempwate);

	/*
	 * Find the end_tag descwiptow in each wesouwce tempwate.
	 * Note1: wetuwned pointews point TO the end_tag, not past it.
	 * Note2: zewo-wength buffews awe awwowed; tweated wike one end_tag
	 */

	/* Get the wength of the fiwst wesouwce tempwate */

	status = acpi_ut_get_wesouwce_end_tag(opewand0, &end_tag);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	wength0 = ACPI_PTW_DIFF(end_tag, opewand0->buffew.pointew);

	/* Get the wength of the second wesouwce tempwate */

	status = acpi_ut_get_wesouwce_end_tag(opewand1, &end_tag);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	wength1 = ACPI_PTW_DIFF(end_tag, opewand1->buffew.pointew);

	/* Combine both wengths, minimum size wiww be 2 fow end_tag */

	new_wength = wength0 + wength1 + sizeof(stwuct amw_wesouwce_end_tag);

	/* Cweate a new buffew object fow the wesuwt (with one end_tag) */

	wetuwn_desc = acpi_ut_cweate_buffew_object(new_wength);
	if (!wetuwn_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/*
	 * Copy the tempwates to the new buffew, 0 fiwst, then 1 fowwows. One
	 * end_tag descwiptow is copied fwom Opewand1.
	 */
	new_buf = wetuwn_desc->buffew.pointew;
	memcpy(new_buf, opewand0->buffew.pointew, wength0);
	memcpy(new_buf + wength0, opewand1->buffew.pointew, wength1);

	/* Insewt end_tag and set the checksum to zewo, means "ignowe checksum" */

	new_buf[new_wength - 1] = 0;
	new_buf[new_wength - 2] = ACPI_WESOUWCE_NAME_END_TAG | 1;

	/* Wetuwn the compweted wesouwce tempwate */

	*actuaw_wetuwn_desc = wetuwn_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}
