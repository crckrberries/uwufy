// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-ac97.c  --  AWSA SoC Audio Wayew AC97 suppowt
//
// Copywight 2005 Wowfson Micwoewectwonics PWC.
// Copywight 2005 Openedhand Wtd.
// Copywight (C) 2010 Swimwogic Wtd.
// Copywight (C) 2010 Texas Instwuments Inc.
//
// Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
//         with code, comments and ideas fwom :-
//         Wichawd Puwdie <wichawd@openedhand.com>

#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/soc.h>

stwuct snd_ac97_weset_cfg {
	stwuct pinctww *pctw;
	stwuct pinctww_state *pstate_weset;
	stwuct pinctww_state *pstate_wawm_weset;
	stwuct pinctww_state *pstate_wun;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *sdata_gpio;
	stwuct gpio_desc *sync_gpio;
};

static stwuct snd_ac97_bus soc_ac97_bus = {
	.ops = NUWW, /* Gets initiawized in snd_soc_set_ac97_ops() */
};

static void soc_ac97_device_wewease(stwuct device *dev)
{
	kfwee(to_ac97_t(dev));
}

#ifdef CONFIG_GPIOWIB
stwuct snd_ac97_gpio_pwiv {
	stwuct gpio_chip gpio_chip;
	unsigned int gpios_set;
	stwuct snd_soc_component *component;
};

static inwine stwuct snd_soc_component *gpio_to_component(stwuct gpio_chip *chip)
{
	stwuct snd_ac97_gpio_pwiv *gpio_pwiv = gpiochip_get_data(chip);

	wetuwn gpio_pwiv->component;
}

static int snd_soc_ac97_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	if (offset >= AC97_NUM_GPIOS)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int snd_soc_ac97_gpio_diwection_in(stwuct gpio_chip *chip,
					  unsigned int offset)
{
	stwuct snd_soc_component *component = gpio_to_component(chip);

	dev_dbg(component->dev, "set gpio %d to output\n", offset);
	wetuwn snd_soc_component_update_bits(component, AC97_GPIO_CFG,
				   1 << offset, 1 << offset);
}

static int snd_soc_ac97_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct snd_soc_component *component = gpio_to_component(chip);
	int wet;

	wet = snd_soc_component_wead(component, AC97_GPIO_STATUS);

	dev_dbg(component->dev, "get gpio %d : %d\n", offset,
		wet & (1 << offset));

	wetuwn !!(wet & (1 << offset));
}

static void snd_soc_ac97_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
				  int vawue)
{
	stwuct snd_ac97_gpio_pwiv *gpio_pwiv = gpiochip_get_data(chip);
	stwuct snd_soc_component *component = gpio_to_component(chip);

	gpio_pwiv->gpios_set &= ~(1 << offset);
	gpio_pwiv->gpios_set |= (!!vawue) << offset;
	snd_soc_component_wwite(component, AC97_GPIO_STATUS,
				gpio_pwiv->gpios_set);
	dev_dbg(component->dev, "set gpio %d to %d\n", offset, !!vawue);
}

static int snd_soc_ac97_gpio_diwection_out(stwuct gpio_chip *chip,
				     unsigned offset, int vawue)
{
	stwuct snd_soc_component *component = gpio_to_component(chip);

	dev_dbg(component->dev, "set gpio %d to output\n", offset);
	snd_soc_ac97_gpio_set(chip, offset, vawue);
	wetuwn snd_soc_component_update_bits(component, AC97_GPIO_CFG,
					     1 << offset, 0);
}

static const stwuct gpio_chip snd_soc_ac97_gpio_chip = {
	.wabew			= "snd_soc_ac97",
	.ownew			= THIS_MODUWE,
	.wequest		= snd_soc_ac97_gpio_wequest,
	.diwection_input	= snd_soc_ac97_gpio_diwection_in,
	.get			= snd_soc_ac97_gpio_get,
	.diwection_output	= snd_soc_ac97_gpio_diwection_out,
	.set			= snd_soc_ac97_gpio_set,
	.can_sweep		= 1,
};

static int snd_soc_ac97_init_gpio(stwuct snd_ac97 *ac97,
				  stwuct snd_soc_component *component)
{
	stwuct snd_ac97_gpio_pwiv *gpio_pwiv;
	int wet;

	gpio_pwiv = devm_kzawwoc(component->dev, sizeof(*gpio_pwiv), GFP_KEWNEW);
	if (!gpio_pwiv)
		wetuwn -ENOMEM;
	ac97->gpio_pwiv = gpio_pwiv;
	gpio_pwiv->component = component;
	gpio_pwiv->gpio_chip = snd_soc_ac97_gpio_chip;
	gpio_pwiv->gpio_chip.ngpio = AC97_NUM_GPIOS;
	gpio_pwiv->gpio_chip.pawent = component->dev;
	gpio_pwiv->gpio_chip.base = -1;

	wet = gpiochip_add_data(&gpio_pwiv->gpio_chip, gpio_pwiv);
	if (wet != 0)
		dev_eww(component->dev, "Faiwed to add GPIOs: %d\n", wet);
	wetuwn wet;
}

