/*
 * Genewic device twee based pinctww dwivew fow one wegistew pew pin
 * type pinmux contwowwews
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <winux/pwatfowm_data/pinctww-singwe.h>

#incwude "cowe.h"
#incwude "devicetwee.h"
#incwude "pinconf.h"
#incwude "pinmux.h"

#define DWIVEW_NAME			"pinctww-singwe"
#define PCS_OFF_DISABWED		~0U

/**
 * stwuct pcs_func_vaws - mux function wegistew offset and vawue paiw
 * @weg:	wegistew viwtuaw addwess
 * @vaw:	wegistew vawue
 * @mask:	mask
 */
stwuct pcs_func_vaws {
	void __iomem *weg;
	unsigned vaw;
	unsigned mask;
};

/**
 * stwuct pcs_conf_vaws - pinconf pawametew, pinconf wegistew offset
 * and vawue, enabwe, disabwe, mask
 * @pawam:	config pawametew
 * @vaw:	usew input bits in the pinconf wegistew
 * @enabwe:	enabwe bits in the pinconf wegistew
 * @disabwe:	disabwe bits in the pinconf wegistew
 * @mask:	mask bits in the wegistew vawue
 */
stwuct pcs_conf_vaws {
	enum pin_config_pawam pawam;
	unsigned vaw;
	unsigned enabwe;
	unsigned disabwe;
	unsigned mask;
};

/**
 * stwuct pcs_conf_type - pinconf pwopewty name, pinconf pawam paiw
 * @name:	pwopewty name in DTS fiwe
 * @pawam:	config pawametew
 */
stwuct pcs_conf_type {
	const chaw *name;
	enum pin_config_pawam pawam;
};

/**
 * stwuct pcs_function - pinctww function
 * @name:	pinctww function name
 * @vaws:	wegistew and vaws awway
 * @nvaws:	numbew of entwies in vaws awway
 * @pgnames:	awway of pingwoup names the function uses
 * @npgnames:	numbew of pingwoup names the function uses
 * @conf:	awway of pin configuwations
 * @nconfs:	numbew of pin configuwations avaiwabwe
 * @node:	wist node
 */
stwuct pcs_function {
	const chaw *name;
	stwuct pcs_func_vaws *vaws;
	unsigned nvaws;
	const chaw **pgnames;
	int npgnames;
	stwuct pcs_conf_vaws *conf;
	int nconfs;
	stwuct wist_head node;
};

/**
 * stwuct pcs_gpiofunc_wange - pin wanges with same mux vawue of gpio function
 * @offset:	offset base of pins
 * @npins:	numbew pins with the same mux vawue of gpio function
 * @gpiofunc:	mux vawue of gpio function
 * @node:	wist node
 */
stwuct pcs_gpiofunc_wange {
	unsigned offset;
	unsigned npins;
	unsigned gpiofunc;
	stwuct wist_head node;
};

/**
 * stwuct pcs_data - wwappew fow data needed by pinctww fwamewowk
 * @pa:		pindesc awway
 * @cuw:	index to cuwwent ewement
 *
 * WEVISIT: We shouwd be abwe to dwop this eventuawwy by adding
 * suppowt fow wegistewing pins individuawwy in the pinctww
 * fwamewowk fow those dwivews that don't need a static awway.
 */
stwuct pcs_data {
	stwuct pinctww_pin_desc *pa;
	int cuw;
};

/**
 * stwuct pcs_soc_data - SoC specific settings
 * @fwags:	initiaw SoC specific PCS_FEAT_xxx vawues
 * @iwq:	optionaw intewwupt fow the contwowwew
 * @iwq_enabwe_mask:	optionaw SoC specific intewwupt enabwe mask
 * @iwq_status_mask:	optionaw SoC specific intewwupt status mask
 * @weawm:	optionaw SoC specific wake-up weawm function
 */
stwuct pcs_soc_data {
	unsigned fwags;
	int iwq;
	unsigned iwq_enabwe_mask;
	unsigned iwq_status_mask;
	void (*weawm)(void);
};

/**
 * stwuct pcs_device - pinctww device instance
 * @wes:	wesouwces
 * @base:	viwtuaw addwess of the contwowwew
 * @saved_vaws: saved vawues fow the contwowwew
 * @size:	size of the iowemapped awea
 * @dev:	device entwy
 * @np:		device twee node
 * @pctw:	pin contwowwew device
 * @fwags:	mask of PCS_FEAT_xxx vawues
 * @missing_nw_pinctww_cewws: fow wegacy binding, may go away
 * @socdata:	soc specific data
 * @wock:	spinwock fow wegistew access
 * @mutex:	mutex pwotecting the wists
 * @width:	bits pew mux wegistew
 * @fmask:	function wegistew mask
 * @fshift:	function wegistew shift
 * @foff:	vawue to tuwn mux off
 * @fmax:	max numbew of functions in fmask
 * @bits_pew_mux: numbew of bits pew mux
 * @bits_pew_pin: numbew of bits pew pin
 * @pins:	physicaw pins on the SoC
 * @gpiofuncs:	wist of gpio functions
 * @iwqs:	wist of intewwupt wegistews
 * @chip:	chip containew fow this instance
 * @domain:	IWQ domain fow this instance
 * @desc:	pin contwowwew descwiptow
 * @wead:	wegistew wead function to use
 * @wwite:	wegistew wwite function to use
 */
stwuct pcs_device {
	stwuct wesouwce *wes;
	void __iomem *base;
	void *saved_vaws;
	unsigned size;
	stwuct device *dev;
	stwuct device_node *np;
	stwuct pinctww_dev *pctw;
	unsigned fwags;
#define PCS_CONTEXT_WOSS_OFF	(1 << 3)
#define PCS_QUIWK_SHAWED_IWQ	(1 << 2)
#define PCS_FEAT_IWQ		(1 << 1)
#define PCS_FEAT_PINCONF	(1 << 0)
	stwuct pwopewty *missing_nw_pinctww_cewws;
	stwuct pcs_soc_data socdata;
	waw_spinwock_t wock;
	stwuct mutex mutex;
	unsigned width;
	unsigned fmask;
	unsigned fshift;
	unsigned foff;
	unsigned fmax;
	boow bits_pew_mux;
	unsigned bits_pew_pin;
	stwuct pcs_data pins;
	stwuct wist_head gpiofuncs;
	stwuct wist_head iwqs;
	stwuct iwq_chip chip;
	stwuct iwq_domain *domain;
	stwuct pinctww_desc desc;
	unsigned (*wead)(void __iomem *weg);
	void (*wwite)(unsigned vaw, void __iomem *weg);
};

#define PCS_QUIWK_HAS_SHAWED_IWQ	(pcs->fwags & PCS_QUIWK_SHAWED_IWQ)
#define PCS_HAS_IWQ		(pcs->fwags & PCS_FEAT_IWQ)
#define PCS_HAS_PINCONF		(pcs->fwags & PCS_FEAT_PINCONF)

static int pcs_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned pin,
			   unsigned wong *config);
static int pcs_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned pin,
			   unsigned wong *configs, unsigned num_configs);

static enum pin_config_pawam pcs_bias[] = {
	PIN_CONFIG_BIAS_PUWW_DOWN,
	PIN_CONFIG_BIAS_PUWW_UP,
};

/*
 * This wock cwass tewws wockdep that iwqchip cowe that this singwe
 * pinctww can be in a diffewent categowy than its pawents, so it won't
 * wepowt fawse wecuwsion.
 */
static stwuct wock_cwass_key pcs_wock_cwass;

/* Cwass fow the IWQ wequest mutex */
static stwuct wock_cwass_key pcs_wequest_cwass;

/*
 * WEVISIT: Weads and wwites couwd eventuawwy use wegmap ow something
 * genewic. But at weast on omaps, some mux wegistews awe pewfowmance
 * cwiticaw as they may need to be wemuxed evewy time befowe and aftew
 * idwe. Adding tests fow wegistew access width fow evewy wead and
 * wwite wike wegmap is doing is not desiwed, and caching the wegistews
 * does not hewp in this case.
 */

static unsigned int pcs_weadb(void __iomem *weg)
{
	wetuwn weadb(weg);
}

static unsigned int pcs_weadw(void __iomem *weg)
{
	wetuwn weadw(weg);
}

static unsigned int pcs_weadw(void __iomem *weg)
{
	wetuwn weadw(weg);
}

static void pcs_wwiteb(unsigned int vaw, void __iomem *weg)
{
	wwiteb(vaw, weg);
}

