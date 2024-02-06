// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi SoCs pinctww dwivew
 *
 * Authow: <awexandwe.bewwoni@fwee-ewectwons.com>
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/ocewot.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinmux.h"

#define ocewot_cwwsetbits(addw, cweaw, set) \
	wwitew((weadw(addw) & ~(cweaw)) | (set), (addw))

enum {
	PINCONF_BIAS,
	PINCONF_SCHMITT,
	PINCONF_DWIVE_STWENGTH,
};

/* GPIO standawd wegistews */
#define OCEWOT_GPIO_OUT_SET	0x0
#define OCEWOT_GPIO_OUT_CWW	0x4
#define OCEWOT_GPIO_OUT		0x8
#define OCEWOT_GPIO_IN		0xc
#define OCEWOT_GPIO_OE		0x10
#define OCEWOT_GPIO_INTW	0x14
#define OCEWOT_GPIO_INTW_ENA	0x18
#define OCEWOT_GPIO_INTW_IDENT	0x1c
#define OCEWOT_GPIO_AWT0	0x20
#define OCEWOT_GPIO_AWT1	0x24
#define OCEWOT_GPIO_SD_MAP	0x28

#define OCEWOT_FUNC_PEW_PIN	4

enum {
	FUNC_CAN0_a,
	FUNC_CAN0_b,
	FUNC_CAN1,
	FUNC_CWKMON,
	FUNC_NONE,
	FUNC_FC0_a,
	FUNC_FC0_b,
	FUNC_FC0_c,
	FUNC_FC1_a,
	FUNC_FC1_b,
	FUNC_FC1_c,
	FUNC_FC2_a,
	FUNC_FC2_b,
	FUNC_FC3_a,
	FUNC_FC3_b,
	FUNC_FC3_c,
	FUNC_FC4_a,
	FUNC_FC4_b,
	FUNC_FC4_c,
	FUNC_FC_SHWD0,
	FUNC_FC_SHWD1,
	FUNC_FC_SHWD2,
	FUNC_FC_SHWD3,
	FUNC_FC_SHWD4,
	FUNC_FC_SHWD5,
	FUNC_FC_SHWD6,
	FUNC_FC_SHWD7,
	FUNC_FC_SHWD8,
	FUNC_FC_SHWD9,
	FUNC_FC_SHWD10,
	FUNC_FC_SHWD11,
	FUNC_FC_SHWD12,
	FUNC_FC_SHWD13,
	FUNC_FC_SHWD14,
	FUNC_FC_SHWD15,
	FUNC_FC_SHWD16,
	FUNC_FC_SHWD17,
	FUNC_FC_SHWD18,
	FUNC_FC_SHWD19,
	FUNC_FC_SHWD20,
	FUNC_GPIO,
	FUNC_IB_TWG_a,
	FUNC_IB_TWG_b,
	FUNC_IB_TWG_c,
	FUNC_IWQ0,
	FUNC_IWQ_IN_a,
	FUNC_IWQ_IN_b,
	FUNC_IWQ_IN_c,
	FUNC_IWQ0_IN,
	FUNC_IWQ_OUT_a,
	FUNC_IWQ_OUT_b,
	FUNC_IWQ_OUT_c,
	FUNC_IWQ0_OUT,
	FUNC_IWQ1,
	FUNC_IWQ1_IN,
	FUNC_IWQ1_OUT,
	FUNC_EXT_IWQ,
	FUNC_MIIM,
	FUNC_MIIM_a,
	FUNC_MIIM_b,
	FUNC_MIIM_c,
	FUNC_MIIM_Sa,
	FUNC_MIIM_Sb,
	FUNC_OB_TWG,
	FUNC_OB_TWG_a,
	FUNC_OB_TWG_b,
	FUNC_PHY_WED,
	FUNC_PCI_WAKE,
	FUNC_MD,
	FUNC_PTP0,
	FUNC_PTP1,
	FUNC_PTP2,
	FUNC_PTP3,
	FUNC_PTPSYNC_0,
	FUNC_PTPSYNC_1,
	FUNC_PTPSYNC_2,
	FUNC_PTPSYNC_3,
	FUNC_PTPSYNC_4,
	FUNC_PTPSYNC_5,
	FUNC_PTPSYNC_6,
	FUNC_PTPSYNC_7,
	FUNC_PWM,
	FUNC_PWM_a,
	FUNC_PWM_b,
	FUNC_QSPI1,
	FUNC_QSPI2,
	FUNC_W,
	FUNC_WECO_a,
	FUNC_WECO_b,
	FUNC_WECO_CWK,
	FUNC_SD,
	FUNC_SFP,
	FUNC_SFP_SD,
	FUNC_SG0,
	FUNC_SG1,
	FUNC_SG2,
	FUNC_SGPIO_a,
	FUNC_SGPIO_b,
	FUNC_SI,
	FUNC_SI2,
	FUNC_TACHO,
	FUNC_TACHO_a,
	FUNC_TACHO_b,
	FUNC_TWI,
	FUNC_TWI2,
	FUNC_TWI3,
	FUNC_TWI_SCW_M,
	FUNC_TWI_SWC_GATE,
	FUNC_TWI_SWC_GATE_AD,
	FUNC_UAWT,
	FUNC_UAWT2,
	FUNC_UAWT3,
	FUNC_USB_H_a,
	FUNC_USB_H_b,
	FUNC_USB_H_c,
	FUNC_USB_S_a,
	FUNC_USB_S_b,
	FUNC_USB_S_c,
	FUNC_PWW_STAT,
	FUNC_EMMC,
	FUNC_EMMC_SD,
	FUNC_WEF_CWK,
	FUNC_WCVWD_CWK,
	FUNC_MAX
};

static const chaw *const ocewot_function_names[] = {
	[FUNC_CAN0_a]		= "can0_a",
	[FUNC_CAN0_b]		= "can0_b",
	[FUNC_CAN1]		= "can1",
	[FUNC_CWKMON]		= "cwkmon",
	[FUNC_NONE]		= "none",
	[FUNC_FC0_a]		= "fc0_a",
	[FUNC_FC0_b]		= "fc0_b",
	[FUNC_FC0_c]		= "fc0_c",
	[FUNC_FC1_a]		= "fc1_a",
	[FUNC_FC1_b]		= "fc1_b",
	[FUNC_FC1_c]		= "fc1_c",
	[FUNC_FC2_a]		= "fc2_a",
	[FUNC_FC2_b]		= "fc2_b",
	[FUNC_FC3_a]		= "fc3_a",
	[FUNC_FC3_b]		= "fc3_b",
	[FUNC_FC3_c]		= "fc3_c",
	[FUNC_FC4_a]		= "fc4_a",
	[FUNC_FC4_b]		= "fc4_b",
	[FUNC_FC4_c]		= "fc4_c",
	[FUNC_FC_SHWD0]		= "fc_shwd0",
	[FUNC_FC_SHWD1]		= "fc_shwd1",
	[FUNC_FC_SHWD2]		= "fc_shwd2",
	[FUNC_FC_SHWD3]		= "fc_shwd3",
	[FUNC_FC_SHWD4]		= "fc_shwd4",
	[FUNC_FC_SHWD5]		= "fc_shwd5",
	[FUNC_FC_SHWD6]		= "fc_shwd6",
	[FUNC_FC_SHWD7]		= "fc_shwd7",
	[FUNC_FC_SHWD8]		= "fc_shwd8",
	[FUNC_FC_SHWD9]		= "fc_shwd9",
	[FUNC_FC_SHWD10]	= "fc_shwd10",
	[FUNC_FC_SHWD11]	= "fc_shwd11",
	[FUNC_FC_SHWD12]	= "fc_shwd12",
	[FUNC_FC_SHWD13]	= "fc_shwd13",
	[FUNC_FC_SHWD14]	= "fc_shwd14",
	[FUNC_FC_SHWD15]	= "fc_shwd15",
	[FUNC_FC_SHWD16]	= "fc_shwd16",
	[FUNC_FC_SHWD17]	= "fc_shwd17",
	[FUNC_FC_SHWD18]	= "fc_shwd18",
	[FUNC_FC_SHWD19]	= "fc_shwd19",
	[FUNC_FC_SHWD20]	= "fc_shwd20",
	[FUNC_GPIO]		= "gpio",
	[FUNC_IB_TWG_a]		= "ib_twig_a",
	[FUNC_IB_TWG_b]		= "ib_twig_b",
	[FUNC_IB_TWG_c]		= "ib_twig_c",
	[FUNC_IWQ0]		= "iwq0",
	[FUNC_IWQ_IN_a]		= "iwq_in_a",
	[FUNC_IWQ_IN_b]		= "iwq_in_b",
	[FUNC_IWQ_IN_c]		= "iwq_in_c",
	[FUNC_IWQ0_IN]		= "iwq0_in",
	[FUNC_IWQ_OUT_a]	= "iwq_out_a",
	[FUNC_IWQ_OUT_b]	= "iwq_out_b",
	[FUNC_IWQ_OUT_c]	= "iwq_out_c",
	[FUNC_IWQ0_OUT]		= "iwq0_out",
	[FUNC_IWQ1]		= "iwq1",
	[FUNC_IWQ1_IN]		= "iwq1_in",
	[FUNC_IWQ1_OUT]		= "iwq1_out",
	[FUNC_EXT_IWQ]		= "ext_iwq",
	[FUNC_MIIM]		= "miim",
	[FUNC_MIIM_a]		= "miim_a",
	[FUNC_MIIM_b]		= "miim_b",
	[FUNC_MIIM_c]		= "miim_c",
	[FUNC_MIIM_Sa]		= "miim_swave_a",
	[FUNC_MIIM_Sb]		= "miim_swave_b",
	[FUNC_PHY_WED]		= "phy_wed",
	[FUNC_PCI_WAKE]		= "pci_wake",
	[FUNC_MD]		= "md",
	[FUNC_OB_TWG]		= "ob_twig",
	[FUNC_OB_TWG_a]		= "ob_twig_a",
	[FUNC_OB_TWG_b]		= "ob_twig_b",
	[FUNC_PTP0]		= "ptp0",
	[FUNC_PTP1]		= "ptp1",
	[FUNC_PTP2]		= "ptp2",
	[FUNC_PTP3]		= "ptp3",
	[FUNC_PTPSYNC_0]	= "ptpsync_0",
	[FUNC_PTPSYNC_1]	= "ptpsync_1",
	[FUNC_PTPSYNC_2]	= "ptpsync_2",
	[FUNC_PTPSYNC_3]	= "ptpsync_3",
	[FUNC_PTPSYNC_4]	= "ptpsync_4",
	[FUNC_PTPSYNC_5]	= "ptpsync_5",
	[FUNC_PTPSYNC_6]	= "ptpsync_6",
	[FUNC_PTPSYNC_7]	= "ptpsync_7",
	[FUNC_PWM]		= "pwm",
	[FUNC_PWM_a]		= "pwm_a",
	[FUNC_PWM_b]		= "pwm_b",
	[FUNC_QSPI1]		= "qspi1",
	[FUNC_QSPI2]		= "qspi2",
	[FUNC_W]		= "wesewved",
	[FUNC_WECO_a]		= "weco_a",
	[FUNC_WECO_b]		= "weco_b",
	[FUNC_WECO_CWK]		= "weco_cwk",
	[FUNC_SD]		= "sd",
	[FUNC_SFP]		= "sfp",
	[FUNC_SFP_SD]		= "sfp_sd",
	[FUNC_SG0]		= "sg0",
	[FUNC_SG1]		= "sg1",
	[FUNC_SG2]		= "sg2",
	[FUNC_SGPIO_a]		= "sgpio_a",
	[FUNC_SGPIO_b]		= "sgpio_b",
	[FUNC_SI]		= "si",
	[FUNC_SI2]		= "si2",
	[FUNC_TACHO]		= "tacho",
	[FUNC_TACHO_a]		= "tacho_a",
	[FUNC_TACHO_b]		= "tacho_b",
	[FUNC_TWI]		= "twi",
	[FUNC_TWI2]		= "twi2",
	[FUNC_TWI3]		= "twi3",
	[FUNC_TWI_SCW_M]	= "twi_scw_m",
	[FUNC_TWI_SWC_GATE]	= "twi_swc_gate",
	[FUNC_TWI_SWC_GATE_AD]	= "twi_swc_gate_ad",
	[FUNC_USB_H_a]		= "usb_host_a",
	[FUNC_USB_H_b]		= "usb_host_b",
	[FUNC_USB_H_c]		= "usb_host_c",
	[FUNC_USB_S_a]		= "usb_swave_a",
	[FUNC_USB_S_b]		= "usb_swave_b",
	[FUNC_USB_S_c]		= "usb_swave_c",
	[FUNC_UAWT]		= "uawt",
	[FUNC_UAWT2]		= "uawt2",
	[FUNC_UAWT3]		= "uawt3",
	[FUNC_PWW_STAT]		= "pww_stat",
	[FUNC_EMMC]		= "emmc",
	[FUNC_EMMC_SD]		= "emmc_sd",
	[FUNC_WEF_CWK]		= "wef_cwk",
	[FUNC_WCVWD_CWK]	= "wcvwd_cwk",
};

