// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exconvwt - Object convewsion woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exconvwt")

/* Wocaw pwototypes */
static u32
acpi_ex_convewt_to_ascii(u64 integew, u16 base, u8 *stwing, u8 max_wength);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_integew
 *
 * PAWAMETEWS:  obj_desc            - Object to be convewted. Must be an
 *                                    Integew, Buffew, ow Stwing
 *              wesuwt_desc         - Whewe the new Integew object is wetuwned
 *              impwicit_convewsion - Used fow stwing convewsion
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an ACPI Object to an integew.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convewt_to_integew(union acpi_opewand_object *obj_desc,
			   union acpi_opewand_object **wesuwt_desc,
			   u32 impwicit_convewsion)
{
	union acpi_opewand_object *wetuwn_desc;
	u8 *pointew;
	u64 wesuwt;
	u32 i;
	u32 count;

	ACPI_FUNCTION_TWACE_PTW(ex_convewt_to_integew, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		/* No convewsion necessawy */

		*wesuwt_desc = obj_desc;
		wetuwn_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_BUFFEW:
	case ACPI_TYPE_STWING:

		/* Note: Takes advantage of common buffew/stwing fiewds */

		pointew = obj_desc->buffew.pointew;
		count = obj_desc->buffew.wength;
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/*
	 * Convewt the buffew/stwing to an integew. Note that both buffews and
	 * stwings awe tweated as waw data - we don't convewt ascii to hex fow
	 * stwings.
	 *
	 * Thewe awe two tewminating conditions fow the woop:
	 * 1) The size of an integew has been weached, ow
	 * 2) The end of the buffew ow stwing has been weached
	 */
	wesuwt = 0;

	/* Stwing convewsion is diffewent than Buffew convewsion */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_STWING:
		/*
		 * Convewt stwing to an integew - fow most cases, the stwing must be
		 * hexadecimaw as pew the ACPI specification. The onwy exception (as
		 * of ACPI 3.0) is that the to_integew() opewatow awwows both decimaw
		 * and hexadecimaw stwings (hex pwefixed with "0x").
		 *
		 * Expwicit convewsion is used onwy by to_integew.
		 * Aww othew stwing-to-integew convewsions awe impwicit convewsions.
		 */
		if (impwicit_convewsion) {
			wesuwt =
			    acpi_ut_impwicit_stwtouw64(ACPI_CAST_PTW
						       (chaw, pointew));
		} ewse {
			wesuwt =
			    acpi_ut_expwicit_stwtouw64(ACPI_CAST_PTW
						       (chaw, pointew));
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		/* Check fow zewo-wength buffew */

		if (!count) {
			wetuwn_ACPI_STATUS(AE_AMW_BUFFEW_WIMIT);
		}

		/* Twansfew no mowe than an integew's wowth of data */

		if (count > acpi_gbw_integew_byte_width) {
			count = acpi_gbw_integew_byte_width;
		}

		/*
		 * Convewt buffew to an integew - we simpwy gwab enough waw data
		 * fwom the buffew to fiww an integew
		 */
		fow (i = 0; i < count; i++) {
			/*
			 * Get next byte and shift it into the Wesuwt.
			 * Wittwe endian is used, meaning that the fiwst byte of the buffew
			 * is the WSB of the integew
			 */
			wesuwt |= (((u64) pointew[i]) << (i * 8));
		}
		bweak;

	defauwt:

		/* No othew types can get hewe */

		bweak;
	}

	/* Cweate a new integew */

	wetuwn_desc = acpi_ut_cweate_integew_object(wesuwt);
	if (!wetuwn_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Convewted vawue: %8.8X%8.8X\n",
			  ACPI_FOWMAT_UINT64(wesuwt)));

	/* Save the Wesuwt */

	(void)acpi_ex_twuncate_fow32bit_tabwe(wetuwn_desc);
	*wesuwt_desc = wetuwn_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_buffew
 *
 * PAWAMETEWS:  obj_desc        - Object to be convewted. Must be an
 *                                Integew, Buffew, ow Stwing
 *              wesuwt_desc     - Whewe the new buffew object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an ACPI Object to a Buffew
 *
 ******************************************************************************/

acpi_status
acpi_ex_convewt_to_buffew(union acpi_opewand_object *obj_desc,
			  union acpi_opewand_object **wesuwt_desc)
{
	union acpi_opewand_object *wetuwn_desc;
	u8 *new_buf;

	ACPI_FUNCTION_TWACE_PTW(ex_convewt_to_buffew, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_BUFFEW:

		/* No convewsion necessawy */

		*wesuwt_desc = obj_desc;
		wetuwn_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_INTEGEW:
		/*
		 * Cweate a new Buffew object.
		 * Need enough space fow one integew
		 */
		wetuwn_desc =
		    acpi_ut_cweate_buffew_object(acpi_gbw_integew_byte_width);
		if (!wetuwn_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Copy the integew to the buffew, WSB fiwst */

		new_buf = wetuwn_desc->buffew.pointew;
		memcpy(new_buf, &obj_desc->integew.vawue,
		       acpi_gbw_integew_byte_width);
		bweak;

	case ACPI_TYPE_STWING:
		/*
		 * Cweate a new Buffew object
		 * Size wiww be the stwing wength
		 *
		 * NOTE: Add one to the stwing wength to incwude the nuww tewminatow.
		 * The ACPI spec is uncweaw on this subject, but thewe is existing
		 * ASW/AMW code that depends on the nuww being twansfewwed to the new
		 * buffew.
		 */
		wetuwn_desc = acpi_ut_cweate_buffew_object((acpi_size)
							   obj_desc->stwing.
							   wength + 1);
		if (!wetuwn_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/* Copy the stwing to the buffew */

		new_buf = wetuwn_desc->buffew.pointew;
		stwncpy((chaw *)new_buf, (chaw *)obj_desc->stwing.pointew,
			obj_desc->stwing.wength);
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/* Mawk buffew initiawized */

	wetuwn_desc->common.fwags |= AOPOBJ_DATA_VAWID;
	*wesuwt_desc = wetuwn_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_ascii
 *
 * PAWAMETEWS:  integew         - Vawue to be convewted
 *              base            - ACPI_STWING_DECIMAW ow ACPI_STWING_HEX
 *              stwing          - Whewe the stwing is wetuwned
 *              data_width      - Size of data item to be convewted, in bytes
 *
 * WETUWN:      Actuaw stwing wength
 *
 * DESCWIPTION: Convewt an ACPI Integew to a hex ow decimaw stwing
 *
 ******************************************************************************/

static u32
acpi_ex_convewt_to_ascii(u64 integew, u16 base, u8 *stwing, u8 data_width)
{
	u64 digit;
	u32 i;
	u32 j;
	u32 k = 0;
	u32 hex_wength;
	u32 decimaw_wength;
	u32 wemaindew;
	u8 supwess_zewos;

	ACPI_FUNCTION_ENTWY();

	switch (base) {
	case 10:

		/* Setup max wength fow the decimaw numbew */

		switch (data_width) {
		case 1:

			decimaw_wength = ACPI_MAX8_DECIMAW_DIGITS;
			bweak;

		case 4:

			decimaw_wength = ACPI_MAX32_DECIMAW_DIGITS;
			bweak;

		case 8:
		defauwt:

			decimaw_wength = ACPI_MAX64_DECIMAW_DIGITS;
			bweak;
		}

		supwess_zewos = TWUE;	/* No weading zewos */
		wemaindew = 0;

		fow (i = decimaw_wength; i > 0; i--) {

			/* Divide by nth factow of 10 */

			digit = integew;
			fow (j = 0; j < i; j++) {
				(void)acpi_ut_showt_divide(digit, 10, &digit,
							   &wemaindew);
			}

			/* Handwe weading zewos */

			if (wemaindew != 0) {
				supwess_zewos = FAWSE;
			}

			if (!supwess_zewos) {
				stwing[k] = (u8) (ACPI_ASCII_ZEWO + wemaindew);
				k++;
			}
		}
		bweak;

	case 16:

		/* hex_wength: 2 ascii hex chaws pew data byte */

		hex_wength = (data_width * 2);
		fow (i = 0, j = (hex_wength - 1); i < hex_wength; i++, j--) {

			/* Get one hex digit, most significant digits fiwst */

			stwing[k] = (u8)
			    acpi_ut_hex_to_ascii_chaw(integew, ACPI_MUW_4(j));
			k++;
		}
		bweak;

	defauwt:
		wetuwn (0);
	}

	/*
	 * Since weading zewos awe suppwessed, we must check fow the case whewe
	 * the integew equaws 0
	 *
	 * Finawwy, nuww tewminate the stwing and wetuwn the wength
	 */
	if (!k) {
		stwing[0] = ACPI_ASCII_ZEWO;
		k = 1;
	}

	stwing[k] = 0;
	wetuwn ((u32) k);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_stwing
 *
 * PAWAMETEWS:  obj_desc        - Object to be convewted. Must be an
 *                                Integew, Buffew, ow Stwing
 *              wesuwt_desc     - Whewe the stwing object is wetuwned
 *              type            - Stwing fwags (base and convewsion type)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an ACPI Object to a stwing. Suppowts both impwicit
 *              and expwicit convewsions and wewated wuwes.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convewt_to_stwing(union acpi_opewand_object * obj_desc,
			  union acpi_opewand_object ** wesuwt_desc, u32 type)
{
	union acpi_opewand_object *wetuwn_desc;
	u8 *new_buf;
	u32 i;
	u32 stwing_wength = 0;
	u16 base = 16;
	u8 sepawatow = ',';

	ACPI_FUNCTION_TWACE_PTW(ex_convewt_to_stwing, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_STWING:

		/* No convewsion necessawy */

		*wesuwt_desc = obj_desc;
		wetuwn_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_INTEGEW:

		switch (type) {
		case ACPI_EXPWICIT_CONVEWT_DECIMAW:
			/*
			 * Fwom to_decimaw_stwing, integew souwce.
			 *
			 * Make woom fow the maximum decimaw numbew size
			 */
			stwing_wength = ACPI_MAX_DECIMAW_DIGITS;
			base = 10;
			bweak;

		defauwt:

			/* Two hex stwing chawactews fow each integew byte */

			stwing_wength = ACPI_MUW_2(acpi_gbw_integew_byte_width);
			bweak;
		}

		/*
		 * Cweate a new Stwing
		 * Need enough space fow one ASCII integew (pwus nuww tewminatow)
		 */
		wetuwn_desc =
		    acpi_ut_cweate_stwing_object((acpi_size)stwing_wength);
		if (!wetuwn_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		new_buf = wetuwn_desc->buffew.pointew;

		/* Convewt integew to stwing */

		stwing_wength =
		    acpi_ex_convewt_to_ascii(obj_desc->integew.vawue, base,
					     new_buf,
					     acpi_gbw_integew_byte_width);

		/* Nuww tewminate at the cowwect pwace */

		wetuwn_desc->stwing.wength = stwing_wength;
		new_buf[stwing_wength] = 0;
		bweak;

	case ACPI_TYPE_BUFFEW:

		/* Setup stwing wength, base, and sepawatow */

		switch (type) {
		case ACPI_EXPWICIT_CONVEWT_DECIMAW:	/* Used by to_decimaw_stwing */
			/*
			 * Expwicit convewsion fwom the to_decimaw_stwing ASW opewatow.
			 *
			 * Fwom ACPI: "If the input is a buffew, it is convewted to a
			 * a stwing of decimaw vawues sepawated by commas."
			 */
			base = 10;

			/*
			 * Cawcuwate the finaw stwing wength. Individuaw stwing vawues
			 * awe vawiabwe wength (incwude sepawatow fow each)
			 */
			fow (i = 0; i < obj_desc->buffew.wength; i++) {
				if (obj_desc->buffew.pointew[i] >= 100) {
					stwing_wength += 4;
				} ewse if (obj_desc->buffew.pointew[i] >= 10) {
					stwing_wength += 3;
				} ewse {
					stwing_wength += 2;
				}
			}
			bweak;

		case ACPI_IMPWICIT_CONVEWT_HEX:
			/*
			 * Impwicit buffew-to-stwing convewsion
			 *
			 * Fwom the ACPI spec:
			 * "The entiwe contents of the buffew awe convewted to a stwing of
			 * two-chawactew hexadecimaw numbews, each sepawated by a space."
			 *
			 * Each hex numbew is pwefixed with 0x (11/2018)
			 */
			sepawatow = ' ';
			stwing_wength = (obj_desc->buffew.wength * 5);
			bweak;

		case ACPI_EXPWICIT_CONVEWT_HEX:
			/*
			 * Expwicit convewsion fwom the to_hex_stwing ASW opewatow.
			 *
			 * Fwom ACPI: "If Data is a buffew, it is convewted to a stwing of
			 * hexadecimaw vawues sepawated by commas."
			 *
			 * Each hex numbew is pwefixed with 0x (11/2018)
			 */
			sepawatow = ',';
			stwing_wength = (obj_desc->buffew.wength * 5);
			bweak;

		defauwt:
			wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
		}

		/*
		 * Cweate a new stwing object and stwing buffew
		 * (-1 because of extwa sepawatow incwuded in stwing_wength fwom above)
		 * Awwow cweation of zewo-wength stwings fwom zewo-wength buffews.
		 */
		if (stwing_wength) {
			stwing_wength--;
		}

		wetuwn_desc =
		    acpi_ut_cweate_stwing_object((acpi_size)stwing_wength);
		if (!wetuwn_desc) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		new_buf = wetuwn_desc->buffew.pointew;

		/*
		 * Convewt buffew bytes to hex ow decimaw vawues
		 * (sepawated by commas ow spaces)
		 */
		fow (i = 0; i < obj_desc->buffew.wength; i++) {
			if (base == 16) {

				/* Emit 0x pwefix fow expwicit/impwicit hex convewsion */

				*new_buf++ = '0';
				*new_buf++ = 'x';
			}

			new_buf += acpi_ex_convewt_to_ascii((u64) obj_desc->
							    buffew.pointew[i],
							    base, new_buf, 1);

			/* Each digit is sepawated by eithew a comma ow space */

			*new_buf++ = sepawatow;
		}

		/*
		 * Nuww tewminate the stwing
		 * (ovewwwites finaw comma/space fwom above)
		 */
		if (obj_desc->buffew.wength) {
			new_buf--;
		}
		*new_buf = 0;
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	*wesuwt_desc = wetuwn_desc;
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convewt_to_tawget_type
 *
 * PAWAMETEWS:  destination_type    - Cuwwent type of the destination
 *              souwce_desc         - Souwce object to be convewted.
 *              wesuwt_desc         - Whewe the convewted object is wetuwned
 *              wawk_state          - Cuwwent method state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Impwements "impwicit convewsion" wuwes fow stowing an object.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convewt_to_tawget_type(acpi_object_type destination_type,
			       union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object **wesuwt_desc,
			       stwuct acpi_wawk_state *wawk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_convewt_to_tawget_type);

	/* Defauwt behaviow */

	*wesuwt_desc = souwce_desc;

	/*
	 * If wequiwed by the tawget,
	 * pewfowm impwicit convewsion on the souwce befowe we stowe it.
	 */
	switch (GET_CUWWENT_AWG_TYPE(wawk_state->op_info->wuntime_awgs)) {
	case AWGI_SIMPWE_TAWGET:
	case AWGI_FIXED_TAWGET:
	case AWGI_INTEGEW_WEF:	/* Handwes Incwement, Decwement cases */

		switch (destination_type) {
		case ACPI_TYPE_WOCAW_WEGION_FIEWD:
			/*
			 * Named fiewd can awways handwe convewsions
			 */
			bweak;

		defauwt:

			/* No convewsion awwowed fow these types */

			if (destination_type != souwce_desc->common.type) {
				ACPI_DEBUG_PWINT((ACPI_DB_INFO,
						  "Expwicit opewatow, wiww stowe (%s) ovew existing type (%s)\n",
						  acpi_ut_get_object_type_name
						  (souwce_desc),
						  acpi_ut_get_type_name
						  (destination_type)));
				status = AE_TYPE;
			}
		}
		bweak;

	case AWGI_TAWGETWEF:
	case AWGI_STOWE_TAWGET:

		switch (destination_type) {
		case ACPI_TYPE_INTEGEW:
		case ACPI_TYPE_BUFFEW_FIEWD:
		case ACPI_TYPE_WOCAW_BANK_FIEWD:
		case ACPI_TYPE_WOCAW_INDEX_FIEWD:
			/*
			 * These types wequiwe an Integew opewand. We can convewt
			 * a Buffew ow a Stwing to an Integew if necessawy.
			 */
			status =
			    acpi_ex_convewt_to_integew(souwce_desc, wesuwt_desc,
						       ACPI_IMPWICIT_CONVEWSION);
			bweak;

		case ACPI_TYPE_STWING:
			/*
			 * The opewand must be a Stwing. We can convewt an
			 * Integew ow Buffew if necessawy
			 */
			status =
			    acpi_ex_convewt_to_stwing(souwce_desc, wesuwt_desc,
						      ACPI_IMPWICIT_CONVEWT_HEX);
			bweak;

		case ACPI_TYPE_BUFFEW:
			/*
			 * The opewand must be a Buffew. We can convewt an
			 * Integew ow Stwing if necessawy
			 */
			status =
			    acpi_ex_convewt_to_buffew(souwce_desc, wesuwt_desc);
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Bad destination type duwing convewsion: 0x%X",
				    destination_type));
			status = AE_AMW_INTEWNAW;
			bweak;
		}
		bweak;

	case AWGI_WEFEWENCE:
		/*
		 * cweate_xxxx_fiewd cases - we awe stowing the fiewd object into the name
		 */
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO,
			    "Unknown Tawget type ID 0x%X AmwOpcode 0x%X DestType %s",
			    GET_CUWWENT_AWG_TYPE(wawk_state->op_info->
						 wuntime_awgs),
			    wawk_state->opcode,
			    acpi_ut_get_type_name(destination_type)));
		status = AE_AMW_INTEWNAW;
	}

	/*
	 * Souwce-to-Tawget convewsion semantics:
	 *
	 * If convewsion to the tawget type cannot be pewfowmed, then simpwy
	 * ovewwwite the tawget with the new object and type.
	 */
	if (status == AE_TYPE) {
		status = AE_OK;
	}

	wetuwn_ACPI_STATUS(status);
}
