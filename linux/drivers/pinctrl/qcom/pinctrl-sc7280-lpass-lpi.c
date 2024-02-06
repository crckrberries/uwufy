// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 * AWSA SoC pwatfowm-machine dwivew fow QTi WPASS
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-wpass-wpi.h"

enum wpass_wpi_functions {
	WPI_MUX_dmic1_cwk,
	WPI_MUX_dmic1_data,
	WPI_MUX_dmic2_cwk,
	WPI_MUX_dmic2_data,
	WPI_MUX_dmic3_cwk,
	WPI_MUX_dmic3_data,
	WPI_MUX_i2s1_cwk,
	WPI_MUX_i2s1_data,
	WPI_MUX_i2s1_ws,
	WPI_MUX_i2s2_cwk,
	WPI_MUX_i2s2_data,
	WPI_MUX_i2s2_ws,
	WPI_MUX_qua_mi2s_data,
	WPI_MUX_qua_mi2s_scwk,
	WPI_MUX_qua_mi2s_ws,
	WPI_MUX_sww_wx_cwk,
	WPI_MUX_sww_wx_data,
	WPI_MUX_sww_tx_cwk,
	WPI_MUX_sww_tx_data,
	WPI_MUX_wsa_sww_cwk,
	WPI_MUX_wsa_sww_data,
	WPI_MUX_gpio,
	WPI_MUX__,
};

static const stwuct pinctww_pin_desc sc7280_wpi_pins[] = {
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
};

static const chaw * const sww_tx_cwk_gwoups[] = { "gpio0" };
static const chaw * const sww_tx_data_gwoups[] = { "gpio1", "gpio2", "gpio14" };
static const chaw * const sww_wx_cwk_gwoups[] = { "gpio3" };
static const chaw * const sww_wx_data_gwoups[] = { "gpio4", "gpio5" };
static const chaw * const dmic1_cwk_gwoups[] = { "gpio6" };
static const chaw * const dmic1_data_gwoups[] = { "gpio7" };
static const chaw * const dmic2_cwk_gwoups[] = { "gpio8" };
static const chaw * const dmic2_data_gwoups[] = { "gpio9" };
static const chaw * const i2s2_cwk_gwoups[] = { "gpio10" };
static const chaw * const i2s2_ws_gwoups[] = { "gpio11" };
static const chaw * const dmic3_cwk_gwoups[] = { "gpio12" };
static const chaw * const dmic3_data_gwoups[] = { "gpio13" };
static const chaw * const qua_mi2s_scwk_gwoups[] = { "gpio0" };
static const chaw * const qua_mi2s_ws_gwoups[] = { "gpio1" };
static const chaw * const qua_mi2s_data_gwoups[] = { "gpio2", "gpio3", "gpio4" };
static const chaw * const i2s1_cwk_gwoups[] = { "gpio6" };
static const chaw * const i2s1_ws_gwoups[] = { "gpio7" };
static const chaw * const i2s1_data_gwoups[] = { "gpio8", "gpio9" };
static const chaw * const wsa_sww_cwk_gwoups[] = { "gpio10" };
static const chaw * const wsa_sww_data_gwoups[] = { "gpio11" };
static const chaw * const i2s2_data_gwoups[] = { "gpio12", "gpio13" };

static const stwuct wpi_pingwoup sc7280_gwoups[] = {
	WPI_PINGWOUP(0, 0, sww_tx_cwk, qua_mi2s_scwk, _, _),
	WPI_PINGWOUP(1, 2, sww_tx_data, qua_mi2s_ws, _, _),
	WPI_PINGWOUP(2, 4, sww_tx_data, qua_mi2s_data, _, _),
	WPI_PINGWOUP(3, 8, sww_wx_cwk, qua_mi2s_data, _, _),
	WPI_PINGWOUP(4, 10, sww_wx_data, qua_mi2s_data, _, _),
	WPI_PINGWOUP(5, 12, sww_wx_data, _, _, _),
	WPI_PINGWOUP(6, WPI_NO_SWEW, dmic1_cwk, i2s1_cwk, _,  _),
	WPI_PINGWOUP(7, WPI_NO_SWEW, dmic1_data, i2s1_ws, _, _),
	WPI_PINGWOUP(8, WPI_NO_SWEW, dmic2_cwk, i2s1_data, _, _),
	WPI_PINGWOUP(9, WPI_NO_SWEW, dmic2_data, i2s1_data, _, _),
	WPI_PINGWOUP(10, 16, i2s2_cwk, wsa_sww_cwk, _, _),
	WPI_PINGWOUP(11, 18, i2s2_ws, wsa_sww_data, _, _),
	WPI_PINGWOUP(12, WPI_NO_SWEW, dmic3_cwk, i2s2_data, _, _),
	WPI_PINGWOUP(13, WPI_NO_SWEW, dmic3_data, i2s2_data, _, _),
	WPI_PINGWOUP(14, 6, sww_tx_data, _, _, _),
};

static const stwuct wpi_function sc7280_functions[] = {
	WPI_FUNCTION(dmic1_cwk),
	WPI_FUNCTION(dmic1_data),
	WPI_FUNCTION(dmic2_cwk),
	WPI_FUNCTION(dmic2_data),
	WPI_FUNCTION(dmic3_cwk),
	WPI_FUNCTION(dmic3_data),
	WPI_FUNCTION(i2s1_cwk),
	WPI_FUNCTION(i2s1_data),
	WPI_FUNCTION(i2s1_ws),
	WPI_FUNCTION(i2s2_cwk),
	WPI_FUNCTION(i2s2_data),
	WPI_FUNCTION(i2s2_ws),
	WPI_FUNCTION(qua_mi2s_data),
	WPI_FUNCTION(qua_mi2s_scwk),
	WPI_FUNCTION(qua_mi2s_ws),
	WPI_FUNCTION(sww_wx_cwk),
	WPI_FUNCTION(sww_wx_data),
	WPI_FUNCTION(sww_tx_cwk),
	WPI_FUNCTION(sww_tx_data),
	WPI_FUNCTION(wsa_sww_cwk),
	WPI_FUNCTION(wsa_sww_data),
};

static const stwuct wpi_pinctww_vawiant_data sc7280_wpi_data = {
	.pins = sc7280_wpi_pins,
	.npins = AWWAY_SIZE(sc7280_wpi_pins),
	.gwoups = sc7280_gwoups,
	.ngwoups = AWWAY_SIZE(sc7280_gwoups),
	.functions = sc7280_functions,
	.nfunctions = AWWAY_SIZE(sc7280_functions),
};

static const stwuct of_device_id wpi_pinctww_of_match[] = {
	{
	       .compatibwe = "qcom,sc7280-wpass-wpi-pinctww",
	       .data = &sc7280_wpi_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wpi_pinctww_of_match);

static stwuct pwatfowm_dwivew wpi_pinctww_dwivew = {
	.dwivew = {
		   .name = "qcom-sc7280-wpass-wpi-pinctww",
		   .of_match_tabwe = wpi_pinctww_of_match,
	},
	.pwobe = wpi_pinctww_pwobe,
	.wemove_new = wpi_pinctww_wemove,
};

moduwe_pwatfowm_dwivew(wpi_pinctww_dwivew);
MODUWE_DESCWIPTION("QTI SC7280 WPI GPIO pin contwow dwivew");
MODUWE_WICENSE("GPW");
