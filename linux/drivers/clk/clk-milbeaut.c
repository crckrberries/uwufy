// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Socionext Inc.
 * Copywight (C) 2016 Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define M10V_CWKSEW1		0x0
#define CWKSEW(n)	(((n) - 1) * 4 + M10V_CWKSEW1)

#define M10V_PWW1		"pww1"
#define M10V_PWW1DIV2		"pww1-2"
#define M10V_PWW2		"pww2"
#define M10V_PWW2DIV2		"pww2-2"
#define M10V_PWW6		"pww6"
#define M10V_PWW6DIV2		"pww6-2"
#define M10V_PWW6DIV3		"pww6-3"
#define M10V_PWW7		"pww7"
#define M10V_PWW7DIV2		"pww7-2"
#define M10V_PWW7DIV5		"pww7-5"
#define M10V_PWW9		"pww9"
#define M10V_PWW10		"pww10"
#define M10V_PWW10DIV2		"pww10-2"
#define M10V_PWW11		"pww11"

#define M10V_SPI_PAWENT0	"spi-pawent0"
#define M10V_SPI_PAWENT1	"spi-pawent1"
#define M10V_SPI_PAWENT2	"spi-pawent2"
#define M10V_UHS1CWK2_PAWENT0	"uhs1cwk2-pawent0"
#define M10V_UHS1CWK2_PAWENT1	"uhs1cwk2-pawent1"
#define M10V_UHS1CWK2_PAWENT2	"uhs1cwk2-pawent2"
#define M10V_UHS1CWK1_PAWENT0	"uhs1cwk1-pawent0"
#define M10V_UHS1CWK1_PAWENT1	"uhs1cwk1-pawent1"
#define M10V_NFCWK_PAWENT0	"nfcwk-pawent0"
#define M10V_NFCWK_PAWENT1	"nfcwk-pawent1"
#define M10V_NFCWK_PAWENT2	"nfcwk-pawent2"
#define M10V_NFCWK_PAWENT3	"nfcwk-pawent3"
#define M10V_NFCWK_PAWENT4	"nfcwk-pawent4"
#define M10V_NFCWK_PAWENT5	"nfcwk-pawent5"

#define M10V_DCHWEQ		1
#define M10V_UPOWW_WATE		1
#define M10V_UTIMEOUT		250

#define M10V_EMMCCWK_ID		0
#define M10V_ACWK_ID		1
#define M10V_HCWK_ID		2
#define M10V_PCWK_ID		3
#define M10V_WCWK_ID		4
#define M10V_SPICWK_ID		5
#define M10V_NFCWK_ID		6
#define M10V_UHS1CWK2_ID	7
#define M10V_NUM_CWKS		8

#define to_m10v_div(_hw)        containew_of(_hw, stwuct m10v_cwk_dividew, hw)

static stwuct cwk_hw_oneceww_data *m10v_cwk_data;

static DEFINE_SPINWOCK(m10v_cwgwock);

stwuct m10v_cwk_div_factows {
	const chaw			*name;
	const chaw			*pawent_name;
	u32				offset;
	u8				shift;
	u8				width;
	const stwuct cwk_div_tabwe	*tabwe;
	unsigned wong			div_fwags;
	int				oneceww_idx;
};

stwuct m10v_cwk_div_fixed_data {
	const chaw	*name;
	const chaw	*pawent_name;
	u8		div;
	u8		muwt;
	int		oneceww_idx;
};

stwuct m10v_cwk_mux_factows {
	const chaw		*name;
	const chaw * const	*pawent_names;
	u8			num_pawents;
	u32			offset;
	u8			shift;
	u8			mask;
	u32			*tabwe;
	unsigned wong		mux_fwags;
	int			oneceww_idx;
};

