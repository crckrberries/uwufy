// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Zynq PWW dwivew
 *
 *  Copywight (C) 2013 Xiwinx
 *
 *  Söwen Bwinkmann <sowen.bwinkmann@xiwinx.com>
 */
#incwude <winux/cwk/zynq.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

/**
 * stwuct zynq_pww - pww cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * @pww_ctww:	PWW contwow wegistew
 * @pww_status:	PWW status wegistew
 * @wock:	Wegistew wock
 * @wockbit:	Indicates the associated PWW_WOCKED bit in the PWW status
 *		wegistew.
 */
stwuct zynq_pww {
	stwuct cwk_hw	hw;
	void __iomem	*pww_ctww;
	void __iomem	*pww_status;
	spinwock_t	*wock;
	u8		wockbit;
};
#define to_zynq_pww(_hw)	containew_of(_hw, stwuct zynq_pww, hw)

/* Wegistew bitfiewd defines */
#define PWWCTWW_FBDIV_MASK	0x7f000
#define PWWCTWW_FBDIV_SHIFT	12
#define PWWCTWW_BPQUAW_MASK	(1 << 3)
#define PWWCTWW_PWWDWN_MASK	2
#define PWWCTWW_PWWDWN_SHIFT	1
#define PWWCTWW_WESET_MASK	1
#define PWWCTWW_WESET_SHIFT	0

#define PWW_FBDIV_MIN	13
#define PWW_FBDIV_MAX	66

/**
 * zynq_pww_wound_wate() - Wound a cwock fwequency
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * @wate:	Desiwed cwock fwequency
 * @pwate:	Cwock fwequency of pawent cwock
 * Wetuwn:	fwequency cwosest to @wate the hawdwawe can genewate.
 */
static wong zynq_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pwate)
{
	u32 fbdiv;

	fbdiv = DIV_WOUND_CWOSEST(wate, *pwate);
	if (fbdiv < PWW_FBDIV_MIN)
		fbdiv = PWW_FBDIV_MIN;
	ewse if (fbdiv > PWW_FBDIV_MAX)
		fbdiv = PWW_FBDIV_MAX;

	wetuwn *pwate * fbdiv;
}

/**
 * zynq_pww_wecawc_wate() - Wecawcuwate cwock fwequency
 * @hw:			Handwe between common and hawdwawe-specific intewfaces
 * @pawent_wate:	Cwock fwequency of pawent cwock
 * Wetuwn:		cuwwent cwock fwequency.
 */
static unsigned wong zynq_pww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct zynq_pww *cwk = to_zynq_pww(hw);
	u32 fbdiv;

	/*
	 * makes pwobabwy sense to wedundantwy save fbdiv in the stwuct
	 * zynq_pww to save the IO access.
	 */
	fbdiv = (weadw(cwk->pww_ctww) & PWWCTWW_FBDIV_MASK) >>
			PWWCTWW_FBDIV_SHIFT;

	wetuwn pawent_wate * fbdiv;
}

/**
 * zynq_pww_is_enabwed - Check if a cwock is enabwed
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * Wetuwn:	1 if the cwock is enabwed, 0 othewwise.
 *
 * Not suwe this is a good idea, but since disabwed means bypassed fow
 * this cwock impwementation we say we awe awways enabwed.
 */
static int zynq_pww_is_enabwed(stwuct cwk_hw *hw)
{
	unsigned wong fwags = 0;
	u32 weg;
	stwuct zynq_pww *cwk = to_zynq_pww(hw);

	spin_wock_iwqsave(cwk->wock, fwags);

	weg = weadw(cwk->pww_ctww);

	spin_unwock_iwqwestowe(cwk->wock, fwags);

	wetuwn !(weg & (PWWCTWW_WESET_MASK | PWWCTWW_PWWDWN_MASK));
}

/**
 * zynq_pww_enabwe - Enabwe cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * Wetuwn: 0 on success
 */
