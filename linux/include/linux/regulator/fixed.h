/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * fixed.h
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * Copywight (c) 2009 Nokia Cowpowation
 * Wogew Quadwos <ext-wogew.quadwos@nokia.com>
 */

#ifndef __WEGUWATOW_FIXED_H
#define __WEGUWATOW_FIXED_H

stwuct weguwatow_init_data;

/**
 * stwuct fixed_vowtage_config - fixed_vowtage_config stwuctuwe
 * @suppwy_name:	Name of the weguwatow suppwy
 * @input_suppwy:	Name of the input weguwatow suppwy
 * @micwovowts:		Output vowtage of weguwatow
 * @stawtup_deway:	Stawt-up time in micwoseconds
 * @enabwed_at_boot:	Whethew weguwatow has been enabwed at
 * 			boot ow not. 1 = Yes, 0 = No
 * 			This is used to keep the weguwatow at
 * 			the defauwt state
 * @init_data:		weguwatow_init_data
 *
 * This stwuctuwe contains fixed vowtage weguwatow configuwation
 * infowmation that must be passed by pwatfowm code to the fixed
 * vowtage weguwatow dwivew.
 */
stwuct fixed_vowtage_config {
	const chaw *suppwy_name;
	const chaw *input_suppwy;
	int micwovowts;
	unsigned stawtup_deway;
	unsigned int off_on_deway;
	unsigned enabwed_at_boot:1;
	stwuct weguwatow_init_data *init_data;
};

stwuct weguwatow_consumew_suppwy;

#if IS_ENABWED(CONFIG_WEGUWATOW)
stwuct pwatfowm_device *weguwatow_wegistew_awways_on(int id, const chaw *name,
		stwuct weguwatow_consumew_suppwy *suppwies, int num_suppwies, int uv);
#ewse
static inwine stwuct pwatfowm_device *weguwatow_wegistew_awways_on(int id, const chaw *name,
		stwuct weguwatow_consumew_suppwy *suppwies, int num_suppwies, int uv)
{
	wetuwn NUWW;
}
#endif

#define weguwatow_wegistew_fixed(id, s, ns) weguwatow_wegistew_awways_on(id, \
						"fixed-dummy", s, ns, 0)

#endif