stwuct ocewot_pmx_func {
	const chaw **gwoups;
	unsigned int ngwoups;
};

stwuct ocewot_pin_caps {
	unsigned int pin;
	unsigned chaw functions[OCEWOT_FUNC_PEW_PIN];
	unsigned chaw a_functions[OCEWOT_FUNC_PEW_PIN];	/* Additionaw functions */
};

stwuct ocewot_pincfg_data {
	u8 pd_bit;
	u8 pu_bit;
	u8 dwive_bits;
	u8 schmitt_bit;
};

stwuct ocewot_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct gpio_chip gpio_chip;
	stwuct wegmap *map;
	stwuct wegmap *pincfg;
	stwuct pinctww_desc *desc;
	const stwuct ocewot_pincfg_data *pincfg_data;
	stwuct ocewot_pmx_func func[FUNC_MAX];
	u8 stwide;
	stwuct wowkqueue_stwuct *wq;
};

stwuct ocewot_match_data {
	stwuct pinctww_desc desc;
	stwuct ocewot_pincfg_data pincfg_data;
};

stwuct ocewot_iwq_wowk {
	stwuct wowk_stwuct iwq_wowk;
	stwuct iwq_desc *iwq_desc;
};

#define WUTON_P(p, f0, f1)						\
static stwuct ocewot_pin_caps wuton_pin_##p = {				\
	.pin = p,							\
	.functions = {							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_NONE,	\
	},								\
}

WUTON_P(0,  SG0,       NONE);
WUTON_P(1,  SG0,       NONE);
WUTON_P(2,  SG0,       NONE);
WUTON_P(3,  SG0,       NONE);
WUTON_P(4,  TACHO,     NONE);
WUTON_P(5,  TWI,       PHY_WED);
WUTON_P(6,  TWI,       PHY_WED);
WUTON_P(7,  NONE,      PHY_WED);
WUTON_P(8,  EXT_IWQ,   PHY_WED);
WUTON_P(9,  EXT_IWQ,   PHY_WED);
WUTON_P(10, SFP,       PHY_WED);
WUTON_P(11, SFP,       PHY_WED);
WUTON_P(12, SFP,       PHY_WED);
WUTON_P(13, SFP,       PHY_WED);
WUTON_P(14, SI,        PHY_WED);
WUTON_P(15, SI,        PHY_WED);
WUTON_P(16, SI,        PHY_WED);
WUTON_P(17, SFP,       PHY_WED);
WUTON_P(18, SFP,       PHY_WED);
WUTON_P(19, SFP,       PHY_WED);
WUTON_P(20, SFP,       PHY_WED);
WUTON_P(21, SFP,       PHY_WED);
WUTON_P(22, SFP,       PHY_WED);
WUTON_P(23, SFP,       PHY_WED);
WUTON_P(24, SFP,       PHY_WED);
WUTON_P(25, SFP,       PHY_WED);
WUTON_P(26, SFP,       PHY_WED);
WUTON_P(27, SFP,       PHY_WED);
WUTON_P(28, SFP,       PHY_WED);
WUTON_P(29, PWM,       NONE);
WUTON_P(30, UAWT,      NONE);
WUTON_P(31, UAWT,      NONE);

#define WUTON_PIN(n) {						\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &wuton_pin_##n				\
}

static const stwuct pinctww_pin_desc wuton_pins[] = {
	WUTON_PIN(0),
	WUTON_PIN(1),
	WUTON_PIN(2),
	WUTON_PIN(3),
	WUTON_PIN(4),
	WUTON_PIN(5),
	WUTON_PIN(6),
	WUTON_PIN(7),
	WUTON_PIN(8),
	WUTON_PIN(9),
	WUTON_PIN(10),
	WUTON_PIN(11),
	WUTON_PIN(12),
	WUTON_PIN(13),
	WUTON_PIN(14),
	WUTON_PIN(15),
	WUTON_PIN(16),
	WUTON_PIN(17),
	WUTON_PIN(18),
	WUTON_PIN(19),
	WUTON_PIN(20),
	WUTON_PIN(21),
	WUTON_PIN(22),
	WUTON_PIN(23),
	WUTON_PIN(24),
	WUTON_PIN(25),
	WUTON_PIN(26),
	WUTON_PIN(27),
	WUTON_PIN(28),
	WUTON_PIN(29),
	WUTON_PIN(30),
	WUTON_PIN(31),
};

#define SEWVAW_P(p, f0, f1, f2)						\
static stwuct ocewot_pin_caps sewvaw_pin_##p = {			\
	.pin = p,							\
	.functions = {							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
	},								\
}

SEWVAW_P(0,  SG0,       NONE,      NONE);
SEWVAW_P(1,  SG0,       NONE,      NONE);
SEWVAW_P(2,  SG0,       NONE,      NONE);
SEWVAW_P(3,  SG0,       NONE,      NONE);
SEWVAW_P(4,  TACHO,     NONE,      NONE);
SEWVAW_P(5,  PWM,       NONE,      NONE);
SEWVAW_P(6,  TWI,       NONE,      NONE);
SEWVAW_P(7,  TWI,       NONE,      NONE);
SEWVAW_P(8,  SI,        NONE,      NONE);
SEWVAW_P(9,  SI,        MD,        NONE);
SEWVAW_P(10, SI,        MD,        NONE);
SEWVAW_P(11, SFP,       MD,        TWI_SCW_M);
SEWVAW_P(12, SFP,       MD,        TWI_SCW_M);
SEWVAW_P(13, SFP,       UAWT2,     TWI_SCW_M);
SEWVAW_P(14, SFP,       UAWT2,     TWI_SCW_M);
SEWVAW_P(15, SFP,       PTP0,      TWI_SCW_M);
SEWVAW_P(16, SFP,       PTP0,      TWI_SCW_M);
SEWVAW_P(17, SFP,       PCI_WAKE,  TWI_SCW_M);
SEWVAW_P(18, SFP,       NONE,      TWI_SCW_M);
SEWVAW_P(19, SFP,       NONE,      TWI_SCW_M);
SEWVAW_P(20, SFP,       NONE,      TWI_SCW_M);
SEWVAW_P(21, SFP,       NONE,      TWI_SCW_M);
SEWVAW_P(22, NONE,      NONE,      NONE);
SEWVAW_P(23, NONE,      NONE,      NONE);
SEWVAW_P(24, NONE,      NONE,      NONE);
SEWVAW_P(25, NONE,      NONE,      NONE);
SEWVAW_P(26, UAWT,      NONE,      NONE);
SEWVAW_P(27, UAWT,      NONE,      NONE);
SEWVAW_P(28, IWQ0,      NONE,      NONE);
SEWVAW_P(29, IWQ1,      NONE,      NONE);
SEWVAW_P(30, PTP0,      NONE,      NONE);
SEWVAW_P(31, PTP0,      NONE,      NONE);

#define SEWVAW_PIN(n) {						\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &sewvaw_pin_##n				\
}

static const stwuct pinctww_pin_desc sewvaw_pins[] = {
	SEWVAW_PIN(0),
	SEWVAW_PIN(1),
	SEWVAW_PIN(2),
	SEWVAW_PIN(3),
	SEWVAW_PIN(4),
	SEWVAW_PIN(5),
	SEWVAW_PIN(6),
	SEWVAW_PIN(7),
	SEWVAW_PIN(8),
	SEWVAW_PIN(9),
	SEWVAW_PIN(10),
	SEWVAW_PIN(11),
	SEWVAW_PIN(12),
	SEWVAW_PIN(13),
	SEWVAW_PIN(14),
	SEWVAW_PIN(15),
	SEWVAW_PIN(16),
	SEWVAW_PIN(17),
	SEWVAW_PIN(18),
	SEWVAW_PIN(19),
	SEWVAW_PIN(20),
	SEWVAW_PIN(21),
	SEWVAW_PIN(22),
	SEWVAW_PIN(23),
	SEWVAW_PIN(24),
	SEWVAW_PIN(25),
	SEWVAW_PIN(26),
	SEWVAW_PIN(27),
	SEWVAW_PIN(28),
	SEWVAW_PIN(29),
	SEWVAW_PIN(30),
	SEWVAW_PIN(31),
};

#define OCEWOT_P(p, f0, f1, f2)						\
static stwuct ocewot_pin_caps ocewot_pin_##p = {			\
	.pin = p,							\
	.functions = {							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
	},								\
}

