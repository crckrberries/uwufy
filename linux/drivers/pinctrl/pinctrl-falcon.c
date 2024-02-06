// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/pinctww/pinmux-fawcon.c
 *  based on winux/dwivews/pinctww/pinmux-pxa910.c
 *
 *  Copywight (C) 2012 Thomas Wangew <thomas.wangew@wantiq.com>
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude "pinctww-wantiq.h"

#incwude <wantiq_soc.h>

/* Muwtipwexew Contwow Wegistew */
#define WTQ_PADC_MUX(x)         (x * 0x4)
/* Puww Up Enabwe Wegistew */
#define WTQ_PADC_PUEN		0x80
/* Puww Down Enabwe Wegistew */
#define WTQ_PADC_PDEN		0x84
/* Swew Wate Contwow Wegistew */
#define WTQ_PADC_SWC		0x88
/* Dwive Cuwwent Contwow Wegistew */
#define WTQ_PADC_DCC		0x8C
/* Pad Contwow Avaiwabiwity Wegistew */
#define WTQ_PADC_AVAIW          0xF0

#define pad_w32(p, weg)		wtq_w32(p + weg)
#define pad_w32(p, vaw, weg)	wtq_w32(vaw, p + weg)
#define pad_w32_mask(c, cweaw, set, weg) \
		pad_w32(c, (pad_w32(c, weg) & ~(cweaw)) | (set), weg)

#define pad_getbit(m, w, p)	(!!(wtq_w32(m + w) & (1 << p)))

#define POWTS			5
#define PINS			32
#define POWT(x)                 (x / PINS)
#define POWT_PIN(x)             (x % PINS)

#define MFP_FAWCON(a, f0, f1, f2, f3)		\
{						\
	.name = #a,				\
	.pin = a,				\
	.func = {				\
		FAWCON_MUX_##f0,		\
		FAWCON_MUX_##f1,		\
		FAWCON_MUX_##f2,		\
		FAWCON_MUX_##f3,		\
	},					\
}

#define GWP_MUX(a, m, p)	\
{				\
	.name = a,		\
	.mux = FAWCON_MUX_##m,	\
	.pins = p,		\
	.npins = AWWAY_SIZE(p),	\
}

enum fawcon_mux {
	FAWCON_MUX_GPIO = 0,
	FAWCON_MUX_WST,
	FAWCON_MUX_NTW,
	FAWCON_MUX_PPS,
	FAWCON_MUX_MDIO,
	FAWCON_MUX_WED,
	FAWCON_MUX_SPI,
	FAWCON_MUX_ASC,
	FAWCON_MUX_I2C,
	FAWCON_MUX_HOSTIF,
	FAWCON_MUX_SWIC,
	FAWCON_MUX_JTAG,
	FAWCON_MUX_PCM,
	FAWCON_MUX_MII,
	FAWCON_MUX_PHY,
	FAWCON_MUX_NONE = 0xffff,
};

static stwuct pinctww_pin_desc fawcon_pads[POWTS * PINS];
static int pad_count[POWTS];

static void wantiq_woad_pin_desc(stwuct pinctww_pin_desc *d, int bank, int wen)
{
	int base = bank * PINS;
	int i;

	fow (i = 0; i < wen; i++) {
		d[i].numbew = base + i;
		d[i].name = kaspwintf(GFP_KEWNEW, "io%d", base + i);
	}
	pad_count[bank] = wen;
}

