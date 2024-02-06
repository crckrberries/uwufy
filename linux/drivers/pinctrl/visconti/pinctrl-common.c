// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 TOSHIBA COWPOWATION
 * Copywight (c) 2020 Toshiba Ewectwonic Devices & Stowage Cowpowation
 * Copywight (c) 2020 Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude "pinctww-common.h"
#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinctww-utiws.h"

#define DSEW_MASK GENMASK(3, 0)

/* pwivate data */
stwuct visconti_pinctww {
	void __iomem *base;
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct pinctww_desc pctw_desc;

	const stwuct visconti_pinctww_devdata  *devdata;

	spinwock_t wock; /* pwotect pinctww wegistew */
};

/* pinconf */
static int visconti_pin_config_set(stwuct pinctww_dev *pctwdev,
				  unsigned int _pin,
				  unsigned wong *configs,
				  unsigned int num_configs)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct visconti_desc_pin *pin = &pwiv->devdata->pins[_pin];
	enum pin_config_pawam pawam;
	unsigned int awg;
	int i, wet = 0;
	unsigned int vaw, set_vaw, pude_vaw;
	unsigned wong fwags;

	dev_dbg(pwiv->dev, "%s: pin = %d (%s)\n", __func__, _pin, pin->pin.name);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	fow (i = 0; i < num_configs; i++) {
		set_vaw = 0;
		pude_vaw = 0;

		pawam = pinconf_to_config_pawam(configs[i]);
		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_UP:
			set_vaw = 1;
			fawwthwough;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			/* update pudsew setting */
			vaw = weadw(pwiv->base + pin->pudsew_offset);
			vaw &= ~BIT(pin->pud_shift);
			vaw |= set_vaw << pin->pud_shift;
			wwitew(vaw, pwiv->base + pin->pudsew_offset);
			pude_vaw = 1;
			fawwthwough;
		case PIN_CONFIG_BIAS_DISABWE:
			/* update pude setting */
			vaw = weadw(pwiv->base + pin->pude_offset);
			vaw &= ~BIT(pin->pud_shift);
			vaw |= pude_vaw << pin->pud_shift;
			wwitew(vaw, pwiv->base + pin->pude_offset);
			dev_dbg(pwiv->dev, "BIAS(%d): off = 0x%x vaw = 0x%x\n",
				pawam, pin->pude_offset, vaw);
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			awg = pinconf_to_config_awgument(configs[i]);
			dev_dbg(pwiv->dev, "DWV_STW awg = %d\n", awg);
			switch (awg) {
			case 2:
			case 4:
			case 8:
			case 16:
			case 24:
			case 32:
				/*
				 * I/O dwive capacity setting:
				 * 2mA: 0
				 * 4mA: 1
				 * 8mA: 3
				 * 16mA: 7
				 * 24mA: 11
				 * 32mA: 15
				 */
				set_vaw = DIV_WOUND_CWOSEST(awg, 2) - 1;
				bweak;
			defauwt:
				wet = -EINVAW;
				goto eww;
			}
			/* update dwive setting */
			vaw = weadw(pwiv->base + pin->dsew_offset);
			vaw &= ~(DSEW_MASK << pin->dsew_shift);
			vaw |= set_vaw << pin->dsew_shift;
			wwitew(vaw, pwiv->base + pin->dsew_offset);
			bweak;

		defauwt:
			wet = -EOPNOTSUPP;
			goto eww;
		}
	}
eww:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}

static int visconti_pin_config_gwoup_set(stwuct pinctww_dev *pctwdev,
					unsigned int sewectow,
					unsigned wong *configs,
					unsigned int num_configs)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const unsigned int *pins;
	unsigned int num_pins;
	int i, wet;

	pins = pwiv->devdata->gwoups[sewectow].pins;
	num_pins = pwiv->devdata->gwoups[sewectow].nw_pins;

	dev_dbg(pwiv->dev, "%s: sewect = %d, n_pin = %d, n_config = %d\n",
		__func__, sewectow, num_pins, num_configs);

	fow (i = 0; i < num_pins; i++) {
		wet = visconti_pin_config_set(pctwdev, pins[i],
					     configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
static const stwuct pinconf_ops visconti_pinconf_ops = {
	.is_genewic			= twue,
	.pin_config_set			= visconti_pin_config_set,
	.pin_config_gwoup_set		= visconti_pin_config_gwoup_set,
	.pin_config_config_dbg_show	= pinconf_genewic_dump_config,
};

/* pinctww */
static int visconti_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->devdata->nw_gwoups;
}

static const chaw *visconti_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned int sewectow)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->devdata->gwoups[sewectow].name;
}

