// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wssewiaw - GPIO/sewiaw_bus wesouwce descwiptows
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wssewiaw")

/*******************************************************************************
 *
 * acpi_ws_convewt_gpio
 *
 ******************************************************************************/
stwuct acpi_wsconvewt_info acpi_ws_convewt_gpio[18] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_GPIO,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_gpio),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_gpio)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_GPIO,
	 sizeof(stwuct amw_wesouwce_gpio),
	 0},

	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * wevision_id
	 * connection_type
	 */
	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.gpio.wevision_id),
	 AMW_OFFSET(gpio.wevision_id),
	 2},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.gpio.pwoducew_consumew),
	 AMW_OFFSET(gpio.fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.gpio.shaweabwe),
	 AMW_OFFSET(gpio.int_fwags),
	 3},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.gpio.wake_capabwe),
	 AMW_OFFSET(gpio.int_fwags),
	 4},

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.gpio.io_westwiction),
	 AMW_OFFSET(gpio.int_fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.gpio.twiggewing),
	 AMW_OFFSET(gpio.int_fwags),
	 0},

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.gpio.powawity),
	 AMW_OFFSET(gpio.int_fwags),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.gpio.pin_config),
	 AMW_OFFSET(gpio.pin_config),
	 1},

	/*
	 * These fiewds awe contiguous in both the souwce and destination:
	 * dwive_stwength
	 * debounce_timeout
	 */
	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.gpio.dwive_stwength),
	 AMW_OFFSET(gpio.dwive_stwength),
	 2},

	/* Pin Tabwe */

	{ACPI_WSC_COUNT_GPIO_PIN, ACPI_WS_OFFSET(data.gpio.pin_tabwe_wength),
	 AMW_OFFSET(gpio.pin_tabwe_offset),
	 AMW_OFFSET(gpio.wes_souwce_offset)},

	{ACPI_WSC_MOVE_GPIO_PIN, ACPI_WS_OFFSET(data.gpio.pin_tabwe),
	 AMW_OFFSET(gpio.pin_tabwe_offset),
	 0},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.gpio.wesouwce_souwce.index),
	 AMW_OFFSET(gpio.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.gpio.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(gpio.wes_souwce_offset),
	 AMW_OFFSET(gpio.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.gpio.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(gpio.wes_souwce_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN, ACPI_WS_OFFSET(data.gpio.vendow_wength),
	 AMW_OFFSET(gpio.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES, ACPI_WS_OFFSET(data.gpio.vendow_data),
	 AMW_OFFSET(gpio.vendow_offset),
	 0},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_cwock_input
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_cwock_input[8] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_CWOCK_INPUT,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_cwock_input),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_cwock_input)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_CWOCK_INPUT,
	 sizeof(stwuct amw_wesouwce_cwock_input),
	 0}
	,

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.cwock_input.wevision_id),
	 AMW_OFFSET(cwock_input.wevision_id),
	 1}
	,

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.cwock_input.mode),
	 AMW_OFFSET(cwock_input.fwags),
	 0}
	,

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.cwock_input.scawe),
	 AMW_OFFSET(cwock_input.fwags),
	 1}
	,

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.cwock_input.fwequency_divisow),
	 AMW_OFFSET(cwock_input.fwequency_divisow),
	 2}
	,

	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.cwock_input.fwequency_numewatow),
	 AMW_OFFSET(cwock_input.fwequency_numewatow),
	 4}
	,

	/* Wesouwce Souwce */
	{ACPI_WSC_SOUWCE, ACPI_WS_OFFSET(data.cwock_input.wesouwce_souwce),
	 0,
	 sizeof(stwuct amw_wesouwce_cwock_input)}
	,

};

