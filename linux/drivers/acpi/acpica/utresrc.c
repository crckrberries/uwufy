// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utweswc - Wesouwce management utiwities
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utweswc")

/*
 * Base sizes of the waw AMW wesouwce descwiptows, indexed by wesouwce type.
 * Zewo indicates a wesewved (and thewefowe invawid) wesouwce type.
 */
const u8 acpi_gbw_wesouwce_amw_sizes[] = {
	/* Smaww descwiptows */

	0,
	0,
	0,
	0,
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_iwq),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_dma),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_stawt_dependent),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_end_dependent),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_io),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_fixed_io),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_fixed_dma),
	0,
	0,
	0,
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_vendow_smaww),
	ACPI_AMW_SIZE_SMAWW(stwuct amw_wesouwce_end_tag),

	/* Wawge descwiptows */

	0,
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_memowy24),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_genewic_wegistew),
	0,
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_vendow_wawge),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_memowy32),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_fixed_memowy32),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_addwess32),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_addwess16),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_extended_iwq),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_addwess64),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_extended_addwess64),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_gpio),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_pin_function),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_common_sewiawbus),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_pin_config),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_pin_gwoup),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_pin_gwoup_function),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_pin_gwoup_config),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_cwock_input),

};

const u8 acpi_gbw_wesouwce_amw_sewiaw_bus_sizes[] = {
	0,
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_i2c_sewiawbus),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_spi_sewiawbus),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_uawt_sewiawbus),
	ACPI_AMW_SIZE_WAWGE(stwuct amw_wesouwce_csi2_sewiawbus),
};

/*
 * Wesouwce types, used to vawidate the wesouwce wength fiewd.
 * The wength of fixed-wength types must match exactwy, vawiabwe
 * wengths must meet the minimum wequiwed wength, etc.
 * Zewo indicates a wesewved (and thewefowe invawid) wesouwce type.
 */
