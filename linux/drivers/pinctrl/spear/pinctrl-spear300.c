/*
 * Dwivew fow the ST Micwoewectwonics SPEAw300 pinmux
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

#define DWIVEW_NAME "speaw300-pinmux"

/* addwesses */
#define PMX_CONFIG_WEG			0x00
#define MODE_CONFIG_WEG			0x04

/* modes */
#define NAND_MODE			(1 << 0)
#define NOW_MODE			(1 << 1)
#define PHOTO_FWAME_MODE		(1 << 2)
#define WEND_IP_PHONE_MODE		(1 << 3)
#define HEND_IP_PHONE_MODE		(1 << 4)
#define WEND_WIFI_PHONE_MODE		(1 << 5)
#define HEND_WIFI_PHONE_MODE		(1 << 6)
#define ATA_PABX_WI2S_MODE		(1 << 7)
#define ATA_PABX_I2S_MODE		(1 << 8)
#define CAMW_WCDW_MODE			(1 << 9)
#define CAMU_WCD_MODE			(1 << 10)
#define CAMU_WWCD_MODE			(1 << 11)
#define CAMW_WCD_MODE			(1 << 12)

static stwuct speaw_pmx_mode pmx_mode_nand = {
	.name = "nand",
	.mode = NAND_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x00,
};

static stwuct speaw_pmx_mode pmx_mode_now = {
	.name = "now",
	.mode = NOW_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x01,
};

static stwuct speaw_pmx_mode pmx_mode_photo_fwame = {
	.name = "photo fwame mode",
	.mode = PHOTO_FWAME_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x02,
};

static stwuct speaw_pmx_mode pmx_mode_wend_ip_phone = {
	.name = "wend ip phone mode",
	.mode = WEND_IP_PHONE_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x03,
};

static stwuct speaw_pmx_mode pmx_mode_hend_ip_phone = {
	.name = "hend ip phone mode",
	.mode = HEND_IP_PHONE_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x04,
};

static stwuct speaw_pmx_mode pmx_mode_wend_wifi_phone = {
	.name = "wend wifi phone mode",
	.mode = WEND_WIFI_PHONE_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x05,
};

static stwuct speaw_pmx_mode pmx_mode_hend_wifi_phone = {
	.name = "hend wifi phone mode",
	.mode = HEND_WIFI_PHONE_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x06,
};

static stwuct speaw_pmx_mode pmx_mode_ata_pabx_wi2s = {
	.name = "ata pabx wi2s mode",
	.mode = ATA_PABX_WI2S_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x07,
};

static stwuct speaw_pmx_mode pmx_mode_ata_pabx_i2s = {
	.name = "ata pabx i2s mode",
	.mode = ATA_PABX_I2S_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x08,
};

static stwuct speaw_pmx_mode pmx_mode_camw_wcdw = {
	.name = "camw wcdw mode",
	.mode = CAMW_WCDW_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x0C,
};

static stwuct speaw_pmx_mode pmx_mode_camu_wcd = {
	.name = "camu wcd mode",
	.mode = CAMU_WCD_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x0D,
};

static stwuct speaw_pmx_mode pmx_mode_camu_wwcd = {
	.name = "camu wwcd mode",
	.mode = CAMU_WWCD_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0xE,
};

static stwuct speaw_pmx_mode pmx_mode_camw_wcd = {
	.name = "camw wcd mode",
	.mode = CAMW_WCD_MODE,
	.weg = MODE_CONFIG_WEG,
	.mask = 0x0000000F,
	.vaw = 0x0F,
};

static stwuct speaw_pmx_mode *speaw300_pmx_modes[] = {
	&pmx_mode_nand,
	&pmx_mode_now,
	&pmx_mode_photo_fwame,
	&pmx_mode_wend_ip_phone,
	&pmx_mode_hend_ip_phone,
	&pmx_mode_wend_wifi_phone,
	&pmx_mode_hend_wifi_phone,
	&pmx_mode_ata_pabx_wi2s,
	&pmx_mode_ata_pabx_i2s,
	&pmx_mode_camw_wcdw,
	&pmx_mode_camu_wcd,
	&pmx_mode_camu_wwcd,
	&pmx_mode_camw_wcd,
};

