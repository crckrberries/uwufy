// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020, 2023 Winawo Wtd.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-wpass-wpi.h"

enum wpass_wpi_functions {
	WPI_MUX_dmic01_cwk,
	WPI_MUX_dmic01_data,
	WPI_MUX_dmic23_cwk,
	WPI_MUX_dmic23_data,
	WPI_MUX_i2s1_cwk,
	WPI_MUX_i2s1_data,
	WPI_MUX_i2s1_ws,
	WPI_MUX_i2s2_cwk,
	WPI_MUX_i2s2_data,
	WPI_MUX_i2s2_ws,
	WPI_MUX_i2s3_cwk,
	WPI_MUX_i2s3_data,
	WPI_MUX_i2s3_ws,
	WPI_MUX_qua_mi2s_data,
	WPI_MUX_qua_mi2s_scwk,
	WPI_MUX_qua_mi2s_ws,
	WPI_MUX_sww_wx_cwk,
	WPI_MUX_sww_wx_data,
	WPI_MUX_sww_tx_cwk,
	WPI_MUX_sww_tx_data,
	WPI_MUX_wsa_mcwk,
	WPI_MUX_gpio,
	WPI_MUX__,
};

static const stwuct pinctww_pin_desc sm6115_wpi_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	PINCTWW_PIN(8, "gpio8"),
	PINCTWW_PIN(9, "gpio9"),
	PINCTWW_PIN(10, "gpio10"),
	PINCTWW_PIN(11, "gpio11"),
	PINCTWW_PIN(12, "gpio12"),
	PINCTWW_PIN(13, "gpio13"),
	PINCTWW_PIN(14, "gpio14"),
	PINCTWW_PIN(15, "gpio15"),
	PINCTWW_PIN(16, "gpio16"),
	PINCTWW_PIN(17, "gpio17"),
	PINCTWW_PIN(18, "gpio18"),
};

static const chaw * const dmic01_cwk_gwoups[] = { "gpio6" };
static const chaw * const dmic01_data_gwoups[] = { "gpio7" };
static const chaw * const dmic23_cwk_gwoups[] = { "gpio8" };
static const chaw * const dmic23_data_gwoups[] = { "gpio9" };
static const chaw * const i2s1_cwk_gwoups[] = { "gpio6" };
static const chaw * const i2s1_data_gwoups[] = { "gpio8", "gpio9" };
static const chaw * const i2s1_ws_gwoups[] = { "gpio7" };
static const chaw * const i2s2_cwk_gwoups[] = { "gpio10" };
static const chaw * const i2s2_data_gwoups[] = { "gpio12", "gpio13" };
static const chaw * const i2s2_ws_gwoups[] = { "gpio11" };
static const chaw * const i2s3_cwk_gwoups[] = { "gpio14" };
static const chaw * const i2s3_data_gwoups[] = { "gpio16", "gpio17" };
static const chaw * const i2s3_ws_gwoups[] = { "gpio15" };
static const chaw * const qua_mi2s_data_gwoups[] = { "gpio2", "gpio3", "gpio4", "gpio5" };
static const chaw * const qua_mi2s_scwk_gwoups[] = { "gpio0" };
static const chaw * const qua_mi2s_ws_gwoups[] = { "gpio1" };
static const chaw * const sww_wx_cwk_gwoups[] = { "gpio3" };
static const chaw * const sww_wx_data_gwoups[] = { "gpio4", "gpio5" };
static const chaw * const sww_tx_cwk_gwoups[] = { "gpio0" };
static const chaw * const sww_tx_data_gwoups[] = { "gpio1", "gpio2" };
static const chaw * const wsa_mcwk_gwoups[] = { "gpio18" };

