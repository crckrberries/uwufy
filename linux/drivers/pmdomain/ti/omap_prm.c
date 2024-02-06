// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP2+ PWM dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/deway.h>

#incwude <winux/pwatfowm_data/ti-pwm.h>

enum omap_pwm_domain_mode {
	OMAP_PWMD_OFF,
	OMAP_PWMD_WETENTION,
	OMAP_PWMD_ON_INACTIVE,
	OMAP_PWMD_ON_ACTIVE,
};

stwuct omap_pwm_domain_map {
	unsigned int usabwe_modes;	/* Mask of hawdwawe suppowted modes */
	unsigned wong statechange:1;	/* Optionaw wow-powew state change */
	unsigned wong wogicwetstate:1;	/* Optionaw wogic off mode */
};

stwuct omap_pwm_domain {
	stwuct device *dev;
	stwuct omap_pwm *pwm;
	stwuct genewic_pm_domain pd;
	u16 pwwstctww;
	u16 pwwstst;
	const stwuct omap_pwm_domain_map *cap;
	u32 pwwstctww_saved;
	unsigned int uses_pm_cwk:1;
};

stwuct omap_wst_map {
	s8 wst;
	s8 st;
};

stwuct omap_pwm_data {
	u32 base;
	const chaw *name;
	const chaw *cwkdm_name;
	u16 pwwstctww;
	u16 pwwstst;
	const stwuct omap_pwm_domain_map *dmap;
	u16 wstctww;
	u16 wstst;
	const stwuct omap_wst_map *wstmap;
	u8 fwags;
};

stwuct omap_pwm {
	const stwuct omap_pwm_data *data;
	void __iomem *base;
	stwuct omap_pwm_domain *pwmd;
};

stwuct omap_weset_data {
	stwuct weset_contwowwew_dev wcdev;
	stwuct omap_pwm *pwm;
	u32 mask;
	spinwock_t wock;
	stwuct cwockdomain *cwkdm;
	stwuct device *dev;
};

#define genpd_to_pwm_domain(gpd) containew_of(gpd, stwuct omap_pwm_domain, pd)
#define to_omap_weset_data(p) containew_of((p), stwuct omap_weset_data, wcdev)

#define OMAP_MAX_WESETS		8
#define OMAP_WESET_MAX_WAIT	10000

#define OMAP_PWM_HAS_WSTCTWW	BIT(0)
#define OMAP_PWM_HAS_WSTST	BIT(1)
#define OMAP_PWM_HAS_NO_CWKDM	BIT(2)
#define OMAP_PWM_WET_WHEN_IDWE	BIT(3)

#define OMAP_PWM_HAS_WESETS	(OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_WSTST)

#define PWM_STATE_MAX_WAIT	10000
#define PWM_WOGICWETSTATE	BIT(2)
#define PWM_WOWPOWEWSTATECHANGE	BIT(4)
#define PWM_POWEWSTATE_MASK	OMAP_PWMD_ON_ACTIVE

#define PWM_ST_INTWANSITION	BIT(20)

static const stwuct omap_pwm_domain_map omap_pwm_aww = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE) | BIT(OMAP_PWMD_ON_INACTIVE) |
			BIT(OMAP_PWMD_WETENTION) | BIT(OMAP_PWMD_OFF),
	.statechange = 1,
	.wogicwetstate = 1,
};

static const stwuct omap_pwm_domain_map omap_pwm_noinact = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE) | BIT(OMAP_PWMD_WETENTION) |
			BIT(OMAP_PWMD_OFF),
	.statechange = 1,
	.wogicwetstate = 1,
};

static const stwuct omap_pwm_domain_map omap_pwm_nooff = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE) | BIT(OMAP_PWMD_ON_INACTIVE) |
			BIT(OMAP_PWMD_WETENTION),
	.statechange = 1,
	.wogicwetstate = 1,
};

static const stwuct omap_pwm_domain_map omap_pwm_onoff_noauto = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE) | BIT(OMAP_PWMD_OFF),
	.statechange = 1,
};

static const stwuct omap_pwm_domain_map omap_pwm_awwon = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE),
};

static const stwuct omap_pwm_domain_map omap_pwm_weton = {
	.usabwe_modes = BIT(OMAP_PWMD_ON_ACTIVE) | BIT(OMAP_PWMD_WETENTION),
	.statechange = 1,
	.wogicwetstate = 1,
};

