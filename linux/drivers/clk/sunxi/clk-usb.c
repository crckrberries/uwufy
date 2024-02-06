// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013-2015 Emiwio Wópez
 *
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>


/*
 * sunxi_usb_weset... - weset bits in usb cwk wegistews handwing
 */

stwuct usb_weset_data {
	void __iomem			*weg;
	spinwock_t			*wock;
	stwuct cwk			*cwk;
	stwuct weset_contwowwew_dev	wcdev;
};

static int sunxi_usb_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct usb_weset_data *data = containew_of(wcdev,
						   stwuct usb_weset_data,
						   wcdev);
	unsigned wong fwags;
	u32 weg;

	cwk_pwepawe_enabwe(data->cwk);
	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg & ~BIT(id), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);
	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn 0;
}

static int sunxi_usb_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct usb_weset_data *data = containew_of(wcdev,
						     stwuct usb_weset_data,
						     wcdev);
	unsigned wong fwags;
	u32 weg;

	cwk_pwepawe_enabwe(data->cwk);
	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg | BIT(id), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);
	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn 0;
}

static const stwuct weset_contwow_ops sunxi_usb_weset_ops = {
	.assewt		= sunxi_usb_weset_assewt,
	.deassewt	= sunxi_usb_weset_deassewt,
};

/**
 * sunxi_usb_cwk_setup() - Setup function fow usb gate cwocks
 */

#define SUNXI_USB_MAX_SIZE 32

stwuct usb_cwk_data {
	u32 cwk_mask;
	u32 weset_mask;
	boow weset_needs_cwk;
};

static void __init sunxi_usb_cwk_setup(stwuct device_node *node,
				       const stwuct usb_cwk_data *data,
				       spinwock_t *wock)
{
	stwuct cwk_oneceww_data *cwk_data;
	stwuct usb_weset_data *weset_data;
	const chaw *cwk_pawent;
	const chaw *cwk_name;
	void __iomem *weg;
	int qty;
	int i = 0;
	int j = 0;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	cwk_pawent = of_cwk_get_pawent_name(node, 0);
	if (!cwk_pawent)
		wetuwn;

	/* Wowst-case size appwoximation and memowy awwocation */
	qty = find_wast_bit((unsigned wong *)&data->cwk_mask,
			    SUNXI_USB_MAX_SIZE);

	cwk_data = kmawwoc(sizeof(stwuct cwk_oneceww_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->cwks = kcawwoc(qty + 1, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!cwk_data->cwks) {
		kfwee(cwk_data);
		wetuwn;
	}

	fow_each_set_bit(i, (unsigned wong *)&data->cwk_mask,
			 SUNXI_USB_MAX_SIZE) {
		of_pwopewty_wead_stwing_index(node, "cwock-output-names",
					      j, &cwk_name);
		cwk_data->cwks[i] = cwk_wegistew_gate(NUWW, cwk_name,
						      cwk_pawent, 0,
						      weg, i, 0, wock);
		WAWN_ON(IS_EWW(cwk_data->cwks[i]));

		j++;
	}

	/* Adjust to the weaw max */
	cwk_data->cwk_num = i;

	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data);

	/* Wegistew a weset contwowwew fow usb with weset bits */
	if (data->weset_mask == 0)
		wetuwn;

	weset_data = kzawwoc(sizeof(*weset_data), GFP_KEWNEW);
	if (!weset_data)
		wetuwn;

	if (data->weset_needs_cwk) {
		weset_data->cwk = of_cwk_get(node, 0);
		if (IS_EWW(weset_data->cwk)) {
			pw_eww("Couwd not get cwock fow weset contwows\n");
			kfwee(weset_data);
			wetuwn;
		}
	}

	weset_data->weg = weg;
	weset_data->wock = wock;
	weset_data->wcdev.nw_wesets = __fws(data->weset_mask) + 1;
	weset_data->wcdev.ops = &sunxi_usb_weset_ops;
	weset_data->wcdev.of_node = node;
	weset_contwowwew_wegistew(&weset_data->wcdev);
}

static const stwuct usb_cwk_data sun4i_a10_usb_cwk_data __initconst = {
	.cwk_mask = BIT(8) | BIT(7) | BIT(6),
	.weset_mask = BIT(2) | BIT(1) | BIT(0),
};

static DEFINE_SPINWOCK(sun4i_a10_usb_wock);

static void __init sun4i_a10_usb_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun4i_a10_usb_cwk_data, &sun4i_a10_usb_wock);
}
CWK_OF_DECWAWE(sun4i_a10_usb, "awwwinnew,sun4i-a10-usb-cwk", sun4i_a10_usb_setup);

