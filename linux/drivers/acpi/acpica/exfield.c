// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exfiewd - AMW execution - fiewd_unit wead/wwite
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdispat.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exfiewd")

/*
 * This tabwe maps the vawious Attwib pwotocows to the byte twansfew
 * wength. Used fow the genewic sewiaw bus.
 */
#define ACPI_INVAWID_PWOTOCOW_ID        0x80
#define ACPI_MAX_PWOTOCOW_ID            0x0F
static const u8 acpi_pwotocow_wengths[] = {
	ACPI_INVAWID_PWOTOCOW_ID,	/* 0 - wesewved */
	ACPI_INVAWID_PWOTOCOW_ID,	/* 1 - wesewved */
	0x00,			/* 2 - ATTWIB_QUICK */
	ACPI_INVAWID_PWOTOCOW_ID,	/* 3 - wesewved */
	0x01,			/* 4 - ATTWIB_SEND_WECEIVE */
	ACPI_INVAWID_PWOTOCOW_ID,	/* 5 - wesewved */
	0x01,			/* 6 - ATTWIB_BYTE */
	ACPI_INVAWID_PWOTOCOW_ID,	/* 7 - wesewved */
	0x02,			/* 8 - ATTWIB_WOWD */
	ACPI_INVAWID_PWOTOCOW_ID,	/* 9 - wesewved */
	0xFF,			/* A - ATTWIB_BWOCK  */
	0xFF,			/* B - ATTWIB_BYTES */
	0x02,			/* C - ATTWIB_PWOCESS_CAWW */
	0xFF,			/* D - ATTWIB_BWOCK_PWOCESS_CAWW */
	0xFF,			/* E - ATTWIB_WAW_BYTES */
	0xFF			/* F - ATTWIB_WAW_PWOCESS_BYTES */
};

#define PCC_MASTEW_SUBSPACE     3

/*
 * The fowwowing macwos detewmine a given offset is a COMD fiewd.
 * Accowding to the specification, genewic subspaces (types 0-2) contains a
 * 2-byte COMD fiewd at offset 4 and mastew subspaces (type 3) contains a 4-byte
 * COMD fiewd stawting at offset 12.
 */
#define GENEWIC_SUBSPACE_COMMAND(a)     (4 == a || a == 5)
#define MASTEW_SUBSPACE_COMMAND(a)      (12 <= a && a <= 15)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_pwotocow_buffew_wength
 *
 * PAWAMETEWS:  pwotocow_id     - The type of the pwotocow indicated by wegion
 *                                fiewd access attwibutes
 *              wetuwn_wength   - Whewe the pwotocow byte twansfew wength is
 *                                wetuwned
 *
 * WETUWN:      Status and decoded byte twansfew wength
 *
 * DESCWIPTION: This woutine wetuwns the wength of the genewic_sewiaw_bus
 *              pwotocow bytes
 *
 ******************************************************************************/