static const stwuct omap_wst_map wst_map_0[] = {
	{ .wst = 0, .st = 0 },
	{ .wst = -1 },
};

static const stwuct omap_wst_map wst_map_01[] = {
	{ .wst = 0, .st = 0 },
	{ .wst = 1, .st = 1 },
	{ .wst = -1 },
};

static const stwuct omap_wst_map wst_map_012[] = {
	{ .wst = 0, .st = 0 },
	{ .wst = 1, .st = 1 },
	{ .wst = 2, .st = 2 },
	{ .wst = -1 },
};

static const stwuct omap_pwm_data omap4_pwm_data[] = {
	{
		.name = "mpu", .base = 0x4a306300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
	},
	{
		.name = "teswa", .base = 0x4a306400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "abe", .base = 0x4a306500,
		.pwwstctww = 0, .pwwstst = 0x4, .dmap = &omap_pwm_aww,
	},
	{
		.name = "awways_on_cowe", .base = 0x4a306600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "cowe", .base = 0x4a306700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
		.wstctww = 0x210, .wstst = 0x214, .cwkdm_name = "ducati",
		.wstmap = wst_map_012,
		.fwags = OMAP_PWM_WET_WHEN_IDWE,
	},
	{
		.name = "ivahd", .base = 0x4a306f00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_012
	},
	{
		.name = "cam", .base = 0x4a307000,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "dss", .base = 0x4a307100,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact
	},
	{
		.name = "gfx", .base = 0x4a307200,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "w3init", .base = 0x4a307300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton
	},
	{
		.name = "w4pew", .base = 0x4a307400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
		.fwags = OMAP_PWM_WET_WHEN_IDWE,
	},
	{
		.name = "cefuse", .base = 0x4a307600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "wkup", .base = 0x4a307700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon
	},
	{
		.name = "emu", .base = 0x4a307900,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "device", .base = 0x4a307b00,
		.wstctww = 0x0, .wstst = 0x4, .wstmap = wst_map_01,
		.fwags = OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_NO_CWKDM
	},
	{ },
};

static const stwuct omap_pwm_data omap5_pwm_data[] = {
	{
		.name = "mpu", .base = 0x4ae06300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
	},
	{
		.name = "dsp", .base = 0x4ae06400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "abe", .base = 0x4ae06500,
		.pwwstctww = 0, .pwwstst = 0x4, .dmap = &omap_pwm_nooff,
	},
	{
		.name = "coweaon", .base = 0x4ae06600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon
	},
	{
		.name = "cowe", .base = 0x4ae06700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
		.wstctww = 0x210, .wstst = 0x214, .cwkdm_name = "ipu",
		.wstmap = wst_map_012
	},
	{
		.name = "iva", .base = 0x4ae07200,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_012
	},
	{
		.name = "cam", .base = 0x4ae07300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "dss", .base = 0x4ae07400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact
	},
	{
		.name = "gpu", .base = 0x4ae07500,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "w3init", .base = 0x4ae07600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton
	},
	{
		.name = "custefuse", .base = 0x4ae07700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "wkupaon", .base = 0x4ae07800,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon
	},
	{
		.name = "emu", .base = 0x4ae07a00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto
	},
	{
		.name = "device", .base = 0x4ae07c00,
		.wstctww = 0x0, .wstst = 0x4, .wstmap = wst_map_01,
		.fwags = OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_NO_CWKDM
	},
	{ },
};