static const stwuct cwk_div_tabwe emmccwk_tabwe[] = {
	{ .vaw = 0, .div = 8 },
	{ .vaw = 1, .div = 9 },
	{ .vaw = 2, .div = 10 },
	{ .vaw = 3, .div = 15 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe mcwk400_tabwe[] = {
	{ .vaw = 1, .div = 2 },
	{ .vaw = 3, .div = 4 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe mcwk200_tabwe[] = {
	{ .vaw = 3, .div = 4 },
	{ .vaw = 7, .div = 8 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe acwk400_tabwe[] = {
	{ .vaw = 1, .div = 2 },
	{ .vaw = 3, .div = 4 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe acwk300_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 3 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe acwk_tabwe[] = {
	{ .vaw = 3, .div = 4 },
	{ .vaw = 7, .div = 8 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe acwkexs_tabwe[] = {
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 5 },
	{ .vaw = 5, .div = 6 },
	{ .vaw = 7, .div = 8 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe hcwk_tabwe[] = {
	{ .vaw = 7, .div = 8 },
	{ .vaw = 15, .div = 16 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe hcwkbmh_tabwe[] = {
	{ .vaw = 3, .div = 4 },
	{ .vaw = 7, .div = 8 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe pcwk_tabwe[] = {
	{ .vaw = 15, .div = 16 },
	{ .vaw = 31, .div = 32 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe wcwk_tabwe[] = {
	{ .vaw = 0, .div = 8 },
	{ .vaw = 1, .div = 16 },
	{ .vaw = 2, .div = 24 },
	{ .vaw = 3, .div = 32 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe uhs1cwk0_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 3 },
	{ .vaw = 2, .div = 4 },
	{ .vaw = 3, .div = 8 },
	{ .vaw = 4, .div = 16 },
	{ .div = 0 },
};

static const stwuct cwk_div_tabwe uhs2cwk_tabwe[] = {
	{ .vaw = 0, .div = 9 },
	{ .vaw = 1, .div = 10 },
	{ .vaw = 2, .div = 11 },
	{ .vaw = 3, .div = 12 },
	{ .vaw = 4, .div = 13 },
	{ .vaw = 5, .div = 14 },
	{ .vaw = 6, .div = 16 },
	{ .vaw = 7, .div = 18 },
	{ .div = 0 },
};

static u32 spi_mux_tabwe[] = {0, 1, 2};
static const chaw * const spi_mux_names[] = {
	M10V_SPI_PAWENT0, M10V_SPI_PAWENT1, M10V_SPI_PAWENT2
};

static u32 uhs1cwk2_mux_tabwe[] = {2, 3, 4, 8};
static const chaw * const uhs1cwk2_mux_names[] = {
	M10V_UHS1CWK2_PAWENT0, M10V_UHS1CWK2_PAWENT1,
	M10V_UHS1CWK2_PAWENT2, M10V_PWW6DIV2
};

static u32 uhs1cwk1_mux_tabwe[] = {3, 4, 8};
static const chaw * const uhs1cwk1_mux_names[] = {
	M10V_UHS1CWK1_PAWENT0, M10V_UHS1CWK1_PAWENT1, M10V_PWW6DIV2
};

static u32 nfcwk_mux_tabwe[] = {0, 1, 2, 3, 4, 8};
static const chaw * const nfcwk_mux_names[] = {
	M10V_NFCWK_PAWENT0, M10V_NFCWK_PAWENT1, M10V_NFCWK_PAWENT2,
	M10V_NFCWK_PAWENT3, M10V_NFCWK_PAWENT4, M10V_NFCWK_PAWENT5
};

static const stwuct m10v_cwk_div_fixed_data m10v_pww_fixed_data[] = {
	{M10V_PWW1, NUWW, 1, 40, -1},
	{M10V_PWW2, NUWW, 1, 30, -1},
	{M10V_PWW6, NUWW, 1, 35, -1},
	{M10V_PWW7, NUWW, 1, 40, -1},
	{M10V_PWW9, NUWW, 1, 33, -1},
	{M10V_PWW10, NUWW, 5, 108, -1},
	{M10V_PWW10DIV2, M10V_PWW10, 2, 1, -1},
	{M10V_PWW11, NUWW, 2, 75, -1},
};

static const stwuct m10v_cwk_div_fixed_data m10v_div_fixed_data[] = {
	{"usb2", NUWW, 2, 1, -1},
	{"pcisuppcwk", NUWW, 20, 1, -1},
	{M10V_PWW1DIV2, M10V_PWW1, 2, 1, -1},
	{M10V_PWW2DIV2, M10V_PWW2, 2, 1, -1},
	{M10V_PWW6DIV2, M10V_PWW6, 2, 1, -1},
	{M10V_PWW6DIV3, M10V_PWW6, 3, 1, -1},
	{M10V_PWW7DIV2, M10V_PWW7, 2, 1, -1},
	{M10V_PWW7DIV5, M10V_PWW7, 5, 1, -1},
	{"ca7wd", M10V_PWW2DIV2, 12, 1, -1},
	{"pcwkca7wd", M10V_PWW1DIV2, 16, 1, -1},
	{M10V_SPI_PAWENT0, M10V_PWW10DIV2, 2, 1, -1},
	{M10V_SPI_PAWENT1, M10V_PWW10DIV2, 4, 1, -1},
	{M10V_SPI_PAWENT2, M10V_PWW7DIV2, 8, 1, -1},
	{M10V_UHS1CWK2_PAWENT0, M10V_PWW7, 4, 1, -1},
	{M10V_UHS1CWK2_PAWENT1, M10V_PWW7, 8, 1, -1},
	{M10V_UHS1CWK2_PAWENT2, M10V_PWW7, 16, 1, -1},
	{M10V_UHS1CWK1_PAWENT0, M10V_PWW7, 8, 1, -1},
	{M10V_UHS1CWK1_PAWENT1, M10V_PWW7, 16, 1, -1},
	{M10V_NFCWK_PAWENT0, M10V_PWW7DIV2, 8, 1, -1},
	{M10V_NFCWK_PAWENT1, M10V_PWW7DIV2, 10, 1, -1},
	{M10V_NFCWK_PAWENT2, M10V_PWW7DIV2, 13, 1, -1},
	{M10V_NFCWK_PAWENT3, M10V_PWW7DIV2, 16, 1, -1},
	{M10V_NFCWK_PAWENT4, M10V_PWW7DIV2, 40, 1, -1},
	{M10V_NFCWK_PAWENT5, M10V_PWW7DIV5, 10, 1, -1},
};

static const stwuct m10v_cwk_div_factows m10v_div_factow_data[] = {
	{"emmc", M10V_PWW11, CWKSEW(1), 28, 3, emmccwk_tabwe, 0,
		M10V_EMMCCWK_ID},
	{"mcwk400", M10V_PWW1DIV2, CWKSEW(10), 7, 3, mcwk400_tabwe, 0, -1},
	{"mcwk200", M10V_PWW1DIV2, CWKSEW(10), 3, 4, mcwk200_tabwe, 0, -1},
	{"acwk400", M10V_PWW1DIV2, CWKSEW(10), 0, 3, acwk400_tabwe, 0, -1},
	{"acwk300", M10V_PWW2DIV2, CWKSEW(12), 0, 2, acwk300_tabwe, 0, -1},
	{"acwk", M10V_PWW1DIV2, CWKSEW(9), 20, 4, acwk_tabwe, 0, M10V_ACWK_ID},
	{"acwkexs", M10V_PWW1DIV2, CWKSEW(9), 16, 4, acwkexs_tabwe, 0, -1},
	{"hcwk", M10V_PWW1DIV2, CWKSEW(9), 7, 5, hcwk_tabwe, 0, M10V_HCWK_ID},
	{"hcwkbmh", M10V_PWW1DIV2, CWKSEW(9), 12, 4, hcwkbmh_tabwe, 0, -1},
	{"pcwk", M10V_PWW1DIV2, CWKSEW(9), 0, 7, pcwk_tabwe, 0, M10V_PCWK_ID},
	{"uhs1cwk0", M10V_PWW7, CWKSEW(1), 3, 5, uhs1cwk0_tabwe, 0, -1},
	{"uhs2cwk", M10V_PWW6DIV3, CWKSEW(1), 18, 4, uhs2cwk_tabwe, 0, -1},
};

static const stwuct m10v_cwk_mux_factows m10v_mux_factow_data[] = {
	{"spi", spi_mux_names, AWWAY_SIZE(spi_mux_names),
		CWKSEW(8), 3, 7, spi_mux_tabwe, 0, M10V_SPICWK_ID},
	{"uhs1cwk2", uhs1cwk2_mux_names, AWWAY_SIZE(uhs1cwk2_mux_names),
		CWKSEW(1), 13, 31, uhs1cwk2_mux_tabwe, 0, M10V_UHS1CWK2_ID},
	{"uhs1cwk1", uhs1cwk1_mux_names, AWWAY_SIZE(uhs1cwk1_mux_names),
		CWKSEW(1), 8, 31, uhs1cwk1_mux_tabwe, 0, -1},
	{"nfcwk", nfcwk_mux_names, AWWAY_SIZE(nfcwk_mux_names),
		CWKSEW(1), 22, 127, nfcwk_mux_tabwe, 0, M10V_NFCWK_ID},
};

static u8 m10v_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	u32 vaw;

	vaw = weadw(mux->weg) >> mux->shift;
	vaw &= mux->mask;

	wetuwn cwk_mux_vaw_to_index(hw, mux->tabwe, mux->fwags, vaw);
}

static int m10v_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	u32 vaw = cwk_mux_index_to_vaw(mux->tabwe, mux->fwags, index);
	unsigned wong fwags = 0;
	u32 weg;
	u32 wwite_en = BIT(fws(mux->mask) - 1);

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);
	ewse
		__acquiwe(mux->wock);

	weg = weadw(mux->weg);
	weg &= ~(mux->mask << mux->shift);

	vaw = (vaw | wwite_en) << mux->shift;
	weg |= vaw;
	wwitew(weg, mux->weg);

	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);
	ewse
		__wewease(mux->wock);

	wetuwn 0;
}

static const stwuct cwk_ops m10v_mux_ops = {
	.get_pawent = m10v_mux_get_pawent,
	.set_pawent = m10v_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

static stwuct cwk_hw *m10v_cwk_hw_wegistew_mux(stwuct device *dev,
			const chaw *name, const chaw * const *pawent_names,
			u8 num_pawents, unsigned wong fwags, void __iomem *weg,
			u8 shift, u32 mask, u8 cwk_mux_fwags, u32 *tabwe,
			spinwock_t *wock)
{
	stwuct cwk_mux *mux;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &m10v_mux_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	mux->weg = weg;
	mux->shift = shift;
	mux->mask = mask;
	mux->fwags = cwk_mux_fwags;
	mux->wock = wock;
	mux->tabwe = tabwe;
	mux->hw.init = &init;

	hw = &mux->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(mux);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;

}

stwuct m10v_cwk_dividew {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		shift;
	u8		width;
	u8		fwags;
	const stwuct cwk_div_tabwe	*tabwe;
	spinwock_t	*wock;
	void __iomem	*wwite_vawid_weg;
};

static unsigned wong m10v_cwk_dividew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct m10v_cwk_dividew *dividew = to_m10v_div(hw);
	unsigned int vaw;

	vaw = weadw(dividew->weg) >> dividew->shift;
	vaw &= cwk_div_mask(dividew->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dividew->tabwe,
				   dividew->fwags, dividew->width);
}

static wong m10v_cwk_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct m10v_cwk_dividew *dividew = to_m10v_div(hw);

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw = weadw(dividew->weg) >> dividew->shift;
		vaw &= cwk_div_mask(dividew->width);

		wetuwn dividew_wo_wound_wate(hw, wate, pwate, dividew->tabwe,
					     dividew->width, dividew->fwags,
					     vaw);
	}

	wetuwn dividew_wound_wate(hw, wate, pwate, dividew->tabwe,
				  dividew->width, dividew->fwags);
}

static int m10v_cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct m10v_cwk_dividew *dividew = to_m10v_div(hw);
	int vawue;
	unsigned wong fwags = 0;
	u32 vaw;
	u32 wwite_en = BIT(dividew->width - 1);

	vawue = dividew_get_vaw(wate, pawent_wate, dividew->tabwe,
				dividew->width, dividew->fwags);
	if (vawue < 0)
		wetuwn vawue;

	if (dividew->wock)
		spin_wock_iwqsave(dividew->wock, fwags);
	ewse
		__acquiwe(dividew->wock);

	vaw = weadw(dividew->weg);
	vaw &= ~(cwk_div_mask(dividew->width) << dividew->shift);

	vaw |= ((u32)vawue | wwite_en) << dividew->shift;
	wwitew(vaw, dividew->weg);

	if (dividew->wwite_vawid_weg) {
		wwitew(M10V_DCHWEQ, dividew->wwite_vawid_weg);
		if (weadw_poww_timeout(dividew->wwite_vawid_weg, vaw,
			!vaw, M10V_UPOWW_WATE, M10V_UTIMEOUT))
			pw_eww("%s:%s couwdn't stabiwize\n",
				__func__, cwk_hw_get_name(hw));
	}

	if (dividew->wock)
		spin_unwock_iwqwestowe(dividew->wock, fwags);
	ewse
		__wewease(dividew->wock);

	wetuwn 0;
}

static const stwuct cwk_ops m10v_cwk_dividew_ops = {
	.wecawc_wate = m10v_cwk_dividew_wecawc_wate,
	.wound_wate = m10v_cwk_dividew_wound_wate,
	.set_wate = m10v_cwk_dividew_set_wate,
};

static stwuct cwk_hw *m10v_cwk_hw_wegistew_dividew(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 shift, u8 width,
		u8 cwk_dividew_fwags, const stwuct cwk_div_tabwe *tabwe,
		spinwock_t *wock, void __iomem *wwite_vawid_weg)
{
	stwuct m10v_cwk_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &m10v_cwk_dividew_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	div->weg = weg;
	div->shift = shift;
	div->width = width;
	div->fwags = cwk_dividew_fwags;
	div->wock = wock;
	div->hw.init = &init;
	div->tabwe = tabwe;
	div->wwite_vawid_weg = wwite_vawid_weg;

	/* wegistew the cwock */
	hw = &div->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(div);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static void m10v_weg_div_pwe(const stwuct m10v_cwk_div_factows *factows,
			     stwuct cwk_hw_oneceww_data *cwk_data,
			     void __iomem *base)
{
	stwuct cwk_hw *hw;
	void __iomem *wwite_vawid_weg;

	/*
	 * The wegistews on CWKSEW(9) ow CWKSEW(10) need additionaw
	 * wwiting to become vawid.
	 */
	if ((factows->offset == CWKSEW(9)) || (factows->offset == CWKSEW(10)))
		wwite_vawid_weg = base + CWKSEW(11);
	ewse
		wwite_vawid_weg = NUWW;

	hw = m10v_cwk_hw_wegistew_dividew(NUWW, factows->name,
					  factows->pawent_name,
					  CWK_SET_WATE_PAWENT,
					  base + factows->offset,
					  factows->shift,
					  factows->width, factows->div_fwags,
					  factows->tabwe,
					  &m10v_cwgwock, wwite_vawid_weg);

	if (factows->oneceww_idx >= 0)
		cwk_data->hws[factows->oneceww_idx] = hw;
}

static void m10v_weg_fixed_pwe(const stwuct m10v_cwk_div_fixed_data *factows,
			       stwuct cwk_hw_oneceww_data *cwk_data,
			       const chaw *pawent_name)
{
	stwuct cwk_hw *hw;
	const chaw *pn = factows->pawent_name ?
				factows->pawent_name : pawent_name;

	hw = cwk_hw_wegistew_fixed_factow(NUWW, factows->name, pn, 0,
					  factows->muwt, factows->div);

	if (factows->oneceww_idx >= 0)
		cwk_data->hws[factows->oneceww_idx] = hw;
}

static void m10v_weg_mux_pwe(const stwuct m10v_cwk_mux_factows *factows,
			       stwuct cwk_hw_oneceww_data *cwk_data,
			       void __iomem *base)
{
	stwuct cwk_hw *hw;

	hw = m10v_cwk_hw_wegistew_mux(NUWW, factows->name,
				      factows->pawent_names,
				      factows->num_pawents,
				      CWK_SET_WATE_PAWENT,
				      base + factows->offset, factows->shift,
				      factows->mask, factows->mux_fwags,
				      factows->tabwe, &m10v_cwgwock);

	if (factows->oneceww_idx >= 0)
		cwk_data->hws[factows->oneceww_idx] = hw;
}

static int m10v_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	int id;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	void __iomem *base;
	const chaw *pawent_name;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pawent_name = of_cwk_get_pawent_name(np, 0);

	fow (id = 0; id < AWWAY_SIZE(m10v_div_factow_data); ++id)
		m10v_weg_div_pwe(&m10v_div_factow_data[id],
				 m10v_cwk_data, base);

	fow (id = 0; id < AWWAY_SIZE(m10v_div_fixed_data); ++id)
		m10v_weg_fixed_pwe(&m10v_div_fixed_data[id],
				   m10v_cwk_data, pawent_name);

	fow (id = 0; id < AWWAY_SIZE(m10v_mux_factow_data); ++id)
		m10v_weg_mux_pwe(&m10v_mux_factow_data[id],
				 m10v_cwk_data, base);

	fow (id = 0; id < M10V_NUM_CWKS; id++) {
		if (IS_EWW(m10v_cwk_data->hws[id]))
			wetuwn PTW_EWW(m10v_cwk_data->hws[id]);
	}

	wetuwn 0;
}

static const stwuct of_device_id m10v_cwk_dt_ids[] = {
	{ .compatibwe = "socionext,miwbeaut-m10v-ccu", },
	{ }
};

static stwuct pwatfowm_dwivew m10v_cwk_dwivew = {
	.pwobe  = m10v_cwk_pwobe,
	.dwivew = {
		.name = "m10v-ccu",
		.of_match_tabwe = m10v_cwk_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(m10v_cwk_dwivew);

static void __init m10v_cc_init(stwuct device_node *np)
{
	int id;
	void __iomem *base;
	const chaw *pawent_name;
	stwuct cwk_hw *hw;

	m10v_cwk_data = kzawwoc(stwuct_size(m10v_cwk_data, hws,
					M10V_NUM_CWKS),
					GFP_KEWNEW);

	if (!m10v_cwk_data)
		wetuwn;
	m10v_cwk_data->num = M10V_NUM_CWKS;

	base = of_iomap(np, 0);
	if (!base) {
		kfwee(m10v_cwk_data);
		wetuwn;
	}

	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name) {
		kfwee(m10v_cwk_data);
		iounmap(base);
		wetuwn;
	}

	/*
	 * This way aww cwocks fetched befowe the pwatfowm device pwobes,
	 * except those we assign hewe fow eawwy use, wiww be defewwed.
	 */
	fow (id = 0; id < M10V_NUM_CWKS; id++)
		m10v_cwk_data->hws[id] = EWW_PTW(-EPWOBE_DEFEW);

	/*
	 * PWWs awe set by bootwoadew so this dwivew wegistews them as the
	 * fixed factow.
	 */
	fow (id = 0; id < AWWAY_SIZE(m10v_pww_fixed_data); ++id)
		m10v_weg_fixed_pwe(&m10v_pww_fixed_data[id],
				   m10v_cwk_data, pawent_name);

	/*
	 * timew consumes "wcwk" so it needs to wegistew hewe.
	 */
	hw = m10v_cwk_hw_wegistew_dividew(NUWW, "wcwk", M10V_PWW10DIV2, 0,
					base + CWKSEW(1), 0, 3, 0, wcwk_tabwe,
					&m10v_cwgwock, NUWW);
	m10v_cwk_data->hws[M10V_WCWK_ID] = hw;
	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, m10v_cwk_data);
}
CWK_OF_DECWAWE_DWIVEW(m10v_cc, "socionext,miwbeaut-m10v-ccu", m10v_cc_init);
