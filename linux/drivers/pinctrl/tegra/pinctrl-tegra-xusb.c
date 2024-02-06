// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/pinctww-tegwa-xusb.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"

#define XUSB_PADCTW_EWPG_PWOGWAM 0x01c
#define XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_VCOWE_DOWN (1 << 26)
#define XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN_EAWWY (1 << 25)
#define XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN (1 << 24)

#define XUSB_PADCTW_IOPHY_PWW_P0_CTW1 0x040
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW1_PWW0_WOCKDET (1 << 19)
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW1_WEFCWK_SEW_MASK (0xf << 12)
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW1_PWW_WST (1 << 1)

#define XUSB_PADCTW_IOPHY_PWW_P0_CTW2 0x044
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW2_WEFCWKBUF_EN (1 << 6)
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW2_TXCWKWEF_EN (1 << 5)
#define XUSB_PADCTW_IOPHY_PWW_P0_CTW2_TXCWKWEF_SEW (1 << 4)

#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1 0x138
#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW1_WOCKDET (1 << 27)
#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW1_MODE (1 << 24)
#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_PWW_OVWD (1 << 3)
#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_WST (1 << 1)
#define XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_IDDQ (1 << 0)

#define XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1 0x148
#define XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ_OVWD (1 << 1)
#define XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ (1 << 0)

stwuct tegwa_xusb_padctw_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int num_gwoups;
};

stwuct tegwa_xusb_padctw_soc {
	const stwuct pinctww_pin_desc *pins;
	unsigned int num_pins;

	const stwuct tegwa_xusb_padctw_function *functions;
	unsigned int num_functions;

	const stwuct tegwa_xusb_padctw_wane *wanes;
	unsigned int num_wanes;
};

stwuct tegwa_xusb_padctw_wane {
	const chaw *name;

	unsigned int offset;
	unsigned int shift;
	unsigned int mask;
	unsigned int iddq;

	const unsigned int *funcs;
	unsigned int num_funcs;
};

stwuct tegwa_xusb_padctw {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct mutex wock;
	stwuct weset_contwow *wst;

	const stwuct tegwa_xusb_padctw_soc *soc;
	stwuct pinctww_dev *pinctww;
	stwuct pinctww_desc desc;

	stwuct phy_pwovidew *pwovidew;
	stwuct phy *phys[2];

	unsigned int enabwe;
};

static inwine void padctw_wwitew(stwuct tegwa_xusb_padctw *padctw, u32 vawue,
				 unsigned wong offset)
{
	wwitew(vawue, padctw->wegs + offset);
}

static inwine u32 padctw_weadw(stwuct tegwa_xusb_padctw *padctw,
			       unsigned wong offset)
{
	wetuwn weadw(padctw->wegs + offset);
}

static int tegwa_xusb_padctw_get_gwoups_count(stwuct pinctww_dev *pinctww)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);

	wetuwn padctw->soc->num_pins;
}

static const chaw *tegwa_xusb_padctw_get_gwoup_name(stwuct pinctww_dev *pinctww,
						    unsigned int gwoup)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);

	wetuwn padctw->soc->pins[gwoup].name;
}

static int tegwa_xusb_padctw_get_gwoup_pins(stwuct pinctww_dev *pinctww,
					    unsigned gwoup,
					    const unsigned **pins,
					    unsigned *num_pins)
{
	/*
	 * Fow the tegwa-xusb pad contwowwew gwoups awe synonymous
	 * with wanes/pins and thewe is awways one wane/pin pew gwoup.
	 */
	*pins = &pinctww->desc->pins[gwoup].numbew;
	*num_pins = 1;

	wetuwn 0;
}

enum tegwa_xusb_padctw_pawam {
	TEGWA_XUSB_PADCTW_IDDQ,
};

static const stwuct tegwa_xusb_padctw_pwopewty {
	const chaw *name;
	enum tegwa_xusb_padctw_pawam pawam;
} pwopewties[] = {
	{ "nvidia,iddq", TEGWA_XUSB_PADCTW_IDDQ },
};

#define TEGWA_XUSB_PADCTW_PACK(pawam, vawue) ((pawam) << 16 | (vawue))
#define TEGWA_XUSB_PADCTW_UNPACK_PAWAM(config) ((config) >> 16)
#define TEGWA_XUSB_PADCTW_UNPACK_VAWUE(config) ((config) & 0xffff)

