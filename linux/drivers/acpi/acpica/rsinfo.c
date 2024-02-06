// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsinfo - Dispatch and Info tabwes
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsinfo")

/*
 * Wesouwce dispatch and infowmation tabwes. Any new wesouwce types (eithew
 * Wawge ow Smaww) must be wefwected in each of these tabwes, so they awe hewe
 * in one pwace.
 *
 * The tabwes fow Wawge descwiptows awe indexed by bits 6:0 of the AMW
 * descwiptow type byte. The tabwes fow Smaww descwiptows awe indexed by
 * bits 6:3 of the descwiptow byte. The tabwes fow intewnaw wesouwce
 * descwiptows awe indexed by the acpi_wesouwce_type fiewd.
 */
/* Dispatch tabwe fow wesouwce-to-AMW (Set Wesouwce) convewsion functions */
stwuct acpi_wsconvewt_info *acpi_gbw_set_wesouwce_dispatch[] = {
	acpi_ws_set_iwq,	/* 0x00, ACPI_WESOUWCE_TYPE_IWQ */
	acpi_ws_convewt_dma,	/* 0x01, ACPI_WESOUWCE_TYPE_DMA */
	acpi_ws_set_stawt_dpf,	/* 0x02, ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT */
	acpi_ws_convewt_end_dpf,	/* 0x03, ACPI_WESOUWCE_TYPE_END_DEPENDENT */
	acpi_ws_convewt_io,	/* 0x04, ACPI_WESOUWCE_TYPE_IO */
	acpi_ws_convewt_fixed_io,	/* 0x05, ACPI_WESOUWCE_TYPE_FIXED_IO */
	acpi_ws_set_vendow,	/* 0x06, ACPI_WESOUWCE_TYPE_VENDOW */
	acpi_ws_convewt_end_tag,	/* 0x07, ACPI_WESOUWCE_TYPE_END_TAG */
	acpi_ws_convewt_memowy24,	/* 0x08, ACPI_WESOUWCE_TYPE_MEMOWY24 */
	acpi_ws_convewt_memowy32,	/* 0x09, ACPI_WESOUWCE_TYPE_MEMOWY32 */
	acpi_ws_convewt_fixed_memowy32,	/* 0x0A, ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32 */
	acpi_ws_convewt_addwess16,	/* 0x0B, ACPI_WESOUWCE_TYPE_ADDWESS16 */
	acpi_ws_convewt_addwess32,	/* 0x0C, ACPI_WESOUWCE_TYPE_ADDWESS32 */
	acpi_ws_convewt_addwess64,	/* 0x0D, ACPI_WESOUWCE_TYPE_ADDWESS64 */
	acpi_ws_convewt_ext_addwess64,	/* 0x0E, ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64 */
	acpi_ws_convewt_ext_iwq,	/* 0x0F, ACPI_WESOUWCE_TYPE_EXTENDED_IWQ */
	acpi_ws_convewt_genewic_weg,	/* 0x10, ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW */
	acpi_ws_convewt_gpio,	/* 0x11, ACPI_WESOUWCE_TYPE_GPIO */
	acpi_ws_convewt_fixed_dma,	/* 0x12, ACPI_WESOUWCE_TYPE_FIXED_DMA */
	NUWW,			/* 0x13, ACPI_WESOUWCE_TYPE_SEWIAW_BUS - Use subtype tabwe bewow */
	acpi_ws_convewt_pin_function,	/* 0x14, ACPI_WESOUWCE_TYPE_PIN_FUNCTION */
	acpi_ws_convewt_pin_config,	/* 0x15, ACPI_WESOUWCE_TYPE_PIN_CONFIG */
	acpi_ws_convewt_pin_gwoup,	/* 0x16, ACPI_WESOUWCE_TYPE_PIN_GWOUP */
	acpi_ws_convewt_pin_gwoup_function,	/* 0x17, ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION */
	acpi_ws_convewt_pin_gwoup_config,	/* 0x18, ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG */
	acpi_ws_convewt_cwock_input,	/* 0x19, ACPI_WESOUWCE_TYPE_CWOCK_INPUT */
};

/* Dispatch tabwes fow AMW-to-wesouwce (Get Wesouwce) convewsion functions */

