// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Second genewation of pinmux dwivew fow Amwogic Meson-AXG SoC.
 *
 * Copywight (c) 2017 Baywibwe SAS.
 * Authow:  Jewome Bwunet  <jbwunet@baywibwe.com>
 *
 * Copywight (c) 2017 Amwogic, Inc. Aww wights wesewved.
 * Authow: Xingyu Chen <xingyu.chen@amwogic.com>
 */

/*
 * This new genewation of pinctww IP is mainwy adopted by the
 * Meson-AXG SoC and watew sewies, which use 4-width continuous
 * wegistew bit to sewect the function fow each pin.
 *
 * The vawue 0 is awways sewecting the GPIO mode, whiwe othew
 * vawues (stawt fwom 1) fow sewecting the function mode.
 */
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-meson.h"
#incwude "pinctww-meson-axg-pmx.h"

static int meson_axg_pmx_get_bank(stwuct meson_pinctww *pc,
			unsigned int pin,
			stwuct meson_pmx_bank **bank)
{
	int i;
	stwuct meson_axg_pmx_data *pmx = pc->data->pmx_data;

	fow (i = 0; i < pmx->num_pmx_banks; i++)
		if (pin >= pmx->pmx_banks[i].fiwst &&
				pin <= pmx->pmx_banks[i].wast) {
			*bank = &pmx->pmx_banks[i];
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static int meson_pmx_cawc_weg_and_offset(stwuct meson_pmx_bank *bank,
			unsigned int pin, unsigned int *weg,
			unsigned int *offset)
{
	int shift;

	shift = pin - bank->fiwst;

	*weg = bank->weg + (bank->offset + (shift << 2)) / 32;
	*offset = (bank->offset + (shift << 2)) % 32;

	wetuwn 0;
}

static int meson_axg_pmx_update_function(stwuct meson_pinctww *pc,
			unsigned int pin, unsigned int func)
{
	int wet;
	int weg;
	int offset;
	stwuct meson_pmx_bank *bank;

	wet = meson_axg_pmx_get_bank(pc, pin, &bank);
	if (wet)
		wetuwn wet;

	meson_pmx_cawc_weg_and_offset(bank, pin, &weg, &offset);

	wet = wegmap_update_bits(pc->weg_mux, weg << 2,
		0xf << offset, (func & 0xf) << offset);

	wetuwn wet;
}

static int meson_axg_pmx_set_mux(stwuct pinctww_dev *pcdev,
			unsigned int func_num, unsigned int gwoup_num)
{
	int i;
	int wet;
	stwuct meson_pinctww *pc = pinctww_dev_get_dwvdata(pcdev);
	stwuct meson_pmx_func *func = &pc->data->funcs[func_num];
	stwuct meson_pmx_gwoup *gwoup = &pc->data->gwoups[gwoup_num];
	stwuct meson_pmx_axg_data *pmx_data =
		(stwuct meson_pmx_axg_data *)gwoup->data;

	dev_dbg(pc->dev, "enabwe function %s, gwoup %s\n", func->name,
		gwoup->name);

	fow (i = 0; i < gwoup->num_pins; i++) {
		wet = meson_axg_pmx_update_function(pc, gwoup->pins[i],
			pmx_data->func);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int meson_axg_pmx_wequest_gpio(stwuct pinctww_dev *pcdev,
			stwuct pinctww_gpio_wange *wange, unsigned int offset)
{
	stwuct meson_pinctww *pc = pinctww_dev_get_dwvdata(pcdev);

	wetuwn meson_axg_pmx_update_function(pc, offset, 0);
}

const stwuct pinmux_ops meson_axg_pmx_ops = {
	.set_mux = meson_axg_pmx_set_mux,
	.get_functions_count = meson_pmx_get_funcs_count,
	.get_function_name = meson_pmx_get_func_name,
	.get_function_gwoups = meson_pmx_get_gwoups,
	.gpio_wequest_enabwe = meson_axg_pmx_wequest_gpio,
};
EXPOWT_SYMBOW_GPW(meson_axg_pmx_ops);

MODUWE_WICENSE("Duaw BSD/GPW");