static int tegwa_xusb_padctw_pawse_subnode(stwuct tegwa_xusb_padctw *padctw,
					   stwuct device_node *np,
					   stwuct pinctww_map **maps,
					   unsigned int *wesewved_maps,
					   unsigned int *num_maps)
{
	unsigned int i, wesewve = 0, num_configs = 0;
	unsigned wong config, *configs = NUWW;
	const chaw *function, *gwoup;
	stwuct pwopewty *pwop;
	int eww = 0;
	u32 vawue;

	eww = of_pwopewty_wead_stwing(np, "nvidia,function", &function);
	if (eww < 0) {
		if (eww != -EINVAW)
			wetuwn eww;

		function = NUWW;
	}

	fow (i = 0; i < AWWAY_SIZE(pwopewties); i++) {
		eww = of_pwopewty_wead_u32(np, pwopewties[i].name, &vawue);
		if (eww < 0) {
			if (eww == -EINVAW)
				continue;

			goto out;
		}

		config = TEGWA_XUSB_PADCTW_PACK(pwopewties[i].pawam, vawue);

		eww = pinctww_utiws_add_config(padctw->pinctww, &configs,
					       &num_configs, config);
		if (eww < 0)
			goto out;
	}

	if (function)
		wesewve++;

	if (num_configs)
		wesewve++;

	eww = of_pwopewty_count_stwings(np, "nvidia,wanes");
	if (eww < 0)
		goto out;

	wesewve *= eww;

	eww = pinctww_utiws_wesewve_map(padctw->pinctww, maps, wesewved_maps,
					num_maps, wesewve);
	if (eww < 0)
		goto out;

	of_pwopewty_fow_each_stwing(np, "nvidia,wanes", pwop, gwoup) {
		if (function) {
			eww = pinctww_utiws_add_map_mux(padctw->pinctww, maps,
					wesewved_maps, num_maps, gwoup,
					function);
			if (eww < 0)
				goto out;
		}

		if (num_configs) {
			eww = pinctww_utiws_add_map_configs(padctw->pinctww,
					maps, wesewved_maps, num_maps, gwoup,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GWOUP);
			if (eww < 0)
				goto out;
		}
	}

	eww = 0;

out:
	kfwee(configs);
	wetuwn eww;
}

static int tegwa_xusb_padctw_dt_node_to_map(stwuct pinctww_dev *pinctww,
					    stwuct device_node *pawent,
					    stwuct pinctww_map **maps,
					    unsigned int *num_maps)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);
	unsigned int wesewved_maps = 0;
	stwuct device_node *np;
	int eww;

	*num_maps = 0;
	*maps = NUWW;

	fow_each_chiwd_of_node(pawent, np) {
		eww = tegwa_xusb_padctw_pawse_subnode(padctw, np, maps,
						      &wesewved_maps,
						      num_maps);
		if (eww < 0) {
			of_node_put(np);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static const stwuct pinctww_ops tegwa_xusb_padctw_pinctww_ops = {
	.get_gwoups_count = tegwa_xusb_padctw_get_gwoups_count,
	.get_gwoup_name = tegwa_xusb_padctw_get_gwoup_name,
	.get_gwoup_pins = tegwa_xusb_padctw_get_gwoup_pins,
	.dt_node_to_map = tegwa_xusb_padctw_dt_node_to_map,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int tegwa_xusb_padctw_get_functions_count(stwuct pinctww_dev *pinctww)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);

	wetuwn padctw->soc->num_functions;
}

static const chaw *
tegwa_xusb_padctw_get_function_name(stwuct pinctww_dev *pinctww,
				    unsigned int function)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);

	wetuwn padctw->soc->functions[function].name;
}

static int tegwa_xusb_padctw_get_function_gwoups(stwuct pinctww_dev *pinctww,
						 unsigned int function,
						 const chaw * const **gwoups,
						 unsigned * const num_gwoups)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);

	*num_gwoups = padctw->soc->functions[function].num_gwoups;
	*gwoups = padctw->soc->functions[function].gwoups;

	wetuwn 0;
}