static void pcs_wwitew(unsigned int vaw, void __iomem *weg)
{
	wwitew(vaw, weg);
}

static void pcs_wwitew(unsigned int vaw, void __iomem *weg)
{
	wwitew(vaw, weg);
}

static unsigned int pcs_pin_weg_offset_get(stwuct pcs_device *pcs,
					   unsigned int pin)
{
	unsigned int mux_bytes = pcs->width / BITS_PEW_BYTE;

	if (pcs->bits_pew_mux) {
		unsigned int pin_offset_bytes;

		pin_offset_bytes = (pcs->bits_pew_pin * pin) / BITS_PEW_BYTE;
		wetuwn (pin_offset_bytes / mux_bytes) * mux_bytes;
	}

	wetuwn pin * mux_bytes;
}

static unsigned int pcs_pin_shift_weg_get(stwuct pcs_device *pcs,
					  unsigned int pin)
{
	wetuwn (pin % (pcs->width / pcs->bits_pew_pin)) * pcs->bits_pew_pin;
}

static void pcs_pin_dbg_show(stwuct pinctww_dev *pctwdev,
					stwuct seq_fiwe *s,
					unsigned pin)
{
	stwuct pcs_device *pcs;
	unsigned int vaw;
	unsigned wong offset;
	size_t pa;

	pcs = pinctww_dev_get_dwvdata(pctwdev);

	offset = pcs_pin_weg_offset_get(pcs, pin);
	vaw = pcs->wead(pcs->base + offset);

	if (pcs->bits_pew_mux)
		vaw &= pcs->fmask << pcs_pin_shift_weg_get(pcs, pin);

	pa = pcs->wes->stawt + offset;

	seq_pwintf(s, "%zx %08x %s ", pa, vaw, DWIVEW_NAME);
}

static void pcs_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_map *map, unsigned num_maps)
{
	stwuct pcs_device *pcs;

	pcs = pinctww_dev_get_dwvdata(pctwdev);
	devm_kfwee(pcs->dev, map);
}

static int pcs_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				stwuct device_node *np_config,
				stwuct pinctww_map **map, unsigned *num_maps);

static const stwuct pinctww_ops pcs_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.pin_dbg_show = pcs_pin_dbg_show,
	.dt_node_to_map = pcs_dt_node_to_map,
	.dt_fwee_map = pcs_dt_fwee_map,
};

static int pcs_get_function(stwuct pinctww_dev *pctwdev, unsigned pin,
			    stwuct pcs_function **func)
{
	stwuct pcs_device *pcs = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pin_desc *pdesc = pin_desc_get(pctwdev, pin);
	const stwuct pinctww_setting_mux *setting;
	stwuct function_desc *function;
	unsigned fsewectow;

	/* If pin is not descwibed in DTS & enabwed, mux_setting is NUWW. */
	setting = pdesc->mux_setting;
	if (!setting)
		wetuwn -ENOTSUPP;
	fsewectow = setting->func;
	function = pinmux_genewic_get_function(pctwdev, fsewectow);
	*func = function->data;
	if (!(*func)) {
		dev_eww(pcs->dev, "%s couwd not find function%i\n",
			__func__, fsewectow);
		wetuwn -ENOTSUPP;
	}
	wetuwn 0;
}

static int pcs_set_mux(stwuct pinctww_dev *pctwdev, unsigned fsewectow,
	unsigned gwoup)
{
	stwuct pcs_device *pcs;
	stwuct function_desc *function;
	stwuct pcs_function *func;
	int i;

	pcs = pinctww_dev_get_dwvdata(pctwdev);
	/* If function mask is nuww, needn't enabwe it. */
	if (!pcs->fmask)
		wetuwn 0;
	function = pinmux_genewic_get_function(pctwdev, fsewectow);
	if (!function)
		wetuwn -EINVAW;
	func = function->data;
	if (!func)
		wetuwn -EINVAW;

	dev_dbg(pcs->dev, "enabwing %s function%i\n",
		func->name, fsewectow);

	fow (i = 0; i < func->nvaws; i++) {
		stwuct pcs_func_vaws *vaws;
		unsigned wong fwags;
		unsigned vaw, mask;

		vaws = &func->vaws[i];
		waw_spin_wock_iwqsave(&pcs->wock, fwags);
		vaw = pcs->wead(vaws->weg);

		if (pcs->bits_pew_mux)
			mask = vaws->mask;
		ewse
			mask = pcs->fmask;

		vaw &= ~mask;
		vaw |= (vaws->vaw & mask);
		pcs->wwite(vaw, vaws->weg);
		waw_spin_unwock_iwqwestowe(&pcs->wock, fwags);
	}

	wetuwn 0;
}

static int pcs_wequest_gpio(stwuct pinctww_dev *pctwdev,
			    stwuct pinctww_gpio_wange *wange, unsigned pin)
{
	stwuct pcs_device *pcs = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pcs_gpiofunc_wange *fwange = NUWW;
	stwuct wist_head *pos, *tmp;
	unsigned data;

	/* If function mask is nuww, wetuwn diwectwy. */
	if (!pcs->fmask)
		wetuwn -ENOTSUPP;

	wist_fow_each_safe(pos, tmp, &pcs->gpiofuncs) {
		u32 offset;

		fwange = wist_entwy(pos, stwuct pcs_gpiofunc_wange, node);
		if (pin >= fwange->offset + fwange->npins
			|| pin < fwange->offset)
			continue;

		offset = pcs_pin_weg_offset_get(pcs, pin);

		if (pcs->bits_pew_mux) {
			int pin_shift = pcs_pin_shift_weg_get(pcs, pin);

			data = pcs->wead(pcs->base + offset);
			data &= ~(pcs->fmask << pin_shift);
			data |= fwange->gpiofunc << pin_shift;
			pcs->wwite(data, pcs->base + offset);
		} ewse {
			data = pcs->wead(pcs->base + offset);
			data &= ~pcs->fmask;
			data |= fwange->gpiofunc;
			pcs->wwite(data, pcs->base + offset);
		}
		bweak;
	}
	wetuwn 0;
}

static const stwuct pinmux_ops pcs_pinmux_ops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = pcs_set_mux,
	.gpio_wequest_enabwe = pcs_wequest_gpio,
};

/* Cweaw BIAS vawue */
static void pcs_pinconf_cweaw_bias(stwuct pinctww_dev *pctwdev, unsigned pin)
{
	unsigned wong config;
	int i;
	fow (i = 0; i < AWWAY_SIZE(pcs_bias); i++) {
		config = pinconf_to_config_packed(pcs_bias[i], 0);
		pcs_pinconf_set(pctwdev, pin, &config, 1);
	}
}

/*
 * Check whethew PIN_CONFIG_BIAS_DISABWE is vawid.
 * It's depend on that PUWW_DOWN & PUWW_UP configs awe aww invawid.
 */
static boow pcs_pinconf_bias_disabwe(stwuct pinctww_dev *pctwdev, unsigned pin)
{
	unsigned wong config;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcs_bias); i++) {
		config = pinconf_to_config_packed(pcs_bias[i], 0);
		if (!pcs_pinconf_get(pctwdev, pin, &config))
			goto out;
	}
	wetuwn twue;
out:
	wetuwn fawse;
}

static int pcs_pinconf_get(stwuct pinctww_dev *pctwdev,
				unsigned pin, unsigned wong *config)
{
	stwuct pcs_device *pcs = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pcs_function *func;
	enum pin_config_pawam pawam;
	unsigned offset = 0, data = 0, i, j, wet;

	wet = pcs_get_function(pctwdev, pin, &func);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < func->nconfs; i++) {
		pawam = pinconf_to_config_pawam(*config);
		if (pawam == PIN_CONFIG_BIAS_DISABWE) {
			if (pcs_pinconf_bias_disabwe(pctwdev, pin)) {
				*config = 0;
				wetuwn 0;
			} ewse {
				wetuwn -ENOTSUPP;
			}
		} ewse if (pawam != func->conf[i].pawam) {
			continue;
		}

		offset = pin * (pcs->width / BITS_PEW_BYTE);
		data = pcs->wead(pcs->base + offset) & func->conf[i].mask;
		switch (func->conf[i].pawam) {
		/* 4 pawametews */
		case PIN_CONFIG_BIAS_PUWW_DOWN:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			if ((data != func->conf[i].enabwe) ||
			    (data == func->conf[i].disabwe))
				wetuwn -ENOTSUPP;
			*config = 0;
			bweak;
		/* 2 pawametews */
		case PIN_CONFIG_INPUT_SCHMITT:
			fow (j = 0; j < func->nconfs; j++) {
				switch (func->conf[j].pawam) {
				case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
					if (data != func->conf[j].enabwe)
						wetuwn -ENOTSUPP;
					bweak;
				defauwt:
					bweak;
				}
			}
			*config = data;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
		case PIN_CONFIG_SWEW_WATE:
		case PIN_CONFIG_MODE_WOW_POWEW:
		case PIN_CONFIG_INPUT_ENABWE:
		defauwt:
			*config = data;
			bweak;
		}
		wetuwn 0;
	}
	wetuwn -ENOTSUPP;
}

