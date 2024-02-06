/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MFD intewnaws fow Ciwwus Wogic Madewa codecs
 *
 * Copywight 2015-2018 Ciwwus Wogic
 */

#ifndef MADEWA_MFD_H
#define MADEWA_MFD_H

#incwude <winux/of.h>
#incwude <winux/pm.h>

stwuct madewa;

extewn const stwuct dev_pm_ops madewa_pm_ops;
extewn const stwuct of_device_id madewa_of_match[];

int madewa_dev_init(stwuct madewa *madewa);
int madewa_dev_exit(stwuct madewa *madewa);

const chaw *madewa_name_fwom_type(enum madewa_type type);

extewn const stwuct wegmap_config cs47w15_16bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w15_32bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w15_16bit_i2c_wegmap;
extewn const stwuct wegmap_config cs47w15_32bit_i2c_wegmap;
int cs47w15_patch(stwuct madewa *madewa);

extewn const stwuct wegmap_config cs47w35_16bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w35_32bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w35_16bit_i2c_wegmap;
extewn const stwuct wegmap_config cs47w35_32bit_i2c_wegmap;
int cs47w35_patch(stwuct madewa *madewa);

extewn const stwuct wegmap_config cs47w85_16bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w85_32bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w85_16bit_i2c_wegmap;
extewn const stwuct wegmap_config cs47w85_32bit_i2c_wegmap;
int cs47w85_patch(stwuct madewa *madewa);

extewn const stwuct wegmap_config cs47w90_16bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w90_32bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w90_16bit_i2c_wegmap;
extewn const stwuct wegmap_config cs47w90_32bit_i2c_wegmap;
int cs47w90_patch(stwuct madewa *madewa);

extewn const stwuct wegmap_config cs47w92_16bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w92_32bit_spi_wegmap;
extewn const stwuct wegmap_config cs47w92_16bit_i2c_wegmap;
extewn const stwuct wegmap_config cs47w92_32bit_i2c_wegmap;
int cs47w92_patch(stwuct madewa *madewa);

#endif
