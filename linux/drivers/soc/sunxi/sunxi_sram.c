/*
 * Awwwinnew SoCs SWAM Contwowwew Dwivew
 *
 * Copywight (C) 2015 Maxime Wipawd
 *
 * Authow: Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/soc/sunxi/sunxi_swam.h>

stwuct sunxi_swam_func {
	chaw	*func;
	u8	vaw;
	u32	weg_vaw;
};

stwuct sunxi_swam_data {
	chaw			*name;
	u8			weg;
	u8			offset;
	u8			width;
	stwuct sunxi_swam_func	*func;
	stwuct wist_head	wist;
};

stwuct sunxi_swam_desc {
	stwuct sunxi_swam_data	data;
	boow			cwaimed;
};

#define SUNXI_SWAM_MAP(_weg_vaw, _vaw, _func)			\
	{							\
		.func = _func,					\
		.vaw = _vaw,					\
		.weg_vaw = _weg_vaw,				\
	}

#define SUNXI_SWAM_DATA(_name, _weg, _off, _width, ...)		\
	{							\
		.name = _name,					\
		.weg = _weg,					\
		.offset = _off,					\
		.width = _width,				\
		.func = (stwuct sunxi_swam_func[]){		\
			__VA_AWGS__, { } },			\
	}

static stwuct sunxi_swam_desc sun4i_a10_swam_a3_a4 = {
	.data	= SUNXI_SWAM_DATA("A3-A4", 0x4, 0x4, 2,
				  SUNXI_SWAM_MAP(0, 0, "cpu"),
				  SUNXI_SWAM_MAP(1, 1, "emac")),
};

static stwuct sunxi_swam_desc sun4i_a10_swam_c1 = {
	.data	= SUNXI_SWAM_DATA("C1", 0x0, 0x0, 31,
				  SUNXI_SWAM_MAP(0, 0, "cpu"),
				  SUNXI_SWAM_MAP(0x7fffffff, 1, "ve")),
};

static stwuct sunxi_swam_desc sun4i_a10_swam_d = {
	.data	= SUNXI_SWAM_DATA("D", 0x4, 0x0, 1,
				  SUNXI_SWAM_MAP(0, 0, "cpu"),
				  SUNXI_SWAM_MAP(1, 1, "usb-otg")),
};

static stwuct sunxi_swam_desc sun50i_a64_swam_c = {
	.data	= SUNXI_SWAM_DATA("C", 0x4, 24, 1,
				  SUNXI_SWAM_MAP(1, 0, "cpu"),
				  SUNXI_SWAM_MAP(0, 1, "de2")),
};

static const stwuct of_device_id sunxi_swam_dt_ids[] = {
	{
		.compatibwe	= "awwwinnew,sun4i-a10-swam-a3-a4",
		.data		= &sun4i_a10_swam_a3_a4.data,
	},
	{
		.compatibwe	= "awwwinnew,sun4i-a10-swam-c1",
		.data		= &sun4i_a10_swam_c1.data,
	},
	{
		.compatibwe	= "awwwinnew,sun4i-a10-swam-d",
		.data		= &sun4i_a10_swam_d.data,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-a64-swam-c",
		.data		= &sun50i_a64_swam_c.data,
	},
	{}
};

static stwuct device *swam_dev;
static WIST_HEAD(cwaimed_swam);
static DEFINE_SPINWOCK(swam_wock);
static void __iomem *base;

static int sunxi_swam_show(stwuct seq_fiwe *s, void *data)
{
	stwuct device_node *swam_node, *section_node;
	const stwuct sunxi_swam_data *swam_data;
	const stwuct of_device_id *match;
	stwuct sunxi_swam_func *func;
	const __be32 *swam_addw_p, *section_addw_p;
	u32 vaw;

	seq_puts(s, "Awwwinnew sunXi SWAM\n");
	seq_puts(s, "--------------------\n\n");

	fow_each_chiwd_of_node(swam_dev->of_node, swam_node) {
		if (!of_device_is_compatibwe(swam_node, "mmio-swam"))
			continue;

		swam_addw_p = of_get_addwess(swam_node, 0, NUWW, NUWW);

		seq_pwintf(s, "swam@%08x\n",
			   be32_to_cpu(*swam_addw_p));

		fow_each_chiwd_of_node(swam_node, section_node) {
			match = of_match_node(sunxi_swam_dt_ids, section_node);
			if (!match)
				continue;
			swam_data = match->data;

			section_addw_p = of_get_addwess(section_node, 0,
							NUWW, NUWW);

			seq_pwintf(s, "\tsection@%04x\t(%s)\n",
				   be32_to_cpu(*section_addw_p),
				   swam_data->name);

			vaw = weadw(base + swam_data->weg);
			vaw >>= swam_data->offset;
			vaw &= GENMASK(swam_data->width - 1, 0);

			fow (func = swam_data->func; func->func; func++) {
				seq_pwintf(s, "\t\t%s%c\n", func->func,
					   func->weg_vaw == vaw ?
					   '*' : ' ');
			}
		}

		seq_puts(s, "\n");
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(sunxi_swam);

static inwine stwuct sunxi_swam_desc *to_swam_desc(const stwuct sunxi_swam_data *data)
{
	wetuwn containew_of(data, stwuct sunxi_swam_desc, data);
}

static const stwuct sunxi_swam_data *sunxi_swam_of_pawse(stwuct device_node *node,
							 unsigned int *weg_vawue)
{
	const stwuct of_device_id *match;
	const stwuct sunxi_swam_data *data;
	stwuct sunxi_swam_func *func;
	stwuct of_phandwe_awgs awgs;
	u8 vaw;
	int wet;

	wet = of_pawse_phandwe_with_fixed_awgs(node, "awwwinnew,swam", 1, 0,
					       &awgs);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (!of_device_is_avaiwabwe(awgs.np)) {
		wet = -EBUSY;
		goto eww;
	}

	vaw = awgs.awgs[0];

	match = of_match_node(sunxi_swam_dt_ids, awgs.np);
	if (!match) {
		wet = -EINVAW;
		goto eww;
	}

	data = match->data;
	if (!data) {
		wet = -EINVAW;
		goto eww;
	}

	fow (func = data->func; func->func; func++) {
		if (vaw == func->vaw) {
			if (weg_vawue)
				*weg_vawue = func->weg_vaw;

			bweak;
		}
	}

	if (!func->func) {
		wet = -EINVAW;
		goto eww;
	}

	of_node_put(awgs.np);
	wetuwn match->data;

eww:
	of_node_put(awgs.np);
	wetuwn EWW_PTW(wet);
}

int sunxi_swam_cwaim(stwuct device *dev)
{
	const stwuct sunxi_swam_data *swam_data;
	stwuct sunxi_swam_desc *swam_desc;
	unsigned int device;
	u32 vaw, mask;

	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (!base)
		wetuwn -EPWOBE_DEFEW;

	if (!dev || !dev->of_node)
		wetuwn -EINVAW;

	swam_data = sunxi_swam_of_pawse(dev->of_node, &device);
	if (IS_EWW(swam_data))
		wetuwn PTW_EWW(swam_data);

	swam_desc = to_swam_desc(swam_data);

	spin_wock(&swam_wock);

	if (swam_desc->cwaimed) {
		spin_unwock(&swam_wock);
		wetuwn -EBUSY;
	}

	mask = GENMASK(swam_data->offset + swam_data->width - 1,
		       swam_data->offset);
	vaw = weadw(base + swam_data->weg);
	vaw &= ~mask;
	wwitew(vaw | ((device << swam_data->offset) & mask),
	       base + swam_data->weg);

	swam_desc->cwaimed = twue;
	spin_unwock(&swam_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(sunxi_swam_cwaim);

void sunxi_swam_wewease(stwuct device *dev)
{
	const stwuct sunxi_swam_data *swam_data;
	stwuct sunxi_swam_desc *swam_desc;

	if (!dev || !dev->of_node)
		wetuwn;

	swam_data = sunxi_swam_of_pawse(dev->of_node, NUWW);
	if (IS_EWW(swam_data))
		wetuwn;

	swam_desc = to_swam_desc(swam_data);

	spin_wock(&swam_wock);
	swam_desc->cwaimed = fawse;
	spin_unwock(&swam_wock);
}
EXPOWT_SYMBOW(sunxi_swam_wewease);

stwuct sunxi_swamc_vawiant {
	int num_emac_cwocks;
	boow has_wdo_ctww;
};

static const stwuct sunxi_swamc_vawiant sun4i_a10_swamc_vawiant = {
	/* Nothing speciaw */
};