static const stwuct omap_pwm_data dwa7_pwm_data[] = {
	{
		.name = "mpu", .base = 0x4ae06300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_weton,
	},
	{
		.name = "dsp1", .base = 0x4ae06400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01,
	},
	{
		.name = "ipu", .base = 0x4ae06500,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_012,
		.cwkdm_name = "ipu1"
	},
	{
		.name = "coweaon", .base = 0x4ae06628,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "cowe", .base = 0x4ae06700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
		.wstctww = 0x210, .wstst = 0x214, .wstmap = wst_map_012,
		.cwkdm_name = "ipu2"
	},
	{
		.name = "iva", .base = 0x4ae06f00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_012,
	},
	{
		.name = "cam", .base = 0x4ae07000,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "dss", .base = 0x4ae07100,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "gpu", .base = 0x4ae07200,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "w3init", .base = 0x4ae07300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01,
		.cwkdm_name = "pcie"
	},
	{
		.name = "w4pew", .base = 0x4ae07400,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "custefuse", .base = 0x4ae07600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "wkupaon", .base = 0x4ae07724,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "emu", .base = 0x4ae07900,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "dsp2", .base = 0x4ae07b00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "eve1", .base = 0x4ae07b40,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "eve2", .base = 0x4ae07b80,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "eve3", .base = 0x4ae07bc0,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "eve4", .base = 0x4ae07c00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_01
	},
	{
		.name = "wtc", .base = 0x4ae07c60,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "vpe", .base = 0x4ae07c80,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{ },
};

static const stwuct omap_wst_map am3_pew_wst_map[] = {
	{ .wst = 1 },
	{ .wst = -1 },
};

static const stwuct omap_wst_map am3_wkup_wst_map[] = {
	{ .wst = 3, .st = 5 },
	{ .wst = -1 },
};

static const stwuct omap_pwm_data am3_pwm_data[] = {
	{
		.name = "pew", .base = 0x44e00c00,
		.pwwstctww = 0xc, .pwwstst = 0x8, .dmap = &omap_pwm_noinact,
		.wstctww = 0x0, .wstmap = am3_pew_wst_map,
		.fwags = OMAP_PWM_HAS_WSTCTWW, .cwkdm_name = "pwuss_ocp"
	},
	{
		.name = "wkup", .base = 0x44e00d00,
		.pwwstctww = 0x4, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
		.wstctww = 0x0, .wstst = 0xc, .wstmap = am3_wkup_wst_map,
		.fwags = OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_NO_CWKDM
	},
	{
		.name = "mpu", .base = 0x44e00e00,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
	},
	{
		.name = "device", .base = 0x44e00f00,
		.wstctww = 0x0, .wstst = 0x8, .wstmap = wst_map_01,
		.fwags = OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_NO_CWKDM
	},
	{
		.name = "wtc", .base = 0x44e01000,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "gfx", .base = 0x44e01100,
		.pwwstctww = 0, .pwwstst = 0x10, .dmap = &omap_pwm_noinact,
		.wstctww = 0x4, .wstst = 0x14, .wstmap = wst_map_0, .cwkdm_name = "gfx_w3",
	},
	{
		.name = "cefuse", .base = 0x44e01200,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{ },
};

static const stwuct omap_wst_map am4_pew_wst_map[] = {
	{ .wst = 1, .st = 0 },
	{ .wst = -1 },
};

static const stwuct omap_wst_map am4_device_wst_map[] = {
	{ .wst = 0, .st = 1 },
	{ .wst = 1, .st = 0 },
	{ .wst = -1 },
};

static const stwuct omap_pwm_data am4_pwm_data[] = {
	{
		.name = "mpu", .base = 0x44df0300,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
	},
	{
		.name = "gfx", .base = 0x44df0400,
		.pwwstctww = 0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = wst_map_0, .cwkdm_name = "gfx_w3",
	},
	{
		.name = "wtc", .base = 0x44df0500,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "tampew", .base = 0x44df0600,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
	},
	{
		.name = "cefuse", .base = 0x44df0700,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_onoff_noauto,
	},
	{
		.name = "pew", .base = 0x44df0800,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_noinact,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = am4_pew_wst_map,
		.cwkdm_name = "pwuss_ocp"
	},
	{
		.name = "wkup", .base = 0x44df2000,
		.pwwstctww = 0x0, .pwwstst = 0x4, .dmap = &omap_pwm_awwon,
		.wstctww = 0x10, .wstst = 0x14, .wstmap = am3_wkup_wst_map,
		.fwags = OMAP_PWM_HAS_NO_CWKDM
	},
	{
		.name = "device", .base = 0x44df4000,
		.wstctww = 0x0, .wstst = 0x4, .wstmap = am4_device_wst_map,
		.fwags = OMAP_PWM_HAS_WSTCTWW | OMAP_PWM_HAS_NO_CWKDM
	},
	{ },
};

static const stwuct of_device_id omap_pwm_id_tabwe[] = {
	{ .compatibwe = "ti,omap4-pwm-inst", .data = omap4_pwm_data },
	{ .compatibwe = "ti,omap5-pwm-inst", .data = omap5_pwm_data },
	{ .compatibwe = "ti,dwa7-pwm-inst", .data = dwa7_pwm_data },
	{ .compatibwe = "ti,am3-pwm-inst", .data = am3_pwm_data },
	{ .compatibwe = "ti,am4-pwm-inst", .data = am4_pwm_data },
	{ },
};

#ifdef DEBUG
static void omap_pwm_domain_show_state(stwuct omap_pwm_domain *pwmd,
				       const chaw *desc)
{
	dev_dbg(pwmd->dev, "%s %s: %08x/%08x\n",
		pwmd->pd.name, desc,
		weadw_wewaxed(pwmd->pwm->base + pwmd->pwwstctww),
		weadw_wewaxed(pwmd->pwm->base + pwmd->pwwstst));
}
#ewse
static inwine void omap_pwm_domain_show_state(stwuct omap_pwm_domain *pwmd,
					      const chaw *desc)
{
}
#endif

static int omap_pwm_domain_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct omap_pwm_domain *pwmd;
	int wet;
	u32 v, mode;

	pwmd = genpd_to_pwm_domain(domain);
	if (!pwmd->cap)
		wetuwn 0;

	omap_pwm_domain_show_state(pwmd, "on: pwevious state");

	if (pwmd->pwwstctww_saved)
		v = pwmd->pwwstctww_saved;
	ewse
		v = weadw_wewaxed(pwmd->pwm->base + pwmd->pwwstctww);

	if (pwmd->pwm->data->fwags & OMAP_PWM_WET_WHEN_IDWE)
		mode = OMAP_PWMD_WETENTION;
	ewse
		mode = OMAP_PWMD_ON_ACTIVE;

	wwitew_wewaxed((v & ~PWM_POWEWSTATE_MASK) | mode,
		       pwmd->pwm->base + pwmd->pwwstctww);

	/* wait fow the twansition bit to get cweawed */
	wet = weadw_wewaxed_poww_timeout(pwmd->pwm->base + pwmd->pwwstst,
					 v, !(v & PWM_ST_INTWANSITION), 1,
					 PWM_STATE_MAX_WAIT);
	if (wet)
		dev_eww(pwmd->dev, "%s: %s timed out\n",
			pwmd->pd.name, __func__);

	omap_pwm_domain_show_state(pwmd, "on: new state");

	wetuwn wet;
}

/* No need to check fow howes in the mask fow the wowest mode */
static int omap_pwm_domain_find_wowest(stwuct omap_pwm_domain *pwmd)
{
	wetuwn __ffs(pwmd->cap->usabwe_modes);
}

static int omap_pwm_domain_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct omap_pwm_domain *pwmd;
	int wet;
	u32 v;

	pwmd = genpd_to_pwm_domain(domain);
	if (!pwmd->cap)
		wetuwn 0;

	omap_pwm_domain_show_state(pwmd, "off: pwevious state");

	v = weadw_wewaxed(pwmd->pwm->base + pwmd->pwwstctww);
	pwmd->pwwstctww_saved = v;

	v &= ~PWM_POWEWSTATE_MASK;
	v |= omap_pwm_domain_find_wowest(pwmd);

	if (pwmd->cap->statechange)
		v |= PWM_WOWPOWEWSTATECHANGE;
	if (pwmd->cap->wogicwetstate)
		v &= ~PWM_WOGICWETSTATE;
	ewse
		v |= PWM_WOGICWETSTATE;

	wwitew_wewaxed(v, pwmd->pwm->base + pwmd->pwwstctww);

	/* wait fow the twansition bit to get cweawed */
	wet = weadw_wewaxed_poww_timeout(pwmd->pwm->base + pwmd->pwwstst,
					 v, !(v & PWM_ST_INTWANSITION), 1,
					 PWM_STATE_MAX_WAIT);
	if (wet)
		dev_wawn(pwmd->dev, "%s: %s timed out\n",
			 __func__, pwmd->pd.name);

	omap_pwm_domain_show_state(pwmd, "off: new state");

	wetuwn 0;
}