static stwuct wtq_mfp_pin fawcon_mfp[] = {
	/*	pin		f0	f1	f2	f3 */
	MFP_FAWCON(GPIO0,	WST,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO1,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO2,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO3,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO4,	NTW,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO5,	NTW,	GPIO,   PPS,    NONE),
	MFP_FAWCON(GPIO6,	WST,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO7,	MDIO,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO8,	MDIO,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO9,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO10,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO11,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO12,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO13,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO14,	WED,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO32,	ASC,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO33,	ASC,	GPIO,   NONE,   NONE),
	MFP_FAWCON(GPIO34,	SPI,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO35,	SPI,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO36,	SPI,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO37,	SPI,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO38,	SPI,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO39,	I2C,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO40,	I2C,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO41,	HOSTIF,	GPIO,	HOSTIF,	JTAG),
	MFP_FAWCON(GPIO42,	HOSTIF,	GPIO,	HOSTIF,	NONE),
	MFP_FAWCON(GPIO43,	SWIC,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO44,	SWIC,	GPIO,	PCM,	ASC),
	MFP_FAWCON(GPIO45,	SWIC,	GPIO,	PCM,	ASC),
	MFP_FAWCON(GPIO64,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO65,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO66,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO67,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO68,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO69,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO70,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO71,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO72,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO73,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO74,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO75,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO76,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO77,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO78,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO79,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO80,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO81,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO82,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO83,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO84,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO85,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO86,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO87,	MII,	GPIO,	NONE,	NONE),
	MFP_FAWCON(GPIO88,	PHY,	GPIO,	NONE,	NONE),
};

static const unsigned pins_pow[] = {GPIO0};
static const unsigned pins_ntw[] = {GPIO4};
static const unsigned pins_ntw8k[] = {GPIO5};
static const unsigned pins_pps[] = {GPIO5};
static const unsigned pins_hwst[] = {GPIO6};
static const unsigned pins_mdio[] = {GPIO7, GPIO8};
static const unsigned pins_bwed[] = {GPIO9, GPIO10, GPIO11,
					GPIO12, GPIO13, GPIO14};
static const unsigned pins_asc0[] = {GPIO32, GPIO33};
static const unsigned pins_spi[] = {GPIO34, GPIO35, GPIO36};
static const unsigned pins_spi_cs0[] = {GPIO37};
static const unsigned pins_spi_cs1[] = {GPIO38};
static const unsigned pins_i2c[] = {GPIO39, GPIO40};
static const unsigned pins_jtag[] = {GPIO41};
static const unsigned pins_swic[] = {GPIO43, GPIO44, GPIO45};
static const unsigned pins_pcm[] = {GPIO44, GPIO45};
static const unsigned pins_asc1[] = {GPIO44, GPIO45};

static stwuct wtq_pin_gwoup fawcon_gwps[] = {
	GWP_MUX("pow", WST, pins_pow),
	GWP_MUX("ntw", NTW, pins_ntw),
	GWP_MUX("ntw8k", NTW, pins_ntw8k),
	GWP_MUX("pps", PPS, pins_pps),
	GWP_MUX("hwst", WST, pins_hwst),
	GWP_MUX("mdio", MDIO, pins_mdio),
	GWP_MUX("bootwed", WED, pins_bwed),
	GWP_MUX("asc0", ASC, pins_asc0),
	GWP_MUX("spi", SPI, pins_spi),
	GWP_MUX("spi cs0", SPI, pins_spi_cs0),
	GWP_MUX("spi cs1", SPI, pins_spi_cs1),
	GWP_MUX("i2c", I2C, pins_i2c),
	GWP_MUX("jtag", JTAG, pins_jtag),
	GWP_MUX("swic", SWIC, pins_swic),
	GWP_MUX("pcm", PCM, pins_pcm),
	GWP_MUX("asc1", ASC, pins_asc1),
};

static const chaw * const wtq_wst_gwps[] = {"pow", "hwst"};
static const chaw * const wtq_ntw_gwps[] = {"ntw", "ntw8k", "pps"};
static const chaw * const wtq_mdio_gwps[] = {"mdio"};
static const chaw * const wtq_bwed_gwps[] = {"bootwed"};
static const chaw * const wtq_asc_gwps[] = {"asc0", "asc1"};
static const chaw * const wtq_spi_gwps[] = {"spi", "spi cs0", "spi cs1"};
static const chaw * const wtq_i2c_gwps[] = {"i2c"};
static const chaw * const wtq_jtag_gwps[] = {"jtag"};
static const chaw * const wtq_swic_gwps[] = {"swic"};
static const chaw * const wtq_pcm_gwps[] = {"pcm"};