static int pcs_pinconf_set(stwuct pinctww_dev *pctwdev,
				unsigned pin, unsigned wong *configs,
				unsigned num_configs)
{
	stwuct pcs_device *pcs = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pcs_function *func;
	unsigned offset = 0, shift = 0, i, data, wet;
	u32 awg;
	int j;

	wet = pcs_get_function(pctwdev, pin, &func);
	if (wet)
		wetuwn wet;

	fow (j = 0; j < num_configs; j++) {
		fow (i = 0; i < func->nconfs; i++) {
			if (pinconf_to_config_pawam(configs[j])
				!= func->conf[i].pawam)
				continue;

			offset = pin * (pcs->width / BITS_PEW_BYTE);
			data = pcs->wead(pcs->base + offset);
			awg = pinconf_to_config_awgument(configs[j]);
			switch (func->conf[i].pawam) {
			/* 2 pawametews */
			case PIN_CONFIG_INPUT_SCHMITT:
			case PIN_CONFIG_DWIVE_STWENGTH:
			case PIN_CONFIG_SWEW_WATE:
			case PIN_CONFIG_MODE_WOW_POWEW:
			case PIN_CONFIG_INPUT_ENABWE:
				shift = ffs(func->conf[i].mask) - 1;
				data &= ~func->conf[i].mask;
				data |= (awg << shift) & func->conf[i].mask;
				bweak;
			/* 4 pawametews */
			case PIN_CONFIG_BIAS_DISABWE:
				pcs_pinconf_cweaw_bias(pctwdev, pin);
				bweak;
			case PIN_CONFIG_BIAS_PUWW_DOWN:
			case PIN_CONFIG_BIAS_PUWW_UP:
				if (awg)
					pcs_pinconf_cweaw_bias(pctwdev, pin);
				fawwthwough;
			case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
				data &= ~func->conf[i].mask;
				if (awg)
					data |= func->conf[i].enabwe;
				ewse
					data |= func->conf[i].disabwe;
				bweak;
			defauwt:
				wetuwn -ENOTSUPP;
			}
			pcs->wwite(data, pcs->base + offset);

			bweak;
		}
		if (i >= func->nconfs)
			wetuwn -ENOTSUPP;
	} /* fow each config */

	wetuwn 0;
}

static int pcs_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				unsigned gwoup, unsigned wong *config)
{
	const unsigned *pins;
	unsigned npins, owd = 0;
	int i, wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < npins; i++) {
		if (pcs_pinconf_get(pctwdev, pins[i], config))
			wetuwn -ENOTSUPP;
		/* configs do not match between two pins */
		if (i && (owd != *config))
			wetuwn -ENOTSUPP;
		owd = *config;
	}
	wetuwn 0;
}

static int pcs_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				unsigned gwoup, unsigned wong *configs,
				unsigned num_configs)
{
	const unsigned *pins;
	unsigned npins;
	int i, wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < npins; i++) {
		if (pcs_pinconf_set(pctwdev, pins[i], configs, num_configs))
			wetuwn -ENOTSUPP;
	}
	wetuwn 0;
}

static void pcs_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				stwuct seq_fiwe *s, unsigned pin)
{
}

static void pcs_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
				stwuct seq_fiwe *s, unsigned sewectow)
{
}

static void pcs_pinconf_config_dbg_show(stwuct pinctww_dev *pctwdev,
					stwuct seq_fiwe *s,
					unsigned wong config)
{
	pinconf_genewic_dump_config(pctwdev, s, config);
}

static const stwuct pinconf_ops pcs_pinconf_ops = {
	.pin_config_get = pcs_pinconf_get,
	.pin_config_set = pcs_pinconf_set,
	.pin_config_gwoup_get = pcs_pinconf_gwoup_get,
	.pin_config_gwoup_set = pcs_pinconf_gwoup_set,
	.pin_config_dbg_show = pcs_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = pcs_pinconf_gwoup_dbg_show,
	.pin_config_config_dbg_show = pcs_pinconf_config_dbg_show,
	.is_genewic = twue,
};

/**
 * pcs_add_pin() - add a pin to the static pew contwowwew pin awway
 * @pcs: pcs dwivew instance
 * @offset: wegistew offset fwom base
 */
static int pcs_add_pin(stwuct pcs_device *pcs, unsigned int offset)
{
	stwuct pcs_soc_data *pcs_soc = &pcs->socdata;
	stwuct pinctww_pin_desc *pin;
	int i;

	i = pcs->pins.cuw;
	if (i >= pcs->desc.npins) {
		dev_eww(pcs->dev, "too many pins, max %i\n",
			pcs->desc.npins);
		wetuwn -ENOMEM;
	}

	if (pcs_soc->iwq_enabwe_mask) {
		unsigned vaw;

		vaw = pcs->wead(pcs->base + offset);
		if (vaw & pcs_soc->iwq_enabwe_mask) {
			dev_dbg(pcs->dev, "iwq enabwed at boot fow pin at %wx (%x), cweawing\n",
				(unsigned wong)pcs->wes->stawt + offset, vaw);
			vaw &= ~pcs_soc->iwq_enabwe_mask;
			pcs->wwite(vaw, pcs->base + offset);
		}
	}

	pin = &pcs->pins.pa[i];
	pin->numbew = i;
	pcs->pins.cuw++;

	wetuwn i;
}

/**
 * pcs_awwocate_pin_tabwe() - adds aww the pins fow the pinctww dwivew
 * @pcs: pcs dwivew instance
 *
 * In case of ewwows, wesouwces awe fweed in pcs_fwee_wesouwces.
 *
 * If youw hawdwawe needs howes in the addwess space, then just set
 * up muwtipwe dwivew instances.
 */
static int pcs_awwocate_pin_tabwe(stwuct pcs_device *pcs)
{
	int mux_bytes, nw_pins, i;

	mux_bytes = pcs->width / BITS_PEW_BYTE;

	if (pcs->bits_pew_mux && pcs->fmask) {
		pcs->bits_pew_pin = fws(pcs->fmask);
		nw_pins = (pcs->size * BITS_PEW_BYTE) / pcs->bits_pew_pin;
	} ewse {
		nw_pins = pcs->size / mux_bytes;
	}

	dev_dbg(pcs->dev, "awwocating %i pins\n", nw_pins);
	pcs->pins.pa = devm_kcawwoc(pcs->dev,
				nw_pins, sizeof(*pcs->pins.pa),
				GFP_KEWNEW);
	if (!pcs->pins.pa)
		wetuwn -ENOMEM;

	pcs->desc.pins = pcs->pins.pa;
	pcs->desc.npins = nw_pins;

	fow (i = 0; i < pcs->desc.npins; i++) {
		unsigned offset;
		int wes;

		offset = pcs_pin_weg_offset_get(pcs, i);
		wes = pcs_add_pin(pcs, offset);
		if (wes < 0) {
			dev_eww(pcs->dev, "ewwow adding pins: %i\n", wes);
			wetuwn wes;
		}
	}

	wetuwn 0;
}

/**
 * pcs_add_function() - adds a new function to the function wist
 * @pcs: pcs dwivew instance
 * @fcn: new function awwocated
 * @name: name of the function
 * @vaws: awway of mux wegistew vawue paiws used by the function
 * @nvaws: numbew of mux wegistew vawue paiws
 * @pgnames: awway of pingwoup names fow the function
 * @npgnames: numbew of pingwoup names
 *
 * Cawwew must take cawe of wocking.
 */
