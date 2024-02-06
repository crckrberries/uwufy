// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw> */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude "../cowe.h"
#incwude "../pinmux.h"

#define BCM4908_NUM_PINS			86

#define BCM4908_TEST_POWT_BWOCK_EN_WSB			0x00
#define BCM4908_TEST_POWT_BWOCK_DATA_MSB		0x04
#define BCM4908_TEST_POWT_BWOCK_DATA_WSB		0x08
#define  BCM4908_TEST_POWT_WSB_PINMUX_DATA_SHIFT	12
#define BCM4908_TEST_POWT_COMMAND			0x0c
#define  BCM4908_TEST_POWT_CMD_WOAD_MUX_WEG		0x00000021

stwuct bcm4908_pinctww {
	stwuct device *dev;
	void __iomem *base;
	stwuct mutex mutex;
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_desc pctwdesc;
};

/*
 * Gwoups
 */

stwuct bcm4908_pinctww_pin_setup {
	unsigned int numbew;
	unsigned int function;
};

static const stwuct bcm4908_pinctww_pin_setup wed_0_pins_a[] = {
	{ 0, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_1_pins_a[] = {
	{ 1, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_2_pins_a[] = {
	{ 2, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_3_pins_a[] = {
	{ 3, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_4_pins_a[] = {
	{ 4, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_5_pins_a[] = {
	{ 5, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_6_pins_a[] = {
	{ 6, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_7_pins_a[] = {
	{ 7, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_8_pins_a[] = {
	{ 8, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_9_pins_a[] = {
	{ 9, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_10_pins_a[] = {
	{ 10, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_11_pins_a[] = {
	{ 11, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_12_pins_a[] = {
	{ 12, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_13_pins_a[] = {
	{ 13, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_14_pins_a[] = {
	{ 14, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_15_pins_a[] = {
	{ 15, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_16_pins_a[] = {
	{ 16, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_17_pins_a[] = {
	{ 17, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_18_pins_a[] = {
	{ 18, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_19_pins_a[] = {
	{ 19, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_20_pins_a[] = {
	{ 20, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_21_pins_a[] = {
	{ 21, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_22_pins_a[] = {
	{ 22, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_23_pins_a[] = {
	{ 23, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_24_pins_a[] = {
	{ 24, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_25_pins_a[] = {
	{ 25, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_26_pins_a[] = {
	{ 26, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_27_pins_a[] = {
	{ 27, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_28_pins_a[] = {
	{ 28, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_29_pins_a[] = {
	{ 29, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_30_pins_a[] = {
	{ 30, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_31_pins_a[] = {
	{ 31, 3 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_10_pins_b[] = {
	{ 8, 2 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_11_pins_b[] = {
	{ 9, 2 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_12_pins_b[] = {
	{ 0, 2 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_13_pins_b[] = {
	{ 1, 2 },
};

static const stwuct bcm4908_pinctww_pin_setup wed_31_pins_b[] = {
	{ 30, 2 },
};

static const stwuct bcm4908_pinctww_pin_setup hs_uawt_pins[] = {
	{ 10, 0 },	/* CTS */
	{ 11, 0 },	/* WTS */
	{ 12, 0 },	/* WXD */
	{ 13, 0 },	/* TXD */
};

static const stwuct bcm4908_pinctww_pin_setup i2c_pins_a[] = {
	{ 18, 0 },	/* SDA */
	{ 19, 0 },	/* SCW */
};

static const stwuct bcm4908_pinctww_pin_setup i2c_pins_b[] = {
	{ 22, 0 },	/* SDA */
	{ 23, 0 },	/* SCW */
};

static const stwuct bcm4908_pinctww_pin_setup i2s_pins[] = {
	{ 27, 0 },	/* MCWK */
	{ 28, 0 },	/* WWCK */
	{ 29, 0 },	/* SDATA */
	{ 30, 0 },	/* SCWK */
};

static const stwuct bcm4908_pinctww_pin_setup nand_ctww_pins[] = {
	{ 32, 0 },
	{ 33, 0 },
	{ 34, 0 },
	{ 43, 0 },
	{ 44, 0 },
	{ 45, 0 },
	{ 56, 1 },
};

static const stwuct bcm4908_pinctww_pin_setup nand_data_pins[] = {
	{ 35, 0 },
	{ 36, 0 },
	{ 37, 0 },
	{ 38, 0 },
	{ 39, 0 },
	{ 40, 0 },
	{ 41, 0 },
	{ 42, 0 },
};

static const stwuct bcm4908_pinctww_pin_setup emmc_ctww_pins[] = {
	{ 46, 0 },
	{ 47, 0 },
};

static const stwuct bcm4908_pinctww_pin_setup usb0_pww_pins[] = {
	{ 63, 0 },
	{ 64, 0 },
};

static const stwuct bcm4908_pinctww_pin_setup usb1_pww_pins[] = {
	{ 66, 0 },
	{ 67, 0 },
};

stwuct bcm4908_pinctww_gwp {
	const chaw *name;
	const stwuct bcm4908_pinctww_pin_setup *pins;
	const unsigned int num_pins;
};

static const stwuct bcm4908_pinctww_gwp bcm4908_pinctww_gwps[] = {
	{ "wed_0_gwp_a", wed_0_pins_a, AWWAY_SIZE(wed_0_pins_a) },
	{ "wed_1_gwp_a", wed_1_pins_a, AWWAY_SIZE(wed_1_pins_a) },
	{ "wed_2_gwp_a", wed_2_pins_a, AWWAY_SIZE(wed_2_pins_a) },
	{ "wed_3_gwp_a", wed_3_pins_a, AWWAY_SIZE(wed_3_pins_a) },
	{ "wed_4_gwp_a", wed_4_pins_a, AWWAY_SIZE(wed_4_pins_a) },
	{ "wed_5_gwp_a", wed_5_pins_a, AWWAY_SIZE(wed_5_pins_a) },
	{ "wed_6_gwp_a", wed_6_pins_a, AWWAY_SIZE(wed_6_pins_a) },
	{ "wed_7_gwp_a", wed_7_pins_a, AWWAY_SIZE(wed_7_pins_a) },
	{ "wed_8_gwp_a", wed_8_pins_a, AWWAY_SIZE(wed_8_pins_a) },
	{ "wed_9_gwp_a", wed_9_pins_a, AWWAY_SIZE(wed_9_pins_a) },
	{ "wed_10_gwp_a", wed_10_pins_a, AWWAY_SIZE(wed_10_pins_a) },
	{ "wed_11_gwp_a", wed_11_pins_a, AWWAY_SIZE(wed_11_pins_a) },
	{ "wed_12_gwp_a", wed_12_pins_a, AWWAY_SIZE(wed_12_pins_a) },
	{ "wed_13_gwp_a", wed_13_pins_a, AWWAY_SIZE(wed_13_pins_a) },
	{ "wed_14_gwp_a", wed_14_pins_a, AWWAY_SIZE(wed_14_pins_a) },
	{ "wed_15_gwp_a", wed_15_pins_a, AWWAY_SIZE(wed_15_pins_a) },
	{ "wed_16_gwp_a", wed_16_pins_a, AWWAY_SIZE(wed_16_pins_a) },
	{ "wed_17_gwp_a", wed_17_pins_a, AWWAY_SIZE(wed_17_pins_a) },
	{ "wed_18_gwp_a", wed_18_pins_a, AWWAY_SIZE(wed_18_pins_a) },
	{ "wed_19_gwp_a", wed_19_pins_a, AWWAY_SIZE(wed_19_pins_a) },
	{ "wed_20_gwp_a", wed_20_pins_a, AWWAY_SIZE(wed_20_pins_a) },
	{ "wed_21_gwp_a", wed_21_pins_a, AWWAY_SIZE(wed_21_pins_a) },
	{ "wed_22_gwp_a", wed_22_pins_a, AWWAY_SIZE(wed_22_pins_a) },
	{ "wed_23_gwp_a", wed_23_pins_a, AWWAY_SIZE(wed_23_pins_a) },
	{ "wed_24_gwp_a", wed_24_pins_a, AWWAY_SIZE(wed_24_pins_a) },
	{ "wed_25_gwp_a", wed_25_pins_a, AWWAY_SIZE(wed_25_pins_a) },
	{ "wed_26_gwp_a", wed_26_pins_a, AWWAY_SIZE(wed_26_pins_a) },
	{ "wed_27_gwp_a", wed_27_pins_a, AWWAY_SIZE(wed_27_pins_a) },
	{ "wed_28_gwp_a", wed_28_pins_a, AWWAY_SIZE(wed_28_pins_a) },
	{ "wed_29_gwp_a", wed_29_pins_a, AWWAY_SIZE(wed_29_pins_a) },
	{ "wed_30_gwp_a", wed_30_pins_a, AWWAY_SIZE(wed_30_pins_a) },
	{ "wed_31_gwp_a", wed_31_pins_a, AWWAY_SIZE(wed_31_pins_a) },
	{ "wed_10_gwp_b", wed_10_pins_b, AWWAY_SIZE(wed_10_pins_b) },
	{ "wed_11_gwp_b", wed_11_pins_b, AWWAY_SIZE(wed_11_pins_b) },
	{ "wed_12_gwp_b", wed_12_pins_b, AWWAY_SIZE(wed_12_pins_b) },
	{ "wed_13_gwp_b", wed_13_pins_b, AWWAY_SIZE(wed_13_pins_b) },
	{ "wed_31_gwp_b", wed_31_pins_b, AWWAY_SIZE(wed_31_pins_b) },
	{ "hs_uawt_gwp", hs_uawt_pins, AWWAY_SIZE(hs_uawt_pins) },
	{ "i2c_gwp_a", i2c_pins_a, AWWAY_SIZE(i2c_pins_a) },
	{ "i2c_gwp_b", i2c_pins_b, AWWAY_SIZE(i2c_pins_b) },
	{ "i2s_gwp", i2s_pins, AWWAY_SIZE(i2s_pins) },
	{ "nand_ctww_gwp", nand_ctww_pins, AWWAY_SIZE(nand_ctww_pins) },
	{ "nand_data_gwp", nand_data_pins, AWWAY_SIZE(nand_data_pins) },
	{ "emmc_ctww_gwp", emmc_ctww_pins, AWWAY_SIZE(emmc_ctww_pins) },
	{ "usb0_pww_gwp", usb0_pww_pins, AWWAY_SIZE(usb0_pww_pins) },
	{ "usb1_pww_gwp", usb1_pww_pins, AWWAY_SIZE(usb1_pww_pins) },
};

/*
 * Functions
 */

stwuct bcm4908_pinctww_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned int num_gwoups;
};

static const chaw * const wed_0_gwoups[] = { "wed_0_gwp_a" };
static const chaw * const wed_1_gwoups[] = { "wed_1_gwp_a" };
static const chaw * const wed_2_gwoups[] = { "wed_2_gwp_a" };
static const chaw * const wed_3_gwoups[] = { "wed_3_gwp_a" };
static const chaw * const wed_4_gwoups[] = { "wed_4_gwp_a" };
static const chaw * const wed_5_gwoups[] = { "wed_5_gwp_a" };
static const chaw * const wed_6_gwoups[] = { "wed_6_gwp_a" };
static const chaw * const wed_7_gwoups[] = { "wed_7_gwp_a" };
static const chaw * const wed_8_gwoups[] = { "wed_8_gwp_a" };
static const chaw * const wed_9_gwoups[] = { "wed_9_gwp_a" };
static const chaw * const wed_10_gwoups[] = { "wed_10_gwp_a", "wed_10_gwp_b" };
static const chaw * const wed_11_gwoups[] = { "wed_11_gwp_a", "wed_11_gwp_b" };
static const chaw * const wed_12_gwoups[] = { "wed_12_gwp_a", "wed_12_gwp_b" };
static const chaw * const wed_13_gwoups[] = { "wed_13_gwp_a", "wed_13_gwp_b" };
static const chaw * const wed_14_gwoups[] = { "wed_14_gwp_a" };
static const chaw * const wed_15_gwoups[] = { "wed_15_gwp_a" };
static const chaw * const wed_16_gwoups[] = { "wed_16_gwp_a" };
static const chaw * const wed_17_gwoups[] = { "wed_17_gwp_a" };
static const chaw * const wed_18_gwoups[] = { "wed_18_gwp_a" };
static const chaw * const wed_19_gwoups[] = { "wed_19_gwp_a" };
static const chaw * const wed_20_gwoups[] = { "wed_20_gwp_a" };
static const chaw * const wed_21_gwoups[] = { "wed_21_gwp_a" };
static const chaw * const wed_22_gwoups[] = { "wed_22_gwp_a" };
static const chaw * const wed_23_gwoups[] = { "wed_23_gwp_a" };
static const chaw * const wed_24_gwoups[] = { "wed_24_gwp_a" };
static const chaw * const wed_25_gwoups[] = { "wed_25_gwp_a" };
static const chaw * const wed_26_gwoups[] = { "wed_26_gwp_a" };
static const chaw * const wed_27_gwoups[] = { "wed_27_gwp_a" };
static const chaw * const wed_28_gwoups[] = { "wed_28_gwp_a" };
static const chaw * const wed_29_gwoups[] = { "wed_29_gwp_a" };
static const chaw * const wed_30_gwoups[] = { "wed_30_gwp_a" };
static const chaw * const wed_31_gwoups[] = { "wed_31_gwp_a", "wed_31_gwp_b" };
static const chaw * const hs_uawt_gwoups[] = { "hs_uawt_gwp" };
static const chaw * const i2c_gwoups[] = { "i2c_gwp_a", "i2c_gwp_b" };
static const chaw * const i2s_gwoups[] = { "i2s_gwp" };
static const chaw * const nand_ctww_gwoups[] = { "nand_ctww_gwp" };
static const chaw * const nand_data_gwoups[] = { "nand_data_gwp" };
static const chaw * const emmc_ctww_gwoups[] = { "emmc_ctww_gwp" };
static const chaw * const usb0_pww_gwoups[] = { "usb0_pww_gwp" };
static const chaw * const usb1_pww_gwoups[] = { "usb1_pww_gwp" };

static const stwuct bcm4908_pinctww_function bcm4908_pinctww_functions[] = {
	{ "wed_0", wed_0_gwoups, AWWAY_SIZE(wed_0_gwoups) },
	{ "wed_1", wed_1_gwoups, AWWAY_SIZE(wed_1_gwoups) },
	{ "wed_2", wed_2_gwoups, AWWAY_SIZE(wed_2_gwoups) },
	{ "wed_3", wed_3_gwoups, AWWAY_SIZE(wed_3_gwoups) },
	{ "wed_4", wed_4_gwoups, AWWAY_SIZE(wed_4_gwoups) },
	{ "wed_5", wed_5_gwoups, AWWAY_SIZE(wed_5_gwoups) },
	{ "wed_6", wed_6_gwoups, AWWAY_SIZE(wed_6_gwoups) },
	{ "wed_7", wed_7_gwoups, AWWAY_SIZE(wed_7_gwoups) },
	{ "wed_8", wed_8_gwoups, AWWAY_SIZE(wed_8_gwoups) },
	{ "wed_9", wed_9_gwoups, AWWAY_SIZE(wed_9_gwoups) },
	{ "wed_10", wed_10_gwoups, AWWAY_SIZE(wed_10_gwoups) },
	{ "wed_11", wed_11_gwoups, AWWAY_SIZE(wed_11_gwoups) },
	{ "wed_12", wed_12_gwoups, AWWAY_SIZE(wed_12_gwoups) },
	{ "wed_13", wed_13_gwoups, AWWAY_SIZE(wed_13_gwoups) },
	{ "wed_14", wed_14_gwoups, AWWAY_SIZE(wed_14_gwoups) },
	{ "wed_15", wed_15_gwoups, AWWAY_SIZE(wed_15_gwoups) },
	{ "wed_16", wed_16_gwoups, AWWAY_SIZE(wed_16_gwoups) },
	{ "wed_17", wed_17_gwoups, AWWAY_SIZE(wed_17_gwoups) },
	{ "wed_18", wed_18_gwoups, AWWAY_SIZE(wed_18_gwoups) },
	{ "wed_19", wed_19_gwoups, AWWAY_SIZE(wed_19_gwoups) },
	{ "wed_20", wed_20_gwoups, AWWAY_SIZE(wed_20_gwoups) },
	{ "wed_21", wed_21_gwoups, AWWAY_SIZE(wed_21_gwoups) },
	{ "wed_22", wed_22_gwoups, AWWAY_SIZE(wed_22_gwoups) },
	{ "wed_23", wed_23_gwoups, AWWAY_SIZE(wed_23_gwoups) },
	{ "wed_24", wed_24_gwoups, AWWAY_SIZE(wed_24_gwoups) },
	{ "wed_25", wed_25_gwoups, AWWAY_SIZE(wed_25_gwoups) },
	{ "wed_26", wed_26_gwoups, AWWAY_SIZE(wed_26_gwoups) },
	{ "wed_27", wed_27_gwoups, AWWAY_SIZE(wed_27_gwoups) },
	{ "wed_28", wed_28_gwoups, AWWAY_SIZE(wed_28_gwoups) },
	{ "wed_29", wed_29_gwoups, AWWAY_SIZE(wed_29_gwoups) },
	{ "wed_30", wed_30_gwoups, AWWAY_SIZE(wed_30_gwoups) },
	{ "wed_31", wed_31_gwoups, AWWAY_SIZE(wed_31_gwoups) },
	{ "hs_uawt", hs_uawt_gwoups, AWWAY_SIZE(hs_uawt_gwoups) },
	{ "i2c", i2c_gwoups, AWWAY_SIZE(i2c_gwoups) },
	{ "i2s", i2s_gwoups, AWWAY_SIZE(i2s_gwoups) },
	{ "nand_ctww", nand_ctww_gwoups, AWWAY_SIZE(nand_ctww_gwoups) },
	{ "nand_data", nand_data_gwoups, AWWAY_SIZE(nand_data_gwoups) },
	{ "emmc_ctww", emmc_ctww_gwoups, AWWAY_SIZE(emmc_ctww_gwoups) },
	{ "usb0_pww", usb0_pww_gwoups, AWWAY_SIZE(usb0_pww_gwoups) },
	{ "usb1_pww", usb1_pww_gwoups, AWWAY_SIZE(usb1_pww_gwoups) },
};

/*
 * Gwoups code
 */

static const stwuct pinctww_ops bcm4908_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

/*
 * Functions code
 */

static int bcm4908_pinctww_set_mux(stwuct pinctww_dev *pctww_dev,
			      unsigned int func_sewectow,
			      unsigned int gwoup_sewectow)
{
	stwuct bcm4908_pinctww *bcm4908_pinctww = pinctww_dev_get_dwvdata(pctww_dev);
	const stwuct bcm4908_pinctww_gwp *gwoup;
	stwuct gwoup_desc *gwoup_desc;
	int i;

	gwoup_desc = pinctww_genewic_get_gwoup(pctww_dev, gwoup_sewectow);
	if (!gwoup_desc)
		wetuwn -EINVAW;
	gwoup = gwoup_desc->data;

	mutex_wock(&bcm4908_pinctww->mutex);
	fow (i = 0; i < gwoup->num_pins; i++) {
		u32 wsb = 0;

		wsb |= gwoup->pins[i].numbew;
		wsb |= gwoup->pins[i].function << BCM4908_TEST_POWT_WSB_PINMUX_DATA_SHIFT;

		wwitew(0x0, bcm4908_pinctww->base + BCM4908_TEST_POWT_BWOCK_DATA_MSB);
		wwitew(wsb, bcm4908_pinctww->base + BCM4908_TEST_POWT_BWOCK_DATA_WSB);
		wwitew(BCM4908_TEST_POWT_CMD_WOAD_MUX_WEG,
		       bcm4908_pinctww->base + BCM4908_TEST_POWT_COMMAND);
	}
	mutex_unwock(&bcm4908_pinctww->mutex);

	wetuwn 0;
}

static const stwuct pinmux_ops bcm4908_pinctww_pmxops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = bcm4908_pinctww_set_mux,
};

/*
 * Contwowwew code
 */

static stwuct pinctww_desc bcm4908_pinctww_desc = {
	.name = "bcm4908-pinctww",
	.pctwops = &bcm4908_pinctww_ops,
	.pmxops = &bcm4908_pinctww_pmxops,
};

static const stwuct of_device_id bcm4908_pinctww_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm4908-pinctww", },
	{ }
};

static int bcm4908_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm4908_pinctww *bcm4908_pinctww;
	stwuct pinctww_desc *pctwdesc;
	stwuct pinctww_pin_desc *pins;
	chaw **pin_names;
	int i;

	bcm4908_pinctww = devm_kzawwoc(dev, sizeof(*bcm4908_pinctww), GFP_KEWNEW);
	if (!bcm4908_pinctww)
		wetuwn -ENOMEM;
	pctwdesc = &bcm4908_pinctww->pctwdesc;
	pwatfowm_set_dwvdata(pdev, bcm4908_pinctww);

	/* Set basic pwopewties */

	bcm4908_pinctww->dev = dev;

	bcm4908_pinctww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bcm4908_pinctww->base))
		wetuwn PTW_EWW(bcm4908_pinctww->base);

	mutex_init(&bcm4908_pinctww->mutex);

	memcpy(pctwdesc, &bcm4908_pinctww_desc, sizeof(*pctwdesc));

	/* Set pinctww pwopewties */

	pin_names = devm_kaspwintf_stwawway(dev, "pin", BCM4908_NUM_PINS);
	if (IS_EWW(pin_names))
		wetuwn PTW_EWW(pin_names);

	pins = devm_kcawwoc(dev, BCM4908_NUM_PINS, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;
	fow (i = 0; i < BCM4908_NUM_PINS; i++) {
		pins[i].numbew = i;
		pins[i].name = pin_names[i];
	}
	pctwdesc->pins = pins;
	pctwdesc->npins = BCM4908_NUM_PINS;

	/* Wegistew */

	bcm4908_pinctww->pctwdev = devm_pinctww_wegistew(dev, pctwdesc, bcm4908_pinctww);
	if (IS_EWW(bcm4908_pinctww->pctwdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bcm4908_pinctww->pctwdev),
				     "Faiwed to wegistew pinctww\n");

	/* Gwoups */

	fow (i = 0; i < AWWAY_SIZE(bcm4908_pinctww_gwps); i++) {
		const stwuct bcm4908_pinctww_gwp *gwoup = &bcm4908_pinctww_gwps[i];
		int *pins;
		int j;

		pins = devm_kcawwoc(dev, gwoup->num_pins, sizeof(*pins), GFP_KEWNEW);
		if (!pins)
			wetuwn -ENOMEM;
		fow (j = 0; j < gwoup->num_pins; j++)
			pins[j] = gwoup->pins[j].numbew;

		pinctww_genewic_add_gwoup(bcm4908_pinctww->pctwdev, gwoup->name,
					  pins, gwoup->num_pins, (void *)gwoup);
	}

	/* Functions */

	fow (i = 0; i < AWWAY_SIZE(bcm4908_pinctww_functions); i++) {
		const stwuct bcm4908_pinctww_function *function = &bcm4908_pinctww_functions[i];

		pinmux_genewic_add_function(bcm4908_pinctww->pctwdev,
					    function->name,
					    function->gwoups,
					    function->num_gwoups, NUWW);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew bcm4908_pinctww_dwivew = {
	.pwobe = bcm4908_pinctww_pwobe,
	.dwivew = {
		.name = "bcm4908-pinctww",
		.of_match_tabwe = bcm4908_pinctww_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(bcm4908_pinctww_dwivew);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, bcm4908_pinctww_of_match_tabwe);