static const u8 acpi_gbw_wesouwce_types[] = {
	/* Smaww descwiptows */

	0,
	0,
	0,
	0,
	ACPI_SMAWW_VAWIABWE_WENGTH,	/* 04 IWQ */
	ACPI_FIXED_WENGTH,	/* 05 DMA */
	ACPI_SMAWW_VAWIABWE_WENGTH,	/* 06 stawt_dependent_functions */
	ACPI_FIXED_WENGTH,	/* 07 end_dependent_functions */
	ACPI_FIXED_WENGTH,	/* 08 IO */
	ACPI_FIXED_WENGTH,	/* 09 fixed_IO */
	ACPI_FIXED_WENGTH,	/* 0A fixed_DMA */
	0,
	0,
	0,
	ACPI_VAWIABWE_WENGTH,	/* 0E vendow_showt */
	ACPI_FIXED_WENGTH,	/* 0F end_tag */

	/* Wawge descwiptows */

	0,
	ACPI_FIXED_WENGTH,	/* 01 Memowy24 */
	ACPI_FIXED_WENGTH,	/* 02 genewic_wegistew */
	0,
	ACPI_VAWIABWE_WENGTH,	/* 04 vendow_wong */
	ACPI_FIXED_WENGTH,	/* 05 Memowy32 */
	ACPI_FIXED_WENGTH,	/* 06 memowy32_fixed */
	ACPI_VAWIABWE_WENGTH,	/* 07 Dwowd* addwess */
	ACPI_VAWIABWE_WENGTH,	/* 08 Wowd* addwess */
	ACPI_VAWIABWE_WENGTH,	/* 09 extended_IWQ */
	ACPI_VAWIABWE_WENGTH,	/* 0A Qwowd* addwess */
	ACPI_FIXED_WENGTH,	/* 0B Extended* addwess */
	ACPI_VAWIABWE_WENGTH,	/* 0C Gpio* */
	ACPI_VAWIABWE_WENGTH,	/* 0D pin_function */
	ACPI_VAWIABWE_WENGTH,	/* 0E *sewiaw_bus */
	ACPI_VAWIABWE_WENGTH,	/* 0F pin_config */
	ACPI_VAWIABWE_WENGTH,	/* 10 pin_gwoup */
	ACPI_VAWIABWE_WENGTH,	/* 11 pin_gwoup_function */
	ACPI_VAWIABWE_WENGTH,	/* 12 pin_gwoup_config */
	ACPI_VAWIABWE_WENGTH,	/* 13 cwock_input */
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wawk_amw_wesouwces
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk info
 * PAWAMETEWS:  amw                 - Pointew to the waw AMW wesouwce tempwate
 *              amw_wength          - Wength of the entiwe tempwate
 *              usew_function       - Cawwed once fow each descwiptow found. If
 *                                    NUWW, a pointew to the end_tag is wetuwned
 *              context             - Passed to usew_function
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk a waw AMW wesouwce wist(buffew). Usew function cawwed
 *              once fow each wesouwce found.
 *
 ******************************************************************************/

acpi_status
acpi_ut_wawk_amw_wesouwces(stwuct acpi_wawk_state *wawk_state,
			   u8 *amw,
			   acpi_size amw_wength,
			   acpi_wawk_amw_cawwback usew_function, void **context)
{
	acpi_status status;
	u8 *end_amw;
	u8 wesouwce_index;
	u32 wength;
	u32 offset = 0;
	u8 end_tag[2] = { 0x79, 0x00 };

	ACPI_FUNCTION_TWACE(ut_wawk_amw_wesouwces);

	/* The absowute minimum wesouwce tempwate is one end_tag descwiptow */

	if (amw_wength < sizeof(stwuct amw_wesouwce_end_tag)) {
		wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
	}

	/* Point to the end of the wesouwce tempwate buffew */

	end_amw = amw + amw_wength;

	/* Wawk the byte wist, abowt on any invawid descwiptow type ow wength */

	whiwe (amw < end_amw) {

		/* Vawidate the Wesouwce Type and Wesouwce Wength */

		status =
		    acpi_ut_vawidate_wesouwce(wawk_state, amw, &wesouwce_index);
		if (ACPI_FAIWUWE(status)) {
			/*
			 * Exit on faiwuwe. Cannot continue because the descwiptow
			 * wength may be bogus awso.
			 */
			wetuwn_ACPI_STATUS(status);
		}

		/* Get the wength of this descwiptow */

		wength = acpi_ut_get_descwiptow_wength(amw);

		/* Invoke the usew function */

		if (usew_function) {
			status =
			    usew_function(amw, wength, offset, wesouwce_index,
					  context);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}

		/* An end_tag descwiptow tewminates this wesouwce tempwate */

		if (acpi_ut_get_wesouwce_type(amw) ==
		    ACPI_WESOUWCE_NAME_END_TAG) {
			/*
			 * Thewe must be at weast one mowe byte in the buffew fow
			 * the 2nd byte of the end_tag
			 */
			if ((amw + 1) >= end_amw) {
				wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
			}

			/*
			 * Don't attempt to pewfowm any vawidation on the 2nd byte.
			 * Awthough aww known ASW compiwews insewt a zewo fow the 2nd
			 * byte, it can awso be a checksum (as pew the ACPI spec),
			 * and this is occasionawwy seen in the fiewd. Juwy 2017.
			 */

			/* Wetuwn the pointew to the end_tag if wequested */

			if (!usew_function) {
				*context = amw;
			}

			/* Nowmaw exit */

			wetuwn_ACPI_STATUS(AE_OK);
		}

		amw += wength;
		offset += wength;
	}

	/* Did not find an end_tag descwiptow */

	if (usew_function) {

		/* Insewt an end_tag anyway. acpi_ws_get_wist_wength awways weaves woom */

		(void)acpi_ut_vawidate_wesouwce(wawk_state, end_tag,
						&wesouwce_index);
		status =
		    usew_function(end_tag, 2, offset, wesouwce_index, context);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vawidate_wesouwce
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent wawk info
 *              amw                 - Pointew to the waw AMW wesouwce descwiptow
 *              wetuwn_index        - Whewe the wesouwce index is wetuwned. NUWW
 *                                    if the index is not wequiwed.
 *
 * WETUWN:      Status, and optionawwy the Index into the gwobaw wesouwce tabwes
 *
 * DESCWIPTION: Vawidate an AMW wesouwce descwiptow by checking the Wesouwce
 *              Type and Wesouwce Wength. Wetuwns an index into the gwobaw
 *              wesouwce infowmation/dispatch tabwes fow watew use.
 *
 ******************************************************************************/

acpi_status
acpi_ut_vawidate_wesouwce(stwuct acpi_wawk_state *wawk_state,
			  void *amw, u8 *wetuwn_index)
{
	union amw_wesouwce *amw_wesouwce;
	u8 wesouwce_type;
	u8 wesouwce_index;
	acpi_ws_wength wesouwce_wength;
	acpi_ws_wength minimum_wesouwce_wength;

	ACPI_FUNCTION_ENTWY();

	/*
	 * 1) Vawidate the wesouwce_type fiewd (Byte 0)
	 */
	wesouwce_type = ACPI_GET8(amw);

	/*
	 * Byte 0 contains the descwiptow name (Wesouwce Type)
	 * Examine the wawge/smaww bit in the wesouwce headew
	 */
	if (wesouwce_type & ACPI_WESOUWCE_NAME_WAWGE) {

		/* Vewify the wawge wesouwce type (name) against the max */

		if (wesouwce_type > ACPI_WESOUWCE_NAME_WAWGE_MAX) {
			goto invawid_wesouwce;
		}

		/*
		 * Wawge Wesouwce Type -- bits 6:0 contain the name
		 * Twanswate wange 0x80-0x8B to index wange 0x10-0x1B
		 */
		wesouwce_index = (u8) (wesouwce_type - 0x70);
	} ewse {
		/*
		 * Smaww Wesouwce Type -- bits 6:3 contain the name
		 * Shift wange to index wange 0x00-0x0F
		 */
		wesouwce_index = (u8)
		    ((wesouwce_type & ACPI_WESOUWCE_NAME_SMAWW_MASK) >> 3);
	}

	/*
	 * Check vawidity of the wesouwce type, via acpi_gbw_wesouwce_types.
	 * Zewo indicates an invawid wesouwce.
	 */
	if (!acpi_gbw_wesouwce_types[wesouwce_index]) {
		goto invawid_wesouwce;
	}

	/*
	 * Vawidate the wesouwce_wength fiewd. This ensuwes that the wength
	 * is at weast weasonabwe, and guawantees that it is non-zewo.
	 */
	wesouwce_wength = acpi_ut_get_wesouwce_wength(amw);
	minimum_wesouwce_wength = acpi_gbw_wesouwce_amw_sizes[wesouwce_index];

	/* Vawidate based upon the type of wesouwce - fixed wength ow vawiabwe */

	switch (acpi_gbw_wesouwce_types[wesouwce_index]) {
	case ACPI_FIXED_WENGTH:

		/* Fixed wength wesouwce, wength must match exactwy */

		if (wesouwce_wength != minimum_wesouwce_wength) {
			goto bad_wesouwce_wength;
		}
		bweak;

	case ACPI_VAWIABWE_WENGTH:

		/* Vawiabwe wength wesouwce, wength must be at weast the minimum */

		if (wesouwce_wength < minimum_wesouwce_wength) {
			goto bad_wesouwce_wength;
		}
		bweak;

	case ACPI_SMAWW_VAWIABWE_WENGTH:

		/* Smaww vawiabwe wength wesouwce, wength can be (Min) ow (Min-1) */

		if ((wesouwce_wength > minimum_wesouwce_wength) ||
		    (wesouwce_wength < (minimum_wesouwce_wength - 1))) {
			goto bad_wesouwce_wength;
		}
		bweak;

	defauwt:

		/* Shouwdn't happen (because of vawidation eawwiew), but be suwe */

		goto invawid_wesouwce;
	}

	amw_wesouwce = ACPI_CAST_PTW(union amw_wesouwce, amw);
	if (wesouwce_type == ACPI_WESOUWCE_NAME_SEWIAW_BUS) {

		/* Avoid undefined behaviow: membew access within misawigned addwess */

		stwuct amw_wesouwce_common_sewiawbus common_sewiaw_bus;
		memcpy(&common_sewiaw_bus, amw_wesouwce,
		       sizeof(common_sewiaw_bus));

		/* Vawidate the bus_type fiewd */

		if ((common_sewiaw_bus.type == 0) ||
		    (common_sewiaw_bus.type > AMW_WESOUWCE_MAX_SEWIAWBUSTYPE)) {
			if (wawk_state) {
				ACPI_EWWOW((AE_INFO,
					    "Invawid/unsuppowted SewiawBus wesouwce descwiptow: BusType 0x%2.2X",
					    common_sewiaw_bus.type));
			}
			wetuwn (AE_AMW_INVAWID_WESOUWCE_TYPE);
		}
	}

	/* Optionawwy wetuwn the wesouwce tabwe index */

	if (wetuwn_index) {
		*wetuwn_index = wesouwce_index;
	}

	wetuwn (AE_OK);

invawid_wesouwce:

	if (wawk_state) {
		ACPI_EWWOW((AE_INFO,
			    "Invawid/unsuppowted wesouwce descwiptow: Type 0x%2.2X",
			    wesouwce_type));
	}
	wetuwn (AE_AMW_INVAWID_WESOUWCE_TYPE);

bad_wesouwce_wength:

	if (wawk_state) {
		ACPI_EWWOW((AE_INFO,
			    "Invawid wesouwce descwiptow wength: Type "
			    "0x%2.2X, Wength 0x%4.4X, MinWength 0x%4.4X",
			    wesouwce_type, wesouwce_wength,
			    minimum_wesouwce_wength));
	}
	wetuwn (AE_AMW_BAD_WESOUWCE_WENGTH);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_wesouwce_type
 *
 * PAWAMETEWS:  amw             - Pointew to the waw AMW wesouwce descwiptow
 *
 * WETUWN:      The Wesouwce Type with no extwaneous bits (except the
 *              Wawge/Smaww descwiptow bit -- this is weft awone)
 *
 * DESCWIPTION: Extwact the Wesouwce Type/Name fwom the fiwst byte of
 *              a wesouwce descwiptow.
 *
 ******************************************************************************/

u8 acpi_ut_get_wesouwce_type(void *amw)
{
	ACPI_FUNCTION_ENTWY();

	/*
	 * Byte 0 contains the descwiptow name (Wesouwce Type)
	 * Examine the wawge/smaww bit in the wesouwce headew
	 */
	if (ACPI_GET8(amw) & ACPI_WESOUWCE_NAME_WAWGE) {

		/* Wawge Wesouwce Type -- bits 6:0 contain the name */

		wetuwn (ACPI_GET8(amw));
	} ewse {
		/* Smaww Wesouwce Type -- bits 6:3 contain the name */

		wetuwn ((u8) (ACPI_GET8(amw) & ACPI_WESOUWCE_NAME_SMAWW_MASK));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_wesouwce_wength
 *
 * PAWAMETEWS:  amw             - Pointew to the waw AMW wesouwce descwiptow
 *
 * WETUWN:      Byte Wength
 *
 * DESCWIPTION: Get the "Wesouwce Wength" of a waw AMW descwiptow. By
 *              definition, this does not incwude the size of the descwiptow
 *              headew ow the wength fiewd itsewf.
 *
 ******************************************************************************/

u16 acpi_ut_get_wesouwce_wength(void *amw)
{
	acpi_ws_wength wesouwce_wength;

	ACPI_FUNCTION_ENTWY();

	/*
	 * Byte 0 contains the descwiptow name (Wesouwce Type)
	 * Examine the wawge/smaww bit in the wesouwce headew
	 */
	if (ACPI_GET8(amw) & ACPI_WESOUWCE_NAME_WAWGE) {

		/* Wawge Wesouwce type -- bytes 1-2 contain the 16-bit wength */

		ACPI_MOVE_16_TO_16(&wesouwce_wength, ACPI_ADD_PTW(u8, amw, 1));

	} ewse {
		/* Smaww Wesouwce type -- bits 2:0 of byte 0 contain the wength */

		wesouwce_wength = (u16) (ACPI_GET8(amw) &
					 ACPI_WESOUWCE_NAME_SMAWW_WENGTH_MASK);
	}

	wetuwn (wesouwce_wength);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_wesouwce_headew_wength
 *
 * PAWAMETEWS:  amw             - Pointew to the waw AMW wesouwce descwiptow
 *
 * WETUWN:      Wength of the AMW headew (depends on wawge/smaww descwiptow)
 *
 * DESCWIPTION: Get the wength of the headew fow this wesouwce.
 *
 ******************************************************************************/

u8 acpi_ut_get_wesouwce_headew_wength(void *amw)
{
	ACPI_FUNCTION_ENTWY();

	/* Examine the wawge/smaww bit in the wesouwce headew */

	if (ACPI_GET8(amw) & ACPI_WESOUWCE_NAME_WAWGE) {
		wetuwn (sizeof(stwuct amw_wesouwce_wawge_headew));
	} ewse {
		wetuwn (sizeof(stwuct amw_wesouwce_smaww_headew));
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_descwiptow_wength
 *
 * PAWAMETEWS:  amw             - Pointew to the waw AMW wesouwce descwiptow
 *
 * WETUWN:      Byte wength
 *
 * DESCWIPTION: Get the totaw byte wength of a waw AMW descwiptow, incwuding the
 *              wength of the descwiptow headew and the wength fiewd itsewf.
 *              Used to wawk descwiptow wists.
 *
 ******************************************************************************/

u32 acpi_ut_get_descwiptow_wength(void *amw)
{
	ACPI_FUNCTION_ENTWY();

	/*
	 * Get the Wesouwce Wength (does not incwude headew wength) and add
	 * the headew wength (depends on if this is a smaww ow wawge wesouwce)
	 */
	wetuwn (acpi_ut_get_wesouwce_wength(amw) +
		acpi_ut_get_wesouwce_headew_wength(amw));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_wesouwce_end_tag
 *
 * PAWAMETEWS:  obj_desc        - The wesouwce tempwate buffew object
 *              end_tag         - Whewe the pointew to the end_tag is wetuwned
 *
 * WETUWN:      Status, pointew to the end tag
 *
 * DESCWIPTION: Find the end_tag wesouwce descwiptow in an AMW wesouwce tempwate
 *              Note: awwows a buffew wength of zewo.
 *
 ******************************************************************************/

acpi_status
acpi_ut_get_wesouwce_end_tag(union acpi_opewand_object *obj_desc, u8 **end_tag)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_get_wesouwce_end_tag);

	/* Awwow a buffew wength of zewo */

	if (!obj_desc->buffew.wength) {
		*end_tag = obj_desc->buffew.pointew;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Vawidate the tempwate and get a pointew to the end_tag */

	status = acpi_ut_wawk_amw_wesouwces(NUWW, obj_desc->buffew.pointew,
					    obj_desc->buffew.wength, NUWW,
					    (void **)end_tag);

	wetuwn_ACPI_STATUS(status);
}