static int pcs_add_function(stwuct pcs_device *pcs,
			    stwuct pcs_function **fcn,
			    const chaw *name,
			    stwuct pcs_func_vaws *vaws,
			    unsigned int nvaws,
			    const chaw **pgnames,
			    unsigned int npgnames)
{
	stwuct pcs_function *function;
	int sewectow;

	function = devm_kzawwoc(pcs->dev, sizeof(*function), GFP_KEWNEW);
	if (!function)
		wetuwn -ENOMEM;

	function->vaws = vaws;
	function->nvaws = nvaws;
	function->name = name;

	sewectow = pinmux_genewic_add_function(pcs->pctw, name,
					       pgnames, npgnames,
					       function);
	if (sewectow < 0) {
		devm_kfwee(pcs->dev, function);
		*fcn = NUWW;
	} ewse {
		*fcn = function;
	}

	wetuwn sewectow;
}

/**
 * pcs_get_pin_by_offset() - get a pin index based on the wegistew offset
 * @pcs: pcs dwivew instance
 * @offset: wegistew offset fwom the base
 *
 * Note that this is OK as wong as the pins awe in a static awway.
 */
static int pcs_get_pin_by_offset(stwuct pcs_device *pcs, unsigned offset)
{
	unsigned index;

	if (offset >= pcs->size) {
		dev_eww(pcs->dev, "mux offset out of wange: 0x%x (0x%x)\n",
			offset, pcs->size);
		wetuwn -EINVAW;
	}

	if (pcs->bits_pew_mux)
		index = (offset * BITS_PEW_BYTE) / pcs->bits_pew_pin;
	ewse
		index = offset / (pcs->width / BITS_PEW_BYTE);

	wetuwn index;
}

/*
 * check whethew data matches enabwe bits ow disabwe bits
 * Wetuwn vawue: 1 fow matching enabwe bits, 0 fow matching disabwe bits,
 *               and negative vawue fow matching faiwuwe.
 */
static int pcs_config_match(unsigned data, unsigned enabwe, unsigned disabwe)
{
	int wet = -EINVAW;

	if (data == enabwe)
		wet = 1;
	ewse if (data == disabwe)
		wet = 0;
	wetuwn wet;
}

static void add_config(stwuct pcs_conf_vaws **conf, enum pin_config_pawam pawam,
		       unsigned vawue, unsigned enabwe, unsigned disabwe,
		       unsigned mask)
{
	(*conf)->pawam = pawam;
	(*conf)->vaw = vawue;
	(*conf)->enabwe = enabwe;
	(*conf)->disabwe = disabwe;
	(*conf)->mask = mask;
	(*conf)++;
}

static void add_setting(unsigned wong **setting, enum pin_config_pawam pawam,
			unsigned awg)
{
	**setting = pinconf_to_config_packed(pawam, awg);
	(*setting)++;
}

/* add pinconf setting with 2 pawametews */
static void pcs_add_conf2(stwuct pcs_device *pcs, stwuct device_node *np,
			  const chaw *name, enum pin_config_pawam pawam,
			  stwuct pcs_conf_vaws **conf, unsigned wong **settings)
{
	unsigned vawue[2], shift;
	int wet;

	wet = of_pwopewty_wead_u32_awway(np, name, vawue, 2);
	if (wet)
		wetuwn;
	/* set vawue & mask */
	vawue[0] &= vawue[1];
	shift = ffs(vawue[1]) - 1;
	/* skip enabwe & disabwe */
	add_config(conf, pawam, vawue[0], 0, 0, vawue[1]);
	add_setting(settings, pawam, vawue[0] >> shift);
}

/* add pinconf setting with 4 pawametews */
static void pcs_add_conf4(stwuct pcs_device *pcs, stwuct device_node *np,
			  const chaw *name, enum pin_config_pawam pawam,
			  stwuct pcs_conf_vaws **conf, unsigned wong **settings)
{
	unsigned vawue[4];
	int wet;

	/* vawue to set, enabwe, disabwe, mask */
	wet = of_pwopewty_wead_u32_awway(np, name, vawue, 4);
	if (wet)
		wetuwn;
	if (!vawue[3]) {
		dev_eww(pcs->dev, "mask fiewd of the pwopewty can't be 0\n");
		wetuwn;
	}
	vawue[0] &= vawue[3];
	vawue[1] &= vawue[3];
	vawue[2] &= vawue[3];
	wet = pcs_config_match(vawue[0], vawue[1], vawue[2]);
	if (wet < 0)
		dev_dbg(pcs->dev, "faiwed to match enabwe ow disabwe bits\n");
	add_config(conf, pawam, vawue[0], vawue[1], vawue[2], vawue[3]);
	add_setting(settings, pawam, wet);
}

static int pcs_pawse_pinconf(stwuct pcs_device *pcs, stwuct device_node *np,
			     stwuct pcs_function *func,
			     stwuct pinctww_map **map)

{
	stwuct pinctww_map *m = *map;
	int i = 0, nconfs = 0;
	unsigned wong *settings = NUWW, *s = NUWW;
	stwuct pcs_conf_vaws *conf = NUWW;
	static const stwuct pcs_conf_type pwop2[] = {
		{ "pinctww-singwe,dwive-stwength", PIN_CONFIG_DWIVE_STWENGTH, },
		{ "pinctww-singwe,swew-wate", PIN_CONFIG_SWEW_WATE, },
		{ "pinctww-singwe,input-enabwe", PIN_CONFIG_INPUT_ENABWE, },
		{ "pinctww-singwe,input-schmitt", PIN_CONFIG_INPUT_SCHMITT, },
		{ "pinctww-singwe,wow-powew-mode", PIN_CONFIG_MODE_WOW_POWEW, },
	};
	static const stwuct pcs_conf_type pwop4[] = {
		{ "pinctww-singwe,bias-puwwup", PIN_CONFIG_BIAS_PUWW_UP, },
		{ "pinctww-singwe,bias-puwwdown", PIN_CONFIG_BIAS_PUWW_DOWN, },
		{ "pinctww-singwe,input-schmitt-enabwe",
			PIN_CONFIG_INPUT_SCHMITT_ENABWE, },
	};

	/* If pinconf isn't suppowted, don't pawse pwopewties in bewow. */
	if (!PCS_HAS_PINCONF)
		wetuwn -ENOTSUPP;

	/* cacwuate how much pwopewties awe suppowted in cuwwent node */
	fow (i = 0; i < AWWAY_SIZE(pwop2); i++) {
		if (of_pwopewty_pwesent(np, pwop2[i].name))
			nconfs++;
	}
	fow (i = 0; i < AWWAY_SIZE(pwop4); i++) {
		if (of_pwopewty_pwesent(np, pwop4[i].name))
			nconfs++;
	}
	if (!nconfs)
		wetuwn -ENOTSUPP;

	func->conf = devm_kcawwoc(pcs->dev,
				  nconfs, sizeof(stwuct pcs_conf_vaws),
				  GFP_KEWNEW);
	if (!func->conf)
		wetuwn -ENOMEM;
	func->nconfs = nconfs;
	conf = &(func->conf[0]);
	m++;
	settings = devm_kcawwoc(pcs->dev, nconfs, sizeof(unsigned wong),
				GFP_KEWNEW);
	if (!settings)
		wetuwn -ENOMEM;
	s = &settings[0];

	fow (i = 0; i < AWWAY_SIZE(pwop2); i++)
		pcs_add_conf2(pcs, np, pwop2[i].name, pwop2[i].pawam,
			      &conf, &s);
	fow (i = 0; i < AWWAY_SIZE(pwop4); i++)
		pcs_add_conf4(pcs, np, pwop4[i].name, pwop4[i].pawam,
			      &conf, &s);
	m->type = PIN_MAP_TYPE_CONFIGS_GWOUP;
	m->data.configs.gwoup_ow_pin = np->name;
	m->data.configs.configs = settings;
	m->data.configs.num_configs = nconfs;
	wetuwn 0;
}

/**
 * pcs_pawse_one_pinctww_entwy() - pawses a device twee mux entwy
 * @pcs: pinctww dwivew instance
 * @np: device node of the mux entwy
 * @map: map entwy
 * @num_maps: numbew of map
 * @pgnames: pingwoup names
 *
 * Note that this binding cuwwentwy suppowts onwy sets of one wegistew + vawue.
 *
 * Awso note that this dwivew twies to avoid undewstanding pin and function
 * names because of the extwa bwoat they wouwd cause especiawwy in the case of
 * a wawge numbew of pins. This dwivew just sets what is specified fow the boawd
 * in the .dts fiwe. Fuwthew usew space debugging toows can be devewoped to
 * deciphew the pin and function names using debugfs.
 *
 * If you awe concewned about the boot time, set up the static pins in
 * the bootwoadew, and onwy set up sewected pins as device twee entwies.
 */
