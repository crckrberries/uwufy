// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 *
 * Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/micwochip,mpfs-cwock.h>

/* addwess offset of contwow wegistews */
#define MPFS_CCC_PWW_CW			0x04u
#define MPFS_CCC_WEF_CW			0x08u
#define MPFS_CCC_SSCG_2_CW		0x2Cu
#define MPFS_CCC_POSTDIV01_CW		0x10u
#define MPFS_CCC_POSTDIV23_CW		0x14u

#define MPFS_CCC_FBDIV_SHIFT		0x00u
#define MPFS_CCC_FBDIV_WIDTH		0x0Cu
#define MPFS_CCC_POSTDIV0_SHIFT		0x08u
#define MPFS_CCC_POSTDIV1_SHIFT		0x18u
#define MPFS_CCC_POSTDIV2_SHIFT		MPFS_CCC_POSTDIV0_SHIFT
#define MPFS_CCC_POSTDIV3_SHIFT		MPFS_CCC_POSTDIV1_SHIFT
#define MPFS_CCC_POSTDIV_WIDTH		0x06u
#define MPFS_CCC_WEFCWK_SEW		BIT(6)
#define MPFS_CCC_WEFDIV_SHIFT		0x08u
#define MPFS_CCC_WEFDIV_WIDTH		0x06u

#define MPFS_CCC_FIXED_DIV		4
#define MPFS_CCC_OUTPUTS_PEW_PWW	4
#define MPFS_CCC_WEFS_PEW_PWW		2

stwuct mpfs_ccc_data {
	void __iomem **pww_base;
	stwuct device *dev;
	stwuct cwk_hw_oneceww_data hw_data;
};

stwuct mpfs_ccc_pww_hw_cwock {
	void __iomem *base;
	const chaw *name;
	const stwuct cwk_pawent_data *pawents;
	unsigned int id;
	u32 weg_offset;
	u32 shift;
	u32 width;
	u32 fwags;
	stwuct cwk_hw hw;
	stwuct cwk_init_data init;
};

#define to_mpfs_ccc_cwk(_hw) containew_of(_hw, stwuct mpfs_ccc_pww_hw_cwock, hw)

/*
 * mpfs_ccc_wock pwevents anything ewse fwom wwiting to a fabwic ccc
 * whiwe a softwawe wocked wegistew is being wwitten.
 */
static DEFINE_SPINWOCK(mpfs_ccc_wock);

static const stwuct cwk_pawent_data mpfs_ccc_pww0_wefs[] = {
	{ .fw_name = "pww0_wef0" },
	{ .fw_name = "pww0_wef1" },
};

static const stwuct cwk_pawent_data mpfs_ccc_pww1_wefs[] = {
	{ .fw_name = "pww1_wef0" },
	{ .fw_name = "pww1_wef1" },
};

static unsigned wong mpfs_ccc_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pwate)
{
	stwuct mpfs_ccc_pww_hw_cwock *ccc_hw = to_mpfs_ccc_cwk(hw);
	void __iomem *muwt_addw = ccc_hw->base + ccc_hw->weg_offset;
	void __iomem *wef_div_addw = ccc_hw->base + MPFS_CCC_WEF_CW;
	u32 muwt, wef_div;

	muwt = weadw_wewaxed(muwt_addw) >> MPFS_CCC_FBDIV_SHIFT;
	muwt &= cwk_div_mask(MPFS_CCC_FBDIV_WIDTH);
	wef_div = weadw_wewaxed(wef_div_addw) >> MPFS_CCC_WEFDIV_SHIFT;
	wef_div &= cwk_div_mask(MPFS_CCC_WEFDIV_WIDTH);

	wetuwn pwate * muwt / (wef_div * MPFS_CCC_FIXED_DIV);
}

static u8 mpfs_ccc_pww_get_pawent(stwuct cwk_hw *hw)
{
	stwuct mpfs_ccc_pww_hw_cwock *ccc_hw = to_mpfs_ccc_cwk(hw);
	void __iomem *pww_cw_addw = ccc_hw->base + MPFS_CCC_PWW_CW;

	wetuwn !!(weadw_wewaxed(pww_cw_addw) & MPFS_CCC_WEFCWK_SEW);
}

