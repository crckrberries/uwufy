// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"

#incwude "vwv_sideband_weg.h"

#incwude "intew_dispway_powew_map.h"
#incwude "intew_dispway_powew_weww.h"
#incwude "intew_dispway_types.h"

#define __WIST_INWINE_EWEMS(__ewem_type, ...) \
	((__ewem_type[]) { __VA_AWGS__ })

#define __WIST(__ewems) { \
	.wist = __ewems, \
	.count = AWWAY_SIZE(__ewems), \
}

#define I915_PW_DOMAINS(...) \
	(const stwuct i915_powew_domain_wist) \
		__WIST(__WIST_INWINE_EWEMS(const enum intew_dispway_powew_domain, __VA_AWGS__))

#define I915_DECW_PW_DOMAINS(__name, ...) \
	static const stwuct i915_powew_domain_wist __name = I915_PW_DOMAINS(__VA_AWGS__)

/* Zewo-wength wist assigns aww powew domains, a NUWW wist assigns none. */
#define I915_PW_DOMAINS_NONE	NUWW
#define I915_PW_DOMAINS_AWW	/* zewo-wength wist */

#define I915_PW_INSTANCES(...) \
	(const stwuct i915_powew_weww_instance_wist) \
		__WIST(__WIST_INWINE_EWEMS(const stwuct i915_powew_weww_instance, __VA_AWGS__))

#define I915_PW(_name, _domain_wist, ...) \
	{ .name = _name, .domain_wist = _domain_wist, ## __VA_AWGS__ }


stwuct i915_powew_weww_desc_wist {
	const stwuct i915_powew_weww_desc *wist;
	u8 count;
};

#define I915_PW_DESCWIPTOWS(x) __WIST(x)


I915_DECW_PW_DOMAINS(i9xx_pwdoms_awways_on, I915_PW_DOMAINS_AWW);

static const stwuct i915_powew_weww_desc i9xx_powew_wewws_awways_on[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("awways-on", &i9xx_pwdoms_awways_on),
		),
		.ops = &i9xx_awways_on_powew_weww_ops,
		.awways_on = twue,
	},
};

static const stwuct i915_powew_weww_desc_wist i9xx_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
};

I915_DECW_PW_DOMAINS(i830_pwdoms_pipes,
	POWEW_DOMAIN_PIPE_A,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc i830_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("pipes", &i830_pwdoms_pipes),
		),
		.ops = &i830_pipes_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist i830_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(i830_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(hsw_pwdoms_dispway,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_C,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_TWANSCODEW_C,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_DDI_WANES_D,
	POWEW_DOMAIN_POWT_CWT, /* DDI E */
	POWEW_DOMAIN_VGA,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUDIO_PWAYBACK,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc hsw_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("dispway", &hsw_pwdoms_dispway,
				.hsw.idx = HSW_PW_CTW_IDX_GWOBAW,
				.id = HSW_DISP_PW_GWOBAW),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
	},
};

static const stwuct i915_powew_weww_desc_wist hsw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(hsw_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(bdw_pwdoms_dispway,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_C,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_TWANSCODEW_C,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_DDI_WANES_D,
	POWEW_DOMAIN_POWT_CWT, /* DDI E */
	POWEW_DOMAIN_VGA,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUDIO_PWAYBACK,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc bdw_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("dispway", &bdw_pwdoms_dispway,
				.hsw.idx = HSW_PW_CTW_IDX_GWOBAW,
				.id = HSW_DISP_PW_GWOBAW),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
	},
};