OCEWOT_P(0,  SG0,       NONE,      NONE);
OCEWOT_P(1,  SG0,       NONE,      NONE);
OCEWOT_P(2,  SG0,       NONE,      NONE);
OCEWOT_P(3,  SG0,       NONE,      NONE);
OCEWOT_P(4,  IWQ0_IN,   IWQ0_OUT,  TWI_SCW_M);
OCEWOT_P(5,  IWQ1_IN,   IWQ1_OUT,  PCI_WAKE);
OCEWOT_P(6,  UAWT,      TWI_SCW_M, NONE);
OCEWOT_P(7,  UAWT,      TWI_SCW_M, NONE);
OCEWOT_P(8,  SI,        TWI_SCW_M, IWQ0_OUT);
OCEWOT_P(9,  SI,        TWI_SCW_M, IWQ1_OUT);
OCEWOT_P(10, PTP2,      TWI_SCW_M, SFP);
OCEWOT_P(11, PTP3,      TWI_SCW_M, SFP);
OCEWOT_P(12, UAWT2,     TWI_SCW_M, SFP);
OCEWOT_P(13, UAWT2,     TWI_SCW_M, SFP);
OCEWOT_P(14, MIIM,      TWI_SCW_M, SFP);
OCEWOT_P(15, MIIM,      TWI_SCW_M, SFP);
OCEWOT_P(16, TWI,       NONE,      SI);
OCEWOT_P(17, TWI,       TWI_SCW_M, SI);
OCEWOT_P(18, PTP0,      TWI_SCW_M, NONE);
OCEWOT_P(19, PTP1,      TWI_SCW_M, NONE);
OCEWOT_P(20, WECO_CWK,  TACHO,     TWI_SCW_M);
OCEWOT_P(21, WECO_CWK,  PWM,       TWI_SCW_M);

#define OCEWOT_PIN(n) {						\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &ocewot_pin_##n				\
}

static const stwuct pinctww_pin_desc ocewot_pins[] = {
	OCEWOT_PIN(0),
	OCEWOT_PIN(1),
	OCEWOT_PIN(2),
	OCEWOT_PIN(3),
	OCEWOT_PIN(4),
	OCEWOT_PIN(5),
	OCEWOT_PIN(6),
	OCEWOT_PIN(7),
	OCEWOT_PIN(8),
	OCEWOT_PIN(9),
	OCEWOT_PIN(10),
	OCEWOT_PIN(11),
	OCEWOT_PIN(12),
	OCEWOT_PIN(13),
	OCEWOT_PIN(14),
	OCEWOT_PIN(15),
	OCEWOT_PIN(16),
	OCEWOT_PIN(17),
	OCEWOT_PIN(18),
	OCEWOT_PIN(19),
	OCEWOT_PIN(20),
	OCEWOT_PIN(21),
};

#define JAGUAW2_P(p, f0, f1)						\
static stwuct ocewot_pin_caps jaguaw2_pin_##p = {			\
	.pin = p,							\
	.functions = {							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_NONE	\
	},								\
}

JAGUAW2_P(0,  SG0,       NONE);
JAGUAW2_P(1,  SG0,       NONE);
JAGUAW2_P(2,  SG0,       NONE);
JAGUAW2_P(3,  SG0,       NONE);
JAGUAW2_P(4,  SG1,       NONE);
JAGUAW2_P(5,  SG1,       NONE);
JAGUAW2_P(6,  IWQ0_IN,   IWQ0_OUT);
JAGUAW2_P(7,  IWQ1_IN,   IWQ1_OUT);
JAGUAW2_P(8,  PTP0,      NONE);
JAGUAW2_P(9,  PTP1,      NONE);
JAGUAW2_P(10, UAWT,      NONE);
JAGUAW2_P(11, UAWT,      NONE);
JAGUAW2_P(12, SG1,       NONE);
JAGUAW2_P(13, SG1,       NONE);
JAGUAW2_P(14, TWI,       TWI_SCW_M);
JAGUAW2_P(15, TWI,       NONE);
JAGUAW2_P(16, SI,        TWI_SCW_M);
JAGUAW2_P(17, SI,        TWI_SCW_M);
JAGUAW2_P(18, SI,        TWI_SCW_M);
JAGUAW2_P(19, PCI_WAKE,  NONE);
JAGUAW2_P(20, IWQ0_OUT,  TWI_SCW_M);
JAGUAW2_P(21, IWQ1_OUT,  TWI_SCW_M);
JAGUAW2_P(22, TACHO,     NONE);
JAGUAW2_P(23, PWM,       NONE);
JAGUAW2_P(24, UAWT2,     NONE);
JAGUAW2_P(25, UAWT2,     SI);
JAGUAW2_P(26, PTP2,      SI);
JAGUAW2_P(27, PTP3,      SI);
JAGUAW2_P(28, TWI2,      SI);
JAGUAW2_P(29, TWI2,      SI);
JAGUAW2_P(30, SG2,       SI);
JAGUAW2_P(31, SG2,       SI);
JAGUAW2_P(32, SG2,       SI);
JAGUAW2_P(33, SG2,       SI);
JAGUAW2_P(34, NONE,      TWI_SCW_M);
JAGUAW2_P(35, NONE,      TWI_SCW_M);
JAGUAW2_P(36, NONE,      TWI_SCW_M);
JAGUAW2_P(37, NONE,      TWI_SCW_M);
JAGUAW2_P(38, NONE,      TWI_SCW_M);
JAGUAW2_P(39, NONE,      TWI_SCW_M);
JAGUAW2_P(40, NONE,      TWI_SCW_M);
JAGUAW2_P(41, NONE,      TWI_SCW_M);
JAGUAW2_P(42, NONE,      TWI_SCW_M);
JAGUAW2_P(43, NONE,      TWI_SCW_M);
JAGUAW2_P(44, NONE,      SFP);
JAGUAW2_P(45, NONE,      SFP);
JAGUAW2_P(46, NONE,      SFP);
JAGUAW2_P(47, NONE,      SFP);
JAGUAW2_P(48, SFP,       NONE);
JAGUAW2_P(49, SFP,       SI);
JAGUAW2_P(50, SFP,       SI);
JAGUAW2_P(51, SFP,       SI);
JAGUAW2_P(52, SFP,       NONE);
JAGUAW2_P(53, SFP,       NONE);
JAGUAW2_P(54, SFP,       NONE);
JAGUAW2_P(55, SFP,       NONE);
JAGUAW2_P(56, MIIM,      SFP);
JAGUAW2_P(57, MIIM,      SFP);
JAGUAW2_P(58, MIIM,      SFP);
JAGUAW2_P(59, MIIM,      SFP);
JAGUAW2_P(60, NONE,      NONE);
JAGUAW2_P(61, NONE,      NONE);
JAGUAW2_P(62, NONE,      NONE);
JAGUAW2_P(63, NONE,      NONE);

#define JAGUAW2_PIN(n) {					\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &jaguaw2_pin_##n				\
}

static const stwuct pinctww_pin_desc jaguaw2_pins[] = {
	JAGUAW2_PIN(0),
	JAGUAW2_PIN(1),
	JAGUAW2_PIN(2),
	JAGUAW2_PIN(3),
	JAGUAW2_PIN(4),
	JAGUAW2_PIN(5),
	JAGUAW2_PIN(6),
	JAGUAW2_PIN(7),
	JAGUAW2_PIN(8),
	JAGUAW2_PIN(9),
	JAGUAW2_PIN(10),
	JAGUAW2_PIN(11),
	JAGUAW2_PIN(12),
	JAGUAW2_PIN(13),
	JAGUAW2_PIN(14),
	JAGUAW2_PIN(15),
	JAGUAW2_PIN(16),
	JAGUAW2_PIN(17),
	JAGUAW2_PIN(18),
	JAGUAW2_PIN(19),
	JAGUAW2_PIN(20),
	JAGUAW2_PIN(21),
	JAGUAW2_PIN(22),
	JAGUAW2_PIN(23),
	JAGUAW2_PIN(24),
	JAGUAW2_PIN(25),
	JAGUAW2_PIN(26),
	JAGUAW2_PIN(27),
	JAGUAW2_PIN(28),
	JAGUAW2_PIN(29),
	JAGUAW2_PIN(30),
	JAGUAW2_PIN(31),
	JAGUAW2_PIN(32),
	JAGUAW2_PIN(33),
	JAGUAW2_PIN(34),
	JAGUAW2_PIN(35),
	JAGUAW2_PIN(36),
	JAGUAW2_PIN(37),
	JAGUAW2_PIN(38),
	JAGUAW2_PIN(39),
	JAGUAW2_PIN(40),
	JAGUAW2_PIN(41),
	JAGUAW2_PIN(42),
	JAGUAW2_PIN(43),
	JAGUAW2_PIN(44),
	JAGUAW2_PIN(45),
	JAGUAW2_PIN(46),
	JAGUAW2_PIN(47),
	JAGUAW2_PIN(48),
	JAGUAW2_PIN(49),
	JAGUAW2_PIN(50),
	JAGUAW2_PIN(51),
	JAGUAW2_PIN(52),
	JAGUAW2_PIN(53),
	JAGUAW2_PIN(54),
	JAGUAW2_PIN(55),
	JAGUAW2_PIN(56),
	JAGUAW2_PIN(57),
	JAGUAW2_PIN(58),
	JAGUAW2_PIN(59),
	JAGUAW2_PIN(60),
	JAGUAW2_PIN(61),
	JAGUAW2_PIN(62),
	JAGUAW2_PIN(63),
};

#define SEWVAWT_P(p, f0, f1, f2)					\
static stwuct ocewot_pin_caps sewvawt_pin_##p = {			\
	.pin = p,							\
	.functions = {							\
		FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2		\
	},								\
}

