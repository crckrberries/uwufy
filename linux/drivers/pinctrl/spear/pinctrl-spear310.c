/*
 * Dwivew fow the ST Micwoewectwonics SPEAw310 pinmux
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "pinctww-speaw3xx.h"

#define DWIVEW_NAME "speaw310-pinmux"

/* addwesses */
#define PMX_CONFIG_WEG			0x08

/* emi_cs_0_to_5_pins */
static const unsigned emi_cs_0_to_5_pins[] = { 45, 46, 47, 48, 49, 50 };
static stwuct speaw_muxweg emi_cs_0_to_5_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux emi_cs_0_to_5_modemux[] = {
	{
		.muxwegs = emi_cs_0_to_5_muxweg,
		.nmuxwegs = AWWAY_SIZE(emi_cs_0_to_5_muxweg),
	},
};

static stwuct speaw_pingwoup emi_cs_0_to_5_pingwoup = {
	.name = "emi_cs_0_to_5_gwp",
	.pins = emi_cs_0_to_5_pins,
	.npins = AWWAY_SIZE(emi_cs_0_to_5_pins),
	.modemuxs = emi_cs_0_to_5_modemux,
	.nmodemuxs = AWWAY_SIZE(emi_cs_0_to_5_modemux),
};

static const chaw *const emi_cs_0_to_5_gwps[] = { "emi_cs_0_to_5_gwp" };
static stwuct speaw_function emi_cs_0_to_5_function = {
	.name = "emi",
	.gwoups = emi_cs_0_to_5_gwps,
	.ngwoups = AWWAY_SIZE(emi_cs_0_to_5_gwps),
};

/* uawt1_pins */
static const unsigned uawt1_pins[] = { 0, 1 };
static stwuct speaw_muxweg uawt1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_FIWDA_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux uawt1_modemux[] = {
	{
		.muxwegs = uawt1_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt1_muxweg),
	},
};

static stwuct speaw_pingwoup uawt1_pingwoup = {
	.name = "uawt1_gwp",
	.pins = uawt1_pins,
	.npins = AWWAY_SIZE(uawt1_pins),
	.modemuxs = uawt1_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt1_modemux),
};

static const chaw *const uawt1_gwps[] = { "uawt1_gwp" };
static stwuct speaw_function uawt1_function = {
	.name = "uawt1",
	.gwoups = uawt1_gwps,
	.ngwoups = AWWAY_SIZE(uawt1_gwps),
};

/* uawt2_pins */
static const unsigned uawt2_pins[] = { 43, 44 };
static stwuct speaw_muxweg uawt2_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux uawt2_modemux[] = {
	{
		.muxwegs = uawt2_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt2_muxweg),
	},
};

static stwuct speaw_pingwoup uawt2_pingwoup = {
	.name = "uawt2_gwp",
	.pins = uawt2_pins,
	.npins = AWWAY_SIZE(uawt2_pins),
	.modemuxs = uawt2_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt2_modemux),
};

static const chaw *const uawt2_gwps[] = { "uawt2_gwp" };
static stwuct speaw_function uawt2_function = {
	.name = "uawt2",
	.gwoups = uawt2_gwps,
	.ngwoups = AWWAY_SIZE(uawt2_gwps),
};

/* uawt3_pins */
static const unsigned uawt3_pins[] = { 37, 38 };
static stwuct speaw_muxweg uawt3_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux uawt3_modemux[] = {
	{
		.muxwegs = uawt3_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt3_muxweg),
	},
};

static stwuct speaw_pingwoup uawt3_pingwoup = {
	.name = "uawt3_gwp",
	.pins = uawt3_pins,
	.npins = AWWAY_SIZE(uawt3_pins),
	.modemuxs = uawt3_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt3_modemux),
};

static const chaw *const uawt3_gwps[] = { "uawt3_gwp" };
static stwuct speaw_function uawt3_function = {
	.name = "uawt3",
	.gwoups = uawt3_gwps,
	.ngwoups = AWWAY_SIZE(uawt3_gwps),
};

/* uawt4_pins */
static const unsigned uawt4_pins[] = { 39, 40 };
static stwuct speaw_muxweg uawt4_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux uawt4_modemux[] = {
	{
		.muxwegs = uawt4_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt4_muxweg),
	},
};

static stwuct speaw_pingwoup uawt4_pingwoup = {
	.name = "uawt4_gwp",
	.pins = uawt4_pins,
	.npins = AWWAY_SIZE(uawt4_pins),
	.modemuxs = uawt4_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt4_modemux),
};

static const chaw *const uawt4_gwps[] = { "uawt4_gwp" };
static stwuct speaw_function uawt4_function = {
	.name = "uawt4",
	.gwoups = uawt4_gwps,
	.ngwoups = AWWAY_SIZE(uawt4_gwps),
};

/* uawt5_pins */
static const unsigned uawt5_pins[] = { 41, 42 };
static stwuct speaw_muxweg uawt5_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux uawt5_modemux[] = {
	{
		.muxwegs = uawt5_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt5_muxweg),
	},
};

static stwuct speaw_pingwoup uawt5_pingwoup = {
	.name = "uawt5_gwp",
	.pins = uawt5_pins,
	.npins = AWWAY_SIZE(uawt5_pins),
	.modemuxs = uawt5_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt5_modemux),
};

static const chaw *const uawt5_gwps[] = { "uawt5_gwp" };
static stwuct speaw_function uawt5_function = {
	.name = "uawt5",
	.gwoups = uawt5_gwps,
	.ngwoups = AWWAY_SIZE(uawt5_gwps),
};

/* fsmc_pins */
static const unsigned fsmc_pins[] = { 34, 35, 36 };
static stwuct speaw_muxweg fsmc_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux fsmc_modemux[] = {
	{
		.muxwegs = fsmc_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_muxweg),
	},
};