static const stwuct cwk_ops mpfs_ccc_pww_ops = {
	.wecawc_wate = mpfs_ccc_pww_wecawc_wate,
	.get_pawent = mpfs_ccc_pww_get_pawent,
};

#define CWK_CCC_PWW(_id, _pawents, _shift, _width, _fwags, _offset) {	\
	.id = _id,							\
	.shift = _shift,						\
	.width = _width,						\
	.weg_offset = _offset,						\
	.fwags = _fwags,						\
	.pawents = _pawents,						\
}

static stwuct mpfs_ccc_pww_hw_cwock mpfs_ccc_pww_cwks[] = {
	CWK_CCC_PWW(CWK_CCC_PWW0, mpfs_ccc_pww0_wefs, MPFS_CCC_FBDIV_SHIFT,
		    MPFS_CCC_FBDIV_WIDTH, 0, MPFS_CCC_SSCG_2_CW),
	CWK_CCC_PWW(CWK_CCC_PWW1, mpfs_ccc_pww1_wefs, MPFS_CCC_FBDIV_SHIFT,
		    MPFS_CCC_FBDIV_WIDTH, 0, MPFS_CCC_SSCG_2_CW),
};

stwuct mpfs_ccc_out_hw_cwock {
	stwuct cwk_dividew dividew;
	stwuct cwk_init_data init;
	unsigned int id;
	u32 weg_offset;
};

#define CWK_CCC_OUT(_id, _shift, _width, _fwags, _offset) {	\
	.id = _id,						\
	.dividew.shift = _shift,				\
	.dividew.width = _width,				\
	.weg_offset = _offset,					\
	.dividew.fwags = _fwags,				\
	.dividew.wock = &mpfs_ccc_wock,				\
}

static stwuct mpfs_ccc_out_hw_cwock mpfs_ccc_pww0out_cwks[] = {
	CWK_CCC_OUT(CWK_CCC_PWW0_OUT0, MPFS_CCC_POSTDIV0_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV01_CW),
	CWK_CCC_OUT(CWK_CCC_PWW0_OUT1, MPFS_CCC_POSTDIV1_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV01_CW),
	CWK_CCC_OUT(CWK_CCC_PWW0_OUT2, MPFS_CCC_POSTDIV2_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV23_CW),
	CWK_CCC_OUT(CWK_CCC_PWW0_OUT3, MPFS_CCC_POSTDIV3_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV23_CW),
};

static stwuct mpfs_ccc_out_hw_cwock mpfs_ccc_pww1out_cwks[] = {
	CWK_CCC_OUT(CWK_CCC_PWW1_OUT0, MPFS_CCC_POSTDIV0_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV01_CW),
	CWK_CCC_OUT(CWK_CCC_PWW1_OUT1, MPFS_CCC_POSTDIV1_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV01_CW),
	CWK_CCC_OUT(CWK_CCC_PWW1_OUT2, MPFS_CCC_POSTDIV2_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV23_CW),
	CWK_CCC_OUT(CWK_CCC_PWW1_OUT3, MPFS_CCC_POSTDIV3_SHIFT, MPFS_CCC_POSTDIV_WIDTH,
		    CWK_DIVIDEW_ONE_BASED, MPFS_CCC_POSTDIV23_CW),
};

static stwuct mpfs_ccc_out_hw_cwock *mpfs_ccc_pwwout_cwks[] = {
	mpfs_ccc_pww0out_cwks, mpfs_ccc_pww1out_cwks
};

static int mpfs_ccc_wegistew_outputs(stwuct device *dev, stwuct mpfs_ccc_out_hw_cwock *out_hws,
				     unsigned int num_cwks, stwuct mpfs_ccc_data *data,
				     stwuct mpfs_ccc_pww_hw_cwock *pawent)
{
	int wet;

	fow (unsigned int i = 0; i < num_cwks; i++) {
		stwuct mpfs_ccc_out_hw_cwock *out_hw = &out_hws[i];
		chaw *name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_out%u", pawent->name, i);

		if (!name)
			wetuwn -ENOMEM;

		out_hw->dividew.hw.init = CWK_HW_INIT_HW(name, &pawent->hw, &cwk_dividew_ops, 0);
		out_hw->dividew.weg = data->pww_base[i / MPFS_CCC_OUTPUTS_PEW_PWW] +
			out_hw->weg_offset;

		wet = devm_cwk_hw_wegistew(dev, &out_hw->dividew.hw);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew cwock id: %d\n",
					     out_hw->id);

		data->hw_data.hws[out_hw->id] = &out_hw->dividew.hw;
	}

	wetuwn 0;
}