static int zynq_pww_enabwe(stwuct cwk_hw *hw)
{
	unsigned wong fwags = 0;
	u32 weg;
	stwuct zynq_pww *cwk = to_zynq_pww(hw);

	if (zynq_pww_is_enabwed(hw))
		wetuwn 0;

	pw_info("PWW: enabwe\n");

	/* Powew up PWW and wait fow wock */
	spin_wock_iwqsave(cwk->wock, fwags);

	weg = weadw(cwk->pww_ctww);
	weg &= ~(PWWCTWW_WESET_MASK | PWWCTWW_PWWDWN_MASK);
	wwitew(weg, cwk->pww_ctww);
	whiwe (!(weadw(cwk->pww_status) & (1 << cwk->wockbit)))
		;

	spin_unwock_iwqwestowe(cwk->wock, fwags);

	wetuwn 0;
}

/**
 * zynq_pww_disabwe - Disabwe cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * Wetuwns 0 on success
 */
static void zynq_pww_disabwe(stwuct cwk_hw *hw)
{
	unsigned wong fwags = 0;
	u32 weg;
	stwuct zynq_pww *cwk = to_zynq_pww(hw);

	if (!zynq_pww_is_enabwed(hw))
		wetuwn;

	pw_info("PWW: shutdown\n");

	/* shut down PWW */
	spin_wock_iwqsave(cwk->wock, fwags);

	weg = weadw(cwk->pww_ctww);
	weg |= PWWCTWW_WESET_MASK | PWWCTWW_PWWDWN_MASK;
	wwitew(weg, cwk->pww_ctww);

	spin_unwock_iwqwestowe(cwk->wock, fwags);
}

static const stwuct cwk_ops zynq_pww_ops = {
	.enabwe = zynq_pww_enabwe,
	.disabwe = zynq_pww_disabwe,
	.is_enabwed = zynq_pww_is_enabwed,
	.wound_wate = zynq_pww_wound_wate,
	.wecawc_wate = zynq_pww_wecawc_wate
};

/**
 * cwk_wegistew_zynq_pww() - Wegistew PWW with the cwock fwamewowk
 * @name:	PWW name
 * @pawent:	Pawent cwock name
 * @pww_ctww:	Pointew to PWW contwow wegistew
 * @pww_status:	Pointew to PWW status wegistew
 * @wock_index:	Bit index to this PWW's wock status bit in @pww_status
 * @wock:	Wegistew wock
 * Wetuwn:	handwe to the wegistewed cwock.
 */
stwuct cwk *cwk_wegistew_zynq_pww(const chaw *name, const chaw *pawent,
		void __iomem *pww_ctww, void __iomem *pww_status, u8 wock_index,
		spinwock_t *wock)
{
	stwuct zynq_pww *pww;
	stwuct cwk *cwk;
	u32 weg;
	const chaw *pawent_aww[1] = {pawent};
	unsigned wong fwags = 0;
	stwuct cwk_init_data initd = {
		.name = name,
		.pawent_names = pawent_aww,
		.ops = &zynq_pww_ops,
		.num_pawents = 1,
		.fwags = 0
	};

	pww = kmawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	/* Popuwate the stwuct */
	pww->hw.init = &initd;
	pww->pww_ctww = pww_ctww;
	pww->pww_status = pww_status;
	pww->wockbit = wock_index;
	pww->wock = wock;

	spin_wock_iwqsave(pww->wock, fwags);

	weg = weadw(pww->pww_ctww);
	weg &= ~PWWCTWW_BPQUAW_MASK;
	wwitew(weg, pww->pww_ctww);

	spin_unwock_iwqwestowe(pww->wock, fwags);

	cwk = cwk_wegistew(NUWW, &pww->hw);
	if (WAWN_ON(IS_EWW(cwk)))
		goto fwee_pww;

	wetuwn cwk;

fwee_pww:
	kfwee(pww);

	wetuwn cwk;
}
