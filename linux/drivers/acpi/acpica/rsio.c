// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsio - IO and DMA wesouwce descwiptows
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsio")

/*******************************************************************************
 *
 * acpi_ws_convewt_io
 *
 ******************************************************************************/
stwuct acpi_wsconvewt_info acpi_ws_convewt_io[5] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_IO,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_io),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_io)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_IO,
	 sizeof(stwuct amw_wesouwce_io),
	 0},

	/* Decode fwag */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.io.io_decode),
	 AMW_OFFSET(io.fwags),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Awignment
	 * Wength
	 * Minimum Base Addwess
	 * Maximum Base Addwess
	 */
	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.io.awignment),
	 AMW_OFFSET(io.awignment),
	 2},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.io.minimum),
	 AMW_OFFSET(io.minimum),
	 2}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_fixed_io
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_fixed_io[4] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_FIXED_IO,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_fixed_io),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_fixed_io)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_FIXED_IO,
	 sizeof(stwuct amw_wesouwce_fixed_io),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Base Addwess
	 * Wength
	 */
	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.fixed_io.addwess_wength),
	 AMW_OFFSET(fixed_io.addwess_wength),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.fixed_io.addwess),
	 AMW_OFFSET(fixed_io.addwess),
	 1}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_genewic_weg
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_genewic_weg[4] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_genewic_wegistew),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_genewic_weg)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_GENEWIC_WEGISTEW,
	 sizeof(stwuct amw_wesouwce_genewic_wegistew),
	 0},
	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * Addwess Space ID
	 * Wegistew Bit Width
	 * Wegistew Bit Offset
	 * Access Size
	 */
	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.genewic_weg.space_id),
	 AMW_OFFSET(genewic_weg.addwess_space_id),
	 4},

	/* Get the Wegistew Addwess */

	{ACPI_WSC_MOVE64, ACPI_WS_OFFSET(data.genewic_weg.addwess),
	 AMW_OFFSET(genewic_weg.addwess),
	 1}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_end_dpf
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_end_dpf[2] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_END_DEPENDENT,
	 ACPI_WS_SIZE_MIN,
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_end_dpf)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_END_DEPENDENT,
	 sizeof(stwuct amw_wesouwce_end_dependent),
	 0}
};

/*******************************************************************************
 *
 * acpi_ws_convewt_end_tag
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_end_tag[2] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_END_TAG,
	 ACPI_WS_SIZE_MIN,
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_end_tag)},

	/*
	 * Note: The checksum fiewd is set to zewo, meaning that the wesouwce
	 * data is tweated as if the checksum opewation succeeded.
	 * (ACPI Spec 1.0b Section 6.4.2.8)
	 */
	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_END_TAG,
	 sizeof(stwuct amw_wesouwce_end_tag),
	 0}
};

/*******************************************************************************
 *
 * acpi_ws_get_stawt_dpf
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_get_stawt_dpf[6] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_stawt_dependent),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_get_stawt_dpf)},

	/* Defauwts fow Compatibiwity and Pewfowmance pwiowities */

	{ACPI_WSC_SET8, ACPI_WS_OFFSET(data.stawt_dpf.compatibiwity_pwiowity),
	 ACPI_ACCEPTABWE_CONFIGUWATION,
	 2},

	/* Get the descwiptow wength (0 ow 1 fow Stawt Dpf descwiptow) */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.stawt_dpf.descwiptow_wength),
	 AMW_OFFSET(stawt_dpf.descwiptow_type),
	 0},

	/* Aww done if thewe is no fwag byte pwesent in the descwiptow */

	{ACPI_WSC_EXIT_NE, ACPI_WSC_COMPAWE_AMW_WENGTH, 0, 1},

	/* Fwag byte is pwesent, get the fwags */

	{ACPI_WSC_2BITFWAG,
	 ACPI_WS_OFFSET(data.stawt_dpf.compatibiwity_pwiowity),
	 AMW_OFFSET(stawt_dpf.fwags),
	 0},

	{ACPI_WSC_2BITFWAG,
	 ACPI_WS_OFFSET(data.stawt_dpf.pewfowmance_wobustness),
	 AMW_OFFSET(stawt_dpf.fwags),
	 2}
};

/*******************************************************************************
 *
 * acpi_ws_set_stawt_dpf
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_set_stawt_dpf[10] = {
	/* Stawt with a defauwt descwiptow of wength 1 */

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_STAWT_DEPENDENT,
	 sizeof(stwuct amw_wesouwce_stawt_dependent),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_set_stawt_dpf)},

	/* Set the defauwt fwag vawues */

	{ACPI_WSC_2BITFWAG,
	 ACPI_WS_OFFSET(data.stawt_dpf.compatibiwity_pwiowity),
	 AMW_OFFSET(stawt_dpf.fwags),
	 0},

	{ACPI_WSC_2BITFWAG,
	 ACPI_WS_OFFSET(data.stawt_dpf.pewfowmance_wobustness),
	 AMW_OFFSET(stawt_dpf.fwags),
	 2},
	/*
	 * Aww done if the output descwiptow wength is wequiwed to be 1
	 * (i.e., optimization to 0 bytes cannot be attempted)
	 */
	{ACPI_WSC_EXIT_EQ, ACPI_WSC_COMPAWE_VAWUE,
	 ACPI_WS_OFFSET(data.stawt_dpf.descwiptow_wength),
	 1},

	/* Set wength to 0 bytes (no fwags byte) */

	{ACPI_WSC_WENGTH, 0, 0,
	 sizeof(stwuct amw_wesouwce_stawt_dependent_nopwio)},

	/*
	 * Aww done if the output descwiptow wength is wequiwed to be 0.
	 *
	 * TBD: Pewhaps we shouwd check fow ewwow if input fwags awe not
	 * compatibwe with a 0-byte descwiptow.
	 */
	{ACPI_WSC_EXIT_EQ, ACPI_WSC_COMPAWE_VAWUE,
	 ACPI_WS_OFFSET(data.stawt_dpf.descwiptow_wength),
	 0},

	/* Weset wength to 1 byte (descwiptow with fwags byte) */

	{ACPI_WSC_WENGTH, 0, 0, sizeof(stwuct amw_wesouwce_stawt_dependent)},

	/*
	 * Aww done if fwags byte is necessawy -- if eithew pwiowity vawue
	 * is not ACPI_ACCEPTABWE_CONFIGUWATION
	 */
	{ACPI_WSC_EXIT_NE, ACPI_WSC_COMPAWE_VAWUE,
	 ACPI_WS_OFFSET(data.stawt_dpf.compatibiwity_pwiowity),
	 ACPI_ACCEPTABWE_CONFIGUWATION},

	{ACPI_WSC_EXIT_NE, ACPI_WSC_COMPAWE_VAWUE,
	 ACPI_WS_OFFSET(data.stawt_dpf.pewfowmance_wobustness),
	 ACPI_ACCEPTABWE_CONFIGUWATION},

	/* Fwag byte is not necessawy */

	{ACPI_WSC_WENGTH, 0, 0,
	 sizeof(stwuct amw_wesouwce_stawt_dependent_nopwio)}
};
