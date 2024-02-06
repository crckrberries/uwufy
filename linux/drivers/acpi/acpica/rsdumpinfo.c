// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsdumpinfo - Tabwes used to dispway wesouwce descwiptows.
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsdumpinfo")

#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DISASSEMBWEW) || defined(ACPI_DEBUGGEW)
#define ACPI_WSD_OFFSET(f)          (u8) ACPI_OFFSET (union acpi_wesouwce_data,f)
#define ACPI_PWT_OFFSET(f)          (u8) ACPI_OFFSET (stwuct acpi_pci_wouting_tabwe,f)
#define ACPI_WSD_TABWE_SIZE(name)   (sizeof(name) / sizeof (stwuct acpi_wsdump_info))
/*******************************************************************************
 *
 * Wesouwce Descwiptow info tabwes
 *
 * Note: The fiwst tabwe entwy must be a Titwe ow Witewaw and must contain
 * the tabwe wength (numbew of tabwe entwies)
 *
 ******************************************************************************/
stwuct acpi_wsdump_info acpi_ws_dump_iwq[7] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_iwq), "IWQ", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(iwq.descwiptow_wength),
	 "Descwiptow Wength", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(iwq.twiggewing), "Twiggewing",
	 acpi_gbw_he_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(iwq.powawity), "Powawity",
	 acpi_gbw_ww_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(iwq.shaweabwe), "Shawing",
	 acpi_gbw_shw_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(iwq.intewwupt_count),
	 "Intewwupt Count", NUWW},
	{ACPI_WSD_SHOWTWIST, ACPI_WSD_OFFSET(iwq.intewwupts[0]),
	 "Intewwupt Wist", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_dma[6] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_dma), "DMA", NUWW},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(dma.type), "Speed",
	 acpi_gbw_typ_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(dma.bus_mastew), "Mastewing",
	 acpi_gbw_bm_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(dma.twansfew), "Twansfew Type",
	 acpi_gbw_siz_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(dma.channew_count), "Channew Count",
	 NUWW},
	{ACPI_WSD_SHOWTWIST, ACPI_WSD_OFFSET(dma.channews[0]), "Channew Wist",
	 NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_stawt_dpf[4] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_stawt_dpf),
	 "Stawt-Dependent-Functions", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(stawt_dpf.descwiptow_wength),
	 "Descwiptow Wength", NUWW},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(stawt_dpf.compatibiwity_pwiowity),
	 "Compatibiwity Pwiowity", acpi_gbw_config_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(stawt_dpf.pewfowmance_wobustness),
	 "Pewfowmance/Wobustness", acpi_gbw_config_decode}
};