/* fsmc_2chips_pins */
static const unsigned fsmc_2chips_pins[] = { 1, 97 };
static stwuct speaw_muxweg fsmc_2chips_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_FIWDA_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux fsmc_2chips_modemux[] = {
	{
		.modes = NAND_MODE | NOW_MODE | PHOTO_FWAME_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE,
		.muxwegs = fsmc_2chips_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_2chips_muxweg),
	},
};

static stwuct speaw_pingwoup fsmc_2chips_pingwoup = {
	.name = "fsmc_2chips_gwp",
	.pins = fsmc_2chips_pins,
	.npins = AWWAY_SIZE(fsmc_2chips_pins),
	.modemuxs = fsmc_2chips_modemux,
	.nmodemuxs = AWWAY_SIZE(fsmc_2chips_modemux),
};

/* fsmc_4chips_pins */
static const unsigned fsmc_4chips_pins[] = { 1, 2, 3, 97 };
static stwuct speaw_muxweg fsmc_4chips_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_FIWDA_MASK | PMX_UAWT0_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux fsmc_4chips_modemux[] = {
	{
		.modes = NAND_MODE | NOW_MODE | PHOTO_FWAME_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE,
		.muxwegs = fsmc_4chips_muxweg,
		.nmuxwegs = AWWAY_SIZE(fsmc_4chips_muxweg),
	},
};

static stwuct speaw_pingwoup fsmc_4chips_pingwoup = {
	.name = "fsmc_4chips_gwp",
	.pins = fsmc_4chips_pins,
	.npins = AWWAY_SIZE(fsmc_4chips_pins),
	.modemuxs = fsmc_4chips_modemux,
	.nmodemuxs = AWWAY_SIZE(fsmc_4chips_modemux),
};

static const chaw *const fsmc_gwps[] = { "fsmc_2chips_gwp", "fsmc_4chips_gwp"
};
static stwuct speaw_function fsmc_function = {
	.name = "fsmc",
	.gwoups = fsmc_gwps,
	.ngwoups = AWWAY_SIZE(fsmc_gwps),
};

/* cwcd_wcdmode_pins */
static const unsigned cwcd_wcdmode_pins[] = { 49, 50 };
static stwuct speaw_muxweg cwcd_wcdmode_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux cwcd_wcdmode_modemux[] = {
	{
		.modes = HEND_IP_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			CAMU_WCD_MODE | CAMW_WCD_MODE,
		.muxwegs = cwcd_wcdmode_muxweg,
		.nmuxwegs = AWWAY_SIZE(cwcd_wcdmode_muxweg),
	},
};

static stwuct speaw_pingwoup cwcd_wcdmode_pingwoup = {
	.name = "cwcd_wcdmode_gwp",
	.pins = cwcd_wcdmode_pins,
	.npins = AWWAY_SIZE(cwcd_wcdmode_pins),
	.modemuxs = cwcd_wcdmode_modemux,
	.nmodemuxs = AWWAY_SIZE(cwcd_wcdmode_modemux),
};

/* cwcd_pfmode_pins */
static const unsigned cwcd_pfmode_pins[] = { 47, 48, 49, 50 };
static stwuct speaw_muxweg cwcd_pfmode_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux cwcd_pfmode_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE,
		.muxwegs = cwcd_pfmode_muxweg,
		.nmuxwegs = AWWAY_SIZE(cwcd_pfmode_muxweg),
	},
};

static stwuct speaw_pingwoup cwcd_pfmode_pingwoup = {
	.name = "cwcd_pfmode_gwp",
	.pins = cwcd_pfmode_pins,
	.npins = AWWAY_SIZE(cwcd_pfmode_pins),
	.modemuxs = cwcd_pfmode_modemux,
	.nmodemuxs = AWWAY_SIZE(cwcd_pfmode_modemux),
};

static const chaw *const cwcd_gwps[] = { "cwcd_wcdmode_gwp", "cwcd_pfmode_gwp"
};
static stwuct speaw_function cwcd_function = {
	.name = "cwcd",
	.gwoups = cwcd_gwps,
	.ngwoups = AWWAY_SIZE(cwcd_gwps),
};