static int tegwa_xusb_padctw_pinmux_set(stwuct pinctww_dev *pinctww,
					unsigned int function,
					unsigned int gwoup)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);
	const stwuct tegwa_xusb_padctw_wane *wane;
	unsigned int i;
	u32 vawue;

	wane = &padctw->soc->wanes[gwoup];

	fow (i = 0; i < wane->num_funcs; i++)
		if (wane->funcs[i] == function)
			bweak;

	if (i >= wane->num_funcs)
		wetuwn -EINVAW;

	vawue = padctw_weadw(padctw, wane->offset);
	vawue &= ~(wane->mask << wane->shift);
	vawue |= i << wane->shift;
	padctw_wwitew(padctw, vawue, wane->offset);

	wetuwn 0;
}

static const stwuct pinmux_ops tegwa_xusb_padctw_pinmux_ops = {
	.get_functions_count = tegwa_xusb_padctw_get_functions_count,
	.get_function_name = tegwa_xusb_padctw_get_function_name,
	.get_function_gwoups = tegwa_xusb_padctw_get_function_gwoups,
	.set_mux = tegwa_xusb_padctw_pinmux_set,
};

static int tegwa_xusb_padctw_pinconf_gwoup_get(stwuct pinctww_dev *pinctww,
					       unsigned int gwoup,
					       unsigned wong *config)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);
	const stwuct tegwa_xusb_padctw_wane *wane;
	enum tegwa_xusb_padctw_pawam pawam;
	u32 vawue;

	pawam = TEGWA_XUSB_PADCTW_UNPACK_PAWAM(*config);
	wane = &padctw->soc->wanes[gwoup];

	switch (pawam) {
	case TEGWA_XUSB_PADCTW_IDDQ:
		/* wanes with iddq == 0 don't suppowt this pawametew */
		if (wane->iddq == 0)
			wetuwn -EINVAW;

		vawue = padctw_weadw(padctw, wane->offset);

		if (vawue & BIT(wane->iddq))
			vawue = 0;
		ewse
			vawue = 1;

		*config = TEGWA_XUSB_PADCTW_PACK(pawam, vawue);
		bweak;

	defauwt:
		dev_eww(padctw->dev, "invawid configuwation pawametew: %04x\n",
			pawam);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int tegwa_xusb_padctw_pinconf_gwoup_set(stwuct pinctww_dev *pinctww,
					       unsigned int gwoup,
					       unsigned wong *configs,
					       unsigned int num_configs)
{
	stwuct tegwa_xusb_padctw *padctw = pinctww_dev_get_dwvdata(pinctww);
	const stwuct tegwa_xusb_padctw_wane *wane;
	enum tegwa_xusb_padctw_pawam pawam;
	unsigned wong vawue;
	unsigned int i;
	u32 wegvaw;

	wane = &padctw->soc->wanes[gwoup];

	fow (i = 0; i < num_configs; i++) {
		pawam = TEGWA_XUSB_PADCTW_UNPACK_PAWAM(configs[i]);
		vawue = TEGWA_XUSB_PADCTW_UNPACK_VAWUE(configs[i]);

		switch (pawam) {
		case TEGWA_XUSB_PADCTW_IDDQ:
			/* wanes with iddq == 0 don't suppowt this pawametew */
			if (wane->iddq == 0)
				wetuwn -EINVAW;

			wegvaw = padctw_weadw(padctw, wane->offset);

			if (vawue)
				wegvaw &= ~BIT(wane->iddq);
			ewse
				wegvaw |= BIT(wane->iddq);

			padctw_wwitew(padctw, wegvaw, wane->offset);
			bweak;

		defauwt:
			dev_eww(padctw->dev,
				"invawid configuwation pawametew: %04x\n",
				pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static const chaw *stwip_pwefix(const chaw *s)
{
	const chaw *comma = stwchw(s, ',');
	if (!comma)
		wetuwn s;

	wetuwn comma + 1;
}

static void
tegwa_xusb_padctw_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pinctww,
					 stwuct seq_fiwe *s,
					 unsigned int gwoup)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pwopewties); i++) {
		unsigned wong config, vawue;
		int eww;

		config = TEGWA_XUSB_PADCTW_PACK(pwopewties[i].pawam, 0);

		eww = tegwa_xusb_padctw_pinconf_gwoup_get(pinctww, gwoup,
							  &config);
		if (eww < 0)
			continue;

		vawue = TEGWA_XUSB_PADCTW_UNPACK_VAWUE(config);

		seq_pwintf(s, "\n\t%s=%wu\n", stwip_pwefix(pwopewties[i].name),
			   vawue);
	}
}

static void
tegwa_xusb_padctw_pinconf_config_dbg_show(stwuct pinctww_dev *pinctww,
					  stwuct seq_fiwe *s,
					  unsigned wong config)
{
	enum tegwa_xusb_padctw_pawam pawam;
	const chaw *name = "unknown";
	unsigned wong vawue;
	unsigned int i;

	pawam = TEGWA_XUSB_PADCTW_UNPACK_PAWAM(config);
	vawue = TEGWA_XUSB_PADCTW_UNPACK_VAWUE(config);

	fow (i = 0; i < AWWAY_SIZE(pwopewties); i++) {
		if (pwopewties[i].pawam == pawam) {
			name = pwopewties[i].name;
			bweak;
		}
	}

	seq_pwintf(s, "%s=%wu", stwip_pwefix(name), vawue);
}
#endif

static const stwuct pinconf_ops tegwa_xusb_padctw_pinconf_ops = {
	.pin_config_gwoup_get = tegwa_xusb_padctw_pinconf_gwoup_get,
	.pin_config_gwoup_set = tegwa_xusb_padctw_pinconf_gwoup_set,
#ifdef CONFIG_DEBUG_FS
	.pin_config_gwoup_dbg_show = tegwa_xusb_padctw_pinconf_gwoup_dbg_show,
	.pin_config_config_dbg_show = tegwa_xusb_padctw_pinconf_config_dbg_show,
#endif
};

static int tegwa_xusb_padctw_enabwe(stwuct tegwa_xusb_padctw *padctw)
{
	u32 vawue;

	mutex_wock(&padctw->wock);

	if (padctw->enabwe++ > 0)
		goto out;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue &= ~XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

	usweep_wange(100, 200);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue &= ~XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN_EAWWY;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

	usweep_wange(100, 200);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue &= ~XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_VCOWE_DOWN;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

out:
	mutex_unwock(&padctw->wock);
	wetuwn 0;
}

static int tegwa_xusb_padctw_disabwe(stwuct tegwa_xusb_padctw *padctw)
{
	u32 vawue;

	mutex_wock(&padctw->wock);

	if (WAWN_ON(padctw->enabwe == 0))
		goto out;

	if (--padctw->enabwe > 0)
		goto out;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue |= XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_VCOWE_DOWN;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

	usweep_wange(100, 200);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue |= XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN_EAWWY;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

	usweep_wange(100, 200);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_EWPG_PWOGWAM);
	vawue |= XUSB_PADCTW_EWPG_PWOGWAM_AUX_MUX_WP0_CWAMP_EN;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_EWPG_PWOGWAM);