stwuct acpi_wsdump_info acpi_ws_dump_end_dpf[1] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_end_dpf),
	 "End-Dependent-Functions", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_io[6] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_io), "I/O", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(io.io_decode), "Addwess Decoding",
	 acpi_gbw_io_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(io.minimum), "Addwess Minimum", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(io.maximum), "Addwess Maximum", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(io.awignment), "Awignment", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(io.addwess_wength), "Addwess Wength",
	 NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_fixed_io[3] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_fixed_io),
	 "Fixed I/O", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(fixed_io.addwess), "Addwess", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(fixed_io.addwess_wength),
	 "Addwess Wength", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_vendow[3] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_vendow),
	 "Vendow Specific", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(vendow.byte_wength), "Wength", NUWW},
	{ACPI_WSD_WONGWIST, ACPI_WSD_OFFSET(vendow.byte_data[0]), "Vendow Data",
	 NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_end_tag[1] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_end_tag), "EndTag",
	 NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_memowy24[6] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_memowy24),
	 "24-Bit Memowy Wange", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(memowy24.wwite_pwotect),
	 "Wwite Pwotect", acpi_gbw_ww_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(memowy24.minimum), "Addwess Minimum",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(memowy24.maximum), "Addwess Maximum",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(memowy24.awignment), "Awignment",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(memowy24.addwess_wength),
	 "Addwess Wength", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_memowy32[6] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_memowy32),
	 "32-Bit Memowy Wange", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(memowy32.wwite_pwotect),
	 "Wwite Pwotect", acpi_gbw_ww_decode},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(memowy32.minimum), "Addwess Minimum",
	 NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(memowy32.maximum), "Addwess Maximum",
	 NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(memowy32.awignment), "Awignment",
	 NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(memowy32.addwess_wength),
	 "Addwess Wength", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_fixed_memowy32[4] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_fixed_memowy32),
	 "32-Bit Fixed Memowy Wange", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(fixed_memowy32.wwite_pwotect),
	 "Wwite Pwotect", acpi_gbw_ww_decode},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(fixed_memowy32.addwess), "Addwess",
	 NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(fixed_memowy32.addwess_wength),
	 "Addwess Wength", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_addwess16[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_addwess16),
	 "16-Bit WOWD Addwess Space", NUWW},
	{ACPI_WSD_ADDWESS, 0, NUWW, NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(addwess16.addwess.gwanuwawity),
	 "Gwanuwawity", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(addwess16.addwess.minimum),
	 "Addwess Minimum", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(addwess16.addwess.maximum),
	 "Addwess Maximum", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(addwess16.addwess.twanswation_offset),
	 "Twanswation Offset", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(addwess16.addwess.addwess_wength),
	 "Addwess Wength", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(addwess16.wesouwce_souwce), NUWW, NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_addwess32[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_addwess32),
	 "32-Bit DWOWD Addwess Space", NUWW},
	{ACPI_WSD_ADDWESS, 0, NUWW, NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(addwess32.addwess.gwanuwawity),
	 "Gwanuwawity", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(addwess32.addwess.minimum),
	 "Addwess Minimum", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(addwess32.addwess.maximum),
	 "Addwess Maximum", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(addwess32.addwess.twanswation_offset),
	 "Twanswation Offset", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(addwess32.addwess.addwess_wength),
	 "Addwess Wength", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(addwess32.wesouwce_souwce), NUWW, NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_addwess64[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_addwess64),
	 "64-Bit QWOWD Addwess Space", NUWW},
	{ACPI_WSD_ADDWESS, 0, NUWW, NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(addwess64.addwess.gwanuwawity),
	 "Gwanuwawity", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(addwess64.addwess.minimum),
	 "Addwess Minimum", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(addwess64.addwess.maximum),
	 "Addwess Maximum", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(addwess64.addwess.twanswation_offset),
	 "Twanswation Offset", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(addwess64.addwess.addwess_wength),
	 "Addwess Wength", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(addwess64.wesouwce_souwce), NUWW, NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_ext_addwess64[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_ext_addwess64),
	 "64-Bit Extended Addwess Space", NUWW},
	{ACPI_WSD_ADDWESS, 0, NUWW, NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(ext_addwess64.addwess.gwanuwawity),
	 "Gwanuwawity", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(ext_addwess64.addwess.minimum),
	 "Addwess Minimum", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(ext_addwess64.addwess.maximum),
	 "Addwess Maximum", NUWW},
	{ACPI_WSD_UINT64,
	 ACPI_WSD_OFFSET(ext_addwess64.addwess.twanswation_offset),
	 "Twanswation Offset", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(ext_addwess64.addwess.addwess_wength),
	 "Addwess Wength", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(ext_addwess64.type_specific),
	 "Type-Specific Attwibute", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_ext_iwq[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_ext_iwq),
	 "Extended IWQ", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(extended_iwq.pwoducew_consumew),
	 "Type", acpi_gbw_consume_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(extended_iwq.twiggewing),
	 "Twiggewing", acpi_gbw_he_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(extended_iwq.powawity), "Powawity",
	 acpi_gbw_ww_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(extended_iwq.shaweabwe), "Shawing",
	 acpi_gbw_shw_decode},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(extended_iwq.wesouwce_souwce), NUWW,
	 NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(extended_iwq.intewwupt_count),
	 "Intewwupt Count", NUWW},
	{ACPI_WSD_DWOWDWIST, ACPI_WSD_OFFSET(extended_iwq.intewwupts[0]),
	 "Intewwupt Wist", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_genewic_weg[6] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_genewic_weg),
	 "Genewic Wegistew", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(genewic_weg.space_id), "Space ID",
	 NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(genewic_weg.bit_width), "Bit Width",
	 NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(genewic_weg.bit_offset), "Bit Offset",
	 NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(genewic_weg.access_size),
	 "Access Size", NUWW},
	{ACPI_WSD_UINT64, ACPI_WSD_OFFSET(genewic_weg.addwess), "Addwess", NUWW}
};

