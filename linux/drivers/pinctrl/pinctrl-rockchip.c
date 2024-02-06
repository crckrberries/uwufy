// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww dwivew fow Wockchip SoCs
 *
 * Copywight (c) 2013 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * With some ideas taken fwom pinctww-samsung:
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Copywight (c) 2012 Winawo Wtd
 *		https://www.winawo.owg
 *
 * and pinctww-at91:
 * Copywight (C) 2011-2012 Jean-Chwistophe PWAGNIOW-VIWWAWD <pwagnioj@jcwosoft.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/stwing_hewpews.h>

#incwude <dt-bindings/pinctww/wockchip.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-wockchip.h"

/*
 * Genewate a bitmask fow setting a vawue (v) with a wwite mask bit in hiwowd
 * wegistew 31:16 awea.
 */
#define WWITE_MASK_VAW(h, w, v) \
	(GENMASK(((h) + 16), ((w) + 16)) | (((v) << (w)) & GENMASK((h), (w))))

/*
 * Encode vawiants of iomux wegistews into a type vawiabwe
 */
#define IOMUX_GPIO_ONWY		BIT(0)
#define IOMUX_WIDTH_4BIT	BIT(1)
#define IOMUX_SOUWCE_PMU	BIT(2)
#define IOMUX_UNWOUTED		BIT(3)
#define IOMUX_WIDTH_3BIT	BIT(4)
#define IOMUX_WIDTH_2BIT	BIT(5)
#define IOMUX_W_SOUWCE_PMU	BIT(6)

#define PIN_BANK(id, pins, wabew)			\
	{						\
		.bank_num	= id,			\
		.nw_pins	= pins,			\
		.name		= wabew,		\
		.iomux		= {			\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
		},					\
	}

#define PIN_BANK_IOMUX_FWAGS(id, pins, wabew, iom0, iom1, iom2, iom3)	\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
	}

#define PIN_BANK_DWV_FWAGS(id, pins, wabew, type0, type1, type2, type3) \
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
		},							\
		.dwv		= {					\
			{ .dwv_type = type0, .offset = -1 },		\
			{ .dwv_type = type1, .offset = -1 },		\
			{ .dwv_type = type2, .offset = -1 },		\
			{ .dwv_type = type3, .offset = -1 },		\
		},							\
	}

#define PIN_BANK_IOMUX_FWAGS_PUWW_FWAGS(id, pins, wabew, iom0, iom1,	\
					iom2, iom3, puww0, puww1,	\
					puww2, puww3)			\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.puww_type[0] = puww0,					\
		.puww_type[1] = puww1,					\
		.puww_type[2] = puww2,					\
		.puww_type[3] = puww3,					\
	}

#define PIN_BANK_DWV_FWAGS_PUWW_FWAGS(id, pins, wabew, dwv0, dwv1,	\
				      dwv2, dwv3, puww0, puww1,		\
				      puww2, puww3)			\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
		},							\
		.dwv		= {					\
			{ .dwv_type = dwv0, .offset = -1 },		\
			{ .dwv_type = dwv1, .offset = -1 },		\
			{ .dwv_type = dwv2, .offset = -1 },		\
			{ .dwv_type = dwv3, .offset = -1 },		\
		},							\
		.puww_type[0] = puww0,					\
		.puww_type[1] = puww1,					\
		.puww_type[2] = puww2,					\
		.puww_type[3] = puww3,					\
	}

#define PIN_BANK_IOMUX_FWAGS_OFFSET(id, pins, wabew, iom0, iom1, iom2,	\
				    iom3, offset0, offset1, offset2,	\
				    offset3)				\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .type = iom0, .offset = offset0 },		\
			{ .type = iom1, .offset = offset1 },		\
			{ .type = iom2, .offset = offset2 },		\
			{ .type = iom3, .offset = offset3 },		\
		},							\
	}

#define PIN_BANK_IOMUX_DWV_FWAGS_OFFSET(id, pins, wabew, iom0, iom1,	\
					iom2, iom3, dwv0, dwv1, dwv2,	\
					dwv3, offset0, offset1,		\
					offset2, offset3)		\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.dwv		= {					\
			{ .dwv_type = dwv0, .offset = offset0 },	\
			{ .dwv_type = dwv1, .offset = offset1 },	\
			{ .dwv_type = dwv2, .offset = offset2 },	\
			{ .dwv_type = dwv3, .offset = offset3 },	\
		},							\
	}

#define PIN_BANK_IOMUX_FWAGS_DWV_FWAGS_OFFSET_PUWW_FWAGS(id, pins,	\
					      wabew, iom0, iom1, iom2,  \
					      iom3, dwv0, dwv1, dwv2,   \
					      dwv3, offset0, offset1,   \
					      offset2, offset3, puww0,  \
					      puww1, puww2, puww3)	\
	{								\
		.bank_num	= id,					\
		.nw_pins	= pins,					\
		.name		= wabew,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.dwv		= {					\
			{ .dwv_type = dwv0, .offset = offset0 },	\
			{ .dwv_type = dwv1, .offset = offset1 },	\
			{ .dwv_type = dwv2, .offset = offset2 },	\
			{ .dwv_type = dwv3, .offset = offset3 },	\
		},							\
		.puww_type[0] = puww0,					\
		.puww_type[1] = puww1,					\
		.puww_type[2] = puww2,					\
		.puww_type[3] = puww3,					\
	}

#define PIN_BANK_MUX_WOUTE_FWAGS(ID, PIN, FUNC, WEG, VAW, FWAG)		\
	{								\
		.bank_num	= ID,					\
		.pin		= PIN,					\
		.func		= FUNC,					\
		.woute_offset	= WEG,					\
		.woute_vaw	= VAW,					\
		.woute_wocation	= FWAG,					\
	}

#define WK_MUXWOUTE_SAME(ID, PIN, FUNC, WEG, VAW)	\
	PIN_BANK_MUX_WOUTE_FWAGS(ID, PIN, FUNC, WEG, VAW, WOCKCHIP_WOUTE_SAME)

#define WK_MUXWOUTE_GWF(ID, PIN, FUNC, WEG, VAW)	\
	PIN_BANK_MUX_WOUTE_FWAGS(ID, PIN, FUNC, WEG, VAW, WOCKCHIP_WOUTE_GWF)

#define WK_MUXWOUTE_PMU(ID, PIN, FUNC, WEG, VAW)	\
	PIN_BANK_MUX_WOUTE_FWAGS(ID, PIN, FUNC, WEG, VAW, WOCKCHIP_WOUTE_PMU)

#define WK3588_PIN_BANK_FWAGS(ID, PIN, WABEW, M, P)			\
	PIN_BANK_IOMUX_FWAGS_PUWW_FWAGS(ID, PIN, WABEW, M, M, M, M, P, P, P, P)

static stwuct wegmap_config wockchip_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static inwine const stwuct wockchip_pin_gwoup *pinctww_name_to_gwoup(
					const stwuct wockchip_pinctww *info,
					const chaw *name)
{
	int i;

	fow (i = 0; i < info->ngwoups; i++) {
		if (!stwcmp(info->gwoups[i].name, name))
			wetuwn &info->gwoups[i];
	}

	wetuwn NUWW;
}

/*
 * given a pin numbew that is wocaw to a pin contwowwew, find out the pin bank
 * and the wegistew base of the pin bank.
 */
static stwuct wockchip_pin_bank *pin_to_bank(stwuct wockchip_pinctww *info,
								unsigned pin)
{
	stwuct wockchip_pin_bank *b = info->ctww->pin_banks;

	whiwe (pin >= (b->pin_base + b->nw_pins))
		b++;

	wetuwn b;
}

static stwuct wockchip_pin_bank *bank_num_to_bank(
					stwuct wockchip_pinctww *info,
					unsigned num)
{
	stwuct wockchip_pin_bank *b = info->ctww->pin_banks;
	int i;

	fow (i = 0; i < info->ctww->nw_banks; i++, b++) {
		if (b->bank_num == num)
			wetuwn b;
	}

	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Pinctww_ops handwing
 */

static int wockchip_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->ngwoups;
}

static const chaw *wockchip_get_gwoup_name(stwuct pinctww_dev *pctwdev,
							unsigned sewectow)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->gwoups[sewectow].name;
}

static int wockchip_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow, const unsigned **pins,
				      unsigned *npins)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	*pins = info->gwoups[sewectow].pins;
	*npins = info->gwoups[sewectow].npins;

	wetuwn 0;
}

static int wockchip_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				 stwuct device_node *np,
				 stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct wockchip_pin_gwoup *gwp;
	stwuct device *dev = info->dev;
	stwuct pinctww_map *new_map;
	stwuct device_node *pawent;
	int map_num = 1;
	int i;

	/*
	 * fiwst find the gwoup of this node and check if we need to cweate
	 * config maps fow pins
	 */
	gwp = pinctww_name_to_gwoup(info, np->name);
	if (!gwp) {
		dev_eww(dev, "unabwe to find gwoup fow node %pOFn\n", np);
		wetuwn -EINVAW;
	}

	map_num += gwp->npins;

	new_map = kcawwoc(map_num, sizeof(*new_map), GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* cweate mux map */
	pawent = of_get_pawent(np);
	if (!pawent) {
		kfwee(new_map);
		wetuwn -EINVAW;
	}
	new_map[0].type = PIN_MAP_TYPE_MUX_GWOUP;
	new_map[0].data.mux.function = pawent->name;
	new_map[0].data.mux.gwoup = np->name;
	of_node_put(pawent);

	/* cweate config map */
	new_map++;
	fow (i = 0; i < gwp->npins; i++) {
		new_map[i].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[i].data.configs.gwoup_ow_pin =
				pin_get_name(pctwdev, gwp->pins[i]);
		new_map[i].data.configs.configs = gwp->data[i].configs;
		new_map[i].data.configs.num_configs = gwp->data[i].nconfigs;
	}

	dev_dbg(dev, "maps: function %s gwoup %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.gwoup, map_num);

	wetuwn 0;
}

static void wockchip_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_map *map, unsigned num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops wockchip_pctww_ops = {
	.get_gwoups_count	= wockchip_get_gwoups_count,
	.get_gwoup_name		= wockchip_get_gwoup_name,
	.get_gwoup_pins		= wockchip_get_gwoup_pins,
	.dt_node_to_map		= wockchip_dt_node_to_map,
	.dt_fwee_map		= wockchip_dt_fwee_map,
};

/*
 * Hawdwawe access
 */

static stwuct wockchip_mux_wecawced_data wv1108_mux_wecawced_data[] = {
	{
		.num = 1,
		.pin = 0,
		.weg = 0x418,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 1,
		.weg = 0x418,
		.bit = 2,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 2,
		.weg = 0x418,
		.bit = 4,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 3,
		.weg = 0x418,
		.bit = 6,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 4,
		.weg = 0x418,
		.bit = 8,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 5,
		.weg = 0x418,
		.bit = 10,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 6,
		.weg = 0x418,
		.bit = 12,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 7,
		.weg = 0x418,
		.bit = 14,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 8,
		.weg = 0x41c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 9,
		.weg = 0x41c,
		.bit = 2,
		.mask = 0x3
	},
};

static stwuct wockchip_mux_wecawced_data wv1126_mux_wecawced_data[] = {
	{
		.num = 0,
		.pin = 20,
		.weg = 0x10000,
		.bit = 0,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 21,
		.weg = 0x10000,
		.bit = 4,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 22,
		.weg = 0x10000,
		.bit = 8,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 23,
		.weg = 0x10000,
		.bit = 12,
		.mask = 0xf
	},
};

static  stwuct wockchip_mux_wecawced_data wk3128_mux_wecawced_data[] = {
	{
		.num = 2,
		.pin = 20,
		.weg = 0xe8,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 21,
		.weg = 0xe8,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 22,
		.weg = 0xe8,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 23,
		.weg = 0xe8,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 24,
		.weg = 0xd4,
		.bit = 12,
		.mask = 0x7
	},
};

static stwuct wockchip_mux_wecawced_data wk3308_mux_wecawced_data[] = {
	{
		/* gpio1b6_sew */
		.num = 1,
		.pin = 14,
		.weg = 0x28,
		.bit = 12,
		.mask = 0xf
	}, {
		/* gpio1b7_sew */
		.num = 1,
		.pin = 15,
		.weg = 0x2c,
		.bit = 0,
		.mask = 0x3
	}, {
		/* gpio1c2_sew */
		.num = 1,
		.pin = 18,
		.weg = 0x30,
		.bit = 4,
		.mask = 0xf
	}, {
		/* gpio1c3_sew */
		.num = 1,
		.pin = 19,
		.weg = 0x30,
		.bit = 8,
		.mask = 0xf
	}, {
		/* gpio1c4_sew */
		.num = 1,
		.pin = 20,
		.weg = 0x30,
		.bit = 12,
		.mask = 0xf
	}, {
		/* gpio1c5_sew */
		.num = 1,
		.pin = 21,
		.weg = 0x34,
		.bit = 0,
		.mask = 0xf
	}, {
		/* gpio1c6_sew */
		.num = 1,
		.pin = 22,
		.weg = 0x34,
		.bit = 4,
		.mask = 0xf
	}, {
		/* gpio1c7_sew */
		.num = 1,
		.pin = 23,
		.weg = 0x34,
		.bit = 8,
		.mask = 0xf
	}, {
		/* gpio2a2_sew */
		.num = 2,
		.pin = 2,
		.weg = 0x40,
		.bit = 4,
		.mask = 0x3
	}, {
		/* gpio2a3_sew */
		.num = 2,
		.pin = 3,
		.weg = 0x40,
		.bit = 6,
		.mask = 0x3
	}, {
		/* gpio2c0_sew */
		.num = 2,
		.pin = 16,
		.weg = 0x50,
		.bit = 0,
		.mask = 0x3
	}, {
		/* gpio3b2_sew */
		.num = 3,
		.pin = 10,
		.weg = 0x68,
		.bit = 4,
		.mask = 0x3
	}, {
		/* gpio3b3_sew */
		.num = 3,
		.pin = 11,
		.weg = 0x68,
		.bit = 6,
		.mask = 0x3
	}, {
		/* gpio3b4_sew */
		.num = 3,
		.pin = 12,
		.weg = 0x68,
		.bit = 8,
		.mask = 0xf
	}, {
		/* gpio3b5_sew */
		.num = 3,
		.pin = 13,
		.weg = 0x68,
		.bit = 12,
		.mask = 0xf
	},
};

static stwuct wockchip_mux_wecawced_data wk3328_mux_wecawced_data[] = {
	{
		.num = 2,
		.pin = 12,
		.weg = 0x24,
		.bit = 8,
		.mask = 0x3
	}, {
		.num = 2,
		.pin = 15,
		.weg = 0x28,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 23,
		.weg = 0x30,
		.bit = 14,
		.mask = 0x3
	},
};

static void wockchip_get_wecawced_mux(stwuct wockchip_pin_bank *bank, int pin,
				      int *weg, u8 *bit, int *mask)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct wockchip_mux_wecawced_data *data;
	int i;

	fow (i = 0; i < ctww->niomux_wecawced; i++) {
		data = &ctww->iomux_wecawced[i];
		if (data->num == bank->bank_num &&
		    data->pin == pin)
			bweak;
	}

	if (i >= ctww->niomux_wecawced)
		wetuwn;

	*weg = data->weg;
	*mask = data->mask;
	*bit = data->bit;
}