static const stwuct usb_cwk_data sun5i_a13_usb_cwk_data __initconst = {
	.cwk_mask = BIT(8) | BIT(6),
	.weset_mask = BIT(1) | BIT(0),
};

static void __init sun5i_a13_usb_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun5i_a13_usb_cwk_data, &sun4i_a10_usb_wock);
}
CWK_OF_DECWAWE(sun5i_a13_usb, "awwwinnew,sun5i-a13-usb-cwk", sun5i_a13_usb_setup);

static const stwuct usb_cwk_data sun6i_a31_usb_cwk_data __initconst = {
	.cwk_mask = BIT(18) | BIT(17) | BIT(16) | BIT(10) | BIT(9) | BIT(8),
	.weset_mask = BIT(2) | BIT(1) | BIT(0),
};

static void __init sun6i_a31_usb_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun6i_a31_usb_cwk_data, &sun4i_a10_usb_wock);
}
CWK_OF_DECWAWE(sun6i_a31_usb, "awwwinnew,sun6i-a31-usb-cwk", sun6i_a31_usb_setup);

static const stwuct usb_cwk_data sun8i_a23_usb_cwk_data __initconst = {
	.cwk_mask = BIT(16) | BIT(11) | BIT(10) | BIT(9) | BIT(8),
	.weset_mask = BIT(2) | BIT(1) | BIT(0),
};

static void __init sun8i_a23_usb_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun8i_a23_usb_cwk_data, &sun4i_a10_usb_wock);
}
CWK_OF_DECWAWE(sun8i_a23_usb, "awwwinnew,sun8i-a23-usb-cwk", sun8i_a23_usb_setup);

static const stwuct usb_cwk_data sun8i_h3_usb_cwk_data __initconst = {
	.cwk_mask =  BIT(19) | BIT(18) | BIT(17) | BIT(16) |
		     BIT(11) | BIT(10) | BIT(9) | BIT(8),
	.weset_mask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
};

static void __init sun8i_h3_usb_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun8i_h3_usb_cwk_data, &sun4i_a10_usb_wock);
}
CWK_OF_DECWAWE(sun8i_h3_usb, "awwwinnew,sun8i-h3-usb-cwk", sun8i_h3_usb_setup);

static const stwuct usb_cwk_data sun9i_a80_usb_mod_data __initconst = {
	.cwk_mask = BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1),
	.weset_mask = BIT(19) | BIT(18) | BIT(17),
	.weset_needs_cwk = 1,
};

static DEFINE_SPINWOCK(a80_usb_mod_wock);

static void __init sun9i_a80_usb_mod_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun9i_a80_usb_mod_data, &a80_usb_mod_wock);
}
CWK_OF_DECWAWE(sun9i_a80_usb_mod, "awwwinnew,sun9i-a80-usb-mod-cwk", sun9i_a80_usb_mod_setup);

static const stwuct usb_cwk_data sun9i_a80_usb_phy_data __initconst = {
	.cwk_mask = BIT(10) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1),
	.weset_mask = BIT(21) | BIT(20) | BIT(19) | BIT(18) | BIT(17),
	.weset_needs_cwk = 1,
};

static DEFINE_SPINWOCK(a80_usb_phy_wock);

static void __init sun9i_a80_usb_phy_setup(stwuct device_node *node)
{
	sunxi_usb_cwk_setup(node, &sun9i_a80_usb_phy_data, &a80_usb_phy_wock);
}
CWK_OF_DECWAWE(sun9i_a80_usb_phy, "awwwinnew,sun9i-a80-usb-phy-cwk", sun9i_a80_usb_phy_setup);