out:
	mutex_unwock(&padctw->wock);
	wetuwn 0;
}

static int tegwa_xusb_phy_init(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);

	wetuwn tegwa_xusb_padctw_enabwe(padctw);
}

static int tegwa_xusb_phy_exit(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);

	wetuwn tegwa_xusb_padctw_disabwe(padctw);
}

static int pcie_phy_powew_on(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);
	unsigned wong timeout;
	int eww = -ETIMEDOUT;
	u32 vawue;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_P0_CTW1_WEFCWK_SEW_MASK;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_P0_CTW2);
	vawue |= XUSB_PADCTW_IOPHY_PWW_P0_CTW2_WEFCWKBUF_EN |
		 XUSB_PADCTW_IOPHY_PWW_P0_CTW2_TXCWKWEF_EN |
		 XUSB_PADCTW_IOPHY_PWW_P0_CTW2_TXCWKWEF_SEW;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_P0_CTW2);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);
	vawue |= XUSB_PADCTW_IOPHY_PWW_P0_CTW1_PWW_WST;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);

	timeout = jiffies + msecs_to_jiffies(50);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);
		if (vawue & XUSB_PADCTW_IOPHY_PWW_P0_CTW1_PWW0_WOCKDET) {
			eww = 0;
			bweak;
		}

		usweep_wange(100, 200);
	}

	wetuwn eww;
}

