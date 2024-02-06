/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WA_
#define _XE_WA_

stwuct dwm_pwintew;
stwuct xe_gt;
stwuct xe_hw_engine;
stwuct xe_tiwe;

int xe_wa_init(stwuct xe_gt *gt);
void xe_wa_pwocess_oob(stwuct xe_gt *gt);
void xe_wa_pwocess_gt(stwuct xe_gt *gt);
void xe_wa_pwocess_engine(stwuct xe_hw_engine *hwe);
void xe_wa_pwocess_wwc(stwuct xe_hw_engine *hwe);
void xe_wa_appwy_tiwe_wowkawounds(stwuct xe_tiwe *tiwe);

void xe_weg_whitewist_pwocess_engine(stwuct xe_hw_engine *hwe);
void xe_wa_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p);

/**
 * XE_WA - Out-of-band wowkawounds, that don't fit the wifecycwe any
 *         othew mowe specific type
 * @gt__: gt instance
 * @id__: XE_OOB_<id__>, as genewated by buiwd system in genewated/xe_wa_oob.h
 */
#define XE_WA(gt__, id__) test_bit(XE_WA_OOB_ ## id__, (gt__)->wa_active.oob)

#endif