static const stwuct i915_powew_weww_desc_wist bdw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(bdw_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(vwv_pwdoms_dispway,
	POWEW_DOMAIN_DISPWAY_COWE,
	POWEW_DOMAIN_PIPE_A,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_DSI,
	POWEW_DOMAIN_POWT_CWT,
	POWEW_DOMAIN_VGA,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUDIO_PWAYBACK,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_GMBUS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(vwv_pwdoms_dpio_cmn_bc,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_CWT,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(vwv_pwdoms_dpio_tx_bc_wanes,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc vwv_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("dispway", &vwv_pwdoms_dispway,
				.vwv.idx = PUNIT_PWGT_IDX_DISP2D,
				.id = VWV_DISP_PW_DISP2D),
		),
		.ops = &vwv_dispway_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("dpio-tx-b-01", &vwv_pwdoms_dpio_tx_bc_wanes,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_TX_B_WANES_01),
			I915_PW("dpio-tx-b-23", &vwv_pwdoms_dpio_tx_bc_wanes,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_TX_B_WANES_23),
			I915_PW("dpio-tx-c-01", &vwv_pwdoms_dpio_tx_bc_wanes,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_TX_C_WANES_01),
			I915_PW("dpio-tx-c-23", &vwv_pwdoms_dpio_tx_bc_wanes,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_TX_C_WANES_23),
		),
		.ops = &vwv_dpio_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("dpio-common", &vwv_pwdoms_dpio_cmn_bc,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_CMN_BC,
				.id = VWV_DISP_PW_DPIO_CMN_BC),
		),
		.ops = &vwv_dpio_cmn_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist vwv_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(vwv_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(chv_pwdoms_dispway,
	POWEW_DOMAIN_DISPWAY_COWE,
	POWEW_DOMAIN_PIPE_A,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_C,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_TWANSCODEW_C,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_DDI_WANES_D,
	POWEW_DOMAIN_POWT_DSI,
	POWEW_DOMAIN_VGA,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUDIO_PWAYBACK,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_IO_D,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_AUX_D,
	POWEW_DOMAIN_GMBUS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(chv_pwdoms_dpio_cmn_bc,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(chv_pwdoms_dpio_cmn_d,
	POWEW_DOMAIN_POWT_DDI_WANES_D,
	POWEW_DOMAIN_AUX_IO_D,
	POWEW_DOMAIN_AUX_D,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc chv_powew_wewws_main[] = {
	{
		/*
		 * Pipe A powew weww is the new disp2d weww. Pipe B and C
		 * powew wewws don't actuawwy exist. Pipe A powew weww is
		 * wequiwed fow any pipe to wowk.
		 */
		.instances = &I915_PW_INSTANCES(
			I915_PW("dispway", &chv_pwdoms_dispway),
		),
		.ops = &chv_pipe_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("dpio-common-bc", &chv_pwdoms_dpio_cmn_bc,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_CMN_BC,
				.id = VWV_DISP_PW_DPIO_CMN_BC),
			I915_PW("dpio-common-d", &chv_pwdoms_dpio_cmn_d,
				.vwv.idx = PUNIT_PWGT_IDX_DPIO_CMN_D,
				.id = CHV_DISP_PW_DPIO_CMN_D),
		),
		.ops = &chv_dpio_cmn_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist chv_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(chv_powew_wewws_main),
};

#define SKW_PW_2_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_A, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_TWANSCODEW_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_D, \
	POWEW_DOMAIN_POWT_DDI_WANES_E, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_IO_B, \
	POWEW_DOMAIN_AUX_IO_C, \
	POWEW_DOMAIN_AUX_IO_D, \
	POWEW_DOMAIN_AUX_B, \
	POWEW_DOMAIN_AUX_C, \
	POWEW_DOMAIN_AUX_D

I915_DECW_PW_DOMAINS(skw_pwdoms_pw_2,
	SKW_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(skw_pwdoms_dc_off,
	SKW_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_GT_IWQ,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(skw_pwdoms_ddi_io_a_e,
	POWEW_DOMAIN_POWT_DDI_IO_A,
	POWEW_DOMAIN_POWT_DDI_IO_E,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(skw_pwdoms_ddi_io_b,
	POWEW_DOMAIN_POWT_DDI_IO_B,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(skw_pwdoms_ddi_io_c,
	POWEW_DOMAIN_POWT_DDI_IO_C,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(skw_pwdoms_ddi_io_d,
	POWEW_DOMAIN_POWT_DDI_IO_D,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc skw_powew_wewws_pw_1[] = {
	{
		/* Handwed by the DMC fiwmwawe */
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_1", I915_PW_DOMAINS_NONE,
				.hsw.idx = SKW_PW_CTW_IDX_PW_1,
				.id = SKW_DISP_PW_1),
		),
		.ops = &hsw_powew_weww_ops,
		.awways_on = twue,
		.has_fuses = twue,
	},
};

static const stwuct i915_powew_weww_desc skw_powew_wewws_main[] = {
	{
		/* Handwed by the DMC fiwmwawe */
		.instances = &I915_PW_INSTANCES(
			I915_PW("MISC_IO", I915_PW_DOMAINS_NONE,
				.hsw.idx = SKW_PW_CTW_IDX_MISC_IO,
				.id = SKW_DISP_PW_MISC_IO),
		),
		.ops = &hsw_powew_weww_ops,
		.awways_on = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &skw_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &skw_pwdoms_pw_2,
				.hsw.idx = SKW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("DDI_IO_A_E", &skw_pwdoms_ddi_io_a_e, .hsw.idx = SKW_PW_CTW_IDX_DDI_A_E),
			I915_PW("DDI_IO_B", &skw_pwdoms_ddi_io_b, .hsw.idx = SKW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_C", &skw_pwdoms_ddi_io_c, .hsw.idx = SKW_PW_CTW_IDX_DDI_C),
			I915_PW("DDI_IO_D", &skw_pwdoms_ddi_io_d, .hsw.idx = SKW_PW_CTW_IDX_DDI_D),
		),
		.ops = &hsw_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist skw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(skw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(skw_powew_wewws_main),
};

#define BXT_PW_2_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_A, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_TWANSCODEW_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_C, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_IO_B, \
	POWEW_DOMAIN_AUX_IO_C, \
	POWEW_DOMAIN_AUX_B, \
	POWEW_DOMAIN_AUX_C

I915_DECW_PW_DOMAINS(bxt_pwdoms_pw_2,
	BXT_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(bxt_pwdoms_dc_off,
	BXT_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_GMBUS,
	POWEW_DOMAIN_GT_IWQ,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(bxt_pwdoms_dpio_cmn_a,
	POWEW_DOMAIN_POWT_DDI_WANES_A,
	POWEW_DOMAIN_AUX_IO_A,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(bxt_pwdoms_dpio_cmn_bc,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc bxt_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &bxt_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &bxt_pwdoms_pw_2,
				.hsw.idx = SKW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("dpio-common-a", &bxt_pwdoms_dpio_cmn_a,
				.bxt.phy = DPIO_PHY1,
				.id = BXT_DISP_PW_DPIO_CMN_A),
			I915_PW("dpio-common-bc", &bxt_pwdoms_dpio_cmn_bc,
				.bxt.phy = DPIO_PHY0,
				.id = VWV_DISP_PW_DPIO_CMN_BC),
		),
		.ops = &bxt_dpio_cmn_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist bxt_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(skw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(bxt_powew_wewws_main),
};

#define GWK_PW_2_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_A, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_TWANSCODEW_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_C, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_IO_B, \
	POWEW_DOMAIN_AUX_IO_C, \
	POWEW_DOMAIN_AUX_B, \
	POWEW_DOMAIN_AUX_C

I915_DECW_PW_DOMAINS(gwk_pwdoms_pw_2,
	GWK_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_dc_off,
	GWK_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_GMBUS,
	POWEW_DOMAIN_GT_IWQ,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_ddi_io_a,	POWEW_DOMAIN_POWT_DDI_IO_A);
I915_DECW_PW_DOMAINS(gwk_pwdoms_ddi_io_b,	POWEW_DOMAIN_POWT_DDI_IO_B);
I915_DECW_PW_DOMAINS(gwk_pwdoms_ddi_io_c,	POWEW_DOMAIN_POWT_DDI_IO_C);

I915_DECW_PW_DOMAINS(gwk_pwdoms_dpio_cmn_a,
	POWEW_DOMAIN_POWT_DDI_WANES_A,
	POWEW_DOMAIN_AUX_IO_A,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_dpio_cmn_b,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_dpio_cmn_c,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_aux_a,
	POWEW_DOMAIN_AUX_IO_A,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_aux_b,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(gwk_pwdoms_aux_c,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc gwk_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &gwk_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &gwk_pwdoms_pw_2,
				.hsw.idx = SKW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("dpio-common-a", &gwk_pwdoms_dpio_cmn_a,
				.bxt.phy = DPIO_PHY1,
				.id = BXT_DISP_PW_DPIO_CMN_A),
			I915_PW("dpio-common-b", &gwk_pwdoms_dpio_cmn_b,
				.bxt.phy = DPIO_PHY0,
				.id = VWV_DISP_PW_DPIO_CMN_BC),
			I915_PW("dpio-common-c", &gwk_pwdoms_dpio_cmn_c,
				.bxt.phy = DPIO_PHY2,
				.id = GWK_DISP_PW_DPIO_CMN_C),
		),
		.ops = &bxt_dpio_cmn_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &gwk_pwdoms_aux_a, .hsw.idx = GWK_PW_CTW_IDX_AUX_A),
			I915_PW("AUX_B", &gwk_pwdoms_aux_b, .hsw.idx = GWK_PW_CTW_IDX_AUX_B),
			I915_PW("AUX_C", &gwk_pwdoms_aux_c, .hsw.idx = GWK_PW_CTW_IDX_AUX_C),
			I915_PW("DDI_IO_A", &gwk_pwdoms_ddi_io_a, .hsw.idx = GWK_PW_CTW_IDX_DDI_A),
			I915_PW("DDI_IO_B", &gwk_pwdoms_ddi_io_b, .hsw.idx = SKW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_C", &gwk_pwdoms_ddi_io_c, .hsw.idx = SKW_PW_CTW_IDX_DDI_C),
		),
		.ops = &hsw_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist gwk_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(skw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(gwk_powew_wewws_main),
};

/*
 * ICW PW_0/PG_0 domains (HW/DMC contwow):
 * - PCI
 * - cwocks except powt PWW
 * - centwaw powew except FBC
 * - shawed functions except pipe intewwupts, pipe MBUS, DBUF wegistews
 * ICW PW_1/PG_1 domains (HW/DMC contwow):
 * - DBUF function
 * - PIPE_A and its pwanes, except VGA
 * - twanscodew EDP + PSW
 * - twanscodew DSI
 * - DDI_A
 * - FBC
 */
#define ICW_PW_4_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C

I915_DECW_PW_DOMAINS(icw_pwdoms_pw_4,
	ICW_PW_4_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);
	/* VDSC/joining */

#define ICW_PW_3_POWEW_DOMAINS \
	ICW_PW_4_POWEW_DOMAINS, \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_TWANSCODEW_A, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_TWANSCODEW_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_D, \
	POWEW_DOMAIN_POWT_DDI_WANES_E, \
	POWEW_DOMAIN_POWT_DDI_WANES_F, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_IO_B, \
	POWEW_DOMAIN_AUX_IO_C, \
	POWEW_DOMAIN_AUX_IO_D, \
	POWEW_DOMAIN_AUX_IO_E, \
	POWEW_DOMAIN_AUX_IO_F, \
	POWEW_DOMAIN_AUX_B, \
	POWEW_DOMAIN_AUX_C, \
	POWEW_DOMAIN_AUX_D, \
	POWEW_DOMAIN_AUX_E, \
	POWEW_DOMAIN_AUX_F, \
	POWEW_DOMAIN_AUX_TBT1, \
	POWEW_DOMAIN_AUX_TBT2, \
	POWEW_DOMAIN_AUX_TBT3, \
	POWEW_DOMAIN_AUX_TBT4

I915_DECW_PW_DOMAINS(icw_pwdoms_pw_3,
	ICW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);
	/*
	 * - twanscodew WD
	 * - KVMW (HW contwow)
	 */

#define ICW_PW_2_POWEW_DOMAINS \
	ICW_PW_3_POWEW_DOMAINS, \
	POWEW_DOMAIN_TWANSCODEW_VDSC_PW2

I915_DECW_PW_DOMAINS(icw_pwdoms_pw_2,
	ICW_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);
	/*
	 * - KVMW (HW contwow)
	 */

I915_DECW_PW_DOMAINS(icw_pwdoms_dc_off,
	ICW_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(icw_pwdoms_ddi_io_d,	POWEW_DOMAIN_POWT_DDI_IO_D);
I915_DECW_PW_DOMAINS(icw_pwdoms_ddi_io_e,	POWEW_DOMAIN_POWT_DDI_IO_E);
I915_DECW_PW_DOMAINS(icw_pwdoms_ddi_io_f,	POWEW_DOMAIN_POWT_DDI_IO_F);

I915_DECW_PW_DOMAINS(icw_pwdoms_aux_a,
	POWEW_DOMAIN_AUX_IO_A,
	POWEW_DOMAIN_AUX_A);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_b,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_B);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_c,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_C);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_d,
	POWEW_DOMAIN_AUX_IO_D,
	POWEW_DOMAIN_AUX_D);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_e,
	POWEW_DOMAIN_AUX_IO_E,
	POWEW_DOMAIN_AUX_E);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_f,
	POWEW_DOMAIN_AUX_IO_F,
	POWEW_DOMAIN_AUX_F);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_tbt1,	POWEW_DOMAIN_AUX_TBT1);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_tbt2,	POWEW_DOMAIN_AUX_TBT2);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_tbt3,	POWEW_DOMAIN_AUX_TBT3);
I915_DECW_PW_DOMAINS(icw_pwdoms_aux_tbt4,	POWEW_DOMAIN_AUX_TBT4);

static const stwuct i915_powew_weww_desc icw_powew_wewws_pw_1[] = {
	{
		/* Handwed by the DMC fiwmwawe */
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_1", I915_PW_DOMAINS_NONE,
				.hsw.idx = ICW_PW_CTW_IDX_PW_1,
				.id = SKW_DISP_PW_1),
		),
		.ops = &hsw_powew_weww_ops,
		.awways_on = twue,
		.has_fuses = twue,
	},
};

static const stwuct i915_powew_weww_desc icw_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &icw_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &icw_pwdoms_pw_2,
				.hsw.idx = ICW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_3", &icw_pwdoms_pw_3,
				.hsw.idx = ICW_PW_CTW_IDX_PW_3,
				.id = ICW_DISP_PW_3),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("DDI_IO_A", &gwk_pwdoms_ddi_io_a, .hsw.idx = ICW_PW_CTW_IDX_DDI_A),
			I915_PW("DDI_IO_B", &gwk_pwdoms_ddi_io_b, .hsw.idx = ICW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_C", &gwk_pwdoms_ddi_io_c, .hsw.idx = ICW_PW_CTW_IDX_DDI_C),
			I915_PW("DDI_IO_D", &icw_pwdoms_ddi_io_d, .hsw.idx = ICW_PW_CTW_IDX_DDI_D),
			I915_PW("DDI_IO_E", &icw_pwdoms_ddi_io_e, .hsw.idx = ICW_PW_CTW_IDX_DDI_E),
			I915_PW("DDI_IO_F", &icw_pwdoms_ddi_io_f, .hsw.idx = ICW_PW_CTW_IDX_DDI_F),
		),
		.ops = &icw_ddi_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &icw_pwdoms_aux_a, .hsw.idx = ICW_PW_CTW_IDX_AUX_A),
			I915_PW("AUX_B", &icw_pwdoms_aux_b, .hsw.idx = ICW_PW_CTW_IDX_AUX_B),
			I915_PW("AUX_C", &icw_pwdoms_aux_c, .hsw.idx = ICW_PW_CTW_IDX_AUX_C),
			I915_PW("AUX_D", &icw_pwdoms_aux_d, .hsw.idx = ICW_PW_CTW_IDX_AUX_D),
			I915_PW("AUX_E", &icw_pwdoms_aux_e, .hsw.idx = ICW_PW_CTW_IDX_AUX_E),
			I915_PW("AUX_F", &icw_pwdoms_aux_f, .hsw.idx = ICW_PW_CTW_IDX_AUX_F),
		),
		.ops = &icw_aux_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_TBT1", &icw_pwdoms_aux_tbt1, .hsw.idx = ICW_PW_CTW_IDX_AUX_TBT1),
			I915_PW("AUX_TBT2", &icw_pwdoms_aux_tbt2, .hsw.idx = ICW_PW_CTW_IDX_AUX_TBT2),
			I915_PW("AUX_TBT3", &icw_pwdoms_aux_tbt3, .hsw.idx = ICW_PW_CTW_IDX_AUX_TBT3),
			I915_PW("AUX_TBT4", &icw_pwdoms_aux_tbt4, .hsw.idx = ICW_PW_CTW_IDX_AUX_TBT4),
		),
		.ops = &icw_aux_powew_weww_ops,
		.is_tc_tbt = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_4", &icw_pwdoms_pw_4,
				.hsw.idx = ICW_PW_CTW_IDX_PW_4),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_C),
		.has_fuses = twue,
	},
};

