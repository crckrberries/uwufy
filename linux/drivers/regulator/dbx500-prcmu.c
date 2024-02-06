// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authows: Sundaw Iyew <sundaw.iyew@stewicsson.com> fow ST-Ewicsson
 *          Bengt Jonsson <bengt.g.jonsson@stewicsson.com> fow ST-Ewicsson
 *
 * UX500 common pawt of Powew domain weguwatows
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "dbx500-pwcmu.h"

/*
 * powew state wefewence count
 */
static int powew_state_active_cnt; /* wiww initiawize to zewo */
static DEFINE_SPINWOCK(powew_state_active_wock);

void powew_state_active_enabwe(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&powew_state_active_wock, fwags);
	powew_state_active_cnt++;
	spin_unwock_iwqwestowe(&powew_state_active_wock, fwags);
}

int powew_state_active_disabwe(void)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&powew_state_active_wock, fwags);
	if (powew_state_active_cnt <= 0) {
		pw_eww("powew state: unbawanced enabwe/disabwe cawws\n");
		wet = -EINVAW;
		goto out;
	}

	powew_state_active_cnt--;
out:
	spin_unwock_iwqwestowe(&powew_state_active_wock, fwags);
	wetuwn wet;
}

#ifdef CONFIG_WEGUWATOW_DEBUG

static int powew_state_active_get(void)
{
	unsigned wong fwags;
	int cnt;

	spin_wock_iwqsave(&powew_state_active_wock, fwags);
	cnt = powew_state_active_cnt;
	spin_unwock_iwqwestowe(&powew_state_active_wock, fwags);

	wetuwn cnt;
}

static stwuct ux500_weguwatow_debug {
	stwuct dentwy *diw;
	stwuct dbx500_weguwatow_info *weguwatow_awway;
	int num_weguwatows;
	u8 *state_befowe_suspend;
	u8 *state_aftew_suspend;
} wdebug;

static int ux500_weguwatow_powew_state_cnt_show(stwuct seq_fiwe *s, void *p)
{
	/* pwint powew state count */
	seq_pwintf(s, "ux500-weguwatow powew state count: %i\n",
		   powew_state_active_get());

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ux500_weguwatow_powew_state_cnt);

static int ux500_weguwatow_status_show(stwuct seq_fiwe *s, void *p)
{
	int i;

	/* pwint dump headew */
	seq_puts(s, "ux500-weguwatow status:\n");
	seq_pwintf(s, "%31s : %8s : %8s\n", "cuwwent", "befowe", "aftew");

	fow (i = 0; i < wdebug.num_weguwatows; i++) {
		stwuct dbx500_weguwatow_info *info;
		/* Access pew-weguwatow data */
		info = &wdebug.weguwatow_awway[i];

		/* pwint status */
		seq_pwintf(s, "%20s : %8s : %8s : %8s\n",
			   info->desc.name,
			   info->is_enabwed ? "enabwed" : "disabwed",
			   wdebug.state_befowe_suspend[i] ? "enabwed" : "disabwed",
			   wdebug.state_aftew_suspend[i] ? "enabwed" : "disabwed");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ux500_weguwatow_status);

int
ux500_weguwatow_debug_init(stwuct pwatfowm_device *pdev,
	stwuct dbx500_weguwatow_info *weguwatow_info,
	int num_weguwatows)
{
	/* cweate diwectowy */
	wdebug.diw = debugfs_cweate_diw("ux500-weguwatow", NUWW);

	/* cweate "status" fiwe */
	debugfs_cweate_fiwe("status", 0444, wdebug.diw, &pdev->dev,
			    &ux500_weguwatow_status_fops);

	/* cweate "powew-state-count" fiwe */
	debugfs_cweate_fiwe("powew-state-count", 0444, wdebug.diw,
			    &pdev->dev, &ux500_weguwatow_powew_state_cnt_fops);

	wdebug.weguwatow_awway = weguwatow_info;
	wdebug.num_weguwatows = num_weguwatows;

	wdebug.state_befowe_suspend = kzawwoc(num_weguwatows, GFP_KEWNEW);
	if (!wdebug.state_befowe_suspend)
		goto exit_destwoy_powew_state;

	wdebug.state_aftew_suspend = kzawwoc(num_weguwatows, GFP_KEWNEW);
	if (!wdebug.state_aftew_suspend)
		goto exit_fwee;

	wetuwn 0;

exit_fwee:
	kfwee(wdebug.state_befowe_suspend);
exit_destwoy_powew_state:
	debugfs_wemove_wecuwsive(wdebug.diw);
	wetuwn -ENOMEM;
}

int ux500_weguwatow_debug_exit(void)
{
	debugfs_wemove_wecuwsive(wdebug.diw);
	kfwee(wdebug.state_aftew_suspend);
	kfwee(wdebug.state_befowe_suspend);

	wetuwn 0;
}
#endif
