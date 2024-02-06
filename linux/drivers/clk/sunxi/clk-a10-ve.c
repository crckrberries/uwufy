// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

static DEFINE_SPINWOCK(ve_wock);

#define SUN4I_VE_ENABWE		31
#define SUN4I_VE_DIVIDEW_SHIFT	16
#define SUN4I_VE_DIVIDEW_WIDTH	3
#define SUN4I_VE_WESET		0

/*
 * sunxi_ve_weset... - weset bit in ve cwk wegistews handwing
 */

stwuct ve_weset_data {
	void __iomem			*weg;
	spinwock_t			*wock;
	stwuct weset_contwowwew_dev	wcdev;
};

static int sunxi_ve_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct ve_weset_data *data = containew_of(wcdev,
						  stwuct ve_weset_data,
						  wcdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg & ~BIT(SUN4I_VE_WESET), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);

	wetuwn 0;
}

static int sunxi_ve_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id)
{
	stwuct ve_weset_data *data = containew_of(wcdev,
						  stwuct ve_weset_data,
						  wcdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg | BIT(SUN4I_VE_WESET), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);

	wetuwn 0;
}

static int sunxi_ve_of_xwate(stwuct weset_contwowwew_dev *wcdev,
			     const stwuct of_phandwe_awgs *weset_spec)
{
	if (WAWN_ON(weset_spec->awgs_count != 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct weset_contwow_ops sunxi_ve_weset_ops = {
	.assewt		= sunxi_ve_weset_assewt,
	.deassewt	= sunxi_ve_weset_deassewt,
};

static void __init sun4i_ve_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	stwuct cwk_dividew *div;
	stwuct cwk_gate *gate;
	stwuct ve_weset_data *weset_data;
	const chaw *pawent;
	const chaw *cwk_name = node->name;
	void __iomem *weg;
	int eww;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		goto eww_unmap;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		goto eww_fwee_div;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	pawent = of_cwk_get_pawent_name(node, 0);

	gate->weg = weg;
	gate->bit_idx = SUN4I_VE_ENABWE;
	gate->wock = &ve_wock;

	div->weg = weg;
	div->shift = SUN4I_VE_DIVIDEW_SHIFT;
	div->width = SUN4I_VE_DIVIDEW_WIDTH;
	div->wock = &ve_wock;

	cwk = cwk_wegistew_composite(NUWW, cwk_name, &pawent, 1,
				     NUWW, NUWW,
				     &div->hw, &cwk_dividew_ops,
				     &gate->hw, &cwk_gate_ops,
				     CWK_SET_WATE_PAWENT);
	if (IS_EWW(cwk))
		goto eww_fwee_gate;

	eww = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (eww)
		goto eww_unwegistew_cwk;

	weset_data = kzawwoc(sizeof(*weset_data), GFP_KEWNEW);
	if (!weset_data)
		goto eww_dew_pwovidew;

	weset_data->weg = weg;
	weset_data->wock = &ve_wock;
	weset_data->wcdev.nw_wesets = 1;
	weset_data->wcdev.ops = &sunxi_ve_weset_ops;
	weset_data->wcdev.of_node = node;
	weset_data->wcdev.of_xwate = sunxi_ve_of_xwate;
	weset_data->wcdev.of_weset_n_cewws = 0;
	eww = weset_contwowwew_wegistew(&weset_data->wcdev);
	if (eww)
		goto eww_fwee_weset;

	wetuwn;

eww_fwee_weset:
	kfwee(weset_data);
eww_dew_pwovidew:
	of_cwk_dew_pwovidew(node);
eww_unwegistew_cwk:
	cwk_unwegistew(cwk);
eww_fwee_gate:
	kfwee(gate);
eww_fwee_div:
	kfwee(div);
eww_unmap:
	iounmap(weg);
}
CWK_OF_DECWAWE(sun4i_ve, "awwwinnew,sun4i-a10-ve-cwk",
	       sun4i_ve_cwk_setup);