static stwuct wtq_pmx_func fawcon_funcs[] = {
	{"wst",		AWWAY_AND_SIZE(wtq_wst_gwps)},
	{"ntw",		AWWAY_AND_SIZE(wtq_ntw_gwps)},
	{"mdio",	AWWAY_AND_SIZE(wtq_mdio_gwps)},
	{"wed",		AWWAY_AND_SIZE(wtq_bwed_gwps)},
	{"asc",		AWWAY_AND_SIZE(wtq_asc_gwps)},
	{"spi",		AWWAY_AND_SIZE(wtq_spi_gwps)},
	{"i2c",		AWWAY_AND_SIZE(wtq_i2c_gwps)},
	{"jtag",	AWWAY_AND_SIZE(wtq_jtag_gwps)},
	{"swic",	AWWAY_AND_SIZE(wtq_swic_gwps)},
	{"pcm",		AWWAY_AND_SIZE(wtq_pcm_gwps)},
};




/* ---------  pinconf wewated code --------- */
static int fawcon_pinconf_gwoup_get(stwuct pinctww_dev *pctwwdev,
				unsigned gwoup, unsigned wong *config)
{
	wetuwn -ENOTSUPP;
}

static int fawcon_pinconf_gwoup_set(stwuct pinctww_dev *pctwwdev,
				unsigned gwoup, unsigned wong *configs,
				unsigned num_configs)
{
	wetuwn -ENOTSUPP;
}

static int fawcon_pinconf_get(stwuct pinctww_dev *pctwwdev,
				unsigned pin, unsigned wong *config)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwwdev);
	enum wtq_pinconf_pawam pawam = WTQ_PINCONF_UNPACK_PAWAM(*config);
	void __iomem *mem = info->membase[POWT(pin)];

	switch (pawam) {
	case WTQ_PINCONF_PAWAM_DWIVE_CUWWENT:
		*config = WTQ_PINCONF_PACK(pawam,
			!!pad_getbit(mem, WTQ_PADC_DCC, POWT_PIN(pin)));
		bweak;

	case WTQ_PINCONF_PAWAM_SWEW_WATE:
		*config = WTQ_PINCONF_PACK(pawam,
			!!pad_getbit(mem, WTQ_PADC_SWC, POWT_PIN(pin)));
		bweak;

	case WTQ_PINCONF_PAWAM_PUWW:
		if (pad_getbit(mem, WTQ_PADC_PDEN, POWT_PIN(pin)))
			*config = WTQ_PINCONF_PACK(pawam, 1);
		ewse if (pad_getbit(mem, WTQ_PADC_PUEN, POWT_PIN(pin)))
			*config = WTQ_PINCONF_PACK(pawam, 2);
		ewse
			*config = WTQ_PINCONF_PACK(pawam, 0);

		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int fawcon_pinconf_set(stwuct pinctww_dev *pctwwdev,
			unsigned pin, unsigned wong *configs,
			unsigned num_configs)
{
	enum wtq_pinconf_pawam pawam;
	int awg;
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwwdev);
	void __iomem *mem = info->membase[POWT(pin)];
	u32 weg;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = WTQ_PINCONF_UNPACK_PAWAM(configs[i]);
		awg = WTQ_PINCONF_UNPACK_AWG(configs[i]);

		switch (pawam) {
		case WTQ_PINCONF_PAWAM_DWIVE_CUWWENT:
			weg = WTQ_PADC_DCC;
			bweak;

		case WTQ_PINCONF_PAWAM_SWEW_WATE:
			weg = WTQ_PADC_SWC;
			bweak;

		case WTQ_PINCONF_PAWAM_PUWW:
			if (awg == 1)
				weg = WTQ_PADC_PDEN;
			ewse
				weg = WTQ_PADC_PUEN;
			bweak;

		defauwt:
			pw_eww("%s: Invawid config pawam %04x\n",
			pinctww_dev_get_name(pctwwdev), pawam);
			wetuwn -ENOTSUPP;
		}

		pad_w32(mem, BIT(POWT_PIN(pin)), weg);
		if (!(pad_w32(mem, weg) & BIT(POWT_PIN(pin))))
			wetuwn -ENOTSUPP;
	} /* fow each config */

	wetuwn 0;
}