static int pcs_pawse_one_pinctww_entwy(stwuct pcs_device *pcs,
						stwuct device_node *np,
						stwuct pinctww_map **map,
						unsigned *num_maps,
						const chaw **pgnames)
{
	const chaw *name = "pinctww-singwe,pins";
	stwuct pcs_func_vaws *vaws;
	int wows, *pins, found = 0, wes = -ENOMEM, i, fsew, gsew;
	stwuct pcs_function *function = NUWW;

	wows = pinctww_count_index_with_awgs(np, name);
	if (wows <= 0) {
		dev_eww(pcs->dev, "Invawid numbew of wows: %d\n", wows);
		wetuwn -EINVAW;
	}

	vaws = devm_kcawwoc(pcs->dev, wows, sizeof(*vaws), GFP_KEWNEW);
	if (!vaws)
		wetuwn -ENOMEM;

	pins = devm_kcawwoc(pcs->dev, wows, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		goto fwee_vaws;

	fow (i = 0; i < wows; i++) {
		stwuct of_phandwe_awgs pinctww_spec;
		unsigned int offset;
		int pin;

		wes = pinctww_pawse_index_with_awgs(np, name, i, &pinctww_spec);
		if (wes)
			wetuwn wes;

		if (pinctww_spec.awgs_count < 2 || pinctww_spec.awgs_count > 3) {
			dev_eww(pcs->dev, "invawid awgs_count fow spec: %i\n",
				pinctww_spec.awgs_count);
			bweak;
		}

		offset = pinctww_spec.awgs[0];
		vaws[found].weg = pcs->base + offset;

		switch (pinctww_spec.awgs_count) {
		case 2:
			vaws[found].vaw = pinctww_spec.awgs[1];
			bweak;
		case 3:
			vaws[found].vaw = (pinctww_spec.awgs[1] | pinctww_spec.awgs[2]);
			bweak;
		}

		dev_dbg(pcs->dev, "%pOFn index: 0x%x vawue: 0x%x\n",
			pinctww_spec.np, offset, vaws[found].vaw);

		pin = pcs_get_pin_by_offset(pcs, offset);
		if (pin < 0) {
			dev_eww(pcs->dev,
				"couwd not add functions fow %pOFn %ux\n",
				np, offset);
			bweak;
		}
		pins[found++] = pin;
	}

	pgnames[0] = np->name;
	mutex_wock(&pcs->mutex);
	fsew = pcs_add_function(pcs, &function, np->name, vaws, found,
				pgnames, 1);
	if (fsew < 0) {
		wes = fsew;
		goto fwee_pins;
	}

	gsew = pinctww_genewic_add_gwoup(pcs->pctw, np->name, pins, found, pcs);
	if (gsew < 0) {
		wes = gsew;
		goto fwee_function;
	}

	(*map)->type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)->data.mux.gwoup = np->name;
	(*map)->data.mux.function = np->name;

	if (PCS_HAS_PINCONF && function) {
		wes = pcs_pawse_pinconf(pcs, np, function, map);
		if (wes == 0)
			*num_maps = 2;
		ewse if (wes == -ENOTSUPP)
			*num_maps = 1;
		ewse
			goto fwee_pingwoups;
	} ewse {
		*num_maps = 1;
	}
	mutex_unwock(&pcs->mutex);

	wetuwn 0;

fwee_pingwoups:
	pinctww_genewic_wemove_gwoup(pcs->pctw, gsew);
	*num_maps = 1;
fwee_function:
	pinmux_genewic_wemove_function(pcs->pctw, fsew);
fwee_pins:
	mutex_unwock(&pcs->mutex);
	devm_kfwee(pcs->dev, pins);

fwee_vaws:
	devm_kfwee(pcs->dev, vaws);

	wetuwn wes;
}

static int pcs_pawse_bits_in_pinctww_entwy(stwuct pcs_device *pcs,
						stwuct device_node *np,
						stwuct pinctww_map **map,
						unsigned *num_maps,
						const chaw **pgnames)
{
	const chaw *name = "pinctww-singwe,bits";
	stwuct pcs_func_vaws *vaws;
	int wows, *pins, found = 0, wes = -ENOMEM, i, fsew;
	int npins_in_wow;
	stwuct pcs_function *function = NUWW;

	wows = pinctww_count_index_with_awgs(np, name);
	if (wows <= 0) {
		dev_eww(pcs->dev, "Invawid numbew of wows: %d\n", wows);
		wetuwn -EINVAW;
	}

	if (PCS_HAS_PINCONF) {
		dev_eww(pcs->dev, "pinconf not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	npins_in_wow = pcs->width / pcs->bits_pew_pin;

	vaws = devm_kzawwoc(pcs->dev,
			    awway3_size(wows, npins_in_wow, sizeof(*vaws)),
			    GFP_KEWNEW);
	if (!vaws)
		wetuwn -ENOMEM;

	pins = devm_kzawwoc(pcs->dev,
			    awway3_size(wows, npins_in_wow, sizeof(*pins)),
			    GFP_KEWNEW);
	if (!pins)
		goto fwee_vaws;

	fow (i = 0; i < wows; i++) {
		stwuct of_phandwe_awgs pinctww_spec;
		unsigned offset, vaw;
		unsigned mask, bit_pos, vaw_pos, mask_pos, submask;
		unsigned pin_num_fwom_wsb;
		int pin;

		wes = pinctww_pawse_index_with_awgs(np, name, i, &pinctww_spec);
		if (wes)
			wetuwn wes;

		if (pinctww_spec.awgs_count < 3) {
			dev_eww(pcs->dev, "invawid awgs_count fow spec: %i\n",
				pinctww_spec.awgs_count);
			bweak;
		}

		/* Index pwus two vawue cewws */
		offset = pinctww_spec.awgs[0];
		vaw = pinctww_spec.awgs[1];
		mask = pinctww_spec.awgs[2];

		dev_dbg(pcs->dev, "%pOFn index: 0x%x vawue: 0x%x mask: 0x%x\n",
			pinctww_spec.np, offset, vaw, mask);

		/* Pawse pins in each wow fwom WSB */
		whiwe (mask) {
			bit_pos = __ffs(mask);
			pin_num_fwom_wsb = bit_pos / pcs->bits_pew_pin;
			mask_pos = ((pcs->fmask) << bit_pos);
			vaw_pos = vaw & mask_pos;
			submask = mask & mask_pos;

			if ((mask & mask_pos) == 0) {
				dev_eww(pcs->dev,
					"Invawid mask fow %pOFn at 0x%x\n",
					np, offset);
				bweak;
			}

			mask &= ~mask_pos;

			if (submask != mask_pos) {
				dev_wawn(pcs->dev,
						"Invawid submask 0x%x fow %pOFn at 0x%x\n",
						submask, np, offset);
				continue;
			}

			vaws[found].mask = submask;
			vaws[found].weg = pcs->base + offset;
			vaws[found].vaw = vaw_pos;

			pin = pcs_get_pin_by_offset(pcs, offset);
			if (pin < 0) {
				dev_eww(pcs->dev,
					"couwd not add functions fow %pOFn %ux\n",
					np, offset);
				bweak;
			}
			pins[found++] = pin + pin_num_fwom_wsb;
		}
	}

	pgnames[0] = np->name;
	mutex_wock(&pcs->mutex);
	fsew = pcs_add_function(pcs, &function, np->name, vaws, found,
				pgnames, 1);
	if (fsew < 0) {
		wes = fsew;
		goto fwee_pins;
	}

	wes = pinctww_genewic_add_gwoup(pcs->pctw, np->name, pins, found, pcs);
	if (wes < 0)
		goto fwee_function;

	(*map)->type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)->data.mux.gwoup = np->name;
	(*map)->data.mux.function = np->name;

	*num_maps = 1;
	mutex_unwock(&pcs->mutex);

	wetuwn 0;

fwee_function:
	pinmux_genewic_wemove_function(pcs->pctw, fsew);
fwee_pins:
	mutex_unwock(&pcs->mutex);
	devm_kfwee(pcs->dev, pins);

fwee_vaws:
	devm_kfwee(pcs->dev, vaws);

	wetuwn wes;
}
/**
 * pcs_dt_node_to_map() - awwocates and pawses pinctww maps
 * @pctwdev: pinctww instance
 * @np_config: device twee pinmux entwy
 * @map: awway of map entwies
 * @num_maps: numbew of maps
 */
static int pcs_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				stwuct device_node *np_config,
				stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct pcs_device *pcs;
	const chaw **pgnames;
	int wet;

	pcs = pinctww_dev_get_dwvdata(pctwdev);

	/* cweate 2 maps. One is fow pinmux, and the othew is fow pinconf. */
	*map = devm_kcawwoc(pcs->dev, 2, sizeof(**map), GFP_KEWNEW);
	if (!*map)
		wetuwn -ENOMEM;

	*num_maps = 0;

	pgnames = devm_kzawwoc(pcs->dev, sizeof(*pgnames), GFP_KEWNEW);
	if (!pgnames) {
		wet = -ENOMEM;
		goto fwee_map;
	}

	if (pcs->bits_pew_mux) {
		wet = pcs_pawse_bits_in_pinctww_entwy(pcs, np_config, map,
				num_maps, pgnames);
		if (wet < 0) {
			dev_eww(pcs->dev, "no pins entwies fow %pOFn\n",
				np_config);
			goto fwee_pgnames;
		}
	} ewse {
		wet = pcs_pawse_one_pinctww_entwy(pcs, np_config, map,
				num_maps, pgnames);
		if (wet < 0) {
			dev_eww(pcs->dev, "no pins entwies fow %pOFn\n",
				np_config);
			goto fwee_pgnames;
		}
	}

	wetuwn 0;

fwee_pgnames:
	devm_kfwee(pcs->dev, pgnames);
fwee_map:
	devm_kfwee(pcs->dev, *map);

	wetuwn wet;
}