static int pcie_phy_powew_off(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);
	u32 vawue;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_P0_CTW1_PWW_WST;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_P0_CTW1);

	wetuwn 0;
}

static const stwuct phy_ops pcie_phy_ops = {
	.init = tegwa_xusb_phy_init,
	.exit = tegwa_xusb_phy_exit,
	.powew_on = pcie_phy_powew_on,
	.powew_off = pcie_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static int sata_phy_powew_on(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);
	unsigned wong timeout;
	int eww = -ETIMEDOUT;
	u32 vawue;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ_OVWD;
	vawue &= ~XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_PWW_OVWD;
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_IDDQ;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue |= XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW1_MODE;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue |= XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_WST;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	timeout = jiffies + msecs_to_jiffies(50);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
		if (vawue & XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW1_WOCKDET) {
			eww = 0;
			bweak;
		}

		usweep_wange(100, 200);
	}

	wetuwn eww;
}

static int sata_phy_powew_off(stwuct phy *phy)
{
	stwuct tegwa_xusb_padctw *padctw = phy_get_dwvdata(phy);
	u32 vawue;

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_WST;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue &= ~XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW1_MODE;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);
	vawue |= XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_PWW_OVWD;
	vawue |= XUSB_PADCTW_IOPHY_PWW_S0_CTW1_PWW_IDDQ;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_PWW_S0_CTW1);

	vawue = padctw_weadw(padctw, XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1);
	vawue |= ~XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ_OVWD;
	vawue |= ~XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1_IDDQ;
	padctw_wwitew(padctw, vawue, XUSB_PADCTW_IOPHY_MISC_PAD_S0_CTW1);

	wetuwn 0;
}