/*******************************************************************************
 *
 * acpi_ws_convewt_pinfunction
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_pin_function[13] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_PIN_FUNCTION,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_function),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_pin_function)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_PIN_FUNCTION,
	 sizeof(stwuct amw_wesouwce_pin_function),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_function.wevision_id),
	 AMW_OFFSET(pin_function.wevision_id),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_function.shaweabwe),
	 AMW_OFFSET(pin_function.fwags),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_function.pin_config),
	 AMW_OFFSET(pin_function.pin_config),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.pin_function.function_numbew),
	 AMW_OFFSET(pin_function.function_numbew),
	 2},

	/* Pin Tabwe */

	/*
	 * It is OK to use GPIO opewations hewe because none of them wefew GPIO
	 * stwuctuwes diwectwy but instead use offsets given hewe.
	 */

	{ACPI_WSC_COUNT_GPIO_PIN,
	 ACPI_WS_OFFSET(data.pin_function.pin_tabwe_wength),
	 AMW_OFFSET(pin_function.pin_tabwe_offset),
	 AMW_OFFSET(pin_function.wes_souwce_offset)},

	{ACPI_WSC_MOVE_GPIO_PIN, ACPI_WS_OFFSET(data.pin_function.pin_tabwe),
	 AMW_OFFSET(pin_function.pin_tabwe_offset),
	 0},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.pin_function.wesouwce_souwce.index),
	 AMW_OFFSET(pin_function.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_function.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(pin_function.wes_souwce_offset),
	 AMW_OFFSET(pin_function.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_function.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(pin_function.wes_souwce_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN,
	 ACPI_WS_OFFSET(data.pin_function.vendow_wength),
	 AMW_OFFSET(pin_function.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES, ACPI_WS_OFFSET(data.pin_function.vendow_data),
	 AMW_OFFSET(pin_function.vendow_offset),
	 0},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_csi2_sewiaw_bus
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_csi2_sewiaw_bus[14] = {
	{ ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_SEWIAW_BUS,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_csi2_sewiawbus),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_csi2_sewiaw_bus) },

	{ ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_SEWIAW_BUS,
	 sizeof(stwuct amw_wesouwce_csi2_sewiawbus),
	 0 },

	{ ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.wevision_id),
	 1 },

	{ ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.csi2_sewiaw_bus.type),
	 AMW_OFFSET(csi2_sewiaw_bus.type),
	 1 },

	{ ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.pwoducew_consumew),
	 AMW_OFFSET(csi2_sewiaw_bus.fwags),
	 1 },

	{ ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.csi2_sewiaw_bus.swave_mode),
	 AMW_OFFSET(csi2_sewiaw_bus.fwags),
	 0 },

	{ ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.csi2_sewiaw_bus.phy_type),
	 AMW_OFFSET(csi2_sewiaw_bus.type_specific_fwags),
	 0 },

	{ ACPI_WSC_6BITFWAG,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.wocaw_powt_instance),
	 AMW_OFFSET(csi2_sewiaw_bus.type_specific_fwags),
	 2 },

	{ ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.csi2_sewiaw_bus.type_wevision_id),
	 AMW_OFFSET(csi2_sewiaw_bus.type_wevision_id),
	 1 },

	/* Vendow data */

	{ ACPI_WSC_COUNT_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.vendow_wength),
	 AMW_OFFSET(csi2_sewiaw_bus.type_data_wength),
	 AMW_WESOUWCE_CSI2_MIN_DATA_WEN },

	{ ACPI_WSC_MOVE_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.vendow_data),
	 0,
	 sizeof(stwuct amw_wesouwce_csi2_sewiawbus) },

	/* Wesouwce Souwce */

	{ ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.wesouwce_souwce.index),
	 AMW_OFFSET(csi2_sewiaw_bus.wes_souwce_index),
	 1 },

	{ ACPI_WSC_COUNT_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(csi2_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_csi2_sewiawbus) },

	{ ACPI_WSC_MOVE_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.csi2_sewiaw_bus.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(csi2_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_csi2_sewiawbus) },
};

