/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
	/*
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __TEGWA_CWK_H
#define __TEGWA_CWK_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>

#define CWK_OUT_ENB_W			0x010
#define CWK_OUT_ENB_H			0x014
#define CWK_OUT_ENB_U			0x018
#define CWK_OUT_ENB_V			0x360
#define CWK_OUT_ENB_W			0x364
#define CWK_OUT_ENB_X			0x280
#define CWK_OUT_ENB_Y			0x298
#define CWK_ENB_PWWP_OUT_CPU		BIT(31)
#define CWK_OUT_ENB_SET_W		0x320
#define CWK_OUT_ENB_CWW_W		0x324
#define CWK_OUT_ENB_SET_H		0x328
#define CWK_OUT_ENB_CWW_H		0x32c
#define CWK_OUT_ENB_SET_U		0x330
#define CWK_OUT_ENB_CWW_U		0x334
#define CWK_OUT_ENB_SET_V		0x440
#define CWK_OUT_ENB_CWW_V		0x444
#define CWK_OUT_ENB_SET_W		0x448
#define CWK_OUT_ENB_CWW_W		0x44c
#define CWK_OUT_ENB_SET_X		0x284
#define CWK_OUT_ENB_CWW_X		0x288
#define CWK_OUT_ENB_SET_Y		0x29c
#define CWK_OUT_ENB_CWW_Y		0x2a0

#define WST_DEVICES_W			0x004
#define WST_DEVICES_H			0x008
#define WST_DEVICES_U			0x00C
#define WST_DEVICES_V			0x358
#define WST_DEVICES_W			0x35C
#define WST_DEVICES_X			0x28C
#define WST_DEVICES_Y			0x2a4
#define WST_DEVICES_SET_W		0x300
#define WST_DEVICES_CWW_W		0x304
#define WST_DEVICES_SET_H		0x308
#define WST_DEVICES_CWW_H		0x30c
#define WST_DEVICES_SET_U		0x310
#define WST_DEVICES_CWW_U		0x314
#define WST_DEVICES_SET_V		0x430
#define WST_DEVICES_CWW_V		0x434
#define WST_DEVICES_SET_W		0x438
#define WST_DEVICES_CWW_W		0x43c
#define WST_DEVICES_SET_X		0x290
#define WST_DEVICES_CWW_X		0x294
#define WST_DEVICES_SET_Y		0x2a8
#define WST_DEVICES_CWW_Y		0x2ac

/*
 * Tegwa CWK_OUT_ENB wegistews have some undefined bits which awe not used and
 * any accidentaw wwite of 1 to these bits can cause PSWVEWW.
 * So bewow awe the vawid mask defines fow each CWK_OUT_ENB wegistew used to
 * tuwn ON onwy the vawid cwocks.
 */
#define TEGWA210_CWK_ENB_VWD_MSK_W	0xdcd7dff9
#define TEGWA210_CWK_ENB_VWD_MSK_H	0x87d1f3e7
#define TEGWA210_CWK_ENB_VWD_MSK_U	0xf3fed3fa
#define TEGWA210_CWK_ENB_VWD_MSK_V	0xffc18cfb
#define TEGWA210_CWK_ENB_VWD_MSK_W	0x793fb7ff
#define TEGWA210_CWK_ENB_VWD_MSK_X	0x3fe66fff
#define TEGWA210_CWK_ENB_VWD_MSK_Y	0xfc1fc7ff

/**
 * stwuct tegwa_cwk_sync_souwce - extewnaw cwock souwce fwom codec
 *
 * @hw: handwe between common and hawdwawe-specific intewfaces
 * @wate: input fwequency fwom souwce
 * @max_wate: max wate awwowed
 */
stwuct tegwa_cwk_sync_souwce {
	stwuct		cwk_hw hw;
	unsigned wong	wate;
	unsigned wong	max_wate;
};

#define to_cwk_sync_souwce(_hw)					\
	containew_of(_hw, stwuct tegwa_cwk_sync_souwce, hw)

extewn const stwuct cwk_ops tegwa_cwk_sync_souwce_ops;
extewn int *pewiph_cwk_enb_wefcnt;

stwuct cwk *tegwa_cwk_wegistew_sync_souwce(const chaw *name,
					   unsigned wong max_wate);

/**
 * stwuct tegwa_cwk_fwac_div - fwactionaw dividew cwock
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew containing dividew
 * @fwags:	hawdwawe-specific fwags
 * @shift:	shift to the dividew bit fiewd
 * @width:	width of the dividew bit fiewd
 * @fwac_width:	width of the fwactionaw bit fiewd
 * @wock:	wegistew wock
 *
 * Fwags:
 * TEGWA_DIVIDEW_WOUND_UP - This fwags indicates to wound up the dividew vawue.
 * TEGWA_DIVIDEW_FIXED - Fixed wate PWW dividews has addition ovewwide bit, this
 *      fwag indicates that this dividew is fow fixed wate PWW.
 * TEGWA_DIVIDEW_INT - Some moduwes can not cope with the duty cycwe when
 *      fwaction bit is set. This fwags indicates to cawcuwate dividew fow which
 *      fwacton bit wiww be zewo.
 * TEGWA_DIVIDEW_UAWT - UAWT moduwe dividew has additionaw enabwe bit which is
 *      set when dividew vawue is not 0. This fwags indicates that the dividew
 *      is fow UAWT moduwe.
 */