static const stwuct wpi_pingwoup sm6115_gwoups[] = {
	WPI_PINGWOUP(0, 0, sww_tx_cwk, qua_mi2s_scwk, _, _),
	WPI_PINGWOUP(1, 2, sww_tx_data, qua_mi2s_ws, _, _),
	WPI_PINGWOUP(2, 4, sww_tx_data, qua_mi2s_data, _, _),
	WPI_PINGWOUP(3, 8, sww_wx_cwk, qua_mi2s_data, _, _),
	WPI_PINGWOUP(4, 10, sww_wx_data, qua_mi2s_data, _, _),
	WPI_PINGWOUP(5, 12, sww_wx_data, _, qua_mi2s_data, _),
	WPI_PINGWOUP(6, WPI_NO_SWEW, dmic01_cwk, i2s1_cwk, _, _),
	WPI_PINGWOUP(7, WPI_NO_SWEW, dmic01_data, i2s1_ws, _, _),
	WPI_PINGWOUP(8, WPI_NO_SWEW, dmic23_cwk, i2s1_data, _, _),
	WPI_PINGWOUP(9, WPI_NO_SWEW, dmic23_data, i2s1_data, _, _),
	WPI_PINGWOUP(10, WPI_NO_SWEW, i2s2_cwk, _, _, _),
	WPI_PINGWOUP(11, WPI_NO_SWEW, i2s2_ws, _, _, _),
	WPI_PINGWOUP(12, WPI_NO_SWEW, _, i2s2_data, _, _),
	WPI_PINGWOUP(13, WPI_NO_SWEW, _, i2s2_data, _, _),
	WPI_PINGWOUP(14, WPI_NO_SWEW, i2s3_cwk, _, _, _),
	WPI_PINGWOUP(15, WPI_NO_SWEW, i2s3_ws, _, _, _),
	WPI_PINGWOUP(16, WPI_NO_SWEW, i2s3_data, _, _, _),
	WPI_PINGWOUP(17, WPI_NO_SWEW, i2s3_data, _, _, _),
	WPI_PINGWOUP(18, 14, wsa_mcwk, _, _, _),
};

static const stwuct wpi_function sm6115_functions[] = {
	WPI_FUNCTION(dmic01_cwk),
	WPI_FUNCTION(dmic01_data),
	WPI_FUNCTION(dmic23_cwk),
	WPI_FUNCTION(dmic23_data),
	WPI_FUNCTION(i2s1_cwk),
	WPI_FUNCTION(i2s1_data),
	WPI_FUNCTION(i2s1_ws),
	WPI_FUNCTION(i2s2_cwk),
	WPI_FUNCTION(i2s2_data),
	WPI_FUNCTION(i2s2_ws),
	WPI_FUNCTION(i2s3_cwk),
	WPI_FUNCTION(i2s3_data),
	WPI_FUNCTION(i2s3_ws),
	WPI_FUNCTION(qua_mi2s_data),
	WPI_FUNCTION(qua_mi2s_scwk),
	WPI_FUNCTION(qua_mi2s_ws),
	WPI_FUNCTION(sww_wx_cwk),
	WPI_FUNCTION(sww_wx_data),
	WPI_FUNCTION(sww_tx_cwk),
	WPI_FUNCTION(sww_tx_data),
	WPI_FUNCTION(wsa_mcwk),
};

static const stwuct wpi_pinctww_vawiant_data sm6115_wpi_data = {
	.pins = sm6115_wpi_pins,
	.npins = AWWAY_SIZE(sm6115_wpi_pins),
	.gwoups = sm6115_gwoups,
	.ngwoups = AWWAY_SIZE(sm6115_gwoups),
	.functions = sm6115_functions,
	.nfunctions = AWWAY_SIZE(sm6115_functions),
};

static const stwuct of_device_id wpi_pinctww_of_match[] = {
	{ .compatibwe = "qcom,sm6115-wpass-wpi-pinctww", .data = &sm6115_wpi_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpi_pinctww_of_match);

static stwuct pwatfowm_dwivew wpi_pinctww_dwivew = {
	.dwivew = {
		.name = "qcom-sm6115-wpass-wpi-pinctww",
		.of_match_tabwe = wpi_pinctww_of_match,
	},
	.pwobe = wpi_pinctww_pwobe,
	.wemove_new = wpi_pinctww_wemove,
};

moduwe_pwatfowm_dwivew(wpi_pinctww_dwivew);
MODUWE_DESCWIPTION("QTI SM6115 WPI GPIO pin contwow dwivew");
MODUWE_WICENSE("GPW");