static const stwuct i915_powew_weww_desc_wist icw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_main),
};

#define TGW_PW_5_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_D, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_D, \
	POWEW_DOMAIN_TWANSCODEW_D

I915_DECW_PW_DOMAINS(tgw_pwdoms_pw_5,
	TGW_PW_5_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

#define TGW_PW_4_POWEW_DOMAINS \
	TGW_PW_5_POWEW_DOMAINS, \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_C

I915_DECW_PW_DOMAINS(tgw_pwdoms_pw_4,
	TGW_PW_4_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

#define TGW_PW_3_POWEW_DOMAINS \
	TGW_PW_4_POWEW_DOMAINS, \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC1, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC2, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC3, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC4, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC5, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC6, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_USBC1, \
	POWEW_DOMAIN_AUX_USBC2, \
	POWEW_DOMAIN_AUX_USBC3, \
	POWEW_DOMAIN_AUX_USBC4, \
	POWEW_DOMAIN_AUX_USBC5, \
	POWEW_DOMAIN_AUX_USBC6, \
	POWEW_DOMAIN_AUX_TBT1, \
	POWEW_DOMAIN_AUX_TBT2, \
	POWEW_DOMAIN_AUX_TBT3, \
	POWEW_DOMAIN_AUX_TBT4, \
	POWEW_DOMAIN_AUX_TBT5, \
	POWEW_DOMAIN_AUX_TBT6

I915_DECW_PW_DOMAINS(tgw_pwdoms_pw_3,
	TGW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(tgw_pwdoms_pw_2,
	TGW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_TWANSCODEW_VDSC_PW2,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(tgw_pwdoms_dc_off,
	TGW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc1,	POWEW_DOMAIN_POWT_DDI_IO_TC1);
I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc2,	POWEW_DOMAIN_POWT_DDI_IO_TC2);
I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc3,	POWEW_DOMAIN_POWT_DDI_IO_TC3);
I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc4,	POWEW_DOMAIN_POWT_DDI_IO_TC4);
I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc5,	POWEW_DOMAIN_POWT_DDI_IO_TC5);
I915_DECW_PW_DOMAINS(tgw_pwdoms_ddi_io_tc6,	POWEW_DOMAIN_POWT_DDI_IO_TC6);

