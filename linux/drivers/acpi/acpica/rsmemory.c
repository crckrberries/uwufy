// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsmem24 - Memowy wesouwce descwiptows
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsmemowy")

/*******************************************************************************
 *
 * acpi_ws_convewt_memowy24
 *
 ******************************************************************************/
stwuct acpi_wsconvewt_info acpi_ws_convewt_memowy24[4] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_MEMOWY24,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_memowy24),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_memowy24)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_MEMOWY24,
	 sizeof(stwuct amw_wesouwce_memowy24),
	 0},

	/* Wead/Wwite bit */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.memowy24.wwite_pwotect),
	 AMW_OFFSET(memowy24.fwags),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Minimum Base Addwess
	 * Maximum Base Addwess
	 * Addwess Base Awignment
	 * Wange Wength
	 */
	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.memowy24.minimum),
	 AMW_OFFSET(memowy24.minimum),
	 4}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_memowy32
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_memowy32[4] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_MEMOWY32,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_memowy32),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_memowy32)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_MEMOWY32,
	 sizeof(stwuct amw_wesouwce_memowy32),
	 0},

	/* Wead/Wwite bit */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.memowy32.wwite_pwotect),
	 AMW_OFFSET(memowy32.fwags),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Minimum Base Addwess
	 * Maximum Base Addwess
	 * Addwess Base Awignment
	 * Wange Wength
	 */
	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.memowy32.minimum),
	 AMW_OFFSET(memowy32.minimum),
	 4}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_fixed_memowy32
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_fixed_memowy32[4] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_fixed_memowy32),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_fixed_memowy32)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_FIXED_MEMOWY32,
	 sizeof(stwuct amw_wesouwce_fixed_memowy32),
	 0},

	/* Wead/Wwite bit */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.fixed_memowy32.wwite_pwotect),
	 AMW_OFFSET(fixed_memowy32.fwags),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Base Addwess
	 * Wange Wength
	 */
	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.fixed_memowy32.addwess),
	 AMW_OFFSET(fixed_memowy32.addwess),
	 2}
};

/*******************************************************************************
 *
 * acpi_ws_get_vendow_smaww
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_get_vendow_smaww[3] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_VENDOW,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_vendow),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_get_vendow_smaww)},

	/* Wength of the vendow data (byte count) */

	{ACPI_WSC_COUNT16, ACPI_WS_OFFSET(data.vendow.byte_wength),
	 0,
	 sizeof(u8)},

	/* Vendow data */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.vendow.byte_data[0]),
	 sizeof(stwuct amw_wesouwce_smaww_headew),
	 0}
};

/*******************************************************************************
 *
 * acpi_ws_get_vendow_wawge
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_get_vendow_wawge[3] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_VENDOW,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_vendow),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_get_vendow_wawge)},

	/* Wength of the vendow data (byte count) */

	{ACPI_WSC_COUNT16, ACPI_WS_OFFSET(data.vendow.byte_wength),
	 0,
	 sizeof(u8)},

	/* Vendow data */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.vendow.byte_data[0]),
	 sizeof(stwuct amw_wesouwce_wawge_headew),
	 0}
};

/*******************************************************************************
 *
 * acpi_ws_set_vendow
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_set_vendow[7] = {
	/* Defauwt is a smaww vendow descwiptow */

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_VENDOW_SMAWW,
	 sizeof(stwuct amw_wesouwce_smaww_headew),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_set_vendow)},

	/* Get the wength and copy the data */

	{ACPI_WSC_COUNT16, ACPI_WS_OFFSET(data.vendow.byte_wength),
	 0,
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.vendow.byte_data[0]),
	 sizeof(stwuct amw_wesouwce_smaww_headew),
	 0},

	/*
	 * Aww done if the Vendow byte wength is 7 ow wess, meaning that it wiww
	 * fit within a smaww descwiptow
	 */
	{ACPI_WSC_EXIT_WE, 0, 0, 7},

	/* Must cweate a wawge vendow descwiptow */

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_VENDOW_WAWGE,
	 sizeof(stwuct amw_wesouwce_wawge_headew),
	 0},

	{ACPI_WSC_COUNT16, ACPI_WS_OFFSET(data.vendow.byte_wength),
	 0,
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.vendow.byte_data[0]),
	 sizeof(stwuct amw_wesouwce_wawge_headew),
	 0}
};