static stwuct wockchip_mux_woute_data px30_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(2, WK_PB4, 1, 0x184, BIT(16 + 7)), /* cif-d0m0 */
	WK_MUXWOUTE_SAME(3, WK_PA1, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d0m1 */
	WK_MUXWOUTE_SAME(2, WK_PB6, 1, 0x184, BIT(16 + 7)), /* cif-d1m0 */
	WK_MUXWOUTE_SAME(3, WK_PA2, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d1m1 */
	WK_MUXWOUTE_SAME(2, WK_PA0, 1, 0x184, BIT(16 + 7)), /* cif-d2m0 */
	WK_MUXWOUTE_SAME(3, WK_PA3, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d2m1 */
	WK_MUXWOUTE_SAME(2, WK_PA1, 1, 0x184, BIT(16 + 7)), /* cif-d3m0 */
	WK_MUXWOUTE_SAME(3, WK_PA5, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d3m1 */
	WK_MUXWOUTE_SAME(2, WK_PA2, 1, 0x184, BIT(16 + 7)), /* cif-d4m0 */
	WK_MUXWOUTE_SAME(3, WK_PA7, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d4m1 */
	WK_MUXWOUTE_SAME(2, WK_PA3, 1, 0x184, BIT(16 + 7)), /* cif-d5m0 */
	WK_MUXWOUTE_SAME(3, WK_PB0, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d5m1 */
	WK_MUXWOUTE_SAME(2, WK_PA4, 1, 0x184, BIT(16 + 7)), /* cif-d6m0 */
	WK_MUXWOUTE_SAME(3, WK_PB1, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d6m1 */
	WK_MUXWOUTE_SAME(2, WK_PA5, 1, 0x184, BIT(16 + 7)), /* cif-d7m0 */
	WK_MUXWOUTE_SAME(3, WK_PB4, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d7m1 */
	WK_MUXWOUTE_SAME(2, WK_PA6, 1, 0x184, BIT(16 + 7)), /* cif-d8m0 */
	WK_MUXWOUTE_SAME(3, WK_PB6, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d8m1 */
	WK_MUXWOUTE_SAME(2, WK_PA7, 1, 0x184, BIT(16 + 7)), /* cif-d9m0 */
	WK_MUXWOUTE_SAME(3, WK_PB7, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d9m1 */
	WK_MUXWOUTE_SAME(2, WK_PB7, 1, 0x184, BIT(16 + 7)), /* cif-d10m0 */
	WK_MUXWOUTE_SAME(3, WK_PC6, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d10m1 */
	WK_MUXWOUTE_SAME(2, WK_PC0, 1, 0x184, BIT(16 + 7)), /* cif-d11m0 */
	WK_MUXWOUTE_SAME(3, WK_PC7, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-d11m1 */
	WK_MUXWOUTE_SAME(2, WK_PB0, 1, 0x184, BIT(16 + 7)), /* cif-vsyncm0 */
	WK_MUXWOUTE_SAME(3, WK_PD1, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-vsyncm1 */
	WK_MUXWOUTE_SAME(2, WK_PB1, 1, 0x184, BIT(16 + 7)), /* cif-hwefm0 */
	WK_MUXWOUTE_SAME(3, WK_PD2, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-hwefm1 */
	WK_MUXWOUTE_SAME(2, WK_PB2, 1, 0x184, BIT(16 + 7)), /* cif-cwkinm0 */
	WK_MUXWOUTE_SAME(3, WK_PD3, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-cwkinm1 */
	WK_MUXWOUTE_SAME(2, WK_PB3, 1, 0x184, BIT(16 + 7)), /* cif-cwkoutm0 */
	WK_MUXWOUTE_SAME(3, WK_PD0, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cif-cwkoutm1 */
	WK_MUXWOUTE_SAME(3, WK_PC6, 2, 0x184, BIT(16 + 8)), /* pdm-m0 */
	WK_MUXWOUTE_SAME(2, WK_PC6, 1, 0x184, BIT(16 + 8) | BIT(8)), /* pdm-m1 */
	WK_MUXWOUTE_SAME(3, WK_PD3, 2, 0x184, BIT(16 + 8)), /* pdm-sdi0m0 */
	WK_MUXWOUTE_SAME(2, WK_PC5, 2, 0x184, BIT(16 + 8) | BIT(8)), /* pdm-sdi0m1 */
	WK_MUXWOUTE_SAME(1, WK_PD3, 2, 0x184, BIT(16 + 10)), /* uawt2-wxm0 */
	WK_MUXWOUTE_SAME(2, WK_PB6, 2, 0x184, BIT(16 + 10) | BIT(10)), /* uawt2-wxm1 */
	WK_MUXWOUTE_SAME(1, WK_PD2, 2, 0x184, BIT(16 + 10)), /* uawt2-txm0 */
	WK_MUXWOUTE_SAME(2, WK_PB4, 2, 0x184, BIT(16 + 10) | BIT(10)), /* uawt2-txm1 */
	WK_MUXWOUTE_SAME(0, WK_PC1, 2, 0x184, BIT(16 + 9)), /* uawt3-wxm0 */
	WK_MUXWOUTE_SAME(1, WK_PB7, 2, 0x184, BIT(16 + 9) | BIT(9)), /* uawt3-wxm1 */
	WK_MUXWOUTE_SAME(0, WK_PC0, 2, 0x184, BIT(16 + 9)), /* uawt3-txm0 */
	WK_MUXWOUTE_SAME(1, WK_PB6, 2, 0x184, BIT(16 + 9) | BIT(9)), /* uawt3-txm1 */
	WK_MUXWOUTE_SAME(0, WK_PC2, 2, 0x184, BIT(16 + 9)), /* uawt3-ctsm0 */
	WK_MUXWOUTE_SAME(1, WK_PB4, 2, 0x184, BIT(16 + 9) | BIT(9)), /* uawt3-ctsm1 */
	WK_MUXWOUTE_SAME(0, WK_PC3, 2, 0x184, BIT(16 + 9)), /* uawt3-wtsm0 */
	WK_MUXWOUTE_SAME(1, WK_PB5, 2, 0x184, BIT(16 + 9) | BIT(9)), /* uawt3-wtsm1 */
};

static stwuct wockchip_mux_woute_data wv1126_mux_woute_data[] = {
	WK_MUXWOUTE_GWF(3, WK_PD2, 1, 0x10260, WWITE_MASK_VAW(0, 0, 0)), /* I2S0_MCWK_M0 */
	WK_MUXWOUTE_GWF(3, WK_PB0, 3, 0x10260, WWITE_MASK_VAW(0, 0, 1)), /* I2S0_MCWK_M1 */

	WK_MUXWOUTE_GWF(0, WK_PD4, 4, 0x10260, WWITE_MASK_VAW(3, 2, 0)), /* I2S1_MCWK_M0 */
	WK_MUXWOUTE_GWF(1, WK_PD5, 2, 0x10260, WWITE_MASK_VAW(3, 2, 1)), /* I2S1_MCWK_M1 */
	WK_MUXWOUTE_GWF(2, WK_PC7, 6, 0x10260, WWITE_MASK_VAW(3, 2, 2)), /* I2S1_MCWK_M2 */

	WK_MUXWOUTE_GWF(1, WK_PD0, 1, 0x10260, WWITE_MASK_VAW(4, 4, 0)), /* I2S2_MCWK_M0 */
	WK_MUXWOUTE_GWF(2, WK_PB3, 2, 0x10260, WWITE_MASK_VAW(4, 4, 1)), /* I2S2_MCWK_M1 */

	WK_MUXWOUTE_GWF(3, WK_PD4, 2, 0x10260, WWITE_MASK_VAW(12, 12, 0)), /* PDM_CWK0_M0 */
	WK_MUXWOUTE_GWF(3, WK_PC0, 3, 0x10260, WWITE_MASK_VAW(12, 12, 1)), /* PDM_CWK0_M1 */

	WK_MUXWOUTE_GWF(3, WK_PC6, 1, 0x10264, WWITE_MASK_VAW(0, 0, 0)), /* CIF_CWKOUT_M0 */
	WK_MUXWOUTE_GWF(2, WK_PD1, 3, 0x10264, WWITE_MASK_VAW(0, 0, 1)), /* CIF_CWKOUT_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA4, 5, 0x10264, WWITE_MASK_VAW(5, 4, 0)), /* I2C3_SCW_M0 */
	WK_MUXWOUTE_GWF(2, WK_PD4, 7, 0x10264, WWITE_MASK_VAW(5, 4, 1)), /* I2C3_SCW_M1 */
	WK_MUXWOUTE_GWF(1, WK_PD6, 3, 0x10264, WWITE_MASK_VAW(5, 4, 2)), /* I2C3_SCW_M2 */

	WK_MUXWOUTE_GWF(3, WK_PA0, 7, 0x10264, WWITE_MASK_VAW(6, 6, 0)), /* I2C4_SCW_M0 */
	WK_MUXWOUTE_GWF(4, WK_PA0, 4, 0x10264, WWITE_MASK_VAW(6, 6, 1)), /* I2C4_SCW_M1 */

	WK_MUXWOUTE_GWF(2, WK_PA5, 7, 0x10264, WWITE_MASK_VAW(9, 8, 0)), /* I2C5_SCW_M0 */
	WK_MUXWOUTE_GWF(3, WK_PB0, 5, 0x10264, WWITE_MASK_VAW(9, 8, 1)), /* I2C5_SCW_M1 */
	WK_MUXWOUTE_GWF(1, WK_PD0, 4, 0x10264, WWITE_MASK_VAW(9, 8, 2)), /* I2C5_SCW_M2 */

	WK_MUXWOUTE_GWF(3, WK_PC0, 5, 0x10264, WWITE_MASK_VAW(11, 10, 0)), /* SPI1_CWK_M0 */
	WK_MUXWOUTE_GWF(1, WK_PC6, 3, 0x10264, WWITE_MASK_VAW(11, 10, 1)), /* SPI1_CWK_M1 */
	WK_MUXWOUTE_GWF(2, WK_PD5, 6, 0x10264, WWITE_MASK_VAW(11, 10, 2)), /* SPI1_CWK_M2 */

	WK_MUXWOUTE_GWF(3, WK_PC0, 2, 0x10264, WWITE_MASK_VAW(12, 12, 0)), /* WGMII_CWK_M0 */
	WK_MUXWOUTE_GWF(2, WK_PB7, 2, 0x10264, WWITE_MASK_VAW(12, 12, 1)), /* WGMII_CWK_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA1, 3, 0x10264, WWITE_MASK_VAW(13, 13, 0)), /* CAN_TXD_M0 */
	WK_MUXWOUTE_GWF(3, WK_PA7, 5, 0x10264, WWITE_MASK_VAW(13, 13, 1)), /* CAN_TXD_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA4, 6, 0x10268, WWITE_MASK_VAW(0, 0, 0)), /* PWM8_M0 */
	WK_MUXWOUTE_GWF(2, WK_PD7, 5, 0x10268, WWITE_MASK_VAW(0, 0, 1)), /* PWM8_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA5, 6, 0x10268, WWITE_MASK_VAW(2, 2, 0)), /* PWM9_M0 */
	WK_MUXWOUTE_GWF(2, WK_PD6, 5, 0x10268, WWITE_MASK_VAW(2, 2, 1)), /* PWM9_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA6, 6, 0x10268, WWITE_MASK_VAW(4, 4, 0)), /* PWM10_M0 */
	WK_MUXWOUTE_GWF(2, WK_PD5, 5, 0x10268, WWITE_MASK_VAW(4, 4, 1)), /* PWM10_M1 */

	WK_MUXWOUTE_GWF(3, WK_PA7, 6, 0x10268, WWITE_MASK_VAW(6, 6, 0)), /* PWM11_IW_M0 */
	WK_MUXWOUTE_GWF(3, WK_PA1, 5, 0x10268, WWITE_MASK_VAW(6, 6, 1)), /* PWM11_IW_M1 */

	WK_MUXWOUTE_GWF(1, WK_PA5, 3, 0x10268, WWITE_MASK_VAW(8, 8, 0)), /* UAWT2_TX_M0 */
	WK_MUXWOUTE_GWF(3, WK_PA2, 1, 0x10268, WWITE_MASK_VAW(8, 8, 1)), /* UAWT2_TX_M1 */

	WK_MUXWOUTE_GWF(3, WK_PC6, 3, 0x10268, WWITE_MASK_VAW(11, 10, 0)), /* UAWT3_TX_M0 */
	WK_MUXWOUTE_GWF(1, WK_PA7, 2, 0x10268, WWITE_MASK_VAW(11, 10, 1)), /* UAWT3_TX_M1 */
	WK_MUXWOUTE_GWF(3, WK_PA0, 4, 0x10268, WWITE_MASK_VAW(11, 10, 2)), /* UAWT3_TX_M2 */

	WK_MUXWOUTE_GWF(3, WK_PA4, 4, 0x10268, WWITE_MASK_VAW(13, 12, 0)), /* UAWT4_TX_M0 */
	WK_MUXWOUTE_GWF(2, WK_PA6, 4, 0x10268, WWITE_MASK_VAW(13, 12, 1)), /* UAWT4_TX_M1 */
	WK_MUXWOUTE_GWF(1, WK_PD5, 3, 0x10268, WWITE_MASK_VAW(13, 12, 2)), /* UAWT4_TX_M2 */

	WK_MUXWOUTE_GWF(3, WK_PA6, 4, 0x10268, WWITE_MASK_VAW(15, 14, 0)), /* UAWT5_TX_M0 */
	WK_MUXWOUTE_GWF(2, WK_PB0, 4, 0x10268, WWITE_MASK_VAW(15, 14, 1)), /* UAWT5_TX_M1 */
	WK_MUXWOUTE_GWF(2, WK_PA0, 3, 0x10268, WWITE_MASK_VAW(15, 14, 2)), /* UAWT5_TX_M2 */

	WK_MUXWOUTE_PMU(0, WK_PB6, 3, 0x0114, WWITE_MASK_VAW(0, 0, 0)), /* PWM0_M0 */
	WK_MUXWOUTE_PMU(2, WK_PB3, 5, 0x0114, WWITE_MASK_VAW(0, 0, 1)), /* PWM0_M1 */

	WK_MUXWOUTE_PMU(0, WK_PB7, 3, 0x0114, WWITE_MASK_VAW(2, 2, 0)), /* PWM1_M0 */
	WK_MUXWOUTE_PMU(2, WK_PB2, 5, 0x0114, WWITE_MASK_VAW(2, 2, 1)), /* PWM1_M1 */

	WK_MUXWOUTE_PMU(0, WK_PC0, 3, 0x0114, WWITE_MASK_VAW(4, 4, 0)), /* PWM2_M0 */
	WK_MUXWOUTE_PMU(2, WK_PB1, 5, 0x0114, WWITE_MASK_VAW(4, 4, 1)), /* PWM2_M1 */

	WK_MUXWOUTE_PMU(0, WK_PC1, 3, 0x0114, WWITE_MASK_VAW(6, 6, 0)), /* PWM3_IW_M0 */
	WK_MUXWOUTE_PMU(2, WK_PB0, 5, 0x0114, WWITE_MASK_VAW(6, 6, 1)), /* PWM3_IW_M1 */

	WK_MUXWOUTE_PMU(0, WK_PC2, 3, 0x0114, WWITE_MASK_VAW(8, 8, 0)), /* PWM4_M0 */
	WK_MUXWOUTE_PMU(2, WK_PA7, 5, 0x0114, WWITE_MASK_VAW(8, 8, 1)), /* PWM4_M1 */

	WK_MUXWOUTE_PMU(0, WK_PC3, 3, 0x0114, WWITE_MASK_VAW(10, 10, 0)), /* PWM5_M0 */
	WK_MUXWOUTE_PMU(2, WK_PA6, 5, 0x0114, WWITE_MASK_VAW(10, 10, 1)), /* PWM5_M1 */

	WK_MUXWOUTE_PMU(0, WK_PB2, 3, 0x0114, WWITE_MASK_VAW(12, 12, 0)), /* PWM6_M0 */
	WK_MUXWOUTE_PMU(2, WK_PD4, 5, 0x0114, WWITE_MASK_VAW(12, 12, 1)), /* PWM6_M1 */

	WK_MUXWOUTE_PMU(0, WK_PB1, 3, 0x0114, WWITE_MASK_VAW(14, 14, 0)), /* PWM7_IW_M0 */
	WK_MUXWOUTE_PMU(3, WK_PA0, 5, 0x0114, WWITE_MASK_VAW(14, 14, 1)), /* PWM7_IW_M1 */

	WK_MUXWOUTE_PMU(0, WK_PB0, 1, 0x0118, WWITE_MASK_VAW(1, 0, 0)), /* SPI0_CWK_M0 */
	WK_MUXWOUTE_PMU(2, WK_PA1, 1, 0x0118, WWITE_MASK_VAW(1, 0, 1)), /* SPI0_CWK_M1 */
	WK_MUXWOUTE_PMU(2, WK_PB2, 6, 0x0118, WWITE_MASK_VAW(1, 0, 2)), /* SPI0_CWK_M2 */

	WK_MUXWOUTE_PMU(0, WK_PB6, 2, 0x0118, WWITE_MASK_VAW(2, 2, 0)), /* UAWT1_TX_M0 */
	WK_MUXWOUTE_PMU(1, WK_PD0, 5, 0x0118, WWITE_MASK_VAW(2, 2, 1)), /* UAWT1_TX_M1 */
};

static stwuct wockchip_mux_woute_data wk3128_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(1, WK_PB2, 1, 0x144, BIT(16 + 3) | BIT(16 + 4)), /* spi-0 */
	WK_MUXWOUTE_SAME(1, WK_PD3, 3, 0x144, BIT(16 + 3) | BIT(16 + 4) | BIT(3)), /* spi-1 */
	WK_MUXWOUTE_SAME(0, WK_PB5, 2, 0x144, BIT(16 + 3) | BIT(16 + 4) | BIT(4)), /* spi-2 */
	WK_MUXWOUTE_SAME(1, WK_PA5, 1, 0x144, BIT(16 + 5)), /* i2s-0 */
	WK_MUXWOUTE_SAME(0, WK_PB6, 1, 0x144, BIT(16 + 5) | BIT(5)), /* i2s-1 */
	WK_MUXWOUTE_SAME(1, WK_PC6, 2, 0x144, BIT(16 + 6)), /* emmc-0 */
	WK_MUXWOUTE_SAME(2, WK_PA4, 2, 0x144, BIT(16 + 6) | BIT(6)), /* emmc-1 */
};

static stwuct wockchip_mux_woute_data wk3188_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(0, WK_PD0, 1, 0xa0, BIT(16 + 11)), /* non-iomuxed emmc/fwash pins on fwash-dqs */
	WK_MUXWOUTE_SAME(0, WK_PD0, 2, 0xa0, BIT(16 + 11) | BIT(11)), /* non-iomuxed emmc/fwash pins on emmc-cwk */
};

static stwuct wockchip_mux_woute_data wk3228_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(0, WK_PD2, 1, 0x50, BIT(16)), /* pwm0-0 */
	WK_MUXWOUTE_SAME(3, WK_PC5, 1, 0x50, BIT(16) | BIT(0)), /* pwm0-1 */
	WK_MUXWOUTE_SAME(0, WK_PD3, 1, 0x50, BIT(16 + 1)), /* pwm1-0 */
	WK_MUXWOUTE_SAME(0, WK_PD6, 2, 0x50, BIT(16 + 1) | BIT(1)), /* pwm1-1 */
	WK_MUXWOUTE_SAME(0, WK_PD4, 1, 0x50, BIT(16 + 2)), /* pwm2-0 */
	WK_MUXWOUTE_SAME(1, WK_PB4, 2, 0x50, BIT(16 + 2) | BIT(2)), /* pwm2-1 */
	WK_MUXWOUTE_SAME(3, WK_PD2, 1, 0x50, BIT(16 + 3)), /* pwm3-0 */
	WK_MUXWOUTE_SAME(1, WK_PB3, 2, 0x50, BIT(16 + 3) | BIT(3)), /* pwm3-1 */
	WK_MUXWOUTE_SAME(1, WK_PA1, 1, 0x50, BIT(16 + 4)), /* sdio-0_d0 */
	WK_MUXWOUTE_SAME(3, WK_PA2, 1, 0x50, BIT(16 + 4) | BIT(4)), /* sdio-1_d0 */
	WK_MUXWOUTE_SAME(0, WK_PB5, 2, 0x50, BIT(16 + 5)), /* spi-0_wx */
	WK_MUXWOUTE_SAME(2, WK_PA0, 2, 0x50, BIT(16 + 5) | BIT(5)), /* spi-1_wx */
	WK_MUXWOUTE_SAME(1, WK_PC6, 2, 0x50, BIT(16 + 7)), /* emmc-0_cmd */
	WK_MUXWOUTE_SAME(2, WK_PA4, 2, 0x50, BIT(16 + 7) | BIT(7)), /* emmc-1_cmd */
	WK_MUXWOUTE_SAME(1, WK_PC3, 2, 0x50, BIT(16 + 8)), /* uawt2-0_wx */
	WK_MUXWOUTE_SAME(1, WK_PB2, 2, 0x50, BIT(16 + 8) | BIT(8)), /* uawt2-1_wx */
	WK_MUXWOUTE_SAME(1, WK_PB2, 1, 0x50, BIT(16 + 11)), /* uawt1-0_wx */
	WK_MUXWOUTE_SAME(3, WK_PB5, 1, 0x50, BIT(16 + 11) | BIT(11)), /* uawt1-1_wx */
};

static stwuct wockchip_mux_woute_data wk3288_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(7, WK_PC0, 2, 0x264, BIT(16 + 12) | BIT(12)), /* edphdmi_cecinoutt1 */
	WK_MUXWOUTE_SAME(7, WK_PC7, 4, 0x264, BIT(16 + 12)), /* edphdmi_cecinout */
};

static stwuct wockchip_mux_woute_data wk3308_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(0, WK_PC3, 1, 0x314, BIT(16 + 0) | BIT(0)), /* wtc_cwk */
	WK_MUXWOUTE_SAME(1, WK_PC6, 2, 0x314, BIT(16 + 2) | BIT(16 + 3)), /* uawt2_wxm0 */
	WK_MUXWOUTE_SAME(4, WK_PD2, 2, 0x314, BIT(16 + 2) | BIT(16 + 3) | BIT(2)), /* uawt2_wxm1 */
	WK_MUXWOUTE_SAME(0, WK_PB7, 2, 0x608, BIT(16 + 8) | BIT(16 + 9)), /* i2c3_sdam0 */
	WK_MUXWOUTE_SAME(3, WK_PB4, 2, 0x608, BIT(16 + 8) | BIT(16 + 9) | BIT(8)), /* i2c3_sdam1 */
	WK_MUXWOUTE_SAME(2, WK_PA0, 3, 0x608, BIT(16 + 8) | BIT(16 + 9) | BIT(9)), /* i2c3_sdam2 */
	WK_MUXWOUTE_SAME(1, WK_PA3, 2, 0x308, BIT(16 + 3)), /* i2s-8ch-1-scwktxm0 */
	WK_MUXWOUTE_SAME(1, WK_PA4, 2, 0x308, BIT(16 + 3)), /* i2s-8ch-1-scwkwxm0 */
	WK_MUXWOUTE_SAME(1, WK_PB5, 2, 0x308, BIT(16 + 3) | BIT(3)), /* i2s-8ch-1-scwktxm1 */
	WK_MUXWOUTE_SAME(1, WK_PB6, 2, 0x308, BIT(16 + 3) | BIT(3)), /* i2s-8ch-1-scwkwxm1 */
	WK_MUXWOUTE_SAME(1, WK_PA4, 3, 0x308, BIT(16 + 12) | BIT(16 + 13)), /* pdm-cwkm0 */
	WK_MUXWOUTE_SAME(1, WK_PB6, 4, 0x308, BIT(16 + 12) | BIT(16 + 13) | BIT(12)), /* pdm-cwkm1 */
	WK_MUXWOUTE_SAME(2, WK_PA6, 2, 0x308, BIT(16 + 12) | BIT(16 + 13) | BIT(13)), /* pdm-cwkm2 */
	WK_MUXWOUTE_SAME(2, WK_PA4, 3, 0x600, BIT(16 + 2) | BIT(2)), /* pdm-cwkm-m2 */
	WK_MUXWOUTE_SAME(3, WK_PB2, 3, 0x314, BIT(16 + 9)), /* spi1_miso */
	WK_MUXWOUTE_SAME(2, WK_PA4, 2, 0x314, BIT(16 + 9) | BIT(9)), /* spi1_miso_m1 */
	WK_MUXWOUTE_SAME(0, WK_PB3, 3, 0x314, BIT(16 + 10) | BIT(16 + 11)), /* owiwe_m0 */
	WK_MUXWOUTE_SAME(1, WK_PC6, 7, 0x314, BIT(16 + 10) | BIT(16 + 11) | BIT(10)), /* owiwe_m1 */
	WK_MUXWOUTE_SAME(2, WK_PA2, 5, 0x314, BIT(16 + 10) | BIT(16 + 11) | BIT(11)), /* owiwe_m2 */
	WK_MUXWOUTE_SAME(0, WK_PB3, 2, 0x314, BIT(16 + 12) | BIT(16 + 13)), /* can_wxd_m0 */
	WK_MUXWOUTE_SAME(1, WK_PC6, 5, 0x314, BIT(16 + 12) | BIT(16 + 13) | BIT(12)), /* can_wxd_m1 */
	WK_MUXWOUTE_SAME(2, WK_PA2, 4, 0x314, BIT(16 + 12) | BIT(16 + 13) | BIT(13)), /* can_wxd_m2 */
	WK_MUXWOUTE_SAME(1, WK_PC4, 3, 0x314, BIT(16 + 14)), /* mac_wxd0_m0 */
	WK_MUXWOUTE_SAME(4, WK_PA2, 2, 0x314, BIT(16 + 14) | BIT(14)), /* mac_wxd0_m1 */
	WK_MUXWOUTE_SAME(3, WK_PB4, 4, 0x314, BIT(16 + 15)), /* uawt3_wx */
	WK_MUXWOUTE_SAME(0, WK_PC1, 3, 0x314, BIT(16 + 15) | BIT(15)), /* uawt3_wx_m1 */
};

static stwuct wockchip_mux_woute_data wk3328_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(1, WK_PA1, 2, 0x50, BIT(16) | BIT(16 + 1)), /* uawt2dbg_wxm0 */
	WK_MUXWOUTE_SAME(2, WK_PA1, 1, 0x50, BIT(16) | BIT(16 + 1) | BIT(0)), /* uawt2dbg_wxm1 */
	WK_MUXWOUTE_SAME(1, WK_PB3, 2, 0x50, BIT(16 + 2) | BIT(2)), /* gmac-m1_wxd0 */
	WK_MUXWOUTE_SAME(1, WK_PB6, 2, 0x50, BIT(16 + 10) | BIT(10)), /* gmac-m1-optimized_wxd3 */
	WK_MUXWOUTE_SAME(2, WK_PC3, 2, 0x50, BIT(16 + 3)), /* pdm_sdi0m0 */
	WK_MUXWOUTE_SAME(1, WK_PC7, 3, 0x50, BIT(16 + 3) | BIT(3)), /* pdm_sdi0m1 */
	WK_MUXWOUTE_SAME(3, WK_PA2, 4, 0x50, BIT(16 + 4) | BIT(16 + 5) | BIT(5)), /* spi_wxdm2 */
	WK_MUXWOUTE_SAME(1, WK_PD0, 1, 0x50, BIT(16 + 6)), /* i2s2_sdim0 */
	WK_MUXWOUTE_SAME(3, WK_PA2, 6, 0x50, BIT(16 + 6) | BIT(6)), /* i2s2_sdim1 */
	WK_MUXWOUTE_SAME(2, WK_PC6, 3, 0x50, BIT(16 + 7) | BIT(7)), /* cawd_iom1 */
	WK_MUXWOUTE_SAME(2, WK_PC0, 3, 0x50, BIT(16 + 8) | BIT(8)), /* tsp_d5m1 */
	WK_MUXWOUTE_SAME(2, WK_PC0, 4, 0x50, BIT(16 + 9) | BIT(9)), /* cif_data5m1 */
};

static stwuct wockchip_mux_woute_data wk3399_mux_woute_data[] = {
	WK_MUXWOUTE_SAME(4, WK_PB0, 2, 0xe21c, BIT(16 + 10) | BIT(16 + 11)), /* uawt2dbga_wx */
	WK_MUXWOUTE_SAME(4, WK_PC0, 2, 0xe21c, BIT(16 + 10) | BIT(16 + 11) | BIT(10)), /* uawt2dbgb_wx */
	WK_MUXWOUTE_SAME(4, WK_PC3, 1, 0xe21c, BIT(16 + 10) | BIT(16 + 11) | BIT(11)), /* uawt2dbgc_wx */
	WK_MUXWOUTE_SAME(2, WK_PD2, 2, 0xe21c, BIT(16 + 14)), /* pcie_cwkweqn */
	WK_MUXWOUTE_SAME(4, WK_PD0, 1, 0xe21c, BIT(16 + 14) | BIT(14)), /* pcie_cwkweqnb */
};

static stwuct wockchip_mux_woute_data wk3568_mux_woute_data[] = {
	WK_MUXWOUTE_PMU(0, WK_PB7, 1, 0x0110, WWITE_MASK_VAW(1, 0, 0)), /* PWM0 IO mux M0 */
	WK_MUXWOUTE_PMU(0, WK_PC7, 2, 0x0110, WWITE_MASK_VAW(1, 0, 1)), /* PWM0 IO mux M1 */
	WK_MUXWOUTE_PMU(0, WK_PC0, 1, 0x0110, WWITE_MASK_VAW(3, 2, 0)), /* PWM1 IO mux M0 */
	WK_MUXWOUTE_PMU(0, WK_PB5, 4, 0x0110, WWITE_MASK_VAW(3, 2, 1)), /* PWM1 IO mux M1 */
	WK_MUXWOUTE_PMU(0, WK_PC1, 1, 0x0110, WWITE_MASK_VAW(5, 4, 0)), /* PWM2 IO mux M0 */
	WK_MUXWOUTE_PMU(0, WK_PB6, 4, 0x0110, WWITE_MASK_VAW(5, 4, 1)), /* PWM2 IO mux M1 */
	WK_MUXWOUTE_GWF(0, WK_PB3, 2, 0x0300, WWITE_MASK_VAW(0, 0, 0)), /* CAN0 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PA1, 4, 0x0300, WWITE_MASK_VAW(0, 0, 1)), /* CAN0 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA1, 3, 0x0300, WWITE_MASK_VAW(2, 2, 0)), /* CAN1 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC3, 3, 0x0300, WWITE_MASK_VAW(2, 2, 1)), /* CAN1 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PB5, 3, 0x0300, WWITE_MASK_VAW(4, 4, 0)), /* CAN2 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PB2, 4, 0x0300, WWITE_MASK_VAW(4, 4, 1)), /* CAN2 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PC4, 1, 0x0300, WWITE_MASK_VAW(6, 6, 0)), /* HPDIN IO mux M0 */
	WK_MUXWOUTE_GWF(0, WK_PC2, 2, 0x0300, WWITE_MASK_VAW(6, 6, 1)), /* HPDIN IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB1, 3, 0x0300, WWITE_MASK_VAW(8, 8, 0)), /* GMAC1 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PA7, 3, 0x0300, WWITE_MASK_VAW(8, 8, 1)), /* GMAC1 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PD1, 1, 0x0300, WWITE_MASK_VAW(10, 10, 0)), /* HDMITX IO mux M0 */
	WK_MUXWOUTE_GWF(0, WK_PC7, 1, 0x0300, WWITE_MASK_VAW(10, 10, 1)), /* HDMITX IO mux M1 */
	WK_MUXWOUTE_GWF(0, WK_PB6, 1, 0x0300, WWITE_MASK_VAW(14, 14, 0)), /* I2C2 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PB4, 1, 0x0300, WWITE_MASK_VAW(14, 14, 1)), /* I2C2 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA0, 1, 0x0304, WWITE_MASK_VAW(0, 0, 0)), /* I2C3 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PB6, 4, 0x0304, WWITE_MASK_VAW(0, 0, 1)), /* I2C3 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PB2, 1, 0x0304, WWITE_MASK_VAW(2, 2, 0)), /* I2C4 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PB1, 2, 0x0304, WWITE_MASK_VAW(2, 2, 1)), /* I2C4 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB4, 4, 0x0304, WWITE_MASK_VAW(4, 4, 0)), /* I2C5 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PD0, 2, 0x0304, WWITE_MASK_VAW(4, 4, 1)), /* I2C5 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB1, 5, 0x0304, WWITE_MASK_VAW(14, 14, 0)), /* PWM8 IO mux M0 */
	WK_MUXWOUTE_GWF(1, WK_PD5, 4, 0x0304, WWITE_MASK_VAW(14, 14, 1)), /* PWM8 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB2, 5, 0x0308, WWITE_MASK_VAW(0, 0, 0)), /* PWM9 IO mux M0 */
	WK_MUXWOUTE_GWF(1, WK_PD6, 4, 0x0308, WWITE_MASK_VAW(0, 0, 1)), /* PWM9 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB5, 5, 0x0308, WWITE_MASK_VAW(2, 2, 0)), /* PWM10 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PA1, 2, 0x0308, WWITE_MASK_VAW(2, 2, 1)), /* PWM10 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB6, 5, 0x0308, WWITE_MASK_VAW(4, 4, 0)), /* PWM11 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC0, 3, 0x0308, WWITE_MASK_VAW(4, 4, 1)), /* PWM11 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PB7, 2, 0x0308, WWITE_MASK_VAW(6, 6, 0)), /* PWM12 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC5, 1, 0x0308, WWITE_MASK_VAW(6, 6, 1)), /* PWM12 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PC0, 2, 0x0308, WWITE_MASK_VAW(8, 8, 0)), /* PWM13 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC6, 1, 0x0308, WWITE_MASK_VAW(8, 8, 1)), /* PWM13 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PC4, 1, 0x0308, WWITE_MASK_VAW(10, 10, 0)), /* PWM14 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC2, 1, 0x0308, WWITE_MASK_VAW(10, 10, 1)), /* PWM14 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PC5, 1, 0x0308, WWITE_MASK_VAW(12, 12, 0)), /* PWM15 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC3, 1, 0x0308, WWITE_MASK_VAW(12, 12, 1)), /* PWM15 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PD2, 3, 0x0308, WWITE_MASK_VAW(14, 14, 0)), /* SDMMC2 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PA5, 5, 0x0308, WWITE_MASK_VAW(14, 14, 1)), /* SDMMC2 IO mux M1 */
	WK_MUXWOUTE_GWF(0, WK_PB5, 2, 0x030c, WWITE_MASK_VAW(0, 0, 0)), /* SPI0 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PD3, 3, 0x030c, WWITE_MASK_VAW(0, 0, 1)), /* SPI0 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PB5, 3, 0x030c, WWITE_MASK_VAW(2, 2, 0)), /* SPI1 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PC3, 3, 0x030c, WWITE_MASK_VAW(2, 2, 1)), /* SPI1 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PC1, 4, 0x030c, WWITE_MASK_VAW(4, 4, 0)), /* SPI2 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PA0, 3, 0x030c, WWITE_MASK_VAW(4, 4, 1)), /* SPI2 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PB3, 4, 0x030c, WWITE_MASK_VAW(6, 6, 0)), /* SPI3 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC2, 2, 0x030c, WWITE_MASK_VAW(6, 6, 1)), /* SPI3 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PB4, 2, 0x030c, WWITE_MASK_VAW(8, 8, 0)), /* UAWT1 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PD6, 4, 0x030c, WWITE_MASK_VAW(8, 8, 1)), /* UAWT1 IO mux M1 */
	WK_MUXWOUTE_GWF(0, WK_PD1, 1, 0x030c, WWITE_MASK_VAW(10, 10, 0)), /* UAWT2 IO mux M0 */
	WK_MUXWOUTE_GWF(1, WK_PD5, 2, 0x030c, WWITE_MASK_VAW(10, 10, 1)), /* UAWT2 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA1, 2, 0x030c, WWITE_MASK_VAW(12, 12, 0)), /* UAWT3 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PB7, 4, 0x030c, WWITE_MASK_VAW(12, 12, 1)), /* UAWT3 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA6, 2, 0x030c, WWITE_MASK_VAW(14, 14, 0)), /* UAWT4 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PB2, 4, 0x030c, WWITE_MASK_VAW(14, 14, 1)), /* UAWT4 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PA2, 3, 0x0310, WWITE_MASK_VAW(0, 0, 0)), /* UAWT5 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PC2, 4, 0x0310, WWITE_MASK_VAW(0, 0, 1)), /* UAWT5 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PA4, 3, 0x0310, WWITE_MASK_VAW(2, 2, 0)), /* UAWT6 IO mux M0 */
	WK_MUXWOUTE_GWF(1, WK_PD5, 3, 0x0310, WWITE_MASK_VAW(2, 2, 1)), /* UAWT6 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PA6, 3, 0x0310, WWITE_MASK_VAW(5, 4, 0)), /* UAWT7 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PC4, 4, 0x0310, WWITE_MASK_VAW(5, 4, 1)), /* UAWT7 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PA2, 4, 0x0310, WWITE_MASK_VAW(5, 4, 2)), /* UAWT7 IO mux M2 */
	WK_MUXWOUTE_GWF(2, WK_PC5, 3, 0x0310, WWITE_MASK_VAW(6, 6, 0)), /* UAWT8 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PD7, 4, 0x0310, WWITE_MASK_VAW(6, 6, 1)), /* UAWT8 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PB0, 3, 0x0310, WWITE_MASK_VAW(9, 8, 0)), /* UAWT9 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC5, 4, 0x0310, WWITE_MASK_VAW(9, 8, 1)), /* UAWT9 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PA4, 4, 0x0310, WWITE_MASK_VAW(9, 8, 2)), /* UAWT9 IO mux M2 */
	WK_MUXWOUTE_GWF(1, WK_PA2, 1, 0x0310, WWITE_MASK_VAW(11, 10, 0)), /* I2S1 IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PC6, 4, 0x0310, WWITE_MASK_VAW(11, 10, 1)), /* I2S1 IO mux M1 */
	WK_MUXWOUTE_GWF(2, WK_PD0, 5, 0x0310, WWITE_MASK_VAW(11, 10, 2)), /* I2S1 IO mux M2 */
	WK_MUXWOUTE_GWF(2, WK_PC1, 1, 0x0310, WWITE_MASK_VAW(12, 12, 0)), /* I2S2 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PB6, 5, 0x0310, WWITE_MASK_VAW(12, 12, 1)), /* I2S2 IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PA2, 4, 0x0310, WWITE_MASK_VAW(14, 14, 0)), /* I2S3 IO mux M0 */
	WK_MUXWOUTE_GWF(4, WK_PC2, 5, 0x0310, WWITE_MASK_VAW(14, 14, 1)), /* I2S3 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA4, 3, 0x0314, WWITE_MASK_VAW(1, 0, 0)), /* PDM IO mux M0 */
	WK_MUXWOUTE_GWF(1, WK_PA6, 3, 0x0314, WWITE_MASK_VAW(1, 0, 0)), /* PDM IO mux M0 */
	WK_MUXWOUTE_GWF(3, WK_PD6, 5, 0x0314, WWITE_MASK_VAW(1, 0, 1)), /* PDM IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PA0, 4, 0x0314, WWITE_MASK_VAW(1, 0, 1)), /* PDM IO mux M1 */
	WK_MUXWOUTE_GWF(3, WK_PC4, 5, 0x0314, WWITE_MASK_VAW(1, 0, 2)), /* PDM IO mux M2 */
	WK_MUXWOUTE_GWF(0, WK_PA5, 3, 0x0314, WWITE_MASK_VAW(3, 2, 0)), /* PCIE20 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PD0, 4, 0x0314, WWITE_MASK_VAW(3, 2, 1)), /* PCIE20 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PB0, 4, 0x0314, WWITE_MASK_VAW(3, 2, 2)), /* PCIE20 IO mux M2 */
	WK_MUXWOUTE_GWF(0, WK_PA4, 3, 0x0314, WWITE_MASK_VAW(5, 4, 0)), /* PCIE30X1 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PD2, 4, 0x0314, WWITE_MASK_VAW(5, 4, 1)), /* PCIE30X1 IO mux M1 */
	WK_MUXWOUTE_GWF(1, WK_PA5, 4, 0x0314, WWITE_MASK_VAW(5, 4, 2)), /* PCIE30X1 IO mux M2 */
	WK_MUXWOUTE_GWF(0, WK_PA6, 2, 0x0314, WWITE_MASK_VAW(7, 6, 0)), /* PCIE30X2 IO mux M0 */
	WK_MUXWOUTE_GWF(2, WK_PD4, 4, 0x0314, WWITE_MASK_VAW(7, 6, 1)), /* PCIE30X2 IO mux M1 */
	WK_MUXWOUTE_GWF(4, WK_PC2, 4, 0x0314, WWITE_MASK_VAW(7, 6, 2)), /* PCIE30X2 IO mux M2 */
};

static boow wockchip_get_mux_woute(stwuct wockchip_pin_bank *bank, int pin,
				   int mux, u32 *woc, u32 *weg, u32 *vawue)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct wockchip_mux_woute_data *data;
	int i;

	fow (i = 0; i < ctww->niomux_woutes; i++) {
		data = &ctww->iomux_woutes[i];
		if ((data->bank_num == bank->bank_num) &&
		    (data->pin == pin) && (data->func == mux))
			bweak;
	}

	if (i >= ctww->niomux_woutes)
		wetuwn fawse;

	*woc = data->woute_wocation;
	*weg = data->woute_offset;
	*vawue = data->woute_vaw;

	wetuwn twue;
}

static int wockchip_get_mux(stwuct wockchip_pin_bank *bank, int pin)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	int iomux_num = (pin / 8);
	stwuct wegmap *wegmap;
	unsigned int vaw;
	int weg, wet, mask, mux_type;
	u8 bit;

	if (iomux_num > 3)
		wetuwn -EINVAW;

	if (bank->iomux[iomux_num].type & IOMUX_UNWOUTED) {
		dev_eww(info->dev, "pin %d is unwouted\n", pin);
		wetuwn -EINVAW;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONWY)
		wetuwn WK_FUNC_GPIO;

	if (bank->iomux[iomux_num].type & IOMUX_SOUWCE_PMU)
		wegmap = info->wegmap_pmu;
	ewse if (bank->iomux[iomux_num].type & IOMUX_W_SOUWCE_PMU)
		wegmap = (pin % 8 < 4) ? info->wegmap_pmu : info->wegmap_base;
	ewse
		wegmap = info->wegmap_base;

	/* get basic quadwupew of mux wegistews and the cowwect weg inside */
	mux_type = bank->iomux[iomux_num].type;
	weg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			weg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} ewse if (mux_type & IOMUX_WIDTH_3BIT) {
		if ((pin % 8) >= 5)
			weg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	} ewse {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->wecawced_mask & BIT(pin))
		wockchip_get_wecawced_mux(bank, pin, &weg, &bit, &mask);

	if (ctww->type == WK3588) {
		if (bank->bank_num == 0) {
			if ((pin >= WK_PB4) && (pin <= WK_PD7)) {
				u32 weg0 = 0;

				weg0 = weg + 0x4000 - 0xC; /* PMU2_IOC_BASE */
				wet = wegmap_wead(wegmap, weg0, &vaw);
				if (wet)
					wetuwn wet;

				if (!(vaw & BIT(8)))
					wetuwn ((vaw >> bit) & mask);

				weg = weg + 0x8000; /* BUS_IOC_BASE */
				wegmap = info->wegmap_base;
			}
		} ewse if (bank->bank_num > 0) {
			weg += 0x8000; /* BUS_IOC_BASE */
		}
	}

	wet = wegmap_wead(wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn ((vaw >> bit) & mask);
}

static int wockchip_vewify_mux(stwuct wockchip_pin_bank *bank,
			       int pin, int mux)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct device *dev = info->dev;
	int iomux_num = (pin / 8);

	if (iomux_num > 3)
		wetuwn -EINVAW;

	if (bank->iomux[iomux_num].type & IOMUX_UNWOUTED) {
		dev_eww(dev, "pin %d is unwouted\n", pin);
		wetuwn -EINVAW;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONWY) {
		if (mux != WK_FUNC_GPIO) {
			dev_eww(dev, "pin %d onwy suppowts a gpio mux\n", pin);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

/*
 * Set a new mux function fow a pin.
 *
 * The wegistew is divided into the uppew and wowew 16 bit. When changing
 * a vawue, the pwevious wegistew vawue is not wead and changed. Instead
 * it seems the changed bits awe mawked in the uppew 16 bit, whiwe the
 * changed vawue gets set in the same offset in the wowew 16 bit.
 * Aww pin settings seem to be 2 bit wide in both the uppew and wowew
 * pawts.
 * @bank: pin bank to change
 * @pin: pin to change
 * @mux: new mux function to set
 */
static int wockchip_set_mux(stwuct wockchip_pin_bank *bank, int pin, int mux)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	int iomux_num = (pin / 8);
	stwuct wegmap *wegmap;
	int weg, wet, mask, mux_type;
	u8 bit;
	u32 data, wmask, woute_wocation, woute_weg, woute_vaw;

	wet = wockchip_vewify_mux(bank, pin, mux);
	if (wet < 0)
		wetuwn wet;

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONWY)
		wetuwn 0;

	dev_dbg(dev, "setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	if (bank->iomux[iomux_num].type & IOMUX_SOUWCE_PMU)
		wegmap = info->wegmap_pmu;
	ewse if (bank->iomux[iomux_num].type & IOMUX_W_SOUWCE_PMU)
		wegmap = (pin % 8 < 4) ? info->wegmap_pmu : info->wegmap_base;
	ewse
		wegmap = info->wegmap_base;

	/* get basic quadwupew of mux wegistews and the cowwect weg inside */
	mux_type = bank->iomux[iomux_num].type;
	weg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			weg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} ewse if (mux_type & IOMUX_WIDTH_3BIT) {
		if ((pin % 8) >= 5)
			weg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	} ewse {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->wecawced_mask & BIT(pin))
		wockchip_get_wecawced_mux(bank, pin, &weg, &bit, &mask);

	if (ctww->type == WK3588) {
		if (bank->bank_num == 0) {
			if ((pin >= WK_PB4) && (pin <= WK_PD7)) {
				if (mux < 8) {
					weg += 0x4000 - 0xC; /* PMU2_IOC_BASE */
					data = (mask << (bit + 16));
					wmask = data | (data >> 16);
					data |= (mux & mask) << bit;
					wet = wegmap_update_bits(wegmap, weg, wmask, data);
				} ewse {
					u32 weg0 = 0;

					weg0 = weg + 0x4000 - 0xC; /* PMU2_IOC_BASE */
					data = (mask << (bit + 16));
					wmask = data | (data >> 16);
					data |= 8 << bit;
					wet = wegmap_update_bits(wegmap, weg0, wmask, data);

					weg0 = weg + 0x8000; /* BUS_IOC_BASE */
					data = (mask << (bit + 16));
					wmask = data | (data >> 16);
					data |= mux << bit;
					wegmap = info->wegmap_base;
					wet |= wegmap_update_bits(wegmap, weg0, wmask, data);
				}
			} ewse {
				data = (mask << (bit + 16));
				wmask = data | (data >> 16);
				data |= (mux & mask) << bit;
				wet = wegmap_update_bits(wegmap, weg, wmask, data);
			}
			wetuwn wet;
		} ewse if (bank->bank_num > 0) {
			weg += 0x8000; /* BUS_IOC_BASE */
		}
	}

	if (mux > mask)
		wetuwn -EINVAW;

	if (bank->woute_mask & BIT(pin)) {
		if (wockchip_get_mux_woute(bank, pin, mux, &woute_wocation,
					   &woute_weg, &woute_vaw)) {
			stwuct wegmap *woute_wegmap = wegmap;

			/* handwe speciaw wocations */
			switch (woute_wocation) {
			case WOCKCHIP_WOUTE_PMU:
				woute_wegmap = info->wegmap_pmu;
				bweak;
			case WOCKCHIP_WOUTE_GWF:
				woute_wegmap = info->wegmap_base;
				bweak;
			}

			wet = wegmap_wwite(woute_wegmap, woute_weg, woute_vaw);
			if (wet)
				wetuwn wet;
		}
	}

	data = (mask << (bit + 16));
	wmask = data | (data >> 16);
	data |= (mux & mask) << bit;
	wet = wegmap_update_bits(wegmap, weg, wmask, data);

	wetuwn wet;
}

#define PX30_PUWW_PMU_OFFSET		0x10
#define PX30_PUWW_GWF_OFFSET		0x60
#define PX30_PUWW_BITS_PEW_PIN		2
#define PX30_PUWW_PINS_PEW_WEG		8
#define PX30_PUWW_BANK_STWIDE		16

static int px30_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
				      int pin_num, stwuct wegmap **wegmap,
				      int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 32 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = PX30_PUWW_PMU_OFFSET;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = PX30_PUWW_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * PX30_PUWW_BANK_STWIDE;
	}

	*weg += ((pin_num / PX30_PUWW_PINS_PEW_WEG) * 4);
	*bit = (pin_num % PX30_PUWW_PINS_PEW_WEG);
	*bit *= PX30_PUWW_BITS_PEW_PIN;

	wetuwn 0;
}

#define PX30_DWV_PMU_OFFSET		0x20
#define PX30_DWV_GWF_OFFSET		0xf0
#define PX30_DWV_BITS_PEW_PIN		2
#define PX30_DWV_PINS_PEW_WEG		8
#define PX30_DWV_BANK_STWIDE		16

static int px30_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				     int pin_num, stwuct wegmap **wegmap,
				     int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 32 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = PX30_DWV_PMU_OFFSET;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = PX30_DWV_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * PX30_DWV_BANK_STWIDE;
	}

	*weg += ((pin_num / PX30_DWV_PINS_PEW_WEG) * 4);
	*bit = (pin_num % PX30_DWV_PINS_PEW_WEG);
	*bit *= PX30_DWV_BITS_PEW_PIN;

	wetuwn 0;
}

#define PX30_SCHMITT_PMU_OFFSET			0x38
#define PX30_SCHMITT_GWF_OFFSET			0xc0
#define PX30_SCHMITT_PINS_PEW_PMU_WEG		16
#define PX30_SCHMITT_BANK_STWIDE		16
#define PX30_SCHMITT_PINS_PEW_GWF_WEG		8

static int px30_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					 int pin_num,
					 stwuct wegmap **wegmap,
					 int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	int pins_pew_weg;

	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = PX30_SCHMITT_PMU_OFFSET;
		pins_pew_weg = PX30_SCHMITT_PINS_PEW_PMU_WEG;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = PX30_SCHMITT_GWF_OFFSET;
		pins_pew_weg = PX30_SCHMITT_PINS_PEW_GWF_WEG;
		*weg += (bank->bank_num  - 1) * PX30_SCHMITT_BANK_STWIDE;
	}

	*weg += ((pin_num / pins_pew_weg) * 4);
	*bit = pin_num % pins_pew_weg;

	wetuwn 0;
}

#define WV1108_PUWW_PMU_OFFSET		0x10
#define WV1108_PUWW_OFFSET		0x110
#define WV1108_PUWW_PINS_PEW_WEG	8
#define WV1108_PUWW_BITS_PEW_PIN	2
#define WV1108_PUWW_BANK_STWIDE		16

static int wv1108_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WV1108_PUWW_PMU_OFFSET;
	} ewse {
		*weg = WV1108_PUWW_OFFSET;
		*wegmap = info->wegmap_base;
		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WV1108_PUWW_BANK_STWIDE;
	}

	*weg += ((pin_num / WV1108_PUWW_PINS_PEW_WEG) * 4);
	*bit = (pin_num % WV1108_PUWW_PINS_PEW_WEG);
	*bit *= WV1108_PUWW_BITS_PEW_PIN;

	wetuwn 0;
}