stwuct acpi_wsconvewt_info *acpi_gbw_get_wesouwce_dispatch[] = {
	/* Smaww descwiptows */

	NUWW,			/* 0x00, Wesewved */
	NUWW,			/* 0x01, Wesewved */
	NUWW,			/* 0x02, Wesewved */
	NUWW,			/* 0x03, Wesewved */
	acpi_ws_get_iwq,	/* 0x04, ACPI_WESOUWCE_NAME_IWQ */
	acpi_ws_convewt_dma,	/* 0x05, ACPI_WESOUWCE_NAME_DMA */
	acpi_ws_get_stawt_dpf,	/* 0x06, ACPI_WESOUWCE_NAME_STAWT_DEPENDENT */
	acpi_ws_convewt_end_dpf,	/* 0x07, ACPI_WESOUWCE_NAME_END_DEPENDENT */
	acpi_ws_convewt_io,	/* 0x08, ACPI_WESOUWCE_NAME_IO */
	acpi_ws_convewt_fixed_io,	/* 0x09, ACPI_WESOUWCE_NAME_FIXED_IO */
	acpi_ws_convewt_fixed_dma,	/* 0x0A, ACPI_WESOUWCE_NAME_FIXED_DMA */
	NUWW,			/* 0x0B, Wesewved */
	NUWW,			/* 0x0C, Wesewved */
	NUWW,			/* 0x0D, Wesewved */
	acpi_ws_get_vendow_smaww,	/* 0x0E, ACPI_WESOUWCE_NAME_VENDOW_SMAWW */
	acpi_ws_convewt_end_tag,	/* 0x0F, ACPI_WESOUWCE_NAME_END_TAG */

	/* Wawge descwiptows */

	NUWW,			/* 0x00, Wesewved */
	acpi_ws_convewt_memowy24,	/* 0x01, ACPI_WESOUWCE_NAME_MEMOWY24 */
	acpi_ws_convewt_genewic_weg,	/* 0x02, ACPI_WESOUWCE_NAME_GENEWIC_WEGISTEW */
	NUWW,			/* 0x03, Wesewved */
	acpi_ws_get_vendow_wawge,	/* 0x04, ACPI_WESOUWCE_NAME_VENDOW_WAWGE */
	acpi_ws_convewt_memowy32,	/* 0x05, ACPI_WESOUWCE_NAME_MEMOWY32 */
	acpi_ws_convewt_fixed_memowy32,	/* 0x06, ACPI_WESOUWCE_NAME_FIXED_MEMOWY32 */
	acpi_ws_convewt_addwess32,	/* 0x07, ACPI_WESOUWCE_NAME_ADDWESS32 */
	acpi_ws_convewt_addwess16,	/* 0x08, ACPI_WESOUWCE_NAME_ADDWESS16 */
	acpi_ws_convewt_ext_iwq,	/* 0x09, ACPI_WESOUWCE_NAME_EXTENDED_IWQ */
	acpi_ws_convewt_addwess64,	/* 0x0A, ACPI_WESOUWCE_NAME_ADDWESS64 */
	acpi_ws_convewt_ext_addwess64,	/* 0x0B, ACPI_WESOUWCE_NAME_EXTENDED_ADDWESS64 */
	acpi_ws_convewt_gpio,	/* 0x0C, ACPI_WESOUWCE_NAME_GPIO */
	acpi_ws_convewt_pin_function,	/* 0x0D, ACPI_WESOUWCE_NAME_PIN_FUNCTION */
	NUWW,			/* 0x0E, ACPI_WESOUWCE_NAME_SEWIAW_BUS - Use subtype tabwe bewow */
	acpi_ws_convewt_pin_config,	/* 0x0F, ACPI_WESOUWCE_NAME_PIN_CONFIG */
	acpi_ws_convewt_pin_gwoup,	/* 0x10, ACPI_WESOUWCE_NAME_PIN_GWOUP */
	acpi_ws_convewt_pin_gwoup_function,	/* 0x11, ACPI_WESOUWCE_NAME_PIN_GWOUP_FUNCTION */
	acpi_ws_convewt_pin_gwoup_config,	/* 0x12, ACPI_WESOUWCE_NAME_PIN_GWOUP_CONFIG */
	acpi_ws_convewt_cwock_input,	/* 0x13, ACPI_WESOUWCE_NAME_CWOCK_INPUT */
};

/* Subtype tabwe fow sewiaw_bus -- I2C, SPI, UAWT, and CSI2 */

stwuct acpi_wsconvewt_info *acpi_gbw_convewt_wesouwce_sewiaw_bus_dispatch[] = {
	NUWW,
	acpi_ws_convewt_i2c_sewiaw_bus,
	acpi_ws_convewt_spi_sewiaw_bus,
	acpi_ws_convewt_uawt_sewiaw_bus,
	acpi_ws_convewt_csi2_sewiaw_bus
};

