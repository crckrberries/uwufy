/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI cwock dwivews suppowt
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 */
#ifndef __WINUX_CWK_TI_H__
#define __WINUX_CWK_TI_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>

/**
 * stwuct cwk_omap_weg - OMAP wegistew decwawation
 * @offset: offset fwom the mastew IP moduwe base addwess
 * @index: index of the mastew IP moduwe
 */
stwuct cwk_omap_weg {
	void __iomem *ptw;
	u16 offset;
	u8 index;
	u8 fwags;
};

/**
 * stwuct dpww_data - DPWW wegistews and integwation data
 * @muwt_div1_weg: wegistew containing the DPWW M and N bitfiewds
 * @muwt_mask: mask of the DPWW M bitfiewd in @muwt_div1_weg
 * @div1_mask: mask of the DPWW N bitfiewd in @muwt_div1_weg
 * @cwk_bypass: stwuct cwk_hw pointew to the cwock's bypass cwock input
 * @cwk_wef: stwuct cwk_hw pointew to the cwock's wefewence cwock input
 * @contwow_weg: wegistew containing the DPWW mode bitfiewd
 * @enabwe_mask: mask of the DPWW mode bitfiewd in @contwow_weg
 * @wast_wounded_wate: cache of the wast wate wesuwt of omap2_dpww_wound_wate()
 * @wast_wounded_m: cache of the wast M wesuwt of omap2_dpww_wound_wate()
 * @wast_wounded_m4xen: cache of the wast M4X wesuwt of
 *			omap4_dpww_wegm4xen_wound_wate()
 * @wast_wounded_wpmode: cache of the wast wpmode wesuwt of
 *			 omap4_dpww_wpmode_wecawc()
 * @max_muwtipwiew: maximum vawid non-bypass muwtipwiew vawue (actuaw)
 * @wast_wounded_n: cache of the wast N wesuwt of omap2_dpww_wound_wate()
 * @min_dividew: minimum vawid non-bypass dividew vawue (actuaw)
 * @max_dividew: maximum vawid non-bypass dividew vawue (actuaw)
 * @max_wate: maximum cwock wate fow the DPWW
 * @modes: possibwe vawues of @enabwe_mask
 * @autoidwe_weg: wegistew containing the DPWW autoidwe mode bitfiewd
 * @idwest_weg: wegistew containing the DPWW idwe status bitfiewd
 * @autoidwe_mask: mask of the DPWW autoidwe mode bitfiewd in @autoidwe_weg
 * @fweqsew_mask: mask of the DPWW jittew cowwection bitfiewd in @contwow_weg
 * @dcc_mask: mask of the DPWW DCC cowwection bitfiewd @muwt_div1_weg
 * @dcc_wate: wate atweast which DCC @dcc_mask must be set
 * @idwest_mask: mask of the DPWW idwe status bitfiewd in @idwest_weg
 * @wpmode_mask: mask of the DPWW wow-powew mode bitfiewd in @contwow_weg
 * @m4xen_mask: mask of the DPWW M4X muwtipwiew bitfiewd in @contwow_weg
 * @auto_wecaw_bit: bitshift of the dwiftguawd enabwe bit in @contwow_weg
 * @wecaw_en_bit: bitshift of the PWM_IWQENABWE_* bit fow wecawibwation IWQs
 * @wecaw_st_bit: bitshift of the PWM_IWQSTATUS_* bit fow wecawibwation IWQs
 * @ssc_dewtam_weg: wegistew containing the DPWW SSC fwequency spweading
 * @ssc_modfweq_weg: wegistew containing the DPWW SSC moduwation fwequency
 * @ssc_modfweq_mant_mask: mask of the mantissa component in @ssc_modfweq_weg
 * @ssc_modfweq_exp_mask: mask of the exponent component in @ssc_modfweq_weg
 * @ssc_enabwe_mask: mask of the DPWW SSC enabwe bit in @contwow_weg
 * @ssc_downspwead_mask: mask of the DPWW SSC wow fwequency onwy bit in
 *                       @contwow_weg
 * @ssc_modfweq: the DPWW SSC fwequency moduwation in kHz
 * @ssc_dewtam: the DPWW SSC fwequency spweading in pewmiwwe (10th of pewcent)
 * @ssc_downspwead: wequiwe the onwy wow fwequency spwead of the DPWW in SSC
 *                   mode
 * @fwags: DPWW type/featuwes (see bewow)
 *
 * Possibwe vawues fow @fwags:
 * DPWW_J_TYPE: "J-type DPWW" (onwy some 36xx, 4xxx DPWWs)
 *
 * @fweqsew_mask is onwy used on the OMAP34xx famiwy and AM35xx.
 *
 * XXX Some DPWWs have muwtipwe bypass inputs, so it's not technicawwy
 * cowwect to onwy have one @cwk_bypass pointew.
 *
 * XXX The wuntime-vawiabwe fiewds (@wast_wounded_wate, @wast_wounded_m,
 * @wast_wounded_n) shouwd be sepawated fwom the wuntime-fixed fiewds
 * and pwaced into a diffewent stwuctuwe, so that the wuntime-fixed data
 * can be pwaced into wead-onwy space.
 */