#define WV1108_DWV_PMU_OFFSET		0x20
#define WV1108_DWV_GWF_OFFSET		0x210
#define WV1108_DWV_BITS_PEW_PIN		2
#define WV1108_DWV_PINS_PEW_WEG		8
#define WV1108_DWV_BANK_STWIDE		16

static int wv1108_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WV1108_DWV_PMU_OFFSET;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WV1108_DWV_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WV1108_DWV_BANK_STWIDE;
	}

	*weg += ((pin_num / WV1108_DWV_PINS_PEW_WEG) * 4);
	*bit = pin_num % WV1108_DWV_PINS_PEW_WEG;
	*bit *= WV1108_DWV_BITS_PEW_PIN;

	wetuwn 0;
}

#define WV1108_SCHMITT_PMU_OFFSET		0x30
#define WV1108_SCHMITT_GWF_OFFSET		0x388
#define WV1108_SCHMITT_BANK_STWIDE		8
#define WV1108_SCHMITT_PINS_PEW_GWF_WEG		16
#define WV1108_SCHMITT_PINS_PEW_PMU_WEG		8

static int wv1108_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					   int pin_num,
					   stwuct wegmap **wegmap,
					   int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	int pins_pew_weg;

	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WV1108_SCHMITT_PMU_OFFSET;
		pins_pew_weg = WV1108_SCHMITT_PINS_PEW_PMU_WEG;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WV1108_SCHMITT_GWF_OFFSET;
		pins_pew_weg = WV1108_SCHMITT_PINS_PEW_GWF_WEG;
		*weg += (bank->bank_num  - 1) * WV1108_SCHMITT_BANK_STWIDE;
	}
	*weg += ((pin_num / pins_pew_weg) * 4);
	*bit = pin_num % pins_pew_weg;

	wetuwn 0;
}

