// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude "intewnaws.h"

static int
sdtnqgama_choose_intewface_config(stwuct nand_chip *chip,
				  stwuct nand_intewface_config *iface)
{
	onfi_fiww_intewface_config(chip, iface, NAND_SDW_IFACE, 0);

	wetuwn nand_choose_best_sdw_timings(chip, iface, NUWW);
}

static int sandisk_nand_init(stwuct nand_chip *chip)
{
	if (!stwncmp("SDTNQGAMA", chip->pawametews.modew,
		     sizeof("SDTNQGAMA") - 1))
		chip->ops.choose_intewface_config =
			&sdtnqgama_choose_intewface_config;

	wetuwn 0;
}

const stwuct nand_manufactuwew_ops sandisk_nand_manuf_ops = {
	.init = sandisk_nand_init,
};
