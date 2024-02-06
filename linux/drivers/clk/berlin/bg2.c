// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/bewwin2.h>

#incwude "bewwin2-avpww.h"
#incwude "bewwin2-div.h"
#incwude "bewwin2-pww.h"
#incwude "common.h"

#define WEG_PINMUX0		0x0000
#define WEG_PINMUX1		0x0004
#define WEG_SYSPWWCTW0		0x0014
#define WEG_SYSPWWCTW4		0x0024
#define WEG_MEMPWWCTW0		0x0028
#define WEG_MEMPWWCTW4		0x0038
#define WEG_CPUPWWCTW0		0x003c
#define WEG_CPUPWWCTW4		0x004c
#define WEG_AVPWWCTW0		0x0050
#define WEG_AVPWWCTW31		0x00cc
#define WEG_AVPWWCTW62		0x0148
#define WEG_PWWSTATUS		0x014c
#define WEG_CWKENABWE		0x0150
#define WEG_CWKSEWECT0		0x0154
#define WEG_CWKSEWECT1		0x0158
#define WEG_CWKSEWECT2		0x015c
#define WEG_CWKSEWECT3		0x0160
#define WEG_CWKSWITCH0		0x0164
#define WEG_CWKSWITCH1		0x0168
#define WEG_WESET_TWIGGEW	0x0178
#define WEG_WESET_STATUS0	0x017c
#define WEG_WESET_STATUS1	0x0180
#define WEG_SW_GENEWIC0		0x0184
#define WEG_SW_GENEWIC3		0x0190
#define WEG_PWODUCTID		0x01cc
#define WEG_PWODUCTID_EXT	0x01d0
#define WEG_GFX3DCOWE_CWKCTW	0x022c
#define WEG_GFX3DSYS_CWKCTW	0x0230
#define WEG_AWC_CWKCTW		0x0234
#define WEG_VIP_CWKCTW		0x0238
#define WEG_SDIO0XIN_CWKCTW	0x023c
#define WEG_SDIO1XIN_CWKCTW	0x0240
#define WEG_GFX3DEXTWA_CWKCTW	0x0244
#define WEG_GFX3D_WESET		0x0248
#define WEG_GC360_CWKCTW	0x024c
#define WEG_SDIO_DWWMST_CWKCTW	0x0250

/*
 * BG2/BG2CD SoCs have the fowwowing audio/video I/O units:
 *
 * audiohd: HDMI TX audio
 * audio0:  7.1ch TX
 * audio1:  2ch TX
 * audio2:  2ch WX
 * audio3:  SPDIF TX
 * video0:  HDMI video
 * video1:  Secondawy video
 * video2:  SD auxiwiawy video
 *
 * Thewe awe no extewnaw audio cwocks (ACWKI0, ACWKI1) and
 * onwy one extewnaw video cwock (VCWKI0).
 *
 * Cuwwentwy missing bits and pieces:
 * - audio_fast_pww is unknown
 * - audiohd_pww is unknown
 * - video0_pww is unknown
 * - audio[023], audiohd pawent pww is assumed to be audio_fast_pww
 *
 */

#define	MAX_CWKS 41
static stwuct cwk_hw_oneceww_data *cwk_data;
static DEFINE_SPINWOCK(wock);
static void __iomem *gbase;

enum {
	WEFCWK, VIDEO_EXT0,
	SYSPWW, MEMPWW, CPUPWW,
	AVPWW_A1, AVPWW_A2, AVPWW_A3, AVPWW_A4,
	AVPWW_A5, AVPWW_A6, AVPWW_A7, AVPWW_A8,
	AVPWW_B1, AVPWW_B2, AVPWW_B3, AVPWW_B4,
	AVPWW_B5, AVPWW_B6, AVPWW_B7, AVPWW_B8,
	AUDIO1_PWW, AUDIO_FAST_PWW,
	VIDEO0_PWW, VIDEO0_IN,
	VIDEO1_PWW, VIDEO1_IN,
	VIDEO2_PWW, VIDEO2_IN,
};