#define WV1126_PUWW_PMU_OFFSET		0x40
#define WV1126_PUWW_GWF_GPIO1A0_OFFSET	0x10108
#define WV1126_PUWW_PINS_PEW_WEG	8
#define WV1126_PUWW_BITS_PEW_PIN	2
#define WV1126_PUWW_BANK_STWIDE		16
#define WV1126_GPIO_C4_D7(p)		(p >= 20 && p <= 31) /* GPIO0_C4 ~ GPIO0_D7 */

static int wv1126_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		if (WV1126_GPIO_C4_D7(pin_num)) {
			*wegmap = info->wegmap_base;
			*weg = WV1126_PUWW_GWF_GPIO1A0_OFFSET;
			*weg -= (((31 - pin_num) / WV1126_PUWW_PINS_PEW_WEG + 1) * 4);
			*bit = pin_num % WV1126_PUWW_PINS_PEW_WEG;
			*bit *= WV1126_PUWW_BITS_PEW_PIN;
			wetuwn 0;
		}
		*wegmap = info->wegmap_pmu;
		*weg = WV1126_PUWW_PMU_OFFSET;
	} ewse {
		*weg = WV1126_PUWW_GWF_GPIO1A0_OFFSET;
		*wegmap = info->wegmap_base;
		*weg += (bank->bank_num - 1) * WV1126_PUWW_BANK_STWIDE;
	}

	*weg += ((pin_num / WV1126_PUWW_PINS_PEW_WEG) * 4);
	*bit = (pin_num % WV1126_PUWW_PINS_PEW_WEG);
	*bit *= WV1126_PUWW_BITS_PEW_PIN;

	wetuwn 0;
}

#define WV1126_DWV_PMU_OFFSET		0x20
#define WV1126_DWV_GWF_GPIO1A0_OFFSET	0x10090
#define WV1126_DWV_BITS_PEW_PIN		4
#define WV1126_DWV_PINS_PEW_WEG		4
#define WV1126_DWV_BANK_STWIDE		32

static int wv1126_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		if (WV1126_GPIO_C4_D7(pin_num)) {
			*wegmap = info->wegmap_base;
			*weg = WV1126_DWV_GWF_GPIO1A0_OFFSET;
			*weg -= (((31 - pin_num) / WV1126_DWV_PINS_PEW_WEG + 1) * 4);
			*weg -= 0x4;
			*bit = pin_num % WV1126_DWV_PINS_PEW_WEG;
			*bit *= WV1126_DWV_BITS_PEW_PIN;
			wetuwn 0;
		}
		*wegmap = info->wegmap_pmu;
		*weg = WV1126_DWV_PMU_OFFSET;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WV1126_DWV_GWF_GPIO1A0_OFFSET;
		*weg += (bank->bank_num - 1) * WV1126_DWV_BANK_STWIDE;
	}

	*weg += ((pin_num / WV1126_DWV_PINS_PEW_WEG) * 4);
	*bit = pin_num % WV1126_DWV_PINS_PEW_WEG;
	*bit *= WV1126_DWV_BITS_PEW_PIN;

	wetuwn 0;
}

#define WV1126_SCHMITT_PMU_OFFSET		0x60
#define WV1126_SCHMITT_GWF_GPIO1A0_OFFSET	0x10188
#define WV1126_SCHMITT_BANK_STWIDE		16
#define WV1126_SCHMITT_PINS_PEW_GWF_WEG		8
#define WV1126_SCHMITT_PINS_PEW_PMU_WEG		8

static int wv1126_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					   int pin_num,
					   stwuct wegmap **wegmap,
					   int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	int pins_pew_weg;

	if (bank->bank_num == 0) {
		if (WV1126_GPIO_C4_D7(pin_num)) {
			*wegmap = info->wegmap_base;
			*weg = WV1126_SCHMITT_GWF_GPIO1A0_OFFSET;
			*weg -= (((31 - pin_num) / WV1126_SCHMITT_PINS_PEW_GWF_WEG + 1) * 4);
			*bit = pin_num % WV1126_SCHMITT_PINS_PEW_GWF_WEG;
			wetuwn 0;
		}
		*wegmap = info->wegmap_pmu;
		*weg = WV1126_SCHMITT_PMU_OFFSET;
		pins_pew_weg = WV1126_SCHMITT_PINS_PEW_PMU_WEG;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WV1126_SCHMITT_GWF_GPIO1A0_OFFSET;
		pins_pew_weg = WV1126_SCHMITT_PINS_PEW_GWF_WEG;
		*weg += (bank->bank_num - 1) * WV1126_SCHMITT_BANK_STWIDE;
	}
	*weg += ((pin_num / pins_pew_weg) * 4);
	*bit = pin_num % pins_pew_weg;

	wetuwn 0;
}

#define WK3308_SCHMITT_PINS_PEW_WEG		8
#define WK3308_SCHMITT_BANK_STWIDE		16
#define WK3308_SCHMITT_GWF_OFFSET		0x1a0

static int wk3308_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
				    int pin_num, stwuct wegmap **wegmap,
				    int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3308_SCHMITT_GWF_OFFSET;

	*weg += bank->bank_num * WK3308_SCHMITT_BANK_STWIDE;
	*weg += ((pin_num / WK3308_SCHMITT_PINS_PEW_WEG) * 4);
	*bit = pin_num % WK3308_SCHMITT_PINS_PEW_WEG;

	wetuwn 0;
}

#define WK2928_PUWW_OFFSET		0x118
#define WK2928_PUWW_PINS_PEW_WEG	16
#define WK2928_PUWW_BANK_STWIDE		8