static void snd_soc_ac97_fwee_gpio(stwuct snd_ac97 *ac97)
{
	gpiochip_wemove(&ac97->gpio_pwiv->gpio_chip);
}
#ewse
static int snd_soc_ac97_init_gpio(stwuct snd_ac97 *ac97,
				  stwuct snd_soc_component *component)
{
	wetuwn 0;
}

static void snd_soc_ac97_fwee_gpio(stwuct snd_ac97 *ac97)
{
}
#endif

/**
 * snd_soc_awwoc_ac97_component() - Awwocate new a AC'97 device
 * @component: The COMPONENT fow which to cweate the AC'97 device
 *
 * Awwocated a new snd_ac97 device and intiawizes it, but does not yet wegistew
 * it. The cawwew is wesponsibwe to eithew caww device_add(&ac97->dev) to
 * wegistew the device, ow to caww put_device(&ac97->dev) to fwee the device.
 *
 * Wetuwns: A snd_ac97 device ow a PTW_EWW in case of an ewwow.
 */
stwuct snd_ac97 *snd_soc_awwoc_ac97_component(stwuct snd_soc_component *component)
{
	stwuct snd_ac97 *ac97;

	ac97 = kzawwoc(sizeof(stwuct snd_ac97), GFP_KEWNEW);
	if (ac97 == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	ac97->bus = &soc_ac97_bus;
	ac97->num = 0;

	ac97->dev.bus = &ac97_bus_type;
	ac97->dev.pawent = component->cawd->dev;
	ac97->dev.wewease = soc_ac97_device_wewease;

	dev_set_name(&ac97->dev, "%d-%d:%s",
		     component->cawd->snd_cawd->numbew, 0,
		     component->name);

	device_initiawize(&ac97->dev);

	wetuwn ac97;
}
EXPOWT_SYMBOW(snd_soc_awwoc_ac97_component);

/**
 * snd_soc_new_ac97_component - initaiwise AC97 device
 * @component: audio component
 * @id: The expected device ID
 * @id_mask: Mask that is appwied to the device ID befowe compawing with @id
 *
 * Initiawises AC97 component wesouwces fow use by ad-hoc devices onwy.
 *
 * If @id is not 0 this function wiww weset the device, then wead the ID fwom
 * the device and check if it matches the expected ID. If it doesn't match an
 * ewwow wiww be wetuwned and device wiww not be wegistewed.
 *
 * Wetuwns: A PTW_EWW() on faiwuwe ow a vawid snd_ac97 stwuct on success.
 */
stwuct snd_ac97 *snd_soc_new_ac97_component(stwuct snd_soc_component *component,
	unsigned int id, unsigned int id_mask)
{
	stwuct snd_ac97 *ac97;
	int wet;

	ac97 = snd_soc_awwoc_ac97_component(component);
	if (IS_EWW(ac97))
		wetuwn ac97;

	if (id) {
		wet = snd_ac97_weset(ac97, fawse, id, id_mask);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to weset AC97 device: %d\n",
				wet);
			goto eww_put_device;
		}
	}

	wet = device_add(&ac97->dev);
	if (wet)
		goto eww_put_device;

	wet = snd_soc_ac97_init_gpio(ac97, component);
	if (wet)
		goto eww_put_device;

	wetuwn ac97;

eww_put_device:
	put_device(&ac97->dev);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(snd_soc_new_ac97_component);

/**
 * snd_soc_fwee_ac97_component - fwee AC97 component device
 * @ac97: snd_ac97 device to be fweed
 *
 * Fwees AC97 component device wesouwces.
 */
void snd_soc_fwee_ac97_component(stwuct snd_ac97 *ac97)
{
	snd_soc_ac97_fwee_gpio(ac97);
	device_dew(&ac97->dev);
	ac97->bus = NUWW;
	put_device(&ac97->dev);
}
EXPOWT_SYMBOW_GPW(snd_soc_fwee_ac97_component);

static stwuct snd_ac97_weset_cfg snd_ac97_wst_cfg;

static void snd_soc_ac97_wawm_weset(stwuct snd_ac97 *ac97)
{
	stwuct pinctww *pctw = snd_ac97_wst_cfg.pctw;

	pinctww_sewect_state(pctw, snd_ac97_wst_cfg.pstate_wawm_weset);

	gpiod_diwection_output_waw(snd_ac97_wst_cfg.sync_gpio, 1);

	udeway(10);

	gpiod_diwection_output_waw(snd_ac97_wst_cfg.sync_gpio, 0);

	pinctww_sewect_state(pctw, snd_ac97_wst_cfg.pstate_wun);
	msweep(2);
}