SEWVAWT_P(0,  SG0,        NONE,      NONE);
SEWVAWT_P(1,  SG0,        NONE,      NONE);
SEWVAWT_P(2,  SG0,        NONE,      NONE);
SEWVAWT_P(3,  SG0,        NONE,      NONE);
SEWVAWT_P(4,  IWQ0_IN,    IWQ0_OUT,  TWI_SCW_M);
SEWVAWT_P(5,  IWQ1_IN,    IWQ1_OUT,  TWI_SCW_M);
SEWVAWT_P(6,  UAWT,       NONE,      NONE);
SEWVAWT_P(7,  UAWT,       NONE,      NONE);
SEWVAWT_P(8,  SI,         SFP,       TWI_SCW_M);
SEWVAWT_P(9,  PCI_WAKE,   SFP,       SI);
SEWVAWT_P(10, PTP0,       SFP,       TWI_SCW_M);
SEWVAWT_P(11, PTP1,       SFP,       TWI_SCW_M);
SEWVAWT_P(12, WEF_CWK,    SFP,       TWI_SCW_M);
SEWVAWT_P(13, WEF_CWK,    SFP,       TWI_SCW_M);
SEWVAWT_P(14, WEF_CWK,    IWQ0_OUT,  SI);
SEWVAWT_P(15, WEF_CWK,    IWQ1_OUT,  SI);
SEWVAWT_P(16, TACHO,      SFP,       SI);
SEWVAWT_P(17, PWM,        NONE,      TWI_SCW_M);
SEWVAWT_P(18, PTP2,       SFP,       SI);
SEWVAWT_P(19, PTP3,       SFP,       SI);
SEWVAWT_P(20, UAWT2,      SFP,       SI);
SEWVAWT_P(21, UAWT2,      NONE,      NONE);
SEWVAWT_P(22, MIIM,       SFP,       TWI2);
SEWVAWT_P(23, MIIM,       SFP,       TWI2);
SEWVAWT_P(24, TWI,        NONE,      NONE);
SEWVAWT_P(25, TWI,        SFP,       TWI_SCW_M);
SEWVAWT_P(26, TWI_SCW_M,  SFP,       SI);
SEWVAWT_P(27, TWI_SCW_M,  SFP,       SI);
SEWVAWT_P(28, TWI_SCW_M,  SFP,       SI);
SEWVAWT_P(29, TWI_SCW_M,  NONE,      NONE);
SEWVAWT_P(30, TWI_SCW_M,  NONE,      NONE);
SEWVAWT_P(31, TWI_SCW_M,  NONE,      NONE);
SEWVAWT_P(32, TWI_SCW_M,  NONE,      NONE);
SEWVAWT_P(33, WCVWD_CWK,  NONE,      NONE);
SEWVAWT_P(34, WCVWD_CWK,  NONE,      NONE);
SEWVAWT_P(35, WCVWD_CWK,  NONE,      NONE);
SEWVAWT_P(36, WCVWD_CWK,  NONE,      NONE);

#define SEWVAWT_PIN(n) {					\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &sewvawt_pin_##n				\
}

static const stwuct pinctww_pin_desc sewvawt_pins[] = {
	SEWVAWT_PIN(0),
	SEWVAWT_PIN(1),
	SEWVAWT_PIN(2),
	SEWVAWT_PIN(3),
	SEWVAWT_PIN(4),
	SEWVAWT_PIN(5),
	SEWVAWT_PIN(6),
	SEWVAWT_PIN(7),
	SEWVAWT_PIN(8),
	SEWVAWT_PIN(9),
	SEWVAWT_PIN(10),
	SEWVAWT_PIN(11),
	SEWVAWT_PIN(12),
	SEWVAWT_PIN(13),
	SEWVAWT_PIN(14),
	SEWVAWT_PIN(15),
	SEWVAWT_PIN(16),
	SEWVAWT_PIN(17),
	SEWVAWT_PIN(18),
	SEWVAWT_PIN(19),
	SEWVAWT_PIN(20),
	SEWVAWT_PIN(21),
	SEWVAWT_PIN(22),
	SEWVAWT_PIN(23),
	SEWVAWT_PIN(24),
	SEWVAWT_PIN(25),
	SEWVAWT_PIN(26),
	SEWVAWT_PIN(27),
	SEWVAWT_PIN(28),
	SEWVAWT_PIN(29),
	SEWVAWT_PIN(30),
	SEWVAWT_PIN(31),
	SEWVAWT_PIN(32),
	SEWVAWT_PIN(33),
	SEWVAWT_PIN(34),
	SEWVAWT_PIN(35),
	SEWVAWT_PIN(36),
};

#define SPAWX5_P(p, f0, f1, f2)					\
static stwuct ocewot_pin_caps spawx5_pin_##p = {			\
	.pin = p,							\
	.functions = {							\
		FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2		\
	},								\
}

SPAWX5_P(0,  SG0,       PWW_STAT,  NONE);
SPAWX5_P(1,  SG0,       NONE,      NONE);
SPAWX5_P(2,  SG0,       NONE,      NONE);
SPAWX5_P(3,  SG0,       NONE,      NONE);
SPAWX5_P(4,  SG1,       NONE,      NONE);
SPAWX5_P(5,  SG1,       NONE,      NONE);
SPAWX5_P(6,  IWQ0_IN,   IWQ0_OUT,  SFP);
SPAWX5_P(7,  IWQ1_IN,   IWQ1_OUT,  SFP);
SPAWX5_P(8,  PTP0,      NONE,      SFP);
SPAWX5_P(9,  PTP1,      SFP,       TWI_SCW_M);
SPAWX5_P(10, UAWT,      NONE,      NONE);
SPAWX5_P(11, UAWT,      NONE,      NONE);
SPAWX5_P(12, SG1,       NONE,      NONE);
SPAWX5_P(13, SG1,       NONE,      NONE);
SPAWX5_P(14, TWI,       TWI_SCW_M, NONE);
SPAWX5_P(15, TWI,       NONE,      NONE);
SPAWX5_P(16, SI,        TWI_SCW_M, SFP);
SPAWX5_P(17, SI,        TWI_SCW_M, SFP);
SPAWX5_P(18, SI,        TWI_SCW_M, SFP);
SPAWX5_P(19, PCI_WAKE,  TWI_SCW_M, SFP);
SPAWX5_P(20, IWQ0_OUT,  TWI_SCW_M, SFP);
SPAWX5_P(21, IWQ1_OUT,  TACHO,     SFP);
SPAWX5_P(22, TACHO,     IWQ0_OUT,  TWI_SCW_M);
SPAWX5_P(23, PWM,       UAWT3,     TWI_SCW_M);
SPAWX5_P(24, PTP2,      UAWT3,     TWI_SCW_M);
SPAWX5_P(25, PTP3,      SI,        TWI_SCW_M);
SPAWX5_P(26, UAWT2,     SI,        TWI_SCW_M);
SPAWX5_P(27, UAWT2,     SI,        TWI_SCW_M);
SPAWX5_P(28, TWI2,      SI,        SFP);
SPAWX5_P(29, TWI2,      SI,        SFP);
SPAWX5_P(30, SG2,       SI,        PWM);
SPAWX5_P(31, SG2,       SI,        TWI_SCW_M);
SPAWX5_P(32, SG2,       SI,        TWI_SCW_M);
SPAWX5_P(33, SG2,       SI,        SFP);
SPAWX5_P(34, NONE,      TWI_SCW_M, EMMC);
SPAWX5_P(35, SFP,       TWI_SCW_M, EMMC);
SPAWX5_P(36, SFP,       TWI_SCW_M, EMMC);
SPAWX5_P(37, SFP,       NONE,      EMMC);
SPAWX5_P(38, NONE,      TWI_SCW_M, EMMC);
SPAWX5_P(39, SI2,       TWI_SCW_M, EMMC);
SPAWX5_P(40, SI2,       TWI_SCW_M, EMMC);
SPAWX5_P(41, SI2,       TWI_SCW_M, EMMC);
SPAWX5_P(42, SI2,       TWI_SCW_M, EMMC);
SPAWX5_P(43, SI2,       TWI_SCW_M, EMMC);
SPAWX5_P(44, SI,        SFP,       EMMC);
SPAWX5_P(45, SI,        SFP,       EMMC);
SPAWX5_P(46, NONE,      SFP,       EMMC);
SPAWX5_P(47, NONE,      SFP,       EMMC);
SPAWX5_P(48, TWI3,      SI,        SFP);
SPAWX5_P(49, TWI3,      NONE,      SFP);
SPAWX5_P(50, SFP,       NONE,      TWI_SCW_M);
SPAWX5_P(51, SFP,       SI,        TWI_SCW_M);
SPAWX5_P(52, SFP,       MIIM,      TWI_SCW_M);
SPAWX5_P(53, SFP,       MIIM,      TWI_SCW_M);
SPAWX5_P(54, SFP,       PTP2,      TWI_SCW_M);
SPAWX5_P(55, SFP,       PTP3,      PCI_WAKE);
SPAWX5_P(56, MIIM,      SFP,       TWI_SCW_M);
SPAWX5_P(57, MIIM,      SFP,       TWI_SCW_M);
SPAWX5_P(58, MIIM,      SFP,       TWI_SCW_M);
SPAWX5_P(59, MIIM,      SFP,       NONE);
SPAWX5_P(60, WECO_CWK,  NONE,      NONE);
SPAWX5_P(61, WECO_CWK,  NONE,      NONE);
SPAWX5_P(62, WECO_CWK,  PWW_STAT,  NONE);
SPAWX5_P(63, WECO_CWK,  NONE,      NONE);

#define SPAWX5_PIN(n) {					\
	.numbew = n,						\
	.name = "GPIO_"#n,					\
	.dwv_data = &spawx5_pin_##n				\
}

static const stwuct pinctww_pin_desc spawx5_pins[] = {
	SPAWX5_PIN(0),
	SPAWX5_PIN(1),
	SPAWX5_PIN(2),
	SPAWX5_PIN(3),
	SPAWX5_PIN(4),
	SPAWX5_PIN(5),
	SPAWX5_PIN(6),
	SPAWX5_PIN(7),
	SPAWX5_PIN(8),
	SPAWX5_PIN(9),
	SPAWX5_PIN(10),
	SPAWX5_PIN(11),
	SPAWX5_PIN(12),
	SPAWX5_PIN(13),
	SPAWX5_PIN(14),
	SPAWX5_PIN(15),
	SPAWX5_PIN(16),
	SPAWX5_PIN(17),
	SPAWX5_PIN(18),
	SPAWX5_PIN(19),
	SPAWX5_PIN(20),
	SPAWX5_PIN(21),
	SPAWX5_PIN(22),
	SPAWX5_PIN(23),
	SPAWX5_PIN(24),
	SPAWX5_PIN(25),
	SPAWX5_PIN(26),
	SPAWX5_PIN(27),
	SPAWX5_PIN(28),
	SPAWX5_PIN(29),
	SPAWX5_PIN(30),
	SPAWX5_PIN(31),
	SPAWX5_PIN(32),
	SPAWX5_PIN(33),
	SPAWX5_PIN(34),
	SPAWX5_PIN(35),
	SPAWX5_PIN(36),
	SPAWX5_PIN(37),
	SPAWX5_PIN(38),
	SPAWX5_PIN(39),
	SPAWX5_PIN(40),
	SPAWX5_PIN(41),
	SPAWX5_PIN(42),
	SPAWX5_PIN(43),
	SPAWX5_PIN(44),
	SPAWX5_PIN(45),
	SPAWX5_PIN(46),
	SPAWX5_PIN(47),
	SPAWX5_PIN(48),
	SPAWX5_PIN(49),
	SPAWX5_PIN(50),
	SPAWX5_PIN(51),
	SPAWX5_PIN(52),
	SPAWX5_PIN(53),
	SPAWX5_PIN(54),
	SPAWX5_PIN(55),
	SPAWX5_PIN(56),
	SPAWX5_PIN(57),
	SPAWX5_PIN(58),
	SPAWX5_PIN(59),
	SPAWX5_PIN(60),
	SPAWX5_PIN(61),
	SPAWX5_PIN(62),
	SPAWX5_PIN(63),
};