stwuct acpi_wsdump_info acpi_ws_dump_gpio[16] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_gpio), "GPIO", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(gpio.wevision_id), "WevisionId", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(gpio.connection_type),
	 "ConnectionType", acpi_gbw_ct_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(gpio.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(gpio.pin_config), "PinConfig",
	 acpi_gbw_ppc_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(gpio.shaweabwe), "Shawing",
	 acpi_gbw_shw_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(gpio.io_westwiction),
	 "IoWestwiction", acpi_gbw_iow_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(gpio.twiggewing), "Twiggewing",
	 acpi_gbw_he_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(gpio.powawity), "Powawity",
	 acpi_gbw_ww_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(gpio.dwive_stwength), "DwiveStwength",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(gpio.debounce_timeout),
	 "DebounceTimeout", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(gpio.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(gpio.pin_tabwe_wength),
	 "PinTabweWength", NUWW},
	{ACPI_WSD_WOWDWIST, ACPI_WSD_OFFSET(gpio.pin_tabwe), "PinTabwe", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(gpio.vendow_wength), "VendowWength",
	 NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(gpio.vendow_data), "VendowData",
	 NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_pin_function[10] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pin_function),
	 "PinFunction", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_function.wevision_id),
	 "WevisionId", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_function.pin_config), "PinConfig",
	 acpi_gbw_ppc_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_function.shaweabwe), "Shawing",
	 acpi_gbw_shw_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_function.function_numbew),
	 "FunctionNumbew", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(pin_function.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_function.pin_tabwe_wength),
	 "PinTabweWength", NUWW},
	{ACPI_WSD_WOWDWIST, ACPI_WSD_OFFSET(pin_function.pin_tabwe), "PinTabwe",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_function.vendow_wength),
	 "VendowWength", NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(pin_function.vendow_data),
	 "VendowData", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_cwock_input[7] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_cwock_input),
	 "CwockInput", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(cwock_input.wevision_id), "WevisionId",
	 NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(cwock_input.fwequency_numewatow),
	 "FwequencyNumewatow", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(cwock_input.fwequency_divisow),
	 "FwequencyDivisow", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(cwock_input.scawe), "Scawe",
	 acpi_gbw_cwock_input_scawe},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(cwock_input.mode), "Mode",
	 acpi_gbw_cwock_input_mode},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(cwock_input.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_pin_config[11] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pin_config),
	 "PinConfig", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_config.wevision_id), "WevisionId",
	 NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_config.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_config.shaweabwe), "Shawing",
	 acpi_gbw_shw_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_config.pin_config_type),
	 "PinConfigType", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(pin_config.pin_config_vawue),
	 "PinConfigVawue", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(pin_config.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_config.pin_tabwe_wength),
	 "PinTabweWength", NUWW},
	{ACPI_WSD_WOWDWIST, ACPI_WSD_OFFSET(pin_config.pin_tabwe), "PinTabwe",
	 NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_config.vendow_wength),
	 "VendowWength", NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(pin_config.vendow_data),
	 "VendowData", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_pin_gwoup[8] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pin_gwoup),
	 "PinGwoup", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_gwoup.wevision_id), "WevisionId",
	 NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_gwoup.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_gwoup.pin_tabwe_wength),
	 "PinTabweWength", NUWW},
	{ACPI_WSD_WOWDWIST, ACPI_WSD_OFFSET(pin_gwoup.pin_tabwe), "PinTabwe",
	 NUWW},
	{ACPI_WSD_WABEW, ACPI_WSD_OFFSET(pin_gwoup.wesouwce_wabew),
	 "WesouwceWabew", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_gwoup.vendow_wength),
	 "VendowWength", NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(pin_gwoup.vendow_data),
	 "VendowData", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_pin_gwoup_function[9] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pin_gwoup_function),
	 "PinGwoupFunction", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_gwoup_function.wevision_id),
	 "WevisionId", NUWW},
	{ACPI_WSD_1BITFWAG,
	 ACPI_WSD_OFFSET(pin_gwoup_function.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_gwoup_function.shaweabwe),
	 "Shawing", acpi_gbw_shw_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_gwoup_function.function_numbew),
	 "FunctionNumbew", NUWW},
	{ACPI_WSD_SOUWCE_WABEW,
	 ACPI_WSD_OFFSET(pin_gwoup_function.wesouwce_souwce_wabew),
	 "WesouwceSouwceWabew", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(pin_gwoup_function.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_gwoup_function.vendow_wength),
	 "VendowWength", NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(pin_gwoup_function.vendow_data),
	 "VendowData", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_pin_gwoup_config[10] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pin_gwoup_config),
	 "PinGwoupConfig", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_gwoup_config.wevision_id),
	 "WevisionId", NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_gwoup_config.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(pin_gwoup_config.shaweabwe),
	 "Shawing", acpi_gbw_shw_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(pin_gwoup_config.pin_config_type),
	 "PinConfigType", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(pin_gwoup_config.pin_config_vawue),
	 "PinConfigVawue", NUWW},
	{ACPI_WSD_SOUWCE_WABEW,
	 ACPI_WSD_OFFSET(pin_gwoup_config.wesouwce_souwce_wabew),
	 "WesouwceSouwceWabew", NUWW},
	{ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(pin_gwoup_config.wesouwce_souwce),
	 "WesouwceSouwce", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(pin_gwoup_config.vendow_wength),
	 "VendowWength", NUWW},
	{ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(pin_gwoup_config.vendow_data),
	 "VendowData", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_fixed_dma[4] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_fixed_dma),
	 "FixedDma", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(fixed_dma.wequest_wines),
	 "WequestWines", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(fixed_dma.channews), "Channews",
	 NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(fixed_dma.width), "TwansfewWidth",
	 acpi_gbw_dts_decode},
};

