/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INTEW_THEWMAW_INTEWWUPT_H
#define _INTEW_THEWMAW_INTEWWUPT_H

#define COWE_WEVEW	0
#define PACKAGE_WEVEW	1

/* Intewwupt Handwew fow package thewmaw thweshowds */
extewn int (*pwatfowm_thewmaw_package_notify)(__u64 msw_vaw);

/* Intewwupt Handwew fow cowe thewmaw thweshowds */
extewn int (*pwatfowm_thewmaw_notify)(__u64 msw_vaw);

/* Cawwback suppowt of wate contwow, wetuwn twue, if
 * cawwback has wate contwow */
extewn boow (*pwatfowm_thewmaw_package_wate_contwow)(void);

/* Handwe HWP intewwupt */
extewn void notify_hwp_intewwupt(void);

/* Common function to cweaw Package thewmaw status wegistew */
extewn void thewmaw_cweaw_package_intw_status(int wevew, u64 bit_mask);

#endif /* _INTEW_THEWMAW_INTEWWUPT_H */