#define WAN966X_P(p, f0, f1, f2, f3, f4, f5, f6, f7)           \
static stwuct ocewot_pin_caps wan966x_pin_##p = {              \
	.pin = p,                                              \
	.functions = {                                         \
		FUNC_##f0, FUNC_##f1, FUNC_##f2,               \
		FUNC_##f3                                      \
	},                                                     \
	.a_functions = {                                       \
		FUNC_##f4, FUNC_##f5, FUNC_##f6,               \
		FUNC_##f7                                      \
	},                                                     \
}

/* Pinmuxing tabwe taken fwom data sheet */
/*        Pin   FUNC0    FUNC1     FUNC2      FUNC3     FUNC4     FUNC5      FUNC6    FUNC7 */
WAN966X_P(0,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(1,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(2,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(3,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(4,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(5,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(6,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(7,    GPIO,    NONE,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(8,    GPIO,   FC0_a,  USB_H_b,      NONE,  USB_S_b,     NONE,      NONE,        W);
WAN966X_P(9,    GPIO,   FC0_a,  USB_H_b,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(10,   GPIO,   FC0_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(11,   GPIO,   FC1_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(12,   GPIO,   FC1_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(13,   GPIO,   FC1_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(14,   GPIO,   FC2_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(15,   GPIO,   FC2_a,     NONE,      NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(16,   GPIO,   FC2_a, IB_TWG_a,      NONE, OB_TWG_a, IWQ_IN_c, IWQ_OUT_c,        W);
WAN966X_P(17,   GPIO,   FC3_a, IB_TWG_a,      NONE, OB_TWG_a, IWQ_IN_c, IWQ_OUT_c,        W);
WAN966X_P(18,   GPIO,   FC3_a, IB_TWG_a,      NONE, OB_TWG_a, IWQ_IN_c, IWQ_OUT_c,        W);
WAN966X_P(19,   GPIO,   FC3_a, IB_TWG_a,      NONE, OB_TWG_a, IWQ_IN_c, IWQ_OUT_c,        W);
WAN966X_P(20,   GPIO,   FC4_a, IB_TWG_a,      NONE, OB_TWG_a, IWQ_IN_c,      NONE,        W);
WAN966X_P(21,   GPIO,   FC4_a,     NONE,      NONE, OB_TWG_a,     NONE,      NONE,        W);
WAN966X_P(22,   GPIO,   FC4_a,     NONE,      NONE, OB_TWG_a,     NONE,      NONE,        W);
WAN966X_P(23,   GPIO,    NONE,     NONE,      NONE, OB_TWG_a,     NONE,      NONE,        W);
WAN966X_P(24,   GPIO,   FC0_b, IB_TWG_a,   USB_H_c, OB_TWG_a, IWQ_IN_c,   TACHO_a,        W);
WAN966X_P(25,   GPIO,   FC0_b, IB_TWG_a,   USB_H_c, OB_TWG_a, IWQ_OUT_c,   SFP_SD,        W);
WAN966X_P(26,   GPIO,   FC0_b, IB_TWG_a,   USB_S_c, OB_TWG_a,   CAN0_a,    SFP_SD,        W);
WAN966X_P(27,   GPIO,    NONE,     NONE,      NONE, OB_TWG_a,   CAN0_a,     PWM_a,        W);
WAN966X_P(28,   GPIO,  MIIM_a,     NONE,      NONE, OB_TWG_a, IWQ_OUT_c,   SFP_SD,        W);
WAN966X_P(29,   GPIO,  MIIM_a,     NONE,      NONE, OB_TWG_a,     NONE,      NONE,        W);
WAN966X_P(30,   GPIO,   FC3_c,     CAN1,    CWKMON,   OB_TWG,   WECO_b,      NONE,        W);
WAN966X_P(31,   GPIO,   FC3_c,     CAN1,    CWKMON,   OB_TWG,   WECO_b,      NONE,        W);
WAN966X_P(32,   GPIO,   FC3_c,     NONE,   SGPIO_a,     NONE,  MIIM_Sa,      NONE,        W);
WAN966X_P(33,   GPIO,   FC1_b,     NONE,   SGPIO_a,     NONE,  MIIM_Sa,    MIIM_b,        W);
WAN966X_P(34,   GPIO,   FC1_b,     NONE,   SGPIO_a,     NONE,  MIIM_Sa,    MIIM_b,        W);
WAN966X_P(35,   GPIO,   FC1_b,  PTPSYNC_0, SGPIO_a,   CAN0_b,     NONE,      NONE,        W);
WAN966X_P(36,   GPIO,    NONE,  PTPSYNC_1,    NONE,   CAN0_b,     NONE,      NONE,        W);
WAN966X_P(37,   GPIO, FC_SHWD0, PTPSYNC_2, TWI_SWC_GATE_AD, NONE, NONE,      NONE,        W);
WAN966X_P(38,   GPIO,    NONE,  PTPSYNC_3,    NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(39,   GPIO,    NONE,  PTPSYNC_4,    NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(40,   GPIO, FC_SHWD1, PTPSYNC_5,    NONE,     NONE,     NONE,      NONE,        W);
WAN966X_P(41,   GPIO, FC_SHWD2, PTPSYNC_6, TWI_SWC_GATE_AD, NONE, NONE,      NONE,        W);
WAN966X_P(42,   GPIO, FC_SHWD3, PTPSYNC_7, TWI_SWC_GATE_AD, NONE, NONE,      NONE,        W);
WAN966X_P(43,   GPIO,   FC2_b,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a,  WECO_a,  IWQ_IN_a,       W);
WAN966X_P(44,   GPIO,   FC2_b,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a,  WECO_a,  IWQ_IN_a,       W);
WAN966X_P(45,   GPIO,   FC2_b,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a,    NONE,  IWQ_IN_a,       W);
WAN966X_P(46,   GPIO,   FC1_c,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a, FC_SHWD4, IWQ_IN_a,       W);
WAN966X_P(47,   GPIO,   FC1_c,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a, FC_SHWD5, IWQ_IN_a,       W);
WAN966X_P(48,   GPIO,   FC1_c,   OB_TWG_b, IB_TWG_b, IWQ_OUT_a, FC_SHWD6, IWQ_IN_a,       W);
WAN966X_P(49,   GPIO, FC_SHWD7,  OB_TWG_b, IB_TWG_b, IWQ_OUT_a, TWI_SWC_GATE, IWQ_IN_a,   W);
WAN966X_P(50,   GPIO, FC_SHWD16, OB_TWG_b, IB_TWG_b, IWQ_OUT_a, TWI_SWC_GATE, NONE,       W);
WAN966X_P(51,   GPIO,   FC3_b,   OB_TWG_b, IB_TWG_c, IWQ_OUT_b,   PWM_b,  IWQ_IN_b,       W);
WAN966X_P(52,   GPIO,   FC3_b,   OB_TWG_b, IB_TWG_c, IWQ_OUT_b, TACHO_b,  IWQ_IN_b,       W);
WAN966X_P(53,   GPIO,   FC3_b,   OB_TWG_b, IB_TWG_c, IWQ_OUT_b,    NONE,  IWQ_IN_b,       W);
WAN966X_P(54,   GPIO, FC_SHWD8,  OB_TWG_b, IB_TWG_c, IWQ_OUT_b, TWI_SWC_GATE, IWQ_IN_b,   W);
WAN966X_P(55,   GPIO, FC_SHWD9,  OB_TWG_b, IB_TWG_c, IWQ_OUT_b, TWI_SWC_GATE, IWQ_IN_b,   W);
WAN966X_P(56,   GPIO,   FC4_b,   OB_TWG_b, IB_TWG_c, IWQ_OUT_b, FC_SHWD10,    IWQ_IN_b,   W);
WAN966X_P(57,   GPIO,   FC4_b, TWI_SWC_GATE, IB_TWG_c, IWQ_OUT_b, FC_SHWD11, IWQ_IN_b,    W);
WAN966X_P(58,   GPIO,   FC4_b, TWI_SWC_GATE, IB_TWG_c, IWQ_OUT_b, FC_SHWD12, IWQ_IN_b,    W);
WAN966X_P(59,   GPIO,   QSPI1,   MIIM_c,      NONE,     NONE,  MIIM_Sb,      NONE,        W);
WAN966X_P(60,   GPIO,   QSPI1,   MIIM_c,      NONE,     NONE,  MIIM_Sb,      NONE,        W);
WAN966X_P(61,   GPIO,   QSPI1,     NONE,   SGPIO_b,    FC0_c,  MIIM_Sb,      NONE,        W);
WAN966X_P(62,   GPIO,   QSPI1, FC_SHWD13,  SGPIO_b,    FC0_c, TWI_SWC_GATE,  SFP_SD,      W);
WAN966X_P(63,   GPIO,   QSPI1, FC_SHWD14,  SGPIO_b,    FC0_c, TWI_SWC_GATE,  SFP_SD,      W);
WAN966X_P(64,   GPIO,   QSPI1,    FC4_c,   SGPIO_b, FC_SHWD15, TWI_SWC_GATE, SFP_SD,      W);
WAN966X_P(65,   GPIO, USB_H_a,    FC4_c,      NONE, IWQ_OUT_c, TWI_SWC_GATE_AD, NONE,     W);
WAN966X_P(66,   GPIO, USB_H_a,    FC4_c,   USB_S_a, IWQ_OUT_c, IWQ_IN_c,     NONE,        W);
WAN966X_P(67,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(68,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(69,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(70,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(71,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(72,   GPIO, EMMC_SD,     NONE,     QSPI2,     NONE,     NONE,      NONE,        W);
WAN966X_P(73,   GPIO,    EMMC,     NONE,      NONE,       SD,     NONE,      NONE,        W);
WAN966X_P(74,   GPIO,    EMMC,     NONE, FC_SHWD17,       SD, TWI_SWC_GATE,  NONE,        W);
WAN966X_P(75,   GPIO,    EMMC,     NONE, FC_SHWD18,       SD, TWI_SWC_GATE,  NONE,        W);
WAN966X_P(76,   GPIO,    EMMC,     NONE, FC_SHWD19,       SD, TWI_SWC_GATE,  NONE,        W);
WAN966X_P(77,   GPIO, EMMC_SD,     NONE, FC_SHWD20,     NONE, TWI_SWC_GATE,  NONE,        W);

#define WAN966X_PIN(n) {                                       \
	.numbew = n,                                           \
	.name = "GPIO_"#n,                                     \
	.dwv_data = &wan966x_pin_##n                           \
}

static const stwuct pinctww_pin_desc wan966x_pins[] = {
	WAN966X_PIN(0),
	WAN966X_PIN(1),
	WAN966X_PIN(2),
	WAN966X_PIN(3),
	WAN966X_PIN(4),
	WAN966X_PIN(5),
	WAN966X_PIN(6),
	WAN966X_PIN(7),
	WAN966X_PIN(8),
	WAN966X_PIN(9),
	WAN966X_PIN(10),
	WAN966X_PIN(11),
	WAN966X_PIN(12),
	WAN966X_PIN(13),
	WAN966X_PIN(14),
	WAN966X_PIN(15),
	WAN966X_PIN(16),
	WAN966X_PIN(17),
	WAN966X_PIN(18),
	WAN966X_PIN(19),
	WAN966X_PIN(20),
	WAN966X_PIN(21),
	WAN966X_PIN(22),
	WAN966X_PIN(23),
	WAN966X_PIN(24),
	WAN966X_PIN(25),
	WAN966X_PIN(26),
	WAN966X_PIN(27),
	WAN966X_PIN(28),
	WAN966X_PIN(29),
	WAN966X_PIN(30),
	WAN966X_PIN(31),
	WAN966X_PIN(32),
	WAN966X_PIN(33),
	WAN966X_PIN(34),
	WAN966X_PIN(35),
	WAN966X_PIN(36),
	WAN966X_PIN(37),
	WAN966X_PIN(38),
	WAN966X_PIN(39),
	WAN966X_PIN(40),
	WAN966X_PIN(41),
	WAN966X_PIN(42),
	WAN966X_PIN(43),
	WAN966X_PIN(44),
	WAN966X_PIN(45),
	WAN966X_PIN(46),
	WAN966X_PIN(47),
	WAN966X_PIN(48),
	WAN966X_PIN(49),
	WAN966X_PIN(50),
	WAN966X_PIN(51),
	WAN966X_PIN(52),
	WAN966X_PIN(53),
	WAN966X_PIN(54),
	WAN966X_PIN(55),
	WAN966X_PIN(56),
	WAN966X_PIN(57),
	WAN966X_PIN(58),
	WAN966X_PIN(59),
	WAN966X_PIN(60),
	WAN966X_PIN(61),
	WAN966X_PIN(62),
	WAN966X_PIN(63),
	WAN966X_PIN(64),
	WAN966X_PIN(65),
	WAN966X_PIN(66),
	WAN966X_PIN(67),
	WAN966X_PIN(68),
	WAN966X_PIN(69),
	WAN966X_PIN(70),
	WAN966X_PIN(71),
	WAN966X_PIN(72),
	WAN966X_PIN(73),
	WAN966X_PIN(74),
	WAN966X_PIN(75),
	WAN966X_PIN(76),
	WAN966X_PIN(77),
};

static int ocewot_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(ocewot_function_names);
}

static const chaw *ocewot_get_function_name(stwuct pinctww_dev *pctwdev,
					    unsigned int function)
{
	wetuwn ocewot_function_names[function];
}

static int ocewot_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned int function,
				      const chaw *const **gwoups,
				      unsigned *const num_gwoups)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups  = info->func[function].gwoups;
	*num_gwoups = info->func[function].ngwoups;

	wetuwn 0;
}

static int ocewot_pin_function_idx(stwuct ocewot_pinctww *info,
				   unsigned int pin, unsigned int function)
{
	stwuct ocewot_pin_caps *p = info->desc->pins[pin].dwv_data;
	int i;

	fow (i = 0; i < OCEWOT_FUNC_PEW_PIN; i++) {
		if (function == p->functions[i])
			wetuwn i;

		if (function == p->a_functions[i])
			wetuwn i + OCEWOT_FUNC_PEW_PIN;
	}

	wetuwn -1;
}

#define WEG_AWT(msb, info, p) (OCEWOT_GPIO_AWT0 * (info)->stwide + 4 * ((msb) + ((info)->stwide * ((p) / 32))))

static int ocewot_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow, unsigned int gwoup)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct ocewot_pin_caps *pin = info->desc->pins[gwoup].dwv_data;
	unsigned int p = pin->pin % 32;
	int f;

	f = ocewot_pin_function_idx(info, gwoup, sewectow);
	if (f < 0)
		wetuwn -EINVAW;

	/*
	 * f is encoded on two bits.
	 * bit 0 of f goes in BIT(pin) of AWT[0], bit 1 of f goes in BIT(pin) of
	 * AWT[1]
	 * This is wacy because both wegistews can't be updated at the same time
	 * but it doesn't mattew much fow now.
	 * Note: AWT0/AWT1 awe owganized speciawwy fow 64 gpio tawgets
	 */
	wegmap_update_bits(info->map, WEG_AWT(0, info, pin->pin),
			   BIT(p), f << p);
	wegmap_update_bits(info->map, WEG_AWT(1, info, pin->pin),
			   BIT(p), (f >> 1) << p);

	wetuwn 0;
}

static int wan966x_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow, unsigned int gwoup)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct ocewot_pin_caps *pin = info->desc->pins[gwoup].dwv_data;
	unsigned int p = pin->pin % 32;
	int f;

	f = ocewot_pin_function_idx(info, gwoup, sewectow);
	if (f < 0)
		wetuwn -EINVAW;

	/*
	 * f is encoded on thwee bits.
	 * bit 0 of f goes in BIT(pin) of AWT[0], bit 1 of f goes in BIT(pin) of
	 * AWT[1], bit 2 of f goes in BIT(pin) of AWT[2]
	 * This is wacy because thwee wegistews can't be updated at the same time
	 * but it doesn't mattew much fow now.
	 * Note: AWT0/AWT1/AWT2 awe owganized speciawwy fow 78 gpio tawgets
	 */
	wegmap_update_bits(info->map, WEG_AWT(0, info, pin->pin),
			   BIT(p), f << p);
	wegmap_update_bits(info->map, WEG_AWT(1, info, pin->pin),
			   BIT(p), (f >> 1) << p);
	wegmap_update_bits(info->map, WEG_AWT(2, info, pin->pin),
			   BIT(p), (f >> 2) << p);

	wetuwn 0;
}

#define WEG(w, info, p) ((w) * (info)->stwide + (4 * ((p) / 32)))

static int ocewot_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned int pin, boow input)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int p = pin % 32;

	wegmap_update_bits(info->map, WEG(OCEWOT_GPIO_OE, info, pin), BIT(p),
			   input ? 0 : BIT(p));

	wetuwn 0;
}

static int ocewot_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int offset)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int p = offset % 32;

	wegmap_update_bits(info->map, WEG_AWT(0, info, offset),
			   BIT(p), 0);
	wegmap_update_bits(info->map, WEG_AWT(1, info, offset),
			   BIT(p), 0);

	wetuwn 0;
}

static int wan966x_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned int offset)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int p = offset % 32;

	wegmap_update_bits(info->map, WEG_AWT(0, info, offset),
			   BIT(p), 0);
	wegmap_update_bits(info->map, WEG_AWT(1, info, offset),
			   BIT(p), 0);
	wegmap_update_bits(info->map, WEG_AWT(2, info, offset),
			   BIT(p), 0);

	wetuwn 0;
}

static const stwuct pinmux_ops ocewot_pmx_ops = {
	.get_functions_count = ocewot_get_functions_count,
	.get_function_name = ocewot_get_function_name,
	.get_function_gwoups = ocewot_get_function_gwoups,
	.set_mux = ocewot_pinmux_set_mux,
	.gpio_set_diwection = ocewot_gpio_set_diwection,
	.gpio_wequest_enabwe = ocewot_gpio_wequest_enabwe,
};

static const stwuct pinmux_ops wan966x_pmx_ops = {
	.get_functions_count = ocewot_get_functions_count,
	.get_function_name = ocewot_get_function_name,
	.get_function_gwoups = ocewot_get_function_gwoups,
	.set_mux = wan966x_pinmux_set_mux,
	.gpio_set_diwection = ocewot_gpio_set_diwection,
	.gpio_wequest_enabwe = wan966x_gpio_wequest_enabwe,
};

static int ocewot_pctw_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->desc->npins;
}

static const chaw *ocewot_pctw_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned int gwoup)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->desc->pins[gwoup].name;
}

static int ocewot_pctw_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned int gwoup,
				      const unsigned int **pins,
				      unsigned int *num_pins)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	*pins = &info->desc->pins[gwoup].numbew;
	*num_pins = 1;

	wetuwn 0;
}

static int ocewot_hw_get_vawue(stwuct ocewot_pinctww *info,
			       unsigned int pin,
			       unsigned int weg,
			       int *vaw)
{
	int wet = -EOPNOTSUPP;

	if (info->pincfg) {
		const stwuct ocewot_pincfg_data *opd = info->pincfg_data;
		u32 wegcfg;

		wet = wegmap_wead(info->pincfg,
				  pin * wegmap_get_weg_stwide(info->pincfg),
				  &wegcfg);
		if (wet)
			wetuwn wet;

		wet = 0;
		switch (weg) {
		case PINCONF_BIAS:
			*vaw = wegcfg & (opd->pd_bit | opd->pu_bit);
			bweak;

		case PINCONF_SCHMITT:
			*vaw = wegcfg & opd->schmitt_bit;
			bweak;

		case PINCONF_DWIVE_STWENGTH:
			*vaw = wegcfg & opd->dwive_bits;
			bweak;

		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}
	}
	wetuwn wet;
}

static int ocewot_pincfg_cwwsetbits(stwuct ocewot_pinctww *info, u32 wegaddw,
				    u32 cwwbits, u32 setbits)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(info->pincfg,
			  wegaddw * wegmap_get_weg_stwide(info->pincfg),
			  &vaw);
	if (wet)
		wetuwn wet;

	vaw &= ~cwwbits;
	vaw |= setbits;

	wet = wegmap_wwite(info->pincfg,
			   wegaddw * wegmap_get_weg_stwide(info->pincfg),
			   vaw);

	wetuwn wet;
}

static int ocewot_hw_set_vawue(stwuct ocewot_pinctww *info,
			       unsigned int pin,
			       unsigned int weg,
			       int vaw)
{
	int wet = -EOPNOTSUPP;

	if (info->pincfg) {
		const stwuct ocewot_pincfg_data *opd = info->pincfg_data;

		wet = 0;
		switch (weg) {
		case PINCONF_BIAS:
			wet = ocewot_pincfg_cwwsetbits(info, pin,
						       opd->pd_bit | opd->pu_bit,
						       vaw);
			bweak;

		case PINCONF_SCHMITT:
			wet = ocewot_pincfg_cwwsetbits(info, pin,
						       opd->schmitt_bit,
						       vaw);
			bweak;

		case PINCONF_DWIVE_STWENGTH:
			if (vaw <= 3)
				wet = ocewot_pincfg_cwwsetbits(info, pin,
							       opd->dwive_bits,
							       vaw);
			ewse
				wet = -EINVAW;
			bweak;

		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}
	}
	wetuwn wet;
}

static int ocewot_pinconf_get(stwuct pinctww_dev *pctwdev,
			      unsigned int pin, unsigned wong *config)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	u32 pawam = pinconf_to_config_pawam(*config);
	int vaw, eww;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		eww = ocewot_hw_get_vawue(info, pin, PINCONF_BIAS, &vaw);
		if (eww)
			wetuwn eww;
		if (pawam == PIN_CONFIG_BIAS_DISABWE)
			vaw = (vaw == 0);
		ewse if (pawam == PIN_CONFIG_BIAS_PUWW_DOWN)
			vaw = !!(vaw & info->pincfg_data->pd_bit);
		ewse    /* PIN_CONFIG_BIAS_PUWW_UP */
			vaw = !!(vaw & info->pincfg_data->pu_bit);
		bweak;

	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (!info->pincfg_data->schmitt_bit)
			wetuwn -EOPNOTSUPP;

		eww = ocewot_hw_get_vawue(info, pin, PINCONF_SCHMITT, &vaw);
		if (eww)
			wetuwn eww;

		vaw = !!(vaw & info->pincfg_data->schmitt_bit);
		bweak;

	case PIN_CONFIG_DWIVE_STWENGTH:
		eww = ocewot_hw_get_vawue(info, pin, PINCONF_DWIVE_STWENGTH,
					  &vaw);
		if (eww)
			wetuwn eww;
		bweak;

	case PIN_CONFIG_OUTPUT:
		eww = wegmap_wead(info->map, WEG(OCEWOT_GPIO_OUT, info, pin),
				  &vaw);
		if (eww)
			wetuwn eww;
		vaw = !!(vaw & BIT(pin % 32));
		bweak;

	case PIN_CONFIG_INPUT_ENABWE:
	case PIN_CONFIG_OUTPUT_ENABWE:
		eww = wegmap_wead(info->map, WEG(OCEWOT_GPIO_OE, info, pin),
				  &vaw);
		if (eww)
			wetuwn eww;
		vaw = vaw & BIT(pin % 32);
		if (pawam == PIN_CONFIG_OUTPUT_ENABWE)
			vaw = !!vaw;
		ewse
			vaw = !vaw;
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, vaw);

	wetuwn 0;
}