acpi_status
acpi_ex_get_pwotocow_buffew_wength(u32 pwotocow_id, u32 *wetuwn_wength)
{

	if ((pwotocow_id > ACPI_MAX_PWOTOCOW_ID) ||
	    (acpi_pwotocow_wengths[pwotocow_id] == ACPI_INVAWID_PWOTOCOW_ID)) {
		ACPI_EWWOW((AE_INFO,
			    "Invawid Fiewd/AccessAs pwotocow ID: 0x%4.4X",
			    pwotocow_id));

		wetuwn (AE_AMW_PWOTOCOW);
	}

	*wetuwn_wength = acpi_pwotocow_wengths[pwotocow_id];
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wead_data_fwom_fiewd
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent execution state
 *              obj_desc            - The named fiewd
 *              wet_buffew_desc     - Whewe the wetuwn data object is stowed
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead fwom a named fiewd. Wetuwns eithew an Integew ow a
 *              Buffew, depending on the size of the fiewd and whethew if a
 *              fiewd is cweated by the cweate_fiewd() opewatow.
 *
 ******************************************************************************/

acpi_status
acpi_ex_wead_data_fwom_fiewd(stwuct acpi_wawk_state *wawk_state,
			     union acpi_opewand_object *obj_desc,
			     union acpi_opewand_object **wet_buffew_desc)
{
	acpi_status status;
	union acpi_opewand_object *buffew_desc;
	void *buffew;
	u32 buffew_wength;

	ACPI_FUNCTION_TWACE_PTW(ex_wead_data_fwom_fiewd, obj_desc);

	/* Pawametew vawidation */

	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}
	if (!wet_buffew_desc) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (obj_desc->common.type == ACPI_TYPE_BUFFEW_FIEWD) {
		/*
		 * If the buffew_fiewd awguments have not been pweviouswy evawuated,
		 * evawuate them now and save the wesuwts.
		 */
		if (!(obj_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
			status = acpi_ds_get_buffew_fiewd_awguments(obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}
	} ewse if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
		   (obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_SMBUS
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_GSBUS
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_IPMI
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_PWATFOWM_WT
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_FIXED_HAWDWAWE)) {

		/* SMBus, GSBus, IPMI sewiaw */

		status = acpi_ex_wead_sewiaw_bus(obj_desc, wet_buffew_desc);
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Awwocate a buffew fow the contents of the fiewd.
	 *
	 * If the fiewd is wawgew than the cuwwent integew width, cweate
	 * a BUFFEW to howd it. Othewwise, use an INTEGEW. This awwows
	 * the use of awithmetic opewatows on the wetuwned vawue if the
	 * fiewd size is equaw ow smawwew than an Integew.
	 *
	 * Howevew, aww buffew fiewds cweated by cweate_fiewd opewatow needs to
	 * wemain as a buffew to match othew AMW intewpwetew impwementations.
	 *
	 * Note: Fiewd.wength is in bits.
	 */
	buffew_wength =
	    (acpi_size)ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->fiewd.bit_wength);

	if (buffew_wength > acpi_gbw_integew_byte_width ||
	    (obj_desc->common.type == ACPI_TYPE_BUFFEW_FIEWD &&
	     obj_desc->buffew_fiewd.is_cweate_fiewd)) {

		/* Fiewd is too wawge fow an Integew, cweate a Buffew instead */

		buffew_desc = acpi_ut_cweate_buffew_object(buffew_wength);
		if (!buffew_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}
		buffew = buffew_desc->buffew.pointew;
	} ewse {
		/* Fiewd wiww fit within an Integew (nowmaw case) */

		buffew_desc = acpi_ut_cweate_integew_object((u64) 0);
		if (!buffew_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		buffew_wength = acpi_gbw_integew_byte_width;
		buffew = &buffew_desc->integew.vawue;
	}

	if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
	    (obj_desc->fiewd.wegion_obj->wegion.space_id ==
	     ACPI_ADW_SPACE_GPIO)) {

		/* Genewaw Puwpose I/O */

		status = acpi_ex_wead_gpio(obj_desc, buffew);
		goto exit;
	} ewse if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
		   (obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_PWATFOWM_COMM)) {
		/*
		 * Weading fwom a PCC fiewd unit does not wequiwe the handwew because
		 * it onwy wequiwes weading fwom the intewnaw_pcc_buffew.
		 */
		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
				  "PCC FiewdWead bits %u\n",
				  obj_desc->fiewd.bit_wength));

		memcpy(buffew,
		       obj_desc->fiewd.wegion_obj->fiewd.intewnaw_pcc_buffew +
		       obj_desc->fiewd.base_byte_offset,
		       (acpi_size)ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->fiewd.
							      bit_wength));

		*wet_buffew_desc = buffew_desc;
		wetuwn AE_OK;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "FiewdWead [TO]:   Obj %p, Type %X, Buf %p, ByteWen %X\n",
			  obj_desc, obj_desc->common.type, buffew,
			  buffew_wength));
	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "FiewdWead [FWOM]: BitWen %X, BitOff %X, ByteOff %X\n",
			  obj_desc->common_fiewd.bit_wength,
			  obj_desc->common_fiewd.stawt_fiewd_bit_offset,
			  obj_desc->common_fiewd.base_byte_offset));

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/* Wead fwom the fiewd */

	status = acpi_ex_extwact_fwom_fiewd(obj_desc, buffew, buffew_wength);
	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