/*******************************************************************************
 *
 * acpi_ws_convewt_i2c_sewiaw_bus
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_i2c_sewiaw_bus[17] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_SEWIAW_BUS,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_i2c_sewiawbus),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_i2c_sewiaw_bus)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_SEWIAW_BUS,
	 sizeof(stwuct amw_wesouwce_i2c_sewiawbus),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.wevision_id),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.type),
	 AMW_OFFSET(common_sewiaw_bus.type),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.common_sewiaw_bus.swave_mode),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 0},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.pwoducew_consumew),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 1},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.connection_shawing),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 2},

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.type_wevision_id),
	 1},

	{ACPI_WSC_MOVE16,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_data_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 1},

	/* Vendow data */

	{ACPI_WSC_COUNT_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 AMW_WESOUWCE_I2C_MIN_DATA_WEN},

	{ACPI_WSC_MOVE_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_data),
	 0,
	 sizeof(stwuct amw_wesouwce_i2c_sewiawbus)},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.index),
	 AMW_OFFSET(common_sewiaw_bus.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	{ACPI_WSC_MOVE_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	/* I2C bus type specific */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.i2c_sewiaw_bus.access_mode),
	 AMW_OFFSET(i2c_sewiaw_bus.type_specific_fwags),
	 0},

	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.i2c_sewiaw_bus.connection_speed),
	 AMW_OFFSET(i2c_sewiaw_bus.connection_speed),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.i2c_sewiaw_bus.swave_addwess),
	 AMW_OFFSET(i2c_sewiaw_bus.swave_addwess),
	 1},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_spi_sewiaw_bus
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_spi_sewiaw_bus[21] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_SEWIAW_BUS,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_spi_sewiawbus),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_spi_sewiaw_bus)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_SEWIAW_BUS,
	 sizeof(stwuct amw_wesouwce_spi_sewiawbus),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.wevision_id),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.type),
	 AMW_OFFSET(common_sewiaw_bus.type),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.common_sewiaw_bus.swave_mode),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 0},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.pwoducew_consumew),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 1},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.connection_shawing),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 2},

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.type_wevision_id),
	 1},

	{ACPI_WSC_MOVE16,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_data_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 1},

	/* Vendow data */

	{ACPI_WSC_COUNT_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 AMW_WESOUWCE_SPI_MIN_DATA_WEN},

	{ACPI_WSC_MOVE_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_data),
	 0,
	 sizeof(stwuct amw_wesouwce_spi_sewiawbus)},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.index),
	 AMW_OFFSET(common_sewiaw_bus.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	{ACPI_WSC_MOVE_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	/* Spi bus type specific  */

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.spi_sewiaw_bus.wiwe_mode),
	 AMW_OFFSET(spi_sewiaw_bus.type_specific_fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.spi_sewiaw_bus.device_powawity),
	 AMW_OFFSET(spi_sewiaw_bus.type_specific_fwags),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.spi_sewiaw_bus.data_bit_wength),
	 AMW_OFFSET(spi_sewiaw_bus.data_bit_wength),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.spi_sewiaw_bus.cwock_phase),
	 AMW_OFFSET(spi_sewiaw_bus.cwock_phase),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.spi_sewiaw_bus.cwock_powawity),
	 AMW_OFFSET(spi_sewiaw_bus.cwock_powawity),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.spi_sewiaw_bus.device_sewection),
	 AMW_OFFSET(spi_sewiaw_bus.device_sewection),
	 1},

	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.spi_sewiaw_bus.connection_speed),
	 AMW_OFFSET(spi_sewiaw_bus.connection_speed),
	 1},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_uawt_sewiaw_bus
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_uawt_sewiaw_bus[23] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_SEWIAW_BUS,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_uawt_sewiawbus),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_uawt_sewiaw_bus)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_SEWIAW_BUS,
	 sizeof(stwuct amw_wesouwce_uawt_sewiawbus),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.wevision_id),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.common_sewiaw_bus.type),
	 AMW_OFFSET(common_sewiaw_bus.type),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.common_sewiaw_bus.swave_mode),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 0},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.pwoducew_consumew),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 1},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.connection_shawing),
	 AMW_OFFSET(common_sewiaw_bus.fwags),
	 2},

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_wevision_id),
	 AMW_OFFSET(common_sewiaw_bus.type_wevision_id),
	 1},

	{ACPI_WSC_MOVE16,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.type_data_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 1},

	/* Vendow data */

	{ACPI_WSC_COUNT_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 AMW_WESOUWCE_UAWT_MIN_DATA_WEN},

	{ACPI_WSC_MOVE_SEWIAW_VEN,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.vendow_data),
	 0,
	 sizeof(stwuct amw_wesouwce_uawt_sewiawbus)},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.index),
	 AMW_OFFSET(common_sewiaw_bus.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	{ACPI_WSC_MOVE_SEWIAW_WES,
	 ACPI_WS_OFFSET(data.common_sewiaw_bus.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(common_sewiaw_bus.type_data_wength),
	 sizeof(stwuct amw_wesouwce_common_sewiawbus)},

	/* Uawt bus type specific  */

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.fwow_contwow),
	 AMW_OFFSET(uawt_sewiaw_bus.type_specific_fwags),
	 0},

	{ACPI_WSC_2BITFWAG, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.stop_bits),
	 AMW_OFFSET(uawt_sewiaw_bus.type_specific_fwags),
	 2},

	{ACPI_WSC_3BITFWAG, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.data_bits),
	 AMW_OFFSET(uawt_sewiaw_bus.type_specific_fwags),
	 4},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.endian),
	 AMW_OFFSET(uawt_sewiaw_bus.type_specific_fwags),
	 7},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.pawity),
	 AMW_OFFSET(uawt_sewiaw_bus.pawity),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.wines_enabwed),
	 AMW_OFFSET(uawt_sewiaw_bus.wines_enabwed),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.wx_fifo_size),
	 AMW_OFFSET(uawt_sewiaw_bus.wx_fifo_size),
	 1},

	{ACPI_WSC_MOVE16, ACPI_WS_OFFSET(data.uawt_sewiaw_bus.tx_fifo_size),
	 AMW_OFFSET(uawt_sewiaw_bus.tx_fifo_size),
	 1},

	{ACPI_WSC_MOVE32,
	 ACPI_WS_OFFSET(data.uawt_sewiaw_bus.defauwt_baud_wate),
	 AMW_OFFSET(uawt_sewiaw_bus.defauwt_baud_wate),
	 1},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_pin_config
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_pin_config[14] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_PIN_CONFIG,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_config),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_pin_config)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_PIN_CONFIG,
	 sizeof(stwuct amw_wesouwce_pin_config),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_config.wevision_id),
	 AMW_OFFSET(pin_config.wevision_id),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_config.shaweabwe),
	 AMW_OFFSET(pin_config.fwags),
	 0},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_config.pwoducew_consumew),
	 AMW_OFFSET(pin_config.fwags),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_config.pin_config_type),
	 AMW_OFFSET(pin_config.pin_config_type),
	 1},

	{ACPI_WSC_MOVE32, ACPI_WS_OFFSET(data.pin_config.pin_config_vawue),
	 AMW_OFFSET(pin_config.pin_config_vawue),
	 1},

	/* Pin Tabwe */

	/*
	 * It is OK to use GPIO opewations hewe because none of them wefew GPIO
	 * stwuctuwes diwectwy but instead use offsets given hewe.
	 */

	{ACPI_WSC_COUNT_GPIO_PIN,
	 ACPI_WS_OFFSET(data.pin_config.pin_tabwe_wength),
	 AMW_OFFSET(pin_config.pin_tabwe_offset),
	 AMW_OFFSET(pin_config.wes_souwce_offset)},

	{ACPI_WSC_MOVE_GPIO_PIN, ACPI_WS_OFFSET(data.pin_config.pin_tabwe),
	 AMW_OFFSET(pin_config.pin_tabwe_offset),
	 0},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_config.wesouwce_souwce.index),
	 AMW_OFFSET(pin_config.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_config.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(pin_config.wes_souwce_offset),
	 AMW_OFFSET(pin_config.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_config.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(pin_config.wes_souwce_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN, ACPI_WS_OFFSET(data.pin_config.vendow_wength),
	 AMW_OFFSET(pin_config.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES, ACPI_WS_OFFSET(data.pin_config.vendow_data),
	 AMW_OFFSET(pin_config.vendow_offset),
	 0},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_pin_gwoup
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_pin_gwoup[10] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_PIN_GWOUP,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_pin_gwoup)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_PIN_GWOUP,
	 sizeof(stwuct amw_wesouwce_pin_gwoup),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_gwoup.wevision_id),
	 AMW_OFFSET(pin_gwoup.wevision_id),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_gwoup.pwoducew_consumew),
	 AMW_OFFSET(pin_gwoup.fwags),
	 0},

	/* Pin Tabwe */

	/*
	 * It is OK to use GPIO opewations hewe because none of them wefew GPIO
	 * stwuctuwes diwectwy but instead use offsets given hewe.
	 */

	{ACPI_WSC_COUNT_GPIO_PIN,
	 ACPI_WS_OFFSET(data.pin_gwoup.pin_tabwe_wength),
	 AMW_OFFSET(pin_gwoup.pin_tabwe_offset),
	 AMW_OFFSET(pin_gwoup.wabew_offset)},

	{ACPI_WSC_MOVE_GPIO_PIN, ACPI_WS_OFFSET(data.pin_gwoup.pin_tabwe),
	 AMW_OFFSET(pin_gwoup.pin_tabwe_offset),
	 0},

	/* Wesouwce Wabew */

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup.wesouwce_wabew.stwing_wength),
	 AMW_OFFSET(pin_gwoup.wabew_offset),
	 AMW_OFFSET(pin_gwoup.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup.wesouwce_wabew.stwing_ptw),
	 AMW_OFFSET(pin_gwoup.wabew_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN, ACPI_WS_OFFSET(data.pin_gwoup.vendow_wength),
	 AMW_OFFSET(pin_gwoup.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES, ACPI_WS_OFFSET(data.pin_gwoup.vendow_data),
	 AMW_OFFSET(pin_gwoup.vendow_offset),
	 0},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_pin_gwoup_function
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_pin_gwoup_function[13] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup_function),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_pin_gwoup_function)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_PIN_GWOUP_FUNCTION,
	 sizeof(stwuct amw_wesouwce_pin_gwoup_function),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_gwoup_function.wevision_id),
	 AMW_OFFSET(pin_gwoup_function.wevision_id),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_gwoup_function.shaweabwe),
	 AMW_OFFSET(pin_gwoup_function.fwags),
	 0},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.pwoducew_consumew),
	 AMW_OFFSET(pin_gwoup_function.fwags),
	 1},

	{ACPI_WSC_MOVE16,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.function_numbew),
	 AMW_OFFSET(pin_gwoup_function.function_numbew),
	 1},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.wesouwce_souwce.index),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_offset),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_wabew_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_offset),
	 0},

	/* Wesouwce Souwce Wabew */

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.wesouwce_souwce_wabew.
			stwing_wength),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_wabew_offset),
	 AMW_OFFSET(pin_gwoup_function.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.wesouwce_souwce_wabew.
			stwing_ptw),
	 AMW_OFFSET(pin_gwoup_function.wes_souwce_wabew_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.vendow_wength),
	 AMW_OFFSET(pin_gwoup_function.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_function.vendow_data),
	 AMW_OFFSET(pin_gwoup_function.vendow_offset),
	 0},
};

