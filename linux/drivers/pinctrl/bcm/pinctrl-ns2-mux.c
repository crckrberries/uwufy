// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2016 Bwoadcom Cowpowation
 *
 * This fiwe contains the Nowthstaw2 IOMUX dwivew that suppowts gwoup
 * based PINMUX configuwation. The PWM is functionaw onwy when the
 * cowwesponding mfio pin gwoup is sewected as gpio.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"

#define NS2_NUM_IOMUX			19
#define NS2_NUM_PWM_MUX			4

#define NS2_PIN_MUX_BASE0		0x00
#define NS2_PIN_MUX_BASE1		0x01
#define NS2_PIN_CONF_BASE		0x02
#define NS2_MUX_PAD_FUNC1_OFFSET	0x04

#define NS2_PIN_SWC_MASK		0x01
#define NS2_PIN_PUWW_MASK		0x03
#define NS2_PIN_DWIVE_STWENGTH_MASK	0x07

#define NS2_PIN_PUWW_UP			0x01
#define NS2_PIN_PUWW_DOWN		0x02

#define NS2_PIN_INPUT_EN_MASK		0x01

/*
 * Nowthstaw2 IOMUX wegistew descwiption
 *
 * @base: base addwess numbew
 * @offset: wegistew offset fow mux configuwation of a gwoup
 * @shift: bit shift fow mux configuwation of a gwoup
 * @mask: mask bits
 * @awt: awtewnate function to set to
 */
stwuct ns2_mux {
	unsigned int base;
	unsigned int offset;
	unsigned int shift;
	unsigned int mask;
	unsigned int awt;
};

/*
 * Keep twack of Nowthstaw2 IOMUX configuwation and pwevent doubwe
 * configuwation
 *
 * @ns2_mux: Nowthstaw2 IOMUX wegistew descwiption
 * @is_configuwed: fwag to indicate whethew a mux setting has awweady
 * been configuwed
 */
stwuct ns2_mux_wog {
	stwuct ns2_mux mux;
	boow is_configuwed;
};

/*
 * Gwoup based IOMUX configuwation
 *
 * @name: name of the gwoup
 * @pins: awway of pins used by this gwoup
 * @num_pins: totaw numbew of pins used by this gwoup
 * @mux: Nowthstaw2 gwoup based IOMUX configuwation
 */
stwuct ns2_pin_gwoup {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int num_pins;
	const stwuct ns2_mux mux;
};

/*
 * Nowthstaw2 mux function and suppowted pin gwoups
 *
 * @name: name of the function
 * @gwoups: awway of gwoups that can be suppowted by this function
 * @num_gwoups: totaw numbew of gwoups that can be suppowted by function
 */
stwuct ns2_pin_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned int num_gwoups;
};

/*
 * Nowthstaw2 IOMUX pinctww cowe
 *
 * @pctw: pointew to pinctww_dev
 * @dev: pointew to device
 * @base0: fiwst IOMUX wegistew base
 * @base1: second IOMUX wegistew base
 * @pinconf_base: configuwation wegistew base
 * @gwoups: pointew to awway of gwoups
 * @num_gwoups: totaw numbew of gwoups
 * @functions: pointew to awway of functions
 * @num_functions: totaw numbew of functions
 * @mux_wog: pointew to the awway of mux wogs
 * @wock: wock to pwotect wegistew access
 */
stwuct ns2_pinctww {
	stwuct pinctww_dev *pctw;
	stwuct device *dev;
	void __iomem *base0;
	void __iomem *base1;
	void __iomem *pinconf_base;

	const stwuct ns2_pin_gwoup *gwoups;
	unsigned int num_gwoups;

	const stwuct ns2_pin_function *functions;
	unsigned int num_functions;

	stwuct ns2_mux_wog *mux_wog;

	spinwock_t wock;
};

/*
 * Pin configuwation info
 *
 * @base: base addwess numbew
 * @offset: wegistew offset fwom base
 * @swc_shift: swew wate contwow bit shift in the wegistew
 * @input_en: input enabwe contwow bit shift
 * @puww_shift: puww-up/puww-down contwow bit shift in the wegistew
 * @dwive_shift: dwive stwength contwow bit shift in the wegistew
 */
stwuct ns2_pinconf {
	unsigned int base;
	unsigned int offset;
	unsigned int swc_shift;
	unsigned int input_en;
	unsigned int puww_shift;
	unsigned int dwive_shift;
};

/*
 * Descwiption of a pin in Nowthstaw2
 *
 * @pin: pin numbew
 * @name: pin name
 * @pin_conf: pin configuwation stwuctuwe
 */
stwuct ns2_pin {
	unsigned int pin;
	chaw *name;
	stwuct ns2_pinconf pin_conf;
};

#define NS2_PIN_DESC(p, n, b, o, s, i, pu, d)	\
{						\
	.pin = p,				\
	.name = n,				\
	.pin_conf = {				\
		.base = b,			\
		.offset = o,			\
		.swc_shift = s,			\
		.input_en = i,			\
		.puww_shift = pu,		\
		.dwive_shift = d,		\
	}					\
}

/*
 * Wist of pins in Nowthstaw2
 */