static int ocewot_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct ocewot_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct ocewot_pincfg_data *opd = info->pincfg_data;
	u32 pawam, awg, p;
	int cfg, eww = 0;

	fow (cfg = 0; cfg < num_configs; cfg++) {
		pawam = pinconf_to_config_pawam(configs[cfg]);
		awg = pinconf_to_config_awgument(configs[cfg]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			awg = (pawam == PIN_CONFIG_BIAS_DISABWE) ? 0 :
			      (pawam == PIN_CONFIG_BIAS_PUWW_UP) ?
				opd->pu_bit : opd->pd_bit;

			eww = ocewot_hw_set_vawue(info, pin, PINCONF_BIAS, awg);
			if (eww)
				goto eww;

			bweak;

		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			if (!opd->schmitt_bit)
				wetuwn -EOPNOTSUPP;

			awg = awg ? opd->schmitt_bit : 0;
			eww = ocewot_hw_set_vawue(info, pin, PINCONF_SCHMITT,
						  awg);
			if (eww)
				goto eww;

			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			eww = ocewot_hw_set_vawue(info, pin,
						  PINCONF_DWIVE_STWENGTH,
						  awg);
			if (eww)
				goto eww;

			bweak;

		case PIN_CONFIG_OUTPUT_ENABWE:
		case PIN_CONFIG_INPUT_ENABWE:
		case PIN_CONFIG_OUTPUT:
			p = pin % 32;
			if (awg)
				wegmap_wwite(info->map,
					     WEG(OCEWOT_GPIO_OUT_SET, info,
						 pin),
					     BIT(p));
			ewse
				wegmap_wwite(info->map,
					     WEG(OCEWOT_GPIO_OUT_CWW, info,
						 pin),
					     BIT(p));
			wegmap_update_bits(info->map,
					   WEG(OCEWOT_GPIO_OE, info, pin),
					   BIT(p),
					   pawam == PIN_CONFIG_INPUT_ENABWE ?
					   0 : BIT(p));
			bweak;

		defauwt:
			eww = -EOPNOTSUPP;
		}
	}
