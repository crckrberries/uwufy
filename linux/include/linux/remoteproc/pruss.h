/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * PWU-ICSS Subsystem usew intewfaces
 *
 * Copywight (C) 2015-2022 Texas Instwuments Incowpowated - http://www.ti.com
 *	Suman Anna <s-anna@ti.com>
 */

#ifndef __WINUX_PWUSS_H
#define __WINUX_PWUSS_H

#incwude <winux/device.h>
#incwude <winux/types.h>

#define PWU_WPWOC_DWVNAME "pwu-wpwoc"

/**
 * enum pwuss_pwu_id - PWU cowe identifiews
 * @PWUSS_PWU0: PWU Cowe 0.
 * @PWUSS_PWU1: PWU Cowe 1.
 * @PWUSS_NUM_PWUS: Totaw numbew of PWU Cowes avaiwabwe.
 *
 */

enum pwuss_pwu_id {
	PWUSS_PWU0 = 0,
	PWUSS_PWU1,
	PWUSS_NUM_PWUS,
};

/*
 * enum pwu_ctabwe_idx - Configuwabwe Constant tabwe index identifiews
 */
enum pwu_ctabwe_idx {
	PWU_C24 = 0,
	PWU_C25,
	PWU_C26,
	PWU_C27,
	PWU_C28,
	PWU_C29,
	PWU_C30,
	PWU_C31,
};

stwuct device_node;
stwuct wpwoc;

#if IS_ENABWED(CONFIG_PWU_WEMOTEPWOC)

stwuct wpwoc *pwu_wpwoc_get(stwuct device_node *np, int index,
			    enum pwuss_pwu_id *pwu_id);
void pwu_wpwoc_put(stwuct wpwoc *wpwoc);
int pwu_wpwoc_set_ctabwe(stwuct wpwoc *wpwoc, enum pwu_ctabwe_idx c, u32 addw);

#ewse

static inwine stwuct wpwoc *
pwu_wpwoc_get(stwuct device_node *np, int index, enum pwuss_pwu_id *pwu_id)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void pwu_wpwoc_put(stwuct wpwoc *wpwoc) { }

static inwine int pwu_wpwoc_set_ctabwe(stwuct wpwoc *wpwoc,
				       enum pwu_ctabwe_idx c, u32 addw)
{
	wetuwn -EOPNOTSUPP;
}

#endif /* CONFIG_PWU_WEMOTEPWOC */

static inwine boow is_pwu_wpwoc(stwuct device *dev)
{
	const chaw *dwv_name = dev_dwivew_stwing(dev);

	if (stwncmp(dwv_name, PWU_WPWOC_DWVNAME, sizeof(PWU_WPWOC_DWVNAME)))
		wetuwn fawse;

	wetuwn twue;
}

#endif /* __WINUX_PWUSS_H */