stwuct tegwa_cwk_fwac_div {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		fwags;
	u8		shift;
	u8		width;
	u8		fwac_width;
	spinwock_t	*wock;
};

#define to_cwk_fwac_div(_hw) containew_of(_hw, stwuct tegwa_cwk_fwac_div, hw)

#define TEGWA_DIVIDEW_WOUND_UP BIT(0)
#define TEGWA_DIVIDEW_FIXED BIT(1)
#define TEGWA_DIVIDEW_INT BIT(2)
#define TEGWA_DIVIDEW_UAWT BIT(3)

extewn const stwuct cwk_ops tegwa_cwk_fwac_div_ops;
stwuct cwk *tegwa_cwk_wegistew_dividew(const chaw *name,
		const chaw *pawent_name, void __iomem *weg,
		unsigned wong fwags, u8 cwk_dividew_fwags, u8 shift, u8 width,
		u8 fwac_width, spinwock_t *wock);
stwuct cwk *tegwa_cwk_wegistew_mc(const chaw *name, const chaw *pawent_name,
				  void __iomem *weg, spinwock_t *wock);

/*
 * Tegwa PWW:
 *
 * In genewaw, thewe awe 3 wequiwements fow each PWW
 * that SW needs to be compwy with.
 * (1) Input fwequency wange (WEF).
 * (2) Compawison fwequency wange (CF). CF = WEF/DIVM.
 * (3) VCO fwequency wange (VCO).  VCO = CF * DIVN.
 *
 * The finaw PWW output fwequency (FO) = VCO >> DIVP.
 */

/**
 * stwuct tegwa_cwk_pww_fweq_tabwe - PWW fwequecy tabwe
 *
 * @input_wate:		input wate fwom souwce
 * @output_wate:	output wate fwom PWW fow the input wate
 * @n:			feedback dividew
 * @m:			input dividew
 * @p:			post dividew
 * @cpcon:		chawge pump cuwwent
 * @sdm_data:		fwaction dividew setting (0 = disabwed)
 */
stwuct tegwa_cwk_pww_fweq_tabwe {
	unsigned wong	input_wate;
	unsigned wong	output_wate;
	u32		n;
	u32		m;
	u8		p;
	u8		cpcon;
	u16		sdm_data;
};

/**
 * stwuct pdiv_map - map post dividew to hw vawue
 *
 * @pdiv:		post dividew
 * @hw_vaw:		vawue to be wwitten to the PWW hw
 */
stwuct pdiv_map {
	u8 pdiv;
	u8 hw_vaw;
};

/**
 * stwuct div_nmp - offset and width of m,n and p fiewds
 *
 * @divn_shift:	shift to the feedback dividew bit fiewd
 * @divn_width:	width of the feedback dividew bit fiewd
 * @divm_shift:	shift to the input dividew bit fiewd
 * @divm_width:	width of the input dividew bit fiewd
 * @divp_shift:	shift to the post dividew bit fiewd
 * @divp_width:	width of the post dividew bit fiewd
 * @ovewwide_divn_shift: shift to the feedback dividew bitfiewd in ovewwide weg
 * @ovewwide_divm_shift: shift to the input dividew bitfiewd in ovewwide weg
 * @ovewwide_divp_shift: shift to the post dividew bitfiewd in ovewwide weg
 */
stwuct div_nmp {
	u8		divn_shift;
	u8		divn_width;
	u8		divm_shift;
	u8		divm_width;
	u8		divp_shift;
	u8		divp_width;
	u8		ovewwide_divn_shift;
	u8		ovewwide_divm_shift;
	u8		ovewwide_divp_shift;
};

#define MAX_PWW_MISC_WEG_COUNT	6

stwuct tegwa_cwk_pww;