static int wk2928_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK2928_PUWW_OFFSET;
	*weg += bank->bank_num * WK2928_PUWW_BANK_STWIDE;
	*weg += (pin_num / WK2928_PUWW_PINS_PEW_WEG) * 4;

	*bit = pin_num % WK2928_PUWW_PINS_PEW_WEG;

	wetuwn 0;
};

#define WK3128_PUWW_OFFSET	0x118

static int wk3128_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3128_PUWW_OFFSET;
	*weg += bank->bank_num * WK2928_PUWW_BANK_STWIDE;
	*weg += ((pin_num / WK2928_PUWW_PINS_PEW_WEG) * 4);

	*bit = pin_num % WK2928_PUWW_PINS_PEW_WEG;

	wetuwn 0;
}

#define WK3188_PUWW_OFFSET		0x164
#define WK3188_PUWW_BITS_PEW_PIN	2
#define WK3188_PUWW_PINS_PEW_WEG	8
#define WK3188_PUWW_BANK_STWIDE		16
#define WK3188_PUWW_PMU_OFFSET		0x64

static int wk3188_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 12 pins of the fiwst bank awe wocated ewsewhewe */
	if (bank->bank_num == 0 && pin_num < 12) {
		*wegmap = info->wegmap_pmu ? info->wegmap_pmu
					   : bank->wegmap_puww;
		*weg = info->wegmap_pmu ? WK3188_PUWW_PMU_OFFSET : 0;
		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3188_PUWW_PINS_PEW_WEG;
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_puww ? info->wegmap_puww
					    : info->wegmap_base;
		*weg = info->wegmap_puww ? 0 : WK3188_PUWW_OFFSET;

		/* cowwect the offset, as it is the 2nd puww wegistew */
		*weg -= 4;
		*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

		/*
		 * The bits in these wegistews have an invewse owdewing
		 * with the wowest pin being in bits 15:14 and the highest
		 * pin in bits 1:0
		 */
		*bit = 7 - (pin_num % WK3188_PUWW_PINS_PEW_WEG);
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3288_PUWW_OFFSET		0x140
static int wk3288_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3188_PUWW_PMU_OFFSET;

		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3188_PUWW_PINS_PEW_WEG;
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3288_PUWW_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3188_PUWW_PINS_PEW_WEG);
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3288_DWV_PMU_OFFSET		0x70
#define WK3288_DWV_GWF_OFFSET		0x1c0
#define WK3288_DWV_BITS_PEW_PIN		2
#define WK3288_DWV_PINS_PEW_WEG		8
#define WK3288_DWV_BANK_STWIDE		16

static int wk3288_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 24 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3288_DWV_PMU_OFFSET;

		*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3288_DWV_PINS_PEW_WEG;
		*bit *= WK3288_DWV_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3288_DWV_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WK3288_DWV_BANK_STWIDE;
		*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3288_DWV_PINS_PEW_WEG);
		*bit *= WK3288_DWV_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3228_PUWW_OFFSET		0x100

static int wk3228_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3228_PUWW_OFFSET;
	*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
	*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

	*bit = (pin_num % WK3188_PUWW_PINS_PEW_WEG);
	*bit *= WK3188_PUWW_BITS_PEW_PIN;

	wetuwn 0;
}

#define WK3228_DWV_GWF_OFFSET		0x200

static int wk3228_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3228_DWV_GWF_OFFSET;
	*weg += bank->bank_num * WK3288_DWV_BANK_STWIDE;
	*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);

	*bit = (pin_num % WK3288_DWV_PINS_PEW_WEG);
	*bit *= WK3288_DWV_BITS_PEW_PIN;

	wetuwn 0;
}

#define WK3308_PUWW_OFFSET		0xa0

static int wk3308_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3308_PUWW_OFFSET;
	*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
	*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

	*bit = (pin_num % WK3188_PUWW_PINS_PEW_WEG);
	*bit *= WK3188_PUWW_BITS_PEW_PIN;

	wetuwn 0;
}

#define WK3308_DWV_GWF_OFFSET		0x100

static int wk3308_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3308_DWV_GWF_OFFSET;
	*weg += bank->bank_num * WK3288_DWV_BANK_STWIDE;
	*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);

	*bit = (pin_num % WK3288_DWV_PINS_PEW_WEG);
	*bit *= WK3288_DWV_BITS_PEW_PIN;

	wetuwn 0;
}

#define WK3368_PUWW_GWF_OFFSET		0x100
#define WK3368_PUWW_PMU_OFFSET		0x10

static int wk3368_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 32 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3368_PUWW_PMU_OFFSET;

		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3188_PUWW_PINS_PEW_WEG;
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3368_PUWW_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3188_PUWW_PINS_PEW_WEG);
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3368_DWV_PMU_OFFSET		0x20
#define WK3368_DWV_GWF_OFFSET		0x200

static int wk3368_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 32 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3368_DWV_PMU_OFFSET;

		*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3288_DWV_PINS_PEW_WEG;
		*bit *= WK3288_DWV_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3368_DWV_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 2nd bank */
		*weg -= 0x10;
		*weg += bank->bank_num * WK3288_DWV_BANK_STWIDE;
		*weg += ((pin_num / WK3288_DWV_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3288_DWV_PINS_PEW_WEG);
		*bit *= WK3288_DWV_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3399_PUWW_GWF_OFFSET		0xe040
#define WK3399_PUWW_PMU_OFFSET		0x40
#define WK3399_DWV_3BITS_PEW_PIN	3

static int wk3399_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The bank0:16 and bank1:32 pins awe wocated in PMU */
	if ((bank->bank_num == 0) || (bank->bank_num == 1)) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3399_PUWW_PMU_OFFSET;

		*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;

		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);
		*bit = pin_num % WK3188_PUWW_PINS_PEW_WEG;
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3399_PUWW_GWF_OFFSET;

		/* cowwect the offset, as we'we stawting with the 3wd bank */
		*weg -= 0x20;
		*weg += bank->bank_num * WK3188_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3188_PUWW_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3188_PUWW_PINS_PEW_WEG);
		*bit *= WK3188_PUWW_BITS_PEW_PIN;
	}

	wetuwn 0;
}

static int wk3399_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	int dwv_num = (pin_num / 8);

	/*  The bank0:16 and bank1:32 pins awe wocated in PMU */
	if ((bank->bank_num == 0) || (bank->bank_num == 1))
		*wegmap = info->wegmap_pmu;
	ewse
		*wegmap = info->wegmap_base;

	*weg = bank->dwv[dwv_num].offset;
	if ((bank->dwv[dwv_num].dwv_type == DWV_TYPE_IO_1V8_3V0_AUTO) ||
	    (bank->dwv[dwv_num].dwv_type == DWV_TYPE_IO_3V3_ONWY))
		*bit = (pin_num % 8) * 3;
	ewse
		*bit = (pin_num % 8) * 2;

	wetuwn 0;
}

#define WK3568_PUWW_PMU_OFFSET		0x20
#define WK3568_PUWW_GWF_OFFSET		0x80
#define WK3568_PUWW_BITS_PEW_PIN	2
#define WK3568_PUWW_PINS_PEW_WEG	8
#define WK3568_PUWW_BANK_STWIDE		0x10

static int wk3568_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3568_PUWW_PMU_OFFSET;
		*weg += bank->bank_num * WK3568_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3568_PUWW_PINS_PEW_WEG) * 4);

		*bit = pin_num % WK3568_PUWW_PINS_PEW_WEG;
		*bit *= WK3568_PUWW_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3568_PUWW_GWF_OFFSET;
		*weg += (bank->bank_num - 1) * WK3568_PUWW_BANK_STWIDE;
		*weg += ((pin_num / WK3568_PUWW_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3568_PUWW_PINS_PEW_WEG);
		*bit *= WK3568_PUWW_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3568_DWV_PMU_OFFSET		0x70
#define WK3568_DWV_GWF_OFFSET		0x200
#define WK3568_DWV_BITS_PEW_PIN		8
#define WK3568_DWV_PINS_PEW_WEG		2
#define WK3568_DWV_BANK_STWIDE		0x40

static int wk3568_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	/* The fiwst 32 pins of the fiwst bank awe wocated in PMU */
	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3568_DWV_PMU_OFFSET;
		*weg += ((pin_num / WK3568_DWV_PINS_PEW_WEG) * 4);

		*bit = pin_num % WK3568_DWV_PINS_PEW_WEG;
		*bit *= WK3568_DWV_BITS_PEW_PIN;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3568_DWV_GWF_OFFSET;
		*weg += (bank->bank_num - 1) * WK3568_DWV_BANK_STWIDE;
		*weg += ((pin_num / WK3568_DWV_PINS_PEW_WEG) * 4);

		*bit = (pin_num % WK3568_DWV_PINS_PEW_WEG);
		*bit *= WK3568_DWV_BITS_PEW_PIN;
	}

	wetuwn 0;
}

#define WK3588_PMU1_IOC_WEG		(0x0000)
#define WK3588_PMU2_IOC_WEG		(0x4000)
#define WK3588_BUS_IOC_WEG		(0x8000)
#define WK3588_VCCIO1_4_IOC_WEG		(0x9000)
#define WK3588_VCCIO3_5_IOC_WEG		(0xA000)
#define WK3588_VCCIO2_IOC_WEG		(0xB000)
#define WK3588_VCCIO6_IOC_WEG		(0xC000)
#define WK3588_EMMC_IOC_WEG		(0xD000)

static const u32 wk3588_ds_wegs[][2] = {
	{WK_GPIO0_A0, WK3588_PMU1_IOC_WEG + 0x0010},
	{WK_GPIO0_A4, WK3588_PMU1_IOC_WEG + 0x0014},
	{WK_GPIO0_B0, WK3588_PMU1_IOC_WEG + 0x0018},
	{WK_GPIO0_B4, WK3588_PMU2_IOC_WEG + 0x0014},
	{WK_GPIO0_C0, WK3588_PMU2_IOC_WEG + 0x0018},
	{WK_GPIO0_C4, WK3588_PMU2_IOC_WEG + 0x001C},
	{WK_GPIO0_D0, WK3588_PMU2_IOC_WEG + 0x0020},
	{WK_GPIO0_D4, WK3588_PMU2_IOC_WEG + 0x0024},
	{WK_GPIO1_A0, WK3588_VCCIO1_4_IOC_WEG + 0x0020},
	{WK_GPIO1_A4, WK3588_VCCIO1_4_IOC_WEG + 0x0024},
	{WK_GPIO1_B0, WK3588_VCCIO1_4_IOC_WEG + 0x0028},
	{WK_GPIO1_B4, WK3588_VCCIO1_4_IOC_WEG + 0x002C},
	{WK_GPIO1_C0, WK3588_VCCIO1_4_IOC_WEG + 0x0030},
	{WK_GPIO1_C4, WK3588_VCCIO1_4_IOC_WEG + 0x0034},
	{WK_GPIO1_D0, WK3588_VCCIO1_4_IOC_WEG + 0x0038},
	{WK_GPIO1_D4, WK3588_VCCIO1_4_IOC_WEG + 0x003C},
	{WK_GPIO2_A0, WK3588_EMMC_IOC_WEG + 0x0040},
	{WK_GPIO2_A4, WK3588_VCCIO3_5_IOC_WEG + 0x0044},
	{WK_GPIO2_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0048},
	{WK_GPIO2_B4, WK3588_VCCIO3_5_IOC_WEG + 0x004C},
	{WK_GPIO2_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0050},
	{WK_GPIO2_C4, WK3588_VCCIO3_5_IOC_WEG + 0x0054},
	{WK_GPIO2_D0, WK3588_EMMC_IOC_WEG + 0x0058},
	{WK_GPIO2_D4, WK3588_EMMC_IOC_WEG + 0x005C},
	{WK_GPIO3_A0, WK3588_VCCIO3_5_IOC_WEG + 0x0060},
	{WK_GPIO3_A4, WK3588_VCCIO3_5_IOC_WEG + 0x0064},
	{WK_GPIO3_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0068},
	{WK_GPIO3_B4, WK3588_VCCIO3_5_IOC_WEG + 0x006C},
	{WK_GPIO3_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0070},
	{WK_GPIO3_C4, WK3588_VCCIO3_5_IOC_WEG + 0x0074},
	{WK_GPIO3_D0, WK3588_VCCIO3_5_IOC_WEG + 0x0078},
	{WK_GPIO3_D4, WK3588_VCCIO3_5_IOC_WEG + 0x007C},
	{WK_GPIO4_A0, WK3588_VCCIO6_IOC_WEG + 0x0080},
	{WK_GPIO4_A4, WK3588_VCCIO6_IOC_WEG + 0x0084},
	{WK_GPIO4_B0, WK3588_VCCIO6_IOC_WEG + 0x0088},
	{WK_GPIO4_B4, WK3588_VCCIO6_IOC_WEG + 0x008C},
	{WK_GPIO4_C0, WK3588_VCCIO6_IOC_WEG + 0x0090},
	{WK_GPIO4_C2, WK3588_VCCIO3_5_IOC_WEG + 0x0090},
	{WK_GPIO4_C4, WK3588_VCCIO3_5_IOC_WEG + 0x0094},
	{WK_GPIO4_D0, WK3588_VCCIO2_IOC_WEG + 0x0098},
	{WK_GPIO4_D4, WK3588_VCCIO2_IOC_WEG + 0x009C},
};

static const u32 wk3588_p_wegs[][2] = {
	{WK_GPIO0_A0, WK3588_PMU1_IOC_WEG + 0x0020},
	{WK_GPIO0_B0, WK3588_PMU1_IOC_WEG + 0x0024},
	{WK_GPIO0_B5, WK3588_PMU2_IOC_WEG + 0x0028},
	{WK_GPIO0_C0, WK3588_PMU2_IOC_WEG + 0x002C},
	{WK_GPIO0_D0, WK3588_PMU2_IOC_WEG + 0x0030},
	{WK_GPIO1_A0, WK3588_VCCIO1_4_IOC_WEG + 0x0110},
	{WK_GPIO1_B0, WK3588_VCCIO1_4_IOC_WEG + 0x0114},
	{WK_GPIO1_C0, WK3588_VCCIO1_4_IOC_WEG + 0x0118},
	{WK_GPIO1_D0, WK3588_VCCIO1_4_IOC_WEG + 0x011C},
	{WK_GPIO2_A0, WK3588_EMMC_IOC_WEG + 0x0120},
	{WK_GPIO2_A6, WK3588_VCCIO3_5_IOC_WEG + 0x0120},
	{WK_GPIO2_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0124},
	{WK_GPIO2_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0128},
	{WK_GPIO2_D0, WK3588_EMMC_IOC_WEG + 0x012C},
	{WK_GPIO3_A0, WK3588_VCCIO3_5_IOC_WEG + 0x0130},
	{WK_GPIO3_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0134},
	{WK_GPIO3_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0138},
	{WK_GPIO3_D0, WK3588_VCCIO3_5_IOC_WEG + 0x013C},
	{WK_GPIO4_A0, WK3588_VCCIO6_IOC_WEG + 0x0140},
	{WK_GPIO4_B0, WK3588_VCCIO6_IOC_WEG + 0x0144},
	{WK_GPIO4_C0, WK3588_VCCIO6_IOC_WEG + 0x0148},
	{WK_GPIO4_C2, WK3588_VCCIO3_5_IOC_WEG + 0x0148},
	{WK_GPIO4_D0, WK3588_VCCIO2_IOC_WEG + 0x014C},
};

static const u32 wk3588_smt_wegs[][2] = {
	{WK_GPIO0_A0, WK3588_PMU1_IOC_WEG + 0x0030},
	{WK_GPIO0_B0, WK3588_PMU1_IOC_WEG + 0x0034},
	{WK_GPIO0_B5, WK3588_PMU2_IOC_WEG + 0x0040},
	{WK_GPIO0_C0, WK3588_PMU2_IOC_WEG + 0x0044},
	{WK_GPIO0_D0, WK3588_PMU2_IOC_WEG + 0x0048},
	{WK_GPIO1_A0, WK3588_VCCIO1_4_IOC_WEG + 0x0210},
	{WK_GPIO1_B0, WK3588_VCCIO1_4_IOC_WEG + 0x0214},
	{WK_GPIO1_C0, WK3588_VCCIO1_4_IOC_WEG + 0x0218},
	{WK_GPIO1_D0, WK3588_VCCIO1_4_IOC_WEG + 0x021C},
	{WK_GPIO2_A0, WK3588_EMMC_IOC_WEG + 0x0220},
	{WK_GPIO2_A6, WK3588_VCCIO3_5_IOC_WEG + 0x0220},
	{WK_GPIO2_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0224},
	{WK_GPIO2_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0228},
	{WK_GPIO2_D0, WK3588_EMMC_IOC_WEG + 0x022C},
	{WK_GPIO3_A0, WK3588_VCCIO3_5_IOC_WEG + 0x0230},
	{WK_GPIO3_B0, WK3588_VCCIO3_5_IOC_WEG + 0x0234},
	{WK_GPIO3_C0, WK3588_VCCIO3_5_IOC_WEG + 0x0238},
	{WK_GPIO3_D0, WK3588_VCCIO3_5_IOC_WEG + 0x023C},
	{WK_GPIO4_A0, WK3588_VCCIO6_IOC_WEG + 0x0240},
	{WK_GPIO4_B0, WK3588_VCCIO6_IOC_WEG + 0x0244},
	{WK_GPIO4_C0, WK3588_VCCIO6_IOC_WEG + 0x0248},
	{WK_GPIO4_C2, WK3588_VCCIO3_5_IOC_WEG + 0x0248},
	{WK_GPIO4_D0, WK3588_VCCIO2_IOC_WEG + 0x024C},
};

#define WK3588_PUWW_BITS_PEW_PIN		2
#define WK3588_PUWW_PINS_PEW_WEG		8