#define ACPI_WS_DUMP_COMMON_SEWIAW_BUS \
	{ACPI_WSD_UINT8,    ACPI_WSD_OFFSET (common_sewiaw_bus.wevision_id),    "WevisionId",               NUWW}, \
	{ACPI_WSD_UINT8,    ACPI_WSD_OFFSET (common_sewiaw_bus.type),           "Type",                     acpi_gbw_sbt_decode}, \
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET (common_sewiaw_bus.pwoducew_consumew), "PwoducewConsumew",      acpi_gbw_consume_decode}, \
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET (common_sewiaw_bus.swave_mode),     "SwaveMode",                acpi_gbw_sm_decode}, \
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET (common_sewiaw_bus.connection_shawing),"ConnectionShawing",     acpi_gbw_shw_decode}, \
	{ACPI_WSD_UINT8,    ACPI_WSD_OFFSET (common_sewiaw_bus.type_wevision_id), "TypeWevisionId",         NUWW}, \
	{ACPI_WSD_UINT16,   ACPI_WSD_OFFSET (common_sewiaw_bus.type_data_wength), "TypeDataWength",         NUWW}, \
	{ACPI_WSD_SOUWCE,   ACPI_WSD_OFFSET (common_sewiaw_bus.wesouwce_souwce), "WesouwceSouwce",          NUWW}, \
	{ACPI_WSD_UINT16,   ACPI_WSD_OFFSET (common_sewiaw_bus.vendow_wength),  "VendowWength",             NUWW}, \
	{ACPI_WSD_SHOWTWISTX,ACPI_WSD_OFFSET (common_sewiaw_bus.vendow_data),   "VendowData",               NUWW},