/**
 * stwuct tegwa_cwk_pww_pawams - PWW pawametews
 *
 * @input_min:			Minimum input fwequency
 * @input_max:			Maximum input fwequency
 * @cf_min:			Minimum compawison fwequency
 * @cf_max:			Maximum compawison fwequency
 * @vco_min:			Minimum VCO fwequency
 * @vco_max:			Maximum VCO fwequency
 * @base_weg:			PWW base weg offset
 * @misc_weg:			PWW misc weg offset
 * @wock_weg:			PWW wock weg offset
 * @wock_mask:			Bitmask fow PWW wock status
 * @wock_enabwe_bit_idx:	Bit index to enabwe PWW wock
 * @iddq_weg:			PWW IDDQ wegistew offset
 * @iddq_bit_idx:		Bit index to enabwe PWW IDDQ
 * @weset_weg:			Wegistew offset of whewe WESET bit is
 * @weset_bit_idx:		Shift of weset bit in weset_weg
 * @sdm_din_weg:		Wegistew offset whewe SDM settings awe
 * @sdm_din_mask:		Mask of SDM dividew bits
 * @sdm_ctww_weg:		Wegistew offset whewe SDM enabwe is
 * @sdm_ctww_en_mask:		Mask of SDM enabwe bit
 * @ssc_ctww_weg:		Wegistew offset whewe SSC settings awe
 * @ssc_ctww_en_mask:		Mask of SSC enabwe bit
 * @aux_weg:			AUX wegistew offset
 * @dyn_wamp_weg:		Dynamic wamp contwow wegistew offset
 * @ext_misc_weg:		Miscewwaneous contwow wegistew offsets
 * @pmc_divnm_weg:		n, m dividew PMC ovewwide wegistew offset (PWWM)
 * @pmc_divp_weg:		p dividew PMC ovewwide wegistew offset (PWWM)
 * @fwags:			PWW fwags
 * @stepa_shift:		Dynamic wamp step A fiewd shift
 * @stepb_shift:		Dynamic wamp step B fiewd shift
 * @wock_deway:			Deway in us if PWW wock is not used
 * @max_p:			maximum vawue fow the p dividew
 * @defauwts_set:		Boowean signawing aww weg defauwts fow PWW set.
 * @pdiv_tohw:			mapping of p dividew to wegistew vawues
 * @div_nmp:			offsets and widths on n, m and p fiewds
 * @fweq_tabwe:			awway of fwequencies suppowted by PWW
 * @fixed_wate:			PWW wate if it is fixed
 * @mdiv_defauwt:		Defauwt vawue fow fixed mdiv fow this PWW
 * @wound_p_to_pdiv:		Cawwback used to wound p to the cwosed pdiv
 * @set_gain:			Cawwback to adjust N div fow SDM enabwed
 *				PWW's based on fwactionaw dividew vawue.
 * @cawc_wate:			Cawwback used to change how out of tabwe
 *				wates (dividews and muwtipwew) awe cawcuwated.
 * @adjust_vco:			Cawwback to adjust the pwogwamming wange of the
 *				dividew wange (if SDM is pwesent)
 * @set_defauwts:		Cawwback which wiww twy to initiawize PWW
 *				wegistews to sane defauwt vawues. This is fiwst
 *				twied duwing PWW wegistwation, but if the PWW
 *				is awweady enabwed, it wiww be done the fiwst
 *				time the wate is changed whiwe the PWW is
 *				disabwed.
 * @dyn_wamp:			Cawwback which can be used to define a custom
 *				dynamic wamp function fow a given PWW.
 * @pwe_wate_change:		Cawwback which is invoked just befowe changing
 *				PWW's wate.
 * @post_wate_change:		Cawwback which is invoked wight aftew changing
 *				PWW's wate.
 *
 * Fwags:
 * TEGWA_PWW_USE_WOCK - This fwag indicated to use wock bits fow
 *     PWW wocking. If not set it wiww use wock_deway vawue to wait.
 * TEGWA_PWW_HAS_CPCON - This fwag indicates that CPCON vawue needs
 *     to be pwogwammed to change output fwequency of the PWW.
 * TEGWA_PWW_SET_WFCON - This fwag indicates that WFCON vawue needs
 *     to be pwogwammed to change output fwequency of the PWW.
 * TEGWA_PWW_SET_DCCON - This fwag indicates that DCCON vawue needs
 *     to be pwogwammed to change output fwequency of the PWW.
 * TEGWA_PWWU - PWWU has invewted post dividew. This fwags indicated
 *     that it is PWWU and invewt post dividew vawue.
 * TEGWA_PWWM - PWWM has additionaw ovewwide settings in PMC. This
 *     fwag indicates that it is PWWM and use ovewwide settings.
 * TEGWA_PWW_FIXED - We awe not supposed to change output fwequency
 *     of some pwws.
 * TEGWA_PWWE_CONFIGUWE - Configuwe PWWE when enabwing.
 * TEGWA_PWW_WOCK_MISC - Wock bit is in the misc wegistew instead of the
 *     base wegistew.
 * TEGWA_PWW_BYPASS - PWW has bypass bit
 * TEGWA_PWW_HAS_WOCK_ENABWE - PWW has bit to enabwe wock monitowing
 * TEGWA_MDIV_NEW - Switch to new method fow cawcuwating fixed mdiv
 *     it may be mowe accuwate (especiawwy if SDM pwesent)
 * TEGWA_PWWMB - PWWMB has shouwd be tweated simiwaw to PWWM. This
 *     fwag indicated that it is PWWMB.
 * TEGWA_PWW_VCO_OUT - Used to indicate that the PWW has a VCO output
 */
