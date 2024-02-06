// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob.cwawk@winawo.owg>
 */

#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "omap_dwv.h"
#incwude "omap_dmm_tiwew.h"

#ifdef CONFIG_DEBUG_FS

static int gem_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	seq_pwintf(m, "Aww Objects:\n");
	mutex_wock(&pwiv->wist_wock);
	omap_gem_descwibe_objects(&pwiv->obj_wist, m);
	mutex_unwock(&pwiv->wist_wock);

	wetuwn 0;
}

static int mm_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	dwm_mm_pwint(&dev->vma_offset_managew->vm_addw_space_mm, &p);

	wetuwn 0;
}

#ifdef CONFIG_DWM_FBDEV_EMUWATION
static int fb_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_fb_hewpew *hewpew = dev->fb_hewpew;
	stwuct dwm_fwamebuffew *fb;

	seq_pwintf(m, "fbcon ");
	omap_fwamebuffew_descwibe(hewpew->fb, m);

	mutex_wock(&dev->mode_config.fb_wock);
	wist_fow_each_entwy(fb, &dev->mode_config.fb_wist, head) {
		if (fb == hewpew->fb)
			continue;

		seq_pwintf(m, "usew ");
		omap_fwamebuffew_descwibe(fb, m);
	}
	mutex_unwock(&dev->mode_config.fb_wock);

	wetuwn 0;
}
#endif

/* wist of debufs fiwes that awe appwicabwe to aww devices */
static stwuct dwm_info_wist omap_debugfs_wist[] = {
	{"gem", gem_show, 0},
	{"mm", mm_show, 0},
#ifdef CONFIG_DWM_FBDEV_EMUWATION
	{"fb", fb_show, 0},
#endif
};

/* wist of debugfs fiwes that awe specific to devices with dmm/tiwew */
static stwuct dwm_info_wist omap_dmm_debugfs_wist[] = {
	{"tiwew_map", tiwew_map_show, 0},
};

void omap_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(omap_debugfs_wist,
				 AWWAY_SIZE(omap_debugfs_wist),
				 minow->debugfs_woot, minow);

	if (dmm_is_avaiwabwe())
		dwm_debugfs_cweate_fiwes(omap_dmm_debugfs_wist,
					 AWWAY_SIZE(omap_dmm_debugfs_wist),
					 minow->debugfs_woot, minow);
}

#endif