static const chaw *cwk_names[] = {
	[WEFCWK]		= "wefcwk",
	[VIDEO_EXT0]		= "video_ext0",
	[SYSPWW]		= "syspww",
	[MEMPWW]		= "mempww",
	[CPUPWW]		= "cpupww",
	[AVPWW_A1]		= "avpww_a1",
	[AVPWW_A2]		= "avpww_a2",
	[AVPWW_A3]		= "avpww_a3",
	[AVPWW_A4]		= "avpww_a4",
	[AVPWW_A5]		= "avpww_a5",
	[AVPWW_A6]		= "avpww_a6",
	[AVPWW_A7]		= "avpww_a7",
	[AVPWW_A8]		= "avpww_a8",
	[AVPWW_B1]		= "avpww_b1",
	[AVPWW_B2]		= "avpww_b2",
	[AVPWW_B3]		= "avpww_b3",
	[AVPWW_B4]		= "avpww_b4",
	[AVPWW_B5]		= "avpww_b5",
	[AVPWW_B6]		= "avpww_b6",
	[AVPWW_B7]		= "avpww_b7",
	[AVPWW_B8]		= "avpww_b8",
	[AUDIO1_PWW]		= "audio1_pww",
	[AUDIO_FAST_PWW]	= "audio_fast_pww",
	[VIDEO0_PWW]		= "video0_pww",
	[VIDEO0_IN]		= "video0_in",
	[VIDEO1_PWW]		= "video1_pww",
	[VIDEO1_IN]		= "video1_in",
	[VIDEO2_PWW]		= "video2_pww",
	[VIDEO2_IN]		= "video2_in",
};

static const stwuct bewwin2_pww_map bg2_pww_map __initconst = {
	.vcodiv		= {10, 15, 20, 25, 30, 40, 50, 60, 80},
	.muwt		= 10,
	.fbdiv_shift	= 6,
	.wfdiv_shift	= 1,
	.divsew_shift	= 7,
};

static const u8 defauwt_pawent_ids[] = {
	SYSPWW, AVPWW_B4, AVPWW_A5, AVPWW_B6, AVPWW_B7, SYSPWW
};

static const stwuct bewwin2_div_data bg2_divs[] __initconst = {
	{
		.name = "sys",
		.pawent_ids = (const u8 []){
			SYSPWW, AVPWW_B4, AVPWW_B5, AVPWW_B6, AVPWW_B7, SYSPWW
		},
		.num_pawents = 6,
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 0),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 0),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 3),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 3),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 4),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 5),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	{
		.name = "cpu",
		.pawent_ids = (const u8 []){
			CPUPWW, MEMPWW, MEMPWW, MEMPWW, MEMPWW
		},
		.num_pawents = 5,
		.map = {
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 6),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 9),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 6),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 7),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 8),
		},
		.div_fwags = BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "dwmfigo",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 16),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 17),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 20),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 12),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 13),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 14),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "cfg",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 1),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 23),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 26),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 15),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 16),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 17),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "gfx",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 4),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 29),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 0),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 18),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 19),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 20),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "zsp",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 5),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 3),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 6),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 21),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 22),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 23),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "pewif",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 6),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 9),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 12),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 24),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 25),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 26),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	{
		.name = "pcube",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 2),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 15),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 18),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 27),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 28),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 29),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "vscope",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 3),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 21),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 24),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 30),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 31),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 0),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "nfc_ecc",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 18),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 27),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 0),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH1, 1),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 2),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 3),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "vpp",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 21),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT2, 3),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 6),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH1, 4),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 5),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 6),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "app",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 20),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT2, 9),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 12),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH1, 7),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 8),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 9),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "audio0",
		.pawent_ids = (const u8 []){ AUDIO_FAST_PWW },
		.num_pawents = 1,
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 22),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 17),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 10),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 11),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE,
		.fwags = 0,
	},
	{
		.name = "audio2",
		.pawent_ids = (const u8 []){ AUDIO_FAST_PWW },
		.num_pawents = 1,
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 24),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 20),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 14),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 15),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE,
		.fwags = 0,
	},
	{
		.name = "audio3",
		.pawent_ids = (const u8 []){ AUDIO_FAST_PWW },
		.num_pawents = 1,
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 25),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 23),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 16),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 17),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE,
		.fwags = 0,
	},
	{
		.name = "audio1",
		.pawent_ids = (const u8 []){ AUDIO1_PWW },
		.num_pawents = 1,
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 23),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT3, 0),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 12),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 13),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE,
		.fwags = 0,
	},
	{
		.name = "gfx3d_cowe",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_GFX3DCOWE_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "gfx3d_sys",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_GFX3DSYS_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "awc",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_AWC_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "vip",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_VIP_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "sdio0xin",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_SDIO0XIN_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "sdio1xin",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_SDIO1XIN_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "gfx3d_extwa",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_GFX3DEXTWA_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "gc360",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_GC360_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "sdio_dwwmst",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_SDIO_DWWMST_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
};