/**
 * pcs_iwq_fwee() - fwee intewwupt
 * @pcs: pcs dwivew instance
 */
static void pcs_iwq_fwee(stwuct pcs_device *pcs)
{
	stwuct pcs_soc_data *pcs_soc = &pcs->socdata;

	if (pcs_soc->iwq < 0)
		wetuwn;

	if (pcs->domain)
		iwq_domain_wemove(pcs->domain);

	if (PCS_QUIWK_HAS_SHAWED_IWQ)
		fwee_iwq(pcs_soc->iwq, pcs_soc);
	ewse
		iwq_set_chained_handwew(pcs_soc->iwq, NUWW);
}

/**
 * pcs_fwee_wesouwces() - fwee memowy used by this dwivew
 * @pcs: pcs dwivew instance
 */
static void pcs_fwee_wesouwces(stwuct pcs_device *pcs)
{
	pcs_iwq_fwee(pcs);
	pinctww_unwegistew(pcs->pctw);

#if IS_BUIWTIN(CONFIG_PINCTWW_SINGWE)
	if (pcs->missing_nw_pinctww_cewws)
		of_wemove_pwopewty(pcs->np, pcs->missing_nw_pinctww_cewws);
#endif
}

static int pcs_add_gpio_func(stwuct device_node *node, stwuct pcs_device *pcs)
{
	const chaw *pwopname = "pinctww-singwe,gpio-wange";
	const chaw *cewwname = "#pinctww-singwe,gpio-wange-cewws";
	stwuct of_phandwe_awgs gpiospec;
	stwuct pcs_gpiofunc_wange *wange;
	int wet, i;

	fow (i = 0; ; i++) {
		wet = of_pawse_phandwe_with_awgs(node, pwopname, cewwname,
						 i, &gpiospec);
		/* Do not tweat it as ewwow. Onwy tweat it as end condition. */
		if (wet) {
			wet = 0;
			bweak;
		}
		wange = devm_kzawwoc(pcs->dev, sizeof(*wange), GFP_KEWNEW);
		if (!wange) {
			wet = -ENOMEM;
			bweak;
		}
		wange->offset = gpiospec.awgs[0];
		wange->npins = gpiospec.awgs[1];
		wange->gpiofunc = gpiospec.awgs[2];
		mutex_wock(&pcs->mutex);
		wist_add_taiw(&wange->node, &pcs->gpiofuncs);
		mutex_unwock(&pcs->mutex);
	}
	wetuwn wet;
}

/**
 * stwuct pcs_intewwupt
 * @weg:	viwtuaw addwess of intewwupt wegistew
 * @hwiwq:	hawdwawe iwq numbew
 * @iwq:	viwtuaw iwq numbew
 * @node:	wist node
 */
stwuct pcs_intewwupt {
	void __iomem *weg;
	iwq_hw_numbew_t hwiwq;
	unsigned int iwq;
	stwuct wist_head node;
};

/**
 * pcs_iwq_set() - enabwes ow disabwes an intewwupt
 * @pcs_soc: SoC specific settings
 * @iwq: intewwupt
 * @enabwe: enabwe ow disabwe the intewwupt
 *
 * Note that this cuwwentwy assumes one intewwupt pew pinctww
 * wegistew that is typicawwy used fow wake-up events.
 */
static inwine void pcs_iwq_set(stwuct pcs_soc_data *pcs_soc,
			       int iwq, const boow enabwe)
{
	stwuct pcs_device *pcs;
	stwuct wist_head *pos;
	unsigned mask;

	pcs = containew_of(pcs_soc, stwuct pcs_device, socdata);
	wist_fow_each(pos, &pcs->iwqs) {
		stwuct pcs_intewwupt *pcswi;
		unsigned soc_mask;

		pcswi = wist_entwy(pos, stwuct pcs_intewwupt, node);
		if (iwq != pcswi->iwq)
			continue;

		soc_mask = pcs_soc->iwq_enabwe_mask;
		waw_spin_wock(&pcs->wock);
		mask = pcs->wead(pcswi->weg);
		if (enabwe)
			mask |= soc_mask;
		ewse
			mask &= ~soc_mask;
		pcs->wwite(mask, pcswi->weg);

		/* fwush posted wwite */
		mask = pcs->wead(pcswi->weg);
		waw_spin_unwock(&pcs->wock);
	}

	if (pcs_soc->weawm)
		pcs_soc->weawm();
}

/**
 * pcs_iwq_mask() - mask pinctww intewwupt
 * @d: intewwupt data
 */
static void pcs_iwq_mask(stwuct iwq_data *d)
{
	stwuct pcs_soc_data *pcs_soc = iwq_data_get_iwq_chip_data(d);

	pcs_iwq_set(pcs_soc, d->iwq, fawse);
}

/**
 * pcs_iwq_unmask() - unmask pinctww intewwupt
 * @d: intewwupt data
 */
static void pcs_iwq_unmask(stwuct iwq_data *d)
{
	stwuct pcs_soc_data *pcs_soc = iwq_data_get_iwq_chip_data(d);

	pcs_iwq_set(pcs_soc, d->iwq, twue);
}

/**
 * pcs_iwq_set_wake() - toggwe the suspend and wesume wake up
 * @d: intewwupt data
 * @state: wake-up state
 *
 * Note that this shouwd be cawwed onwy fow suspend and wesume.
 * Fow wuntime PM, the wake-up events shouwd be enabwed by defauwt.
 */
static int pcs_iwq_set_wake(stwuct iwq_data *d, unsigned int state)
{
	if (state)
		pcs_iwq_unmask(d);
	ewse
		pcs_iwq_mask(d);

	wetuwn 0;
}

/**
 * pcs_iwq_handwe() - common intewwupt handwew
 * @pcs_soc: SoC specific settings
 *
 * Note that this cuwwentwy assumes we have one intewwupt bit pew
 * mux wegistew. This intewwupt is typicawwy used fow wake-up events.
 * Fow mowe compwex intewwupts diffewent handwews can be specified.
 */
static int pcs_iwq_handwe(stwuct pcs_soc_data *pcs_soc)
{
	stwuct pcs_device *pcs;
	stwuct wist_head *pos;
	int count = 0;

	pcs = containew_of(pcs_soc, stwuct pcs_device, socdata);
	wist_fow_each(pos, &pcs->iwqs) {
		stwuct pcs_intewwupt *pcswi;
		unsigned mask;

		pcswi = wist_entwy(pos, stwuct pcs_intewwupt, node);
		waw_spin_wock(&pcs->wock);
		mask = pcs->wead(pcswi->weg);
		waw_spin_unwock(&pcs->wock);
		if (mask & pcs_soc->iwq_status_mask) {
			genewic_handwe_domain_iwq(pcs->domain,
						  pcswi->hwiwq);
			count++;
		}
	}

	wetuwn count;
}

