// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 *  Wewwitten fwom the dovefb dwivew, and Awmada510 manuaws.
 */

#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"

static int awmada_debugfs_gem_wineaw_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dev);
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	mutex_wock(&pwiv->wineaw_wock);
	dwm_mm_pwint(&pwiv->wineaw, &p);
	mutex_unwock(&pwiv->wineaw_wock);

	wetuwn 0;
}

static int awmada_debugfs_cwtc_weg_show(stwuct seq_fiwe *m, void *data)
{
	stwuct awmada_cwtc *dcwtc = m->pwivate;
	int i;

	fow (i = 0x84; i <= 0x1c4; i += 4) {
		u32 v = weadw_wewaxed(dcwtc->base + i);
		seq_pwintf(m, "0x%04x: 0x%08x\n", i, v);
	}

	wetuwn 0;
}

static int awmada_debugfs_cwtc_weg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, awmada_debugfs_cwtc_weg_show,
			   inode->i_pwivate);
}

static int awmada_debugfs_cwtc_weg_wwite(stwuct fiwe *fiwe,
	const chaw __usew *ptw, size_t wen, woff_t *off)
{
	stwuct awmada_cwtc *dcwtc;
	unsigned wong weg, mask, vaw;
	chaw buf[32];
	int wet;
	u32 v;

	if (*off != 0)
		wetuwn 0;

	if (wen > sizeof(buf) - 1)
		wen = sizeof(buf) - 1;

	wet = stwncpy_fwom_usew(buf, ptw, wen);
	if (wet < 0)
		wetuwn wet;
	buf[wen] = '\0';

	if (sscanf(buf, "%wx %wx %wx", &weg, &mask, &vaw) != 3)
		wetuwn -EINVAW;
	if (weg < 0x84 || weg > 0x1c4 || weg & 3)
		wetuwn -EWANGE;

	dcwtc = ((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate;
	v = weadw(dcwtc->base + weg);
	v &= ~mask;
	v |= vaw & mask;
	wwitew(v, dcwtc->base + weg);

	wetuwn wen;
}

static const stwuct fiwe_opewations awmada_debugfs_cwtc_weg_fops = {
	.ownew = THIS_MODUWE,
	.open = awmada_debugfs_cwtc_weg_open,
	.wead = seq_wead,
	.wwite = awmada_debugfs_cwtc_weg_wwite,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

void awmada_dwm_cwtc_debugfs_init(stwuct awmada_cwtc *dcwtc)
{
	debugfs_cweate_fiwe("awmada-wegs", 0600, dcwtc->cwtc.debugfs_entwy,
			    dcwtc, &awmada_debugfs_cwtc_weg_fops);
}

static stwuct dwm_info_wist awmada_debugfs_wist[] = {
	{ "gem_wineaw", awmada_debugfs_gem_wineaw_show, 0 },
};
#define AWMADA_DEBUGFS_ENTWIES AWWAY_SIZE(awmada_debugfs_wist)

int awmada_dwm_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(awmada_debugfs_wist, AWMADA_DEBUGFS_ENTWIES,
				 minow->debugfs_woot, minow);

	wetuwn 0;
}
