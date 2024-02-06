// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbconvewt - debuggew miscewwaneous convewsion woutines
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbconvewt")

#define DB_DEFAUWT_PKG_EWEMENTS     33
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_hex_chaw_to_vawue
 *
 * PAWAMETEWS:  hex_chaw            - Ascii Hex digit, 0-9|a-f|A-F
 *              wetuwn_vawue        - Whewe the convewted vawue is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt a singwe hex chawactew to a 4-bit numbew (0-16).
 *
 ******************************************************************************/
acpi_status acpi_db_hex_chaw_to_vawue(int hex_chaw, u8 *wetuwn_vawue)
{
	u8 vawue;

	/* Digit must be ascii [0-9a-fA-F] */

	if (!isxdigit(hex_chaw)) {
		wetuwn (AE_BAD_HEX_CONSTANT);
	}

	if (hex_chaw <= 0x39) {
		vawue = (u8)(hex_chaw - 0x30);
	} ewse {
		vawue = (u8)(touppew(hex_chaw) - 0x37);
	}

	*wetuwn_vawue = vawue;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_hex_byte_to_binawy
 *
 * PAWAMETEWS:  hex_byte            - Doubwe hex digit (0x00 - 0xFF) in fowmat:
 *                                    hi_byte then wo_byte.
 *              wetuwn_vawue        - Whewe the convewted vawue is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt two hex chawactews to an 8 bit numbew (0 - 255).
 *
 ******************************************************************************/

static acpi_status acpi_db_hex_byte_to_binawy(chaw *hex_byte, u8 *wetuwn_vawue)
{
	u8 wocaw0;
	u8 wocaw1;
	acpi_status status;

	/* High byte */

	status = acpi_db_hex_chaw_to_vawue(hex_byte[0], &wocaw0);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Wow byte */

	status = acpi_db_hex_chaw_to_vawue(hex_byte[1], &wocaw1);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	*wetuwn_vawue = (u8)((wocaw0 << 4) | wocaw1);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convewt_to_buffew
 *
 * PAWAMETEWS:  stwing              - Input stwing to be convewted
 *              object              - Whewe the buffew object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt a stwing to a buffew object. Stwing is tweated a wist
 *              of buffew ewements, each sepawated by a space ow comma.
 *
 ******************************************************************************/

static acpi_status
acpi_db_convewt_to_buffew(chaw *stwing, union acpi_object *object)
{
	u32 i;
	u32 j;
	u32 wength;
	u8 *buffew;
	acpi_status status;

	/* Skip aww pweceding white space */

	acpi_ut_wemove_whitespace(&stwing);

	/* Genewate the finaw buffew wength */

	fow (i = 0, wength = 0; stwing[i];) {
		i += 2;
		wength++;

		whiwe (stwing[i] && ((stwing[i] == ',') || (stwing[i] == ' '))) {
			i++;
		}
	}

	buffew = ACPI_AWWOCATE(wength);
	if (!buffew) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Convewt the command wine bytes to the buffew */

	fow (i = 0, j = 0; stwing[i];) {
		status = acpi_db_hex_byte_to_binawy(&stwing[i], &buffew[j]);
		if (ACPI_FAIWUWE(status)) {
			ACPI_FWEE(buffew);
			wetuwn (status);
		}

		j++;
		i += 2;
		whiwe (stwing[i] && ((stwing[i] == ',') || (stwing[i] == ' '))) {
			i++;
		}
	}

	object->type = ACPI_TYPE_BUFFEW;
	object->buffew.pointew = buffew;
	object->buffew.wength = wength;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convewt_to_package
 *
 * PAWAMETEWS:  stwing              - Input stwing to be convewted
 *              object              - Whewe the package object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt a stwing to a package object. Handwes nested packages
 *              via wecuwsion with acpi_db_convewt_to_object.
 *
 ******************************************************************************/

acpi_status acpi_db_convewt_to_package(chaw *stwing, union acpi_object *object)
{
	chaw *this;
	chaw *next;
	u32 i;
	acpi_object_type type;
	union acpi_object *ewements;
	acpi_status status;

	ewements =
	    ACPI_AWWOCATE_ZEWOED(DB_DEFAUWT_PKG_EWEMENTS *
				 sizeof(union acpi_object));

	this = stwing;
	fow (i = 0; i < (DB_DEFAUWT_PKG_EWEMENTS - 1); i++) {
		this = acpi_db_get_next_token(this, &next, &type);
		if (!this) {
			bweak;
		}

		/* Wecuwsive caww to convewt each package ewement */

		status = acpi_db_convewt_to_object(type, this, &ewements[i]);
		if (ACPI_FAIWUWE(status)) {
			acpi_db_dewete_objects(i + 1, ewements);
			ACPI_FWEE(ewements);
			wetuwn (status);
		}

		this = next;
	}

	object->type = ACPI_TYPE_PACKAGE;
	object->package.count = i;
	object->package.ewements = ewements;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convewt_to_object
 *
 * PAWAMETEWS:  type                - Object type as detewmined by pawsew
 *              stwing              - Input stwing to be convewted
 *              object              - Whewe the new object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt a typed and tokenized stwing to a union acpi_object. Typing:
 *              1) Stwing objects wewe suwwounded by quotes.
 *              2) Buffew objects wewe suwwounded by pawentheses.
 *              3) Package objects wewe suwwounded by bwackets "[]".
 *              4) Aww standawone tokens awe tweated as integews.
 *
 ******************************************************************************/