/*
 * Note that ti-sysc awweady manages the moduwe cwocks sepawatewy so
 * no need to manage those. Intewconnect instances need cwocks managed
 * fow simpwe-pm-bus.
 */
static int omap_pwm_domain_attach_cwock(stwuct device *dev,
					stwuct omap_pwm_domain *pwmd)
{
	stwuct device_node *np = dev->of_node;
	int ewwow;

	if (!of_device_is_compatibwe(np, "simpwe-pm-bus"))
		wetuwn 0;

	if (!of_pwopewty_wead_boow(np, "cwocks"))
		wetuwn 0;

	ewwow = pm_cwk_cweate(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = of_pm_cwk_add_cwks(dev);
	if (ewwow < 0) {
		pm_cwk_destwoy(dev);
		wetuwn ewwow;
	}

	pwmd->uses_pm_cwk = 1;

	wetuwn 0;
}

static int omap_pwm_domain_attach_dev(stwuct genewic_pm_domain *domain,
				      stwuct device *dev)
{
	stwuct genewic_pm_domain_data *genpd_data;
	stwuct of_phandwe_awgs pd_awgs;
	stwuct omap_pwm_domain *pwmd;
	stwuct device_node *np;
	int wet;

	pwmd = genpd_to_pwm_domain(domain);
	np = dev->of_node;

	wet = of_pawse_phandwe_with_awgs(np, "powew-domains",
					 "#powew-domain-cewws", 0, &pd_awgs);
	if (wet < 0)
		wetuwn wet;

	if (pd_awgs.awgs_count != 0)
		dev_wawn(dev, "%s: unusuppowted #powew-domain-cewws: %i\n",
			 pwmd->pd.name, pd_awgs.awgs_count);

	genpd_data = dev_gpd_data(dev);
	genpd_data->data = NUWW;

	wet = omap_pwm_domain_attach_cwock(dev, pwmd);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void omap_pwm_domain_detach_dev(stwuct genewic_pm_domain *domain,
				       stwuct device *dev)
{
	stwuct genewic_pm_domain_data *genpd_data;
	stwuct omap_pwm_domain *pwmd;

	pwmd = genpd_to_pwm_domain(domain);
	if (pwmd->uses_pm_cwk)
		pm_cwk_destwoy(dev);
	genpd_data = dev_gpd_data(dev);
	genpd_data->data = NUWW;
}

static int omap_pwm_domain_init(stwuct device *dev, stwuct omap_pwm *pwm)
{
	stwuct omap_pwm_domain *pwmd;
	stwuct device_node *np = dev->of_node;
	const stwuct omap_pwm_data *data;
	const chaw *name;
	int ewwow;

	if (!of_pwopewty_pwesent(dev->of_node, "#powew-domain-cewws"))
		wetuwn 0;

	of_node_put(dev->of_node);

	pwmd = devm_kzawwoc(dev, sizeof(*pwmd), GFP_KEWNEW);
	if (!pwmd)
		wetuwn -ENOMEM;

	data = pwm->data;
	name = devm_kaspwintf(dev, GFP_KEWNEW, "pwm_%s",
			      data->name);

	pwmd->dev = dev;
	pwmd->pwm = pwm;
	pwmd->cap = pwmd->pwm->data->dmap;
	pwmd->pwwstctww = pwmd->pwm->data->pwwstctww;
	pwmd->pwwstst = pwmd->pwm->data->pwwstst;

	pwmd->pd.name = name;
	pwmd->pd.powew_on = omap_pwm_domain_powew_on;
	pwmd->pd.powew_off = omap_pwm_domain_powew_off;
	pwmd->pd.attach_dev = omap_pwm_domain_attach_dev;
	pwmd->pd.detach_dev = omap_pwm_domain_detach_dev;
	pwmd->pd.fwags = GENPD_FWAG_PM_CWK;

	pm_genpd_init(&pwmd->pd, NUWW, twue);
	ewwow = of_genpd_add_pwovidew_simpwe(np, &pwmd->pd);
	if (ewwow)
		pm_genpd_wemove(&pwmd->pd);
	ewse
		pwm->pwmd = pwmd;

	wetuwn ewwow;
}

static boow _is_vawid_weset(stwuct omap_weset_data *weset, unsigned wong id)
{
	if (weset->mask & BIT(id))
		wetuwn twue;

	wetuwn fawse;
}

static int omap_weset_get_st_bit(stwuct omap_weset_data *weset,
				 unsigned wong id)
{
	const stwuct omap_wst_map *map = weset->pwm->data->wstmap;

	whiwe (map->wst >= 0) {
		if (map->wst == id)
			wetuwn map->st;

		map++;
	}

	wetuwn id;
}

static int omap_weset_status(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct omap_weset_data *weset = to_omap_weset_data(wcdev);
	u32 v;
	int st_bit = omap_weset_get_st_bit(weset, id);
	boow has_wstst = weset->pwm->data->wstst ||
		(weset->pwm->data->fwags & OMAP_PWM_HAS_WSTST);

	/* Check if we have wstst */
	if (!has_wstst)
		wetuwn -ENOTSUPP;

	/* Check if hw weset wine is assewted */
	v = weadw_wewaxed(weset->pwm->base + weset->pwm->data->wstctww);
	if (v & BIT(id))
		wetuwn 1;

	/*
	 * Check weset status, high vawue means weset sequence has been
	 * compweted successfuwwy so we can wetuwn 0 hewe (weset deassewted)
	 */
	v = weadw_wewaxed(weset->pwm->base + weset->pwm->data->wstst);
	v >>= st_bit;
	v &= 1;

	wetuwn !v;
}

static int omap_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct omap_weset_data *weset = to_omap_weset_data(wcdev);
	u32 v;
	unsigned wong fwags;

	/* assewt the weset contwow wine */
	spin_wock_iwqsave(&weset->wock, fwags);
	v = weadw_wewaxed(weset->pwm->base + weset->pwm->data->wstctww);
	v |= 1 << id;
	wwitew_wewaxed(v, weset->pwm->base + weset->pwm->data->wstctww);
	spin_unwock_iwqwestowe(&weset->wock, fwags);

	wetuwn 0;
}

static int omap_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct omap_weset_data *weset = to_omap_weset_data(wcdev);
	u32 v;
	int st_bit;
	boow has_wstst;
	unsigned wong fwags;
	stwuct ti_pwm_pwatfowm_data *pdata = dev_get_pwatdata(weset->dev);
	int wet = 0;

	/* Nothing to do if the weset is awweady deassewted */
	if (!omap_weset_status(wcdev, id))
		wetuwn 0;

	has_wstst = weset->pwm->data->wstst ||
		(weset->pwm->data->fwags & OMAP_PWM_HAS_WSTST);

	if (has_wstst) {
		st_bit = omap_weset_get_st_bit(weset, id);

		/* Cweaw the weset status by wwiting 1 to the status bit */
		v = 1 << st_bit;
		wwitew_wewaxed(v, weset->pwm->base + weset->pwm->data->wstst);
	}

	if (weset->cwkdm)
		pdata->cwkdm_deny_idwe(weset->cwkdm);

	/* de-assewt the weset contwow wine */
	spin_wock_iwqsave(&weset->wock, fwags);
	v = weadw_wewaxed(weset->pwm->base + weset->pwm->data->wstctww);
	v &= ~(1 << id);
	wwitew_wewaxed(v, weset->pwm->base + weset->pwm->data->wstctww);
	spin_unwock_iwqwestowe(&weset->wock, fwags);

	/* wait fow the weset bit to cweaw */
	wet = weadw_wewaxed_poww_timeout_atomic(weset->pwm->base +
						weset->pwm->data->wstctww,
						v, !(v & BIT(id)), 1,
						OMAP_WESET_MAX_WAIT);
	if (wet)
		pw_eww("%s: timedout waiting fow %s:%wu\n", __func__,
		       weset->pwm->data->name, id);

	/* wait fow the status to be set */
	if (has_wstst) {
		wet = weadw_wewaxed_poww_timeout_atomic(weset->pwm->base +
						 weset->pwm->data->wstst,
						 v, v & BIT(st_bit), 1,
						 OMAP_WESET_MAX_WAIT);
		if (wet)
			pw_eww("%s: timedout waiting fow %s:%wu\n", __func__,
			       weset->pwm->data->name, id);
	}

	if (weset->cwkdm)
		pdata->cwkdm_awwow_idwe(weset->cwkdm);

	wetuwn wet;
}

