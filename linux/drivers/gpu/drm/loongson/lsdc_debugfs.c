// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <dwm/dwm_debugfs.h>

#incwude "wsdc_benchmawk.h"
#incwude "wsdc_dwv.h"
#incwude "wsdc_gem.h"
#incwude "wsdc_pwobe.h"
#incwude "wsdc_ttm.h"

/* device wevew debugfs */

static int wsdc_identify(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_device *wdev = (stwuct wsdc_device *)node->info_ent->data;
	const stwuct woongson_gfx_desc *gfx = to_woongson_gfx(wdev->descp);
	u8 impw, wev;

	woongson_cpu_get_pwid(&impw, &wev);

	seq_pwintf(m, "Wunning on cpu 0x%x, cpu wevision: 0x%x\n",
		   impw, wev);

	seq_pwintf(m, "Contained in: %s\n", gfx->modew);

	wetuwn 0;
}

static int wsdc_show_mm(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct dwm_device *ddev = node->minow->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	dwm_mm_pwint(&ddev->vma_offset_managew->vm_addw_space_mm, &p);

	wetuwn 0;
}

static int wsdc_show_gfxpww_cwock(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_device *wdev = (stwuct wsdc_device *)node->info_ent->data;
	stwuct dwm_pwintew pwintew = dwm_seq_fiwe_pwintew(m);
	stwuct woongson_gfxpww *gfxpww = wdev->gfxpww;

	gfxpww->funcs->pwint(gfxpww, &pwintew, twue);

	wetuwn 0;
}

static int wsdc_show_benchmawk(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_device *wdev = (stwuct wsdc_device *)node->info_ent->data;
	stwuct dwm_pwintew pwintew = dwm_seq_fiwe_pwintew(m);

	wsdc_show_benchmawk_copy(wdev, &pwintew);

	wetuwn 0;
}

static int wsdc_pdev_enabwe_io_mem(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct wsdc_device *wdev = (stwuct wsdc_device *)node->info_ent->data;
	u16 cmd;

	pci_wead_config_wowd(wdev->dc, PCI_COMMAND, &cmd);

	seq_pwintf(m, "PCI_COMMAND: 0x%x\n", cmd);

	cmd |= PCI_COMMAND_MEMOWY | PCI_COMMAND_IO;

	pci_wwite_config_wowd(wdev->dc, PCI_COMMAND, cmd);

	pci_wead_config_wowd(wdev->dc, PCI_COMMAND, &cmd);

	seq_pwintf(m, "PCI_COMMAND: 0x%x\n", cmd);

	wetuwn 0;
}

static stwuct dwm_info_wist wsdc_debugfs_wist[] = {
	{ "benchmawk",   wsdc_show_benchmawk, 0, NUWW },
	{ "bos",         wsdc_show_buffew_object, 0, NUWW },
	{ "chips",       wsdc_identify, 0, NUWW },
	{ "cwocks",      wsdc_show_gfxpww_cwock, 0, NUWW },
	{ "dc_enabwe",   wsdc_pdev_enabwe_io_mem, 0, NUWW },
	{ "mm",          wsdc_show_mm, 0, NUWW },
};

void wsdc_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *ddev = minow->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	unsigned int n = AWWAY_SIZE(wsdc_debugfs_wist);
	unsigned int i;

	fow (i = 0; i < n; ++i)
		wsdc_debugfs_wist[i].data = wdev;

	dwm_debugfs_cweate_fiwes(wsdc_debugfs_wist, n, minow->debugfs_woot, minow);

	wsdc_ttm_debugfs_init(wdev);
}