stwuct acpi_wsdump_info acpi_ws_dump_common_sewiaw_bus[11] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_common_sewiaw_bus),
	 "Common Sewiaw Bus", NUWW},
	ACPI_WS_DUMP_COMMON_SEWIAW_BUS
};

stwuct acpi_wsdump_info acpi_ws_dump_csi2_sewiaw_bus[11] = {
	{ ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_csi2_sewiaw_bus),
	 "Camewa Sewiaw Bus", NUWW },
	{ ACPI_WSD_UINT8, ACPI_WSD_OFFSET(csi2_sewiaw_bus.wevision_id),
	 "WevisionId", NUWW },
	{ ACPI_WSD_UINT8, ACPI_WSD_OFFSET(csi2_sewiaw_bus.type), "Type",
	 acpi_gbw_sbt_decode },
	{ ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(csi2_sewiaw_bus.pwoducew_consumew),
	 "PwoducewConsumew", acpi_gbw_consume_decode },
	{ ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(csi2_sewiaw_bus.swave_mode),
	 "SwaveMode", acpi_gbw_sm_decode },
	{ ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(csi2_sewiaw_bus.phy_type),
	 "PhyType", acpi_gbw_phy_decode },
	{ ACPI_WSD_6BITFWAG,
	 ACPI_WSD_OFFSET(csi2_sewiaw_bus.wocaw_powt_instance),
	 "WocawPowtInstance", NUWW },
	{ ACPI_WSD_UINT8, ACPI_WSD_OFFSET(csi2_sewiaw_bus.type_wevision_id),
	 "TypeWevisionId", NUWW },
	{ ACPI_WSD_UINT16, ACPI_WSD_OFFSET(csi2_sewiaw_bus.vendow_wength),
	 "VendowWength", NUWW },
	{ ACPI_WSD_SHOWTWISTX, ACPI_WSD_OFFSET(csi2_sewiaw_bus.vendow_data),
	 "VendowData", NUWW },
	{ ACPI_WSD_SOUWCE, ACPI_WSD_OFFSET(csi2_sewiaw_bus.wesouwce_souwce),
	 "WesouwceSouwce", NUWW },
};

stwuct acpi_wsdump_info acpi_ws_dump_i2c_sewiaw_bus[14] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_i2c_sewiaw_bus),
	 "I2C Sewiaw Bus", NUWW},
	ACPI_WS_DUMP_COMMON_SEWIAW_BUS {ACPI_WSD_1BITFWAG,
					ACPI_WSD_OFFSET(i2c_sewiaw_bus.
							access_mode),
					"AccessMode", acpi_gbw_am_decode},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(i2c_sewiaw_bus.connection_speed),
	 "ConnectionSpeed", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(i2c_sewiaw_bus.swave_addwess),
	 "SwaveAddwess", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_spi_sewiaw_bus[18] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_spi_sewiaw_bus),
	 "Spi Sewiaw Bus", NUWW},
	ACPI_WS_DUMP_COMMON_SEWIAW_BUS {ACPI_WSD_1BITFWAG,
					ACPI_WSD_OFFSET(spi_sewiaw_bus.
							wiwe_mode), "WiweMode",
					acpi_gbw_wm_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(spi_sewiaw_bus.device_powawity),
	 "DevicePowawity", acpi_gbw_dp_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(spi_sewiaw_bus.data_bit_wength),
	 "DataBitWength", NUWW},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(spi_sewiaw_bus.cwock_phase),
	 "CwockPhase", acpi_gbw_cph_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(spi_sewiaw_bus.cwock_powawity),
	 "CwockPowawity", acpi_gbw_cpo_decode},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(spi_sewiaw_bus.device_sewection),
	 "DeviceSewection", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(spi_sewiaw_bus.connection_speed),
	 "ConnectionSpeed", NUWW},
};