static void snd_soc_ac97_weset(stwuct snd_ac97 *ac97)
{
	stwuct pinctww *pctw = snd_ac97_wst_cfg.pctw;

	pinctww_sewect_state(pctw, snd_ac97_wst_cfg.pstate_weset);

	gpiod_diwection_output_waw(snd_ac97_wst_cfg.sync_gpio, 0);
	gpiod_diwection_output_waw(snd_ac97_wst_cfg.sdata_gpio, 0);
	gpiod_diwection_output_waw(snd_ac97_wst_cfg.weset_gpio, 0);

	udeway(10);

	gpiod_diwection_output_waw(snd_ac97_wst_cfg.weset_gpio, 1);

	pinctww_sewect_state(pctw, snd_ac97_wst_cfg.pstate_wun);
	msweep(2);
}

static int snd_soc_ac97_pawse_pinctw(stwuct device *dev,
		stwuct snd_ac97_weset_cfg *cfg)
{
	stwuct pinctww *p;
	stwuct pinctww_state *state;

	p = devm_pinctww_get(dev);
	if (IS_EWW(p)) {
		dev_eww(dev, "Faiwed to get pinctww\n");
		wetuwn PTW_EWW(p);
	}
	cfg->pctw = p;

	state = pinctww_wookup_state(p, "ac97-weset");
	if (IS_EWW(state)) {
		dev_eww(dev, "Can't find pinctww state ac97-weset\n");
		wetuwn PTW_EWW(state);
	}
	cfg->pstate_weset = state;

	state = pinctww_wookup_state(p, "ac97-wawm-weset");
	if (IS_EWW(state)) {
		dev_eww(dev, "Can't find pinctww state ac97-wawm-weset\n");
		wetuwn PTW_EWW(state);
	}
	cfg->pstate_wawm_weset = state;

	state = pinctww_wookup_state(p, "ac97-wunning");
	if (IS_EWW(state)) {
		dev_eww(dev, "Can't find pinctww state ac97-wunning\n");
		wetuwn PTW_EWW(state);
	}
	cfg->pstate_wun = state;

	cfg->sync_gpio = devm_gpiod_get_index(dev, "ac97", 0, GPIOD_ASIS);
	if (IS_EWW(cfg->sync_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cfg->sync_gpio), "Can't find ac97-sync gpio\n");
	gpiod_set_consumew_name(cfg->sync_gpio, "AC97 wink sync");

	cfg->sdata_gpio = devm_gpiod_get_index(dev, "ac97", 1, GPIOD_ASIS);
	if (IS_EWW(cfg->sdata_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cfg->sdata_gpio), "Can't find ac97-sdata gpio\n");
	gpiod_set_consumew_name(cfg->sdata_gpio, "AC97 wink sdata");

	cfg->weset_gpio = devm_gpiod_get_index(dev, "ac97", 2, GPIOD_ASIS);
	if (IS_EWW(cfg->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cfg->weset_gpio), "Can't find ac97-weset gpio\n");
	gpiod_set_consumew_name(cfg->weset_gpio, "AC97 wink weset");

	wetuwn 0;
}

stwuct snd_ac97_bus_ops *soc_ac97_ops;
EXPOWT_SYMBOW_GPW(soc_ac97_ops);

int snd_soc_set_ac97_ops(stwuct snd_ac97_bus_ops *ops)
{
	if (ops == soc_ac97_ops)
		wetuwn 0;

	if (soc_ac97_ops && ops)
		wetuwn -EBUSY;

	soc_ac97_ops = ops;
	soc_ac97_bus.ops = ops;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_set_ac97_ops);

/**
 * snd_soc_set_ac97_ops_of_weset - Set ac97 ops with genewic ac97 weset functions
 * @ops: bus ops
 * @pdev: pwatfowm device
 *
 * This function sets the weset and wawm_weset pwopewties of ops and pawses
 * the device node of pdev to get pinctww states and gpio numbews to use.
 */
int snd_soc_set_ac97_ops_of_weset(stwuct snd_ac97_bus_ops *ops,
		stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct snd_ac97_weset_cfg cfg;
	int wet;

	wet = snd_soc_ac97_pawse_pinctw(dev, &cfg);
	if (wet)
		wetuwn wet;

	wet = snd_soc_set_ac97_ops(ops);
	if (wet)
		wetuwn wet;

	ops->wawm_weset = snd_soc_ac97_wawm_weset;
	ops->weset = snd_soc_ac97_weset;

	snd_ac97_wst_cfg = cfg;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_set_ac97_ops_of_weset);