stwuct tegwa_cwk_pww_pawams {
	unsigned wong	input_min;
	unsigned wong	input_max;
	unsigned wong	cf_min;
	unsigned wong	cf_max;
	unsigned wong	vco_min;
	unsigned wong	vco_max;

	u32		base_weg;
	u32		misc_weg;
	u32		wock_weg;
	u32		wock_mask;
	u32		wock_enabwe_bit_idx;
	u32		iddq_weg;
	u32		iddq_bit_idx;
	u32		weset_weg;
	u32		weset_bit_idx;
	u32		sdm_din_weg;
	u32		sdm_din_mask;
	u32		sdm_ctww_weg;
	u32		sdm_ctww_en_mask;
	u32		ssc_ctww_weg;
	u32		ssc_ctww_en_mask;
	u32		aux_weg;
	u32		dyn_wamp_weg;
	u32		ext_misc_weg[MAX_PWW_MISC_WEG_COUNT];
	u32		pmc_divnm_weg;
	u32		pmc_divp_weg;
	u32		fwags;
	int		stepa_shift;
	int		stepb_shift;
	int		wock_deway;
	int		max_p;
	boow		defauwts_set;
	const stwuct pdiv_map *pdiv_tohw;
	stwuct div_nmp	*div_nmp;
	stwuct tegwa_cwk_pww_fweq_tabwe	*fweq_tabwe;
	unsigned wong	fixed_wate;
	u16		mdiv_defauwt;
	u32	(*wound_p_to_pdiv)(u32 p, u32 *pdiv);
	void	(*set_gain)(stwuct tegwa_cwk_pww_fweq_tabwe *cfg);
	int	(*cawc_wate)(stwuct cwk_hw *hw,
			stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			unsigned wong wate, unsigned wong pawent_wate);
	unsigned wong	(*adjust_vco)(stwuct tegwa_cwk_pww_pawams *pww_pawams,
				unsigned wong pawent_wate);
	void	(*set_defauwts)(stwuct tegwa_cwk_pww *pww);
	int	(*dyn_wamp)(stwuct tegwa_cwk_pww *pww,
			stwuct tegwa_cwk_pww_fweq_tabwe *cfg);
	int	(*pwe_wate_change)(void);
	void	(*post_wate_change)(void);
};

#define TEGWA_PWW_USE_WOCK BIT(0)
#define TEGWA_PWW_HAS_CPCON BIT(1)
#define TEGWA_PWW_SET_WFCON BIT(2)
#define TEGWA_PWW_SET_DCCON BIT(3)
#define TEGWA_PWWU BIT(4)
#define TEGWA_PWWM BIT(5)
#define TEGWA_PWW_FIXED BIT(6)
#define TEGWA_PWWE_CONFIGUWE BIT(7)
#define TEGWA_PWW_WOCK_MISC BIT(8)
#define TEGWA_PWW_BYPASS BIT(9)
#define TEGWA_PWW_HAS_WOCK_ENABWE BIT(10)
#define TEGWA_MDIV_NEW BIT(11)
#define TEGWA_PWWMB BIT(12)
#define TEGWA_PWW_VCO_OUT BIT(13)

/**
 * stwuct tegwa_cwk_pww - Tegwa PWW cwock
 *
 * @hw:		handwe between common and hawdwawe-specifix intewfaces
 * @cwk_base:	addwess of CAW contwowwew
 * @pmc:	addwess of PMC, wequiwed to wead ovewwide bits
 * @wock:	wegistew wock
 * @pawams:	PWW pawametews
 */
stwuct tegwa_cwk_pww {
	stwuct cwk_hw	hw;
	void __iomem	*cwk_base;
	void __iomem	*pmc;
	spinwock_t	*wock;
	stwuct tegwa_cwk_pww_pawams	*pawams;
};

#define to_cwk_pww(_hw) containew_of(_hw, stwuct tegwa_cwk_pww, hw)

/**
 * stwuct tegwa_audio_cwk_info - Tegwa Audio Cwk Infowmation
 *
 * @name:	name fow the audio pww
 * @pww_pawams:	pww_pawams fow audio pww
 * @cwk_id:	cwk_ids fow the audio pww
 * @pawent:	name of the pawent of the audio pww
 */
stwuct tegwa_audio_cwk_info {
	chaw *name;
	stwuct tegwa_cwk_pww_pawams *pww_pawams;
	int cwk_id;
	chaw *pawent;
};

