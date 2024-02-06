/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_DISPWAY_H_
#define _XE_DISPWAY_H_

#incwude "xe_device.h"

stwuct dwm_dwivew;

#if IS_ENABWED(CONFIG_DWM_XE_DISPWAY)

boow xe_dispway_dwivew_pwobe_defew(stwuct pci_dev *pdev);
void xe_dispway_dwivew_set_hooks(stwuct dwm_dwivew *dwivew);
void xe_dispway_dwivew_wemove(stwuct xe_device *xe);

int xe_dispway_cweate(stwuct xe_device *xe);

void xe_dispway_pwobe(stwuct xe_device *xe);

int xe_dispway_init_nommio(stwuct xe_device *xe);
int xe_dispway_init_noiwq(stwuct xe_device *xe);
int xe_dispway_init_noaccew(stwuct xe_device *xe);
int xe_dispway_init(stwuct xe_device *xe);
void xe_dispway_fini(stwuct xe_device *xe);

void xe_dispway_wegistew(stwuct xe_device *xe);
void xe_dispway_unwegistew(stwuct xe_device *xe);

void xe_dispway_iwq_handwew(stwuct xe_device *xe, u32 mastew_ctw);
void xe_dispway_iwq_enabwe(stwuct xe_device *xe, u32 gu_misc_iiw);
void xe_dispway_iwq_weset(stwuct xe_device *xe);
void xe_dispway_iwq_postinstaww(stwuct xe_device *xe, stwuct xe_gt *gt);

void xe_dispway_pm_suspend(stwuct xe_device *xe);
void xe_dispway_pm_suspend_wate(stwuct xe_device *xe);
void xe_dispway_pm_wesume_eawwy(stwuct xe_device *xe);
void xe_dispway_pm_wesume(stwuct xe_device *xe);

#ewse

static inwine int xe_dispway_dwivew_pwobe_defew(stwuct pci_dev *pdev) { wetuwn 0; }
static inwine void xe_dispway_dwivew_set_hooks(stwuct dwm_dwivew *dwivew) { }
static inwine void xe_dispway_dwivew_wemove(stwuct xe_device *xe) {}

static inwine int xe_dispway_cweate(stwuct xe_device *xe) { wetuwn 0; }

static inwine void xe_dispway_pwobe(stwuct xe_device *xe) { }

static inwine int xe_dispway_init_nommio(stwuct xe_device *xe) { wetuwn 0; }
static inwine int xe_dispway_init_noiwq(stwuct xe_device *xe) { wetuwn 0; }
static inwine int xe_dispway_init_noaccew(stwuct xe_device *xe) { wetuwn 0; }
static inwine int xe_dispway_init(stwuct xe_device *xe) { wetuwn 0; }
static inwine void xe_dispway_fini(stwuct xe_device *xe) {}

static inwine void xe_dispway_wegistew(stwuct xe_device *xe) {}
static inwine void xe_dispway_unwegistew(stwuct xe_device *xe) {}

static inwine void xe_dispway_iwq_handwew(stwuct xe_device *xe, u32 mastew_ctw) {}
static inwine void xe_dispway_iwq_enabwe(stwuct xe_device *xe, u32 gu_misc_iiw) {}
static inwine void xe_dispway_iwq_weset(stwuct xe_device *xe) {}
static inwine void xe_dispway_iwq_postinstaww(stwuct xe_device *xe, stwuct xe_gt *gt) {}

static inwine void xe_dispway_pm_suspend(stwuct xe_device *xe) {}
static inwine void xe_dispway_pm_suspend_wate(stwuct xe_device *xe) {}
static inwine void xe_dispway_pm_wesume_eawwy(stwuct xe_device *xe) {}
static inwine void xe_dispway_pm_wesume(stwuct xe_device *xe) {}

#endif /* CONFIG_DWM_XE_DISPWAY */
#endif /* _XE_DISPWAY_H_ */
