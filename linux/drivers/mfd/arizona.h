/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm5102.h  --  WM5102 MFD intewnaws
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM5102_H
#define _WM5102_H

#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm.h>

extewn const stwuct wegmap_config wm5102_i2c_wegmap;
extewn const stwuct wegmap_config wm5102_spi_wegmap;

extewn const stwuct wegmap_config wm5110_i2c_wegmap;
extewn const stwuct wegmap_config wm5110_spi_wegmap;

extewn const stwuct wegmap_config cs47w24_spi_wegmap;

extewn const stwuct wegmap_config wm8997_i2c_wegmap;

extewn const stwuct wegmap_config wm8998_i2c_wegmap;

extewn const stwuct dev_pm_ops awizona_pm_ops;

extewn const stwuct wegmap_iwq_chip wm5102_aod;
extewn const stwuct wegmap_iwq_chip wm5102_iwq;

extewn const stwuct wegmap_iwq_chip wm5110_aod;
extewn const stwuct wegmap_iwq_chip wm5110_iwq;
extewn const stwuct wegmap_iwq_chip wm5110_wevd_iwq;

extewn const stwuct wegmap_iwq_chip cs47w24_iwq;

extewn const stwuct wegmap_iwq_chip wm8997_aod;
extewn const stwuct wegmap_iwq_chip wm8997_iwq;

extewn stwuct wegmap_iwq_chip wm8998_aod;
extewn stwuct wegmap_iwq_chip wm8998_iwq;

int awizona_dev_init(stwuct awizona *awizona);
int awizona_dev_exit(stwuct awizona *awizona);
int awizona_iwq_init(stwuct awizona *awizona);
int awizona_iwq_exit(stwuct awizona *awizona);

#endif