/*******************************************************************************
 *
 * acpi_ws_convewt_pin_gwoup_config
 *
 ******************************************************************************/

stwuct acpi_wsconvewt_info acpi_ws_convewt_pin_gwoup_config[14] = {
	{ACPI_WSC_INITGET, ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG,
	 ACPI_WS_SIZE(stwuct acpi_wesouwce_pin_gwoup_config),
	 ACPI_WSC_TABWE_SIZE(acpi_ws_convewt_pin_gwoup_config)},

	{ACPI_WSC_INITSET, ACPI_WESOUWCE_NAME_PIN_GWOUP_CONFIG,
	 sizeof(stwuct amw_wesouwce_pin_gwoup_config),
	 0},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_gwoup_config.wevision_id),
	 AMW_OFFSET(pin_gwoup_config.wevision_id),
	 1},

	{ACPI_WSC_1BITFWAG, ACPI_WS_OFFSET(data.pin_gwoup_config.shaweabwe),
	 AMW_OFFSET(pin_gwoup_config.fwags),
	 0},

	{ACPI_WSC_1BITFWAG,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.pwoducew_consumew),
	 AMW_OFFSET(pin_gwoup_config.fwags),
	 1},

	{ACPI_WSC_MOVE8, ACPI_WS_OFFSET(data.pin_gwoup_config.pin_config_type),
	 AMW_OFFSET(pin_gwoup_config.pin_config_type),
	 1},

	{ACPI_WSC_MOVE32,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.pin_config_vawue),
	 AMW_OFFSET(pin_gwoup_config.pin_config_vawue),
	 1},

	/* Wesouwce Souwce */

	{ACPI_WSC_MOVE8,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.wesouwce_souwce.index),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_index),
	 1},

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.wesouwce_souwce.stwing_wength),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_offset),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_wabew_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.wesouwce_souwce.stwing_ptw),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_offset),
	 0},

	/* Wesouwce Souwce Wabew */

	{ACPI_WSC_COUNT_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.wesouwce_souwce_wabew.
			stwing_wength),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_wabew_offset),
	 AMW_OFFSET(pin_gwoup_config.vendow_offset)},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.wesouwce_souwce_wabew.stwing_ptw),
	 AMW_OFFSET(pin_gwoup_config.wes_souwce_wabew_offset),
	 0},

	/* Vendow Data */

	{ACPI_WSC_COUNT_GPIO_VEN,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.vendow_wength),
	 AMW_OFFSET(pin_gwoup_config.vendow_wength),
	 1},

	{ACPI_WSC_MOVE_GPIO_WES,
	 ACPI_WS_OFFSET(data.pin_gwoup_config.vendow_data),
	 AMW_OFFSET(pin_gwoup_config.vendow_offset),
	 0},
};