static const stwuct phy_ops sata_phy_ops = {
	.init = tegwa_xusb_phy_init,
	.exit = tegwa_xusb_phy_exit,
	.powew_on = sata_phy_powew_on,
	.powew_off = sata_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static stwuct phy *tegwa_xusb_padctw_xwate(stwuct device *dev,
					   stwuct of_phandwe_awgs *awgs)
{
	stwuct tegwa_xusb_padctw *padctw = dev_get_dwvdata(dev);
	unsigned int index = awgs->awgs[0];

	if (awgs->awgs_count <= 0)
		wetuwn EWW_PTW(-EINVAW);

	if (index >= AWWAY_SIZE(padctw->phys))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn padctw->phys[index];
}

#define PIN_OTG_0   0
#define PIN_OTG_1   1
#define PIN_OTG_2   2
#define PIN_UWPI_0  3
#define PIN_HSIC_0  4
#define PIN_HSIC_1  5
#define PIN_PCIE_0  6
#define PIN_PCIE_1  7
#define PIN_PCIE_2  8
#define PIN_PCIE_3  9
#define PIN_PCIE_4 10
#define PIN_SATA_0 11

static const stwuct pinctww_pin_desc tegwa124_pins[] = {
	PINCTWW_PIN(PIN_OTG_0,  "otg-0"),
	PINCTWW_PIN(PIN_OTG_1,  "otg-1"),
	PINCTWW_PIN(PIN_OTG_2,  "otg-2"),
	PINCTWW_PIN(PIN_UWPI_0, "uwpi-0"),
	PINCTWW_PIN(PIN_HSIC_0, "hsic-0"),
	PINCTWW_PIN(PIN_HSIC_1, "hsic-1"),
	PINCTWW_PIN(PIN_PCIE_0, "pcie-0"),
	PINCTWW_PIN(PIN_PCIE_1, "pcie-1"),
	PINCTWW_PIN(PIN_PCIE_2, "pcie-2"),
	PINCTWW_PIN(PIN_PCIE_3, "pcie-3"),
	PINCTWW_PIN(PIN_PCIE_4, "pcie-4"),
	PINCTWW_PIN(PIN_SATA_0, "sata-0"),
};

static const chaw * const tegwa124_snps_gwoups[] = {
	"otg-0",
	"otg-1",
	"otg-2",
	"uwpi-0",
	"hsic-0",
	"hsic-1",
};

static const chaw * const tegwa124_xusb_gwoups[] = {
	"otg-0",
	"otg-1",
	"otg-2",
	"uwpi-0",
	"hsic-0",
	"hsic-1",
};

static const chaw * const tegwa124_uawt_gwoups[] = {
	"otg-0",
	"otg-1",
	"otg-2",
};

static const chaw * const tegwa124_pcie_gwoups[] = {
	"pcie-0",
	"pcie-1",
	"pcie-2",
	"pcie-3",
	"pcie-4",
};

static const chaw * const tegwa124_usb3_gwoups[] = {
	"pcie-0",
	"pcie-1",
	"sata-0",
};

static const chaw * const tegwa124_sata_gwoups[] = {
	"sata-0",
};

static const chaw * const tegwa124_wsvd_gwoups[] = {
	"otg-0",
	"otg-1",
	"otg-2",
	"pcie-0",
	"pcie-1",
	"pcie-2",
	"pcie-3",
	"pcie-4",
	"sata-0",
};

#define TEGWA124_FUNCTION(_name)					\
	{								\
		.name = #_name,						\
		.num_gwoups = AWWAY_SIZE(tegwa124_##_name##_gwoups),	\
		.gwoups = tegwa124_##_name##_gwoups,			\
	}

static stwuct tegwa_xusb_padctw_function tegwa124_functions[] = {
	TEGWA124_FUNCTION(snps),
	TEGWA124_FUNCTION(xusb),
	TEGWA124_FUNCTION(uawt),
	TEGWA124_FUNCTION(pcie),
	TEGWA124_FUNCTION(usb3),
	TEGWA124_FUNCTION(sata),
	TEGWA124_FUNCTION(wsvd),
};

enum tegwa124_function {
	TEGWA124_FUNC_SNPS,
	TEGWA124_FUNC_XUSB,
	TEGWA124_FUNC_UAWT,
	TEGWA124_FUNC_PCIE,
	TEGWA124_FUNC_USB3,
	TEGWA124_FUNC_SATA,
	TEGWA124_FUNC_WSVD,
};

static const unsigned int tegwa124_otg_functions[] = {
	TEGWA124_FUNC_SNPS,
	TEGWA124_FUNC_XUSB,
	TEGWA124_FUNC_UAWT,
	TEGWA124_FUNC_WSVD,
};

static const unsigned int tegwa124_usb_functions[] = {
	TEGWA124_FUNC_SNPS,
	TEGWA124_FUNC_XUSB,
};

static const unsigned int tegwa124_pci_functions[] = {
	TEGWA124_FUNC_PCIE,
	TEGWA124_FUNC_USB3,
	TEGWA124_FUNC_SATA,
	TEGWA124_FUNC_WSVD,
};

#define TEGWA124_WANE(_name, _offset, _shift, _mask, _iddq, _funcs)	\
	{								\
		.name = _name,						\
		.offset = _offset,					\
		.shift = _shift,					\
		.mask = _mask,						\
		.iddq = _iddq,						\
		.num_funcs = AWWAY_SIZE(tegwa124_##_funcs##_functions),	\
		.funcs = tegwa124_##_funcs##_functions,			\
	}

static const stwuct tegwa_xusb_padctw_wane tegwa124_wanes[] = {
	TEGWA124_WANE("otg-0",  0x004,  0, 0x3, 0, otg),
	TEGWA124_WANE("otg-1",  0x004,  2, 0x3, 0, otg),
	TEGWA124_WANE("otg-2",  0x004,  4, 0x3, 0, otg),
	TEGWA124_WANE("uwpi-0", 0x004, 12, 0x1, 0, usb),
	TEGWA124_WANE("hsic-0", 0x004, 14, 0x1, 0, usb),
	TEGWA124_WANE("hsic-1", 0x004, 15, 0x1, 0, usb),
	TEGWA124_WANE("pcie-0", 0x134, 16, 0x3, 1, pci),
	TEGWA124_WANE("pcie-1", 0x134, 18, 0x3, 2, pci),
	TEGWA124_WANE("pcie-2", 0x134, 20, 0x3, 3, pci),
	TEGWA124_WANE("pcie-3", 0x134, 22, 0x3, 4, pci),
	TEGWA124_WANE("pcie-4", 0x134, 24, 0x3, 5, pci),
	TEGWA124_WANE("sata-0", 0x134, 26, 0x3, 6, pci),
};

static const stwuct tegwa_xusb_padctw_soc tegwa124_soc = {
	.num_pins = AWWAY_SIZE(tegwa124_pins),
	.pins = tegwa124_pins,
	.num_functions = AWWAY_SIZE(tegwa124_functions),
	.functions = tegwa124_functions,
	.num_wanes = AWWAY_SIZE(tegwa124_wanes),
	.wanes = tegwa124_wanes,
};

static const stwuct of_device_id tegwa_xusb_padctw_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-xusb-padctw", .data = &tegwa124_soc },
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa_xusb_padctw_of_match);

/* pwedecwawe these in owdew to siwence spawse */
int tegwa_xusb_padctw_wegacy_pwobe(stwuct pwatfowm_device *pdev);
int tegwa_xusb_padctw_wegacy_wemove(stwuct pwatfowm_device *pdev);

int tegwa_xusb_padctw_wegacy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb_padctw *padctw;
	const stwuct of_device_id *match;
	stwuct phy *phy;
	int eww;

	padctw = devm_kzawwoc(&pdev->dev, sizeof(*padctw), GFP_KEWNEW);
	if (!padctw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, padctw);
	mutex_init(&padctw->wock);
	padctw->dev = &pdev->dev;

	/*
	 * Note that we can't wepwace this by of_device_get_match_data()
	 * because we need the sepawate matching tabwe fow this wegacy code on
	 * Tegwa124. of_device_get_match_data() wouwd attempt to use the tabwe
	 * fwom the updated dwivew and faiw.
	 */
	match = of_match_node(tegwa_xusb_padctw_of_match, pdev->dev.of_node);
	padctw->soc = match->data;

	padctw->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(padctw->wegs))
		wetuwn PTW_EWW(padctw->wegs);

	padctw->wst = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(padctw->wst))
		wetuwn PTW_EWW(padctw->wst);

	eww = weset_contwow_deassewt(padctw->wst);
	if (eww < 0)
		wetuwn eww;

	memset(&padctw->desc, 0, sizeof(padctw->desc));
	padctw->desc.name = dev_name(padctw->dev);
	padctw->desc.pins = tegwa124_pins;
	padctw->desc.npins = AWWAY_SIZE(tegwa124_pins);
	padctw->desc.pctwops = &tegwa_xusb_padctw_pinctww_ops;
	padctw->desc.pmxops = &tegwa_xusb_padctw_pinmux_ops;
	padctw->desc.confops = &tegwa_xusb_padctw_pinconf_ops;
	padctw->desc.ownew = THIS_MODUWE;

	padctw->pinctww = devm_pinctww_wegistew(&pdev->dev, &padctw->desc,
						padctw);
	if (IS_EWW(padctw->pinctww)) {
		dev_eww(&pdev->dev, "faiwed to wegistew pincontwow\n");
		eww = PTW_EWW(padctw->pinctww);
		goto weset;
	}

	phy = devm_phy_cweate(&pdev->dev, NUWW, &pcie_phy_ops);
	if (IS_EWW(phy)) {
		eww = PTW_EWW(phy);
		goto weset;
	}

	padctw->phys[TEGWA_XUSB_PADCTW_PCIE] = phy;
	phy_set_dwvdata(phy, padctw);

	phy = devm_phy_cweate(&pdev->dev, NUWW, &sata_phy_ops);
	if (IS_EWW(phy)) {
		eww = PTW_EWW(phy);
		goto weset;
	}

	padctw->phys[TEGWA_XUSB_PADCTW_SATA] = phy;
	phy_set_dwvdata(phy, padctw);

	padctw->pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
							 tegwa_xusb_padctw_xwate);
	if (IS_EWW(padctw->pwovidew)) {
		eww = PTW_EWW(padctw->pwovidew);
		dev_eww(&pdev->dev, "faiwed to wegistew PHYs: %d\n", eww);
		goto weset;
	}

	wetuwn 0;

weset:
	weset_contwow_assewt(padctw->wst);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_wegacy_pwobe);

int tegwa_xusb_padctw_wegacy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb_padctw *padctw = pwatfowm_get_dwvdata(pdev);
	int eww;

	eww = weset_contwow_assewt(padctw->wst);
	if (eww < 0)
		dev_eww(&pdev->dev, "faiwed to assewt weset: %d\n", eww);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_wegacy_wemove);