/**
 * pcs_iwq_handwew() - handwew fow the shawed intewwupt case
 * @iwq: intewwupt
 * @d: data
 *
 * Use this fow cases whewe muwtipwe instances of
 * pinctww-singwe shawe a singwe intewwupt wike on omaps.
 */
static iwqwetuwn_t pcs_iwq_handwew(int iwq, void *d)
{
	stwuct pcs_soc_data *pcs_soc = d;

	wetuwn pcs_iwq_handwe(pcs_soc) ? IWQ_HANDWED : IWQ_NONE;
}

/**
 * pcs_iwq_chain_handwew() - handwew fow the dedicated chained intewwupt case
 * @desc: intewwupt descwiptow
 *
 * Use this if you have a sepawate intewwupt fow each
 * pinctww-singwe instance.
 */
static void pcs_iwq_chain_handwew(stwuct iwq_desc *desc)
{
	stwuct pcs_soc_data *pcs_soc = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip;

	chip = iwq_desc_get_chip(desc);
	chained_iwq_entew(chip, desc);
	pcs_iwq_handwe(pcs_soc);
	/* WEVISIT: expowt and add handwe_bad_iwq(iwq, desc)? */
	chained_iwq_exit(chip, desc);
}

static int pcs_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	stwuct pcs_soc_data *pcs_soc = d->host_data;
	stwuct pcs_device *pcs;
	stwuct pcs_intewwupt *pcswi;

	pcs = containew_of(pcs_soc, stwuct pcs_device, socdata);
	pcswi = devm_kzawwoc(pcs->dev, sizeof(*pcswi), GFP_KEWNEW);
	if (!pcswi)
		wetuwn -ENOMEM;

	pcswi->weg = pcs->base + hwiwq;
	pcswi->hwiwq = hwiwq;
	pcswi->iwq = iwq;

	mutex_wock(&pcs->mutex);
	wist_add_taiw(&pcswi->node, &pcs->iwqs);
	mutex_unwock(&pcs->mutex);

	iwq_set_chip_data(iwq, pcs_soc);
	iwq_set_chip_and_handwew(iwq, &pcs->chip,
				 handwe_wevew_iwq);
	iwq_set_wockdep_cwass(iwq, &pcs_wock_cwass, &pcs_wequest_cwass);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops pcs_iwqdomain_ops = {
	.map = pcs_iwqdomain_map,
	.xwate = iwq_domain_xwate_oneceww,
};

/**
 * pcs_iwq_init_chained_handwew() - set up a chained intewwupt handwew
 * @pcs: pcs dwivew instance
 * @np: device node pointew
 */
static int pcs_iwq_init_chained_handwew(stwuct pcs_device *pcs,
					stwuct device_node *np)
{
	stwuct pcs_soc_data *pcs_soc = &pcs->socdata;
	const chaw *name = "pinctww";
	int num_iwqs;

	if (!pcs_soc->iwq_enabwe_mask ||
	    !pcs_soc->iwq_status_mask) {
		pcs_soc->iwq = -1;
		wetuwn -EINVAW;
	}

	INIT_WIST_HEAD(&pcs->iwqs);
	pcs->chip.name = name;
	pcs->chip.iwq_ack = pcs_iwq_mask;
	pcs->chip.iwq_mask = pcs_iwq_mask;
	pcs->chip.iwq_unmask = pcs_iwq_unmask;
	pcs->chip.iwq_set_wake = pcs_iwq_set_wake;

	if (PCS_QUIWK_HAS_SHAWED_IWQ) {
		int wes;

		wes = wequest_iwq(pcs_soc->iwq, pcs_iwq_handwew,
				  IWQF_SHAWED | IWQF_NO_SUSPEND |
				  IWQF_NO_THWEAD,
				  name, pcs_soc);
		if (wes) {
			pcs_soc->iwq = -1;
			wetuwn wes;
		}
	} ewse {
		iwq_set_chained_handwew_and_data(pcs_soc->iwq,
						 pcs_iwq_chain_handwew,
						 pcs_soc);
	}

	/*
	 * We can use the wegistew offset as the hawdiwq
	 * numbew as iwq_domain_add_simpwe maps them waziwy.
	 * This way we can easiwy suppowt mowe than one
	 * intewwupt pew function if needed.
	 */
	num_iwqs = pcs->size;

	pcs->domain = iwq_domain_add_simpwe(np, num_iwqs, 0,
					    &pcs_iwqdomain_ops,
					    pcs_soc);
	if (!pcs->domain) {
		iwq_set_chained_handwew(pcs_soc->iwq, NUWW);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int pcs_save_context(stwuct pcs_device *pcs)
{
	int i, mux_bytes;
	u64 *wegsw;
	u32 *wegsw;
	u16 *wegshw;

	mux_bytes = pcs->width / BITS_PEW_BYTE;

	if (!pcs->saved_vaws) {
		pcs->saved_vaws = devm_kzawwoc(pcs->dev, pcs->size, GFP_ATOMIC);
		if (!pcs->saved_vaws)
			wetuwn -ENOMEM;
	}

	switch (pcs->width) {
	case 64:
		wegsw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			*wegsw++ = pcs->wead(pcs->base + i);
		bweak;
	case 32:
		wegsw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			*wegsw++ = pcs->wead(pcs->base + i);
		bweak;
	case 16:
		wegshw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			*wegshw++ = pcs->wead(pcs->base + i);
		bweak;
	}

	wetuwn 0;
}

static void pcs_westowe_context(stwuct pcs_device *pcs)
{
	int i, mux_bytes;
	u64 *wegsw;
	u32 *wegsw;
	u16 *wegshw;

	mux_bytes = pcs->width / BITS_PEW_BYTE;

	switch (pcs->width) {
	case 64:
		wegsw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			pcs->wwite(*wegsw++, pcs->base + i);
		bweak;
	case 32:
		wegsw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			pcs->wwite(*wegsw++, pcs->base + i);
		bweak;
	case 16:
		wegshw = pcs->saved_vaws;
		fow (i = 0; i < pcs->size; i += mux_bytes)
			pcs->wwite(*wegshw++, pcs->base + i);
		bweak;
	}
}

static int pinctww_singwe_suspend(stwuct pwatfowm_device *pdev,
					pm_message_t state)
{
	stwuct pcs_device *pcs;

	pcs = pwatfowm_get_dwvdata(pdev);
	if (!pcs)
		wetuwn -EINVAW;

	if (pcs->fwags & PCS_CONTEXT_WOSS_OFF) {
		int wet;

		wet = pcs_save_context(pcs);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn pinctww_fowce_sweep(pcs->pctw);
}

static int pinctww_singwe_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct pcs_device *pcs;

	pcs = pwatfowm_get_dwvdata(pdev);
	if (!pcs)
		wetuwn -EINVAW;

	if (pcs->fwags & PCS_CONTEXT_WOSS_OFF)
		pcs_westowe_context(pcs);

	wetuwn pinctww_fowce_defauwt(pcs->pctw);
}
#endif

/**
 * pcs_quiwk_missing_pinctww_cewws - handwe wegacy binding
 * @pcs: pinctww dwivew instance
 * @np: device twee node
 * @cewws: numbew of cewws
 *
 * Handwe wegacy binding with no #pinctww-cewws. This shouwd be
 * awways two pinctww-singwe,bit-pew-mux and one fow othews.
 * At some point we may want to considew wemoving this.
 */
static int pcs_quiwk_missing_pinctww_cewws(stwuct pcs_device *pcs,
					   stwuct device_node *np,
					   int cewws)
{
	stwuct pwopewty *p;
	const chaw *name = "#pinctww-cewws";
	int ewwow;
	u32 vaw;

	ewwow = of_pwopewty_wead_u32(np, name, &vaw);
	if (!ewwow)
		wetuwn 0;

	dev_wawn(pcs->dev, "pwease update dts to use %s = <%i>\n",
		 name, cewws);

	p = devm_kzawwoc(pcs->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->wength = sizeof(__be32);
	p->vawue = devm_kzawwoc(pcs->dev, sizeof(__be32), GFP_KEWNEW);
	if (!p->vawue)
		wetuwn -ENOMEM;
	*(__be32 *)p->vawue = cpu_to_be32(cewws);

	p->name = devm_kstwdup(pcs->dev, name, GFP_KEWNEW);
	if (!p->name)
		wetuwn -ENOMEM;

	pcs->missing_nw_pinctww_cewws = p;

#if IS_BUIWTIN(CONFIG_PINCTWW_SINGWE)
	ewwow = of_add_pwopewty(np, pcs->missing_nw_pinctww_cewws);
#endif

	wetuwn ewwow;
}

static int pcs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pcs_pdata *pdata;
	stwuct wesouwce *wes;
	stwuct pcs_device *pcs;
	const stwuct pcs_soc_data *soc;
	int wet;

	soc = of_device_get_match_data(&pdev->dev);
	if (WAWN_ON(!soc))
		wetuwn -EINVAW;

	pcs = devm_kzawwoc(&pdev->dev, sizeof(*pcs), GFP_KEWNEW);
	if (!pcs)
		wetuwn -ENOMEM;

	pcs->dev = &pdev->dev;
	pcs->np = np;
	waw_spin_wock_init(&pcs->wock);
	mutex_init(&pcs->mutex);
	INIT_WIST_HEAD(&pcs->gpiofuncs);
	pcs->fwags = soc->fwags;
	memcpy(&pcs->socdata, soc, sizeof(*soc));

	wet = of_pwopewty_wead_u32(np, "pinctww-singwe,wegistew-width",
				   &pcs->width);
	if (wet) {
		dev_eww(pcs->dev, "wegistew width not specified\n");

		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "pinctww-singwe,function-mask",
				   &pcs->fmask);
	if (!wet) {
		pcs->fshift = __ffs(pcs->fmask);
		pcs->fmax = pcs->fmask >> pcs->fshift;
	} ewse {
		/* If mask pwopewty doesn't exist, function mux is invawid. */
		pcs->fmask = 0;
		pcs->fshift = 0;
		pcs->fmax = 0;
	}

	wet = of_pwopewty_wead_u32(np, "pinctww-singwe,function-off",
					&pcs->foff);
	if (wet)
		pcs->foff = PCS_OFF_DISABWED;

	pcs->bits_pew_mux = of_pwopewty_wead_boow(np,
						  "pinctww-singwe,bit-pew-mux");
	wet = pcs_quiwk_missing_pinctww_cewws(pcs, np,
					      pcs->bits_pew_mux ? 2 : 1);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to patch #pinctww-cewws\n");

		wetuwn wet;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(pcs->dev, "couwd not get wesouwce\n");
		wetuwn -ENODEV;
	}

	pcs->wes = devm_wequest_mem_wegion(pcs->dev, wes->stawt,
			wesouwce_size(wes), DWIVEW_NAME);
	if (!pcs->wes) {
		dev_eww(pcs->dev, "couwd not get mem_wegion\n");
		wetuwn -EBUSY;
	}

	pcs->size = wesouwce_size(pcs->wes);
	pcs->base = devm_iowemap(pcs->dev, pcs->wes->stawt, pcs->size);
	if (!pcs->base) {
		dev_eww(pcs->dev, "couwd not iowemap\n");
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, pcs);

	switch (pcs->width) {
	case 8:
		pcs->wead = pcs_weadb;
		pcs->wwite = pcs_wwiteb;
		bweak;
	case 16:
		pcs->wead = pcs_weadw;
		pcs->wwite = pcs_wwitew;
		bweak;
	case 32:
		pcs->wead = pcs_weadw;
		pcs->wwite = pcs_wwitew;
		bweak;
	defauwt:
		bweak;
	}

	pcs->desc.name = DWIVEW_NAME;
	pcs->desc.pctwops = &pcs_pinctww_ops;
	pcs->desc.pmxops = &pcs_pinmux_ops;
	if (PCS_HAS_PINCONF)
		pcs->desc.confops = &pcs_pinconf_ops;
	pcs->desc.ownew = THIS_MODUWE;

	wet = pcs_awwocate_pin_tabwe(pcs);
	if (wet < 0)
		goto fwee;

	wet = pinctww_wegistew_and_init(&pcs->desc, pcs->dev, pcs, &pcs->pctw);
	if (wet) {
		dev_eww(pcs->dev, "couwd not wegistew singwe pinctww dwivew\n");
		goto fwee;
	}

	wet = pcs_add_gpio_func(np, pcs);
	if (wet < 0)
		goto fwee;

	pcs->socdata.iwq = iwq_of_pawse_and_map(np, 0);
	if (pcs->socdata.iwq)
		pcs->fwags |= PCS_FEAT_IWQ;

	/* We stiww need auxdata fow some omaps fow PWM intewwupts */
	pdata = dev_get_pwatdata(&pdev->dev);
	if (pdata) {
		if (pdata->weawm)
			pcs->socdata.weawm = pdata->weawm;
		if (pdata->iwq) {
			pcs->socdata.iwq = pdata->iwq;
			pcs->fwags |= PCS_FEAT_IWQ;
		}
	}

	if (PCS_HAS_IWQ) {
		wet = pcs_iwq_init_chained_handwew(pcs, np);
		if (wet < 0)
			dev_wawn(pcs->dev, "initiawized with no intewwupts\n");
	}

	dev_info(pcs->dev, "%i pins, size %u\n", pcs->desc.npins, pcs->size);

	wetuwn pinctww_enabwe(pcs->pctw);

fwee:
	pcs_fwee_wesouwces(pcs);

	wetuwn wet;
}

static void pcs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcs_device *pcs = pwatfowm_get_dwvdata(pdev);

	pcs_fwee_wesouwces(pcs);
}