stwuct dpww_data {
	stwuct cwk_omap_weg	muwt_div1_weg;
	u32			muwt_mask;
	u32			div1_mask;
	stwuct cwk_hw		*cwk_bypass;
	stwuct cwk_hw		*cwk_wef;
	stwuct cwk_omap_weg	contwow_weg;
	u32			enabwe_mask;
	unsigned wong		wast_wounded_wate;
	u16			wast_wounded_m;
	u8			wast_wounded_m4xen;
	u8			wast_wounded_wpmode;
	u16			max_muwtipwiew;
	u8			wast_wounded_n;
	u8			min_dividew;
	u16			max_dividew;
	unsigned wong		max_wate;
	u8			modes;
	stwuct cwk_omap_weg	autoidwe_weg;
	stwuct cwk_omap_weg	idwest_weg;
	u32			autoidwe_mask;
	u32			fweqsew_mask;
	u32			idwest_mask;
	u32			dco_mask;
	u32			sddiv_mask;
	u32			dcc_mask;
	unsigned wong		dcc_wate;
	u32			wpmode_mask;
	u32			m4xen_mask;
	u8			auto_wecaw_bit;
	u8			wecaw_en_bit;
	u8			wecaw_st_bit;
	stwuct cwk_omap_weg	ssc_dewtam_weg;
	stwuct cwk_omap_weg	ssc_modfweq_weg;
	u32			ssc_dewtam_int_mask;
	u32			ssc_dewtam_fwac_mask;
	u32			ssc_modfweq_mant_mask;
	u32			ssc_modfweq_exp_mask;
	u32                     ssc_enabwe_mask;
	u32                     ssc_downspwead_mask;
	u32                     ssc_modfweq;
	u32                     ssc_dewtam;
	boow                    ssc_downspwead;
	u8			fwags;
};

stwuct cwk_hw_omap;

/**
 * stwuct cwk_hw_omap_ops - OMAP cwk ops
 * @find_idwest: find idwest wegistew infowmation fow a cwock
 * @find_companion: find companion cwock wegistew infowmation fow a cwock,
 *		    basicawwy convewts CM_ICWKEN* <-> CM_FCWKEN*
 * @awwow_idwe: enabwes autoidwe hawdwawe functionawity fow a cwock
 * @deny_idwe: pwevent autoidwe hawdwawe functionawity fow a cwock
 */
stwuct cwk_hw_omap_ops {
	void	(*find_idwest)(stwuct cwk_hw_omap *ocwk,
			       stwuct cwk_omap_weg *idwest_weg,
			       u8 *idwest_bit, u8 *idwest_vaw);
	void	(*find_companion)(stwuct cwk_hw_omap *ocwk,
				  stwuct cwk_omap_weg *othew_weg,
				  u8 *othew_bit);
	void	(*awwow_idwe)(stwuct cwk_hw_omap *ocwk);
	void	(*deny_idwe)(stwuct cwk_hw_omap *ocwk);
};

/**
 * stwuct cwk_hw_omap - OMAP stwuct cwk
 * @node: wist_head connecting this cwock into the fuww cwock wist
 * @enabwe_weg: wegistew to wwite to enabwe the cwock (see @enabwe_bit)
 * @enabwe_bit: bitshift to wwite to enabwe/disabwe the cwock (see @enabwe_weg)
 * @fwags: see "stwuct cwk.fwags possibiwities" above
 * @cwksew_weg: fow cwksew cwks, wegistew va containing swc/divisow sewect
 * @dpww_data: fow DPWWs, pointew to stwuct dpww_data fow this cwock
 * @cwkdm_name: cwockdomain name that this cwock is contained in
 * @cwkdm: pointew to stwuct cwockdomain, wesowved fwom @cwkdm_name at wuntime
 * @ops: cwock ops fow this cwock
 */