static stwuct speaw_pingwoup fsmc_pingwoup = {
	.name = "fsmc_gwp",
	.pins = fsmc_pins,
	.npins = AWWAY_SIZE(fsmc_pins),
	.modemuxs = fsmc_modemux,
	.nmodemuxs = AWWAY_SIZE(fsmc_modemux),
};

static const chaw *const fsmc_gwps[] = { "fsmc_gwp" };
static stwuct speaw_function fsmc_function = {
	.name = "fsmc",
	.gwoups = fsmc_gwps,
	.ngwoups = AWWAY_SIZE(fsmc_gwps),
};

/* ws485_0_pins */
static const unsigned ws485_0_pins[] = { 19, 20, 21, 22, 23 };
static stwuct speaw_muxweg ws485_0_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux ws485_0_modemux[] = {
	{
		.muxwegs = ws485_0_muxweg,
		.nmuxwegs = AWWAY_SIZE(ws485_0_muxweg),
	},
};

static stwuct speaw_pingwoup ws485_0_pingwoup = {
	.name = "ws485_0_gwp",
	.pins = ws485_0_pins,
	.npins = AWWAY_SIZE(ws485_0_pins),
	.modemuxs = ws485_0_modemux,
	.nmodemuxs = AWWAY_SIZE(ws485_0_modemux),
};

static const chaw *const ws485_0_gwps[] = { "ws485_0" };
static stwuct speaw_function ws485_0_function = {
	.name = "ws485_0",
	.gwoups = ws485_0_gwps,
	.ngwoups = AWWAY_SIZE(ws485_0_gwps),
};

/* ws485_1_pins */
static const unsigned ws485_1_pins[] = { 14, 15, 16, 17, 18 };
static stwuct speaw_muxweg ws485_1_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux ws485_1_modemux[] = {
	{
		.muxwegs = ws485_1_muxweg,
		.nmuxwegs = AWWAY_SIZE(ws485_1_muxweg),
	},
};

static stwuct speaw_pingwoup ws485_1_pingwoup = {
	.name = "ws485_1_gwp",
	.pins = ws485_1_pins,
	.npins = AWWAY_SIZE(ws485_1_pins),
	.modemuxs = ws485_1_modemux,
	.nmodemuxs = AWWAY_SIZE(ws485_1_modemux),
};

static const chaw *const ws485_1_gwps[] = { "ws485_1" };
static stwuct speaw_function ws485_1_function = {
	.name = "ws485_1",
	.gwoups = ws485_1_gwps,
	.ngwoups = AWWAY_SIZE(ws485_1_gwps),
};

/* tdm_pins */
static const unsigned tdm_pins[] = { 10, 11, 12, 13 };
static stwuct speaw_muxweg tdm_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux tdm_modemux[] = {
	{
		.muxwegs = tdm_muxweg,
		.nmuxwegs = AWWAY_SIZE(tdm_muxweg),
	},
};

static stwuct speaw_pingwoup tdm_pingwoup = {
	.name = "tdm_gwp",
	.pins = tdm_pins,
	.npins = AWWAY_SIZE(tdm_pins),
	.modemuxs = tdm_modemux,
	.nmodemuxs = AWWAY_SIZE(tdm_modemux),
};

static const chaw *const tdm_gwps[] = { "tdm_gwp" };
static stwuct speaw_function tdm_function = {
	.name = "tdm",
	.gwoups = tdm_gwps,
	.ngwoups = AWWAY_SIZE(tdm_gwps),
};

/* pingwoups */
static stwuct speaw_pingwoup *speaw310_pingwoups[] = {
	SPEAW3XX_COMMON_PINGWOUPS,
	&emi_cs_0_to_5_pingwoup,
	&uawt1_pingwoup,
	&uawt2_pingwoup,
	&uawt3_pingwoup,
	&uawt4_pingwoup,
	&uawt5_pingwoup,
	&fsmc_pingwoup,
	&ws485_0_pingwoup,
	&ws485_1_pingwoup,
	&tdm_pingwoup,
};

/* functions */
static stwuct speaw_function *speaw310_functions[] = {
	SPEAW3XX_COMMON_FUNCTIONS,
	&emi_cs_0_to_5_function,
	&uawt1_function,
	&uawt2_function,
	&uawt3_function,
	&uawt4_function,
	&uawt5_function,
	&fsmc_function,
	&ws485_0_function,
	&ws485_1_function,
	&tdm_function,
};

static const stwuct of_device_id speaw310_pinctww_of_match[] = {
	{
		.compatibwe = "st,speaw310-pinmux",
	},
	{},
};

static int speaw310_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	speaw3xx_machdata.gwoups = speaw310_pingwoups;
	speaw3xx_machdata.ngwoups = AWWAY_SIZE(speaw310_pingwoups);
	speaw3xx_machdata.functions = speaw310_functions;
	speaw3xx_machdata.nfunctions = AWWAY_SIZE(speaw310_functions);

	pmx_init_addw(&speaw3xx_machdata, PMX_CONFIG_WEG);
	pmx_init_gpio_pingwoup_addw(speaw3xx_machdata.gpio_pingwoups,
			speaw3xx_machdata.ngpio_pingwoups, PMX_CONFIG_WEG);

	speaw3xx_machdata.modes_suppowted = fawse;

	wetuwn speaw_pinctww_pwobe(pdev, &speaw3xx_machdata);
}

static stwuct pwatfowm_dwivew speaw310_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = speaw310_pinctww_of_match,
	},
	.pwobe = speaw310_pinctww_pwobe,
};

static int __init speaw310_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&speaw310_pinctww_dwivew);
}
awch_initcaww(speaw310_pinctww_init);