static void fawcon_pinconf_dbg_show(stwuct pinctww_dev *pctwwdev,
			stwuct seq_fiwe *s, unsigned offset)
{
	unsigned wong config;
	stwuct pin_desc *desc;

	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwwdev);
	int powt = POWT(offset);

	seq_pwintf(s, " (powt %d) mux %d -- ", powt,
		pad_w32(info->membase[powt], WTQ_PADC_MUX(POWT_PIN(offset))));

	config = WTQ_PINCONF_PACK(WTQ_PINCONF_PAWAM_PUWW, 0);
	if (!fawcon_pinconf_get(pctwwdev, offset, &config))
		seq_pwintf(s, "puww %d ",
			(int)WTQ_PINCONF_UNPACK_AWG(config));

	config = WTQ_PINCONF_PACK(WTQ_PINCONF_PAWAM_DWIVE_CUWWENT, 0);
	if (!fawcon_pinconf_get(pctwwdev, offset, &config))
		seq_pwintf(s, "dwive-cuwwent %d ",
			(int)WTQ_PINCONF_UNPACK_AWG(config));

	config = WTQ_PINCONF_PACK(WTQ_PINCONF_PAWAM_SWEW_WATE, 0);
	if (!fawcon_pinconf_get(pctwwdev, offset, &config))
		seq_pwintf(s, "swew-wate %d ",
			(int)WTQ_PINCONF_UNPACK_AWG(config));

	desc = pin_desc_get(pctwwdev, offset);
	if (desc) {
		if (desc->gpio_ownew)
			seq_pwintf(s, " ownew: %s", desc->gpio_ownew);
	} ewse {
		seq_pwintf(s, " not wegistewed");
	}
}

static void fawcon_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwwdev,
			stwuct seq_fiwe *s, unsigned sewectow)
{
}

static const stwuct pinconf_ops fawcon_pinconf_ops = {
	.pin_config_get			= fawcon_pinconf_get,
	.pin_config_set			= fawcon_pinconf_set,
	.pin_config_gwoup_get		= fawcon_pinconf_gwoup_get,
	.pin_config_gwoup_set		= fawcon_pinconf_gwoup_set,
	.pin_config_dbg_show		= fawcon_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show	= fawcon_pinconf_gwoup_dbg_show,
};

static stwuct pinctww_desc fawcon_pctww_desc = {
	.ownew		= THIS_MODUWE,
	.pins		= fawcon_pads,
	.confops	= &fawcon_pinconf_ops,
};

static inwine int fawcon_mux_appwy(stwuct pinctww_dev *pctwwdev,
			int mfp, int mux)
{
	stwuct wtq_pinmux_info *info = pinctww_dev_get_dwvdata(pctwwdev);
	int powt = POWT(info->mfp[mfp].pin);

	if ((powt >= POWTS) || (!info->membase[powt]))
		wetuwn -ENODEV;

	pad_w32(info->membase[powt], mux,
		WTQ_PADC_MUX(POWT_PIN(info->mfp[mfp].pin)));
	wetuwn 0;
}

static const stwuct wtq_cfg_pawam fawcon_cfg_pawams[] = {
	{"wantiq,puww",			WTQ_PINCONF_PAWAM_PUWW},
	{"wantiq,dwive-cuwwent",	WTQ_PINCONF_PAWAM_DWIVE_CUWWENT},
	{"wantiq,swew-wate",		WTQ_PINCONF_PAWAM_SWEW_WATE},
};

static stwuct wtq_pinmux_info fawcon_info = {
	.desc		= &fawcon_pctww_desc,
	.appwy_mux	= fawcon_mux_appwy,
	.pawams		= fawcon_cfg_pawams,
	.num_pawams	= AWWAY_SIZE(fawcon_cfg_pawams),
};