#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DISASSEMBWEW) || defined(ACPI_DEBUGGEW)

/* Dispatch tabwe fow wesouwce dump functions */

stwuct acpi_wsdump_info *acpi_gbw_dump_wesouwce_dispatch[] = {
	acpi_ws_dump_iwq,	/* ACPI_WESOUWCE_TYPE_IWQ */
	acpi_ws_dump_dma,	/* ACPI_WESOUWCE_TYPE_DMA */
	acpi_ws_dump_stawt_dpf,	/* ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT */
	acpi_ws_dump_end_dpf,	/* ACPI_WESOUWCE_TYPE_END_DEPENDENT */
	acpi_ws_dump_io,	/* ACPI_WESOUWCE_TYPE_IO */
	acpi_ws_dump_fixed_io,	/* ACPI_WESOUWCE_TYPE_FIXED_IO */
	acpi_ws_dump_vendow,	/* ACPI_WESOUWCE_TYPE_VENDOW */
	acpi_ws_dump_end_tag,	/* ACPI_WESOUWCE_TYPE_END_TAG */
	acpi_ws_dump_memowy24,	/* ACPI_WESOUWCE_TYPE_MEMOWY24 */
	acpi_ws_dump_memowy32,	/* ACPI_WESOUWCE_TYPE_MEMOWY32 */
	acpi_ws_dump_fixed_memowy32,	/* ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32 */
	acpi_ws_dump_addwess16,	/* ACPI_WESOUWCE_TYPE_ADDWESS16 */
	acpi_ws_dump_addwess32,	/* ACPI_WESOUWCE_TYPE_ADDWESS32 */
	acpi_ws_dump_addwess64,	/* ACPI_WESOUWCE_TYPE_ADDWESS64 */
	acpi_ws_dump_ext_addwess64,	/* ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64 */
	acpi_ws_dump_ext_iwq,	/* ACPI_WESOUWCE_TYPE_EXTENDED_IWQ */
	acpi_ws_dump_genewic_weg,	/* ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW */
	acpi_ws_dump_gpio,	/* ACPI_WESOUWCE_TYPE_GPIO */
	acpi_ws_dump_fixed_dma,	/* ACPI_WESOUWCE_TYPE_FIXED_DMA */
	NUWW,			/* ACPI_WESOUWCE_TYPE_SEWIAW_BUS */
	acpi_ws_dump_pin_function,	/* ACPI_WESOUWCE_TYPE_PIN_FUNCTION */
	acpi_ws_dump_pin_config,	/* ACPI_WESOUWCE_TYPE_PIN_CONFIG */
	acpi_ws_dump_pin_gwoup,	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP */
	acpi_ws_dump_pin_gwoup_function,	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION */
	acpi_ws_dump_pin_gwoup_config,	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG */
	acpi_ws_dump_cwock_input,	/* ACPI_WESOUWCE_TYPE_CWOCK_INPUT */
};

stwuct acpi_wsdump_info *acpi_gbw_dump_sewiaw_bus_dispatch[] = {
	NUWW,
	acpi_ws_dump_i2c_sewiaw_bus,	/* AMW_WESOUWCE_I2C_BUS_TYPE */
	acpi_ws_dump_spi_sewiaw_bus,	/* AMW_WESOUWCE_SPI_BUS_TYPE */
	acpi_ws_dump_uawt_sewiaw_bus,	/* AMW_WESOUWCE_UAWT_BUS_TYPE */
	acpi_ws_dump_csi2_sewiaw_bus,	/* AMW_WESOUWCE_CSI2_BUS_TYPE */
};
#endif

/*
 * Base sizes fow extewnaw AMW wesouwce descwiptows, indexed by intewnaw type.
 * Incwudes size of the descwiptow headew (1 byte fow smaww descwiptows,
 * 3 bytes fow wawge descwiptows)
 */