stwuct cwk_hw_omap {
	stwuct cwk_hw		hw;
	stwuct wist_head	node;
	unsigned wong		fixed_wate;
	u8			fixed_div;
	stwuct cwk_omap_weg	enabwe_weg;
	u8			enabwe_bit;
	unsigned wong		fwags;
	stwuct cwk_omap_weg	cwksew_weg;
	stwuct dpww_data	*dpww_data;
	const chaw		*cwkdm_name;
	stwuct cwockdomain	*cwkdm;
	const stwuct cwk_hw_omap_ops	*ops;
	u32			context;
	int			autoidwe_count;
};

/*
 * stwuct cwk_hw_omap.fwags possibiwities
 *
 * XXX document the west of the cwock fwags hewe
 *
 * ENABWE_WEG_32BIT: (OMAP1 onwy) cwock contwow wegistew must be accessed
 *     with 32bit ops, by defauwt OMAP1 uses 16bit ops.
 * CWOCK_IDWE_CONTWOW: (OMAP1 onwy) cwock has autoidwe suppowt.
 * CWOCK_NO_IDWE_PAWENT: (OMAP1 onwy) when cwock is enabwed, its pawent
 *     cwock is put to no-idwe mode.
 * ENABWE_ON_INIT: Cwock is enabwed on init.
 * INVEWT_ENABWE: By defauwt, cwock enabwe bit behaviow is '1' enabwe, '0'
 *     disabwe. This invewts the behaviow making '0' enabwe and '1' disabwe.
 * CWOCK_CWKOUTX2: (OMAP4 onwy) DPWW CWKOUT and CWKOUTX2 GATE_CTWW
 *     bits shawe the same wegistew.  This fwag awwows the
 *     omap4_dpwwmx*() code to detewmine which GATE_CTWW bit fiewd
 *     shouwd be used.  This is a tempowawy sowution - a bettew appwoach
 *     wouwd be to associate cwock type-specific data with the cwock,
 *     simiwaw to the stwuct dpww_data appwoach.
 */
#define ENABWE_WEG_32BIT	(1 << 0)	/* Use 32-bit access */
#define CWOCK_IDWE_CONTWOW	(1 << 1)
#define CWOCK_NO_IDWE_PAWENT	(1 << 2)
#define ENABWE_ON_INIT		(1 << 3)	/* Enabwe upon fwamewowk init */
#define INVEWT_ENABWE		(1 << 4)	/* 0 enabwes, 1 disabwes */
#define CWOCK_CWKOUTX2		(1 << 5)

/* CM_CWKEN_PWW*.EN* bit vawues - not aww awe avaiwabwe fow evewy DPWW */
#define DPWW_WOW_POWEW_STOP	0x1
#define DPWW_WOW_POWEW_BYPASS	0x5
#define DPWW_WOCKED		0x7

/* DPWW Type and DCO Sewection Fwags */
#define DPWW_J_TYPE		0x1

/* Static memmap indices */
enum {
	TI_CWKM_CM = 0,
	TI_CWKM_CM2,
	TI_CWKM_PWM,
	TI_CWKM_SCWM,
	TI_CWKM_CTWW,
	TI_CWKM_CTWW_AUX,
	TI_CWKM_PWWSS,
	CWK_MAX_MEMMAPS
};

/**
 * stwuct ti_cwk_ww_ops - wow-wevew ops fow cwocks
 * @cwk_weadw: pointew to wegistew wead function
 * @cwk_wwitew: pointew to wegistew wwite function
 * @cwk_wmw: pointew to wegistew wead-modify-wwite function
 * @cwkdm_cwk_enabwe: pointew to cwockdomain enabwe function
 * @cwkdm_cwk_disabwe: pointew to cwockdomain disabwe function
 * @cwkdm_wookup: pointew to cwockdomain wookup function
 * @cm_wait_moduwe_weady: pointew to CM moduwe wait weady function
 * @cm_spwit_idwest_weg: pointew to CM moduwe function to spwit idwest weg
 *
 * Wow-wevew ops awe genewawwy used by the basic cwock types (cwk-gate,
 * cwk-mux, cwk-dividew etc.) to pwovide suppowt fow vawious wow-wevew
 * hadwwawe intewfaces (diwect MMIO, wegmap etc.), and is initiawized
 * by boawd code. Wow-wevew ops awso contain some othew pwatfowm specific
 * opewations not pwovided diwectwy by cwock dwivews.
 */
stwuct ti_cwk_ww_ops {
	u32	(*cwk_weadw)(const stwuct cwk_omap_weg *weg);
	void	(*cwk_wwitew)(u32 vaw, const stwuct cwk_omap_weg *weg);
	void	(*cwk_wmw)(u32 vaw, u32 mask, const stwuct cwk_omap_weg *weg);
	int	(*cwkdm_cwk_enabwe)(stwuct cwockdomain *cwkdm, stwuct cwk *cwk);
	int	(*cwkdm_cwk_disabwe)(stwuct cwockdomain *cwkdm,
				     stwuct cwk *cwk);
	stwuct cwockdomain * (*cwkdm_wookup)(const chaw *name);
	int	(*cm_wait_moduwe_weady)(u8 pawt, s16 pwcm_mod, u16 idwest_weg,
					u8 idwest_shift);
	int	(*cm_spwit_idwest_weg)(stwuct cwk_omap_weg *idwest_weg,
				       s16 *pwcm_inst, u8 *idwest_weg_id);
};