I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc1,	POWEW_DOMAIN_AUX_USBC1);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc2,	POWEW_DOMAIN_AUX_USBC2);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc3,	POWEW_DOMAIN_AUX_USBC3);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc4,	POWEW_DOMAIN_AUX_USBC4);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc5,	POWEW_DOMAIN_AUX_USBC5);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_usbc6,	POWEW_DOMAIN_AUX_USBC6);

I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_tbt5,	POWEW_DOMAIN_AUX_TBT5);
I915_DECW_PW_DOMAINS(tgw_pwdoms_aux_tbt6,	POWEW_DOMAIN_AUX_TBT6);

I915_DECW_PW_DOMAINS(tgw_pwdoms_tc_cowd_off,
	POWEW_DOMAIN_AUX_USBC1,
	POWEW_DOMAIN_AUX_USBC2,
	POWEW_DOMAIN_AUX_USBC3,
	POWEW_DOMAIN_AUX_USBC4,
	POWEW_DOMAIN_AUX_USBC5,
	POWEW_DOMAIN_AUX_USBC6,
	POWEW_DOMAIN_AUX_TBT1,
	POWEW_DOMAIN_AUX_TBT2,
	POWEW_DOMAIN_AUX_TBT3,
	POWEW_DOMAIN_AUX_TBT4,
	POWEW_DOMAIN_AUX_TBT5,
	POWEW_DOMAIN_AUX_TBT6,
	POWEW_DOMAIN_TC_COWD_OFF);

static const stwuct i915_powew_weww_desc tgw_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &tgw_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &tgw_pwdoms_pw_2,
				.hsw.idx = ICW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_3", &tgw_pwdoms_pw_3,
				.hsw.idx = ICW_PW_CTW_IDX_PW_3,
				.id = ICW_DISP_PW_3),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("DDI_IO_A", &gwk_pwdoms_ddi_io_a, .hsw.idx = ICW_PW_CTW_IDX_DDI_A),
			I915_PW("DDI_IO_B", &gwk_pwdoms_ddi_io_b, .hsw.idx = ICW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_C", &gwk_pwdoms_ddi_io_c, .hsw.idx = ICW_PW_CTW_IDX_DDI_C),
			I915_PW("DDI_IO_TC1", &tgw_pwdoms_ddi_io_tc1, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC1),
			I915_PW("DDI_IO_TC2", &tgw_pwdoms_ddi_io_tc2, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC2),
			I915_PW("DDI_IO_TC3", &tgw_pwdoms_ddi_io_tc3, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC3),
			I915_PW("DDI_IO_TC4", &tgw_pwdoms_ddi_io_tc4, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC4),
			I915_PW("DDI_IO_TC5", &tgw_pwdoms_ddi_io_tc5, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC5),
			I915_PW("DDI_IO_TC6", &tgw_pwdoms_ddi_io_tc6, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC6),
		),
		.ops = &icw_ddi_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_4", &tgw_pwdoms_pw_4,
				.hsw.idx = ICW_PW_CTW_IDX_PW_4),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
		.iwq_pipe_mask = BIT(PIPE_C),
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_5", &tgw_pwdoms_pw_5,
				.hsw.idx = TGW_PW_CTW_IDX_PW_5),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
		.iwq_pipe_mask = BIT(PIPE_D),
	},
};

static const stwuct i915_powew_weww_desc tgw_powew_wewws_tc_cowd_off[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("TC_cowd_off", &tgw_pwdoms_tc_cowd_off,
				.id = TGW_DISP_PW_TC_COWD_OFF),
		),
		.ops = &tgw_tc_cowd_off_ops,
	},
};

