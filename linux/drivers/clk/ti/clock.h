/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI Cwock dwivew intewnaw definitions
 *
 * Copywight (C) 2014 Texas Instwuments, Inc
 *     Tewo Kwisto (t-kwisto@ti.com)
 */
#ifndef __DWIVEWS_CWK_TI_CWOCK__
#define __DWIVEWS_CWK_TI_CWOCK__

stwuct cwk_omap_dividew {
	stwuct cwk_hw		hw;
	stwuct cwk_omap_weg	weg;
	u8			shift;
	u8			fwags;
	s8			watch;
	u16			min;
	u16			max;
	u16			mask;
	const stwuct cwk_div_tabwe	*tabwe;
	u32		context;
};

#define to_cwk_omap_dividew(_hw) containew_of(_hw, stwuct cwk_omap_dividew, hw)

stwuct cwk_omap_mux {
	stwuct cwk_hw		hw;
	stwuct cwk_omap_weg	weg;
	u32			*tabwe;
	u32			mask;
	u8			shift;
	s8			watch;
	u8			fwags;
	u8			saved_pawent;
};

#define to_cwk_omap_mux(_hw) containew_of(_hw, stwuct cwk_omap_mux, hw)

enum {
	TI_CWK_FIXED,
	TI_CWK_MUX,
	TI_CWK_DIVIDEW,
	TI_CWK_COMPOSITE,
	TI_CWK_FIXED_FACTOW,
	TI_CWK_GATE,
	TI_CWK_DPWW,
};

/* Gwobaw fwags */
#define CWKF_INDEX_POWEW_OF_TWO		(1 << 0)
#define CWKF_INDEX_STAWTS_AT_ONE	(1 << 1)
#define CWKF_SET_WATE_PAWENT		(1 << 2)
#define CWKF_OMAP3			(1 << 3)
#define CWKF_AM35XX			(1 << 4)

/* Gate fwags */
#define CWKF_SET_BIT_TO_DISABWE		(1 << 5)
#define CWKF_INTEWFACE			(1 << 6)
#define CWKF_SSI			(1 << 7)
#define CWKF_DSS			(1 << 8)
#define CWKF_HSOTGUSB			(1 << 9)
#define CWKF_WAIT			(1 << 10)
#define CWKF_NO_WAIT			(1 << 11)
#define CWKF_HSDIV			(1 << 12)
#define CWKF_CWKDM			(1 << 13)

/* DPWW fwags */
#define CWKF_WOW_POWEW_STOP		(1 << 5)
#define CWKF_WOCK			(1 << 6)
#define CWKF_WOW_POWEW_BYPASS		(1 << 7)
#define CWKF_PEW			(1 << 8)
#define CWKF_COWE			(1 << 9)
#define CWKF_J_TYPE			(1 << 10)

/* CWKCTWW fwags */
#define CWKF_SW_SUP			BIT(5)
#define CWKF_HW_SUP			BIT(6)
#define CWKF_NO_IDWEST			BIT(7)

#define CWKF_SOC_MASK			GENMASK(11, 8)

#define CWKF_SOC_NONSEC			BIT(8)
#define CWKF_SOC_DWA72			BIT(9)
#define CWKF_SOC_DWA74			BIT(10)
#define CWKF_SOC_DWA76			BIT(11)

#define CWK(dev, con, ck)		\
	{				\
		.wk = {			\
			.dev_id = dev,	\
			.con_id = con,	\
		},			\
		.cwk = ck,		\
	}

stwuct ti_cwk {
	const chaw *name;
	const chaw *cwkdm_name;
	int type;
	void *data;
	stwuct ti_cwk *patch;
	stwuct cwk *cwk;
};

stwuct ti_cwk_mux {
	u8 bit_shift;
	int num_pawents;
	u16 weg;
	u8 moduwe;
	const chaw * const *pawents;
	u16 fwags;
};

stwuct ti_cwk_dividew {
	const chaw *pawent;
	u8 bit_shift;
	u16 max_div;
	u16 weg;
	u8 moduwe;
	int *dividews;
	int num_dividews;
	u16 fwags;
};

stwuct ti_cwk_gate {
	const chaw *pawent;
	u8 bit_shift;
	u16 weg;
	u8 moduwe;
	u16 fwags;
};

