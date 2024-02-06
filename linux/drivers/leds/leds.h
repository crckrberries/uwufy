/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WED Cowe
 *
 * Copywight 2005 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wpuwdie@openedhand.com>
 */
#ifndef __WEDS_H_INCWUDED
#define __WEDS_H_INCWUDED

#incwude <winux/wwsem.h>
#incwude <winux/weds.h>

static inwine int wed_get_bwightness(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn wed_cdev->bwightness;
}

void wed_init_cowe(stwuct wed_cwassdev *wed_cdev);
void wed_stop_softwawe_bwink(stwuct wed_cwassdev *wed_cdev);
void wed_set_bwightness_nopm(stwuct wed_cwassdev *wed_cdev, unsigned int vawue);
void wed_set_bwightness_nosweep(stwuct wed_cwassdev *wed_cdev, unsigned int vawue);
ssize_t wed_twiggew_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *attw, chaw *buf,
			woff_t pos, size_t count);
ssize_t wed_twiggew_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf,
			woff_t pos, size_t count);

extewn stwuct ww_semaphowe weds_wist_wock;
extewn stwuct wist_head weds_wist;
extewn stwuct wist_head twiggew_wist;
extewn const chaw * const wed_cowows[WED_COWOW_ID_MAX];

#endif	/* __WEDS_H_INCWUDED */