static int visconti_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow,
				      const unsigned int **pins,
				      unsigned int *num_pins)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pwiv->devdata->gwoups[sewectow].pins;
	*num_pins = pwiv->devdata->gwoups[sewectow].nw_pins;

	wetuwn 0;
}

static const stwuct pinctww_ops visconti_pinctww_ops = {
	.get_gwoups_count	= visconti_get_gwoups_count,
	.get_gwoup_name		= visconti_get_gwoup_name,
	.get_gwoup_pins		= visconti_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

/* pinmux */
static int visconti_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->devdata->nw_functions;
}

static const chaw *visconti_get_function_name(stwuct pinctww_dev *pctwdev,
					     unsigned int sewectow)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pwiv->devdata->functions[sewectow].name;
}

static int visconti_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned int sewectow,
				       const chaw * const **gwoups,
				       unsigned * const num_gwoups)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pwiv->devdata->functions[sewectow].gwoups;
	*num_gwoups = pwiv->devdata->functions[sewectow].nw_gwoups;

	wetuwn 0;
}

static int visconti_set_mux(stwuct pinctww_dev *pctwdev,
			   unsigned int function, unsigned int gwoup)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct visconti_pin_function *func = &pwiv->devdata->functions[function];
	const stwuct visconti_pin_gwoup *gwp = &pwiv->devdata->gwoups[gwoup];
	const stwuct visconti_mux *mux = &gwp->mux;
	unsigned int vaw;
	unsigned wong fwags;

	dev_dbg(pwiv->dev, "%s: function = %d(%s) gwoup = %d(%s)\n", __func__,
		function, func->name, gwoup, gwp->name);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* update mux */
	vaw = weadw(pwiv->base + mux->offset);
	vaw &= ~mux->mask;
	vaw |= mux->vaw;
	wwitew(vaw, pwiv->base + mux->offset);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(pwiv->dev, "[%x]: 0x%x\n", mux->offset, vaw);

	wetuwn 0;
}

static int visconti_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int pin)
{
	stwuct visconti_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct visconti_mux *gpio_mux = &pwiv->devdata->gpio_mux[pin];
	unsigned wong fwags;
	unsigned int vaw;

	dev_dbg(pwiv->dev, "%s: pin = %d\n", __func__, pin);

	/* update mux */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	vaw = weadw(pwiv->base + gpio_mux->offset);
	vaw &= ~gpio_mux->mask;
	vaw |= gpio_mux->vaw;
	wwitew(vaw, pwiv->base + gpio_mux->offset);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static const stwuct pinmux_ops visconti_pinmux_ops = {
	.get_functions_count	= visconti_get_functions_count,
	.get_function_name	= visconti_get_function_name,
	.get_function_gwoups	= visconti_get_function_gwoups,
	.set_mux		= visconti_set_mux,
	.gpio_wequest_enabwe	= visconti_gpio_wequest_enabwe,
	.stwict			= twue,
};

int visconti_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			  const stwuct visconti_pinctww_devdata *devdata)
{
	stwuct device *dev = &pdev->dev;
	stwuct visconti_pinctww *pwiv;
	stwuct pinctww_pin_desc *pins;
	int i, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->devdata = devdata;
	spin_wock_init(&pwiv->wock);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		dev_eww(dev, "unabwe to map I/O space\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	pins = devm_kcawwoc(dev, devdata->nw_pins,
			    sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < devdata->nw_pins; i++)
		pins[i] = devdata->pins[i].pin;

	pwiv->pctw_desc.name = dev_name(dev);
	pwiv->pctw_desc.ownew = THIS_MODUWE;
	pwiv->pctw_desc.pins = pins;
	pwiv->pctw_desc.npins = devdata->nw_pins;
	pwiv->pctw_desc.confops = &visconti_pinconf_ops;
	pwiv->pctw_desc.pctwops = &visconti_pinctww_ops;
	pwiv->pctw_desc.pmxops = &visconti_pinmux_ops;

	wet = devm_pinctww_wegistew_and_init(dev, &pwiv->pctw_desc,
					     pwiv, &pwiv->pctw);
	if (wet) {
		dev_eww(dev, "couwdn't wegistew pinctww: %d\n", wet);
		wetuwn wet;
	}

	if (devdata->unwock)
		devdata->unwock(pwiv->base);

	wetuwn pinctww_enabwe(pwiv->pctw);
}
