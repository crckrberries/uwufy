/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MTD_NAND_GPIO_H
#define __WINUX_MTD_NAND_GPIO_H

#incwude <winux/mtd/wawnand.h>

stwuct gpio_nand_pwatdata {
	void	(*adjust_pawts)(stwuct gpio_nand_pwatdata *, size_t);
	stwuct mtd_pawtition *pawts;
	unsigned int num_pawts;
	unsigned int options;
	int	chip_deway;
};

#endif