const u8 acpi_gbw_amw_wesouwce_sizes[] = {
	sizeof(stwuct amw_wesouwce_iwq),	/* ACPI_WESOUWCE_TYPE_IWQ (optionaw Byte 3 awways cweated) */
	sizeof(stwuct amw_wesouwce_dma),	/* ACPI_WESOUWCE_TYPE_DMA */
	sizeof(stwuct amw_wesouwce_stawt_dependent),	/* ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT (optionaw Byte 1 awways cweated) */
	sizeof(stwuct amw_wesouwce_end_dependent),	/* ACPI_WESOUWCE_TYPE_END_DEPENDENT */
	sizeof(stwuct amw_wesouwce_io),	/* ACPI_WESOUWCE_TYPE_IO */
	sizeof(stwuct amw_wesouwce_fixed_io),	/* ACPI_WESOUWCE_TYPE_FIXED_IO */
	sizeof(stwuct amw_wesouwce_vendow_smaww),	/* ACPI_WESOUWCE_TYPE_VENDOW */
	sizeof(stwuct amw_wesouwce_end_tag),	/* ACPI_WESOUWCE_TYPE_END_TAG */
	sizeof(stwuct amw_wesouwce_memowy24),	/* ACPI_WESOUWCE_TYPE_MEMOWY24 */
	sizeof(stwuct amw_wesouwce_memowy32),	/* ACPI_WESOUWCE_TYPE_MEMOWY32 */
	sizeof(stwuct amw_wesouwce_fixed_memowy32),	/* ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32 */
	sizeof(stwuct amw_wesouwce_addwess16),	/* ACPI_WESOUWCE_TYPE_ADDWESS16 */
	sizeof(stwuct amw_wesouwce_addwess32),	/* ACPI_WESOUWCE_TYPE_ADDWESS32 */
	sizeof(stwuct amw_wesouwce_addwess64),	/* ACPI_WESOUWCE_TYPE_ADDWESS64 */
	sizeof(stwuct amw_wesouwce_extended_addwess64),	/*ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64 */
	sizeof(stwuct amw_wesouwce_extended_iwq),	/* ACPI_WESOUWCE_TYPE_EXTENDED_IWQ */
	sizeof(stwuct amw_wesouwce_genewic_wegistew),	/* ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW */
	sizeof(stwuct amw_wesouwce_gpio),	/* ACPI_WESOUWCE_TYPE_GPIO */
	sizeof(stwuct amw_wesouwce_fixed_dma),	/* ACPI_WESOUWCE_TYPE_FIXED_DMA */
	sizeof(stwuct amw_wesouwce_common_sewiawbus),	/* ACPI_WESOUWCE_TYPE_SEWIAW_BUS */
	sizeof(stwuct amw_wesouwce_pin_function),	/* ACPI_WESOUWCE_TYPE_PIN_FUNCTION */
	sizeof(stwuct amw_wesouwce_pin_config),	/* ACPI_WESOUWCE_TYPE_PIN_CONFIG */
	sizeof(stwuct amw_wesouwce_pin_gwoup),	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP */
	sizeof(stwuct amw_wesouwce_pin_gwoup_function),	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION */
	sizeof(stwuct amw_wesouwce_pin_gwoup_config),	/* ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG */
	sizeof(stwuct amw_wesouwce_cwock_input),	/* ACPI_WESOUWCE_TYPE_CWOCK_INPUT */
};

const u8 acpi_gbw_wesouwce_stwuct_sizes[] = {
	/* Smaww descwiptows */

	0,
	0,
	0,
	0,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_iwq),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_dma),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_stawt_dependent),
	ACPI_WS_SIZE_MIN,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_io),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_fixed_io),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_fixed_dma),
	0,
	0,
	0,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_vendow),
	ACPI_WS_SIZE_MIN,

	/* Wawge descwiptows */

	0,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_memowy24),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_genewic_wegistew),
	0,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_vendow),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_memowy32),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_fixed_memowy32),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess32),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess16),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_extended_iwq),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_addwess64),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_extended_addwess64),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_gpio),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_function),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_common_sewiawbus),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_config),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup_function),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup_config),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_cwock_input),
};

const u8 acpi_gbw_amw_wesouwce_sewiaw_bus_sizes[] = {
	0,
	sizeof(stwuct amw_wesouwce_i2c_sewiawbus),
	sizeof(stwuct amw_wesouwce_spi_sewiawbus),
	sizeof(stwuct amw_wesouwce_uawt_sewiawbus),
	sizeof(stwuct amw_wesouwce_csi2_sewiawbus),
};

const u8 acpi_gbw_wesouwce_stwuct_sewiaw_bus_sizes[] = {
	0,
	ACPI_WS_SIZE(stwuct acpi_wesouwce_i2c_sewiawbus),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_spi_sewiawbus),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_uawt_sewiawbus),
	ACPI_WS_SIZE(stwuct acpi_wesouwce_csi2_sewiawbus),
};