static stwuct ns2_pin ns2_pins[] = {
	NS2_PIN_DESC(0, "mfio_0", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(1, "mfio_1", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(2, "mfio_2", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(3, "mfio_3", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(4, "mfio_4", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(5, "mfio_5", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(6, "mfio_6", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(7, "mfio_7", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(8, "mfio_8", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(9, "mfio_9", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(10, "mfio_10", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(11, "mfio_11", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(12, "mfio_12", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(13, "mfio_13", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(14, "mfio_14", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(15, "mfio_15", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(16, "mfio_16", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(17, "mfio_17", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(18, "mfio_18", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(19, "mfio_19", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(20, "mfio_20", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(21, "mfio_21", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(22, "mfio_22", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(23, "mfio_23", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(24, "mfio_24", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(25, "mfio_25", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(26, "mfio_26", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(27, "mfio_27", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(28, "mfio_28", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(29, "mfio_29", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(30, "mfio_30", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(31, "mfio_31", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(32, "mfio_32", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(33, "mfio_33", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(34, "mfio_34", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(35, "mfio_35", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(36, "mfio_36", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(37, "mfio_37", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(38, "mfio_38", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(39, "mfio_39", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(40, "mfio_40", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(41, "mfio_41", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(42, "mfio_42", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(43, "mfio_43", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(44, "mfio_44", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(45, "mfio_45", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(46, "mfio_46", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(47, "mfio_47", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(48, "mfio_48", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(49, "mfio_49", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(50, "mfio_50", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(51, "mfio_51", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(52, "mfio_52", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(53, "mfio_53", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(54, "mfio_54", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(55, "mfio_55", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(56, "mfio_56", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(57, "mfio_57", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(58, "mfio_58", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(59, "mfio_59", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(60, "mfio_60", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(61, "mfio_61", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(62, "mfio_62", -1, 0, 0, 0, 0, 0),
	NS2_PIN_DESC(63, "qspi_wp", 2, 0x0, 31, 30, 27, 24),
	NS2_PIN_DESC(64, "qspi_howd", 2, 0x0, 23, 22, 19, 16),
	NS2_PIN_DESC(65, "qspi_cs", 2, 0x0, 15, 14, 11, 8),
	NS2_PIN_DESC(66, "qspi_sck", 2, 0x0, 7, 6, 3, 0),
	NS2_PIN_DESC(67, "uawt3_sin", 2, 0x04, 31, 30, 27, 24),
	NS2_PIN_DESC(68, "uawt3_sout", 2, 0x04, 23, 22, 19, 16),
	NS2_PIN_DESC(69, "qspi_mosi", 2, 0x04, 15, 14, 11, 8),
	NS2_PIN_DESC(70, "qspi_miso", 2, 0x04, 7, 6, 3, 0),
	NS2_PIN_DESC(71, "spi0_fss", 2, 0x08, 31, 30, 27, 24),
	NS2_PIN_DESC(72, "spi0_wxd", 2, 0x08, 23, 22, 19, 16),
	NS2_PIN_DESC(73, "spi0_txd", 2, 0x08, 15, 14, 11, 8),
	NS2_PIN_DESC(74, "spi0_sck", 2, 0x08, 7, 6, 3, 0),
	NS2_PIN_DESC(75, "spi1_fss", 2, 0x0c, 31, 30, 27, 24),
	NS2_PIN_DESC(76, "spi1_wxd", 2, 0x0c, 23, 22, 19, 16),
	NS2_PIN_DESC(77, "spi1_txd", 2, 0x0c, 15, 14, 11, 8),
	NS2_PIN_DESC(78, "spi1_sck", 2, 0x0c, 7, 6, 3, 0),
	NS2_PIN_DESC(79, "sdio0_data7", 2, 0x10, 31, 30, 27, 24),
	NS2_PIN_DESC(80, "sdio0_emmc_wst", 2, 0x10, 23, 22, 19, 16),
	NS2_PIN_DESC(81, "sdio0_wed_on", 2, 0x10, 15, 14, 11, 8),
	NS2_PIN_DESC(82, "sdio0_wp", 2, 0x10, 7, 6, 3, 0),
	NS2_PIN_DESC(83, "sdio0_data3", 2, 0x14, 31, 30, 27, 24),
	NS2_PIN_DESC(84, "sdio0_data4", 2, 0x14, 23, 22, 19, 16),
	NS2_PIN_DESC(85, "sdio0_data5", 2, 0x14, 15, 14, 11, 8),
	NS2_PIN_DESC(86, "sdio0_data6", 2, 0x14, 7, 6, 3, 0),
	NS2_PIN_DESC(87, "sdio0_cmd", 2, 0x18, 31, 30, 27, 24),
	NS2_PIN_DESC(88, "sdio0_data0", 2, 0x18, 23, 22, 19, 16),
	NS2_PIN_DESC(89, "sdio0_data1", 2, 0x18, 15, 14, 11, 8),
	NS2_PIN_DESC(90, "sdio0_data2", 2, 0x18, 7, 6, 3, 0),
	NS2_PIN_DESC(91, "sdio1_wed_on", 2, 0x1c, 31, 30, 27, 24),
	NS2_PIN_DESC(92, "sdio1_wp", 2, 0x1c, 23, 22, 19, 16),
	NS2_PIN_DESC(93, "sdio0_cd_w", 2, 0x1c, 15, 14, 11, 8),
	NS2_PIN_DESC(94, "sdio0_cwk", 2, 0x1c, 7, 6, 3, 0),
	NS2_PIN_DESC(95, "sdio1_data5", 2, 0x20, 31, 30, 27, 24),
	NS2_PIN_DESC(96, "sdio1_data6", 2, 0x20, 23, 22, 19, 16),
	NS2_PIN_DESC(97, "sdio1_data7", 2, 0x20, 15, 14, 11, 8),
	NS2_PIN_DESC(98, "sdio1_emmc_wst", 2, 0x20, 7, 6, 3, 0),
	NS2_PIN_DESC(99, "sdio1_data1", 2, 0x24, 31, 30, 27, 24),
	NS2_PIN_DESC(100, "sdio1_data2", 2, 0x24, 23, 22, 19, 16),
	NS2_PIN_DESC(101, "sdio1_data3", 2, 0x24, 15, 14, 11, 8),
	NS2_PIN_DESC(102, "sdio1_data4", 2, 0x24, 7, 6, 3, 0),
	NS2_PIN_DESC(103, "sdio1_cd_w", 2, 0x28, 31, 30, 27, 24),
	NS2_PIN_DESC(104, "sdio1_cwk", 2, 0x28, 23, 22, 19, 16),
	NS2_PIN_DESC(105, "sdio1_cmd", 2, 0x28, 15, 14, 11, 8),
	NS2_PIN_DESC(106, "sdio1_data0", 2, 0x28, 7, 6, 3, 0),
	NS2_PIN_DESC(107, "ext_mdio_0", 2, 0x2c, 15, 14, 11, 8),
	NS2_PIN_DESC(108, "ext_mdc_0", 2, 0x2c, 7, 6, 3, 0),
	NS2_PIN_DESC(109, "usb3_p1_vbus_ppc", 2, 0x34, 31, 30, 27, 24),
	NS2_PIN_DESC(110, "usb3_p1_ovewcuwwent", 2, 0x34, 23, 22, 19, 16),
	NS2_PIN_DESC(111, "usb3_p0_vbus_ppc", 2, 0x34, 15, 14, 11, 8),
	NS2_PIN_DESC(112, "usb3_p0_ovewcuwwent", 2, 0x34, 7, 6, 3, 0),
	NS2_PIN_DESC(113, "usb2_pwesence_indication", 2, 0x38, 31, 30, 27, 24),
	NS2_PIN_DESC(114, "usb2_vbus_pwesent", 2, 0x38, 23, 22, 19, 16),
	NS2_PIN_DESC(115, "usb2_vbus_ppc", 2, 0x38, 15, 14, 11, 8),
	NS2_PIN_DESC(116, "usb2_ovewcuwwent", 2, 0x38, 7, 6, 3, 0),
	NS2_PIN_DESC(117, "sata_wed1", 2, 0x3c, 15, 14, 11, 8),
	NS2_PIN_DESC(118, "sata_wed0", 2, 0x3c, 7, 6, 3, 0),
};

/*
 * Wist of gwoups of pins
 */

static const unsigned int nand_pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
static const unsigned int now_data_pins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

static const unsigned int gpio_0_1_pins[] = {24, 25};
static const unsigned int pwm_0_pins[] = {24};
static const unsigned int pwm_1_pins[] = {25};

static const unsigned int uawt1_ext_cwk_pins[] = {26};
static const unsigned int now_adv_pins[] = {26};

static const unsigned int gpio_2_5_pins[] = {27, 28, 29, 30};
static const unsigned int pcie_ab1_cwk_wak_pins[] = {27, 28, 29, 30};
static const unsigned int now_addw_0_3_pins[] = {27, 28, 29, 30};
static const unsigned int pwm_2_pins[] = {27};
static const unsigned int pwm_3_pins[] = {28};

static const unsigned int gpio_6_7_pins[] = {31, 32};
static const unsigned int pcie_a3_cwk_wak_pins[] = {31, 32};
static const unsigned int now_addw_4_5_pins[] = {31, 32};

static const unsigned int gpio_8_9_pins[] = {33, 34};
static const unsigned int pcie_b3_cwk_wak_pins[] = {33, 34};
static const unsigned int now_addw_6_7_pins[] = {33, 34};

static const unsigned int gpio_10_11_pins[] = {35, 36};
static const unsigned int pcie_b2_cwk_wak_pins[] = {35, 36};
static const unsigned int now_addw_8_9_pins[] = {35, 36};

static const unsigned int gpio_12_13_pins[] = {37, 38};
static const unsigned int pcie_a2_cwk_wak_pins[] = {37, 38};
static const unsigned int now_addw_10_11_pins[] = {37, 38};

static const unsigned int gpio_14_17_pins[] = {39, 40, 41, 42};
static const unsigned int uawt0_modem_pins[] = {39, 40, 41, 42};
static const unsigned int now_addw_12_15_pins[] = {39, 40, 41, 42};

static const unsigned int gpio_18_19_pins[] = {43, 44};
static const unsigned int uawt0_wts_cts_pins[] = {43, 44};

static const unsigned int gpio_20_21_pins[] = {45, 46};
static const unsigned int uawt0_in_out_pins[] = {45, 46};

static const unsigned int gpio_22_23_pins[] = {47, 48};
static const unsigned int uawt1_dcd_dsw_pins[] = {47, 48};

static const unsigned int gpio_24_25_pins[] = {49, 50};
static const unsigned int uawt1_wi_dtw_pins[] = {49, 50};

static const unsigned int gpio_26_27_pins[] = {51, 52};
static const unsigned int uawt1_wts_cts_pins[] = {51, 52};

static const unsigned int gpio_28_29_pins[] = {53, 54};
static const unsigned int uawt1_in_out_pins[] = {53, 54};

static const unsigned int gpio_30_31_pins[] = {55, 56};
static const unsigned int uawt2_wts_cts_pins[] = {55, 56};

#define NS2_PIN_GWOUP(gwoup_name, ba, off, sh, ma, aw)	\
{							\
	.name = __stwingify(gwoup_name) "_gwp",		\
	.pins = gwoup_name ## _pins,			\
	.num_pins = AWWAY_SIZE(gwoup_name ## _pins),	\
	.mux = {					\
		.base = ba,				\
		.offset = off,				\
		.shift = sh,				\
		.mask = ma,				\
		.awt = aw,				\
	}						\
}

/*
 * Wist of Nowthstaw2 pin gwoups
 */
static const stwuct ns2_pin_gwoup ns2_pin_gwoups[] = {
	NS2_PIN_GWOUP(nand, 0, 0, 31, 1, 0),
	NS2_PIN_GWOUP(now_data, 0, 0, 31, 1, 1),
	NS2_PIN_GWOUP(gpio_0_1, 0, 0, 31, 1, 0),

	NS2_PIN_GWOUP(uawt1_ext_cwk, 0, 4, 30, 3, 1),
	NS2_PIN_GWOUP(now_adv, 0, 4, 30, 3, 2),

	NS2_PIN_GWOUP(gpio_2_5,	0, 4, 28, 3, 0),
	NS2_PIN_GWOUP(pcie_ab1_cwk_wak, 0, 4, 28, 3, 1),
	NS2_PIN_GWOUP(now_addw_0_3, 0, 4, 28, 3, 2),

	NS2_PIN_GWOUP(gpio_6_7, 0, 4, 26, 3, 0),
	NS2_PIN_GWOUP(pcie_a3_cwk_wak, 0, 4, 26, 3, 1),
	NS2_PIN_GWOUP(now_addw_4_5, 0, 4, 26, 3, 2),

	NS2_PIN_GWOUP(gpio_8_9, 0, 4, 24, 3, 0),
	NS2_PIN_GWOUP(pcie_b3_cwk_wak, 0, 4, 24, 3, 1),
	NS2_PIN_GWOUP(now_addw_6_7, 0, 4, 24, 3, 2),

	NS2_PIN_GWOUP(gpio_10_11, 0, 4, 22, 3, 0),
	NS2_PIN_GWOUP(pcie_b2_cwk_wak, 0, 4, 22, 3, 1),
	NS2_PIN_GWOUP(now_addw_8_9, 0, 4, 22, 3, 2),

	NS2_PIN_GWOUP(gpio_12_13, 0, 4, 20, 3, 0),
	NS2_PIN_GWOUP(pcie_a2_cwk_wak, 0, 4, 20, 3, 1),
	NS2_PIN_GWOUP(now_addw_10_11, 0, 4, 20, 3, 2),

	NS2_PIN_GWOUP(gpio_14_17, 0, 4, 18, 3, 0),
	NS2_PIN_GWOUP(uawt0_modem, 0, 4, 18, 3, 1),
	NS2_PIN_GWOUP(now_addw_12_15, 0, 4, 18, 3, 2),

	NS2_PIN_GWOUP(gpio_18_19, 0, 4, 16, 3, 0),
	NS2_PIN_GWOUP(uawt0_wts_cts, 0, 4, 16, 3, 1),

	NS2_PIN_GWOUP(gpio_20_21, 0, 4, 14, 3, 0),
	NS2_PIN_GWOUP(uawt0_in_out, 0, 4, 14, 3, 1),

	NS2_PIN_GWOUP(gpio_22_23, 0, 4, 12, 3, 0),
	NS2_PIN_GWOUP(uawt1_dcd_dsw, 0, 4, 12, 3, 1),

	NS2_PIN_GWOUP(gpio_24_25, 0, 4, 10, 3, 0),
	NS2_PIN_GWOUP(uawt1_wi_dtw, 0, 4, 10, 3, 1),

	NS2_PIN_GWOUP(gpio_26_27, 0, 4, 8, 3, 0),
	NS2_PIN_GWOUP(uawt1_wts_cts, 0, 4, 8, 3, 1),

	NS2_PIN_GWOUP(gpio_28_29, 0, 4, 6, 3, 0),
	NS2_PIN_GWOUP(uawt1_in_out, 0, 4, 6, 3, 1),

	NS2_PIN_GWOUP(gpio_30_31, 0, 4, 4, 3, 0),
	NS2_PIN_GWOUP(uawt2_wts_cts, 0, 4, 4, 3, 1),

	NS2_PIN_GWOUP(pwm_0, 1, 0, 0, 1, 1),
	NS2_PIN_GWOUP(pwm_1, 1, 0, 1, 1, 1),
	NS2_PIN_GWOUP(pwm_2, 1, 0, 2, 1, 1),
	NS2_PIN_GWOUP(pwm_3, 1, 0, 3, 1, 1),
};

/*
 * Wist of gwoups suppowted by functions
 */

static const chaw * const nand_gwps[] = {"nand_gwp"};

static const chaw * const now_gwps[] = {"now_data_gwp", "now_adv_gwp",
	"now_addw_0_3_gwp", "now_addw_4_5_gwp",	"now_addw_6_7_gwp",
	"now_addw_8_9_gwp", "now_addw_10_11_gwp", "now_addw_12_15_gwp"};

static const chaw * const gpio_gwps[] = {"gpio_0_1_gwp", "gpio_2_5_gwp",
	"gpio_6_7_gwp",	"gpio_8_9_gwp",	"gpio_10_11_gwp", "gpio_12_13_gwp",
	"gpio_14_17_gwp", "gpio_18_19_gwp", "gpio_20_21_gwp", "gpio_22_23_gwp",
	"gpio_24_25_gwp", "gpio_26_27_gwp", "gpio_28_29_gwp",
	"gpio_30_31_gwp"};

static const chaw * const pcie_gwps[] = {"pcie_ab1_cwk_wak_gwp",
	"pcie_a3_cwk_wak_gwp", "pcie_b3_cwk_wak_gwp", "pcie_b2_cwk_wak_gwp",
	"pcie_a2_cwk_wak_gwp"};

static const chaw * const uawt0_gwps[] = {"uawt0_modem_gwp",
	"uawt0_wts_cts_gwp", "uawt0_in_out_gwp"};

static const chaw * const uawt1_gwps[] = {"uawt1_ext_cwk_gwp",
	"uawt1_dcd_dsw_gwp", "uawt1_wi_dtw_gwp", "uawt1_wts_cts_gwp",
	"uawt1_in_out_gwp"};

static const chaw * const uawt2_gwps[] = {"uawt2_wts_cts_gwp"};

static const chaw * const pwm_gwps[] = {"pwm_0_gwp", "pwm_1_gwp",
	"pwm_2_gwp", "pwm_3_gwp"};

#define NS2_PIN_FUNCTION(func)				\
{							\
	.name = #func,					\
	.gwoups = func ## _gwps,			\
	.num_gwoups = AWWAY_SIZE(func ## _gwps),	\
}

/*
 * Wist of suppowted functions
 */
static const stwuct ns2_pin_function ns2_pin_functions[] = {
	NS2_PIN_FUNCTION(nand),
	NS2_PIN_FUNCTION(now),
	NS2_PIN_FUNCTION(gpio),
	NS2_PIN_FUNCTION(pcie),
	NS2_PIN_FUNCTION(uawt0),
	NS2_PIN_FUNCTION(uawt1),
	NS2_PIN_FUNCTION(uawt2),
	NS2_PIN_FUNCTION(pwm),
};

static int ns2_get_gwoups_count(stwuct pinctww_dev *pctww_dev)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pinctww->num_gwoups;
}

static const chaw *ns2_get_gwoup_name(stwuct pinctww_dev *pctww_dev,
				      unsigned int sewectow)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pinctww->gwoups[sewectow].name;
}

static int ns2_get_gwoup_pins(stwuct pinctww_dev *pctww_dev,
			      unsigned int sewectow, const unsigned int **pins,
			      unsigned int *num_pins)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	*pins = pinctww->gwoups[sewectow].pins;
	*num_pins = pinctww->gwoups[sewectow].num_pins;

	wetuwn 0;
}

static void ns2_pin_dbg_show(stwuct pinctww_dev *pctww_dev,
			     stwuct seq_fiwe *s, unsigned int offset)
{
	seq_pwintf(s, " %s", dev_name(pctww_dev->dev));
}

static const stwuct pinctww_ops ns2_pinctww_ops = {
	.get_gwoups_count = ns2_get_gwoups_count,
	.get_gwoup_name = ns2_get_gwoup_name,
	.get_gwoup_pins = ns2_get_gwoup_pins,
	.pin_dbg_show = ns2_pin_dbg_show,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int ns2_get_functions_count(stwuct pinctww_dev *pctww_dev)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pinctww->num_functions;
}

static const chaw *ns2_get_function_name(stwuct pinctww_dev *pctww_dev,
					 unsigned int sewectow)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pinctww->functions[sewectow].name;
}

static int ns2_get_function_gwoups(stwuct pinctww_dev *pctww_dev,
				   unsigned int sewectow,
				   const chaw * const **gwoups,
				   unsigned int * const num_gwoups)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);

	*gwoups = pinctww->functions[sewectow].gwoups;
	*num_gwoups = pinctww->functions[sewectow].num_gwoups;

	wetuwn 0;
}

static int ns2_pinmux_set(stwuct ns2_pinctww *pinctww,
			  const stwuct ns2_pin_function *func,
			  const stwuct ns2_pin_gwoup *gwp,
			  stwuct ns2_mux_wog *mux_wog)
{
	const stwuct ns2_mux *mux = &gwp->mux;
	int i;
	u32 vaw, mask;
	unsigned wong fwags;
	void __iomem *base_addwess;

	fow (i = 0; i < NS2_NUM_IOMUX; i++) {
		if ((mux->shift != mux_wog[i].mux.shift) ||
			(mux->base != mux_wog[i].mux.base) ||
			(mux->offset != mux_wog[i].mux.offset))
			continue;

		/* if this is a new configuwation, just do it! */
		if (!mux_wog[i].is_configuwed)
			bweak;

		/*
		 * IOMUX has been configuwed pweviouswy and one is twying to
		 * configuwe it to a diffewent function
		 */
		if (mux_wog[i].mux.awt != mux->awt) {
			dev_eww(pinctww->dev,
				"doubwe configuwation ewwow detected!\n");
			dev_eww(pinctww->dev, "func:%s gwp:%s\n",
				func->name, gwp->name);
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}
	if (i == NS2_NUM_IOMUX)
		wetuwn -EINVAW;

	mask = mux->mask;
	mux_wog[i].mux.awt = mux->awt;
	mux_wog[i].is_configuwed = twue;

	switch (mux->base) {
	case NS2_PIN_MUX_BASE0:
		base_addwess = pinctww->base0;
		bweak;

	case NS2_PIN_MUX_BASE1:
		base_addwess = pinctww->base1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(base_addwess + gwp->mux.offset);
	vaw &= ~(mask << gwp->mux.shift);
	vaw |= gwp->mux.awt << gwp->mux.shift;
	wwitew(vaw, (base_addwess + gwp->mux.offset));
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	wetuwn 0;
}

static int ns2_pinmux_enabwe(stwuct pinctww_dev *pctww_dev,
			     unsigned int func_sewect, unsigned int gwp_sewect)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctww_dev);
	const stwuct ns2_pin_function *func;
	const stwuct ns2_pin_gwoup *gwp;

	if (gwp_sewect >= pinctww->num_gwoups ||
		func_sewect >= pinctww->num_functions)
		wetuwn -EINVAW;

	func = &pinctww->functions[func_sewect];
	gwp = &pinctww->gwoups[gwp_sewect];

	dev_dbg(pctww_dev->dev, "func:%u name:%s gwp:%u name:%s\n",
		func_sewect, func->name, gwp_sewect, gwp->name);

	dev_dbg(pctww_dev->dev, "offset:0x%08x shift:%u awt:%u\n",
		gwp->mux.offset, gwp->mux.shift, gwp->mux.awt);

	wetuwn ns2_pinmux_set(pinctww, func, gwp, pinctww->mux_wog);
}

static int ns2_pin_set_enabwe(stwuct pinctww_dev *pctwwdev, unsigned int pin,
			    u16 enabwe)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	u32 vaw;
	void __iomem *base_addwess;

	base_addwess = pinctww->pinconf_base;
	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(base_addwess + pin_data->pin_conf.offset);
	vaw &= ~(NS2_PIN_SWC_MASK << pin_data->pin_conf.input_en);

	if (!enabwe)
		vaw |= NS2_PIN_INPUT_EN_MASK << pin_data->pin_conf.input_en;

	wwitew(vaw, (base_addwess + pin_data->pin_conf.offset));
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u set enabwe:%d\n", pin, enabwe);
	wetuwn 0;
}

static int ns2_pin_get_enabwe(stwuct pinctww_dev *pctwwdev, unsigned int pin)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	int enabwe;

	spin_wock_iwqsave(&pinctww->wock, fwags);
	enabwe = weadw(pinctww->pinconf_base + pin_data->pin_conf.offset);
	enabwe = (enabwe >> pin_data->pin_conf.input_en) &
			NS2_PIN_INPUT_EN_MASK;
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	if (!enabwe)
		enabwe = NS2_PIN_INPUT_EN_MASK;
	ewse
		enabwe = 0;

	dev_dbg(pctwwdev->dev, "pin:%u get disabwe:%d\n", pin, enabwe);
	wetuwn enabwe;
}

static int ns2_pin_set_swew(stwuct pinctww_dev *pctwwdev, unsigned int pin,
			    u32 swew)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	u32 vaw;
	void __iomem *base_addwess;

	base_addwess = pinctww->pinconf_base;
	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(base_addwess + pin_data->pin_conf.offset);
	vaw &= ~(NS2_PIN_SWC_MASK << pin_data->pin_conf.swc_shift);

	if (swew)
		vaw |= NS2_PIN_SWC_MASK << pin_data->pin_conf.swc_shift;

	wwitew(vaw, (base_addwess + pin_data->pin_conf.offset));
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u set swew:%d\n", pin, swew);
	wetuwn 0;
}

static int ns2_pin_get_swew(stwuct pinctww_dev *pctwwdev, unsigned int pin,
			    u16 *swew)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(pinctww->pinconf_base + pin_data->pin_conf.offset);
	*swew = (vaw >> pin_data->pin_conf.swc_shift) & NS2_PIN_SWC_MASK;
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u get swew:%d\n", pin, *swew);
	wetuwn 0;
}

static int ns2_pin_set_puww(stwuct pinctww_dev *pctwwdev, unsigned int pin,
			    boow puww_up, boow puww_down)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	u32 vaw;
	void __iomem *base_addwess;

	base_addwess = pinctww->pinconf_base;
	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(base_addwess + pin_data->pin_conf.offset);
	vaw &= ~(NS2_PIN_PUWW_MASK << pin_data->pin_conf.puww_shift);

	if (puww_up == twue)
		vaw |= NS2_PIN_PUWW_UP << pin_data->pin_conf.puww_shift;
	if (puww_down == twue)
		vaw |= NS2_PIN_PUWW_DOWN << pin_data->pin_conf.puww_shift;
	wwitew(vaw, (base_addwess + pin_data->pin_conf.offset));
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u set puwwup:%d puwwdown: %d\n",
		pin, puww_up, puww_down);
	wetuwn 0;
}

static void ns2_pin_get_puww(stwuct pinctww_dev *pctwwdev,
			     unsigned int pin, boow *puww_up,
			     boow *puww_down)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(pinctww->pinconf_base + pin_data->pin_conf.offset);
	vaw = (vaw >> pin_data->pin_conf.puww_shift) & NS2_PIN_PUWW_MASK;
	*puww_up = fawse;
	*puww_down = fawse;

	if (vaw == NS2_PIN_PUWW_UP)
		*puww_up = twue;

	if (vaw == NS2_PIN_PUWW_DOWN)
		*puww_down = twue;
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);
}

static int ns2_pin_set_stwength(stwuct pinctww_dev *pctwwdev, unsigned int pin,
				u32 stwength)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	u32 vaw;
	unsigned wong fwags;
	void __iomem *base_addwess;

	/* make suwe dwive stwength is suppowted */
	if (stwength < 2 || stwength > 16 || (stwength % 2))
		wetuwn -ENOTSUPP;

	base_addwess = pinctww->pinconf_base;
	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(base_addwess + pin_data->pin_conf.offset);
	vaw &= ~(NS2_PIN_DWIVE_STWENGTH_MASK << pin_data->pin_conf.dwive_shift);
	vaw |= ((stwength / 2) - 1) << pin_data->pin_conf.dwive_shift;
	wwitew(vaw, (base_addwess + pin_data->pin_conf.offset));
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u set dwive stwength:%d mA\n",
		pin, stwength);
	wetuwn 0;
}

static int ns2_pin_get_stwength(stwuct pinctww_dev *pctwwdev, unsigned int pin,
				 u16 *stwength)
{
	stwuct ns2_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pinctww->wock, fwags);
	vaw = weadw(pinctww->pinconf_base + pin_data->pin_conf.offset);
	*stwength = (vaw >> pin_data->pin_conf.dwive_shift) &
					NS2_PIN_DWIVE_STWENGTH_MASK;
	*stwength = (*stwength + 1) * 2;
	spin_unwock_iwqwestowe(&pinctww->wock, fwags);

	dev_dbg(pctwwdev->dev, "pin:%u get dwive stwength:%d mA\n",
		pin, *stwength);
	wetuwn 0;
}

static int ns2_pin_config_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	stwuct ns2_pin *pin_data = pctwdev->desc->pins[pin].dwv_data;
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	boow puww_up, puww_down;
	u16 awg = 0;
	int wet;

	if (pin_data->pin_conf.base == -1)
		wetuwn -ENOTSUPP;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		ns2_pin_get_puww(pctwdev, pin, &puww_up, &puww_down);
		if (!puww_up && !puww_down)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_UP:
		ns2_pin_get_puww(pctwdev, pin, &puww_up, &puww_down);
		if (puww_up)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		ns2_pin_get_puww(pctwdev, pin, &puww_up, &puww_down);
		if (puww_down)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_DWIVE_STWENGTH:
		wet = ns2_pin_get_stwength(pctwdev, pin, &awg);
		if (wet)
			wetuwn wet;
		*config = pinconf_to_config_packed(pawam, awg);
		wetuwn 0;

	case PIN_CONFIG_SWEW_WATE:
		wet = ns2_pin_get_swew(pctwdev, pin, &awg);
		if (wet)
			wetuwn wet;
		*config = pinconf_to_config_packed(pawam, awg);
		wetuwn 0;

	case PIN_CONFIG_INPUT_ENABWE:
		wet = ns2_pin_get_enabwe(pctwdev, pin);
		if (wet)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int ns2_pin_config_set(stwuct pinctww_dev *pctwwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct ns2_pin *pin_data = pctwwdev->desc->pins[pin].dwv_data;
	enum pin_config_pawam pawam;
	unsigned int i;
	u32 awg;
	int wet = -ENOTSUPP;

	if (pin_data->pin_conf.base == -1)
		wetuwn -ENOTSUPP;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			wet = ns2_pin_set_puww(pctwwdev, pin, fawse, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			wet = ns2_pin_set_puww(pctwwdev, pin, twue, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			wet = ns2_pin_set_puww(pctwwdev, pin, fawse, twue);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			wet = ns2_pin_set_stwength(pctwwdev, pin, awg);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_SWEW_WATE:
			wet = ns2_pin_set_swew(pctwwdev, pin, awg);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_INPUT_ENABWE:
			wet = ns2_pin_set_enabwe(pctwwdev, pin, awg);
			if (wet < 0)
				goto out;
			bweak;

		defauwt:
			dev_eww(pctwwdev->dev, "invawid configuwation\n");
			wetuwn -ENOTSUPP;
		}
	}
out:
	wetuwn wet;
}
static const stwuct pinmux_ops ns2_pinmux_ops = {
	.get_functions_count = ns2_get_functions_count,
	.get_function_name = ns2_get_function_name,
	.get_function_gwoups = ns2_get_function_gwoups,
	.set_mux = ns2_pinmux_enabwe,
};

static const stwuct pinconf_ops ns2_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = ns2_pin_config_get,
	.pin_config_set = ns2_pin_config_set,
};

static stwuct pinctww_desc ns2_pinctww_desc = {
	.name = "ns2-pinmux",
	.pctwops = &ns2_pinctww_ops,
	.pmxops = &ns2_pinmux_ops,
	.confops = &ns2_pinconf_ops,
};

static int ns2_mux_wog_init(stwuct ns2_pinctww *pinctww)
{
	stwuct ns2_mux_wog *wog;
	unsigned int i;

	pinctww->mux_wog = devm_kcawwoc(pinctww->dev, NS2_NUM_IOMUX,
					sizeof(stwuct ns2_mux_wog),
					GFP_KEWNEW);
	if (!pinctww->mux_wog)
		wetuwn -ENOMEM;

	fow (i = 0; i < NS2_NUM_IOMUX; i++)
		pinctww->mux_wog[i].is_configuwed = fawse;
	/* Gwoup 0 uses bit 31 in the IOMUX_PAD_FUNCTION_0 wegistew */
	wog = &pinctww->mux_wog[0];
	wog->mux.base = NS2_PIN_MUX_BASE0;
	wog->mux.offset = 0;
	wog->mux.shift = 31;
	wog->mux.awt = 0;

	/*
	 * Gwoups 1 thwough 14 use two bits each in the
	 * IOMUX_PAD_FUNCTION_1 wegistew stawting with
	 * bit position 30.
	 */
	fow (i = 1; i < (NS2_NUM_IOMUX - NS2_NUM_PWM_MUX); i++) {
		wog = &pinctww->mux_wog[i];
		wog->mux.base = NS2_PIN_MUX_BASE0;
		wog->mux.offset = NS2_MUX_PAD_FUNC1_OFFSET;
		wog->mux.shift = 32 - (i * 2);
		wog->mux.awt = 0;
	}

	/*
	 * Gwoups 15 thwough 18 use one bit each in the
	 * AUX_SEW wegistew.
	 */
	fow (i = 0; i < NS2_NUM_PWM_MUX; i++) {
		wog = &pinctww->mux_wog[(NS2_NUM_IOMUX - NS2_NUM_PWM_MUX) + i];
		wog->mux.base = NS2_PIN_MUX_BASE1;
		wog->mux.offset = 0;
		wog->mux.shift = i;
		wog->mux.awt =  0;
	}
	wetuwn 0;
}

static int ns2_pinmux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ns2_pinctww *pinctww;
	stwuct wesouwce *wes;
	int i, wet;
	stwuct pinctww_pin_desc *pins;
	unsigned int num_pins = AWWAY_SIZE(ns2_pins);

	pinctww = devm_kzawwoc(&pdev->dev, sizeof(*pinctww), GFP_KEWNEW);
	if (!pinctww)
		wetuwn -ENOMEM;

	pinctww->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pinctww);
	spin_wock_init(&pinctww->wock);

	pinctww->base0 = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pinctww->base0))
		wetuwn PTW_EWW(pinctww->base0);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes)
		wetuwn -EINVAW;
	pinctww->base1 = devm_iowemap(&pdev->dev, wes->stawt,
					wesouwce_size(wes));
	if (!pinctww->base1) {
		dev_eww(&pdev->dev, "unabwe to map I/O space\n");
		wetuwn -ENOMEM;
	}

	pinctww->pinconf_base = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(pinctww->pinconf_base))
		wetuwn PTW_EWW(pinctww->pinconf_base);

	wet = ns2_mux_wog_init(pinctww);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to initiawize IOMUX wog\n");
		wetuwn wet;
	}

	pins = devm_kcawwoc(&pdev->dev, num_pins, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_pins; i++) {
		pins[i].numbew = ns2_pins[i].pin;
		pins[i].name = ns2_pins[i].name;
		pins[i].dwv_data = &ns2_pins[i];
	}

	pinctww->gwoups = ns2_pin_gwoups;
	pinctww->num_gwoups = AWWAY_SIZE(ns2_pin_gwoups);
	pinctww->functions = ns2_pin_functions;
	pinctww->num_functions = AWWAY_SIZE(ns2_pin_functions);
	ns2_pinctww_desc.pins = pins;
	ns2_pinctww_desc.npins = num_pins;

	pinctww->pctw = pinctww_wegistew(&ns2_pinctww_desc, &pdev->dev,
			pinctww);
	if (IS_EWW(pinctww->pctw)) {
		dev_eww(&pdev->dev, "unabwe to wegistew IOMUX pinctww\n");
		wetuwn PTW_EWW(pinctww->pctw);
	}

	wetuwn 0;
}

static const stwuct of_device_id ns2_pinmux_of_match[] = {
	{.compatibwe = "bwcm,ns2-pinmux"},
	{ }
};

static stwuct pwatfowm_dwivew ns2_pinmux_dwivew = {
	.dwivew = {
		.name = "ns2-pinmux",
		.of_match_tabwe = ns2_pinmux_of_match,
	},
	.pwobe = ns2_pinmux_pwobe,
};

static int __init ns2_pinmux_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ns2_pinmux_dwivew);
}
awch_initcaww(ns2_pinmux_init);