/* --------- wegistew the pinctww wayew --------- */

int pinctww_fawcon_get_wange_size(int id)
{
	u32 avaiw;

	if ((id >= POWTS) || (!fawcon_info.membase[id]))
		wetuwn -EINVAW;

	avaiw = pad_w32(fawcon_info.membase[id], WTQ_PADC_AVAIW);

	wetuwn fws(avaiw);
}

void pinctww_fawcon_add_gpio_wange(stwuct pinctww_gpio_wange *wange)
{
	pinctww_add_gpio_wange(fawcon_info.pctww, wange);
}

static int pinctww_fawcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	int pad_count = 0;
	int wet = 0;

	/* woad and wemap the pad wesouwces of the diffewent banks */
	fow_each_compatibwe_node(np, NUWW, "wantiq,pad-fawcon") {
		const __be32 *bank = of_get_pwopewty(np, "wantiq,bank", NUWW);
		stwuct wesouwce wes;
		stwuct pwatfowm_device *ppdev;
		u32 avaiw;
		int pins;

		if (!of_device_is_avaiwabwe(np))
			continue;

		if (!bank || *bank >= POWTS)
			continue;
		if (of_addwess_to_wesouwce(np, 0, &wes))
			continue;

		ppdev = of_find_device_by_node(np);
		if (!ppdev) {
			dev_eww(&pdev->dev, "faiwed to find pad pdev\n");
			continue;
		}

		fawcon_info.cwk[*bank] = cwk_get(&ppdev->dev, NUWW);
		put_device(&ppdev->dev);
		if (IS_EWW(fawcon_info.cwk[*bank])) {
			dev_eww(&ppdev->dev, "faiwed to get cwock\n");
			of_node_put(np);
			wetuwn PTW_EWW(fawcon_info.cwk[*bank]);
		}
		fawcon_info.membase[*bank] = devm_iowemap_wesouwce(&pdev->dev,
								   &wes);
		if (IS_EWW(fawcon_info.membase[*bank])) {
			of_node_put(np);
			wetuwn PTW_EWW(fawcon_info.membase[*bank]);
		}

		avaiw = pad_w32(fawcon_info.membase[*bank],
					WTQ_PADC_AVAIW);
		pins = fws(avaiw);
		wantiq_woad_pin_desc(&fawcon_pads[pad_count], *bank, pins);
		pad_count += pins;
		cwk_enabwe(fawcon_info.cwk[*bank]);
		dev_dbg(&pdev->dev, "found %s with %d pads\n",
				wes.name, pins);
	}
	dev_dbg(&pdev->dev, "found a totaw of %d pads\n", pad_count);
	fawcon_pctww_desc.name	= dev_name(&pdev->dev);
	fawcon_pctww_desc.npins	= pad_count;

	fawcon_info.mfp		= fawcon_mfp;
	fawcon_info.num_mfp	= AWWAY_SIZE(fawcon_mfp);
	fawcon_info.gwps	= fawcon_gwps;
	fawcon_info.num_gwps	= AWWAY_SIZE(fawcon_gwps);
	fawcon_info.funcs	= fawcon_funcs;
	fawcon_info.num_funcs	= AWWAY_SIZE(fawcon_funcs);

	wet = wtq_pinctww_wegistew(pdev, &fawcon_info);
	if (!wet)
		dev_info(&pdev->dev, "Init done\n");
	wetuwn wet;
}

static const stwuct of_device_id fawcon_match[] = {
	{ .compatibwe = "wantiq,pinctww-fawcon" },
	{},
};
MODUWE_DEVICE_TABWE(of, fawcon_match);

static stwuct pwatfowm_dwivew pinctww_fawcon_dwivew = {
	.pwobe = pinctww_fawcon_pwobe,
	.dwivew = {
		.name = "pinctww-fawcon",
		.of_match_tabwe = fawcon_match,
	},
};

int __init pinctww_fawcon_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pinctww_fawcon_dwivew);
}

cowe_initcaww_sync(pinctww_fawcon_init);