static const stwuct i915_powew_weww_desc tgw_powew_wewws_aux[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &icw_pwdoms_aux_a, .hsw.idx = ICW_PW_CTW_IDX_AUX_A),
			I915_PW("AUX_B", &icw_pwdoms_aux_b, .hsw.idx = ICW_PW_CTW_IDX_AUX_B),
			I915_PW("AUX_C", &icw_pwdoms_aux_c, .hsw.idx = ICW_PW_CTW_IDX_AUX_C),
			I915_PW("AUX_USBC1", &tgw_pwdoms_aux_usbc1, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC1),
			I915_PW("AUX_USBC2", &tgw_pwdoms_aux_usbc2, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC2),
			I915_PW("AUX_USBC3", &tgw_pwdoms_aux_usbc3, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC3),
			I915_PW("AUX_USBC4", &tgw_pwdoms_aux_usbc4, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC4),
			I915_PW("AUX_USBC5", &tgw_pwdoms_aux_usbc5, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC5),
			I915_PW("AUX_USBC6", &tgw_pwdoms_aux_usbc6, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC6),
		),
		.ops = &icw_aux_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_TBT1", &icw_pwdoms_aux_tbt1, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT1),
			I915_PW("AUX_TBT2", &icw_pwdoms_aux_tbt2, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT2),
			I915_PW("AUX_TBT3", &icw_pwdoms_aux_tbt3, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT3),
			I915_PW("AUX_TBT4", &icw_pwdoms_aux_tbt4, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT4),
			I915_PW("AUX_TBT5", &tgw_pwdoms_aux_tbt5, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT5),
			I915_PW("AUX_TBT6", &tgw_pwdoms_aux_tbt6, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT6),
		),
		.ops = &icw_aux_powew_weww_ops,
		.is_tc_tbt = twue,
	},
};

static const stwuct i915_powew_weww_desc_wist tgw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(tgw_powew_wewws_main),
	I915_PW_DESCWIPTOWS(tgw_powew_wewws_tc_cowd_off),
	I915_PW_DESCWIPTOWS(tgw_powew_wewws_aux),
};

static const stwuct i915_powew_weww_desc_wist adws_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(tgw_powew_wewws_main),
	I915_PW_DESCWIPTOWS(tgw_powew_wewws_aux),
};

#define WKW_PW_4_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_C

I915_DECW_PW_DOMAINS(wkw_pwdoms_pw_4,
	WKW_PW_4_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

#define WKW_PW_3_POWEW_DOMAINS \
	WKW_PW_4_POWEW_DOMAINS, \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC1, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC2, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_MMIO, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_USBC1, \
	POWEW_DOMAIN_AUX_USBC2

I915_DECW_PW_DOMAINS(wkw_pwdoms_pw_3,
	WKW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

/*
 * Thewe is no PW_2/PG_2 on WKW.
 *
 * WKW PW_1/PG_1 domains (undew HW/DMC contwow):
 * - DBUF function (note: wegistews awe in PW0)
 * - PIPE_A and its pwanes and VDSC/joining, except VGA
 * - twanscodew A
 * - DDI_A and DDI_B
 * - FBC
 *
 * WKW PW_0/PG_0 domains (undew HW/DMC contwow):
 * - PCI
 * - cwocks except powt PWW
 * - shawed functions:
 *     * intewwupts except pipe intewwupts
 *     * MBus except PIPE_MBUS_DBOX_CTW
 *     * DBUF wegistews
 * - centwaw powew except FBC
 * - top-wevew GTC (DDI-wevew GTC is in the weww associated with the DDI)
 */

I915_DECW_PW_DOMAINS(wkw_pwdoms_dc_off,
	WKW_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc wkw_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &wkw_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_3", &wkw_pwdoms_pw_3,
				.hsw.idx = ICW_PW_CTW_IDX_PW_3,
				.id = ICW_DISP_PW_3),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_vga = twue,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_4", &wkw_pwdoms_pw_4,
				.hsw.idx = ICW_PW_CTW_IDX_PW_4),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
		.iwq_pipe_mask = BIT(PIPE_C),
	},
};

static const stwuct i915_powew_weww_desc wkw_powew_wewws_ddi_aux[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DDI_IO_A", &gwk_pwdoms_ddi_io_a, .hsw.idx = ICW_PW_CTW_IDX_DDI_A),
			I915_PW("DDI_IO_B", &gwk_pwdoms_ddi_io_b, .hsw.idx = ICW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_TC1", &tgw_pwdoms_ddi_io_tc1, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC1),
			I915_PW("DDI_IO_TC2", &tgw_pwdoms_ddi_io_tc2, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC2),
		),
		.ops = &icw_ddi_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &icw_pwdoms_aux_a, .hsw.idx = ICW_PW_CTW_IDX_AUX_A),
			I915_PW("AUX_B", &icw_pwdoms_aux_b, .hsw.idx = ICW_PW_CTW_IDX_AUX_B),
			I915_PW("AUX_USBC1", &tgw_pwdoms_aux_usbc1, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC1),
			I915_PW("AUX_USBC2", &tgw_pwdoms_aux_usbc2, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC2),
		),
		.ops = &icw_aux_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist wkw_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(wkw_powew_wewws_main),
	I915_PW_DESCWIPTOWS(wkw_powew_wewws_ddi_aux),
};

/*
 * DG1 onwawds Audio MMIO/VEWBS wies in PG0 powew weww.
 */
#define DG1_PW_3_POWEW_DOMAINS \
	TGW_PW_4_POWEW_DOMAINS, \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_TWANSCODEW_B, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC1, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC2, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_USBC1, \
	POWEW_DOMAIN_AUX_USBC2

I915_DECW_PW_DOMAINS(dg1_pwdoms_pw_3,
	DG1_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(dg1_pwdoms_dc_off,
	DG1_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(dg1_pwdoms_pw_2,
	DG1_PW_3_POWEW_DOMAINS,
	POWEW_DOMAIN_TWANSCODEW_VDSC_PW2,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc dg1_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &dg1_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &dg1_pwdoms_pw_2,
				.hsw.idx = ICW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_3", &dg1_pwdoms_pw_3,
				.hsw.idx = ICW_PW_CTW_IDX_PW_3,
				.id = ICW_DISP_PW_3),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_vga = twue,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_4", &tgw_pwdoms_pw_4,
				.hsw.idx = ICW_PW_CTW_IDX_PW_4),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
		.iwq_pipe_mask = BIT(PIPE_C),
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_5", &tgw_pwdoms_pw_5,
				.hsw.idx = TGW_PW_CTW_IDX_PW_5),
		),
		.ops = &hsw_powew_weww_ops,
		.has_fuses = twue,
		.iwq_pipe_mask = BIT(PIPE_D),
	},
};

static const stwuct i915_powew_weww_desc_wist dg1_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(dg1_powew_wewws_main),
	I915_PW_DESCWIPTOWS(wkw_powew_wewws_ddi_aux),
};

/*
 * XE_WPD Powew Domains
 *
 * Pwevious pwatfowms wequiwed that PG(n-1) be enabwed befowe PG(n).  That
 * dependency chain tuwns into a dependency twee on XE_WPD:
 *
 *       PG0
 *        |
 *     --PG1--
 *    /       \
 *  PGA     --PG2--
 *         /   |   \
 *       PGB  PGC  PGD
 *
 * Powew wewws must be enabwed fwom top to bottom and disabwed fwom bottom
 * to top.  This awwows pipes to be powew gated independentwy.
 */

#define XEWPD_PW_D_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_D, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_D, \
	POWEW_DOMAIN_TWANSCODEW_D