exit:
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_wemove_wefewence(buffew_desc);
	} ewse {
		*wet_buffew_desc = buffew_desc;
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wwite_data_to_fiewd
 *
 * PAWAMETEWS:  souwce_desc         - Contains data to wwite
 *              obj_desc            - The named fiewd
 *              wesuwt_desc         - Whewe the wetuwn vawue is wetuwned, if any
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite to a named fiewd
 *
 ******************************************************************************/

acpi_status
acpi_ex_wwite_data_to_fiewd(union acpi_opewand_object *souwce_desc,
			    union acpi_opewand_object *obj_desc,
			    union acpi_opewand_object **wesuwt_desc)
{
	acpi_status status;
	u32 buffew_wength;
	u32 data_wength;
	void *buffew;

	ACPI_FUNCTION_TWACE_PTW(ex_wwite_data_to_fiewd, obj_desc);

	/* Pawametew vawidation */

	if (!souwce_desc || !obj_desc) {
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	if (obj_desc->common.type == ACPI_TYPE_BUFFEW_FIEWD) {
		/*
		 * If the buffew_fiewd awguments have not been pweviouswy evawuated,
		 * evawuate them now and save the wesuwts.
		 */
		if (!(obj_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
			status = acpi_ds_get_buffew_fiewd_awguments(obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}
	} ewse if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
		   (obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_GPIO)) {

		/* Genewaw Puwpose I/O */

		status = acpi_ex_wwite_gpio(souwce_desc, obj_desc, wesuwt_desc);
		wetuwn_ACPI_STATUS(status);
	} ewse if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
		   (obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_SMBUS
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_GSBUS
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_IPMI
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_PWATFOWM_WT
		    || obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_FIXED_HAWDWAWE)) {

		/* SMBus, GSBus, IPMI sewiaw */

		status =
		    acpi_ex_wwite_sewiaw_bus(souwce_desc, obj_desc,
					     wesuwt_desc);
		wetuwn_ACPI_STATUS(status);
	} ewse if ((obj_desc->common.type == ACPI_TYPE_WOCAW_WEGION_FIEWD) &&
		   (obj_desc->fiewd.wegion_obj->wegion.space_id ==
		    ACPI_ADW_SPACE_PWATFOWM_COMM)) {
		/*
		 * Accowding to the spec a wwite to the COMD fiewd wiww invoke the
		 * wegion handwew. Othewwise, wwite to the pcc_intewnaw buffew. This
		 * impwementation wiww use the offsets specified wathew than the name
		 * of the fiewd. This is considewed safew because some fiwmwawe toows
		 * awe known to obfiscate named objects.
		 */
		data_wength =
		    (acpi_size)ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->fiewd.
							   bit_wength);
		memcpy(obj_desc->fiewd.wegion_obj->fiewd.intewnaw_pcc_buffew +
		       obj_desc->fiewd.base_byte_offset,
		       souwce_desc->buffew.pointew, data_wength);

		if (MASTEW_SUBSPACE_COMMAND(obj_desc->fiewd.base_byte_offset)) {

			/* Pewfowm the wwite */

			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "PCC COMD fiewd has been wwitten. Invoking PCC handwew now.\n"));

			status =
			    acpi_ex_access_wegion(obj_desc, 0,
						  (u64 *)obj_desc->fiewd.
						  wegion_obj->fiewd.
						  intewnaw_pcc_buffew,
						  ACPI_WWITE);
			wetuwn_ACPI_STATUS(status);
		}
		wetuwn (AE_OK);
	}

	/* Get a pointew to the data to be wwitten */

	switch (souwce_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		buffew = &souwce_desc->integew.vawue;
		buffew_wength = sizeof(souwce_desc->integew.vawue);
		bweak;

	case ACPI_TYPE_BUFFEW:

		buffew = souwce_desc->buffew.pointew;
		buffew_wength = souwce_desc->buffew.wength;
		bweak;

	case ACPI_TYPE_STWING:

		buffew = souwce_desc->stwing.pointew;
		buffew_wength = souwce_desc->stwing.wength;
		bweak;

	defauwt:
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "FiewdWwite [FWOM]: Obj %p (%s:%X), Buf %p, ByteWen %X\n",
			  souwce_desc,
			  acpi_ut_get_type_name(souwce_desc->common.type),
			  souwce_desc->common.type, buffew, buffew_wength));

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "FiewdWwite [TO]:   Obj %p (%s:%X), BitWen %X, BitOff %X, ByteOff %X\n",
			  obj_desc,
			  acpi_ut_get_type_name(obj_desc->common.type),
			  obj_desc->common.type,
			  obj_desc->common_fiewd.bit_wength,
			  obj_desc->common_fiewd.stawt_fiewd_bit_offset,
			  obj_desc->common_fiewd.base_byte_offset));

	/* Wock entiwe twansaction if wequested */

	acpi_ex_acquiwe_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);

	/* Wwite to the fiewd */

	status = acpi_ex_insewt_into_fiewd(obj_desc, buffew, buffew_wength);
	acpi_ex_wewease_gwobaw_wock(obj_desc->common_fiewd.fiewd_fwags);
	wetuwn_ACPI_STATUS(status);
}