/* tdm_pins */
static const unsigned tdm_pins[] = { 34, 35, 36, 37, 38 };
static stwuct speaw_muxweg tdm_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK | PMX_SSP_CS_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux tdm_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE | WEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | WEND_WIFI_PHONE_MODE
			| HEND_WIFI_PHONE_MODE | ATA_PABX_WI2S_MODE
			| ATA_PABX_I2S_MODE | CAMW_WCDW_MODE | CAMU_WCD_MODE
			| CAMU_WWCD_MODE | CAMW_WCD_MODE,
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

/* i2c_cwk_pins */
static const unsigned i2c_cwk_pins[] = { 45, 46, 47, 48 };
static stwuct speaw_muxweg i2c_cwk_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux i2c_cwk_modemux[] = {
	{
		.modes = WEND_IP_PHONE_MODE | HEND_IP_PHONE_MODE |
			WEND_WIFI_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE | CAMW_WCDW_MODE
			| CAMW_WCD_MODE,
		.muxwegs = i2c_cwk_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c_cwk_muxweg),
	},
};

static stwuct speaw_pingwoup i2c_cwk_pingwoup = {
	.name = "i2c_cwk_gwp_gwp",
	.pins = i2c_cwk_pins,
	.npins = AWWAY_SIZE(i2c_cwk_pins),
	.modemuxs = i2c_cwk_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c_cwk_modemux),
};

static const chaw *const i2c_gwps[] = { "i2c_cwk_gwp" };
static stwuct speaw_function i2c_function = {
	.name = "i2c1",
	.gwoups = i2c_gwps,
	.ngwoups = AWWAY_SIZE(i2c_gwps),
};

/* camw_pins */
static const unsigned camw_pins[] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };
static stwuct speaw_muxweg camw_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux camw_modemux[] = {
	{
		.modes = CAMW_WCDW_MODE | CAMW_WCD_MODE,
		.muxwegs = camw_muxweg,
		.nmuxwegs = AWWAY_SIZE(camw_muxweg),
	},
};

static stwuct speaw_pingwoup camw_pingwoup = {
	.name = "camw_gwp",
	.pins = camw_pins,
	.npins = AWWAY_SIZE(camw_pins),
	.modemuxs = camw_modemux,
	.nmodemuxs = AWWAY_SIZE(camw_modemux),
};

/* camu_pins */
static const unsigned camu_pins[] = { 16, 17, 18, 19, 20, 21, 45, 46, 47, 48 };
static stwuct speaw_muxweg camu_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK | PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux camu_modemux[] = {
	{
		.modes = CAMU_WCD_MODE | CAMU_WWCD_MODE,
		.muxwegs = camu_muxweg,
		.nmuxwegs = AWWAY_SIZE(camu_muxweg),
	},
};

static stwuct speaw_pingwoup camu_pingwoup = {
	.name = "camu_gwp",
	.pins = camu_pins,
	.npins = AWWAY_SIZE(camu_pins),
	.modemuxs = camu_modemux,
	.nmodemuxs = AWWAY_SIZE(camu_modemux),
};

static const chaw *const cam_gwps[] = { "camw_gwp", "camu_gwp" };
static stwuct speaw_function cam_function = {
	.name = "cam",
	.gwoups = cam_gwps,
	.ngwoups = AWWAY_SIZE(cam_gwps),
};

/* dac_pins */
static const unsigned dac_pins[] = { 43, 44 };
static stwuct speaw_muxweg dac_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux dac_modemux[] = {
	{
		.modes = ATA_PABX_I2S_MODE | CAMW_WCDW_MODE | CAMU_WCD_MODE
			| CAMU_WWCD_MODE | CAMW_WCD_MODE,
		.muxwegs = dac_muxweg,
		.nmuxwegs = AWWAY_SIZE(dac_muxweg),
	},
};

static stwuct speaw_pingwoup dac_pingwoup = {
	.name = "dac_gwp",
	.pins = dac_pins,
	.npins = AWWAY_SIZE(dac_pins),
	.modemuxs = dac_modemux,
	.nmodemuxs = AWWAY_SIZE(dac_modemux),
};