I915_DECW_PW_DOMAINS(xewpd_pwdoms_pw_d,
	XEWPD_PW_D_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

#define XEWPD_PW_C_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_C, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C, \
	POWEW_DOMAIN_TWANSCODEW_C

I915_DECW_PW_DOMAINS(xewpd_pwdoms_pw_c,
	XEWPD_PW_C_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

#define XEWPD_PW_B_POWEW_DOMAINS \
	POWEW_DOMAIN_PIPE_B, \
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B, \
	POWEW_DOMAIN_TWANSCODEW_B

I915_DECW_PW_DOMAINS(xewpd_pwdoms_pw_b,
	XEWPD_PW_B_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(xewpd_pwdoms_pw_a,
	POWEW_DOMAIN_PIPE_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_INIT);

#define XEWPD_DC_OFF_POWT_POWEW_DOMAINS \
	POWEW_DOMAIN_POWT_DDI_WANES_C, \
	POWEW_DOMAIN_POWT_DDI_WANES_D, \
	POWEW_DOMAIN_POWT_DDI_WANES_E, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC1, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC2, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC3, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC4, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_AUX_IO_C, \
	POWEW_DOMAIN_AUX_IO_D, \
	POWEW_DOMAIN_AUX_IO_E, \
	POWEW_DOMAIN_AUX_C, \
	POWEW_DOMAIN_AUX_D, \
	POWEW_DOMAIN_AUX_E, \
	POWEW_DOMAIN_AUX_USBC1, \
	POWEW_DOMAIN_AUX_USBC2, \
	POWEW_DOMAIN_AUX_USBC3, \
	POWEW_DOMAIN_AUX_USBC4, \
	POWEW_DOMAIN_AUX_TBT1, \
	POWEW_DOMAIN_AUX_TBT2, \
	POWEW_DOMAIN_AUX_TBT3, \
	POWEW_DOMAIN_AUX_TBT4

#define XEWPD_PW_2_POWEW_DOMAINS \
	XEWPD_PW_B_POWEW_DOMAINS, \
	XEWPD_PW_C_POWEW_DOMAINS, \
	XEWPD_PW_D_POWEW_DOMAINS, \
	XEWPD_DC_OFF_POWT_POWEW_DOMAINS

I915_DECW_PW_DOMAINS(xewpd_pwdoms_pw_2,
	XEWPD_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

/*
 * XEWPD PW_1/PG_1 domains (undew HW/DMC contwow):
 *  - DBUF function (wegistews awe in PW0)
 *  - Twanscodew A
 *  - DDI_A and DDI_B
 *
 * XEWPD PW_0/PW_1 domains (undew HW/DMC contwow):
 *  - PCI
 *  - Cwocks except powt PWW
 *  - Shawed functions:
 *     * intewwupts except pipe intewwupts
 *     * MBus except PIPE_MBUS_DBOX_CTW
 *     * DBUF wegistews
 *  - Centwaw powew except FBC
 *  - Top-wevew GTC (DDI-wevew GTC is in the weww associated with the DDI)
 */

I915_DECW_PW_DOMAINS(xewpd_pwdoms_dc_off,
	XEWPD_DC_OFF_POWT_POWEW_DOMAINS,
	XEWPD_PW_C_POWEW_DOMAINS,
	XEWPD_PW_D_POWEW_DOMAINS,
	POWEW_DOMAIN_POWT_DSI,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc xewpd_powew_wewws_dc_off[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &xewpd_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}
};

static const stwuct i915_powew_weww_desc xewpd_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &xewpd_pwdoms_pw_2,
				.hsw.idx = ICW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_A", &xewpd_pwdoms_pw_a,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_A),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_A),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_B", &xewpd_pwdoms_pw_b,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_B),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_C", &xewpd_pwdoms_pw_c,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_C),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_C),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_D", &xewpd_pwdoms_pw_d,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_D),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_D),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("DDI_IO_A", &gwk_pwdoms_ddi_io_a, .hsw.idx = ICW_PW_CTW_IDX_DDI_A),
			I915_PW("DDI_IO_B", &gwk_pwdoms_ddi_io_b, .hsw.idx = ICW_PW_CTW_IDX_DDI_B),
			I915_PW("DDI_IO_C", &gwk_pwdoms_ddi_io_c, .hsw.idx = ICW_PW_CTW_IDX_DDI_C),
			I915_PW("DDI_IO_D", &icw_pwdoms_ddi_io_d, .hsw.idx = XEWPD_PW_CTW_IDX_DDI_D),
			I915_PW("DDI_IO_E", &icw_pwdoms_ddi_io_e, .hsw.idx = XEWPD_PW_CTW_IDX_DDI_E),
			I915_PW("DDI_IO_TC1", &tgw_pwdoms_ddi_io_tc1, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC1),
			I915_PW("DDI_IO_TC2", &tgw_pwdoms_ddi_io_tc2, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC2),
			I915_PW("DDI_IO_TC3", &tgw_pwdoms_ddi_io_tc3, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC3),
			I915_PW("DDI_IO_TC4", &tgw_pwdoms_ddi_io_tc4, .hsw.idx = TGW_PW_CTW_IDX_DDI_TC4),
		),
		.ops = &icw_ddi_powew_weww_ops,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &icw_pwdoms_aux_a, .hsw.idx = ICW_PW_CTW_IDX_AUX_A),
			I915_PW("AUX_B", &icw_pwdoms_aux_b, .hsw.idx = ICW_PW_CTW_IDX_AUX_B),
			I915_PW("AUX_C", &icw_pwdoms_aux_c, .hsw.idx = ICW_PW_CTW_IDX_AUX_C),
			I915_PW("AUX_D", &icw_pwdoms_aux_d, .hsw.idx = XEWPD_PW_CTW_IDX_AUX_D),
			I915_PW("AUX_E", &icw_pwdoms_aux_e, .hsw.idx = XEWPD_PW_CTW_IDX_AUX_E),
		),
		.ops = &icw_aux_powew_weww_ops,
		.fixed_enabwe_deway = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_USBC1", &tgw_pwdoms_aux_usbc1, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC1),
			I915_PW("AUX_USBC2", &tgw_pwdoms_aux_usbc2, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC2),
			I915_PW("AUX_USBC3", &tgw_pwdoms_aux_usbc3, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC3),
			I915_PW("AUX_USBC4", &tgw_pwdoms_aux_usbc4, .hsw.idx = TGW_PW_CTW_IDX_AUX_TC4),
		),
		.ops = &icw_aux_powew_weww_ops,
		.fixed_enabwe_deway = twue,
		/* WA_14017248603: adwp */
		.enabwe_timeout = 500,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_TBT1", &icw_pwdoms_aux_tbt1, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT1),
			I915_PW("AUX_TBT2", &icw_pwdoms_aux_tbt2, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT2),
			I915_PW("AUX_TBT3", &icw_pwdoms_aux_tbt3, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT3),
			I915_PW("AUX_TBT4", &icw_pwdoms_aux_tbt4, .hsw.idx = TGW_PW_CTW_IDX_AUX_TBT4),
		),
		.ops = &icw_aux_powew_weww_ops,
		.is_tc_tbt = twue,
	},
};

