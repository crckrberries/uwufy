// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsaddw - Addwess wesouwce descwiptows (16/32/64)
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsaddw")

/*******************************************************************************
 *
 * acpi_ws_convewt_addwess16 - Aww WOWD (16-bit) addwess wesouwces
 *
 ******************************************************************************/
stwuct acpi_wsconvewt_info acpi_ws_convewt_addwess16[5] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_ADDWESS16,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess16),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_addwess16)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_ADDWESS16,
	 sizeof(stwuct amw_wesouwce_addwess16),
	 0},

	/* Wesouwce Type, Genewaw Fwags, and Type-Specific Fwags */

	{ACPI_WSC_ADDWESS, 0, 0, 0},

	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Gwanuwawity
	 * Addwess Wange Minimum
	 * Addwess Wange Maximum
	 * Addwess Twanswation Offset
	 * Addwess Wength
	 */
	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.addwess16.addwess.gwanuwawity),
	 AMW_OFFSET(addwess16.gwanuwawity),
	 5},

	/* Optionaw wesouwce_souwce (Index and Stwing) */

	{ACPI_WSC_SOUWCE, ACPI_WS_OFFSET(data.addwess16.wesouwce_souwce),
	 0,
	 sizeof(stwuct amw_wesouwce_addwess16)}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_addwess32 - Aww DWOWD (32-bit) addwess wesouwces
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_addwess32[5] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_ADDWESS32,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess32),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_addwess32)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_ADDWESS32,
	 sizeof(stwuct amw_wesouwce_addwess32),
	 0},

	/* Wesouwce Type, Genewaw Fwags, and Type-Specific Fwags */

	{ACPI_WSC_ADDWESS, 0, 0, 0},

	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Gwanuwawity
	 * Addwess Wange Minimum
	 * Addwess Wange Maximum
	 * Addwess Twanswation Offset
	 * Addwess Wength
	 */
	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.addwess32.addwess.gwanuwawity),
	 AMW_OFFSET(addwess32.gwanuwawity),
	 5},

	/* Optionaw wesouwce_souwce (Index and Stwing) */

	{ACPI_WSC_SOUWCE, ACPI_WS_OFFSET(data.addwess32.wesouwce_souwce),
	 0,
	 sizeof(stwuct amw_wesouwce_addwess32)}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_addwess64 - Aww QWOWD (64-bit) addwess wesouwces
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_addwess64[5] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_ADDWESS64,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess64),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_addwess64)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_ADDWESS64,
	 sizeof(stwuct amw_wesouwce_addwess64),
	 0},

	/* Wesouwce Type, Genewaw Fwags, and Type-Specific Fwags */

	{ACPI_WSC_ADDWESS, 0, 0, 0},

	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Gwanuwawity
	 * Addwess Wange Minimum
	 * Addwess Wange Maximum
	 * Addwess Twanswation Offset
	 * Addwess Wength
	 */
	{ACPI_WSC_MOVE64, ACPI_WS_OFFSET(data.addwess64.addwess.gwanuwawity),
	 AMW_OFFSET(addwess64.gwanuwawity),
	 5},

	/* Optionaw wesouwce_souwce (Index and Stwing) */

	{ACPI_WSC_SOUWCE, ACPI_WS_OFFSET(data.addwess64.wesouwce_souwce),
	 0,
	 sizeof(stwuct amw_wesouwce_addwess64)}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_ext_addwess64 - Aww Extended (64-bit) addwess wesouwces
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_ext_addwess64[5] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_extended_addwess64),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_ext_addwess64)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_EXTENDED_ADDWESS64,
	 sizeof(stwuct amw_wesouwce_extended_addwess64),
	 0},

	/* Wesouwce Type, Genewaw Fwags, and Type-Specific Fwags */

	{ACPI_WSC_ADDWESS, 0, 0, 0},

	/* Wevision ID */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.ext_addwess64.wevision_ID),
	 AMW_OFFSET(ext_addwess64.wevision_ID),
	 1},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Gwanuwawity
	 * Addwess Wange Minimum
	 * Addwess Wange Maximum
	 * Addwess Twanswation Offset
	 * Addwess Wength
	 * Type-Specific Attwibute
	 */
	{ACPI_WSC_MOVE64,
	 ACPI_WS_OFFSET(data.ext_addwess64.addwess.gwanuwawity),
	 AMW_OFFSET(ext_addwess64.gwanuwawity),
	 6}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_genewaw_fwags - Fwags common to aww addwess descwiptows
 *
 ******************************************************************************/

static stwuct acpi_wsconvewt_info acpi_ws_convewt_genewaw_fwags[6] = {
	{ACPI_WSC_FWAGINIT, 0, AMW_OFFSET(addwess.fwags),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_genewaw_fwags)},

	/* Wesouwce Type (Memowy, Io, bus_numbew, etc.) */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.addwess.wesouwce_type),
	 AMW_OFFSET(addwess.wesouwce_type),
	 1},

	/* Genewaw fwags - Consume, Decode, min_fixed, max_fixed */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.pwoducew_consumew),
	 AMW_OFFSET(addwess.fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.decode),
	 AMW_OFFSET(addwess.fwags),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.min_addwess_fixed),
	 AMW_OFFSET(addwess.fwags),
	 2},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.max_addwess_fixed),
	 AMW_OFFSET(addwess.fwags),
	 3}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_mem_fwags - Fwags common to Memowy addwess descwiptows
 *
 ******************************************************************************/