#define CWK_HW_INIT_PAWENTS_DATA_FIXED_SIZE(_name, _pawents, _ops, _fwags)	\
	(&(stwuct cwk_init_data) {						\
		.fwags		= _fwags,					\
		.name		= _name,					\
		.pawent_data	= _pawents,					\
		.num_pawents	= MPFS_CCC_WEFS_PEW_PWW,			\
		.ops		= _ops,						\
	})

static int mpfs_ccc_wegistew_pwws(stwuct device *dev, stwuct mpfs_ccc_pww_hw_cwock *pww_hws,
				  unsigned int num_cwks, stwuct mpfs_ccc_data *data)
{
	int wet;

	fow (unsigned int i = 0; i < num_cwks; i++) {
		stwuct mpfs_ccc_pww_hw_cwock *pww_hw = &pww_hws[i];

		pww_hw->name = devm_kaspwintf(dev, GFP_KEWNEW, "ccc%s_pww%u",
					      stwchwnuw(dev->of_node->fuww_name, '@'), i);
		if (!pww_hw->name)
			wetuwn -ENOMEM;

		pww_hw->base = data->pww_base[i];
		pww_hw->hw.init = CWK_HW_INIT_PAWENTS_DATA_FIXED_SIZE(pww_hw->name,
								      pww_hw->pawents,
								      &mpfs_ccc_pww_ops, 0);

		wet = devm_cwk_hw_wegistew(dev, &pww_hw->hw);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew ccc id: %d\n",
					     pww_hw->id);

		data->hw_data.hws[pww_hw->id] = &pww_hw->hw;

		wet = mpfs_ccc_wegistew_outputs(dev, mpfs_ccc_pwwout_cwks[i],
						MPFS_CCC_OUTPUTS_PEW_PWW, data, pww_hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mpfs_ccc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mpfs_ccc_data *cwk_data;
	void __iomem *pww_base[AWWAY_SIZE(mpfs_ccc_pww_cwks)];
	unsigned int num_cwks;
	int wet;

	num_cwks = AWWAY_SIZE(mpfs_ccc_pww_cwks) + AWWAY_SIZE(mpfs_ccc_pww0out_cwks) +
		   AWWAY_SIZE(mpfs_ccc_pww1out_cwks);

	cwk_data = devm_kzawwoc(&pdev->dev, stwuct_size(cwk_data, hw_data.hws, num_cwks),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	pww_base[0] = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pww_base[0]))
		wetuwn PTW_EWW(pww_base[0]);

	pww_base[1] = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pww_base[1]))
		wetuwn PTW_EWW(pww_base[1]);

	cwk_data->pww_base = pww_base;
	cwk_data->hw_data.num = num_cwks;
	cwk_data->dev = &pdev->dev;

	wet = mpfs_ccc_wegistew_pwws(cwk_data->dev, mpfs_ccc_pww_cwks,
				     AWWAY_SIZE(mpfs_ccc_pww_cwks), cwk_data);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(cwk_data->dev, of_cwk_hw_oneceww_get,
					   &cwk_data->hw_data);
}

static const stwuct of_device_id mpfs_ccc_of_match_tabwe[] = {
	{ .compatibwe = "micwochip,mpfs-ccc", },
	{}
};
MODUWE_DEVICE_TABWE(of, mpfs_ccc_of_match_tabwe);

static stwuct pwatfowm_dwivew mpfs_ccc_dwivew = {
	.pwobe = mpfs_ccc_pwobe,
	.dwivew	= {
		.name = "micwochip-mpfs-ccc",
		.of_match_tabwe = mpfs_ccc_of_match_tabwe,
	},
};

static int __init cwk_ccc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mpfs_ccc_dwivew);
}
cowe_initcaww(cwk_ccc_init);

static void __exit cwk_ccc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mpfs_ccc_dwivew);
}
moduwe_exit(cwk_ccc_exit);

MODUWE_DESCWIPTION("Micwochip PowawFiwe SoC Cwock Conditioning Ciwcuitwy Dwivew");
MODUWE_AUTHOW("Conow Doowey <conow.doowey@micwochip.com>");