static int wk3588_cawc_puww_weg_and_bit(stwuct wockchip_pin_bank *bank,
					int pin_num, stwuct wegmap **wegmap,
					int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	fow (i = AWWAY_SIZE(wk3588_p_wegs) - 1; i >= 0; i--) {
		if (pin >= wk3588_p_wegs[i][0]) {
			*weg = wk3588_p_wegs[i][1];
			*wegmap = info->wegmap_base;
			*bit = pin_num % WK3588_PUWW_PINS_PEW_WEG;
			*bit *= WK3588_PUWW_BITS_PEW_PIN;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

#define WK3588_DWV_BITS_PEW_PIN		4
#define WK3588_DWV_PINS_PEW_WEG		4

static int wk3588_cawc_dwv_weg_and_bit(stwuct wockchip_pin_bank *bank,
				       int pin_num, stwuct wegmap **wegmap,
				       int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	fow (i = AWWAY_SIZE(wk3588_ds_wegs) - 1; i >= 0; i--) {
		if (pin >= wk3588_ds_wegs[i][0]) {
			*weg = wk3588_ds_wegs[i][1];
			*wegmap = info->wegmap_base;
			*bit = pin_num % WK3588_DWV_PINS_PEW_WEG;
			*bit *= WK3588_DWV_BITS_PEW_PIN;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

#define WK3588_SMT_BITS_PEW_PIN		1
#define WK3588_SMT_PINS_PEW_WEG		8

static int wk3588_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					   int pin_num,
					   stwuct wegmap **wegmap,
					   int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	fow (i = AWWAY_SIZE(wk3588_smt_wegs) - 1; i >= 0; i--) {
		if (pin >= wk3588_smt_wegs[i][0]) {
			*weg = wk3588_smt_wegs[i][1];
			*wegmap = info->wegmap_base;
			*bit = pin_num % WK3588_SMT_PINS_PEW_WEG;
			*bit *= WK3588_SMT_BITS_PEW_PIN;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int wockchip_pewpin_dwv_wist[DWV_TYPE_MAX][8] = {
	{ 2, 4, 8, 12, -1, -1, -1, -1 },
	{ 3, 6, 9, 12, -1, -1, -1, -1 },
	{ 5, 10, 15, 20, -1, -1, -1, -1 },
	{ 4, 6, 8, 10, 12, 14, 16, 18 },
	{ 4, 7, 10, 13, 16, 19, 22, 26 }
};

static int wockchip_get_dwive_pewpin(stwuct wockchip_pin_bank *bank,
				     int pin_num)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	stwuct wegmap *wegmap;
	int weg, wet;
	u32 data, temp, wmask_bits;
	u8 bit;
	int dwv_type = bank->dwv[pin_num / 8].dwv_type;

	wet = ctww->dwv_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;

	switch (dwv_type) {
	case DWV_TYPE_IO_1V8_3V0_AUTO:
	case DWV_TYPE_IO_3V3_ONWY:
		wmask_bits = WK3399_DWV_3BITS_PEW_PIN;
		switch (bit) {
		case 0 ... 12:
			/* weguwaw case, nothing to do */
			bweak;
		case 15:
			/*
			 * dwive-stwength offset is speciaw, as it is
			 * spwead ovew 2 wegistews
			 */
			wet = wegmap_wead(wegmap, weg, &data);
			if (wet)
				wetuwn wet;

			wet = wegmap_wead(wegmap, weg + 0x4, &temp);
			if (wet)
				wetuwn wet;

			/*
			 * the bit data[15] contains bit 0 of the vawue
			 * whiwe temp[1:0] contains bits 2 and 1
			 */
			data >>= 15;
			temp &= 0x3;
			temp <<= 1;
			data |= temp;

			wetuwn wockchip_pewpin_dwv_wist[dwv_type][data];
		case 18 ... 21:
			/* setting fuwwy encwosed in the second wegistew */
			weg += 4;
			bit -= 16;
			bweak;
		defauwt:
			dev_eww(dev, "unsuppowted bit: %d fow pinctww dwive type: %d\n",
				bit, dwv_type);
			wetuwn -EINVAW;
		}

		bweak;
	case DWV_TYPE_IO_DEFAUWT:
	case DWV_TYPE_IO_1V8_OW_3V0:
	case DWV_TYPE_IO_1V8_ONWY:
		wmask_bits = WK3288_DWV_BITS_PEW_PIN;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted pinctww dwive type: %d\n", dwv_type);
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wegmap, weg, &data);
	if (wet)
		wetuwn wet;

	data >>= bit;
	data &= (1 << wmask_bits) - 1;

	wetuwn wockchip_pewpin_dwv_wist[dwv_type][data];
}

static int wockchip_set_dwive_pewpin(stwuct wockchip_pin_bank *bank,
				     int pin_num, int stwength)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	stwuct wegmap *wegmap;
	int weg, wet, i;
	u32 data, wmask, wmask_bits, temp;
	u8 bit;
	int dwv_type = bank->dwv[pin_num / 8].dwv_type;

	dev_dbg(dev, "setting dwive of GPIO%d-%d to %d\n",
		bank->bank_num, pin_num, stwength);

	wet = ctww->dwv_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;
	if (ctww->type == WK3588) {
		wmask_bits = WK3588_DWV_BITS_PEW_PIN;
		wet = stwength;
		goto config;
	} ewse if (ctww->type == WK3568) {
		wmask_bits = WK3568_DWV_BITS_PEW_PIN;
		wet = (1 << (stwength + 1)) - 1;
		goto config;
	}

	if (ctww->type == WV1126) {
		wmask_bits = WV1126_DWV_BITS_PEW_PIN;
		wet = stwength;
		goto config;
	}

	wet = -EINVAW;
	fow (i = 0; i < AWWAY_SIZE(wockchip_pewpin_dwv_wist[dwv_type]); i++) {
		if (wockchip_pewpin_dwv_wist[dwv_type][i] == stwength) {
			wet = i;
			bweak;
		} ewse if (wockchip_pewpin_dwv_wist[dwv_type][i] < 0) {
			wet = wockchip_pewpin_dwv_wist[dwv_type][i];
			bweak;
		}
	}

	if (wet < 0) {
		dev_eww(dev, "unsuppowted dwivew stwength %d\n", stwength);
		wetuwn wet;
	}

	switch (dwv_type) {
	case DWV_TYPE_IO_1V8_3V0_AUTO:
	case DWV_TYPE_IO_3V3_ONWY:
		wmask_bits = WK3399_DWV_3BITS_PEW_PIN;
		switch (bit) {
		case 0 ... 12:
			/* weguwaw case, nothing to do */
			bweak;
		case 15:
			/*
			 * dwive-stwength offset is speciaw, as it is spwead
			 * ovew 2 wegistews, the bit data[15] contains bit 0
			 * of the vawue whiwe temp[1:0] contains bits 2 and 1
			 */
			data = (wet & 0x1) << 15;
			temp = (wet >> 0x1) & 0x3;

			wmask = BIT(15) | BIT(31);
			data |= BIT(31);
			wet = wegmap_update_bits(wegmap, weg, wmask, data);
			if (wet)
				wetuwn wet;

			wmask = 0x3 | (0x3 << 16);
			temp |= (0x3 << 16);
			weg += 0x4;
			wet = wegmap_update_bits(wegmap, weg, wmask, temp);

			wetuwn wet;
		case 18 ... 21:
			/* setting fuwwy encwosed in the second wegistew */
			weg += 4;
			bit -= 16;
			bweak;
		defauwt:
			dev_eww(dev, "unsuppowted bit: %d fow pinctww dwive type: %d\n",
				bit, dwv_type);
			wetuwn -EINVAW;
		}
		bweak;
	case DWV_TYPE_IO_DEFAUWT:
	case DWV_TYPE_IO_1V8_OW_3V0:
	case DWV_TYPE_IO_1V8_ONWY:
		wmask_bits = WK3288_DWV_BITS_PEW_PIN;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted pinctww dwive type: %d\n", dwv_type);
		wetuwn -EINVAW;
	}

config:
	/* enabwe the wwite to the equivawent wowew bits */
	data = ((1 << wmask_bits) - 1) << (bit + 16);
	wmask = data | (data >> 16);
	data |= (wet << bit);

	wet = wegmap_update_bits(wegmap, weg, wmask, data);

	wetuwn wet;
}

static int wockchip_puww_wist[PUWW_TYPE_MAX][4] = {
	{
		PIN_CONFIG_BIAS_DISABWE,
		PIN_CONFIG_BIAS_PUWW_UP,
		PIN_CONFIG_BIAS_PUWW_DOWN,
		PIN_CONFIG_BIAS_BUS_HOWD
	},
	{
		PIN_CONFIG_BIAS_DISABWE,
		PIN_CONFIG_BIAS_PUWW_DOWN,
		PIN_CONFIG_BIAS_DISABWE,
		PIN_CONFIG_BIAS_PUWW_UP
	},
};

static int wockchip_get_puww(stwuct wockchip_pin_bank *bank, int pin_num)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	stwuct wegmap *wegmap;
	int weg, wet, puww_type;
	u8 bit;
	u32 data;

	/* wk3066b does suppowt any puwws */
	if (ctww->type == WK3066B)
		wetuwn PIN_CONFIG_BIAS_DISABWE;

	wet = ctww->puww_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wegmap, weg, &data);
	if (wet)
		wetuwn wet;

	switch (ctww->type) {
	case WK2928:
	case WK3128:
		wetuwn !(data & BIT(bit))
				? PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT
				: PIN_CONFIG_BIAS_DISABWE;
	case PX30:
	case WV1108:
	case WK3188:
	case WK3288:
	case WK3308:
	case WK3368:
	case WK3399:
	case WK3568:
	case WK3588:
		puww_type = bank->puww_type[pin_num / 8];
		data >>= bit;
		data &= (1 << WK3188_PUWW_BITS_PEW_PIN) - 1;
		/*
		 * In the TWM, puww-up being 1 fow evewything except the GPIO0_D3-D6,
		 * whewe that puww up vawue becomes 3.
		 */
		if (ctww->type == WK3568 && bank->bank_num == 0 && pin_num >= 27 && pin_num <= 30) {
			if (data == 3)
				data = 1;
		}

		wetuwn wockchip_puww_wist[puww_type][data];
	defauwt:
		dev_eww(dev, "unsuppowted pinctww type\n");
		wetuwn -EINVAW;
	};
}

static int wockchip_set_puww(stwuct wockchip_pin_bank *bank,
					int pin_num, int puww)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	stwuct wegmap *wegmap;
	int weg, wet, i, puww_type;
	u8 bit;
	u32 data, wmask;

	dev_dbg(dev, "setting puww of GPIO%d-%d to %d\n", bank->bank_num, pin_num, puww);

	/* wk3066b does suppowt any puwws */
	if (ctww->type == WK3066B)
		wetuwn puww ? -EINVAW : 0;

	wet = ctww->puww_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;

	switch (ctww->type) {
	case WK2928:
	case WK3128:
		data = BIT(bit + 16);
		if (puww == PIN_CONFIG_BIAS_DISABWE)
			data |= BIT(bit);
		wet = wegmap_wwite(wegmap, weg, data);
		bweak;
	case PX30:
	case WV1108:
	case WV1126:
	case WK3188:
	case WK3288:
	case WK3308:
	case WK3368:
	case WK3399:
	case WK3568:
	case WK3588:
		puww_type = bank->puww_type[pin_num / 8];
		wet = -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(wockchip_puww_wist[puww_type]);
			i++) {
			if (wockchip_puww_wist[puww_type][i] == puww) {
				wet = i;
				bweak;
			}
		}
		/*
		 * In the TWM, puww-up being 1 fow evewything except the GPIO0_D3-D6,
		 * whewe that puww up vawue becomes 3.
		 */
		if (ctww->type == WK3568 && bank->bank_num == 0 && pin_num >= 27 && pin_num <= 30) {
			if (wet == 1)
				wet = 3;
		}

		if (wet < 0) {
			dev_eww(dev, "unsuppowted puww setting %d\n", puww);
			wetuwn wet;
		}

		/* enabwe the wwite to the equivawent wowew bits */
		data = ((1 << WK3188_PUWW_BITS_PEW_PIN) - 1) << (bit + 16);
		wmask = data | (data >> 16);
		data |= (wet << bit);

		wet = wegmap_update_bits(wegmap, weg, wmask, data);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted pinctww type\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

#define WK3328_SCHMITT_BITS_PEW_PIN		1
#define WK3328_SCHMITT_PINS_PEW_WEG		16
#define WK3328_SCHMITT_BANK_STWIDE		8
#define WK3328_SCHMITT_GWF_OFFSET		0x380

static int wk3328_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					   int pin_num,
					   stwuct wegmap **wegmap,
					   int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	*wegmap = info->wegmap_base;
	*weg = WK3328_SCHMITT_GWF_OFFSET;

	*weg += bank->bank_num * WK3328_SCHMITT_BANK_STWIDE;
	*weg += ((pin_num / WK3328_SCHMITT_PINS_PEW_WEG) * 4);
	*bit = pin_num % WK3328_SCHMITT_PINS_PEW_WEG;

	wetuwn 0;
}

#define WK3568_SCHMITT_BITS_PEW_PIN		2
#define WK3568_SCHMITT_PINS_PEW_WEG		8
#define WK3568_SCHMITT_BANK_STWIDE		0x10
#define WK3568_SCHMITT_GWF_OFFSET		0xc0
#define WK3568_SCHMITT_PMUGWF_OFFSET		0x30

static int wk3568_cawc_schmitt_weg_and_bit(stwuct wockchip_pin_bank *bank,
					   int pin_num,
					   stwuct wegmap **wegmap,
					   int *weg, u8 *bit)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;

	if (bank->bank_num == 0) {
		*wegmap = info->wegmap_pmu;
		*weg = WK3568_SCHMITT_PMUGWF_OFFSET;
	} ewse {
		*wegmap = info->wegmap_base;
		*weg = WK3568_SCHMITT_GWF_OFFSET;
		*weg += (bank->bank_num - 1) * WK3568_SCHMITT_BANK_STWIDE;
	}

	*weg += ((pin_num / WK3568_SCHMITT_PINS_PEW_WEG) * 4);
	*bit = pin_num % WK3568_SCHMITT_PINS_PEW_WEG;
	*bit *= WK3568_SCHMITT_BITS_PEW_PIN;

	wetuwn 0;
}

static int wockchip_get_schmitt(stwuct wockchip_pin_bank *bank, int pin_num)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct wegmap *wegmap;
	int weg, wet;
	u8 bit;
	u32 data;

	wet = ctww->schmitt_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wegmap, weg, &data);
	if (wet)
		wetuwn wet;

	data >>= bit;
	switch (ctww->type) {
	case WK3568:
		wetuwn data & ((1 << WK3568_SCHMITT_BITS_PEW_PIN) - 1);
	defauwt:
		bweak;
	}

	wetuwn data & 0x1;
}

static int wockchip_set_schmitt(stwuct wockchip_pin_bank *bank,
				int pin_num, int enabwe)
{
	stwuct wockchip_pinctww *info = bank->dwvdata;
	stwuct wockchip_pin_ctww *ctww = info->ctww;
	stwuct device *dev = info->dev;
	stwuct wegmap *wegmap;
	int weg, wet;
	u8 bit;
	u32 data, wmask;

	dev_dbg(dev, "setting input schmitt of GPIO%d-%d to %d\n",
		bank->bank_num, pin_num, enabwe);

	wet = ctww->schmitt_cawc_weg(bank, pin_num, &wegmap, &weg, &bit);
	if (wet)
		wetuwn wet;

	/* enabwe the wwite to the equivawent wowew bits */
	switch (ctww->type) {
	case WK3568:
		data = ((1 << WK3568_SCHMITT_BITS_PEW_PIN) - 1) << (bit + 16);
		wmask = data | (data >> 16);
		data |= ((enabwe ? 0x2 : 0x1) << bit);
		bweak;
	defauwt:
		data = BIT(bit + 16) | (enabwe << bit);
		wmask = BIT(bit + 16) | BIT(bit);
		bweak;
	}

	wetuwn wegmap_update_bits(wegmap, weg, wmask, data);
}

/*
 * Pinmux_ops handwing
 */

static int wockchip_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->nfunctions;
}

static const chaw *wockchip_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					  unsigned sewectow)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->functions[sewectow].name;
}

static int wockchip_pmx_get_gwoups(stwuct pinctww_dev *pctwdev,
				unsigned sewectow, const chaw * const **gwoups,
				unsigned * const num_gwoups)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = info->functions[sewectow].gwoups;
	*num_gwoups = info->functions[sewectow].ngwoups;

	wetuwn 0;
}

static int wockchip_pmx_set(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			    unsigned gwoup)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	const unsigned int *pins = info->gwoups[gwoup].pins;
	const stwuct wockchip_pin_config *data = info->gwoups[gwoup].data;
	stwuct device *dev = info->dev;
	stwuct wockchip_pin_bank *bank;
	int cnt, wet = 0;

	dev_dbg(dev, "enabwe function %s gwoup %s\n",
		info->functions[sewectow].name, info->gwoups[gwoup].name);

	/*
	 * fow each pin in the pin gwoup sewected, pwogwam the cowwesponding
	 * pin function numbew in the config wegistew.
	 */
	fow (cnt = 0; cnt < info->gwoups[gwoup].npins; cnt++) {
		bank = pin_to_bank(info, pins[cnt]);
		wet = wockchip_set_mux(bank, pins[cnt] - bank->pin_base,
				       data[cnt].func);
		if (wet)
			bweak;
	}

	if (wet) {
		/* wevewt the awweady done pin settings */
		fow (cnt--; cnt >= 0; cnt--)
			wockchip_set_mux(bank, pins[cnt] - bank->pin_base, 0);

		wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					   stwuct pinctww_gpio_wange *wange,
					   unsigned offset,
					   boow input)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wockchip_pin_bank *bank;

	bank = pin_to_bank(info, offset);
	wetuwn wockchip_set_mux(bank, offset - bank->pin_base, WK_FUNC_GPIO);
}

static const stwuct pinmux_ops wockchip_pmx_ops = {
	.get_functions_count	= wockchip_pmx_get_funcs_count,
	.get_function_name	= wockchip_pmx_get_func_name,
	.get_function_gwoups	= wockchip_pmx_get_gwoups,
	.set_mux		= wockchip_pmx_set,
	.gpio_set_diwection	= wockchip_pmx_gpio_set_diwection,
};

/*
 * Pinconf_ops handwing
 */

static boow wockchip_pinconf_puww_vawid(stwuct wockchip_pin_ctww *ctww,
					enum pin_config_pawam puww)
{
	switch (ctww->type) {
	case WK2928:
	case WK3128:
		wetuwn (puww == PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT ||
					puww == PIN_CONFIG_BIAS_DISABWE);
	case WK3066B:
		wetuwn puww ? fawse : twue;
	case PX30:
	case WV1108:
	case WV1126:
	case WK3188:
	case WK3288:
	case WK3308:
	case WK3368:
	case WK3399:
	case WK3568:
	case WK3588:
		wetuwn (puww != PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT);
	}

	wetuwn fawse;
}

static int wockchip_pinconf_defew_pin(stwuct wockchip_pin_bank *bank,
					 unsigned int pin, u32 pawam, u32 awg)
{
	stwuct wockchip_pin_defewwed *cfg;

	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;

	cfg->pin = pin;
	cfg->pawam = pawam;
	cfg->awg = awg;

	wist_add_taiw(&cfg->head, &bank->defewwed_pins);

	wetuwn 0;
}