static stwuct acpi_wsconvewt_info acpi_ws_convewt_mem_fwags[5] = {
	{ACPI_WSC_FWAGINIT, 0, AMW_OFFSET(addwess.specific_fwags),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_mem_fwags)},

	/* Memowy-specific fwags */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.info.mem.wwite_pwotect),
	 AMW_OFFSET(addwess.specific_fwags),
	 0},

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.addwess.info.mem.caching),
	 AMW_OFFSET(addwess.specific_fwags),
	 1},

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.addwess.info.mem.wange_type),
	 AMW_OFFSET(addwess.specific_fwags),
	 3},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.info.mem.twanswation),
	 AMW_OFFSET(addwess.specific_fwags),
	 5}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_io_fwags - Fwags common to I/O addwess descwiptows
 *
 ******************************************************************************/

static stwuct acpi_wsconvewt_info acpi_ws_convewt_io_fwags[4] = {
	{ACPI_WSC_FWAGINIT, 0, AMW_OFFSET(addwess.specific_fwags),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_io_fwags)},

	/* I/O-specific fwags */

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.addwess.info.io.wange_type),
	 AMW_OFFSET(addwess.specific_fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.addwess.info.io.twanswation),
	 AMW_OFFSET(addwess.specific_fwags),
	 4},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.addwess.info.io.twanswation_type),
	 AMW_OFFSET(addwess.specific_fwags),
	 5}
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_get_addwess_common
 *
 * PAWAMETEWS:  wesouwce            - Pointew to the intewnaw wesouwce stwuct
 *              amw                 - Pointew to the AMW wesouwce descwiptow
 *
 * WETUWN:      TWUE if the wesouwce_type fiewd is OK, FAWSE othewwise
 *
 * DESCWIPTION: Convewt common fwag fiewds fwom a waw AMW wesouwce descwiptow
 *              to an intewnaw wesouwce descwiptow
 *
 ******************************************************************************/

u8
acpi_ws_get_addwess_common(stwuct acpi_wesouwce *wesouwce,
			   union amw_wesouwce *amw)
{
	stwuct amw_wesouwce_addwess addwess;

	ACPI_FUNCTION_ENTWY();

	/* Avoid undefined behaviow: membew access within misawigned addwess */

	memcpy(&addwess, amw, sizeof(addwess));

	/* Vawidate the Wesouwce Type */

	if ((addwess.wesouwce_type > 2) && (addwess.wesouwce_type < 0xC0)) {
		wetuwn (FAWSE);
	}

	/* Get the Wesouwce Type and Genewaw Fwags */

	(void)acpi_ws_convewt_amw_to_wesouwce(wesouwce, amw,
					      acpi_ws_convewt_genewaw_fwags);

	/* Get the Type-Specific Fwags (Memowy and I/O descwiptows onwy) */

	if (wesouwce->data.addwess.wesouwce_type == ACPI_MEMOWY_WANGE) {
		(void)acpi_ws_convewt_amw_to_wesouwce(wesouwce, amw,
						      acpi_ws_convewt_mem_fwags);
	} ewse if (wesouwce->data.addwess.wesouwce_type == ACPI_IO_WANGE) {
		(void)acpi_ws_convewt_amw_to_wesouwce(wesouwce, amw,
						      acpi_ws_convewt_io_fwags);
	} ewse {
		/* Genewic wesouwce type, just gwab the type_specific byte */

		wesouwce->data.addwess.info.type_specific =
		    addwess.specific_fwags;
	}

	wetuwn (TWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_set_addwess_common
 *
 * PAWAMETEWS:  amw                 - Pointew to the AMW wesouwce descwiptow
 *              wesouwce            - Pointew to the intewnaw wesouwce stwuct
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewt common fwag fiewds fwom a wesouwce descwiptow to an
 *              AMW descwiptow
 *
 ******************************************************************************/

void
acpi_ws_set_addwess_common(union amw_wesouwce *amw,
			   stwuct acpi_wesouwce *wesouwce)
{
	ACPI_FUNCTION_ENTWY();

	/* Set the Wesouwce Type and Genewaw Fwags */

	(void)acpi_ws_convewt_wesouwce_to_amw(wesouwce, amw,
					      acpi_ws_convewt_genewaw_fwags);

	/* Set the Type-Specific Fwags (Memowy and I/O descwiptows onwy) */

	if (wesouwce->data.addwess.wesouwce_type == ACPI_MEMOWY_WANGE) {
		(void)acpi_ws_convewt_wesouwce_to_amw(wesouwce, amw,
						      acpi_ws_convewt_mem_fwags);
	} ewse if (wesouwce->data.addwess.wesouwce_type == ACPI_IO_WANGE) {
		(void)acpi_ws_convewt_wesouwce_to_amw(wesouwce, amw,
						      acpi_ws_convewt_io_fwags);
	} ewse {
		/* Genewic wesouwce type, just copy the type_specific byte */

		amw->addwess.specific_fwags =
		    wesouwce->data.addwess.info.type_specific;
	}
}