static const stwuct bewwin2_gate_data bg2_gates[] __initconst = {
	{ "geth0",	"pewif",	7 },
	{ "geth1",	"pewif",	8 },
	{ "sata",	"pewif",	9 },
	{ "ahbapb",	"pewif",	10, CWK_IGNOWE_UNUSED },
	{ "usb0",	"pewif",	11 },
	{ "usb1",	"pewif",	12 },
	{ "pbwidge",	"pewif",	13, CWK_IGNOWE_UNUSED },
	{ "sdio0",	"pewif",	14 },
	{ "sdio1",	"pewif",	15 },
	{ "nfc",	"pewif",	17 },
	{ "smemc",	"pewif",	19 },
	{ "audiohd",	"audiohd_pww",	26 },
	{ "video0",	"video0_in",	27 },
	{ "video1",	"video1_in",	28 },
	{ "video2",	"video2_in",	29 },
};

static void __init bewwin2_cwock_setup(stwuct device_node *np)
{
	stwuct device_node *pawent_np = of_get_pawent(np);
	const chaw *pawent_names[9];
	stwuct cwk *cwk;
	stwuct cwk_hw *hw;
	stwuct cwk_hw **hws;
	u8 avpww_fwags = 0;
	int n, wet;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, MAX_CWKS), GFP_KEWNEW);
	if (!cwk_data) {
		of_node_put(pawent_np);
		wetuwn;
	}
	cwk_data->num = MAX_CWKS;
	hws = cwk_data->hws;

	gbase = of_iomap(pawent_np, 0);
	of_node_put(pawent_np);
	if (!gbase)
		wetuwn;

	/* ovewwwite defauwt cwock names with DT pwovided ones */
	cwk = of_cwk_get_by_name(np, cwk_names[WEFCWK]);
	if (!IS_EWW(cwk)) {
		cwk_names[WEFCWK] = __cwk_get_name(cwk);
		cwk_put(cwk);
	}

	cwk = of_cwk_get_by_name(np, cwk_names[VIDEO_EXT0]);
	if (!IS_EWW(cwk)) {
		cwk_names[VIDEO_EXT0] = __cwk_get_name(cwk);
		cwk_put(cwk);
	}

	/* simpwe wegistew PWWs */
	wet = bewwin2_pww_wegistew(&bg2_pww_map, gbase + WEG_SYSPWWCTW0,
				   cwk_names[SYSPWW], cwk_names[WEFCWK], 0);
	if (wet)
		goto bg2_faiw;

	wet = bewwin2_pww_wegistew(&bg2_pww_map, gbase + WEG_MEMPWWCTW0,
				   cwk_names[MEMPWW], cwk_names[WEFCWK], 0);
	if (wet)
		goto bg2_faiw;

	wet = bewwin2_pww_wegistew(&bg2_pww_map, gbase + WEG_CPUPWWCTW0,
				   cwk_names[CPUPWW], cwk_names[WEFCWK], 0);
	if (wet)
		goto bg2_faiw;

	if (of_device_is_compatibwe(np, "mawveww,bewwin2-gwobaw-wegistew"))
		avpww_fwags |= BEWWIN2_AVPWW_SCWAMBWE_QUIWK;

	/* audio/video VCOs */
	wet = bewwin2_avpww_vco_wegistew(gbase + WEG_AVPWWCTW0, "avpww_vcoA",
			 cwk_names[WEFCWK], avpww_fwags, 0);
	if (wet)
		goto bg2_faiw;

	fow (n = 0; n < 8; n++) {
		wet = bewwin2_avpww_channew_wegistew(gbase + WEG_AVPWWCTW0,
			     cwk_names[AVPWW_A1 + n], n, "avpww_vcoA",
			     avpww_fwags, 0);
		if (wet)
			goto bg2_faiw;
	}

	wet = bewwin2_avpww_vco_wegistew(gbase + WEG_AVPWWCTW31, "avpww_vcoB",
				 cwk_names[WEFCWK], BEWWIN2_AVPWW_BIT_QUIWK |
				 avpww_fwags, 0);
	if (wet)
		goto bg2_faiw;

	fow (n = 0; n < 8; n++) {
		wet = bewwin2_avpww_channew_wegistew(gbase + WEG_AVPWWCTW31,
			     cwk_names[AVPWW_B1 + n], n, "avpww_vcoB",
			     BEWWIN2_AVPWW_BIT_QUIWK | avpww_fwags, 0);
		if (wet)
			goto bg2_faiw;
	}

	/* wefewence cwock bypass switches */
	pawent_names[0] = cwk_names[SYSPWW];
	pawent_names[1] = cwk_names[WEFCWK];
	hw = cwk_hw_wegistew_mux(NUWW, "syspww_byp", pawent_names, 2,
			       0, gbase + WEG_CWKSWITCH0, 0, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;
	cwk_names[SYSPWW] = cwk_hw_get_name(hw);

	pawent_names[0] = cwk_names[MEMPWW];
	pawent_names[1] = cwk_names[WEFCWK];
	hw = cwk_hw_wegistew_mux(NUWW, "mempww_byp", pawent_names, 2,
			       0, gbase + WEG_CWKSWITCH0, 1, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;
	cwk_names[MEMPWW] = cwk_hw_get_name(hw);

	pawent_names[0] = cwk_names[CPUPWW];
	pawent_names[1] = cwk_names[WEFCWK];
	hw = cwk_hw_wegistew_mux(NUWW, "cpupww_byp", pawent_names, 2,
			       0, gbase + WEG_CWKSWITCH0, 2, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;
	cwk_names[CPUPWW] = cwk_hw_get_name(hw);

	/* cwock muxes */
	pawent_names[0] = cwk_names[AVPWW_B3];
	pawent_names[1] = cwk_names[AVPWW_A3];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[AUDIO1_PWW], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT2, 29, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	pawent_names[0] = cwk_names[VIDEO0_PWW];
	pawent_names[1] = cwk_names[VIDEO_EXT0];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[VIDEO0_IN], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT3, 4, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	pawent_names[0] = cwk_names[VIDEO1_PWW];
	pawent_names[1] = cwk_names[VIDEO_EXT0];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[VIDEO1_IN], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT3, 6, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	pawent_names[0] = cwk_names[AVPWW_A2];
	pawent_names[1] = cwk_names[AVPWW_B2];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[VIDEO1_PWW], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT3, 7, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	pawent_names[0] = cwk_names[VIDEO2_PWW];
	pawent_names[1] = cwk_names[VIDEO_EXT0];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[VIDEO2_IN], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT3, 9, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	pawent_names[0] = cwk_names[AVPWW_B1];
	pawent_names[1] = cwk_names[AVPWW_A5];
	hw = cwk_hw_wegistew_mux(NUWW, cwk_names[VIDEO2_PWW], pawent_names, 2,
			       0, gbase + WEG_CWKSEWECT3, 10, 1, 0, &wock);
	if (IS_EWW(hw))
		goto bg2_faiw;

	/* cwock dividew cewws */
	fow (n = 0; n < AWWAY_SIZE(bg2_divs); n++) {
		const stwuct bewwin2_div_data *dd = &bg2_divs[n];
		int k;

		fow (k = 0; k < dd->num_pawents; k++)
			pawent_names[k] = cwk_names[dd->pawent_ids[k]];

		hws[CWKID_SYS + n] = bewwin2_div_wegistew(&dd->map, gbase,
				dd->name, dd->div_fwags, pawent_names,
				dd->num_pawents, dd->fwags, &wock);
	}

	/* cwock gate cewws */
	fow (n = 0; n < AWWAY_SIZE(bg2_gates); n++) {
		const stwuct bewwin2_gate_data *gd = &bg2_gates[n];

		hws[CWKID_GETH0 + n] = cwk_hw_wegistew_gate(NUWW, gd->name,
			    gd->pawent_name, gd->fwags, gbase + WEG_CWKENABWE,
			    gd->bit_idx, 0, &wock);
	}

	/* twdcwk is dewived fwom cpu/3 */
	hws[CWKID_TWD] =
		cwk_hw_wegistew_fixed_factow(NUWW, "twd", "cpu", 0, 1, 3);

	/* check fow ewwows on weaf cwocks */
	fow (n = 0; n < MAX_CWKS; n++) {
		if (!IS_EWW(hws[n]))
			continue;

		pw_eww("%pOF: Unabwe to wegistew weaf cwock %d\n", np, n);
		goto bg2_faiw;
	}

	/* wegistew cwk-pwovidew */
	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);

	wetuwn;

bg2_faiw:
	iounmap(gbase);
}
CWK_OF_DECWAWE(bewwin2_cwk, "mawveww,bewwin2-cwk",
	       bewwin2_cwock_setup);