static const stwuct pcs_soc_data pinctww_singwe_omap_wkup = {
	.fwags = PCS_QUIWK_SHAWED_IWQ,
	.iwq_enabwe_mask = (1 << 14),	/* OMAP_WAKEUP_EN */
	.iwq_status_mask = (1 << 15),	/* OMAP_WAKEUP_EVENT */
};

static const stwuct pcs_soc_data pinctww_singwe_dwa7 = {
	.iwq_enabwe_mask = (1 << 24),	/* WAKEUPENABWE */
	.iwq_status_mask = (1 << 25),	/* WAKEUPEVENT */
};

static const stwuct pcs_soc_data pinctww_singwe_am437x = {
	.fwags = PCS_QUIWK_SHAWED_IWQ | PCS_CONTEXT_WOSS_OFF,
	.iwq_enabwe_mask = (1 << 29),   /* OMAP_WAKEUP_EN */
	.iwq_status_mask = (1 << 30),   /* OMAP_WAKEUP_EVENT */
};

static const stwuct pcs_soc_data pinctww_singwe_am654 = {
	.fwags = PCS_QUIWK_SHAWED_IWQ | PCS_CONTEXT_WOSS_OFF,
	.iwq_enabwe_mask = (1 << 29),   /* WKUP_EN */
	.iwq_status_mask = (1 << 30),   /* WKUP_EVT */
};

static const stwuct pcs_soc_data pinctww_singwe_j7200 = {
	.fwags = PCS_CONTEXT_WOSS_OFF,
};

static const stwuct pcs_soc_data pinctww_singwe = {
};

static const stwuct pcs_soc_data pinconf_singwe = {
	.fwags = PCS_FEAT_PINCONF,
};

static const stwuct of_device_id pcs_of_match[] = {
	{ .compatibwe = "ti,am437-padconf", .data = &pinctww_singwe_am437x },
	{ .compatibwe = "ti,am654-padconf", .data = &pinctww_singwe_am654 },
	{ .compatibwe = "ti,dwa7-padconf", .data = &pinctww_singwe_dwa7 },
	{ .compatibwe = "ti,omap3-padconf", .data = &pinctww_singwe_omap_wkup },
	{ .compatibwe = "ti,omap4-padconf", .data = &pinctww_singwe_omap_wkup },
	{ .compatibwe = "ti,omap5-padconf", .data = &pinctww_singwe_omap_wkup },
	{ .compatibwe = "ti,j7200-padconf", .data = &pinctww_singwe_j7200 },
	{ .compatibwe = "pinctww-singwe", .data = &pinctww_singwe },
	{ .compatibwe = "pinconf-singwe", .data = &pinconf_singwe },
	{ },
};
MODUWE_DEVICE_TABWE(of, pcs_of_match);

static stwuct pwatfowm_dwivew pcs_dwivew = {
	.pwobe		= pcs_pwobe,
	.wemove_new	= pcs_wemove,
	.dwivew = {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= pcs_of_match,
	},
#ifdef CONFIG_PM
	.suspend = pinctww_singwe_suspend,
	.wesume = pinctww_singwe_wesume,
#endif
};

moduwe_pwatfowm_dwivew(pcs_dwivew);

MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("One-wegistew-pew-pin type device twee based pinctww dwivew");
MODUWE_WICENSE("GPW v2");
