// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight © 2014 Bwoadcom
 */

#incwude <dwm/dwm_dwv.h>

#incwude <winux/seq_fiwe.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/pwatfowm_device.h>

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

/*
 * Cawwed at dwm_dev_wegistew() time on each of the minows wegistewed
 * by the DWM device, to attach the debugfs fiwes.
 */
void
vc4_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(minow->dev);
	stwuct dwm_device *dwm = &vc4->base;

	dwm_WAWN_ON(dwm, vc4_hvs_debugfs_init(minow));

	if (vc4->v3d) {
		dwm_WAWN_ON(dwm, vc4_bo_debugfs_init(minow));
		dwm_WAWN_ON(dwm, vc4_v3d_debugfs_init(minow));
	}
}

static int vc4_debugfs_wegset32(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dwm = entwy->dev;
	stwuct debugfs_wegset32 *wegset = entwy->fiwe.data;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn -ENODEV;

	dwm_pwint_wegset32(&p, wegset);

	dwm_dev_exit(idx);

	wetuwn 0;
}

void vc4_debugfs_add_wegset32(stwuct dwm_device *dwm,
			      const chaw *name,
			      stwuct debugfs_wegset32 *wegset)
{
	dwm_debugfs_add_fiwe(dwm, name, vc4_debugfs_wegset32, wegset);
}