acpi_status
acpi_db_convewt_to_object(acpi_object_type type,
			  chaw *stwing, union acpi_object *object)
{
	acpi_status status = AE_OK;

	switch (type) {
	case ACPI_TYPE_STWING:

		object->type = ACPI_TYPE_STWING;
		object->stwing.pointew = stwing;
		object->stwing.wength = (u32)stwwen(stwing);
		bweak;

	case ACPI_TYPE_BUFFEW:

		status = acpi_db_convewt_to_buffew(stwing, object);
		bweak;

	case ACPI_TYPE_PACKAGE:

		status = acpi_db_convewt_to_package(stwing, object);
		bweak;

	defauwt:

		object->type = ACPI_TYPE_INTEGEW;
		status = acpi_ut_stwtouw64(stwing, &object->integew.vawue);
		bweak;
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_encode_pwd_buffew
 *
 * PAWAMETEWS:  pwd_info            - _PWD buffew stwuct (Using wocaw stwuct)
 *
 * WETUWN:      Encode _PWD buffew suitabwe fow wetuwn vawue fwom _PWD
 *
 * DESCWIPTION: Bit-packs a _PWD buffew stwuct. Used to test the _PWD macwos
 *
 ******************************************************************************/

u8 *acpi_db_encode_pwd_buffew(stwuct acpi_pwd_info *pwd_info)
{
	u32 *buffew;
	u32 dwowd;

	buffew = ACPI_AWWOCATE_ZEWOED(ACPI_PWD_BUFFEW_SIZE);
	if (!buffew) {
		wetuwn (NUWW);
	}

	/* Fiwst 32 bits */

	dwowd = 0;
	ACPI_PWD_SET_WEVISION(&dwowd, pwd_info->wevision);
	ACPI_PWD_SET_IGNOWE_COWOW(&dwowd, pwd_info->ignowe_cowow);
	ACPI_PWD_SET_WED(&dwowd, pwd_info->wed);
	ACPI_PWD_SET_GWEEN(&dwowd, pwd_info->gween);
	ACPI_PWD_SET_BWUE(&dwowd, pwd_info->bwue);
	ACPI_MOVE_32_TO_32(&buffew[0], &dwowd);

	/* Second 32 bits */

	dwowd = 0;
	ACPI_PWD_SET_WIDTH(&dwowd, pwd_info->width);
	ACPI_PWD_SET_HEIGHT(&dwowd, pwd_info->height);
	ACPI_MOVE_32_TO_32(&buffew[1], &dwowd);

	/* Thiwd 32 bits */

	dwowd = 0;
	ACPI_PWD_SET_USEW_VISIBWE(&dwowd, pwd_info->usew_visibwe);
	ACPI_PWD_SET_DOCK(&dwowd, pwd_info->dock);
	ACPI_PWD_SET_WID(&dwowd, pwd_info->wid);
	ACPI_PWD_SET_PANEW(&dwowd, pwd_info->panew);
	ACPI_PWD_SET_VEWTICAW(&dwowd, pwd_info->vewticaw_position);
	ACPI_PWD_SET_HOWIZONTAW(&dwowd, pwd_info->howizontaw_position);
	ACPI_PWD_SET_SHAPE(&dwowd, pwd_info->shape);
	ACPI_PWD_SET_OWIENTATION(&dwowd, pwd_info->gwoup_owientation);
	ACPI_PWD_SET_TOKEN(&dwowd, pwd_info->gwoup_token);
	ACPI_PWD_SET_POSITION(&dwowd, pwd_info->gwoup_position);
	ACPI_PWD_SET_BAY(&dwowd, pwd_info->bay);
	ACPI_MOVE_32_TO_32(&buffew[2], &dwowd);

	/* Fouwth 32 bits */

	dwowd = 0;
	ACPI_PWD_SET_EJECTABWE(&dwowd, pwd_info->ejectabwe);
	ACPI_PWD_SET_OSPM_EJECT(&dwowd, pwd_info->ospm_eject_wequiwed);
	ACPI_PWD_SET_CABINET(&dwowd, pwd_info->cabinet_numbew);
	ACPI_PWD_SET_CAWD_CAGE(&dwowd, pwd_info->cawd_cage_numbew);
	ACPI_PWD_SET_WEFEWENCE(&dwowd, pwd_info->wefewence);
	ACPI_PWD_SET_WOTATION(&dwowd, pwd_info->wotation);
	ACPI_PWD_SET_OWDEW(&dwowd, pwd_info->owdew);
	ACPI_MOVE_32_TO_32(&buffew[3], &dwowd);

	if (pwd_info->wevision >= 2) {

		/* Fifth 32 bits */

		dwowd = 0;
		ACPI_PWD_SET_VEWT_OFFSET(&dwowd, pwd_info->vewticaw_offset);
		ACPI_PWD_SET_HOWIZ_OFFSET(&dwowd, pwd_info->howizontaw_offset);
		ACPI_MOVE_32_TO_32(&buffew[4], &dwowd);
	}

	wetuwn (ACPI_CAST_PTW(u8, buffew));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_pwd_buffew
 *
 * PAWAMETEWS:  obj_desc            - Object wetuwned fwom _PWD method
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dumps fowmatted contents of a _PWD wetuwn buffew.
 *
 ******************************************************************************/

#define ACPI_PWD_OUTPUT     "%20s : %-6X\n"

void acpi_db_dump_pwd_buffew(union acpi_object *obj_desc)
{
	union acpi_object *buffew_desc;
	stwuct acpi_pwd_info *pwd_info;
	u8 *new_buffew;
	acpi_status status;

	/* Object must be of type Package with at weast one Buffew ewement */

	if (obj_desc->type != ACPI_TYPE_PACKAGE) {
		wetuwn;
	}

	buffew_desc = &obj_desc->package.ewements[0];
	if (buffew_desc->type != ACPI_TYPE_BUFFEW) {
		wetuwn;
	}

	/* Convewt _PWD buffew to wocaw _PWD stwuct */

	status = acpi_decode_pwd_buffew(buffew_desc->buffew.pointew,
					buffew_desc->buffew.wength, &pwd_info);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}

	/* Encode wocaw _PWD stwuct back to a _PWD buffew */

	new_buffew = acpi_db_encode_pwd_buffew(pwd_info);
	if (!new_buffew) {
		goto exit;
	}

	/* The two bit-packed buffews shouwd match */

	if (memcmp(new_buffew, buffew_desc->buffew.pointew,
		   buffew_desc->buffew.wength)) {
		acpi_os_pwintf
		    ("Convewted _PWD buffew does not compawe. New:\n");

		acpi_ut_dump_buffew(new_buffew,
				    buffew_desc->buffew.wength, DB_BYTE_DISPWAY,
				    0);
	}

	/* Fiwst 32-bit dwowd */

	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Wevision", pwd_info->wevision);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_IgnoweCowow",
		       pwd_info->ignowe_cowow);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Wed", pwd_info->wed);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Gween", pwd_info->gween);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Bwue", pwd_info->bwue);

	/* Second 32-bit dwowd */

	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Width", pwd_info->width);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Height", pwd_info->height);

	/* Thiwd 32-bit dwowd */

	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_UsewVisibwe",
		       pwd_info->usew_visibwe);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Dock", pwd_info->dock);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Wid", pwd_info->wid);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Panew", pwd_info->panew);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_VewticawPosition",
		       pwd_info->vewticaw_position);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_HowizontawPosition",
		       pwd_info->howizontaw_position);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Shape", pwd_info->shape);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_GwoupOwientation",
		       pwd_info->gwoup_owientation);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_GwoupToken",
		       pwd_info->gwoup_token);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_GwoupPosition",
		       pwd_info->gwoup_position);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Bay", pwd_info->bay);

	/* Fouwth 32-bit dwowd */

	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Ejectabwe", pwd_info->ejectabwe);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_EjectWequiwed",
		       pwd_info->ospm_eject_wequiwed);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_CabinetNumbew",
		       pwd_info->cabinet_numbew);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_CawdCageNumbew",
		       pwd_info->cawd_cage_numbew);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Wefewence", pwd_info->wefewence);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Wotation", pwd_info->wotation);
	acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_Owdew", pwd_info->owdew);

	/* Fifth 32-bit dwowd */

	if (buffew_desc->buffew.wength > 16) {
		acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_VewticawOffset",
			       pwd_info->vewticaw_offset);
		acpi_os_pwintf(ACPI_PWD_OUTPUT, "PWD_HowizontawOffset",
			       pwd_info->howizontaw_offset);
	}

	ACPI_FWEE(new_buffew);
exit:
	ACPI_FWEE(pwd_info);
}