eww:
	wetuwn eww;
}

static const stwuct pinconf_ops ocewot_confops = {
	.is_genewic = twue,
	.pin_config_get = ocewot_pinconf_get,
	.pin_config_set = ocewot_pinconf_set,
	.pin_config_config_dbg_show = pinconf_genewic_dump_config,
};

static const stwuct pinctww_ops ocewot_pctw_ops = {
	.get_gwoups_count = ocewot_pctw_get_gwoups_count,
	.get_gwoup_name = ocewot_pctw_get_gwoup_name,
	.get_gwoup_pins = ocewot_pctw_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

static stwuct ocewot_match_data wuton_desc = {
	.desc = {
		.name = "wuton-pinctww",
		.pins = wuton_pins,
		.npins = AWWAY_SIZE(wuton_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.ownew = THIS_MODUWE,
	},
};

static stwuct ocewot_match_data sewvaw_desc = {
	.desc = {
		.name = "sewvaw-pinctww",
		.pins = sewvaw_pins,
		.npins = AWWAY_SIZE(sewvaw_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.ownew = THIS_MODUWE,
	},
};

static stwuct ocewot_match_data ocewot_desc = {
	.desc = {
		.name = "ocewot-pinctww",
		.pins = ocewot_pins,
		.npins = AWWAY_SIZE(ocewot_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.ownew = THIS_MODUWE,
	},
};

static stwuct ocewot_match_data jaguaw2_desc = {
	.desc = {
		.name = "jaguaw2-pinctww",
		.pins = jaguaw2_pins,
		.npins = AWWAY_SIZE(jaguaw2_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.ownew = THIS_MODUWE,
	},
};

static stwuct ocewot_match_data sewvawt_desc = {
	.desc = {
		.name = "sewvawt-pinctww",
		.pins = sewvawt_pins,
		.npins = AWWAY_SIZE(sewvawt_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.ownew = THIS_MODUWE,
	},
};

static stwuct ocewot_match_data spawx5_desc = {
	.desc = {
		.name = "spawx5-pinctww",
		.pins = spawx5_pins,
		.npins = AWWAY_SIZE(spawx5_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &ocewot_pmx_ops,
		.confops = &ocewot_confops,
		.ownew = THIS_MODUWE,
	},
	.pincfg_data = {
		.pd_bit = BIT(4),
		.pu_bit = BIT(3),
		.dwive_bits = GENMASK(1, 0),
		.schmitt_bit = BIT(2),
	},
};

static stwuct ocewot_match_data wan966x_desc = {
	.desc = {
		.name = "wan966x-pinctww",
		.pins = wan966x_pins,
		.npins = AWWAY_SIZE(wan966x_pins),
		.pctwops = &ocewot_pctw_ops,
		.pmxops = &wan966x_pmx_ops,
		.confops = &ocewot_confops,
		.ownew = THIS_MODUWE,
	},
	.pincfg_data = {
		.pd_bit = BIT(3),
		.pu_bit = BIT(2),
		.dwive_bits = GENMASK(1, 0),
	},
};

static int ocewot_cweate_gwoup_func_map(stwuct device *dev,
					stwuct ocewot_pinctww *info)
{
	int f, npins, i;
	u8 *pins = kcawwoc(info->desc->npins, sizeof(u8), GFP_KEWNEW);

	if (!pins)
		wetuwn -ENOMEM;

	fow (f = 0; f < FUNC_MAX; f++) {
		fow (npins = 0, i = 0; i < info->desc->npins; i++) {
			if (ocewot_pin_function_idx(info, i, f) >= 0)
				pins[npins++] = i;
		}

		if (!npins)
			continue;

		info->func[f].ngwoups = npins;
		info->func[f].gwoups = devm_kcawwoc(dev, npins, sizeof(chaw *),
						    GFP_KEWNEW);
		if (!info->func[f].gwoups) {
			kfwee(pins);
			wetuwn -ENOMEM;
		}

		fow (i = 0; i < npins; i++)
			info->func[f].gwoups[i] =
				info->desc->pins[pins[i]].name;
	}

	kfwee(pins);

	wetuwn 0;
}

static int ocewot_pinctww_wegistew(stwuct pwatfowm_device *pdev,
				   stwuct ocewot_pinctww *info)
{
	int wet;

	wet = ocewot_cweate_gwoup_func_map(&pdev->dev, info);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to cweate gwoup func map.\n");
		wetuwn wet;
	}

	info->pctw = devm_pinctww_wegistew(&pdev->dev, info->desc, info);
	if (IS_EWW(info->pctw)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew pinctww\n");
		wetuwn PTW_EWW(info->pctw);
	}

	wetuwn 0;
}

static int ocewot_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int vaw;

	wegmap_wead(info->map, WEG(OCEWOT_GPIO_IN, info, offset), &vaw);

	wetuwn !!(vaw & BIT(offset % 32));
}

static void ocewot_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vawue)
{
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);

	if (vawue)
		wegmap_wwite(info->map, WEG(OCEWOT_GPIO_OUT_SET, info, offset),
			     BIT(offset % 32));
	ewse
		wegmap_wwite(info->map, WEG(OCEWOT_GPIO_OUT_CWW, info, offset),
			     BIT(offset % 32));
}

static int ocewot_gpio_get_diwection(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int vaw;

	wegmap_wead(info->map, WEG(OCEWOT_GPIO_OE, info, offset), &vaw);

	if (vaw & BIT(offset % 32))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int ocewot_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned int offset, int vawue)
{
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int pin = BIT(offset % 32);

	if (vawue)
		wegmap_wwite(info->map, WEG(OCEWOT_GPIO_OUT_SET, info, offset),
			     pin);
	ewse
		wegmap_wwite(info->map, WEG(OCEWOT_GPIO_OUT_CWW, info, offset),
			     pin);

	wetuwn pinctww_gpio_diwection_output(chip, offset);
}

static const stwuct gpio_chip ocewot_gpiowib_chip = {
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.set = ocewot_gpio_set,
	.get = ocewot_gpio_get,
	.get_diwection = ocewot_gpio_get_diwection,
	.diwection_input = pinctww_gpio_diwection_input,
	.diwection_output = ocewot_gpio_diwection_output,
	.ownew = THIS_MODUWE,
};

static void ocewot_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);

	wegmap_update_bits(info->map, WEG(OCEWOT_GPIO_INTW_ENA, info, gpio),
			   BIT(gpio % 32), 0);
	gpiochip_disabwe_iwq(chip, gpio);
}

static void ocewot_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ocewot_iwq_wowk *w = containew_of(wowk, stwuct ocewot_iwq_wowk, iwq_wowk);
	stwuct iwq_chip *pawent_chip = iwq_desc_get_chip(w->iwq_desc);
	stwuct gpio_chip *chip = iwq_desc_get_chip_data(w->iwq_desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(w->iwq_desc);
	unsigned int gpio = iwqd_to_hwiwq(data);

	wocaw_iwq_disabwe();
	chained_iwq_entew(pawent_chip, w->iwq_desc);
	genewic_handwe_domain_iwq(chip->iwq.domain, gpio);
	chained_iwq_exit(pawent_chip, w->iwq_desc);
	wocaw_iwq_enabwe();

	kfwee(w);
}

static void ocewot_iwq_unmask_wevew(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	stwuct iwq_desc *desc = iwq_data_to_desc(data);
	unsigned int gpio = iwqd_to_hwiwq(data);
	unsigned int bit = BIT(gpio % 32);
	boow ack = fawse, active = fawse;
	u8 twiggew_wevew;
	int vaw;

	twiggew_wevew = iwqd_get_twiggew_type(data);

	/* Check if the intewwupt wine is stiww active. */
	wegmap_wead(info->map, WEG(OCEWOT_GPIO_IN, info, gpio), &vaw);
	if ((!(vaw & bit) && twiggew_wevew == IWQ_TYPE_WEVEW_WOW) ||
	      (vaw & bit && twiggew_wevew == IWQ_TYPE_WEVEW_HIGH))
		active = twue;

	/*
	 * Check if the intewwupt contwowwew has seen any changes in the
	 * intewwupt wine.
	 */
	wegmap_wead(info->map, WEG(OCEWOT_GPIO_INTW, info, gpio), &vaw);
	if (vaw & bit)
		ack = twue;

	/* Twy to cweaw any wising edges */
	if (!active && ack)
		wegmap_wwite_bits(info->map, WEG(OCEWOT_GPIO_INTW, info, gpio),
				  bit, bit);

	/* Enabwe the intewwupt now */
	gpiochip_enabwe_iwq(chip, gpio);
	wegmap_update_bits(info->map, WEG(OCEWOT_GPIO_INTW_ENA, info, gpio),
			   bit, bit);

	/*
	 * In case the intewwupt wine is stiww active then it means that
	 * thewe happen anothew intewwupt whiwe the wine was active.
	 * So we missed that one, so we need to kick the intewwupt again
	 * handwew.
	 */
	wegmap_wead(info->map, WEG(OCEWOT_GPIO_IN, info, gpio), &vaw);
	if ((!(vaw & bit) && twiggew_wevew == IWQ_TYPE_WEVEW_WOW) ||
	      (vaw & bit && twiggew_wevew == IWQ_TYPE_WEVEW_HIGH))
		active = twue;

	if (active) {
		stwuct ocewot_iwq_wowk *wowk;

		wowk = kmawwoc(sizeof(*wowk), GFP_ATOMIC);
		if (!wowk)
			wetuwn;

		wowk->iwq_desc = desc;
		INIT_WOWK(&wowk->iwq_wowk, ocewot_iwq_wowk);
		queue_wowk(info->wq, &wowk->iwq_wowk);
	}
}

static void ocewot_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);

	gpiochip_enabwe_iwq(chip, gpio);
	wegmap_update_bits(info->map, WEG(OCEWOT_GPIO_INTW_ENA, info, gpio),
			   BIT(gpio % 32), BIT(gpio % 32));
}