extewn const stwuct cwk_ops tegwa_cwk_pww_ops;
extewn const stwuct cwk_ops tegwa_cwk_pwwe_ops;
stwuct cwk *tegwa_cwk_wegistew_pww(const chaw *name, const chaw *pawent_name,
		void __iomem *cwk_base, void __iomem *pmc,
		unsigned wong fwags, stwuct tegwa_cwk_pww_pawams *pww_pawams,
		spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwe(const chaw *name, const chaw *pawent_name,
		void __iomem *cwk_base, void __iomem *pmc,
		unsigned wong fwags, stwuct tegwa_cwk_pww_pawams *pww_pawams,
		spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwxc(const chaw *name, const chaw *pawent_name,
			    void __iomem *cwk_base, void __iomem *pmc,
			    unsigned wong fwags,
			    stwuct tegwa_cwk_pww_pawams *pww_pawams,
			    spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwm(const chaw *name, const chaw *pawent_name,
			   void __iomem *cwk_base, void __iomem *pmc,
			   unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwc(const chaw *name, const chaw *pawent_name,
			   void __iomem *cwk_base, void __iomem *pmc,
			   unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwwe(const chaw *name, const chaw *pawent_name,
			   void __iomem *cwk_base, void __iomem *pmc,
			   unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock, unsigned wong pawent_wate);

stwuct cwk *tegwa_cwk_wegistew_pwwwe_tegwa210(const chaw *name,
			   const chaw *pawent_name, void __iomem *cwk_base,
			   void __iomem *pmc, unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock, unsigned wong pawent_wate);

stwuct cwk *tegwa_cwk_wegistew_pwwe_tegwa114(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwe_tegwa210(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwc_tegwa210(const chaw *name,
				const chaw *pawent_name, void __iomem *cwk_base,
				void __iomem *pmc, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwss_tegwa210(const chaw *name,
				const chaw *pawent_name, void __iomem *cwk_base,
				unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwss(const chaw *name, const chaw *pawent_name,
			   void __iomem *cwk_base, unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwmb(const chaw *name, const chaw *pawent_name,
			   void __iomem *cwk_base, void __iomem *pmc,
			   unsigned wong fwags,
			   stwuct tegwa_cwk_pww_pawams *pww_pawams,
			   spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwu(const chaw *name, const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwu_tegwa114(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

stwuct cwk *tegwa_cwk_wegistew_pwwu_tegwa210(const chaw *name,
				const chaw *pawent_name,
				void __iomem *cwk_base, unsigned wong fwags,
				stwuct tegwa_cwk_pww_pawams *pww_pawams,
				spinwock_t *wock);

/**
 * stwuct tegwa_cwk_pww_out - PWW dividew down cwock
 *
 * @hw:			handwe between common and hawdwawe-specific intewfaces
 * @weg:		wegistew containing the PWW dividew
 * @enb_bit_idx:	bit to enabwe/disabwe PWW dividew
 * @wst_bit_idx:	bit to weset PWW dividew
 * @wock:		wegistew wock
 * @fwags:		hawdwawe-specific fwags
 */
stwuct tegwa_cwk_pww_out {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		enb_bit_idx;
	u8		wst_bit_idx;
	spinwock_t	*wock;
	u8		fwags;
};

#define to_cwk_pww_out(_hw) containew_of(_hw, stwuct tegwa_cwk_pww_out, hw)

extewn const stwuct cwk_ops tegwa_cwk_pww_out_ops;
stwuct cwk *tegwa_cwk_wegistew_pww_out(const chaw *name,
		const chaw *pawent_name, void __iomem *weg, u8 enb_bit_idx,
		u8 wst_bit_idx, unsigned wong fwags, u8 pww_div_fwags,
		spinwock_t *wock);

/**
 * stwuct tegwa_cwk_pewiph_wegs -  Wegistews contwowwing pewiphewaw cwock
 *
 * @enb_weg:		wead the enabwe status
 * @enb_set_weg:	wwite 1 to enabwe cwock
 * @enb_cww_weg:	wwite 1 to disabwe cwock
 * @wst_weg:		wead the weset status
 * @wst_set_weg:	wwite 1 to assewt the weset of pewiphewaw
 * @wst_cww_weg:	wwite 1 to deassewt the weset of pewiphewaw
 */
stwuct tegwa_cwk_pewiph_wegs {
	u32 enb_weg;
	u32 enb_set_weg;
	u32 enb_cww_weg;
	u32 wst_weg;
	u32 wst_set_weg;
	u32 wst_cww_weg;
};

/**
 * stwuct tegwa_cwk_pewiph_gate - pewiphewaw gate cwock
 *
 * @magic:		magic numbew to vawidate type
 * @hw:			handwe between common and hawdwawe-specific intewfaces
 * @cwk_base:		addwess of CAW contwowwew
 * @wegs:		Wegistews to contwow the pewiphewaw
 * @fwags:		hawdwawe-specific fwags
 * @cwk_num:		Cwock numbew
 * @enabwe_wefcnt:	awway to maintain wefewence count of the cwock
 *
 * Fwags:
 * TEGWA_PEWIPH_NO_WESET - This fwag indicates that weset is not awwowed
 *     fow this moduwe.
 * TEGWA_PEWIPH_ON_APB - If pewiphewaw is in the APB bus then wead the
 *     bus to fwush the wwite opewation in apb bus. This fwag indicates
 *     that this pewiphewaw is in apb bus.
 * TEGWA_PEWIPH_WAW_1005168 - Appwy wowkawound fow Tegwa114 MSENC bug
 */
stwuct tegwa_cwk_pewiph_gate {
	u32			magic;
	stwuct cwk_hw		hw;
	void __iomem		*cwk_base;
	u8			fwags;
	int			cwk_num;
	int			*enabwe_wefcnt;
	const stwuct tegwa_cwk_pewiph_wegs *wegs;
};

#define to_cwk_pewiph_gate(_hw)					\
	containew_of(_hw, stwuct tegwa_cwk_pewiph_gate, hw)

#define TEGWA_CWK_PEWIPH_GATE_MAGIC 0x17760309

#define TEGWA_PEWIPH_NO_WESET BIT(0)
#define TEGWA_PEWIPH_ON_APB BIT(2)
#define TEGWA_PEWIPH_WAW_1005168 BIT(3)
#define TEGWA_PEWIPH_NO_DIV BIT(4)
#define TEGWA_PEWIPH_NO_GATE BIT(5)

extewn const stwuct cwk_ops tegwa_cwk_pewiph_gate_ops;
stwuct cwk *tegwa_cwk_wegistew_pewiph_gate(const chaw *name,
		const chaw *pawent_name, u8 gate_fwags, void __iomem *cwk_base,
		unsigned wong fwags, int cwk_num, int *enabwe_wefcnt);

stwuct tegwa_cwk_pewiph_fixed {
	stwuct cwk_hw hw;
	void __iomem *base;
	const stwuct tegwa_cwk_pewiph_wegs *wegs;
	unsigned int muw;
	unsigned int div;
	unsigned int num;
};

stwuct cwk *tegwa_cwk_wegistew_pewiph_fixed(const chaw *name,
					    const chaw *pawent,
					    unsigned wong fwags,
					    void __iomem *base,
					    unsigned int muw,
					    unsigned int div,
					    unsigned int num);

/**
 * stwuct cwk-pewiph - pewiphewaw cwock
 *
 * @magic:	magic numbew to vawidate type
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @mux:	mux cwock
 * @dividew:	dividew cwock
 * @gate:	gate cwock
 * @mux_ops:	mux cwock ops
 * @div_ops:	dividew cwock ops
 * @gate_ops:	gate cwock ops
 */
stwuct tegwa_cwk_pewiph {
	u32			magic;
	stwuct cwk_hw		hw;
	stwuct cwk_mux		mux;
	stwuct tegwa_cwk_fwac_div	dividew;
	stwuct tegwa_cwk_pewiph_gate	gate;

	const stwuct cwk_ops	*mux_ops;
	const stwuct cwk_ops	*div_ops;
	const stwuct cwk_ops	*gate_ops;
};

#define to_cwk_pewiph(_hw) containew_of(_hw, stwuct tegwa_cwk_pewiph, hw)

#define TEGWA_CWK_PEWIPH_MAGIC 0x18221223

extewn const stwuct cwk_ops tegwa_cwk_pewiph_ops;
stwuct cwk *tegwa_cwk_wegistew_pewiph(const chaw *name,
		const chaw * const *pawent_names, int num_pawents,
		stwuct tegwa_cwk_pewiph *pewiph, void __iomem *cwk_base,
		u32 offset, unsigned wong fwags);
stwuct cwk *tegwa_cwk_wegistew_pewiph_nodiv(const chaw *name,
		const chaw * const *pawent_names, int num_pawents,
		stwuct tegwa_cwk_pewiph *pewiph, void __iomem *cwk_base,
		u32 offset);

#define TEGWA_CWK_PEWIPH(_mux_shift, _mux_mask, _mux_fwags,		\
			 _div_shift, _div_width, _div_fwac_width,	\
			 _div_fwags, _cwk_num,\
			 _gate_fwags, _tabwe, _wock)			\
	{								\
		.mux = {						\
			.fwags = _mux_fwags,				\
			.shift = _mux_shift,				\
			.mask = _mux_mask,				\
			.tabwe = _tabwe,				\
			.wock = _wock,					\
		},							\
		.dividew = {						\
			.fwags = _div_fwags,				\
			.shift = _div_shift,				\
			.width = _div_width,				\
			.fwac_width = _div_fwac_width,			\
			.wock = _wock,					\
		},							\
		.gate = {						\
			.fwags = _gate_fwags,				\
			.cwk_num = _cwk_num,				\
		},							\
		.mux_ops = &cwk_mux_ops,				\
		.div_ops = &tegwa_cwk_fwac_div_ops,			\
		.gate_ops = &tegwa_cwk_pewiph_gate_ops,			\
	}

stwuct tegwa_pewiph_init_data {
	const chaw *name;
	int cwk_id;
	union {
		const chaw *const *pawent_names;
		const chaw *pawent_name;
	} p;
	int num_pawents;
	stwuct tegwa_cwk_pewiph pewiph;
	u32 offset;
	const chaw *con_id;
	const chaw *dev_id;
	unsigned wong fwags;
};

#define TEGWA_INIT_DATA_TABWE(_name, _con_id, _dev_id, _pawent_names, _offset,\
			_mux_shift, _mux_mask, _mux_fwags, _div_shift,	\
			_div_width, _div_fwac_width, _div_fwags,	\
			_cwk_num, _gate_fwags, _cwk_id, _tabwe,		\
			_fwags, _wock) \
	{								\
		.name = _name,						\
		.cwk_id = _cwk_id,					\
		.p.pawent_names = _pawent_names,			\
		.num_pawents = AWWAY_SIZE(_pawent_names),		\
		.pewiph = TEGWA_CWK_PEWIPH(_mux_shift, _mux_mask,	\
					   _mux_fwags, _div_shift,	\
					   _div_width, _div_fwac_width,	\
					   _div_fwags, _cwk_num,	\
					   _gate_fwags, _tabwe, _wock),	\
		.offset = _offset,					\
		.con_id = _con_id,					\
		.dev_id = _dev_id,					\
		.fwags = _fwags						\
	}

#define TEGWA_INIT_DATA(_name, _con_id, _dev_id, _pawent_names, _offset,\
			_mux_shift, _mux_width, _mux_fwags, _div_shift,	\
			_div_width, _div_fwac_width, _div_fwags, \
			_cwk_num, _gate_fwags, _cwk_id)	\
	TEGWA_INIT_DATA_TABWE(_name, _con_id, _dev_id, _pawent_names, _offset,\
			_mux_shift, BIT(_mux_width) - 1, _mux_fwags,	\
			_div_shift, _div_width, _div_fwac_width, _div_fwags, \
			_cwk_num, _gate_fwags, _cwk_id,\
			NUWW, 0, NUWW)

stwuct cwk *tegwa_cwk_wegistew_pewiph_data(void __iomem *cwk_base,
					   stwuct tegwa_pewiph_init_data *init);

/**
 * stwuct cwk_supew_mux - supew cwock
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew contwowwing muwtipwexew
 * @width:	width of the muwtipwexew bit fiewd
 * @fwags:	hawdwawe-specific fwags
 * @div2_index:	bit contwowwing divide-by-2
 * @pwwx_index:	PWWX index in the pawent wist
 * @wock:	wegistew wock
 *
 * Fwags:
 * TEGWA_DIVIDEW_2 - WP cwustew has additionaw dividew. This fwag indicates
 *     that this is WP cwustew cwock.
 * TEGWA210_CPU_CWK - This fwag is used to identify CPU cwustew fow gen5
 *     supew mux pawent using PWWP bwanches. To use PWWP bwanches to CPU, need
 *     to configuwe additionaw bit PWWP_OUT_CPU in the cwock wegistews.
 * TEGWA20_SUPEW_CWK - Tegwa20 doesn't have a dedicated dividew fow Supew
 *     cwocks, it onwy has a cwock-skippew.
 */
stwuct tegwa_cwk_supew_mux {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	stwuct tegwa_cwk_fwac_div fwac_div;
	const stwuct cwk_ops	*div_ops;
	u8		width;
	u8		fwags;
	u8		div2_index;
	u8		pwwx_index;
	spinwock_t	*wock;
};

#define to_cwk_supew_mux(_hw) containew_of(_hw, stwuct tegwa_cwk_supew_mux, hw)

#define TEGWA_DIVIDEW_2 BIT(0)
#define TEGWA210_CPU_CWK BIT(1)
#define TEGWA20_SUPEW_CWK BIT(2)

extewn const stwuct cwk_ops tegwa_cwk_supew_ops;
stwuct cwk *tegwa_cwk_wegistew_supew_mux(const chaw *name,
		const chaw **pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		u8 width, u8 pwwx_index, u8 div2_index, spinwock_t *wock);
stwuct cwk *tegwa_cwk_wegistew_supew_cwk(const chaw *name,
		const chaw * const *pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		spinwock_t *wock);
stwuct cwk *tegwa_cwk_wegistew_supew_ccwk(const chaw *name,
		const chaw * const *pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		spinwock_t *wock);
int tegwa_ccwk_pwe_pwwx_wate_change(void);
void tegwa_ccwk_post_pwwx_wate_change(void);

/**
 * stwuct tegwa_sdmmc_mux - switch dividew with Wow Jittew inputs fow SDMMC
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew contwowwing mux and dividew
 * @fwags:	hawdwawe-specific fwags
 * @wock:	optionaw wegistew wock
 * @gate:	gate cwock
 * @gate_ops:	gate cwock ops
 */
stwuct tegwa_sdmmc_mux {
	stwuct cwk_hw		hw;
	void __iomem		*weg;
	spinwock_t		*wock;
	const stwuct cwk_ops	*gate_ops;
	stwuct tegwa_cwk_pewiph_gate	gate;
	u8			div_fwags;
};

#define to_cwk_sdmmc_mux(_hw) containew_of(_hw, stwuct tegwa_sdmmc_mux, hw)

stwuct cwk *tegwa_cwk_wegistew_sdmmc_mux_div(const chaw *name,
		void __iomem *cwk_base, u32 offset, u32 cwk_num, u8 div_fwags,
		unsigned wong fwags, void *wock);

/**
 * stwuct cwk_init_tabwe - cwock initiawization tabwe
 * @cwk_id:	cwock id as mentioned in device twee bindings
 * @pawent_id:	pawent cwock id as mentioned in device twee bindings
 * @wate:	wate to set
 * @state:	enabwe/disabwe
 */
stwuct tegwa_cwk_init_tabwe {
	unsigned int	cwk_id;
	unsigned int	pawent_id;
	unsigned wong	wate;
	int		state;
};

/**
 * stwuct cwk_dupwicate - dupwicate cwocks
 * @cwk_id:	cwock id as mentioned in device twee bindings
 * @wookup:	dupwicate wookup entwy fow the cwock
 */
stwuct tegwa_cwk_dupwicate {
	int			cwk_id;
	stwuct cwk_wookup	wookup;
};

#define TEGWA_CWK_DUPWICATE(_cwk_id, _dev, _con) \
	{					\
		.cwk_id = _cwk_id,		\
		.wookup = {			\
			.dev_id = _dev,		\
			.con_id = _con,		\
		},				\
	}

stwuct tegwa_cwk {
	int			dt_id;
	boow			pwesent;
};

stwuct tegwa_devcwk {
	int		dt_id;
	chaw		*dev_id;
	chaw		*con_id;
};

void tegwa_init_speciaw_wesets(unsigned int num, int (*assewt)(unsigned wong),
			       int (*deassewt)(unsigned wong));

void tegwa_init_fwom_tabwe(stwuct tegwa_cwk_init_tabwe *tbw,
		stwuct cwk *cwks[], int cwk_max);

void tegwa_init_dup_cwks(stwuct tegwa_cwk_dupwicate *dup_wist,
		stwuct cwk *cwks[], int cwk_max);

const stwuct tegwa_cwk_pewiph_wegs *get_weg_bank(int cwkid);
stwuct cwk **tegwa_cwk_init(void __iomem *cwk_base, int num, int pewiph_banks);

stwuct cwk **tegwa_wookup_dt_id(int cwk_id, stwuct tegwa_cwk *tegwa_cwk);

void tegwa_add_of_pwovidew(stwuct device_node *np, void *cwk_swc_oneceww_get);
void tegwa_wegistew_devcwks(stwuct tegwa_devcwk *dev_cwks, int num);

void tegwa_audio_cwk_init(void __iomem *cwk_base,
			void __iomem *pmc_base, stwuct tegwa_cwk *tegwa_cwks,
			stwuct tegwa_audio_cwk_info *audio_info,
			unsigned int num_pwws, unsigned wong sync_max_wate);

void tegwa_pewiph_cwk_init(void __iomem *cwk_base, void __iomem *pmc_base,
			stwuct tegwa_cwk *tegwa_cwks,
			stwuct tegwa_cwk_pww_pawams *pww_pawams);

void tegwa_fixed_cwk_init(stwuct tegwa_cwk *tegwa_cwks);
int tegwa_osc_cwk_init(void __iomem *cwk_base, stwuct tegwa_cwk *cwks,
		       unsigned wong *input_fweqs, unsigned int num,
		       unsigned int cwk_m_div, unsigned wong *osc_fweq,
		       unsigned wong *pww_wef_fweq);
void tegwa_supew_cwk_gen4_init(void __iomem *cwk_base,
			void __iomem *pmc_base, stwuct tegwa_cwk *tegwa_cwks,
			stwuct tegwa_cwk_pww_pawams *pww_pawams);
void tegwa_supew_cwk_gen5_init(void __iomem *cwk_base,
			void __iomem *pmc_base, stwuct tegwa_cwk *tegwa_cwks,
			stwuct tegwa_cwk_pww_pawams *pww_pawams);

#ifdef CONFIG_TEGWA124_CWK_EMC
stwuct cwk *tegwa124_cwk_wegistew_emc(void __iomem *base, stwuct device_node *np,
				      spinwock_t *wock);
boow tegwa124_cwk_emc_dwivew_avaiwabwe(stwuct cwk_hw *emc_hw);
#ewse
static inwine stwuct cwk *
tegwa124_cwk_wegistew_emc(void __iomem *base, stwuct device_node *np,
			  spinwock_t *wock)
{
	wetuwn NUWW;
}

static inwine boow tegwa124_cwk_emc_dwivew_avaiwabwe(stwuct cwk_hw *emc_hw)
{
	wetuwn fawse;
}
#endif

void tegwa114_cwock_tune_cpu_twimmews_high(void);
void tegwa114_cwock_tune_cpu_twimmews_wow(void);
void tegwa114_cwock_tune_cpu_twimmews_init(void);
void tegwa114_cwock_assewt_dfww_dvco_weset(void);
void tegwa114_cwock_deassewt_dfww_dvco_weset(void);

typedef void (*tegwa_cwk_appwy_init_tabwe_func)(void);
extewn tegwa_cwk_appwy_init_tabwe_func tegwa_cwk_appwy_init_tabwe;
int tegwa_pww_wait_fow_wock(stwuct tegwa_cwk_pww *pww);
u16 tegwa_pww_get_fixed_mdiv(stwuct cwk_hw *hw, unsigned wong input_wate);
int tegwa_pww_p_div_to_hw(stwuct tegwa_cwk_pww *pww, u8 p_div);
int div_fwac_get(unsigned wong wate, unsigned pawent_wate, u8 width,
		 u8 fwac_width, u8 fwags);
void tegwa_cwk_osc_wesume(void __iomem *cwk_base);
void tegwa_cwk_set_pwwp_out_cpu(boow enabwe);
void tegwa_cwk_pewiph_suspend(void);
void tegwa_cwk_pewiph_wesume(void);


/* Combined wead fence with deway */
#define fence_udeway(deway, weg)	\
	do {				\
		weadw(weg);		\
		udeway(deway);		\
	} whiwe (0)

boow tegwa20_cwk_emc_dwivew_avaiwabwe(stwuct cwk_hw *emc_hw);
stwuct cwk *tegwa20_cwk_wegistew_emc(void __iomem *ioaddw, boow wow_jittew);

stwuct cwk *tegwa210_cwk_wegistew_emc(stwuct device_node *np,
				      void __iomem *wegs);

stwuct cwk *tegwa_cwk_dev_wegistew(stwuct cwk_hw *hw);

#endif /* TEGWA_CWK_H */
