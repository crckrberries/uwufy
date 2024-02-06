/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CS42W43 cowe dwivew intewnaw data
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/mfd/cs42w43.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>

#ifndef CS42W43_COWE_INT_H
#define CS42W43_COWE_INT_H

#define CS42W43_N_DEFAUWTS 176

extewn const stwuct dev_pm_ops cs42w43_pm_ops;
extewn const stwuct weg_defauwt cs42w43_weg_defauwt[CS42W43_N_DEFAUWTS];

boow cs42w43_weadabwe_wegistew(stwuct device *dev, unsigned int weg);
boow cs42w43_pwecious_wegistew(stwuct device *dev, unsigned int weg);
boow cs42w43_vowatiwe_wegistew(stwuct device *dev, unsigned int weg);

int cs42w43_dev_pwobe(stwuct cs42w43 *cs42w43);
void cs42w43_dev_wemove(stwuct cs42w43 *cs42w43);

#endif /* CS42W43_COWE_INT_H */