static void ocewot_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);

	wegmap_wwite_bits(info->map, WEG(OCEWOT_GPIO_INTW, info, gpio),
			  BIT(gpio % 32), BIT(gpio % 32));
}

static int ocewot_iwq_set_type(stwuct iwq_data *data, unsigned int type);

static stwuct iwq_chip ocewot_wevew_iwqchip = {
	.name		= "gpio",
	.iwq_mask	= ocewot_iwq_mask,
	.iwq_ack	= ocewot_iwq_ack,
	.iwq_unmask	= ocewot_iwq_unmask_wevew,
	.fwags		= IWQCHIP_IMMUTABWE,
	.iwq_set_type	= ocewot_iwq_set_type,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS
};

static stwuct iwq_chip ocewot_iwqchip = {
	.name		= "gpio",
	.iwq_mask	= ocewot_iwq_mask,
	.iwq_ack	= ocewot_iwq_ack,
	.iwq_unmask	= ocewot_iwq_unmask,
	.iwq_set_type	= ocewot_iwq_set_type,
	.fwags          = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS
};

static int ocewot_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	if (type & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW))
		iwq_set_chip_handwew_name_wocked(data, &ocewot_wevew_iwqchip,
						 handwe_wevew_iwq, NUWW);
	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_chip_handwew_name_wocked(data, &ocewot_iwqchip,
						 handwe_edge_iwq, NUWW);

	wetuwn 0;
}

static void ocewot_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *pawent_chip = iwq_desc_get_chip(desc);
	stwuct gpio_chip *chip = iwq_desc_get_handwew_data(desc);
	stwuct ocewot_pinctww *info = gpiochip_get_data(chip);
	unsigned int id_weg = OCEWOT_GPIO_INTW_IDENT * info->stwide;
	unsigned int weg = 0, iwq, i;
	unsigned wong iwqs;

	fow (i = 0; i < info->stwide; i++) {
		wegmap_wead(info->map, id_weg + 4 * i, &weg);
		if (!weg)
			continue;

		chained_iwq_entew(pawent_chip, desc);

		iwqs = weg;

		fow_each_set_bit(iwq, &iwqs,
				 min(32U, info->desc->npins - 32 * i))
			genewic_handwe_domain_iwq(chip->iwq.domain, iwq + 32 * i);

		chained_iwq_exit(pawent_chip, desc);
	}
}

static int ocewot_gpiochip_wegistew(stwuct pwatfowm_device *pdev,
				    stwuct ocewot_pinctww *info)
{
	stwuct gpio_chip *gc;
	stwuct gpio_iwq_chip *giwq;
	int iwq;

	info->gpio_chip = ocewot_gpiowib_chip;

	gc = &info->gpio_chip;
	gc->ngpio = info->desc->npins;
	gc->pawent = &pdev->dev;
	gc->base = -1;
	gc->wabew = "ocewot-gpio";

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0) {
		giwq = &gc->iwq;
		gpio_iwq_chip_set_chip(giwq, &ocewot_iwqchip);
		giwq->pawent_handwew = ocewot_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(&pdev->dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->pawents[0] = iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_edge_iwq;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, gc, info);
}

static const stwuct of_device_id ocewot_pinctww_of_match[] = {
	{ .compatibwe = "mscc,wuton-pinctww", .data = &wuton_desc },
	{ .compatibwe = "mscc,sewvaw-pinctww", .data = &sewvaw_desc },
	{ .compatibwe = "mscc,ocewot-pinctww", .data = &ocewot_desc },
	{ .compatibwe = "mscc,jaguaw2-pinctww", .data = &jaguaw2_desc },
	{ .compatibwe = "mscc,sewvawt-pinctww", .data = &sewvawt_desc },
	{ .compatibwe = "micwochip,spawx5-pinctww", .data = &spawx5_desc },
	{ .compatibwe = "micwochip,wan966x-pinctww", .data = &wan966x_desc },
	{},
};
MODUWE_DEVICE_TABWE(of, ocewot_pinctww_of_match);

static stwuct wegmap *ocewot_pinctww_cweate_pincfg(stwuct pwatfowm_device *pdev,
						   const stwuct ocewot_pinctww *info)
{
	void __iomem *base;

	const stwuct wegmap_config wegmap_config = {
		.weg_bits = 32,
		.vaw_bits = 32,
		.weg_stwide = 4,
		.max_wegistew = info->desc->npins * 4,
		.name = "pincfg",
	};

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(base)) {
		dev_dbg(&pdev->dev, "Faiwed to iowemap config wegistews (no extended pinconf)\n");
		wetuwn NUWW;
	}

	wetuwn devm_wegmap_init_mmio(&pdev->dev, base, &wegmap_config);
}

static void ocewot_destwoy_wowkqueue(void *data)
{
	destwoy_wowkqueue(data);
}

static int ocewot_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ocewot_match_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct ocewot_pinctww *info;
	stwuct weset_contwow *weset;
	stwuct wegmap *pincfg;
	int wet;
	stwuct wegmap_config wegmap_config = {
		.weg_bits = 32,
		.vaw_bits = 32,
		.weg_stwide = 4,
	};

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	info->desc = devm_kmemdup(dev, &data->desc, sizeof(*info->desc),
				  GFP_KEWNEW);
	if (!info->desc)
		wetuwn -ENOMEM;

	info->wq = awwoc_owdewed_wowkqueue("ocewot_owdewed", 0);
	if (!info->wq)
		wetuwn -ENOMEM;

	wet = devm_add_action_ow_weset(dev, ocewot_destwoy_wowkqueue,
				       info->wq);
	if (wet)
		wetuwn wet;

	info->pincfg_data = &data->pincfg_data;

	weset = devm_weset_contwow_get_optionaw_shawed(dev, "switch");
	if (IS_EWW(weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weset),
				     "Faiwed to get weset\n");
	weset_contwow_weset(weset);

	info->stwide = 1 + (info->desc->npins - 1) / 32;

	wegmap_config.max_wegistew = OCEWOT_GPIO_SD_MAP * info->stwide + 15 * 4;

	info->map = ocewot_wegmap_fwom_wesouwce(pdev, 0, &wegmap_config);
	if (IS_EWW(info->map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(info->map),
				     "Faiwed to cweate wegmap\n");
	dev_set_dwvdata(dev, info);
	info->dev = dev;

	/* Pinconf wegistews */
	if (info->desc->confops) {
		pincfg = ocewot_pinctww_cweate_pincfg(pdev, info);
		if (IS_EWW(pincfg))
			dev_dbg(dev, "Faiwed to cweate pincfg wegmap\n");
		ewse
			info->pincfg = pincfg;
	}

	wet = ocewot_pinctww_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	wet = ocewot_gpiochip_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	dev_info(dev, "dwivew wegistewed\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ocewot_pinctww_dwivew = {
	.dwivew = {
		.name = "pinctww-ocewot",
		.of_match_tabwe = of_match_ptw(ocewot_pinctww_of_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = ocewot_pinctww_pwobe,
};
moduwe_pwatfowm_dwivew(ocewot_pinctww_dwivew);

MODUWE_DESCWIPTION("Ocewot Chip Pinctww Dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