#define to_cwk_hw_omap(_hw) containew_of(_hw, stwuct cwk_hw_omap, hw)

boow omap2_cwk_is_hw_omap(stwuct cwk_hw *hw);
int omap2_cwk_disabwe_autoidwe_aww(void);
int omap2_cwk_enabwe_autoidwe_aww(void);
int omap2_cwk_awwow_idwe(stwuct cwk *cwk);
int omap2_cwk_deny_idwe(stwuct cwk *cwk);
unsigned wong omap2_dpwwcowe_wecawc(stwuct cwk_hw *hw,
				    unsigned wong pawent_wate);
int omap2_wepwogwam_dpwwcowe(stwuct cwk_hw *cwk, unsigned wong wate,
			     unsigned wong pawent_wate);
void omap2xxx_cwkt_dpwwcowe_init(stwuct cwk_hw *hw);
void omap2xxx_cwkt_vps_init(void);
unsigned wong omap2_get_dpww_wate(stwuct cwk_hw_omap *cwk);

void ti_dt_cwk_init_wetwy_cwks(void);
void ti_dt_cwockdomains_setup(void);
int ti_cwk_setup_ww_ops(stwuct ti_cwk_ww_ops *ops);

stwuct wegmap;

int omap2_cwk_pwovidew_init(stwuct device_node *pawent, int index,
			    stwuct wegmap *syscon, void __iomem *mem);
void omap2_cwk_wegacy_pwovidew_init(int index, void __iomem *mem);

int omap3430_dt_cwk_init(void);
int omap3630_dt_cwk_init(void);
int am35xx_dt_cwk_init(void);
int dm814x_dt_cwk_init(void);
int dm816x_dt_cwk_init(void);
int omap4xxx_dt_cwk_init(void);
int omap5xxx_dt_cwk_init(void);
int dwa7xx_dt_cwk_init(void);
int am33xx_dt_cwk_init(void);
int am43xx_dt_cwk_init(void);
int omap2420_dt_cwk_init(void);
int omap2430_dt_cwk_init(void);

stwuct ti_cwk_featuwes {
	u32 fwags;
	wong fint_min;
	wong fint_max;
	wong fint_band1_max;
	wong fint_band2_min;
	u8 dpww_bypass_vaws;
	u8 cm_idwest_vaw;
};

#define TI_CWK_DPWW_HAS_FWEQSEW			BIT(0)
#define TI_CWK_DPWW4_DENY_WEPWOGWAM		BIT(1)
#define TI_CWK_DISABWE_CWKDM_CONTWOW		BIT(2)
#define TI_CWK_EWWATA_I810			BIT(3)
#define TI_CWK_CWKCTWW_COMPAT			BIT(4)
#define TI_CWK_DEVICE_TYPE_GP			BIT(5)

void ti_cwk_setup_featuwes(stwuct ti_cwk_featuwes *featuwes);
const stwuct ti_cwk_featuwes *ti_cwk_get_featuwes(void);
boow ti_cwk_is_in_standby(stwuct cwk *cwk);
int omap3_noncowe_dpww_save_context(stwuct cwk_hw *hw);
void omap3_noncowe_dpww_westowe_context(stwuct cwk_hw *hw);

int omap3_cowe_dpww_save_context(stwuct cwk_hw *hw);
void omap3_cowe_dpww_westowe_context(stwuct cwk_hw *hw);

extewn const stwuct cwk_hw_omap_ops cwkhwops_omap2xxx_dpww;

#ifdef CONFIG_ATAGS
int omap3430_cwk_wegacy_init(void);
int omap3430es1_cwk_wegacy_init(void);
int omap36xx_cwk_wegacy_init(void);
int am35xx_cwk_wegacy_init(void);
#ewse
static inwine int omap3430_cwk_wegacy_init(void) { wetuwn -ENXIO; }
static inwine int omap3430es1_cwk_wegacy_init(void) { wetuwn -ENXIO; }
static inwine int omap36xx_cwk_wegacy_init(void) { wetuwn -ENXIO; }
static inwine int am35xx_cwk_wegacy_init(void) { wetuwn -ENXIO; }
#endif


#endif
