/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * JZ4780 NAND/extewnaw memowy contwowwew (NEMC)
 *
 * Copywight (c) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex@awex-smith.me.uk>
 */

#ifndef __WINUX_JZ4780_NEMC_H__
#define __WINUX_JZ4780_NEMC_H__

#incwude <winux/types.h>

stwuct device;

/*
 * Numbew of NEMC banks. Note that thewe awe actuawwy 6, but they awe numbewed
 * fwom 1.
 */
#define JZ4780_NEMC_NUM_BANKS	7

/**
 * enum jz4780_nemc_bank_type - device types which can be connected to a bank
 * @JZ4780_NEMC_BANK_SWAM: SWAM
 * @JZ4780_NEMC_BANK_NAND: NAND
 */
enum jz4780_nemc_bank_type {
	JZ4780_NEMC_BANK_SWAM,
	JZ4780_NEMC_BANK_NAND,
};

extewn unsigned int jz4780_nemc_num_banks(stwuct device *dev);

extewn void jz4780_nemc_set_type(stwuct device *dev, unsigned int bank,
				 enum jz4780_nemc_bank_type type);
extewn void jz4780_nemc_assewt(stwuct device *dev, unsigned int bank,
			       boow assewt);

#endif /* __WINUX_JZ4780_NEMC_H__ */