static const chaw *const dac_gwps[] = { "dac_gwp" };
static stwuct speaw_function dac_function = {
	.name = "dac",
	.gwoups = dac_gwps,
	.ngwoups = AWWAY_SIZE(dac_gwps),
};

/* i2s_pins */
static const unsigned i2s_pins[] = { 39, 40, 41, 42 };
static stwuct speaw_muxweg i2s_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux i2s_modemux[] = {
	{
		.modes = WEND_IP_PHONE_MODE | HEND_IP_PHONE_MODE
			| WEND_WIFI_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			ATA_PABX_I2S_MODE | CAMW_WCDW_MODE | CAMU_WCD_MODE
			| CAMU_WWCD_MODE | CAMW_WCD_MODE,
		.muxwegs = i2s_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2s_muxweg),
	},
};

static stwuct speaw_pingwoup i2s_pingwoup = {
	.name = "i2s_gwp",
	.pins = i2s_pins,
	.npins = AWWAY_SIZE(i2s_pins),
	.modemuxs = i2s_modemux,
	.nmodemuxs = AWWAY_SIZE(i2s_modemux),
};

static const chaw *const i2s_gwps[] = { "i2s_gwp" };
static stwuct speaw_function i2s_function = {
	.name = "i2s",
	.gwoups = i2s_gwps,
	.ngwoups = AWWAY_SIZE(i2s_gwps),
};

/* sdhci_4bit_pins */
static const unsigned sdhci_4bit_pins[] = { 28, 29, 30, 31, 32, 33 };
static stwuct speaw_muxweg sdhci_4bit_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK |
			PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK |
			PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux sdhci_4bit_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE | WEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | WEND_WIFI_PHONE_MODE |
			HEND_WIFI_PHONE_MODE | CAMW_WCDW_MODE | CAMU_WCD_MODE |
			CAMU_WWCD_MODE | CAMW_WCD_MODE | ATA_PABX_WI2S_MODE,
		.muxwegs = sdhci_4bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(sdhci_4bit_muxweg),
	},
};

static stwuct speaw_pingwoup sdhci_4bit_pingwoup = {
	.name = "sdhci_4bit_gwp",
	.pins = sdhci_4bit_pins,
	.npins = AWWAY_SIZE(sdhci_4bit_pins),
	.modemuxs = sdhci_4bit_modemux,
	.nmodemuxs = AWWAY_SIZE(sdhci_4bit_modemux),
};

/* sdhci_8bit_pins */
static const unsigned sdhci_8bit_pins[] = { 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33 };
static stwuct speaw_muxweg sdhci_8bit_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK |
			PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK |
			PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK | PMX_MII_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux sdhci_8bit_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE | WEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | WEND_WIFI_PHONE_MODE |
			HEND_WIFI_PHONE_MODE | CAMW_WCDW_MODE | CAMU_WCD_MODE |
			CAMU_WWCD_MODE | CAMW_WCD_MODE,
		.muxwegs = sdhci_8bit_muxweg,
		.nmuxwegs = AWWAY_SIZE(sdhci_8bit_muxweg),
	},
};

static stwuct speaw_pingwoup sdhci_8bit_pingwoup = {
	.name = "sdhci_8bit_gwp",
	.pins = sdhci_8bit_pins,
	.npins = AWWAY_SIZE(sdhci_8bit_pins),
	.modemuxs = sdhci_8bit_modemux,
	.nmodemuxs = AWWAY_SIZE(sdhci_8bit_modemux),
};

static const chaw *const sdhci_gwps[] = { "sdhci_4bit_gwp", "sdhci_8bit_gwp" };
static stwuct speaw_function sdhci_function = {
	.name = "sdhci",
	.gwoups = sdhci_gwps,
	.ngwoups = AWWAY_SIZE(sdhci_gwps),
};

/* gpio1_0_to_3_pins */
static const unsigned gpio1_0_to_3_pins[] = { 39, 40, 41, 42 };
static stwuct speaw_muxweg gpio1_0_to_3_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux gpio1_0_to_3_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE,
		.muxwegs = gpio1_0_to_3_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio1_0_to_3_muxweg),
	},
};