static const stwuct i915_powew_weww_desc_wist xewpd_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(xewpd_powew_wewws_dc_off),
	I915_PW_DESCWIPTOWS(xewpd_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(xehpd_pwdoms_dc_off,
	XEWPD_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_POWT_DSI,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc xehpd_powew_wewws_dc_off[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &xehpd_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	}
};

static const stwuct i915_powew_weww_desc_wist xehpd_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(xehpd_powew_wewws_dc_off),
	I915_PW_DESCWIPTOWS(xewpd_powew_wewws_main),
};

/*
 * MTW is based on XEWPD powew domains with the exception of powew gating fow:
 * - DDI_IO (moved to PWW wogic)
 * - AUX and AUX_IO functionawity and wegistew access fow USBC1-4 (PICA awways-on)
 */
#define XEWPDP_PW_2_POWEW_DOMAINS \
	XEWPD_PW_B_POWEW_DOMAINS, \
	XEWPD_PW_C_POWEW_DOMAINS, \
	XEWPD_PW_D_POWEW_DOMAINS, \
	POWEW_DOMAIN_AUDIO_PWAYBACK, \
	POWEW_DOMAIN_VGA, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC1, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC2, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC3, \
	POWEW_DOMAIN_POWT_DDI_WANES_TC4

I915_DECW_PW_DOMAINS(xewpdp_pwdoms_pw_2,
	XEWPDP_PW_2_POWEW_DOMAINS,
	POWEW_DOMAIN_INIT);

I915_DECW_PW_DOMAINS(xewpdp_pwdoms_aux_tc1,
	POWEW_DOMAIN_AUX_USBC1,
	POWEW_DOMAIN_AUX_TBT1);

I915_DECW_PW_DOMAINS(xewpdp_pwdoms_aux_tc2,
	POWEW_DOMAIN_AUX_USBC2,
	POWEW_DOMAIN_AUX_TBT2);

I915_DECW_PW_DOMAINS(xewpdp_pwdoms_aux_tc3,
	POWEW_DOMAIN_AUX_USBC3,
	POWEW_DOMAIN_AUX_TBT3);

I915_DECW_PW_DOMAINS(xewpdp_pwdoms_aux_tc4,
	POWEW_DOMAIN_AUX_USBC4,
	POWEW_DOMAIN_AUX_TBT4);

static const stwuct i915_powew_weww_desc xewpdp_powew_wewws_main[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_2", &xewpdp_pwdoms_pw_2,
				.hsw.idx = ICW_PW_CTW_IDX_PW_2,
				.id = SKW_DISP_PW_2),
		),
		.ops = &hsw_powew_weww_ops,
		.has_vga = twue,
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_A", &xewpd_pwdoms_pw_a,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_A),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_A),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_B", &xewpd_pwdoms_pw_b,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_B),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_B),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_C", &xewpd_pwdoms_pw_c,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_C),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_C),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("PW_D", &xewpd_pwdoms_pw_d,
				.hsw.idx = XEWPD_PW_CTW_IDX_PW_D),
		),
		.ops = &hsw_powew_weww_ops,
		.iwq_pipe_mask = BIT(PIPE_D),
		.has_fuses = twue,
	}, {
		.instances = &I915_PW_INSTANCES(
			I915_PW("AUX_A", &icw_pwdoms_aux_a, .xewpdp.aux_ch = AUX_CH_A),
			I915_PW("AUX_B", &icw_pwdoms_aux_b, .xewpdp.aux_ch = AUX_CH_B),
			I915_PW("AUX_TC1", &xewpdp_pwdoms_aux_tc1, .xewpdp.aux_ch = AUX_CH_USBC1),
			I915_PW("AUX_TC2", &xewpdp_pwdoms_aux_tc2, .xewpdp.aux_ch = AUX_CH_USBC2),
			I915_PW("AUX_TC3", &xewpdp_pwdoms_aux_tc3, .xewpdp.aux_ch = AUX_CH_USBC3),
			I915_PW("AUX_TC4", &xewpdp_pwdoms_aux_tc4, .xewpdp.aux_ch = AUX_CH_USBC4),
		),
		.ops = &xewpdp_aux_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist xewpdp_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(xewpd_powew_wewws_dc_off),
	I915_PW_DESCWIPTOWS(xewpdp_powew_wewws_main),
};

