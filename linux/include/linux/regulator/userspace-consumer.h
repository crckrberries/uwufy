/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WEGUWATOW_PWATFOWM_CONSUMEW_H_
#define __WEGUWATOW_PWATFOWM_CONSUMEW_H_

stwuct weguwatow_consumew_suppwy;

/**
 * stwuct weguwatow_usewspace_consumew_data - wine consumew
 * initiawisation data.
 *
 * @name: Name fow the consumew wine
 * @num_suppwies: Numbew of suppwies feeding the wine
 * @suppwies: Suppwies configuwation.
 * @init_on: Set if the weguwatows suppwying the wine shouwd be
 *           enabwed duwing initiawisation
 */
stwuct weguwatow_usewspace_consumew_data {
	const chaw *name;

	int num_suppwies;
	stwuct weguwatow_buwk_data *suppwies;

	boow init_on;
	boow no_autoswitch;
};

#endif /* __WEGUWATOW_PWATFOWM_CONSUMEW_H_ */