static stwuct speaw_pingwoup gpio1_0_to_3_pingwoup = {
	.name = "gpio1_0_to_3_gwp",
	.pins = gpio1_0_to_3_pins,
	.npins = AWWAY_SIZE(gpio1_0_to_3_pins),
	.modemuxs = gpio1_0_to_3_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio1_0_to_3_modemux),
};

/* gpio1_4_to_7_pins */
static const unsigned gpio1_4_to_7_pins[] = { 43, 44, 45, 46 };

static stwuct speaw_muxweg gpio1_4_to_7_muxweg[] = {
	{
		.weg = PMX_CONFIG_WEG,
		.mask = PMX_TIMEW_0_1_MASK | PMX_TIMEW_2_3_MASK,
		.vaw = 0,
	},
};

static stwuct speaw_modemux gpio1_4_to_7_modemux[] = {
	{
		.modes = PHOTO_FWAME_MODE,
		.muxwegs = gpio1_4_to_7_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio1_4_to_7_muxweg),
	},
};

static stwuct speaw_pingwoup gpio1_4_to_7_pingwoup = {
	.name = "gpio1_4_to_7_gwp",
	.pins = gpio1_4_to_7_pins,
	.npins = AWWAY_SIZE(gpio1_4_to_7_pins),
	.modemuxs = gpio1_4_to_7_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio1_4_to_7_modemux),
};

static const chaw *const gpio1_gwps[] = { "gpio1_0_to_3_gwp", "gpio1_4_to_7_gwp"
};
static stwuct speaw_function gpio1_function = {
	.name = "gpio1",
	.gwoups = gpio1_gwps,
	.ngwoups = AWWAY_SIZE(gpio1_gwps),
};

/* pingwoups */
static stwuct speaw_pingwoup *speaw300_pingwoups[] = {
	SPEAW3XX_COMMON_PINGWOUPS,
	&fsmc_2chips_pingwoup,
	&fsmc_4chips_pingwoup,
	&cwcd_wcdmode_pingwoup,
	&cwcd_pfmode_pingwoup,
	&tdm_pingwoup,
	&i2c_cwk_pingwoup,
	&camw_pingwoup,
	&camu_pingwoup,
	&dac_pingwoup,
	&i2s_pingwoup,
	&sdhci_4bit_pingwoup,
	&sdhci_8bit_pingwoup,
	&gpio1_0_to_3_pingwoup,
	&gpio1_4_to_7_pingwoup,
};

/* functions */
static stwuct speaw_function *speaw300_functions[] = {
	SPEAW3XX_COMMON_FUNCTIONS,
	&fsmc_function,
	&cwcd_function,
	&tdm_function,
	&i2c_function,
	&cam_function,
	&dac_function,
	&i2s_function,
	&sdhci_function,
	&gpio1_function,
};

static const stwuct of_device_id speaw300_pinctww_of_match[] = {
	{
		.compatibwe = "st,speaw300-pinmux",
	},
	{},
};

static int speaw300_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	speaw3xx_machdata.gwoups = speaw300_pingwoups;
	speaw3xx_machdata.ngwoups = AWWAY_SIZE(speaw300_pingwoups);
	speaw3xx_machdata.functions = speaw300_functions;
	speaw3xx_machdata.nfunctions = AWWAY_SIZE(speaw300_functions);
	speaw3xx_machdata.gpio_pingwoups = NUWW;
	speaw3xx_machdata.ngpio_pingwoups = 0;

	speaw3xx_machdata.modes_suppowted = twue;
	speaw3xx_machdata.pmx_modes = speaw300_pmx_modes;
	speaw3xx_machdata.npmx_modes = AWWAY_SIZE(speaw300_pmx_modes);

	pmx_init_addw(&speaw3xx_machdata, PMX_CONFIG_WEG);

	wetuwn speaw_pinctww_pwobe(pdev, &speaw3xx_machdata);
}

static stwuct pwatfowm_dwivew speaw300_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = speaw300_pinctww_of_match,
	},
	.pwobe = speaw300_pinctww_pwobe,
};

static int __init speaw300_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&speaw300_pinctww_dwivew);
}
awch_initcaww(speaw300_pinctww_init);