/* set the pin config settings fow a specified pin */
static int wockchip_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
				unsigned wong *configs, unsigned num_configs)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wockchip_pin_bank *bank = pin_to_bank(info, pin);
	stwuct gpio_chip *gpio = &bank->gpio_chip;
	enum pin_config_pawam pawam;
	u32 awg;
	int i;
	int wc;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		if (pawam == PIN_CONFIG_OUTPUT || pawam == PIN_CONFIG_INPUT_ENABWE) {
			/*
			 * Check fow gpio dwivew not being pwobed yet.
			 * The wock makes suwe that eithew gpio-pwobe has compweted
			 * ow the gpio dwivew hasn't pwobed yet.
			 */
			mutex_wock(&bank->defewwed_wock);
			if (!gpio || !gpio->diwection_output) {
				wc = wockchip_pinconf_defew_pin(bank, pin - bank->pin_base, pawam,
								awg);
				mutex_unwock(&bank->defewwed_wock);
				if (wc)
					wetuwn wc;

				bweak;
			}
			mutex_unwock(&bank->defewwed_wock);
		}

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			wc =  wockchip_set_puww(bank, pin - bank->pin_base,
				pawam);
			if (wc)
				wetuwn wc;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
		case PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT:
		case PIN_CONFIG_BIAS_BUS_HOWD:
			if (!wockchip_pinconf_puww_vawid(info->ctww, pawam))
				wetuwn -ENOTSUPP;

			if (!awg)
				wetuwn -EINVAW;

			wc = wockchip_set_puww(bank, pin - bank->pin_base,
				pawam);
			if (wc)
				wetuwn wc;
			bweak;
		case PIN_CONFIG_OUTPUT:
			wc = wockchip_set_mux(bank, pin - bank->pin_base,
					      WK_FUNC_GPIO);
			if (wc != WK_FUNC_GPIO)
				wetuwn -EINVAW;

			wc = gpio->diwection_output(gpio, pin - bank->pin_base,
						    awg);
			if (wc)
				wetuwn wc;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			wc = wockchip_set_mux(bank, pin - bank->pin_base,
					      WK_FUNC_GPIO);
			if (wc != WK_FUNC_GPIO)
				wetuwn -EINVAW;

			wc = gpio->diwection_input(gpio, pin - bank->pin_base);
			if (wc)
				wetuwn wc;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			/* wk3288 is the fiwst with pew-pin dwive-stwength */
			if (!info->ctww->dwv_cawc_weg)
				wetuwn -ENOTSUPP;

			wc = wockchip_set_dwive_pewpin(bank,
						pin - bank->pin_base, awg);
			if (wc < 0)
				wetuwn wc;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			if (!info->ctww->schmitt_cawc_weg)
				wetuwn -ENOTSUPP;

			wc = wockchip_set_schmitt(bank,
						  pin - bank->pin_base, awg);
			if (wc < 0)
				wetuwn wc;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
			bweak;
		}
	} /* fow each config */

	wetuwn 0;
}

/* get the pin config settings fow a specified pin */
static int wockchip_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
							unsigned wong *config)
{
	stwuct wockchip_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wockchip_pin_bank *bank = pin_to_bank(info, pin);
	stwuct gpio_chip *gpio = &bank->gpio_chip;
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	u16 awg;
	int wc;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (wockchip_get_puww(bank, pin - bank->pin_base) != pawam)
			wetuwn -EINVAW;

		awg = 0;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
	case PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT:
	case PIN_CONFIG_BIAS_BUS_HOWD:
		if (!wockchip_pinconf_puww_vawid(info->ctww, pawam))
			wetuwn -ENOTSUPP;

		if (wockchip_get_puww(bank, pin - bank->pin_base) != pawam)
			wetuwn -EINVAW;

		awg = 1;
		bweak;
	case PIN_CONFIG_OUTPUT:
		wc = wockchip_get_mux(bank, pin - bank->pin_base);
		if (wc != WK_FUNC_GPIO)
			wetuwn -EINVAW;

		if (!gpio || !gpio->get) {
			awg = 0;
			bweak;
		}

		wc = gpio->get(gpio, pin - bank->pin_base);
		if (wc < 0)
			wetuwn wc;

		awg = wc ? 1 : 0;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		/* wk3288 is the fiwst with pew-pin dwive-stwength */
		if (!info->ctww->dwv_cawc_weg)
			wetuwn -ENOTSUPP;

		wc = wockchip_get_dwive_pewpin(bank, pin - bank->pin_base);
		if (wc < 0)
			wetuwn wc;

		awg = wc;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (!info->ctww->schmitt_cawc_weg)
			wetuwn -ENOTSUPP;

		wc = wockchip_get_schmitt(bank, pin - bank->pin_base);
		if (wc < 0)
			wetuwn wc;

		awg = wc;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
		bweak;
	}

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static const stwuct pinconf_ops wockchip_pinconf_ops = {
	.pin_config_get			= wockchip_pinconf_get,
	.pin_config_set			= wockchip_pinconf_set,
	.is_genewic			= twue,
};

static const stwuct of_device_id wockchip_bank_match[] = {
	{ .compatibwe = "wockchip,gpio-bank" },
	{ .compatibwe = "wockchip,wk3188-gpio-bank0" },
	{},
};

static void wockchip_pinctww_chiwd_count(stwuct wockchip_pinctww *info,
						stwuct device_node *np)
{
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(np, chiwd) {
		if (of_match_node(wockchip_bank_match, chiwd))
			continue;

		info->nfunctions++;
		info->ngwoups += of_get_chiwd_count(chiwd);
	}
}

static int wockchip_pinctww_pawse_gwoups(stwuct device_node *np,
					      stwuct wockchip_pin_gwoup *gwp,
					      stwuct wockchip_pinctww *info,
					      u32 index)
{
	stwuct device *dev = info->dev;
	stwuct wockchip_pin_bank *bank;
	int size;
	const __be32 *wist;
	int num;
	int i, j;
	int wet;

	dev_dbg(dev, "gwoup(%d): %pOFn\n", index, np);

	/* Initiawise gwoup */
	gwp->name = np->name;

	/*
	 * the binding fowmat is wockchip,pins = <bank pin mux CONFIG>,
	 * do sanity check and cawcuwate pins numbew
	 */
	wist = of_get_pwopewty(np, "wockchip,pins", &size);
	/* we do not check wetuwn since it's safe node passed down */
	size /= sizeof(*wist);
	if (!size || size % 4)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "wwong pins numbew ow pins and configs shouwd be by 4\n");

	gwp->npins = size / 4;

	gwp->pins = devm_kcawwoc(dev, gwp->npins, sizeof(*gwp->pins), GFP_KEWNEW);
	gwp->data = devm_kcawwoc(dev, gwp->npins, sizeof(*gwp->data), GFP_KEWNEW);
	if (!gwp->pins || !gwp->data)
		wetuwn -ENOMEM;

	fow (i = 0, j = 0; i < size; i += 4, j++) {
		const __be32 *phandwe;
		stwuct device_node *np_config;

		num = be32_to_cpu(*wist++);
		bank = bank_num_to_bank(info, num);
		if (IS_EWW(bank))
			wetuwn PTW_EWW(bank);

		gwp->pins[j] = bank->pin_base + be32_to_cpu(*wist++);
		gwp->data[j].func = be32_to_cpu(*wist++);

		phandwe = wist++;
		if (!phandwe)
			wetuwn -EINVAW;

		np_config = of_find_node_by_phandwe(be32_to_cpup(phandwe));
		wet = pinconf_genewic_pawse_dt_config(np_config, NUWW,
				&gwp->data[j].configs, &gwp->data[j].nconfigs);
		of_node_put(np_config);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_pinctww_pawse_functions(stwuct device_node *np,
						stwuct wockchip_pinctww *info,
						u32 index)
{
	stwuct device *dev = info->dev;
	stwuct device_node *chiwd;
	stwuct wockchip_pmx_func *func;
	stwuct wockchip_pin_gwoup *gwp;
	int wet;
	static u32 gwp_index;
	u32 i = 0;

	dev_dbg(dev, "pawse function(%d): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initiawise function */
	func->name = np->name;
	func->ngwoups = of_get_chiwd_count(np);
	if (func->ngwoups <= 0)
		wetuwn 0;

	func->gwoups = devm_kcawwoc(dev, func->ngwoups, sizeof(*func->gwoups), GFP_KEWNEW);
	if (!func->gwoups)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np, chiwd) {
		func->gwoups[i] = chiwd->name;
		gwp = &info->gwoups[gwp_index++];
		wet = wockchip_pinctww_pawse_gwoups(chiwd, gwp, info, i++);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wockchip_pinctww_pawse_dt(stwuct pwatfowm_device *pdev,
					      stwuct wockchip_pinctww *info)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int wet;
	int i;

	wockchip_pinctww_chiwd_count(info, np);

	dev_dbg(dev, "nfunctions = %d\n", info->nfunctions);
	dev_dbg(dev, "ngwoups = %d\n", info->ngwoups);

	info->functions = devm_kcawwoc(dev, info->nfunctions, sizeof(*info->functions), GFP_KEWNEW);
	if (!info->functions)
		wetuwn -ENOMEM;

	info->gwoups = devm_kcawwoc(dev, info->ngwoups, sizeof(*info->gwoups), GFP_KEWNEW);
	if (!info->gwoups)
		wetuwn -ENOMEM;

	i = 0;

	fow_each_chiwd_of_node(np, chiwd) {
		if (of_match_node(wockchip_bank_match, chiwd))
			continue;

		wet = wockchip_pinctww_pawse_functions(chiwd, info, i++);
		if (wet) {
			dev_eww(dev, "faiwed to pawse function\n");
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wockchip_pinctww_wegistew(stwuct pwatfowm_device *pdev,
					stwuct wockchip_pinctww *info)
{
	stwuct pinctww_desc *ctwwdesc = &info->pctw;
	stwuct pinctww_pin_desc *pindesc, *pdesc;
	stwuct wockchip_pin_bank *pin_bank;
	stwuct device *dev = &pdev->dev;
	chaw **pin_names;
	int pin, bank, wet;
	int k;

	ctwwdesc->name = "wockchip-pinctww";
	ctwwdesc->ownew = THIS_MODUWE;
	ctwwdesc->pctwops = &wockchip_pctww_ops;
	ctwwdesc->pmxops = &wockchip_pmx_ops;
	ctwwdesc->confops = &wockchip_pinconf_ops;

	pindesc = devm_kcawwoc(dev, info->ctww->nw_pins, sizeof(*pindesc), GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;

	ctwwdesc->pins = pindesc;
	ctwwdesc->npins = info->ctww->nw_pins;

	pdesc = pindesc;
	fow (bank = 0, k = 0; bank < info->ctww->nw_banks; bank++) {
		pin_bank = &info->ctww->pin_banks[bank];

		pin_names = devm_kaspwintf_stwawway(dev, pin_bank->name, pin_bank->nw_pins);
		if (IS_EWW(pin_names))
			wetuwn PTW_EWW(pin_names);

		fow (pin = 0; pin < pin_bank->nw_pins; pin++, k++) {
			pdesc->numbew = k;
			pdesc->name = pin_names[pin];
			pdesc++;
		}

		INIT_WIST_HEAD(&pin_bank->defewwed_pins);
		mutex_init(&pin_bank->defewwed_wock);
	}

	wet = wockchip_pinctww_pawse_dt(pdev, info);
	if (wet)
		wetuwn wet;

	info->pctw_dev = devm_pinctww_wegistew(dev, ctwwdesc, info);
	if (IS_EWW(info->pctw_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(info->pctw_dev), "couwd not wegistew pinctww dwivew\n");

	wetuwn 0;
}

static const stwuct of_device_id wockchip_pinctww_dt_match[];

/* wetwieve the soc specific data */
static stwuct wockchip_pin_ctww *wockchip_pinctww_get_soc_data(
						stwuct wockchip_pinctww *d,
						stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	const stwuct of_device_id *match;
	stwuct wockchip_pin_ctww *ctww;
	stwuct wockchip_pin_bank *bank;
	int gwf_offs, pmu_offs, dwv_gwf_offs, dwv_pmu_offs, i, j;

	match = of_match_node(wockchip_pinctww_dt_match, node);
	ctww = (stwuct wockchip_pin_ctww *)match->data;

	gwf_offs = ctww->gwf_mux_offset;
	pmu_offs = ctww->pmu_mux_offset;
	dwv_pmu_offs = ctww->pmu_dwv_offset;
	dwv_gwf_offs = ctww->gwf_dwv_offset;
	bank = ctww->pin_banks;
	fow (i = 0; i < ctww->nw_banks; ++i, ++bank) {
		int bank_pins = 0;

		waw_spin_wock_init(&bank->swock);
		bank->dwvdata = d;
		bank->pin_base = ctww->nw_pins;
		ctww->nw_pins += bank->nw_pins;

		/* cawcuwate iomux and dwv offsets */
		fow (j = 0; j < 4; j++) {
			stwuct wockchip_iomux *iom = &bank->iomux[j];
			stwuct wockchip_dwv *dwv = &bank->dwv[j];
			int inc;

			if (bank_pins >= bank->nw_pins)
				bweak;

			/* pweset iomux offset vawue, set new stawt vawue */
			if (iom->offset >= 0) {
				if ((iom->type & IOMUX_SOUWCE_PMU) ||
				    (iom->type & IOMUX_W_SOUWCE_PMU))
					pmu_offs = iom->offset;
				ewse
					gwf_offs = iom->offset;
			} ewse { /* set cuwwent iomux offset */
				iom->offset = ((iom->type & IOMUX_SOUWCE_PMU) ||
					       (iom->type & IOMUX_W_SOUWCE_PMU)) ?
							pmu_offs : gwf_offs;
			}

			/* pweset dwv offset vawue, set new stawt vawue */
			if (dwv->offset >= 0) {
				if (iom->type & IOMUX_SOUWCE_PMU)
					dwv_pmu_offs = dwv->offset;
				ewse
					dwv_gwf_offs = dwv->offset;
			} ewse { /* set cuwwent dwv offset */
				dwv->offset = (iom->type & IOMUX_SOUWCE_PMU) ?
						dwv_pmu_offs : dwv_gwf_offs;
			}

			dev_dbg(dev, "bank %d, iomux %d has iom_offset 0x%x dwv_offset 0x%x\n",
				i, j, iom->offset, dwv->offset);

			/*
			 * Incwease offset accowding to iomux width.
			 * 4bit iomux'es awe spwead ovew two wegistews.
			 */
			inc = (iom->type & (IOMUX_WIDTH_4BIT |
					    IOMUX_WIDTH_3BIT |
					    IOMUX_WIDTH_2BIT)) ? 8 : 4;
			if ((iom->type & IOMUX_SOUWCE_PMU) || (iom->type & IOMUX_W_SOUWCE_PMU))
				pmu_offs += inc;
			ewse
				gwf_offs += inc;

			/*
			 * Incwease offset accowding to dwv width.
			 * 3bit dwive-stwenth'es awe spwead ovew two wegistews.
			 */
			if ((dwv->dwv_type == DWV_TYPE_IO_1V8_3V0_AUTO) ||
			    (dwv->dwv_type == DWV_TYPE_IO_3V3_ONWY))
				inc = 8;
			ewse
				inc = 4;

			if (iom->type & IOMUX_SOUWCE_PMU)
				dwv_pmu_offs += inc;
			ewse
				dwv_gwf_offs += inc;

			bank_pins += 8;
		}

		/* cawcuwate the pew-bank wecawced_mask */
		fow (j = 0; j < ctww->niomux_wecawced; j++) {
			int pin = 0;

			if (ctww->iomux_wecawced[j].num == bank->bank_num) {
				pin = ctww->iomux_wecawced[j].pin;
				bank->wecawced_mask |= BIT(pin);
			}
		}

		/* cawcuwate the pew-bank woute_mask */
		fow (j = 0; j < ctww->niomux_woutes; j++) {
			int pin = 0;

			if (ctww->iomux_woutes[j].bank_num == bank->bank_num) {
				pin = ctww->iomux_woutes[j].pin;
				bank->woute_mask |= BIT(pin);
			}
		}
	}

	wetuwn ctww;
}

#define WK3288_GWF_GPIO6C_IOMUX		0x64
#define GPIO6C6_SEW_WWITE_ENABWE	BIT(28)

static u32 wk3288_gwf_gpio6c_iomux;

static int __maybe_unused wockchip_pinctww_suspend(stwuct device *dev)
{
	stwuct wockchip_pinctww *info = dev_get_dwvdata(dev);
	int wet = pinctww_fowce_sweep(info->pctw_dev);

	if (wet)
		wetuwn wet;

	/*
	 * WK3288 GPIO6_C6 mux wouwd be modified by Maskwom when wesume, so save
	 * the setting hewe, and westowe it at wesume.
	 */
	if (info->ctww->type == WK3288) {
		wet = wegmap_wead(info->wegmap_base, WK3288_GWF_GPIO6C_IOMUX,
				  &wk3288_gwf_gpio6c_iomux);
		if (wet) {
			pinctww_fowce_defauwt(info->pctw_dev);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int __maybe_unused wockchip_pinctww_wesume(stwuct device *dev)
{
	stwuct wockchip_pinctww *info = dev_get_dwvdata(dev);
	int wet;

	if (info->ctww->type == WK3288) {
		wet = wegmap_wwite(info->wegmap_base, WK3288_GWF_GPIO6C_IOMUX,
				   wk3288_gwf_gpio6c_iomux |
				   GPIO6C6_SEW_WWITE_ENABWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn pinctww_fowce_defauwt(info->pctw_dev);
}

static SIMPWE_DEV_PM_OPS(wockchip_pinctww_dev_pm_ops, wockchip_pinctww_suspend,
			 wockchip_pinctww_wesume);

static int wockchip_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pinctww *info;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node, *node;
	stwuct wockchip_pin_ctww *ctww;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet;

	if (!dev->of_node)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "device twee node not found\n");

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = dev;

	ctww = wockchip_pinctww_get_soc_data(info, pdev);
	if (!ctww)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "dwivew data not avaiwabwe\n");
	info->ctww = ctww;

	node = of_pawse_phandwe(np, "wockchip,gwf", 0);
	if (node) {
		info->wegmap_base = syscon_node_to_wegmap(node);
		of_node_put(node);
		if (IS_EWW(info->wegmap_base))
			wetuwn PTW_EWW(info->wegmap_base);
	} ewse {
		base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		wockchip_wegmap_config.max_wegistew = wesouwce_size(wes) - 4;
		wockchip_wegmap_config.name = "wockchip,pinctww";
		info->wegmap_base =
			devm_wegmap_init_mmio(dev, base, &wockchip_wegmap_config);

		/* to check fow the owd dt-bindings */
		info->weg_size = wesouwce_size(wes);

		/* Honow the owd binding, with puww wegistews as 2nd wesouwce */
		if (ctww->type == WK3188 && info->weg_size < 0x200) {
			base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &wes);
			if (IS_EWW(base))
				wetuwn PTW_EWW(base);

			wockchip_wegmap_config.max_wegistew = wesouwce_size(wes) - 4;
			wockchip_wegmap_config.name = "wockchip,pinctww-puww";
			info->wegmap_puww =
				devm_wegmap_init_mmio(dev, base, &wockchip_wegmap_config);
		}
	}

	/* twy to find the optionaw wefewence to the pmu syscon */
	node = of_pawse_phandwe(np, "wockchip,pmu", 0);
	if (node) {
		info->wegmap_pmu = syscon_node_to_wegmap(node);
		of_node_put(node);
		if (IS_EWW(info->wegmap_pmu))
			wetuwn PTW_EWW(info->wegmap_pmu);
	}

	wet = wockchip_pinctww_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, info);

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, &pdev->dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew gpio device\n");

	wetuwn 0;
}

static void wockchip_pinctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pinctww *info = pwatfowm_get_dwvdata(pdev);
	stwuct wockchip_pin_bank *bank;
	stwuct wockchip_pin_defewwed *cfg;
	int i;

	of_pwatfowm_depopuwate(&pdev->dev);

	fow (i = 0; i < info->ctww->nw_banks; i++) {
		bank = &info->ctww->pin_banks[i];

		mutex_wock(&bank->defewwed_wock);
		whiwe (!wist_empty(&bank->defewwed_pins)) {
			cfg = wist_fiwst_entwy(&bank->defewwed_pins,
					       stwuct wockchip_pin_defewwed, head);
			wist_dew(&cfg->head);
			kfwee(cfg);
		}
		mutex_unwock(&bank->defewwed_wock);
	}
}

static stwuct wockchip_pin_bank px30_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU
			    ),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
};

static stwuct wockchip_pin_ctww px30_pin_ctww = {
		.pin_banks		= px30_pin_banks,
		.nw_banks		= AWWAY_SIZE(px30_pin_banks),
		.wabew			= "PX30-GPIO",
		.type			= PX30,
		.gwf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x0,
		.iomux_woutes		= px30_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(px30_mux_woute_data),
		.puww_cawc_weg		= px30_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= px30_cawc_dwv_weg_and_bit,
		.schmitt_cawc_weg	= px30_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wv1108_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3", 0, 0, 0, 0),
};

static stwuct wockchip_pin_ctww wv1108_pin_ctww = {
	.pin_banks		= wv1108_pin_banks,
	.nw_banks		= AWWAY_SIZE(wv1108_pin_banks),
	.wabew			= "WV1108-GPIO",
	.type			= WV1108,
	.gwf_mux_offset		= 0x10,
	.pmu_mux_offset		= 0x0,
	.iomux_wecawced		= wv1108_mux_wecawced_data,
	.niomux_wecawced	= AWWAY_SIZE(wv1108_mux_wecawced_data),
	.puww_cawc_weg		= wv1108_cawc_puww_weg_and_bit,
	.dwv_cawc_weg		= wv1108_cawc_dwv_weg_and_bit,
	.schmitt_cawc_weg	= wv1108_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wv1126_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0",
			     IOMUX_WIDTH_4BIT | IOMUX_SOUWCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOUWCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_W_SOUWCE_PMU,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS_OFFSET(1, 32, "gpio1",
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    0x10010, 0x10018, 0x10020, 0x10028),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(4, 2, "gpio4",
			     IOMUX_WIDTH_4BIT, 0, 0, 0),
};

static stwuct wockchip_pin_ctww wv1126_pin_ctww = {
	.pin_banks		= wv1126_pin_banks,
	.nw_banks		= AWWAY_SIZE(wv1126_pin_banks),
	.wabew			= "WV1126-GPIO",
	.type			= WV1126,
	.gwf_mux_offset		= 0x10004, /* mux offset fwom GPIO0_D0 */
	.pmu_mux_offset		= 0x0,
	.iomux_woutes		= wv1126_mux_woute_data,
	.niomux_woutes		= AWWAY_SIZE(wv1126_mux_woute_data),
	.iomux_wecawced		= wv1126_mux_wecawced_data,
	.niomux_wecawced	= AWWAY_SIZE(wv1126_mux_wecawced_data),
	.puww_cawc_weg		= wv1126_cawc_puww_weg_and_bit,
	.dwv_cawc_weg		= wv1126_cawc_dwv_weg_and_bit,
	.schmitt_cawc_weg	= wv1126_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wk2928_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk2928_pin_ctww = {
		.pin_banks		= wk2928_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk2928_pin_banks),
		.wabew			= "WK2928-GPIO",
		.type			= WK2928,
		.gwf_mux_offset		= 0xa8,
		.puww_cawc_weg		= wk2928_cawc_puww_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3036_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
};

static stwuct wockchip_pin_ctww wk3036_pin_ctww = {
		.pin_banks		= wk3036_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3036_pin_banks),
		.wabew			= "WK3036-GPIO",
		.type			= WK2928,
		.gwf_mux_offset		= 0xa8,
		.puww_cawc_weg		= wk2928_cawc_puww_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3066a_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
	PIN_BANK(4, 32, "gpio4"),
	PIN_BANK(6, 16, "gpio6"),
};

static stwuct wockchip_pin_ctww wk3066a_pin_ctww = {
		.pin_banks		= wk3066a_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3066a_pin_banks),
		.wabew			= "WK3066a-GPIO",
		.type			= WK2928,
		.gwf_mux_offset		= 0xa8,
		.puww_cawc_weg		= wk2928_cawc_puww_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3066b_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk3066b_pin_ctww = {
		.pin_banks	= wk3066b_pin_banks,
		.nw_banks	= AWWAY_SIZE(wk3066b_pin_banks),
		.wabew		= "WK3066b-GPIO",
		.type		= WK3066B,
		.gwf_mux_offset	= 0x60,
};

static stwuct wockchip_pin_bank wk3128_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk3128_pin_ctww = {
		.pin_banks		= wk3128_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3128_pin_banks),
		.wabew			= "WK3128-GPIO",
		.type			= WK3128,
		.gwf_mux_offset		= 0xa8,
		.iomux_wecawced		= wk3128_mux_wecawced_data,
		.niomux_wecawced	= AWWAY_SIZE(wk3128_mux_wecawced_data),
		.iomux_woutes		= wk3128_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3128_mux_woute_data),
		.puww_cawc_weg		= wk3128_cawc_puww_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3188_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_GPIO_ONWY, 0, 0, 0),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk3188_pin_ctww = {
		.pin_banks		= wk3188_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3188_pin_banks),
		.wabew			= "WK3188-GPIO",
		.type			= WK3188,
		.gwf_mux_offset		= 0x60,
		.iomux_woutes		= wk3188_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3188_mux_woute_data),
		.puww_cawc_weg		= wk3188_cawc_puww_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3228_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk3228_pin_ctww = {
		.pin_banks		= wk3228_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3228_pin_banks),
		.wabew			= "WK3228-GPIO",
		.type			= WK3288,
		.gwf_mux_offset		= 0x0,
		.iomux_woutes		= wk3228_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3228_mux_woute_data),
		.puww_cawc_weg		= wk3228_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3228_cawc_dwv_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3288_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 24, "gpio0", IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_UNWOUTED
			    ),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", IOMUX_UNWOUTED,
					     IOMUX_UNWOUTED,
					     IOMUX_UNWOUTED,
					     0
			    ),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", 0, 0, 0, IOMUX_UNWOUTED),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3", 0, 0, 0, IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     0,
					     0
			    ),
	PIN_BANK_IOMUX_FWAGS(5, 32, "gpio5", IOMUX_UNWOUTED,
					     0,
					     0,
					     IOMUX_UNWOUTED
			    ),
	PIN_BANK_IOMUX_FWAGS(6, 32, "gpio6", 0, 0, 0, IOMUX_UNWOUTED),
	PIN_BANK_IOMUX_FWAGS(7, 32, "gpio7", 0,
					     0,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_UNWOUTED
			    ),
	PIN_BANK(8, 16, "gpio8"),
};