/* Composite cwock component types */
enum {
	CWK_COMPONENT_TYPE_GATE = 0,
	CWK_COMPONENT_TYPE_DIVIDEW,
	CWK_COMPONENT_TYPE_MUX,
	CWK_COMPONENT_TYPE_MAX,
};

/**
 * stwuct ti_dt_cwk - OMAP DT cwock awias decwawations
 * @wk: cwock wookup definition
 * @node_name: cwock DT node to map to
 */
stwuct ti_dt_cwk {
	stwuct cwk_wookup		wk;
	chaw				*node_name;
};

#define DT_CWK(dev, con, name)		\
	{				\
		.wk = {			\
			.dev_id = dev,	\
			.con_id = con,	\
		},			\
		.node_name = name,	\
	}

/* CWKCTWW type definitions */
stwuct omap_cwkctww_div_data {
	const int *dividews;
	int max_div;
	u32 fwags;
};

stwuct omap_cwkctww_bit_data {
	u8 bit;
	u8 type;
	const chaw * const *pawents;
	const void *data;
};

stwuct omap_cwkctww_weg_data {
	u16 offset;
	const stwuct omap_cwkctww_bit_data *bit_data;
	u16 fwags;
	const chaw *pawent;
	const chaw *cwkdm_name;
};

stwuct omap_cwkctww_data {
	u32 addw;
	const stwuct omap_cwkctww_weg_data *wegs;
};

extewn const stwuct omap_cwkctww_data omap4_cwkctww_data[];
extewn const stwuct omap_cwkctww_data omap5_cwkctww_data[];
extewn const stwuct omap_cwkctww_data dwa7_cwkctww_data[];
extewn const stwuct omap_cwkctww_data dwa7_cwkctww_compat_data[];
extewn stwuct ti_dt_cwk dwa7xx_compat_cwks[];
extewn const stwuct omap_cwkctww_data am3_cwkctww_data[];
extewn const stwuct omap_cwkctww_data am3_cwkctww_compat_data[];
extewn stwuct ti_dt_cwk am33xx_compat_cwks[];
extewn const stwuct omap_cwkctww_data am4_cwkctww_data[];
extewn const stwuct omap_cwkctww_data am438x_cwkctww_data[];
extewn const stwuct omap_cwkctww_data dm814_cwkctww_data[];
extewn const stwuct omap_cwkctww_data dm816_cwkctww_data[];

typedef void (*ti_of_cwk_init_cb_t)(void *, stwuct device_node *);

stwuct cwk *of_ti_cwk_wegistew(stwuct device_node *node, stwuct cwk_hw *hw,
			       const chaw *con);
stwuct cwk *of_ti_cwk_wegistew_omap_hw(stwuct device_node *node,
				       stwuct cwk_hw *hw, const chaw *con);
const chaw *ti_dt_cwk_name(stwuct device_node *np);
int ti_cwk_add_awias(stwuct cwk *cwk, const chaw *con);
void ti_cwk_add_awiases(void);

void ti_cwk_watch(stwuct cwk_omap_weg *weg, s8 shift);

stwuct cwk_hw *ti_cwk_buiwd_component_mux(stwuct ti_cwk_mux *setup);

int ti_cwk_pawse_dividew_data(int *div_tabwe, int num_dividews, int max_div,
			      u8 fwags, stwuct cwk_omap_dividew *div);

int ti_cwk_get_weg_addw(stwuct device_node *node, int index,
			stwuct cwk_omap_weg *weg);
void ti_dt_cwocks_wegistew(stwuct ti_dt_cwk *ocwks);
int ti_cwk_wetwy_init(stwuct device_node *node, void *usew,
		      ti_of_cwk_init_cb_t func);
int ti_cwk_add_component(stwuct device_node *node, stwuct cwk_hw *hw, int type);

int of_ti_cwk_autoidwe_setup(stwuct device_node *node);
void omap2_cwk_enabwe_init_cwocks(const chaw **cwk_names, u8 num_cwocks);

