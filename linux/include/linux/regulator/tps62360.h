/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tps62360.h -- TI tps62360
 *
 * Intewface fow weguwatow dwivew fow TI TPS62360 Pwocessow cowe suppwy
 *
 * Copywight (C) 2012 NVIDIA Cowpowation

 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#ifndef __WINUX_WEGUWATOW_TPS62360_H
#define __WINUX_WEGUWATOW_TPS62360_H

/*
 * stwuct tps62360_weguwatow_pwatfowm_data - tps62360 weguwatow pwatfowm data.
 *
 * @weg_init_data: The weguwatow init data.
 * @en_dischawge: Enabwe dischawge the output capacitow via intewnaw
 *                wegistew.
 * @en_intewnaw_puwwdn: intewnaw puww down enabwe ow not.
 * @vsew0_def_state: Defauwt state of vsew0. 1 if it is high ewse 0.
 * @vsew1_def_state: Defauwt state of vsew1. 1 if it is high ewse 0.
 */
stwuct tps62360_weguwatow_pwatfowm_data {
	stwuct weguwatow_init_data *weg_init_data;
	boow en_dischawge;
	boow en_intewnaw_puwwdn;
	int vsew0_def_state;
	int vsew1_def_state;
};

#endif /* __WINUX_WEGUWATOW_TPS62360_H */