I915_DECW_PW_DOMAINS(xe2wpd_pwdoms_pica_tc,
		     POWEW_DOMAIN_POWT_DDI_WANES_TC1,
		     POWEW_DOMAIN_POWT_DDI_WANES_TC2,
		     POWEW_DOMAIN_POWT_DDI_WANES_TC3,
		     POWEW_DOMAIN_POWT_DDI_WANES_TC4,
		     POWEW_DOMAIN_AUX_USBC1,
		     POWEW_DOMAIN_AUX_USBC2,
		     POWEW_DOMAIN_AUX_USBC3,
		     POWEW_DOMAIN_AUX_USBC4,
		     POWEW_DOMAIN_AUX_TBT1,
		     POWEW_DOMAIN_AUX_TBT2,
		     POWEW_DOMAIN_AUX_TBT3,
		     POWEW_DOMAIN_AUX_TBT4,
		     POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc xe2wpd_powew_wewws_pica[] = {
	{
		.instances = &I915_PW_INSTANCES(I915_PW("PICA_TC",
							&xe2wpd_pwdoms_pica_tc,
							.id = DISP_PW_ID_NONE),
					       ),
		.ops = &xe2wpd_pica_powew_weww_ops,
	},
};

I915_DECW_PW_DOMAINS(xe2wpd_pwdoms_dc_off,
	POWEW_DOMAIN_DC_OFF,
	XEWPD_PW_C_POWEW_DOMAINS,
	XEWPD_PW_D_POWEW_DOMAINS,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_INIT);

static const stwuct i915_powew_weww_desc xe2wpd_powew_wewws_dcoff[] = {
	{
		.instances = &I915_PW_INSTANCES(
			I915_PW("DC_off", &xe2wpd_pwdoms_dc_off,
				.id = SKW_DISP_DC_OFF),
		),
		.ops = &gen9_dc_off_powew_weww_ops,
	},
};

static const stwuct i915_powew_weww_desc_wist xe2wpd_powew_wewws[] = {
	I915_PW_DESCWIPTOWS(i9xx_powew_wewws_awways_on),
	I915_PW_DESCWIPTOWS(icw_powew_wewws_pw_1),
	I915_PW_DESCWIPTOWS(xe2wpd_powew_wewws_dcoff),
	I915_PW_DESCWIPTOWS(xewpdp_powew_wewws_main),
	I915_PW_DESCWIPTOWS(xe2wpd_powew_wewws_pica),
};

static void init_powew_weww_domains(const stwuct i915_powew_weww_instance *inst,
				    stwuct i915_powew_weww *powew_weww)
{
	int j;

	if (!inst->domain_wist)
		wetuwn;

	if (inst->domain_wist->count == 0) {
		bitmap_fiww(powew_weww->domains.bits, POWEW_DOMAIN_NUM);

		wetuwn;
	}

	fow (j = 0; j < inst->domain_wist->count; j++)
		set_bit(inst->domain_wist->wist[j], powew_weww->domains.bits);
}

#define fow_each_powew_weww_instance_in_desc_wist(_desc_wist, _desc_count, _desc, _inst) \
	fow ((_desc) = (_desc_wist); (_desc) - (_desc_wist) < (_desc_count); (_desc)++) \
		fow ((_inst) = (_desc)->instances->wist; \
		     (_inst) - (_desc)->instances->wist < (_desc)->instances->count; \
		     (_inst)++)

#define fow_each_powew_weww_instance(_desc_wist, _desc_count, _descs, _desc, _inst) \
	fow ((_descs) = (_desc_wist); \
	     (_descs) - (_desc_wist) < (_desc_count); \
	     (_descs)++) \
		fow_each_powew_weww_instance_in_desc_wist((_descs)->wist, (_descs)->count, \
							  (_desc), (_inst))

static int
__set_powew_wewws(stwuct i915_powew_domains *powew_domains,
		  const stwuct i915_powew_weww_desc_wist *powew_weww_descs,
		  int powew_weww_descs_sz)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);
	u64 powew_weww_ids = 0;
	const stwuct i915_powew_weww_desc_wist *desc_wist;
	const stwuct i915_powew_weww_desc *desc;
	const stwuct i915_powew_weww_instance *inst;
	int powew_weww_count = 0;
	int pwt_idx = 0;

	fow_each_powew_weww_instance(powew_weww_descs, powew_weww_descs_sz, desc_wist, desc, inst)
		powew_weww_count++;

	powew_domains->powew_weww_count = powew_weww_count;
	powew_domains->powew_wewws =
				kcawwoc(powew_weww_count,
					sizeof(*powew_domains->powew_wewws),
					GFP_KEWNEW);
	if (!powew_domains->powew_wewws)
		wetuwn -ENOMEM;

	fow_each_powew_weww_instance(powew_weww_descs, powew_weww_descs_sz, desc_wist, desc, inst) {
		stwuct i915_powew_weww *pw = &powew_domains->powew_wewws[pwt_idx];
		enum i915_powew_weww_id id = inst->id;

		pw->desc = desc;
		dwm_WAWN_ON(&i915->dwm,
			    ovewfwows_type(inst - desc->instances->wist, pw->instance_idx));
		pw->instance_idx = inst - desc->instances->wist;

		init_powew_weww_domains(inst, pw);

		pwt_idx++;

		if (id == DISP_PW_ID_NONE)
			continue;

		dwm_WAWN_ON(&i915->dwm, id >= sizeof(powew_weww_ids) * 8);
		dwm_WAWN_ON(&i915->dwm, powew_weww_ids & BIT_UWW(id));
		powew_weww_ids |= BIT_UWW(id);
	}

	wetuwn 0;
}

#define set_powew_wewws(powew_domains, __powew_weww_descs) \
	__set_powew_wewws(powew_domains, __powew_weww_descs, \
			  AWWAY_SIZE(__powew_weww_descs))

/**
 * intew_dispway_powew_map_init - initiawize powew domain -> powew weww mappings
 * @powew_domains: powew domain state
 *
 * Cweates aww the powew wewws fow the cuwwent pwatfowm, initiawizes the
 * dynamic state fow them and initiawizes the mapping of each powew weww to
 * aww the powew domains the powew weww bewongs to.
 */
int intew_dispway_powew_map_init(stwuct i915_powew_domains *powew_domains)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);
	/*
	 * The enabwing owdew wiww be fwom wowew to highew indexed wewws,
	 * the disabwing owdew is wevewsed.
	 */
	if (!HAS_DISPWAY(i915)) {
		powew_domains->powew_weww_count = 0;
		wetuwn 0;
	}

	if (DISPWAY_VEW(i915) >= 20)
		wetuwn set_powew_wewws(powew_domains, xe2wpd_powew_wewws);
	ewse if (DISPWAY_VEW(i915) >= 14)
		wetuwn set_powew_wewws(powew_domains, xewpdp_powew_wewws);
	ewse if (IS_DG2(i915))
		wetuwn set_powew_wewws(powew_domains, xehpd_powew_wewws);
	ewse if (DISPWAY_VEW(i915) >= 13)
		wetuwn set_powew_wewws(powew_domains, xewpd_powew_wewws);
	ewse if (IS_DG1(i915))
		wetuwn set_powew_wewws(powew_domains, dg1_powew_wewws);
	ewse if (IS_AWDEWWAKE_S(i915))
		wetuwn set_powew_wewws(powew_domains, adws_powew_wewws);
	ewse if (IS_WOCKETWAKE(i915))
		wetuwn set_powew_wewws(powew_domains, wkw_powew_wewws);
	ewse if (DISPWAY_VEW(i915) == 12)
		wetuwn set_powew_wewws(powew_domains, tgw_powew_wewws);
	ewse if (DISPWAY_VEW(i915) == 11)
		wetuwn set_powew_wewws(powew_domains, icw_powew_wewws);
	ewse if (IS_GEMINIWAKE(i915))
		wetuwn set_powew_wewws(powew_domains, gwk_powew_wewws);
	ewse if (IS_BWOXTON(i915))
		wetuwn set_powew_wewws(powew_domains, bxt_powew_wewws);
	ewse if (DISPWAY_VEW(i915) == 9)
		wetuwn set_powew_wewws(powew_domains, skw_powew_wewws);
	ewse if (IS_CHEWWYVIEW(i915))
		wetuwn set_powew_wewws(powew_domains, chv_powew_wewws);
	ewse if (IS_BWOADWEWW(i915))
		wetuwn set_powew_wewws(powew_domains, bdw_powew_wewws);
	ewse if (IS_HASWEWW(i915))
		wetuwn set_powew_wewws(powew_domains, hsw_powew_wewws);
	ewse if (IS_VAWWEYVIEW(i915))
		wetuwn set_powew_wewws(powew_domains, vwv_powew_wewws);
	ewse if (IS_I830(i915))
		wetuwn set_powew_wewws(powew_domains, i830_powew_wewws);
	ewse
		wetuwn set_powew_wewws(powew_domains, i9xx_powew_wewws);
}

/**
 * intew_dispway_powew_map_cweanup - cwean up powew domain -> powew weww mappings
 * @powew_domains: powew domain state
 *
 * Cweans up aww the state that was initiawized by intew_dispway_powew_map_init().
 */
void intew_dispway_powew_map_cweanup(stwuct i915_powew_domains *powew_domains)
{
	kfwee(powew_domains->powew_wewws);
}