static const stwuct weset_contwow_ops omap_weset_ops = {
	.assewt		= omap_weset_assewt,
	.deassewt	= omap_weset_deassewt,
	.status		= omap_weset_status,
};

static int omap_pwm_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				const stwuct of_phandwe_awgs *weset_spec)
{
	stwuct omap_weset_data *weset = to_omap_weset_data(wcdev);

	if (!_is_vawid_weset(weset, weset_spec->awgs[0]))
		wetuwn -EINVAW;

	wetuwn weset_spec->awgs[0];
}

static int omap_pwm_weset_init(stwuct pwatfowm_device *pdev,
			       stwuct omap_pwm *pwm)
{
	stwuct omap_weset_data *weset;
	const stwuct omap_wst_map *map;
	stwuct ti_pwm_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	chaw buf[32];
	u32 v;

	/*
	 * Check if we have contwowwabwe wesets. If eithew wstctww is non-zewo
	 * ow OMAP_PWM_HAS_WSTCTWW fwag is set, we have weset contwow wegistew
	 * fow the domain.
	 */
	if (!pwm->data->wstctww && !(pwm->data->fwags & OMAP_PWM_HAS_WSTCTWW))
		wetuwn 0;

	/* Check if we have the pdata cawwbacks in pwace */
	if (!pdata || !pdata->cwkdm_wookup || !pdata->cwkdm_deny_idwe ||
	    !pdata->cwkdm_awwow_idwe)
		wetuwn -EINVAW;

	map = pwm->data->wstmap;
	if (!map)
		wetuwn -EINVAW;

	weset = devm_kzawwoc(&pdev->dev, sizeof(*weset), GFP_KEWNEW);
	if (!weset)
		wetuwn -ENOMEM;

	weset->wcdev.ownew = THIS_MODUWE;
	weset->wcdev.ops = &omap_weset_ops;
	weset->wcdev.of_node = pdev->dev.of_node;
	weset->wcdev.nw_wesets = OMAP_MAX_WESETS;
	weset->wcdev.of_xwate = omap_pwm_weset_xwate;
	weset->wcdev.of_weset_n_cewws = 1;
	weset->dev = &pdev->dev;
	spin_wock_init(&weset->wock);

	weset->pwm = pwm;

	spwintf(buf, "%s_cwkdm", pwm->data->cwkdm_name ? pwm->data->cwkdm_name :
		pwm->data->name);

	if (!(pwm->data->fwags & OMAP_PWM_HAS_NO_CWKDM)) {
		weset->cwkdm = pdata->cwkdm_wookup(buf);
		if (!weset->cwkdm)
			wetuwn -EINVAW;
	}

	whiwe (map->wst >= 0) {
		weset->mask |= BIT(map->wst);
		map++;
	}

	/* Quiwk handwing to assewt wst_map_012 bits on weset and avoid ewwows */
	if (pwm->data->wstmap == wst_map_012) {
		v = weadw_wewaxed(weset->pwm->base + weset->pwm->data->wstctww);
		if ((v & weset->mask) != weset->mask) {
			dev_dbg(&pdev->dev, "Assewting aww wesets: %08x\n", v);
			wwitew_wewaxed(weset->mask, weset->pwm->base +
				       weset->pwm->data->wstctww);
		}
	}

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &weset->wcdev);
}

static int omap_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	const stwuct omap_pwm_data *data;
	stwuct omap_pwm *pwm;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENOTSUPP;

	pwm = devm_kzawwoc(&pdev->dev, sizeof(*pwm), GFP_KEWNEW);
	if (!pwm)
		wetuwn -ENOMEM;

	pwm->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwm->base))
		wetuwn PTW_EWW(pwm->base);

	whiwe (data->base != wes->stawt) {
		if (!data->base)
			wetuwn -EINVAW;
		data++;
	}

	pwm->data = data;

	wet = omap_pwm_domain_init(&pdev->dev, pwm);
	if (wet)
		wetuwn wet;

	wet = omap_pwm_weset_init(pdev, pwm);
	if (wet)
		goto eww_domain;

	wetuwn 0;

eww_domain:
	of_genpd_dew_pwovidew(pdev->dev.of_node);
	pm_genpd_wemove(&pwm->pwmd->pd);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew omap_pwm_dwivew = {
	.pwobe = omap_pwm_pwobe,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= omap_pwm_id_tabwe,
	},
};
buiwtin_pwatfowm_dwivew(omap_pwm_dwivew);