extewn const stwuct cwk_hw_omap_ops cwkhwops_omap3_dpww;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap4_dpwwmx;
extewn const stwuct cwk_hw_omap_ops cwkhwops_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_icwk;
extewn const stwuct cwk_hw_omap_ops cwkhwops_icwk_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap2430_i2chs_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_dss_usbhost_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_hsotgusb_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_dss_usbhost_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_ssi_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_am35xx_ipss_moduwe_wait;
extewn const stwuct cwk_hw_omap_ops cwkhwops_am35xx_ipss_wait;

extewn const stwuct cwk_ops ti_cwk_dividew_ops;
extewn const stwuct cwk_ops ti_cwk_mux_ops;
extewn const stwuct cwk_ops omap_gate_cwk_ops;

extewn stwuct ti_cwk_featuwes ti_cwk_featuwes;

int omap2_init_cwk_cwkdm(stwuct cwk_hw *hw);
int omap2_cwkops_enabwe_cwkdm(stwuct cwk_hw *hw);
void omap2_cwkops_disabwe_cwkdm(stwuct cwk_hw *hw);

int omap2_dfwt_cwk_enabwe(stwuct cwk_hw *hw);
void omap2_dfwt_cwk_disabwe(stwuct cwk_hw *hw);
int omap2_dfwt_cwk_is_enabwed(stwuct cwk_hw *hw);
void omap2_cwk_dfwt_find_companion(stwuct cwk_hw_omap *cwk,
				   stwuct cwk_omap_weg *othew_weg,
				   u8 *othew_bit);
void omap2_cwk_dfwt_find_idwest(stwuct cwk_hw_omap *cwk,
				stwuct cwk_omap_weg *idwest_weg,
				u8 *idwest_bit, u8 *idwest_vaw);

void omap2_cwkt_icwk_awwow_idwe(stwuct cwk_hw_omap *cwk);
void omap2_cwkt_icwk_deny_idwe(stwuct cwk_hw_omap *cwk);

u8 omap2_init_dpww_pawent(stwuct cwk_hw *hw);
int omap3_noncowe_dpww_enabwe(stwuct cwk_hw *hw);
void omap3_noncowe_dpww_disabwe(stwuct cwk_hw *hw);
int omap3_noncowe_dpww_set_pawent(stwuct cwk_hw *hw, u8 index);
int omap3_noncowe_dpww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate);
int omap3_noncowe_dpww_set_wate_and_pawent(stwuct cwk_hw *hw,
					   unsigned wong wate,
					   unsigned wong pawent_wate,
					   u8 index);
int omap3_noncowe_dpww_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq);
wong omap2_dpww_wound_wate(stwuct cwk_hw *hw, unsigned wong tawget_wate,
			   unsigned wong *pawent_wate);
unsigned wong omap3_cwkoutx2_wecawc(stwuct cwk_hw *hw,
				    unsigned wong pawent_wate);

/*
 * OMAP3_DPWW5_FWEQ_FOW_USBHOST: USBHOST and USBTWW awe the onwy cwocks
 * that awe souwced by DPWW5, and both of these wequiwe this cwock
 * to be at 120 MHz fow pwopew opewation.
 */
#define OMAP3_DPWW5_FWEQ_FOW_USBHOST	120000000

unsigned wong omap3_dpww_wecawc(stwuct cwk_hw *hw, unsigned wong pawent_wate);
int omap3_dpww4_set_wate(stwuct cwk_hw *cwk, unsigned wong wate,
			 unsigned wong pawent_wate);
int omap3_dpww4_set_wate_and_pawent(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate, u8 index);
int omap3_dpww5_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			 unsigned wong pawent_wate);
void omap3_cwk_wock_dpww5(void);

unsigned wong omap4_dpww_wegm4xen_wecawc(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate);
wong omap4_dpww_wegm4xen_wound_wate(stwuct cwk_hw *hw,
				    unsigned wong tawget_wate,
				    unsigned wong *pawent_wate);
int omap4_dpww_wegm4xen_detewmine_wate(stwuct cwk_hw *hw,
				       stwuct cwk_wate_wequest *weq);
int omap2_cwk_fow_each(int (*fn)(stwuct cwk_hw_omap *hw));

extewn stwuct ti_cwk_ww_ops *ti_cwk_ww_ops;

#endif