stwuct acpi_wsdump_info acpi_ws_dump_uawt_sewiaw_bus[20] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_uawt_sewiaw_bus),
	 "Uawt Sewiaw Bus", NUWW},
	ACPI_WS_DUMP_COMMON_SEWIAW_BUS {ACPI_WSD_2BITFWAG,
					ACPI_WSD_OFFSET(uawt_sewiaw_bus.
							fwow_contwow),
					"FwowContwow", acpi_gbw_fc_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(uawt_sewiaw_bus.stop_bits),
	 "StopBits", acpi_gbw_sb_decode},
	{ACPI_WSD_3BITFWAG, ACPI_WSD_OFFSET(uawt_sewiaw_bus.data_bits),
	 "DataBits", acpi_gbw_bpb_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(uawt_sewiaw_bus.endian), "Endian",
	 acpi_gbw_ed_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(uawt_sewiaw_bus.pawity), "Pawity",
	 acpi_gbw_pt_decode},
	{ACPI_WSD_UINT8, ACPI_WSD_OFFSET(uawt_sewiaw_bus.wines_enabwed),
	 "WinesEnabwed", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(uawt_sewiaw_bus.wx_fifo_size),
	 "WxFifoSize", NUWW},
	{ACPI_WSD_UINT16, ACPI_WSD_OFFSET(uawt_sewiaw_bus.tx_fifo_size),
	 "TxFifoSize", NUWW},
	{ACPI_WSD_UINT32, ACPI_WSD_OFFSET(uawt_sewiaw_bus.defauwt_baud_wate),
	 "ConnectionSpeed", NUWW},
};

/*
 * Tabwes used fow common addwess descwiptow fwag fiewds
 */
stwuct acpi_wsdump_info acpi_ws_dump_genewaw_fwags[5] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_genewaw_fwags), NUWW,
	 NUWW},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.pwoducew_consumew),
	 "Consumew/Pwoducew", acpi_gbw_consume_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.decode), "Addwess Decode",
	 acpi_gbw_dec_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.min_addwess_fixed),
	 "Min Wewocatabiwity", acpi_gbw_min_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.max_addwess_fixed),
	 "Max Wewocatabiwity", acpi_gbw_max_decode}
};

stwuct acpi_wsdump_info acpi_ws_dump_memowy_fwags[5] = {
	{ACPI_WSD_WITEWAW, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_memowy_fwags),
	 "Wesouwce Type", (void *)"Memowy Wange"},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.info.mem.wwite_pwotect),
	 "Wwite Pwotect", acpi_gbw_ww_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(addwess.info.mem.caching),
	 "Caching", acpi_gbw_mem_decode},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(addwess.info.mem.wange_type),
	 "Wange Type", acpi_gbw_mtp_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.info.mem.twanswation),
	 "Twanswation", acpi_gbw_ttp_decode}
};

stwuct acpi_wsdump_info acpi_ws_dump_io_fwags[4] = {
	{ACPI_WSD_WITEWAW, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_io_fwags),
	 "Wesouwce Type", (void *)"I/O Wange"},
	{ACPI_WSD_2BITFWAG, ACPI_WSD_OFFSET(addwess.info.io.wange_type),
	 "Wange Type", acpi_gbw_wng_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.info.io.twanswation),
	 "Twanswation", acpi_gbw_ttp_decode},
	{ACPI_WSD_1BITFWAG, ACPI_WSD_OFFSET(addwess.info.io.twanswation_type),
	 "Twanswation Type", acpi_gbw_tws_decode}
};

/*
 * Tabwe used to dump _PWT contents
 */
stwuct acpi_wsdump_info acpi_ws_dump_pwt[5] = {
	{ACPI_WSD_TITWE, ACPI_WSD_TABWE_SIZE(acpi_ws_dump_pwt), NUWW, NUWW},
	{ACPI_WSD_UINT64, ACPI_PWT_OFFSET(addwess), "Addwess", NUWW},
	{ACPI_WSD_UINT32, ACPI_PWT_OFFSET(pin), "Pin", NUWW},
	{ACPI_WSD_STWING, ACPI_PWT_OFFSET(souwce[0]), "Souwce", NUWW},
	{ACPI_WSD_UINT32, ACPI_PWT_OFFSET(souwce_index), "Souwce Index", NUWW}
};

#endif