static stwuct wockchip_pin_ctww wk3288_pin_ctww = {
		.pin_banks		= wk3288_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3288_pin_banks),
		.wabew			= "WK3288-GPIO",
		.type			= WK3288,
		.gwf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x84,
		.iomux_woutes		= wk3288_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3288_mux_woute_data),
		.puww_cawc_weg		= wk3288_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3288_cawc_dwv_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3308_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FWAGS(4, 32, "gpio4", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
};

static stwuct wockchip_pin_ctww wk3308_pin_ctww = {
		.pin_banks		= wk3308_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3308_pin_banks),
		.wabew			= "WK3308-GPIO",
		.type			= WK3308,
		.gwf_mux_offset		= 0x0,
		.iomux_wecawced		= wk3308_mux_wecawced_data,
		.niomux_wecawced	= AWWAY_SIZE(wk3308_mux_wecawced_data),
		.iomux_woutes		= wk3308_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3308_mux_woute_data),
		.puww_cawc_weg		= wk3308_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3308_cawc_dwv_weg_and_bit,
		.schmitt_cawc_weg	= wk3308_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3328_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", 0,
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0,
			     0),
};

static stwuct wockchip_pin_ctww wk3328_pin_ctww = {
		.pin_banks		= wk3328_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3328_pin_banks),
		.wabew			= "WK3328-GPIO",
		.type			= WK3288,
		.gwf_mux_offset		= 0x0,
		.iomux_wecawced		= wk3328_mux_wecawced_data,
		.niomux_wecawced	= AWWAY_SIZE(wk3328_mux_wecawced_data),
		.iomux_woutes		= wk3328_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3328_mux_woute_data),
		.puww_cawc_weg		= wk3228_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3228_cawc_dwv_weg_and_bit,
		.schmitt_cawc_weg	= wk3328_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3368_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU,
					     IOMUX_SOUWCE_PMU
			    ),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static stwuct wockchip_pin_ctww wk3368_pin_ctww = {
		.pin_banks		= wk3368_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3368_pin_banks),
		.wabew			= "WK3368-GPIO",
		.type			= WK3368,
		.gwf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x0,
		.puww_cawc_weg		= wk3368_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3368_cawc_dwv_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3399_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS_DWV_FWAGS_OFFSET_PUWW_FWAGS(0, 32, "gpio0",
							 IOMUX_SOUWCE_PMU,
							 IOMUX_SOUWCE_PMU,
							 IOMUX_SOUWCE_PMU,
							 IOMUX_SOUWCE_PMU,
							 DWV_TYPE_IO_1V8_ONWY,
							 DWV_TYPE_IO_1V8_ONWY,
							 DWV_TYPE_IO_DEFAUWT,
							 DWV_TYPE_IO_DEFAUWT,
							 0x80,
							 0x88,
							 -1,
							 -1,
							 PUWW_TYPE_IO_1V8_ONWY,
							 PUWW_TYPE_IO_1V8_ONWY,
							 PUWW_TYPE_IO_DEFAUWT,
							 PUWW_TYPE_IO_DEFAUWT
							),
	PIN_BANK_IOMUX_DWV_FWAGS_OFFSET(1, 32, "gpio1", IOMUX_SOUWCE_PMU,
					IOMUX_SOUWCE_PMU,
					IOMUX_SOUWCE_PMU,
					IOMUX_SOUWCE_PMU,
					DWV_TYPE_IO_1V8_OW_3V0,
					DWV_TYPE_IO_1V8_OW_3V0,
					DWV_TYPE_IO_1V8_OW_3V0,
					DWV_TYPE_IO_1V8_OW_3V0,
					0xa0,
					0xa8,
					0xb0,
					0xb8
					),
	PIN_BANK_DWV_FWAGS_PUWW_FWAGS(2, 32, "gpio2", DWV_TYPE_IO_1V8_OW_3V0,
				      DWV_TYPE_IO_1V8_OW_3V0,
				      DWV_TYPE_IO_1V8_ONWY,
				      DWV_TYPE_IO_1V8_ONWY,
				      PUWW_TYPE_IO_DEFAUWT,
				      PUWW_TYPE_IO_DEFAUWT,
				      PUWW_TYPE_IO_1V8_ONWY,
				      PUWW_TYPE_IO_1V8_ONWY
				      ),
	PIN_BANK_DWV_FWAGS(3, 32, "gpio3", DWV_TYPE_IO_3V3_ONWY,
			   DWV_TYPE_IO_3V3_ONWY,
			   DWV_TYPE_IO_3V3_ONWY,
			   DWV_TYPE_IO_1V8_OW_3V0
			   ),
	PIN_BANK_DWV_FWAGS(4, 32, "gpio4", DWV_TYPE_IO_1V8_OW_3V0,
			   DWV_TYPE_IO_1V8_3V0_AUTO,
			   DWV_TYPE_IO_1V8_OW_3V0,
			   DWV_TYPE_IO_1V8_OW_3V0
			   ),
};

static stwuct wockchip_pin_ctww wk3399_pin_ctww = {
		.pin_banks		= wk3399_pin_banks,
		.nw_banks		= AWWAY_SIZE(wk3399_pin_banks),
		.wabew			= "WK3399-GPIO",
		.type			= WK3399,
		.gwf_mux_offset		= 0xe000,
		.pmu_mux_offset		= 0x0,
		.gwf_dwv_offset		= 0xe100,
		.pmu_dwv_offset		= 0x80,
		.iomux_woutes		= wk3399_mux_woute_data,
		.niomux_woutes		= AWWAY_SIZE(wk3399_mux_woute_data),
		.puww_cawc_weg		= wk3399_cawc_puww_weg_and_bit,
		.dwv_cawc_weg		= wk3399_cawc_dwv_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3568_pin_banks[] = {
	PIN_BANK_IOMUX_FWAGS(0, 32, "gpio0", IOMUX_SOUWCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOUWCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOUWCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOUWCE_PMU | IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FWAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
};

static stwuct wockchip_pin_ctww wk3568_pin_ctww = {
	.pin_banks		= wk3568_pin_banks,
	.nw_banks		= AWWAY_SIZE(wk3568_pin_banks),
	.wabew			= "WK3568-GPIO",
	.type			= WK3568,
	.gwf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.gwf_dwv_offset		= 0x0200,
	.pmu_dwv_offset		= 0x0070,
	.iomux_woutes		= wk3568_mux_woute_data,
	.niomux_woutes		= AWWAY_SIZE(wk3568_mux_woute_data),
	.puww_cawc_weg		= wk3568_cawc_puww_weg_and_bit,
	.dwv_cawc_weg		= wk3568_cawc_dwv_weg_and_bit,
	.schmitt_cawc_weg	= wk3568_cawc_schmitt_weg_and_bit,
};

static stwuct wockchip_pin_bank wk3588_pin_banks[] = {
	WK3588_PIN_BANK_FWAGS(0, 32, "gpio0",
			      IOMUX_WIDTH_4BIT, PUWW_TYPE_IO_1V8_ONWY),
	WK3588_PIN_BANK_FWAGS(1, 32, "gpio1",
			      IOMUX_WIDTH_4BIT, PUWW_TYPE_IO_1V8_ONWY),
	WK3588_PIN_BANK_FWAGS(2, 32, "gpio2",
			      IOMUX_WIDTH_4BIT, PUWW_TYPE_IO_1V8_ONWY),
	WK3588_PIN_BANK_FWAGS(3, 32, "gpio3",
			      IOMUX_WIDTH_4BIT, PUWW_TYPE_IO_1V8_ONWY),
	WK3588_PIN_BANK_FWAGS(4, 32, "gpio4",
			      IOMUX_WIDTH_4BIT, PUWW_TYPE_IO_1V8_ONWY),
};

static stwuct wockchip_pin_ctww wk3588_pin_ctww = {
	.pin_banks		= wk3588_pin_banks,
	.nw_banks		= AWWAY_SIZE(wk3588_pin_banks),
	.wabew			= "WK3588-GPIO",
	.type			= WK3588,
	.puww_cawc_weg		= wk3588_cawc_puww_weg_and_bit,
	.dwv_cawc_weg		= wk3588_cawc_dwv_weg_and_bit,
	.schmitt_cawc_weg	= wk3588_cawc_schmitt_weg_and_bit,
};

static const stwuct of_device_id wockchip_pinctww_dt_match[] = {
	{ .compatibwe = "wockchip,px30-pinctww",
		.data = &px30_pin_ctww },
	{ .compatibwe = "wockchip,wv1108-pinctww",
		.data = &wv1108_pin_ctww },
	{ .compatibwe = "wockchip,wv1126-pinctww",
		.data = &wv1126_pin_ctww },
	{ .compatibwe = "wockchip,wk2928-pinctww",
		.data = &wk2928_pin_ctww },
	{ .compatibwe = "wockchip,wk3036-pinctww",
		.data = &wk3036_pin_ctww },
	{ .compatibwe = "wockchip,wk3066a-pinctww",
		.data = &wk3066a_pin_ctww },
	{ .compatibwe = "wockchip,wk3066b-pinctww",
		.data = &wk3066b_pin_ctww },
	{ .compatibwe = "wockchip,wk3128-pinctww",
		.data = (void *)&wk3128_pin_ctww },
	{ .compatibwe = "wockchip,wk3188-pinctww",
		.data = &wk3188_pin_ctww },
	{ .compatibwe = "wockchip,wk3228-pinctww",
		.data = &wk3228_pin_ctww },
	{ .compatibwe = "wockchip,wk3288-pinctww",
		.data = &wk3288_pin_ctww },
	{ .compatibwe = "wockchip,wk3308-pinctww",
		.data = &wk3308_pin_ctww },
	{ .compatibwe = "wockchip,wk3328-pinctww",
		.data = &wk3328_pin_ctww },
	{ .compatibwe = "wockchip,wk3368-pinctww",
		.data = &wk3368_pin_ctww },
	{ .compatibwe = "wockchip,wk3399-pinctww",
		.data = &wk3399_pin_ctww },
	{ .compatibwe = "wockchip,wk3568-pinctww",
		.data = &wk3568_pin_ctww },
	{ .compatibwe = "wockchip,wk3588-pinctww",
		.data = &wk3588_pin_ctww },
	{},
};

static stwuct pwatfowm_dwivew wockchip_pinctww_dwivew = {
	.pwobe		= wockchip_pinctww_pwobe,
	.wemove_new	= wockchip_pinctww_wemove,
	.dwivew = {
		.name	= "wockchip-pinctww",
		.pm = &wockchip_pinctww_dev_pm_ops,
		.of_match_tabwe = wockchip_pinctww_dt_match,
	},
};

static int __init wockchip_pinctww_dwv_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wockchip_pinctww_dwivew);
}
postcowe_initcaww(wockchip_pinctww_dwv_wegistew);

static void __exit wockchip_pinctww_dwv_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&wockchip_pinctww_dwivew);
}
moduwe_exit(wockchip_pinctww_dwv_unwegistew);

MODUWE_DESCWIPTION("WOCKCHIP Pin Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pinctww-wockchip");
MODUWE_DEVICE_TABWE(of, wockchip_pinctww_dt_match);