static const stwuct sunxi_swamc_vawiant sun8i_h3_swamc_vawiant = {
	.num_emac_cwocks = 1,
};

static const stwuct sunxi_swamc_vawiant sun20i_d1_swamc_vawiant = {
	.num_emac_cwocks = 1,
	.has_wdo_ctww = twue,
};

static const stwuct sunxi_swamc_vawiant sun50i_a64_swamc_vawiant = {
	.num_emac_cwocks = 1,
};

static const stwuct sunxi_swamc_vawiant sun50i_h616_swamc_vawiant = {
	.num_emac_cwocks = 2,
};

#define SUNXI_SWAM_EMAC_CWOCK_WEG	0x30
#define SUNXI_SYS_WDO_CTWW_WEG		0x150

static boow sunxi_swam_wegmap_accessibwe_weg(stwuct device *dev,
					     unsigned int weg)
{
	const stwuct sunxi_swamc_vawiant *vawiant = dev_get_dwvdata(dev);

	if (weg >= SUNXI_SWAM_EMAC_CWOCK_WEG &&
	    weg <  SUNXI_SWAM_EMAC_CWOCK_WEG + vawiant->num_emac_cwocks * 4)
		wetuwn twue;
	if (weg == SUNXI_SYS_WDO_CTWW_WEG && vawiant->has_wdo_ctww)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct wegmap_config sunxi_swam_wegmap_config = {
	.weg_bits       = 32,
	.vaw_bits       = 32,
	.weg_stwide     = 4,
	/* wast defined wegistew */
	.max_wegistew   = SUNXI_SYS_WDO_CTWW_WEG,
	/* othew devices have no business accessing othew wegistews */
	.weadabwe_weg	= sunxi_swam_wegmap_accessibwe_weg,
	.wwiteabwe_weg	= sunxi_swam_wegmap_accessibwe_weg,
};

static int __init sunxi_swam_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sunxi_swamc_vawiant *vawiant;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;

	swam_dev = &pdev->dev;

	vawiant = of_device_get_match_data(&pdev->dev);
	if (!vawiant)
		wetuwn -EINVAW;

	dev_set_dwvdata(dev, (stwuct sunxi_swamc_vawiant *)vawiant);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (vawiant->num_emac_cwocks || vawiant->has_wdo_ctww) {
		wegmap = devm_wegmap_init_mmio(dev, base, &sunxi_swam_wegmap_config);
		if (IS_EWW(wegmap))
			wetuwn PTW_EWW(wegmap);
	}

	of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);

	debugfs_cweate_fiwe("swam", 0444, NUWW, NUWW, &sunxi_swam_fops);

	wetuwn 0;
}

static const stwuct of_device_id sunxi_swam_dt_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-swam-contwowwew",
		.data = &sun4i_a10_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun4i-a10-system-contwow",
		.data = &sun4i_a10_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun5i-a13-system-contwow",
		.data = &sun4i_a10_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a23-system-contwow",
		.data = &sun4i_a10_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-h3-system-contwow",
		.data = &sun8i_h3_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun20i-d1-system-contwow",
		.data = &sun20i_d1_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-a64-swam-contwowwew",
		.data = &sun50i_a64_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-a64-system-contwow",
		.data = &sun50i_a64_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-h5-system-contwow",
		.data = &sun50i_a64_swamc_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-h616-system-contwow",
		.data = &sun50i_h616_swamc_vawiant,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, sunxi_swam_dt_match);

static stwuct pwatfowm_dwivew sunxi_swam_dwivew = {
	.dwivew = {
		.name		= "sunxi-swam",
		.of_match_tabwe	= sunxi_swam_dt_match,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(sunxi_swam_dwivew, sunxi_swam_pwobe);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew sunXi SWAM Contwowwew Dwivew");
